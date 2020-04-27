#include <limits.h>
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
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT NODE *from_long(long val);
IMPORT NODE *from_bool(int val);
IMPORT NODE *boolean_false;
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *from_uint32_string(const uint32_t *str, long len);
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_cell(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *undefined;
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_c_function(const char *name, void *func);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
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
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__hash;
static NODE_GETTER get__hash;
static NODE_GETTER get__hex;
static NODE_GETTER get_value_or_future__hex;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__is_a_character;
static NODE_GETTER get__is_a_character;
static NODE_GETTER get__is_a_lower_case_letter_character;
static NODE_GETTER get_value_or_future__is_a_lower_case_letter_character;
static NODE_GETTER get__is_an_upper_case_letter_character;
static NODE_GETTER get_value_or_future__is_an_upper_case_letter_character;
static int poly_idx__less;
static NODE_GETTER get__less;
static int poly_idx__minus;
static NODE_GETTER get__minus;
static int poly_idx__plus;
static NODE_GETTER get__plus;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static int poly_idx__serialize;
static NODE_GETTER get__serialize;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__sequence;
static NODE_GETTER get_value_or_future__std__sequence;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static int poly_idx__to_integer;
static NODE_GETTER get__to_integer;
static int poly_idx__to_lower_case;
static NODE_GETTER get__to_lower_case;
static int poly_idx__to_string;
static NODE_GETTER get__to_string;
static int poly_idx__to_upper_case;
static NODE_GETTER get__to_upper_case;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static struct {
  NODE *std__is_a_character;
  NODE *types__character;
  NODE *std__character;
  NODE *std__is_a_whitespace_character;
  NODE *std__is_a_digit;
  NODE *std__is_a_letter;
  NODE *std__is_a_lower_case_letter;
  NODE *std__is_an_upper_case_letter;
  NODE *std__is_a_letter_character;
  NODE *std__is_a_lower_case_letter_character;
  NODE *std__is_an_upper_case_letter_character;
  NODE *std__is_a_vowel;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__is_a_character;
static void type__std__is_a_character(void);
static NODE *get__std__is_a_character(void) {
  return var.std__is_a_character;
}

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  uint32_t code;
} CHARACTER;
static NODE *get__types__character(void) {
  return var.types__character;
}
static NODE *create__types__character(uint32_t code);

static uint32_t func__types__character___to_uchar32(NODE *node);
static void entry__std__character_1(void);
static NODE *func__std__character_1;
static NODE *get__std__character(void) {
  return var.std__character;
}
static void entry__types__character__plus_1(void);
static NODE *func__types__character__plus_1;
static void entry__types__character__minus_1(void);
static NODE *func__types__character__minus_1;
static void entry__types__character__equal_1(void);
static NODE *func__types__character__equal_1;
static void entry__types__character__less_1(void);
static NODE *func__types__character__less_1;
static void entry__types__character__hash_1(void);
static NODE *func__types__character__hash_1;
static void entry__types__character__to_string_1(void);
static NODE *func__types__character__to_string_1;
static void entry__types__character__to_integer_1(void);
static NODE *func__types__character__to_integer_1;

static long func__types__character___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__std__is_a_whitespace_character_1;
static void entry__std__is_a_whitespace_character_1(void);
static FRAME_INFO frame__std__is_a_whitespace_character_1 = {1, {"chr"}};
static void cont__std__is_a_whitespace_character_2(void);
static NODE *func__std__is_a_whitespace_character_3;
static void entry__std__is_a_whitespace_character_3(void);
static FRAME_INFO frame__std__is_a_whitespace_character_3 = {1, {"chr"}};
static void cont__std__is_a_whitespace_character_4(void);
static NODE *func__std__is_a_whitespace_character_5;
static void entry__std__is_a_whitespace_character_5(void);
static FRAME_INFO frame__std__is_a_whitespace_character_5 = {1, {"chr"}};
static void cont__std__is_a_whitespace_character_6(void);
static NODE *func__std__is_a_whitespace_character_7;
static void entry__std__is_a_whitespace_character_7(void);
static FRAME_INFO frame__std__is_a_whitespace_character_7 = {1, {"chr"}};
static void cont__std__is_a_whitespace_character_8(void);
static void cont__std__is_a_whitespace_character_9(void);
static void cont__std__is_a_whitespace_character_10(void);
static void cont__std__is_a_whitespace_character_11(void);
static NODE *get__std__is_a_whitespace_character(void) {
  return var.std__is_a_whitespace_character;
}
static NODE *func__std__is_a_digit_1;
static void entry__std__is_a_digit_1(void);
static FRAME_INFO frame__std__is_a_digit_1 = {1, {"chr"}};
static void cont__std__is_a_digit_2(void);
static void cont__std__is_a_digit_3(void);
static NODE *func__std__is_a_digit_4;
static void entry__std__is_a_digit_4(void);
static FRAME_INFO frame__std__is_a_digit_4 = {1, {"chr"}};
static void cont__std__is_a_digit_5(void);
static void cont__std__is_a_digit_6(void);
static void cont__std__is_a_digit_7(void);
static NODE *get__std__is_a_digit(void) {
  return var.std__is_a_digit;
}
static NODE *func__std__is_a_letter_1;
static void entry__std__is_a_letter_1(void);
static FRAME_INFO frame__std__is_a_letter_1 = {1, {"chr"}};
static void cont__std__is_a_letter_2(void);
static void cont__std__is_a_letter_3(void);
static NODE *func__std__is_a_letter_4;
static void entry__std__is_a_letter_4(void);
static FRAME_INFO frame__std__is_a_letter_4 = {1, {"chr"}};
static void cont__std__is_a_letter_5(void);
static void cont__std__is_a_letter_6(void);
static void cont__std__is_a_letter_7(void);
static NODE *func__std__is_a_letter_8;
static void entry__std__is_a_letter_8(void);
static FRAME_INFO frame__std__is_a_letter_8 = {1, {"chr"}};
static void cont__std__is_a_letter_9(void);
static void cont__std__is_a_letter_10(void);
static NODE *func__std__is_a_letter_11;
static void entry__std__is_a_letter_11(void);
static FRAME_INFO frame__std__is_a_letter_11 = {1, {"chr"}};
static void cont__std__is_a_letter_12(void);
static void cont__std__is_a_letter_13(void);
static void cont__std__is_a_letter_14(void);
static void cont__std__is_a_letter_15(void);
static NODE *get__std__is_a_letter(void) {
  return var.std__is_a_letter;
}
static NODE *func__std__is_a_lower_case_letter_1;
static void entry__std__is_a_lower_case_letter_1(void);
static FRAME_INFO frame__std__is_a_lower_case_letter_1 = {1, {"chr"}};
static void cont__std__is_a_lower_case_letter_2(void);
static void cont__std__is_a_lower_case_letter_3(void);
static NODE *func__std__is_a_lower_case_letter_4;
static void entry__std__is_a_lower_case_letter_4(void);
static FRAME_INFO frame__std__is_a_lower_case_letter_4 = {1, {"chr"}};
static void cont__std__is_a_lower_case_letter_5(void);
static void cont__std__is_a_lower_case_letter_6(void);
static void cont__std__is_a_lower_case_letter_7(void);
static NODE *get__std__is_a_lower_case_letter(void) {
  return var.std__is_a_lower_case_letter;
}
static NODE *func__std__is_an_upper_case_letter_1;
static void entry__std__is_an_upper_case_letter_1(void);
static FRAME_INFO frame__std__is_an_upper_case_letter_1 = {1, {"chr"}};
static void cont__std__is_an_upper_case_letter_2(void);
static void cont__std__is_an_upper_case_letter_3(void);
static NODE *func__std__is_an_upper_case_letter_4;
static void entry__std__is_an_upper_case_letter_4(void);
static FRAME_INFO frame__std__is_an_upper_case_letter_4 = {1, {"chr"}};
static void cont__std__is_an_upper_case_letter_5(void);
static void cont__std__is_an_upper_case_letter_6(void);
static void cont__std__is_an_upper_case_letter_7(void);
static NODE *get__std__is_an_upper_case_letter(void) {
  return var.std__is_an_upper_case_letter;
}
static NODE *func__std__is_a_letter_character_1;
static void entry__std__is_a_letter_character_1(void);
static FRAME_INFO frame__std__is_a_letter_character_1 = {1, {"chr"}};
static void cont__std__is_a_letter_character_2(void);
static void cont__std__is_a_letter_character_3(void);
static NODE *func__std__is_a_letter_character_4;
static void entry__std__is_a_letter_character_4(void);
static FRAME_INFO frame__std__is_a_letter_character_4 = {1, {"chr"}};
static void cont__std__is_a_letter_character_5(void);
static void cont__std__is_a_letter_character_6(void);
static void cont__std__is_a_letter_character_7(void);
static NODE *func__std__is_a_letter_character_8;
static void entry__std__is_a_letter_character_8(void);
static FRAME_INFO frame__std__is_a_letter_character_8 = {1, {"chr"}};
static void cont__std__is_a_letter_character_9(void);
static void cont__std__is_a_letter_character_10(void);
static NODE *func__std__is_a_letter_character_11;
static void entry__std__is_a_letter_character_11(void);
static FRAME_INFO frame__std__is_a_letter_character_11 = {1, {"chr"}};
static void cont__std__is_a_letter_character_12(void);
static void cont__std__is_a_letter_character_13(void);
static void cont__std__is_a_letter_character_14(void);
static NODE *func__std__is_a_letter_character_15;
static void entry__std__is_a_letter_character_15(void);
static FRAME_INFO frame__std__is_a_letter_character_15 = {1, {"chr"}};
static void cont__std__is_a_letter_character_16(void);
static void cont__std__is_a_letter_character_17(void);
static NODE *func__std__is_a_letter_character_18;
static void entry__std__is_a_letter_character_18(void);
static FRAME_INFO frame__std__is_a_letter_character_18 = {1, {"chr"}};
static void cont__std__is_a_letter_character_19(void);
static void cont__std__is_a_letter_character_20(void);
static NODE *func__std__is_a_letter_character_21;
static void entry__std__is_a_letter_character_21(void);
static FRAME_INFO frame__std__is_a_letter_character_21 = {1, {"chr"}};
static void cont__std__is_a_letter_character_22(void);
static void cont__std__is_a_letter_character_23(void);
static NODE *func__std__is_a_letter_character_24;
static void entry__std__is_a_letter_character_24(void);
static FRAME_INFO frame__std__is_a_letter_character_24 = {1, {"chr"}};
static void cont__std__is_a_letter_character_25(void);
static void cont__std__is_a_letter_character_26(void);
static void cont__std__is_a_letter_character_27(void);
static void cont__std__is_a_letter_character_28(void);
static void cont__std__is_a_letter_character_29(void);
static void cont__std__is_a_letter_character_30(void);
static void cont__std__is_a_letter_character_31(void);
static NODE *get__std__is_a_letter_character(void) {
  return var.std__is_a_letter_character;
}
static NODE *func__std__is_a_lower_case_letter_character_1;
static void entry__std__is_a_lower_case_letter_character_1(void);
static FRAME_INFO frame__std__is_a_lower_case_letter_character_1 = {1, {"chr"}};
static void cont__std__is_a_lower_case_letter_character_2(void);
static void cont__std__is_a_lower_case_letter_character_3(void);
static NODE *func__std__is_a_lower_case_letter_character_4;
static void entry__std__is_a_lower_case_letter_character_4(void);
static FRAME_INFO frame__std__is_a_lower_case_letter_character_4 = {1, {"chr"}};
static void cont__std__is_a_lower_case_letter_character_5(void);
static void cont__std__is_a_lower_case_letter_character_6(void);
static void cont__std__is_a_lower_case_letter_character_7(void);
static NODE *func__std__is_a_lower_case_letter_character_8;
static void entry__std__is_a_lower_case_letter_character_8(void);
static FRAME_INFO frame__std__is_a_lower_case_letter_character_8 = {1, {"chr"}};
static void cont__std__is_a_lower_case_letter_character_9(void);
static void cont__std__is_a_lower_case_letter_character_10(void);
static NODE *func__std__is_a_lower_case_letter_character_11;
static void entry__std__is_a_lower_case_letter_character_11(void);
static FRAME_INFO frame__std__is_a_lower_case_letter_character_11 = {1, {"chr"}};
static void cont__std__is_a_lower_case_letter_character_12(void);
static void cont__std__is_a_lower_case_letter_character_13(void);
static NODE *func__std__is_a_lower_case_letter_character_14;
static void entry__std__is_a_lower_case_letter_character_14(void);
static FRAME_INFO frame__std__is_a_lower_case_letter_character_14 = {1, {"chr"}};
static void cont__std__is_a_lower_case_letter_character_15(void);
static void cont__std__is_a_lower_case_letter_character_16(void);
static NODE *func__std__is_a_lower_case_letter_character_17;
static void entry__std__is_a_lower_case_letter_character_17(void);
static FRAME_INFO frame__std__is_a_lower_case_letter_character_17 = {1, {"chr"}};
static void cont__std__is_a_lower_case_letter_character_18(void);
static void cont__std__is_a_lower_case_letter_character_19(void);
static void cont__std__is_a_lower_case_letter_character_20(void);
static void cont__std__is_a_lower_case_letter_character_21(void);
static void cont__std__is_a_lower_case_letter_character_22(void);
static void cont__std__is_a_lower_case_letter_character_23(void);
static NODE *get__std__is_a_lower_case_letter_character(void) {
  return var.std__is_a_lower_case_letter_character;
}
static NODE *func__std__is_an_upper_case_letter_character_1;
static void entry__std__is_an_upper_case_letter_character_1(void);
static FRAME_INFO frame__std__is_an_upper_case_letter_character_1 = {1, {"chr"}};
static void cont__std__is_an_upper_case_letter_character_2(void);
static void cont__std__is_an_upper_case_letter_character_3(void);
static NODE *func__std__is_an_upper_case_letter_character_4;
static void entry__std__is_an_upper_case_letter_character_4(void);
static FRAME_INFO frame__std__is_an_upper_case_letter_character_4 = {1, {"chr"}};
static void cont__std__is_an_upper_case_letter_character_5(void);
static void cont__std__is_an_upper_case_letter_character_6(void);
static void cont__std__is_an_upper_case_letter_character_7(void);
static NODE *func__std__is_an_upper_case_letter_character_8;
static void entry__std__is_an_upper_case_letter_character_8(void);
static FRAME_INFO frame__std__is_an_upper_case_letter_character_8 = {1, {"chr"}};
static void cont__std__is_an_upper_case_letter_character_9(void);
static void cont__std__is_an_upper_case_letter_character_10(void);
static NODE *func__std__is_an_upper_case_letter_character_11;
static void entry__std__is_an_upper_case_letter_character_11(void);
static FRAME_INFO frame__std__is_an_upper_case_letter_character_11 = {1, {"chr"}};
static void cont__std__is_an_upper_case_letter_character_12(void);
static void cont__std__is_an_upper_case_letter_character_13(void);
static NODE *func__std__is_an_upper_case_letter_character_14;
static void entry__std__is_an_upper_case_letter_character_14(void);
static FRAME_INFO frame__std__is_an_upper_case_letter_character_14 = {1, {"chr"}};
static void cont__std__is_an_upper_case_letter_character_15(void);
static void cont__std__is_an_upper_case_letter_character_16(void);
static NODE *func__std__is_an_upper_case_letter_character_17;
static void entry__std__is_an_upper_case_letter_character_17(void);
static FRAME_INFO frame__std__is_an_upper_case_letter_character_17 = {1, {"chr"}};
static void cont__std__is_an_upper_case_letter_character_18(void);
static void cont__std__is_an_upper_case_letter_character_19(void);
static void cont__std__is_an_upper_case_letter_character_20(void);
static void cont__std__is_an_upper_case_letter_character_21(void);
static void cont__std__is_an_upper_case_letter_character_22(void);
static void cont__std__is_an_upper_case_letter_character_23(void);
static NODE *get__std__is_an_upper_case_letter_character(void) {
  return var.std__is_an_upper_case_letter_character;
}
static NODE *func__types__character__to_lower_case_1;
static void entry__types__character__to_lower_case_1(void);
static FRAME_INFO frame__types__character__to_lower_case_1 = {2, {"chr", "return"}};
static void cont__types__character__to_lower_case_2(void);
static NODE *func__types__character__to_lower_case_3;
static void entry__types__character__to_lower_case_3(void);
static FRAME_INFO frame__types__character__to_lower_case_3 = {2, {"return", "chr"}};
static void cont__types__character__to_lower_case_4(void);
static NODE *func__types__character__to_lower_case_5;
static void entry__types__character__to_lower_case_5(void);
static FRAME_INFO frame__types__character__to_lower_case_5 = {2, {"return", "chr"}};
static void cont__types__character__to_lower_case_6(void);
static NODE *func__types__character__to_upper_case_1;
static void entry__types__character__to_upper_case_1(void);
static FRAME_INFO frame__types__character__to_upper_case_1 = {2, {"chr", "return"}};
static void cont__types__character__to_upper_case_2(void);
static NODE *func__types__character__to_upper_case_3;
static void entry__types__character__to_upper_case_3(void);
static FRAME_INFO frame__types__character__to_upper_case_3 = {2, {"return", "chr"}};
static void cont__types__character__to_upper_case_4(void);
static NODE *func__types__character__to_upper_case_5;
static void entry__types__character__to_upper_case_5(void);
static FRAME_INFO frame__types__character__to_upper_case_5 = {2, {"return", "chr"}};
static void cont__types__character__to_upper_case_6(void);
static NODE *func__std__is_a_vowel_1;
static void entry__std__is_a_vowel_1(void);
static FRAME_INFO frame__std__is_a_vowel_1 = {1, {"chr"}};
static void cont__std__is_a_vowel_2(void);
static NODE *func__std__is_a_vowel_3;
static void entry__std__is_a_vowel_3(void);
static FRAME_INFO frame__std__is_a_vowel_3 = {0, {}};
static NODE *func__std__is_a_vowel_4;
static void entry__std__is_a_vowel_4(void);
static FRAME_INFO frame__std__is_a_vowel_4 = {0, {}};
static NODE *get__std__is_a_vowel(void) {
  return var.std__is_a_vowel;
}
static NODE *func__types__character__serialize_1;
static void entry__types__character__serialize_1(void);
static FRAME_INFO frame__types__character__serialize_1 = {3, {"self", "indent", "buf"}};
static NODE *string__578a5af303e9cc6;
static void cont__types__character__serialize_3(void);
static NODE *func__types__character__serialize_4;
static void entry__types__character__serialize_4(void);
static FRAME_INFO frame__types__character__serialize_4 = {1, {"self"}};
static void cont__types__character__serialize_5(void);
static NODE *func__types__character__serialize_6;
static void entry__types__character__serialize_6(void);
static FRAME_INFO frame__types__character__serialize_6 = {1, {"self"}};
static void cont__types__character__serialize_7(void);
static NODE *func__types__character__serialize_8;
static void entry__types__character__serialize_8(void);
static FRAME_INFO frame__types__character__serialize_8 = {1, {"self"}};
static void cont__types__character__serialize_9(void);
static NODE *func__types__character__serialize_10;
static void entry__types__character__serialize_10(void);
static FRAME_INFO frame__types__character__serialize_10 = {1, {"self"}};
static void cont__types__character__serialize_11(void);
static void cont__types__character__serialize_12(void);
static void cont__types__character__serialize_13(void);
static void cont__types__character__serialize_14(void);
static void cont__types__character__serialize_15(void);
static NODE *func__types__character__serialize_16;
static void entry__types__character__serialize_16(void);
static FRAME_INFO frame__types__character__serialize_16 = {2, {"buf", "self"}};
static void cont__types__character__serialize_17(void);
static void cont__types__character__serialize_18(void);
static NODE *string__fa728415fa96bb4;
static void cont__types__character__serialize_20(void);
static void cont__types__character__serialize_21(void);
static NODE *func__types__character__serialize_22;
static void entry__types__character__serialize_22(void);
static FRAME_INFO frame__types__character__serialize_22 = {2, {"buf", "self"}};
static void cont__types__character__serialize_23(void);
static void cont__types__character__serialize_24(void);
static void cont__types__character__serialize_25(void);
void run__basic__types__character(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_character, NULL, 25, 25, 2, 20},
  {run__basic__types__character, NULL, },
  {entry__std__character_1, NULL, 71, 75, 3, 2},
  {entry__types__character__plus_1, NULL, 86, 91, 3, 2},
  {entry__types__character__minus_1, NULL, 102, 113, 3, 2},
  {entry__types__character__equal_1, NULL, 118, 124, 3, 2},
  {entry__types__character__less_1, NULL, 129, 135, 3, 2},
  {entry__types__character__hash_1, NULL, 140, 146, 3, 2},
  {entry__types__character__to_string_1, NULL, 151, 160, 3, 2},
  {entry__types__character__to_integer_1, NULL, 165, 168, 3, 2},
  {entry__std__is_a_whitespace_character_7, NULL, 201, 201, 54, 66},
  {cont__std__is_a_whitespace_character_8, &frame__std__is_a_whitespace_character_7, 201, 201, 54, 66},
  {entry__std__is_a_whitespace_character_5, NULL, 201, 201, 37, 49},
  {cont__std__is_a_whitespace_character_6, &frame__std__is_a_whitespace_character_5, 201, 201, 37, 66},
  {cont__std__is_a_whitespace_character_9, &frame__std__is_a_whitespace_character_5, 201, 201, 37, 66},
  {entry__std__is_a_whitespace_character_3, NULL, 201, 201, 20, 32},
  {cont__std__is_a_whitespace_character_4, &frame__std__is_a_whitespace_character_3, 201, 201, 20, 66},
  {cont__std__is_a_whitespace_character_10, &frame__std__is_a_whitespace_character_3, 201, 201, 20, 66},
  {entry__std__is_a_whitespace_character_1, NULL, 201, 201, 6, 15},
  {cont__std__is_a_whitespace_character_2, &frame__std__is_a_whitespace_character_1, 201, 201, 6, 66},
  {cont__std__is_a_whitespace_character_11, &frame__std__is_a_whitespace_character_1, 201, 201, 3, 66},
  {entry__std__is_a_digit_4, NULL, 211, 211, 20, 29},
  {cont__std__is_a_digit_5, &frame__std__is_a_digit_4, 211, 211, 20, 29},
  {cont__std__is_a_digit_6, &frame__std__is_a_digit_4, 211, 211, 20, 29},
  {entry__std__is_a_digit_1, NULL, 211, 211, 6, 15},
  {cont__std__is_a_digit_2, &frame__std__is_a_digit_1, 211, 211, 6, 15},
  {cont__std__is_a_digit_3, &frame__std__is_a_digit_1, 211, 211, 6, 29},
  {cont__std__is_a_digit_7, &frame__std__is_a_digit_1, 211, 211, 3, 29},
  {entry__std__is_a_letter_4, NULL, 224, 224, 20, 29},
  {cont__std__is_a_letter_5, &frame__std__is_a_letter_4, 224, 224, 20, 29},
  {cont__std__is_a_letter_6, &frame__std__is_a_letter_4, 224, 224, 20, 29},
  {entry__std__is_a_letter_11, NULL, 224, 224, 48, 57},
  {cont__std__is_a_letter_12, &frame__std__is_a_letter_11, 224, 224, 48, 57},
  {cont__std__is_a_letter_13, &frame__std__is_a_letter_11, 224, 224, 48, 57},
  {entry__std__is_a_letter_8, NULL, 224, 224, 34, 43},
  {cont__std__is_a_letter_9, &frame__std__is_a_letter_8, 224, 224, 34, 43},
  {cont__std__is_a_letter_10, &frame__std__is_a_letter_8, 224, 224, 34, 57},
  {cont__std__is_a_letter_14, &frame__std__is_a_letter_8, 224, 224, 34, 57},
  {entry__std__is_a_letter_1, NULL, 224, 224, 6, 15},
  {cont__std__is_a_letter_2, &frame__std__is_a_letter_1, 224, 224, 6, 15},
  {cont__std__is_a_letter_3, &frame__std__is_a_letter_1, 224, 224, 6, 29},
  {cont__std__is_a_letter_7, &frame__std__is_a_letter_1, 224, 224, 6, 57},
  {cont__std__is_a_letter_15, &frame__std__is_a_letter_1, 224, 224, 3, 57},
  {entry__std__is_a_lower_case_letter_4, NULL, 237, 237, 20, 29},
  {cont__std__is_a_lower_case_letter_5, &frame__std__is_a_lower_case_letter_4, 237, 237, 20, 29},
  {cont__std__is_a_lower_case_letter_6, &frame__std__is_a_lower_case_letter_4, 237, 237, 20, 29},
  {entry__std__is_a_lower_case_letter_1, NULL, 237, 237, 6, 15},
  {cont__std__is_a_lower_case_letter_2, &frame__std__is_a_lower_case_letter_1, 237, 237, 6, 15},
  {cont__std__is_a_lower_case_letter_3, &frame__std__is_a_lower_case_letter_1, 237, 237, 6, 29},
  {cont__std__is_a_lower_case_letter_7, &frame__std__is_a_lower_case_letter_1, 237, 237, 3, 29},
  {entry__std__is_an_upper_case_letter_4, NULL, 250, 250, 20, 29},
  {cont__std__is_an_upper_case_letter_5, &frame__std__is_an_upper_case_letter_4, 250, 250, 20, 29},
  {cont__std__is_an_upper_case_letter_6, &frame__std__is_an_upper_case_letter_4, 250, 250, 20, 29},
  {entry__std__is_an_upper_case_letter_1, NULL, 250, 250, 6, 15},
  {cont__std__is_an_upper_case_letter_2, &frame__std__is_an_upper_case_letter_1, 250, 250, 6, 15},
  {cont__std__is_an_upper_case_letter_3, &frame__std__is_an_upper_case_letter_1, 250, 250, 6, 29},
  {cont__std__is_an_upper_case_letter_7, &frame__std__is_an_upper_case_letter_1, 250, 250, 3, 29},
  {entry__std__is_a_letter_character_4, NULL, 266, 266, 21, 30},
  {cont__std__is_a_letter_character_5, &frame__std__is_a_letter_character_4, 266, 266, 21, 30},
  {cont__std__is_a_letter_character_6, &frame__std__is_a_letter_character_4, 266, 266, 21, 30},
  {entry__std__is_a_letter_character_11, NULL, 267, 267, 21, 30},
  {cont__std__is_a_letter_character_12, &frame__std__is_a_letter_character_11, 267, 267, 21, 30},
  {cont__std__is_a_letter_character_13, &frame__std__is_a_letter_character_11, 267, 267, 21, 30},
  {entry__std__is_a_letter_character_24, NULL, 268, 268, 49, 58},
  {cont__std__is_a_letter_character_25, &frame__std__is_a_letter_character_24, 268, 268, 49, 58},
  {cont__std__is_a_letter_character_26, &frame__std__is_a_letter_character_24, 268, 268, 49, 58},
  {entry__std__is_a_letter_character_21, NULL, 268, 268, 35, 44},
  {cont__std__is_a_letter_character_22, &frame__std__is_a_letter_character_21, 268, 268, 35, 44},
  {cont__std__is_a_letter_character_23, &frame__std__is_a_letter_character_21, 268, 268, 35, 58},
  {cont__std__is_a_letter_character_27, &frame__std__is_a_letter_character_21, 268, 268, 35, 58},
  {entry__std__is_a_letter_character_18, NULL, 268, 268, 21, 30},
  {cont__std__is_a_letter_character_19, &frame__std__is_a_letter_character_18, 268, 268, 21, 30},
  {cont__std__is_a_letter_character_20, &frame__std__is_a_letter_character_18, 268, 268, 21, 58},
  {cont__std__is_a_letter_character_28, &frame__std__is_a_letter_character_18, 268, 268, 21, 58},
  {entry__std__is_a_letter_character_15, NULL, 268, 268, 7, 16},
  {cont__std__is_a_letter_character_16, &frame__std__is_a_letter_character_15, 268, 268, 7, 16},
  {cont__std__is_a_letter_character_17, &frame__std__is_a_letter_character_15, 268, 268, 7, 58},
  {cont__std__is_a_letter_character_29, &frame__std__is_a_letter_character_15, 268, 268, 7, 58},
  {entry__std__is_a_letter_character_8, NULL, 267, 267, 7, 16},
  {cont__std__is_a_letter_character_9, &frame__std__is_a_letter_character_8, 267, 267, 7, 16},
  {cont__std__is_a_letter_character_10, &frame__std__is_a_letter_character_8, 267, 267, 7, 30},
  {cont__std__is_a_letter_character_14, &frame__std__is_a_letter_character_8, 268, 268, 7, 58},
  {cont__std__is_a_letter_character_30, &frame__std__is_a_letter_character_8, },
  {entry__std__is_a_letter_character_1, NULL, 266, 266, 7, 16},
  {cont__std__is_a_letter_character_2, &frame__std__is_a_letter_character_1, 266, 266, 7, 16},
  {cont__std__is_a_letter_character_3, &frame__std__is_a_letter_character_1, 266, 266, 7, 30},
  {cont__std__is_a_letter_character_7, &frame__std__is_a_letter_character_1, },
  {cont__std__is_a_letter_character_31, &frame__std__is_a_letter_character_1, 264, 268, 3, 59},
  {entry__std__is_a_lower_case_letter_character_4, NULL, 284, 284, 21, 30},
  {cont__std__is_a_lower_case_letter_character_5, &frame__std__is_a_lower_case_letter_character_4, 284, 284, 21, 30},
  {cont__std__is_a_lower_case_letter_character_6, &frame__std__is_a_lower_case_letter_character_4, 284, 284, 21, 30},
  {entry__std__is_a_lower_case_letter_character_17, NULL, 285, 285, 49, 58},
  {cont__std__is_a_lower_case_letter_character_18, &frame__std__is_a_lower_case_letter_character_17, 285, 285, 49, 58},
  {cont__std__is_a_lower_case_letter_character_19, &frame__std__is_a_lower_case_letter_character_17, 285, 285, 49, 58},
  {entry__std__is_a_lower_case_letter_character_14, NULL, 285, 285, 35, 44},
  {cont__std__is_a_lower_case_letter_character_15, &frame__std__is_a_lower_case_letter_character_14, 285, 285, 35, 44},
  {cont__std__is_a_lower_case_letter_character_16, &frame__std__is_a_lower_case_letter_character_14, 285, 285, 35, 58},
  {cont__std__is_a_lower_case_letter_character_20, &frame__std__is_a_lower_case_letter_character_14, 285, 285, 35, 58},
  {entry__std__is_a_lower_case_letter_character_11, NULL, 285, 285, 21, 30},
  {cont__std__is_a_lower_case_letter_character_12, &frame__std__is_a_lower_case_letter_character_11, 285, 285, 21, 30},
  {cont__std__is_a_lower_case_letter_character_13, &frame__std__is_a_lower_case_letter_character_11, 285, 285, 21, 58},
  {cont__std__is_a_lower_case_letter_character_21, &frame__std__is_a_lower_case_letter_character_11, 285, 285, 21, 58},
  {entry__std__is_a_lower_case_letter_character_8, NULL, 285, 285, 7, 16},
  {cont__std__is_a_lower_case_letter_character_9, &frame__std__is_a_lower_case_letter_character_8, 285, 285, 7, 16},
  {cont__std__is_a_lower_case_letter_character_10, &frame__std__is_a_lower_case_letter_character_8, 285, 285, 7, 58},
  {cont__std__is_a_lower_case_letter_character_22, &frame__std__is_a_lower_case_letter_character_8, 285, 285, 7, 58},
  {entry__std__is_a_lower_case_letter_character_1, NULL, 284, 284, 7, 16},
  {cont__std__is_a_lower_case_letter_character_2, &frame__std__is_a_lower_case_letter_character_1, 284, 284, 7, 16},
  {cont__std__is_a_lower_case_letter_character_3, &frame__std__is_a_lower_case_letter_character_1, 284, 284, 7, 30},
  {cont__std__is_a_lower_case_letter_character_7, &frame__std__is_a_lower_case_letter_character_1, 283, 285, 5, 57},
  {cont__std__is_a_lower_case_letter_character_23, &frame__std__is_a_lower_case_letter_character_1, 282, 285, 3, 59},
  {entry__std__is_an_upper_case_letter_character_4, NULL, 301, 301, 21, 30},
  {cont__std__is_an_upper_case_letter_character_5, &frame__std__is_an_upper_case_letter_character_4, 301, 301, 21, 30},
  {cont__std__is_an_upper_case_letter_character_6, &frame__std__is_an_upper_case_letter_character_4, 301, 301, 21, 30},
  {entry__std__is_an_upper_case_letter_character_17, NULL, 302, 302, 49, 58},
  {cont__std__is_an_upper_case_letter_character_18, &frame__std__is_an_upper_case_letter_character_17, 302, 302, 49, 58},
  {cont__std__is_an_upper_case_letter_character_19, &frame__std__is_an_upper_case_letter_character_17, 302, 302, 49, 58},
  {entry__std__is_an_upper_case_letter_character_14, NULL, 302, 302, 35, 44},
  {cont__std__is_an_upper_case_letter_character_15, &frame__std__is_an_upper_case_letter_character_14, 302, 302, 35, 44},
  {cont__std__is_an_upper_case_letter_character_16, &frame__std__is_an_upper_case_letter_character_14, 302, 302, 35, 58},
  {cont__std__is_an_upper_case_letter_character_20, &frame__std__is_an_upper_case_letter_character_14, 302, 302, 35, 58},
  {entry__std__is_an_upper_case_letter_character_11, NULL, 302, 302, 21, 30},
  {cont__std__is_an_upper_case_letter_character_12, &frame__std__is_an_upper_case_letter_character_11, 302, 302, 21, 30},
  {cont__std__is_an_upper_case_letter_character_13, &frame__std__is_an_upper_case_letter_character_11, 302, 302, 21, 58},
  {cont__std__is_an_upper_case_letter_character_21, &frame__std__is_an_upper_case_letter_character_11, 302, 302, 21, 58},
  {entry__std__is_an_upper_case_letter_character_8, NULL, 302, 302, 7, 16},
  {cont__std__is_an_upper_case_letter_character_9, &frame__std__is_an_upper_case_letter_character_8, 302, 302, 7, 16},
  {cont__std__is_an_upper_case_letter_character_10, &frame__std__is_an_upper_case_letter_character_8, 302, 302, 7, 58},
  {cont__std__is_an_upper_case_letter_character_22, &frame__std__is_an_upper_case_letter_character_8, 302, 302, 7, 58},
  {entry__std__is_an_upper_case_letter_character_1, NULL, 301, 301, 7, 16},
  {cont__std__is_an_upper_case_letter_character_2, &frame__std__is_an_upper_case_letter_character_1, 301, 301, 7, 16},
  {cont__std__is_an_upper_case_letter_character_3, &frame__std__is_an_upper_case_letter_character_1, 301, 301, 7, 30},
  {cont__std__is_an_upper_case_letter_character_7, &frame__std__is_an_upper_case_letter_character_1, 300, 302, 5, 57},
  {cont__std__is_an_upper_case_letter_character_23, &frame__std__is_an_upper_case_letter_character_1, 299, 302, 3, 59},
  {entry__types__character__to_lower_case_3, NULL, 318, 318, 14, 21},
  {cont__types__character__to_lower_case_4, &frame__types__character__to_lower_case_3, 318, 318, 7, 21},
  {entry__types__character__to_lower_case_5, NULL, 320, 320, 7, 16},
  {entry__types__character__to_lower_case_1, NULL, 317, 317, 5, 41},
  {cont__types__character__to_lower_case_2, &frame__types__character__to_lower_case_1, 316, 320, 3, 17},
  {cont__types__character__to_lower_case_6, &frame__types__character__to_lower_case_1, 320, 320, 17, 17},
  {entry__types__character__to_upper_case_3, NULL, 336, 336, 14, 21},
  {cont__types__character__to_upper_case_4, &frame__types__character__to_upper_case_3, 336, 336, 7, 21},
  {entry__types__character__to_upper_case_5, NULL, 338, 338, 7, 16},
  {entry__types__character__to_upper_case_1, NULL, 335, 335, 5, 40},
  {cont__types__character__to_upper_case_2, &frame__types__character__to_upper_case_1, 334, 338, 3, 17},
  {cont__types__character__to_upper_case_6, &frame__types__character__to_upper_case_1, 338, 338, 17, 17},
  {entry__std__is_a_vowel_3, NULL, 351, 351, 62, 68},
  {entry__std__is_a_vowel_4, NULL, 351, 351, 71, 78},
  {entry__std__is_a_vowel_1, NULL, 351, 351, 12, 59},
  {cont__std__is_a_vowel_2, &frame__std__is_a_vowel_1, 351, 351, 3, 78},
  {entry__types__character__serialize_10, NULL, 367, 367, 7, 22},
  {cont__types__character__serialize_11, &frame__types__character__serialize_10, 367, 367, 7, 22},
  {entry__types__character__serialize_8, NULL, 366, 366, 7, 22},
  {cont__types__character__serialize_9, &frame__types__character__serialize_8, 367, 367, 7, 22},
  {cont__types__character__serialize_12, &frame__types__character__serialize_8, },
  {entry__types__character__serialize_6, NULL, 365, 365, 7, 18},
  {cont__types__character__serialize_7, &frame__types__character__serialize_6, },
  {cont__types__character__serialize_13, &frame__types__character__serialize_6, },
  {entry__types__character__serialize_4, NULL, 364, 364, 7, 16},
  {cont__types__character__serialize_5, &frame__types__character__serialize_4, },
  {cont__types__character__serialize_14, &frame__types__character__serialize_4, },
  {entry__types__character__serialize_16, NULL, 369, 369, 37, 51},
  {cont__types__character__serialize_17, &frame__types__character__serialize_16, 369, 369, 33, 52},
  {cont__types__character__serialize_18, &frame__types__character__serialize_16, 369, 369, 19, 57},
  {cont__types__character__serialize_20, &frame__types__character__serialize_16, 369, 369, 7, 57},
  {cont__types__character__serialize_21, &frame__types__character__serialize_16, 369, 369, 57, 57},
  {entry__types__character__serialize_22, NULL, 371, 371, 7, 20},
  {cont__types__character__serialize_23, &frame__types__character__serialize_22, 371, 371, 20, 20},
  {entry__types__character__serialize_1, NULL, 363, 363, 7, 16},
  {cont__types__character__serialize_3, &frame__types__character__serialize_1, },
  {cont__types__character__serialize_15, &frame__types__character__serialize_1, 361, 371, 3, 21},
  {cont__types__character__serialize_24, &frame__types__character__serialize_1, 372, 372, 6, 23},
  {cont__types__character__serialize_25, &frame__types__character__serialize_1, 372, 372, 3, 23}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  CHARACTER character;
};
static void type__std__is_a_character(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_character);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_character, attr);
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
static NODE *character__224;
static NODE *character__9;
static NODE *character__90;
static NODE *character__122;
static NODE *character__57;
static NODE *character__65;
static NODE *character__73;
static NODE *character__10;
static NODE *character__48;
static NODE *character__13;
static NODE *character__85;
static NODE *character__126;
static NODE *character__64;
static NODE *character__215;
static NODE *character__34;
static NODE *character__111;
static NODE *character__247;
static NODE *character__255;
static NODE *character__39;
static NODE *character__105;
static NODE *character__192;
static NODE *character__32;
static NODE *character__117;
static NODE *character__101;
static NODE *character__59;
static NODE *character__97;
static NODE *character__69;
static NODE *number__0x20;
static NODE *character__223;
static NODE *character__79;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__character",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/character.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__character(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void *collect_character(CHARACTER *node) {
  CHARACTER *new_node = allocate(sizeof(CHARACTER));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->code = node->code;
  return new_node;
}

