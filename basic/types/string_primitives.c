#include <string.h>
#include <fnmatch.h>
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
IMPORT NODE *zero;
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
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
IMPORT void *allocate(long size);
IMPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
IMPORT void no_such_function(void);
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT void too_many_arguments_error(void);
IMPORT void invalid_index_error(void);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT void *allocate_large(long size);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void *allocate_memory(size_t size);
IMPORT NODE *from_long(long val);
IMPORT NODE *boolean_true;
IMPORT NODE *boolean_false;
IMPORT void join_nodes(void *left_node_pp, void *right_node_pp);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uint64(uint64_t val);
IMPORT NODE *create_cell(void);
IMPORT NODE *undefined;
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *empty_string;
IMPORT int print(char **buf_p, const char *format, ...);
IMPORT NODE *from_double(double val);
IMPORT NODE *from_c_string(const char *str);
IMPORT void deallocate_memory(void *buf);
IMPORT NODE *from_bool(int val);
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_c_function(const char *name, void *func);
IMPORT NODE *from_uint32_string(const uint32_t *str, long len);
IMPORT void set_module(const char *name);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *create_future(void);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
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
IMPORT void initialize_future(NODE *var, NODE *val);
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
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static int poly_idx__count_character_occurrences;
static NODE_GETTER get__count_character_occurrences;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__for_each_from_to;
static NODE_GETTER get_value_or_future__for_each_from_to;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static int poly_idx__hash;
static NODE_GETTER get__hash;
static int poly_idx__hash2;
static NODE_GETTER get__hash2;
static NODE_GETTER get__hex;
static NODE_GETTER get_value_or_future__hex;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__is_a_latin_1_string;
static NODE_GETTER get__is_a_latin_1_string;
static int poly_idx__is_a_string;
static NODE_GETTER get__is_a_string;
static int poly_idx__length_of;
static NODE_GETTER get__length_of;
static int poly_idx__less;
static NODE_GETTER get__less;
static int poly_idx__parse_integer;
static NODE_GETTER get__parse_integer;
static int poly_idx__parse_real;
static NODE_GETTER get__parse_real;
static int poly_idx__push;
static NODE_GETTER get__push;
static int poly_idx__range;
static NODE_GETTER get__range;
static int poly_idx__serialize;
static NODE_GETTER get__serialize;
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
static NODE_GETTER get__std__shift_left;
static NODE_GETTER get_value_or_future__std__shift_left;
static NODE_GETTER get__std__times;
static NODE_GETTER get_value_or_future__std__times;
static NODE_GETTER get__std__value_range;
static NODE_GETTER get_value_or_future__std__value_range;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__to_integer;
static NODE_GETTER get_value_or_future__to_integer;
static int poly_idx__to_string;
static NODE_GETTER get__to_string;
static int poly_idx__to_utf8;
static NODE_GETTER get__to_utf8;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__generic_list;
static NODE_GETTER get_value_or_future__types__generic_list;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static struct {
  NODE *std__is_a_string;
  NODE *std__count_character_occurrences;
  NODE *std__to_utf8;
  NODE *std__is_a_latin_1_string;
  NODE *types__string;
  NODE *types__octet_string;
  NODE *types__quad_octet_string;
  NODE *std__empty_string;
  NODE *std__matches_file_pattern;
  NODE *std__from_utf8;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__is_a_string;
static void type__std__is_a_string(void);
static NODE *get__std__is_a_string(void) {
  return var.std__is_a_string;
}
static int poly_idx__std__count_character_occurrences;
static void type__std__count_character_occurrences(void);
static NODE *get__std__count_character_occurrences(void) {
  return var.std__count_character_occurrences;
}
static int poly_idx__std__to_utf8;
static void type__std__to_utf8(void);
static NODE *get__std__to_utf8(void) {
  return var.std__to_utf8;
}
static int poly_idx__std__is_a_latin_1_string;
static void type__std__is_a_latin_1_string(void);
static NODE *get__std__is_a_latin_1_string(void) {
  return var.std__is_a_latin_1_string;
}
static NODE *get__types__string(void) {
  return var.types__string;
}

typedef struct OCTET_DATA OCTET_DATA;
struct OCTET_DATA {
  long size; // in octets
  long length; // in 8-bit-characters (which is the same as octets)
  uint8_t buffer[0];
};

typedef struct QUAD_OCTET_DATA QUAD_OCTET_DATA;
struct QUAD_OCTET_DATA {
  long size; // in octets
  long length;  // in 32-bit-characters
  uint32_t buffer[0];
};

static OCTET_DATA *collect_octet_data(OCTET_DATA *data);

static QUAD_OCTET_DATA *collect_quad_octet_data(QUAD_OCTET_DATA *data);

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  long offset; // usually zero
  long length;
  OCTET_DATA *data;
} OCTET_STRING;

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  long offset; // usually zero
  long length;
  QUAD_OCTET_DATA *data;
} QUAD_OCTET_STRING;
static NODE *get__types__octet_string(void) {
  return var.types__octet_string;
}
static NODE *create__types__octet_string(long offset, long length, OCTET_DATA *data);
static NODE *get__types__quad_octet_string(void) {
  return var.types__quad_octet_string;
}
static NODE *create__types__quad_octet_string(long offset, long length, QUAD_OCTET_DATA *data);
static NODE *get__std__empty_string(void) {
  return var.std__empty_string;
}

static char *func__types__octet_string___to_c_string(NODE *node);

static uint8_t *func__types__octet_string___to_octets(NODE *node, long *size_p);

static long func__types__octet_string___length_of(NODE *node);

static long func__types__quad_octet_string___length_of(NODE *node);
static void entry__types__octet_string__length_of_1(void);
static NODE *func__types__octet_string__length_of_1;
static void entry__types__quad_octet_string__length_of_1(void);
static NODE *func__types__quad_octet_string__length_of_1;
static void entry__types__octet_string__equal_1(void);
static NODE *func__types__octet_string__equal_1;
static void entry__types__quad_octet_string__equal_1(void);
static NODE *func__types__quad_octet_string__equal_1;
static void entry__types__octet_string__count_character_occurrences_1(void);
static NODE *func__types__octet_string__count_character_occurrences_1;
static void entry__types__quad_octet_string__count_character_occurrences_1(void);
static NODE *func__types__quad_octet_string__count_character_occurrences_1;
static void entry__types__octet_string__less_1(void);
static NODE *func__types__octet_string__less_1;
static void entry__types__quad_octet_string__less_1(void);
static NODE *func__types__quad_octet_string__less_1;
static void entry__types__octet_string__hash_1(void);
static NODE *func__types__octet_string__hash_1;
static void entry__types__octet_string__hash2_1(void);
static NODE *func__types__octet_string__hash2_1;
static void entry__types__quad_octet_string__hash_1(void);
static NODE *func__types__quad_octet_string__hash_1;
static void entry__types__quad_octet_string__hash2_1(void);
static NODE *func__types__quad_octet_string__hash2_1;
static NODE *func__types__string__to_string_1;
static void entry__types__string__to_string_1(void);
static FRAME_INFO frame__types__string__to_string_1 = {1, {"self"}};
static NODE *func__types__string__serialize_1;
static void entry__types__string__serialize_1(void);
static FRAME_INFO frame__types__string__serialize_1 = {4, {"self", "indent", "buf", "s"}};
static NODE *string__578a5af303e9cc3;
static NODE *func__types__string__serialize_3;
static void entry__types__string__serialize_3(void);
static FRAME_INFO frame__types__string__serialize_3 = {5, {"idx", "chr", "buf", "self", "s"}};
static void cont__types__string__serialize_4(void);
static NODE *func__types__string__serialize_5;
static void entry__types__string__serialize_5(void);
static FRAME_INFO frame__types__string__serialize_5 = {1, {"chr"}};
static void cont__types__string__serialize_6(void);
static NODE *func__types__string__serialize_7;
static void entry__types__string__serialize_7(void);
static FRAME_INFO frame__types__string__serialize_7 = {1, {"chr"}};
static void cont__types__string__serialize_8(void);
static NODE *func__types__string__serialize_9;
static void entry__types__string__serialize_9(void);
static FRAME_INFO frame__types__string__serialize_9 = {1, {"chr"}};
static void cont__types__string__serialize_10(void);
static NODE *func__types__string__serialize_11;
static void entry__types__string__serialize_11(void);
static FRAME_INFO frame__types__string__serialize_11 = {1, {"chr"}};
static void cont__types__string__serialize_12(void);
static void cont__types__string__serialize_13(void);
static void cont__types__string__serialize_14(void);
static void cont__types__string__serialize_15(void);
static void cont__types__string__serialize_16(void);
static NODE *func__types__string__serialize_17;
static void entry__types__string__serialize_17(void);
static FRAME_INFO frame__types__string__serialize_17 = {5, {"buf", "self", "s", "idx", "chr"}};
static void cont__types__string__serialize_18(void);
static void cont__types__string__serialize_19(void);
static void cont__types__string__serialize_20(void);
static void cont__types__string__serialize_21(void);
static void cont__types__string__serialize_22(void);
static NODE *string__fa728415fa96bb4;
static void cont__types__string__serialize_24(void);
static void cont__types__string__serialize_25(void);
static void cont__types__string__serialize_26(void);
static void cont__types__string__serialize_27(void);
static void cont__types__string__serialize_28(void);
static void cont__types__string__serialize_29(void);
static void cont__types__string__serialize_30(void);
static void cont__types__string__serialize_31(void);
static NODE *func__types__string__parse_integer_1;
static void entry__types__string__parse_integer_1(void);
static FRAME_INFO frame__types__string__parse_integer_1 = {4, {"self", "return", "val", "negate"}};
static void cont__types__string__parse_integer_2(void);
static NODE *func__types__string__parse_integer_3;
static void entry__types__string__parse_integer_3(void);
static FRAME_INFO frame__types__string__parse_integer_3 = {2, {"self", "negate"}};
static void cont__types__string__parse_integer_4(void);
static void cont__types__string__parse_integer_5(void);
static void cont__types__string__parse_integer_6(void);
static NODE *func__types__string__parse_integer_7;
static void entry__types__string__parse_integer_7(void);
static FRAME_INFO frame__types__string__parse_integer_7 = {4, {"break", "self", "val", "return"}};
static NODE *func__types__string__parse_integer_8;
static void entry__types__string__parse_integer_8(void);
static FRAME_INFO frame__types__string__parse_integer_8 = {4, {"self", "val", "return", "break"}};
static NODE *string__2d7981f4e6882ba7;
static void cont__types__string__parse_integer_10(void);
static NODE *func__types__string__parse_integer_11;
static void entry__types__string__parse_integer_11(void);
static FRAME_INFO frame__types__string__parse_integer_11 = {4, {"self", "val", "return", "break"}};
static void cont__types__string__parse_integer_12(void);
static NODE *func__types__string__parse_integer_13;
static void entry__types__string__parse_integer_13(void);
static FRAME_INFO frame__types__string__parse_integer_13 = {6, {"idx", "chr", "val", "return", "self", "break"}};
static void cont__types__string__parse_integer_14(void);
static NODE *func__types__string__parse_integer_15;
static void entry__types__string__parse_integer_15(void);
static FRAME_INFO frame__types__string__parse_integer_15 = {2, {"val", "chr"}};
static void cont__types__string__parse_integer_16(void);
static void cont__types__string__parse_integer_17(void);
static void cont__types__string__parse_integer_18(void);
static NODE *func__types__string__parse_integer_19;
static void entry__types__string__parse_integer_19(void);
static FRAME_INFO frame__types__string__parse_integer_19 = {4, {"idx", "return", "self", "break"}};
static void cont__types__string__parse_integer_20(void);
static void cont__types__string__parse_integer_21(void);
static NODE *func__types__string__parse_integer_22;
static void entry__types__string__parse_integer_22(void);
static FRAME_INFO frame__types__string__parse_integer_22 = {2, {"return", "self"}};
static void cont__types__string__parse_integer_23(void);
static void cont__types__string__parse_integer_24(void);
static void cont__types__string__parse_integer_25(void);
static NODE *func__types__string__parse_integer_26;
static void entry__types__string__parse_integer_26(void);
static FRAME_INFO frame__types__string__parse_integer_26 = {4, {"self", "val", "return", "break"}};
static NODE *string__2d7981f4e6882baa;
static void cont__types__string__parse_integer_28(void);
static NODE *func__types__string__parse_integer_29;
static void entry__types__string__parse_integer_29(void);
static FRAME_INFO frame__types__string__parse_integer_29 = {4, {"self", "val", "return", "break"}};
static void cont__types__string__parse_integer_30(void);
static NODE *func__types__string__parse_integer_31;
static void entry__types__string__parse_integer_31(void);
static FRAME_INFO frame__types__string__parse_integer_31 = {6, {"idx", "chr", "val", "return", "self", "break"}};
static void cont__types__string__parse_integer_32(void);
static NODE *func__types__string__parse_integer_33;
static void entry__types__string__parse_integer_33(void);
static FRAME_INFO frame__types__string__parse_integer_33 = {2, {"val", "chr"}};
static void cont__types__string__parse_integer_34(void);
static void cont__types__string__parse_integer_35(void);
static void cont__types__string__parse_integer_36(void);
static NODE *func__types__string__parse_integer_37;
static void entry__types__string__parse_integer_37(void);
static FRAME_INFO frame__types__string__parse_integer_37 = {4, {"idx", "return", "self", "break"}};
static void cont__types__string__parse_integer_38(void);
static void cont__types__string__parse_integer_39(void);
static NODE *func__types__string__parse_integer_40;
static void entry__types__string__parse_integer_40(void);
static FRAME_INFO frame__types__string__parse_integer_40 = {2, {"return", "self"}};
static void cont__types__string__parse_integer_41(void);
static void cont__types__string__parse_integer_42(void);
static void cont__types__string__parse_integer_43(void);
static NODE *func__types__string__parse_integer_44;
static void entry__types__string__parse_integer_44(void);
static FRAME_INFO frame__types__string__parse_integer_44 = {4, {"self", "val", "return", "break"}};
static NODE *string__2d7981f4e6882bbd;
static void cont__types__string__parse_integer_46(void);
static NODE *func__types__string__parse_integer_47;
static void entry__types__string__parse_integer_47(void);
static FRAME_INFO frame__types__string__parse_integer_47 = {4, {"self", "val", "return", "break"}};
static void cont__types__string__parse_integer_48(void);
static NODE *func__types__string__parse_integer_49;
static void entry__types__string__parse_integer_49(void);
static FRAME_INFO frame__types__string__parse_integer_49 = {6, {"idx", "chr", "val", "return", "self", "break"}};
static void cont__types__string__parse_integer_50(void);
static NODE *func__types__string__parse_integer_51;
static void entry__types__string__parse_integer_51(void);
static FRAME_INFO frame__types__string__parse_integer_51 = {2, {"val", "chr"}};
static void cont__types__string__parse_integer_52(void);
static void cont__types__string__parse_integer_53(void);
static void cont__types__string__parse_integer_54(void);
static void cont__types__string__parse_integer_55(void);
static NODE *func__types__string__parse_integer_56;
static void entry__types__string__parse_integer_56(void);
static FRAME_INFO frame__types__string__parse_integer_56 = {2, {"val", "chr"}};
static void cont__types__string__parse_integer_57(void);
static void cont__types__string__parse_integer_58(void);
static void cont__types__string__parse_integer_59(void);
static void cont__types__string__parse_integer_60(void);
static void cont__types__string__parse_integer_61(void);
static NODE *func__types__string__parse_integer_62;
static void entry__types__string__parse_integer_62(void);
static FRAME_INFO frame__types__string__parse_integer_62 = {2, {"val", "chr"}};
static void cont__types__string__parse_integer_63(void);
static void cont__types__string__parse_integer_64(void);
static void cont__types__string__parse_integer_65(void);
static void cont__types__string__parse_integer_66(void);
static NODE *func__types__string__parse_integer_67;
static void entry__types__string__parse_integer_67(void);
static FRAME_INFO frame__types__string__parse_integer_67 = {4, {"idx", "return", "self", "break"}};
static void cont__types__string__parse_integer_68(void);
static void cont__types__string__parse_integer_69(void);
static NODE *func__types__string__parse_integer_70;
static void entry__types__string__parse_integer_70(void);
static FRAME_INFO frame__types__string__parse_integer_70 = {2, {"return", "self"}};
static void cont__types__string__parse_integer_71(void);
static void cont__types__string__parse_integer_72(void);
static void cont__types__string__parse_integer_73(void);
static NODE *func__types__string__parse_integer_74;
static void entry__types__string__parse_integer_74(void);
static FRAME_INFO frame__types__string__parse_integer_74 = {4, {"self", "val", "return", "break"}};
static NODE *func__types__string__parse_integer_75;
static void entry__types__string__parse_integer_75(void);
static FRAME_INFO frame__types__string__parse_integer_75 = {6, {"idx", "chr", "val", "return", "self", "break"}};
static void cont__types__string__parse_integer_76(void);
static NODE *func__types__string__parse_integer_77;
static void entry__types__string__parse_integer_77(void);
static FRAME_INFO frame__types__string__parse_integer_77 = {2, {"val", "chr"}};
static void cont__types__string__parse_integer_78(void);
static void cont__types__string__parse_integer_79(void);
static void cont__types__string__parse_integer_80(void);
static NODE *func__types__string__parse_integer_81;
static void entry__types__string__parse_integer_81(void);
static FRAME_INFO frame__types__string__parse_integer_81 = {4, {"idx", "return", "self", "break"}};
static void cont__types__string__parse_integer_82(void);
static void cont__types__string__parse_integer_83(void);
static NODE *func__types__string__parse_integer_84;
static void entry__types__string__parse_integer_84(void);
static FRAME_INFO frame__types__string__parse_integer_84 = {2, {"return", "self"}};
static void cont__types__string__parse_integer_85(void);
static void cont__types__string__parse_integer_86(void);
static void cont__types__string__parse_integer_87(void);
static void cont__types__string__parse_integer_88(void);
static void cont__types__string__parse_integer_89(void);
static NODE *func__types__string__parse_integer_90;
static void entry__types__string__parse_integer_90(void);
static FRAME_INFO frame__types__string__parse_integer_90 = {1, {"val"}};
static void cont__types__string__parse_integer_91(void);
static NODE *func__types__string__parse_integer_92;
static void entry__types__string__parse_integer_92(void);
static FRAME_INFO frame__types__string__parse_integer_92 = {1, {"val"}};
static void cont__types__string__parse_integer_93(void);

