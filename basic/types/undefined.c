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
IMPORT NODE *undefined;
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
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_arguments_error(void);
IMPORT void invalid_results_error(void);
IMPORT void *collect_simple_node(SIMPLE_NODE *node);
IMPORT void no_such_function(void);
IMPORT OCTREE no_attributes_level_1;
IMPORT OCTREE no_attributes_level_2;
IMPORT OCTREE no_attributes_level_3;
IMPORT OCTREE no_attributes_level_4;
IMPORT OCTREE no_attributes_level_5;
IMPORT OCTREE no_attributes_level_6;
IMPORT OCTREE no_attributes_level_7;
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
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
static int poly_idx__default_value;
static NODE_GETTER get__default_value;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__is_defined;
static NODE_GETTER get__is_defined;
static int poly_idx__is_undefined;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get__register_deserializer;
static NODE_GETTER get_value_or_future__register_deserializer;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static struct {
  NODE *types__undefined;
  NODE *std__undefined;
} var;
static const char *var_names[] = {
};
static NODE *get__types__undefined(void) {
  return var.types__undefined;
}
static NODE *create__types__undefined();
static NODE *get__std__undefined(void) {
  return var.std__undefined;
}
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {2, {"left", "right"}};
static void cont__5_2(void);
static NODE *func__6_1;
static void entry__6_1(void);
static FRAME_INFO frame__6_1 = {2, {"self", "default"}};

static long func__types__undefined___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *string__16_1;
static NODE *func__16_2;
static void entry__16_2(void);
static FRAME_INFO frame__16_2 = {2, {"text", "base_indent"}};
static void cont__16_3(void);
void run__basic__types__undefined(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__types__undefined, NULL, 53, 53, 1, 72},
  {cont__16_3, NULL, },
  {entry__5_1, NULL, 41, 41, 43, 60},
  {cont__5_2, &frame__5_1, 41, 41, 40, 60},
  {entry__6_1, NULL, 43, 43, 50, 59},
  {entry__16_2, NULL, 53, 53, 56, 72}
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

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__undefined",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/undefined.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__undefined(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 53: register_deserializer "undefined": (text _base_indent) -> text undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__16_1;
  arguments->slots[1] = func__16_2;
  result_count = 0;
  myself = get__register_deserializer();
  func = myself->type;
  frame->cont = cont__16_3;
}
static void entry__16_2(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // text: 0
  // base_indent: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 53: ... -> text undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__16_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static VTABLE vtable__types__undefined = {
  sizeof(SIMPLE_NODE),
  (COLLECTOR *)&collect_simple_node,
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
  &func__types__undefined___debug_string
};

static ATTRIBUTES attributes__types__undefined = {
  &vtable__types__undefined,
  {
    &no_attributes_level_1, &no_attributes_level_2,
    &no_attributes_level_3, &no_attributes_level_4,
    &no_attributes_level_5, &no_attributes_level_6,
    &no_attributes_level_7
  }
};

static void type__types__undefined(void) {
  {
    runtime_error("Attempt to call an undefined value as a function!");
  }
}
SIMPLE_NODE types__undefined__node =
  {
    type__types__undefined,
    &attributes__types__undefined
  };

static NODE *create__types__undefined() {
  return (NODE *)&types__undefined__node;
}
static void entry__5_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 41: ... right.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 41: ... -> right.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // default: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 43: ... -> default
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* default */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static long func__types__undefined___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "undefined");
}
EXPORT void collect__basic__types__undefined(void) {
  var.types__undefined = collect_node(var.types__undefined);
  collect_static_attributes(&attributes__types__undefined);
  var.std__undefined = collect_node(var.std__undefined);
  string__16_1 = collect_node(string__16_1);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__undefined(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__undefined(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  func__5_1 = create_function(entry__5_1, 2);
  func__6_1 = create_function(entry__6_1, 2);
  func__16_2 = create_function(entry__16_2, 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__undefined(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__undefined");
  set_used_namespaces(used_namespaces);
  var.types__undefined = create__types__undefined();
  define_single_assign_static("types", "undefined", get__types__undefined, &var.types__undefined);
  var.std__undefined = create__types__undefined();
  define_single_assign_static("std", "undefined", get__std__undefined, &var.std__undefined);
  string__16_1 = from_latin_1_string("undefined", 9);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__undefined(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__undefined");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "default_value", &get__default_value, &poly_idx__default_value);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "is_defined", &get__is_defined, &poly_idx__is_defined);
  use_polymorphic_function(NULL, "is_undefined", &get__is_undefined, &poly_idx__is_undefined);
  use_read_only(NULL, "register_deserializer", &get__register_deserializer, &get_value_or_future__register_deserializer);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  define_attribute("types", "undefined", poly_idx__is_defined, get__false());
  define_attribute("types", "undefined", poly_idx__is_undefined, get__true());
  define_method("types", "undefined", poly_idx__equal, func__5_1);
  define_method("types", "undefined", poly_idx__default_value, func__6_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__undefined(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__undefined(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__undefined);
}
