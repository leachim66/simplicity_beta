/*
  Copyright (C) 2015 by
  Dipl.-Ing. Michael Niederle

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Library General Public License, version 2, or
  (at your option) under the terms of the GNU Lesser General Public License,
  version 3.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser (Library) General Public License for more details.

  For details of the GNU General Public License see the accompanying
  files LGPLv2.txt and LGLPv3.txt or
  http://www.gnu.org/licenses/lgpl-2.0.html
  http://www.gnu.org/licenses/lgpl-3.0.html
  or write to the
  Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#include "common.h"

//#define DEBUG
//#define PROFILE

#define INITIAL_POOL_SIZE      0x400000
#define MEMORY_SOFT_LIMIT       0x10000
#define MEMORY_HARD_LIMIT        0x4000

#define LARGE_OBJECT_THRESHOLD   0x1000

#if UINTPTR_MAX == 0xffffffffffffffff
  #define FIRST_INVALID_ADDRESS 0xc000000000000000UL
  #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)
#else
  #define FIRST_INVALID_ADDRESS 0xc0000000
  #define SAMPLE_POINTER ((void *)0x12345678)
#endif

#define ENCODE_ADDRESS(addr) ((void *)(FIRST_INVALID_ADDRESS|(uintptr_t)(addr) >> 2))
#define DECODE_ADDRESS(addr) ((void *)((uintptr_t)(addr) << 2))
#define IS_AN_INVALID_ADDRESS(addr) ((void *)(addr) >= (void *)FIRST_INVALID_ADDRESS)

#define IS_COLLECTED(addr) (((void *)(addr)) >= coll_node_buf && ((void *)(addr)) < coll_node_buf_end)
//#define IS_OLD(addr) (((void *)(addr)) >= static_node_buf && ((void *)(addr)) < static_node_buf_end)
#define IS_OLD(addr) false
#define MARK(addr) (((MEMORY_BLOCK *)(addr))-1)->mark = current_mark;

#define TYPEOF(node) (node)->type
#define SIZEOF(node) (node)->attributes->vtable->size

#define TOTAL_FRAME_SIZE(frame) (sizeof(FRAME)+(frame)->slot_count*sizeof(NODE *))


#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define REGISTER register
  #define ASM(x) asm(x)
#else
  #define REGISTER
  #define ASM(x)
#endif

EXPORT REGISTER int argument_count ASM("ebx");
  // the number of input arguments of the current call
EXPORT REGISTER FRAME *arguments ASM("r12");
  // a frame-structure containing all input arguments of the current call
  // all fields of the structure beside the arguments itself are uninitialized
  // the frame structure is used to make it easy for the callee to convert its
  // input arguments into a full-fledged function frame
EXPORT REGISTER NODE *myself ASM("r13");
  // the function object of the called function
EXPORT REGISTER FUNC func ASM("r14");
  // the function pointer itself
EXPORT REGISTER FRAME *frame ASM("r15");
  // the frame-structure of the currently running function

int argument_count_save;
FRAME *arguments_save;
NODE *myself_save;
FUNC func_save;
FRAME *frame_save;

EXPORT int result_count;
  // the number of results the caller expects
EXPORT DYNAMICS *dynamics;
  // a pointer to the current dynamic environment

EXPORT int main_argc;
EXPORT char **main_argv;

typedef enum {
  EM__NORMAL,
  EM__RECORD,
  EM__REPLAY
} EVENT__MODE;

EXPORT EVENT__MODE event__mode = EM__NORMAL;
static FILE *log_fp;
static long action_counter = 0;

typedef struct MEMORY_BLOCK {
  struct MEMORY_BLOCK *link;
  long mark;
  DESTRUCTOR destructor;
} MEMORY_BLOCK;

static MEMORY_BLOCK *memory_blocks;

static void *node_buf;
static void *node_buf_soft_limit;
static void *node_buf_hard_limit;
static void *node_buf_end;
EXPORT void *node_p;
EXPORT void *update_start_p; // helps to prevent unnecessary duplications

//void *static_node_buf;
//void *static_node_buf_end;

EXPORT void *coll_node_buf;
EXPORT void *coll_node_buf_end;

EXPORT NODE *undefined;
EXPORT NODE *zero;
EXPORT NODE *boolean_true;
EXPORT NODE *boolean_false;
EXPORT NODE *empty_string;
EXPORT NODE_GETTER raise_exception_getter;

EXPORT uint64_t instruction_counter = 0;

extern void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future);

// "no_attributes" is used for <types::undefined>

extern void no_such_function(void);
void no_such_attribute(void);

SIMPLE_NODE no_such_attribute_node = {no_such_attribute, NULL};

EXPORT OCTREE no_attributes_level_1 = {{
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&no_such_attribute_node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&no_such_attribute_node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&no_such_attribute_node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&no_such_attribute_node
}};

EXPORT OCTREE no_attributes_level_2 = {{
  &no_attributes_level_1, &no_attributes_level_1,
  &no_attributes_level_1, &no_attributes_level_1,
  &no_attributes_level_1, &no_attributes_level_1,
  &no_attributes_level_1, &no_attributes_level_1
}};

EXPORT OCTREE no_attributes_level_3 = {{
  &no_attributes_level_2, &no_attributes_level_2,
  &no_attributes_level_2, &no_attributes_level_2,
  &no_attributes_level_2, &no_attributes_level_2,
  &no_attributes_level_2, &no_attributes_level_2
}};

EXPORT OCTREE no_attributes_level_4 = {{
  &no_attributes_level_3, &no_attributes_level_3,
  &no_attributes_level_3, &no_attributes_level_3,
  &no_attributes_level_3, &no_attributes_level_3,
  &no_attributes_level_3, &no_attributes_level_3
}};

EXPORT OCTREE no_attributes_level_5 = {{
  &no_attributes_level_4, &no_attributes_level_4,
  &no_attributes_level_4, &no_attributes_level_4,
  &no_attributes_level_4, &no_attributes_level_4,
  &no_attributes_level_4, &no_attributes_level_4
}};

EXPORT OCTREE no_attributes_level_6 = {{
  &no_attributes_level_5, &no_attributes_level_5,
  &no_attributes_level_5, &no_attributes_level_5,
  &no_attributes_level_5, &no_attributes_level_5,
  &no_attributes_level_5, &no_attributes_level_5
}};

EXPORT OCTREE no_attributes_level_7 = {{
  &no_attributes_level_6, &no_attributes_level_6,
  &no_attributes_level_6, &no_attributes_level_6,
  &no_attributes_level_6, &no_attributes_level_6,
  &no_attributes_level_6, &no_attributes_level_6
}};

EXPORT OCTREE no_attributes_level_8 = {{
  &no_attributes_level_7, &no_attributes_level_7,
  &no_attributes_level_7, &no_attributes_level_7,
  &no_attributes_level_7, &no_attributes_level_7,
  &no_attributes_level_7, &no_attributes_level_7
}};

// "undefined_attributes" is used for all other objects

extern SIMPLE_NODE *types__undefined__node;

// the first 8 and all even IDs starting with 10 are by default undefined methods
// all odd IDs starting with 9 are by default attributes initialized to <undefined>

EXPORT OCTREE undefined_attributes_level_1 = {{
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&no_such_attribute_node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&no_such_attribute_node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&no_such_attribute_node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&no_such_attribute_node
}};

OCTREE mixed_attributes_level_1 = {{
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&types__undefined__node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&types__undefined__node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&types__undefined__node,
  (OCTREE *)&no_such_attribute_node, (OCTREE *)&types__undefined__node
}};

EXPORT OCTREE undefined_attributes_level_2 = {{
  &mixed_attributes_level_1, &mixed_attributes_level_1,
  &mixed_attributes_level_1, &mixed_attributes_level_1,
  &mixed_attributes_level_1, &mixed_attributes_level_1,
  &mixed_attributes_level_1, &mixed_attributes_level_1
}};

EXPORT OCTREE undefined_attributes_level_3 = {{
  &undefined_attributes_level_2, &undefined_attributes_level_2,
  &undefined_attributes_level_2, &undefined_attributes_level_2,
  &undefined_attributes_level_2, &undefined_attributes_level_2,
  &undefined_attributes_level_2, &undefined_attributes_level_2
}};

EXPORT OCTREE undefined_attributes_level_4 = {{
  &undefined_attributes_level_3, &undefined_attributes_level_3,
  &undefined_attributes_level_3, &undefined_attributes_level_3,
  &undefined_attributes_level_3, &undefined_attributes_level_3,
  &undefined_attributes_level_3, &undefined_attributes_level_3
}};

EXPORT OCTREE undefined_attributes_level_5 = {{
  &undefined_attributes_level_4, &undefined_attributes_level_4,
  &undefined_attributes_level_4, &undefined_attributes_level_4,
  &undefined_attributes_level_4, &undefined_attributes_level_4,
  &undefined_attributes_level_4, &undefined_attributes_level_4
}};

EXPORT OCTREE undefined_attributes_level_6 = {{
  &undefined_attributes_level_5, &undefined_attributes_level_5,
  &undefined_attributes_level_5, &undefined_attributes_level_5,
  &undefined_attributes_level_5, &undefined_attributes_level_5,
  &undefined_attributes_level_5, &undefined_attributes_level_5
}};

EXPORT OCTREE undefined_attributes_level_7 = {{
  &undefined_attributes_level_6, &undefined_attributes_level_6,
  &undefined_attributes_level_6, &undefined_attributes_level_6,
  &undefined_attributes_level_6, &undefined_attributes_level_6,
  &undefined_attributes_level_6, &undefined_attributes_level_6
}};

EXPORT OCTREE undefined_attributes_level_8 = {{
  &undefined_attributes_level_7, &undefined_attributes_level_7,
  &undefined_attributes_level_7, &undefined_attributes_level_7,
  &undefined_attributes_level_7, &undefined_attributes_level_7,
  &undefined_attributes_level_7, &undefined_attributes_level_7
}};

static void *unused_pool;

static size_t pool_size;
static size_t size_of_new_pool;
static size_t size_of_current_pool;
static size_t size_of_unused_pool;

extern void crash_dump(void);
extern void collect_garbage();

EXPORT int runtime_debug_level = 0;
  // 0: no debug messages
  // 1: important debug messages
  // 2: all debug messages

EXPORT __attribute__ ((noreturn)) void unrecoverable_error(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  vfprintf(stderr, msg, args);
  fprintf(stderr, "\n");
  va_end(args);
  if (instruction_counter > 0) crash_dump();
  exit(EXIT_FAILURE);
}

EXPORT __attribute__ ((noreturn)) void out_of_memory_error(void) {
  unrecoverable_error("Out of memory!");
}

EXPORT __attribute__ ((noreturn)) void invalid_continuation_error(void) {
  unrecoverable_error("Invalid continuation!");
}

EXPORT void *allocate(long size) {
  if ((void *)((char *)node_p+size) > node_buf_hard_limit)
    unrecoverable_error("OUT OF MEMORY (allocating %ld bytes)!", size);
  void *p = node_p;
  node_p = ((char *)node_p)+size;
  return p;
}

EXPORT void *allocate_and_clear(long size) {
  void *buf = allocate(size);
  memset(buf, 0, size);
  return buf;
}

static void *allocate_pool() {
  void *addr = unused_pool;
  unused_pool = NULL;
  size_of_new_pool = size_of_unused_pool;
  if (addr) return addr;
  if (runtime_debug_level > 0) {
    fprintf(
      stderr, "%lu: malloc pool of size %ld for process %d\n",
      instruction_counter, pool_size, getpid());
  }
  addr = malloc(pool_size);
  size_of_new_pool = pool_size;
  if (addr) {
    #ifdef DEBUG
      memset(addr, 0xfe, size_of_new_pool);
    #endif
    return addr;
  }
  unrecoverable_error("MEMORY POOL ALLOCATION FAILED!");
}

static void deallocate_pool(void *pool) {
  #ifdef DEBUG
    memset(pool, 0xfe, size_of_current_pool);
  #endif
  if (size_of_current_pool == pool_size) {
    unused_pool = pool;
    size_of_unused_pool = size_of_current_pool;
  } else {
    if (runtime_debug_level > 0) {
      fprintf(
	stderr, "%lu: free pool of size %ld for process %d\n",
	instruction_counter, size_of_current_pool, getpid());
    }
    free(pool);
    unused_pool = NULL;
  }
}

static uint64_t total_allocated_memory = 0;

EXPORT void *allocate_memory(size_t size) {
  void *p = malloc(size);
  if (!p) out_of_memory_error();
  #ifdef DEBUG
    memset(p, 0xfe, size);
  #endif
  uint64_t previously_allocated_memory = total_allocated_memory;
  total_allocated_memory += size;

  return p;
}

EXPORT void *reallocate_memory(void * buf, size_t size) {
  void *p = realloc(buf, size);
  if (!p) out_of_memory_error();
  size_t previously_allocated_memory = total_allocated_memory;
  total_allocated_memory += size;
  return p;
}

EXPORT void *allocate_gc(long size) {
  if ((void *)((char *)node_p+size) > node_buf_soft_limit) {
    collect_garbage();
  }
  void *p = node_p;
  #ifdef DEBUG
    memset(p, 0xfe, size);
  #endif
  node_p = (char *)node_p+size;
  return p;
}

EXPORT void allocate_arguments(void) {
  if (argument_count == 0) arguments = node_p; // This is essential!
  node_p = (char *)node_p+sizeof(FRAME)+argument_count*sizeof(NODE *);
  arguments->caller_frame = NULL;
  arguments->slot_count = argument_count;
}

EXPORT void *allocate_fixed(long size) {
  void *p = allocate_memory(sizeof(MEMORY_BLOCK)+size);
  ((MEMORY_BLOCK *)p)->link = memory_blocks;
  ((MEMORY_BLOCK *)p)->mark = 0;
  ((MEMORY_BLOCK *)p)->destructor = NULL;
  memory_blocks = p;
  return (char *)p+sizeof(MEMORY_BLOCK);
}

EXPORT void *allocate_fixed_with_destructor(long size, DESTRUCTOR destructor) {
  void *p = allocate_memory(sizeof(MEMORY_BLOCK)+size);
  ((MEMORY_BLOCK *)p)->link = memory_blocks;
  ((MEMORY_BLOCK *)p)->mark = 0;
  ((MEMORY_BLOCK *)p)->destructor = destructor;
  memory_blocks = p;
  return (char *)p+sizeof(MEMORY_BLOCK);
}

EXPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count) {
  long size = sizeof(FRAME)+slot_count*sizeof(NODE *);
  if ((void *)((char *)node_p+size) > node_buf_soft_limit) {
    collect_garbage();
  }
  FRAME *new_frame = node_p;
  node_p = (char *)node_p+size;
  FRAME *caller_frame = frame;
  frame = new_frame;
  frame->caller_frame = caller_frame;
  frame->caller_result_count = result_count;
  frame->slot_count = slot_count;
  while (slot_idx < slot_count) {
    frame->slots[slot_idx++] = undefined;
  }
}

EXPORT void *allocate_large(long size) {
  if (size > LARGE_OBJECT_THRESHOLD)
    return allocate_fixed(size);
  else
    return allocate(size);
}

EXPORT void deallocate_memory(void *buf) {
  free(buf);
}

EXPORT void *copy(const void *buf, long size) {
  if ((void *)((char *)node_p+size) > node_buf_hard_limit) out_of_memory_error();
  void *p = node_p;
  node_p = (char *)node_p+size;
  memcpy(p, buf, size);
  return p;
}

static DYNAMICS empty_dynamics = {{
  &undefined_attributes_level_1, &undefined_attributes_level_2,
  &undefined_attributes_level_3, &undefined_attributes_level_4,
  &undefined_attributes_level_5, &undefined_attributes_level_6,
  &undefined_attributes_level_7, &undefined_attributes_level_8
}};

typedef struct PHASE_2_COLLECTOR {
  void *dummy;
  void *next_collector;
  void (*collector)(void *data);
} PHASE_2_COLLECTOR;

PHASE_2_COLLECTOR *phase_2_collectors;

EXPORT void register_phase_2_collector(void *data) {
  ((PHASE_2_COLLECTOR *)data)->next_collector = phase_2_collectors;
  phase_2_collectors = (PHASE_2_COLLECTOR *)data;
}

extern void set_module(const char *name);

NODE *get_attribute(NODE *node, int idx);
NODE *create_function(FUNC func, int par_cnt);

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
  unrecoverable_error("Caught segfault at address %p", si->si_addr);
}

EXPORT int child_changed_state = false;

void child_sigaction(int signal, siginfo_t *si, void *arg) {
  child_changed_state = true;
}

EXPORT int window_changed_size = false;

void winch_sigaction(int signal, siginfo_t *si, void *arg)
{
  window_changed_size = true;
}

extern NODE *from_c_string(const char *str);

NODE *from_vprintf(const char *msg, va_list args) {
  int n;
  char *big_buf;
  char buf[512];
  n = vsnprintf(buf, 512, msg, args);
  if (n < 512) return from_c_string(buf);
  big_buf = allocate_memory(n+1);
  n = vsprintf(big_buf, msg, args);
  NODE *node = from_c_string(big_buf);
  deallocate_memory(big_buf);
  return node;
}

EXPORT NODE *from_printf(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  NODE *node = from_vprintf(msg, args);
  return node;
}

jmp_buf main_loop_start;

EXPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  NODE *msg_node = from_vprintf(msg, args);
  va_end(args);
  arguments_save = node_p;
  arguments_save->slots[0] = msg_node;
  argument_count_save = 1;
  myself_save = raise_exception_getter();
  func_save = myself_save->type;
  frame_save = frame;
  longjmp(main_loop_start, 1);
}

EXPORT void too_few_arguments_error(void) {
  runtime_error("Too few arguments!");
}

EXPORT void too_many_arguments_error(void) {
  runtime_error("Too many arguments!");
}

EXPORT void invalid_arguments_error(void) {
  runtime_error("Invalid arguments!");
}

EXPORT void too_few_results_error(void) {
  runtime_error("Too few results!");
}

EXPORT void too_many_results_error(void) {
  runtime_error("Too many results!");
}

EXPORT void invalid_results_error(void) {
  runtime_error("Invalid results!");
}

EXPORT void invalid_index_error(void) {
  runtime_error("Invalid index!");
}

EXPORT void divide_by_zero_error(void) {
  runtime_error("Divide by zero!");
}

EXPORT void not_yet_implemented_error(void) {
  runtime_error("Not yet implemented!");
}

EXPORT void no_such_function(void) {
  runtime_error("No such function!");
}

static NODE *last_node;
static int last_attr_idx;
extern const char **polymorphic_function_names;
long debug_string(NODE *node, int indent, int max_depth, char *buf);

EXPORT void no_such_attribute(void) {
  long len = debug_string(last_node, 0, 1, NULL);
  char *buf = malloc(len);
  debug_string(last_node, 0, 1, buf);
  buf[len-1] = 0;
  runtime_error(
    "Attempt to access the undefined attribute <%s> of\n%s",
    polymorphic_function_names[last_attr_idx], buf);
}

EXPORT void resource_error(void) {
  runtime_error("Failed to allocate a resource!");
}

EXPORT void io_error(void) {
  runtime_error("Input-output error!");
}

#ifdef __CYGWIN__
FUNC invalid_continuation;

static void invalid_continuation_function(void) {
#else
void invalid_continuation(void) {
#endif
  runtime_error("Invalid continuation!");
}

EXPORT void initialize_runtime(void) {
  debug_info("initialize runtime\n");

  // set the "object"-bit for "undefined_attributes"
  int i;
  for (i = 1; i < 8; i += 2) {
    mixed_attributes_level_1.nodes[i] =
      (OCTREE *)(((long)mixed_attributes_level_1.nodes[i])|1);
  }

  #ifdef __CYGWIN__
    invalid_continuation = invalid_continuation_function;
  #endif

  struct sigaction sa;
  sigset_t set;

  memset(&sa, 0, sizeof(sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = segfault_sigaction;
  sa.sa_flags   = SA_SIGINFO;
  sigaction(SIGSEGV, &sa, NULL);

  memset(&sa, 0, sizeof(sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = child_sigaction;
  sa.sa_flags   = SA_SIGINFO;
  sigaction(SIGCHLD, &sa, NULL);

  memset(&sa, 0, sizeof(sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = winch_sigaction;
  sa.sa_flags   = SA_SIGINFO;
  sigaction(SIGWINCH, &sa, NULL);

  sigemptyset(&set);
  sigaddset(&set, SIGCHLD); // block SIGCHLD until unblocked
  sigaddset(&set, SIGWINCH); // block SIGWINCH until unblocked
  sigprocmask(SIG_BLOCK, &set, NULL);

  signal(SIGPIPE, SIG_IGN);

  pool_size = INITIAL_POOL_SIZE;
  node_buf = allocate_pool();
  node_buf_end = (char *)node_buf+pool_size;
  node_buf_hard_limit = (char *)node_buf_end-MEMORY_HARD_LIMIT;
  node_buf_soft_limit = (char *)node_buf_end-MEMORY_SOFT_LIMIT;
  node_p = node_buf;

  dynamics = &empty_dynamics;
}

EXPORT void initialize_phase_3(void) {
  NODE_GETTER getter, dummy;
  use_read_only("std", "undefined", &getter, &dummy);
  undefined = getter();
  use_read_only("std", "zero", &getter, &dummy);
  zero = getter();
  use_read_only("std", "true", &getter, &dummy);
  boolean_true = getter();
  use_read_only("std", "false", &getter, &dummy);
  boolean_false = getter();
  use_read_only("std", "empty_string", &getter, &dummy);
  empty_string = getter();
  use_read_only("std", "raise", &getter, &dummy);
  raise_exception_getter = getter;
}

extern NODE *var__std__undefined;

extern void set_module(const char *name);

static int within_garbage_collection;

EXPORT long current_mark;

static void *collect_function(FUNCTION *node);
static long func__types__function___debug_string(
  NODE *node, int indent, int max_depth, char *buf);

static VTABLE vtable__types__function = {
  sizeof(FUNCTION),
  (void *)collect_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__function___debug_string
};

static ATTRIBUTES function_attributes = {
  &vtable__types__function,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static CLOSURE *collect_closure(CLOSURE *node);
static long func__types__closure___debug_string(
  NODE *node, int indent, int max_depth, char *buf);

static VTABLE vtable__types__closure = {
  sizeof(CLOSURE),
  (void *)collect_closure,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__closure___debug_string
};

static ATTRIBUTES closure_attributes = {
  &vtable__types__closure
};

static CONTINUATION *collect_continuation(CONTINUATION *node);
static long func__types__continuation___debug_string(
  NODE *node, int indent, int max_depth, char *buf);

static VTABLE vtable__types__continuation = {
  sizeof(CONTINUATION),
  (void *)collect_continuation,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__continuation___debug_string
};

static ATTRIBUTES continuation_attributes = {
  &vtable__types__continuation
};

extern int is_a_power_of_two(int n);

// declare as "void *" to avoid silly compiler warnings
// prefer static nodes to prevent that static nodes point to dynamic nodes
EXPORT void join_nodes(void *left_node_pp, void *right_node_pp) {
  void *left_p = *(void **)left_node_pp;
  void *right_p = *(void **)right_node_pp;
  void *joined_p;
  /*if (left_p >= static_node_buf && left_p < static_node_buf_end) {
    if (right_p >= static_node_buf && right_p < static_node_buf_end) {
      if (left_p < right_p) {
        joined_p = left_p;
      } else {
        joined_p = right_p;
      }
    } else {
      joined_p = left_p;
    }
  } else {
    if (right_p >= static_node_buf && right_p < static_node_buf_end) {
      joined_p = right_p;
    } else {*/
      if (left_p < right_p) {
        joined_p = left_p;
      } else {
        joined_p = right_p;
      }
  /*  }
  }*/
  *(void **)left_node_pp = joined_p;
  *(void **)right_node_pp = joined_p;
}

