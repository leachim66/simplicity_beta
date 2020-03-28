#include <runtime/platform.h>
#include <stdint.h>
#include <stdlib.h>
/**********************
D E C L A R A T I O N S
**********************/

#ifndef IMPORT
  #define IMPORT extern
#endif

#ifndef EXPORT
  #define EXPORT
#endif

#ifndef NULL
  #define NULL ((void *)0)
#endif
#define false 0
#define true 1
typedef union NODE NODE;
IMPORT void *coll_node_buf;
IMPORT void *coll_node_buf_end;
IMPORT void *static_node_buf;
IMPORT void *static_node_buf_end;
typedef void (*DESTRUCTOR)(void *);
typedef struct MEMORY_BLOCK {
  struct MEMORY_BLOCK *link;
  long mark;
  DESTRUCTOR destructor;
} MEMORY_BLOCK;
IMPORT long current_mark;
typedef void (*FUNC)(void);
typedef NODE *(*NODE_GETTER)(void);
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
typedef struct CONTINUATION_INFO {
  FUNC continuation;
  struct FRAME_INFO *frame_info;
  uint16_t first_line;
  uint16_t last_line;
  uint8_t first_column;
  uint8_t last_column;
  uint8_t submodule_index;
  uint8_t unused;
} CONTINUATION_INFO;
typedef void *COLLECTOR(void *);
IMPORT uint32_t to_int8(NODE *node);
IMPORT uint64_t to_int16(NODE *node);
IMPORT uint32_t to_int32(NODE *node);
IMPORT uint64_t to_int64(NODE *node);
IMPORT uint32_t to_uint8(NODE *node);
IMPORT uint64_t to_uint16(NODE *node);
IMPORT uint32_t to_uint32(NODE *node);
IMPORT uint64_t to_uint64(NODE *node);
IMPORT uint32_t to_uchar32(NODE *node);
IMPORT int to_bool(NODE *node);
IMPORT int to_int(NODE *node);
IMPORT long to_long(NODE *node);
IMPORT double to_double(NODE *node);
IMPORT char *to_c_string(NODE *node);
IMPORT uint8_t *to_octets(NODE *node, long *size_p);
IMPORT NODE *get_item_of(NODE *node, long idx);
IMPORT long length_of(NODE *node);
IMPORT void unfold(NODE *node);
IMPORT long debug_string(NODE *node, int indent, int max_depth, char *buf);
typedef struct VTABLE {
  size_t size;
  COLLECTOR *collect;
  int8_t (*to_int8)(NODE *);
  int16_t (*to_int16)(NODE *);
  int32_t (*to_int32)(NODE *);
  int64_t (*to_int64)(NODE *);
  uint8_t (*to_uint8)(NODE *);
  uint16_t (*to_uint16)(NODE *);
  uint32_t (*to_uint32)(NODE *);
  uint64_t (*to_uint64)(NODE *);
  uint32_t (*to_uchar32)(NODE *);
  int (*to_bool)(NODE *);
  int (*to_int)(NODE *);
  long (*to_long)(NODE *);
  double (*to_double)(NODE *);
  char *(*to_c_string)(NODE *);
  uint8_t *(*to_octets)(NODE *, long *size_p);
  NODE *(*get_item_of)(NODE *, long idx);
  long (*length_of)(NODE *);
  void (*unfold)(NODE *);
  long (*debug_string)(NODE *, int indent, int max_depth, char *buf);
} VTABLE;
typedef struct OCTREE {
  struct OCTREE *nodes[8];
} OCTREE;
typedef struct ATTRIBUTES {
  struct VTABLE *vtable;
  struct OCTREE *nodes[7];
} ATTRIBUTES;
typedef struct FRAME {
  FUNC cont;
  struct FRAME *caller_frame;
  long caller_result_count;
  long slot_count;
  NODE *slots[0];
} FRAME;
typedef struct DYNAMICS {
  struct OCTREE *nodes[8];
} DYNAMICS;
typedef struct CONTINUATION {
  FUNC type;
  struct ATTRIBUTES *attributes;
  int result_count;
  struct FRAME *frame;
  struct DYNAMICS *dynamics;
  struct FRAME *exit_frame; // used by exit-functions
} CONTINUATION;
typedef struct CLOSURE {
  FUNC type;
  struct ATTRIBUTES *attributes;
  int parameter_count;
  struct FRAME *frame;
} CLOSURE;
typedef struct SIMPLE_NODE {
  FUNC type;
  struct ATTRIBUTES *attributes;
} SIMPLE_NODE;
typedef struct MODULE_INFO {
  struct MODULE_INFO *link;
  const char *name;
  struct CONTINUATION_INFO *continuation_info;
  int continuation_count;
  NODE **var_tab;
  const char **var_names;
  int top_level_count;
  const char **used_namespaces;
  const char *filenames[];
} MODULE_INFO;
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define REGISTER register
#else
  #define REGISTER IMPORT
#endif
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define ASM(x) asm(x)
#else
  #define ASM(x)
#endif
REGISTER FUNC func ASM("r14");
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
IMPORT NODE *from_c_string(const char *str);
IMPORT NODE *undefined;
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void register_collector(FUNC collector);