static VTABLE vtable__types__character = {
  sizeof(CHARACTER),
  (COLLECTOR *)&collect_character,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__character___to_uchar32,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__character___debug_string
};

static ATTRIBUTES attributes__types__character = {
  &vtable__types__character,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__character(void) {
  {
    runtime_error("Attempt to call a character value as a function!");
  }
}
static NODE *create__types__character(uint32_t code) {
  NODE *node = allocate(sizeof(CHARACTER));
  node->type = type__types__character;
  node->attributes = &attributes__types__character;
  node->character.code = code;
  return node;
}

NODE *runtime__from_uchar32(uint32_t code) {
  return create__types__character(code);
}

static uint32_t func__types__character___to_uchar32(NODE *node) {
  return node->character.code;
}
static void entry__std__character_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  uint32_t code = to_uint32(arguments->slots[0]);
  {
    NODE *result__node = (NODE *)(create__types__character(code));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__character__plus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long code = (long)arguments->slots[0]->character.code+to_long(arguments->slots[1]);
  if (code >= 0x100000000LL || code < 0) {
    invalid_arguments_error();
  }
  {
    NODE *result__node = (NODE *)(create__types__character((uint32_t)code));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__character__minus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__character) {
    {
    NODE *result__node = (NODE *)(from_long(
        (long)arguments->slots[0]->character.code-(long)arguments->slots[1]->character.code));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
  } else {
    long code = (long)arguments->slots[0]->character.code-to_long(arguments->slots[1]);
    if (code >= 0x100000000LL || code < 0) {
    invalid_arguments_error();
  }
    {
    NODE *result__node = (NODE *)(create__types__character((uint32_t)code));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static void entry__types__character__equal_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__character) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->character.code == arguments->slots[1]->character.code));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
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
static void entry__types__character__less_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__character) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->character.code < arguments->slots[1]->character.code));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__character__hash_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  uint32_t hash = arguments->slots[0]->character.code;
  hash *= 179234567;
  hash ^= hash >> 27 | hash << 5;
  {
    NODE *result__node = (NODE *)(from_uint32(hash));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}
