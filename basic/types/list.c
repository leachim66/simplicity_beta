#include <string.h>
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
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
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
#define IS_OLD(addr) false
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
static NODE *func__14_1;
static void entry__14_1(void);
static FRAME_INFO frame__14_1 = {1, {"self"}};
static void entry__15_1(void);
static NODE *func__15_1;
static NODE *get__std__list(void) {
  return var.std__list;
}
static void entry__16_1(void);
static NODE *func__16_1;
static void entry__17_1(void);
static NODE *func__17_1;
static void entry__18_1(void);
static NODE *func__18_1;
static void entry__19_1(void);
static NODE *func__19_1;
static void entry__20_1(void);
static NODE *func__20_1;
static void entry__21_1(void);
static NODE *func__21_1;
static void entry__22_1(void);
static NODE *func__22_1;
static NODE *func__23_1;
static void entry__23_1(void);
static FRAME_INFO frame__23_1 = {3, {"self", "idx", "count"}};
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
static NODE *func__24_1;
static void entry__24_1(void);
static FRAME_INFO frame__24_1 = {3, {"self", "idx", "return"}};
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
static NODE *func__25_1;
static void entry__25_1(void);
static FRAME_INFO frame__25_1 = {1, {"self"}};
static void cont__25_2(void);
static void cont__25_3(void);
static NODE *func__26_1;
static void entry__26_1(void);
static FRAME_INFO frame__26_1 = {7, {"self", "first", "last", "body", "body2", "i", "n"}};
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
static NODE *func__27_1;
static void entry__27_1(void);
static FRAME_INFO frame__27_1 = {7, {"self", "first", "last", "body", "body2", "i", "n"}};
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
static NODE *func__28_1;
static void entry__28_1(void);
static FRAME_INFO frame__28_1 = {5, {"self", "body", "body2", "i", "n"}};
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
static NODE *func__29_1;
static void entry__29_1(void);
static FRAME_INFO frame__29_1 = {6, {"self", "body", "return", "i", "n", "new_list"}};
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
static NODE *func__30_1;
static void entry__30_1(void);
static FRAME_INFO frame__30_1 = {4, {"self", "body", "i", "n"}};
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
static NODE *func__31_1;
static void entry__31_1(void);
static FRAME_INFO frame__31_1 = {1, {"self"}};
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
static NODE *func__32_1;
static void entry__32_1(void);
static FRAME_INFO frame__32_1 = {2, {"self", "item"}};
static void cont__32_2(void);
static void cont__32_3(void);
static NODE *func__33_1;
static void entry__33_1(void);
static FRAME_INFO frame__33_1 = {5, {"left", "right", "func", "return", "result"}};
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
static NODE *func__34_1;
static void entry__34_1(void);
static FRAME_INFO frame__34_1 = {4, {"self", "indent", "return", "buf"}};
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
static NODE *func__35_1;
static void entry__35_1(void);
static FRAME_INFO frame__35_1 = {4, {"self", "func", "return", "n"}};
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
static NODE *func__37_1;
static void entry__37_1(void);
static FRAME_INFO frame__37_1 = {1, {"self"}};
static NODE *func__38_1;
static void entry__38_1(void);
static FRAME_INFO frame__38_1 = {3, {"left", "right", "return"}};
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
static NODE *func__39_1;
static void entry__39_1(void);
static FRAME_INFO frame__39_1 = {3, {"self", "test", "new_list"}};
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
static NODE *func__40_1;
static void entry__40_1(void);
static FRAME_INFO frame__40_1 = {3, {"self", "func", "new_list"}};
static void cont__40_2(void);
static NODE *func__40_3;
static void entry__40_3(void);
static FRAME_INFO frame__40_3 = {3, {"item", "new_list", "func"}};
static void cont__40_4(void);
static void cont__40_5(void);
static void cont__40_6(void);
static NODE *func__41_1;
static void entry__41_1(void);
static FRAME_INFO frame__41_1 = {2, {"self", "n"}};
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
static NODE *func__42_1;
static void entry__42_1(void);
static FRAME_INFO frame__42_1 = {3, {"lists", "n", "result"}};
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
static NODE *func__43_1;
static void entry__43_1(void);
static FRAME_INFO frame__43_1 = {3, {"self", "item", "return"}};
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
static NODE *func__46_1;
static void entry__46_1(void);
static FRAME_INFO frame__46_1 = {1, {"items"}};
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
static NODE *string__94_1;
static NODE *func__94_2;
static void entry__94_2(void);
static FRAME_INFO frame__94_2 = {4, {"text", "base_indent", "return", "obj"}};
static NODE *string__94_3;
static void cont__94_4(void);
static NODE *func__94_5;
static void entry__94_5(void);
static FRAME_INFO frame__94_5 = {2, {"return", "text"}};
static void cont__94_6(void);
static void cont__94_7(void);
static void cont__94_8(void);
static void cont__94_9(void);
static void cont__94_10(void);
static void cont__94_11(void);
static NODE *func__94_12;
static void entry__94_12(void);
static FRAME_INFO frame__94_12 = {0, {}};
static NODE *string__94_13;
static void cont__94_14(void);
static NODE *func__94_15;
static void entry__94_15(void);
static FRAME_INFO frame__94_15 = {6, {"text", "return", "obj", "base_indent", "remaining_text", "indent"}};
static void cont__94_16(void);
static void cont__94_17(void);
static NODE *func__94_18;
static void entry__94_18(void);
static FRAME_INFO frame__94_18 = {1, {"text"}};
static void cont__94_19(void);
static void cont__94_20(void);
static void cont__94_21(void);
static void cont__94_22(void);
static NODE *func__94_23;
static void entry__94_23(void);
static FRAME_INFO frame__94_23 = {3, {"return", "text", "obj"}};
static void cont__94_24(void);
static void cont__94_25(void);
static void cont__94_26(void);
static void cont__94_27(void);
static NODE *func__94_28;
static void entry__94_28(void);
static FRAME_INFO frame__94_28 = {3, {"return", "text", "obj"}};
static void cont__94_29(void);
static void cont__94_30(void);
static void cont__94_31(void);
static void cont__94_32(void);
static void cont__94_33(void);
void run__basic__types__list(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_list, NULL, 25, 25, 2, 15},
  {type__std__is_a_sequence, NULL, 568, 568, 2, 19},
  {run__basic__types__list, NULL, 586, 601, 1, 45},
  {cont__94_33, NULL, },
  {entry__14_1, NULL, 164, 164, 30, 36},
  {entry__15_1, NULL, 167, 179, 3, 2},
  {entry__16_1, NULL, 182, 185, 3, 2},
  {entry__17_1, NULL, 188, 206, 3, 2},
  {entry__18_1, NULL, 209, 216, 3, 2},
  {entry__19_1, NULL, 219, 230, 3, 2},
  {entry__20_1, NULL, 233, 239, 3, 2},
  {entry__21_1, NULL, 242, 267, 3, 2},
  {entry__22_1, NULL, 270, 291, 3, 2},
  {entry__23_4, NULL, 300, 300, 44, 48},
  {cont__23_5, &frame__23_4, 300, 300, 31, 49},
  {cont__23_6, &frame__23_4, 300, 300, 62, 70},
  {cont__23_7, &frame__23_4, 300, 300, 73, 73},
  {cont__23_8, &frame__23_4, 300, 300, 51, 74},
  {cont__23_9, &frame__23_4, 300, 300, 18, 75},
  {cont__23_10, &frame__23_4, 300, 300, 75, 75},
  {entry__23_1, NULL, 300, 300, 6, 15},
  {cont__23_2, &frame__23_1, 300, 300, 6, 15},
  {cont__23_3, &frame__23_1, 300, 300, 3, 75},
  {cont__23_11, &frame__23_1, },
  {entry__24_4, NULL, 310, 310, 7, 16},
  {entry__24_5, NULL, 312, 312, 14, 28},
  {cont__24_6, &frame__24_5, 312, 312, 14, 30},
  {cont__24_7, &frame__24_5, 312, 312, 14, 34},
  {cont__24_8, &frame__24_5, 312, 312, 7, 34},
  {entry__24_1, NULL, 309, 309, 5, 12},
  {cont__24_2, &frame__24_1, 309, 309, 5, 12},
  {cont__24_3, &frame__24_1, 308, 312, 3, 35},
  {cont__24_9, &frame__24_1, 312, 312, 35, 35},
  {entry__25_1, NULL, 314, 314, 42, 56},
  {cont__25_2, &frame__25_1, 314, 314, 42, 61},
  {cont__25_3, &frame__25_1, 314, 314, 39, 61},
  {entry__26_10, NULL, 341, 341, 16, 22},
  {cont__26_11, &frame__26_10, 341, 341, 9, 22},
  {entry__26_12, NULL, 343, 343, 14, 20},
  {cont__26_13, &frame__26_12, 343, 343, 9, 20},
  {entry__26_16, NULL, 344, 344, 28, 32},
  {cont__26_17, &frame__26_16, 344, 344, 28, 32},
  {entry__26_19, NULL, 344, 344, 35, 39},
  {entry__26_7, NULL, 340, 340, 7, 30},
  {cont__26_8, &frame__26_7, 340, 340, 7, 35},
  {cont__26_9, &frame__26_7, 339, 343, 5, 21},
  {cont__26_14, &frame__26_7, 344, 344, 8, 23},
  {cont__26_15, &frame__26_7, 344, 344, 8, 32},
  {cont__26_18, &frame__26_7, 344, 344, 5, 39},
  {cont__26_20, &frame__26_7, 345, 345, 5, 13},
  {cont__26_21, &frame__26_7, 345, 345, 13, 13},
  {entry__26_4, NULL, 338, 338, 12, 17},
  {cont__26_5, &frame__26_4, 338, 338, 12, 17},
  {cont__26_6, &frame__26_4, 338, 345, 9, 13},
  {entry__26_1, NULL, 336, 336, 3, 34},
  {cont__26_2, &frame__26_1, 337, 337, 3, 32},
  {cont__26_3, &frame__26_1, 338, 345, 3, 13},
  {entry__27_10, NULL, 353, 353, 16, 22},
  {cont__27_11, &frame__27_10, 353, 353, 9, 22},
  {entry__27_12, NULL, 355, 355, 14, 20},
  {cont__27_13, &frame__27_12, 355, 355, 9, 20},
  {entry__27_16, NULL, 356, 356, 28, 32},
  {cont__27_17, &frame__27_16, 356, 356, 28, 32},
  {entry__27_19, NULL, 356, 356, 35, 39},
  {entry__27_7, NULL, 352, 352, 7, 30},
  {cont__27_8, &frame__27_7, 352, 352, 7, 35},
  {cont__27_9, &frame__27_7, 351, 355, 5, 21},
  {cont__27_14, &frame__27_7, 356, 356, 8, 23},
  {cont__27_15, &frame__27_7, 356, 356, 8, 32},
  {cont__27_18, &frame__27_7, 356, 356, 5, 39},
  {cont__27_20, &frame__27_7, 357, 357, 5, 14},
  {cont__27_21, &frame__27_7, 357, 357, 14, 14},
  {entry__27_4, NULL, 350, 350, 12, 17},
  {cont__27_5, &frame__27_4, 350, 350, 12, 17},
  {cont__27_6, &frame__27_4, 350, 357, 9, 14},
  {entry__27_1, NULL, 348, 348, 3, 34},
  {cont__27_2, &frame__27_1, 349, 349, 3, 32},
  {cont__27_3, &frame__27_1, 350, 357, 3, 14},
  {entry__28_13, NULL, 366, 366, 32, 36},
  {cont__28_14, &frame__28_13, 366, 366, 32, 36},
  {entry__28_16, NULL, 366, 366, 39, 43},
  {entry__28_9, NULL, 365, 365, 16, 22},
  {cont__28_10, &frame__28_9, 365, 365, 9, 22},
  {cont__28_11, &frame__28_9, 366, 366, 12, 27},
  {cont__28_12, &frame__28_9, 366, 366, 12, 36},
  {cont__28_15, &frame__28_9, 366, 366, 9, 43},
  {cont__28_17, &frame__28_9, 367, 367, 9, 17},
  {cont__28_18, &frame__28_9, 367, 367, 17, 17},
  {entry__28_6, NULL, 364, 364, 16, 21},
  {cont__28_7, &frame__28_6, 364, 364, 16, 21},
  {cont__28_8, &frame__28_6, 364, 367, 13, 17},
  {entry__28_5, NULL, 364, 367, 7, 17},
  {entry__28_27, NULL, 371, 371, 32, 36},
  {cont__28_28, &frame__28_27, 371, 371, 32, 36},
  {entry__28_30, NULL, 371, 371, 39, 43},
  {entry__28_23, NULL, 370, 370, 14, 20},
  {cont__28_24, &frame__28_23, 370, 370, 9, 20},
  {cont__28_25, &frame__28_23, 371, 371, 12, 27},
  {cont__28_26, &frame__28_23, 371, 371, 12, 36},
  {cont__28_29, &frame__28_23, 371, 371, 9, 43},
  {cont__28_31, &frame__28_23, 372, 372, 9, 17},
  {cont__28_32, &frame__28_23, 372, 372, 17, 17},
  {entry__28_20, NULL, 369, 369, 16, 21},
  {cont__28_21, &frame__28_20, 369, 369, 16, 21},
  {cont__28_22, &frame__28_20, 369, 372, 13, 17},
  {entry__28_19, NULL, 369, 372, 7, 17},
  {entry__28_1, NULL, 361, 361, 3, 20},
  {cont__28_2, &frame__28_1, 363, 363, 5, 28},
  {cont__28_3, &frame__28_1, 363, 363, 5, 33},
  {cont__28_4, &frame__28_1, 362, 372, 3, 19},
  {entry__29_9, NULL, 386, 386, 31, 37},
  {cont__29_10, &frame__29_9, 386, 386, 24, 38},
  {cont__29_11, &frame__29_9, 386, 386, 9, 38},
  {cont__29_12, &frame__29_9, 387, 387, 9, 17},
  {cont__29_13, &frame__29_9, 387, 387, 17, 17},
  {entry__29_6, NULL, 385, 385, 16, 21},
  {cont__29_7, &frame__29_6, 385, 385, 16, 21},
  {cont__29_8, &frame__29_6, 385, 387, 13, 17},
  {entry__29_5, NULL, 385, 387, 7, 17},
  {entry__29_18, NULL, 390, 390, 29, 35},
  {cont__29_19, &frame__29_18, 390, 390, 24, 36},
  {cont__29_20, &frame__29_18, 390, 390, 9, 36},
  {cont__29_21, &frame__29_18, 391, 391, 9, 17},
  {cont__29_22, &frame__29_18, 391, 391, 17, 17},
  {entry__29_15, NULL, 389, 389, 16, 21},
  {cont__29_16, &frame__29_15, 389, 389, 16, 21},
  {cont__29_17, &frame__29_15, 389, 391, 13, 17},
  {entry__29_14, NULL, 389, 391, 7, 17},
  {entry__29_1, NULL, 381, 381, 3, 20},
  {cont__29_2, &frame__29_1, 384, 384, 5, 28},
  {cont__29_3, &frame__29_1, 384, 384, 5, 33},
  {cont__29_4, &frame__29_1, 383, 391, 3, 19},
  {cont__29_23, &frame__29_1, 392, 392, 3, 17},
  {cont__29_24, &frame__29_1, 392, 392, 17, 17},
  {entry__30_5, NULL, 398, 398, 10, 16},
  {cont__30_6, &frame__30_5, 398, 398, 23, 25},
  {cont__30_7, &frame__30_5, 398, 398, 18, 26},
  {cont__30_8, &frame__30_5, 398, 398, 5, 26},
  {cont__30_9, &frame__30_5, 399, 399, 5, 13},
  {cont__30_10, &frame__30_5, 399, 399, 13, 13},
  {entry__30_3, NULL, 397, 397, 12, 16},
  {cont__30_4, &frame__30_3, 397, 399, 9, 13},
  {entry__30_13, NULL, 400, 400, 22, 28},
  {cont__30_14, &frame__30_13, 400, 400, 17, 28},
  {entry__30_1, NULL, 396, 396, 3, 20},
  {cont__30_2, &frame__30_1, 397, 399, 3, 13},
  {cont__30_11, &frame__30_1, 400, 400, 6, 14},
  {cont__30_12, &frame__30_1, 400, 400, 3, 28},
  {entry__31_4, NULL, 403, 403, 28, 80},
  {entry__31_1, NULL, 403, 403, 6, 20},
  {cont__31_2, &frame__31_1, 403, 403, 6, 25},
  {cont__31_3, &frame__31_1, 403, 403, 3, 80},
  {cont__31_6, &frame__31_1, 404, 404, 20, 20},
  {cont__31_7, &frame__31_1, 404, 404, 6, 21},
  {cont__31_8, &frame__31_1, 404, 404, 23, 29},
  {cont__31_9, &frame__31_1, 404, 404, 3, 29},
  {entry__32_1, NULL, 406, 406, 41, 50},
  {cont__32_2, &frame__32_1, 406, 406, 34, 56},
  {cont__32_3, &frame__32_1, 406, 406, 31, 56},
  {entry__33_11, NULL, 423, 423, 49, 56},
  {cont__33_12, &frame__33_11, 423, 423, 38, 44},
  {cont__33_13, &frame__33_11, 423, 423, 38, 56},
  {cont__33_14, &frame__33_11, 423, 423, 38, 56},
  {cont__33_15, &frame__33_11, 423, 423, 38, 56},
  {entry__33_19, NULL, 424, 424, 45, 52},
  {cont__33_20, &frame__33_19, 424, 424, 54, 60},
  {cont__33_21, &frame__33_19, 424, 424, 40, 61},
  {cont__33_22, &frame__33_19, 424, 424, 36, 62},
  {cont__33_23, &frame__33_19, 424, 424, 36, 62},
  {entry__33_17, NULL, 424, 424, 17, 31},
  {cont__33_18, &frame__33_17, 424, 424, 17, 62},
  {cont__33_24, &frame__33_17, 424, 424, 17, 62},
  {entry__33_26, NULL, 426, 426, 30, 39},
  {cont__33_27, &frame__33_26, 426, 426, 17, 39},
  {cont__33_28, &frame__33_26, 426, 426, 39, 39},
  {entry__33_29, NULL, 428, 428, 30, 40},
  {cont__33_30, &frame__33_29, 428, 428, 17, 40},
  {cont__33_31, &frame__33_29, 428, 428, 40, 40},
  {entry__33_9, NULL, 423, 423, 17, 33},
  {cont__33_10, &frame__33_9, 423, 423, 17, 56},
  {cont__33_16, &frame__33_9, 422, 424, 15, 61},
  {cont__33_25, &frame__33_9, 421, 428, 13, 41},
  {entry__33_32, NULL, 430, 430, 20, 38},
  {cont__33_33, &frame__33_32, 430, 430, 13, 38},
  {entry__33_6, NULL, 420, 420, 11, 26},
  {cont__33_7, &frame__33_6, 420, 420, 11, 30},
  {cont__33_8, &frame__33_6, 419, 430, 9, 39},
  {entry__33_34, NULL, 432, 432, 16, 35},
  {cont__33_35, &frame__33_34, 432, 432, 9, 35},
  {entry__33_3, NULL, 418, 418, 7, 21},
  {cont__33_4, &frame__33_3, 418, 418, 7, 25},
  {cont__33_5, &frame__33_3, 417, 432, 5, 36},
  {entry__33_1, NULL, 415, 415, 3, 17},
  {cont__33_2, &frame__33_1, 416, 432, 3, 37},
  {cont__33_36, &frame__33_1, 432, 432, 37, 37},
  {entry__34_3, NULL, 440, 440, 21, 35},
  {entry__34_7, NULL, 443, 443, 33, 40},
  {cont__34_8, &frame__34_7, 443, 443, 26, 41},
  {cont__34_9, &frame__34_7, 443, 443, 58, 65},
  {cont__34_10, &frame__34_7, 443, 443, 43, 66},
  {cont__34_11, &frame__34_7, 443, 443, 5, 66},
  {cont__34_12, &frame__34_7, 443, 443, 66, 66},
  {entry__34_1, NULL, 440, 440, 6, 18},
  {cont__34_2, &frame__34_1, 440, 440, 3, 35},
  {cont__34_5, &frame__34_1, 442, 443, 3, 66},
  {cont__34_13, &frame__34_1, 444, 444, 3, 8},
  {entry__35_4, NULL, 456, 456, 7, 17},
  {entry__35_7, NULL, 460, 460, 43, 49},
  {cont__35_8, &frame__35_7, 460, 460, 32, 38},
  {cont__35_9, &frame__35_7, 460, 460, 32, 49},
  {cont__35_10, &frame__35_7, 460, 460, 32, 49},
  {cont__35_11, &frame__35_7, 460, 460, 32, 49},
  {entry__35_15, NULL, 461, 461, 39, 45},
  {cont__35_16, &frame__35_15, 461, 461, 47, 53},
  {cont__35_17, &frame__35_15, 461, 461, 34, 54},
  {cont__35_18, &frame__35_15, 461, 461, 30, 55},
  {cont__35_19, &frame__35_15, 461, 461, 30, 55},
  {entry__35_13, NULL, 461, 461, 11, 25},
  {cont__35_14, &frame__35_13, 461, 461, 11, 55},
  {cont__35_20, &frame__35_13, 461, 461, 11, 55},
  {entry__35_22, NULL, 463, 463, 11, 21},
  {entry__35_23, NULL, 465, 465, 23, 29},
  {cont__35_24, &frame__35_23, 465, 465, 31, 37},
  {cont__35_25, &frame__35_23, 465, 465, 18, 38},
  {cont__35_26, &frame__35_23, 465, 465, 11, 38},
  {entry__35_5, NULL, 460, 460, 11, 27},
  {cont__35_6, &frame__35_5, 460, 460, 11, 49},
  {cont__35_12, &frame__35_5, 459, 461, 9, 54},
  {cont__35_21, &frame__35_5, 458, 465, 7, 39},
  {entry__35_30, NULL, 470, 470, 29, 43},
  {cont__35_31, &frame__35_30, 470, 470, 24, 44},
  {cont__35_32, &frame__35_30, 470, 470, 62, 64},
  {cont__35_33, &frame__35_30, 470, 470, 51, 67},
  {cont__35_34, &frame__35_30, 470, 470, 46, 68},
  {cont__35_35, &frame__35_30, 470, 470, 18, 69},
  {cont__35_36, &frame__35_30, 470, 470, 11, 69},
  {entry__35_37, NULL, 473, 473, 24, 38},
  {cont__35_38, &frame__35_37, 473, 473, 19, 44},
  {cont__35_39, &frame__35_37, 473, 473, 62, 64},
  {cont__35_40, &frame__35_37, 473, 473, 51, 67},
  {cont__35_41, &frame__35_37, 473, 473, 46, 73},
  {cont__35_42, &frame__35_37, 473, 473, 13, 79},
  {cont__35_43, &frame__35_37, 472, 473, 11, 79},
  {entry__35_27, NULL, 467, 467, 7, 18},
  {cont__35_28, &frame__35_27, 469, 469, 9, 25},
  {cont__35_29, &frame__35_27, 468, 473, 7, 81},
  {entry__35_1, NULL, 452, 452, 3, 20},
  {cont__35_2, &frame__35_1, 455, 455, 5, 8},
  {cont__35_3, &frame__35_1, 453, 473, 3, 83},
  {cont__35_44, &frame__35_1, 473, 473, 83, 83},
  {entry__37_1, NULL, 504, 504, 44, 57},
  {entry__38_3, NULL, 516, 516, 30, 44},
  {cont__38_4, &frame__38_3, 516, 516, 30, 44},
  {entry__38_6, NULL, 516, 516, 47, 58},
  {entry__38_12, NULL, 517, 517, 43, 54},
  {entry__38_18, NULL, 518, 518, 52, 63},
  {entry__38_14, NULL, 518, 518, 40, 49},
  {cont__38_15, &frame__38_14, 518, 518, 32, 49},
  {cont__38_16, &frame__38_14, 518, 518, 32, 49},
  {cont__38_17, &frame__38_14, 518, 518, 29, 63},
  {entry__38_1, NULL, 516, 516, 10, 25},
  {cont__38_2, &frame__38_1, 516, 516, 10, 44},
  {cont__38_5, &frame__38_1, 516, 516, 3, 58},
  {cont__38_7, &frame__38_1, 517, 517, 6, 20},
  {cont__38_8, &frame__38_1, 517, 517, 25, 40},
  {cont__38_9, &frame__38_1, 517, 517, 6, 40},
  {cont__38_10, &frame__38_1, 517, 517, 6, 40},
  {cont__38_11, &frame__38_1, 517, 517, 3, 54},
  {cont__38_13, &frame__38_1, 518, 518, 3, 63},
  {cont__38_19, &frame__38_1, 519, 519, 3, 9},
  {entry__39_5, NULL, 523, 523, 40, 58},
  {cont__39_6, &frame__39_5, 523, 523, 58, 58},
  {entry__39_3, NULL, 523, 523, 28, 37},
  {cont__39_4, &frame__39_3, 523, 523, 25, 58},
  {entry__39_1, NULL, 522, 522, 3, 39},
  {cont__39_2, &frame__39_1, 523, 523, 3, 58},
  {cont__39_7, &frame__39_1, 524, 524, 3, 13},
  {entry__40_3, NULL, 528, 528, 40, 49},
  {cont__40_4, &frame__40_3, 528, 528, 25, 49},
  {cont__40_5, &frame__40_3, 528, 528, 49, 49},
  {entry__40_1, NULL, 527, 527, 3, 39},
  {cont__40_2, &frame__40_1, 528, 528, 3, 49},
  {cont__40_6, &frame__40_1, 529, 529, 3, 13},
  {entry__41_2, NULL, 537, 537, 31, 37},
  {entry__41_5, NULL, 538, 538, 15, 48},
  {entry__41_12, NULL, 541, 541, 18, 36},
  {cont__41_13, &frame__41_12, 541, 541, 36, 36},
  {entry__41_3, NULL, 538, 538, 8, 12},
  {cont__41_4, &frame__41_3, 538, 538, 5, 48},
  {cont__41_7, &frame__41_3, 539, 539, 23, 31},
  {cont__41_8, &frame__41_3, 539, 539, 5, 32},
  {cont__41_9, &frame__41_3, 540, 540, 5, 25},
  {cont__41_10, &frame__41_3, 541, 541, 8, 15},
  {cont__41_11, &frame__41_3, 541, 541, 5, 36},
  {cont__41_14, &frame__41_3, 542, 542, 5, 13},
  {entry__41_15, NULL, 537, 537, 13, 25},
  {entry__41_1, NULL, 537, 542, 3, 13},
  {entry__42_6, NULL, 554, 554, 66, 80},
  {cont__42_7, &frame__42_6, 554, 554, 53, 80},
  {cont__42_8, &frame__42_6, 554, 554, 80, 80},
  {entry__42_5, NULL, 554, 554, 22, 80},
  {entry__42_14, NULL, 556, 556, 51, 65},
  {cont__42_15, &frame__42_14, 556, 556, 38, 65},
  {cont__42_16, &frame__42_14, 556, 556, 65, 65},
  {entry__42_10, NULL, 556, 556, 8, 30},
  {cont__42_11, &frame__42_10, 556, 556, 8, 35},
  {cont__42_12, &frame__42_10, 556, 556, 8, 35},
  {cont__42_13, &frame__42_10, 556, 556, 5, 65},
  {entry__42_1, NULL, 552, 552, 16, 23},
  {cont__42_2, &frame__42_1, 552, 552, 3, 24},
  {cont__42_3, &frame__42_1, 554, 554, 13, 15},
  {cont__42_4, &frame__42_1, 554, 554, 3, 80},
  {cont__42_9, &frame__42_1, 555, 556, 3, 65},
  {cont__42_17, &frame__42_1, 557, 557, 3, 11},
  {entry__43_4, NULL, 565, 565, 58, 68},
  {entry__43_2, NULL, 565, 565, 36, 55},
  {cont__43_3, &frame__43_2, 565, 565, 33, 68},
  {entry__43_1, NULL, 565, 565, 3, 68},
  {cont__43_5, &frame__43_1, 566, 566, 3, 10},
  {entry__46_6, NULL, 583, 583, 33, 55},
  {cont__46_7, &frame__46_6, 583, 583, 33, 55},
  {entry__46_9, NULL, 583, 583, 58, 68},
  {entry__46_4, NULL, 583, 583, 14, 28},
  {cont__46_5, &frame__46_4, 583, 583, 14, 55},
  {cont__46_8, &frame__46_4, 583, 583, 11, 68},
  {entry__46_3, NULL, 582, 583, 9, 68},
  {cont__46_10, &frame__46_3, 584, 584, 9, 16},
  {entry__46_1, NULL, 574, 574, 5, 16},
  {cont__46_2, &frame__46_1, 573, 584, 3, 18},
  {entry__94_5, NULL, 592, 592, 51, 51},
  {cont__94_6, &frame__94_5, 592, 592, 37, 52},
  {cont__94_7, &frame__94_5, 592, 592, 30, 63},
  {entry__94_12, NULL, 594, 594, 5, 67},
  {entry__94_18, NULL, 597, 597, 32, 38},
  {cont__94_19, &frame__94_18, 597, 597, 32, 48},
  {cont__94_20, &frame__94_18, 597, 597, 32, 48},
  {cont__94_21, &frame__94_18, 597, 597, 32, 48},
  {entry__94_23, NULL, 597, 597, 51, 65},
  {entry__94_28, NULL, 599, 599, 31, 45},
  {entry__94_15, NULL, 597, 597, 8, 22},
  {cont__94_16, &frame__94_15, 597, 597, 8, 27},
  {cont__94_17, &frame__94_15, 597, 597, 8, 48},
  {cont__94_22, &frame__94_15, 597, 597, 5, 65},
  {cont__94_24, &frame__94_15, 598, 598, 5, 59},
  {cont__94_25, &frame__94_15, 599, 599, 8, 28},
  {cont__94_26, &frame__94_15, 599, 599, 8, 28},
  {cont__94_27, &frame__94_15, 599, 599, 5, 45},
  {cont__94_29, &frame__94_15, 601, 601, 15, 44},
  {cont__94_30, &frame__94_15, 601, 601, 5, 44},
  {cont__94_31, &frame__94_15, 601, 601, 44, 44},
  {entry__94_2, NULL, 592, 592, 6, 27},
  {cont__94_4, &frame__94_2, 592, 592, 3, 63},
  {cont__94_8, &frame__94_2, 593, 593, 6, 12},
  {cont__94_9, &frame__94_2, 593, 593, 6, 22},
  {cont__94_10, &frame__94_2, 593, 593, 6, 22},
  {cont__94_11, &frame__94_2, 593, 594, 3, 67},
  {cont__94_14, &frame__94_2, 596, 601, 3, 44},
  {cont__94_32, &frame__94_2, 601, 601, 44, 44}
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
  // 586: register_deserializer "list":
  // 587:   (
  // 588:     $text
  // 589:     base_indent
  // 590:     -> return
  // 591:   )
  // 592:   if text .has_prefix. "()": return range(text 3 -1) empty_list
  // 593:   if text(1) != '@nl;':
  // 594:     raise "Invalid list object encountered during deserialisation!"
  // 595:   $$obj empty_list
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__94_1;
  arguments->slots[1] = func__94_2;
  result_count = 0;
  myself = get__register_deserializer();
  func = myself->type;
  frame->cont = cont__94_33;
}
static void entry__94_2(void) {
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
  // 592: ... text .has_prefix. "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = string__94_3;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__94_4;
}
static void cont__94_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 592: ... : return range(text 3 -1) empty_list
  frame->slots[5] /* temp__2 */ = create_closure(entry__94_5, 0);
  // 592: if text .has_prefix. "()": return range(text 3 -1) empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__94_8;
}
static void entry__94_5(void) {
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
  // 592: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__94_6;
}
static void cont__94_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 592: ... range(text 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__94_7;
}
static void cont__94_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 592: ... return range(text 3 -1) empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__94_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 593: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__94_9;
}
static void cont__94_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 593: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__94_10;
}
static void cont__94_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 593: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__94_11;
}
static void cont__94_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 593: if text(1) != '@nl;':
  // 594:   raise "Invalid list object encountered during deserialisation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__94_12;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__94_14;
}
static void entry__94_12(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 594: raise "Invalid list object encountered during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__94_13;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__94_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 595: $$obj empty_list
  ((CELL *)frame->slots[3])->contents /* obj */ = get__empty_list();
  // 596: ... :
  // 597:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 598:   get_deserialization_indent $remaining_text $indent text
  // 599:   if indent <= base_indent: return text obj
  // 600:   !text remaining_text
  // 601:   push &obj deserialize_item(&text indent)
  frame->slots[4] /* temp__1 */ = create_closure(entry__94_15, 0);
  // 596: forever:
  // 597:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 598:   get_deserialization_indent $remaining_text $indent text
  // 599:   if indent <= base_indent: return text obj
  // 600:   !text remaining_text
  // 601:   push &obj deserialize_item(&text indent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__94_32;
}
static void entry__94_15(void) {
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
  // 597: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__94_16;
}
static void cont__94_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 597: ... length_of(text) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__94_17;
}
static void cont__94_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 597: ... text(1) != '@nl;'
  frame->slots[9] /* temp__4 */ = create_closure(entry__94_18, 0);
  // 597: ... length_of(text) == 0 || text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__94_22;
}
static void entry__94_18(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 597: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__94_19;
}
static void cont__94_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 597: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__94_20;
}
static void cont__94_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 597: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__94_21;
}
static void cont__94_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 597: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__94_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 597: ... : return text obj
  frame->slots[10] /* temp__5 */ = create_closure(entry__94_23, 0);
  // 597: if length_of(text) == 0 || text(1) != '@nl;': return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__94_24;
}
static void entry__94_23(void) {
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
  // 597: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__94_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 598: get_deserialization_indent $remaining_text $indent text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 2;
  myself = get__get_deserialization_indent();
  func = myself->type;
  frame->cont = cont__94_25;
}
static void cont__94_25(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 598: ... remaining_text
  initialize_future(frame->slots[4] /* remaining_text */, frame->slots[6] /* temp__1 */);
  // 598: ... indent
  initialize_future(frame->slots[5] /* indent */, frame->slots[7] /* temp__2 */);
  // 599: ... indent <= base_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base_indent */;
  arguments->slots[1] = frame->slots[5] /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__94_26;
}
static void cont__94_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 599: ... indent <= base_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__94_27;
}
static void cont__94_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 599: ... : return text obj
  frame->slots[8] /* temp__3 */ = create_closure(entry__94_28, 0);
  // 599: if indent <= base_indent: return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__94_29;
}
static void entry__94_28(void) {
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
  // 599: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__94_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 600: !text remaining_text
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[4] /* remaining_text */;
  // 601: ... deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[5] /* indent */;
  result_count = 2;
  myself = get__deserialize_item();
  func = myself->type;
  frame->cont = cont__94_30;
}
static void cont__94_30(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[6] /* temp__1 */ = arguments->slots[1];
  // 601: push &obj deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* obj */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__94_31;
}
static void cont__94_31(void) {
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
static void cont__94_32(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__94_33(void) {
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
  } else if (data && !IS_OLD(data)) {
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
static void entry__14_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 164: ... -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_1(void) {
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
static void entry__16_1(void) {
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
static void entry__17_1(void) {
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
static void entry__18_1(void) {
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
static void entry__19_1(void) {
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
static void entry__20_1(void) {
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
static void entry__21_1(void) {
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
static void entry__22_1(void) {
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
static void entry__23_1(void) {
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
  // 300: ... count != 0
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
  // 300: ... count != 0
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
  // 300: ... : !self append(range(self 1 idx-1) range(self idx+count -1))
  frame->slots[5] /* temp__3 */ = create_closure(entry__23_4, 0);
  // 300: if count != 0: !self append(range(self 1 idx-1) range(self idx+count -1))
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
  // 300: ... idx-1
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
  // 300: ... range(self 1 idx-1)
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
  // 300: ... idx+count
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
  // 300: ... 1
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
  // 300: ... range(self idx+count -1)
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
  // 300: ... !self append(range(self 1 idx-1) range(self idx+count -1))
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
static void entry__24_1(void) {
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
  // 309: idx >= 0
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
  // 309: idx >= 0
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
  // 309: ... :
  // 310:   return idx
  frame->slots[5] /* temp__3 */ = create_closure(entry__24_4, 0);
  // 311: :
  // 312:   return length_of(self)+1+idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__24_5, 0);
  // 308: if
  // 309:   idx >= 0:
  // 310:     return idx
  // 311:   :
  // 312:     return length_of(self)+1+idx
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
  // 310: return idx
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
  // 312: ... length_of(self)
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
  // 312: ... length_of(self)+1
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
  // 312: ... length_of(self)+1+idx
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
  // 312: return length_of(self)+1+idx
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
static void entry__25_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 314: ... length_of(self)
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
  // 314: ... length_of(self) == 0
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
  // 314: ... -> length_of(self) == 0
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
  // 340: parameter_count_of(body)
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
  // 340: parameter_count_of(body) == 2
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
  // 340: ... :
  // 341:   body i self(i)
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_10, 0);
  // 342: :
  // 343:   body self(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__26_12, 0);
  // 339: if
  // 340:   parameter_count_of(body) == 2:
  // 341:     body i self(i)
  // 342:   :
  // 343:     body self(i)
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
  // 341: ... self(i)
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
  // 341: body i self(i)
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
  // 343: ... self(i)
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
  // 343: body self(i)
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
  // 344: ... body2.is_defined
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
  // 344: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_16, 0);
  // 344: ... body2.is_defined && i < n
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
  // 344: ... i < n
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
  // 344: ... i < n
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
  // 344: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__26_19, 0);
  // 344: if body2.is_defined && i < n: body2
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
  // 344: ... body2
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
  // 345: plus &i 1
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
  // 338: ... i <= n
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
  // 338: ... i <= n
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
  // 338: ... :
  // 339:   if
  // 340:     parameter_count_of(body) == 2:
  // 341:       body i self(i)
  // 342:     :
  // 343:       body self(i)
  // 344:   if body2.is_defined && i < n: body2
  // 345:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__26_7, 0);
  // 338: ... -> i <= n:
  // 339:   if
  // 340:     parameter_count_of(body) == 2:
  // 341:       body i self(i)
  // 342:     :
  // 343:       body self(i)
  // 344:   if body2.is_defined && i < n: body2
  // 345:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_1(void) {
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
  // 336: $$i normalized_index(self first)
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
  // 337: $n normalized_index(self last)
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
  // 338: ... -> i <= n:
  // 339:   if
  // 340:     parameter_count_of(body) == 2:
  // 341:       body i self(i)
  // 342:     :
  // 343:       body self(i)
  // 344:   if body2.is_defined && i < n: body2
  // 345:   plus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__26_4, 0);
  // 338: while -> i <= n:
  // 339:   if
  // 340:     parameter_count_of(body) == 2:
  // 341:       body i self(i)
  // 342:     :
  // 343:       body self(i)
  // 344:   if body2.is_defined && i < n: body2
  // 345:   plus &i 1
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
  // 352: parameter_count_of(body)
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
  // 352: parameter_count_of(body) == 2
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
  // 352: ... :
  // 353:   body i self(i)
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_10, 0);
  // 354: :
  // 355:   body self(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__27_12, 0);
  // 351: if
  // 352:   parameter_count_of(body) == 2:
  // 353:     body i self(i)
  // 354:   :
  // 355:     body self(i)
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
  // 353: ... self(i)
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
  // 353: body i self(i)
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
  // 355: ... self(i)
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
  // 355: body self(i)
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
  // 356: ... body2.is_defined
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
  // 356: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_16, 0);
  // 356: ... body2.is_defined && i < n
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
  // 356: ... i < n
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
  // 356: ... i < n
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
  // 356: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__27_19, 0);
  // 356: if body2.is_defined && i < n: body2
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
  // 356: ... body2
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
  // 357: minus &i 1
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
  // 350: ... i >= n
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
  // 350: ... i >= n
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
  // 350: ... :
  // 351:   if
  // 352:     parameter_count_of(body) == 2:
  // 353:       body i self(i)
  // 354:     :
  // 355:       body self(i)
  // 356:   if body2.is_defined && i < n: body2
  // 357:   minus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__27_7, 0);
  // 350: ... -> i >= n:
  // 351:   if
  // 352:     parameter_count_of(body) == 2:
  // 353:       body i self(i)
  // 354:     :
  // 355:       body self(i)
  // 356:   if body2.is_defined && i < n: body2
  // 357:   minus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1(void) {
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
  // 348: $$i normalized_index(self first)
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
  // 349: $n normalized_index(self last)
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
  // 350: ... -> i >= n:
  // 351:   if
  // 352:     parameter_count_of(body) == 2:
  // 353:       body i self(i)
  // 354:     :
  // 355:       body self(i)
  // 356:   if body2.is_defined && i < n: body2
  // 357:   minus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__27_4, 0);
  // 350: while -> i >= n:
  // 351:   if
  // 352:     parameter_count_of(body) == 2:
  // 353:       body i self(i)
  // 354:     :
  // 355:       body self(i)
  // 356:   if body2.is_defined && i < n: body2
  // 357:   minus &i 1
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
  // 370: ... self(i)
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
  // 370: body self(i)
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
  // 371: ... body2.is_defined
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
  // 371: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_27, 0);
  // 371: ... body2.is_defined && i < n
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
  // 371: ... i < n
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
  // 371: ... i < n
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
  // 371: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_30, 0);
  // 371: if body2.is_defined && i < n: body2
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
  // 371: ... body2
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
  // 372: plus &i 1
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
  // 369: ... i <= n
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
  // 369: ... i <= n
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
  // 369: ... :
  // 370:   body self(i)
  // 371:   if body2.is_defined && i < n: body2
  // 372:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_23, 0);
  // 369: ... -> i <= n:
  // 370:   body self(i)
  // 371:   if body2.is_defined && i < n: body2
  // 372:   plus &i 1
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
  // 365: ... self(i)
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
  // 365: body i self(i)
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
  // 366: ... body2.is_defined
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
  // 366: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_13, 0);
  // 366: ... body2.is_defined && i < n
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
  // 366: ... i < n
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
  // 366: ... i < n
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
  // 366: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_16, 0);
  // 366: if body2.is_defined && i < n: body2
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
  // 366: ... body2
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
  // 367: plus &i 1
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
  // 364: ... i <= n
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
  // 364: ... i <= n
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
  // 364: ... :
  // 365:   body i self(i)
  // 366:   if body2.is_defined && i < n: body2
  // 367:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_9, 0);
  // 364: ... -> i <= n:
  // 365:   body i self(i)
  // 366:   if body2.is_defined && i < n: body2
  // 367:   plus &i 1
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
  // 364: ... -> i <= n:
  // 365:   body i self(i)
  // 366:   if body2.is_defined && i < n: body2
  // 367:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__28_6, 0);
  // 364: while -> i <= n:
  // 365:   body i self(i)
  // 366:   if body2.is_defined && i < n: body2
  // 367:   plus &i 1
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
  // 369: ... -> i <= n:
  // 370:   body self(i)
  // 371:   if body2.is_defined && i < n: body2
  // 372:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__28_20, 0);
  // 369: while -> i <= n:
  // 370:   body self(i)
  // 371:   if body2.is_defined && i < n: body2
  // 372:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_1(void) {
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
  // 360: $$i 1
  ((CELL *)frame->slots[3])->contents /* i */ = number__1;
  // 361: $n length_of(self)
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
  // 363: parameter_count_of(body)
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
  // 363: parameter_count_of(body) == 2
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
  // 363: ... :
  // 364:   while -> i <= n:
  // 365:     body i self(i)
  // 366:     if body2.is_defined && i < n: body2
  // 367:     plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__28_5, 0);
  // 368: :
  // 369:   while -> i <= n:
  // 370:     body self(i)
  // 371:     if body2.is_defined && i < n: body2
  // 372:     plus &i 1
  frame->slots[8] /* temp__4 */ = create_closure(entry__28_19, 0);
  // 362: if
  // 363:   parameter_count_of(body) == 2:
  // 364:     while -> i <= n:
  // 365:       body i self(i)
  // 366:       if body2.is_defined && i < n: body2
  // 367:       plus &i 1
  // 368:   :
  // 369:     while -> i <= n:
  // 370:       body self(i)
  // 371:       if body2.is_defined && i < n: body2
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
static void entry__29_1(void) {
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
  // 380: $$i 1
  ((CELL *)frame->slots[3])->contents /* i */ = number__1;
  // 381: $n length_of(self)
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
  // 382: $$new_list types::list
  ((CELL *)frame->slots[5])->contents /* new_list */ = var.types__list;
  // 384: parameter_count_of(body)
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
  // 384: parameter_count_of(body) == 2
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
  // 384: ... :
  // 385:   while -> i <= n:
  // 386:     push &new_list body(i self(i))
  // 387:     plus &i 1
  frame->slots[8] /* temp__3 */ = create_closure(entry__29_5, 0);
  // 388: :
  // 389:   while -> i <= n:
  // 390:     push &new_list body(self(i))
  // 391:     plus &i 1
  frame->slots[9] /* temp__4 */ = create_closure(entry__29_14, 0);
  // 383: if
  // 384:   parameter_count_of(body) == 2:
  // 385:     while -> i <= n:
  // 386:       push &new_list body(i self(i))
  // 387:       plus &i 1
  // 388:   :
  // 389:     while -> i <= n:
  // 390:       push &new_list body(self(i))
  // 391:       plus &i 1
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
  // 390: ... self(i)
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
  // 390: ... body(self(i))
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
  // 390: push &new_list body(self(i))
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
  // 391: plus &i 1
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
  // 389: ... i <= n
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
  // 389: ... i <= n
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
  // 389: ... :
  // 390:   push &new_list body(self(i))
  // 391:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__29_18, 0);
  // 389: ... -> i <= n:
  // 390:   push &new_list body(self(i))
  // 391:   plus &i 1
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
  // 386: ... self(i)
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
  // 386: ... body(i self(i))
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
  // 386: push &new_list body(i self(i))
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
  // 387: plus &i 1
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
  // 385: ... i <= n
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
  // 385: ... i <= n
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
  // 385: ... :
  // 386:   push &new_list body(i self(i))
  // 387:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__29_9, 0);
  // 385: ... -> i <= n:
  // 386:   push &new_list body(i self(i))
  // 387:   plus &i 1
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
  // 385: ... -> i <= n:
  // 386:   push &new_list body(i self(i))
  // 387:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__29_6, 0);
  // 385: while -> i <= n:
  // 386:   push &new_list body(i self(i))
  // 387:   plus &i 1
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
  // 389: ... -> i <= n:
  // 390:   push &new_list body(self(i))
  // 391:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__29_15, 0);
  // 389: while -> i <= n:
  // 390:   push &new_list body(self(i))
  // 391:   plus &i 1
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
  // 392: return new_list
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
  // 400: ... self(i)
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
  // 400: ... body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_1(void) {
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
  // 395: $$i 1
  ((CELL *)frame->slots[2])->contents /* i */ = number__1;
  // 396: $n length_of(self)
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
  // 397: ... -> i < n:
  // 398:   body self(i) self(i+1)
  // 399:   plus &i 2
  frame->slots[4] /* temp__1 */ = create_closure(entry__30_3, 0);
  // 397: while -> i < n:
  // 398:   body self(i) self(i+1)
  // 399:   plus &i 2
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
  // 398: ... self(i)
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
  // 398: ... i+1
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
  // 398: ... self(i+1)
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
  // 398: body self(i) self(i+1)
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
  // 399: plus &i 2
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
  // 397: ... i < n
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
  // 397: ... :
  // 398:   body self(i) self(i+1)
  // 399:   plus &i 2
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_5, 0);
  // 397: ... -> i < n:
  // 398:   body self(i) self(i+1)
  // 399:   plus &i 2
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
  // 400: ... is_odd(n)
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
  // 400: ... : body self(i)
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_13, 0);
  // 400: if is_odd(n): body self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__31_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 403: ... length_of(self)
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
  // 403: ... length_of(self) == 0
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
  // 403: if length_of(self) == 0: raise "Attempt to get an element from an empty list!"
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
  // 403: ... raise "Attempt to get an element from an empty list!"
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
  // 404: ... 1
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
  // 404: ... range(self 2 -1)
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
  // 404: ... self(1)
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
  // 404: -> range(self 2 -1) self(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__32_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // item: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 406: ... list(item)
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
  // 406: ... append(list(item) self)
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
  // 406: ... -> append(list(item) self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_1(void) {
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
  // 415: $$result list()
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
  // 416: ... :
  // 417:   if
  // 418:     length_of(left) > 0:
  // 419:       if
  // 420:         length_of(right) > 0:
  // 421:           if
  // 422:             ||
  // 423:               func.is_undefined && left(1) <= right(1)
  // 424:               func.is_defined && not(func(right(1) left(1)))
  // 425:             :
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__33_3, 0);
  // 416: forever:
  // 417:   if
  // 418:     length_of(left) > 0:
  // 419:       if
  // 420:         length_of(right) > 0:
  // 421:           if
  // 422:             ||
  // 423:               func.is_undefined && left(1) <= right(1)
  // 424:               func.is_defined && not(func(right(1) left(1)))
  // 425:             :
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
  // 426: ... get(&left)
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
  // 426: push &result get(&left)
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
  // 428: ... get(&right)
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
  // 428: push &result get(&right)
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
  // 423: func.is_undefined
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
  // 423: ... left(1) <= right(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__33_11, 0);
  // 423: func.is_undefined && left(1) <= right(1)
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
  // 423: ... right(1)
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
  // 423: ... left(1)
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
  // 423: ... left(1) <= right(1)
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
  // 423: ... left(1) <= right(1)
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
  // 423: ... left(1) <= right(1)
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
  // 424: func.is_defined && not(func(right(1) left(1)))
  frame->slots[8] /* temp__5 */ = create_closure(entry__33_17, 0);
  // 422: ||
  // 423:   func.is_undefined && left(1) <= right(1)
  // 424:   func.is_defined && not(func(right(1) left(1)))
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
  // 424: func.is_defined
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
  // 424: ... not(func(right(1) left(1)))
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_19, 0);
  // 424: func.is_defined && not(func(right(1) left(1)))
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
  // 424: ... right(1)
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
  // 424: ... left(1)
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
  // 424: ... func(right(1) left(1))
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
  // 424: ... not(func(right(1) left(1)))
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
  // 424: ... not(func(right(1) left(1)))
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
  // 424: func.is_defined && not(func(right(1) left(1)))
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
  // 425: :
  // 426:   push &result get(&left)
  frame->slots[9] /* temp__6 */ = create_closure(entry__33_26, 0);
  // 427: :
  // 428:   push &result get(&right)
  frame->slots[10] /* temp__7 */ = create_closure(entry__33_29, 0);
  // 421: if
  // 422:   ||
  // 423:     func.is_undefined && left(1) <= right(1)
  // 424:     func.is_defined && not(func(right(1) left(1)))
  // 425:   :
  // 426:     push &result get(&left)
  // 427:   :
  // 428:     push &result get(&right)
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
  // 430: ... append(result left)
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
  // 430: return append(result left)
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
  // 420: length_of(right)
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
  // 420: length_of(right) > 0
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
  // 420: ... :
  // 421:   if
  // 422:     ||
  // 423:       func.is_undefined && left(1) <= right(1)
  // 424:       func.is_defined && not(func(right(1) left(1)))
  // 425:     :
  // 426:       push &result get(&left)
  // 427:     :
  // 428:       push &result get(&right)
  frame->slots[7] /* temp__3 */ = create_closure(entry__33_9, 0);
  // 429: :
  // 430:   return append(result left)
  frame->slots[8] /* temp__4 */ = create_closure(entry__33_32, 0);
  // 419: if
  // 420:   length_of(right) > 0:
  // 421:     if
  // 422:       ||
  // 423:         func.is_undefined && left(1) <= right(1)
  // 424:         func.is_defined && not(func(right(1) left(1)))
  // 425:       :
  // 426:         push &result get(&left)
  // 427:       :
  // 428:         push &result get(&right)
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
  // 432: ... append(result right)
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
  // 432: return append(result right)
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
  // 418: length_of(left)
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
  // 418: length_of(left) > 0
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
  // 418: ... :
  // 419:   if
  // 420:     length_of(right) > 0:
  // 421:       if
  // 422:         ||
  // 423:           func.is_undefined && left(1) <= right(1)
  // 424:           func.is_defined && not(func(right(1) left(1)))
  // 425:         :
  // 426:           push &result get(&left)
  // 427:         :
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__33_6, 0);
  // 431: :
  // 432:   return append(result right)
  frame->slots[8] /* temp__4 */ = create_closure(entry__33_34, 0);
  // 417: if
  // 418:   length_of(left) > 0:
  // 419:     if
  // 420:       length_of(right) > 0:
  // 421:         if
  // 422:           ||
  // 423:             func.is_undefined && left(1) <= right(1)
  // 424:             func.is_defined && not(func(right(1) left(1)))
  // 425:           :
  // 426:             push &result get(&left)
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
static void entry__34_1(void) {
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
  // 440: ... self.is_empty
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
  // 440: ... : return "list()"
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_3, 0);
  // 440: if self.is_empty: return "list()"
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
  // 440: ... return "list()"
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
  // 441: $$buf "list"
  ((CELL *)frame->slots[3])->contents /* buf */ = string__34_6;
  // 442: ... : (item)
  // 443:   write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
  frame->slots[4] /* temp__1 */ = create_closure(entry__34_7, 1);
  // 442: for_each self: (item)
  // 443:   write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
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
  // 443: ... indent+2
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
  // 443: ... spaces(indent+2)
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
  // 443: ... indent+2
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
  // 443: ... serialize(item indent+2)
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
  // 443: write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
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
  // 444: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__35_1(void) {
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
  // 452: $n length_of(self)
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
  // 455: 0, 1
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
  // 455: ... :
  // 456:   return self
  frame->slots[5] /* temp__2 */ = create_closure(entry__35_4, 0);
  // 457: ... :
  // 458:   if
  // 459:     ||
  // 460:       func.is_undefined && self(1) <= self(2)
  // 461:       func.is_defined && not(func(self(2) self(1)))
  // 462:     :
  // 463:       return self
  // 464:     :
  // 465:       return list(self(2) self(1))
  frame->slots[6] /* temp__3 */ = create_closure(entry__35_5, 0);
  // 466: :
  // 467:   $m n .div. 2
  // 468:   if
  // 469:     func.is_undefined:
  // 470:       return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  // 471:     :
  // 472:       return
  // 473:         merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  frame->slots[7] /* temp__4 */ = create_closure(entry__35_27, 0);
  // 453: case
  // 454:   n
  // 455:   0, 1:
  // 456:     return self
  // 457:   2:
  // 458:     if
  // 459:       ||
  // 460:         func.is_undefined && self(1) <= self(2)
  // 461:         func.is_defined && not(func(self(2) self(1)))
  // 462:       :
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
  // 470: ... range(self 1 m)
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
  // 470: ... sort(range(self 1 m))
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
  // 470: ... m+1
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
  // 470: ... range(self m+1 n)
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
  // 470: ... sort(range(self m+1 n))
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
  // 470: ... merge(sort(range(self 1 m)) sort(range(self m+1 n)))
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
  // 470: return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
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
  // 473: ... range(self 1 m)
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
  // 473: ... sort(range(self 1 m) func)
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
  // 473: ... m+1
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
  // 473: ... range(self m+1 n)
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
  // 473: ... sort(range(self m+1 n) func)
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
  // 473: merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
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
  // 472: return
  // 473:   merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
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
  // 463: return self
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
  // 465: ... self(2)
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
  // 465: ... self(1)
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
  // 465: ... list(self(2) self(1))
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
  // 465: return list(self(2) self(1))
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
  // 456: return self
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
  // 460: func.is_undefined
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
  // 460: ... self(1) <= self(2)
  frame->slots[6] /* temp__4 */ = create_closure(entry__35_7, 0);
  // 460: func.is_undefined && self(1) <= self(2)
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
  // 460: ... self(2)
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
  // 460: ... self(1)
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
  // 460: ... self(1) <= self(2)
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
  // 460: ... self(1) <= self(2)
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
  // 460: ... self(1) <= self(2)
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
  // 461: func.is_defined && not(func(self(2) self(1)))
  frame->slots[7] /* temp__5 */ = create_closure(entry__35_13, 0);
  // 459: ||
  // 460:   func.is_undefined && self(1) <= self(2)
  // 461:   func.is_defined && not(func(self(2) self(1)))
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
  // 461: func.is_defined
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
  // 461: ... not(func(self(2) self(1)))
  frame->slots[4] /* temp__3 */ = create_closure(entry__35_15, 0);
  // 461: func.is_defined && not(func(self(2) self(1)))
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
  // 461: ... self(2)
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
  // 461: ... self(1)
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
  // 461: ... func(self(2) self(1))
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
  // 461: ... not(func(self(2) self(1)))
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
  // 461: ... not(func(self(2) self(1)))
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
  // 461: func.is_defined && not(func(self(2) self(1)))
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
  // 462: :
  // 463:   return self
  frame->slots[8] /* temp__6 */ = create_closure(entry__35_22, 0);
  // 464: :
  // 465:   return list(self(2) self(1))
  frame->slots[9] /* temp__7 */ = create_closure(entry__35_23, 0);
  // 458: if
  // 459:   ||
  // 460:     func.is_undefined && self(1) <= self(2)
  // 461:     func.is_defined && not(func(self(2) self(1)))
  // 462:   :
  // 463:     return self
  // 464:   :
  // 465:     return list(self(2) self(1))
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
  // 467: $m n .div. 2
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
  // 469: func.is_undefined
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
  // 469: ... :
  // 470:   return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  frame->slots[6] /* temp__2 */ = create_closure(entry__35_30, 0);
  // 471: :
  // 472:   return
  // 473:     merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  frame->slots[7] /* temp__3 */ = create_closure(entry__35_37, 0);
  // 468: if
  // 469:   func.is_undefined:
  // 470:     return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  // 471:   :
  // 472:     return
  // 473:       merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
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
    if (max_depth == 0) {
      if (node->list.length == 1) {
        return debug_print(indent, buf, "<list of 1 item>", node);
      } else {
        return debug_print(indent, buf, "<list of %ld items>", node->list.length);
      }
    } else {
      int i, n, len;
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
static void entry__37_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 504: ... -> types::list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__list;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_1(void) {
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
  // 516: ... right.is_defined
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
  // 516: ... right.is_a_list
  frame->slots[5] /* temp__3 */ = create_closure(entry__38_3, 0);
  // 516: ... right.is_defined && right.is_a_list
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
  // 516: ... right.is_a_list
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
  // 516: ... right.is_a_list
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
  // 516: ... : return false
  frame->slots[6] /* temp__4 */ = create_closure(entry__38_6, 0);
  // 516: unless right.is_defined && right.is_a_list: return false
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
  // 516: ... return false
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
  // 517: ... length_of(left)
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
  // 517: ... length_of(right)
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
  // 517: ... length_of(left) != length_of(right)
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
  // 517: ... length_of(left) != length_of(right)
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
  // 517: ... : return false
  frame->slots[7] /* temp__5 */ = create_closure(entry__38_12, 0);
  // 517: if length_of(left) != length_of(right): return false
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
  // 517: ... return false
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
  // 518: ... : (idx item) if item != right(idx): return false
  frame->slots[3] /* temp__1 */ = create_closure(entry__38_14, 2);
  // 518: for_each left: (idx item) if item != right(idx): return false
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
  // 518: ... return false
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
  // 518: ... right(idx)
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
  // 518: ... item != right(idx)
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
  // 518: ... item != right(idx)
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
  // 518: ... : return false
  frame->slots[7] /* temp__4 */ = create_closure(entry__38_18, 0);
  // 518: ... if item != right(idx): return false
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
  // 519: -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__39_1(void) {
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
  // 522: $$new_list new_empty_collection(self)
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
  // 523: ... : (item) if test(item): push &new_list item
  frame->slots[3] /* temp__1 */ = create_closure(entry__39_3, 1);
  // 523: for_each self: (item) if test(item): push &new_list item
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
  // 523: ... push &new_list item
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
  // 523: ... test(item)
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
  // 523: ... : push &new_list item
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_5, 0);
  // 523: ... if test(item): push &new_list item
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
  // 524: -> new_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_list */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__40_1(void) {
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
  // 527: $$new_list new_empty_collection(self)
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
  // 528: ... : (item) push &new_list func(item)
  frame->slots[3] /* temp__1 */ = create_closure(entry__40_3, 1);
  // 528: for_each self: (item) push &new_list func(item)
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
  // 528: ... func(item)
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
  // 528: ... push &new_list func(item)
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
  // 529: -> new_list
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
  // 537: ... -> self
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
  // 538: ... n < 0
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
  // 538: if n < 0: raise "Negative argument for dup!"
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
  // 538: ... raise "Negative argument for dup!"
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
  // 539: ... n .div. 2
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
  // 539: $$result dup(self n .div. 2)
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
  // 540: append &result result
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
  // 541: ... n.is_odd
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
  // 541: ... : append &result self
  frame->slots[4] /* temp__2 */ = create_closure(entry__41_12, 0);
  // 541: if n.is_odd: append &result self
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
  // 541: ... append &result self
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
  // 542: -> result
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
  // 537: ... -> empty_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // n: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 537: ... -> self
  frame->slots[2] /* temp__1 */ = create_closure(entry__41_2, 0);
  // 537: ... :
  // 538:   if n < 0: raise "Negative argument for dup!"
  // 539:   $$result dup(self n .div. 2)
  // 540:   append &result result
  // 541:   if n.is_odd: append &result self
  // 542:   -> result
  frame->slots[3] /* temp__2 */ = create_closure(entry__41_3, 0);
  // 537: case n 0 (-> empty_list) 1 (-> self):
  // 538:   if n < 0: raise "Negative argument for dup!"
  // 539:   $$result dup(self n .div. 2)
  // 540:   append &result result
  // 541:   if n.is_odd: append &result self
  // 542:   -> result
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
static void entry__42_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // lists: 0
  // n: 1
  // result: 2
  frame->slots[1] /* n */ = create_future();
  frame->slots[2] /* result */ = create_cell();
  frame->slots[0] /* lists */ = from_arguments(0, argument_count-0);
  // 552: ... lists(1)
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
  // 552: $n length_of(lists(1))
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
  // 553: $$result empty_list
  ((CELL *)frame->slots[2])->contents /* result */ = get__empty_list();
  // 554: ... n-1
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
  // 554: ... : (i) for_each lists: (current_list) push &result current_list(i)
  frame->slots[4] /* temp__2 */ = create_closure(entry__42_5, 1);
  // 554: from_to 1 n-1: (i) for_each lists: (current_list) push &result current_list(i)
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
  // 554: ... current_list(i)
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
  // 554: ... push &result current_list(i)
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
  // 554: ... : (current_list) push &result current_list(i)
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_6, 1);
  // 554: ... for_each lists: (current_list) push &result current_list(i)
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
  // 555: ... : (current_list)
  // 556:   if length_of(current_list) >= n: push &result current_list(n)
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_10, 1);
  // 555: for_each lists: (current_list)
  // 556:   if length_of(current_list) >= n: push &result current_list(n)
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
  // 556: ... current_list(n)
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
  // 556: ... push &result current_list(n)
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
  // 556: ... length_of(current_list)
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
  // 556: ... length_of(current_list) >= n
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
  // 556: ... length_of(current_list) >= n
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
  // 556: ... : push &result current_list(n)
  frame->slots[6] /* temp__4 */ = create_closure(entry__42_14, 0);
  // 556: if length_of(current_list) >= n: push &result current_list(n)
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
  // 557: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_1(void) {
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
  // 565: ... : (current_item) if current_item == item: return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__43_2, 1);
  // 565: for_each self: (current_item) if current_item == item: return true
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
  // 565: ... return true
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
  // 565: ... current_item == item
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
  // 565: ... : return true
  frame->slots[4] /* temp__2 */ = create_closure(entry__43_4, 0);
  // 565: ... if current_item == item: return true
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
  // 566: -> false
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
  // 582: ... : (item)
  // 583:   if item == element || item .contains. element: return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__46_4, 1);
  // 582: for_each self: (item)
  // 583:   if item == element || item .contains. element: return true
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
  // 583: ... return true
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
  // 583: ... item == element
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
  // 583: ... item .contains. element
  frame->slots[5] /* temp__3 */ = create_closure(entry__46_6, 0);
  // 583: ... item == element || item .contains. element
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
  // 583: ... item .contains. element
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
  // 583: ... item .contains. element
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
  // 583: ... : return true
  frame->slots[6] /* temp__4 */ = create_closure(entry__46_9, 0);
  // 583: if item == element || item .contains. element: return true
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
  // 584: -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__46_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // items: 0
  frame->slots[0] /* items */ = from_arguments(0, argument_count-0);
  // 574: list(items*)
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
  // 574: list(items*)
  // 575:   .is_a_sequence true
  // 576:   /contains:
  // 577:     (
  // 578:       self
  // 579:       element
  // 580:       -> return
  // 581:     )
  // 582:     for_each self: (item)
  // 583:       if item == element || item .contains. element: return true
  // ...
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_sequence, get__true());
    set_attribute(temp->attributes, poly_idx__contains, func__46_3);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 573: ->
  // 574:   list(items*)
  // 575:     .is_a_sequence true
  // 576:     /contains:
  // 577:       (
  // 578:         self
  // 579:         element
  // 580:         -> return
  // 581:       )
  // 582:       for_each self: (item)
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
  func__14_1 = collect_node(func__14_1);
  var.std__list = collect_node(var.std__list);
  func__23_1 = collect_node(func__23_1);
  var.std__normalized_index = collect_node(var.std__normalized_index);
  func__24_1 = collect_node(func__24_1);
  func__25_1 = collect_node(func__25_1);
  func__26_1 = collect_node(func__26_1);
  func__27_1 = collect_node(func__27_1);
  func__28_1 = collect_node(func__28_1);
  func__29_1 = collect_node(func__29_1);
  func__30_1 = collect_node(func__30_1);
  string__31_5 = collect_node(string__31_5);
  func__31_4 = collect_node(func__31_4);
  func__31_1 = collect_node(func__31_1);
  func__32_1 = collect_node(func__32_1);
  func__33_1 = collect_node(func__33_1);
  string__34_4 = collect_node(string__34_4);
  string__34_6 = collect_node(string__34_6);
  func__34_1 = collect_node(func__34_1);
  func__35_1 = collect_node(func__35_1);
  func__37_1 = collect_node(func__37_1);
  func__38_1 = collect_node(func__38_1);
  func__39_1 = collect_node(func__39_1);
  func__40_1 = collect_node(func__40_1);
  string__41_6 = collect_node(string__41_6);
  func__41_5 = collect_node(func__41_5);
  func__41_15 = collect_node(func__41_15);
  func__41_1 = collect_node(func__41_1);
  func__42_1 = collect_node(func__42_1);
  func__43_1 = collect_node(func__43_1);
  var.std__is_a_sequence = collect_node(var.std__is_a_sequence);
  var.std__sequence = collect_node(var.std__sequence);
  func__46_3 = collect_node(func__46_3);
  func__46_1 = collect_node(func__46_1);
  string__94_1 = collect_node(string__94_1);
  string__94_3 = collect_node(string__94_3);
  string__94_13 = collect_node(string__94_13);
  func__94_12 = collect_node(func__94_12);
  func__94_2 = collect_node(func__94_2);
  character__10 = collect_node(character__10);
  number__0 = collect_node(number__0);
  number__3 = collect_node(number__3);
  number__1 = collect_node(number__1);
  number__2 = collect_node(number__2);
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
  set_module("basic__types__list");
  set_used_namespaces(used_namespaces);
  character__10 = create_future();
  number__0 = create_future();
  number__3 = create_future();
  number__1 = create_future();
  number__2 = create_future();
  var.types__generic_list = create_future_with_prototype(create__types__generic_list());
  define_single_assign_static("types", "generic_list", get__types__generic_list, &var.types__generic_list);
  var.types__list = create_future_with_prototype(create__types__list(0, NULL));
  define_single_assign_static("types", "list", get__types__list, &var.types__list);
  var.std__empty_list = create__types__list(0, NULL);
  define_single_assign_static("std", "empty_list", get__std__empty_list, &var.std__empty_list);
  func__14_1 = create_future();
  func__15_1 = create_future();
  define_single_assign_static("std", "list", get__std__list, &var.std__list);
  func__16_1 = create_future();
  func__17_1 = create_future();
  func__18_1 = create_future();
  func__19_1 = create_future();
  func__20_1 = create_future();
  func__21_1 = create_future();
  func__22_1 = create_future();
  func__23_1 = create_future();
  func__24_1 = create_future();
  define_single_assign_static("std", "normalized_index", get__std__normalized_index, &var.std__normalized_index);
  func__25_1 = create_future();
  func__26_1 = create_future();
  func__27_1 = create_future();
  func__28_1 = create_future();
  func__29_1 = create_future();
  func__30_1 = create_future();
  string__31_5 = from_latin_1_string("Attempt to get an element from an empty list!", 45);
  func__31_4 = create_future();
  func__31_1 = create_future();
  func__32_1 = create_future();
  func__33_1 = create_future();
  string__34_4 = from_latin_1_string("list()", 6);
  string__34_6 = from_latin_1_string("list", 4);
  func__34_1 = create_future();
  func__35_1 = create_future();
  func__37_1 = create_future();
  func__38_1 = create_future();
  func__39_1 = create_future();
  func__40_1 = create_future();
  string__41_6 = from_latin_1_string("Negative argument for dup!", 26);
  func__41_5 = create_future();
  func__41_15 = create_future();
  func__41_1 = create_future();
  func__42_1 = create_future();
  func__43_1 = create_future();
  func__46_3 = create_future();
  func__46_1 = create_future();
  define_single_assign_static("std", "sequence", get__std__sequence, &var.std__sequence);
  string__94_1 = from_latin_1_string("list", 4);
  string__94_3 = from_latin_1_string("()", 2);
  string__94_13 = from_latin_1_string("Invalid list object encountered during deserialisation!", 55);
  func__94_12 = create_future();
  func__94_2 = create_future();
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__list(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
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
  define_method("types", "list", poly_idx__to_list, func__14_1);
  define_method("types", "list", poly_idx__length_of, func__16_1);
  define_method("types", "list", poly_idx__push, func__17_1);
  define_method("types", "list", poly_idx__drop, func__18_1);
  define_method("types", "list", poly_idx__pop, func__19_1);
  define_method("types", "list", poly_idx__peek, func__20_1);
  define_method("types", "list", poly_idx__append, func__21_1);
  define_method("types", "list", poly_idx__range, func__22_1);
  define_method("types", "generic_list", poly_idx__delete_at, func__23_1);
  define_method("types", "generic_list", poly_idx__is_empty, func__25_1);
  define_method("types", "generic_list", poly_idx__for_each_from_to, func__26_1);
  define_method("types", "generic_list", poly_idx__for_each_from_down_to, func__27_1);
  define_method("types", "generic_list", poly_idx__for_each, func__28_1);
  define_method("types", "generic_list", poly_idx__update_each, func__29_1);
  define_method("types", "list", poly_idx__for_each_pair, func__30_1);
  define_method("types", "generic_list", poly_idx__get, func__31_1);
  define_method("types", "list", poly_idx__put, func__32_1);
  define_method("types", "list", poly_idx__merge, func__33_1);
  define_method("types", "list", poly_idx__serialize, func__34_1);
  define_method("types", "list", poly_idx__sort, func__35_1);
  define_method("types", "list", poly_idx__new_empty_collection, func__37_1);
  define_method("types", "generic_list", poly_idx__equal, func__38_1);
  define_method("types", "generic_list", poly_idx__filter, func__39_1);
  define_method("types", "generic_list", poly_idx__map, func__40_1);
  define_method("types", "generic_list", poly_idx__dup, func__41_1);
  define_method("types", "generic_list", poly_idx__interleave, func__42_1);
  define_method("types", "generic_list", poly_idx__contains, func__43_1);
  define_attribute("types", "object", poly_idx__is_a_sequence, get__false());
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__list(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&character__10, from_uchar32(10));
  assign_value(&number__0, from_uint32(0U));
  assign_value(&number__3, from_uint32(3U));
  assign_value(&number__1, from_uint32(1U));
  assign_value(&number__2, from_uint32(2U));
  assign_value(&var.std__is_a_list, create_function(type__std__is_a_list, -1));
  assign_value(&var.types__generic_list, get__types__object());
  assign_variable(&var.types__list, &var.types__generic_list);
  assign_variable(&var.std__list, &func__15_1);
  assign_variable(&var.std__normalized_index, &func__24_1);
  assign_value(&var.std__is_a_sequence, create_function(type__std__is_a_sequence, -1));
  assign_variable(&var.std__sequence, &func__46_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__list(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__14_1, create_function(entry__14_1, 1));
  assign_value(&func__15_1, create_function(entry__15_1, -1));
  assign_value(&func__16_1, create_function(entry__16_1, 1));
  assign_value(&func__17_1, create_function(entry__17_1, 2));
  assign_value(&func__18_1, create_function(entry__18_1, 1));
  assign_value(&func__19_1, create_function(entry__19_1, 1));
  assign_value(&func__20_1, create_function(entry__20_1, 1));
  assign_value(&func__21_1, create_function(entry__21_1, 2));
  assign_value(&func__22_1, create_function(entry__22_1, 3));
  assign_value(&func__23_1, create_function(entry__23_1, -1));
  assign_value(&func__24_1, create_function(entry__24_1, 2));
  assign_value(&func__25_1, create_function(entry__25_1, 1));
  assign_value(&func__26_1, create_function(entry__26_1, -1));
  assign_value(&func__27_1, create_function(entry__27_1, -1));
  assign_value(&func__28_1, create_function(entry__28_1, -1));
  assign_value(&func__29_1, create_function(entry__29_1, 2));
  assign_value(&func__30_1, create_function(entry__30_1, 2));
  assign_value(&func__31_4, create_function(entry__31_4, 0));
  assign_value(&func__31_1, create_function(entry__31_1, 1));
  assign_value(&func__32_1, create_function(entry__32_1, 2));
  assign_value(&func__33_1, create_function(entry__33_1, -1));
  assign_value(&func__34_1, create_function(entry__34_1, -1));
  assign_value(&func__35_1, create_function(entry__35_1, -1));
  assign_value(&func__37_1, create_function(entry__37_1, 1));
  assign_value(&func__38_1, create_function(entry__38_1, 2));
  assign_value(&func__39_1, create_function(entry__39_1, 2));
  assign_value(&func__40_1, create_function(entry__40_1, 2));
  assign_value(&func__41_5, create_function(entry__41_5, 0));
  assign_value(&func__41_15, create_function(entry__41_15, 0));
  assign_value(&func__41_1, create_function(entry__41_1, 2));
  assign_value(&func__42_1, create_function(entry__42_1, -1));
  assign_value(&func__43_1, create_function(entry__43_1, 2));
  assign_value(&func__46_3, create_function(entry__46_3, 2));
  assign_value(&func__46_1, create_function(entry__46_1, -1));
  assign_value(&func__94_12, create_function(entry__94_12, 0));
  assign_value(&func__94_2, create_function(entry__94_2, 2));
  register_collector(collect__basic__types__list);
}
