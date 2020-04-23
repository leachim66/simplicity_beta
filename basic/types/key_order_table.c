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
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_continuation_with_exit(FUNC exit_func);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void continuation_type_function(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *undefined;
IMPORT void allocate_arguments(void);
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
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void def_attribute(NODE **var_p, int idx, void *attr);
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
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__dec;
static NODE_GETTER get_value_or_future__dec;
static NODE_GETTER get__empty_key_order_table;
static NODE_GETTER get_value_or_future__empty_key_order_table;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__for_each;
static NODE_GETTER get__for_each;
static int poly_idx__for_each_from_down_to;
static NODE_GETTER get__for_each_from_down_to;
static int poly_idx__for_each_from_to;
static NODE_GETTER get__for_each_from_to;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static int poly_idx__is_a_key_order_table;
static NODE_GETTER get__is_a_key_order_table;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static int poly_idx__length_of;
static NODE_GETTER get__length_of;
static int poly_idx__new_empty_collection;
static NODE_GETTER get__new_empty_collection;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static int poly_idx__private__get_item;
static NODE_GETTER get__private__get_item;
static int poly_idx__private__set_item;
static NODE_GETTER get__private__set_item;
static NODE_GETTER get__register_collection_serializer;
static NODE_GETTER get_value_or_future__register_collection_serializer;
static int poly_idx__serialization_tag_of;
static NODE_GETTER get__serialization_tag_of;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_of;
static NODE_GETTER get_value_or_future__std__key_of;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__value_of;
static NODE_GETTER get_value_or_future__std__value_of;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__generic_table;
static NODE_GETTER get_value_or_future__types__generic_table;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static int poly_idx__update_each;
static NODE_GETTER get__update_each;
static int poly_idx__update_each_from_down_to;
static NODE_GETTER get__update_each_from_down_to;
static int poly_idx__update_each_from_to;
static NODE_GETTER get__update_each_from_to;
static struct {
  NODE *_NONE;
  NODE *_INSERT;
  NODE *_UPDATE;
  NODE *_tree_of;
  NODE *_key_of;
  NODE *_value_of;
  NODE *_left_of;
  NODE *_right_of;
  NODE *_remove_leftmost;
  NODE *_remove_rightmost;
  NODE *_empty_node;
  NODE *_fetch_first;
  NODE *_retrieve_item;
  NODE *_add_item;
  NODE *_remove_item;
  NODE *_for_each_item;
  NODE *_for_each_item_from_to;
  NODE *_for_each_item_from_down_to;
  NODE *_update_each_item;
  NODE *_update_each_item_from_to;
  NODE *_update_each_item_from_down_to;
  NODE *std__is_a_key_order_table;
  NODE *types__key_order_table;
  NODE *std__empty_key_order_table;
  NODE *std__key_order_table;
} var;
static const char *var_names[] = {
  "NONE",
  "INSERT",
  "UPDATE",
  "tree_of",
  "key_of",
  "value_of",
  "left_of",
  "right_of",
  "remove_leftmost",
  "remove_rightmost",
  "empty_node",
  "fetch_first",
  "retrieve_item",
  "add_item",
  "remove_item",
  "for_each_item",
  "for_each_item_from_to",
  "for_each_item_from_down_to",
  "update_each_item",
  "update_each_item_from_to",
  "update_each_item_from_down_to"
};
static int poly_idx__std__is_a_key_order_table;
static void type__std__is_a_key_order_table(void);
static NODE *get__std__is_a_key_order_table(void) {
  return var.std__is_a_key_order_table;
}
static NODE *unique__NONE;
static NODE *unique__INSERT;
static NODE *unique__UPDATE;
static int poly_idx__tree_of;
static void type__tree_of(void);
static int poly_idx__key_of;
static void type__key_of(void);
static int poly_idx__value_of;
static void type__value_of(void);
static int poly_idx__left_of;
static void type__left_of(void);
static int poly_idx__right_of;
static void type__right_of(void);
static NODE *func__12_1_remove_leftmost;
static void entry__12_1_remove_leftmost(void);
static FRAME_INFO frame__12_1_remove_leftmost = {4, {"node", "key", "value", "left"}};
static void cont__12_2(void);
static void cont__12_3(void);
static NODE *func__12_4;
static void entry__12_4(void);
static FRAME_INFO frame__12_4 = {4, {"left", "key", "value", "node"}};
static void cont__12_5(void);
static NODE *func__12_6;
static void entry__12_6(void);
static FRAME_INFO frame__12_6 = {3, {"key", "node", "value"}};
static void cont__12_7(void);
static void cont__12_8(void);
static void cont__12_9(void);
static void cont__12_10(void);
static NODE *func__13_1_remove_rightmost;
static void entry__13_1_remove_rightmost(void);
static FRAME_INFO frame__13_1_remove_rightmost = {4, {"node", "key", "value", "right"}};
static void cont__13_2(void);
static void cont__13_3(void);
static NODE *func__13_4;
static void entry__13_4(void);
static FRAME_INFO frame__13_4 = {4, {"right", "key", "value", "node"}};
static void cont__13_5(void);
static NODE *func__13_6;
static void entry__13_6(void);
static FRAME_INFO frame__13_6 = {3, {"key", "node", "value"}};
static void cont__13_7(void);
static void cont__13_8(void);
static void cont__13_9(void);
static void cont__13_10(void);
static NODE *get__types__key_order_table(void) {
  return var.types__key_order_table;
}
static NODE *func__18_1_fetch_first;
static void entry__18_1_fetch_first(void);
static FRAME_INFO frame__18_1_fetch_first = {3, {"myself", "return", "left"}};
static void exit__18_1_fetch_first(void);
static void cont__18_2(void);
static void cont__18_3(void);
static NODE *func__18_4;
static void entry__18_4(void);
static FRAME_INFO frame__18_4 = {5, {"left", "myself", "return", "key", "value"}};
static void cont__18_5(void);
static NODE *func__18_6;
static void entry__18_6(void);
static FRAME_INFO frame__18_6 = {4, {"myself", "return", "key", "value"}};
static void cont__18_7(void);
static void cont__18_8(void);
static void cont__18_9(void);
static void cont__18_10(void);
static NODE *func__19_1_retrieve_item;
static void entry__19_1_retrieve_item(void);
static FRAME_INFO frame__19_1_retrieve_item = {4, {"myself", "key", "return", "my_key"}};
static void cont__19_2(void);
static NODE *func__19_3;
static void entry__19_3(void);
static FRAME_INFO frame__19_3 = {1, {"return"}};
static void cont__19_4(void);
static void cont__19_5(void);
static NODE *func__19_6;
static void entry__19_6(void);
static FRAME_INFO frame__19_6 = {4, {"key", "my_key", "return", "myself"}};
static void cont__19_7(void);
static NODE *func__19_8;
static void entry__19_8(void);
static FRAME_INFO frame__19_8 = {2, {"return", "myself"}};
static void cont__19_9(void);
static NODE *func__19_10;
static void entry__19_10(void);
static FRAME_INFO frame__19_10 = {4, {"key", "my_key", "return", "myself"}};
static void cont__19_11(void);
static NODE *func__19_12;
static void entry__19_12(void);
static FRAME_INFO frame__19_12 = {3, {"return", "myself", "key"}};
static void cont__19_13(void);
static void cont__19_14(void);
static NODE *func__19_15;
static void entry__19_15(void);
static FRAME_INFO frame__19_15 = {4, {"my_key", "key", "return", "myself"}};
static void cont__19_16(void);
static NODE *func__19_17;
static void entry__19_17(void);
static FRAME_INFO frame__19_17 = {3, {"return", "myself", "key"}};
static void cont__19_18(void);
static void cont__19_19(void);
static void cont__19_20(void);
static NODE *func__20_1_add_item;
static void entry__20_1_add_item(void);
static FRAME_INFO frame__20_1_add_item = {5, {"myself", "key", "value", "return", "my_key"}};
static void cont__20_2(void);
static NODE *func__20_3;
static void entry__20_3(void);
static FRAME_INFO frame__20_3 = {3, {"return", "key", "value"}};
static void cont__20_4(void);
static void cont__20_5(void);
static NODE *func__20_6;
static void entry__20_6(void);
static FRAME_INFO frame__20_6 = {5, {"key", "my_key", "return", "myself", "value"}};
static void cont__20_7(void);
static NODE *func__20_8;
static void entry__20_8(void);
static FRAME_INFO frame__20_8 = {3, {"return", "myself", "value"}};
static NODE *func__20_9;
static void entry__20_9(void);
static FRAME_INFO frame__20_9 = {5, {"key", "my_key", "myself", "value", "return"}};
static void cont__20_10(void);
static NODE *func__20_11;
static void entry__20_11(void);
static FRAME_INFO frame__20_11 = {6, {"myself", "key", "value", "return", "left", "mode"}};
static void cont__20_12(void);
static void cont__20_13(void);
static NODE *func__20_14;
static void entry__20_14(void);
static FRAME_INFO frame__20_14 = {5, {"my_key", "key", "myself", "value", "return"}};
static void cont__20_15(void);
static NODE *func__20_16;
static void entry__20_16(void);
static FRAME_INFO frame__20_16 = {6, {"myself", "key", "value", "return", "right", "mode"}};
static void cont__20_17(void);
static void cont__20_18(void);
static void cont__20_19(void);
static NODE *func__21_1_remove_item;
static void entry__21_1_remove_item(void);
static FRAME_INFO frame__21_1_remove_item = {4, {"myself", "key", "return", "my_key"}};
static void cont__21_2(void);
static NODE *func__21_3;
static void entry__21_3(void);
static FRAME_INFO frame__21_3 = {1, {"return"}};
static void cont__21_4(void);
static void cont__21_5(void);
static NODE *func__21_6;
static void entry__21_6(void);
static FRAME_INFO frame__21_6 = {4, {"key", "my_key", "myself", "return"}};
static void cont__21_7(void);
static NODE *func__21_8;
static void entry__21_8(void);
static FRAME_INFO frame__21_8 = {4, {"myself", "return", "left", "right"}};
static void cont__21_9(void);
static void cont__21_10(void);
static void cont__21_11(void);
static NODE *func__21_12;
static void entry__21_12(void);
static FRAME_INFO frame__21_12 = {3, {"right", "return", "left"}};
static void cont__21_13(void);
static NODE *func__21_14;
static void entry__21_14(void);
static FRAME_INFO frame__21_14 = {5, {"right", "return", "left", "head_key", "head_value"}};
static void cont__21_15(void);
static NODE *func__21_16;
static void entry__21_16(void);
static FRAME_INFO frame__21_16 = {2, {"return", "left"}};
static NODE *func__21_17;
static void entry__21_17(void);
static FRAME_INFO frame__21_17 = {2, {"return", "right"}};
static NODE *func__21_18;
static void entry__21_18(void);
static FRAME_INFO frame__21_18 = {4, {"key", "my_key", "myself", "return"}};
static void cont__21_19(void);
static NODE *func__21_20;
static void entry__21_20(void);
static FRAME_INFO frame__21_20 = {4, {"myself", "key", "return", "left"}};
static void cont__21_21(void);
static void cont__21_22(void);
static void cont__21_23(void);
static NODE *func__21_24;
static void entry__21_24(void);
static FRAME_INFO frame__21_24 = {1, {"return"}};
static void cont__21_25(void);
static NODE *func__21_26;
static void entry__21_26(void);
static FRAME_INFO frame__21_26 = {4, {"my_key", "key", "myself", "return"}};
static void cont__21_27(void);
static NODE *func__21_28;
static void entry__21_28(void);
static FRAME_INFO frame__21_28 = {4, {"myself", "key", "return", "right"}};
static void cont__21_29(void);
static void cont__21_30(void);
static void cont__21_31(void);
static NODE *func__21_32;
static void entry__21_32(void);
static FRAME_INFO frame__21_32 = {1, {"return"}};
static void cont__21_33(void);
static void cont__21_34(void);
static NODE *func__22_1_types__key_order_table_private__set_item;
static void entry__22_1_types__key_order_table_private__set_item(void);
static FRAME_INFO frame__22_1_types__key_order_table_private__set_item = {3, {"self", "key", "value"}};
static void cont__22_2(void);
static NODE *func__22_3;
static void entry__22_3(void);
static FRAME_INFO frame__22_3 = {3, {"self", "key", "new_tree"}};
static void cont__22_4(void);
static void cont__22_5(void);
static void cont__22_6(void);
static void cont__22_7(void);
static NODE *func__22_8;
static void entry__22_8(void);
static FRAME_INFO frame__22_8 = {2, {"self", "new_tree"}};
static void cont__22_9(void);
static void cont__22_10(void);
static NODE *func__22_11;
static void entry__22_11(void);
static FRAME_INFO frame__22_11 = {5, {"self", "key", "value", "new_tree", "mode"}};
static void cont__22_12(void);
static void cont__22_13(void);
static void cont__22_14(void);
static NODE *func__22_15;
static void entry__22_15(void);
static FRAME_INFO frame__22_15 = {1, {"self"}};
static void cont__22_16(void);
static void cont__22_17(void);
static void cont__22_18(void);
static NODE *func__23_1_types__key_order_table_private__get_item;
static void entry__23_1_types__key_order_table_private__get_item(void);
static FRAME_INFO frame__23_1_types__key_order_table_private__get_item = {2, {"self", "key"}};
static void cont__23_2(void);
static NODE *string__26_1;
static NODE *func__27_1_types__key_order_table_new_empty_collection;
static void entry__27_1_types__key_order_table_new_empty_collection(void);
static FRAME_INFO frame__27_1_types__key_order_table_new_empty_collection = {1, {"self"}};
static NODE *get__std__empty_key_order_table(void) {
  return var.std__empty_key_order_table;
}
static NODE *func__29_1_std__key_order_table;
static void entry__29_1_std__key_order_table(void);
static FRAME_INFO frame__29_1_std__key_order_table = {2, {"initializers", "tab"}};
static NODE *func__29_2;
static void entry__29_2(void);
static FRAME_INFO frame__29_2 = {2, {"initializer", "tab"}};
static void cont__29_3(void);
static void cont__29_4(void);
static void cont__29_5(void);
static void cont__29_6(void);
static NODE *get__std__key_order_table(void) {
  return var.std__key_order_table;
}
static NODE *func__30_1_for_each_item;
static void entry__30_1_for_each_item(void);
static FRAME_INFO frame__30_1_for_each_item = {2, {"myself", "body"}};
static void cont__30_2(void);
static NODE *func__30_3;
static void entry__30_3(void);
static FRAME_INFO frame__30_3 = {2, {"myself", "body"}};
static void cont__30_4(void);
static void cont__30_5(void);
static void cont__30_6(void);
static void cont__30_7(void);
static NODE *func__30_8;
static void entry__30_8(void);
static FRAME_INFO frame__30_8 = {2, {"body", "myself"}};
static void cont__30_9(void);
static void cont__30_10(void);
static NODE *func__30_11;
static void entry__30_11(void);
static FRAME_INFO frame__30_11 = {2, {"body", "myself"}};
static void cont__30_12(void);
static void cont__30_13(void);
static void cont__30_14(void);
static NODE *func__31_1_types__key_order_table_for_each;
static void entry__31_1_types__key_order_table_for_each(void);
static FRAME_INFO frame__31_1_types__key_order_table_for_each = {3, {"self", "body", "tree"}};
static void cont__31_2(void);
static void cont__31_3(void);
static NODE *func__31_4;
static void entry__31_4(void);
static FRAME_INFO frame__31_4 = {2, {"tree", "body"}};
static NODE *func__32_1_for_each_item_from_to;
static void entry__32_1_for_each_item_from_to(void);
static FRAME_INFO frame__32_1_for_each_item_from_to = {4, {"myself", "first", "last", "body"}};
static void cont__32_2(void);
static NODE *func__32_3;
static void entry__32_3(void);
static FRAME_INFO frame__32_3 = {5, {"myself", "first", "last", "body", "key"}};
static void cont__32_4(void);
static void cont__32_5(void);
static NODE *func__32_6;
static void entry__32_6(void);
static FRAME_INFO frame__32_6 = {2, {"first", "key"}};
static void cont__32_7(void);
static void cont__32_8(void);
static NODE *func__32_9;
static void entry__32_9(void);
static FRAME_INFO frame__32_9 = {4, {"myself", "first", "last", "body"}};
static void cont__32_10(void);
static void cont__32_11(void);
static void cont__32_12(void);
static NODE *func__32_13;
static void entry__32_13(void);
static FRAME_INFO frame__32_13 = {2, {"key", "first"}};
static void cont__32_14(void);
static void cont__32_15(void);
static void cont__32_16(void);
static NODE *func__32_17;
static void entry__32_17(void);
static FRAME_INFO frame__32_17 = {2, {"last", "key"}};
static void cont__32_18(void);
static NODE *func__32_19;
static void entry__32_19(void);
static FRAME_INFO frame__32_19 = {2, {"last", "key"}};
static void cont__32_20(void);
static void cont__32_21(void);
static void cont__32_22(void);
static void cont__32_23(void);
static NODE *func__32_24;
static void entry__32_24(void);
static FRAME_INFO frame__32_24 = {3, {"body", "key", "myself"}};
static void cont__32_25(void);
static void cont__32_26(void);
static NODE *func__32_27;
static void entry__32_27(void);
static FRAME_INFO frame__32_27 = {3, {"body", "key", "myself"}};
static void cont__32_28(void);
static NODE *func__32_29;
static void entry__32_29(void);
static FRAME_INFO frame__32_29 = {2, {"body", "myself"}};
static void cont__32_30(void);
static void cont__32_31(void);
static void cont__32_32(void);
static NODE *func__32_33;
static void entry__32_33(void);
static FRAME_INFO frame__32_33 = {2, {"key", "last"}};
static void cont__32_34(void);
static void cont__32_35(void);
static NODE *func__32_36;
static void entry__32_36(void);
static FRAME_INFO frame__32_36 = {4, {"myself", "first", "last", "body"}};
static void cont__32_37(void);
static NODE *func__33_1_types__key_order_table_for_each_from_to;
static void entry__33_1_types__key_order_table_for_each_from_to(void);
static FRAME_INFO frame__33_1_types__key_order_table_for_each_from_to = {5, {"self", "first", "last", "body", "tree"}};
static void cont__33_2(void);
static void cont__33_3(void);
static NODE *func__33_4;
static void entry__33_4(void);
static FRAME_INFO frame__33_4 = {4, {"tree", "first", "last", "body"}};
static NODE *func__34_1_for_each_item_from_down_to;
static void entry__34_1_for_each_item_from_down_to(void);
static FRAME_INFO frame__34_1_for_each_item_from_down_to = {4, {"myself", "last", "first", "body"}};
static void cont__34_2(void);
static NODE *func__34_3;
static void entry__34_3(void);
static FRAME_INFO frame__34_3 = {5, {"myself", "last", "first", "body", "key"}};
static void cont__34_4(void);
static void cont__34_5(void);
static NODE *func__34_6;
static void entry__34_6(void);
static FRAME_INFO frame__34_6 = {2, {"key", "last"}};
static void cont__34_7(void);
static void cont__34_8(void);
static NODE *func__34_9;
static void entry__34_9(void);
static FRAME_INFO frame__34_9 = {4, {"myself", "last", "first", "body"}};
static void cont__34_10(void);
static void cont__34_11(void);
static void cont__34_12(void);
static NODE *func__34_13;
static void entry__34_13(void);
static FRAME_INFO frame__34_13 = {2, {"key", "first"}};
static void cont__34_14(void);
static void cont__34_15(void);
static void cont__34_16(void);
static NODE *func__34_17;
static void entry__34_17(void);
static FRAME_INFO frame__34_17 = {2, {"last", "key"}};
static void cont__34_18(void);
static NODE *func__34_19;
static void entry__34_19(void);
static FRAME_INFO frame__34_19 = {2, {"last", "key"}};
static void cont__34_20(void);
static void cont__34_21(void);
static void cont__34_22(void);
static void cont__34_23(void);
static NODE *func__34_24;
static void entry__34_24(void);
static FRAME_INFO frame__34_24 = {3, {"body", "key", "myself"}};
static void cont__34_25(void);
static void cont__34_26(void);
static NODE *func__34_27;
static void entry__34_27(void);
static FRAME_INFO frame__34_27 = {3, {"body", "key", "myself"}};
static void cont__34_28(void);
static NODE *func__34_29;
static void entry__34_29(void);
static FRAME_INFO frame__34_29 = {2, {"body", "myself"}};
static void cont__34_30(void);
static void cont__34_31(void);
static void cont__34_32(void);
static NODE *func__34_33;
static void entry__34_33(void);
static FRAME_INFO frame__34_33 = {2, {"first", "key"}};
static void cont__34_34(void);
static void cont__34_35(void);
static NODE *func__34_36;
static void entry__34_36(void);
static FRAME_INFO frame__34_36 = {4, {"myself", "last", "first", "body"}};
static void cont__34_37(void);
static NODE *func__35_1_types__key_order_table_for_each_from_down_to;
static void entry__35_1_types__key_order_table_for_each_from_down_to(void);
static FRAME_INFO frame__35_1_types__key_order_table_for_each_from_down_to = {5, {"self", "last", "first", "body", "tree"}};
static void cont__35_2(void);
static void cont__35_3(void);
static NODE *func__35_4;
static void entry__35_4(void);
static FRAME_INFO frame__35_4 = {4, {"tree", "last", "first", "body"}};
static NODE *func__36_1_update_each_item;
static void entry__36_1_update_each_item(void);
static FRAME_INFO frame__36_1_update_each_item = {2, {"myself", "body"}};
static void cont__36_2(void);
static NODE *func__36_3;
static void entry__36_3(void);
static FRAME_INFO frame__36_3 = {2, {"myself", "body"}};
static void cont__36_4(void);
static void cont__36_5(void);
static void cont__36_6(void);
static void cont__36_7(void);
static void cont__36_8(void);
static void cont__36_9(void);
static void cont__36_10(void);
static void cont__36_11(void);
static NODE *func__37_1_update_each_item_from_to;
static void entry__37_1_update_each_item_from_to(void);
static FRAME_INFO frame__37_1_update_each_item_from_to = {4, {"myself", "first", "last", "body"}};
static void cont__37_2(void);
static NODE *func__37_3;
static void entry__37_3(void);
static FRAME_INFO frame__37_3 = {5, {"myself", "first", "last", "body", "key"}};
static void cont__37_4(void);
static void cont__37_5(void);
static NODE *func__37_6;
static void entry__37_6(void);
static FRAME_INFO frame__37_6 = {2, {"first", "key"}};
static void cont__37_7(void);
static void cont__37_8(void);
static NODE *func__37_9;
static void entry__37_9(void);
static FRAME_INFO frame__37_9 = {4, {"myself", "first", "last", "body"}};
static void cont__37_10(void);
static void cont__37_11(void);
static void cont__37_12(void);
static void cont__37_13(void);
static NODE *func__37_14;
static void entry__37_14(void);
static FRAME_INFO frame__37_14 = {2, {"key", "first"}};
static void cont__37_15(void);
static void cont__37_16(void);
static void cont__37_17(void);
static NODE *func__37_18;
static void entry__37_18(void);
static FRAME_INFO frame__37_18 = {2, {"last", "key"}};
static void cont__37_19(void);
static NODE *func__37_20;
static void entry__37_20(void);
static FRAME_INFO frame__37_20 = {2, {"last", "key"}};
static void cont__37_21(void);
static void cont__37_22(void);
static void cont__37_23(void);
static void cont__37_24(void);
static NODE *func__37_25;
static void entry__37_25(void);
static FRAME_INFO frame__37_25 = {3, {"body", "myself", "key"}};
static void cont__37_26(void);
static void cont__37_27(void);
static void cont__37_28(void);
static void cont__37_29(void);
static NODE *func__37_30;
static void entry__37_30(void);
static FRAME_INFO frame__37_30 = {2, {"key", "last"}};
static void cont__37_31(void);
static void cont__37_32(void);
static NODE *func__37_33;
static void entry__37_33(void);
static FRAME_INFO frame__37_33 = {4, {"myself", "first", "last", "body"}};
static void cont__37_34(void);
static void cont__37_35(void);
static void cont__37_36(void);
static NODE *func__38_1_types__key_order_table_update_each_from_to;
static void entry__38_1_types__key_order_table_update_each_from_to(void);
static FRAME_INFO frame__38_1_types__key_order_table_update_each_from_to = {4, {"self", "first", "last", "body"}};
static void cont__38_2(void);
static void cont__38_3(void);
static NODE *func__38_4;
static void entry__38_4(void);
static FRAME_INFO frame__38_4 = {4, {"self", "first", "last", "body"}};
static void cont__38_5(void);
static void cont__38_6(void);
static void cont__38_7(void);
static NODE *func__39_1_update_each_item_from_down_to;
static void entry__39_1_update_each_item_from_down_to(void);
static FRAME_INFO frame__39_1_update_each_item_from_down_to = {4, {"myself", "last", "first", "body"}};
static void cont__39_2(void);
static NODE *func__39_3;
static void entry__39_3(void);
static FRAME_INFO frame__39_3 = {5, {"myself", "last", "first", "body", "key"}};
static void cont__39_4(void);
static void cont__39_5(void);
static NODE *func__39_6;
static void entry__39_6(void);
static FRAME_INFO frame__39_6 = {2, {"key", "last"}};
static void cont__39_7(void);
static void cont__39_8(void);
static NODE *func__39_9;
static void entry__39_9(void);
static FRAME_INFO frame__39_9 = {4, {"myself", "last", "first", "body"}};
static void cont__39_10(void);
static void cont__39_11(void);
static void cont__39_12(void);
static void cont__39_13(void);
static NODE *func__39_14;
static void entry__39_14(void);
static FRAME_INFO frame__39_14 = {2, {"key", "first"}};
static void cont__39_15(void);
static void cont__39_16(void);
static void cont__39_17(void);
static NODE *func__39_18;
static void entry__39_18(void);
static FRAME_INFO frame__39_18 = {2, {"last", "key"}};
static void cont__39_19(void);
static NODE *func__39_20;
static void entry__39_20(void);
static FRAME_INFO frame__39_20 = {2, {"last", "key"}};
static void cont__39_21(void);
static void cont__39_22(void);
static void cont__39_23(void);
static void cont__39_24(void);
static NODE *func__39_25;
static void entry__39_25(void);
static FRAME_INFO frame__39_25 = {3, {"body", "myself", "key"}};
static void cont__39_26(void);
static void cont__39_27(void);
static void cont__39_28(void);
static void cont__39_29(void);
static NODE *func__39_30;
static void entry__39_30(void);
static FRAME_INFO frame__39_30 = {2, {"first", "key"}};
static void cont__39_31(void);
static void cont__39_32(void);
static NODE *func__39_33;
static void entry__39_33(void);
static FRAME_INFO frame__39_33 = {4, {"myself", "last", "first", "body"}};
static void cont__39_34(void);
static void cont__39_35(void);
static void cont__39_36(void);
static NODE *func__40_1_types__key_order_table_update_each_from_down_to;
static void entry__40_1_types__key_order_table_update_each_from_down_to(void);
static FRAME_INFO frame__40_1_types__key_order_table_update_each_from_down_to = {4, {"self", "last", "first", "body"}};
static void cont__40_2(void);
static void cont__40_3(void);
static NODE *func__40_4;
static void entry__40_4(void);
static FRAME_INFO frame__40_4 = {4, {"self", "last", "first", "body"}};
static void cont__40_5(void);
static void cont__40_6(void);
static void cont__40_7(void);
static NODE *func__41_1_types__key_order_table_update_each;
static void entry__41_1_types__key_order_table_update_each(void);
static FRAME_INFO frame__41_1_types__key_order_table_update_each = {2, {"self", "body"}};
static void cont__41_2(void);
static void cont__41_3(void);
static NODE *func__41_4;
static void entry__41_4(void);
static FRAME_INFO frame__41_4 = {2, {"self", "body"}};
static void cont__41_5(void);
static void cont__41_6(void);
static void cont__41_7(void);
static void cont__84_1(void);
void run__basic__types__key_order_table(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_key_order_table, NULL, 23, 23, 2, 26},
  {type__tree_of, NULL, 32, 32, 2, 8},
  {type__key_of, NULL, 33, 33, 2, 7},
  {type__value_of, NULL, 34, 34, 2, 9},
  {type__left_of, NULL, 35, 35, 2, 8},
  {type__right_of, NULL, 36, 36, 2, 9},
  {run__basic__types__key_order_table, NULL, 387, 387, 1, 70},
  {cont__84_1, NULL, },
  {entry__12_4, NULL, 47, 47, 7, 39},
  {cont__12_5, &frame__12_4, 48, 48, 24, 24},
  {entry__12_6, NULL, 50, 50, 7, 23},
  {cont__12_7, &frame__12_6, 51, 51, 7, 27},
  {cont__12_8, &frame__12_6, 52, 52, 7, 26},
  {cont__12_9, &frame__12_6, 52, 52, 26, 26},
  {entry__12_1_remove_leftmost, NULL, 44, 44, 3, 22},
  {cont__12_2, &frame__12_1_remove_leftmost, 46, 46, 5, 19},
  {cont__12_3, &frame__12_1_remove_leftmost, 45, 52, 3, 27},
  {cont__12_10, &frame__12_1_remove_leftmost, },
  {entry__13_4, NULL, 63, 63, 7, 41},
  {cont__13_5, &frame__13_4, 64, 64, 26, 26},
  {entry__13_6, NULL, 66, 66, 7, 23},
  {cont__13_7, &frame__13_6, 67, 67, 7, 27},
  {cont__13_8, &frame__13_6, 68, 68, 7, 25},
  {cont__13_9, &frame__13_6, 68, 68, 25, 25},
  {entry__13_1_remove_rightmost, NULL, 60, 60, 3, 24},
  {cont__13_2, &frame__13_1_remove_rightmost, 62, 62, 5, 20},
  {cont__13_3, &frame__13_1_remove_rightmost, 61, 68, 3, 26},
  {cont__13_10, &frame__13_1_remove_rightmost, },
  {entry__18_4, NULL, 86, 86, 7, 35},
  {cont__18_5, &frame__18_4, 88, 88, 7, 22},
  {entry__18_6, NULL, 90, 90, 7, 25},
  {cont__18_7, &frame__18_6, 91, 91, 7, 29},
  {cont__18_8, &frame__18_6, 92, 92, 7, 30},
  {cont__18_9, &frame__18_6, 93, 93, 7, 22},
  {entry__18_1_fetch_first, NULL, 83, 83, 3, 24},
  {cont__18_2, &frame__18_1_fetch_first, 85, 85, 5, 19},
  {cont__18_3, &frame__18_1_fetch_first, 84, 93, 3, 23},
  {cont__18_10, &frame__18_1_fetch_first, 93, 93, 23, 23},
  {entry__19_3, NULL, 101, 101, 27, 42},
  {entry__19_8, NULL, 104, 104, 30, 45},
  {cont__19_9, &frame__19_8, 104, 104, 23, 45},
  {entry__19_6, NULL, 104, 104, 8, 20},
  {cont__19_7, &frame__19_6, 104, 104, 5, 45},
  {entry__19_12, NULL, 105, 105, 43, 57},
  {cont__19_13, &frame__19_12, 105, 105, 29, 62},
  {cont__19_14, &frame__19_12, 105, 105, 22, 62},
  {entry__19_10, NULL, 105, 105, 8, 19},
  {cont__19_11, &frame__19_10, 105, 105, 5, 62},
  {entry__19_17, NULL, 106, 106, 43, 58},
  {cont__19_18, &frame__19_17, 106, 106, 29, 63},
  {cont__19_19, &frame__19_17, 106, 106, 22, 63},
  {entry__19_15, NULL, 106, 106, 8, 19},
  {cont__19_16, &frame__19_15, 106, 106, 5, 63},
  {entry__19_1_retrieve_item, NULL, 101, 101, 6, 24},
  {cont__19_2, &frame__19_1_retrieve_item, 101, 101, 3, 42},
  {cont__19_4, &frame__19_1_retrieve_item, 102, 102, 3, 24},
  {cont__19_5, &frame__19_1_retrieve_item, 103, 106, 3, 63},
  {cont__19_20, &frame__19_1_retrieve_item, 106, 106, 63, 63},
  {entry__20_3, NULL, 115, 115, 27, 79},
  {entry__20_8, NULL, 118, 118, 23, 59},
  {entry__20_6, NULL, 118, 118, 8, 20},
  {cont__20_7, &frame__20_6, 118, 118, 5, 59},
  {entry__20_11, NULL, 120, 120, 28, 42},
  {cont__20_12, &frame__20_11, 120, 120, 7, 52},
  {cont__20_13, &frame__20_11, 121, 121, 7, 39},
  {entry__20_9, NULL, 119, 119, 8, 19},
  {cont__20_10, &frame__20_9, 119, 121, 5, 39},
  {entry__20_16, NULL, 123, 123, 29, 44},
  {cont__20_17, &frame__20_16, 123, 123, 7, 54},
  {cont__20_18, &frame__20_16, 124, 124, 7, 41},
  {entry__20_14, NULL, 122, 122, 8, 19},
  {cont__20_15, &frame__20_14, 122, 124, 5, 41},
  {entry__20_1_add_item, NULL, 115, 115, 6, 24},
  {cont__20_2, &frame__20_1_add_item, 115, 115, 3, 79},
  {cont__20_4, &frame__20_1_add_item, 116, 116, 3, 24},
  {cont__20_5, &frame__20_1_add_item, 117, 124, 3, 42},
  {cont__20_19, &frame__20_1_add_item, 124, 124, 42, 42},
  {entry__21_3, NULL, 132, 132, 27, 55},
  {entry__21_14, NULL, 142, 142, 15, 54},
  {cont__21_15, &frame__21_14, 143, 148, 15, 34},
  {entry__21_16, NULL, 150, 150, 15, 25},
  {entry__21_12, NULL, 141, 141, 13, 28},
  {cont__21_13, &frame__21_12, 140, 150, 11, 26},
  {entry__21_17, NULL, 152, 152, 11, 22},
  {entry__21_8, NULL, 136, 136, 7, 27},
  {cont__21_9, &frame__21_8, 137, 137, 7, 30},
  {cont__21_10, &frame__21_8, 139, 139, 9, 23},
  {cont__21_11, &frame__21_8, 138, 152, 7, 23},
  {entry__21_6, NULL, 135, 135, 8, 20},
  {cont__21_7, &frame__21_6, 135, 152, 5, 24},
  {entry__21_24, NULL, 155, 155, 24, 52},
  {entry__21_20, NULL, 154, 154, 25, 39},
  {cont__21_21, &frame__21_20, 154, 154, 7, 44},
  {cont__21_22, &frame__21_20, 155, 155, 10, 21},
  {cont__21_23, &frame__21_20, 155, 155, 7, 52},
  {cont__21_25, &frame__21_20, 157, 157, 7, 19},
  {entry__21_18, NULL, 153, 153, 8, 19},
  {cont__21_19, &frame__21_18, 153, 157, 5, 19},
  {entry__21_32, NULL, 160, 160, 25, 53},
  {entry__21_28, NULL, 159, 159, 26, 41},
  {cont__21_29, &frame__21_28, 159, 159, 7, 46},
  {cont__21_30, &frame__21_28, 160, 160, 10, 22},
  {cont__21_31, &frame__21_28, 160, 160, 7, 53},
  {cont__21_33, &frame__21_28, 162, 162, 7, 19},
  {entry__21_26, NULL, 158, 158, 8, 19},
  {cont__21_27, &frame__21_26, 158, 162, 5, 19},
  {entry__21_1_remove_item, NULL, 132, 132, 6, 24},
  {cont__21_2, &frame__21_1_remove_item, 132, 132, 3, 55},
  {cont__21_4, &frame__21_1_remove_item, 133, 133, 3, 24},
  {cont__21_5, &frame__21_1_remove_item, 134, 162, 3, 20},
  {cont__21_34, &frame__21_1_remove_item, 162, 162, 20, 20},
  {entry__22_8, NULL, 177, 177, 14, 27},
  {cont__22_9, &frame__22_8, 177, 177, 9, 27},
  {cont__22_10, &frame__22_8, 177, 177, 27, 27},
  {entry__22_3, NULL, 174, 174, 29, 41},
  {cont__22_4, &frame__22_3, 174, 174, 7, 46},
  {cont__22_5, &frame__22_3, 175, 175, 10, 25},
  {cont__22_6, &frame__22_3, 175, 175, 10, 25},
  {cont__22_7, &frame__22_3, 175, 177, 7, 27},
  {entry__22_15, NULL, 181, 181, 31, 44},
  {cont__22_16, &frame__22_15, 181, 181, 26, 44},
  {cont__22_17, &frame__22_15, 181, 181, 44, 44},
  {entry__22_11, NULL, 179, 179, 32, 44},
  {cont__22_12, &frame__22_11, 179, 179, 7, 54},
  {cont__22_13, &frame__22_11, 181, 181, 10, 23},
  {cont__22_14, &frame__22_11, 181, 181, 7, 44},
  {entry__22_1_types__key_order_table_private__set_item, NULL, 173, 173, 5, 22},
  {cont__22_2, &frame__22_1_types__key_order_table_private__set_item, 172, 181, 3, 45},
  {cont__22_18, &frame__22_1_types__key_order_table_private__set_item, },
  {entry__23_1_types__key_order_table_private__get_item, NULL, 190, 190, 17, 29},
  {cont__23_2, &frame__23_1_types__key_order_table_private__get_item, 190, 190, 3, 33},
  {entry__27_1_types__key_order_table_new_empty_collection, NULL, 208, 208, 3, 27},
  {entry__29_2, NULL, 229, 229, 5, 61},
  {cont__29_3, &frame__29_2, 229, 229, 10, 33},
  {cont__29_4, &frame__29_2, 229, 229, 5, 34},
  {cont__29_5, &frame__29_2, 229, 229, 61, 61},
  {entry__29_1_std__key_order_table, NULL, 228, 229, 3, 61},
  {cont__29_6, &frame__29_1_std__key_order_table, 230, 230, 3, 8},
  {entry__30_8, NULL, 237, 237, 14, 27},
  {cont__30_9, &frame__30_8, 237, 237, 29, 44},
  {cont__30_10, &frame__30_8, 237, 237, 9, 44},
  {entry__30_11, NULL, 239, 239, 14, 29},
  {cont__30_12, &frame__30_11, 239, 239, 9, 29},
  {entry__30_3, NULL, 234, 234, 19, 33},
  {cont__30_4, &frame__30_3, 234, 234, 5, 38},
  {cont__30_5, &frame__30_3, 236, 236, 7, 30},
  {cont__30_6, &frame__30_3, 236, 236, 7, 35},
  {cont__30_7, &frame__30_3, 235, 239, 5, 30},
  {cont__30_13, &frame__30_3, 240, 240, 19, 34},
  {cont__30_14, &frame__30_3, 240, 240, 5, 39},
  {entry__30_1_for_each_item, NULL, 233, 233, 6, 22},
  {cont__30_2, &frame__30_1_for_each_item, 233, 240, 3, 39},
  {entry__31_4, NULL, 250, 250, 23, 45},
  {entry__31_1_types__key_order_table_for_each, NULL, 249, 249, 3, 21},
  {cont__31_2, &frame__31_1_types__key_order_table_for_each, 250, 250, 6, 20},
  {cont__31_3, &frame__31_1_types__key_order_table_for_each, 250, 250, 3, 45},
  {entry__32_6, NULL, 255, 255, 30, 40},
  {cont__32_7, &frame__32_6, 255, 255, 30, 40},
  {entry__32_9, NULL, 256, 256, 29, 43},
  {cont__32_10, &frame__32_9, 256, 256, 7, 59},
  {entry__32_13, NULL, 258, 258, 30, 41},
  {cont__32_14, &frame__32_13, 258, 258, 30, 41},
  {cont__32_15, &frame__32_13, 258, 258, 30, 41},
  {entry__32_19, NULL, 258, 258, 69, 79},
  {cont__32_20, &frame__32_19, 258, 258, 69, 79},
  {cont__32_21, &frame__32_19, 258, 258, 69, 79},
  {entry__32_17, NULL, 258, 258, 48, 64},
  {cont__32_18, &frame__32_17, 258, 258, 48, 79},
  {cont__32_22, &frame__32_17, 258, 258, 48, 79},
  {entry__32_27, NULL, 262, 262, 22, 37},
  {cont__32_28, &frame__32_27, 262, 262, 13, 37},
  {entry__32_29, NULL, 264, 264, 18, 33},
  {cont__32_30, &frame__32_29, 264, 264, 13, 33},
  {entry__32_24, NULL, 261, 261, 11, 34},
  {cont__32_25, &frame__32_24, 261, 261, 11, 39},
  {cont__32_26, &frame__32_24, 260, 264, 9, 34},
  {entry__32_33, NULL, 265, 265, 29, 38},
  {cont__32_34, &frame__32_33, 265, 265, 29, 38},
  {entry__32_36, NULL, 266, 266, 29, 44},
  {cont__32_37, &frame__32_36, 266, 266, 7, 60},
  {entry__32_3, NULL, 254, 254, 5, 23},
  {cont__32_4, &frame__32_3, 255, 255, 8, 25},
  {cont__32_5, &frame__32_3, 255, 255, 8, 40},
  {cont__32_8, &frame__32_3, 255, 256, 5, 59},
  {cont__32_11, &frame__32_3, 258, 258, 8, 25},
  {cont__32_12, &frame__32_3, 258, 258, 8, 41},
  {cont__32_16, &frame__32_3, 258, 258, 8, 79},
  {cont__32_23, &frame__32_3, 257, 264, 5, 36},
  {cont__32_31, &frame__32_3, 265, 265, 8, 24},
  {cont__32_32, &frame__32_3, 265, 265, 8, 38},
  {cont__32_35, &frame__32_3, 265, 266, 5, 60},
  {entry__32_1_for_each_item_from_to, NULL, 253, 253, 6, 22},
  {cont__32_2, &frame__32_1_for_each_item_from_to, 253, 266, 3, 61},
  {entry__33_4, NULL, 278, 278, 23, 64},
  {entry__33_1_types__key_order_table_for_each_from_to, NULL, 277, 277, 3, 21},
  {cont__33_2, &frame__33_1_types__key_order_table_for_each_from_to, 278, 278, 6, 20},
  {cont__33_3, &frame__33_1_types__key_order_table_for_each_from_to, 278, 278, 3, 64},
  {entry__34_6, NULL, 283, 283, 29, 38},
  {cont__34_7, &frame__34_6, 283, 283, 29, 38},
  {entry__34_9, NULL, 284, 284, 34, 49},
  {cont__34_10, &frame__34_9, 284, 284, 7, 65},
  {entry__34_13, NULL, 286, 286, 30, 41},
  {cont__34_14, &frame__34_13, 286, 286, 30, 41},
  {cont__34_15, &frame__34_13, 286, 286, 30, 41},
  {entry__34_19, NULL, 286, 286, 69, 79},
  {cont__34_20, &frame__34_19, 286, 286, 69, 79},
  {cont__34_21, &frame__34_19, 286, 286, 69, 79},
  {entry__34_17, NULL, 286, 286, 48, 64},
  {cont__34_18, &frame__34_17, 286, 286, 48, 79},
  {cont__34_22, &frame__34_17, 286, 286, 48, 79},
  {entry__34_27, NULL, 290, 290, 22, 37},
  {cont__34_28, &frame__34_27, 290, 290, 13, 37},
  {entry__34_29, NULL, 292, 292, 18, 33},
  {cont__34_30, &frame__34_29, 292, 292, 13, 33},
  {entry__34_24, NULL, 289, 289, 11, 34},
  {cont__34_25, &frame__34_24, 289, 289, 11, 39},
  {cont__34_26, &frame__34_24, 288, 292, 9, 34},
  {entry__34_33, NULL, 293, 293, 30, 40},
  {cont__34_34, &frame__34_33, 293, 293, 30, 40},
  {entry__34_36, NULL, 294, 294, 34, 48},
  {cont__34_37, &frame__34_36, 294, 294, 7, 64},
  {entry__34_3, NULL, 282, 282, 5, 23},
  {cont__34_4, &frame__34_3, 283, 283, 8, 24},
  {cont__34_5, &frame__34_3, 283, 283, 8, 38},
  {cont__34_8, &frame__34_3, 283, 284, 5, 65},
  {cont__34_11, &frame__34_3, 286, 286, 8, 25},
  {cont__34_12, &frame__34_3, 286, 286, 8, 41},
  {cont__34_16, &frame__34_3, 286, 286, 8, 79},
  {cont__34_23, &frame__34_3, 285, 292, 5, 36},
  {cont__34_31, &frame__34_3, 293, 293, 8, 25},
  {cont__34_32, &frame__34_3, 293, 293, 8, 40},
  {cont__34_35, &frame__34_3, 293, 294, 5, 64},
  {entry__34_1_for_each_item_from_down_to, NULL, 281, 281, 6, 22},
  {cont__34_2, &frame__34_1_for_each_item_from_down_to, 281, 294, 3, 65},
  {entry__35_4, NULL, 306, 306, 23, 69},
  {entry__35_1_types__key_order_table_for_each_from_down_to, NULL, 305, 305, 3, 21},
  {cont__35_2, &frame__35_1_types__key_order_table_for_each_from_down_to, 306, 306, 6, 20},
  {cont__35_3, &frame__35_1_types__key_order_table_for_each_from_down_to, 306, 306, 3, 69},
  {entry__36_3, NULL, 314, 314, 23, 36},
  {cont__36_4, &frame__36_3, 314, 314, 5, 41},
  {cont__36_5, &frame__36_3, 315, 315, 10, 23},
  {cont__36_6, &frame__36_3, 315, 315, 26, 40},
  {cont__36_7, &frame__36_3, 315, 315, 5, 40},
  {cont__36_8, &frame__36_3, 316, 316, 23, 37},
  {cont__36_9, &frame__36_3, 316, 316, 5, 42},
  {cont__36_10, &frame__36_3, 316, 316, 42, 42},
  {entry__36_1_update_each_item, NULL, 313, 313, 6, 22},
  {cont__36_2, &frame__36_1_update_each_item, 313, 316, 3, 42},
  {cont__36_11, &frame__36_1_update_each_item, },
  {entry__37_6, NULL, 327, 327, 30, 40},
  {cont__37_7, &frame__37_6, 327, 327, 30, 40},
  {entry__37_9, NULL, 328, 328, 33, 46},
  {cont__37_10, &frame__37_9, 328, 328, 7, 62},
  {cont__37_11, &frame__37_9, 328, 328, 62, 62},
  {entry__37_14, NULL, 330, 330, 30, 41},
  {cont__37_15, &frame__37_14, 330, 330, 30, 41},
  {cont__37_16, &frame__37_14, 330, 330, 30, 41},
  {entry__37_20, NULL, 330, 330, 69, 79},
  {cont__37_21, &frame__37_20, 330, 330, 69, 79},
  {cont__37_22, &frame__37_20, 330, 330, 69, 79},
  {entry__37_18, NULL, 330, 330, 48, 64},
  {cont__37_19, &frame__37_18, 330, 330, 48, 79},
  {cont__37_23, &frame__37_18, 330, 330, 48, 79},
  {entry__37_25, NULL, 332, 332, 19, 33},
  {cont__37_26, &frame__37_25, 332, 332, 9, 33},
  {cont__37_27, &frame__37_25, 332, 332, 33, 33},
  {entry__37_30, NULL, 333, 333, 29, 38},
  {cont__37_31, &frame__37_30, 333, 333, 29, 38},
  {entry__37_33, NULL, 334, 334, 33, 47},
  {cont__37_34, &frame__37_33, 334, 334, 7, 63},
  {cont__37_35, &frame__37_33, 334, 334, 63, 63},
  {entry__37_3, NULL, 326, 326, 5, 23},
  {cont__37_4, &frame__37_3, 327, 327, 8, 25},
  {cont__37_5, &frame__37_3, 327, 327, 8, 40},
  {cont__37_8, &frame__37_3, 327, 328, 5, 62},
  {cont__37_12, &frame__37_3, 330, 330, 8, 25},
  {cont__37_13, &frame__37_3, 330, 330, 8, 41},
  {cont__37_17, &frame__37_3, 330, 330, 8, 79},
  {cont__37_24, &frame__37_3, 329, 332, 5, 34},
  {cont__37_28, &frame__37_3, 333, 333, 8, 24},
  {cont__37_29, &frame__37_3, 333, 333, 8, 38},
  {cont__37_32, &frame__37_3, 333, 334, 5, 63},
  {entry__37_1_update_each_item_from_to, NULL, 325, 325, 6, 22},
  {cont__37_2, &frame__37_1_update_each_item_from_to, 325, 334, 3, 64},
  {cont__37_36, &frame__37_1_update_each_item_from_to, },
  {entry__38_4, NULL, 346, 346, 31, 42},
  {cont__38_5, &frame__38_4, 346, 346, 5, 58},
  {cont__38_6, &frame__38_4, 346, 346, 58, 58},
  {entry__38_1_types__key_order_table_update_each_from_to, NULL, 345, 345, 6, 18},
  {cont__38_2, &frame__38_1_types__key_order_table_update_each_from_to, 345, 345, 6, 29},
  {cont__38_3, &frame__38_1_types__key_order_table_update_each_from_to, 345, 346, 3, 58},
  {cont__38_7, &frame__38_1_types__key_order_table_update_each_from_to, },
  {entry__39_6, NULL, 357, 357, 29, 38},
  {cont__39_7, &frame__39_6, 357, 357, 29, 38},
  {entry__39_9, NULL, 358, 358, 38, 52},
  {cont__39_10, &frame__39_9, 358, 358, 7, 68},
  {cont__39_11, &frame__39_9, 358, 358, 68, 68},
  {entry__39_14, NULL, 360, 360, 30, 41},
  {cont__39_15, &frame__39_14, 360, 360, 30, 41},
  {cont__39_16, &frame__39_14, 360, 360, 30, 41},
  {entry__39_20, NULL, 360, 360, 69, 79},
  {cont__39_21, &frame__39_20, 360, 360, 69, 79},
  {cont__39_22, &frame__39_20, 360, 360, 69, 79},
  {entry__39_18, NULL, 360, 360, 48, 64},
  {cont__39_19, &frame__39_18, 360, 360, 48, 79},
  {cont__39_23, &frame__39_18, 360, 360, 48, 79},
  {entry__39_25, NULL, 362, 362, 19, 33},
  {cont__39_26, &frame__39_25, 362, 362, 9, 33},
  {cont__39_27, &frame__39_25, 362, 362, 33, 33},
  {entry__39_30, NULL, 363, 363, 30, 40},
  {cont__39_31, &frame__39_30, 363, 363, 30, 40},
  {entry__39_33, NULL, 364, 364, 38, 51},
  {cont__39_34, &frame__39_33, 364, 364, 7, 67},
  {cont__39_35, &frame__39_33, 364, 364, 67, 67},
  {entry__39_3, NULL, 356, 356, 5, 23},
  {cont__39_4, &frame__39_3, 357, 357, 8, 24},
  {cont__39_5, &frame__39_3, 357, 357, 8, 38},
  {cont__39_8, &frame__39_3, 357, 358, 5, 68},
  {cont__39_12, &frame__39_3, 360, 360, 8, 25},
  {cont__39_13, &frame__39_3, 360, 360, 8, 41},
  {cont__39_17, &frame__39_3, 360, 360, 8, 79},
  {cont__39_24, &frame__39_3, 359, 362, 5, 34},
  {cont__39_28, &frame__39_3, 363, 363, 8, 25},
  {cont__39_29, &frame__39_3, 363, 363, 8, 40},
  {cont__39_32, &frame__39_3, 363, 364, 5, 67},
  {entry__39_1_update_each_item_from_down_to, NULL, 355, 355, 6, 22},
  {cont__39_2, &frame__39_1_update_each_item_from_down_to, 355, 364, 3, 68},
  {cont__39_36, &frame__39_1_update_each_item_from_down_to, },
  {entry__40_4, NULL, 376, 376, 36, 47},
  {cont__40_5, &frame__40_4, 376, 376, 5, 63},
  {cont__40_6, &frame__40_4, 376, 376, 63, 63},
  {entry__40_1_types__key_order_table_update_each_from_down_to, NULL, 375, 375, 6, 18},
  {cont__40_2, &frame__40_1_types__key_order_table_update_each_from_down_to, 375, 375, 6, 29},
  {cont__40_3, &frame__40_1_types__key_order_table_update_each_from_down_to, 375, 376, 3, 63},
  {cont__40_7, &frame__40_1_types__key_order_table_update_each_from_down_to, },
  {entry__41_4, NULL, 385, 385, 50, 61},
  {cont__41_5, &frame__41_4, 385, 385, 32, 66},
  {cont__41_6, &frame__41_4, 385, 385, 66, 66},
  {entry__41_1_types__key_order_table_update_each, NULL, 385, 385, 6, 18},
  {cont__41_2, &frame__41_1_types__key_order_table_update_each, 385, 385, 6, 29},
  {cont__41_3, &frame__41_1_types__key_order_table_update_each, 385, 385, 3, 66},
  {cont__41_7, &frame__41_1_types__key_order_table_update_each, }
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__std__is_a_key_order_table(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_key_order_table);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_key_order_table, attr);
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
static void type__key_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__key_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__key_of, attr);
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
static void type__value_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__value_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__value_of, attr);
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
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__key_order_table",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/key_order_table.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__key_order_table(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 70: $types::key_order_table types::generic_table
  initialize_maybe_future(var.types__key_order_table, get__types__generic_table());
  // 74: $empty_node types::object
  initialize_maybe_future(var._empty_node, get__types__object());
  // 387: register_collection_serializer "key_order_table" empty_key_order_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__26_1;
  arguments->slots[1] = get__empty_key_order_table();
  result_count = 0;
  myself = get__register_collection_serializer();
  func = myself->type;
  frame->cont = cont__84_1;
}
static void cont__84_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_1_remove_leftmost(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // node: 0
  // key: 1
  // value: 2
  // left: 3
  frame->slots[3] /* left */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* key */ = create_cell();
  frame->slots[2] /* value */ = create_cell();
  // 44: $$left left_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
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
  ((CELL *)frame->slots[3])->contents /* left */ = arguments->slots[0];
  // 46: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* left */;
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
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 46: ... :
  // 47:   remove_leftmost &left !key !value
  // 48:   !node.left_of left
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_4, 0);
  // 49: :
  // 50:   !key key_of(node)
  // 51:   !value value_of(node)
  // 52:   !node right_of(node)
  frame->slots[6] /* temp__3 */ = create_closure(entry__12_6, 0);
  // 45: if
  // 46:   left.is_defined:
  // 47:     remove_leftmost &left !key !value
  // 48:     !node.left_of left
  // 49:   :
  // 50:     !key key_of(node)
  // 51:     !value value_of(node)
  // 52:     !node right_of(node)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 3 ?
    frame->caller_result_count-3 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_10;
}
static void entry__12_4(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // left: 0
  // key: 1
  // value: 2
  // node: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* left */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  frame->slots[3] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 47: remove_leftmost &left !key !value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  result_count = 3;
  myself = var._remove_leftmost;
  func = myself->type;
  frame->cont = cont__12_5;
}
static void cont__12_5(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* left */ = arguments->slots[0];
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[1];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[2];
  // 48: !node.left_of left
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* left */;
  // 48: !node.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[3])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_6(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // key: 0
  // node: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[0]; /* node */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 50: !key key_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__12_7;
}
static void cont__12_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* key */ = arguments->slots[0];
  // 51: !value value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__12_8;
}
static void cont__12_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[0];
  // 52: !node right_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__12_9;
}
static void cont__12_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* node */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__12_10(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+3] = arguments->slots[i];
  }
  argument_count += 3;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* value */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_1_remove_rightmost(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // node: 0
  // key: 1
  // value: 2
  // right: 3
  frame->slots[3] /* right */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* key */ = create_cell();
  frame->slots[2] /* value */ = create_cell();
  // 60: $$right right_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__13_2;
}
static void cont__13_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* right */ = arguments->slots[0];
  // 62: right.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* right */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__13_3;
}
static void cont__13_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 62: ... :
  // 63:   remove_rightmost &right !key !value
  // 64:   !node.right_of right
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_4, 0);
  // 65: :
  // 66:   !key key_of(node)
  // 67:   !value value_of(node)
  // 68:   !node left_of(node)
  frame->slots[6] /* temp__3 */ = create_closure(entry__13_6, 0);
  // 61: if
  // 62:   right.is_defined:
  // 63:     remove_rightmost &right !key !value
  // 64:     !node.right_of right
  // 65:   :
  // 66:     !key key_of(node)
  // 67:     !value value_of(node)
  // 68:     !node left_of(node)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 3 ?
    frame->caller_result_count-3 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_10;
}
static void entry__13_4(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // right: 0
  // key: 1
  // value: 2
  // node: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  frame->slots[3] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: remove_rightmost &right !key !value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 3;
  myself = var._remove_rightmost;
  func = myself->type;
  frame->cont = cont__13_5;
}
static void cont__13_5(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[1];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[2];
  // 64: !node.right_of right
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* right */;
  // 64: !node.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[3])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_6(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // key: 0
  // node: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[0]; /* node */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 66: !key key_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__13_7;
}
static void cont__13_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* key */ = arguments->slots[0];
  // 67: !value value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__13_8;
}
static void cont__13_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[0];
  // 68: !node left_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__13_9;
}
static void cont__13_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* node */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_10(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+3] = arguments->slots[i];
  }
  argument_count += 3;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* value */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1_fetch_first(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // myself: 0
  // return: 1
  // left: 2
  frame->slots[1] /* return */ = create_continuation_with_exit(exit__18_1_fetch_first);
  frame->slots[2] /* left */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 83: $$left left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__18_2;
}
static void cont__18_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* left */ = arguments->slots[0];
  // 85: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_3;
}
static void cont__18_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 85: ... :
  // 86:   fetch_first &left $key $value
  // 87:   !myself.left_of left
  // 88:   return key value
  frame->slots[4] /* temp__2 */ = create_closure(entry__18_4, 0);
  // 89: :
  // 90:   $key key_of(myself)
  // 91:   $value value_of(myself)
  // 92:   !myself right_of(myself)
  // 93:   return key value
  frame->slots[5] /* temp__3 */ = create_closure(entry__18_6, 0);
  // 84: if
  // 85:   left.is_defined:
  // 86:     fetch_first &left $key $value
  // 87:     !myself.left_of left
  // 88:     return key value
  // 89:   :
  // 90:     $key key_of(myself)
  // 91:     $value value_of(myself)
  // 92:     !myself right_of(myself)
  // 93:     return key value
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
  frame->cont = cont__18_10;
}
static void entry__18_4(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // left: 0
  // myself: 1
  // return: 2
  // key: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* left */
  frame->slots[1] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[1]; /* return */
  frame->slots[3] /* key */ = create_future();
  frame->slots[4] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 86: fetch_first &left $key $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  result_count = 3;
  myself = var._fetch_first;
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* left */ = arguments->slots[0];
  frame->slots[5] /* temp__1 */ = arguments->slots[1];
  frame->slots[6] /* temp__2 */ = arguments->slots[2];
  // 86: ... key
  initialize_future(frame->slots[3] /* key */, frame->slots[5] /* temp__1 */);
  // 86: ... value
  initialize_future(frame->slots[4] /* value */, frame->slots[6] /* temp__2 */);
  // 87: !myself.left_of left
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* left */;
  // 87: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* myself */ = temp;

  }
  // 88: return key value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* key */;
  arguments->slots[1] = frame->slots[4] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_6(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // return: 1
  // key: 2
  // value: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* key */ = create_future();
  frame->slots[3] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: $key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__18_7;
}
static void cont__18_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* key */, arguments->slots[0]);
  // 91: $value value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__18_8;
}
static void cont__18_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* value */, arguments->slots[0]);
  // 92: !myself right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__18_9;
}
static void cont__18_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* myself */ = arguments->slots[0];
  // 93: return key value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* key */;
  arguments->slots[1] = frame->slots[3] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_10(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__18_1_fetch_first(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  func = continuation_type_function;
}
static void entry__19_1_retrieve_item(void) {
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
  // 101: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__19_2;
}
static void cont__19_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 101: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_3, 0);
  // 101: if myself.is_undefined: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_4;
}
static void entry__19_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 101: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__19_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 102: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__19_5;
}
static void cont__19_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 104: -> key == my_key: return value_of(myself)
  frame->slots[4] /* temp__1 */ = create_closure(entry__19_6, 0);
  // 105: -> key < my_key: return retrieve_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_10, 0);
  // 106: -> key > my_key: return retrieve_item(right_of(myself) key)
  frame->slots[6] /* temp__3 */ = create_closure(entry__19_15, 0);
  // 103: cond
  // 104:   -> key == my_key: return value_of(myself)
  // 105:   -> key < my_key: return retrieve_item(left_of(myself) key)
  // 106:   -> key > my_key: return retrieve_item(right_of(myself) key)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__19_20;
}
static void entry__19_17(void) {
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
  // 106: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__19_18;
}
static void cont__19_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 106: ... retrieve_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__19_19;
}
static void cont__19_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 106: ... return retrieve_item(right_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_12(void) {
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
  // 105: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__19_13;
}
static void cont__19_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 105: ... retrieve_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__19_14;
}
static void cont__19_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 105: ... return retrieve_item(left_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_8(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // myself: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: ... value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__19_9;
}
static void cont__19_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 104: ... return value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_6(void) {
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
  // 104: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_7;
}
static void cont__19_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 104: ... : return value_of(myself)
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_8, 0);
  // 104: -> key == my_key: return value_of(myself)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_10(void) {
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
  // 105: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__19_11;
}
static void cont__19_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 105: ... : return retrieve_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_12, 0);
  // 105: -> key < my_key: return retrieve_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_15(void) {
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
  // 106: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__19_16;
}
static void cont__19_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 106: ... : return retrieve_item(right_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_17, 0);
  // 106: -> key > my_key: return retrieve_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_20(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__20_1_add_item(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // myself: 0
  // key: 1
  // value: 2
  // return: 3
  // my_key: 4
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* my_key */ = create_future();
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 115: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 115: ... : return empty_node(.key_of key .value_of value) INSERT
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_3, 0);
  // 115: if myself.is_undefined: return empty_node(.key_of key .value_of value) INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__20_4;
}
static void entry__20_3(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // key: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: ... empty_node(.key_of key .value_of value)
  {
    NODE *temp = clone_object_and_attributes(var._empty_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[1] /* key */);
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[2] /* value */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 115: ... return empty_node(.key_of key .value_of value) INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = var._INSERT;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__20_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 116: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__20_5;
}
static void cont__20_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* my_key */, arguments->slots[0]);
  // 118: -> key == my_key: return myself(.value_of value) UPDATE
  frame->slots[5] /* temp__1 */ = create_closure(entry__20_6, 0);
  // 119: -> key < my_key:
  // 120:   add_item $left $mode left_of(myself) key value
  // 121:   return myself(.left_of left) mode
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_9, 0);
  // 122: -> key > my_key:
  // 123:   add_item $right $mode right_of(myself) key value
  // 124:   return myself(.right_of right) mode
  frame->slots[7] /* temp__3 */ = create_closure(entry__20_14, 0);
  // 117: cond
  // 118:   -> key == my_key: return myself(.value_of value) UPDATE
  // 119:   -> key < my_key:
  // 120:     add_item $left $mode left_of(myself) key value
  // 121:     return myself(.left_of left) mode
  // 122:   -> key > my_key:
  // 123:     add_item $right $mode right_of(myself) key value
  // 124:     return myself(.right_of right) mode
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__20_19;
}
static void entry__20_16(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // myself: 0
  // key: 1
  // value: 2
  // return: 3
  // right: 4
  // mode: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* value */
  frame->slots[3] = myself->closure.frame->slots[4]; /* return */
  frame->slots[4] /* right */ = create_future();
  frame->slots[5] /* mode */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 123: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__20_17;
}
static void cont__20_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 123: add_item $right $mode right_of(myself) key value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[2] /* value */;
  result_count = 2;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__20_18;
}
static void cont__20_18(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  frame->slots[8] /* temp__3 */ = arguments->slots[1];
  // 123: ... right
  initialize_future(frame->slots[4] /* right */, frame->slots[7] /* temp__2 */);
  // 123: ... mode
  initialize_future(frame->slots[5] /* mode */, frame->slots[8] /* temp__3 */);
  // 124: ... myself(.right_of right)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* right */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 124: return myself(.right_of right) mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* mode */;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_11(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // myself: 0
  // key: 1
  // value: 2
  // return: 3
  // left: 4
  // mode: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* value */
  frame->slots[3] = myself->closure.frame->slots[4]; /* return */
  frame->slots[4] /* left */ = create_future();
  frame->slots[5] /* mode */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__20_12;
}
static void cont__20_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 120: add_item $left $mode left_of(myself) key value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[2] /* value */;
  result_count = 2;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__20_13;
}
static void cont__20_13(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  frame->slots[8] /* temp__3 */ = arguments->slots[1];
  // 120: ... left
  initialize_future(frame->slots[4] /* left */, frame->slots[7] /* temp__2 */);
  // 120: ... mode
  initialize_future(frame->slots[5] /* mode */, frame->slots[8] /* temp__3 */);
  // 121: ... myself(.left_of left)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* left */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 121: return myself(.left_of left) mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* mode */;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_8(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // myself: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: ... myself(.value_of value)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[2] /* value */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 118: ... return myself(.value_of value) UPDATE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = var._UPDATE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_6(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // key: 0
  // my_key: 1
  // return: 2
  // myself: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[4]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[4] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__20_7;
}
static void cont__20_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 118: ... : return myself(.value_of value) UPDATE
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_8, 0);
  // 118: -> key == my_key: return myself(.value_of value) UPDATE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_9(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // value: 3
  // return: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[4]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* value */
  frame->slots[4] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__20_10;
}
static void cont__20_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 119: ... :
  // 120:   add_item $left $mode left_of(myself) key value
  // 121:   return myself(.left_of left) mode
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_11, 0);
  // 119: -> key < my_key:
  // 120:   add_item $left $mode left_of(myself) key value
  // 121:   return myself(.left_of left) mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_14(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // my_key: 0
  // key: 1
  // myself: 2
  // value: 3
  // return: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* value */
  frame->slots[4] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 122: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__20_15;
}
static void cont__20_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 122: ... :
  // 123:   add_item $right $mode right_of(myself) key value
  // 124:   return myself(.right_of right) mode
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_16, 0);
  // 122: -> key > my_key:
  // 123:   add_item $right $mode right_of(myself) key value
  // 124:   return myself(.right_of right) mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__20_19(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__21_1_remove_item(void) {
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
  // 132: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__21_2;
}
static void cont__21_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 132: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_3, 0);
  // 132: if myself.is_undefined: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_4;
}
static void entry__21_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 132: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 133: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__21_5;
}
static void cont__21_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 135: -> key == my_key:
  // 136:   $left left_of(myself)
  // 137:   $$right right_of(myself)
  // 138:   if
  // 139:     left.is_defined:
  // 140:       if
  // 141:         right.is_defined:
  // 142:           fetch_first &right $head_key $head_value
  // 143:           return
  // 144:             types::object
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__21_6, 0);
  // 153: -> key < my_key:
  // 154:   $left remove_item(left_of(myself) key)
  // 155:   if NONE == left: return NONE # nothing removed
  // 156:   !myself.left_of left
  // 157:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_18, 0);
  // 158: -> key > my_key:
  // 159:   $right remove_item(right_of(myself) key)
  // 160:   if NONE == right: return NONE # nothing removed
  // 161:   !myself.right_of right
  // 162:   return myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_26, 0);
  // 134: cond
  // 135:   -> key == my_key:
  // 136:     $left left_of(myself)
  // 137:     $$right right_of(myself)
  // 138:     if
  // 139:       left.is_defined:
  // 140:         if
  // 141:           right.is_defined:
  // 142:             fetch_first &right $head_key $head_value
  // 143:             return
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__21_34;
}
static void entry__21_28(void) {
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
  // 159: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__21_29;
}
static void cont__21_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 159: $right remove_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__21_30;
}
static void cont__21_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* right */, arguments->slots[0]);
  // 160: ... NONE == right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* right */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_31;
}
static void cont__21_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 160: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_32, 0);
  // 160: if NONE == right: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_33;
}
static void entry__21_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 160: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 161: !myself.right_of right
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* right */;
  // 161: !myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 162: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_20(void) {
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
  // 154: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__21_21;
}
static void cont__21_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 154: $left remove_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__21_22;
}
static void cont__21_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* left */, arguments->slots[0]);
  // 155: ... NONE == left
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* left */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_23;
}
static void cont__21_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 155: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_24, 0);
  // 155: if NONE == left: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_25;
}
static void entry__21_24(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 155: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 156: !myself.left_of left
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* left */;
  // 156: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 157: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_14(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // right: 0
  // return: 1
  // left: 2
  // head_key: 3
  // head_value: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  frame->slots[3] /* head_key */ = create_future();
  frame->slots[4] /* head_value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 142: fetch_first &right $head_key $head_value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 3;
  myself = var._fetch_first;
  func = myself->type;
  frame->cont = cont__21_15;
}
static void cont__21_15(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  frame->slots[5] /* temp__1 */ = arguments->slots[1];
  frame->slots[6] /* temp__2 */ = arguments->slots[2];
  // 142: ... head_key
  initialize_future(frame->slots[3] /* head_key */, frame->slots[5] /* temp__1 */);
  // 142: ... head_value
  initialize_future(frame->slots[4] /* head_value */, frame->slots[6] /* temp__2 */);
  // 144: types::object
  // 145:   .key_of head_key
  // 146:   .value_of head_value
  // 147:   .left_of left
  // 148:   .right_of right
  {
    NODE *temp = clone_object_and_attributes(get__types__object());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[3] /* head_key */);
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* head_value */);
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[2] /* left */);
    set_attribute_value(temp->attributes, poly_idx__right_of, ((CELL *)frame->slots[0])->contents /* right */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 143: return
  // 144:   types::object
  // 145:     .key_of head_key
  // 146:     .value_of head_value
  // 147:     .left_of left
  // 148:     .right_of right
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_16(void) {
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
  // 150: return left
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* left */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_12(void) {
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
  // 141: right.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_13;
}
static void cont__21_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 141: ... :
  // 142:   fetch_first &right $head_key $head_value
  // 143:   return
  // 144:     types::object
  // 145:       .key_of head_key
  // 146:       .value_of head_value
  // 147:       .left_of left
  // 148:       .right_of right
  frame->slots[4] /* temp__2 */ = create_closure(entry__21_14, 0);
  // 149: :
  // 150:   return left
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_16, 0);
  // 140: if
  // 141:   right.is_defined:
  // 142:     fetch_first &right $head_key $head_value
  // 143:     return
  // 144:       types::object
  // 145:         .key_of head_key
  // 146:         .value_of head_value
  // 147:         .left_of left
  // 148:         .right_of right
  // 149:   :
  // ...
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
static void entry__21_17(void) {
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
  // 152: return right
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* right */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_8(void) {
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
  // 136: $left left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__21_9;
}
static void cont__21_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* left */, arguments->slots[0]);
  // 137: $$right right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__21_10;
}
static void cont__21_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* right */ = arguments->slots[0];
  // 139: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_11;
}
static void cont__21_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 139: ... :
  // 140:   if
  // 141:     right.is_defined:
  // 142:       fetch_first &right $head_key $head_value
  // 143:       return
  // 144:         types::object
  // 145:           .key_of head_key
  // 146:           .value_of head_value
  // 147:           .left_of left
  // 148:           .right_of right
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_12, 0);
  // 151: :
  // 152:   return right
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_17, 0);
  // 138: if
  // 139:   left.is_defined:
  // 140:     if
  // 141:       right.is_defined:
  // 142:         fetch_first &right $head_key $head_value
  // 143:         return
  // 144:           types::object
  // 145:             .key_of head_key
  // 146:             .value_of head_value
  // 147:             .left_of left
  // ...
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
static void entry__21_6(void) {
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
  // 135: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_7;
}
static void cont__21_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 135: ... :
  // 136:   $left left_of(myself)
  // 137:   $$right right_of(myself)
  // 138:   if
  // 139:     left.is_defined:
  // 140:       if
  // 141:         right.is_defined:
  // 142:           fetch_first &right $head_key $head_value
  // 143:           return
  // 144:             types::object
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_8, 0);
  // 135: -> key == my_key:
  // 136:   $left left_of(myself)
  // 137:   $$right right_of(myself)
  // 138:   if
  // 139:     left.is_defined:
  // 140:       if
  // 141:         right.is_defined:
  // 142:           fetch_first &right $head_key $head_value
  // 143:           return
  // 144:             types::object
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_18(void) {
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
  // 153: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__21_19;
}
static void cont__21_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 153: ... :
  // 154:   $left remove_item(left_of(myself) key)
  // 155:   if NONE == left: return NONE # nothing removed
  // 156:   !myself.left_of left
  // 157:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_20, 0);
  // 153: -> key < my_key:
  // 154:   $left remove_item(left_of(myself) key)
  // 155:   if NONE == left: return NONE # nothing removed
  // 156:   !myself.left_of left
  // 157:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_26(void) {
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
  // 158: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__21_27;
}
static void cont__21_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 158: ... :
  // 159:   $right remove_item(right_of(myself) key)
  // 160:   if NONE == right: return NONE # nothing removed
  // 161:   !myself.right_of right
  // 162:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_28, 0);
  // 158: -> key > my_key:
  // 159:   $right remove_item(right_of(myself) key)
  // 160:   if NONE == right: return NONE # nothing removed
  // 161:   !myself.right_of right
  // 162:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_34(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__22_1_types__key_order_table_private__set_item(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // key: 1
  // value: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 173: value.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* value */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__22_2;
}
static void cont__22_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 173: ... :
  // 174:   $new_tree remove_item(tree_of(self) key)
  // 175:   if NONE != new_tree:
  // 176:     !self.tree_of new_tree
  // 177:     dec &self.length_of
  frame->slots[4] /* temp__2 */ = create_closure(entry__22_3, 0);
  // 178: :
  // 179:   add_item $new_tree $mode tree_of(self) key value
  // 180:   !self.tree_of new_tree
  // 181:   if mode == INSERT: inc &self.length_of
  frame->slots[5] /* temp__3 */ = create_closure(entry__22_11, 0);
  // 172: if
  // 173:   value.is_undefined:
  // 174:     $new_tree remove_item(tree_of(self) key)
  // 175:     if NONE != new_tree:
  // 176:       !self.tree_of new_tree
  // 177:       dec &self.length_of
  // 178:   :
  // 179:     add_item $new_tree $mode tree_of(self) key value
  // 180:     !self.tree_of new_tree
  // 181:     if mode == INSERT: inc &self.length_of
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
  frame->cont = cont__22_18;
}
static void entry__22_15(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 181: ... self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__22_16;
}
static void cont__22_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 181: ... inc &self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__22_17;
}
static void cont__22_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 181: ... &self.length_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__length_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // new_tree: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_tree */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: !self.tree_of new_tree
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_tree */;
  // 176: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 177: ... self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__22_9;
}
static void cont__22_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 177: dec &self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__22_10;
}
static void cont__22_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 177: ... &self.length_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__length_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_3(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // key: 1
  // new_tree: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] /* new_tree */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__22_4;
}
static void cont__22_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 174: $new_tree remove_item(tree_of(self) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__22_5;
}
static void cont__22_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* new_tree */, arguments->slots[0]);
  // 175: ... NONE != new_tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[2] /* new_tree */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__22_6;
}
static void cont__22_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 175: ... NONE != new_tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_7;
}
static void cont__22_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 175: ... :
  // 176:   !self.tree_of new_tree
  // 177:   dec &self.length_of
  frame->slots[5] /* temp__3 */ = create_closure(entry__22_8, 0);
  // 175: if NONE != new_tree:
  // 176:   !self.tree_of new_tree
  // 177:   dec &self.length_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_11(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // self: 0
  // key: 1
  // value: 2
  // new_tree: 3
  // mode: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  frame->slots[3] /* new_tree */ = create_future();
  frame->slots[4] /* mode */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__22_12;
}
static void cont__22_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 179: add_item $new_tree $mode tree_of(self) key value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[2] /* value */;
  result_count = 2;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__22_13;
}
static void cont__22_13(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  frame->slots[7] /* temp__3 */ = arguments->slots[1];
  // 179: ... new_tree
  initialize_future(frame->slots[3] /* new_tree */, frame->slots[6] /* temp__2 */);
  // 179: ... mode
  initialize_future(frame->slots[4] /* mode */, frame->slots[7] /* temp__3 */);
  // 180: !self.tree_of new_tree
  frame->slots[5] /* temp__1 */ = frame->slots[3] /* new_tree */;
  // 180: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 181: ... mode == INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mode */;
  arguments->slots[1] = var._INSERT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__22_14;
}
static void cont__22_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 181: ... : inc &self.length_of
  frame->slots[6] /* temp__2 */ = create_closure(entry__22_15, 0);
  // 181: if mode == INSERT: inc &self.length_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__22_18(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_1_types__key_order_table_private__get_item(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // key: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 190: ... tree_of(self)
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 190: retrieve_item tree_of(self) key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = frame->caller_result_count;
  myself = var._retrieve_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__27_1_types__key_order_table_new_empty_collection(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 208: -> types::key_order_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__key_order_table;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_1_std__key_order_table(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // initializers: 0
  // tab: 1
  frame->slots[1] /* tab */ = create_cell();
  frame->slots[0] /* initializers */ = from_arguments(0, argument_count-0);
  // 227: $$tab types::key_order_table
  ((CELL *)frame->slots[1])->contents /* tab */ = var.types__key_order_table;
  // 228: ... : (initializer)
  // 229:   !tab(std::key_of(initializer)) std::value_of(initializer)
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_2, 1);
  // 228: for_each initializers: (initializer)
  // 229:   !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializers */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__29_6;
}
static void entry__29_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // initializer: 0
  // tab: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* tab */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 229: !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializer */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__29_3;
}
static void cont__29_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 229: ... std::key_of(initializer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializer */;
  result_count = 1;
  myself = get__std__key_of();
  func = myself->type;
  frame->cont = cont__29_4;
}
static void cont__29_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 229: !tab(std::key_of(initializer))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* tab */;
  func = myself->type;
  frame->cont = cont__29_5;
}
static void cont__29_5(void) {
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
static void cont__29_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 230: -> tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* tab */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_3(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // myself: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 234: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__30_4;
}
static void cont__30_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 234: for_each_item left_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = 0;
  myself = var._for_each_item;
  func = myself->type;
  frame->cont = cont__30_5;
}
static void cont__30_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 236: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__30_6;
}
static void cont__30_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 236: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_7;
}
static void cont__30_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 236: ... :
  // 237:   body key_of(myself) value_of(myself)
  frame->slots[4] /* temp__3 */ = create_closure(entry__30_8, 0);
  // 238: :
  // 239:   body value_of(myself)
  frame->slots[5] /* temp__4 */ = create_closure(entry__30_11, 0);
  // 235: if
  // 236:   parameter_count_of(body) == 2:
  // 237:     body key_of(myself) value_of(myself)
  // 238:   :
  // 239:     body value_of(myself)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_13;
}
static void entry__30_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // body: 0
  // myself: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 237: ... key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__30_9;
}
static void cont__30_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 237: ... value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__30_10;
}
static void cont__30_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 237: body key_of(myself) value_of(myself)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_11(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // body: 0
  // myself: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 239: ... value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__30_12;
}
static void cont__30_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 239: body value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 240: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__30_14;
}
static void cont__30_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 240: for_each_item right_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_1_for_each_item(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 233: ... myself.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_2;
}
static void cont__30_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 233: ... :
  // 234:   for_each_item left_of(myself) body
  // 235:   if
  // 236:     parameter_count_of(body) == 2:
  // 237:       body key_of(myself) value_of(myself)
  // 238:     :
  // 239:       body value_of(myself)
  // 240:   for_each_item right_of(myself) body
  frame->slots[3] /* temp__2 */ = create_closure(entry__30_3, 0);
  // 233: if myself.is_defined:
  // 234:   for_each_item left_of(myself) body
  // 235:   if
  // 236:     parameter_count_of(body) == 2:
  // 237:       body key_of(myself) value_of(myself)
  // 238:     :
  // 239:       body value_of(myself)
  // 240:   for_each_item right_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__31_4(void) {
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
  // 250: ... for_each_item tree body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__31_1_types__key_order_table_for_each(void) {
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
  // 249: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__31_2;
}
static void cont__31_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* tree */, arguments->slots[0]);
  // 250: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__31_3;
}
static void cont__31_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 250: ... : for_each_item tree body
  frame->slots[4] /* temp__2 */ = create_closure(entry__31_4, 0);
  // 250: if tree.is_defined: for_each_item tree body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_36(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // myself: 0
  // first: 1
  // last: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 266: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__32_37;
}
static void cont__32_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 266: for_each_item_from_to right_of(myself) first last body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* first */;
  arguments->slots[2] = frame->slots[2] /* last */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item_from_to;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_3(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // myself: 0
  // first: 1
  // last: 2
  // body: 3
  // key: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] /* key */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 254: $key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__32_4;
}
static void cont__32_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* key */, arguments->slots[0]);
  // 255: ... first.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__32_5;
}
static void cont__32_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 255: ... first < key
  frame->slots[7] /* temp__3 */ = create_closure(entry__32_6, 0);
  // 255: ... first.is_undefined || first < key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__32_8;
}
static void entry__32_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // first: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* first */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 255: ... first < key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__32_7;
}
static void cont__32_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 255: ... first < key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__32_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 255: ... :
  // 256:   for_each_item_from_to left_of(myself) first last body
  frame->slots[8] /* temp__4 */ = create_closure(entry__32_9, 0);
  // 255: if first.is_undefined || first < key:
  // 256:   for_each_item_from_to left_of(myself) first last body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__32_11;
}
static void entry__32_9(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // myself: 0
  // first: 1
  // last: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 256: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__32_10;
}
static void cont__32_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 256: for_each_item_from_to left_of(myself) first last body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* first */;
  arguments->slots[2] = frame->slots[2] /* last */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item_from_to;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__32_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 258: ... first.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__32_12;
}
static void cont__32_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 258: ... key >= first
  frame->slots[8] /* temp__4 */ = create_closure(entry__32_13, 0);
  // 258: ... first.is_undefined || key >= first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__32_16;
}
static void entry__32_13(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // key: 0
  // first: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 258: ... key >= first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__32_14;
}
static void cont__32_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 258: ... key >= first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__32_15;
}
static void cont__32_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 258: ... key >= first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__32_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 258: ... last.is_undefined || key <= last
  frame->slots[9] /* temp__5 */ = create_closure(entry__32_17, 0);
  // 258: ... first.is_undefined || key >= first) && (last.is_undefined || key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__32_23;
}
static void entry__32_17(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // last: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* last */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 258: ... last.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__32_18;
}
static void cont__32_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 258: ... key <= last
  frame->slots[4] /* temp__3 */ = create_closure(entry__32_19, 0);
  // 258: ... last.is_undefined || key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__32_22;
}
static void entry__32_19(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // last: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* last */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 258: ... key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__32_20;
}
static void cont__32_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 258: ... key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__32_21;
}
static void cont__32_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 258: ... key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__32_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 258: ... last.is_undefined || key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__32_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 259: :
  // 260:   if
  // 261:     parameter_count_of(body) == 2:
  // 262:       body key value_of(myself)
  // 263:     :
  // 264:       body value_of(myself)
  frame->slots[10] /* temp__6 */ = create_closure(entry__32_24, 0);
  // 257: if
  // 258:   (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 259:   :
  // 260:     if
  // 261:       parameter_count_of(body) == 2:
  // 262:         body key value_of(myself)
  // 263:       :
  // 264:         body value_of(myself)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__32_31;
}
static void entry__32_27(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // key: 1
  // myself: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 262: ... value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__32_28;
}
static void cont__32_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 262: body key value_of(myself)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_29(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // body: 0
  // myself: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 264: ... value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__32_30;
}
static void cont__32_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 264: body value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_24(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // body: 0
  // key: 1
  // myself: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 261: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__32_25;
}
static void cont__32_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 261: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__32_26;
}
static void cont__32_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 261: ... :
  // 262:   body key value_of(myself)
  frame->slots[5] /* temp__3 */ = create_closure(entry__32_27, 0);
  // 263: :
  // 264:   body value_of(myself)
  frame->slots[6] /* temp__4 */ = create_closure(entry__32_29, 0);
  // 260: if
  // 261:   parameter_count_of(body) == 2:
  // 262:     body key value_of(myself)
  // 263:   :
  // 264:     body value_of(myself)
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
static void cont__32_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 265: ... last.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* last */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__32_32;
}
static void cont__32_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 265: ... last > key
  frame->slots[7] /* temp__3 */ = create_closure(entry__32_33, 0);
  // 265: ... last.is_undefined || last > key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__32_35;
}
static void entry__32_33(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // key: 0
  // last: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 265: ... last > key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__32_34;
}
static void cont__32_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 265: ... last > key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__32_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 265: ... :
  // 266:   for_each_item_from_to right_of(myself) first last body
  frame->slots[8] /* temp__4 */ = create_closure(entry__32_36, 0);
  // 265: if last.is_undefined || last > key:
  // 266:   for_each_item_from_to right_of(myself) first last body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_1_for_each_item_from_to(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // myself: 0
  // first: 1
  // last: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 253: ... myself.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__32_2;
}
static void cont__32_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 253: ... :
  // 254:   $key key_of(myself)
  // 255:   if first.is_undefined || first < key:
  // 256:     for_each_item_from_to left_of(myself) first last body
  // 257:   if
  // 258:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 259:     :
  // 260:       if
  // 261:         parameter_count_of(body) == 2:
  // 262:           body key value_of(myself)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__32_3, 0);
  // 253: if myself.is_defined:
  // 254:   $key key_of(myself)
  // 255:   if first.is_undefined || first < key:
  // 256:     for_each_item_from_to left_of(myself) first last body
  // 257:   if
  // 258:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 259:     :
  // 260:       if
  // 261:         parameter_count_of(body) == 2:
  // 262:           body key value_of(myself)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_4(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // tree: 0
  // first: 1
  // last: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 278: ... for_each_item_from_to tree first last body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = frame->slots[1] /* first */;
  arguments->slots[2] = frame->slots[2] /* last */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item_from_to;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_1_types__key_order_table_for_each_from_to(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  // tree: 4
  frame->slots[4] /* tree */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 277: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__33_2;
}
static void cont__33_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* tree */, arguments->slots[0]);
  // 278: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_3;
}
static void cont__33_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 278: ... : for_each_item_from_to tree first last body
  frame->slots[6] /* temp__2 */ = create_closure(entry__33_4, 0);
  // 278: if tree.is_defined: for_each_item_from_to tree first last body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_36(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // myself: 0
  // last: 1
  // first: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 294: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__34_37;
}
static void cont__34_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 294: for_each_item_from_down_to left_of(myself) last first body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* first */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item_from_down_to;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_3(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // myself: 0
  // last: 1
  // first: 2
  // body: 3
  // key: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] /* key */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 282: $key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__34_4;
}
static void cont__34_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* key */, arguments->slots[0]);
  // 283: ... last.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__34_5;
}
static void cont__34_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 283: ... last > key
  frame->slots[7] /* temp__3 */ = create_closure(entry__34_6, 0);
  // 283: ... last.is_undefined || last > key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__34_8;
}
static void entry__34_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // key: 0
  // last: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 283: ... last > key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__34_7;
}
static void cont__34_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 283: ... last > key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 283: ... :
  // 284:   for_each_item_from_down_to right_of(myself) last first body
  frame->slots[8] /* temp__4 */ = create_closure(entry__34_9, 0);
  // 283: if last.is_undefined || last > key:
  // 284:   for_each_item_from_down_to right_of(myself) last first body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_11;
}
static void entry__34_9(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // myself: 0
  // last: 1
  // first: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__34_10;
}
static void cont__34_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 284: for_each_item_from_down_to right_of(myself) last first body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* first */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item_from_down_to;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 286: ... first.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* first */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__34_12;
}
static void cont__34_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 286: ... key >= first
  frame->slots[8] /* temp__4 */ = create_closure(entry__34_13, 0);
  // 286: ... first.is_undefined || key >= first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__34_16;
}
static void entry__34_13(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // key: 0
  // first: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 286: ... key >= first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__34_14;
}
static void cont__34_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 286: ... key >= first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__34_15;
}
static void cont__34_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 286: ... key >= first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 286: ... last.is_undefined || key <= last
  frame->slots[9] /* temp__5 */ = create_closure(entry__34_17, 0);
  // 286: ... first.is_undefined || key >= first) && (last.is_undefined || key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__34_23;
}
static void entry__34_17(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // last: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* last */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 286: ... last.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__34_18;
}
static void cont__34_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 286: ... key <= last
  frame->slots[4] /* temp__3 */ = create_closure(entry__34_19, 0);
  // 286: ... last.is_undefined || key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__34_22;
}
static void entry__34_19(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // last: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* last */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 286: ... key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__34_20;
}
static void cont__34_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 286: ... key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__34_21;
}
static void cont__34_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 286: ... key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 286: ... last.is_undefined || key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 287: :
  // 288:   if
  // 289:     parameter_count_of(body) == 2:
  // 290:       body key value_of(myself)
  // 291:     :
  // 292:       body value_of(myself)
  frame->slots[10] /* temp__6 */ = create_closure(entry__34_24, 0);
  // 285: if
  // 286:   (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 287:   :
  // 288:     if
  // 289:       parameter_count_of(body) == 2:
  // 290:         body key value_of(myself)
  // 291:       :
  // 292:         body value_of(myself)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_31;
}
static void entry__34_27(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // key: 1
  // myself: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 290: ... value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__34_28;
}
static void cont__34_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 290: body key value_of(myself)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_29(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // body: 0
  // myself: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 292: ... value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__34_30;
}
static void cont__34_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 292: body value_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_24(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // body: 0
  // key: 1
  // myself: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 289: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__34_25;
}
static void cont__34_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 289: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_26;
}
static void cont__34_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 289: ... :
  // 290:   body key value_of(myself)
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_27, 0);
  // 291: :
  // 292:   body value_of(myself)
  frame->slots[6] /* temp__4 */ = create_closure(entry__34_29, 0);
  // 288: if
  // 289:   parameter_count_of(body) == 2:
  // 290:     body key value_of(myself)
  // 291:   :
  // 292:     body value_of(myself)
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
static void cont__34_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 293: ... first.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* first */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__34_32;
}
static void cont__34_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 293: ... first < key
  frame->slots[7] /* temp__3 */ = create_closure(entry__34_33, 0);
  // 293: ... first.is_undefined || first < key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__34_35;
}
static void entry__34_33(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // first: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* first */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 293: ... first < key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__34_34;
}
static void cont__34_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 293: ... first < key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 293: ... :
  // 294:   for_each_item_from_down_to left_of(myself) last first body
  frame->slots[8] /* temp__4 */ = create_closure(entry__34_36, 0);
  // 293: if first.is_undefined || first < key:
  // 294:   for_each_item_from_down_to left_of(myself) last first body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_1_for_each_item_from_down_to(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // myself: 0
  // last: 1
  // first: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 281: ... myself.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_2;
}
static void cont__34_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 281: ... :
  // 282:   $key key_of(myself)
  // 283:   if last.is_undefined || last > key:
  // 284:     for_each_item_from_down_to right_of(myself) last first body
  // 285:   if
  // 286:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 287:     :
  // 288:       if
  // 289:         parameter_count_of(body) == 2:
  // 290:           body key value_of(myself)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_3, 0);
  // 281: if myself.is_defined:
  // 282:   $key key_of(myself)
  // 283:   if last.is_undefined || last > key:
  // 284:     for_each_item_from_down_to right_of(myself) last first body
  // 285:   if
  // 286:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 287:     :
  // 288:       if
  // 289:         parameter_count_of(body) == 2:
  // 290:           body key value_of(myself)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_4(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // tree: 0
  // last: 1
  // first: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: ... for_each_item_from_down_to tree last first body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* first */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item_from_down_to;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_1_types__key_order_table_for_each_from_down_to(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // self: 0
  // last: 1
  // first: 2
  // body: 3
  // tree: 4
  frame->slots[4] /* tree */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 305: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__35_2;
}
static void cont__35_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* tree */, arguments->slots[0]);
  // 306: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__35_3;
}
static void cont__35_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 306: ... : for_each_item_from_down_to tree last first body
  frame->slots[6] /* temp__2 */ = create_closure(entry__35_4, 0);
  // 306: if tree.is_defined: for_each_item_from_down_to tree last first body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_1_update_each_item(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 313: ... myself.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_2;
}
static void cont__36_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 313: ... :
  // 314:   update_each_item &myself.left_of body
  // 315:   body key_of(myself) &myself.value_of
  // 316:   update_each_item &myself.right_of body
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_3, 0);
  // 313: if myself.is_defined:
  // 314:   update_each_item &myself.left_of body
  // 315:   body key_of(myself) &myself.value_of
  // 316:   update_each_item &myself.right_of body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_11;
}
static void entry__36_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // myself: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 314: ... myself.left_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 314: update_each_item &myself.left_of body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = 1;
  myself = var._update_each_item;
  func = myself->type;
  frame->cont = cont__36_5;
}
static void cont__36_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 314: ... &myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 315: ... key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__36_6;
}
static void cont__36_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 315: ... myself.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__36_7;
}
static void cont__36_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 315: body key_of(myself) &myself.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__36_8;
}
static void cont__36_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 315: ... &myself.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 316: ... myself.right_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__36_9;
}
static void cont__36_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 316: update_each_item &myself.right_of body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = 1;
  myself = var._update_each_item;
  func = myself->type;
  frame->cont = cont__36_10;
}
static void cont__36_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 316: ... &myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_11(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_1_update_each_item_from_to(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // myself: 0
  // first: 1
  // last: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 325: ... myself.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_2;
}
static void cont__37_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 325: ... :
  // 326:   $key key_of(myself)
  // 327:   if first.is_undefined || first < key:
  // 328:     update_each_item_from_to &myself.left_of first last body
  // 329:   if
  // 330:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 331:     :
  // 332:       body key &myself.value_of
  // 333:   if last.is_undefined || last > key:
  // 334:     update_each_item_from_to &myself.right_of first last body
  frame->slots[5] /* temp__2 */ = create_closure(entry__37_3, 0);
  // 325: if myself.is_defined:
  // 326:   $key key_of(myself)
  // 327:   if first.is_undefined || first < key:
  // 328:     update_each_item_from_to &myself.left_of first last body
  // 329:   if
  // 330:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 331:     :
  // 332:       body key &myself.value_of
  // 333:   if last.is_undefined || last > key:
  // 334:     update_each_item_from_to &myself.right_of first last body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_36;
}
static void entry__37_33(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // myself: 0
  // first: 1
  // last: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 334: ... myself.right_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__37_34;
}
static void cont__37_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 334: update_each_item_from_to &myself.right_of first last body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* first */;
  arguments->slots[2] = frame->slots[2] /* last */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = 1;
  myself = var._update_each_item_from_to;
  func = myself->type;
  frame->cont = cont__37_35;
}
static void cont__37_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 334: ... &myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[5] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_3(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // myself: 0
  // first: 1
  // last: 2
  // body: 3
  // key: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] /* key */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 326: $key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__37_4;
}
static void cont__37_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* key */, arguments->slots[0]);
  // 327: ... first.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__37_5;
}
static void cont__37_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 327: ... first < key
  frame->slots[7] /* temp__3 */ = create_closure(entry__37_6, 0);
  // 327: ... first.is_undefined || first < key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__37_8;
}
static void entry__37_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // first: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* first */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 327: ... first < key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__37_7;
}
static void cont__37_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 327: ... first < key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 327: ... :
  // 328:   update_each_item_from_to &myself.left_of first last body
  frame->slots[8] /* temp__4 */ = create_closure(entry__37_9, 0);
  // 327: if first.is_undefined || first < key:
  // 328:   update_each_item_from_to &myself.left_of first last body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_12;
}
static void entry__37_9(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // myself: 0
  // first: 1
  // last: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 328: ... myself.left_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__37_10;
}
static void cont__37_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 328: update_each_item_from_to &myself.left_of first last body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* first */;
  arguments->slots[2] = frame->slots[2] /* last */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = 1;
  myself = var._update_each_item_from_to;
  func = myself->type;
  frame->cont = cont__37_11;
}
static void cont__37_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 328: ... &myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[5] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 330: ... first.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__37_13;
}
static void cont__37_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 330: ... key >= first
  frame->slots[8] /* temp__4 */ = create_closure(entry__37_14, 0);
  // 330: ... first.is_undefined || key >= first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__37_17;
}
static void entry__37_14(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // key: 0
  // first: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 330: ... key >= first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__37_15;
}
static void cont__37_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 330: ... key >= first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__37_16;
}
static void cont__37_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 330: ... key >= first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 330: ... last.is_undefined || key <= last
  frame->slots[9] /* temp__5 */ = create_closure(entry__37_18, 0);
  // 330: ... first.is_undefined || key >= first) && (last.is_undefined || key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__37_24;
}
static void entry__37_18(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // last: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* last */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 330: ... last.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__37_19;
}
static void cont__37_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 330: ... key <= last
  frame->slots[4] /* temp__3 */ = create_closure(entry__37_20, 0);
  // 330: ... last.is_undefined || key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__37_23;
}
static void entry__37_20(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // last: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* last */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 330: ... key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__37_21;
}
static void cont__37_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 330: ... key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__37_22;
}
static void cont__37_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 330: ... key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 330: ... last.is_undefined || key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 331: :
  // 332:   body key &myself.value_of
  frame->slots[10] /* temp__6 */ = create_closure(entry__37_25, 0);
  // 329: if
  // 330:   (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 331:   :
  // 332:     body key &myself.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_28;
}
static void entry__37_25(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // body: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 332: ... myself.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__37_26;
}
static void cont__37_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 332: body key &myself.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__37_27;
}
static void cont__37_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 332: ... &myself.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 333: ... last.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* last */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__37_29;
}
static void cont__37_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 333: ... last > key
  frame->slots[7] /* temp__3 */ = create_closure(entry__37_30, 0);
  // 333: ... last.is_undefined || last > key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__37_32;
}
static void entry__37_30(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // key: 0
  // last: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... last > key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__37_31;
}
static void cont__37_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 333: ... last > key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 333: ... :
  // 334:   update_each_item_from_to &myself.right_of first last body
  frame->slots[8] /* temp__4 */ = create_closure(entry__37_33, 0);
  // 333: if last.is_undefined || last > key:
  // 334:   update_each_item_from_to &myself.right_of first last body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_36(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_1_types__key_order_table_update_each_from_to(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 345: ... tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__38_2;
}
static void cont__38_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 345: ... tree_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_3;
}
static void cont__38_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   update_each_item_from_to &self.tree_of first last body
  frame->slots[6] /* temp__3 */ = create_closure(entry__38_4, 0);
  // 345: if tree_of(self).is_defined:
  // 346:   update_each_item_from_to &self.tree_of first last body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_7;
}
static void entry__38_4(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 346: ... self.tree_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__38_5;
}
static void cont__38_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 346: update_each_item_from_to &self.tree_of first last body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* first */;
  arguments->slots[2] = frame->slots[2] /* last */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = 1;
  myself = var._update_each_item_from_to;
  func = myself->type;
  frame->cont = cont__38_6;
}
static void cont__38_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 346: ... &self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[5] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_7(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_1_update_each_item_from_down_to(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // myself: 0
  // last: 1
  // first: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 355: ... myself.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_2;
}
static void cont__39_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 355: ... :
  // 356:   $key key_of(myself)
  // 357:   if last.is_undefined || last > key:
  // 358:     update_each_item_from_down_to &myself.right_of last first body
  // 359:   if
  // 360:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 361:     :
  // 362:       body key &myself.value_of
  // 363:   if first.is_undefined || first < key:
  // 364:     update_each_item_from_down_to &myself.left_of last first body
  frame->slots[5] /* temp__2 */ = create_closure(entry__39_3, 0);
  // 355: if myself.is_defined:
  // 356:   $key key_of(myself)
  // 357:   if last.is_undefined || last > key:
  // 358:     update_each_item_from_down_to &myself.right_of last first body
  // 359:   if
  // 360:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 361:     :
  // 362:       body key &myself.value_of
  // 363:   if first.is_undefined || first < key:
  // 364:     update_each_item_from_down_to &myself.left_of last first body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_36;
}
static void entry__39_33(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // myself: 0
  // last: 1
  // first: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: ... myself.left_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__39_34;
}
static void cont__39_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 364: update_each_item_from_down_to &myself.left_of last first body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* first */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = 1;
  myself = var._update_each_item_from_down_to;
  func = myself->type;
  frame->cont = cont__39_35;
}
static void cont__39_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 364: ... &myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[5] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_3(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // myself: 0
  // last: 1
  // first: 2
  // body: 3
  // key: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] /* key */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 356: $key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__39_4;
}
static void cont__39_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* key */, arguments->slots[0]);
  // 357: ... last.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__39_5;
}
static void cont__39_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 357: ... last > key
  frame->slots[7] /* temp__3 */ = create_closure(entry__39_6, 0);
  // 357: ... last.is_undefined || last > key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__39_8;
}
static void entry__39_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // key: 0
  // last: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 357: ... last > key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__39_7;
}
static void cont__39_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 357: ... last > key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 357: ... :
  // 358:   update_each_item_from_down_to &myself.right_of last first body
  frame->slots[8] /* temp__4 */ = create_closure(entry__39_9, 0);
  // 357: if last.is_undefined || last > key:
  // 358:   update_each_item_from_down_to &myself.right_of last first body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_12;
}
static void entry__39_9(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // myself: 0
  // last: 1
  // first: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 358: ... myself.right_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__39_10;
}
static void cont__39_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 358: update_each_item_from_down_to &myself.right_of last first body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* first */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = 1;
  myself = var._update_each_item_from_down_to;
  func = myself->type;
  frame->cont = cont__39_11;
}
static void cont__39_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 358: ... &myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[5] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 360: ... first.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* first */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__39_13;
}
static void cont__39_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 360: ... key >= first
  frame->slots[8] /* temp__4 */ = create_closure(entry__39_14, 0);
  // 360: ... first.is_undefined || key >= first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__39_17;
}
static void entry__39_14(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // key: 0
  // first: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 360: ... key >= first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__39_15;
}
static void cont__39_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 360: ... key >= first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__39_16;
}
static void cont__39_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 360: ... key >= first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 360: ... last.is_undefined || key <= last
  frame->slots[9] /* temp__5 */ = create_closure(entry__39_18, 0);
  // 360: ... first.is_undefined || key >= first) && (last.is_undefined || key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__39_24;
}
static void entry__39_18(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // last: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* last */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 360: ... last.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__39_19;
}
static void cont__39_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 360: ... key <= last
  frame->slots[4] /* temp__3 */ = create_closure(entry__39_20, 0);
  // 360: ... last.is_undefined || key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__39_23;
}
static void entry__39_20(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // last: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* last */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 360: ... key <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__39_21;
}
static void cont__39_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 360: ... key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__39_22;
}
static void cont__39_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 360: ... key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 360: ... last.is_undefined || key <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 361: :
  // 362:   body key &myself.value_of
  frame->slots[10] /* temp__6 */ = create_closure(entry__39_25, 0);
  // 359: if
  // 360:   (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 361:   :
  // 362:     body key &myself.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_28;
}
static void entry__39_25(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // body: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 362: ... myself.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* myself */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__39_26;
}
static void cont__39_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 362: body key &myself.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__39_27;
}
static void cont__39_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 362: ... &myself.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 363: ... first.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* first */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__39_29;
}
static void cont__39_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 363: ... first < key
  frame->slots[7] /* temp__3 */ = create_closure(entry__39_30, 0);
  // 363: ... first.is_undefined || first < key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__39_32;
}
static void entry__39_30(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // first: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* first */
  frame->slots[1] = myself->closure.frame->slots[4]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 363: ... first < key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__39_31;
}
static void cont__39_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 363: ... first < key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 363: ... :
  // 364:   update_each_item_from_down_to &myself.left_of last first body
  frame->slots[8] /* temp__4 */ = create_closure(entry__39_33, 0);
  // 363: if first.is_undefined || first < key:
  // 364:   update_each_item_from_down_to &myself.left_of last first body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_36(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__40_1_types__key_order_table_update_each_from_down_to(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // self: 0
  // last: 1
  // first: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 375: ... tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__40_2;
}
static void cont__40_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 375: ... tree_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__40_3;
}
static void cont__40_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 375: ... :
  // 376:   update_each_item_from_down_to &self.tree_of last first body
  frame->slots[6] /* temp__3 */ = create_closure(entry__40_4, 0);
  // 375: if tree_of(self).is_defined:
  // 376:   update_each_item_from_down_to &self.tree_of last first body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__40_7;
}
static void entry__40_4(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // last: 1
  // first: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 376: ... self.tree_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__40_5;
}
static void cont__40_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 376: update_each_item_from_down_to &self.tree_of last first body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* first */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = 1;
  myself = var._update_each_item_from_down_to;
  func = myself->type;
  frame->cont = cont__40_6;
}
static void cont__40_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 376: ... &self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[5] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__40_7(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_1_types__key_order_table_update_each(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 385: ... tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__41_2;
}
static void cont__41_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 385: ... tree_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__41_3;
}
static void cont__41_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 385: ... : update_each_item &self.tree_of body
  frame->slots[4] /* temp__3 */ = create_closure(entry__41_4, 0);
  // 385: if tree_of(self).is_defined: update_each_item &self.tree_of body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__41_7;
}
static void entry__41_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 385: ... self.tree_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__41_5;
}
static void cont__41_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 385: ... update_each_item &self.tree_of body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = 1;
  myself = var._update_each_item;
  func = myself->type;
  frame->cont = cont__41_6;
}
static void cont__41_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 385: ... &self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__41_7(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__key_order_table(void) {
  var.std__is_a_key_order_table = collect_node(var.std__is_a_key_order_table);
  var._NONE = collect_node(var._NONE);
  var._INSERT = collect_node(var._INSERT);
  var._UPDATE = collect_node(var._UPDATE);
  var._tree_of = collect_node(var._tree_of);
  var._key_of = collect_node(var._key_of);
  var._value_of = collect_node(var._value_of);
  var._left_of = collect_node(var._left_of);
  var._right_of = collect_node(var._right_of);
  var._remove_leftmost = collect_node(var._remove_leftmost);
  var._remove_rightmost = collect_node(var._remove_rightmost);
  var.types__key_order_table = collect_node(var.types__key_order_table);
  var._empty_node = collect_node(var._empty_node);
  var._fetch_first = collect_node(var._fetch_first);
  var._retrieve_item = collect_node(var._retrieve_item);
  var._add_item = collect_node(var._add_item);
  var._remove_item = collect_node(var._remove_item);
  var.std__empty_key_order_table = collect_node(var.std__empty_key_order_table);
  var.std__key_order_table = collect_node(var.std__key_order_table);
  var._for_each_item = collect_node(var._for_each_item);
  var._for_each_item_from_to = collect_node(var._for_each_item_from_to);
  var._for_each_item_from_down_to = collect_node(var._for_each_item_from_down_to);
  var._update_each_item = collect_node(var._update_each_item);
  var._update_each_item_from_to = collect_node(var._update_each_item_from_to);
  var._update_each_item_from_down_to = collect_node(var._update_each_item_from_down_to);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__key_order_table(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_a_key_order_table", get__std__is_a_key_order_table, &poly_idx__std__is_a_key_order_table, &var.std__is_a_key_order_table);
  register_polymorphic_function_with_setter("_basic__types__key_order_table::tree_of", &poly_idx__tree_of);
  register_polymorphic_function_with_setter("_basic__types__key_order_table::key_of", &poly_idx__key_of);
  register_polymorphic_function_with_setter("_basic__types__key_order_table::value_of", &poly_idx__value_of);
  register_polymorphic_function_with_setter("_basic__types__key_order_table::left_of", &poly_idx__left_of);
  register_polymorphic_function_with_setter("_basic__types__key_order_table::right_of", &poly_idx__right_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__key_order_table(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__0 = from_uint32(0U);
  number__2 = from_uint32(2U);
  unique__NONE = register_unique_item("NONE");
  unique__INSERT = register_unique_item("INSERT");
  unique__UPDATE = register_unique_item("UPDATE");
  func__12_1_remove_leftmost = create_function(entry__12_1_remove_leftmost, 1);
  func__13_1_remove_rightmost = create_function(entry__13_1_remove_rightmost, 1);
  func__18_1_fetch_first = create_function(entry__18_1_fetch_first, 1);
  func__19_1_retrieve_item = create_function(entry__19_1_retrieve_item, 2);
  func__20_1_add_item = create_function(entry__20_1_add_item, 3);
  func__21_1_remove_item = create_function(entry__21_1_remove_item, 2);
  func__22_1_types__key_order_table_private__set_item = create_function(entry__22_1_types__key_order_table_private__set_item, 3);
  func__23_1_types__key_order_table_private__get_item = create_function(entry__23_1_types__key_order_table_private__get_item, 2);
  string__26_1 = from_latin_1_string("key_order_table", 15);
  func__27_1_types__key_order_table_new_empty_collection = create_function(entry__27_1_types__key_order_table_new_empty_collection, 1);
  func__29_1_std__key_order_table = create_function(entry__29_1_std__key_order_table, -1);
  func__30_1_for_each_item = create_function(entry__30_1_for_each_item, 2);
  func__31_1_types__key_order_table_for_each = create_function(entry__31_1_types__key_order_table_for_each, 2);
  func__32_1_for_each_item_from_to = create_function(entry__32_1_for_each_item_from_to, 4);
  func__33_1_types__key_order_table_for_each_from_to = create_function(entry__33_1_types__key_order_table_for_each_from_to, 4);
  func__34_1_for_each_item_from_down_to = create_function(entry__34_1_for_each_item_from_down_to, 4);
  func__35_1_types__key_order_table_for_each_from_down_to = create_function(entry__35_1_types__key_order_table_for_each_from_down_to, 4);
  func__36_1_update_each_item = create_function(entry__36_1_update_each_item, 2);
  func__37_1_update_each_item_from_to = create_function(entry__37_1_update_each_item_from_to, 4);
  func__38_1_types__key_order_table_update_each_from_to = create_function(entry__38_1_types__key_order_table_update_each_from_to, 4);
  func__39_1_update_each_item_from_down_to = create_function(entry__39_1_update_each_item_from_down_to, 4);
  func__40_1_types__key_order_table_update_each_from_down_to = create_function(entry__40_1_types__key_order_table_update_each_from_down_to, 4);
  func__41_1_types__key_order_table_update_each = create_function(entry__41_1_types__key_order_table_update_each, 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__key_order_table(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__key_order_table");
  set_used_namespaces(used_namespaces);
  assign_value(&var._NONE, unique__NONE);
  assign_value(&var._INSERT, unique__INSERT);
  assign_value(&var._UPDATE, unique__UPDATE);
  define_single_assign_static("types", "key_order_table", get__types__key_order_table, &var.types__key_order_table);
  define_single_assign_static("std", "empty_key_order_table", get__std__empty_key_order_table, &var.std__empty_key_order_table);
  define_single_assign_static("std", "key_order_table", get__std__key_order_table, &var.std__key_order_table);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__key_order_table(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__key_order_table");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "empty_key_order_table", &get__empty_key_order_table, &get_value_or_future__empty_key_order_table);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_polymorphic_function(NULL, "for_each_from_down_to", &get__for_each_from_down_to, &poly_idx__for_each_from_down_to);
  use_polymorphic_function(NULL, "for_each_from_to", &get__for_each_from_to, &poly_idx__for_each_from_to);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_polymorphic_function(NULL, "is_a_key_order_table", &get__is_a_key_order_table, &poly_idx__is_a_key_order_table);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_polymorphic_function(NULL, "length_of", &get__length_of, &poly_idx__length_of);
  use_polymorphic_function(NULL, "new_empty_collection", &get__new_empty_collection, &poly_idx__new_empty_collection);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_polymorphic_function("private", "get_item", &get__private__get_item, &poly_idx__private__get_item);
  use_polymorphic_function("private", "set_item", &get__private__set_item, &poly_idx__private__set_item);
  use_read_only(NULL, "register_collection_serializer", &get__register_collection_serializer, &get_value_or_future__register_collection_serializer);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_of", &get__std__key_of, &get_value_or_future__std__key_of);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "value_of", &get__std__value_of, &get_value_or_future__std__value_of);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "generic_table", &get__types__generic_table, &get_value_or_future__types__generic_table);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_polymorphic_function(NULL, "update_each", &get__update_each, &poly_idx__update_each);
  use_polymorphic_function(NULL, "update_each_from_down_to", &get__update_each_from_down_to, &poly_idx__update_each_from_down_to);
  use_polymorphic_function(NULL, "update_each_from_to", &get__update_each_from_to, &poly_idx__update_each_from_to);
  define_attribute("types", "object", poly_idx__is_a_key_order_table, get__false());
  define_attribute("types", "key_order_table", poly_idx__is_a_key_order_table, get__true());
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__left_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__right_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  define_method("types", "key_order_table", poly_idx__private__set_item, func__22_1_types__key_order_table_private__set_item);
  define_method("types", "key_order_table", poly_idx__private__get_item, func__23_1_types__key_order_table_private__get_item);
  define_attribute("types", "key_order_table", poly_idx__tree_of, get__undefined());
  define_attribute("types", "key_order_table", poly_idx__length_of, number__0);
  define_attribute("types", "key_order_table", poly_idx__serialization_tag_of, string__26_1);
  define_method("types", "key_order_table", poly_idx__new_empty_collection, func__27_1_types__key_order_table_new_empty_collection);
  define_method("types", "key_order_table", poly_idx__for_each, func__31_1_types__key_order_table_for_each);
  define_method("types", "key_order_table", poly_idx__for_each_from_to, func__33_1_types__key_order_table_for_each_from_to);
  define_method("types", "key_order_table", poly_idx__for_each_from_down_to, func__35_1_types__key_order_table_for_each_from_down_to);
  define_method("types", "key_order_table", poly_idx__update_each_from_to, func__38_1_types__key_order_table_update_each_from_to);
  define_method("types", "key_order_table", poly_idx__update_each_from_down_to, func__40_1_types__key_order_table_update_each_from_down_to);
  define_method("types", "key_order_table", poly_idx__update_each, func__41_1_types__key_order_table_update_each);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__key_order_table(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_key_order_table, create_function(type__std__is_a_key_order_table, -1));
  assign_value(&var._tree_of, create_function(type__tree_of, -1));
  assign_value(&var._key_of, create_function(type__key_of, -1));
  assign_value(&var._value_of, create_function(type__value_of, -1));
  assign_value(&var._left_of, create_function(type__left_of, -1));
  assign_value(&var._right_of, create_function(type__right_of, -1));
  assign_variable(&var._remove_leftmost, &func__12_1_remove_leftmost);
  assign_variable(&var._remove_rightmost, &func__13_1_remove_rightmost);
  assign_value(&var.types__key_order_table, get__types__generic_table());
  assign_value(&var._empty_node, get__types__object());
  assign_variable(&var._fetch_first, &func__18_1_fetch_first);
  assign_variable(&var._retrieve_item, &func__19_1_retrieve_item);
  assign_variable(&var._add_item, &func__20_1_add_item);
  assign_variable(&var._remove_item, &func__21_1_remove_item);
  assign_variable(&var.std__empty_key_order_table, &var.types__key_order_table);
  assign_variable(&var.std__key_order_table, &func__29_1_std__key_order_table);
  assign_variable(&var._for_each_item, &func__30_1_for_each_item);
  assign_variable(&var._for_each_item_from_to, &func__32_1_for_each_item_from_to);
  assign_variable(&var._for_each_item_from_down_to, &func__34_1_for_each_item_from_down_to);
  assign_variable(&var._update_each_item, &func__36_1_update_each_item);
  assign_variable(&var._update_each_item_from_to, &func__37_1_update_each_item_from_to);
  assign_variable(&var._update_each_item_from_down_to, &func__39_1_update_each_item_from_down_to);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__key_order_table(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__key_order_table);
}
