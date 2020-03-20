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
IMPORT void *allocate(long size);
IMPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
IMPORT NODE *collect_node(NODE *node);
IMPORT void no_such_function(void);
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);
IMPORT const char *indent_to_string(int indent);
IMPORT int print(char **buf_p, const char *format, ...);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *create_future(void);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
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
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
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
static int poly_idx__contains;
static NODE_GETTER get__contains;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__is_a_value_range;
static NODE_GETTER get__is_a_value_range;
static int poly_idx__lower_bound_of;
static NODE_GETTER get__lower_bound_of;
static int poly_idx__serialize;
static NODE_GETTER get__serialize;
static NODE_GETTER get__spaces;
static NODE_GETTER get_value_or_future__spaces;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static int poly_idx__upper_bound_of;
static NODE_GETTER get__upper_bound_of;
static struct {
  NODE *std__is_a_value_range;
  NODE *types__value_range;
  NODE *std__value_range;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__is_a_value_range;
static void type__std__is_a_value_range(void);
static NODE *get__std__is_a_value_range(void) {
  return var.std__is_a_value_range;
}

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  NODE *lower_bound;
  NODE *upper_bound;
} VALUE_RANGE;
static NODE *get__types__value_range(void) {
  return var.types__value_range;
}
static NODE *create__types__value_range(NODE *lower_bound, NODE *upper_bound);
static void entry__6_1(void);
static NODE *func__6_1;
static NODE *get__std__value_range(void) {
  return var.std__value_range;
}
static void entry__7_1(void);
static NODE *func__7_1;
static void entry__8_1(void);
static NODE *func__8_1;

static long func__types__value_range___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__10_1;
static void entry__10_1(void);
static FRAME_INFO frame__10_1 = {2, {"left", "right"}};
static void cont__10_2(void);
static NODE *func__10_3;
static void entry__10_3(void);
static FRAME_INFO frame__10_3 = {2, {"left", "right"}};
static void cont__10_4(void);
static void cont__10_5(void);
static void cont__10_6(void);
static NODE *func__10_7;
static void entry__10_7(void);
static FRAME_INFO frame__10_7 = {2, {"left", "right"}};
static void cont__10_8(void);
static void cont__10_9(void);
static void cont__10_10(void);
static void cont__10_11(void);
static void cont__10_12(void);
static NODE *func__11_1;
static void entry__11_1(void);
static FRAME_INFO frame__11_1 = {2, {"self", "item"}};
static void cont__11_2(void);
static void cont__11_3(void);
static void cont__11_4(void);
static NODE *func__11_5;
static void entry__11_5(void);
static FRAME_INFO frame__11_5 = {2, {"self", "item"}};
static void cont__11_6(void);
static void cont__11_7(void);
static void cont__11_8(void);
static void cont__11_9(void);
static NODE *func__12_1;
static void entry__12_1(void);
static FRAME_INFO frame__12_1 = {2, {"self", "indent"}};
static void cont__12_2(void);
static void cont__12_3(void);
static void cont__12_4(void);
static void cont__12_5(void);
static void cont__12_6(void);
static void cont__12_7(void);
static void cont__12_8(void);
static void cont__12_9(void);
static void cont__12_10(void);
static void cont__12_11(void);
static NODE *string__12_12;
static NODE *string__12_13;
static NODE *string__12_14;
static void cont__12_15(void);
void run__basic__types__value_range(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_value_range, NULL, 23, 23, 2, 22},
  {run__basic__types__value_range, NULL, },
  {entry__6_1, NULL, 48, 51, 3, 2},
  {entry__7_1, NULL, 54, 57, 3, 2},
  {entry__8_1, NULL, 60, 63, 3, 2},
  {entry__10_7, NULL, 89, 89, 7, 26},
  {cont__10_8, &frame__10_7, 89, 89, 31, 51},
  {cont__10_9, &frame__10_7, 89, 89, 7, 51},
  {cont__10_10, &frame__10_7, 89, 89, 7, 51},
  {entry__10_3, NULL, 88, 88, 7, 26},
  {cont__10_4, &frame__10_3, 88, 88, 31, 51},
  {cont__10_5, &frame__10_3, 88, 88, 7, 51},
  {cont__10_6, &frame__10_3, 89, 89, 7, 51},
  {cont__10_11, &frame__10_3, },
  {entry__10_1, NULL, 87, 87, 7, 28},
  {cont__10_2, &frame__10_1, },
  {cont__10_12, &frame__10_1, 85, 89, 3, 52},
  {entry__11_5, NULL, 92, 92, 46, 65},
  {cont__11_6, &frame__11_5, 92, 92, 38, 65},
  {cont__11_7, &frame__11_5, 92, 92, 38, 65},
  {cont__11_8, &frame__11_5, 92, 92, 38, 65},
  {entry__11_1, NULL, 92, 92, 14, 33},
  {cont__11_2, &frame__11_1, 92, 92, 6, 33},
  {cont__11_3, &frame__11_1, 92, 92, 6, 33},
  {cont__11_4, &frame__11_1, 92, 92, 6, 65},
  {cont__11_9, &frame__11_1, 92, 92, 3, 65},
  {entry__12_1, NULL, 101, 101, 14, 21},
  {cont__12_2, &frame__12_1, 101, 101, 7, 22},
  {cont__12_3, &frame__12_1, 101, 101, 36, 55},
  {cont__12_4, &frame__12_1, 101, 101, 26, 56},
  {cont__12_5, &frame__12_1, 101, 101, 60, 67},
  {cont__12_6, &frame__12_1, 102, 102, 18, 25},
  {cont__12_7, &frame__12_1, 102, 102, 11, 26},
  {cont__12_8, &frame__12_1, 102, 102, 40, 59},
  {cont__12_9, &frame__12_1, 102, 102, 30, 60},
  {cont__12_10, &frame__12_1, 102, 102, 64, 71},
  {cont__12_11, &frame__12_1, 99, 102, 6, 72},
  {cont__12_15, &frame__12_1, 99, 102, 3, 72}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  VALUE_RANGE value_range;
};
static void type__std__is_a_value_range(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_value_range);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_value_range, attr);
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
static NODE *number__0;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__value_range",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/value_range.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__value_range(void) {
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
static void *collect_value_range(VALUE_RANGE *node) {
  VALUE_RANGE *new_node = allocate(sizeof(VALUE_RANGE));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->lower_bound = collect_node(node->lower_bound);
  new_node->upper_bound = collect_node(node->upper_bound);
  return new_node;
}

