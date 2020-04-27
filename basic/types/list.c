#include <string.h>
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
REGISTER NODE *myself ASM("r13");
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
IMPORT int result_count;
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
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
IMPORT void *allocate(long size);
IMPORT NODE *collect_node(NODE *node);
IMPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT void invalid_index_error(void);
IMPORT void *allocate_large(long size);
IMPORT NODE *from_long(long val);
IMPORT NODE *undefined;
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);
IMPORT const char *indent_to_string(int indent);
IMPORT int print(char **buf_p, const char *format, ...);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT void set_attribute(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_c_function(const char *name, void *func);
IMPORT NODE *from_uchar32(unsigned int chr);
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
static int poly_idx__append;
static NODE_GETTER get__append;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static int poly_idx__contains;
static NODE_GETTER get__contains;
static int poly_idx__delete_at;
static NODE_GETTER get__delete_at;
static NODE_GETTER get__deserialize_item;
static NODE_GETTER get_value_or_future__deserialize_item;
static NODE_GETTER get__div;
static NODE_GETTER get_value_or_future__div;
static int poly_idx__drop;
static NODE_GETTER get__drop;
static int poly_idx__dup;
static NODE_GETTER get__dup;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__filter;
static NODE_GETTER get__filter;
static int poly_idx__for_each;
static NODE_GETTER get__for_each;
static int poly_idx__for_each_from_down_to;
static NODE_GETTER get__for_each_from_down_to;
static int poly_idx__for_each_from_to;
static NODE_GETTER get__for_each_from_to;
static int poly_idx__for_each_pair;
static NODE_GETTER get__for_each_pair;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__from_to;
static NODE_GETTER get_value_or_future__from_to;
static int poly_idx__get;
static NODE_GETTER get__get;
static NODE_GETTER get__get_deserialization_indent;
static NODE_GETTER get_value_or_future__get_deserialization_indent;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__interleave;
static NODE_GETTER get__interleave;
static int poly_idx__is_a_list;
static NODE_GETTER get__is_a_list;
static int poly_idx__is_a_sequence;
static NODE_GETTER get__is_a_sequence;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static int poly_idx__is_empty;
static NODE_GETTER get__is_empty;
static NODE_GETTER get__is_odd;
static NODE_GETTER get_value_or_future__is_odd;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static int poly_idx__length_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static int poly_idx__map;
static NODE_GETTER get__map;
static int poly_idx__merge;
static NODE_GETTER get__merge;
static NODE_GETTER get__minus;
static NODE_GETTER get_value_or_future__minus;
static int poly_idx__new_empty_collection;
static NODE_GETTER get__new_empty_collection;
static NODE_GETTER get__normalized_index;
static NODE_GETTER get_value_or_future__normalized_index;
static NODE_GETTER get__not;
static NODE_GETTER get_value_or_future__not;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static int poly_idx__peek;
static NODE_GETTER get__peek;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static int poly_idx__pop;
static NODE_GETTER get__pop;
static int poly_idx__push;
static NODE_GETTER get__push;
static int poly_idx__put;
static NODE_GETTER get__put;
static NODE_GETTER get__raise;
static NODE_GETTER get_value_or_future__raise;
static int poly_idx__range;
static NODE_GETTER get__range;
static NODE_GETTER get__register_deserializer;
static NODE_GETTER get_value_or_future__register_deserializer;
static int poly_idx__serialize;
static NODE_GETTER get__serialize;
static int poly_idx__sort;
static NODE_GETTER get__sort;
static NODE_GETTER get__spaces;
static NODE_GETTER get_value_or_future__spaces;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static int poly_idx__to_list;
static NODE_GETTER get__to_list;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static int poly_idx__update_each;
static NODE_GETTER get__update_each;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static struct {
  NODE *std__is_a_list;
  NODE *types__generic_list;
  NODE *types__list;
  NODE *std__empty_list;
  NODE *std__list;
  NODE *std__normalized_index;
  NODE *std__is_a_sequence;
  NODE *std__sequence;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__is_a_list;
static void type__std__is_a_list(void);
static NODE *get__std__is_a_list(void) {
  return var.std__is_a_list;
}
static NODE *get__types__generic_list(void) {
  return var.types__generic_list;
}
static NODE *create__types__generic_list();

typedef struct LIST_DATA LIST_DATA;
struct LIST_DATA {
  long size;
  long length;
  NODE **items;
};

static LIST_DATA *collect_list_data(LIST_DATA *data);

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  long length;
  LIST_DATA *data;
} LIST;
static NODE *get__types__list(void) {
  return var.types__list;
}
extern NODE *create__types__list(long length, LIST_DATA *data);
static NODE *get__std__empty_list(void) {
  return var.std__empty_list;
}

static void func__types__list___unfold(NODE *list);

static long func__types__list___length_of(NODE *node);

static NODE *func__types__list___get_item_of(NODE *node, long idx);
static NODE *func__14_1_types__list_to_list;
static void entry__14_1_types__list_to_list(void);
static FRAME_INFO frame__14_1_types__list_to_list = {1, {"self"}};
static void entry__15_1_std__list(void);
static NODE *func__15_1_std__list;
static NODE *get__std__list(void) {
  return var.std__list;
}
static void entry__16_1_types__list_length_of(void);
static NODE *func__16_1_types__list_length_of;
static void entry__17_1_types__list_push(void);
static NODE *func__17_1_types__list_push;
static void entry__18_1_types__list_drop(void);
static NODE *func__18_1_types__list_drop;
static void entry__19_1_types__list_pop(void);
static NODE *func__19_1_types__list_pop;
static void entry__20_1_types__list_peek(void);
static NODE *func__20_1_types__list_peek;
static void entry__21_1_types__list_append(void);
static NODE *func__21_1_types__list_append;
static void entry__22_1_types__list_range(void);
static NODE *func__22_1_types__list_range;
static NODE *func__23_1_types__generic_list_delete_at;
static void entry__23_1_types__generic_list_delete_at(void);
static FRAME_INFO frame__23_1_types__generic_list_delete_at = {3, {"self", "idx", "count"}};
static void cont__23_2(void);
static void cont__23_3(void);
static NODE *func__23_4;
static void entry__23_4(void);
static FRAME_INFO frame__23_4 = {3, {"self", "idx", "count"}};
static void cont__23_5(void);
static void cont__23_6(void);
static void cont__23_7(void);
static void cont__23_8(void);
static void cont__23_9(void);
static void cont__23_10(void);
static void cont__23_11(void);
static NODE *func__24_1_std__normalized_index;
static void entry__24_1_std__normalized_index(void);
static FRAME_INFO frame__24_1_std__normalized_index = {3, {"self", "idx", "return"}};
static void cont__24_2(void);
static void cont__24_3(void);
static NODE *func__24_4;
static void entry__24_4(void);
static FRAME_INFO frame__24_4 = {2, {"return", "idx"}};
static NODE *func__24_5;
static void entry__24_5(void);
static FRAME_INFO frame__24_5 = {3, {"return", "self", "idx"}};
static void cont__24_6(void);
static void cont__24_7(void);
static void cont__24_8(void);
static void cont__24_9(void);
static NODE *get__std__normalized_index(void) {
  return var.std__normalized_index;
}
static NODE *func__25_1_types__generic_list_is_empty;
static void entry__25_1_types__generic_list_is_empty(void);
static FRAME_INFO frame__25_1_types__generic_list_is_empty = {1, {"self"}};
static void cont__25_2(void);
static void cont__25_3(void);
static NODE *func__26_1_types__generic_list_for_each_from_to;
static void entry__26_1_types__generic_list_for_each_from_to(void);
static FRAME_INFO frame__26_1_types__generic_list_for_each_from_to = {7, {"self", "first", "last", "body", "body2", "i", "n"}};
static void cont__26_2(void);
static void cont__26_3(void);
static NODE *func__26_4;
static void entry__26_4(void);
static FRAME_INFO frame__26_4 = {5, {"n", "i", "body", "self", "body2"}};
static void cont__26_5(void);
static void cont__26_6(void);
static NODE *func__26_7;
static void entry__26_7(void);
static FRAME_INFO frame__26_7 = {5, {"body", "i", "self", "body2", "n"}};
static void cont__26_8(void);
static void cont__26_9(void);
static NODE *func__26_10;
static void entry__26_10(void);
static FRAME_INFO frame__26_10 = {3, {"body", "i", "self"}};
static void cont__26_11(void);
static NODE *func__26_12;
static void entry__26_12(void);
static FRAME_INFO frame__26_12 = {3, {"body", "self", "i"}};
static void cont__26_13(void);
static void cont__26_14(void);
static void cont__26_15(void);
static NODE *func__26_16;
static void entry__26_16(void);
static FRAME_INFO frame__26_16 = {2, {"i", "n"}};
static void cont__26_17(void);
static void cont__26_18(void);
static NODE *func__26_19;
static void entry__26_19(void);
static FRAME_INFO frame__26_19 = {1, {"body2"}};
static void cont__26_20(void);
static void cont__26_21(void);
static NODE *func__27_1_types__generic_list_for_each_from_down_to;
static void entry__27_1_types__generic_list_for_each_from_down_to(void);
static FRAME_INFO frame__27_1_types__generic_list_for_each_from_down_to = {7, {"self", "first", "last", "body", "body2", "i", "n"}};
static void cont__27_2(void);
static void cont__27_3(void);
static NODE *func__27_4;
static void entry__27_4(void);
static FRAME_INFO frame__27_4 = {5, {"i", "n", "body", "self", "body2"}};
static void cont__27_5(void);
static void cont__27_6(void);
static NODE *func__27_7;
static void entry__27_7(void);
static FRAME_INFO frame__27_7 = {5, {"body", "i", "self", "body2", "n"}};
static void cont__27_8(void);
static void cont__27_9(void);
static NODE *func__27_10;
static void entry__27_10(void);
static FRAME_INFO frame__27_10 = {3, {"body", "i", "self"}};
static void cont__27_11(void);
static NODE *func__27_12;
static void entry__27_12(void);
static FRAME_INFO frame__27_12 = {3, {"body", "self", "i"}};
static void cont__27_13(void);
static void cont__27_14(void);
static void cont__27_15(void);
static NODE *func__27_16;
static void entry__27_16(void);
static FRAME_INFO frame__27_16 = {2, {"i", "n"}};
static void cont__27_17(void);
static void cont__27_18(void);
static NODE *func__27_19;
static void entry__27_19(void);
static FRAME_INFO frame__27_19 = {1, {"body2"}};
static void cont__27_20(void);
static void cont__27_21(void);
static NODE *func__28_1_types__generic_list_for_each;
static void entry__28_1_types__generic_list_for_each(void);
static FRAME_INFO frame__28_1_types__generic_list_for_each = {5, {"self", "body", "body2", "i", "n"}};
static void cont__28_2(void);
static void cont__28_3(void);
static void cont__28_4(void);
static NODE *func__28_5;
static void entry__28_5(void);
static FRAME_INFO frame__28_5 = {5, {"n", "i", "body", "self", "body2"}};
static NODE *func__28_6;
static void entry__28_6(void);
static FRAME_INFO frame__28_6 = {5, {"n", "i", "body", "self", "body2"}};
static void cont__28_7(void);
static void cont__28_8(void);
static NODE *func__28_9;
static void entry__28_9(void);
static FRAME_INFO frame__28_9 = {5, {"body", "i", "self", "body2", "n"}};
static void cont__28_10(void);
static void cont__28_11(void);
static void cont__28_12(void);
static NODE *func__28_13;
static void entry__28_13(void);
static FRAME_INFO frame__28_13 = {2, {"i", "n"}};
static void cont__28_14(void);
static void cont__28_15(void);
static NODE *func__28_16;
static void entry__28_16(void);
static FRAME_INFO frame__28_16 = {1, {"body2"}};
static void cont__28_17(void);
static void cont__28_18(void);
static NODE *func__28_19;
static void entry__28_19(void);
static FRAME_INFO frame__28_19 = {5, {"n", "i", "body", "self", "body2"}};
static NODE *func__28_20;
static void entry__28_20(void);
static FRAME_INFO frame__28_20 = {5, {"n", "i", "body", "self", "body2"}};
static void cont__28_21(void);
static void cont__28_22(void);
static NODE *func__28_23;
static void entry__28_23(void);
static FRAME_INFO frame__28_23 = {5, {"body", "self", "i", "body2", "n"}};
static void cont__28_24(void);
static void cont__28_25(void);
static void cont__28_26(void);
static NODE *func__28_27;
static void entry__28_27(void);
static FRAME_INFO frame__28_27 = {2, {"i", "n"}};
static void cont__28_28(void);
static void cont__28_29(void);
static NODE *func__28_30;
static void entry__28_30(void);
static FRAME_INFO frame__28_30 = {1, {"body2"}};
static void cont__28_31(void);
static void cont__28_32(void);
static NODE *func__29_1_types__generic_list_update_each;
static void entry__29_1_types__generic_list_update_each(void);
static FRAME_INFO frame__29_1_types__generic_list_update_each = {7, {"self", "body", "return", "update_item", "i", "n", "new_list"}};
static NODE *func__29_2_update_item;
static void entry__29_2_update_item(void);
static FRAME_INFO frame__29_2_update_item = {3, {"new_item", "new_list", "i"}};
static void cont__29_3(void);
static NODE *func__29_4;
static void entry__29_4(void);
static FRAME_INFO frame__29_4 = {2, {"new_item", "new_list"}};
static void cont__29_5(void);
static NODE *func__29_6;
static void entry__29_6(void);
static FRAME_INFO frame__29_6 = {2, {"new_list", "new_item"}};
static void cont__29_7(void);
static NODE *func__29_8;
static void entry__29_8(void);
static FRAME_INFO frame__29_8 = {2, {"new_list", "new_item"}};
static void cont__29_9(void);
static void cont__29_10(void);
static void cont__29_11(void);
static void cont__29_12(void);
static void cont__29_13(void);
static void cont__29_14(void);
static NODE *func__29_15;
static void entry__29_15(void);
static FRAME_INFO frame__29_15 = {5, {"n", "i", "update_item", "body", "self"}};
static NODE *func__29_16;
static void entry__29_16(void);
static FRAME_INFO frame__29_16 = {5, {"n", "i", "update_item", "body", "self"}};
static void cont__29_17(void);
static void cont__29_18(void);
static NODE *func__29_19;
static void entry__29_19(void);
static FRAME_INFO frame__29_19 = {4, {"update_item", "body", "i", "self"}};
static void cont__29_20(void);
static void cont__29_21(void);
static NODE *func__29_22;
static void entry__29_22(void);
static FRAME_INFO frame__29_22 = {5, {"n", "i", "update_item", "body", "self"}};
static NODE *func__29_23;
static void entry__29_23(void);
static FRAME_INFO frame__29_23 = {5, {"n", "i", "update_item", "body", "self"}};
static void cont__29_24(void);
static void cont__29_25(void);
static NODE *func__29_26;
static void entry__29_26(void);
static FRAME_INFO frame__29_26 = {4, {"update_item", "body", "self", "i"}};
static void cont__29_27(void);
static void cont__29_28(void);
static void cont__29_29(void);
static void cont__29_30(void);
static NODE *func__30_1_types__list_for_each_pair;
static void entry__30_1_types__list_for_each_pair(void);
static FRAME_INFO frame__30_1_types__list_for_each_pair = {4, {"self", "body", "i", "n"}};
static void cont__30_2(void);
static NODE *func__30_3;
static void entry__30_3(void);
static FRAME_INFO frame__30_3 = {4, {"i", "n", "body", "self"}};
static void cont__30_4(void);
static NODE *func__30_5;
static void entry__30_5(void);
static FRAME_INFO frame__30_5 = {3, {"body", "self", "i"}};
static void cont__30_6(void);
static void cont__30_7(void);
static void cont__30_8(void);
static void cont__30_9(void);
static void cont__30_10(void);
static void cont__30_11(void);
static void cont__30_12(void);
static NODE *func__30_13;
static void entry__30_13(void);
static FRAME_INFO frame__30_13 = {3, {"body", "self", "i"}};
static void cont__30_14(void);
static NODE *func__31_1_types__generic_list_get;
static void entry__31_1_types__generic_list_get(void);
static FRAME_INFO frame__31_1_types__generic_list_get = {1, {"self"}};
static void cont__31_2(void);
static void cont__31_3(void);
static NODE *func__31_4;
static void entry__31_4(void);
static FRAME_INFO frame__31_4 = {0, {}};
static NODE *string__57ec57a17085427f;
static void cont__31_6(void);
static void cont__31_7(void);
static void cont__31_8(void);
static void cont__31_9(void);
static NODE *func__32_1_types__list_put;
static void entry__32_1_types__list_put(void);
static FRAME_INFO frame__32_1_types__list_put = {2, {"self", "item"}};
static void cont__32_2(void);
static void cont__32_3(void);
static NODE *func__33_1_types__list_merge;
static void entry__33_1_types__list_merge(void);
static FRAME_INFO frame__33_1_types__list_merge = {5, {"left", "right", "func", "return", "result"}};
static void cont__33_2(void);
static NODE *func__33_3;
static void entry__33_3(void);
static FRAME_INFO frame__33_3 = {5, {"left", "right", "func", "result", "return"}};
static void cont__33_4(void);
static void cont__33_5(void);
static NODE *func__33_6;
static void entry__33_6(void);
static FRAME_INFO frame__33_6 = {5, {"right", "func", "left", "result", "return"}};
static void cont__33_7(void);
static void cont__33_8(void);
static NODE *func__33_9;
static void entry__33_9(void);
static FRAME_INFO frame__33_9 = {4, {"func", "right", "left", "result"}};
static void cont__33_10(void);
static NODE *func__33_11;
static void entry__33_11(void);
static FRAME_INFO frame__33_11 = {2, {"right", "left"}};
static void cont__33_12(void);
static void cont__33_13(void);
static void cont__33_14(void);
static void cont__33_15(void);
static void cont__33_16(void);
static NODE *func__33_17;
static void entry__33_17(void);
static FRAME_INFO frame__33_17 = {3, {"func", "right", "left"}};
static void cont__33_18(void);
static NODE *func__33_19;
static void entry__33_19(void);
static FRAME_INFO frame__33_19 = {3, {"func", "right", "left"}};
static void cont__33_20(void);
static void cont__33_21(void);
static void cont__33_22(void);
static void cont__33_23(void);
static void cont__33_24(void);
static void cont__33_25(void);
static NODE *func__33_26;
static void entry__33_26(void);
static FRAME_INFO frame__33_26 = {2, {"result", "left"}};
static void cont__33_27(void);
static void cont__33_28(void);
static NODE *func__33_29;
static void entry__33_29(void);
static FRAME_INFO frame__33_29 = {2, {"result", "right"}};
static void cont__33_30(void);
static void cont__33_31(void);
static NODE *func__33_32;
static void entry__33_32(void);
static FRAME_INFO frame__33_32 = {3, {"return", "result", "left"}};
static void cont__33_33(void);
static NODE *func__33_34;
static void entry__33_34(void);
static FRAME_INFO frame__33_34 = {3, {"return", "result", "right"}};
static void cont__33_35(void);
static void cont__33_36(void);
static NODE *func__34_1_types__list_serialize;
static void entry__34_1_types__list_serialize(void);
static FRAME_INFO frame__34_1_types__list_serialize = {4, {"self", "indent", "return", "buf"}};
static void cont__34_2(void);
static NODE *func__34_3;
static void entry__34_3(void);
static FRAME_INFO frame__34_3 = {1, {"return"}};
static NODE *string__7e1f534683fac2fe;
static void cont__34_5(void);
static NODE *string__1a0aeb0b5df87d4d;
static NODE *func__34_7;
static void entry__34_7(void);
static FRAME_INFO frame__34_7 = {3, {"item", "buf", "indent"}};
static void cont__34_8(void);
static void cont__34_9(void);
static void cont__34_10(void);
static void cont__34_11(void);
static void cont__34_12(void);
static void cont__34_13(void);
static NODE *func__35_1_types__list_sort;
static void entry__35_1_types__list_sort(void);
static FRAME_INFO frame__35_1_types__list_sort = {4, {"self", "func", "return", "n"}};
static void cont__35_2(void);
static void cont__35_3(void);
static NODE *func__35_4;
static void entry__35_4(void);
static FRAME_INFO frame__35_4 = {2, {"return", "self"}};
static NODE *func__35_5;
static void entry__35_5(void);
static FRAME_INFO frame__35_5 = {3, {"func", "self", "return"}};
static void cont__35_6(void);
static NODE *func__35_7;
static void entry__35_7(void);
static FRAME_INFO frame__35_7 = {1, {"self"}};
static void cont__35_8(void);
static void cont__35_9(void);
static void cont__35_10(void);
static void cont__35_11(void);
static void cont__35_12(void);
static NODE *func__35_13;
static void entry__35_13(void);
static FRAME_INFO frame__35_13 = {2, {"func", "self"}};
static void cont__35_14(void);
static NODE *func__35_15;
static void entry__35_15(void);
static FRAME_INFO frame__35_15 = {2, {"func", "self"}};
static void cont__35_16(void);
static void cont__35_17(void);
static void cont__35_18(void);
static void cont__35_19(void);
static void cont__35_20(void);
static void cont__35_21(void);
static NODE *func__35_22;
static void entry__35_22(void);
static FRAME_INFO frame__35_22 = {2, {"return", "self"}};
static NODE *func__35_23;
static void entry__35_23(void);
static FRAME_INFO frame__35_23 = {2, {"return", "self"}};
static void cont__35_24(void);
static void cont__35_25(void);
static void cont__35_26(void);
static NODE *func__35_27;
static void entry__35_27(void);
static FRAME_INFO frame__35_27 = {5, {"n", "func", "return", "self", "m"}};
static void cont__35_28(void);
static void cont__35_29(void);
static NODE *func__35_30;
static void entry__35_30(void);
static FRAME_INFO frame__35_30 = {4, {"return", "self", "m", "n"}};
static void cont__35_31(void);
static void cont__35_32(void);
static void cont__35_33(void);
static void cont__35_34(void);
static void cont__35_35(void);
static void cont__35_36(void);
static NODE *func__35_37;
static void entry__35_37(void);
static FRAME_INFO frame__35_37 = {5, {"return", "self", "m", "func", "n"}};
static void cont__35_38(void);
static void cont__35_39(void);
static void cont__35_40(void);
static void cont__35_41(void);
static void cont__35_42(void);
static void cont__35_43(void);
static void cont__35_44(void);

static long func__types__list___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__37_1_types__list_new_empty_collection;
static void entry__37_1_types__list_new_empty_collection(void);
static FRAME_INFO frame__37_1_types__list_new_empty_collection = {1, {"self"}};
static NODE *func__38_1_types__generic_list_equal;
static void entry__38_1_types__generic_list_equal(void);
static FRAME_INFO frame__38_1_types__generic_list_equal = {3, {"left", "right", "return"}};
static void cont__38_2(void);
static NODE *func__38_3;
static void entry__38_3(void);
static FRAME_INFO frame__38_3 = {1, {"right"}};
static void cont__38_4(void);
static void cont__38_5(void);
static NODE *func__38_6;
static void entry__38_6(void);
static FRAME_INFO frame__38_6 = {1, {"return"}};
static void cont__38_7(void);
static void cont__38_8(void);
static void cont__38_9(void);
static void cont__38_10(void);
static void cont__38_11(void);
static NODE *func__38_12;
static void entry__38_12(void);
static FRAME_INFO frame__38_12 = {1, {"return"}};
static void cont__38_13(void);
static NODE *func__38_14;
static void entry__38_14(void);
static FRAME_INFO frame__38_14 = {4, {"idx", "item", "right", "return"}};
static void cont__38_15(void);
static void cont__38_16(void);
static void cont__38_17(void);
static NODE *func__38_18;
static void entry__38_18(void);
static FRAME_INFO frame__38_18 = {1, {"return"}};
static void cont__38_19(void);
static NODE *func__39_1_types__generic_list_filter;
static void entry__39_1_types__generic_list_filter(void);
static FRAME_INFO frame__39_1_types__generic_list_filter = {3, {"self", "test", "new_list"}};
static void cont__39_2(void);
static NODE *func__39_3;
static void entry__39_3(void);
static FRAME_INFO frame__39_3 = {3, {"item", "test", "new_list"}};
static void cont__39_4(void);
static NODE *func__39_5;
static void entry__39_5(void);
static FRAME_INFO frame__39_5 = {2, {"new_list", "item"}};
static void cont__39_6(void);
static void cont__39_7(void);
static NODE *func__40_1_types__generic_list_map;
static void entry__40_1_types__generic_list_map(void);
static FRAME_INFO frame__40_1_types__generic_list_map = {3, {"self", "func", "new_list"}};
static void cont__40_2(void);
static NODE *func__40_3;
static void entry__40_3(void);
static FRAME_INFO frame__40_3 = {3, {"item", "new_list", "func"}};
static void cont__40_4(void);
static void cont__40_5(void);
static void cont__40_6(void);
static NODE *func__41_1_types__generic_list_dup;
static void entry__41_1_types__generic_list_dup(void);
static FRAME_INFO frame__41_1_types__generic_list_dup = {2, {"self", "n"}};
static NODE *func__41_2;
static void entry__41_2(void);
static FRAME_INFO frame__41_2 = {1, {"self"}};
static NODE *func__41_3;
static void entry__41_3(void);
static FRAME_INFO frame__41_3 = {3, {"n", "self", "result"}};
static void cont__41_4(void);
static NODE *func__41_5;
static void entry__41_5(void);
static FRAME_INFO frame__41_5 = {0, {}};
static NODE *string__963fa2c6021831d1;
static void cont__41_7(void);
static void cont__41_8(void);
static void cont__41_9(void);
static void cont__41_10(void);
static void cont__41_11(void);
static NODE *func__41_12;
static void entry__41_12(void);
static FRAME_INFO frame__41_12 = {2, {"result", "self"}};
static void cont__41_13(void);
static void cont__41_14(void);
static NODE *func__41_15;
static void entry__41_15(void);
static FRAME_INFO frame__41_15 = {0, {}};
static NODE *func__42_1_types__generic_list_interleave;
static void entry__42_1_types__generic_list_interleave(void);
static FRAME_INFO frame__42_1_types__generic_list_interleave = {3, {"lists", "n", "result"}};
static void cont__42_2(void);
static void cont__42_3(void);
static void cont__42_4(void);
static NODE *func__42_5;
static void entry__42_5(void);
static FRAME_INFO frame__42_5 = {3, {"i", "lists", "result"}};
static NODE *func__42_6;
static void entry__42_6(void);
static FRAME_INFO frame__42_6 = {3, {"current_list", "result", "i"}};
static void cont__42_7(void);
static void cont__42_8(void);
static void cont__42_9(void);
static NODE *func__42_10;
static void entry__42_10(void);
static FRAME_INFO frame__42_10 = {3, {"current_list", "n", "result"}};
static void cont__42_11(void);
static void cont__42_12(void);
static void cont__42_13(void);
static NODE *func__42_14;
static void entry__42_14(void);
static FRAME_INFO frame__42_14 = {3, {"result", "current_list", "n"}};
static void cont__42_15(void);
static void cont__42_16(void);
static void cont__42_17(void);
static NODE *func__43_1_types__generic_list_contains;
static void entry__43_1_types__generic_list_contains(void);
static FRAME_INFO frame__43_1_types__generic_list_contains = {3, {"self", "item", "return"}};
static NODE *func__43_2;
static void entry__43_2(void);
static FRAME_INFO frame__43_2 = {3, {"current_item", "item", "return"}};
static void cont__43_3(void);
static NODE *func__43_4;
static void entry__43_4(void);
static FRAME_INFO frame__43_4 = {1, {"return"}};
static void cont__43_5(void);
static int poly_idx__std__is_a_sequence;
static void type__std__is_a_sequence(void);
static NODE *get__std__is_a_sequence(void) {
  return var.std__is_a_sequence;
}
static NODE *func__46_1_std__sequence;
static void entry__46_1_std__sequence(void);
static FRAME_INFO frame__46_1_std__sequence = {1, {"items"}};
static void cont__46_2(void);
static NODE *func__46_3;
static void entry__46_3(void);
static FRAME_INFO frame__46_3 = {3, {"self", "element", "return"}};
static NODE *func__46_4;
static void entry__46_4(void);
static FRAME_INFO frame__46_4 = {3, {"item", "element", "return"}};
static void cont__46_5(void);
static NODE *func__46_6;
static void entry__46_6(void);
static FRAME_INFO frame__46_6 = {2, {"item", "element"}};
static void cont__46_7(void);
static void cont__46_8(void);
static NODE *func__46_9;
static void entry__46_9(void);
static FRAME_INFO frame__46_9 = {1, {"return"}};
static void cont__46_10(void);
static NODE *get__std__sequence(void) {
  return var.std__sequence;
}
static NODE *func__94_1;
static void entry__94_1(void);
static FRAME_INFO frame__94_1 = {4, {"text", "base_indent", "return", "obj"}};
static NODE *string__2d7981f4e6482bec;
static void cont__94_3(void);
static NODE *func__94_4;
static void entry__94_4(void);
static FRAME_INFO frame__94_4 = {2, {"return", "text"}};
static void cont__94_5(void);
static void cont__94_6(void);
static void cont__94_7(void);
static void cont__94_8(void);
static void cont__94_9(void);
static void cont__94_10(void);
static NODE *func__94_11;
static void entry__94_11(void);
static FRAME_INFO frame__94_11 = {0, {}};
static NODE *string__b53819e78eec080a;
static void cont__94_13(void);
static NODE *func__94_14;
static void entry__94_14(void);
static FRAME_INFO frame__94_14 = {6, {"text", "return", "obj", "base_indent", "remaining_text", "indent"}};
static void cont__94_15(void);
static void cont__94_16(void);
static NODE *func__94_17;
static void entry__94_17(void);
static FRAME_INFO frame__94_17 = {1, {"text"}};
static void cont__94_18(void);
static void cont__94_19(void);
static void cont__94_20(void);
static void cont__94_21(void);
static NODE *func__94_22;
static void entry__94_22(void);
static FRAME_INFO frame__94_22 = {3, {"return", "text", "obj"}};
static void cont__94_23(void);
static void cont__94_24(void);
static void cont__94_25(void);
static void cont__94_26(void);
static NODE *func__94_27;
static void entry__94_27(void);
static FRAME_INFO frame__94_27 = {3, {"return", "text", "obj"}};
static void cont__94_28(void);
static void cont__94_29(void);
static void cont__94_30(void);
static void cont__94_31(void);
static void cont__94_32(void);
void run__basic__types__list(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_list, NULL, 25, 25, 2, 15},
  {type__std__is_a_sequence, NULL, 722, 722, 2, 19},
  {run__basic__types__list, NULL, 747, 764, 1, 45},
  {cont__94_32, NULL, },
  {entry__14_1_types__list_to_list, NULL, 176, 176, 3, 9},
  {entry__15_1_std__list, NULL, 181, 193, 3, 2},
  {entry__16_1_types__list_length_of, NULL, 198, 201, 3, 2},
  {entry__17_1_types__list_push, NULL, 206, 224, 3, 2},
  {entry__18_1_types__list_drop, NULL, 229, 236, 3, 2},
  {entry__19_1_types__list_pop, NULL, 241, 252, 3, 2},
  {entry__20_1_types__list_peek, NULL, 257, 263, 3, 2},
  {entry__21_1_types__list_append, NULL, 268, 293, 3, 2},
  {entry__22_1_types__list_range, NULL, 298, 319, 3, 2},
  {entry__23_4, NULL, 329, 329, 44, 48},
  {cont__23_5, &frame__23_4, 329, 329, 31, 49},
  {cont__23_6, &frame__23_4, 329, 329, 62, 70},
  {cont__23_7, &frame__23_4, 329, 329, 73, 73},
  {cont__23_8, &frame__23_4, 329, 329, 51, 74},
  {cont__23_9, &frame__23_4, 329, 329, 18, 75},
  {cont__23_10, &frame__23_4, 329, 329, 75, 75},
  {entry__23_1_types__generic_list_delete_at, NULL, 329, 329, 6, 15},
  {cont__23_2, &frame__23_1_types__generic_list_delete_at, 329, 329, 6, 15},
  {cont__23_3, &frame__23_1_types__generic_list_delete_at, 329, 329, 3, 75},
  {cont__23_11, &frame__23_1_types__generic_list_delete_at, },
  {entry__24_4, NULL, 341, 341, 7, 16},
  {entry__24_5, NULL, 343, 343, 14, 28},
  {cont__24_6, &frame__24_5, 343, 343, 14, 30},
  {cont__24_7, &frame__24_5, 343, 343, 14, 34},
  {cont__24_8, &frame__24_5, 343, 343, 7, 34},
  {entry__24_1_std__normalized_index, NULL, 340, 340, 5, 12},
  {cont__24_2, &frame__24_1_std__normalized_index, 340, 340, 5, 12},
  {cont__24_3, &frame__24_1_std__normalized_index, 339, 343, 3, 35},
  {cont__24_9, &frame__24_1_std__normalized_index, 343, 343, 35, 35},
  {entry__25_1_types__generic_list_is_empty, NULL, 351, 351, 6, 20},
  {cont__25_2, &frame__25_1_types__generic_list_is_empty, 351, 351, 6, 25},
  {cont__25_3, &frame__25_1_types__generic_list_is_empty, 351, 351, 3, 25},
  {entry__26_10, NULL, 380, 380, 16, 22},
  {cont__26_11, &frame__26_10, 380, 380, 9, 22},
  {entry__26_12, NULL, 382, 382, 14, 20},
  {cont__26_13, &frame__26_12, 382, 382, 9, 20},
  {entry__26_16, NULL, 383, 383, 28, 32},
  {cont__26_17, &frame__26_16, 383, 383, 28, 32},
  {entry__26_19, NULL, 383, 383, 35, 39},
  {entry__26_7, NULL, 379, 379, 7, 30},
  {cont__26_8, &frame__26_7, 379, 379, 7, 35},
  {cont__26_9, &frame__26_7, 378, 382, 5, 21},
  {cont__26_14, &frame__26_7, 383, 383, 8, 23},
  {cont__26_15, &frame__26_7, 383, 383, 8, 32},
  {cont__26_18, &frame__26_7, 383, 383, 5, 39},
  {cont__26_20, &frame__26_7, 384, 384, 5, 13},
  {cont__26_21, &frame__26_7, 384, 384, 13, 13},
  {entry__26_4, NULL, 377, 377, 12, 17},
  {cont__26_5, &frame__26_4, 377, 377, 12, 17},
  {cont__26_6, &frame__26_4, 377, 384, 9, 13},
  {entry__26_1_types__generic_list_for_each_from_to, NULL, 375, 375, 3, 34},
  {cont__26_2, &frame__26_1_types__generic_list_for_each_from_to, 376, 376, 3, 32},
  {cont__26_3, &frame__26_1_types__generic_list_for_each_from_to, 377, 384, 3, 13},
  {entry__27_10, NULL, 413, 413, 16, 22},
  {cont__27_11, &frame__27_10, 413, 413, 9, 22},
  {entry__27_12, NULL, 415, 415, 14, 20},
  {cont__27_13, &frame__27_12, 415, 415, 9, 20},
  {entry__27_16, NULL, 416, 416, 28, 32},
  {cont__27_17, &frame__27_16, 416, 416, 28, 32},
  {entry__27_19, NULL, 416, 416, 35, 39},
  {entry__27_7, NULL, 412, 412, 7, 30},
  {cont__27_8, &frame__27_7, 412, 412, 7, 35},
  {cont__27_9, &frame__27_7, 411, 415, 5, 21},
  {cont__27_14, &frame__27_7, 416, 416, 8, 23},
  {cont__27_15, &frame__27_7, 416, 416, 8, 32},
  {cont__27_18, &frame__27_7, 416, 416, 5, 39},
  {cont__27_20, &frame__27_7, 417, 417, 5, 14},
  {cont__27_21, &frame__27_7, 417, 417, 14, 14},
  {entry__27_4, NULL, 410, 410, 12, 17},
  {cont__27_5, &frame__27_4, 410, 410, 12, 17},
  {cont__27_6, &frame__27_4, 410, 417, 9, 14},
  {entry__27_1_types__generic_list_for_each_from_down_to, NULL, 408, 408, 3, 34},
  {cont__27_2, &frame__27_1_types__generic_list_for_each_from_down_to, 409, 409, 3, 32},
  {cont__27_3, &frame__27_1_types__generic_list_for_each_from_down_to, 410, 417, 3, 14},
  {entry__28_13, NULL, 442, 442, 32, 36},
  {cont__28_14, &frame__28_13, 442, 442, 32, 36},
  {entry__28_16, NULL, 442, 442, 39, 43},
  {entry__28_9, NULL, 441, 441, 16, 22},
  {cont__28_10, &frame__28_9, 441, 441, 9, 22},
  {cont__28_11, &frame__28_9, 442, 442, 12, 27},
  {cont__28_12, &frame__28_9, 442, 442, 12, 36},
  {cont__28_15, &frame__28_9, 442, 442, 9, 43},
  {cont__28_17, &frame__28_9, 443, 443, 9, 17},
  {cont__28_18, &frame__28_9, 443, 443, 17, 17},
  {entry__28_6, NULL, 440, 440, 16, 21},
  {cont__28_7, &frame__28_6, 440, 440, 16, 21},
  {cont__28_8, &frame__28_6, 440, 443, 13, 17},
  {entry__28_5, NULL, 440, 443, 7, 17},
  {entry__28_27, NULL, 447, 447, 32, 36},
  {cont__28_28, &frame__28_27, 447, 447, 32, 36},
  {entry__28_30, NULL, 447, 447, 39, 43},
  {entry__28_23, NULL, 446, 446, 14, 20},
  {cont__28_24, &frame__28_23, 446, 446, 9, 20},
  {cont__28_25, &frame__28_23, 447, 447, 12, 27},
  {cont__28_26, &frame__28_23, 447, 447, 12, 36},
  {cont__28_29, &frame__28_23, 447, 447, 9, 43},
  {cont__28_31, &frame__28_23, 448, 448, 9, 17},
  {cont__28_32, &frame__28_23, 448, 448, 17, 17},
  {entry__28_20, NULL, 445, 445, 16, 21},
  {cont__28_21, &frame__28_20, 445, 445, 16, 21},
  {cont__28_22, &frame__28_20, 445, 448, 13, 17},
  {entry__28_19, NULL, 445, 448, 7, 17},
  {entry__28_1_types__generic_list_for_each, NULL, 437, 437, 3, 20},
  {cont__28_2, &frame__28_1_types__generic_list_for_each, 439, 439, 5, 28},
  {cont__28_3, &frame__28_1_types__generic_list_for_each, 439, 439, 5, 33},
  {cont__28_4, &frame__28_1_types__generic_list_for_each, 438, 448, 3, 19},
  {entry__29_6, NULL, 478, 478, 11, 35},
  {cont__29_7, &frame__29_6, 478, 478, 35, 35},
  {entry__29_8, NULL, 480, 480, 11, 33},
  {cont__29_9, &frame__29_8, 480, 480, 33, 33},
  {entry__29_4, NULL, 477, 477, 9, 30},
  {cont__29_5, &frame__29_4, 476, 480, 7, 34},
  {entry__29_2_update_item, NULL, 475, 475, 8, 26},
  {cont__29_3, &frame__29_2_update_item, 475, 480, 5, 35},
  {cont__29_10, &frame__29_2_update_item, 481, 481, 5, 13},
  {cont__29_11, &frame__29_2_update_item, 481, 481, 13, 13},
  {entry__29_19, NULL, 488, 488, 43, 49},
  {cont__29_20, &frame__29_19, 488, 488, 36, 50},
  {cont__29_21, &frame__29_19, 488, 488, 24, 50},
  {entry__29_16, NULL, 488, 488, 16, 21},
  {cont__29_17, &frame__29_16, 488, 488, 16, 21},
  {cont__29_18, &frame__29_16, 488, 488, 13, 50},
  {entry__29_15, NULL, 488, 488, 7, 50},
  {entry__29_26, NULL, 490, 490, 41, 47},
  {cont__29_27, &frame__29_26, 490, 490, 36, 48},
  {cont__29_28, &frame__29_26, 490, 490, 24, 48},
  {entry__29_23, NULL, 490, 490, 16, 21},
  {cont__29_24, &frame__29_23, 490, 490, 16, 21},
  {cont__29_25, &frame__29_23, 490, 490, 13, 48},
  {entry__29_22, NULL, 490, 490, 7, 48},
  {entry__29_1_types__generic_list_update_each, NULL, 484, 484, 3, 20},
  {cont__29_12, &frame__29_1_types__generic_list_update_each, 487, 487, 5, 28},
  {cont__29_13, &frame__29_1_types__generic_list_update_each, 487, 487, 5, 33},
  {cont__29_14, &frame__29_1_types__generic_list_update_each, 486, 490, 3, 49},
  {cont__29_29, &frame__29_1_types__generic_list_update_each, 491, 491, 3, 17},
  {cont__29_30, &frame__29_1_types__generic_list_update_each, 491, 491, 17, 17},
  {entry__30_5, NULL, 507, 507, 10, 16},
  {cont__30_6, &frame__30_5, 507, 507, 23, 25},
  {cont__30_7, &frame__30_5, 507, 507, 18, 26},
  {cont__30_8, &frame__30_5, 507, 507, 5, 26},
  {cont__30_9, &frame__30_5, 508, 508, 5, 13},
  {cont__30_10, &frame__30_5, 508, 508, 13, 13},
  {entry__30_3, NULL, 506, 506, 12, 16},
  {cont__30_4, &frame__30_3, 506, 508, 9, 13},
  {entry__30_13, NULL, 509, 509, 22, 28},
  {cont__30_14, &frame__30_13, 509, 509, 17, 28},
  {entry__30_1_types__list_for_each_pair, NULL, 505, 505, 3, 20},
  {cont__30_2, &frame__30_1_types__list_for_each_pair, 506, 508, 3, 13},
  {cont__30_11, &frame__30_1_types__list_for_each_pair, 509, 509, 6, 14},
  {cont__30_12, &frame__30_1_types__list_for_each_pair, 509, 509, 3, 28},
  {entry__31_4, NULL, 517, 517, 28, 80},
  {entry__31_1_types__generic_list_get, NULL, 517, 517, 6, 20},
  {cont__31_2, &frame__31_1_types__generic_list_get, 517, 517, 6, 25},
  {cont__31_3, &frame__31_1_types__generic_list_get, 517, 517, 3, 80},
  {cont__31_6, &frame__31_1_types__generic_list_get, 518, 518, 20, 20},
  {cont__31_7, &frame__31_1_types__generic_list_get, 518, 518, 6, 21},
  {cont__31_8, &frame__31_1_types__generic_list_get, 518, 518, 23, 29},
  {cont__31_9, &frame__31_1_types__generic_list_get, 518, 518, 3, 29},
  {entry__32_1_types__list_put, NULL, 527, 527, 13, 22},
  {cont__32_2, &frame__32_1_types__list_put, 527, 527, 6, 28},
  {cont__32_3, &frame__32_1_types__list_put, 527, 527, 3, 28},
  {entry__33_11, NULL, 546, 546, 49, 56},
  {cont__33_12, &frame__33_11, 546, 546, 38, 44},
  {cont__33_13, &frame__33_11, 546, 546, 38, 56},
  {cont__33_14, &frame__33_11, 546, 546, 38, 56},
  {cont__33_15, &frame__33_11, 546, 546, 38, 56},
  {entry__33_19, NULL, 547, 547, 45, 52},
  {cont__33_20, &frame__33_19, 547, 547, 54, 60},
  {cont__33_21, &frame__33_19, 547, 547, 40, 61},
  {cont__33_22, &frame__33_19, 547, 547, 36, 62},
  {cont__33_23, &frame__33_19, 547, 547, 36, 62},
  {entry__33_17, NULL, 547, 547, 17, 31},
  {cont__33_18, &frame__33_17, 547, 547, 17, 62},
  {cont__33_24, &frame__33_17, 547, 547, 17, 62},
  {entry__33_26, NULL, 549, 549, 30, 39},
  {cont__33_27, &frame__33_26, 549, 549, 17, 39},
  {cont__33_28, &frame__33_26, 549, 549, 39, 39},
  {entry__33_29, NULL, 551, 551, 30, 40},
  {cont__33_30, &frame__33_29, 551, 551, 17, 40},
  {cont__33_31, &frame__33_29, 551, 551, 40, 40},
  {entry__33_9, NULL, 546, 546, 17, 33},
  {cont__33_10, &frame__33_9, 546, 546, 17, 56},
  {cont__33_16, &frame__33_9, 545, 547, 15, 61},
  {cont__33_25, &frame__33_9, 544, 551, 13, 41},
  {entry__33_32, NULL, 553, 553, 20, 38},
  {cont__33_33, &frame__33_32, 553, 553, 13, 38},
  {entry__33_6, NULL, 543, 543, 11, 26},
  {cont__33_7, &frame__33_6, 543, 543, 11, 30},
  {cont__33_8, &frame__33_6, 542, 553, 9, 39},
  {entry__33_34, NULL, 555, 555, 16, 35},
  {cont__33_35, &frame__33_34, 555, 555, 9, 35},
  {entry__33_3, NULL, 541, 541, 7, 21},
  {cont__33_4, &frame__33_3, 541, 541, 7, 25},
  {cont__33_5, &frame__33_3, 540, 555, 5, 36},
  {entry__33_1_types__list_merge, NULL, 538, 538, 3, 17},
  {cont__33_2, &frame__33_1_types__list_merge, 539, 555, 3, 37},
  {cont__33_36, &frame__33_1_types__list_merge, 555, 555, 37, 37},
  {entry__34_3, NULL, 565, 565, 21, 35},
  {entry__34_7, NULL, 568, 568, 33, 40},
  {cont__34_8, &frame__34_7, 568, 568, 26, 41},
  {cont__34_9, &frame__34_7, 568, 568, 58, 65},
  {cont__34_10, &frame__34_7, 568, 568, 43, 66},
  {cont__34_11, &frame__34_7, 568, 568, 5, 66},
  {cont__34_12, &frame__34_7, 568, 568, 66, 66},
  {entry__34_1_types__list_serialize, NULL, 565, 565, 6, 18},
  {cont__34_2, &frame__34_1_types__list_serialize, 565, 565, 3, 35},
  {cont__34_5, &frame__34_1_types__list_serialize, 567, 568, 3, 66},
  {cont__34_13, &frame__34_1_types__list_serialize, 569, 569, 3, 8},
  {entry__35_4, NULL, 586, 586, 7, 17},
  {entry__35_7, NULL, 590, 590, 43, 49},
  {cont__35_8, &frame__35_7, 590, 590, 32, 38},
  {cont__35_9, &frame__35_7, 590, 590, 32, 49},
  {cont__35_10, &frame__35_7, 590, 590, 32, 49},
  {cont__35_11, &frame__35_7, 590, 590, 32, 49},
  {entry__35_15, NULL, 591, 591, 39, 45},
  {cont__35_16, &frame__35_15, 591, 591, 47, 53},
  {cont__35_17, &frame__35_15, 591, 591, 34, 54},
  {cont__35_18, &frame__35_15, 591, 591, 30, 55},
  {cont__35_19, &frame__35_15, 591, 591, 30, 55},
  {entry__35_13, NULL, 591, 591, 11, 25},
  {cont__35_14, &frame__35_13, 591, 591, 11, 55},
  {cont__35_20, &frame__35_13, 591, 591, 11, 55},
  {entry__35_22, NULL, 593, 593, 11, 21},
  {entry__35_23, NULL, 595, 595, 23, 29},
  {cont__35_24, &frame__35_23, 595, 595, 31, 37},
  {cont__35_25, &frame__35_23, 595, 595, 18, 38},
  {cont__35_26, &frame__35_23, 595, 595, 11, 38},
  {entry__35_5, NULL, 590, 590, 11, 27},
  {cont__35_6, &frame__35_5, 590, 590, 11, 49},
  {cont__35_12, &frame__35_5, 589, 591, 9, 54},
  {cont__35_21, &frame__35_5, 588, 595, 7, 39},
  {entry__35_30, NULL, 600, 600, 29, 43},
  {cont__35_31, &frame__35_30, 600, 600, 24, 44},
  {cont__35_32, &frame__35_30, 600, 600, 62, 64},
  {cont__35_33, &frame__35_30, 600, 600, 51, 67},
  {cont__35_34, &frame__35_30, 600, 600, 46, 68},
  {cont__35_35, &frame__35_30, 600, 600, 18, 69},
  {cont__35_36, &frame__35_30, 600, 600, 11, 69},
  {entry__35_37, NULL, 603, 603, 24, 38},
  {cont__35_38, &frame__35_37, 603, 603, 19, 44},
  {cont__35_39, &frame__35_37, 603, 603, 62, 64},
  {cont__35_40, &frame__35_37, 603, 603, 51, 67},
  {cont__35_41, &frame__35_37, 603, 603, 46, 73},
  {cont__35_42, &frame__35_37, 603, 603, 13, 79},
  {cont__35_43, &frame__35_37, 602, 603, 11, 79},
  {entry__35_27, NULL, 597, 597, 7, 18},
  {cont__35_28, &frame__35_27, 599, 599, 9, 25},
  {cont__35_29, &frame__35_27, 598, 603, 7, 81},
  {entry__35_1_types__list_sort, NULL, 582, 582, 3, 20},
  {cont__35_2, &frame__35_1_types__list_sort, 585, 585, 5, 8},
  {cont__35_3, &frame__35_1_types__list_sort, 583, 603, 3, 83},
  {cont__35_44, &frame__35_1_types__list_sort, 603, 603, 83, 83},
  {entry__37_1_types__list_new_empty_collection, NULL, 640, 640, 3, 16},
  {entry__38_3, NULL, 652, 652, 30, 44},
  {cont__38_4, &frame__38_3, 652, 652, 30, 44},
  {entry__38_6, NULL, 652, 652, 47, 58},
  {entry__38_12, NULL, 653, 653, 43, 54},
  {entry__38_18, NULL, 654, 654, 52, 63},
  {entry__38_14, NULL, 654, 654, 40, 49},
  {cont__38_15, &frame__38_14, 654, 654, 32, 49},
  {cont__38_16, &frame__38_14, 654, 654, 32, 49},
  {cont__38_17, &frame__38_14, 654, 654, 29, 63},
  {entry__38_1_types__generic_list_equal, NULL, 652, 652, 10, 25},
  {cont__38_2, &frame__38_1_types__generic_list_equal, 652, 652, 10, 44},
  {cont__38_5, &frame__38_1_types__generic_list_equal, 652, 652, 3, 58},
  {cont__38_7, &frame__38_1_types__generic_list_equal, 653, 653, 6, 20},
  {cont__38_8, &frame__38_1_types__generic_list_equal, 653, 653, 25, 40},
  {cont__38_9, &frame__38_1_types__generic_list_equal, 653, 653, 6, 40},
  {cont__38_10, &frame__38_1_types__generic_list_equal, 653, 653, 6, 40},
  {cont__38_11, &frame__38_1_types__generic_list_equal, 653, 653, 3, 54},
  {cont__38_13, &frame__38_1_types__generic_list_equal, 654, 654, 3, 63},
  {cont__38_19, &frame__38_1_types__generic_list_equal, 655, 655, 3, 9},
  {entry__39_5, NULL, 665, 665, 40, 58},
  {cont__39_6, &frame__39_5, 665, 665, 58, 58},
  {entry__39_3, NULL, 665, 665, 28, 37},
  {cont__39_4, &frame__39_3, 665, 665, 25, 58},
  {entry__39_1_types__generic_list_filter, NULL, 664, 664, 3, 39},
  {cont__39_2, &frame__39_1_types__generic_list_filter, 665, 665, 3, 58},
  {cont__39_7, &frame__39_1_types__generic_list_filter, 666, 666, 3, 13},
  {entry__40_3, NULL, 678, 678, 40, 49},
  {cont__40_4, &frame__40_3, 678, 678, 25, 49},
  {cont__40_5, &frame__40_3, 678, 678, 49, 49},
  {entry__40_1_types__generic_list_map, NULL, 677, 677, 3, 39},
  {cont__40_2, &frame__40_1_types__generic_list_map, 678, 678, 3, 49},
  {cont__40_6, &frame__40_1_types__generic_list_map, 679, 679, 3, 13},
  {entry__41_2, NULL, 688, 688, 31, 37},
  {entry__41_5, NULL, 689, 689, 15, 48},
  {entry__41_12, NULL, 692, 692, 18, 36},
  {cont__41_13, &frame__41_12, 692, 692, 36, 36},
  {entry__41_3, NULL, 689, 689, 8, 12},
  {cont__41_4, &frame__41_3, 689, 689, 5, 48},
  {cont__41_7, &frame__41_3, 690, 690, 23, 31},
  {cont__41_8, &frame__41_3, 690, 690, 5, 32},
  {cont__41_9, &frame__41_3, 691, 691, 5, 25},
  {cont__41_10, &frame__41_3, 692, 692, 8, 15},
  {cont__41_11, &frame__41_3, 692, 692, 5, 36},
  {cont__41_14, &frame__41_3, 693, 693, 5, 13},
  {entry__41_15, NULL, 688, 688, 13, 25},
  {entry__41_1_types__generic_list_dup, NULL, 688, 693, 3, 13},
  {entry__42_6, NULL, 706, 706, 66, 80},
  {cont__42_7, &frame__42_6, 706, 706, 53, 80},
  {cont__42_8, &frame__42_6, 706, 706, 80, 80},
  {entry__42_5, NULL, 706, 706, 22, 80},
  {entry__42_14, NULL, 708, 708, 51, 65},
  {cont__42_15, &frame__42_14, 708, 708, 38, 65},
  {cont__42_16, &frame__42_14, 708, 708, 65, 65},
  {entry__42_10, NULL, 708, 708, 8, 30},
  {cont__42_11, &frame__42_10, 708, 708, 8, 35},
  {cont__42_12, &frame__42_10, 708, 708, 8, 35},
  {cont__42_13, &frame__42_10, 708, 708, 5, 65},
  {entry__42_1_types__generic_list_interleave, NULL, 704, 704, 16, 23},
  {cont__42_2, &frame__42_1_types__generic_list_interleave, 704, 704, 3, 24},
  {cont__42_3, &frame__42_1_types__generic_list_interleave, 706, 706, 13, 15},
  {cont__42_4, &frame__42_1_types__generic_list_interleave, 706, 706, 3, 80},
  {cont__42_9, &frame__42_1_types__generic_list_interleave, 707, 708, 3, 65},
  {cont__42_17, &frame__42_1_types__generic_list_interleave, 709, 709, 3, 11},
  {entry__43_4, NULL, 719, 719, 58, 68},
  {entry__43_2, NULL, 719, 719, 36, 55},
  {cont__43_3, &frame__43_2, 719, 719, 33, 68},
  {entry__43_1_types__generic_list_contains, NULL, 719, 719, 3, 68},
  {cont__43_5, &frame__43_1_types__generic_list_contains, 720, 720, 3, 10},
  {entry__46_6, NULL, 744, 744, 33, 55},
  {cont__46_7, &frame__46_6, 744, 744, 33, 55},
  {entry__46_9, NULL, 744, 744, 58, 68},
  {entry__46_4, NULL, 744, 744, 14, 28},
  {cont__46_5, &frame__46_4, 744, 744, 14, 55},
  {cont__46_8, &frame__46_4, 744, 744, 11, 68},
  {entry__46_3, NULL, 743, 744, 9, 68},
  {cont__46_10, &frame__46_3, 745, 745, 9, 16},
  {entry__46_1_std__sequence, NULL, 735, 735, 5, 16},
  {cont__46_2, &frame__46_1_std__sequence, 734, 745, 3, 18},
  {entry__94_4, NULL, 755, 755, 51, 51},
  {cont__94_5, &frame__94_4, 755, 755, 37, 52},
  {cont__94_6, &frame__94_4, 755, 755, 30, 63},
  {entry__94_11, NULL, 757, 757, 5, 67},
  {entry__94_17, NULL, 760, 760, 32, 38},
  {cont__94_18, &frame__94_17, 760, 760, 32, 48},
  {cont__94_19, &frame__94_17, 760, 760, 32, 48},
  {cont__94_20, &frame__94_17, 760, 760, 32, 48},
  {entry__94_22, NULL, 760, 760, 51, 65},
  {entry__94_27, NULL, 762, 762, 31, 45},
  {entry__94_14, NULL, 760, 760, 8, 22},
  {cont__94_15, &frame__94_14, 760, 760, 8, 27},
  {cont__94_16, &frame__94_14, 760, 760, 8, 48},
  {cont__94_21, &frame__94_14, 760, 760, 5, 65},
  {cont__94_23, &frame__94_14, 761, 761, 5, 59},
  {cont__94_24, &frame__94_14, 762, 762, 8, 28},
  {cont__94_25, &frame__94_14, 762, 762, 8, 28},
  {cont__94_26, &frame__94_14, 762, 762, 5, 45},
  {cont__94_28, &frame__94_14, 764, 764, 15, 44},
  {cont__94_29, &frame__94_14, 764, 764, 5, 44},
  {cont__94_30, &frame__94_14, 764, 764, 44, 44},
  {entry__94_1, NULL, 755, 755, 6, 27},
  {cont__94_3, &frame__94_1, 755, 755, 3, 63},
  {cont__94_7, &frame__94_1, 756, 756, 6, 12},
  {cont__94_8, &frame__94_1, 756, 756, 6, 22},
  {cont__94_9, &frame__94_1, 756, 756, 6, 22},
  {cont__94_10, &frame__94_1, 756, 757, 3, 67},
  {cont__94_13, &frame__94_1, 759, 764, 3, 44},
  {cont__94_31, &frame__94_1, 764, 764, 44, 44}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  LIST list;
};
static void type__std__is_a_list(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_list);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_list, attr);
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
static void type__std__is_a_sequence(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_sequence);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_sequence, attr);
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
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__list",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/list.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__list(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 747: register_deserializer "list":
  // 748:   #
  // 749:     constructs a list from its serialized representation
  // 750:   (
  // 751:     $text
  // 752:     base_indent
  // 753:     -> return
  // 754:   )
  // 755:   if text .has_prefix. "()": return range(text 3 -1) empty_list
  // 756:   if text(1) != '@nl;':
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1a0aeb0b5df87d4d;
  arguments->slots[1] = func__94_1;
  result_count = 0;
  myself = get__register_deserializer();
  func = myself->type;
  frame->cont = cont__94_32;
}
static void entry__94_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // text: 0
  // base_indent: 1
  // return: 2
  // obj: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* obj */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 755: ... text .has_prefix. "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = string__2d7981f4e6482bec;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__94_3;
}
static void cont__94_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 755: ... : return range(text 3 -1) empty_list
  frame->slots[5] /* temp__2 */ = create_closure(entry__94_4, 0);
  // 755: if text .has_prefix. "()": return range(text 3 -1) empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__94_7;
}
static void entry__94_4(void) {
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
  // 755: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__94_5;
}
static void cont__94_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 755: ... range(text 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__94_6;
}
static void cont__94_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 755: ... return range(text 3 -1) empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__94_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 756: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__94_8;
}
static void cont__94_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 756: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__94_9;
}
static void cont__94_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 756: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__94_10;
}
static void cont__94_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 756: if text(1) != '@nl;':
  // 757:   raise "Invalid list object encountered during deserialisation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__94_11;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__94_13;
}
static void entry__94_11(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 757: raise "Invalid list object encountered during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b53819e78eec080a;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__94_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 758: $$obj empty_list
  ((CELL *)frame->slots[3])->contents /* obj */ = get__empty_list();
  // 759: ... :
  // 760:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 761:   get_deserialization_indent $remaining_text $indent text
  // 762:   if indent <= base_indent: return text obj
  // 763:   !text remaining_text
  // 764:   push &obj deserialize_item(&text indent)
  frame->slots[4] /* temp__1 */ = create_closure(entry__94_14, 0);
  // 759: forever:
  // 760:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 761:   get_deserialization_indent $remaining_text $indent text
  // 762:   if indent <= base_indent: return text obj
  // 763:   !text remaining_text
  // 764:   push &obj deserialize_item(&text indent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__94_31;
}
static void entry__94_14(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // text: 0
  // return: 1
  // obj: 2
  // base_indent: 3
  // remaining_text: 4
  // indent: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  frame->slots[2] = myself->closure.frame->slots[3]; /* obj */
  frame->slots[3] = myself->closure.frame->slots[1]; /* base_indent */
  frame->slots[4] /* remaining_text */ = create_future();
  frame->slots[5] /* indent */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__94_15;
}
static void cont__94_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 760: ... length_of(text) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__94_16;
}
static void cont__94_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 760: ... text(1) != '@nl;'
  frame->slots[9] /* temp__4 */ = create_closure(entry__94_17, 0);
  // 760: ... length_of(text) == 0 || text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__94_21;
}
static void entry__94_17(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__94_18;
}
static void cont__94_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 760: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__94_19;
}
static void cont__94_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 760: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__94_20;
}
static void cont__94_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 760: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__94_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 760: ... : return text obj
  frame->slots[10] /* temp__5 */ = create_closure(entry__94_22, 0);
  // 760: if length_of(text) == 0 || text(1) != '@nl;': return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__94_23;
}
static void entry__94_22(void) {
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
  // 760: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__94_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 761: get_deserialization_indent $remaining_text $indent text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 2;
  myself = get__get_deserialization_indent();
  func = myself->type;
  frame->cont = cont__94_24;
}
static void cont__94_24(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 761: ... remaining_text
  initialize_future(frame->slots[4] /* remaining_text */, frame->slots[6] /* temp__1 */);
  // 761: ... indent
  initialize_future(frame->slots[5] /* indent */, frame->slots[7] /* temp__2 */);
  // 762: ... indent <= base_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base_indent */;
  arguments->slots[1] = frame->slots[5] /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__94_25;
}
static void cont__94_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 762: ... indent <= base_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__94_26;
}
static void cont__94_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 762: ... : return text obj
  frame->slots[8] /* temp__3 */ = create_closure(entry__94_27, 0);
  // 762: if indent <= base_indent: return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__94_28;
}
static void entry__94_27(void) {
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
  // 762: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__94_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 763: !text remaining_text
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[4] /* remaining_text */;
  // 764: ... deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[5] /* indent */;
  result_count = 2;
  myself = get__deserialize_item();
  func = myself->type;
  frame->cont = cont__94_29;
}
static void cont__94_29(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[6] /* temp__1 */ = arguments->slots[1];
  // 764: push &obj deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* obj */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__94_30;
}
static void cont__94_30(void) {
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
static void cont__94_31(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__94_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static VTABLE vtable__types__generic_list = {
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
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function
};

static ATTRIBUTES attributes__types__generic_list = {
  &vtable__types__generic_list,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__generic_list(void) {
  {
    runtime_error("Attempt to call the generic list prototype as a function!");
  }
}
SIMPLE_NODE types__generic_list__node =
  {
    type__types__generic_list,
    &attributes__types__generic_list
  };

static NODE *create__types__generic_list() {
  return (NODE *)&types__generic_list__node;
}

static LIST_DATA *collect_list_data(LIST_DATA *data) {
  if (IS_COLLECTED(data)) {
    void *new_location = *(void **)data;
    if (IS_AN_INVALID_LENGTH(new_location)) return DECODE_FROM_LENGTH(new_location);
    LIST_DATA *new_data = allocate(sizeof(LIST_DATA));
    long n = data->length;
    *(void **)data = ENCODE_TO_LENGTH(new_data);
    new_data->size = n;
    new_data->length = n;
    new_data->items = allocate(n*sizeof(NODE *));
    int i;
    for (i = 0; i < n; ++i) {
      new_data->items[i] = collect_node(data->items[i]);
    }
    return new_data;
  } else if (data && !IS_STATIC(data)) {
    MARK(data)
    int i;
    for (i = 0; i < data->length; ++i) {
      data->items[i] = collect_node(data->items[i]);
    }
  }
  return data;
}
static void *collect_list(LIST *node) {
  LIST *new_node = allocate(sizeof(LIST));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->length = node->length;
  new_node->data = collect_list_data(node->data);
  return new_node;
}

static VTABLE vtable__types__list = {
  sizeof(LIST),
  (COLLECTOR *)&collect_list,
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
  &func__types__list___get_item_of,
  &func__types__list___length_of,
  &func__types__list___unfold,
  &func__types__list___debug_string
};

static ATTRIBUTES attributes__types__list = {
  &vtable__types__list,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

extern void type__types__list(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  long length = myself->list.length;
  long idx = to_long(arguments->slots[0]);
  if (idx < 0) idx = length+idx+1;
  if (idx < 1 || idx > length) {
    invalid_index_error();
  }
  if (argument_count == 1) {
    NODE *result__node = (NODE *)(myself->list.data->items[idx-1]);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  NODE *item = arguments->slots[1];
  LIST_DATA *new_data = allocate_large(sizeof(LIST_DATA)+length*sizeof(NODE *));
  new_data->items = (void *)(new_data+1);
  memcpy(new_data->items, myself->list.data->items, length*sizeof(NODE *));
  new_data->items[idx-1] = item;
  new_data->size = length;
  new_data->length = length;
  {
    NODE *result__node = (NODE *)(create__types__list(length, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
extern NODE *create__types__list(long length, LIST_DATA *data) {
  NODE *node = allocate(sizeof(LIST));
  node->type = type__types__list;
  node->attributes = &attributes__types__list;
  node->list.length = length;
  node->list.data = data;
  return node;
}

NODE *runtime__from_arguments(int first_idx, int count) {
  if (count <= 0) return get__std__empty_list();
  LIST_DATA *data = allocate(sizeof(LIST_DATA));
  data->size = count;
  data->length = count;
  data->items = arguments->slots+first_idx;
  return create__types__list(count, data);
}

static void func__types__list___unfold(NODE *list) {
  int i;
  for (i = 0; i < list->list.length; ++i) {
    arguments->slots[argument_count++] = list->list.data->items[i];
  }
}

static long func__types__list___length_of(NODE *node) {
  return node->list.length;
}

static NODE *func__types__list___get_item_of(NODE *node, long idx) {
  return node->list.data->items[idx];
}
static void entry__14_1_types__list_to_list(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 176: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_1_std__list(void) {
  if (argument_count < 0) {
    too_few_arguments_error();
    return;
  }
  LIST_DATA *data = NULL;
  if (argument_count > 0) {
    node_p += sizeof(FRAME)-sizeof(LIST_DATA);
    data = allocate(sizeof(LIST_DATA)); // <data> replaces the argument list header!
    data->size = argument_count;
    data->length = argument_count;
    data->items = node_p;
    allocate(argument_count*sizeof(NODE *)); // let <node_p> skip the items
  }
  {
    NODE *result__node = (NODE *)(create__types__list(argument_count, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__16_1_types__list_length_of(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_long(arguments->slots[0]->list.length));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__17_1_types__list_push(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *right = arguments->slots[1];
  NODE *left = arguments->slots[0];
  long left_length = left->list.length;
  long new_length = left_length+1;
  LIST_DATA *data = left->list.data;
  if (!data || data->size < new_length || data->length != left_length) {
    long new_size = ALLOCATION_SIZE(2*new_length);
    LIST_DATA *new_data = allocate_large(sizeof(LIST_DATA)+new_size*sizeof(NODE *));
    new_data->items = (void *)(new_data+1);
    if (data) memcpy(new_data->items, data->items, left_length*sizeof(NODE *));
    new_data->size = new_size;
    data = new_data;
  }
  data->items[left_length] = right;
  data->length = new_length;
  {
    NODE *result__node = (NODE *)(create__types__list(new_length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__18_1_types__list_drop(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *list = arguments->slots[0];
  long len = list->list.length;
  if (len == 0) {
    runtime_error("Attempt to drop an element from an empty list!");
  }
  NODE *new_list = create__types__list(len-1, list->list.data);
  {
    NODE *result__node = (NODE *)(create__types__list(len-1, list->list.data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__19_1_types__list_pop(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  if (result_count != 2) {
    runtime_error("Invalid number of expected results!");
  }
  NODE *list = arguments->slots[0];
  long len = list->list.length;
  if (len == 0) {
    runtime_error("Attempt to pop an element from an empty list!");
  }
  NODE *new_list = create__types__list(len-1, list->list.data);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = new_list;
  arguments->slots[1] = list->list.data->items[len-1];
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__20_1_types__list_peek(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *list = arguments->slots[0];
  long len = list->list.length;
  if (len == 0) {
    runtime_error("Attempt to peek an element of an empty list!");
  }
  {
    NODE *result__node = (NODE *)(list->list.data->items[len-1]);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__21_1_types__list_append(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *right = arguments->slots[1];
  if ((right)->type != type__types__list) {
    invalid_arguments_error();
  }
  NODE *left = arguments->slots[0];
  long left_length = left->list.length;
  if (left_length == 0) {
    NODE *result__node = (NODE *)(right);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  long right_length = right->list.length;
  if (right_length == 0) {
    NODE *result__node = (NODE *)(left);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  long new_length = left_length+right_length;
  LIST_DATA *data = left->list.data;
  if (data->size < new_length || data->length != left_length) {
    long new_size = ALLOCATION_SIZE(2*new_length);
    LIST_DATA *new_data = allocate_large(sizeof(LIST_DATA)+new_size*sizeof(NODE *));
    new_data->items = (void *)(new_data+1);
    if (data) memcpy(new_data->items, data->items, left_length*sizeof(NODE *));
    new_data->size = new_size;
    data = new_data;
  }
  memcpy(
    data->items+left_length,
    right->list.data->items,
    right_length*sizeof(NODE *));
  data->length = new_length;
  {
    NODE *result__node = (NODE *)(create__types__list(new_length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__22_1_types__list_range(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  long first_idx = to_long(arguments->slots[1]);
  long last_idx = to_long(arguments->slots[2]);
  long len = self->list.length;
  if (first_idx < 0) first_idx = len+first_idx+1;
  if (last_idx < 0) last_idx = len+last_idx+1;
  if (first_idx < 1 || first_idx > len+1) {
    invalid_index_error();
  }
  if (last_idx < 0 || last_idx > len) {
    invalid_index_error();
  }
  if (first_idx > last_idx+1) {
    invalid_arguments_error();
  }
  if (first_idx == 1 && last_idx == len) {
    NODE *result__node = (NODE *)(self);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  long new_len = last_idx-first_idx+1;
  if (new_len == 0) {
    NODE *result__node = (NODE *)(get__std__empty_list());
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  LIST_DATA *data = self->list.data;
  LIST_DATA *new_data = allocate_large(sizeof(LIST_DATA)+new_len*sizeof(NODE *));
  new_data->items = (void *)(new_data+1);
  memcpy(new_data->items, data->items+first_idx-1, new_len*sizeof(NODE *));
  new_data->size = new_len;
  new_data->length = new_len;
  {
    NODE *result__node = (NODE *)(create__types__list(new_len, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__23_1_types__generic_list_delete_at(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // idx: 1
  // count: 2
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  switch(argument_count) {
    default: frame->slots[2] /* count */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* count */ = number__1;
  }
  // 329: ... count != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* count */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 329: ... count != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__23_3;
}
static void cont__23_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 329: ... : !self append(range(self 1 idx-1) range(self idx+count -1))
  frame->slots[5] /* temp__3 */ = create_closure(entry__23_4, 0);
  // 329: if count != 0: !self append(range(self 1 idx-1) range(self idx+count -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__23_11;
}
static void entry__23_4(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // self: 0
  // idx: 1
  // count: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[2]; /* count */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 329: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__23_5;
}
static void cont__23_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 329: ... range(self 1 idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__23_6;
}
static void cont__23_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 329: ... idx+count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[2] /* count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__23_7;
}
static void cont__23_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 329: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__23_8;
}
static void cont__23_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 329: ... range(self idx+count -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  arguments->slots[2] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__23_9;
}
static void cont__23_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 329: ... !self append(range(self 1 idx-1) range(self idx+count -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__23_10;
}
static void cont__23_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_11(void) {
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
static void entry__24_1_std__normalized_index(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // self: 0
  // idx: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 340: idx >= 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 340: idx >= 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__24_3;
}
static void cont__24_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 340: ... :
  // 341:   return idx
  frame->slots[5] /* temp__3 */ = create_closure(entry__24_4, 0);
  // 342: :
  // 343:   return length_of(self)+1+idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__24_5, 0);
  // 339: if
  // 340:   idx >= 0:
  // 341:     return idx
  // 342:   :
  // 343:     return length_of(self)+1+idx
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_9;
}
static void entry__24_4(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // idx: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 341: return idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_5(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // return: 0
  // self: 1
  // idx: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__24_6;
}
static void cont__24_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 343: ... length_of(self)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__24_7;
}
static void cont__24_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 343: ... length_of(self)+1+idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* idx */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__24_8;
}
static void cont__24_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 343: return length_of(self)+1+idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_9(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__25_1_types__generic_list_is_empty(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 351: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 351: ... length_of(self) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_3;
}
static void cont__25_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 351: -> length_of(self) == 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_7(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // body: 0
  // i: 1
  // self: 2
  // body2: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* self */
  frame->slots[3] = myself->closure.frame->slots[4]; /* body2 */
  frame->slots[4] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 379: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__26_8;
}
static void cont__26_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 379: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__26_9;
}
static void cont__26_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 379: ... :
  // 380:   body i self(i)
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_10, 0);
  // 381: :
  // 382:   body self(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__26_12, 0);
  // 378: if
  // 379:   parameter_count_of(body) == 2:
  // 380:     body i self(i)
  // 381:   :
  // 382:     body self(i)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__26_14;
}
static void entry__26_10(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // i: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 380: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__26_11;
}
static void cont__26_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 380: body i self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_12(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // self: 1
  // i: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 382: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__26_13;
}
static void cont__26_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 382: body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 383: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__26_15;
}
static void cont__26_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 383: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_16, 0);
  // 383: ... body2.is_defined && i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__26_18;
}
static void entry__26_16(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // i: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[4]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__26_17;
}
static void cont__26_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 383: ... i < n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__26_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 383: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__26_19, 0);
  // 383: if body2.is_defined && i < n: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__26_20;
}
static void entry__26_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 384: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__26_21;
}
static void cont__26_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_4(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // body: 2
  // self: 3
  // body2: 4
  frame->slots[0] = myself->closure.frame->slots[6]; /* n */
  frame->slots[1] = myself->closure.frame->slots[5]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* body */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] = myself->closure.frame->slots[4]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 377: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__26_5;
}
static void cont__26_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 377: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__26_6;
}
static void cont__26_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 377: ... :
  // 378:   if
  // 379:     parameter_count_of(body) == 2:
  // 380:       body i self(i)
  // 381:     :
  // 382:       body self(i)
  // 383:   if body2.is_defined && i < n: body2
  // 384:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_7, 0);
  // 377: ... -> i <= n:
  // 378:   if
  // 379:     parameter_count_of(body) == 2:
  // 380:       body i self(i)
  // 381:     :
  // 382:       body self(i)
  // 383:   if body2.is_defined && i < n: body2
  // 384:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_1_types__generic_list_for_each_from_to(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  // body2: 4
  // i: 5
  // n: 6
  frame->slots[5] /* i */ = create_cell();
  frame->slots[6] /* n */ = create_future();
  if (argument_count < 4) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 5) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[4] /* body2 */ = arguments->slots[4];
    case 4:;
  }
  switch(argument_count) {
    case 4: frame->slots[4] /* body2 */ = undefined;
  }
  // 375: $$i normalized_index(self first)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__normalized_index();
  func = myself->type;
  frame->cont = cont__26_2;
}
static void cont__26_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* i */ = arguments->slots[0];
  // 376: $n normalized_index(self last)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* last */;
  result_count = 1;
  myself = get__normalized_index();
  func = myself->type;
  frame->cont = cont__26_3;
}
static void cont__26_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* n */, arguments->slots[0]);
  // 377: ... -> i <= n:
  // 378:   if
  // 379:     parameter_count_of(body) == 2:
  // 380:       body i self(i)
  // 381:     :
  // 382:       body self(i)
  // 383:   if body2.is_defined && i < n: body2
  // 384:   plus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__26_4, 0);
  // 377: while -> i <= n:
  // 378:   if
  // 379:     parameter_count_of(body) == 2:
  // 380:       body i self(i)
  // 381:     :
  // 382:       body self(i)
  // 383:   if body2.is_defined && i < n: body2
  // 384:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__27_7(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // body: 0
  // i: 1
  // self: 2
  // body2: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* self */
  frame->slots[3] = myself->closure.frame->slots[4]; /* body2 */
  frame->slots[4] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 412: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__27_8;
}
static void cont__27_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 412: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__27_9;
}
static void cont__27_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 412: ... :
  // 413:   body i self(i)
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_10, 0);
  // 414: :
  // 415:   body self(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__27_12, 0);
  // 411: if
  // 412:   parameter_count_of(body) == 2:
  // 413:     body i self(i)
  // 414:   :
  // 415:     body self(i)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__27_14;
}
static void entry__27_10(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // i: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 413: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__27_11;
}
static void cont__27_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 413: body i self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__27_12(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // self: 1
  // i: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 415: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__27_13;
}
static void cont__27_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 415: body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 416: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_15;
}
static void cont__27_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 416: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_16, 0);
  // 416: ... body2.is_defined && i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__27_18;
}
static void entry__27_16(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // i: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[4]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__27_17;
}
static void cont__27_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 416: ... i < n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__27_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 416: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__27_19, 0);
  // 416: if body2.is_defined && i < n: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__27_20;
}
static void entry__27_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 417: minus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__27_21;
}
static void cont__27_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_4(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // i: 0
  // n: 1
  // body: 2
  // self: 3
  // body2: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* i */
  frame->slots[1] = myself->closure.frame->slots[6]; /* n */
  frame->slots[2] = myself->closure.frame->slots[3]; /* body */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] = myself->closure.frame->slots[4]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 410: ... i >= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__27_5;
}
static void cont__27_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 410: ... i >= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__27_6;
}
static void cont__27_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 410: ... :
  // 411:   if
  // 412:     parameter_count_of(body) == 2:
  // 413:       body i self(i)
  // 414:     :
  // 415:       body self(i)
  // 416:   if body2.is_defined && i < n: body2
  // 417:   minus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_7, 0);
  // 410: ... -> i >= n:
  // 411:   if
  // 412:     parameter_count_of(body) == 2:
  // 413:       body i self(i)
  // 414:     :
  // 415:       body self(i)
  // 416:   if body2.is_defined && i < n: body2
  // 417:   minus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1_types__generic_list_for_each_from_down_to(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  // body2: 4
  // i: 5
  // n: 6
  frame->slots[5] /* i */ = create_cell();
  frame->slots[6] /* n */ = create_future();
  if (argument_count < 4) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 5) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[4] /* body2 */ = arguments->slots[4];
    case 4:;
  }
  switch(argument_count) {
    case 4: frame->slots[4] /* body2 */ = undefined;
  }
  // 408: $$i normalized_index(self first)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__normalized_index();
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* i */ = arguments->slots[0];
  // 409: $n normalized_index(self last)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* last */;
  result_count = 1;
  myself = get__normalized_index();
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* n */, arguments->slots[0]);
  // 410: ... -> i >= n:
  // 411:   if
  // 412:     parameter_count_of(body) == 2:
  // 413:       body i self(i)
  // 414:     :
  // 415:       body self(i)
  // 416:   if body2.is_defined && i < n: body2
  // 417:   minus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__27_4, 0);
  // 410: while -> i >= n:
  // 411:   if
  // 412:     parameter_count_of(body) == 2:
  // 413:       body i self(i)
  // 414:     :
  // 415:       body self(i)
  // 416:   if body2.is_defined && i < n: body2
  // 417:   minus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_23(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // body: 0
  // self: 1
  // i: 2
  // body2: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[3]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* i */
  frame->slots[3] = myself->closure.frame->slots[4]; /* body2 */
  frame->slots[4] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 446: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__28_24;
}
static void cont__28_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 446: body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__28_25;
}
static void cont__28_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 447: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__28_26;
}
static void cont__28_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 447: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_27, 0);
  // 447: ... body2.is_defined && i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__28_29;
}
static void entry__28_27(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // i: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* i */
  frame->slots[1] = myself->closure.frame->slots[4]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 447: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_28;
}
static void cont__28_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 447: ... i < n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__28_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 447: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_30, 0);
  // 447: if body2.is_defined && i < n: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__28_31;
}
static void entry__28_30(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 447: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__28_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 448: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__28_32;
}
static void cont__28_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_20(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // body: 2
  // self: 3
  // body2: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] = myself->closure.frame->slots[3]; /* self */
  frame->slots[4] = myself->closure.frame->slots[4]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 445: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_21;
}
static void cont__28_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 445: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__28_22;
}
static void cont__28_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 445: ... :
  // 446:   body self(i)
  // 447:   if body2.is_defined && i < n: body2
  // 448:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_23, 0);
  // 445: ... -> i <= n:
  // 446:   body self(i)
  // 447:   if body2.is_defined && i < n: body2
  // 448:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_9(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // body: 0
  // i: 1
  // self: 2
  // body2: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* self */
  frame->slots[3] = myself->closure.frame->slots[4]; /* body2 */
  frame->slots[4] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__28_10;
}
static void cont__28_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 441: body i self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__28_11;
}
static void cont__28_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 442: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__28_12;
}
static void cont__28_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 442: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_13, 0);
  // 442: ... body2.is_defined && i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__28_15;
}
static void entry__28_13(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // i: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[4]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_14;
}
static void cont__28_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 442: ... i < n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__28_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 442: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_16, 0);
  // 442: if body2.is_defined && i < n: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__28_17;
}
static void entry__28_16(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__28_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 443: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__28_18;
}
static void cont__28_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_6(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // body: 2
  // self: 3
  // body2: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] = myself->closure.frame->slots[3]; /* self */
  frame->slots[4] = myself->closure.frame->slots[4]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 440: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_7;
}
static void cont__28_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 440: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__28_8;
}
static void cont__28_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   body i self(i)
  // 442:   if body2.is_defined && i < n: body2
  // 443:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_9, 0);
  // 440: ... -> i <= n:
  // 441:   body i self(i)
  // 442:   if body2.is_defined && i < n: body2
  // 443:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_5(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // n: 0
  // i: 1
  // body: 2
  // self: 3
  // body2: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* n */
  frame->slots[1] = myself->closure.frame->slots[3]; /* i */
  frame->slots[2] = myself->closure.frame->slots[1]; /* body */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] = myself->closure.frame->slots[2]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 440: ... -> i <= n:
  // 441:   body i self(i)
  // 442:   if body2.is_defined && i < n: body2
  // 443:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__28_6, 0);
  // 440: while -> i <= n:
  // 441:   body i self(i)
  // 442:   if body2.is_defined && i < n: body2
  // 443:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_19(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // n: 0
  // i: 1
  // body: 2
  // self: 3
  // body2: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* n */
  frame->slots[1] = myself->closure.frame->slots[3]; /* i */
  frame->slots[2] = myself->closure.frame->slots[1]; /* body */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] = myself->closure.frame->slots[2]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 445: ... -> i <= n:
  // 446:   body self(i)
  // 447:   if body2.is_defined && i < n: body2
  // 448:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__28_20, 0);
  // 445: while -> i <= n:
  // 446:   body self(i)
  // 447:   if body2.is_defined && i < n: body2
  // 448:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_1_types__generic_list_for_each(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // self: 0
  // body: 1
  // body2: 2
  // i: 3
  // n: 4
  frame->slots[3] /* i */ = create_cell();
  frame->slots[4] /* n */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* body2 */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* body2 */ = undefined;
  }
  // 436: $$i 1
  ((CELL *)frame->slots[3])->contents /* i */ = number__1;
  // 437: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__28_2;
}
static void cont__28_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* n */, arguments->slots[0]);
  // 439: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__28_3;
}
static void cont__28_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 439: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_4;
}
static void cont__28_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 439: ... :
  // 440:   while -> i <= n:
  // 441:     body i self(i)
  // 442:     if body2.is_defined && i < n: body2
  // 443:     plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_5, 0);
  // 444: :
  // 445:   while -> i <= n:
  // 446:     body self(i)
  // 447:     if body2.is_defined && i < n: body2
  // 448:     plus &i 1
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_19, 0);
  // 438: if
  // 439:   parameter_count_of(body) == 2:
  // 440:     while -> i <= n:
  // 441:       body i self(i)
  // 442:       if body2.is_defined && i < n: body2
  // 443:       plus &i 1
  // 444:   :
  // 445:     while -> i <= n:
  // 446:       body self(i)
  // 447:       if body2.is_defined && i < n: body2
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_1_types__generic_list_update_each(void) {
  allocate_initialized_frame_gc(3, 11);
  // slot allocations:
  // self: 0
  // body: 1
  // return: 2
  // update_item: 3
  // i: 4
  // n: 5
  // new_list: 6
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* update_item */ = create_future();
  frame->slots[4] /* i */ = create_cell();
  frame->slots[5] /* n */ = create_future();
  frame->slots[6] /* new_list */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 474: ... : (new_item)
  // 475:   if new_item.is_defined:
  // 476:     if
  // 477:       new_item.is_a_sequence:
  // 478:         append &new_list new_item
  // 479:       :
  // 480:         push &new_list new_item
  // 481:   plus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__29_2_update_item, 1);
  // 474: $update_item: (new_item)
  // 475:   if new_item.is_defined:
  // 476:     if
  // 477:       new_item.is_a_sequence:
  // 478:         append &new_list new_item
  // 479:       :
  // 480:         push &new_list new_item
  // 481:   plus &i 1
  initialize_future(frame->slots[3] /* update_item */, frame->slots[7] /* temp__1 */);
  // 483: $$i 1
  ((CELL *)frame->slots[4])->contents /* i */ = number__1;
  // 484: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__29_12;
}
static void entry__29_2_update_item(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // new_item: 0
  // new_list: 1
  // i: 2
  frame->slots[1] = myself->closure.frame->slots[6]; /* new_list */
  frame->slots[2] = myself->closure.frame->slots[4]; /* i */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 475: ... new_item.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* new_item */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_3;
}
static void cont__29_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 475: ... :
  // 476:   if
  // 477:     new_item.is_a_sequence:
  // 478:       append &new_list new_item
  // 479:     :
  // 480:       push &new_list new_item
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_4, 0);
  // 475: if new_item.is_defined:
  // 476:   if
  // 477:     new_item.is_a_sequence:
  // 478:       append &new_list new_item
  // 479:     :
  // 480:       push &new_list new_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_10;
}
static void entry__29_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // new_list: 0
  // new_item: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_list */
  frame->slots[1] = myself->closure.frame->slots[0]; /* new_item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 478: append &new_list new_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_list */;
  arguments->slots[1] = frame->slots[1] /* new_item */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__29_7;
}
static void cont__29_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_list */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // new_list: 0
  // new_item: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_list */
  frame->slots[1] = myself->closure.frame->slots[0]; /* new_item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 480: push &new_list new_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_list */;
  arguments->slots[1] = frame->slots[1] /* new_item */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_9;
}
static void cont__29_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_list */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_4(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // new_item: 0
  // new_list: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* new_item */
  frame->slots[1] = myself->closure.frame->slots[1]; /* new_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 477: new_item.is_a_sequence
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* new_item */;
  result_count = 1;
  myself = get__is_a_sequence();
  func = myself->type;
  frame->cont = cont__29_5;
}
static void cont__29_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 477: ... :
  // 478:   append &new_list new_item
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_6, 0);
  // 479: :
  // 480:   push &new_list new_item
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_8, 0);
  // 476: if
  // 477:   new_item.is_a_sequence:
  // 478:     append &new_list new_item
  // 479:   :
  // 480:     push &new_list new_item
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 481: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__29_11;
}
static void cont__29_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* n */, arguments->slots[0]);
  // 485: $$new_list types::list
  ((CELL *)frame->slots[6])->contents /* new_list */ = var.types__list;
  // 487: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__29_13;
}
static void cont__29_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 487: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_14;
}
static void cont__29_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 487: ... :
  // 488:   while -> i <= n: update_item body(i self(i))
  frame->slots[9] /* temp__3 */ = create_closure(entry__29_15, 0);
  // 489: :
  // 490:   while -> i <= n: update_item body(self(i))
  frame->slots[10] /* temp__4 */ = create_closure(entry__29_22, 0);
  // 486: if
  // 487:   parameter_count_of(body) == 2:
  // 488:     while -> i <= n: update_item body(i self(i))
  // 489:   :
  // 490:     while -> i <= n: update_item body(self(i))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  arguments->slots[2] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_29;
}
static void entry__29_26(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // update_item: 0
  // body: 1
  // self: 2
  // i: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* update_item */
  frame->slots[1] = myself->closure.frame->slots[3]; /* body */
  frame->slots[2] = myself->closure.frame->slots[4]; /* self */
  frame->slots[3] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 490: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__29_27;
}
static void cont__29_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 490: ... body(self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__29_28;
}
static void cont__29_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 490: ... update_item body(self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* update_item */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_23(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // update_item: 2
  // body: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* update_item */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[4]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 490: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__29_24;
}
static void cont__29_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 490: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__29_25;
}
static void cont__29_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 490: ... : update_item body(self(i))
  frame->slots[7] /* temp__3 */ = create_closure(entry__29_26, 0);
  // 490: ... -> i <= n: update_item body(self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_19(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // update_item: 0
  // body: 1
  // i: 2
  // self: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* update_item */
  frame->slots[1] = myself->closure.frame->slots[3]; /* body */
  frame->slots[2] = myself->closure.frame->slots[1]; /* i */
  frame->slots[3] = myself->closure.frame->slots[4]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 488: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[3] /* self */;
  func = myself->type;
  frame->cont = cont__29_20;
}
static void cont__29_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 488: ... body(i self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__29_21;
}
static void cont__29_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 488: ... update_item body(i self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* update_item */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_16(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // update_item: 2
  // body: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* update_item */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[4]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 488: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__29_17;
}
static void cont__29_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 488: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__29_18;
}
static void cont__29_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 488: ... : update_item body(i self(i))
  frame->slots[7] /* temp__3 */ = create_closure(entry__29_19, 0);
  // 488: ... -> i <= n: update_item body(i self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_15(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // n: 0
  // i: 1
  // update_item: 2
  // body: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* n */
  frame->slots[1] = myself->closure.frame->slots[4]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* update_item */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 488: ... -> i <= n: update_item body(i self(i))
  frame->slots[5] /* temp__1 */ = create_closure(entry__29_16, 0);
  // 488: while -> i <= n: update_item body(i self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_22(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // n: 0
  // i: 1
  // update_item: 2
  // body: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* n */
  frame->slots[1] = myself->closure.frame->slots[4]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* update_item */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 490: ... -> i <= n: update_item body(self(i))
  frame->slots[5] /* temp__1 */ = create_closure(entry__29_23, 0);
  // 490: while -> i <= n: update_item body(self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 491: return new_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* new_list */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = cont__29_30;
}
static void cont__29_30(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__30_13(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // self: 1
  // i: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[2]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 509: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__30_14;
}
static void cont__30_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 509: ... body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_1_types__list_for_each_pair(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // body: 1
  // i: 2
  // n: 3
  frame->slots[2] /* i */ = create_cell();
  frame->slots[3] /* n */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 504: $$i 1
  ((CELL *)frame->slots[2])->contents /* i */ = number__1;
  // 505: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__30_2;
}
static void cont__30_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 506: ... -> i < n:
  // 507:   body self(i) self(i+1)
  // 508:   plus &i 2
  frame->slots[4] /* temp__1 */ = create_closure(entry__30_3, 0);
  // 506: while -> i < n:
  // 507:   body self(i) self(i+1)
  // 508:   plus &i 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__30_11;
}
static void entry__30_5(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // body: 0
  // self: 1
  // i: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[3]; /* self */
  frame->slots[2] = myself->closure.frame->slots[0]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 507: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__30_6;
}
static void cont__30_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 507: ... i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__30_7;
}
static void cont__30_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 507: ... self(i+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__30_8;
}
static void cont__30_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 507: body self(i) self(i+1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__30_9;
}
static void cont__30_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 508: plus &i 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__30_10;
}
static void cont__30_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_3(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // i: 0
  // n: 1
  // body: 2
  // self: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* i */
  frame->slots[1] = myself->closure.frame->slots[3]; /* n */
  frame->slots[2] = myself->closure.frame->slots[1]; /* body */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 506: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__30_4;
}
static void cont__30_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 506: ... :
  // 507:   body self(i) self(i+1)
  // 508:   plus &i 2
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_5, 0);
  // 506: ... -> i < n:
  // 507:   body self(i) self(i+1)
  // 508:   plus &i 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 509: ... is_odd(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__30_12;
}
static void cont__30_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 509: ... : body self(i)
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_13, 0);
  // 509: if is_odd(n): body self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__31_1_types__generic_list_get(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 517: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__31_2;
}
static void cont__31_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 517: ... length_of(self) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__31_3;
}
static void cont__31_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 517: if length_of(self) == 0: raise "Attempt to get an element from an empty list!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__31_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__31_6;
}
static void entry__31_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 517: ... raise "Attempt to get an element from an empty list!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__57ec57a17085427f;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__31_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 518: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__31_7;
}
static void cont__31_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 518: ... range(self 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__31_8;
}
static void cont__31_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 518: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__31_9;
}
static void cont__31_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 518: -> range(self 2 -1) self(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__32_1_types__list_put(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // item: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 527: ... list(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__32_2;
}
static void cont__32_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 527: ... append(list(item) self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__32_3;
}
static void cont__32_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 527: -> append(list(item) self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_1_types__list_merge(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // left: 0
  // right: 1
  // func: 2
  // return: 3
  // result: 4
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* result */ = create_cell();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  frame->slots[0] /* left */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* right */ = create_cell_with_contents(arguments->slots[1]);
  switch(argument_count) {
    default: frame->slots[2] /* func */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* func */ = undefined;
  }
  // 538: $$result list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__33_2;
}
static void cont__33_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* result */ = arguments->slots[0];
  // 539: ... :
  // 540:   if
  // 541:     length_of(left) > 0:
  // 542:       if
  // 543:         length_of(right) > 0:
  // 544:           if
  // 545:             ||
  // 546:               func.is_undefined && left(1) <= right(1)
  // 547:               func.is_defined && not(func(right(1) left(1)))
  // 548:             :
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__33_3, 0);
  // 539: forever:
  // 540:   if
  // 541:     length_of(left) > 0:
  // 542:       if
  // 543:         length_of(right) > 0:
  // 544:           if
  // 545:             ||
  // 546:               func.is_undefined && left(1) <= right(1)
  // 547:               func.is_defined && not(func(right(1) left(1)))
  // 548:             :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__33_36;
}
static void entry__33_26(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // result: 0
  // left: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* result */
  frame->slots[1] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 549: ... get(&left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* left */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__33_27;
}
static void cont__33_27(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* left */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 549: push &result get(&left)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_28;
}
static void cont__33_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_29(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // result: 0
  // right: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* result */
  frame->slots[1] = myself->closure.frame->slots[1]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 551: ... get(&right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* right */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__33_30;
}
static void cont__33_30(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* right */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 551: push &result get(&right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_31;
}
static void cont__33_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_9(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // func: 0
  // right: 1
  // left: 2
  // result: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* func */
  frame->slots[1] = myself->closure.frame->slots[0]; /* right */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  frame->slots[3] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 546: func.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__33_10;
}
static void cont__33_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 546: ... left(1) <= right(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__33_11, 0);
  // 546: func.is_undefined && left(1) <= right(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__33_16;
}
static void entry__33_11(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // right: 0
  // left: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* right */
  frame->slots[1] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 546: ... right(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* right */;
  func = myself->type;
  frame->cont = cont__33_12;
}
static void cont__33_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 546: ... left(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* left */;
  func = myself->type;
  frame->cont = cont__33_13;
}
static void cont__33_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 546: ... left(1) <= right(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__33_14;
}
static void cont__33_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 546: ... left(1) <= right(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__33_15;
}
static void cont__33_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 546: ... left(1) <= right(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 547: func.is_defined && not(func(right(1) left(1)))
  frame->slots[8] /* temp__5 */ = create_closure(entry__33_17, 0);
  // 545: ||
  // 546:   func.is_undefined && left(1) <= right(1)
  // 547:   func.is_defined && not(func(right(1) left(1)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__33_25;
}
static void entry__33_17(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // func: 0
  // right: 1
  // left: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* func */
  frame->slots[1] = myself->closure.frame->slots[1]; /* right */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 547: func.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_18;
}
static void cont__33_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 547: ... not(func(right(1) left(1)))
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_19, 0);
  // 547: func.is_defined && not(func(right(1) left(1)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__33_24;
}
static void entry__33_19(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // func: 0
  // right: 1
  // left: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* func */
  frame->slots[1] = myself->closure.frame->slots[1]; /* right */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 547: ... right(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* right */;
  func = myself->type;
  frame->cont = cont__33_20;
}
static void cont__33_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 547: ... left(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* left */;
  func = myself->type;
  frame->cont = cont__33_21;
}
static void cont__33_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 547: ... func(right(1) left(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__33_22;
}
static void cont__33_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 547: ... not(func(right(1) left(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__33_23;
}
static void cont__33_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 547: ... not(func(right(1) left(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 547: func.is_defined && not(func(right(1) left(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 548: :
  // 549:   push &result get(&left)
  frame->slots[9] /* temp__6 */ = create_closure(entry__33_26, 0);
  // 550: :
  // 551:   push &result get(&right)
  frame->slots[10] /* temp__7 */ = create_closure(entry__33_29, 0);
  // 544: if
  // 545:   ||
  // 546:     func.is_undefined && left(1) <= right(1)
  // 547:     func.is_defined && not(func(right(1) left(1)))
  // 548:   :
  // 549:     push &result get(&left)
  // 550:   :
  // 551:     push &result get(&right)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  arguments->slots[2] = frame->slots[10] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_32(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // result: 1
  // left: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* result */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 553: ... append(result left)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* left */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__33_33;
}
static void cont__33_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 553: return append(result left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_6(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // right: 0
  // func: 1
  // left: 2
  // result: 3
  // return: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* right */
  frame->slots[1] = myself->closure.frame->slots[2]; /* func */
  frame->slots[2] = myself->closure.frame->slots[0]; /* left */
  frame->slots[3] = myself->closure.frame->slots[3]; /* result */
  frame->slots[4] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 543: length_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__33_7;
}
static void cont__33_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 543: length_of(right) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__33_8;
}
static void cont__33_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 543: ... :
  // 544:   if
  // 545:     ||
  // 546:       func.is_undefined && left(1) <= right(1)
  // 547:       func.is_defined && not(func(right(1) left(1)))
  // 548:     :
  // 549:       push &result get(&left)
  // 550:     :
  // 551:       push &result get(&right)
  frame->slots[7] /* temp__3 */ = create_closure(entry__33_9, 0);
  // 552: :
  // 553:   return append(result left)
  frame->slots[8] /* temp__4 */ = create_closure(entry__33_32, 0);
  // 542: if
  // 543:   length_of(right) > 0:
  // 544:     if
  // 545:       ||
  // 546:         func.is_undefined && left(1) <= right(1)
  // 547:         func.is_defined && not(func(right(1) left(1)))
  // 548:       :
  // 549:         push &result get(&left)
  // 550:       :
  // 551:         push &result get(&right)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_34(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // result: 1
  // right: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* result */
  frame->slots[2] = myself->closure.frame->slots[1]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 555: ... append(result right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* right */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__33_35;
}
static void cont__33_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 555: return append(result right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_3(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // left: 0
  // right: 1
  // func: 2
  // result: 3
  // return: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* left */
  frame->slots[1] = myself->closure.frame->slots[1]; /* right */
  frame->slots[2] = myself->closure.frame->slots[2]; /* func */
  frame->slots[3] = myself->closure.frame->slots[4]; /* result */
  frame->slots[4] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 541: length_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__33_4;
}
static void cont__33_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 541: length_of(left) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__33_5;
}
static void cont__33_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 541: ... :
  // 542:   if
  // 543:     length_of(right) > 0:
  // 544:       if
  // 545:         ||
  // 546:           func.is_undefined && left(1) <= right(1)
  // 547:           func.is_defined && not(func(right(1) left(1)))
  // 548:         :
  // 549:           push &result get(&left)
  // 550:         :
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__33_6, 0);
  // 554: :
  // 555:   return append(result right)
  frame->slots[8] /* temp__4 */ = create_closure(entry__33_34, 0);
  // 540: if
  // 541:   length_of(left) > 0:
  // 542:     if
  // 543:       length_of(right) > 0:
  // 544:         if
  // 545:           ||
  // 546:             func.is_undefined && left(1) <= right(1)
  // 547:             func.is_defined && not(func(right(1) left(1)))
  // 548:           :
  // 549:             push &result get(&left)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_36(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__34_1_types__list_serialize(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // indent: 1
  // return: 2
  // buf: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* buf */ = create_cell();
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
  // 565: ... self.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_2;
}
static void cont__34_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 565: ... : return "list()"
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_3, 0);
  // 565: if self.is_empty: return "list()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_5;
}
static void entry__34_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 565: ... return "list()"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7e1f534683fac2fe;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 566: $$buf "list"
  ((CELL *)frame->slots[3])->contents /* buf */ = string__1a0aeb0b5df87d4d;
  // 567: ... : (item)
  // 568:   write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
  frame->slots[4] /* temp__1 */ = create_closure(entry__34_7, 1);
  // 567: for_each self: (item)
  // 568:   write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_13;
}
static void entry__34_7(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // item: 0
  // buf: 1
  // indent: 2
  frame->slots[1] = myself->closure.frame->slots[3]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[1]; /* indent */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 568: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_8;
}
static void cont__34_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 568: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__34_9;
}
static void cont__34_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 568: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_10;
}
static void cont__34_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 568: ... serialize(item indent+2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__34_11;
}
static void cont__34_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 568: write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = character__10;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__34_12;
}
static void cont__34_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 569: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__35_1_types__list_sort(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // self: 0
  // func: 1
  // return: 2
  // n: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* n */ = create_future();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* func */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* func */ = undefined;
  }
  // 582: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__35_2;
}
static void cont__35_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 585: 0, 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = var.std__sequence;
  func = myself->type;
  frame->cont = cont__35_3;
}
static void cont__35_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 585: ... :
  // 586:   return self
  frame->slots[5] /* temp__2 */ = create_closure(entry__35_4, 0);
  // 587: ... :
  // 588:   if
  // 589:     ||
  // 590:       func.is_undefined && self(1) <= self(2)
  // 591:       func.is_defined && not(func(self(2) self(1)))
  // 592:     :
  // 593:       return self
  // 594:     :
  // 595:       return list(self(2) self(1))
  frame->slots[6] /* temp__3 */ = create_closure(entry__35_5, 0);
  // 596: :
  // 597:   $m n .div. 2
  // 598:   if
  // 599:     func.is_undefined:
  // 600:       return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  // 601:     :
  // 602:       return
  // 603:         merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  frame->slots[7] /* temp__4 */ = create_closure(entry__35_27, 0);
  // 583: case
  // 584:   n
  // 585:   0, 1:
  // 586:     return self
  // 587:   2:
  // 588:     if
  // 589:       ||
  // 590:         func.is_undefined && self(1) <= self(2)
  // 591:         func.is_defined && not(func(self(2) self(1)))
  // 592:       :
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  arguments->slots[3] = number__2;
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  arguments->slots[5] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__35_44;
}
static void entry__35_30(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // return: 0
  // self: 1
  // m: 2
  // n: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* self */
  frame->slots[2] = myself->closure.frame->slots[4]; /* m */
  frame->slots[3] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 600: ... range(self 1 m)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_31;
}
static void cont__35_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 600: ... sort(range(self 1 m))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__35_32;
}
static void cont__35_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 600: ... m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* m */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__35_33;
}
static void cont__35_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 600: ... range(self m+1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  arguments->slots[2] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_34;
}
static void cont__35_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 600: ... sort(range(self m+1 n))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__35_35;
}
static void cont__35_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 600: ... merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__merge();
  func = myself->type;
  frame->cont = cont__35_36;
}
static void cont__35_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 600: return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_37(void) {
  allocate_initialized_frame_gc(5, 11);
  // slot allocations:
  // return: 0
  // self: 1
  // m: 2
  // func: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* self */
  frame->slots[2] = myself->closure.frame->slots[4]; /* m */
  frame->slots[3] = myself->closure.frame->slots[1]; /* func */
  frame->slots[4] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 603: ... range(self 1 m)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_38;
}
static void cont__35_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 603: ... sort(range(self 1 m) func)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[3] /* func */;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__35_39;
}
static void cont__35_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 603: ... m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* m */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__35_40;
}
static void cont__35_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 603: ... range(self m+1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[10] /* temp__6 */;
  arguments->slots[2] = frame->slots[4] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_41;
}
static void cont__35_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 603: ... sort(range(self m+1 n) func)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* func */;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__35_42;
}
static void cont__35_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 603: merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = frame->slots[3] /* func */;
  result_count = 1;
  myself = get__merge();
  func = myself->type;
  frame->cont = cont__35_43;
}
static void cont__35_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 602: return
  // 603:   merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_22(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: return self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_23(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // return: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 595: ... self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__35_24;
}
static void cont__35_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 595: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__35_25;
}
static void cont__35_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 595: ... list(self(2) self(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__35_26;
}
static void cont__35_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 595: return list(self(2) self(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_4(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 586: return self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_5(void) {
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // func: 0
  // self: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* func */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 590: func.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__35_6;
}
static void cont__35_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 590: ... self(1) <= self(2)
  frame->slots[6] /* temp__4 */ = create_closure(entry__35_7, 0);
  // 590: func.is_undefined && self(1) <= self(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__35_12;
}
static void entry__35_7(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 590: ... self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__35_8;
}
static void cont__35_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 590: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__35_9;
}
static void cont__35_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 590: ... self(1) <= self(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__35_10;
}
static void cont__35_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 590: ... self(1) <= self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__35_11;
}
static void cont__35_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 590: ... self(1) <= self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 591: func.is_defined && not(func(self(2) self(1)))
  frame->slots[7] /* temp__5 */ = create_closure(entry__35_13, 0);
  // 589: ||
  // 590:   func.is_undefined && self(1) <= self(2)
  // 591:   func.is_defined && not(func(self(2) self(1)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__35_21;
}
static void entry__35_13(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // func: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* func */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 591: func.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__35_14;
}
static void cont__35_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 591: ... not(func(self(2) self(1)))
  frame->slots[4] /* temp__3 */ = create_closure(entry__35_15, 0);
  // 591: func.is_defined && not(func(self(2) self(1)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__35_20;
}
static void entry__35_15(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // func: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* func */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 591: ... self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__35_16;
}
static void cont__35_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 591: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__35_17;
}
static void cont__35_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 591: ... func(self(2) self(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__35_18;
}
static void cont__35_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 591: ... not(func(self(2) self(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__35_19;
}
static void cont__35_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 591: ... not(func(self(2) self(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 591: func.is_defined && not(func(self(2) self(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 592: :
  // 593:   return self
  frame->slots[8] /* temp__6 */ = create_closure(entry__35_22, 0);
  // 594: :
  // 595:   return list(self(2) self(1))
  frame->slots[9] /* temp__7 */ = create_closure(entry__35_23, 0);
  // 588: if
  // 589:   ||
  // 590:     func.is_undefined && self(1) <= self(2)
  // 591:     func.is_defined && not(func(self(2) self(1)))
  // 592:   :
  // 593:     return self
  // 594:   :
  // 595:     return list(self(2) self(1))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  arguments->slots[2] = frame->slots[9] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_27(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // n: 0
  // func: 1
  // return: 2
  // self: 3
  // m: 4
  frame->slots[0] = myself->closure.frame->slots[3]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* func */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] /* m */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 597: $m n .div. 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__35_28;
}
static void cont__35_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* m */, arguments->slots[0]);
  // 599: func.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* func */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__35_29;
}
static void cont__35_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 599: ... :
  // 600:   return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  frame->slots[6] /* temp__2 */ = create_closure(entry__35_30, 0);
  // 601: :
  // 602:   return
  // 603:     merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  frame->slots[7] /* temp__3 */ = create_closure(entry__35_37, 0);
  // 598: if
  // 599:   func.is_undefined:
  // 600:     return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  // 601:   :
  // 602:     return
  // 603:       merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__35_44(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}

static long func__types__list___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  if (node->list.length == 0) {
    return debug_print(indent, buf, "empty_list", node);
  } else {
    if (max_depth <= 1) {
      if (node->list.length == 1) {
        return debug_print(indent, buf, "<list of 1 item>", node);
      } else {
        return debug_print(indent, buf, "<list of %ld items>", node->list.length);
      }
    } else {
      long i, n, len;
      n = debug_print_head(&indent, &buf, "list");
      const char *contents_indent = indent_to_string(indent);
      for (i = 0; i < node->list.length; ++i) {
        n += print(&buf, contents_indent);
        len = debug_string(node->list.data->items[i], indent, max_depth-1, buf);
        if (buf) buf += len;
        n += len;
      }
      return n;
    }
  }
}
static void entry__37_1_types__list_new_empty_collection(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 640: -> types::list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__list;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_1_types__generic_list_equal(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // left: 0
  // right: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 652: ... right.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_2;
}
static void cont__38_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 652: ... right.is_a_list
  frame->slots[5] /* temp__3 */ = create_closure(entry__38_3, 0);
  // 652: ... right.is_defined && right.is_a_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_5;
}
static void entry__38_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // right: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 652: ... right.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* right */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__38_4;
}
static void cont__38_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 652: ... right.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 652: ... : return false
  frame->slots[6] /* temp__4 */ = create_closure(entry__38_6, 0);
  // 652: unless right.is_defined && right.is_a_list: return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__38_7;
}
static void entry__38_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 652: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 653: ... length_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__38_8;
}
static void cont__38_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 653: ... length_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__38_9;
}
static void cont__38_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 653: ... length_of(left) != length_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_10;
}
static void cont__38_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 653: ... length_of(left) != length_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__38_11;
}
static void cont__38_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 653: ... : return false
  frame->slots[7] /* temp__5 */ = create_closure(entry__38_12, 0);
  // 653: if length_of(left) != length_of(right): return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_13;
}
static void entry__38_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 653: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 654: ... : (idx item) if item != right(idx): return false
  frame->slots[3] /* temp__1 */ = create_closure(entry__38_14, 2);
  // 654: for_each left: (idx item) if item != right(idx): return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_19;
}
static void entry__38_18(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 654: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_14(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // idx: 0
  // item: 1
  // right: 2
  // return: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* right */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 654: ... right(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = frame->slots[2] /* right */;
  func = myself->type;
  frame->cont = cont__38_15;
}
static void cont__38_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 654: ... item != right(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_16;
}
static void cont__38_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 654: ... item != right(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__38_17;
}
static void cont__38_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 654: ... : return false
  frame->slots[7] /* temp__4 */ = create_closure(entry__38_18, 0);
  // 654: ... if item != right(idx): return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 655: -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__39_1_types__generic_list_filter(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // test: 1
  // new_list: 2
  frame->slots[2] /* new_list */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 664: $$new_list new_empty_collection(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__new_empty_collection();
  func = myself->type;
  frame->cont = cont__39_2;
}
static void cont__39_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* new_list */ = arguments->slots[0];
  // 665: ... : (item) if test(item): push &new_list item
  frame->slots[3] /* temp__1 */ = create_closure(entry__39_3, 1);
  // 665: for_each self: (item) if test(item): push &new_list item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__39_7;
}
static void entry__39_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // new_list: 0
  // item: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* new_list */
  frame->slots[1] = myself->closure.frame->slots[0]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 665: ... push &new_list item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_list */;
  arguments->slots[1] = frame->slots[1] /* item */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__39_6;
}
static void cont__39_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_list */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_3(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // item: 0
  // test: 1
  // new_list: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* test */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_list */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 665: ... test(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[1] /* test */;
  func = myself->type;
  frame->cont = cont__39_4;
}
static void cont__39_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 665: ... : push &new_list item
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_5, 0);
  // 665: ... if test(item): push &new_list item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 666: -> new_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_list */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__40_1_types__generic_list_map(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // func: 1
  // new_list: 2
  frame->slots[2] /* new_list */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 677: $$new_list new_empty_collection(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__new_empty_collection();
  func = myself->type;
  frame->cont = cont__40_2;
}
static void cont__40_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* new_list */ = arguments->slots[0];
  // 678: ... : (item) push &new_list func(item)
  frame->slots[3] /* temp__1 */ = create_closure(entry__40_3, 1);
  // 678: for_each self: (item) push &new_list func(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__40_6;
}
static void entry__40_3(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // item: 0
  // new_list: 1
  // func: 2
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_list */
  frame->slots[2] = myself->closure.frame->slots[1]; /* func */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 678: ... func(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[2] /* func */;
  func = myself->type;
  frame->cont = cont__40_4;
}
static void cont__40_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 678: ... push &new_list func(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_list */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__40_5;
}
static void cont__40_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* new_list */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__40_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 679: -> new_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_list */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 688: ... -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // n: 0
  // self: 1
  // result: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* n */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] /* result */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 689: ... n < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__41_4;
}
static void cont__41_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 689: if n < 0: raise "Negative argument for dup!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__41_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__41_7;
}
static void entry__41_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 689: ... raise "Negative argument for dup!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__963fa2c6021831d1;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__41_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 690: ... n .div. 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__41_8;
}
static void cont__41_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 690: $$result dup(self n .div. 2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__41_9;
}
static void cont__41_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  // 691: append &result result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* result */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__41_10;
}
static void cont__41_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  // 692: ... n.is_odd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__41_11;
}
static void cont__41_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 692: ... : append &result self
  frame->slots[4] /* temp__2 */ = create_closure(entry__41_12, 0);
  // 692: if n.is_odd: append &result self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__41_14;
}
static void entry__41_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // result: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* result */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 692: ... append &result self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[1] /* self */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__41_13;
}
static void cont__41_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__41_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 693: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 688: ... -> empty_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_1_types__generic_list_dup(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // n: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 688: ... -> self
  frame->slots[2] /* temp__1 */ = create_closure(entry__41_2, 0);
  // 688: ... :
  // 689:   if n < 0: raise "Negative argument for dup!"
  // 690:   $$result dup(self n .div. 2)
  // 691:   append &result result
  // 692:   if n.is_odd: append &result self
  // 693:   -> result
  frame->slots[3] /* temp__2 */ = create_closure(entry__41_3, 0);
  // 688: case n 0 (-> empty_list) 1 (-> self):
  // 689:   if n < 0: raise "Negative argument for dup!"
  // 690:   $$result dup(self n .div. 2)
  // 691:   append &result result
  // 692:   if n.is_odd: append &result self
  // 693:   -> result
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = func__41_15;
  arguments->slots[3] = number__1;
  arguments->slots[4] = frame->slots[2] /* temp__1 */;
  arguments->slots[5] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__42_1_types__generic_list_interleave(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // lists: 0
  // n: 1
  // result: 2
  frame->slots[1] /* n */ = create_future();
  frame->slots[2] /* result */ = create_cell();
  frame->slots[0] /* lists */ = from_arguments(0, argument_count-0);
  // 704: ... lists(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* lists */;
  func = myself->type;
  frame->cont = cont__42_2;
}
static void cont__42_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 704: $n length_of(lists(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__42_3;
}
static void cont__42_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* n */, arguments->slots[0]);
  // 705: $$result empty_list
  ((CELL *)frame->slots[2])->contents /* result */ = get__empty_list();
  // 706: ... n-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__42_4;
}
static void cont__42_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 706: ... : (i) for_each lists: (current_list) push &result current_list(i)
  frame->slots[4] /* temp__2 */ = create_closure(entry__42_5, 1);
  // 706: from_to 1 n-1: (i) for_each lists: (current_list) push &result current_list(i)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__42_9;
}
static void entry__42_6(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // current_list: 0
  // result: 1
  // i: 2
  frame->slots[1] = myself->closure.frame->slots[2]; /* result */
  frame->slots[2] = myself->closure.frame->slots[0]; /* i */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 706: ... current_list(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  result_count = 1;
  myself = frame->slots[0] /* current_list */;
  func = myself->type;
  frame->cont = cont__42_7;
}
static void cont__42_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 706: ... push &result current_list(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__42_8;
}
static void cont__42_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__42_5(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // i: 0
  // lists: 1
  // result: 2
  frame->slots[1] = myself->closure.frame->slots[0]; /* lists */
  frame->slots[2] = myself->closure.frame->slots[2]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 706: ... : (current_list) push &result current_list(i)
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_6, 1);
  // 706: ... for_each lists: (current_list) push &result current_list(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* lists */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__42_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 707: ... : (current_list)
  // 708:   if length_of(current_list) >= n: push &result current_list(n)
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_10, 1);
  // 707: for_each lists: (current_list)
  // 708:   if length_of(current_list) >= n: push &result current_list(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lists */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__42_17;
}
static void entry__42_14(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // result: 0
  // current_list: 1
  // n: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* result */
  frame->slots[1] = myself->closure.frame->slots[0]; /* current_list */
  frame->slots[2] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 708: ... current_list(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  result_count = 1;
  myself = frame->slots[1] /* current_list */;
  func = myself->type;
  frame->cont = cont__42_15;
}
static void cont__42_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 708: ... push &result current_list(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__42_16;
}
static void cont__42_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__42_10(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // current_list: 0
  // n: 1
  // result: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  frame->slots[2] = myself->closure.frame->slots[2]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 708: ... length_of(current_list)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* current_list */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__42_11;
}
static void cont__42_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 708: ... length_of(current_list) >= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__42_12;
}
static void cont__42_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 708: ... length_of(current_list) >= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__42_13;
}
static void cont__42_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 708: ... : push &result current_list(n)
  frame->slots[6] /* temp__4 */ = create_closure(entry__42_14, 0);
  // 708: if length_of(current_list) >= n: push &result current_list(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__42_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 709: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_1_types__generic_list_contains(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // self: 0
  // item: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 719: ... : (current_item) if current_item == item: return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__43_2, 1);
  // 719: for_each self: (current_item) if current_item == item: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__43_5;
}
static void entry__43_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__43_2(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // current_item: 0
  // item: 1
  // return: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* item */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 719: ... current_item == item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* current_item */;
  arguments->slots[1] = frame->slots[1] /* item */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__43_3;
}
static void cont__43_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 719: ... : return true
  frame->slots[4] /* temp__2 */ = create_closure(entry__43_4, 0);
  // 719: ... if current_item == item: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__43_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 720: -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__46_3(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // self: 0
  // element: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 743: ... : (item)
  // 744:   if item == element || item .contains. element: return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__46_4, 1);
  // 743: for_each self: (item)
  // 744:   if item == element || item .contains. element: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__46_10;
}
static void entry__46_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__46_4(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // item: 0
  // element: 1
  // return: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* element */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 744: ... item == element
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  arguments->slots[1] = frame->slots[1] /* element */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__46_5;
}
static void cont__46_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 744: ... item .contains. element
  frame->slots[5] /* temp__3 */ = create_closure(entry__46_6, 0);
  // 744: ... item == element || item .contains. element
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__46_8;
}
static void entry__46_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // item: 0
  // element: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* item */
  frame->slots[1] = myself->closure.frame->slots[1]; /* element */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: ... item .contains. element
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  arguments->slots[1] = frame->slots[1] /* element */;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__46_7;
}
static void cont__46_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 744: ... item .contains. element
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__46_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 744: ... : return true
  frame->slots[6] /* temp__4 */ = create_closure(entry__46_9, 0);
  // 744: if item == element || item .contains. element: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__46_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__46_1_std__sequence(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // items: 0
  frame->slots[0] /* items */ = from_arguments(0, argument_count-0);
  // 735: list(items*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* items */);
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__46_2;
}
static void cont__46_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 735: list(items*)
  // 736:   .is_a_sequence true
  // 737:   /contains:
  // 738:     (
  // 739:       self
  // 740:       element
  // 741:       -> return
  // 742:     )
  // 743:     for_each self: (item)
  // 744:       if item == element || item .contains. element: return true
  // ...
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_sequence, get__true());
    set_attribute(temp->attributes, poly_idx__contains, func__46_3);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 734: ->
  // 735:   list(items*)
  // 736:     .is_a_sequence true
  // 737:     /contains:
  // 738:       (
  // 739:         self
  // 740:         element
  // 741:         -> return
  // 742:       )
  // 743:       for_each self: (item)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__list(void) {
  var.std__is_a_list = collect_node(var.std__is_a_list);
  var.types__generic_list = collect_node(var.types__generic_list);
  collect_static_attributes(&attributes__types__generic_list);
  var.types__list = collect_node(var.types__list);
  collect_static_attributes(&attributes__types__list);
  var.std__empty_list = collect_node(var.std__empty_list);
  var.std__list = collect_node(var.std__list);
  var.std__normalized_index = collect_node(var.std__normalized_index);
  var.std__is_a_sequence = collect_node(var.std__is_a_sequence);
  var.std__sequence = collect_node(var.std__sequence);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__list(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_a_list", get__std__is_a_list, &poly_idx__std__is_a_list, &var.std__is_a_list);
  define_c_function("from_arguments", runtime__from_arguments);
  define_polymorphic_function("std", "is_a_sequence", get__std__is_a_sequence, &poly_idx__std__is_a_sequence, &var.std__is_a_sequence);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__list(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__10 = from_uchar32(10);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__14_1_types__list_to_list = create_function(entry__14_1_types__list_to_list, 1);
  func__15_1_std__list = create_function(entry__15_1_std__list, -1);
  func__16_1_types__list_length_of = create_function(entry__16_1_types__list_length_of, 1);
  func__17_1_types__list_push = create_function(entry__17_1_types__list_push, 2);
  func__18_1_types__list_drop = create_function(entry__18_1_types__list_drop, 1);
  func__19_1_types__list_pop = create_function(entry__19_1_types__list_pop, 1);
  func__20_1_types__list_peek = create_function(entry__20_1_types__list_peek, 1);
  func__21_1_types__list_append = create_function(entry__21_1_types__list_append, 2);
  func__22_1_types__list_range = create_function(entry__22_1_types__list_range, 3);
  func__23_1_types__generic_list_delete_at = create_function(entry__23_1_types__generic_list_delete_at, -1);
  func__24_1_std__normalized_index = create_function(entry__24_1_std__normalized_index, 2);
  func__25_1_types__generic_list_is_empty = create_function(entry__25_1_types__generic_list_is_empty, 1);
  func__26_1_types__generic_list_for_each_from_to = create_function(entry__26_1_types__generic_list_for_each_from_to, -1);
  func__27_1_types__generic_list_for_each_from_down_to = create_function(entry__27_1_types__generic_list_for_each_from_down_to, -1);
  func__28_1_types__generic_list_for_each = create_function(entry__28_1_types__generic_list_for_each, -1);
  func__29_1_types__generic_list_update_each = create_function(entry__29_1_types__generic_list_update_each, 2);
  func__30_1_types__list_for_each_pair = create_function(entry__30_1_types__list_for_each_pair, 2);
  string__57ec57a17085427f = from_latin_1_string("Attempt to get an element from an empty list!", 45);
  func__31_4 = create_function(entry__31_4, 0);
  func__31_1_types__generic_list_get = create_function(entry__31_1_types__generic_list_get, 1);
  func__32_1_types__list_put = create_function(entry__32_1_types__list_put, 2);
  func__33_1_types__list_merge = create_function(entry__33_1_types__list_merge, -1);
  string__7e1f534683fac2fe = from_latin_1_string("list()", 6);
  string__1a0aeb0b5df87d4d = from_latin_1_string("list", 4);
  func__34_1_types__list_serialize = create_function(entry__34_1_types__list_serialize, -1);
  func__35_1_types__list_sort = create_function(entry__35_1_types__list_sort, -1);
  func__37_1_types__list_new_empty_collection = create_function(entry__37_1_types__list_new_empty_collection, 1);
  func__38_1_types__generic_list_equal = create_function(entry__38_1_types__generic_list_equal, 2);
  func__39_1_types__generic_list_filter = create_function(entry__39_1_types__generic_list_filter, 2);
  func__40_1_types__generic_list_map = create_function(entry__40_1_types__generic_list_map, 2);
  string__963fa2c6021831d1 = from_latin_1_string("Negative argument for dup!", 26);
  func__41_5 = create_function(entry__41_5, 0);
  func__41_15 = create_function(entry__41_15, 0);
  func__41_1_types__generic_list_dup = create_function(entry__41_1_types__generic_list_dup, 2);
  func__42_1_types__generic_list_interleave = create_function(entry__42_1_types__generic_list_interleave, -1);
  func__43_1_types__generic_list_contains = create_function(entry__43_1_types__generic_list_contains, 2);
  func__46_3 = create_function(entry__46_3, 2);
  func__46_1_std__sequence = create_function(entry__46_1_std__sequence, -1);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  string__b53819e78eec080a = from_latin_1_string("Invalid list object encountered during deserialisation!", 55);
  func__94_11 = create_function(entry__94_11, 0);
  func__94_1 = create_function(entry__94_1, 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__list(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__list");
  set_used_namespaces(used_namespaces);
  var.types__generic_list = create_future_with_prototype(create__types__generic_list());
  define_single_assign_static("types", "generic_list", get__types__generic_list, &var.types__generic_list);
  var.types__list = create_future_with_prototype(create__types__list(0, NULL));
  define_single_assign_static("types", "list", get__types__list, &var.types__list);
  var.std__empty_list = create__types__list(0, NULL);
  define_single_assign_static("std", "empty_list", get__std__empty_list, &var.std__empty_list);
  define_single_assign_static("std", "list", get__std__list, &var.std__list);
  define_single_assign_static("std", "normalized_index", get__std__normalized_index, &var.std__normalized_index);
  define_single_assign_static("std", "sequence", get__std__sequence, &var.std__sequence);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__list(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__list");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "append", &get__append, &poly_idx__append);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_polymorphic_function(NULL, "contains", &get__contains, &poly_idx__contains);
  use_polymorphic_function(NULL, "delete_at", &get__delete_at, &poly_idx__delete_at);
  use_read_only(NULL, "deserialize_item", &get__deserialize_item, &get_value_or_future__deserialize_item);
  use_read_only(NULL, "div", &get__div, &get_value_or_future__div);
  use_polymorphic_function(NULL, "drop", &get__drop, &poly_idx__drop);
  use_polymorphic_function(NULL, "dup", &get__dup, &poly_idx__dup);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "filter", &get__filter, &poly_idx__filter);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_polymorphic_function(NULL, "for_each_from_down_to", &get__for_each_from_down_to, &poly_idx__for_each_from_down_to);
  use_polymorphic_function(NULL, "for_each_from_to", &get__for_each_from_to, &poly_idx__for_each_from_to);
  use_polymorphic_function(NULL, "for_each_pair", &get__for_each_pair, &poly_idx__for_each_pair);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
  use_polymorphic_function(NULL, "get", &get__get, &poly_idx__get);
  use_read_only(NULL, "get_deserialization_indent", &get__get_deserialization_indent, &get_value_or_future__get_deserialization_indent);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "interleave", &get__interleave, &poly_idx__interleave);
  use_polymorphic_function(NULL, "is_a_list", &get__is_a_list, &poly_idx__is_a_list);
  use_polymorphic_function(NULL, "is_a_sequence", &get__is_a_sequence, &poly_idx__is_a_sequence);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_polymorphic_function(NULL, "is_empty", &get__is_empty, &poly_idx__is_empty);
  use_read_only(NULL, "is_odd", &get__is_odd, &get_value_or_future__is_odd);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_polymorphic_function(NULL, "length_of", &get__length_of, &poly_idx__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_polymorphic_function(NULL, "map", &get__map, &poly_idx__map);
  use_polymorphic_function(NULL, "merge", &get__merge, &poly_idx__merge);
  use_read_only(NULL, "minus", &get__minus, &get_value_or_future__minus);
  use_polymorphic_function(NULL, "new_empty_collection", &get__new_empty_collection, &poly_idx__new_empty_collection);
  use_read_only(NULL, "normalized_index", &get__normalized_index, &get_value_or_future__normalized_index);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_polymorphic_function(NULL, "peek", &get__peek, &poly_idx__peek);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_polymorphic_function(NULL, "pop", &get__pop, &poly_idx__pop);
  use_polymorphic_function(NULL, "push", &get__push, &poly_idx__push);
  use_polymorphic_function(NULL, "put", &get__put, &poly_idx__put);
  use_read_only(NULL, "raise", &get__raise, &get_value_or_future__raise);
  use_polymorphic_function(NULL, "range", &get__range, &poly_idx__range);
  use_read_only(NULL, "register_deserializer", &get__register_deserializer, &get_value_or_future__register_deserializer);
  use_polymorphic_function(NULL, "serialize", &get__serialize, &poly_idx__serialize);
  use_polymorphic_function(NULL, "sort", &get__sort, &poly_idx__sort);
  use_read_only(NULL, "spaces", &get__spaces, &get_value_or_future__spaces);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_polymorphic_function(NULL, "to_list", &get__to_list, &poly_idx__to_list);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_polymorphic_function(NULL, "update_each", &get__update_each, &poly_idx__update_each);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
  define_attribute("types", "object", poly_idx__is_a_list, get__false());
  define_attribute("types", "list", poly_idx__is_a_list, get__true());
  define_method("types", "list", poly_idx__to_list, func__14_1_types__list_to_list);
  define_method("types", "list", poly_idx__length_of, func__16_1_types__list_length_of);
  define_method("types", "list", poly_idx__push, func__17_1_types__list_push);
  define_method("types", "list", poly_idx__drop, func__18_1_types__list_drop);
  define_method("types", "list", poly_idx__pop, func__19_1_types__list_pop);
  define_method("types", "list", poly_idx__peek, func__20_1_types__list_peek);
  define_method("types", "list", poly_idx__append, func__21_1_types__list_append);
  define_method("types", "list", poly_idx__range, func__22_1_types__list_range);
  define_method("types", "generic_list", poly_idx__delete_at, func__23_1_types__generic_list_delete_at);
  define_method("types", "generic_list", poly_idx__is_empty, func__25_1_types__generic_list_is_empty);
  define_method("types", "generic_list", poly_idx__for_each_from_to, func__26_1_types__generic_list_for_each_from_to);
  define_method("types", "generic_list", poly_idx__for_each_from_down_to, func__27_1_types__generic_list_for_each_from_down_to);
  define_method("types", "generic_list", poly_idx__for_each, func__28_1_types__generic_list_for_each);
  define_method("types", "generic_list", poly_idx__update_each, func__29_1_types__generic_list_update_each);
  define_method("types", "list", poly_idx__for_each_pair, func__30_1_types__list_for_each_pair);
  define_method("types", "generic_list", poly_idx__get, func__31_1_types__generic_list_get);
  define_method("types", "list", poly_idx__put, func__32_1_types__list_put);
  define_method("types", "list", poly_idx__merge, func__33_1_types__list_merge);
  define_method("types", "list", poly_idx__serialize, func__34_1_types__list_serialize);
  define_method("types", "list", poly_idx__sort, func__35_1_types__list_sort);
  define_method("types", "list", poly_idx__new_empty_collection, func__37_1_types__list_new_empty_collection);
  define_method("types", "generic_list", poly_idx__equal, func__38_1_types__generic_list_equal);
  define_method("types", "generic_list", poly_idx__filter, func__39_1_types__generic_list_filter);
  define_method("types", "generic_list", poly_idx__map, func__40_1_types__generic_list_map);
  define_method("types", "generic_list", poly_idx__dup, func__41_1_types__generic_list_dup);
  define_method("types", "generic_list", poly_idx__interleave, func__42_1_types__generic_list_interleave);
  define_method("types", "generic_list", poly_idx__contains, func__43_1_types__generic_list_contains);
  define_attribute("types", "object", poly_idx__is_a_sequence, get__false());
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__list(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_list, create_function(type__std__is_a_list, -1));
  assign_value(&var.types__generic_list, get__types__object());
  assign_variable(&var.types__list, &var.types__generic_list);
  assign_variable(&var.std__list, &func__15_1_std__list);
  assign_variable(&var.std__normalized_index, &func__24_1_std__normalized_index);
  assign_value(&var.std__is_a_sequence, create_function(type__std__is_a_sequence, -1));
  assign_variable(&var.std__sequence, &func__46_1_std__sequence);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__list(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__list);
}
