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
REGISTER FUNC func ASM("r14");
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
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_cell(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void define_type_function(
  const char *namespace, const char *name, FUNC type, int par_cnt
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
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
static NODE_GETTER get__deserialize_item;
static NODE_GETTER get_value_or_future__deserialize_item;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__get_deserialization_indent;
static NODE_GETTER get_value_or_future__get_deserialization_indent;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__is_a_table;
static NODE_GETTER get__is_a_table;
static int poly_idx__is_empty;
static NODE_GETTER get__is_empty;
static int poly_idx__keys_of;
static NODE_GETTER get__keys_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static int poly_idx__map;
static NODE_GETTER get__map;
static NODE_GETTER get__new_empty_collection;
static NODE_GETTER get_value_or_future__new_empty_collection;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__raise;
static NODE_GETTER get_value_or_future__raise;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__register_collection_serializer;
static NODE_GETTER get_value_or_future__register_collection_serializer;
static NODE_GETTER get__register_deserializer;
static NODE_GETTER get_value_or_future__register_deserializer;
static int poly_idx__serialization_tag_of;
static NODE_GETTER get__serialization_tag_of;
static int poly_idx__serialize;
static NODE_GETTER get__serialize;
static NODE_GETTER get__spaces;
static NODE_GETTER get_value_or_future__spaces;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_of;
static NODE_GETTER get_value_or_future__std__key_of;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__std__value_of;
static NODE_GETTER get_value_or_future__std__value_of;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__types__unordered_table;
static NODE_GETTER get_value_or_future__types__unordered_table;
static int poly_idx__union;
static NODE_GETTER get__union;
static int poly_idx__values_of;
static NODE_GETTER get__values_of;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static struct {
  NODE *_NONE;
  NODE *private__set_item;
  NODE *private__get_item;
  NODE *types__generic_table;
  NODE *std__is_a_table;
  NODE *types__table;
  NODE *std__empty_table;
  NODE *std__table;
  NODE *std__register_collection_serializer;
} var;
static const char *var_names[] = {
  "NONE"
};
static int poly_idx__private__set_item;
static void type__private__set_item(void);
static NODE *get__private__set_item(void) {
  return var.private__set_item;
}
static int poly_idx__private__get_item;
static void type__private__get_item(void);
static NODE *get__private__get_item(void) {
  return var.private__get_item;
}
static NODE *get__types__generic_table(void) {
  return var.types__generic_table;
}
static NODE *unique__NONE;
static NODE *func__5_1_types__generic_table_;
static void entry__5_1_types__generic_table_(void);
static FRAME_INFO frame__5_1_types__generic_table_ = {3, {"key", "value", "myself"}};
static void cont__5_2(void);
static NODE *func__5_3;
static void entry__5_3(void);
static FRAME_INFO frame__5_3 = {2, {"myself", "key"}};
static NODE *func__5_4;
static void entry__5_4(void);
static FRAME_INFO frame__5_4 = {3, {"myself", "key", "value"}};
static NODE *func__6_1_types__generic_table_union;
static void entry__6_1_types__generic_table_union(void);
static FRAME_INFO frame__6_1_types__generic_table_union = {2, {"left", "right"}};
static NODE *func__6_2;
static void entry__6_2(void);
static FRAME_INFO frame__6_2 = {3, {"key", "value", "left"}};
static void cont__6_3(void);
static void cont__6_4(void);
static NODE *func__7_1_types__generic_table_map;
static void entry__7_1_types__generic_table_map(void);
static FRAME_INFO frame__7_1_types__generic_table_map = {3, {"self", "func", "new_table"}};
static void cont__7_2(void);
static NODE *func__7_3;
static void entry__7_3(void);
static FRAME_INFO frame__7_3 = {4, {"key", "value", "new_table", "func"}};
static void cont__7_4(void);
static void cont__7_5(void);
static void cont__7_6(void);
static NODE *func__8_1_types__generic_table_serialize;
static void entry__8_1_types__generic_table_serialize(void);
static FRAME_INFO frame__8_1_types__generic_table_serialize = {5, {"self", "indent", "return", "tag", "buf"}};
static void cont__8_2(void);
static void cont__8_3(void);
static NODE *func__8_4;
static void entry__8_4(void);
static FRAME_INFO frame__8_4 = {2, {"return", "tag"}};
static NODE *string__8_5;
static void cont__8_6(void);
static void cont__8_7(void);
static NODE *func__8_8;
static void entry__8_8(void);
static FRAME_INFO frame__8_8 = {4, {"key", "value", "buf", "indent"}};
static void cont__8_9(void);
static void cont__8_10(void);
static void cont__8_11(void);
static void cont__8_12(void);
static void cont__8_13(void);
static void cont__8_14(void);
static NODE *string__8_15;
static void cont__8_16(void);
static void cont__8_17(void);
static NODE *func__9_1_types__generic_table_keys_of;
static void entry__9_1_types__generic_table_keys_of(void);
static FRAME_INFO frame__9_1_types__generic_table_keys_of = {2, {"self", "keys"}};
static NODE *func__9_2;
static void entry__9_2(void);
static FRAME_INFO frame__9_2 = {3, {"key", "value", "keys"}};
static void cont__9_3(void);
static void cont__9_4(void);
static NODE *func__10_1_types__generic_table_values_of;
static void entry__10_1_types__generic_table_values_of(void);
static FRAME_INFO frame__10_1_types__generic_table_values_of = {2, {"self", "values"}};
static NODE *func__10_2;
static void entry__10_2(void);
static FRAME_INFO frame__10_2 = {3, {"key", "value", "values"}};
static void cont__10_3(void);
static void cont__10_4(void);
static NODE *func__11_1_types__generic_table_is_empty;
static void entry__11_1_types__generic_table_is_empty(void);
static FRAME_INFO frame__11_1_types__generic_table_is_empty = {1, {"self"}};
static void cont__11_2(void);
static void cont__11_3(void);
static int poly_idx__std__is_a_table;
static void type__std__is_a_table(void);
static NODE *get__std__is_a_table(void) {
  return var.std__is_a_table;
}
static NODE *get__types__table(void) {
  return var.types__table;
}
static NODE *string__16_1;
static NODE *get__std__empty_table(void) {
  return var.std__empty_table;
}
static NODE *func__18_1_std__table;
static void entry__18_1_std__table(void);
static FRAME_INFO frame__18_1_std__table = {2, {"args", "tab"}};
static NODE *func__18_2;
static void entry__18_2(void);
static FRAME_INFO frame__18_2 = {2, {"arg", "tab"}};
static void cont__18_3(void);
static void cont__18_4(void);
static void cont__18_5(void);
static void cont__18_6(void);
static NODE *get__std__table(void) {
  return var.std__table;
}
static NODE *func__19_1_std__register_collection_serializer;
static void entry__19_1_std__register_collection_serializer(void);
static FRAME_INFO frame__19_1_std__register_collection_serializer = {2, {"name", "empty_collection"}};
static NODE *func__19_2;
static void entry__19_2(void);
static FRAME_INFO frame__19_2 = {7, {"text", "base_indent", "return", "name", "empty_collection", "invalid_table_error", "obj"}};
static NODE *func__19_3_invalid_table_error;
static void entry__19_3_invalid_table_error(void);
static FRAME_INFO frame__19_3_invalid_table_error = {1, {"name"}};
static NODE *string__19_4;
static NODE *string__19_5;
static void cont__19_6(void);
static void cont__19_7(void);
static NODE *func__19_8;
static void entry__19_8(void);
static FRAME_INFO frame__19_8 = {2, {"return", "text"}};
static void cont__19_9(void);
static void cont__19_10(void);
static void cont__19_11(void);
static void cont__19_12(void);
static void cont__19_13(void);
static void cont__19_14(void);
static void cont__19_15(void);
static NODE *func__19_16;
static void entry__19_16(void);
static FRAME_INFO frame__19_16 = {9, {"text", "return", "obj", "base_indent", "invalid_table_error", "remaining_text", "indent", "key", "value"}};
static void cont__19_17(void);
static void cont__19_18(void);
static NODE *func__19_19;
static void entry__19_19(void);
static FRAME_INFO frame__19_19 = {1, {"text"}};
static void cont__19_20(void);
static void cont__19_21(void);
static void cont__19_22(void);
static void cont__19_23(void);
static NODE *func__19_24;
static void entry__19_24(void);
static FRAME_INFO frame__19_24 = {3, {"return", "text", "obj"}};
static void cont__19_25(void);
static void cont__19_26(void);
static void cont__19_27(void);
static void cont__19_28(void);
static NODE *func__19_29;
static void entry__19_29(void);
static FRAME_INFO frame__19_29 = {3, {"return", "text", "obj"}};
static void cont__19_30(void);
static void cont__19_31(void);
static NODE *func__19_32;
static void entry__19_32(void);
static FRAME_INFO frame__19_32 = {1, {"text"}};
static void cont__19_33(void);
static void cont__19_34(void);
static void cont__19_35(void);
static NODE *func__19_36;
static void entry__19_36(void);
static FRAME_INFO frame__19_36 = {1, {"text"}};
static void cont__19_37(void);
static void cont__19_38(void);
static void cont__19_39(void);
static NODE *func__19_40;
static void entry__19_40(void);
static FRAME_INFO frame__19_40 = {1, {"text"}};
static void cont__19_41(void);
static void cont__19_42(void);
static void cont__19_43(void);
static void cont__19_44(void);
static void cont__19_45(void);
static NODE *func__19_46;
static void entry__19_46(void);
static FRAME_INFO frame__19_46 = {1, {"text"}};
static void cont__19_47(void);
static void cont__19_48(void);
static void cont__19_49(void);
static void cont__19_50(void);
static void cont__19_51(void);
static void cont__19_52(void);
static void cont__19_53(void);
static void cont__19_54(void);
static void cont__19_55(void);
static void cont__19_56(void);
static NODE *get__std__register_collection_serializer(void) {
  return var.std__register_collection_serializer;
}
static void cont__40_1(void);
void run__basic__types__table(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__private__set_item, NULL, 23, 23, 2, 18},
  {type__private__get_item, NULL, 31, 31, 2, 18},
  {type__std__is_a_table, NULL, 127, 127, 2, 16},
  {run__basic__types__table, NULL, 191, 191, 1, 50},
  {cont__40_1, NULL, },
  {entry__5_3, NULL, 54, 54, 7, 34},
  {entry__5_4, NULL, 56, 56, 7, 40},
  {entry__5_1_types__generic_table_, NULL, 53, 53, 5, 17},
  {cont__5_2, &frame__5_1_types__generic_table_, 52, 56, 3, 41},
  {entry__6_2, NULL, 65, 65, 31, 40},
  {cont__6_3, &frame__6_2, 65, 65, 46, 46},
  {entry__6_1_types__generic_table_union, NULL, 65, 65, 3, 46},
  {cont__6_4, &frame__6_1_types__generic_table_union, },
  {entry__7_3, NULL, 75, 75, 30, 56},
  {cont__7_4, &frame__7_3, 75, 75, 30, 44},
  {cont__7_5, &frame__7_3, 75, 75, 56, 56},
  {entry__7_1_types__generic_table_map, NULL, 74, 74, 3, 40},
  {cont__7_2, &frame__7_1_types__generic_table_map, 75, 75, 3, 56},
  {cont__7_6, &frame__7_1_types__generic_table_map, 76, 76, 3, 14},
  {entry__8_4, NULL, 87, 87, 28, 37},
  {cont__8_6, &frame__8_4, 87, 87, 21, 37},
  {entry__8_8, NULL, 93, 93, 14, 21},
  {cont__8_9, &frame__8_8, 93, 93, 7, 22},
  {cont__8_10, &frame__8_8, 94, 94, 21, 28},
  {cont__8_11, &frame__8_8, 94, 94, 7, 29},
  {cont__8_12, &frame__8_8, 96, 96, 23, 30},
  {cont__8_13, &frame__8_8, 96, 96, 7, 31},
  {cont__8_14, &frame__8_8, 90, 96, 5, 31},
  {cont__8_16, &frame__8_8, 96, 96, 32, 32},
  {entry__8_1_types__generic_table_serialize, NULL, 86, 86, 3, 33},
  {cont__8_2, &frame__8_1_types__generic_table_serialize, 87, 87, 6, 18},
  {cont__8_3, &frame__8_1_types__generic_table_serialize, 87, 87, 3, 37},
  {cont__8_7, &frame__8_1_types__generic_table_serialize, 89, 96, 3, 32},
  {cont__8_17, &frame__8_1_types__generic_table_serialize, 97, 97, 3, 8},
  {entry__9_2, NULL, 106, 106, 31, 44},
  {cont__9_3, &frame__9_2, 106, 106, 44, 44},
  {entry__9_1_types__generic_table_keys_of, NULL, 106, 106, 3, 44},
  {cont__9_4, &frame__9_1_types__generic_table_keys_of, 107, 107, 3, 9},
  {entry__10_2, NULL, 116, 116, 31, 48},
  {cont__10_3, &frame__10_2, 116, 116, 48, 48},
  {entry__10_1_types__generic_table_values_of, NULL, 116, 116, 3, 48},
  {cont__10_4, &frame__10_1_types__generic_table_values_of, 117, 117, 3, 11},
  {entry__11_1_types__generic_table_is_empty, NULL, 125, 125, 6, 20},
  {cont__11_2, &frame__11_1_types__generic_table_is_empty, 125, 125, 6, 25},
  {cont__11_3, &frame__11_1_types__generic_table_is_empty, 125, 125, 3, 25},
  {entry__18_2, NULL, 157, 157, 24, 64},
  {cont__18_3, &frame__18_2, 157, 157, 29, 44},
  {cont__18_4, &frame__18_2, 157, 157, 24, 45},
  {cont__18_5, &frame__18_2, 157, 157, 64, 64},
  {entry__18_1_std__table, NULL, 157, 157, 3, 64},
  {cont__18_6, &frame__18_1_std__table, 158, 158, 3, 8},
  {entry__19_3_invalid_table_error, NULL, 174, 174, 13, 72},
  {cont__19_6, &frame__19_3_invalid_table_error, 174, 174, 7, 72},
  {entry__19_8, NULL, 176, 176, 53, 53},
  {cont__19_9, &frame__19_8, 176, 176, 39, 54},
  {cont__19_10, &frame__19_8, 176, 176, 32, 66},
  {entry__19_19, NULL, 180, 180, 34, 40},
  {cont__19_20, &frame__19_19, 180, 180, 34, 50},
  {cont__19_21, &frame__19_19, 180, 180, 34, 50},
  {cont__19_22, &frame__19_19, 180, 180, 34, 50},
  {entry__19_24, NULL, 180, 180, 53, 67},
  {entry__19_29, NULL, 182, 182, 33, 47},
  {entry__19_36, NULL, 185, 185, 40, 46},
  {cont__19_37, &frame__19_36, 185, 185, 40, 53},
  {cont__19_38, &frame__19_36, 185, 185, 40, 53},
  {entry__19_40, NULL, 185, 185, 71, 71},
  {cont__19_41, &frame__19_40, 185, 185, 56, 71},
  {cont__19_42, &frame__19_40, 185, 185, 71, 71},
  {entry__19_32, NULL, 185, 185, 16, 30},
  {cont__19_33, &frame__19_32, 185, 185, 16, 35},
  {cont__19_34, &frame__19_32, 185, 185, 16, 35},
  {cont__19_35, &frame__19_32, 185, 185, 16, 53},
  {cont__19_39, &frame__19_32, 185, 185, 13, 71},
  {entry__19_46, NULL, 186, 186, 34, 40},
  {cont__19_47, &frame__19_46, 186, 186, 34, 47},
  {cont__19_48, &frame__19_46, 186, 186, 34, 47},
  {cont__19_49, &frame__19_46, 186, 186, 34, 47},
  {entry__19_16, NULL, 180, 180, 10, 24},
  {cont__19_17, &frame__19_16, 180, 180, 10, 29},
  {cont__19_18, &frame__19_16, 180, 180, 10, 50},
  {cont__19_23, &frame__19_16, 180, 180, 7, 67},
  {cont__19_25, &frame__19_16, 181, 181, 7, 61},
  {cont__19_26, &frame__19_16, 182, 182, 10, 30},
  {cont__19_27, &frame__19_16, 182, 182, 10, 30},
  {cont__19_28, &frame__19_16, 182, 182, 7, 47},
  {cont__19_30, &frame__19_16, 184, 184, 7, 41},
  {cont__19_31, &frame__19_16, 185, 185, 7, 71},
  {cont__19_43, &frame__19_16, 186, 186, 10, 24},
  {cont__19_44, &frame__19_16, 186, 186, 10, 29},
  {cont__19_45, &frame__19_16, 186, 186, 10, 47},
  {cont__19_50, &frame__19_16, 186, 186, 7, 67},
  {cont__19_51, &frame__19_16, 187, 187, 22, 22},
  {cont__19_52, &frame__19_16, 187, 187, 7, 22},
  {cont__19_53, &frame__19_16, 188, 188, 7, 43},
  {cont__19_54, &frame__19_16, 189, 189, 7, 15},
  {cont__19_55, &frame__19_16, 189, 189, 21, 21},
  {entry__19_2, NULL, 176, 176, 8, 29},
  {cont__19_7, &frame__19_2, 176, 176, 5, 66},
  {cont__19_11, &frame__19_2, 177, 177, 8, 14},
  {cont__19_12, &frame__19_2, 177, 177, 8, 24},
  {cont__19_13, &frame__19_2, 177, 177, 8, 24},
  {cont__19_14, &frame__19_2, 177, 177, 5, 44},
  {cont__19_15, &frame__19_2, 179, 189, 5, 21},
  {cont__19_56, &frame__19_2, 189, 189, 21, 21},
  {entry__19_1_std__register_collection_serializer, NULL, 167, 189, 3, 22}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__private__set_item(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__private__set_item);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__private__set_item, attr);
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
static void type__private__get_item(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__private__get_item);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__private__get_item, attr);
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
static void type__std__is_a_table(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_table);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_table, attr);
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
static NODE *character__10;
static NODE *number__0;
static NODE *number__3;
static NODE *number__4;
static NODE *character__32;
static NODE *character__61;
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__table",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/table.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__table(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 38: $types::generic_table types::object
  initialize_maybe_future(var.types__generic_table, get__types__object());
  // 131: $types::table types::unordered_table
  initialize_maybe_future(var.types__table, get__types__unordered_table());
  // 191: register_collection_serializer "table" empty_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__16_1;
  arguments->slots[1] = get__empty_table();
  result_count = 0;
  myself = get__register_collection_serializer();
  func = myself->type;
  frame->cont = cont__40_1;
}
static void cont__40_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_3(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // myself: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 54: private::get_item myself key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = frame->caller_result_count;
  myself = var.private__get_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__5_4(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // myself: 0
  // key: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: private::set_item myself key value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[2] /* value */;
  result_count = frame->caller_result_count;
  myself = var.private__set_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__5_1_types__generic_table_(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // key: 0
  // value: 1
  // myself: 2
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
  frame->slots[2] /* myself */ = myself;
  // 53: NONE == value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[1] /* value */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 53: ... :
  // 54:   private::get_item myself key
  frame->slots[4] /* temp__2 */ = create_closure(entry__5_3, 0);
  // 55: :
  // 56:   private::set_item myself key value
  frame->slots[5] /* temp__3 */ = create_closure(entry__5_4, 0);
  // 52: if
  // 53:   NONE == value:
  // 54:     private::get_item myself key
  // 55:   :
  // 56:     private::set_item myself key value
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
static void entry__6_1_types__generic_table_union(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* left */ = create_cell_with_contents(arguments->slots[0]);
  // 65: ... : (key value) !left(key) value
  frame->slots[2] /* temp__1 */ = create_closure(entry__6_2, 2);
  // 65: for_each right: (key value) !left(key) value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__6_4;
}
static void entry__6_2(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // key: 0
  // value: 1
  // left: 2
  frame->slots[2] = myself->closure.frame->slots[0]; /* left */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 65: ... !left(key) value
  frame->slots[3] /* temp__1 */ = frame->slots[1] /* value */;
  // 65: ... !left(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* left */;
  func = myself->type;
  frame->cont = cont__6_3;
}
static void cont__6_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* left */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_4(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_1_types__generic_table_map(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // func: 1
  // new_table: 2
  frame->slots[2] /* new_table */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 74: $$new_table new_empty_collection(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__new_empty_collection();
  func = myself->type;
  frame->cont = cont__7_2;
}
static void cont__7_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* new_table */ = arguments->slots[0];
  // 75: ... : (key value) !new_table(key) func(value)
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_3, 2);
  // 75: for_each self: (key value) !new_table(key) func(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_6;
}
static void entry__7_3(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // key: 0
  // value: 1
  // new_table: 2
  // func: 3
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_table */
  frame->slots[3] = myself->closure.frame->slots[1]; /* func */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 75: ... !new_table(key) func(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  result_count = 1;
  myself = frame->slots[3] /* func */;
  func = myself->type;
  frame->cont = cont__7_4;
}
static void cont__7_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 75: ... !new_table(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* new_table */;
  func = myself->type;
  frame->cont = cont__7_5;
}
static void cont__7_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* new_table */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 76: -> new_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_table */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_1_types__generic_table_serialize(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // self: 0
  // indent: 1
  // return: 2
  // tag: 3
  // buf: 4
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* tag */ = create_future();
  frame->slots[4] /* buf */ = create_cell();
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
  // 86: $tag serialization_tag_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__serialization_tag_of();
  func = myself->type;
  frame->cont = cont__8_2;
}
static void cont__8_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* tag */, arguments->slots[0]);
  // 87: ... self.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__8_3;
}
static void cont__8_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 87: ... : return "@(tag)()"
  frame->slots[6] /* temp__2 */ = create_closure(entry__8_4, 0);
  // 87: if self.is_empty: return "@(tag)()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__8_7;
}
static void entry__8_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // tag: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* tag */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: ... "@(tag)()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* tag */;
  arguments->slots[1] = string__8_5;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__8_6;
}
static void cont__8_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 87: ... return "@(tag)()"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 88: $$buf tag
  ((CELL *)frame->slots[4])->contents /* buf */ = frame->slots[3] /* tag */;
  // 89: ... : (key value)
  // 90:   write_to
  // 91:     &buf
  // 92:     '@nl;'
  // 93:     spaces(indent+2)
  // 94:     serialize(key indent+2)
  // 95:     " = "
  // 96:     serialize(value indent+4)
  frame->slots[5] /* temp__1 */ = create_closure(entry__8_8, 2);
  // 89: for_each self: (key value)
  // 90:   write_to
  // 91:     &buf
  // 92:     '@nl;'
  // 93:     spaces(indent+2)
  // 94:     serialize(key indent+2)
  // 95:     " = "
  // 96:     serialize(value indent+4)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__8_17;
}
static void entry__8_8(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // key: 0
  // value: 1
  // buf: 2
  // indent: 3
  frame->slots[2] = myself->closure.frame->slots[4]; /* buf */
  frame->slots[3] = myself->closure.frame->slots[1]; /* indent */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 93: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_9;
}
static void cont__8_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 93: spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__8_10;
}
static void cont__8_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 94: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_11;
}
static void cont__8_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 94: serialize(key indent+2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__8_12;
}
static void cont__8_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 96: ... indent+4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* indent */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_13;
}
static void cont__8_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 96: serialize(value indent+4)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__8_14;
}
static void cont__8_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 90: write_to
  // 91:   &buf
  // 92:   '@nl;'
  // 93:   spaces(indent+2)
  // 94:   serialize(key indent+2)
  // 95:   " = "
  // 96:   serialize(value indent+4)
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = character__10;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  arguments->slots[3] = frame->slots[6] /* temp__3 */;
  arguments->slots[4] = string__8_15;
  arguments->slots[5] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__8_16;
}
static void cont__8_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 97: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* buf */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__9_1_types__generic_table_keys_of(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // keys: 1
  frame->slots[1] /* keys */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 105: $$keys empty_list
  ((CELL *)frame->slots[1])->contents /* keys */ = get__empty_list();
  // 106: ... : (key _value) push &keys key
  frame->slots[2] /* temp__1 */ = create_closure(entry__9_2, 2);
  // 106: for_each self: (key _value) push &keys key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__9_4;
}
static void entry__9_2(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // key: 0
  // value: 1
  // keys: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* keys */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 106: ... push &keys key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* keys */;
  arguments->slots[1] = frame->slots[0] /* key */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* keys */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 107: -> keys
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* keys */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_1_types__generic_table_values_of(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // values: 1
  frame->slots[1] /* values */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 115: $$values empty_list
  ((CELL *)frame->slots[1])->contents /* values */ = get__empty_list();
  // 116: ... : (_key value) push &values value
  frame->slots[2] /* temp__1 */ = create_closure(entry__10_2, 2);
  // 116: for_each self: (_key value) push &values value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void entry__10_2(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // key: 0
  // value: 1
  // values: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* values */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 116: ... push &values value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* values */;
  arguments->slots[1] = frame->slots[1] /* value */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__10_3;
}
static void cont__10_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* values */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 117: -> values
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* values */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_1_types__generic_table_is_empty(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 125: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__11_2;
}
static void cont__11_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 125: ... length_of(self) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 125: -> length_of(self) == 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1_std__table(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  // tab: 1
  frame->slots[1] /* tab */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 156: $$tab types::table
  ((CELL *)frame->slots[1])->contents /* tab */ = var.types__table;
  // 157: ... : (arg) !tab(std::key_of(arg)) std::value_of(arg)
  frame->slots[2] /* temp__1 */ = create_closure(entry__18_2, 1);
  // 157: for_each args: (arg) !tab(std::key_of(arg)) std::value_of(arg)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__18_6;
}
static void entry__18_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // arg: 0
  // tab: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* tab */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 157: ... !tab(std::key_of(arg)) std::value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__18_3;
}
static void cont__18_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 157: ... std::key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__std__key_of();
  func = myself->type;
  frame->cont = cont__18_4;
}
static void cont__18_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 157: ... !tab(std::key_of(arg))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* tab */;
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
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
static void cont__18_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 158: -> tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* tab */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_2(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // text: 0
  // base_indent: 1
  // return: 2
  // name: 3
  // empty_collection: 4
  // invalid_table_error: 5
  // obj: 6
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] = myself->closure.frame->slots[0]; /* name */
  frame->slots[4] = myself->closure.frame->slots[1]; /* empty_collection */
  frame->slots[5] /* invalid_table_error */ = create_future();
  frame->slots[6] /* obj */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 173: ... :
  // 174:   raise "Invalid @(name) object encountered during deserialisation!"
  frame->slots[7] /* temp__1 */ = create_closure(entry__19_3_invalid_table_error, 0);
  // 173: $invalid_table_error:
  // 174:   raise "Invalid @(name) object encountered during deserialisation!"
  initialize_future(frame->slots[5] /* invalid_table_error */, frame->slots[7] /* temp__1 */);
  // 176: ... text .has_prefix. "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = string__8_5;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__19_7;
}
static void entry__19_3_invalid_table_error(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... "Invalid @(name) object encountered during deserialisation!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__19_4;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__19_5;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__19_6;
}
static void cont__19_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: raise "Invalid @(name) object encountered during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__19_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 176: ... : return range(text 3 -1) empty_table
  frame->slots[8] /* temp__2 */ = create_closure(entry__19_8, 0);
  // 176: if text .has_prefix. "()": return range(text 3 -1) empty_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_11;
}
static void entry__19_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // return: 0
  // text: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__19_9;
}
static void cont__19_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 176: ... range(text 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__19_10;
}
static void cont__19_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 176: ... return range(text 3 -1) empty_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__empty_table();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__19_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__19_12;
}
static void cont__19_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 177: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_13;
}
static void cont__19_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 177: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_14;
}
static void cont__19_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 177: if text(1) != '@nl;' invalid_table_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* invalid_table_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_15;
}
static void cont__19_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 178: $$obj empty_collection
  ((CELL *)frame->slots[6])->contents /* obj */ = frame->slots[4] /* empty_collection */;
  // 179: ... :
  // 180:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 181:   get_deserialization_indent $remaining_text $indent text
  // 182:   if indent <= base_indent: return text obj
  // 183:   !text remaining_text
  // 184:   $key deserialize_item(&text indent)
  // 185:   while -> length_of(text) >= 1 && text(1) == ' ': range &text 2 -1
  // 186:   if length_of(text) == 0 || text(1) != '=' invalid_table_error
  // 187:   range &text 2 -1
  // 188:   $value deserialize_item(&text indent)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__19_16, 0);
  // 179: forever:
  // 180:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 181:   get_deserialization_indent $remaining_text $indent text
  // 182:   if indent <= base_indent: return text obj
  // 183:   !text remaining_text
  // 184:   $key deserialize_item(&text indent)
  // 185:   while -> length_of(text) >= 1 && text(1) == ' ': range &text 2 -1
  // 186:   if length_of(text) == 0 || text(1) != '=' invalid_table_error
  // 187:   range &text 2 -1
  // 188:   $value deserialize_item(&text indent)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__19_56;
}
static void entry__19_16(void) {
  allocate_initialized_frame_gc(5, 14);
  // slot allocations:
  // text: 0
  // return: 1
  // obj: 2
  // base_indent: 3
  // invalid_table_error: 4
  // remaining_text: 5
  // indent: 6
  // key: 7
  // value: 8
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  frame->slots[2] = myself->closure.frame->slots[6]; /* obj */
  frame->slots[3] = myself->closure.frame->slots[1]; /* base_indent */
  frame->slots[4] = myself->closure.frame->slots[5]; /* invalid_table_error */
  frame->slots[5] /* remaining_text */ = create_future();
  frame->slots[6] /* indent */ = create_future();
  frame->slots[7] /* key */ = create_future();
  frame->slots[8] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__19_17;
}
static void cont__19_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 180: ... length_of(text) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_18;
}
static void cont__19_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 180: ... text(1) != '@nl;'
  frame->slots[12] /* temp__4 */ = create_closure(entry__19_19, 0);
  // 180: ... length_of(text) == 0 || text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__19_23;
}
static void entry__19_19(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__19_20;
}
static void cont__19_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 180: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_21;
}
static void cont__19_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_22;
}
static void cont__19_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 180: ... : return text obj
  frame->slots[13] /* temp__5 */ = create_closure(entry__19_24, 0);
  // 180: if length_of(text) == 0 || text(1) != '@nl;': return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_25;
}
static void entry__19_24(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // text: 1
  // obj: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* obj */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__19_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 181: get_deserialization_indent $remaining_text $indent text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 2;
  myself = get__get_deserialization_indent();
  func = myself->type;
  frame->cont = cont__19_26;
}
static void cont__19_26(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  frame->slots[10] /* temp__2 */ = arguments->slots[1];
  // 181: ... remaining_text
  initialize_future(frame->slots[5] /* remaining_text */, frame->slots[9] /* temp__1 */);
  // 181: ... indent
  initialize_future(frame->slots[6] /* indent */, frame->slots[10] /* temp__2 */);
  // 182: ... indent <= base_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base_indent */;
  arguments->slots[1] = frame->slots[6] /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__19_27;
}
static void cont__19_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 182: ... indent <= base_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_28;
}
static void cont__19_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 182: ... : return text obj
  frame->slots[11] /* temp__3 */ = create_closure(entry__19_29, 0);
  // 182: if indent <= base_indent: return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_30;
}
static void entry__19_29(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // text: 1
  // obj: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* obj */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 182: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__19_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 183: !text remaining_text
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[5] /* remaining_text */;
  // 184: $key deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[6] /* indent */;
  result_count = 2;
  myself = get__deserialize_item();
  func = myself->type;
  frame->cont = cont__19_31;
}
static void cont__19_31(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[9] /* temp__1 */ = arguments->slots[1];
  // 184: ... key
  initialize_future(frame->slots[7] /* key */, frame->slots[9] /* temp__1 */);
  // 185: ... -> length_of(text) >= 1 && text(1) == ' ': range &text 2 -1
  frame->slots[9] /* temp__1 */ = create_closure(entry__19_32, 0);
  // 185: while -> length_of(text) >= 1 && text(1) == ' ': range &text 2 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__19_43;
}
static void entry__19_40(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__19_41;
}
static void cont__19_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 185: ... range &text 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__19_42;
}
static void cont__19_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_32(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__19_33;
}
static void cont__19_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 185: ... length_of(text) >= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__19_34;
}
static void cont__19_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 185: ... length_of(text) >= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_35;
}
static void cont__19_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 185: ... text(1) == ' '
  frame->slots[5] /* temp__5 */ = create_closure(entry__19_36, 0);
  // 185: ... length_of(text) >= 1 && text(1) == ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__19_39;
}
static void entry__19_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__19_37;
}
static void cont__19_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 185: ... text(1) == ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_38;
}
static void cont__19_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 185: ... text(1) == ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 185: ... : range &text 2 -1
  frame->slots[6] /* temp__6 */ = create_closure(entry__19_40, 0);
  // 185: ... -> length_of(text) >= 1 && text(1) == ' ': range &text 2 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 186: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__19_44;
}
static void cont__19_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 186: ... length_of(text) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_45;
}
static void cont__19_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 186: ... text(1) != '='
  frame->slots[12] /* temp__4 */ = create_closure(entry__19_46, 0);
  // 186: ... length_of(text) == 0 || text(1) != '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__19_50;
}
static void entry__19_46(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__19_47;
}
static void cont__19_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 186: ... text(1) != '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_48;
}
static void cont__19_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 186: ... text(1) != '='
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_49;
}
static void cont__19_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 186: ... text(1) != '='
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 186: if length_of(text) == 0 || text(1) != '=' invalid_table_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* invalid_table_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_51;
}
static void cont__19_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 187: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__19_52;
}
static void cont__19_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 187: range &text 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__19_53;
}
static void cont__19_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 188: $value deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[6] /* indent */;
  result_count = 2;
  myself = get__deserialize_item();
  func = myself->type;
  frame->cont = cont__19_54;
}
static void cont__19_54(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[9] /* temp__1 */ = arguments->slots[1];
  // 188: ... value
  initialize_future(frame->slots[8] /* value */, frame->slots[9] /* temp__1 */);
  // 189: !obj(key) value
  frame->slots[9] /* temp__1 */ = frame->slots[8] /* value */;
  // 189: !obj(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* key */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* obj */;
  func = myself->type;
  frame->cont = cont__19_55;
}
static void cont__19_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* obj */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_56(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__19_1_std__register_collection_serializer(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // empty_collection: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 167: ... :
  // 168:   (
  // 169:     $text
  // 170:     base_indent
  // 171:     -> return
  // 172:   )
  // 173:   $invalid_table_error:
  // 174:     raise "Invalid @(name) object encountered during deserialisation!"
  // 175:   
  // 176:   if text .has_prefix. "()": return range(text 3 -1) empty_table
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__19_2, 2);
  // 167: register_deserializer name:
  // 168:   (
  // 169:     $text
  // 170:     base_indent
  // 171:     -> return
  // 172:   )
  // 173:   $invalid_table_error:
  // 174:     raise "Invalid @(name) object encountered during deserialisation!"
  // 175:   
  // 176:   if text .has_prefix. "()": return range(text 3 -1) empty_table
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__register_deserializer();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__types__table(void) {
  var.private__set_item = collect_node(var.private__set_item);
  var.private__get_item = collect_node(var.private__get_item);
  var.types__generic_table = collect_node(var.types__generic_table);
  var._NONE = collect_node(var._NONE);
  var.std__is_a_table = collect_node(var.std__is_a_table);
  var.types__table = collect_node(var.types__table);
  var.std__empty_table = collect_node(var.std__empty_table);
  var.std__table = collect_node(var.std__table);
  var.std__register_collection_serializer = collect_node(var.std__register_collection_serializer);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__table(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("private", "set_item", get__private__set_item, &poly_idx__private__set_item, &var.private__set_item);
  define_polymorphic_function("private", "get_item", get__private__get_item, &poly_idx__private__get_item, &var.private__get_item);
  define_polymorphic_function("std", "is_a_table", get__std__is_a_table, &poly_idx__std__is_a_table, &var.std__is_a_table);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__table(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__10 = from_uchar32(10);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__4 = from_uint32(4U);
  character__32 = from_uchar32(32);
  character__61 = from_uchar32(61);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  unique__NONE = register_unique_item("NONE");
  func__6_1_types__generic_table_union = create_function(entry__6_1_types__generic_table_union, 2);
  func__7_1_types__generic_table_map = create_function(entry__7_1_types__generic_table_map, 2);
  string__8_5 = from_latin_1_string("()", 2);
  string__8_15 = from_latin_1_string(" = ", 3);
  func__8_1_types__generic_table_serialize = create_function(entry__8_1_types__generic_table_serialize, -1);
  func__9_1_types__generic_table_keys_of = create_function(entry__9_1_types__generic_table_keys_of, 1);
  func__10_1_types__generic_table_values_of = create_function(entry__10_1_types__generic_table_values_of, 1);
  func__11_1_types__generic_table_is_empty = create_function(entry__11_1_types__generic_table_is_empty, 1);
  string__16_1 = from_latin_1_string("table", 5);
  func__18_1_std__table = create_function(entry__18_1_std__table, -1);
  string__19_4 = from_latin_1_string("Invalid ", 8);
  string__19_5 = from_latin_1_string(" object encountered during deserialisation!", 43);
  func__19_1_std__register_collection_serializer = create_function(entry__19_1_std__register_collection_serializer, 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__table(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__table");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("types", "generic_table", get__types__generic_table, &var.types__generic_table);
  assign_value(&var._NONE, unique__NONE);
  define_single_assign_static("types", "table", get__types__table, &var.types__table);
  define_single_assign_static("std", "empty_table", get__std__empty_table, &var.std__empty_table);
  define_single_assign_static("std", "table", get__std__table, &var.std__table);
  define_single_assign_static("std", "register_collection_serializer", get__std__register_collection_serializer, &var.std__register_collection_serializer);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__table(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__table");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "deserialize_item", &get__deserialize_item, &get_value_or_future__deserialize_item);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "get_deserialization_indent", &get__get_deserialization_indent, &get_value_or_future__get_deserialization_indent);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "is_a_table", &get__is_a_table, &poly_idx__is_a_table);
  use_polymorphic_function(NULL, "is_empty", &get__is_empty, &poly_idx__is_empty);
  use_polymorphic_function(NULL, "keys_of", &get__keys_of, &poly_idx__keys_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_polymorphic_function(NULL, "map", &get__map, &poly_idx__map);
  use_read_only(NULL, "new_empty_collection", &get__new_empty_collection, &get_value_or_future__new_empty_collection);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "raise", &get__raise, &get_value_or_future__raise);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "register_collection_serializer", &get__register_collection_serializer, &get_value_or_future__register_collection_serializer);
  use_read_only(NULL, "register_deserializer", &get__register_deserializer, &get_value_or_future__register_deserializer);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_polymorphic_function(NULL, "serialize", &get__serialize, &poly_idx__serialize);
  use_read_only(NULL, "spaces", &get__spaces, &get_value_or_future__spaces);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_of", &get__std__key_of, &get_value_or_future__std__key_of);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only("std", "value_of", &get__std__value_of, &get_value_or_future__std__value_of);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only("types", "unordered_table", &get__types__unordered_table, &get_value_or_future__types__unordered_table);
  use_polymorphic_function(NULL, "union", &get__union, &poly_idx__union);
  use_polymorphic_function(NULL, "values_of", &get__values_of, &poly_idx__values_of);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
  define_type_function("types", "generic_table", entry__5_1_types__generic_table_, -1);
  define_method("types", "generic_table", poly_idx__union, func__6_1_types__generic_table_union);
  define_method("types", "generic_table", poly_idx__map, func__7_1_types__generic_table_map);
  define_method("types", "generic_table", poly_idx__serialize, func__8_1_types__generic_table_serialize);
  define_method("types", "generic_table", poly_idx__keys_of, func__9_1_types__generic_table_keys_of);
  define_method("types", "generic_table", poly_idx__values_of, func__10_1_types__generic_table_values_of);
  define_method("types", "generic_table", poly_idx__is_empty, func__11_1_types__generic_table_is_empty);
  define_attribute("types", "object", poly_idx__is_a_table, get__false());
  define_attribute("types", "generic_table", poly_idx__is_a_table, get__true());
  define_attribute("types", "table", poly_idx__serialization_tag_of, string__16_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__table(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.private__set_item, create_function(type__private__set_item, -1));
  assign_value(&var.private__get_item, create_function(type__private__get_item, -1));
  assign_value(&var.types__generic_table, get__types__object());
  assign_value(&var.std__is_a_table, create_function(type__std__is_a_table, -1));
  assign_value(&var.types__table, get__types__unordered_table());
  assign_variable(&var.std__empty_table, &var.types__table);
  assign_variable(&var.std__table, &func__18_1_std__table);
  assign_variable(&var.std__register_collection_serializer, &func__19_1_std__register_collection_serializer);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__table(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__table);
}