static VTABLE vtable__types__value_range = {
  sizeof(VALUE_RANGE),
  (COLLECTOR *)&collect_value_range,
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
  &func__types__value_range___debug_string
};

static ATTRIBUTES attributes__types__value_range = {
  &vtable__types__value_range,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__value_range(void) {
  {
    runtime_error("Attempt to call a value range as a function!");
  }
}
static NODE *create__types__value_range(NODE *lower_bound, NODE *upper_bound) {
  NODE *node = allocate(sizeof(VALUE_RANGE));
  node->type = type__types__value_range;
  node->attributes = &attributes__types__value_range;
  node->value_range.lower_bound = lower_bound;
  node->value_range.upper_bound = upper_bound;
  return node;
}
static void entry__6_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__value_range(arguments->slots[0], arguments->slots[1]));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__7_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(arguments->slots[0]->value_range.lower_bound);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__8_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(arguments->slots[0]->value_range.upper_bound);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static long func__types__value_range___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  int i, n, len;
  n = debug_print_head(&indent, &buf, "value_range");
  const char *contents_indent = indent_to_string(indent);
  n += print(&buf, contents_indent);
  len = debug_string(node->value_range.lower_bound, indent, max_depth-1, buf);
  if (buf) buf += len;
  n += len;
  n += print(&buf, contents_indent);
  len = debug_string(node->value_range.upper_bound, indent, max_depth-1, buf);
  if (buf) buf += len;
  n += len;
  return n;
}
static void entry__10_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 87: right.is_a_value_range
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__is_a_value_range();
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__3 */ = create_closure(entry__10_3, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_12;
}
static void entry__10_3(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // left: 0
  // right: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* left */
  frame->slots[1] = myself->closure.frame->slots[1]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 88: lower_bound_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void cont__10_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 88: ... lower_bound_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 88: lower_bound_of(left) == lower_bound_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__10_6;
}
static void cont__10_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 89: upper_bound_of(left) == upper_bound_of(right)
  frame->slots[6] /* temp__5 */ = create_closure(entry__10_7, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_11;
}
static void entry__10_7(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // left: 0
  // right: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* left */
  frame->slots[1] = myself->closure.frame->slots[1]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 89: upper_bound_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__10_8;
}
static void cont__10_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 89: ... upper_bound_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__10_9;
}
static void cont__10_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 89: upper_bound_of(left) == upper_bound_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__10_10;
}
static void cont__10_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: upper_bound_of(left) == upper_bound_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 85: ->
  // 86:   &&
  // 87:     right.is_a_value_range
  // 88:     lower_bound_of(left) == lower_bound_of(right)
  // 89:     upper_bound_of(left) == upper_bound_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_1(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // item: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 92: ... lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__11_2;
}
static void cont__11_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 92: ... item >= lower_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 92: ... item >= lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__11_4;
}
static void cont__11_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 92: ... item <= upper_bound_of(self)
  frame->slots[6] /* temp__5 */ = create_closure(entry__11_5, 0);
  // 92: ... item >= lower_bound_of(self) && item <= upper_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__11_9;
}
static void entry__11_5(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // item: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 92: ... upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__11_6;
}
static void cont__11_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 92: ... item <= upper_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* item */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_7;
}
static void cont__11_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 92: ... item <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__11_8;
}
static void cont__11_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 92: ... item <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 92: -> item >= lower_bound_of(self) && item <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_1(void) {
  allocate_initialized_frame_gc(2, 13);
  // slot allocations:
  // self: 0
  // indent: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* indent */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* indent */ = number__0;
  }
  // 101: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__12_2;
}
static void cont__12_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 101: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 101: ... lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__12_4;
}
static void cont__12_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 101: ... serialize(lower_bound_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__12_5;
}
static void cont__12_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 101: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__12_6;
}
static void cont__12_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 102: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__12_7;
}
static void cont__12_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 102: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__12_8;
}
static void cont__12_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 102: ... upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__12_9;
}
static void cont__12_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__10 */ = arguments->slots[0];
  // 102: ... serialize(upper_bound_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__10 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__12_10;
}
static void cont__12_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 102: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__12_11;
}
static void cont__12_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__11 */ = arguments->slots[0];
  //  99: ... "
  // 100:   value_range
  // 101:   @(spaces(indent+2))@(serialize(lower_bound_of(self)))@(indent+2)@
  // 102:   @nl;@(spaces(indent+2))@(serialize(upper_bound_of(self)))@(indent+2)
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__12_12;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = frame->slots[7] /* temp__6 */;
  arguments->slots[4] = string__12_13;
  arguments->slots[5] = frame->slots[8] /* temp__7 */;
  arguments->slots[6] = frame->slots[10] /* temp__9 */;
  arguments->slots[7] = frame->slots[12] /* temp__11 */;
  arguments->slots[8] = string__12_14;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__12_15;
}
static void cont__12_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  //  99: -> "
  // 100:   value_range
  // 101:   @(spaces(indent+2))@(serialize(lower_bound_of(self)))@(indent+2)@
  // 102:   @nl;@(spaces(indent+2))@(serialize(upper_bound_of(self)))@(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__value_range(void) {
  var.std__is_a_value_range = collect_node(var.std__is_a_value_range);
  var.types__value_range = collect_node(var.types__value_range);
  collect_static_attributes(&attributes__types__value_range);
  var.std__value_range = collect_node(var.std__value_range);
  func__10_1 = collect_node(func__10_1);
  func__11_1 = collect_node(func__11_1);
  string__12_12 = collect_node(string__12_12);
  string__12_13 = collect_node(string__12_13);
  string__12_14 = collect_node(string__12_14);
  func__12_1 = collect_node(func__12_1);
  number__0 = collect_node(number__0);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__value_range(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_a_value_range", get__std__is_a_value_range, &poly_idx__std__is_a_value_range, &var.std__is_a_value_range);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__value_range(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__value_range");
  set_used_namespaces(used_namespaces);
  number__0 = create_future();
  number__2 = create_future();
  var.types__value_range = create_future_with_prototype(create__types__value_range(NULL, NULL));
  define_single_assign_static("types", "value_range", get__types__value_range, &var.types__value_range);
  func__6_1 = create_future();
  define_single_assign_static("std", "value_range", get__std__value_range, &var.std__value_range);
  func__7_1 = create_future();
  func__8_1 = create_future();
  func__10_1 = create_future();
  func__11_1 = create_future();
  string__12_12 = from_latin_1_string("value_range\012", 12);
  string__12_13 = from_latin_1_string("\012", 1);
  string__12_14 = from_latin_1_string("\012", 1);
  func__12_1 = create_future();
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__value_range(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__value_range");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "contains", &get__contains, &poly_idx__contains);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "is_a_value_range", &get__is_a_value_range, &poly_idx__is_a_value_range);
  use_polymorphic_function(NULL, "lower_bound_of", &get__lower_bound_of, &poly_idx__lower_bound_of);
  use_polymorphic_function(NULL, "serialize", &get__serialize, &poly_idx__serialize);
  use_read_only(NULL, "spaces", &get__spaces, &get_value_or_future__spaces);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_polymorphic_function(NULL, "upper_bound_of", &get__upper_bound_of, &poly_idx__upper_bound_of);
  define_attribute("types", "object", poly_idx__is_a_value_range, get__false());
  define_attribute("types", "value_range", poly_idx__is_a_value_range, get__true());
  define_method("types", "value_range", poly_idx__lower_bound_of, func__7_1);
  define_method("types", "value_range", poly_idx__upper_bound_of, func__8_1);
  define_method("types", "value_range", poly_idx__equal, func__10_1);
  define_method("types", "value_range", poly_idx__contains, func__11_1);
  define_method("types", "value_range", poly_idx__serialize, func__12_1);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__value_range(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&number__0, from_uint32(0U));
  assign_value(&number__2, from_uint32(2U));
  assign_value(&var.std__is_a_value_range, create_function(type__std__is_a_value_range, -1));
  assign_value(&var.types__value_range, get__types__object());
  assign_variable(&var.std__value_range, &func__6_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__value_range(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__6_1, create_function(entry__6_1, 2));
  assign_value(&func__7_1, create_function(entry__7_1, 1));
  assign_value(&func__8_1, create_function(entry__8_1, 1));
  assign_value(&func__10_1, create_function(entry__10_1, 2));
  assign_value(&func__11_1, create_function(entry__11_1, 2));
  assign_value(&func__12_1, create_function(entry__12_1, -1));
  register_collector(collect__basic__types__value_range);
}
