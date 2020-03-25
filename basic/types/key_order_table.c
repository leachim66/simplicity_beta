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
  {run__basic__types__key_order_table, NULL, 331, 331, 1, 70},
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
  {entry__18_4, NULL, 92, 92, 7, 35},
  {cont__18_5, &frame__18_4, 94, 94, 7, 22},
  {entry__18_6, NULL, 96, 96, 7, 25},
  {cont__18_7, &frame__18_6, 97, 97, 7, 29},
  {cont__18_8, &frame__18_6, 98, 98, 7, 30},
  {cont__18_9, &frame__18_6, 99, 99, 7, 22},
  {entry__18_1_fetch_first, NULL, 89, 89, 3, 24},
  {cont__18_2, &frame__18_1_fetch_first, 91, 91, 5, 19},
  {cont__18_3, &frame__18_1_fetch_first, 90, 99, 3, 23},
  {cont__18_10, &frame__18_1_fetch_first, 99, 99, 23, 23},
  {entry__19_3, NULL, 107, 107, 27, 42},
  {entry__19_8, NULL, 110, 110, 30, 45},
  {cont__19_9, &frame__19_8, 110, 110, 23, 45},
  {entry__19_6, NULL, 110, 110, 8, 20},
  {cont__19_7, &frame__19_6, 110, 110, 5, 45},
  {entry__19_12, NULL, 111, 111, 43, 57},
  {cont__19_13, &frame__19_12, 111, 111, 29, 62},
  {cont__19_14, &frame__19_12, 111, 111, 22, 62},
  {entry__19_10, NULL, 111, 111, 8, 19},
  {cont__19_11, &frame__19_10, 111, 111, 5, 62},
  {entry__19_17, NULL, 112, 112, 43, 58},
  {cont__19_18, &frame__19_17, 112, 112, 29, 63},
  {cont__19_19, &frame__19_17, 112, 112, 22, 63},
  {entry__19_15, NULL, 112, 112, 8, 19},
  {cont__19_16, &frame__19_15, 112, 112, 5, 63},
  {entry__19_1_retrieve_item, NULL, 107, 107, 6, 24},
  {cont__19_2, &frame__19_1_retrieve_item, 107, 107, 3, 42},
  {cont__19_4, &frame__19_1_retrieve_item, 108, 108, 3, 24},
  {cont__19_5, &frame__19_1_retrieve_item, 109, 112, 3, 63},
  {cont__19_20, &frame__19_1_retrieve_item, 112, 112, 63, 63},
  {entry__20_3, NULL, 121, 121, 27, 79},
  {entry__20_8, NULL, 124, 124, 23, 59},
  {entry__20_6, NULL, 124, 124, 8, 20},
  {cont__20_7, &frame__20_6, 124, 124, 5, 59},
  {entry__20_11, NULL, 126, 126, 28, 42},
  {cont__20_12, &frame__20_11, 126, 126, 7, 52},
  {cont__20_13, &frame__20_11, 127, 127, 7, 39},
  {entry__20_9, NULL, 125, 125, 8, 19},
  {cont__20_10, &frame__20_9, 125, 127, 5, 39},
  {entry__20_16, NULL, 129, 129, 29, 44},
  {cont__20_17, &frame__20_16, 129, 129, 7, 54},
  {cont__20_18, &frame__20_16, 130, 130, 7, 41},
  {entry__20_14, NULL, 128, 128, 8, 19},
  {cont__20_15, &frame__20_14, 128, 130, 5, 41},
  {entry__20_1_add_item, NULL, 121, 121, 6, 24},
  {cont__20_2, &frame__20_1_add_item, 121, 121, 3, 79},
  {cont__20_4, &frame__20_1_add_item, 122, 122, 3, 24},
  {cont__20_5, &frame__20_1_add_item, 123, 130, 3, 42},
  {cont__20_19, &frame__20_1_add_item, 130, 130, 42, 42},
  {entry__21_3, NULL, 138, 138, 27, 55},
  {entry__21_14, NULL, 148, 148, 15, 54},
  {cont__21_15, &frame__21_14, 149, 154, 15, 34},
  {entry__21_16, NULL, 156, 156, 15, 25},
  {entry__21_12, NULL, 147, 147, 13, 28},
  {cont__21_13, &frame__21_12, 146, 156, 11, 26},
  {entry__21_17, NULL, 158, 158, 11, 22},
  {entry__21_8, NULL, 142, 142, 7, 27},
  {cont__21_9, &frame__21_8, 143, 143, 7, 30},
  {cont__21_10, &frame__21_8, 145, 145, 9, 23},
  {cont__21_11, &frame__21_8, 144, 158, 7, 23},
  {entry__21_6, NULL, 141, 141, 8, 20},
  {cont__21_7, &frame__21_6, 141, 158, 5, 24},
  {entry__21_24, NULL, 161, 161, 24, 52},
  {entry__21_20, NULL, 160, 160, 25, 39},
  {cont__21_21, &frame__21_20, 160, 160, 7, 44},
  {cont__21_22, &frame__21_20, 161, 161, 10, 21},
  {cont__21_23, &frame__21_20, 161, 161, 7, 52},
  {cont__21_25, &frame__21_20, 163, 163, 7, 19},
  {entry__21_18, NULL, 159, 159, 8, 19},
  {cont__21_19, &frame__21_18, 159, 163, 5, 19},
  {entry__21_32, NULL, 166, 166, 25, 53},
  {entry__21_28, NULL, 165, 165, 26, 41},
  {cont__21_29, &frame__21_28, 165, 165, 7, 46},
  {cont__21_30, &frame__21_28, 166, 166, 10, 22},
  {cont__21_31, &frame__21_28, 166, 166, 7, 53},
  {cont__21_33, &frame__21_28, 168, 168, 7, 19},
  {entry__21_26, NULL, 164, 164, 8, 19},
  {cont__21_27, &frame__21_26, 164, 168, 5, 19},
  {entry__21_1_remove_item, NULL, 138, 138, 6, 24},
  {cont__21_2, &frame__21_1_remove_item, 138, 138, 3, 55},
  {cont__21_4, &frame__21_1_remove_item, 139, 139, 3, 24},
  {cont__21_5, &frame__21_1_remove_item, 140, 168, 3, 20},
  {cont__21_34, &frame__21_1_remove_item, 168, 168, 20, 20},
  {entry__22_8, NULL, 181, 181, 14, 27},
  {cont__22_9, &frame__22_8, 181, 181, 9, 27},
  {cont__22_10, &frame__22_8, 181, 181, 27, 27},
  {entry__22_3, NULL, 178, 178, 29, 41},
  {cont__22_4, &frame__22_3, 178, 178, 7, 46},
  {cont__22_5, &frame__22_3, 179, 179, 10, 25},
  {cont__22_6, &frame__22_3, 179, 179, 10, 25},
  {cont__22_7, &frame__22_3, 179, 181, 7, 27},
  {entry__22_15, NULL, 185, 185, 31, 44},
  {cont__22_16, &frame__22_15, 185, 185, 26, 44},
  {cont__22_17, &frame__22_15, 185, 185, 44, 44},
  {entry__22_11, NULL, 183, 183, 32, 44},
  {cont__22_12, &frame__22_11, 183, 183, 7, 54},
  {cont__22_13, &frame__22_11, 185, 185, 10, 23},
  {cont__22_14, &frame__22_11, 185, 185, 7, 44},
  {entry__22_1_types__key_order_table_private__set_item, NULL, 177, 177, 5, 22},
  {cont__22_2, &frame__22_1_types__key_order_table_private__set_item, 176, 185, 3, 45},
  {cont__22_18, &frame__22_1_types__key_order_table_private__set_item, },
  {entry__23_1_types__key_order_table_private__get_item, NULL, 188, 188, 17, 29},
  {cont__23_2, &frame__23_1_types__key_order_table_private__get_item, 188, 188, 3, 33},
  {entry__27_1_types__key_order_table_new_empty_collection, NULL, 194, 194, 55, 79},
  {entry__29_2, NULL, 201, 201, 5, 61},
  {cont__29_3, &frame__29_2, 201, 201, 10, 33},
  {cont__29_4, &frame__29_2, 201, 201, 5, 34},
  {cont__29_5, &frame__29_2, 201, 201, 61, 61},
  {entry__29_1_std__key_order_table, NULL, 200, 201, 3, 61},
  {cont__29_6, &frame__29_1_std__key_order_table, 202, 202, 3, 8},
  {entry__30_8, NULL, 209, 209, 14, 27},
  {cont__30_9, &frame__30_8, 209, 209, 29, 44},
  {cont__30_10, &frame__30_8, 209, 209, 9, 44},
  {entry__30_11, NULL, 211, 211, 14, 29},
  {cont__30_12, &frame__30_11, 211, 211, 9, 29},
  {entry__30_3, NULL, 206, 206, 19, 33},
  {cont__30_4, &frame__30_3, 206, 206, 5, 38},
  {cont__30_5, &frame__30_3, 208, 208, 7, 30},
  {cont__30_6, &frame__30_3, 208, 208, 7, 35},
  {cont__30_7, &frame__30_3, 207, 211, 5, 30},
  {cont__30_13, &frame__30_3, 212, 212, 19, 34},
  {cont__30_14, &frame__30_3, 212, 212, 5, 39},
  {entry__30_1_for_each_item, NULL, 205, 205, 6, 22},
  {cont__30_2, &frame__30_1_for_each_item, 205, 212, 3, 39},
  {entry__31_4, NULL, 216, 216, 23, 45},
  {entry__31_1_types__key_order_table_for_each, NULL, 215, 215, 3, 21},
  {cont__31_2, &frame__31_1_types__key_order_table_for_each, 216, 216, 6, 20},
  {cont__31_3, &frame__31_1_types__key_order_table_for_each, 216, 216, 3, 45},
  {entry__32_6, NULL, 221, 221, 30, 40},
  {cont__32_7, &frame__32_6, 221, 221, 30, 40},
  {entry__32_9, NULL, 222, 222, 29, 43},
  {cont__32_10, &frame__32_9, 222, 222, 7, 59},
  {entry__32_13, NULL, 224, 224, 30, 41},
  {cont__32_14, &frame__32_13, 224, 224, 30, 41},
  {cont__32_15, &frame__32_13, 224, 224, 30, 41},
  {entry__32_19, NULL, 224, 224, 69, 79},
  {cont__32_20, &frame__32_19, 224, 224, 69, 79},
  {cont__32_21, &frame__32_19, 224, 224, 69, 79},
  {entry__32_17, NULL, 224, 224, 48, 64},
  {cont__32_18, &frame__32_17, 224, 224, 48, 79},
  {cont__32_22, &frame__32_17, 224, 224, 48, 79},
  {entry__32_27, NULL, 228, 228, 22, 37},
  {cont__32_28, &frame__32_27, 228, 228, 13, 37},
  {entry__32_29, NULL, 230, 230, 18, 33},
  {cont__32_30, &frame__32_29, 230, 230, 13, 33},
  {entry__32_24, NULL, 227, 227, 11, 34},
  {cont__32_25, &frame__32_24, 227, 227, 11, 39},
  {cont__32_26, &frame__32_24, 226, 230, 9, 34},
  {entry__32_33, NULL, 231, 231, 29, 38},
  {cont__32_34, &frame__32_33, 231, 231, 29, 38},
  {entry__32_36, NULL, 232, 232, 29, 44},
  {cont__32_37, &frame__32_36, 232, 232, 7, 60},
  {entry__32_3, NULL, 220, 220, 5, 23},
  {cont__32_4, &frame__32_3, 221, 221, 8, 25},
  {cont__32_5, &frame__32_3, 221, 221, 8, 40},
  {cont__32_8, &frame__32_3, 221, 222, 5, 59},
  {cont__32_11, &frame__32_3, 224, 224, 8, 25},
  {cont__32_12, &frame__32_3, 224, 224, 8, 41},
  {cont__32_16, &frame__32_3, 224, 224, 8, 79},
  {cont__32_23, &frame__32_3, 223, 230, 5, 36},
  {cont__32_31, &frame__32_3, 231, 231, 8, 24},
  {cont__32_32, &frame__32_3, 231, 231, 8, 38},
  {cont__32_35, &frame__32_3, 231, 232, 5, 60},
  {entry__32_1_for_each_item_from_to, NULL, 219, 219, 6, 22},
  {cont__32_2, &frame__32_1_for_each_item_from_to, 219, 232, 3, 61},
  {entry__33_4, NULL, 236, 236, 23, 64},
  {entry__33_1_types__key_order_table_for_each_from_to, NULL, 235, 235, 3, 21},
  {cont__33_2, &frame__33_1_types__key_order_table_for_each_from_to, 236, 236, 6, 20},
  {cont__33_3, &frame__33_1_types__key_order_table_for_each_from_to, 236, 236, 3, 64},
  {entry__34_6, NULL, 241, 241, 29, 38},
  {cont__34_7, &frame__34_6, 241, 241, 29, 38},
  {entry__34_9, NULL, 242, 242, 34, 49},
  {cont__34_10, &frame__34_9, 242, 242, 7, 65},
  {entry__34_13, NULL, 244, 244, 30, 41},
  {cont__34_14, &frame__34_13, 244, 244, 30, 41},
  {cont__34_15, &frame__34_13, 244, 244, 30, 41},
  {entry__34_19, NULL, 244, 244, 69, 79},
  {cont__34_20, &frame__34_19, 244, 244, 69, 79},
  {cont__34_21, &frame__34_19, 244, 244, 69, 79},
  {entry__34_17, NULL, 244, 244, 48, 64},
  {cont__34_18, &frame__34_17, 244, 244, 48, 79},
  {cont__34_22, &frame__34_17, 244, 244, 48, 79},
  {entry__34_27, NULL, 248, 248, 22, 37},
  {cont__34_28, &frame__34_27, 248, 248, 13, 37},
  {entry__34_29, NULL, 250, 250, 18, 33},
  {cont__34_30, &frame__34_29, 250, 250, 13, 33},
  {entry__34_24, NULL, 247, 247, 11, 34},
  {cont__34_25, &frame__34_24, 247, 247, 11, 39},
  {cont__34_26, &frame__34_24, 246, 250, 9, 34},
  {entry__34_33, NULL, 251, 251, 30, 40},
  {cont__34_34, &frame__34_33, 251, 251, 30, 40},
  {entry__34_36, NULL, 252, 252, 34, 48},
  {cont__34_37, &frame__34_36, 252, 252, 7, 64},
  {entry__34_3, NULL, 240, 240, 5, 23},
  {cont__34_4, &frame__34_3, 241, 241, 8, 24},
  {cont__34_5, &frame__34_3, 241, 241, 8, 38},
  {cont__34_8, &frame__34_3, 241, 242, 5, 65},
  {cont__34_11, &frame__34_3, 244, 244, 8, 25},
  {cont__34_12, &frame__34_3, 244, 244, 8, 41},
  {cont__34_16, &frame__34_3, 244, 244, 8, 79},
  {cont__34_23, &frame__34_3, 243, 250, 5, 36},
  {cont__34_31, &frame__34_3, 251, 251, 8, 25},
  {cont__34_32, &frame__34_3, 251, 251, 8, 40},
  {cont__34_35, &frame__34_3, 251, 252, 5, 64},
  {entry__34_1_for_each_item_from_down_to, NULL, 239, 239, 6, 22},
  {cont__34_2, &frame__34_1_for_each_item_from_down_to, 239, 252, 3, 65},
  {entry__35_4, NULL, 256, 256, 23, 69},
  {entry__35_1_types__key_order_table_for_each_from_down_to, NULL, 255, 255, 3, 21},
  {cont__35_2, &frame__35_1_types__key_order_table_for_each_from_down_to, 256, 256, 6, 20},
  {cont__35_3, &frame__35_1_types__key_order_table_for_each_from_down_to, 256, 256, 3, 69},
  {entry__36_3, NULL, 264, 264, 23, 36},
  {cont__36_4, &frame__36_3, 264, 264, 5, 41},
  {cont__36_5, &frame__36_3, 265, 265, 10, 23},
  {cont__36_6, &frame__36_3, 265, 265, 26, 40},
  {cont__36_7, &frame__36_3, 265, 265, 5, 40},
  {cont__36_8, &frame__36_3, 266, 266, 23, 37},
  {cont__36_9, &frame__36_3, 266, 266, 5, 42},
  {cont__36_10, &frame__36_3, 266, 266, 42, 42},
  {entry__36_1_update_each_item, NULL, 263, 263, 6, 22},
  {cont__36_2, &frame__36_1_update_each_item, 263, 266, 3, 42},
  {cont__36_11, &frame__36_1_update_each_item, },
  {entry__37_6, NULL, 277, 277, 30, 40},
  {cont__37_7, &frame__37_6, 277, 277, 30, 40},
  {entry__37_9, NULL, 278, 278, 33, 46},
  {cont__37_10, &frame__37_9, 278, 278, 7, 62},
  {cont__37_11, &frame__37_9, 278, 278, 62, 62},
  {entry__37_14, NULL, 280, 280, 30, 41},
  {cont__37_15, &frame__37_14, 280, 280, 30, 41},
  {cont__37_16, &frame__37_14, 280, 280, 30, 41},
  {entry__37_20, NULL, 280, 280, 69, 79},
  {cont__37_21, &frame__37_20, 280, 280, 69, 79},
  {cont__37_22, &frame__37_20, 280, 280, 69, 79},
  {entry__37_18, NULL, 280, 280, 48, 64},
  {cont__37_19, &frame__37_18, 280, 280, 48, 79},
  {cont__37_23, &frame__37_18, 280, 280, 48, 79},
  {entry__37_25, NULL, 282, 282, 19, 33},
  {cont__37_26, &frame__37_25, 282, 282, 9, 33},
  {cont__37_27, &frame__37_25, 282, 282, 33, 33},
  {entry__37_30, NULL, 283, 283, 29, 38},
  {cont__37_31, &frame__37_30, 283, 283, 29, 38},
  {entry__37_33, NULL, 284, 284, 33, 47},
  {cont__37_34, &frame__37_33, 284, 284, 7, 63},
  {cont__37_35, &frame__37_33, 284, 284, 63, 63},
  {entry__37_3, NULL, 276, 276, 5, 23},
  {cont__37_4, &frame__37_3, 277, 277, 8, 25},
  {cont__37_5, &frame__37_3, 277, 277, 8, 40},
  {cont__37_8, &frame__37_3, 277, 278, 5, 62},
  {cont__37_12, &frame__37_3, 280, 280, 8, 25},
  {cont__37_13, &frame__37_3, 280, 280, 8, 41},
  {cont__37_17, &frame__37_3, 280, 280, 8, 79},
  {cont__37_24, &frame__37_3, 279, 282, 5, 34},
  {cont__37_28, &frame__37_3, 283, 283, 8, 24},
  {cont__37_29, &frame__37_3, 283, 283, 8, 38},
  {cont__37_32, &frame__37_3, 283, 284, 5, 63},
  {entry__37_1_update_each_item_from_to, NULL, 275, 275, 6, 22},
  {cont__37_2, &frame__37_1_update_each_item_from_to, 275, 284, 3, 64},
  {cont__37_36, &frame__37_1_update_each_item_from_to, },
  {entry__38_4, NULL, 294, 294, 31, 42},
  {cont__38_5, &frame__38_4, 294, 294, 5, 58},
  {cont__38_6, &frame__38_4, 294, 294, 58, 58},
  {entry__38_1_types__key_order_table_update_each_from_to, NULL, 293, 293, 6, 18},
  {cont__38_2, &frame__38_1_types__key_order_table_update_each_from_to, 293, 293, 6, 29},
  {cont__38_3, &frame__38_1_types__key_order_table_update_each_from_to, 293, 294, 3, 58},
  {cont__38_7, &frame__38_1_types__key_order_table_update_each_from_to, },
  {entry__39_6, NULL, 305, 305, 29, 38},
  {cont__39_7, &frame__39_6, 305, 305, 29, 38},
  {entry__39_9, NULL, 306, 306, 38, 52},
  {cont__39_10, &frame__39_9, 306, 306, 7, 68},
  {cont__39_11, &frame__39_9, 306, 306, 68, 68},
  {entry__39_14, NULL, 308, 308, 30, 41},
  {cont__39_15, &frame__39_14, 308, 308, 30, 41},
  {cont__39_16, &frame__39_14, 308, 308, 30, 41},
  {entry__39_20, NULL, 308, 308, 69, 79},
  {cont__39_21, &frame__39_20, 308, 308, 69, 79},
  {cont__39_22, &frame__39_20, 308, 308, 69, 79},
  {entry__39_18, NULL, 308, 308, 48, 64},
  {cont__39_19, &frame__39_18, 308, 308, 48, 79},
  {cont__39_23, &frame__39_18, 308, 308, 48, 79},
  {entry__39_25, NULL, 310, 310, 19, 33},
  {cont__39_26, &frame__39_25, 310, 310, 9, 33},
  {cont__39_27, &frame__39_25, 310, 310, 33, 33},
  {entry__39_30, NULL, 311, 311, 30, 40},
  {cont__39_31, &frame__39_30, 311, 311, 30, 40},
  {entry__39_33, NULL, 312, 312, 38, 51},
  {cont__39_34, &frame__39_33, 312, 312, 7, 67},
  {cont__39_35, &frame__39_33, 312, 312, 67, 67},
  {entry__39_3, NULL, 304, 304, 5, 23},
  {cont__39_4, &frame__39_3, 305, 305, 8, 24},
  {cont__39_5, &frame__39_3, 305, 305, 8, 38},
  {cont__39_8, &frame__39_3, 305, 306, 5, 68},
  {cont__39_12, &frame__39_3, 308, 308, 8, 25},
  {cont__39_13, &frame__39_3, 308, 308, 8, 41},
  {cont__39_17, &frame__39_3, 308, 308, 8, 79},
  {cont__39_24, &frame__39_3, 307, 310, 5, 34},
  {cont__39_28, &frame__39_3, 311, 311, 8, 25},
  {cont__39_29, &frame__39_3, 311, 311, 8, 40},
  {cont__39_32, &frame__39_3, 311, 312, 5, 67},
  {entry__39_1_update_each_item_from_down_to, NULL, 303, 303, 6, 22},
  {cont__39_2, &frame__39_1_update_each_item_from_down_to, 303, 312, 3, 68},
  {cont__39_36, &frame__39_1_update_each_item_from_down_to, },
  {entry__40_4, NULL, 322, 322, 36, 47},
  {cont__40_5, &frame__40_4, 322, 322, 5, 63},
  {cont__40_6, &frame__40_4, 322, 322, 63, 63},
  {entry__40_1_types__key_order_table_update_each_from_down_to, NULL, 321, 321, 6, 18},
  {cont__40_2, &frame__40_1_types__key_order_table_update_each_from_down_to, 321, 321, 6, 29},
  {cont__40_3, &frame__40_1_types__key_order_table_update_each_from_down_to, 321, 322, 3, 63},
  {cont__40_7, &frame__40_1_types__key_order_table_update_each_from_down_to, },
  {entry__41_4, NULL, 329, 329, 50, 61},
  {cont__41_5, &frame__41_4, 329, 329, 32, 66},
  {cont__41_6, &frame__41_4, 329, 329, 66, 66},
  {entry__41_1_types__key_order_table_update_each, NULL, 329, 329, 6, 18},
  {cont__41_2, &frame__41_1_types__key_order_table_update_each, 329, 329, 6, 29},
  {cont__41_3, &frame__41_1_types__key_order_table_update_each, 329, 329, 3, 66},
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
  // 80: $empty_node types::object
  initialize_maybe_future(var._empty_node, get__types__object());
  // 331: register_collection_serializer "key_order_table" empty_key_order_table
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
  // 89: $$left left_of(myself)
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
  // 91: left.is_defined
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
  // 91: ... :
  // 92:   fetch_first &left $key $value
  // 93:   !myself.left_of left
  // 94:   return key value
  frame->slots[4] /* temp__2 */ = create_closure(entry__18_4, 0);
  // 95: :
  // 96:   $key key_of(myself)
  // 97:   $value value_of(myself)
  // 98:   !myself right_of(myself)
  // 99:   return key value
  frame->slots[5] /* temp__3 */ = create_closure(entry__18_6, 0);
  // 90: if
  // 91:   left.is_defined:
  // 92:     fetch_first &left $key $value
  // 93:     !myself.left_of left
  // 94:     return key value
  // 95:   :
  // 96:     $key key_of(myself)
  // 97:     $value value_of(myself)
  // 98:     !myself right_of(myself)
  // 99:     return key value
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
  // 92: fetch_first &left $key $value
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
  // 92: ... key
  initialize_future(frame->slots[3] /* key */, frame->slots[5] /* temp__1 */);
  // 92: ... value
  initialize_future(frame->slots[4] /* value */, frame->slots[6] /* temp__2 */);
  // 93: !myself.left_of left
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* left */;
  // 93: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* myself */ = temp;

  }
  // 94: return key value
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
  // 96: $key key_of(myself)
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
  // 97: $value value_of(myself)
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
  // 98: !myself right_of(myself)
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
  // 99: return key value
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
  // 107: ... myself.is_undefined
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
  // 107: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_3, 0);
  // 107: if myself.is_undefined: return undefined
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
  // 107: ... return undefined
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
  // 108: $my_key key_of(myself)
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
  // 110: -> key == my_key: return value_of(myself)
  frame->slots[4] /* temp__1 */ = create_closure(entry__19_6, 0);
  // 111: -> key < my_key: return retrieve_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_10, 0);
  // 112: -> key > my_key: return retrieve_item(right_of(myself) key)
  frame->slots[6] /* temp__3 */ = create_closure(entry__19_15, 0);
  // 109: cond
  // 110:   -> key == my_key: return value_of(myself)
  // 111:   -> key < my_key: return retrieve_item(left_of(myself) key)
  // 112:   -> key > my_key: return retrieve_item(right_of(myself) key)
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
  // 112: ... right_of(myself)
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
  // 112: ... retrieve_item(right_of(myself) key)
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
  // 112: ... return retrieve_item(right_of(myself) key)
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
  // 111: ... left_of(myself)
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
  // 111: ... retrieve_item(left_of(myself) key)
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
  // 111: ... return retrieve_item(left_of(myself) key)
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
  // 110: ... value_of(myself)
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
  // 110: ... return value_of(myself)
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
  // 110: ... key == my_key
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
  // 110: ... : return value_of(myself)
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_8, 0);
  // 110: -> key == my_key: return value_of(myself)
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
  // 111: ... key < my_key
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
  // 111: ... : return retrieve_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_12, 0);
  // 111: -> key < my_key: return retrieve_item(left_of(myself) key)
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
  // 112: ... key > my_key
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
  // 112: ... : return retrieve_item(right_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_17, 0);
  // 112: -> key > my_key: return retrieve_item(right_of(myself) key)
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
  // 121: ... myself.is_undefined
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
  // 121: ... : return empty_node(.key_of key .value_of value) INSERT
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_3, 0);
  // 121: if myself.is_undefined: return empty_node(.key_of key .value_of value) INSERT
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
  // 121: ... empty_node(.key_of key .value_of value)
  {
    NODE *temp = clone_object_and_attributes(var._empty_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[1] /* key */);
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[2] /* value */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 121: ... return empty_node(.key_of key .value_of value) INSERT
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
  // 122: $my_key key_of(myself)
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
  // 124: -> key == my_key: return myself(.value_of value) UPDATE
  frame->slots[5] /* temp__1 */ = create_closure(entry__20_6, 0);
  // 125: -> key < my_key:
  // 126:   add_item $left $mode left_of(myself) key value
  // 127:   return myself(.left_of left) mode
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_9, 0);
  // 128: -> key > my_key:
  // 129:   add_item $right $mode right_of(myself) key value
  // 130:   return myself(.right_of right) mode
  frame->slots[7] /* temp__3 */ = create_closure(entry__20_14, 0);
  // 123: cond
  // 124:   -> key == my_key: return myself(.value_of value) UPDATE
  // 125:   -> key < my_key:
  // 126:     add_item $left $mode left_of(myself) key value
  // 127:     return myself(.left_of left) mode
  // 128:   -> key > my_key:
  // 129:     add_item $right $mode right_of(myself) key value
  // 130:     return myself(.right_of right) mode
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
  // 129: ... right_of(myself)
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
  // 129: add_item $right $mode right_of(myself) key value
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
  // 129: ... right
  initialize_future(frame->slots[4] /* right */, frame->slots[7] /* temp__2 */);
  // 129: ... mode
  initialize_future(frame->slots[5] /* mode */, frame->slots[8] /* temp__3 */);
  // 130: ... myself(.right_of right)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* right */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 130: return myself(.right_of right) mode
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
  // 126: ... left_of(myself)
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
  // 126: add_item $left $mode left_of(myself) key value
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
  // 126: ... left
  initialize_future(frame->slots[4] /* left */, frame->slots[7] /* temp__2 */);
  // 126: ... mode
  initialize_future(frame->slots[5] /* mode */, frame->slots[8] /* temp__3 */);
  // 127: ... myself(.left_of left)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* left */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 127: return myself(.left_of left) mode
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
  // 124: ... myself(.value_of value)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[2] /* value */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 124: ... return myself(.value_of value) UPDATE
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
  // 124: ... key == my_key
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
  // 124: ... : return myself(.value_of value) UPDATE
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_8, 0);
  // 124: -> key == my_key: return myself(.value_of value) UPDATE
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
  // 125: ... key < my_key
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
  // 125: ... :
  // 126:   add_item $left $mode left_of(myself) key value
  // 127:   return myself(.left_of left) mode
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_11, 0);
  // 125: -> key < my_key:
  // 126:   add_item $left $mode left_of(myself) key value
  // 127:   return myself(.left_of left) mode
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
  // 128: ... key > my_key
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
  // 128: ... :
  // 129:   add_item $right $mode right_of(myself) key value
  // 130:   return myself(.right_of right) mode
  frame->slots[6] /* temp__2 */ = create_closure(entry__20_16, 0);
  // 128: -> key > my_key:
  // 129:   add_item $right $mode right_of(myself) key value
  // 130:   return myself(.right_of right) mode
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
  // 138: ... myself.is_undefined
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
  // 138: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_3, 0);
  // 138: if myself.is_undefined: return NONE # nothing removed
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
  // 138: ... return NONE # nothing removed
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
  // 139: $my_key key_of(myself)
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
  // 141: -> key == my_key:
  // 142:   $left left_of(myself)
  // 143:   $$right right_of(myself)
  // 144:   if
  // 145:     left.is_defined:
  // 146:       if
  // 147:         right.is_defined:
  // 148:           fetch_first &right $head_key $head_value
  // 149:           return
  // 150:             types::object
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__21_6, 0);
  // 159: -> key < my_key:
  // 160:   $left remove_item(left_of(myself) key)
  // 161:   if NONE == left: return NONE # nothing removed
  // 162:   !myself.left_of left
  // 163:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_18, 0);
  // 164: -> key > my_key:
  // 165:   $right remove_item(right_of(myself) key)
  // 166:   if NONE == right: return NONE # nothing removed
  // 167:   !myself.right_of right
  // 168:   return myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_26, 0);
  // 140: cond
  // 141:   -> key == my_key:
  // 142:     $left left_of(myself)
  // 143:     $$right right_of(myself)
  // 144:     if
  // 145:       left.is_defined:
  // 146:         if
  // 147:           right.is_defined:
  // 148:             fetch_first &right $head_key $head_value
  // 149:             return
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
  // 165: ... right_of(myself)
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
  // 165: $right remove_item(right_of(myself) key)
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
  // 166: ... NONE == right
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
  // 166: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_32, 0);
  // 166: if NONE == right: return NONE # nothing removed
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
  // 166: ... return NONE # nothing removed
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
  // 167: !myself.right_of right
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* right */;
  // 167: !myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 168: return myself
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
  // 160: ... left_of(myself)
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
  // 160: $left remove_item(left_of(myself) key)
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
  // 161: ... NONE == left
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
  // 161: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_24, 0);
  // 161: if NONE == left: return NONE # nothing removed
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
  // 161: ... return NONE # nothing removed
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
  // 162: !myself.left_of left
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* left */;
  // 162: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 163: return myself
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
  // 148: fetch_first &right $head_key $head_value
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
  // 148: ... head_key
  initialize_future(frame->slots[3] /* head_key */, frame->slots[5] /* temp__1 */);
  // 148: ... head_value
  initialize_future(frame->slots[4] /* head_value */, frame->slots[6] /* temp__2 */);
  // 150: types::object
  // 151:   .key_of head_key
  // 152:   .value_of head_value
  // 153:   .left_of left
  // 154:   .right_of right
  {
    NODE *temp = clone_object_and_attributes(get__types__object());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[3] /* head_key */);
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* head_value */);
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[2] /* left */);
    set_attribute_value(temp->attributes, poly_idx__right_of, ((CELL *)frame->slots[0])->contents /* right */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 149: return
  // 150:   types::object
  // 151:     .key_of head_key
  // 152:     .value_of head_value
  // 153:     .left_of left
  // 154:     .right_of right
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
  // 156: return left
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
  // 147: right.is_defined
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
  // 147: ... :
  // 148:   fetch_first &right $head_key $head_value
  // 149:   return
  // 150:     types::object
  // 151:       .key_of head_key
  // 152:       .value_of head_value
  // 153:       .left_of left
  // 154:       .right_of right
  frame->slots[4] /* temp__2 */ = create_closure(entry__21_14, 0);
  // 155: :
  // 156:   return left
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_16, 0);
  // 146: if
  // 147:   right.is_defined:
  // 148:     fetch_first &right $head_key $head_value
  // 149:     return
  // 150:       types::object
  // 151:         .key_of head_key
  // 152:         .value_of head_value
  // 153:         .left_of left
  // 154:         .right_of right
  // 155:   :
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
  // 158: return right
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
  // 142: $left left_of(myself)
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
  // 143: $$right right_of(myself)
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
  // 145: left.is_defined
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
  // 145: ... :
  // 146:   if
  // 147:     right.is_defined:
  // 148:       fetch_first &right $head_key $head_value
  // 149:       return
  // 150:         types::object
  // 151:           .key_of head_key
  // 152:           .value_of head_value
  // 153:           .left_of left
  // 154:           .right_of right
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_12, 0);
  // 157: :
  // 158:   return right
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_17, 0);
  // 144: if
  // 145:   left.is_defined:
  // 146:     if
  // 147:       right.is_defined:
  // 148:         fetch_first &right $head_key $head_value
  // 149:         return
  // 150:           types::object
  // 151:             .key_of head_key
  // 152:             .value_of head_value
  // 153:             .left_of left
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
  // 141: ... key == my_key
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
  // 141: ... :
  // 142:   $left left_of(myself)
  // 143:   $$right right_of(myself)
  // 144:   if
  // 145:     left.is_defined:
  // 146:       if
  // 147:         right.is_defined:
  // 148:           fetch_first &right $head_key $head_value
  // 149:           return
  // 150:             types::object
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_8, 0);
  // 141: -> key == my_key:
  // 142:   $left left_of(myself)
  // 143:   $$right right_of(myself)
  // 144:   if
  // 145:     left.is_defined:
  // 146:       if
  // 147:         right.is_defined:
  // 148:           fetch_first &right $head_key $head_value
  // 149:           return
  // 150:             types::object
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
  // 159: ... key < my_key
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
  // 159: ... :
  // 160:   $left remove_item(left_of(myself) key)
  // 161:   if NONE == left: return NONE # nothing removed
  // 162:   !myself.left_of left
  // 163:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_20, 0);
  // 159: -> key < my_key:
  // 160:   $left remove_item(left_of(myself) key)
  // 161:   if NONE == left: return NONE # nothing removed
  // 162:   !myself.left_of left
  // 163:   return myself
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
  // 164: ... key > my_key
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
  // 164: ... :
  // 165:   $right remove_item(right_of(myself) key)
  // 166:   if NONE == right: return NONE # nothing removed
  // 167:   !myself.right_of right
  // 168:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_28, 0);
  // 164: -> key > my_key:
  // 165:   $right remove_item(right_of(myself) key)
  // 166:   if NONE == right: return NONE # nothing removed
  // 167:   !myself.right_of right
  // 168:   return myself
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
  // 177: value.is_undefined
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
  // 177: ... :
  // 178:   $new_tree remove_item(tree_of(self) key)
  // 179:   if NONE != new_tree:
  // 180:     !self.tree_of new_tree
  // 181:     dec &self.length_of
  frame->slots[4] /* temp__2 */ = create_closure(entry__22_3, 0);
  // 182: :
  // 183:   add_item $new_tree $mode tree_of(self) key value
  // 184:   !self.tree_of new_tree
  // 185:   if mode == INSERT: inc &self.length_of
  frame->slots[5] /* temp__3 */ = create_closure(entry__22_11, 0);
  // 176: if
  // 177:   value.is_undefined:
  // 178:     $new_tree remove_item(tree_of(self) key)
  // 179:     if NONE != new_tree:
  // 180:       !self.tree_of new_tree
  // 181:       dec &self.length_of
  // 182:   :
  // 183:     add_item $new_tree $mode tree_of(self) key value
  // 184:     !self.tree_of new_tree
  // 185:     if mode == INSERT: inc &self.length_of
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
  // 185: ... self.length_of
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
  // 185: ... inc &self.length_of
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
  // 185: ... &self.length_of
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
  // 180: !self.tree_of new_tree
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_tree */;
  // 180: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 181: ... self.length_of
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
  // 181: dec &self.length_of
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
  // 181: ... &self.length_of
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
  // 178: ... tree_of(self)
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
  // 178: $new_tree remove_item(tree_of(self) key)
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
  // 179: ... NONE != new_tree
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
  // 179: ... NONE != new_tree
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
  // 179: ... :
  // 180:   !self.tree_of new_tree
  // 181:   dec &self.length_of
  frame->slots[5] /* temp__3 */ = create_closure(entry__22_8, 0);
  // 179: if NONE != new_tree:
  // 180:   !self.tree_of new_tree
  // 181:   dec &self.length_of
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
  // 183: ... tree_of(self)
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
  // 183: add_item $new_tree $mode tree_of(self) key value
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
  // 183: ... new_tree
  initialize_future(frame->slots[3] /* new_tree */, frame->slots[6] /* temp__2 */);
  // 183: ... mode
  initialize_future(frame->slots[4] /* mode */, frame->slots[7] /* temp__3 */);
  // 184: !self.tree_of new_tree
  frame->slots[5] /* temp__1 */ = frame->slots[3] /* new_tree */;
  // 184: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 185: ... mode == INSERT
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
  // 185: ... : inc &self.length_of
  frame->slots[6] /* temp__2 */ = create_closure(entry__22_15, 0);
  // 185: if mode == INSERT: inc &self.length_of
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
  // 188: ... tree_of(self)
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
  // 188: retrieve_item tree_of(self) key
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
  // 194: ... -> types::key_order_table
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
  // 199: $$tab types::key_order_table
  ((CELL *)frame->slots[1])->contents /* tab */ = var.types__key_order_table;
  // 200: ... : (initializer)
  // 201:   !tab(std::key_of(initializer)) std::value_of(initializer)
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_2, 1);
  // 200: for_each initializers: (initializer)
  // 201:   !tab(std::key_of(initializer)) std::value_of(initializer)
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
  // 201: !tab(std::key_of(initializer)) std::value_of(initializer)
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
  // 201: ... std::key_of(initializer)
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
  // 201: !tab(std::key_of(initializer))
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
  // 202: -> tab
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
  // 206: ... left_of(myself)
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
  // 206: for_each_item left_of(myself) body
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
  // 208: parameter_count_of(body)
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
  // 208: parameter_count_of(body) == 2
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
  // 208: ... :
  // 209:   body key_of(myself) value_of(myself)
  frame->slots[4] /* temp__3 */ = create_closure(entry__30_8, 0);
  // 210: :
  // 211:   body value_of(myself)
  frame->slots[5] /* temp__4 */ = create_closure(entry__30_11, 0);
  // 207: if
  // 208:   parameter_count_of(body) == 2:
  // 209:     body key_of(myself) value_of(myself)
  // 210:   :
  // 211:     body value_of(myself)
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
  // 209: ... key_of(myself)
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
  // 209: ... value_of(myself)
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
  // 209: body key_of(myself) value_of(myself)
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
  // 211: ... value_of(myself)
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
  // 211: body value_of(myself)
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
  // 212: ... right_of(myself)
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
  // 212: for_each_item right_of(myself) body
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
  // 205: ... myself.is_defined
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
  // 205: ... :
  // 206:   for_each_item left_of(myself) body
  // 207:   if
  // 208:     parameter_count_of(body) == 2:
  // 209:       body key_of(myself) value_of(myself)
  // 210:     :
  // 211:       body value_of(myself)
  // 212:   for_each_item right_of(myself) body
  frame->slots[3] /* temp__2 */ = create_closure(entry__30_3, 0);
  // 205: if myself.is_defined:
  // 206:   for_each_item left_of(myself) body
  // 207:   if
  // 208:     parameter_count_of(body) == 2:
  // 209:       body key_of(myself) value_of(myself)
  // 210:     :
  // 211:       body value_of(myself)
  // 212:   for_each_item right_of(myself) body
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
  // 216: ... for_each_item tree body
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
  // 215: $tree tree_of(self)
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
  // 216: ... tree.is_defined
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
  // 216: ... : for_each_item tree body
  frame->slots[4] /* temp__2 */ = create_closure(entry__31_4, 0);
  // 216: if tree.is_defined: for_each_item tree body
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
  // 232: ... right_of(myself)
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
  // 232: for_each_item_from_to right_of(myself) first last body
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
  // 220: $key key_of(myself)
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
  // 221: ... first.is_undefined
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
  // 221: ... first < key
  frame->slots[7] /* temp__3 */ = create_closure(entry__32_6, 0);
  // 221: ... first.is_undefined || first < key
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
  // 221: ... first < key
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
  // 221: ... first < key
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
  // 221: ... :
  // 222:   for_each_item_from_to left_of(myself) first last body
  frame->slots[8] /* temp__4 */ = create_closure(entry__32_9, 0);
  // 221: if first.is_undefined || first < key:
  // 222:   for_each_item_from_to left_of(myself) first last body
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
  // 222: ... left_of(myself)
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
  // 222: for_each_item_from_to left_of(myself) first last body
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
  // 224: ... first.is_undefined
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
  // 224: ... key >= first
  frame->slots[8] /* temp__4 */ = create_closure(entry__32_13, 0);
  // 224: ... first.is_undefined || key >= first
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
  // 224: ... key >= first
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
  // 224: ... key >= first
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
  // 224: ... key >= first
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
  // 224: ... last.is_undefined || key <= last
  frame->slots[9] /* temp__5 */ = create_closure(entry__32_17, 0);
  // 224: ... first.is_undefined || key >= first) && (last.is_undefined || key <= last
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
  // 224: ... last.is_undefined
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
  // 224: ... key <= last
  frame->slots[4] /* temp__3 */ = create_closure(entry__32_19, 0);
  // 224: ... last.is_undefined || key <= last
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
  // 224: ... key <= last
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
  // 224: ... key <= last
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
  // 224: ... key <= last
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
  // 224: ... last.is_undefined || key <= last
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
  // 225: :
  // 226:   if
  // 227:     parameter_count_of(body) == 2:
  // 228:       body key value_of(myself)
  // 229:     :
  // 230:       body value_of(myself)
  frame->slots[10] /* temp__6 */ = create_closure(entry__32_24, 0);
  // 223: if
  // 224:   (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 225:   :
  // 226:     if
  // 227:       parameter_count_of(body) == 2:
  // 228:         body key value_of(myself)
  // 229:       :
  // 230:         body value_of(myself)
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
  // 228: ... value_of(myself)
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
  // 228: body key value_of(myself)
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
  // 230: ... value_of(myself)
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
  // 230: body value_of(myself)
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
  // 227: parameter_count_of(body)
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
  // 227: parameter_count_of(body) == 2
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
  // 227: ... :
  // 228:   body key value_of(myself)
  frame->slots[5] /* temp__3 */ = create_closure(entry__32_27, 0);
  // 229: :
  // 230:   body value_of(myself)
  frame->slots[6] /* temp__4 */ = create_closure(entry__32_29, 0);
  // 226: if
  // 227:   parameter_count_of(body) == 2:
  // 228:     body key value_of(myself)
  // 229:   :
  // 230:     body value_of(myself)
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
  // 231: ... last.is_undefined
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
  // 231: ... last > key
  frame->slots[7] /* temp__3 */ = create_closure(entry__32_33, 0);
  // 231: ... last.is_undefined || last > key
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
  // 231: ... last > key
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
  // 231: ... last > key
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
  // 231: ... :
  // 232:   for_each_item_from_to right_of(myself) first last body
  frame->slots[8] /* temp__4 */ = create_closure(entry__32_36, 0);
  // 231: if last.is_undefined || last > key:
  // 232:   for_each_item_from_to right_of(myself) first last body
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
  // 219: ... myself.is_defined
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
  // 219: ... :
  // 220:   $key key_of(myself)
  // 221:   if first.is_undefined || first < key:
  // 222:     for_each_item_from_to left_of(myself) first last body
  // 223:   if
  // 224:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 225:     :
  // 226:       if
  // 227:         parameter_count_of(body) == 2:
  // 228:           body key value_of(myself)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__32_3, 0);
  // 219: if myself.is_defined:
  // 220:   $key key_of(myself)
  // 221:   if first.is_undefined || first < key:
  // 222:     for_each_item_from_to left_of(myself) first last body
  // 223:   if
  // 224:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 225:     :
  // 226:       if
  // 227:         parameter_count_of(body) == 2:
  // 228:           body key value_of(myself)
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
  // 236: ... for_each_item_from_to tree first last body
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
  // 235: $tree tree_of(self)
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
  // 236: ... tree.is_defined
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
  // 236: ... : for_each_item_from_to tree first last body
  frame->slots[6] /* temp__2 */ = create_closure(entry__33_4, 0);
  // 236: if tree.is_defined: for_each_item_from_to tree first last body
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
  // 252: ... left_of(myself)
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
  // 252: for_each_item_from_down_to left_of(myself) last first body
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
  // 240: $key key_of(myself)
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
  // 241: ... last.is_undefined
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
  // 241: ... last > key
  frame->slots[7] /* temp__3 */ = create_closure(entry__34_6, 0);
  // 241: ... last.is_undefined || last > key
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
  // 241: ... last > key
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
  // 241: ... last > key
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
  // 241: ... :
  // 242:   for_each_item_from_down_to right_of(myself) last first body
  frame->slots[8] /* temp__4 */ = create_closure(entry__34_9, 0);
  // 241: if last.is_undefined || last > key:
  // 242:   for_each_item_from_down_to right_of(myself) last first body
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
  // 242: ... right_of(myself)
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
  // 242: for_each_item_from_down_to right_of(myself) last first body
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
  // 244: ... first.is_undefined
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
  // 244: ... key >= first
  frame->slots[8] /* temp__4 */ = create_closure(entry__34_13, 0);
  // 244: ... first.is_undefined || key >= first
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
  // 244: ... key >= first
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
  // 244: ... key >= first
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
  // 244: ... key >= first
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
  // 244: ... last.is_undefined || key <= last
  frame->slots[9] /* temp__5 */ = create_closure(entry__34_17, 0);
  // 244: ... first.is_undefined || key >= first) && (last.is_undefined || key <= last
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
  // 244: ... last.is_undefined
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
  // 244: ... key <= last
  frame->slots[4] /* temp__3 */ = create_closure(entry__34_19, 0);
  // 244: ... last.is_undefined || key <= last
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
  // 244: ... key <= last
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
  // 244: ... key <= last
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
  // 244: ... key <= last
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
  // 244: ... last.is_undefined || key <= last
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
  // 245: :
  // 246:   if
  // 247:     parameter_count_of(body) == 2:
  // 248:       body key value_of(myself)
  // 249:     :
  // 250:       body value_of(myself)
  frame->slots[10] /* temp__6 */ = create_closure(entry__34_24, 0);
  // 243: if
  // 244:   (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 245:   :
  // 246:     if
  // 247:       parameter_count_of(body) == 2:
  // 248:         body key value_of(myself)
  // 249:       :
  // 250:         body value_of(myself)
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
  // 248: ... value_of(myself)
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
  // 248: body key value_of(myself)
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
  // 250: ... value_of(myself)
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
  // 250: body value_of(myself)
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
  // 247: parameter_count_of(body)
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
  // 247: parameter_count_of(body) == 2
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
  // 247: ... :
  // 248:   body key value_of(myself)
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_27, 0);
  // 249: :
  // 250:   body value_of(myself)
  frame->slots[6] /* temp__4 */ = create_closure(entry__34_29, 0);
  // 246: if
  // 247:   parameter_count_of(body) == 2:
  // 248:     body key value_of(myself)
  // 249:   :
  // 250:     body value_of(myself)
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
  // 251: ... first.is_undefined
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
  // 251: ... first < key
  frame->slots[7] /* temp__3 */ = create_closure(entry__34_33, 0);
  // 251: ... first.is_undefined || first < key
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
  // 251: ... first < key
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
  // 251: ... first < key
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
  // 251: ... :
  // 252:   for_each_item_from_down_to left_of(myself) last first body
  frame->slots[8] /* temp__4 */ = create_closure(entry__34_36, 0);
  // 251: if first.is_undefined || first < key:
  // 252:   for_each_item_from_down_to left_of(myself) last first body
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
  // 239: ... myself.is_defined
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
  // 239: ... :
  // 240:   $key key_of(myself)
  // 241:   if last.is_undefined || last > key:
  // 242:     for_each_item_from_down_to right_of(myself) last first body
  // 243:   if
  // 244:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 245:     :
  // 246:       if
  // 247:         parameter_count_of(body) == 2:
  // 248:           body key value_of(myself)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_3, 0);
  // 239: if myself.is_defined:
  // 240:   $key key_of(myself)
  // 241:   if last.is_undefined || last > key:
  // 242:     for_each_item_from_down_to right_of(myself) last first body
  // 243:   if
  // 244:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 245:     :
  // 246:       if
  // 247:         parameter_count_of(body) == 2:
  // 248:           body key value_of(myself)
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
  // 256: ... for_each_item_from_down_to tree last first body
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
  // 255: $tree tree_of(self)
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
  // 256: ... tree.is_defined
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
  // 256: ... : for_each_item_from_down_to tree last first body
  frame->slots[6] /* temp__2 */ = create_closure(entry__35_4, 0);
  // 256: if tree.is_defined: for_each_item_from_down_to tree last first body
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
  // 263: ... myself.is_defined
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
  // 263: ... :
  // 264:   update_each_item &myself.left_of body
  // 265:   body key_of(myself) &myself.value_of
  // 266:   update_each_item &myself.right_of body
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_3, 0);
  // 263: if myself.is_defined:
  // 264:   update_each_item &myself.left_of body
  // 265:   body key_of(myself) &myself.value_of
  // 266:   update_each_item &myself.right_of body
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
  // 264: ... myself.left_of
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
  // 264: update_each_item &myself.left_of body
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
  // 264: ... &myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 265: ... key_of(myself)
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
  // 265: ... myself.value_of
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
  // 265: body key_of(myself) &myself.value_of
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
  // 265: ... &myself.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 266: ... myself.right_of
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
  // 266: update_each_item &myself.right_of body
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
  // 266: ... &myself.right_of
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
  // 275: ... myself.is_defined
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
  // 275: ... :
  // 276:   $key key_of(myself)
  // 277:   if first.is_undefined || first < key:
  // 278:     update_each_item_from_to &myself.left_of first last body
  // 279:   if
  // 280:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 281:     :
  // 282:       body key &myself.value_of
  // 283:   if last.is_undefined || last > key:
  // 284:     update_each_item_from_to &myself.right_of first last body
  frame->slots[5] /* temp__2 */ = create_closure(entry__37_3, 0);
  // 275: if myself.is_defined:
  // 276:   $key key_of(myself)
  // 277:   if first.is_undefined || first < key:
  // 278:     update_each_item_from_to &myself.left_of first last body
  // 279:   if
  // 280:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 281:     :
  // 282:       body key &myself.value_of
  // 283:   if last.is_undefined || last > key:
  // 284:     update_each_item_from_to &myself.right_of first last body
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
  // 284: ... myself.right_of
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
  // 284: update_each_item_from_to &myself.right_of first last body
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
  // 284: ... &myself.right_of
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
  // 276: $key key_of(myself)
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
  // 277: ... first.is_undefined
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
  // 277: ... first < key
  frame->slots[7] /* temp__3 */ = create_closure(entry__37_6, 0);
  // 277: ... first.is_undefined || first < key
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
  // 277: ... first < key
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
  // 277: ... first < key
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
  // 277: ... :
  // 278:   update_each_item_from_to &myself.left_of first last body
  frame->slots[8] /* temp__4 */ = create_closure(entry__37_9, 0);
  // 277: if first.is_undefined || first < key:
  // 278:   update_each_item_from_to &myself.left_of first last body
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
  // 278: ... myself.left_of
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
  // 278: update_each_item_from_to &myself.left_of first last body
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
  // 278: ... &myself.left_of
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
  // 280: ... first.is_undefined
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
  // 280: ... key >= first
  frame->slots[8] /* temp__4 */ = create_closure(entry__37_14, 0);
  // 280: ... first.is_undefined || key >= first
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
  // 280: ... key >= first
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
  // 280: ... key >= first
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
  // 280: ... key >= first
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
  // 280: ... last.is_undefined || key <= last
  frame->slots[9] /* temp__5 */ = create_closure(entry__37_18, 0);
  // 280: ... first.is_undefined || key >= first) && (last.is_undefined || key <= last
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
  // 280: ... last.is_undefined
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
  // 280: ... key <= last
  frame->slots[4] /* temp__3 */ = create_closure(entry__37_20, 0);
  // 280: ... last.is_undefined || key <= last
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
  // 280: ... key <= last
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
  // 280: ... key <= last
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
  // 280: ... key <= last
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
  // 280: ... last.is_undefined || key <= last
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
  // 281: :
  // 282:   body key &myself.value_of
  frame->slots[10] /* temp__6 */ = create_closure(entry__37_25, 0);
  // 279: if
  // 280:   (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 281:   :
  // 282:     body key &myself.value_of
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
  // 282: ... myself.value_of
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
  // 282: body key &myself.value_of
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
  // 282: ... &myself.value_of
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
  // 283: ... last.is_undefined
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
  // 283: ... last > key
  frame->slots[7] /* temp__3 */ = create_closure(entry__37_30, 0);
  // 283: ... last.is_undefined || last > key
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
  // 283: ... last > key
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
  // 283: ... last > key
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
  // 283: ... :
  // 284:   update_each_item_from_to &myself.right_of first last body
  frame->slots[8] /* temp__4 */ = create_closure(entry__37_33, 0);
  // 283: if last.is_undefined || last > key:
  // 284:   update_each_item_from_to &myself.right_of first last body
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
  // 293: ... tree_of(self)
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
  // 293: ... tree_of(self).is_defined
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
  // 293: ... :
  // 294:   update_each_item_from_to &self.tree_of first last body
  frame->slots[6] /* temp__3 */ = create_closure(entry__38_4, 0);
  // 293: if tree_of(self).is_defined:
  // 294:   update_each_item_from_to &self.tree_of first last body
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
  // 294: ... self.tree_of
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
  // 294: update_each_item_from_to &self.tree_of first last body
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
  // 294: ... &self.tree_of
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
  // 303: ... myself.is_defined
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
  // 303: ... :
  // 304:   $key key_of(myself)
  // 305:   if last.is_undefined || last > key:
  // 306:     update_each_item_from_down_to &myself.right_of last first body
  // 307:   if
  // 308:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 309:     :
  // 310:       body key &myself.value_of
  // 311:   if first.is_undefined || first < key:
  // 312:     update_each_item_from_down_to &myself.left_of last first body
  frame->slots[5] /* temp__2 */ = create_closure(entry__39_3, 0);
  // 303: if myself.is_defined:
  // 304:   $key key_of(myself)
  // 305:   if last.is_undefined || last > key:
  // 306:     update_each_item_from_down_to &myself.right_of last first body
  // 307:   if
  // 308:     (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 309:     :
  // 310:       body key &myself.value_of
  // 311:   if first.is_undefined || first < key:
  // 312:     update_each_item_from_down_to &myself.left_of last first body
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
  // 312: ... myself.left_of
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
  // 312: update_each_item_from_down_to &myself.left_of last first body
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
  // 312: ... &myself.left_of
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
  // 304: $key key_of(myself)
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
  // 305: ... last.is_undefined
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
  // 305: ... last > key
  frame->slots[7] /* temp__3 */ = create_closure(entry__39_6, 0);
  // 305: ... last.is_undefined || last > key
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
  // 305: ... last > key
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
  // 305: ... last > key
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
  // 305: ... :
  // 306:   update_each_item_from_down_to &myself.right_of last first body
  frame->slots[8] /* temp__4 */ = create_closure(entry__39_9, 0);
  // 305: if last.is_undefined || last > key:
  // 306:   update_each_item_from_down_to &myself.right_of last first body
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
  // 306: ... myself.right_of
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
  // 306: update_each_item_from_down_to &myself.right_of last first body
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
  // 306: ... &myself.right_of
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
  // 308: ... first.is_undefined
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
  // 308: ... key >= first
  frame->slots[8] /* temp__4 */ = create_closure(entry__39_14, 0);
  // 308: ... first.is_undefined || key >= first
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
  // 308: ... key >= first
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
  // 308: ... key >= first
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
  // 308: ... key >= first
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
  // 308: ... last.is_undefined || key <= last
  frame->slots[9] /* temp__5 */ = create_closure(entry__39_18, 0);
  // 308: ... first.is_undefined || key >= first) && (last.is_undefined || key <= last
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
  // 308: ... last.is_undefined
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
  // 308: ... key <= last
  frame->slots[4] /* temp__3 */ = create_closure(entry__39_20, 0);
  // 308: ... last.is_undefined || key <= last
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
  // 308: ... key <= last
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
  // 308: ... key <= last
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
  // 308: ... key <= last
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
  // 308: ... last.is_undefined || key <= last
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
  // 309: :
  // 310:   body key &myself.value_of
  frame->slots[10] /* temp__6 */ = create_closure(entry__39_25, 0);
  // 307: if
  // 308:   (first.is_undefined || key >= first) && (last.is_undefined || key <= last)
  // 309:   :
  // 310:     body key &myself.value_of
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
  // 310: ... myself.value_of
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
  // 310: body key &myself.value_of
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
  // 310: ... &myself.value_of
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
  // 311: ... first.is_undefined
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
  // 311: ... first < key
  frame->slots[7] /* temp__3 */ = create_closure(entry__39_30, 0);
  // 311: ... first.is_undefined || first < key
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
  // 311: ... first < key
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
  // 311: ... first < key
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
  // 311: ... :
  // 312:   update_each_item_from_down_to &myself.left_of last first body
  frame->slots[8] /* temp__4 */ = create_closure(entry__39_33, 0);
  // 311: if first.is_undefined || first < key:
  // 312:   update_each_item_from_down_to &myself.left_of last first body
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
  // 321: ... tree_of(self)
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
  // 321: ... tree_of(self).is_defined
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
  // 321: ... :
  // 322:   update_each_item_from_down_to &self.tree_of last first body
  frame->slots[6] /* temp__3 */ = create_closure(entry__40_4, 0);
  // 321: if tree_of(self).is_defined:
  // 322:   update_each_item_from_down_to &self.tree_of last first body
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
  // 322: ... self.tree_of
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
  // 322: update_each_item_from_down_to &self.tree_of last first body
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
  // 322: ... &self.tree_of
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
  // 329: ... tree_of(self)
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
  // 329: ... tree_of(self).is_defined
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
  // 329: ... : update_each_item &self.tree_of body
  frame->slots[4] /* temp__3 */ = create_closure(entry__41_4, 0);
  // 329: if tree_of(self).is_defined: update_each_item &self.tree_of body
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
  // 329: ... self.tree_of
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
  // 329: ... update_each_item &self.tree_of body
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
  // 329: ... &self.tree_of
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
