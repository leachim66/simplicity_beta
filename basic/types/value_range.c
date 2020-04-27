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
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
static int poly_idx__contains;
static NODE_GETTER get__contains;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__for_each;
static NODE_GETTER get__for_each;
static NODE_GETTER get__from_to;
static NODE_GETTER get_value_or_future__from_to;
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
static void entry__std__value_range_1(void);
static NODE *func__std__value_range_1;
static NODE *get__std__value_range(void) {
  return var.std__value_range;
}
static void entry__types__value_range__lower_bound_of_1(void);
static NODE *func__types__value_range__lower_bound_of_1;
static void entry__types__value_range__upper_bound_of_1(void);
static NODE *func__types__value_range__upper_bound_of_1;

static long func__types__value_range___debug_string(
  NODE *node, int indent, int max_depth, char *buf
);
static NODE *func__types__value_range__equal_1;
static void entry__types__value_range__equal_1(void);
static FRAME_INFO frame__types__value_range__equal_1 = {2, {"left", "right"}};
static void cont__types__value_range__equal_2(void);
static NODE *func__types__value_range__equal_3;
static void entry__types__value_range__equal_3(void);
static FRAME_INFO frame__types__value_range__equal_3 = {2, {"left", "right"}};
static void cont__types__value_range__equal_4(void);
static void cont__types__value_range__equal_5(void);
static void cont__types__value_range__equal_6(void);
static NODE *func__types__value_range__equal_7;
static void entry__types__value_range__equal_7(void);
static FRAME_INFO frame__types__value_range__equal_7 = {2, {"left", "right"}};
static void cont__types__value_range__equal_8(void);
static void cont__types__value_range__equal_9(void);
static void cont__types__value_range__equal_10(void);
static void cont__types__value_range__equal_11(void);
static void cont__types__value_range__equal_12(void);
static NODE *func__types__value_range__contains_1;
static void entry__types__value_range__contains_1(void);
static FRAME_INFO frame__types__value_range__contains_1 = {2, {"self", "item"}};
static void cont__types__value_range__contains_2(void);
static void cont__types__value_range__contains_3(void);
static void cont__types__value_range__contains_4(void);
static NODE *func__types__value_range__contains_5;
static void entry__types__value_range__contains_5(void);
static FRAME_INFO frame__types__value_range__contains_5 = {2, {"self", "item"}};
static void cont__types__value_range__contains_6(void);
static void cont__types__value_range__contains_7(void);
static void cont__types__value_range__contains_8(void);
static void cont__types__value_range__contains_9(void);
static NODE *func__types__value_range__for_each_1;
static void entry__types__value_range__for_each_1(void);
static FRAME_INFO frame__types__value_range__for_each_1 = {2, {"self", "body"}};
static void cont__types__value_range__for_each_2(void);
static void cont__types__value_range__for_each_3(void);
static NODE *func__types__value_range__for_each_4;
static void entry__types__value_range__for_each_4(void);
static FRAME_INFO frame__types__value_range__for_each_4 = {2, {"item", "body"}};
static NODE *func__types__value_range__serialize_1;
static void entry__types__value_range__serialize_1(void);
static FRAME_INFO frame__types__value_range__serialize_1 = {2, {"self", "indent"}};
static void cont__types__value_range__serialize_2(void);
static void cont__types__value_range__serialize_3(void);
static void cont__types__value_range__serialize_4(void);
static void cont__types__value_range__serialize_5(void);
static void cont__types__value_range__serialize_6(void);
static void cont__types__value_range__serialize_7(void);
static void cont__types__value_range__serialize_8(void);
static void cont__types__value_range__serialize_9(void);
static void cont__types__value_range__serialize_10(void);
static void cont__types__value_range__serialize_11(void);
static NODE *string__d62119844f001643;
static NODE *string__578a5af303e9ceb;
static void cont__types__value_range__serialize_14(void);
void run__basic__types__value_range(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_value_range, NULL, 23, 23, 2, 22},
  {run__basic__types__value_range, NULL, },
  {entry__std__value_range_1, NULL, 52, 55, 3, 2},
  {entry__types__value_range__lower_bound_of_1, NULL, 60, 63, 3, 2},
  {entry__types__value_range__upper_bound_of_1, NULL, 68, 71, 3, 2},
  {entry__types__value_range__equal_7, NULL, 105, 105, 7, 26},
  {cont__types__value_range__equal_8, &frame__types__value_range__equal_7, 105, 105, 31, 51},
  {cont__types__value_range__equal_9, &frame__types__value_range__equal_7, 105, 105, 7, 51},
  {cont__types__value_range__equal_10, &frame__types__value_range__equal_7, 105, 105, 7, 51},
  {entry__types__value_range__equal_3, NULL, 104, 104, 7, 26},
  {cont__types__value_range__equal_4, &frame__types__value_range__equal_3, 104, 104, 31, 51},
  {cont__types__value_range__equal_5, &frame__types__value_range__equal_3, 104, 104, 7, 51},
  {cont__types__value_range__equal_6, &frame__types__value_range__equal_3, 105, 105, 7, 51},
  {cont__types__value_range__equal_11, &frame__types__value_range__equal_3, },
  {entry__types__value_range__equal_1, NULL, 103, 103, 7, 28},
  {cont__types__value_range__equal_2, &frame__types__value_range__equal_1, },
  {cont__types__value_range__equal_12, &frame__types__value_range__equal_1, 101, 105, 3, 52},
  {entry__types__value_range__contains_5, NULL, 119, 119, 46, 65},
  {cont__types__value_range__contains_6, &frame__types__value_range__contains_5, 119, 119, 38, 65},
  {cont__types__value_range__contains_7, &frame__types__value_range__contains_5, 119, 119, 38, 65},
  {cont__types__value_range__contains_8, &frame__types__value_range__contains_5, 119, 119, 38, 65},
  {entry__types__value_range__contains_1, NULL, 119, 119, 14, 33},
  {cont__types__value_range__contains_2, &frame__types__value_range__contains_1, 119, 119, 6, 33},
  {cont__types__value_range__contains_3, &frame__types__value_range__contains_1, 119, 119, 6, 33},
  {cont__types__value_range__contains_4, &frame__types__value_range__contains_1, 119, 119, 6, 65},
  {cont__types__value_range__contains_9, &frame__types__value_range__contains_1, 119, 119, 3, 65},
  {entry__types__value_range__for_each_4, NULL, 134, 134, 5, 13},
  {entry__types__value_range__for_each_1, NULL, 133, 133, 11, 30},
  {cont__types__value_range__for_each_2, &frame__types__value_range__for_each_1, 133, 133, 32, 51},
  {cont__types__value_range__for_each_3, &frame__types__value_range__for_each_1, 133, 134, 3, 13},
  {entry__types__value_range__serialize_1, NULL, 145, 145, 14, 21},
  {cont__types__value_range__serialize_2, &frame__types__value_range__serialize_1, 145, 145, 7, 22},
  {cont__types__value_range__serialize_3, &frame__types__value_range__serialize_1, 145, 145, 36, 55},
  {cont__types__value_range__serialize_4, &frame__types__value_range__serialize_1, 145, 145, 26, 56},
  {cont__types__value_range__serialize_5, &frame__types__value_range__serialize_1, 145, 145, 60, 67},
  {cont__types__value_range__serialize_6, &frame__types__value_range__serialize_1, 146, 146, 18, 25},
  {cont__types__value_range__serialize_7, &frame__types__value_range__serialize_1, 146, 146, 11, 26},
  {cont__types__value_range__serialize_8, &frame__types__value_range__serialize_1, 146, 146, 40, 59},
  {cont__types__value_range__serialize_9, &frame__types__value_range__serialize_1, 146, 146, 30, 60},
  {cont__types__value_range__serialize_10, &frame__types__value_range__serialize_1, 146, 146, 64, 71},
  {cont__types__value_range__serialize_11, &frame__types__value_range__serialize_1, 143, 146, 6, 72},
  {cont__types__value_range__serialize_14, &frame__types__value_range__serialize_1, 143, 146, 3, 72}
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
static void entry__std__value_range_1(void) {
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
static void entry__types__value_range__lower_bound_of_1(void) {
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
static void entry__types__value_range__upper_bound_of_1(void) {
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

static long func__types__value_range___debug_string(
  NODE *node, int indent, int max_depth, char *buf
) {
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
static void entry__types__value_range__equal_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 103: right.is_a_value_range
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__is_a_value_range();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_2;
}
static void cont__types__value_range__equal_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__value_range__equal_3, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_12;
}
static void entry__types__value_range__equal_3(void) {
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
  // 104: lower_bound_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_4;
}
static void cont__types__value_range__equal_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 104: ... lower_bound_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_5;
}
static void cont__types__value_range__equal_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 104: lower_bound_of(left) == lower_bound_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_6;
}
static void cont__types__value_range__equal_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 105: upper_bound_of(left) == upper_bound_of(right)
  frame->slots[6] /* temp__5 */ = create_closure(entry__types__value_range__equal_7, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_11;
}
static void entry__types__value_range__equal_7(void) {
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
  // 105: upper_bound_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_8;
}
static void cont__types__value_range__equal_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 105: ... upper_bound_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_9;
}
static void cont__types__value_range__equal_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 105: upper_bound_of(left) == upper_bound_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__value_range__equal_10;
}
static void cont__types__value_range__equal_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 105: upper_bound_of(left) == upper_bound_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__value_range__equal_11(void) {
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
static void cont__types__value_range__equal_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 101: ->
  // 102:   &&
  // 103:     right.is_a_value_range
  // 104:     lower_bound_of(left) == lower_bound_of(right)
  // 105:     upper_bound_of(left) == upper_bound_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__value_range__contains_1(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // item: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 119: ... lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__contains_2;
}
static void cont__types__value_range__contains_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 119: ... item >= lower_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__value_range__contains_3;
}
static void cont__types__value_range__contains_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 119: ... item >= lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__value_range__contains_4;
}
static void cont__types__value_range__contains_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 119: ... item <= upper_bound_of(self)
  frame->slots[6] /* temp__5 */ = create_closure(entry__types__value_range__contains_5, 0);
  // 119: ... item >= lower_bound_of(self) && item <= upper_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__value_range__contains_9;
}
static void entry__types__value_range__contains_5(void) {
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
  // 119: ... upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__contains_6;
}
static void cont__types__value_range__contains_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 119: ... item <= upper_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* item */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__value_range__contains_7;
}
static void cont__types__value_range__contains_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 119: ... item <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__value_range__contains_8;
}
static void cont__types__value_range__contains_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 119: ... item <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__value_range__contains_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 119: -> item >= lower_bound_of(self) && item <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__value_range__for_each_4(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // body: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 134: body item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__value_range__for_each_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 133: ... lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__for_each_2;
}
static void cont__types__value_range__for_each_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 133: ... upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__for_each_3;
}
static void cont__types__value_range__for_each_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 133: ... : (item)
  // 134:   body item
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__value_range__for_each_4, 1);
  // 133: from_to lower_bound_of(self) upper_bound_of(self): (item)
  // 134:   body item
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__from_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__value_range__serialize_1(void) {
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
  // 145: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_2;
}
static void cont__types__value_range__serialize_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 145: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_3;
}
static void cont__types__value_range__serialize_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 145: ... lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_4;
}
static void cont__types__value_range__serialize_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 145: ... serialize(lower_bound_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_5;
}
static void cont__types__value_range__serialize_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 145: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_6;
}
static void cont__types__value_range__serialize_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 146: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_7;
}
static void cont__types__value_range__serialize_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 146: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_8;
}
static void cont__types__value_range__serialize_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 146: ... upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_9;
}
static void cont__types__value_range__serialize_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__10 */ = arguments->slots[0];
  // 146: ... serialize(upper_bound_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__10 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_10;
}
static void cont__types__value_range__serialize_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 146: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_11;
}
static void cont__types__value_range__serialize_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__11 */ = arguments->slots[0];
  // 143: ... "
  // 144:   value_range
  // 145:   @(spaces(indent+2))@(serialize(lower_bound_of(self)))@(indent+2)@
  // 146:   @nl;@(spaces(indent+2))@(serialize(upper_bound_of(self)))@(indent+2)
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__d62119844f001643;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = frame->slots[7] /* temp__6 */;
  arguments->slots[4] = string__578a5af303e9ceb;
  arguments->slots[5] = frame->slots[8] /* temp__7 */;
  arguments->slots[6] = frame->slots[10] /* temp__9 */;
  arguments->slots[7] = frame->slots[12] /* temp__11 */;
  arguments->slots[8] = string__578a5af303e9ceb;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__types__value_range__serialize_14;
}
static void cont__types__value_range__serialize_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 143: -> "
  // 144:   value_range
  // 145:   @(spaces(indent+2))@(serialize(lower_bound_of(self)))@(indent+2)@
  // 146:   @nl;@(spaces(indent+2))@(serialize(upper_bound_of(self)))@(indent+2)
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
  number__0 = from_uint32(0U);
  number__2 = from_uint32(2U);
  func__std__value_range_1 = create_function(entry__std__value_range_1, 2);
  func__types__value_range__lower_bound_of_1 = create_function(entry__types__value_range__lower_bound_of_1, 1);
  func__types__value_range__upper_bound_of_1 = create_function(entry__types__value_range__upper_bound_of_1, 1);
  func__types__value_range__equal_1 = create_function(entry__types__value_range__equal_1, 2);
  func__types__value_range__contains_1 = create_function(entry__types__value_range__contains_1, 2);
  func__types__value_range__for_each_1 = create_function(entry__types__value_range__for_each_1, 2);
  string__d62119844f001643 = from_latin_1_string("value_range\012", 12);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  func__types__value_range__serialize_1 = create_function(entry__types__value_range__serialize_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__value_range(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__value_range");
  set_used_namespaces(used_namespaces);
  var.types__value_range = create_future_with_prototype(create__types__value_range(NULL, NULL));
  define_single_assign_static("types", "value_range", get__types__value_range, &var.types__value_range);
  define_single_assign_static("std", "value_range", get__std__value_range, &var.std__value_range);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__value_range(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__value_range");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "contains", &get__contains, &poly_idx__contains);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
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
  define_method("types", "value_range", poly_idx__lower_bound_of, func__types__value_range__lower_bound_of_1);
  define_method("types", "value_range", poly_idx__upper_bound_of, func__types__value_range__upper_bound_of_1);
  define_method("types", "value_range", poly_idx__equal, func__types__value_range__equal_1);
  define_method("types", "value_range", poly_idx__contains, func__types__value_range__contains_1);
  define_method("types", "value_range", poly_idx__for_each, func__types__value_range__for_each_1);
  define_method("types", "value_range", poly_idx__serialize, func__types__value_range__serialize_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__value_range(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_value_range, create_function(type__std__is_a_value_range, -1));
  assign_value(&var.types__value_range, get__types__object());
  assign_variable(&var.std__value_range, &func__std__value_range_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__value_range(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__value_range);
}