EXPORT NODE *clone_object_and_attributes(NODE *node) {
  NODE *new_node = copy(node, node->attributes->vtable->size);
  new_node->attributes = copy(new_node->attributes, sizeof(ATTRIBUTES));
  return new_node;
}

static FUNC *collectors;
int collector_count = 0;

EXPORT void register_collector(FUNC collector) {
  if (collector_count == 0) {
    collectors = allocate_memory(sizeof(FUNC));
  } else if (is_a_power_of_two(collector_count)) {
    collectors = realloc(collectors, 2*collector_count*sizeof(FUNC));
  }
  collectors[collector_count++] = collector;
}

EXPORT NODE *collect_node(NODE *node) {
  if (!IS_COLLECTED(node)) return node;
  void *new_location = *(void **)node;
  if (IS_AN_INVALID_ADDRESS(new_location)) return DECODE_ADDRESS(new_location);
  return node->attributes->vtable->collect(node);
}

static NODE *collect_function_or_value(NODE *node) {
  if ((uintptr_t)node & 1) {
    return (NODE *)(((uintptr_t)collect_node((NODE *)(((uintptr_t)node)-1)))+1);
  } else {
    return collect_node(node);
  }
}

static OCTREE *collect_octree(OCTREE *octree, int depth) {
  if (!IS_COLLECTED(octree)) return octree;
  if (octree->nodes[0] == (OCTREE *)UINTPTR_MAX) return octree->nodes[1];
  OCTREE *new_octree = allocate(sizeof(OCTREE));
  OCTREE *first_node = octree->nodes[0];
  OCTREE *second_node = octree->nodes[1];
  octree->nodes[0] = (OCTREE *)UINTPTR_MAX;
  octree->nodes[1] = new_octree;
  int i;
  if (depth > 0) {
    new_octree->nodes[0] = collect_octree(first_node, depth-1);
    new_octree->nodes[1] = collect_octree(second_node, depth-1);
    for (i = 2; i < 8; ++i) {
      new_octree->nodes[i] = collect_octree(octree->nodes[i], depth-1);
    }
  } else {
    new_octree->nodes[0] = (OCTREE *)collect_function_or_value((NODE *)first_node);
    new_octree->nodes[1] = (OCTREE *)collect_function_or_value((NODE *)second_node);
    for (i = 2; i < 8; ++i) {
      new_octree->nodes[i] = (OCTREE *)collect_function_or_value((NODE *)octree->nodes[i]);
    }
  }
  return new_octree;
}

