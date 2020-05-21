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
IMPORT NODE *get_dynamic_slot(int id);
IMPORT void define_dynamic_slot(int id, NODE *node);
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
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *undefined;
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_future(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *empty_string;
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_namespace(const char *namespace);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void register_polymorphic_function(const char *name, int *id_p);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
typedef void (*NODE_SETTER)(NODE *);
IMPORT void define_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER definer,
  int *id_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
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
static NODE_GETTER get__ANY_CHARACTER;
static NODE_GETTER get_value_or_future__ANY_CHARACTER;
static NODE_GETTER get__FOREIGN;
static NODE_GETTER get_value_or_future__FOREIGN;
static NODE_GETTER get__H1;
static NODE_GETTER get_value_or_future__H1;
static NODE_GETTER get__HEAD;
static NODE_GETTER get_value_or_future__HEAD;
static NODE_GETTER get__HTML;
static NODE_GETTER get_value_or_future__HTML;
static NODE_GETTER get__HTML_HEADER;
static NODE_GETTER get_value_or_future__HTML_HEADER;
static NODE_GETTER get__HTTP_HEADER;
static NODE_GETTER get_value_or_future__HTTP_HEADER;
static NODE_GETTER get__MULTI_LINE;
static NODE_GETTER get_value_or_future__MULTI_LINE;
static NODE_GETTER get__MULTI_PARAGRAPH;
static NODE_GETTER get_value_or_future__MULTI_PARAGRAPH;
static NODE_GETTER get__P;
static NODE_GETTER get_value_or_future__P;
static NODE_GETTER get__PRE;
static NODE_GETTER get_value_or_future__PRE;
static NODE_GETTER get__SIMPLE;
static NODE_GETTER get_value_or_future__SIMPLE;
static NODE_GETTER get__SINGLE_LINE;
static NODE_GETTER get_value_or_future__SINGLE_LINE;
static NODE_GETTER get__TITLE;
static NODE_GETTER get_value_or_future__TITLE;
static NODE_GETTER get__VOID;
static NODE_GETTER get_value_or_future__VOID;
static NODE_GETTER get__alt;
static NODE_GETTER get_value_or_future__alt;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__between;
static NODE_GETTER get_value_or_future__between;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__character;
static NODE_GETTER get_value_or_future__character;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__define_tag;
static NODE_GETTER get_value_or_future__define_tag;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__emit;
static NODE_GETTER get_value_or_future__emit;
static NODE_GETTER get__encode;
static NODE_GETTER get_value_or_future__encode;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_a_function;
static NODE_GETTER get_value_or_future__is_a_function;
static NODE_GETTER get__is_a_key_value_pair;
static NODE_GETTER get_value_or_future__is_a_key_value_pair;
static NODE_GETTER get__is_a_string;
static NODE_GETTER get_value_or_future__is_a_string;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__key_of;
static NODE_GETTER get_value_or_future__key_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__many;
static NODE_GETTER get_value_or_future__many;
static NODE_GETTER get__not_followed_by;
static NODE_GETTER get_value_or_future__not_followed_by;
static NODE_GETTER get__raise;
static NODE_GETTER get_value_or_future__raise;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static NODE_GETTER get__sequence;
static NODE_GETTER get_value_or_future__sequence;
static NODE_GETTER get__split;
static NODE_GETTER get_value_or_future__split;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__sequence;
static NODE_GETTER get_value_or_future__std__sequence;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__std__times;
static NODE_GETTER get_value_or_future__std__times;
static NODE_GETTER get__std__value_range;
static NODE_GETTER get_value_or_future__std__value_range;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static NODE_GETTER get__types__string;
static NODE_GETTER get_value_or_future__types__string;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__value_of;
static NODE_GETTER get_value_or_future__value_of;
static NODE_GETTER get__write;
static NODE_GETTER get_value_or_future__write;
static NODE_GETTER get__writeln;
static NODE_GETTER get_value_or_future__writeln;
static struct {
  NODE *_convert_from_percent_encoding;
  NODE *_hex_digit_value;
  NODE *_hex_digit;
  NODE *html__SIMPLE;
  NODE *html__SINGLE_LINE;
  NODE *html__MULTI_LINE;
  NODE *html__MULTI_PARAGRAPH;
  NODE *html__NORMAL;
  NODE *html__VOID;
  NODE *html__FOREIGN;
  NODE *html__TEXT;
  NODE *html__define_tag;
  NODE *html__HTML;
  NODE *html__HEAD;
  NODE *html__META;
  NODE *html__TITLE;
  NODE *html__STYLE;
  NODE *html__SCRIPT;
  NODE *html__BODY;
  NODE *html__A;
  NODE *html__H1;
  NODE *html__H2;
  NODE *html__H3;
  NODE *html__H4;
  NODE *html__H5;
  NODE *html__H6;
  NODE *html__DIV;
  NODE *html__P;
  NODE *html__SPAN;
  NODE *html__HR;
  NODE *html__BR;
  NODE *html__NOBR;
  NODE *html__OL;
  NODE *html__UL;
  NODE *html__LI;
  NODE *html__TABLE;
  NODE *html__TR;
  NODE *html__TH;
  NODE *html__TD;
  NODE *html__DL;
  NODE *html__DT;
  NODE *html__DD;
  NODE *html__FORM;
  NODE *html__FIELDSET;
  NODE *html__LEGEND;
  NODE *html__INPUT;
  NODE *html__TEXTAREA;
  NODE *html__SELECT;
  NODE *html__OPTION;
  NODE *html__BUTTON;
  NODE *html__CODE;
  NODE *html__PRE;
  NODE *html__B;
  NODE *html__EM;
  NODE *html__CENTER;
  NODE *html__LINK;
  NODE *html__IMG;
  NODE *html__FIGURE;
  NODE *html__FIGCAPTION;
  NODE *html__VIDEO;
  NODE *html__SOURCE;
  NODE *html__CANVAS;
  NODE *html__HTTP_HEADER;
  NODE *html__HTML_HEADER;
  NODE *html__ERROR_PAGE;
  NODE *html__DUMP_PAGE;
} var;
static const char *var_names[] = {
  "convert_from_percent_encoding",
  "hex_digit_value",
  "hex_digit"
};
static int poly_idx__convert_from_percent_encoding;
static void type__convert_from_percent_encoding(void);
static NODE *unique__html__SIMPLE;
static NODE *get__html__SIMPLE(void) {
  return var.html__SIMPLE;
}
static NODE *unique__html__SINGLE_LINE;
static NODE *get__html__SINGLE_LINE(void) {
  return var.html__SINGLE_LINE;
}
static NODE *unique__html__MULTI_LINE;
static NODE *get__html__MULTI_LINE(void) {
  return var.html__MULTI_LINE;
}
static NODE *unique__html__MULTI_PARAGRAPH;
static NODE *get__html__MULTI_PARAGRAPH(void) {
  return var.html__MULTI_PARAGRAPH;
}
static NODE *unique__html__NORMAL;
static NODE *get__html__NORMAL(void) {
  return var.html__NORMAL;
}
static NODE *unique__html__VOID;
static NODE *get__html__VOID(void) {
  return var.html__VOID;
}
static NODE *unique__html__FOREIGN;
static NODE *get__html__FOREIGN(void) {
  return var.html__FOREIGN;
}
static int dyna_idx__html__emit;
static NODE *get__html__emit(void) {
  return get_dynamic_slot(dyna_idx__html__emit);
}
static void define__html__emit(NODE *node) {
  define_dynamic_slot(dyna_idx__html__emit, node);
}
static NODE *func__html__emit_1;
static void entry__html__emit_1(void);
static FRAME_INFO frame__html__emit_1 = {1, {"args"}};
static NODE *func__html__emit_2;
static void entry__html__emit_2(void);
static FRAME_INFO frame__html__emit_2 = {1, {"arg"}};
static int dyna_idx__html__encode;
static NODE *get__html__encode(void) {
  return get_dynamic_slot(dyna_idx__html__encode);
}
static void define__html__encode(NODE *node) {
  define_dynamic_slot(dyna_idx__html__encode, node);
}
static NODE *func__html__encode_1;
static void entry__html__encode_1(void);
static FRAME_INFO frame__html__encode_1 = {3, {"txt", "tag", "arg_str"}};
static NODE *func__html__TEXT_1;
static void entry__html__TEXT_1(void);
static FRAME_INFO frame__html__TEXT_1 = {1, {"args"}};
static void cont__html__TEXT_2(void);
static NODE *get__html__TEXT(void) {
  return var.html__TEXT;
}
static NODE *func__hex_digit_value_1;
static void entry__hex_digit_value_1(void);
static FRAME_INFO frame__hex_digit_value_1 = {2, {"chr", "return"}};
static NODE *func__hex_digit_value_2;
static void entry__hex_digit_value_2(void);
static FRAME_INFO frame__hex_digit_value_2 = {2, {"chr", "return"}};
static void cont__hex_digit_value_3(void);
static void cont__hex_digit_value_4(void);
static NODE *func__hex_digit_value_5;
static void entry__hex_digit_value_5(void);
static FRAME_INFO frame__hex_digit_value_5 = {1, {"chr"}};
static void cont__hex_digit_value_6(void);
static void cont__hex_digit_value_7(void);
static void cont__hex_digit_value_8(void);
static NODE *func__hex_digit_value_9;
static void entry__hex_digit_value_9(void);
static FRAME_INFO frame__hex_digit_value_9 = {2, {"return", "chr"}};
static void cont__hex_digit_value_10(void);
static NODE *func__hex_digit_value_11;
static void entry__hex_digit_value_11(void);
static FRAME_INFO frame__hex_digit_value_11 = {2, {"chr", "return"}};
static void cont__hex_digit_value_12(void);
static void cont__hex_digit_value_13(void);
static NODE *func__hex_digit_value_14;
static void entry__hex_digit_value_14(void);
static FRAME_INFO frame__hex_digit_value_14 = {1, {"chr"}};
static void cont__hex_digit_value_15(void);
static void cont__hex_digit_value_16(void);
static void cont__hex_digit_value_17(void);
static NODE *func__hex_digit_value_18;
static void entry__hex_digit_value_18(void);
static FRAME_INFO frame__hex_digit_value_18 = {2, {"return", "chr"}};
static void cont__hex_digit_value_19(void);
static void cont__hex_digit_value_20(void);
static NODE *func__hex_digit_value_21;
static void entry__hex_digit_value_21(void);
static FRAME_INFO frame__hex_digit_value_21 = {2, {"chr", "return"}};
static void cont__hex_digit_value_22(void);
static void cont__hex_digit_value_23(void);
static NODE *func__hex_digit_value_24;
static void entry__hex_digit_value_24(void);
static FRAME_INFO frame__hex_digit_value_24 = {1, {"chr"}};
static void cont__hex_digit_value_25(void);
static void cont__hex_digit_value_26(void);
static void cont__hex_digit_value_27(void);
static NODE *func__hex_digit_value_28;
static void entry__hex_digit_value_28(void);
static FRAME_INFO frame__hex_digit_value_28 = {2, {"return", "chr"}};
static void cont__hex_digit_value_29(void);
static void cont__hex_digit_value_30(void);
static NODE *func__hex_digit_value_31;
static void entry__hex_digit_value_31(void);
static FRAME_INFO frame__hex_digit_value_31 = {0, {}};
static NODE *string__7fe91a650e32a4f3;
static void cont__hex_digit_value_33(void);
static NODE *func__types__string__convert_from_percent_encoding_1;
static void entry__types__string__convert_from_percent_encoding_1(void);
static FRAME_INFO frame__types__string__convert_from_percent_encoding_1 = {1, {"self"}};
static NODE *string__578a5af303e9cca;
static NODE *string__578a5af303e9cc1;
static void cont__types__string__convert_from_percent_encoding_4(void);
static void cont__types__string__convert_from_percent_encoding_5(void);
static NODE *string__578a5af303e9cc4;
static void cont__types__string__convert_from_percent_encoding_7(void);
static NODE *func__types__string__convert_from_percent_encoding_8;
static void entry__types__string__convert_from_percent_encoding_8(void);
static FRAME_INFO frame__types__string__convert_from_percent_encoding_8 = {1, {"capture"}};
static void cont__types__string__convert_from_percent_encoding_9(void);
static void cont__types__string__convert_from_percent_encoding_10(void);
static void cont__types__string__convert_from_percent_encoding_11(void);
static void cont__types__string__convert_from_percent_encoding_12(void);
static void cont__types__string__convert_from_percent_encoding_13(void);
static void cont__types__string__convert_from_percent_encoding_14(void);
static void cont__types__string__convert_from_percent_encoding_15(void);
static void cont__types__string__convert_from_percent_encoding_16(void);
static void cont__types__string__convert_from_percent_encoding_17(void);
static NODE *func__html__define_tag_1;
static void entry__html__define_tag_1(void);
static FRAME_INFO frame__html__define_tag_1 = {3, {"name", "mode", "tag_mode"}};
static NODE *func__html__define_tag_2;
static void entry__html__define_tag_2(void);
static FRAME_INFO frame__html__define_tag_2 = {9, {"args", "name", "mode", "tag_mode", "i", "n", "arg_str", "contents", "emit_tag"}};
static NODE *func__html__define_tag_3;
static void entry__html__define_tag_3(void);
static FRAME_INFO frame__html__define_tag_3 = {5, {"cts", "name", "arg_str", "mode", "tag_mode"}};
static NODE *string__578a5af303e9cdd;
static void cont__html__define_tag_5(void);
static void cont__html__define_tag_6(void);
static NODE *func__html__define_tag_7;
static void entry__html__define_tag_7(void);
static FRAME_INFO frame__html__define_tag_7 = {4, {"mode", "cts", "name", "arg_str"}};
static NODE *string__578a5af303e9cdf;
static void cont__html__define_tag_9(void);
static void cont__html__define_tag_10(void);
static NODE *func__html__define_tag_11;
static void entry__html__define_tag_11(void);
static FRAME_INFO frame__html__define_tag_11 = {0, {}};
static void cont__html__define_tag_12(void);
static void cont__html__define_tag_13(void);
static NODE *func__html__define_tag_14;
static void entry__html__define_tag_14(void);
static FRAME_INFO frame__html__define_tag_14 = {1, {"cts"}};
static NODE *func__html__define_tag_15;
static void entry__html__define_tag_15(void);
static FRAME_INFO frame__html__define_tag_15 = {3, {"cts", "name", "arg_str"}};
static void cont__html__define_tag_16(void);
static void cont__html__define_tag_17(void);
static NODE *string__2d7981f4e6e82bea;
static NODE *func__html__define_tag_19;
static void entry__html__define_tag_19(void);
static FRAME_INFO frame__html__define_tag_19 = {2, {"tag_mode", "name"}};
static NODE *func__html__define_tag_20;
static void entry__html__define_tag_20(void);
static FRAME_INFO frame__html__define_tag_20 = {1, {"name"}};
static NODE *string__fa737c15fc96be3;
static NODE *func__html__define_tag_22;
static void entry__html__define_tag_22(void);
static FRAME_INFO frame__html__define_tag_22 = {0, {}};
static NODE *func__html__define_tag_23;
static void entry__html__define_tag_23(void);
static FRAME_INFO frame__html__define_tag_23 = {0, {}};
static NODE *string__2d7981f4e6702bfb;
static void cont__html__define_tag_25(void);
static void cont__html__define_tag_26(void);
static NODE *func__html__define_tag_27;
static void entry__html__define_tag_27(void);
static FRAME_INFO frame__html__define_tag_27 = {0, {}};
static void cont__html__define_tag_28(void);
static NODE *func__html__define_tag_29;
static void entry__html__define_tag_29(void);
static FRAME_INFO frame__html__define_tag_29 = {5, {"break", "n", "i", "args", "arg_str"}};
static NODE *func__html__define_tag_30;
static void entry__html__define_tag_30(void);
static FRAME_INFO frame__html__define_tag_30 = {6, {"n", "i", "break", "args", "arg_str", "arg"}};
static void cont__html__define_tag_31(void);
static void cont__html__define_tag_32(void);
static void cont__html__define_tag_33(void);
static void cont__html__define_tag_34(void);
static void cont__html__define_tag_35(void);
static void cont__html__define_tag_36(void);
static void cont__html__define_tag_37(void);
static NODE *string__578a5af303e9ccc;
static void cont__html__define_tag_39(void);
static void cont__html__define_tag_40(void);
static void cont__html__define_tag_41(void);
static void cont__html__define_tag_42(void);
static NODE *string__721f55a3811b42ec;
static void cont__html__define_tag_44(void);
static void cont__html__define_tag_45(void);
static NODE *string__2d7981f4e6e02be7;
static void cont__html__define_tag_47(void);
static void cont__html__define_tag_48(void);
static void cont__html__define_tag_49(void);
static void cont__html__define_tag_50(void);
static void cont__html__define_tag_51(void);
static NODE *func__html__define_tag_52;
static void entry__html__define_tag_52(void);
static FRAME_INFO frame__html__define_tag_52 = {4, {"i", "n", "contents", "args"}};
static void cont__html__define_tag_53(void);
static NODE *func__html__define_tag_54;
static void entry__html__define_tag_54(void);
static FRAME_INFO frame__html__define_tag_54 = {4, {"contents", "args", "i", "n"}};
static void cont__html__define_tag_55(void);
static void cont__html__define_tag_56(void);
static NODE *func__html__define_tag_57;
static void entry__html__define_tag_57(void);
static FRAME_INFO frame__html__define_tag_57 = {4, {"i", "n", "contents", "args"}};
static void cont__html__define_tag_58(void);
static NODE *func__html__define_tag_59;
static void entry__html__define_tag_59(void);
static FRAME_INFO frame__html__define_tag_59 = {3, {"contents", "args", "i"}};
static void cont__html__define_tag_60(void);
static void cont__html__define_tag_61(void);
static void cont__html__define_tag_62(void);
static NODE *func__html__define_tag_63;
static void entry__html__define_tag_63(void);
static FRAME_INFO frame__html__define_tag_63 = {2, {"contents", "name"}};
static void cont__html__define_tag_64(void);
static NODE *func__html__define_tag_65;
static void entry__html__define_tag_65(void);
static FRAME_INFO frame__html__define_tag_65 = {1, {"name"}};
static NODE *string__7c1f5409013a62a3;
static void cont__html__define_tag_67(void);
static void cont__html__define_tag_68(void);
static void cont__html__define_tag_69(void);
static void cont__html__define_tag_70(void);
static NODE *func__html__define_tag_71;
static void entry__html__define_tag_71(void);
static FRAME_INFO frame__html__define_tag_71 = {2, {"contents", "emit_tag"}};
static NODE *string__2d7981f4e7582bcf;
static void cont__html__define_tag_73(void);
static NODE *func__html__define_tag_74;
static void entry__html__define_tag_74(void);
static FRAME_INFO frame__html__define_tag_74 = {3, {"field", "emit_tag", "convert"}};
static NODE *func__html__define_tag_75;
static void entry__html__define_tag_75(void);
static FRAME_INFO frame__html__define_tag_75 = {1, {"line"}};
static NODE *string__fa737415dc96bf2;
static NODE *string__ba0ae9cb5df07d07;
static void cont__html__define_tag_78(void);
static NODE *string__8e0aea4b5dc07d02;
static void cont__html__define_tag_80(void);
static NODE *string__2d7981f4e5e82bef;
static NODE *string__578a5af303e9ccb;
static void cont__html__define_tag_83(void);
static NODE *string__2d7981f4e5e82bf9;
static void cont__html__define_tag_85(void);
static NODE *string__2d7981f4e5e82b9e;
static NODE *string__578a5af303e9cba;
static void cont__html__define_tag_88(void);
static void cont__html__define_tag_89(void);
static void cont__html__define_tag_90(void);
static void cont__html__define_tag_91(void);
static void cont__html__define_tag_92(void);
static NODE *func__html__define_tag_93;
static void entry__html__define_tag_93(void);
static FRAME_INFO frame__html__define_tag_93 = {1, {"text"}};
static void cont__html__define_tag_94(void);
static void cont__html__define_tag_95(void);
static NODE *string__fa737415d616bf2;
static NODE *string__ba0afa8b5d287d07;
static void cont__html__define_tag_98(void);
static void cont__html__define_tag_99(void);
static NODE *string__2d7981f4e6582bef;
static void cont__html__define_tag_101(void);
static void cont__html__define_tag_102(void);
static void cont__html__define_tag_103(void);
static void cont__html__define_tag_104(void);
static NODE *func__html__define_tag_105;
static void entry__html__define_tag_105(void);
static FRAME_INFO frame__html__define_tag_105 = {1, {"text"}};
static void cont__html__define_tag_106(void);
static void cont__html__define_tag_107(void);
static NODE *string__fa737415d396bf2;
static NODE *string__ba0afa8b5d707d07;
static void cont__html__define_tag_110(void);
static void cont__html__define_tag_111(void);
static void cont__html__define_tag_112(void);
static void cont__html__define_tag_113(void);
static void cont__html__define_tag_114(void);
static void cont__html__define_tag_115(void);
static void cont__html__define_tag_116(void);
static void cont__html__define_tag_117(void);
static void cont__html__define_tag_118(void);
static NODE *func__html__define_tag_119;
static void entry__html__define_tag_119(void);
static FRAME_INFO frame__html__define_tag_119 = {3, {"reference", "link", "text"}};
static void cont__html__define_tag_120(void);
static void cont__html__define_tag_121(void);
static NODE *string__65b02728dcea54a7;
static NODE *string__2d7981f4e6182bfb;
static NODE *string__ba0afa8b5d687d07;
static void cont__html__define_tag_125(void);
static void cont__html__define_tag_126(void);
static void cont__html__define_tag_127(void);
static NODE *string__2d7981f4e6582be5;
static void cont__html__define_tag_129(void);
static NODE *func__html__define_tag_130;
static void entry__html__define_tag_130(void);
static FRAME_INFO frame__html__define_tag_130 = {2, {"field", "convert"}};
static void cont__html__define_tag_131(void);
static void cont__html__define_tag_132(void);
static void cont__html__define_tag_133(void);
static NODE *string__d6c0aed004987b9e;
static NODE *string__d45aee43eaadd069;
static void cont__html__define_tag_136(void);
static NODE *func__html__define_tag_137;
static void entry__html__define_tag_137(void);
static FRAME_INFO frame__html__define_tag_137 = {2, {"convert", "field"}};
static void cont__html__define_tag_138(void);
static void cont__html__define_tag_139(void);
static NODE *func__html__define_tag_140;
static void entry__html__define_tag_140(void);
static FRAME_INFO frame__html__define_tag_140 = {2, {"emit_tag", "contents"}};
static NODE *get__html__define_tag(void) {
  return var.html__define_tag;
}
static NODE *get__html__HTML(void) {
  return var.html__HTML;
}
static NODE *get__html__HEAD(void) {
  return var.html__HEAD;
}
static NODE *get__html__META(void) {
  return var.html__META;
}
static NODE *get__html__TITLE(void) {
  return var.html__TITLE;
}
static NODE *get__html__STYLE(void) {
  return var.html__STYLE;
}
static NODE *get__html__SCRIPT(void) {
  return var.html__SCRIPT;
}
static NODE *get__html__BODY(void) {
  return var.html__BODY;
}
static NODE *get__html__A(void) {
  return var.html__A;
}
static NODE *get__html__H1(void) {
  return var.html__H1;
}
static NODE *get__html__H2(void) {
  return var.html__H2;
}
static NODE *get__html__H3(void) {
  return var.html__H3;
}
static NODE *get__html__H4(void) {
  return var.html__H4;
}
static NODE *get__html__H5(void) {
  return var.html__H5;
}
static NODE *get__html__H6(void) {
  return var.html__H6;
}
static NODE *get__html__DIV(void) {
  return var.html__DIV;
}
static NODE *get__html__P(void) {
  return var.html__P;
}
static NODE *get__html__SPAN(void) {
  return var.html__SPAN;
}
static NODE *get__html__HR(void) {
  return var.html__HR;
}
static NODE *get__html__BR(void) {
  return var.html__BR;
}
static NODE *get__html__NOBR(void) {
  return var.html__NOBR;
}
static NODE *get__html__OL(void) {
  return var.html__OL;
}
static NODE *get__html__UL(void) {
  return var.html__UL;
}
static NODE *get__html__LI(void) {
  return var.html__LI;
}
static NODE *get__html__TABLE(void) {
  return var.html__TABLE;
}
static NODE *get__html__TR(void) {
  return var.html__TR;
}
static NODE *get__html__TH(void) {
  return var.html__TH;
}
static NODE *get__html__TD(void) {
  return var.html__TD;
}
static NODE *get__html__DL(void) {
  return var.html__DL;
}
static NODE *get__html__DT(void) {
  return var.html__DT;
}
static NODE *get__html__DD(void) {
  return var.html__DD;
}
static NODE *get__html__FORM(void) {
  return var.html__FORM;
}
static NODE *get__html__FIELDSET(void) {
  return var.html__FIELDSET;
}
static NODE *get__html__LEGEND(void) {
  return var.html__LEGEND;
}
static NODE *get__html__INPUT(void) {
  return var.html__INPUT;
}
static NODE *get__html__TEXTAREA(void) {
  return var.html__TEXTAREA;
}
static NODE *get__html__SELECT(void) {
  return var.html__SELECT;
}
static NODE *get__html__OPTION(void) {
  return var.html__OPTION;
}
static NODE *get__html__BUTTON(void) {
  return var.html__BUTTON;
}
static NODE *get__html__CODE(void) {
  return var.html__CODE;
}
static NODE *get__html__PRE(void) {
  return var.html__PRE;
}
static NODE *get__html__B(void) {
  return var.html__B;
}
static NODE *get__html__EM(void) {
  return var.html__EM;
}
static NODE *get__html__CENTER(void) {
  return var.html__CENTER;
}
static NODE *get__html__LINK(void) {
  return var.html__LINK;
}
static NODE *get__html__IMG(void) {
  return var.html__IMG;
}
static NODE *get__html__FIGURE(void) {
  return var.html__FIGURE;
}
static NODE *get__html__FIGCAPTION(void) {
  return var.html__FIGCAPTION;
}
static NODE *get__html__VIDEO(void) {
  return var.html__VIDEO;
}
static NODE *get__html__SOURCE(void) {
  return var.html__SOURCE;
}
static NODE *get__html__CANVAS(void) {
  return var.html__CANVAS;
}
static NODE *func__html__HTTP_HEADER_1;
static void entry__html__HTTP_HEADER_1(void);
static FRAME_INFO frame__html__HTTP_HEADER_1 = {0, {}};
static NODE *string__c0902590ad1223f4;
static NODE *get__html__HTTP_HEADER(void) {
  return var.html__HTTP_HEADER;
}
static NODE *func__html__HTML_HEADER_1;
static void entry__html__HTML_HEADER_1(void);
static FRAME_INFO frame__html__HTML_HEADER_1 = {0, {}};
static NODE *string__db8101d080cbfa33;
static NODE *get__html__HTML_HEADER(void) {
  return var.html__HTML_HEADER;
}
static NODE *func__html__ERROR_PAGE_1;
static void entry__html__ERROR_PAGE_1(void);
static FRAME_INFO frame__html__ERROR_PAGE_1 = {2, {"msg", "details"}};
static void cont__html__ERROR_PAGE_2(void);
static void cont__html__ERROR_PAGE_3(void);
static NODE *func__html__ERROR_PAGE_4;
static void entry__html__ERROR_PAGE_4(void);
static FRAME_INFO frame__html__ERROR_PAGE_4 = {2, {"msg", "details"}};
static NODE *func__html__ERROR_PAGE_5;
static void entry__html__ERROR_PAGE_5(void);
static FRAME_INFO frame__html__ERROR_PAGE_5 = {1, {"msg"}};
static void cont__html__ERROR_PAGE_6(void);
static NODE *func__html__ERROR_PAGE_7;
static void entry__html__ERROR_PAGE_7(void);
static FRAME_INFO frame__html__ERROR_PAGE_7 = {2, {"msg", "details"}};
static void cont__html__ERROR_PAGE_8(void);
static void cont__html__ERROR_PAGE_9(void);
static NODE *func__html__ERROR_PAGE_10;
static void entry__html__ERROR_PAGE_10(void);
static FRAME_INFO frame__html__ERROR_PAGE_10 = {1, {"details"}};
static NODE *get__html__ERROR_PAGE(void) {
  return var.html__ERROR_PAGE;
}
static NODE *func__html__DUMP_PAGE_1;
static void entry__html__DUMP_PAGE_1(void);
static FRAME_INFO frame__html__DUMP_PAGE_1 = {1, {"msg"}};
static void cont__html__DUMP_PAGE_2(void);
static void cont__html__DUMP_PAGE_3(void);
static NODE *func__html__DUMP_PAGE_4;
static void entry__html__DUMP_PAGE_4(void);
static FRAME_INFO frame__html__DUMP_PAGE_4 = {1, {"msg"}};
static NODE *func__html__DUMP_PAGE_5;
static void entry__html__DUMP_PAGE_5(void);
static FRAME_INFO frame__html__DUMP_PAGE_5 = {0, {}};
static NODE *string__a0aec0b5d087d49;
static void cont__html__DUMP_PAGE_7(void);
static NODE *func__html__DUMP_PAGE_8;
static void entry__html__DUMP_PAGE_8(void);
static FRAME_INFO frame__html__DUMP_PAGE_8 = {1, {"msg"}};
static void cont__html__DUMP_PAGE_9(void);
static NODE *get__html__DUMP_PAGE(void) {
  return var.html__DUMP_PAGE;
}
static void cont__82_1(void);
static void cont__82_2(void);
static void cont__82_3(void);
static void cont__82_4(void);
static NODE *string__120aec4b5d087d55;
static void cont__85_2(void);
static NODE *string__120ae80b5d687d5d;
static void cont__86_2(void);
static NODE *string__180ae80b5dc07d58;
static void cont__87_2(void);
static NODE *string__585aee03eaa95032;
static void cont__88_2(void);
static NODE *string__625aed43eaa92032;
static void cont__89_2(void);
static void cont__90_1(void);
static NODE *string__60aea8b5d407d40;
static void cont__91_2(void);
static NODE *string__578a5af303e9c80;
static void cont__92_2(void);
static NODE *string__2d7981f4e4482bf4;
static void cont__93_2(void);
static NODE *string__2d7981f4e4482bf7;
static void cont__94_2(void);
static NODE *string__2d7981f4e4482bf6;
static void cont__95_2(void);
static NODE *string__2d7981f4e4482bf1;
static void cont__96_2(void);
static NODE *string__2d7981f4e4482bf0;
static void cont__97_2(void);
static NODE *string__2d7981f4e4482bf3;
static void cont__98_2(void);
static NODE *string__fa721415d616bba;
static void cont__99_2(void);
static NODE *string__578a5af303e9c91;
static void cont__100_2(void);
static NODE *string__240aed4b5d687d57;
static void cont__101_2(void);
static NODE *string__2d7981f4e4482bb7;
static void cont__102_2(void);
static NODE *string__2d7981f4e4182bb7;
static void cont__103_2(void);
static NODE *string__1e0aea8b5d707d4b;
static void cont__104_2(void);
static NODE *string__2d7981f4e4702ba9;
static void cont__105_2(void);
static NODE *string__2d7981f4e4a02ba9;
static void cont__106_2(void);
static NODE *string__2d7981f4e4682bac;
static void cont__107_2(void);
static NODE *string__485aeb83eaa95032;
static void cont__108_2(void);
static NODE *string__2d7981f4e4a82bb7;
static void cont__109_2(void);
static NODE *string__2d7981f4e4a82bad;
static void cont__110_2(void);
static NODE *string__2d7981f4e4a82ba1;
static void cont__111_2(void);
static NODE *string__2d7981f4e4282ba9;
static void cont__112_2(void);
static NODE *string__2d7981f4e4282bb1;
static void cont__113_2(void);
static NODE *string__2d7981f4e4282ba1;
static void cont__114_2(void);
static NODE *string__e0aea8b5df07d54;
static void cont__115_2(void);
static NODE *string__66b0a91484fd5094;
static void cont__116_2(void);
static NODE *string__561f570681ca02b3;
static void cont__117_2(void);
static NODE *string__565aef03ea608023;
static void cont__118_2(void);
static NODE *string__6c80a95a04fcd2c1;
static void cont__119_2(void);
static NODE *string__401f570901a202a3;
static void cont__120_2(void);
static NODE *string__701f540701c352b9;
static void cont__121_2(void);
static NODE *string__701f534181c302b9;
static void cont__122_2(void);
static NODE *string__40aea8b5d407d5c;
static void cont__123_2(void);
static NODE *string__fa724415db96ba9;
static void cont__124_2(void);
static NODE *string__578a5af303e9c83;
static void cont__125_2(void);
static NODE *string__2d7981f4e4202ba8;
static void cont__126_2(void);
static NODE *string__441f5341019202a5;
static void cont__127_2(void);
static NODE *string__1a0aeb0b5d107d52;
static void cont__128_2(void);
static NODE *string__fa722015d416bab;
static void cont__129_2(void);
static NODE *string__561f5303812ac2b2;
static void cont__130_2(void);
static NODE *string__1d68225b2f52750f;
static void cont__131_2(void);
static NODE *string__585aea03eae17038;
static void cont__132_2(void);
static NODE *string__721f52c901a2a2b2;
static void cont__133_2(void);
static NODE *string__441f53c101b242a4;
static void cont__134_2(void);
void run__system__export__html(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__convert_from_percent_encoding, NULL, 30, 30, 2, 30},
  {run__system__export__html, NULL, 60, 60, 16, 25},
  {cont__82_1, NULL, 60, 60, 27, 36},
  {cont__82_2, NULL, 60, 60, 38, 47},
  {cont__82_3, NULL, 60, 60, 1, 48},
  {cont__82_4, NULL, 186, 186, 1, 40},
  {cont__85_2, NULL, 187, 187, 1, 40},
  {cont__86_2, NULL, 188, 188, 1, 41},
  {cont__87_2, NULL, 189, 189, 1, 43},
  {cont__88_2, NULL, 190, 190, 1, 42},
  {cont__89_2, NULL, 191, 191, 1, 44},
  {cont__90_1, NULL, 192, 192, 1, 40},
  {cont__91_2, NULL, 193, 193, 1, 30},
  {cont__92_2, NULL, 194, 194, 1, 37},
  {cont__93_2, NULL, 195, 195, 1, 37},
  {cont__94_2, NULL, 196, 196, 1, 37},
  {cont__95_2, NULL, 197, 197, 1, 37},
  {cont__96_2, NULL, 198, 198, 1, 37},
  {cont__97_2, NULL, 199, 199, 1, 37},
  {cont__98_2, NULL, 200, 200, 1, 43},
  {cont__99_2, NULL, 201, 201, 1, 39},
  {cont__100_2, NULL, 202, 202, 1, 36},
  {cont__101_2, NULL, 203, 203, 1, 37},
  {cont__102_2, NULL, 204, 204, 1, 42},
  {cont__103_2, NULL, 205, 205, 1, 45},
  {cont__104_2, NULL, 206, 206, 1, 36},
  {cont__105_2, NULL, 207, 207, 1, 36},
  {cont__106_2, NULL, 208, 208, 1, 37},
  {cont__107_2, NULL, 209, 209, 1, 42},
  {cont__108_2, NULL, 210, 210, 1, 36},
  {cont__109_2, NULL, 211, 211, 1, 36},
  {cont__110_2, NULL, 212, 212, 1, 37},
  {cont__111_2, NULL, 213, 213, 1, 36},
  {cont__112_2, NULL, 214, 214, 1, 37},
  {cont__113_2, NULL, 215, 215, 1, 36},
  {cont__114_2, NULL, 216, 216, 1, 40},
  {cont__115_2, NULL, 217, 217, 1, 48},
  {cont__116_2, NULL, 218, 218, 1, 45},
  {cont__117_2, NULL, 219, 219, 1, 43},
  {cont__118_2, NULL, 220, 220, 1, 49},
  {cont__119_2, NULL, 221, 221, 1, 49},
  {cont__120_2, NULL, 222, 222, 1, 44},
  {cont__121_2, NULL, 223, 223, 1, 45},
  {cont__122_2, NULL, 224, 224, 1, 41},
  {cont__123_2, NULL, 225, 225, 1, 38},
  {cont__124_2, NULL, 226, 226, 1, 30},
  {cont__125_2, NULL, 227, 227, 1, 32},
  {cont__126_2, NULL, 228, 228, 1, 40},
  {cont__127_2, NULL, 229, 229, 1, 41},
  {cont__128_2, NULL, 230, 230, 1, 39},
  {cont__129_2, NULL, 231, 231, 1, 49},
  {cont__130_2, NULL, 232, 232, 1, 57},
  {cont__131_2, NULL, 233, 233, 1, 47},
  {cont__132_2, NULL, 234, 234, 1, 45},
  {cont__133_2, NULL, 235, 235, 1, 49},
  {cont__134_2, NULL, },
  {entry__html__emit_2, NULL, 42, 42, 43, 51},
  {entry__html__emit_1, NULL, 42, 42, 22, 51},
  {entry__html__encode_1, NULL, 44, 44, 36, 43},
  {entry__html__TEXT_1, NULL, 46, 46, 35, 47},
  {cont__html__TEXT_2, &frame__html__TEXT_1, 46, 46, 22, 67},
  {entry__hex_digit_value_5, NULL, 54, 54, 22, 31},
  {cont__hex_digit_value_6, &frame__hex_digit_value_5, 54, 54, 22, 31},
  {cont__hex_digit_value_7, &frame__hex_digit_value_5, 54, 54, 22, 31},
  {entry__hex_digit_value_9, NULL, 54, 54, 41, 47},
  {cont__hex_digit_value_10, &frame__hex_digit_value_9, 54, 54, 34, 47},
  {entry__hex_digit_value_2, NULL, 54, 54, 8, 17},
  {cont__hex_digit_value_3, &frame__hex_digit_value_2, 54, 54, 8, 17},
  {cont__hex_digit_value_4, &frame__hex_digit_value_2, 54, 54, 8, 31},
  {cont__hex_digit_value_8, &frame__hex_digit_value_2, 54, 54, 5, 47},
  {entry__hex_digit_value_14, NULL, 55, 55, 22, 31},
  {cont__hex_digit_value_15, &frame__hex_digit_value_14, 55, 55, 22, 31},
  {cont__hex_digit_value_16, &frame__hex_digit_value_14, 55, 55, 22, 31},
  {entry__hex_digit_value_18, NULL, 55, 55, 41, 47},
  {cont__hex_digit_value_19, &frame__hex_digit_value_18, 55, 55, 41, 50},
  {cont__hex_digit_value_20, &frame__hex_digit_value_18, 55, 55, 34, 50},
  {entry__hex_digit_value_11, NULL, 55, 55, 8, 17},
  {cont__hex_digit_value_12, &frame__hex_digit_value_11, 55, 55, 8, 17},
  {cont__hex_digit_value_13, &frame__hex_digit_value_11, 55, 55, 8, 31},
  {cont__hex_digit_value_17, &frame__hex_digit_value_11, 55, 55, 5, 50},
  {entry__hex_digit_value_24, NULL, 56, 56, 22, 31},
  {cont__hex_digit_value_25, &frame__hex_digit_value_24, 56, 56, 22, 31},
  {cont__hex_digit_value_26, &frame__hex_digit_value_24, 56, 56, 22, 31},
  {entry__hex_digit_value_28, NULL, 56, 56, 41, 47},
  {cont__hex_digit_value_29, &frame__hex_digit_value_28, 56, 56, 41, 50},
  {cont__hex_digit_value_30, &frame__hex_digit_value_28, 56, 56, 34, 50},
  {entry__hex_digit_value_21, NULL, 56, 56, 8, 17},
  {cont__hex_digit_value_22, &frame__hex_digit_value_21, 56, 56, 8, 17},
  {cont__hex_digit_value_23, &frame__hex_digit_value_21, 56, 56, 8, 31},
  {cont__hex_digit_value_27, &frame__hex_digit_value_21, 56, 56, 5, 50},
  {entry__hex_digit_value_31, NULL, 58, 58, 7, 31},
  {entry__hex_digit_value_1, NULL, 53, 58, 3, 32},
  {cont__hex_digit_value_33, &frame__hex_digit_value_1, 58, 58, 32, 32},
  {entry__types__string__convert_from_percent_encoding_8, NULL, 73, 73, 41, 50},
  {cont__types__string__convert_from_percent_encoding_9, &frame__types__string__convert_from_percent_encoding_8, 73, 73, 25, 51},
  {cont__types__string__convert_from_percent_encoding_10, &frame__types__string__convert_from_percent_encoding_8, 73, 73, 22, 51},
  {cont__types__string__convert_from_percent_encoding_11, &frame__types__string__convert_from_percent_encoding_8, 73, 73, 69, 78},
  {cont__types__string__convert_from_percent_encoding_12, &frame__types__string__convert_from_percent_encoding_8, 73, 73, 53, 79},
  {cont__types__string__convert_from_percent_encoding_13, &frame__types__string__convert_from_percent_encoding_8, 73, 73, 22, 79},
  {cont__types__string__convert_from_percent_encoding_14, &frame__types__string__convert_from_percent_encoding_8, 73, 73, 12, 80},
  {cont__types__string__convert_from_percent_encoding_15, &frame__types__string__convert_from_percent_encoding_8, 73, 73, 9, 80},
  {entry__types__string__convert_from_percent_encoding_1, NULL, 67, 67, 21, 29},
  {cont__types__string__convert_from_percent_encoding_4, &frame__types__string__convert_from_percent_encoding_1, 67, 67, 3, 29},
  {cont__types__string__convert_from_percent_encoding_5, &frame__types__string__convert_from_percent_encoding_1, 71, 71, 7, 31},
  {cont__types__string__convert_from_percent_encoding_7, &frame__types__string__convert_from_percent_encoding_1, 70, 73, 5, 81},
  {cont__types__string__convert_from_percent_encoding_16, &frame__types__string__convert_from_percent_encoding_1, 68, 73, 3, 82},
  {cont__types__string__convert_from_percent_encoding_17, &frame__types__string__convert_from_percent_encoding_1, 73, 73, 83, 83},
  {entry__html__define_tag_11, NULL, 127, 127, 34, 44},
  {entry__html__define_tag_14, NULL, 130, 130, 15, 17},
  {entry__html__define_tag_15, NULL, 132, 132, 22, 34},
  {cont__html__define_tag_16, &frame__html__define_tag_15, 132, 132, 15, 47},
  {entry__html__define_tag_7, NULL, 126, 126, 11, 18},
  {cont__html__define_tag_9, &frame__html__define_tag_7, 127, 127, 14, 31},
  {cont__html__define_tag_10, &frame__html__define_tag_7, 127, 127, 11, 44},
  {cont__html__define_tag_12, &frame__html__define_tag_7, 129, 129, 13, 29},
  {cont__html__define_tag_13, &frame__html__define_tag_7, 128, 132, 11, 48},
  {cont__html__define_tag_17, &frame__html__define_tag_7, 133, 133, 11, 28},
  {entry__html__define_tag_20, NULL, 137, 137, 15, 33},
  {entry__html__define_tag_22, NULL, 139, 139, 15, 22},
  {entry__html__define_tag_23, NULL, 141, 141, 15, 23},
  {entry__html__define_tag_19, NULL, 135, 141, 11, 24},
  {entry__html__define_tag_27, NULL, 142, 142, 30, 40},
  {entry__html__define_tag_3, NULL, 123, 123, 7, 27},
  {cont__html__define_tag_5, &frame__html__define_tag_3, 125, 125, 9, 22},
  {cont__html__define_tag_6, &frame__html__define_tag_3, 124, 141, 7, 26},
  {cont__html__define_tag_25, &frame__html__define_tag_3, 142, 142, 14, 27},
  {cont__html__define_tag_26, &frame__html__define_tag_3, 142, 142, 7, 40},
  {entry__html__define_tag_30, NULL, 105, 105, 12, 16},
  {cont__html__define_tag_31, &frame__html__define_tag_30, 105, 105, 9, 22},
  {cont__html__define_tag_32, &frame__html__define_tag_30, 106, 106, 9, 20},
  {cont__html__define_tag_33, &frame__html__define_tag_30, 107, 107, 16, 38},
  {cont__html__define_tag_34, &frame__html__define_tag_30, 107, 107, 9, 44},
  {cont__html__define_tag_35, &frame__html__define_tag_30, 112, 112, 25, 35},
  {cont__html__define_tag_36, &frame__html__define_tag_30, 112, 112, 25, 45},
  {cont__html__define_tag_37, &frame__html__define_tag_30, 112, 112, 47, 55},
  {cont__html__define_tag_39, &frame__html__define_tag_30, 112, 112, 13, 56},
  {cont__html__define_tag_40, &frame__html__define_tag_30, 114, 114, 25, 37},
  {cont__html__define_tag_41, &frame__html__define_tag_30, 114, 114, 25, 47},
  {cont__html__define_tag_42, &frame__html__define_tag_30, 114, 114, 49, 67},
  {cont__html__define_tag_44, &frame__html__define_tag_30, 114, 114, 13, 68},
  {cont__html__define_tag_45, &frame__html__define_tag_30, },
  {cont__html__define_tag_47, &frame__html__define_tag_30, 108, 115, 9, 21},
  {cont__html__define_tag_48, &frame__html__define_tag_30, 116, 116, 9, 14},
  {cont__html__define_tag_49, &frame__html__define_tag_30, 116, 116, 14, 14},
  {entry__html__define_tag_29, NULL, 104, 116, 7, 14},
  {cont__html__define_tag_50, &frame__html__define_tag_29, 116, 116, 14, 14},
  {entry__html__define_tag_54, NULL, 119, 119, 34, 48},
  {cont__html__define_tag_55, &frame__html__define_tag_54, 119, 119, 17, 50},
  {cont__html__define_tag_56, &frame__html__define_tag_54, 119, 119, 50, 50},
  {entry__html__define_tag_52, NULL, 119, 119, 10, 14},
  {cont__html__define_tag_53, &frame__html__define_tag_52, 119, 119, 7, 50},
  {entry__html__define_tag_59, NULL, 120, 120, 18, 34},
  {cont__html__define_tag_60, &frame__html__define_tag_59, 120, 120, 34, 34},
  {entry__html__define_tag_57, NULL, 120, 120, 10, 15},
  {cont__html__define_tag_58, &frame__html__define_tag_57, 120, 120, 7, 34},
  {entry__html__define_tag_65, NULL, 145, 145, 54, 69},
  {cont__html__define_tag_67, &frame__html__define_tag_65, 145, 145, 54, 69},
  {cont__html__define_tag_68, &frame__html__define_tag_65, 145, 145, 54, 69},
  {entry__html__define_tag_63, NULL, 145, 145, 30, 49},
  {cont__html__define_tag_64, &frame__html__define_tag_63, 145, 145, 30, 69},
  {cont__html__define_tag_69, &frame__html__define_tag_63, 145, 145, 30, 69},
  {entry__html__define_tag_93, NULL, 158, 158, 49, 49},
  {cont__html__define_tag_94, &frame__html__define_tag_93, 158, 158, 35, 50},
  {cont__html__define_tag_95, &frame__html__define_tag_93, 158, 158, 22, 58},
  {cont__html__define_tag_98, &frame__html__define_tag_93, 158, 158, 19, 58},
  {entry__html__define_tag_105, NULL, 162, 162, 49, 49},
  {cont__html__define_tag_106, &frame__html__define_tag_105, 162, 162, 35, 50},
  {cont__html__define_tag_107, &frame__html__define_tag_105, 162, 162, 22, 58},
  {cont__html__define_tag_110, &frame__html__define_tag_105, 162, 162, 19, 58},
  {entry__html__define_tag_119, NULL, 172, 172, 19, 50},
  {cont__html__define_tag_120, &frame__html__define_tag_119, 173, 173, 19, 50},
  {cont__html__define_tag_121, &frame__html__define_tag_119, 174, 175, 22, 55},
  {cont__html__define_tag_125, &frame__html__define_tag_119, 174, 175, 19, 55},
  {entry__html__define_tag_75, NULL, 150, 150, 15, 28},
  {cont__html__define_tag_78, &frame__html__define_tag_75, 151, 151, 15, 26},
  {cont__html__define_tag_80, &frame__html__define_tag_75, 152, 152, 15, 24},
  {cont__html__define_tag_83, &frame__html__define_tag_75, 153, 153, 15, 24},
  {cont__html__define_tag_85, &frame__html__define_tag_75, 154, 154, 15, 24},
  {cont__html__define_tag_88, &frame__html__define_tag_75, 156, 156, 27, 46},
  {cont__html__define_tag_89, &frame__html__define_tag_75, 156, 156, 27, 61},
  {cont__html__define_tag_90, &frame__html__define_tag_75, 156, 156, 22, 62},
  {cont__html__define_tag_91, &frame__html__define_tag_75, 156, 156, 17, 67},
  {cont__html__define_tag_92, &frame__html__define_tag_75, 155, 158, 15, 59},
  {cont__html__define_tag_99, &frame__html__define_tag_75, 160, 160, 28, 48},
  {cont__html__define_tag_101, &frame__html__define_tag_75, 160, 160, 28, 63},
  {cont__html__define_tag_102, &frame__html__define_tag_75, 160, 160, 23, 64},
  {cont__html__define_tag_103, &frame__html__define_tag_75, 160, 160, 17, 70},
  {cont__html__define_tag_104, &frame__html__define_tag_75, 159, 162, 15, 59},
  {cont__html__define_tag_111, &frame__html__define_tag_75, 166, 166, 24, 43},
  {cont__html__define_tag_112, &frame__html__define_tag_75, 166, 166, 24, 58},
  {cont__html__define_tag_113, &frame__html__define_tag_75, 166, 166, 19, 59},
  {cont__html__define_tag_114, &frame__html__define_tag_75, 169, 169, 24, 43},
  {cont__html__define_tag_115, &frame__html__define_tag_75, 169, 169, 24, 58},
  {cont__html__define_tag_116, &frame__html__define_tag_75, 169, 169, 19, 59},
  {cont__html__define_tag_117, &frame__html__define_tag_75, },
  {cont__html__define_tag_118, &frame__html__define_tag_75, 163, 175, 15, 57},
  {cont__html__define_tag_126, &frame__html__define_tag_75, 148, 175, 13, 58},
  {cont__html__define_tag_127, &frame__html__define_tag_75, 175, 175, 59, 59},
  {entry__html__define_tag_130, NULL, 179, 179, 63, 63},
  {cont__html__define_tag_131, &frame__html__define_tag_130, 179, 179, 48, 64},
  {cont__html__define_tag_132, &frame__html__define_tag_130, 179, 179, 40, 65},
  {cont__html__define_tag_133, &frame__html__define_tag_130, 179, 179, 15, 74},
  {cont__html__define_tag_136, &frame__html__define_tag_130, 179, 179, 74, 74},
  {entry__html__define_tag_137, NULL, 181, 181, 15, 28},
  {cont__html__define_tag_138, &frame__html__define_tag_137, 181, 181, 28, 28},
  {entry__html__define_tag_74, NULL, 178, 178, 13, 35},
  {cont__html__define_tag_129, &frame__html__define_tag_74, 177, 181, 11, 29},
  {cont__html__define_tag_139, &frame__html__define_tag_74, 182, 182, 11, 24},
  {entry__html__define_tag_71, NULL, 146, 146, 18, 43},
  {cont__html__define_tag_73, &frame__html__define_tag_71, 146, 182, 9, 24},
  {entry__html__define_tag_140, NULL, 184, 184, 9, 25},
  {entry__html__define_tag_2, NULL, 101, 101, 5, 22},
  {cont__html__define_tag_28, &frame__html__define_tag_2, 103, 116, 5, 15},
  {cont__html__define_tag_51, &frame__html__define_tag_2, 118, 120, 5, 34},
  {cont__html__define_tag_61, &frame__html__define_tag_2, 145, 145, 7, 25},
  {cont__html__define_tag_62, &frame__html__define_tag_2, 145, 145, 7, 69},
  {cont__html__define_tag_70, &frame__html__define_tag_2, 144, 184, 5, 26},
  {entry__html__define_tag_1, NULL, 99, 184, 3, 27},
  {entry__html__HTTP_HEADER_1, NULL, 238, 240, 3, 6},
  {entry__html__HTML_HEADER_1, NULL, 242, 242, 21, 45},
  {entry__html__ERROR_PAGE_5, NULL, 248, 248, 11, 19},
  {entry__html__ERROR_PAGE_10, NULL, 251, 251, 30, 38},
  {entry__html__ERROR_PAGE_7, NULL, 250, 250, 7, 12},
  {cont__html__ERROR_PAGE_8, &frame__html__ERROR_PAGE_7, 251, 251, 10, 27},
  {cont__html__ERROR_PAGE_9, &frame__html__ERROR_PAGE_7, 251, 251, 7, 38},
  {entry__html__ERROR_PAGE_4, NULL, 248, 248, 5, 19},
  {cont__html__ERROR_PAGE_6, &frame__html__ERROR_PAGE_4, 249, 251, 5, 38},
  {entry__html__ERROR_PAGE_1, NULL, 245, 245, 3, 13},
  {cont__html__ERROR_PAGE_2, &frame__html__ERROR_PAGE_1, 246, 246, 3, 13},
  {cont__html__ERROR_PAGE_3, &frame__html__ERROR_PAGE_1, 247, 251, 3, 39},
  {entry__html__DUMP_PAGE_5, NULL, 264, 264, 11, 22},
  {entry__html__DUMP_PAGE_8, NULL, 266, 266, 7, 15},
  {cont__html__DUMP_PAGE_9, &frame__html__DUMP_PAGE_8, 267, 267, 7, 13},
  {entry__html__DUMP_PAGE_4, NULL, 264, 264, 5, 22},
  {cont__html__DUMP_PAGE_7, &frame__html__DUMP_PAGE_4, 265, 267, 5, 13},
  {entry__html__DUMP_PAGE_1, NULL, 261, 261, 3, 13},
  {cont__html__DUMP_PAGE_2, &frame__html__DUMP_PAGE_1, 262, 262, 3, 13},
  {cont__html__DUMP_PAGE_3, &frame__html__DUMP_PAGE_1, 263, 267, 3, 14}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__convert_from_percent_encoding(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__convert_from_percent_encoding);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__convert_from_percent_encoding, attr);
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
static NODE *character__65;
static NODE *character__10;
static NODE *number__3;
static NODE *character__70;
static NODE *character__48;
static NODE *character__102;
static NODE *character__60;
static NODE *character__95;
static NODE *number__16;
static NODE *character__40;
static NODE *character__34;
static NODE *character__93;
static NODE *character__91;
static NODE *character__41;
static NODE *number__1;
static NODE *character__97;
static NODE *number__2;
static NODE *character__42;
static NODE *number__10;

