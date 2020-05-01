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
typedef void (*NODE_SETTER)(NODE *);
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
IMPORT void *copy(const void *buf, long size);
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
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
REGISTER int argument_count ASM("ebx");
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_future(void);
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *empty_string;
IMPORT NODE *undefined;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_cell(void);
IMPORT void allocate_arguments(void);
IMPORT void too_few_arguments_error(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *create_continuation_with_exit(FUNC exit_func);
IMPORT void optional_item(NODE *item);
IMPORT void continuation_type_function(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_used_namespaces(const char **namespaces);
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
IMPORT void use_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
);
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__END_OF_TEXT;
static NODE_GETTER get_value_or_future__END_OF_TEXT;
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__alt;
static NODE_GETTER get_value_or_future__alt;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static int poly_idx__before;
static NODE_GETTER get__before;
static int poly_idx__behind;
static NODE_GETTER get__behind;
static int poly_idx__between;
static NODE_GETTER get__between;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static int poly_idx__contains;
static NODE_GETTER get__contains;
static NODE_GETTER get__div;
static NODE_GETTER get_value_or_future__div;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__do_while;
static NODE_GETTER get_value_or_future__do_while;
static int poly_idx__dup;
static NODE_GETTER get__dup;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__for_each_line;
static NODE_GETTER get_value_or_future__for_each_line;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static int poly_idx__from;
static NODE_GETTER get__from;
static NODE_GETTER get__from_down_to;
static NODE_GETTER get_value_or_future__from_down_to;
static NODE_GETTER get__from_to;
static NODE_GETTER get_value_or_future__from_to;
static NODE_GETTER get__grammar__current_node;
static NODE_SETTER set__grammar__current_node;
static NODE_SETTER define__grammar__current_node;
static int poly_idx__grammar__match;
static NODE_GETTER get__grammar__match;
static NODE_GETTER get__grammar__search;
static NODE_GETTER get_value_or_future__grammar__search;
static NODE_GETTER get__has_minimum_length;
static NODE_GETTER get_value_or_future__has_minimum_length;
static int poly_idx__has_prefix;
static NODE_GETTER get__has_prefix;
static int poly_idx__has_suffix;
static NODE_GETTER get__has_suffix;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_a_digit;
static NODE_GETTER get_value_or_future__is_a_digit;
static NODE_GETTER get__is_a_letter_character;
static NODE_GETTER get_value_or_future__is_a_letter_character;
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
static NODE_GETTER get__map;
static NODE_GETTER get_value_or_future__map;
static int poly_idx__match;
static NODE_GETTER get__match;
static int poly_idx__match_character;
static NODE_GETTER get__match_character;
static int poly_idx__matches;
static NODE_GETTER get__matches;
static NODE_GETTER get__min;
static NODE_GETTER get_value_or_future__min;
static NODE_GETTER get__minus;
static NODE_GETTER get_value_or_future__minus;
static int poly_idx__new_empty_collection;
static NODE_GETTER get__new_empty_collection;
static NODE_GETTER get__not_followed_by;
static NODE_GETTER get_value_or_future__not_followed_by;
static int poly_idx__numerically_less;
static NODE_GETTER get__numerically_less;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static NODE_GETTER get__parse_integer;
static NODE_GETTER get_value_or_future__parse_integer;
static int poly_idx__parse_number;
static NODE_GETTER get__parse_number;
static NODE_GETTER get__parse_real;
static NODE_GETTER get_value_or_future__parse_real;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static int poly_idx__put;
static NODE_GETTER get__put;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static int poly_idx__search;
static NODE_GETTER get__search;
static int poly_idx__search_character;
static NODE_GETTER get__search_character;
static NODE_GETTER get__spaces;
static NODE_GETTER get_value_or_future__spaces;
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
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__sequence;
static NODE_GETTER get_value_or_future__std__sequence;
static NODE_GETTER get__std__times;
static NODE_GETTER get_value_or_future__std__times;
static NODE_GETTER get__std__write;
static NODE_SETTER define__std__write;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__table;
static NODE_GETTER get_value_or_future__table;
static int poly_idx__to_integer;
static NODE_GETTER get__to_integer;
static int poly_idx__to_list;
static NODE_GETTER get__to_list;
static int poly_idx__to_lower_case;
static NODE_GETTER get__to_lower_case;
static int poly_idx__to_number;
static NODE_GETTER get__to_number;
static int poly_idx__to_real;
static NODE_GETTER get__to_real;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static int poly_idx__to_title_case;
static NODE_GETTER get__to_title_case;
static int poly_idx__to_upper_case;
static NODE_GETTER get__to_upper_case;
static NODE_GETTER get__trim;
static NODE_GETTER get_value_or_future__trim;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static int poly_idx__truncate_before;
static NODE_GETTER get__truncate_before;
static int poly_idx__truncate_behind;
static NODE_GETTER get__truncate_behind;
static int poly_idx__truncate_from;
static NODE_GETTER get__truncate_from;
static int poly_idx__truncate_until;
static NODE_GETTER get__truncate_until;
static NODE_GETTER get__types__grammar_node;
static NODE_GETTER get_value_or_future__types__grammar_node;
static NODE_GETTER get__types__octet_string;
static NODE_GETTER get_value_or_future__types__octet_string;
static NODE_GETTER get__types__quad_octet_string;
static NODE_GETTER get_value_or_future__types__quad_octet_string;
static NODE_GETTER get__types__string;
static NODE_GETTER get_value_or_future__types__string;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static int poly_idx__until;
static NODE_GETTER get__until;
static NODE_GETTER get__value_of;
static NODE_GETTER get_value_or_future__value_of;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static int poly_idx__without_prefix;
static NODE_GETTER get__without_prefix;
static int poly_idx__without_suffix;
static NODE_GETTER get__without_suffix;
static int poly_idx__write_to;
static NODE_GETTER get__write_to;
static struct {
  NODE *_umlaut_conversions;
  NODE *_eighty_spaces;
  NODE *std__string;
  NODE *std__pad_left;
  NODE *std__pad_right;
  NODE *std__truncate;
  NODE *std__pad_or_truncate;
  NODE *std__trim;
  NODE *std__normalize;
  NODE *std__split;
  NODE *std__join;
  NODE *std__count_occurrences;
  NODE *std__replace_umlauts;
  NODE *std__replace_all;
  NODE *std__delete_all;
  NODE *std__spaces;
  NODE *std__indented;
  NODE *std__for_each_line;
  NODE *std__collect_output;
} var;
static const char *var_names[] = {
  "umlaut_conversions",
  "eighty_spaces"
};
static NODE *func__types__string__to_integer_1;
static void entry__types__string__to_integer_1(void);
static FRAME_INFO frame__types__string__to_integer_1 = {3, {"self", "return", "value"}};
static void cont__types__string__to_integer_2(void);
static void cont__types__string__to_integer_3(void);
static void cont__types__string__to_integer_4(void);
static NODE *func__types__string__to_integer_5;
static void entry__types__string__to_integer_5(void);
static FRAME_INFO frame__types__string__to_integer_5 = {1, {"return"}};
static void cont__types__string__to_integer_6(void);
static NODE *func__types__string__to_real_1;
static void entry__types__string__to_real_1(void);
static FRAME_INFO frame__types__string__to_real_1 = {3, {"self", "return", "value"}};
static void cont__types__string__to_real_2(void);
static void cont__types__string__to_real_3(void);
static void cont__types__string__to_real_4(void);
static NODE *func__types__string__to_real_5;
static void entry__types__string__to_real_5(void);
static FRAME_INFO frame__types__string__to_real_5 = {1, {"return"}};
static void cont__types__string__to_real_6(void);
static NODE *func__types__string__parse_number_1;
static void entry__types__string__parse_number_1(void);
static FRAME_INFO frame__types__string__parse_number_1 = {3, {"self", "i", "n"}};
static void cont__types__string__parse_number_2(void);
static void cont__types__string__parse_number_3(void);
static void cont__types__string__parse_number_4(void);
static NODE *func__types__string__parse_number_5;
static void entry__types__string__parse_number_5(void);
static FRAME_INFO frame__types__string__parse_number_5 = {1, {"i"}};
static void cont__types__string__parse_number_6(void);
static void cont__types__string__parse_number_7(void);
static NODE *func__types__string__parse_number_8;
static void entry__types__string__parse_number_8(void);
static FRAME_INFO frame__types__string__parse_number_8 = {3, {"n", "i", "self"}};
static void cont__types__string__parse_number_9(void);
static void cont__types__string__parse_number_10(void);
static NODE *func__types__string__parse_number_11;
static void entry__types__string__parse_number_11(void);
static FRAME_INFO frame__types__string__parse_number_11 = {2, {"self", "i"}};
static void cont__types__string__parse_number_12(void);
static void cont__types__string__parse_number_13(void);
static void cont__types__string__parse_number_14(void);
static NODE *func__types__string__parse_number_15;
static void entry__types__string__parse_number_15(void);
static FRAME_INFO frame__types__string__parse_number_15 = {1, {"i"}};
static void cont__types__string__parse_number_16(void);
static void cont__types__string__parse_number_17(void);
static void cont__types__string__parse_number_18(void);
static void cont__types__string__parse_number_19(void);
static NODE *func__types__string__parse_number_20;
static void entry__types__string__parse_number_20(void);
static FRAME_INFO frame__types__string__parse_number_20 = {2, {"self", "i"}};
static void cont__types__string__parse_number_21(void);
static void cont__types__string__parse_number_22(void);
static void cont__types__string__parse_number_23(void);
static NODE *func__types__string__parse_number_24;
static void entry__types__string__parse_number_24(void);
static FRAME_INFO frame__types__string__parse_number_24 = {1, {"self"}};
static NODE *func__types__string__parse_number_25;
static void entry__types__string__parse_number_25(void);
static FRAME_INFO frame__types__string__parse_number_25 = {1, {"self"}};
static NODE *func__types__string__to_number_1;
static void entry__types__string__to_number_1(void);
static FRAME_INFO frame__types__string__to_number_1 = {3, {"self", "return", "value"}};
static void cont__types__string__to_number_2(void);
static void cont__types__string__to_number_3(void);
static void cont__types__string__to_number_4(void);
static NODE *func__types__string__to_number_5;
static void entry__types__string__to_number_5(void);
static FRAME_INFO frame__types__string__to_number_5 = {1, {"return"}};
static void cont__types__string__to_number_6(void);
static NODE *func__types__string__put_1;
static void entry__types__string__put_1(void);
static FRAME_INFO frame__types__string__put_1 = {2, {"self", "chr"}};
static void cont__types__string__put_2(void);
static void cont__types__string__put_3(void);
static NODE *func__types__string__write_to_1;
static void entry__types__string__write_to_1(void);
static FRAME_INFO frame__types__string__write_to_1 = {2, {"self", "args"}};
static NODE *func__types__string__write_to_2;
static void entry__types__string__write_to_2(void);
static FRAME_INFO frame__types__string__write_to_2 = {2, {"arg", "self"}};
static void cont__types__string__write_to_3(void);
static void cont__types__string__write_to_4(void);
static void cont__types__string__write_to_5(void);
static NODE *func__types__string__numerically_less_1;
static void entry__types__string__numerically_less_1(void);
static FRAME_INFO frame__types__string__numerically_less_1 = {5, {"left", "right", "return", "left_len", "right_len"}};
static void cont__types__string__numerically_less_2(void);
static void cont__types__string__numerically_less_3(void);
static void cont__types__string__numerically_less_4(void);
static NODE *func__types__string__numerically_less_5;
static void entry__types__string__numerically_less_5(void);
static FRAME_INFO frame__types__string__numerically_less_5 = {8, {"i", "left", "right", "left_len", "right_len", "return", "left_chr", "right_chr"}};
static void cont__types__string__numerically_less_6(void);
static void cont__types__string__numerically_less_7(void);
static void cont__types__string__numerically_less_8(void);
static void cont__types__string__numerically_less_9(void);
static NODE *func__types__string__numerically_less_10;
static void entry__types__string__numerically_less_10(void);
static FRAME_INFO frame__types__string__numerically_less_10 = {8, {"left_chr", "right_chr", "i", "left_len", "left", "right_len", "right", "return"}};
static void cont__types__string__numerically_less_11(void);
static void cont__types__string__numerically_less_12(void);
static NODE *func__types__string__numerically_less_13;
static void entry__types__string__numerically_less_13(void);
static FRAME_INFO frame__types__string__numerically_less_13 = {2, {"left_chr", "right_chr"}};
static void cont__types__string__numerically_less_14(void);
static void cont__types__string__numerically_less_15(void);
static NODE *func__types__string__numerically_less_16;
static void entry__types__string__numerically_less_16(void);
static FRAME_INFO frame__types__string__numerically_less_16 = {1, {"right_chr"}};
static void cont__types__string__numerically_less_17(void);
static void cont__types__string__numerically_less_18(void);
static NODE *func__types__string__numerically_less_19;
static void entry__types__string__numerically_less_19(void);
static FRAME_INFO frame__types__string__numerically_less_19 = {1, {"right_chr"}};
static void cont__types__string__numerically_less_20(void);
static void cont__types__string__numerically_less_21(void);
static void cont__types__string__numerically_less_22(void);
static void cont__types__string__numerically_less_23(void);
static void cont__types__string__numerically_less_24(void);
static NODE *func__types__string__numerically_less_25;
static void entry__types__string__numerically_less_25(void);
static FRAME_INFO frame__types__string__numerically_less_25 = {9, {"i", "left_len", "left", "right_len", "right", "return", "left_chr", "right_chr", "j"}};
static void cont__types__string__numerically_less_26(void);
static NODE *func__types__string__numerically_less_27;
static void entry__types__string__numerically_less_27(void);
static FRAME_INFO frame__types__string__numerically_less_27 = {8, {"left_len", "j", "left", "right_len", "right", "return", "left_chr", "right_chr"}};
static void cont__types__string__numerically_less_28(void);
static void cont__types__string__numerically_less_29(void);
static NODE *func__types__string__numerically_less_30;
static void entry__types__string__numerically_less_30(void);
static FRAME_INFO frame__types__string__numerically_less_30 = {2, {"left", "j"}};
static void cont__types__string__numerically_less_31(void);
static void cont__types__string__numerically_less_32(void);
static void cont__types__string__numerically_less_33(void);
static NODE *func__types__string__numerically_less_34;
static void entry__types__string__numerically_less_34(void);
static FRAME_INFO frame__types__string__numerically_less_34 = {4, {"right_len", "j", "right", "return"}};
static void cont__types__string__numerically_less_35(void);
static void cont__types__string__numerically_less_36(void);
static NODE *func__types__string__numerically_less_37;
static void entry__types__string__numerically_less_37(void);
static FRAME_INFO frame__types__string__numerically_less_37 = {2, {"right", "j"}};
static void cont__types__string__numerically_less_38(void);
static void cont__types__string__numerically_less_39(void);
static void cont__types__string__numerically_less_40(void);
static NODE *func__types__string__numerically_less_41;
static void entry__types__string__numerically_less_41(void);
static FRAME_INFO frame__types__string__numerically_less_41 = {1, {"j"}};
static void cont__types__string__numerically_less_42(void);
static NODE *func__types__string__numerically_less_43;
static void entry__types__string__numerically_less_43(void);
static FRAME_INFO frame__types__string__numerically_less_43 = {1, {"return"}};
static NODE *func__types__string__numerically_less_44;
static void entry__types__string__numerically_less_44(void);
static FRAME_INFO frame__types__string__numerically_less_44 = {6, {"right_len", "j", "right", "return", "left_chr", "right_chr"}};
static void cont__types__string__numerically_less_45(void);
static void cont__types__string__numerically_less_46(void);
static NODE *func__types__string__numerically_less_47;
static void entry__types__string__numerically_less_47(void);
static FRAME_INFO frame__types__string__numerically_less_47 = {2, {"right", "j"}};
static void cont__types__string__numerically_less_48(void);
static void cont__types__string__numerically_less_49(void);
static void cont__types__string__numerically_less_50(void);
static NODE *func__types__string__numerically_less_51;
static void entry__types__string__numerically_less_51(void);
static FRAME_INFO frame__types__string__numerically_less_51 = {1, {"return"}};
static NODE *func__types__string__numerically_less_52;
static void entry__types__string__numerically_less_52(void);
static FRAME_INFO frame__types__string__numerically_less_52 = {3, {"return", "left_chr", "right_chr"}};
static void cont__types__string__numerically_less_53(void);
static NODE *func__types__string__numerically_less_54;
static void entry__types__string__numerically_less_54(void);
static FRAME_INFO frame__types__string__numerically_less_54 = {3, {"return", "left_chr", "right_chr"}};
static void cont__types__string__numerically_less_55(void);
static void cont__types__string__numerically_less_56(void);
static void cont__types__string__numerically_less_57(void);
static void cont__types__string__numerically_less_58(void);
static NODE *func__types__string__to_list_1;
static void entry__types__string__to_list_1(void);
static FRAME_INFO frame__types__string__to_list_1 = {2, {"self", "items"}};
static NODE *func__types__string__to_list_2;
static void entry__types__string__to_list_2(void);
static FRAME_INFO frame__types__string__to_list_2 = {2, {"item", "items"}};
static void cont__types__string__to_list_3(void);
static void cont__types__string__to_list_4(void);
static NODE *func__std__string_1;
static void entry__std__string_1(void);
static FRAME_INFO frame__std__string_1 = {3, {"args", "buf", "n"}};
static void cont__std__string_2(void);
static NODE *func__std__string_3;
static void entry__std__string_3(void);
static FRAME_INFO frame__std__string_3 = {3, {"i", "buf", "args"}};
static void cont__std__string_4(void);
static void cont__std__string_5(void);
static void cont__std__string_6(void);
static void cont__std__string_7(void);
static NODE *get__std__string(void) {
  return var.std__string;
}
static NODE *func__types__string__dup_1;
static void entry__types__string__dup_1(void);
static FRAME_INFO frame__types__string__dup_1 = {3, {"self", "n", "return"}};
static NODE *func__types__string__dup_2;
static void entry__types__string__dup_2(void);
static FRAME_INFO frame__types__string__dup_2 = {1, {"return"}};
static NODE *func__types__string__dup_3;
static void entry__types__string__dup_3(void);
static FRAME_INFO frame__types__string__dup_3 = {2, {"return", "self"}};
static NODE *func__types__string__dup_4;
static void entry__types__string__dup_4(void);
static FRAME_INFO frame__types__string__dup_4 = {5, {"n", "self", "return", "h", "str"}};
static void cont__types__string__dup_5(void);
static NODE *func__types__string__dup_6;
static void entry__types__string__dup_6(void);
static FRAME_INFO frame__types__string__dup_6 = {0, {}};
static NODE *string__963fa2c6021831d1;
static void cont__types__string__dup_8(void);
static void cont__types__string__dup_9(void);
static void cont__types__string__dup_10(void);
static void cont__types__string__dup_11(void);
static void cont__types__string__dup_12(void);
static NODE *func__types__string__dup_13;
static void entry__types__string__dup_13(void);
static FRAME_INFO frame__types__string__dup_13 = {2, {"return", "str"}};
static void cont__types__string__dup_14(void);
static NODE *func__types__string__dup_15;
static void entry__types__string__dup_15(void);
static FRAME_INFO frame__types__string__dup_15 = {3, {"return", "str", "self"}};
static void cont__types__string__dup_16(void);
static void cont__types__string__dup_17(void);
static NODE *func__std__pad_left_1;
static void entry__std__pad_left_1(void);
static FRAME_INFO frame__std__pad_left_1 = {6, {"expr", "n", "pad", "return", "text", "len"}};
static NODE *string__578a5af303e9cc1;
static void cont__std__pad_left_3(void);
static void cont__std__pad_left_4(void);
static void cont__std__pad_left_5(void);
static NODE *func__std__pad_left_6;
static void entry__std__pad_left_6(void);
static FRAME_INFO frame__std__pad_left_6 = {6, {"pad", "return", "n", "len", "text", "pad_len"}};
static void cont__std__pad_left_7(void);
static void cont__std__pad_left_8(void);
static void cont__std__pad_left_9(void);
static void cont__std__pad_left_10(void);
static void cont__std__pad_left_11(void);
static void cont__std__pad_left_12(void);
static void cont__std__pad_left_13(void);
static void cont__std__pad_left_14(void);
static void cont__std__pad_left_15(void);
static void cont__std__pad_left_16(void);
static NODE *get__std__pad_left(void) {
  return var.std__pad_left;
}
static NODE *func__std__pad_right_1;
static void entry__std__pad_right_1(void);
static FRAME_INFO frame__std__pad_right_1 = {6, {"expr", "n", "pad", "return", "text", "len"}};
static void cont__std__pad_right_2(void);
static void cont__std__pad_right_3(void);
static void cont__std__pad_right_4(void);
static NODE *func__std__pad_right_5;
static void entry__std__pad_right_5(void);
static FRAME_INFO frame__std__pad_right_5 = {6, {"pad", "return", "text", "n", "len", "pad_len"}};
static void cont__std__pad_right_6(void);
static void cont__std__pad_right_7(void);
static void cont__std__pad_right_8(void);
static void cont__std__pad_right_9(void);
static void cont__std__pad_right_10(void);
static void cont__std__pad_right_11(void);
static void cont__std__pad_right_12(void);
static void cont__std__pad_right_13(void);
static void cont__std__pad_right_14(void);
static void cont__std__pad_right_15(void);
static NODE *get__std__pad_right(void) {
  return var.std__pad_right;
}
static NODE *func__std__truncate_1;
static void entry__std__truncate_1(void);
static FRAME_INFO frame__std__truncate_1 = {4, {"expr", "n", "text", "len"}};
static void cont__std__truncate_2(void);
static void cont__std__truncate_3(void);
static void cont__std__truncate_4(void);
static NODE *func__std__truncate_5;
static void entry__std__truncate_5(void);
static FRAME_INFO frame__std__truncate_5 = {1, {"text"}};
static NODE *func__std__truncate_6;
static void entry__std__truncate_6(void);
static FRAME_INFO frame__std__truncate_6 = {2, {"text", "n"}};
static void cont__std__truncate_7(void);
static NODE *get__std__truncate(void) {
  return var.std__truncate;
}
static NODE *func__std__pad_or_truncate_1;
static void entry__std__pad_or_truncate_1(void);
static FRAME_INFO frame__std__pad_or_truncate_1 = {4, {"expr", "n", "text", "len"}};
static void cont__std__pad_or_truncate_2(void);
static void cont__std__pad_or_truncate_3(void);
static void cont__std__pad_or_truncate_4(void);
static NODE *func__std__pad_or_truncate_5;
static void entry__std__pad_or_truncate_5(void);
static FRAME_INFO frame__std__pad_or_truncate_5 = {3, {"text", "n", "len"}};
static void cont__std__pad_or_truncate_6(void);
static void cont__std__pad_or_truncate_7(void);
static void cont__std__pad_or_truncate_8(void);
static NODE *func__std__pad_or_truncate_9;
static void entry__std__pad_or_truncate_9(void);
static FRAME_INFO frame__std__pad_or_truncate_9 = {2, {"text", "n"}};
static void cont__std__pad_or_truncate_10(void);
static NODE *get__std__pad_or_truncate(void) {
  return var.std__pad_or_truncate;
}
static NODE *func__types__string__match_character_1;
static void entry__types__string__match_character_1(void);
static FRAME_INFO frame__types__string__match_character_1 = {2, {"self", "chr"}};
static void cont__types__string__match_character_2(void);
static void cont__types__string__match_character_3(void);
static NODE *func__types__string__match_character_4;
static void entry__types__string__match_character_4(void);
static FRAME_INFO frame__types__string__match_character_4 = {2, {"self", "chr"}};
static void cont__types__string__match_character_5(void);
static void cont__types__string__match_character_6(void);
static void cont__types__string__match_character_7(void);
static NODE *func__types__string__match_character_8;
static void entry__types__string__match_character_8(void);
static FRAME_INFO frame__types__string__match_character_8 = {0, {}};
static NODE *func__types__string__match_character_9;
static void entry__types__string__match_character_9(void);
static FRAME_INFO frame__types__string__match_character_9 = {0, {}};
static NODE *func__types__string__grammar__match_1;
static void entry__types__string__grammar__match_1(void);
static FRAME_INFO frame__types__string__grammar__match_1 = {4, {"expr", "stream", "return", "len"}};
static void cont__types__string__grammar__match_2(void);
static void cont__types__string__grammar__match_3(void);
static NODE *func__types__string__grammar__match_4;
static void entry__types__string__grammar__match_4(void);
static FRAME_INFO frame__types__string__grammar__match_4 = {1, {"return"}};
static void cont__types__string__grammar__match_5(void);
static void cont__types__string__grammar__match_6(void);
static void cont__types__string__grammar__match_7(void);
static NODE *func__types__string__grammar__match_8;
static void entry__types__string__grammar__match_8(void);
static FRAME_INFO frame__types__string__grammar__match_8 = {2, {"return", "len"}};
static void cont__types__string__grammar__match_9(void);
static NODE *func__types__string__match_1;
static void entry__types__string__match_1(void);
static FRAME_INFO frame__types__string__match_1 = {4, {"stream", "expr", "return", "n"}};
static void cont__types__string__match_2(void);
static void cont__types__string__match_3(void);
static void cont__types__string__match_4(void);
static NODE *func__types__string__match_5;
static void entry__types__string__match_5(void);
static FRAME_INFO frame__types__string__match_5 = {2, {"return", "n"}};
static void cont__types__string__match_6(void);
static NODE *func__types__string__search_character_1;
static void entry__types__string__search_character_1(void);
static FRAME_INFO frame__types__string__search_character_1 = {3, {"self", "chr", "sum"}};
static void cont__types__string__search_character_2(void);
static NODE *func__types__string__search_character_3;
static void entry__types__string__search_character_3(void);
static FRAME_INFO frame__types__string__search_character_3 = {3, {"self", "chr", "sum"}};
static void cont__types__string__search_character_4(void);
static void cont__types__string__search_character_5(void);
static NODE *func__types__string__search_character_6;
static void entry__types__string__search_character_6(void);
static FRAME_INFO frame__types__string__search_character_6 = {1, {"sum"}};
static void cont__types__string__search_character_7(void);
static NODE *func__types__string__search_character_8;
static void entry__types__string__search_character_8(void);
static FRAME_INFO frame__types__string__search_character_8 = {3, {"self", "chr", "sum"}};
static void cont__types__string__search_character_9(void);
static void cont__types__string__search_character_10(void);
static void cont__types__string__search_character_11(void);
static void cont__types__string__search_character_12(void);
static NODE *func__types__string__search_character_13;
static void entry__types__string__search_character_13(void);
static FRAME_INFO frame__types__string__search_character_13 = {0, {}};
static NODE *func__types__string__search_1;
static void entry__types__string__search_1(void);
static FRAME_INFO frame__types__string__search_1 = {5, {"stream", "expr", "return__1", "pos", "len"}};
static void cont__types__string__search_2(void);
static NODE *func__types__string__before_1;
static void entry__types__string__before_1(void);
static FRAME_INFO frame__types__string__before_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__types__string__before_2(void);
static void cont__types__string__before_3(void);
static NODE *func__types__string__before_4;
static void entry__types__string__before_4(void);
static FRAME_INFO frame__types__string__before_4 = {3, {"return", "str", "pos"}};
static void cont__types__string__before_5(void);
static void cont__types__string__before_6(void);
static NODE *func__types__string__before_7;
static void entry__types__string__before_7(void);
static FRAME_INFO frame__types__string__before_7 = {1, {"return"}};
static void cont__types__string__before_8(void);
static NODE *func__types__string__truncate_from_1;
static void entry__types__string__truncate_from_1(void);
static FRAME_INFO frame__types__string__truncate_from_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__types__string__truncate_from_2(void);
static void cont__types__string__truncate_from_3(void);
static NODE *func__types__string__truncate_from_4;
static void entry__types__string__truncate_from_4(void);
static FRAME_INFO frame__types__string__truncate_from_4 = {3, {"return", "str", "pos"}};
static void cont__types__string__truncate_from_5(void);
static void cont__types__string__truncate_from_6(void);
static NODE *func__types__string__truncate_from_7;
static void entry__types__string__truncate_from_7(void);
static FRAME_INFO frame__types__string__truncate_from_7 = {2, {"return", "str"}};
static void cont__types__string__truncate_from_8(void);
static NODE *func__types__string__behind_1;
static void entry__types__string__behind_1(void);
static FRAME_INFO frame__types__string__behind_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__types__string__behind_2(void);
static void cont__types__string__behind_3(void);
static NODE *func__types__string__behind_4;
static void entry__types__string__behind_4(void);
static FRAME_INFO frame__types__string__behind_4 = {4, {"return", "str", "pos", "len"}};
static void cont__types__string__behind_5(void);
static void cont__types__string__behind_6(void);
static void cont__types__string__behind_7(void);
static NODE *func__types__string__behind_8;
static void entry__types__string__behind_8(void);
static FRAME_INFO frame__types__string__behind_8 = {1, {"return"}};
static void cont__types__string__behind_9(void);
static NODE *func__types__string__truncate_until_1;
static void entry__types__string__truncate_until_1(void);
static FRAME_INFO frame__types__string__truncate_until_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__types__string__truncate_until_2(void);
static void cont__types__string__truncate_until_3(void);
static NODE *func__types__string__truncate_until_4;
static void entry__types__string__truncate_until_4(void);
static FRAME_INFO frame__types__string__truncate_until_4 = {4, {"return", "str", "pos", "len"}};
static void cont__types__string__truncate_until_5(void);
static void cont__types__string__truncate_until_6(void);
static void cont__types__string__truncate_until_7(void);
static NODE *func__types__string__truncate_until_8;
static void entry__types__string__truncate_until_8(void);
static FRAME_INFO frame__types__string__truncate_until_8 = {2, {"return", "str"}};
static void cont__types__string__truncate_until_9(void);
static NODE *func__types__string__from_1;
static void entry__types__string__from_1(void);
static FRAME_INFO frame__types__string__from_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__types__string__from_2(void);
static void cont__types__string__from_3(void);
static NODE *func__types__string__from_4;
static void entry__types__string__from_4(void);
static FRAME_INFO frame__types__string__from_4 = {3, {"return", "str", "pos"}};
static void cont__types__string__from_5(void);
static void cont__types__string__from_6(void);
static NODE *func__types__string__from_7;
static void entry__types__string__from_7(void);
static FRAME_INFO frame__types__string__from_7 = {1, {"return"}};
static void cont__types__string__from_8(void);
static NODE *func__types__string__truncate_before_1;
static void entry__types__string__truncate_before_1(void);
static FRAME_INFO frame__types__string__truncate_before_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__types__string__truncate_before_2(void);
static void cont__types__string__truncate_before_3(void);
static NODE *func__types__string__truncate_before_4;
static void entry__types__string__truncate_before_4(void);
static FRAME_INFO frame__types__string__truncate_before_4 = {3, {"return", "str", "pos"}};
static void cont__types__string__truncate_before_5(void);
static void cont__types__string__truncate_before_6(void);
static NODE *func__types__string__truncate_before_7;
static void entry__types__string__truncate_before_7(void);
static FRAME_INFO frame__types__string__truncate_before_7 = {2, {"return", "str"}};
static void cont__types__string__truncate_before_8(void);
static NODE *func__types__string__until_1;
static void entry__types__string__until_1(void);
static FRAME_INFO frame__types__string__until_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__types__string__until_2(void);
static void cont__types__string__until_3(void);
static NODE *func__types__string__until_4;
static void entry__types__string__until_4(void);
static FRAME_INFO frame__types__string__until_4 = {4, {"return", "str", "pos", "len"}};
static void cont__types__string__until_5(void);
static void cont__types__string__until_6(void);
static void cont__types__string__until_7(void);
static NODE *func__types__string__until_8;
static void entry__types__string__until_8(void);
static FRAME_INFO frame__types__string__until_8 = {1, {"return"}};
static void cont__types__string__until_9(void);
static NODE *func__types__string__truncate_behind_1;
static void entry__types__string__truncate_behind_1(void);
static FRAME_INFO frame__types__string__truncate_behind_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__types__string__truncate_behind_2(void);
static void cont__types__string__truncate_behind_3(void);
static NODE *func__types__string__truncate_behind_4;
static void entry__types__string__truncate_behind_4(void);
static FRAME_INFO frame__types__string__truncate_behind_4 = {4, {"return", "str", "pos", "len"}};
static void cont__types__string__truncate_behind_5(void);
static void cont__types__string__truncate_behind_6(void);
static void cont__types__string__truncate_behind_7(void);
static NODE *func__types__string__truncate_behind_8;
static void entry__types__string__truncate_behind_8(void);
static FRAME_INFO frame__types__string__truncate_behind_8 = {2, {"return", "str"}};
static void cont__types__string__truncate_behind_9(void);
static NODE *func__types__string__between_1;
static void entry__types__string__between_1(void);
static FRAME_INFO frame__types__string__between_1 = {4, {"str", "expr_1", "expr_2", "nth"}};
static void cont__types__string__between_2(void);
static void cont__types__string__between_3(void);
static NODE *func__types__string__has_prefix_1;
static void entry__types__string__has_prefix_1(void);
static FRAME_INFO frame__types__string__has_prefix_1 = {2, {"self", "prefix"}};
static void cont__types__string__has_prefix_2(void);
static void cont__types__string__has_prefix_3(void);
static NODE *func__types__string__has_suffix_1;
static void entry__types__string__has_suffix_1(void);
static FRAME_INFO frame__types__string__has_suffix_1 = {4, {"self", "suffix", "return", "len"}};
static void cont__types__string__has_suffix_2(void);
static NODE *func__types__string__has_suffix_3;
static void entry__types__string__has_suffix_3(void);
static FRAME_INFO frame__types__string__has_suffix_3 = {5, {"i", "self", "suffix", "len", "return"}};
static void cont__types__string__has_suffix_4(void);
static void cont__types__string__has_suffix_5(void);
static void cont__types__string__has_suffix_6(void);
static void cont__types__string__has_suffix_7(void);
static void cont__types__string__has_suffix_8(void);
static void cont__types__string__has_suffix_9(void);
static NODE *func__types__string__has_suffix_10;
static void entry__types__string__has_suffix_10(void);
static FRAME_INFO frame__types__string__has_suffix_10 = {1, {"return"}};
static void cont__types__string__has_suffix_11(void);
static NODE *func__types__string__without_prefix_1;
static void entry__types__string__without_prefix_1(void);
static FRAME_INFO frame__types__string__without_prefix_1 = {4, {"self", "prefix", "return", "n"}};
static void cont__types__string__without_prefix_2(void);
static void cont__types__string__without_prefix_3(void);
static NODE *func__types__string__without_prefix_4;
static void entry__types__string__without_prefix_4(void);
static FRAME_INFO frame__types__string__without_prefix_4 = {3, {"return", "self", "n"}};
static void cont__types__string__without_prefix_5(void);
static void cont__types__string__without_prefix_6(void);
static void cont__types__string__without_prefix_7(void);
static void cont__types__string__without_prefix_8(void);
static NODE *func__types__string__without_suffix_1;
static void entry__types__string__without_suffix_1(void);
static FRAME_INFO frame__types__string__without_suffix_1 = {4, {"self", "suffix", "return", "len"}};
static void cont__types__string__without_suffix_2(void);
static NODE *func__types__string__without_suffix_3;
static void entry__types__string__without_suffix_3(void);
static FRAME_INFO frame__types__string__without_suffix_3 = {5, {"i", "self", "suffix", "len", "return"}};
static void cont__types__string__without_suffix_4(void);
static void cont__types__string__without_suffix_5(void);
static void cont__types__string__without_suffix_6(void);
static void cont__types__string__without_suffix_7(void);
static void cont__types__string__without_suffix_8(void);
static void cont__types__string__without_suffix_9(void);
static NODE *func__types__string__without_suffix_10;
static void entry__types__string__without_suffix_10(void);
static FRAME_INFO frame__types__string__without_suffix_10 = {3, {"return", "self", "i"}};
static void cont__types__string__without_suffix_11(void);
static void cont__types__string__without_suffix_12(void);
static void cont__types__string__without_suffix_13(void);
static NODE *func__std__trim_1;
static void entry__std__trim_1(void);
static FRAME_INFO frame__std__trim_1 = {3, {"str", "s", "e"}};
static void cont__std__trim_2(void);
static NODE *func__std__trim_3;
static void entry__std__trim_3(void);
static FRAME_INFO frame__std__trim_3 = {3, {"e", "s", "str"}};
static void cont__std__trim_4(void);
static void cont__std__trim_5(void);
static NODE *func__std__trim_6;
static void entry__std__trim_6(void);
static FRAME_INFO frame__std__trim_6 = {2, {"str", "s"}};
static void cont__std__trim_7(void);
static void cont__std__trim_8(void);
static void cont__std__trim_9(void);
static void cont__std__trim_10(void);
static NODE *func__std__trim_11;
static void entry__std__trim_11(void);
static FRAME_INFO frame__std__trim_11 = {1, {"s"}};
static void cont__std__trim_12(void);
static void cont__std__trim_13(void);
static NODE *func__std__trim_14;
static void entry__std__trim_14(void);
static FRAME_INFO frame__std__trim_14 = {3, {"e", "s", "str"}};
static void cont__std__trim_15(void);
static void cont__std__trim_16(void);
static NODE *func__std__trim_17;
static void entry__std__trim_17(void);
static FRAME_INFO frame__std__trim_17 = {2, {"str", "e"}};
static void cont__std__trim_18(void);
static void cont__std__trim_19(void);
static void cont__std__trim_20(void);
static void cont__std__trim_21(void);
static NODE *func__std__trim_22;
static void entry__std__trim_22(void);
static FRAME_INFO frame__std__trim_22 = {1, {"e"}};
static void cont__std__trim_23(void);
static void cont__std__trim_24(void);
static void cont__std__trim_25(void);
static NODE *get__std__trim(void) {
  return var.std__trim;
}
static NODE *func__std__normalize_1;
static void entry__std__normalize_1(void);
static FRAME_INFO frame__std__normalize_1 = {1, {"str"}};
static void cont__std__normalize_2(void);
static void cont__std__normalize_3(void);
static void cont__std__normalize_4(void);
static void cont__std__normalize_5(void);
static void cont__std__normalize_6(void);
static NODE *get__std__normalize(void) {
  return var.std__normalize;
}
static NODE *func__std__split_1;
static void entry__std__split_1(void);
static FRAME_INFO frame__std__split_1 = {3, {"text", "separator", "items"}};
static void cont__std__split_3(void);
static void cont__std__split_2(void);
static NODE *func__std__split_4;
static void entry__std__split_4(void);
static FRAME_INFO frame__std__split_4 = {5, {"separator", "text", "items", "pos", "len"}};
static void cont__std__split_5(void);
static void cont__std__split_6(void);
static NODE *func__std__split_7;
static void entry__std__split_7(void);
static FRAME_INFO frame__std__split_7 = {4, {"items", "text", "pos", "len"}};
static void cont__std__split_8(void);
static void cont__std__split_9(void);
static void cont__std__split_10(void);
static void cont__std__split_11(void);
static void cont__std__split_12(void);
static void cont__std__split_13(void);
static void cont__std__split_14(void);
static void cont__std__split_15(void);
static void cont__std__split_16(void);
static void cont__std__split_17(void);
static void cont__std__split_18(void);
static NODE *func__std__split_19;
static void entry__std__split_19(void);
static FRAME_INFO frame__std__split_19 = {2, {"items", "text"}};
static void cont__std__split_20(void);
static void cont__std__split_21(void);
static NODE *get__std__split(void) {
  return var.std__split;
}
static NODE *func__std__join_1;
static void entry__std__join_1(void);
static FRAME_INFO frame__std__join_1 = {3, {"words", "separator", "text"}};
static NODE *func__std__join_2;
static void entry__std__join_2(void);
static FRAME_INFO frame__std__join_2 = {2, {"word", "text"}};
static void cont__std__join_3(void);
static NODE *func__std__join_4;
static void entry__std__join_4(void);
static FRAME_INFO frame__std__join_4 = {2, {"text", "separator"}};
static void cont__std__join_5(void);
static void cont__std__join_6(void);
static NODE *get__std__join(void) {
  return var.std__join;
}
static NODE *func__std__count_occurrences_1;
static void entry__std__count_occurrences_1(void);
static FRAME_INFO frame__std__count_occurrences_1 = {3, {"text", "expr", "n"}};
static NODE *func__std__count_occurrences_2;
static void entry__std__count_occurrences_2(void);
static FRAME_INFO frame__std__count_occurrences_2 = {5, {"expr", "text", "n", "pos", "len"}};
static void cont__std__count_occurrences_3(void);
static void cont__std__count_occurrences_4(void);
static NODE *func__std__count_occurrences_5;
static void entry__std__count_occurrences_5(void);
static FRAME_INFO frame__std__count_occurrences_5 = {4, {"text", "pos", "len", "n"}};
static void cont__std__count_occurrences_6(void);
static void cont__std__count_occurrences_7(void);
static void cont__std__count_occurrences_8(void);
static void cont__std__count_occurrences_9(void);
static void cont__std__count_occurrences_10(void);
static void cont__std__count_occurrences_11(void);
static void cont__std__count_occurrences_12(void);
static NODE *get__std__count_occurrences(void) {
  return var.std__count_occurrences;
}
static NODE *func__types__string__matches_1;
static void entry__types__string__matches_1(void);
static FRAME_INFO frame__types__string__matches_1 = {2, {"text", "expr"}};
static void cont__types__string__matches_2(void);
static void cont__types__string__matches_3(void);
static void cont__types__string__matches_4(void);
static NODE *func__types__string__contains_1;
static void entry__types__string__contains_1(void);
static FRAME_INFO frame__types__string__contains_1 = {4, {"text", "expr", "pos", "len"}};
static void cont__types__string__contains_2(void);
static void cont__types__string__contains_3(void);
static NODE *func__std__replace_umlauts_1;
static void entry__std__replace_umlauts_1(void);
static FRAME_INFO frame__std__replace_umlauts_1 = {4, {"text", "s", "result", "copy"}};
static NODE *func__std__replace_umlauts_2;
static void entry__std__replace_umlauts_2(void);
static FRAME_INFO frame__std__replace_umlauts_2 = {4, {"idx", "result", "text", "s"}};
static void cont__std__replace_umlauts_3(void);
static void cont__std__replace_umlauts_4(void);
static void cont__std__replace_umlauts_5(void);
static NODE *func__std__replace_umlauts_6;
static void entry__std__replace_umlauts_6(void);
static FRAME_INFO frame__std__replace_umlauts_6 = {4, {"idx", "chr", "copy", "result"}};
static void cont__std__replace_umlauts_7(void);
static void cont__std__replace_umlauts_8(void);
static NODE *func__std__replace_umlauts_9;
static void entry__std__replace_umlauts_9(void);
static FRAME_INFO frame__std__replace_umlauts_9 = {4, {"chr", "copy", "idx", "result"}};
static void cont__std__replace_umlauts_10(void);
static void cont__std__replace_umlauts_11(void);
static NODE *func__std__replace_umlauts_12;
static void entry__std__replace_umlauts_12(void);
static FRAME_INFO frame__std__replace_umlauts_12 = {5, {"copy", "idx", "chr", "result", "conversion"}};
static void cont__std__replace_umlauts_13(void);
static void cont__std__replace_umlauts_14(void);
static void cont__std__replace_umlauts_15(void);
static void cont__std__replace_umlauts_16(void);
static NODE *func__std__replace_umlauts_17;
static void entry__std__replace_umlauts_17(void);
static FRAME_INFO frame__std__replace_umlauts_17 = {2, {"result", "conversion"}};
static void cont__std__replace_umlauts_18(void);
static NODE *func__std__replace_umlauts_19;
static void entry__std__replace_umlauts_19(void);
static FRAME_INFO frame__std__replace_umlauts_19 = {1, {"result"}};
static void cont__std__replace_umlauts_20(void);
static NODE *func__std__replace_umlauts_21;
static void entry__std__replace_umlauts_21(void);
static FRAME_INFO frame__std__replace_umlauts_21 = {4, {"copy", "idx", "result", "chr"}};
static void cont__std__replace_umlauts_22(void);
static void cont__std__replace_umlauts_23(void);
static void cont__std__replace_umlauts_24(void);
static void cont__std__replace_umlauts_25(void);
static void cont__std__replace_umlauts_26(void);
static void cont__std__replace_umlauts_27(void);
static void cont__std__replace_umlauts_28(void);
static NODE *get__std__replace_umlauts(void) {
  return var.std__replace_umlauts;
}
static NODE *func__std__replace_all_1;
static void entry__std__replace_all_1(void);
static FRAME_INFO frame__std__replace_all_1 = {3, {"text", "args", "new_text"}};
static NODE *func__std__replace_all_2;
static void entry__std__replace_all_2(void);
static FRAME_INFO frame__std__replace_all_2 = {3, {"text", "args", "new_text"}};
static void cont__std__replace_all_3(void);
static void cont__std__replace_all_4(void);
static NODE *func__std__replace_all_5;
static void entry__std__replace_all_5(void);
static FRAME_INFO frame__std__replace_all_5 = {3, {"args", "text", "new_text"}};
static NODE *func__std__replace_all_6;
static void entry__std__replace_all_6(void);
static FRAME_INFO frame__std__replace_all_6 = {4, {"break", "args", "text", "new_text"}};
static NODE *func__std__replace_all_7;
static void entry__std__replace_all_7(void);
static FRAME_INFO frame__std__replace_all_7 = {7, {"arg", "text", "new_text", "break", "expression", "replacement", "len"}};
static void cont__std__replace_all_8(void);
static void cont__std__replace_all_9(void);
static void cont__std__replace_all_10(void);
static void cont__std__replace_all_11(void);
static NODE *func__std__replace_all_12;
static void entry__std__replace_all_12(void);
static FRAME_INFO frame__std__replace_all_12 = {5, {"replacement", "new_text", "text", "len", "break"}};
static void cont__std__replace_all_13(void);
static NODE *func__std__replace_all_14;
static void entry__std__replace_all_14(void);
static FRAME_INFO frame__std__replace_all_14 = {2, {"new_text", "replacement"}};
static void cont__std__replace_all_15(void);
static NODE *func__std__replace_all_16;
static void entry__std__replace_all_16(void);
static FRAME_INFO frame__std__replace_all_16 = {4, {"new_text", "replacement", "text", "len"}};
static void cont__std__replace_all_17(void);
static void cont__std__replace_all_18(void);
static void cont__std__replace_all_19(void);
static void cont__std__replace_all_20(void);
static void cont__std__replace_all_21(void);
static void cont__std__replace_all_22(void);
static void cont__std__replace_all_23(void);
static void cont__std__replace_all_24(void);
static void cont__std__replace_all_25(void);
static void cont__std__replace_all_26(void);
static void cont__std__replace_all_27(void);
static void cont__std__replace_all_28(void);
static void cont__std__replace_all_29(void);
static NODE *get__std__replace_all(void) {
  return var.std__replace_all;
}
static NODE *func__std__delete_all_1;
static void entry__std__delete_all_1(void);
static FRAME_INFO frame__std__delete_all_1 = {3, {"text", "expressions", "new_text"}};
static NODE *func__std__delete_all_2;
static void entry__std__delete_all_2(void);
static FRAME_INFO frame__std__delete_all_2 = {3, {"text", "expressions", "new_text"}};
static void cont__std__delete_all_3(void);
static void cont__std__delete_all_4(void);
static NODE *func__std__delete_all_5;
static void entry__std__delete_all_5(void);
static FRAME_INFO frame__std__delete_all_5 = {3, {"expressions", "text", "new_text"}};
static NODE *func__std__delete_all_6;
static void entry__std__delete_all_6(void);
static FRAME_INFO frame__std__delete_all_6 = {4, {"break", "expressions", "text", "new_text"}};
static NODE *func__std__delete_all_7;
static void entry__std__delete_all_7(void);
static FRAME_INFO frame__std__delete_all_7 = {4, {"expression", "text", "break", "len"}};
static void cont__std__delete_all_8(void);
static void cont__std__delete_all_9(void);
static NODE *func__std__delete_all_10;
static void entry__std__delete_all_10(void);
static FRAME_INFO frame__std__delete_all_10 = {3, {"text", "len", "break"}};
static void cont__std__delete_all_11(void);
static void cont__std__delete_all_12(void);
static void cont__std__delete_all_13(void);
static void cont__std__delete_all_14(void);
static void cont__std__delete_all_15(void);
static void cont__std__delete_all_16(void);
static void cont__std__delete_all_17(void);
static void cont__std__delete_all_18(void);
static void cont__std__delete_all_19(void);
static NODE *get__std__delete_all(void) {
  return var.std__delete_all;
}
static NODE *string__49792677fe126f62;
static NODE *func__std__spaces_1;
static void entry__std__spaces_1(void);
static FRAME_INFO frame__std__spaces_1 = {1, {"n"}};
static void cont__std__spaces_2(void);
static NODE *func__std__spaces_3;
static void entry__std__spaces_3(void);
static FRAME_INFO frame__std__spaces_3 = {1, {"n"}};
static void cont__std__spaces_4(void);
static NODE *func__std__spaces_5;
static void entry__std__spaces_5(void);
static FRAME_INFO frame__std__spaces_5 = {1, {"n"}};
static void cont__std__spaces_6(void);
static NODE *get__std__spaces(void) {
  return var.std__spaces;
}
static NODE *func__std__indented_1;
static void entry__std__indented_1(void);
static FRAME_INFO frame__std__indented_1 = {2, {"indent", "text"}};
static void cont__std__indented_2(void);
static NODE *func__std__indented_3;
static void entry__std__indented_3(void);
static FRAME_INFO frame__std__indented_3 = {3, {"indent", "text", "indentation"}};
static void cont__std__indented_4(void);
static void cont__std__indented_5(void);
static void cont__std__indented_6(void);
static void cont__std__indented_7(void);
static NODE *string__578a5af303e9ceb;
static void cont__std__indented_9(void);
static void cont__std__indented_10(void);
static void cont__std__indented_11(void);
static void cont__std__indented_12(void);
static void cont__std__indented_13(void);
static NODE *func__std__indented_14;
static void entry__std__indented_14(void);
static FRAME_INFO frame__std__indented_14 = {1, {"text"}};
static void cont__std__indented_15(void);
static void cont__std__indented_16(void);
static void cont__std__indented_17(void);
static NODE *func__std__indented_18;
static void entry__std__indented_18(void);
static FRAME_INFO frame__std__indented_18 = {2, {"text", "indentation"}};
static void cont__std__indented_19(void);
static void cont__std__indented_20(void);
static NODE *get__std__indented(void) {
  return var.std__indented;
}
static NODE *func__std__for_each_line_1;
static void entry__std__for_each_line_1(void);
static FRAME_INFO frame__std__for_each_line_1 = {6, {"text", "body", "body2", "no", "pos", "len"}};
static void cont__std__for_each_line_2(void);
static void cont__std__for_each_line_3(void);
static NODE *func__std__for_each_line_4;
static void entry__std__for_each_line_4(void);
static FRAME_INFO frame__std__for_each_line_4 = {6, {"body", "no", "text", "pos", "body2", "rest"}};
static void cont__std__for_each_line_5(void);
static void cont__std__for_each_line_6(void);
static NODE *func__std__for_each_line_7;
static void entry__std__for_each_line_7(void);
static FRAME_INFO frame__std__for_each_line_7 = {4, {"body", "no", "text", "pos"}};
static void cont__std__for_each_line_8(void);
static void cont__std__for_each_line_9(void);
static NODE *func__std__for_each_line_10;
static void entry__std__for_each_line_10(void);
static FRAME_INFO frame__std__for_each_line_10 = {3, {"body", "text", "pos"}};
static void cont__std__for_each_line_11(void);
static void cont__std__for_each_line_12(void);
static void cont__std__for_each_line_13(void);
static void cont__std__for_each_line_14(void);
static void cont__std__for_each_line_15(void);
static void cont__std__for_each_line_16(void);
static void cont__std__for_each_line_17(void);
static NODE *func__std__for_each_line_18;
static void entry__std__for_each_line_18(void);
static FRAME_INFO frame__std__for_each_line_18 = {1, {"rest"}};
static void cont__std__for_each_line_19(void);
static void cont__std__for_each_line_20(void);
static void cont__std__for_each_line_21(void);
static void cont__std__for_each_line_22(void);
static NODE *func__std__for_each_line_23;
static void entry__std__for_each_line_23(void);
static FRAME_INFO frame__std__for_each_line_23 = {3, {"text", "body", "no"}};
static void cont__std__for_each_line_24(void);
static void cont__std__for_each_line_25(void);
static NODE *func__std__for_each_line_26;
static void entry__std__for_each_line_26(void);
static FRAME_INFO frame__std__for_each_line_26 = {3, {"body", "no", "text"}};
static void cont__std__for_each_line_27(void);
static void cont__std__for_each_line_28(void);
static NODE *func__std__for_each_line_29;
static void entry__std__for_each_line_29(void);
static FRAME_INFO frame__std__for_each_line_29 = {3, {"body", "no", "text"}};
static NODE *func__std__for_each_line_30;
static void entry__std__for_each_line_30(void);
static FRAME_INFO frame__std__for_each_line_30 = {2, {"body", "text"}};
static NODE *get__std__for_each_line(void) {
  return var.std__for_each_line;
}
static NODE *func__types__string__to_lower_case_1;
static void entry__types__string__to_lower_case_1(void);
static FRAME_INFO frame__types__string__to_lower_case_1 = {1, {"text"}};
static void cont__types__string__to_lower_case_2(void);
static NODE *func__types__string__to_upper_case_1;
static void entry__types__string__to_upper_case_1(void);
static FRAME_INFO frame__types__string__to_upper_case_1 = {1, {"text"}};
static void cont__types__string__to_upper_case_2(void);
static NODE *func__types__string__to_title_case_1;
static void entry__types__string__to_title_case_1(void);
static FRAME_INFO frame__types__string__to_title_case_1 = {3, {"text", "out", "to_upper"}};
static NODE *func__types__string__to_title_case_2;
static void entry__types__string__to_title_case_2(void);
static FRAME_INFO frame__types__string__to_title_case_2 = {3, {"chr", "to_upper", "out"}};
static void cont__types__string__to_title_case_3(void);
static NODE *func__types__string__to_title_case_4;
static void entry__types__string__to_title_case_4(void);
static FRAME_INFO frame__types__string__to_title_case_4 = {3, {"to_upper", "out", "chr"}};
static NODE *func__types__string__to_title_case_5;
static void entry__types__string__to_title_case_5(void);
static FRAME_INFO frame__types__string__to_title_case_5 = {3, {"out", "chr", "to_upper"}};
static void cont__types__string__to_title_case_6(void);
static void cont__types__string__to_title_case_7(void);
static NODE *func__types__string__to_title_case_8;
static void entry__types__string__to_title_case_8(void);
static FRAME_INFO frame__types__string__to_title_case_8 = {2, {"out", "chr"}};
static void cont__types__string__to_title_case_9(void);
static void cont__types__string__to_title_case_10(void);
static NODE *func__types__string__to_title_case_11;
static void entry__types__string__to_title_case_11(void);
static FRAME_INFO frame__types__string__to_title_case_11 = {3, {"out", "chr", "to_upper"}};
static void cont__types__string__to_title_case_12(void);
static void cont__types__string__to_title_case_13(void);
static NODE *func__types__octet_string__new_empty_collection_1;
static void entry__types__octet_string__new_empty_collection_1(void);
static FRAME_INFO frame__types__octet_string__new_empty_collection_1 = {1, {"self"}};
static NODE *func__types__quad_octet_string__new_empty_collection_1;
static void entry__types__quad_octet_string__new_empty_collection_1(void);
static FRAME_INFO frame__types__quad_octet_string__new_empty_collection_1 = {1, {"self"}};
static NODE *func__std__collect_output_1;
static void entry__std__collect_output_1(void);
static FRAME_INFO frame__std__collect_output_1 = {3, {"self", "body", "return__1"}};
static void exit__std__collect_output_1(void);
static NODE *func__std__collect_output_2;
static void entry__std__collect_output_2(void);
static FRAME_INFO frame__std__collect_output_2 = {2, {"args", "self"}};
static void cont__std__collect_output_3(void);
static void cont__std__collect_output_4(void);
static NODE *get__std__collect_output(void) {
  return var.std__collect_output;
}
static void cont__93_1(void);
static NODE *string__578a5af303e9cc0;
static void cont__93_3(void);
static NODE *string__521f55e4811a62fe;
static void cont__93_5(void);
static NODE *string__99240e5a959a30d3;
static void cont__93_7(void);
static NODE *string__578a5af303e9cde;
static void cont__93_9(void);
static NODE *string__785aea43eabc907e;
static void cont__93_11(void);
static NODE *string__578a5af303e9c9d;
static void cont__93_13(void);
static NODE *string__578a5af303e9cc5;
static void cont__93_15(void);
static NODE *string__578a5af303e9cc3;
static void cont__93_17(void);
static NODE *string__fa732415d316be5;
static void cont__93_19(void);
static NODE *string__578a5af303e9c80;
static void cont__93_21(void);
static NODE *string__2d7981f4e6e82bf9;
static void cont__93_23(void);
static NODE *string__565ae8c3ea6c907e;
static void cont__93_25(void);
static NODE *string__6c5ae903ea04907e;
static void cont__93_27(void);
static NODE *string__fa732415db96be5;
static void cont__93_29(void);
static NODE *string__578a5af303e9c9f;
static void cont__93_31(void);
static NODE *string__7c1f5624819a22fe;
static void cont__93_33(void);
static NODE *string__fa732815f516be1;
static void cont__93_35(void);
static NODE *string__2d7981f4e5f82bf7;
static void cont__93_37(void);
static NODE *string__2d7981f4e5f82bf6;
static void cont__93_39(void);
static NODE *string__578a5af303e9cc6;
static void cont__93_41(void);
static NODE *string__920aea0b5dc87d10;
static void cont__93_43(void);
static NODE *string__6a5aeb43ea5c907e;
static void cont__93_45(void);
static NODE *string__578a5af303e9ccf;
static void cont__93_47(void);
static NODE *string__578a5af303e9ccd;
static void cont__93_49(void);
static NODE *string__2d7981f4e5f82bf4;
static void cont__93_51(void);
static NODE *string__578a5af303e9c8e;
static void cont__93_53(void);
static NODE *string__2d7981f4e6f82bfb;
static void cont__93_55(void);
static NODE *string__fa734015f516bf8;
static void cont__93_57(void);
static NODE *string__fa734015f516bfe;
static void cont__93_59(void);
static NODE *string__fa734815f516bf8;
static void cont__93_61(void);
static void cont__93_62(void);
static NODE *string__578a5af303e9ca0;
static void cont__93_64(void);
static void cont__93_65(void);
static void cont__93_66(void);
static void cont__93_67(void);
static NODE *string__2d7981f4e5002ba0;
static void cont__93_69(void);
static void cont__93_70(void);
static NODE *string__2d7981f4e5002b80;
static void cont__93_72(void);
static NODE *string__578a5af303e9ca2;
static void cont__93_74(void);
static NODE *string__578a5af303e9ca4;
static void cont__93_76(void);
static void cont__93_77(void);
static void cont__93_78(void);
static void cont__93_79(void);
static NODE *string__578a5af303e9ca8;
static void cont__93_81(void);
static void cont__93_82(void);
static void cont__93_83(void);
static void cont__93_84(void);
static NODE *string__578a5af303e9ca5;
static void cont__93_86(void);
static NODE *string__578a5af303e9caf;
static void cont__93_88(void);
static NODE *string__578a5af303e9cae;
static void cont__93_90(void);
static void cont__93_91(void);
static void cont__93_92(void);
static void cont__93_93(void);
static NODE *string__2d7981f4e5702ba0;
static void cont__93_95(void);
static NODE *string__578a5af303e9c99;
static void cont__93_97(void);
static NODE *string__578a5af303e9cd1;
static void cont__93_99(void);
static NODE *string__578a5af303e9cb4;
static void cont__93_101(void);
static void cont__93_102(void);
static void cont__93_103(void);
static NODE *string__2d7981f4e5a02ba0;
static void cont__93_105(void);
static NODE *string__578a5af303e9cb8;
static void cont__93_107(void);
static NODE *string__578a5af303e9c91;
static void cont__93_109(void);
static NODE *string__2d7981f4e4902bb6;
static void cont__93_111(void);
static void cont__93_112(void);
static void cont__93_113(void);
static void cont__93_114(void);
static void cont__93_115(void);
static NODE *string__2d7981f4e4002ba0;
static void cont__93_117(void);
static void cont__93_118(void);
static void cont__93_119(void);
static NODE *string__578a5af303e9c82;
static void cont__93_121(void);
static NODE *string__578a5af303e9c84;
static void cont__93_123(void);
static void cont__93_124(void);
static void cont__93_125(void);
static void cont__93_126(void);
static NODE *string__578a5af303e9c88;
static void cont__93_128(void);
static void cont__93_129(void);
static void cont__93_130(void);
static void cont__93_131(void);
static NODE *string__578a5af303e9c85;
static void cont__93_133(void);
static NODE *string__578a5af303e9c8f;
static void cont__93_135(void);
static void cont__93_136(void);
static void cont__93_137(void);
static void cont__93_138(void);
static void cont__93_139(void);
static NODE *string__2d7981f4e4702ba0;
static void cont__93_141(void);
static NODE *string__578a5af303e9cce;
static void cont__93_143(void);
static void cont__93_144(void);
static NODE *string__578a5af303e9c94;
static void cont__93_146(void);
static void cont__93_147(void);
static void cont__93_148(void);
static NODE *string__2d7981f4e4a02ba0;
static void cont__93_150(void);
static NODE *string__578a5af303e9c98;
static void cont__93_152(void);
static void cont__93_153(void);
static void cont__93_154(void);
static void cont__93_155(void);
static void cont__93_156(void);
static void cont__93_157(void);
static void cont__93_158(void);
static void cont__93_159(void);
static void cont__93_160(void);
static void cont__93_161(void);
static void cont__93_162(void);
static void cont__93_163(void);
static void cont__93_164(void);
static void cont__93_165(void);
static void cont__93_166(void);
static void cont__93_167(void);
static void cont__93_168(void);
static void cont__93_169(void);
static void cont__93_170(void);
static void cont__93_171(void);
static void cont__93_172(void);
static void cont__93_173(void);
static void cont__93_174(void);
static void cont__93_175(void);
static void cont__93_176(void);
static void cont__93_177(void);
static void cont__93_178(void);
static void cont__93_179(void);
static void cont__93_180(void);
static void cont__93_181(void);
static void cont__93_182(void);
static NODE *string__578a5af303e9ca6;
static void cont__93_184(void);
static NODE *string__578a5af303e9c86;
static void cont__93_186(void);
static void cont__93_187(void);
static void cont__93_188(void);
static void cont__93_189(void);
static void cont__93_190(void);
static void cont__93_191(void);
static void cont__93_192(void);
static NODE *string__578a5af303e9ca9;
static void cont__93_194(void);
static NODE *string__578a5af303e9c89;
static void cont__93_196(void);
static void cont__93_197(void);
static void cont__93_198(void);
static void cont__93_199(void);
static void cont__93_200(void);
static void cont__93_201(void);
static void cont__93_202(void);
static void cont__93_203(void);
static void cont__93_204(void);
static void cont__93_205(void);
static void cont__93_206(void);
static void cont__93_207(void);
static void cont__93_208(void);
static NODE *string__2d7981f4e5402b8f;
static void cont__93_210(void);
static NODE *string__2d7981f4e4402baf;
static void cont__93_212(void);
static NODE *string__578a5af303e9cab;
static void cont__93_214(void);
static NODE *string__578a5af303e9c8b;
static void cont__93_216(void);
static NODE *string__578a5af303e9caa;
static void cont__93_218(void);
static NODE *string__578a5af303e9c8a;
static void cont__93_220(void);
static void cont__93_221(void);
static NODE *string__578a5af303e9cad;
static void cont__93_223(void);
static NODE *string__578a5af303e9c8d;
static void cont__93_225(void);
static void cont__93_226(void);
static void cont__93_227(void);
static void cont__93_228(void);
static void cont__93_229(void);
static void cont__93_230(void);
static void cont__93_231(void);
static void cont__93_232(void);
static void cont__93_233(void);
static void cont__93_234(void);
static void cont__93_235(void);
static void cont__93_236(void);
static void cont__93_237(void);
static void cont__93_238(void);
static void cont__93_239(void);
static void cont__93_240(void);
static void cont__93_241(void);
static void cont__93_242(void);
static void cont__93_243(void);
static void cont__93_244(void);
static void cont__93_245(void);
static void cont__93_246(void);
static void cont__93_247(void);
static void cont__93_248(void);
static NODE *string__2d7981f4e5702b80;
static void cont__93_250(void);
static void cont__93_251(void);
static NODE *string__578a5af303e9cb3;
static void cont__93_253(void);
static NODE *string__578a5af303e9c93;
static void cont__93_255(void);
static void cont__93_256(void);
static void cont__93_257(void);
static void cont__93_258(void);
static void cont__93_259(void);
static NODE *string__578a5af303e9cb2;
static void cont__93_261(void);
static NODE *string__578a5af303e9c92;
static void cont__93_263(void);
static void cont__93_264(void);
static void cont__93_265(void);
static void cont__93_266(void);
static void cont__93_267(void);
static void cont__93_268(void);
static void cont__93_269(void);
static NODE *string__578a5af303e9cb5;
static void cont__93_271(void);
static NODE *string__578a5af303e9c95;
static void cont__93_273(void);
static void cont__93_274(void);
static void cont__93_275(void);
static void cont__93_276(void);
static void cont__93_277(void);
static void cont__93_278(void);
static void cont__93_279(void);
static void cont__93_280(void);
static void cont__93_281(void);
static void cont__93_282(void);
static void cont__93_283(void);
static void cont__93_284(void);
static void cont__93_285(void);
static void cont__93_286(void);
static void cont__93_287(void);
static void cont__93_288(void);
static void cont__93_289(void);
static NODE *string__578a5af303e9cb6;
static void cont__93_291(void);
static NODE *string__578a5af303e9c96;
static void cont__93_293(void);
static void cont__93_294(void);
static void cont__93_295(void);
static void cont__93_296(void);
static NODE *string__578a5af303e9cbb;
static void cont__93_298(void);
static NODE *string__578a5af303e9c9b;
static void cont__93_300(void);
static void cont__93_301(void);
static void cont__93_302(void);
static void cont__93_303(void);
static void cont__93_304(void);
static void cont__93_305(void);
static NODE *string__578a5af303e9c83;
static void cont__93_307(void);
static NODE *string__578a5af303e9ca3;
static void cont__93_309(void);
static void cont__93_310(void);
static void cont__93_311(void);
static void cont__93_312(void);
static void cont__93_313(void);
static void cont__93_314(void);
static void cont__93_315(void);
static void cont__93_316(void);
static void cont__93_317(void);
static void cont__93_318(void);
static void cont__93_319(void);
static void cont__93_320(void);
static void cont__93_321(void);
static NODE *string__578a5af303e9ca7;
static void cont__93_323(void);
static NODE *string__578a5af303e9c87;
static void cont__93_325(void);
static void cont__93_326(void);
static NODE *string__2d7981f4e5282b9f;
static void cont__93_328(void);
static NODE *string__2d7981f4e5282bbf;
static void cont__93_330(void);
static NODE *string__2d7981f4e4282bbf;
static void cont__93_332(void);
static NODE *string__2d7981f4e5682b8f;
static void cont__93_334(void);
static NODE *string__2d7981f4e5682baf;
static void cont__93_336(void);
static NODE *string__2d7981f4e4682baf;
static void cont__93_338(void);
static NODE *string__2d7981f4e5782b8f;
static void cont__93_340(void);
static NODE *string__2d7981f4e5782baf;
static void cont__93_342(void);
static NODE *string__2d7981f4e4782baf;
static void cont__93_344(void);
static void cont__93_345(void);
static void cont__93_346(void);
static void cont__93_347(void);
static void cont__93_348(void);
static void cont__93_349(void);
static void cont__93_350(void);
static void cont__93_351(void);
static void cont__93_352(void);
static void cont__93_353(void);
static void cont__93_354(void);
static void cont__93_355(void);
static void cont__93_356(void);
static void cont__93_357(void);
static void cont__93_358(void);
static void cont__93_359(void);
static void cont__93_360(void);
static void cont__93_361(void);
static void cont__93_362(void);
static void cont__93_363(void);
static void cont__93_364(void);
static void cont__93_365(void);
static void cont__93_366(void);
static void cont__93_367(void);
static void cont__93_368(void);
static void cont__93_369(void);
static void cont__93_370(void);
static void cont__93_371(void);
static void cont__93_372(void);
static void cont__93_373(void);
static void cont__93_374(void);
static void cont__93_375(void);
static void cont__93_376(void);
static void cont__93_377(void);
static void cont__93_378(void);
static void cont__93_379(void);
static void cont__93_380(void);
static void cont__93_381(void);
static void cont__93_382(void);
static void cont__93_383(void);
static void cont__93_384(void);
static void cont__93_385(void);
static void cont__93_386(void);
static void cont__93_387(void);
static void cont__93_388(void);
static void cont__93_389(void);
static void cont__93_390(void);
void run__basic__types__string(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__types__string, NULL, 747, 747, 5, 18},
  {cont__93_1, NULL, 748, 748, 5, 13},
  {cont__93_3, NULL, 749, 749, 5, 18},
  {cont__93_5, NULL, 750, 750, 5, 19},
  {cont__93_7, NULL, 751, 751, 5, 13},
  {cont__93_9, NULL, 752, 752, 5, 17},
  {cont__93_11, NULL, 753, 753, 5, 13},
  {cont__93_13, NULL, 754, 754, 5, 13},
  {cont__93_15, NULL, 755, 755, 5, 18},
  {cont__93_17, NULL, 756, 756, 5, 15},
  {cont__93_19, NULL, 757, 757, 5, 13},
  {cont__93_21, NULL, 758, 758, 5, 14},
  {cont__93_23, NULL, 759, 759, 5, 17},
  {cont__93_25, NULL, 760, 760, 5, 17},
  {cont__93_27, NULL, 761, 761, 5, 15},
  {cont__93_29, NULL, 762, 762, 5, 13},
  {cont__93_31, NULL, 763, 763, 5, 18},
  {cont__93_33, NULL, 764, 764, 5, 15},
  {cont__93_35, NULL, 765, 765, 5, 14},
  {cont__93_37, NULL, 766, 766, 5, 14},
  {cont__93_39, NULL, 767, 767, 5, 13},
  {cont__93_41, NULL, 768, 768, 5, 16},
  {cont__93_43, NULL, 769, 769, 5, 17},
  {cont__93_45, NULL, 770, 770, 5, 13},
  {cont__93_47, NULL, 771, 771, 5, 13},
  {cont__93_49, NULL, 772, 772, 5, 14},
  {cont__93_51, NULL, 773, 773, 5, 13},
  {cont__93_53, NULL, 774, 774, 5, 14},
  {cont__93_55, NULL, 775, 775, 5, 15},
  {cont__93_57, NULL, 776, 776, 5, 15},
  {cont__93_59, NULL, 777, 777, 5, 15},
  {cont__93_61, NULL, 778, 778, 5, 13},
  {cont__93_62, NULL, 779, 779, 5, 13},
  {cont__93_64, NULL, 780, 780, 5, 13},
  {cont__93_65, NULL, 781, 781, 5, 13},
  {cont__93_66, NULL, 782, 782, 5, 13},
  {cont__93_67, NULL, 783, 783, 5, 14},
  {cont__93_69, NULL, 784, 784, 5, 13},
  {cont__93_70, NULL, 785, 785, 5, 14},
  {cont__93_72, NULL, 786, 786, 5, 13},
  {cont__93_74, NULL, 787, 787, 5, 13},
  {cont__93_76, NULL, 788, 788, 5, 13},
  {cont__93_77, NULL, 789, 789, 5, 13},
  {cont__93_78, NULL, 790, 790, 5, 13},
  {cont__93_79, NULL, 791, 791, 5, 13},
  {cont__93_81, NULL, 792, 792, 5, 13},
  {cont__93_82, NULL, 793, 793, 5, 13},
  {cont__93_83, NULL, 794, 794, 5, 13},
  {cont__93_84, NULL, 795, 795, 5, 13},
  {cont__93_86, NULL, 796, 796, 5, 13},
  {cont__93_88, NULL, 797, 797, 5, 13},
  {cont__93_90, NULL, 798, 798, 5, 13},
  {cont__93_91, NULL, 799, 799, 5, 13},
  {cont__93_92, NULL, 800, 800, 5, 13},
  {cont__93_93, NULL, 801, 801, 5, 14},
  {cont__93_95, NULL, 802, 802, 5, 13},
  {cont__93_97, NULL, 803, 803, 5, 13},
  {cont__93_99, NULL, 804, 804, 5, 13},
  {cont__93_101, NULL, 805, 805, 5, 13},
  {cont__93_102, NULL, 806, 806, 5, 13},
  {cont__93_103, NULL, 807, 807, 5, 14},
  {cont__93_105, NULL, 808, 808, 5, 13},
  {cont__93_107, NULL, 809, 809, 5, 13},
  {cont__93_109, NULL, 810, 810, 5, 14},
  {cont__93_111, NULL, 811, 811, 5, 13},
  {cont__93_112, NULL, 812, 812, 5, 13},
  {cont__93_113, NULL, 813, 813, 5, 13},
  {cont__93_114, NULL, 814, 814, 5, 13},
  {cont__93_115, NULL, 815, 815, 5, 14},
  {cont__93_117, NULL, 816, 816, 5, 13},
  {cont__93_118, NULL, 817, 817, 5, 14},
  {cont__93_119, NULL, 818, 818, 5, 13},
  {cont__93_121, NULL, 819, 819, 5, 13},
  {cont__93_123, NULL, 820, 820, 5, 13},
  {cont__93_124, NULL, 821, 821, 5, 13},
  {cont__93_125, NULL, 822, 822, 5, 13},
  {cont__93_126, NULL, 823, 823, 5, 13},
  {cont__93_128, NULL, 824, 824, 5, 13},
  {cont__93_129, NULL, 825, 825, 5, 13},
  {cont__93_130, NULL, 826, 826, 5, 13},
  {cont__93_131, NULL, 827, 827, 5, 13},
  {cont__93_133, NULL, 828, 828, 5, 13},
  {cont__93_135, NULL, 829, 829, 5, 13},
  {cont__93_136, NULL, 830, 830, 5, 13},
  {cont__93_137, NULL, 831, 831, 5, 13},
  {cont__93_138, NULL, 832, 832, 5, 13},
  {cont__93_139, NULL, 833, 833, 5, 14},
  {cont__93_141, NULL, 834, 834, 5, 13},
  {cont__93_143, NULL, 835, 835, 5, 13},
  {cont__93_144, NULL, 836, 836, 5, 13},
  {cont__93_146, NULL, 837, 837, 5, 13},
  {cont__93_147, NULL, 838, 838, 5, 13},
  {cont__93_148, NULL, 839, 839, 5, 14},
  {cont__93_150, NULL, 840, 840, 5, 13},
  {cont__93_152, NULL, 841, 841, 5, 13},
  {cont__93_153, NULL, 842, 842, 5, 13},
  {cont__93_154, NULL, 843, 843, 5, 13},
  {cont__93_155, NULL, 844, 844, 5, 13},
  {cont__93_156, NULL, 845, 845, 5, 13},
  {cont__93_157, NULL, 846, 846, 5, 13},
  {cont__93_158, NULL, 847, 847, 5, 13},
  {cont__93_159, NULL, 848, 848, 5, 13},
  {cont__93_160, NULL, 849, 849, 5, 13},
  {cont__93_161, NULL, 850, 850, 5, 13},
  {cont__93_162, NULL, 851, 851, 5, 13},
  {cont__93_163, NULL, 852, 852, 5, 13},
  {cont__93_164, NULL, 853, 853, 5, 13},
  {cont__93_165, NULL, 854, 854, 5, 13},
  {cont__93_166, NULL, 855, 855, 5, 13},
  {cont__93_167, NULL, 856, 856, 5, 13},
  {cont__93_168, NULL, 857, 857, 5, 13},
  {cont__93_169, NULL, 858, 858, 5, 13},
  {cont__93_170, NULL, 859, 859, 5, 13},
  {cont__93_171, NULL, 860, 860, 5, 13},
  {cont__93_172, NULL, 861, 861, 5, 13},
  {cont__93_173, NULL, 862, 862, 5, 13},
  {cont__93_174, NULL, 863, 863, 5, 13},
  {cont__93_175, NULL, 864, 864, 5, 13},
  {cont__93_176, NULL, 865, 865, 5, 13},
  {cont__93_177, NULL, 866, 866, 5, 13},
  {cont__93_178, NULL, 867, 867, 5, 13},
  {cont__93_179, NULL, 868, 868, 5, 13},
  {cont__93_180, NULL, 869, 869, 5, 13},
  {cont__93_181, NULL, 870, 870, 5, 13},
  {cont__93_182, NULL, 871, 871, 5, 13},
  {cont__93_184, NULL, 872, 872, 5, 13},
  {cont__93_186, NULL, 873, 873, 5, 13},
  {cont__93_187, NULL, 874, 874, 5, 13},
  {cont__93_188, NULL, 875, 875, 5, 13},
  {cont__93_189, NULL, 876, 876, 5, 13},
  {cont__93_190, NULL, 877, 877, 5, 13},
  {cont__93_191, NULL, 878, 878, 5, 13},
  {cont__93_192, NULL, 879, 879, 5, 13},
  {cont__93_194, NULL, 880, 880, 5, 13},
  {cont__93_196, NULL, 881, 881, 5, 13},
  {cont__93_197, NULL, 882, 882, 5, 13},
  {cont__93_198, NULL, 883, 883, 5, 13},
  {cont__93_199, NULL, 884, 884, 5, 13},
  {cont__93_200, NULL, 885, 885, 5, 13},
  {cont__93_201, NULL, 886, 886, 5, 13},
  {cont__93_202, NULL, 887, 887, 5, 13},
  {cont__93_203, NULL, 888, 888, 5, 13},
  {cont__93_204, NULL, 889, 889, 5, 13},
  {cont__93_205, NULL, 890, 890, 5, 13},
  {cont__93_206, NULL, 891, 891, 5, 13},
  {cont__93_207, NULL, 892, 892, 5, 13},
  {cont__93_208, NULL, 893, 893, 5, 14},
  {cont__93_210, NULL, 894, 894, 5, 14},
  {cont__93_212, NULL, 895, 895, 5, 13},
  {cont__93_214, NULL, 896, 896, 5, 13},
  {cont__93_216, NULL, 897, 897, 5, 13},
  {cont__93_218, NULL, 898, 898, 5, 13},
  {cont__93_220, NULL, 899, 899, 5, 13},
  {cont__93_221, NULL, 900, 900, 5, 13},
  {cont__93_223, NULL, 901, 901, 5, 13},
  {cont__93_225, NULL, 902, 902, 5, 13},
  {cont__93_226, NULL, 903, 903, 5, 13},
  {cont__93_227, NULL, 904, 904, 5, 13},
  {cont__93_228, NULL, 905, 905, 5, 13},
  {cont__93_229, NULL, 906, 906, 5, 13},
  {cont__93_230, NULL, 907, 907, 5, 13},
  {cont__93_231, NULL, 908, 908, 5, 13},
  {cont__93_232, NULL, 909, 909, 5, 13},
  {cont__93_233, NULL, 910, 910, 5, 13},
  {cont__93_234, NULL, 911, 911, 5, 13},
  {cont__93_235, NULL, 912, 912, 5, 13},
  {cont__93_236, NULL, 913, 913, 5, 13},
  {cont__93_237, NULL, 914, 914, 5, 13},
  {cont__93_238, NULL, 915, 915, 5, 13},
  {cont__93_239, NULL, 916, 916, 5, 13},
  {cont__93_240, NULL, 917, 917, 5, 13},
  {cont__93_241, NULL, 918, 918, 5, 13},
  {cont__93_242, NULL, 919, 919, 5, 13},
  {cont__93_243, NULL, 920, 920, 5, 13},
  {cont__93_244, NULL, 921, 921, 5, 13},
  {cont__93_245, NULL, 922, 922, 5, 13},
  {cont__93_246, NULL, 923, 923, 5, 13},
  {cont__93_247, NULL, 924, 924, 5, 13},
  {cont__93_248, NULL, 925, 925, 5, 14},
  {cont__93_250, NULL, 926, 926, 5, 14},
  {cont__93_251, NULL, 927, 927, 5, 13},
  {cont__93_253, NULL, 928, 928, 5, 13},
  {cont__93_255, NULL, 929, 929, 5, 13},
  {cont__93_256, NULL, 930, 930, 5, 13},
  {cont__93_257, NULL, 931, 931, 5, 13},
  {cont__93_258, NULL, 932, 932, 5, 13},
  {cont__93_259, NULL, 933, 933, 5, 13},
  {cont__93_261, NULL, 934, 934, 5, 13},
  {cont__93_263, NULL, 935, 935, 5, 13},
  {cont__93_264, NULL, 936, 936, 5, 13},
  {cont__93_265, NULL, 937, 937, 5, 13},
  {cont__93_266, NULL, 938, 938, 5, 13},
  {cont__93_267, NULL, 939, 939, 5, 13},
  {cont__93_268, NULL, 940, 940, 5, 13},
  {cont__93_269, NULL, 941, 941, 5, 13},
  {cont__93_271, NULL, 942, 942, 5, 13},
  {cont__93_273, NULL, 943, 943, 5, 13},
  {cont__93_274, NULL, 944, 944, 5, 13},
  {cont__93_275, NULL, 945, 945, 5, 13},
  {cont__93_276, NULL, 946, 946, 5, 13},
  {cont__93_277, NULL, 947, 947, 5, 13},
  {cont__93_278, NULL, 948, 948, 5, 13},
  {cont__93_279, NULL, 949, 949, 5, 13},
  {cont__93_280, NULL, 950, 950, 5, 13},
  {cont__93_281, NULL, 951, 951, 5, 13},
  {cont__93_282, NULL, 952, 952, 5, 13},
  {cont__93_283, NULL, 953, 953, 5, 13},
  {cont__93_284, NULL, 954, 954, 5, 13},
  {cont__93_285, NULL, 955, 955, 5, 13},
  {cont__93_286, NULL, 956, 956, 5, 13},
  {cont__93_287, NULL, 957, 957, 5, 13},
  {cont__93_288, NULL, 958, 958, 5, 13},
  {cont__93_289, NULL, 959, 959, 5, 13},
  {cont__93_291, NULL, 960, 960, 5, 13},
  {cont__93_293, NULL, 961, 961, 5, 13},
  {cont__93_294, NULL, 962, 962, 5, 13},
  {cont__93_295, NULL, 963, 963, 5, 13},
  {cont__93_296, NULL, 964, 964, 5, 13},
  {cont__93_298, NULL, 965, 965, 5, 13},
  {cont__93_300, NULL, 966, 966, 5, 13},
  {cont__93_301, NULL, 967, 967, 5, 13},
  {cont__93_302, NULL, 968, 968, 5, 13},
  {cont__93_303, NULL, 969, 969, 5, 13},
  {cont__93_304, NULL, 970, 970, 5, 13},
  {cont__93_305, NULL, 971, 971, 5, 13},
  {cont__93_307, NULL, 972, 972, 5, 13},
  {cont__93_309, NULL, 973, 973, 5, 13},
  {cont__93_310, NULL, 974, 974, 5, 13},
  {cont__93_311, NULL, 975, 975, 5, 13},
  {cont__93_312, NULL, 976, 976, 5, 13},
  {cont__93_313, NULL, 977, 977, 5, 13},
  {cont__93_314, NULL, 978, 978, 5, 13},
  {cont__93_315, NULL, 979, 979, 5, 13},
  {cont__93_316, NULL, 980, 980, 5, 13},
  {cont__93_317, NULL, 981, 981, 5, 13},
  {cont__93_318, NULL, 982, 982, 5, 13},
  {cont__93_319, NULL, 983, 983, 5, 13},
  {cont__93_320, NULL, 984, 984, 5, 13},
  {cont__93_321, NULL, 985, 985, 5, 13},
  {cont__93_323, NULL, 986, 986, 5, 13},
  {cont__93_325, NULL, 987, 987, 5, 13},
  {cont__93_326, NULL, 988, 988, 5, 14},
  {cont__93_328, NULL, 989, 989, 5, 14},
  {cont__93_330, NULL, 990, 990, 5, 14},
  {cont__93_332, NULL, 991, 991, 5, 14},
  {cont__93_334, NULL, 992, 992, 5, 14},
  {cont__93_336, NULL, 993, 993, 5, 14},
  {cont__93_338, NULL, 994, 994, 5, 14},
  {cont__93_340, NULL, 995, 995, 5, 14},
  {cont__93_342, NULL, 996, 996, 5, 14},
  {cont__93_344, NULL, 997, 997, 5, 13},
  {cont__93_345, NULL, 998, 998, 5, 13},
  {cont__93_346, NULL, 999, 999, 5, 13},
  {cont__93_347, NULL, 1000, 1000, 5, 13},
  {cont__93_348, NULL, 1001, 1001, 5, 13},
  {cont__93_349, NULL, 1002, 1002, 5, 13},
  {cont__93_350, NULL, 1003, 1003, 5, 13},
  {cont__93_351, NULL, 1004, 1004, 5, 13},
  {cont__93_352, NULL, 1005, 1005, 5, 13},
  {cont__93_353, NULL, 1006, 1006, 5, 13},
  {cont__93_354, NULL, 1007, 1007, 5, 13},
  {cont__93_355, NULL, 1008, 1008, 5, 13},
  {cont__93_356, NULL, 1009, 1009, 5, 13},
  {cont__93_357, NULL, 1010, 1010, 5, 13},
  {cont__93_358, NULL, 1011, 1011, 5, 13},
  {cont__93_359, NULL, 1012, 1012, 5, 13},
  {cont__93_360, NULL, 1013, 1013, 5, 13},
  {cont__93_361, NULL, 1014, 1014, 5, 13},
  {cont__93_362, NULL, 1015, 1015, 5, 13},
  {cont__93_363, NULL, 1016, 1016, 5, 13},
  {cont__93_364, NULL, 1017, 1017, 5, 14},
  {cont__93_365, NULL, 1018, 1018, 5, 14},
  {cont__93_366, NULL, 1019, 1019, 5, 13},
  {cont__93_367, NULL, 1020, 1020, 5, 13},
  {cont__93_368, NULL, 1021, 1021, 5, 13},
  {cont__93_369, NULL, 1022, 1022, 5, 13},
  {cont__93_370, NULL, 1023, 1023, 5, 13},
  {cont__93_371, NULL, 1024, 1024, 5, 13},
  {cont__93_372, NULL, 1025, 1025, 5, 13},
  {cont__93_373, NULL, 1026, 1026, 5, 13},
  {cont__93_374, NULL, 1027, 1027, 5, 13},
  {cont__93_375, NULL, 1028, 1028, 5, 13},
  {cont__93_376, NULL, 1029, 1029, 5, 14},
  {cont__93_377, NULL, 1030, 1030, 5, 14},
  {cont__93_378, NULL, 1031, 1031, 5, 14},
  {cont__93_379, NULL, 1032, 1032, 5, 13},
  {cont__93_380, NULL, 1033, 1033, 5, 13},
  {cont__93_381, NULL, 1034, 1034, 5, 13},
  {cont__93_382, NULL, 1035, 1035, 5, 13},
  {cont__93_383, NULL, 1036, 1036, 5, 13},
  {cont__93_384, NULL, 1037, 1037, 5, 13},
  {cont__93_385, NULL, 1038, 1038, 5, 14},
  {cont__93_386, NULL, 1039, 1039, 5, 14},
  {cont__93_387, NULL, 1040, 1040, 5, 13},
  {cont__93_388, NULL, 1041, 1041, 5, 13},
  {cont__93_389, NULL, 745, 1041, 1, 14},
  {cont__93_390, NULL, },
  {entry__types__string__to_integer_5, NULL, 45, 45, 18, 33},
  {entry__types__string__to_integer_1, NULL, 44, 44, 3, 28},
  {cont__types__string__to_integer_2, &frame__types__string__to_integer_1, 45, 45, 6, 15},
  {cont__types__string__to_integer_3, &frame__types__string__to_integer_1, 45, 45, 6, 15},
  {cont__types__string__to_integer_4, &frame__types__string__to_integer_1, 45, 45, 3, 33},
  {cont__types__string__to_integer_6, &frame__types__string__to_integer_1, 46, 46, 3, 10},
  {entry__types__string__to_real_5, NULL, 56, 56, 18, 33},
  {entry__types__string__to_real_1, NULL, 55, 55, 3, 25},
  {cont__types__string__to_real_2, &frame__types__string__to_real_1, 56, 56, 6, 15},
  {cont__types__string__to_real_3, &frame__types__string__to_real_1, 56, 56, 6, 15},
  {cont__types__string__to_real_4, &frame__types__string__to_real_1, 56, 56, 3, 33},
  {cont__types__string__to_real_6, &frame__types__string__to_real_1, 57, 57, 3, 10},
  {entry__types__string__parse_number_5, NULL, 67, 67, 22, 27},
  {cont__types__string__parse_number_6, &frame__types__string__parse_number_5, 67, 67, 27, 27},
  {entry__types__string__parse_number_11, NULL, 68, 68, 22, 28},
  {cont__types__string__parse_number_12, &frame__types__string__parse_number_11, 68, 68, 22, 39},
  {cont__types__string__parse_number_13, &frame__types__string__parse_number_11, 68, 68, 22, 39},
  {entry__types__string__parse_number_15, NULL, 68, 68, 42, 47},
  {cont__types__string__parse_number_16, &frame__types__string__parse_number_15, 68, 68, 47, 47},
  {entry__types__string__parse_number_8, NULL, 68, 68, 12, 17},
  {cont__types__string__parse_number_9, &frame__types__string__parse_number_8, 68, 68, 12, 17},
  {cont__types__string__parse_number_10, &frame__types__string__parse_number_8, 68, 68, 12, 39},
  {cont__types__string__parse_number_14, &frame__types__string__parse_number_8, 68, 68, 9, 47},
  {entry__types__string__parse_number_20, NULL, 70, 70, 15, 21},
  {cont__types__string__parse_number_21, &frame__types__string__parse_number_20, 70, 70, 15, 28},
  {cont__types__string__parse_number_22, &frame__types__string__parse_number_20, 70, 70, 15, 28},
  {entry__types__string__parse_number_24, NULL, 71, 71, 7, 21},
  {entry__types__string__parse_number_25, NULL, 73, 73, 7, 24},
  {entry__types__string__parse_number_1, NULL, 66, 66, 3, 20},
  {cont__types__string__parse_number_2, &frame__types__string__parse_number_1, 67, 67, 6, 12},
  {cont__types__string__parse_number_3, &frame__types__string__parse_number_1, 67, 67, 6, 19},
  {cont__types__string__parse_number_4, &frame__types__string__parse_number_1, 67, 67, 3, 27},
  {cont__types__string__parse_number_7, &frame__types__string__parse_number_1, 68, 68, 3, 47},
  {cont__types__string__parse_number_17, &frame__types__string__parse_number_1, 70, 70, 5, 10},
  {cont__types__string__parse_number_18, &frame__types__string__parse_number_1, 70, 70, 5, 10},
  {cont__types__string__parse_number_19, &frame__types__string__parse_number_1, 70, 70, 5, 28},
  {cont__types__string__parse_number_23, &frame__types__string__parse_number_1, 69, 73, 3, 25},
  {entry__types__string__to_number_5, NULL, 83, 83, 18, 33},
  {entry__types__string__to_number_1, NULL, 82, 82, 3, 27},
  {cont__types__string__to_number_2, &frame__types__string__to_number_1, 83, 83, 6, 15},
  {cont__types__string__to_number_3, &frame__types__string__to_number_1, 83, 83, 6, 15},
  {cont__types__string__to_number_4, &frame__types__string__to_number_1, 83, 83, 3, 33},
  {cont__types__string__to_number_6, &frame__types__string__to_number_1, 84, 84, 3, 10},
  {entry__types__string__put_1, NULL, 93, 93, 13, 25},
  {cont__types__string__put_2, &frame__types__string__put_1, 93, 93, 6, 31},
  {cont__types__string__put_3, &frame__types__string__put_1, 93, 93, 3, 31},
  {entry__types__string__write_to_2, NULL, 102, 102, 37, 49},
  {cont__types__string__write_to_3, &frame__types__string__write_to_2, 102, 102, 24, 49},
  {cont__types__string__write_to_4, &frame__types__string__write_to_2, 102, 102, 49, 49},
  {entry__types__string__write_to_1, NULL, 102, 102, 3, 49},
  {cont__types__string__write_to_5, &frame__types__string__write_to_1, },
  {entry__types__string__numerically_less_19, NULL, 123, 123, 11, 26},
  {cont__types__string__numerically_less_20, &frame__types__string__numerically_less_19, 123, 123, 11, 26},
  {cont__types__string__numerically_less_21, &frame__types__string__numerically_less_19, 123, 123, 11, 26},
  {entry__types__string__numerically_less_16, NULL, 122, 122, 11, 26},
  {cont__types__string__numerically_less_17, &frame__types__string__numerically_less_16, 122, 122, 11, 26},
  {cont__types__string__numerically_less_18, &frame__types__string__numerically_less_16, 123, 123, 11, 26},
  {cont__types__string__numerically_less_22, &frame__types__string__numerically_less_16, },
  {entry__types__string__numerically_less_13, NULL, 121, 121, 11, 25},
  {cont__types__string__numerically_less_14, &frame__types__string__numerically_less_13, 121, 121, 11, 25},
  {cont__types__string__numerically_less_15, &frame__types__string__numerically_less_13, },
  {cont__types__string__numerically_less_23, &frame__types__string__numerically_less_13, },
  {entry__types__string__numerically_less_30, NULL, 128, 128, 32, 38},
  {cont__types__string__numerically_less_31, &frame__types__string__numerically_less_30, 128, 128, 32, 49},
  {cont__types__string__numerically_less_32, &frame__types__string__numerically_less_30, 128, 128, 32, 49},
  {entry__types__string__numerically_less_37, NULL, 130, 130, 37, 44},
  {cont__types__string__numerically_less_38, &frame__types__string__numerically_less_37, 130, 130, 37, 55},
  {cont__types__string__numerically_less_39, &frame__types__string__numerically_less_37, 130, 130, 37, 55},
  {entry__types__string__numerically_less_41, NULL, 131, 131, 21, 26},
  {cont__types__string__numerically_less_42, &frame__types__string__numerically_less_41, 131, 131, 26, 26},
  {entry__types__string__numerically_less_43, NULL, 133, 133, 21, 32},
  {entry__types__string__numerically_less_34, NULL, 130, 130, 19, 32},
  {cont__types__string__numerically_less_35, &frame__types__string__numerically_less_34, 130, 130, 19, 32},
  {cont__types__string__numerically_less_36, &frame__types__string__numerically_less_34, 130, 130, 19, 55},
  {cont__types__string__numerically_less_40, &frame__types__string__numerically_less_34, 129, 133, 17, 33},
  {entry__types__string__numerically_less_47, NULL, 136, 136, 37, 44},
  {cont__types__string__numerically_less_48, &frame__types__string__numerically_less_47, 136, 136, 37, 55},
  {cont__types__string__numerically_less_49, &frame__types__string__numerically_less_47, 136, 136, 37, 55},
  {entry__types__string__numerically_less_51, NULL, 137, 137, 21, 31},
  {entry__types__string__numerically_less_52, NULL, 139, 139, 28, 47},
  {cont__types__string__numerically_less_53, &frame__types__string__numerically_less_52, 139, 139, 21, 47},
  {entry__types__string__numerically_less_44, NULL, 136, 136, 19, 32},
  {cont__types__string__numerically_less_45, &frame__types__string__numerically_less_44, 136, 136, 19, 32},
  {cont__types__string__numerically_less_46, &frame__types__string__numerically_less_44, 136, 136, 19, 55},
  {cont__types__string__numerically_less_50, &frame__types__string__numerically_less_44, 135, 139, 17, 48},
  {entry__types__string__numerically_less_27, NULL, 128, 128, 15, 27},
  {cont__types__string__numerically_less_28, &frame__types__string__numerically_less_27, 128, 128, 15, 27},
  {cont__types__string__numerically_less_29, &frame__types__string__numerically_less_27, 128, 128, 15, 49},
  {cont__types__string__numerically_less_33, &frame__types__string__numerically_less_27, 127, 139, 13, 50},
  {entry__types__string__numerically_less_25, NULL, 125, 125, 11, 17},
  {cont__types__string__numerically_less_26, &frame__types__string__numerically_less_25, 126, 139, 11, 51},
  {entry__types__string__numerically_less_54, NULL, 141, 141, 18, 37},
  {cont__types__string__numerically_less_55, &frame__types__string__numerically_less_54, 141, 141, 11, 37},
  {entry__types__string__numerically_less_10, NULL, 120, 120, 11, 25},
  {cont__types__string__numerically_less_11, &frame__types__string__numerically_less_10, 120, 120, 11, 25},
  {cont__types__string__numerically_less_12, &frame__types__string__numerically_less_10, },
  {cont__types__string__numerically_less_24, &frame__types__string__numerically_less_10, 118, 141, 7, 38},
  {cont__types__string__numerically_less_56, &frame__types__string__numerically_less_10, 142, 142, 14, 33},
  {cont__types__string__numerically_less_57, &frame__types__string__numerically_less_10, 142, 142, 7, 33},
  {entry__types__string__numerically_less_5, NULL, 115, 115, 5, 21},
  {cont__types__string__numerically_less_6, &frame__types__string__numerically_less_5, 116, 116, 5, 23},
  {cont__types__string__numerically_less_7, &frame__types__string__numerically_less_5, 117, 117, 8, 28},
  {cont__types__string__numerically_less_8, &frame__types__string__numerically_less_5, 117, 117, 8, 28},
  {cont__types__string__numerically_less_9, &frame__types__string__numerically_less_5, 117, 142, 5, 33},
  {entry__types__string__numerically_less_1, NULL, 112, 112, 3, 27},
  {cont__types__string__numerically_less_2, &frame__types__string__numerically_less_1, 113, 113, 3, 29},
  {cont__types__string__numerically_less_3, &frame__types__string__numerically_less_1, 114, 114, 13, 35},
  {cont__types__string__numerically_less_4, &frame__types__string__numerically_less_1, 114, 142, 3, 34},
  {cont__types__string__numerically_less_58, &frame__types__string__numerically_less_1, 142, 142, 34, 34},
  {entry__types__string__to_list_2, NULL, 151, 151, 25, 40},
  {cont__types__string__to_list_3, &frame__types__string__to_list_2, 151, 151, 40, 40},
  {entry__types__string__to_list_1, NULL, 151, 151, 3, 40},
  {cont__types__string__to_list_4, &frame__types__string__to_list_1, 152, 152, 3, 10},
  {entry__std__string_3, NULL, 162, 162, 42, 48},
  {cont__std__string_4, &frame__std__string_3, 162, 162, 32, 49},
  {cont__std__string_5, &frame__std__string_3, 162, 162, 20, 49},
  {cont__std__string_6, &frame__std__string_3, 162, 162, 49, 49},
  {entry__std__string_1, NULL, 161, 161, 3, 20},
  {cont__std__string_2, &frame__std__string_1, 162, 162, 3, 49},
  {cont__std__string_7, &frame__std__string_1, 163, 163, 3, 8},
  {entry__types__string__dup_2, NULL, 176, 176, 7, 15},
  {entry__types__string__dup_3, NULL, 178, 178, 7, 17},
  {entry__types__string__dup_6, NULL, 180, 180, 17, 50},
  {entry__types__string__dup_13, NULL, 185, 185, 18, 32},
  {cont__types__string__dup_14, &frame__types__string__dup_13, 185, 185, 11, 32},
  {entry__types__string__dup_15, NULL, 187, 187, 18, 37},
  {cont__types__string__dup_16, &frame__types__string__dup_15, 187, 187, 11, 37},
  {entry__types__string__dup_4, NULL, 180, 180, 10, 14},
  {cont__types__string__dup_5, &frame__types__string__dup_4, 180, 180, 7, 50},
  {cont__types__string__dup_8, &frame__types__string__dup_4, 181, 181, 7, 18},
  {cont__types__string__dup_9, &frame__types__string__dup_4, 182, 182, 7, 22},
  {cont__types__string__dup_10, &frame__types__string__dup_4, 184, 184, 9, 11},
  {cont__types__string__dup_11, &frame__types__string__dup_4, 184, 184, 9, 16},
  {cont__types__string__dup_12, &frame__types__string__dup_4, 183, 187, 7, 38},
  {entry__types__string__dup_1, NULL, 173, 187, 3, 40},
  {cont__types__string__dup_17, &frame__types__string__dup_1, 187, 187, 40, 40},
  {entry__std__pad_left_6, NULL, 207, 207, 5, 27},
  {cont__std__pad_left_7, &frame__std__pad_left_6, 208, 208, 33, 37},
  {cont__std__pad_left_8, &frame__std__pad_left_6, 208, 208, 33, 45},
  {cont__std__pad_left_9, &frame__std__pad_left_6, 208, 208, 33, 47},
  {cont__std__pad_left_10, &frame__std__pad_left_6, 208, 208, 33, 61},
  {cont__std__pad_left_11, &frame__std__pad_left_6, 208, 208, 25, 62},
  {cont__std__pad_left_12, &frame__std__pad_left_6, 208, 208, 66, 70},
  {cont__std__pad_left_13, &frame__std__pad_left_6, 208, 208, 19, 71},
  {cont__std__pad_left_14, &frame__std__pad_left_6, 208, 208, 12, 77},
  {cont__std__pad_left_15, &frame__std__pad_left_6, 208, 208, 5, 77},
  {entry__std__pad_left_1, NULL, 204, 204, 3, 22},
  {cont__std__pad_left_3, &frame__std__pad_left_1, 205, 205, 3, 22},
  {cont__std__pad_left_4, &frame__std__pad_left_1, 206, 206, 6, 12},
  {cont__std__pad_left_5, &frame__std__pad_left_1, 206, 208, 3, 77},
  {cont__std__pad_left_16, &frame__std__pad_left_1, 209, 209, 3, 9},
  {entry__std__pad_right_5, NULL, 229, 229, 5, 27},
  {cont__std__pad_right_6, &frame__std__pad_right_5, 230, 230, 38, 42},
  {cont__std__pad_right_7, &frame__std__pad_right_5, 230, 230, 38, 50},
  {cont__std__pad_right_8, &frame__std__pad_right_5, 230, 230, 38, 52},
  {cont__std__pad_right_9, &frame__std__pad_right_5, 230, 230, 38, 66},
  {cont__std__pad_right_10, &frame__std__pad_right_5, 230, 230, 30, 67},
  {cont__std__pad_right_11, &frame__std__pad_right_5, 230, 230, 71, 75},
  {cont__std__pad_right_12, &frame__std__pad_right_5, 230, 230, 24, 76},
  {cont__std__pad_right_13, &frame__std__pad_right_5, 230, 230, 12, 77},
  {cont__std__pad_right_14, &frame__std__pad_right_5, 230, 230, 5, 77},
  {entry__std__pad_right_1, NULL, 226, 226, 3, 22},
  {cont__std__pad_right_2, &frame__std__pad_right_1, 227, 227, 3, 22},
  {cont__std__pad_right_3, &frame__std__pad_right_1, 228, 228, 6, 12},
  {cont__std__pad_right_4, &frame__std__pad_right_1, 228, 230, 3, 77},
  {cont__std__pad_right_15, &frame__std__pad_right_1, 231, 231, 3, 9},
  {entry__std__truncate_5, NULL, 247, 247, 15, 21},
  {entry__std__truncate_6, NULL, 247, 247, 27, 41},
  {cont__std__truncate_7, &frame__std__truncate_6, 247, 247, 24, 41},
  {entry__std__truncate_1, NULL, 245, 245, 3, 22},
  {cont__std__truncate_2, &frame__std__truncate_1, 246, 246, 3, 22},
  {cont__std__truncate_3, &frame__std__truncate_1, 247, 247, 6, 12},
  {cont__std__truncate_4, &frame__std__truncate_1, 247, 247, 3, 41},
  {entry__std__pad_or_truncate_5, NULL, 264, 264, 38, 42},
  {cont__std__pad_or_truncate_6, &frame__std__pad_or_truncate_5, 264, 264, 30, 43},
  {cont__std__pad_or_truncate_7, &frame__std__pad_or_truncate_5, 264, 264, 18, 44},
  {cont__std__pad_or_truncate_8, &frame__std__pad_or_truncate_5, 264, 264, 15, 44},
  {entry__std__pad_or_truncate_9, NULL, 264, 264, 50, 64},
  {cont__std__pad_or_truncate_10, &frame__std__pad_or_truncate_9, 264, 264, 47, 64},
  {entry__std__pad_or_truncate_1, NULL, 262, 262, 3, 22},
  {cont__std__pad_or_truncate_2, &frame__std__pad_or_truncate_1, 263, 263, 3, 22},
  {cont__std__pad_or_truncate_3, &frame__std__pad_or_truncate_1, 264, 264, 6, 12},
  {cont__std__pad_or_truncate_4, &frame__std__pad_or_truncate_1, 264, 264, 3, 64},
  {entry__types__string__match_character_4, NULL, 273, 273, 29, 35},
  {cont__types__string__match_character_5, &frame__types__string__match_character_4, 273, 273, 29, 42},
  {cont__types__string__match_character_6, &frame__types__string__match_character_4, 273, 273, 29, 42},
  {entry__types__string__match_character_8, NULL, 273, 273, 45, 48},
  {entry__types__string__match_character_9, NULL, 273, 273, 51, 62},
  {entry__types__string__match_character_1, NULL, 273, 273, 6, 20},
  {cont__types__string__match_character_2, &frame__types__string__match_character_1, 273, 273, 6, 24},
  {cont__types__string__match_character_3, &frame__types__string__match_character_1, 273, 273, 6, 42},
  {cont__types__string__match_character_7, &frame__types__string__match_character_1, 273, 273, 3, 62},
  {entry__types__string__grammar__match_4, NULL, 284, 284, 43, 58},
  {entry__types__string__grammar__match_8, NULL, 285, 285, 35, 44},
  {entry__types__string__grammar__match_1, NULL, 283, 283, 3, 22},
  {cont__types__string__grammar__match_2, &frame__types__string__grammar__match_1, 284, 284, 10, 40},
  {cont__types__string__grammar__match_3, &frame__types__string__grammar__match_1, 284, 284, 3, 58},
  {cont__types__string__grammar__match_5, &frame__types__string__grammar__match_1, 285, 285, 6, 24},
  {cont__types__string__grammar__match_6, &frame__types__string__grammar__match_1, 285, 285, 6, 32},
  {cont__types__string__grammar__match_7, &frame__types__string__grammar__match_1, 285, 285, 3, 44},
  {cont__types__string__grammar__match_9, &frame__types__string__grammar__match_1, 286, 286, 3, 14},
  {entry__types__string__match_5, NULL, 298, 298, 39, 68},
  {entry__types__string__match_1, NULL, 297, 297, 3, 32},
  {cont__types__string__match_2, &frame__types__string__match_1, 298, 298, 6, 31},
  {cont__types__string__match_3, &frame__types__string__match_1, 298, 298, 6, 36},
  {cont__types__string__match_4, &frame__types__string__match_1, 298, 298, 3, 68},
  {cont__types__string__match_6, &frame__types__string__match_1, 299, 299, 3, 6},
  {entry__types__string__search_character_6, NULL, 313, 313, 12, 16},
  {cont__types__string__search_character_7, &frame__types__string__search_character_6, 313, 313, 9, 16},
  {entry__types__string__search_character_8, NULL, 314, 314, 43, 43},
  {cont__types__string__search_character_9, &frame__types__string__search_character_8, 314, 314, 29, 44},
  {cont__types__string__search_character_10, &frame__types__string__search_character_8, 314, 314, 50, 54},
  {cont__types__string__search_character_11, &frame__types__string__search_character_8, 314, 314, 12, 55},
  {cont__types__string__search_character_12, &frame__types__string__search_character_8, 314, 314, 9, 55},
  {entry__types__string__search_character_3, NULL, 312, 312, 9, 15},
  {cont__types__string__search_character_4, &frame__types__string__search_character_3, 312, 312, 9, 22},
  {cont__types__string__search_character_5, &frame__types__string__search_character_3, 311, 314, 7, 55},
  {entry__types__string__search_character_13, NULL, 315, 315, 5, 16},
  {entry__types__string__search_character_1, NULL, 310, 310, 5, 31},
  {cont__types__string__search_character_2, &frame__types__string__search_character_1, 309, 315, 3, 16},
  {entry__types__string__search_1, NULL, 331, 331, 3, 39},
  {cont__types__string__search_2, &frame__types__string__search_1, 332, 332, 3, 12},
  {entry__types__string__before_4, NULL, 370, 370, 26, 30},
  {cont__types__string__before_5, &frame__types__string__before_4, 370, 370, 14, 31},
  {cont__types__string__before_6, &frame__types__string__before_4, 370, 370, 7, 31},
  {entry__types__string__before_7, NULL, 372, 372, 7, 15},
  {entry__types__string__before_1, NULL, 367, 367, 3, 41},
  {cont__types__string__before_2, &frame__types__string__before_1, 369, 369, 5, 18},
  {cont__types__string__before_3, &frame__types__string__before_1, 368, 372, 3, 16},
  {cont__types__string__before_8, &frame__types__string__before_1, 372, 372, 16, 16},
  {entry__types__string__truncate_from_4, NULL, 401, 401, 26, 30},
  {cont__types__string__truncate_from_5, &frame__types__string__truncate_from_4, 401, 401, 14, 31},
  {cont__types__string__truncate_from_6, &frame__types__string__truncate_from_4, 401, 401, 7, 31},
  {entry__types__string__truncate_from_7, NULL, 403, 403, 7, 16},
  {entry__types__string__truncate_from_1, NULL, 398, 398, 3, 41},
  {cont__types__string__truncate_from_2, &frame__types__string__truncate_from_1, 400, 400, 5, 18},
  {cont__types__string__truncate_from_3, &frame__types__string__truncate_from_1, 399, 403, 3, 17},
  {cont__types__string__truncate_from_8, &frame__types__string__truncate_from_1, 403, 403, 17, 17},
  {entry__types__string__behind_4, NULL, 439, 439, 24, 30},
  {cont__types__string__behind_5, &frame__types__string__behind_4, 439, 439, 33, 33},
  {cont__types__string__behind_6, &frame__types__string__behind_4, 439, 439, 14, 34},
  {cont__types__string__behind_7, &frame__types__string__behind_4, 439, 439, 7, 34},
  {entry__types__string__behind_8, NULL, 441, 441, 7, 15},
  {entry__types__string__behind_1, NULL, 436, 436, 3, 40},
  {cont__types__string__behind_2, &frame__types__string__behind_1, 438, 438, 5, 18},
  {cont__types__string__behind_3, &frame__types__string__behind_1, 437, 441, 3, 16},
  {cont__types__string__behind_9, &frame__types__string__behind_1, 441, 441, 16, 16},
  {entry__types__string__truncate_until_4, NULL, 470, 470, 24, 30},
  {cont__types__string__truncate_until_5, &frame__types__string__truncate_until_4, 470, 470, 33, 33},
  {cont__types__string__truncate_until_6, &frame__types__string__truncate_until_4, 470, 470, 14, 34},
  {cont__types__string__truncate_until_7, &frame__types__string__truncate_until_4, 470, 470, 7, 34},
  {entry__types__string__truncate_until_8, NULL, 472, 472, 7, 16},
  {entry__types__string__truncate_until_1, NULL, 467, 467, 3, 40},
  {cont__types__string__truncate_until_2, &frame__types__string__truncate_until_1, 469, 469, 5, 18},
  {cont__types__string__truncate_until_3, &frame__types__string__truncate_until_1, 468, 472, 3, 17},
  {cont__types__string__truncate_until_9, &frame__types__string__truncate_until_1, 472, 472, 17, 17},
  {entry__types__string__from_4, NULL, 504, 504, 29, 29},
  {cont__types__string__from_5, &frame__types__string__from_4, 504, 504, 14, 30},
  {cont__types__string__from_6, &frame__types__string__from_4, 504, 504, 7, 30},
  {entry__types__string__from_7, NULL, 506, 506, 7, 15},
  {entry__types__string__from_1, NULL, 501, 501, 3, 41},
  {cont__types__string__from_2, &frame__types__string__from_1, 503, 503, 5, 18},
  {cont__types__string__from_3, &frame__types__string__from_1, 502, 506, 3, 16},
  {cont__types__string__from_8, &frame__types__string__from_1, 506, 506, 16, 16},
  {entry__types__string__truncate_before_4, NULL, 526, 526, 29, 29},
  {cont__types__string__truncate_before_5, &frame__types__string__truncate_before_4, 526, 526, 14, 30},
  {cont__types__string__truncate_before_6, &frame__types__string__truncate_before_4, 526, 526, 7, 30},
  {entry__types__string__truncate_before_7, NULL, 528, 528, 7, 16},
  {entry__types__string__truncate_before_1, NULL, 523, 523, 3, 41},
  {cont__types__string__truncate_before_2, &frame__types__string__truncate_before_1, 525, 525, 5, 18},
  {cont__types__string__truncate_before_3, &frame__types__string__truncate_before_1, 524, 528, 3, 17},
  {cont__types__string__truncate_before_8, &frame__types__string__truncate_before_1, 528, 528, 17, 17},
  {entry__types__string__until_4, NULL, 557, 557, 26, 32},
  {cont__types__string__until_5, &frame__types__string__until_4, 557, 557, 26, 34},
  {cont__types__string__until_6, &frame__types__string__until_4, 557, 557, 14, 35},
  {cont__types__string__until_7, &frame__types__string__until_4, 557, 557, 7, 35},
  {entry__types__string__until_8, NULL, 559, 559, 7, 15},
  {entry__types__string__until_1, NULL, 554, 554, 3, 40},
  {cont__types__string__until_2, &frame__types__string__until_1, 556, 556, 5, 18},
  {cont__types__string__until_3, &frame__types__string__until_1, 555, 559, 3, 16},
  {cont__types__string__until_9, &frame__types__string__until_1, 559, 559, 16, 16},
  {entry__types__string__truncate_behind_4, NULL, 579, 579, 26, 32},
  {cont__types__string__truncate_behind_5, &frame__types__string__truncate_behind_4, 579, 579, 26, 34},
  {cont__types__string__truncate_behind_6, &frame__types__string__truncate_behind_4, 579, 579, 14, 35},
  {cont__types__string__truncate_behind_7, &frame__types__string__truncate_behind_4, 579, 579, 7, 35},
  {entry__types__string__truncate_behind_8, NULL, 581, 581, 7, 16},
  {entry__types__string__truncate_behind_1, NULL, 576, 576, 3, 40},
  {cont__types__string__truncate_behind_2, &frame__types__string__truncate_behind_1, 578, 578, 5, 18},
  {cont__types__string__truncate_behind_3, &frame__types__string__truncate_behind_1, 577, 581, 3, 17},
  {cont__types__string__truncate_behind_9, &frame__types__string__truncate_behind_1, 581, 581, 17, 17},
  {entry__types__string__between_1, NULL, 600, 600, 6, 27},
  {cont__types__string__between_2, &frame__types__string__between_1, 600, 600, 6, 43},
  {cont__types__string__between_3, &frame__types__string__between_1, 600, 600, 3, 43},
  {entry__types__string__has_prefix_1, NULL, 611, 611, 6, 23},
  {cont__types__string__has_prefix_2, &frame__types__string__has_prefix_1, 611, 611, 6, 34},
  {cont__types__string__has_prefix_3, &frame__types__string__has_prefix_1, 611, 611, 3, 34},
  {entry__types__string__has_suffix_10, NULL, 625, 625, 51, 61},
  {entry__types__string__has_suffix_3, NULL, 625, 625, 28, 28},
  {cont__types__string__has_suffix_4, &frame__types__string__has_suffix_3, 625, 625, 14, 29},
  {cont__types__string__has_suffix_5, &frame__types__string__has_suffix_3, 625, 625, 8, 37},
  {cont__types__string__has_suffix_6, &frame__types__string__has_suffix_3, 625, 625, 42, 46},
  {cont__types__string__has_suffix_7, &frame__types__string__has_suffix_3, 625, 625, 42, 48},
  {cont__types__string__has_suffix_8, &frame__types__string__has_suffix_3, 625, 625, 8, 48},
  {cont__types__string__has_suffix_9, &frame__types__string__has_suffix_3, 625, 625, 5, 61},
  {entry__types__string__has_suffix_1, NULL, 623, 623, 3, 22},
  {cont__types__string__has_suffix_2, &frame__types__string__has_suffix_1, 624, 625, 3, 61},
  {cont__types__string__has_suffix_11, &frame__types__string__has_suffix_1, 626, 626, 3, 10},
  {entry__types__string__without_prefix_4, NULL, 639, 639, 38, 40},
  {cont__types__string__without_prefix_5, &frame__types__string__without_prefix_4, 639, 639, 43, 43},
  {cont__types__string__without_prefix_6, &frame__types__string__without_prefix_4, 639, 639, 27, 44},
  {cont__types__string__without_prefix_7, &frame__types__string__without_prefix_4, 639, 639, 20, 44},
  {entry__types__string__without_prefix_1, NULL, 638, 638, 3, 23},
  {cont__types__string__without_prefix_2, &frame__types__string__without_prefix_1, 639, 639, 6, 17},
  {cont__types__string__without_prefix_3, &frame__types__string__without_prefix_1, 639, 639, 3, 44},
  {cont__types__string__without_prefix_8, &frame__types__string__without_prefix_1, 640, 640, 3, 9},
  {entry__types__string__without_suffix_10, NULL, 654, 654, 71, 73},
  {cont__types__string__without_suffix_11, &frame__types__string__without_suffix_10, 654, 654, 58, 74},
  {cont__types__string__without_suffix_12, &frame__types__string__without_suffix_10, 654, 654, 51, 74},
  {entry__types__string__without_suffix_3, NULL, 654, 654, 28, 28},
  {cont__types__string__without_suffix_4, &frame__types__string__without_suffix_3, 654, 654, 14, 29},
  {cont__types__string__without_suffix_5, &frame__types__string__without_suffix_3, 654, 654, 8, 37},
  {cont__types__string__without_suffix_6, &frame__types__string__without_suffix_3, 654, 654, 42, 46},
  {cont__types__string__without_suffix_7, &frame__types__string__without_suffix_3, 654, 654, 42, 48},
  {cont__types__string__without_suffix_8, &frame__types__string__without_suffix_3, 654, 654, 8, 48},
  {cont__types__string__without_suffix_9, &frame__types__string__without_suffix_3, 654, 654, 5, 74},
  {entry__types__string__without_suffix_1, NULL, 652, 652, 3, 22},
  {cont__types__string__without_suffix_2, &frame__types__string__without_suffix_1, 653, 654, 3, 74},
  {cont__types__string__without_suffix_13, &frame__types__string__without_suffix_1, 655, 655, 3, 9},
  {entry__std__trim_6, NULL, 665, 665, 22, 27},
  {cont__std__trim_7, &frame__std__trim_6, 665, 665, 22, 34},
  {cont__std__trim_8, &frame__std__trim_6, 665, 665, 22, 34},
  {cont__std__trim_9, &frame__std__trim_6, 665, 665, 22, 34},
  {entry__std__trim_11, NULL, 665, 665, 37, 45},
  {cont__std__trim_12, &frame__std__trim_11, 665, 665, 45, 45},
  {entry__std__trim_3, NULL, 665, 665, 12, 17},
  {cont__std__trim_4, &frame__std__trim_3, 665, 665, 12, 17},
  {cont__std__trim_5, &frame__std__trim_3, 665, 665, 12, 34},
  {cont__std__trim_10, &frame__std__trim_3, 665, 665, 9, 45},
  {entry__std__trim_17, NULL, 666, 666, 22, 27},
  {cont__std__trim_18, &frame__std__trim_17, 666, 666, 22, 34},
  {cont__std__trim_19, &frame__std__trim_17, 666, 666, 22, 34},
  {cont__std__trim_20, &frame__std__trim_17, 666, 666, 22, 34},
  {entry__std__trim_22, NULL, 666, 666, 37, 46},
  {cont__std__trim_23, &frame__std__trim_22, 666, 666, 46, 46},
  {entry__std__trim_14, NULL, 666, 666, 12, 17},
  {cont__std__trim_15, &frame__std__trim_14, 666, 666, 12, 17},
  {cont__std__trim_16, &frame__std__trim_14, 666, 666, 12, 34},
  {cont__std__trim_21, &frame__std__trim_14, 666, 666, 9, 46},
  {entry__std__trim_1, NULL, 664, 664, 3, 20},
  {cont__std__trim_2, &frame__std__trim_1, 665, 665, 3, 45},
  {cont__std__trim_13, &frame__std__trim_1, 666, 666, 3, 46},
  {cont__std__trim_24, &frame__std__trim_1, 667, 667, 3, 16},
  {cont__std__trim_25, &frame__std__trim_1, 667, 667, 16, 16},
  {entry__std__normalize_1, NULL, 675, 675, 3, 11},
  {cont__std__normalize_2, &frame__std__normalize_1, 676, 676, 25, 53},
  {cont__std__normalize_3, &frame__std__normalize_1, 676, 676, 20, 54},
  {cont__std__normalize_4, &frame__std__normalize_1, 676, 676, 20, 60},
  {cont__std__normalize_5, &frame__std__normalize_1, 676, 676, 3, 60},
  {cont__std__normalize_6, &frame__std__normalize_1, 676, 676, 60, 60},
  {entry__std__split_7, NULL, 689, 689, 32, 36},
  {cont__std__split_8, &frame__std__split_7, 689, 689, 19, 37},
  {cont__std__split_9, &frame__std__split_7, 689, 689, 7, 37},
  {cont__std__split_10, &frame__std__split_7, 690, 690, 19, 25},
  {cont__std__split_11, &frame__std__split_7, 690, 690, 28, 28},
  {cont__std__split_12, &frame__std__split_7, 690, 690, 7, 28},
  {cont__std__split_13, &frame__std__split_7, 690, 690, 28, 28},
  {entry__std__split_4, NULL, 687, 687, 5, 44},
  {cont__std__split_5, &frame__std__split_4, 688, 688, 8, 21},
  {cont__std__split_6, &frame__std__split_4, 688, 690, 5, 28},
  {cont__std__split_14, &frame__std__split_4, 691, 691, 8, 21},
  {cont__std__split_15, &frame__std__split_4, 691, 691, 5, 21},
  {entry__std__split_19, NULL, 692, 692, 27, 42},
  {cont__std__split_20, &frame__std__split_19, 692, 692, 42, 42},
  {entry__std__split_1, NULL, 683, 683, 5, 13},
  {cont__std__split_3, &frame__std__split_1, },
  {cont__std__split_2, &frame__std__split_1, 686, 691, 3, 21},
  {cont__std__split_16, &frame__std__split_1, 692, 692, 6, 20},
  {cont__std__split_17, &frame__std__split_1, 692, 692, 6, 24},
  {cont__std__split_18, &frame__std__split_1, 692, 692, 3, 42},
  {cont__std__split_21, &frame__std__split_1, 693, 693, 3, 10},
  {entry__std__join_2, NULL, 705, 705, 7, 23},
  {cont__std__join_3, &frame__std__join_2, 705, 705, 23, 23},
  {entry__std__join_4, NULL, 707, 707, 7, 28},
  {cont__std__join_5, &frame__std__join_4, 707, 707, 28, 28},
  {entry__std__join_1, NULL, 703, 707, 3, 29},
  {cont__std__join_6, &frame__std__join_1, 708, 708, 3, 9},
  {entry__std__count_occurrences_5, NULL, 721, 721, 19, 25},
  {cont__std__count_occurrences_6, &frame__std__count_occurrences_5, 721, 721, 28, 28},
  {cont__std__count_occurrences_7, &frame__std__count_occurrences_5, 721, 721, 7, 28},
  {cont__std__count_occurrences_8, &frame__std__count_occurrences_5, 722, 722, 7, 12},
  {cont__std__count_occurrences_9, &frame__std__count_occurrences_5, 722, 722, 12, 12},
  {entry__std__count_occurrences_2, NULL, 719, 719, 5, 39},
  {cont__std__count_occurrences_3, &frame__std__count_occurrences_2, 720, 720, 8, 21},
  {cont__std__count_occurrences_4, &frame__std__count_occurrences_2, 720, 722, 5, 12},
  {cont__std__count_occurrences_10, &frame__std__count_occurrences_2, 723, 723, 8, 21},
  {cont__std__count_occurrences_11, &frame__std__count_occurrences_2, 723, 723, 5, 21},
  {entry__std__count_occurrences_1, NULL, 718, 723, 3, 21},
  {cont__std__count_occurrences_12, &frame__std__count_occurrences_1, 724, 724, 3, 6},
  {entry__types__string__matches_1, NULL, 733, 733, 6, 30},
  {cont__types__string__matches_2, &frame__types__string__matches_1, 733, 733, 35, 49},
  {cont__types__string__matches_3, &frame__types__string__matches_1, 733, 733, 6, 49},
  {cont__types__string__matches_4, &frame__types__string__matches_1, 733, 733, 3, 49},
  {entry__types__string__contains_1, NULL, 742, 742, 3, 38},
  {cont__types__string__contains_2, &frame__types__string__contains_1, 743, 743, 6, 19},
  {cont__types__string__contains_3, &frame__types__string__contains_1, 743, 743, 3, 19},
  {entry__std__replace_umlauts_2, NULL, 1053, 1053, 20, 36},
  {cont__std__replace_umlauts_3, &frame__std__replace_umlauts_2, 1053, 1053, 5, 36},
  {cont__std__replace_umlauts_4, &frame__std__replace_umlauts_2, 1054, 1054, 5, 12},
  {cont__std__replace_umlauts_5, &frame__std__replace_umlauts_2, 1054, 1054, 12, 12},
  {entry__std__replace_umlauts_17, NULL, 1064, 1064, 15, 39},
  {cont__std__replace_umlauts_18, &frame__std__replace_umlauts_17, 1064, 1064, 39, 39},
  {entry__std__replace_umlauts_19, NULL, 1066, 1066, 15, 30},
  {cont__std__replace_umlauts_20, &frame__std__replace_umlauts_19, 1066, 1066, 30, 30},
  {entry__std__replace_umlauts_12, NULL, 1060, 1060, 16, 20},
  {cont__std__replace_umlauts_13, &frame__std__replace_umlauts_12, 1060, 1060, 11, 20},
  {cont__std__replace_umlauts_14, &frame__std__replace_umlauts_12, 1061, 1061, 11, 45},
  {cont__std__replace_umlauts_15, &frame__std__replace_umlauts_12, 1063, 1063, 13, 33},
  {cont__std__replace_umlauts_16, &frame__std__replace_umlauts_12, 1062, 1066, 11, 31},
  {entry__std__replace_umlauts_21, NULL, 1068, 1068, 16, 20},
  {cont__std__replace_umlauts_22, &frame__std__replace_umlauts_21, 1068, 1068, 11, 20},
  {cont__std__replace_umlauts_23, &frame__std__replace_umlauts_21, 1069, 1069, 24, 31},
  {cont__std__replace_umlauts_24, &frame__std__replace_umlauts_21, 1069, 1069, 11, 31},
  {cont__std__replace_umlauts_25, &frame__std__replace_umlauts_21, 1069, 1069, 31, 31},
  {entry__std__replace_umlauts_9, NULL, 1059, 1059, 9, 23},
  {cont__std__replace_umlauts_10, &frame__std__replace_umlauts_9, 1059, 1059, 9, 23},
  {cont__std__replace_umlauts_11, &frame__std__replace_umlauts_9, 1058, 1069, 7, 32},
  {entry__std__replace_umlauts_6, NULL, 1057, 1057, 8, 22},
  {cont__std__replace_umlauts_7, &frame__std__replace_umlauts_6, 1057, 1057, 8, 22},
  {cont__std__replace_umlauts_8, &frame__std__replace_umlauts_6, 1057, 1069, 5, 33},
  {entry__std__replace_umlauts_1, NULL, 1056, 1069, 3, 34},
  {cont__std__replace_umlauts_26, &frame__std__replace_umlauts_1, 1070, 1070, 8, 22},
  {cont__std__replace_umlauts_27, &frame__std__replace_umlauts_1, 1070, 1070, 3, 22},
  {cont__std__replace_umlauts_28, &frame__std__replace_umlauts_1, 1071, 1071, 3, 11},
  {entry__std__replace_all_14, NULL, 1111, 1111, 15, 42},
  {cont__std__replace_all_15, &frame__std__replace_all_14, 1111, 1111, 42, 42},
  {entry__std__replace_all_16, NULL, 1113, 1113, 44, 60},
  {cont__std__replace_all_17, &frame__std__replace_all_16, 1113, 1113, 32, 61},
  {cont__std__replace_all_18, &frame__std__replace_all_16, 1113, 1113, 15, 61},
  {cont__std__replace_all_19, &frame__std__replace_all_16, 1113, 1113, 61, 61},
  {entry__std__replace_all_12, NULL, 1110, 1110, 13, 35},
  {cont__std__replace_all_13, &frame__std__replace_all_12, 1109, 1113, 11, 62},
  {cont__std__replace_all_20, &frame__std__replace_all_12, 1114, 1114, 23, 27},
  {cont__std__replace_all_21, &frame__std__replace_all_12, 1114, 1114, 30, 30},
  {cont__std__replace_all_22, &frame__std__replace_all_12, 1114, 1114, 11, 30},
  {cont__std__replace_all_23, &frame__std__replace_all_12, 1115, 1115, 11, 15},
  {entry__std__replace_all_7, NULL, 1105, 1105, 9, 31},
  {cont__std__replace_all_8, &frame__std__replace_all_7, 1106, 1106, 9, 34},
  {cont__std__replace_all_9, &frame__std__replace_all_7, 1107, 1107, 9, 43},
  {cont__std__replace_all_10, &frame__std__replace_all_7, 1108, 1108, 12, 25},
  {cont__std__replace_all_11, &frame__std__replace_all_7, 1108, 1115, 9, 15},
  {entry__std__replace_all_6, NULL, 1104, 1115, 7, 16},
  {cont__std__replace_all_24, &frame__std__replace_all_6, 1116, 1116, 22, 28},
  {cont__std__replace_all_25, &frame__std__replace_all_6, 1116, 1116, 7, 28},
  {cont__std__replace_all_26, &frame__std__replace_all_6, 1117, 1117, 22, 22},
  {cont__std__replace_all_27, &frame__std__replace_all_6, 1117, 1117, 7, 22},
  {cont__std__replace_all_28, &frame__std__replace_all_6, 1117, 1117, 22, 22},
  {entry__std__replace_all_5, NULL, 1103, 1117, 5, 22},
  {entry__std__replace_all_2, NULL, 1102, 1102, 12, 26},
  {cont__std__replace_all_3, &frame__std__replace_all_2, 1102, 1102, 12, 30},
  {cont__std__replace_all_4, &frame__std__replace_all_2, 1102, 1117, 9, 23},
  {entry__std__replace_all_1, NULL, 1102, 1117, 3, 23},
  {cont__std__replace_all_29, &frame__std__replace_all_1, 1118, 1118, 3, 13},
  {entry__std__delete_all_10, NULL, 1133, 1133, 23, 27},
  {cont__std__delete_all_11, &frame__std__delete_all_10, 1133, 1133, 30, 30},
  {cont__std__delete_all_12, &frame__std__delete_all_10, 1133, 1133, 11, 30},
  {cont__std__delete_all_13, &frame__std__delete_all_10, 1134, 1134, 11, 15},
  {entry__std__delete_all_7, NULL, 1131, 1131, 9, 43},
  {cont__std__delete_all_8, &frame__std__delete_all_7, 1132, 1132, 12, 25},
  {cont__std__delete_all_9, &frame__std__delete_all_7, 1132, 1134, 9, 15},
  {entry__std__delete_all_6, NULL, 1130, 1134, 7, 16},
  {cont__std__delete_all_14, &frame__std__delete_all_6, 1135, 1135, 22, 28},
  {cont__std__delete_all_15, &frame__std__delete_all_6, 1135, 1135, 7, 28},
  {cont__std__delete_all_16, &frame__std__delete_all_6, 1136, 1136, 22, 22},
  {cont__std__delete_all_17, &frame__std__delete_all_6, 1136, 1136, 7, 22},
  {cont__std__delete_all_18, &frame__std__delete_all_6, 1136, 1136, 22, 22},
  {entry__std__delete_all_5, NULL, 1129, 1136, 5, 22},
  {entry__std__delete_all_2, NULL, 1128, 1128, 12, 26},
  {cont__std__delete_all_3, &frame__std__delete_all_2, 1128, 1128, 12, 30},
  {cont__std__delete_all_4, &frame__std__delete_all_2, 1128, 1136, 9, 23},
  {entry__std__delete_all_1, NULL, 1128, 1136, 3, 23},
  {cont__std__delete_all_19, &frame__std__delete_all_1, 1137, 1137, 3, 13},
  {entry__std__spaces_3, NULL, 1150, 1150, 17, 26},
  {cont__std__spaces_4, &frame__std__spaces_3, 1150, 1150, 14, 26},
  {entry__std__spaces_5, NULL, 1150, 1150, 32, 55},
  {cont__std__spaces_6, &frame__std__spaces_5, 1150, 1150, 29, 55},
  {entry__std__spaces_1, NULL, 1150, 1150, 6, 11},
  {cont__std__spaces_2, &frame__std__spaces_1, 1150, 1150, 3, 55},
  {entry__std__indented_14, NULL, 1164, 1164, 36, 42},
  {cont__std__indented_15, &frame__std__indented_14, 1164, 1164, 36, 52},
  {cont__std__indented_16, &frame__std__indented_14, 1164, 1164, 36, 52},
  {entry__std__indented_18, NULL, 1164, 1164, 55, 78},
  {cont__std__indented_19, &frame__std__indented_18, 1164, 1164, 78, 78},
  {entry__std__indented_3, NULL, 1160, 1160, 5, 31},
  {cont__std__indented_4, &frame__std__indented_3, 1163, 1163, 31, 53},
  {cont__std__indented_5, &frame__std__indented_3, 1163, 1163, 15, 54},
  {cont__std__indented_6, &frame__std__indented_3, 1163, 1163, 7, 54},
  {cont__std__indented_7, &frame__std__indented_3, 1163, 1163, 58, 77},
  {cont__std__indented_9, &frame__std__indented_3, 1163, 1163, 7, 77},
  {cont__std__indented_10, &frame__std__indented_3, 1161, 1163, 5, 77},
  {cont__std__indented_11, &frame__std__indented_3, 1164, 1164, 12, 26},
  {cont__std__indented_12, &frame__std__indented_3, 1164, 1164, 12, 31},
  {cont__std__indented_13, &frame__std__indented_3, 1164, 1164, 12, 52},
  {cont__std__indented_17, &frame__std__indented_3, 1164, 1164, 5, 78},
  {entry__std__indented_1, NULL, 1159, 1159, 6, 15},
  {cont__std__indented_2, &frame__std__indented_1, 1159, 1164, 3, 78},
  {cont__std__indented_20, &frame__std__indented_1, 1165, 1165, 3, 9},
  {entry__std__for_each_line_7, NULL, 1181, 1181, 32, 36},
  {cont__std__for_each_line_8, &frame__std__for_each_line_7, 1181, 1181, 19, 37},
  {cont__std__for_each_line_9, &frame__std__for_each_line_7, 1181, 1181, 11, 37},
  {entry__std__for_each_line_10, NULL, 1183, 1183, 29, 33},
  {cont__std__for_each_line_11, &frame__std__for_each_line_10, 1183, 1183, 16, 34},
  {cont__std__for_each_line_12, &frame__std__for_each_line_10, 1183, 1183, 11, 34},
  {entry__std__for_each_line_18, NULL, 1185, 1185, 30, 56},
  {cont__std__for_each_line_19, &frame__std__for_each_line_18, 1185, 1185, 30, 56},
  {entry__std__for_each_line_4, NULL, 1180, 1180, 9, 32},
  {cont__std__for_each_line_5, &frame__std__for_each_line_4, 1180, 1180, 9, 37},
  {cont__std__for_each_line_6, &frame__std__for_each_line_4, 1179, 1183, 7, 35},
  {cont__std__for_each_line_13, &frame__std__for_each_line_4, 1184, 1184, 24, 28},
  {cont__std__for_each_line_14, &frame__std__for_each_line_4, 1184, 1184, 31, 31},
  {cont__std__for_each_line_15, &frame__std__for_each_line_4, 1184, 1184, 7, 32},
  {cont__std__for_each_line_16, &frame__std__for_each_line_4, 1185, 1185, 10, 25},
  {cont__std__for_each_line_17, &frame__std__for_each_line_4, 1185, 1185, 10, 56},
  {cont__std__for_each_line_20, &frame__std__for_each_line_4, 1185, 1185, 7, 62},
  {cont__std__for_each_line_21, &frame__std__for_each_line_4, 1186, 1186, 37, 40},
  {cont__std__for_each_line_22, &frame__std__for_each_line_4, 1186, 1186, 7, 40},
  {entry__std__for_each_line_29, NULL, 1191, 1191, 13, 24},
  {entry__std__for_each_line_30, NULL, 1193, 1193, 13, 21},
  {entry__std__for_each_line_26, NULL, 1190, 1190, 11, 34},
  {cont__std__for_each_line_27, &frame__std__for_each_line_26, 1190, 1190, 11, 39},
  {cont__std__for_each_line_28, &frame__std__for_each_line_26, 1189, 1193, 9, 22},
  {entry__std__for_each_line_23, NULL, 1188, 1188, 10, 24},
  {cont__std__for_each_line_24, &frame__std__for_each_line_23, 1188, 1188, 10, 28},
  {cont__std__for_each_line_25, &frame__std__for_each_line_23, 1188, 1193, 7, 23},
  {entry__std__for_each_line_1, NULL, 1176, 1176, 3, 31},
  {cont__std__for_each_line_2, &frame__std__for_each_line_1, 1178, 1178, 5, 18},
  {cont__std__for_each_line_3, &frame__std__for_each_line_1, 1177, 1193, 3, 25},
  {entry__types__string__to_lower_case_1, NULL, 1201, 1201, 6, 28},
  {cont__types__string__to_lower_case_2, &frame__types__string__to_lower_case_1, 1201, 1201, 3, 28},
  {entry__types__string__to_upper_case_1, NULL, 1209, 1209, 6, 28},
  {cont__types__string__to_upper_case_2, &frame__types__string__to_upper_case_1, 1209, 1209, 3, 28},
  {entry__types__string__to_title_case_5, NULL, 1224, 1224, 23, 39},
  {cont__types__string__to_title_case_6, &frame__types__string__to_title_case_5, 1224, 1224, 13, 39},
  {cont__types__string__to_title_case_7, &frame__types__string__to_title_case_5, 1225, 1225, 27, 27},
  {entry__types__string__to_title_case_8, NULL, 1227, 1227, 23, 39},
  {cont__types__string__to_title_case_9, &frame__types__string__to_title_case_8, 1227, 1227, 13, 39},
  {cont__types__string__to_title_case_10, &frame__types__string__to_title_case_8, 1227, 1227, 39, 39},
  {entry__types__string__to_title_case_4, NULL, 1222, 1227, 9, 40},
  {entry__types__string__to_title_case_11, NULL, 1229, 1229, 9, 21},
  {cont__types__string__to_title_case_12, &frame__types__string__to_title_case_11, 1230, 1230, 22, 22},
  {entry__types__string__to_title_case_2, NULL, 1221, 1221, 7, 31},
  {cont__types__string__to_title_case_3, &frame__types__string__to_title_case_2, 1220, 1230, 5, 23},
  {entry__types__string__to_title_case_1, NULL, 1219, 1230, 3, 24},
  {cont__types__string__to_title_case_13, &frame__types__string__to_title_case_1, 1231, 1231, 3, 8},
  {entry__types__octet_string__new_empty_collection_1, NULL, 1239, 1239, 3, 24},
  {entry__types__quad_octet_string__new_empty_collection_1, NULL, 1247, 1247, 3, 24},
  {entry__std__collect_output_2, NULL, 1256, 1256, 24, 43},
  {cont__std__collect_output_3, &frame__std__collect_output_2, 1256, 1256, 43, 43},
  {entry__std__collect_output_1, NULL, 1258, 1258, 3, 6},
  {cont__std__collect_output_4, &frame__std__collect_output_1, 1258, 1258, 6, 6}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *character__506;
static NODE *character__343;
static NODE *character__338;
static NODE *character__311;
static NODE *character__287;
static NODE *character__270;
static NODE *character__224;
static NODE *character__9;
static NODE *character__455;
static NODE *character__348;
static NODE *character__333;
static NODE *character__301;
static NODE *character__256;
static NODE *character__234;
static NODE *character__486;
static NODE *character__484;
static NODE *character__475;
static NODE *character__467;
static NODE *character__358;
static NODE *character__331;
static NODE *character__323;
static NODE *character__244;
static NODE *character__236;
static NODE *character__188;
static NODE *character__179;
static NODE *character__504;
static NODE *character__465;
static NODE *character__389;
static NODE *character__368;
static NODE *character__321;
static NODE *character__313;
static NODE *character__246;
static NODE *character__198;
static NODE *character__169;
static NODE *character__471;
static NODE *character__382;
static NODE *character__354;
static NODE *character__327;
static NODE *character__303;
static NODE *character__295;
static NODE *character__216;
static NODE *character__208;
static NODE *character__184;
static NODE *character__461;
static NODE *character__400;
static NODE *character__392;
static NODE *character__378;
static NODE *character__364;
static NODE *character__317;
static NODE *character__293;
static NODE *character__285;
static NODE *character__279;
static NODE *character__226;
static NODE *character__218;
static NODE *character__194;
static NODE *character__172;
static NODE *number__80;
static NODE *character__57;
static NODE *character__402;
static NODE *character__366;
static NODE *character__315;
static NODE *character__307;
static NODE *character__291;
static NODE *character__283;
static NODE *character__228;
static NODE *character__204;
static NODE *character__196;
static NODE *character__160;
static NODE *character__473;
static NODE *character__380;
static NODE *character__376;
static NODE *character__374;
static NODE *character__305;
static NODE *character__297;
static NODE *character__281;
static NODE *character__238;
static NODE *character__214;
static NODE *character__206;
static NODE *character__162;
static NODE *character__509;
static NODE *character__482;
static NODE *character__468;
static NODE *character__463;
static NODE *character__387;
static NODE *character__335;
static NODE *character__259;
static NODE *character__232;
static NODE *character__170;
static NODE *character__167;
static NODE *character__63;
static NODE *character__499;
static NODE *character__478;
static NODE *character__371;
static NODE *character__325;
static NODE *character__324;
static NODE *character__249;
static NODE *character__242;
static NODE *character__211;
static NODE *character__166;
static NODE *character__10;
static NODE *character__45;
static NODE *character__481;
static NODE *character__453;
static NODE *character__334;
static NODE *character__288;
static NODE *character__231;
static NODE *character__212;
static NODE *character__185;
static NODE *number__0;
static NODE *character__345;
static NODE *character__344;
static NODE *character__298;
static NODE *character__269;
static NODE *character__222;
static NODE *character__221;
static NODE *character__13;
static NODE *character__460;
static NODE *character__457;
static NODE *character__365;
static NODE *character__308;
static NODE *character__284;
static NODE *character__262;
static NODE *character__205;
static NODE *character__181;
static NODE *character__470;
static NODE *character__393;
static NODE *character__379;
static NODE *character__355;
static NODE *character__341;
static NODE *character__318;
static NODE *character__294;
static NODE *character__272;
static NODE *character__219;
static NODE *character__195;
static NODE *character__173;
static NODE *character__492;
static NODE *character__489;
static NODE *character__383;
static NODE *character__361;
static NODE *character__304;
static NODE *character__280;
static NODE *character__266;
static NODE *character__239;
static NODE *character__201;
static NODE *character__163;
static NODE *number__0x80;
static NODE *character__397;
static NODE *character__375;
static NODE *character__351;
static NODE *character__328;
static NODE *character__314;
static NODE *character__290;
static NODE *character__276;
static NODE *character__252;
static NODE *character__229;
static NODE *character__215;
static NODE *character__191;
static NODE *character__177;
static NODE *character__485;
static NODE *character__476;
static NODE *character__403;
static NODE *character__322;
static NODE *character__300;
static NODE *character__267;
static NODE *character__235;
static NODE *character__189;
static NODE *character__507;
static NODE *character__454;
static NODE *character__349;
static NODE *character__332;
static NODE *character__310;
static NODE *character__286;
static NODE *character__271;
static NODE *character__257;
static NODE *character__225;
static NODE *character__505;
static NODE *character__497;
static NODE *character__464;
static NODE *character__456;
static NODE *character__369;
static NODE *character__312;
static NODE *character__255;
static NODE *character__247;
static NODE *character__209;
static NODE *character__168;
static NODE *character__487;
static NODE *character__474;
static NODE *character__466;
static NODE *character__388;
static NODE *character__359;
static NODE *character__320;
static NODE *character__245;
static NODE *character__237;
static NODE *character__199;
static NODE *character__501;
static NODE *character__362;
static NODE *character__330;
static NODE *character__319;
static NODE *character__273;
static NODE *character__251;
static NODE *character__192;
static NODE *character__178;
static NODE *character__164;
static NODE *character__32;
static NODE *character__491;
static NODE *character__384;
static NODE *character__372;
static NODE *character__340;
static NODE *character__309;
static NODE *character__265;
static NODE *character__241;
static NODE *character__202;
static NODE *character__394;
static NODE *character__386;
static NODE *character__350;
static NODE *character__342;
static NODE *character__339;
static NODE *character__277;
static NODE *character__263;
static NODE *character__180;
static NODE *character__174;
static NODE *character__511;
static NODE *character__458;
static NODE *character__396;
static NODE *character__360;
static NODE *character__352;
static NODE *character__329;
static NODE *character__275;
static NODE *character__261;
static NODE *character__253;
static NODE *character__190;
static NODE *character__182;
static NODE *character__176;
static NODE *character__493;
static NODE *character__488;
static NODE *character__479;
static NODE *character__452;
static NODE *character__370;
static NODE *character__357;
static NODE *character__346;
static NODE *character__243;
static NODE *character__200;
static NODE *character__197;
static NODE *number__1;
static NODE *character__498;
static NODE *character__483;
static NODE *character__469;
static NODE *character__462;
static NODE *character__356;
static NODE *character__248;
static NODE *character__233;
static NODE *character__210;
static NODE *character__187;
static NODE *character__186;
static NODE *character__508;
static NODE *character__347;
static NODE *character__326;
static NODE *character__299;
static NODE *character__258;
static NODE *character__223;
static NODE *character__220;
static NODE *character__49;
static NODE *character__46;
static NODE *character__480;
static NODE *character__337;
static NODE *character__336;
static NODE *character__289;
static NODE *character__268;
static NODE *character__230;
static NODE *number__2;
static NODE *character__395;
static NODE *character__373;
static NODE *character__316;
static NODE *character__292;
static NODE *character__278;
static NODE *character__254;
static NODE *character__240;
static NODE *character__227;
static NODE *character__213;
static NODE *character__175;
static NODE *character__500;
static NODE *character__490;
static NODE *character__401;
static NODE *character__385;
static NODE *character__363;
static NODE *character__302;
static NODE *character__264;
static NODE *character__203;
static NODE *character__165;
static NODE *character__472;
static NODE *character__459;
static NODE *character__391;
static NODE *character__377;
static NODE *character__353;
static NODE *character__296;
static NODE *character__274;
static NODE *character__250;
static NODE *character__217;
static NODE *character__193;
static NODE *character__171;
static NODE *character__128;
static NODE *character__510;
static NODE *character__381;
static NODE *character__367;
static NODE *character__306;
static NODE *character__282;
static NODE *character__260;
static NODE *character__207;
static NODE *character__183;
static NODE *character__161;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__string",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/string.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__string(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 295);
  // 747: '@nbsp;' = " "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__160;
  arguments->slots[1] = string__578a5af303e9cc1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_1;
}
static void cont__93_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 748: '¡' = "!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__161;
  arguments->slots[1] = string__578a5af303e9cc0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_3;
}
static void cont__93_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 749: '¢' = "(cent)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__162;
  arguments->slots[1] = string__521f55e4811a62fe;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_5;
}
static void cont__93_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 750: '£' = "(pound)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__163;
  arguments->slots[1] = string__99240e5a959a30d3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_7;
}
static void cont__93_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 751: '¤' = "?"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__164;
  arguments->slots[1] = string__578a5af303e9cde;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_9;
}
static void cont__93_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 752: '¥' = "(yen)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__165;
  arguments->slots[1] = string__785aea43eabc907e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_11;
}
static void cont__93_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 753: '¦' = "|"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__166;
  arguments->slots[1] = string__578a5af303e9c9d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_13;
}
static void cont__93_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 754: '§' = "$"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__167;
  arguments->slots[1] = string__578a5af303e9cc5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_15;
}
static void cont__93_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 755: '¨' = "@quot;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__168;
  arguments->slots[1] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_17;
}
static void cont__93_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 756: '©' = "(c)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__169;
  arguments->slots[1] = string__fa732415d316be5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_19;
}
static void cont__93_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 757: 'ª' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__170;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_21;
}
static void cont__93_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 758: '«' = "<<"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__171;
  arguments->slots[1] = string__2d7981f4e6e82bf9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_23;
}
static void cont__93_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 759: '¬' = "(not)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__172;
  arguments->slots[1] = string__565ae8c3ea6c907e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_25;
}
static void cont__93_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 760: '­' = "(shy)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__173;
  arguments->slots[1] = string__6c5ae903ea04907e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_27;
}
static void cont__93_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 761: '®' = "(r)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__174;
  arguments->slots[1] = string__fa732415db96be5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_29;
}
static void cont__93_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 762: '¯' = "~"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__175;
  arguments->slots[1] = string__578a5af303e9c9f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_31;
}
static void cont__93_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 763: '°' = "(grad)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__176;
  arguments->slots[1] = string__7c1f5624819a22fe;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_33;
}
static void cont__93_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  // 764: '±' = "+/-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__177;
  arguments->slots[1] = string__fa732815f516be1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_35;
}
static void cont__93_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 765: '²' = "^2"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__178;
  arguments->slots[1] = string__2d7981f4e5f82bf7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_37;
}
static void cont__93_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__19 */ = arguments->slots[0];
  // 766: '³' = "^3"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__179;
  arguments->slots[1] = string__2d7981f4e5f82bf6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_39;
}
static void cont__93_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__20 */ = arguments->slots[0];
  // 767: '´' = "'"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__180;
  arguments->slots[1] = string__578a5af303e9cc6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_41;
}
static void cont__93_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__21 */ = arguments->slots[0];
  // 768: 'µ' = "(mu)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__181;
  arguments->slots[1] = string__920aea0b5dc87d10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_43;
}
static void cont__93_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__22 */ = arguments->slots[0];
  // 769: '¶' = "(par)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__182;
  arguments->slots[1] = string__6a5aeb43ea5c907e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_45;
}
static void cont__93_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__23 */ = arguments->slots[0];
  // 770: '·' = "."
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__183;
  arguments->slots[1] = string__578a5af303e9ccf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_47;
}
static void cont__93_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__24 */ = arguments->slots[0];
  // 771: '¸' = ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__184;
  arguments->slots[1] = string__578a5af303e9ccd;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_49;
}
static void cont__93_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[24] /* temp__25 */ = arguments->slots[0];
  // 772: '¹' = "^1"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__185;
  arguments->slots[1] = string__2d7981f4e5f82bf4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_51;
}
static void cont__93_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[25] /* temp__26 */ = arguments->slots[0];
  // 773: 'º' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__186;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_53;
}
static void cont__93_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[26] /* temp__27 */ = arguments->slots[0];
  // 774: '»' = ">>"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__187;
  arguments->slots[1] = string__2d7981f4e6f82bfb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_55;
}
static void cont__93_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[27] /* temp__28 */ = arguments->slots[0];
  // 775: '¼' = "1/4"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__188;
  arguments->slots[1] = string__fa734015f516bf8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_57;
}
static void cont__93_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[28] /* temp__29 */ = arguments->slots[0];
  // 776: '½' = "1/2"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__189;
  arguments->slots[1] = string__fa734015f516bfe;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_59;
}
static void cont__93_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[29] /* temp__30 */ = arguments->slots[0];
  // 777: '¾' = "3/4"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__190;
  arguments->slots[1] = string__fa734815f516bf8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_61;
}
static void cont__93_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[30] /* temp__31 */ = arguments->slots[0];
  // 778: '¿' = "?"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__191;
  arguments->slots[1] = string__578a5af303e9cde;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_62;
}
static void cont__93_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[31] /* temp__32 */ = arguments->slots[0];
  // 779: 'À' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__192;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_64;
}
static void cont__93_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__33 */ = arguments->slots[0];
  // 780: 'Á' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__193;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_65;
}
static void cont__93_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__34 */ = arguments->slots[0];
  // 781: 'Â' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__194;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_66;
}
static void cont__93_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__35 */ = arguments->slots[0];
  // 782: 'Ã' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__195;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_67;
}
static void cont__93_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[35] /* temp__36 */ = arguments->slots[0];
  // 783: 'Ä' = "Ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__196;
  arguments->slots[1] = string__2d7981f4e5002ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_69;
}
static void cont__93_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[36] /* temp__37 */ = arguments->slots[0];
  // 784: 'Å' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__197;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_70;
}
static void cont__93_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[37] /* temp__38 */ = arguments->slots[0];
  // 785: 'Æ' = "AE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__198;
  arguments->slots[1] = string__2d7981f4e5002b80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_72;
}
static void cont__93_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[38] /* temp__39 */ = arguments->slots[0];
  // 786: 'Ç' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__199;
  arguments->slots[1] = string__578a5af303e9ca2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_74;
}
static void cont__93_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[39] /* temp__40 */ = arguments->slots[0];
  // 787: 'È' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__200;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_76;
}
static void cont__93_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[40] /* temp__41 */ = arguments->slots[0];
  // 788: 'É' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__201;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_77;
}
static void cont__93_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[41] /* temp__42 */ = arguments->slots[0];
  // 789: 'Ê' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__202;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_78;
}
static void cont__93_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[42] /* temp__43 */ = arguments->slots[0];
  // 790: 'Ë' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__203;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_79;
}
static void cont__93_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[43] /* temp__44 */ = arguments->slots[0];
  // 791: 'Ì' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__204;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_81;
}
static void cont__93_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[44] /* temp__45 */ = arguments->slots[0];
  // 792: 'Í' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__205;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_82;
}
static void cont__93_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[45] /* temp__46 */ = arguments->slots[0];
  // 793: 'Î' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__206;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_83;
}
static void cont__93_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[46] /* temp__47 */ = arguments->slots[0];
  // 794: 'Ï' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__207;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_84;
}
static void cont__93_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[47] /* temp__48 */ = arguments->slots[0];
  // 795: 'Ð' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__208;
  arguments->slots[1] = string__578a5af303e9ca5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_86;
}
static void cont__93_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[48] /* temp__49 */ = arguments->slots[0];
  // 796: 'Ñ' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__209;
  arguments->slots[1] = string__578a5af303e9caf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_88;
}
static void cont__93_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[49] /* temp__50 */ = arguments->slots[0];
  // 797: 'Ò' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__210;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_90;
}
static void cont__93_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[50] /* temp__51 */ = arguments->slots[0];
  // 798: 'Ó' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__211;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_91;
}
static void cont__93_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[51] /* temp__52 */ = arguments->slots[0];
  // 799: 'Ô' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__212;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_92;
}
static void cont__93_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[52] /* temp__53 */ = arguments->slots[0];
  // 800: 'Õ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__213;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_93;
}
static void cont__93_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[53] /* temp__54 */ = arguments->slots[0];
  // 801: 'Ö' = "Oe"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__214;
  arguments->slots[1] = string__2d7981f4e5702ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_95;
}
static void cont__93_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[54] /* temp__55 */ = arguments->slots[0];
  // 802: '×' = "x"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__215;
  arguments->slots[1] = string__578a5af303e9c99;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_97;
}
static void cont__93_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[55] /* temp__56 */ = arguments->slots[0];
  // 803: 'Ø' = "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__216;
  arguments->slots[1] = string__578a5af303e9cd1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_99;
}
static void cont__93_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[56] /* temp__57 */ = arguments->slots[0];
  // 804: 'Ù' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__217;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_101;
}
static void cont__93_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[57] /* temp__58 */ = arguments->slots[0];
  // 805: 'Ú' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__218;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_102;
}
static void cont__93_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[58] /* temp__59 */ = arguments->slots[0];
  // 806: 'Û' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__219;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_103;
}
static void cont__93_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[59] /* temp__60 */ = arguments->slots[0];
  // 807: 'Ü' = "Ue"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__220;
  arguments->slots[1] = string__2d7981f4e5a02ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_105;
}
static void cont__93_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[60] /* temp__61 */ = arguments->slots[0];
  // 808: 'Ý' = "Y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__221;
  arguments->slots[1] = string__578a5af303e9cb8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_107;
}
static void cont__93_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[61] /* temp__62 */ = arguments->slots[0];
  // 809: 'Þ' = "p"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__222;
  arguments->slots[1] = string__578a5af303e9c91;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_109;
}
static void cont__93_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[62] /* temp__63 */ = arguments->slots[0];
  // 810: 'ß' = "ss"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__223;
  arguments->slots[1] = string__2d7981f4e4902bb6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_111;
}
static void cont__93_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[63] /* temp__64 */ = arguments->slots[0];
  // 811: 'à' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__224;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_112;
}
static void cont__93_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[64] /* temp__65 */ = arguments->slots[0];
  // 812: 'á' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__225;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_113;
}
static void cont__93_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[65] /* temp__66 */ = arguments->slots[0];
  // 813: 'â' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__226;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_114;
}
static void cont__93_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[66] /* temp__67 */ = arguments->slots[0];
  // 814: 'ã' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__227;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_115;
}
static void cont__93_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[67] /* temp__68 */ = arguments->slots[0];
  // 815: 'ä' = "ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__228;
  arguments->slots[1] = string__2d7981f4e4002ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_117;
}
static void cont__93_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[68] /* temp__69 */ = arguments->slots[0];
  // 816: 'å' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__229;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_118;
}
static void cont__93_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[69] /* temp__70 */ = arguments->slots[0];
  // 817: 'æ' = "ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__230;
  arguments->slots[1] = string__2d7981f4e4002ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_119;
}
static void cont__93_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[70] /* temp__71 */ = arguments->slots[0];
  // 818: 'ç' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__231;
  arguments->slots[1] = string__578a5af303e9c82;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_121;
}
static void cont__93_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[71] /* temp__72 */ = arguments->slots[0];
  // 819: 'è' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__232;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_123;
}
static void cont__93_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[72] /* temp__73 */ = arguments->slots[0];
  // 820: 'é' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__233;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_124;
}
static void cont__93_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[73] /* temp__74 */ = arguments->slots[0];
  // 821: 'ê' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__234;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_125;
}
static void cont__93_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[74] /* temp__75 */ = arguments->slots[0];
  // 822: 'ë' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__235;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_126;
}
static void cont__93_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[75] /* temp__76 */ = arguments->slots[0];
  // 823: 'ì' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__236;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_128;
}
static void cont__93_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[76] /* temp__77 */ = arguments->slots[0];
  // 824: 'í' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__237;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_129;
}
static void cont__93_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[77] /* temp__78 */ = arguments->slots[0];
  // 825: 'î' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__238;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_130;
}
static void cont__93_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[78] /* temp__79 */ = arguments->slots[0];
  // 826: 'ï' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__239;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_131;
}
static void cont__93_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[79] /* temp__80 */ = arguments->slots[0];
  // 827: 'ð' = "d"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__240;
  arguments->slots[1] = string__578a5af303e9c85;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_133;
}
static void cont__93_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[80] /* temp__81 */ = arguments->slots[0];
  // 828: 'ñ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__241;
  arguments->slots[1] = string__578a5af303e9c8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_135;
}
static void cont__93_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[81] /* temp__82 */ = arguments->slots[0];
  // 829: 'ò' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__242;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_136;
}
static void cont__93_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[82] /* temp__83 */ = arguments->slots[0];
  // 830: 'ó' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__243;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_137;
}
static void cont__93_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[83] /* temp__84 */ = arguments->slots[0];
  // 831: 'ô' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__244;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_138;
}
static void cont__93_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[84] /* temp__85 */ = arguments->slots[0];
  // 832: 'õ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__245;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_139;
}
static void cont__93_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[85] /* temp__86 */ = arguments->slots[0];
  // 833: 'ö' = "oe"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__246;
  arguments->slots[1] = string__2d7981f4e4702ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_141;
}
static void cont__93_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[86] /* temp__87 */ = arguments->slots[0];
  // 834: '÷' = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__247;
  arguments->slots[1] = string__578a5af303e9cce;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_143;
}
static void cont__93_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[87] /* temp__88 */ = arguments->slots[0];
  // 835: 'ø' = "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__248;
  arguments->slots[1] = string__578a5af303e9cd1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_144;
}
static void cont__93_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[88] /* temp__89 */ = arguments->slots[0];
  // 836: 'ù' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__249;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_146;
}
static void cont__93_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[89] /* temp__90 */ = arguments->slots[0];
  // 837: 'ú' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__250;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_147;
}
static void cont__93_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[90] /* temp__91 */ = arguments->slots[0];
  // 838: 'û' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__251;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_148;
}
static void cont__93_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[91] /* temp__92 */ = arguments->slots[0];
  // 839: 'ü' = "ue"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__252;
  arguments->slots[1] = string__2d7981f4e4a02ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_150;
}
static void cont__93_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[92] /* temp__93 */ = arguments->slots[0];
  // 840: 'ý' = "y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__253;
  arguments->slots[1] = string__578a5af303e9c98;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_152;
}
static void cont__93_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[93] /* temp__94 */ = arguments->slots[0];
  // 841: 'þ' = "p"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__254;
  arguments->slots[1] = string__578a5af303e9c91;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_153;
}
static void cont__93_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[94] /* temp__95 */ = arguments->slots[0];
  // 842: 'ÿ' = "y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__255;
  arguments->slots[1] = string__578a5af303e9c98;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_154;
}
static void cont__93_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[95] /* temp__96 */ = arguments->slots[0];
  // 843: 'Ā' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__256;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_155;
}
static void cont__93_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[96] /* temp__97 */ = arguments->slots[0];
  // 844: 'ā' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__257;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_156;
}
static void cont__93_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[97] /* temp__98 */ = arguments->slots[0];
  // 845: 'Ă' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__258;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_157;
}
static void cont__93_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[98] /* temp__99 */ = arguments->slots[0];
  // 846: 'ă' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__259;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_158;
}
static void cont__93_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[99] /* temp__100 */ = arguments->slots[0];
  // 847: 'Ą' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__260;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_159;
}
static void cont__93_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[100] /* temp__101 */ = arguments->slots[0];
  // 848: 'ą' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__261;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_160;
}
static void cont__93_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[101] /* temp__102 */ = arguments->slots[0];
  // 849: 'Ć' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__262;
  arguments->slots[1] = string__578a5af303e9ca2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_161;
}
static void cont__93_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[102] /* temp__103 */ = arguments->slots[0];
  // 850: 'ć' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__263;
  arguments->slots[1] = string__578a5af303e9c82;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_162;
}
static void cont__93_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[103] /* temp__104 */ = arguments->slots[0];
  // 851: 'Ĉ' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__264;
  arguments->slots[1] = string__578a5af303e9ca2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_163;
}
static void cont__93_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[104] /* temp__105 */ = arguments->slots[0];
  // 852: 'ĉ' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__265;
  arguments->slots[1] = string__578a5af303e9c82;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_164;
}
static void cont__93_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[105] /* temp__106 */ = arguments->slots[0];
  // 853: 'Ċ' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__266;
  arguments->slots[1] = string__578a5af303e9ca2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_165;
}
static void cont__93_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[106] /* temp__107 */ = arguments->slots[0];
  // 854: 'ċ' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__267;
  arguments->slots[1] = string__578a5af303e9c82;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_166;
}
static void cont__93_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[107] /* temp__108 */ = arguments->slots[0];
  // 855: 'Č' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__268;
  arguments->slots[1] = string__578a5af303e9ca2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_167;
}
static void cont__93_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[108] /* temp__109 */ = arguments->slots[0];
  // 856: 'č' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__269;
  arguments->slots[1] = string__578a5af303e9c82;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_168;
}
static void cont__93_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[109] /* temp__110 */ = arguments->slots[0];
  // 857: 'Ď' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__270;
  arguments->slots[1] = string__578a5af303e9ca5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_169;
}
static void cont__93_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[110] /* temp__111 */ = arguments->slots[0];
  // 858: 'ď' = "d"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__271;
  arguments->slots[1] = string__578a5af303e9c85;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_170;
}
static void cont__93_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[111] /* temp__112 */ = arguments->slots[0];
  // 859: 'Đ' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__272;
  arguments->slots[1] = string__578a5af303e9ca5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_171;
}
static void cont__93_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[112] /* temp__113 */ = arguments->slots[0];
  // 860: 'đ' = "d"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__273;
  arguments->slots[1] = string__578a5af303e9c85;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_172;
}
static void cont__93_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[113] /* temp__114 */ = arguments->slots[0];
  // 861: 'Ē' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__274;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_173;
}
static void cont__93_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[114] /* temp__115 */ = arguments->slots[0];
  // 862: 'ē' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__275;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_174;
}
static void cont__93_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[115] /* temp__116 */ = arguments->slots[0];
  // 863: 'Ĕ' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__276;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_175;
}
static void cont__93_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[116] /* temp__117 */ = arguments->slots[0];
  // 864: 'ĕ' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__277;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_176;
}
static void cont__93_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[117] /* temp__118 */ = arguments->slots[0];
  // 865: 'Ė' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__278;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_177;
}
static void cont__93_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[118] /* temp__119 */ = arguments->slots[0];
  // 866: 'ė' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__279;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_178;
}
static void cont__93_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[119] /* temp__120 */ = arguments->slots[0];
  // 867: 'Ę' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__280;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_179;
}
static void cont__93_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[120] /* temp__121 */ = arguments->slots[0];
  // 868: 'ę' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__281;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_180;
}
static void cont__93_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[121] /* temp__122 */ = arguments->slots[0];
  // 869: 'Ě' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__282;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_181;
}
static void cont__93_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[122] /* temp__123 */ = arguments->slots[0];
  // 870: 'ě' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__283;
  arguments->slots[1] = string__578a5af303e9c84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_182;
}
static void cont__93_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[123] /* temp__124 */ = arguments->slots[0];
  // 871: 'Ĝ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__284;
  arguments->slots[1] = string__578a5af303e9ca6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_184;
}
static void cont__93_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[124] /* temp__125 */ = arguments->slots[0];
  // 872: 'ĝ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__285;
  arguments->slots[1] = string__578a5af303e9c86;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_186;
}
static void cont__93_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[125] /* temp__126 */ = arguments->slots[0];
  // 873: 'Ğ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__286;
  arguments->slots[1] = string__578a5af303e9ca6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_187;
}
static void cont__93_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[126] /* temp__127 */ = arguments->slots[0];
  // 874: 'ğ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__287;
  arguments->slots[1] = string__578a5af303e9c86;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_188;
}
static void cont__93_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[127] /* temp__128 */ = arguments->slots[0];
  // 875: 'Ġ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__288;
  arguments->slots[1] = string__578a5af303e9ca6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_189;
}
static void cont__93_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[128] /* temp__129 */ = arguments->slots[0];
  // 876: 'ġ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__289;
  arguments->slots[1] = string__578a5af303e9c86;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_190;
}
static void cont__93_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[129] /* temp__130 */ = arguments->slots[0];
  // 877: 'Ģ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__290;
  arguments->slots[1] = string__578a5af303e9ca6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_191;
}
static void cont__93_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[130] /* temp__131 */ = arguments->slots[0];
  // 878: 'ģ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__291;
  arguments->slots[1] = string__578a5af303e9c86;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_192;
}
static void cont__93_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[131] /* temp__132 */ = arguments->slots[0];
  // 879: 'Ĥ' = "H"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__292;
  arguments->slots[1] = string__578a5af303e9ca9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_194;
}
static void cont__93_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[132] /* temp__133 */ = arguments->slots[0];
  // 880: 'ĥ' = "h"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__293;
  arguments->slots[1] = string__578a5af303e9c89;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_196;
}
static void cont__93_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[133] /* temp__134 */ = arguments->slots[0];
  // 881: 'Ħ' = "H"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__294;
  arguments->slots[1] = string__578a5af303e9ca9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_197;
}
static void cont__93_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[134] /* temp__135 */ = arguments->slots[0];
  // 882: 'ħ' = "h"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__295;
  arguments->slots[1] = string__578a5af303e9c89;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_198;
}
static void cont__93_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[135] /* temp__136 */ = arguments->slots[0];
  // 883: 'Ĩ' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__296;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_199;
}
static void cont__93_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[136] /* temp__137 */ = arguments->slots[0];
  // 884: 'ĩ' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__297;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_200;
}
static void cont__93_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[137] /* temp__138 */ = arguments->slots[0];
  // 885: 'Ī' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__298;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_201;
}
static void cont__93_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[138] /* temp__139 */ = arguments->slots[0];
  // 886: 'ī' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__299;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_202;
}
static void cont__93_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[139] /* temp__140 */ = arguments->slots[0];
  // 887: 'Ĭ' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__300;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_203;
}
static void cont__93_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[140] /* temp__141 */ = arguments->slots[0];
  // 888: 'ĭ' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__301;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_204;
}
static void cont__93_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[141] /* temp__142 */ = arguments->slots[0];
  // 889: 'Į' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__302;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_205;
}
static void cont__93_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[142] /* temp__143 */ = arguments->slots[0];
  // 890: 'į' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__303;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_206;
}
static void cont__93_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[143] /* temp__144 */ = arguments->slots[0];
  // 891: 'İ' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__304;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_207;
}
static void cont__93_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[144] /* temp__145 */ = arguments->slots[0];
  // 892: 'ı' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__305;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_208;
}
static void cont__93_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[145] /* temp__146 */ = arguments->slots[0];
  // 893: 'Ĳ' = "IJ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__306;
  arguments->slots[1] = string__2d7981f4e5402b8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_210;
}
static void cont__93_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[146] /* temp__147 */ = arguments->slots[0];
  // 894: 'ĳ' = "ij"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__307;
  arguments->slots[1] = string__2d7981f4e4402baf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_212;
}
static void cont__93_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[147] /* temp__148 */ = arguments->slots[0];
  // 895: 'Ĵ' = "J"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__308;
  arguments->slots[1] = string__578a5af303e9cab;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_214;
}
static void cont__93_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[148] /* temp__149 */ = arguments->slots[0];
  // 896: 'ĵ' = "j"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__309;
  arguments->slots[1] = string__578a5af303e9c8b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_216;
}
static void cont__93_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[149] /* temp__150 */ = arguments->slots[0];
  // 897: 'Ķ' = "K"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__310;
  arguments->slots[1] = string__578a5af303e9caa;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_218;
}
static void cont__93_218(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[150] /* temp__151 */ = arguments->slots[0];
  // 898: 'ķ' = "k"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__311;
  arguments->slots[1] = string__578a5af303e9c8a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_220;
}
static void cont__93_220(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[151] /* temp__152 */ = arguments->slots[0];
  // 899: 'ĸ' = "k"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__312;
  arguments->slots[1] = string__578a5af303e9c8a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_221;
}
static void cont__93_221(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[152] /* temp__153 */ = arguments->slots[0];
  // 900: 'Ĺ' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__313;
  arguments->slots[1] = string__578a5af303e9cad;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_223;
}
static void cont__93_223(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[153] /* temp__154 */ = arguments->slots[0];
  // 901: 'ĺ' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__314;
  arguments->slots[1] = string__578a5af303e9c8d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_225;
}
static void cont__93_225(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[154] /* temp__155 */ = arguments->slots[0];
  // 902: 'Ļ' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__315;
  arguments->slots[1] = string__578a5af303e9cad;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_226;
}
static void cont__93_226(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[155] /* temp__156 */ = arguments->slots[0];
  // 903: 'ļ' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__316;
  arguments->slots[1] = string__578a5af303e9c8d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_227;
}
static void cont__93_227(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[156] /* temp__157 */ = arguments->slots[0];
  // 904: 'Ľ' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__317;
  arguments->slots[1] = string__578a5af303e9cad;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_228;
}
static void cont__93_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[157] /* temp__158 */ = arguments->slots[0];
  // 905: 'ľ' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__318;
  arguments->slots[1] = string__578a5af303e9c8d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_229;
}
static void cont__93_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[158] /* temp__159 */ = arguments->slots[0];
  // 906: 'Ŀ' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__319;
  arguments->slots[1] = string__578a5af303e9cad;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_230;
}
static void cont__93_230(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[159] /* temp__160 */ = arguments->slots[0];
  // 907: 'ŀ' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__320;
  arguments->slots[1] = string__578a5af303e9c8d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_231;
}
static void cont__93_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[160] /* temp__161 */ = arguments->slots[0];
  // 908: 'Ł' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__321;
  arguments->slots[1] = string__578a5af303e9cad;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_232;
}
static void cont__93_232(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[161] /* temp__162 */ = arguments->slots[0];
  // 909: 'ł' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__322;
  arguments->slots[1] = string__578a5af303e9c8d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_233;
}
static void cont__93_233(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[162] /* temp__163 */ = arguments->slots[0];
  // 910: 'Ń' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__323;
  arguments->slots[1] = string__578a5af303e9caf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_234;
}
static void cont__93_234(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[163] /* temp__164 */ = arguments->slots[0];
  // 911: 'ń' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__324;
  arguments->slots[1] = string__578a5af303e9c8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_235;
}
static void cont__93_235(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[164] /* temp__165 */ = arguments->slots[0];
  // 912: 'Ņ' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__325;
  arguments->slots[1] = string__578a5af303e9caf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_236;
}
static void cont__93_236(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[165] /* temp__166 */ = arguments->slots[0];
  // 913: 'ņ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__326;
  arguments->slots[1] = string__578a5af303e9c8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_237;
}
static void cont__93_237(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[166] /* temp__167 */ = arguments->slots[0];
  // 914: 'Ň' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__327;
  arguments->slots[1] = string__578a5af303e9caf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_238;
}
static void cont__93_238(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[167] /* temp__168 */ = arguments->slots[0];
  // 915: 'ň' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__328;
  arguments->slots[1] = string__578a5af303e9c8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_239;
}
static void cont__93_239(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[168] /* temp__169 */ = arguments->slots[0];
  // 916: 'ŉ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__329;
  arguments->slots[1] = string__578a5af303e9c8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_240;
}
static void cont__93_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[169] /* temp__170 */ = arguments->slots[0];
  // 917: 'Ŋ' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__330;
  arguments->slots[1] = string__578a5af303e9caf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_241;
}
static void cont__93_241(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[170] /* temp__171 */ = arguments->slots[0];
  // 918: 'ŋ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__331;
  arguments->slots[1] = string__578a5af303e9c8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_242;
}
static void cont__93_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[171] /* temp__172 */ = arguments->slots[0];
  // 919: 'Ō' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__332;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_243;
}
static void cont__93_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[172] /* temp__173 */ = arguments->slots[0];
  // 920: 'ō' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__333;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_244;
}
static void cont__93_244(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[173] /* temp__174 */ = arguments->slots[0];
  // 921: 'Ŏ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__334;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_245;
}
static void cont__93_245(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[174] /* temp__175 */ = arguments->slots[0];
  // 922: 'ŏ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__335;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_246;
}
static void cont__93_246(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[175] /* temp__176 */ = arguments->slots[0];
  // 923: 'Ő' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__336;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_247;
}
static void cont__93_247(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[176] /* temp__177 */ = arguments->slots[0];
  // 924: 'ő' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__337;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_248;
}
static void cont__93_248(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[177] /* temp__178 */ = arguments->slots[0];
  // 925: 'Œ' = "OE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__338;
  arguments->slots[1] = string__2d7981f4e5702b80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_250;
}
static void cont__93_250(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[178] /* temp__179 */ = arguments->slots[0];
  // 926: 'œ' = "oe"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__339;
  arguments->slots[1] = string__2d7981f4e4702ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_251;
}
static void cont__93_251(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[179] /* temp__180 */ = arguments->slots[0];
  // 927: 'Ŕ' = "R"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__340;
  arguments->slots[1] = string__578a5af303e9cb3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_253;
}
static void cont__93_253(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[180] /* temp__181 */ = arguments->slots[0];
  // 928: 'ŕ' = "r"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__341;
  arguments->slots[1] = string__578a5af303e9c93;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_255;
}
static void cont__93_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[181] /* temp__182 */ = arguments->slots[0];
  // 929: 'Ŗ' = "R"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__342;
  arguments->slots[1] = string__578a5af303e9cb3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_256;
}
static void cont__93_256(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[182] /* temp__183 */ = arguments->slots[0];
  // 930: 'ŗ' = "r"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__343;
  arguments->slots[1] = string__578a5af303e9c93;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_257;
}
static void cont__93_257(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[183] /* temp__184 */ = arguments->slots[0];
  // 931: 'Ř' = "R"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__344;
  arguments->slots[1] = string__578a5af303e9cb3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_258;
}
static void cont__93_258(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[184] /* temp__185 */ = arguments->slots[0];
  // 932: 'ř' = "r"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__345;
  arguments->slots[1] = string__578a5af303e9c93;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_259;
}
static void cont__93_259(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[185] /* temp__186 */ = arguments->slots[0];
  // 933: 'Ś' = "S"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__346;
  arguments->slots[1] = string__578a5af303e9cb2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_261;
}
static void cont__93_261(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[186] /* temp__187 */ = arguments->slots[0];
  // 934: 'ś' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__347;
  arguments->slots[1] = string__578a5af303e9c92;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_263;
}
static void cont__93_263(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[187] /* temp__188 */ = arguments->slots[0];
  // 935: 'Ŝ' = "S"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__348;
  arguments->slots[1] = string__578a5af303e9cb2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_264;
}
static void cont__93_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[188] /* temp__189 */ = arguments->slots[0];
  // 936: 'ŝ' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__349;
  arguments->slots[1] = string__578a5af303e9c92;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_265;
}
static void cont__93_265(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[189] /* temp__190 */ = arguments->slots[0];
  // 937: 'Ş' = "S"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__350;
  arguments->slots[1] = string__578a5af303e9cb2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_266;
}
static void cont__93_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[190] /* temp__191 */ = arguments->slots[0];
  // 938: 'ş' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__351;
  arguments->slots[1] = string__578a5af303e9c92;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_267;
}
static void cont__93_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[191] /* temp__192 */ = arguments->slots[0];
  // 939: 'Š' = "S"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__352;
  arguments->slots[1] = string__578a5af303e9cb2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_268;
}
static void cont__93_268(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[192] /* temp__193 */ = arguments->slots[0];
  // 940: 'š' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__353;
  arguments->slots[1] = string__578a5af303e9c92;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_269;
}
static void cont__93_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[193] /* temp__194 */ = arguments->slots[0];
  // 941: 'Ţ' = "T"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__354;
  arguments->slots[1] = string__578a5af303e9cb5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_271;
}
static void cont__93_271(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[194] /* temp__195 */ = arguments->slots[0];
  // 942: 'ţ' = "t"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__355;
  arguments->slots[1] = string__578a5af303e9c95;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_273;
}
static void cont__93_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[195] /* temp__196 */ = arguments->slots[0];
  // 943: 'Ť' = "T"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__356;
  arguments->slots[1] = string__578a5af303e9cb5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_274;
}
static void cont__93_274(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[196] /* temp__197 */ = arguments->slots[0];
  // 944: 'ť' = "t"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__357;
  arguments->slots[1] = string__578a5af303e9c95;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_275;
}
static void cont__93_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[197] /* temp__198 */ = arguments->slots[0];
  // 945: 'Ŧ' = "T"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__358;
  arguments->slots[1] = string__578a5af303e9cb5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_276;
}
static void cont__93_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[198] /* temp__199 */ = arguments->slots[0];
  // 946: 'ŧ' = "t"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__359;
  arguments->slots[1] = string__578a5af303e9c95;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_277;
}
static void cont__93_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[199] /* temp__200 */ = arguments->slots[0];
  // 947: 'Ũ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__360;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_278;
}
static void cont__93_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[200] /* temp__201 */ = arguments->slots[0];
  // 948: 'ũ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__361;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_279;
}
static void cont__93_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[201] /* temp__202 */ = arguments->slots[0];
  // 949: 'Ū' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__362;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_280;
}
static void cont__93_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[202] /* temp__203 */ = arguments->slots[0];
  // 950: 'ū' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__363;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_281;
}
static void cont__93_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[203] /* temp__204 */ = arguments->slots[0];
  // 951: 'Ŭ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__364;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_282;
}
static void cont__93_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[204] /* temp__205 */ = arguments->slots[0];
  // 952: 'ŭ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__365;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_283;
}
static void cont__93_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[205] /* temp__206 */ = arguments->slots[0];
  // 953: 'Ů' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__366;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_284;
}
static void cont__93_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[206] /* temp__207 */ = arguments->slots[0];
  // 954: 'ů' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__367;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_285;
}
static void cont__93_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[207] /* temp__208 */ = arguments->slots[0];
  // 955: 'Ű' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__368;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_286;
}
static void cont__93_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[208] /* temp__209 */ = arguments->slots[0];
  // 956: 'ű' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__369;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_287;
}
static void cont__93_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[209] /* temp__210 */ = arguments->slots[0];
  // 957: 'Ų' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__370;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_288;
}
static void cont__93_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[210] /* temp__211 */ = arguments->slots[0];
  // 958: 'ų' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__371;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_289;
}
static void cont__93_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[211] /* temp__212 */ = arguments->slots[0];
  // 959: 'Ŵ' = "W"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__372;
  arguments->slots[1] = string__578a5af303e9cb6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_291;
}
static void cont__93_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[212] /* temp__213 */ = arguments->slots[0];
  // 960: 'ŵ' = "w"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__373;
  arguments->slots[1] = string__578a5af303e9c96;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_293;
}
static void cont__93_293(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[213] /* temp__214 */ = arguments->slots[0];
  // 961: 'Ŷ' = "Y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__374;
  arguments->slots[1] = string__578a5af303e9cb8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_294;
}
static void cont__93_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[214] /* temp__215 */ = arguments->slots[0];
  // 962: 'ŷ' = "y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__375;
  arguments->slots[1] = string__578a5af303e9c98;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_295;
}
static void cont__93_295(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[215] /* temp__216 */ = arguments->slots[0];
  // 963: 'Ÿ' = "Y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__376;
  arguments->slots[1] = string__578a5af303e9cb8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_296;
}
static void cont__93_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[216] /* temp__217 */ = arguments->slots[0];
  // 964: 'Ź' = "Z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__377;
  arguments->slots[1] = string__578a5af303e9cbb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_298;
}
static void cont__93_298(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[217] /* temp__218 */ = arguments->slots[0];
  // 965: 'ź' = "z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__378;
  arguments->slots[1] = string__578a5af303e9c9b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_300;
}
static void cont__93_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[218] /* temp__219 */ = arguments->slots[0];
  // 966: 'Ż' = "Z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__379;
  arguments->slots[1] = string__578a5af303e9cbb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_301;
}
static void cont__93_301(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[219] /* temp__220 */ = arguments->slots[0];
  // 967: 'ż' = "z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__380;
  arguments->slots[1] = string__578a5af303e9c9b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_302;
}
static void cont__93_302(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[220] /* temp__221 */ = arguments->slots[0];
  // 968: 'Ž' = "Z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__381;
  arguments->slots[1] = string__578a5af303e9cbb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_303;
}
static void cont__93_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[221] /* temp__222 */ = arguments->slots[0];
  // 969: 'ž' = "z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__382;
  arguments->slots[1] = string__578a5af303e9c9b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_304;
}
static void cont__93_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[222] /* temp__223 */ = arguments->slots[0];
  // 970: 'ſ' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__383;
  arguments->slots[1] = string__578a5af303e9c92;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_305;
}
static void cont__93_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[223] /* temp__224 */ = arguments->slots[0];
  // 971: 'ƀ' = "b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__384;
  arguments->slots[1] = string__578a5af303e9c83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_307;
}
static void cont__93_307(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[224] /* temp__225 */ = arguments->slots[0];
  // 972: 'Ɓ' = "B"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__385;
  arguments->slots[1] = string__578a5af303e9ca3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_309;
}
static void cont__93_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[225] /* temp__226 */ = arguments->slots[0];
  // 973: 'Ƃ' = "B"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__386;
  arguments->slots[1] = string__578a5af303e9ca3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_310;
}
static void cont__93_310(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[226] /* temp__227 */ = arguments->slots[0];
  // 974: 'ƃ' = "b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__387;
  arguments->slots[1] = string__578a5af303e9c83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_311;
}
static void cont__93_311(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[227] /* temp__228 */ = arguments->slots[0];
  // 975: 'Ƅ' = "b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__388;
  arguments->slots[1] = string__578a5af303e9c83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_312;
}
static void cont__93_312(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[228] /* temp__229 */ = arguments->slots[0];
  // 976: 'ƅ' = "b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__389;
  arguments->slots[1] = string__578a5af303e9c83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_313;
}
static void cont__93_313(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[229] /* temp__230 */ = arguments->slots[0];
  // 977: 'Ƈ' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__391;
  arguments->slots[1] = string__578a5af303e9ca2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_314;
}
static void cont__93_314(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[230] /* temp__231 */ = arguments->slots[0];
  // 978: 'ƈ' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__392;
  arguments->slots[1] = string__578a5af303e9c82;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_315;
}
static void cont__93_315(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[231] /* temp__232 */ = arguments->slots[0];
  // 979: 'Ɖ' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__393;
  arguments->slots[1] = string__578a5af303e9ca5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_316;
}
static void cont__93_316(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[232] /* temp__233 */ = arguments->slots[0];
  // 980: 'Ɗ' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__394;
  arguments->slots[1] = string__578a5af303e9ca5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_317;
}
static void cont__93_317(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[233] /* temp__234 */ = arguments->slots[0];
  // 981: 'Ƌ' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__395;
  arguments->slots[1] = string__578a5af303e9ca5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_318;
}
static void cont__93_318(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[234] /* temp__235 */ = arguments->slots[0];
  // 982: 'ƌ' = "d"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__396;
  arguments->slots[1] = string__578a5af303e9c85;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_319;
}
static void cont__93_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[235] /* temp__236 */ = arguments->slots[0];
  // 983: 'ƍ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__397;
  arguments->slots[1] = string__578a5af303e9c86;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_320;
}
static void cont__93_320(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[236] /* temp__237 */ = arguments->slots[0];
  // 984: 'Ɛ' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__400;
  arguments->slots[1] = string__578a5af303e9ca4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_321;
}
static void cont__93_321(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[237] /* temp__238 */ = arguments->slots[0];
  // 985: 'Ƒ' = "F"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__401;
  arguments->slots[1] = string__578a5af303e9ca7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_323;
}
static void cont__93_323(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[238] /* temp__239 */ = arguments->slots[0];
  // 986: 'ƒ' = "f"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__402;
  arguments->slots[1] = string__578a5af303e9c87;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_325;
}
static void cont__93_325(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[239] /* temp__240 */ = arguments->slots[0];
  // 987: 'Ɠ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__403;
  arguments->slots[1] = string__578a5af303e9ca6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_326;
}
static void cont__93_326(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[240] /* temp__241 */ = arguments->slots[0];
  // 988: 'Ǆ' = "DZ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__452;
  arguments->slots[1] = string__2d7981f4e5282b9f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_328;
}
static void cont__93_328(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[241] /* temp__242 */ = arguments->slots[0];
  // 989: 'ǅ' = "Dz"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__453;
  arguments->slots[1] = string__2d7981f4e5282bbf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_330;
}
static void cont__93_330(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[242] /* temp__243 */ = arguments->slots[0];
  // 990: 'ǆ' = "dz"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__454;
  arguments->slots[1] = string__2d7981f4e4282bbf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_332;
}
static void cont__93_332(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[243] /* temp__244 */ = arguments->slots[0];
  // 991: 'Ǉ' = "LJ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__455;
  arguments->slots[1] = string__2d7981f4e5682b8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_334;
}
static void cont__93_334(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[244] /* temp__245 */ = arguments->slots[0];
  // 992: 'ǈ' = "Lj"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__456;
  arguments->slots[1] = string__2d7981f4e5682baf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_336;
}
static void cont__93_336(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[245] /* temp__246 */ = arguments->slots[0];
  // 993: 'ǉ' = "lj"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__457;
  arguments->slots[1] = string__2d7981f4e4682baf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_338;
}
static void cont__93_338(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[246] /* temp__247 */ = arguments->slots[0];
  // 994: 'Ǌ' = "NJ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__458;
  arguments->slots[1] = string__2d7981f4e5782b8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_340;
}
static void cont__93_340(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[247] /* temp__248 */ = arguments->slots[0];
  // 995: 'ǋ' = "Nj"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__459;
  arguments->slots[1] = string__2d7981f4e5782baf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_342;
}
static void cont__93_342(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[248] /* temp__249 */ = arguments->slots[0];
  // 996: 'ǌ' = "nj"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__460;
  arguments->slots[1] = string__2d7981f4e4782baf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_344;
}
static void cont__93_344(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[249] /* temp__250 */ = arguments->slots[0];
  // 997: 'Ǎ' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__461;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_345;
}
static void cont__93_345(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[250] /* temp__251 */ = arguments->slots[0];
  // 998: 'ǎ' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__462;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_346;
}
static void cont__93_346(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[251] /* temp__252 */ = arguments->slots[0];
  // 999: 'Ǐ' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__463;
  arguments->slots[1] = string__578a5af303e9ca8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_347;
}
static void cont__93_347(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[252] /* temp__253 */ = arguments->slots[0];
  // 1000: 'ǐ' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__464;
  arguments->slots[1] = string__578a5af303e9c88;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_348;
}
static void cont__93_348(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[253] /* temp__254 */ = arguments->slots[0];
  // 1001: 'Ǒ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__465;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_349;
}
static void cont__93_349(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[254] /* temp__255 */ = arguments->slots[0];
  // 1002: 'ǒ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__466;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_350;
}
static void cont__93_350(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[255] /* temp__256 */ = arguments->slots[0];
  // 1003: 'Ǔ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__467;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_351;
}
static void cont__93_351(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[256] /* temp__257 */ = arguments->slots[0];
  // 1004: 'ǔ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__468;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_352;
}
static void cont__93_352(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[257] /* temp__258 */ = arguments->slots[0];
  // 1005: 'Ǖ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__469;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_353;
}
static void cont__93_353(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[258] /* temp__259 */ = arguments->slots[0];
  // 1006: 'ǖ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__470;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_354;
}
static void cont__93_354(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[259] /* temp__260 */ = arguments->slots[0];
  // 1007: 'Ǘ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__471;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_355;
}
static void cont__93_355(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[260] /* temp__261 */ = arguments->slots[0];
  // 1008: 'ǘ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__472;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_356;
}
static void cont__93_356(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[261] /* temp__262 */ = arguments->slots[0];
  // 1009: 'Ǚ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__473;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_357;
}
static void cont__93_357(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[262] /* temp__263 */ = arguments->slots[0];
  // 1010: 'ǚ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__474;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_358;
}
static void cont__93_358(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[263] /* temp__264 */ = arguments->slots[0];
  // 1011: 'Ǜ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__475;
  arguments->slots[1] = string__578a5af303e9cb4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_359;
}
static void cont__93_359(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[264] /* temp__265 */ = arguments->slots[0];
  // 1012: 'ǜ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__476;
  arguments->slots[1] = string__578a5af303e9c94;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_360;
}
static void cont__93_360(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[265] /* temp__266 */ = arguments->slots[0];
  // 1013: 'Ǟ' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__478;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_361;
}
static void cont__93_361(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[266] /* temp__267 */ = arguments->slots[0];
  // 1014: 'ǟ' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__479;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_362;
}
static void cont__93_362(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[267] /* temp__268 */ = arguments->slots[0];
  // 1015: 'Ǡ' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__480;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_363;
}
static void cont__93_363(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[268] /* temp__269 */ = arguments->slots[0];
  // 1016: 'ǡ' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__481;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_364;
}
static void cont__93_364(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[269] /* temp__270 */ = arguments->slots[0];
  // 1017: 'Ǣ' = "AE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__482;
  arguments->slots[1] = string__2d7981f4e5002b80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_365;
}
static void cont__93_365(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[270] /* temp__271 */ = arguments->slots[0];
  // 1018: 'ǣ' = "ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__483;
  arguments->slots[1] = string__2d7981f4e4002ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_366;
}
static void cont__93_366(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[271] /* temp__272 */ = arguments->slots[0];
  // 1019: 'Ǥ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__484;
  arguments->slots[1] = string__578a5af303e9ca6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_367;
}
static void cont__93_367(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[272] /* temp__273 */ = arguments->slots[0];
  // 1020: 'ǥ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__485;
  arguments->slots[1] = string__578a5af303e9c86;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_368;
}
static void cont__93_368(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[273] /* temp__274 */ = arguments->slots[0];
  // 1021: 'Ǧ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__486;
  arguments->slots[1] = string__578a5af303e9ca6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_369;
}
static void cont__93_369(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[274] /* temp__275 */ = arguments->slots[0];
  // 1022: 'ǧ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__487;
  arguments->slots[1] = string__578a5af303e9c86;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_370;
}
static void cont__93_370(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[275] /* temp__276 */ = arguments->slots[0];
  // 1023: 'Ǩ' = "K"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__488;
  arguments->slots[1] = string__578a5af303e9caa;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_371;
}
static void cont__93_371(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[276] /* temp__277 */ = arguments->slots[0];
  // 1024: 'ǩ' = "k"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__489;
  arguments->slots[1] = string__578a5af303e9c8a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_372;
}
static void cont__93_372(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[277] /* temp__278 */ = arguments->slots[0];
  // 1025: 'Ǫ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__490;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_373;
}
static void cont__93_373(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[278] /* temp__279 */ = arguments->slots[0];
  // 1026: 'ǫ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__491;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_374;
}
static void cont__93_374(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[279] /* temp__280 */ = arguments->slots[0];
  // 1027: 'Ǭ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__492;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_375;
}
static void cont__93_375(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[280] /* temp__281 */ = arguments->slots[0];
  // 1028: 'ǭ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__493;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_376;
}
static void cont__93_376(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[281] /* temp__282 */ = arguments->slots[0];
  // 1029: 'Ǳ' = "DZ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__497;
  arguments->slots[1] = string__2d7981f4e5282b9f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_377;
}
static void cont__93_377(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[282] /* temp__283 */ = arguments->slots[0];
  // 1030: 'ǲ' = "Dz"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__498;
  arguments->slots[1] = string__2d7981f4e5282bbf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_378;
}
static void cont__93_378(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[283] /* temp__284 */ = arguments->slots[0];
  // 1031: 'ǳ' = "dz"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__499;
  arguments->slots[1] = string__2d7981f4e4282bbf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_379;
}
static void cont__93_379(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[284] /* temp__285 */ = arguments->slots[0];
  // 1032: 'Ǵ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__500;
  arguments->slots[1] = string__578a5af303e9ca6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_380;
}
static void cont__93_380(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[285] /* temp__286 */ = arguments->slots[0];
  // 1033: 'ǵ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__501;
  arguments->slots[1] = string__578a5af303e9c86;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_381;
}
static void cont__93_381(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[286] /* temp__287 */ = arguments->slots[0];
  // 1034: 'Ǹ' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__504;
  arguments->slots[1] = string__578a5af303e9caf;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_382;
}
static void cont__93_382(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[287] /* temp__288 */ = arguments->slots[0];
  // 1035: 'ǹ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__505;
  arguments->slots[1] = string__578a5af303e9c8f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_383;
}
static void cont__93_383(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[288] /* temp__289 */ = arguments->slots[0];
  // 1036: 'Ǻ' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__506;
  arguments->slots[1] = string__578a5af303e9ca0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_384;
}
static void cont__93_384(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[289] /* temp__290 */ = arguments->slots[0];
  // 1037: 'ǻ' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__507;
  arguments->slots[1] = string__578a5af303e9c80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_385;
}
static void cont__93_385(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[290] /* temp__291 */ = arguments->slots[0];
  // 1038: 'Ǽ' = "AE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__508;
  arguments->slots[1] = string__2d7981f4e5002b80;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_386;
}
static void cont__93_386(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[291] /* temp__292 */ = arguments->slots[0];
  // 1039: 'ǽ' = "ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__509;
  arguments->slots[1] = string__2d7981f4e4002ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_387;
}
static void cont__93_387(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[292] /* temp__293 */ = arguments->slots[0];
  // 1040: 'Ǿ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__510;
  arguments->slots[1] = string__578a5af303e9cae;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_388;
}
static void cont__93_388(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[293] /* temp__294 */ = arguments->slots[0];
  // 1041: 'ǿ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__511;
  arguments->slots[1] = string__578a5af303e9c8e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_389;
}
static void cont__93_389(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[294] /* temp__295 */ = arguments->slots[0];
  // 745: $umlaut_conversions
  // 746:   table
  // 747:     '@nbsp;' = " "
  // 748:     '¡' = "!"
  // 749:     '¢' = "(cent)"
  // 750:     '£' = "(pound)"
  // 751:     '¤' = "?"
  // 752:     '¥' = "(yen)"
  // 753:     '¦' = "|"
  // 754:     '§' = "$"
  // ...
  argument_count = 295;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  arguments->slots[4] = frame->slots[4] /* temp__5 */;
  arguments->slots[5] = frame->slots[5] /* temp__6 */;
  arguments->slots[6] = frame->slots[6] /* temp__7 */;
  arguments->slots[7] = frame->slots[7] /* temp__8 */;
  arguments->slots[8] = frame->slots[8] /* temp__9 */;
  arguments->slots[9] = frame->slots[9] /* temp__10 */;
  arguments->slots[10] = frame->slots[10] /* temp__11 */;
  arguments->slots[11] = frame->slots[11] /* temp__12 */;
  arguments->slots[12] = frame->slots[12] /* temp__13 */;
  arguments->slots[13] = frame->slots[13] /* temp__14 */;
  arguments->slots[14] = frame->slots[14] /* temp__15 */;
  arguments->slots[15] = frame->slots[15] /* temp__16 */;
  arguments->slots[16] = frame->slots[16] /* temp__17 */;
  arguments->slots[17] = frame->slots[17] /* temp__18 */;
  arguments->slots[18] = frame->slots[18] /* temp__19 */;
  arguments->slots[19] = frame->slots[19] /* temp__20 */;
  arguments->slots[20] = frame->slots[20] /* temp__21 */;
  arguments->slots[21] = frame->slots[21] /* temp__22 */;
  arguments->slots[22] = frame->slots[22] /* temp__23 */;
  arguments->slots[23] = frame->slots[23] /* temp__24 */;
  arguments->slots[24] = frame->slots[24] /* temp__25 */;
  arguments->slots[25] = frame->slots[25] /* temp__26 */;
  arguments->slots[26] = frame->slots[26] /* temp__27 */;
  arguments->slots[27] = frame->slots[27] /* temp__28 */;
  arguments->slots[28] = frame->slots[28] /* temp__29 */;
  arguments->slots[29] = frame->slots[29] /* temp__30 */;
  arguments->slots[30] = frame->slots[30] /* temp__31 */;
  arguments->slots[31] = frame->slots[31] /* temp__32 */;
  arguments->slots[32] = frame->slots[32] /* temp__33 */;
  arguments->slots[33] = frame->slots[33] /* temp__34 */;
  arguments->slots[34] = frame->slots[34] /* temp__35 */;
  arguments->slots[35] = frame->slots[35] /* temp__36 */;
  arguments->slots[36] = frame->slots[36] /* temp__37 */;
  arguments->slots[37] = frame->slots[37] /* temp__38 */;
  arguments->slots[38] = frame->slots[38] /* temp__39 */;
  arguments->slots[39] = frame->slots[39] /* temp__40 */;
  arguments->slots[40] = frame->slots[40] /* temp__41 */;
  arguments->slots[41] = frame->slots[41] /* temp__42 */;
  arguments->slots[42] = frame->slots[42] /* temp__43 */;
  arguments->slots[43] = frame->slots[43] /* temp__44 */;
  arguments->slots[44] = frame->slots[44] /* temp__45 */;
  arguments->slots[45] = frame->slots[45] /* temp__46 */;
  arguments->slots[46] = frame->slots[46] /* temp__47 */;
  arguments->slots[47] = frame->slots[47] /* temp__48 */;
  arguments->slots[48] = frame->slots[48] /* temp__49 */;
  arguments->slots[49] = frame->slots[49] /* temp__50 */;
  arguments->slots[50] = frame->slots[50] /* temp__51 */;
  arguments->slots[51] = frame->slots[51] /* temp__52 */;
  arguments->slots[52] = frame->slots[52] /* temp__53 */;
  arguments->slots[53] = frame->slots[53] /* temp__54 */;
  arguments->slots[54] = frame->slots[54] /* temp__55 */;
  arguments->slots[55] = frame->slots[55] /* temp__56 */;
  arguments->slots[56] = frame->slots[56] /* temp__57 */;
  arguments->slots[57] = frame->slots[57] /* temp__58 */;
  arguments->slots[58] = frame->slots[58] /* temp__59 */;
  arguments->slots[59] = frame->slots[59] /* temp__60 */;
  arguments->slots[60] = frame->slots[60] /* temp__61 */;
  arguments->slots[61] = frame->slots[61] /* temp__62 */;
  arguments->slots[62] = frame->slots[62] /* temp__63 */;
  arguments->slots[63] = frame->slots[63] /* temp__64 */;
  arguments->slots[64] = frame->slots[64] /* temp__65 */;
  arguments->slots[65] = frame->slots[65] /* temp__66 */;
  arguments->slots[66] = frame->slots[66] /* temp__67 */;
  arguments->slots[67] = frame->slots[67] /* temp__68 */;
  arguments->slots[68] = frame->slots[68] /* temp__69 */;
  arguments->slots[69] = frame->slots[69] /* temp__70 */;
  arguments->slots[70] = frame->slots[70] /* temp__71 */;
  arguments->slots[71] = frame->slots[71] /* temp__72 */;
  arguments->slots[72] = frame->slots[72] /* temp__73 */;
  arguments->slots[73] = frame->slots[73] /* temp__74 */;
  arguments->slots[74] = frame->slots[74] /* temp__75 */;
  arguments->slots[75] = frame->slots[75] /* temp__76 */;
  arguments->slots[76] = frame->slots[76] /* temp__77 */;
  arguments->slots[77] = frame->slots[77] /* temp__78 */;
  arguments->slots[78] = frame->slots[78] /* temp__79 */;
  arguments->slots[79] = frame->slots[79] /* temp__80 */;
  arguments->slots[80] = frame->slots[80] /* temp__81 */;
  arguments->slots[81] = frame->slots[81] /* temp__82 */;
  arguments->slots[82] = frame->slots[82] /* temp__83 */;
  arguments->slots[83] = frame->slots[83] /* temp__84 */;
  arguments->slots[84] = frame->slots[84] /* temp__85 */;
  arguments->slots[85] = frame->slots[85] /* temp__86 */;
  arguments->slots[86] = frame->slots[86] /* temp__87 */;
  arguments->slots[87] = frame->slots[87] /* temp__88 */;
  arguments->slots[88] = frame->slots[88] /* temp__89 */;
  arguments->slots[89] = frame->slots[89] /* temp__90 */;
  arguments->slots[90] = frame->slots[90] /* temp__91 */;
  arguments->slots[91] = frame->slots[91] /* temp__92 */;
  arguments->slots[92] = frame->slots[92] /* temp__93 */;
  arguments->slots[93] = frame->slots[93] /* temp__94 */;
  arguments->slots[94] = frame->slots[94] /* temp__95 */;
  arguments->slots[95] = frame->slots[95] /* temp__96 */;
  arguments->slots[96] = frame->slots[96] /* temp__97 */;
  arguments->slots[97] = frame->slots[97] /* temp__98 */;
  arguments->slots[98] = frame->slots[98] /* temp__99 */;
  arguments->slots[99] = frame->slots[99] /* temp__100 */;
  arguments->slots[100] = frame->slots[100] /* temp__101 */;
  arguments->slots[101] = frame->slots[101] /* temp__102 */;
  arguments->slots[102] = frame->slots[102] /* temp__103 */;
  arguments->slots[103] = frame->slots[103] /* temp__104 */;
  arguments->slots[104] = frame->slots[104] /* temp__105 */;
  arguments->slots[105] = frame->slots[105] /* temp__106 */;
  arguments->slots[106] = frame->slots[106] /* temp__107 */;
  arguments->slots[107] = frame->slots[107] /* temp__108 */;
  arguments->slots[108] = frame->slots[108] /* temp__109 */;
  arguments->slots[109] = frame->slots[109] /* temp__110 */;
  arguments->slots[110] = frame->slots[110] /* temp__111 */;
  arguments->slots[111] = frame->slots[111] /* temp__112 */;
  arguments->slots[112] = frame->slots[112] /* temp__113 */;
  arguments->slots[113] = frame->slots[113] /* temp__114 */;
  arguments->slots[114] = frame->slots[114] /* temp__115 */;
  arguments->slots[115] = frame->slots[115] /* temp__116 */;
  arguments->slots[116] = frame->slots[116] /* temp__117 */;
  arguments->slots[117] = frame->slots[117] /* temp__118 */;
  arguments->slots[118] = frame->slots[118] /* temp__119 */;
  arguments->slots[119] = frame->slots[119] /* temp__120 */;
  arguments->slots[120] = frame->slots[120] /* temp__121 */;
  arguments->slots[121] = frame->slots[121] /* temp__122 */;
  arguments->slots[122] = frame->slots[122] /* temp__123 */;
  arguments->slots[123] = frame->slots[123] /* temp__124 */;
  arguments->slots[124] = frame->slots[124] /* temp__125 */;
  arguments->slots[125] = frame->slots[125] /* temp__126 */;
  arguments->slots[126] = frame->slots[126] /* temp__127 */;
  arguments->slots[127] = frame->slots[127] /* temp__128 */;
  arguments->slots[128] = frame->slots[128] /* temp__129 */;
  arguments->slots[129] = frame->slots[129] /* temp__130 */;
  arguments->slots[130] = frame->slots[130] /* temp__131 */;
  arguments->slots[131] = frame->slots[131] /* temp__132 */;
  arguments->slots[132] = frame->slots[132] /* temp__133 */;
  arguments->slots[133] = frame->slots[133] /* temp__134 */;
  arguments->slots[134] = frame->slots[134] /* temp__135 */;
  arguments->slots[135] = frame->slots[135] /* temp__136 */;
  arguments->slots[136] = frame->slots[136] /* temp__137 */;
  arguments->slots[137] = frame->slots[137] /* temp__138 */;
  arguments->slots[138] = frame->slots[138] /* temp__139 */;
  arguments->slots[139] = frame->slots[139] /* temp__140 */;
  arguments->slots[140] = frame->slots[140] /* temp__141 */;
  arguments->slots[141] = frame->slots[141] /* temp__142 */;
  arguments->slots[142] = frame->slots[142] /* temp__143 */;
  arguments->slots[143] = frame->slots[143] /* temp__144 */;
  arguments->slots[144] = frame->slots[144] /* temp__145 */;
  arguments->slots[145] = frame->slots[145] /* temp__146 */;
  arguments->slots[146] = frame->slots[146] /* temp__147 */;
  arguments->slots[147] = frame->slots[147] /* temp__148 */;
  arguments->slots[148] = frame->slots[148] /* temp__149 */;
  arguments->slots[149] = frame->slots[149] /* temp__150 */;
  arguments->slots[150] = frame->slots[150] /* temp__151 */;
  arguments->slots[151] = frame->slots[151] /* temp__152 */;
  arguments->slots[152] = frame->slots[152] /* temp__153 */;
  arguments->slots[153] = frame->slots[153] /* temp__154 */;
  arguments->slots[154] = frame->slots[154] /* temp__155 */;
  arguments->slots[155] = frame->slots[155] /* temp__156 */;
  arguments->slots[156] = frame->slots[156] /* temp__157 */;
  arguments->slots[157] = frame->slots[157] /* temp__158 */;
  arguments->slots[158] = frame->slots[158] /* temp__159 */;
  arguments->slots[159] = frame->slots[159] /* temp__160 */;
  arguments->slots[160] = frame->slots[160] /* temp__161 */;
  arguments->slots[161] = frame->slots[161] /* temp__162 */;
  arguments->slots[162] = frame->slots[162] /* temp__163 */;
  arguments->slots[163] = frame->slots[163] /* temp__164 */;
  arguments->slots[164] = frame->slots[164] /* temp__165 */;
  arguments->slots[165] = frame->slots[165] /* temp__166 */;
  arguments->slots[166] = frame->slots[166] /* temp__167 */;
  arguments->slots[167] = frame->slots[167] /* temp__168 */;
  arguments->slots[168] = frame->slots[168] /* temp__169 */;
  arguments->slots[169] = frame->slots[169] /* temp__170 */;
  arguments->slots[170] = frame->slots[170] /* temp__171 */;
  arguments->slots[171] = frame->slots[171] /* temp__172 */;
  arguments->slots[172] = frame->slots[172] /* temp__173 */;
  arguments->slots[173] = frame->slots[173] /* temp__174 */;
  arguments->slots[174] = frame->slots[174] /* temp__175 */;
  arguments->slots[175] = frame->slots[175] /* temp__176 */;
  arguments->slots[176] = frame->slots[176] /* temp__177 */;
  arguments->slots[177] = frame->slots[177] /* temp__178 */;
  arguments->slots[178] = frame->slots[178] /* temp__179 */;
  arguments->slots[179] = frame->slots[179] /* temp__180 */;
  arguments->slots[180] = frame->slots[180] /* temp__181 */;
  arguments->slots[181] = frame->slots[181] /* temp__182 */;
  arguments->slots[182] = frame->slots[182] /* temp__183 */;
  arguments->slots[183] = frame->slots[183] /* temp__184 */;
  arguments->slots[184] = frame->slots[184] /* temp__185 */;
  arguments->slots[185] = frame->slots[185] /* temp__186 */;
  arguments->slots[186] = frame->slots[186] /* temp__187 */;
  arguments->slots[187] = frame->slots[187] /* temp__188 */;
  arguments->slots[188] = frame->slots[188] /* temp__189 */;
  arguments->slots[189] = frame->slots[189] /* temp__190 */;
  arguments->slots[190] = frame->slots[190] /* temp__191 */;
  arguments->slots[191] = frame->slots[191] /* temp__192 */;
  arguments->slots[192] = frame->slots[192] /* temp__193 */;
  arguments->slots[193] = frame->slots[193] /* temp__194 */;
  arguments->slots[194] = frame->slots[194] /* temp__195 */;
  arguments->slots[195] = frame->slots[195] /* temp__196 */;
  arguments->slots[196] = frame->slots[196] /* temp__197 */;
  arguments->slots[197] = frame->slots[197] /* temp__198 */;
  arguments->slots[198] = frame->slots[198] /* temp__199 */;
  arguments->slots[199] = frame->slots[199] /* temp__200 */;
  arguments->slots[200] = frame->slots[200] /* temp__201 */;
  arguments->slots[201] = frame->slots[201] /* temp__202 */;
  arguments->slots[202] = frame->slots[202] /* temp__203 */;
  arguments->slots[203] = frame->slots[203] /* temp__204 */;
  arguments->slots[204] = frame->slots[204] /* temp__205 */;
  arguments->slots[205] = frame->slots[205] /* temp__206 */;
  arguments->slots[206] = frame->slots[206] /* temp__207 */;
  arguments->slots[207] = frame->slots[207] /* temp__208 */;
  arguments->slots[208] = frame->slots[208] /* temp__209 */;
  arguments->slots[209] = frame->slots[209] /* temp__210 */;
  arguments->slots[210] = frame->slots[210] /* temp__211 */;
  arguments->slots[211] = frame->slots[211] /* temp__212 */;
  arguments->slots[212] = frame->slots[212] /* temp__213 */;
  arguments->slots[213] = frame->slots[213] /* temp__214 */;
  arguments->slots[214] = frame->slots[214] /* temp__215 */;
  arguments->slots[215] = frame->slots[215] /* temp__216 */;
  arguments->slots[216] = frame->slots[216] /* temp__217 */;
  arguments->slots[217] = frame->slots[217] /* temp__218 */;
  arguments->slots[218] = frame->slots[218] /* temp__219 */;
  arguments->slots[219] = frame->slots[219] /* temp__220 */;
  arguments->slots[220] = frame->slots[220] /* temp__221 */;
  arguments->slots[221] = frame->slots[221] /* temp__222 */;
  arguments->slots[222] = frame->slots[222] /* temp__223 */;
  arguments->slots[223] = frame->slots[223] /* temp__224 */;
  arguments->slots[224] = frame->slots[224] /* temp__225 */;
  arguments->slots[225] = frame->slots[225] /* temp__226 */;
  arguments->slots[226] = frame->slots[226] /* temp__227 */;
  arguments->slots[227] = frame->slots[227] /* temp__228 */;
  arguments->slots[228] = frame->slots[228] /* temp__229 */;
  arguments->slots[229] = frame->slots[229] /* temp__230 */;
  arguments->slots[230] = frame->slots[230] /* temp__231 */;
  arguments->slots[231] = frame->slots[231] /* temp__232 */;
  arguments->slots[232] = frame->slots[232] /* temp__233 */;
  arguments->slots[233] = frame->slots[233] /* temp__234 */;
  arguments->slots[234] = frame->slots[234] /* temp__235 */;
  arguments->slots[235] = frame->slots[235] /* temp__236 */;
  arguments->slots[236] = frame->slots[236] /* temp__237 */;
  arguments->slots[237] = frame->slots[237] /* temp__238 */;
  arguments->slots[238] = frame->slots[238] /* temp__239 */;
  arguments->slots[239] = frame->slots[239] /* temp__240 */;
  arguments->slots[240] = frame->slots[240] /* temp__241 */;
  arguments->slots[241] = frame->slots[241] /* temp__242 */;
  arguments->slots[242] = frame->slots[242] /* temp__243 */;
  arguments->slots[243] = frame->slots[243] /* temp__244 */;
  arguments->slots[244] = frame->slots[244] /* temp__245 */;
  arguments->slots[245] = frame->slots[245] /* temp__246 */;
  arguments->slots[246] = frame->slots[246] /* temp__247 */;
  arguments->slots[247] = frame->slots[247] /* temp__248 */;
  arguments->slots[248] = frame->slots[248] /* temp__249 */;
  arguments->slots[249] = frame->slots[249] /* temp__250 */;
  arguments->slots[250] = frame->slots[250] /* temp__251 */;
  arguments->slots[251] = frame->slots[251] /* temp__252 */;
  arguments->slots[252] = frame->slots[252] /* temp__253 */;
  arguments->slots[253] = frame->slots[253] /* temp__254 */;
  arguments->slots[254] = frame->slots[254] /* temp__255 */;
  arguments->slots[255] = frame->slots[255] /* temp__256 */;
  arguments->slots[256] = frame->slots[256] /* temp__257 */;
  arguments->slots[257] = frame->slots[257] /* temp__258 */;
  arguments->slots[258] = frame->slots[258] /* temp__259 */;
  arguments->slots[259] = frame->slots[259] /* temp__260 */;
  arguments->slots[260] = frame->slots[260] /* temp__261 */;
  arguments->slots[261] = frame->slots[261] /* temp__262 */;
  arguments->slots[262] = frame->slots[262] /* temp__263 */;
  arguments->slots[263] = frame->slots[263] /* temp__264 */;
  arguments->slots[264] = frame->slots[264] /* temp__265 */;
  arguments->slots[265] = frame->slots[265] /* temp__266 */;
  arguments->slots[266] = frame->slots[266] /* temp__267 */;
  arguments->slots[267] = frame->slots[267] /* temp__268 */;
  arguments->slots[268] = frame->slots[268] /* temp__269 */;
  arguments->slots[269] = frame->slots[269] /* temp__270 */;
  arguments->slots[270] = frame->slots[270] /* temp__271 */;
  arguments->slots[271] = frame->slots[271] /* temp__272 */;
  arguments->slots[272] = frame->slots[272] /* temp__273 */;
  arguments->slots[273] = frame->slots[273] /* temp__274 */;
  arguments->slots[274] = frame->slots[274] /* temp__275 */;
  arguments->slots[275] = frame->slots[275] /* temp__276 */;
  arguments->slots[276] = frame->slots[276] /* temp__277 */;
  arguments->slots[277] = frame->slots[277] /* temp__278 */;
  arguments->slots[278] = frame->slots[278] /* temp__279 */;
  arguments->slots[279] = frame->slots[279] /* temp__280 */;
  arguments->slots[280] = frame->slots[280] /* temp__281 */;
  arguments->slots[281] = frame->slots[281] /* temp__282 */;
  arguments->slots[282] = frame->slots[282] /* temp__283 */;
  arguments->slots[283] = frame->slots[283] /* temp__284 */;
  arguments->slots[284] = frame->slots[284] /* temp__285 */;
  arguments->slots[285] = frame->slots[285] /* temp__286 */;
  arguments->slots[286] = frame->slots[286] /* temp__287 */;
  arguments->slots[287] = frame->slots[287] /* temp__288 */;
  arguments->slots[288] = frame->slots[288] /* temp__289 */;
  arguments->slots[289] = frame->slots[289] /* temp__290 */;
  arguments->slots[290] = frame->slots[290] /* temp__291 */;
  arguments->slots[291] = frame->slots[291] /* temp__292 */;
  arguments->slots[292] = frame->slots[292] /* temp__293 */;
  arguments->slots[293] = frame->slots[293] /* temp__294 */;
  arguments->slots[294] = frame->slots[294] /* temp__295 */;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__93_390;
}
static void cont__93_390(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._umlaut_conversions, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__to_integer_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // return: 1
  // value: 2
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[2] /* value */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 44: parse_integer &self $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = get__parse_integer();
  func = myself->type;
  frame->cont = cont__types__string__to_integer_2;
}
static void cont__types__string__to_integer_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 44: ... value
  initialize_future(frame->slots[2] /* value */, frame->slots[3] /* temp__1 */);
  // 45: ... self != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__to_integer_3;
}
static void cont__types__string__to_integer_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 45: ... self != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__to_integer_4;
}
static void cont__types__string__to_integer_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 45: ... : return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__string__to_integer_5, 0);
  // 45: if self != "": return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__to_integer_6;
}
static void entry__types__string__to_integer_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__to_integer_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 46: -> value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* value */;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__to_real_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // return: 1
  // value: 2
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[2] /* value */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 55: parse_real &self $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = get__parse_real();
  func = myself->type;
  frame->cont = cont__types__string__to_real_2;
}
static void cont__types__string__to_real_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 55: ... value
  initialize_future(frame->slots[2] /* value */, frame->slots[3] /* temp__1 */);
  // 56: ... self != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__to_real_3;
}
static void cont__types__string__to_real_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 56: ... self != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__to_real_4;
}
static void cont__types__string__to_real_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 56: ... : return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__string__to_real_5, 0);
  // 56: if self != "": return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__to_real_6;
}
static void entry__types__string__to_real_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__to_real_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 57: -> value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* value */;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_number_24(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 71: parse_real self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = frame->caller_result_count;
  myself = get__parse_real();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_number_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 73: parse_integer self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = frame->caller_result_count;
  myself = get__parse_integer();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__parse_number_1(void) {
  allocate_initialized_frame_gc(1, 9);
  // slot allocations:
  // self: 0
  // i: 1
  // n: 2
  frame->slots[1] /* i */ = create_cell();
  frame->slots[2] /* n */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 65: $$i 1
  ((CELL *)frame->slots[1])->contents /* i */ = number__1;
  // 66: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_2;
}
static void cont__types__string__parse_number_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* n */, arguments->slots[0]);
  // 67: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__types__string__parse_number_3;
}
static void cont__types__string__parse_number_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 67: ... self(1) == '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_4;
}
static void cont__types__string__parse_number_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 67: ... : inc &i
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__string__parse_number_5, 0);
  // 67: if self(1) == '-': inc &i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_7;
}
static void entry__types__string__parse_number_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // i: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 67: ... inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_6;
}
static void cont__types__string__parse_number_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_number_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 68: ... -> i <= n && self(i).is_a_digit: inc &i
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__string__parse_number_8, 0);
  // 68: while -> i <= n && self(i).is_a_digit: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_17;
}
static void entry__types__string__parse_number_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // i: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 68: ... inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_16;
}
static void cont__types__string__parse_number_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__parse_number_8(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 68: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_9;
}
static void cont__types__string__parse_number_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 68: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_10;
}
static void cont__types__string__parse_number_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 68: ... self(i).is_a_digit
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__string__parse_number_11, 0);
  // 68: ... i <= n && self(i).is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_14;
}
static void entry__types__string__parse_number_11(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 68: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__types__string__parse_number_12;
}
static void cont__types__string__parse_number_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 68: ... self(i).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_13;
}
static void cont__types__string__parse_number_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 68: ... self(i).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_number_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 68: ... : inc &i
  frame->slots[7] /* temp__5 */ = create_closure(entry__types__string__parse_number_15, 0);
  // 68: ... -> i <= n && self(i).is_a_digit: inc &i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_number_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 70: i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_18;
}
static void cont__types__string__parse_number_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 70: i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_19;
}
static void cont__types__string__parse_number_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 70: ... self(i) == '.'
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__string__parse_number_20, 0);
  // 70: i <= n && self(i) == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_23;
}
static void entry__types__string__parse_number_20(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__types__string__parse_number_21;
}
static void cont__types__string__parse_number_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 70: ... self(i) == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__parse_number_22;
}
static void cont__types__string__parse_number_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 70: ... self(i) == '.'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__parse_number_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 70: ... :
  // 71:   parse_real self
  frame->slots[7] /* temp__5 */ = create_closure(entry__types__string__parse_number_24, 0);
  // 72: :
  // 73:   parse_integer self
  frame->slots[8] /* temp__6 */ = create_closure(entry__types__string__parse_number_25, 0);
  // 69: if
  // 70:   i <= n && self(i) == '.':
  // 71:     parse_real self
  // 72:   :
  // 73:     parse_integer self
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  arguments->slots[2] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__to_number_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // return: 1
  // value: 2
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[2] /* value */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 82: parse_number &self $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = get__parse_number();
  func = myself->type;
  frame->cont = cont__types__string__to_number_2;
}
static void cont__types__string__to_number_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 82: ... value
  initialize_future(frame->slots[2] /* value */, frame->slots[3] /* temp__1 */);
  // 83: ... self != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__to_number_3;
}
static void cont__types__string__to_number_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 83: ... self != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__to_number_4;
}
static void cont__types__string__to_number_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 83: ... : return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__string__to_number_5, 0);
  // 83: if self != "": return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__to_number_6;
}
static void entry__types__string__to_number_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 83: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__to_number_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 84: -> value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* value */;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__put_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // chr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 93: ... chr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__types__string__put_2;
}
static void cont__types__string__put_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 93: ... append(chr.to_string self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__string__put_3;
}
static void cont__types__string__put_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 93: -> append(chr.to_string self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__write_to_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // args: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* args */ = from_arguments(1, argument_count-1);
  // 102: ... : (arg) append &self arg.to_string
  frame->slots[2] /* temp__1 */ = create_closure(entry__types__string__write_to_2, 1);
  // 102: for_each args: (arg) append &self arg.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__string__write_to_5;
}
static void entry__types__string__write_to_2(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // arg: 0
  // self: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 102: ... arg.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__types__string__write_to_3;
}
static void cont__types__string__write_to_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 102: ... append &self arg.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__string__write_to_4;
}
static void cont__types__string__write_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* self */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__write_to_5(void) {
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
static void entry__types__string__numerically_less_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // left: 0
  // right: 1
  // return: 2
  // left_len: 3
  // right_len: 4
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* left_len */ = create_future();
  frame->slots[4] /* right_len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 112: $left_len length_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_2;
}
static void cont__types__string__numerically_less_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* left_len */, arguments->slots[0]);
  // 113: $right_len length_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_3;
}
static void cont__types__string__numerically_less_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* right_len */, arguments->slots[0]);
  // 114: ... min(left_len right_len)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* left_len */;
  arguments->slots[1] = frame->slots[4] /* right_len */;
  result_count = 1;
  myself = get__min();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_4;
}
static void cont__types__string__numerically_less_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 114: ... : (i)
  // 115:   $left_chr left(i)
  // 116:   $right_chr right(i)
  // 117:   if left_chr != right_chr:
  // 118:     if
  // 119:       &&
  // 120:         left_chr >= '1'
  // 121:         left_chr <= '9'
  // 122:         right_chr >= '1'
  // 123:         right_chr <= '9'
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__string__numerically_less_5, 1);
  // 114: from_to 1 min(left_len right_len): (i)
  // 115:   $left_chr left(i)
  // 116:   $right_chr right(i)
  // 117:   if left_chr != right_chr:
  // 118:     if
  // 119:       &&
  // 120:         left_chr >= '1'
  // 121:         left_chr <= '9'
  // 122:         right_chr >= '1'
  // 123:         right_chr <= '9'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_58;
}
static void entry__types__string__numerically_less_10(void) {
  allocate_initialized_frame_gc(8, 14);
  // slot allocations:
  // left_chr: 0
  // right_chr: 1
  // i: 2
  // left_len: 3
  // left: 4
  // right_len: 5
  // right: 6
  // return: 7
  frame->slots[0] = myself->closure.frame->slots[6]; /* left_chr */
  frame->slots[1] = myself->closure.frame->slots[7]; /* right_chr */
  frame->slots[2] = myself->closure.frame->slots[0]; /* i */
  frame->slots[3] = myself->closure.frame->slots[3]; /* left_len */
  frame->slots[4] = myself->closure.frame->slots[1]; /* left */
  frame->slots[5] = myself->closure.frame->slots[4]; /* right_len */
  frame->slots[6] = myself->closure.frame->slots[2]; /* right */
  frame->slots[7] = myself->closure.frame->slots[5]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: left_chr >= '1'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left_chr */;
  arguments->slots[1] = character__49;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_11;
}
static void cont__types__string__numerically_less_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__3 */ = arguments->slots[0];
  // 120: left_chr >= '1'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_12;
}
static void cont__types__string__numerically_less_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  frame->slots[11] /* temp__4 */ = create_closure(entry__types__string__numerically_less_13, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_24;
}
static void entry__types__string__numerically_less_13(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // left_chr: 0
  // right_chr: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* left_chr */
  frame->slots[1] = myself->closure.frame->slots[1]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: left_chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[0] /* left_chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_14;
}
static void cont__types__string__numerically_less_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 121: left_chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_15;
}
static void cont__types__string__numerically_less_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__4 */ = create_closure(entry__types__string__numerically_less_16, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_23;
}
static void entry__types__string__numerically_less_16(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // right_chr: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 122: right_chr >= '1'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* right_chr */;
  arguments->slots[1] = character__49;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_17;
}
static void cont__types__string__numerically_less_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 122: right_chr >= '1'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_18;
}
static void cont__types__string__numerically_less_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 123: right_chr <= '9'
  frame->slots[4] /* temp__4 */ = create_closure(entry__types__string__numerically_less_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_22;
}
static void entry__types__string__numerically_less_19(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // right_chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 123: right_chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[0] /* right_chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_20;
}
static void cont__types__string__numerically_less_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 123: right_chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_21;
}
static void cont__types__string__numerically_less_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 123: right_chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__numerically_less_22(void) {
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
static void cont__types__string__numerically_less_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__numerically_less_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 124: :
  // 125:   $$j i+1
  // 126:   forever:
  // 127:     if
  // 128:       j <= left_len && left(j).is_a_digit:
  // 129:         if
  // 130:           j <= right_len && right(j).is_a_digit:
  // 131:             !j j+1
  // 132:           :
  // 133:             return false
  // ...
  frame->slots[12] /* temp__5 */ = create_closure(entry__types__string__numerically_less_25, 0);
  // 140: :
  // 141:   return left_chr < right_chr
  frame->slots[13] /* temp__6 */ = create_closure(entry__types__string__numerically_less_54, 0);
  // 118: if
  // 119:   &&
  // 120:     left_chr >= '1'
  // 121:     left_chr <= '9'
  // 122:     right_chr >= '1'
  // 123:     right_chr <= '9'
  // 124:   :
  // 125:     $$j i+1
  // 126:     forever:
  // 127:       if
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__5 */;
  arguments->slots[2] = frame->slots[13] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_56;
}
static void entry__types__string__numerically_less_51(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 137: return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__numerically_less_52(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // left_chr: 1
  // right_chr: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[4]; /* left_chr */
  frame->slots[2] = myself->closure.frame->slots[5]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 139: ... left_chr < right_chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* left_chr */;
  arguments->slots[1] = frame->slots[2] /* right_chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_53;
}
static void cont__types__string__numerically_less_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 139: return left_chr < right_chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__numerically_less_41(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // j: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* j */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 131: !j j+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* j */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_42;
}
static void cont__types__string__numerically_less_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* j */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__numerically_less_43(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 133: return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__numerically_less_34(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // right_len: 0
  // j: 1
  // right: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* right_len */
  frame->slots[1] = myself->closure.frame->slots[1]; /* j */
  frame->slots[2] = myself->closure.frame->slots[4]; /* right */
  frame->slots[3] = myself->closure.frame->slots[5]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: j <= right_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* right_len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_35;
}
static void cont__types__string__numerically_less_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 130: j <= right_len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_36;
}
static void cont__types__string__numerically_less_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 130: ... right(j).is_a_digit
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__string__numerically_less_37, 0);
  // 130: j <= right_len && right(j).is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_40;
}
static void entry__types__string__numerically_less_37(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // right: 0
  // j: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* j */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: ... right(j)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = frame->slots[0] /* right */;
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_38;
}
static void cont__types__string__numerically_less_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 130: ... right(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_39;
}
static void cont__types__string__numerically_less_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 130: ... right(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__numerically_less_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 130: ... :
  // 131:   !j j+1
  frame->slots[8] /* temp__5 */ = create_closure(entry__types__string__numerically_less_41, 0);
  // 132: :
  // 133:   return false
  frame->slots[9] /* temp__6 */ = create_closure(entry__types__string__numerically_less_43, 0);
  // 129: if
  // 130:   j <= right_len && right(j).is_a_digit:
  // 131:     !j j+1
  // 132:   :
  // 133:     return false
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__numerically_less_44(void) {
  allocate_initialized_frame_gc(6, 12);
  // slot allocations:
  // right_len: 0
  // j: 1
  // right: 2
  // return: 3
  // left_chr: 4
  // right_chr: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* right_len */
  frame->slots[1] = myself->closure.frame->slots[1]; /* j */
  frame->slots[2] = myself->closure.frame->slots[4]; /* right */
  frame->slots[3] = myself->closure.frame->slots[5]; /* return */
  frame->slots[4] = myself->closure.frame->slots[6]; /* left_chr */
  frame->slots[5] = myself->closure.frame->slots[7]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 136: j <= right_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* right_len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_45;
}
static void cont__types__string__numerically_less_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 136: j <= right_len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_46;
}
static void cont__types__string__numerically_less_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 136: ... right(j).is_a_digit
  frame->slots[9] /* temp__4 */ = create_closure(entry__types__string__numerically_less_47, 0);
  // 136: j <= right_len && right(j).is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_50;
}
static void entry__types__string__numerically_less_47(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // right: 0
  // j: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* j */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 136: ... right(j)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = frame->slots[0] /* right */;
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_48;
}
static void cont__types__string__numerically_less_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 136: ... right(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_49;
}
static void cont__types__string__numerically_less_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 136: ... right(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__numerically_less_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 136: ... :
  // 137:   return true
  frame->slots[10] /* temp__5 */ = create_closure(entry__types__string__numerically_less_51, 0);
  // 138: :
  // 139:   return left_chr < right_chr
  frame->slots[11] /* temp__6 */ = create_closure(entry__types__string__numerically_less_52, 0);
  // 135: if
  // 136:   j <= right_len && right(j).is_a_digit:
  // 137:     return true
  // 138:   :
  // 139:     return left_chr < right_chr
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__5 */;
  arguments->slots[2] = frame->slots[11] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__numerically_less_27(void) {
  allocate_initialized_frame_gc(8, 14);
  // slot allocations:
  // left_len: 0
  // j: 1
  // left: 2
  // right_len: 3
  // right: 4
  // return: 5
  // left_chr: 6
  // right_chr: 7
  frame->slots[0] = myself->closure.frame->slots[1]; /* left_len */
  frame->slots[1] = myself->closure.frame->slots[8]; /* j */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  frame->slots[3] = myself->closure.frame->slots[3]; /* right_len */
  frame->slots[4] = myself->closure.frame->slots[4]; /* right */
  frame->slots[5] = myself->closure.frame->slots[5]; /* return */
  frame->slots[6] = myself->closure.frame->slots[6]; /* left_chr */
  frame->slots[7] = myself->closure.frame->slots[7]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 128: j <= left_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left_len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_28;
}
static void cont__types__string__numerically_less_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__3 */ = arguments->slots[0];
  // 128: j <= left_len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_29;
}
static void cont__types__string__numerically_less_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 128: ... left(j).is_a_digit
  frame->slots[11] /* temp__4 */ = create_closure(entry__types__string__numerically_less_30, 0);
  // 128: j <= left_len && left(j).is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_33;
}
static void entry__types__string__numerically_less_30(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // left: 0
  // j: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* left */
  frame->slots[1] = myself->closure.frame->slots[1]; /* j */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 128: ... left(j)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = frame->slots[0] /* left */;
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_31;
}
static void cont__types__string__numerically_less_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 128: ... left(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_32;
}
static void cont__types__string__numerically_less_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 128: ... left(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__numerically_less_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 128: ... :
  // 129:   if
  // 130:     j <= right_len && right(j).is_a_digit:
  // 131:       !j j+1
  // 132:     :
  // 133:       return false
  frame->slots[12] /* temp__5 */ = create_closure(entry__types__string__numerically_less_34, 0);
  // 134: :
  // 135:   if
  // 136:     j <= right_len && right(j).is_a_digit:
  // 137:       return true
  // 138:     :
  // 139:       return left_chr < right_chr
  frame->slots[13] /* temp__6 */ = create_closure(entry__types__string__numerically_less_44, 0);
  // 127: if
  // 128:   j <= left_len && left(j).is_a_digit:
  // 129:     if
  // 130:       j <= right_len && right(j).is_a_digit:
  // 131:         !j j+1
  // 132:       :
  // 133:         return false
  // 134:   :
  // 135:     if
  // 136:       j <= right_len && right(j).is_a_digit:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__5 */;
  arguments->slots[2] = frame->slots[13] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__numerically_less_25(void) {
  allocate_initialized_frame_gc(8, 10);
  // slot allocations:
  // i: 0
  // left_len: 1
  // left: 2
  // right_len: 3
  // right: 4
  // return: 5
  // left_chr: 6
  // right_chr: 7
  // j: 8
  frame->slots[0] = myself->closure.frame->slots[2]; /* i */
  frame->slots[1] = myself->closure.frame->slots[3]; /* left_len */
  frame->slots[2] = myself->closure.frame->slots[4]; /* left */
  frame->slots[3] = myself->closure.frame->slots[5]; /* right_len */
  frame->slots[4] = myself->closure.frame->slots[6]; /* right */
  frame->slots[5] = myself->closure.frame->slots[7]; /* return */
  frame->slots[6] = myself->closure.frame->slots[0]; /* left_chr */
  frame->slots[7] = myself->closure.frame->slots[1]; /* right_chr */
  frame->slots[8] /* j */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 125: $$j i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_26;
}
static void cont__types__string__numerically_less_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* j */ = arguments->slots[0];
  // 126: ... :
  // 127:   if
  // 128:     j <= left_len && left(j).is_a_digit:
  // 129:       if
  // 130:         j <= right_len && right(j).is_a_digit:
  // 131:           !j j+1
  // 132:         :
  // 133:           return false
  // 134:     :
  // 135:       if
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__types__string__numerically_less_27, 0);
  // 126: forever:
  // 127:   if
  // 128:     j <= left_len && left(j).is_a_digit:
  // 129:       if
  // 130:         j <= right_len && right(j).is_a_digit:
  // 131:           !j j+1
  // 132:         :
  // 133:           return false
  // 134:     :
  // 135:       if
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__numerically_less_54(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // left_chr: 1
  // right_chr: 2
  frame->slots[0] = myself->closure.frame->slots[7]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* left_chr */
  frame->slots[2] = myself->closure.frame->slots[1]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 141: ... left_chr < right_chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* left_chr */;
  arguments->slots[1] = frame->slots[2] /* right_chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_55;
}
static void cont__types__string__numerically_less_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 141: return left_chr < right_chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__numerically_less_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 142: ... left_len < right_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* left_len */;
  arguments->slots[1] = frame->slots[5] /* right_len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_57;
}
static void cont__types__string__numerically_less_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 142: return left_len < right_len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[7] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__numerically_less_5(void) {
  allocate_initialized_frame_gc(6, 11);
  // slot allocations:
  // i: 0
  // left: 1
  // right: 2
  // left_len: 3
  // right_len: 4
  // return: 5
  // left_chr: 6
  // right_chr: 7
  frame->slots[1] = myself->closure.frame->slots[0]; /* left */
  frame->slots[2] = myself->closure.frame->slots[1]; /* right */
  frame->slots[3] = myself->closure.frame->slots[3]; /* left_len */
  frame->slots[4] = myself->closure.frame->slots[4]; /* right_len */
  frame->slots[5] = myself->closure.frame->slots[2]; /* return */
  frame->slots[6] /* left_chr */ = create_future();
  frame->slots[7] /* right_chr */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 115: $left_chr left(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[1] /* left */;
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_6;
}
static void cont__types__string__numerically_less_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* left_chr */, arguments->slots[0]);
  // 116: $right_chr right(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[2] /* right */;
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_7;
}
static void cont__types__string__numerically_less_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* right_chr */, arguments->slots[0]);
  // 117: ... left_chr != right_chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* left_chr */;
  arguments->slots[1] = frame->slots[7] /* right_chr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_8;
}
static void cont__types__string__numerically_less_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 117: ... left_chr != right_chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__string__numerically_less_9;
}
static void cont__types__string__numerically_less_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 117: ... :
  // 118:   if
  // 119:     &&
  // 120:       left_chr >= '1'
  // 121:       left_chr <= '9'
  // 122:       right_chr >= '1'
  // 123:       right_chr <= '9'
  // 124:     :
  // 125:       $$j i+1
  // 126:       forever:
  // ...
  frame->slots[10] /* temp__3 */ = create_closure(entry__types__string__numerically_less_10, 0);
  // 117: if left_chr != right_chr:
  // 118:   if
  // 119:     &&
  // 120:       left_chr >= '1'
  // 121:       left_chr <= '9'
  // 122:       right_chr >= '1'
  // 123:       right_chr <= '9'
  // 124:     :
  // 125:       $$j i+1
  // 126:       forever:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__numerically_less_58(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__to_list_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // items: 1
  frame->slots[1] /* items */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 150: $$items empty_list
  ((CELL *)frame->slots[1])->contents /* items */ = get__empty_list();
  // 151: ... : (item) push &items item
  frame->slots[2] /* temp__1 */ = create_closure(entry__types__string__to_list_2, 1);
  // 151: for_each self: (item) push &items item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__string__to_list_4;
}
static void entry__types__string__to_list_2(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // items: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* items */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 151: ... push &items item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* items */;
  arguments->slots[1] = frame->slots[0] /* item */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__string__to_list_3;
}
static void cont__types__string__to_list_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* items */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__to_list_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 152: -> items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* items */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__string_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // args: 0
  // buf: 1
  // n: 2
  frame->slots[1] /* buf */ = create_cell();
  frame->slots[2] /* n */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 160: $$buf ""
  ((CELL *)frame->slots[1])->contents /* buf */ = empty_string;
  // 161: $n length_of(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__string_2;
}
static void cont__std__string_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* n */, arguments->slots[0]);
  // 162: ... : (i) append &buf to_string(args(i))
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__string_3, 1);
  // 162: from_to 1 n: (i) append &buf to_string(args(i))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[2] /* n */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__std__string_7;
}
static void entry__std__string_3(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // i: 0
  // buf: 1
  // args: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 162: ... args(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[2] /* args */;
  func = myself->type;
  frame->cont = cont__std__string_4;
}
static void cont__std__string_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 162: ... to_string(args(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__std__string_5;
}
static void cont__std__string_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 162: ... append &buf to_string(args(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__string_6;
}
static void cont__std__string_6(void) {
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
static void cont__std__string_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 163: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__dup_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // n: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 175: ... :
  // 176:   return ""
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__string__dup_2, 0);
  // 177: ... :
  // 178:   return self
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__string__dup_3, 0);
  // 179: :
  // 180:   if n < 0: Error "Negative argument for dup!"
  // 181:   $h n .div. 2
  // 182:   $str dup(self h)
  // 183:   if
  // 184:     2*h == n:
  // 185:       return string(str str)
  // 186:     :
  // 187:       return string(str str self)
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__string__dup_4, 0);
  // 173: case
  // 174:   n
  // 175:   0:
  // 176:     return ""
  // 177:   1:
  // 178:     return self
  // 179:   :
  // 180:     if n < 0: Error "Negative argument for dup!"
  // 181:     $h n .div. 2
  // 182:     $str dup(self h)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = number__1;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__types__string__dup_17;
}
static void entry__types__string__dup_13(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // str: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[4]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... string(str str)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[1] /* str */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__types__string__dup_14;
}
static void cont__types__string__dup_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 185: return string(str str)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__dup_15(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // str: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[4]; /* str */
  frame->slots[2] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: ... string(str str self)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[1] /* str */;
  arguments->slots[2] = frame->slots[2] /* self */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__types__string__dup_16;
}
static void cont__types__string__dup_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 187: return string(str str self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__dup_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__dup_3(void) {
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
  // 178: return self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__dup_4(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // n: 0
  // self: 1
  // return: 2
  // h: 3
  // str: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* n */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* h */ = create_future();
  frame->slots[4] /* str */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... n < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__dup_5;
}
static void cont__types__string__dup_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 180: if n < 0: Error "Negative argument for dup!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__types__string__dup_6;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__dup_8;
}
static void entry__types__string__dup_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... Error "Negative argument for dup!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__963fa2c6021831d1;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__dup_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 181: $h n .div. 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__types__string__dup_9;
}
static void cont__types__string__dup_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* h */, arguments->slots[0]);
  // 182: $str dup(self h)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[3] /* h */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__types__string__dup_10;
}
static void cont__types__string__dup_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* str */, arguments->slots[0]);
  // 184: 2*h
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[3] /* h */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__types__string__dup_11;
}
static void cont__types__string__dup_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 184: 2*h == n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__dup_12;
}
static void cont__types__string__dup_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 184: ... :
  // 185:   return string(str str)
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__string__dup_13, 0);
  // 186: :
  // 187:   return string(str str self)
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__string__dup_15, 0);
  // 183: if
  // 184:   2*h == n:
  // 185:     return string(str str)
  // 186:   :
  // 187:     return string(str str self)
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
static void cont__types__string__dup_17(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__pad_left_1(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // expr: 0
  // n: 1
  // pad: 2
  // return: 3
  // text: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* text */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* pad */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* pad */ = string__578a5af303e9cc1;
  }
  // 204: $text expr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__std__pad_left_3;
}
static void cont__std__pad_left_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* text */, arguments->slots[0]);
  // 205: $len length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__pad_left_4;
}
static void cont__std__pad_left_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* len */, arguments->slots[0]);
  // 206: ... len < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__pad_left_5;
}
static void cont__std__pad_left_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 206: ... :
  // 207:   $pad_len length_of(pad)
  // 208:   return string(range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len) text)
  frame->slots[7] /* temp__2 */ = create_closure(entry__std__pad_left_6, 0);
  // 206: if len < n:
  // 207:   $pad_len length_of(pad)
  // 208:   return string(range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len) text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__pad_left_16;
}
static void entry__std__pad_left_6(void) {
  allocate_initialized_frame_gc(5, 14);
  // slot allocations:
  // pad: 0
  // return: 1
  // n: 2
  // len: 3
  // text: 4
  // pad_len: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* pad */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] = myself->closure.frame->slots[1]; /* n */
  frame->slots[3] = myself->closure.frame->slots[5]; /* len */
  frame->slots[4] = myself->closure.frame->slots[4]; /* text */
  frame->slots[5] /* pad_len */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: $pad_len length_of(pad)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pad */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__pad_left_7;
}
static void cont__std__pad_left_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* pad_len */, arguments->slots[0]);
  // 208: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__pad_left_8;
}
static void cont__std__pad_left_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 208: ... n-len+pad_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[5] /* pad_len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__pad_left_9;
}
static void cont__std__pad_left_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__6 */ = arguments->slots[0];
  // 208: ... n-len+pad_len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__pad_left_10;
}
static void cont__std__pad_left_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 208: ... n-len+pad_len-1 .div. pad_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* pad_len */;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__std__pad_left_11;
}
static void cont__std__pad_left_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  // 208: ... dup(pad n-len+pad_len-1 .div. pad_len)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pad */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__pad_left_12;
}
static void cont__std__pad_left_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 208: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__pad_left_13;
}
static void cont__std__pad_left_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__8 */ = arguments->slots[0];
  // 208: ... range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[13] /* temp__8 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__pad_left_14;
}
static void cont__std__pad_left_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 208: ... string(range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len) text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* text */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__pad_left_15;
}
static void cont__std__pad_left_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 208: return string(range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len) text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__pad_left_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 209: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__pad_right_1(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // expr: 0
  // n: 1
  // pad: 2
  // return: 3
  // text: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* text */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* pad */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* pad */ = string__578a5af303e9cc1;
  }
  // 226: $text expr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__std__pad_right_2;
}
static void cont__std__pad_right_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* text */, arguments->slots[0]);
  // 227: $len length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__pad_right_3;
}
static void cont__std__pad_right_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* len */, arguments->slots[0]);
  // 228: ... len < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__pad_right_4;
}
static void cont__std__pad_right_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 228: ... :
  // 229:   $pad_len length_of(pad)
  // 230:   return string(text range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len))
  frame->slots[7] /* temp__2 */ = create_closure(entry__std__pad_right_5, 0);
  // 228: if len < n:
  // 229:   $pad_len length_of(pad)
  // 230:   return string(text range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__pad_right_15;
}
static void entry__std__pad_right_5(void) {
  allocate_initialized_frame_gc(5, 14);
  // slot allocations:
  // pad: 0
  // return: 1
  // text: 2
  // n: 3
  // len: 4
  // pad_len: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* pad */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] = myself->closure.frame->slots[4]; /* text */
  frame->slots[3] = myself->closure.frame->slots[1]; /* n */
  frame->slots[4] = myself->closure.frame->slots[5]; /* len */
  frame->slots[5] /* pad_len */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 229: $pad_len length_of(pad)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pad */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__pad_right_6;
}
static void cont__std__pad_right_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* pad_len */, arguments->slots[0]);
  // 230: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__pad_right_7;
}
static void cont__std__pad_right_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 230: ... n-len+pad_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[5] /* pad_len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__pad_right_8;
}
static void cont__std__pad_right_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__6 */ = arguments->slots[0];
  // 230: ... n-len+pad_len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__pad_right_9;
}
static void cont__std__pad_right_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 230: ... n-len+pad_len-1 .div. pad_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* pad_len */;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__std__pad_right_10;
}
static void cont__std__pad_right_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  // 230: ... dup(pad n-len+pad_len-1 .div. pad_len)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pad */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__pad_right_11;
}
static void cont__std__pad_right_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 230: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__pad_right_12;
}
static void cont__std__pad_right_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__8 */ = arguments->slots[0];
  // 230: ... range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[13] /* temp__8 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__pad_right_13;
}
static void cont__std__pad_right_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 230: ... string(text range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__pad_right_14;
}
static void cont__std__pad_right_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 230: return string(text range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__pad_right_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 231: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__truncate_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 247: ... -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__truncate_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // text: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 247: ... range(text 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__truncate_7;
}
static void cont__std__truncate_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 247: ... -> range(text 1 n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__truncate_1(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // expr: 0
  // n: 1
  // text: 2
  // len: 3
  frame->slots[2] /* text */ = create_future();
  frame->slots[3] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 245: $text expr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__std__truncate_2;
}
static void cont__std__truncate_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* text */, arguments->slots[0]);
  // 246: $len length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__truncate_3;
}
static void cont__std__truncate_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 247: ... len < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__truncate_4;
}
static void cont__std__truncate_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 247: ... -> text
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__truncate_5, 0);
  // 247: ... -> range(text 1 n)
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__truncate_6, 0);
  // 247: if len < n (-> text) -> range(text 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__pad_or_truncate_5(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // text: 0
  // n: 1
  // len: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  frame->slots[2] = myself->closure.frame->slots[3]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 264: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__pad_or_truncate_6;
}
static void cont__std__pad_or_truncate_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 264: ... dup(" " n-len)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__pad_or_truncate_7;
}
static void cont__std__pad_or_truncate_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 264: ... string(text dup(" " n-len))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__pad_or_truncate_8;
}
static void cont__std__pad_or_truncate_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 264: ... -> string(text dup(" " n-len))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pad_or_truncate_9(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // text: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 264: ... range(text 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__pad_or_truncate_10;
}
static void cont__std__pad_or_truncate_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 264: ... -> range(text 1 n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pad_or_truncate_1(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // expr: 0
  // n: 1
  // text: 2
  // len: 3
  frame->slots[2] /* text */ = create_future();
  frame->slots[3] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 262: $text expr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__std__pad_or_truncate_2;
}
static void cont__std__pad_or_truncate_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* text */, arguments->slots[0]);
  // 263: $len length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__pad_or_truncate_3;
}
static void cont__std__pad_or_truncate_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 264: ... len < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__pad_or_truncate_4;
}
static void cont__std__pad_or_truncate_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 264: ... -> string(text dup(" " n-len))
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__pad_or_truncate_5, 0);
  // 264: ... -> range(text 1 n)
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__pad_or_truncate_9, 0);
  // 264: if len < n (-> string(text dup(" " n-len))) -> range(text 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__match_character_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 273: ... -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__match_character_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 273: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__match_character_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // chr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 273: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__string__match_character_2;
}
static void cont__types__string__match_character_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 273: ... length_of(self) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__string__match_character_3;
}
static void cont__types__string__match_character_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 273: ... self(1) == chr
  frame->slots[5] /* temp__4 */ = create_closure(entry__types__string__match_character_4, 0);
  // 273: ... length_of(self) > 0 && self(1) == chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__string__match_character_7;
}
static void entry__types__string__match_character_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 273: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__types__string__match_character_5;
}
static void cont__types__string__match_character_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 273: ... self(1) == chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__match_character_6;
}
static void cont__types__string__match_character_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 273: ... self(1) == chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__string__match_character_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 273: if length_of(self) > 0 && self(1) == chr (-> 1) -> undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__types__string__match_character_8;
  arguments->slots[2] = func__types__string__match_character_9;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__grammar__match_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // expr: 0
  // stream: 1
  // return: 2
  // len: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 283: $len length_of(expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__string__grammar__match_2;
}
static void cont__types__string__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 284: ... stream .has_minimum_length. len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__types__string__grammar__match_3;
}
static void cont__types__string__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 284: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__grammar__match_4, 0);
  // 284: unless stream .has_minimum_length. len: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__string__grammar__match_5;
}
static void entry__types__string__grammar__match_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__grammar__match_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 285: ... range(stream 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__grammar__match_6;
}
static void cont__types__string__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 285: ... range(stream 1 len) == expr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__grammar__match_7;
}
static void cont__types__string__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 285: ... : return len
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__string__grammar__match_8, 0);
  // 285: if range(stream 1 len) == expr: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__grammar__match_9;
}
static void entry__types__string__grammar__match_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // len: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__grammar__match_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 286: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__match_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // stream: 0
  // expr: 1
  // return: 2
  // n: 3
  frame->slots[2] /* return */ = create_continuation();
  define__grammar__current_node(undefined);
  frame->slots[3] /* n */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 296: %%grammar::current_node types::grammar_node
  set__grammar__current_node(get__types__grammar_node());
  // 297: $n grammar::match(expr stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* stream */;
  result_count = 1;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__types__string__match_2;
}
static void cont__types__string__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 298: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__string__match_3;
}
static void cont__types__string__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 298: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__match_4;
}
static void cont__types__string__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 298: ... : return n grammar::current_node
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__string__match_5, 0);
  // 298: if parameter_count_of(return) == 2: return n grammar::current_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__match_6;
}
static void entry__types__string__match_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 298: ... return n grammar::current_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = get__grammar__current_node();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__match_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 299: -> n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__search_character_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // sum: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* sum */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 313: ... sum+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sum */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__search_character_7;
}
static void cont__types__string__search_character_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 313: -> sum+1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__search_character_8(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // self: 0
  // chr: 1
  // sum: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  frame->slots[2] = myself->closure.frame->slots[2]; /* sum */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 314: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__search_character_9;
}
static void cont__types__string__search_character_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 314: ... range(self 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__search_character_10;
}
static void cont__types__string__search_character_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 314: ... sum+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* sum */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__search_character_11;
}
static void cont__types__string__search_character_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 314: ... search_character(range(self 2 -1) chr sum+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__search_character();
  func = myself->type;
  frame->cont = cont__types__string__search_character_12;
}
static void cont__types__string__search_character_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 314: -> search_character(range(self 2 -1) chr sum+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__search_character_3(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // self: 0
  // chr: 1
  // sum: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* chr */
  frame->slots[2] = myself->closure.frame->slots[2]; /* sum */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 312: self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__types__string__search_character_4;
}
static void cont__types__string__search_character_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 312: self(1) == chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__search_character_5;
}
static void cont__types__string__search_character_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 313: -> sum+1
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__string__search_character_6, 0);
  // 314: -> search_character(range(self 2 -1) chr sum+1)
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__string__search_character_8, 0);
  // 311: if
  // 312:   self(1) == chr
  // 313:   -> sum+1
  // 314:   -> search_character(range(self 2 -1) chr sum+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__search_character_13(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 315: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__search_character_1(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // chr: 1
  // sum: 2
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* sum */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* sum */ = number__0;
  }
  // 310: self .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__types__string__search_character_2;
}
static void cont__types__string__search_character_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 310: ... :
  // 311:   if
  // 312:     self(1) == chr
  // 313:     -> sum+1
  // 314:     -> search_character(range(self 2 -1) chr sum+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__string__search_character_3, 0);
  // 309: if
  // 310:   self .has_minimum_length. 1:
  // 311:     if
  // 312:       self(1) == chr
  // 313:       -> sum+1
  // 314:       -> search_character(range(self 2 -1) chr sum+1)
  // 315:   -> undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = func__types__string__search_character_13;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__search_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // stream: 0
  // expr: 1
  // return__1: 2
  // pos: 3
  // len: 4
  frame->slots[2] /* return__1 */ = create_continuation();
  define__grammar__current_node(undefined);
  frame->slots[3] /* pos */ = create_future();
  frame->slots[4] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 330: %%grammar::current_node types::grammar_node
  set__grammar__current_node(get__types__grammar_node());
  // 331: grammar::search $pos $len expr stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* stream */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__search_2;
}
static void cont__types__string__search_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 331: ... pos
  initialize_future(frame->slots[3] /* pos */, frame->slots[5] /* temp__1 */);
  // 331: ... len
  initialize_future(frame->slots[4] /* len */, frame->slots[6] /* temp__2 */);
  // 332: -> pos len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  arguments->slots[1] = frame->slots[4] /* len */;
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__before_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // str: 0
  // expr: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = number__1;
  }
  // 367: grammar::search $pos $_len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__before_2;
}
static void cont__types__string__before_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 367: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 367: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 369: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__before_3;
}
static void cont__types__string__before_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 369: ... :
  // 370:   return range(str 1 pos-1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__before_4, 0);
  // 371: :
  // 372:   return ""
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__before_7, 0);
  // 368: if
  // 369:   pos.is_defined:
  // 370:     return range(str 1 pos-1)
  // 371:   :
  // 372:     return ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__before_8;
}
static void entry__types__string__before_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // str: 1
  // pos: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 370: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__before_5;
}
static void cont__types__string__before_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 370: ... range(str 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__before_6;
}
static void cont__types__string__before_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 370: return range(str 1 pos-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__before_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 372: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__before_8(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__truncate_from_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // str: 0
  // expr: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = number__1;
  }
  // 398: grammar::search $pos $_len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__truncate_from_2;
}
static void cont__types__string__truncate_from_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 398: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 398: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 400: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__truncate_from_3;
}
static void cont__types__string__truncate_from_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 400: ... :
  // 401:   return range(str 1 pos-1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__truncate_from_4, 0);
  // 402: :
  // 403:   return str
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__truncate_from_7, 0);
  // 399: if
  // 400:   pos.is_defined:
  // 401:     return range(str 1 pos-1)
  // 402:   :
  // 403:     return str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__truncate_from_8;
}
static void entry__types__string__truncate_from_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // str: 1
  // pos: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 401: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__truncate_from_5;
}
static void cont__types__string__truncate_from_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 401: ... range(str 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__truncate_from_6;
}
static void cont__types__string__truncate_from_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 401: return range(str 1 pos-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__truncate_from_7(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // str: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 403: return str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__truncate_from_8(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__behind_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // str: 0
  // expr: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = number__1;
  }
  // 436: grammar::search $pos $len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__behind_2;
}
static void cont__types__string__behind_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 436: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 436: ... len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 438: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__behind_3;
}
static void cont__types__string__behind_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 438: ... :
  // 439:   return range(str pos+len -1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__behind_4, 0);
  // 440: :
  // 441:   return ""
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__behind_8, 0);
  // 437: if
  // 438:   pos.is_defined:
  // 439:     return range(str pos+len -1)
  // 440:   :
  // 441:     return ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__behind_9;
}
static void entry__types__string__behind_4(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // return: 0
  // str: 1
  // pos: 2
  // len: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  frame->slots[3] = myself->closure.frame->slots[5]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 439: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__behind_5;
}
static void cont__types__string__behind_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 439: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__behind_6;
}
static void cont__types__string__behind_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 439: ... range(str pos+len -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__behind_7;
}
static void cont__types__string__behind_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 439: return range(str pos+len -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__behind_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__behind_9(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__truncate_until_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // str: 0
  // expr: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = number__1;
  }
  // 467: grammar::search $pos $len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__truncate_until_2;
}
static void cont__types__string__truncate_until_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 467: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 467: ... len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 469: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__truncate_until_3;
}
static void cont__types__string__truncate_until_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 469: ... :
  // 470:   return range(str pos+len -1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__truncate_until_4, 0);
  // 471: :
  // 472:   return str
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__truncate_until_8, 0);
  // 468: if
  // 469:   pos.is_defined:
  // 470:     return range(str pos+len -1)
  // 471:   :
  // 472:     return str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__truncate_until_9;
}
static void entry__types__string__truncate_until_4(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // return: 0
  // str: 1
  // pos: 2
  // len: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  frame->slots[3] = myself->closure.frame->slots[5]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 470: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__truncate_until_5;
}
static void cont__types__string__truncate_until_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 470: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__truncate_until_6;
}
static void cont__types__string__truncate_until_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 470: ... range(str pos+len -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__truncate_until_7;
}
static void cont__types__string__truncate_until_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 470: return range(str pos+len -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__truncate_until_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // str: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 472: return str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__truncate_until_9(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__from_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // str: 0
  // expr: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = number__1;
  }
  // 501: grammar::search $pos $_len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__from_2;
}
static void cont__types__string__from_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 501: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 501: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 503: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__from_3;
}
static void cont__types__string__from_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 503: ... :
  // 504:   return range(str pos -1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__from_4, 0);
  // 505: :
  // 506:   return ""
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__from_7, 0);
  // 502: if
  // 503:   pos.is_defined:
  // 504:     return range(str pos -1)
  // 505:   :
  // 506:     return ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__from_8;
}
static void entry__types__string__from_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // str: 1
  // pos: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 504: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__from_5;
}
static void cont__types__string__from_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 504: ... range(str pos -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[2] /* pos */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__from_6;
}
static void cont__types__string__from_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 504: return range(str pos -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__from_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 506: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__from_8(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__truncate_before_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // str: 0
  // expr: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = number__1;
  }
  // 523: grammar::search $pos $_len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__truncate_before_2;
}
static void cont__types__string__truncate_before_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 523: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 523: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 525: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__truncate_before_3;
}
static void cont__types__string__truncate_before_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 525: ... :
  // 526:   return range(str pos -1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__truncate_before_4, 0);
  // 527: :
  // 528:   return str
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__truncate_before_7, 0);
  // 524: if
  // 525:   pos.is_defined:
  // 526:     return range(str pos -1)
  // 527:   :
  // 528:     return str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__truncate_before_8;
}
static void entry__types__string__truncate_before_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // str: 1
  // pos: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 526: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__truncate_before_5;
}
static void cont__types__string__truncate_before_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 526: ... range(str pos -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[2] /* pos */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__truncate_before_6;
}
static void cont__types__string__truncate_before_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 526: return range(str pos -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__truncate_before_7(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // str: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 528: return str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__truncate_before_8(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__until_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // str: 0
  // expr: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = number__1;
  }
  // 554: grammar::search $pos $len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__until_2;
}
static void cont__types__string__until_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 554: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 554: ... len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 556: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__until_3;
}
static void cont__types__string__until_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 556: ... :
  // 557:   return range(str 1 pos+len-1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__until_4, 0);
  // 558: :
  // 559:   return ""
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__until_8, 0);
  // 555: if
  // 556:   pos.is_defined:
  // 557:     return range(str 1 pos+len-1)
  // 558:   :
  // 559:     return ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__until_9;
}
static void entry__types__string__until_4(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // return: 0
  // str: 1
  // pos: 2
  // len: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  frame->slots[3] = myself->closure.frame->slots[5]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 557: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__until_5;
}
static void cont__types__string__until_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 557: ... pos+len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__until_6;
}
static void cont__types__string__until_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 557: ... range(str 1 pos+len-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__until_7;
}
static void cont__types__string__until_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 557: return range(str 1 pos+len-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__until_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 559: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__until_9(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__truncate_behind_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // str: 0
  // expr: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = number__1;
  }
  // 576: grammar::search $pos $len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__truncate_behind_2;
}
static void cont__types__string__truncate_behind_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 576: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 576: ... len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 578: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__truncate_behind_3;
}
static void cont__types__string__truncate_behind_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 578: ... :
  // 579:   return range(str 1 pos+len-1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__string__truncate_behind_4, 0);
  // 580: :
  // 581:   return str
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__string__truncate_behind_8, 0);
  // 577: if
  // 578:   pos.is_defined:
  // 579:     return range(str 1 pos+len-1)
  // 580:   :
  // 581:     return str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__truncate_behind_9;
}
static void entry__types__string__truncate_behind_4(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // return: 0
  // str: 1
  // pos: 2
  // len: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  frame->slots[3] = myself->closure.frame->slots[5]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 579: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__truncate_behind_5;
}
static void cont__types__string__truncate_behind_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 579: ... pos+len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__truncate_behind_6;
}
static void cont__types__string__truncate_behind_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 579: ... range(str 1 pos+len-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__truncate_behind_7;
}
static void cont__types__string__truncate_behind_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 579: return range(str 1 pos+len-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__truncate_behind_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // str: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 581: return str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__truncate_behind_9(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__between_1(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // str: 0
  // expr_1: 1
  // expr_2: 2
  // nth: 3
  if (argument_count < 3) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* nth */ = arguments->slots[3];
    case 3:;
  }
  switch(argument_count) {
    case 3: frame->slots[3] /* nth */ = number__1;
  }
  // 600: ... behind(str expr_1 nth)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* str */;
  arguments->slots[1] = frame->slots[1] /* expr_1 */;
  arguments->slots[2] = frame->slots[3] /* nth */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__types__string__between_2;
}
static void cont__types__string__between_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 600: ... behind(str expr_1 nth) .before. expr_2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* expr_2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__types__string__between_3;
}
static void cont__types__string__between_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 600: -> behind(str expr_1 nth) .before. expr_2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__has_prefix_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // prefix: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 611: ... match(self prefix)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* prefix */;
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__types__string__has_prefix_2;
}
static void cont__types__string__has_prefix_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 611: ... match(self prefix).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__has_prefix_3;
}
static void cont__types__string__has_prefix_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 611: -> match(self prefix).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__has_suffix_1(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // suffix: 1
  // return: 2
  // len: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 623: $len length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__string__has_suffix_2;
}
static void cont__types__string__has_suffix_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 624: ... : (i)
  // 625:   if match(range(self i -1) suffix) == len-i+1: return true
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__string__has_suffix_3, 1);
  // 624: from_down_to len 1: (i)
  // 625:   if match(range(self i -1) suffix) == len-i+1: return true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__from_down_to();
  func = myself->type;
  frame->cont = cont__types__string__has_suffix_11;
}
static void entry__types__string__has_suffix_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 625: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__has_suffix_3(void) {
  allocate_initialized_frame_gc(5, 12);
  // slot allocations:
  // i: 0
  // self: 1
  // suffix: 2
  // len: 3
  // return: 4
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* suffix */
  frame->slots[3] = myself->closure.frame->slots[3]; /* len */
  frame->slots[4] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 625: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__has_suffix_4;
}
static void cont__types__string__has_suffix_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 625: ... range(self i -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[0] /* i */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__has_suffix_5;
}
static void cont__types__string__has_suffix_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 625: ... match(range(self i -1) suffix)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__types__string__has_suffix_6;
}
static void cont__types__string__has_suffix_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 625: ... len-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[0] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__has_suffix_7;
}
static void cont__types__string__has_suffix_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 625: ... len-i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__has_suffix_8;
}
static void cont__types__string__has_suffix_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 625: ... match(range(self i -1) suffix) == len-i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__has_suffix_9;
}
static void cont__types__string__has_suffix_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 625: ... : return true
  frame->slots[11] /* temp__7 */ = create_closure(entry__types__string__has_suffix_10, 0);
  // 625: if match(range(self i -1) suffix) == len-i+1: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__has_suffix_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 626: -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__without_prefix_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // prefix: 1
  // return: 2
  // n: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* n */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 638: $n match(self prefix)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* prefix */;
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__types__string__without_prefix_2;
}
static void cont__types__string__without_prefix_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 639: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__without_prefix_3;
}
static void cont__types__string__without_prefix_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 639: ... : return range(self n+1 -1)
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__string__without_prefix_4, 0);
  // 639: if n.is_defined: return range(self n+1 -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__string__without_prefix_8;
}
static void entry__types__string__without_prefix_4(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // return: 0
  // self: 1
  // n: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[3]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 639: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__without_prefix_5;
}
static void cont__types__string__without_prefix_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 639: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__without_prefix_6;
}
static void cont__types__string__without_prefix_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 639: ... range(self n+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__without_prefix_7;
}
static void cont__types__string__without_prefix_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 639: ... return range(self n+1 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__without_prefix_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 640: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__string__without_suffix_1(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // suffix: 1
  // return: 2
  // len: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 652: $len length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_2;
}
static void cont__types__string__without_suffix_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 653: ... : (i)
  // 654:   if match(range(self i -1) suffix) == len-i+1: return range(self 1 i-1)
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__string__without_suffix_3, 1);
  // 653: from_to 1 len: (i)
  // 654:   if match(range(self i -1) suffix) == len-i+1: return range(self 1 i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* len */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_13;
}
static void entry__types__string__without_suffix_10(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // self: 1
  // i: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  frame->slots[2] = myself->closure.frame->slots[0]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 654: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_11;
}
static void cont__types__string__without_suffix_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 654: ... range(self 1 i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_12;
}
static void cont__types__string__without_suffix_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 654: ... return range(self 1 i-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__without_suffix_3(void) {
  allocate_initialized_frame_gc(5, 12);
  // slot allocations:
  // i: 0
  // self: 1
  // suffix: 2
  // len: 3
  // return: 4
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* suffix */
  frame->slots[3] = myself->closure.frame->slots[3]; /* len */
  frame->slots[4] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 654: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_4;
}
static void cont__types__string__without_suffix_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 654: ... range(self i -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[0] /* i */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_5;
}
static void cont__types__string__without_suffix_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 654: ... match(range(self i -1) suffix)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_6;
}
static void cont__types__string__without_suffix_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 654: ... len-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[0] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_7;
}
static void cont__types__string__without_suffix_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 654: ... len-i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_8;
}
static void cont__types__string__without_suffix_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 654: ... match(range(self i -1) suffix) == len-i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__without_suffix_9;
}
static void cont__types__string__without_suffix_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 654: ... : return range(self 1 i-1)
  frame->slots[11] /* temp__7 */ = create_closure(entry__types__string__without_suffix_10, 0);
  // 654: if match(range(self i -1) suffix) == len-i+1: return range(self 1 i-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__string__without_suffix_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 655: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__trim_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // str: 0
  // s: 1
  // e: 2
  frame->slots[1] /* s */ = create_cell();
  frame->slots[2] /* e */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* str */ = create_cell_with_contents(arguments->slots[0]);
  // 663: $$s 1
  ((CELL *)frame->slots[1])->contents /* s */ = number__1;
  // 664: $$e length_of(str)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__trim_2;
}
static void cont__std__trim_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* e */ = arguments->slots[0];
  // 665: ... -> s <= e && str(s) <= ' ': plus &s 1
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__trim_3, 0);
  // 665: while -> s <= e && str(s) <= ' ': plus &s 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__trim_13;
}
static void entry__std__trim_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // s: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 665: ... plus &s 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__std__trim_12;
}
static void cont__std__trim_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* s */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__trim_3(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // e: 0
  // s: 1
  // str: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* e */
  frame->slots[1] = myself->closure.frame->slots[1]; /* s */
  frame->slots[2] = myself->closure.frame->slots[0]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 665: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* e */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__trim_4;
}
static void cont__std__trim_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 665: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__trim_5;
}
static void cont__std__trim_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 665: ... str(s) <= ' '
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__trim_6, 0);
  // 665: ... s <= e && str(s) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__trim_10;
}
static void entry__std__trim_6(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // str: 0
  // s: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* str */
  frame->slots[1] = myself->closure.frame->slots[1]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 665: ... str(s)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* str */;
  func = myself->type;
  frame->cont = cont__std__trim_7;
}
static void cont__std__trim_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 665: ... str(s) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__trim_8;
}
static void cont__std__trim_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 665: ... str(s) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__trim_9;
}
static void cont__std__trim_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 665: ... str(s) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__trim_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 665: ... : plus &s 1
  frame->slots[7] /* temp__5 */ = create_closure(entry__std__trim_11, 0);
  // 665: ... -> s <= e && str(s) <= ' ': plus &s 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__trim_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 666: ... -> e >= s && str(e) <= ' ': minus &e 1
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__trim_14, 0);
  // 666: while -> e >= s && str(e) <= ' ': minus &e 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__trim_24;
}
static void entry__std__trim_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // e: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 666: ... minus &e 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* e */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__std__trim_23;
}
static void cont__std__trim_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* e */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__trim_14(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // e: 0
  // s: 1
  // str: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* e */
  frame->slots[1] = myself->closure.frame->slots[1]; /* s */
  frame->slots[2] = myself->closure.frame->slots[0]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 666: ... e >= s
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* e */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__trim_15;
}
static void cont__std__trim_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 666: ... e >= s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__trim_16;
}
static void cont__std__trim_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 666: ... str(e) <= ' '
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__trim_17, 0);
  // 666: ... e >= s && str(e) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__trim_21;
}
static void entry__std__trim_17(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // str: 0
  // e: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* str */
  frame->slots[1] = myself->closure.frame->slots[0]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 666: ... str(e)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* e */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* str */;
  func = myself->type;
  frame->cont = cont__std__trim_18;
}
static void cont__std__trim_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 666: ... str(e) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__trim_19;
}
static void cont__std__trim_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 666: ... str(e) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__trim_20;
}
static void cont__std__trim_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 666: ... str(e) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__trim_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 666: ... : minus &e 1
  frame->slots[7] /* temp__5 */ = create_closure(entry__std__trim_22, 0);
  // 666: ... -> e >= s && str(e) <= ' ': minus &e 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__trim_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 667: range &str s e
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* e */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__trim_25;
}
static void cont__std__trim_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__normalize_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // str: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* str */ = create_cell_with_contents(arguments->slots[0]);
  // 675: trim &str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__std__normalize_2;
}
static void cont__std__normalize_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  // 676: ... alt(' ' '@ht;' '@nl;' '@cr;')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__9;
  arguments->slots[2] = character__10;
  arguments->slots[3] = character__13;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__std__normalize_3;
}
static void cont__std__normalize_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 676: ... many(alt(' ' '@ht;' '@nl;' '@cr;'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__std__normalize_4;
}
static void cont__std__normalize_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 676: ... many(alt(' ' '@ht;' '@nl;' '@cr;')) = " "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__578a5af303e9cc1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__normalize_5;
}
static void cont__std__normalize_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 676: replace_all &str many(alt(' ' '@ht;' '@nl;' '@cr;')) = " "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__std__normalize_6;
}
static void cont__std__normalize_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__split_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // text: 0
  // separator: 1
  // items: 2
  frame->slots[1] /* separator */ = create_future();
  frame->slots[2] /* items */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  switch(argument_count) {
    default: frame->slots[1] /* separator */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    default:
      func = cont__std__split_2;
      return;
    case 1:;
  }
  // 683: separator
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__std__split_3;
}
static void cont__std__split_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* separator */, arguments->slots[0]);
  func = cont__std__split_2;
}
static void cont__std__split_2(void) {
  // 685: $$items empty_list
  ((CELL *)frame->slots[2])->contents /* items */ = get__empty_list();
  // 686: ... :
  // 687:   grammar::search $pos $len separator text
  // 688:   if pos.is_defined:
  // 689:     push &items range(text 1 pos-1)
  // 690:     range &text pos+len -1
  // 691:   -> pos.is_defined
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__split_4, 0);
  // 686: do_while:
  // 687:   grammar::search $pos $len separator text
  // 688:   if pos.is_defined:
  // 689:     push &items range(text 1 pos-1)
  // 690:     range &text pos+len -1
  // 691:   -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do_while();
  func = myself->type;
  frame->cont = cont__std__split_16;
}
static void entry__std__split_4(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // separator: 0
  // text: 1
  // items: 2
  // pos: 3
  // len: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* separator */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* items */
  frame->slots[3] /* pos */ = create_future();
  frame->slots[4] /* len */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 687: grammar::search $pos $len separator text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* separator */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__std__split_5;
}
static void cont__std__split_5(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 687: ... pos
  initialize_future(frame->slots[3] /* pos */, frame->slots[5] /* temp__1 */);
  // 687: ... len
  initialize_future(frame->slots[4] /* len */, frame->slots[6] /* temp__2 */);
  // 688: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__split_6;
}
static void cont__std__split_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 688: ... :
  // 689:   push &items range(text 1 pos-1)
  // 690:   range &text pos+len -1
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__split_7, 0);
  // 688: if pos.is_defined:
  // 689:   push &items range(text 1 pos-1)
  // 690:   range &text pos+len -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__split_14;
}
static void entry__std__split_7(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // items: 0
  // text: 1
  // pos: 2
  // len: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* items */
  frame->slots[1] = myself->closure.frame->slots[1]; /* text */
  frame->slots[2] = myself->closure.frame->slots[3]; /* pos */
  frame->slots[3] = myself->closure.frame->slots[4]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 689: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__split_8;
}
static void cont__std__split_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 689: ... range(text 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__split_9;
}
static void cont__std__split_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 689: push &items range(text 1 pos-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* items */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__split_10;
}
static void cont__std__split_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* items */ = arguments->slots[0];
  // 690: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__split_11;
}
static void cont__std__split_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 690: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__split_12;
}
static void cont__std__split_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 690: range &text pos+len -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__split_13;
}
static void cont__std__split_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__split_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 691: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__split_15;
}
static void cont__std__split_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 691: -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__split_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 692: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__split_17;
}
static void cont__std__split_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 692: ... length_of(text) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__split_18;
}
static void cont__std__split_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 692: ... : push &items text
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__split_19, 0);
  // 692: if length_of(text) > 0: push &items text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__split_21;
}
static void entry__std__split_19(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // items: 0
  // text: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* items */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 692: ... push &items text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* items */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__split_20;
}
static void cont__std__split_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* items */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__split_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 693: -> items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* items */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__join_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // words: 0
  // separator: 1
  // text: 2
  frame->slots[2] /* text */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* separator */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* separator */ = string__578a5af303e9cc1;
  }
  // 702: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 704: ... : (word)
  // 705:   append &text word
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__join_2, 1);
  // 706: :
  // 707:   append &text separator
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__join_4, 0);
  // 703: for_each
  // 704:   words: (word)
  // 705:     append &text word
  // 706:   :
  // 707:     append &text separator
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* words */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__join_6;
}
static void entry__std__join_2(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // word: 0
  // text: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 705: append &text word
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = frame->slots[0] /* word */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__join_3;
}
static void cont__std__join_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__join_4(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // text: 0
  // separator: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* separator */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 707: append &text separator
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* separator */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__join_5;
}
static void cont__std__join_5(void) {
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
static void cont__std__join_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 708: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__count_occurrences_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // text: 0
  // expr: 1
  // n: 2
  frame->slots[2] /* n */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 717: $$n 0
  ((CELL *)frame->slots[2])->contents /* n */ = number__0;
  // 718: ... :
  // 719:   grammar::search $pos $len expr text
  // 720:   if pos.is_defined:
  // 721:     range &text pos+len -1
  // 722:     inc &n
  // 723:   -> pos.is_defined
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__count_occurrences_2, 0);
  // 718: do_while:
  // 719:   grammar::search $pos $len expr text
  // 720:   if pos.is_defined:
  // 721:     range &text pos+len -1
  // 722:     inc &n
  // 723:   -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do_while();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_12;
}
static void entry__std__count_occurrences_2(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // expr: 0
  // text: 1
  // n: 2
  // pos: 3
  // len: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* n */
  frame->slots[3] /* pos */ = create_future();
  frame->slots[4] /* len */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: grammar::search $pos $len expr text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_3;
}
static void cont__std__count_occurrences_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 719: ... pos
  initialize_future(frame->slots[3] /* pos */, frame->slots[5] /* temp__1 */);
  // 719: ... len
  initialize_future(frame->slots[4] /* len */, frame->slots[6] /* temp__2 */);
  // 720: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_4;
}
static void cont__std__count_occurrences_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 720: ... :
  // 721:   range &text pos+len -1
  // 722:   inc &n
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__count_occurrences_5, 0);
  // 720: if pos.is_defined:
  // 721:   range &text pos+len -1
  // 722:   inc &n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_10;
}
static void entry__std__count_occurrences_5(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // text: 0
  // pos: 1
  // len: 2
  // n: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  frame->slots[1] = myself->closure.frame->slots[3]; /* pos */
  frame->slots[2] = myself->closure.frame->slots[4]; /* len */
  frame->slots[3] = myself->closure.frame->slots[2]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 721: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* pos */;
  arguments->slots[1] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_6;
}
static void cont__std__count_occurrences_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 721: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_7;
}
static void cont__std__count_occurrences_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 721: range &text pos+len -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_8;
}
static void cont__std__count_occurrences_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 722: inc &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* n */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_9;
}
static void cont__std__count_occurrences_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* n */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__count_occurrences_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 723: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__count_occurrences_11;
}
static void cont__std__count_occurrences_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 723: -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__count_occurrences_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 724: -> n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* n */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__matches_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // text: 0
  // expr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 733: ... grammar::match(expr text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* text */;
  result_count = 1;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__types__string__matches_2;
}
static void cont__types__string__matches_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 733: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__string__matches_3;
}
static void cont__types__string__matches_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 733: ... grammar::match(expr text) == length_of(text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__string__matches_4;
}
static void cont__types__string__matches_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 733: -> grammar::match(expr text) == length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__contains_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // text: 0
  // expr: 1
  // pos: 2
  // len: 3
  frame->slots[2] /* pos */ = create_future();
  frame->slots[3] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 742: grammar::search $pos $_len expr text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* text */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__types__string__contains_2;
}
static void cont__types__string__contains_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  frame->slots[5] /* temp__2 */ = arguments->slots[1];
  // 742: ... pos
  initialize_future(frame->slots[2] /* pos */, frame->slots[4] /* temp__1 */);
  // 742: ... _len
  initialize_future(frame->slots[3] /* len */, frame->slots[5] /* temp__2 */);
  // 743: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__string__contains_3;
}
static void cont__types__string__contains_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 743: -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__replace_umlauts_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // text: 0
  // s: 1
  // result: 2
  // copy: 3
  frame->slots[3] /* copy */ = create_future();
  frame->slots[1] /* s */ = create_cell();
  frame->slots[2] /* result */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1052: ... : (idx)
  // 1053:   append &result range(text s idx)
  // 1054:   !s idx+2
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__replace_umlauts_2, 1);
  // 1052: $copy: (idx)
  // 1053:   append &result range(text s idx)
  // 1054:   !s idx+2
  initialize_future(frame->slots[3] /* copy */, frame->slots[4] /* temp__1 */);
  // 1049: $$s 1
  ((CELL *)frame->slots[1])->contents /* s */ = number__1;
  // 1050: $$result ""
  ((CELL *)frame->slots[2])->contents /* result */ = empty_string;
  // 1056: ... : (idx chr)
  // 1057:   if chr >= '@0x80;':
  // 1058:     if
  // 1059:       chr >= '@nbsp;':
  // 1060:         copy idx-1
  // 1061:         $conversion umlaut_conversions(chr)
  // 1062:         if
  // 1063:           conversion.is_defined:
  // 1064:             append &result conversion
  // 1065:           :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__replace_umlauts_6, 2);
  // 1056: for_each text: (idx chr)
  // 1057:   if chr >= '@0x80;':
  // 1058:     if
  // 1059:       chr >= '@nbsp;':
  // 1060:         copy idx-1
  // 1061:         $conversion umlaut_conversions(chr)
  // 1062:         if
  // 1063:           conversion.is_defined:
  // 1064:             append &result conversion
  // 1065:           :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_26;
}
static void entry__std__replace_umlauts_17(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // result: 0
  // conversion: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* result */
  frame->slots[1] = myself->closure.frame->slots[4]; /* conversion */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1064: append &result conversion
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[1] /* conversion */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_18;
}
static void cont__std__replace_umlauts_18(void) {
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
static void entry__std__replace_umlauts_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // result: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1066: push &result '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_20;
}
static void cont__std__replace_umlauts_20(void) {
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
static void entry__std__replace_umlauts_12(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // copy: 0
  // idx: 1
  // chr: 2
  // result: 3
  // conversion: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* copy */
  frame->slots[1] = myself->closure.frame->slots[2]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[0]; /* chr */
  frame->slots[3] = myself->closure.frame->slots[3]; /* result */
  frame->slots[4] /* conversion */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1060: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_13;
}
static void cont__std__replace_umlauts_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1060: copy idx-1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* copy */;
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_14;
}
static void cont__std__replace_umlauts_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1061: $conversion umlaut_conversions(chr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* chr */;
  result_count = 1;
  myself = var._umlaut_conversions;
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_15;
}
static void cont__std__replace_umlauts_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* conversion */, arguments->slots[0]);
  // 1063: conversion.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* conversion */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_16;
}
static void cont__std__replace_umlauts_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1063: ... :
  // 1064:   append &result conversion
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__replace_umlauts_17, 0);
  // 1065: :
  // 1066:   push &result '?'
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__replace_umlauts_19, 0);
  // 1062: if
  // 1063:   conversion.is_defined:
  // 1064:     append &result conversion
  // 1065:   :
  // 1066:     push &result '?'
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
static void entry__std__replace_umlauts_21(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // copy: 0
  // idx: 1
  // result: 2
  // chr: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* copy */
  frame->slots[1] = myself->closure.frame->slots[2]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[3]; /* result */
  frame->slots[3] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1068: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_22;
}
static void cont__std__replace_umlauts_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1068: copy idx-1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* copy */;
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_23;
}
static void cont__std__replace_umlauts_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1069: ... chr-0x80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* chr */;
  arguments->slots[1] = number__0x80;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_24;
}
static void cont__std__replace_umlauts_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1069: push &result chr-0x80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_25;
}
static void cont__std__replace_umlauts_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__replace_umlauts_9(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // chr: 0
  // copy: 1
  // idx: 2
  // result: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* chr */
  frame->slots[1] = myself->closure.frame->slots[2]; /* copy */
  frame->slots[2] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1059: chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__160;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_10;
}
static void cont__std__replace_umlauts_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1059: chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_11;
}
static void cont__std__replace_umlauts_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1059: ... :
  // 1060:   copy idx-1
  // 1061:   $conversion umlaut_conversions(chr)
  // 1062:   if
  // 1063:     conversion.is_defined:
  // 1064:       append &result conversion
  // 1065:     :
  // 1066:       push &result '?'
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__replace_umlauts_12, 0);
  // 1067: :
  // 1068:   copy idx-1
  // 1069:   push &result chr-0x80
  frame->slots[7] /* temp__4 */ = create_closure(entry__std__replace_umlauts_21, 0);
  // 1058: if
  // 1059:   chr >= '@nbsp;':
  // 1060:     copy idx-1
  // 1061:     $conversion umlaut_conversions(chr)
  // 1062:     if
  // 1063:       conversion.is_defined:
  // 1064:         append &result conversion
  // 1065:       :
  // 1066:         push &result '?'
  // 1067:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__replace_umlauts_2(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // idx: 0
  // result: 1
  // text: 2
  // s: 3
  frame->slots[1] = myself->closure.frame->slots[2]; /* result */
  frame->slots[2] = myself->closure.frame->slots[0]; /* text */
  frame->slots[3] = myself->closure.frame->slots[1]; /* s */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1053: ... range(text s idx)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[2] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_3;
}
static void cont__std__replace_umlauts_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1053: append &result range(text s idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_4;
}
static void cont__std__replace_umlauts_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* result */ = arguments->slots[0];
  // 1054: !s idx+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_5;
}
static void cont__std__replace_umlauts_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* s */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__replace_umlauts_6(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // idx: 0
  // chr: 1
  // copy: 2
  // result: 3
  frame->slots[2] = myself->closure.frame->slots[3]; /* copy */
  frame->slots[3] = myself->closure.frame->slots[2]; /* result */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1057: ... chr >= '@0x80;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__128;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_7;
}
static void cont__std__replace_umlauts_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1057: ... chr >= '@0x80;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_8;
}
static void cont__std__replace_umlauts_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1057: ... :
  // 1058:   if
  // 1059:     chr >= '@nbsp;':
  // 1060:       copy idx-1
  // 1061:       $conversion umlaut_conversions(chr)
  // 1062:       if
  // 1063:         conversion.is_defined:
  // 1064:           append &result conversion
  // 1065:         :
  // 1066:           push &result '?'
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__replace_umlauts_9, 0);
  // 1057: if chr >= '@0x80;':
  // 1058:   if
  // 1059:     chr >= '@nbsp;':
  // 1060:       copy idx-1
  // 1061:       $conversion umlaut_conversions(chr)
  // 1062:       if
  // 1063:         conversion.is_defined:
  // 1064:           append &result conversion
  // 1065:         :
  // 1066:           push &result '?'
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__replace_umlauts_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1070: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_27;
}
static void cont__std__replace_umlauts_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1070: copy length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[3] /* copy */;
  func = myself->type;
  frame->cont = cont__std__replace_umlauts_28;
}
static void cont__std__replace_umlauts_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1071: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__replace_all_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // text: 0
  // args: 1
  // new_text: 2
  frame->slots[2] /* new_text */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* args */ = from_arguments(1, argument_count-1);
  // 1101: $$new_text ""
  ((CELL *)frame->slots[2])->contents /* new_text */ = empty_string;
  // 1102: ... -> length_of(text) > 0:
  // 1103:   do: (-> break)
  // 1104:     for_each args: (arg)
  // 1105:       $expression key_of(arg)
  // 1106:       $replacement value_of(arg)
  // 1107:       grammar::match $len expression text
  // 1108:       if len.is_defined:
  // 1109:         if
  // 1110:           replacement.is_a_string:
  // 1111:             append &new_text replacement
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__replace_all_2, 0);
  // 1102: while -> length_of(text) > 0:
  // 1103:   do: (-> break)
  // 1104:     for_each args: (arg)
  // 1105:       $expression key_of(arg)
  // 1106:       $replacement value_of(arg)
  // 1107:       grammar::match $len expression text
  // 1108:       if len.is_defined:
  // 1109:         if
  // 1110:           replacement.is_a_string:
  // 1111:             append &new_text replacement
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__replace_all_29;
}
static void entry__std__replace_all_6(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // break: 0
  // args: 1
  // text: 2
  // new_text: 3
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  frame->slots[2] = myself->closure.frame->slots[1]; /* text */
  frame->slots[3] = myself->closure.frame->slots[2]; /* new_text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1104: ... : (arg)
  // 1105:   $expression key_of(arg)
  // 1106:   $replacement value_of(arg)
  // 1107:   grammar::match $len expression text
  // 1108:   if len.is_defined:
  // 1109:     if
  // 1110:       replacement.is_a_string:
  // 1111:         append &new_text replacement
  // 1112:       :
  // 1113:         append &new_text replacement(range(text 1 len))
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__replace_all_7, 1);
  // 1104: for_each args: (arg)
  // 1105:   $expression key_of(arg)
  // 1106:   $replacement value_of(arg)
  // 1107:   grammar::match $len expression text
  // 1108:   if len.is_defined:
  // 1109:     if
  // 1110:       replacement.is_a_string:
  // 1111:         append &new_text replacement
  // 1112:       :
  // 1113:         append &new_text replacement(range(text 1 len))
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__replace_all_24;
}
static void entry__std__replace_all_12(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // replacement: 0
  // new_text: 1
  // text: 2
  // len: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* replacement */
  frame->slots[1] = myself->closure.frame->slots[2]; /* new_text */
  frame->slots[2] = myself->closure.frame->slots[1]; /* text */
  frame->slots[3] = myself->closure.frame->slots[6]; /* len */
  frame->slots[4] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1110: replacement.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* replacement */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__std__replace_all_13;
}
static void cont__std__replace_all_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1110: ... :
  // 1111:   append &new_text replacement
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__replace_all_14, 0);
  // 1112: :
  // 1113:   append &new_text replacement(range(text 1 len))
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__replace_all_16, 0);
  // 1109: if
  // 1110:   replacement.is_a_string:
  // 1111:     append &new_text replacement
  // 1112:   :
  // 1113:     append &new_text replacement(range(text 1 len))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__replace_all_20;
}
static void entry__std__replace_all_14(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // new_text: 0
  // replacement: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_text */
  frame->slots[1] = myself->closure.frame->slots[0]; /* replacement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1111: append &new_text replacement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_text */;
  arguments->slots[1] = frame->slots[1] /* replacement */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__replace_all_15;
}
static void cont__std__replace_all_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__replace_all_16(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // new_text: 0
  // replacement: 1
  // text: 2
  // len: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_text */
  frame->slots[1] = myself->closure.frame->slots[0]; /* replacement */
  frame->slots[2] = myself->closure.frame->slots[2]; /* text */
  frame->slots[3] = myself->closure.frame->slots[3]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1113: ... range(text 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__replace_all_17;
}
static void cont__std__replace_all_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1113: ... replacement(range(text 1 len))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* replacement */;
  func = myself->type;
  frame->cont = cont__std__replace_all_18;
}
static void cont__std__replace_all_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1113: append &new_text replacement(range(text 1 len))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__replace_all_19;
}
static void cont__std__replace_all_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__replace_all_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1114: ... len+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__replace_all_21;
}
static void cont__std__replace_all_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1114: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__replace_all_22;
}
static void cont__std__replace_all_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1114: range &text len+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__replace_all_23;
}
static void cont__std__replace_all_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* text */ = arguments->slots[0];
  // 1115: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__replace_all_7(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // arg: 0
  // text: 1
  // new_text: 2
  // break: 3
  // expression: 4
  // replacement: 5
  // len: 6
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  frame->slots[2] = myself->closure.frame->slots[3]; /* new_text */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  frame->slots[4] /* expression */ = create_future();
  frame->slots[5] /* replacement */ = create_future();
  frame->slots[6] /* len */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1105: $expression key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__replace_all_8;
}
static void cont__std__replace_all_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* expression */, arguments->slots[0]);
  // 1106: $replacement value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__replace_all_9;
}
static void cont__std__replace_all_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* replacement */, arguments->slots[0]);
  // 1107: grammar::match $len expression text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* expression */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__std__replace_all_10;
}
static void cont__std__replace_all_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* len */, arguments->slots[0]);
  // 1108: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__replace_all_11;
}
static void cont__std__replace_all_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 1108: ... :
  // 1109:   if
  // 1110:     replacement.is_a_string:
  // 1111:       append &new_text replacement
  // 1112:     :
  // 1113:       append &new_text replacement(range(text 1 len))
  // 1114:   range &text len+1 -1
  // 1115:   break
  frame->slots[8] /* temp__2 */ = create_closure(entry__std__replace_all_12, 0);
  // 1108: if len.is_defined:
  // 1109:   if
  // 1110:     replacement.is_a_string:
  // 1111:       append &new_text replacement
  // 1112:     :
  // 1113:       append &new_text replacement(range(text 1 len))
  // 1114:   range &text len+1 -1
  // 1115:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__replace_all_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1116: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* text */;
  func = myself->type;
  frame->cont = cont__std__replace_all_25;
}
static void cont__std__replace_all_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1116: push &new_text text(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* new_text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__replace_all_26;
}
static void cont__std__replace_all_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* new_text */ = arguments->slots[0];
  // 1117: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__replace_all_27;
}
static void cont__std__replace_all_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1117: range &text 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__replace_all_28;
}
static void cont__std__replace_all_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__replace_all_5(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // args: 0
  // text: 1
  // new_text: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* args */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1103: ... : (-> break)
  // 1104:   for_each args: (arg)
  // 1105:     $expression key_of(arg)
  // 1106:     $replacement value_of(arg)
  // 1107:     grammar::match $len expression text
  // 1108:     if len.is_defined:
  // 1109:       if
  // 1110:         replacement.is_a_string:
  // 1111:           append &new_text replacement
  // 1112:         :
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__replace_all_6, 0);
  // 1103: do: (-> break)
  // 1104:   for_each args: (arg)
  // 1105:     $expression key_of(arg)
  // 1106:     $replacement value_of(arg)
  // 1107:     grammar::match $len expression text
  // 1108:     if len.is_defined:
  // 1109:       if
  // 1110:         replacement.is_a_string:
  // 1111:           append &new_text replacement
  // 1112:         :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__replace_all_2(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // text: 0
  // args: 1
  // new_text: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* args */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1102: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__replace_all_3;
}
static void cont__std__replace_all_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1102: ... length_of(text) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__replace_all_4;
}
static void cont__std__replace_all_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1102: ... :
  // 1103:   do: (-> break)
  // 1104:     for_each args: (arg)
  // 1105:       $expression key_of(arg)
  // 1106:       $replacement value_of(arg)
  // 1107:       grammar::match $len expression text
  // 1108:       if len.is_defined:
  // 1109:         if
  // 1110:           replacement.is_a_string:
  // 1111:             append &new_text replacement
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__replace_all_5, 0);
  // 1102: ... -> length_of(text) > 0:
  // 1103:   do: (-> break)
  // 1104:     for_each args: (arg)
  // 1105:       $expression key_of(arg)
  // 1106:       $replacement value_of(arg)
  // 1107:       grammar::match $len expression text
  // 1108:       if len.is_defined:
  // 1109:         if
  // 1110:           replacement.is_a_string:
  // 1111:             append &new_text replacement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__replace_all_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1118: -> new_text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__delete_all_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // text: 0
  // expressions: 1
  // new_text: 2
  frame->slots[2] /* new_text */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* expressions */ = from_arguments(1, argument_count-1);
  // 1127: $$new_text ""
  ((CELL *)frame->slots[2])->contents /* new_text */ = empty_string;
  // 1128: ... -> length_of(text) > 0:
  // 1129:   do: (-> break)
  // 1130:     for_each expressions: (expression)
  // 1131:       grammar::match $len expression text
  // 1132:       if len.is_defined:
  // 1133:         range &text len+1 -1
  // 1134:         break
  // 1135:     push &new_text text(1)
  // 1136:     range &text 2 -1
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__delete_all_2, 0);
  // 1128: while -> length_of(text) > 0:
  // 1129:   do: (-> break)
  // 1130:     for_each expressions: (expression)
  // 1131:       grammar::match $len expression text
  // 1132:       if len.is_defined:
  // 1133:         range &text len+1 -1
  // 1134:         break
  // 1135:     push &new_text text(1)
  // 1136:     range &text 2 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__delete_all_19;
}
static void entry__std__delete_all_6(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // break: 0
  // expressions: 1
  // text: 2
  // new_text: 3
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* expressions */
  frame->slots[2] = myself->closure.frame->slots[1]; /* text */
  frame->slots[3] = myself->closure.frame->slots[2]; /* new_text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1130: ... : (expression)
  // 1131:   grammar::match $len expression text
  // 1132:   if len.is_defined:
  // 1133:     range &text len+1 -1
  // 1134:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__delete_all_7, 1);
  // 1130: for_each expressions: (expression)
  // 1131:   grammar::match $len expression text
  // 1132:   if len.is_defined:
  // 1133:     range &text len+1 -1
  // 1134:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expressions */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__delete_all_14;
}
static void entry__std__delete_all_10(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // text: 0
  // len: 1
  // break: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  frame->slots[1] = myself->closure.frame->slots[3]; /* len */
  frame->slots[2] = myself->closure.frame->slots[2]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1133: ... len+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__delete_all_11;
}
static void cont__std__delete_all_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1133: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__delete_all_12;
}
static void cont__std__delete_all_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1133: range &text len+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__delete_all_13;
}
static void cont__std__delete_all_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 1134: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__delete_all_7(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // expression: 0
  // text: 1
  // break: 2
  // len: 3
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  frame->slots[2] = myself->closure.frame->slots[0]; /* break */
  frame->slots[3] /* len */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1131: grammar::match $len expression text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__std__delete_all_8;
}
static void cont__std__delete_all_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 1132: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__delete_all_9;
}
static void cont__std__delete_all_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1132: ... :
  // 1133:   range &text len+1 -1
  // 1134:   break
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__delete_all_10, 0);
  // 1132: if len.is_defined:
  // 1133:   range &text len+1 -1
  // 1134:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__delete_all_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1135: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* text */;
  func = myself->type;
  frame->cont = cont__std__delete_all_15;
}
static void cont__std__delete_all_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1135: push &new_text text(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* new_text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__delete_all_16;
}
static void cont__std__delete_all_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* new_text */ = arguments->slots[0];
  // 1136: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__delete_all_17;
}
static void cont__std__delete_all_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1136: range &text 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__delete_all_18;
}
static void cont__std__delete_all_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__delete_all_5(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // expressions: 0
  // text: 1
  // new_text: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* expressions */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1129: ... : (-> break)
  // 1130:   for_each expressions: (expression)
  // 1131:     grammar::match $len expression text
  // 1132:     if len.is_defined:
  // 1133:       range &text len+1 -1
  // 1134:       break
  // 1135:   push &new_text text(1)
  // 1136:   range &text 2 -1
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__delete_all_6, 0);
  // 1129: do: (-> break)
  // 1130:   for_each expressions: (expression)
  // 1131:     grammar::match $len expression text
  // 1132:     if len.is_defined:
  // 1133:       range &text len+1 -1
  // 1134:       break
  // 1135:   push &new_text text(1)
  // 1136:   range &text 2 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__delete_all_2(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // text: 0
  // expressions: 1
  // new_text: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* expressions */
  frame->slots[2] = myself->closure.frame->slots[2]; /* new_text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1128: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__delete_all_3;
}
static void cont__std__delete_all_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1128: ... length_of(text) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__delete_all_4;
}
static void cont__std__delete_all_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1128: ... :
  // 1129:   do: (-> break)
  // 1130:     for_each expressions: (expression)
  // 1131:       grammar::match $len expression text
  // 1132:       if len.is_defined:
  // 1133:         range &text len+1 -1
  // 1134:         break
  // 1135:     push &new_text text(1)
  // 1136:     range &text 2 -1
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__delete_all_5, 0);
  // 1128: ... -> length_of(text) > 0:
  // 1129:   do: (-> break)
  // 1130:     for_each expressions: (expression)
  // 1131:       grammar::match $len expression text
  // 1132:       if len.is_defined:
  // 1133:         range &text len+1 -1
  // 1134:         break
  // 1135:     push &new_text text(1)
  // 1136:     range &text 2 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__delete_all_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1137: -> new_text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__spaces_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // n: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1150: ... dup(" " n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__spaces_4;
}
static void cont__std__spaces_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1150: ... -> dup(" " n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__spaces_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // n: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1150: ... range(eighty_spaces 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._eighty_spaces;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__spaces_6;
}
static void cont__std__spaces_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1150: ... -> range(eighty_spaces 1 n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__spaces_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // n: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1150: ... n > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__80;
  arguments->slots[1] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__spaces_2;
}
static void cont__std__spaces_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1150: ... -> dup(" " n)
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__spaces_3, 0);
  // 1150: ... -> range(eighty_spaces 1 n)
  frame->slots[3] /* temp__3 */ = create_closure(entry__std__spaces_5, 0);
  // 1150: if n > 80 (-> dup(" " n)) -> range(eighty_spaces 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__indented_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // indent: 0
  // text: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* text */ = create_cell_with_contents(arguments->slots[1]);
  // 1159: ... indent > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__indented_2;
}
static void cont__std__indented_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1159: ... :
  // 1160:   $indentation spaces(indent)
  // 1161:   replace_all
  // 1162:     &text
  // 1163:     '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT)) = "@nl;@(indentation)"
  // 1164:   unless length_of(text) == 0 || text(1) == '@nl;': append indentation &text
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__indented_3, 0);
  // 1159: if indent > 0:
  // 1160:   $indentation spaces(indent)
  // 1161:   replace_all
  // 1162:     &text
  // 1163:     '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT)) = "@nl;@(indentation)"
  // 1164:   unless length_of(text) == 0 || text(1) == '@nl;': append indentation &text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__indented_20;
}
static void entry__std__indented_18(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // text: 0
  // indentation: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indentation */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1164: ... append indentation &text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indentation */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__indented_19;
}
static void cont__std__indented_19(void) {
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
static void entry__std__indented_3(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // indent: 0
  // text: 1
  // indentation: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* indent */
  frame->slots[1] = myself->closure.frame->slots[1]; /* text */
  frame->slots[2] /* indentation */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1160: $indentation spaces(indent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__std__indented_4;
}
static void cont__std__indented_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* indentation */, arguments->slots[0]);
  // 1163: ... alt('@nl;' END_OF_TEXT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__10;
  arguments->slots[1] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__std__indented_5;
}
static void cont__std__indented_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 1163: ... not_followed_by(alt('@nl;' END_OF_TEXT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__std__indented_6;
}
static void cont__std__indented_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1163: '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__10;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__std__indented_7;
}
static void cont__std__indented_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1163: ... "@nl;@(indentation)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ceb;
  arguments->slots[1] = frame->slots[2] /* indentation */;
  result_count = 1;
  myself = var.std__string;
  func = myself->type;
  frame->cont = cont__std__indented_9;
}
static void cont__std__indented_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 1163: '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT)) = "@nl;@(indentation)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__indented_10;
}
static void cont__std__indented_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1161: replace_all
  // 1162:   &text
  // 1163:   '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT)) = "@nl;@(indentation)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__std__indented_11;
}
static void cont__std__indented_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* text */ = arguments->slots[0];
  // 1164: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__indented_12;
}
static void cont__std__indented_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1164: ... length_of(text) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__indented_13;
}
static void cont__std__indented_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1164: ... text(1) == '@nl;'
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__indented_14, 0);
  // 1164: ... length_of(text) == 0 || text(1) == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__indented_17;
}
static void entry__std__indented_14(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1164: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__std__indented_15;
}
static void cont__std__indented_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1164: ... text(1) == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__indented_16;
}
static void cont__std__indented_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1164: ... text(1) == '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__indented_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1164: ... : append indentation &text
  frame->slots[7] /* temp__5 */ = create_closure(entry__std__indented_18, 0);
  // 1164: unless length_of(text) == 0 || text(1) == '@nl;': append indentation &text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__indented_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1165: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__for_each_line_29(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // body: 0
  // no: 1
  // text: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* no */
  frame->slots[2] = myself->closure.frame->slots[2]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1191: body no text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* no */;
  arguments->slots[1] = frame->slots[2] /* text */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__for_each_line_30(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // text: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1193: body text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* text */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__for_each_line_26(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // body: 0
  // no: 1
  // text: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* no */
  frame->slots[2] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1190: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__for_each_line_27;
}
static void cont__std__for_each_line_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1190: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__for_each_line_28;
}
static void cont__std__for_each_line_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1190: ... :
  // 1191:   body no text
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__for_each_line_29, 0);
  // 1192: :
  // 1193:   body text
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__for_each_line_30, 0);
  // 1189: if
  // 1190:   parameter_count_of(body) == 2:
  // 1191:     body no text
  // 1192:   :
  // 1193:     body text
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__for_each_line_4(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // body: 0
  // no: 1
  // text: 2
  // pos: 3
  // body2: 4
  // rest: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  frame->slots[1] = myself->closure.frame->slots[3]; /* no */
  frame->slots[2] = myself->closure.frame->slots[0]; /* text */
  frame->slots[3] = myself->closure.frame->slots[4]; /* pos */
  frame->slots[4] = myself->closure.frame->slots[2]; /* body2 */
  frame->slots[5] /* rest */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1180: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__for_each_line_5;
}
static void cont__std__for_each_line_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1180: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__for_each_line_6;
}
static void cont__std__for_each_line_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1180: ... :
  // 1181:   body no range(text 1 pos-1)
  frame->slots[8] /* temp__3 */ = create_closure(entry__std__for_each_line_7, 0);
  // 1182: :
  // 1183:   body range(text 1 pos-1)
  frame->slots[9] /* temp__4 */ = create_closure(entry__std__for_each_line_10, 0);
  // 1179: if
  // 1180:   parameter_count_of(body) == 2:
  // 1181:     body no range(text 1 pos-1)
  // 1182:   :
  // 1183:     body range(text 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__for_each_line_13;
}
static void entry__std__for_each_line_7(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // body: 0
  // no: 1
  // text: 2
  // pos: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* no */
  frame->slots[2] = myself->closure.frame->slots[2]; /* text */
  frame->slots[3] = myself->closure.frame->slots[3]; /* pos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1181: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__for_each_line_8;
}
static void cont__std__for_each_line_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1181: ... range(text 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__for_each_line_9;
}
static void cont__std__for_each_line_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1181: body no range(text 1 pos-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* no */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__for_each_line_10(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // body: 0
  // text: 1
  // pos: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  frame->slots[2] = myself->closure.frame->slots[3]; /* pos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1183: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__for_each_line_11;
}
static void cont__std__for_each_line_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1183: ... range(text 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__for_each_line_12;
}
static void cont__std__for_each_line_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1183: body range(text 1 pos-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__for_each_line_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1184: ... pos+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__for_each_line_14;
}
static void cont__std__for_each_line_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1184: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__for_each_line_15;
}
static void cont__std__for_each_line_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1184: $rest range(text pos+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__for_each_line_16;
}
static void cont__std__for_each_line_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* rest */, arguments->slots[0]);
  // 1185: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__for_each_line_17;
}
static void cont__std__for_each_line_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1185: ... rest .has_minimum_length. 1
  frame->slots[8] /* temp__3 */ = create_closure(entry__std__for_each_line_18, 0);
  // 1185: ... body2.is_defined && rest .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__for_each_line_20;
}
static void entry__std__for_each_line_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // rest: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* rest */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1185: ... rest .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* rest */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__for_each_line_19;
}
static void cont__std__for_each_line_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1185: ... rest .has_minimum_length. 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__for_each_line_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1185: if body2.is_defined && rest .has_minimum_length. 1 body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* body2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__for_each_line_21;
}
static void cont__std__for_each_line_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1186: ... no+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* no */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__for_each_line_22;
}
static void cont__std__for_each_line_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1186: for_each_line rest body body2 no+1
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* rest */;
  arguments->slots[1] = frame->slots[0] /* body */;
  arguments->slots[2] = frame->slots[4] /* body2 */;
  arguments->slots[3] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__for_each_line_23(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // text: 0
  // body: 1
  // no: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  frame->slots[2] = myself->closure.frame->slots[3]; /* no */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1188: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__for_each_line_24;
}
static void cont__std__for_each_line_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1188: ... length_of(text) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__for_each_line_25;
}
static void cont__std__for_each_line_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1188: ... :
  // 1189:   if
  // 1190:     parameter_count_of(body) == 2:
  // 1191:       body no text
  // 1192:     :
  // 1193:       body text
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__for_each_line_26, 0);
  // 1188: if length_of(text) > 0:
  // 1189:   if
  // 1190:     parameter_count_of(body) == 2:
  // 1191:       body no text
  // 1192:     :
  // 1193:       body text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__for_each_line_1(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // text: 0
  // body: 1
  // body2: 2
  // no: 3
  // pos: 4
  // len: 5
  frame->slots[4] /* pos */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* no */ = arguments->slots[3];
    case 3: frame->slots[2] /* body2 */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* body2 */ = undefined;
    case 3: frame->slots[3] /* no */ = number__1;
  }
  // 1176: search text '@nl;' $pos $_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = character__10;
  result_count = 2;
  myself = get__search();
  func = myself->type;
  frame->cont = cont__std__for_each_line_2;
}
static void cont__std__for_each_line_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 1176: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 1176: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 1178: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__for_each_line_3;
}
static void cont__std__for_each_line_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1178: ... :
  // 1179:   if
  // 1180:     parameter_count_of(body) == 2:
  // 1181:       body no range(text 1 pos-1)
  // 1182:     :
  // 1183:       body range(text 1 pos-1)
  // 1184:   $rest range(text pos+1 -1)
  // 1185:   if body2.is_defined && rest .has_minimum_length. 1 body2
  // 1186:   for_each_line rest body body2 no+1
  frame->slots[7] /* temp__2 */ = create_closure(entry__std__for_each_line_4, 0);
  // 1187: :
  // 1188:   if length_of(text) > 0:
  // 1189:     if
  // 1190:       parameter_count_of(body) == 2:
  // 1191:         body no text
  // 1192:       :
  // 1193:         body text
  frame->slots[8] /* temp__3 */ = create_closure(entry__std__for_each_line_23, 0);
  // 1177: if
  // 1178:   pos.is_defined:
  // 1179:     if
  // 1180:       parameter_count_of(body) == 2:
  // 1181:         body no range(text 1 pos-1)
  // 1182:       :
  // 1183:         body range(text 1 pos-1)
  // 1184:     $rest range(text pos+1 -1)
  // 1185:     if body2.is_defined && rest .has_minimum_length. 1 body2
  // 1186:     for_each_line rest body body2 no+1
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__to_lower_case_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // text: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1201: ... map(text to_lower_case)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = get__to_lower_case();
  result_count = 1;
  myself = get__map();
  func = myself->type;
  frame->cont = cont__types__string__to_lower_case_2;
}
static void cont__types__string__to_lower_case_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1201: -> map(text to_lower_case)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__to_upper_case_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // text: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1209: ... map(text to_upper_case)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = get__to_upper_case();
  result_count = 1;
  myself = get__map();
  func = myself->type;
  frame->cont = cont__types__string__to_upper_case_2;
}
static void cont__types__string__to_upper_case_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1209: -> map(text to_upper_case)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__to_title_case_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  // out: 1
  // to_upper: 2
  frame->slots[1] /* out */ = create_cell();
  frame->slots[2] /* to_upper */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1217: $$out ""
  ((CELL *)frame->slots[1])->contents /* out */ = empty_string;
  // 1218: $$to_upper true
  ((CELL *)frame->slots[2])->contents /* to_upper */ = get__true();
  // 1219: ... : (chr)
  // 1220:   if
  // 1221:     chr.is_a_letter_character:
  // 1222:       if
  // 1223:         to_upper:
  // 1224:           push &out chr.to_upper_case
  // 1225:           !to_upper false
  // 1226:         :
  // 1227:           push &out chr.to_lower_case
  // 1228:     :
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__string__to_title_case_2, 1);
  // 1219: for_each text: (chr)
  // 1220:   if
  // 1221:     chr.is_a_letter_character:
  // 1222:       if
  // 1223:         to_upper:
  // 1224:           push &out chr.to_upper_case
  // 1225:           !to_upper false
  // 1226:         :
  // 1227:           push &out chr.to_lower_case
  // 1228:     :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__string__to_title_case_13;
}
static void entry__types__string__to_title_case_5(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // out: 0
  // chr: 1
  // to_upper: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* out */
  frame->slots[1] = myself->closure.frame->slots[2]; /* chr */
  frame->slots[2] = myself->closure.frame->slots[0]; /* to_upper */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1224: ... chr.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__types__string__to_title_case_6;
}
static void cont__types__string__to_title_case_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1224: push &out chr.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* out */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__string__to_title_case_7;
}
static void cont__types__string__to_title_case_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* out */ = arguments->slots[0];
  // 1225: !to_upper false
  ((CELL *)frame->slots[2])->contents /* to_upper */ = get__false();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__to_title_case_8(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // out: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* out */
  frame->slots[1] = myself->closure.frame->slots[2]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1227: ... chr.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__types__string__to_title_case_9;
}
static void cont__types__string__to_title_case_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1227: push &out chr.to_lower_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* out */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__string__to_title_case_10;
}
static void cont__types__string__to_title_case_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* out */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__to_title_case_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // to_upper: 0
  // out: 1
  // chr: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* to_upper */
  frame->slots[1] = myself->closure.frame->slots[2]; /* out */
  frame->slots[2] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1223: ... :
  // 1224:   push &out chr.to_upper_case
  // 1225:   !to_upper false
  frame->slots[3] /* temp__1 */ = create_closure(entry__types__string__to_title_case_5, 0);
  // 1226: :
  // 1227:   push &out chr.to_lower_case
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__string__to_title_case_8, 0);
  // 1222: if
  // 1223:   to_upper:
  // 1224:     push &out chr.to_upper_case
  // 1225:     !to_upper false
  // 1226:   :
  // 1227:     push &out chr.to_lower_case
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* to_upper */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__string__to_title_case_11(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // out: 0
  // chr: 1
  // to_upper: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* out */
  frame->slots[1] = myself->closure.frame->slots[0]; /* chr */
  frame->slots[2] = myself->closure.frame->slots[1]; /* to_upper */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1229: push &out chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* out */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__string__to_title_case_12;
}
static void cont__types__string__to_title_case_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* out */ = arguments->slots[0];
  // 1230: !to_upper true
  ((CELL *)frame->slots[2])->contents /* to_upper */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__string__to_title_case_2(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // chr: 0
  // to_upper: 1
  // out: 2
  frame->slots[1] = myself->closure.frame->slots[2]; /* to_upper */
  frame->slots[2] = myself->closure.frame->slots[1]; /* out */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1221: chr.is_a_letter_character
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter_character();
  func = myself->type;
  frame->cont = cont__types__string__to_title_case_3;
}
static void cont__types__string__to_title_case_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1221: ... :
  // 1222:   if
  // 1223:     to_upper:
  // 1224:       push &out chr.to_upper_case
  // 1225:       !to_upper false
  // 1226:     :
  // 1227:       push &out chr.to_lower_case
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__string__to_title_case_4, 0);
  // 1228: :
  // 1229:   push &out chr
  // 1230:   !to_upper true
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__string__to_title_case_11, 0);
  // 1220: if
  // 1221:   chr.is_a_letter_character:
  // 1222:     if
  // 1223:       to_upper:
  // 1224:         push &out chr.to_upper_case
  // 1225:         !to_upper false
  // 1226:       :
  // 1227:         push &out chr.to_lower_case
  // 1228:   :
  // 1229:     push &out chr
  // ...
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
static void cont__types__string__to_title_case_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1231: -> out
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* out */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__octet_string__new_empty_collection_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1239: -> types::octet_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__types__octet_string();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__quad_octet_string__new_empty_collection_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1247: -> types::octet_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__types__octet_string();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__collect_output_1(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // self: 0
  // body: 1
  // return__1: 2
  frame->slots[2] /* return__1 */ = create_continuation_with_exit(exit__std__collect_output_1);
  define__std__write(create_future());
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  frame->slots[1] /* body */ = arguments->slots[argument_count-1];
  switch(argument_count) {
    default: frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[0] /* self */ = create_cell_with_contents(empty_string);
  }
  // 1256: ... : (args*) write_to &self args*
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__collect_output_2, -1);
  // 1256: %std::write: (args*) write_to &self args*
  initialize_future(get__std__write(), frame->slots[3] /* temp__1 */);
  // 1258: body
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__std__collect_output_4;
}
static void entry__std__collect_output_2(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // args: 0
  // self: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 1256: ... write_to &self args*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = ((CELL *)frame->slots[1])->contents /* self */;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__std__collect_output_3;
}
static void cont__std__collect_output_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* self */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__collect_output_4(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__std__collect_output_1(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i;
  int n = argument_count;
  FRAME *return_arguments = arguments;
  allocate_arguments();
  argument_count = 0;
  arguments = node_p;
  optional_item(((CELL *)frame->slots[0])->contents /* self */);
  for (i = 0; i < n; ++i) {
    arguments->slots[argument_count++] = return_arguments->slots[i];
  }
  func = continuation_type_function;
}
EXPORT void collect__basic__types__string(void) {
  var.std__string = collect_node(var.std__string);
  var.std__pad_left = collect_node(var.std__pad_left);
  var.std__pad_right = collect_node(var.std__pad_right);
  var.std__truncate = collect_node(var.std__truncate);
  var.std__pad_or_truncate = collect_node(var.std__pad_or_truncate);
  var.std__trim = collect_node(var.std__trim);
  var.std__normalize = collect_node(var.std__normalize);
  var.std__split = collect_node(var.std__split);
  var.std__join = collect_node(var.std__join);
  var.std__count_occurrences = collect_node(var.std__count_occurrences);
  var._umlaut_conversions = collect_node(var._umlaut_conversions);
  var.std__replace_umlauts = collect_node(var.std__replace_umlauts);
  var.std__replace_all = collect_node(var.std__replace_all);
  var.std__delete_all = collect_node(var.std__delete_all);
  var._eighty_spaces = collect_node(var._eighty_spaces);
  var.std__spaces = collect_node(var.std__spaces);
  var.std__indented = collect_node(var.std__indented);
  var.std__for_each_line = collect_node(var.std__for_each_line);
  var.std__collect_output = collect_node(var.std__collect_output);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__string(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__string(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__string");
  character__506 = from_uchar32(506);
  character__343 = from_uchar32(343);
  character__338 = from_uchar32(338);
  character__311 = from_uchar32(311);
  character__287 = from_uchar32(287);
  character__270 = from_uchar32(270);
  character__224 = from_uchar32(224);
  character__9 = from_uchar32(9);
  character__455 = from_uchar32(455);
  character__348 = from_uchar32(348);
  character__333 = from_uchar32(333);
  character__301 = from_uchar32(301);
  character__256 = from_uchar32(256);
  character__234 = from_uchar32(234);
  character__486 = from_uchar32(486);
  character__484 = from_uchar32(484);
  character__475 = from_uchar32(475);
  character__467 = from_uchar32(467);
  character__358 = from_uchar32(358);
  character__331 = from_uchar32(331);
  character__323 = from_uchar32(323);
  character__244 = from_uchar32(244);
  character__236 = from_uchar32(236);
  character__188 = from_uchar32(188);
  character__179 = from_uchar32(179);
  character__504 = from_uchar32(504);
  character__465 = from_uchar32(465);
  character__389 = from_uchar32(389);
  character__368 = from_uchar32(368);
  character__321 = from_uchar32(321);
  character__313 = from_uchar32(313);
  character__246 = from_uchar32(246);
  character__198 = from_uchar32(198);
  character__169 = from_uchar32(169);
  character__471 = from_uchar32(471);
  character__382 = from_uchar32(382);
  character__354 = from_uchar32(354);
  character__327 = from_uchar32(327);
  character__303 = from_uchar32(303);
  character__295 = from_uchar32(295);
  character__216 = from_uchar32(216);
  character__208 = from_uchar32(208);
  character__184 = from_uchar32(184);
  character__461 = from_uchar32(461);
  character__400 = from_uchar32(400);
  character__392 = from_uchar32(392);
  character__378 = from_uchar32(378);
  character__364 = from_uchar32(364);
  character__317 = from_uchar32(317);
  character__293 = from_uchar32(293);
  character__285 = from_uchar32(285);
  character__279 = from_uchar32(279);
  character__226 = from_uchar32(226);
  character__218 = from_uchar32(218);
  character__194 = from_uchar32(194);
  character__172 = from_uchar32(172);
  number__80 = from_uint32(80U);
  character__57 = from_uchar32(57);
  character__402 = from_uchar32(402);
  character__366 = from_uchar32(366);
  character__315 = from_uchar32(315);
  character__307 = from_uchar32(307);
  character__291 = from_uchar32(291);
  character__283 = from_uchar32(283);
  character__228 = from_uchar32(228);
  character__204 = from_uchar32(204);
  character__196 = from_uchar32(196);
  character__160 = from_uchar32(160);
  character__473 = from_uchar32(473);
  character__380 = from_uchar32(380);
  character__376 = from_uchar32(376);
  character__374 = from_uchar32(374);
  character__305 = from_uchar32(305);
  character__297 = from_uchar32(297);
  character__281 = from_uchar32(281);
  character__238 = from_uchar32(238);
  character__214 = from_uchar32(214);
  character__206 = from_uchar32(206);
  character__162 = from_uchar32(162);
  character__509 = from_uchar32(509);
  character__482 = from_uchar32(482);
  character__468 = from_uchar32(468);
  character__463 = from_uchar32(463);
  character__387 = from_uchar32(387);
  character__335 = from_uchar32(335);
  character__259 = from_uchar32(259);
  character__232 = from_uchar32(232);
  character__170 = from_uchar32(170);
  character__167 = from_uchar32(167);
  character__63 = from_uchar32(63);
  character__499 = from_uchar32(499);
  character__478 = from_uchar32(478);
  character__371 = from_uchar32(371);
  character__325 = from_uchar32(325);
  character__324 = from_uchar32(324);
  character__249 = from_uchar32(249);
  character__242 = from_uchar32(242);
  character__211 = from_uchar32(211);
  character__166 = from_uchar32(166);
  character__10 = from_uchar32(10);
  character__45 = from_uchar32(45);
  character__481 = from_uchar32(481);
  character__453 = from_uchar32(453);
  character__334 = from_uchar32(334);
  character__288 = from_uchar32(288);
  character__231 = from_uchar32(231);
  character__212 = from_uchar32(212);
  character__185 = from_uchar32(185);
  number__0 = from_uint32(0U);
  character__345 = from_uchar32(345);
  character__344 = from_uchar32(344);
  character__298 = from_uchar32(298);
  character__269 = from_uchar32(269);
  character__222 = from_uchar32(222);
  character__221 = from_uchar32(221);
  character__13 = from_uchar32(13);
  character__460 = from_uchar32(460);
  character__457 = from_uchar32(457);
  character__365 = from_uchar32(365);
  character__308 = from_uchar32(308);
  character__284 = from_uchar32(284);
  character__262 = from_uchar32(262);
  character__205 = from_uchar32(205);
  character__181 = from_uchar32(181);
  character__470 = from_uchar32(470);
  character__393 = from_uchar32(393);
  character__379 = from_uchar32(379);
  character__355 = from_uchar32(355);
  character__341 = from_uchar32(341);
  character__318 = from_uchar32(318);
  character__294 = from_uchar32(294);
  character__272 = from_uchar32(272);
  character__219 = from_uchar32(219);
  character__195 = from_uchar32(195);
  character__173 = from_uchar32(173);
  character__492 = from_uchar32(492);
  character__489 = from_uchar32(489);
  character__383 = from_uchar32(383);
  character__361 = from_uchar32(361);
  character__304 = from_uchar32(304);
  character__280 = from_uchar32(280);
  character__266 = from_uchar32(266);
  character__239 = from_uchar32(239);
  character__201 = from_uchar32(201);
  character__163 = from_uchar32(163);
  number__0x80 = from_uint32(128U);
  character__397 = from_uchar32(397);
  character__375 = from_uchar32(375);
  character__351 = from_uchar32(351);
  character__328 = from_uchar32(328);
  character__314 = from_uchar32(314);
  character__290 = from_uchar32(290);
  character__276 = from_uchar32(276);
  character__252 = from_uchar32(252);
  character__229 = from_uchar32(229);
  character__215 = from_uchar32(215);
  character__191 = from_uchar32(191);
  character__177 = from_uchar32(177);
  character__485 = from_uchar32(485);
  character__476 = from_uchar32(476);
  character__403 = from_uchar32(403);
  character__322 = from_uchar32(322);
  character__300 = from_uchar32(300);
  character__267 = from_uchar32(267);
  character__235 = from_uchar32(235);
  character__189 = from_uchar32(189);
  character__507 = from_uchar32(507);
  character__454 = from_uchar32(454);
  character__349 = from_uchar32(349);
  character__332 = from_uchar32(332);
  character__310 = from_uchar32(310);
  character__286 = from_uchar32(286);
  character__271 = from_uchar32(271);
  character__257 = from_uchar32(257);
  character__225 = from_uchar32(225);
  character__505 = from_uchar32(505);
  character__497 = from_uchar32(497);
  character__464 = from_uchar32(464);
  character__456 = from_uchar32(456);
  character__369 = from_uchar32(369);
  character__312 = from_uchar32(312);
  character__255 = from_uchar32(255);
  character__247 = from_uchar32(247);
  character__209 = from_uchar32(209);
  character__168 = from_uchar32(168);
  character__487 = from_uchar32(487);
  character__474 = from_uchar32(474);
  character__466 = from_uchar32(466);
  character__388 = from_uchar32(388);
  character__359 = from_uchar32(359);
  character__320 = from_uchar32(320);
  character__245 = from_uchar32(245);
  character__237 = from_uchar32(237);
  character__199 = from_uchar32(199);
  character__501 = from_uchar32(501);
  character__362 = from_uchar32(362);
  character__330 = from_uchar32(330);
  character__319 = from_uchar32(319);
  character__273 = from_uchar32(273);
  character__251 = from_uchar32(251);
  character__192 = from_uchar32(192);
  character__178 = from_uchar32(178);
  character__164 = from_uchar32(164);
  character__32 = from_uchar32(32);
  character__491 = from_uchar32(491);
  character__384 = from_uchar32(384);
  character__372 = from_uchar32(372);
  character__340 = from_uchar32(340);
  character__309 = from_uchar32(309);
  character__265 = from_uchar32(265);
  character__241 = from_uchar32(241);
  character__202 = from_uchar32(202);
  character__394 = from_uchar32(394);
  character__386 = from_uchar32(386);
  character__350 = from_uchar32(350);
  character__342 = from_uchar32(342);
  character__339 = from_uchar32(339);
  character__277 = from_uchar32(277);
  character__263 = from_uchar32(263);
  character__180 = from_uchar32(180);
  character__174 = from_uchar32(174);
  character__511 = from_uchar32(511);
  character__458 = from_uchar32(458);
  character__396 = from_uchar32(396);
  character__360 = from_uchar32(360);
  character__352 = from_uchar32(352);
  character__329 = from_uchar32(329);
  character__275 = from_uchar32(275);
  character__261 = from_uchar32(261);
  character__253 = from_uchar32(253);
  character__190 = from_uchar32(190);
  character__182 = from_uchar32(182);
  character__176 = from_uchar32(176);
  character__493 = from_uchar32(493);
  character__488 = from_uchar32(488);
  character__479 = from_uchar32(479);
  character__452 = from_uchar32(452);
  character__370 = from_uchar32(370);
  character__357 = from_uchar32(357);
  character__346 = from_uchar32(346);
  character__243 = from_uchar32(243);
  character__200 = from_uchar32(200);
  character__197 = from_uchar32(197);
  number__1 = from_uint32(1U);
  character__498 = from_uchar32(498);
  character__483 = from_uchar32(483);
  character__469 = from_uchar32(469);
  character__462 = from_uchar32(462);
  character__356 = from_uchar32(356);
  character__248 = from_uchar32(248);
  character__233 = from_uchar32(233);
  character__210 = from_uchar32(210);
  character__187 = from_uchar32(187);
  character__186 = from_uchar32(186);
  character__508 = from_uchar32(508);
  character__347 = from_uchar32(347);
  character__326 = from_uchar32(326);
  character__299 = from_uchar32(299);
  character__258 = from_uchar32(258);
  character__223 = from_uchar32(223);
  character__220 = from_uchar32(220);
  character__49 = from_uchar32(49);
  character__46 = from_uchar32(46);
  character__480 = from_uchar32(480);
  character__337 = from_uchar32(337);
  character__336 = from_uchar32(336);
  character__289 = from_uchar32(289);
  character__268 = from_uchar32(268);
  character__230 = from_uchar32(230);
  number__2 = from_uint32(2U);
  character__395 = from_uchar32(395);
  character__373 = from_uchar32(373);
  character__316 = from_uchar32(316);
  character__292 = from_uchar32(292);
  character__278 = from_uchar32(278);
  character__254 = from_uchar32(254);
  character__240 = from_uchar32(240);
  character__227 = from_uchar32(227);
  character__213 = from_uchar32(213);
  character__175 = from_uchar32(175);
  character__500 = from_uchar32(500);
  character__490 = from_uchar32(490);
  character__401 = from_uchar32(401);
  character__385 = from_uchar32(385);
  character__363 = from_uchar32(363);
  character__302 = from_uchar32(302);
  character__264 = from_uchar32(264);
  character__203 = from_uchar32(203);
  character__165 = from_uchar32(165);
  character__472 = from_uchar32(472);
  character__459 = from_uchar32(459);
  character__391 = from_uchar32(391);
  character__377 = from_uchar32(377);
  character__353 = from_uchar32(353);
  character__296 = from_uchar32(296);
  character__274 = from_uchar32(274);
  character__250 = from_uchar32(250);
  character__217 = from_uchar32(217);
  character__193 = from_uchar32(193);
  character__171 = from_uchar32(171);
  character__128 = from_uchar32(128);
  character__510 = from_uchar32(510);
  character__381 = from_uchar32(381);
  character__367 = from_uchar32(367);
  character__306 = from_uchar32(306);
  character__282 = from_uchar32(282);
  character__260 = from_uchar32(260);
  character__207 = from_uchar32(207);
  character__183 = from_uchar32(183);
  character__161 = from_uchar32(161);
  func__types__string__to_integer_1 = create_function(entry__types__string__to_integer_1, 1);
  func__types__string__to_real_1 = create_function(entry__types__string__to_real_1, 1);
  func__types__string__parse_number_1 = create_function(entry__types__string__parse_number_1, 1);
  func__types__string__to_number_1 = create_function(entry__types__string__to_number_1, 1);
  func__types__string__put_1 = create_function(entry__types__string__put_1, 2);
  func__types__string__write_to_1 = create_function(entry__types__string__write_to_1, -1);
  func__types__string__numerically_less_1 = create_function(entry__types__string__numerically_less_1, 2);
  func__types__string__to_list_1 = create_function(entry__types__string__to_list_1, 1);
  func__std__string_1 = create_function(entry__std__string_1, -1);
  string__963fa2c6021831d1 = from_latin_1_string("Negative argument for dup!", 26);
  func__types__string__dup_6 = create_function(entry__types__string__dup_6, 0);
  func__types__string__dup_1 = create_function(entry__types__string__dup_1, 2);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  func__std__pad_left_1 = create_function(entry__std__pad_left_1, -1);
  func__std__pad_right_1 = create_function(entry__std__pad_right_1, -1);
  func__std__truncate_1 = create_function(entry__std__truncate_1, 2);
  func__std__pad_or_truncate_1 = create_function(entry__std__pad_or_truncate_1, 2);
  func__types__string__match_character_8 = create_function(entry__types__string__match_character_8, 0);
  func__types__string__match_character_9 = create_function(entry__types__string__match_character_9, 0);
  func__types__string__match_character_1 = create_function(entry__types__string__match_character_1, 2);
  func__types__string__grammar__match_1 = create_function(entry__types__string__grammar__match_1, 2);
  func__types__string__match_1 = create_function(entry__types__string__match_1, 2);
  func__types__string__search_character_13 = create_function(entry__types__string__search_character_13, 0);
  func__types__string__search_character_1 = create_function(entry__types__string__search_character_1, -1);
  func__types__string__search_1 = create_function(entry__types__string__search_1, 2);
  func__types__string__before_1 = create_function(entry__types__string__before_1, -1);
  func__types__string__truncate_from_1 = create_function(entry__types__string__truncate_from_1, -1);
  func__types__string__behind_1 = create_function(entry__types__string__behind_1, -1);
  func__types__string__truncate_until_1 = create_function(entry__types__string__truncate_until_1, -1);
  func__types__string__from_1 = create_function(entry__types__string__from_1, -1);
  func__types__string__truncate_before_1 = create_function(entry__types__string__truncate_before_1, -1);
  func__types__string__until_1 = create_function(entry__types__string__until_1, -1);
  func__types__string__truncate_behind_1 = create_function(entry__types__string__truncate_behind_1, -1);
  func__types__string__between_1 = create_function(entry__types__string__between_1, -1);
  func__types__string__has_prefix_1 = create_function(entry__types__string__has_prefix_1, 2);
  func__types__string__has_suffix_1 = create_function(entry__types__string__has_suffix_1, 2);
  func__types__string__without_prefix_1 = create_function(entry__types__string__without_prefix_1, 2);
  func__types__string__without_suffix_1 = create_function(entry__types__string__without_suffix_1, 2);
  func__std__trim_1 = create_function(entry__std__trim_1, 1);
  func__std__normalize_1 = create_function(entry__std__normalize_1, 1);
  func__std__split_1 = create_function(entry__std__split_1, -1);
  func__std__join_1 = create_function(entry__std__join_1, -1);
  func__std__count_occurrences_1 = create_function(entry__std__count_occurrences_1, 2);
  func__types__string__matches_1 = create_function(entry__types__string__matches_1, 2);
  func__types__string__contains_1 = create_function(entry__types__string__contains_1, 2);
  func__std__replace_umlauts_1 = create_function(entry__std__replace_umlauts_1, 1);
  func__std__replace_all_1 = create_function(entry__std__replace_all_1, -1);
  func__std__delete_all_1 = create_function(entry__std__delete_all_1, -1);
  string__49792677fe126f62 = from_latin_1_string("                                                                                ", 80);
  func__std__spaces_1 = create_function(entry__std__spaces_1, 1);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  func__std__indented_1 = create_function(entry__std__indented_1, 2);
  func__std__for_each_line_1 = create_function(entry__std__for_each_line_1, -1);
  func__types__string__to_lower_case_1 = create_function(entry__types__string__to_lower_case_1, 1);
  func__types__string__to_upper_case_1 = create_function(entry__types__string__to_upper_case_1, 1);
  func__types__string__to_title_case_1 = create_function(entry__types__string__to_title_case_1, 1);
  func__types__octet_string__new_empty_collection_1 = create_function(entry__types__octet_string__new_empty_collection_1, 1);
  func__types__quad_octet_string__new_empty_collection_1 = create_function(entry__types__quad_octet_string__new_empty_collection_1, 1);
  func__std__collect_output_1 = create_function(entry__std__collect_output_1, -1);
  string__578a5af303e9cc0 = from_latin_1_string("!", 1);
  string__521f55e4811a62fe = from_latin_1_string("(cent)", 6);
  string__99240e5a959a30d3 = from_latin_1_string("(pound)", 7);
  string__578a5af303e9cde = from_latin_1_string("?", 1);
  string__785aea43eabc907e = from_latin_1_string("(yen)", 5);
  string__578a5af303e9c9d = from_latin_1_string("|", 1);
  string__578a5af303e9cc5 = from_latin_1_string("$", 1);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__fa732415d316be5 = from_latin_1_string("(c)", 3);
  string__578a5af303e9c80 = from_latin_1_string("a", 1);
  string__2d7981f4e6e82bf9 = from_latin_1_string("<<", 2);
  string__565ae8c3ea6c907e = from_latin_1_string("(not)", 5);
  string__6c5ae903ea04907e = from_latin_1_string("(shy)", 5);
  string__fa732415db96be5 = from_latin_1_string("(r)", 3);
  string__578a5af303e9c9f = from_latin_1_string("~", 1);
  string__7c1f5624819a22fe = from_latin_1_string("(grad)", 6);
  string__fa732815f516be1 = from_latin_1_string("+/-", 3);
  string__2d7981f4e5f82bf7 = from_latin_1_string("^2", 2);
  string__2d7981f4e5f82bf6 = from_latin_1_string("^3", 2);
  string__578a5af303e9cc6 = from_latin_1_string("'", 1);
  string__920aea0b5dc87d10 = from_latin_1_string("(mu)", 4);
  string__6a5aeb43ea5c907e = from_latin_1_string("(par)", 5);
  string__578a5af303e9ccf = from_latin_1_string(".", 1);
  string__578a5af303e9ccd = from_latin_1_string(",", 1);
  string__2d7981f4e5f82bf4 = from_latin_1_string("^1", 2);
  string__578a5af303e9c8e = from_latin_1_string("o", 1);
  string__2d7981f4e6f82bfb = from_latin_1_string(">>", 2);
  string__fa734015f516bf8 = from_latin_1_string("1/4", 3);
  string__fa734015f516bfe = from_latin_1_string("1/2", 3);
  string__fa734815f516bf8 = from_latin_1_string("3/4", 3);
  string__578a5af303e9ca0 = from_latin_1_string("A", 1);
  string__2d7981f4e5002ba0 = from_latin_1_string("Ae", 2);
  string__2d7981f4e5002b80 = from_latin_1_string("AE", 2);
  string__578a5af303e9ca2 = from_latin_1_string("C", 1);
  string__578a5af303e9ca4 = from_latin_1_string("E", 1);
  string__578a5af303e9ca8 = from_latin_1_string("I", 1);
  string__578a5af303e9ca5 = from_latin_1_string("D", 1);
  string__578a5af303e9caf = from_latin_1_string("N", 1);
  string__578a5af303e9cae = from_latin_1_string("O", 1);
  string__2d7981f4e5702ba0 = from_latin_1_string("Oe", 2);
  string__578a5af303e9c99 = from_latin_1_string("x", 1);
  string__578a5af303e9cd1 = from_latin_1_string("0", 1);
  string__578a5af303e9cb4 = from_latin_1_string("U", 1);
  string__2d7981f4e5a02ba0 = from_latin_1_string("Ue", 2);
  string__578a5af303e9cb8 = from_latin_1_string("Y", 1);
  string__578a5af303e9c91 = from_latin_1_string("p", 1);
  string__2d7981f4e4902bb6 = from_latin_1_string("ss", 2);
  string__2d7981f4e4002ba0 = from_latin_1_string("ae", 2);
  string__578a5af303e9c82 = from_latin_1_string("c", 1);
  string__578a5af303e9c84 = from_latin_1_string("e", 1);
  string__578a5af303e9c88 = from_latin_1_string("i", 1);
  string__578a5af303e9c85 = from_latin_1_string("d", 1);
  string__578a5af303e9c8f = from_latin_1_string("n", 1);
  string__2d7981f4e4702ba0 = from_latin_1_string("oe", 2);
  string__578a5af303e9cce = from_latin_1_string("/", 1);
  string__578a5af303e9c94 = from_latin_1_string("u", 1);
  string__2d7981f4e4a02ba0 = from_latin_1_string("ue", 2);
  string__578a5af303e9c98 = from_latin_1_string("y", 1);
  string__578a5af303e9ca6 = from_latin_1_string("G", 1);
  string__578a5af303e9c86 = from_latin_1_string("g", 1);
  string__578a5af303e9ca9 = from_latin_1_string("H", 1);
  string__578a5af303e9c89 = from_latin_1_string("h", 1);
  string__2d7981f4e5402b8f = from_latin_1_string("IJ", 2);
  string__2d7981f4e4402baf = from_latin_1_string("ij", 2);
  string__578a5af303e9cab = from_latin_1_string("J", 1);
  string__578a5af303e9c8b = from_latin_1_string("j", 1);
  string__578a5af303e9caa = from_latin_1_string("K", 1);
  string__578a5af303e9c8a = from_latin_1_string("k", 1);
  string__578a5af303e9cad = from_latin_1_string("L", 1);
  string__578a5af303e9c8d = from_latin_1_string("l", 1);
  string__2d7981f4e5702b80 = from_latin_1_string("OE", 2);
  string__578a5af303e9cb3 = from_latin_1_string("R", 1);
  string__578a5af303e9c93 = from_latin_1_string("r", 1);
  string__578a5af303e9cb2 = from_latin_1_string("S", 1);
  string__578a5af303e9c92 = from_latin_1_string("s", 1);
  string__578a5af303e9cb5 = from_latin_1_string("T", 1);
  string__578a5af303e9c95 = from_latin_1_string("t", 1);
  string__578a5af303e9cb6 = from_latin_1_string("W", 1);
  string__578a5af303e9c96 = from_latin_1_string("w", 1);
  string__578a5af303e9cbb = from_latin_1_string("Z", 1);
  string__578a5af303e9c9b = from_latin_1_string("z", 1);
  string__578a5af303e9c83 = from_latin_1_string("b", 1);
  string__578a5af303e9ca3 = from_latin_1_string("B", 1);
  string__578a5af303e9ca7 = from_latin_1_string("F", 1);
  string__578a5af303e9c87 = from_latin_1_string("f", 1);
  string__2d7981f4e5282b9f = from_latin_1_string("DZ", 2);
  string__2d7981f4e5282bbf = from_latin_1_string("Dz", 2);
  string__2d7981f4e4282bbf = from_latin_1_string("dz", 2);
  string__2d7981f4e5682b8f = from_latin_1_string("LJ", 2);
  string__2d7981f4e5682baf = from_latin_1_string("Lj", 2);
  string__2d7981f4e4682baf = from_latin_1_string("lj", 2);
  string__2d7981f4e5782b8f = from_latin_1_string("NJ", 2);
  string__2d7981f4e5782baf = from_latin_1_string("Nj", 2);
  string__2d7981f4e4782baf = from_latin_1_string("nj", 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__string(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__string");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "string", get__std__string, &var.std__string);
  define_single_assign_static("std", "pad_left", get__std__pad_left, &var.std__pad_left);
  define_single_assign_static("std", "pad_right", get__std__pad_right, &var.std__pad_right);
  define_single_assign_static("std", "truncate", get__std__truncate, &var.std__truncate);
  define_single_assign_static("std", "pad_or_truncate", get__std__pad_or_truncate, &var.std__pad_or_truncate);
  define_single_assign_static("std", "trim", get__std__trim, &var.std__trim);
  define_single_assign_static("std", "normalize", get__std__normalize, &var.std__normalize);
  define_single_assign_static("std", "split", get__std__split, &var.std__split);
  define_single_assign_static("std", "join", get__std__join, &var.std__join);
  define_single_assign_static("std", "count_occurrences", get__std__count_occurrences, &var.std__count_occurrences);
  var._umlaut_conversions = create_future();
  define_single_assign_static("std", "replace_umlauts", get__std__replace_umlauts, &var.std__replace_umlauts);
  define_single_assign_static("std", "replace_all", get__std__replace_all, &var.std__replace_all);
  define_single_assign_static("std", "delete_all", get__std__delete_all, &var.std__delete_all);
  define_single_assign_static("std", "spaces", get__std__spaces, &var.std__spaces);
  define_single_assign_static("std", "indented", get__std__indented, &var.std__indented);
  define_single_assign_static("std", "for_each_line", get__std__for_each_line, &var.std__for_each_line);
  define_single_assign_static("std", "collect_output", get__std__collect_output, &var.std__collect_output);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__string(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__string");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "END_OF_TEXT", &get__END_OF_TEXT, &get_value_or_future__END_OF_TEXT);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_polymorphic_function(NULL, "before", &get__before, &poly_idx__before);
  use_polymorphic_function(NULL, "behind", &get__behind, &poly_idx__behind);
  use_polymorphic_function(NULL, "between", &get__between, &poly_idx__between);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_polymorphic_function(NULL, "contains", &get__contains, &poly_idx__contains);
  use_read_only(NULL, "div", &get__div, &get_value_or_future__div);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "do_while", &get__do_while, &get_value_or_future__do_while);
  use_polymorphic_function(NULL, "dup", &get__dup, &poly_idx__dup);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "for_each_line", &get__for_each_line, &get_value_or_future__for_each_line);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_polymorphic_function(NULL, "from", &get__from, &poly_idx__from);
  use_read_only(NULL, "from_down_to", &get__from_down_to, &get_value_or_future__from_down_to);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
  use_multi_assign_dynamic("grammar", "current_node", &get__grammar__current_node, &set__grammar__current_node, &define__grammar__current_node);
  use_polymorphic_function("grammar", "match", &get__grammar__match, &poly_idx__grammar__match);
  use_read_only("grammar", "search", &get__grammar__search, &get_value_or_future__grammar__search);
  use_read_only(NULL, "has_minimum_length", &get__has_minimum_length, &get_value_or_future__has_minimum_length);
  use_polymorphic_function(NULL, "has_prefix", &get__has_prefix, &poly_idx__has_prefix);
  use_polymorphic_function(NULL, "has_suffix", &get__has_suffix, &poly_idx__has_suffix);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_a_digit", &get__is_a_digit, &get_value_or_future__is_a_digit);
  use_read_only(NULL, "is_a_letter_character", &get__is_a_letter_character, &get_value_or_future__is_a_letter_character);
  use_read_only(NULL, "is_a_string", &get__is_a_string, &get_value_or_future__is_a_string);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "key_of", &get__key_of, &get_value_or_future__key_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "many", &get__many, &get_value_or_future__many);
  use_read_only(NULL, "map", &get__map, &get_value_or_future__map);
  use_polymorphic_function(NULL, "match", &get__match, &poly_idx__match);
  use_polymorphic_function(NULL, "match_character", &get__match_character, &poly_idx__match_character);
  use_polymorphic_function(NULL, "matches", &get__matches, &poly_idx__matches);
  use_read_only(NULL, "min", &get__min, &get_value_or_future__min);
  use_read_only(NULL, "minus", &get__minus, &get_value_or_future__minus);
  use_polymorphic_function(NULL, "new_empty_collection", &get__new_empty_collection, &poly_idx__new_empty_collection);
  use_read_only(NULL, "not_followed_by", &get__not_followed_by, &get_value_or_future__not_followed_by);
  use_polymorphic_function(NULL, "numerically_less", &get__numerically_less, &poly_idx__numerically_less);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_read_only(NULL, "parse_integer", &get__parse_integer, &get_value_or_future__parse_integer);
  use_polymorphic_function(NULL, "parse_number", &get__parse_number, &poly_idx__parse_number);
  use_read_only(NULL, "parse_real", &get__parse_real, &get_value_or_future__parse_real);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "put", &get__put, &poly_idx__put);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_polymorphic_function(NULL, "search", &get__search, &poly_idx__search);
  use_polymorphic_function(NULL, "search_character", &get__search_character, &poly_idx__search_character);
  use_read_only(NULL, "spaces", &get__spaces, &get_value_or_future__spaces);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "times", &get__std__times, &get_value_or_future__std__times);
  use_single_assign_dynamic("std", "write", &get__std__write, &define__std__write);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "table", &get__table, &get_value_or_future__table);
  use_polymorphic_function(NULL, "to_integer", &get__to_integer, &poly_idx__to_integer);
  use_polymorphic_function(NULL, "to_list", &get__to_list, &poly_idx__to_list);
  use_polymorphic_function(NULL, "to_lower_case", &get__to_lower_case, &poly_idx__to_lower_case);
  use_polymorphic_function(NULL, "to_number", &get__to_number, &poly_idx__to_number);
  use_polymorphic_function(NULL, "to_real", &get__to_real, &poly_idx__to_real);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_polymorphic_function(NULL, "to_title_case", &get__to_title_case, &poly_idx__to_title_case);
  use_polymorphic_function(NULL, "to_upper_case", &get__to_upper_case, &poly_idx__to_upper_case);
  use_read_only(NULL, "trim", &get__trim, &get_value_or_future__trim);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_polymorphic_function(NULL, "truncate_before", &get__truncate_before, &poly_idx__truncate_before);
  use_polymorphic_function(NULL, "truncate_behind", &get__truncate_behind, &poly_idx__truncate_behind);
  use_polymorphic_function(NULL, "truncate_from", &get__truncate_from, &poly_idx__truncate_from);
  use_polymorphic_function(NULL, "truncate_until", &get__truncate_until, &poly_idx__truncate_until);
  use_read_only("types", "grammar_node", &get__types__grammar_node, &get_value_or_future__types__grammar_node);
  use_read_only("types", "octet_string", &get__types__octet_string, &get_value_or_future__types__octet_string);
  use_read_only("types", "quad_octet_string", &get__types__quad_octet_string, &get_value_or_future__types__quad_octet_string);
  use_read_only("types", "string", &get__types__string, &get_value_or_future__types__string);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_polymorphic_function(NULL, "until", &get__until, &poly_idx__until);
  use_read_only(NULL, "value_of", &get__value_of, &get_value_or_future__value_of);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  use_polymorphic_function(NULL, "without_prefix", &get__without_prefix, &poly_idx__without_prefix);
  use_polymorphic_function(NULL, "without_suffix", &get__without_suffix, &poly_idx__without_suffix);
  use_polymorphic_function(NULL, "write_to", &get__write_to, &poly_idx__write_to);
  define_method("types", "string", poly_idx__to_integer, func__types__string__to_integer_1);
  define_method("types", "string", poly_idx__to_real, func__types__string__to_real_1);
  define_method("types", "string", poly_idx__parse_number, func__types__string__parse_number_1);
  define_method("types", "string", poly_idx__to_number, func__types__string__to_number_1);
  define_method("types", "string", poly_idx__put, func__types__string__put_1);
  define_method("types", "string", poly_idx__write_to, func__types__string__write_to_1);
  define_method("types", "string", poly_idx__numerically_less, func__types__string__numerically_less_1);
  define_method("types", "string", poly_idx__to_list, func__types__string__to_list_1);
  define_method("types", "string", poly_idx__dup, func__types__string__dup_1);
  define_method("types", "string", poly_idx__match_character, func__types__string__match_character_1);
  define_method("types", "string", poly_idx__grammar__match, func__types__string__grammar__match_1);
  define_method("types", "string", poly_idx__match, func__types__string__match_1);
  define_method("types", "string", poly_idx__search_character, func__types__string__search_character_1);
  define_method("types", "string", poly_idx__search, func__types__string__search_1);
  define_method("types", "string", poly_idx__before, func__types__string__before_1);
  define_method("types", "string", poly_idx__truncate_from, func__types__string__truncate_from_1);
  define_method("types", "string", poly_idx__behind, func__types__string__behind_1);
  define_method("types", "string", poly_idx__truncate_until, func__types__string__truncate_until_1);
  define_method("types", "string", poly_idx__from, func__types__string__from_1);
  define_method("types", "string", poly_idx__truncate_before, func__types__string__truncate_before_1);
  define_method("types", "string", poly_idx__until, func__types__string__until_1);
  define_method("types", "string", poly_idx__truncate_behind, func__types__string__truncate_behind_1);
  define_method("types", "string", poly_idx__between, func__types__string__between_1);
  define_method("types", "string", poly_idx__has_prefix, func__types__string__has_prefix_1);
  define_method("types", "string", poly_idx__has_suffix, func__types__string__has_suffix_1);
  define_method("types", "string", poly_idx__without_prefix, func__types__string__without_prefix_1);
  define_method("types", "string", poly_idx__without_suffix, func__types__string__without_suffix_1);
  define_method("types", "string", poly_idx__matches, func__types__string__matches_1);
  define_method("types", "string", poly_idx__contains, func__types__string__contains_1);
  define_method("types", "string", poly_idx__to_lower_case, func__types__string__to_lower_case_1);
  define_method("types", "string", poly_idx__to_upper_case, func__types__string__to_upper_case_1);
  define_method("types", "string", poly_idx__to_title_case, func__types__string__to_title_case_1);
  define_method("types", "octet_string", poly_idx__new_empty_collection, func__types__octet_string__new_empty_collection_1);
  define_method("types", "quad_octet_string", poly_idx__new_empty_collection, func__types__quad_octet_string__new_empty_collection_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__string(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__string, &func__std__string_1);
  assign_variable(&var.std__pad_left, &func__std__pad_left_1);
  assign_variable(&var.std__pad_right, &func__std__pad_right_1);
  assign_variable(&var.std__truncate, &func__std__truncate_1);
  assign_variable(&var.std__pad_or_truncate, &func__std__pad_or_truncate_1);
  assign_variable(&var.std__trim, &func__std__trim_1);
  assign_variable(&var.std__normalize, &func__std__normalize_1);
  assign_variable(&var.std__split, &func__std__split_1);
  assign_variable(&var.std__join, &func__std__join_1);
  assign_variable(&var.std__count_occurrences, &func__std__count_occurrences_1);
  assign_variable(&var.std__replace_umlauts, &func__std__replace_umlauts_1);
  assign_variable(&var.std__replace_all, &func__std__replace_all_1);
  assign_variable(&var.std__delete_all, &func__std__delete_all_1);
  assign_value(&var._eighty_spaces, string__49792677fe126f62);
  assign_variable(&var.std__spaces, &func__std__spaces_1);
  assign_variable(&var.std__indented, &func__std__indented_1);
  assign_variable(&var.std__for_each_line, &func__std__for_each_line_1);
  assign_variable(&var.std__collect_output, &func__std__collect_output_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__string(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__string);
}