#if UINTPTR_MAX == 0xffffffffffffffff
  #define FIRST_INVALID_ADDRESS 0xc000000000000000UL
  #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)
#else
  #define FIRST_INVALID_ADDRESS 0xc0000000
  #define SAMPLE_POINTER ((void *)0x12345678)
#endif

#define MAKE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)+1))
#define RETRIEVE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)-1))
#define CONTAINS_AN_ATTRIBUTE_VALUE(node) (((uintptr_t)node)&1)

#define ENCODE_ADDRESS(addr) ((void *)((uintptr_t)addr | 2))
#define DECODE_ADDRESS(addr) ((void *)((uintptr_t)addr & -3))
#define IS_AN_INVALID_ADDRESS(addr) ((uintptr_t)addr & 2)

#define MSB (1L << (8*sizeof(void *)-1))
#define ENCODE_TO_LENGTH(addr) ((void *)(((uintptr_t)addr >> 1) | MSB))
#define DECODE_FROM_LENGTH(addr) ((void *)((uintptr_t)addr << 1))
#define IS_AN_INVALID_LENGTH(addr) ((uintptr_t)addr & MSB)

#define IS_COLLECTED(addr) (((void *)(addr)) >= coll_node_buf && ((void *)(addr)) < coll_node_buf_end)
#define IS_STATIC(addr) (((void *)(addr)) >= static_node_buf && ((void *)(addr)) < static_node_buf_end)
#define MARK(addr) (((MEMORY_BLOCK *)(addr))-1)->mark = current_mark;

#define ALLOCATION_SIZE(size) (((size)+sizeof(void *)-1)&-sizeof(void *))
#define TYPEOF(node) (node)->type
#define SIZEOF(node) (node)->attributes->vtable->size

#ifdef WITHIN_LIBRARY
  #define DEBUG_FILENAME(filename) filename
#else
  #define DEBUG_FILENAME(filename) "./" filename
#endif

#ifdef __CYGWIN__
  extern FUNC invalid_continuation;
#else
  extern void invalid_continuation(void);
