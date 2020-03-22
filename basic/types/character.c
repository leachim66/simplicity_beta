#include <limits.h>
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
IMPORT NODE *create_future(void);
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
static NODE_GETTER get__is_an_uppper_case_letter_character;
static NODE_GETTER get_value_or_future__is_an_uppper_case_letter_character;
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
  NODE *std__is_an_uppper_case_letter_character;
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
static void entry__8_1(void);
static NODE *func__8_1;
static NODE *get__std__character(void) {
  return var.std__character;
}
static void entry__9_1(void);
static NODE *func__9_1;
static void entry__10_1(void);
static NODE *func__10_1;
static void entry__11_1(void);
static NODE *func__11_1;
static void entry__12_1(void);
static NODE *func__12_1;
static void entry__13_1(void);
static NODE *func__13_1;
static void entry__14_1(void);
static NODE *func__14_1;
static void entry__15_1(void);
static NODE *func__15_1;

static long func__types__character___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__17_1;
static void entry__17_1(void);
static FRAME_INFO frame__17_1 = {1, {"chr"}};
static void cont__17_2(void);
static NODE *func__17_3;
static void entry__17_3(void);
static FRAME_INFO frame__17_3 = {1, {"chr"}};
static void cont__17_4(void);
static NODE *func__17_5;
static void entry__17_5(void);
static FRAME_INFO frame__17_5 = {1, {"chr"}};
static void cont__17_6(void);
static NODE *func__17_7;
static void entry__17_7(void);
static FRAME_INFO frame__17_7 = {1, {"chr"}};
static void cont__17_8(void);
static void cont__17_9(void);
static void cont__17_10(void);
static void cont__17_11(void);
static NODE *get__std__is_a_whitespace_character(void) {
  return var.std__is_a_whitespace_character;
}
static NODE *func__18_1;
static void entry__18_1(void);
static FRAME_INFO frame__18_1 = {1, {"chr"}};
static void cont__18_2(void);
static void cont__18_3(void);
static NODE *func__18_4;
static void entry__18_4(void);
static FRAME_INFO frame__18_4 = {1, {"chr"}};
static void cont__18_5(void);
static void cont__18_6(void);
static void cont__18_7(void);
static NODE *get__std__is_a_digit(void) {
  return var.std__is_a_digit;
}
static NODE *func__19_1;
static void entry__19_1(void);
static FRAME_INFO frame__19_1 = {1, {"chr"}};
static void cont__19_2(void);
static void cont__19_3(void);
static NODE *func__19_4;
static void entry__19_4(void);
static FRAME_INFO frame__19_4 = {1, {"chr"}};
static void cont__19_5(void);
static void cont__19_6(void);
static void cont__19_7(void);
static NODE *func__19_8;
static void entry__19_8(void);
static FRAME_INFO frame__19_8 = {1, {"chr"}};
static void cont__19_9(void);
static void cont__19_10(void);
static NODE *func__19_11;
static void entry__19_11(void);
static FRAME_INFO frame__19_11 = {1, {"chr"}};
static void cont__19_12(void);
static void cont__19_13(void);
static void cont__19_14(void);
static void cont__19_15(void);
static NODE *get__std__is_a_letter(void) {
  return var.std__is_a_letter;
}
static NODE *func__20_1;
static void entry__20_1(void);
static FRAME_INFO frame__20_1 = {1, {"chr"}};
static void cont__20_2(void);
static void cont__20_3(void);
static NODE *func__20_4;
static void entry__20_4(void);
static FRAME_INFO frame__20_4 = {1, {"chr"}};
static void cont__20_5(void);
static void cont__20_6(void);
static void cont__20_7(void);
static NODE *get__std__is_a_lower_case_letter(void) {
  return var.std__is_a_lower_case_letter;
}
static NODE *func__21_1;
static void entry__21_1(void);
static FRAME_INFO frame__21_1 = {1, {"chr"}};
static void cont__21_2(void);
static void cont__21_3(void);
static NODE *func__21_4;
static void entry__21_4(void);
static FRAME_INFO frame__21_4 = {1, {"chr"}};
static void cont__21_5(void);
static void cont__21_6(void);
static void cont__21_7(void);
static NODE *get__std__is_an_upper_case_letter(void) {
  return var.std__is_an_upper_case_letter;
}
static NODE *func__22_1;
static void entry__22_1(void);
static FRAME_INFO frame__22_1 = {1, {"chr"}};
static void cont__22_2(void);
static void cont__22_3(void);
static NODE *func__22_4;
static void entry__22_4(void);
static FRAME_INFO frame__22_4 = {1, {"chr"}};
static void cont__22_5(void);
static void cont__22_6(void);
static void cont__22_7(void);
static NODE *func__22_8;
static void entry__22_8(void);
static FRAME_INFO frame__22_8 = {1, {"chr"}};
static void cont__22_9(void);
static void cont__22_10(void);
static NODE *func__22_11;
static void entry__22_11(void);
static FRAME_INFO frame__22_11 = {1, {"chr"}};
static void cont__22_12(void);
static void cont__22_13(void);
static void cont__22_14(void);
static NODE *func__22_15;
static void entry__22_15(void);
static FRAME_INFO frame__22_15 = {1, {"chr"}};
static void cont__22_16(void);
static void cont__22_17(void);
static NODE *func__22_18;
static void entry__22_18(void);
static FRAME_INFO frame__22_18 = {1, {"chr"}};
static void cont__22_19(void);
static void cont__22_20(void);
static NODE *func__22_21;
static void entry__22_21(void);
static FRAME_INFO frame__22_21 = {1, {"chr"}};
static void cont__22_22(void);
static void cont__22_23(void);
static NODE *func__22_24;
static void entry__22_24(void);
static FRAME_INFO frame__22_24 = {1, {"chr"}};
static void cont__22_25(void);
static void cont__22_26(void);
static void cont__22_27(void);
static void cont__22_28(void);
static void cont__22_29(void);
static void cont__22_30(void);
static void cont__22_31(void);
static NODE *get__std__is_a_letter_character(void) {
  return var.std__is_a_letter_character;
}
static NODE *func__23_1;
static void entry__23_1(void);
static FRAME_INFO frame__23_1 = {1, {"chr"}};
static void cont__23_2(void);
static void cont__23_3(void);
static NODE *func__23_4;
static void entry__23_4(void);
static FRAME_INFO frame__23_4 = {1, {"chr"}};
static void cont__23_5(void);
static void cont__23_6(void);
static void cont__23_7(void);
static NODE *func__23_8;
static void entry__23_8(void);
static FRAME_INFO frame__23_8 = {1, {"chr"}};
static void cont__23_9(void);
static void cont__23_10(void);
static NODE *func__23_11;
static void entry__23_11(void);
static FRAME_INFO frame__23_11 = {1, {"chr"}};
static void cont__23_12(void);
static void cont__23_13(void);
static NODE *func__23_14;
static void entry__23_14(void);
static FRAME_INFO frame__23_14 = {1, {"chr"}};
static void cont__23_15(void);
static void cont__23_16(void);
static NODE *func__23_17;
static void entry__23_17(void);
static FRAME_INFO frame__23_17 = {1, {"chr"}};
static void cont__23_18(void);
static void cont__23_19(void);
static void cont__23_20(void);
static void cont__23_21(void);
static void cont__23_22(void);
static void cont__23_23(void);
static NODE *get__std__is_a_lower_case_letter_character(void) {
  return var.std__is_a_lower_case_letter_character;
}
static NODE *func__24_1;
static void entry__24_1(void);
static FRAME_INFO frame__24_1 = {1, {"chr"}};
static void cont__24_2(void);
static void cont__24_3(void);
static NODE *func__24_4;
static void entry__24_4(void);
static FRAME_INFO frame__24_4 = {1, {"chr"}};
static void cont__24_5(void);
static void cont__24_6(void);
static void cont__24_7(void);
static NODE *func__24_8;
static void entry__24_8(void);
static FRAME_INFO frame__24_8 = {1, {"chr"}};
static void cont__24_9(void);
static void cont__24_10(void);
static NODE *func__24_11;
static void entry__24_11(void);
static FRAME_INFO frame__24_11 = {1, {"chr"}};
static void cont__24_12(void);
static void cont__24_13(void);
static NODE *func__24_14;
static void entry__24_14(void);
static FRAME_INFO frame__24_14 = {1, {"chr"}};
static void cont__24_15(void);
static void cont__24_16(void);
static NODE *func__24_17;
static void entry__24_17(void);
static FRAME_INFO frame__24_17 = {1, {"chr"}};
static void cont__24_18(void);
static void cont__24_19(void);
static void cont__24_20(void);
static void cont__24_21(void);
static void cont__24_22(void);
static void cont__24_23(void);
static NODE *get__std__is_an_uppper_case_letter_character(void) {
  return var.std__is_an_uppper_case_letter_character;
}
static NODE *func__25_1;
static void entry__25_1(void);
static FRAME_INFO frame__25_1 = {2, {"chr", "return"}};
static void cont__25_2(void);
static NODE *func__25_3;
static void entry__25_3(void);
static FRAME_INFO frame__25_3 = {2, {"return", "chr"}};
static void cont__25_4(void);
static NODE *func__25_5;
static void entry__25_5(void);
static FRAME_INFO frame__25_5 = {2, {"return", "chr"}};
static void cont__25_6(void);
static NODE *func__26_1;
static void entry__26_1(void);
static FRAME_INFO frame__26_1 = {2, {"chr", "return"}};
static void cont__26_2(void);
static NODE *func__26_3;
static void entry__26_3(void);
static FRAME_INFO frame__26_3 = {2, {"return", "chr"}};
static void cont__26_4(void);
static NODE *func__26_5;
static void entry__26_5(void);
static FRAME_INFO frame__26_5 = {2, {"return", "chr"}};
static void cont__26_6(void);
static NODE *func__27_1;
static void entry__27_1(void);
static FRAME_INFO frame__27_1 = {1, {"chr"}};
static void cont__27_2(void);
static NODE *func__27_3;
static void entry__27_3(void);
static FRAME_INFO frame__27_3 = {0, {}};
static NODE *func__27_4;
static void entry__27_4(void);
static FRAME_INFO frame__27_4 = {0, {}};
static NODE *get__std__is_a_vowel(void) {
  return var.std__is_a_vowel;
}
static NODE *func__28_1;
static void entry__28_1(void);
static FRAME_INFO frame__28_1 = {3, {"self", "indent", "buf"}};
static NODE *string__28_2;
static void cont__28_3(void);
static NODE *func__28_4;
static void entry__28_4(void);
static FRAME_INFO frame__28_4 = {1, {"self"}};
static void cont__28_5(void);
static NODE *func__28_6;
static void entry__28_6(void);
static FRAME_INFO frame__28_6 = {1, {"self"}};
static void cont__28_7(void);
static NODE *func__28_8;
static void entry__28_8(void);
static FRAME_INFO frame__28_8 = {1, {"self"}};
static void cont__28_9(void);
static NODE *func__28_10;
static void entry__28_10(void);
static FRAME_INFO frame__28_10 = {1, {"self"}};
static void cont__28_11(void);
static void cont__28_12(void);
static void cont__28_13(void);
static void cont__28_14(void);
static void cont__28_15(void);
static NODE *func__28_16;
static void entry__28_16(void);
static FRAME_INFO frame__28_16 = {2, {"buf", "self"}};
static void cont__28_17(void);
static void cont__28_18(void);
static NODE *string__28_19;
static void cont__28_20(void);
static void cont__28_21(void);
static NODE *func__28_22;
static void entry__28_22(void);
static FRAME_INFO frame__28_22 = {2, {"buf", "self"}};
static void cont__28_23(void);
static void cont__28_24(void);
static void cont__28_25(void);
void run__basic__types__character(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_character, NULL, 25, 25, 2, 20},
  {run__basic__types__character, NULL, },
  {entry__8_1, NULL, 65, 70, 3, 2},
  {entry__9_1, NULL, 73, 78, 3, 2},
  {entry__10_1, NULL, 81, 92, 3, 2},
  {entry__11_1, NULL, 95, 101, 3, 2},
  {entry__12_1, NULL, 104, 110, 3, 2},
  {entry__13_1, NULL, 113, 119, 3, 2},
  {entry__14_1, NULL, 122, 131, 3, 2},
  {entry__15_1, NULL, 134, 137, 3, 2},
  {entry__17_7, NULL, 159, 159, 54, 66},
  {cont__17_8, &frame__17_7, 159, 159, 54, 66},
  {entry__17_5, NULL, 159, 159, 37, 49},
  {cont__17_6, &frame__17_5, 159, 159, 37, 66},
  {cont__17_9, &frame__17_5, 159, 159, 37, 66},
  {entry__17_3, NULL, 159, 159, 20, 32},
  {cont__17_4, &frame__17_3, 159, 159, 20, 66},
  {cont__17_10, &frame__17_3, 159, 159, 20, 66},
  {entry__17_1, NULL, 159, 159, 6, 15},
  {cont__17_2, &frame__17_1, 159, 159, 6, 66},
  {cont__17_11, &frame__17_1, 159, 159, 3, 66},
  {entry__18_4, NULL, 161, 161, 42, 51},
  {cont__18_5, &frame__18_4, 161, 161, 42, 51},
  {cont__18_6, &frame__18_4, 161, 161, 42, 51},
  {entry__18_1, NULL, 161, 161, 28, 37},
  {cont__18_2, &frame__18_1, 161, 161, 28, 37},
  {cont__18_3, &frame__18_1, 161, 161, 28, 51},
  {cont__18_7, &frame__18_1, 161, 161, 25, 51},
  {entry__19_4, NULL, 163, 163, 43, 52},
  {cont__19_5, &frame__19_4, 163, 163, 43, 52},
  {cont__19_6, &frame__19_4, 163, 163, 43, 52},
  {entry__19_11, NULL, 163, 163, 71, 80},
  {cont__19_12, &frame__19_11, 163, 163, 71, 80},
  {cont__19_13, &frame__19_11, 163, 163, 71, 80},
  {entry__19_8, NULL, 163, 163, 57, 66},
  {cont__19_9, &frame__19_8, 163, 163, 57, 66},
  {cont__19_10, &frame__19_8, 163, 163, 57, 80},
  {cont__19_14, &frame__19_8, 163, 163, 57, 80},
  {entry__19_1, NULL, 163, 163, 29, 38},
  {cont__19_2, &frame__19_1, 163, 163, 29, 38},
  {cont__19_3, &frame__19_1, 163, 163, 29, 52},
  {cont__19_7, &frame__19_1, 163, 163, 29, 80},
  {cont__19_15, &frame__19_1, 163, 163, 26, 80},
  {entry__20_4, NULL, 165, 165, 54, 63},
  {cont__20_5, &frame__20_4, 165, 165, 54, 63},
  {cont__20_6, &frame__20_4, 165, 165, 54, 63},
  {entry__20_1, NULL, 165, 165, 40, 49},
  {cont__20_2, &frame__20_1, 165, 165, 40, 49},
  {cont__20_3, &frame__20_1, 165, 165, 40, 63},
  {cont__20_7, &frame__20_1, 165, 165, 37, 63},
  {entry__21_4, NULL, 167, 167, 55, 64},
  {cont__21_5, &frame__21_4, 167, 167, 55, 64},
  {cont__21_6, &frame__21_4, 167, 167, 55, 64},
  {entry__21_1, NULL, 167, 167, 41, 50},
  {cont__21_2, &frame__21_1, 167, 167, 41, 50},
  {cont__21_3, &frame__21_1, 167, 167, 41, 64},
  {cont__21_7, &frame__21_1, 167, 167, 38, 64},
  {entry__22_4, NULL, 172, 172, 21, 30},
  {cont__22_5, &frame__22_4, 172, 172, 21, 30},
  {cont__22_6, &frame__22_4, 172, 172, 21, 30},
  {entry__22_11, NULL, 173, 173, 21, 30},
  {cont__22_12, &frame__22_11, 173, 173, 21, 30},
  {cont__22_13, &frame__22_11, 173, 173, 21, 30},
  {entry__22_24, NULL, 174, 174, 49, 58},
  {cont__22_25, &frame__22_24, 174, 174, 49, 58},
  {cont__22_26, &frame__22_24, 174, 174, 49, 58},
  {entry__22_21, NULL, 174, 174, 35, 44},
  {cont__22_22, &frame__22_21, 174, 174, 35, 44},
  {cont__22_23, &frame__22_21, 174, 174, 35, 58},
  {cont__22_27, &frame__22_21, 174, 174, 35, 58},
  {entry__22_18, NULL, 174, 174, 21, 30},
  {cont__22_19, &frame__22_18, 174, 174, 21, 30},
  {cont__22_20, &frame__22_18, 174, 174, 21, 58},
  {cont__22_28, &frame__22_18, 174, 174, 21, 58},
  {entry__22_15, NULL, 174, 174, 7, 16},
  {cont__22_16, &frame__22_15, 174, 174, 7, 16},
  {cont__22_17, &frame__22_15, 174, 174, 7, 58},
  {cont__22_29, &frame__22_15, 174, 174, 7, 58},
  {entry__22_8, NULL, 173, 173, 7, 16},
  {cont__22_9, &frame__22_8, 173, 173, 7, 16},
  {cont__22_10, &frame__22_8, 173, 173, 7, 30},
  {cont__22_14, &frame__22_8, 174, 174, 7, 58},
  {cont__22_30, &frame__22_8, },
  {entry__22_1, NULL, 172, 172, 7, 16},
  {cont__22_2, &frame__22_1, 172, 172, 7, 16},
  {cont__22_3, &frame__22_1, 172, 172, 7, 30},
  {cont__22_7, &frame__22_1, },
  {cont__22_31, &frame__22_1, 170, 174, 3, 59},
  {entry__23_4, NULL, 179, 179, 21, 30},
  {cont__23_5, &frame__23_4, 179, 179, 21, 30},
  {cont__23_6, &frame__23_4, 179, 179, 21, 30},
  {entry__23_17, NULL, 180, 180, 49, 58},
  {cont__23_18, &frame__23_17, 180, 180, 49, 58},
  {cont__23_19, &frame__23_17, 180, 180, 49, 58},
  {entry__23_14, NULL, 180, 180, 35, 44},
  {cont__23_15, &frame__23_14, 180, 180, 35, 44},
  {cont__23_16, &frame__23_14, 180, 180, 35, 58},
  {cont__23_20, &frame__23_14, 180, 180, 35, 58},
  {entry__23_11, NULL, 180, 180, 21, 30},
  {cont__23_12, &frame__23_11, 180, 180, 21, 30},
  {cont__23_13, &frame__23_11, 180, 180, 21, 58},
  {cont__23_21, &frame__23_11, 180, 180, 21, 58},
  {entry__23_8, NULL, 180, 180, 7, 16},
  {cont__23_9, &frame__23_8, 180, 180, 7, 16},
  {cont__23_10, &frame__23_8, 180, 180, 7, 58},
  {cont__23_22, &frame__23_8, 180, 180, 7, 58},
  {entry__23_1, NULL, 179, 179, 7, 16},
  {cont__23_2, &frame__23_1, 179, 179, 7, 16},
  {cont__23_3, &frame__23_1, 179, 179, 7, 30},
  {cont__23_7, &frame__23_1, 178, 180, 5, 57},
  {cont__23_23, &frame__23_1, 177, 180, 3, 59},
  {entry__24_4, NULL, 185, 185, 21, 30},
  {cont__24_5, &frame__24_4, 185, 185, 21, 30},
  {cont__24_6, &frame__24_4, 185, 185, 21, 30},
  {entry__24_17, NULL, 186, 186, 49, 58},
  {cont__24_18, &frame__24_17, 186, 186, 49, 58},
  {cont__24_19, &frame__24_17, 186, 186, 49, 58},
  {entry__24_14, NULL, 186, 186, 35, 44},
  {cont__24_15, &frame__24_14, 186, 186, 35, 44},
  {cont__24_16, &frame__24_14, 186, 186, 35, 58},
  {cont__24_20, &frame__24_14, 186, 186, 35, 58},
  {entry__24_11, NULL, 186, 186, 21, 30},
  {cont__24_12, &frame__24_11, 186, 186, 21, 30},
  {cont__24_13, &frame__24_11, 186, 186, 21, 58},
  {cont__24_21, &frame__24_11, 186, 186, 21, 58},
  {entry__24_8, NULL, 186, 186, 7, 16},
  {cont__24_9, &frame__24_8, 186, 186, 7, 16},
  {cont__24_10, &frame__24_8, 186, 186, 7, 58},
  {cont__24_22, &frame__24_8, 186, 186, 7, 58},
  {entry__24_1, NULL, 185, 185, 7, 16},
  {cont__24_2, &frame__24_1, 185, 185, 7, 16},
  {cont__24_3, &frame__24_1, 185, 185, 7, 30},
  {cont__24_7, &frame__24_1, 184, 186, 5, 57},
  {cont__24_23, &frame__24_1, 183, 186, 3, 59},
  {entry__25_3, NULL, 195, 195, 14, 21},
  {cont__25_4, &frame__25_3, 195, 195, 7, 21},
  {entry__25_5, NULL, 197, 197, 7, 16},
  {entry__25_1, NULL, 194, 194, 5, 42},
  {cont__25_2, &frame__25_1, 193, 197, 3, 17},
  {cont__25_6, &frame__25_1, 197, 197, 17, 17},
  {entry__26_3, NULL, 206, 206, 14, 21},
  {cont__26_4, &frame__26_3, 206, 206, 7, 21},
  {entry__26_5, NULL, 208, 208, 7, 16},
  {entry__26_1, NULL, 205, 205, 5, 40},
  {cont__26_2, &frame__26_1, 204, 208, 3, 17},
  {cont__26_6, &frame__26_1, 208, 208, 17, 17},
  {entry__27_3, NULL, 211, 211, 62, 68},
  {entry__27_4, NULL, 211, 211, 71, 78},
  {entry__27_1, NULL, 211, 211, 12, 59},
  {cont__27_2, &frame__27_1, 211, 211, 3, 78},
  {entry__28_10, NULL, 221, 221, 7, 22},
  {cont__28_11, &frame__28_10, 221, 221, 7, 22},
  {entry__28_8, NULL, 220, 220, 7, 22},
  {cont__28_9, &frame__28_8, 221, 221, 7, 22},
  {cont__28_12, &frame__28_8, },
  {entry__28_6, NULL, 219, 219, 7, 18},
  {cont__28_7, &frame__28_6, },
  {cont__28_13, &frame__28_6, },
  {entry__28_4, NULL, 218, 218, 7, 16},
  {cont__28_5, &frame__28_4, },
  {cont__28_14, &frame__28_4, },
  {entry__28_16, NULL, 223, 223, 37, 51},
  {cont__28_17, &frame__28_16, 223, 223, 33, 52},
  {cont__28_18, &frame__28_16, 223, 223, 19, 57},
  {cont__28_20, &frame__28_16, 223, 223, 7, 57},
  {cont__28_21, &frame__28_16, 223, 223, 57, 57},
  {entry__28_22, NULL, 225, 225, 7, 20},
  {cont__28_23, &frame__28_22, 225, 225, 20, 20},
  {entry__28_1, NULL, 217, 217, 7, 16},
  {cont__28_3, &frame__28_1, },
  {cont__28_15, &frame__28_1, 215, 225, 3, 21},
  {cont__28_24, &frame__28_1, 226, 226, 6, 23},
  {cont__28_25, &frame__28_1, 226, 226, 3, 23}
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
static void entry__8_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  uint64_t code = to_uint64(arguments->slots[0]);
  if (code >= 0x100000000LL) {
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
static void entry__9_1(void) {
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
static void entry__10_1(void) {
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
static void entry__11_1(void) {
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
static void entry__12_1(void) {
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
static void entry__13_1(void) {
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
static void entry__14_1(void) {
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
static void entry__15_1(void) {
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
static void entry__17_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 159: ... chr == ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__17_2;
}
static void cont__17_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 159: ... chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__17_3, 0);
  // 159: ... chr == ' ' || chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__17_11;
}
static void entry__17_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 159: ... chr == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__17_4;
}
static void cont__17_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 159: ... chr == '@cr;' || chr == '@ht;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__17_5, 0);
  // 159: ... chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__17_10;
}
static void entry__17_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 159: ... chr == '@cr;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__13;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__17_6;
}
static void cont__17_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 159: ... chr == '@ht;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__17_7, 0);
  // 159: ... chr == '@cr;' || chr == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__17_9;
}
static void entry__17_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 159: ... chr == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__17_8;
}
static void cont__17_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 159: ... chr == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 159: ... chr == '@cr;' || chr == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 159: ... chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 159: -> chr == ' ' || chr == '@nl;' || chr == '@cr;' || chr == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 161: ... chr >= '0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__18_2;
}
static void cont__18_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 161: ... chr >= '0'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__18_3;
}
static void cont__18_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 161: ... chr <= '9'
  frame->slots[4] /* temp__4 */ = create_closure(entry__18_4, 0);
  // 161: ... chr >= '0' && chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void entry__18_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 161: ... chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 161: ... chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__18_6;
}
static void cont__18_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 161: ... chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__18_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 161: ... -> chr >= '0' && chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 163: ... chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__19_2;
}
static void cont__19_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 163: ... chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_3;
}
static void cont__19_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 163: ... chr <= 'z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__19_4, 0);
  // 163: ... chr >= 'a' && chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__19_7;
}
static void entry__19_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: ... chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__19_5;
}
static void cont__19_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 163: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_6;
}
static void cont__19_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 163: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 163: ... chr >= 'A' && chr <= 'Z'
  frame->slots[6] /* temp__6 */ = create_closure(entry__19_8, 0);
  // 163: ... chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__19_15;
}
static void entry__19_8(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: ... chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__19_9;
}
static void cont__19_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 163: ... chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_10;
}
static void cont__19_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 163: ... chr <= 'Z'
  frame->slots[4] /* temp__4 */ = create_closure(entry__19_11, 0);
  // 163: ... chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__19_14;
}
static void entry__19_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: ... chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__19_12;
}
static void cont__19_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 163: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__19_13;
}
static void cont__19_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 163: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 163: ... chr >= 'A' && chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 163: ... -> chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 165: ... chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 165: ... chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__20_3;
}
static void cont__20_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 165: ... chr <= 'z'
  frame->slots[4] /* temp__4 */ = create_closure(entry__20_4, 0);
  // 165: ... chr >= 'a' && chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__20_7;
}
static void entry__20_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 165: ... chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__20_5;
}
static void cont__20_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 165: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__20_6;
}
static void cont__20_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 165: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__20_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 165: ... -> chr >= 'a' && chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 167: ... chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__21_2;
}
static void cont__21_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 167: ... chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__21_3;
}
static void cont__21_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 167: ... chr <= 'Z'
  frame->slots[4] /* temp__4 */ = create_closure(entry__21_4, 0);
  // 167: ... chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__21_7;
}
static void entry__21_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 167: ... chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__21_5;
}
static void cont__21_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 167: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__21_6;
}
static void cont__21_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 167: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 167: ... -> chr >= 'A' && chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 172: chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__22_2;
}
static void cont__22_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 172: chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_3;
}
static void cont__22_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 172: ... chr <= 'z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__22_4, 0);
  // 172: chr >= 'a' && chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__22_7;
}
static void entry__22_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: ... chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__22_5;
}
static void cont__22_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 172: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_6;
}
static void cont__22_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 172: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__6 */ = create_closure(entry__22_8, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__22_31;
}
static void entry__22_8(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__22_9;
}
static void cont__22_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 173: chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_10;
}
static void cont__22_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 173: ... chr <= 'Z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__22_11, 0);
  // 173: chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__22_14;
}
static void entry__22_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: ... chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__22_12;
}
static void cont__22_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 173: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_13;
}
static void cont__22_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 173: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: chr >= 'À' && chr <= 'ÿ' && chr != '×' && chr != '÷'
  frame->slots[6] /* temp__6 */ = create_closure(entry__22_15, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__22_30;
}
static void entry__22_15(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: chr >= 'À'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__192;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__22_16;
}
static void cont__22_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 174: chr >= 'À'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_17;
}
static void cont__22_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... chr <= 'ÿ' && chr != '×' && chr != '÷'
  frame->slots[4] /* temp__4 */ = create_closure(entry__22_18, 0);
  // 174: chr >= 'À' && chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__22_29;
}
static void entry__22_18(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... chr <= 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__255;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__22_19;
}
static void cont__22_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 174: ... chr <= 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_20;
}
static void cont__22_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... chr != '×' && chr != '÷'
  frame->slots[4] /* temp__4 */ = create_closure(entry__22_21, 0);
  // 174: ... chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__22_28;
}
static void entry__22_21(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... chr != '×'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__215;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__22_22;
}
static void cont__22_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 174: ... chr != '×'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_23;
}
static void cont__22_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... chr != '÷'
  frame->slots[4] /* temp__4 */ = create_closure(entry__22_24, 0);
  // 174: ... chr != '×' && chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__22_27;
}
static void entry__22_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__247;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__22_25;
}
static void cont__22_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_26;
}
static void cont__22_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: ... chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: ... chr != '×' && chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: ... chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: chr >= 'À' && chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_30(void) {
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
static void cont__22_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 170: ->
  // 171:   ||
  // 172:     chr >= 'a' && chr <= 'z'
  // 173:     chr >= 'A' && chr <= 'Z'
  // 174:     chr >= 'À' && chr <= 'ÿ' && chr != '×' && chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 179: chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 179: chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
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
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 179: ... chr <= 'z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__23_4, 0);
  // 179: chr >= 'a' && chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__23_7;
}
static void entry__23_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... chr <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__23_5;
}
static void cont__23_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 179: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__23_6;
}
static void cont__23_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 179: ... chr <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  frame->slots[6] /* temp__6 */ = create_closure(entry__23_8, 0);
  // 178: ||
  // 179:   chr >= 'a' && chr <= 'z'
  // 180:   chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__23_23;
}
static void entry__23_8(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: chr >= 'à'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__224;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__23_9;
}
static void cont__23_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 180: chr >= 'à'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__23_10;
}
static void cont__23_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: ... chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  frame->slots[4] /* temp__4 */ = create_closure(entry__23_11, 0);
  // 180: chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__23_22;
}
static void entry__23_11(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... chr <= 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__255;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__23_12;
}
static void cont__23_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 180: ... chr <= 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__23_13;
}
static void cont__23_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: ... chr != '÷' && chr != 'ÿ'
  frame->slots[4] /* temp__4 */ = create_closure(entry__23_14, 0);
  // 180: ... chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__23_21;
}
static void entry__23_14(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... chr != '÷'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__247;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_15;
}
static void cont__23_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 180: ... chr != '÷'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__23_16;
}
static void cont__23_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: ... chr != 'ÿ'
  frame->slots[4] /* temp__4 */ = create_closure(entry__23_17, 0);
  // 180: ... chr != '÷' && chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__23_20;
}
static void entry__23_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... chr != 'ÿ'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__255;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_18;
}
static void cont__23_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: ... chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__23_19;
}
static void cont__23_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: ... chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: ... chr != '÷' && chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: ... chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 177: ->
  // 178:   ||
  // 179:     chr >= 'a' && chr <= 'z'
  // 180:     chr >= 'à' && chr <= 'ÿ' && chr != '÷' && chr != 'ÿ'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 185: chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
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
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 185: chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
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
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 185: ... chr <= 'Z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__24_4, 0);
  // 185: chr >= 'A' && chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__24_7;
}
static void entry__24_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... chr <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void cont__24_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 185: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__24_6;
}
static void cont__24_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 185: ... chr <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 186: chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  frame->slots[6] /* temp__6 */ = create_closure(entry__24_8, 0);
  // 184: ||
  // 185:   chr >= 'A' && chr <= 'Z'
  // 186:   chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__24_23;
}
static void entry__24_8(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: chr >= 'À'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__192;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__24_9;
}
static void cont__24_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 186: chr >= 'À'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__24_10;
}
static void cont__24_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 186: ... chr <= 'ß' && chr != '×' && chr != 'ß'
  frame->slots[4] /* temp__4 */ = create_closure(entry__24_11, 0);
  // 186: chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__24_22;
}
static void entry__24_11(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: ... chr <= 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__223;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__24_12;
}
static void cont__24_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 186: ... chr <= 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__24_13;
}
static void cont__24_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 186: ... chr != '×' && chr != 'ß'
  frame->slots[4] /* temp__4 */ = create_closure(entry__24_14, 0);
  // 186: ... chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__24_21;
}
static void entry__24_14(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: ... chr != '×'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__215;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__24_15;
}
static void cont__24_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 186: ... chr != '×'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__24_16;
}
static void cont__24_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 186: ... chr != 'ß'
  frame->slots[4] /* temp__4 */ = create_closure(entry__24_17, 0);
  // 186: ... chr != '×' && chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__24_20;
}
static void entry__24_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: ... chr != 'ß'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__223;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__24_18;
}
static void cont__24_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 186: ... chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__24_19;
}
static void cont__24_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 186: ... chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 186: ... chr != '×' && chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 186: ... chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 186: chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 183: ->
  // 184:   ||
  // 185:     chr >= 'A' && chr <= 'Z'
  // 186:     chr >= 'À' && chr <= 'ß' && chr != '×' && chr != 'ß'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // chr: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 194: chr.is_an_uppper_case_letter_character
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_an_uppper_case_letter_character();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 194: ... :
  // 195:   return chr+0x20
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_3, 0);
  // 196: :
  // 197:   return chr
  frame->slots[4] /* temp__3 */ = create_closure(entry__25_5, 0);
  // 193: if
  // 194:   chr.is_an_uppper_case_letter_character:
  // 195:     return chr+0x20
  // 196:   :
  // 197:     return chr
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_6;
}
static void entry__25_3(void) {
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
  // 195: ... chr+0x20
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = number__0x20;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__25_4;
}
static void cont__25_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 195: return chr+0x20
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_5(void) {
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
  // 197: return chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_6(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__26_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // chr: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 205: chr.is_a_lower_case_letter_character
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_lower_case_letter_character();
  func = myself->type;
  frame->cont = cont__26_2;
}
static void cont__26_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 205: ... :
  // 206:   return chr-0x20
  frame->slots[3] /* temp__2 */ = create_closure(entry__26_3, 0);
  // 207: :
  // 208:   return chr
  frame->slots[4] /* temp__3 */ = create_closure(entry__26_5, 0);
  // 204: if
  // 205:   chr.is_a_lower_case_letter_character:
  // 206:     return chr-0x20
  // 207:   :
  // 208:     return chr
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__26_6;
}
static void entry__26_3(void) {
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
  // 206: ... chr-0x20
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = number__0x20;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__26_4;
}
static void cont__26_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 206: return chr-0x20
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_5(void) {
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
  // 208: return chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_6(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__27_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 211: ... -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 211: ... -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 211: ... 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'
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
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 211: case chr 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' (-> true) -> false
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  arguments->slots[2] = func__27_3;
  arguments->slots[3] = func__27_4;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_1(void) {
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
  // 214: $$buf "'"
  ((CELL *)frame->slots[2])->contents /* buf */ = string__28_2;
  // 217: self < ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_3;
}
static void cont__28_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__28_4, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__28_15;
}
static void entry__28_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 218: self > '~'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__126;
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_5;
}
static void cont__28_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__28_6, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__28_14;
}
static void entry__28_6(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 219: self == '@@'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = character__64;
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
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__28_8, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__28_13;
}
static void entry__28_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: self == '@quot;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = character__34;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_9;
}
static void cont__28_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 221: self == '@apos;'
  frame->slots[3] /* temp__3 */ = create_closure(entry__28_10, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__28_12;
}
static void entry__28_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 221: self == '@apos;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_11;
}
static void cont__28_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 221: self == '@apos;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__28_12(void) {
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
static void cont__28_13(void) {
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
static void cont__28_14(void) {
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
static void cont__28_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 222: :
  // 223:   append &buf string("@@0x" hex(self.to_integer) ';')
  frame->slots[6] /* temp__4 */ = create_closure(entry__28_16, 0);
  // 224: :
  // 225:   push &buf self
  frame->slots[7] /* temp__5 */ = create_closure(entry__28_22, 0);
  // 215: if
  // 216:   ||
  // 217:     self < ' '
  // 218:     self > '~'
  // 219:     self == '@@'
  // 220:     self == '@quot;'
  // 221:     self == '@apos;'
  // 222:   :
  // 223:     append &buf string("@@0x" hex(self.to_integer) ';')
  // 224:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  arguments->slots[2] = frame->slots[7] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__28_24;
}
static void entry__28_16(void) {
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
  // 223: ... self.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__28_17;
}
static void cont__28_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 223: ... hex(self.to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__hex();
  func = myself->type;
  frame->cont = cont__28_18;
}
static void cont__28_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 223: ... string("@@0x" hex(self.to_integer) ';')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__28_19;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = character__59;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__28_20;
}
static void cont__28_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 223: append &buf string("@@0x" hex(self.to_integer) ';')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__28_21;
}
static void cont__28_21(void) {
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
static void entry__28_22(void) {
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
  // 225: push &buf self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__28_23;
}
static void cont__28_23(void) {
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
static void cont__28_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 226: ... push(buf '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__28_25;
}
static void cont__28_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 226: -> push(buf '@apos;')
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
  func__17_1 = collect_node(func__17_1);
  var.std__is_a_digit = collect_node(var.std__is_a_digit);
  func__18_1 = collect_node(func__18_1);
  var.std__is_a_letter = collect_node(var.std__is_a_letter);
  func__19_1 = collect_node(func__19_1);
  var.std__is_a_lower_case_letter = collect_node(var.std__is_a_lower_case_letter);
  func__20_1 = collect_node(func__20_1);
  var.std__is_an_upper_case_letter = collect_node(var.std__is_an_upper_case_letter);
  func__21_1 = collect_node(func__21_1);
  var.std__is_a_letter_character = collect_node(var.std__is_a_letter_character);
  func__22_1 = collect_node(func__22_1);
  var.std__is_a_lower_case_letter_character = collect_node(var.std__is_a_lower_case_letter_character);
  func__23_1 = collect_node(func__23_1);
  var.std__is_an_uppper_case_letter_character = collect_node(var.std__is_an_uppper_case_letter_character);
  func__24_1 = collect_node(func__24_1);
  func__25_1 = collect_node(func__25_1);
  func__26_1 = collect_node(func__26_1);
  var.std__is_a_vowel = collect_node(var.std__is_a_vowel);
  func__27_3 = collect_node(func__27_3);
  func__27_4 = collect_node(func__27_4);
  func__27_1 = collect_node(func__27_1);
  string__28_2 = collect_node(string__28_2);
  string__28_19 = collect_node(string__28_19);
  func__28_1 = collect_node(func__28_1);
  character__224 = collect_node(character__224);
  character__9 = collect_node(character__9);
  character__90 = collect_node(character__90);
  character__122 = collect_node(character__122);
  character__57 = collect_node(character__57);
  character__65 = collect_node(character__65);
  character__73 = collect_node(character__73);
  character__10 = collect_node(character__10);
  character__48 = collect_node(character__48);
  character__13 = collect_node(character__13);
  character__85 = collect_node(character__85);
  character__126 = collect_node(character__126);
  character__64 = collect_node(character__64);
  character__215 = collect_node(character__215);
  character__34 = collect_node(character__34);
  character__111 = collect_node(character__111);
  character__247 = collect_node(character__247);
  character__255 = collect_node(character__255);
  character__39 = collect_node(character__39);
  character__105 = collect_node(character__105);
  character__192 = collect_node(character__192);
  character__32 = collect_node(character__32);
  character__117 = collect_node(character__117);
  character__101 = collect_node(character__101);
  character__59 = collect_node(character__59);
  character__97 = collect_node(character__97);
  character__69 = collect_node(character__69);
  number__0x20 = collect_node(number__0x20);
  character__223 = collect_node(character__223);
  character__79 = collect_node(character__79);
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
  func__17_1 = create_function(entry__17_1, 1);
  func__18_1 = create_function(entry__18_1, 1);
  func__19_1 = create_function(entry__19_1, 1);
  func__20_1 = create_function(entry__20_1, 1);
  func__21_1 = create_function(entry__21_1, 1);
  func__22_1 = create_function(entry__22_1, 1);
  func__23_1 = create_function(entry__23_1, 1);
  func__24_1 = create_function(entry__24_1, 1);
  func__25_1 = create_function(entry__25_1, 1);
  func__26_1 = create_function(entry__26_1, 1);
  func__27_3 = create_function(entry__27_3, 0);
  func__27_4 = create_function(entry__27_4, 0);
  func__27_1 = create_function(entry__27_1, 1);
  string__28_2 = from_latin_1_string("'", 1);
  string__28_19 = from_latin_1_string("@0x", 3);
  func__28_1 = create_function(entry__28_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__character(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__character");
  set_used_namespaces(used_namespaces);
  var.types__character = create_future_with_prototype(create__types__character(0));
  define_single_assign_static("types", "character", get__types__character, &var.types__character);
  func__8_1 = create_future();
  define_single_assign_static("std", "character", get__std__character, &var.std__character);
  func__9_1 = create_future();
  func__10_1 = create_future();
  func__11_1 = create_future();
  func__12_1 = create_future();
  func__13_1 = create_future();
  func__14_1 = create_future();
  func__15_1 = create_future();
  define_single_assign_static("std", "is_a_whitespace_character", get__std__is_a_whitespace_character, &var.std__is_a_whitespace_character);
  define_single_assign_static("std", "is_a_digit", get__std__is_a_digit, &var.std__is_a_digit);
  define_single_assign_static("std", "is_a_letter", get__std__is_a_letter, &var.std__is_a_letter);
  define_single_assign_static("std", "is_a_lower_case_letter", get__std__is_a_lower_case_letter, &var.std__is_a_lower_case_letter);
  define_single_assign_static("std", "is_an_upper_case_letter", get__std__is_an_upper_case_letter, &var.std__is_an_upper_case_letter);
  define_single_assign_static("std", "is_a_letter_character", get__std__is_a_letter_character, &var.std__is_a_letter_character);
  define_single_assign_static("std", "is_a_lower_case_letter_character", get__std__is_a_lower_case_letter_character, &var.std__is_a_lower_case_letter_character);
  define_single_assign_static("std", "is_an_uppper_case_letter_character", get__std__is_an_uppper_case_letter_character, &var.std__is_an_uppper_case_letter_character);
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
  use_read_only(NULL, "is_an_uppper_case_letter_character", &get__is_an_uppper_case_letter_character, &get_value_or_future__is_an_uppper_case_letter_character);
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
  define_method("types", "character", poly_idx__plus, func__9_1);
  define_method("types", "character", poly_idx__minus, func__10_1);
  define_method("types", "character", poly_idx__equal, func__11_1);
  define_method("types", "character", poly_idx__less, func__12_1);
  define_method("types", "character", poly_idx__hash, func__13_1);
  define_method("types", "character", poly_idx__to_string, func__14_1);
  define_method("types", "character", poly_idx__to_integer, func__15_1);
  define_method("types", "character", poly_idx__to_lower_case, func__25_1);
  define_method("types", "character", poly_idx__to_upper_case, func__26_1);
  define_method("types", "character", poly_idx__serialize, func__28_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__character(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_character, create_function(type__std__is_a_character, -1));
  assign_value(&var.types__character, get__types__object());
  assign_variable(&var.std__character, &func__8_1);
  assign_variable(&var.std__is_a_whitespace_character, &func__17_1);
  assign_variable(&var.std__is_a_digit, &func__18_1);
  assign_variable(&var.std__is_a_letter, &func__19_1);
  assign_variable(&var.std__is_a_lower_case_letter, &func__20_1);
  assign_variable(&var.std__is_an_upper_case_letter, &func__21_1);
  assign_variable(&var.std__is_a_letter_character, &func__22_1);
  assign_variable(&var.std__is_a_lower_case_letter_character, &func__23_1);
  assign_variable(&var.std__is_an_uppper_case_letter_character, &func__24_1);
  assign_variable(&var.std__is_a_vowel, &func__27_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__character(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  assign_value(&func__8_1, create_function(entry__8_1, 1));
  assign_value(&func__9_1, create_function(entry__9_1, 2));
  assign_value(&func__10_1, create_function(entry__10_1, 2));
  assign_value(&func__11_1, create_function(entry__11_1, 2));
  assign_value(&func__12_1, create_function(entry__12_1, 2));
  assign_value(&func__13_1, create_function(entry__13_1, 1));
  assign_value(&func__14_1, create_function(entry__14_1, 1));
  assign_value(&func__15_1, create_function(entry__15_1, 1));
  register_collector(collect__basic__types__character);
}
