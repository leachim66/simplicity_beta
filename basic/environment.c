#include <stdlib.h>
#include <runtime/platform.h>
#include <stdint.h>

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
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define REGISTER register
#else
  #define REGISTER IMPORT
#endif
typedef struct FRAME {
  FUNC cont;
  struct FRAME *caller_frame;
  long caller_result_count;
  long slot_count;
  NODE *slots[0];
} FRAME;
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define ASM(x) asm(x)
#else
  #define ASM(x)
#endif
REGISTER FRAME *arguments ASM("r12");
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
REGISTER NODE *myself ASM("r13");
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
REGISTER FUNC func ASM("r14");
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
REGISTER int argument_count ASM("ebx");
IMPORT void *node_p;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_future(void);
IMPORT int main_argc;
IMPORT void invalid_index_error(void);
IMPORT NODE *from_c_string(const char *str);
IMPORT char **main_argv;
IMPORT NODE *from_int(int val);
typedef enum {
  EM__NORMAL,
  EM__RECORD,
  EM__REPLAY
} EVENT__MODE;
IMPORT EVENT__MODE event__mode;
IMPORT void record__event(const char *name);
IMPORT void store__c_string(const char *buf);
IMPORT void replay__event(const char *name);
IMPORT void retrieve__c_string(char **buf_p);
IMPORT void store__integer(int val);
IMPORT void retrieve__integer(int *val_p);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void assign_value(NODE **dest, NODE *val);
typedef void (*NODE_SETTER)(NODE *);
IMPORT void define_multi_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void *update_start_p;
IMPORT void def_attribute(NODE **var_p, int idx, void *attr);
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
static NODE_GETTER get__before;
static NODE_GETTER get_value_or_future__before;
static NODE_GETTER get__behind;
static NODE_GETTER get_value_or_future__behind;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static NODE_GETTER get__from_to;
static NODE_GETTER get_value_or_future__from_to;
static NODE_GETTER get__from_utf8;
static NODE_GETTER get_value_or_future__from_utf8;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__private__get_item;
static NODE_GETTER get_value_or_future__private__get_item;
static NODE_GETTER get__private__set_item;
static NODE_GETTER get_value_or_future__private__set_item;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static struct {
  NODE *_argv;
  NODE *_argc;
  NODE *_envv;
  NODE *_envc;
  NODE *_arguments;
  NODE *_env_1;
  NODE *_putenv;
  NODE *_NONE;
  NODE *_env_2;
  NODE *std__program_name;
  NODE *std__command_line_arguments;
  NODE *std__environment;
} var;
static const char *var_names[] = {
  "argv",
  "argc",
  "envv",
  "envc",
  "arguments",
  "env_1",
  "putenv",
  "NONE",
  "env_2"
};
static void entry__1_1_argv(void);
static NODE *func__1_1_argv;
static void entry__2_1_argc(void);
static NODE *func__2_1_argc;