EXPORT void collect_static_attributes(ATTRIBUTES *attributes) {
  int i;
  for (i = 0; i < 7; ++i) {
    attributes->nodes[i] = collect_octree(attributes->nodes[i], i);
  }
}

EXPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes) {
  if (!IS_COLLECTED(attributes)) return attributes;
  void *new_location = attributes->nodes[0];
  if (IS_AN_INVALID_ADDRESS(new_location)) return DECODE_ADDRESS(new_location);
  ATTRIBUTES *new_attributes = allocate(sizeof(ATTRIBUTES));
  new_attributes->vtable = attributes->vtable;
  OCTREE *node_0 = attributes->nodes[0];
  attributes->nodes[0] = ENCODE_ADDRESS(new_attributes);
  new_attributes->nodes[0] = collect_octree(node_0, 0);
  int i;
  for (i = 1; i < 7; ++i) {
    new_attributes->nodes[i] = collect_octree(attributes->nodes[i], i);
  }
  return new_attributes;
}

EXPORT void *collect_simple_node(SIMPLE_NODE *node) {
  SIMPLE_NODE *new_node = allocate(sizeof(SIMPLE_NODE));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  return new_node;
}

static FRAME *collect_frame(FRAME *frame) {
  if (!IS_COLLECTED(frame)) return frame;
  if (frame->slot_count == 0xffffffff) return (FRAME *)frame->cont;
  FRAME *new_frame = allocate(TOTAL_FRAME_SIZE(frame));
  new_frame->cont = frame->cont;
  new_frame->slot_count = frame->slot_count;
  frame->cont = (void *)new_frame; // new location
  frame->slot_count = 0xffffffff; // invalid value
  new_frame->caller_frame = collect_frame(frame->caller_frame);
  new_frame->caller_result_count = frame->caller_result_count;
  int i;
  for (i = 0; i < new_frame->slot_count; ++i) {
    new_frame->slots[i] = collect_node(frame->slots[i]);
  }
  return new_frame;
}

