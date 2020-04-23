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
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
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
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__empty_insert_order_table;
static NODE_GETTER get_value_or_future__empty_insert_order_table;
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
static int poly_idx__insert_before;
static NODE_GETTER get__insert_before;
static int poly_idx__insert_behind;
static NODE_GETTER get__insert_behind;
static int poly_idx__is_an_insert_order_table;
static NODE_GETTER get__is_an_insert_order_table;
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
static NODE_GETTER get__raise;
static NODE_GETTER get_value_or_future__raise;
static NODE_GETTER get__register_collection_serializer;
static NODE_GETTER get_value_or_future__register_collection_serializer;
static int poly_idx__serialization_tag_of;
static NODE_GETTER get__serialization_tag_of;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_of;
static NODE_GETTER get_value_or_future__std__key_of;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
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
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *_NONE;
  NODE *_INSERT;
  NODE *_UPDATE;
  NODE *_tree_of;
  NODE *_first_of;
  NODE *_last_of;
  NODE *_key_of;
  NODE *_value_of;
  NODE *_left_of;
  NODE *_right_of;
  NODE *_next_of;
  NODE *_previous_of;
  NODE *_remove_leftmost;
  NODE *_remove_rightmost;
  NODE *_empty_node;
  NODE *_fetch_first;
  NODE *_retrieve_item;
  NODE *_add_item;
  NODE *_update_item;
  NODE *_remove_item;
  NODE *std__is_an_insert_order_table;
  NODE *types__insert_order_table;
  NODE *std__empty_insert_order_table;
  NODE *std__insert_order_table;
} var;
static const char *var_names[] = {
  "NONE",
  "INSERT",
  "UPDATE",
  "tree_of",
  "first_of",
  "last_of",
  "key_of",
  "value_of",
  "left_of",
  "right_of",
  "next_of",
  "previous_of",
  "remove_leftmost",
  "remove_rightmost",
  "empty_node",
  "fetch_first",
  "retrieve_item",
  "add_item",
  "update_item",
  "remove_item"
};
static int poly_idx__std__is_an_insert_order_table;
static void type__std__is_an_insert_order_table(void);
static NODE *get__std__is_an_insert_order_table(void) {
  return var.std__is_an_insert_order_table;
}
static NODE *unique__NONE;
static NODE *unique__INSERT;
static NODE *unique__UPDATE;
static int poly_idx__tree_of;
static void type__tree_of(void);
static int poly_idx__first_of;
static void type__first_of(void);
static int poly_idx__last_of;
static void type__last_of(void);
static int poly_idx__key_of;
static void type__key_of(void);
static int poly_idx__value_of;
static void type__value_of(void);
static int poly_idx__left_of;
static void type__left_of(void);
static int poly_idx__right_of;
static void type__right_of(void);
static int poly_idx__next_of;
static void type__next_of(void);
static int poly_idx__previous_of;
static void type__previous_of(void);
static NODE *func__16_1_remove_leftmost;
static void entry__16_1_remove_leftmost(void);
static FRAME_INFO frame__16_1_remove_leftmost = {4, {"node", "key", "value", "left"}};
static void cont__16_2(void);
static void cont__16_3(void);
static NODE *func__16_4;
static void entry__16_4(void);
static FRAME_INFO frame__16_4 = {4, {"left", "key", "value", "node"}};
static void cont__16_5(void);
static NODE *func__16_6;
static void entry__16_6(void);
static FRAME_INFO frame__16_6 = {3, {"key", "node", "value"}};
static void cont__16_7(void);
static void cont__16_8(void);
static void cont__16_9(void);
static void cont__16_10(void);
static NODE *func__17_1_remove_rightmost;
static void entry__17_1_remove_rightmost(void);
static FRAME_INFO frame__17_1_remove_rightmost = {4, {"node", "key", "value", "right"}};
static void cont__17_2(void);
static void cont__17_3(void);
static NODE *func__17_4;
static void entry__17_4(void);
static FRAME_INFO frame__17_4 = {4, {"right", "key", "value", "node"}};
static void cont__17_5(void);
static NODE *func__17_6;
static void entry__17_6(void);
static FRAME_INFO frame__17_6 = {3, {"key", "node", "value"}};
static void cont__17_7(void);
static void cont__17_8(void);
static void cont__17_9(void);
static void cont__17_10(void);
static NODE *get__types__insert_order_table(void) {
  return var.types__insert_order_table;
}
static NODE *func__24_1_fetch_first;
static void entry__24_1_fetch_first(void);
static FRAME_INFO frame__24_1_fetch_first = {2, {"myself", "left"}};
static void cont__24_2(void);
static void cont__24_3(void);
static NODE *func__24_4;
static void entry__24_4(void);
static FRAME_INFO frame__24_4 = {3, {"left", "myself", "head"}};
static void cont__24_5(void);
static NODE *func__24_6;
static void entry__24_6(void);
static FRAME_INFO frame__24_6 = {2, {"myself", "head"}};
static void cont__24_7(void);
static void cont__24_8(void);
static NODE *func__25_1_retrieve_item;
static void entry__25_1_retrieve_item(void);
static FRAME_INFO frame__25_1_retrieve_item = {4, {"myself", "key", "return", "my_key"}};
static void cont__25_2(void);
static NODE *func__25_3;
static void entry__25_3(void);
static FRAME_INFO frame__25_3 = {1, {"return"}};
static void cont__25_4(void);
static void cont__25_5(void);
static NODE *func__25_6;
static void entry__25_6(void);
static FRAME_INFO frame__25_6 = {4, {"key", "my_key", "return", "myself"}};
static void cont__25_7(void);
static NODE *func__25_8;
static void entry__25_8(void);
static FRAME_INFO frame__25_8 = {2, {"return", "myself"}};
static NODE *func__25_9;
static void entry__25_9(void);
static FRAME_INFO frame__25_9 = {4, {"key", "my_key", "return", "myself"}};
static void cont__25_10(void);
static NODE *func__25_11;
static void entry__25_11(void);
static FRAME_INFO frame__25_11 = {3, {"return", "myself", "key"}};
static void cont__25_12(void);
static void cont__25_13(void);
static NODE *func__25_14;
static void entry__25_14(void);
static FRAME_INFO frame__25_14 = {4, {"my_key", "key", "return", "myself"}};
static void cont__25_15(void);
static NODE *func__25_16;
static void entry__25_16(void);
static FRAME_INFO frame__25_16 = {3, {"return", "myself", "key"}};
static void cont__25_17(void);
static void cont__25_18(void);
static void cont__25_19(void);
static NODE *func__26_1_add_item;
static void entry__26_1_add_item(void);
static FRAME_INFO frame__26_1_add_item = {7, {"myself", "previous", "next", "key", "value", "return", "my_key"}};
static void cont__26_2(void);
static NODE *func__26_3;
static void entry__26_3(void);
static FRAME_INFO frame__26_3 = {5, {"return", "previous", "next", "key", "value"}};
static void cont__26_4(void);
static void cont__26_5(void);
static NODE *func__26_6;
static void entry__26_6(void);
static FRAME_INFO frame__26_6 = {5, {"key", "my_key", "return", "myself", "value"}};
static void cont__26_7(void);
static NODE *func__26_8;
static void entry__26_8(void);
static FRAME_INFO frame__26_8 = {3, {"return", "myself", "value"}};
static NODE *func__26_9;
static void entry__26_9(void);
static FRAME_INFO frame__26_9 = {7, {"key", "my_key", "myself", "previous", "next", "value", "return"}};
static void cont__26_10(void);
static NODE *func__26_11;
static void entry__26_11(void);
static FRAME_INFO frame__26_11 = {8, {"myself", "previous", "next", "key", "value", "return", "left", "mode"}};
static void cont__26_12(void);
static void cont__26_13(void);
static NODE *func__26_14;
static void entry__26_14(void);
static FRAME_INFO frame__26_14 = {7, {"my_key", "key", "myself", "previous", "next", "value", "return"}};
static void cont__26_15(void);
static NODE *func__26_16;
static void entry__26_16(void);
static FRAME_INFO frame__26_16 = {8, {"myself", "previous", "next", "key", "value", "return", "right", "mode"}};
static void cont__26_17(void);
static void cont__26_18(void);
static void cont__26_19(void);
static NODE *func__27_1_update_item;
static void entry__27_1_update_item(void);
static FRAME_INFO frame__27_1_update_item = {4, {"myself", "key", "updater", "my_key"}};
static void cont__27_2(void);
static NODE *func__27_3;
static void entry__27_3(void);
static FRAME_INFO frame__27_3 = {4, {"key", "my_key", "updater", "myself"}};
static void cont__27_4(void);
static NODE *func__27_5;
static void entry__27_5(void);
static FRAME_INFO frame__27_5 = {2, {"updater", "myself"}};
static void cont__27_6(void);
static NODE *func__27_7;
static void entry__27_7(void);
static FRAME_INFO frame__27_7 = {4, {"key", "my_key", "myself", "updater"}};
static void cont__27_8(void);
static NODE *func__27_9;
static void entry__27_9(void);
static FRAME_INFO frame__27_9 = {3, {"myself", "key", "updater"}};
static void cont__27_10(void);
static void cont__27_11(void);
static NODE *func__27_12;
static void entry__27_12(void);
static FRAME_INFO frame__27_12 = {4, {"my_key", "key", "myself", "updater"}};
static void cont__27_13(void);
static NODE *func__27_14;
static void entry__27_14(void);
static FRAME_INFO frame__27_14 = {3, {"myself", "key", "updater"}};
static void cont__27_15(void);
static void cont__27_16(void);
static void cont__27_17(void);
static NODE *func__28_1_remove_item;
static void entry__28_1_remove_item(void);
static FRAME_INFO frame__28_1_remove_item = {4, {"myself", "key", "return", "my_key"}};
static void cont__28_2(void);
static NODE *func__28_3;
static void entry__28_3(void);
static FRAME_INFO frame__28_3 = {1, {"return"}};
static void cont__28_4(void);
static void cont__28_5(void);
static NODE *func__28_6;
static void entry__28_6(void);
static FRAME_INFO frame__28_6 = {4, {"key", "my_key", "myself", "return"}};
static void cont__28_7(void);
static NODE *func__28_8;
static void entry__28_8(void);
static FRAME_INFO frame__28_8 = {4, {"myself", "return", "left", "right"}};
static void cont__28_9(void);
static void cont__28_10(void);
static void cont__28_11(void);
static NODE *func__28_12;
static void entry__28_12(void);
static FRAME_INFO frame__28_12 = {4, {"right", "return", "left", "myself"}};
static void cont__28_13(void);
static NODE *func__28_14;
static void entry__28_14(void);
static FRAME_INFO frame__28_14 = {5, {"right", "return", "left", "myself", "head"}};
static void cont__28_15(void);
static NODE *func__28_16;
static void entry__28_16(void);
static FRAME_INFO frame__28_16 = {3, {"return", "left", "myself"}};
static NODE *func__28_17;
static void entry__28_17(void);
static FRAME_INFO frame__28_17 = {3, {"return", "right", "myself"}};
static NODE *func__28_18;
static void entry__28_18(void);
static FRAME_INFO frame__28_18 = {4, {"key", "my_key", "myself", "return"}};
static void cont__28_19(void);
static NODE *func__28_20;
static void entry__28_20(void);
static FRAME_INFO frame__28_20 = {5, {"myself", "key", "return", "left", "removed_item"}};
static void cont__28_21(void);
static void cont__28_22(void);
static void cont__28_23(void);
static NODE *func__28_24;
static void entry__28_24(void);
static FRAME_INFO frame__28_24 = {1, {"return"}};
static void cont__28_25(void);
static NODE *func__28_26;
static void entry__28_26(void);
static FRAME_INFO frame__28_26 = {4, {"my_key", "key", "myself", "return"}};
static void cont__28_27(void);
static NODE *func__28_28;
static void entry__28_28(void);
static FRAME_INFO frame__28_28 = {5, {"myself", "key", "return", "right", "removed_item"}};
static void cont__28_29(void);
static void cont__28_30(void);
static void cont__28_31(void);
static NODE *func__28_32;
static void entry__28_32(void);
static FRAME_INFO frame__28_32 = {1, {"return"}};
static void cont__28_33(void);
static void cont__28_34(void);
static NODE *func__29_1_types__insert_order_table_private__set_item;
static void entry__29_1_types__insert_order_table_private__set_item(void);
static FRAME_INFO frame__29_1_types__insert_order_table_private__set_item = {3, {"self", "key", "value"}};
static void cont__29_2(void);
static NODE *func__29_3;
static void entry__29_3(void);
static FRAME_INFO frame__29_3 = {4, {"self", "key", "new_tree", "removed_item"}};
static void cont__29_4(void);
static void cont__29_5(void);
static void cont__29_6(void);
static void cont__29_7(void);
static NODE *func__29_8;
static void entry__29_8(void);
static FRAME_INFO frame__29_8 = {5, {"removed_item", "new_tree", "self", "previous", "next"}};
static void cont__29_9(void);
static void cont__29_10(void);
static void cont__29_11(void);
static NODE *func__29_12;
static void entry__29_12(void);
static FRAME_INFO frame__29_12 = {3, {"new_tree", "previous", "next"}};
static NODE *func__29_13;
static void entry__29_13(void);
static FRAME_INFO frame__29_13 = {2, {"item", "next"}};
static void cont__29_14(void);
static NODE *func__29_15;
static void entry__29_15(void);
static FRAME_INFO frame__29_15 = {2, {"self", "next"}};
static void cont__29_16(void);
static void cont__29_17(void);
static NODE *func__29_18;
static void entry__29_18(void);
static FRAME_INFO frame__29_18 = {3, {"new_tree", "next", "previous"}};
static NODE *func__29_19;
static void entry__29_19(void);
static FRAME_INFO frame__29_19 = {2, {"item", "previous"}};
static void cont__29_20(void);
static NODE *func__29_21;
static void entry__29_21(void);
static FRAME_INFO frame__29_21 = {2, {"self", "previous"}};
static void cont__29_22(void);
static void cont__29_23(void);
static void cont__29_24(void);
static NODE *func__29_25;
static void entry__29_25(void);
static FRAME_INFO frame__29_25 = {5, {"self", "key", "value", "new_tree", "mode"}};
static void cont__29_26(void);
static void cont__29_27(void);
static void cont__29_28(void);
static void cont__29_29(void);
static NODE *func__29_30;
static void entry__29_30(void);
static FRAME_INFO frame__29_30 = {3, {"self", "new_tree", "key"}};
static void cont__29_31(void);
static void cont__29_32(void);
static NODE *func__29_33;
static void entry__29_33(void);
static FRAME_INFO frame__29_33 = {3, {"new_tree", "self", "key"}};
static void cont__29_34(void);
static NODE *func__29_35;
static void entry__29_35(void);
static FRAME_INFO frame__29_35 = {2, {"item", "key"}};
static void cont__29_36(void);
static NODE *func__29_37;
static void entry__29_37(void);
static FRAME_INFO frame__29_37 = {2, {"self", "key"}};
static void cont__29_38(void);
static void cont__29_39(void);
static void cont__29_40(void);
static void cont__29_41(void);
static void cont__29_42(void);
static NODE *func__30_1_types__insert_order_table_private__get_item;
static void entry__30_1_types__insert_order_table_private__get_item(void);
static FRAME_INFO frame__30_1_types__insert_order_table_private__get_item = {3, {"self", "key", "item"}};
static void cont__30_2(void);
static void cont__30_3(void);
static void cont__30_4(void);
static NODE *func__30_5;
static void entry__30_5(void);
static FRAME_INFO frame__30_5 = {1, {"item"}};
static void cont__30_6(void);
static NODE *func__30_7;
static void entry__30_7(void);
static FRAME_INFO frame__30_7 = {0, {}};
static NODE *string__35_1;
static NODE *func__36_1_types__insert_order_table_new_empty_collection;
static void entry__36_1_types__insert_order_table_new_empty_collection(void);
static FRAME_INFO frame__36_1_types__insert_order_table_new_empty_collection = {1, {"self"}};
static NODE *get__std__empty_insert_order_table(void) {
  return var.std__empty_insert_order_table;
}
static NODE *func__38_1_std__insert_order_table;
static void entry__38_1_std__insert_order_table(void);
static FRAME_INFO frame__38_1_std__insert_order_table = {2, {"initializers", "tab"}};
static NODE *func__38_2;
static void entry__38_2(void);
static FRAME_INFO frame__38_2 = {2, {"initializer", "tab"}};
static void cont__38_3(void);
static void cont__38_4(void);
static void cont__38_5(void);
static void cont__38_6(void);
static NODE *get__std__insert_order_table(void) {
  return var.std__insert_order_table;
}
static NODE *func__39_1_types__insert_order_table_for_each;
static void entry__39_1_types__insert_order_table_for_each(void);
static FRAME_INFO frame__39_1_types__insert_order_table_for_each = {3, {"self", "body", "tree"}};
static void cont__39_2(void);
static void cont__39_3(void);
static NODE *func__39_4;
static void entry__39_4(void);
static FRAME_INFO frame__39_4 = {4, {"self", "tree", "body", "key"}};
static void cont__39_5(void);
static NODE *func__39_6;
static void entry__39_6(void);
static FRAME_INFO frame__39_6 = {3, {"key", "tree", "body"}};
static void cont__39_7(void);
static NODE *func__39_8;
static void entry__39_8(void);
static FRAME_INFO frame__39_8 = {4, {"tree", "key", "body", "item"}};
static void cont__39_9(void);
static void cont__39_10(void);
static void cont__39_11(void);
static NODE *func__39_12;
static void entry__39_12(void);
static FRAME_INFO frame__39_12 = {3, {"body", "key", "item"}};
static void cont__39_13(void);
static NODE *func__39_14;
static void entry__39_14(void);
static FRAME_INFO frame__39_14 = {2, {"body", "item"}};
static void cont__39_15(void);
static void cont__39_16(void);
static void cont__39_17(void);
static NODE *func__40_1_types__insert_order_table_for_each_from_to;
static void entry__40_1_types__insert_order_table_for_each_from_to(void);
static FRAME_INFO frame__40_1_types__insert_order_table_for_each_from_to = {6, {"self", "first", "last", "body", "return", "tree"}};
static void cont__40_2(void);
static void cont__40_3(void);
static NODE *func__40_4;
static void entry__40_4(void);
static FRAME_INFO frame__40_4 = {7, {"first", "self", "tree", "body", "last", "return", "key"}};
static void cont__40_5(void);
static NODE *func__40_6;
static void entry__40_6(void);
static FRAME_INFO frame__40_6 = {1, {"first"}};
static NODE *func__40_7;
static void entry__40_7(void);
static FRAME_INFO frame__40_7 = {1, {"self"}};
static void cont__40_8(void);
static void cont__40_9(void);
static NODE *func__40_10;
static void entry__40_10(void);
static FRAME_INFO frame__40_10 = {5, {"key", "tree", "body", "last", "return"}};
static void cont__40_11(void);
static NODE *func__40_12;
static void entry__40_12(void);
static FRAME_INFO frame__40_12 = {6, {"tree", "key", "body", "last", "return", "item"}};
static void cont__40_13(void);
static void cont__40_14(void);
static void cont__40_15(void);
static NODE *func__40_16;
static void entry__40_16(void);
static FRAME_INFO frame__40_16 = {3, {"body", "key", "item"}};
static void cont__40_17(void);
static NODE *func__40_18;
static void entry__40_18(void);
static FRAME_INFO frame__40_18 = {2, {"body", "item"}};
static void cont__40_19(void);
static void cont__40_20(void);
static void cont__40_21(void);
static void cont__40_22(void);
static void cont__40_23(void);
static void cont__40_24(void);
static NODE *func__41_1_types__insert_order_table_for_each_from_down_to;
static void entry__41_1_types__insert_order_table_for_each_from_down_to(void);
static FRAME_INFO frame__41_1_types__insert_order_table_for_each_from_down_to = {6, {"self", "last", "first", "body", "return", "tree"}};
static void cont__41_2(void);
static void cont__41_3(void);
static NODE *func__41_4;
static void entry__41_4(void);
static FRAME_INFO frame__41_4 = {7, {"last", "self", "tree", "body", "first", "return", "key"}};
static void cont__41_5(void);
static NODE *func__41_6;
static void entry__41_6(void);
static FRAME_INFO frame__41_6 = {1, {"last"}};
static NODE *func__41_7;
static void entry__41_7(void);
static FRAME_INFO frame__41_7 = {1, {"self"}};
static void cont__41_8(void);
static void cont__41_9(void);
static NODE *func__41_10;
static void entry__41_10(void);
static FRAME_INFO frame__41_10 = {5, {"key", "tree", "body", "first", "return"}};
static void cont__41_11(void);
static NODE *func__41_12;
static void entry__41_12(void);
static FRAME_INFO frame__41_12 = {6, {"tree", "key", "body", "first", "return", "item"}};
static void cont__41_13(void);
static void cont__41_14(void);
static void cont__41_15(void);
static NODE *func__41_16;
static void entry__41_16(void);
static FRAME_INFO frame__41_16 = {3, {"body", "key", "item"}};
static void cont__41_17(void);
static NODE *func__41_18;
static void entry__41_18(void);
static FRAME_INFO frame__41_18 = {2, {"body", "item"}};
static void cont__41_19(void);
static void cont__41_20(void);
static void cont__41_21(void);
static void cont__41_22(void);
static void cont__41_23(void);
static void cont__41_24(void);
static NODE *func__42_1_types__insert_order_table_update_each;
static void entry__42_1_types__insert_order_table_update_each(void);
static FRAME_INFO frame__42_1_types__insert_order_table_update_each = {3, {"self", "body", "tree"}};
static void cont__42_2(void);
static void cont__42_3(void);
static NODE *func__42_4;
static void entry__42_4(void);
static FRAME_INFO frame__42_4 = {4, {"self", "tree", "body", "key"}};
static void cont__42_5(void);
static NODE *func__42_6;
static void entry__42_6(void);
static FRAME_INFO frame__42_6 = {3, {"key", "tree", "body"}};
static void cont__42_7(void);
static NODE *func__42_8;
static void entry__42_8(void);
static FRAME_INFO frame__42_8 = {3, {"tree", "key", "body"}};
static NODE *func__42_9;
static void entry__42_9(void);
static FRAME_INFO frame__42_9 = {3, {"item", "body", "key"}};
static void cont__42_10(void);
static void cont__42_11(void);
static void cont__42_12(void);
static void cont__42_13(void);
static void cont__42_14(void);
static void cont__42_15(void);
static NODE *func__43_1_types__insert_order_table_update_each_from_to;
static void entry__43_1_types__insert_order_table_update_each_from_to(void);
static FRAME_INFO frame__43_1_types__insert_order_table_update_each_from_to = {5, {"self", "first", "last", "body", "tree"}};
static void cont__43_2(void);
static void cont__43_3(void);
static NODE *func__43_4;
static void entry__43_4(void);
static FRAME_INFO frame__43_4 = {6, {"first", "self", "tree", "body", "last", "key"}};
static void cont__43_5(void);
static NODE *func__43_6;
static void entry__43_6(void);
static FRAME_INFO frame__43_6 = {1, {"first"}};
static NODE *func__43_7;
static void entry__43_7(void);
static FRAME_INFO frame__43_7 = {1, {"self"}};
static void cont__43_8(void);
static void cont__43_9(void);
static NODE *func__43_10;
static void entry__43_10(void);
static FRAME_INFO frame__43_10 = {5, {"break", "key", "tree", "body", "last"}};
static NODE *func__43_11;
static void entry__43_11(void);
static FRAME_INFO frame__43_11 = {5, {"key", "tree", "body", "last", "break"}};
static void cont__43_12(void);
static NODE *func__43_13;
static void entry__43_13(void);
static FRAME_INFO frame__43_13 = {5, {"tree", "key", "body", "last", "break"}};
static NODE *func__43_14;
static void entry__43_14(void);
static FRAME_INFO frame__43_14 = {5, {"item", "body", "key", "last", "break"}};
static void cont__43_15(void);
static void cont__43_16(void);
static void cont__43_17(void);
static void cont__43_18(void);
static void cont__43_19(void);
static void cont__43_20(void);
static void cont__43_21(void);
static void cont__43_22(void);
static void cont__43_23(void);
static NODE *func__44_1_types__insert_order_table_update_each_from_down_to;
static void entry__44_1_types__insert_order_table_update_each_from_down_to(void);
static FRAME_INFO frame__44_1_types__insert_order_table_update_each_from_down_to = {5, {"self", "last", "first", "body", "tree"}};
static void cont__44_2(void);
static void cont__44_3(void);
static NODE *func__44_4;
static void entry__44_4(void);
static FRAME_INFO frame__44_4 = {6, {"last", "self", "tree", "body", "first", "key"}};
static void cont__44_5(void);
static NODE *func__44_6;
static void entry__44_6(void);
static FRAME_INFO frame__44_6 = {1, {"last"}};
static NODE *func__44_7;
static void entry__44_7(void);
static FRAME_INFO frame__44_7 = {1, {"self"}};
static void cont__44_8(void);
static void cont__44_9(void);
static NODE *func__44_10;
static void entry__44_10(void);
static FRAME_INFO frame__44_10 = {5, {"break", "key", "tree", "body", "first"}};
static NODE *func__44_11;
static void entry__44_11(void);
static FRAME_INFO frame__44_11 = {5, {"key", "tree", "body", "first", "break"}};
static void cont__44_12(void);
static NODE *func__44_13;
static void entry__44_13(void);
static FRAME_INFO frame__44_13 = {5, {"tree", "key", "body", "first", "break"}};
static NODE *func__44_14;
static void entry__44_14(void);
static FRAME_INFO frame__44_14 = {5, {"item", "body", "key", "first", "break"}};
static void cont__44_15(void);
static void cont__44_16(void);
static void cont__44_17(void);
static void cont__44_18(void);
static void cont__44_19(void);
static void cont__44_20(void);
static void cont__44_21(void);
static void cont__44_22(void);
static void cont__44_23(void);
static NODE *func__45_1_types__insert_order_table_insert_before;
static void entry__45_1_types__insert_order_table_insert_before(void);
static FRAME_INFO frame__45_1_types__insert_order_table_insert_before = {7, {"self", "key", "new_key", "new_value", "tree", "before_key", "mode"}};
static void cont__45_2(void);
static NODE *func__45_3;
static void entry__45_3(void);
static FRAME_INFO frame__45_3 = {3, {"item", "before_key", "new_key"}};
static void cont__45_4(void);
static void cont__45_5(void);
static void cont__45_6(void);
static NODE *func__45_7;
static void entry__45_7(void);
static FRAME_INFO frame__45_7 = {3, {"tree", "before_key", "new_key"}};
static NODE *func__45_8;
static void entry__45_8(void);
static FRAME_INFO frame__45_8 = {2, {"item", "new_key"}};
static void cont__45_9(void);
static NODE *func__45_10;
static void entry__45_10(void);
static FRAME_INFO frame__45_10 = {2, {"self", "new_key"}};
static void cont__45_11(void);
static void cont__45_12(void);
static void cont__45_13(void);
static void cont__45_14(void);
static NODE *func__45_15;
static void entry__45_15(void);
static FRAME_INFO frame__45_15 = {0, {}};
static NODE *string__45_16;
static void cont__45_17(void);
static NODE *func__46_1_types__insert_order_table_insert_behind;
static void entry__46_1_types__insert_order_table_insert_behind(void);
static FRAME_INFO frame__46_1_types__insert_order_table_insert_behind = {7, {"self", "key", "new_key", "new_value", "tree", "behind_key", "mode"}};
static void cont__46_2(void);
static NODE *func__46_3;
static void entry__46_3(void);
static FRAME_INFO frame__46_3 = {3, {"item", "behind_key", "new_key"}};
static void cont__46_4(void);
static void cont__46_5(void);
static void cont__46_6(void);
static NODE *func__46_7;
static void entry__46_7(void);
static FRAME_INFO frame__46_7 = {3, {"tree", "behind_key", "new_key"}};
static NODE *func__46_8;
static void entry__46_8(void);
static FRAME_INFO frame__46_8 = {2, {"item", "new_key"}};
static void cont__46_9(void);
static NODE *func__46_10;
static void entry__46_10(void);
static FRAME_INFO frame__46_10 = {2, {"self", "new_key"}};
static void cont__46_11(void);
static void cont__46_12(void);
static void cont__46_13(void);
static void cont__46_14(void);
static NODE *func__46_15;
static void entry__46_15(void);
static FRAME_INFO frame__46_15 = {0, {}};
static void cont__46_16(void);
static void cont__94_1(void);
void run__basic__types__insert_order_table(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_an_insert_order_table, NULL, 23, 23, 2, 30},
  {type__tree_of, NULL, 32, 32, 2, 8},
  {type__first_of, NULL, 33, 33, 2, 9},
  {type__last_of, NULL, 34, 34, 2, 8},
  {type__key_of, NULL, 35, 35, 2, 7},
  {type__value_of, NULL, 36, 36, 2, 9},
  {type__left_of, NULL, 37, 37, 2, 8},
  {type__right_of, NULL, 38, 38, 2, 9},
  {type__next_of, NULL, 39, 39, 2, 8},
  {type__previous_of, NULL, 40, 40, 2, 12},
  {run__basic__types__insert_order_table, NULL, 446, 446, 1, 76},
  {cont__94_1, NULL, },
  {entry__16_4, NULL, 51, 51, 7, 39},
  {cont__16_5, &frame__16_4, 52, 52, 24, 24},
  {entry__16_6, NULL, 54, 54, 7, 23},
  {cont__16_7, &frame__16_6, 55, 55, 7, 27},
  {cont__16_8, &frame__16_6, 56, 56, 7, 26},
  {cont__16_9, &frame__16_6, 56, 56, 26, 26},
  {entry__16_1_remove_leftmost, NULL, 48, 48, 3, 22},
  {cont__16_2, &frame__16_1_remove_leftmost, 50, 50, 5, 19},
  {cont__16_3, &frame__16_1_remove_leftmost, 49, 56, 3, 27},
  {cont__16_10, &frame__16_1_remove_leftmost, },
  {entry__17_4, NULL, 67, 67, 7, 41},
  {cont__17_5, &frame__17_4, 68, 68, 26, 26},
  {entry__17_6, NULL, 70, 70, 7, 23},
  {cont__17_7, &frame__17_6, 71, 71, 7, 27},
  {cont__17_8, &frame__17_6, 72, 72, 7, 25},
  {cont__17_9, &frame__17_6, 72, 72, 25, 25},
  {entry__17_1_remove_rightmost, NULL, 64, 64, 3, 24},
  {cont__17_2, &frame__17_1_remove_rightmost, 66, 66, 5, 20},
  {cont__17_3, &frame__17_1_remove_rightmost, 65, 72, 3, 26},
  {cont__17_10, &frame__17_1_remove_rightmost, },
  {entry__24_4, NULL, 92, 92, 7, 29},
  {cont__24_5, &frame__24_4, 94, 94, 7, 13},
  {entry__24_6, NULL, 97, 97, 7, 30},
  {cont__24_7, &frame__24_6, 98, 98, 7, 13},
  {entry__24_1_fetch_first, NULL, 89, 89, 3, 24},
  {cont__24_2, &frame__24_1_fetch_first, 91, 91, 5, 19},
  {cont__24_3, &frame__24_1_fetch_first, 90, 98, 3, 14},
  {cont__24_8, &frame__24_1_fetch_first, },
  {entry__25_3, NULL, 106, 106, 27, 42},
  {entry__25_8, NULL, 109, 109, 23, 35},
  {entry__25_6, NULL, 109, 109, 8, 20},
  {cont__25_7, &frame__25_6, 109, 109, 5, 35},
  {entry__25_11, NULL, 110, 110, 43, 57},
  {cont__25_12, &frame__25_11, 110, 110, 29, 62},
  {cont__25_13, &frame__25_11, 110, 110, 22, 62},
  {entry__25_9, NULL, 110, 110, 8, 19},
  {cont__25_10, &frame__25_9, 110, 110, 5, 62},
  {entry__25_16, NULL, 111, 111, 43, 58},
  {cont__25_17, &frame__25_16, 111, 111, 29, 63},
  {cont__25_18, &frame__25_16, 111, 111, 22, 63},
  {entry__25_14, NULL, 111, 111, 8, 19},
  {cont__25_15, &frame__25_14, 111, 111, 5, 63},
  {entry__25_1_retrieve_item, NULL, 106, 106, 6, 24},
  {cont__25_2, &frame__25_1_retrieve_item, 106, 106, 3, 42},
  {cont__25_4, &frame__25_1_retrieve_item, 107, 107, 3, 24},
  {cont__25_5, &frame__25_1_retrieve_item, 108, 111, 3, 63},
  {cont__25_19, &frame__25_1_retrieve_item, 111, 111, 63, 63},
  {entry__26_3, NULL, 123, 129, 5, 12},
  {entry__26_8, NULL, 132, 132, 23, 59},
  {entry__26_6, NULL, 132, 132, 8, 20},
  {cont__26_7, &frame__26_6, 132, 132, 5, 59},
  {entry__26_11, NULL, 134, 134, 28, 42},
  {cont__26_12, &frame__26_11, 134, 134, 7, 66},
  {cont__26_13, &frame__26_11, 135, 135, 7, 39},
  {entry__26_9, NULL, 133, 133, 8, 19},
  {cont__26_10, &frame__26_9, 133, 135, 5, 39},
  {entry__26_16, NULL, 137, 137, 29, 44},
  {cont__26_17, &frame__26_16, 137, 137, 7, 68},
  {cont__26_18, &frame__26_16, 138, 138, 7, 41},
  {entry__26_14, NULL, 136, 136, 8, 19},
  {cont__26_15, &frame__26_14, 136, 138, 5, 41},
  {entry__26_1_add_item, NULL, 122, 122, 6, 24},
  {cont__26_2, &frame__26_1_add_item, 122, 129, 3, 13},
  {cont__26_4, &frame__26_1_add_item, 130, 130, 3, 24},
  {cont__26_5, &frame__26_1_add_item, 131, 138, 3, 42},
  {cont__26_19, &frame__26_1_add_item, 138, 138, 42, 42},
  {entry__27_5, NULL, 148, 148, 23, 37},
  {cont__27_6, &frame__27_5, 148, 148, 37, 37},
  {entry__27_3, NULL, 148, 148, 8, 20},
  {cont__27_4, &frame__27_3, 148, 148, 5, 37},
  {entry__27_9, NULL, 149, 149, 35, 48},
  {cont__27_10, &frame__27_9, 149, 149, 22, 60},
  {cont__27_11, &frame__27_9, 149, 149, 60, 60},
  {entry__27_7, NULL, 149, 149, 8, 19},
  {cont__27_8, &frame__27_7, 149, 149, 5, 60},
  {entry__27_14, NULL, 150, 150, 35, 49},
  {cont__27_15, &frame__27_14, 150, 150, 22, 61},
  {cont__27_16, &frame__27_14, 150, 150, 61, 61},
  {entry__27_12, NULL, 150, 150, 8, 19},
  {cont__27_13, &frame__27_12, 150, 150, 5, 61},
  {entry__27_1_update_item, NULL, 146, 146, 3, 24},
  {cont__27_2, &frame__27_1_update_item, 147, 150, 3, 61},
  {cont__27_17, &frame__27_1_update_item, },
  {entry__28_3, NULL, 162, 162, 27, 65},
  {entry__28_14, NULL, 172, 172, 15, 38},
  {cont__28_15, &frame__28_14, 173, 173, 15, 63},
  {entry__28_16, NULL, 175, 175, 15, 32},
  {entry__28_12, NULL, 171, 171, 13, 28},
  {cont__28_13, &frame__28_12, 170, 175, 11, 33},
  {entry__28_17, NULL, 177, 177, 11, 29},
  {entry__28_8, NULL, 166, 166, 7, 27},
  {cont__28_9, &frame__28_8, 167, 167, 7, 30},
  {cont__28_10, &frame__28_8, 169, 169, 9, 23},
  {cont__28_11, &frame__28_8, 168, 177, 7, 30},
  {entry__28_6, NULL, 165, 165, 8, 20},
  {cont__28_7, &frame__28_6, 165, 177, 5, 31},
  {entry__28_24, NULL, 180, 180, 24, 62},
  {entry__28_20, NULL, 179, 179, 39, 53},
  {cont__28_21, &frame__28_20, 179, 179, 7, 57},
  {cont__28_22, &frame__28_20, 180, 180, 10, 21},
  {cont__28_23, &frame__28_20, 180, 180, 7, 62},
  {cont__28_25, &frame__28_20, 182, 182, 7, 32},
  {entry__28_18, NULL, 178, 178, 8, 19},
  {cont__28_19, &frame__28_18, 178, 182, 5, 32},
  {entry__28_32, NULL, 185, 185, 25, 63},
  {entry__28_28, NULL, 184, 184, 40, 55},
  {cont__28_29, &frame__28_28, 184, 184, 7, 59},
  {cont__28_30, &frame__28_28, 185, 185, 10, 22},
  {cont__28_31, &frame__28_28, 185, 185, 7, 63},
  {cont__28_33, &frame__28_28, 187, 187, 7, 32},
  {entry__28_26, NULL, 183, 183, 8, 19},
  {cont__28_27, &frame__28_26, 183, 187, 5, 32},
  {entry__28_1_remove_item, NULL, 162, 162, 6, 24},
  {cont__28_2, &frame__28_1_remove_item, 162, 162, 3, 65},
  {cont__28_4, &frame__28_1_remove_item, 163, 163, 3, 24},
  {cont__28_5, &frame__28_1_remove_item, 164, 187, 3, 33},
  {cont__28_34, &frame__28_1_remove_item, 187, 187, 33, 33},
  {entry__29_13, NULL, 205, 205, 70, 70},
  {entry__29_12, NULL, 205, 205, 13, 70},
  {cont__29_14, &frame__29_12, 205, 205, 70, 70},
  {entry__29_15, NULL, 207, 207, 31, 31},
  {entry__29_19, NULL, 210, 210, 74, 74},
  {entry__29_18, NULL, 210, 210, 13, 74},
  {cont__29_20, &frame__29_18, 210, 210, 74, 74},
  {entry__29_21, NULL, 212, 212, 34, 34},
  {entry__29_8, NULL, 201, 201, 9, 43},
  {cont__29_9, &frame__29_8, 202, 202, 9, 35},
  {cont__29_10, &frame__29_8, 204, 204, 11, 29},
  {cont__29_11, &frame__29_8, 203, 207, 9, 32},
  {cont__29_16, &frame__29_8, 209, 209, 11, 25},
  {cont__29_17, &frame__29_8, 208, 212, 9, 35},
  {cont__29_22, &frame__29_8, 214, 214, 14, 27},
  {cont__29_23, &frame__29_8, 214, 214, 9, 27},
  {cont__29_24, &frame__29_8, 214, 214, 27, 27},
  {entry__29_3, NULL, 199, 199, 44, 56},
  {cont__29_4, &frame__29_3, 199, 199, 7, 60},
  {cont__29_5, &frame__29_3, 200, 200, 10, 25},
  {cont__29_6, &frame__29_3, 200, 200, 10, 25},
  {cont__29_7, &frame__29_3, 200, 214, 7, 27},
  {entry__29_35, NULL, 220, 220, 74, 74},
  {entry__29_33, NULL, 220, 220, 35, 47},
  {cont__29_34, &frame__29_33, 220, 220, 13, 74},
  {cont__29_36, &frame__29_33, 220, 220, 74, 74},
  {entry__29_37, NULL, 222, 222, 30, 30},
  {entry__29_30, NULL, 219, 219, 11, 23},
  {cont__29_31, &frame__29_30, 219, 219, 11, 34},
  {cont__29_32, &frame__29_30, 218, 222, 9, 31},
  {cont__29_38, &frame__29_30, 224, 224, 14, 27},
  {cont__29_39, &frame__29_30, 224, 224, 9, 27},
  {cont__29_40, &frame__29_30, 224, 224, 27, 27},
  {entry__29_25, NULL, 216, 216, 33, 45},
  {cont__29_26, &frame__29_25, 216, 216, 47, 59},
  {cont__29_27, &frame__29_25, 216, 216, 7, 79},
  {cont__29_28, &frame__29_25, 217, 217, 10, 23},
  {cont__29_29, &frame__29_25, 217, 224, 7, 27},
  {cont__29_41, &frame__29_25, 225, 225, 28, 28},
  {entry__29_1_types__insert_order_table_private__set_item, NULL, 198, 198, 5, 22},
  {cont__29_2, &frame__29_1_types__insert_order_table_private__set_item, 197, 225, 3, 29},
  {cont__29_42, &frame__29_1_types__insert_order_table_private__set_item, },
  {entry__30_5, NULL, 235, 235, 26, 39},
  {cont__30_6, &frame__30_5, 235, 235, 23, 39},
  {entry__30_7, NULL, 235, 235, 42, 53},
  {entry__30_1_types__insert_order_table_private__get_item, NULL, 234, 234, 23, 35},
  {cont__30_2, &frame__30_1_types__insert_order_table_private__get_item, 234, 234, 3, 40},
  {cont__30_3, &frame__30_1_types__insert_order_table_private__get_item, 235, 235, 6, 20},
  {cont__30_4, &frame__30_1_types__insert_order_table_private__get_item, 235, 235, 3, 53},
  {entry__36_1_types__insert_order_table_new_empty_collection, NULL, 255, 255, 3, 30},
  {entry__38_2, NULL, 276, 276, 5, 61},
  {cont__38_3, &frame__38_2, 276, 276, 10, 33},
  {cont__38_4, &frame__38_2, 276, 276, 5, 34},
  {cont__38_5, &frame__38_2, 276, 276, 61, 61},
  {entry__38_1_std__insert_order_table, NULL, 275, 276, 3, 61},
  {cont__38_6, &frame__38_1_std__insert_order_table, 277, 277, 3, 8},
  {entry__39_12, NULL, 293, 293, 20, 33},
  {cont__39_13, &frame__39_12, 293, 293, 11, 33},
  {entry__39_14, NULL, 295, 295, 16, 29},
  {cont__39_15, &frame__39_14, 295, 295, 11, 29},
  {entry__39_8, NULL, 290, 290, 7, 35},
  {cont__39_9, &frame__39_8, 292, 292, 9, 32},
  {cont__39_10, &frame__39_8, 292, 292, 9, 37},
  {cont__39_11, &frame__39_8, 291, 295, 7, 30},
  {cont__39_16, &frame__39_8, 296, 296, 7, 24},
  {cont__39_17, &frame__39_8, 296, 296, 24, 24},
  {entry__39_6, NULL, 289, 289, 14, 27},
  {cont__39_7, &frame__39_6, 289, 296, 11, 24},
  {entry__39_4, NULL, 288, 288, 5, 24},
  {cont__39_5, &frame__39_4, 289, 296, 5, 24},
  {entry__39_1_types__insert_order_table_for_each, NULL, 286, 286, 3, 21},
  {cont__39_2, &frame__39_1_types__insert_order_table_for_each, 287, 287, 6, 20},
  {cont__39_3, &frame__39_1_types__insert_order_table_for_each, 287, 296, 3, 25},
  {entry__40_6, NULL, 310, 310, 32, 39},
  {entry__40_7, NULL, 310, 310, 45, 58},
  {cont__40_8, &frame__40_7, 310, 310, 42, 58},
  {entry__40_16, NULL, 315, 315, 20, 33},
  {cont__40_17, &frame__40_16, 315, 315, 11, 33},
  {entry__40_18, NULL, 317, 317, 16, 29},
  {cont__40_19, &frame__40_18, 317, 317, 11, 29},
  {entry__40_12, NULL, 312, 312, 7, 35},
  {cont__40_13, &frame__40_12, 314, 314, 9, 32},
  {cont__40_14, &frame__40_12, 314, 314, 9, 37},
  {cont__40_15, &frame__40_12, 313, 317, 7, 30},
  {cont__40_20, &frame__40_12, 318, 318, 10, 20},
  {cont__40_21, &frame__40_12, 318, 318, 7, 27},
  {cont__40_22, &frame__40_12, 319, 319, 7, 24},
  {cont__40_23, &frame__40_12, 319, 319, 24, 24},
  {entry__40_10, NULL, 311, 311, 14, 27},
  {cont__40_11, &frame__40_10, 311, 319, 11, 24},
  {entry__40_4, NULL, 310, 310, 14, 29},
  {cont__40_5, &frame__40_4, 310, 310, 5, 59},
  {cont__40_9, &frame__40_4, 311, 319, 5, 24},
  {entry__40_1_types__insert_order_table_for_each_from_to, NULL, 308, 308, 3, 21},
  {cont__40_2, &frame__40_1_types__insert_order_table_for_each_from_to, 309, 309, 6, 20},
  {cont__40_3, &frame__40_1_types__insert_order_table_for_each_from_to, 309, 319, 3, 25},
  {cont__40_24, &frame__40_1_types__insert_order_table_for_each_from_to, 319, 319, 25, 25},
  {entry__41_6, NULL, 333, 333, 31, 37},
  {entry__41_7, NULL, 333, 333, 43, 55},
  {cont__41_8, &frame__41_7, 333, 333, 40, 55},
  {entry__41_16, NULL, 338, 338, 20, 33},
  {cont__41_17, &frame__41_16, 338, 338, 11, 33},
  {entry__41_18, NULL, 340, 340, 16, 29},
  {cont__41_19, &frame__41_18, 340, 340, 11, 29},
  {entry__41_12, NULL, 335, 335, 7, 35},
  {cont__41_13, &frame__41_12, 337, 337, 9, 32},
  {cont__41_14, &frame__41_12, 337, 337, 9, 37},
  {cont__41_15, &frame__41_12, 336, 340, 7, 30},
  {cont__41_20, &frame__41_12, 341, 341, 10, 21},
  {cont__41_21, &frame__41_12, 341, 341, 7, 28},
  {cont__41_22, &frame__41_12, 342, 342, 7, 28},
  {cont__41_23, &frame__41_12, 342, 342, 28, 28},
  {entry__41_10, NULL, 334, 334, 14, 27},
  {cont__41_11, &frame__41_10, 334, 342, 11, 28},
  {entry__41_4, NULL, 333, 333, 14, 28},
  {cont__41_5, &frame__41_4, 333, 333, 5, 56},
  {cont__41_9, &frame__41_4, 334, 342, 5, 28},
  {entry__41_1_types__insert_order_table_for_each_from_down_to, NULL, 331, 331, 3, 21},
  {cont__41_2, &frame__41_1_types__insert_order_table_for_each_from_down_to, 332, 332, 6, 20},
  {cont__41_3, &frame__41_1_types__insert_order_table_for_each_from_down_to, 332, 342, 3, 29},
  {cont__41_24, &frame__41_1_types__insert_order_table_for_each_from_down_to, 342, 342, 29, 29},
  {entry__42_9, NULL, 356, 356, 19, 31},
  {cont__42_10, &frame__42_9, 356, 356, 9, 31},
  {cont__42_11, &frame__42_9, 357, 357, 9, 26},
  {cont__42_12, &frame__42_9, 357, 357, 26, 26},
  {entry__42_8, NULL, 355, 357, 7, 26},
  {cont__42_13, &frame__42_8, 357, 357, 27, 27},
  {entry__42_6, NULL, 354, 354, 14, 27},
  {cont__42_7, &frame__42_6, 354, 357, 11, 27},
  {entry__42_4, NULL, 353, 353, 5, 24},
  {cont__42_5, &frame__42_4, 354, 357, 5, 27},
  {cont__42_14, &frame__42_4, 358, 358, 22, 22},
  {entry__42_1_types__insert_order_table_update_each, NULL, 351, 351, 3, 22},
  {cont__42_2, &frame__42_1_types__insert_order_table_update_each, 352, 352, 6, 20},
  {cont__42_3, &frame__42_1_types__insert_order_table_update_each, 352, 358, 3, 22},
  {cont__42_15, &frame__42_1_types__insert_order_table_update_each, },
  {entry__43_6, NULL, 371, 371, 32, 39},
  {entry__43_7, NULL, 371, 371, 45, 58},
  {cont__43_8, &frame__43_7, 371, 371, 42, 58},
  {entry__43_14, NULL, 375, 375, 21, 33},
  {cont__43_15, &frame__43_14, 375, 375, 11, 33},
  {cont__43_16, &frame__43_14, 376, 376, 14, 24},
  {cont__43_17, &frame__43_14, 376, 376, 11, 30},
  {cont__43_18, &frame__43_14, 377, 377, 11, 28},
  {cont__43_19, &frame__43_14, 377, 377, 28, 28},
  {entry__43_13, NULL, 374, 377, 9, 28},
  {cont__43_20, &frame__43_13, 377, 377, 29, 29},
  {entry__43_11, NULL, 373, 373, 16, 29},
  {cont__43_12, &frame__43_11, 373, 377, 13, 29},
  {entry__43_10, NULL, 373, 377, 7, 29},
  {cont__43_21, &frame__43_10, 377, 377, 29, 29},
  {entry__43_4, NULL, 371, 371, 14, 29},
  {cont__43_5, &frame__43_4, 371, 371, 5, 59},
  {cont__43_9, &frame__43_4, 372, 377, 5, 30},
  {cont__43_22, &frame__43_4, 378, 378, 22, 22},
  {entry__43_1_types__insert_order_table_update_each_from_to, NULL, 369, 369, 3, 22},
  {cont__43_2, &frame__43_1_types__insert_order_table_update_each_from_to, 370, 370, 6, 20},
  {cont__43_3, &frame__43_1_types__insert_order_table_update_each_from_to, 370, 378, 3, 22},
  {cont__43_23, &frame__43_1_types__insert_order_table_update_each_from_to, },
  {entry__44_6, NULL, 391, 391, 31, 37},
  {entry__44_7, NULL, 391, 391, 43, 55},
  {cont__44_8, &frame__44_7, 391, 391, 40, 55},
  {entry__44_14, NULL, 395, 395, 21, 33},
  {cont__44_15, &frame__44_14, 395, 395, 11, 33},
  {cont__44_16, &frame__44_14, 396, 396, 14, 25},
  {cont__44_17, &frame__44_14, 396, 396, 11, 31},
  {cont__44_18, &frame__44_14, 397, 397, 11, 32},
  {cont__44_19, &frame__44_14, 397, 397, 32, 32},
  {entry__44_13, NULL, 394, 397, 9, 32},
  {cont__44_20, &frame__44_13, 397, 397, 33, 33},
  {entry__44_11, NULL, 393, 393, 16, 29},
  {cont__44_12, &frame__44_11, 393, 397, 13, 33},
  {entry__44_10, NULL, 393, 397, 7, 33},
  {cont__44_21, &frame__44_10, 397, 397, 33, 33},
  {entry__44_4, NULL, 391, 391, 14, 28},
  {cont__44_5, &frame__44_4, 391, 391, 5, 56},
  {cont__44_9, &frame__44_4, 392, 397, 5, 34},
  {cont__44_22, &frame__44_4, 398, 398, 22, 22},
  {entry__44_1_types__insert_order_table_update_each_from_down_to, NULL, 389, 389, 3, 22},
  {cont__44_2, &frame__44_1_types__insert_order_table_update_each_from_down_to, 390, 390, 6, 20},
  {cont__44_3, &frame__44_1_types__insert_order_table_update_each_from_down_to, 390, 398, 3, 22},
  {cont__44_23, &frame__44_1_types__insert_order_table_update_each_from_down_to, },
  {entry__45_3, NULL, 412, 412, 5, 33},
  {cont__45_4, &frame__45_3, 413, 413, 29, 29},
  {entry__45_8, NULL, 416, 416, 65, 65},
  {entry__45_7, NULL, 416, 416, 7, 65},
  {cont__45_9, &frame__45_7, 416, 416, 65, 65},
  {entry__45_10, NULL, 418, 418, 28, 28},
  {entry__45_15, NULL, 421, 421, 22, 59},
  {entry__45_1_types__insert_order_table_insert_before, NULL, 409, 409, 3, 22},
  {cont__45_2, &frame__45_1_types__insert_order_table_insert_before, 411, 413, 3, 29},
  {cont__45_5, &frame__45_1_types__insert_order_table_insert_before, 415, 415, 5, 25},
  {cont__45_6, &frame__45_1_types__insert_order_table_insert_before, 414, 418, 3, 29},
  {cont__45_11, &frame__45_1_types__insert_order_table_insert_before, 419, 419, 3, 55},
  {cont__45_12, &frame__45_1_types__insert_order_table_insert_before, 421, 421, 6, 19},
  {cont__45_13, &frame__45_1_types__insert_order_table_insert_before, 421, 421, 6, 19},
  {cont__45_14, &frame__45_1_types__insert_order_table_insert_before, 421, 421, 3, 59},
  {cont__45_17, &frame__45_1_types__insert_order_table_insert_before, },
  {entry__46_3, NULL, 435, 435, 5, 29},
  {cont__46_4, &frame__46_3, 436, 436, 25, 25},
  {entry__46_8, NULL, 439, 439, 69, 69},
  {entry__46_7, NULL, 439, 439, 7, 69},
  {cont__46_9, &frame__46_7, 439, 439, 69, 69},
  {entry__46_10, NULL, 441, 441, 27, 27},
  {entry__46_15, NULL, 444, 444, 22, 59},
  {entry__46_1_types__insert_order_table_insert_behind, NULL, 432, 432, 3, 22},
  {cont__46_2, &frame__46_1_types__insert_order_table_insert_behind, 434, 436, 3, 25},
  {cont__46_5, &frame__46_1_types__insert_order_table_insert_behind, 438, 438, 5, 25},
  {cont__46_6, &frame__46_1_types__insert_order_table_insert_behind, 437, 441, 3, 28},
  {cont__46_11, &frame__46_1_types__insert_order_table_insert_behind, 442, 442, 3, 55},
  {cont__46_12, &frame__46_1_types__insert_order_table_insert_behind, 444, 444, 6, 19},
  {cont__46_13, &frame__46_1_types__insert_order_table_insert_behind, 444, 444, 6, 19},
  {cont__46_14, &frame__46_1_types__insert_order_table_insert_behind, 444, 444, 3, 59},
  {cont__46_16, &frame__46_1_types__insert_order_table_insert_behind, }
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__std__is_an_insert_order_table(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_an_insert_order_table);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_an_insert_order_table, attr);
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
static void type__first_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__first_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__first_of, attr);
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
static void type__last_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__last_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__last_of, attr);
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
static void type__next_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__next_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__next_of, attr);
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
static void type__previous_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__previous_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__previous_of, attr);
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
  "basic__types__insert_order_table",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/insert_order_table.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__insert_order_table(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 74: $types::insert_order_table types::generic_table
  initialize_maybe_future(var.types__insert_order_table, get__types__generic_table());
  // 78: $empty_node types::object
  initialize_maybe_future(var._empty_node, get__types__object());
  // 446: register_collection_serializer "insert_order_table" empty_insert_order_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__35_1;
  arguments->slots[1] = get__empty_insert_order_table();
  result_count = 0;
  myself = get__register_collection_serializer();
  func = myself->type;
  frame->cont = cont__94_1;
}
static void cont__94_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__16_1_remove_leftmost(void) {
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
  // 48: $$left left_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__16_2;
}
static void cont__16_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* left */ = arguments->slots[0];
  // 50: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__16_3;
}
static void cont__16_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 50: ... :
  // 51:   remove_leftmost &left !key !value
  // 52:   !node.left_of left
  frame->slots[5] /* temp__2 */ = create_closure(entry__16_4, 0);
  // 53: :
  // 54:   !key key_of(node)
  // 55:   !value value_of(node)
  // 56:   !node right_of(node)
  frame->slots[6] /* temp__3 */ = create_closure(entry__16_6, 0);
  // 49: if
  // 50:   left.is_defined:
  // 51:     remove_leftmost &left !key !value
  // 52:     !node.left_of left
  // 53:   :
  // 54:     !key key_of(node)
  // 55:     !value value_of(node)
  // 56:     !node right_of(node)
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
  frame->cont = cont__16_10;
}
static void entry__16_4(void) {
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
  // 51: remove_leftmost &left !key !value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  result_count = 3;
  myself = var._remove_leftmost;
  func = myself->type;
  frame->cont = cont__16_5;
}
static void cont__16_5(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* left */ = arguments->slots[0];
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[1];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[2];
  // 52: !node.left_of left
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* left */;
  // 52: !node.left_of
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
static void entry__16_6(void) {
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
  // 54: !key key_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__16_7;
}
static void cont__16_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* key */ = arguments->slots[0];
  // 55: !value value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__16_8;
}
static void cont__16_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[0];
  // 56: !node right_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__16_9;
}
static void cont__16_9(void) {
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
static void cont__16_10(void) {
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
static void entry__17_1_remove_rightmost(void) {
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
  // 64: $$right right_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__17_2;
}
static void cont__17_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* right */ = arguments->slots[0];
  // 66: right.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* right */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__17_3;
}
static void cont__17_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 66: ... :
  // 67:   remove_rightmost &right !key !value
  // 68:   !node.right_of right
  frame->slots[5] /* temp__2 */ = create_closure(entry__17_4, 0);
  // 69: :
  // 70:   !key key_of(node)
  // 71:   !value value_of(node)
  // 72:   !node left_of(node)
  frame->slots[6] /* temp__3 */ = create_closure(entry__17_6, 0);
  // 65: if
  // 66:   right.is_defined:
  // 67:     remove_rightmost &right !key !value
  // 68:     !node.right_of right
  // 69:   :
  // 70:     !key key_of(node)
  // 71:     !value value_of(node)
  // 72:     !node left_of(node)
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
  frame->cont = cont__17_10;
}
static void entry__17_4(void) {
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
  // 67: remove_rightmost &right !key !value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 3;
  myself = var._remove_rightmost;
  func = myself->type;
  frame->cont = cont__17_5;
}
static void cont__17_5(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[1];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[2];
  // 68: !node.right_of right
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* right */;
  // 68: !node.right_of
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
static void entry__17_6(void) {
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
  // 70: !key key_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__17_7;
}
static void cont__17_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* key */ = arguments->slots[0];
  // 71: !value value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__17_8;
}
static void cont__17_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[0];
  // 72: !node left_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__17_9;
}
static void cont__17_9(void) {
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
static void cont__17_10(void) {
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
static void entry__24_1_fetch_first(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // myself: 0
  // left: 1
  frame->slots[1] /* left */ = create_cell();
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
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* left */ = arguments->slots[0];
  // 91: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_3;
}
static void cont__24_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 91: ... :
  // 92:   fetch_first &left $head
  // 93:   !myself.left_of left
  // 94:   -> head
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_4, 0);
  // 95: :
  // 96:   $head myself
  // 97:   !myself right_of(myself)
  // 98:   -> head
  frame->slots[4] /* temp__3 */ = create_closure(entry__24_6, 0);
  // 90: if
  // 91:   left.is_defined:
  // 92:     fetch_first &left $head
  // 93:     !myself.left_of left
  // 94:     -> head
  // 95:   :
  // 96:     $head myself
  // 97:     !myself right_of(myself)
  // 98:     -> head
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_8;
}
static void entry__24_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // left: 0
  // myself: 1
  // head: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* left */
  frame->slots[1] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[2] /* head */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 92: fetch_first &left $head
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  result_count = 2;
  myself = var._fetch_first;
  func = myself->type;
  frame->cont = cont__24_5;
}
static void cont__24_5(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* left */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 92: ... head
  initialize_future(frame->slots[2] /* head */, frame->slots[3] /* temp__1 */);
  // 93: !myself.left_of left
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* left */;
  // 93: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* myself */ = temp;

  }
  // 94: -> head
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* head */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // myself: 0
  // head: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  // _define $head myself
  frame->slots[1] /* head */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 96: $head myself
  initialize_maybe_future(frame->slots[1] /* head */, ((CELL *)frame->slots[0])->contents /* myself */);
  // 97: !myself right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__24_7;
}
static void cont__24_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* myself */ = arguments->slots[0];
  // 98: -> head
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* head */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_8(void) {
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
static void entry__25_1_retrieve_item(void) {
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
  // 106: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 106: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_3, 0);
  // 106: if myself.is_undefined: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_4;
}
static void entry__25_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 106: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 107: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__25_5;
}
static void cont__25_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 109: -> key == my_key: return myself
  frame->slots[4] /* temp__1 */ = create_closure(entry__25_6, 0);
  // 110: -> key < my_key: return retrieve_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_9, 0);
  // 111: -> key > my_key: return retrieve_item(right_of(myself) key)
  frame->slots[6] /* temp__3 */ = create_closure(entry__25_14, 0);
  // 108: cond
  // 109:   -> key == my_key: return myself
  // 110:   -> key < my_key: return retrieve_item(left_of(myself) key)
  // 111:   -> key > my_key: return retrieve_item(right_of(myself) key)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__25_19;
}
static void entry__25_16(void) {
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
  // 111: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__25_17;
}
static void cont__25_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 111: ... retrieve_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__25_18;
}
static void cont__25_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 111: ... return retrieve_item(right_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_11(void) {
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
  // 110: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__25_12;
}
static void cont__25_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 110: ... retrieve_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__25_13;
}
static void cont__25_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 110: ... return retrieve_item(left_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // myself: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: ... return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_6(void) {
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
  // 109: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_7;
}
static void cont__25_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 109: ... : return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_8, 0);
  // 109: -> key == my_key: return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_9(void) {
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
  // 110: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__25_10;
}
static void cont__25_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 110: ... : return retrieve_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_11, 0);
  // 110: -> key < my_key: return retrieve_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_14(void) {
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
  // 111: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__25_15;
}
static void cont__25_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 111: ... : return retrieve_item(right_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_16, 0);
  // 111: -> key > my_key: return retrieve_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_19(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__26_1_add_item(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // myself: 0
  // previous: 1
  // next: 2
  // key: 3
  // value: 4
  // return: 5
  // my_key: 6
  frame->slots[5] /* return */ = create_continuation();
  frame->slots[6] /* my_key */ = create_future();
  if (argument_count != 5) {
    invalid_arguments_error();
    return;
  }
  // 122: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__26_2;
}
static void cont__26_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 122: ... :
  // 123:   return
  // 124:     empty_node
  // 125:       .previous_of previous
  // 126:       .next_of next
  // 127:       .key_of key
  // 128:       .value_of value
  // 129:     INSERT
  frame->slots[8] /* temp__2 */ = create_closure(entry__26_3, 0);
  // 122: if myself.is_undefined:
  // 123:   return
  // 124:     empty_node
  // 125:       .previous_of previous
  // 126:       .next_of next
  // 127:       .key_of key
  // 128:       .value_of value
  // 129:     INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__26_4;
}
static void entry__26_3(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // return: 0
  // previous: 1
  // next: 2
  // key: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* previous */
  frame->slots[2] = myself->closure.frame->slots[2]; /* next */
  frame->slots[3] = myself->closure.frame->slots[3]; /* key */
  frame->slots[4] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 124: empty_node
  // 125:   .previous_of previous
  // 126:   .next_of next
  // 127:   .key_of key
  // 128:   .value_of value
  {
    NODE *temp = clone_object_and_attributes(var._empty_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__previous_of, frame->slots[1] /* previous */);
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[2] /* next */);
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[3] /* key */);
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* value */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 123: return
  // 124:   empty_node
  // 125:     .previous_of previous
  // 126:     .next_of next
  // 127:     .key_of key
  // 128:     .value_of value
  // 129:   INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = var._INSERT;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 130: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__26_5;
}
static void cont__26_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* my_key */, arguments->slots[0]);
  // 132: -> key == my_key: return myself(.value_of value) UPDATE
  frame->slots[7] /* temp__1 */ = create_closure(entry__26_6, 0);
  // 133: -> key < my_key:
  // 134:   add_item $left $mode left_of(myself) previous next key value
  // 135:   return myself(.left_of left) mode
  frame->slots[8] /* temp__2 */ = create_closure(entry__26_9, 0);
  // 136: -> key > my_key:
  // 137:   add_item $right $mode right_of(myself) previous next key value
  // 138:   return myself(.right_of right) mode
  frame->slots[9] /* temp__3 */ = create_closure(entry__26_14, 0);
  // 131: cond
  // 132:   -> key == my_key: return myself(.value_of value) UPDATE
  // 133:   -> key < my_key:
  // 134:     add_item $left $mode left_of(myself) previous next key value
  // 135:     return myself(.left_of left) mode
  // 136:   -> key > my_key:
  // 137:     add_item $right $mode right_of(myself) previous next key value
  // 138:     return myself(.right_of right) mode
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__26_19;
}
static void entry__26_16(void) {
  allocate_initialized_frame_gc(6, 11);
  // slot allocations:
  // myself: 0
  // previous: 1
  // next: 2
  // key: 3
  // value: 4
  // return: 5
  // right: 6
  // mode: 7
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* previous */
  frame->slots[2] = myself->closure.frame->slots[4]; /* next */
  frame->slots[3] = myself->closure.frame->slots[1]; /* key */
  frame->slots[4] = myself->closure.frame->slots[5]; /* value */
  frame->slots[5] = myself->closure.frame->slots[6]; /* return */
  frame->slots[6] /* right */ = create_future();
  frame->slots[7] /* mode */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 137: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__26_17;
}
static void cont__26_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 137: add_item $right $mode right_of(myself) previous next key value
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* previous */;
  arguments->slots[2] = frame->slots[2] /* next */;
  arguments->slots[3] = frame->slots[3] /* key */;
  arguments->slots[4] = frame->slots[4] /* value */;
  result_count = 2;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__26_18;
}
static void cont__26_18(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  frame->slots[10] /* temp__3 */ = arguments->slots[1];
  // 137: ... right
  initialize_future(frame->slots[6] /* right */, frame->slots[9] /* temp__2 */);
  // 137: ... mode
  initialize_future(frame->slots[7] /* mode */, frame->slots[10] /* temp__3 */);
  // 138: ... myself(.right_of right)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[6] /* right */);
    frame->slots[8] /* temp__1 */ = temp;

  }
  // 138: return myself(.right_of right) mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* mode */;
  result_count = frame->caller_result_count;
  myself = frame->slots[5] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_11(void) {
  allocate_initialized_frame_gc(6, 11);
  // slot allocations:
  // myself: 0
  // previous: 1
  // next: 2
  // key: 3
  // value: 4
  // return: 5
  // left: 6
  // mode: 7
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* previous */
  frame->slots[2] = myself->closure.frame->slots[4]; /* next */
  frame->slots[3] = myself->closure.frame->slots[0]; /* key */
  frame->slots[4] = myself->closure.frame->slots[5]; /* value */
  frame->slots[5] = myself->closure.frame->slots[6]; /* return */
  frame->slots[6] /* left */ = create_future();
  frame->slots[7] /* mode */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 134: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__26_12;
}
static void cont__26_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 134: add_item $left $mode left_of(myself) previous next key value
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* previous */;
  arguments->slots[2] = frame->slots[2] /* next */;
  arguments->slots[3] = frame->slots[3] /* key */;
  arguments->slots[4] = frame->slots[4] /* value */;
  result_count = 2;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__26_13;
}
static void cont__26_13(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  frame->slots[10] /* temp__3 */ = arguments->slots[1];
  // 134: ... left
  initialize_future(frame->slots[6] /* left */, frame->slots[9] /* temp__2 */);
  // 134: ... mode
  initialize_future(frame->slots[7] /* mode */, frame->slots[10] /* temp__3 */);
  // 135: ... myself(.left_of left)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[6] /* left */);
    frame->slots[8] /* temp__1 */ = temp;

  }
  // 135: return myself(.left_of left) mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* mode */;
  result_count = frame->caller_result_count;
  myself = frame->slots[5] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_8(void) {
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
  // 132: ... myself(.value_of value)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[2] /* value */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 132: ... return myself(.value_of value) UPDATE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = var._UPDATE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_6(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // key: 0
  // my_key: 1
  // return: 2
  // myself: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[3]; /* key */
  frame->slots[1] = myself->closure.frame->slots[6]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[5]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[4] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 132: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__26_7;
}
static void cont__26_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 132: ... : return myself(.value_of value) UPDATE
  frame->slots[6] /* temp__2 */ = create_closure(entry__26_8, 0);
  // 132: -> key == my_key: return myself(.value_of value) UPDATE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_9(void) {
  allocate_initialized_frame_gc(7, 9);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // previous: 3
  // next: 4
  // value: 5
  // return: 6
  frame->slots[0] = myself->closure.frame->slots[3]; /* key */
  frame->slots[1] = myself->closure.frame->slots[6]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[1]; /* previous */
  frame->slots[4] = myself->closure.frame->slots[2]; /* next */
  frame->slots[5] = myself->closure.frame->slots[4]; /* value */
  frame->slots[6] = myself->closure.frame->slots[5]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 133: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__26_10;
}
static void cont__26_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 133: ... :
  // 134:   add_item $left $mode left_of(myself) previous next key value
  // 135:   return myself(.left_of left) mode
  frame->slots[8] /* temp__2 */ = create_closure(entry__26_11, 0);
  // 133: -> key < my_key:
  // 134:   add_item $left $mode left_of(myself) previous next key value
  // 135:   return myself(.left_of left) mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_14(void) {
  allocate_initialized_frame_gc(7, 9);
  // slot allocations:
  // my_key: 0
  // key: 1
  // myself: 2
  // previous: 3
  // next: 4
  // value: 5
  // return: 6
  frame->slots[0] = myself->closure.frame->slots[6]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[1]; /* previous */
  frame->slots[4] = myself->closure.frame->slots[2]; /* next */
  frame->slots[5] = myself->closure.frame->slots[4]; /* value */
  frame->slots[6] = myself->closure.frame->slots[5]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 136: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__26_15;
}
static void cont__26_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 136: ... :
  // 137:   add_item $right $mode right_of(myself) previous next key value
  // 138:   return myself(.right_of right) mode
  frame->slots[8] /* temp__2 */ = create_closure(entry__26_16, 0);
  // 136: -> key > my_key:
  // 137:   add_item $right $mode right_of(myself) previous next key value
  // 138:   return myself(.right_of right) mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__26_19(void) {
  myself = frame->slots[5] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__27_1_update_item(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // updater: 2
  // my_key: 3
  frame->slots[3] /* my_key */ = create_future();
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 146: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 148: -> key == my_key: updater &myself
  frame->slots[4] /* temp__1 */ = create_closure(entry__27_3, 0);
  // 149: -> key < my_key: update_item &myself.left_of key updater
  frame->slots[5] /* temp__2 */ = create_closure(entry__27_7, 0);
  // 150: -> key > my_key: update_item &myself.right_of key updater
  frame->slots[6] /* temp__3 */ = create_closure(entry__27_12, 0);
  // 147: cond
  // 148:   -> key == my_key: updater &myself
  // 149:   -> key < my_key: update_item &myself.left_of key updater
  // 150:   -> key > my_key: update_item &myself.right_of key updater
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__27_17;
}
static void entry__27_14(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // myself: 0
  // key: 1
  // updater: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* updater */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: ... myself.right_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__27_15;
}
static void cont__27_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 150: ... update_item &myself.right_of key updater
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[2] /* updater */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__27_16;
}
static void cont__27_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 150: ... &myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_9(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // myself: 0
  // key: 1
  // updater: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* updater */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 149: ... myself.left_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__27_10;
}
static void cont__27_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 149: ... update_item &myself.left_of key updater
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[2] /* updater */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__27_11;
}
static void cont__27_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 149: ... &myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // updater: 0
  // myself: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* updater */
  frame->slots[1] = myself->closure.frame->slots[3]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 148: ... updater &myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* myself */;
  result_count = 1;
  myself = frame->slots[0] /* updater */;
  func = myself->type;
  frame->cont = cont__27_6;
}
static void cont__27_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* myself */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_3(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // updater: 2
  // myself: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* updater */
  frame->slots[3] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 148: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 148: ... : updater &myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__27_5, 0);
  // 148: -> key == my_key: updater &myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_7(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // updater: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* updater */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 149: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__27_8;
}
static void cont__27_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 149: ... : update_item &myself.left_of key updater
  frame->slots[5] /* temp__2 */ = create_closure(entry__27_9, 0);
  // 149: -> key < my_key: update_item &myself.left_of key updater
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_12(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // my_key: 0
  // key: 1
  // myself: 2
  // updater: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* updater */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__27_13;
}
static void cont__27_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 150: ... : update_item &myself.right_of key updater
  frame->slots[5] /* temp__2 */ = create_closure(entry__27_14, 0);
  // 150: -> key > my_key: update_item &myself.right_of key updater
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__27_17(void) {
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
static void entry__28_1_remove_item(void) {
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
  // 162: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__28_2;
}
static void cont__28_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 162: ... : return NONE undefined # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_3, 0);
  // 162: if myself.is_undefined: return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__28_4;
}
static void entry__28_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 162: ... return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__28_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 163: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._key_of;
  func = myself->type;
  frame->cont = cont__28_5;
}
static void cont__28_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 165: -> key == my_key:
  // 166:   $left left_of(myself)
  // 167:   $$right right_of(myself)
  // 168:   if
  // 169:     left.is_defined:
  // 170:       if
  // 171:         right.is_defined:
  // 172:           fetch_first &right $head
  // 173:           return head(.left_of left .right_of right) myself
  // 174:         :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__28_6, 0);
  // 178: -> key < my_key:
  // 179:   remove_item $left $removed_item left_of(myself) key
  // 180:   if NONE == left: return NONE undefined # nothing removed
  // 181:   !myself.left_of left
  // 182:   return myself removed_item
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_18, 0);
  // 183: -> key > my_key:
  // 184:   remove_item $right $removed_item right_of(myself) key
  // 185:   if NONE == right: return NONE undefined # nothing removed
  // 186:   !myself.right_of right
  // 187:   return myself removed_item
  frame->slots[6] /* temp__3 */ = create_closure(entry__28_26, 0);
  // 164: cond
  // 165:   -> key == my_key:
  // 166:     $left left_of(myself)
  // 167:     $$right right_of(myself)
  // 168:     if
  // 169:       left.is_defined:
  // 170:         if
  // 171:           right.is_defined:
  // 172:             fetch_first &right $head
  // 173:             return head(.left_of left .right_of right) myself
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__28_34;
}
static void entry__28_28(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // right: 3
  // removed_item: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* right */ = create_future();
  frame->slots[4] /* removed_item */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 184: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__28_29;
}
static void cont__28_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 184: remove_item $right $removed_item right_of(myself) key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 2;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__28_30;
}
static void cont__28_30(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  frame->slots[7] /* temp__3 */ = arguments->slots[1];
  // 184: ... right
  initialize_future(frame->slots[3] /* right */, frame->slots[6] /* temp__2 */);
  // 184: ... removed_item
  initialize_future(frame->slots[4] /* removed_item */, frame->slots[7] /* temp__3 */);
  // 185: ... NONE == right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* right */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_31;
}
static void cont__28_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 185: ... : return NONE undefined # nothing removed
  frame->slots[6] /* temp__2 */ = create_closure(entry__28_32, 0);
  // 185: if NONE == right: return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__28_33;
}
static void entry__28_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__28_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 186: !myself.right_of right
  frame->slots[5] /* temp__1 */ = frame->slots[3] /* right */;
  // 186: !myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 187: return myself removed_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  arguments->slots[1] = frame->slots[4] /* removed_item */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_20(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // left: 3
  // removed_item: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* left */ = create_future();
  frame->slots[4] /* removed_item */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__28_21;
}
static void cont__28_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 179: remove_item $left $removed_item left_of(myself) key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 2;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__28_22;
}
static void cont__28_22(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  frame->slots[7] /* temp__3 */ = arguments->slots[1];
  // 179: ... left
  initialize_future(frame->slots[3] /* left */, frame->slots[6] /* temp__2 */);
  // 179: ... removed_item
  initialize_future(frame->slots[4] /* removed_item */, frame->slots[7] /* temp__3 */);
  // 180: ... NONE == left
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* left */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_23;
}
static void cont__28_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 180: ... : return NONE undefined # nothing removed
  frame->slots[6] /* temp__2 */ = create_closure(entry__28_24, 0);
  // 180: if NONE == left: return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__28_25;
}
static void entry__28_24(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__28_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 181: !myself.left_of left
  frame->slots[5] /* temp__1 */ = frame->slots[3] /* left */;
  // 181: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 182: return myself removed_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  arguments->slots[1] = frame->slots[4] /* removed_item */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_14(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // right: 0
  // return: 1
  // left: 2
  // myself: 3
  // head: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  frame->slots[3] = myself->closure.frame->slots[3]; /* myself */
  frame->slots[4] /* head */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: fetch_first &right $head
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 2;
  myself = var._fetch_first;
  func = myself->type;
  frame->cont = cont__28_15;
}
static void cont__28_15(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  frame->slots[5] /* temp__1 */ = arguments->slots[1];
  // 172: ... head
  initialize_future(frame->slots[4] /* head */, frame->slots[5] /* temp__1 */);
  // 173: ... head(.left_of left .right_of right)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* head */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[2] /* left */);
    set_attribute_value(temp->attributes, poly_idx__right_of, ((CELL *)frame->slots[0])->contents /* right */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 173: return head(.left_of left .right_of right) myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_16(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // left: 1
  // myself: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* left */
  frame->slots[2] = myself->closure.frame->slots[3]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: return left myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* left */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_12(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // right: 0
  // return: 1
  // left: 2
  // myself: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  frame->slots[3] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: right.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__28_13;
}
static void cont__28_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 171: ... :
  // 172:   fetch_first &right $head
  // 173:   return head(.left_of left .right_of right) myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_14, 0);
  // 174: :
  // 175:   return left myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__28_16, 0);
  // 170: if
  // 171:   right.is_defined:
  // 172:     fetch_first &right $head
  // 173:     return head(.left_of left .right_of right) myself
  // 174:   :
  // 175:     return left myself
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
static void entry__28_17(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // right: 1
  // myself: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* right */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 177: return right myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* right */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_8(void) {
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
  // 166: $left left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__28_9;
}
static void cont__28_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* left */, arguments->slots[0]);
  // 167: $$right right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__28_10;
}
static void cont__28_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* right */ = arguments->slots[0];
  // 169: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__28_11;
}
static void cont__28_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 169: ... :
  // 170:   if
  // 171:     right.is_defined:
  // 172:       fetch_first &right $head
  // 173:       return head(.left_of left .right_of right) myself
  // 174:     :
  // 175:       return left myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_12, 0);
  // 176: :
  // 177:   return right myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__28_17, 0);
  // 168: if
  // 169:   left.is_defined:
  // 170:     if
  // 171:       right.is_defined:
  // 172:         fetch_first &right $head
  // 173:         return head(.left_of left .right_of right) myself
  // 174:       :
  // 175:         return left myself
  // 176:   :
  // 177:     return right myself
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
static void entry__28_6(void) {
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
  // 165: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_7;
}
static void cont__28_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 165: ... :
  // 166:   $left left_of(myself)
  // 167:   $$right right_of(myself)
  // 168:   if
  // 169:     left.is_defined:
  // 170:       if
  // 171:         right.is_defined:
  // 172:           fetch_first &right $head
  // 173:           return head(.left_of left .right_of right) myself
  // 174:         :
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_8, 0);
  // 165: -> key == my_key:
  // 166:   $left left_of(myself)
  // 167:   $$right right_of(myself)
  // 168:   if
  // 169:     left.is_defined:
  // 170:       if
  // 171:         right.is_defined:
  // 172:           fetch_first &right $head
  // 173:           return head(.left_of left .right_of right) myself
  // 174:         :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_18(void) {
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
  // 178: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_19;
}
static void cont__28_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 178: ... :
  // 179:   remove_item $left $removed_item left_of(myself) key
  // 180:   if NONE == left: return NONE undefined # nothing removed
  // 181:   !myself.left_of left
  // 182:   return myself removed_item
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_20, 0);
  // 178: -> key < my_key:
  // 179:   remove_item $left $removed_item left_of(myself) key
  // 180:   if NONE == left: return NONE undefined # nothing removed
  // 181:   !myself.left_of left
  // 182:   return myself removed_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_26(void) {
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
  // 183: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_27;
}
static void cont__28_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 183: ... :
  // 184:   remove_item $right $removed_item right_of(myself) key
  // 185:   if NONE == right: return NONE undefined # nothing removed
  // 186:   !myself.right_of right
  // 187:   return myself removed_item
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_28, 0);
  // 183: -> key > my_key:
  // 184:   remove_item $right $removed_item right_of(myself) key
  // 185:   if NONE == right: return NONE undefined # nothing removed
  // 186:   !myself.right_of right
  // 187:   return myself removed_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__28_34(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__29_1_types__insert_order_table_private__set_item(void) {
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
  // 198: value.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* value */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 198: ... :
  // 199:   remove_item $$new_tree $removed_item tree_of(self) key
  // 200:   if NONE != new_tree:
  // 201:     $previous previous_of(removed_item)
  // 202:     $next next_of(removed_item)
  // 203:     if
  // 204:       previous.is_defined:
  // 205:         update_item &new_tree previous: (&item) !item.next_of next
  // 206:       :
  // 207:         !self.first_of next
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_3, 0);
  // 215: :
  // 216:   add_item $$new_tree $mode tree_of(self) last_of(self) undefined key value
  // 217:   if mode == INSERT:
  // 218:     if
  // 219:       last_of(self).is_defined:
  // 220:         update_item &new_tree last_of(self): (&item) !item.next_of key
  // 221:       :
  // 222:         !self.first_of key
  // 223:     !self.last_of key
  // 224:     inc &self.length_of
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__29_25, 0);
  // 197: if
  // 198:   value.is_undefined:
  // 199:     remove_item $$new_tree $removed_item tree_of(self) key
  // 200:     if NONE != new_tree:
  // 201:       $previous previous_of(removed_item)
  // 202:       $next next_of(removed_item)
  // 203:       if
  // 204:         previous.is_defined:
  // 205:           update_item &new_tree previous: (&item) !item.next_of next
  // 206:         :
  // ...
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
  frame->cont = cont__29_42;
}
static void entry__29_8(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // removed_item: 0
  // new_tree: 1
  // self: 2
  // previous: 3
  // next: 4
  frame->slots[0] = myself->closure.frame->slots[3]; /* removed_item */
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_tree */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  frame->slots[3] /* previous */ = create_future();
  frame->slots[4] /* next */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: $previous previous_of(removed_item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* removed_item */;
  result_count = 1;
  myself = var._previous_of;
  func = myself->type;
  frame->cont = cont__29_9;
}
static void cont__29_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* previous */, arguments->slots[0]);
  // 202: $next next_of(removed_item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* removed_item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__29_10;
}
static void cont__29_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* next */, arguments->slots[0]);
  // 204: previous.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* previous */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_11;
}
static void cont__29_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 204: ... :
  // 205:   update_item &new_tree previous: (&item) !item.next_of next
  frame->slots[6] /* temp__2 */ = create_closure(entry__29_12, 0);
  // 206: :
  // 207:   !self.first_of next
  frame->slots[7] /* temp__3 */ = create_closure(entry__29_15, 0);
  // 203: if
  // 204:   previous.is_defined:
  // 205:     update_item &new_tree previous: (&item) !item.next_of next
  // 206:   :
  // 207:     !self.first_of next
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_16;
}
static void entry__29_12(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // new_tree: 0
  // previous: 1
  // next: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_tree */
  frame->slots[1] = myself->closure.frame->slots[3]; /* previous */
  frame->slots[2] = myself->closure.frame->slots[4]; /* next */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 205: ... : (&item) !item.next_of next
  frame->slots[3] /* temp__1 */ = create_closure(entry__29_13, 1);
  // 205: update_item &new_tree previous: (&item) !item.next_of next
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_tree */;
  arguments->slots[1] = frame->slots[1] /* previous */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__29_14;
}
static void entry__29_13(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // item: 0
  // next: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* next */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 205: ... !item.next_of next
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* next */;
  // 205: ... !item.next_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_15(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // next: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* self */
  frame->slots[1] = myself->closure.frame->slots[4]; /* next */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: !self.first_of next
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* next */;
  // 207: !self.first_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__first_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 209: next.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* next */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_17;
}
static void cont__29_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 209: ... :
  // 210:   update_item &new_tree next: (&item) !item.previous_of previous
  frame->slots[6] /* temp__2 */ = create_closure(entry__29_18, 0);
  // 211: :
  // 212:   !self.last_of previous
  frame->slots[7] /* temp__3 */ = create_closure(entry__29_21, 0);
  // 208: if
  // 209:   next.is_defined:
  // 210:     update_item &new_tree next: (&item) !item.previous_of previous
  // 211:   :
  // 212:     !self.last_of previous
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_22;
}
static void entry__29_18(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // new_tree: 0
  // next: 1
  // previous: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_tree */
  frame->slots[1] = myself->closure.frame->slots[4]; /* next */
  frame->slots[2] = myself->closure.frame->slots[3]; /* previous */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 210: ... : (&item) !item.previous_of previous
  frame->slots[3] /* temp__1 */ = create_closure(entry__29_19, 1);
  // 210: update_item &new_tree next: (&item) !item.previous_of previous
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_tree */;
  arguments->slots[1] = frame->slots[1] /* next */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__29_20;
}
static void entry__29_19(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // item: 0
  // previous: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* previous */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 210: ... !item.previous_of previous
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* previous */;
  // 210: ... !item.previous_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__previous_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_21(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // previous: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* previous */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: !self.last_of previous
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* previous */;
  // 212: !self.last_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__last_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 213: !self.tree_of new_tree
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* new_tree */;
  // 213: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  // 214: ... self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__29_23;
}
static void cont__29_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 214: dec &self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__29_24;
}
static void cont__29_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 214: ... &self.length_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__length_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_3(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // key: 1
  // new_tree: 2
  // removed_item: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] /* new_tree */ = create_cell();
  frame->slots[3] /* removed_item */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 199: ... tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__29_4;
}
static void cont__29_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 199: remove_item $$new_tree $removed_item tree_of(self) key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 2;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__29_5;
}
static void cont__29_5(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* new_tree */ = arguments->slots[0];
  frame->slots[5] /* temp__2 */ = arguments->slots[1];
  // 199: ... removed_item
  initialize_future(frame->slots[3] /* removed_item */, frame->slots[5] /* temp__2 */);
  // 200: ... NONE != new_tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* new_tree */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_6;
}
static void cont__29_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 200: ... NONE != new_tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__29_7;
}
static void cont__29_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 200: ... :
  // 201:   $previous previous_of(removed_item)
  // 202:   $next next_of(removed_item)
  // 203:   if
  // 204:     previous.is_defined:
  // 205:       update_item &new_tree previous: (&item) !item.next_of next
  // 206:     :
  // 207:       !self.first_of next
  // 208:   if
  // 209:     next.is_defined:
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__29_8, 0);
  // 200: if NONE != new_tree:
  // 201:   $previous previous_of(removed_item)
  // 202:   $next next_of(removed_item)
  // 203:   if
  // 204:     previous.is_defined:
  // 205:       update_item &new_tree previous: (&item) !item.next_of next
  // 206:     :
  // 207:       !self.first_of next
  // 208:   if
  // 209:     next.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_25(void) {
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
  frame->slots[3] /* new_tree */ = create_cell();
  frame->slots[4] /* mode */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 216: ... tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__29_26;
}
static void cont__29_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 216: ... last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._last_of;
  func = myself->type;
  frame->cont = cont__29_27;
}
static void cont__29_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 216: add_item $$new_tree $mode tree_of(self) last_of(self) undefined key value
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = get__undefined();
  arguments->slots[3] = frame->slots[1] /* key */;
  arguments->slots[4] = frame->slots[2] /* value */;
  result_count = 2;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__29_28;
}
static void cont__29_28(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* new_tree */ = arguments->slots[0];
  frame->slots[7] /* temp__3 */ = arguments->slots[1];
  // 216: ... mode
  initialize_future(frame->slots[4] /* mode */, frame->slots[7] /* temp__3 */);
  // 217: ... mode == INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mode */;
  arguments->slots[1] = var._INSERT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_29;
}
static void cont__29_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 217: ... :
  // 218:   if
  // 219:     last_of(self).is_defined:
  // 220:       update_item &new_tree last_of(self): (&item) !item.next_of key
  // 221:     :
  // 222:       !self.first_of key
  // 223:   !self.last_of key
  // 224:   inc &self.length_of
  frame->slots[6] /* temp__2 */ = create_closure(entry__29_30, 0);
  // 217: if mode == INSERT:
  // 218:   if
  // 219:     last_of(self).is_defined:
  // 220:       update_item &new_tree last_of(self): (&item) !item.next_of key
  // 221:     :
  // 222:       !self.first_of key
  // 223:   !self.last_of key
  // 224:   inc &self.length_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_41;
}
static void entry__29_30(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // self: 0
  // new_tree: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* new_tree */
  frame->slots[2] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 219: last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._last_of;
  func = myself->type;
  frame->cont = cont__29_31;
}
static void cont__29_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 219: last_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_32;
}
static void cont__29_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 219: ... :
  // 220:   update_item &new_tree last_of(self): (&item) !item.next_of key
  frame->slots[5] /* temp__3 */ = create_closure(entry__29_33, 0);
  // 221: :
  // 222:   !self.first_of key
  frame->slots[6] /* temp__4 */ = create_closure(entry__29_37, 0);
  // 218: if
  // 219:   last_of(self).is_defined:
  // 220:     update_item &new_tree last_of(self): (&item) !item.next_of key
  // 221:   :
  // 222:     !self.first_of key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_38;
}
static void entry__29_33(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // new_tree: 0
  // self: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_tree */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[2]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: ... last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = var._last_of;
  func = myself->type;
  frame->cont = cont__29_34;
}
static void cont__29_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 220: ... : (&item) !item.next_of key
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_35, 1);
  // 220: update_item &new_tree last_of(self): (&item) !item.next_of key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_tree */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__29_36;
}
static void entry__29_35(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // item: 0
  // key: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 220: ... !item.next_of key
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* key */;
  // 220: ... !item.next_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_37(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 222: !self.first_of key
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* key */;
  // 222: !self.first_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__first_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 223: !self.last_of key
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* key */;
  // 223: !self.last_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__last_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 224: ... self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__29_39;
}
static void cont__29_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 224: inc &self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__29_40;
}
static void cont__29_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 224: ... &self.length_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__length_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 225: !self.tree_of new_tree
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* new_tree */;
  // 225: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_42(void) {
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
static void entry__30_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // item: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 235: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__30_6;
}
static void cont__30_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 235: ... -> value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 235: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_1_types__insert_order_table_private__get_item(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // key: 1
  // item: 2
  frame->slots[2] /* item */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 234: ... tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__30_2;
}
static void cont__30_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 234: $item retrieve_item(tree_of(self) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__30_3;
}
static void cont__30_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* item */, arguments->slots[0]);
  // 235: ... item.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* item */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_4;
}
static void cont__30_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 235: ... -> value_of(item)
  frame->slots[4] /* temp__2 */ = create_closure(entry__30_5, 0);
  // 235: if item.is_defined (-> value_of(item)) -> undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = func__30_7;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_1_types__insert_order_table_new_empty_collection(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 255: -> types::insert_order_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__insert_order_table;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_1_std__insert_order_table(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // initializers: 0
  // tab: 1
  frame->slots[1] /* tab */ = create_cell();
  frame->slots[0] /* initializers */ = from_arguments(0, argument_count-0);
  // 274: $$tab types::insert_order_table
  ((CELL *)frame->slots[1])->contents /* tab */ = var.types__insert_order_table;
  // 275: ... : (initializer)
  // 276:   !tab(std::key_of(initializer)) std::value_of(initializer)
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_2, 1);
  // 275: for_each initializers: (initializer)
  // 276:   !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializers */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_6;
}
static void entry__38_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // initializer: 0
  // tab: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* tab */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 276: !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializer */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__38_3;
}
static void cont__38_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 276: ... std::key_of(initializer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializer */;
  result_count = 1;
  myself = get__std__key_of();
  func = myself->type;
  frame->cont = cont__38_4;
}
static void cont__38_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 276: !tab(std::key_of(initializer))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* tab */;
  func = myself->type;
  frame->cont = cont__38_5;
}
static void cont__38_5(void) {
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
static void cont__38_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 277: -> tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* tab */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_8(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // tree: 0
  // key: 1
  // body: 2
  // item: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] /* item */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 290: $item retrieve_item(tree key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__39_9;
}
static void cont__39_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* item */, arguments->slots[0]);
  // 292: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__39_10;
}
static void cont__39_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 292: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__39_11;
}
static void cont__39_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 292: ... :
  // 293:   body key value_of(item)
  frame->slots[6] /* temp__3 */ = create_closure(entry__39_12, 0);
  // 294: :
  // 295:   body value_of(item)
  frame->slots[7] /* temp__4 */ = create_closure(entry__39_14, 0);
  // 291: if
  // 292:   parameter_count_of(body) == 2:
  // 293:     body key value_of(item)
  // 294:   :
  // 295:     body value_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_16;
}
static void entry__39_12(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // key: 1
  // item: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 293: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__39_13;
}
static void cont__39_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 293: body key value_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_14(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // body: 0
  // item: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[3]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 295: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__39_15;
}
static void cont__39_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 295: body value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 296: !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__39_17;
}
static void cont__39_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // key: 0
  // tree: 1
  // body: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* tree */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 289: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_7;
}
static void cont__39_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 289: ... :
  // 290:   $item retrieve_item(tree key)
  // 291:   if
  // 292:     parameter_count_of(body) == 2:
  // 293:       body key value_of(item)
  // 294:     :
  // 295:       body value_of(item)
  // 296:   !key next_of(item)
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_8, 0);
  // 289: ... -> key.is_defined:
  // 290:   $item retrieve_item(tree key)
  // 291:   if
  // 292:     parameter_count_of(body) == 2:
  // 293:       body key value_of(item)
  // 294:     :
  // 295:       body value_of(item)
  // 296:   !key next_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // tree: 1
  // body: 2
  // key: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[2] = myself->closure.frame->slots[1]; /* body */
  frame->slots[3] /* key */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 288: $$key first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._first_of;
  func = myself->type;
  frame->cont = cont__39_5;
}
static void cont__39_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* key */ = arguments->slots[0];
  // 289: ... -> key.is_defined:
  // 290:   $item retrieve_item(tree key)
  // 291:   if
  // 292:     parameter_count_of(body) == 2:
  // 293:       body key value_of(item)
  // 294:     :
  // 295:       body value_of(item)
  // 296:   !key next_of(item)
  frame->slots[4] /* temp__1 */ = create_closure(entry__39_6, 0);
  // 289: while -> key.is_defined:
  // 290:   $item retrieve_item(tree key)
  // 291:   if
  // 292:     parameter_count_of(body) == 2:
  // 293:       body key value_of(item)
  // 294:     :
  // 295:       body value_of(item)
  // 296:   !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_1_types__insert_order_table_for_each(void) {
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
  // 286: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__39_2;
}
static void cont__39_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* tree */, arguments->slots[0]);
  // 287: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_3;
}
static void cont__39_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 287: ... :
  // 288:   $$key first_of(self)
  // 289:   while -> key.is_defined:
  // 290:     $item retrieve_item(tree key)
  // 291:     if
  // 292:       parameter_count_of(body) == 2:
  // 293:         body key value_of(item)
  // 294:       :
  // 295:         body value_of(item)
  // 296:     !key next_of(item)
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_4, 0);
  // 287: if tree.is_defined:
  // 288:   $$key first_of(self)
  // 289:   while -> key.is_defined:
  // 290:     $item retrieve_item(tree key)
  // 291:     if
  // 292:       parameter_count_of(body) == 2:
  // 293:         body key value_of(item)
  // 294:       :
  // 295:         body value_of(item)
  // 296:     !key next_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__40_1_types__insert_order_table_for_each_from_to(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  // return: 4
  // tree: 5
  frame->slots[4] /* return */ = create_continuation();
  frame->slots[5] /* tree */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 308: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
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
  initialize_future(frame->slots[5] /* tree */, arguments->slots[0]);
  // 309: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* tree */;
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
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 309: ... :
  // 310:   $$key if(first.is_defined (-> first) -> first_of(self))
  // 311:   while -> key.is_defined:
  // 312:     $item retrieve_item(tree key)
  // 313:     if
  // 314:       parameter_count_of(body) == 2:
  // 315:         body key value_of(item)
  // 316:       :
  // 317:         body value_of(item)
  // 318:     if key == last return
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__40_4, 0);
  // 309: if tree.is_defined:
  // 310:   $$key if(first.is_defined (-> first) -> first_of(self))
  // 311:   while -> key.is_defined:
  // 312:     $item retrieve_item(tree key)
  // 313:     if
  // 314:       parameter_count_of(body) == 2:
  // 315:         body key value_of(item)
  // 316:       :
  // 317:         body value_of(item)
  // 318:     if key == last return
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__40_24;
}
static void entry__40_12(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // tree: 0
  // key: 1
  // body: 2
  // last: 3
  // return: 4
  // item: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] = myself->closure.frame->slots[3]; /* last */
  frame->slots[4] = myself->closure.frame->slots[4]; /* return */
  frame->slots[5] /* item */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 312: $item retrieve_item(tree key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__40_13;
}
static void cont__40_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* item */, arguments->slots[0]);
  // 314: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__40_14;
}
static void cont__40_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 314: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__40_15;
}
static void cont__40_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 314: ... :
  // 315:   body key value_of(item)
  frame->slots[8] /* temp__3 */ = create_closure(entry__40_16, 0);
  // 316: :
  // 317:   body value_of(item)
  frame->slots[9] /* temp__4 */ = create_closure(entry__40_18, 0);
  // 313: if
  // 314:   parameter_count_of(body) == 2:
  // 315:     body key value_of(item)
  // 316:   :
  // 317:     body value_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__40_20;
}
static void entry__40_16(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // key: 1
  // item: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[5]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 315: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__40_17;
}
static void cont__40_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 315: body key value_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__40_18(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // body: 0
  // item: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[5]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 317: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__40_19;
}
static void cont__40_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 317: body value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__40_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 318: ... key == last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* last */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__40_21;
}
static void cont__40_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 318: if key == last return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__40_22;
}
static void cont__40_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 319: !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__40_23;
}
static void cont__40_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__40_10(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // key: 0
  // tree: 1
  // body: 2
  // last: 3
  // return: 4
  frame->slots[0] = myself->closure.frame->slots[6]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[2] = myself->closure.frame->slots[3]; /* body */
  frame->slots[3] = myself->closure.frame->slots[4]; /* last */
  frame->slots[4] = myself->closure.frame->slots[5]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 311: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__40_11;
}
static void cont__40_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 311: ... :
  // 312:   $item retrieve_item(tree key)
  // 313:   if
  // 314:     parameter_count_of(body) == 2:
  // 315:       body key value_of(item)
  // 316:     :
  // 317:       body value_of(item)
  // 318:   if key == last return
  // 319:   !key next_of(item)
  frame->slots[6] /* temp__2 */ = create_closure(entry__40_12, 0);
  // 311: ... -> key.is_defined:
  // 312:   $item retrieve_item(tree key)
  // 313:   if
  // 314:     parameter_count_of(body) == 2:
  // 315:       body key value_of(item)
  // 316:     :
  // 317:       body value_of(item)
  // 318:   if key == last return
  // 319:   !key next_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__40_4(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // first: 0
  // self: 1
  // tree: 2
  // body: 3
  // last: 4
  // return: 5
  // key: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* first */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[5]; /* tree */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[2]; /* last */
  frame->slots[5] = myself->closure.frame->slots[4]; /* return */
  frame->slots[6] /* key */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 310: ... first.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__40_5;
}
static void cont__40_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 310: ... -> first
  frame->slots[8] /* temp__2 */ = create_closure(entry__40_6, 0);
  // 310: ... -> first_of(self)
  frame->slots[9] /* temp__3 */ = create_closure(entry__40_7, 0);
  // 310: $$key if(first.is_defined (-> first) -> first_of(self))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__40_9;
}
static void entry__40_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // first: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 310: ... -> first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__40_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 310: ... first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._first_of;
  func = myself->type;
  frame->cont = cont__40_8;
}
static void cont__40_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 310: ... -> first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__40_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* key */ = arguments->slots[0];
  // 311: ... -> key.is_defined:
  // 312:   $item retrieve_item(tree key)
  // 313:   if
  // 314:     parameter_count_of(body) == 2:
  // 315:       body key value_of(item)
  // 316:     :
  // 317:       body value_of(item)
  // 318:   if key == last return
  // 319:   !key next_of(item)
  frame->slots[7] /* temp__1 */ = create_closure(entry__40_10, 0);
  // 311: while -> key.is_defined:
  // 312:   $item retrieve_item(tree key)
  // 313:   if
  // 314:     parameter_count_of(body) == 2:
  // 315:       body key value_of(item)
  // 316:     :
  // 317:       body value_of(item)
  // 318:   if key == last return
  // 319:   !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__40_24(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__41_1_types__insert_order_table_for_each_from_down_to(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // self: 0
  // last: 1
  // first: 2
  // body: 3
  // return: 4
  // tree: 5
  frame->slots[4] /* return */ = create_continuation();
  frame->slots[5] /* tree */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 331: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
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
  initialize_future(frame->slots[5] /* tree */, arguments->slots[0]);
  // 332: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* tree */;
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
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 332: ... :
  // 333:   $$key if(last.is_defined (-> last) -> last_of(self))
  // 334:   while -> key.is_defined:
  // 335:     $item retrieve_item(tree key)
  // 336:     if
  // 337:       parameter_count_of(body) == 2:
  // 338:         body key value_of(item)
  // 339:       :
  // 340:         body value_of(item)
  // 341:     if key == first return
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__41_4, 0);
  // 332: if tree.is_defined:
  // 333:   $$key if(last.is_defined (-> last) -> last_of(self))
  // 334:   while -> key.is_defined:
  // 335:     $item retrieve_item(tree key)
  // 336:     if
  // 337:       parameter_count_of(body) == 2:
  // 338:         body key value_of(item)
  // 339:       :
  // 340:         body value_of(item)
  // 341:     if key == first return
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__41_24;
}
static void entry__41_12(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // tree: 0
  // key: 1
  // body: 2
  // first: 3
  // return: 4
  // item: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] = myself->closure.frame->slots[3]; /* first */
  frame->slots[4] = myself->closure.frame->slots[4]; /* return */
  frame->slots[5] /* item */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 335: $item retrieve_item(tree key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__41_13;
}
static void cont__41_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* item */, arguments->slots[0]);
  // 337: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__41_14;
}
static void cont__41_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 337: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__41_15;
}
static void cont__41_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 337: ... :
  // 338:   body key value_of(item)
  frame->slots[8] /* temp__3 */ = create_closure(entry__41_16, 0);
  // 339: :
  // 340:   body value_of(item)
  frame->slots[9] /* temp__4 */ = create_closure(entry__41_18, 0);
  // 336: if
  // 337:   parameter_count_of(body) == 2:
  // 338:     body key value_of(item)
  // 339:   :
  // 340:     body value_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__41_20;
}
static void entry__41_16(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // key: 1
  // item: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[5]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 338: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__41_17;
}
static void cont__41_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 338: body key value_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__41_18(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // body: 0
  // item: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[5]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 340: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__41_19;
}
static void cont__41_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 340: body value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__41_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 341: ... key == first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* first */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__41_21;
}
static void cont__41_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 341: if key == first return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__41_22;
}
static void cont__41_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 342: !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* item */;
  result_count = 1;
  myself = var._previous_of;
  func = myself->type;
  frame->cont = cont__41_23;
}
static void cont__41_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_10(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // key: 0
  // tree: 1
  // body: 2
  // first: 3
  // return: 4
  frame->slots[0] = myself->closure.frame->slots[6]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[2] = myself->closure.frame->slots[3]; /* body */
  frame->slots[3] = myself->closure.frame->slots[4]; /* first */
  frame->slots[4] = myself->closure.frame->slots[5]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 334: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__41_11;
}
static void cont__41_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 334: ... :
  // 335:   $item retrieve_item(tree key)
  // 336:   if
  // 337:     parameter_count_of(body) == 2:
  // 338:       body key value_of(item)
  // 339:     :
  // 340:       body value_of(item)
  // 341:   if key == first return
  // 342:   !key previous_of(item)
  frame->slots[6] /* temp__2 */ = create_closure(entry__41_12, 0);
  // 334: ... -> key.is_defined:
  // 335:   $item retrieve_item(tree key)
  // 336:   if
  // 337:     parameter_count_of(body) == 2:
  // 338:       body key value_of(item)
  // 339:     :
  // 340:       body value_of(item)
  // 341:   if key == first return
  // 342:   !key previous_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_4(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // last: 0
  // self: 1
  // tree: 2
  // body: 3
  // first: 4
  // return: 5
  // key: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* last */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[5]; /* tree */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[2]; /* first */
  frame->slots[5] = myself->closure.frame->slots[4]; /* return */
  frame->slots[6] /* key */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... last.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__41_5;
}
static void cont__41_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 333: ... -> last
  frame->slots[8] /* temp__2 */ = create_closure(entry__41_6, 0);
  // 333: ... -> last_of(self)
  frame->slots[9] /* temp__3 */ = create_closure(entry__41_7, 0);
  // 333: $$key if(last.is_defined (-> last) -> last_of(self))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__41_9;
}
static void entry__41_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // last: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... -> last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._last_of;
  func = myself->type;
  frame->cont = cont__41_8;
}
static void cont__41_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 333: ... -> last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__41_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* key */ = arguments->slots[0];
  // 334: ... -> key.is_defined:
  // 335:   $item retrieve_item(tree key)
  // 336:   if
  // 337:     parameter_count_of(body) == 2:
  // 338:       body key value_of(item)
  // 339:     :
  // 340:       body value_of(item)
  // 341:   if key == first return
  // 342:   !key previous_of(item)
  frame->slots[7] /* temp__1 */ = create_closure(entry__41_10, 0);
  // 334: while -> key.is_defined:
  // 335:   $item retrieve_item(tree key)
  // 336:   if
  // 337:     parameter_count_of(body) == 2:
  // 338:       body key value_of(item)
  // 339:     :
  // 340:       body value_of(item)
  // 341:   if key == first return
  // 342:   !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__41_24(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__42_1_types__insert_order_table_update_each(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // body: 1
  // tree: 2
  frame->slots[2] /* tree */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 351: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__42_2;
}
static void cont__42_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* tree */ = arguments->slots[0];
  // 352: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__42_3;
}
static void cont__42_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 352: ... :
  // 353:   $$key first_of(self)
  // 354:   while -> key.is_defined:
  // 355:     update_item &tree key: (&item)
  // 356:       body key &item.value_of
  // 357:       !key next_of(item)
  // 358:   !self.tree_of tree
  frame->slots[4] /* temp__2 */ = create_closure(entry__42_4, 0);
  // 352: if tree.is_defined:
  // 353:   $$key first_of(self)
  // 354:   while -> key.is_defined:
  // 355:     update_item &tree key: (&item)
  // 356:       body key &item.value_of
  // 357:       !key next_of(item)
  // 358:   !self.tree_of tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__42_15;
}
static void entry__42_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // tree: 1
  // body: 2
  // key: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[2] = myself->closure.frame->slots[1]; /* body */
  frame->slots[3] /* key */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 353: $$key first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._first_of;
  func = myself->type;
  frame->cont = cont__42_5;
}
static void cont__42_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* key */ = arguments->slots[0];
  // 354: ... -> key.is_defined:
  // 355:   update_item &tree key: (&item)
  // 356:     body key &item.value_of
  // 357:     !key next_of(item)
  frame->slots[4] /* temp__1 */ = create_closure(entry__42_6, 0);
  // 354: while -> key.is_defined:
  // 355:   update_item &tree key: (&item)
  // 356:     body key &item.value_of
  // 357:     !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__42_14;
}
static void entry__42_8(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // tree: 0
  // key: 1
  // body: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 355: ... : (&item)
  // 356:   body key &item.value_of
  // 357:   !key next_of(item)
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_9, 1);
  // 355: update_item &tree key: (&item)
  // 356:   body key &item.value_of
  // 357:   !key next_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__42_13;
}
static void entry__42_9(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // item: 0
  // body: 1
  // key: 2
  frame->slots[1] = myself->closure.frame->slots[2]; /* body */
  frame->slots[2] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 356: ... item.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__42_10;
}
static void cont__42_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 356: body key &item.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__42_11;
}
static void cont__42_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 356: ... &item.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  // 357: !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__42_12;
}
static void cont__42_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* key */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__42_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__42_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // key: 0
  // tree: 1
  // body: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* tree */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 354: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__42_7;
}
static void cont__42_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 354: ... :
  // 355:   update_item &tree key: (&item)
  // 356:     body key &item.value_of
  // 357:     !key next_of(item)
  frame->slots[4] /* temp__2 */ = create_closure(entry__42_8, 0);
  // 354: ... -> key.is_defined:
  // 355:   update_item &tree key: (&item)
  // 356:     body key &item.value_of
  // 357:     !key next_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__42_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 358: !self.tree_of tree
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* tree */;
  // 358: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__42_15(void) {
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
static void entry__43_1_types__insert_order_table_update_each_from_to(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  // tree: 4
  frame->slots[4] /* tree */ = create_cell();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 369: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__43_2;
}
static void cont__43_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 370: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__43_3;
}
static void cont__43_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 370: ... :
  // 371:   $$key if(first.is_defined (-> first) -> first_of(self))
  // 372:   do: (-> break)
  // 373:     while -> key.is_defined:
  // 374:       update_item &tree key: (&item)
  // 375:         body key &item.value_of
  // 376:         if key == last break
  // 377:         !key next_of(item)
  // 378:   !self.tree_of tree
  frame->slots[6] /* temp__2 */ = create_closure(entry__43_4, 0);
  // 370: if tree.is_defined:
  // 371:   $$key if(first.is_defined (-> first) -> first_of(self))
  // 372:   do: (-> break)
  // 373:     while -> key.is_defined:
  // 374:       update_item &tree key: (&item)
  // 375:         body key &item.value_of
  // 376:         if key == last break
  // 377:         !key next_of(item)
  // 378:   !self.tree_of tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__43_23;
}
static void entry__43_4(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // first: 0
  // self: 1
  // tree: 2
  // body: 3
  // last: 4
  // key: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* first */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[4]; /* tree */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[2]; /* last */
  frame->slots[5] /* key */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 371: ... first.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__43_5;
}
static void cont__43_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 371: ... -> first
  frame->slots[7] /* temp__2 */ = create_closure(entry__43_6, 0);
  // 371: ... -> first_of(self)
  frame->slots[8] /* temp__3 */ = create_closure(entry__43_7, 0);
  // 371: $$key if(first.is_defined (-> first) -> first_of(self))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__43_9;
}
static void entry__43_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // first: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 371: ... -> first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 371: ... first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._first_of;
  func = myself->type;
  frame->cont = cont__43_8;
}
static void cont__43_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 371: ... -> first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__43_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  // 372: ... : (-> break)
  // 373:   while -> key.is_defined:
  // 374:     update_item &tree key: (&item)
  // 375:       body key &item.value_of
  // 376:       if key == last break
  // 377:       !key next_of(item)
  frame->slots[6] /* temp__1 */ = create_closure(entry__43_10, 0);
  // 372: do: (-> break)
  // 373:   while -> key.is_defined:
  // 374:     update_item &tree key: (&item)
  // 375:       body key &item.value_of
  // 376:       if key == last break
  // 377:       !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__43_22;
}
static void entry__43_10(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // break: 0
  // key: 1
  // tree: 2
  // body: 3
  // last: 4
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[5]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[4]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 373: ... -> key.is_defined:
  // 374:   update_item &tree key: (&item)
  // 375:     body key &item.value_of
  // 376:     if key == last break
  // 377:     !key next_of(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__43_11, 0);
  // 373: while -> key.is_defined:
  // 374:   update_item &tree key: (&item)
  // 375:     body key &item.value_of
  // 376:     if key == last break
  // 377:     !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__43_21;
}
static void entry__43_13(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // tree: 0
  // key: 1
  // body: 2
  // last: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] = myself->closure.frame->slots[3]; /* last */
  frame->slots[4] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 374: ... : (&item)
  // 375:   body key &item.value_of
  // 376:   if key == last break
  // 377:   !key next_of(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__43_14, 1);
  // 374: update_item &tree key: (&item)
  // 375:   body key &item.value_of
  // 376:   if key == last break
  // 377:   !key next_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__43_20;
}
static void entry__43_14(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // item: 0
  // body: 1
  // key: 2
  // last: 3
  // break: 4
  frame->slots[1] = myself->closure.frame->slots[2]; /* body */
  frame->slots[2] = myself->closure.frame->slots[1]; /* key */
  frame->slots[3] = myself->closure.frame->slots[3]; /* last */
  frame->slots[4] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 375: ... item.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__43_15;
}
static void cont__43_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 375: body key &item.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__43_16;
}
static void cont__43_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 375: ... &item.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  // 376: ... key == last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* last */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__43_17;
}
static void cont__43_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 376: if key == last break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__43_18;
}
static void cont__43_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 377: !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__43_19;
}
static void cont__43_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* key */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__43_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_11(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // key: 0
  // tree: 1
  // body: 2
  // last: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[2] = myself->closure.frame->slots[3]; /* body */
  frame->slots[3] = myself->closure.frame->slots[4]; /* last */
  frame->slots[4] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 373: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__43_12;
}
static void cont__43_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 373: ... :
  // 374:   update_item &tree key: (&item)
  // 375:     body key &item.value_of
  // 376:     if key == last break
  // 377:     !key next_of(item)
  frame->slots[6] /* temp__2 */ = create_closure(entry__43_13, 0);
  // 373: ... -> key.is_defined:
  // 374:   update_item &tree key: (&item)
  // 375:     body key &item.value_of
  // 376:     if key == last break
  // 377:     !key next_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__43_21(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__43_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 378: !self.tree_of tree
  frame->slots[6] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* tree */;
  // 378: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[6] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__43_23(void) {
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
static void entry__44_1_types__insert_order_table_update_each_from_down_to(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // self: 0
  // last: 1
  // first: 2
  // body: 3
  // tree: 4
  frame->slots[4] /* tree */ = create_cell();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 389: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__44_2;
}
static void cont__44_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 390: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__44_3;
}
static void cont__44_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 390: ... :
  // 391:   $$key if(last.is_defined (-> last) -> last_of(self))
  // 392:   do: (-> break)
  // 393:     while -> key.is_defined:
  // 394:       update_item &tree key: (&item)
  // 395:         body key &item.value_of
  // 396:         if key == first break
  // 397:         !key previous_of(item)
  // 398:   !self.tree_of tree
  frame->slots[6] /* temp__2 */ = create_closure(entry__44_4, 0);
  // 390: if tree.is_defined:
  // 391:   $$key if(last.is_defined (-> last) -> last_of(self))
  // 392:   do: (-> break)
  // 393:     while -> key.is_defined:
  // 394:       update_item &tree key: (&item)
  // 395:         body key &item.value_of
  // 396:         if key == first break
  // 397:         !key previous_of(item)
  // 398:   !self.tree_of tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__44_23;
}
static void entry__44_4(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // last: 0
  // self: 1
  // tree: 2
  // body: 3
  // first: 4
  // key: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* last */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[4]; /* tree */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[2]; /* first */
  frame->slots[5] /* key */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 391: ... last.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__44_5;
}
static void cont__44_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 391: ... -> last
  frame->slots[7] /* temp__2 */ = create_closure(entry__44_6, 0);
  // 391: ... -> last_of(self)
  frame->slots[8] /* temp__3 */ = create_closure(entry__44_7, 0);
  // 391: $$key if(last.is_defined (-> last) -> last_of(self))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__44_9;
}
static void entry__44_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // last: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 391: ... -> last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__44_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 391: ... last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._last_of;
  func = myself->type;
  frame->cont = cont__44_8;
}
static void cont__44_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 391: ... -> last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__44_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  // 392: ... : (-> break)
  // 393:   while -> key.is_defined:
  // 394:     update_item &tree key: (&item)
  // 395:       body key &item.value_of
  // 396:       if key == first break
  // 397:       !key previous_of(item)
  frame->slots[6] /* temp__1 */ = create_closure(entry__44_10, 0);
  // 392: do: (-> break)
  // 393:   while -> key.is_defined:
  // 394:     update_item &tree key: (&item)
  // 395:       body key &item.value_of
  // 396:       if key == first break
  // 397:       !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__44_22;
}
static void entry__44_10(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // break: 0
  // key: 1
  // tree: 2
  // body: 3
  // first: 4
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[5]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[4]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 393: ... -> key.is_defined:
  // 394:   update_item &tree key: (&item)
  // 395:     body key &item.value_of
  // 396:     if key == first break
  // 397:     !key previous_of(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__44_11, 0);
  // 393: while -> key.is_defined:
  // 394:   update_item &tree key: (&item)
  // 395:     body key &item.value_of
  // 396:     if key == first break
  // 397:     !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__44_21;
}
static void entry__44_13(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // tree: 0
  // key: 1
  // body: 2
  // first: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] = myself->closure.frame->slots[3]; /* first */
  frame->slots[4] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 394: ... : (&item)
  // 395:   body key &item.value_of
  // 396:   if key == first break
  // 397:   !key previous_of(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__44_14, 1);
  // 394: update_item &tree key: (&item)
  // 395:   body key &item.value_of
  // 396:   if key == first break
  // 397:   !key previous_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__44_20;
}
static void entry__44_14(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // item: 0
  // body: 1
  // key: 2
  // first: 3
  // break: 4
  frame->slots[1] = myself->closure.frame->slots[2]; /* body */
  frame->slots[2] = myself->closure.frame->slots[1]; /* key */
  frame->slots[3] = myself->closure.frame->slots[3]; /* first */
  frame->slots[4] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 395: ... item.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__44_15;
}
static void cont__44_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 395: body key &item.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__44_16;
}
static void cont__44_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 395: ... &item.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  // 396: ... key == first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* first */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__44_17;
}
static void cont__44_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 396: if key == first break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__44_18;
}
static void cont__44_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 397: !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._previous_of;
  func = myself->type;
  frame->cont = cont__44_19;
}
static void cont__44_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* key */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__44_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__44_11(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // key: 0
  // tree: 1
  // body: 2
  // first: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[2] = myself->closure.frame->slots[3]; /* body */
  frame->slots[3] = myself->closure.frame->slots[4]; /* first */
  frame->slots[4] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 393: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__44_12;
}
static void cont__44_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 393: ... :
  // 394:   update_item &tree key: (&item)
  // 395:     body key &item.value_of
  // 396:     if key == first break
  // 397:     !key previous_of(item)
  frame->slots[6] /* temp__2 */ = create_closure(entry__44_13, 0);
  // 393: ... -> key.is_defined:
  // 394:   update_item &tree key: (&item)
  // 395:     body key &item.value_of
  // 396:     if key == first break
  // 397:     !key previous_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__44_21(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__44_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 398: !self.tree_of tree
  frame->slots[6] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* tree */;
  // 398: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[6] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__44_23(void) {
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
static void entry__45_1_types__insert_order_table_insert_before(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // self: 0
  // key: 1
  // new_key: 2
  // new_value: 3
  // tree: 4
  // before_key: 5
  // mode: 6
  frame->slots[4] /* tree */ = create_cell();
  frame->slots[5] /* before_key */ = create_cell();
  frame->slots[6] /* mode */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 409: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__45_2;
}
static void cont__45_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 410: $$before_key undefined
  ((CELL *)frame->slots[5])->contents /* before_key */ = get__undefined();
  // 411: ... : (&item)
  // 412:   !before_key previous_of(item)
  // 413:   !item.previous_of new_key
  frame->slots[7] /* temp__1 */ = create_closure(entry__45_3, 1);
  // 411: update_item &tree key: (&item)
  // 412:   !before_key previous_of(item)
  // 413:   !item.previous_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__45_5;
}
static void entry__45_3(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // item: 0
  // before_key: 1
  // new_key: 2
  frame->slots[1] = myself->closure.frame->slots[5]; /* before_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 412: !before_key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._previous_of;
  func = myself->type;
  frame->cont = cont__45_4;
}
static void cont__45_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* before_key */ = arguments->slots[0];
  // 413: !item.previous_of new_key
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* new_key */;
  // 413: !item.previous_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__previous_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__45_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 415: before_key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* before_key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__45_6;
}
static void cont__45_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 415: ... :
  // 416:   update_item &tree before_key: (&item) !item.next_of new_key
  frame->slots[8] /* temp__2 */ = create_closure(entry__45_7, 0);
  // 417: :
  // 418:   !self.first_of new_key
  frame->slots[9] /* temp__3 */ = create_closure(entry__45_10, 0);
  // 414: if
  // 415:   before_key.is_defined:
  // 416:     update_item &tree before_key: (&item) !item.next_of new_key
  // 417:   :
  // 418:     !self.first_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__45_11;
}
static void entry__45_7(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // tree: 0
  // before_key: 1
  // new_key: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[5]; /* before_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... : (&item) !item.next_of new_key
  frame->slots[3] /* temp__1 */ = create_closure(entry__45_8, 1);
  // 416: update_item &tree before_key: (&item) !item.next_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* before_key */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__45_9;
}
static void entry__45_8(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // item: 0
  // new_key: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 416: ... !item.next_of new_key
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_key */;
  // 416: ... !item.next_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__45_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__45_10(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // new_key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 418: !self.first_of new_key
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_key */;
  // 418: !self.first_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__first_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__45_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 419: add_item &tree $mode before_key key new_key new_value
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* before_key */;
  arguments->slots[2] = frame->slots[1] /* key */;
  arguments->slots[3] = frame->slots[2] /* new_key */;
  arguments->slots[4] = frame->slots[3] /* new_value */;
  result_count = 2;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__45_12;
}
static void cont__45_12(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  frame->slots[7] /* temp__1 */ = arguments->slots[1];
  // 419: ... mode
  initialize_future(frame->slots[6] /* mode */, frame->slots[7] /* temp__1 */);
  // 420: !self.tree_of tree
  frame->slots[7] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* tree */;
  // 420: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[7] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 421: ... mode != INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* mode */;
  arguments->slots[1] = var._INSERT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__45_13;
}
static void cont__45_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 421: ... mode != INSERT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__45_14;
}
static void cont__45_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 421: if mode != INSERT: raise "Invalid tree insert operation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__45_15;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__45_17;
}
static void entry__45_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 421: ... raise "Invalid tree insert operation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__45_16;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__45_17(void) {
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
static void entry__46_1_types__insert_order_table_insert_behind(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // self: 0
  // key: 1
  // new_key: 2
  // new_value: 3
  // tree: 4
  // behind_key: 5
  // mode: 6
  frame->slots[4] /* tree */ = create_cell();
  frame->slots[5] /* behind_key */ = create_cell();
  frame->slots[6] /* mode */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 432: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__46_2;
}
static void cont__46_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 433: $$behind_key undefined
  ((CELL *)frame->slots[5])->contents /* behind_key */ = get__undefined();
  // 434: ... : (&item)
  // 435:   !behind_key next_of(item)
  // 436:   !item.next_of new_key
  frame->slots[7] /* temp__1 */ = create_closure(entry__46_3, 1);
  // 434: update_item &tree key: (&item)
  // 435:   !behind_key next_of(item)
  // 436:   !item.next_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__46_5;
}
static void entry__46_3(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // item: 0
  // behind_key: 1
  // new_key: 2
  frame->slots[1] = myself->closure.frame->slots[5]; /* behind_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 435: !behind_key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__46_4;
}
static void cont__46_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* behind_key */ = arguments->slots[0];
  // 436: !item.next_of new_key
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* new_key */;
  // 436: !item.next_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__46_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 438: behind_key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* behind_key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__46_6;
}
static void cont__46_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 438: ... :
  // 439:   update_item &tree behind_key: (&item) !item.previous_of new_key
  frame->slots[8] /* temp__2 */ = create_closure(entry__46_7, 0);
  // 440: :
  // 441:   !self.last_of new_key
  frame->slots[9] /* temp__3 */ = create_closure(entry__46_10, 0);
  // 437: if
  // 438:   behind_key.is_defined:
  // 439:     update_item &tree behind_key: (&item) !item.previous_of new_key
  // 440:   :
  // 441:     !self.last_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__46_11;
}
static void entry__46_7(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // tree: 0
  // behind_key: 1
  // new_key: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[5]; /* behind_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 439: ... : (&item) !item.previous_of new_key
  frame->slots[3] /* temp__1 */ = create_closure(entry__46_8, 1);
  // 439: update_item &tree behind_key: (&item) !item.previous_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* behind_key */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__46_9;
}
static void entry__46_8(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // item: 0
  // new_key: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 439: ... !item.previous_of new_key
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_key */;
  // 439: ... !item.previous_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__previous_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__46_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__46_10(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // new_key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: !self.last_of new_key
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_key */;
  // 441: !self.last_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__last_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__46_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 442: add_item &tree $mode key behind_key new_key new_value
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = ((CELL *)frame->slots[5])->contents /* behind_key */;
  arguments->slots[3] = frame->slots[2] /* new_key */;
  arguments->slots[4] = frame->slots[3] /* new_value */;
  result_count = 2;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__46_12;
}
static void cont__46_12(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  frame->slots[7] /* temp__1 */ = arguments->slots[1];
  // 442: ... mode
  initialize_future(frame->slots[6] /* mode */, frame->slots[7] /* temp__1 */);
  // 443: !self.tree_of tree
  frame->slots[7] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* tree */;
  // 443: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[7] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 444: ... mode != INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* mode */;
  arguments->slots[1] = var._INSERT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__46_13;
}
static void cont__46_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 444: ... mode != INSERT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__46_14;
}
static void cont__46_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 444: if mode != INSERT: raise "Invalid tree insert operation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__46_15;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__46_16;
}
static void entry__46_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 444: ... raise "Invalid tree insert operation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__45_16;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__46_16(void) {
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
EXPORT void collect__basic__types__insert_order_table(void) {
  var.std__is_an_insert_order_table = collect_node(var.std__is_an_insert_order_table);
  var._NONE = collect_node(var._NONE);
  var._INSERT = collect_node(var._INSERT);
  var._UPDATE = collect_node(var._UPDATE);
  var._tree_of = collect_node(var._tree_of);
  var._first_of = collect_node(var._first_of);
  var._last_of = collect_node(var._last_of);
  var._key_of = collect_node(var._key_of);
  var._value_of = collect_node(var._value_of);
  var._left_of = collect_node(var._left_of);
  var._right_of = collect_node(var._right_of);
  var._next_of = collect_node(var._next_of);
  var._previous_of = collect_node(var._previous_of);
  var._remove_leftmost = collect_node(var._remove_leftmost);
  var._remove_rightmost = collect_node(var._remove_rightmost);
  var.types__insert_order_table = collect_node(var.types__insert_order_table);
  var._empty_node = collect_node(var._empty_node);
  var._fetch_first = collect_node(var._fetch_first);
  var._retrieve_item = collect_node(var._retrieve_item);
  var._add_item = collect_node(var._add_item);
  var._update_item = collect_node(var._update_item);
  var._remove_item = collect_node(var._remove_item);
  var.std__empty_insert_order_table = collect_node(var.std__empty_insert_order_table);
  var.std__insert_order_table = collect_node(var.std__insert_order_table);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__insert_order_table(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_an_insert_order_table", get__std__is_an_insert_order_table, &poly_idx__std__is_an_insert_order_table, &var.std__is_an_insert_order_table);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::tree_of", &poly_idx__tree_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::first_of", &poly_idx__first_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::last_of", &poly_idx__last_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::key_of", &poly_idx__key_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::value_of", &poly_idx__value_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::left_of", &poly_idx__left_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::right_of", &poly_idx__right_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::next_of", &poly_idx__next_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::previous_of", &poly_idx__previous_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__insert_order_table(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__0 = from_uint32(0U);
  number__2 = from_uint32(2U);
  unique__NONE = register_unique_item("NONE");
  unique__INSERT = register_unique_item("INSERT");
  unique__UPDATE = register_unique_item("UPDATE");
  func__16_1_remove_leftmost = create_function(entry__16_1_remove_leftmost, 1);
  func__17_1_remove_rightmost = create_function(entry__17_1_remove_rightmost, 1);
  func__24_1_fetch_first = create_function(entry__24_1_fetch_first, 1);
  func__25_1_retrieve_item = create_function(entry__25_1_retrieve_item, 2);
  func__26_1_add_item = create_function(entry__26_1_add_item, 5);
  func__27_1_update_item = create_function(entry__27_1_update_item, 3);
  func__28_1_remove_item = create_function(entry__28_1_remove_item, 2);
  func__29_1_types__insert_order_table_private__set_item = create_function(entry__29_1_types__insert_order_table_private__set_item, 3);
  func__30_7 = create_function(entry__30_7, 0);
  func__30_1_types__insert_order_table_private__get_item = create_function(entry__30_1_types__insert_order_table_private__get_item, 2);
  string__35_1 = from_latin_1_string("insert_order_table", 18);
  func__36_1_types__insert_order_table_new_empty_collection = create_function(entry__36_1_types__insert_order_table_new_empty_collection, 1);
  func__38_1_std__insert_order_table = create_function(entry__38_1_std__insert_order_table, -1);
  func__39_1_types__insert_order_table_for_each = create_function(entry__39_1_types__insert_order_table_for_each, 2);
  func__40_1_types__insert_order_table_for_each_from_to = create_function(entry__40_1_types__insert_order_table_for_each_from_to, 4);
  func__41_1_types__insert_order_table_for_each_from_down_to = create_function(entry__41_1_types__insert_order_table_for_each_from_down_to, 4);
  func__42_1_types__insert_order_table_update_each = create_function(entry__42_1_types__insert_order_table_update_each, 2);
  func__43_1_types__insert_order_table_update_each_from_to = create_function(entry__43_1_types__insert_order_table_update_each_from_to, 4);
  func__44_1_types__insert_order_table_update_each_from_down_to = create_function(entry__44_1_types__insert_order_table_update_each_from_down_to, 4);
  string__45_16 = from_latin_1_string("Invalid tree insert operation!", 30);
  func__45_15 = create_function(entry__45_15, 0);
  func__45_1_types__insert_order_table_insert_before = create_function(entry__45_1_types__insert_order_table_insert_before, 4);
  func__46_15 = create_function(entry__46_15, 0);
  func__46_1_types__insert_order_table_insert_behind = create_function(entry__46_1_types__insert_order_table_insert_behind, 4);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__insert_order_table(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__insert_order_table");
  set_used_namespaces(used_namespaces);
  assign_value(&var._NONE, unique__NONE);
  assign_value(&var._INSERT, unique__INSERT);
  assign_value(&var._UPDATE, unique__UPDATE);
  define_single_assign_static("types", "insert_order_table", get__types__insert_order_table, &var.types__insert_order_table);
  define_single_assign_static("std", "empty_insert_order_table", get__std__empty_insert_order_table, &var.std__empty_insert_order_table);
  define_single_assign_static("std", "insert_order_table", get__std__insert_order_table, &var.std__insert_order_table);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__insert_order_table(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__insert_order_table");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "empty_insert_order_table", &get__empty_insert_order_table, &get_value_or_future__empty_insert_order_table);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_polymorphic_function(NULL, "for_each_from_down_to", &get__for_each_from_down_to, &poly_idx__for_each_from_down_to);
  use_polymorphic_function(NULL, "for_each_from_to", &get__for_each_from_to, &poly_idx__for_each_from_to);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_polymorphic_function(NULL, "insert_before", &get__insert_before, &poly_idx__insert_before);
  use_polymorphic_function(NULL, "insert_behind", &get__insert_behind, &poly_idx__insert_behind);
  use_polymorphic_function(NULL, "is_an_insert_order_table", &get__is_an_insert_order_table, &poly_idx__is_an_insert_order_table);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_polymorphic_function(NULL, "length_of", &get__length_of, &poly_idx__length_of);
  use_polymorphic_function(NULL, "new_empty_collection", &get__new_empty_collection, &poly_idx__new_empty_collection);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_polymorphic_function("private", "get_item", &get__private__get_item, &poly_idx__private__get_item);
  use_polymorphic_function("private", "set_item", &get__private__set_item, &poly_idx__private__set_item);
  use_read_only(NULL, "raise", &get__raise, &get_value_or_future__raise);
  use_read_only(NULL, "register_collection_serializer", &get__register_collection_serializer, &get_value_or_future__register_collection_serializer);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_of", &get__std__key_of, &get_value_or_future__std__key_of);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "value_of", &get__std__value_of, &get_value_or_future__std__value_of);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "generic_table", &get__types__generic_table, &get_value_or_future__types__generic_table);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_polymorphic_function(NULL, "update_each", &get__update_each, &poly_idx__update_each);
  use_polymorphic_function(NULL, "update_each_from_down_to", &get__update_each_from_down_to, &poly_idx__update_each_from_down_to);
  use_polymorphic_function(NULL, "update_each_from_to", &get__update_each_from_to, &poly_idx__update_each_from_to);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  define_attribute("types", "object", poly_idx__is_an_insert_order_table, get__false());
  define_attribute("types", "insert_order_table", poly_idx__is_an_insert_order_table, get__true());
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__left_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__right_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__next_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__previous_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  define_method("types", "insert_order_table", poly_idx__private__set_item, func__29_1_types__insert_order_table_private__set_item);
  define_method("types", "insert_order_table", poly_idx__private__get_item, func__30_1_types__insert_order_table_private__get_item);
  define_attribute("types", "insert_order_table", poly_idx__tree_of, get__undefined());
  define_attribute("types", "insert_order_table", poly_idx__first_of, get__undefined());
  define_attribute("types", "insert_order_table", poly_idx__last_of, get__undefined());
  define_attribute("types", "insert_order_table", poly_idx__length_of, number__0);
  define_attribute("types", "insert_order_table", poly_idx__serialization_tag_of, string__35_1);
  define_method("types", "insert_order_table", poly_idx__new_empty_collection, func__36_1_types__insert_order_table_new_empty_collection);
  define_method("types", "insert_order_table", poly_idx__for_each, func__39_1_types__insert_order_table_for_each);
  define_method("types", "insert_order_table", poly_idx__for_each_from_to, func__40_1_types__insert_order_table_for_each_from_to);
  define_method("types", "insert_order_table", poly_idx__for_each_from_down_to, func__41_1_types__insert_order_table_for_each_from_down_to);
  define_method("types", "insert_order_table", poly_idx__update_each, func__42_1_types__insert_order_table_update_each);
  define_method("types", "insert_order_table", poly_idx__update_each_from_to, func__43_1_types__insert_order_table_update_each_from_to);
  define_method("types", "insert_order_table", poly_idx__update_each_from_down_to, func__44_1_types__insert_order_table_update_each_from_down_to);
  define_method("types", "insert_order_table", poly_idx__insert_before, func__45_1_types__insert_order_table_insert_before);
  define_method("types", "insert_order_table", poly_idx__insert_behind, func__46_1_types__insert_order_table_insert_behind);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__insert_order_table(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_an_insert_order_table, create_function(type__std__is_an_insert_order_table, -1));
  assign_value(&var._tree_of, create_function(type__tree_of, -1));
  assign_value(&var._first_of, create_function(type__first_of, -1));
  assign_value(&var._last_of, create_function(type__last_of, -1));
  assign_value(&var._key_of, create_function(type__key_of, -1));
  assign_value(&var._value_of, create_function(type__value_of, -1));
  assign_value(&var._left_of, create_function(type__left_of, -1));
  assign_value(&var._right_of, create_function(type__right_of, -1));
  assign_value(&var._next_of, create_function(type__next_of, -1));
  assign_value(&var._previous_of, create_function(type__previous_of, -1));
  assign_variable(&var._remove_leftmost, &func__16_1_remove_leftmost);
  assign_variable(&var._remove_rightmost, &func__17_1_remove_rightmost);
  assign_value(&var.types__insert_order_table, get__types__generic_table());
  assign_value(&var._empty_node, get__types__object());
  assign_variable(&var._fetch_first, &func__24_1_fetch_first);
  assign_variable(&var._retrieve_item, &func__25_1_retrieve_item);
  assign_variable(&var._add_item, &func__26_1_add_item);
  assign_variable(&var._update_item, &func__27_1_update_item);
  assign_variable(&var._remove_item, &func__28_1_remove_item);
  assign_variable(&var.std__empty_insert_order_table, &var.types__insert_order_table);
  assign_variable(&var.std__insert_order_table, &func__38_1_std__insert_order_table);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__insert_order_table(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__insert_order_table);
}
