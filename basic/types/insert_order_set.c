#include <runtime/platform.h>

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
typedef __INT8_TYPE__ int8_t;
typedef __INT16_TYPE__ int16_t;
typedef __INT32_TYPE__ int32_t;
typedef __INT64_TYPE__ int64_t;
typedef __INTPTR_TYPE__ intptr_t;

#ifdef __UINT8_TYPE__
  typedef __UINT8_TYPE__ uint8_t;
#else
  typedef unsigned __INT8_TYPE__ uint8_t;
#endif

#ifdef __UINT16_TYPE__
  typedef __UINT16_TYPE__ uint16_t;
#else
  typedef unsigned __INT16_TYPE__ uint16_t;
#endif

#ifdef __UINT32_TYPE__
  typedef __UINT32_TYPE__ uint32_t;
#else
  typedef unsigned __INT32_TYPE__ uint32_t;
#endif

#ifdef __UINT64_TYPE__
  typedef __UINT64_TYPE__ uint64_t;
#else
  typedef unsigned __INT64_TYPE__ uint64_t;
#endif

#ifdef __UINTPTR_TYPE__
  typedef __UINTPTR_TYPE__ uintptr_t;
#else
  typedef unsigned __INTPTR_TYPE__ uintptr_t;
#endif
typedef __SIZE_TYPE__ size_t;
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
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *undefined;
IMPORT NODE *create_future(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void allocate_arguments(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void define_type_function(
  const char *namespace, const char *name, FUNC type, int par_cnt
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
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
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__delete_at;
static NODE_GETTER get_value_or_future__delete_at;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__first_index_of;
static NODE_GETTER get__first_index_of;
static int poly_idx__for_each;
static NODE_GETTER get__for_each;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__is_an_insert_order_set;
static NODE_GETTER get__is_an_insert_order_set;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static int poly_idx__is_empty;
static NODE_GETTER get__is_empty;
static int poly_idx__last_index_of;
static NODE_GETTER get__last_index_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static int poly_idx__serialization_tag_of;
static NODE_GETTER get__serialization_tag_of;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__generic_set;
static NODE_GETTER get_value_or_future__types__generic_set;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static struct {
  NODE *_NONE;
  NODE *_index_table_of;
  NODE *_keys_of;
  NODE *std__is_an_insert_order_set;
  NODE *types__insert_order_set;
  NODE *std__empty_insert_order_set;
  NODE *std__insert_order_set;
} var;
static const char *var_names[] = {
  "NONE",
  "index_table_of",
  "keys_of"
};
static int poly_idx__std__is_an_insert_order_set;
static void type__std__is_an_insert_order_set(void);
static NODE *get__std__is_an_insert_order_set(void) {
  return var.std__is_an_insert_order_set;
}
static NODE *unique__NONE;
static int poly_idx__index_table_of;
static void type__index_table_of(void);
static int poly_idx__keys_of;
static void type__keys_of(void);
static NODE *get__types__insert_order_set(void) {
  return var.types__insert_order_set;
}
static NODE *func__10_1_types__insert_order_set_;
static void entry__10_1_types__insert_order_set_(void);
static FRAME_INFO frame__10_1_types__insert_order_set_ = {4, {"key", "value", "myself", "idx"}};
static void cont__10_2(void);
static void cont__10_3(void);
static NODE *func__10_4;
static void entry__10_4(void);
static FRAME_INFO frame__10_4 = {1, {"idx"}};
static void cont__10_5(void);
static NODE *func__10_6;
static void entry__10_6(void);
static FRAME_INFO frame__10_6 = {3, {"idx", "myself", "key"}};
static void cont__10_7(void);
static NODE *func__10_8;
static void entry__10_8(void);
static FRAME_INFO frame__10_8 = {2, {"myself", "key"}};
static void cont__10_9(void);
static void cont__10_10(void);
static void cont__10_11(void);
static void cont__10_12(void);
static void cont__10_13(void);
static void cont__10_14(void);
static void cont__10_15(void);
static NODE *func__10_16;
static void entry__10_16(void);
static FRAME_INFO frame__10_16 = {3, {"idx", "myself", "key"}};
static void cont__10_17(void);
static NODE *func__10_18;
static void entry__10_18(void);
static FRAME_INFO frame__10_18 = {3, {"myself", "idx", "key"}};
static void cont__10_19(void);
static void cont__10_20(void);
static void cont__10_21(void);
static void cont__10_22(void);
static void cont__10_23(void);
static NODE *func__10_24;
static void entry__10_24(void);
static FRAME_INFO frame__10_24 = {0, {}};
static NODE *string__3cace614246a32e7;
static NODE *string__60153133ec65829c;
static NODE *func__12_1_types__insert_order_set_is_empty;
static void entry__12_1_types__insert_order_set_is_empty(void);
static FRAME_INFO frame__12_1_types__insert_order_set_is_empty = {1, {"self"}};
static void cont__12_2(void);
static void cont__12_3(void);
static NODE *func__13_1_types__insert_order_set_first_index_of;
static void entry__13_1_types__insert_order_set_first_index_of(void);
static FRAME_INFO frame__13_1_types__insert_order_set_first_index_of = {1, {"self"}};
static void cont__13_2(void);
static NODE *func__13_3;
static void entry__13_3(void);
static FRAME_INFO frame__13_3 = {1, {"self"}};
static void cont__13_4(void);
static void cont__13_5(void);
static NODE *func__13_6;
static void entry__13_6(void);
static FRAME_INFO frame__13_6 = {0, {}};
static NODE *func__14_1_types__insert_order_set_last_index_of;
static void entry__14_1_types__insert_order_set_last_index_of(void);
static FRAME_INFO frame__14_1_types__insert_order_set_last_index_of = {1, {"self"}};
static void cont__14_2(void);
static NODE *func__14_3;
static void entry__14_3(void);
static FRAME_INFO frame__14_3 = {1, {"self"}};
static void cont__14_4(void);
static void cont__14_5(void);
static void cont__14_6(void);
static NODE *func__14_7;
static void entry__14_7(void);
static FRAME_INFO frame__14_7 = {0, {}};
static NODE *func__15_1_types__insert_order_set_for_each;
static void entry__15_1_types__insert_order_set_for_each(void);
static FRAME_INFO frame__15_1_types__insert_order_set_for_each = {2, {"self", "body"}};
static void cont__15_2(void);
static NODE *func__15_3;
static void entry__15_3(void);
static FRAME_INFO frame__15_3 = {3, {"idx", "value", "body"}};
static void cont__15_4(void);
static void cont__15_5(void);
static NODE *func__15_6;
static void entry__15_6(void);
static FRAME_INFO frame__15_6 = {3, {"body", "idx", "value"}};
static NODE *func__15_7;
static void entry__15_7(void);
static FRAME_INFO frame__15_7 = {2, {"body", "value"}};
static NODE *get__std__empty_insert_order_set(void) {
  return var.std__empty_insert_order_set;
}
static NODE *func__17_1_std__insert_order_set;
static void entry__17_1_std__insert_order_set(void);
static FRAME_INFO frame__17_1_std__insert_order_set = {2, {"args", "tab"}};
static NODE *func__17_2;
static void entry__17_2(void);
static FRAME_INFO frame__17_2 = {2, {"key", "tab"}};
static void cont__17_3(void);
static void cont__17_4(void);
static NODE *get__std__insert_order_set(void) {
  return var.std__insert_order_set;
}
void run__basic__types__insert_order_set(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_an_insert_order_set, NULL, 23, 23, 2, 28},
  {type__index_table_of, NULL, 30, 30, 2, 15},
  {type__keys_of, NULL, 31, 31, 2, 8},
  {run__basic__types__insert_order_set, NULL, 38, 38, 1, 43},
  {entry__10_4, NULL, 54, 54, 8, 21},
  {cont__10_5, &frame__10_4, 54, 54, 5, 21},
  {entry__10_8, NULL, 57, 57, 15, 28},
  {cont__10_9, &frame__10_8, 57, 57, 9, 32},
  {cont__10_10, &frame__10_8, 58, 58, 47, 61},
  {cont__10_11, &frame__10_8, 58, 58, 9, 62},
  {cont__10_12, &frame__10_8, 58, 58, 10, 30},
  {cont__10_13, &frame__10_8, 58, 58, 9, 35},
  {cont__10_14, &frame__10_8, 58, 58, 62, 62},
  {entry__10_6, NULL, 56, 56, 14, 27},
  {cont__10_7, &frame__10_6, 56, 58, 7, 62},
  {cont__10_15, &frame__10_6, 59, 59, 7, 15},
  {entry__10_18, NULL, 62, 62, 20, 33},
  {cont__10_19, &frame__10_18, 62, 62, 9, 37},
  {cont__10_20, &frame__10_18, 63, 63, 10, 30},
  {cont__10_21, &frame__10_18, 63, 63, 9, 35},
  {cont__10_22, &frame__10_18, 63, 63, 45, 45},
  {entry__10_16, NULL, 61, 61, 10, 23},
  {cont__10_17, &frame__10_16, 61, 63, 7, 45},
  {cont__10_23, &frame__10_16, 64, 64, 7, 15},
  {entry__10_24, NULL, 66, 66, 7, 65},
  {entry__10_1_types__insert_order_set_, NULL, 50, 50, 8, 29},
  {cont__10_2, &frame__10_1_types__insert_order_set_, 50, 50, 3, 34},
  {cont__10_3, &frame__10_1_types__insert_order_set_, 51, 66, 3, 66},
  {entry__12_1_types__insert_order_set_is_empty, NULL, 77, 77, 6, 18},
  {cont__12_2, &frame__12_1_types__insert_order_set_is_empty, 77, 77, 6, 27},
  {cont__12_3, &frame__12_1_types__insert_order_set_is_empty, 77, 77, 3, 27},
  {entry__13_3, NULL, 85, 85, 38, 50},
  {cont__13_4, &frame__13_3, 85, 85, 38, 53},
  {cont__13_5, &frame__13_3, 85, 85, 35, 53},
  {entry__13_6, NULL, 85, 85, 21, 32},
  {entry__13_1_types__insert_order_set_first_index_of, NULL, 85, 85, 6, 18},
  {cont__13_2, &frame__13_1_types__insert_order_set_first_index_of, 85, 85, 3, 53},
  {entry__14_3, NULL, 93, 93, 53, 53},
  {cont__14_4, &frame__14_3, 93, 93, 38, 50},
  {cont__14_5, &frame__14_3, 93, 93, 38, 54},
  {cont__14_6, &frame__14_3, 93, 93, 35, 54},
  {entry__14_7, NULL, 93, 93, 21, 32},
  {entry__14_1_types__insert_order_set_last_index_of, NULL, 93, 93, 6, 18},
  {cont__14_2, &frame__14_1_types__insert_order_set_last_index_of, 93, 93, 3, 54},
  {entry__15_6, NULL, 105, 105, 9, 22},
  {entry__15_7, NULL, 107, 107, 9, 18},
  {entry__15_3, NULL, 104, 104, 7, 30},
  {cont__15_4, &frame__15_3, 104, 104, 7, 35},
  {cont__15_5, &frame__15_3, 103, 107, 5, 19},
  {entry__15_1_types__insert_order_set_for_each, NULL, 102, 102, 12, 24},
  {cont__15_2, &frame__15_1_types__insert_order_set_for_each, 102, 107, 3, 20},
  {entry__17_2, NULL, 120, 120, 24, 32},
  {cont__17_3, &frame__17_2, 120, 120, 37, 37},
  {entry__17_1_std__insert_order_set, NULL, 120, 120, 3, 37},
  {cont__17_4, &frame__17_1_std__insert_order_set, 121, 121, 3, 8}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__std__is_an_insert_order_set(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_an_insert_order_set);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_an_insert_order_set, attr);
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
static void type__index_table_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__index_table_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__index_table_of, attr);
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
static void type__keys_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__keys_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__keys_of, attr);
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
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__insert_order_set",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/insert_order_set.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__insert_order_set(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 38: $types::insert_order_set types::generic_set
  initialize_maybe_future(var.types__insert_order_set, get__types__generic_set());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 54: ... idx.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 54: -> idx.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // idx: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[1] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: ... idx.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_7;
}
static void cont__10_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 56: ... :
  // 57:   push &myself.keys_of key
  // 58:   !myself.index_table_of(key) length_of(keys_of(myself))
  frame->slots[4] /* temp__2 */ = create_closure(entry__10_8, 0);
  // 56: unless idx.is_defined:
  // 57:   push &myself.keys_of key
  // 58:   !myself.index_table_of(key) length_of(keys_of(myself))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__10_15;
}
static void entry__10_8(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // myself: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[2]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 57: ... myself.keys_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._keys_of;
  func = myself->type;
  frame->cont = cont__10_9;
}
static void cont__10_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 57: push &myself.keys_of key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__10_10;
}
static void cont__10_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 57: ... &myself.keys_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__keys_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 58: ... keys_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._keys_of;
  func = myself->type;
  frame->cont = cont__10_11;
}
static void cont__10_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 58: !myself.index_table_of(key) length_of(keys_of(myself))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__10_12;
}
static void cont__10_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 58: ... myself.index_table_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._index_table_of;
  func = myself->type;
  frame->cont = cont__10_13;
}
static void cont__10_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 58: !myself.index_table_of(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__10_14;
}
static void cont__10_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 58: !myself.index_table_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__index_table_of, frame->slots[4] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 59: -> myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* myself */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_16(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // idx: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[1] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: ... idx.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_17;
}
static void cont__10_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 61: ... :
  // 62:   delete_at &myself.keys_of idx
  // 63:   !myself.index_table_of(key) undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__10_18, 0);
  // 61: if idx.is_defined:
  // 62:   delete_at &myself.keys_of idx
  // 63:   !myself.index_table_of(key) undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_23;
}
static void entry__10_18(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // myself: 0
  // idx: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[2]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 62: ... myself.keys_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._keys_of;
  func = myself->type;
  frame->cont = cont__10_19;
}
static void cont__10_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 62: delete_at &myself.keys_of idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__10_20;
}
static void cont__10_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 62: ... &myself.keys_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__keys_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 63: !myself.index_table_of(key) undefined
  frame->slots[3] /* temp__1 */ = get__undefined();
  // 63: ... myself.index_table_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._index_table_of;
  func = myself->type;
  frame->cont = cont__10_21;
}
static void cont__10_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 63: !myself.index_table_of(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__10_22;
}
static void cont__10_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 63: !myself.index_table_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__index_table_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 64: -> myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* myself */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_24(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 66: Error "Attempt to set a set element to a nonboolean value!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__3cace614246a32e7;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_1_types__insert_order_set_(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // key: 0
  // value: 1
  // myself: 2
  // idx: 3
  frame->slots[3] /* idx */ = create_future();
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
  frame->slots[2] /* myself */ = create_cell_with_contents(myself);
  // 50: ... index_table_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* myself */;
  result_count = 1;
  myself = var._index_table_of;
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 50: $idx index_table_of(myself)(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  result_count = 1;
  myself = frame->slots[4] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__10_3;
}
static void cont__10_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* idx */, arguments->slots[0]);
  // 54: -> idx.is_defined
  frame->slots[4] /* temp__1 */ = create_closure(entry__10_4, 0);
  // 55: ... :
  // 56:   unless idx.is_defined:
  // 57:     push &myself.keys_of key
  // 58:     !myself.index_table_of(key) length_of(keys_of(myself))
  // 59:   -> myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_6, 0);
  // 60: ... :
  // 61:   if idx.is_defined:
  // 62:     delete_at &myself.keys_of idx
  // 63:     !myself.index_table_of(key) undefined
  // 64:   -> myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__10_16, 0);
  // 51: case
  // 52:   value
  // 53:   NONE
  // 54:   -> idx.is_defined
  // 55:   true:
  // 56:     unless idx.is_defined:
  // 57:       push &myself.keys_of key
  // 58:       !myself.index_table_of(key) length_of(keys_of(myself))
  // 59:     -> myself
  // 60:   false:
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = var._NONE;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  arguments->slots[3] = get__true();
  arguments->slots[4] = frame->slots[5] /* temp__2 */;
  arguments->slots[5] = get__false();
  arguments->slots[6] = frame->slots[6] /* temp__3 */;
  arguments->slots[7] = func__10_24;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_1_types__insert_order_set_is_empty(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 77: ... keys_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._keys_of;
  func = myself->type;
  frame->cont = cont__12_2;
}
static void cont__12_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 77: ... keys_of(self).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 77: -> keys_of(self).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_3(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 85: ... keys_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._keys_of;
  func = myself->type;
  frame->cont = cont__13_4;
}
static void cont__13_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 85: ... keys_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__13_5;
}
static void cont__13_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 85: ... -> keys_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 85: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_1_types__insert_order_set_first_index_of(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 85: ... self.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__13_2;
}
static void cont__13_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 85: ... -> keys_of(self)(1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__13_3, 0);
  // 85: if self.is_empty (-> undefined) -> keys_of(self)(1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__13_6;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__14_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 93: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__14_4;
}
static void cont__14_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 93: ... keys_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._keys_of;
  func = myself->type;
  frame->cont = cont__14_5;
}
static void cont__14_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 93: ... keys_of(self)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__14_6;
}
static void cont__14_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 93: ... -> keys_of(self)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 93: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_1_types__insert_order_set_last_index_of(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 93: ... self.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__14_2;
}
static void cont__14_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 93: ... -> keys_of(self)(-1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__14_3, 0);
  // 93: if self.is_empty (-> undefined) -> keys_of(self)(-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__14_7;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_6(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // body: 0
  // idx: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: body idx value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[2] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_7(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // value: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 107: body value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_3(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // idx: 0
  // value: 1
  // body: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 104: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__15_4;
}
static void cont__15_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 104: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__15_5;
}
static void cont__15_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 104: ... :
  // 105:   body idx value
  frame->slots[5] /* temp__3 */ = create_closure(entry__15_6, 0);
  // 106: :
  // 107:   body value
  frame->slots[6] /* temp__4 */ = create_closure(entry__15_7, 0);
  // 103: if
  // 104:   parameter_count_of(body) == 2:
  // 105:     body idx value
  // 106:   :
  // 107:     body value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_1_types__insert_order_set_for_each(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 102: ... keys_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._keys_of;
  func = myself->type;
  frame->cont = cont__15_2;
}
static void cont__15_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 102: ... : (idx value)
  // 103:   if
  // 104:     parameter_count_of(body) == 2:
  // 105:       body idx value
  // 106:     :
  // 107:       body value
  frame->slots[3] /* temp__2 */ = create_closure(entry__15_3, 2);
  // 102: for_each keys_of(self): (idx value)
  // 103:   if
  // 104:     parameter_count_of(body) == 2:
  // 105:       body idx value
  // 106:     :
  // 107:       body value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__17_1_std__insert_order_set(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  // tab: 1
  frame->slots[1] /* tab */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 119: $$tab types::insert_order_set
  ((CELL *)frame->slots[1])->contents /* tab */ = var.types__insert_order_set;
  // 120: ... : (key) !tab(key) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__17_2, 1);
  // 120: for_each args: (key) !tab(key) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__17_4;
}
static void entry__17_2(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // key: 0
  // tab: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* tab */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 120: ... !tab(key) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 120: ... !tab(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* tab */;
  func = myself->type;
  frame->cont = cont__17_3;
}
static void cont__17_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* tab */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 121: -> tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* tab */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__insert_order_set(void) {
  var.std__is_an_insert_order_set = collect_node(var.std__is_an_insert_order_set);
  var._NONE = collect_node(var._NONE);
  var._index_table_of = collect_node(var._index_table_of);
  var._keys_of = collect_node(var._keys_of);
  var.types__insert_order_set = collect_node(var.types__insert_order_set);
  var.std__empty_insert_order_set = collect_node(var.std__empty_insert_order_set);
  var.std__insert_order_set = collect_node(var.std__insert_order_set);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__insert_order_set(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_an_insert_order_set", get__std__is_an_insert_order_set, &poly_idx__std__is_an_insert_order_set, &var.std__is_an_insert_order_set);
  register_polymorphic_function_with_setter("_basic__types__insert_order_set::index_table_of", &poly_idx__index_table_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_set::keys_of", &poly_idx__keys_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__insert_order_set(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  unique__NONE = register_unique_item("NONE");
  string__3cace614246a32e7 = from_latin_1_string("Attempt to set a set element to a nonboolean value!", 51);
  func__10_24 = create_function(entry__10_24, 0);
  string__60153133ec65829c = from_latin_1_string("insert_order_set", 16);
  func__12_1_types__insert_order_set_is_empty = create_function(entry__12_1_types__insert_order_set_is_empty, 1);
  func__13_6 = create_function(entry__13_6, 0);
  func__13_1_types__insert_order_set_first_index_of = create_function(entry__13_1_types__insert_order_set_first_index_of, 1);
  func__14_7 = create_function(entry__14_7, 0);
  func__14_1_types__insert_order_set_last_index_of = create_function(entry__14_1_types__insert_order_set_last_index_of, 1);
  func__15_1_types__insert_order_set_for_each = create_function(entry__15_1_types__insert_order_set_for_each, 2);
  func__17_1_std__insert_order_set = create_function(entry__17_1_std__insert_order_set, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__insert_order_set(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__insert_order_set");
  set_used_namespaces(used_namespaces);
  assign_value(&var._NONE, unique__NONE);
  define_single_assign_static("types", "insert_order_set", get__types__insert_order_set, &var.types__insert_order_set);
  define_single_assign_static("std", "empty_insert_order_set", get__std__empty_insert_order_set, &var.std__empty_insert_order_set);
  define_single_assign_static("std", "insert_order_set", get__std__insert_order_set, &var.std__insert_order_set);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__insert_order_set(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__insert_order_set");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "delete_at", &get__delete_at, &get_value_or_future__delete_at);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "first_index_of", &get__first_index_of, &poly_idx__first_index_of);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "is_an_insert_order_set", &get__is_an_insert_order_set, &poly_idx__is_an_insert_order_set);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_polymorphic_function(NULL, "is_empty", &get__is_empty, &poly_idx__is_empty);
  use_polymorphic_function(NULL, "last_index_of", &get__last_index_of, &poly_idx__last_index_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "generic_set", &get__types__generic_set, &get_value_or_future__types__generic_set);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  define_attribute("types", "object", poly_idx__is_an_insert_order_set, get__false());
  define_attribute("types", "insert_order_set", poly_idx__is_an_insert_order_set, get__true());
  define_attribute("types", "insert_order_set", poly_idx__index_table_of, get__empty_table());
  define_attribute("types", "insert_order_set", poly_idx__keys_of, get__empty_list());
  define_type_function("types", "insert_order_set", entry__10_1_types__insert_order_set_, -1);
  define_attribute("types", "insert_order_set", poly_idx__serialization_tag_of, string__60153133ec65829c);
  define_method("types", "insert_order_set", poly_idx__is_empty, func__12_1_types__insert_order_set_is_empty);
  define_method("types", "insert_order_set", poly_idx__first_index_of, func__13_1_types__insert_order_set_first_index_of);
  define_method("types", "insert_order_set", poly_idx__last_index_of, func__14_1_types__insert_order_set_last_index_of);
  define_method("types", "insert_order_set", poly_idx__for_each, func__15_1_types__insert_order_set_for_each);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__insert_order_set(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_an_insert_order_set, create_function(type__std__is_an_insert_order_set, -1));
  assign_value(&var._index_table_of, create_function(type__index_table_of, -1));
  assign_value(&var._keys_of, create_function(type__keys_of, -1));
  assign_value(&var.types__insert_order_set, get__types__generic_set());
  assign_variable(&var.std__empty_insert_order_set, &var.types__insert_order_set);
  assign_variable(&var.std__insert_order_set, &func__17_1_std__insert_order_set);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__insert_order_set(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__insert_order_set);
}