static DYNAMICS *collect_dynamics(DYNAMICS *dynamics) {
  if (!IS_COLLECTED(dynamics)) return dynamics;
  void *new_location = *(void **)dynamics;
  if (IS_AN_INVALID_ADDRESS(new_location)) return DECODE_ADDRESS(new_location);
  DYNAMICS *new_dynamics = allocate(sizeof(DYNAMICS));
  OCTREE *first_tree = dynamics->nodes[0];
  *(void **)dynamics = ENCODE_ADDRESS(new_dynamics);
  new_dynamics->nodes[0] = collect_octree(first_tree, 0);
  int i;
  for (i = 1; i < 8; ++i) {
    new_dynamics->nodes[i] = collect_octree(dynamics->nodes[i], i);
  }
  return new_dynamics;
}

EXPORT int total_garbage_collections = 0;

EXPORT void collect_garbage() {
  int i;
  ++total_garbage_collections;
  if (runtime_debug_level > 1) {
    fprintf(
      stderr, "%lu: collection #%d\n",
      instruction_counter, total_garbage_collections);
  }
  if (within_garbage_collection) {
    runtime_error(
      "ATTEMPT TO START A GARBAGE COLLECTION FROM WITHIN A GARBAGE "
      "COLLECTION!");
  }

  if (node_p > node_buf_hard_limit) {
    runtime_error("POOL OVERFLOW (%p > %p)", node_p, node_buf_hard_limit);
  }

  //struct timeval t1;
  //gettimeofday(&t1, NULL);

  within_garbage_collection = true;

  phase_2_collectors = NULL;

  coll_node_buf = node_buf;
  coll_node_buf_end = node_buf_end;

  int do_collect_top_of_heap = (arguments == node_p);

  size_of_current_pool = size_of_new_pool;
  node_buf = allocate_pool();
  #ifdef DEBUG
    memset(node_buf, 0xfe, size_of_new_pool);
  #endif
  node_buf_end = (char *)node_buf+pool_size;
  node_buf_hard_limit = (char *)node_buf_end-MEMORY_HARD_LIMIT;
  node_buf_soft_limit = (char *)node_buf_end-MEMORY_SOFT_LIMIT;
  node_p = node_buf;
  for (i = 0; i < collector_count; ++i) {
    collectors[i]();
  }
  collect_static_attributes(&function_attributes);
  collect_static_attributes(&closure_attributes);
  collect_static_attributes(&continuation_attributes);
  dynamics = collect_dynamics(dynamics);
  frame = collect_frame(frame);
  myself = collect_node(myself);
  undefined = collect_node(undefined);
  zero = collect_node(zero);
  boolean_true = collect_node(boolean_true);
  boolean_false = collect_node(boolean_false);
  empty_string = collect_node(empty_string);
  if (do_collect_top_of_heap) {
    for (i = 0; i < argument_count; ++i) {
      arguments->slots[i] = collect_node(arguments->slots[i]);
    }
  } else {
    arguments = collect_frame(arguments);
  }

  while (phase_2_collectors) {
    phase_2_collectors->collector(phase_2_collectors);
    phase_2_collectors = phase_2_collectors->next_collector;
  }


  if (do_collect_top_of_heap) {
    for (i = 0; i < argument_count; ++i) {
      ((FRAME *)node_p)->slots[i] = arguments->slots[i];
    }
    arguments = node_p;
  }

  if (memory_blocks) {
    MEMORY_BLOCK *mbp, **mbpp;
    mbpp = &memory_blocks;
    mbp = memory_blocks;
    while (mbp) {
      if (mbp->mark == current_mark) {
        *mbpp = mbp;
        mbpp = &mbp->link;
        mbp = *mbpp;
      } else {
        MEMORY_BLOCK *p = mbp;
        mbp = mbp->link;
	if (p->destructor) p->destructor(p+1);
        deallocate_memory(p);
      }
    }
    *mbpp = NULL;
    current_mark = 3-current_mark;
  }

  if (5*(node_p-node_buf) > pool_size) pool_size += pool_size;
  deallocate_pool(coll_node_buf);
  update_start_p = node_p;
  if (runtime_debug_level > 1) {
    fprintf(
      stderr, "%lu: memory usage %d / %d\n",
      instruction_counter, node_p-node_buf, pool_size);
  }

  within_garbage_collection = false;
}

static const char* indents_0 = "\t\t\t\t\t";
static const char* indents_2 = "\t\t\t\t\t  ";
static const char* indents_4 = "\t\t\t\t\t    ";
static const char* indents_6 = "\t\t\t\t\t      ";

EXPORT const char *indent_to_string(int indent) {
  if (indent > 40) indent = 40; // acceptable maximum indent
  indent = indent & 0x3e; //make even
  const char *str;
  switch (indent & 7) {
    case 0:
      str = indents_0;
      break;
    case 2:
      str = indents_2;
      break;
    case 4:
      str = indents_4;
      break;
    case 6:
      str = indents_6;
      break;
  }
  return str+5-(indent >> 3);
}

EXPORT int print(char **buf_p, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int len;
  char *buf = *buf_p;
  if (buf) {
    len = vsprintf(buf, format, args);
    *buf_p = buf+len;
  } else {
    len = vsnprintf(NULL, 0, format, args);
  }
  va_end(args);
  return len;
}

static int vprint(char **buf_p, const char *format, va_list args) {
  int len;
  char *buf = *buf_p;
  if (buf) {
    len = vsprintf(buf, format, args);
    *buf_p = buf+len;
  } else {
    len = vsnprintf(NULL, 0, format, args);
  }
  return len;
}

