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
IMPORT NODE *create_continuation_with_exit(FUNC exit_func);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void continuation_type_function(void);
IMPORT NODE *create_continuation(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
IMPORT NODE *undefined;
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void def_attribute(NODE **var_p, int idx, void *attr);
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
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__dec;
static NODE_GETTER get_value_or_future__dec;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__for_each;
static NODE_GETTER get__for_each;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static int poly_idx__is_a_key_order_set;
static NODE_GETTER get__is_a_key_order_set;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static int poly_idx__key_of;
static NODE_GETTER get__key_of;
static int poly_idx__length_of;
static NODE_GETTER get__length_of;
static int poly_idx__serialization_tag_of;
static NODE_GETTER get__serialization_tag_of;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__generic_set;
static NODE_GETTER get_value_or_future__types__generic_set;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static struct {
  NODE *_NONE;
  NODE *_tree_of;
  NODE *_left_of;
  NODE *_right_of;
  NODE *_empty_node;
  NODE *_fetch_first;
  NODE *_get_item;
  NODE *_add_item;
  NODE *_remove_item;
  NODE *_for_each_item;
  NODE *std__is_a_key_order_set;
  NODE *types__key_order_set;
  NODE *std__empty_key_order_set;
  NODE *std__key_order_set;
} var;
static const char *var_names[] = {
  "NONE",
  "tree_of",
  "left_of",
  "right_of",
  "empty_node",
  "fetch_first",
  "get_item",
  "add_item",
  "remove_item",
  "for_each_item"
};
static int poly_idx__std__is_a_key_order_set;
static void type__std__is_a_key_order_set(void);
static NODE *get__std__is_a_key_order_set(void) {
  return var.std__is_a_key_order_set;
}
static NODE *unique__NONE;
static int poly_idx__tree_of;
static void type__tree_of(void);
static int poly_idx__left_of;
static void type__left_of(void);
static int poly_idx__right_of;
static void type__right_of(void);
static NODE *get__types__key_order_set(void) {
  return var.types__key_order_set;
}
static NODE *func__12_1_fetch_first;
static void entry__12_1_fetch_first(void);
static FRAME_INFO frame__12_1_fetch_first = {3, {"myself", "return", "left"}};
static void exit__12_1_fetch_first(void);
static void cont__12_2(void);
static void cont__12_3(void);
static NODE *func__12_4;
static void entry__12_4(void);
static FRAME_INFO frame__12_4 = {4, {"left", "myself", "return", "key"}};
static void cont__12_5(void);
static NODE *func__12_6;
static void entry__12_6(void);
static FRAME_INFO frame__12_6 = {3, {"myself", "return", "key"}};
static void cont__12_7(void);
static void cont__12_8(void);
static void cont__12_9(void);
static NODE *func__13_1_get_item;
static void entry__13_1_get_item(void);
static FRAME_INFO frame__13_1_get_item = {4, {"myself", "key", "return", "my_key"}};
static void cont__13_2(void);
static NODE *func__13_3;
static void entry__13_3(void);
static FRAME_INFO frame__13_3 = {1, {"return"}};
static void cont__13_4(void);
static void cont__13_5(void);
static NODE *func__13_6;
static void entry__13_6(void);
static FRAME_INFO frame__13_6 = {3, {"key", "my_key", "return"}};
static void cont__13_7(void);
static NODE *func__13_8;
static void entry__13_8(void);
static FRAME_INFO frame__13_8 = {1, {"return"}};
static NODE *func__13_9;
static void entry__13_9(void);
static FRAME_INFO frame__13_9 = {4, {"key", "my_key", "return", "myself"}};
static void cont__13_10(void);
static NODE *func__13_11;
static void entry__13_11(void);
static FRAME_INFO frame__13_11 = {3, {"return", "myself", "key"}};
static void cont__13_12(void);
static void cont__13_13(void);
static NODE *func__13_14;
static void entry__13_14(void);
static FRAME_INFO frame__13_14 = {4, {"my_key", "key", "return", "myself"}};
static void cont__13_15(void);
static NODE *func__13_16;
static void entry__13_16(void);
static FRAME_INFO frame__13_16 = {3, {"return", "myself", "key"}};
static void cont__13_17(void);
static void cont__13_18(void);
static void cont__13_19(void);
static NODE *func__14_1_add_item;
static void entry__14_1_add_item(void);
static FRAME_INFO frame__14_1_add_item = {4, {"myself", "key", "return", "my_key"}};
static void cont__14_2(void);
static NODE *func__14_3;
static void entry__14_3(void);
static FRAME_INFO frame__14_3 = {2, {"return", "key"}};
static void cont__14_4(void);
static void cont__14_5(void);
static NODE *func__14_6;
static void entry__14_6(void);
static FRAME_INFO frame__14_6 = {3, {"key", "my_key", "return"}};
static void cont__14_7(void);
static NODE *func__14_8;
static void entry__14_8(void);
static FRAME_INFO frame__14_8 = {1, {"return"}};
static NODE *func__14_9;
static void entry__14_9(void);
static FRAME_INFO frame__14_9 = {4, {"key", "my_key", "myself", "return"}};
static void cont__14_10(void);
static NODE *func__14_11;
static void entry__14_11(void);
static FRAME_INFO frame__14_11 = {4, {"myself", "key", "return", "left"}};
static void cont__14_12(void);
static void cont__14_13(void);
static void cont__14_14(void);
static NODE *func__14_15;
static void entry__14_15(void);
static FRAME_INFO frame__14_15 = {1, {"return"}};
static void cont__14_16(void);
static NODE *func__14_17;
static void entry__14_17(void);
static FRAME_INFO frame__14_17 = {4, {"my_key", "key", "myself", "return"}};
static void cont__14_18(void);
static NODE *func__14_19;
static void entry__14_19(void);
static FRAME_INFO frame__14_19 = {4, {"myself", "key", "return", "right"}};
static void cont__14_20(void);
static void cont__14_21(void);
static void cont__14_22(void);
static NODE *func__14_23;
static void entry__14_23(void);
static FRAME_INFO frame__14_23 = {1, {"return"}};
static void cont__14_24(void);
static void cont__14_25(void);
static NODE *func__15_1_remove_item;
static void entry__15_1_remove_item(void);
static FRAME_INFO frame__15_1_remove_item = {4, {"myself", "key", "return", "my_key"}};
static void cont__15_2(void);
static NODE *func__15_3;
static void entry__15_3(void);
static FRAME_INFO frame__15_3 = {1, {"return"}};
static void cont__15_4(void);
static void cont__15_5(void);
static NODE *func__15_6;
static void entry__15_6(void);
static FRAME_INFO frame__15_6 = {4, {"key", "my_key", "myself", "return"}};
static void cont__15_7(void);
static NODE *func__15_8;
static void entry__15_8(void);
static FRAME_INFO frame__15_8 = {4, {"myself", "return", "left", "right"}};
static void cont__15_9(void);
static void cont__15_10(void);
static void cont__15_11(void);
static NODE *func__15_12;
static void entry__15_12(void);
static FRAME_INFO frame__15_12 = {3, {"right", "return", "left"}};
static void cont__15_13(void);
static NODE *func__15_14;
static void entry__15_14(void);
static FRAME_INFO frame__15_14 = {4, {"right", "return", "left", "head"}};
static void cont__15_15(void);
static NODE *func__15_16;
static void entry__15_16(void);
static FRAME_INFO frame__15_16 = {2, {"return", "left"}};
static NODE *func__15_17;
static void entry__15_17(void);
static FRAME_INFO frame__15_17 = {2, {"return", "right"}};
static NODE *func__15_18;
static void entry__15_18(void);
static FRAME_INFO frame__15_18 = {4, {"key", "my_key", "myself", "return"}};
static void cont__15_19(void);
static NODE *func__15_20;
static void entry__15_20(void);
static FRAME_INFO frame__15_20 = {4, {"myself", "key", "return", "left"}};
static void cont__15_21(void);
static void cont__15_22(void);
static void cont__15_23(void);
static NODE *func__15_24;
static void entry__15_24(void);
static FRAME_INFO frame__15_24 = {1, {"return"}};
static void cont__15_25(void);
static NODE *func__15_26;
static void entry__15_26(void);
static FRAME_INFO frame__15_26 = {4, {"my_key", "key", "myself", "return"}};
static void cont__15_27(void);
static NODE *func__15_28;
static void entry__15_28(void);
static FRAME_INFO frame__15_28 = {4, {"myself", "key", "return", "right"}};
static void cont__15_29(void);
static void cont__15_30(void);
static void cont__15_31(void);
static NODE *func__15_32;
static void entry__15_32(void);
static FRAME_INFO frame__15_32 = {1, {"return"}};
static void cont__15_33(void);
static void cont__15_34(void);
static NODE *func__16_1_types__key_order_set_;
static void entry__16_1_types__key_order_set_(void);
static FRAME_INFO frame__16_1_types__key_order_set_ = {4, {"key", "value", "myself", "return"}};
static NODE *func__16_2;
static void entry__16_2(void);
static FRAME_INFO frame__16_2 = {3, {"return", "myself", "key"}};
static void cont__16_3(void);
static void cont__16_4(void);
static NODE *func__16_5;
static void entry__16_5(void);
static FRAME_INFO frame__16_5 = {4, {"myself", "key", "return", "new_tree"}};
static void cont__16_6(void);
static void cont__16_7(void);
static void cont__16_8(void);
static void cont__16_9(void);
static NODE *func__16_10;
static void entry__16_10(void);
static FRAME_INFO frame__16_10 = {2, {"myself", "new_tree"}};
static void cont__16_11(void);
static void cont__16_12(void);
static void cont__16_13(void);
static NODE *func__16_14;
static void entry__16_14(void);
static FRAME_INFO frame__16_14 = {4, {"myself", "key", "return", "new_tree"}};
static void cont__16_15(void);
static void cont__16_16(void);
static void cont__16_17(void);
static void cont__16_18(void);
static NODE *func__16_19;
static void entry__16_19(void);
static FRAME_INFO frame__16_19 = {2, {"myself", "new_tree"}};
static void cont__16_20(void);
static void cont__16_21(void);
static void cont__16_22(void);
static NODE *func__16_23;
static void entry__16_23(void);
static FRAME_INFO frame__16_23 = {0, {}};
static NODE *string__16_24;
static void cont__16_25(void);
static NODE *string__19_1;
static NODE *get__std__empty_key_order_set(void) {
  return var.std__empty_key_order_set;
}
static NODE *func__21_1_std__key_order_set;
static void entry__21_1_std__key_order_set(void);
static FRAME_INFO frame__21_1_std__key_order_set = {0, {}};
static NODE *get__std__key_order_set(void) {
  return var.std__key_order_set;
}
static NODE *func__22_1_for_each_item;
static void entry__22_1_for_each_item(void);
static FRAME_INFO frame__22_1_for_each_item = {2, {"myself", "body"}};
static void cont__22_2(void);
static NODE *func__22_3;
static void entry__22_3(void);
static FRAME_INFO frame__22_3 = {2, {"myself", "body"}};
static void cont__22_4(void);
static void cont__22_5(void);
static void cont__22_6(void);
static void cont__22_7(void);
static void cont__22_8(void);
static NODE *func__23_1_types__key_order_set_for_each;
static void entry__23_1_types__key_order_set_for_each(void);
static FRAME_INFO frame__23_1_types__key_order_set_for_each = {3, {"self", "body", "tree"}};
static void cont__23_2(void);
static void cont__23_3(void);
static NODE *func__23_4;
static void entry__23_4(void);
static FRAME_INFO frame__23_4 = {2, {"tree", "body"}};
void run__basic__types__key_order_set(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_key_order_set, NULL, 23, 23, 2, 24},
  {type__tree_of, NULL, 30, 30, 2, 8},
  {type__left_of, NULL, 31, 31, 2, 8},
  {type__right_of, NULL, 32, 32, 2, 9},
  {run__basic__types__key_order_set, NULL, 40, 40, 1, 25},
  {entry__12_4, NULL, 52, 52, 7, 29},
  {cont__12_5, &frame__12_4, 54, 54, 7, 16},
  {entry__12_6, NULL, 56, 56, 7, 25},
  {cont__12_7, &frame__12_6, 57, 57, 7, 30},
  {cont__12_8, &frame__12_6, 58, 58, 7, 16},
  {entry__12_1_fetch_first, NULL, 49, 49, 3, 24},
  {cont__12_2, &frame__12_1_fetch_first, 51, 51, 5, 19},
  {cont__12_3, &frame__12_1_fetch_first, 50, 58, 3, 17},
  {cont__12_9, &frame__12_1_fetch_first, 58, 58, 17, 17},
  {entry__13_3, NULL, 66, 66, 27, 38},
  {entry__13_8, NULL, 69, 69, 23, 33},
  {entry__13_6, NULL, 69, 69, 8, 20},
  {cont__13_7, &frame__13_6, 69, 69, 5, 33},
  {entry__13_11, NULL, 70, 70, 38, 52},
  {cont__13_12, &frame__13_11, 70, 70, 29, 57},
  {cont__13_13, &frame__13_11, 70, 70, 22, 57},
  {entry__13_9, NULL, 70, 70, 8, 19},
  {cont__13_10, &frame__13_9, 70, 70, 5, 57},
  {entry__13_16, NULL, 71, 71, 38, 53},
  {cont__13_17, &frame__13_16, 71, 71, 29, 58},
  {cont__13_18, &frame__13_16, 71, 71, 22, 58},
  {entry__13_14, NULL, 71, 71, 8, 19},
  {cont__13_15, &frame__13_14, 71, 71, 5, 58},
  {entry__13_1_get_item, NULL, 66, 66, 6, 24},
  {cont__13_2, &frame__13_1_get_item, 66, 66, 3, 38},
  {cont__13_4, &frame__13_1_get_item, 67, 67, 3, 24},
  {cont__13_5, &frame__13_1_get_item, 68, 71, 3, 58},
  {cont__13_19, &frame__13_1_get_item, 71, 71, 58, 58},
  {entry__14_3, NULL, 79, 79, 27, 56},
  {entry__14_8, NULL, 82, 82, 23, 33},
  {entry__14_6, NULL, 82, 82, 8, 20},
  {cont__14_7, &frame__14_6, 82, 82, 5, 33},
  {entry__14_15, NULL, 85, 85, 24, 50},
  {entry__14_11, NULL, 84, 84, 22, 36},
  {cont__14_12, &frame__14_11, 84, 84, 7, 41},
  {cont__14_13, &frame__14_11, 85, 85, 10, 21},
  {cont__14_14, &frame__14_11, 85, 85, 7, 50},
  {cont__14_16, &frame__14_11, 87, 87, 7, 19},
  {entry__14_9, NULL, 83, 83, 8, 19},
  {cont__14_10, &frame__14_9, 83, 87, 5, 19},
  {entry__14_23, NULL, 90, 90, 25, 51},
  {entry__14_19, NULL, 89, 89, 23, 38},
  {cont__14_20, &frame__14_19, 89, 89, 7, 43},
  {cont__14_21, &frame__14_19, 90, 90, 10, 22},
  {cont__14_22, &frame__14_19, 90, 90, 7, 51},
  {cont__14_24, &frame__14_19, 92, 92, 7, 19},
  {entry__14_17, NULL, 88, 88, 8, 19},
  {cont__14_18, &frame__14_17, 88, 92, 5, 19},
  {entry__14_1_add_item, NULL, 79, 79, 6, 24},
  {cont__14_2, &frame__14_1_add_item, 79, 79, 3, 56},
  {cont__14_4, &frame__14_1_add_item, 80, 80, 3, 24},
  {cont__14_5, &frame__14_1_add_item, 81, 92, 3, 20},
  {cont__14_25, &frame__14_1_add_item, 92, 92, 20, 20},
  {entry__15_3, NULL, 100, 100, 27, 55},
  {entry__15_14, NULL, 110, 110, 15, 39},
  {cont__15_15, &frame__15_14, 111, 111, 15, 78},
  {entry__15_16, NULL, 113, 113, 15, 25},
  {entry__15_12, NULL, 109, 109, 13, 28},
  {cont__15_13, &frame__15_12, 108, 113, 11, 26},
  {entry__15_17, NULL, 115, 115, 11, 22},
  {entry__15_8, NULL, 104, 104, 7, 27},
  {cont__15_9, &frame__15_8, 105, 105, 7, 30},
  {cont__15_10, &frame__15_8, 107, 107, 9, 23},
  {cont__15_11, &frame__15_8, 106, 115, 7, 23},
  {entry__15_6, NULL, 103, 103, 8, 20},
  {cont__15_7, &frame__15_6, 103, 115, 5, 24},
  {entry__15_24, NULL, 118, 118, 24, 52},
  {entry__15_20, NULL, 117, 117, 25, 39},
  {cont__15_21, &frame__15_20, 117, 117, 7, 44},
  {cont__15_22, &frame__15_20, 118, 118, 10, 21},
  {cont__15_23, &frame__15_20, 118, 118, 7, 52},
  {cont__15_25, &frame__15_20, 120, 120, 7, 19},
  {entry__15_18, NULL, 116, 116, 8, 19},
  {cont__15_19, &frame__15_18, 116, 120, 5, 19},
  {entry__15_32, NULL, 123, 123, 25, 53},
  {entry__15_28, NULL, 122, 122, 26, 41},
  {cont__15_29, &frame__15_28, 122, 122, 7, 46},
  {cont__15_30, &frame__15_28, 123, 123, 10, 22},
  {cont__15_31, &frame__15_28, 123, 123, 7, 53},
  {cont__15_33, &frame__15_28, 125, 125, 7, 19},
  {entry__15_26, NULL, 121, 121, 8, 19},
  {cont__15_27, &frame__15_26, 121, 125, 5, 19},
  {entry__15_1_remove_item, NULL, 100, 100, 6, 24},
  {cont__15_2, &frame__15_1_remove_item, 100, 100, 3, 55},
  {cont__15_4, &frame__15_1_remove_item, 101, 101, 3, 24},
  {cont__15_5, &frame__15_1_remove_item, 102, 125, 3, 20},
  {cont__15_34, &frame__15_1_remove_item, 125, 125, 20, 20},
  {entry__16_2, NULL, 139, 139, 23, 37},
  {cont__16_3, &frame__16_2, 139, 139, 14, 42},
  {cont__16_4, &frame__16_2, 139, 139, 7, 42},
  {entry__16_10, NULL, 144, 144, 14, 29},
  {cont__16_11, &frame__16_10, 144, 144, 9, 29},
  {cont__16_12, &frame__16_10, 144, 144, 29, 29},
  {entry__16_5, NULL, 141, 141, 26, 40},
  {cont__16_6, &frame__16_5, 141, 141, 7, 45},
  {cont__16_7, &frame__16_5, 142, 142, 10, 25},
  {cont__16_8, &frame__16_5, 142, 142, 10, 25},
  {cont__16_9, &frame__16_5, 142, 144, 7, 29},
  {cont__16_13, &frame__16_5, 145, 145, 7, 19},
  {entry__16_19, NULL, 150, 150, 14, 29},
  {cont__16_20, &frame__16_19, 150, 150, 9, 29},
  {cont__16_21, &frame__16_19, 150, 150, 29, 29},
  {entry__16_14, NULL, 147, 147, 29, 43},
  {cont__16_15, &frame__16_14, 147, 147, 7, 48},
  {cont__16_16, &frame__16_14, 148, 148, 10, 25},
  {cont__16_17, &frame__16_14, 148, 148, 10, 25},
  {cont__16_18, &frame__16_14, 148, 150, 7, 29},
  {cont__16_22, &frame__16_14, 151, 151, 7, 19},
  {entry__16_23, NULL, 153, 153, 7, 65},
  {entry__16_1_types__key_order_set_, NULL, 136, 153, 3, 66},
  {cont__16_25, &frame__16_1_types__key_order_set_, 153, 153, 66, 66},
  {entry__21_1_std__key_order_set, NULL, 160, 162, 21, 37},
  {entry__22_3, NULL, 166, 166, 19, 33},
  {cont__22_4, &frame__22_3, 166, 166, 5, 38},
  {cont__22_5, &frame__22_3, 167, 167, 10, 23},
  {cont__22_6, &frame__22_3, 167, 167, 5, 23},
  {cont__22_7, &frame__22_3, 168, 168, 19, 34},
  {cont__22_8, &frame__22_3, 168, 168, 5, 39},
  {entry__22_1_for_each_item, NULL, 165, 165, 6, 22},
  {cont__22_2, &frame__22_1_for_each_item, 165, 168, 3, 39},
  {entry__23_4, NULL, 178, 178, 23, 45},
  {entry__23_1_types__key_order_set_for_each, NULL, 177, 177, 3, 21},
  {cont__23_2, &frame__23_1_types__key_order_set_for_each, 178, 178, 6, 20},
  {cont__23_3, &frame__23_1_types__key_order_set_for_each, 178, 178, 3, 45}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__std__is_a_key_order_set(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_key_order_set);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_key_order_set, attr);
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
static void type__tree_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__tree_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__tree_of, attr);
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
static void type__left_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__left_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__left_of, attr);
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
static void type__right_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__right_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__right_of, attr);
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

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__key_order_set",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/key_order_set.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__key_order_set(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 34: $types::key_order_set types::generic_set
  initialize_maybe_future(var.types__key_order_set, get__types__generic_set());
  // 40: $empty_node types::object
  initialize_maybe_future(var._empty_node, get__types__object());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_1_fetch_first(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // myself: 0
  // return: 1
  // left: 2
  frame->slots[1] /* return */ = create_continuation_with_exit(exit__12_1_fetch_first);
  frame->slots[2] /* left */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 49: $$left left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__12_2;
}
static void cont__12_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* left */ = arguments->slots[0];
  // 51: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 51: ... :
  // 52:   $key fetch_first(&left)
  // 53:   !myself.left_of left
  // 54:   return key
  frame->slots[4] /* temp__2 */ = create_closure(entry__12_4, 0);
  // 55: :
  // 56:   $key key_of(myself)
  // 57:   !myself right_of(myself)
  // 58:   return key
  frame->slots[5] /* temp__3 */ = create_closure(entry__12_6, 0);
  // 50: if
  // 51:   left.is_defined:
  // 52:     $key fetch_first(&left)
  // 53:     !myself.left_of left
  // 54:     return key
  // 55:   :
  // 56:     $key key_of(myself)
  // 57:     !myself right_of(myself)
  // 58:     return key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_9;
}
static void entry__12_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // left: 0
  // myself: 1
  // return: 2
  // key: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* left */
  frame->slots[1] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[1]; /* return */
  frame->slots[3] /* key */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 52: $key fetch_first(&left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  result_count = 2;
  myself = var._fetch_first;
  func = myself->type;
  frame->cont = cont__12_5;
}
static void cont__12_5(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* left */ = arguments->slots[0];
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 52: ... key
  initialize_future(frame->slots[3] /* key */, frame->slots[4] /* temp__1 */);
  // 53: !myself.left_of left
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* left */;
  // 53: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* myself */ = temp;

  }
  // 54: return key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* key */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // myself: 0
  // return: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* key */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: $key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__12_7;
}
static void cont__12_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* key */, arguments->slots[0]);
  // 57: !myself right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__12_8;
}
static void cont__12_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* myself */ = arguments->slots[0];
  // 58: return key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* key */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__12_9(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__12_1_fetch_first(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  func = continuation_type_function;
}
static void entry__13_1_get_item(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // my_key: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* my_key */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 66: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__13_2;
}
static void cont__13_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 66: ... : return false
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_3, 0);
  // 66: if myself.is_undefined: return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_4;
}
static void entry__13_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 66: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__13_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 67: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__13_5;
}
static void cont__13_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 69: -> key == my_key: return true
  frame->slots[4] /* temp__1 */ = create_closure(entry__13_6, 0);
  // 70: -> key < my_key: return get_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_9, 0);
  // 71: -> key > my_key: return get_item(right_of(myself) key)
  frame->slots[6] /* temp__3 */ = create_closure(entry__13_14, 0);
  // 68: cond
  // 69:   -> key == my_key: return true
  // 70:   -> key < my_key: return get_item(left_of(myself) key)
  // 71:   -> key > my_key: return get_item(right_of(myself) key)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__13_19;
}
static void entry__13_16(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 71: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__13_17;
}
static void cont__13_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 71: ... get_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._get_item;
  func = myself->type;
  frame->cont = cont__13_18;
}
static void cont__13_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 71: ... return get_item(right_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_11(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__13_12;
}
static void cont__13_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 70: ... get_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._get_item;
  func = myself->type;
  frame->cont = cont__13_13;
}
static void cont__13_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 70: ... return get_item(left_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // key: 0
  // my_key: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__13_7;
}
static void cont__13_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 69: ... : return true
  frame->slots[4] /* temp__2 */ = create_closure(entry__13_8, 0);
  // 69: -> key == my_key: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_9(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // return: 2
  // myself: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__13_10;
}
static void cont__13_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 70: ... : return get_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_11, 0);
  // 70: -> key < my_key: return get_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_14(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // my_key: 0
  // key: 1
  // return: 2
  // myself: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 71: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__13_15;
}
static void cont__13_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 71: ... : return get_item(right_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_16, 0);
  // 71: -> key > my_key: return get_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_19(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__14_1_add_item(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // my_key: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* my_key */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 79: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__14_2;
}
static void cont__14_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 79: ... : return empty_node(.key_of key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__14_3, 0);
  // 79: if myself.is_undefined: return empty_node(.key_of key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__14_4;
}
static void entry__14_3(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 79: ... empty_node(.key_of key)
  {
    NODE *temp = clone_object_and_attributes(var._empty_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[1] /* key */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 79: ... return empty_node(.key_of key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__14_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 80: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__14_5;
}
static void cont__14_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 82: -> key == my_key: return NONE
  frame->slots[4] /* temp__1 */ = create_closure(entry__14_6, 0);
  // 83: -> key < my_key:
  // 84:   $left add_item(left_of(myself) key)
  // 85:   if NONE == left: return NONE # nothing added
  // 86:   !myself.left_of left
  // 87:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__14_9, 0);
  // 88: -> key > my_key:
  // 89:   $right add_item(right_of(myself) key)
  // 90:   if NONE == right: return NONE # nothing added
  // 91:   !myself.right_of right
  // 92:   return myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__14_17, 0);
  // 81: cond
  // 82:   -> key == my_key: return NONE
  // 83:   -> key < my_key:
  // 84:     $left add_item(left_of(myself) key)
  // 85:     if NONE == left: return NONE # nothing added
  // 86:     !myself.left_of left
  // 87:     return myself
  // 88:   -> key > my_key:
  // 89:     $right add_item(right_of(myself) key)
  // 90:     if NONE == right: return NONE # nothing added
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__14_25;
}
static void entry__14_19(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // right: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* right */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 89: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__14_20;
}
static void cont__14_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 89: $right add_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__14_21;
}
static void cont__14_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* right */, arguments->slots[0]);
  // 90: ... NONE == right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* right */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__14_22;
}
static void cont__14_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 90: ... : return NONE # nothing added
  frame->slots[5] /* temp__2 */ = create_closure(entry__14_23, 0);
  // 90: if NONE == right: return NONE # nothing added
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__14_24;
}
static void entry__14_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: ... return NONE # nothing added
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__14_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 91: !myself.right_of right
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* right */;
  // 91: !myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 92: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__14_11(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // left: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* left */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 84: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__14_12;
}
static void cont__14_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 84: $left add_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__14_13;
}
static void cont__14_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* left */, arguments->slots[0]);
  // 85: ... NONE == left
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* left */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__14_14;
}
static void cont__14_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 85: ... : return NONE # nothing added
  frame->slots[5] /* temp__2 */ = create_closure(entry__14_15, 0);
  // 85: if NONE == left: return NONE # nothing added
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__14_16;
}
static void entry__14_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 85: ... return NONE # nothing added
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__14_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 86: !myself.left_of left
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* left */;
  // 86: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 87: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__14_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 82: ... return NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__14_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // key: 0
  // my_key: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 82: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__14_7;
}
static void cont__14_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 82: ... : return NONE
  frame->slots[4] /* temp__2 */ = create_closure(entry__14_8, 0);
  // 82: -> key == my_key: return NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_9(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 83: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__14_10;
}
static void cont__14_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 83: ... :
  // 84:   $left add_item(left_of(myself) key)
  // 85:   if NONE == left: return NONE # nothing added
  // 86:   !myself.left_of left
  // 87:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__14_11, 0);
  // 83: -> key < my_key:
  // 84:   $left add_item(left_of(myself) key)
  // 85:   if NONE == left: return NONE # nothing added
  // 86:   !myself.left_of left
  // 87:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_17(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // my_key: 0
  // key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 88: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__14_18;
}
static void cont__14_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 88: ... :
  // 89:   $right add_item(right_of(myself) key)
  // 90:   if NONE == right: return NONE # nothing added
  // 91:   !myself.right_of right
  // 92:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__14_19, 0);
  // 88: -> key > my_key:
  // 89:   $right add_item(right_of(myself) key)
  // 90:   if NONE == right: return NONE # nothing added
  // 91:   !myself.right_of right
  // 92:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__14_25(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__15_1_remove_item(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // my_key: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* my_key */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 100: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__15_2;
}
static void cont__15_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 100: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__15_3, 0);
  // 100: if myself.is_undefined: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__15_4;
}
static void entry__15_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 100: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__15_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 101: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__15_5;
}
static void cont__15_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 103: -> key == my_key:
  // 104:   $left left_of(myself)
  // 105:   $$right right_of(myself)
  // 106:   if
  // 107:     left.is_defined:
  // 108:       if
  // 109:         right.is_defined:
  // 110:           $head fetch_first(&right)
  // 111:           return types::object(.key_of head .left_of left .right_of right)
  // 112:         :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__15_6, 0);
  // 116: -> key < my_key:
  // 117:   $left remove_item(left_of(myself) key)
  // 118:   if NONE == left: return NONE # nothing removed
  // 119:   !myself.left_of left
  // 120:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__15_18, 0);
  // 121: -> key > my_key:
  // 122:   $right remove_item(right_of(myself) key)
  // 123:   if NONE == right: return NONE # nothing removed
  // 124:   !myself.right_of right
  // 125:   return myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__15_26, 0);
  // 102: cond
  // 103:   -> key == my_key:
  // 104:     $left left_of(myself)
  // 105:     $$right right_of(myself)
  // 106:     if
  // 107:       left.is_defined:
  // 108:         if
  // 109:           right.is_defined:
  // 110:             $head fetch_first(&right)
  // 111:             return types::object(.key_of head .left_of left .right_of right)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__15_34;
}
static void entry__15_28(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // right: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* right */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 122: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__15_29;
}
static void cont__15_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 122: $right remove_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__15_30;
}
static void cont__15_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* right */, arguments->slots[0]);
  // 123: ... NONE == right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* right */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__15_31;
}
static void cont__15_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 123: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__15_32, 0);
  // 123: if NONE == right: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__15_33;
}
static void entry__15_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 123: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__15_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 124: !myself.right_of right
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* right */;
  // 124: !myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 125: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_20(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // left: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* left */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__15_21;
}
static void cont__15_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 117: $left remove_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__15_22;
}
static void cont__15_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* left */, arguments->slots[0]);
  // 118: ... NONE == left
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* left */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__15_23;
}
static void cont__15_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 118: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__15_24, 0);
  // 118: if NONE == left: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__15_25;
}
static void entry__15_24(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__15_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 119: !myself.left_of left
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* left */;
  // 119: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 120: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_14(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // right: 0
  // return: 1
  // left: 2
  // head: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  frame->slots[3] /* head */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 110: $head fetch_first(&right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 2;
  myself = var._fetch_first;
  func = myself->type;
  frame->cont = cont__15_15;
}
static void cont__15_15(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 110: ... head
  initialize_future(frame->slots[3] /* head */, frame->slots[4] /* temp__1 */);
  // 111: ... types::object(.key_of head .left_of left .right_of right)
  {
    NODE *temp = clone_object_and_attributes(get__types__object());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[3] /* head */);
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[2] /* left */);
    set_attribute_value(temp->attributes, poly_idx__right_of, ((CELL *)frame->slots[0])->contents /* right */);
    frame->slots[4] /* temp__1 */ = temp;

  }
  // 111: return types::object(.key_of head .left_of left .right_of right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // left: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 113: return left
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* left */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_12(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // right: 0
  // return: 1
  // left: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: right.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__15_13;
}
static void cont__15_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 109: ... :
  // 110:   $head fetch_first(&right)
  // 111:   return types::object(.key_of head .left_of left .right_of right)
  frame->slots[4] /* temp__2 */ = create_closure(entry__15_14, 0);
  // 112: :
  // 113:   return left
  frame->slots[5] /* temp__3 */ = create_closure(entry__15_16, 0);
  // 108: if
  // 109:   right.is_defined:
  // 110:     $head fetch_first(&right)
  // 111:     return types::object(.key_of head .left_of left .right_of right)
  // 112:   :
  // 113:     return left
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
static void entry__15_17(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // right: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: return right
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* right */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_8(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // myself: 0
  // return: 1
  // left: 2
  // right: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] /* left */ = create_future();
  frame->slots[3] /* right */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: $left left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__15_9;
}
static void cont__15_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* left */, arguments->slots[0]);
  // 105: $$right right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__15_10;
}
static void cont__15_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* right */ = arguments->slots[0];
  // 107: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__15_11;
}
static void cont__15_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 107: ... :
  // 108:   if
  // 109:     right.is_defined:
  // 110:       $head fetch_first(&right)
  // 111:       return types::object(.key_of head .left_of left .right_of right)
  // 112:     :
  // 113:       return left
  frame->slots[5] /* temp__2 */ = create_closure(entry__15_12, 0);
  // 114: :
  // 115:   return right
  frame->slots[6] /* temp__3 */ = create_closure(entry__15_17, 0);
  // 106: if
  // 107:   left.is_defined:
  // 108:     if
  // 109:       right.is_defined:
  // 110:         $head fetch_first(&right)
  // 111:         return types::object(.key_of head .left_of left .right_of right)
  // 112:       :
  // 113:         return left
  // 114:   :
  // 115:     return right
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_6(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 103: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__15_7;
}
static void cont__15_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 103: ... :
  // 104:   $left left_of(myself)
  // 105:   $$right right_of(myself)
  // 106:   if
  // 107:     left.is_defined:
  // 108:       if
  // 109:         right.is_defined:
  // 110:           $head fetch_first(&right)
  // 111:           return types::object(.key_of head .left_of left .right_of right)
  // 112:         :
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__15_8, 0);
  // 103: -> key == my_key:
  // 104:   $left left_of(myself)
  // 105:   $$right right_of(myself)
  // 106:   if
  // 107:     left.is_defined:
  // 108:       if
  // 109:         right.is_defined:
  // 110:           $head fetch_first(&right)
  // 111:           return types::object(.key_of head .left_of left .right_of right)
  // 112:         :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_18(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__15_19;
}
static void cont__15_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 116: ... :
  // 117:   $left remove_item(left_of(myself) key)
  // 118:   if NONE == left: return NONE # nothing removed
  // 119:   !myself.left_of left
  // 120:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__15_20, 0);
  // 116: -> key < my_key:
  // 117:   $left remove_item(left_of(myself) key)
  // 118:   if NONE == left: return NONE # nothing removed
  // 119:   !myself.left_of left
  // 120:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_26(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // my_key: 0
  // key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__15_27;
}
static void cont__15_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 121: ... :
  // 122:   $right remove_item(right_of(myself) key)
  // 123:   if NONE == right: return NONE # nothing removed
  // 124:   !myself.right_of right
  // 125:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__15_28, 0);
  // 121: -> key > my_key:
  // 122:   $right remove_item(right_of(myself) key)
  // 123:   if NONE == right: return NONE # nothing removed
  // 124:   !myself.right_of right
  // 125:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__15_34(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__16_1_types__key_order_set_(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // key: 0
  // value: 1
  // myself: 2
  // return: 3
  frame->slots[3] /* return */ = create_continuation();
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
  // 138: ... :
  // 139:   return get_item(tree_of(myself) key)
  frame->slots[4] /* temp__1 */ = create_closure(entry__16_2, 0);
  // 140: ... :
  // 141:   $new_tree add_item(tree_of(myself) key)
  // 142:   if NONE != new_tree:
  // 143:     !myself.tree_of new_tree
  // 144:     inc &myself.length_of
  // 145:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__16_5, 0);
  // 146: ... :
  // 147:   $new_tree remove_item(tree_of(myself) key)
  // 148:   if NONE != new_tree:
  // 149:     !myself.tree_of new_tree
  // 150:     dec &myself.length_of
  // 151:   return myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__16_14, 0);
  // 136: case
  // 137:   value
  // 138:   NONE:
  // 139:     return get_item(tree_of(myself) key)
  // 140:   true:
  // 141:     $new_tree add_item(tree_of(myself) key)
  // 142:     if NONE != new_tree:
  // 143:       !myself.tree_of new_tree
  // 144:       inc &myself.length_of
  // 145:     return myself
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
  arguments->slots[7] = func__16_23;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__16_25;
}
static void entry__16_2(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 139: ... tree_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* myself */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__16_3;
}
static void cont__16_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 139: ... get_item(tree_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._get_item;
  func = myself->type;
  frame->cont = cont__16_4;
}
static void cont__16_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 139: return get_item(tree_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__16_5(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // new_tree: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* new_tree */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 141: ... tree_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__16_6;
}
static void cont__16_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 141: $new_tree add_item(tree_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__16_7;
}
static void cont__16_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* new_tree */, arguments->slots[0]);
  // 142: ... NONE != new_tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* new_tree */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__16_8;
}
static void cont__16_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 142: ... NONE != new_tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__16_9;
}
static void cont__16_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 142: ... :
  // 143:   !myself.tree_of new_tree
  // 144:   inc &myself.length_of
  frame->slots[6] /* temp__3 */ = create_closure(entry__16_10, 0);
  // 142: if NONE != new_tree:
  // 143:   !myself.tree_of new_tree
  // 144:   inc &myself.length_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__16_13;
}
static void entry__16_10(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // new_tree: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* new_tree */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 143: !myself.tree_of new_tree
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_tree */;
  // 143: !myself.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 144: ... myself.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__16_11;
}
static void cont__16_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 144: inc &myself.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__16_12;
}
static void cont__16_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 144: ... &myself.length_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__length_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__16_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 145: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__16_14(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // new_tree: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* new_tree */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 147: ... tree_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__16_15;
}
static void cont__16_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 147: $new_tree remove_item(tree_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__16_16;
}
static void cont__16_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* new_tree */, arguments->slots[0]);
  // 148: ... NONE != new_tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* new_tree */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__16_17;
}
static void cont__16_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 148: ... NONE != new_tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__16_18;
}
static void cont__16_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 148: ... :
  // 149:   !myself.tree_of new_tree
  // 150:   dec &myself.length_of
  frame->slots[6] /* temp__3 */ = create_closure(entry__16_19, 0);
  // 148: if NONE != new_tree:
  // 149:   !myself.tree_of new_tree
  // 150:   dec &myself.length_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__16_22;
}
static void entry__16_19(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // new_tree: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* new_tree */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 149: !myself.tree_of new_tree
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_tree */;
  // 149: !myself.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 150: ... myself.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__16_20;
}
static void cont__16_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 150: dec &myself.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__16_21;
}
static void cont__16_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 150: ... &myself.length_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__length_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__16_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 151: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__16_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 153: Error "Attempt to set a set element to a nonboolean value!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__16_24;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__16_25(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__21_1_std__key_order_set(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 160: ... -> types::key_order_set
  // 161:   #
  // 162:     returns an empty *key order set*
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__key_order_set;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_3(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // myself: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 166: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__22_4;
}
static void cont__22_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 166: for_each_item left_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = 0;
  myself = var._for_each_item;
  func = myself->type;
  frame->cont = cont__22_5;
}
static void cont__22_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 167: ... key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__22_6;
}
static void cont__22_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 167: body key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__22_7;
}
static void cont__22_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 168: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__22_8;
}
static void cont__22_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 168: for_each_item right_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_1_for_each_item(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 165: ... myself.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_2;
}
static void cont__22_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 165: ... :
  // 166:   for_each_item left_of(myself) body
  // 167:   body key_of(myself)
  // 168:   for_each_item right_of(myself) body
  frame->slots[3] /* temp__2 */ = create_closure(entry__22_3, 0);
  // 165: if myself.is_defined:
  // 166:   for_each_item left_of(myself) body
  // 167:   body key_of(myself)
  // 168:   for_each_item right_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_4(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // tree: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 178: ... for_each_item tree body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_1_types__key_order_set_for_each(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // body: 1
  // tree: 2
  frame->slots[2] /* tree */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 177: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* tree */, arguments->slots[0]);
  // 178: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__23_3;
}
static void cont__23_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 178: ... : for_each_item tree body
  frame->slots[4] /* temp__2 */ = create_closure(entry__23_4, 0);
  // 178: if tree.is_defined: for_each_item tree body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__types__key_order_set(void) {
  var.std__is_a_key_order_set = collect_node(var.std__is_a_key_order_set);
  var._NONE = collect_node(var._NONE);
  var._tree_of = collect_node(var._tree_of);
  var._left_of = collect_node(var._left_of);
  var._right_of = collect_node(var._right_of);
  var.types__key_order_set = collect_node(var.types__key_order_set);
  var._empty_node = collect_node(var._empty_node);
  var._fetch_first = collect_node(var._fetch_first);
  var._get_item = collect_node(var._get_item);
  var._add_item = collect_node(var._add_item);
  var._remove_item = collect_node(var._remove_item);
  var.std__empty_key_order_set = collect_node(var.std__empty_key_order_set);
  var.std__key_order_set = collect_node(var.std__key_order_set);
  var._for_each_item = collect_node(var._for_each_item);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__key_order_set(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_a_key_order_set", get__std__is_a_key_order_set, &poly_idx__std__is_a_key_order_set, &var.std__is_a_key_order_set);
  register_polymorphic_function_with_setter("_basic__types__key_order_set::tree_of", &poly_idx__tree_of);
  register_polymorphic_function_with_setter("_basic__types__key_order_set::left_of", &poly_idx__left_of);
  register_polymorphic_function_with_setter("_basic__types__key_order_set::right_of", &poly_idx__right_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__key_order_set(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__0 = from_uint32(0U);
  unique__NONE = register_unique_item("NONE");
  func__12_1_fetch_first = create_function(entry__12_1_fetch_first, 1);
  func__13_1_get_item = create_function(entry__13_1_get_item, 2);
  func__14_1_add_item = create_function(entry__14_1_add_item, 2);
  func__15_1_remove_item = create_function(entry__15_1_remove_item, 2);
  string__16_24 = from_latin_1_string("Attempt to set a set element to a nonboolean value!", 51);
  func__16_23 = create_function(entry__16_23, 0);
  string__19_1 = from_latin_1_string("key_order_set", 13);
  func__21_1_std__key_order_set = create_function(entry__21_1_std__key_order_set, 0);
  func__22_1_for_each_item = create_function(entry__22_1_for_each_item, 2);
  func__23_1_types__key_order_set_for_each = create_function(entry__23_1_types__key_order_set_for_each, 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__key_order_set(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__key_order_set");
  set_used_namespaces(used_namespaces);
  assign_value(&var._NONE, unique__NONE);
  define_single_assign_static("types", "key_order_set", get__types__key_order_set, &var.types__key_order_set);
  define_single_assign_static("std", "empty_key_order_set", get__std__empty_key_order_set, &var.std__empty_key_order_set);
  define_single_assign_static("std", "key_order_set", get__std__key_order_set, &var.std__key_order_set);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__key_order_set(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__key_order_set");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_polymorphic_function(NULL, "is_a_key_order_set", &get__is_a_key_order_set, &poly_idx__is_a_key_order_set);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_polymorphic_function(NULL, "key_of", &get__key_of, &poly_idx__key_of);
  use_polymorphic_function(NULL, "length_of", &get__length_of, &poly_idx__length_of);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "generic_set", &get__types__generic_set, &get_value_or_future__types__generic_set);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  define_attribute("types", "object", poly_idx__is_a_key_order_set, get__false());
  define_attribute("types", "key_order_set", poly_idx__is_a_key_order_set, get__true());
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__left_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__right_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  define_type_function("types", "key_order_set", entry__16_1_types__key_order_set_, -1);
  define_attribute("types", "key_order_set", poly_idx__tree_of, get__undefined());
  define_attribute("types", "key_order_set", poly_idx__length_of, number__0);
  define_attribute("types", "key_order_set", poly_idx__serialization_tag_of, string__19_1);
  define_method("types", "key_order_set", poly_idx__for_each, func__23_1_types__key_order_set_for_each);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__key_order_set(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_key_order_set, create_function(type__std__is_a_key_order_set, -1));
  assign_value(&var._tree_of, create_function(type__tree_of, -1));
  assign_value(&var._left_of, create_function(type__left_of, -1));
  assign_value(&var._right_of, create_function(type__right_of, -1));
  assign_value(&var.types__key_order_set, get__types__generic_set());
  assign_value(&var._empty_node, get__types__object());
  assign_variable(&var._fetch_first, &func__12_1_fetch_first);
  assign_variable(&var._get_item, &func__13_1_get_item);
  assign_variable(&var._add_item, &func__14_1_add_item);
  assign_variable(&var._remove_item, &func__15_1_remove_item);
  assign_variable(&var.std__empty_key_order_set, &var.types__key_order_set);
  assign_variable(&var.std__key_order_set, &func__21_1_std__key_order_set);
  assign_variable(&var._for_each_item, &func__22_1_for_each_item);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__key_order_set(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__key_order_set);
}
