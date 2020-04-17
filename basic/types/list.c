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
static FRAME_INFO frame__29_1_types__generic_list_update_each = {6, {"self", "body", "return", "i", "n", "new_list"}};
static void cont__29_2(void);
static void cont__29_3(void);
static void cont__29_4(void);
static NODE *func__29_5;
static void entry__29_5(void);
static FRAME_INFO frame__29_5 = {5, {"n", "i", "new_list", "body", "self"}};
static NODE *func__29_6;
static void entry__29_6(void);
static FRAME_INFO frame__29_6 = {5, {"n", "i", "new_list", "body", "self"}};
static void cont__29_7(void);
static void cont__29_8(void);
static NODE *func__29_9;
static void entry__29_9(void);
static FRAME_INFO frame__29_9 = {4, {"new_list", "body", "i", "self"}};
static void cont__29_10(void);
static void cont__29_11(void);
static void cont__29_12(void);
static void cont__29_13(void);
static NODE *func__29_14;
static void entry__29_14(void);
static FRAME_INFO frame__29_14 = {5, {"n", "i", "new_list", "body", "self"}};
static NODE *func__29_15;
static void entry__29_15(void);
static FRAME_INFO frame__29_15 = {5, {"n", "i", "new_list", "body", "self"}};
static void cont__29_16(void);
static void cont__29_17(void);
static NODE *func__29_18;
static void entry__29_18(void);
static FRAME_INFO frame__29_18 = {4, {"new_list", "body", "self", "i"}};
static void cont__29_19(void);
static void cont__29_20(void);
static void cont__29_21(void);
static void cont__29_22(void);
static void cont__29_23(void);
static void cont__29_24(void);
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
static NODE *string__31_5;
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
static NODE *string__34_4;
static void cont__34_5(void);
static NODE *string__34_6;
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
static NODE *string__41_6;
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
static NODE *string__94_2;
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
static NODE *string__94_12;
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
  {type__std__is_a_sequence, NULL, 654, 654, 2, 19},
  {run__basic__types__list, NULL, 676, 693, 1, 45},
  {cont__94_32, NULL, },
  {entry__14_1_types__list_to_list, NULL, 170, 170, 30, 36},
  {entry__15_1_std__list, NULL, 175, 187, 3, 2},
  {entry__16_1_types__list_length_of, NULL, 192, 195, 3, 2},
  {entry__17_1_types__list_push, NULL, 200, 218, 3, 2},
  {entry__18_1_types__list_drop, NULL, 223, 230, 3, 2},
  {entry__19_1_types__list_pop, NULL, 235, 246, 3, 2},
  {entry__20_1_types__list_peek, NULL, 251, 257, 3, 2},
  {entry__21_1_types__list_append, NULL, 262, 287, 3, 2},
  {entry__22_1_types__list_range, NULL, 292, 313, 3, 2},
  {entry__23_4, NULL, 323, 323, 44, 48},
  {cont__23_5, &frame__23_4, 323, 323, 31, 49},
  {cont__23_6, &frame__23_4, 323, 323, 62, 70},
  {cont__23_7, &frame__23_4, 323, 323, 73, 73},
  {cont__23_8, &frame__23_4, 323, 323, 51, 74},
  {cont__23_9, &frame__23_4, 323, 323, 18, 75},
  {cont__23_10, &frame__23_4, 323, 323, 75, 75},
  {entry__23_1_types__generic_list_delete_at, NULL, 323, 323, 6, 15},
  {cont__23_2, &frame__23_1_types__generic_list_delete_at, 323, 323, 6, 15},
  {cont__23_3, &frame__23_1_types__generic_list_delete_at, 323, 323, 3, 75},
  {cont__23_11, &frame__23_1_types__generic_list_delete_at, },
  {entry__24_4, NULL, 335, 335, 7, 16},
  {entry__24_5, NULL, 337, 337, 14, 28},
  {cont__24_6, &frame__24_5, 337, 337, 14, 30},
  {cont__24_7, &frame__24_5, 337, 337, 14, 34},
  {cont__24_8, &frame__24_5, 337, 337, 7, 34},
  {entry__24_1_std__normalized_index, NULL, 334, 334, 5, 12},
  {cont__24_2, &frame__24_1_std__normalized_index, 334, 334, 5, 12},
  {cont__24_3, &frame__24_1_std__normalized_index, 333, 337, 3, 35},
  {cont__24_9, &frame__24_1_std__normalized_index, 337, 337, 35, 35},
  {entry__25_1_types__generic_list_is_empty, NULL, 345, 345, 6, 20},
  {cont__25_2, &frame__25_1_types__generic_list_is_empty, 345, 345, 6, 25},
  {cont__25_3, &frame__25_1_types__generic_list_is_empty, 345, 345, 3, 25},
  {entry__26_10, NULL, 374, 374, 16, 22},
  {cont__26_11, &frame__26_10, 374, 374, 9, 22},
  {entry__26_12, NULL, 376, 376, 14, 20},
  {cont__26_13, &frame__26_12, 376, 376, 9, 20},
  {entry__26_16, NULL, 377, 377, 28, 32},
  {cont__26_17, &frame__26_16, 377, 377, 28, 32},
  {entry__26_19, NULL, 377, 377, 35, 39},
  {entry__26_7, NULL, 373, 373, 7, 30},
  {cont__26_8, &frame__26_7, 373, 373, 7, 35},
  {cont__26_9, &frame__26_7, 372, 376, 5, 21},
  {cont__26_14, &frame__26_7, 377, 377, 8, 23},
  {cont__26_15, &frame__26_7, 377, 377, 8, 32},
  {cont__26_18, &frame__26_7, 377, 377, 5, 39},
  {cont__26_20, &frame__26_7, 378, 378, 5, 13},
  {cont__26_21, &frame__26_7, 378, 378, 13, 13},
  {entry__26_4, NULL, 371, 371, 12, 17},
  {cont__26_5, &frame__26_4, 371, 371, 12, 17},
  {cont__26_6, &frame__26_4, 371, 378, 9, 13},
  {entry__26_1_types__generic_list_for_each_from_to, NULL, 369, 369, 3, 34},
  {cont__26_2, &frame__26_1_types__generic_list_for_each_from_to, 370, 370, 3, 32},
  {cont__26_3, &frame__26_1_types__generic_list_for_each_from_to, 371, 378, 3, 13},
  {entry__27_10, NULL, 407, 407, 16, 22},
  {cont__27_11, &frame__27_10, 407, 407, 9, 22},
  {entry__27_12, NULL, 409, 409, 14, 20},
  {cont__27_13, &frame__27_12, 409, 409, 9, 20},
  {entry__27_16, NULL, 410, 410, 28, 32},
  {cont__27_17, &frame__27_16, 410, 410, 28, 32},
  {entry__27_19, NULL, 410, 410, 35, 39},
  {entry__27_7, NULL, 406, 406, 7, 30},
  {cont__27_8, &frame__27_7, 406, 406, 7, 35},
  {cont__27_9, &frame__27_7, 405, 409, 5, 21},
  {cont__27_14, &frame__27_7, 410, 410, 8, 23},
  {cont__27_15, &frame__27_7, 410, 410, 8, 32},
  {cont__27_18, &frame__27_7, 410, 410, 5, 39},
  {cont__27_20, &frame__27_7, 411, 411, 5, 14},
  {cont__27_21, &frame__27_7, 411, 411, 14, 14},
  {entry__27_4, NULL, 404, 404, 12, 17},
  {cont__27_5, &frame__27_4, 404, 404, 12, 17},
  {cont__27_6, &frame__27_4, 404, 411, 9, 14},
  {entry__27_1_types__generic_list_for_each_from_down_to, NULL, 402, 402, 3, 34},
  {cont__27_2, &frame__27_1_types__generic_list_for_each_from_down_to, 403, 403, 3, 32},
  {cont__27_3, &frame__27_1_types__generic_list_for_each_from_down_to, 404, 411, 3, 14},
  {entry__28_13, NULL, 425, 425, 32, 36},
  {cont__28_14, &frame__28_13, 425, 425, 32, 36},
  {entry__28_16, NULL, 425, 425, 39, 43},
  {entry__28_9, NULL, 424, 424, 16, 22},
  {cont__28_10, &frame__28_9, 424, 424, 9, 22},
  {cont__28_11, &frame__28_9, 425, 425, 12, 27},
  {cont__28_12, &frame__28_9, 425, 425, 12, 36},
  {cont__28_15, &frame__28_9, 425, 425, 9, 43},
  {cont__28_17, &frame__28_9, 426, 426, 9, 17},
  {cont__28_18, &frame__28_9, 426, 426, 17, 17},
  {entry__28_6, NULL, 423, 423, 16, 21},
  {cont__28_7, &frame__28_6, 423, 423, 16, 21},
  {cont__28_8, &frame__28_6, 423, 426, 13, 17},
  {entry__28_5, NULL, 423, 426, 7, 17},
  {entry__28_27, NULL, 430, 430, 32, 36},
  {cont__28_28, &frame__28_27, 430, 430, 32, 36},
  {entry__28_30, NULL, 430, 430, 39, 43},
  {entry__28_23, NULL, 429, 429, 14, 20},
  {cont__28_24, &frame__28_23, 429, 429, 9, 20},
  {cont__28_25, &frame__28_23, 430, 430, 12, 27},
  {cont__28_26, &frame__28_23, 430, 430, 12, 36},
  {cont__28_29, &frame__28_23, 430, 430, 9, 43},
  {cont__28_31, &frame__28_23, 431, 431, 9, 17},
  {cont__28_32, &frame__28_23, 431, 431, 17, 17},
  {entry__28_20, NULL, 428, 428, 16, 21},
  {cont__28_21, &frame__28_20, 428, 428, 16, 21},
  {cont__28_22, &frame__28_20, 428, 431, 13, 17},
  {entry__28_19, NULL, 428, 431, 7, 17},
  {entry__28_1_types__generic_list_for_each, NULL, 420, 420, 3, 20},
  {cont__28_2, &frame__28_1_types__generic_list_for_each, 422, 422, 5, 28},
  {cont__28_3, &frame__28_1_types__generic_list_for_each, 422, 422, 5, 33},
  {cont__28_4, &frame__28_1_types__generic_list_for_each, 421, 431, 3, 19},
  {entry__29_9, NULL, 445, 445, 31, 37},
  {cont__29_10, &frame__29_9, 445, 445, 24, 38},
  {cont__29_11, &frame__29_9, 445, 445, 9, 38},
  {cont__29_12, &frame__29_9, 446, 446, 9, 17},
  {cont__29_13, &frame__29_9, 446, 446, 17, 17},
  {entry__29_6, NULL, 444, 444, 16, 21},
  {cont__29_7, &frame__29_6, 444, 444, 16, 21},
  {cont__29_8, &frame__29_6, 444, 446, 13, 17},
  {entry__29_5, NULL, 444, 446, 7, 17},
  {entry__29_18, NULL, 449, 449, 29, 35},
  {cont__29_19, &frame__29_18, 449, 449, 24, 36},
  {cont__29_20, &frame__29_18, 449, 449, 9, 36},
  {cont__29_21, &frame__29_18, 450, 450, 9, 17},
  {cont__29_22, &frame__29_18, 450, 450, 17, 17},
  {entry__29_15, NULL, 448, 448, 16, 21},
  {cont__29_16, &frame__29_15, 448, 448, 16, 21},
  {cont__29_17, &frame__29_15, 448, 450, 13, 17},
  {entry__29_14, NULL, 448, 450, 7, 17},
  {entry__29_1_types__generic_list_update_each, NULL, 440, 440, 3, 20},
  {cont__29_2, &frame__29_1_types__generic_list_update_each, 443, 443, 5, 28},
  {cont__29_3, &frame__29_1_types__generic_list_update_each, 443, 443, 5, 33},
  {cont__29_4, &frame__29_1_types__generic_list_update_each, 442, 450, 3, 19},
  {cont__29_23, &frame__29_1_types__generic_list_update_each, 451, 451, 3, 17},
  {cont__29_24, &frame__29_1_types__generic_list_update_each, 451, 451, 17, 17},
  {entry__30_5, NULL, 461, 461, 10, 16},
  {cont__30_6, &frame__30_5, 461, 461, 23, 25},
  {cont__30_7, &frame__30_5, 461, 461, 18, 26},
  {cont__30_8, &frame__30_5, 461, 461, 5, 26},
  {cont__30_9, &frame__30_5, 462, 462, 5, 13},
  {cont__30_10, &frame__30_5, 462, 462, 13, 13},
  {entry__30_3, NULL, 460, 460, 12, 16},
  {cont__30_4, &frame__30_3, 460, 462, 9, 13},
  {entry__30_13, NULL, 463, 463, 22, 28},
  {cont__30_14, &frame__30_13, 463, 463, 17, 28},
  {entry__30_1_types__list_for_each_pair, NULL, 459, 459, 3, 20},
  {cont__30_2, &frame__30_1_types__list_for_each_pair, 460, 462, 3, 13},
  {cont__30_11, &frame__30_1_types__list_for_each_pair, 463, 463, 6, 14},
  {cont__30_12, &frame__30_1_types__list_for_each_pair, 463, 463, 3, 28},
  {entry__31_4, NULL, 469, 469, 28, 80},
  {entry__31_1_types__generic_list_get, NULL, 469, 469, 6, 20},
  {cont__31_2, &frame__31_1_types__generic_list_get, 469, 469, 6, 25},
  {cont__31_3, &frame__31_1_types__generic_list_get, 469, 469, 3, 80},
  {cont__31_6, &frame__31_1_types__generic_list_get, 470, 470, 20, 20},
  {cont__31_7, &frame__31_1_types__generic_list_get, 470, 470, 6, 21},
  {cont__31_8, &frame__31_1_types__generic_list_get, 470, 470, 23, 29},
  {cont__31_9, &frame__31_1_types__generic_list_get, 470, 470, 3, 29},
  {entry__32_1_types__list_put, NULL, 477, 477, 13, 22},
  {cont__32_2, &frame__32_1_types__list_put, 477, 477, 6, 28},
  {cont__32_3, &frame__32_1_types__list_put, 477, 477, 3, 28},
  {entry__33_11, NULL, 494, 494, 49, 56},
  {cont__33_12, &frame__33_11, 494, 494, 38, 44},
  {cont__33_13, &frame__33_11, 494, 494, 38, 56},
  {cont__33_14, &frame__33_11, 494, 494, 38, 56},
  {cont__33_15, &frame__33_11, 494, 494, 38, 56},
  {entry__33_19, NULL, 495, 495, 45, 52},
  {cont__33_20, &frame__33_19, 495, 495, 54, 60},
  {cont__33_21, &frame__33_19, 495, 495, 40, 61},
  {cont__33_22, &frame__33_19, 495, 495, 36, 62},
  {cont__33_23, &frame__33_19, 495, 495, 36, 62},
  {entry__33_17, NULL, 495, 495, 17, 31},
  {cont__33_18, &frame__33_17, 495, 495, 17, 62},
  {cont__33_24, &frame__33_17, 495, 495, 17, 62},
  {entry__33_26, NULL, 497, 497, 30, 39},
  {cont__33_27, &frame__33_26, 497, 497, 17, 39},
  {cont__33_28, &frame__33_26, 497, 497, 39, 39},
  {entry__33_29, NULL, 499, 499, 30, 40},
  {cont__33_30, &frame__33_29, 499, 499, 17, 40},
  {cont__33_31, &frame__33_29, 499, 499, 40, 40},
  {entry__33_9, NULL, 494, 494, 17, 33},
  {cont__33_10, &frame__33_9, 494, 494, 17, 56},
  {cont__33_16, &frame__33_9, 493, 495, 15, 61},
  {cont__33_25, &frame__33_9, 492, 499, 13, 41},
  {entry__33_32, NULL, 501, 501, 20, 38},
  {cont__33_33, &frame__33_32, 501, 501, 13, 38},
  {entry__33_6, NULL, 491, 491, 11, 26},
  {cont__33_7, &frame__33_6, 491, 491, 11, 30},
  {cont__33_8, &frame__33_6, 490, 501, 9, 39},
  {entry__33_34, NULL, 503, 503, 16, 35},
  {cont__33_35, &frame__33_34, 503, 503, 9, 35},
  {entry__33_3, NULL, 489, 489, 7, 21},
  {cont__33_4, &frame__33_3, 489, 489, 7, 25},
  {cont__33_5, &frame__33_3, 488, 503, 5, 36},
  {entry__33_1_types__list_merge, NULL, 486, 486, 3, 17},
  {cont__33_2, &frame__33_1_types__list_merge, 487, 503, 3, 37},
  {cont__33_36, &frame__33_1_types__list_merge, 503, 503, 37, 37},
  {entry__34_3, NULL, 511, 511, 21, 35},
  {entry__34_7, NULL, 514, 514, 33, 40},
  {cont__34_8, &frame__34_7, 514, 514, 26, 41},
  {cont__34_9, &frame__34_7, 514, 514, 58, 65},
  {cont__34_10, &frame__34_7, 514, 514, 43, 66},
  {cont__34_11, &frame__34_7, 514, 514, 5, 66},
  {cont__34_12, &frame__34_7, 514, 514, 66, 66},
  {entry__34_1_types__list_serialize, NULL, 511, 511, 6, 18},
  {cont__34_2, &frame__34_1_types__list_serialize, 511, 511, 3, 35},
  {cont__34_5, &frame__34_1_types__list_serialize, 513, 514, 3, 66},
  {cont__34_13, &frame__34_1_types__list_serialize, 515, 515, 3, 8},
  {entry__35_4, NULL, 527, 527, 7, 17},
  {entry__35_7, NULL, 531, 531, 43, 49},
  {cont__35_8, &frame__35_7, 531, 531, 32, 38},
  {cont__35_9, &frame__35_7, 531, 531, 32, 49},
  {cont__35_10, &frame__35_7, 531, 531, 32, 49},
  {cont__35_11, &frame__35_7, 531, 531, 32, 49},
  {entry__35_15, NULL, 532, 532, 39, 45},
  {cont__35_16, &frame__35_15, 532, 532, 47, 53},
  {cont__35_17, &frame__35_15, 532, 532, 34, 54},
  {cont__35_18, &frame__35_15, 532, 532, 30, 55},
  {cont__35_19, &frame__35_15, 532, 532, 30, 55},
  {entry__35_13, NULL, 532, 532, 11, 25},
  {cont__35_14, &frame__35_13, 532, 532, 11, 55},
  {cont__35_20, &frame__35_13, 532, 532, 11, 55},
  {entry__35_22, NULL, 534, 534, 11, 21},
  {entry__35_23, NULL, 536, 536, 23, 29},
  {cont__35_24, &frame__35_23, 536, 536, 31, 37},
  {cont__35_25, &frame__35_23, 536, 536, 18, 38},
  {cont__35_26, &frame__35_23, 536, 536, 11, 38},
  {entry__35_5, NULL, 531, 531, 11, 27},
  {cont__35_6, &frame__35_5, 531, 531, 11, 49},
  {cont__35_12, &frame__35_5, 530, 532, 9, 54},
  {cont__35_21, &frame__35_5, 529, 536, 7, 39},
  {entry__35_30, NULL, 541, 541, 29, 43},
  {cont__35_31, &frame__35_30, 541, 541, 24, 44},
  {cont__35_32, &frame__35_30, 541, 541, 62, 64},
  {cont__35_33, &frame__35_30, 541, 541, 51, 67},
  {cont__35_34, &frame__35_30, 541, 541, 46, 68},
  {cont__35_35, &frame__35_30, 541, 541, 18, 69},
  {cont__35_36, &frame__35_30, 541, 541, 11, 69},
  {entry__35_37, NULL, 544, 544, 24, 38},
  {cont__35_38, &frame__35_37, 544, 544, 19, 44},
  {cont__35_39, &frame__35_37, 544, 544, 62, 64},
  {cont__35_40, &frame__35_37, 544, 544, 51, 67},
  {cont__35_41, &frame__35_37, 544, 544, 46, 73},
  {cont__35_42, &frame__35_37, 544, 544, 13, 79},
  {cont__35_43, &frame__35_37, 543, 544, 11, 79},
  {entry__35_27, NULL, 538, 538, 7, 18},
  {cont__35_28, &frame__35_27, 540, 540, 9, 25},
  {cont__35_29, &frame__35_27, 539, 544, 7, 81},
  {entry__35_1_types__list_sort, NULL, 523, 523, 3, 20},
  {cont__35_2, &frame__35_1_types__list_sort, 526, 526, 5, 8},
  {cont__35_3, &frame__35_1_types__list_sort, 524, 544, 3, 83},
  {cont__35_44, &frame__35_1_types__list_sort, 544, 544, 83, 83},
  {entry__37_1_types__list_new_empty_collection, NULL, 581, 581, 3, 16},
  {entry__38_3, NULL, 593, 593, 30, 44},
  {cont__38_4, &frame__38_3, 593, 593, 30, 44},
  {entry__38_6, NULL, 593, 593, 47, 58},
  {entry__38_12, NULL, 594, 594, 43, 54},
  {entry__38_18, NULL, 595, 595, 52, 63},
  {entry__38_14, NULL, 595, 595, 40, 49},
  {cont__38_15, &frame__38_14, 595, 595, 32, 49},
  {cont__38_16, &frame__38_14, 595, 595, 32, 49},
  {cont__38_17, &frame__38_14, 595, 595, 29, 63},
  {entry__38_1_types__generic_list_equal, NULL, 593, 593, 10, 25},
  {cont__38_2, &frame__38_1_types__generic_list_equal, 593, 593, 10, 44},
  {cont__38_5, &frame__38_1_types__generic_list_equal, 593, 593, 3, 58},
  {cont__38_7, &frame__38_1_types__generic_list_equal, 594, 594, 6, 20},
  {cont__38_8, &frame__38_1_types__generic_list_equal, 594, 594, 25, 40},
  {cont__38_9, &frame__38_1_types__generic_list_equal, 594, 594, 6, 40},
  {cont__38_10, &frame__38_1_types__generic_list_equal, 594, 594, 6, 40},
  {cont__38_11, &frame__38_1_types__generic_list_equal, 594, 594, 3, 54},
  {cont__38_13, &frame__38_1_types__generic_list_equal, 595, 595, 3, 63},
  {cont__38_19, &frame__38_1_types__generic_list_equal, 596, 596, 3, 9},
  {entry__39_5, NULL, 604, 604, 40, 58},
  {cont__39_6, &frame__39_5, 604, 604, 58, 58},
  {entry__39_3, NULL, 604, 604, 28, 37},
  {cont__39_4, &frame__39_3, 604, 604, 25, 58},
  {entry__39_1_types__generic_list_filter, NULL, 603, 603, 3, 39},
  {cont__39_2, &frame__39_1_types__generic_list_filter, 604, 604, 3, 58},
  {cont__39_7, &frame__39_1_types__generic_list_filter, 605, 605, 3, 13},
  {entry__40_3, NULL, 613, 613, 40, 49},
  {cont__40_4, &frame__40_3, 613, 613, 25, 49},
  {cont__40_5, &frame__40_3, 613, 613, 49, 49},
  {entry__40_1_types__generic_list_map, NULL, 612, 612, 3, 39},
  {cont__40_2, &frame__40_1_types__generic_list_map, 613, 613, 3, 49},
  {cont__40_6, &frame__40_1_types__generic_list_map, 614, 614, 3, 13},
  {entry__41_2, NULL, 622, 622, 31, 37},
  {entry__41_5, NULL, 623, 623, 15, 48},
  {entry__41_12, NULL, 626, 626, 18, 36},
  {cont__41_13, &frame__41_12, 626, 626, 36, 36},
  {entry__41_3, NULL, 623, 623, 8, 12},
  {cont__41_4, &frame__41_3, 623, 623, 5, 48},
  {cont__41_7, &frame__41_3, 624, 624, 23, 31},
  {cont__41_8, &frame__41_3, 624, 624, 5, 32},
  {cont__41_9, &frame__41_3, 625, 625, 5, 25},
  {cont__41_10, &frame__41_3, 626, 626, 8, 15},
  {cont__41_11, &frame__41_3, 626, 626, 5, 36},
  {cont__41_14, &frame__41_3, 627, 627, 5, 13},
  {entry__41_15, NULL, 622, 622, 13, 25},
  {entry__41_1_types__generic_list_dup, NULL, 622, 627, 3, 13},
  {entry__42_6, NULL, 640, 640, 66, 80},
  {cont__42_7, &frame__42_6, 640, 640, 53, 80},
  {cont__42_8, &frame__42_6, 640, 640, 80, 80},
  {entry__42_5, NULL, 640, 640, 22, 80},
  {entry__42_14, NULL, 642, 642, 51, 65},
  {cont__42_15, &frame__42_14, 642, 642, 38, 65},
  {cont__42_16, &frame__42_14, 642, 642, 65, 65},
  {entry__42_10, NULL, 642, 642, 8, 30},
  {cont__42_11, &frame__42_10, 642, 642, 8, 35},
  {cont__42_12, &frame__42_10, 642, 642, 8, 35},
  {cont__42_13, &frame__42_10, 642, 642, 5, 65},
  {entry__42_1_types__generic_list_interleave, NULL, 638, 638, 16, 23},
  {cont__42_2, &frame__42_1_types__generic_list_interleave, 638, 638, 3, 24},
  {cont__42_3, &frame__42_1_types__generic_list_interleave, 640, 640, 13, 15},
  {cont__42_4, &frame__42_1_types__generic_list_interleave, 640, 640, 3, 80},
  {cont__42_9, &frame__42_1_types__generic_list_interleave, 641, 642, 3, 65},
  {cont__42_17, &frame__42_1_types__generic_list_interleave, 643, 643, 3, 11},
  {entry__43_4, NULL, 651, 651, 58, 68},
  {entry__43_2, NULL, 651, 651, 36, 55},
  {cont__43_3, &frame__43_2, 651, 651, 33, 68},
  {entry__43_1_types__generic_list_contains, NULL, 651, 651, 3, 68},
  {cont__43_5, &frame__43_1_types__generic_list_contains, 652, 652, 3, 10},
  {entry__46_6, NULL, 673, 673, 33, 55},
  {cont__46_7, &frame__46_6, 673, 673, 33, 55},
  {entry__46_9, NULL, 673, 673, 58, 68},
  {entry__46_4, NULL, 673, 673, 14, 28},
  {cont__46_5, &frame__46_4, 673, 673, 14, 55},
  {cont__46_8, &frame__46_4, 673, 673, 11, 68},
  {entry__46_3, NULL, 672, 673, 9, 68},
  {cont__46_10, &frame__46_3, 674, 674, 9, 16},
  {entry__46_1_std__sequence, NULL, 664, 664, 5, 16},
  {cont__46_2, &frame__46_1_std__sequence, 663, 674, 3, 18},
  {entry__94_4, NULL, 684, 684, 51, 51},
  {cont__94_5, &frame__94_4, 684, 684, 37, 52},
  {cont__94_6, &frame__94_4, 684, 684, 30, 63},
  {entry__94_11, NULL, 686, 686, 5, 67},
  {entry__94_17, NULL, 689, 689, 32, 38},
  {cont__94_18, &frame__94_17, 689, 689, 32, 48},
  {cont__94_19, &frame__94_17, 689, 689, 32, 48},
  {cont__94_20, &frame__94_17, 689, 689, 32, 48},
  {entry__94_22, NULL, 689, 689, 51, 65},
  {entry__94_27, NULL, 691, 691, 31, 45},
  {entry__94_14, NULL, 689, 689, 8, 22},
  {cont__94_15, &frame__94_14, 689, 689, 8, 27},
  {cont__94_16, &frame__94_14, 689, 689, 8, 48},
  {cont__94_21, &frame__94_14, 689, 689, 5, 65},
  {cont__94_23, &frame__94_14, 690, 690, 5, 59},
  {cont__94_24, &frame__94_14, 691, 691, 8, 28},
  {cont__94_25, &frame__94_14, 691, 691, 8, 28},
  {cont__94_26, &frame__94_14, 691, 691, 5, 45},
  {cont__94_28, &frame__94_14, 693, 693, 15, 44},
  {cont__94_29, &frame__94_14, 693, 693, 5, 44},
  {cont__94_30, &frame__94_14, 693, 693, 44, 44},
  {entry__94_1, NULL, 684, 684, 6, 27},
  {cont__94_3, &frame__94_1, 684, 684, 3, 63},
  {cont__94_7, &frame__94_1, 685, 685, 6, 12},
  {cont__94_8, &frame__94_1, 685, 685, 6, 22},
  {cont__94_9, &frame__94_1, 685, 685, 6, 22},
  {cont__94_10, &frame__94_1, 685, 686, 3, 67},
  {cont__94_13, &frame__94_1, 688, 693, 3, 44},
  {cont__94_31, &frame__94_1, 693, 693, 44, 44}
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
  // 676: register_deserializer "list":
  // 677:   #
  // 678:     constructs a list from its serialized representation
  // 679:   (
  // 680:     $text
  // 681:     base_indent
  // 682:     -> return
  // 683:   )
  // 684:   if text .has_prefix. "()": return range(text 3 -1) empty_list
  // 685:   if text(1) != '@nl;':
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_6;
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
  // 684: ... text .has_prefix. "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = string__94_2;
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
  // 684: ... : return range(text 3 -1) empty_list
  frame->slots[5] /* temp__2 */ = create_closure(entry__94_4, 0);
  // 684: if text .has_prefix. "()": return range(text 3 -1) empty_list
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
  // 684: ... 1
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
  // 684: ... range(text 3 -1)
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
  // 684: ... return range(text 3 -1) empty_list
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
  // 685: ... text(1)
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
  // 685: ... text(1) != '@nl;'
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
  // 685: ... text(1) != '@nl;'
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
  // 685: if text(1) != '@nl;':
  // 686:   raise "Invalid list object encountered during deserialisation!"
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
  // 686: raise "Invalid list object encountered during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__94_12;
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
  // 687: $$obj empty_list
  ((CELL *)frame->slots[3])->contents /* obj */ = get__empty_list();
  // 688: ... :
  // 689:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 690:   get_deserialization_indent $remaining_text $indent text
  // 691:   if indent <= base_indent: return text obj
  // 692:   !text remaining_text
  // 693:   push &obj deserialize_item(&text indent)
  frame->slots[4] /* temp__1 */ = create_closure(entry__94_14, 0);
  // 688: forever:
  // 689:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 690:   get_deserialization_indent $remaining_text $indent text
  // 691:   if indent <= base_indent: return text obj
  // 692:   !text remaining_text
  // 693:   push &obj deserialize_item(&text indent)
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
  // 689: ... length_of(text)
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
  // 689: ... length_of(text) == 0
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
  // 689: ... text(1) != '@nl;'
  frame->slots[9] /* temp__4 */ = create_closure(entry__94_17, 0);
  // 689: ... length_of(text) == 0 || text(1) != '@nl;'
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
  // 689: ... text(1)
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
  // 689: ... text(1) != '@nl;'
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
  // 689: ... text(1) != '@nl;'
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
  // 689: ... text(1) != '@nl;'
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
  // 689: ... : return text obj
  frame->slots[10] /* temp__5 */ = create_closure(entry__94_22, 0);
  // 689: if length_of(text) == 0 || text(1) != '@nl;': return text obj
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
  // 689: ... return text obj
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
  // 690: get_deserialization_indent $remaining_text $indent text
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
  // 690: ... remaining_text
  initialize_future(frame->slots[4] /* remaining_text */, frame->slots[6] /* temp__1 */);
  // 690: ... indent
  initialize_future(frame->slots[5] /* indent */, frame->slots[7] /* temp__2 */);
  // 691: ... indent <= base_indent
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
  // 691: ... indent <= base_indent
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
  // 691: ... : return text obj
  frame->slots[8] /* temp__3 */ = create_closure(entry__94_27, 0);
  // 691: if indent <= base_indent: return text obj
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
  // 691: ... return text obj
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
  // 692: !text remaining_text
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[4] /* remaining_text */;
  // 693: ... deserialize_item(&text indent)
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
  // 693: push &obj deserialize_item(&text indent)
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
  // 170: ... -> self
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
  // 323: ... count != 0
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
  // 323: ... count != 0
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
  // 323: ... : !self append(range(self 1 idx-1) range(self idx+count -1))
  frame->slots[5] /* temp__3 */ = create_closure(entry__23_4, 0);
  // 323: if count != 0: !self append(range(self 1 idx-1) range(self idx+count -1))
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
  // 323: ... idx-1
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
  // 323: ... range(self 1 idx-1)
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
  // 323: ... idx+count
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
  // 323: ... 1
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
  // 323: ... range(self idx+count -1)
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
  // 323: ... !self append(range(self 1 idx-1) range(self idx+count -1))
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
  // 334: idx >= 0
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
  // 334: idx >= 0
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
  // 334: ... :
  // 335:   return idx
  frame->slots[5] /* temp__3 */ = create_closure(entry__24_4, 0);
  // 336: :
  // 337:   return length_of(self)+1+idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__24_5, 0);
  // 333: if
  // 334:   idx >= 0:
  // 335:     return idx
  // 336:   :
  // 337:     return length_of(self)+1+idx
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
  // 335: return idx
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
  // 337: ... length_of(self)
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
  // 337: ... length_of(self)+1
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
  // 337: ... length_of(self)+1+idx
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
  // 337: return length_of(self)+1+idx
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
  // 345: ... length_of(self)
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
  // 345: ... length_of(self) == 0
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
  // 345: -> length_of(self) == 0
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
  // 373: parameter_count_of(body)
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
  // 373: parameter_count_of(body) == 2
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
  // 373: ... :
  // 374:   body i self(i)
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_10, 0);
  // 375: :
  // 376:   body self(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__26_12, 0);
  // 372: if
  // 373:   parameter_count_of(body) == 2:
  // 374:     body i self(i)
  // 375:   :
  // 376:     body self(i)
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
  // 374: ... self(i)
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
  // 374: body i self(i)
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
  // 376: ... self(i)
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
  // 376: body self(i)
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
  // 377: ... body2.is_defined
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
  // 377: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_16, 0);
  // 377: ... body2.is_defined && i < n
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
  // 377: ... i < n
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
  // 377: ... i < n
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
  // 377: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__26_19, 0);
  // 377: if body2.is_defined && i < n: body2
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
  // 377: ... body2
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
  // 378: plus &i 1
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
  // 371: ... i <= n
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
  // 371: ... i <= n
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
  // 371: ... :
  // 372:   if
  // 373:     parameter_count_of(body) == 2:
  // 374:       body i self(i)
  // 375:     :
  // 376:       body self(i)
  // 377:   if body2.is_defined && i < n: body2
  // 378:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_7, 0);
  // 371: ... -> i <= n:
  // 372:   if
  // 373:     parameter_count_of(body) == 2:
  // 374:       body i self(i)
  // 375:     :
  // 376:       body self(i)
  // 377:   if body2.is_defined && i < n: body2
  // 378:   plus &i 1
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
  // 369: $$i normalized_index(self first)
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
  // 370: $n normalized_index(self last)
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
  // 371: ... -> i <= n:
  // 372:   if
  // 373:     parameter_count_of(body) == 2:
  // 374:       body i self(i)
  // 375:     :
  // 376:       body self(i)
  // 377:   if body2.is_defined && i < n: body2
  // 378:   plus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__26_4, 0);
  // 371: while -> i <= n:
  // 372:   if
  // 373:     parameter_count_of(body) == 2:
  // 374:       body i self(i)
  // 375:     :
  // 376:       body self(i)
  // 377:   if body2.is_defined && i < n: body2
  // 378:   plus &i 1
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
  // 406: parameter_count_of(body)
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
  // 406: parameter_count_of(body) == 2
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
  // 406: ... :
  // 407:   body i self(i)
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_10, 0);
  // 408: :
  // 409:   body self(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__27_12, 0);
  // 405: if
  // 406:   parameter_count_of(body) == 2:
  // 407:     body i self(i)
  // 408:   :
  // 409:     body self(i)
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
  // 407: ... self(i)
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
  // 407: body i self(i)
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
  // 409: ... self(i)
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
  // 409: body self(i)
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
  // 410: ... body2.is_defined
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
  // 410: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_16, 0);
  // 410: ... body2.is_defined && i < n
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
  // 410: ... i < n
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
  // 410: ... i < n
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
  // 410: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__27_19, 0);
  // 410: if body2.is_defined && i < n: body2
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
  // 410: ... body2
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
  // 411: minus &i 1
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
  // 404: ... i >= n
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
  // 404: ... i >= n
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
  // 404: ... :
  // 405:   if
  // 406:     parameter_count_of(body) == 2:
  // 407:       body i self(i)
  // 408:     :
  // 409:       body self(i)
  // 410:   if body2.is_defined && i < n: body2
  // 411:   minus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_7, 0);
  // 404: ... -> i >= n:
  // 405:   if
  // 406:     parameter_count_of(body) == 2:
  // 407:       body i self(i)
  // 408:     :
  // 409:       body self(i)
  // 410:   if body2.is_defined && i < n: body2
  // 411:   minus &i 1
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
  // 402: $$i normalized_index(self first)
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
  // 403: $n normalized_index(self last)
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
  // 404: ... -> i >= n:
  // 405:   if
  // 406:     parameter_count_of(body) == 2:
  // 407:       body i self(i)
  // 408:     :
  // 409:       body self(i)
  // 410:   if body2.is_defined && i < n: body2
  // 411:   minus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__27_4, 0);
  // 404: while -> i >= n:
  // 405:   if
  // 406:     parameter_count_of(body) == 2:
  // 407:       body i self(i)
  // 408:     :
  // 409:       body self(i)
  // 410:   if body2.is_defined && i < n: body2
  // 411:   minus &i 1
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
  // 429: ... self(i)
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
  // 429: body self(i)
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
  // 430: ... body2.is_defined
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
  // 430: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_27, 0);
  // 430: ... body2.is_defined && i < n
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
  // 430: ... i < n
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
  // 430: ... i < n
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
  // 430: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_30, 0);
  // 430: if body2.is_defined && i < n: body2
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
  // 430: ... body2
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
  // 431: plus &i 1
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
  // 428: ... i <= n
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
  // 428: ... i <= n
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
  // 428: ... :
  // 429:   body self(i)
  // 430:   if body2.is_defined && i < n: body2
  // 431:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_23, 0);
  // 428: ... -> i <= n:
  // 429:   body self(i)
  // 430:   if body2.is_defined && i < n: body2
  // 431:   plus &i 1
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
  // 424: ... self(i)
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
  // 424: body i self(i)
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
  // 425: ... body2.is_defined
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
  // 425: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_13, 0);
  // 425: ... body2.is_defined && i < n
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
  // 425: ... i < n
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
  // 425: ... i < n
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
  // 425: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_16, 0);
  // 425: if body2.is_defined && i < n: body2
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
  // 425: ... body2
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
  // 426: plus &i 1
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
  // 423: ... i <= n
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
  // 423: ... i <= n
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
  // 423: ... :
  // 424:   body i self(i)
  // 425:   if body2.is_defined && i < n: body2
  // 426:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_9, 0);
  // 423: ... -> i <= n:
  // 424:   body i self(i)
  // 425:   if body2.is_defined && i < n: body2
  // 426:   plus &i 1
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
  // 423: ... -> i <= n:
  // 424:   body i self(i)
  // 425:   if body2.is_defined && i < n: body2
  // 426:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__28_6, 0);
  // 423: while -> i <= n:
  // 424:   body i self(i)
  // 425:   if body2.is_defined && i < n: body2
  // 426:   plus &i 1
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
  // 428: ... -> i <= n:
  // 429:   body self(i)
  // 430:   if body2.is_defined && i < n: body2
  // 431:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__28_20, 0);
  // 428: while -> i <= n:
  // 429:   body self(i)
  // 430:   if body2.is_defined && i < n: body2
  // 431:   plus &i 1
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
  // 419: $$i 1
  ((CELL *)frame->slots[3])->contents /* i */ = number__1;
  // 420: $n length_of(self)
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
  // 422: parameter_count_of(body)
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
  // 422: parameter_count_of(body) == 2
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
  // 422: ... :
  // 423:   while -> i <= n:
  // 424:     body i self(i)
  // 425:     if body2.is_defined && i < n: body2
  // 426:     plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_5, 0);
  // 427: :
  // 428:   while -> i <= n:
  // 429:     body self(i)
  // 430:     if body2.is_defined && i < n: body2
  // 431:     plus &i 1
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_19, 0);
  // 421: if
  // 422:   parameter_count_of(body) == 2:
  // 423:     while -> i <= n:
  // 424:       body i self(i)
  // 425:       if body2.is_defined && i < n: body2
  // 426:       plus &i 1
  // 427:   :
  // 428:     while -> i <= n:
  // 429:       body self(i)
  // 430:       if body2.is_defined && i < n: body2
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
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // self: 0
  // body: 1
  // return: 2
  // i: 3
  // n: 4
  // new_list: 5
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* i */ = create_cell();
  frame->slots[4] /* n */ = create_future();
  frame->slots[5] /* new_list */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 439: $$i 1
  ((CELL *)frame->slots[3])->contents /* i */ = number__1;
  // 440: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* n */, arguments->slots[0]);
  // 441: $$new_list types::list
  ((CELL *)frame->slots[5])->contents /* new_list */ = var.types__list;
  // 443: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__29_3;
}
static void cont__29_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 443: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_4;
}
static void cont__29_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 443: ... :
  // 444:   while -> i <= n:
  // 445:     push &new_list body(i self(i))
  // 446:     plus &i 1
  frame->slots[8] /* temp__3 */ = create_closure(entry__29_5, 0);
  // 447: :
  // 448:   while -> i <= n:
  // 449:     push &new_list body(self(i))
  // 450:     plus &i 1
  frame->slots[9] /* temp__4 */ = create_closure(entry__29_14, 0);
  // 442: if
  // 443:   parameter_count_of(body) == 2:
  // 444:     while -> i <= n:
  // 445:       push &new_list body(i self(i))
  // 446:       plus &i 1
  // 447:   :
  // 448:     while -> i <= n:
  // 449:       push &new_list body(self(i))
  // 450:       plus &i 1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_23;
}
static void entry__29_18(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // new_list: 0
  // body: 1
  // self: 2
  // i: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* new_list */
  frame->slots[1] = myself->closure.frame->slots[3]; /* body */
  frame->slots[2] = myself->closure.frame->slots[4]; /* self */
  frame->slots[3] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 449: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__29_19;
}
static void cont__29_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 449: ... body(self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__29_20;
}
static void cont__29_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 449: push &new_list body(self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_list */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_21;
}
static void cont__29_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_list */ = arguments->slots[0];
  // 450: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__29_22;
}
static void cont__29_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_15(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // new_list: 2
  // body: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_list */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[4]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 448: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__29_16;
}
static void cont__29_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 448: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__29_17;
}
static void cont__29_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 448: ... :
  // 449:   push &new_list body(self(i))
  // 450:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__29_18, 0);
  // 448: ... -> i <= n:
  // 449:   push &new_list body(self(i))
  // 450:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_9(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // new_list: 0
  // body: 1
  // i: 2
  // self: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* new_list */
  frame->slots[1] = myself->closure.frame->slots[3]; /* body */
  frame->slots[2] = myself->closure.frame->slots[1]; /* i */
  frame->slots[3] = myself->closure.frame->slots[4]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 445: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[3] /* self */;
  func = myself->type;
  frame->cont = cont__29_10;
}
static void cont__29_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 445: ... body(i self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__29_11;
}
static void cont__29_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 445: push &new_list body(i self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_list */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_12;
}
static void cont__29_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_list */ = arguments->slots[0];
  // 446: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__29_13;
}
static void cont__29_13(void) {
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
static void entry__29_6(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // new_list: 2
  // body: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_list */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  frame->slots[4] = myself->closure.frame->slots[4]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 444: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__29_7;
}
static void cont__29_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 444: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__29_8;
}
static void cont__29_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 444: ... :
  // 445:   push &new_list body(i self(i))
  // 446:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__29_9, 0);
  // 444: ... -> i <= n:
  // 445:   push &new_list body(i self(i))
  // 446:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_5(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // n: 0
  // i: 1
  // new_list: 2
  // body: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* n */
  frame->slots[1] = myself->closure.frame->slots[3]; /* i */
  frame->slots[2] = myself->closure.frame->slots[5]; /* new_list */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 444: ... -> i <= n:
  // 445:   push &new_list body(i self(i))
  // 446:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__29_6, 0);
  // 444: while -> i <= n:
  // 445:   push &new_list body(i self(i))
  // 446:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_14(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // n: 0
  // i: 1
  // new_list: 2
  // body: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* n */
  frame->slots[1] = myself->closure.frame->slots[3]; /* i */
  frame->slots[2] = myself->closure.frame->slots[5]; /* new_list */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 448: ... -> i <= n:
  // 449:   push &new_list body(self(i))
  // 450:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__29_15, 0);
  // 448: while -> i <= n:
  // 449:   push &new_list body(self(i))
  // 450:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 451: return new_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* new_list */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = cont__29_24;
}
static void cont__29_24(void) {
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
  // 463: ... self(i)
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
  // 463: ... body self(i)
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
  // 458: $$i 1
  ((CELL *)frame->slots[2])->contents /* i */ = number__1;
  // 459: $n length_of(self)
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
  // 460: ... -> i < n:
  // 461:   body self(i) self(i+1)
  // 462:   plus &i 2
  frame->slots[4] /* temp__1 */ = create_closure(entry__30_3, 0);
  // 460: while -> i < n:
  // 461:   body self(i) self(i+1)
  // 462:   plus &i 2
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
  // 461: ... self(i)
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
  // 461: ... i+1
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
  // 461: ... self(i+1)
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
  // 461: body self(i) self(i+1)
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
  // 462: plus &i 2
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
  // 460: ... i < n
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
  // 460: ... :
  // 461:   body self(i) self(i+1)
  // 462:   plus &i 2
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_5, 0);
  // 460: ... -> i < n:
  // 461:   body self(i) self(i+1)
  // 462:   plus &i 2
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
  // 463: ... is_odd(n)
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
  // 463: ... : body self(i)
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_13, 0);
  // 463: if is_odd(n): body self(i)
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
  // 469: ... length_of(self)
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
  // 469: ... length_of(self) == 0
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
  // 469: if length_of(self) == 0: raise "Attempt to get an element from an empty list!"
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
  // 469: ... raise "Attempt to get an element from an empty list!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__31_5;
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
  // 470: ... 1
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
  // 470: ... range(self 2 -1)
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
  // 470: ... self(1)
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
  // 470: -> range(self 2 -1) self(1)
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
  // 477: ... list(item)
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
  // 477: ... append(list(item) self)
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
  // 477: -> append(list(item) self)
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
  // 486: $$result list()
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
  // 487: ... :
  // 488:   if
  // 489:     length_of(left) > 0:
  // 490:       if
  // 491:         length_of(right) > 0:
  // 492:           if
  // 493:             ||
  // 494:               func.is_undefined && left(1) <= right(1)
  // 495:               func.is_defined && not(func(right(1) left(1)))
  // 496:             :
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__33_3, 0);
  // 487: forever:
  // 488:   if
  // 489:     length_of(left) > 0:
  // 490:       if
  // 491:         length_of(right) > 0:
  // 492:           if
  // 493:             ||
  // 494:               func.is_undefined && left(1) <= right(1)
  // 495:               func.is_defined && not(func(right(1) left(1)))
  // 496:             :
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
  // 497: ... get(&left)
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
  // 497: push &result get(&left)
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
  // 499: ... get(&right)
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
  // 499: push &result get(&right)
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
  // 494: func.is_undefined
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
  // 494: ... left(1) <= right(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__33_11, 0);
  // 494: func.is_undefined && left(1) <= right(1)
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
  // 494: ... right(1)
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
  // 494: ... left(1)
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
  // 494: ... left(1) <= right(1)
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
  // 494: ... left(1) <= right(1)
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
  // 494: ... left(1) <= right(1)
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
  // 495: func.is_defined && not(func(right(1) left(1)))
  frame->slots[8] /* temp__5 */ = create_closure(entry__33_17, 0);
  // 493: ||
  // 494:   func.is_undefined && left(1) <= right(1)
  // 495:   func.is_defined && not(func(right(1) left(1)))
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
  // 495: func.is_defined
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
  // 495: ... not(func(right(1) left(1)))
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_19, 0);
  // 495: func.is_defined && not(func(right(1) left(1)))
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
  // 495: ... right(1)
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
  // 495: ... left(1)
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
  // 495: ... func(right(1) left(1))
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
  // 495: ... not(func(right(1) left(1)))
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
  // 495: ... not(func(right(1) left(1)))
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
  // 495: func.is_defined && not(func(right(1) left(1)))
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
  // 496: :
  // 497:   push &result get(&left)
  frame->slots[9] /* temp__6 */ = create_closure(entry__33_26, 0);
  // 498: :
  // 499:   push &result get(&right)
  frame->slots[10] /* temp__7 */ = create_closure(entry__33_29, 0);
  // 492: if
  // 493:   ||
  // 494:     func.is_undefined && left(1) <= right(1)
  // 495:     func.is_defined && not(func(right(1) left(1)))
  // 496:   :
  // 497:     push &result get(&left)
  // 498:   :
  // 499:     push &result get(&right)
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
  // 501: ... append(result left)
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
  // 501: return append(result left)
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
  // 491: length_of(right)
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
  // 491: length_of(right) > 0
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
  // 491: ... :
  // 492:   if
  // 493:     ||
  // 494:       func.is_undefined && left(1) <= right(1)
  // 495:       func.is_defined && not(func(right(1) left(1)))
  // 496:     :
  // 497:       push &result get(&left)
  // 498:     :
  // 499:       push &result get(&right)
  frame->slots[7] /* temp__3 */ = create_closure(entry__33_9, 0);
  // 500: :
  // 501:   return append(result left)
  frame->slots[8] /* temp__4 */ = create_closure(entry__33_32, 0);
  // 490: if
  // 491:   length_of(right) > 0:
  // 492:     if
  // 493:       ||
  // 494:         func.is_undefined && left(1) <= right(1)
  // 495:         func.is_defined && not(func(right(1) left(1)))
  // 496:       :
  // 497:         push &result get(&left)
  // 498:       :
  // 499:         push &result get(&right)
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
  // 503: ... append(result right)
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
  // 503: return append(result right)
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
  // 489: length_of(left)
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
  // 489: length_of(left) > 0
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
  // 489: ... :
  // 490:   if
  // 491:     length_of(right) > 0:
  // 492:       if
  // 493:         ||
  // 494:           func.is_undefined && left(1) <= right(1)
  // 495:           func.is_defined && not(func(right(1) left(1)))
  // 496:         :
  // 497:           push &result get(&left)
  // 498:         :
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__33_6, 0);
  // 502: :
  // 503:   return append(result right)
  frame->slots[8] /* temp__4 */ = create_closure(entry__33_34, 0);
  // 488: if
  // 489:   length_of(left) > 0:
  // 490:     if
  // 491:       length_of(right) > 0:
  // 492:         if
  // 493:           ||
  // 494:             func.is_undefined && left(1) <= right(1)
  // 495:             func.is_defined && not(func(right(1) left(1)))
  // 496:           :
  // 497:             push &result get(&left)
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
  // 511: ... self.is_empty
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
  // 511: ... : return "list()"
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_3, 0);
  // 511: if self.is_empty: return "list()"
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
  // 511: ... return "list()"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_4;
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
  // 512: $$buf "list"
  ((CELL *)frame->slots[3])->contents /* buf */ = string__34_6;
  // 513: ... : (item)
  // 514:   write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
  frame->slots[4] /* temp__1 */ = create_closure(entry__34_7, 1);
  // 513: for_each self: (item)
  // 514:   write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
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
  // 514: ... indent+2
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
  // 514: ... spaces(indent+2)
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
  // 514: ... indent+2
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
  // 514: ... serialize(item indent+2)
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
  // 514: write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
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
  // 515: -> buf
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
  // 523: $n length_of(self)
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
  // 526: 0, 1
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
  // 526: ... :
  // 527:   return self
  frame->slots[5] /* temp__2 */ = create_closure(entry__35_4, 0);
  // 528: ... :
  // 529:   if
  // 530:     ||
  // 531:       func.is_undefined && self(1) <= self(2)
  // 532:       func.is_defined && not(func(self(2) self(1)))
  // 533:     :
  // 534:       return self
  // 535:     :
  // 536:       return list(self(2) self(1))
  frame->slots[6] /* temp__3 */ = create_closure(entry__35_5, 0);
  // 537: :
  // 538:   $m n .div. 2
  // 539:   if
  // 540:     func.is_undefined:
  // 541:       return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  // 542:     :
  // 543:       return
  // 544:         merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  frame->slots[7] /* temp__4 */ = create_closure(entry__35_27, 0);
  // 524: case
  // 525:   n
  // 526:   0, 1:
  // 527:     return self
  // 528:   2:
  // 529:     if
  // 530:       ||
  // 531:         func.is_undefined && self(1) <= self(2)
  // 532:         func.is_defined && not(func(self(2) self(1)))
  // 533:       :
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
  // 541: ... range(self 1 m)
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
  // 541: ... sort(range(self 1 m))
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
  // 541: ... m+1
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
  // 541: ... range(self m+1 n)
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
  // 541: ... sort(range(self m+1 n))
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
  // 541: ... merge(sort(range(self 1 m)) sort(range(self m+1 n)))
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
  // 541: return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
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
  // 544: ... range(self 1 m)
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
  // 544: ... sort(range(self 1 m) func)
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
  // 544: ... m+1
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
  // 544: ... range(self m+1 n)
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
  // 544: ... sort(range(self m+1 n) func)
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
  // 544: merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
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
  // 543: return
  // 544:   merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
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
  // 534: return self
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
  // 536: ... self(2)
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
  // 536: ... self(1)
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
  // 536: ... list(self(2) self(1))
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
  // 536: return list(self(2) self(1))
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
  // 527: return self
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
  // 531: func.is_undefined
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
  // 531: ... self(1) <= self(2)
  frame->slots[6] /* temp__4 */ = create_closure(entry__35_7, 0);
  // 531: func.is_undefined && self(1) <= self(2)
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
  // 531: ... self(2)
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
  // 531: ... self(1)
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
  // 531: ... self(1) <= self(2)
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
  // 531: ... self(1) <= self(2)
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
  // 531: ... self(1) <= self(2)
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
  // 532: func.is_defined && not(func(self(2) self(1)))
  frame->slots[7] /* temp__5 */ = create_closure(entry__35_13, 0);
  // 530: ||
  // 531:   func.is_undefined && self(1) <= self(2)
  // 532:   func.is_defined && not(func(self(2) self(1)))
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
  // 532: func.is_defined
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
  // 532: ... not(func(self(2) self(1)))
  frame->slots[4] /* temp__3 */ = create_closure(entry__35_15, 0);
  // 532: func.is_defined && not(func(self(2) self(1)))
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
  // 532: ... self(2)
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
  // 532: ... self(1)
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
  // 532: ... func(self(2) self(1))
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
  // 532: ... not(func(self(2) self(1)))
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
  // 532: ... not(func(self(2) self(1)))
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
  // 532: func.is_defined && not(func(self(2) self(1)))
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
  // 533: :
  // 534:   return self
  frame->slots[8] /* temp__6 */ = create_closure(entry__35_22, 0);
  // 535: :
  // 536:   return list(self(2) self(1))
  frame->slots[9] /* temp__7 */ = create_closure(entry__35_23, 0);
  // 529: if
  // 530:   ||
  // 531:     func.is_undefined && self(1) <= self(2)
  // 532:     func.is_defined && not(func(self(2) self(1)))
  // 533:   :
  // 534:     return self
  // 535:   :
  // 536:     return list(self(2) self(1))
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
  // 538: $m n .div. 2
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
  // 540: func.is_undefined
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
  // 540: ... :
  // 541:   return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  frame->slots[6] /* temp__2 */ = create_closure(entry__35_30, 0);
  // 542: :
  // 543:   return
  // 544:     merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  frame->slots[7] /* temp__3 */ = create_closure(entry__35_37, 0);
  // 539: if
  // 540:   func.is_undefined:
  // 541:     return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  // 542:   :
  // 543:     return
  // 544:       merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
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
  // 581: -> types::list
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
  // 593: ... right.is_defined
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
  // 593: ... right.is_a_list
  frame->slots[5] /* temp__3 */ = create_closure(entry__38_3, 0);
  // 593: ... right.is_defined && right.is_a_list
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
  // 593: ... right.is_a_list
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
  // 593: ... right.is_a_list
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
  // 593: ... : return false
  frame->slots[6] /* temp__4 */ = create_closure(entry__38_6, 0);
  // 593: unless right.is_defined && right.is_a_list: return false
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
  // 593: ... return false
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
  // 594: ... length_of(left)
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
  // 594: ... length_of(right)
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
  // 594: ... length_of(left) != length_of(right)
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
  // 594: ... length_of(left) != length_of(right)
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
  // 594: ... : return false
  frame->slots[7] /* temp__5 */ = create_closure(entry__38_12, 0);
  // 594: if length_of(left) != length_of(right): return false
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
  // 594: ... return false
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
  // 595: ... : (idx item) if item != right(idx): return false
  frame->slots[3] /* temp__1 */ = create_closure(entry__38_14, 2);
  // 595: for_each left: (idx item) if item != right(idx): return false
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
  // 595: ... return false
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
  // 595: ... right(idx)
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
  // 595: ... item != right(idx)
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
  // 595: ... item != right(idx)
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
  // 595: ... : return false
  frame->slots[7] /* temp__4 */ = create_closure(entry__38_18, 0);
  // 595: ... if item != right(idx): return false
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
  // 596: -> true
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
  // 603: $$new_list new_empty_collection(self)
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
  // 604: ... : (item) if test(item): push &new_list item
  frame->slots[3] /* temp__1 */ = create_closure(entry__39_3, 1);
  // 604: for_each self: (item) if test(item): push &new_list item
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
  // 604: ... push &new_list item
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
  // 604: ... test(item)
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
  // 604: ... : push &new_list item
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_5, 0);
  // 604: ... if test(item): push &new_list item
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
  // 605: -> new_list
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
  // 612: $$new_list new_empty_collection(self)
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
  // 613: ... : (item) push &new_list func(item)
  frame->slots[3] /* temp__1 */ = create_closure(entry__40_3, 1);
  // 613: for_each self: (item) push &new_list func(item)
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
  // 613: ... func(item)
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
  // 613: ... push &new_list func(item)
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
  // 614: -> new_list
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
  // 622: ... -> self
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
  // 623: ... n < 0
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
  // 623: if n < 0: raise "Negative argument for dup!"
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
  // 623: ... raise "Negative argument for dup!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__41_6;
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
  // 624: ... n .div. 2
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
  // 624: $$result dup(self n .div. 2)
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
  // 625: append &result result
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
  // 626: ... n.is_odd
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
  // 626: ... : append &result self
  frame->slots[4] /* temp__2 */ = create_closure(entry__41_12, 0);
  // 626: if n.is_odd: append &result self
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
  // 626: ... append &result self
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
  // 627: -> result
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
  // 622: ... -> empty_list
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
  // 622: ... -> self
  frame->slots[2] /* temp__1 */ = create_closure(entry__41_2, 0);
  // 622: ... :
  // 623:   if n < 0: raise "Negative argument for dup!"
  // 624:   $$result dup(self n .div. 2)
  // 625:   append &result result
  // 626:   if n.is_odd: append &result self
  // 627:   -> result
  frame->slots[3] /* temp__2 */ = create_closure(entry__41_3, 0);
  // 622: case n 0 (-> empty_list) 1 (-> self):
  // 623:   if n < 0: raise "Negative argument for dup!"
  // 624:   $$result dup(self n .div. 2)
  // 625:   append &result result
  // 626:   if n.is_odd: append &result self
  // 627:   -> result
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
  // 638: ... lists(1)
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
  // 638: $n length_of(lists(1))
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
  // 639: $$result empty_list
  ((CELL *)frame->slots[2])->contents /* result */ = get__empty_list();
  // 640: ... n-1
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
  // 640: ... : (i) for_each lists: (current_list) push &result current_list(i)
  frame->slots[4] /* temp__2 */ = create_closure(entry__42_5, 1);
  // 640: from_to 1 n-1: (i) for_each lists: (current_list) push &result current_list(i)
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
  // 640: ... current_list(i)
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
  // 640: ... push &result current_list(i)
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
  // 640: ... : (current_list) push &result current_list(i)
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_6, 1);
  // 640: ... for_each lists: (current_list) push &result current_list(i)
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
  // 641: ... : (current_list)
  // 642:   if length_of(current_list) >= n: push &result current_list(n)
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_10, 1);
  // 641: for_each lists: (current_list)
  // 642:   if length_of(current_list) >= n: push &result current_list(n)
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
  // 642: ... current_list(n)
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
  // 642: ... push &result current_list(n)
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
  // 642: ... length_of(current_list)
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
  // 642: ... length_of(current_list) >= n
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
  // 642: ... length_of(current_list) >= n
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
  // 642: ... : push &result current_list(n)
  frame->slots[6] /* temp__4 */ = create_closure(entry__42_14, 0);
  // 642: if length_of(current_list) >= n: push &result current_list(n)
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
  // 643: -> result
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
  // 651: ... : (current_item) if current_item == item: return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__43_2, 1);
  // 651: for_each self: (current_item) if current_item == item: return true
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
  // 651: ... return true
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
  // 651: ... current_item == item
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
  // 651: ... : return true
  frame->slots[4] /* temp__2 */ = create_closure(entry__43_4, 0);
  // 651: ... if current_item == item: return true
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
  // 652: -> false
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
  // 672: ... : (item)
  // 673:   if item == element || item .contains. element: return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__46_4, 1);
  // 672: for_each self: (item)
  // 673:   if item == element || item .contains. element: return true
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
  // 673: ... return true
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
  // 673: ... item == element
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
  // 673: ... item .contains. element
  frame->slots[5] /* temp__3 */ = create_closure(entry__46_6, 0);
  // 673: ... item == element || item .contains. element
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
  // 673: ... item .contains. element
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
  // 673: ... item .contains. element
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
  // 673: ... : return true
  frame->slots[6] /* temp__4 */ = create_closure(entry__46_9, 0);
  // 673: if item == element || item .contains. element: return true
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
  // 674: -> false
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
  // 664: list(items*)
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
  // 664: list(items*)
  // 665:   .is_a_sequence true
  // 666:   /contains:
  // 667:     (
  // 668:       self
  // 669:       element
  // 670:       -> return
  // 671:     )
  // 672:     for_each self: (item)
  // 673:       if item == element || item .contains. element: return true
  // ...
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_sequence, get__true());
    set_attribute(temp->attributes, poly_idx__contains, func__46_3);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 663: ->
  // 664:   list(items*)
  // 665:     .is_a_sequence true
  // 666:     /contains:
  // 667:       (
  // 668:         self
  // 669:         element
  // 670:         -> return
  // 671:       )
  // 672:       for_each self: (item)
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
  string__31_5 = from_latin_1_string("Attempt to get an element from an empty list!", 45);
  func__31_4 = create_function(entry__31_4, 0);
  func__31_1_types__generic_list_get = create_function(entry__31_1_types__generic_list_get, 1);
  func__32_1_types__list_put = create_function(entry__32_1_types__list_put, 2);
  func__33_1_types__list_merge = create_function(entry__33_1_types__list_merge, -1);
  string__34_4 = from_latin_1_string("list()", 6);
  string__34_6 = from_latin_1_string("list", 4);
  func__34_1_types__list_serialize = create_function(entry__34_1_types__list_serialize, -1);
  func__35_1_types__list_sort = create_function(entry__35_1_types__list_sort, -1);
  func__37_1_types__list_new_empty_collection = create_function(entry__37_1_types__list_new_empty_collection, 1);
  func__38_1_types__generic_list_equal = create_function(entry__38_1_types__generic_list_equal, 2);
  func__39_1_types__generic_list_filter = create_function(entry__39_1_types__generic_list_filter, 2);
  func__40_1_types__generic_list_map = create_function(entry__40_1_types__generic_list_map, 2);
  string__41_6 = from_latin_1_string("Negative argument for dup!", 26);
  func__41_5 = create_function(entry__41_5, 0);
  func__41_15 = create_function(entry__41_15, 0);
  func__41_1_types__generic_list_dup = create_function(entry__41_1_types__generic_list_dup, 2);
  func__42_1_types__generic_list_interleave = create_function(entry__42_1_types__generic_list_interleave, -1);
  func__43_1_types__generic_list_contains = create_function(entry__43_1_types__generic_list_contains, 2);
  func__46_3 = create_function(entry__46_3, 2);
  func__46_1_std__sequence = create_function(entry__46_1_std__sequence, -1);
  string__94_2 = from_latin_1_string("()", 2);
  string__94_12 = from_latin_1_string("Invalid list object encountered during deserialisation!", 55);
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