EXPORT int debug_print(int indent, char *buf, const char *format, ...) {
  va_list args;
  int len = 0;
  va_start(args, format);
  if (indent < 0) {
    if (buf) *buf++ = ' ';
    ++len;
  }
  len += vprint(&buf, format, args);
  va_end(args);
  if (buf) *buf = '\n';
  return len+1;
}

EXPORT int debug_print_head(int *indent_p, char **buf_p, const char *format, ...) {
  va_list args;
  long len = 0;
  int indent = *indent_p;
  char *buf = *buf_p;
  if (indent < 0) {
    if (buf) *buf++ = '\n';
    ++len;
    indent = -indent;
    const char *head_indent = indent_to_string(indent);
    len += print(&buf, head_indent);
  }
  va_start(args, format);
  len += vprint(&buf, format, args);
  va_end(args);
  if (buf) *buf++ = '\n';
  *indent_p = indent+2;
  *buf_p = buf;
  return len+1;
}

EXPORT uint32_t to_int8(NODE *node) {
  return node->attributes->vtable->to_uint8(node);
}

EXPORT uint64_t to_int16(NODE *node) {
  return node->attributes->vtable->to_uint16(node);
}

EXPORT uint32_t to_int32(NODE *node) {
  return node->attributes->vtable->to_uint32(node);
}

EXPORT uint64_t to_int64(NODE *node) {
  return node->attributes->vtable->to_uint64(node);
}

EXPORT uint32_t to_uint8(NODE *node) {
  return node->attributes->vtable->to_uint8(node);
}

EXPORT uint64_t to_uint16(NODE *node) {
  return node->attributes->vtable->to_uint16(node);
}

EXPORT uint32_t to_uint32(NODE *node) {
  return node->attributes->vtable->to_uint32(node);
}

EXPORT uint64_t to_uint64(NODE *node) {
  return node->attributes->vtable->to_uint64(node);
}

EXPORT uint32_t to_uchar32(NODE *node) {
  return node->attributes->vtable->to_uchar32(node);
}

EXPORT int to_bool(NODE *node) {
  return node->attributes->vtable->to_bool(node);
}

EXPORT int to_int(NODE *node) {
  return node->attributes->vtable->to_int(node);
}

EXPORT long to_long(NODE *node) {
  return node->attributes->vtable->to_long(node);
}

EXPORT double to_double(NODE *node) {
  return node->attributes->vtable->to_double(node);
}

EXPORT char *to_c_string(NODE *node) {
  return node->attributes->vtable->to_c_string(node);
}

EXPORT uint8_t *to_octets(NODE *node, long *size_p) {
  return node->attributes->vtable->to_octets(node, size_p);
}

EXPORT NODE *get_item_of(NODE *node, long idx) {
  return node->attributes->vtable->get_item_of(node, idx);
}

EXPORT long length_of(NODE *node) {
  return node->attributes->vtable->length_of(node);
}

EXPORT void unfold(NODE *node) {
  node->attributes->vtable->unfold(node);
}

EXPORT long debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return node->attributes->vtable->debug_string(node, indent, max_depth, buf);
}

EXPORT void optional_item(NODE *item) {
  if (item->type != undefined->type) {
    arguments->slots[argument_count++] = item;
  }
}

#ifdef PROFILE
  extern const char **polymorphic_function_names;
  #define MAX_ATTR_NUM 1000
  static int max_attr_id = -1;
  static long dispatches[MAX_ATTR_NUM];
#endif

EXPORT NODE *get_attribute(NODE *node, int idx) {
  #ifdef PROFILE
    if (idx < MAX_ATTR_NUM) {
      if (idx > max_attr_id) max_attr_id = idx;
      ++dispatches[idx];
    }
  #endif
  last_node = node; // for error messages
  last_attr_idx = idx; // for error messages
  if (idx < 8) {
    return (NODE *)node->attributes->nodes[0]->nodes[idx];
  } else if (idx < 72) {
    idx -= 8;
    return (NODE *)node->attributes->nodes[1]->nodes[idx >> 3]->nodes[idx & 7];
  } else if (idx < 584) {
    idx -= 72;
    return (NODE *)node->attributes->nodes[2]->nodes[idx >> 6]->nodes[(idx >> 3) & 7]->nodes[idx & 7];
  } else if (idx < 4680) {
    idx -= 584;
    return (NODE *)node->attributes->nodes[3]->nodes[idx >> 9]->nodes[(idx >> 6) & 7]->nodes[(idx >> 3) & 7]->nodes[idx & 7];
  } else {
    idx -= 4680;
    return (NODE *)node->attributes->nodes[4]->nodes[idx >> 12]->nodes[(idx >> 9) & 7]->nodes[(idx >> 6) & 7]->nodes[(idx >> 3) & 7]->nodes[idx & 7];
  }
}

EXPORT void polymorph_dispatch(int idx) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (idx < 8) {
    myself = (NODE *)arguments->slots[0]->attributes->nodes[0]->nodes[idx];
  } else if (idx < 72) {
    idx -= 8;
    myself = (NODE *)arguments->slots[0]->attributes->nodes[1]->nodes[idx >> 3]->nodes[idx & 7];
  } else if (idx < 584) {
    idx -= 72;
    myself = (NODE *)arguments->slots[0]->attributes->nodes[2]->nodes[idx >> 6]->nodes[(idx >> 3) & 7]->nodes[idx & 7];
  } else if (idx < 4680) {
    idx -= 584;
    myself = (NODE *)arguments->slots[0]->attributes->nodes[3]->nodes[idx >> 9]->nodes[(idx >> 6) & 7]->nodes[(idx >> 3) & 7]->nodes[idx & 7];
  } else {
    idx -= 4680;
    myself = (NODE *)arguments->slots[0]->attributes->nodes[4]->nodes[idx >> 12]->nodes[(idx >> 9) & 7]->nodes[(idx >> 6) & 7]->nodes[(idx >> 3) & 7]->nodes[idx & 7];
  }
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      invalid_arguments_error();
      return;
    }
    arguments = node_p;
    arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);
    func = frame->cont;
    frame->cont = invalid_continuation;
  } else {
    func = myself->type;
  }
}

EXPORT void set_attribute(ATTRIBUTES *attributes, int idx, void *attr) {
  int depth = 0;
  int n = 8;
  while (idx >= n) {
    ++depth;
    idx -= n;
    n <<= 3;
  }
  OCTREE **interior_pp = &attributes->nodes[depth];
  OCTREE *interior_p = *interior_pp;
  while (depth > 0) {
    if ((void *)interior_p < update_start_p || (void *)interior_p >= node_p) {
      interior_p = copy(interior_p, sizeof(OCTREE));
      *interior_pp = interior_p;
    }
    interior_pp = &interior_p->nodes[(idx >> 3*depth) & 7];
    interior_p = *interior_pp;
    --depth;
  }
  if ((void *)interior_p < update_start_p || (void *)interior_p >= node_p) {
    interior_p = copy(interior_p, sizeof(OCTREE));
    *interior_pp = interior_p;
  }
  interior_p->nodes[idx & 7] = attr;
}

EXPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr) {
  set_attribute(attributes, idx, MAKE_ATTRIBUTE_VALUE(attr));
}

void reset_log_file(void) {
  fseek(log_fp, 0, SEEK_SET);
}

static char get_character(void) {
  int chr = getc(log_fp);
  if (chr == EOF) runtime_error("End of log file encountered!");
  return (char)chr;
}

static int digit_value(char chr) {
  if (chr < '0' || chr > '9') {
    runtime_error("Invalid number in event log!");
  }
  return chr-'0';
}

static long get_number(terminator) {
  long val = 0;
  int do_negate = false;
  char chr;
  do {
    chr = get_character();
  } while (chr <= 0x20);
  if (chr == '-') {
    do_negate = true;
  } else {
    val = digit_value(chr);
  }
  while (true) {
    chr = get_character();
    if (chr < '0' || chr > '9') break;
    val = 10*val+digit_value(chr);
  }
  if (do_negate) val = -val;
  return val;
}

EXPORT void record__event(const char *name) {
  fprintf(log_fp, "%s\n", name);
}

EXPORT void successful__action(const char *name) {
  ++action_counter;
}

EXPORT void failed__action(const char *name) {
  ++action_counter;
  fprintf(log_fp, "%s (%ld)\n", name, action_counter);
}