static void entry__types__character__to_string_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  if (arguments->slots[0]->character.code <= 0xff) {
    char buf[1];
    buf[0] = arguments->slots[0]->character.code;
    {
    NODE *result__node = (NODE *)(from_latin_1_string(buf, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    {
    NODE *result__node = (NODE *)(from_uint32_string(&arguments->slots[0]->character.code, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static void entry__types__character__to_integer_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_uint32(arguments->slots[0]->character.code));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static long func__types__character___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  if (node->character.code == '@') {
    return debug_print(indent, buf, "'@@'");
  } else if (node->character.code == '\'') {
    return debug_print(indent, buf, "'@apos;'");
  } else if (
    node->character.code >= 0x20 && node->character.code < 0x7f /*||
    node->character.code >= 0xa0 && node->character.code < 0x100*/
  ) {
    return debug_print(indent, buf, "'%c'", node->character.code);
  } else {
    return debug_print(indent, buf, "'@0x%x;'", node->character.code);
  }
}
static void entry__std__is_a_whitespace_character_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 201: ... chr == ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_a_whitespace_character_2;
}
static void cont__std__is_a_whitespace_character_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 201: ... chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__std__is_a_whitespace_character_3, 0);
  // 201: ... chr == ' ' || chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__is_a_whitespace_character_11;
}
static void entry__std__is_a_whitespace_character_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: ... chr == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_a_whitespace_character_4;
}
static void cont__std__is_a_whitespace_character_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 201: ... chr == '@cr;' || chr == '@ht;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__std__is_a_whitespace_character_5, 0);
  // 201: ... chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__is_a_whitespace_character_10;
}
static void entry__std__is_a_whitespace_character_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: ... chr == '@cr;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__13;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_a_whitespace_character_6;
}
static void cont__std__is_a_whitespace_character_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 201: ... chr == '@ht;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__std__is_a_whitespace_character_7, 0);
  // 201: ... chr == '@cr;' || chr == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__is_a_whitespace_character_9;
}
static void entry__std__is_a_whitespace_character_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: ... chr == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_a_whitespace_character_8;
}
static void cont__std__is_a_whitespace_character_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 201: ... chr == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_whitespace_character_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 201: ... chr == '@cr;' || chr == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_whitespace_character_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 201: ... chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_whitespace_character_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 201: -> chr == ' ' || chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_a_digit_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 211: ... chr >= '0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_digit_2;
}
static void cont__std__is_a_digit_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 211: ... chr >= '0'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_digit_3;
}
static void cont__std__is_a_digit_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 211: ... chr <= '9'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_digit_4, 0);
  // 211: ... chr >= '0' && chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_digit_7;
}
static void entry__std__is_a_digit_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 211: ... chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_digit_5;
}
static void cont__std__is_a_digit_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 211: ... chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_digit_6;
}
static void cont__std__is_a_digit_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 211: ... chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_digit_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 211: -> chr >= '0' && chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_a_letter_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 224: ... chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_2;
}
static void cont__std__is_a_letter_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 224: ... chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_3;
}
static void cont__std__is_a_letter_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 224: ... chr <= 'z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__std__is_a_letter_4, 0);
  // 224: ... chr >= 'a' && chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_7;
}
static void entry__std__is_a_letter_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: ... chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_5;
}
static void cont__std__is_a_letter_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 224: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_6;
}
static void cont__std__is_a_letter_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 224: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 224: ... chr >= 'A' && chr <= 'Z'
  frame->slots[6] /* temp__6 */ = create_closure(entry__std__is_a_letter_8, 0);
  // 224: ... chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_15;
}
static void entry__std__is_a_letter_8(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: ... chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_9;
}
static void cont__std__is_a_letter_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 224: ... chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_10;
}
static void cont__std__is_a_letter_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 224: ... chr <= 'Z'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_letter_11, 0);
  // 224: ... chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_14;
}
static void entry__std__is_a_letter_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: ... chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_12;
}
static void cont__std__is_a_letter_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 224: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_13;
}
static void cont__std__is_a_letter_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 224: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 224: ... chr >= 'A' && chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 224: -> chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_a_lower_case_letter_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 237: ... chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_2;
}
static void cont__std__is_a_lower_case_letter_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 237: ... chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_3;
}
static void cont__std__is_a_lower_case_letter_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 237: ... chr <= 'z'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_lower_case_letter_4, 0);
  // 237: ... chr >= 'a' && chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_7;
}
static void entry__std__is_a_lower_case_letter_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 237: ... chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_5;
}
static void cont__std__is_a_lower_case_letter_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 237: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_6;
}
static void cont__std__is_a_lower_case_letter_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 237: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_lower_case_letter_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 237: -> chr >= 'a' && chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_an_upper_case_letter_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 250: ... chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_2;
}
static void cont__std__is_an_upper_case_letter_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 250: ... chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_3;
}
static void cont__std__is_an_upper_case_letter_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 250: ... chr <= 'Z'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_an_upper_case_letter_4, 0);
  // 250: ... chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_7;
}
static void entry__std__is_an_upper_case_letter_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 250: ... chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_5;
}
static void cont__std__is_an_upper_case_letter_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 250: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_6;
}
static void cont__std__is_an_upper_case_letter_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 250: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_an_upper_case_letter_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 250: -> chr >= 'A' && chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_a_letter_character_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 266: chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_2;
}
static void cont__std__is_a_letter_character_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 266: chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_3;
}
static void cont__std__is_a_letter_character_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 266: ... chr <= 'z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__std__is_a_letter_character_4, 0);
  // 266: chr >= 'a' && chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_7;
}
static void entry__std__is_a_letter_character_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 266: ... chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_5;
}
static void cont__std__is_a_letter_character_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 266: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_6;
}
static void cont__std__is_a_letter_character_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 266: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_character_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__6 */ = create_closure(entry__std__is_a_letter_character_8, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_31;
}
static void entry__std__is_a_letter_character_8(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 267: chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_9;
}
static void cont__std__is_a_letter_character_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 267: chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_10;
}
static void cont__std__is_a_letter_character_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 267: ... chr <= 'Z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__std__is_a_letter_character_11, 0);
  // 267: chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_14;
}
static void entry__std__is_a_letter_character_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 267: ... chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_12;
}
static void cont__std__is_a_letter_character_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 267: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_13;
}
static void cont__std__is_a_letter_character_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 267: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_character_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 268: chr >= 'À' && chr <= 'ÿ' && chr != '×' && chr != '÷'
  frame->slots[6] /* temp__6 */ = create_closure(entry__std__is_a_letter_character_15, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_30;
}
static void entry__std__is_a_letter_character_15(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 268: chr >= 'À'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__192;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_16;
}
static void cont__std__is_a_letter_character_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 268: chr >= 'À'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_17;
}
static void cont__std__is_a_letter_character_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 268: ... chr <= 'ÿ' && chr != '×' && chr != '÷'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_letter_character_18, 0);
  // 268: chr >= 'À' && chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_29;
}
static void entry__std__is_a_letter_character_18(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 268: ... chr <= 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__255;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_19;
}
static void cont__std__is_a_letter_character_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 268: ... chr <= 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_20;
}
static void cont__std__is_a_letter_character_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 268: ... chr != '×' && chr != '÷'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_letter_character_21, 0);
  // 268: ... chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_28;
}
static void entry__std__is_a_letter_character_21(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 268: ... chr != '×'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__215;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_22;
}
static void cont__std__is_a_letter_character_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 268: ... chr != '×'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_23;
}
static void cont__std__is_a_letter_character_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 268: ... chr != '÷'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_letter_character_24, 0);
  // 268: ... chr != '×' && chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_27;
}
static void entry__std__is_a_letter_character_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 268: ... chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__247;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_25;
}
static void cont__std__is_a_letter_character_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 268: ... chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_letter_character_26;
}
static void cont__std__is_a_letter_character_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 268: ... chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_character_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 268: ... chr != '×' && chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_character_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 268: ... chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_character_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 268: chr >= 'À' && chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_letter_character_30(void) {
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
static void cont__std__is_a_letter_character_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 264: ->
  // 265:   ||
  // 266:     chr >= 'a' && chr <= 'z'
  // 267:     chr >= 'A' && chr <= 'Z'
  // 268:     chr >= 'À' && chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_a_lower_case_letter_character_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 284: chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_2;
}
static void cont__std__is_a_lower_case_letter_character_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 284: chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_3;
}
static void cont__std__is_a_lower_case_letter_character_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 284: ... chr <= 'z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__std__is_a_lower_case_letter_character_4, 0);
  // 284: chr >= 'a' && chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_7;
}
static void entry__std__is_a_lower_case_letter_character_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: ... chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_5;
}
static void cont__std__is_a_lower_case_letter_character_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 284: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_6;
}
static void cont__std__is_a_lower_case_letter_character_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 284: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_lower_case_letter_character_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 285: chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  frame->slots[6] /* temp__6 */ = create_closure(entry__std__is_a_lower_case_letter_character_8, 0);
  // 283: ||
  // 284:   chr >= 'a' && chr <= 'z'
  // 285:   chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_23;
}
static void entry__std__is_a_lower_case_letter_character_8(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: chr >= 'à'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__224;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_9;
}
static void cont__std__is_a_lower_case_letter_character_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 285: chr >= 'à'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_10;
}
static void cont__std__is_a_lower_case_letter_character_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 285: ... chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_lower_case_letter_character_11, 0);
  // 285: chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_22;
}
static void entry__std__is_a_lower_case_letter_character_11(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: ... chr <= 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__255;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_12;
}
static void cont__std__is_a_lower_case_letter_character_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 285: ... chr <= 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_13;
}
static void cont__std__is_a_lower_case_letter_character_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 285: ... chr != '÷' && chr != 'ÿ'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_lower_case_letter_character_14, 0);
  // 285: ... chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_21;
}
static void entry__std__is_a_lower_case_letter_character_14(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: ... chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__247;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_15;
}
static void cont__std__is_a_lower_case_letter_character_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 285: ... chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_16;
}
static void cont__std__is_a_lower_case_letter_character_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 285: ... chr != 'ÿ'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_a_lower_case_letter_character_17, 0);
  // 285: ... chr != '÷' && chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_20;
}
static void entry__std__is_a_lower_case_letter_character_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: ... chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__255;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_18;
}
static void cont__std__is_a_lower_case_letter_character_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 285: ... chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_a_lower_case_letter_character_19;
}
static void cont__std__is_a_lower_case_letter_character_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 285: ... chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_lower_case_letter_character_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 285: ... chr != '÷' && chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_lower_case_letter_character_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 285: ... chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_lower_case_letter_character_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 285: chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_a_lower_case_letter_character_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 282: ->
  // 283:   ||
  // 284:     chr >= 'a' && chr <= 'z'
  // 285:     chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_an_upper_case_letter_character_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 301: chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_2;
}
static void cont__std__is_an_upper_case_letter_character_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 301: chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_3;
}
static void cont__std__is_an_upper_case_letter_character_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 301: ... chr <= 'Z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__std__is_an_upper_case_letter_character_4, 0);
  // 301: chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_7;
}
static void entry__std__is_an_upper_case_letter_character_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 301: ... chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_5;
}
static void cont__std__is_an_upper_case_letter_character_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 301: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_6;
}
static void cont__std__is_an_upper_case_letter_character_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 301: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_an_upper_case_letter_character_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 302: chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  frame->slots[6] /* temp__6 */ = create_closure(entry__std__is_an_upper_case_letter_character_8, 0);
  // 300: ||
  // 301:   chr >= 'A' && chr <= 'Z'
  // 302:   chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_23;
}
static void entry__std__is_an_upper_case_letter_character_8(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 302: chr >= 'À'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__192;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_9;
}
static void cont__std__is_an_upper_case_letter_character_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 302: chr >= 'À'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_10;
}
static void cont__std__is_an_upper_case_letter_character_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 302: ... chr <= 'ß' && chr != '×' && chr != 'ß'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_an_upper_case_letter_character_11, 0);
  // 302: chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_22;
}
static void entry__std__is_an_upper_case_letter_character_11(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 302: ... chr <= 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__223;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_12;
}
static void cont__std__is_an_upper_case_letter_character_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 302: ... chr <= 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_13;
}
static void cont__std__is_an_upper_case_letter_character_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 302: ... chr != '×' && chr != 'ß'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_an_upper_case_letter_character_14, 0);
  // 302: ... chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_21;
}
static void entry__std__is_an_upper_case_letter_character_14(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 302: ... chr != '×'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__215;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_15;
}
static void cont__std__is_an_upper_case_letter_character_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 302: ... chr != '×'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_16;
}
static void cont__std__is_an_upper_case_letter_character_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 302: ... chr != 'ß'
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__is_an_upper_case_letter_character_17, 0);
  // 302: ... chr != '×' && chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_20;
}
static void entry__std__is_an_upper_case_letter_character_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 302: ... chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__223;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_18;
}
static void cont__std__is_an_upper_case_letter_character_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 302: ... chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__is_an_upper_case_letter_character_19;
}
static void cont__std__is_an_upper_case_letter_character_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 302: ... chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_an_upper_case_letter_character_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 302: ... chr != '×' && chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_an_upper_case_letter_character_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 302: ... chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_an_upper_case_letter_character_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 302: chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__is_an_upper_case_letter_character_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 299: ->
  // 300:   ||
  // 301:     chr >= 'A' && chr <= 'Z'
  // 302:     chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__character__to_lower_case_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // chr: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 317: chr.is_an_upper_case_letter_character
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_an_upper_case_letter_character();
  func = myself->type;
  frame->cont = cont__types__character__to_lower_case_2;
}
static void cont__types__character__to_lower_case_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 317: ... :
  // 318:   return chr+0x20
  frame->slots[3] /* temp__2 */ = create_closure(entry__types__character__to_lower_case_3, 0);
  // 319: :
  // 320:   return chr
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__character__to_lower_case_5, 0);
  // 316: if
  // 317:   chr.is_an_upper_case_letter_character:
  // 318:     return chr+0x20
  // 319:   :
  // 320:     return chr
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__character__to_lower_case_6;
}
static void entry__types__character__to_lower_case_3(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 318: ... chr+0x20
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = number__0x20;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__character__to_lower_case_4;
}
static void cont__types__character__to_lower_case_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 318: return chr+0x20
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__character__to_lower_case_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 320: return chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__character__to_lower_case_6(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__character__to_upper_case_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // chr: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 335: chr.is_a_lower_case_letter_character
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_lower_case_letter_character();
  func = myself->type;
  frame->cont = cont__types__character__to_upper_case_2;
}
static void cont__types__character__to_upper_case_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 335: ... :
  // 336:   return chr-0x20
  frame->slots[3] /* temp__2 */ = create_closure(entry__types__character__to_upper_case_3, 0);
  // 337: :
  // 338:   return chr
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__character__to_upper_case_5, 0);
  // 334: if
  // 335:   chr.is_a_lower_case_letter_character:
  // 336:     return chr-0x20
  // 337:   :
  // 338:     return chr
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__character__to_upper_case_6;
}
static void entry__types__character__to_upper_case_3(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 336: ... chr-0x20
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = number__0x20;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__character__to_upper_case_4;
}
static void cont__types__character__to_upper_case_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 336: return chr-0x20
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__character__to_upper_case_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 338: return chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__character__to_upper_case_6(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__is_a_vowel_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 351: ... -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_a_vowel_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 351: ... -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_a_vowel_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 351: ... 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'
  argument_count = 10;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__101;
  arguments->slots[2] = character__105;
  arguments->slots[3] = character__111;
  arguments->slots[4] = character__117;
  arguments->slots[5] = character__65;
  arguments->slots[6] = character__69;
  arguments->slots[7] = character__73;
  arguments->slots[8] = character__79;
  arguments->slots[9] = character__85;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__std__is_a_vowel_2;
}
static void cont__std__is_a_vowel_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 351: case chr 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' (-> true) -> false
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  arguments->slots[2] = func__std__is_a_vowel_3;
  arguments->slots[3] = func__std__is_a_vowel_4;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__character__serialize_1(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // self: 0
  // indent: 1
  // buf: 2
  frame->slots[2] /* buf */ = create_cell();
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
  // 360: $$buf "'"
  ((CELL *)frame->slots[2])->contents /* buf */ = string__578a5af303e9cc6;
  // 363: self < ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__character__serialize_3;
}
static void cont__types__character__serialize_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__character__serialize_4, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__character__serialize_15;
}
static void entry__types__character__serialize_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: self > '~'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__126;
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__character__serialize_5;
}
static void cont__types__character__serialize_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__types__character__serialize_6, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__character__serialize_14;
}
static void entry__types__character__serialize_6(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 365: self == '@@'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = character__64;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__character__serialize_7;
}
static void cont__types__character__serialize_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__types__character__serialize_8, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__character__serialize_13;
}
static void entry__types__character__serialize_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 366: self == '@quot;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = character__34;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__character__serialize_9;
}
static void cont__types__character__serialize_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 367: self == '@apos;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__types__character__serialize_10, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__character__serialize_12;
}
static void entry__types__character__serialize_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 367: self == '@apos;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__character__serialize_11;
}
static void cont__types__character__serialize_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 367: self == '@apos;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__character__serialize_12(void) {
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
static void cont__types__character__serialize_13(void) {
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
static void cont__types__character__serialize_14(void) {
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
static void cont__types__character__serialize_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 368: :
  // 369:   append &buf string("@@0x" hex(self.to_integer) ';')
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__character__serialize_16, 0);
  // 370: :
  // 371:   push &buf self
  frame->slots[7] /* temp__5 */ = create_closure(entry__types__character__serialize_22, 0);
  // 361: if
  // 362:   ||
  // 363:     self < ' '
  // 364:     self > '~'
  // 365:     self == '@@'
  // 366:     self == '@quot;'
  // 367:     self == '@apos;'
  // 368:   :
  // 369:     append &buf string("@@0x" hex(self.to_integer) ';')
  // 370:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  arguments->slots[2] = frame->slots[7] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__character__serialize_24;
}
static void entry__types__character__serialize_16(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // buf: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 369: ... self.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__types__character__serialize_17;
}
static void cont__types__character__serialize_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 369: ... hex(self.to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__hex();
  func = myself->type;
  frame->cont = cont__types__character__serialize_18;
}
static void cont__types__character__serialize_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 369: ... string("@@0x" hex(self.to_integer) ';')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fa728415fa96bb4;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = character__59;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__types__character__serialize_20;
}
static void cont__types__character__serialize_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 369: append &buf string("@@0x" hex(self.to_integer) ';')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__character__serialize_21;
}
static void cont__types__character__serialize_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__character__serialize_22(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // buf: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 371: push &buf self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__character__serialize_23;
}
static void cont__types__character__serialize_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__character__serialize_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 372: ... push(buf '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__character__serialize_25;
}
static void cont__types__character__serialize_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 372: -> push(buf '@apos;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__character(void) {
  var.std__is_a_character = collect_node(var.std__is_a_character);
  var.types__character = collect_node(var.types__character);
  collect_static_attributes(&attributes__types__character);
  var.std__character = collect_node(var.std__character);
  var.std__is_a_whitespace_character = collect_node(var.std__is_a_whitespace_character);
  var.std__is_a_digit = collect_node(var.std__is_a_digit);
  var.std__is_a_letter = collect_node(var.std__is_a_letter);
  var.std__is_a_lower_case_letter = collect_node(var.std__is_a_lower_case_letter);
  var.std__is_an_upper_case_letter = collect_node(var.std__is_an_upper_case_letter);
  var.std__is_a_letter_character = collect_node(var.std__is_a_letter_character);
  var.std__is_a_lower_case_letter_character = collect_node(var.std__is_a_lower_case_letter_character);
  var.std__is_an_upper_case_letter_character = collect_node(var.std__is_an_upper_case_letter_character);
  var.std__is_a_vowel = collect_node(var.std__is_a_vowel);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__character(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_a_character", get__std__is_a_character, &poly_idx__std__is_a_character, &var.std__is_a_character);
  define_c_function("from_uchar32", runtime__from_uchar32);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__character(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__224 = from_uchar32(224);
  character__9 = from_uchar32(9);
  character__90 = from_uchar32(90);
  character__122 = from_uchar32(122);
  character__57 = from_uchar32(57);
  character__65 = from_uchar32(65);
  character__73 = from_uchar32(73);
  character__10 = from_uchar32(10);
  character__48 = from_uchar32(48);
  character__13 = from_uchar32(13);
  character__85 = from_uchar32(85);
  character__126 = from_uchar32(126);
  character__64 = from_uchar32(64);
  character__215 = from_uchar32(215);
  character__34 = from_uchar32(34);
  character__111 = from_uchar32(111);
  character__247 = from_uchar32(247);
  character__255 = from_uchar32(255);
  character__39 = from_uchar32(39);
  character__105 = from_uchar32(105);
  character__192 = from_uchar32(192);
  character__32 = from_uchar32(32);
  character__117 = from_uchar32(117);
  character__101 = from_uchar32(101);
  character__59 = from_uchar32(59);
  character__97 = from_uchar32(97);
  character__69 = from_uchar32(69);
  number__0x20 = from_uint32(32U);
  character__223 = from_uchar32(223);
  character__79 = from_uchar32(79);
  func__std__character_1 = create_function(entry__std__character_1, 1);
  func__types__character__plus_1 = create_function(entry__types__character__plus_1, 2);
  func__types__character__minus_1 = create_function(entry__types__character__minus_1, 2);
  func__types__character__equal_1 = create_function(entry__types__character__equal_1, 2);
  func__types__character__less_1 = create_function(entry__types__character__less_1, 2);
  func__types__character__hash_1 = create_function(entry__types__character__hash_1, 1);
  func__types__character__to_string_1 = create_function(entry__types__character__to_string_1, 1);
  func__types__character__to_integer_1 = create_function(entry__types__character__to_integer_1, 1);
  func__std__is_a_whitespace_character_1 = create_function(entry__std__is_a_whitespace_character_1, 1);
  func__std__is_a_digit_1 = create_function(entry__std__is_a_digit_1, 1);
  func__std__is_a_letter_1 = create_function(entry__std__is_a_letter_1, 1);
  func__std__is_a_lower_case_letter_1 = create_function(entry__std__is_a_lower_case_letter_1, 1);
  func__std__is_an_upper_case_letter_1 = create_function(entry__std__is_an_upper_case_letter_1, 1);
  func__std__is_a_letter_character_1 = create_function(entry__std__is_a_letter_character_1, 1);
  func__std__is_a_lower_case_letter_character_1 = create_function(entry__std__is_a_lower_case_letter_character_1, 1);
  func__std__is_an_upper_case_letter_character_1 = create_function(entry__std__is_an_upper_case_letter_character_1, 1);
  func__types__character__to_lower_case_1 = create_function(entry__types__character__to_lower_case_1, 1);
  func__types__character__to_upper_case_1 = create_function(entry__types__character__to_upper_case_1, 1);
  func__std__is_a_vowel_3 = create_function(entry__std__is_a_vowel_3, 0);
  func__std__is_a_vowel_4 = create_function(entry__std__is_a_vowel_4, 0);
  func__std__is_a_vowel_1 = create_function(entry__std__is_a_vowel_1, 1);
  string__578a5af303e9cc6 = from_latin_1_string("'", 1);
  string__fa728415fa96bb4 = from_latin_1_string("@0x", 3);
  func__types__character__serialize_1 = create_function(entry__types__character__serialize_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__character(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__character");
  set_used_namespaces(used_namespaces);
  var.types__character = create_future_with_prototype(create__types__character(0));
  define_single_assign_static("types", "character", get__types__character, &var.types__character);
  define_single_assign_static("std", "character", get__std__character, &var.std__character);
  define_single_assign_static("std", "is_a_whitespace_character", get__std__is_a_whitespace_character, &var.std__is_a_whitespace_character);
  define_single_assign_static("std", "is_a_digit", get__std__is_a_digit, &var.std__is_a_digit);
  define_single_assign_static("std", "is_a_letter", get__std__is_a_letter, &var.std__is_a_letter);
  define_single_assign_static("std", "is_a_lower_case_letter", get__std__is_a_lower_case_letter, &var.std__is_a_lower_case_letter);
  define_single_assign_static("std", "is_an_upper_case_letter", get__std__is_an_upper_case_letter, &var.std__is_an_upper_case_letter);
  define_single_assign_static("std", "is_a_letter_character", get__std__is_a_letter_character, &var.std__is_a_letter_character);
  define_single_assign_static("std", "is_a_lower_case_letter_character", get__std__is_a_lower_case_letter_character, &var.std__is_a_lower_case_letter_character);
  define_single_assign_static("std", "is_an_upper_case_letter_character", get__std__is_an_upper_case_letter_character, &var.std__is_an_upper_case_letter_character);
  define_single_assign_static("std", "is_a_vowel", get__std__is_a_vowel, &var.std__is_a_vowel);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__character(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__character");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "hash", &get__hash, &poly_idx__hash);
  use_read_only(NULL, "hex", &get__hex, &get_value_or_future__hex);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "is_a_character", &get__is_a_character, &poly_idx__is_a_character);
  use_read_only(NULL, "is_a_lower_case_letter_character", &get__is_a_lower_case_letter_character, &get_value_or_future__is_a_lower_case_letter_character);
  use_read_only(NULL, "is_an_upper_case_letter_character", &get__is_an_upper_case_letter_character, &get_value_or_future__is_an_upper_case_letter_character);
  use_polymorphic_function(NULL, "less", &get__less, &poly_idx__less);
  use_polymorphic_function(NULL, "minus", &get__minus, &poly_idx__minus);
  use_polymorphic_function(NULL, "plus", &get__plus, &poly_idx__plus);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "serialize", &get__serialize, &poly_idx__serialize);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_polymorphic_function(NULL, "to_integer", &get__to_integer, &poly_idx__to_integer);
  use_polymorphic_function(NULL, "to_lower_case", &get__to_lower_case, &poly_idx__to_lower_case);
  use_polymorphic_function(NULL, "to_string", &get__to_string, &poly_idx__to_string);
  use_polymorphic_function(NULL, "to_upper_case", &get__to_upper_case, &poly_idx__to_upper_case);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  define_attribute("types", "object", poly_idx__is_a_character, get__false());
  define_attribute("types", "character", poly_idx__is_a_character, get__true());
  define_method("types", "character", poly_idx__plus, func__types__character__plus_1);
  define_method("types", "character", poly_idx__minus, func__types__character__minus_1);
  define_method("types", "character", poly_idx__equal, func__types__character__equal_1);
  define_method("types", "character", poly_idx__less, func__types__character__less_1);
  define_method("types", "character", poly_idx__hash, func__types__character__hash_1);
  define_method("types", "character", poly_idx__to_string, func__types__character__to_string_1);
  define_method("types", "character", poly_idx__to_integer, func__types__character__to_integer_1);
  define_method("types", "character", poly_idx__to_lower_case, func__types__character__to_lower_case_1);
  define_method("types", "character", poly_idx__to_upper_case, func__types__character__to_upper_case_1);
  define_method("types", "character", poly_idx__serialize, func__types__character__serialize_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__character(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_character, create_function(type__std__is_a_character, -1));
  assign_value(&var.types__character, get__types__object());
  assign_variable(&var.std__character, &func__std__character_1);
  assign_variable(&var.std__is_a_whitespace_character, &func__std__is_a_whitespace_character_1);
  assign_variable(&var.std__is_a_digit, &func__std__is_a_digit_1);
  assign_variable(&var.std__is_a_letter, &func__std__is_a_letter_1);
  assign_variable(&var.std__is_a_lower_case_letter, &func__std__is_a_lower_case_letter_1);
  assign_variable(&var.std__is_an_upper_case_letter, &func__std__is_an_upper_case_letter_1);
  assign_variable(&var.std__is_a_letter_character, &func__std__is_a_letter_character_1);
  assign_variable(&var.std__is_a_lower_case_letter_character, &func__std__is_a_lower_case_letter_character_1);
  assign_variable(&var.std__is_an_upper_case_letter_character, &func__std__is_an_upper_case_letter_character_1);
  assign_variable(&var.std__is_a_vowel, &func__std__is_a_vowel_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__character(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__character);
}