static long func__types__octet_string___debug_string(NODE *node, int indent, int max_depth, char *buf);

static long func__types__quad_octet_string___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__types__octet_string__push_1(void);
static NODE *func__types__octet_string__push_1;
static void entry__types__quad_octet_string__push_1(void);
static NODE *func__types__quad_octet_string__push_1;
static void entry__types__octet_string__append_1(void);
static NODE *func__types__octet_string__append_1;
static void entry__types__quad_octet_string__append_1(void);
static NODE *func__types__quad_octet_string__append_1;
static void entry__types__string__parse_real_1(void);
static NODE *func__types__string__parse_real_1;
static void entry__types__octet_string__range_1(void);
static NODE *func__types__octet_string__range_1;
static void entry__types__quad_octet_string__range_1(void);
static NODE *func__types__quad_octet_string__range_1;
static void entry__std__matches_file_pattern_1(void);
static NODE *func__std__matches_file_pattern_1;
static NODE *get__std__matches_file_pattern(void) {
  return var.std__matches_file_pattern;
}
static void entry__types__octet_string__is_a_latin_1_string_1(void);
static NODE *func__types__octet_string__is_a_latin_1_string_1;
static void entry__types__quad_octet_string__is_a_latin_1_string_1(void);
static NODE *func__types__quad_octet_string__is_a_latin_1_string_1;
static void entry__std__from_utf8_1(void);
static NODE *func__std__from_utf8_1;
static NODE *get__std__from_utf8(void) {
  return var.std__from_utf8;
}
static void entry__types__octet_string__to_utf8_1(void);
static NODE *func__types__octet_string__to_utf8_1;
static void entry__types__quad_octet_string__to_utf8_1(void);
static NODE *func__types__quad_octet_string__to_utf8_1;
void run__basic__types__string_primitives(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_string, NULL, 26, 26, 2, 17},
  {type__std__count_character_occurrences, NULL, 31, 31, 2, 33},
  {type__std__to_utf8, NULL, 35, 35, 2, 13},
  {type__std__is_a_latin_1_string, NULL, 39, 39, 2, 25},
  {run__basic__types__string_primitives, NULL, 43, 62, 1, 55},
  {entry__types__octet_string__length_of_1, NULL, 352, 355, 3, 2},
  {entry__types__quad_octet_string__length_of_1, NULL, 360, 363, 3, 2},
  {entry__types__octet_string__equal_1, NULL, 368, 390, 3, 2},
  {entry__types__quad_octet_string__equal_1, NULL, 395, 417, 3, 2},
  {entry__types__octet_string__count_character_occurrences_1, NULL, 422, 434, 3, 2},
  {entry__types__quad_octet_string__count_character_occurrences_1, NULL, 439, 451, 3, 2},
  {entry__types__octet_string__less_1, NULL, 456, 506, 3, 2},
  {entry__types__quad_octet_string__less_1, NULL, 511, 561, 3, 2},
  {entry__types__octet_string__hash_1, NULL, 566, 587, 3, 2},
  {entry__types__octet_string__hash2_1, NULL, 592, 604, 3, 2},
  {entry__types__quad_octet_string__hash_1, NULL, 609, 630, 3, 2},
  {entry__types__quad_octet_string__hash2_1, NULL, 635, 647, 3, 2},
  {entry__types__string__to_string_1, NULL, 655, 655, 3, 9},
  {entry__types__string__serialize_11, NULL, 673, 673, 9, 23},
  {cont__types__string__serialize_12, &frame__types__string__serialize_11, 673, 673, 9, 23},
  {entry__types__string__serialize_9, NULL, 672, 672, 9, 23},
  {cont__types__string__serialize_10, &frame__types__string__serialize_9, 673, 673, 9, 23},
  {cont__types__string__serialize_13, &frame__types__string__serialize_9, },
  {entry__types__string__serialize_7, NULL, 671, 671, 9, 19},
  {cont__types__string__serialize_8, &frame__types__string__serialize_7, },
  {cont__types__string__serialize_14, &frame__types__string__serialize_7, },
  {entry__types__string__serialize_5, NULL, 670, 670, 9, 17},
  {cont__types__string__serialize_6, &frame__types__string__serialize_5, },
  {cont__types__string__serialize_15, &frame__types__string__serialize_5, },
  {entry__types__string__serialize_17, NULL, 675, 675, 34, 38},
  {cont__types__string__serialize_18, &frame__types__string__serialize_17, 675, 675, 21, 39},
  {cont__types__string__serialize_19, &frame__types__string__serialize_17, 675, 675, 9, 39},
  {cont__types__string__serialize_20, &frame__types__string__serialize_17, 676, 676, 39, 52},
  {cont__types__string__serialize_21, &frame__types__string__serialize_17, 676, 676, 35, 53},
  {cont__types__string__serialize_22, &frame__types__string__serialize_17, 676, 676, 21, 58},
  {cont__types__string__serialize_24, &frame__types__string__serialize_17, 676, 676, 9, 58},
  {cont__types__string__serialize_25, &frame__types__string__serialize_17, 677, 677, 9, 16},
  {cont__types__string__serialize_26, &frame__types__string__serialize_17, 677, 677, 16, 16},
  {entry__types__string__serialize_3, NULL, 669, 669, 9, 17},
  {cont__types__string__serialize_4, &frame__types__string__serialize_3, },
  {cont__types__string__serialize_16, &frame__types__string__serialize_3, 667, 677, 5, 17},
  {entry__types__string__serialize_1, NULL, 666, 677, 3, 18},
  {cont__types__string__serialize_27, &frame__types__string__serialize_1, 678, 678, 29, 29},
  {cont__types__string__serialize_28, &frame__types__string__serialize_1, 678, 678, 15, 30},
  {cont__types__string__serialize_29, &frame__types__string__serialize_1, 678, 678, 3, 30},
  {cont__types__string__serialize_30, &frame__types__string__serialize_1, 679, 679, 6, 23},
  {cont__types__string__serialize_31, &frame__types__string__serialize_1, 679, 679, 3, 23},
  {entry__types__string__parse_integer_3, NULL, 691, 691, 20, 20},
  {cont__types__string__parse_integer_4, &frame__types__string__parse_integer_3, 691, 691, 5, 20},
  {cont__types__string__parse_integer_5, &frame__types__string__parse_integer_3, 692, 692, 16, 16},
  {entry__types__string__parse_integer_15, NULL, 700, 700, 21, 28},
  {cont__types__string__parse_integer_16, &frame__types__string__parse_integer_15, 700, 700, 32, 38},
  {cont__types__string__parse_integer_17, &frame__types__string__parse_integer_15, 700, 700, 15, 39},
  {cont__types__string__parse_integer_18, &frame__types__string__parse_integer_15, 700, 700, 39, 39},
  {entry__types__string__parse_integer_22, NULL, 702, 702, 28, 48},
  {entry__types__string__parse_integer_19, NULL, 702, 702, 18, 25},
  {cont__types__string__parse_integer_20, &frame__types__string__parse_integer_19, 702, 702, 18, 25},
  {cont__types__string__parse_integer_21, &frame__types__string__parse_integer_19, 702, 702, 15, 48},
  {cont__types__string__parse_integer_23, &frame__types__string__parse_integer_19, 703, 703, 32, 32},
  {cont__types__string__parse_integer_24, &frame__types__string__parse_integer_19, 703, 703, 15, 32},
  {cont__types__string__parse_integer_25, &frame__types__string__parse_integer_19, 704, 704, 15, 19},
  {entry__types__string__parse_integer_13, NULL, 699, 699, 13, 22},
  {cont__types__string__parse_integer_14, &frame__types__string__parse_integer_13, 697, 704, 11, 20},
  {entry__types__string__parse_integer_11, NULL, 696, 696, 34, 34},
  {cont__types__string__parse_integer_12, &frame__types__string__parse_integer_11, 696, 704, 9, 21},
  {entry__types__string__parse_integer_8, NULL, 695, 695, 10, 31},
  {cont__types__string__parse_integer_10, &frame__types__string__parse_integer_8, 695, 704, 7, 22},
  {entry__types__string__parse_integer_33, NULL, 710, 710, 21, 28},
  {cont__types__string__parse_integer_34, &frame__types__string__parse_integer_33, 710, 710, 32, 38},
  {cont__types__string__parse_integer_35, &frame__types__string__parse_integer_33, 710, 710, 15, 39},
  {cont__types__string__parse_integer_36, &frame__types__string__parse_integer_33, 710, 710, 39, 39},
  {entry__types__string__parse_integer_40, NULL, 712, 712, 28, 48},
  {entry__types__string__parse_integer_37, NULL, 712, 712, 18, 25},
  {cont__types__string__parse_integer_38, &frame__types__string__parse_integer_37, 712, 712, 18, 25},
  {cont__types__string__parse_integer_39, &frame__types__string__parse_integer_37, 712, 712, 15, 48},
  {cont__types__string__parse_integer_41, &frame__types__string__parse_integer_37, 713, 713, 32, 32},
  {cont__types__string__parse_integer_42, &frame__types__string__parse_integer_37, 713, 713, 15, 32},
  {cont__types__string__parse_integer_43, &frame__types__string__parse_integer_37, 714, 714, 15, 19},
  {entry__types__string__parse_integer_31, NULL, 709, 709, 13, 22},
  {cont__types__string__parse_integer_32, &frame__types__string__parse_integer_31, 707, 714, 11, 20},
  {entry__types__string__parse_integer_29, NULL, 706, 706, 34, 34},
  {cont__types__string__parse_integer_30, &frame__types__string__parse_integer_29, 706, 714, 9, 21},
  {entry__types__string__parse_integer_26, NULL, 705, 705, 10, 31},
  {cont__types__string__parse_integer_28, &frame__types__string__parse_integer_26, 705, 714, 7, 22},
  {entry__types__string__parse_integer_51, NULL, 719, 719, 21, 28},
  {cont__types__string__parse_integer_52, &frame__types__string__parse_integer_51, 719, 719, 32, 38},
  {cont__types__string__parse_integer_53, &frame__types__string__parse_integer_51, 719, 719, 15, 39},
  {cont__types__string__parse_integer_54, &frame__types__string__parse_integer_51, 719, 719, 39, 39},
  {entry__types__string__parse_integer_56, NULL, 721, 721, 21, 28},
  {cont__types__string__parse_integer_57, &frame__types__string__parse_integer_56, 721, 721, 32, 38},
  {cont__types__string__parse_integer_58, &frame__types__string__parse_integer_56, 721, 721, 21, 38},
  {cont__types__string__parse_integer_59, &frame__types__string__parse_integer_56, 721, 721, 15, 42},
  {cont__types__string__parse_integer_60, &frame__types__string__parse_integer_56, 721, 721, 42, 42},
  {entry__types__string__parse_integer_62, NULL, 723, 723, 21, 28},
  {cont__types__string__parse_integer_63, &frame__types__string__parse_integer_62, 723, 723, 32, 38},
  {cont__types__string__parse_integer_64, &frame__types__string__parse_integer_62, 723, 723, 21, 38},
  {cont__types__string__parse_integer_65, &frame__types__string__parse_integer_62, 723, 723, 15, 42},
  {cont__types__string__parse_integer_66, &frame__types__string__parse_integer_62, 723, 723, 42, 42},
  {entry__types__string__parse_integer_70, NULL, 725, 725, 28, 48},
  {entry__types__string__parse_integer_67, NULL, 725, 725, 18, 25},
  {cont__types__string__parse_integer_68, &frame__types__string__parse_integer_67, 725, 725, 18, 25},
  {cont__types__string__parse_integer_69, &frame__types__string__parse_integer_67, 725, 725, 15, 48},
  {cont__types__string__parse_integer_71, &frame__types__string__parse_integer_67, 726, 726, 32, 32},
  {cont__types__string__parse_integer_72, &frame__types__string__parse_integer_67, 726, 726, 15, 32},
  {cont__types__string__parse_integer_73, &frame__types__string__parse_integer_67, 727, 727, 15, 19},
  {entry__types__string__parse_integer_49, NULL, 718, 718, 13, 22},
  {cont__types__string__parse_integer_50, &frame__types__string__parse_integer_49, 720, 720, 13, 22},
  {cont__types__string__parse_integer_55, &frame__types__string__parse_integer_49, 722, 722, 13, 22},
  {cont__types__string__parse_integer_61, &frame__types__string__parse_integer_49, 717, 727, 11, 20},
  {entry__types__string__parse_integer_47, NULL, 716, 716, 34, 34},
  {cont__types__string__parse_integer_48, &frame__types__string__parse_integer_47, 716, 727, 9, 21},
  {entry__types__string__parse_integer_44, NULL, 715, 715, 10, 31},
  {cont__types__string__parse_integer_46, &frame__types__string__parse_integer_44, 715, 727, 7, 22},
  {entry__types__string__parse_integer_77, NULL, 733, 733, 20, 25},
  {cont__types__string__parse_integer_78, &frame__types__string__parse_integer_77, 733, 733, 28, 34},
  {cont__types__string__parse_integer_79, &frame__types__string__parse_integer_77, 733, 733, 15, 35},
  {cont__types__string__parse_integer_80, &frame__types__string__parse_integer_77, 733, 733, 35, 35},
  {entry__types__string__parse_integer_84, NULL, 735, 735, 28, 48},
  {entry__types__string__parse_integer_81, NULL, 735, 735, 18, 25},
  {cont__types__string__parse_integer_82, &frame__types__string__parse_integer_81, 735, 735, 18, 25},
  {cont__types__string__parse_integer_83, &frame__types__string__parse_integer_81, 735, 735, 15, 48},
  {cont__types__string__parse_integer_85, &frame__types__string__parse_integer_81, 736, 736, 32, 32},
  {cont__types__string__parse_integer_86, &frame__types__string__parse_integer_81, 736, 736, 15, 32},
  {cont__types__string__parse_integer_87, &frame__types__string__parse_integer_81, 737, 737, 15, 19},
  {entry__types__string__parse_integer_75, NULL, 732, 732, 13, 22},
  {cont__types__string__parse_integer_76, &frame__types__string__parse_integer_75, 730, 737, 11, 20},
  {entry__types__string__parse_integer_74, NULL, 729, 737, 9, 21},
  {entry__types__string__parse_integer_7, NULL, 694, 737, 5, 23},
  {cont__types__string__parse_integer_88, &frame__types__string__parse_integer_7, 738, 738, 12, 12},
  {entry__types__string__parse_integer_90, NULL, 743, 743, 11, 13},
  {cont__types__string__parse_integer_91, &frame__types__string__parse_integer_90, 743, 743, 7, 13},
  {entry__types__string__parse_integer_92, NULL, 744, 744, 7, 12},
  {entry__types__string__parse_integer_1, NULL, 690, 690, 6, 26},
  {cont__types__string__parse_integer_2, &frame__types__string__parse_integer_1, 690, 692, 3, 16},
  {cont__types__string__parse_integer_6, &frame__types__string__parse_integer_1, 693, 738, 3, 12},
  {cont__types__string__parse_integer_89, &frame__types__string__parse_integer_1, 744, 744, 7, 12},
  {cont__types__string__parse_integer_93, &frame__types__string__parse_integer_1, 739, 744, 3, 13},
  {entry__types__octet_string__push_1, NULL, 817, 858, 3, 2},
  {entry__types__quad_octet_string__push_1, NULL, 863, 889, 3, 2},
  {entry__types__octet_string__append_1, NULL, 894, 938, 3, 2},
  {entry__types__quad_octet_string__append_1, NULL, 943, 987, 3, 2},
  {entry__types__string__parse_real_1, NULL, 992, 1004, 3, 2},
  {entry__types__octet_string__range_1, NULL, 1009, 1026, 3, 2},
  {entry__types__quad_octet_string__range_1, NULL, 1031, 1063, 3, 2},
  {entry__std__matches_file_pattern_1, NULL, 1068, 1076, 3, 2},
  {entry__types__octet_string__is_a_latin_1_string_1, NULL, 1081, 1084, 3, 2},
  {entry__types__quad_octet_string__is_a_latin_1_string_1, NULL, 1089, 1092, 3, 2},
  {entry__std__from_utf8_1, NULL, 1097, 1192, 3, 2},
  {entry__types__octet_string__to_utf8_1, NULL, 1197, 1226, 3, 2},
  {entry__types__quad_octet_string__to_utf8_1, NULL, 1242, 1331, 3, 2}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  QUAD_OCTET_STRING quad_octet_string;
  OCTET_STRING octet_string;
};
static void type__std__is_a_string(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_string);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_string, attr);
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
static void type__std__count_character_occurrences(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__count_character_occurrences);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__count_character_occurrences, attr);
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
static void type__std__to_utf8(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_utf8);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_utf8, attr);
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
static void type__std__is_a_latin_1_string(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_latin_1_string);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_latin_1_string, attr);
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
static NODE *character__57;
static NODE *character__55;
static NODE *character__65;
static NODE *character__45;
static NODE *number__0;
static NODE *character__70;
static NODE *number__3;
static NODE *character__48;
static NODE *character__102;
static NODE *number__4;
static NODE *character__126;
static NODE *character__64;
static NODE *character__34;
static NODE *character__39;
static NODE *character__32;
static NODE *character__97;
static NODE *character__59;
static NODE *number__1;
static NODE *character__49;
static NODE *number__2;
static NODE *number__10;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__string_primitives",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/string_primitives.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__string_primitives(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 43: $types::string types::generic_list
  // 44:   #
  // 45:     a sequence of zero or more characters
  // 46:     
  // 47:     This is one of the most fundamental types. It behaves like a scalar as
  // 48:     well as a collection (of characters).
  // 49:     
  // 50:     The characters in the string can be indexed by integers ranging from
  // 51:     1 to the total length of the string.
  // 52:     
  // ...
  initialize_maybe_future(var.types__string, get__types__generic_list());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static OCTET_DATA *collect_octet_data(OCTET_DATA *data) {
  if (IS_COLLECTED(data)) {
    void *new_location = *(void **)data;
    if (IS_AN_INVALID_LENGTH(new_location)) return DECODE_FROM_LENGTH(new_location);
    long length = data->length;
    long size = ALLOCATION_SIZE(length);
    OCTET_DATA *new_data = allocate(sizeof(OCTET_DATA)+size);
    *(void **)data = ENCODE_TO_LENGTH(new_data);
    new_data->size = size;
    new_data->length = length;
    memcpy(new_data->buffer, data->buffer, length);
    return new_data;
  } else if (data && !IS_STATIC(data)) {
    MARK(data)
  }
  return data;
}