EXPORT void replay__event(const char *name) {
  char tag[64];
  char *p = tag;
  char chr;
  do {
    chr = get_character();
  } while (chr <= 0x20);
  while (true) {
    if (chr == '\n') break;
    if (p >= tag+63) runtime_error("Invalid event tag encountered!");
    *p++ = chr;
    chr = get_character();
  };
  *p = 0;
  if (strcmp(name, tag) != 0) {
    runtime_error(
      "Unexpected event tag encountered (encountered \"%s\", expected \"%s\")!",
      tag, name);
  }
}

EXPORT int replay__action(const char *name) {
  return false;
}

EXPORT void report__event(const char *name) {
  printf("%s\n", name);
}

static void print_pointer(FILE *fp, void *ptr) {
  if (ptr) {
    if (ptr == (void *)FIRST_INVALID_ADDRESS) {
      fprintf(fp, "  -1\n");
    } else {
      fprintf(fp, "  1\n");
    }
  } else {
    fprintf(fp, "  0\n");
  }
}

EXPORT void print__pointer(void *ptr) {
  print_pointer(stdout, ptr);
}

EXPORT void store__pointer(void *ptr) {
  print_pointer(log_fp, ptr);
}

EXPORT void retrieve__pointer(void **ptr_p) {
}

static void print_integer(FILE *fp, int val) {
  fprintf(fp, "  %d\n", val);
}

EXPORT void print__integer(int val) {
  print_integer(stdout, val);
}

EXPORT void store__integer(int val) {
  print_integer(log_fp, val);
}

EXPORT void retrieve__integer(int *val_p) {
  int val = (int)get_number();
  *val_p = val;
}

static void print_long_integer(FILE *fp, long val) {
  fprintf(fp, "  %ld\n", val);
}

EXPORT void print__long_integer(long val) {
  print_long_integer(stdout, val);
}

EXPORT void store__long_integer(long val) {
  print_long_integer(log_fp, val);
}

EXPORT void retrieve__long_integer(long *val_p) {
  long val = get_number();
  *val_p = val;
}

static void print_int_array(FILE *fp, const int *buf, long len) {
  fprintf(fp, "  %ld", len);
  if (len > 0) {
    long i;
    for (i = 0; i < len; ++i) {
      if (i % 16 == 0) fprintf(fp, "\n ");
      uint8_t chr = buf[i];
      fprintf(fp, " %d", chr);
    }
  }
  fprintf(fp, "\n");
}

EXPORT void print__int_array(const int *buf, long len) {
  print_int_array(stdout, buf, len);
}

EXPORT void store__int_array(const int *buf, long len) {
  print_int_array(log_fp, buf, len);
}

EXPORT long retrieve__int_array(int **buf_p) {
  long len = get_number();
  int *buf = NULL;
  if (len > 0) {
    buf = allocate_memory(len*sizeof(int));
    long i;
    for (i = 0; i < len; ++i) {
      int v = get_number();
      buf[i] = v;
    }
  }
  *buf_p = buf;
  return len;
}

static void print_memory(FILE *fp, const uint8_t *buf, long len) {
  fprintf(fp, "  %ld", len);
  if (len > 0) {
    long i;
    for (i = 0; i < len; ++i) {
      if (i % 32 == 0) fprintf(fp, "\n  ");
      uint8_t chr = buf[i];
      if (chr > 0x20 && chr < 0x7f && chr != '%') {
        fputc((char)chr, fp);
      } else {
        fprintf(fp, "%%%02x", chr);
      }
    }
  }
  fprintf(fp, "\n");
}

EXPORT void print__memory(const uint8_t *buf, long len) {
  print_memory(stdout, buf, len);
}

EXPORT void store__memory(const uint8_t *buf, long len) {
  print_memory(log_fp, buf, len);
}

EXPORT long retrieve__memory(uint8_t **buf_p) {
  long len = get_number();
  char *buf = NULL;
  if (len > 0) {
    buf = allocate_memory(len);
    long i;
    for (i = 0; i < len; ++i) {
      char chr;
      do {
	chr = get_character();
      } while (chr <= 0x20);
      if (chr == '%') {
	unsigned int val;
	fscanf(log_fp, "%02x", &val);
	buf[i] = (char)val;
      } else {
	buf[i] = chr;
      }
    }
  }
  *buf_p = buf;
  return len;
}

static void print_c_string(FILE *fp, const char *buf) {
  if (buf) {
    uint8_t chr;
    fprintf(fp, "  %ld \"", strlen(buf));
    while (chr = (uint8_t)*buf++) {
      if (chr >= 0x20 && chr < 0x7f && chr != '%') {
        fputc((char)chr, fp);
      } else {
	fprintf(fp, "%%%02x", chr);
      }
    }
    fprintf(fp, "\"\n");
  } else {
    fprintf(fp, "  <null>\n");
  }
}

EXPORT void print__c_string(const char *buf) {
  print_c_string(stdout, buf);
}

EXPORT void store__c_string(const char *buf) {
  print_c_string(log_fp, buf);
}

EXPORT void retrieve__c_string(char **buf_p) {
  long len = get_number();
  if (get_character() != '\"') runtime_error("Invalid string in event log!");
  char *buf = allocate_memory(len+1);
  long i;
  for (i = 0; i < len; ++i) {
    char chr = get_character();
    if (chr == '%') {
      unsigned int val;
      fscanf(log_fp, "%02x", &val);
      buf[i] = (char)val;
    } else {
      buf[i] = chr;
    }
  }
  if (
    get_character() != '\"' || get_character() != '\n'
  ) runtime_error("Invalid string in event log!");
  buf[len] = 0;
  *buf_p = buf;
}

static void *collect_function(FUNCTION *node) {
  FUNCTION *new_node = allocate(sizeof(FUNCTION));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->parameter_count = node->parameter_count;
  return new_node;
}

static long func__types__function___debug_string(
  NODE *node, int indent, int max_depth, char *buf
) {
  const char *module_filename;
  CONTINUATION_INFO *info;
  FUNC func = node->type;
  if (retrieve_continuation_info(func, &module_filename, &info)) {
    return debug_print(indent, buf,
      "<function %s: %d:%d-%d:%d>",
      module_filename,
      info->first_line, info->first_column,
      info->last_line, info->last_column);
  } else {
    return debug_print(indent, buf, "<function %p>", func);
  }
}

extern NODE *from_int(int val);
extern int par_count_id;

EXPORT NODE *create_function(FUNC func, int par_count) {
  NODE *node = allocate(sizeof(FUNCTION));
  node->type = func;
  node->attributes = &function_attributes;
  node->function.parameter_count = par_count;
  return node;
}

static CLOSURE *collect_closure(CLOSURE *node) {
  CLOSURE *new_node = allocate(sizeof(CLOSURE));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->parameter_count = node->parameter_count;
  new_node->frame = collect_frame(node->frame);
  return new_node;
}

static long func__types__closure___debug_string(
  NODE *node, int indent, int max_depth, char *buf
) {
  return debug_print(indent, buf, "<closure>");
}

EXPORT NODE *create_closure(FUNC type, int par_count) {
  NODE *node = allocate(sizeof(CLOSURE));
  node->type = type;
  node->attributes = copy(&closure_attributes, sizeof(ATTRIBUTES));
  node->closure.parameter_count = par_count;
  node->closure.frame = frame;
  return node;
}

__attribute__ ((noreturn)) void already_used_continuation_error(void) {
  unrecoverable_error("Already used continuation!");
}

