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
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
REGISTER FRAME *arguments ASM("r12");
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
IMPORT NODE *clone_object_and_attributes(NODE *node);
IMPORT void *update_start_p;
IMPORT void *node_p;
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
REGISTER FUNC func ASM("r14");
REGISTER FRAME *frame ASM("r15");
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
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void *collect_simple_node(SIMPLE_NODE *node);
IMPORT void no_such_function(void);
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT NODE *from_bool(int val);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *undefined;
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_c_function(const char *name, void *func);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
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
IMPORT void assign_value(NODE **dest, NODE *val);
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
static int poly_idx__and;
static NODE_GETTER get__and;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__if;
static NODE_GETTER get__if;
static int poly_idx__is_a_boolean;
static NODE_GETTER get__is_a_boolean;
static int poly_idx__not;
static NODE_GETTER get__not;
static int poly_idx__or;
static NODE_GETTER get__or;
static NODE_GETTER get__pass;
static NODE_GETTER get_value_or_future__pass;
static NODE_GETTER get__register_deserializer;
static NODE_GETTER get_value_or_future__register_deserializer;
static int poly_idx__std__to_string;
static NODE_GETTER get__std__to_string;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static int poly_idx__unless;
static NODE_GETTER get__unless;
static struct {
  NODE *std__is_a_boolean;
  NODE *types__true;
  NODE *std__true;
  NODE *types__false;
  NODE *std__false;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__is_a_boolean;
static void type__std__is_a_boolean(void);
static NODE *get__std__is_a_boolean(void) {
  return var.std__is_a_boolean;
}
static NODE *get__types__true(void) {
  return var.types__true;
}
static NODE *create__types__true();
static NODE *get__std__true(void) {
  return var.std__true;
}
static NODE *get__types__false(void) {
  return var.types__false;
}
static NODE *create__types__false();
static NODE *get__std__false(void) {
  return var.std__false;
}

static int func__types__true___to_bool(NODE *node);

static int func__types__false___to_bool(NODE *node);
static NODE *string__12_1;
static NODE *string__13_1;

static long func__types__true___debug_string(NODE *node, int indent, int max_depth, char *buf);

static long func__types__false___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__16_1_types__true_equal(void);
static NODE *func__16_1_types__true_equal;
static void entry__17_1_types__false_equal(void);
static NODE *func__17_1_types__false_equal;
static NODE *func__18_1_types__true_not;
static void entry__18_1_types__true_not(void);
static FRAME_INFO frame__18_1_types__true_not = {1, {"self"}};
static NODE *func__19_1_types__false_not;
static void entry__19_1_types__false_not(void);
static FRAME_INFO frame__19_1_types__false_not = {1, {"self"}};
static NODE *func__20_1_types__true_and;
static void entry__20_1_types__true_and(void);
static FRAME_INFO frame__20_1_types__true_and = {2, {"left", "right"}};
static void cont__20_2(void);
static NODE *func__21_1_types__false_and;
static void entry__21_1_types__false_and(void);
static FRAME_INFO frame__21_1_types__false_and = {2, {"left", "right"}};
static NODE *func__22_1_types__true_or;
static void entry__22_1_types__true_or(void);
static FRAME_INFO frame__22_1_types__true_or = {2, {"left", "right"}};
static NODE *func__23_1_types__false_or;
static void entry__23_1_types__false_or(void);
static FRAME_INFO frame__23_1_types__false_or = {2, {"left", "right"}};
static void cont__23_2(void);
static NODE *func__24_1_types__true_if;
static void entry__24_1_types__true_if(void);
static FRAME_INFO frame__24_1_types__true_if = {3, {"condition", "then", "else"}};
static NODE *func__25_1_types__false_if;
static void entry__25_1_types__false_if(void);
static FRAME_INFO frame__25_1_types__false_if = {3, {"condition", "then", "else"}};
static NODE *func__26_1_types__true_unless;
static void entry__26_1_types__true_unless(void);
static FRAME_INFO frame__26_1_types__true_unless = {2, {"condition", "body"}};
static NODE *func__27_1_types__false_unless;
static void entry__27_1_types__false_unless(void);
static FRAME_INFO frame__27_1_types__false_unless = {2, {"condition", "body"}};
static NODE *func__57_1;
static void entry__57_1(void);
static FRAME_INFO frame__57_1 = {2, {"text", "base_indent"}};
static void cont__57_2(void);
static NODE *func__58_1;
static void entry__58_1(void);
static FRAME_INFO frame__58_1 = {2, {"text", "base_indent"}};
static void cont__58_2(void);
void run__basic__types__boolean(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_boolean, NULL, 23, 23, 2, 18},
  {run__basic__types__boolean, NULL, 175, 175, 1, 62},
  {cont__57_2, NULL, 176, 176, 1, 64},
  {cont__58_2, NULL, },
  {entry__16_1_types__true_equal, NULL, 138, 141, 3, 2},
  {entry__17_1_types__false_equal, NULL, 144, 147, 3, 2},
  {entry__18_1_types__true_not, NULL, 149, 149, 27, 34},
  {entry__19_1_types__false_not, NULL, 151, 151, 28, 34},
  {entry__20_1_types__true_and, NULL, 153, 153, 36, 42},
  {cont__20_2, &frame__20_1_types__true_and, 153, 153, 33, 42},
  {entry__21_1_types__false_and, NULL, 155, 155, 35, 42},
  {entry__22_1_types__true_or, NULL, 157, 157, 33, 39},
  {entry__23_1_types__false_or, NULL, 159, 159, 36, 42},
  {cont__23_2, &frame__23_1_types__false_or, 159, 159, 33, 42},
  {entry__24_1_types__true_if, NULL, 161, 161, 43, 46},
  {entry__25_1_types__false_if, NULL, 169, 169, 3, 6},
  {entry__26_1_types__true_unless, NULL, 171, 171, 41, 44},
  {entry__27_1_types__false_unless, NULL, 173, 173, 41, 44},
  {entry__57_1, NULL, 175, 175, 51, 62},
  {entry__58_1, NULL, 176, 176, 52, 64}
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
static void type__std__is_a_boolean(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_boolean);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_boolean, attr);
      arguments = node_p;
      argument_count = 1;
      arguments->slots[0] = temp;
    } else {
      arguments = node_p;
      arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);
    }
    func = frame->cont;
    frame->cont = invalid_continuation;
  } else {
    func = myself->type;
  }
}

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__boolean",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/boolean.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__boolean(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 175: register_deserializer "true": (text _base_indent) -> text true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__12_1;
  arguments->slots[1] = func__57_1;
  result_count = 0;
  myself = get__register_deserializer();
  func = myself->type;
  frame->cont = cont__57_2;
}
static void entry__57_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // text: 0
  // base_indent: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 175: ... -> text true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__57_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 176: register_deserializer "false": (text _base_indent) -> text false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__13_1;
  arguments->slots[1] = func__58_1;
  result_count = 0;
  myself = get__register_deserializer();
  func = myself->type;
  frame->cont = cont__58_2;
}
static void entry__58_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // text: 0
  // base_indent: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 176: ... -> text false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = get__false();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__58_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static VTABLE vtable__types__true = {
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
  &func__types__true___to_bool,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__true___debug_string
};

