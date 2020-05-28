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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
IMPORT NODE *get_attribute(NODE *node, int idx);
REGISTER FRAME *arguments ASM("r12");
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
IMPORT void set_module(const char *name);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
static NODE *func__remove_leftmost_1;
static void entry__remove_leftmost_1(void);
static FRAME_INFO frame__remove_leftmost_1 = {4, {"node", "key", "value", "left"}};
static void cont__remove_leftmost_2(void);
static void cont__remove_leftmost_3(void);
static NODE *func__remove_leftmost_4;
static void entry__remove_leftmost_4(void);
static FRAME_INFO frame__remove_leftmost_4 = {4, {"left", "key", "value", "node"}};
static void cont__remove_leftmost_5(void);
static NODE *func__remove_leftmost_6;
static void entry__remove_leftmost_6(void);
static FRAME_INFO frame__remove_leftmost_6 = {3, {"key", "node", "value"}};
static void cont__remove_leftmost_7(void);
static void cont__remove_leftmost_8(void);
static void cont__remove_leftmost_9(void);
static void cont__remove_leftmost_10(void);
static NODE *func__remove_rightmost_1;
static void entry__remove_rightmost_1(void);
static FRAME_INFO frame__remove_rightmost_1 = {4, {"node", "key", "value", "right"}};
static void cont__remove_rightmost_2(void);
static void cont__remove_rightmost_3(void);
static NODE *func__remove_rightmost_4;
static void entry__remove_rightmost_4(void);
static FRAME_INFO frame__remove_rightmost_4 = {4, {"right", "key", "value", "node"}};
static void cont__remove_rightmost_5(void);
static NODE *func__remove_rightmost_6;
static void entry__remove_rightmost_6(void);
static FRAME_INFO frame__remove_rightmost_6 = {3, {"key", "node", "value"}};
static void cont__remove_rightmost_7(void);
static void cont__remove_rightmost_8(void);
static void cont__remove_rightmost_9(void);
static void cont__remove_rightmost_10(void);
static NODE *get__types__insert_order_table(void) {
  return var.types__insert_order_table;
}
static NODE *func__fetch_first_1;
static void entry__fetch_first_1(void);
static FRAME_INFO frame__fetch_first_1 = {2, {"myself", "left"}};
static void cont__fetch_first_2(void);
static void cont__fetch_first_3(void);
static NODE *func__fetch_first_4;
static void entry__fetch_first_4(void);
static FRAME_INFO frame__fetch_first_4 = {3, {"left", "myself", "head"}};
static void cont__fetch_first_5(void);
static NODE *func__fetch_first_6;
static void entry__fetch_first_6(void);
static FRAME_INFO frame__fetch_first_6 = {2, {"myself", "head"}};
static void cont__fetch_first_7(void);
static void cont__fetch_first_8(void);
static NODE *func__retrieve_item_1;
static void entry__retrieve_item_1(void);
static FRAME_INFO frame__retrieve_item_1 = {4, {"myself", "key", "return", "my_key"}};
static void cont__retrieve_item_2(void);
static NODE *func__retrieve_item_3;
static void entry__retrieve_item_3(void);
static FRAME_INFO frame__retrieve_item_3 = {1, {"return"}};
static void cont__retrieve_item_4(void);
static void cont__retrieve_item_5(void);
static NODE *func__retrieve_item_6;
static void entry__retrieve_item_6(void);
static FRAME_INFO frame__retrieve_item_6 = {4, {"key", "my_key", "return", "myself"}};
static void cont__retrieve_item_7(void);
static NODE *func__retrieve_item_8;
static void entry__retrieve_item_8(void);
static FRAME_INFO frame__retrieve_item_8 = {2, {"return", "myself"}};
static NODE *func__retrieve_item_9;
static void entry__retrieve_item_9(void);
static FRAME_INFO frame__retrieve_item_9 = {4, {"key", "my_key", "return", "myself"}};
static void cont__retrieve_item_10(void);
static NODE *func__retrieve_item_11;
static void entry__retrieve_item_11(void);
static FRAME_INFO frame__retrieve_item_11 = {3, {"return", "myself", "key"}};
static void cont__retrieve_item_12(void);
static void cont__retrieve_item_13(void);
static NODE *func__retrieve_item_14;
static void entry__retrieve_item_14(void);
static FRAME_INFO frame__retrieve_item_14 = {4, {"my_key", "key", "return", "myself"}};
static void cont__retrieve_item_15(void);
static NODE *func__retrieve_item_16;
static void entry__retrieve_item_16(void);
static FRAME_INFO frame__retrieve_item_16 = {3, {"return", "myself", "key"}};
static void cont__retrieve_item_17(void);
static void cont__retrieve_item_18(void);
static void cont__retrieve_item_19(void);
static NODE *func__add_item_1;
static void entry__add_item_1(void);
static FRAME_INFO frame__add_item_1 = {7, {"myself", "previous", "next", "key", "value", "return", "my_key"}};
static void cont__add_item_2(void);
static NODE *func__add_item_3;
static void entry__add_item_3(void);
static FRAME_INFO frame__add_item_3 = {5, {"return", "previous", "next", "key", "value"}};
static void cont__add_item_4(void);
static void cont__add_item_5(void);
static NODE *func__add_item_6;
static void entry__add_item_6(void);
static FRAME_INFO frame__add_item_6 = {5, {"key", "my_key", "return", "myself", "value"}};
static void cont__add_item_7(void);
static NODE *func__add_item_8;
static void entry__add_item_8(void);
static FRAME_INFO frame__add_item_8 = {3, {"return", "myself", "value"}};
static NODE *func__add_item_9;
static void entry__add_item_9(void);
static FRAME_INFO frame__add_item_9 = {7, {"key", "my_key", "myself", "previous", "next", "value", "return"}};
static void cont__add_item_10(void);
static NODE *func__add_item_11;
static void entry__add_item_11(void);
static FRAME_INFO frame__add_item_11 = {8, {"myself", "previous", "next", "key", "value", "return", "left", "mode"}};
static void cont__add_item_12(void);
static void cont__add_item_13(void);
static NODE *func__add_item_14;
static void entry__add_item_14(void);
static FRAME_INFO frame__add_item_14 = {7, {"my_key", "key", "myself", "previous", "next", "value", "return"}};
static void cont__add_item_15(void);
static NODE *func__add_item_16;
static void entry__add_item_16(void);
static FRAME_INFO frame__add_item_16 = {8, {"myself", "previous", "next", "key", "value", "return", "right", "mode"}};
static void cont__add_item_17(void);
static void cont__add_item_18(void);
static void cont__add_item_19(void);
static NODE *func__update_item_1;
static void entry__update_item_1(void);
static FRAME_INFO frame__update_item_1 = {4, {"myself", "key", "updater", "my_key"}};
static void cont__update_item_2(void);
static NODE *func__update_item_3;
static void entry__update_item_3(void);
static FRAME_INFO frame__update_item_3 = {4, {"key", "my_key", "updater", "myself"}};
static void cont__update_item_4(void);
static NODE *func__update_item_5;
static void entry__update_item_5(void);
static FRAME_INFO frame__update_item_5 = {2, {"updater", "myself"}};
static void cont__update_item_6(void);
static NODE *func__update_item_7;
static void entry__update_item_7(void);
static FRAME_INFO frame__update_item_7 = {4, {"key", "my_key", "myself", "updater"}};
static void cont__update_item_8(void);
static NODE *func__update_item_9;
static void entry__update_item_9(void);
static FRAME_INFO frame__update_item_9 = {3, {"myself", "key", "updater"}};
static void cont__update_item_10(void);
static void cont__update_item_11(void);
static NODE *func__update_item_12;
static void entry__update_item_12(void);
static FRAME_INFO frame__update_item_12 = {4, {"my_key", "key", "myself", "updater"}};
static void cont__update_item_13(void);
static NODE *func__update_item_14;
static void entry__update_item_14(void);
static FRAME_INFO frame__update_item_14 = {3, {"myself", "key", "updater"}};
static void cont__update_item_15(void);
static void cont__update_item_16(void);
static void cont__update_item_17(void);
static NODE *func__remove_item_1;
static void entry__remove_item_1(void);
static FRAME_INFO frame__remove_item_1 = {4, {"myself", "key", "return", "my_key"}};
static void cont__remove_item_2(void);
static NODE *func__remove_item_3;
static void entry__remove_item_3(void);
static FRAME_INFO frame__remove_item_3 = {1, {"return"}};
static void cont__remove_item_4(void);
static void cont__remove_item_5(void);
static NODE *func__remove_item_6;
static void entry__remove_item_6(void);
static FRAME_INFO frame__remove_item_6 = {4, {"key", "my_key", "myself", "return"}};
static void cont__remove_item_7(void);
static NODE *func__remove_item_8;
static void entry__remove_item_8(void);
static FRAME_INFO frame__remove_item_8 = {4, {"myself", "return", "left", "right"}};
static void cont__remove_item_9(void);
static void cont__remove_item_10(void);
static void cont__remove_item_11(void);
static NODE *func__remove_item_12;
static void entry__remove_item_12(void);
static FRAME_INFO frame__remove_item_12 = {4, {"right", "return", "left", "myself"}};
static void cont__remove_item_13(void);
static NODE *func__remove_item_14;
static void entry__remove_item_14(void);
static FRAME_INFO frame__remove_item_14 = {5, {"right", "return", "left", "myself", "head"}};
static void cont__remove_item_15(void);
static NODE *func__remove_item_16;
static void entry__remove_item_16(void);
static FRAME_INFO frame__remove_item_16 = {3, {"return", "left", "myself"}};
static NODE *func__remove_item_17;
static void entry__remove_item_17(void);
static FRAME_INFO frame__remove_item_17 = {3, {"return", "right", "myself"}};
static NODE *func__remove_item_18;
static void entry__remove_item_18(void);
static FRAME_INFO frame__remove_item_18 = {4, {"key", "my_key", "myself", "return"}};
static void cont__remove_item_19(void);
static NODE *func__remove_item_20;
static void entry__remove_item_20(void);
static FRAME_INFO frame__remove_item_20 = {5, {"myself", "key", "return", "left", "removed_item"}};
static void cont__remove_item_21(void);
static void cont__remove_item_22(void);
static void cont__remove_item_23(void);
static NODE *func__remove_item_24;
static void entry__remove_item_24(void);
static FRAME_INFO frame__remove_item_24 = {1, {"return"}};
static void cont__remove_item_25(void);
static NODE *func__remove_item_26;
static void entry__remove_item_26(void);
static FRAME_INFO frame__remove_item_26 = {4, {"my_key", "key", "myself", "return"}};
static void cont__remove_item_27(void);
static NODE *func__remove_item_28;
static void entry__remove_item_28(void);
static FRAME_INFO frame__remove_item_28 = {5, {"myself", "key", "return", "right", "removed_item"}};
static void cont__remove_item_29(void);
static void cont__remove_item_30(void);
static void cont__remove_item_31(void);
static NODE *func__remove_item_32;
static void entry__remove_item_32(void);
static FRAME_INFO frame__remove_item_32 = {1, {"return"}};
static void cont__remove_item_33(void);
static void cont__remove_item_34(void);
static NODE *func__types__insert_order_table__private__set_item_1;
static void entry__types__insert_order_table__private__set_item_1(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_1 = {3, {"self", "key", "value"}};
static void cont__types__insert_order_table__private__set_item_2(void);
static NODE *func__types__insert_order_table__private__set_item_3;
static void entry__types__insert_order_table__private__set_item_3(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_3 = {4, {"self", "key", "new_tree", "removed_item"}};
static void cont__types__insert_order_table__private__set_item_4(void);
static void cont__types__insert_order_table__private__set_item_5(void);
static void cont__types__insert_order_table__private__set_item_6(void);
static void cont__types__insert_order_table__private__set_item_7(void);
static NODE *func__types__insert_order_table__private__set_item_8;
static void entry__types__insert_order_table__private__set_item_8(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_8 = {5, {"removed_item", "new_tree", "self", "previous", "next"}};
static void cont__types__insert_order_table__private__set_item_9(void);
static void cont__types__insert_order_table__private__set_item_10(void);
static void cont__types__insert_order_table__private__set_item_11(void);
static NODE *func__types__insert_order_table__private__set_item_12;
static void entry__types__insert_order_table__private__set_item_12(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_12 = {3, {"new_tree", "previous", "next"}};
static NODE *func__types__insert_order_table__private__set_item_13;
static void entry__types__insert_order_table__private__set_item_13(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_13 = {2, {"item", "next"}};
static void cont__types__insert_order_table__private__set_item_14(void);
static NODE *func__types__insert_order_table__private__set_item_15;
static void entry__types__insert_order_table__private__set_item_15(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_15 = {2, {"self", "next"}};
static void cont__types__insert_order_table__private__set_item_16(void);
static void cont__types__insert_order_table__private__set_item_17(void);
static NODE *func__types__insert_order_table__private__set_item_18;
static void entry__types__insert_order_table__private__set_item_18(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_18 = {3, {"new_tree", "next", "previous"}};
static NODE *func__types__insert_order_table__private__set_item_19;
static void entry__types__insert_order_table__private__set_item_19(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_19 = {2, {"item", "previous"}};
static void cont__types__insert_order_table__private__set_item_20(void);
static NODE *func__types__insert_order_table__private__set_item_21;
static void entry__types__insert_order_table__private__set_item_21(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_21 = {2, {"self", "previous"}};
static void cont__types__insert_order_table__private__set_item_22(void);
static void cont__types__insert_order_table__private__set_item_23(void);
static void cont__types__insert_order_table__private__set_item_24(void);
static NODE *func__types__insert_order_table__private__set_item_25;
static void entry__types__insert_order_table__private__set_item_25(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_25 = {5, {"self", "key", "value", "new_tree", "mode"}};
static void cont__types__insert_order_table__private__set_item_26(void);
static void cont__types__insert_order_table__private__set_item_27(void);
static void cont__types__insert_order_table__private__set_item_28(void);
static void cont__types__insert_order_table__private__set_item_29(void);
static NODE *func__types__insert_order_table__private__set_item_30;
static void entry__types__insert_order_table__private__set_item_30(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_30 = {3, {"self", "new_tree", "key"}};
static void cont__types__insert_order_table__private__set_item_31(void);
static void cont__types__insert_order_table__private__set_item_32(void);
static NODE *func__types__insert_order_table__private__set_item_33;
static void entry__types__insert_order_table__private__set_item_33(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_33 = {3, {"new_tree", "self", "key"}};
static void cont__types__insert_order_table__private__set_item_34(void);
static NODE *func__types__insert_order_table__private__set_item_35;
static void entry__types__insert_order_table__private__set_item_35(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_35 = {2, {"item", "key"}};
static void cont__types__insert_order_table__private__set_item_36(void);
static NODE *func__types__insert_order_table__private__set_item_37;
static void entry__types__insert_order_table__private__set_item_37(void);
static FRAME_INFO frame__types__insert_order_table__private__set_item_37 = {2, {"self", "key"}};
static void cont__types__insert_order_table__private__set_item_38(void);
static void cont__types__insert_order_table__private__set_item_39(void);
static void cont__types__insert_order_table__private__set_item_40(void);
static void cont__types__insert_order_table__private__set_item_41(void);
static void cont__types__insert_order_table__private__set_item_42(void);
static NODE *func__types__insert_order_table__private__get_item_1;
static void entry__types__insert_order_table__private__get_item_1(void);
static FRAME_INFO frame__types__insert_order_table__private__get_item_1 = {3, {"self", "key", "item"}};
static void cont__types__insert_order_table__private__get_item_2(void);
static void cont__types__insert_order_table__private__get_item_3(void);
static void cont__types__insert_order_table__private__get_item_4(void);
static NODE *func__types__insert_order_table__private__get_item_5;
static void entry__types__insert_order_table__private__get_item_5(void);
static FRAME_INFO frame__types__insert_order_table__private__get_item_5 = {1, {"item"}};
static void cont__types__insert_order_table__private__get_item_6(void);
static NODE *func__types__insert_order_table__private__get_item_7;
static void entry__types__insert_order_table__private__get_item_7(void);
static FRAME_INFO frame__types__insert_order_table__private__get_item_7 = {0, {}};
static NODE *string__1160a298062c3c9e;
static NODE *func__types__insert_order_table__new_empty_collection_1;
static void entry__types__insert_order_table__new_empty_collection_1(void);
static FRAME_INFO frame__types__insert_order_table__new_empty_collection_1 = {1, {"self"}};
static NODE *get__std__empty_insert_order_table(void) {
  return var.std__empty_insert_order_table;
}
static NODE *func__std__insert_order_table_1;
static void entry__std__insert_order_table_1(void);
static FRAME_INFO frame__std__insert_order_table_1 = {2, {"initializers", "tab"}};
static NODE *func__std__insert_order_table_2;
static void entry__std__insert_order_table_2(void);
static FRAME_INFO frame__std__insert_order_table_2 = {2, {"initializer", "tab"}};
static void cont__std__insert_order_table_3(void);
static void cont__std__insert_order_table_4(void);
static void cont__std__insert_order_table_5(void);
static void cont__std__insert_order_table_6(void);
static NODE *get__std__insert_order_table(void) {
  return var.std__insert_order_table;
}
static NODE *func__types__insert_order_table__for_each_1;
static void entry__types__insert_order_table__for_each_1(void);
static FRAME_INFO frame__types__insert_order_table__for_each_1 = {3, {"self", "body", "tree"}};
static void cont__types__insert_order_table__for_each_2(void);
static void cont__types__insert_order_table__for_each_3(void);
static NODE *func__types__insert_order_table__for_each_4;
static void entry__types__insert_order_table__for_each_4(void);
static FRAME_INFO frame__types__insert_order_table__for_each_4 = {4, {"self", "tree", "body", "key"}};
static void cont__types__insert_order_table__for_each_5(void);
static NODE *func__types__insert_order_table__for_each_6;
static void entry__types__insert_order_table__for_each_6(void);
static FRAME_INFO frame__types__insert_order_table__for_each_6 = {3, {"key", "tree", "body"}};
static void cont__types__insert_order_table__for_each_7(void);
static NODE *func__types__insert_order_table__for_each_8;
static void entry__types__insert_order_table__for_each_8(void);
static FRAME_INFO frame__types__insert_order_table__for_each_8 = {4, {"tree", "key", "body", "item"}};
static void cont__types__insert_order_table__for_each_9(void);
static void cont__types__insert_order_table__for_each_10(void);
static void cont__types__insert_order_table__for_each_11(void);
static NODE *func__types__insert_order_table__for_each_12;
static void entry__types__insert_order_table__for_each_12(void);
static FRAME_INFO frame__types__insert_order_table__for_each_12 = {3, {"body", "key", "item"}};
static void cont__types__insert_order_table__for_each_13(void);
static NODE *func__types__insert_order_table__for_each_14;
static void entry__types__insert_order_table__for_each_14(void);
static FRAME_INFO frame__types__insert_order_table__for_each_14 = {2, {"body", "item"}};
static void cont__types__insert_order_table__for_each_15(void);
static void cont__types__insert_order_table__for_each_16(void);
static void cont__types__insert_order_table__for_each_17(void);
static NODE *func__types__insert_order_table__for_each_from_to_1;
static void entry__types__insert_order_table__for_each_from_to_1(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_to_1 = {6, {"self", "first", "last", "body", "return", "tree"}};
static void cont__types__insert_order_table__for_each_from_to_2(void);
static void cont__types__insert_order_table__for_each_from_to_3(void);
static NODE *func__types__insert_order_table__for_each_from_to_4;
static void entry__types__insert_order_table__for_each_from_to_4(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_to_4 = {7, {"first", "self", "tree", "body", "last", "return", "key"}};
static void cont__types__insert_order_table__for_each_from_to_5(void);
static NODE *func__types__insert_order_table__for_each_from_to_6;
static void entry__types__insert_order_table__for_each_from_to_6(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_to_6 = {1, {"first"}};
static NODE *func__types__insert_order_table__for_each_from_to_7;
static void entry__types__insert_order_table__for_each_from_to_7(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_to_7 = {1, {"self"}};
static void cont__types__insert_order_table__for_each_from_to_8(void);
static void cont__types__insert_order_table__for_each_from_to_9(void);
static NODE *func__types__insert_order_table__for_each_from_to_10;
static void entry__types__insert_order_table__for_each_from_to_10(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_to_10 = {5, {"key", "tree", "body", "last", "return"}};
static void cont__types__insert_order_table__for_each_from_to_11(void);
static NODE *func__types__insert_order_table__for_each_from_to_12;
static void entry__types__insert_order_table__for_each_from_to_12(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_to_12 = {6, {"tree", "key", "body", "last", "return", "item"}};
static void cont__types__insert_order_table__for_each_from_to_13(void);
static void cont__types__insert_order_table__for_each_from_to_14(void);
static void cont__types__insert_order_table__for_each_from_to_15(void);
static NODE *func__types__insert_order_table__for_each_from_to_16;
static void entry__types__insert_order_table__for_each_from_to_16(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_to_16 = {3, {"body", "key", "item"}};
static void cont__types__insert_order_table__for_each_from_to_17(void);
static NODE *func__types__insert_order_table__for_each_from_to_18;
static void entry__types__insert_order_table__for_each_from_to_18(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_to_18 = {2, {"body", "item"}};
static void cont__types__insert_order_table__for_each_from_to_19(void);
static void cont__types__insert_order_table__for_each_from_to_20(void);
static void cont__types__insert_order_table__for_each_from_to_21(void);
static void cont__types__insert_order_table__for_each_from_to_22(void);
static void cont__types__insert_order_table__for_each_from_to_23(void);
static void cont__types__insert_order_table__for_each_from_to_24(void);
static NODE *func__types__insert_order_table__for_each_from_down_to_1;
static void entry__types__insert_order_table__for_each_from_down_to_1(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_down_to_1 = {6, {"self", "last", "first", "body", "return", "tree"}};
static void cont__types__insert_order_table__for_each_from_down_to_2(void);
static void cont__types__insert_order_table__for_each_from_down_to_3(void);
static NODE *func__types__insert_order_table__for_each_from_down_to_4;
static void entry__types__insert_order_table__for_each_from_down_to_4(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_down_to_4 = {7, {"last", "self", "tree", "body", "first", "return", "key"}};
static void cont__types__insert_order_table__for_each_from_down_to_5(void);
static NODE *func__types__insert_order_table__for_each_from_down_to_6;
static void entry__types__insert_order_table__for_each_from_down_to_6(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_down_to_6 = {1, {"last"}};
static NODE *func__types__insert_order_table__for_each_from_down_to_7;
static void entry__types__insert_order_table__for_each_from_down_to_7(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_down_to_7 = {1, {"self"}};
static void cont__types__insert_order_table__for_each_from_down_to_8(void);
static void cont__types__insert_order_table__for_each_from_down_to_9(void);
static NODE *func__types__insert_order_table__for_each_from_down_to_10;
static void entry__types__insert_order_table__for_each_from_down_to_10(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_down_to_10 = {5, {"key", "tree", "body", "first", "return"}};
static void cont__types__insert_order_table__for_each_from_down_to_11(void);
static NODE *func__types__insert_order_table__for_each_from_down_to_12;
static void entry__types__insert_order_table__for_each_from_down_to_12(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_down_to_12 = {6, {"tree", "key", "body", "first", "return", "item"}};
static void cont__types__insert_order_table__for_each_from_down_to_13(void);
static void cont__types__insert_order_table__for_each_from_down_to_14(void);
static void cont__types__insert_order_table__for_each_from_down_to_15(void);
static NODE *func__types__insert_order_table__for_each_from_down_to_16;
static void entry__types__insert_order_table__for_each_from_down_to_16(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_down_to_16 = {3, {"body", "key", "item"}};
static void cont__types__insert_order_table__for_each_from_down_to_17(void);
static NODE *func__types__insert_order_table__for_each_from_down_to_18;
static void entry__types__insert_order_table__for_each_from_down_to_18(void);
static FRAME_INFO frame__types__insert_order_table__for_each_from_down_to_18 = {2, {"body", "item"}};
static void cont__types__insert_order_table__for_each_from_down_to_19(void);
static void cont__types__insert_order_table__for_each_from_down_to_20(void);
static void cont__types__insert_order_table__for_each_from_down_to_21(void);
static void cont__types__insert_order_table__for_each_from_down_to_22(void);
static void cont__types__insert_order_table__for_each_from_down_to_23(void);
static void cont__types__insert_order_table__for_each_from_down_to_24(void);
static NODE *func__types__insert_order_table__update_each_1;
static void entry__types__insert_order_table__update_each_1(void);
static FRAME_INFO frame__types__insert_order_table__update_each_1 = {3, {"self", "body", "tree"}};
static void cont__types__insert_order_table__update_each_2(void);
static void cont__types__insert_order_table__update_each_3(void);
static NODE *func__types__insert_order_table__update_each_4;
static void entry__types__insert_order_table__update_each_4(void);
static FRAME_INFO frame__types__insert_order_table__update_each_4 = {4, {"self", "tree", "body", "key"}};
static void cont__types__insert_order_table__update_each_5(void);
static NODE *func__types__insert_order_table__update_each_6;
static void entry__types__insert_order_table__update_each_6(void);
static FRAME_INFO frame__types__insert_order_table__update_each_6 = {3, {"key", "tree", "body"}};
static void cont__types__insert_order_table__update_each_7(void);
static NODE *func__types__insert_order_table__update_each_8;
static void entry__types__insert_order_table__update_each_8(void);
static FRAME_INFO frame__types__insert_order_table__update_each_8 = {3, {"tree", "key", "body"}};
static NODE *func__types__insert_order_table__update_each_9;
static void entry__types__insert_order_table__update_each_9(void);
static FRAME_INFO frame__types__insert_order_table__update_each_9 = {3, {"item", "body", "key"}};
static void cont__types__insert_order_table__update_each_10(void);
static void cont__types__insert_order_table__update_each_11(void);
static void cont__types__insert_order_table__update_each_12(void);
static void cont__types__insert_order_table__update_each_13(void);
static void cont__types__insert_order_table__update_each_14(void);
static void cont__types__insert_order_table__update_each_15(void);
static NODE *func__types__insert_order_table__update_each_from_to_1;
static void entry__types__insert_order_table__update_each_from_to_1(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_to_1 = {5, {"self", "first", "last", "body", "tree"}};
static void cont__types__insert_order_table__update_each_from_to_2(void);
static void cont__types__insert_order_table__update_each_from_to_3(void);
static NODE *func__types__insert_order_table__update_each_from_to_4;
static void entry__types__insert_order_table__update_each_from_to_4(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_to_4 = {6, {"first", "self", "tree", "body", "last", "key"}};
static void cont__types__insert_order_table__update_each_from_to_5(void);
static NODE *func__types__insert_order_table__update_each_from_to_6;
static void entry__types__insert_order_table__update_each_from_to_6(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_to_6 = {1, {"first"}};
static NODE *func__types__insert_order_table__update_each_from_to_7;
static void entry__types__insert_order_table__update_each_from_to_7(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_to_7 = {1, {"self"}};
static void cont__types__insert_order_table__update_each_from_to_8(void);
static void cont__types__insert_order_table__update_each_from_to_9(void);
static NODE *func__types__insert_order_table__update_each_from_to_10;
static void entry__types__insert_order_table__update_each_from_to_10(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_to_10 = {5, {"break", "key", "tree", "body", "last"}};
static NODE *func__types__insert_order_table__update_each_from_to_11;
static void entry__types__insert_order_table__update_each_from_to_11(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_to_11 = {5, {"key", "tree", "body", "last", "break"}};
static void cont__types__insert_order_table__update_each_from_to_12(void);
static NODE *func__types__insert_order_table__update_each_from_to_13;
static void entry__types__insert_order_table__update_each_from_to_13(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_to_13 = {5, {"tree", "key", "body", "last", "break"}};
static NODE *func__types__insert_order_table__update_each_from_to_14;
static void entry__types__insert_order_table__update_each_from_to_14(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_to_14 = {5, {"item", "body", "key", "last", "break"}};
static void cont__types__insert_order_table__update_each_from_to_15(void);
static void cont__types__insert_order_table__update_each_from_to_16(void);
static void cont__types__insert_order_table__update_each_from_to_17(void);
static void cont__types__insert_order_table__update_each_from_to_18(void);
static void cont__types__insert_order_table__update_each_from_to_19(void);
static void cont__types__insert_order_table__update_each_from_to_20(void);
static void cont__types__insert_order_table__update_each_from_to_21(void);
static void cont__types__insert_order_table__update_each_from_to_22(void);
static void cont__types__insert_order_table__update_each_from_to_23(void);
static NODE *func__types__insert_order_table__update_each_from_down_to_1;
static void entry__types__insert_order_table__update_each_from_down_to_1(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_down_to_1 = {5, {"self", "last", "first", "body", "tree"}};
static void cont__types__insert_order_table__update_each_from_down_to_2(void);
static void cont__types__insert_order_table__update_each_from_down_to_3(void);
static NODE *func__types__insert_order_table__update_each_from_down_to_4;
static void entry__types__insert_order_table__update_each_from_down_to_4(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_down_to_4 = {6, {"last", "self", "tree", "body", "first", "key"}};
static void cont__types__insert_order_table__update_each_from_down_to_5(void);
static NODE *func__types__insert_order_table__update_each_from_down_to_6;
static void entry__types__insert_order_table__update_each_from_down_to_6(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_down_to_6 = {1, {"last"}};
static NODE *func__types__insert_order_table__update_each_from_down_to_7;
static void entry__types__insert_order_table__update_each_from_down_to_7(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_down_to_7 = {1, {"self"}};
static void cont__types__insert_order_table__update_each_from_down_to_8(void);
static void cont__types__insert_order_table__update_each_from_down_to_9(void);
static NODE *func__types__insert_order_table__update_each_from_down_to_10;
static void entry__types__insert_order_table__update_each_from_down_to_10(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_down_to_10 = {5, {"break", "key", "tree", "body", "first"}};
static NODE *func__types__insert_order_table__update_each_from_down_to_11;
static void entry__types__insert_order_table__update_each_from_down_to_11(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_down_to_11 = {5, {"key", "tree", "body", "first", "break"}};
static void cont__types__insert_order_table__update_each_from_down_to_12(void);
static NODE *func__types__insert_order_table__update_each_from_down_to_13;
static void entry__types__insert_order_table__update_each_from_down_to_13(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_down_to_13 = {5, {"tree", "key", "body", "first", "break"}};
static NODE *func__types__insert_order_table__update_each_from_down_to_14;
static void entry__types__insert_order_table__update_each_from_down_to_14(void);
static FRAME_INFO frame__types__insert_order_table__update_each_from_down_to_14 = {5, {"item", "body", "key", "first", "break"}};
static void cont__types__insert_order_table__update_each_from_down_to_15(void);
static void cont__types__insert_order_table__update_each_from_down_to_16(void);
static void cont__types__insert_order_table__update_each_from_down_to_17(void);
static void cont__types__insert_order_table__update_each_from_down_to_18(void);
static void cont__types__insert_order_table__update_each_from_down_to_19(void);
static void cont__types__insert_order_table__update_each_from_down_to_20(void);
static void cont__types__insert_order_table__update_each_from_down_to_21(void);
static void cont__types__insert_order_table__update_each_from_down_to_22(void);
static void cont__types__insert_order_table__update_each_from_down_to_23(void);
static NODE *func__types__insert_order_table__insert_before_1;
static void entry__types__insert_order_table__insert_before_1(void);
static FRAME_INFO frame__types__insert_order_table__insert_before_1 = {7, {"self", "key", "new_key", "new_value", "tree", "before_key", "mode"}};
static void cont__types__insert_order_table__insert_before_2(void);
static NODE *func__types__insert_order_table__insert_before_3;
static void entry__types__insert_order_table__insert_before_3(void);
static FRAME_INFO frame__types__insert_order_table__insert_before_3 = {3, {"item", "before_key", "new_key"}};
static void cont__types__insert_order_table__insert_before_4(void);
static void cont__types__insert_order_table__insert_before_5(void);
static void cont__types__insert_order_table__insert_before_6(void);
static NODE *func__types__insert_order_table__insert_before_7;
static void entry__types__insert_order_table__insert_before_7(void);
static FRAME_INFO frame__types__insert_order_table__insert_before_7 = {3, {"tree", "before_key", "new_key"}};
static NODE *func__types__insert_order_table__insert_before_8;
static void entry__types__insert_order_table__insert_before_8(void);
static FRAME_INFO frame__types__insert_order_table__insert_before_8 = {2, {"item", "new_key"}};
static void cont__types__insert_order_table__insert_before_9(void);
static NODE *func__types__insert_order_table__insert_before_10;
static void entry__types__insert_order_table__insert_before_10(void);
static FRAME_INFO frame__types__insert_order_table__insert_before_10 = {2, {"self", "new_key"}};
static void cont__types__insert_order_table__insert_before_11(void);
static void cont__types__insert_order_table__insert_before_12(void);
static void cont__types__insert_order_table__insert_before_13(void);
static void cont__types__insert_order_table__insert_before_14(void);
static NODE *func__types__insert_order_table__insert_before_15;
static void entry__types__insert_order_table__insert_before_15(void);
static FRAME_INFO frame__types__insert_order_table__insert_before_15 = {0, {}};
static NODE *string__d2f4ba5cf0563ffa;
static void cont__types__insert_order_table__insert_before_17(void);
static NODE *func__types__insert_order_table__insert_behind_1;
static void entry__types__insert_order_table__insert_behind_1(void);
static FRAME_INFO frame__types__insert_order_table__insert_behind_1 = {7, {"self", "key", "new_key", "new_value", "tree", "behind_key", "mode"}};
static void cont__types__insert_order_table__insert_behind_2(void);
static NODE *func__types__insert_order_table__insert_behind_3;
static void entry__types__insert_order_table__insert_behind_3(void);
static FRAME_INFO frame__types__insert_order_table__insert_behind_3 = {3, {"item", "behind_key", "new_key"}};
static void cont__types__insert_order_table__insert_behind_4(void);
static void cont__types__insert_order_table__insert_behind_5(void);
static void cont__types__insert_order_table__insert_behind_6(void);
static NODE *func__types__insert_order_table__insert_behind_7;
static void entry__types__insert_order_table__insert_behind_7(void);
static FRAME_INFO frame__types__insert_order_table__insert_behind_7 = {3, {"tree", "behind_key", "new_key"}};
static NODE *func__types__insert_order_table__insert_behind_8;
static void entry__types__insert_order_table__insert_behind_8(void);
static FRAME_INFO frame__types__insert_order_table__insert_behind_8 = {2, {"item", "new_key"}};
static void cont__types__insert_order_table__insert_behind_9(void);
static NODE *func__types__insert_order_table__insert_behind_10;
static void entry__types__insert_order_table__insert_behind_10(void);
static FRAME_INFO frame__types__insert_order_table__insert_behind_10 = {2, {"self", "new_key"}};
static void cont__types__insert_order_table__insert_behind_11(void);
static void cont__types__insert_order_table__insert_behind_12(void);
static void cont__types__insert_order_table__insert_behind_13(void);
static void cont__types__insert_order_table__insert_behind_14(void);
static NODE *func__types__insert_order_table__insert_behind_15;
static void entry__types__insert_order_table__insert_behind_15(void);
static FRAME_INFO frame__types__insert_order_table__insert_behind_15 = {0, {}};
static void cont__types__insert_order_table__insert_behind_16(void);
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
  {run__basic__types__insert_order_table, NULL, 466, 466, 1, 76},
  {cont__94_1, NULL, },
  {entry__remove_leftmost_4, NULL, 51, 51, 7, 39},
  {cont__remove_leftmost_5, &frame__remove_leftmost_4, 52, 52, 24, 24},
  {entry__remove_leftmost_6, NULL, 54, 54, 7, 23},
  {cont__remove_leftmost_7, &frame__remove_leftmost_6, 55, 55, 7, 27},
  {cont__remove_leftmost_8, &frame__remove_leftmost_6, 56, 56, 7, 26},
  {cont__remove_leftmost_9, &frame__remove_leftmost_6, 56, 56, 26, 26},
  {entry__remove_leftmost_1, NULL, 48, 48, 3, 22},
  {cont__remove_leftmost_2, &frame__remove_leftmost_1, 50, 50, 5, 19},
  {cont__remove_leftmost_3, &frame__remove_leftmost_1, 49, 56, 3, 27},
  {cont__remove_leftmost_10, &frame__remove_leftmost_1, },
  {entry__remove_rightmost_4, NULL, 67, 67, 7, 41},
  {cont__remove_rightmost_5, &frame__remove_rightmost_4, 68, 68, 26, 26},
  {entry__remove_rightmost_6, NULL, 70, 70, 7, 23},
  {cont__remove_rightmost_7, &frame__remove_rightmost_6, 71, 71, 7, 27},
  {cont__remove_rightmost_8, &frame__remove_rightmost_6, 72, 72, 7, 25},
  {cont__remove_rightmost_9, &frame__remove_rightmost_6, 72, 72, 25, 25},
  {entry__remove_rightmost_1, NULL, 64, 64, 3, 24},
  {cont__remove_rightmost_2, &frame__remove_rightmost_1, 66, 66, 5, 20},
  {cont__remove_rightmost_3, &frame__remove_rightmost_1, 65, 72, 3, 26},
  {cont__remove_rightmost_10, &frame__remove_rightmost_1, },
  {entry__fetch_first_4, NULL, 92, 92, 7, 29},
  {cont__fetch_first_5, &frame__fetch_first_4, 94, 94, 7, 13},
  {entry__fetch_first_6, NULL, 97, 97, 7, 30},
  {cont__fetch_first_7, &frame__fetch_first_6, 98, 98, 7, 13},
  {entry__fetch_first_1, NULL, 89, 89, 3, 24},
  {cont__fetch_first_2, &frame__fetch_first_1, 91, 91, 5, 19},
  {cont__fetch_first_3, &frame__fetch_first_1, 90, 98, 3, 14},
  {cont__fetch_first_8, &frame__fetch_first_1, },
  {entry__retrieve_item_3, NULL, 106, 106, 27, 42},
  {entry__retrieve_item_8, NULL, 109, 109, 23, 35},
  {entry__retrieve_item_6, NULL, 109, 109, 8, 20},
  {cont__retrieve_item_7, &frame__retrieve_item_6, 109, 109, 5, 35},
  {entry__retrieve_item_11, NULL, 110, 110, 43, 57},
  {cont__retrieve_item_12, &frame__retrieve_item_11, 110, 110, 29, 62},
  {cont__retrieve_item_13, &frame__retrieve_item_11, 110, 110, 22, 62},
  {entry__retrieve_item_9, NULL, 110, 110, 8, 19},
  {cont__retrieve_item_10, &frame__retrieve_item_9, 110, 110, 5, 62},
  {entry__retrieve_item_16, NULL, 111, 111, 43, 58},
  {cont__retrieve_item_17, &frame__retrieve_item_16, 111, 111, 29, 63},
  {cont__retrieve_item_18, &frame__retrieve_item_16, 111, 111, 22, 63},
  {entry__retrieve_item_14, NULL, 111, 111, 8, 19},
  {cont__retrieve_item_15, &frame__retrieve_item_14, 111, 111, 5, 63},
  {entry__retrieve_item_1, NULL, 106, 106, 6, 24},
  {cont__retrieve_item_2, &frame__retrieve_item_1, 106, 106, 3, 42},
  {cont__retrieve_item_4, &frame__retrieve_item_1, 107, 107, 3, 24},
  {cont__retrieve_item_5, &frame__retrieve_item_1, 108, 111, 3, 63},
  {cont__retrieve_item_19, &frame__retrieve_item_1, 111, 111, 63, 63},
  {entry__add_item_3, NULL, 123, 129, 5, 12},
  {entry__add_item_8, NULL, 132, 132, 23, 59},
  {entry__add_item_6, NULL, 132, 132, 8, 20},
  {cont__add_item_7, &frame__add_item_6, 132, 132, 5, 59},
  {entry__add_item_11, NULL, 134, 134, 28, 42},
  {cont__add_item_12, &frame__add_item_11, 134, 134, 7, 66},
  {cont__add_item_13, &frame__add_item_11, 135, 135, 7, 39},
  {entry__add_item_9, NULL, 133, 133, 8, 19},
  {cont__add_item_10, &frame__add_item_9, 133, 135, 5, 39},
  {entry__add_item_16, NULL, 137, 137, 29, 44},
  {cont__add_item_17, &frame__add_item_16, 137, 137, 7, 68},
  {cont__add_item_18, &frame__add_item_16, 138, 138, 7, 41},
  {entry__add_item_14, NULL, 136, 136, 8, 19},
  {cont__add_item_15, &frame__add_item_14, 136, 138, 5, 41},
  {entry__add_item_1, NULL, 122, 122, 6, 24},
  {cont__add_item_2, &frame__add_item_1, 122, 129, 3, 13},
  {cont__add_item_4, &frame__add_item_1, 130, 130, 3, 24},
  {cont__add_item_5, &frame__add_item_1, 131, 138, 3, 42},
  {cont__add_item_19, &frame__add_item_1, 138, 138, 42, 42},
  {entry__update_item_5, NULL, 148, 148, 23, 37},
  {cont__update_item_6, &frame__update_item_5, 148, 148, 37, 37},
  {entry__update_item_3, NULL, 148, 148, 8, 20},
  {cont__update_item_4, &frame__update_item_3, 148, 148, 5, 37},
  {entry__update_item_9, NULL, 149, 149, 35, 48},
  {cont__update_item_10, &frame__update_item_9, 149, 149, 22, 60},
  {cont__update_item_11, &frame__update_item_9, 149, 149, 60, 60},
  {entry__update_item_7, NULL, 149, 149, 8, 19},
  {cont__update_item_8, &frame__update_item_7, 149, 149, 5, 60},
  {entry__update_item_14, NULL, 150, 150, 35, 49},
  {cont__update_item_15, &frame__update_item_14, 150, 150, 22, 61},
  {cont__update_item_16, &frame__update_item_14, 150, 150, 61, 61},
  {entry__update_item_12, NULL, 150, 150, 8, 19},
  {cont__update_item_13, &frame__update_item_12, 150, 150, 5, 61},
  {entry__update_item_1, NULL, 146, 146, 3, 24},
  {cont__update_item_2, &frame__update_item_1, 147, 150, 3, 61},
  {cont__update_item_17, &frame__update_item_1, },
  {entry__remove_item_3, NULL, 162, 162, 27, 65},
  {entry__remove_item_14, NULL, 172, 172, 15, 38},
  {cont__remove_item_15, &frame__remove_item_14, 173, 173, 15, 63},
  {entry__remove_item_16, NULL, 175, 175, 15, 32},
  {entry__remove_item_12, NULL, 171, 171, 13, 28},
  {cont__remove_item_13, &frame__remove_item_12, 170, 175, 11, 33},
  {entry__remove_item_17, NULL, 177, 177, 11, 29},
  {entry__remove_item_8, NULL, 166, 166, 7, 27},
  {cont__remove_item_9, &frame__remove_item_8, 167, 167, 7, 30},
  {cont__remove_item_10, &frame__remove_item_8, 169, 169, 9, 23},
  {cont__remove_item_11, &frame__remove_item_8, 168, 177, 7, 30},
  {entry__remove_item_6, NULL, 165, 165, 8, 20},
  {cont__remove_item_7, &frame__remove_item_6, 165, 177, 5, 31},
  {entry__remove_item_24, NULL, 180, 180, 24, 62},
  {entry__remove_item_20, NULL, 179, 179, 39, 53},
  {cont__remove_item_21, &frame__remove_item_20, 179, 179, 7, 57},
  {cont__remove_item_22, &frame__remove_item_20, 180, 180, 10, 21},
  {cont__remove_item_23, &frame__remove_item_20, 180, 180, 7, 62},
  {cont__remove_item_25, &frame__remove_item_20, 182, 182, 7, 32},
  {entry__remove_item_18, NULL, 178, 178, 8, 19},
  {cont__remove_item_19, &frame__remove_item_18, 178, 182, 5, 32},
  {entry__remove_item_32, NULL, 185, 185, 25, 63},
  {entry__remove_item_28, NULL, 184, 184, 40, 55},
  {cont__remove_item_29, &frame__remove_item_28, 184, 184, 7, 59},
  {cont__remove_item_30, &frame__remove_item_28, 185, 185, 10, 22},
  {cont__remove_item_31, &frame__remove_item_28, 185, 185, 7, 63},
  {cont__remove_item_33, &frame__remove_item_28, 187, 187, 7, 32},
  {entry__remove_item_26, NULL, 183, 183, 8, 19},
  {cont__remove_item_27, &frame__remove_item_26, 183, 187, 5, 32},
  {entry__remove_item_1, NULL, 162, 162, 6, 24},
  {cont__remove_item_2, &frame__remove_item_1, 162, 162, 3, 65},
  {cont__remove_item_4, &frame__remove_item_1, 163, 163, 3, 24},
  {cont__remove_item_5, &frame__remove_item_1, 164, 187, 3, 33},
  {cont__remove_item_34, &frame__remove_item_1, 187, 187, 33, 33},
  {entry__types__insert_order_table__private__set_item_13, NULL, 205, 205, 70, 70},
  {entry__types__insert_order_table__private__set_item_12, NULL, 205, 205, 13, 70},
  {cont__types__insert_order_table__private__set_item_14, &frame__types__insert_order_table__private__set_item_12, 205, 205, 70, 70},
  {entry__types__insert_order_table__private__set_item_15, NULL, 207, 207, 31, 31},
  {entry__types__insert_order_table__private__set_item_19, NULL, 210, 210, 74, 74},
  {entry__types__insert_order_table__private__set_item_18, NULL, 210, 210, 13, 74},
  {cont__types__insert_order_table__private__set_item_20, &frame__types__insert_order_table__private__set_item_18, 210, 210, 74, 74},
  {entry__types__insert_order_table__private__set_item_21, NULL, 212, 212, 34, 34},
  {entry__types__insert_order_table__private__set_item_8, NULL, 201, 201, 9, 43},
  {cont__types__insert_order_table__private__set_item_9, &frame__types__insert_order_table__private__set_item_8, 202, 202, 9, 35},
  {cont__types__insert_order_table__private__set_item_10, &frame__types__insert_order_table__private__set_item_8, 204, 204, 11, 29},
  {cont__types__insert_order_table__private__set_item_11, &frame__types__insert_order_table__private__set_item_8, 203, 207, 9, 32},
  {cont__types__insert_order_table__private__set_item_16, &frame__types__insert_order_table__private__set_item_8, 209, 209, 11, 25},
  {cont__types__insert_order_table__private__set_item_17, &frame__types__insert_order_table__private__set_item_8, 208, 212, 9, 35},
  {cont__types__insert_order_table__private__set_item_22, &frame__types__insert_order_table__private__set_item_8, 214, 214, 14, 27},
  {cont__types__insert_order_table__private__set_item_23, &frame__types__insert_order_table__private__set_item_8, 214, 214, 9, 27},
  {cont__types__insert_order_table__private__set_item_24, &frame__types__insert_order_table__private__set_item_8, 214, 214, 27, 27},
  {entry__types__insert_order_table__private__set_item_3, NULL, 199, 199, 44, 56},
  {cont__types__insert_order_table__private__set_item_4, &frame__types__insert_order_table__private__set_item_3, 199, 199, 7, 60},
  {cont__types__insert_order_table__private__set_item_5, &frame__types__insert_order_table__private__set_item_3, 200, 200, 10, 25},
  {cont__types__insert_order_table__private__set_item_6, &frame__types__insert_order_table__private__set_item_3, 200, 200, 10, 25},
  {cont__types__insert_order_table__private__set_item_7, &frame__types__insert_order_table__private__set_item_3, 200, 214, 7, 27},
  {entry__types__insert_order_table__private__set_item_35, NULL, 220, 220, 74, 74},
  {entry__types__insert_order_table__private__set_item_33, NULL, 220, 220, 35, 47},
  {cont__types__insert_order_table__private__set_item_34, &frame__types__insert_order_table__private__set_item_33, 220, 220, 13, 74},
  {cont__types__insert_order_table__private__set_item_36, &frame__types__insert_order_table__private__set_item_33, 220, 220, 74, 74},
  {entry__types__insert_order_table__private__set_item_37, NULL, 222, 222, 30, 30},
  {entry__types__insert_order_table__private__set_item_30, NULL, 219, 219, 11, 23},
  {cont__types__insert_order_table__private__set_item_31, &frame__types__insert_order_table__private__set_item_30, 219, 219, 11, 34},
  {cont__types__insert_order_table__private__set_item_32, &frame__types__insert_order_table__private__set_item_30, 218, 222, 9, 31},
  {cont__types__insert_order_table__private__set_item_38, &frame__types__insert_order_table__private__set_item_30, 224, 224, 14, 27},
  {cont__types__insert_order_table__private__set_item_39, &frame__types__insert_order_table__private__set_item_30, 224, 224, 9, 27},
  {cont__types__insert_order_table__private__set_item_40, &frame__types__insert_order_table__private__set_item_30, 224, 224, 27, 27},
  {entry__types__insert_order_table__private__set_item_25, NULL, 216, 216, 33, 45},
  {cont__types__insert_order_table__private__set_item_26, &frame__types__insert_order_table__private__set_item_25, 216, 216, 47, 59},
  {cont__types__insert_order_table__private__set_item_27, &frame__types__insert_order_table__private__set_item_25, 216, 216, 7, 79},
  {cont__types__insert_order_table__private__set_item_28, &frame__types__insert_order_table__private__set_item_25, 217, 217, 10, 23},
  {cont__types__insert_order_table__private__set_item_29, &frame__types__insert_order_table__private__set_item_25, 217, 224, 7, 27},
  {cont__types__insert_order_table__private__set_item_41, &frame__types__insert_order_table__private__set_item_25, 225, 225, 28, 28},
  {entry__types__insert_order_table__private__set_item_1, NULL, 198, 198, 5, 22},
  {cont__types__insert_order_table__private__set_item_2, &frame__types__insert_order_table__private__set_item_1, 197, 225, 3, 29},
  {cont__types__insert_order_table__private__set_item_42, &frame__types__insert_order_table__private__set_item_1, },
  {entry__types__insert_order_table__private__get_item_5, NULL, 235, 235, 26, 39},
  {cont__types__insert_order_table__private__get_item_6, &frame__types__insert_order_table__private__get_item_5, 235, 235, 23, 39},
  {entry__types__insert_order_table__private__get_item_7, NULL, 235, 235, 42, 53},
  {entry__types__insert_order_table__private__get_item_1, NULL, 234, 234, 23, 35},
  {cont__types__insert_order_table__private__get_item_2, &frame__types__insert_order_table__private__get_item_1, 234, 234, 3, 40},
  {cont__types__insert_order_table__private__get_item_3, &frame__types__insert_order_table__private__get_item_1, 235, 235, 6, 20},
  {cont__types__insert_order_table__private__get_item_4, &frame__types__insert_order_table__private__get_item_1, 235, 235, 3, 53},
  {entry__types__insert_order_table__new_empty_collection_1, NULL, 255, 255, 3, 30},
  {entry__std__insert_order_table_2, NULL, 276, 276, 5, 61},
  {cont__std__insert_order_table_3, &frame__std__insert_order_table_2, 276, 276, 10, 33},
  {cont__std__insert_order_table_4, &frame__std__insert_order_table_2, 276, 276, 5, 34},
  {cont__std__insert_order_table_5, &frame__std__insert_order_table_2, 276, 276, 61, 61},
  {entry__std__insert_order_table_1, NULL, 275, 276, 3, 61},
  {cont__std__insert_order_table_6, &frame__std__insert_order_table_1, 277, 277, 3, 8},
  {entry__types__insert_order_table__for_each_12, NULL, 293, 293, 20, 33},
  {cont__types__insert_order_table__for_each_13, &frame__types__insert_order_table__for_each_12, 293, 293, 11, 33},
  {entry__types__insert_order_table__for_each_14, NULL, 295, 295, 16, 29},
  {cont__types__insert_order_table__for_each_15, &frame__types__insert_order_table__for_each_14, 295, 295, 11, 29},
  {entry__types__insert_order_table__for_each_8, NULL, 290, 290, 7, 35},
  {cont__types__insert_order_table__for_each_9, &frame__types__insert_order_table__for_each_8, 292, 292, 9, 32},
  {cont__types__insert_order_table__for_each_10, &frame__types__insert_order_table__for_each_8, 292, 292, 9, 37},
  {cont__types__insert_order_table__for_each_11, &frame__types__insert_order_table__for_each_8, 291, 295, 7, 30},
  {cont__types__insert_order_table__for_each_16, &frame__types__insert_order_table__for_each_8, 296, 296, 7, 24},
  {cont__types__insert_order_table__for_each_17, &frame__types__insert_order_table__for_each_8, 296, 296, 24, 24},
  {entry__types__insert_order_table__for_each_6, NULL, 289, 289, 14, 27},
  {cont__types__insert_order_table__for_each_7, &frame__types__insert_order_table__for_each_6, 289, 296, 11, 24},
  {entry__types__insert_order_table__for_each_4, NULL, 288, 288, 5, 24},
  {cont__types__insert_order_table__for_each_5, &frame__types__insert_order_table__for_each_4, 289, 296, 5, 24},
  {entry__types__insert_order_table__for_each_1, NULL, 286, 286, 3, 21},
  {cont__types__insert_order_table__for_each_2, &frame__types__insert_order_table__for_each_1, 287, 287, 6, 20},
  {cont__types__insert_order_table__for_each_3, &frame__types__insert_order_table__for_each_1, 287, 296, 3, 25},
  {entry__types__insert_order_table__for_each_from_to_6, NULL, 313, 313, 9, 16},
  {entry__types__insert_order_table__for_each_from_to_7, NULL, 314, 314, 12, 25},
  {cont__types__insert_order_table__for_each_from_to_8, &frame__types__insert_order_table__for_each_from_to_7, 314, 314, 9, 25},
  {entry__types__insert_order_table__for_each_from_to_16, NULL, 320, 320, 20, 33},
  {cont__types__insert_order_table__for_each_from_to_17, &frame__types__insert_order_table__for_each_from_to_16, 320, 320, 11, 33},
  {entry__types__insert_order_table__for_each_from_to_18, NULL, 322, 322, 16, 29},
  {cont__types__insert_order_table__for_each_from_to_19, &frame__types__insert_order_table__for_each_from_to_18, 322, 322, 11, 29},
  {entry__types__insert_order_table__for_each_from_to_12, NULL, 317, 317, 7, 35},
  {cont__types__insert_order_table__for_each_from_to_13, &frame__types__insert_order_table__for_each_from_to_12, 319, 319, 9, 32},
  {cont__types__insert_order_table__for_each_from_to_14, &frame__types__insert_order_table__for_each_from_to_12, 319, 319, 9, 37},
  {cont__types__insert_order_table__for_each_from_to_15, &frame__types__insert_order_table__for_each_from_to_12, 318, 322, 7, 30},
  {cont__types__insert_order_table__for_each_from_to_20, &frame__types__insert_order_table__for_each_from_to_12, 323, 323, 10, 20},
  {cont__types__insert_order_table__for_each_from_to_21, &frame__types__insert_order_table__for_each_from_to_12, 323, 323, 7, 27},
  {cont__types__insert_order_table__for_each_from_to_22, &frame__types__insert_order_table__for_each_from_to_12, 324, 324, 7, 24},
  {cont__types__insert_order_table__for_each_from_to_23, &frame__types__insert_order_table__for_each_from_to_12, 324, 324, 24, 24},
  {entry__types__insert_order_table__for_each_from_to_10, NULL, 316, 316, 14, 27},
  {cont__types__insert_order_table__for_each_from_to_11, &frame__types__insert_order_table__for_each_from_to_10, 316, 324, 11, 24},
  {entry__types__insert_order_table__for_each_from_to_4, NULL, 312, 312, 9, 24},
  {cont__types__insert_order_table__for_each_from_to_5, &frame__types__insert_order_table__for_each_from_to_4, 310, 314, 5, 26},
  {cont__types__insert_order_table__for_each_from_to_9, &frame__types__insert_order_table__for_each_from_to_4, 316, 324, 5, 24},
  {entry__types__insert_order_table__for_each_from_to_1, NULL, 308, 308, 3, 21},
  {cont__types__insert_order_table__for_each_from_to_2, &frame__types__insert_order_table__for_each_from_to_1, 309, 309, 6, 20},
  {cont__types__insert_order_table__for_each_from_to_3, &frame__types__insert_order_table__for_each_from_to_1, 309, 324, 3, 25},
  {cont__types__insert_order_table__for_each_from_to_24, &frame__types__insert_order_table__for_each_from_to_1, 324, 324, 25, 25},
  {entry__types__insert_order_table__for_each_from_down_to_6, NULL, 341, 341, 9, 15},
  {entry__types__insert_order_table__for_each_from_down_to_7, NULL, 342, 342, 12, 24},
  {cont__types__insert_order_table__for_each_from_down_to_8, &frame__types__insert_order_table__for_each_from_down_to_7, 342, 342, 9, 24},
  {entry__types__insert_order_table__for_each_from_down_to_16, NULL, 348, 348, 20, 33},
  {cont__types__insert_order_table__for_each_from_down_to_17, &frame__types__insert_order_table__for_each_from_down_to_16, 348, 348, 11, 33},
  {entry__types__insert_order_table__for_each_from_down_to_18, NULL, 350, 350, 16, 29},
  {cont__types__insert_order_table__for_each_from_down_to_19, &frame__types__insert_order_table__for_each_from_down_to_18, 350, 350, 11, 29},
  {entry__types__insert_order_table__for_each_from_down_to_12, NULL, 345, 345, 7, 35},
  {cont__types__insert_order_table__for_each_from_down_to_13, &frame__types__insert_order_table__for_each_from_down_to_12, 347, 347, 9, 32},
  {cont__types__insert_order_table__for_each_from_down_to_14, &frame__types__insert_order_table__for_each_from_down_to_12, 347, 347, 9, 37},
  {cont__types__insert_order_table__for_each_from_down_to_15, &frame__types__insert_order_table__for_each_from_down_to_12, 346, 350, 7, 30},
  {cont__types__insert_order_table__for_each_from_down_to_20, &frame__types__insert_order_table__for_each_from_down_to_12, 351, 351, 10, 21},
  {cont__types__insert_order_table__for_each_from_down_to_21, &frame__types__insert_order_table__for_each_from_down_to_12, 351, 351, 7, 28},
  {cont__types__insert_order_table__for_each_from_down_to_22, &frame__types__insert_order_table__for_each_from_down_to_12, 352, 352, 7, 28},
  {cont__types__insert_order_table__for_each_from_down_to_23, &frame__types__insert_order_table__for_each_from_down_to_12, 352, 352, 28, 28},
  {entry__types__insert_order_table__for_each_from_down_to_10, NULL, 344, 344, 14, 27},
  {cont__types__insert_order_table__for_each_from_down_to_11, &frame__types__insert_order_table__for_each_from_down_to_10, 344, 352, 11, 28},
  {entry__types__insert_order_table__for_each_from_down_to_4, NULL, 340, 340, 9, 23},
  {cont__types__insert_order_table__for_each_from_down_to_5, &frame__types__insert_order_table__for_each_from_down_to_4, 338, 342, 5, 25},
  {cont__types__insert_order_table__for_each_from_down_to_9, &frame__types__insert_order_table__for_each_from_down_to_4, 344, 352, 5, 28},
  {entry__types__insert_order_table__for_each_from_down_to_1, NULL, 336, 336, 3, 21},
  {cont__types__insert_order_table__for_each_from_down_to_2, &frame__types__insert_order_table__for_each_from_down_to_1, 337, 337, 6, 20},
  {cont__types__insert_order_table__for_each_from_down_to_3, &frame__types__insert_order_table__for_each_from_down_to_1, 337, 352, 3, 29},
  {cont__types__insert_order_table__for_each_from_down_to_24, &frame__types__insert_order_table__for_each_from_down_to_1, 352, 352, 29, 29},
  {entry__types__insert_order_table__update_each_9, NULL, 366, 366, 19, 31},
  {cont__types__insert_order_table__update_each_10, &frame__types__insert_order_table__update_each_9, 366, 366, 9, 31},
  {cont__types__insert_order_table__update_each_11, &frame__types__insert_order_table__update_each_9, 367, 367, 9, 26},
  {cont__types__insert_order_table__update_each_12, &frame__types__insert_order_table__update_each_9, 367, 367, 26, 26},
  {entry__types__insert_order_table__update_each_8, NULL, 365, 367, 7, 26},
  {cont__types__insert_order_table__update_each_13, &frame__types__insert_order_table__update_each_8, 367, 367, 27, 27},
  {entry__types__insert_order_table__update_each_6, NULL, 364, 364, 14, 27},
  {cont__types__insert_order_table__update_each_7, &frame__types__insert_order_table__update_each_6, 364, 367, 11, 27},
  {entry__types__insert_order_table__update_each_4, NULL, 363, 363, 5, 24},
  {cont__types__insert_order_table__update_each_5, &frame__types__insert_order_table__update_each_4, 364, 367, 5, 27},
  {cont__types__insert_order_table__update_each_14, &frame__types__insert_order_table__update_each_4, 368, 368, 22, 22},
  {entry__types__insert_order_table__update_each_1, NULL, 361, 361, 3, 22},
  {cont__types__insert_order_table__update_each_2, &frame__types__insert_order_table__update_each_1, 362, 362, 6, 20},
  {cont__types__insert_order_table__update_each_3, &frame__types__insert_order_table__update_each_1, 362, 368, 3, 22},
  {cont__types__insert_order_table__update_each_15, &frame__types__insert_order_table__update_each_1, },
  {entry__types__insert_order_table__update_each_from_to_6, NULL, 384, 384, 9, 16},
  {entry__types__insert_order_table__update_each_from_to_7, NULL, 385, 385, 12, 25},
  {cont__types__insert_order_table__update_each_from_to_8, &frame__types__insert_order_table__update_each_from_to_7, 385, 385, 9, 25},
  {entry__types__insert_order_table__update_each_from_to_14, NULL, 390, 390, 21, 33},
  {cont__types__insert_order_table__update_each_from_to_15, &frame__types__insert_order_table__update_each_from_to_14, 390, 390, 11, 33},
  {cont__types__insert_order_table__update_each_from_to_16, &frame__types__insert_order_table__update_each_from_to_14, 391, 391, 14, 24},
  {cont__types__insert_order_table__update_each_from_to_17, &frame__types__insert_order_table__update_each_from_to_14, 391, 391, 11, 30},
  {cont__types__insert_order_table__update_each_from_to_18, &frame__types__insert_order_table__update_each_from_to_14, 392, 392, 11, 28},
  {cont__types__insert_order_table__update_each_from_to_19, &frame__types__insert_order_table__update_each_from_to_14, 392, 392, 28, 28},
  {entry__types__insert_order_table__update_each_from_to_13, NULL, 389, 392, 9, 28},
  {cont__types__insert_order_table__update_each_from_to_20, &frame__types__insert_order_table__update_each_from_to_13, 392, 392, 29, 29},
  {entry__types__insert_order_table__update_each_from_to_11, NULL, 388, 388, 16, 29},
  {cont__types__insert_order_table__update_each_from_to_12, &frame__types__insert_order_table__update_each_from_to_11, 388, 392, 13, 29},
  {entry__types__insert_order_table__update_each_from_to_10, NULL, 388, 392, 7, 29},
  {cont__types__insert_order_table__update_each_from_to_21, &frame__types__insert_order_table__update_each_from_to_10, 392, 392, 29, 29},
  {entry__types__insert_order_table__update_each_from_to_4, NULL, 383, 383, 9, 24},
  {cont__types__insert_order_table__update_each_from_to_5, &frame__types__insert_order_table__update_each_from_to_4, 381, 385, 5, 26},
  {cont__types__insert_order_table__update_each_from_to_9, &frame__types__insert_order_table__update_each_from_to_4, 387, 392, 5, 30},
  {cont__types__insert_order_table__update_each_from_to_22, &frame__types__insert_order_table__update_each_from_to_4, 393, 393, 22, 22},
  {entry__types__insert_order_table__update_each_from_to_1, NULL, 379, 379, 3, 22},
  {cont__types__insert_order_table__update_each_from_to_2, &frame__types__insert_order_table__update_each_from_to_1, 380, 380, 6, 20},
  {cont__types__insert_order_table__update_each_from_to_3, &frame__types__insert_order_table__update_each_from_to_1, 380, 393, 3, 22},
  {cont__types__insert_order_table__update_each_from_to_23, &frame__types__insert_order_table__update_each_from_to_1, },
  {entry__types__insert_order_table__update_each_from_down_to_6, NULL, 409, 409, 9, 15},
  {entry__types__insert_order_table__update_each_from_down_to_7, NULL, 410, 410, 12, 24},
  {cont__types__insert_order_table__update_each_from_down_to_8, &frame__types__insert_order_table__update_each_from_down_to_7, 410, 410, 9, 24},
  {entry__types__insert_order_table__update_each_from_down_to_14, NULL, 415, 415, 21, 33},
  {cont__types__insert_order_table__update_each_from_down_to_15, &frame__types__insert_order_table__update_each_from_down_to_14, 415, 415, 11, 33},
  {cont__types__insert_order_table__update_each_from_down_to_16, &frame__types__insert_order_table__update_each_from_down_to_14, 416, 416, 14, 25},
  {cont__types__insert_order_table__update_each_from_down_to_17, &frame__types__insert_order_table__update_each_from_down_to_14, 416, 416, 11, 31},
  {cont__types__insert_order_table__update_each_from_down_to_18, &frame__types__insert_order_table__update_each_from_down_to_14, 417, 417, 11, 32},
  {cont__types__insert_order_table__update_each_from_down_to_19, &frame__types__insert_order_table__update_each_from_down_to_14, 417, 417, 32, 32},
  {entry__types__insert_order_table__update_each_from_down_to_13, NULL, 414, 417, 9, 32},
  {cont__types__insert_order_table__update_each_from_down_to_20, &frame__types__insert_order_table__update_each_from_down_to_13, 417, 417, 33, 33},
  {entry__types__insert_order_table__update_each_from_down_to_11, NULL, 413, 413, 16, 29},
  {cont__types__insert_order_table__update_each_from_down_to_12, &frame__types__insert_order_table__update_each_from_down_to_11, 413, 417, 13, 33},
  {entry__types__insert_order_table__update_each_from_down_to_10, NULL, 413, 417, 7, 33},
  {cont__types__insert_order_table__update_each_from_down_to_21, &frame__types__insert_order_table__update_each_from_down_to_10, 417, 417, 33, 33},
  {entry__types__insert_order_table__update_each_from_down_to_4, NULL, 408, 408, 9, 23},
  {cont__types__insert_order_table__update_each_from_down_to_5, &frame__types__insert_order_table__update_each_from_down_to_4, 406, 410, 5, 25},
  {cont__types__insert_order_table__update_each_from_down_to_9, &frame__types__insert_order_table__update_each_from_down_to_4, 412, 417, 5, 34},
  {cont__types__insert_order_table__update_each_from_down_to_22, &frame__types__insert_order_table__update_each_from_down_to_4, 418, 418, 22, 22},
  {entry__types__insert_order_table__update_each_from_down_to_1, NULL, 404, 404, 3, 22},
  {cont__types__insert_order_table__update_each_from_down_to_2, &frame__types__insert_order_table__update_each_from_down_to_1, 405, 405, 6, 20},
  {cont__types__insert_order_table__update_each_from_down_to_3, &frame__types__insert_order_table__update_each_from_down_to_1, 405, 418, 3, 22},
  {cont__types__insert_order_table__update_each_from_down_to_23, &frame__types__insert_order_table__update_each_from_down_to_1, },
  {entry__types__insert_order_table__insert_before_3, NULL, 432, 432, 5, 33},
  {cont__types__insert_order_table__insert_before_4, &frame__types__insert_order_table__insert_before_3, 433, 433, 29, 29},
  {entry__types__insert_order_table__insert_before_8, NULL, 436, 436, 65, 65},
  {entry__types__insert_order_table__insert_before_7, NULL, 436, 436, 7, 65},
  {cont__types__insert_order_table__insert_before_9, &frame__types__insert_order_table__insert_before_7, 436, 436, 65, 65},
  {entry__types__insert_order_table__insert_before_10, NULL, 438, 438, 28, 28},
  {entry__types__insert_order_table__insert_before_15, NULL, 441, 441, 22, 59},
  {entry__types__insert_order_table__insert_before_1, NULL, 429, 429, 3, 22},
  {cont__types__insert_order_table__insert_before_2, &frame__types__insert_order_table__insert_before_1, 431, 433, 3, 29},
  {cont__types__insert_order_table__insert_before_5, &frame__types__insert_order_table__insert_before_1, 435, 435, 5, 25},
  {cont__types__insert_order_table__insert_before_6, &frame__types__insert_order_table__insert_before_1, 434, 438, 3, 29},
  {cont__types__insert_order_table__insert_before_11, &frame__types__insert_order_table__insert_before_1, 439, 439, 3, 55},
  {cont__types__insert_order_table__insert_before_12, &frame__types__insert_order_table__insert_before_1, 441, 441, 6, 19},
  {cont__types__insert_order_table__insert_before_13, &frame__types__insert_order_table__insert_before_1, 441, 441, 6, 19},
  {cont__types__insert_order_table__insert_before_14, &frame__types__insert_order_table__insert_before_1, 441, 441, 3, 59},
  {cont__types__insert_order_table__insert_before_17, &frame__types__insert_order_table__insert_before_1, },
  {entry__types__insert_order_table__insert_behind_3, NULL, 455, 455, 5, 29},
  {cont__types__insert_order_table__insert_behind_4, &frame__types__insert_order_table__insert_behind_3, 456, 456, 25, 25},
  {entry__types__insert_order_table__insert_behind_8, NULL, 459, 459, 69, 69},
  {entry__types__insert_order_table__insert_behind_7, NULL, 459, 459, 7, 69},
  {cont__types__insert_order_table__insert_behind_9, &frame__types__insert_order_table__insert_behind_7, 459, 459, 69, 69},
  {entry__types__insert_order_table__insert_behind_10, NULL, 461, 461, 27, 27},
  {entry__types__insert_order_table__insert_behind_15, NULL, 464, 464, 22, 59},
  {entry__types__insert_order_table__insert_behind_1, NULL, 452, 452, 3, 22},
  {cont__types__insert_order_table__insert_behind_2, &frame__types__insert_order_table__insert_behind_1, 454, 456, 3, 25},
  {cont__types__insert_order_table__insert_behind_5, &frame__types__insert_order_table__insert_behind_1, 458, 458, 5, 25},
  {cont__types__insert_order_table__insert_behind_6, &frame__types__insert_order_table__insert_behind_1, 457, 461, 3, 28},
  {cont__types__insert_order_table__insert_behind_11, &frame__types__insert_order_table__insert_behind_1, 462, 462, 3, 55},
  {cont__types__insert_order_table__insert_behind_12, &frame__types__insert_order_table__insert_behind_1, 464, 464, 6, 19},
  {cont__types__insert_order_table__insert_behind_13, &frame__types__insert_order_table__insert_behind_1, 464, 464, 6, 19},
  {cont__types__insert_order_table__insert_behind_14, &frame__types__insert_order_table__insert_behind_1, 464, 464, 3, 59},
  {cont__types__insert_order_table__insert_behind_16, &frame__types__insert_order_table__insert_behind_1, }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  // 75:   #
  // 76:     the prototype object for all insert-order tables
  initialize_maybe_future(var.types__insert_order_table, get__types__generic_table());
  // 78: $empty_node types::object
  initialize_maybe_future(var._empty_node, get__types__object());
  // 466: register_collection_serializer "insert_order_table" empty_insert_order_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1160a298062c3c9e;
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
static void entry__remove_leftmost_1(void) {
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
  frame->cont = cont__remove_leftmost_2;
}
static void cont__remove_leftmost_2(void) {
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
  frame->cont = cont__remove_leftmost_3;
}
static void cont__remove_leftmost_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 50: ... :
  // 51:   remove_leftmost &left !key !value
  // 52:   !node.left_of left
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_leftmost_4, 0);
  // 53: :
  // 54:   !key key_of(node)
  // 55:   !value value_of(node)
  // 56:   !node right_of(node)
  frame->slots[6] /* temp__3 */ = create_closure(entry__remove_leftmost_6, 0);
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
  frame->cont = cont__remove_leftmost_10;
}
static void entry__remove_leftmost_4(void) {
  allocate_initialized_frame_gc(4, 4);
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
  frame->cont = cont__remove_leftmost_5;
}
static void cont__remove_leftmost_5(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* left */ = arguments->slots[0];
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[1];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[2];
  // 52: !node.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, ((CELL *)frame->slots[0])->contents /* left */);
    ((CELL *)frame->slots[3])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__remove_leftmost_6(void) {
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
  frame->cont = cont__remove_leftmost_7;
}
static void cont__remove_leftmost_7(void) {
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
  frame->cont = cont__remove_leftmost_8;
}
static void cont__remove_leftmost_8(void) {
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
  frame->cont = cont__remove_leftmost_9;
}
static void cont__remove_leftmost_9(void) {
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
static void cont__remove_leftmost_10(void) {
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
static void entry__remove_rightmost_1(void) {
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
  frame->cont = cont__remove_rightmost_2;
}
static void cont__remove_rightmost_2(void) {
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
  frame->cont = cont__remove_rightmost_3;
}
static void cont__remove_rightmost_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 66: ... :
  // 67:   remove_rightmost &right !key !value
  // 68:   !node.right_of right
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_rightmost_4, 0);
  // 69: :
  // 70:   !key key_of(node)
  // 71:   !value value_of(node)
  // 72:   !node left_of(node)
  frame->slots[6] /* temp__3 */ = create_closure(entry__remove_rightmost_6, 0);
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
  frame->cont = cont__remove_rightmost_10;
}
static void entry__remove_rightmost_4(void) {
  allocate_initialized_frame_gc(4, 4);
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
  frame->cont = cont__remove_rightmost_5;
}
static void cont__remove_rightmost_5(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[1];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[2];
  // 68: !node.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, ((CELL *)frame->slots[0])->contents /* right */);
    ((CELL *)frame->slots[3])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__remove_rightmost_6(void) {
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
  frame->cont = cont__remove_rightmost_7;
}
static void cont__remove_rightmost_7(void) {
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
  frame->cont = cont__remove_rightmost_8;
}
static void cont__remove_rightmost_8(void) {
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
  frame->cont = cont__remove_rightmost_9;
}
static void cont__remove_rightmost_9(void) {
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
static void cont__remove_rightmost_10(void) {
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
static void entry__fetch_first_1(void) {
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
  frame->cont = cont__fetch_first_2;
}
static void cont__fetch_first_2(void) {
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
  frame->cont = cont__fetch_first_3;
}
static void cont__fetch_first_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 91: ... :
  // 92:   fetch_first &left $head
  // 93:   !myself.left_of left
  // 94:   -> head
  frame->slots[3] /* temp__2 */ = create_closure(entry__fetch_first_4, 0);
  // 95: :
  // 96:   $head myself
  // 97:   !myself right_of(myself)
  // 98:   -> head
  frame->slots[4] /* temp__3 */ = create_closure(entry__fetch_first_6, 0);
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
  frame->cont = cont__fetch_first_8;
}
static void entry__fetch_first_4(void) {
  allocate_initialized_frame_gc(2, 3);
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
  frame->cont = cont__fetch_first_5;
}
static void cont__fetch_first_5(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* left */ = arguments->slots[0];
  initialize_future(frame->slots[2] /* head */, arguments->slots[1]);
  // 93: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, ((CELL *)frame->slots[0])->contents /* left */);
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
static void entry__fetch_first_6(void) {
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
  frame->cont = cont__fetch_first_7;
}
static void cont__fetch_first_7(void) {
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
static void cont__fetch_first_8(void) {
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
static void entry__retrieve_item_1(void) {
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
  frame->cont = cont__retrieve_item_2;
}
static void cont__retrieve_item_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 106: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__retrieve_item_3, 0);
  // 106: if myself.is_undefined: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__retrieve_item_4;
}
static void entry__retrieve_item_3(void) {
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
static void cont__retrieve_item_4(void) {
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
  frame->cont = cont__retrieve_item_5;
}
static void cont__retrieve_item_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 109: -> key == my_key: return myself
  frame->slots[4] /* temp__1 */ = create_closure(entry__retrieve_item_6, 0);
  // 110: -> key < my_key: return retrieve_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__retrieve_item_9, 0);
  // 111: -> key > my_key: return retrieve_item(right_of(myself) key)
  frame->slots[6] /* temp__3 */ = create_closure(entry__retrieve_item_14, 0);
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
  frame->cont = cont__retrieve_item_19;
}
static void entry__retrieve_item_16(void) {
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
  frame->cont = cont__retrieve_item_17;
}
static void cont__retrieve_item_17(void) {
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
  frame->cont = cont__retrieve_item_18;
}
static void cont__retrieve_item_18(void) {
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
static void entry__retrieve_item_11(void) {
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
  frame->cont = cont__retrieve_item_12;
}
static void cont__retrieve_item_12(void) {
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
  frame->cont = cont__retrieve_item_13;
}
static void cont__retrieve_item_13(void) {
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
static void entry__retrieve_item_8(void) {
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
static void entry__retrieve_item_6(void) {
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
  frame->cont = cont__retrieve_item_7;
}
static void cont__retrieve_item_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 109: ... : return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__retrieve_item_8, 0);
  // 109: -> key == my_key: return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__retrieve_item_9(void) {
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
  frame->cont = cont__retrieve_item_10;
}
static void cont__retrieve_item_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 110: ... : return retrieve_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__retrieve_item_11, 0);
  // 110: -> key < my_key: return retrieve_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__retrieve_item_14(void) {
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
  frame->cont = cont__retrieve_item_15;
}
static void cont__retrieve_item_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 111: ... : return retrieve_item(right_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__retrieve_item_16, 0);
  // 111: -> key > my_key: return retrieve_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__retrieve_item_19(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__add_item_1(void) {
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
  frame->cont = cont__add_item_2;
}
static void cont__add_item_2(void) {
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
  frame->slots[8] /* temp__2 */ = create_closure(entry__add_item_3, 0);
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
  frame->cont = cont__add_item_4;
}
static void entry__add_item_3(void) {
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
static void cont__add_item_4(void) {
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
  frame->cont = cont__add_item_5;
}
static void cont__add_item_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* my_key */, arguments->slots[0]);
  // 132: -> key == my_key: return myself(.value_of value) UPDATE
  frame->slots[7] /* temp__1 */ = create_closure(entry__add_item_6, 0);
  // 133: -> key < my_key:
  // 134:   add_item $left $mode left_of(myself) previous next key value
  // 135:   return myself(.left_of left) mode
  frame->slots[8] /* temp__2 */ = create_closure(entry__add_item_9, 0);
  // 136: -> key > my_key:
  // 137:   add_item $right $mode right_of(myself) previous next key value
  // 138:   return myself(.right_of right) mode
  frame->slots[9] /* temp__3 */ = create_closure(entry__add_item_14, 0);
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
  frame->cont = cont__add_item_19;
}
static void entry__add_item_16(void) {
  allocate_initialized_frame_gc(6, 9);
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
  frame->cont = cont__add_item_17;
}
static void cont__add_item_17(void) {
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
  frame->cont = cont__add_item_18;
}
static void cont__add_item_18(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* right */, arguments->slots[0]);
  initialize_future(frame->slots[7] /* mode */, arguments->slots[1]);
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
static void entry__add_item_11(void) {
  allocate_initialized_frame_gc(6, 9);
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
  frame->cont = cont__add_item_12;
}
static void cont__add_item_12(void) {
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
  frame->cont = cont__add_item_13;
}
static void cont__add_item_13(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* left */, arguments->slots[0]);
  initialize_future(frame->slots[7] /* mode */, arguments->slots[1]);
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
static void entry__add_item_8(void) {
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
static void entry__add_item_6(void) {
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
  frame->cont = cont__add_item_7;
}
static void cont__add_item_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 132: ... : return myself(.value_of value) UPDATE
  frame->slots[6] /* temp__2 */ = create_closure(entry__add_item_8, 0);
  // 132: -> key == my_key: return myself(.value_of value) UPDATE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__add_item_9(void) {
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
  frame->cont = cont__add_item_10;
}
static void cont__add_item_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 133: ... :
  // 134:   add_item $left $mode left_of(myself) previous next key value
  // 135:   return myself(.left_of left) mode
  frame->slots[8] /* temp__2 */ = create_closure(entry__add_item_11, 0);
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
static void entry__add_item_14(void) {
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
  frame->cont = cont__add_item_15;
}
static void cont__add_item_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 136: ... :
  // 137:   add_item $right $mode right_of(myself) previous next key value
  // 138:   return myself(.right_of right) mode
  frame->slots[8] /* temp__2 */ = create_closure(entry__add_item_16, 0);
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
static void cont__add_item_19(void) {
  myself = frame->slots[5] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__update_item_1(void) {
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
  frame->cont = cont__update_item_2;
}
static void cont__update_item_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 148: -> key == my_key: updater &myself
  frame->slots[4] /* temp__1 */ = create_closure(entry__update_item_3, 0);
  // 149: -> key < my_key: update_item &myself.left_of key updater
  frame->slots[5] /* temp__2 */ = create_closure(entry__update_item_7, 0);
  // 150: -> key > my_key: update_item &myself.right_of key updater
  frame->slots[6] /* temp__3 */ = create_closure(entry__update_item_12, 0);
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
  frame->cont = cont__update_item_17;
}
static void entry__update_item_14(void) {
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
  frame->cont = cont__update_item_15;
}
static void cont__update_item_15(void) {
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
  frame->cont = cont__update_item_16;
}
static void cont__update_item_16(void) {
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
static void entry__update_item_9(void) {
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
  frame->cont = cont__update_item_10;
}
static void cont__update_item_10(void) {
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
  frame->cont = cont__update_item_11;
}
static void cont__update_item_11(void) {
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
static void entry__update_item_5(void) {
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
  frame->cont = cont__update_item_6;
}
static void cont__update_item_6(void) {
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
static void entry__update_item_3(void) {
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
  frame->cont = cont__update_item_4;
}
static void cont__update_item_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 148: ... : updater &myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__update_item_5, 0);
  // 148: -> key == my_key: updater &myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__update_item_7(void) {
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
  frame->cont = cont__update_item_8;
}
static void cont__update_item_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 149: ... : update_item &myself.left_of key updater
  frame->slots[5] /* temp__2 */ = create_closure(entry__update_item_9, 0);
  // 149: -> key < my_key: update_item &myself.left_of key updater
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__update_item_12(void) {
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
  frame->cont = cont__update_item_13;
}
static void cont__update_item_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 150: ... : update_item &myself.right_of key updater
  frame->slots[5] /* temp__2 */ = create_closure(entry__update_item_14, 0);
  // 150: -> key > my_key: update_item &myself.right_of key updater
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__update_item_17(void) {
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
static void entry__remove_item_1(void) {
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
  frame->cont = cont__remove_item_2;
}
static void cont__remove_item_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 162: ... : return NONE undefined # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_item_3, 0);
  // 162: if myself.is_undefined: return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__remove_item_4;
}
static void entry__remove_item_3(void) {
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
static void cont__remove_item_4(void) {
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
  frame->cont = cont__remove_item_5;
}
static void cont__remove_item_5(void) {
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
  frame->slots[4] /* temp__1 */ = create_closure(entry__remove_item_6, 0);
  // 178: -> key < my_key:
  // 179:   remove_item $left $removed_item left_of(myself) key
  // 180:   if NONE == left: return NONE undefined # nothing removed
  // 181:   !myself.left_of left
  // 182:   return myself removed_item
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_item_18, 0);
  // 183: -> key > my_key:
  // 184:   remove_item $right $removed_item right_of(myself) key
  // 185:   if NONE == right: return NONE undefined # nothing removed
  // 186:   !myself.right_of right
  // 187:   return myself removed_item
  frame->slots[6] /* temp__3 */ = create_closure(entry__remove_item_26, 0);
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
  frame->cont = cont__remove_item_34;
}
static void entry__remove_item_28(void) {
  allocate_initialized_frame_gc(3, 7);
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
  frame->cont = cont__remove_item_29;
}
static void cont__remove_item_29(void) {
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
  frame->cont = cont__remove_item_30;
}
static void cont__remove_item_30(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* right */, arguments->slots[0]);
  initialize_future(frame->slots[4] /* removed_item */, arguments->slots[1]);
  // 185: ... NONE == right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* right */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__remove_item_31;
}
static void cont__remove_item_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 185: ... : return NONE undefined # nothing removed
  frame->slots[6] /* temp__2 */ = create_closure(entry__remove_item_32, 0);
  // 185: if NONE == right: return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__remove_item_33;
}
static void entry__remove_item_32(void) {
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
static void cont__remove_item_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 186: !myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[3] /* right */);
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
static void entry__remove_item_20(void) {
  allocate_initialized_frame_gc(3, 7);
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
  frame->cont = cont__remove_item_21;
}
static void cont__remove_item_21(void) {
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
  frame->cont = cont__remove_item_22;
}
static void cont__remove_item_22(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* left */, arguments->slots[0]);
  initialize_future(frame->slots[4] /* removed_item */, arguments->slots[1]);
  // 180: ... NONE == left
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* left */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__remove_item_23;
}
static void cont__remove_item_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 180: ... : return NONE undefined # nothing removed
  frame->slots[6] /* temp__2 */ = create_closure(entry__remove_item_24, 0);
  // 180: if NONE == left: return NONE undefined # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__remove_item_25;
}
static void entry__remove_item_24(void) {
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
static void cont__remove_item_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 181: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[3] /* left */);
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
static void entry__remove_item_14(void) {
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
  frame->cont = cont__remove_item_15;
}
static void cont__remove_item_15(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  initialize_future(frame->slots[4] /* head */, arguments->slots[1]);
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
static void entry__remove_item_16(void) {
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
static void entry__remove_item_12(void) {
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
  frame->cont = cont__remove_item_13;
}
static void cont__remove_item_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 171: ... :
  // 172:   fetch_first &right $head
  // 173:   return head(.left_of left .right_of right) myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_item_14, 0);
  // 174: :
  // 175:   return left myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__remove_item_16, 0);
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
static void entry__remove_item_17(void) {
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
static void entry__remove_item_8(void) {
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
  frame->cont = cont__remove_item_9;
}
static void cont__remove_item_9(void) {
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
  frame->cont = cont__remove_item_10;
}
static void cont__remove_item_10(void) {
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
  frame->cont = cont__remove_item_11;
}
static void cont__remove_item_11(void) {
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
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_item_12, 0);
  // 176: :
  // 177:   return right myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__remove_item_17, 0);
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
static void entry__remove_item_6(void) {
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
  frame->cont = cont__remove_item_7;
}
static void cont__remove_item_7(void) {
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
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_item_8, 0);
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
static void entry__remove_item_18(void) {
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
  frame->cont = cont__remove_item_19;
}
static void cont__remove_item_19(void) {
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
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_item_20, 0);
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
static void entry__remove_item_26(void) {
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
  frame->cont = cont__remove_item_27;
}
static void cont__remove_item_27(void) {
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
  frame->slots[5] /* temp__2 */ = create_closure(entry__remove_item_28, 0);
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
static void cont__remove_item_34(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__private__set_item_1(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_2;
}
static void cont__types__insert_order_table__private__set_item_2(void) {
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
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__insert_order_table__private__set_item_3, 0);
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
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__insert_order_table__private__set_item_25, 0);
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
  frame->cont = cont__types__insert_order_table__private__set_item_42;
}
static void entry__types__insert_order_table__private__set_item_8(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_9;
}
static void cont__types__insert_order_table__private__set_item_9(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_10;
}
static void cont__types__insert_order_table__private__set_item_10(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_11;
}
static void cont__types__insert_order_table__private__set_item_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 204: ... :
  // 205:   update_item &new_tree previous: (&item) !item.next_of next
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__private__set_item_12, 0);
  // 206: :
  // 207:   !self.first_of next
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__insert_order_table__private__set_item_15, 0);
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
  frame->cont = cont__types__insert_order_table__private__set_item_16;
}
static void entry__types__insert_order_table__private__set_item_12(void) {
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
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__insert_order_table__private__set_item_13, 1);
  // 205: update_item &new_tree previous: (&item) !item.next_of next
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_tree */;
  arguments->slots[1] = frame->slots[1] /* previous */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__private__set_item_14;
}
static void entry__types__insert_order_table__private__set_item_13(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // next: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* next */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 205: ... !item.next_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[1] /* next */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__private__set_item_14(void) {
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
static void entry__types__insert_order_table__private__set_item_15(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // next: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* self */
  frame->slots[1] = myself->closure.frame->slots[4]; /* next */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: !self.first_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__first_of, frame->slots[1] /* next */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__private__set_item_16(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_17;
}
static void cont__types__insert_order_table__private__set_item_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 209: ... :
  // 210:   update_item &new_tree next: (&item) !item.previous_of previous
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__private__set_item_18, 0);
  // 211: :
  // 212:   !self.last_of previous
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__insert_order_table__private__set_item_21, 0);
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
  frame->cont = cont__types__insert_order_table__private__set_item_22;
}
static void entry__types__insert_order_table__private__set_item_18(void) {
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
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__insert_order_table__private__set_item_19, 1);
  // 210: update_item &new_tree next: (&item) !item.previous_of previous
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_tree */;
  arguments->slots[1] = frame->slots[1] /* next */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__private__set_item_20;
}
static void entry__types__insert_order_table__private__set_item_19(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // previous: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* previous */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 210: ... !item.previous_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__previous_of, frame->slots[1] /* previous */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__private__set_item_20(void) {
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
static void entry__types__insert_order_table__private__set_item_21(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // previous: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* previous */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: !self.last_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__last_of, frame->slots[1] /* previous */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__private__set_item_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 213: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, ((CELL *)frame->slots[1])->contents /* new_tree */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  // 214: ... self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__private__set_item_23;
}
static void cont__types__insert_order_table__private__set_item_23(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_24;
}
static void cont__types__insert_order_table__private__set_item_24(void) {
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
static void entry__types__insert_order_table__private__set_item_3(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_4;
}
static void cont__types__insert_order_table__private__set_item_4(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_5;
}
static void cont__types__insert_order_table__private__set_item_5(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* new_tree */ = arguments->slots[0];
  initialize_future(frame->slots[3] /* removed_item */, arguments->slots[1]);
  // 200: ... NONE != new_tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* new_tree */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__private__set_item_6;
}
static void cont__types__insert_order_table__private__set_item_6(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_7;
}
static void cont__types__insert_order_table__private__set_item_7(void) {
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
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__insert_order_table__private__set_item_8, 0);
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
static void entry__types__insert_order_table__private__set_item_25(void) {
  allocate_initialized_frame_gc(3, 7);
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
  frame->cont = cont__types__insert_order_table__private__set_item_26;
}
static void cont__types__insert_order_table__private__set_item_26(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_27;
}
static void cont__types__insert_order_table__private__set_item_27(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_28;
}
static void cont__types__insert_order_table__private__set_item_28(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* new_tree */ = arguments->slots[0];
  initialize_future(frame->slots[4] /* mode */, arguments->slots[1]);
  // 217: ... mode == INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* mode */;
  arguments->slots[1] = var._INSERT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__private__set_item_29;
}
static void cont__types__insert_order_table__private__set_item_29(void) {
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
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__private__set_item_30, 0);
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
  frame->cont = cont__types__insert_order_table__private__set_item_41;
}
static void entry__types__insert_order_table__private__set_item_30(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_31;
}
static void cont__types__insert_order_table__private__set_item_31(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_32;
}
static void cont__types__insert_order_table__private__set_item_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 219: ... :
  // 220:   update_item &new_tree last_of(self): (&item) !item.next_of key
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__insert_order_table__private__set_item_33, 0);
  // 221: :
  // 222:   !self.first_of key
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__insert_order_table__private__set_item_37, 0);
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
  frame->cont = cont__types__insert_order_table__private__set_item_38;
}
static void entry__types__insert_order_table__private__set_item_33(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_34;
}
static void cont__types__insert_order_table__private__set_item_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 220: ... : (&item) !item.next_of key
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__insert_order_table__private__set_item_35, 1);
  // 220: update_item &new_tree last_of(self): (&item) !item.next_of key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_tree */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__private__set_item_36;
}
static void entry__types__insert_order_table__private__set_item_35(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // key: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 220: ... !item.next_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[1] /* key */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__private__set_item_36(void) {
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
static void entry__types__insert_order_table__private__set_item_37(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 222: !self.first_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__first_of, frame->slots[1] /* key */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__private__set_item_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 223: !self.last_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__last_of, frame->slots[2] /* key */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 224: ... self.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__private__set_item_39;
}
static void cont__types__insert_order_table__private__set_item_39(void) {
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
  frame->cont = cont__types__insert_order_table__private__set_item_40;
}
static void cont__types__insert_order_table__private__set_item_40(void) {
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
static void cont__types__insert_order_table__private__set_item_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 225: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, ((CELL *)frame->slots[3])->contents /* new_tree */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__private__set_item_42(void) {
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
static void entry__types__insert_order_table__private__get_item_5(void) {
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
  frame->cont = cont__types__insert_order_table__private__get_item_6;
}
static void cont__types__insert_order_table__private__get_item_6(void) {
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
static void entry__types__insert_order_table__private__get_item_7(void) {
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
static void entry__types__insert_order_table__private__get_item_1(void) {
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
  frame->cont = cont__types__insert_order_table__private__get_item_2;
}
static void cont__types__insert_order_table__private__get_item_2(void) {
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
  frame->cont = cont__types__insert_order_table__private__get_item_3;
}
static void cont__types__insert_order_table__private__get_item_3(void) {
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
  frame->cont = cont__types__insert_order_table__private__get_item_4;
}
static void cont__types__insert_order_table__private__get_item_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 235: ... -> value_of(item)
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__insert_order_table__private__get_item_5, 0);
  // 235: if item.is_defined (-> value_of(item)) -> undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = func__types__insert_order_table__private__get_item_7;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__insert_order_table__new_empty_collection_1(void) {
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
static void entry__std__insert_order_table_1(void) {
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
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__insert_order_table_2, 1);
  // 275: for_each initializers: (initializer)
  // 276:   !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializers */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__insert_order_table_6;
}
static void entry__std__insert_order_table_2(void) {
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
  frame->cont = cont__std__insert_order_table_3;
}
static void cont__std__insert_order_table_3(void) {
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
  frame->cont = cont__std__insert_order_table_4;
}
static void cont__std__insert_order_table_4(void) {
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
  frame->cont = cont__std__insert_order_table_5;
}
static void cont__std__insert_order_table_5(void) {
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
static void cont__std__insert_order_table_6(void) {
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
static void entry__types__insert_order_table__for_each_8(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_9;
}
static void cont__types__insert_order_table__for_each_9(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_10;
}
static void cont__types__insert_order_table__for_each_10(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_11;
}
static void cont__types__insert_order_table__for_each_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 292: ... :
  // 293:   body key value_of(item)
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__insert_order_table__for_each_12, 0);
  // 294: :
  // 295:   body value_of(item)
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__insert_order_table__for_each_14, 0);
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
  frame->cont = cont__types__insert_order_table__for_each_16;
}
static void entry__types__insert_order_table__for_each_12(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_13;
}
static void cont__types__insert_order_table__for_each_13(void) {
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
static void entry__types__insert_order_table__for_each_14(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_15;
}
static void cont__types__insert_order_table__for_each_15(void) {
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
static void cont__types__insert_order_table__for_each_16(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_17;
}
static void cont__types__insert_order_table__for_each_17(void) {
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
static void entry__types__insert_order_table__for_each_6(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_7;
}
static void cont__types__insert_order_table__for_each_7(void) {
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
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__insert_order_table__for_each_8, 0);
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
static void entry__types__insert_order_table__for_each_4(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_5;
}
static void cont__types__insert_order_table__for_each_5(void) {
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
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__insert_order_table__for_each_6, 0);
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
static void entry__types__insert_order_table__for_each_1(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_2;
}
static void cont__types__insert_order_table__for_each_2(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_3;
}
static void cont__types__insert_order_table__for_each_3(void) {
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
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__insert_order_table__for_each_4, 0);
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
static void entry__types__insert_order_table__for_each_from_to_1(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_from_to_2;
}
static void cont__types__insert_order_table__for_each_from_to_2(void) {
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
  frame->cont = cont__types__insert_order_table__for_each_from_to_3;
}
static void cont__types__insert_order_table__for_each_from_to_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 309: ... :
  // 310:   $$key
  // 311:     if
  // 312:       first.is_defined
  // 313:       -> first
  // 314:       -> first_of(self)
  // 315:   
  // 316:   while -> key.is_defined:
  // 317:     $item retrieve_item(tree key)
  // 318:     if
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__insert_order_table__for_each_from_to_4, 0);
  // 309: if tree.is_defined:
  // 310:   $$key
  // 311:     if
  // 312:       first.is_defined
  // 313:       -> first
  // 314:       -> first_of(self)
  // 315:   
  // 316:   while -> key.is_defined:
  // 317:     $item retrieve_item(tree key)
  // 318:     if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_24;
}
static void entry__types__insert_order_table__for_each_from_to_12(void) {
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
  // 317: $item retrieve_item(tree key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_13;
}
static void cont__types__insert_order_table__for_each_from_to_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* item */, arguments->slots[0]);
  // 319: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_14;
}
static void cont__types__insert_order_table__for_each_from_to_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 319: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_15;
}
static void cont__types__insert_order_table__for_each_from_to_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 319: ... :
  // 320:   body key value_of(item)
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__insert_order_table__for_each_from_to_16, 0);
  // 321: :
  // 322:   body value_of(item)
  frame->slots[9] /* temp__4 */ = create_closure(entry__types__insert_order_table__for_each_from_to_18, 0);
  // 318: if
  // 319:   parameter_count_of(body) == 2:
  // 320:     body key value_of(item)
  // 321:   :
  // 322:     body value_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_20;
}
static void entry__types__insert_order_table__for_each_from_to_16(void) {
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
  // 320: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_17;
}
static void cont__types__insert_order_table__for_each_from_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 320: body key value_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__insert_order_table__for_each_from_to_18(void) {
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
  // 322: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_19;
}
static void cont__types__insert_order_table__for_each_from_to_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 322: body value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__insert_order_table__for_each_from_to_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 323: ... key == last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* last */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_21;
}
static void cont__types__insert_order_table__for_each_from_to_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 323: if key == last return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_22;
}
static void cont__types__insert_order_table__for_each_from_to_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 324: !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_23;
}
static void cont__types__insert_order_table__for_each_from_to_23(void) {
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
static void entry__types__insert_order_table__for_each_from_to_10(void) {
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
  // 316: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_11;
}
static void cont__types__insert_order_table__for_each_from_to_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 316: ... :
  // 317:   $item retrieve_item(tree key)
  // 318:   if
  // 319:     parameter_count_of(body) == 2:
  // 320:       body key value_of(item)
  // 321:     :
  // 322:       body value_of(item)
  // 323:   if key == last return
  // 324:   !key next_of(item)
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__for_each_from_to_12, 0);
  // 316: ... -> key.is_defined:
  // 317:   $item retrieve_item(tree key)
  // 318:   if
  // 319:     parameter_count_of(body) == 2:
  // 320:       body key value_of(item)
  // 321:     :
  // 322:       body value_of(item)
  // 323:   if key == last return
  // 324:   !key next_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__for_each_from_to_4(void) {
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
  // 312: first.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_5;
}
static void cont__types__insert_order_table__for_each_from_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 313: -> first
  frame->slots[8] /* temp__2 */ = create_closure(entry__types__insert_order_table__for_each_from_to_6, 0);
  // 314: -> first_of(self)
  frame->slots[9] /* temp__3 */ = create_closure(entry__types__insert_order_table__for_each_from_to_7, 0);
  // 310: $$key
  // 311:   if
  // 312:     first.is_defined
  // 313:     -> first
  // 314:     -> first_of(self)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_9;
}
static void entry__types__insert_order_table__for_each_from_to_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // first: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 313: -> first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__for_each_from_to_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 314: ... first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._first_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_to_8;
}
static void cont__types__insert_order_table__for_each_from_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 314: -> first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__for_each_from_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* key */ = arguments->slots[0];
  // 316: ... -> key.is_defined:
  // 317:   $item retrieve_item(tree key)
  // 318:   if
  // 319:     parameter_count_of(body) == 2:
  // 320:       body key value_of(item)
  // 321:     :
  // 322:       body value_of(item)
  // 323:   if key == last return
  // 324:   !key next_of(item)
  frame->slots[7] /* temp__1 */ = create_closure(entry__types__insert_order_table__for_each_from_to_10, 0);
  // 316: while -> key.is_defined:
  // 317:   $item retrieve_item(tree key)
  // 318:   if
  // 319:     parameter_count_of(body) == 2:
  // 320:       body key value_of(item)
  // 321:     :
  // 322:       body value_of(item)
  // 323:   if key == last return
  // 324:   !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__insert_order_table__for_each_from_to_24(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__for_each_from_down_to_1(void) {
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
  // 336: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_2;
}
static void cont__types__insert_order_table__for_each_from_down_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* tree */, arguments->slots[0]);
  // 337: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_3;
}
static void cont__types__insert_order_table__for_each_from_down_to_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 337: ... :
  // 338:   $$key
  // 339:     if
  // 340:       last.is_defined
  // 341:       -> last
  // 342:       -> last_of(self)
  // 343:   
  // 344:   while -> key.is_defined:
  // 345:     $item retrieve_item(tree key)
  // 346:     if
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__insert_order_table__for_each_from_down_to_4, 0);
  // 337: if tree.is_defined:
  // 338:   $$key
  // 339:     if
  // 340:       last.is_defined
  // 341:       -> last
  // 342:       -> last_of(self)
  // 343:   
  // 344:   while -> key.is_defined:
  // 345:     $item retrieve_item(tree key)
  // 346:     if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_24;
}
static void entry__types__insert_order_table__for_each_from_down_to_12(void) {
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
  // 345: $item retrieve_item(tree key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_13;
}
static void cont__types__insert_order_table__for_each_from_down_to_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* item */, arguments->slots[0]);
  // 347: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_14;
}
static void cont__types__insert_order_table__for_each_from_down_to_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 347: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_15;
}
static void cont__types__insert_order_table__for_each_from_down_to_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 347: ... :
  // 348:   body key value_of(item)
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__insert_order_table__for_each_from_down_to_16, 0);
  // 349: :
  // 350:   body value_of(item)
  frame->slots[9] /* temp__4 */ = create_closure(entry__types__insert_order_table__for_each_from_down_to_18, 0);
  // 346: if
  // 347:   parameter_count_of(body) == 2:
  // 348:     body key value_of(item)
  // 349:   :
  // 350:     body value_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_20;
}
static void entry__types__insert_order_table__for_each_from_down_to_16(void) {
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
  // 348: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_17;
}
static void cont__types__insert_order_table__for_each_from_down_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 348: body key value_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__insert_order_table__for_each_from_down_to_18(void) {
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
  // 350: ... value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_19;
}
static void cont__types__insert_order_table__for_each_from_down_to_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 350: body value_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__insert_order_table__for_each_from_down_to_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 351: ... key == first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* first */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_21;
}
static void cont__types__insert_order_table__for_each_from_down_to_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 351: if key == first return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_22;
}
static void cont__types__insert_order_table__for_each_from_down_to_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 352: !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* item */;
  result_count = 1;
  myself = var._previous_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_23;
}
static void cont__types__insert_order_table__for_each_from_down_to_23(void) {
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
static void entry__types__insert_order_table__for_each_from_down_to_10(void) {
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
  // 344: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_11;
}
static void cont__types__insert_order_table__for_each_from_down_to_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 344: ... :
  // 345:   $item retrieve_item(tree key)
  // 346:   if
  // 347:     parameter_count_of(body) == 2:
  // 348:       body key value_of(item)
  // 349:     :
  // 350:       body value_of(item)
  // 351:   if key == first return
  // 352:   !key previous_of(item)
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__for_each_from_down_to_12, 0);
  // 344: ... -> key.is_defined:
  // 345:   $item retrieve_item(tree key)
  // 346:   if
  // 347:     parameter_count_of(body) == 2:
  // 348:       body key value_of(item)
  // 349:     :
  // 350:       body value_of(item)
  // 351:   if key == first return
  // 352:   !key previous_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__for_each_from_down_to_4(void) {
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
  // 340: last.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_5;
}
static void cont__types__insert_order_table__for_each_from_down_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 341: -> last
  frame->slots[8] /* temp__2 */ = create_closure(entry__types__insert_order_table__for_each_from_down_to_6, 0);
  // 342: -> last_of(self)
  frame->slots[9] /* temp__3 */ = create_closure(entry__types__insert_order_table__for_each_from_down_to_7, 0);
  // 338: $$key
  // 339:   if
  // 340:     last.is_defined
  // 341:     -> last
  // 342:     -> last_of(self)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_9;
}
static void entry__types__insert_order_table__for_each_from_down_to_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // last: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 341: -> last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__for_each_from_down_to_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 342: ... last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._last_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__for_each_from_down_to_8;
}
static void cont__types__insert_order_table__for_each_from_down_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 342: -> last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__for_each_from_down_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* key */ = arguments->slots[0];
  // 344: ... -> key.is_defined:
  // 345:   $item retrieve_item(tree key)
  // 346:   if
  // 347:     parameter_count_of(body) == 2:
  // 348:       body key value_of(item)
  // 349:     :
  // 350:       body value_of(item)
  // 351:   if key == first return
  // 352:   !key previous_of(item)
  frame->slots[7] /* temp__1 */ = create_closure(entry__types__insert_order_table__for_each_from_down_to_10, 0);
  // 344: while -> key.is_defined:
  // 345:   $item retrieve_item(tree key)
  // 346:   if
  // 347:     parameter_count_of(body) == 2:
  // 348:       body key value_of(item)
  // 349:     :
  // 350:       body value_of(item)
  // 351:   if key == first return
  // 352:   !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__insert_order_table__for_each_from_down_to_24(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__update_each_1(void) {
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
  // 361: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_2;
}
static void cont__types__insert_order_table__update_each_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* tree */ = arguments->slots[0];
  // 362: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_3;
}
static void cont__types__insert_order_table__update_each_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 362: ... :
  // 363:   $$key first_of(self)
  // 364:   while -> key.is_defined:
  // 365:     update_item &tree key: (&item)
  // 366:       body key &item.value_of
  // 367:       !key next_of(item)
  // 368:   !self.tree_of tree
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__insert_order_table__update_each_4, 0);
  // 362: if tree.is_defined:
  // 363:   $$key first_of(self)
  // 364:   while -> key.is_defined:
  // 365:     update_item &tree key: (&item)
  // 366:       body key &item.value_of
  // 367:       !key next_of(item)
  // 368:   !self.tree_of tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_15;
}
static void entry__types__insert_order_table__update_each_4(void) {
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
  // 363: $$key first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._first_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_5;
}
static void cont__types__insert_order_table__update_each_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* key */ = arguments->slots[0];
  // 364: ... -> key.is_defined:
  // 365:   update_item &tree key: (&item)
  // 366:     body key &item.value_of
  // 367:     !key next_of(item)
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__insert_order_table__update_each_6, 0);
  // 364: while -> key.is_defined:
  // 365:   update_item &tree key: (&item)
  // 366:     body key &item.value_of
  // 367:     !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_14;
}
static void entry__types__insert_order_table__update_each_8(void) {
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
  // 365: ... : (&item)
  // 366:   body key &item.value_of
  // 367:   !key next_of(item)
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__insert_order_table__update_each_9, 1);
  // 365: update_item &tree key: (&item)
  // 366:   body key &item.value_of
  // 367:   !key next_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_13;
}
static void entry__types__insert_order_table__update_each_9(void) {
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
  // 366: ... item.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_10;
}
static void cont__types__insert_order_table__update_each_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 366: body key &item.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_11;
}
static void cont__types__insert_order_table__update_each_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 366: ... &item.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  // 367: !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_12;
}
static void cont__types__insert_order_table__update_each_12(void) {
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
static void cont__types__insert_order_table__update_each_13(void) {
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
static void entry__types__insert_order_table__update_each_6(void) {
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
  // 364: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_7;
}
static void cont__types__insert_order_table__update_each_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 364: ... :
  // 365:   update_item &tree key: (&item)
  // 366:     body key &item.value_of
  // 367:     !key next_of(item)
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__insert_order_table__update_each_8, 0);
  // 364: ... -> key.is_defined:
  // 365:   update_item &tree key: (&item)
  // 366:     body key &item.value_of
  // 367:     !key next_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 368: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, ((CELL *)frame->slots[1])->contents /* tree */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_15(void) {
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
static void entry__types__insert_order_table__update_each_from_to_1(void) {
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
  // 379: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_2;
}
static void cont__types__insert_order_table__update_each_from_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 380: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_3;
}
static void cont__types__insert_order_table__update_each_from_to_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 380: ... :
  // 381:   $$key
  // 382:     if
  // 383:       first.is_defined
  // 384:       -> first
  // 385:       -> first_of(self)
  // 386:   
  // 387:   do: (-> break)
  // 388:     while -> key.is_defined:
  // 389:       update_item &tree key: (&item)
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__update_each_from_to_4, 0);
  // 380: if tree.is_defined:
  // 381:   $$key
  // 382:     if
  // 383:       first.is_defined
  // 384:       -> first
  // 385:       -> first_of(self)
  // 386:   
  // 387:   do: (-> break)
  // 388:     while -> key.is_defined:
  // 389:       update_item &tree key: (&item)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_23;
}
static void entry__types__insert_order_table__update_each_from_to_4(void) {
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
  // 383: first.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_5;
}
static void cont__types__insert_order_table__update_each_from_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 384: -> first
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__insert_order_table__update_each_from_to_6, 0);
  // 385: -> first_of(self)
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__insert_order_table__update_each_from_to_7, 0);
  // 381: $$key
  // 382:   if
  // 383:     first.is_defined
  // 384:     -> first
  // 385:     -> first_of(self)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_9;
}
static void entry__types__insert_order_table__update_each_from_to_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // first: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 384: -> first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__update_each_from_to_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 385: ... first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._first_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_8;
}
static void cont__types__insert_order_table__update_each_from_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 385: -> first_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_from_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  // 387: ... : (-> break)
  // 388:   while -> key.is_defined:
  // 389:     update_item &tree key: (&item)
  // 390:       body key &item.value_of
  // 391:       if key == last break
  // 392:       !key next_of(item)
  frame->slots[6] /* temp__1 */ = create_closure(entry__types__insert_order_table__update_each_from_to_10, 0);
  // 387: do: (-> break)
  // 388:   while -> key.is_defined:
  // 389:     update_item &tree key: (&item)
  // 390:       body key &item.value_of
  // 391:       if key == last break
  // 392:       !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_22;
}
static void entry__types__insert_order_table__update_each_from_to_10(void) {
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
  // 388: ... -> key.is_defined:
  // 389:   update_item &tree key: (&item)
  // 390:     body key &item.value_of
  // 391:     if key == last break
  // 392:     !key next_of(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__insert_order_table__update_each_from_to_11, 0);
  // 388: while -> key.is_defined:
  // 389:   update_item &tree key: (&item)
  // 390:     body key &item.value_of
  // 391:     if key == last break
  // 392:     !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_21;
}
static void entry__types__insert_order_table__update_each_from_to_13(void) {
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
  // 389: ... : (&item)
  // 390:   body key &item.value_of
  // 391:   if key == last break
  // 392:   !key next_of(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__insert_order_table__update_each_from_to_14, 1);
  // 389: update_item &tree key: (&item)
  // 390:   body key &item.value_of
  // 391:   if key == last break
  // 392:   !key next_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_20;
}
static void entry__types__insert_order_table__update_each_from_to_14(void) {
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
  // 390: ... item.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_15;
}
static void cont__types__insert_order_table__update_each_from_to_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 390: body key &item.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_16;
}
static void cont__types__insert_order_table__update_each_from_to_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 390: ... &item.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  // 391: ... key == last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* last */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_17;
}
static void cont__types__insert_order_table__update_each_from_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 391: if key == last break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_18;
}
static void cont__types__insert_order_table__update_each_from_to_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 392: !key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_19;
}
static void cont__types__insert_order_table__update_each_from_to_19(void) {
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
static void cont__types__insert_order_table__update_each_from_to_20(void) {
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
static void entry__types__insert_order_table__update_each_from_to_11(void) {
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
  // 388: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_to_12;
}
static void cont__types__insert_order_table__update_each_from_to_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 388: ... :
  // 389:   update_item &tree key: (&item)
  // 390:     body key &item.value_of
  // 391:     if key == last break
  // 392:     !key next_of(item)
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__update_each_from_to_13, 0);
  // 388: ... -> key.is_defined:
  // 389:   update_item &tree key: (&item)
  // 390:     body key &item.value_of
  // 391:     if key == last break
  // 392:     !key next_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_from_to_21(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_from_to_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 393: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, ((CELL *)frame->slots[2])->contents /* tree */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_from_to_23(void) {
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
static void entry__types__insert_order_table__update_each_from_down_to_1(void) {
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
  // 404: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_2;
}
static void cont__types__insert_order_table__update_each_from_down_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 405: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_3;
}
static void cont__types__insert_order_table__update_each_from_down_to_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 405: ... :
  // 406:   $$key
  // 407:     if
  // 408:       last.is_defined
  // 409:       -> last
  // 410:       -> last_of(self)
  // 411:   
  // 412:   do: (-> break)
  // 413:     while -> key.is_defined:
  // 414:       update_item &tree key: (&item)
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__update_each_from_down_to_4, 0);
  // 405: if tree.is_defined:
  // 406:   $$key
  // 407:     if
  // 408:       last.is_defined
  // 409:       -> last
  // 410:       -> last_of(self)
  // 411:   
  // 412:   do: (-> break)
  // 413:     while -> key.is_defined:
  // 414:       update_item &tree key: (&item)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_23;
}
static void entry__types__insert_order_table__update_each_from_down_to_4(void) {
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
  // 408: last.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_5;
}
static void cont__types__insert_order_table__update_each_from_down_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 409: -> last
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__insert_order_table__update_each_from_down_to_6, 0);
  // 410: -> last_of(self)
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__insert_order_table__update_each_from_down_to_7, 0);
  // 406: $$key
  // 407:   if
  // 408:     last.is_defined
  // 409:     -> last
  // 410:     -> last_of(self)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_9;
}
static void entry__types__insert_order_table__update_each_from_down_to_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // last: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* last */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 409: -> last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__insert_order_table__update_each_from_down_to_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 410: ... last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._last_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_8;
}
static void cont__types__insert_order_table__update_each_from_down_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 410: -> last_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_from_down_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  // 412: ... : (-> break)
  // 413:   while -> key.is_defined:
  // 414:     update_item &tree key: (&item)
  // 415:       body key &item.value_of
  // 416:       if key == first break
  // 417:       !key previous_of(item)
  frame->slots[6] /* temp__1 */ = create_closure(entry__types__insert_order_table__update_each_from_down_to_10, 0);
  // 412: do: (-> break)
  // 413:   while -> key.is_defined:
  // 414:     update_item &tree key: (&item)
  // 415:       body key &item.value_of
  // 416:       if key == first break
  // 417:       !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_22;
}
static void entry__types__insert_order_table__update_each_from_down_to_10(void) {
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
  // 413: ... -> key.is_defined:
  // 414:   update_item &tree key: (&item)
  // 415:     body key &item.value_of
  // 416:     if key == first break
  // 417:     !key previous_of(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__insert_order_table__update_each_from_down_to_11, 0);
  // 413: while -> key.is_defined:
  // 414:   update_item &tree key: (&item)
  // 415:     body key &item.value_of
  // 416:     if key == first break
  // 417:     !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_21;
}
static void entry__types__insert_order_table__update_each_from_down_to_13(void) {
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
  // 414: ... : (&item)
  // 415:   body key &item.value_of
  // 416:   if key == first break
  // 417:   !key previous_of(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__insert_order_table__update_each_from_down_to_14, 1);
  // 414: update_item &tree key: (&item)
  // 415:   body key &item.value_of
  // 416:   if key == first break
  // 417:   !key previous_of(item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_20;
}
static void entry__types__insert_order_table__update_each_from_down_to_14(void) {
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
  // 415: ... item.value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._value_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_15;
}
static void cont__types__insert_order_table__update_each_from_down_to_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 415: body key &item.value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_16;
}
static void cont__types__insert_order_table__update_each_from_down_to_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 415: ... &item.value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__value_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  // 416: ... key == first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* first */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_17;
}
static void cont__types__insert_order_table__update_each_from_down_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 416: if key == first break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_18;
}
static void cont__types__insert_order_table__update_each_from_down_to_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 417: !key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._previous_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_19;
}
static void cont__types__insert_order_table__update_each_from_down_to_19(void) {
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
static void cont__types__insert_order_table__update_each_from_down_to_20(void) {
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
static void entry__types__insert_order_table__update_each_from_down_to_11(void) {
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
  // 413: ... key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__update_each_from_down_to_12;
}
static void cont__types__insert_order_table__update_each_from_down_to_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 413: ... :
  // 414:   update_item &tree key: (&item)
  // 415:     body key &item.value_of
  // 416:     if key == first break
  // 417:     !key previous_of(item)
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__insert_order_table__update_each_from_down_to_13, 0);
  // 413: ... -> key.is_defined:
  // 414:   update_item &tree key: (&item)
  // 415:     body key &item.value_of
  // 416:     if key == first break
  // 417:     !key previous_of(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_from_down_to_21(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_from_down_to_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 418: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, ((CELL *)frame->slots[2])->contents /* tree */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__update_each_from_down_to_23(void) {
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
static void entry__types__insert_order_table__insert_before_1(void) {
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
  // 429: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_2;
}
static void cont__types__insert_order_table__insert_before_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 430: $$before_key undefined
  ((CELL *)frame->slots[5])->contents /* before_key */ = get__undefined();
  // 431: ... : (&item)
  // 432:   !before_key previous_of(item)
  // 433:   !item.previous_of new_key
  frame->slots[7] /* temp__1 */ = create_closure(entry__types__insert_order_table__insert_before_3, 1);
  // 431: update_item &tree key: (&item)
  // 432:   !before_key previous_of(item)
  // 433:   !item.previous_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_5;
}
static void entry__types__insert_order_table__insert_before_3(void) {
  allocate_initialized_frame_gc(3, 3);
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
  // 432: !before_key previous_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._previous_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_4;
}
static void cont__types__insert_order_table__insert_before_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* before_key */ = arguments->slots[0];
  // 433: !item.previous_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__previous_of, frame->slots[2] /* new_key */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__insert_before_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 435: before_key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* before_key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_6;
}
static void cont__types__insert_order_table__insert_before_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 435: ... :
  // 436:   update_item &tree before_key: (&item) !item.next_of new_key
  frame->slots[8] /* temp__2 */ = create_closure(entry__types__insert_order_table__insert_before_7, 0);
  // 437: :
  // 438:   !self.first_of new_key
  frame->slots[9] /* temp__3 */ = create_closure(entry__types__insert_order_table__insert_before_10, 0);
  // 434: if
  // 435:   before_key.is_defined:
  // 436:     update_item &tree before_key: (&item) !item.next_of new_key
  // 437:   :
  // 438:     !self.first_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_11;
}
static void entry__types__insert_order_table__insert_before_7(void) {
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
  // 436: ... : (&item) !item.next_of new_key
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__insert_order_table__insert_before_8, 1);
  // 436: update_item &tree before_key: (&item) !item.next_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* before_key */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_9;
}
static void entry__types__insert_order_table__insert_before_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // new_key: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 436: ... !item.next_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[1] /* new_key */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__insert_before_9(void) {
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
static void entry__types__insert_order_table__insert_before_10(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // new_key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 438: !self.first_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__first_of, frame->slots[1] /* new_key */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__insert_before_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 439: add_item &tree $mode before_key key new_key new_value
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
  frame->cont = cont__types__insert_order_table__insert_before_12;
}
static void cont__types__insert_order_table__insert_before_12(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  initialize_future(frame->slots[6] /* mode */, arguments->slots[1]);
  // 440: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, ((CELL *)frame->slots[4])->contents /* tree */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 441: ... mode != INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* mode */;
  arguments->slots[1] = var._INSERT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_13;
}
static void cont__types__insert_order_table__insert_before_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 441: ... mode != INSERT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_14;
}
static void cont__types__insert_order_table__insert_before_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 441: if mode != INSERT: raise "Invalid tree insert operation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__types__insert_order_table__insert_before_15;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_before_17;
}
static void entry__types__insert_order_table__insert_before_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... raise "Invalid tree insert operation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__d2f4ba5cf0563ffa;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__insert_order_table__insert_before_17(void) {
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
static void entry__types__insert_order_table__insert_behind_1(void) {
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
  // 452: $$tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_2;
}
static void cont__types__insert_order_table__insert_behind_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 453: $$behind_key undefined
  ((CELL *)frame->slots[5])->contents /* behind_key */ = get__undefined();
  // 454: ... : (&item)
  // 455:   !behind_key next_of(item)
  // 456:   !item.next_of new_key
  frame->slots[7] /* temp__1 */ = create_closure(entry__types__insert_order_table__insert_behind_3, 1);
  // 454: update_item &tree key: (&item)
  // 455:   !behind_key next_of(item)
  // 456:   !item.next_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* tree */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_5;
}
static void entry__types__insert_order_table__insert_behind_3(void) {
  allocate_initialized_frame_gc(3, 3);
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
  // 455: !behind_key next_of(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  result_count = 1;
  myself = var._next_of;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_4;
}
static void cont__types__insert_order_table__insert_behind_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* behind_key */ = arguments->slots[0];
  // 456: !item.next_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__next_of, frame->slots[2] /* new_key */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__insert_behind_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  // 458: behind_key.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* behind_key */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_6;
}
static void cont__types__insert_order_table__insert_behind_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 458: ... :
  // 459:   update_item &tree behind_key: (&item) !item.previous_of new_key
  frame->slots[8] /* temp__2 */ = create_closure(entry__types__insert_order_table__insert_behind_7, 0);
  // 460: :
  // 461:   !self.last_of new_key
  frame->slots[9] /* temp__3 */ = create_closure(entry__types__insert_order_table__insert_behind_10, 0);
  // 457: if
  // 458:   behind_key.is_defined:
  // 459:     update_item &tree behind_key: (&item) !item.previous_of new_key
  // 460:   :
  // 461:     !self.last_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_11;
}
static void entry__types__insert_order_table__insert_behind_7(void) {
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
  // 459: ... : (&item) !item.previous_of new_key
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__insert_order_table__insert_behind_8, 1);
  // 459: update_item &tree behind_key: (&item) !item.previous_of new_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* behind_key */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._update_item;
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_9;
}
static void entry__types__insert_order_table__insert_behind_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // new_key: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* item */ = create_cell_with_contents(arguments->slots[0]);
  // 459: ... !item.previous_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* item */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__previous_of, frame->slots[1] /* new_key */);
    ((CELL *)frame->slots[0])->contents /* item */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* item */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__insert_behind_9(void) {
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
static void entry__types__insert_order_table__insert_behind_10(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // new_key: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 461: !self.last_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__last_of, frame->slots[1] /* new_key */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__insert_order_table__insert_behind_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 462: add_item &tree $mode key behind_key new_key new_value
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
  frame->cont = cont__types__insert_order_table__insert_behind_12;
}
static void cont__types__insert_order_table__insert_behind_12(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* tree */ = arguments->slots[0];
  initialize_future(frame->slots[6] /* mode */, arguments->slots[1]);
  // 463: !self.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, ((CELL *)frame->slots[4])->contents /* tree */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 464: ... mode != INSERT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* mode */;
  arguments->slots[1] = var._INSERT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_13;
}
static void cont__types__insert_order_table__insert_behind_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 464: ... mode != INSERT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_14;
}
static void cont__types__insert_order_table__insert_behind_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 464: if mode != INSERT: raise "Invalid tree insert operation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__types__insert_order_table__insert_behind_15;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__insert_order_table__insert_behind_16;
}
static void entry__types__insert_order_table__insert_behind_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 464: ... raise "Invalid tree insert operation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__d2f4ba5cf0563ffa;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__insert_order_table__insert_behind_16(void) {
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
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__insert_order_table(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__insert_order_table");
  number__0 = from_uint32(0U);
  number__2 = from_uint32(2U);
  define_polymorphic_function("std", "is_an_insert_order_table", get__std__is_an_insert_order_table, &poly_idx__std__is_an_insert_order_table, &var.std__is_an_insert_order_table);
  unique__NONE = register_unique_item("NONE");
  unique__INSERT = register_unique_item("INSERT");
  unique__UPDATE = register_unique_item("UPDATE");
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::tree_of", &poly_idx__tree_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::first_of", &poly_idx__first_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::last_of", &poly_idx__last_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::key_of", &poly_idx__key_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::value_of", &poly_idx__value_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::left_of", &poly_idx__left_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::right_of", &poly_idx__right_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::next_of", &poly_idx__next_of);
  register_polymorphic_function_with_setter("_basic__types__insert_order_table::previous_of", &poly_idx__previous_of);
  func__remove_leftmost_1 = create_function(entry__remove_leftmost_1, 1);
  func__remove_rightmost_1 = create_function(entry__remove_rightmost_1, 1);
  func__fetch_first_1 = create_function(entry__fetch_first_1, 1);
  func__retrieve_item_1 = create_function(entry__retrieve_item_1, 2);
  func__add_item_1 = create_function(entry__add_item_1, 5);
  func__update_item_1 = create_function(entry__update_item_1, 3);
  func__remove_item_1 = create_function(entry__remove_item_1, 2);
  func__types__insert_order_table__private__set_item_1 = create_function(entry__types__insert_order_table__private__set_item_1, 3);
  func__types__insert_order_table__private__get_item_7 = create_function(entry__types__insert_order_table__private__get_item_7, 0);
  func__types__insert_order_table__private__get_item_1 = create_function(entry__types__insert_order_table__private__get_item_1, 2);
  string__1160a298062c3c9e = from_latin_1_string("insert_order_table", 18);
  func__types__insert_order_table__new_empty_collection_1 = create_function(entry__types__insert_order_table__new_empty_collection_1, 1);
  func__std__insert_order_table_1 = create_function(entry__std__insert_order_table_1, -1);
  func__types__insert_order_table__for_each_1 = create_function(entry__types__insert_order_table__for_each_1, 2);
  func__types__insert_order_table__for_each_from_to_1 = create_function(entry__types__insert_order_table__for_each_from_to_1, 4);
  func__types__insert_order_table__for_each_from_down_to_1 = create_function(entry__types__insert_order_table__for_each_from_down_to_1, 4);
  func__types__insert_order_table__update_each_1 = create_function(entry__types__insert_order_table__update_each_1, 2);
  func__types__insert_order_table__update_each_from_to_1 = create_function(entry__types__insert_order_table__update_each_from_to_1, 4);
  func__types__insert_order_table__update_each_from_down_to_1 = create_function(entry__types__insert_order_table__update_each_from_down_to_1, 4);
  string__d2f4ba5cf0563ffa = from_latin_1_string("Invalid tree insert operation!", 30);
  func__types__insert_order_table__insert_before_15 = create_function(entry__types__insert_order_table__insert_before_15, 0);
  func__types__insert_order_table__insert_before_1 = create_function(entry__types__insert_order_table__insert_before_1, 4);
  func__types__insert_order_table__insert_behind_15 = create_function(entry__types__insert_order_table__insert_behind_15, 0);
  func__types__insert_order_table__insert_behind_1 = create_function(entry__types__insert_order_table__insert_behind_1, 4);
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
  var.types__insert_order_table = create_future();
  define_single_assign_static("types", "insert_order_table", get__types__insert_order_table, &var.types__insert_order_table);
  var._empty_node = create_future();
  var.std__empty_insert_order_table = create_future();
  define_single_assign_static("std", "empty_insert_order_table", get__std__empty_insert_order_table, &var.std__empty_insert_order_table);
  var.std__insert_order_table = create_future();
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
  define_method("types", "insert_order_table", poly_idx__private__set_item, func__types__insert_order_table__private__set_item_1);
  define_method("types", "insert_order_table", poly_idx__private__get_item, func__types__insert_order_table__private__get_item_1);
  define_attribute("types", "insert_order_table", poly_idx__tree_of, get__undefined());
  define_attribute("types", "insert_order_table", poly_idx__first_of, get__undefined());
  define_attribute("types", "insert_order_table", poly_idx__last_of, get__undefined());
  define_attribute("types", "insert_order_table", poly_idx__length_of, number__0);
  define_attribute("types", "insert_order_table", poly_idx__serialization_tag_of, string__1160a298062c3c9e);
  define_method("types", "insert_order_table", poly_idx__new_empty_collection, func__types__insert_order_table__new_empty_collection_1);
  define_method("types", "insert_order_table", poly_idx__for_each, func__types__insert_order_table__for_each_1);
  define_method("types", "insert_order_table", poly_idx__for_each_from_to, func__types__insert_order_table__for_each_from_to_1);
  define_method("types", "insert_order_table", poly_idx__for_each_from_down_to, func__types__insert_order_table__for_each_from_down_to_1);
  define_method("types", "insert_order_table", poly_idx__update_each, func__types__insert_order_table__update_each_1);
  define_method("types", "insert_order_table", poly_idx__update_each_from_to, func__types__insert_order_table__update_each_from_to_1);
  define_method("types", "insert_order_table", poly_idx__update_each_from_down_to, func__types__insert_order_table__update_each_from_down_to_1);
  define_method("types", "insert_order_table", poly_idx__insert_before, func__types__insert_order_table__insert_before_1);
  define_method("types", "insert_order_table", poly_idx__insert_behind, func__types__insert_order_table__insert_behind_1);
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
  assign_variable(&var._remove_leftmost, &func__remove_leftmost_1);
  assign_variable(&var._remove_rightmost, &func__remove_rightmost_1);
  initialize_future(var.types__insert_order_table, get__types__generic_table());
  initialize_future(var._empty_node, get__types__object());
  assign_variable(&var._fetch_first, &func__fetch_first_1);
  assign_variable(&var._retrieve_item, &func__retrieve_item_1);
  assign_variable(&var._add_item, &func__add_item_1);
  assign_variable(&var._update_item, &func__update_item_1);
  assign_variable(&var._remove_item, &func__remove_item_1);
  initialize_future(var.std__empty_insert_order_table, var.types__insert_order_table);
  initialize_future(var.std__insert_order_table, func__std__insert_order_table_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__insert_order_table(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__insert_order_table);
}