static QUAD_OCTET_DATA *collect_quad_octet_data(QUAD_OCTET_DATA *data) {
  if (IS_COLLECTED(data)) {
    void *new_location = *(void **)data;
    if (IS_AN_INVALID_LENGTH(new_location)) return DECODE_FROM_LENGTH(new_location);
    long length = data->length;
    long size = ALLOCATION_SIZE(4*length);
    QUAD_OCTET_DATA *new_data = allocate(sizeof(QUAD_OCTET_DATA)+size);
    *(void **)data = ENCODE_TO_LENGTH(new_data);
    new_data->size = size;
    new_data->length = length;
    memcpy(new_data->buffer, data->buffer, 4*length);
    return new_data;
  } else if (data && !IS_STATIC(data)) {
    MARK(data)
  }
  return data;
}
static void *collect_octet_string(OCTET_STRING *node) {
  OCTET_STRING *new_node = allocate(sizeof(OCTET_STRING));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->offset = node->offset;
  new_node->length = node->length;
  new_node->data = collect_octet_data(node->data);
  return new_node;
}
static void *collect_quad_octet_string(QUAD_OCTET_STRING *node) {
  QUAD_OCTET_STRING *new_node = allocate(sizeof(QUAD_OCTET_STRING));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->offset = node->offset;
  new_node->length = node->length;
  new_node->data = collect_quad_octet_data(node->data);
  return new_node;
}

static VTABLE vtable__types__octet_string = {
  sizeof(OCTET_STRING),
  (COLLECTOR *)&collect_octet_string,
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
  &func__types__octet_string___to_c_string,
  &func__types__octet_string___to_octets,
  (void *)no_such_function,
  &func__types__octet_string___length_of,
  (void *)no_such_function,
  &func__types__octet_string___debug_string
};