static ATTRIBUTES attributes__types__true = {
  &vtable__types__true,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__true(void) {
  {
    runtime_error("Attempt to call the boolean value true as a function!");
  }
}
SIMPLE_NODE types__true__node =
  {
    type__types__true,
    &attributes__types__true
  };

static NODE *create__types__true() {
  return (NODE *)&types__true__node;
}

static VTABLE vtable__types__false = {
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
  &func__types__false___to_bool,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__false___debug_string
};

static ATTRIBUTES attributes__types__false = {
  &vtable__types__false,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__false(void) {
  {
    runtime_error("Attempt to call the boolean value false as a function!");
  }
}
SIMPLE_NODE types__false__node =
  {
    type__types__false,
    &attributes__types__false
  };

static NODE *create__types__false() {
  return (NODE *)&types__false__node;
}

NODE *runtime__from_bool(int val) {
  if (val)
    return get__std__true();
  else
    return get__std__false();
}

static int func__types__true___to_bool(NODE *node) {
  return true;
}

static int func__types__false___to_bool(NODE *node) {
  return false;
}

static long func__types__true___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "true");
}

static long func__types__false___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "false");
}
static void entry__16_1_types__true_equal(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_bool((arguments->slots[1])->type == type__types__true));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__17_1_types__false_equal(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_bool((arguments->slots[1])->type == type__types__false));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__18_1_types__true_not(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 149: ... -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_1_types__false_not(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 151: ... -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_1_types__true_and(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 153: ... right()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[1] /* right */;
  func = myself->type;
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 153: ... -> right()
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_1_types__false_and(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 155: ... -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_1_types__true_or(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 157: ... -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_1_types__false_or(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 159: ... right()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[1] /* right */;
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 159: ... -> right()
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_1_types__true_if(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // condition: 0
  // then: 1
  // else: 2
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* else */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* else */ = undefined;
  }
  // 161: ... then
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* then */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_1_types__false_if(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // condition: 0
  // then: 1
  // else: 2
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* else */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* else */ = get__pass();
  }
  // 169: else
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* else */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_1_types__true_unless(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // condition: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 171: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__27_1_types__false_unless(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // condition: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 173: ... body
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__types__boolean(void) {
  var.std__is_a_boolean = collect_node(var.std__is_a_boolean);
  var.types__true = collect_node(var.types__true);
  collect_static_attributes(&attributes__types__true);
  var.std__true = collect_node(var.std__true);
  var.types__false = collect_node(var.types__false);
  collect_static_attributes(&attributes__types__false);
  var.std__false = collect_node(var.std__false);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__boolean(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_a_boolean", get__std__is_a_boolean, &poly_idx__std__is_a_boolean, &var.std__is_a_boolean);
  define_c_function("from_bool", runtime__from_bool);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__boolean(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  string__12_1 = from_latin_1_string("true", 4);
  string__13_1 = from_latin_1_string("false", 5);
  func__16_1_types__true_equal = create_function(entry__16_1_types__true_equal, 2);
  func__17_1_types__false_equal = create_function(entry__17_1_types__false_equal, 2);
  func__18_1_types__true_not = create_function(entry__18_1_types__true_not, 1);
  func__19_1_types__false_not = create_function(entry__19_1_types__false_not, 1);
  func__20_1_types__true_and = create_function(entry__20_1_types__true_and, 2);
  func__21_1_types__false_and = create_function(entry__21_1_types__false_and, 2);
  func__22_1_types__true_or = create_function(entry__22_1_types__true_or, 2);
  func__23_1_types__false_or = create_function(entry__23_1_types__false_or, 2);
  func__24_1_types__true_if = create_function(entry__24_1_types__true_if, -1);
  func__25_1_types__false_if = create_function(entry__25_1_types__false_if, -1);
  func__26_1_types__true_unless = create_function(entry__26_1_types__true_unless, 2);
  func__27_1_types__false_unless = create_function(entry__27_1_types__false_unless, 2);
  func__57_1 = create_function(entry__57_1, 2);
  func__58_1 = create_function(entry__58_1, 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__boolean(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__boolean");
  set_used_namespaces(used_namespaces);
  var.types__true = create_future_with_prototype(create__types__true());
  define_single_assign_static("types", "true", get__types__true, &var.types__true);
  var.std__true = create__types__true();
  define_single_assign_static("std", "true", get__std__true, &var.std__true);
  var.types__false = create_future_with_prototype(create__types__false());
  define_single_assign_static("types", "false", get__types__false, &var.types__false);
  var.std__false = create__types__false();
  define_single_assign_static("std", "false", get__std__false, &var.std__false);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__boolean(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__boolean");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "and", &get__and, &poly_idx__and);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "if", &get__if, &poly_idx__if);
  use_polymorphic_function(NULL, "is_a_boolean", &get__is_a_boolean, &poly_idx__is_a_boolean);
  use_polymorphic_function(NULL, "not", &get__not, &poly_idx__not);
  use_polymorphic_function(NULL, "or", &get__or, &poly_idx__or);
  use_read_only(NULL, "pass", &get__pass, &get_value_or_future__pass);
  use_read_only(NULL, "register_deserializer", &get__register_deserializer, &get_value_or_future__register_deserializer);
  use_polymorphic_function("std", "to_string", &get__std__to_string, &poly_idx__std__to_string);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_polymorphic_function(NULL, "unless", &get__unless, &poly_idx__unless);
  define_attribute("types", "object", poly_idx__is_a_boolean, get__false());
  define_attribute("types", "true", poly_idx__is_a_boolean, get__true());
  define_attribute("types", "false", poly_idx__is_a_boolean, get__true());
  define_attribute("types", "true", poly_idx__std__to_string, string__12_1);
  define_attribute("types", "false", poly_idx__std__to_string, string__13_1);
  define_method("types", "true", poly_idx__equal, func__16_1_types__true_equal);
  define_method("types", "false", poly_idx__equal, func__17_1_types__false_equal);
  define_method("types", "true", poly_idx__not, func__18_1_types__true_not);
  define_method("types", "false", poly_idx__not, func__19_1_types__false_not);
  define_method("types", "true", poly_idx__and, func__20_1_types__true_and);
  define_method("types", "false", poly_idx__and, func__21_1_types__false_and);
  define_method("types", "true", poly_idx__or, func__22_1_types__true_or);
  define_method("types", "false", poly_idx__or, func__23_1_types__false_or);
  define_method("types", "true", poly_idx__if, func__24_1_types__true_if);
  define_method("types", "false", poly_idx__if, func__25_1_types__false_if);
  define_method("types", "true", poly_idx__unless, func__26_1_types__true_unless);
  define_method("types", "false", poly_idx__unless, func__27_1_types__false_unless);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__boolean(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_boolean, create_function(type__std__is_a_boolean, -1));
  assign_value(&var.types__true, get__types__object());
  assign_value(&var.types__false, get__types__object());
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__boolean(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__boolean);
}