static const char *used_namespaces[] = {
  "builtin",
  "std",
  "html",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "system__export__html",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("system/export/html.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__system__export__html(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 3);
  // 60: ... '0' .. '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__57;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__82_1;
}
static void cont__82_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 60: ... 'a' .. 'f'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__102;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__82_2;
}
static void cont__82_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 60: ... 'A' .. 'F'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__65;
  arguments->slots[1] = character__70;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__82_3;
}
static void cont__82_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 60: $hex_digit alt('0' .. '9' 'a' .. 'f' 'A' .. 'F')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__82_4;
}
static void cont__82_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._hex_digit, arguments->slots[0]);
  // 186: define_tag $html::HTML "html" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aec4b5d087d55;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__85_2;
}
static void cont__85_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__HTML, arguments->slots[0]);
  // 187: define_tag $html::HEAD "head" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120ae80b5d687d5d;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__86_2;
}
static void cont__86_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__HEAD, arguments->slots[0]);
  // 188: define_tag $html::META "meta" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__180ae80b5dc07d58;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__87_2;
}
static void cont__87_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__META, arguments->slots[0]);
  // 189: define_tag $html::TITLE "title" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585aee03eaa95032;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__88_2;
}
static void cont__88_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__TITLE, arguments->slots[0]);
  // 190: define_tag $html::STYLE "style" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__625aed43eaa92032;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__89_2;
}
static void cont__89_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__STYLE, arguments->slots[0]);
  // 191: define_tag $html::SCRIPT "script" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7c1f5409013a62a3;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__90_1;
}
static void cont__90_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__SCRIPT, arguments->slots[0]);
  // 192: define_tag $html::BODY "body" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__60aea8b5d407d40;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__91_2;
}
static void cont__91_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__BODY, arguments->slots[0]);
  // 193: define_tag $html::A "a" SIMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9c80;
  arguments->slots[1] = get__SIMPLE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__92_2;
}
static void cont__92_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__A, arguments->slots[0]);
  // 194: define_tag $html::H1 "h1" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4482bf4;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__93_2;
}
static void cont__93_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__H1, arguments->slots[0]);
  // 195: define_tag $html::H2 "h2" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4482bf7;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__94_2;
}
static void cont__94_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__H2, arguments->slots[0]);
  // 196: define_tag $html::H3 "h3" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4482bf6;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__95_2;
}
static void cont__95_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__H3, arguments->slots[0]);
  // 197: define_tag $html::H4 "h4" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4482bf1;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__96_2;
}
static void cont__96_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__H4, arguments->slots[0]);
  // 198: define_tag $html::H5 "h5" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4482bf0;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__97_2;
}
static void cont__97_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__H5, arguments->slots[0]);
  // 199: define_tag $html::H6 "h6" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4482bf3;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__98_2;
}
static void cont__98_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__H6, arguments->slots[0]);
  // 200: define_tag $html::DIV "div" MULTI_PARAGRAPH
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa721415d616bba;
  arguments->slots[1] = get__MULTI_PARAGRAPH();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__99_2;
}
static void cont__99_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__DIV, arguments->slots[0]);
  // 201: define_tag $html::P "p" MULTI_PARAGRAPH
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9c91;
  arguments->slots[1] = get__MULTI_PARAGRAPH();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__100_2;
}
static void cont__100_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__P, arguments->slots[0]);
  // 202: define_tag $html::SPAN "span" SIMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__240aed4b5d687d57;
  arguments->slots[1] = get__SIMPLE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__101_2;
}
static void cont__101_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__SPAN, arguments->slots[0]);
  // 203: define_tag $html::HR "hr" SIMPLE VOID
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4482bb7;
  arguments->slots[1] = get__SIMPLE();
  arguments->slots[2] = get__VOID();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__102_2;
}
static void cont__102_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__HR, arguments->slots[0]);
  // 204: define_tag $html::BR "br" SINGLE_LINE VOID
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4182bb7;
  arguments->slots[1] = get__SINGLE_LINE();
  arguments->slots[2] = get__VOID();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__103_2;
}
static void cont__103_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__BR, arguments->slots[0]);
  // 205: define_tag $html::NOBR "nobr" MULTI_PARAGRAPH
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1e0aea8b5d707d4b;
  arguments->slots[1] = get__MULTI_PARAGRAPH();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__104_2;
}
static void cont__104_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__NOBR, arguments->slots[0]);
  // 206: define_tag $html::OL "ol" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4702ba9;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__105_2;
}
static void cont__105_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__OL, arguments->slots[0]);
  // 207: define_tag $html::UL "ul" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4a02ba9;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__106_2;
}
static void cont__106_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__UL, arguments->slots[0]);
  // 208: define_tag $html::LI "li" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4682bac;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__107_2;
}
static void cont__107_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__LI, arguments->slots[0]);
  // 209: define_tag $html::TABLE "table" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__485aeb83eaa95032;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__108_2;
}
static void cont__108_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__TABLE, arguments->slots[0]);
  // 210: define_tag $html::TR "tr" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4a82bb7;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__109_2;
}
static void cont__109_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__TR, arguments->slots[0]);
  // 211: define_tag $html::TH "th" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4a82bad;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__110_2;
}
static void cont__110_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__TH, arguments->slots[0]);
  // 212: define_tag $html::TD "td" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4a82ba1;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__111_2;
}
static void cont__111_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__TD, arguments->slots[0]);
  // 213: define_tag $html::DL "dl" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4282ba9;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__112_2;
}
static void cont__112_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__DL, arguments->slots[0]);
  // 214: define_tag $html::DT "dt" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4282bb1;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__113_2;
}
static void cont__113_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__DT, arguments->slots[0]);
  // 215: define_tag $html::DD "dd" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4282ba1;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__114_2;
}
static void cont__114_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__DD, arguments->slots[0]);
  // 216: define_tag $html::FORM "form" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__e0aea8b5df07d54;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__115_2;
}
static void cont__115_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__FORM, arguments->slots[0]);
  // 217: define_tag $html::FIELDSET "fieldset" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__66b0a91484fd5094;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__116_2;
}
static void cont__116_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__FIELDSET, arguments->slots[0]);
  // 218: define_tag $html::LEGEND "legend" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__561f570681ca02b3;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__117_2;
}
static void cont__117_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__LEGEND, arguments->slots[0]);
  // 219: define_tag $html::INPUT "input" SIMPLE VOID
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__565aef03ea608023;
  arguments->slots[1] = get__SIMPLE();
  arguments->slots[2] = get__VOID();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__118_2;
}
static void cont__118_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__INPUT, arguments->slots[0]);
  // 220: define_tag $html::TEXTAREA "textarea" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6c80a95a04fcd2c1;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__119_2;
}
static void cont__119_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__TEXTAREA, arguments->slots[0]);
  // 221: define_tag $html::SELECT "select" MULTI_PARAGRAPH
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__401f570901a202a3;
  arguments->slots[1] = get__MULTI_PARAGRAPH();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__120_2;
}
static void cont__120_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__SELECT, arguments->slots[0]);
  // 222: define_tag $html::OPTION "option" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__701f540701c352b9;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__121_2;
}
static void cont__121_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__OPTION, arguments->slots[0]);
  // 223: define_tag $html::BUTTON "button" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__701f534181c302b9;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__122_2;
}
static void cont__122_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__BUTTON, arguments->slots[0]);
  // 224: define_tag $html::CODE "code" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__40aea8b5d407d5c;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__123_2;
}
static void cont__123_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__CODE, arguments->slots[0]);
  // 225: define_tag $html::PRE "pre" MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa724415db96ba9;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__124_2;
}
static void cont__124_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__PRE, arguments->slots[0]);
  // 226: define_tag $html::B "b" SIMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9c83;
  arguments->slots[1] = get__SIMPLE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__125_2;
}
static void cont__125_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__B, arguments->slots[0]);
  // 227: define_tag $html::EM "em" SIMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4202ba8;
  arguments->slots[1] = get__SIMPLE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__126_2;
}
static void cont__126_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__EM, arguments->slots[0]);
  // 228: define_tag $html::CENTER "center" SIMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__441f5341019202a5;
  arguments->slots[1] = get__SIMPLE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__127_2;
}
static void cont__127_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__CENTER, arguments->slots[0]);
  // 229: define_tag $html::LINK "link" SINGLE_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1a0aeb0b5d107d52;
  arguments->slots[1] = get__SINGLE_LINE();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__128_2;
}
static void cont__128_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__LINK, arguments->slots[0]);
  // 230: define_tag $html::IMG "img" SIMPLE VOID
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fa722015d416bab;
  arguments->slots[1] = get__SIMPLE();
  arguments->slots[2] = get__VOID();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__129_2;
}
static void cont__129_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__IMG, arguments->slots[0]);
  // 231: define_tag $html::FIGURE "figure" MULTI_PARAGRAPH
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__561f5303812ac2b2;
  arguments->slots[1] = get__MULTI_PARAGRAPH();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__130_2;
}
static void cont__130_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__FIGURE, arguments->slots[0]);
  // 232: define_tag $html::FIGCAPTION "figcaption" MULTI_PARAGRAPH
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1d68225b2f52750f;
  arguments->slots[1] = get__MULTI_PARAGRAPH();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__131_2;
}
static void cont__131_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__FIGCAPTION, arguments->slots[0]);
  // 233: define_tag $html::VIDEO "video" MULTI_PARAGRAPH
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585aea03eae17038;
  arguments->slots[1] = get__MULTI_PARAGRAPH();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__132_2;
}
static void cont__132_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__VIDEO, arguments->slots[0]);
  // 234: define_tag $html::SOURCE "source" SIMPLE VOID
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__721f52c901a2a2b2;
  arguments->slots[1] = get__SIMPLE();
  arguments->slots[2] = get__VOID();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__133_2;
}
static void cont__133_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__SOURCE, arguments->slots[0]);
  // 235: define_tag $html::CANVAS "canvas" MULTI_PARAGRAPH
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__441f53c101b242a4;
  arguments->slots[1] = get__MULTI_PARAGRAPH();
  result_count = 1;
  myself = get__define_tag();
  func = myself->type;
  frame->cont = cont__134_2;
}
static void cont__134_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.html__CANVAS, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__html__emit_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // arg: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 42: ... write arg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__emit_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 42: ... for_each args: (arg) write arg
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = func__html__emit_2;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__encode_1(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // txt: 0
  // tag: 1
  // arg_str: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 44: ... emit txt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* txt */;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__TEXT_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 46: ... string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__html__TEXT_2;
}
static void cont__html__TEXT_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 46: ... html::encode string(args*) undefined undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = get__undefined();
  arguments->slots[2] = get__undefined();
  result_count = frame->caller_result_count;
  myself = get__html__encode();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__hex_digit_value_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // chr: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 54: -> chr >= '0' && chr <= '9': return chr-'0'
  frame->slots[2] /* temp__1 */ = create_closure(entry__hex_digit_value_2, 0);
  // 55: -> chr >= 'a' && chr <= 'f': return chr-'a'+10
  frame->slots[3] /* temp__2 */ = create_closure(entry__hex_digit_value_11, 0);
  // 56: -> chr >= 'A' && chr <= 'F': return chr-'A'+10
  frame->slots[4] /* temp__3 */ = create_closure(entry__hex_digit_value_21, 0);
  // 53: cond
  // 54:   -> chr >= '0' && chr <= '9': return chr-'0'
  // 55:   -> chr >= 'a' && chr <= 'f': return chr-'a'+10
  // 56:   -> chr >= 'A' && chr <= 'F': return chr-'A'+10
  // 57:   :
  // 58:     raise "invalid hex digit"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  arguments->slots[3] = func__hex_digit_value_31;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__hex_digit_value_33;
}
static void entry__hex_digit_value_28(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // return: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: ... chr-'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__hex_digit_value_29;
}
static void cont__hex_digit_value_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 56: ... chr-'A'+10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__hex_digit_value_30;
}
static void cont__hex_digit_value_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 56: ... return chr-'A'+10
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__hex_digit_value_18(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // return: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 55: ... chr-'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__hex_digit_value_19;
}
static void cont__hex_digit_value_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 55: ... chr-'a'+10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__hex_digit_value_20;
}
static void cont__hex_digit_value_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 55: ... return chr-'a'+10
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__hex_digit_value_9(void) {
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
  // 54: ... chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__hex_digit_value_10;
}
static void cont__hex_digit_value_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 54: ... return chr-'0'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__hex_digit_value_2(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // chr: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 54: ... chr >= '0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__hex_digit_value_3;
}
static void cont__hex_digit_value_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 54: ... chr >= '0'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__hex_digit_value_4;
}
static void cont__hex_digit_value_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 54: ... chr <= '9'
  frame->slots[5] /* temp__4 */ = create_closure(entry__hex_digit_value_5, 0);
  // 54: ... chr >= '0' && chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__hex_digit_value_8;
}
static void entry__hex_digit_value_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 54: ... chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__hex_digit_value_6;
}
static void cont__hex_digit_value_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 54: ... chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__hex_digit_value_7;
}
static void cont__hex_digit_value_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 54: ... chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__hex_digit_value_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 54: ... : return chr-'0'
  frame->slots[6] /* temp__5 */ = create_closure(entry__hex_digit_value_9, 0);
  // 54: -> chr >= '0' && chr <= '9': return chr-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__hex_digit_value_11(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // chr: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 55: ... chr >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__hex_digit_value_12;
}
static void cont__hex_digit_value_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 55: ... chr >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__hex_digit_value_13;
}
static void cont__hex_digit_value_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 55: ... chr <= 'f'
  frame->slots[5] /* temp__4 */ = create_closure(entry__hex_digit_value_14, 0);
  // 55: ... chr >= 'a' && chr <= 'f'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__hex_digit_value_17;
}
static void entry__hex_digit_value_14(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 55: ... chr <= 'f'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__102;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__hex_digit_value_15;
}
static void cont__hex_digit_value_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 55: ... chr <= 'f'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__hex_digit_value_16;
}
static void cont__hex_digit_value_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 55: ... chr <= 'f'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__hex_digit_value_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 55: ... : return chr-'a'+10
  frame->slots[6] /* temp__5 */ = create_closure(entry__hex_digit_value_18, 0);
  // 55: -> chr >= 'a' && chr <= 'f': return chr-'a'+10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__hex_digit_value_21(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // chr: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: ... chr >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__hex_digit_value_22;
}
static void cont__hex_digit_value_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 56: ... chr >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__hex_digit_value_23;
}
static void cont__hex_digit_value_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 56: ... chr <= 'F'
  frame->slots[5] /* temp__4 */ = create_closure(entry__hex_digit_value_24, 0);
  // 56: ... chr >= 'A' && chr <= 'F'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__hex_digit_value_27;
}
static void entry__hex_digit_value_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: ... chr <= 'F'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__70;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__hex_digit_value_25;
}
static void cont__hex_digit_value_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 56: ... chr <= 'F'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__hex_digit_value_26;
}
static void cont__hex_digit_value_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 56: ... chr <= 'F'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__hex_digit_value_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 56: ... : return chr-'A'+10
  frame->slots[6] /* temp__5 */ = create_closure(entry__hex_digit_value_28, 0);
  // 56: -> chr >= 'A' && chr <= 'F': return chr-'A'+10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__hex_digit_value_31(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 58: raise "invalid hex digit"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7fe91a650e32a4f3;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__hex_digit_value_33(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__convert_from_percent_encoding_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 67: ... "+" = " "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cca;
  arguments->slots[1] = string__578a5af303e9cc1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_4;
}
static void cont__types__string__convert_from_percent_encoding_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 67: replace_all &self "+" = " "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_5;
}
static void cont__types__string__convert_from_percent_encoding_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  // 71: "%", hex_digit, hex_digit
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc4;
  arguments->slots[1] = var._hex_digit;
  arguments->slots[2] = var._hex_digit;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_7;
}
static void cont__types__string__convert_from_percent_encoding_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 70: =
  // 71:   "%", hex_digit, hex_digit
  // 72:   : (capture)
  // 73:     -> character(16*hex_digit_value(capture(2))+hex_digit_value(capture(3)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__types__string__convert_from_percent_encoding_8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_16;
}
static void entry__types__string__convert_from_percent_encoding_8(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // capture: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 73: ... capture(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* capture */;
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_9;
}
static void cont__types__string__convert_from_percent_encoding_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 73: ... hex_digit_value(capture(2))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = var._hex_digit_value;
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_10;
}
static void cont__types__string__convert_from_percent_encoding_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 73: ... 16*hex_digit_value(capture(2))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__16;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_11;
}
static void cont__types__string__convert_from_percent_encoding_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 73: ... capture(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = frame->slots[0] /* capture */;
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_12;
}
static void cont__types__string__convert_from_percent_encoding_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__7 */ = arguments->slots[0];
  // 73: ... hex_digit_value(capture(3))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__7 */;
  result_count = 1;
  myself = var._hex_digit_value;
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_13;
}
static void cont__types__string__convert_from_percent_encoding_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 73: ... 16*hex_digit_value(capture(2))+hex_digit_value(capture(3))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_14;
}
static void cont__types__string__convert_from_percent_encoding_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 73: ... character(16*hex_digit_value(capture(2))+hex_digit_value(capture(3)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__character();
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_15;
}
static void cont__types__string__convert_from_percent_encoding_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 73: -> character(16*hex_digit_value(capture(2))+hex_digit_value(capture(3)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__convert_from_percent_encoding_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 68: replace_all
  // 69:   &self
  // 70:   =
  // 71:     "%", hex_digit, hex_digit
  // 72:     : (capture)
  // 73:       -> character(16*hex_digit_value(capture(2))+hex_digit_value(capture(3)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__types__string__convert_from_percent_encoding_17;
}
static void cont__types__string__convert_from_percent_encoding_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__html__define_tag_74(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // field: 0
  // emit_tag: 1
  // convert: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* emit_tag */
  // _define $convert 
  // : (&line)
  //   std::key_value_pair !temp__1 "<|>" "<br>"
  //   std::key_value_pair !temp__2 '<' "&lt;"
  //   std::key_value_pair !temp__3 "\*" "*"
  //   std::key_value_pair !temp__4 "\<" "<"
  //   std::key_value_pair !temp__5 "\[" "["
  //   not_followed_by !temp__10 '*'
  //   std::sequence !temp__9 temp__10 ANY_CHARACTER
  //   many !temp__8 temp__9
  //   std::sequence !temp__7 '*' temp__8 '*'
  //   std::key_value_pair !temp__6 temp__7: (text)
  //     std::negate !temp__3 2
  //     range !temp__2 text 2 temp__3
  //     string !temp__1 "<i>" temp__2 "</i>"
  //     -> temp__1
  //   not_followed_by !temp__15 "**"
  //   std::sequence !temp__14 temp__15 ANY_CHARACTER
  //   many !temp__13 temp__14
  //   std::sequence !temp__12 "**" temp__13 "**"
  //   std::key_value_pair !temp__11 temp__12: (text)
  //     std::negate !temp__3 3
  //     range !temp__2 text 3 temp__3
  //     string !temp__1 "<b>" temp__2 "</b>"
  //     -> temp__1
  //   not_followed_by !temp__20 ']'
  //   std::sequence !temp__19 temp__20 ANY_CHARACTER
  //   many !temp__18 temp__19
  //   not_followed_by !temp__23 ')'
  //   std::sequence !temp__22 temp__23 ANY_CHARACTER
  //   many !temp__21 temp__22
  //   sequence !temp__17 '[' temp__18 ']' '(' temp__21 ')'
  //   std::key_value_pair !temp__16 temp__17: (reference)
  //     between $link reference '(' ')'
  //     between $text reference '[' ']'
  //     std::string
  //       !temp__1
  //       "
  //         <a href="@
  //       link
  //       "@quot;>"
  //       text
  //       "</a>"
  //     -> temp__1
  //   replace_all !line
  //     line
  //     temp__1
  //     temp__2
  //     temp__3
  //     temp__4
  //     temp__5
  //     temp__6
  //     temp__11
  //     temp__16
  frame->slots[2] /* convert */ = func__html__define_tag_75;
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* field */ = create_cell_with_contents(arguments->slots[0]);
  // 178: field .has_prefix. "* "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* field */;
  arguments->slots[1] = string__2d7981f4e6582be5;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__html__define_tag_129;
}
static void entry__html__define_tag_75(void) {
  allocate_initialized_frame_gc(1, 24);
  // slot allocations:
  // line: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* line */ = create_cell_with_contents(arguments->slots[0]);
  // 150: "<|>" = "<br>"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa737415dc96bf2;
  arguments->slots[1] = string__ba0ae9cb5df07d07;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_78;
}
static void cont__html__define_tag_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 151: '<' = "&lt;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = string__8e0aea4b5dc07d02;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_80;
}
static void cont__html__define_tag_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 152: "\*" = "*"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5e82bef;
  arguments->slots[1] = string__578a5af303e9ccb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_83;
}
static void cont__html__define_tag_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 153: "\<" = "<"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5e82bf9;
  arguments->slots[1] = string__578a5af303e9cdd;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_85;
}
static void cont__html__define_tag_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 154: "\[" = "["
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5e82b9e;
  arguments->slots[1] = string__578a5af303e9cba;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_88;
}
static void cont__html__define_tag_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 156: ... not_followed_by('*')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__42;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__html__define_tag_89;
}
static void cont__html__define_tag_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__10 */ = arguments->slots[0];
  // 156: ... not_followed_by('*'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__10 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__html__define_tag_90;
}
static void cont__html__define_tag_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__9 */ = arguments->slots[0];
  // 156: ... many(not_followed_by('*'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__9 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__html__define_tag_91;
}
static void cont__html__define_tag_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__8 */ = arguments->slots[0];
  // 156: '*', many(not_followed_by('*'), ANY_CHARACTER), '*'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = frame->slots[8] /* temp__8 */;
  arguments->slots[2] = character__42;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__html__define_tag_92;
}
static void cont__html__define_tag_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__7 */ = arguments->slots[0];
  // 155: =
  // 156:   '*', many(not_followed_by('*'), ANY_CHARACTER), '*'
  // 157:   : (text)
  // 158:     -> string("<i>" range(text 2 -2) "</i>")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__7 */;
  arguments->slots[1] = func__html__define_tag_93;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_99;
}
static void entry__html__define_tag_93(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 158: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__html__define_tag_94;
}
static void cont__html__define_tag_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 158: ... range(text 2 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__html__define_tag_95;
}
static void cont__html__define_tag_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 158: ... string("<i>" range(text 2 -2) "</i>")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fa737415d616bf2;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__ba0afa8b5d287d07;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__html__define_tag_98;
}
static void cont__html__define_tag_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 158: -> string("<i>" range(text 2 -2) "</i>")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 160: ... not_followed_by("**")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6582bef;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__html__define_tag_101;
}
static void cont__html__define_tag_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__15 */ = arguments->slots[0];
  // 160: ... not_followed_by("**"), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__15 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__html__define_tag_102;
}
static void cont__html__define_tag_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__14 */ = arguments->slots[0];
  // 160: ... many(not_followed_by("**"), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__14 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__html__define_tag_103;
}
static void cont__html__define_tag_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__13 */ = arguments->slots[0];
  // 160: "**", many(not_followed_by("**"), ANY_CHARACTER), "**"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6582bef;
  arguments->slots[1] = frame->slots[13] /* temp__13 */;
  arguments->slots[2] = string__2d7981f4e6582bef;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__html__define_tag_104;
}
static void cont__html__define_tag_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__12 */ = arguments->slots[0];
  // 159: =
  // 160:   "**", many(not_followed_by("**"), ANY_CHARACTER), "**"
  // 161:   : (text)
  // 162:     -> string("<b>" range(text 3 -3) "</b>")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__12 */;
  arguments->slots[1] = func__html__define_tag_105;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_111;
}
static void entry__html__define_tag_105(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 162: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__html__define_tag_106;
}
static void cont__html__define_tag_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 162: ... range(text 3 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__html__define_tag_107;
}
static void cont__html__define_tag_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 162: ... string("<b>" range(text 3 -3) "</b>")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fa737415d396bf2;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__ba0afa8b5d707d07;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__html__define_tag_110;
}
static void cont__html__define_tag_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 162: -> string("<b>" range(text 3 -3) "</b>")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__11 */ = arguments->slots[0];
  // 166: ... not_followed_by(']')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__93;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__html__define_tag_112;
}
static void cont__html__define_tag_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__20 */ = arguments->slots[0];
  // 166: ... not_followed_by(']'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[20] /* temp__20 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__html__define_tag_113;
}
static void cont__html__define_tag_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__19 */ = arguments->slots[0];
  // 166: many(not_followed_by(']'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__19 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__html__define_tag_114;
}
static void cont__html__define_tag_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__18 */ = arguments->slots[0];
  // 169: ... not_followed_by(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__html__define_tag_115;
}
static void cont__html__define_tag_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__23 */ = arguments->slots[0];
  // 169: ... not_followed_by(')'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[23] /* temp__23 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__html__define_tag_116;
}
static void cont__html__define_tag_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__22 */ = arguments->slots[0];
  // 169: many(not_followed_by(')'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[22] /* temp__22 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__html__define_tag_117;
}
static void cont__html__define_tag_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__21 */ = arguments->slots[0];
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = character__91;
  arguments->slots[1] = frame->slots[18] /* temp__18 */;
  arguments->slots[2] = character__93;
  arguments->slots[3] = character__40;
  arguments->slots[4] = frame->slots[21] /* temp__21 */;
  arguments->slots[5] = character__41;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__html__define_tag_118;
}
static void cont__html__define_tag_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__17 */ = arguments->slots[0];
  // 163: =
  // 164:   sequence
  // 165:     '['
  // 166:     many(not_followed_by(']'), ANY_CHARACTER)
  // 167:     ']'
  // 168:     '('
  // 169:     many(not_followed_by(')'), ANY_CHARACTER)
  // 170:     ')'
  // 171:   : (reference)
  // 172:     $link between(reference '(' ')')
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__17 */;
  arguments->slots[1] = func__html__define_tag_119;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_126;
}
static void entry__html__define_tag_119(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  // link: 1
  // text: 2
  frame->slots[1] /* link */ = create_future();
  frame->slots[2] /* text */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 172: $link between(reference '(' ')')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  arguments->slots[1] = character__40;
  arguments->slots[2] = character__41;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__html__define_tag_120;
}
static void cont__html__define_tag_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* link */, arguments->slots[0]);
  // 173: $text between(reference '[' ']')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  arguments->slots[1] = character__91;
  arguments->slots[2] = character__93;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__html__define_tag_121;
}
static void cont__html__define_tag_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* text */, arguments->slots[0]);
  // 174: ... "
  // 175:   <a href="@(link)@quot;>@(text)</a>@
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__65b02728dcea54a7;
  arguments->slots[1] = frame->slots[1] /* link */;
  arguments->slots[2] = string__2d7981f4e6182bfb;
  arguments->slots[3] = frame->slots[2] /* text */;
  arguments->slots[4] = string__ba0afa8b5d687d07;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__html__define_tag_125;
}
static void cont__html__define_tag_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 174: -> "
  // 175:   <a href="@(link)@quot;>@(text)</a>@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__16 */ = arguments->slots[0];
  // 148: replace_all
  // 149:   &line
  // 150:   "<|>" = "<br>"
  // 151:   '<' = "&lt;"
  // 152:   "\*" = "*"
  // 153:   "\<" = "<"
  // 154:   "\[" = "["
  // 155:   =
  // 156:     '*', many(not_followed_by('*'), ANY_CHARACTER), '*'
  // 157:     : (text)
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  arguments->slots[3] = frame->slots[3] /* temp__3 */;
  arguments->slots[4] = frame->slots[4] /* temp__4 */;
  arguments->slots[5] = frame->slots[5] /* temp__5 */;
  arguments->slots[6] = frame->slots[6] /* temp__6 */;
  arguments->slots[7] = frame->slots[11] /* temp__11 */;
  arguments->slots[8] = frame->slots[16] /* temp__16 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__html__define_tag_127;
}
static void cont__html__define_tag_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* line */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* line */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 178: ... :
  // 179:   !field string("<ul><li>" convert(range(field 3 -1)) "</ul>")
  frame->slots[4] /* temp__2 */ = create_closure(entry__html__define_tag_130, 0);
  // 180: :
  // 181:   convert &field
  frame->slots[5] /* temp__3 */ = create_closure(entry__html__define_tag_137, 0);
  // 177: if
  // 178:   field .has_prefix. "* ":
  // 179:     !field string("<ul><li>" convert(range(field 3 -1)) "</ul>")
  // 180:   :
  // 181:     convert &field
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__html__define_tag_139;
}
static void entry__html__define_tag_130(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // field: 0
  // convert: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* field */
  frame->slots[1] = myself->closure.frame->slots[2]; /* convert */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__html__define_tag_131;
}
static void cont__html__define_tag_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 179: ... range(field 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* field */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__html__define_tag_132;
}
static void cont__html__define_tag_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 179: ... convert(range(field 3 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* convert */;
  func = myself->type;
  frame->cont = cont__html__define_tag_133;
}
static void cont__html__define_tag_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 179: !field string("<ul><li>" convert(range(field 3 -1)) "</ul>")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__d6c0aed004987b9e;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = string__d45aee43eaadd069;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__html__define_tag_136;
}
static void cont__html__define_tag_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* field */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__html__define_tag_137(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // convert: 0
  // field: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* convert */
  frame->slots[1] = myself->closure.frame->slots[0]; /* field */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 181: convert &field
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* field */;
  result_count = 1;
  myself = frame->slots[0] /* convert */;
  func = myself->type;
  frame->cont = cont__html__define_tag_138;
}
static void cont__html__define_tag_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* field */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_139(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 182: emit_tag field
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* field */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* emit_tag */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_71(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // contents: 0
  // emit_tag: 1
  frame->slots[0] = myself->closure.frame->slots[7]; /* contents */
  frame->slots[1] = myself->closure.frame->slots[8]; /* emit_tag */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 146: ... split(contents "@nl;@nl;")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* contents */;
  arguments->slots[1] = string__2d7981f4e7582bcf;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__html__define_tag_73;
}
static void cont__html__define_tag_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 146: ... : ($field)
  // 147:   $convert: (&line)
  // 148:     replace_all
  // 149:       &line
  // 150:       "<|>" = "<br>"
  // 151:       '<' = "&lt;"
  // 152:       "\*" = "*"
  // 153:       "\<" = "<"
  // 154:       "\[" = "["
  // 155:       =
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__html__define_tag_74, 1);
  // 146: for_each split(contents "@nl;@nl;"): ($field)
  // 147:   $convert: (&line)
  // 148:     replace_all
  // 149:       &line
  // 150:       "<|>" = "<br>"
  // 151:       '<' = "&lt;"
  // 152:       "\*" = "*"
  // 153:       "\<" = "<"
  // 154:       "\[" = "["
  // 155:       =
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_140(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // emit_tag: 0
  // contents: 1
  frame->slots[0] = myself->closure.frame->slots[8]; /* emit_tag */
  frame->slots[1] = myself->closure.frame->slots[7]; /* contents */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 184: emit_tag contents
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* contents */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* emit_tag */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_2(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(4, 14);
  // slot allocations:
  // args: 0
  // name: 1
  // mode: 2
  // tag_mode: 3
  // i: 4
  // n: 5
  // arg_str: 6
  // contents: 7
  // emit_tag: 8
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* mode */
  frame->slots[3] = myself->closure.frame->slots[2]; /* tag_mode */
  frame->slots[8] /* emit_tag */ = create_future();
  frame->slots[4] /* i */ = create_cell();
  frame->slots[5] /* n */ = create_future();
  frame->slots[6] /* arg_str */ = create_cell();
  frame->slots[7] /* contents */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 122: ... : (cts)
  // 123:   emit "<" name arg_str
  // 124:   if
  // 125:     cts.is_defined:
  // 126:       emit ">"
  // 127:       if mode == MULTI_LINE: emit '@nl;'
  // 128:       if
  // 129:         cts.is_a_function:
  // 130:           cts
  // 131:         :
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__html__define_tag_3, 1);
  // 122: $emit_tag: (cts)
  // 123:   emit "<" name arg_str
  // 124:   if
  // 125:     cts.is_defined:
  // 126:       emit ">"
  // 127:       if mode == MULTI_LINE: emit '@nl;'
  // 128:       if
  // 129:         cts.is_a_function:
  // 130:           cts
  // 131:         :
  // ...
  initialize_future(frame->slots[8] /* emit_tag */, frame->slots[9] /* temp__1 */);
  // 100: $$i 1
  ((CELL *)frame->slots[4])->contents /* i */ = number__1;
  // 101: $n length_of(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__html__define_tag_28;
}
static void entry__html__define_tag_27(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 142: ... emit '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__10;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_3(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // cts: 0
  // name: 1
  // arg_str: 2
  // mode: 3
  // tag_mode: 4
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  frame->slots[2] = myself->closure.frame->slots[6]; /* arg_str */
  frame->slots[3] = myself->closure.frame->slots[2]; /* mode */
  frame->slots[4] = myself->closure.frame->slots[3]; /* tag_mode */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 123: emit "<" name arg_str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdd;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* arg_str */;
  result_count = 0;
  myself = get__emit();
  func = myself->type;
  frame->cont = cont__html__define_tag_5;
}
static void cont__html__define_tag_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 125: cts.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* cts */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__html__define_tag_6;
}
static void cont__html__define_tag_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 125: ... :
  // 126:   emit ">"
  // 127:   if mode == MULTI_LINE: emit '@nl;'
  // 128:   if
  // 129:     cts.is_a_function:
  // 130:       cts
  // 131:     :
  // 132:       encode cts.to_string name arg_str
  // 133:   emit "</" name ">"
  frame->slots[6] /* temp__2 */ = create_closure(entry__html__define_tag_7, 0);
  // 134: :
  // 135:   case tag_mode
  // 136:     html::NORMAL:
  // 137:       emit "></" name ">"
  // 138:     VOID:
  // 139:       emit ">"
  // 140:     FOREIGN:
  // 141:       emit "/>"
  frame->slots[7] /* temp__3 */ = create_closure(entry__html__define_tag_19, 0);
  // 124: if
  // 125:   cts.is_defined:
  // 126:     emit ">"
  // 127:     if mode == MULTI_LINE: emit '@nl;'
  // 128:     if
  // 129:       cts.is_a_function:
  // 130:         cts
  // 131:       :
  // 132:         encode cts.to_string name arg_str
  // 133:     emit "</" name ">"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__html__define_tag_25;
}
static void entry__html__define_tag_20(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 137: emit "></" name ">"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fa737c15fc96be3;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cdf;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_22(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 139: emit ">"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdf;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 141: emit "/>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6702bfb;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_7(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // mode: 0
  // cts: 1
  // name: 2
  // arg_str: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* mode */
  frame->slots[1] = myself->closure.frame->slots[0]; /* cts */
  frame->slots[2] = myself->closure.frame->slots[1]; /* name */
  frame->slots[3] = myself->closure.frame->slots[2]; /* arg_str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 126: emit ">"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdf;
  result_count = 0;
  myself = get__emit();
  func = myself->type;
  frame->cont = cont__html__define_tag_9;
}
static void cont__html__define_tag_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 127: ... mode == MULTI_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mode */;
  arguments->slots[1] = get__MULTI_LINE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__html__define_tag_10;
}
static void cont__html__define_tag_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 127: if mode == MULTI_LINE: emit '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__html__define_tag_11;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__html__define_tag_12;
}
static void entry__html__define_tag_11(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 127: ... emit '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__10;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__html__define_tag_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 129: cts.is_a_function
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* cts */;
  result_count = 1;
  myself = get__is_a_function();
  func = myself->type;
  frame->cont = cont__html__define_tag_13;
}
static void cont__html__define_tag_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 129: ... :
  // 130:   cts
  frame->slots[5] /* temp__2 */ = create_closure(entry__html__define_tag_14, 0);
  // 131: :
  // 132:   encode cts.to_string name arg_str
  frame->slots[6] /* temp__3 */ = create_closure(entry__html__define_tag_15, 0);
  // 128: if
  // 129:   cts.is_a_function:
  // 130:     cts
  // 131:   :
  // 132:     encode cts.to_string name arg_str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__html__define_tag_17;
}
static void entry__html__define_tag_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // cts: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* cts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: cts
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* cts */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_15(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // cts: 0
  // name: 1
  // arg_str: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* cts */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  frame->slots[2] = myself->closure.frame->slots[3]; /* arg_str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 132: ... cts.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* cts */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__html__define_tag_16;
}
static void cont__html__define_tag_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 132: encode cts.to_string name arg_str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* arg_str */;
  result_count = frame->caller_result_count;
  myself = get__encode();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__html__define_tag_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 133: emit "</" name ">"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6e82bea;
  arguments->slots[1] = frame->slots[2] /* name */;
  arguments->slots[2] = string__578a5af303e9cdf;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_19(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // tag_mode: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* tag_mode */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 136: ... :
  // 137:   emit "></" name ">"
  frame->slots[2] /* temp__1 */ = create_closure(entry__html__define_tag_20, 0);
  // 135: case tag_mode
  // 136:   html::NORMAL:
  // 137:     emit "></" name ">"
  // 138:   VOID:
  // 139:     emit ">"
  // 140:   FOREIGN:
  // 141:     emit "/>"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tag_mode */;
  arguments->slots[1] = var.html__NORMAL;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = get__VOID();
  arguments->slots[4] = func__html__define_tag_22;
  arguments->slots[5] = get__FOREIGN();
  arguments->slots[6] = func__html__define_tag_23;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__html__define_tag_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 142: ... mode == SIMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mode */;
  arguments->slots[1] = get__SIMPLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__html__define_tag_26;
}
static void cont__html__define_tag_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 142: unless mode == SIMPLE: emit '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__html__define_tag_27;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__html__define_tag_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* n */, arguments->slots[0]);
  // 102: $$arg_str ""
  ((CELL *)frame->slots[6])->contents /* arg_str */ = empty_string;
  // 103: ... : (-> break)
  // 104:   forever:
  // 105:     if i > n break
  // 106:     $arg args(i)
  // 107:     unless arg.is_a_key_value_pair break
  // 108:     append
  // 109:       &arg_str
  // 110:       string
  // 111:         " "
  // 112:         replace_all(key_of(arg).to_string '_' = "-")
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__html__define_tag_29, 0);
  // 103: do: (-> break)
  // 104:   forever:
  // 105:     if i > n break
  // 106:     $arg args(i)
  // 107:     unless arg.is_a_key_value_pair break
  // 108:     append
  // 109:       &arg_str
  // 110:       string
  // 111:         " "
  // 112:         replace_all(key_of(arg).to_string '_' = "-")
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__html__define_tag_51;
}
static void entry__html__define_tag_29(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // break: 0
  // n: 1
  // i: 2
  // args: 3
  // arg_str: 4
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[5]; /* n */
  frame->slots[2] = myself->closure.frame->slots[4]; /* i */
  frame->slots[3] = myself->closure.frame->slots[0]; /* args */
  frame->slots[4] = myself->closure.frame->slots[6]; /* arg_str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: ... :
  // 105:   if i > n break
  // 106:   $arg args(i)
  // 107:   unless arg.is_a_key_value_pair break
  // 108:   append
  // 109:     &arg_str
  // 110:     string
  // 111:       " "
  // 112:       replace_all(key_of(arg).to_string '_' = "-")
  // 113:       "=@quot;"
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__html__define_tag_30, 0);
  // 104: forever:
  // 105:   if i > n break
  // 106:   $arg args(i)
  // 107:   unless arg.is_a_key_value_pair break
  // 108:   append
  // 109:     &arg_str
  // 110:     string
  // 111:       " "
  // 112:       replace_all(key_of(arg).to_string '_' = "-")
  // 113:       "=@quot;"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__html__define_tag_50;
}
static void entry__html__define_tag_30(void) {
  allocate_initialized_frame_gc(5, 15);
  // slot allocations:
  // n: 0
  // i: 1
  // break: 2
  // args: 3
  // arg_str: 4
  // arg: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* n */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* break */
  frame->slots[3] = myself->closure.frame->slots[3]; /* args */
  frame->slots[4] = myself->closure.frame->slots[4]; /* arg_str */
  frame->slots[5] /* arg */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: ... i > n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__html__define_tag_31;
}
static void cont__html__define_tag_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 105: if i > n break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__html__define_tag_32;
}
static void cont__html__define_tag_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 106: $arg args(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[3] /* args */;
  func = myself->type;
  frame->cont = cont__html__define_tag_33;
}
static void cont__html__define_tag_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* arg */, arguments->slots[0]);
  // 107: ... arg.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* arg */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_34;
}
static void cont__html__define_tag_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 107: unless arg.is_a_key_value_pair break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__html__define_tag_35;
}
static void cont__html__define_tag_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 112: ... key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__html__define_tag_36;
}
static void cont__html__define_tag_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  // 112: ... key_of(arg).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__html__define_tag_37;
}
static void cont__html__define_tag_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 112: ... '_' = "-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__95;
  arguments->slots[1] = string__578a5af303e9ccc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_39;
}
static void cont__html__define_tag_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 112: replace_all(key_of(arg).to_string '_' = "-")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = frame->slots[10] /* temp__5 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__html__define_tag_40;
}
static void cont__html__define_tag_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 114: ... value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__html__define_tag_41;
}
static void cont__html__define_tag_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__8 */ = arguments->slots[0];
  // 114: ... value_of(arg).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__8 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__html__define_tag_42;
}
static void cont__html__define_tag_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 114: ... '@quot;' = "&quot;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = string__721f55a3811b42ec;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__html__define_tag_44;
}
static void cont__html__define_tag_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__9 */ = arguments->slots[0];
  // 114: replace_all(value_of(arg).to_string '@quot;' = "&quot;")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[14] /* temp__9 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__html__define_tag_45;
}
static void cont__html__define_tag_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__6 */ = arguments->slots[0];
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = string__2d7981f4e6e02be7;
  arguments->slots[3] = frame->slots[11] /* temp__6 */;
  arguments->slots[4] = character__34;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__html__define_tag_47;
}
static void cont__html__define_tag_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 108: append
  // 109:   &arg_str
  // 110:   string
  // 111:     " "
  // 112:     replace_all(key_of(arg).to_string '_' = "-")
  // 113:     "=@quot;"
  // 114:     replace_all(value_of(arg).to_string '@quot;' = "&quot;")
  // 115:     '@quot;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* arg_str */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__html__define_tag_48;
}
static void cont__html__define_tag_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* arg_str */ = arguments->slots[0];
  // 116: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__html__define_tag_49;
}
static void cont__html__define_tag_49(void) {
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
static void cont__html__define_tag_50(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 117: $$contents undefined
  ((CELL *)frame->slots[7])->contents /* contents */ = get__undefined();
  // 119: -> i < n: !contents string(range(args i n)*)
  frame->slots[9] /* temp__1 */ = create_closure(entry__html__define_tag_52, 0);
  // 120: -> i == n: !contents args(i)
  frame->slots[10] /* temp__2 */ = create_closure(entry__html__define_tag_57, 0);
  // 118: cond
  // 119:   -> i < n: !contents string(range(args i n)*)
  // 120:   -> i == n: !contents args(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__html__define_tag_61;
}
static void entry__html__define_tag_59(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // contents: 0
  // args: 1
  // i: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* contents */
  frame->slots[1] = myself->closure.frame->slots[3]; /* args */
  frame->slots[2] = myself->closure.frame->slots[0]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: ... !contents args(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* args */;
  func = myself->type;
  frame->cont = cont__html__define_tag_60;
}
static void cont__html__define_tag_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* contents */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__html__define_tag_54(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // contents: 0
  // args: 1
  // i: 2
  // n: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* contents */
  frame->slots[1] = myself->closure.frame->slots[3]; /* args */
  frame->slots[2] = myself->closure.frame->slots[0]; /* i */
  frame->slots[3] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... range(args i n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[2] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__html__define_tag_55;
}
static void cont__html__define_tag_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 119: ... !contents string(range(args i n)*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[4] /* temp__1 */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__html__define_tag_56;
}
static void cont__html__define_tag_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* contents */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__html__define_tag_52(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // i: 0
  // n: 1
  // contents: 2
  // args: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* i */
  frame->slots[1] = myself->closure.frame->slots[5]; /* n */
  frame->slots[2] = myself->closure.frame->slots[7]; /* contents */
  frame->slots[3] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__html__define_tag_53;
}
static void cont__html__define_tag_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 119: ... : !contents string(range(args i n)*)
  frame->slots[5] /* temp__2 */ = create_closure(entry__html__define_tag_54, 0);
  // 119: -> i < n: !contents string(range(args i n)*)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__html__define_tag_57(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // i: 0
  // n: 1
  // contents: 2
  // args: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* i */
  frame->slots[1] = myself->closure.frame->slots[5]; /* n */
  frame->slots[2] = myself->closure.frame->slots[7]; /* contents */
  frame->slots[3] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: ... i == n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__html__define_tag_58;
}
static void cont__html__define_tag_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 120: ... : !contents args(i)
  frame->slots[5] /* temp__2 */ = create_closure(entry__html__define_tag_59, 0);
  // 120: -> i == n: !contents args(i)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 145: contents.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* contents */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__html__define_tag_62;
}
static void cont__html__define_tag_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 145: ... contents.is_a_string && name != "script"
  frame->slots[11] /* temp__3 */ = create_closure(entry__html__define_tag_63, 0);
  // 145: contents.is_defined && contents.is_a_string && name != "script"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__html__define_tag_70;
}
static void entry__html__define_tag_63(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // contents: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[7]; /* contents */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 145: ... contents.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* contents */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__html__define_tag_64;
}
static void cont__html__define_tag_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 145: ... name != "script"
  frame->slots[4] /* temp__3 */ = create_closure(entry__html__define_tag_65, 0);
  // 145: ... contents.is_a_string && name != "script"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__html__define_tag_69;
}
static void entry__html__define_tag_65(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 145: ... name != "script"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__7c1f5409013a62a3;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__html__define_tag_67;
}
static void cont__html__define_tag_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 145: ... name != "script"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__html__define_tag_68;
}
static void cont__html__define_tag_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 145: ... name != "script"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 145: ... contents.is_a_string && name != "script"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__html__define_tag_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 145: ... :
  // 146:   for_each split(contents "@nl;@nl;"): ($field)
  // 147:     $convert: (&line)
  // 148:       replace_all
  // 149:         &line
  // 150:         "<|>" = "<br>"
  // 151:         '<' = "&lt;"
  // 152:         "\*" = "*"
  // 153:         "\<" = "<"
  // 154:         "\[" = "["
  // ...
  frame->slots[12] /* temp__4 */ = create_closure(entry__html__define_tag_71, 0);
  // 183: :
  // 184:   emit_tag contents
  frame->slots[13] /* temp__5 */ = create_closure(entry__html__define_tag_140, 0);
  // 144: if
  // 145:   contents.is_defined && contents.is_a_string && name != "script":
  // 146:     for_each split(contents "@nl;@nl;"): ($field)
  // 147:       $convert: (&line)
  // 148:         replace_all
  // 149:           &line
  // 150:           "<|>" = "<br>"
  // 151:           '<' = "&lt;"
  // 152:           "\*" = "*"
  // 153:           "\<" = "<"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  arguments->slots[2] = frame->slots[13] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__define_tag_1(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // name: 0
  // mode: 1
  // tag_mode: 2
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* tag_mode */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* tag_mode */ = var.html__NORMAL;
  }
  //  99: ... : (args*)
  // 100:   $$i 1
  // 101:   $n length_of(args)
  // 102:   $$arg_str ""
  // 103:   do: (-> break)
  // 104:     forever:
  // 105:       if i > n break
  // 106:       $arg args(i)
  // 107:       unless arg.is_a_key_value_pair break
  // 108:       append
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__html__define_tag_2, -1);
  //  99: ->: (args*)
  // 100:   $$i 1
  // 101:   $n length_of(args)
  // 102:   $$arg_str ""
  // 103:   do: (-> break)
  // 104:     forever:
  // 105:       if i > n break
  // 106:       $arg args(i)
  // 107:       unless arg.is_a_key_value_pair break
  // 108:       append
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__html__HTTP_HEADER_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 238: write "
  // 239:   Content-type: text/html; charset=utf-8
  // 240:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c0902590ad1223f4;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__HTML_HEADER_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 242: ... writeln "<!doctype html>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__db8101d080cbfa33;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__ERROR_PAGE_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // details: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 251: ... P details
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* details */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__ERROR_PAGE_7(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // msg: 0
  // details: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* msg */
  frame->slots[1] = myself->closure.frame->slots[1]; /* details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 250: H1 msg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* msg */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__html__ERROR_PAGE_8;
}
static void cont__html__ERROR_PAGE_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 251: ... details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__html__ERROR_PAGE_9;
}
static void cont__html__ERROR_PAGE_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 251: ... : P details
  frame->slots[3] /* temp__2 */ = create_closure(entry__html__ERROR_PAGE_10, 0);
  // 251: if details.is_defined: P details
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__ERROR_PAGE_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // msg: 0
  // details: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* msg */
  frame->slots[1] = myself->closure.frame->slots[1]; /* details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 248: ... : TITLE msg
  frame->slots[2] /* temp__1 */ = create_closure(entry__html__ERROR_PAGE_5, 0);
  // 248: HEAD: TITLE msg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__HEAD();
  func = myself->type;
  frame->cont = cont__html__ERROR_PAGE_6;
}
static void entry__html__ERROR_PAGE_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // msg: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* msg */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 248: ... TITLE msg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* msg */;
  result_count = frame->caller_result_count;
  myself = get__TITLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__html__ERROR_PAGE_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 249: ... :
  // 250:   H1 msg
  // 251:   if details.is_defined: P details
  frame->slots[2] /* temp__1 */ = create_closure(entry__html__ERROR_PAGE_7, 0);
  // 249: HTML:
  // 250:   H1 msg
  // 251:   if details.is_defined: P details
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__HTML();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__ERROR_PAGE_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // msg: 0
  // details: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* details */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* details */ = undefined;
  }
  // 245: HTTP_HEADER
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__HTTP_HEADER();
  func = myself->type;
  frame->cont = cont__html__ERROR_PAGE_2;
}
static void cont__html__ERROR_PAGE_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 246: HTML_HEADER
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__HTML_HEADER();
  func = myself->type;
  frame->cont = cont__html__ERROR_PAGE_3;
}
static void cont__html__ERROR_PAGE_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 247: ... :
  // 248:   HEAD: TITLE msg
  // 249:   HTML:
  // 250:     H1 msg
  // 251:     if details.is_defined: P details
  frame->slots[2] /* temp__1 */ = create_closure(entry__html__ERROR_PAGE_4, 0);
  // 247: HTML:
  // 248:   HEAD: TITLE msg
  // 249:   HTML:
  // 250:     H1 msg
  // 251:     if details.is_defined: P details
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__HTML();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__DUMP_PAGE_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // msg: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* msg */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 266: H1 "dump"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a0aec0b5d087d49;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__html__DUMP_PAGE_9;
}
static void cont__html__DUMP_PAGE_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 267: PRE msg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* msg */;
  result_count = frame->caller_result_count;
  myself = get__PRE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__DUMP_PAGE_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // msg: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* msg */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 264: HEAD: TITLE "dump"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__html__DUMP_PAGE_5;
  result_count = 0;
  myself = get__HEAD();
  func = myself->type;
  frame->cont = cont__html__DUMP_PAGE_7;
}
static void entry__html__DUMP_PAGE_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 264: ... TITLE "dump"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a0aec0b5d087d49;
  result_count = frame->caller_result_count;
  myself = get__TITLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__html__DUMP_PAGE_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 265: ... :
  // 266:   H1 "dump"
  // 267:   PRE msg
  frame->slots[1] /* temp__1 */ = create_closure(entry__html__DUMP_PAGE_8, 0);
  // 265: HTML:
  // 266:   H1 "dump"
  // 267:   PRE msg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__HTML();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__html__DUMP_PAGE_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // msg: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 261: HTTP_HEADER
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__HTTP_HEADER();
  func = myself->type;
  frame->cont = cont__html__DUMP_PAGE_2;
}
static void cont__html__DUMP_PAGE_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 262: HTML_HEADER
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__HTML_HEADER();
  func = myself->type;
  frame->cont = cont__html__DUMP_PAGE_3;
}
static void cont__html__DUMP_PAGE_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 263: ... :
  // 264:   HEAD: TITLE "dump"
  // 265:   HTML:
  // 266:     H1 "dump"
  // 267:     PRE msg
  frame->slots[1] /* temp__1 */ = create_closure(entry__html__DUMP_PAGE_4, 0);
  // 263: HTML:
  // 264:   HEAD: TITLE "dump"
  // 265:   HTML:
  // 266:     H1 "dump"
  // 267:     PRE msg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__HTML();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__system__export__html(void) {
  var._convert_from_percent_encoding = collect_node(var._convert_from_percent_encoding);
  var.html__SIMPLE = collect_node(var.html__SIMPLE);
  var.html__SINGLE_LINE = collect_node(var.html__SINGLE_LINE);
  var.html__MULTI_LINE = collect_node(var.html__MULTI_LINE);
  var.html__MULTI_PARAGRAPH = collect_node(var.html__MULTI_PARAGRAPH);
  var.html__NORMAL = collect_node(var.html__NORMAL);
  var.html__VOID = collect_node(var.html__VOID);
  var.html__FOREIGN = collect_node(var.html__FOREIGN);
  var.html__TEXT = collect_node(var.html__TEXT);
  var._hex_digit_value = collect_node(var._hex_digit_value);
  var._hex_digit = collect_node(var._hex_digit);
  var.html__define_tag = collect_node(var.html__define_tag);
  var.html__HTML = collect_node(var.html__HTML);
  var.html__HEAD = collect_node(var.html__HEAD);
  var.html__META = collect_node(var.html__META);
  var.html__TITLE = collect_node(var.html__TITLE);
  var.html__STYLE = collect_node(var.html__STYLE);
  var.html__SCRIPT = collect_node(var.html__SCRIPT);
  var.html__BODY = collect_node(var.html__BODY);
  var.html__A = collect_node(var.html__A);
  var.html__H1 = collect_node(var.html__H1);
  var.html__H2 = collect_node(var.html__H2);
  var.html__H3 = collect_node(var.html__H3);
  var.html__H4 = collect_node(var.html__H4);
  var.html__H5 = collect_node(var.html__H5);
  var.html__H6 = collect_node(var.html__H6);
  var.html__DIV = collect_node(var.html__DIV);
  var.html__P = collect_node(var.html__P);
  var.html__SPAN = collect_node(var.html__SPAN);
  var.html__HR = collect_node(var.html__HR);
  var.html__BR = collect_node(var.html__BR);
  var.html__NOBR = collect_node(var.html__NOBR);
  var.html__OL = collect_node(var.html__OL);
  var.html__UL = collect_node(var.html__UL);
  var.html__LI = collect_node(var.html__LI);
  var.html__TABLE = collect_node(var.html__TABLE);
  var.html__TR = collect_node(var.html__TR);
  var.html__TH = collect_node(var.html__TH);
  var.html__TD = collect_node(var.html__TD);
  var.html__DL = collect_node(var.html__DL);
  var.html__DT = collect_node(var.html__DT);
  var.html__DD = collect_node(var.html__DD);
  var.html__FORM = collect_node(var.html__FORM);
  var.html__FIELDSET = collect_node(var.html__FIELDSET);
  var.html__LEGEND = collect_node(var.html__LEGEND);
  var.html__INPUT = collect_node(var.html__INPUT);
  var.html__TEXTAREA = collect_node(var.html__TEXTAREA);
  var.html__SELECT = collect_node(var.html__SELECT);
  var.html__OPTION = collect_node(var.html__OPTION);
  var.html__BUTTON = collect_node(var.html__BUTTON);
  var.html__CODE = collect_node(var.html__CODE);
  var.html__PRE = collect_node(var.html__PRE);
  var.html__B = collect_node(var.html__B);
  var.html__EM = collect_node(var.html__EM);
  var.html__CENTER = collect_node(var.html__CENTER);
  var.html__LINK = collect_node(var.html__LINK);
  var.html__IMG = collect_node(var.html__IMG);
  var.html__FIGURE = collect_node(var.html__FIGURE);
  var.html__FIGCAPTION = collect_node(var.html__FIGCAPTION);
  var.html__VIDEO = collect_node(var.html__VIDEO);
  var.html__SOURCE = collect_node(var.html__SOURCE);
  var.html__CANVAS = collect_node(var.html__CANVAS);
  var.html__HTTP_HEADER = collect_node(var.html__HTTP_HEADER);
  var.html__HTML_HEADER = collect_node(var.html__HTML_HEADER);
  var.html__ERROR_PAGE = collect_node(var.html__ERROR_PAGE);
  var.html__DUMP_PAGE = collect_node(var.html__DUMP_PAGE);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__system__export__html(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_namespace("builtin");
  define_namespace("html");
}