EXPORT void continuation_type_function(void) {
  dynamics = myself->continuation.dynamics;
  frame = myself->continuation.frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

EXPORT void continuation_trampoline(void) {
  myself = frame->slots[0];
  dynamics = myself->continuation.dynamics;
  frame = myself->continuation.frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static CONTINUATION *collect_continuation(CONTINUATION *node) {
  CONTINUATION *new_node = allocate(sizeof(CONTINUATION));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->result_count = node->result_count;
  new_node->frame = collect_frame(node->frame);
  new_node->dynamics = collect_dynamics(node->dynamics);
  new_node->exit_frame = collect_frame(node->exit_frame);
  return new_node;
}

extern int retrieve_continuation_info(
  FUNC func, const char **filename_p, CONTINUATION_INFO **info_p
);

static long func__types__continuation___debug_string(
  NODE *node, int indent, int max_depth, char *buf
) {
  const char *module_filename;
  CONTINUATION_INFO *info;
  FUNC func = ((CONTINUATION *)node)->frame->cont;
  if (retrieve_continuation_info(func, &module_filename, &info)) {
    return debug_print(indent, buf,
      "<continuation %s: %d:%d-%d:%d>",
      module_filename,
      info->first_line, info->first_column,
      info->last_line, info->last_column);
  } else {
    return debug_print(indent, buf, "<continuation %p>", func);
  }
}

extern NODE *from_int(int val);

EXPORT NODE *create_continuation(void) {
  if (frame->caller_frame->cont == invalid_continuation) return undefined;
  NODE *node = allocate(sizeof(CONTINUATION));
  node->type = continuation_type_function;
  node->attributes = &continuation_attributes;
  node->continuation.frame = frame->caller_frame;
  node->continuation.dynamics = dynamics;
  node->continuation.exit_frame = NULL;
  node->continuation.result_count = result_count;
  return node;
}

EXPORT NODE *create_continuation_with_exit(FUNC exit_func) {
  NODE *node = create_continuation();
  node->type = exit_func;
  node->continuation.exit_frame = frame;
  return node;
}

extern void invalid_arguments_error(void);

static void entry__function__parameter_count_of(void) {
  if (argument_count != 1) invalid_arguments_error();
  int par_count = arguments->slots[0]->function.parameter_count;
  NODE *node = par_count < 0 ? undefined : from_int(par_count);
  arguments = node_p;
  arguments->slots[0] = node;
  argument_count = 1;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static void entry__continuation__parameter_count_of(void) {
  if (argument_count != 1) invalid_arguments_error();
  int par_count = arguments->slots[0]->continuation.result_count;
  NODE *node = par_count < 0 ? undefined : from_int(par_count);
  arguments = node_p;
  arguments->slots[0] = node;
  argument_count = 1;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

EXPORT void initialize_function_attributes(void) {
  NODE_GETTER getter, dummy;
  use_read_only("types", "function", &getter, &dummy);
  NODE *node = getter();
  ATTRIBUTES *function_attr = node->attributes;
  int i;
  for (i = 0; i < 7; ++i) {
    OCTREE *tree = function_attr->nodes[i];
    function_attributes.nodes[i] = tree;
    closure_attributes.nodes[i] = tree;
  }
  update_start_p = node_p;
  set_attribute(
    &function_attributes, par_count_id,
    create_function(entry__function__parameter_count_of, 1));
  update_start_p = node_p;
  set_attribute(
    &closure_attributes, par_count_id,
    create_function(entry__function__parameter_count_of, 1));
}

static void initialize_continuation_attributes(void) {
  NODE_GETTER getter, dummy;
  use_read_only("types", "continuation", &getter, &dummy);
  NODE *node = getter();
  ATTRIBUTES *continuation_attr = node->attributes;
  int i;
  for (i = 0; i < 7; ++i) {
    OCTREE *tree = continuation_attr->nodes[i];
    continuation_attributes.nodes[i] = tree;
  }
  update_start_p = node_p;
  set_attribute(
    &continuation_attributes, par_count_id,
    create_function(entry__continuation__parameter_count_of, 1));
}

static void future_attribute(void) {
  runtime_error("Attempt to call a polymorphic function on a not yet initialized object!");
}

static SIMPLE_NODE future_attribute_node = {future_attribute, NULL};

static OCTREE future_attributes_level_1 = {{
  (OCTREE *)&future_attribute_node, (OCTREE *)&future_attribute_node,
  (OCTREE *)&future_attribute_node, (OCTREE *)&future_attribute_node,
  (OCTREE *)&future_attribute_node, (OCTREE *)&future_attribute_node,
  (OCTREE *)&future_attribute_node, (OCTREE *)&future_attribute_node
}};

static OCTREE future_attributes_level_2 = {{
  &future_attributes_level_1, &future_attributes_level_1,
  &future_attributes_level_1, &future_attributes_level_1,
  &future_attributes_level_1, &future_attributes_level_1,
  &future_attributes_level_1, &future_attributes_level_1
}};

static OCTREE future_attributes_level_3 = {{
  &future_attributes_level_2, &future_attributes_level_2,
  &future_attributes_level_2, &future_attributes_level_2,
  &future_attributes_level_2, &future_attributes_level_2,
  &future_attributes_level_2, &future_attributes_level_2
}};

static OCTREE future_attributes_level_4 = {{
  &future_attributes_level_3, &future_attributes_level_3,
  &future_attributes_level_3, &future_attributes_level_3,
  &future_attributes_level_3, &future_attributes_level_3,
  &future_attributes_level_3, &future_attributes_level_3
}};

static OCTREE future_attributes_level_5 = {{
  &future_attributes_level_4, &future_attributes_level_4,
  &future_attributes_level_4, &future_attributes_level_4,
  &future_attributes_level_4, &future_attributes_level_4,
  &future_attributes_level_4, &future_attributes_level_4
}};

static OCTREE future_attributes_level_6 = {{
  &future_attributes_level_5, &future_attributes_level_5,
  &future_attributes_level_5, &future_attributes_level_5,
  &future_attributes_level_5, &future_attributes_level_5,
  &future_attributes_level_5, &future_attributes_level_5
}};

static OCTREE future_attributes_level_7 = {{
  &future_attributes_level_6, &future_attributes_level_6,
  &future_attributes_level_6, &future_attributes_level_6,
  &future_attributes_level_6, &future_attributes_level_6,
  &future_attributes_level_6, &future_attributes_level_6
}};

static void type__types__future(void) {
  runtime_error("Attempt to call a not yet initialized object!");
}

static ATTRIBUTE_LIST *collect_attribute_list(ATTRIBUTE_LIST *list) {
  if (!list) return list;
  ATTRIBUTE_LIST *new_list = allocate(sizeof(ATTRIBUTE_LIST));
  new_list->link = collect_attribute_list((list->link));
  new_list->idx = list->idx;
  new_list->attr = collect_function_or_value(list->attr);
  return new_list;
}

static FUTURE *collect_future(FUTURE *node) {
  // ATTENTION: NOT YET COMPLETE!
  FUTURE *new_node = allocate(sizeof(NODE));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->link = collect_node(node->link);
  new_node->pending_attributes = collect_attribute_list(node->pending_attributes);
  new_node->dependent_futures = collect_node(node->dependent_futures);
  new_node->prototype = node->prototype;
  new_node->is_already_initialized = node->is_already_initialized;
  return new_node;
}

static long func__types__future___debug_string(
  NODE *node, int indent, int max_depth, char *buf
) {
  return debug_print(indent, buf, "<future>");
}

static VTABLE vtable__types__future = {
  sizeof(FUTURE),
  (void *)collect_future,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__future___debug_string
};

static ATTRIBUTES attributes__types__future = {
  &vtable__types__future,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

EXPORT NODE *create_future(void) {
  NODE *node = allocate(sizeof(FUTURE));
  node->type = type__types__future;
  node->attributes = &attributes__types__future;
  node->future.link = NULL;
  node->future.pending_attributes = NULL;
  node->future.dependent_futures = NULL;
  node->future.prototype = NULL;
  node->future.is_already_initialized = false;
  return node;
}

EXPORT NODE *create_future_with_prototype(NODE *prototype) {
  NODE *node = allocate(sizeof(FUTURE));
  node->type = type__types__future;
  node->attributes = &attributes__types__future;
  node->future.link = NULL;
  node->future.pending_attributes = NULL;
  node->future.dependent_futures = NULL;
  node->future.prototype = prototype;
  node->future.is_already_initialized = false;
  return node;
}

EXPORT void initialize_future(NODE *var, NODE *val) {
  if (val->type == type__types__future) {
    //fprintf(stderr, "initialize future with future\n");
    var->future.link = val->future.dependent_futures;
    var->future.is_already_initialized = true;
    val->future.dependent_futures = var;
  } else {
    do {
      NODE *link = var->future.link;
      NODE *dependent_futures = var->future.dependent_futures;
      ATTRIBUTE_LIST *pending_attributes =  var->future.pending_attributes;
      //fprintf(stderr, "initialize future\n");
      NODE *prototype = var->future.prototype;
      if (prototype) {
	memcpy(var, prototype, prototype->attributes->vtable->size);
	ATTRIBUTES *attr = var->attributes;
	ATTRIBUTES *base_attr = val->attributes;
	int i;
	for (i = 0; i < 7; ++i) {
	  attr->nodes[i] = base_attr->nodes[i];
	}
	if ((void *)attr->vtable->debug_string == (void *)no_such_function) {
          attr->vtable->debug_string = (void *)base_attr->vtable->debug_string;
	}
      } else {
	memcpy(var, val, val->attributes->vtable->size);
      }
      if (pending_attributes) {
	//fprintf(stderr, "initialize pending attributes\n");
	ATTRIBUTES *attributes = var->attributes;
	if (!prototype) {
	  var->attributes = allocate(sizeof(ATTRIBUTES));
	  memcpy(var->attributes, attributes, sizeof(ATTRIBUTES));
	  attributes = var->attributes;
	}
	update_start_p = node_p;
	while (pending_attributes) {
	  if (pending_attributes->idx == -1) {
	    var->type = pending_attributes->attr;
	  } else {
	    set_attribute(attributes, pending_attributes->idx, pending_attributes->attr);
	  }
	  pending_attributes = pending_attributes->link;
	}
      }
      if (dependent_futures) {
	initialize_future(dependent_futures, var);
      }
      var = link;
    } while (var);
  }
}

EXPORT void maybe_initialize_future(NODE *var, NODE *val) {
  if (val != NULL) initialize_future(var, val);
}

EXPORT void initialize_maybe_future(NODE *var, NODE *val) {
  if (var->type == type__types__future && !var->future.is_already_initialized) {
    initialize_future(var, val);
  }
}

EXPORT void assign_value(NODE **dest, NODE *val) {
  if (*dest) {
    initialize_future(*dest, val);
  } else {
    *dest = val;
  }
}

EXPORT void assign_variable(NODE **dest, NODE **var_p) {
  if (!*var_p) *var_p = create_future();
  if (*dest) {
    initialize_future(*dest, *var_p);
  } else {
    *dest = *var_p;
  }
}

EXPORT void def_attribute(NODE **var_p, int idx, void *attr) {
  if (!*var_p) *var_p = create_future();
  NODE *var = *var_p;
  if (var->type == type__types__future) {
    ATTRIBUTE_LIST *attr_list = allocate(sizeof(ATTRIBUTE_LIST));
    attr_list->link = var->future.pending_attributes;
    attr_list->idx = idx;
    attr_list->attr = attr;
    var->future.pending_attributes = attr_list;
  } else {
    //runtime_error("def_attribute called for already defined object!");
    if (idx == -1) {
      //fprintf(stderr, "      define type function\n");
      var->type = attr;
    } else {
      ATTRIBUTES *attributes = var->attributes;
      /*if ((void *)attributes < update_start_p || (void *)attributes >= node_p) {
	var->attributes = allocate(sizeof(ATTRIBUTES));
	memcpy(var->attributes, attributes, sizeof(ATTRIBUTES));
	attributes = var->attributes;
      }*/
      set_attribute(attributes, idx, attr);
    }
  }
}

static CELL *collect_cell(CELL *node) {
  CELL *new_node = allocate(sizeof(CELL));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->contents = collect_node(node->contents);
  return new_node;
}

static VTABLE vtable__types__cell = {
  sizeof(CELL),
  (void *)collect_cell,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
};

static ATTRIBUTES attributes__types__cell = {
  &vtable__types__cell,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

EXPORT NODE *create_cell(void) {
  NODE *node = allocate(sizeof(CELL));
  node->type = NULL;
  node->attributes = &attributes__types__cell;
  node->cell.contents = undefined;
  return node;
}

EXPORT NODE *create_cell_with_contents(NODE *contents) {
  NODE *node = allocate(sizeof(CELL));
  node->type = NULL;
  node->attributes = &attributes__types__cell;
  node->cell.contents = contents;
  return node;
}

EXPORT NODE *get_dynamic_slot(int id) {
  int depth = 0;
  int n = 8;
  while (id >= n) {
    ++depth;
    id -= n;
    n <<= 3;
  }
  OCTREE *interior_p = dynamics->nodes[depth];
  while (depth > 0) {
    interior_p = interior_p->nodes[(id >> 3*depth) & 7];
    --depth;
  }
  return (NODE *)interior_p->nodes[id & 7];
}

EXPORT NODE *get_dynamic_cell(int id) {
  return get_dynamic_slot(id)->cell.contents;
}

EXPORT void set_dynamic_cell(int id, NODE *node) {
  get_dynamic_slot(id)->cell.contents = node;
}

EXPORT void define_dynamic_slot(int id, NODE *node) {
  int depth = 0;
  int n = 8;
  while (id >= n) {
    ++depth;
    id -= n;
    n <<= 3;
  }
  dynamics = copy(dynamics, sizeof(OCTREE));
  OCTREE **interior_pp = &dynamics->nodes[depth];
  OCTREE *interior_p = *interior_pp;
  while (depth > 0) {
    interior_p = copy(interior_p, sizeof(OCTREE));
    *interior_pp = interior_p;
    interior_pp = &interior_p->nodes[(id >> 3*depth) & 7];
    interior_p = *interior_pp;
    --depth;
  }
  interior_p = copy(interior_p, sizeof(OCTREE));
  *interior_pp = interior_p;
  interior_p->nodes[id & 7] = (void *)node;
}

EXPORT void define_dynamic_cell(int id, NODE *node) {
  define_dynamic_slot(id, create_cell_with_contents(node));
}

EXPORT void terminate(int exit_code) {
  #ifdef PROFILE
    fprintf(stderr, "profiling data:\n");
    fprintf(stderr, "  max. attribute id: %d\n", max_attr_id);
    long total = 0;
    int i;
    for (i = 0; i <= max_attr_id; ++i) {
      if (dispatches[i] > 0) {
	fprintf(stderr, "%s: %ld\n", polymorphic_function_names[i], dispatches[i]);
	total += dispatches[i];
      }
    }
    fprintf(stderr, "total: %ld\n", total);
  #endif
  exit(exit_code);
}

int show_debug_info = false;

void debug_info(const char *msg, ...) {
  if (show_debug_info) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
  }
}

static void skip_argument(void) {
  main_argv[1] = main_argv[0];
  ++main_argv;
  --main_argc;
}

extern void debug(FUNC entry);

static open_log_file(void) {
  skip_argument();
  const char *s = main_argv[0];
  const char *p = s;
  while (*p) {
    if (*p++ == '/') s = p;
  }
  char *home = getenv("HOME");
  if (!home) {
    runtime_error(
      "%sing failed due to unset HOME-environment variable",
      event__mode == EM__RECORD ? "Logg" : "Replay");
  }
  char *filename = allocate_memory(strlen(home)+strlen(s)+24);
  sprintf(filename, "%s/.simplicity/%s-event.log", home, s);
  if (event__mode == EM__RECORD) {
    fprintf(stderr, "logging events to \"%s\"\n", filename);
  }
  log_fp = fopen(filename, event__mode == EM__RECORD ? "w" : "r");
  if (!log_fp) {
    perror(filename);
    exit(EXIT_FAILURE);
  }
  deallocate_memory(filename);
}

static __attribute__ ((noreturn)) void main_loop(void) {
  if (setjmp(main_loop_start) != 0) {
    argument_count = argument_count_save;
    arguments = arguments_save;
    myself = myself_save;
    func = func_save;
    frame = frame_save;
  }
  while (true) {
   func();
    ++instruction_counter;
  }
}

EXPORT __attribute__ ((noreturn)) void execute(FUNC entry) {
  initialize_continuation_attributes();

  // allocate a top-level frame to store continuations  frame = node_p;
  frame = node_p;
  node_p = (char *)node_p+sizeof(FRAME);
  frame->cont = NULL;
  frame->caller_frame = NULL;
  frame->caller_result_count = 0;
  frame->slot_count = 0;

  debug_info("execute\n");
  if (main_argc > 1) {
    if (strcmp(main_argv[1], "++RECORD++") == 0) {
      event__mode = EM__RECORD;
      open_log_file();
    } else if (strcmp(main_argv[1], "++DEBUG++") == 0) {
      event__mode = EM__REPLAY;
      open_log_file();
      debug(entry);
    }
  }
  argument_count = 0;
  func = entry;
  main_loop();
}

static jmp_buf back_from_callback;

#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  static int saved_argument_count;
  static FRAME *saved_arguments;
  static NODE *saved_myself;
  static FUNC saved_func;
  static FUNC saved_cont;
#endif

void return_from_callback(void) {
  // save global register variables
  #if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
    saved_argument_count = argument_count;
    saved_arguments = arguments;
    saved_myself = myself;
    saved_func = func;
    saved_cont = frame->cont;
  #endif
  longjmp(back_from_callback, true);
}

EXPORT void invoke_callback(NODE *callback) {
  myself = callback;
  func = myself->type;
  frame->cont = return_from_callback;
  if (!setjmp(back_from_callback)) main_loop();
  #if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
    argument_count = saved_argument_count;
    arguments = saved_arguments;
    myself = saved_myself;
    func = saved_func;
    frame->cont = saved_cont;
  #endif
}