#endif
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__operating_system;
static NODE_GETTER get_value_or_future__operating_system;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static struct {
  NODE *std__operating_system;
  NODE *std__hardware_architecture;
  NODE *std__c_compiler;
  NODE *std__current_directory_separator;
  NODE *std__current_path_separator;
} var;
static const char *var_names[] = {
};
static void entry__1_1_std__operating_system(void);
static NODE *func__1_1_std__operating_system;
static NODE *get__std__operating_system(void) {
  return var.std__operating_system;
}
static void entry__2_1_std__hardware_architecture(void);
static NODE *func__2_1_std__hardware_architecture;
static NODE *get__std__hardware_architecture(void) {
  return var.std__hardware_architecture;
}
static void entry__3_1_std__c_compiler(void);
static NODE *func__3_1_std__c_compiler;
static NODE *get__std__c_compiler(void) {
  return var.std__c_compiler;
}
static NODE *func__4_1_std__current_directory_separator;
static void entry__4_1_std__current_directory_separator(void);
static FRAME_INFO frame__4_1_std__current_directory_separator = {0, {}};
static void cont__4_2(void);
static NODE *string__4_3;
static void cont__4_4(void);
static NODE *func__4_5;
static void entry__4_5(void);
static FRAME_INFO frame__4_5 = {0, {}};
static NODE *func__4_6;
static void entry__4_6(void);
static FRAME_INFO frame__4_6 = {0, {}};
static NODE *get__std__current_directory_separator(void) {
  return var.std__current_directory_separator;
}
static NODE *func__5_1_std__current_path_separator;
static void entry__5_1_std__current_path_separator(void);
static FRAME_INFO frame__5_1_std__current_path_separator = {0, {}};
static void cont__5_2(void);
static void cont__5_3(void);
static NODE *func__5_4;
static void entry__5_4(void);
static FRAME_INFO frame__5_4 = {0, {}};
static NODE *func__5_5;
static void entry__5_5(void);
static FRAME_INFO frame__5_5 = {0, {}};
static NODE *get__std__current_path_separator(void) {
  return var.std__current_path_separator;
}
void run__basic__platform(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__platform, NULL, },
  {entry__1_1_std__operating_system, NULL, 42, 66, 24, 0},
  {entry__2_1_std__hardware_architecture, NULL, 68, 87, 29, 0},
  {entry__3_1_std__c_compiler, NULL, 89, 110, 18, 0},
  {entry__4_5, NULL, 115, 115, 5, 10},
  {entry__4_6, NULL, 116, 116, 5, 10},
  {entry__4_1_std__current_directory_separator, NULL, 114, 114, 5, 22},
  {cont__4_2, &frame__4_1_std__current_directory_separator, 114, 114, 5, 31},
  {cont__4_4, &frame__4_1_std__current_directory_separator, 113, 116, 3, 10},
  {entry__5_4, NULL, 121, 121, 5, 10},
  {entry__5_5, NULL, 122, 122, 5, 10},
  {entry__5_1_std__current_path_separator, NULL, 120, 120, 5, 22},
  {cont__5_2, &frame__5_1_std__current_path_separator, 120, 120, 5, 31},
  {cont__5_3, &frame__5_1_std__current_path_separator, 119, 122, 3, 10}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
};
static NODE *character__92;
static NODE *character__47;
static NODE *character__58;
static NODE *character__59;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__platform",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/platform.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__platform(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__1_1_std__operating_system(void) {
  const char *platform =
  #if defined(OS_linux)
    "linux";
  #elif defined(OS_bsd)
    "bsd";
  #elif defined(OS_darwin)
    "darwin";
  #elif defined(OS_cygwin)
    "cygwin";
  #elif defined(OS_posix)
    "posix";
  #elif defined(OS_win)
    "win";
  #else
    NULL;
  #endif
  NODE *result;
  if (platform) {
    result = from_c_string(platform);
  } else {
    result = undefined;
  }
  {
    NODE *result__node = (NODE *)(result);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__2_1_std__hardware_architecture(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  const char *architecture =
  #if defined(ARCHITECTURE_x86_64)
    "x86_64";
  #elif defined(ARCHITECTURE_x86_32)
    "x86_32";
  #elif defined(ARCHITECTURE_arm_32)
    "arm_32";
  #else
    NULL;
  #endif
  NODE *result;
  if (architecture) {
    result = from_c_string(architecture);
  } else {
    result = undefined;
  }
  {
    NODE *result__node = (NODE *)(result);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__3_1_std__c_compiler(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  const char *compiler =
  #if defined(CC_gcc)
    "gcc";
  #elif defined(CC_clang)
    "clang";
  #elif defined(CC_c99)
    "c99";
  #elif defined(CC_cc)
    "cc";
  #else
    NULL;
  #endif
  NODE *result;
  if (compiler) {
    result = from_c_string(compiler);
  } else {
    result = undefined;
  }
  {
    NODE *result__node = (NODE *)(result);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__4_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: -> '\'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__92;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: -> '/'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__47;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_1_std__current_directory_separator(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 114: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__4_2;
}
static void cont__4_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 114: operating_system() == "win"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = string__4_3;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__4_4;
}
static void cont__4_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 113: if
  // 114:   operating_system() == "win"
  // 115:   -> '\'
  // 116:   -> '/'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__4_5;
  arguments->slots[2] = func__4_6;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__5_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: -> ';'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__59;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 122: -> ':'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_1_std__current_path_separator(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 120: operating_system() == "win"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = string__4_3;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__5_3;
}
static void cont__5_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 119: if
  // 120:   operating_system() == "win"
  // 121:   -> ';'
  // 122:   -> ':'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__5_4;
  arguments->slots[2] = func__5_5;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__platform(void) {
  var.std__operating_system = collect_node(var.std__operating_system);
  var.std__hardware_architecture = collect_node(var.std__hardware_architecture);
  var.std__c_compiler = collect_node(var.std__c_compiler);
  var.std__current_directory_separator = collect_node(var.std__current_directory_separator);
  var.std__current_path_separator = collect_node(var.std__current_path_separator);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__platform(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__platform(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__92 = from_uchar32(92);
  character__47 = from_uchar32(47);
  character__58 = from_uchar32(58);
  character__59 = from_uchar32(59);
  func__1_1_std__operating_system = create_function(entry__1_1_std__operating_system, -1);
  func__2_1_std__hardware_architecture = create_function(entry__2_1_std__hardware_architecture, 0);
  func__3_1_std__c_compiler = create_function(entry__3_1_std__c_compiler, 0);
  string__4_3 = from_latin_1_string("win", 3);
  func__4_5 = create_function(entry__4_5, 0);
  func__4_6 = create_function(entry__4_6, 0);
  func__4_1_std__current_directory_separator = create_function(entry__4_1_std__current_directory_separator, 0);
  func__5_4 = create_function(entry__5_4, 0);
  func__5_5 = create_function(entry__5_5, 0);
  func__5_1_std__current_path_separator = create_function(entry__5_1_std__current_path_separator, 0);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__platform(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__platform");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "operating_system", get__std__operating_system, &var.std__operating_system);
  define_single_assign_static("std", "hardware_architecture", get__std__hardware_architecture, &var.std__hardware_architecture);
  define_single_assign_static("std", "c_compiler", get__std__c_compiler, &var.std__c_compiler);
  define_single_assign_static("std", "current_directory_separator", get__std__current_directory_separator, &var.std__current_directory_separator);
  define_single_assign_static("std", "current_path_separator", get__std__current_path_separator, &var.std__current_path_separator);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__platform(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__platform");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "operating_system", &get__operating_system, &get_value_or_future__operating_system);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__platform(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__operating_system, &func__1_1_std__operating_system);
  assign_variable(&var.std__hardware_architecture, &func__2_1_std__hardware_architecture);
  assign_variable(&var.std__c_compiler, &func__3_1_std__c_compiler);
  assign_variable(&var.std__current_directory_separator, &func__4_1_std__current_directory_separator);
  assign_variable(&var.std__current_path_separator, &func__5_1_std__current_path_separator);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__platform(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__platform);
}