static int already_run_phase_2 = false;

EXPORT void phase_2__system__export__html(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("system__export__html");
  character__57 = from_uchar32(57);
  character__65 = from_uchar32(65);
  character__10 = from_uchar32(10);
  number__3 = from_uint32(3U);
  character__70 = from_uchar32(70);
  character__48 = from_uchar32(48);
  character__102 = from_uchar32(102);
  character__60 = from_uchar32(60);
  character__95 = from_uchar32(95);
  number__16 = from_uint32(16U);
  character__40 = from_uchar32(40);
  character__34 = from_uchar32(34);
  character__93 = from_uchar32(93);
  character__91 = from_uchar32(91);
  character__41 = from_uchar32(41);
  number__1 = from_uint32(1U);
  character__97 = from_uchar32(97);
  number__2 = from_uint32(2U);
  character__42 = from_uchar32(42);
  number__10 = from_uint32(10U);
  register_polymorphic_function("_system__export__html::convert_from_percent_encoding", &poly_idx__convert_from_percent_encoding);
  unique__html__SIMPLE = register_unique_item("html__SIMPLE");
  unique__html__SINGLE_LINE = register_unique_item("html__SINGLE_LINE");
  unique__html__MULTI_LINE = register_unique_item("html__MULTI_LINE");
  unique__html__MULTI_PARAGRAPH = register_unique_item("html__MULTI_PARAGRAPH");
  unique__html__NORMAL = register_unique_item("html__NORMAL");
  unique__html__VOID = register_unique_item("html__VOID");
  unique__html__FOREIGN = register_unique_item("html__FOREIGN");
  func__html__emit_2 = create_function(entry__html__emit_2, 1);
  func__html__emit_1 = create_function(entry__html__emit_1, -1);
  func__html__encode_1 = create_function(entry__html__encode_1, 3);
  func__html__TEXT_1 = create_function(entry__html__TEXT_1, -1);
  string__7fe91a650e32a4f3 = from_latin_1_string("invalid hex digit", 17);
  func__hex_digit_value_31 = create_function(entry__hex_digit_value_31, 0);
  func__hex_digit_value_1 = create_function(entry__hex_digit_value_1, 1);
  string__578a5af303e9cca = from_latin_1_string("+", 1);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  string__578a5af303e9cc4 = from_latin_1_string("%", 1);
  func__types__string__convert_from_percent_encoding_8 = create_function(entry__types__string__convert_from_percent_encoding_8, 1);
  func__types__string__convert_from_percent_encoding_1 = create_function(entry__types__string__convert_from_percent_encoding_1, 1);
  string__578a5af303e9cdd = from_latin_1_string("<", 1);
  string__578a5af303e9cdf = from_latin_1_string(">", 1);
  func__html__define_tag_11 = create_function(entry__html__define_tag_11, 0);
  string__2d7981f4e6e82bea = from_latin_1_string("</", 2);
  string__fa737c15fc96be3 = from_latin_1_string("></", 3);
  func__html__define_tag_22 = create_function(entry__html__define_tag_22, 0);
  string__2d7981f4e6702bfb = from_latin_1_string("/>", 2);
  func__html__define_tag_23 = create_function(entry__html__define_tag_23, 0);
  func__html__define_tag_27 = create_function(entry__html__define_tag_27, 0);
  string__578a5af303e9ccc = from_latin_1_string("-", 1);
  string__721f55a3811b42ec = from_latin_1_string("&quot;", 6);
  string__2d7981f4e6e02be7 = from_latin_1_string("=\042", 2);
  string__7c1f5409013a62a3 = from_latin_1_string("script", 6);
  string__2d7981f4e7582bcf = from_latin_1_string(
    "\n"
    "\n",
    2);
  string__fa737415dc96bf2 = from_latin_1_string("<|>", 3);
  string__ba0ae9cb5df07d07 = from_latin_1_string("<br>", 4);
  string__8e0aea4b5dc07d02 = from_latin_1_string("&lt;", 4);
  string__2d7981f4e5e82bef = from_latin_1_string("\134*", 2);
  string__578a5af303e9ccb = from_latin_1_string("*", 1);
  string__2d7981f4e5e82bf9 = from_latin_1_string("\134<", 2);
  string__2d7981f4e5e82b9e = from_latin_1_string("\134[", 2);
  string__578a5af303e9cba = from_latin_1_string("[", 1);
  string__fa737415d616bf2 = from_latin_1_string("<i>", 3);
  string__ba0afa8b5d287d07 = from_latin_1_string("</i>", 4);
  func__html__define_tag_93 = create_function(entry__html__define_tag_93, 1);
  string__2d7981f4e6582bef = from_latin_1_string("**", 2);
  string__fa737415d396bf2 = from_latin_1_string("<b>", 3);
  string__ba0afa8b5d707d07 = from_latin_1_string("</b>", 4);
  func__html__define_tag_105 = create_function(entry__html__define_tag_105, 1);
  string__65b02728dcea54a7 = from_latin_1_string("<a href=\042", 9);
  string__2d7981f4e6182bfb = from_latin_1_string("\042>", 2);
  string__ba0afa8b5d687d07 = from_latin_1_string("</a>", 4);
  func__html__define_tag_119 = create_function(entry__html__define_tag_119, 1);
  func__html__define_tag_75 = create_function(entry__html__define_tag_75, 1);
  string__2d7981f4e6582be5 = from_latin_1_string("* ", 2);
  string__d6c0aed004987b9e = from_latin_1_string("<ul><li>", 8);
  string__d45aee43eaadd069 = from_latin_1_string("</ul>", 5);
  func__html__define_tag_1 = create_function(entry__html__define_tag_1, -1);
  string__c0902590ad1223f4 = from_latin_1_string(
    "Content-type: text/html; charset=utf-8\n"
    "\n",
    40);
  func__html__HTTP_HEADER_1 = create_function(entry__html__HTTP_HEADER_1, 0);
  string__db8101d080cbfa33 = from_latin_1_string("<!doctype html>", 15);
  func__html__HTML_HEADER_1 = create_function(entry__html__HTML_HEADER_1, 0);
  func__html__ERROR_PAGE_1 = create_function(entry__html__ERROR_PAGE_1, -1);
  string__a0aec0b5d087d49 = from_latin_1_string("dump", 4);
  func__html__DUMP_PAGE_5 = create_function(entry__html__DUMP_PAGE_5, 0);
  func__html__DUMP_PAGE_1 = create_function(entry__html__DUMP_PAGE_1, 1);
  string__120aec4b5d087d55 = from_latin_1_string("html", 4);
  string__120ae80b5d687d5d = from_latin_1_string("head", 4);
  string__180ae80b5dc07d58 = from_latin_1_string("meta", 4);
  string__585aee03eaa95032 = from_latin_1_string("title", 5);
  string__625aed43eaa92032 = from_latin_1_string("style", 5);
  string__60aea8b5d407d40 = from_latin_1_string("body", 4);
  string__578a5af303e9c80 = from_latin_1_string("a", 1);
  string__2d7981f4e4482bf4 = from_latin_1_string("h1", 2);
  string__2d7981f4e4482bf7 = from_latin_1_string("h2", 2);
  string__2d7981f4e4482bf6 = from_latin_1_string("h3", 2);
  string__2d7981f4e4482bf1 = from_latin_1_string("h4", 2);
  string__2d7981f4e4482bf0 = from_latin_1_string("h5", 2);
  string__2d7981f4e4482bf3 = from_latin_1_string("h6", 2);
  string__fa721415d616bba = from_latin_1_string("div", 3);
  string__578a5af303e9c91 = from_latin_1_string("p", 1);
  string__240aed4b5d687d57 = from_latin_1_string("span", 4);
  string__2d7981f4e4482bb7 = from_latin_1_string("hr", 2);
  string__2d7981f4e4182bb7 = from_latin_1_string("br", 2);
  string__1e0aea8b5d707d4b = from_latin_1_string("nobr", 4);
  string__2d7981f4e4702ba9 = from_latin_1_string("ol", 2);
  string__2d7981f4e4a02ba9 = from_latin_1_string("ul", 2);
  string__2d7981f4e4682bac = from_latin_1_string("li", 2);
  string__485aeb83eaa95032 = from_latin_1_string("table", 5);
  string__2d7981f4e4a82bb7 = from_latin_1_string("tr", 2);
  string__2d7981f4e4a82bad = from_latin_1_string("th", 2);
  string__2d7981f4e4a82ba1 = from_latin_1_string("td", 2);
  string__2d7981f4e4282ba9 = from_latin_1_string("dl", 2);
  string__2d7981f4e4282bb1 = from_latin_1_string("dt", 2);
  string__2d7981f4e4282ba1 = from_latin_1_string("dd", 2);
  string__e0aea8b5df07d54 = from_latin_1_string("form", 4);
  string__66b0a91484fd5094 = from_latin_1_string("fieldset", 8);
  string__561f570681ca02b3 = from_latin_1_string("legend", 6);
  string__565aef03ea608023 = from_latin_1_string("input", 5);
  string__6c80a95a04fcd2c1 = from_latin_1_string("textarea", 8);
  string__401f570901a202a3 = from_latin_1_string("select", 6);
  string__701f540701c352b9 = from_latin_1_string("option", 6);
  string__701f534181c302b9 = from_latin_1_string("button", 6);
  string__40aea8b5d407d5c = from_latin_1_string("code", 4);
  string__fa724415db96ba9 = from_latin_1_string("pre", 3);
  string__578a5af303e9c83 = from_latin_1_string("b", 1);
  string__2d7981f4e4202ba8 = from_latin_1_string("em", 2);
  string__441f5341019202a5 = from_latin_1_string("center", 6);
  string__1a0aeb0b5d107d52 = from_latin_1_string("link", 4);
  string__fa722015d416bab = from_latin_1_string("img", 3);
  string__561f5303812ac2b2 = from_latin_1_string("figure", 6);
  string__1d68225b2f52750f = from_latin_1_string("figcaption", 10);
  string__585aea03eae17038 = from_latin_1_string("video", 5);
  string__721f52c901a2a2b2 = from_latin_1_string("source", 6);
  string__441f53c101b242a4 = from_latin_1_string("canvas", 6);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__system__export__html(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("system__export__html");
  set_used_namespaces(used_namespaces);
  assign_value(&var.html__SIMPLE, unique__html__SIMPLE);
  define_single_assign_static("html", "SIMPLE", get__html__SIMPLE, &var.html__SIMPLE);
  assign_value(&var.html__SINGLE_LINE, unique__html__SINGLE_LINE);
  define_single_assign_static("html", "SINGLE_LINE", get__html__SINGLE_LINE, &var.html__SINGLE_LINE);
  assign_value(&var.html__MULTI_LINE, unique__html__MULTI_LINE);
  define_single_assign_static("html", "MULTI_LINE", get__html__MULTI_LINE, &var.html__MULTI_LINE);
  assign_value(&var.html__MULTI_PARAGRAPH, unique__html__MULTI_PARAGRAPH);
  define_single_assign_static("html", "MULTI_PARAGRAPH", get__html__MULTI_PARAGRAPH, &var.html__MULTI_PARAGRAPH);
  assign_value(&var.html__NORMAL, unique__html__NORMAL);
  define_single_assign_static("html", "NORMAL", get__html__NORMAL, &var.html__NORMAL);
  assign_value(&var.html__VOID, unique__html__VOID);
  define_single_assign_static("html", "VOID", get__html__VOID, &var.html__VOID);
  assign_value(&var.html__FOREIGN, unique__html__FOREIGN);
  define_single_assign_static("html", "FOREIGN", get__html__FOREIGN, &var.html__FOREIGN);
  define_single_assign_dynamic("html", "emit", get__html__emit, define__html__emit, &dyna_idx__html__emit);
  define_single_assign_dynamic("html", "encode", get__html__encode, define__html__encode, &dyna_idx__html__encode);
  define_single_assign_static("html", "TEXT", get__html__TEXT, &var.html__TEXT);
  var._hex_digit = create_future();
  define_single_assign_static("html", "define_tag", get__html__define_tag, &var.html__define_tag);
  define_single_assign_static("html", "HTML", get__html__HTML, &var.html__HTML);
  define_single_assign_static("html", "HEAD", get__html__HEAD, &var.html__HEAD);
  define_single_assign_static("html", "META", get__html__META, &var.html__META);
  define_single_assign_static("html", "TITLE", get__html__TITLE, &var.html__TITLE);
  define_single_assign_static("html", "STYLE", get__html__STYLE, &var.html__STYLE);
  define_single_assign_static("html", "SCRIPT", get__html__SCRIPT, &var.html__SCRIPT);
  define_single_assign_static("html", "BODY", get__html__BODY, &var.html__BODY);
  define_single_assign_static("html", "A", get__html__A, &var.html__A);
  define_single_assign_static("html", "H1", get__html__H1, &var.html__H1);
  define_single_assign_static("html", "H2", get__html__H2, &var.html__H2);
  define_single_assign_static("html", "H3", get__html__H3, &var.html__H3);
  define_single_assign_static("html", "H4", get__html__H4, &var.html__H4);
  define_single_assign_static("html", "H5", get__html__H5, &var.html__H5);
  define_single_assign_static("html", "H6", get__html__H6, &var.html__H6);
  define_single_assign_static("html", "DIV", get__html__DIV, &var.html__DIV);
  define_single_assign_static("html", "P", get__html__P, &var.html__P);
  define_single_assign_static("html", "SPAN", get__html__SPAN, &var.html__SPAN);
  define_single_assign_static("html", "HR", get__html__HR, &var.html__HR);
  define_single_assign_static("html", "BR", get__html__BR, &var.html__BR);
  define_single_assign_static("html", "NOBR", get__html__NOBR, &var.html__NOBR);
  define_single_assign_static("html", "OL", get__html__OL, &var.html__OL);
  define_single_assign_static("html", "UL", get__html__UL, &var.html__UL);
  define_single_assign_static("html", "LI", get__html__LI, &var.html__LI);
  define_single_assign_static("html", "TABLE", get__html__TABLE, &var.html__TABLE);
  define_single_assign_static("html", "TR", get__html__TR, &var.html__TR);
  define_single_assign_static("html", "TH", get__html__TH, &var.html__TH);
  define_single_assign_static("html", "TD", get__html__TD, &var.html__TD);
  define_single_assign_static("html", "DL", get__html__DL, &var.html__DL);
  define_single_assign_static("html", "DT", get__html__DT, &var.html__DT);
  define_single_assign_static("html", "DD", get__html__DD, &var.html__DD);
  define_single_assign_static("html", "FORM", get__html__FORM, &var.html__FORM);
  define_single_assign_static("html", "FIELDSET", get__html__FIELDSET, &var.html__FIELDSET);
  define_single_assign_static("html", "LEGEND", get__html__LEGEND, &var.html__LEGEND);
  define_single_assign_static("html", "INPUT", get__html__INPUT, &var.html__INPUT);
  define_single_assign_static("html", "TEXTAREA", get__html__TEXTAREA, &var.html__TEXTAREA);
  define_single_assign_static("html", "SELECT", get__html__SELECT, &var.html__SELECT);
  define_single_assign_static("html", "OPTION", get__html__OPTION, &var.html__OPTION);
  define_single_assign_static("html", "BUTTON", get__html__BUTTON, &var.html__BUTTON);
  define_single_assign_static("html", "CODE", get__html__CODE, &var.html__CODE);
  define_single_assign_static("html", "PRE", get__html__PRE, &var.html__PRE);
  define_single_assign_static("html", "B", get__html__B, &var.html__B);
  define_single_assign_static("html", "EM", get__html__EM, &var.html__EM);
  define_single_assign_static("html", "CENTER", get__html__CENTER, &var.html__CENTER);
  define_single_assign_static("html", "LINK", get__html__LINK, &var.html__LINK);
  define_single_assign_static("html", "IMG", get__html__IMG, &var.html__IMG);
  define_single_assign_static("html", "FIGURE", get__html__FIGURE, &var.html__FIGURE);
  define_single_assign_static("html", "FIGCAPTION", get__html__FIGCAPTION, &var.html__FIGCAPTION);
  define_single_assign_static("html", "VIDEO", get__html__VIDEO, &var.html__VIDEO);
  define_single_assign_static("html", "SOURCE", get__html__SOURCE, &var.html__SOURCE);
  define_single_assign_static("html", "CANVAS", get__html__CANVAS, &var.html__CANVAS);
  define_single_assign_static("html", "HTTP_HEADER", get__html__HTTP_HEADER, &var.html__HTTP_HEADER);
  define_single_assign_static("html", "HTML_HEADER", get__html__HTML_HEADER, &var.html__HTML_HEADER);
  define_single_assign_static("html", "ERROR_PAGE", get__html__ERROR_PAGE, &var.html__ERROR_PAGE);
  define_single_assign_static("html", "DUMP_PAGE", get__html__DUMP_PAGE, &var.html__DUMP_PAGE);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__system__export__html(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("system__export__html");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "ANY_CHARACTER", &get__ANY_CHARACTER, &get_value_or_future__ANY_CHARACTER);
  use_read_only(NULL, "FOREIGN", &get__FOREIGN, &get_value_or_future__FOREIGN);
  use_read_only(NULL, "H1", &get__H1, &get_value_or_future__H1);
  use_read_only(NULL, "HEAD", &get__HEAD, &get_value_or_future__HEAD);
  use_read_only(NULL, "HTML", &get__HTML, &get_value_or_future__HTML);
  use_read_only(NULL, "HTML_HEADER", &get__HTML_HEADER, &get_value_or_future__HTML_HEADER);
  use_read_only(NULL, "HTTP_HEADER", &get__HTTP_HEADER, &get_value_or_future__HTTP_HEADER);
  use_read_only(NULL, "MULTI_LINE", &get__MULTI_LINE, &get_value_or_future__MULTI_LINE);
  use_read_only(NULL, "MULTI_PARAGRAPH", &get__MULTI_PARAGRAPH, &get_value_or_future__MULTI_PARAGRAPH);
  use_read_only(NULL, "P", &get__P, &get_value_or_future__P);
  use_read_only(NULL, "PRE", &get__PRE, &get_value_or_future__PRE);
  use_read_only(NULL, "SIMPLE", &get__SIMPLE, &get_value_or_future__SIMPLE);
  use_read_only(NULL, "SINGLE_LINE", &get__SINGLE_LINE, &get_value_or_future__SINGLE_LINE);
  use_read_only(NULL, "TITLE", &get__TITLE, &get_value_or_future__TITLE);
  use_read_only(NULL, "VOID", &get__VOID, &get_value_or_future__VOID);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "between", &get__between, &get_value_or_future__between);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "character", &get__character, &get_value_or_future__character);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "define_tag", &get__define_tag, &get_value_or_future__define_tag);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "emit", &get__emit, &get_value_or_future__emit);
  use_read_only(NULL, "encode", &get__encode, &get_value_or_future__encode);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_a_function", &get__is_a_function, &get_value_or_future__is_a_function);
  use_read_only(NULL, "is_a_key_value_pair", &get__is_a_key_value_pair, &get_value_or_future__is_a_key_value_pair);
  use_read_only(NULL, "is_a_string", &get__is_a_string, &get_value_or_future__is_a_string);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "key_of", &get__key_of, &get_value_or_future__key_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "many", &get__many, &get_value_or_future__many);
  use_read_only(NULL, "not_followed_by", &get__not_followed_by, &get_value_or_future__not_followed_by);
  use_read_only(NULL, "raise", &get__raise, &get_value_or_future__raise);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_read_only(NULL, "sequence", &get__sequence, &get_value_or_future__sequence);
  use_read_only(NULL, "split", &get__split, &get_value_or_future__split);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only("std", "times", &get__std__times, &get_value_or_future__std__times);
  use_read_only("std", "value_range", &get__std__value_range, &get_value_or_future__std__value_range);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_read_only("types", "string", &get__types__string, &get_value_or_future__types__string);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "value_of", &get__value_of, &get_value_or_future__value_of);
  use_read_only(NULL, "write", &get__write, &get_value_or_future__write);
  use_read_only(NULL, "writeln", &get__writeln, &get_value_or_future__writeln);
  define_method("types", "string", poly_idx__convert_from_percent_encoding, func__types__string__convert_from_percent_encoding_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__system__export__html(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var._convert_from_percent_encoding, create_function(type__convert_from_percent_encoding, -1));
  define__html__emit(func__html__emit_1);
  define__html__encode(func__html__encode_1);
  assign_variable(&var.html__TEXT, &func__html__TEXT_1);
  assign_variable(&var._hex_digit_value, &func__hex_digit_value_1);
  assign_variable(&var.html__define_tag, &func__html__define_tag_1);
  assign_variable(&var.html__HTTP_HEADER, &func__html__HTTP_HEADER_1);
  assign_variable(&var.html__HTML_HEADER, &func__html__HTML_HEADER_1);
  assign_variable(&var.html__ERROR_PAGE, &func__html__ERROR_PAGE_1);
  assign_variable(&var.html__DUMP_PAGE, &func__html__DUMP_PAGE_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__system__export__html(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__system__export__html);
}
