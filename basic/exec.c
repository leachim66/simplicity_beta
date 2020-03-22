#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
IMPORT void *allocate_memory(size_t size);
REGISTER FRAME *arguments ASM("r12");
IMPORT void deallocate_memory(void *buf);
IMPORT int result_count;
IMPORT void resource_error(void);
IMPORT NODE *from_int(int val);
IMPORT void *node_p;
IMPORT NODE *undefined;
IMPORT void allocate_arguments(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *from_arguments(int first_idx, int count);
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *empty_string;
IMPORT void *reallocate_memory(void * buf, size_t size);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT void optional_item(NODE *item);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
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
IMPORT void assign_value(NODE **dest, NODE *val);
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
#define IS_OLD(addr) false
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
static NODE_GETTER get__TRIM;
static NODE_GETTER get_value_or_future__TRIM;
static NODE_GETTER get__call;
static NODE_GETTER get_value_or_future__call;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__create_file_descriptor;
static NODE_GETTER get_value_or_future__create_file_descriptor;
static NODE_GETTER get__extract_options;
static NODE_GETTER get_value_or_future__extract_options;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static NODE_GETTER get__raise;
static NODE_GETTER get_value_or_future__raise;
static NODE_GETTER get__std__false;
static NODE_GETTER get_value_or_future__std__false;
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__std__true;
static NODE_GETTER get_value_or_future__std__true;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static NODE_GETTER get__trim;
static NODE_GETTER get_value_or_future__trim;
static NODE_GETTER get__update_each;
static NODE_GETTER get_value_or_future__update_each;
static struct {
  NODE *_posix_exec;
  NODE *_posix_launch;
  NODE *_posix_call;
  NODE *_posix_pipe;
  NODE *std__SIGHUP;
  NODE *std__SIGINT;
  NODE *std__SIGQUIT;
  NODE *std__SIGABRT;
  NODE *std__SIGKILL;
  NODE *std__SIGUSR1;
  NODE *std__SIGUSR2;
  NODE *std__SIGALRM;
  NODE *std__SIGTERM;
  NODE *std__launch;
  NODE *std__kill;
  NODE *std__exec;
  NODE *std__call;
  NODE *std__pipe;
  NODE *std__extern;
} var;
static const char *var_names[] = {
  "posix_exec",
  "posix_launch",
  "posix_call",
  "posix_pipe"
};
static NODE *get__std__SIGHUP(void) {
  return var.std__SIGHUP;
}
static NODE *get__std__SIGINT(void) {
  return var.std__SIGINT;
}
static NODE *get__std__SIGQUIT(void) {
  return var.std__SIGQUIT;
}
static NODE *get__std__SIGABRT(void) {
  return var.std__SIGABRT;
}
static NODE *get__std__SIGKILL(void) {
  return var.std__SIGKILL;
}
static NODE *get__std__SIGUSR1(void) {
  return var.std__SIGUSR1;
}
static NODE *get__std__SIGUSR2(void) {
  return var.std__SIGUSR2;
}
static NODE *get__std__SIGALRM(void) {
  return var.std__SIGALRM;
}
static NODE *get__std__SIGTERM(void) {
  return var.std__SIGTERM;
}

static void close_fd(int *fd_p);
static void entry__11_1(void);
static NODE *func__11_1;
static void entry__12_1(void);
static NODE *func__12_1;
static NODE *func__13_1;
static void entry__13_1(void);
static FRAME_INFO frame__13_1 = {2, {"args", "return"}};
static void cont__13_2(void);
static NODE *func__13_3;
static void entry__13_3(void);
static FRAME_INFO frame__13_3 = {1, {"args"}};
static NODE *func__13_4;
static void entry__13_4(void);
static FRAME_INFO frame__13_4 = {2, {"return", "args"}};
static void cont__13_5(void);
static NODE *func__13_6;
static void entry__13_6(void);
static FRAME_INFO frame__13_6 = {4, {"args", "return", "pid", "out"}};
static void cont__13_7(void);
static void cont__13_8(void);
static NODE *func__13_9;
static void entry__13_9(void);
static FRAME_INFO frame__13_9 = {5, {"args", "return", "pid", "out", "in"}};
static void cont__13_10(void);
static void cont__13_11(void);
static void cont__13_12(void);
static NODE *func__13_13;
static void entry__13_13(void);
static FRAME_INFO frame__13_13 = {6, {"args", "return", "pid", "out", "in", "err"}};
static void cont__13_14(void);
static void cont__13_15(void);
static void cont__13_16(void);
static void cont__13_17(void);
static void cont__13_18(void);
static NODE *get__std__launch(void) {
  return var.std__launch;
}
static void entry__14_1(void);
static NODE *func__14_1;
static void entry__15_1(void);
static NODE *func__15_1;
static NODE *get__std__kill(void) {
  return var.std__kill;
}
static void entry__16_1(void);
static NODE *func__16_1;
static NODE *func__17_1;
static void entry__17_1(void);
static FRAME_INFO frame__17_1 = {1, {"args"}};
static void cont__17_2(void);
static NODE *get__std__exec(void) {
  return var.std__exec;
}
static NODE *func__18_1;
static void entry__18_1(void);
static FRAME_INFO frame__18_1 = {1, {"args"}};
static void cont__18_2(void);
static NODE *get__std__call(void) {
  return var.std__call;
}
static NODE *func__19_1;
static void entry__19_1(void);
static FRAME_INFO frame__19_1 = {2, {"input", "cmds"}};
static void cont__19_2(void);
static NODE *func__19_3;
static void entry__19_3(void);
static FRAME_INFO frame__19_3 = {1, {"input"}};
static void cont__19_4(void);
static void cont__19_5(void);
static void cont__19_6(void);
static NODE *func__19_7;
static void entry__19_7(void);
static FRAME_INFO frame__19_7 = {0, {}};
static NODE *string__19_8;
static void cont__19_9(void);
static NODE *func__19_10;
static void entry__19_10(void);
static FRAME_INFO frame__19_10 = {1, {"cmd"}};
static void cont__19_11(void);
static void cont__19_12(void);
static NODE *get__std__pipe(void) {
  return var.std__pipe;
}
static NODE *func__20_1;
static void entry__20_1(void);
static FRAME_INFO frame__20_1 = {3, {"options", "filename", "do_trim"}};
static void cont__20_2(void);
static void cont__20_3(void);
static NODE *func__20_4;
static void entry__20_4(void);
static FRAME_INFO frame__20_4 = {1, {"filename"}};
static NODE *func__20_5;
static void entry__20_5(void);
static FRAME_INFO frame__20_5 = {3, {"args", "filename", "result"}};
static void cont__20_6(void);
static void cont__20_7(void);
static NODE *func__20_8;
static void entry__20_8(void);
static FRAME_INFO frame__20_8 = {1, {"result"}};
static void cont__20_9(void);
static NODE *func__20_10;
static void entry__20_10(void);
static FRAME_INFO frame__20_10 = {1, {"result"}};
static NODE *func__20_11;
static void entry__20_11(void);
static FRAME_INFO frame__20_11 = {1, {"filename"}};
static NODE *func__20_12;
static void entry__20_12(void);
static FRAME_INFO frame__20_12 = {2, {"args", "filename"}};
static NODE *get__std__extern(void) {
  return var.std__extern;
}
void run__basic__exec(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__exec, NULL, },
  {entry__11_1, NULL, 55, 81, 3, 2},
  {entry__12_1, NULL, 84, 200, 3, 2},
  {entry__13_3, NULL, 210, 210, 7, 24},
  {entry__13_4, NULL, 212, 212, 14, 32},
  {cont__13_5, &frame__13_4, 212, 212, 7, 32},
  {entry__13_6, NULL, 214, 214, 7, 34},
  {cont__13_7, &frame__13_6, 215, 215, 18, 44},
  {cont__13_8, &frame__13_6, 215, 215, 7, 44},
  {entry__13_9, NULL, 217, 217, 7, 38},
  {cont__13_10, &frame__13_9, 218, 218, 18, 44},
  {cont__13_11, &frame__13_9, 218, 218, 46, 71},
  {cont__13_12, &frame__13_9, 218, 218, 7, 71},
  {entry__13_13, NULL, 220, 220, 7, 43},
  {cont__13_14, &frame__13_13, 223, 223, 9, 35},
  {cont__13_15, &frame__13_13, 224, 224, 9, 34},
  {cont__13_16, &frame__13_13, 225, 225, 9, 35},
  {cont__13_17, &frame__13_13, 221, 225, 7, 35},
  {entry__13_1, NULL, 208, 208, 5, 30},
  {cont__13_2, &frame__13_1, 207, 225, 3, 37},
  {cont__13_18, &frame__13_1, 225, 225, 37, 37},
  {entry__14_1, NULL, 228, 430, 3, 2},
  {entry__15_1, NULL, 433, 438, 3, 2},
  {entry__16_1, NULL, 441, 767, 3, 2},
  {entry__17_1, NULL, 770, 770, 3, 29},
  {cont__17_2, &frame__17_1, 771, 771, 3, 18},
  {entry__18_1, NULL, 774, 774, 3, 29},
  {cont__18_2, &frame__18_1, 775, 775, 3, 18},
  {entry__19_3, NULL, 778, 778, 24, 39},
  {cont__19_4, &frame__19_3, 778, 778, 39, 39},
  {entry__19_7, NULL, 779, 779, 21, 46},
  {entry__19_10, NULL, 780, 780, 29, 37},
  {cont__19_11, &frame__19_10, 780, 780, 37, 37},
  {entry__19_1, NULL, 778, 778, 6, 21},
  {cont__19_2, &frame__19_1, 778, 778, 3, 39},
  {cont__19_5, &frame__19_1, 779, 779, 6, 18},
  {cont__19_6, &frame__19_1, 779, 779, 3, 46},
  {cont__19_9, &frame__19_1, 780, 780, 3, 37},
  {cont__19_12, &frame__19_1, 781, 781, 3, 24},
  {entry__20_8, NULL, 789, 789, 32, 42},
  {cont__20_9, &frame__20_8, 789, 789, 29, 42},
  {entry__20_10, NULL, 789, 789, 45, 53},
  {entry__20_5, NULL, 788, 788, 7, 33},
  {cont__20_6, &frame__20_5, 789, 789, 10, 26},
  {cont__20_7, &frame__20_5, 789, 789, 7, 53},
  {entry__20_4, NULL, 787, 789, 5, 53},
  {entry__20_12, NULL, 790, 790, 18, 36},
  {entry__20_11, NULL, 790, 790, 5, 36},
  {entry__20_1, NULL, 784, 784, 27, 38},
  {cont__20_2, &frame__20_1, 784, 784, 3, 47},
  {cont__20_3, &frame__20_1, 785, 790, 3, 36}
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
static NODE *number__6;
static NODE *number__15;
static NODE *number__12;
static NODE *number__0;
static NODE *number__3;
static NODE *number__4;
static NODE *number__9;
static NODE *number__1;
static NODE *number__2;
static NODE *number__10;
static NODE *number__14;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__exec",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/exec.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__exec(void) {
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

static void close_fd(int *fd_p) {
  if (*fd_p >= 0) {
    close(*fd_p);
    *fd_p = -1;
  }
}
static void entry__11_1(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  int i;
  sigset_t set;
  int ret = sigpending(&set);
  if (ret != -1) {
    // cancel all pending signals
    for (i = 1; i <= 31; ++i) {
      if (sigismember(&set, i)) {
        signal(i, SIG_IGN);
      }
    }
  }
  char **args = allocate_memory((argument_count+1)*sizeof(char *));
  // convert all arguments into C-strings
  for (i = 0; i < argument_count; ++i) {
    args[i] = to_c_string(arguments->slots[i]);
  }
  args[argument_count] = NULL;
  int err = execvp(args[0], args); // This call should not return!
  // on failure: free all allocated buffers
  for (i = 0; i < argument_count; ++i) {
    deallocate_memory(args[i]);
  }
  deallocate_memory(args);
  {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__12_1(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  int res_cnt = result_count;
  if (res_cnt < 0) res_cnt = 0;
  if (res_cnt > 4) res_cnt = 4;
  int do_redirect_stdout = (res_cnt >= 2);
  int do_redirect_stdin = (res_cnt >= 3);
  int do_redirect_stderr = (res_cnt >= 4);

  // initialize all pipe handles to invalid file descriptors
  struct {
    int read_fd;
    int write_fd;
  } out_pipe = {-1, -1}, in_pipe = {-1, -1}, err_pipe = {-1, -1};

  if (do_redirect_stdout) {
    if (pipe((int *)&out_pipe) != 0) {
    resource_error();
  }
  }
  if (do_redirect_stdin) {
    if (pipe((int *)&in_pipe) != 0) {
    resource_error();
  }
  }
  if (do_redirect_stderr) {
    if (pipe((int *)&err_pipe) != 0) {
    resource_error();
  }
  }

  int pid = fork();
  if (pid == 0) { // child process
    if (do_redirect_stdout) {
      //close(out_pipe.read_fd);
      dup2(out_pipe.write_fd, STDOUT_FILENO);
      //close(out_pipe.write_fd);
    }
    if (do_redirect_stdin) {
      //close(in_pipe.write_fd);
      dup2(in_pipe.read_fd, STDIN_FILENO);
      //close(in_pipe.read_fd);
    }
    if (do_redirect_stderr) {
      //close(err_pipe.read_fd);
      dup2(err_pipe.write_fd, STDERR_FILENO);
      //close(err_pipe.write_fd);
    }
    char buf[32];
    sprintf(buf, "/proc/%d/fd", getpid());
    struct dirent *dp;
    DIR *dir = opendir(buf);
    int dfd = dirfd(dir);
    while ((dp = readdir(dir)) != NULL) {
      if (dp->d_name[0] != '.') {
        int fd = atoi(dp->d_name);
        if (fd >= 3 && fd != dfd && fd < 1024) {
          // valgrind uses file descriptors 1024 and above,
          // so we just ignore them
          close(fd);
        }
      }
    }
    closedir(dir);
    char **args = allocate_memory((argument_count+1)*sizeof(char *));
    // convert all arguments into C-strings
    int i;
    for (i = 0; i < argument_count; ++i) {
      args[i] = to_c_string(arguments->slots[i]);
    }
    args[argument_count] = NULL;
    execvp(args[0], args);
    exit(EXIT_FAILURE);
  }

  // parent process

  if (pid == -1) goto cleanup_and_return; // fork failed

  NODE *out_fd, *in_fd, *err_fd;

  if (do_redirect_stdout) {
    close_fd(&out_pipe.write_fd);
    out_fd = from_int(out_pipe.read_fd);
  }

  if (do_redirect_stdin) {
    close_fd(&in_pipe.read_fd);
    in_fd = from_int(in_pipe.write_fd);
  }

  if (do_redirect_stderr) {
    close_fd(&err_pipe.write_fd);
    err_fd = from_int(err_pipe.read_fd);
  }

  argument_count = res_cnt;
  arguments = node_p;
  switch (res_cnt) {
    case 4: arguments->slots[3] = err_fd;
    case 3: arguments->slots[2] = in_fd;
    case 2: arguments->slots[1] = out_fd;
    case 1: arguments->slots[0] = from_int(pid);
  }
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }

  cleanup_and_return:

  close_fd(&out_pipe.read_fd);
  close_fd(&out_pipe.write_fd);
  close_fd(&in_pipe.read_fd);
  close_fd(&in_pipe.write_fd);
  close_fd(&err_pipe.read_fd);
  close_fd(&err_pipe.write_fd);

  argument_count = res_cnt;
  arguments = node_p;
  switch (res_cnt) {
    case 4: arguments->slots[3] = undefined;
    case 3: arguments->slots[2] = undefined;
    case 2: arguments->slots[1] = undefined;
    case 1: arguments->slots[0] = undefined;
  }
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__13_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // args: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 208: parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__13_2;
}
static void cont__13_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 209: ... :
  // 210:   posix_launch args*
  frame->slots[3] /* temp__2 */ = create_closure(entry__13_3, 0);
  // 211: ... :
  // 212:   return posix_launch(args*)
  frame->slots[4] /* temp__3 */ = create_closure(entry__13_4, 0);
  // 213: ... :
  // 214:   posix_launch $pid $out args*
  // 215:   return pid create_file_descriptor(out)
  frame->slots[5] /* temp__4 */ = create_closure(entry__13_6, 0);
  // 216: ... :
  // 217:   posix_launch $pid $out $in args*
  // 218:   return pid create_file_descriptor(out) create_file_descriptor(in)
  frame->slots[6] /* temp__5 */ = create_closure(entry__13_9, 0);
  // 219: ... :
  // 220:   posix_launch $pid $out $in $err args*
  // 221:   return
  // 222:     pid
  // 223:     create_file_descriptor(out)
  // 224:     create_file_descriptor(in)
  // 225:     create_file_descriptor(err)
  frame->slots[7] /* temp__6 */ = create_closure(entry__13_13, 0);
  // 207: case
  // 208:   parameter_count_of(return)
  // 209:   0:
  // 210:     posix_launch args*
  // 211:   1:
  // 212:     return posix_launch(args*)
  // 213:   2:
  // 214:     posix_launch $pid $out args*
  // 215:     return pid create_file_descriptor(out)
  // 216:   3:
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  arguments->slots[3] = number__1;
  arguments->slots[4] = frame->slots[4] /* temp__3 */;
  arguments->slots[5] = number__2;
  arguments->slots[6] = frame->slots[5] /* temp__4 */;
  arguments->slots[7] = number__3;
  arguments->slots[8] = frame->slots[6] /* temp__5 */;
  arguments->slots[9] = number__4;
  arguments->slots[10] = frame->slots[7] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__13_18;
}
static void entry__13_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 210: posix_launch args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._posix_launch;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // args: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: ... posix_launch(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* args */);
  result_count = 1;
  myself = var._posix_launch;
  func = myself->type;
  frame->cont = cont__13_5;
}
static void cont__13_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 212: return posix_launch(args*)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_6(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // args: 0
  // return: 1
  // pid: 2
  // out: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* pid */ = create_future();
  frame->slots[3] /* out */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: posix_launch $pid $out args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 2;
  myself = var._posix_launch;
  func = myself->type;
  frame->cont = cont__13_7;
}
static void cont__13_7(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  frame->slots[5] /* temp__2 */ = arguments->slots[1];
  // 214: ... pid
  initialize_future(frame->slots[2] /* pid */, frame->slots[4] /* temp__1 */);
  // 214: ... out
  initialize_future(frame->slots[3] /* out */, frame->slots[5] /* temp__2 */);
  // 215: ... create_file_descriptor(out)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* out */;
  result_count = 1;
  myself = get__create_file_descriptor();
  func = myself->type;
  frame->cont = cont__13_8;
}
static void cont__13_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 215: return pid create_file_descriptor(out)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pid */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_9(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // args: 0
  // return: 1
  // pid: 2
  // out: 3
  // in: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* pid */ = create_future();
  frame->slots[3] /* out */ = create_future();
  frame->slots[4] /* in */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 217: posix_launch $pid $out $in args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 3;
  myself = var._posix_launch;
  func = myself->type;
  frame->cont = cont__13_10;
}
static void cont__13_10(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 217: ... pid
  initialize_future(frame->slots[2] /* pid */, frame->slots[5] /* temp__1 */);
  // 217: ... out
  initialize_future(frame->slots[3] /* out */, frame->slots[6] /* temp__2 */);
  // 217: ... in
  initialize_future(frame->slots[4] /* in */, frame->slots[7] /* temp__3 */);
  // 218: ... create_file_descriptor(out)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* out */;
  result_count = 1;
  myself = get__create_file_descriptor();
  func = myself->type;
  frame->cont = cont__13_11;
}
static void cont__13_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 218: ... create_file_descriptor(in)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* in */;
  result_count = 1;
  myself = get__create_file_descriptor();
  func = myself->type;
  frame->cont = cont__13_12;
}
static void cont__13_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 218: return pid create_file_descriptor(out) create_file_descriptor(in)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pid */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_13(void) {
  allocate_initialized_frame_gc(2, 10);
  // slot allocations:
  // args: 0
  // return: 1
  // pid: 2
  // out: 3
  // in: 4
  // err: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* pid */ = create_future();
  frame->slots[3] /* out */ = create_future();
  frame->slots[4] /* in */ = create_future();
  frame->slots[5] /* err */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: posix_launch $pid $out $in $err args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 4;
  myself = var._posix_launch;
  func = myself->type;
  frame->cont = cont__13_14;
}
static void cont__13_14(void) {
  if (argument_count != 4) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  frame->slots[8] /* temp__3 */ = arguments->slots[2];
  frame->slots[9] /* temp__4 */ = arguments->slots[3];
  // 220: ... pid
  initialize_future(frame->slots[2] /* pid */, frame->slots[6] /* temp__1 */);
  // 220: ... out
  initialize_future(frame->slots[3] /* out */, frame->slots[7] /* temp__2 */);
  // 220: ... in
  initialize_future(frame->slots[4] /* in */, frame->slots[8] /* temp__3 */);
  // 220: ... err
  initialize_future(frame->slots[5] /* err */, frame->slots[9] /* temp__4 */);
  // 223: create_file_descriptor(out)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* out */;
  result_count = 1;
  myself = get__create_file_descriptor();
  func = myself->type;
  frame->cont = cont__13_15;
}
static void cont__13_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 224: create_file_descriptor(in)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* in */;
  result_count = 1;
  myself = get__create_file_descriptor();
  func = myself->type;
  frame->cont = cont__13_16;
}
static void cont__13_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 225: create_file_descriptor(err)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* err */;
  result_count = 1;
  myself = get__create_file_descriptor();
  func = myself->type;
  frame->cont = cont__13_17;
}
static void cont__13_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 221: return
  // 222:   pid
  // 223:   create_file_descriptor(out)
  // 224:   create_file_descriptor(in)
  // 225:   create_file_descriptor(err)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pid */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  arguments->slots[3] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__13_18(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__14_1(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  int res_cnt = result_count;
  if (res_cnt < 0) res_cnt = 0;
  if (res_cnt > 3) res_cnt = 3;
  int do_redirect_stdout = (res_cnt >= 1);
  int do_redirect_stderr = (res_cnt >= 3);

  char *out_buf = NULL;
  char *err_buf = NULL;
  size_t out_len = 0;
  size_t err_len = 0;

  NODE *result = get__std__false();
  NODE *out_str = empty_string;
  NODE *err_str = empty_string;

  // initialize all pipe handles to invalid file descriptors
  struct {
    int read_fd;
    int write_fd;
  } out_pipe = {-1, -1}, err_pipe = {-1, -1};

  if (do_redirect_stdout) {
    if (pipe((int *)&out_pipe) != 0) {
    resource_error();
  }
  }
  if (do_redirect_stderr) {
    if (pipe((int *)&err_pipe) != 0) {
    resource_error();
  }
  }

  // check the arguments **before** the fork!!!
  // otherwise the child process could raise a Simplicity error message!

  char **args = allocate_memory((argument_count+1)*sizeof(char *));
  // convert all arguments into C-strings
  int i;
  for (i = 0; i < argument_count; ++i) {
    args[i] = to_c_string(arguments->slots[i]);
  }
  args[argument_count] = NULL;

  int pid = fork();
  if (pid == 0) { // child process
    if (do_redirect_stdout) {
      //close(out_pipe.read_fd);
      dup2(out_pipe.write_fd, STDOUT_FILENO);
      //close(out_pipe.write_fd);
    }
    if (do_redirect_stderr) {
      //close(err_pipe.read_fd);
      dup2(err_pipe.write_fd, STDERR_FILENO);
      //close(err_pipe.write_fd);
    }
    char buf[32];
    sprintf(buf, "/proc/%d/fd", getpid());
    struct dirent *dp;
    DIR *dir = opendir(buf);
    int dfd = dirfd(dir);
    while ((dp = readdir(dir)) != NULL) {
      if (dp->d_name[0] != '.') {
        int fd = atoi(dp->d_name);
        if (fd >= 3 && fd != dfd && fd < 1024) {
          // valgrind uses file descriptors 1024 and above,
          // so we just ignore them
          close(fd);
        }
      }
    }
    closedir(dir);
    execvp(args[0], args);
    exit(EXIT_FAILURE);
  }

  // parent process

  // free the arguments in the parent process
  for (i = 0; i < argument_count; ++i) {
    deallocate_memory(args[i]);
  }
  deallocate_memory(args);

  if (pid == -1) goto cleanup_and_return; // fork failed

  size_t out_buf_size;
  size_t err_buf_size;

  if (do_redirect_stdout) {
    close_fd(&out_pipe.write_fd); // MUST be closed before starting reading!!!
    out_buf_size = 4096;
    out_buf = allocate_memory(out_buf_size);
  }

  if (do_redirect_stderr) {
    close_fd(&err_pipe.write_fd); // MUST be closed before starting reading!!!
    err_buf_size = 4096;
    err_buf = allocate_memory(err_buf_size);
  }

  int do_read_from_stdout = do_redirect_stdout;
  int do_read_from_stderr = do_redirect_stderr;

  while (do_read_from_stdout || do_read_from_stderr) {
    int nfds;
    fd_set rfds;
    nfds = 0;
    FD_ZERO(&rfds);
    if (do_read_from_stdout) {
      if (out_pipe.read_fd > nfds) {
        nfds = out_pipe.read_fd;
      }
      FD_SET(out_pipe.read_fd, &rfds);
    }
    if (do_read_from_stderr) {
      if (err_pipe.read_fd > out_pipe.read_fd) {
        nfds = err_pipe.read_fd;
      }
      FD_SET(err_pipe.read_fd, &rfds);
    }
    ++nfds; // number of highest file descriptor + 1

    int ret;
    do {
      ret = select(nfds, &rfds, NULL, NULL, NULL);
    } while (ret < 0 && errno == EINTR);
    if (ret < 0) goto cleanup_and_return;

    if (do_read_from_stdout && FD_ISSET(out_pipe.read_fd, &rfds)) {
      ssize_t bytes_read;
      do {
        bytes_read = read(out_pipe.read_fd, out_buf+out_len, out_buf_size-out_len);
      } while (bytes_read < 0 && errno == EINTR);
      if (bytes_read < 0) goto cleanup_and_return;
      if (bytes_read > 0) {
        out_len += bytes_read;
        if (out_len > out_buf_size/2) {
          out_buf_size *= 2;
          out_buf = reallocate_memory(out_buf, out_buf_size);
        }
      } else {
        do_read_from_stdout = false;
        close_fd(&out_pipe.read_fd);
      }
    }

    if (do_read_from_stderr && FD_ISSET(err_pipe.read_fd, &rfds)) {
      ssize_t bytes_read;
      do {
        bytes_read = read(err_pipe.read_fd, err_buf+err_len, err_buf_size-err_len);
      } while (bytes_read < 0 && errno == EINTR);
      if (bytes_read < 0) goto cleanup_and_return;
      err_len += bytes_read;
      if (bytes_read > 0) {
        if (err_len > err_buf_size/2) {
          err_buf_size *= 2;
          err_buf = reallocate_memory(err_buf, err_buf_size);
        }
      } else {
        do_read_from_stderr = false;
        close_fd(&err_pipe.read_fd);
      }
    }
  }

  if (do_redirect_stdout) {
    out_str = from_latin_1_string(out_buf, out_len);
  }

  if (do_redirect_stderr) {
    err_str = from_latin_1_string(err_buf, err_len);
  }

  int status;
  retry:;
  int ret = waitpid(pid, &status, 0);
  if (ret == -1 && errno == EINTR) goto retry;

  // it's essential to check whether the program exited normally!
  int successful = (WIFEXITED(status) && WEXITSTATUS(status) == 0);
  if (successful) result = get__std__true();

  cleanup_and_return:

  deallocate_memory(out_buf);
  deallocate_memory(err_buf);
  close_fd(&out_pipe.read_fd);
  close_fd(&out_pipe.write_fd);
  close_fd(&err_pipe.read_fd);
  close_fd(&err_pipe.write_fd);

  argument_count = res_cnt;
  arguments = node_p;
  switch (res_cnt) {
    case 3: arguments->slots[1] = err_str;
    case 2: arguments->slots[res_cnt-1] = result;
    case 1:
      if (successful || res_cnt > 1) {
        arguments->slots[0] = out_str;
      } else {
        // do not silently ignore an error!
        arguments->slots[0] = undefined;
      }
  }
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__15_1(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  kill(to_int(arguments->slots[0]), argument_count == 2 ? to_int(arguments->slots[1]) : SIGKILL);
  {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__16_1(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  int res_cnt = result_count;
  if (res_cnt < 0) res_cnt = 0;
  if (res_cnt > 3) res_cnt = 3;
  int do_redirect_stdin = (argument_count == 2);
  int do_redirect_stdout = (res_cnt >= 1);
  int do_redirect_stderr = (res_cnt >= 3);

  uint8_t *input = NULL;
  char *out_buf = NULL;
  char **err_buf_tab = NULL;
  size_t out_len = 0;
  size_t *err_len_tab = NULL;

  NODE *result = get__std__false();
  NODE *out_str = empty_string;
  NODE *err_str = empty_string;

  int i;

  NODE *cmds = arguments->slots[0];
  int cmd_cnt = length_of(cmds);

  int *pids;
  struct {
    int read_fd;
    int write_fd;
  } *out_pipes, *err_pipes;

  pids = allocate_memory(cmd_cnt*sizeof(int));
  for (i = 0; i < cmd_cnt; ++i) {
    pids[i] = -1;
  }
  out_pipes = allocate_memory((cmd_cnt+1)*sizeof(*out_pipes));
  if (do_redirect_stdin) {
    if (pipe((int *)&out_pipes[0]) != 0) {
    resource_error();
  }
  } else {
    out_pipes[0].read_fd = -1;
    out_pipes[0].write_fd = -1;
  }
  for (i = 1; i < cmd_cnt; ++i) {
    if (pipe((int *)&out_pipes[i]) != 0) {
    resource_error();
  }
  }
  if (do_redirect_stdout) {
    if (pipe((int *)&out_pipes[cmd_cnt]) != 0) {
    resource_error();
  }
  } else {
    out_pipes[cmd_cnt].read_fd = -1;
    out_pipes[cmd_cnt].write_fd = -1;
  }

  err_pipes = allocate_memory(cmd_cnt*sizeof(*err_pipes));
  if (do_redirect_stderr) {
    for (i = 0; i < cmd_cnt; ++i) {
      if (pipe((int *)&err_pipes[i]) != 0) {
    resource_error();
  }
    }
  } else {
    for (i = 0; i < cmd_cnt; ++i) {
      err_pipes[i].read_fd = -1;
      err_pipes[i].write_fd = -1;
    }
  }

  int pid;
  int cmd_idx = 0;
  do {
    pid = fork();
    if (pid == 0) { // child process
      // duplicate all needed handles
      if (do_redirect_stdin || cmd_idx != 0) {
        dup2(out_pipes[cmd_idx].read_fd, STDIN_FILENO);
      }
      if (do_redirect_stdout || cmd_idx != cmd_cnt-1) {
        dup2(out_pipes[cmd_idx+1].write_fd, STDOUT_FILENO);
      }
      if (do_redirect_stderr) {
        dup2(err_pipes[cmd_idx].write_fd, STDERR_FILENO);
      }

      // close all handles created for the parent process or sibling processes
      /*for (i = 0; i < cmd_cnt; ++i) {
        close(out_pipes[i].read_fd);
        close(out_pipes[i].write_fd);
      }
      if (do_redirect_stdout) {
        close(out_pipes[cmd_cnt].read_fd);
        close(out_pipes[cmd_cnt].write_fd);
      }
      if (do_redirect_stderr) {
        for (i = 0; i < cmd_cnt; ++i) {
          close(err_pipes[i].read_fd);
          close(err_pipes[i].write_fd);
        }
      }*/
      char buf[32];
      sprintf(buf, "/proc/%d/fd", getpid());
      struct dirent *dp;
      DIR *dir = opendir(buf);
      int dfd = dirfd(dir);
      while ((dp = readdir(dir)) != NULL) {
        if (dp->d_name[0] != '.') {
          int fd = atoi(dp->d_name);
          if (fd >= 3 && fd != dfd && fd < 1024) {
            // valgrind uses file descriptors 1024 and above,
            // so we just ignore them
            close(fd);
          }
        }
      }
      closedir(dir);

      NODE *cmd = get_item_of(cmds, cmd_idx);
      long len = length_of(cmd);
      char **args = allocate_memory((len+1)*sizeof(char *));
      // convert all arguments into C-strings
      for (i = 0; i < len; ++i) {
        args[i] = to_c_string(get_item_of(cmd, i));
      }
      args[len] = NULL;
      execvp(args[0], args);
      exit(EXIT_FAILURE);
    }
    pids[cmd_idx++] = pid;
  } while (pid > 0 && cmd_idx < cmd_cnt);

  if (pid < 0) goto cleanup_and_return;

  long input_size, s;
  size_t out_buf_size;
  size_t *err_buf_size_tab;

  // close all handles created for the child processes

  if (do_redirect_stdin) {
    close_fd(&out_pipes[0].read_fd);
    input = to_octets(arguments->slots[1], &input_size);
    s = 0;
  }
  for (i = 1; i < cmd_cnt; ++i) {
    close_fd(&out_pipes[i].read_fd);
    close_fd(&out_pipes[i].write_fd);
  }

  if (do_redirect_stdout) {
    close_fd(&out_pipes[cmd_cnt].write_fd);
    out_buf_size = 4096;
    out_buf = allocate_memory(out_buf_size);
  }

  if (do_redirect_stderr) {
    for (i = 0; i < cmd_cnt; ++i) {
      close_fd(&err_pipes[i].write_fd);
    }
    err_buf_tab = allocate_memory(cmd_cnt*sizeof(char *));
    err_buf_size_tab = allocate_memory(cmd_cnt*sizeof(size_t));
    err_len_tab = allocate_memory(cmd_cnt*sizeof(size_t));
    for (i = 0; i < cmd_cnt; ++i) {
      err_buf_tab[i] = allocate_memory(4096);
      err_buf_size_tab[i] = 4096;
      err_len_tab[i] = 0;
    }
  }

  int do_write_to_stdin = do_redirect_stdin;
  int do_read_from_stdout = do_redirect_stdout;
  int do_read_from_stderr = do_redirect_stderr ? cmd_cnt : 0;

  int out_pipe_read_fd = out_pipes[cmd_cnt].read_fd;
  int in_pipe_write_fd = out_pipes[0].write_fd;

  while (do_write_to_stdin || do_read_from_stdout || do_read_from_stderr) {
    int nfds;
    fd_set rfds;
    fd_set wfds;
    nfds = 0;
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    if (do_write_to_stdin) {
      if (in_pipe_write_fd > nfds) {
        nfds = in_pipe_write_fd;
      }
      FD_SET(in_pipe_write_fd, &wfds);
    }
    if (do_read_from_stdout) {
      if (out_pipe_read_fd > nfds) {
        nfds = out_pipe_read_fd;
      }
      FD_SET(out_pipe_read_fd, &rfds);
    }
    if (do_read_from_stderr) {
      for (i = 0; i < cmd_cnt; ++i) {
        if (err_pipes[i].read_fd >= 0) {
          if (err_pipes[i].read_fd > nfds) nfds = err_pipes[i].read_fd;
          FD_SET(err_pipes[i].read_fd, &rfds);
        }
      }
    }
    ++nfds; // number of highest file descriptor + 1

    int ret;
    do {
      ret = select(nfds, &rfds, &wfds, NULL, NULL);
    } while (ret < 0 && errno == EINTR);
    if (ret < 0) goto cleanup_and_return;

    if (do_write_to_stdin && FD_ISSET(in_pipe_write_fd, &wfds)) {
      ssize_t bytes_written;
      do {
        bytes_written = write(in_pipe_write_fd, input+s, input_size-s);
      } while (bytes_written < 0 && errno == EINTR);
      if (bytes_written < 0) goto cleanup_and_return;
      if (bytes_written > 0) {
        s += bytes_written;
      } else {
        do_write_to_stdin = false;
        close_fd(&out_pipes[0].write_fd);
      }
    }

    if (do_read_from_stdout && FD_ISSET(out_pipe_read_fd, &rfds)) {
      ssize_t bytes_read;
      do {
        bytes_read = read(out_pipe_read_fd, out_buf+out_len, out_buf_size-out_len);
      } while (bytes_read < 0 && errno == EINTR);
      if (bytes_read < 0) goto cleanup_and_return;
      if (bytes_read > 0) {
        out_len += bytes_read;
        if (out_len > out_buf_size/2) {
          out_buf_size *= 2;
          out_buf = reallocate_memory(out_buf, out_buf_size);
        }
      } else {
        do_read_from_stdout = false;
        close_fd(&out_pipe_read_fd);
      }
    }

    if (do_read_from_stderr) {
      for (i = 0; i < cmd_cnt; ++i) {
        if (err_pipes[i].read_fd >= 0 && FD_ISSET(err_pipes[i].read_fd, &rfds)) {
          ssize_t bytes_read;
          do {
            bytes_read =
              read(
                err_pipes[i].read_fd,
                err_buf_tab[i]+err_len_tab[i],
                err_buf_size_tab[i]-err_len_tab[i]);
          } while (bytes_read < 0 && errno == EINTR);
          if (bytes_read < 0) goto cleanup_and_return;
          err_len_tab[i] += bytes_read;
          if (bytes_read > 0) {
            if (err_len_tab[i] > err_buf_size_tab[i]/2) {
              err_buf_size_tab[i] *= 2;
              err_buf_tab[i] =
                reallocate_memory(err_buf_tab[i], err_buf_size_tab[i]);
            }
          } else {
            --do_read_from_stderr;
            close_fd(&err_pipes[i].read_fd);
          }
        }
      }
    }
  }

  int success = true;
  int status;

  for (i = 0; i < cmd_cnt; ++i) {
    retry:;
    int ret = waitpid(pids[i], &status, 0);
    if (ret == -1 && errno == EINTR) goto retry;
    if (ret < 0 || WEXITSTATUS(status) != 0) success = false;
  }

  if (success) result = get__std__true();

  if (do_redirect_stdout) {
    out_str = from_latin_1_string(out_buf, out_len);
  }

  if (do_redirect_stderr) {
    int err_len = 0;
    for (i = 0; i < cmd_cnt; ++i) {
      err_len += err_len_tab[i];
    }
    char *err_buf = allocate_memory(err_len);
    err_len = 0;
    for (i = 0; i < cmd_cnt; ++i) {
      memcpy(err_buf+err_len, err_buf_tab[i], err_len_tab[i]);
      err_len += err_len_tab[i];
    }
    err_str = from_latin_1_string(err_buf, err_len);
    deallocate_memory(err_buf);
  }

  cleanup_and_return:

  deallocate_memory(input);
  deallocate_memory(out_buf);
  if (err_buf_tab) {
    for (i = 0; i < cmd_cnt; ++i) {
      deallocate_memory(err_buf_tab[i]);
    }
    deallocate_memory(err_buf_tab);
    deallocate_memory(err_buf_size_tab);
    deallocate_memory(err_len_tab);
  }
  for (i = 0; i <= cmd_cnt; ++i) {
    close_fd(&out_pipes[i].read_fd);
    close_fd(&out_pipes[i].write_fd);
  }
  for (i = 0; i < cmd_cnt; ++i) {
    close_fd(&err_pipes[i].read_fd);
    close_fd(&err_pipes[i].write_fd);
  }

  argument_count = res_cnt;
  arguments = node_p;
  switch (res_cnt) {
    case 3: arguments->slots[1] = err_str;
    case 2: arguments->slots[res_cnt-1] = result;
    case 1: arguments->slots[0] = out_str;
  }

  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__17_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = create_cell_with_contents(from_arguments(0, argument_count-0));
  // 770: update_each &args to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* args */;
  arguments->slots[1] = get__to_string();
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__17_2;
}
static void cont__17_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* args */ = arguments->slots[0];
  // 771: posix_exec args*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* args */);
  result_count = frame->caller_result_count;
  myself = var._posix_exec;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = create_cell_with_contents(from_arguments(0, argument_count-0));
  // 774: update_each &args to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* args */;
  arguments->slots[1] = get__to_string();
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__18_2;
}
static void cont__18_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* args */ = arguments->slots[0];
  // 775: posix_call args*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* args */);
  result_count = frame->caller_result_count;
  myself = var._posix_call;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // input: 0
  // cmds: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* input */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* cmds */ = create_cell_with_contents(from_arguments(1, argument_count-1));
  // 778: ... input.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* input */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__19_2;
}
static void cont__19_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 778: ... : to_string &input
  frame->slots[3] /* temp__2 */ = create_closure(entry__19_3, 0);
  // 778: if input.is_defined: to_string &input
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_5;
}
static void entry__19_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // input: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* input */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 778: ... to_string &input
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* input */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__19_4;
}
static void cont__19_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* input */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 779: ... cmds.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* cmds */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__19_6;
}
static void cont__19_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 779: if cmds.is_empty: raise "Invalid arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__19_7;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_9;
}
static void entry__19_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 779: ... raise "Invalid arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__19_8;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__19_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 780: update_each &cmds: (&cmd) cmd !cmd*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* cmds */;
  arguments->slots[1] = func__19_10;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__19_12;
}
static void entry__19_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // cmd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* cmd */ = create_cell_with_contents(arguments->slots[0]);
  // 780: ... cmd !cmd*
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = ((CELL *)frame->slots[0])->contents /* cmd */;
  func = myself->type;
  frame->cont = cont__19_11;
}
static void cont__19_11(void) {
  allocate_arguments();
  ((CELL *)frame->slots[0])->contents /* cmd */ = from_arguments(0, argument_count-0);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* cmd */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* cmds */ = arguments->slots[0];
  // 781: posix_pipe cmds input?
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = ((CELL *)frame->slots[1])->contents /* cmds */;
  optional_item(((CELL *)frame->slots[0])->contents /* input */);
  result_count = frame->caller_result_count;
  myself = var._posix_pipe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_12(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // args: 0
  // filename: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 790: ... call filename args*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[1] /* filename */;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = get__call();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // result: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 789: ... result.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__20_9;
}
static void cont__20_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 789: ... -> result.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // result: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 789: ... -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_5(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // args: 0
  // filename: 1
  // result: 2
  frame->slots[1] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[2] /* result */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 788: call $result filename args*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[1] /* filename */;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__call();
  func = myself->type;
  frame->cont = cont__20_6;
}
static void cont__20_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* result */, arguments->slots[0]);
  // 789: ... result.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* result */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__20_7;
}
static void cont__20_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 789: ... -> result.trim
  frame->slots[4] /* temp__2 */ = create_closure(entry__20_8, 0);
  // 789: ... -> result
  frame->slots[5] /* temp__3 */ = create_closure(entry__20_10, 0);
  // 789: if result.is_defined (-> result.trim) -> result
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 787: ... : (args*)
  // 788:   call $result filename args*
  // 789:   if result.is_defined (-> result.trim) -> result
  frame->slots[1] /* temp__1 */ = create_closure(entry__20_5, -1);
  // 787: -> : (args*)
  // 788:   call $result filename args*
  // 789:   if result.is_defined (-> result.trim) -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 790: ... : (args*) call filename args*
  frame->slots[1] /* temp__1 */ = create_closure(entry__20_12, -1);
  // 790: -> : (args*) call filename args*
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // options: 0
  // filename: 1
  // do_trim: 2
  frame->slots[2] /* do_trim */ = create_future();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[1] /* filename */ = arguments->slots[argument_count-1];
  frame->slots[0] /* options */ = from_arguments(0, argument_count-1);
  // 784: ... TRIM = false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__TRIM();
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 784: extract_options options TRIM = false $do_trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* options */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__extract_options();
  func = myself->type;
  frame->cont = cont__20_3;
}
static void cont__20_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_trim */, arguments->slots[0]);
  // 787: -> : (args*)
  // 788:   call $result filename args*
  // 789:   if result.is_defined (-> result.trim) -> result
  frame->slots[3] /* temp__1 */ = create_closure(entry__20_4, 0);
  // 790: -> : (args*) call filename args*
  frame->slots[4] /* temp__2 */ = create_closure(entry__20_11, 0);
  // 785: if
  // 786:   do_trim
  // 787:   -> : (args*)
  // 788:     call $result filename args*
  // 789:     if result.is_defined (-> result.trim) -> result
  // 790:   -> : (args*) call filename args*
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_trim */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__exec(void) {
  var.std__SIGHUP = collect_node(var.std__SIGHUP);
  var.std__SIGINT = collect_node(var.std__SIGINT);
  var.std__SIGQUIT = collect_node(var.std__SIGQUIT);
  var.std__SIGABRT = collect_node(var.std__SIGABRT);
  var.std__SIGKILL = collect_node(var.std__SIGKILL);
  var.std__SIGUSR1 = collect_node(var.std__SIGUSR1);
  var.std__SIGUSR2 = collect_node(var.std__SIGUSR2);
  var.std__SIGALRM = collect_node(var.std__SIGALRM);
  var.std__SIGTERM = collect_node(var.std__SIGTERM);
  var._posix_exec = collect_node(var._posix_exec);
  var._posix_launch = collect_node(var._posix_launch);
  var.std__launch = collect_node(var.std__launch);
  var._posix_call = collect_node(var._posix_call);
  var.std__kill = collect_node(var.std__kill);
  var._posix_pipe = collect_node(var._posix_pipe);
  var.std__exec = collect_node(var.std__exec);
  var.std__call = collect_node(var.std__call);
  var.std__pipe = collect_node(var.std__pipe);
  string__19_8 = collect_node(string__19_8);
  var.std__extern = collect_node(var.std__extern);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__exec(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__exec(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__6 = from_uint32(6U);
  number__15 = from_uint32(15U);
  number__12 = from_uint32(12U);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__4 = from_uint32(4U);
  number__9 = from_uint32(9U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  number__10 = from_uint32(10U);
  number__14 = from_uint32(14U);
  func__13_1 = create_function(entry__13_1, -1);
  func__17_1 = create_function(entry__17_1, -1);
  func__18_1 = create_function(entry__18_1, -1);
  func__19_7 = create_function(entry__19_7, 0);
  func__19_10 = create_function(entry__19_10, 1);
  func__19_1 = create_function(entry__19_1, -1);
  func__20_1 = create_function(entry__20_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__exec(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__exec");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "SIGHUP", get__std__SIGHUP, &var.std__SIGHUP);
  define_single_assign_static("std", "SIGINT", get__std__SIGINT, &var.std__SIGINT);
  define_single_assign_static("std", "SIGQUIT", get__std__SIGQUIT, &var.std__SIGQUIT);
  define_single_assign_static("std", "SIGABRT", get__std__SIGABRT, &var.std__SIGABRT);
  define_single_assign_static("std", "SIGKILL", get__std__SIGKILL, &var.std__SIGKILL);
  define_single_assign_static("std", "SIGUSR1", get__std__SIGUSR1, &var.std__SIGUSR1);
  define_single_assign_static("std", "SIGUSR2", get__std__SIGUSR2, &var.std__SIGUSR2);
  define_single_assign_static("std", "SIGALRM", get__std__SIGALRM, &var.std__SIGALRM);
  define_single_assign_static("std", "SIGTERM", get__std__SIGTERM, &var.std__SIGTERM);
  func__11_1 = create_future();
  func__12_1 = create_future();
  define_single_assign_static("std", "launch", get__std__launch, &var.std__launch);
  func__14_1 = create_future();
  func__15_1 = create_future();
  define_single_assign_static("std", "kill", get__std__kill, &var.std__kill);
  func__16_1 = create_future();
  define_single_assign_static("std", "exec", get__std__exec, &var.std__exec);
  define_single_assign_static("std", "call", get__std__call, &var.std__call);
  string__19_8 = from_latin_1_string("Invalid arguments!", 18);
  define_single_assign_static("std", "pipe", get__std__pipe, &var.std__pipe);
  define_single_assign_static("std", "extern", get__std__extern, &var.std__extern);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__exec(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__exec");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "TRIM", &get__TRIM, &get_value_or_future__TRIM);
  use_read_only(NULL, "call", &get__call, &get_value_or_future__call);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "create_file_descriptor", &get__create_file_descriptor, &get_value_or_future__create_file_descriptor);
  use_read_only(NULL, "extract_options", &get__extract_options, &get_value_or_future__extract_options);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_read_only(NULL, "raise", &get__raise, &get_value_or_future__raise);
  use_read_only("std", "false", &get__std__false, &get_value_or_future__std__false);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "true", &get__std__true, &get_value_or_future__std__true);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_read_only(NULL, "trim", &get__trim, &get_value_or_future__trim);
  use_read_only(NULL, "update_each", &get__update_each, &get_value_or_future__update_each);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__exec(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__SIGHUP, number__1);
  assign_value(&var.std__SIGINT, number__2);
  assign_value(&var.std__SIGQUIT, number__3);
  assign_value(&var.std__SIGABRT, number__6);
  assign_value(&var.std__SIGKILL, number__9);
  assign_value(&var.std__SIGUSR1, number__10);
  assign_value(&var.std__SIGUSR2, number__12);
  assign_value(&var.std__SIGALRM, number__14);
  assign_value(&var.std__SIGTERM, number__15);
  assign_variable(&var._posix_exec, &func__11_1);
  assign_variable(&var._posix_launch, &func__12_1);
  assign_variable(&var.std__launch, &func__13_1);
  assign_variable(&var._posix_call, &func__14_1);
  assign_variable(&var.std__kill, &func__15_1);
  assign_variable(&var._posix_pipe, &func__16_1);
  assign_variable(&var.std__exec, &func__17_1);
  assign_variable(&var.std__call, &func__18_1);
  assign_variable(&var.std__pipe, &func__19_1);
  assign_variable(&var.std__extern, &func__20_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__exec(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  assign_value(&func__11_1, create_function(entry__11_1, -1));
  assign_value(&func__12_1, create_function(entry__12_1, -1));
  assign_value(&func__14_1, create_function(entry__14_1, -1));
  assign_value(&func__15_1, create_function(entry__15_1, -1));
  assign_value(&func__16_1, create_function(entry__16_1, -1));
  register_collector(collect__basic__exec);
}
