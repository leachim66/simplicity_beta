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
REGISTER NODE *myself ASM("r13");
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
IMPORT void too_few_arguments_error(void);
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
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_c_function(const char *name, void *func);
IMPORT NODE *from_uint32_string(const uint32_t *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
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
static void entry__24_1_types__octet_string_length_of(void);
static NODE *func__24_1_types__octet_string_length_of;
static void entry__25_1_types__quad_octet_string_length_of(void);
static NODE *func__25_1_types__quad_octet_string_length_of;
static void entry__26_1_types__octet_string_equal(void);
static NODE *func__26_1_types__octet_string_equal;
static void entry__27_1_types__quad_octet_string_equal(void);
static NODE *func__27_1_types__quad_octet_string_equal;
static void entry__28_1_types__octet_string_count_character_occurrences(void);
static NODE *func__28_1_types__octet_string_count_character_occurrences;
static void entry__29_1_types__quad_octet_string_count_character_occurrences(void);
static NODE *func__29_1_types__quad_octet_string_count_character_occurrences;
static void entry__30_1_types__octet_string_less(void);
static NODE *func__30_1_types__octet_string_less;
static void entry__31_1_types__quad_octet_string_less(void);
static NODE *func__31_1_types__quad_octet_string_less;
static void entry__32_1_types__octet_string_hash(void);
static NODE *func__32_1_types__octet_string_hash;
static void entry__33_1_types__quad_octet_string_hash(void);
static NODE *func__33_1_types__quad_octet_string_hash;
static NODE *func__34_1_types__string_to_string;
static void entry__34_1_types__string_to_string(void);
static FRAME_INFO frame__34_1_types__string_to_string = {1, {"self"}};
static NODE *func__35_1_types__string_serialize;
static void entry__35_1_types__string_serialize(void);
static FRAME_INFO frame__35_1_types__string_serialize = {4, {"self", "indent", "buf", "s"}};
static NODE *string__35_2;
static NODE *func__35_3;
static void entry__35_3(void);
static FRAME_INFO frame__35_3 = {5, {"idx", "chr", "buf", "self", "s"}};
static void cont__35_4(void);
static NODE *func__35_5;
static void entry__35_5(void);
static FRAME_INFO frame__35_5 = {1, {"chr"}};
static void cont__35_6(void);
static NODE *func__35_7;
static void entry__35_7(void);
static FRAME_INFO frame__35_7 = {1, {"chr"}};
static void cont__35_8(void);
static NODE *func__35_9;
static void entry__35_9(void);
static FRAME_INFO frame__35_9 = {1, {"chr"}};
static void cont__35_10(void);
static NODE *func__35_11;
static void entry__35_11(void);
static FRAME_INFO frame__35_11 = {1, {"chr"}};
static void cont__35_12(void);
static void cont__35_13(void);
static void cont__35_14(void);
static void cont__35_15(void);
static void cont__35_16(void);
static NODE *func__35_17;
static void entry__35_17(void);
static FRAME_INFO frame__35_17 = {5, {"buf", "self", "s", "idx", "chr"}};
static void cont__35_18(void);
static void cont__35_19(void);
static void cont__35_20(void);
static void cont__35_21(void);
static void cont__35_22(void);
static NODE *string__35_23;
static void cont__35_24(void);
static void cont__35_25(void);
static void cont__35_26(void);
static void cont__35_27(void);
static void cont__35_28(void);
static void cont__35_29(void);
static void cont__35_30(void);
static void cont__35_31(void);
static NODE *func__36_1_types__string_parse_integer;
static void entry__36_1_types__string_parse_integer(void);
static FRAME_INFO frame__36_1_types__string_parse_integer = {4, {"self", "return", "val", "negate"}};
static void cont__36_2(void);
static NODE *func__36_3;
static void entry__36_3(void);
static FRAME_INFO frame__36_3 = {2, {"self", "negate"}};
static void cont__36_4(void);
static void cont__36_5(void);
static void cont__36_6(void);
static NODE *func__36_7;
static void entry__36_7(void);
static FRAME_INFO frame__36_7 = {4, {"break", "self", "val", "return"}};
static NODE *func__36_8;
static void entry__36_8(void);
static FRAME_INFO frame__36_8 = {4, {"self", "val", "return", "break"}};
static NODE *string__36_9;
static void cont__36_10(void);
static NODE *func__36_11;
static void entry__36_11(void);
static FRAME_INFO frame__36_11 = {4, {"self", "val", "return", "break"}};
static void cont__36_12(void);
static NODE *func__36_13;
static void entry__36_13(void);
static FRAME_INFO frame__36_13 = {6, {"idx", "chr", "val", "return", "self", "break"}};
static void cont__36_14(void);
static NODE *func__36_15;
static void entry__36_15(void);
static FRAME_INFO frame__36_15 = {2, {"val", "chr"}};
static void cont__36_16(void);
static void cont__36_17(void);
static void cont__36_18(void);
static NODE *func__36_19;
static void entry__36_19(void);
static FRAME_INFO frame__36_19 = {4, {"idx", "return", "self", "break"}};
static void cont__36_20(void);
static void cont__36_21(void);
static NODE *func__36_22;
static void entry__36_22(void);
static FRAME_INFO frame__36_22 = {2, {"return", "self"}};
static void cont__36_23(void);
static void cont__36_24(void);
static void cont__36_25(void);
static NODE *func__36_26;
static void entry__36_26(void);
static FRAME_INFO frame__36_26 = {4, {"self", "val", "return", "break"}};
static NODE *string__36_27;
static void cont__36_28(void);
static NODE *func__36_29;
static void entry__36_29(void);
static FRAME_INFO frame__36_29 = {4, {"self", "val", "return", "break"}};
static void cont__36_30(void);
static NODE *func__36_31;
static void entry__36_31(void);
static FRAME_INFO frame__36_31 = {6, {"idx", "chr", "val", "return", "self", "break"}};
static void cont__36_32(void);
static NODE *func__36_33;
static void entry__36_33(void);
static FRAME_INFO frame__36_33 = {2, {"val", "chr"}};
static void cont__36_34(void);
static void cont__36_35(void);
static void cont__36_36(void);
static NODE *func__36_37;
static void entry__36_37(void);
static FRAME_INFO frame__36_37 = {4, {"idx", "return", "self", "break"}};
static void cont__36_38(void);
static void cont__36_39(void);
static NODE *func__36_40;
static void entry__36_40(void);
static FRAME_INFO frame__36_40 = {2, {"return", "self"}};
static void cont__36_41(void);
static void cont__36_42(void);
static void cont__36_43(void);
static NODE *func__36_44;
static void entry__36_44(void);
static FRAME_INFO frame__36_44 = {4, {"self", "val", "return", "break"}};
static NODE *string__36_45;
static void cont__36_46(void);
static NODE *func__36_47;
static void entry__36_47(void);
static FRAME_INFO frame__36_47 = {4, {"self", "val", "return", "break"}};
static void cont__36_48(void);
static NODE *func__36_49;
static void entry__36_49(void);
static FRAME_INFO frame__36_49 = {6, {"idx", "chr", "val", "return", "self", "break"}};
static void cont__36_50(void);
static NODE *func__36_51;
static void entry__36_51(void);
static FRAME_INFO frame__36_51 = {2, {"val", "chr"}};
static void cont__36_52(void);
static void cont__36_53(void);
static void cont__36_54(void);
static void cont__36_55(void);
static NODE *func__36_56;
static void entry__36_56(void);
static FRAME_INFO frame__36_56 = {2, {"val", "chr"}};
static void cont__36_57(void);
static void cont__36_58(void);
static void cont__36_59(void);
static void cont__36_60(void);
static void cont__36_61(void);
static NODE *func__36_62;
static void entry__36_62(void);
static FRAME_INFO frame__36_62 = {2, {"val", "chr"}};
static void cont__36_63(void);
static void cont__36_64(void);
static void cont__36_65(void);
static void cont__36_66(void);
static NODE *func__36_67;
static void entry__36_67(void);
static FRAME_INFO frame__36_67 = {4, {"idx", "return", "self", "break"}};
static void cont__36_68(void);
static void cont__36_69(void);
static NODE *func__36_70;
static void entry__36_70(void);
static FRAME_INFO frame__36_70 = {2, {"return", "self"}};
static void cont__36_71(void);
static void cont__36_72(void);
static void cont__36_73(void);
static NODE *func__36_74;
static void entry__36_74(void);
static FRAME_INFO frame__36_74 = {4, {"self", "val", "return", "break"}};
static NODE *func__36_75;
static void entry__36_75(void);
static FRAME_INFO frame__36_75 = {6, {"idx", "chr", "val", "return", "self", "break"}};
static void cont__36_76(void);
static NODE *func__36_77;
static void entry__36_77(void);
static FRAME_INFO frame__36_77 = {2, {"val", "chr"}};
static void cont__36_78(void);
static void cont__36_79(void);
static void cont__36_80(void);
static NODE *func__36_81;
static void entry__36_81(void);
static FRAME_INFO frame__36_81 = {4, {"idx", "return", "self", "break"}};
static void cont__36_82(void);
static void cont__36_83(void);
static NODE *func__36_84;
static void entry__36_84(void);
static FRAME_INFO frame__36_84 = {2, {"return", "self"}};
static void cont__36_85(void);
static void cont__36_86(void);
static void cont__36_87(void);
static void cont__36_88(void);
static void cont__36_89(void);
static NODE *func__36_90;
static void entry__36_90(void);
static FRAME_INFO frame__36_90 = {1, {"val"}};
static void cont__36_91(void);
static NODE *func__36_92;
static void entry__36_92(void);
static FRAME_INFO frame__36_92 = {1, {"val"}};
static void cont__36_93(void);

static long func__types__octet_string___debug_string(NODE *node, int indent, int max_depth, char *buf);

static long func__types__quad_octet_string___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__39_1_types__octet_string_push(void);
static NODE *func__39_1_types__octet_string_push;
static void entry__40_1_types__quad_octet_string_push(void);
static NODE *func__40_1_types__quad_octet_string_push;
static void entry__41_1_types__octet_string_append(void);
static NODE *func__41_1_types__octet_string_append;
static void entry__42_1_types__quad_octet_string_append(void);
static NODE *func__42_1_types__quad_octet_string_append;
static void entry__43_1_types__string_parse_real(void);
static NODE *func__43_1_types__string_parse_real;
static void entry__44_1_types__octet_string_range(void);
static NODE *func__44_1_types__octet_string_range;
static void entry__45_1_types__quad_octet_string_range(void);
static NODE *func__45_1_types__quad_octet_string_range;
static void entry__46_1_std__matches_file_pattern(void);
static NODE *func__46_1_std__matches_file_pattern;
static NODE *get__std__matches_file_pattern(void) {
  return var.std__matches_file_pattern;
}
static void entry__47_1_types__octet_string_is_a_latin_1_string(void);
static NODE *func__47_1_types__octet_string_is_a_latin_1_string;
static void entry__48_1_types__quad_octet_string_is_a_latin_1_string(void);
static NODE *func__48_1_types__quad_octet_string_is_a_latin_1_string;
static void entry__49_1_std__from_utf8(void);
static NODE *func__49_1_std__from_utf8;
static NODE *get__std__from_utf8(void) {
  return var.std__from_utf8;
}
static void entry__50_1_types__octet_string_to_utf8(void);
static NODE *func__50_1_types__octet_string_to_utf8;
static void entry__51_1_types__quad_octet_string_to_utf8(void);
static NODE *func__51_1_types__quad_octet_string_to_utf8;
void run__basic__types__string_primitives(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_string, NULL, 26, 26, 2, 17},
  {type__std__count_character_occurrences, NULL, 31, 31, 2, 33},
  {type__std__to_utf8, NULL, 35, 35, 2, 13},
  {type__std__is_a_latin_1_string, NULL, 39, 39, 2, 25},
  {run__basic__types__string_primitives, NULL, 43, 43, 1, 34},
  {entry__24_1_types__octet_string_length_of, NULL, 349, 352, 3, 2},
  {entry__25_1_types__quad_octet_string_length_of, NULL, 355, 358, 3, 2},
  {entry__26_1_types__octet_string_equal, NULL, 363, 385, 3, 2},
  {entry__27_1_types__quad_octet_string_equal, NULL, 390, 412, 3, 2},
  {entry__28_1_types__octet_string_count_character_occurrences, NULL, 417, 429, 3, 2},
  {entry__29_1_types__quad_octet_string_count_character_occurrences, NULL, 434, 446, 3, 2},
  {entry__30_1_types__octet_string_less, NULL, 451, 501, 3, 2},
  {entry__31_1_types__quad_octet_string_less, NULL, 506, 556, 3, 2},
  {entry__32_1_types__octet_string_hash, NULL, 561, 582, 3, 2},
  {entry__33_1_types__quad_octet_string_hash, NULL, 587, 608, 3, 2},
  {entry__34_1_types__string_to_string, NULL, 616, 616, 3, 9},
  {entry__35_11, NULL, 634, 634, 9, 23},
  {cont__35_12, &frame__35_11, 634, 634, 9, 23},
  {entry__35_9, NULL, 633, 633, 9, 23},
  {cont__35_10, &frame__35_9, 634, 634, 9, 23},
  {cont__35_13, &frame__35_9, },
  {entry__35_7, NULL, 632, 632, 9, 19},
  {cont__35_8, &frame__35_7, },
  {cont__35_14, &frame__35_7, },
  {entry__35_5, NULL, 631, 631, 9, 17},
  {cont__35_6, &frame__35_5, },
  {cont__35_15, &frame__35_5, },
  {entry__35_17, NULL, 636, 636, 34, 38},
  {cont__35_18, &frame__35_17, 636, 636, 21, 39},
  {cont__35_19, &frame__35_17, 636, 636, 9, 39},
  {cont__35_20, &frame__35_17, 637, 637, 39, 52},
  {cont__35_21, &frame__35_17, 637, 637, 35, 53},
  {cont__35_22, &frame__35_17, 637, 637, 21, 58},
  {cont__35_24, &frame__35_17, 637, 637, 9, 58},
  {cont__35_25, &frame__35_17, 638, 638, 9, 16},
  {cont__35_26, &frame__35_17, 638, 638, 16, 16},
  {entry__35_3, NULL, 630, 630, 9, 17},
  {cont__35_4, &frame__35_3, },
  {cont__35_16, &frame__35_3, 628, 638, 5, 17},
  {entry__35_1_types__string_serialize, NULL, 627, 638, 3, 18},
  {cont__35_27, &frame__35_1_types__string_serialize, 639, 639, 29, 29},
  {cont__35_28, &frame__35_1_types__string_serialize, 639, 639, 15, 30},
  {cont__35_29, &frame__35_1_types__string_serialize, 639, 639, 3, 30},
  {cont__35_30, &frame__35_1_types__string_serialize, 640, 640, 6, 23},
  {cont__35_31, &frame__35_1_types__string_serialize, 640, 640, 3, 23},
  {entry__36_3, NULL, 652, 652, 20, 20},
  {cont__36_4, &frame__36_3, 652, 652, 5, 20},
  {cont__36_5, &frame__36_3, 653, 653, 16, 16},
  {entry__36_15, NULL, 661, 661, 21, 28},
  {cont__36_16, &frame__36_15, 661, 661, 32, 38},
  {cont__36_17, &frame__36_15, 661, 661, 15, 39},
  {cont__36_18, &frame__36_15, 661, 661, 39, 39},
  {entry__36_22, NULL, 663, 663, 28, 48},
  {entry__36_19, NULL, 663, 663, 18, 25},
  {cont__36_20, &frame__36_19, 663, 663, 18, 25},
  {cont__36_21, &frame__36_19, 663, 663, 15, 48},
  {cont__36_23, &frame__36_19, 664, 664, 32, 32},
  {cont__36_24, &frame__36_19, 664, 664, 15, 32},
  {cont__36_25, &frame__36_19, 665, 665, 15, 19},
  {entry__36_13, NULL, 660, 660, 13, 22},
  {cont__36_14, &frame__36_13, 658, 665, 11, 20},
  {entry__36_11, NULL, 657, 657, 34, 34},
  {cont__36_12, &frame__36_11, 657, 665, 9, 21},
  {entry__36_8, NULL, 656, 656, 10, 31},
  {cont__36_10, &frame__36_8, 656, 665, 7, 22},
  {entry__36_33, NULL, 671, 671, 21, 28},
  {cont__36_34, &frame__36_33, 671, 671, 32, 38},
  {cont__36_35, &frame__36_33, 671, 671, 15, 39},
  {cont__36_36, &frame__36_33, 671, 671, 39, 39},
  {entry__36_40, NULL, 673, 673, 28, 48},
  {entry__36_37, NULL, 673, 673, 18, 25},
  {cont__36_38, &frame__36_37, 673, 673, 18, 25},
  {cont__36_39, &frame__36_37, 673, 673, 15, 48},
  {cont__36_41, &frame__36_37, 674, 674, 32, 32},
  {cont__36_42, &frame__36_37, 674, 674, 15, 32},
  {cont__36_43, &frame__36_37, 675, 675, 15, 19},
  {entry__36_31, NULL, 670, 670, 13, 22},
  {cont__36_32, &frame__36_31, 668, 675, 11, 20},
  {entry__36_29, NULL, 667, 667, 34, 34},
  {cont__36_30, &frame__36_29, 667, 675, 9, 21},
  {entry__36_26, NULL, 666, 666, 10, 31},
  {cont__36_28, &frame__36_26, 666, 675, 7, 22},
  {entry__36_51, NULL, 681, 681, 21, 28},
  {cont__36_52, &frame__36_51, 681, 681, 32, 38},
  {cont__36_53, &frame__36_51, 681, 681, 15, 39},
  {cont__36_54, &frame__36_51, 681, 681, 39, 39},
  {entry__36_56, NULL, 683, 683, 21, 28},
  {cont__36_57, &frame__36_56, 683, 683, 32, 38},
  {cont__36_58, &frame__36_56, 683, 683, 21, 38},
  {cont__36_59, &frame__36_56, 683, 683, 15, 42},
  {cont__36_60, &frame__36_56, 683, 683, 42, 42},
  {entry__36_62, NULL, 685, 685, 21, 28},
  {cont__36_63, &frame__36_62, 685, 685, 32, 38},
  {cont__36_64, &frame__36_62, 685, 685, 21, 38},
  {cont__36_65, &frame__36_62, 685, 685, 15, 42},
  {cont__36_66, &frame__36_62, 685, 685, 42, 42},
  {entry__36_70, NULL, 687, 687, 28, 48},
  {entry__36_67, NULL, 687, 687, 18, 25},
  {cont__36_68, &frame__36_67, 687, 687, 18, 25},
  {cont__36_69, &frame__36_67, 687, 687, 15, 48},
  {cont__36_71, &frame__36_67, 688, 688, 32, 32},
  {cont__36_72, &frame__36_67, 688, 688, 15, 32},
  {cont__36_73, &frame__36_67, 689, 689, 15, 19},
  {entry__36_49, NULL, 680, 680, 13, 22},
  {cont__36_50, &frame__36_49, 682, 682, 13, 22},
  {cont__36_55, &frame__36_49, 684, 684, 13, 22},
  {cont__36_61, &frame__36_49, 678, 689, 11, 20},
  {entry__36_47, NULL, 677, 677, 34, 34},
  {cont__36_48, &frame__36_47, 677, 689, 9, 21},
  {entry__36_44, NULL, 676, 676, 10, 31},
  {cont__36_46, &frame__36_44, 676, 689, 7, 22},
  {entry__36_77, NULL, 695, 695, 20, 25},
  {cont__36_78, &frame__36_77, 695, 695, 28, 34},
  {cont__36_79, &frame__36_77, 695, 695, 15, 35},
  {cont__36_80, &frame__36_77, 695, 695, 35, 35},
  {entry__36_84, NULL, 697, 697, 28, 48},
  {entry__36_81, NULL, 697, 697, 18, 25},
  {cont__36_82, &frame__36_81, 697, 697, 18, 25},
  {cont__36_83, &frame__36_81, 697, 697, 15, 48},
  {cont__36_85, &frame__36_81, 698, 698, 32, 32},
  {cont__36_86, &frame__36_81, 698, 698, 15, 32},
  {cont__36_87, &frame__36_81, 699, 699, 15, 19},
  {entry__36_75, NULL, 694, 694, 13, 22},
  {cont__36_76, &frame__36_75, 692, 699, 11, 20},
  {entry__36_74, NULL, 691, 699, 9, 21},
  {entry__36_7, NULL, 655, 699, 5, 23},
  {cont__36_88, &frame__36_7, 700, 700, 12, 12},
  {entry__36_90, NULL, 701, 701, 26, 28},
  {cont__36_91, &frame__36_90, 701, 701, 22, 28},
  {entry__36_92, NULL, 701, 701, 31, 36},
  {entry__36_1_types__string_parse_integer, NULL, 651, 651, 6, 26},
  {cont__36_2, &frame__36_1_types__string_parse_integer, 651, 653, 3, 16},
  {cont__36_6, &frame__36_1_types__string_parse_integer, 654, 700, 3, 12},
  {cont__36_89, &frame__36_1_types__string_parse_integer, 701, 701, 11, 37},
  {cont__36_93, &frame__36_1_types__string_parse_integer, 701, 701, 3, 37},
  {entry__39_1_types__octet_string_push, NULL, 774, 815, 3, 2},
  {entry__40_1_types__quad_octet_string_push, NULL, 820, 846, 3, 2},
  {entry__41_1_types__octet_string_append, NULL, 851, 895, 3, 2},
  {entry__42_1_types__quad_octet_string_append, NULL, 900, 944, 3, 2},
  {entry__43_1_types__string_parse_real, NULL, 949, 961, 3, 2},
  {entry__44_1_types__octet_string_range, NULL, 966, 983, 3, 2},
  {entry__45_1_types__quad_octet_string_range, NULL, 988, 1020, 3, 2},
  {entry__46_1_std__matches_file_pattern, NULL, 1025, 1033, 3, 2},
  {entry__47_1_types__octet_string_is_a_latin_1_string, NULL, 1038, 1041, 3, 2},
  {entry__48_1_types__quad_octet_string_is_a_latin_1_string, NULL, 1046, 1049, 3, 2},
  {entry__49_1_std__from_utf8, NULL, 1054, 1149, 3, 2},
  {entry__50_1_types__octet_string_to_utf8, NULL, 1154, 1183, 3, 2},
  {entry__51_1_types__quad_octet_string_to_utf8, NULL, 1199, 1288, 3, 2}
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
static void entry__24_1_types__octet_string_length_of(void) {
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
static void entry__25_1_types__quad_octet_string_length_of(void) {
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
static void entry__26_1_types__octet_string_equal(void) {
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
static void entry__27_1_types__quad_octet_string_equal(void) {
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
static void entry__28_1_types__octet_string_count_character_occurrences(void) {
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
static void entry__29_1_types__quad_octet_string_count_character_occurrences(void) {
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
static void entry__30_1_types__octet_string_less(void) {
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
static void entry__31_1_types__quad_octet_string_less(void) {
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
static void entry__32_1_types__octet_string_hash(void) {
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
static void entry__33_1_types__quad_octet_string_hash(void) {
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
static void entry__34_1_types__string_to_string(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 616: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__35_1_types__string_serialize(void) {
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
  // 625: $$buf "@quot;"
  ((CELL *)frame->slots[2])->contents /* buf */ = string__35_2;
  // 626: $$s 1
  ((CELL *)frame->slots[3])->contents /* s */ = number__1;
  // 627: ... : (idx chr)
  // 628:   if
  // 629:     ||
  // 630:       chr < ' '
  // 631:       chr > '~'
  // 632:       chr == '@@'
  // 633:       chr == '@quot;'
  // 634:       chr == '@apos;'
  // 635:     :
  // 636:       append &buf range(self s idx-1)
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__35_3, 2);
  // 627: for_each self: (idx chr)
  // 628:   if
  // 629:     ||
  // 630:       chr < ' '
  // 631:       chr > '~'
  // 632:       chr == '@@'
  // 633:       chr == '@quot;'
  // 634:       chr == '@apos;'
  // 635:     :
  // 636:       append &buf range(self s idx-1)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__35_27;
}
static void entry__35_17(void) {
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
  // 636: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__35_18;
}
static void cont__35_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 636: ... range(self s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* s */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_19;
}
static void cont__35_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 636: append &buf range(self s idx-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__35_20;
}
static void cont__35_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 637: ... chr.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* chr */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__35_21;
}
static void cont__35_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 637: ... hex(chr.to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__hex();
  func = myself->type;
  frame->cont = cont__35_22;
}
static void cont__35_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 637: ... string("@@0x" hex(chr.to_integer) ';')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__35_23;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = character__59;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__35_24;
}
static void cont__35_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 637: append &buf string("@@0x" hex(chr.to_integer) ';')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__35_25;
}
static void cont__35_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 638: !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__35_26;
}
static void cont__35_26(void) {
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
static void entry__35_3(void) {
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
  // 630: chr < ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__35_4;
}
static void cont__35_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  frame->slots[7] /* temp__3 */ = create_closure(entry__35_5, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__35_16;
}
static void entry__35_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 631: chr > '~'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__126;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__35_6;
}
static void cont__35_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__35_7, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__35_15;
}
static void entry__35_7(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 632: chr == '@@'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__64;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__35_8;
}
static void cont__35_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__35_9, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__35_14;
}
static void entry__35_9(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 633: chr == '@quot;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__34;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__35_10;
}
static void cont__35_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 634: chr == '@apos;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__35_11, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__35_13;
}
static void entry__35_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 634: chr == '@apos;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__35_12;
}
static void cont__35_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 634: chr == '@apos;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_13(void) {
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
static void cont__35_14(void) {
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
static void cont__35_15(void) {
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
static void cont__35_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 635: :
  // 636:   append &buf range(self s idx-1)
  // 637:   append &buf string("@@0x" hex(chr.to_integer) ';')
  // 638:   !s idx+1
  frame->slots[8] /* temp__4 */ = create_closure(entry__35_17, 0);
  // 628: if
  // 629:   ||
  // 630:     chr < ' '
  // 631:     chr > '~'
  // 632:     chr == '@@'
  // 633:     chr == '@quot;'
  // 634:     chr == '@apos;'
  // 635:   :
  // 636:     append &buf range(self s idx-1)
  // 637:     append &buf string("@@0x" hex(chr.to_integer) ';')
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
static void cont__35_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 639: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__35_28;
}
static void cont__35_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 639: ... range(self s -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_29;
}
static void cont__35_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 639: append &buf range(self s -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__35_30;
}
static void cont__35_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* buf */ = arguments->slots[0];
  // 640: ... push(buf '@quot;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = character__34;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__35_31;
}
static void cont__35_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 640: -> push(buf '@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_1_types__string_parse_integer(void) {
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
  // 649: $$val 0
  ((CELL *)frame->slots[2])->contents /* val */ = number__0;
  // 650: $$negate false
  ((CELL *)frame->slots[3])->contents /* negate */ = get__false();
  // 651: ... self .has_prefix. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_2;
}
static void cont__36_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 651: ... :
  // 652:   range &self 2 -1
  // 653:   !negate true
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_3, 0);
  // 651: if self .has_prefix. '-':
  // 652:   range &self 2 -1
  // 653:   !negate true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_6;
}
static void entry__36_3(void) {
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
  // 652: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 652: range &self 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_5;
}
static void cont__36_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  // 653: !negate true
  ((CELL *)frame->slots[1])->contents /* negate */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 654: ... : (-> break)
  // 655:   cond
  // 656:     -> self .has_prefix. "0b":
  // 657:       for_each_from_to self 3 -1: (idx chr)
  // 658:         case
  // 659:           chr
  // 660:           '0' .. '1':
  // 661:             !val (val << 1)+(chr-'0')
  // 662:           :
  // 663:             if idx <= 3: return self undefined
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__36_7, 0);
  // 654: do: (-> break)
  // 655:   cond
  // 656:     -> self .has_prefix. "0b":
  // 657:       for_each_from_to self 3 -1: (idx chr)
  // 658:         case
  // 659:           chr
  // 660:           '0' .. '1':
  // 661:             !val (val << 1)+(chr-'0')
  // 662:           :
  // 663:             if idx <= 3: return self undefined
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__36_89;
}
static void entry__36_7(void) {
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
  // 656: -> self .has_prefix. "0b":
  // 657:   for_each_from_to self 3 -1: (idx chr)
  // 658:     case
  // 659:       chr
  // 660:       '0' .. '1':
  // 661:         !val (val << 1)+(chr-'0')
  // 662:       :
  // 663:         if idx <= 3: return self undefined
  // 664:         range &self idx -1
  // 665:         break
  frame->slots[4] /* temp__1 */ = create_closure(entry__36_8, 0);
  // 666: -> self .has_prefix. "0o":
  // 667:   for_each_from_to self 3 -1: (idx chr)
  // 668:     case
  // 669:       chr
  // 670:       '0' .. '7':
  // 671:         !val (val << 3)+(chr-'0')
  // 672:       :
  // 673:         if idx <= 3: return self undefined
  // 674:         range &self idx -1
  // 675:         break
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_26, 0);
  // 676: -> self .has_prefix. "0x":
  // 677:   for_each_from_to self 3 -1: (idx chr)
  // 678:     case
  // 679:       chr
  // 680:       '0' .. '9':
  // 681:         !val (val << 4)+(chr-'0')
  // 682:       'a' .. 'f':
  // 683:         !val (val << 4)+(chr-'a')+10
  // 684:       'A' .. 'F':
  // 685:         !val (val << 4)+(chr-'A')+10
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__36_44, 0);
  // 690: :
  // 691:   for_each self: (idx chr)
  // 692:     case
  // 693:       chr
  // 694:       '0' .. '9':
  // 695:         !val 10*val+(chr-'0')
  // 696:       :
  // 697:         if idx <= 1: return self undefined
  // 698:         range &self idx -1
  // 699:         break
  frame->slots[7] /* temp__4 */ = create_closure(entry__36_74, 0);
  // 655: cond
  // 656:   -> self .has_prefix. "0b":
  // 657:     for_each_from_to self 3 -1: (idx chr)
  // 658:       case
  // 659:         chr
  // 660:         '0' .. '1':
  // 661:           !val (val << 1)+(chr-'0')
  // 662:         :
  // 663:           if idx <= 3: return self undefined
  // 664:           range &self idx -1
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
  frame->cont = cont__36_88;
}
static void entry__36_77(void) {
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
  // 695: ... 10*val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__10;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__36_78;
}
static void cont__36_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 695: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__36_79;
}
static void cont__36_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 695: !val 10*val+(chr-'0')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_80;
}
static void cont__36_80(void) {
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
static void entry__36_81(void) {
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
  // 697: ... idx <= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__36_82;
}
static void cont__36_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 697: ... idx <= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__36_83;
}
static void cont__36_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 697: ... : return self undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__36_84, 0);
  // 697: if idx <= 1: return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_85;
}
static void entry__36_84(void) {
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
  // 697: ... return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 698: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_86;
}
static void cont__36_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 698: range &self idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_87;
}
static void cont__36_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* self */ = arguments->slots[0];
  // 699: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_75(void) {
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
  // 694: '0' .. '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__57;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__36_76;
}
static void cont__36_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 694: ... :
  // 695:   !val 10*val+(chr-'0')
  frame->slots[7] /* temp__2 */ = create_closure(entry__36_77, 0);
  // 696: :
  // 697:   if idx <= 1: return self undefined
  // 698:   range &self idx -1
  // 699:   break
  frame->slots[8] /* temp__3 */ = create_closure(entry__36_81, 0);
  // 692: case
  // 693:   chr
  // 694:   '0' .. '9':
  // 695:     !val 10*val+(chr-'0')
  // 696:   :
  // 697:     if idx <= 1: return self undefined
  // 698:     range &self idx -1
  // 699:     break
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
static void entry__36_62(void) {
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
  // 685: ... val << 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__36_63;
}
static void cont__36_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 685: ... chr-'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__36_64;
}
static void cont__36_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 685: ... val << 4)+(chr-'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_65;
}
static void cont__36_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 685: !val (val << 4)+(chr-'A')+10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_66;
}
static void cont__36_66(void) {
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
static void entry__36_67(void) {
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
  // 687: ... idx <= 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__36_68;
}
static void cont__36_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 687: ... idx <= 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__36_69;
}
static void cont__36_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 687: ... : return self undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__36_70, 0);
  // 687: if idx <= 3: return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_71;
}
static void entry__36_70(void) {
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
  // 687: ... return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 688: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_72;
}
static void cont__36_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 688: range &self idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_73;
}
static void cont__36_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* self */ = arguments->slots[0];
  // 689: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_49(void) {
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
  // 680: '0' .. '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__57;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__36_50;
}
static void cont__36_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 680: ... :
  // 681:   !val (val << 4)+(chr-'0')
  frame->slots[7] /* temp__2 */ = create_closure(entry__36_51, 0);
  // 682: 'a' .. 'f'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__102;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__36_55;
}
static void entry__36_51(void) {
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
  // 681: ... val << 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__36_52;
}
static void cont__36_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 681: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__36_53;
}
static void cont__36_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 681: !val (val << 4)+(chr-'0')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_54;
}
static void cont__36_54(void) {
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
static void cont__36_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 682: ... :
  // 683:   !val (val << 4)+(chr-'a')+10
  frame->slots[9] /* temp__4 */ = create_closure(entry__36_56, 0);
  // 684: 'A' .. 'F'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__65;
  arguments->slots[1] = character__70;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__36_61;
}
static void entry__36_56(void) {
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
  // 683: ... val << 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__36_57;
}
static void cont__36_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 683: ... chr-'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__36_58;
}
static void cont__36_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 683: ... val << 4)+(chr-'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_59;
}
static void cont__36_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 683: !val (val << 4)+(chr-'a')+10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_60;
}
static void cont__36_60(void) {
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
static void cont__36_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 684: ... :
  // 685:   !val (val << 4)+(chr-'A')+10
  frame->slots[11] /* temp__6 */ = create_closure(entry__36_62, 0);
  // 686: :
  // 687:   if idx <= 3: return self undefined
  // 688:   range &self idx -1
  // 689:   break
  frame->slots[12] /* temp__7 */ = create_closure(entry__36_67, 0);
  // 678: case
  // 679:   chr
  // 680:   '0' .. '9':
  // 681:     !val (val << 4)+(chr-'0')
  // 682:   'a' .. 'f':
  // 683:     !val (val << 4)+(chr-'a')+10
  // 684:   'A' .. 'F':
  // 685:     !val (val << 4)+(chr-'A')+10
  // 686:   :
  // 687:     if idx <= 3: return self undefined
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
static void entry__36_47(void) {
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
  // 677: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_48;
}
static void cont__36_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 677: ... : (idx chr)
  // 678:   case
  // 679:     chr
  // 680:     '0' .. '9':
  // 681:       !val (val << 4)+(chr-'0')
  // 682:     'a' .. 'f':
  // 683:       !val (val << 4)+(chr-'a')+10
  // 684:     'A' .. 'F':
  // 685:       !val (val << 4)+(chr-'A')+10
  // 686:     :
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_49, 2);
  // 677: for_each_from_to self 3 -1: (idx chr)
  // 678:   case
  // 679:     chr
  // 680:     '0' .. '9':
  // 681:       !val (val << 4)+(chr-'0')
  // 682:     'a' .. 'f':
  // 683:       !val (val << 4)+(chr-'a')+10
  // 684:     'A' .. 'F':
  // 685:       !val (val << 4)+(chr-'A')+10
  // 686:     :
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
static void entry__36_33(void) {
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
  // 671: ... val << 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__36_34;
}
static void cont__36_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 671: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__36_35;
}
static void cont__36_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 671: !val (val << 3)+(chr-'0')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_36;
}
static void cont__36_36(void) {
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
static void entry__36_37(void) {
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
  // 673: ... idx <= 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__36_38;
}
static void cont__36_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 673: ... idx <= 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__36_39;
}
static void cont__36_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 673: ... : return self undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__36_40, 0);
  // 673: if idx <= 3: return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_41;
}
static void entry__36_40(void) {
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
  // 673: ... return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 674: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_42;
}
static void cont__36_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 674: range &self idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_43;
}
static void cont__36_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* self */ = arguments->slots[0];
  // 675: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_31(void) {
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
  // 670: '0' .. '7'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__55;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__36_32;
}
static void cont__36_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 670: ... :
  // 671:   !val (val << 3)+(chr-'0')
  frame->slots[7] /* temp__2 */ = create_closure(entry__36_33, 0);
  // 672: :
  // 673:   if idx <= 3: return self undefined
  // 674:   range &self idx -1
  // 675:   break
  frame->slots[8] /* temp__3 */ = create_closure(entry__36_37, 0);
  // 668: case
  // 669:   chr
  // 670:   '0' .. '7':
  // 671:     !val (val << 3)+(chr-'0')
  // 672:   :
  // 673:     if idx <= 3: return self undefined
  // 674:     range &self idx -1
  // 675:     break
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
static void entry__36_29(void) {
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
  // 667: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_30;
}
static void cont__36_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 667: ... : (idx chr)
  // 668:   case
  // 669:     chr
  // 670:     '0' .. '7':
  // 671:       !val (val << 3)+(chr-'0')
  // 672:     :
  // 673:       if idx <= 3: return self undefined
  // 674:       range &self idx -1
  // 675:       break
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_31, 2);
  // 667: for_each_from_to self 3 -1: (idx chr)
  // 668:   case
  // 669:     chr
  // 670:     '0' .. '7':
  // 671:       !val (val << 3)+(chr-'0')
  // 672:     :
  // 673:       if idx <= 3: return self undefined
  // 674:       range &self idx -1
  // 675:       break
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
static void entry__36_15(void) {
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
  // 661: ... val << 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__shift_left();
  func = myself->type;
  frame->cont = cont__36_16;
}
static void cont__36_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 661: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__36_17;
}
static void cont__36_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 661: !val (val << 1)+(chr-'0')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_18;
}
static void cont__36_18(void) {
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
static void entry__36_19(void) {
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
  // 663: ... idx <= 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__36_20;
}
static void cont__36_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 663: ... idx <= 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__36_21;
}
static void cont__36_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 663: ... : return self undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__36_22, 0);
  // 663: if idx <= 3: return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_23;
}
static void entry__36_22(void) {
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
  // 663: ... return self undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 664: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_24;
}
static void cont__36_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 664: range &self idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_25;
}
static void cont__36_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* self */ = arguments->slots[0];
  // 665: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_13(void) {
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
  // 660: '0' .. '1'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__49;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__36_14;
}
static void cont__36_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 660: ... :
  // 661:   !val (val << 1)+(chr-'0')
  frame->slots[7] /* temp__2 */ = create_closure(entry__36_15, 0);
  // 662: :
  // 663:   if idx <= 3: return self undefined
  // 664:   range &self idx -1
  // 665:   break
  frame->slots[8] /* temp__3 */ = create_closure(entry__36_19, 0);
  // 658: case
  // 659:   chr
  // 660:   '0' .. '1':
  // 661:     !val (val << 1)+(chr-'0')
  // 662:   :
  // 663:     if idx <= 3: return self undefined
  // 664:     range &self idx -1
  // 665:     break
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
static void entry__36_11(void) {
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
  // 657: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_12;
}
static void cont__36_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 657: ... : (idx chr)
  // 658:   case
  // 659:     chr
  // 660:     '0' .. '1':
  // 661:       !val (val << 1)+(chr-'0')
  // 662:     :
  // 663:       if idx <= 3: return self undefined
  // 664:       range &self idx -1
  // 665:       break
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_13, 2);
  // 657: for_each_from_to self 3 -1: (idx chr)
  // 658:   case
  // 659:     chr
  // 660:     '0' .. '1':
  // 661:       !val (val << 1)+(chr-'0')
  // 662:     :
  // 663:       if idx <= 3: return self undefined
  // 664:       range &self idx -1
  // 665:       break
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
static void entry__36_8(void) {
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
  // 656: ... self .has_prefix. "0b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = string__36_9;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_10;
}
static void cont__36_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 656: ... :
  // 657:   for_each_from_to self 3 -1: (idx chr)
  // 658:     case
  // 659:       chr
  // 660:       '0' .. '1':
  // 661:         !val (val << 1)+(chr-'0')
  // 662:       :
  // 663:         if idx <= 3: return self undefined
  // 664:         range &self idx -1
  // 665:         break
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_11, 0);
  // 656: -> self .has_prefix. "0b":
  // 657:   for_each_from_to self 3 -1: (idx chr)
  // 658:     case
  // 659:       chr
  // 660:       '0' .. '1':
  // 661:         !val (val << 1)+(chr-'0')
  // 662:       :
  // 663:         if idx <= 3: return self undefined
  // 664:         range &self idx -1
  // 665:         break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_26(void) {
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
  // 666: ... self .has_prefix. "0o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = string__36_27;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_28;
}
static void cont__36_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 666: ... :
  // 667:   for_each_from_to self 3 -1: (idx chr)
  // 668:     case
  // 669:       chr
  // 670:       '0' .. '7':
  // 671:         !val (val << 3)+(chr-'0')
  // 672:       :
  // 673:         if idx <= 3: return self undefined
  // 674:         range &self idx -1
  // 675:         break
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_29, 0);
  // 666: -> self .has_prefix. "0o":
  // 667:   for_each_from_to self 3 -1: (idx chr)
  // 668:     case
  // 669:       chr
  // 670:       '0' .. '7':
  // 671:         !val (val << 3)+(chr-'0')
  // 672:       :
  // 673:         if idx <= 3: return self undefined
  // 674:         range &self idx -1
  // 675:         break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_44(void) {
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
  // 676: ... self .has_prefix. "0x"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = string__36_45;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_46;
}
static void cont__36_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 676: ... :
  // 677:   for_each_from_to self 3 -1: (idx chr)
  // 678:     case
  // 679:       chr
  // 680:       '0' .. '9':
  // 681:         !val (val << 4)+(chr-'0')
  // 682:       'a' .. 'f':
  // 683:         !val (val << 4)+(chr-'a')+10
  // 684:       'A' .. 'F':
  // 685:         !val (val << 4)+(chr-'A')+10
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_47, 0);
  // 676: -> self .has_prefix. "0x":
  // 677:   for_each_from_to self 3 -1: (idx chr)
  // 678:     case
  // 679:       chr
  // 680:       '0' .. '9':
  // 681:         !val (val << 4)+(chr-'0')
  // 682:       'a' .. 'f':
  // 683:         !val (val << 4)+(chr-'a')+10
  // 684:       'A' .. 'F':
  // 685:         !val (val << 4)+(chr-'A')+10
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_74(void) {
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
  // 691: ... : (idx chr)
  // 692:   case
  // 693:     chr
  // 694:     '0' .. '9':
  // 695:       !val 10*val+(chr-'0')
  // 696:     :
  // 697:       if idx <= 1: return self undefined
  // 698:       range &self idx -1
  // 699:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__36_75, 2);
  // 691: for_each self: (idx chr)
  // 692:   case
  // 693:     chr
  // 694:     '0' .. '9':
  // 695:       !val 10*val+(chr-'0')
  // 696:     :
  // 697:       if idx <= 1: return self undefined
  // 698:       range &self idx -1
  // 699:       break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 700: !self ""
  ((CELL *)frame->slots[1])->contents /* self */ = empty_string;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 701: ... -> -val
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_90, 0);
  // 701: ... -> val
  frame->slots[6] /* temp__3 */ = create_closure(entry__36_92, 0);
  // 701: ... if(negate (-> -val) -> val)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* negate */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_93;
}
static void entry__36_90(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // val: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 701: ... val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_91;
}
static void cont__36_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 701: ... -> -val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_92(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // val: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 701: ... -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 701: -> self if(negate (-> -val) -> val)
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
static void entry__39_1_types__octet_string_push(void) {
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
static void entry__40_1_types__quad_octet_string_push(void) {
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
static void entry__41_1_types__octet_string_append(void) {
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
static void entry__42_1_types__quad_octet_string_append(void) {
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
static void entry__43_1_types__string_parse_real(void) {
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
static void entry__44_1_types__octet_string_range(void) {
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
static void entry__45_1_types__quad_octet_string_range(void) {
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
static void entry__46_1_std__matches_file_pattern(void) {
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
static void entry__47_1_types__octet_string_is_a_latin_1_string(void) {
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
static void entry__48_1_types__quad_octet_string_is_a_latin_1_string(void) {
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
static void entry__49_1_std__from_utf8(void) {
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
static void entry__50_1_types__octet_string_to_utf8(void) {
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
static void entry__51_1_types__quad_octet_string_to_utf8(void) {
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
  define_polymorphic_function("std", "is_a_string", get__std__is_a_string, &poly_idx__std__is_a_string, &var.std__is_a_string);
  define_polymorphic_function("std", "count_character_occurrences", get__std__count_character_occurrences, &poly_idx__std__count_character_occurrences, &var.std__count_character_occurrences);
  define_polymorphic_function("std", "to_utf8", get__std__to_utf8, &poly_idx__std__to_utf8, &var.std__to_utf8);
  define_polymorphic_function("std", "is_a_latin_1_string", get__std__is_a_latin_1_string, &poly_idx__std__is_a_latin_1_string, &var.std__is_a_latin_1_string);
  define_c_function("from_latin_1_string", runtime__from_latin_1_string);
  define_c_function("from_uint32_string", runtime__from_uint32_string);
  define_c_function("from_c_string", runtime__from_c_string);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__string_primitives(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
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
  func__24_1_types__octet_string_length_of = create_function(entry__24_1_types__octet_string_length_of, 1);
  func__25_1_types__quad_octet_string_length_of = create_function(entry__25_1_types__quad_octet_string_length_of, 1);
  func__26_1_types__octet_string_equal = create_function(entry__26_1_types__octet_string_equal, 2);
  func__27_1_types__quad_octet_string_equal = create_function(entry__27_1_types__quad_octet_string_equal, 2);
  func__28_1_types__octet_string_count_character_occurrences = create_function(entry__28_1_types__octet_string_count_character_occurrences, 2);
  func__29_1_types__quad_octet_string_count_character_occurrences = create_function(entry__29_1_types__quad_octet_string_count_character_occurrences, 2);
  func__30_1_types__octet_string_less = create_function(entry__30_1_types__octet_string_less, 2);
  func__31_1_types__quad_octet_string_less = create_function(entry__31_1_types__quad_octet_string_less, 2);
  func__32_1_types__octet_string_hash = create_function(entry__32_1_types__octet_string_hash, 1);
  func__33_1_types__quad_octet_string_hash = create_function(entry__33_1_types__quad_octet_string_hash, 1);
  func__34_1_types__string_to_string = create_function(entry__34_1_types__string_to_string, 1);
  string__35_2 = from_latin_1_string("\042", 1);
  string__35_23 = from_latin_1_string("@0x", 3);
  func__35_1_types__string_serialize = create_function(entry__35_1_types__string_serialize, -1);
  string__36_9 = from_latin_1_string("0b", 2);
  string__36_27 = from_latin_1_string("0o", 2);
  string__36_45 = from_latin_1_string("0x", 2);
  func__36_1_types__string_parse_integer = create_function(entry__36_1_types__string_parse_integer, 1);
  func__39_1_types__octet_string_push = create_function(entry__39_1_types__octet_string_push, 2);
  func__40_1_types__quad_octet_string_push = create_function(entry__40_1_types__quad_octet_string_push, 2);
  func__41_1_types__octet_string_append = create_function(entry__41_1_types__octet_string_append, 2);
  func__42_1_types__quad_octet_string_append = create_function(entry__42_1_types__quad_octet_string_append, 2);
  func__43_1_types__string_parse_real = create_function(entry__43_1_types__string_parse_real, 1);
  func__44_1_types__octet_string_range = create_function(entry__44_1_types__octet_string_range, 3);
  func__45_1_types__quad_octet_string_range = create_function(entry__45_1_types__quad_octet_string_range, 3);
  func__46_1_std__matches_file_pattern = create_function(entry__46_1_std__matches_file_pattern, 2);
  func__47_1_types__octet_string_is_a_latin_1_string = create_function(entry__47_1_types__octet_string_is_a_latin_1_string, 1);
  func__48_1_types__quad_octet_string_is_a_latin_1_string = create_function(entry__48_1_types__quad_octet_string_is_a_latin_1_string, 1);
  func__49_1_std__from_utf8 = create_function(entry__49_1_std__from_utf8, 1);
  func__50_1_types__octet_string_to_utf8 = create_function(entry__50_1_types__octet_string_to_utf8, 1);
  func__51_1_types__quad_octet_string_to_utf8 = create_function(entry__51_1_types__quad_octet_string_to_utf8, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__string_primitives(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__string_primitives");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("types", "string", get__types__string, &var.types__string);
  var.types__octet_string = create_future_with_prototype(create__types__octet_string(0, 0, NULL));
  define_single_assign_static("types", "octet_string", get__types__octet_string, &var.types__octet_string);
  var.types__quad_octet_string = create_future_with_prototype(create__types__quad_octet_string(0, 0, NULL));
  define_single_assign_static("types", "quad_octet_string", get__types__quad_octet_string, &var.types__quad_octet_string);
  var.std__empty_string = create__types__octet_string(0, 0, NULL);
  define_single_assign_static("std", "empty_string", get__std__empty_string, &var.std__empty_string);
  define_single_assign_static("std", "matches_file_pattern", get__std__matches_file_pattern, &var.std__matches_file_pattern);
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
  define_method("types", "octet_string", poly_idx__length_of, func__24_1_types__octet_string_length_of);
  define_method("types", "quad_octet_string", poly_idx__length_of, func__25_1_types__quad_octet_string_length_of);
  define_method("types", "octet_string", poly_idx__equal, func__26_1_types__octet_string_equal);
  define_method("types", "quad_octet_string", poly_idx__equal, func__27_1_types__quad_octet_string_equal);
  define_method("types", "octet_string", poly_idx__count_character_occurrences, func__28_1_types__octet_string_count_character_occurrences);
  define_method("types", "quad_octet_string", poly_idx__count_character_occurrences, func__29_1_types__quad_octet_string_count_character_occurrences);
  define_method("types", "octet_string", poly_idx__less, func__30_1_types__octet_string_less);
  define_method("types", "quad_octet_string", poly_idx__less, func__31_1_types__quad_octet_string_less);
  define_method("types", "octet_string", poly_idx__hash, func__32_1_types__octet_string_hash);
  define_method("types", "quad_octet_string", poly_idx__hash, func__33_1_types__quad_octet_string_hash);
  define_method("types", "string", poly_idx__to_string, func__34_1_types__string_to_string);
  define_method("types", "string", poly_idx__serialize, func__35_1_types__string_serialize);
  define_method("types", "string", poly_idx__parse_integer, func__36_1_types__string_parse_integer);
  define_method("types", "octet_string", poly_idx__push, func__39_1_types__octet_string_push);
  define_method("types", "quad_octet_string", poly_idx__push, func__40_1_types__quad_octet_string_push);
  define_method("types", "octet_string", poly_idx__append, func__41_1_types__octet_string_append);
  define_method("types", "quad_octet_string", poly_idx__append, func__42_1_types__quad_octet_string_append);
  define_method("types", "string", poly_idx__parse_real, func__43_1_types__string_parse_real);
  define_method("types", "octet_string", poly_idx__range, func__44_1_types__octet_string_range);
  define_method("types", "quad_octet_string", poly_idx__range, func__45_1_types__quad_octet_string_range);
  define_method("types", "octet_string", poly_idx__is_a_latin_1_string, func__47_1_types__octet_string_is_a_latin_1_string);
  define_method("types", "quad_octet_string", poly_idx__is_a_latin_1_string, func__48_1_types__quad_octet_string_is_a_latin_1_string);
  define_method("types", "octet_string", poly_idx__to_utf8, func__50_1_types__octet_string_to_utf8);
  define_method("types", "quad_octet_string", poly_idx__to_utf8, func__51_1_types__quad_octet_string_to_utf8);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__string_primitives(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_string, create_function(type__std__is_a_string, -1));
  assign_value(&var.std__count_character_occurrences, create_function(type__std__count_character_occurrences, -1));
  assign_value(&var.std__to_utf8, create_function(type__std__to_utf8, -1));
  assign_value(&var.std__is_a_latin_1_string, create_function(type__std__is_a_latin_1_string, -1));
  assign_value(&var.types__string, get__types__generic_list());
  assign_variable(&var.types__octet_string, &var.types__string);
  assign_variable(&var.types__quad_octet_string, &var.types__string);
  assign_variable(&var.std__matches_file_pattern, &func__46_1_std__matches_file_pattern);
  assign_variable(&var.std__from_utf8, &func__49_1_std__from_utf8);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__string_primitives(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__string_primitives);
}
