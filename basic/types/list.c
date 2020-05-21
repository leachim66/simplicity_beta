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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
REGISTER FRAME *arguments ASM("r12");
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
IMPORT void define_c_function(const char *name, void *func);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
static int poly_idx__for_each_downwards;
static NODE_GETTER get__for_each_downwards;
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
static NODE *func__types__list__to_list_1;
static void entry__types__list__to_list_1(void);
static FRAME_INFO frame__types__list__to_list_1 = {1, {"self"}};
static void entry__std__list_1(void);
static NODE *func__std__list_1;
static NODE *get__std__list(void) {
  return var.std__list;
}
static void entry__types__list__length_of_1(void);
static NODE *func__types__list__length_of_1;
static void entry__types__list__push_1(void);
static NODE *func__types__list__push_1;
static void entry__types__list__drop_1(void);
static NODE *func__types__list__drop_1;
static void entry__types__list__pop_1(void);
static NODE *func__types__list__pop_1;
static void entry__types__list__peek_1(void);
static NODE *func__types__list__peek_1;
static void entry__types__list__append_1(void);
static NODE *func__types__list__append_1;
static void entry__types__list__range_1(void);
static NODE *func__types__list__range_1;
static NODE *func__types__generic_list__delete_at_1;
static void entry__types__generic_list__delete_at_1(void);
static FRAME_INFO frame__types__generic_list__delete_at_1 = {3, {"self", "idx", "count"}};
static void cont__types__generic_list__delete_at_2(void);
static void cont__types__generic_list__delete_at_3(void);
static NODE *func__types__generic_list__delete_at_4;
static void entry__types__generic_list__delete_at_4(void);
static FRAME_INFO frame__types__generic_list__delete_at_4 = {3, {"self", "idx", "count"}};
static void cont__types__generic_list__delete_at_5(void);
static void cont__types__generic_list__delete_at_6(void);
static void cont__types__generic_list__delete_at_7(void);
static void cont__types__generic_list__delete_at_8(void);
static void cont__types__generic_list__delete_at_9(void);
static void cont__types__generic_list__delete_at_10(void);
static void cont__types__generic_list__delete_at_11(void);
static NODE *func__std__normalized_index_1;
static void entry__std__normalized_index_1(void);
static FRAME_INFO frame__std__normalized_index_1 = {3, {"self", "idx", "return"}};
static void cont__std__normalized_index_2(void);
static void cont__std__normalized_index_3(void);
static NODE *func__std__normalized_index_4;
static void entry__std__normalized_index_4(void);
static FRAME_INFO frame__std__normalized_index_4 = {2, {"return", "idx"}};
static NODE *func__std__normalized_index_5;
static void entry__std__normalized_index_5(void);
static FRAME_INFO frame__std__normalized_index_5 = {3, {"return", "self", "idx"}};
static void cont__std__normalized_index_6(void);
static void cont__std__normalized_index_7(void);
static void cont__std__normalized_index_8(void);
static void cont__std__normalized_index_9(void);
static NODE *get__std__normalized_index(void) {
  return var.std__normalized_index;
}
static NODE *func__types__generic_list__is_empty_1;
static void entry__types__generic_list__is_empty_1(void);
static FRAME_INFO frame__types__generic_list__is_empty_1 = {1, {"self"}};
static void cont__types__generic_list__is_empty_2(void);
static void cont__types__generic_list__is_empty_3(void);
static NODE *func__types__generic_list__for_each_from_to_1;
static void entry__types__generic_list__for_each_from_to_1(void);
static FRAME_INFO frame__types__generic_list__for_each_from_to_1 = {7, {"self", "first", "last", "body", "body2", "i", "n"}};
static void cont__types__generic_list__for_each_from_to_2(void);
static void cont__types__generic_list__for_each_from_to_3(void);
static NODE *func__types__generic_list__for_each_from_to_4;
static void entry__types__generic_list__for_each_from_to_4(void);
static FRAME_INFO frame__types__generic_list__for_each_from_to_4 = {5, {"n", "i", "body", "self", "body2"}};
static void cont__types__generic_list__for_each_from_to_5(void);
static void cont__types__generic_list__for_each_from_to_6(void);
static NODE *func__types__generic_list__for_each_from_to_7;
static void entry__types__generic_list__for_each_from_to_7(void);
static FRAME_INFO frame__types__generic_list__for_each_from_to_7 = {5, {"body", "i", "self", "body2", "n"}};
static void cont__types__generic_list__for_each_from_to_8(void);
static void cont__types__generic_list__for_each_from_to_9(void);
static NODE *func__types__generic_list__for_each_from_to_10;
static void entry__types__generic_list__for_each_from_to_10(void);
static FRAME_INFO frame__types__generic_list__for_each_from_to_10 = {3, {"body", "i", "self"}};
static void cont__types__generic_list__for_each_from_to_11(void);
static NODE *func__types__generic_list__for_each_from_to_12;
static void entry__types__generic_list__for_each_from_to_12(void);
static FRAME_INFO frame__types__generic_list__for_each_from_to_12 = {3, {"body", "self", "i"}};
static void cont__types__generic_list__for_each_from_to_13(void);
static void cont__types__generic_list__for_each_from_to_14(void);
static void cont__types__generic_list__for_each_from_to_15(void);
static NODE *func__types__generic_list__for_each_from_to_16;
static void entry__types__generic_list__for_each_from_to_16(void);
static FRAME_INFO frame__types__generic_list__for_each_from_to_16 = {2, {"i", "n"}};
static void cont__types__generic_list__for_each_from_to_17(void);
static void cont__types__generic_list__for_each_from_to_18(void);
static NODE *func__types__generic_list__for_each_from_to_19;
static void entry__types__generic_list__for_each_from_to_19(void);
static FRAME_INFO frame__types__generic_list__for_each_from_to_19 = {1, {"body2"}};
static void cont__types__generic_list__for_each_from_to_20(void);
static void cont__types__generic_list__for_each_from_to_21(void);
static NODE *func__types__generic_list__for_each_from_down_to_1;
static void entry__types__generic_list__for_each_from_down_to_1(void);
static FRAME_INFO frame__types__generic_list__for_each_from_down_to_1 = {7, {"self", "first", "last", "body", "body2", "i", "n"}};
static void cont__types__generic_list__for_each_from_down_to_2(void);
static void cont__types__generic_list__for_each_from_down_to_3(void);
static NODE *func__types__generic_list__for_each_from_down_to_4;
static void entry__types__generic_list__for_each_from_down_to_4(void);
static FRAME_INFO frame__types__generic_list__for_each_from_down_to_4 = {5, {"i", "n", "body", "self", "body2"}};
static void cont__types__generic_list__for_each_from_down_to_5(void);
static void cont__types__generic_list__for_each_from_down_to_6(void);
static NODE *func__types__generic_list__for_each_from_down_to_7;
static void entry__types__generic_list__for_each_from_down_to_7(void);
static FRAME_INFO frame__types__generic_list__for_each_from_down_to_7 = {5, {"body", "i", "self", "body2", "n"}};
static void cont__types__generic_list__for_each_from_down_to_8(void);
static void cont__types__generic_list__for_each_from_down_to_9(void);
static NODE *func__types__generic_list__for_each_from_down_to_10;
static void entry__types__generic_list__for_each_from_down_to_10(void);
static FRAME_INFO frame__types__generic_list__for_each_from_down_to_10 = {3, {"body", "i", "self"}};
static void cont__types__generic_list__for_each_from_down_to_11(void);
static NODE *func__types__generic_list__for_each_from_down_to_12;
static void entry__types__generic_list__for_each_from_down_to_12(void);
static FRAME_INFO frame__types__generic_list__for_each_from_down_to_12 = {3, {"body", "self", "i"}};
static void cont__types__generic_list__for_each_from_down_to_13(void);
static void cont__types__generic_list__for_each_from_down_to_14(void);
static void cont__types__generic_list__for_each_from_down_to_15(void);
static NODE *func__types__generic_list__for_each_from_down_to_16;
static void entry__types__generic_list__for_each_from_down_to_16(void);
static FRAME_INFO frame__types__generic_list__for_each_from_down_to_16 = {2, {"i", "n"}};
static void cont__types__generic_list__for_each_from_down_to_17(void);
static void cont__types__generic_list__for_each_from_down_to_18(void);
static NODE *func__types__generic_list__for_each_from_down_to_19;
static void entry__types__generic_list__for_each_from_down_to_19(void);
static FRAME_INFO frame__types__generic_list__for_each_from_down_to_19 = {1, {"body2"}};
static void cont__types__generic_list__for_each_from_down_to_20(void);
static void cont__types__generic_list__for_each_from_down_to_21(void);
static NODE *func__types__generic_list__for_each_1;
static void entry__types__generic_list__for_each_1(void);
static FRAME_INFO frame__types__generic_list__for_each_1 = {5, {"self", "body", "body2", "i", "n"}};
static void cont__types__generic_list__for_each_2(void);
static void cont__types__generic_list__for_each_3(void);
static void cont__types__generic_list__for_each_4(void);
static NODE *func__types__generic_list__for_each_5;
static void entry__types__generic_list__for_each_5(void);
static FRAME_INFO frame__types__generic_list__for_each_5 = {5, {"n", "i", "body", "self", "body2"}};
static NODE *func__types__generic_list__for_each_6;
static void entry__types__generic_list__for_each_6(void);
static FRAME_INFO frame__types__generic_list__for_each_6 = {5, {"n", "i", "body", "self", "body2"}};
static void cont__types__generic_list__for_each_7(void);
static void cont__types__generic_list__for_each_8(void);
static NODE *func__types__generic_list__for_each_9;
static void entry__types__generic_list__for_each_9(void);
static FRAME_INFO frame__types__generic_list__for_each_9 = {5, {"body", "i", "self", "body2", "n"}};
static void cont__types__generic_list__for_each_10(void);
static void cont__types__generic_list__for_each_11(void);
static void cont__types__generic_list__for_each_12(void);
static NODE *func__types__generic_list__for_each_13;
static void entry__types__generic_list__for_each_13(void);
static FRAME_INFO frame__types__generic_list__for_each_13 = {2, {"i", "n"}};
static void cont__types__generic_list__for_each_14(void);
static void cont__types__generic_list__for_each_15(void);
static NODE *func__types__generic_list__for_each_16;
static void entry__types__generic_list__for_each_16(void);
static FRAME_INFO frame__types__generic_list__for_each_16 = {1, {"body2"}};
static void cont__types__generic_list__for_each_17(void);
static void cont__types__generic_list__for_each_18(void);
static NODE *func__types__generic_list__for_each_19;
static void entry__types__generic_list__for_each_19(void);
static FRAME_INFO frame__types__generic_list__for_each_19 = {5, {"n", "i", "body", "self", "body2"}};
static NODE *func__types__generic_list__for_each_20;
static void entry__types__generic_list__for_each_20(void);
static FRAME_INFO frame__types__generic_list__for_each_20 = {5, {"n", "i", "body", "self", "body2"}};
static void cont__types__generic_list__for_each_21(void);
static void cont__types__generic_list__for_each_22(void);
static NODE *func__types__generic_list__for_each_23;
static void entry__types__generic_list__for_each_23(void);
static FRAME_INFO frame__types__generic_list__for_each_23 = {5, {"body", "self", "i", "body2", "n"}};
static void cont__types__generic_list__for_each_24(void);
static void cont__types__generic_list__for_each_25(void);
static void cont__types__generic_list__for_each_26(void);
static NODE *func__types__generic_list__for_each_27;
static void entry__types__generic_list__for_each_27(void);
static FRAME_INFO frame__types__generic_list__for_each_27 = {2, {"i", "n"}};
static void cont__types__generic_list__for_each_28(void);
static void cont__types__generic_list__for_each_29(void);
static NODE *func__types__generic_list__for_each_30;
static void entry__types__generic_list__for_each_30(void);
static FRAME_INFO frame__types__generic_list__for_each_30 = {1, {"body2"}};
static void cont__types__generic_list__for_each_31(void);
static void cont__types__generic_list__for_each_32(void);
static NODE *func__types__generic_list__for_each_downwards_1;
static void entry__types__generic_list__for_each_downwards_1(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_1 = {5, {"self", "body", "body2", "i", "n"}};
static void cont__types__generic_list__for_each_downwards_2(void);
static void cont__types__generic_list__for_each_downwards_3(void);
static void cont__types__generic_list__for_each_downwards_4(void);
static NODE *func__types__generic_list__for_each_downwards_5;
static void entry__types__generic_list__for_each_downwards_5(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_5 = {5, {"n", "i", "body", "self", "body2"}};
static NODE *func__types__generic_list__for_each_downwards_6;
static void entry__types__generic_list__for_each_downwards_6(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_6 = {5, {"n", "i", "body", "self", "body2"}};
static void cont__types__generic_list__for_each_downwards_7(void);
static void cont__types__generic_list__for_each_downwards_8(void);
static NODE *func__types__generic_list__for_each_downwards_9;
static void entry__types__generic_list__for_each_downwards_9(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_9 = {5, {"body", "n", "self", "body2", "i"}};
static void cont__types__generic_list__for_each_downwards_10(void);
static void cont__types__generic_list__for_each_downwards_11(void);
static void cont__types__generic_list__for_each_downwards_12(void);
static NODE *func__types__generic_list__for_each_downwards_13;
static void entry__types__generic_list__for_each_downwards_13(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_13 = {2, {"i", "n"}};
static void cont__types__generic_list__for_each_downwards_14(void);
static void cont__types__generic_list__for_each_downwards_15(void);
static NODE *func__types__generic_list__for_each_downwards_16;
static void entry__types__generic_list__for_each_downwards_16(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_16 = {1, {"body2"}};
static void cont__types__generic_list__for_each_downwards_17(void);
static void cont__types__generic_list__for_each_downwards_18(void);
static NODE *func__types__generic_list__for_each_downwards_19;
static void entry__types__generic_list__for_each_downwards_19(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_19 = {5, {"n", "i", "body", "self", "body2"}};
static NODE *func__types__generic_list__for_each_downwards_20;
static void entry__types__generic_list__for_each_downwards_20(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_20 = {5, {"n", "i", "body", "self", "body2"}};
static void cont__types__generic_list__for_each_downwards_21(void);
static void cont__types__generic_list__for_each_downwards_22(void);
static NODE *func__types__generic_list__for_each_downwards_23;
static void entry__types__generic_list__for_each_downwards_23(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_23 = {5, {"body", "self", "n", "body2", "i"}};
static void cont__types__generic_list__for_each_downwards_24(void);
static void cont__types__generic_list__for_each_downwards_25(void);
static void cont__types__generic_list__for_each_downwards_26(void);
static NODE *func__types__generic_list__for_each_downwards_27;
static void entry__types__generic_list__for_each_downwards_27(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_27 = {2, {"i", "n"}};
static void cont__types__generic_list__for_each_downwards_28(void);
static void cont__types__generic_list__for_each_downwards_29(void);
static NODE *func__types__generic_list__for_each_downwards_30;
static void entry__types__generic_list__for_each_downwards_30(void);
static FRAME_INFO frame__types__generic_list__for_each_downwards_30 = {1, {"body2"}};
static void cont__types__generic_list__for_each_downwards_31(void);
static void cont__types__generic_list__for_each_downwards_32(void);
static NODE *func__types__generic_list__update_each_1;
static void entry__types__generic_list__update_each_1(void);
static FRAME_INFO frame__types__generic_list__update_each_1 = {7, {"self", "body", "return", "update_item", "i", "n", "new_list"}};
static NODE *func__types__generic_list__update_each_2;
static void entry__types__generic_list__update_each_2(void);
static FRAME_INFO frame__types__generic_list__update_each_2 = {3, {"new_item", "new_list", "i"}};
static void cont__types__generic_list__update_each_3(void);
static NODE *func__types__generic_list__update_each_4;
static void entry__types__generic_list__update_each_4(void);
static FRAME_INFO frame__types__generic_list__update_each_4 = {2, {"new_item", "new_list"}};
static void cont__types__generic_list__update_each_5(void);
static NODE *func__types__generic_list__update_each_6;
static void entry__types__generic_list__update_each_6(void);
static FRAME_INFO frame__types__generic_list__update_each_6 = {2, {"new_list", "new_item"}};
static void cont__types__generic_list__update_each_7(void);
static NODE *func__types__generic_list__update_each_8;
static void entry__types__generic_list__update_each_8(void);
static FRAME_INFO frame__types__generic_list__update_each_8 = {2, {"new_list", "new_item"}};
static void cont__types__generic_list__update_each_9(void);
static void cont__types__generic_list__update_each_10(void);
static void cont__types__generic_list__update_each_11(void);
static void cont__types__generic_list__update_each_12(void);
static void cont__types__generic_list__update_each_13(void);
static void cont__types__generic_list__update_each_14(void);
static NODE *func__types__generic_list__update_each_15;
static void entry__types__generic_list__update_each_15(void);
static FRAME_INFO frame__types__generic_list__update_each_15 = {5, {"n", "i", "update_item", "body", "self"}};
static NODE *func__types__generic_list__update_each_16;
static void entry__types__generic_list__update_each_16(void);
static FRAME_INFO frame__types__generic_list__update_each_16 = {5, {"n", "i", "update_item", "body", "self"}};
static void cont__types__generic_list__update_each_17(void);
static void cont__types__generic_list__update_each_18(void);
static NODE *func__types__generic_list__update_each_19;
static void entry__types__generic_list__update_each_19(void);
static FRAME_INFO frame__types__generic_list__update_each_19 = {4, {"update_item", "body", "i", "self"}};
static void cont__types__generic_list__update_each_20(void);
static void cont__types__generic_list__update_each_21(void);
static NODE *func__types__generic_list__update_each_22;
static void entry__types__generic_list__update_each_22(void);
static FRAME_INFO frame__types__generic_list__update_each_22 = {5, {"n", "i", "update_item", "body", "self"}};
static NODE *func__types__generic_list__update_each_23;
static void entry__types__generic_list__update_each_23(void);
static FRAME_INFO frame__types__generic_list__update_each_23 = {5, {"n", "i", "update_item", "body", "self"}};
static void cont__types__generic_list__update_each_24(void);
static void cont__types__generic_list__update_each_25(void);
static NODE *func__types__generic_list__update_each_26;
static void entry__types__generic_list__update_each_26(void);
static FRAME_INFO frame__types__generic_list__update_each_26 = {4, {"update_item", "body", "self", "i"}};
static void cont__types__generic_list__update_each_27(void);
static void cont__types__generic_list__update_each_28(void);
static void cont__types__generic_list__update_each_29(void);
static void cont__types__generic_list__update_each_30(void);
static NODE *func__types__list__for_each_pair_1;
static void entry__types__list__for_each_pair_1(void);
static FRAME_INFO frame__types__list__for_each_pair_1 = {4, {"self", "body", "i", "n"}};
static void cont__types__list__for_each_pair_2(void);
static NODE *func__types__list__for_each_pair_3;
static void entry__types__list__for_each_pair_3(void);
static FRAME_INFO frame__types__list__for_each_pair_3 = {4, {"i", "n", "body", "self"}};
static void cont__types__list__for_each_pair_4(void);
static NODE *func__types__list__for_each_pair_5;
static void entry__types__list__for_each_pair_5(void);
static FRAME_INFO frame__types__list__for_each_pair_5 = {3, {"body", "self", "i"}};
static void cont__types__list__for_each_pair_6(void);
static void cont__types__list__for_each_pair_7(void);
static void cont__types__list__for_each_pair_8(void);
static void cont__types__list__for_each_pair_9(void);
static void cont__types__list__for_each_pair_10(void);
static void cont__types__list__for_each_pair_11(void);
static void cont__types__list__for_each_pair_12(void);
static NODE *func__types__list__for_each_pair_13;
static void entry__types__list__for_each_pair_13(void);
static FRAME_INFO frame__types__list__for_each_pair_13 = {3, {"body", "self", "i"}};
static void cont__types__list__for_each_pair_14(void);
static NODE *func__types__generic_list__get_1;
static void entry__types__generic_list__get_1(void);
static FRAME_INFO frame__types__generic_list__get_1 = {1, {"self"}};
static void cont__types__generic_list__get_2(void);
static void cont__types__generic_list__get_3(void);
static NODE *func__types__generic_list__get_4;
static void entry__types__generic_list__get_4(void);
static FRAME_INFO frame__types__generic_list__get_4 = {0, {}};
static NODE *string__57ec57a17085427f;
static void cont__types__generic_list__get_6(void);
static void cont__types__generic_list__get_7(void);
static void cont__types__generic_list__get_8(void);
static void cont__types__generic_list__get_9(void);
static NODE *func__types__list__put_1;
static void entry__types__list__put_1(void);
static FRAME_INFO frame__types__list__put_1 = {2, {"self", "item"}};
static void cont__types__list__put_2(void);
static void cont__types__list__put_3(void);
static NODE *func__types__list__merge_1;
static void entry__types__list__merge_1(void);
static FRAME_INFO frame__types__list__merge_1 = {5, {"left", "right", "func", "return", "result"}};
static void cont__types__list__merge_2(void);
static NODE *func__types__list__merge_3;
static void entry__types__list__merge_3(void);
static FRAME_INFO frame__types__list__merge_3 = {5, {"left", "right", "func", "result", "return"}};
static void cont__types__list__merge_4(void);
static void cont__types__list__merge_5(void);
static NODE *func__types__list__merge_6;
static void entry__types__list__merge_6(void);
static FRAME_INFO frame__types__list__merge_6 = {5, {"right", "func", "left", "result", "return"}};
static void cont__types__list__merge_7(void);
static void cont__types__list__merge_8(void);
static NODE *func__types__list__merge_9;
static void entry__types__list__merge_9(void);
static FRAME_INFO frame__types__list__merge_9 = {4, {"func", "right", "left", "result"}};
static void cont__types__list__merge_10(void);
static NODE *func__types__list__merge_11;
static void entry__types__list__merge_11(void);
static FRAME_INFO frame__types__list__merge_11 = {2, {"right", "left"}};
static void cont__types__list__merge_12(void);
static void cont__types__list__merge_13(void);
static void cont__types__list__merge_14(void);
static void cont__types__list__merge_15(void);
static void cont__types__list__merge_16(void);
static NODE *func__types__list__merge_17;
static void entry__types__list__merge_17(void);
static FRAME_INFO frame__types__list__merge_17 = {3, {"func", "right", "left"}};
static void cont__types__list__merge_18(void);
static NODE *func__types__list__merge_19;
static void entry__types__list__merge_19(void);
static FRAME_INFO frame__types__list__merge_19 = {3, {"func", "right", "left"}};
static void cont__types__list__merge_20(void);
static void cont__types__list__merge_21(void);
static void cont__types__list__merge_22(void);
static void cont__types__list__merge_23(void);
static void cont__types__list__merge_24(void);
static void cont__types__list__merge_25(void);
static NODE *func__types__list__merge_26;
static void entry__types__list__merge_26(void);
static FRAME_INFO frame__types__list__merge_26 = {2, {"result", "left"}};
static void cont__types__list__merge_27(void);
static void cont__types__list__merge_28(void);
static NODE *func__types__list__merge_29;
static void entry__types__list__merge_29(void);
static FRAME_INFO frame__types__list__merge_29 = {2, {"result", "right"}};
static void cont__types__list__merge_30(void);
static void cont__types__list__merge_31(void);
static NODE *func__types__list__merge_32;
static void entry__types__list__merge_32(void);
static FRAME_INFO frame__types__list__merge_32 = {3, {"return", "result", "left"}};
static void cont__types__list__merge_33(void);
static NODE *func__types__list__merge_34;
static void entry__types__list__merge_34(void);
static FRAME_INFO frame__types__list__merge_34 = {3, {"return", "result", "right"}};
static void cont__types__list__merge_35(void);
static void cont__types__list__merge_36(void);
static NODE *func__types__list__serialize_1;
static void entry__types__list__serialize_1(void);
static FRAME_INFO frame__types__list__serialize_1 = {4, {"self", "indent", "return", "buf"}};
static void cont__types__list__serialize_2(void);
static NODE *func__types__list__serialize_3;
static void entry__types__list__serialize_3(void);
static FRAME_INFO frame__types__list__serialize_3 = {1, {"return"}};
static NODE *string__7e1f534683fac2fe;
static void cont__types__list__serialize_5(void);
static NODE *string__1a0aeb0b5df87d4d;
static NODE *func__types__list__serialize_7;
static void entry__types__list__serialize_7(void);
static FRAME_INFO frame__types__list__serialize_7 = {3, {"item", "buf", "indent"}};
static void cont__types__list__serialize_8(void);
static void cont__types__list__serialize_9(void);
static void cont__types__list__serialize_10(void);
static void cont__types__list__serialize_11(void);
static void cont__types__list__serialize_12(void);
static void cont__types__list__serialize_13(void);
static NODE *func__types__list__sort_1;
static void entry__types__list__sort_1(void);
static FRAME_INFO frame__types__list__sort_1 = {4, {"self", "func", "return", "n"}};
static void cont__types__list__sort_2(void);
static void cont__types__list__sort_3(void);
static NODE *func__types__list__sort_4;
static void entry__types__list__sort_4(void);
static FRAME_INFO frame__types__list__sort_4 = {2, {"return", "self"}};
static NODE *func__types__list__sort_5;
static void entry__types__list__sort_5(void);
static FRAME_INFO frame__types__list__sort_5 = {3, {"func", "self", "return"}};
static void cont__types__list__sort_6(void);
static NODE *func__types__list__sort_7;
static void entry__types__list__sort_7(void);
static FRAME_INFO frame__types__list__sort_7 = {1, {"self"}};
static void cont__types__list__sort_8(void);
static void cont__types__list__sort_9(void);
static void cont__types__list__sort_10(void);
static void cont__types__list__sort_11(void);
static void cont__types__list__sort_12(void);
static NODE *func__types__list__sort_13;
static void entry__types__list__sort_13(void);
static FRAME_INFO frame__types__list__sort_13 = {2, {"func", "self"}};
static void cont__types__list__sort_14(void);
static NODE *func__types__list__sort_15;
static void entry__types__list__sort_15(void);
static FRAME_INFO frame__types__list__sort_15 = {2, {"func", "self"}};
static void cont__types__list__sort_16(void);
static void cont__types__list__sort_17(void);
static void cont__types__list__sort_18(void);
static void cont__types__list__sort_19(void);
static void cont__types__list__sort_20(void);
static void cont__types__list__sort_21(void);
static NODE *func__types__list__sort_22;
static void entry__types__list__sort_22(void);
static FRAME_INFO frame__types__list__sort_22 = {2, {"return", "self"}};
static NODE *func__types__list__sort_23;
static void entry__types__list__sort_23(void);
static FRAME_INFO frame__types__list__sort_23 = {2, {"return", "self"}};
static void cont__types__list__sort_24(void);
static void cont__types__list__sort_25(void);
static void cont__types__list__sort_26(void);
static NODE *func__types__list__sort_27;
static void entry__types__list__sort_27(void);
static FRAME_INFO frame__types__list__sort_27 = {5, {"n", "func", "return", "self", "m"}};
static void cont__types__list__sort_28(void);
static void cont__types__list__sort_29(void);
static NODE *func__types__list__sort_30;
static void entry__types__list__sort_30(void);
static FRAME_INFO frame__types__list__sort_30 = {4, {"return", "self", "m", "n"}};
static void cont__types__list__sort_31(void);
static void cont__types__list__sort_32(void);
static void cont__types__list__sort_33(void);
static void cont__types__list__sort_34(void);
static void cont__types__list__sort_35(void);
static void cont__types__list__sort_36(void);
static NODE *func__types__list__sort_37;
static void entry__types__list__sort_37(void);
static FRAME_INFO frame__types__list__sort_37 = {5, {"return", "self", "m", "func", "n"}};
static void cont__types__list__sort_38(void);
static void cont__types__list__sort_39(void);
static void cont__types__list__sort_40(void);
static void cont__types__list__sort_41(void);
static void cont__types__list__sort_42(void);
static void cont__types__list__sort_43(void);
static void cont__types__list__sort_44(void);

static long func__types__list___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__types__list__new_empty_collection_1;
static void entry__types__list__new_empty_collection_1(void);
static FRAME_INFO frame__types__list__new_empty_collection_1 = {1, {"self"}};
static NODE *func__types__generic_list__equal_1;
static void entry__types__generic_list__equal_1(void);
static FRAME_INFO frame__types__generic_list__equal_1 = {3, {"left", "right", "return"}};
static void cont__types__generic_list__equal_2(void);
static NODE *func__types__generic_list__equal_3;
static void entry__types__generic_list__equal_3(void);
static FRAME_INFO frame__types__generic_list__equal_3 = {1, {"right"}};
static void cont__types__generic_list__equal_4(void);
static void cont__types__generic_list__equal_5(void);
static NODE *func__types__generic_list__equal_6;
static void entry__types__generic_list__equal_6(void);
static FRAME_INFO frame__types__generic_list__equal_6 = {1, {"return"}};
static void cont__types__generic_list__equal_7(void);
static void cont__types__generic_list__equal_8(void);
static void cont__types__generic_list__equal_9(void);
static void cont__types__generic_list__equal_10(void);
static void cont__types__generic_list__equal_11(void);
static NODE *func__types__generic_list__equal_12;
static void entry__types__generic_list__equal_12(void);
static FRAME_INFO frame__types__generic_list__equal_12 = {1, {"return"}};
static void cont__types__generic_list__equal_13(void);
static NODE *func__types__generic_list__equal_14;
static void entry__types__generic_list__equal_14(void);
static FRAME_INFO frame__types__generic_list__equal_14 = {4, {"idx", "item", "right", "return"}};
static void cont__types__generic_list__equal_15(void);
static void cont__types__generic_list__equal_16(void);
static void cont__types__generic_list__equal_17(void);
static NODE *func__types__generic_list__equal_18;
static void entry__types__generic_list__equal_18(void);
static FRAME_INFO frame__types__generic_list__equal_18 = {1, {"return"}};
static void cont__types__generic_list__equal_19(void);
static NODE *func__types__generic_list__filter_1;
static void entry__types__generic_list__filter_1(void);
static FRAME_INFO frame__types__generic_list__filter_1 = {3, {"self", "test", "new_list"}};
static void cont__types__generic_list__filter_2(void);
static NODE *func__types__generic_list__filter_3;
static void entry__types__generic_list__filter_3(void);
static FRAME_INFO frame__types__generic_list__filter_3 = {3, {"item", "test", "new_list"}};
static void cont__types__generic_list__filter_4(void);
static NODE *func__types__generic_list__filter_5;
static void entry__types__generic_list__filter_5(void);
static FRAME_INFO frame__types__generic_list__filter_5 = {2, {"new_list", "item"}};
static void cont__types__generic_list__filter_6(void);
static void cont__types__generic_list__filter_7(void);
static NODE *func__types__generic_list__map_1;
static void entry__types__generic_list__map_1(void);
static FRAME_INFO frame__types__generic_list__map_1 = {3, {"self", "func", "new_list"}};
static void cont__types__generic_list__map_2(void);
static NODE *func__types__generic_list__map_3;
static void entry__types__generic_list__map_3(void);
static FRAME_INFO frame__types__generic_list__map_3 = {3, {"item", "new_list", "func"}};
static void cont__types__generic_list__map_4(void);
static void cont__types__generic_list__map_5(void);
static void cont__types__generic_list__map_6(void);
static NODE *func__types__generic_list__dup_1;
static void entry__types__generic_list__dup_1(void);
static FRAME_INFO frame__types__generic_list__dup_1 = {2, {"self", "n"}};
static NODE *func__types__generic_list__dup_2;
static void entry__types__generic_list__dup_2(void);
static FRAME_INFO frame__types__generic_list__dup_2 = {1, {"self"}};
static NODE *func__types__generic_list__dup_3;
static void entry__types__generic_list__dup_3(void);
static FRAME_INFO frame__types__generic_list__dup_3 = {3, {"n", "self", "result"}};
static void cont__types__generic_list__dup_4(void);
static NODE *func__types__generic_list__dup_5;
static void entry__types__generic_list__dup_5(void);
static FRAME_INFO frame__types__generic_list__dup_5 = {0, {}};
static NODE *string__963fa2c6021831d1;
static void cont__types__generic_list__dup_7(void);
static void cont__types__generic_list__dup_8(void);
static void cont__types__generic_list__dup_9(void);
static void cont__types__generic_list__dup_10(void);
static void cont__types__generic_list__dup_11(void);
static NODE *func__types__generic_list__dup_12;
static void entry__types__generic_list__dup_12(void);
static FRAME_INFO frame__types__generic_list__dup_12 = {2, {"result", "self"}};
static void cont__types__generic_list__dup_13(void);
static void cont__types__generic_list__dup_14(void);
static NODE *func__types__generic_list__dup_15;
static void entry__types__generic_list__dup_15(void);
static FRAME_INFO frame__types__generic_list__dup_15 = {0, {}};
static NODE *func__types__generic_list__interleave_1;
static void entry__types__generic_list__interleave_1(void);
static FRAME_INFO frame__types__generic_list__interleave_1 = {3, {"lists", "n", "result"}};
static void cont__types__generic_list__interleave_2(void);
static void cont__types__generic_list__interleave_3(void);
static void cont__types__generic_list__interleave_4(void);
static NODE *func__types__generic_list__interleave_5;
static void entry__types__generic_list__interleave_5(void);
static FRAME_INFO frame__types__generic_list__interleave_5 = {3, {"i", "lists", "result"}};
static NODE *func__types__generic_list__interleave_6;
static void entry__types__generic_list__interleave_6(void);
static FRAME_INFO frame__types__generic_list__interleave_6 = {3, {"current_list", "result", "i"}};
static void cont__types__generic_list__interleave_7(void);
static void cont__types__generic_list__interleave_8(void);
static void cont__types__generic_list__interleave_9(void);
static NODE *func__types__generic_list__interleave_10;
static void entry__types__generic_list__interleave_10(void);
static FRAME_INFO frame__types__generic_list__interleave_10 = {3, {"current_list", "n", "result"}};
static void cont__types__generic_list__interleave_11(void);
static void cont__types__generic_list__interleave_12(void);
static void cont__types__generic_list__interleave_13(void);
static NODE *func__types__generic_list__interleave_14;
static void entry__types__generic_list__interleave_14(void);
static FRAME_INFO frame__types__generic_list__interleave_14 = {3, {"result", "current_list", "n"}};
static void cont__types__generic_list__interleave_15(void);
static void cont__types__generic_list__interleave_16(void);
static void cont__types__generic_list__interleave_17(void);
static NODE *func__types__generic_list__contains_1;
static void entry__types__generic_list__contains_1(void);
static FRAME_INFO frame__types__generic_list__contains_1 = {3, {"self", "item", "return"}};
static NODE *func__types__generic_list__contains_2;
static void entry__types__generic_list__contains_2(void);
static FRAME_INFO frame__types__generic_list__contains_2 = {3, {"current_item", "item", "return"}};
static void cont__types__generic_list__contains_3(void);
static NODE *func__types__generic_list__contains_4;
static void entry__types__generic_list__contains_4(void);
static FRAME_INFO frame__types__generic_list__contains_4 = {1, {"return"}};
static void cont__types__generic_list__contains_5(void);
static int poly_idx__std__is_a_sequence;
static void type__std__is_a_sequence(void);
static NODE *get__std__is_a_sequence(void) {
  return var.std__is_a_sequence;
}
static NODE *func__std__sequence_1;
static void entry__std__sequence_1(void);
static FRAME_INFO frame__std__sequence_1 = {1, {"items"}};
static void cont__std__sequence_2(void);
static NODE *func__std__sequence_3;
static void entry__std__sequence_3(void);
static FRAME_INFO frame__std__sequence_3 = {3, {"self", "element", "return"}};
static NODE *func__std__sequence_4;
static void entry__std__sequence_4(void);
static FRAME_INFO frame__std__sequence_4 = {3, {"item", "element", "return"}};
static void cont__std__sequence_5(void);
static NODE *func__std__sequence_6;
static void entry__std__sequence_6(void);
static FRAME_INFO frame__std__sequence_6 = {2, {"item", "element"}};
static void cont__std__sequence_7(void);
static void cont__std__sequence_8(void);
static NODE *func__std__sequence_9;
static void entry__std__sequence_9(void);
static FRAME_INFO frame__std__sequence_9 = {1, {"return"}};
static void cont__std__sequence_10(void);
static NODE *get__std__sequence(void) {
  return var.std__sequence;
}
static NODE *func__96_1;
static void entry__96_1(void);
static FRAME_INFO frame__96_1 = {4, {"text", "base_indent", "return", "obj"}};
static NODE *string__2d7981f4e6482bec;
static void cont__96_3(void);
static NODE *func__96_4;
static void entry__96_4(void);
static FRAME_INFO frame__96_4 = {2, {"return", "text"}};
static void cont__96_5(void);
static void cont__96_6(void);
static void cont__96_7(void);
static void cont__96_8(void);
static void cont__96_9(void);
static void cont__96_10(void);
static NODE *func__96_11;
static void entry__96_11(void);
static FRAME_INFO frame__96_11 = {0, {}};
static NODE *string__b53819e78eec080a;
static void cont__96_13(void);
static NODE *func__96_14;
static void entry__96_14(void);
static FRAME_INFO frame__96_14 = {6, {"text", "return", "obj", "base_indent", "remaining_text", "indent"}};
static void cont__96_15(void);
static void cont__96_16(void);
static NODE *func__96_17;
static void entry__96_17(void);
static FRAME_INFO frame__96_17 = {1, {"text"}};
static void cont__96_18(void);
static void cont__96_19(void);
static void cont__96_20(void);
static void cont__96_21(void);
static NODE *func__96_22;
static void entry__96_22(void);
static FRAME_INFO frame__96_22 = {3, {"return", "text", "obj"}};
static void cont__96_23(void);
static void cont__96_24(void);
static void cont__96_25(void);
static void cont__96_26(void);
static NODE *func__96_27;
static void entry__96_27(void);
static FRAME_INFO frame__96_27 = {3, {"return", "text", "obj"}};
static void cont__96_28(void);
static void cont__96_29(void);
static void cont__96_30(void);
static void cont__96_31(void);
static void cont__96_32(void);
void run__basic__types__list(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_list, NULL, 25, 25, 2, 15},
  {type__std__is_a_sequence, NULL, 753, 753, 2, 19},
  {run__basic__types__list, NULL, 778, 795, 1, 45},
  {cont__96_32, NULL, },
  {entry__types__list__to_list_1, NULL, 177, 177, 3, 9},
  {entry__std__list_1, NULL, 182, 194, 3, 2},
  {entry__types__list__length_of_1, NULL, 199, 202, 3, 2},
  {entry__types__list__push_1, NULL, 207, 225, 3, 2},
  {entry__types__list__drop_1, NULL, 230, 237, 3, 2},
  {entry__types__list__pop_1, NULL, 242, 253, 3, 2},
  {entry__types__list__peek_1, NULL, 258, 264, 3, 2},
  {entry__types__list__append_1, NULL, 269, 294, 3, 2},
  {entry__types__list__range_1, NULL, 299, 320, 3, 2},
  {entry__types__generic_list__delete_at_4, NULL, 330, 330, 44, 48},
  {cont__types__generic_list__delete_at_5, &frame__types__generic_list__delete_at_4, 330, 330, 31, 49},
  {cont__types__generic_list__delete_at_6, &frame__types__generic_list__delete_at_4, 330, 330, 62, 70},
  {cont__types__generic_list__delete_at_7, &frame__types__generic_list__delete_at_4, 330, 330, 73, 73},
  {cont__types__generic_list__delete_at_8, &frame__types__generic_list__delete_at_4, 330, 330, 51, 74},
  {cont__types__generic_list__delete_at_9, &frame__types__generic_list__delete_at_4, 330, 330, 18, 75},
  {cont__types__generic_list__delete_at_10, &frame__types__generic_list__delete_at_4, 330, 330, 75, 75},
  {entry__types__generic_list__delete_at_1, NULL, 330, 330, 6, 15},
  {cont__types__generic_list__delete_at_2, &frame__types__generic_list__delete_at_1, 330, 330, 6, 15},
  {cont__types__generic_list__delete_at_3, &frame__types__generic_list__delete_at_1, 330, 330, 3, 75},
  {cont__types__generic_list__delete_at_11, &frame__types__generic_list__delete_at_1, },
  {entry__std__normalized_index_4, NULL, 342, 342, 7, 16},
  {entry__std__normalized_index_5, NULL, 344, 344, 14, 28},
  {cont__std__normalized_index_6, &frame__std__normalized_index_5, 344, 344, 14, 30},
  {cont__std__normalized_index_7, &frame__std__normalized_index_5, 344, 344, 14, 34},
  {cont__std__normalized_index_8, &frame__std__normalized_index_5, 344, 344, 7, 34},
  {entry__std__normalized_index_1, NULL, 341, 341, 5, 12},
  {cont__std__normalized_index_2, &frame__std__normalized_index_1, 341, 341, 5, 12},
  {cont__std__normalized_index_3, &frame__std__normalized_index_1, 340, 344, 3, 35},
  {cont__std__normalized_index_9, &frame__std__normalized_index_1, 344, 344, 35, 35},
  {entry__types__generic_list__is_empty_1, NULL, 352, 352, 6, 20},
  {cont__types__generic_list__is_empty_2, &frame__types__generic_list__is_empty_1, 352, 352, 6, 25},
  {cont__types__generic_list__is_empty_3, &frame__types__generic_list__is_empty_1, 352, 352, 3, 25},
  {entry__types__generic_list__for_each_from_to_10, NULL, 381, 381, 16, 22},
  {cont__types__generic_list__for_each_from_to_11, &frame__types__generic_list__for_each_from_to_10, 381, 381, 9, 22},
  {entry__types__generic_list__for_each_from_to_12, NULL, 383, 383, 14, 20},
  {cont__types__generic_list__for_each_from_to_13, &frame__types__generic_list__for_each_from_to_12, 383, 383, 9, 20},
  {entry__types__generic_list__for_each_from_to_16, NULL, 384, 384, 28, 32},
  {cont__types__generic_list__for_each_from_to_17, &frame__types__generic_list__for_each_from_to_16, 384, 384, 28, 32},
  {entry__types__generic_list__for_each_from_to_19, NULL, 384, 384, 35, 39},
  {entry__types__generic_list__for_each_from_to_7, NULL, 380, 380, 7, 30},
  {cont__types__generic_list__for_each_from_to_8, &frame__types__generic_list__for_each_from_to_7, 380, 380, 7, 35},
  {cont__types__generic_list__for_each_from_to_9, &frame__types__generic_list__for_each_from_to_7, 379, 383, 5, 21},
  {cont__types__generic_list__for_each_from_to_14, &frame__types__generic_list__for_each_from_to_7, 384, 384, 8, 23},
  {cont__types__generic_list__for_each_from_to_15, &frame__types__generic_list__for_each_from_to_7, 384, 384, 8, 32},
  {cont__types__generic_list__for_each_from_to_18, &frame__types__generic_list__for_each_from_to_7, 384, 384, 5, 39},
  {cont__types__generic_list__for_each_from_to_20, &frame__types__generic_list__for_each_from_to_7, 385, 385, 5, 13},
  {cont__types__generic_list__for_each_from_to_21, &frame__types__generic_list__for_each_from_to_7, 385, 385, 13, 13},
  {entry__types__generic_list__for_each_from_to_4, NULL, 378, 378, 12, 17},
  {cont__types__generic_list__for_each_from_to_5, &frame__types__generic_list__for_each_from_to_4, 378, 378, 12, 17},
  {cont__types__generic_list__for_each_from_to_6, &frame__types__generic_list__for_each_from_to_4, 378, 385, 9, 13},
  {entry__types__generic_list__for_each_from_to_1, NULL, 376, 376, 3, 34},
  {cont__types__generic_list__for_each_from_to_2, &frame__types__generic_list__for_each_from_to_1, 377, 377, 3, 32},
  {cont__types__generic_list__for_each_from_to_3, &frame__types__generic_list__for_each_from_to_1, 378, 385, 3, 13},
  {entry__types__generic_list__for_each_from_down_to_10, NULL, 414, 414, 16, 22},
  {cont__types__generic_list__for_each_from_down_to_11, &frame__types__generic_list__for_each_from_down_to_10, 414, 414, 9, 22},
  {entry__types__generic_list__for_each_from_down_to_12, NULL, 416, 416, 14, 20},
  {cont__types__generic_list__for_each_from_down_to_13, &frame__types__generic_list__for_each_from_down_to_12, 416, 416, 9, 20},
  {entry__types__generic_list__for_each_from_down_to_16, NULL, 417, 417, 28, 32},
  {cont__types__generic_list__for_each_from_down_to_17, &frame__types__generic_list__for_each_from_down_to_16, 417, 417, 28, 32},
  {entry__types__generic_list__for_each_from_down_to_19, NULL, 417, 417, 35, 39},
  {entry__types__generic_list__for_each_from_down_to_7, NULL, 413, 413, 7, 30},
  {cont__types__generic_list__for_each_from_down_to_8, &frame__types__generic_list__for_each_from_down_to_7, 413, 413, 7, 35},
  {cont__types__generic_list__for_each_from_down_to_9, &frame__types__generic_list__for_each_from_down_to_7, 412, 416, 5, 21},
  {cont__types__generic_list__for_each_from_down_to_14, &frame__types__generic_list__for_each_from_down_to_7, 417, 417, 8, 23},
  {cont__types__generic_list__for_each_from_down_to_15, &frame__types__generic_list__for_each_from_down_to_7, 417, 417, 8, 32},
  {cont__types__generic_list__for_each_from_down_to_18, &frame__types__generic_list__for_each_from_down_to_7, 417, 417, 5, 39},
  {cont__types__generic_list__for_each_from_down_to_20, &frame__types__generic_list__for_each_from_down_to_7, 418, 418, 5, 14},
  {cont__types__generic_list__for_each_from_down_to_21, &frame__types__generic_list__for_each_from_down_to_7, 418, 418, 14, 14},
  {entry__types__generic_list__for_each_from_down_to_4, NULL, 411, 411, 12, 17},
  {cont__types__generic_list__for_each_from_down_to_5, &frame__types__generic_list__for_each_from_down_to_4, 411, 411, 12, 17},
  {cont__types__generic_list__for_each_from_down_to_6, &frame__types__generic_list__for_each_from_down_to_4, 411, 418, 9, 14},
  {entry__types__generic_list__for_each_from_down_to_1, NULL, 409, 409, 3, 34},
  {cont__types__generic_list__for_each_from_down_to_2, &frame__types__generic_list__for_each_from_down_to_1, 410, 410, 3, 32},
  {cont__types__generic_list__for_each_from_down_to_3, &frame__types__generic_list__for_each_from_down_to_1, 411, 418, 3, 14},
  {entry__types__generic_list__for_each_13, NULL, 443, 443, 32, 36},
  {cont__types__generic_list__for_each_14, &frame__types__generic_list__for_each_13, 443, 443, 32, 36},
  {entry__types__generic_list__for_each_16, NULL, 443, 443, 39, 43},
  {entry__types__generic_list__for_each_9, NULL, 442, 442, 16, 22},
  {cont__types__generic_list__for_each_10, &frame__types__generic_list__for_each_9, 442, 442, 9, 22},
  {cont__types__generic_list__for_each_11, &frame__types__generic_list__for_each_9, 443, 443, 12, 27},
  {cont__types__generic_list__for_each_12, &frame__types__generic_list__for_each_9, 443, 443, 12, 36},
  {cont__types__generic_list__for_each_15, &frame__types__generic_list__for_each_9, 443, 443, 9, 43},
  {cont__types__generic_list__for_each_17, &frame__types__generic_list__for_each_9, 444, 444, 9, 17},
  {cont__types__generic_list__for_each_18, &frame__types__generic_list__for_each_9, 444, 444, 17, 17},
  {entry__types__generic_list__for_each_6, NULL, 441, 441, 16, 21},
  {cont__types__generic_list__for_each_7, &frame__types__generic_list__for_each_6, 441, 441, 16, 21},
  {cont__types__generic_list__for_each_8, &frame__types__generic_list__for_each_6, 441, 444, 13, 17},
  {entry__types__generic_list__for_each_5, NULL, 441, 444, 7, 17},
  {entry__types__generic_list__for_each_27, NULL, 448, 448, 32, 36},
  {cont__types__generic_list__for_each_28, &frame__types__generic_list__for_each_27, 448, 448, 32, 36},
  {entry__types__generic_list__for_each_30, NULL, 448, 448, 39, 43},
  {entry__types__generic_list__for_each_23, NULL, 447, 447, 14, 20},
  {cont__types__generic_list__for_each_24, &frame__types__generic_list__for_each_23, 447, 447, 9, 20},
  {cont__types__generic_list__for_each_25, &frame__types__generic_list__for_each_23, 448, 448, 12, 27},
  {cont__types__generic_list__for_each_26, &frame__types__generic_list__for_each_23, 448, 448, 12, 36},
  {cont__types__generic_list__for_each_29, &frame__types__generic_list__for_each_23, 448, 448, 9, 43},
  {cont__types__generic_list__for_each_31, &frame__types__generic_list__for_each_23, 449, 449, 9, 17},
  {cont__types__generic_list__for_each_32, &frame__types__generic_list__for_each_23, 449, 449, 17, 17},
  {entry__types__generic_list__for_each_20, NULL, 446, 446, 16, 21},
  {cont__types__generic_list__for_each_21, &frame__types__generic_list__for_each_20, 446, 446, 16, 21},
  {cont__types__generic_list__for_each_22, &frame__types__generic_list__for_each_20, 446, 449, 13, 17},
  {entry__types__generic_list__for_each_19, NULL, 446, 449, 7, 17},
  {entry__types__generic_list__for_each_1, NULL, 438, 438, 3, 20},
  {cont__types__generic_list__for_each_2, &frame__types__generic_list__for_each_1, 440, 440, 5, 28},
  {cont__types__generic_list__for_each_3, &frame__types__generic_list__for_each_1, 440, 440, 5, 33},
  {cont__types__generic_list__for_each_4, &frame__types__generic_list__for_each_1, 439, 449, 3, 19},
  {entry__types__generic_list__for_each_downwards_13, NULL, 474, 474, 32, 36},
  {cont__types__generic_list__for_each_downwards_14, &frame__types__generic_list__for_each_downwards_13, 474, 474, 32, 36},
  {entry__types__generic_list__for_each_downwards_16, NULL, 474, 474, 39, 43},
  {entry__types__generic_list__for_each_downwards_9, NULL, 473, 473, 16, 22},
  {cont__types__generic_list__for_each_downwards_10, &frame__types__generic_list__for_each_downwards_9, 473, 473, 9, 22},
  {cont__types__generic_list__for_each_downwards_11, &frame__types__generic_list__for_each_downwards_9, 474, 474, 12, 27},
  {cont__types__generic_list__for_each_downwards_12, &frame__types__generic_list__for_each_downwards_9, 474, 474, 12, 36},
  {cont__types__generic_list__for_each_downwards_15, &frame__types__generic_list__for_each_downwards_9, 474, 474, 9, 43},
  {cont__types__generic_list__for_each_downwards_17, &frame__types__generic_list__for_each_downwards_9, 475, 475, 9, 18},
  {cont__types__generic_list__for_each_downwards_18, &frame__types__generic_list__for_each_downwards_9, 475, 475, 18, 18},
  {entry__types__generic_list__for_each_downwards_6, NULL, 472, 472, 16, 21},
  {cont__types__generic_list__for_each_downwards_7, &frame__types__generic_list__for_each_downwards_6, 472, 472, 16, 21},
  {cont__types__generic_list__for_each_downwards_8, &frame__types__generic_list__for_each_downwards_6, 472, 475, 13, 18},
  {entry__types__generic_list__for_each_downwards_5, NULL, 472, 475, 7, 18},
  {entry__types__generic_list__for_each_downwards_27, NULL, 479, 479, 32, 36},
  {cont__types__generic_list__for_each_downwards_28, &frame__types__generic_list__for_each_downwards_27, 479, 479, 32, 36},
  {entry__types__generic_list__for_each_downwards_30, NULL, 479, 479, 39, 43},
  {entry__types__generic_list__for_each_downwards_23, NULL, 478, 478, 14, 20},
  {cont__types__generic_list__for_each_downwards_24, &frame__types__generic_list__for_each_downwards_23, 478, 478, 9, 20},
  {cont__types__generic_list__for_each_downwards_25, &frame__types__generic_list__for_each_downwards_23, 479, 479, 12, 27},
  {cont__types__generic_list__for_each_downwards_26, &frame__types__generic_list__for_each_downwards_23, 479, 479, 12, 36},
  {cont__types__generic_list__for_each_downwards_29, &frame__types__generic_list__for_each_downwards_23, 479, 479, 9, 43},
  {cont__types__generic_list__for_each_downwards_31, &frame__types__generic_list__for_each_downwards_23, 480, 480, 9, 18},
  {cont__types__generic_list__for_each_downwards_32, &frame__types__generic_list__for_each_downwards_23, 480, 480, 18, 18},
  {entry__types__generic_list__for_each_downwards_20, NULL, 477, 477, 16, 21},
  {cont__types__generic_list__for_each_downwards_21, &frame__types__generic_list__for_each_downwards_20, 477, 477, 16, 21},
  {cont__types__generic_list__for_each_downwards_22, &frame__types__generic_list__for_each_downwards_20, 477, 480, 13, 18},
  {entry__types__generic_list__for_each_downwards_19, NULL, 477, 480, 7, 18},
  {entry__types__generic_list__for_each_downwards_1, NULL, 469, 469, 3, 21},
  {cont__types__generic_list__for_each_downwards_2, &frame__types__generic_list__for_each_downwards_1, 471, 471, 5, 28},
  {cont__types__generic_list__for_each_downwards_3, &frame__types__generic_list__for_each_downwards_1, 471, 471, 5, 33},
  {cont__types__generic_list__for_each_downwards_4, &frame__types__generic_list__for_each_downwards_1, 470, 480, 3, 20},
  {entry__types__generic_list__update_each_6, NULL, 510, 510, 11, 35},
  {cont__types__generic_list__update_each_7, &frame__types__generic_list__update_each_6, 510, 510, 35, 35},
  {entry__types__generic_list__update_each_8, NULL, 512, 512, 11, 33},
  {cont__types__generic_list__update_each_9, &frame__types__generic_list__update_each_8, 512, 512, 33, 33},
  {entry__types__generic_list__update_each_4, NULL, 509, 509, 9, 30},
  {cont__types__generic_list__update_each_5, &frame__types__generic_list__update_each_4, 508, 512, 7, 34},
  {entry__types__generic_list__update_each_2, NULL, 507, 507, 8, 26},
  {cont__types__generic_list__update_each_3, &frame__types__generic_list__update_each_2, 507, 512, 5, 35},
  {cont__types__generic_list__update_each_10, &frame__types__generic_list__update_each_2, 513, 513, 5, 13},
  {cont__types__generic_list__update_each_11, &frame__types__generic_list__update_each_2, 513, 513, 13, 13},
  {entry__types__generic_list__update_each_19, NULL, 520, 520, 43, 49},
  {cont__types__generic_list__update_each_20, &frame__types__generic_list__update_each_19, 520, 520, 36, 50},
  {cont__types__generic_list__update_each_21, &frame__types__generic_list__update_each_19, 520, 520, 24, 50},
  {entry__types__generic_list__update_each_16, NULL, 520, 520, 16, 21},
  {cont__types__generic_list__update_each_17, &frame__types__generic_list__update_each_16, 520, 520, 16, 21},
  {cont__types__generic_list__update_each_18, &frame__types__generic_list__update_each_16, 520, 520, 13, 50},
  {entry__types__generic_list__update_each_15, NULL, 520, 520, 7, 50},
  {entry__types__generic_list__update_each_26, NULL, 522, 522, 41, 47},
  {cont__types__generic_list__update_each_27, &frame__types__generic_list__update_each_26, 522, 522, 36, 48},
  {cont__types__generic_list__update_each_28, &frame__types__generic_list__update_each_26, 522, 522, 24, 48},
  {entry__types__generic_list__update_each_23, NULL, 522, 522, 16, 21},
  {cont__types__generic_list__update_each_24, &frame__types__generic_list__update_each_23, 522, 522, 16, 21},
  {cont__types__generic_list__update_each_25, &frame__types__generic_list__update_each_23, 522, 522, 13, 48},
  {entry__types__generic_list__update_each_22, NULL, 522, 522, 7, 48},
  {entry__types__generic_list__update_each_1, NULL, 516, 516, 3, 20},
  {cont__types__generic_list__update_each_12, &frame__types__generic_list__update_each_1, 519, 519, 5, 28},
  {cont__types__generic_list__update_each_13, &frame__types__generic_list__update_each_1, 519, 519, 5, 33},
  {cont__types__generic_list__update_each_14, &frame__types__generic_list__update_each_1, 518, 522, 3, 49},
  {cont__types__generic_list__update_each_29, &frame__types__generic_list__update_each_1, 523, 523, 3, 17},
  {cont__types__generic_list__update_each_30, &frame__types__generic_list__update_each_1, 523, 523, 17, 17},
  {entry__types__list__for_each_pair_5, NULL, 539, 539, 10, 16},
  {cont__types__list__for_each_pair_6, &frame__types__list__for_each_pair_5, 539, 539, 23, 25},
  {cont__types__list__for_each_pair_7, &frame__types__list__for_each_pair_5, 539, 539, 18, 26},
  {cont__types__list__for_each_pair_8, &frame__types__list__for_each_pair_5, 539, 539, 5, 26},
  {cont__types__list__for_each_pair_9, &frame__types__list__for_each_pair_5, 540, 540, 5, 13},
  {cont__types__list__for_each_pair_10, &frame__types__list__for_each_pair_5, 540, 540, 13, 13},
  {entry__types__list__for_each_pair_3, NULL, 538, 538, 12, 16},
  {cont__types__list__for_each_pair_4, &frame__types__list__for_each_pair_3, 538, 540, 9, 13},
  {entry__types__list__for_each_pair_13, NULL, 541, 541, 22, 28},
  {cont__types__list__for_each_pair_14, &frame__types__list__for_each_pair_13, 541, 541, 17, 28},
  {entry__types__list__for_each_pair_1, NULL, 537, 537, 3, 20},
  {cont__types__list__for_each_pair_2, &frame__types__list__for_each_pair_1, 538, 540, 3, 13},
  {cont__types__list__for_each_pair_11, &frame__types__list__for_each_pair_1, 541, 541, 6, 14},
  {cont__types__list__for_each_pair_12, &frame__types__list__for_each_pair_1, 541, 541, 3, 28},
  {entry__types__generic_list__get_4, NULL, 549, 549, 28, 80},
  {entry__types__generic_list__get_1, NULL, 549, 549, 6, 20},
  {cont__types__generic_list__get_2, &frame__types__generic_list__get_1, 549, 549, 6, 25},
  {cont__types__generic_list__get_3, &frame__types__generic_list__get_1, 549, 549, 3, 80},
  {cont__types__generic_list__get_6, &frame__types__generic_list__get_1, 550, 550, 20, 20},
  {cont__types__generic_list__get_7, &frame__types__generic_list__get_1, 550, 550, 6, 21},
  {cont__types__generic_list__get_8, &frame__types__generic_list__get_1, 550, 550, 23, 29},
  {cont__types__generic_list__get_9, &frame__types__generic_list__get_1, 550, 550, 3, 29},
  {entry__types__list__put_1, NULL, 559, 559, 13, 22},
  {cont__types__list__put_2, &frame__types__list__put_1, 559, 559, 6, 28},
  {cont__types__list__put_3, &frame__types__list__put_1, 559, 559, 3, 28},
  {entry__types__list__merge_11, NULL, 578, 578, 49, 56},
  {cont__types__list__merge_12, &frame__types__list__merge_11, 578, 578, 38, 44},
  {cont__types__list__merge_13, &frame__types__list__merge_11, 578, 578, 38, 56},
  {cont__types__list__merge_14, &frame__types__list__merge_11, 578, 578, 38, 56},
  {cont__types__list__merge_15, &frame__types__list__merge_11, 578, 578, 38, 56},
  {entry__types__list__merge_19, NULL, 579, 579, 45, 52},
  {cont__types__list__merge_20, &frame__types__list__merge_19, 579, 579, 54, 60},
  {cont__types__list__merge_21, &frame__types__list__merge_19, 579, 579, 40, 61},
  {cont__types__list__merge_22, &frame__types__list__merge_19, 579, 579, 36, 62},
  {cont__types__list__merge_23, &frame__types__list__merge_19, 579, 579, 36, 62},
  {entry__types__list__merge_17, NULL, 579, 579, 17, 31},
  {cont__types__list__merge_18, &frame__types__list__merge_17, 579, 579, 17, 62},
  {cont__types__list__merge_24, &frame__types__list__merge_17, 579, 579, 17, 62},
  {entry__types__list__merge_26, NULL, 581, 581, 30, 39},
  {cont__types__list__merge_27, &frame__types__list__merge_26, 581, 581, 17, 39},
  {cont__types__list__merge_28, &frame__types__list__merge_26, 581, 581, 39, 39},
  {entry__types__list__merge_29, NULL, 583, 583, 30, 40},
  {cont__types__list__merge_30, &frame__types__list__merge_29, 583, 583, 17, 40},
  {cont__types__list__merge_31, &frame__types__list__merge_29, 583, 583, 40, 40},
  {entry__types__list__merge_9, NULL, 578, 578, 17, 33},
  {cont__types__list__merge_10, &frame__types__list__merge_9, 578, 578, 17, 56},
  {cont__types__list__merge_16, &frame__types__list__merge_9, 577, 579, 15, 62},
  {cont__types__list__merge_25, &frame__types__list__merge_9, 576, 583, 13, 41},
  {entry__types__list__merge_32, NULL, 585, 585, 20, 38},
  {cont__types__list__merge_33, &frame__types__list__merge_32, 585, 585, 13, 38},
  {entry__types__list__merge_6, NULL, 575, 575, 11, 26},
  {cont__types__list__merge_7, &frame__types__list__merge_6, 575, 575, 11, 30},
  {cont__types__list__merge_8, &frame__types__list__merge_6, 574, 585, 9, 39},
  {entry__types__list__merge_34, NULL, 587, 587, 16, 35},
  {cont__types__list__merge_35, &frame__types__list__merge_34, 587, 587, 9, 35},
  {entry__types__list__merge_3, NULL, 573, 573, 7, 21},
  {cont__types__list__merge_4, &frame__types__list__merge_3, 573, 573, 7, 25},
  {cont__types__list__merge_5, &frame__types__list__merge_3, 572, 587, 5, 36},
  {entry__types__list__merge_1, NULL, 570, 570, 3, 17},
  {cont__types__list__merge_2, &frame__types__list__merge_1, 571, 587, 3, 37},
  {cont__types__list__merge_36, &frame__types__list__merge_1, 587, 587, 37, 37},
  {entry__types__list__serialize_3, NULL, 597, 597, 21, 35},
  {entry__types__list__serialize_7, NULL, 600, 600, 33, 40},
  {cont__types__list__serialize_8, &frame__types__list__serialize_7, 600, 600, 26, 41},
  {cont__types__list__serialize_9, &frame__types__list__serialize_7, 600, 600, 58, 65},
  {cont__types__list__serialize_10, &frame__types__list__serialize_7, 600, 600, 43, 66},
  {cont__types__list__serialize_11, &frame__types__list__serialize_7, 600, 600, 5, 66},
  {cont__types__list__serialize_12, &frame__types__list__serialize_7, 600, 600, 66, 66},
  {entry__types__list__serialize_1, NULL, 597, 597, 6, 18},
  {cont__types__list__serialize_2, &frame__types__list__serialize_1, 597, 597, 3, 35},
  {cont__types__list__serialize_5, &frame__types__list__serialize_1, 599, 600, 3, 66},
  {cont__types__list__serialize_13, &frame__types__list__serialize_1, 601, 601, 3, 8},
  {entry__types__list__sort_4, NULL, 617, 617, 7, 17},
  {entry__types__list__sort_7, NULL, 621, 621, 43, 49},
  {cont__types__list__sort_8, &frame__types__list__sort_7, 621, 621, 32, 38},
  {cont__types__list__sort_9, &frame__types__list__sort_7, 621, 621, 32, 49},
  {cont__types__list__sort_10, &frame__types__list__sort_7, 621, 621, 32, 49},
  {cont__types__list__sort_11, &frame__types__list__sort_7, 621, 621, 32, 49},
  {entry__types__list__sort_15, NULL, 622, 622, 39, 45},
  {cont__types__list__sort_16, &frame__types__list__sort_15, 622, 622, 47, 53},
  {cont__types__list__sort_17, &frame__types__list__sort_15, 622, 622, 34, 54},
  {cont__types__list__sort_18, &frame__types__list__sort_15, 622, 622, 30, 55},
  {cont__types__list__sort_19, &frame__types__list__sort_15, 622, 622, 30, 55},
  {entry__types__list__sort_13, NULL, 622, 622, 11, 25},
  {cont__types__list__sort_14, &frame__types__list__sort_13, 622, 622, 11, 55},
  {cont__types__list__sort_20, &frame__types__list__sort_13, 622, 622, 11, 55},
  {entry__types__list__sort_22, NULL, 624, 624, 11, 21},
  {entry__types__list__sort_23, NULL, 626, 626, 23, 29},
  {cont__types__list__sort_24, &frame__types__list__sort_23, 626, 626, 31, 37},
  {cont__types__list__sort_25, &frame__types__list__sort_23, 626, 626, 18, 38},
  {cont__types__list__sort_26, &frame__types__list__sort_23, 626, 626, 11, 38},
  {entry__types__list__sort_5, NULL, 621, 621, 11, 27},
  {cont__types__list__sort_6, &frame__types__list__sort_5, 621, 621, 11, 49},
  {cont__types__list__sort_12, &frame__types__list__sort_5, 620, 622, 9, 55},
  {cont__types__list__sort_21, &frame__types__list__sort_5, 619, 626, 7, 39},
  {entry__types__list__sort_30, NULL, 631, 631, 29, 43},
  {cont__types__list__sort_31, &frame__types__list__sort_30, 631, 631, 24, 44},
  {cont__types__list__sort_32, &frame__types__list__sort_30, 631, 631, 62, 64},
  {cont__types__list__sort_33, &frame__types__list__sort_30, 631, 631, 51, 67},
  {cont__types__list__sort_34, &frame__types__list__sort_30, 631, 631, 46, 68},
  {cont__types__list__sort_35, &frame__types__list__sort_30, 631, 631, 18, 69},
  {cont__types__list__sort_36, &frame__types__list__sort_30, 631, 631, 11, 69},
  {entry__types__list__sort_37, NULL, 634, 634, 24, 38},
  {cont__types__list__sort_38, &frame__types__list__sort_37, 634, 634, 19, 44},
  {cont__types__list__sort_39, &frame__types__list__sort_37, 634, 634, 62, 64},
  {cont__types__list__sort_40, &frame__types__list__sort_37, 634, 634, 51, 67},
  {cont__types__list__sort_41, &frame__types__list__sort_37, 634, 634, 46, 73},
  {cont__types__list__sort_42, &frame__types__list__sort_37, 634, 634, 13, 79},
  {cont__types__list__sort_43, &frame__types__list__sort_37, 633, 634, 11, 79},
  {entry__types__list__sort_27, NULL, 628, 628, 7, 18},
  {cont__types__list__sort_28, &frame__types__list__sort_27, 630, 630, 9, 25},
  {cont__types__list__sort_29, &frame__types__list__sort_27, 629, 634, 7, 81},
  {entry__types__list__sort_1, NULL, 614, 614, 3, 20},
  {cont__types__list__sort_2, &frame__types__list__sort_1, 616, 616, 5, 8},
  {cont__types__list__sort_3, &frame__types__list__sort_1, 615, 634, 3, 83},
  {cont__types__list__sort_44, &frame__types__list__sort_1, 634, 634, 83, 83},
  {entry__types__list__new_empty_collection_1, NULL, 671, 671, 3, 16},
  {entry__types__generic_list__equal_3, NULL, 683, 683, 30, 44},
  {cont__types__generic_list__equal_4, &frame__types__generic_list__equal_3, 683, 683, 30, 44},
  {entry__types__generic_list__equal_6, NULL, 683, 683, 47, 58},
  {entry__types__generic_list__equal_12, NULL, 684, 684, 43, 54},
  {entry__types__generic_list__equal_18, NULL, 685, 685, 52, 63},
  {entry__types__generic_list__equal_14, NULL, 685, 685, 40, 49},
  {cont__types__generic_list__equal_15, &frame__types__generic_list__equal_14, 685, 685, 32, 49},
  {cont__types__generic_list__equal_16, &frame__types__generic_list__equal_14, 685, 685, 32, 49},
  {cont__types__generic_list__equal_17, &frame__types__generic_list__equal_14, 685, 685, 29, 63},
  {entry__types__generic_list__equal_1, NULL, 683, 683, 10, 25},
  {cont__types__generic_list__equal_2, &frame__types__generic_list__equal_1, 683, 683, 10, 44},
  {cont__types__generic_list__equal_5, &frame__types__generic_list__equal_1, 683, 683, 3, 58},
  {cont__types__generic_list__equal_7, &frame__types__generic_list__equal_1, 684, 684, 6, 20},
  {cont__types__generic_list__equal_8, &frame__types__generic_list__equal_1, 684, 684, 25, 40},
  {cont__types__generic_list__equal_9, &frame__types__generic_list__equal_1, 684, 684, 6, 40},
  {cont__types__generic_list__equal_10, &frame__types__generic_list__equal_1, 684, 684, 6, 40},
  {cont__types__generic_list__equal_11, &frame__types__generic_list__equal_1, 684, 684, 3, 54},
  {cont__types__generic_list__equal_13, &frame__types__generic_list__equal_1, 685, 685, 3, 63},
  {cont__types__generic_list__equal_19, &frame__types__generic_list__equal_1, 686, 686, 3, 9},
  {entry__types__generic_list__filter_5, NULL, 696, 696, 40, 58},
  {cont__types__generic_list__filter_6, &frame__types__generic_list__filter_5, 696, 696, 58, 58},
  {entry__types__generic_list__filter_3, NULL, 696, 696, 28, 37},
  {cont__types__generic_list__filter_4, &frame__types__generic_list__filter_3, 696, 696, 25, 58},
  {entry__types__generic_list__filter_1, NULL, 695, 695, 3, 39},
  {cont__types__generic_list__filter_2, &frame__types__generic_list__filter_1, 696, 696, 3, 58},
  {cont__types__generic_list__filter_7, &frame__types__generic_list__filter_1, 697, 697, 3, 13},
  {entry__types__generic_list__map_3, NULL, 709, 709, 40, 49},
  {cont__types__generic_list__map_4, &frame__types__generic_list__map_3, 709, 709, 25, 49},
  {cont__types__generic_list__map_5, &frame__types__generic_list__map_3, 709, 709, 49, 49},
  {entry__types__generic_list__map_1, NULL, 708, 708, 3, 39},
  {cont__types__generic_list__map_2, &frame__types__generic_list__map_1, 709, 709, 3, 49},
  {cont__types__generic_list__map_6, &frame__types__generic_list__map_1, 710, 710, 3, 13},
  {entry__types__generic_list__dup_2, NULL, 719, 719, 31, 37},
  {entry__types__generic_list__dup_5, NULL, 720, 720, 15, 48},
  {entry__types__generic_list__dup_12, NULL, 723, 723, 18, 36},
  {cont__types__generic_list__dup_13, &frame__types__generic_list__dup_12, 723, 723, 36, 36},
  {entry__types__generic_list__dup_3, NULL, 720, 720, 8, 12},
  {cont__types__generic_list__dup_4, &frame__types__generic_list__dup_3, 720, 720, 5, 48},
  {cont__types__generic_list__dup_7, &frame__types__generic_list__dup_3, 721, 721, 23, 31},
  {cont__types__generic_list__dup_8, &frame__types__generic_list__dup_3, 721, 721, 5, 32},
  {cont__types__generic_list__dup_9, &frame__types__generic_list__dup_3, 722, 722, 5, 25},
  {cont__types__generic_list__dup_10, &frame__types__generic_list__dup_3, 723, 723, 8, 15},
  {cont__types__generic_list__dup_11, &frame__types__generic_list__dup_3, 723, 723, 5, 36},
  {cont__types__generic_list__dup_14, &frame__types__generic_list__dup_3, 724, 724, 5, 13},
  {entry__types__generic_list__dup_15, NULL, 719, 719, 13, 25},
  {entry__types__generic_list__dup_1, NULL, 719, 724, 3, 13},
  {entry__types__generic_list__interleave_6, NULL, 737, 737, 66, 80},
  {cont__types__generic_list__interleave_7, &frame__types__generic_list__interleave_6, 737, 737, 53, 80},
  {cont__types__generic_list__interleave_8, &frame__types__generic_list__interleave_6, 737, 737, 80, 80},
  {entry__types__generic_list__interleave_5, NULL, 737, 737, 22, 80},
  {entry__types__generic_list__interleave_14, NULL, 739, 739, 51, 65},
  {cont__types__generic_list__interleave_15, &frame__types__generic_list__interleave_14, 739, 739, 38, 65},
  {cont__types__generic_list__interleave_16, &frame__types__generic_list__interleave_14, 739, 739, 65, 65},
  {entry__types__generic_list__interleave_10, NULL, 739, 739, 8, 30},
  {cont__types__generic_list__interleave_11, &frame__types__generic_list__interleave_10, 739, 739, 8, 35},
  {cont__types__generic_list__interleave_12, &frame__types__generic_list__interleave_10, 739, 739, 8, 35},
  {cont__types__generic_list__interleave_13, &frame__types__generic_list__interleave_10, 739, 739, 5, 65},
  {entry__types__generic_list__interleave_1, NULL, 735, 735, 16, 23},
  {cont__types__generic_list__interleave_2, &frame__types__generic_list__interleave_1, 735, 735, 3, 24},
  {cont__types__generic_list__interleave_3, &frame__types__generic_list__interleave_1, 737, 737, 13, 15},
  {cont__types__generic_list__interleave_4, &frame__types__generic_list__interleave_1, 737, 737, 3, 80},
  {cont__types__generic_list__interleave_9, &frame__types__generic_list__interleave_1, 738, 739, 3, 65},
  {cont__types__generic_list__interleave_17, &frame__types__generic_list__interleave_1, 740, 740, 3, 11},
  {entry__types__generic_list__contains_4, NULL, 750, 750, 58, 68},
  {entry__types__generic_list__contains_2, NULL, 750, 750, 36, 55},
  {cont__types__generic_list__contains_3, &frame__types__generic_list__contains_2, 750, 750, 33, 68},
  {entry__types__generic_list__contains_1, NULL, 750, 750, 3, 68},
  {cont__types__generic_list__contains_5, &frame__types__generic_list__contains_1, 751, 751, 3, 10},
  {entry__std__sequence_6, NULL, 775, 775, 33, 55},
  {cont__std__sequence_7, &frame__std__sequence_6, 775, 775, 33, 55},
  {entry__std__sequence_9, NULL, 775, 775, 58, 68},
  {entry__std__sequence_4, NULL, 775, 775, 14, 28},
  {cont__std__sequence_5, &frame__std__sequence_4, 775, 775, 14, 55},
  {cont__std__sequence_8, &frame__std__sequence_4, 775, 775, 11, 68},
  {entry__std__sequence_3, NULL, 774, 775, 9, 68},
  {cont__std__sequence_10, &frame__std__sequence_3, 776, 776, 9, 16},
  {entry__std__sequence_1, NULL, 766, 766, 5, 16},
  {cont__std__sequence_2, &frame__std__sequence_1, 768, 776, 7, 18},
  {entry__96_4, NULL, 786, 786, 51, 51},
  {cont__96_5, &frame__96_4, 786, 786, 37, 52},
  {cont__96_6, &frame__96_4, 786, 786, 30, 63},
  {entry__96_11, NULL, 788, 788, 5, 67},
  {entry__96_17, NULL, 791, 791, 32, 38},
  {cont__96_18, &frame__96_17, 791, 791, 32, 48},
  {cont__96_19, &frame__96_17, 791, 791, 32, 48},
  {cont__96_20, &frame__96_17, 791, 791, 32, 48},
  {entry__96_22, NULL, 791, 791, 51, 65},
  {entry__96_27, NULL, 793, 793, 31, 45},
  {entry__96_14, NULL, 791, 791, 8, 22},
  {cont__96_15, &frame__96_14, 791, 791, 8, 27},
  {cont__96_16, &frame__96_14, 791, 791, 8, 48},
  {cont__96_21, &frame__96_14, 791, 791, 5, 65},
  {cont__96_23, &frame__96_14, 792, 792, 5, 59},
  {cont__96_24, &frame__96_14, 793, 793, 8, 28},
  {cont__96_25, &frame__96_14, 793, 793, 8, 28},
  {cont__96_26, &frame__96_14, 793, 793, 5, 45},
  {cont__96_28, &frame__96_14, 795, 795, 15, 44},
  {cont__96_29, &frame__96_14, 795, 795, 5, 44},
  {cont__96_30, &frame__96_14, 795, 795, 44, 44},
  {entry__96_1, NULL, 786, 786, 6, 27},
  {cont__96_3, &frame__96_1, 786, 786, 3, 63},
  {cont__96_7, &frame__96_1, 787, 787, 6, 12},
  {cont__96_8, &frame__96_1, 787, 787, 6, 22},
  {cont__96_9, &frame__96_1, 787, 787, 6, 22},
  {cont__96_10, &frame__96_1, 787, 788, 3, 67},
  {cont__96_13, &frame__96_1, 790, 795, 3, 44},
  {cont__96_31, &frame__96_1, 795, 795, 44, 44}
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  // 778: register_deserializer "list":
  // 779:   #
  // 780:     constructs a list from its serialized representation
  // 781:   (
  // 782:     $text
  // 783:     base_indent
  // 784:     -> return
  // 785:   )
  // 786:   if text .has_prefix. "()": return range(text 3 -1) empty_list
  // 787:   if text(1) != '@nl;':
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1a0aeb0b5df87d4d;
  arguments->slots[1] = func__96_1;
  result_count = 0;
  myself = get__register_deserializer();
  func = myself->type;
  frame->cont = cont__96_32;
}
static void entry__96_1(void) {
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
  // 786: ... text .has_prefix. "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = string__2d7981f4e6482bec;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__96_3;
}
static void cont__96_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 786: ... : return range(text 3 -1) empty_list
  frame->slots[5] /* temp__2 */ = create_closure(entry__96_4, 0);
  // 786: if text .has_prefix. "()": return range(text 3 -1) empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__96_7;
}
static void entry__96_4(void) {
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
  // 786: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__96_5;
}
static void cont__96_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 786: ... range(text 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__96_6;
}
static void cont__96_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 786: ... return range(text 3 -1) empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__empty_list();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__96_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 787: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__96_8;
}
static void cont__96_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 787: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__96_9;
}
static void cont__96_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 787: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__96_10;
}
static void cont__96_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 787: if text(1) != '@nl;':
  // 788:   raise "Invalid list object encountered during deserialisation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__96_11;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__96_13;
}
static void entry__96_11(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 788: raise "Invalid list object encountered during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b53819e78eec080a;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__96_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 789: $$obj empty_list
  ((CELL *)frame->slots[3])->contents /* obj */ = get__empty_list();
  // 790: ... :
  // 791:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 792:   get_deserialization_indent $remaining_text $indent text
  // 793:   if indent <= base_indent: return text obj
  // 794:   !text remaining_text
  // 795:   push &obj deserialize_item(&text indent)
  frame->slots[4] /* temp__1 */ = create_closure(entry__96_14, 0);
  // 790: forever:
  // 791:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 792:   get_deserialization_indent $remaining_text $indent text
  // 793:   if indent <= base_indent: return text obj
  // 794:   !text remaining_text
  // 795:   push &obj deserialize_item(&text indent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__96_31;
}
static void entry__96_14(void) {
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
  // 791: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__96_15;
}
static void cont__96_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 791: ... length_of(text) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__96_16;
}
static void cont__96_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 791: ... text(1) != '@nl;'
  frame->slots[9] /* temp__4 */ = create_closure(entry__96_17, 0);
  // 791: ... length_of(text) == 0 || text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__96_21;
}
static void entry__96_17(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 791: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__96_18;
}
static void cont__96_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 791: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__96_19;
}
static void cont__96_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 791: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__96_20;
}
static void cont__96_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 791: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__96_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 791: ... : return text obj
  frame->slots[10] /* temp__5 */ = create_closure(entry__96_22, 0);
  // 791: if length_of(text) == 0 || text(1) != '@nl;': return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__96_23;
}
static void entry__96_22(void) {
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
  // 791: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__96_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 792: get_deserialization_indent $remaining_text $indent text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 2;
  myself = get__get_deserialization_indent();
  func = myself->type;
  frame->cont = cont__96_24;
}
static void cont__96_24(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* remaining_text */, arguments->slots[0]);
  initialize_future(frame->slots[5] /* indent */, arguments->slots[1]);
  // 793: ... indent <= base_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base_indent */;
  arguments->slots[1] = frame->slots[5] /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__96_25;
}
static void cont__96_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 793: ... indent <= base_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__96_26;
}
static void cont__96_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 793: ... : return text obj
  frame->slots[8] /* temp__3 */ = create_closure(entry__96_27, 0);
  // 793: if indent <= base_indent: return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__96_28;
}
static void entry__96_27(void) {
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
  // 793: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__96_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 794: !text remaining_text
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[4] /* remaining_text */;
  // 795: ... deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[5] /* indent */;
  result_count = 2;
  myself = get__deserialize_item();
  func = myself->type;
  frame->cont = cont__96_29;
}
static void cont__96_29(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[6] /* temp__1 */ = arguments->slots[1];
  // 795: push &obj deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* obj */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__96_30;
}
static void cont__96_30(void) {
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
static void cont__96_31(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__96_32(void) {
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
static void entry__types__list__to_list_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 177: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__list_1(void) {
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
static void entry__types__list__length_of_1(void) {
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
static void entry__types__list__push_1(void) {
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
static void entry__types__list__drop_1(void) {
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
static void entry__types__list__pop_1(void) {
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
static void entry__types__list__peek_1(void) {
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
static void entry__types__list__append_1(void) {
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
static void entry__types__list__range_1(void) {
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
static void entry__types__generic_list__delete_at_1(void) {
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
  // 330: ... count != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* count */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_2;
}
static void cont__types__generic_list__delete_at_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 330: ... count != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_3;
}
static void cont__types__generic_list__delete_at_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 330: ... : !self append(range(self 1 idx-1) range(self idx+count -1))
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__generic_list__delete_at_4, 0);
  // 330: if count != 0: !self append(range(self 1 idx-1) range(self idx+count -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_11;
}
static void entry__types__generic_list__delete_at_4(void) {
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
  // 330: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_5;
}
static void cont__types__generic_list__delete_at_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 330: ... range(self 1 idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_6;
}
static void cont__types__generic_list__delete_at_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 330: ... idx+count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[2] /* count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_7;
}
static void cont__types__generic_list__delete_at_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 330: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_8;
}
static void cont__types__generic_list__delete_at_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 330: ... range(self idx+count -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  arguments->slots[2] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_9;
}
static void cont__types__generic_list__delete_at_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 330: ... !self append(range(self 1 idx-1) range(self idx+count -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__generic_list__delete_at_10;
}
static void cont__types__generic_list__delete_at_10(void) {
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
static void cont__types__generic_list__delete_at_11(void) {
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
static void entry__std__normalized_index_1(void) {
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
  // 341: idx >= 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__normalized_index_2;
}
static void cont__std__normalized_index_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 341: idx >= 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__normalized_index_3;
}
static void cont__std__normalized_index_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 341: ... :
  // 342:   return idx
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__normalized_index_4, 0);
  // 343: :
  // 344:   return length_of(self)+1+idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__normalized_index_5, 0);
  // 340: if
  // 341:   idx >= 0:
  // 342:     return idx
  // 343:   :
  // 344:     return length_of(self)+1+idx
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__normalized_index_9;
}
static void entry__std__normalized_index_4(void) {
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
  // 342: return idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__normalized_index_5(void) {
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
  // 344: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__normalized_index_6;
}
static void cont__std__normalized_index_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 344: ... length_of(self)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__normalized_index_7;
}
static void cont__std__normalized_index_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 344: ... length_of(self)+1+idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* idx */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__normalized_index_8;
}
static void cont__std__normalized_index_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 344: return length_of(self)+1+idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__normalized_index_9(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__is_empty_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 352: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__is_empty_2;
}
static void cont__types__generic_list__is_empty_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 352: ... length_of(self) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__is_empty_3;
}
static void cont__types__generic_list__is_empty_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 352: -> length_of(self) == 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_from_to_7(void) {
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
  // 380: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_8;
}
static void cont__types__generic_list__for_each_from_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 380: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_9;
}
static void cont__types__generic_list__for_each_from_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 380: ... :
  // 381:   body i self(i)
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_from_to_10, 0);
  // 382: :
  // 383:   body self(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_from_to_12, 0);
  // 379: if
  // 380:   parameter_count_of(body) == 2:
  // 381:     body i self(i)
  // 382:   :
  // 383:     body self(i)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_14;
}
static void entry__types__generic_list__for_each_from_to_10(void) {
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
  // 381: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_11;
}
static void cont__types__generic_list__for_each_from_to_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 381: body i self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__for_each_from_to_12(void) {
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
  // 383: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_13;
}
static void cont__types__generic_list__for_each_from_to_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 383: body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__for_each_from_to_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 384: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_15;
}
static void cont__types__generic_list__for_each_from_to_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 384: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_from_to_16, 0);
  // 384: ... body2.is_defined && i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_18;
}
static void entry__types__generic_list__for_each_from_to_16(void) {
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
  // 384: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_17;
}
static void cont__types__generic_list__for_each_from_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 384: ... i < n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_list__for_each_from_to_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 384: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_from_to_19, 0);
  // 384: if body2.is_defined && i < n: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_20;
}
static void entry__types__generic_list__for_each_from_to_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 384: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__for_each_from_to_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 385: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_21;
}
static void cont__types__generic_list__for_each_from_to_21(void) {
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
static void entry__types__generic_list__for_each_from_to_4(void) {
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
  // 378: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_5;
}
static void cont__types__generic_list__for_each_from_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 378: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_6;
}
static void cont__types__generic_list__for_each_from_to_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 378: ... :
  // 379:   if
  // 380:     parameter_count_of(body) == 2:
  // 381:       body i self(i)
  // 382:     :
  // 383:       body self(i)
  // 384:   if body2.is_defined && i < n: body2
  // 385:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_from_to_7, 0);
  // 378: ... -> i <= n:
  // 379:   if
  // 380:     parameter_count_of(body) == 2:
  // 381:       body i self(i)
  // 382:     :
  // 383:       body self(i)
  // 384:   if body2.is_defined && i < n: body2
  // 385:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_from_to_1(void) {
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
  // 376: $$i normalized_index(self first)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__normalized_index();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_2;
}
static void cont__types__generic_list__for_each_from_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* i */ = arguments->slots[0];
  // 377: $n normalized_index(self last)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* last */;
  result_count = 1;
  myself = get__normalized_index();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_to_3;
}
static void cont__types__generic_list__for_each_from_to_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* n */, arguments->slots[0]);
  // 378: ... -> i <= n:
  // 379:   if
  // 380:     parameter_count_of(body) == 2:
  // 381:       body i self(i)
  // 382:     :
  // 383:       body self(i)
  // 384:   if body2.is_defined && i < n: body2
  // 385:   plus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__types__generic_list__for_each_from_to_4, 0);
  // 378: while -> i <= n:
  // 379:   if
  // 380:     parameter_count_of(body) == 2:
  // 381:       body i self(i)
  // 382:     :
  // 383:       body self(i)
  // 384:   if body2.is_defined && i < n: body2
  // 385:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__for_each_from_down_to_7(void) {
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
  // 413: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_8;
}
static void cont__types__generic_list__for_each_from_down_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 413: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_9;
}
static void cont__types__generic_list__for_each_from_down_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 413: ... :
  // 414:   body i self(i)
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_from_down_to_10, 0);
  // 415: :
  // 416:   body self(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_from_down_to_12, 0);
  // 412: if
  // 413:   parameter_count_of(body) == 2:
  // 414:     body i self(i)
  // 415:   :
  // 416:     body self(i)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_14;
}
static void entry__types__generic_list__for_each_from_down_to_10(void) {
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
  // 414: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_11;
}
static void cont__types__generic_list__for_each_from_down_to_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 414: body i self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__for_each_from_down_to_12(void) {
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
  // 416: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_13;
}
static void cont__types__generic_list__for_each_from_down_to_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 416: body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__for_each_from_down_to_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 417: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_15;
}
static void cont__types__generic_list__for_each_from_down_to_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 417: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_from_down_to_16, 0);
  // 417: ... body2.is_defined && i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_18;
}
static void entry__types__generic_list__for_each_from_down_to_16(void) {
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
  // 417: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_17;
}
static void cont__types__generic_list__for_each_from_down_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 417: ... i < n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_list__for_each_from_down_to_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 417: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_from_down_to_19, 0);
  // 417: if body2.is_defined && i < n: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_20;
}
static void entry__types__generic_list__for_each_from_down_to_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 417: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__for_each_from_down_to_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 418: minus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_21;
}
static void cont__types__generic_list__for_each_from_down_to_21(void) {
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
static void entry__types__generic_list__for_each_from_down_to_4(void) {
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
  // 411: ... i >= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_5;
}
static void cont__types__generic_list__for_each_from_down_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 411: ... i >= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_6;
}
static void cont__types__generic_list__for_each_from_down_to_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 411: ... :
  // 412:   if
  // 413:     parameter_count_of(body) == 2:
  // 414:       body i self(i)
  // 415:     :
  // 416:       body self(i)
  // 417:   if body2.is_defined && i < n: body2
  // 418:   minus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_from_down_to_7, 0);
  // 411: ... -> i >= n:
  // 412:   if
  // 413:     parameter_count_of(body) == 2:
  // 414:       body i self(i)
  // 415:     :
  // 416:       body self(i)
  // 417:   if body2.is_defined && i < n: body2
  // 418:   minus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_from_down_to_1(void) {
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
  // 409: $$i normalized_index(self first)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__normalized_index();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_2;
}
static void cont__types__generic_list__for_each_from_down_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* i */ = arguments->slots[0];
  // 410: $n normalized_index(self last)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* last */;
  result_count = 1;
  myself = get__normalized_index();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_from_down_to_3;
}
static void cont__types__generic_list__for_each_from_down_to_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* n */, arguments->slots[0]);
  // 411: ... -> i >= n:
  // 412:   if
  // 413:     parameter_count_of(body) == 2:
  // 414:       body i self(i)
  // 415:     :
  // 416:       body self(i)
  // 417:   if body2.is_defined && i < n: body2
  // 418:   minus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__types__generic_list__for_each_from_down_to_4, 0);
  // 411: while -> i >= n:
  // 412:   if
  // 413:     parameter_count_of(body) == 2:
  // 414:       body i self(i)
  // 415:     :
  // 416:       body self(i)
  // 417:   if body2.is_defined && i < n: body2
  // 418:   minus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__for_each_23(void) {
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
  // 447: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_24;
}
static void cont__types__generic_list__for_each_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 447: body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_25;
}
static void cont__types__generic_list__for_each_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 448: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_26;
}
static void cont__types__generic_list__for_each_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 448: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_27, 0);
  // 448: ... body2.is_defined && i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_29;
}
static void entry__types__generic_list__for_each_27(void) {
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
  // 448: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_28;
}
static void cont__types__generic_list__for_each_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 448: ... i < n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_list__for_each_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 448: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_30, 0);
  // 448: if body2.is_defined && i < n: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_31;
}
static void entry__types__generic_list__for_each_30(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 448: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__for_each_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 449: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_32;
}
static void cont__types__generic_list__for_each_32(void) {
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
static void entry__types__generic_list__for_each_20(void) {
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
  // 446: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_21;
}
static void cont__types__generic_list__for_each_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 446: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_22;
}
static void cont__types__generic_list__for_each_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 446: ... :
  // 447:   body self(i)
  // 448:   if body2.is_defined && i < n: body2
  // 449:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_23, 0);
  // 446: ... -> i <= n:
  // 447:   body self(i)
  // 448:   if body2.is_defined && i < n: body2
  // 449:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_9(void) {
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
  // 442: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_10;
}
static void cont__types__generic_list__for_each_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 442: body i self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_11;
}
static void cont__types__generic_list__for_each_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 443: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_12;
}
static void cont__types__generic_list__for_each_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 443: ... i < n
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_13, 0);
  // 443: ... body2.is_defined && i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_15;
}
static void entry__types__generic_list__for_each_13(void) {
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
  // 443: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_14;
}
static void cont__types__generic_list__for_each_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 443: ... i < n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_list__for_each_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 443: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_16, 0);
  // 443: if body2.is_defined && i < n: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_17;
}
static void entry__types__generic_list__for_each_16(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 443: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__for_each_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 444: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_18;
}
static void cont__types__generic_list__for_each_18(void) {
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
static void entry__types__generic_list__for_each_6(void) {
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
  // 441: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_7;
}
static void cont__types__generic_list__for_each_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 441: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_8;
}
static void cont__types__generic_list__for_each_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 441: ... :
  // 442:   body i self(i)
  // 443:   if body2.is_defined && i < n: body2
  // 444:   plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_9, 0);
  // 441: ... -> i <= n:
  // 442:   body i self(i)
  // 443:   if body2.is_defined && i < n: body2
  // 444:   plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_5(void) {
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
  // 441: ... -> i <= n:
  // 442:   body i self(i)
  // 443:   if body2.is_defined && i < n: body2
  // 444:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__generic_list__for_each_6, 0);
  // 441: while -> i <= n:
  // 442:   body i self(i)
  // 443:   if body2.is_defined && i < n: body2
  // 444:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__for_each_19(void) {
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
  // 446: ... -> i <= n:
  // 447:   body self(i)
  // 448:   if body2.is_defined && i < n: body2
  // 449:   plus &i 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__generic_list__for_each_20, 0);
  // 446: while -> i <= n:
  // 447:   body self(i)
  // 448:   if body2.is_defined && i < n: body2
  // 449:   plus &i 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__for_each_1(void) {
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
  // 437: $$i 1
  ((CELL *)frame->slots[3])->contents /* i */ = number__1;
  // 438: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_2;
}
static void cont__types__generic_list__for_each_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* n */, arguments->slots[0]);
  // 440: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_3;
}
static void cont__types__generic_list__for_each_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 440: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_4;
}
static void cont__types__generic_list__for_each_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   while -> i <= n:
  // 442:     body i self(i)
  // 443:     if body2.is_defined && i < n: body2
  // 444:     plus &i 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_5, 0);
  // 445: :
  // 446:   while -> i <= n:
  // 447:     body self(i)
  // 448:     if body2.is_defined && i < n: body2
  // 449:     plus &i 1
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_19, 0);
  // 439: if
  // 440:   parameter_count_of(body) == 2:
  // 441:     while -> i <= n:
  // 442:       body i self(i)
  // 443:       if body2.is_defined && i < n: body2
  // 444:       plus &i 1
  // 445:   :
  // 446:     while -> i <= n:
  // 447:       body self(i)
  // 448:       if body2.is_defined && i < n: body2
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
static void entry__types__generic_list__for_each_downwards_23(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // body: 0
  // self: 1
  // n: 2
  // body2: 3
  // i: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[3]; /* self */
  frame->slots[2] = myself->closure.frame->slots[0]; /* n */
  frame->slots[3] = myself->closure.frame->slots[4]; /* body2 */
  frame->slots[4] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 478: ... self(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* n */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_24;
}
static void cont__types__generic_list__for_each_downwards_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 478: body self(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_25;
}
static void cont__types__generic_list__for_each_downwards_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 479: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_26;
}
static void cont__types__generic_list__for_each_downwards_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 479: ... n > i
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_downwards_27, 0);
  // 479: ... body2.is_defined && n > i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_29;
}
static void entry__types__generic_list__for_each_downwards_27(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // i: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* i */
  frame->slots[1] = myself->closure.frame->slots[2]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 479: ... n > i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_28;
}
static void cont__types__generic_list__for_each_downwards_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 479: ... n > i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_list__for_each_downwards_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 479: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_downwards_30, 0);
  // 479: if body2.is_defined && n > i: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_31;
}
static void entry__types__generic_list__for_each_downwards_30(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 479: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__for_each_downwards_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 480: minus &n 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_32;
}
static void cont__types__generic_list__for_each_downwards_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* n */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_downwards_20(void) {
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
  // 477: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* n */;
  arguments->slots[1] = frame->slots[1] /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_21;
}
static void cont__types__generic_list__for_each_downwards_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 477: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_22;
}
static void cont__types__generic_list__for_each_downwards_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 477: ... :
  // 478:   body self(n)
  // 479:   if body2.is_defined && n > i: body2
  // 480:   minus &n 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_downwards_23, 0);
  // 477: ... -> i <= n:
  // 478:   body self(n)
  // 479:   if body2.is_defined && n > i: body2
  // 480:   minus &n 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_downwards_9(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // body: 0
  // n: 1
  // self: 2
  // body2: 3
  // i: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* n */
  frame->slots[2] = myself->closure.frame->slots[3]; /* self */
  frame->slots[3] = myself->closure.frame->slots[4]; /* body2 */
  frame->slots[4] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 473: ... self(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* n */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_10;
}
static void cont__types__generic_list__for_each_downwards_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 473: body n self(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_11;
}
static void cont__types__generic_list__for_each_downwards_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 474: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_12;
}
static void cont__types__generic_list__for_each_downwards_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 474: ... n > i
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_downwards_13, 0);
  // 474: ... body2.is_defined && n > i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_15;
}
static void entry__types__generic_list__for_each_downwards_13(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // i: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* i */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 474: ... n > i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_14;
}
static void cont__types__generic_list__for_each_downwards_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 474: ... n > i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_list__for_each_downwards_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 474: ... : body2
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_downwards_16, 0);
  // 474: if body2.is_defined && n > i: body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_17;
}
static void entry__types__generic_list__for_each_downwards_16(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body2: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 474: ... body2
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__for_each_downwards_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 475: minus &n 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_18;
}
static void cont__types__generic_list__for_each_downwards_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* n */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_downwards_6(void) {
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
  // 472: ... n >= i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* n */;
  arguments->slots[1] = frame->slots[1] /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_7;
}
static void cont__types__generic_list__for_each_downwards_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 472: ... n >= i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_8;
}
static void cont__types__generic_list__for_each_downwards_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 472: ... :
  // 473:   body n self(n)
  // 474:   if body2.is_defined && n > i: body2
  // 475:   minus &n 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_downwards_9, 0);
  // 472: ... -> n >= i:
  // 473:   body n self(n)
  // 474:   if body2.is_defined && n > i: body2
  // 475:   minus &n 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__for_each_downwards_5(void) {
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
  // 472: ... -> n >= i:
  // 473:   body n self(n)
  // 474:   if body2.is_defined && n > i: body2
  // 475:   minus &n 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__generic_list__for_each_downwards_6, 0);
  // 472: while -> n >= i:
  // 473:   body n self(n)
  // 474:   if body2.is_defined && n > i: body2
  // 475:   minus &n 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__for_each_downwards_19(void) {
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
  // 477: ... -> i <= n:
  // 478:   body self(n)
  // 479:   if body2.is_defined && n > i: body2
  // 480:   minus &n 1
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__generic_list__for_each_downwards_20, 0);
  // 477: while -> i <= n:
  // 478:   body self(n)
  // 479:   if body2.is_defined && n > i: body2
  // 480:   minus &n 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__for_each_downwards_1(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // self: 0
  // body: 1
  // body2: 2
  // i: 3
  // n: 4
  // _define $i 1
  frame->slots[3] /* i */ = number__1;
  frame->slots[4] /* n */ = create_cell();
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
  // 469: $$n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_2;
}
static void cont__types__generic_list__for_each_downwards_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* n */ = arguments->slots[0];
  // 471: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_3;
}
static void cont__types__generic_list__for_each_downwards_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 471: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__for_each_downwards_4;
}
static void cont__types__generic_list__for_each_downwards_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 471: ... :
  // 472:   while -> n >= i:
  // 473:     body n self(n)
  // 474:     if body2.is_defined && n > i: body2
  // 475:     minus &n 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__for_each_downwards_5, 0);
  // 476: :
  // 477:   while -> i <= n:
  // 478:     body self(n)
  // 479:     if body2.is_defined && n > i: body2
  // 480:     minus &n 1
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__generic_list__for_each_downwards_19, 0);
  // 470: if
  // 471:   parameter_count_of(body) == 2:
  // 472:     while -> n >= i:
  // 473:       body n self(n)
  // 474:       if body2.is_defined && n > i: body2
  // 475:       minus &n 1
  // 476:   :
  // 477:     while -> i <= n:
  // 478:       body self(n)
  // 479:       if body2.is_defined && n > i: body2
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
static void entry__types__generic_list__update_each_1(void) {
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
  // 506: ... : (new_item)
  // 507:   if new_item.is_defined:
  // 508:     if
  // 509:       new_item.is_a_sequence:
  // 510:         append &new_list new_item
  // 511:       :
  // 512:         push &new_list new_item
  // 513:   plus &i 1
  frame->slots[7] /* temp__1 */ = create_closure(entry__types__generic_list__update_each_2, 1);
  // 506: $update_item: (new_item)
  // 507:   if new_item.is_defined:
  // 508:     if
  // 509:       new_item.is_a_sequence:
  // 510:         append &new_list new_item
  // 511:       :
  // 512:         push &new_list new_item
  // 513:   plus &i 1
  initialize_future(frame->slots[3] /* update_item */, frame->slots[7] /* temp__1 */);
  // 515: $$i 1
  ((CELL *)frame->slots[4])->contents /* i */ = number__1;
  // 516: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_12;
}
static void entry__types__generic_list__update_each_2(void) {
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
  // 507: ... new_item.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* new_item */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_3;
}
static void cont__types__generic_list__update_each_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 507: ... :
  // 508:   if
  // 509:     new_item.is_a_sequence:
  // 510:       append &new_list new_item
  // 511:     :
  // 512:       push &new_list new_item
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__generic_list__update_each_4, 0);
  // 507: if new_item.is_defined:
  // 508:   if
  // 509:     new_item.is_a_sequence:
  // 510:       append &new_list new_item
  // 511:     :
  // 512:       push &new_list new_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_10;
}
static void entry__types__generic_list__update_each_6(void) {
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
  // 510: append &new_list new_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_list */;
  arguments->slots[1] = frame->slots[1] /* new_item */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_7;
}
static void cont__types__generic_list__update_each_7(void) {
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
static void entry__types__generic_list__update_each_8(void) {
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
  // 512: push &new_list new_item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_list */;
  arguments->slots[1] = frame->slots[1] /* new_item */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_9;
}
static void cont__types__generic_list__update_each_9(void) {
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
static void entry__types__generic_list__update_each_4(void) {
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
  // 509: new_item.is_a_sequence
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* new_item */;
  result_count = 1;
  myself = get__is_a_sequence();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_5;
}
static void cont__types__generic_list__update_each_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 509: ... :
  // 510:   append &new_list new_item
  frame->slots[3] /* temp__2 */ = create_closure(entry__types__generic_list__update_each_6, 0);
  // 511: :
  // 512:   push &new_list new_item
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__generic_list__update_each_8, 0);
  // 508: if
  // 509:   new_item.is_a_sequence:
  // 510:     append &new_list new_item
  // 511:   :
  // 512:     push &new_list new_item
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
static void cont__types__generic_list__update_each_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 513: plus &i 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_11;
}
static void cont__types__generic_list__update_each_11(void) {
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
static void cont__types__generic_list__update_each_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* n */, arguments->slots[0]);
  // 517: $$new_list types::list
  ((CELL *)frame->slots[6])->contents /* new_list */ = var.types__list;
  // 519: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_13;
}
static void cont__types__generic_list__update_each_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 519: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_14;
}
static void cont__types__generic_list__update_each_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 519: ... :
  // 520:   while -> i <= n: update_item body(i self(i))
  frame->slots[9] /* temp__3 */ = create_closure(entry__types__generic_list__update_each_15, 0);
  // 521: :
  // 522:   while -> i <= n: update_item body(self(i))
  frame->slots[10] /* temp__4 */ = create_closure(entry__types__generic_list__update_each_22, 0);
  // 518: if
  // 519:   parameter_count_of(body) == 2:
  // 520:     while -> i <= n: update_item body(i self(i))
  // 521:   :
  // 522:     while -> i <= n: update_item body(self(i))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  arguments->slots[2] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_29;
}
static void entry__types__generic_list__update_each_26(void) {
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
  // 522: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  result_count = 1;
  myself = frame->slots[2] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_27;
}
static void cont__types__generic_list__update_each_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 522: ... body(self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_28;
}
static void cont__types__generic_list__update_each_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 522: ... update_item body(self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* update_item */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__update_each_23(void) {
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
  // 522: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_24;
}
static void cont__types__generic_list__update_each_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 522: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_25;
}
static void cont__types__generic_list__update_each_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 522: ... : update_item body(self(i))
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__update_each_26, 0);
  // 522: ... -> i <= n: update_item body(self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__update_each_19(void) {
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
  // 520: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[3] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_20;
}
static void cont__types__generic_list__update_each_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 520: ... body(i self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_21;
}
static void cont__types__generic_list__update_each_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 520: ... update_item body(i self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* update_item */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__update_each_16(void) {
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
  // 520: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_17;
}
static void cont__types__generic_list__update_each_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 520: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_18;
}
static void cont__types__generic_list__update_each_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 520: ... : update_item body(i self(i))
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__generic_list__update_each_19, 0);
  // 520: ... -> i <= n: update_item body(i self(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__update_each_15(void) {
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
  // 520: ... -> i <= n: update_item body(i self(i))
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__generic_list__update_each_16, 0);
  // 520: while -> i <= n: update_item body(i self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__update_each_22(void) {
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
  // 522: ... -> i <= n: update_item body(self(i))
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__generic_list__update_each_23, 0);
  // 522: while -> i <= n: update_item body(self(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__update_each_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 523: return new_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* new_list */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = cont__types__generic_list__update_each_30;
}
static void cont__types__generic_list__update_each_30(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__list__for_each_pair_13(void) {
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
  // 541: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_14;
}
static void cont__types__list__for_each_pair_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 541: ... body self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__list__for_each_pair_1(void) {
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
  // 536: $$i 1
  ((CELL *)frame->slots[2])->contents /* i */ = number__1;
  // 537: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_2;
}
static void cont__types__list__for_each_pair_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 538: ... -> i < n:
  // 539:   body self(i) self(i+1)
  // 540:   plus &i 2
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__list__for_each_pair_3, 0);
  // 538: while -> i < n:
  // 539:   body self(i) self(i+1)
  // 540:   plus &i 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_11;
}
static void entry__types__list__for_each_pair_5(void) {
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
  // 539: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_6;
}
static void cont__types__list__for_each_pair_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 539: ... i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_7;
}
static void cont__types__list__for_each_pair_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 539: ... self(i+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_8;
}
static void cont__types__list__for_each_pair_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 539: body self(i) self(i+1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_9;
}
static void cont__types__list__for_each_pair_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 540: plus &i 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_10;
}
static void cont__types__list__for_each_pair_10(void) {
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
static void entry__types__list__for_each_pair_3(void) {
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
  // 538: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_4;
}
static void cont__types__list__for_each_pair_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 538: ... :
  // 539:   body self(i) self(i+1)
  // 540:   plus &i 2
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__list__for_each_pair_5, 0);
  // 538: ... -> i < n:
  // 539:   body self(i) self(i+1)
  // 540:   plus &i 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__list__for_each_pair_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 541: ... is_odd(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__types__list__for_each_pair_12;
}
static void cont__types__list__for_each_pair_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 541: ... : body self(i)
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__list__for_each_pair_13, 0);
  // 541: if is_odd(n): body self(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__get_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 549: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__get_2;
}
static void cont__types__generic_list__get_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 549: ... length_of(self) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__get_3;
}
static void cont__types__generic_list__get_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 549: if length_of(self) == 0: raise "Attempt to get an element from an empty list!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__types__generic_list__get_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__get_6;
}
static void entry__types__generic_list__get_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 549: ... raise "Attempt to get an element from an empty list!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__57ec57a17085427f;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__get_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 550: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__generic_list__get_7;
}
static void cont__types__generic_list__get_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 550: ... range(self 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__generic_list__get_8;
}
static void cont__types__generic_list__get_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 550: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__types__generic_list__get_9;
}
static void cont__types__generic_list__get_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 550: -> range(self 2 -1) self(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__list__put_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // item: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 559: ... list(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__types__list__put_2;
}
static void cont__types__list__put_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 559: ... append(list(item) self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__list__put_3;
}
static void cont__types__list__put_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 559: -> append(list(item) self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__list__merge_1(void) {
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
  // 570: $$result list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__types__list__merge_2;
}
static void cont__types__list__merge_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* result */ = arguments->slots[0];
  // 571: ... :
  // 572:   if
  // 573:     length_of(left) > 0:
  // 574:       if
  // 575:         length_of(right) > 0:
  // 576:           if
  // 577:             ||
  // 578:               func.is_undefined && left(1) <= right(1)
  // 579:               func.is_defined && not(func(right(1) left(1)))
  // 580:             :
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__list__merge_3, 0);
  // 571: forever:
  // 572:   if
  // 573:     length_of(left) > 0:
  // 574:       if
  // 575:         length_of(right) > 0:
  // 576:           if
  // 577:             ||
  // 578:               func.is_undefined && left(1) <= right(1)
  // 579:               func.is_defined && not(func(right(1) left(1)))
  // 580:             :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__list__merge_36;
}
static void entry__types__list__merge_26(void) {
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
  // 581: ... get(&left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* left */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__types__list__merge_27;
}
static void cont__types__list__merge_27(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* left */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 581: push &result get(&left)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__list__merge_28;
}
static void cont__types__list__merge_28(void) {
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
static void entry__types__list__merge_29(void) {
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
  // 583: ... get(&right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* right */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__types__list__merge_30;
}
static void cont__types__list__merge_30(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* right */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 583: push &result get(&right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__list__merge_31;
}
static void cont__types__list__merge_31(void) {
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
static void entry__types__list__merge_9(void) {
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
  // 578: func.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__types__list__merge_10;
}
static void cont__types__list__merge_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 578: ... left(1) <= right(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__list__merge_11, 0);
  // 578: func.is_undefined && left(1) <= right(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__list__merge_16;
}
static void entry__types__list__merge_11(void) {
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
  // 578: ... right(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* right */;
  func = myself->type;
  frame->cont = cont__types__list__merge_12;
}
static void cont__types__list__merge_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 578: ... left(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* left */;
  func = myself->type;
  frame->cont = cont__types__list__merge_13;
}
static void cont__types__list__merge_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 578: ... left(1) <= right(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__list__merge_14;
}
static void cont__types__list__merge_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 578: ... left(1) <= right(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__list__merge_15;
}
static void cont__types__list__merge_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 578: ... left(1) <= right(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__list__merge_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 579: func.is_defined && not(func(right(1) left(1)))
  frame->slots[8] /* temp__5 */ = create_closure(entry__types__list__merge_17, 0);
  // 577: ||
  // 578:   func.is_undefined && left(1) <= right(1)
  // 579:   func.is_defined && not(func(right(1) left(1)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__list__merge_25;
}
static void entry__types__list__merge_17(void) {
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
  // 579: func.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__list__merge_18;
}
static void cont__types__list__merge_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 579: ... not(func(right(1) left(1)))
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__list__merge_19, 0);
  // 579: func.is_defined && not(func(right(1) left(1)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__list__merge_24;
}
static void entry__types__list__merge_19(void) {
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
  // 579: ... right(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* right */;
  func = myself->type;
  frame->cont = cont__types__list__merge_20;
}
static void cont__types__list__merge_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 579: ... left(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* left */;
  func = myself->type;
  frame->cont = cont__types__list__merge_21;
}
static void cont__types__list__merge_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 579: ... func(right(1) left(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__types__list__merge_22;
}
static void cont__types__list__merge_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 579: ... not(func(right(1) left(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__types__list__merge_23;
}
static void cont__types__list__merge_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 579: ... not(func(right(1) left(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__list__merge_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 579: func.is_defined && not(func(right(1) left(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__list__merge_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 580: :
  // 581:   push &result get(&left)
  frame->slots[9] /* temp__6 */ = create_closure(entry__types__list__merge_26, 0);
  // 582: :
  // 583:   push &result get(&right)
  frame->slots[10] /* temp__7 */ = create_closure(entry__types__list__merge_29, 0);
  // 576: if
  // 577:   ||
  // 578:     func.is_undefined && left(1) <= right(1)
  // 579:     func.is_defined && not(func(right(1) left(1)))
  // 580:   :
  // 581:     push &result get(&left)
  // 582:   :
  // 583:     push &result get(&right)
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
static void entry__types__list__merge_32(void) {
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
  // 585: ... append(result left)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* left */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__list__merge_33;
}
static void cont__types__list__merge_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 585: return append(result left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__list__merge_6(void) {
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
  // 575: length_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__list__merge_7;
}
static void cont__types__list__merge_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 575: length_of(right) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__list__merge_8;
}
static void cont__types__list__merge_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 575: ... :
  // 576:   if
  // 577:     ||
  // 578:       func.is_undefined && left(1) <= right(1)
  // 579:       func.is_defined && not(func(right(1) left(1)))
  // 580:     :
  // 581:       push &result get(&left)
  // 582:     :
  // 583:       push &result get(&right)
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__list__merge_9, 0);
  // 584: :
  // 585:   return append(result left)
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__list__merge_32, 0);
  // 574: if
  // 575:   length_of(right) > 0:
  // 576:     if
  // 577:       ||
  // 578:         func.is_undefined && left(1) <= right(1)
  // 579:         func.is_defined && not(func(right(1) left(1)))
  // 580:       :
  // 581:         push &result get(&left)
  // 582:       :
  // 583:         push &result get(&right)
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
static void entry__types__list__merge_34(void) {
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
  // 587: ... append(result right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* right */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__list__merge_35;
}
static void cont__types__list__merge_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 587: return append(result right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__list__merge_3(void) {
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
  // 573: length_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__list__merge_4;
}
static void cont__types__list__merge_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 573: length_of(left) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__list__merge_5;
}
static void cont__types__list__merge_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 573: ... :
  // 574:   if
  // 575:     length_of(right) > 0:
  // 576:       if
  // 577:         ||
  // 578:           func.is_undefined && left(1) <= right(1)
  // 579:           func.is_defined && not(func(right(1) left(1)))
  // 580:         :
  // 581:           push &result get(&left)
  // 582:         :
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__list__merge_6, 0);
  // 586: :
  // 587:   return append(result right)
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__list__merge_34, 0);
  // 572: if
  // 573:   length_of(left) > 0:
  // 574:     if
  // 575:       length_of(right) > 0:
  // 576:         if
  // 577:           ||
  // 578:             func.is_undefined && left(1) <= right(1)
  // 579:             func.is_defined && not(func(right(1) left(1)))
  // 580:           :
  // 581:             push &result get(&left)
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
static void cont__types__list__merge_36(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__list__serialize_1(void) {
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
  // 597: ... self.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__types__list__serialize_2;
}
static void cont__types__list__serialize_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 597: ... : return "list()"
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__list__serialize_3, 0);
  // 597: if self.is_empty: return "list()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__list__serialize_5;
}
static void entry__types__list__serialize_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 597: ... return "list()"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7e1f534683fac2fe;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__list__serialize_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 598: $$buf "list"
  ((CELL *)frame->slots[3])->contents /* buf */ = string__1a0aeb0b5df87d4d;
  // 599: ... : (item)
  // 600:   write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__list__serialize_7, 1);
  // 599: for_each self: (item)
  // 600:   write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__list__serialize_13;
}
static void entry__types__list__serialize_7(void) {
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
  // 600: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__list__serialize_8;
}
static void cont__types__list__serialize_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 600: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__types__list__serialize_9;
}
static void cont__types__list__serialize_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 600: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__list__serialize_10;
}
static void cont__types__list__serialize_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 600: ... serialize(item indent+2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__types__list__serialize_11;
}
static void cont__types__list__serialize_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 600: write_to &buf '@nl;' spaces(indent+2) serialize(item indent+2)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = character__10;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__types__list__serialize_12;
}
static void cont__types__list__serialize_12(void) {
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
static void cont__types__list__serialize_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 601: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__list__sort_1(void) {
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
  // 614: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__list__sort_2;
}
static void cont__types__list__sort_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 616: 0, 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = var.std__sequence;
  func = myself->type;
  frame->cont = cont__types__list__sort_3;
}
static void cont__types__list__sort_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 616: ... :
  // 617:   return self
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__list__sort_4, 0);
  // 618: ... :
  // 619:   if
  // 620:     ||
  // 621:       func.is_undefined && self(1) <= self(2)
  // 622:       func.is_defined && not(func(self(2) self(1)))
  // 623:     :
  // 624:       return self
  // 625:     :
  // 626:       return list(self(2) self(1))
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__list__sort_5, 0);
  // 627: :
  // 628:   $m n .div. 2
  // 629:   if
  // 630:     func.is_undefined:
  // 631:       return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  // 632:     :
  // 633:       return
  // 634:         merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__list__sort_27, 0);
  // 615: case n
  // 616:   0, 1:
  // 617:     return self
  // 618:   2:
  // 619:     if
  // 620:       ||
  // 621:         func.is_undefined && self(1) <= self(2)
  // 622:         func.is_defined && not(func(self(2) self(1)))
  // 623:       :
  // 624:         return self
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
  frame->cont = cont__types__list__sort_44;
}
static void entry__types__list__sort_30(void) {
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
  // 631: ... range(self 1 m)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__list__sort_31;
}
static void cont__types__list__sort_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 631: ... sort(range(self 1 m))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__types__list__sort_32;
}
static void cont__types__list__sort_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 631: ... m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* m */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__list__sort_33;
}
static void cont__types__list__sort_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 631: ... range(self m+1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  arguments->slots[2] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__list__sort_34;
}
static void cont__types__list__sort_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 631: ... sort(range(self m+1 n))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__types__list__sort_35;
}
static void cont__types__list__sort_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 631: ... merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__merge();
  func = myself->type;
  frame->cont = cont__types__list__sort_36;
}
static void cont__types__list__sort_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 631: return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__list__sort_37(void) {
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
  // 634: ... range(self 1 m)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* m */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__list__sort_38;
}
static void cont__types__list__sort_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 634: ... sort(range(self 1 m) func)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[3] /* func */;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__types__list__sort_39;
}
static void cont__types__list__sort_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 634: ... m+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* m */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__list__sort_40;
}
static void cont__types__list__sort_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 634: ... range(self m+1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[10] /* temp__6 */;
  arguments->slots[2] = frame->slots[4] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__list__sort_41;
}
static void cont__types__list__sort_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 634: ... sort(range(self m+1 n) func)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__5 */;
  arguments->slots[1] = frame->slots[3] /* func */;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__types__list__sort_42;
}
static void cont__types__list__sort_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 634: merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = frame->slots[3] /* func */;
  result_count = 1;
  myself = get__merge();
  func = myself->type;
  frame->cont = cont__types__list__sort_43;
}
static void cont__types__list__sort_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 633: return
  // 634:   merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__list__sort_22(void) {
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
  // 624: return self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__list__sort_23(void) {
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
  // 626: ... self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__sort_24;
}
static void cont__types__list__sort_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 626: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__sort_25;
}
static void cont__types__list__sort_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 626: ... list(self(2) self(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__types__list__sort_26;
}
static void cont__types__list__sort_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 626: return list(self(2) self(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__list__sort_4(void) {
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
  // 617: return self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__list__sort_5(void) {
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
  // 621: func.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__types__list__sort_6;
}
static void cont__types__list__sort_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 621: ... self(1) <= self(2)
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__list__sort_7, 0);
  // 621: func.is_undefined && self(1) <= self(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__list__sort_12;
}
static void entry__types__list__sort_7(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 621: ... self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__sort_8;
}
static void cont__types__list__sort_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 621: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__sort_9;
}
static void cont__types__list__sort_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 621: ... self(1) <= self(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__list__sort_10;
}
static void cont__types__list__sort_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 621: ... self(1) <= self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__list__sort_11;
}
static void cont__types__list__sort_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 621: ... self(1) <= self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__list__sort_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 622: func.is_defined && not(func(self(2) self(1)))
  frame->slots[7] /* temp__5 */ = create_closure(entry__types__list__sort_13, 0);
  // 620: ||
  // 621:   func.is_undefined && self(1) <= self(2)
  // 622:   func.is_defined && not(func(self(2) self(1)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__list__sort_21;
}
static void entry__types__list__sort_13(void) {
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
  // 622: func.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__list__sort_14;
}
static void cont__types__list__sort_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 622: ... not(func(self(2) self(1)))
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__list__sort_15, 0);
  // 622: func.is_defined && not(func(self(2) self(1)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__list__sort_20;
}
static void entry__types__list__sort_15(void) {
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
  // 622: ... self(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__sort_16;
}
static void cont__types__list__sort_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 622: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* self */;
  func = myself->type;
  frame->cont = cont__types__list__sort_17;
}
static void cont__types__list__sort_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 622: ... func(self(2) self(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__types__list__sort_18;
}
static void cont__types__list__sort_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 622: ... not(func(self(2) self(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__types__list__sort_19;
}
static void cont__types__list__sort_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 622: ... not(func(self(2) self(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__list__sort_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 622: func.is_defined && not(func(self(2) self(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__list__sort_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 623: :
  // 624:   return self
  frame->slots[8] /* temp__6 */ = create_closure(entry__types__list__sort_22, 0);
  // 625: :
  // 626:   return list(self(2) self(1))
  frame->slots[9] /* temp__7 */ = create_closure(entry__types__list__sort_23, 0);
  // 619: if
  // 620:   ||
  // 621:     func.is_undefined && self(1) <= self(2)
  // 622:     func.is_defined && not(func(self(2) self(1)))
  // 623:   :
  // 624:     return self
  // 625:   :
  // 626:     return list(self(2) self(1))
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
static void entry__types__list__sort_27(void) {
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
  // 628: $m n .div. 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__types__list__sort_28;
}
static void cont__types__list__sort_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* m */, arguments->slots[0]);
  // 630: func.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* func */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__types__list__sort_29;
}
static void cont__types__list__sort_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 630: ... :
  // 631:   return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__list__sort_30, 0);
  // 632: :
  // 633:   return
  // 634:     merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__list__sort_37, 0);
  // 629: if
  // 630:   func.is_undefined:
  // 631:     return merge(sort(range(self 1 m)) sort(range(self m+1 n)))
  // 632:   :
  // 633:     return
  // 634:       merge(sort(range(self 1 m) func) sort(range(self m+1 n) func) func)
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
static void cont__types__list__sort_44(void) {
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
static void entry__types__list__new_empty_collection_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 671: -> types::list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__list;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__equal_1(void) {
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
  // 683: ... right.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_2;
}
static void cont__types__generic_list__equal_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 683: ... right.is_a_list
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__generic_list__equal_3, 0);
  // 683: ... right.is_defined && right.is_a_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_5;
}
static void entry__types__generic_list__equal_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // right: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 683: ... right.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* right */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_4;
}
static void cont__types__generic_list__equal_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 683: ... right.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_list__equal_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 683: ... : return false
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__generic_list__equal_6, 0);
  // 683: unless right.is_defined && right.is_a_list: return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_7;
}
static void entry__types__generic_list__equal_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 683: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__equal_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 684: ... length_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_8;
}
static void cont__types__generic_list__equal_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 684: ... length_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_9;
}
static void cont__types__generic_list__equal_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 684: ... length_of(left) != length_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_10;
}
static void cont__types__generic_list__equal_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 684: ... length_of(left) != length_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_11;
}
static void cont__types__generic_list__equal_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 684: ... : return false
  frame->slots[7] /* temp__5 */ = create_closure(entry__types__generic_list__equal_12, 0);
  // 684: if length_of(left) != length_of(right): return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_13;
}
static void entry__types__generic_list__equal_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 684: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__equal_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 685: ... : (idx item) if item != right(idx): return false
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__generic_list__equal_14, 2);
  // 685: for_each left: (idx item) if item != right(idx): return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_19;
}
static void entry__types__generic_list__equal_18(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 685: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__equal_14(void) {
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
  // 685: ... right(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = frame->slots[2] /* right */;
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_15;
}
static void cont__types__generic_list__equal_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 685: ... item != right(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_16;
}
static void cont__types__generic_list__equal_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 685: ... item != right(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__equal_17;
}
static void cont__types__generic_list__equal_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 685: ... : return false
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__generic_list__equal_18, 0);
  // 685: ... if item != right(idx): return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__equal_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 686: -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__filter_1(void) {
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
  // 695: $$new_list new_empty_collection(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__new_empty_collection();
  func = myself->type;
  frame->cont = cont__types__generic_list__filter_2;
}
static void cont__types__generic_list__filter_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* new_list */ = arguments->slots[0];
  // 696: ... : (item) if test(item): push &new_list item
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__generic_list__filter_3, 1);
  // 696: for_each self: (item) if test(item): push &new_list item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__generic_list__filter_7;
}
static void entry__types__generic_list__filter_5(void) {
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
  // 696: ... push &new_list item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_list */;
  arguments->slots[1] = frame->slots[1] /* item */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__generic_list__filter_6;
}
static void cont__types__generic_list__filter_6(void) {
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
static void entry__types__generic_list__filter_3(void) {
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
  // 696: ... test(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[1] /* test */;
  func = myself->type;
  frame->cont = cont__types__generic_list__filter_4;
}
static void cont__types__generic_list__filter_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 696: ... : push &new_list item
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__generic_list__filter_5, 0);
  // 696: ... if test(item): push &new_list item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__filter_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 697: -> new_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_list */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__map_1(void) {
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
  // 708: $$new_list new_empty_collection(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__new_empty_collection();
  func = myself->type;
  frame->cont = cont__types__generic_list__map_2;
}
static void cont__types__generic_list__map_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* new_list */ = arguments->slots[0];
  // 709: ... : (item) push &new_list func(item)
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__generic_list__map_3, 1);
  // 709: for_each self: (item) push &new_list func(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__generic_list__map_6;
}
static void entry__types__generic_list__map_3(void) {
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
  // 709: ... func(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[2] /* func */;
  func = myself->type;
  frame->cont = cont__types__generic_list__map_4;
}
static void cont__types__generic_list__map_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 709: ... push &new_list func(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_list */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__generic_list__map_5;
}
static void cont__types__generic_list__map_5(void) {
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
static void cont__types__generic_list__map_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 710: -> new_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_list */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__dup_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: ... -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__dup_3(void) {
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
  // 720: ... n < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__dup_4;
}
static void cont__types__generic_list__dup_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 720: if n < 0: raise "Negative argument for dup!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__types__generic_list__dup_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__dup_7;
}
static void entry__types__generic_list__dup_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 720: ... raise "Negative argument for dup!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__963fa2c6021831d1;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__dup_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 721: ... n .div. 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__types__generic_list__dup_8;
}
static void cont__types__generic_list__dup_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 721: $$result dup(self n .div. 2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__types__generic_list__dup_9;
}
static void cont__types__generic_list__dup_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  // 722: append &result result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* result */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__generic_list__dup_10;
}
static void cont__types__generic_list__dup_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  // 723: ... n.is_odd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__types__generic_list__dup_11;
}
static void cont__types__generic_list__dup_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 723: ... : append &result self
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__generic_list__dup_12, 0);
  // 723: if n.is_odd: append &result self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_list__dup_14;
}
static void entry__types__generic_list__dup_12(void) {
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
  // 723: ... append &result self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[1] /* self */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__generic_list__dup_13;
}
static void cont__types__generic_list__dup_13(void) {
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
static void cont__types__generic_list__dup_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 724: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__dup_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: ... -> empty_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__dup_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // n: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 719: ... -> self
  frame->slots[2] /* temp__1 */ = create_closure(entry__types__generic_list__dup_2, 0);
  // 719: ... :
  // 720:   if n < 0: raise "Negative argument for dup!"
  // 721:   $$result dup(self n .div. 2)
  // 722:   append &result result
  // 723:   if n.is_odd: append &result self
  // 724:   -> result
  frame->slots[3] /* temp__2 */ = create_closure(entry__types__generic_list__dup_3, 0);
  // 719: case n 0 (-> empty_list) 1 (-> self):
  // 720:   if n < 0: raise "Negative argument for dup!"
  // 721:   $$result dup(self n .div. 2)
  // 722:   append &result result
  // 723:   if n.is_odd: append &result self
  // 724:   -> result
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = func__types__generic_list__dup_15;
  arguments->slots[3] = number__1;
  arguments->slots[4] = frame->slots[2] /* temp__1 */;
  arguments->slots[5] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__interleave_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // lists: 0
  // n: 1
  // result: 2
  frame->slots[1] /* n */ = create_future();
  frame->slots[2] /* result */ = create_cell();
  frame->slots[0] /* lists */ = from_arguments(0, argument_count-0);
  // 735: ... lists(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* lists */;
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_2;
}
static void cont__types__generic_list__interleave_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 735: $n length_of(lists(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_3;
}
static void cont__types__generic_list__interleave_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* n */, arguments->slots[0]);
  // 736: $$result empty_list
  ((CELL *)frame->slots[2])->contents /* result */ = get__empty_list();
  // 737: ... n-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_4;
}
static void cont__types__generic_list__interleave_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 737: ... : (i) for_each lists: (current_list) push &result current_list(i)
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__generic_list__interleave_5, 1);
  // 737: from_to 1 n-1: (i) for_each lists: (current_list) push &result current_list(i)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_9;
}
static void entry__types__generic_list__interleave_6(void) {
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
  // 737: ... current_list(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  result_count = 1;
  myself = frame->slots[0] /* current_list */;
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_7;
}
static void cont__types__generic_list__interleave_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 737: ... push &result current_list(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_8;
}
static void cont__types__generic_list__interleave_8(void) {
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
static void entry__types__generic_list__interleave_5(void) {
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
  // 737: ... : (current_list) push &result current_list(i)
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__generic_list__interleave_6, 1);
  // 737: ... for_each lists: (current_list) push &result current_list(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* lists */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__interleave_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 738: ... : (current_list)
  // 739:   if length_of(current_list) >= n: push &result current_list(n)
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__generic_list__interleave_10, 1);
  // 738: for_each lists: (current_list)
  // 739:   if length_of(current_list) >= n: push &result current_list(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lists */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_17;
}
static void entry__types__generic_list__interleave_14(void) {
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
  // 739: ... current_list(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  result_count = 1;
  myself = frame->slots[1] /* current_list */;
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_15;
}
static void cont__types__generic_list__interleave_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 739: ... push &result current_list(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_16;
}
static void cont__types__generic_list__interleave_16(void) {
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
static void entry__types__generic_list__interleave_10(void) {
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
  // 739: ... length_of(current_list)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* current_list */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_11;
}
static void cont__types__generic_list__interleave_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 739: ... length_of(current_list) >= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_12;
}
static void cont__types__generic_list__interleave_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 739: ... length_of(current_list) >= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__generic_list__interleave_13;
}
static void cont__types__generic_list__interleave_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 739: ... : push &result current_list(n)
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__generic_list__interleave_14, 0);
  // 739: if length_of(current_list) >= n: push &result current_list(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__interleave_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 740: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_list__contains_1(void) {
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
  // 750: ... : (current_item) if current_item == item: return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__generic_list__contains_2, 1);
  // 750: for_each self: (current_item) if current_item == item: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__generic_list__contains_5;
}
static void entry__types__generic_list__contains_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 750: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__generic_list__contains_2(void) {
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
  // 750: ... current_item == item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* current_item */;
  arguments->slots[1] = frame->slots[1] /* item */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_list__contains_3;
}
static void cont__types__generic_list__contains_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 750: ... : return true
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__generic_list__contains_4, 0);
  // 750: ... if current_item == item: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_list__contains_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 751: -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__sequence_3(void) {
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
  // 774: ... : (item)
  // 775:   if item == element || item .contains. element: return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__sequence_4, 1);
  // 774: for_each self: (item)
  // 775:   if item == element || item .contains. element: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__sequence_10;
}
static void entry__std__sequence_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 775: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__sequence_4(void) {
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
  // 775: ... item == element
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  arguments->slots[1] = frame->slots[1] /* element */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__sequence_5;
}
static void cont__std__sequence_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 775: ... item .contains. element
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__sequence_6, 0);
  // 775: ... item == element || item .contains. element
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__sequence_8;
}
static void entry__std__sequence_6(void) {
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
  // 775: ... item .contains. element
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  arguments->slots[1] = frame->slots[1] /* element */;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__std__sequence_7;
}
static void cont__std__sequence_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 775: ... item .contains. element
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__sequence_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 775: ... : return true
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__sequence_9, 0);
  // 775: if item == element || item .contains. element: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__sequence_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 776: -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__sequence_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // items: 0
  frame->slots[0] /* items */ = from_arguments(0, argument_count-0);
  // 766: list(items*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* items */);
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__std__sequence_2;
}
static void cont__std__sequence_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_sequence, get__true());
    set_attribute(temp->attributes, poly_idx__contains, func__std__sequence_3);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 768: /contains:
  // 769:   (
  // 770:     self
  // 771:     element
  // 772:     -> return
  // 773:   )
  // 774:   for_each self: (item)
  // 775:     if item == element || item .contains. element: return true
  // 776:   -> false
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
  define_c_function("from_arguments", runtime__from_arguments);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__list(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__list");
  character__10 = from_uchar32(10);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  define_polymorphic_function("std", "is_a_list", get__std__is_a_list, &poly_idx__std__is_a_list, &var.std__is_a_list);
  func__types__list__to_list_1 = create_function(entry__types__list__to_list_1, 1);
  func__std__list_1 = create_function(entry__std__list_1, -1);
  func__types__list__length_of_1 = create_function(entry__types__list__length_of_1, 1);
  func__types__list__push_1 = create_function(entry__types__list__push_1, 2);
  func__types__list__drop_1 = create_function(entry__types__list__drop_1, 1);
  func__types__list__pop_1 = create_function(entry__types__list__pop_1, 1);
  func__types__list__peek_1 = create_function(entry__types__list__peek_1, 1);
  func__types__list__append_1 = create_function(entry__types__list__append_1, 2);
  func__types__list__range_1 = create_function(entry__types__list__range_1, 3);
  func__types__generic_list__delete_at_1 = create_function(entry__types__generic_list__delete_at_1, -1);
  func__std__normalized_index_1 = create_function(entry__std__normalized_index_1, 2);
  func__types__generic_list__is_empty_1 = create_function(entry__types__generic_list__is_empty_1, 1);
  func__types__generic_list__for_each_from_to_1 = create_function(entry__types__generic_list__for_each_from_to_1, -1);
  func__types__generic_list__for_each_from_down_to_1 = create_function(entry__types__generic_list__for_each_from_down_to_1, -1);
  func__types__generic_list__for_each_1 = create_function(entry__types__generic_list__for_each_1, -1);
  func__types__generic_list__for_each_downwards_1 = create_function(entry__types__generic_list__for_each_downwards_1, -1);
  func__types__generic_list__update_each_1 = create_function(entry__types__generic_list__update_each_1, 2);
  func__types__list__for_each_pair_1 = create_function(entry__types__list__for_each_pair_1, 2);
  string__57ec57a17085427f = from_latin_1_string("Attempt to get an element from an empty list!", 45);
  func__types__generic_list__get_4 = create_function(entry__types__generic_list__get_4, 0);
  func__types__generic_list__get_1 = create_function(entry__types__generic_list__get_1, 1);
  func__types__list__put_1 = create_function(entry__types__list__put_1, 2);
  func__types__list__merge_1 = create_function(entry__types__list__merge_1, -1);
  string__7e1f534683fac2fe = from_latin_1_string("list()", 6);
  string__1a0aeb0b5df87d4d = from_latin_1_string("list", 4);
  func__types__list__serialize_1 = create_function(entry__types__list__serialize_1, -1);
  func__types__list__sort_1 = create_function(entry__types__list__sort_1, -1);
  func__types__list__new_empty_collection_1 = create_function(entry__types__list__new_empty_collection_1, 1);
  func__types__generic_list__equal_1 = create_function(entry__types__generic_list__equal_1, 2);
  func__types__generic_list__filter_1 = create_function(entry__types__generic_list__filter_1, 2);
  func__types__generic_list__map_1 = create_function(entry__types__generic_list__map_1, 2);
  string__963fa2c6021831d1 = from_latin_1_string("Negative argument for dup!", 26);
  func__types__generic_list__dup_5 = create_function(entry__types__generic_list__dup_5, 0);
  func__types__generic_list__dup_15 = create_function(entry__types__generic_list__dup_15, 0);
  func__types__generic_list__dup_1 = create_function(entry__types__generic_list__dup_1, 2);
  func__types__generic_list__interleave_1 = create_function(entry__types__generic_list__interleave_1, -1);
  func__types__generic_list__contains_1 = create_function(entry__types__generic_list__contains_1, 2);
  define_polymorphic_function("std", "is_a_sequence", get__std__is_a_sequence, &poly_idx__std__is_a_sequence, &var.std__is_a_sequence);
  func__std__sequence_3 = create_function(entry__std__sequence_3, 2);
  func__std__sequence_1 = create_function(entry__std__sequence_1, -1);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  string__b53819e78eec080a = from_latin_1_string("Invalid list object encountered during deserialisation!", 55);
  func__96_11 = create_function(entry__96_11, 0);
  func__96_1 = create_function(entry__96_1, 2);
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
  use_polymorphic_function(NULL, "for_each_downwards", &get__for_each_downwards, &poly_idx__for_each_downwards);
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
  define_method("types", "list", poly_idx__to_list, func__types__list__to_list_1);
  define_method("types", "list", poly_idx__length_of, func__types__list__length_of_1);
  define_method("types", "list", poly_idx__push, func__types__list__push_1);
  define_method("types", "list", poly_idx__drop, func__types__list__drop_1);
  define_method("types", "list", poly_idx__pop, func__types__list__pop_1);
  define_method("types", "list", poly_idx__peek, func__types__list__peek_1);
  define_method("types", "list", poly_idx__append, func__types__list__append_1);
  define_method("types", "list", poly_idx__range, func__types__list__range_1);
  define_method("types", "generic_list", poly_idx__delete_at, func__types__generic_list__delete_at_1);
  define_method("types", "generic_list", poly_idx__is_empty, func__types__generic_list__is_empty_1);
  define_method("types", "generic_list", poly_idx__for_each_from_to, func__types__generic_list__for_each_from_to_1);
  define_method("types", "generic_list", poly_idx__for_each_from_down_to, func__types__generic_list__for_each_from_down_to_1);
  define_method("types", "generic_list", poly_idx__for_each, func__types__generic_list__for_each_1);
  define_method("types", "generic_list", poly_idx__for_each_downwards, func__types__generic_list__for_each_downwards_1);
  define_method("types", "generic_list", poly_idx__update_each, func__types__generic_list__update_each_1);
  define_method("types", "list", poly_idx__for_each_pair, func__types__list__for_each_pair_1);
  define_method("types", "generic_list", poly_idx__get, func__types__generic_list__get_1);
  define_method("types", "list", poly_idx__put, func__types__list__put_1);
  define_method("types", "list", poly_idx__merge, func__types__list__merge_1);
  define_method("types", "list", poly_idx__serialize, func__types__list__serialize_1);
  define_method("types", "list", poly_idx__sort, func__types__list__sort_1);
  define_method("types", "list", poly_idx__new_empty_collection, func__types__list__new_empty_collection_1);
  define_method("types", "generic_list", poly_idx__equal, func__types__generic_list__equal_1);
  define_method("types", "generic_list", poly_idx__filter, func__types__generic_list__filter_1);
  define_method("types", "generic_list", poly_idx__map, func__types__generic_list__map_1);
  define_method("types", "generic_list", poly_idx__dup, func__types__generic_list__dup_1);
  define_method("types", "generic_list", poly_idx__interleave, func__types__generic_list__interleave_1);
  define_method("types", "generic_list", poly_idx__contains, func__types__generic_list__contains_1);
  define_attribute("types", "object", poly_idx__is_a_sequence, get__false());
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__list(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_list, create_function(type__std__is_a_list, -1));
  assign_value(&var.types__generic_list, get__types__object());
  assign_variable(&var.types__list, &var.types__generic_list);
  assign_variable(&var.std__list, &func__std__list_1);
  assign_variable(&var.std__normalized_index, &func__std__normalized_index_1);
  assign_value(&var.std__is_a_sequence, create_function(type__std__is_a_sequence, -1));
  assign_variable(&var.std__sequence, &func__std__sequence_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__list(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__list);
}