extern char **environ;
static int ENVC = 0;
static void entry__4_1_envv(void);
static NODE *func__4_1_envv;
static void entry__5_1_envc(void);
static NODE *func__5_1_envc;
static NODE *get__std__program_name(void) {
  return var.std__program_name;
}
static NODE *get__std__command_line_arguments(void) {
  return var.std__command_line_arguments;
}
static void entry__12_1_putenv(void);
static NODE *func__12_1_putenv;
static NODE *unique__NONE;
static NODE *func__15_1_env_2_;
static void entry__15_1_env_2_(void);
static FRAME_INFO frame__15_1_env_2_ = {3, {"key", "value", "myself"}};
static void cont__15_2(void);
static NODE *func__15_3;
static void entry__15_3(void);
static FRAME_INFO frame__15_3 = {2, {"myself", "key"}};
static NODE *func__15_4;
static void entry__15_4(void);
static FRAME_INFO frame__15_4 = {3, {"key", "value", "myself"}};
static NODE *string__15_5;
static void cont__15_6(void);
static void cont__15_7(void);
static NODE *get__std__environment(void) {
  return var.std__environment;
}
static void set__std__environment(NODE *val) {
  var.std__environment = val;
}
static void cont__22_1(void);
static void cont__24_1(void);
static void cont__24_2(void);
static NODE *func__24_3;
static void entry__24_3(void);
static FRAME_INFO frame__24_3 = {1, {"i"}};
static void cont__24_4(void);
static void cont__24_5(void);
static void cont__24_6(void);
static void cont__27_1(void);
static NODE *func__27_2;
static void entry__27_2(void);
static FRAME_INFO frame__27_2 = {2, {"i", "str"}};
static void cont__27_3(void);
static void cont__27_4(void);
static void cont__27_5(void);
static void cont__27_6(void);
static void cont__27_7(void);
static void cont__27_8(void);
void run__basic__environment(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__environment, NULL, 69, 69, 1, 26},
  {cont__22_1, NULL, 76, 76, 11, 16},
  {cont__24_1, NULL, 76, 76, 11, 18},
  {cont__24_2, NULL, 76, 76, 1, 47},
  {cont__24_6, NULL, 88, 88, 11, 16},
  {cont__27_1, NULL, 88, 90, 1, 43},
  {cont__27_8, NULL, 118, 118, 1, 24},
  {entry__1_1_argv, NULL, 26, 31, 3, 2},
  {entry__2_1_argc, NULL, 34, 37, 3, 2},
  {entry__4_1_envv, NULL, 45, 56, 3, 2},
  {entry__5_1_envc, NULL, 59, 67, 3, 2},
  {entry__12_1_putenv, NULL, 93, 97, 3, 2},
  {entry__15_3, NULL, 111, 111, 7, 34},
  {entry__15_4, NULL, 115, 115, 14, 30},
  {cont__15_6, &frame__15_4, 115, 115, 7, 30},
  {cont__15_7, &frame__15_4, 116, 116, 7, 40},
  {entry__15_1_env_2_, NULL, 110, 110, 5, 17},
  {cont__15_2, &frame__15_1_env_2_, 109, 116, 3, 41},
  {entry__24_3, NULL, 76, 76, 41, 47},
  {cont__24_4, &frame__24_3, 76, 76, 25, 47},
  {cont__24_5, &frame__24_3, 76, 76, 47, 47},
  {entry__27_2, NULL, 89, 89, 8, 14},
  {cont__27_3, &frame__27_2, 89, 89, 3, 24},
  {cont__27_4, &frame__27_2, 90, 90, 3, 43},
  {cont__27_5, &frame__27_2, 90, 90, 10, 25},
  {cont__27_6, &frame__27_2, 90, 90, 3, 26},
  {cont__27_7, &frame__27_2, 90, 90, 43, 43}
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
static NODE *number__0;
static NODE *character__61;
static NODE *number__1;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__environment",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/environment.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__environment(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 2);
  // 69: $std::program_name argv(0)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  result_count = 1;
  myself = var._argv;
  func = myself->type;
  frame->cont = cont__22_1;
}
static void cont__22_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.std__program_name, arguments->slots[0]);
  // 75: $$arguments empty_list
  var._arguments = get__empty_list();
  // 76: ... argc()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._argc;
  func = myself->type;
  frame->cont = cont__24_1;
}
static void cont__24_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 76: ... argc()-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 76: from_to 1 argc()-1: (i) push &arguments argv(i)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = func__24_3;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__24_6;
}
static void entry__24_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // i: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 76: ... argv(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = var._argv;
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 76: ... push &arguments argv(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._arguments;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void cont__24_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._arguments = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 78: $std::command_line_arguments arguments
  initialize_future(var.std__command_line_arguments, var._arguments);
  // 87: $$env_1 empty_table
  var._env_1 = get__empty_table();
  // 88: ... envc()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._envc;
  func = myself->type;
  frame->cont = cont__27_1;
}
static void cont__27_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 88: from_to 1 envc(): (i)
  // 89:   $str envv(i).from_utf8
  // 90:   !env_1(str .before. '=') str .behind. '='
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = func__27_2;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__27_8;
}
static void entry__27_2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // i: 0
  // str: 1
  frame->slots[1] /* str */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 89: ... envv(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = var._envv;
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: $str envv(i).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* str */, arguments->slots[0]);
  // 90: !env_1(str .before. '=') str .behind. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__27_5;
}
static void cont__27_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 90: ... str .before. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__27_6;
}
static void cont__27_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 90: !env_1(str .before. '=')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._env_1;
  func = myself->type;
  frame->cont = cont__27_7;
}
static void cont__27_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._env_1 = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__27_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 101: $env_2 env_1
  initialize_future(var._env_2, var._env_1);
  // 118: $$std::environment env_2
  var.std__environment = var._env_2;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__1_1_argv(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int idx = to_int(arguments->slots[0]);
  if (idx < 0 || idx >= main_argc) {
    invalid_index_error();
  }
  {
    NODE *result__node = (NODE *)(from_c_string(main_argv[idx]));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}
static void entry__2_1_argc(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_int(main_argc));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}
static void entry__4_1_envv(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char *entry;
  if (event__mode != EM__REPLAY) {
    int idx = to_int(arguments->slots[0]);
    if (idx < 1 || idx > ENVC) {
    invalid_index_error();
  }
    entry = environ[idx-1];
    if (event__mode == EM__RECORD) {
      record__event("envv");
      store__c_string(entry);
    }
  } else {
    replay__event("envv");
    retrieve__c_string(&entry);
  }
  {
    NODE *result__node = (NODE *)(from_c_string(entry));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__5_1_envc(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  if (event__mode != EM__REPLAY) {
    if (ENVC == 0) while (environ[ENVC]) ++ENVC;
    if (event__mode == EM__RECORD) {
      record__event("envc");
      store__integer(ENVC);
    }
  } else {
    replay__event("envc");
    retrieve__integer(&ENVC);
  }
  {
    NODE *result__node = (NODE *)(from_int(ENVC));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}
static void entry__12_1_putenv(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  putenv(to_c_string(arguments->slots[0]));
  {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__15_3(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // myself: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 111: private::get_item myself key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = frame->caller_result_count;
  myself = get__private__get_item();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_4(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // key: 0
  // value: 1
  // myself: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* value */
  frame->slots[2] = myself->closure.frame->slots[2]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: ... "@(key)=@(value)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = string__15_5;
  arguments->slots[2] = frame->slots[1] /* value */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__15_6;
}
static void cont__15_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 115: putenv "@(key)=@(value)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = var._putenv;
  func = myself->type;
  frame->cont = cont__15_7;
}
static void cont__15_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 116: private::set_item myself key value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* myself */;
  arguments->slots[1] = frame->slots[0] /* key */;
  arguments->slots[2] = frame->slots[1] /* value */;
  result_count = frame->caller_result_count;
  myself = get__private__set_item();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_1_env_2_(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // key: 0
  // value: 1
  // myself: 2
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* value */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* value */ = var._NONE;
  }
  frame->slots[2] /* myself */ = myself;
  // 110: NONE == value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[1] /* value */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__15_2;
}
static void cont__15_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 110: ... :
  // 111:   private::get_item myself key
  frame->slots[4] /* temp__2 */ = create_closure(entry__15_3, 0);
  // 112: :
  // 113:   #ewriteln key ": " value
  // 114:   
  // 115:   putenv "@(key)=@(value)"
  // 116:   private::set_item myself key value
  frame->slots[5] /* temp__3 */ = create_closure(entry__15_4, 0);
  // 109: if
  // 110:   NONE == value:
  // 111:     private::get_item myself key
  // 112:   :
  // 113:     #ewriteln key ": " value
  // 114:     
  // 115:     putenv "@(key)=@(value)"
  // 116:     private::set_item myself key value
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
EXPORT void collect__basic__environment(void) {
  var._argv = collect_node(var._argv);
  var._argc = collect_node(var._argc);
  var._envv = collect_node(var._envv);
  var._envc = collect_node(var._envc);
  var.std__program_name = collect_node(var.std__program_name);
  var._arguments = collect_node(var._arguments);
  var.std__command_line_arguments = collect_node(var.std__command_line_arguments);
  var._env_1 = collect_node(var._env_1);
  var._putenv = collect_node(var._putenv);
  var._NONE = collect_node(var._NONE);
  var._env_2 = collect_node(var._env_2);
  var.std__environment = collect_node(var.std__environment);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__environment(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__environment(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__0 = from_uint32(0U);
  character__61 = from_uchar32(61);
  number__1 = from_uint32(1U);
  func__1_1_argv = create_function(entry__1_1_argv, 1);
  func__2_1_argc = create_function(entry__2_1_argc, 0);
  func__4_1_envv = create_function(entry__4_1_envv, 1);
  func__5_1_envc = create_function(entry__5_1_envc, 0);
  func__12_1_putenv = create_function(entry__12_1_putenv, 1);
  unique__NONE = register_unique_item("NONE");
  string__15_5 = from_latin_1_string("=", 1);
  func__24_3 = create_function(entry__24_3, 1);
  func__27_2 = create_function(entry__27_2, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__environment(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__environment");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "program_name", get__std__program_name, &var.std__program_name);
  define_single_assign_static("std", "command_line_arguments", get__std__command_line_arguments, &var.std__command_line_arguments);
  assign_value(&var._NONE, unique__NONE);
  var._env_2 = create_future();
  define_multi_assign_static("std", "environment", get__std__environment, set__std__environment);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__environment(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__environment");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "before", &get__before, &get_value_or_future__before);
  use_read_only(NULL, "behind", &get__behind, &get_value_or_future__behind);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
  use_read_only(NULL, "from_utf8", &get__from_utf8, &get_value_or_future__from_utf8);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only("private", "get_item", &get__private__get_item, &get_value_or_future__private__get_item);
  use_read_only("private", "set_item", &get__private__set_item, &get_value_or_future__private__set_item);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  update_start_p = node_p;
  def_attribute(&var._env_2, -1, entry__15_1_env_2_);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__environment(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var._argv, &func__1_1_argv);
  assign_variable(&var._argc, &func__2_1_argc);
  assign_variable(&var._envv, &func__4_1_envv);
  assign_variable(&var._envc, &func__5_1_envc);
  assign_variable(&var._putenv, &func__12_1_putenv);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__environment(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__environment);
}