static ATTRIBUTES attributes__types__octet_string = {
  &vtable__types__octet_string,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__octet_string(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  long idx = to_long(arguments->slots[0]);
  long length = myself->octet_string.length;
  if (idx < 0) idx = length+idx+1;
  if (idx < 1 || idx > length) {
    invalid_index_error();
  }
  if (argument_count == 1)
    {
    NODE *result__node = (NODE *)(from_uchar32(
        myself->octet_string.data->buffer[myself->octet_string.offset+idx-1]));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }

  uint32_t chr = to_uchar32(arguments->slots[1]);
  long start_offset = myself->octet_string.offset;
  OCTET_DATA *data = myself->octet_string.data;
  if (data->buffer[idx-1] == chr) {
    NODE *result__node = (NODE *)(myself);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if (chr > 0xff) {
    long size = ALLOCATION_SIZE(4*length);
    QUAD_OCTET_DATA *new_data = allocate_large(sizeof(QUAD_OCTET_DATA)+size);
    long i;
    for (i = 0; i < length; ++i) {
      new_data->buffer[i] = data->buffer[start_offset+i];
    }
    new_data->size = size;
    new_data->length = length;
    new_data->buffer[idx-1] = chr;
    {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(0, length, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    long size = ALLOCATION_SIZE(length);
    OCTET_DATA *new_data = allocate_large(sizeof(OCTET_DATA)+size);
    memcpy(new_data->buffer, data->buffer+start_offset, length);
    new_data->size = size;
    new_data->length = length;
    new_data->buffer[idx-1] = chr;
    {
    NODE *result__node = (NODE *)(create__types__octet_string(0, length, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static NODE *create__types__octet_string(long offset, long length, OCTET_DATA *data) {
  NODE *node = allocate(sizeof(OCTET_STRING));
  node->type = type__types__octet_string;
  node->attributes = &attributes__types__octet_string;
  node->octet_string.offset = offset;
  node->octet_string.length = length;
  node->octet_string.data = data;
  return node;
}

static VTABLE vtable__types__quad_octet_string = {
  sizeof(QUAD_OCTET_STRING),
  (COLLECTOR *)&collect_quad_octet_string,
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
  &func__types__quad_octet_string___length_of,
  (void *)no_such_function,
  &func__types__quad_octet_string___debug_string
};

static ATTRIBUTES attributes__types__quad_octet_string = {
  &vtable__types__quad_octet_string,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__quad_octet_string(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  long idx = to_long(arguments->slots[0]);
  long length = myself->quad_octet_string.length;
  if (idx < 0) idx = length+idx+1;
  if (idx < 1 || idx > length) {
    invalid_index_error();
  }
  if (argument_count == 1)
    {
    NODE *result__node = (NODE *)(from_uchar32(
        myself->quad_octet_string.data->buffer[myself->quad_octet_string.offset+idx-1]));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }

  uint32_t chr = to_uchar32(arguments->slots[1]);
  long start_offset = myself->quad_octet_string.offset;
  QUAD_OCTET_DATA *data = myself->quad_octet_string.data;
  if (data->buffer[idx-1] == chr) {
    NODE *result__node = (NODE *)(myself);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if (chr <= 0xff && data->buffer[start_offset+idx-1] > 0xff) {
    long i;
    for (i = 0; i < length; ++i) {
      if (i != idx-1 && data->buffer[start_offset+i] > 0xff) goto quad;
    }
    long size = ALLOCATION_SIZE(length);
    OCTET_DATA *new_data = allocate_large(sizeof(OCTET_DATA)+size);
    for (i = 0; i < length; ++i) {
      new_data->buffer[i] = data->buffer[start_offset+i];
    }
    new_data->size = size;
    new_data->length = length;
    new_data->buffer[idx-1] = chr;
    {
    NODE *result__node = (NODE *)(create__types__octet_string(0, length, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  quad:;
  long size = ALLOCATION_SIZE(4*length);
  QUAD_OCTET_DATA *new_data = allocate_large(sizeof(QUAD_OCTET_DATA)+size);
  memcpy(new_data->buffer, data->buffer+start_offset, 4*length);
  new_data->size = size;
  new_data->length = length;
  new_data->buffer[idx-1] = chr;
  {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(0, length, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static NODE *create__types__quad_octet_string(long offset, long length, QUAD_OCTET_DATA *data) {
  NODE *node = allocate(sizeof(QUAD_OCTET_STRING));
  node->type = type__types__quad_octet_string;
  node->attributes = &attributes__types__quad_octet_string;
  node->quad_octet_string.offset = offset;
  node->quad_octet_string.length = length;
  node->quad_octet_string.data = data;
  return node;
}

NODE *runtime__from_latin_1_string(const char *str, long len) {
  long size = ALLOCATION_SIZE(len);
  OCTET_DATA *data = allocate_large(sizeof(OCTET_DATA)+size);
  data->size = size;
  data->length = len;
  memcpy(data->buffer, str, len);
  return create__types__octet_string(0, len, data);
}

NODE *runtime__from_uint32_string(const uint32_t *str, long len) {
  long size = ALLOCATION_SIZE(4*len);
  QUAD_OCTET_DATA *data = allocate_large(sizeof(QUAD_OCTET_DATA)+size);
  data->size = size;
  data->length = len;
  memcpy(data->buffer, str, 4*len);
  return create__types__quad_octet_string(0, len, data);
}

NODE *runtime__from_c_string(const char *str) {
  return from_latin_1_string(str, strlen(str));
}

static char *func__types__octet_string___to_c_string(NODE *node) {
  long offset = node->octet_string.offset;
  long size = node->octet_string.length;
  char *buf = allocate_memory(size+1);
  memcpy(buf, node->octet_string.data->buffer+offset, size);
  buf[size] = 0;
  return buf;
}

static uint8_t *func__types__octet_string___to_octets(NODE *node, long *size_p) {
  long offset = node->octet_string.offset;
  long size = node->octet_string.length;
  uint8_t *buf = allocate_memory(size);
  memcpy(buf, node->octet_string.data->buffer+offset, size);
  *size_p = size;
  return buf;
}

static long func__types__octet_string___length_of(NODE *node) {
  return node->octet_string.length;
}

static long func__types__quad_octet_string___length_of(NODE *node) {
  return node->quad_octet_string.length;
}
static void entry__types__octet_string__length_of_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_long(arguments->slots[0]->octet_string.length));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__quad_octet_string__length_of_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_long(arguments->slots[0]->quad_octet_string.length));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__octet_string__equal_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *left = arguments->slots[0];
  NODE *right = arguments->slots[1];
  if (left == right) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if ((right)->type != type__types__octet_string) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  OCTET_DATA *left_data = left->octet_string.data;
  OCTET_DATA *right_data = right->octet_string.data;
  long left_offset = left->octet_string.offset;
  long right_offset = right->octet_string.offset;
  long len = left->octet_string.length;
  if (len != right->octet_string.length) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if (left_offset == right_offset && left_data == right_data) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  long i;
  for (i = 0; i < len; ++i) {
    if (left_data->buffer[left_offset+i] != right_data->buffer[right_offset+i]) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  if (left_offset == right_offset) {
    // join the two versions of the string data to simplify future comparisons
    join_nodes(&left->octet_string.data, &right->octet_string.data);
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__quad_octet_string__equal_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *left = arguments->slots[0];
  NODE *right = arguments->slots[1];
  if (left == right) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if ((right)->type != type__types__quad_octet_string) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  QUAD_OCTET_DATA *left_data = left->quad_octet_string.data;
  QUAD_OCTET_DATA *right_data = right->quad_octet_string.data;
  long left_offset = left->quad_octet_string.offset;
  long right_offset = right->quad_octet_string.offset;
  long len = left->quad_octet_string.length;
  if (len != right->quad_octet_string.length) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if (left_offset == right_offset && left_data == right_data) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  long i;
  for (i = 0; i < len; ++i) {
    if (left_data->buffer[left_offset+i] != right_data->buffer[right_offset+i]) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  if (left_offset == right_offset) {
    // join the two versions of the string data to simplify future comparisons
    join_nodes(&left->quad_octet_string.data, &right->quad_octet_string.data);
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__octet_string__count_character_occurrences_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *string = arguments->slots[0];
  uint8_t chr = (uint8_t)to_uchar32(arguments->slots[1]);
  long count = 0;
  OCTET_DATA *data = string->octet_string.data;
  long offset = string->octet_string.offset;
  long len = string->octet_string.length;
  while (--len >= 0) {
    if (data->buffer[offset++] == chr) ++count;
  }
  {
    NODE *result__node = (NODE *)(from_long(count));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__quad_octet_string__count_character_occurrences_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *string = arguments->slots[0];
  uint32_t chr = to_uchar32(arguments->slots[1]);
  long count = 0;
  QUAD_OCTET_DATA *data = string->quad_octet_string.data;
  long offset = string->quad_octet_string.offset;
  long len = string->quad_octet_string.length;
  while (--len >= 0) {
    if (data->buffer[offset++] == chr) ++count;
  }
  {
    NODE *result__node = (NODE *)(from_long(count));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__octet_string__less_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *left = arguments->slots[0];
  NODE *right = arguments->slots[1];
  if (left == right) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if ((right)->type == type__types__octet_string) {
    OCTET_DATA *left_data = left->octet_string.data;
    OCTET_DATA *right_data = right->octet_string.data;
    long left_offset = left->octet_string.offset;
    long right_offset = right->octet_string.offset;
    long left_len = left->octet_string.length;
    long right_len = right->octet_string.length;
    if (left_offset == right_offset && left_len == right_len && left_data == right_data)
      {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    long len = left_len;
    if (right_len < len) len = right_len;
    long i;
    for (i = 0; i < len; ++i) {
      uint8_t left_chr = left_data->buffer[left_offset+i];
      uint8_t right_chr = right_data->buffer[right_offset+i];
      if (left_chr < right_chr) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
      if (left_chr > right_chr) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    }
    if (left_len < right_len) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    if (left_offset == right_offset && left_len == right_len) { // both strings are equal!
      // join the two versions of the string data to simplify future comparisons
      join_nodes(&left->octet_string.data, &right->octet_string.data);
    }
    {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((right)->type == type__types__quad_octet_string) {
    OCTET_DATA *left_data = left->octet_string.data;
    QUAD_OCTET_DATA *right_data = right->quad_octet_string.data;
    long left_offset = left->octet_string.offset;
    long right_offset = right->quad_octet_string.offset;
    long left_len = left->octet_string.length;
    long right_len = right->quad_octet_string.length;
    long len = left_len;
    if (right_len < len) len = right_len;
    long i;
    for (i = 0; i < len; ++i) {
      uint32_t left_chr = left_data->buffer[left_offset+i];
      uint32_t right_chr = right_data->buffer[right_offset+i];
      if (left_chr < right_chr) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
      if (left_chr > right_chr) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    }
    if (left_len < right_len) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    {
    invalid_arguments_error();
  }
  }
}
static void entry__types__quad_octet_string__less_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *left = arguments->slots[0];
  NODE *right = arguments->slots[1];
  if (left == right) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if ((right)->type == type__types__octet_string) {
    QUAD_OCTET_DATA *left_data = left->quad_octet_string.data;
    OCTET_DATA *right_data = right->octet_string.data;
    long left_offset = left->quad_octet_string.offset;
    long right_offset = right->octet_string.offset;
    long left_len = left->quad_octet_string.length;
    long right_len = right->octet_string.length;
    long len = left_len;
    if (right_len < len) len = right_len;
    long i;
    for (i = 0; i < len; ++i) {
      uint32_t left_chr = left_data->buffer[left_offset+i];
      uint32_t right_chr = right_data->buffer[right_offset+i];
      if (left_chr < right_chr) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
      if (left_chr > right_chr) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    }
    if (left_len < right_len) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((right)->type == type__types__quad_octet_string) {
    QUAD_OCTET_DATA *left_data = left->quad_octet_string.data;
    QUAD_OCTET_DATA *right_data = right->quad_octet_string.data;
    long left_offset = left->quad_octet_string.offset;
    long right_offset = right->quad_octet_string.offset;
    long left_len = left->quad_octet_string.length;
    long right_len = right->quad_octet_string.length;
    if (left_offset == right_offset && left_len == right_len && left_data == right_data)
      {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    long len = left_len;
    if (right_len < len) len = right_len;
    long i;
    for (i = 0; i < len; ++i) {
      uint32_t left_chr = left_data->buffer[left_offset+i];
      uint32_t right_chr = right_data->buffer[right_offset+i];
      if (left_chr < right_chr) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
      if (left_chr > right_chr) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    }
    if (left_len < right_len) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    if (left_offset == right_offset && left_len == right_len) { // both strings are equal!
      // join the two versions of the string data to simplify future comparisons
      join_nodes(&left->octet_string.data, &right->octet_string.data);
    }
    {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    {
    invalid_arguments_error();
  }
  }
}
static void entry__types__octet_string__hash_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  uint8_t *buf = self->octet_string.data->buffer+self->octet_string.offset;
  long len = self->octet_string.length;
  uint32_t hash = 0x7890abcd;
  long i;
  if (len > 16) {
    for (i = len-8; i < len; ++i) {
      hash = (hash << 7) | (hash >> 25);
      hash ^= buf[i];
    }
    len = 8;
  }
  for (i = 0; i < len; ++i) {
    hash = (hash << 7) | (hash >> 25);
    hash ^= buf[i];
  }
  hash *= 234256597;
  hash ^= hash >> 26 | hash << 6;
  {
    NODE *result__node = (NODE *)(from_uint32(hash));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__octet_string__hash2_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  uint8_t *buf = self->octet_string.data->buffer+self->octet_string.offset;
  long len = self->octet_string.length;
  uint64_t hash = 0xd39c20af14b5e607L;
  long i;
  for (i = 0; i < len; ++i) {
    hash = (hash << 19) | (hash >> 45);
    hash ^= buf[i];
  }
  {
    NODE *result__node = (NODE *)(from_uint64(hash));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__quad_octet_string__hash_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  uint32_t *buf = self->quad_octet_string.data->buffer+self->quad_octet_string.offset;
  long len = self->quad_octet_string.length;
  uint32_t hash = 0x3456789a;
  long i;
  if (len > 16) {
    for (i = len-8; i < len; ++i) {
      hash = (hash << 13) | (hash >> 19);
      hash ^= buf[i];
    }
    len = 8;
  }
  for (i = 0; i < len; ++i) {
    hash = (hash << 13) | (hash >> 19);
    hash ^= buf[i];
  }
  hash *= 234256597;
  hash ^= hash >> 22 | hash << 10;
  {
    NODE *result__node = (NODE *)(from_uint32(hash));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__quad_octet_string__hash2_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  uint32_t *buf = self->quad_octet_string.data->buffer+self->quad_octet_string.offset;
  long len = self->quad_octet_string.length;
  uint64_t hash = 0xd39c20af14b5e607L;
  long i;
  for (i = 0; i < len; ++i) {
    hash = (hash << 19) | (hash >> 45);
    hash ^= buf[i];
  }
  {
    NODE *result__node = (NODE *)(from_uint64(hash));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__string__to_string_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 655: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__serialize_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // indent: 1
  // buf: 2
  // s: 3
  frame->slots[2] /* buf */ = create_cell();
  frame->slots[3] /* s */ = create_cell();
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
    case 1: frame->slots[1] /* indent */ = undefined;
  }
  // 664: $$buf "@quot;"
  ((CELL *)frame->slots[2])->contents /* buf */ = string__578a5af303e9cc3;
  // 665: $$s 1
  ((CELL *)frame->slots[3])->contents /* s */ = number__1;
  // 666: ... : (idx chr)
  // 667:   if
  // 668:     ||
  // 669:       chr < ' '
  // 670:       chr > '~'
  // 671:       chr == '@@'
  // 672:       chr == '@quot;'
  // 673:       chr == '@apos;'
  // 674:     :
  // 675:       append &buf range(self s idx-1)
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__string__serialize_3, 2);
  // 666: for_each self: (idx chr)
  // 667:   if
  // 668:     ||
  // 669:       chr < ' '
  // 670:       chr > '~'
  // 671:       chr == '@@'
  // 672:       chr == '@quot;'
  // 673:       chr == '@apos;'
  // 674:     :
  // 675:       append &buf range(self s idx-1)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__string__serialize_27;
}
static void entry__types__string__serialize_17(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // buf: 0
  // self: 1
  // s: 2
  // idx: 3
  // chr: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[3]; /* self */
  frame->slots[2] = myself->closure.frame->slots[4]; /* s */
  frame->slots[3] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 675: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__serialize_18;
}
static void cont__types__string__serialize_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 675: ... range(self s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* s */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__serialize_19;
}
static void cont__types__string__serialize_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 675: append &buf range(self s idx-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__string__serialize_20;
}
static void cont__types__string__serialize_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 676: ... chr.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* chr */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__types__string__serialize_21;
}
static void cont__types__string__serialize_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 676: ... hex(chr.to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__hex();
  func = myself->type;
  frame->cont = cont__types__string__serialize_22;
}
static void cont__types__string__serialize_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 676: ... string("@@0x" hex(chr.to_integer) ';')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fa728415fa96bb4;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = character__59;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__types__string__serialize_24;
}
static void cont__types__string__serialize_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 676: append &buf string("@@0x" hex(chr.to_integer) ';')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__string__serialize_25;
}
static void cont__types__string__serialize_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 677: !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__serialize_26;
}
static void cont__types__string__serialize_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* s */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__serialize_3(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // idx: 0
  // chr: 1
  // buf: 2
  // self: 3
  // s: 4
  frame->slots[2] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] = myself->closure.frame->slots[3]; /* s */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 669: chr < ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__serialize_4;
}
static void cont__types__string__serialize_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__string__serialize_5, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__string__serialize_16;
}
static void entry__types__string__serialize_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 670: chr > '~'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__126;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__serialize_6;
}
static void cont__types__string__serialize_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__types__string__serialize_7, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__string__serialize_15;
}
static void entry__types__string__serialize_7(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 671: chr == '@@'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__64;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__serialize_8;
}
static void cont__types__string__serialize_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__types__string__serialize_9, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__string__serialize_14;
}
static void entry__types__string__serialize_9(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 672: chr == '@quot;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__34;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__serialize_10;
}
static void cont__types__string__serialize_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 673: chr == '@apos;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__types__string__serialize_11, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__string__serialize_13;
}
static void entry__types__string__serialize_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 673: chr == '@apos;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__serialize_12;
}
static void cont__types__string__serialize_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 673: chr == '@apos;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__serialize_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__serialize_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__serialize_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__serialize_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 674: :
  // 675:   append &buf range(self s idx-1)
  // 676:   append &buf string("@@0x" hex(chr.to_integer) ';')
  // 677:   !s idx+1
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__string__serialize_17, 0);
  // 667: if
  // 668:   ||
  // 669:     chr < ' '
  // 670:     chr > '~'
  // 671:     chr == '@@'
  // 672:     chr == '@quot;'
  // 673:     chr == '@apos;'
  // 674:   :
  // 675:     append &buf range(self s idx-1)
  // 676:     append &buf string("@@0x" hex(chr.to_integer) ';')
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__serialize_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 678: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__serialize_28;
}
static void cont__types__string__serialize_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 678: ... range(self s -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__serialize_29;
}
static void cont__types__string__serialize_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 678: append &buf range(self s -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__string__serialize_30;
}
static void cont__types__string__serialize_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* buf */ = arguments->slots[0];
  // 679: ... push(buf '@quot;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = character__34;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__string__serialize_31;
}
static void cont__types__string__serialize_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 679: -> push(buf '@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_1(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // return: 1
  // val: 2
  // negate: 3
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[2] /* val */ = create_cell();
  frame->slots[3] /* negate */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 688: $$val 0
  ((CELL *)frame->slots[2])->contents /* val */ = number__0;
  // 689: $$negate false
  ((CELL *)frame->slots[3])->contents /* negate */ = get__false();
  // 690: ... self .has_prefix. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_2;
}
static void cont__types__string__parse_integer_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 690: ... :
  // 691:   range &self 2 -1
  // 692:   !negate true
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_3, 0);
  // 690: if self .has_prefix. '-':
  // 691:   range &self 2 -1
  // 692:   !negate true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_6;
}
static void entry__types__string__parse_integer_3(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // negate: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* negate */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 691: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_4;
}
static void cont__types__string__parse_integer_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 691: range &self 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_5;
}
static void cont__types__string__parse_integer_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  // 692: !negate true
  ((CELL *)frame->slots[1])->contents /* negate */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_integer_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 693: ... : (-> break)
  // 694:   cond
  // 695:     -> self .has_prefix. "0b":
  // 696:       for_each_from_to self 3 -1: (idx chr)
  // 697:         case
  // 698:           chr
  // 699:           '0' .. '1':
  // 700:             !val (val << 1)+(chr-'0')
  // 701:           :
  // 702:             if idx <= 3: return self undefined
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__string__parse_integer_7, 0);
  // 693: do: (-> break)
  // 694:   cond
  // 695:     -> self .has_prefix. "0b":
  // 696:       for_each_from_to self 3 -1: (idx chr)
  // 697:         case
  // 698:           chr
  // 699:           '0' .. '1':
  // 700:             !val (val << 1)+(chr-'0')
  // 701:           :
  // 702:             if idx <= 3: return self undefined
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_89;
}
static void entry__types__string__parse_integer_7(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // break: 0
  // self: 1
  // val: 2
  // return: 3
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[2]; /* val */
  frame->slots[3] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 695: -> self .has_prefix. "0b":
  // 696:   for_each_from_to self 3 -1: (idx chr)
  // 697:     case
  // 698:       chr
  // 699:       '0' .. '1':
  // 700:         !val (val << 1)+(chr-'0')
  // 701:       :
  // 702:         if idx <= 3: return self undefined
  // 703:         range &self idx -1
  // 704:         break
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__string__parse_integer_8, 0);
  // 705: -> self .has_prefix. "0o":
  // 706:   for_each_from_to self 3 -1: (idx chr)
  // 707:     case
  // 708:       chr
  // 709:       '0' .. '7':
  // 710:         !val (val << 3)+(chr-'0')
  // 711:       :
  // 712:         if idx <= 3: return self undefined
  // 713:         range &self idx -1
  // 714:         break
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_26, 0);
  // 715: -> self .has_prefix. "0x":
  // 716:   for_each_from_to self 3 -1: (idx chr)
  // 717:     case chr
  // 718:       '0' .. '9':
  // 719:         !val (val << 4)+(chr-'0')
  // 720:       'a' .. 'f':
  // 721:         !val (val << 4)+(chr-'a')+10
  // 722:       'A' .. 'F':
  // 723:         !val (val << 4)+(chr-'A')+10
  // 724:       :
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__string__parse_integer_44, 0);
  // 728: :
  // 729:   for_each self: (idx chr)
  // 730:     case
  // 731:       chr
  // 732:       '0' .. '9':
  // 733:         !val 10*val+(chr-'0')
  // 734:       :
  // 735:         if idx <= 1: return self undefined
  // 736:         range &self idx -1
  // 737:         break
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__string__parse_integer_74, 0);
  // 694: cond
  // 695:   -> self .has_prefix. "0b":
  // 696:     for_each_from_to self 3 -1: (idx chr)
  // 697:       case
  // 698:         chr
  // 699:         '0' .. '1':
  // 700:           !val (val << 1)+(chr-'0')
  // 701:         :
  // 702:           if idx <= 3: return self undefined
  // 703:           range &self idx -1
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  arguments->slots[3] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_88;
}
static void entry__types__string__parse_integer_77(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // val: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 733: ... 10*val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__10;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_78;
}
static void cont__types__string__parse_integer_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 733: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_79;
}
static void cont__types__string__parse_integer_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 733: !val 10*val+(chr-'0')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_80;
}
static void cont__types__string__parse_integer_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_81(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // idx: 0
  // return: 1
  // self: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] = myself->closure.frame->slots[4]; /* self */
  frame->slots[3] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 735: ... idx <= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_82;
}
static void cont__types__string__parse_integer_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 735: ... idx <= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_83;
}
static void cont__types__string__parse_integer_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 735: ... : return self undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__string__parse_integer_84, 0);
  // 735: if idx <= 1: return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_85;
}
static void entry__types__string__parse_integer_84(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 735: ... return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__parse_integer_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 736: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_86;
}
static void cont__types__string__parse_integer_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 736: range &self idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_87;
}
static void cont__types__string__parse_integer_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* self */ = arguments->slots[0];
  // 737: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_75(void) {
  allocate_initialized_frame_gc(6, 9);
  // slot allocations:
  // idx: 0
  // chr: 1
  // val: 2
  // return: 3
  // self: 4
  // break: 5
  frame->slots[2] = myself->closure.frame->slots[1]; /* val */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  frame->slots[5] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 732: '0' .. '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__57;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_76;
}
static void cont__types__string__parse_integer_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 732: ... :
  // 733:   !val 10*val+(chr-'0')
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__parse_integer_77, 0);
  // 734: :
  // 735:   if idx <= 1: return self undefined
  // 736:   range &self idx -1
  // 737:   break
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__parse_integer_81, 0);
  // 730: case
  // 731:   chr
  // 732:   '0' .. '9':
  // 733:     !val 10*val+(chr-'0')
  // 734:   :
  // 735:     if idx <= 1: return self undefined
  // 736:     range &self idx -1
  // 737:     break
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  arguments->slots[3] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_62(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // val: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 723: ... val << 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_63;
}
static void cont__types__string__parse_integer_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 723: ... chr-'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_64;
}
static void cont__types__string__parse_integer_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 723: ... val << 4)+(chr-'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_65;
}
static void cont__types__string__parse_integer_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 723: !val (val << 4)+(chr-'A')+10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_66;
}
static void cont__types__string__parse_integer_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_67(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // idx: 0
  // return: 1
  // self: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] = myself->closure.frame->slots[4]; /* self */
  frame->slots[3] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 725: ... idx <= 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_68;
}
static void cont__types__string__parse_integer_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 725: ... idx <= 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_69;
}
static void cont__types__string__parse_integer_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 725: ... : return self undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__string__parse_integer_70, 0);
  // 725: if idx <= 3: return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_71;
}
static void entry__types__string__parse_integer_70(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 725: ... return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__parse_integer_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 726: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_72;
}
static void cont__types__string__parse_integer_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 726: range &self idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_73;
}
static void cont__types__string__parse_integer_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* self */ = arguments->slots[0];
  // 727: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_49(void) {
  allocate_initialized_frame_gc(6, 13);
  // slot allocations:
  // idx: 0
  // chr: 1
  // val: 2
  // return: 3
  // self: 4
  // break: 5
  frame->slots[2] = myself->closure.frame->slots[1]; /* val */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  frame->slots[5] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 718: '0' .. '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__57;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_50;
}
static void cont__types__string__parse_integer_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 718: ... :
  // 719:   !val (val << 4)+(chr-'0')
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__parse_integer_51, 0);
  // 720: 'a' .. 'f'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__102;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_55;
}
static void entry__types__string__parse_integer_51(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // val: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: ... val << 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_52;
}
static void cont__types__string__parse_integer_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 719: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_53;
}
static void cont__types__string__parse_integer_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 719: !val (val << 4)+(chr-'0')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_54;
}
static void cont__types__string__parse_integer_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_integer_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 720: ... :
  // 721:   !val (val << 4)+(chr-'a')+10
  frame->slots[9] /* temp__4 */ = create_closure(entry__types__string__parse_integer_56, 0);
  // 722: 'A' .. 'F'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__65;
  arguments->slots[1] = character__70;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_61;
}
static void entry__types__string__parse_integer_56(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // val: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 721: ... val << 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_57;
}
static void cont__types__string__parse_integer_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 721: ... chr-'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_58;
}
static void cont__types__string__parse_integer_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 721: ... val << 4)+(chr-'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_59;
}
static void cont__types__string__parse_integer_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 721: !val (val << 4)+(chr-'a')+10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_60;
}
static void cont__types__string__parse_integer_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_integer_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 722: ... :
  // 723:   !val (val << 4)+(chr-'A')+10
  frame->slots[11] /* temp__6 */ = create_closure(entry__types__string__parse_integer_62, 0);
  // 724: :
  // 725:   if idx <= 3: return self undefined
  // 726:   range &self idx -1
  // 727:   break
  frame->slots[12] /* temp__7 */ = create_closure(entry__types__string__parse_integer_67, 0);
  // 717: case chr
  // 718:   '0' .. '9':
  // 719:     !val (val << 4)+(chr-'0')
  // 720:   'a' .. 'f':
  // 721:     !val (val << 4)+(chr-'a')+10
  // 722:   'A' .. 'F':
  // 723:     !val (val << 4)+(chr-'A')+10
  // 724:   :
  // 725:     if idx <= 3: return self undefined
  // 726:     range &self idx -1
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  arguments->slots[3] = frame->slots[8] /* temp__3 */;
  arguments->slots[4] = frame->slots[9] /* temp__4 */;
  arguments->slots[5] = frame->slots[10] /* temp__5 */;
  arguments->slots[6] = frame->slots[11] /* temp__6 */;
  arguments->slots[7] = frame->slots[12] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_47(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // val: 1
  // return: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* val */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 716: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_48;
}
static void cont__types__string__parse_integer_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 716: ... : (idx chr)
  // 717:   case chr
  // 718:     '0' .. '9':
  // 719:       !val (val << 4)+(chr-'0')
  // 720:     'a' .. 'f':
  // 721:       !val (val << 4)+(chr-'a')+10
  // 722:     'A' .. 'F':
  // 723:       !val (val << 4)+(chr-'A')+10
  // 724:     :
  // 725:       if idx <= 3: return self undefined
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_49, 2);
  // 716: for_each_from_to self 3 -1: (idx chr)
  // 717:   case chr
  // 718:     '0' .. '9':
  // 719:       !val (val << 4)+(chr-'0')
  // 720:     'a' .. 'f':
  // 721:       !val (val << 4)+(chr-'a')+10
  // 722:     'A' .. 'F':
  // 723:       !val (val << 4)+(chr-'A')+10
  // 724:     :
  // 725:       if idx <= 3: return self undefined
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  arguments->slots[3] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_from_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_33(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // val: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 710: ... val << 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_34;
}
static void cont__types__string__parse_integer_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 710: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_35;
}
static void cont__types__string__parse_integer_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 710: !val (val << 3)+(chr-'0')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_36;
}
static void cont__types__string__parse_integer_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_37(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // idx: 0
  // return: 1
  // self: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] = myself->closure.frame->slots[4]; /* self */
  frame->slots[3] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 712: ... idx <= 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_38;
}
static void cont__types__string__parse_integer_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 712: ... idx <= 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_39;
}
static void cont__types__string__parse_integer_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 712: ... : return self undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__string__parse_integer_40, 0);
  // 712: if idx <= 3: return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_41;
}
static void entry__types__string__parse_integer_40(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 712: ... return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__parse_integer_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 713: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_42;
}
static void cont__types__string__parse_integer_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 713: range &self idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_43;
}
static void cont__types__string__parse_integer_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* self */ = arguments->slots[0];
  // 714: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_31(void) {
  allocate_initialized_frame_gc(6, 9);
  // slot allocations:
  // idx: 0
  // chr: 1
  // val: 2
  // return: 3
  // self: 4
  // break: 5
  frame->slots[2] = myself->closure.frame->slots[1]; /* val */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  frame->slots[5] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 709: '0' .. '7'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__55;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_32;
}
static void cont__types__string__parse_integer_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 709: ... :
  // 710:   !val (val << 3)+(chr-'0')
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__parse_integer_33, 0);
  // 711: :
  // 712:   if idx <= 3: return self undefined
  // 713:   range &self idx -1
  // 714:   break
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__parse_integer_37, 0);
  // 707: case
  // 708:   chr
  // 709:   '0' .. '7':
  // 710:     !val (val << 3)+(chr-'0')
  // 711:   :
  // 712:     if idx <= 3: return self undefined
  // 713:     range &self idx -1
  // 714:     break
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  arguments->slots[3] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_29(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // val: 1
  // return: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* val */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 706: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_30;
}
static void cont__types__string__parse_integer_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 706: ... : (idx chr)
  // 707:   case
  // 708:     chr
  // 709:     '0' .. '7':
  // 710:       !val (val << 3)+(chr-'0')
  // 711:     :
  // 712:       if idx <= 3: return self undefined
  // 713:       range &self idx -1
  // 714:       break
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_31, 2);
  // 706: for_each_from_to self 3 -1: (idx chr)
  // 707:   case
  // 708:     chr
  // 709:     '0' .. '7':
  // 710:       !val (val << 3)+(chr-'0')
  // 711:     :
  // 712:       if idx <= 3: return self undefined
  // 713:       range &self idx -1
  // 714:       break
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  arguments->slots[3] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_from_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_15(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // val: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: ... val << 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_16;
}
static void cont__types__string__parse_integer_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 700: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_17;
}
static void cont__types__string__parse_integer_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 700: !val (val << 1)+(chr-'0')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_18;
}
static void cont__types__string__parse_integer_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_19(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // idx: 0
  // return: 1
  // self: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] = myself->closure.frame->slots[4]; /* self */
  frame->slots[3] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 702: ... idx <= 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_20;
}
static void cont__types__string__parse_integer_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 702: ... idx <= 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_21;
}
static void cont__types__string__parse_integer_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 702: ... : return self undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__string__parse_integer_22, 0);
  // 702: if idx <= 3: return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_23;
}
static void entry__types__string__parse_integer_22(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 702: ... return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__parse_integer_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 703: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_24;
}
static void cont__types__string__parse_integer_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 703: range &self idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_25;
}
static void cont__types__string__parse_integer_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* self */ = arguments->slots[0];
  // 704: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_13(void) {
  allocate_initialized_frame_gc(6, 9);
  // slot allocations:
  // idx: 0
  // chr: 1
  // val: 2
  // return: 3
  // self: 4
  // break: 5
  frame->slots[2] = myself->closure.frame->slots[1]; /* val */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  frame->slots[5] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 699: '0' .. '1'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__49;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_14;
}
static void cont__types__string__parse_integer_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 699: ... :
  // 700:   !val (val << 1)+(chr-'0')
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__parse_integer_15, 0);
  // 701: :
  // 702:   if idx <= 3: return self undefined
  // 703:   range &self idx -1
  // 704:   break
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__parse_integer_19, 0);
  // 697: case
  // 698:   chr
  // 699:   '0' .. '1':
  // 700:     !val (val << 1)+(chr-'0')
  // 701:   :
  // 702:     if idx <= 3: return self undefined
  // 703:     range &self idx -1
  // 704:     break
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  arguments->slots[3] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_11(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // val: 1
  // return: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* val */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 696: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_12;
}
static void cont__types__string__parse_integer_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 696: ... : (idx chr)
  // 697:   case
  // 698:     chr
  // 699:     '0' .. '1':
  // 700:       !val (val << 1)+(chr-'0')
  // 701:     :
  // 702:       if idx <= 3: return self undefined
  // 703:       range &self idx -1
  // 704:       break
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_13, 2);
  // 696: for_each_from_to self 3 -1: (idx chr)
  // 697:   case
  // 698:     chr
  // 699:     '0' .. '1':
  // 700:       !val (val << 1)+(chr-'0')
  // 701:     :
  // 702:       if idx <= 3: return self undefined
  // 703:       range &self idx -1
  // 704:       break
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  arguments->slots[3] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_from_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_integer_8(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // val: 1
  // return: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* val */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 695: ... self .has_prefix. "0b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = string__2d7981f4e6882ba7;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_10;
}
static void cont__types__string__parse_integer_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 695: ... :
  // 696:   for_each_from_to self 3 -1: (idx chr)
  // 697:     case
  // 698:       chr
  // 699:       '0' .. '1':
  // 700:         !val (val << 1)+(chr-'0')
  // 701:       :
  // 702:         if idx <= 3: return self undefined
  // 703:         range &self idx -1
  // 704:         break
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_11, 0);
  // 695: -> self .has_prefix. "0b":
  // 696:   for_each_from_to self 3 -1: (idx chr)
  // 697:     case
  // 698:       chr
  // 699:       '0' .. '1':
  // 700:         !val (val << 1)+(chr-'0')
  // 701:       :
  // 702:         if idx <= 3: return self undefined
  // 703:         range &self idx -1
  // 704:         break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_26(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // val: 1
  // return: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* val */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 705: ... self .has_prefix. "0o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = string__2d7981f4e6882baa;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_28;
}
static void cont__types__string__parse_integer_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 705: ... :
  // 706:   for_each_from_to self 3 -1: (idx chr)
  // 707:     case
  // 708:       chr
  // 709:       '0' .. '7':
  // 710:         !val (val << 3)+(chr-'0')
  // 711:       :
  // 712:         if idx <= 3: return self undefined
  // 713:         range &self idx -1
  // 714:         break
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_29, 0);
  // 705: -> self .has_prefix. "0o":
  // 706:   for_each_from_to self 3 -1: (idx chr)
  // 707:     case
  // 708:       chr
  // 709:       '0' .. '7':
  // 710:         !val (val << 3)+(chr-'0')
  // 711:       :
  // 712:         if idx <= 3: return self undefined
  // 713:         range &self idx -1
  // 714:         break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_44(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // val: 1
  // return: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* val */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 715: ... self .has_prefix. "0x"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = string__2d7981f4e6882bbd;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_46;
}
static void cont__types__string__parse_integer_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 715: ... :
  // 716:   for_each_from_to self 3 -1: (idx chr)
  // 717:     case chr
  // 718:       '0' .. '9':
  // 719:         !val (val << 4)+(chr-'0')
  // 720:       'a' .. 'f':
  // 721:         !val (val << 4)+(chr-'a')+10
  // 722:       'A' .. 'F':
  // 723:         !val (val << 4)+(chr-'A')+10
  // 724:       :
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_47, 0);
  // 715: -> self .has_prefix. "0x":
  // 716:   for_each_from_to self 3 -1: (idx chr)
  // 717:     case chr
  // 718:       '0' .. '9':
  // 719:         !val (val << 4)+(chr-'0')
  // 720:       'a' .. 'f':
  // 721:         !val (val << 4)+(chr-'a')+10
  // 722:       'A' .. 'F':
  // 723:         !val (val << 4)+(chr-'A')+10
  // 724:       :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_74(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // self: 0
  // val: 1
  // return: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* val */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 729: ... : (idx chr)
  // 730:   case
  // 731:     chr
  // 732:     '0' .. '9':
  // 733:       !val 10*val+(chr-'0')
  // 734:     :
  // 735:       if idx <= 1: return self undefined
  // 736:       range &self idx -1
  // 737:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__string__parse_integer_75, 2);
  // 729: for_each self: (idx chr)
  // 730:   case
  // 731:     chr
  // 732:     '0' .. '9':
  // 733:       !val 10*val+(chr-'0')
  // 734:     :
  // 735:       if idx <= 1: return self undefined
  // 736:       range &self idx -1
  // 737:       break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__parse_integer_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 738: !self ""
  ((CELL *)frame->slots[1])->contents /* self */ = empty_string;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_integer_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 743: -> -val
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__parse_integer_90, 0);
  // 744: -> val
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__string__parse_integer_92, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* negate */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_93;
}
static void entry__types__string__parse_integer_90(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // val: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 743: ... val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__parse_integer_91;
}
static void cont__types__string__parse_integer_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 743: -> -val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_integer_92(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // val: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_integer_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 739: ->
  // 740:   self
  // 741:   if
  // 742:     negate
  // 743:     -> -val
  // 744:     -> val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}

static long func__types__octet_string___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  long len = 0;
  if (indent < 0) {
    if (buf) *buf++ = ' ';
    ++len;
  }
  if (buf) *buf++ = '\"';
  ++len;
  long i;
  long s = node->octet_string.offset;
  long e = s+node->octet_string.length;
  for (i = s; i < e; ++i) {
    uint8_t chr = node->octet_string.data->buffer[i];
    if (chr >= 0x20 && chr <= 0x7e || chr >= 0xa0 && chr < 0xff) {
      if (chr == '\"') {
        len += print(&buf, "@quot;");
      } else if (chr == '@') {
        len += print(&buf, "@@");
      } else {
        if (buf) *buf++ = chr;
        ++len;
      }
    } else {
      len += print(&buf, "@0x%x;", chr);
    }
  }
  len += print(&buf, "\"\n");
  return len;
}

static long func__types__quad_octet_string___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  long len = 0;
  if (indent < 0) {
    if (buf) *buf++ = ' ';
    ++len;
  }
  if (buf) *buf++ = '\"';
  ++len;
  long i;
  long s = node->quad_octet_string.offset;
  long e = s+node->quad_octet_string.length;
  for (i = s; i < e; ++i) {
    uint32_t chr = node->quad_octet_string.data->buffer[i];
    if (chr >= 0x20 && chr <= 0x7e || chr >= 0xa0 && chr < 0xff) {
      if (chr == '\"') {
        len += print(&buf, "@quot;");
      } else if (chr == '@') {
        len += print(&buf, "@@");
      } else {
        if (buf) *buf++ = chr;
        ++len;
      }
    } else {
      len += print(&buf, "@0x%x;", chr);
    }
  }
  len += print(&buf, "\"\n");
  return len;
}
static void entry__types__octet_string__push_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  uint32_t chr_code = to_uchar32(arguments->slots[1]);
  NODE *left = arguments->slots[0];
  long left_start_offset = left->octet_string.offset;
  long left_length = left->octet_string.length;
  long left_end_offset = left_start_offset+left_length;
  long new_length = left_length+1;
  OCTET_DATA *data = left->octet_string.data;
  if (chr_code <= 0xff) {
    if (!data || data->size < left_end_offset+1 || data->length != left_end_offset) {
      long new_size = ALLOCATION_SIZE(2*new_length);
      OCTET_DATA *new_data = allocate_large(sizeof(OCTET_DATA)+new_size);
      if (data) {
        memcpy(
          new_data->buffer,
          data->buffer+left_start_offset,
          left_length);
      }
      left_start_offset = 0;
      left_end_offset = left_length;
      new_data->size = new_size;
      data = new_data;
    }
    data->buffer[left_end_offset] = (uint8_t)chr_code;
    data->length = left_end_offset+1;
    {
    NODE *result__node = (NODE *)(create__types__octet_string(left_start_offset, new_length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    long new_size = ALLOCATION_SIZE(4*2*new_length);
    QUAD_OCTET_DATA *new_data = allocate_large(sizeof(QUAD_OCTET_DATA)+new_size);
    new_data->size = new_size;
    new_data->length = new_length;
    if (data) {
      long idx;
      for (idx = 0; idx < left_length; ++idx) {
        new_data->buffer[idx] = data->buffer[left_start_offset+idx];
      }
    }
    new_data->buffer[left_length] = chr_code;
    {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(0, new_length, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static void entry__types__quad_octet_string__push_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  uint32_t chr_code = to_uchar32(arguments->slots[1]);
  NODE *left = arguments->slots[0];
  long left_start_offset = left->quad_octet_string.offset;
  long left_length = left->quad_octet_string.length;
  long left_end_offset = left_start_offset+left_length;
  long new_length = left_length+1;
  QUAD_OCTET_DATA *data = left->quad_octet_string.data;
  if (!data || data->size < 4*(left_end_offset+1) || data->length != left_end_offset) {
    long new_size = ALLOCATION_SIZE(4*2*new_length);
    QUAD_OCTET_DATA *new_data = allocate_large(sizeof(QUAD_OCTET_DATA)+new_size);
    if (data) {
      memcpy(
        new_data->buffer,
        data->buffer+left_start_offset,
        4*left_length);
    }
    left_start_offset = 0;
    left_end_offset = left_length;
    new_data->size = new_size;
    data = new_data;
  }
  data->buffer[left_end_offset] = chr_code;
  data->length = left_end_offset+1;
  {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(left_start_offset, new_length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__octet_string__append_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *left = arguments->slots[0];
  NODE *right = arguments->slots[1];
  long left_offset = left->octet_string.offset;
  long left_length = left->octet_string.length;
  long right_length = right->octet_string.length;
  long new_length = left_length+right_length;
  OCTET_DATA *data = left->octet_string.data;
  if ((right)->type == type__types__octet_string) {
    if (left_length == 0) {
    NODE *result__node = (NODE *)(right);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    if (right_length == 0) {
    NODE *result__node = (NODE *)(left);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    if (data->size < left_offset+new_length || data->length != left_offset+left_length) {
      long new_size = ALLOCATION_SIZE(2*new_length);
      OCTET_DATA *new_data = allocate_large(sizeof(OCTET_DATA)+new_size);
      memcpy(new_data->buffer, data->buffer+left_offset, left_length);
      left_offset = 0;
      new_data->size = new_size;
      data = new_data;
    }
    memcpy(
      data->buffer+left_offset+left_length,
      right->octet_string.data->buffer+right->octet_string.offset,
      right_length);
    data->length = left_offset+new_length;
    {
    NODE *result__node = (NODE *)(create__types__octet_string(left_offset, new_length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((right)->type == type__types__quad_octet_string) {
    if (left_length == 0) {
    NODE *result__node = (NODE *)(right);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    long new_size = ALLOCATION_SIZE(4*2*new_length);
    QUAD_OCTET_DATA *new_data = allocate_large(sizeof(QUAD_OCTET_DATA)+new_size);
    new_data->size = new_size;
    new_data->length = new_length;
    long idx;
    for (idx = 0; idx < left_length; ++idx) {
      new_data->buffer[idx] = data->buffer[left_offset+idx];
    }
    memcpy(
      new_data->buffer+left_length,
      right->quad_octet_string.data->buffer+right->quad_octet_string.offset,
      4*right_length);
    {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(0, new_length, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    {
    invalid_arguments_error();
  }
  }
}
static void entry__types__quad_octet_string__append_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *left = arguments->slots[0];
  NODE *right = arguments->slots[1];
  long left_offset = left->quad_octet_string.offset;
  long left_length = left->quad_octet_string.length;
  long right_length = right->quad_octet_string.length;
  long new_length = left_length+right_length;
  QUAD_OCTET_DATA *data = left->quad_octet_string.data;
  if ((right)->type == type__types__octet_string) {
    if (right_length == 0) {
    NODE *result__node = (NODE *)(left);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    if (data->size < 4*(left_offset+new_length) || data->length != left_offset+left_length) {
      long new_size = ALLOCATION_SIZE(4*2*new_length);
      QUAD_OCTET_DATA *new_data = allocate_large(sizeof(QUAD_OCTET_DATA)+new_size);
      memcpy(new_data->buffer, data->buffer+left_offset, 4*left_length);
      left_offset = 0;
      new_data->size = new_size;
      data = new_data;
    }
    long src_idx = left_offset+left_length;
    long dest_idx = right->octet_string.offset;
    while (--right_length >= 0) {
      data->buffer[src_idx++] = right->octet_string.data->buffer[dest_idx++];
    }
    data->length = left_offset+new_length;
    {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(left_offset, new_length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((right)->type == type__types__quad_octet_string) {
    if (data->size < 4*(left_offset+new_length) || data->length != left_offset+left_length) {
      long new_size = ALLOCATION_SIZE(4*2*new_length);
      QUAD_OCTET_DATA *new_data = allocate_large(sizeof(QUAD_OCTET_DATA)+new_size);
      memcpy(new_data->buffer, data->buffer+left_offset, 4*left_length);
      left_offset = 0;
      new_data->size = new_size;
      data = new_data;
    }
    memcpy(
      data->buffer+left_offset+left_length,
      right->quad_octet_string.data->buffer+right->quad_octet_string.offset,
      4*right_length);
    data->length = left_offset+new_length;
    {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(left_offset, new_length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    {
    invalid_arguments_error();
  }
  }
}
static void entry__types__string__parse_real_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char *str = to_c_string(arguments->slots[0]);
  char *end;
  double result = strtod(str, &end);
  NODE *value = from_double(result);
  NODE *remaining_str = from_c_string(end);
  deallocate_memory(str);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = remaining_str;
  arguments->slots[1] = value;
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__octet_string__range_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  long first_idx = to_long(arguments->slots[1]);
  long last_idx = to_long(arguments->slots[2]);
  long len = self->octet_string.length;
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
    NODE *result__node = (NODE *)(empty_string);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__octet_string(
      self->octet_string.offset+first_idx-1, new_len, self->octet_string.data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__quad_octet_string__range_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  long first_idx = to_long(arguments->slots[1]);
  long last_idx = to_long(arguments->slots[2]);
  long len = self->octet_string.length;
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
    NODE *result__node = (NODE *)(empty_string);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  long idx;
  long offset = self->quad_octet_string.offset;
  QUAD_OCTET_DATA *data = self->quad_octet_string.data;
  for (idx = first_idx-1; idx < last_idx; ++idx) {
    if (data->buffer[offset+idx] > 0xff) {
      {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(offset+first_idx-1, new_len, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    }
  }
  long new_size = ALLOCATION_SIZE(new_len);
  OCTET_DATA *new_data = allocate_large(sizeof(OCTET_DATA)+new_size);
  new_data->size = new_size;
  new_data->length = new_len;
  offset += first_idx-1;
  for (idx = 0; idx < new_len; ++idx) {
    new_data->buffer[idx] = data->buffer[idx+offset];
  }
  {
    NODE *result__node = (NODE *)(create__types__octet_string(0, new_len, new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__std__matches_file_pattern_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  char *filename = to_c_string(arguments->slots[0]);
  char *pattern = to_c_string(arguments->slots[1]);
  int ret = fnmatch(pattern, filename, 0);
  deallocate_memory(pattern);
  deallocate_memory(filename);
  {
    NODE *result__node = (NODE *)(from_bool(ret == 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}
static void entry__types__octet_string__is_a_latin_1_string_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__quad_octet_string__is_a_latin_1_string_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__std__from_utf8_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  uint8_t *buf = (unsigned char *)to_c_string(arguments->slots[0]);
  long length = 0;
  long src_idx, dest_idx;
  int is_latin_1 = true;
  uint8_t chr;
  // check vor valid utf-8 encoding
  // the allowed maximum size is 32 bits instead of 21 bits!
  src_idx = 0;
  while (chr = buf[src_idx++]) {
    int n; // number of continuation octets
    if (chr >= 0x80) {
      if ((chr & 0xe0) == 0xc0) { // 2 byte code
        if (chr & 0x3c) is_latin_1 = false; // more than 8 bits
        n = 1;
      } else if ((chr & 0xf0) == 0xe0) { // 3 byte code
        is_latin_1 = false;
        n = 2;
      } else if ((chr & 0xf8) == 0xf0) { // 4 byte code
        is_latin_1 = false;
        n = 3;
      } else if ((chr & 0xfc) == 0xf8) { // 5 byte code
        is_latin_1 = false;
        n = 4;
      } else if ((chr & 0xfe) == 0xfc) { // 6 byte code
        is_latin_1 = false;
        n = 5;
      } else if (chr == 0xfe) { // 7 byte code
        if (buf[src_idx] & 0x3e) {
    invalid_arguments_error();
  } // more than 32 bits
        is_latin_1 = false;
        n = 6;
      } else {
    invalid_arguments_error();
  }
      while (--n >= 0) {
        chr = buf[src_idx++];
        if ((chr & 0xc0) != 0x80) {
    invalid_arguments_error();
  }
      }
    }
    ++length;
  }
  if (is_latin_1) {
    long size = ALLOCATION_SIZE(length);
    OCTET_DATA *data = allocate_large(sizeof(OCTET_DATA)+size);
    data->size = size;
    data->length = length;
    src_idx = 0;
    for (dest_idx = 0; dest_idx < length; ++dest_idx) {
      uint8_t chr;
      chr = buf[src_idx++];
      if (chr >= 0x80) {
        chr = ((chr & 0x1f) << 6) | (buf[src_idx++] & 0x3f);
      }
      data->buffer[dest_idx] = chr;
    }
    deallocate_memory(buf);
    {
    NODE *result__node = (NODE *)(create__types__octet_string(0, length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    long size = ALLOCATION_SIZE(4*length);
    QUAD_OCTET_DATA *data = allocate_large(sizeof(QUAD_OCTET_DATA)+size);
    data->size = size;
    data->length = length;
    src_idx = 0;
    for (dest_idx = 0; dest_idx < length; ++dest_idx) {
      uint32_t chr;
      chr = buf[src_idx++];
      if (chr >= 0x80) {
        int n; // number of continuation octets
        if ((chr & 0xe0) == 0xc0) { // 2 byte code
          chr &= 0x1f;
          n = 1;
        } else if ((chr & 0xf0) == 0xe0) { // 3 byte code
          chr &= 0x0f;
          n = 2;
        } else if ((chr & 0xf8) == 0xf0) { // 4 byte code
          chr &= 0x07;
          n = 3;
        } else if ((chr & 0xfc) == 0xf8) { // 5 byte code
          chr &= 0x03;
          n = 4;
        } else if ((chr & 0xfe) == 0xfc) { // 6 byte code
          chr &= 0x01;
          n = 5;
        } else { // 7 byte code
          chr = 0;
          n = 6;
        }
        while (--n >= 0) {
          chr = (chr << 6) | (buf[src_idx++] & 0x3f);
        }
      }
      data->buffer[dest_idx] = chr;
    }
    deallocate_memory(buf);
    {
    NODE *result__node = (NODE *)(create__types__quad_octet_string(0, length, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static void entry__types__octet_string__to_utf8_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  long offset = self->octet_string.offset;
  long len = self->octet_string.length;
  long new_len = len;
  uint8_t *src = self->octet_string.data->buffer+offset;
  long i;
  for(i = 0; i < len; ++i) {
    uint8_t chr = src[i];
    if (chr >= 0x80) {
      ++new_len;
    }
  }
  long size = ALLOCATION_SIZE(new_len);
  OCTET_DATA *data = allocate_large(sizeof(OCTET_DATA)+size);
  data->size = size;
  data->length = new_len;
  uint8_t *dst = data->buffer;
  for(i = 0; i < len; ++i) {
    uint8_t chr = src[i];
    if (chr >= 0x80) {
      *dst++ = chr >> 6 | 0xc0;
      *dst++ = chr & 0x3f | 0x80;
    } else {
      *dst++ = chr;
    }
  }
  {
    NODE *result__node = (NODE *)(create__types__octet_string(0, new_len, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__quad_octet_string__to_utf8_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *self = arguments->slots[0];
  long offset = self->quad_octet_string.offset;
  long len = self->quad_octet_string.length;
  long new_len = len;
  uint32_t *src = self->quad_octet_string.data->buffer+offset;
  long i;
  for(i = 0; i < len; ++i) {
    uint32_t chr = src[i];
    if (chr >= 0x80) {
      if (chr >= 0x800) {
        if (chr >= 0x10000) {
          if (chr >= 0x200000) {
            if (chr >= 0x4000000) {
              if (chr >= 0x80000000) {
                new_len += 6;
              } else {
                new_len += 5;
              }
            } else {
              new_len += 4;
            }
          } else {
            new_len += 3;
          }
        } else {
          new_len += 2;
        }
      } else {
        ++new_len;
      }
    }
  }
  long size = ALLOCATION_SIZE(new_len);
  OCTET_DATA *data = allocate_large(sizeof(OCTET_DATA)+size);
  data->size = size;
  data->length = new_len;
  uint8_t *dst = data->buffer;
  for(i = 0; i < len; ++i) {
    uint32_t chr = src[i];
    if (chr >= 0x80) {
      if (chr >= 0x800) {
        if (chr >= 0x10000) {
          if (chr >= 0x200000) {
            if (chr >= 0x4000000) {
              if (chr >= 0x80000000) {
                *dst++ = 0xfe;
                *dst++ = (chr >> 30) & 0x3f | 0x80;
                *dst++ = (chr >> 24) & 0x3f | 0x80;
                *dst++ = (chr >> 18) & 0x3f | 0x80;
                *dst++ = (chr >> 12) & 0x3f | 0x80;
                *dst++ = (chr >> 6) & 0x3f | 0x80;
                *dst++ = chr & 0x3f | 0x80;
              } else {
                *dst++ = chr >> 30 | 0xfc0;
                *dst++ = (chr >> 24) & 0x3f | 0x80;
                *dst++ = (chr >> 18) & 0x3f | 0x80;
                *dst++ = (chr >> 12) & 0x3f | 0x80;
                *dst++ = (chr >> 6) & 0x3f | 0x80;
                *dst++ = chr & 0x3f | 0x80;
              }
            } else {
              *dst++ = chr >> 24 | 0xf8;
              *dst++ = (chr >> 18) & 0x3f | 0x80;
              *dst++ = (chr >> 12) & 0x3f | 0x80;
              *dst++ = (chr >> 6) & 0x3f | 0x80;
              *dst++ = chr & 0x3f | 0x80;
            }
          } else {
            *dst++ = chr >> 18 | 0xf0;
            *dst++ = (chr >> 12) & 0x3f | 0x80;
            *dst++ = (chr >> 6) & 0x3f | 0x80;
            *dst++ = chr & 0x3f | 0x80;
          }
        } else {
          *dst++ = chr >> 12 | 0xe0;
          *dst++ = (chr >> 6) & 0x3f | 0x80;
          *dst++ = chr & 0x3f | 0x80;
        }
      } else {
        *dst++ = chr >> 6 | 0xc0;
        *dst++ = chr & 0x3f | 0x80;
      }
    } else {
      *dst++ = chr;
    }
  }
  {
    NODE *result__node = (NODE *)(create__types__octet_string(0, new_len, data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
EXPORT void collect__basic__types__string_primitives(void) {
  var.std__is_a_string = collect_node(var.std__is_a_string);
  var.std__count_character_occurrences = collect_node(var.std__count_character_occurrences);
  var.std__to_utf8 = collect_node(var.std__to_utf8);
  var.std__is_a_latin_1_string = collect_node(var.std__is_a_latin_1_string);
  var.types__string = collect_node(var.types__string);
  var.types__octet_string = collect_node(var.types__octet_string);
  collect_static_attributes(&attributes__types__octet_string);
  var.types__quad_octet_string = collect_node(var.types__quad_octet_string);
  collect_static_attributes(&attributes__types__quad_octet_string);
  var.std__empty_string = collect_node(var.std__empty_string);
  var.std__matches_file_pattern = collect_node(var.std__matches_file_pattern);
  var.std__from_utf8 = collect_node(var.std__from_utf8);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__string_primitives(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_c_function("from_latin_1_string", runtime__from_latin_1_string);
  define_c_function("from_uint32_string", runtime__from_uint32_string);
  define_c_function("from_c_string", runtime__from_c_string);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__string_primitives(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__string_primitives");
  character__57 = from_uchar32(57);
  character__55 = from_uchar32(55);
  character__65 = from_uchar32(65);
  character__45 = from_uchar32(45);
  number__0 = from_uint32(0U);
  character__70 = from_uchar32(70);
  number__3 = from_uint32(3U);
  character__48 = from_uchar32(48);
  character__102 = from_uchar32(102);
  number__4 = from_uint32(4U);
  character__126 = from_uchar32(126);
  character__64 = from_uchar32(64);
  character__34 = from_uchar32(34);
  character__39 = from_uchar32(39);
  character__32 = from_uchar32(32);
  character__97 = from_uchar32(97);
  character__59 = from_uchar32(59);
  number__1 = from_uint32(1U);
  character__49 = from_uchar32(49);
  number__2 = from_uint32(2U);
  number__10 = from_uint32(10U);
  define_polymorphic_function("std", "is_a_string", get__std__is_a_string, &poly_idx__std__is_a_string, &var.std__is_a_string);
  define_polymorphic_function("std", "count_character_occurrences", get__std__count_character_occurrences, &poly_idx__std__count_character_occurrences, &var.std__count_character_occurrences);
  define_polymorphic_function("std", "to_utf8", get__std__to_utf8, &poly_idx__std__to_utf8, &var.std__to_utf8);
  define_polymorphic_function("std", "is_a_latin_1_string", get__std__is_a_latin_1_string, &poly_idx__std__is_a_latin_1_string, &var.std__is_a_latin_1_string);
  func__types__octet_string__length_of_1 = create_function(entry__types__octet_string__length_of_1, 1);
  func__types__quad_octet_string__length_of_1 = create_function(entry__types__quad_octet_string__length_of_1, 1);
  func__types__octet_string__equal_1 = create_function(entry__types__octet_string__equal_1, 2);
  func__types__quad_octet_string__equal_1 = create_function(entry__types__quad_octet_string__equal_1, 2);
  func__types__octet_string__count_character_occurrences_1 = create_function(entry__types__octet_string__count_character_occurrences_1, 2);
  func__types__quad_octet_string__count_character_occurrences_1 = create_function(entry__types__quad_octet_string__count_character_occurrences_1, 2);
  func__types__octet_string__less_1 = create_function(entry__types__octet_string__less_1, 2);
  func__types__quad_octet_string__less_1 = create_function(entry__types__quad_octet_string__less_1, 2);
  func__types__octet_string__hash_1 = create_function(entry__types__octet_string__hash_1, 1);
  func__types__octet_string__hash2_1 = create_function(entry__types__octet_string__hash2_1, 1);
  func__types__quad_octet_string__hash_1 = create_function(entry__types__quad_octet_string__hash_1, 1);
  func__types__quad_octet_string__hash2_1 = create_function(entry__types__quad_octet_string__hash2_1, 1);
  func__types__string__to_string_1 = create_function(entry__types__string__to_string_1, 1);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__fa728415fa96bb4 = from_latin_1_string("@0x", 3);
  func__types__string__serialize_1 = create_function(entry__types__string__serialize_1, -1);
  string__2d7981f4e6882ba7 = from_latin_1_string("0b", 2);
  string__2d7981f4e6882baa = from_latin_1_string("0o", 2);
  string__2d7981f4e6882bbd = from_latin_1_string("0x", 2);
  func__types__string__parse_integer_1 = create_function(entry__types__string__parse_integer_1, 1);
  func__types__octet_string__push_1 = create_function(entry__types__octet_string__push_1, 2);
  func__types__quad_octet_string__push_1 = create_function(entry__types__quad_octet_string__push_1, 2);
  func__types__octet_string__append_1 = create_function(entry__types__octet_string__append_1, 2);
  func__types__quad_octet_string__append_1 = create_function(entry__types__quad_octet_string__append_1, 2);
  func__types__string__parse_real_1 = create_function(entry__types__string__parse_real_1, 1);
  func__types__octet_string__range_1 = create_function(entry__types__octet_string__range_1, 3);
  func__types__quad_octet_string__range_1 = create_function(entry__types__quad_octet_string__range_1, 3);
  func__std__matches_file_pattern_1 = create_function(entry__std__matches_file_pattern_1, 2);
  func__types__octet_string__is_a_latin_1_string_1 = create_function(entry__types__octet_string__is_a_latin_1_string_1, 1);
  func__types__quad_octet_string__is_a_latin_1_string_1 = create_function(entry__types__quad_octet_string__is_a_latin_1_string_1, 1);
  func__std__from_utf8_1 = create_function(entry__std__from_utf8_1, 1);
  func__types__octet_string__to_utf8_1 = create_function(entry__types__octet_string__to_utf8_1, 1);
  func__types__quad_octet_string__to_utf8_1 = create_function(entry__types__quad_octet_string__to_utf8_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__string_primitives(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__string_primitives");
  set_used_namespaces(used_namespaces);
  var.types__string = create_future();
  define_single_assign_static("types", "string", get__types__string, &var.types__string);
  var.types__octet_string = create_future_with_prototype(create__types__octet_string(0, 0, NULL));
  define_single_assign_static("types", "octet_string", get__types__octet_string, &var.types__octet_string);
  var.types__quad_octet_string = create_future_with_prototype(create__types__quad_octet_string(0, 0, NULL));
  define_single_assign_static("types", "quad_octet_string", get__types__quad_octet_string, &var.types__quad_octet_string);
  var.std__empty_string = create__types__octet_string(0, 0, NULL);
  define_single_assign_static("std", "empty_string", get__std__empty_string, &var.std__empty_string);
  var.std__matches_file_pattern = create_future();
  define_single_assign_static("std", "matches_file_pattern", get__std__matches_file_pattern, &var.std__matches_file_pattern);
  var.std__from_utf8 = create_future();
  define_single_assign_static("std", "from_utf8", get__std__from_utf8, &var.std__from_utf8);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__string_primitives(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__string_primitives");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "append", &get__append, &poly_idx__append);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_polymorphic_function(NULL, "count_character_occurrences", &get__count_character_occurrences, &poly_idx__count_character_occurrences);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "for_each_from_to", &get__for_each_from_to, &get_value_or_future__for_each_from_to);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_polymorphic_function(NULL, "hash", &get__hash, &poly_idx__hash);
  use_polymorphic_function(NULL, "hash2", &get__hash2, &poly_idx__hash2);
  use_read_only(NULL, "hex", &get__hex, &get_value_or_future__hex);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "is_a_latin_1_string", &get__is_a_latin_1_string, &poly_idx__is_a_latin_1_string);
  use_polymorphic_function(NULL, "is_a_string", &get__is_a_string, &poly_idx__is_a_string);
  use_polymorphic_function(NULL, "length_of", &get__length_of, &poly_idx__length_of);
  use_polymorphic_function(NULL, "less", &get__less, &poly_idx__less);
  use_polymorphic_function(NULL, "parse_integer", &get__parse_integer, &poly_idx__parse_integer);
  use_polymorphic_function(NULL, "parse_real", &get__parse_real, &poly_idx__parse_real);
  use_polymorphic_function(NULL, "push", &get__push, &poly_idx__push);
  use_polymorphic_function(NULL, "range", &get__range, &poly_idx__range);
  use_polymorphic_function(NULL, "serialize", &get__serialize, &poly_idx__serialize);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "shift_left", &get__std__shift_left, &get_value_or_future__std__shift_left);
  use_read_only("std", "times", &get__std__times, &get_value_or_future__std__times);
  use_read_only("std", "value_range", &get__std__value_range, &get_value_or_future__std__value_range);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "to_integer", &get__to_integer, &get_value_or_future__to_integer);
  use_polymorphic_function(NULL, "to_string", &get__to_string, &poly_idx__to_string);
  use_polymorphic_function(NULL, "to_utf8", &get__to_utf8, &poly_idx__to_utf8);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "generic_list", &get__types__generic_list, &get_value_or_future__types__generic_list);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  define_attribute("types", "object", poly_idx__is_a_string, get__false());
  define_attribute("types", "string", poly_idx__is_a_string, get__true());
  define_method("types", "octet_string", poly_idx__length_of, func__types__octet_string__length_of_1);
  define_method("types", "quad_octet_string", poly_idx__length_of, func__types__quad_octet_string__length_of_1);
  define_method("types", "octet_string", poly_idx__equal, func__types__octet_string__equal_1);
  define_method("types", "quad_octet_string", poly_idx__equal, func__types__quad_octet_string__equal_1);
  define_method("types", "octet_string", poly_idx__count_character_occurrences, func__types__octet_string__count_character_occurrences_1);
  define_method("types", "quad_octet_string", poly_idx__count_character_occurrences, func__types__quad_octet_string__count_character_occurrences_1);
  define_method("types", "octet_string", poly_idx__less, func__types__octet_string__less_1);
  define_method("types", "quad_octet_string", poly_idx__less, func__types__quad_octet_string__less_1);
  define_method("types", "octet_string", poly_idx__hash, func__types__octet_string__hash_1);
  define_method("types", "octet_string", poly_idx__hash2, func__types__octet_string__hash2_1);
  define_method("types", "quad_octet_string", poly_idx__hash, func__types__quad_octet_string__hash_1);
  define_method("types", "quad_octet_string", poly_idx__hash2, func__types__quad_octet_string__hash2_1);
  define_method("types", "string", poly_idx__to_string, func__types__string__to_string_1);
  define_method("types", "string", poly_idx__serialize, func__types__string__serialize_1);
  define_method("types", "string", poly_idx__parse_integer, func__types__string__parse_integer_1);
  define_method("types", "octet_string", poly_idx__push, func__types__octet_string__push_1);
  define_method("types", "quad_octet_string", poly_idx__push, func__types__quad_octet_string__push_1);
  define_method("types", "octet_string", poly_idx__append, func__types__octet_string__append_1);
  define_method("types", "quad_octet_string", poly_idx__append, func__types__quad_octet_string__append_1);
  define_method("types", "string", poly_idx__parse_real, func__types__string__parse_real_1);
  define_method("types", "octet_string", poly_idx__range, func__types__octet_string__range_1);
  define_method("types", "quad_octet_string", poly_idx__range, func__types__quad_octet_string__range_1);
  define_method("types", "octet_string", poly_idx__is_a_latin_1_string, func__types__octet_string__is_a_latin_1_string_1);
  define_method("types", "quad_octet_string", poly_idx__is_a_latin_1_string, func__types__quad_octet_string__is_a_latin_1_string_1);
  define_method("types", "octet_string", poly_idx__to_utf8, func__types__octet_string__to_utf8_1);
  define_method("types", "quad_octet_string", poly_idx__to_utf8, func__types__quad_octet_string__to_utf8_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__string_primitives(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_string, create_function(type__std__is_a_string, -1));
  assign_value(&var.std__count_character_occurrences, create_function(type__std__count_character_occurrences, -1));
  assign_value(&var.std__to_utf8, create_function(type__std__to_utf8, -1));
  assign_value(&var.std__is_a_latin_1_string, create_function(type__std__is_a_latin_1_string, -1));
  initialize_future(var.types__string, get__types__generic_list());
  assign_variable(&var.types__octet_string, &var.types__string);
  assign_variable(&var.types__quad_octet_string, &var.types__string);
  initialize_future(var.std__matches_file_pattern, func__std__matches_file_pattern_1);
  initialize_future(var.std__from_utf8, func__std__from_utf8_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__string_primitives(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__string_primitives);
}
