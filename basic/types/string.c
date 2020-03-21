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
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
IMPORT NODE *create_function(FUNC func, int par_count);
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
  NODE *std__spaces;
  NODE *std__indented;
  NODE *std__for_each_line;
  NODE *std__collect_output;
  NODE *std__concatenate;
} var;
static const char *var_names[] = {
  "umlaut_conversions",
  "eighty_spaces"
};
static NODE *func__1_1;
static void entry__1_1(void);
static FRAME_INFO frame__1_1 = {3, {"self", "return", "value"}};
static void cont__1_2(void);
static void cont__1_3(void);
static void cont__1_4(void);
static NODE *func__1_5;
static void entry__1_5(void);
static FRAME_INFO frame__1_5 = {1, {"return"}};
static void cont__1_6(void);
static NODE *func__2_1;
static void entry__2_1(void);
static FRAME_INFO frame__2_1 = {3, {"self", "return", "value"}};
static void cont__2_2(void);
static void cont__2_3(void);
static void cont__2_4(void);
static NODE *func__2_5;
static void entry__2_5(void);
static FRAME_INFO frame__2_5 = {1, {"return"}};
static void cont__2_6(void);
static NODE *func__3_1;
static void entry__3_1(void);
static FRAME_INFO frame__3_1 = {3, {"self", "i", "n"}};
static void cont__3_2(void);
static void cont__3_3(void);
static void cont__3_4(void);
static NODE *func__3_5;
static void entry__3_5(void);
static FRAME_INFO frame__3_5 = {1, {"i"}};
static void cont__3_6(void);
static void cont__3_7(void);
static NODE *func__3_8;
static void entry__3_8(void);
static FRAME_INFO frame__3_8 = {3, {"n", "i", "self"}};
static void cont__3_9(void);
static void cont__3_10(void);
static NODE *func__3_11;
static void entry__3_11(void);
static FRAME_INFO frame__3_11 = {2, {"self", "i"}};
static void cont__3_12(void);
static void cont__3_13(void);
static void cont__3_14(void);
static NODE *func__3_15;
static void entry__3_15(void);
static FRAME_INFO frame__3_15 = {1, {"i"}};
static void cont__3_16(void);
static void cont__3_17(void);
static void cont__3_18(void);
static void cont__3_19(void);
static NODE *func__3_20;
static void entry__3_20(void);
static FRAME_INFO frame__3_20 = {2, {"self", "i"}};
static void cont__3_21(void);
static void cont__3_22(void);
static void cont__3_23(void);
static NODE *func__3_24;
static void entry__3_24(void);
static FRAME_INFO frame__3_24 = {1, {"self"}};
static NODE *func__3_25;
static void entry__3_25(void);
static FRAME_INFO frame__3_25 = {1, {"self"}};
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {3, {"self", "return", "value"}};
static void cont__4_2(void);
static void cont__4_3(void);
static void cont__4_4(void);
static NODE *func__4_5;
static void entry__4_5(void);
static FRAME_INFO frame__4_5 = {1, {"return"}};
static void cont__4_6(void);
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {2, {"self", "chr"}};
static void cont__5_2(void);
static void cont__5_3(void);
static NODE *func__6_1;
static void entry__6_1(void);
static FRAME_INFO frame__6_1 = {2, {"self", "args"}};
static NODE *func__6_2;
static void entry__6_2(void);
static FRAME_INFO frame__6_2 = {2, {"arg", "self"}};
static void cont__6_3(void);
static void cont__6_4(void);
static void cont__6_5(void);
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {5, {"left", "right", "return", "left_len", "right_len"}};
static void cont__7_2(void);
static void cont__7_3(void);
static void cont__7_4(void);
static NODE *func__7_5;
static void entry__7_5(void);
static FRAME_INFO frame__7_5 = {8, {"i", "left", "right", "left_len", "right_len", "return", "left_chr", "right_chr"}};
static void cont__7_6(void);
static void cont__7_7(void);
static void cont__7_8(void);
static void cont__7_9(void);
static NODE *func__7_10;
static void entry__7_10(void);
static FRAME_INFO frame__7_10 = {8, {"left_chr", "right_chr", "i", "left_len", "left", "right_len", "right", "return"}};
static void cont__7_11(void);
static void cont__7_12(void);
static NODE *func__7_13;
static void entry__7_13(void);
static FRAME_INFO frame__7_13 = {2, {"left_chr", "right_chr"}};
static void cont__7_14(void);
static void cont__7_15(void);
static NODE *func__7_16;
static void entry__7_16(void);
static FRAME_INFO frame__7_16 = {1, {"right_chr"}};
static void cont__7_17(void);
static void cont__7_18(void);
static NODE *func__7_19;
static void entry__7_19(void);
static FRAME_INFO frame__7_19 = {1, {"right_chr"}};
static void cont__7_20(void);
static void cont__7_21(void);
static void cont__7_22(void);
static void cont__7_23(void);
static void cont__7_24(void);
static NODE *func__7_25;
static void entry__7_25(void);
static FRAME_INFO frame__7_25 = {9, {"i", "left_len", "left", "right_len", "right", "return", "left_chr", "right_chr", "j"}};
static void cont__7_26(void);
static NODE *func__7_27;
static void entry__7_27(void);
static FRAME_INFO frame__7_27 = {8, {"left_len", "j", "left", "right_len", "right", "return", "left_chr", "right_chr"}};
static void cont__7_28(void);
static void cont__7_29(void);
static NODE *func__7_30;
static void entry__7_30(void);
static FRAME_INFO frame__7_30 = {2, {"left", "j"}};
static void cont__7_31(void);
static void cont__7_32(void);
static void cont__7_33(void);
static NODE *func__7_34;
static void entry__7_34(void);
static FRAME_INFO frame__7_34 = {4, {"right_len", "j", "right", "return"}};
static void cont__7_35(void);
static void cont__7_36(void);
static NODE *func__7_37;
static void entry__7_37(void);
static FRAME_INFO frame__7_37 = {2, {"right", "j"}};
static void cont__7_38(void);
static void cont__7_39(void);
static void cont__7_40(void);
static NODE *func__7_41;
static void entry__7_41(void);
static FRAME_INFO frame__7_41 = {1, {"j"}};
static void cont__7_42(void);
static NODE *func__7_43;
static void entry__7_43(void);
static FRAME_INFO frame__7_43 = {1, {"return"}};
static NODE *func__7_44;
static void entry__7_44(void);
static FRAME_INFO frame__7_44 = {6, {"right_len", "j", "right", "return", "left_chr", "right_chr"}};
static void cont__7_45(void);
static void cont__7_46(void);
static NODE *func__7_47;
static void entry__7_47(void);
static FRAME_INFO frame__7_47 = {2, {"right", "j"}};
static void cont__7_48(void);
static void cont__7_49(void);
static void cont__7_50(void);
static NODE *func__7_51;
static void entry__7_51(void);
static FRAME_INFO frame__7_51 = {1, {"return"}};
static NODE *func__7_52;
static void entry__7_52(void);
static FRAME_INFO frame__7_52 = {3, {"return", "left_chr", "right_chr"}};
static void cont__7_53(void);
static NODE *func__7_54;
static void entry__7_54(void);
static FRAME_INFO frame__7_54 = {3, {"return", "left_chr", "right_chr"}};
static void cont__7_55(void);
static void cont__7_56(void);
static void cont__7_57(void);
static void cont__7_58(void);
static NODE *func__8_1;
static void entry__8_1(void);
static FRAME_INFO frame__8_1 = {2, {"self", "items"}};
static NODE *func__8_2;
static void entry__8_2(void);
static FRAME_INFO frame__8_2 = {2, {"item", "items"}};
static void cont__8_3(void);
static void cont__8_4(void);
static NODE *func__9_1;
static void entry__9_1(void);
static FRAME_INFO frame__9_1 = {3, {"args", "buf", "n"}};
static void cont__9_2(void);
static NODE *func__9_3;
static void entry__9_3(void);
static FRAME_INFO frame__9_3 = {3, {"i", "buf", "args"}};
static void cont__9_4(void);
static void cont__9_5(void);
static void cont__9_6(void);
static void cont__9_7(void);
static NODE *get__std__string(void) {
  return var.std__string;
}
static NODE *func__10_1;
static void entry__10_1(void);
static FRAME_INFO frame__10_1 = {3, {"self", "n", "return"}};
static NODE *func__10_2;
static void entry__10_2(void);
static FRAME_INFO frame__10_2 = {1, {"return"}};
static NODE *func__10_3;
static void entry__10_3(void);
static FRAME_INFO frame__10_3 = {2, {"return", "self"}};
static NODE *func__10_4;
static void entry__10_4(void);
static FRAME_INFO frame__10_4 = {5, {"n", "self", "return", "h", "str"}};
static void cont__10_5(void);
static NODE *func__10_6;
static void entry__10_6(void);
static FRAME_INFO frame__10_6 = {0, {}};
static NODE *string__10_7;
static void cont__10_8(void);
static void cont__10_9(void);
static void cont__10_10(void);
static void cont__10_11(void);
static void cont__10_12(void);
static NODE *func__10_13;
static void entry__10_13(void);
static FRAME_INFO frame__10_13 = {2, {"return", "str"}};
static void cont__10_14(void);
static NODE *func__10_15;
static void entry__10_15(void);
static FRAME_INFO frame__10_15 = {3, {"return", "str", "self"}};
static void cont__10_16(void);
static void cont__10_17(void);
static NODE *func__11_1;
static void entry__11_1(void);
static FRAME_INFO frame__11_1 = {6, {"expr", "n", "pad", "return", "text", "len"}};
static NODE *string__11_2;
static void cont__11_3(void);
static void cont__11_4(void);
static void cont__11_5(void);
static NODE *func__11_6;
static void entry__11_6(void);
static FRAME_INFO frame__11_6 = {6, {"pad", "return", "n", "len", "text", "pad_len"}};
static void cont__11_7(void);
static void cont__11_8(void);
static void cont__11_9(void);
static void cont__11_10(void);
static void cont__11_11(void);
static void cont__11_12(void);
static void cont__11_13(void);
static void cont__11_14(void);
static void cont__11_15(void);
static void cont__11_16(void);
static NODE *get__std__pad_left(void) {
  return var.std__pad_left;
}
static NODE *func__12_1;
static void entry__12_1(void);
static FRAME_INFO frame__12_1 = {6, {"expr", "n", "pad", "return", "text", "len"}};
static NODE *string__12_2;
static void cont__12_3(void);
static void cont__12_4(void);
static void cont__12_5(void);
static NODE *func__12_6;
static void entry__12_6(void);
static FRAME_INFO frame__12_6 = {6, {"pad", "return", "text", "n", "len", "pad_len"}};
static void cont__12_7(void);
static void cont__12_8(void);
static void cont__12_9(void);
static void cont__12_10(void);
static void cont__12_11(void);
static void cont__12_12(void);
static void cont__12_13(void);
static void cont__12_14(void);
static void cont__12_15(void);
static void cont__12_16(void);
static NODE *get__std__pad_right(void) {
  return var.std__pad_right;
}
static NODE *func__13_1;
static void entry__13_1(void);
static FRAME_INFO frame__13_1 = {4, {"expr", "n", "text", "len"}};
static void cont__13_2(void);
static void cont__13_3(void);
static void cont__13_4(void);
static NODE *func__13_5;
static void entry__13_5(void);
static FRAME_INFO frame__13_5 = {1, {"text"}};
static NODE *func__13_6;
static void entry__13_6(void);
static FRAME_INFO frame__13_6 = {2, {"text", "n"}};
static void cont__13_7(void);
static NODE *get__std__truncate(void) {
  return var.std__truncate;
}
static NODE *func__14_1;
static void entry__14_1(void);
static FRAME_INFO frame__14_1 = {4, {"expr", "n", "text", "len"}};
static void cont__14_2(void);
static void cont__14_3(void);
static void cont__14_4(void);
static NODE *func__14_5;
static void entry__14_5(void);
static FRAME_INFO frame__14_5 = {3, {"text", "n", "len"}};
static void cont__14_6(void);
static NODE *string__14_7;
static void cont__14_8(void);
static void cont__14_9(void);
static NODE *func__14_10;
static void entry__14_10(void);
static FRAME_INFO frame__14_10 = {2, {"text", "n"}};
static void cont__14_11(void);
static NODE *get__std__pad_or_truncate(void) {
  return var.std__pad_or_truncate;
}
static NODE *func__15_1;
static void entry__15_1(void);
static FRAME_INFO frame__15_1 = {2, {"self", "chr"}};
static void cont__15_2(void);
static void cont__15_3(void);
static NODE *func__15_4;
static void entry__15_4(void);
static FRAME_INFO frame__15_4 = {2, {"self", "chr"}};
static void cont__15_5(void);
static void cont__15_6(void);
static void cont__15_7(void);
static NODE *func__15_8;
static void entry__15_8(void);
static FRAME_INFO frame__15_8 = {0, {}};
static NODE *func__15_9;
static void entry__15_9(void);
static FRAME_INFO frame__15_9 = {0, {}};
static NODE *func__16_1;
static void entry__16_1(void);
static FRAME_INFO frame__16_1 = {4, {"expr", "stream", "return", "len"}};
static void cont__16_2(void);
static void cont__16_3(void);
static NODE *func__16_4;
static void entry__16_4(void);
static FRAME_INFO frame__16_4 = {1, {"return"}};
static void cont__16_5(void);
static void cont__16_6(void);
static void cont__16_7(void);
static NODE *func__16_8;
static void entry__16_8(void);
static FRAME_INFO frame__16_8 = {2, {"return", "len"}};
static void cont__16_9(void);
static NODE *func__17_1;
static void entry__17_1(void);
static FRAME_INFO frame__17_1 = {4, {"stream", "expr", "return", "n"}};
static void cont__17_2(void);
static void cont__17_3(void);
static void cont__17_4(void);
static NODE *func__17_5;
static void entry__17_5(void);
static FRAME_INFO frame__17_5 = {2, {"return", "n"}};
static void cont__17_6(void);
static NODE *func__18_1;
static void entry__18_1(void);
static FRAME_INFO frame__18_1 = {3, {"self", "chr", "sum"}};
static void cont__18_2(void);
static NODE *func__18_3;
static void entry__18_3(void);
static FRAME_INFO frame__18_3 = {3, {"self", "chr", "sum"}};
static void cont__18_4(void);
static void cont__18_5(void);
static NODE *func__18_6;
static void entry__18_6(void);
static FRAME_INFO frame__18_6 = {1, {"sum"}};
static void cont__18_7(void);
static NODE *func__18_8;
static void entry__18_8(void);
static FRAME_INFO frame__18_8 = {3, {"self", "chr", "sum"}};
static void cont__18_9(void);
static void cont__18_10(void);
static void cont__18_11(void);
static void cont__18_12(void);
static NODE *func__18_13;
static void entry__18_13(void);
static FRAME_INFO frame__18_13 = {0, {}};
static NODE *func__19_1;
static void entry__19_1(void);
static FRAME_INFO frame__19_1 = {5, {"stream", "expr", "return__1", "pos", "len"}};
static void cont__19_2(void);
static NODE *func__20_1;
static void entry__20_1(void);
static FRAME_INFO frame__20_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__20_2(void);
static void cont__20_3(void);
static NODE *func__20_4;
static void entry__20_4(void);
static FRAME_INFO frame__20_4 = {3, {"return", "str", "pos"}};
static void cont__20_5(void);
static void cont__20_6(void);
static NODE *func__20_7;
static void entry__20_7(void);
static FRAME_INFO frame__20_7 = {1, {"return"}};
static void cont__20_8(void);
static NODE *func__21_1;
static void entry__21_1(void);
static FRAME_INFO frame__21_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__21_2(void);
static void cont__21_3(void);
static NODE *func__21_4;
static void entry__21_4(void);
static FRAME_INFO frame__21_4 = {3, {"return", "str", "pos"}};
static void cont__21_5(void);
static void cont__21_6(void);
static NODE *func__21_7;
static void entry__21_7(void);
static FRAME_INFO frame__21_7 = {2, {"return", "str"}};
static void cont__21_8(void);
static NODE *func__22_1;
static void entry__22_1(void);
static FRAME_INFO frame__22_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__22_2(void);
static void cont__22_3(void);
static NODE *func__22_4;
static void entry__22_4(void);
static FRAME_INFO frame__22_4 = {4, {"return", "str", "pos", "len"}};
static void cont__22_5(void);
static void cont__22_6(void);
static void cont__22_7(void);
static NODE *func__22_8;
static void entry__22_8(void);
static FRAME_INFO frame__22_8 = {1, {"return"}};
static void cont__22_9(void);
static NODE *func__23_1;
static void entry__23_1(void);
static FRAME_INFO frame__23_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__23_2(void);
static void cont__23_3(void);
static NODE *func__23_4;
static void entry__23_4(void);
static FRAME_INFO frame__23_4 = {4, {"return", "str", "pos", "len"}};
static void cont__23_5(void);
static void cont__23_6(void);
static void cont__23_7(void);
static NODE *func__23_8;
static void entry__23_8(void);
static FRAME_INFO frame__23_8 = {2, {"return", "str"}};
static void cont__23_9(void);
static NODE *func__24_1;
static void entry__24_1(void);
static FRAME_INFO frame__24_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__24_2(void);
static void cont__24_3(void);
static NODE *func__24_4;
static void entry__24_4(void);
static FRAME_INFO frame__24_4 = {3, {"return", "str", "pos"}};
static void cont__24_5(void);
static void cont__24_6(void);
static NODE *func__24_7;
static void entry__24_7(void);
static FRAME_INFO frame__24_7 = {1, {"return"}};
static void cont__24_8(void);
static NODE *func__25_1;
static void entry__25_1(void);
static FRAME_INFO frame__25_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__25_2(void);
static void cont__25_3(void);
static NODE *func__25_4;
static void entry__25_4(void);
static FRAME_INFO frame__25_4 = {3, {"return", "str", "pos"}};
static void cont__25_5(void);
static void cont__25_6(void);
static NODE *func__25_7;
static void entry__25_7(void);
static FRAME_INFO frame__25_7 = {2, {"return", "str"}};
static void cont__25_8(void);
static NODE *func__26_1;
static void entry__26_1(void);
static FRAME_INFO frame__26_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__26_2(void);
static void cont__26_3(void);
static NODE *func__26_4;
static void entry__26_4(void);
static FRAME_INFO frame__26_4 = {4, {"return", "str", "pos", "len"}};
static void cont__26_5(void);
static void cont__26_6(void);
static void cont__26_7(void);
static NODE *func__26_8;
static void entry__26_8(void);
static FRAME_INFO frame__26_8 = {1, {"return"}};
static void cont__26_9(void);
static NODE *func__27_1;
static void entry__27_1(void);
static FRAME_INFO frame__27_1 = {6, {"str", "expr", "nth", "return", "pos", "len"}};
static void cont__27_2(void);
static void cont__27_3(void);
static NODE *func__27_4;
static void entry__27_4(void);
static FRAME_INFO frame__27_4 = {4, {"return", "str", "pos", "len"}};
static void cont__27_5(void);
static void cont__27_6(void);
static void cont__27_7(void);
static NODE *func__27_8;
static void entry__27_8(void);
static FRAME_INFO frame__27_8 = {2, {"return", "str"}};
static void cont__27_9(void);
static NODE *func__28_1;
static void entry__28_1(void);
static FRAME_INFO frame__28_1 = {4, {"str", "expr_1", "expr_2", "nth"}};
static void cont__28_2(void);
static void cont__28_3(void);
static NODE *func__29_1;
static void entry__29_1(void);
static FRAME_INFO frame__29_1 = {2, {"self", "prefix"}};
static void cont__29_2(void);
static void cont__29_3(void);
static NODE *func__30_1;
static void entry__30_1(void);
static FRAME_INFO frame__30_1 = {4, {"self", "suffix", "return", "len"}};
static void cont__30_2(void);
static NODE *func__30_3;
static void entry__30_3(void);
static FRAME_INFO frame__30_3 = {5, {"i", "self", "suffix", "len", "return"}};
static void cont__30_4(void);
static void cont__30_5(void);
static void cont__30_6(void);
static void cont__30_7(void);
static void cont__30_8(void);
static void cont__30_9(void);
static NODE *func__30_10;
static void entry__30_10(void);
static FRAME_INFO frame__30_10 = {1, {"return"}};
static void cont__30_11(void);
static NODE *func__31_1;
static void entry__31_1(void);
static FRAME_INFO frame__31_1 = {4, {"self", "prefix", "return", "n"}};
static void cont__31_2(void);
static void cont__31_3(void);
static NODE *func__31_4;
static void entry__31_4(void);
static FRAME_INFO frame__31_4 = {3, {"return", "self", "n"}};
static void cont__31_5(void);
static void cont__31_6(void);
static void cont__31_7(void);
static void cont__31_8(void);
static NODE *func__32_1;
static void entry__32_1(void);
static FRAME_INFO frame__32_1 = {4, {"self", "suffix", "return", "len"}};
static void cont__32_2(void);
static NODE *func__32_3;
static void entry__32_3(void);
static FRAME_INFO frame__32_3 = {5, {"i", "self", "suffix", "len", "return"}};
static void cont__32_4(void);
static void cont__32_5(void);
static void cont__32_6(void);
static void cont__32_7(void);
static void cont__32_8(void);
static void cont__32_9(void);
static NODE *func__32_10;
static void entry__32_10(void);
static FRAME_INFO frame__32_10 = {3, {"return", "self", "i"}};
static void cont__32_11(void);
static void cont__32_12(void);
static void cont__32_13(void);
static NODE *func__33_1;
static void entry__33_1(void);
static FRAME_INFO frame__33_1 = {3, {"str", "s", "e"}};
static void cont__33_2(void);
static NODE *func__33_3;
static void entry__33_3(void);
static FRAME_INFO frame__33_3 = {3, {"e", "s", "str"}};
static void cont__33_4(void);
static void cont__33_5(void);
static NODE *func__33_6;
static void entry__33_6(void);
static FRAME_INFO frame__33_6 = {2, {"str", "s"}};
static void cont__33_7(void);
static void cont__33_8(void);
static void cont__33_9(void);
static void cont__33_10(void);
static NODE *func__33_11;
static void entry__33_11(void);
static FRAME_INFO frame__33_11 = {1, {"s"}};
static void cont__33_12(void);
static void cont__33_13(void);
static NODE *func__33_14;
static void entry__33_14(void);
static FRAME_INFO frame__33_14 = {3, {"e", "s", "str"}};
static void cont__33_15(void);
static void cont__33_16(void);
static NODE *func__33_17;
static void entry__33_17(void);
static FRAME_INFO frame__33_17 = {2, {"str", "e"}};
static void cont__33_18(void);
static void cont__33_19(void);
static void cont__33_20(void);
static void cont__33_21(void);
static NODE *func__33_22;
static void entry__33_22(void);
static FRAME_INFO frame__33_22 = {1, {"e"}};
static void cont__33_23(void);
static void cont__33_24(void);
static void cont__33_25(void);
static NODE *get__std__trim(void) {
  return var.std__trim;
}
static NODE *func__34_1;
static void entry__34_1(void);
static FRAME_INFO frame__34_1 = {1, {"str"}};
static void cont__34_2(void);
static void cont__34_3(void);
static void cont__34_4(void);
static NODE *string__34_5;
static void cont__34_6(void);
static void cont__34_7(void);
static NODE *get__std__normalize(void) {
  return var.std__normalize;
}
static NODE *func__35_1;
static void entry__35_1(void);
static FRAME_INFO frame__35_1 = {3, {"text", "separator", "items"}};
static void cont__35_3(void);
static void cont__35_2(void);
static NODE *func__35_4;
static void entry__35_4(void);
static FRAME_INFO frame__35_4 = {5, {"separator", "text", "items", "pos", "len"}};
static void cont__35_5(void);
static void cont__35_6(void);
static NODE *func__35_7;
static void entry__35_7(void);
static FRAME_INFO frame__35_7 = {4, {"items", "text", "pos", "len"}};
static void cont__35_8(void);
static void cont__35_9(void);
static void cont__35_10(void);
static void cont__35_11(void);
static void cont__35_12(void);
static void cont__35_13(void);
static void cont__35_14(void);
static void cont__35_15(void);
static void cont__35_16(void);
static void cont__35_17(void);
static void cont__35_18(void);
static NODE *func__35_19;
static void entry__35_19(void);
static FRAME_INFO frame__35_19 = {2, {"items", "text"}};
static void cont__35_20(void);
static void cont__35_21(void);
static NODE *get__std__split(void) {
  return var.std__split;
}
static NODE *func__36_1;
static void entry__36_1(void);
static FRAME_INFO frame__36_1 = {3, {"words", "separator", "text"}};
static NODE *string__36_2;
static NODE *func__36_3;
static void entry__36_3(void);
static FRAME_INFO frame__36_3 = {2, {"word", "text"}};
static void cont__36_4(void);
static NODE *func__36_5;
static void entry__36_5(void);
static FRAME_INFO frame__36_5 = {2, {"text", "separator"}};
static void cont__36_6(void);
static void cont__36_7(void);
static NODE *get__std__join(void) {
  return var.std__join;
}
static NODE *func__37_1;
static void entry__37_1(void);
static FRAME_INFO frame__37_1 = {3, {"text", "expr", "n"}};
static NODE *func__37_2;
static void entry__37_2(void);
static FRAME_INFO frame__37_2 = {5, {"expr", "text", "n", "pos", "len"}};
static void cont__37_3(void);
static void cont__37_4(void);
static NODE *func__37_5;
static void entry__37_5(void);
static FRAME_INFO frame__37_5 = {4, {"text", "pos", "len", "n"}};
static void cont__37_6(void);
static void cont__37_7(void);
static void cont__37_8(void);
static void cont__37_9(void);
static void cont__37_10(void);
static void cont__37_11(void);
static void cont__37_12(void);
static NODE *get__std__count_occurrences(void) {
  return var.std__count_occurrences;
}
static NODE *func__38_1;
static void entry__38_1(void);
static FRAME_INFO frame__38_1 = {2, {"text", "expr"}};
static void cont__38_2(void);
static void cont__38_3(void);
static void cont__38_4(void);
static NODE *func__39_1;
static void entry__39_1(void);
static FRAME_INFO frame__39_1 = {4, {"text", "expr", "pos", "len"}};
static void cont__39_2(void);
static void cont__39_3(void);
static NODE *func__41_1;
static void entry__41_1(void);
static FRAME_INFO frame__41_1 = {4, {"text", "s", "result", "copy"}};
static NODE *func__41_2;
static void entry__41_2(void);
static FRAME_INFO frame__41_2 = {4, {"idx", "result", "text", "s"}};
static void cont__41_3(void);
static void cont__41_4(void);
static void cont__41_5(void);
static NODE *func__41_6;
static void entry__41_6(void);
static FRAME_INFO frame__41_6 = {4, {"idx", "chr", "copy", "result"}};
static void cont__41_7(void);
static void cont__41_8(void);
static NODE *func__41_9;
static void entry__41_9(void);
static FRAME_INFO frame__41_9 = {4, {"chr", "copy", "idx", "result"}};
static void cont__41_10(void);
static void cont__41_11(void);
static NODE *func__41_12;
static void entry__41_12(void);
static FRAME_INFO frame__41_12 = {5, {"copy", "idx", "chr", "result", "conversion"}};
static void cont__41_13(void);
static void cont__41_14(void);
static void cont__41_15(void);
static void cont__41_16(void);
static NODE *func__41_17;
static void entry__41_17(void);
static FRAME_INFO frame__41_17 = {2, {"result", "conversion"}};
static void cont__41_18(void);
static NODE *func__41_19;
static void entry__41_19(void);
static FRAME_INFO frame__41_19 = {1, {"result"}};
static void cont__41_20(void);
static NODE *func__41_21;
static void entry__41_21(void);
static FRAME_INFO frame__41_21 = {4, {"copy", "idx", "result", "chr"}};
static void cont__41_22(void);
static void cont__41_23(void);
static void cont__41_24(void);
static void cont__41_25(void);
static void cont__41_26(void);
static void cont__41_27(void);
static void cont__41_28(void);
static NODE *get__std__replace_umlauts(void) {
  return var.std__replace_umlauts;
}
static NODE *func__42_1;
static void entry__42_1(void);
static FRAME_INFO frame__42_1 = {3, {"text", "args", "new_text"}};
static NODE *func__42_2;
static void entry__42_2(void);
static FRAME_INFO frame__42_2 = {3, {"text", "args", "new_text"}};
static void cont__42_3(void);
static void cont__42_4(void);
static NODE *func__42_5;
static void entry__42_5(void);
static FRAME_INFO frame__42_5 = {3, {"args", "text", "new_text"}};
static NODE *func__42_6;
static void entry__42_6(void);
static FRAME_INFO frame__42_6 = {4, {"break", "args", "text", "new_text"}};
static NODE *func__42_7;
static void entry__42_7(void);
static FRAME_INFO frame__42_7 = {7, {"arg", "text", "new_text", "break", "expression", "replacement", "len"}};
static void cont__42_8(void);
static void cont__42_9(void);
static void cont__42_10(void);
static void cont__42_11(void);
static NODE *func__42_12;
static void entry__42_12(void);
static FRAME_INFO frame__42_12 = {5, {"replacement", "new_text", "text", "len", "break"}};
static void cont__42_13(void);
static NODE *func__42_14;
static void entry__42_14(void);
static FRAME_INFO frame__42_14 = {2, {"new_text", "replacement"}};
static void cont__42_15(void);
static NODE *func__42_16;
static void entry__42_16(void);
static FRAME_INFO frame__42_16 = {4, {"new_text", "replacement", "text", "len"}};
static void cont__42_17(void);
static void cont__42_18(void);
static void cont__42_19(void);
static void cont__42_20(void);
static void cont__42_21(void);
static void cont__42_22(void);
static void cont__42_23(void);
static void cont__42_24(void);
static void cont__42_25(void);
static void cont__42_26(void);
static void cont__42_27(void);
static void cont__42_28(void);
static void cont__42_29(void);
static NODE *get__std__replace_all(void) {
  return var.std__replace_all;
}
static NODE *string__43_1;
static NODE *func__44_1;
static void entry__44_1(void);
static FRAME_INFO frame__44_1 = {1, {"n"}};
static void cont__44_2(void);
static NODE *func__44_3;
static void entry__44_3(void);
static FRAME_INFO frame__44_3 = {1, {"n"}};
static NODE *string__44_4;
static void cont__44_5(void);
static NODE *func__44_6;
static void entry__44_6(void);
static FRAME_INFO frame__44_6 = {1, {"n"}};
static void cont__44_7(void);
static NODE *get__std__spaces(void) {
  return var.std__spaces;
}
static NODE *func__45_1;
static void entry__45_1(void);
static FRAME_INFO frame__45_1 = {2, {"indent", "text"}};
static void cont__45_2(void);
static NODE *func__45_3;
static void entry__45_3(void);
static FRAME_INFO frame__45_3 = {3, {"indent", "text", "indentation"}};
static void cont__45_4(void);
static void cont__45_5(void);
static void cont__45_6(void);
static void cont__45_7(void);
static NODE *string__45_8;
static void cont__45_9(void);
static void cont__45_10(void);
static void cont__45_11(void);
static void cont__45_12(void);
static void cont__45_13(void);
static NODE *func__45_14;
static void entry__45_14(void);
static FRAME_INFO frame__45_14 = {1, {"text"}};
static void cont__45_15(void);
static void cont__45_16(void);
static void cont__45_17(void);
static NODE *func__45_18;
static void entry__45_18(void);
static FRAME_INFO frame__45_18 = {2, {"text", "indentation"}};
static void cont__45_19(void);
static void cont__45_20(void);
static NODE *get__std__indented(void) {
  return var.std__indented;
}
static NODE *func__46_1;
static void entry__46_1(void);
static FRAME_INFO frame__46_1 = {6, {"text", "body", "body2", "no", "pos", "len"}};
static void cont__46_2(void);
static void cont__46_3(void);
static NODE *func__46_4;
static void entry__46_4(void);
static FRAME_INFO frame__46_4 = {6, {"body", "no", "text", "pos", "body2", "rest"}};
static void cont__46_5(void);
static void cont__46_6(void);
static NODE *func__46_7;
static void entry__46_7(void);
static FRAME_INFO frame__46_7 = {4, {"body", "no", "text", "pos"}};
static void cont__46_8(void);
static void cont__46_9(void);
static NODE *func__46_10;
static void entry__46_10(void);
static FRAME_INFO frame__46_10 = {3, {"body", "text", "pos"}};
static void cont__46_11(void);
static void cont__46_12(void);
static void cont__46_13(void);
static void cont__46_14(void);
static void cont__46_15(void);
static void cont__46_16(void);
static void cont__46_17(void);
static NODE *func__46_18;
static void entry__46_18(void);
static FRAME_INFO frame__46_18 = {1, {"rest"}};
static void cont__46_19(void);
static void cont__46_20(void);
static void cont__46_21(void);
static void cont__46_22(void);
static NODE *func__46_23;
static void entry__46_23(void);
static FRAME_INFO frame__46_23 = {3, {"text", "body", "no"}};
static void cont__46_24(void);
static void cont__46_25(void);
static NODE *func__46_26;
static void entry__46_26(void);
static FRAME_INFO frame__46_26 = {3, {"body", "no", "text"}};
static void cont__46_27(void);
static void cont__46_28(void);
static NODE *func__46_29;
static void entry__46_29(void);
static FRAME_INFO frame__46_29 = {3, {"body", "no", "text"}};
static NODE *func__46_30;
static void entry__46_30(void);
static FRAME_INFO frame__46_30 = {2, {"body", "text"}};
static NODE *get__std__for_each_line(void) {
  return var.std__for_each_line;
}
static NODE *func__47_1;
static void entry__47_1(void);
static FRAME_INFO frame__47_1 = {1, {"text"}};
static void cont__47_2(void);
static NODE *func__48_1;
static void entry__48_1(void);
static FRAME_INFO frame__48_1 = {1, {"text"}};
static void cont__48_2(void);
static NODE *func__49_1;
static void entry__49_1(void);
static FRAME_INFO frame__49_1 = {3, {"text", "out", "to_upper"}};
static NODE *func__49_2;
static void entry__49_2(void);
static FRAME_INFO frame__49_2 = {3, {"chr", "to_upper", "out"}};
static void cont__49_3(void);
static NODE *func__49_4;
static void entry__49_4(void);
static FRAME_INFO frame__49_4 = {3, {"to_upper", "out", "chr"}};
static NODE *func__49_5;
static void entry__49_5(void);
static FRAME_INFO frame__49_5 = {3, {"out", "chr", "to_upper"}};
static void cont__49_6(void);
static void cont__49_7(void);
static NODE *func__49_8;
static void entry__49_8(void);
static FRAME_INFO frame__49_8 = {2, {"out", "chr"}};
static void cont__49_9(void);
static void cont__49_10(void);
static NODE *func__49_11;
static void entry__49_11(void);
static FRAME_INFO frame__49_11 = {3, {"out", "chr", "to_upper"}};
static void cont__49_12(void);
static void cont__49_13(void);
static NODE *func__50_1;
static void entry__50_1(void);
static FRAME_INFO frame__50_1 = {1, {"self"}};
static NODE *func__51_1;
static void entry__51_1(void);
static FRAME_INFO frame__51_1 = {1, {"self"}};
static NODE *func__52_1;
static void entry__52_1(void);
static FRAME_INFO frame__52_1 = {3, {"self", "body", "return__1"}};
static void exit__52_1(void);
static NODE *func__52_2;
static void entry__52_2(void);
static FRAME_INFO frame__52_2 = {2, {"args", "self"}};
static void cont__52_3(void);
static void cont__52_4(void);
static NODE *get__std__collect_output(void) {
  return var.std__collect_output;
}
static NODE *func__53_1;
static void entry__53_1(void);
static FRAME_INFO frame__53_1 = {3, {"strings", "func", "buf"}};
static void cont__53_2(void);
static NODE *func__53_3;
static void entry__53_3(void);
static FRAME_INFO frame__53_3 = {3, {"strings", "buf", "func"}};
static NODE *func__53_4;
static void entry__53_4(void);
static FRAME_INFO frame__53_4 = {3, {"str", "buf", "func"}};
static void cont__53_5(void);
static void cont__53_6(void);
static NODE *func__53_7;
static void entry__53_7(void);
static FRAME_INFO frame__53_7 = {2, {"strings", "buf"}};
static NODE *func__53_8;
static void entry__53_8(void);
static FRAME_INFO frame__53_8 = {2, {"str", "buf"}};
static void cont__53_9(void);
static void cont__53_10(void);
static NODE *get__std__concatenate(void) {
  return var.std__concatenate;
}
static NODE *string__93_1;
static void cont__93_2(void);
static NODE *string__93_3;
static void cont__93_4(void);
static NODE *string__93_5;
static void cont__93_6(void);
static NODE *string__93_7;
static void cont__93_8(void);
static NODE *string__93_9;
static void cont__93_10(void);
static NODE *string__93_11;
static void cont__93_12(void);
static NODE *string__93_13;
static void cont__93_14(void);
static NODE *string__93_15;
static void cont__93_16(void);
static NODE *string__93_17;
static void cont__93_18(void);
static NODE *string__93_19;
static void cont__93_20(void);
static NODE *string__93_21;
static void cont__93_22(void);
static NODE *string__93_23;
static void cont__93_24(void);
static NODE *string__93_25;
static void cont__93_26(void);
static NODE *string__93_27;
static void cont__93_28(void);
static NODE *string__93_29;
static void cont__93_30(void);
static NODE *string__93_31;
static void cont__93_32(void);
static NODE *string__93_33;
static void cont__93_34(void);
static NODE *string__93_35;
static void cont__93_36(void);
static NODE *string__93_37;
static void cont__93_38(void);
static NODE *string__93_39;
static void cont__93_40(void);
static NODE *string__93_41;
static void cont__93_42(void);
static NODE *string__93_43;
static void cont__93_44(void);
static NODE *string__93_45;
static void cont__93_46(void);
static NODE *string__93_47;
static void cont__93_48(void);
static NODE *string__93_49;
static void cont__93_50(void);
static NODE *string__93_51;
static void cont__93_52(void);
static NODE *string__93_53;
static void cont__93_54(void);
static NODE *string__93_55;
static void cont__93_56(void);
static NODE *string__93_57;
static void cont__93_58(void);
static NODE *string__93_59;
static void cont__93_60(void);
static NODE *string__93_61;
static void cont__93_62(void);
static NODE *string__93_63;
static void cont__93_64(void);
static NODE *string__93_65;
static void cont__93_66(void);
static NODE *string__93_67;
static void cont__93_68(void);
static NODE *string__93_69;
static void cont__93_70(void);
static NODE *string__93_71;
static void cont__93_72(void);
static NODE *string__93_73;
static void cont__93_74(void);
static NODE *string__93_75;
static void cont__93_76(void);
static NODE *string__93_77;
static void cont__93_78(void);
static NODE *string__93_79;
static void cont__93_80(void);
static NODE *string__93_81;
static void cont__93_82(void);
static NODE *string__93_83;
static void cont__93_84(void);
static NODE *string__93_85;
static void cont__93_86(void);
static NODE *string__93_87;
static void cont__93_88(void);
static NODE *string__93_89;
static void cont__93_90(void);
static NODE *string__93_91;
static void cont__93_92(void);
static NODE *string__93_93;
static void cont__93_94(void);
static NODE *string__93_95;
static void cont__93_96(void);
static NODE *string__93_97;
static void cont__93_98(void);
static NODE *string__93_99;
static void cont__93_100(void);
static NODE *string__93_101;
static void cont__93_102(void);
static NODE *string__93_103;
static void cont__93_104(void);
static NODE *string__93_105;
static void cont__93_106(void);
static NODE *string__93_107;
static void cont__93_108(void);
static NODE *string__93_109;
static void cont__93_110(void);
static NODE *string__93_111;
static void cont__93_112(void);
static NODE *string__93_113;
static void cont__93_114(void);
static NODE *string__93_115;
static void cont__93_116(void);
static NODE *string__93_117;
static void cont__93_118(void);
static NODE *string__93_119;
static void cont__93_120(void);
static NODE *string__93_121;
static void cont__93_122(void);
static NODE *string__93_123;
static void cont__93_124(void);
static NODE *string__93_125;
static void cont__93_126(void);
static NODE *string__93_127;
static void cont__93_128(void);
static NODE *string__93_129;
static void cont__93_130(void);
static NODE *string__93_131;
static void cont__93_132(void);
static NODE *string__93_133;
static void cont__93_134(void);
static NODE *string__93_135;
static void cont__93_136(void);
static NODE *string__93_137;
static void cont__93_138(void);
static NODE *string__93_139;
static void cont__93_140(void);
static NODE *string__93_141;
static void cont__93_142(void);
static NODE *string__93_143;
static void cont__93_144(void);
static NODE *string__93_145;
static void cont__93_146(void);
static NODE *string__93_147;
static void cont__93_148(void);
static NODE *string__93_149;
static void cont__93_150(void);
static NODE *string__93_151;
static void cont__93_152(void);
static NODE *string__93_153;
static void cont__93_154(void);
static NODE *string__93_155;
static void cont__93_156(void);
static NODE *string__93_157;
static void cont__93_158(void);
static NODE *string__93_159;
static void cont__93_160(void);
static NODE *string__93_161;
static void cont__93_162(void);
static NODE *string__93_163;
static void cont__93_164(void);
static NODE *string__93_165;
static void cont__93_166(void);
static NODE *string__93_167;
static void cont__93_168(void);
static NODE *string__93_169;
static void cont__93_170(void);
static NODE *string__93_171;
static void cont__93_172(void);
static NODE *string__93_173;
static void cont__93_174(void);
static NODE *string__93_175;
static void cont__93_176(void);
static NODE *string__93_177;
static void cont__93_178(void);
static NODE *string__93_179;
static void cont__93_180(void);
static NODE *string__93_181;
static void cont__93_182(void);
static NODE *string__93_183;
static void cont__93_184(void);
static NODE *string__93_185;
static void cont__93_186(void);
static NODE *string__93_187;
static void cont__93_188(void);
static NODE *string__93_189;
static void cont__93_190(void);
static NODE *string__93_191;
static void cont__93_192(void);
static NODE *string__93_193;
static void cont__93_194(void);
static NODE *string__93_195;
static void cont__93_196(void);
static NODE *string__93_197;
static void cont__93_198(void);
static NODE *string__93_199;
static void cont__93_200(void);
static NODE *string__93_201;
static void cont__93_202(void);
static NODE *string__93_203;
static void cont__93_204(void);
static NODE *string__93_205;
static void cont__93_206(void);
static NODE *string__93_207;
static void cont__93_208(void);
static NODE *string__93_209;
static void cont__93_210(void);
static NODE *string__93_211;
static void cont__93_212(void);
static NODE *string__93_213;
static void cont__93_214(void);
static NODE *string__93_215;
static void cont__93_216(void);
static NODE *string__93_217;
static void cont__93_218(void);
static NODE *string__93_219;
static void cont__93_220(void);
static NODE *string__93_221;
static void cont__93_222(void);
static NODE *string__93_223;
static void cont__93_224(void);
static NODE *string__93_225;
static void cont__93_226(void);
static NODE *string__93_227;
static void cont__93_228(void);
static NODE *string__93_229;
static void cont__93_230(void);
static NODE *string__93_231;
static void cont__93_232(void);
static NODE *string__93_233;
static void cont__93_234(void);
static NODE *string__93_235;
static void cont__93_236(void);
static NODE *string__93_237;
static void cont__93_238(void);
static NODE *string__93_239;
static void cont__93_240(void);
static NODE *string__93_241;
static void cont__93_242(void);
static NODE *string__93_243;
static void cont__93_244(void);
static NODE *string__93_245;
static void cont__93_246(void);
static NODE *string__93_247;
static void cont__93_248(void);
static NODE *string__93_249;
static void cont__93_250(void);
static NODE *string__93_251;
static void cont__93_252(void);
static NODE *string__93_253;
static void cont__93_254(void);
static NODE *string__93_255;
static void cont__93_256(void);
static NODE *string__93_257;
static void cont__93_258(void);
static NODE *string__93_259;
static void cont__93_260(void);
static NODE *string__93_261;
static void cont__93_262(void);
static NODE *string__93_263;
static void cont__93_264(void);
static NODE *string__93_265;
static void cont__93_266(void);
static NODE *string__93_267;
static void cont__93_268(void);
static NODE *string__93_269;
static void cont__93_270(void);
static NODE *string__93_271;
static void cont__93_272(void);
static NODE *string__93_273;
static void cont__93_274(void);
static NODE *string__93_275;
static void cont__93_276(void);
static NODE *string__93_277;
static void cont__93_278(void);
static NODE *string__93_279;
static void cont__93_280(void);
static NODE *string__93_281;
static void cont__93_282(void);
static NODE *string__93_283;
static void cont__93_284(void);
static NODE *string__93_285;
static void cont__93_286(void);
static NODE *string__93_287;
static void cont__93_288(void);
static NODE *string__93_289;
static void cont__93_290(void);
static NODE *string__93_291;
static void cont__93_292(void);
static NODE *string__93_293;
static void cont__93_294(void);
static NODE *string__93_295;
static void cont__93_296(void);
static NODE *string__93_297;
static void cont__93_298(void);
static NODE *string__93_299;
static void cont__93_300(void);
static NODE *string__93_301;
static void cont__93_302(void);
static NODE *string__93_303;
static void cont__93_304(void);
static NODE *string__93_305;
static void cont__93_306(void);
static NODE *string__93_307;
static void cont__93_308(void);
static NODE *string__93_309;
static void cont__93_310(void);
static NODE *string__93_311;
static void cont__93_312(void);
static NODE *string__93_313;
static void cont__93_314(void);
static NODE *string__93_315;
static void cont__93_316(void);
static NODE *string__93_317;
static void cont__93_318(void);
static NODE *string__93_319;
static void cont__93_320(void);
static NODE *string__93_321;
static void cont__93_322(void);
static NODE *string__93_323;
static void cont__93_324(void);
static NODE *string__93_325;
static void cont__93_326(void);
static NODE *string__93_327;
static void cont__93_328(void);
static NODE *string__93_329;
static void cont__93_330(void);
static NODE *string__93_331;
static void cont__93_332(void);
static NODE *string__93_333;
static void cont__93_334(void);
static NODE *string__93_335;
static void cont__93_336(void);
static NODE *string__93_337;
static void cont__93_338(void);
static NODE *string__93_339;
static void cont__93_340(void);
static NODE *string__93_341;
static void cont__93_342(void);
static NODE *string__93_343;
static void cont__93_344(void);
static NODE *string__93_345;
static void cont__93_346(void);
static NODE *string__93_347;
static void cont__93_348(void);
static NODE *string__93_349;
static void cont__93_350(void);
static NODE *string__93_351;
static void cont__93_352(void);
static NODE *string__93_353;
static void cont__93_354(void);
static NODE *string__93_355;
static void cont__93_356(void);
static NODE *string__93_357;
static void cont__93_358(void);
static NODE *string__93_359;
static void cont__93_360(void);
static NODE *string__93_361;
static void cont__93_362(void);
static NODE *string__93_363;
static void cont__93_364(void);
static NODE *string__93_365;
static void cont__93_366(void);
static NODE *string__93_367;
static void cont__93_368(void);
static NODE *string__93_369;
static void cont__93_370(void);
static NODE *string__93_371;
static void cont__93_372(void);
static NODE *string__93_373;
static void cont__93_374(void);
static NODE *string__93_375;
static void cont__93_376(void);
static NODE *string__93_377;
static void cont__93_378(void);
static NODE *string__93_379;
static void cont__93_380(void);
static NODE *string__93_381;
static void cont__93_382(void);
static NODE *string__93_383;
static void cont__93_384(void);
static NODE *string__93_385;
static void cont__93_386(void);
static NODE *string__93_387;
static void cont__93_388(void);
static NODE *string__93_389;
static void cont__93_390(void);
static NODE *string__93_391;
static void cont__93_392(void);
static NODE *string__93_393;
static void cont__93_394(void);
static NODE *string__93_395;
static void cont__93_396(void);
static NODE *string__93_397;
static void cont__93_398(void);
static NODE *string__93_399;
static void cont__93_400(void);
static NODE *string__93_401;
static void cont__93_402(void);
static NODE *string__93_403;
static void cont__93_404(void);
static NODE *string__93_405;
static void cont__93_406(void);
static NODE *string__93_407;
static void cont__93_408(void);
static NODE *string__93_409;
static void cont__93_410(void);
static NODE *string__93_411;
static void cont__93_412(void);
static NODE *string__93_413;
static void cont__93_414(void);
static NODE *string__93_415;
static void cont__93_416(void);
static NODE *string__93_417;
static void cont__93_418(void);
static NODE *string__93_419;
static void cont__93_420(void);
static NODE *string__93_421;
static void cont__93_422(void);
static NODE *string__93_423;
static void cont__93_424(void);
static NODE *string__93_425;
static void cont__93_426(void);
static NODE *string__93_427;
static void cont__93_428(void);
static NODE *string__93_429;
static void cont__93_430(void);
static NODE *string__93_431;
static void cont__93_432(void);
static NODE *string__93_433;
static void cont__93_434(void);
static NODE *string__93_435;
static void cont__93_436(void);
static NODE *string__93_437;
static void cont__93_438(void);
static NODE *string__93_439;
static void cont__93_440(void);
static NODE *string__93_441;
static void cont__93_442(void);
static NODE *string__93_443;
static void cont__93_444(void);
static NODE *string__93_445;
static void cont__93_446(void);
static NODE *string__93_447;
static void cont__93_448(void);
static NODE *string__93_449;
static void cont__93_450(void);
static NODE *string__93_451;
static void cont__93_452(void);
static NODE *string__93_453;
static void cont__93_454(void);
static NODE *string__93_455;
static void cont__93_456(void);
static NODE *string__93_457;
static void cont__93_458(void);
static NODE *string__93_459;
static void cont__93_460(void);
static NODE *string__93_461;
static void cont__93_462(void);
static NODE *string__93_463;
static void cont__93_464(void);
static NODE *string__93_465;
static void cont__93_466(void);
static NODE *string__93_467;
static void cont__93_468(void);
static NODE *string__93_469;
static void cont__93_470(void);
static NODE *string__93_471;
static void cont__93_472(void);
static NODE *string__93_473;
static void cont__93_474(void);
static NODE *string__93_475;
static void cont__93_476(void);
static NODE *string__93_477;
static void cont__93_478(void);
static NODE *string__93_479;
static void cont__93_480(void);
static NODE *string__93_481;
static void cont__93_482(void);
static NODE *string__93_483;
static void cont__93_484(void);
static NODE *string__93_485;
static void cont__93_486(void);
static NODE *string__93_487;
static void cont__93_488(void);
static NODE *string__93_489;
static void cont__93_490(void);
static NODE *string__93_491;
static void cont__93_492(void);
static NODE *string__93_493;
static void cont__93_494(void);
static NODE *string__93_495;
static void cont__93_496(void);
static NODE *string__93_497;
static void cont__93_498(void);
static NODE *string__93_499;
static void cont__93_500(void);
static NODE *string__93_501;
static void cont__93_502(void);
static NODE *string__93_503;
static void cont__93_504(void);
static NODE *string__93_505;
static void cont__93_506(void);
static NODE *string__93_507;
static void cont__93_508(void);
static NODE *string__93_509;
static void cont__93_510(void);
static NODE *string__93_511;
static void cont__93_512(void);
static NODE *string__93_513;
static void cont__93_514(void);
static NODE *string__93_515;
static void cont__93_516(void);
static NODE *string__93_517;
static void cont__93_518(void);
static NODE *string__93_519;
static void cont__93_520(void);
static NODE *string__93_521;
static void cont__93_522(void);
static NODE *string__93_523;
static void cont__93_524(void);
static NODE *string__93_525;
static void cont__93_526(void);
static NODE *string__93_527;
static void cont__93_528(void);
static NODE *string__93_529;
static void cont__93_530(void);
static NODE *string__93_531;
static void cont__93_532(void);
static NODE *string__93_533;
static void cont__93_534(void);
static NODE *string__93_535;
static void cont__93_536(void);
static NODE *string__93_537;
static void cont__93_538(void);
static NODE *string__93_539;
static void cont__93_540(void);
static NODE *string__93_541;
static void cont__93_542(void);
static NODE *string__93_543;
static void cont__93_544(void);
static NODE *string__93_545;
static void cont__93_546(void);
static NODE *string__93_547;
static void cont__93_548(void);
static NODE *string__93_549;
static void cont__93_550(void);
static NODE *string__93_551;
static void cont__93_552(void);
static NODE *string__93_553;
static void cont__93_554(void);
static NODE *string__93_555;
static void cont__93_556(void);
static NODE *string__93_557;
static void cont__93_558(void);
static NODE *string__93_559;
static void cont__93_560(void);
static NODE *string__93_561;
static void cont__93_562(void);
static NODE *string__93_563;
static void cont__93_564(void);
static NODE *string__93_565;
static void cont__93_566(void);
static NODE *string__93_567;
static void cont__93_568(void);
static NODE *string__93_569;
static void cont__93_570(void);
static NODE *string__93_571;
static void cont__93_572(void);
static NODE *string__93_573;
static void cont__93_574(void);
static NODE *string__93_575;
static void cont__93_576(void);
static NODE *string__93_577;
static void cont__93_578(void);
static NODE *string__93_579;
static void cont__93_580(void);
static NODE *string__93_581;
static void cont__93_582(void);
static NODE *string__93_583;
static void cont__93_584(void);
static NODE *string__93_585;
static void cont__93_586(void);
static NODE *string__93_587;
static void cont__93_588(void);
static void cont__93_589(void);
void run__basic__types__string(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__types__string, NULL, 640, 640, 5, 13},
  {cont__93_2, NULL, 641, 641, 5, 18},
  {cont__93_4, NULL, 642, 642, 5, 19},
  {cont__93_6, NULL, 643, 643, 5, 13},
  {cont__93_8, NULL, 644, 644, 5, 17},
  {cont__93_10, NULL, 645, 645, 5, 13},
  {cont__93_12, NULL, 646, 646, 5, 13},
  {cont__93_14, NULL, 647, 647, 5, 18},
  {cont__93_16, NULL, 648, 648, 5, 15},
  {cont__93_18, NULL, 649, 649, 5, 13},
  {cont__93_20, NULL, 650, 650, 5, 14},
  {cont__93_22, NULL, 651, 651, 5, 17},
  {cont__93_24, NULL, 652, 652, 5, 17},
  {cont__93_26, NULL, 653, 653, 5, 15},
  {cont__93_28, NULL, 654, 654, 5, 13},
  {cont__93_30, NULL, 655, 655, 5, 18},
  {cont__93_32, NULL, 656, 656, 5, 15},
  {cont__93_34, NULL, 657, 657, 5, 14},
  {cont__93_36, NULL, 658, 658, 5, 14},
  {cont__93_38, NULL, 659, 659, 5, 13},
  {cont__93_40, NULL, 660, 660, 5, 16},
  {cont__93_42, NULL, 661, 661, 5, 17},
  {cont__93_44, NULL, 662, 662, 5, 13},
  {cont__93_46, NULL, 663, 663, 5, 13},
  {cont__93_48, NULL, 664, 664, 5, 14},
  {cont__93_50, NULL, 665, 665, 5, 13},
  {cont__93_52, NULL, 666, 666, 5, 14},
  {cont__93_54, NULL, 667, 667, 5, 15},
  {cont__93_56, NULL, 668, 668, 5, 15},
  {cont__93_58, NULL, 669, 669, 5, 15},
  {cont__93_60, NULL, 670, 670, 5, 13},
  {cont__93_62, NULL, 671, 671, 5, 13},
  {cont__93_64, NULL, 672, 672, 5, 13},
  {cont__93_66, NULL, 673, 673, 5, 13},
  {cont__93_68, NULL, 674, 674, 5, 13},
  {cont__93_70, NULL, 675, 675, 5, 14},
  {cont__93_72, NULL, 676, 676, 5, 13},
  {cont__93_74, NULL, 677, 677, 5, 14},
  {cont__93_76, NULL, 678, 678, 5, 13},
  {cont__93_78, NULL, 679, 679, 5, 13},
  {cont__93_80, NULL, 680, 680, 5, 13},
  {cont__93_82, NULL, 681, 681, 5, 13},
  {cont__93_84, NULL, 682, 682, 5, 13},
  {cont__93_86, NULL, 683, 683, 5, 13},
  {cont__93_88, NULL, 684, 684, 5, 13},
  {cont__93_90, NULL, 685, 685, 5, 13},
  {cont__93_92, NULL, 686, 686, 5, 13},
  {cont__93_94, NULL, 687, 687, 5, 13},
  {cont__93_96, NULL, 688, 688, 5, 13},
  {cont__93_98, NULL, 689, 689, 5, 13},
  {cont__93_100, NULL, 690, 690, 5, 13},
  {cont__93_102, NULL, 691, 691, 5, 13},
  {cont__93_104, NULL, 692, 692, 5, 13},
  {cont__93_106, NULL, 693, 693, 5, 14},
  {cont__93_108, NULL, 694, 694, 5, 13},
  {cont__93_110, NULL, 695, 695, 5, 13},
  {cont__93_112, NULL, 696, 696, 5, 13},
  {cont__93_114, NULL, 697, 697, 5, 13},
  {cont__93_116, NULL, 698, 698, 5, 13},
  {cont__93_118, NULL, 699, 699, 5, 14},
  {cont__93_120, NULL, 700, 700, 5, 13},
  {cont__93_122, NULL, 701, 701, 5, 13},
  {cont__93_124, NULL, 702, 702, 5, 14},
  {cont__93_126, NULL, 703, 703, 5, 13},
  {cont__93_128, NULL, 704, 704, 5, 13},
  {cont__93_130, NULL, 705, 705, 5, 13},
  {cont__93_132, NULL, 706, 706, 5, 13},
  {cont__93_134, NULL, 707, 707, 5, 14},
  {cont__93_136, NULL, 708, 708, 5, 13},
  {cont__93_138, NULL, 709, 709, 5, 14},
  {cont__93_140, NULL, 710, 710, 5, 13},
  {cont__93_142, NULL, 711, 711, 5, 13},
  {cont__93_144, NULL, 712, 712, 5, 13},
  {cont__93_146, NULL, 713, 713, 5, 13},
  {cont__93_148, NULL, 714, 714, 5, 13},
  {cont__93_150, NULL, 715, 715, 5, 13},
  {cont__93_152, NULL, 716, 716, 5, 13},
  {cont__93_154, NULL, 717, 717, 5, 13},
  {cont__93_156, NULL, 718, 718, 5, 13},
  {cont__93_158, NULL, 719, 719, 5, 13},
  {cont__93_160, NULL, 720, 720, 5, 13},
  {cont__93_162, NULL, 721, 721, 5, 13},
  {cont__93_164, NULL, 722, 722, 5, 13},
  {cont__93_166, NULL, 723, 723, 5, 13},
  {cont__93_168, NULL, 724, 724, 5, 13},
  {cont__93_170, NULL, 725, 725, 5, 14},
  {cont__93_172, NULL, 726, 726, 5, 13},
  {cont__93_174, NULL, 727, 727, 5, 13},
  {cont__93_176, NULL, 728, 728, 5, 13},
  {cont__93_178, NULL, 729, 729, 5, 13},
  {cont__93_180, NULL, 730, 730, 5, 13},
  {cont__93_182, NULL, 731, 731, 5, 14},
  {cont__93_184, NULL, 732, 732, 5, 13},
  {cont__93_186, NULL, 733, 733, 5, 13},
  {cont__93_188, NULL, 734, 734, 5, 13},
  {cont__93_190, NULL, 735, 735, 5, 13},
  {cont__93_192, NULL, 736, 736, 5, 13},
  {cont__93_194, NULL, 737, 737, 5, 13},
  {cont__93_196, NULL, 738, 738, 5, 13},
  {cont__93_198, NULL, 739, 739, 5, 13},
  {cont__93_200, NULL, 740, 740, 5, 13},
  {cont__93_202, NULL, 741, 741, 5, 13},
  {cont__93_204, NULL, 742, 742, 5, 13},
  {cont__93_206, NULL, 743, 743, 5, 13},
  {cont__93_208, NULL, 744, 744, 5, 13},
  {cont__93_210, NULL, 745, 745, 5, 13},
  {cont__93_212, NULL, 746, 746, 5, 13},
  {cont__93_214, NULL, 747, 747, 5, 13},
  {cont__93_216, NULL, 748, 748, 5, 13},
  {cont__93_218, NULL, 749, 749, 5, 13},
  {cont__93_220, NULL, 750, 750, 5, 13},
  {cont__93_222, NULL, 751, 751, 5, 13},
  {cont__93_224, NULL, 752, 752, 5, 13},
  {cont__93_226, NULL, 753, 753, 5, 13},
  {cont__93_228, NULL, 754, 754, 5, 13},
  {cont__93_230, NULL, 755, 755, 5, 13},
  {cont__93_232, NULL, 756, 756, 5, 13},
  {cont__93_234, NULL, 757, 757, 5, 13},
  {cont__93_236, NULL, 758, 758, 5, 13},
  {cont__93_238, NULL, 759, 759, 5, 13},
  {cont__93_240, NULL, 760, 760, 5, 13},
  {cont__93_242, NULL, 761, 761, 5, 13},
  {cont__93_244, NULL, 762, 762, 5, 13},
  {cont__93_246, NULL, 763, 763, 5, 13},
  {cont__93_248, NULL, 764, 764, 5, 13},
  {cont__93_250, NULL, 765, 765, 5, 13},
  {cont__93_252, NULL, 766, 766, 5, 13},
  {cont__93_254, NULL, 767, 767, 5, 13},
  {cont__93_256, NULL, 768, 768, 5, 13},
  {cont__93_258, NULL, 769, 769, 5, 13},
  {cont__93_260, NULL, 770, 770, 5, 13},
  {cont__93_262, NULL, 771, 771, 5, 13},
  {cont__93_264, NULL, 772, 772, 5, 13},
  {cont__93_266, NULL, 773, 773, 5, 13},
  {cont__93_268, NULL, 774, 774, 5, 13},
  {cont__93_270, NULL, 775, 775, 5, 13},
  {cont__93_272, NULL, 776, 776, 5, 13},
  {cont__93_274, NULL, 777, 777, 5, 13},
  {cont__93_276, NULL, 778, 778, 5, 13},
  {cont__93_278, NULL, 779, 779, 5, 13},
  {cont__93_280, NULL, 780, 780, 5, 13},
  {cont__93_282, NULL, 781, 781, 5, 13},
  {cont__93_284, NULL, 782, 782, 5, 13},
  {cont__93_286, NULL, 783, 783, 5, 13},
  {cont__93_288, NULL, 784, 784, 5, 13},
  {cont__93_290, NULL, 785, 785, 5, 14},
  {cont__93_292, NULL, 786, 786, 5, 14},
  {cont__93_294, NULL, 787, 787, 5, 13},
  {cont__93_296, NULL, 788, 788, 5, 13},
  {cont__93_298, NULL, 789, 789, 5, 13},
  {cont__93_300, NULL, 790, 790, 5, 13},
  {cont__93_302, NULL, 791, 791, 5, 13},
  {cont__93_304, NULL, 792, 792, 5, 13},
  {cont__93_306, NULL, 793, 793, 5, 13},
  {cont__93_308, NULL, 794, 794, 5, 13},
  {cont__93_310, NULL, 795, 795, 5, 13},
  {cont__93_312, NULL, 796, 796, 5, 13},
  {cont__93_314, NULL, 797, 797, 5, 13},
  {cont__93_316, NULL, 798, 798, 5, 13},
  {cont__93_318, NULL, 799, 799, 5, 13},
  {cont__93_320, NULL, 800, 800, 5, 13},
  {cont__93_322, NULL, 801, 801, 5, 13},
  {cont__93_324, NULL, 802, 802, 5, 13},
  {cont__93_326, NULL, 803, 803, 5, 13},
  {cont__93_328, NULL, 804, 804, 5, 13},
  {cont__93_330, NULL, 805, 805, 5, 13},
  {cont__93_332, NULL, 806, 806, 5, 13},
  {cont__93_334, NULL, 807, 807, 5, 13},
  {cont__93_336, NULL, 808, 808, 5, 13},
  {cont__93_338, NULL, 809, 809, 5, 13},
  {cont__93_340, NULL, 810, 810, 5, 13},
  {cont__93_342, NULL, 811, 811, 5, 13},
  {cont__93_344, NULL, 812, 812, 5, 13},
  {cont__93_346, NULL, 813, 813, 5, 13},
  {cont__93_348, NULL, 814, 814, 5, 13},
  {cont__93_350, NULL, 815, 815, 5, 13},
  {cont__93_352, NULL, 816, 816, 5, 13},
  {cont__93_354, NULL, 817, 817, 5, 14},
  {cont__93_356, NULL, 818, 818, 5, 14},
  {cont__93_358, NULL, 819, 819, 5, 13},
  {cont__93_360, NULL, 820, 820, 5, 13},
  {cont__93_362, NULL, 821, 821, 5, 13},
  {cont__93_364, NULL, 822, 822, 5, 13},
  {cont__93_366, NULL, 823, 823, 5, 13},
  {cont__93_368, NULL, 824, 824, 5, 13},
  {cont__93_370, NULL, 825, 825, 5, 13},
  {cont__93_372, NULL, 826, 826, 5, 13},
  {cont__93_374, NULL, 827, 827, 5, 13},
  {cont__93_376, NULL, 828, 828, 5, 13},
  {cont__93_378, NULL, 829, 829, 5, 13},
  {cont__93_380, NULL, 830, 830, 5, 13},
  {cont__93_382, NULL, 831, 831, 5, 13},
  {cont__93_384, NULL, 832, 832, 5, 13},
  {cont__93_386, NULL, 833, 833, 5, 13},
  {cont__93_388, NULL, 834, 834, 5, 13},
  {cont__93_390, NULL, 835, 835, 5, 13},
  {cont__93_392, NULL, 836, 836, 5, 13},
  {cont__93_394, NULL, 837, 837, 5, 13},
  {cont__93_396, NULL, 838, 838, 5, 13},
  {cont__93_398, NULL, 839, 839, 5, 13},
  {cont__93_400, NULL, 840, 840, 5, 13},
  {cont__93_402, NULL, 841, 841, 5, 13},
  {cont__93_404, NULL, 842, 842, 5, 13},
  {cont__93_406, NULL, 843, 843, 5, 13},
  {cont__93_408, NULL, 844, 844, 5, 13},
  {cont__93_410, NULL, 845, 845, 5, 13},
  {cont__93_412, NULL, 846, 846, 5, 13},
  {cont__93_414, NULL, 847, 847, 5, 13},
  {cont__93_416, NULL, 848, 848, 5, 13},
  {cont__93_418, NULL, 849, 849, 5, 13},
  {cont__93_420, NULL, 850, 850, 5, 13},
  {cont__93_422, NULL, 851, 851, 5, 13},
  {cont__93_424, NULL, 852, 852, 5, 13},
  {cont__93_426, NULL, 853, 853, 5, 13},
  {cont__93_428, NULL, 854, 854, 5, 13},
  {cont__93_430, NULL, 855, 855, 5, 13},
  {cont__93_432, NULL, 856, 856, 5, 13},
  {cont__93_434, NULL, 857, 857, 5, 13},
  {cont__93_436, NULL, 858, 858, 5, 13},
  {cont__93_438, NULL, 859, 859, 5, 13},
  {cont__93_440, NULL, 860, 860, 5, 13},
  {cont__93_442, NULL, 861, 861, 5, 13},
  {cont__93_444, NULL, 862, 862, 5, 13},
  {cont__93_446, NULL, 863, 863, 5, 13},
  {cont__93_448, NULL, 864, 864, 5, 13},
  {cont__93_450, NULL, 865, 865, 5, 13},
  {cont__93_452, NULL, 866, 866, 5, 13},
  {cont__93_454, NULL, 867, 867, 5, 13},
  {cont__93_456, NULL, 868, 868, 5, 13},
  {cont__93_458, NULL, 869, 869, 5, 13},
  {cont__93_460, NULL, 870, 870, 5, 13},
  {cont__93_462, NULL, 871, 871, 5, 13},
  {cont__93_464, NULL, 872, 872, 5, 13},
  {cont__93_466, NULL, 873, 873, 5, 13},
  {cont__93_468, NULL, 874, 874, 5, 13},
  {cont__93_470, NULL, 875, 875, 5, 13},
  {cont__93_472, NULL, 876, 876, 5, 13},
  {cont__93_474, NULL, 877, 877, 5, 13},
  {cont__93_476, NULL, 878, 878, 5, 13},
  {cont__93_478, NULL, 879, 879, 5, 13},
  {cont__93_480, NULL, 880, 880, 5, 14},
  {cont__93_482, NULL, 881, 881, 5, 14},
  {cont__93_484, NULL, 882, 882, 5, 14},
  {cont__93_486, NULL, 883, 883, 5, 14},
  {cont__93_488, NULL, 884, 884, 5, 14},
  {cont__93_490, NULL, 885, 885, 5, 14},
  {cont__93_492, NULL, 886, 886, 5, 14},
  {cont__93_494, NULL, 887, 887, 5, 14},
  {cont__93_496, NULL, 888, 888, 5, 14},
  {cont__93_498, NULL, 889, 889, 5, 13},
  {cont__93_500, NULL, 890, 890, 5, 13},
  {cont__93_502, NULL, 891, 891, 5, 13},
  {cont__93_504, NULL, 892, 892, 5, 13},
  {cont__93_506, NULL, 893, 893, 5, 13},
  {cont__93_508, NULL, 894, 894, 5, 13},
  {cont__93_510, NULL, 895, 895, 5, 13},
  {cont__93_512, NULL, 896, 896, 5, 13},
  {cont__93_514, NULL, 897, 897, 5, 13},
  {cont__93_516, NULL, 898, 898, 5, 13},
  {cont__93_518, NULL, 899, 899, 5, 13},
  {cont__93_520, NULL, 900, 900, 5, 13},
  {cont__93_522, NULL, 901, 901, 5, 13},
  {cont__93_524, NULL, 902, 902, 5, 13},
  {cont__93_526, NULL, 903, 903, 5, 13},
  {cont__93_528, NULL, 904, 904, 5, 13},
  {cont__93_530, NULL, 905, 905, 5, 13},
  {cont__93_532, NULL, 906, 906, 5, 13},
  {cont__93_534, NULL, 907, 907, 5, 13},
  {cont__93_536, NULL, 908, 908, 5, 13},
  {cont__93_538, NULL, 909, 909, 5, 14},
  {cont__93_540, NULL, 910, 910, 5, 14},
  {cont__93_542, NULL, 911, 911, 5, 13},
  {cont__93_544, NULL, 912, 912, 5, 13},
  {cont__93_546, NULL, 913, 913, 5, 13},
  {cont__93_548, NULL, 914, 914, 5, 13},
  {cont__93_550, NULL, 915, 915, 5, 13},
  {cont__93_552, NULL, 916, 916, 5, 13},
  {cont__93_554, NULL, 917, 917, 5, 13},
  {cont__93_556, NULL, 918, 918, 5, 13},
  {cont__93_558, NULL, 919, 919, 5, 13},
  {cont__93_560, NULL, 920, 920, 5, 13},
  {cont__93_562, NULL, 921, 921, 5, 14},
  {cont__93_564, NULL, 922, 922, 5, 14},
  {cont__93_566, NULL, 923, 923, 5, 14},
  {cont__93_568, NULL, 924, 924, 5, 13},
  {cont__93_570, NULL, 925, 925, 5, 13},
  {cont__93_572, NULL, 926, 926, 5, 13},
  {cont__93_574, NULL, 927, 927, 5, 13},
  {cont__93_576, NULL, 928, 928, 5, 13},
  {cont__93_578, NULL, 929, 929, 5, 13},
  {cont__93_580, NULL, 930, 930, 5, 14},
  {cont__93_582, NULL, 931, 931, 5, 14},
  {cont__93_584, NULL, 932, 932, 5, 13},
  {cont__93_586, NULL, 933, 933, 5, 13},
  {cont__93_588, NULL, 638, 933, 1, 14},
  {cont__93_589, NULL, },
  {entry__1_5, NULL, 29, 29, 18, 33},
  {entry__1_1, NULL, 28, 28, 3, 28},
  {cont__1_2, &frame__1_1, 29, 29, 6, 15},
  {cont__1_3, &frame__1_1, 29, 29, 6, 15},
  {cont__1_4, &frame__1_1, 29, 29, 3, 33},
  {cont__1_6, &frame__1_1, 30, 30, 3, 10},
  {entry__2_5, NULL, 38, 38, 18, 33},
  {entry__2_1, NULL, 37, 37, 3, 25},
  {cont__2_2, &frame__2_1, 38, 38, 6, 15},
  {cont__2_3, &frame__2_1, 38, 38, 6, 15},
  {cont__2_4, &frame__2_1, 38, 38, 3, 33},
  {cont__2_6, &frame__2_1, 39, 39, 3, 10},
  {entry__3_5, NULL, 44, 44, 22, 27},
  {cont__3_6, &frame__3_5, 44, 44, 27, 27},
  {entry__3_11, NULL, 45, 45, 22, 28},
  {cont__3_12, &frame__3_11, 45, 45, 22, 39},
  {cont__3_13, &frame__3_11, 45, 45, 22, 39},
  {entry__3_15, NULL, 45, 45, 42, 47},
  {cont__3_16, &frame__3_15, 45, 45, 47, 47},
  {entry__3_8, NULL, 45, 45, 12, 17},
  {cont__3_9, &frame__3_8, 45, 45, 12, 17},
  {cont__3_10, &frame__3_8, 45, 45, 12, 39},
  {cont__3_14, &frame__3_8, 45, 45, 9, 47},
  {entry__3_20, NULL, 47, 47, 15, 21},
  {cont__3_21, &frame__3_20, 47, 47, 15, 28},
  {cont__3_22, &frame__3_20, 47, 47, 15, 28},
  {entry__3_24, NULL, 48, 48, 7, 21},
  {entry__3_25, NULL, 50, 50, 7, 24},
  {entry__3_1, NULL, 43, 43, 3, 20},
  {cont__3_2, &frame__3_1, 44, 44, 6, 12},
  {cont__3_3, &frame__3_1, 44, 44, 6, 19},
  {cont__3_4, &frame__3_1, 44, 44, 3, 27},
  {cont__3_7, &frame__3_1, 45, 45, 3, 47},
  {cont__3_17, &frame__3_1, 47, 47, 5, 10},
  {cont__3_18, &frame__3_1, 47, 47, 5, 10},
  {cont__3_19, &frame__3_1, 47, 47, 5, 28},
  {cont__3_23, &frame__3_1, 46, 50, 3, 25},
  {entry__4_5, NULL, 58, 58, 18, 33},
  {entry__4_1, NULL, 57, 57, 3, 27},
  {cont__4_2, &frame__4_1, 58, 58, 6, 15},
  {cont__4_3, &frame__4_1, 58, 58, 6, 15},
  {cont__4_4, &frame__4_1, 58, 58, 3, 33},
  {cont__4_6, &frame__4_1, 59, 59, 3, 10},
  {entry__5_1, NULL, 61, 61, 42, 54},
  {cont__5_2, &frame__5_1, 61, 61, 35, 60},
  {cont__5_3, &frame__5_1, 61, 61, 32, 60},
  {entry__6_2, NULL, 68, 68, 37, 49},
  {cont__6_3, &frame__6_2, 68, 68, 24, 49},
  {cont__6_4, &frame__6_2, 68, 68, 49, 49},
  {entry__6_1, NULL, 68, 68, 3, 49},
  {cont__6_5, &frame__6_1, },
  {entry__7_19, NULL, 87, 87, 11, 26},
  {cont__7_20, &frame__7_19, 87, 87, 11, 26},
  {cont__7_21, &frame__7_19, 87, 87, 11, 26},
  {entry__7_16, NULL, 86, 86, 11, 26},
  {cont__7_17, &frame__7_16, 86, 86, 11, 26},
  {cont__7_18, &frame__7_16, 87, 87, 11, 26},
  {cont__7_22, &frame__7_16, },
  {entry__7_13, NULL, 85, 85, 11, 25},
  {cont__7_14, &frame__7_13, 85, 85, 11, 25},
  {cont__7_15, &frame__7_13, },
  {cont__7_23, &frame__7_13, },
  {entry__7_30, NULL, 92, 92, 32, 38},
  {cont__7_31, &frame__7_30, 92, 92, 32, 49},
  {cont__7_32, &frame__7_30, 92, 92, 32, 49},
  {entry__7_37, NULL, 94, 94, 37, 44},
  {cont__7_38, &frame__7_37, 94, 94, 37, 55},
  {cont__7_39, &frame__7_37, 94, 94, 37, 55},
  {entry__7_41, NULL, 95, 95, 21, 26},
  {cont__7_42, &frame__7_41, 95, 95, 26, 26},
  {entry__7_43, NULL, 97, 97, 21, 32},
  {entry__7_34, NULL, 94, 94, 19, 32},
  {cont__7_35, &frame__7_34, 94, 94, 19, 32},
  {cont__7_36, &frame__7_34, 94, 94, 19, 55},
  {cont__7_40, &frame__7_34, 93, 97, 17, 33},
  {entry__7_47, NULL, 100, 100, 37, 44},
  {cont__7_48, &frame__7_47, 100, 100, 37, 55},
  {cont__7_49, &frame__7_47, 100, 100, 37, 55},
  {entry__7_51, NULL, 101, 101, 21, 31},
  {entry__7_52, NULL, 103, 103, 28, 47},
  {cont__7_53, &frame__7_52, 103, 103, 21, 47},
  {entry__7_44, NULL, 100, 100, 19, 32},
  {cont__7_45, &frame__7_44, 100, 100, 19, 32},
  {cont__7_46, &frame__7_44, 100, 100, 19, 55},
  {cont__7_50, &frame__7_44, 99, 103, 17, 48},
  {entry__7_27, NULL, 92, 92, 15, 27},
  {cont__7_28, &frame__7_27, 92, 92, 15, 27},
  {cont__7_29, &frame__7_27, 92, 92, 15, 49},
  {cont__7_33, &frame__7_27, 91, 103, 13, 50},
  {entry__7_25, NULL, 89, 89, 11, 17},
  {cont__7_26, &frame__7_25, 90, 103, 11, 51},
  {entry__7_54, NULL, 105, 105, 18, 37},
  {cont__7_55, &frame__7_54, 105, 105, 11, 37},
  {entry__7_10, NULL, 84, 84, 11, 25},
  {cont__7_11, &frame__7_10, 84, 84, 11, 25},
  {cont__7_12, &frame__7_10, },
  {cont__7_24, &frame__7_10, 82, 105, 7, 38},
  {cont__7_56, &frame__7_10, 106, 106, 14, 33},
  {cont__7_57, &frame__7_10, 106, 106, 7, 33},
  {entry__7_5, NULL, 79, 79, 5, 21},
  {cont__7_6, &frame__7_5, 80, 80, 5, 23},
  {cont__7_7, &frame__7_5, 81, 81, 8, 28},
  {cont__7_8, &frame__7_5, 81, 81, 8, 28},
  {cont__7_9, &frame__7_5, 81, 106, 5, 33},
  {entry__7_1, NULL, 76, 76, 3, 27},
  {cont__7_2, &frame__7_1, 77, 77, 3, 29},
  {cont__7_3, &frame__7_1, 78, 78, 13, 35},
  {cont__7_4, &frame__7_1, 78, 106, 3, 34},
  {cont__7_58, &frame__7_1, 106, 106, 34, 34},
  {entry__8_2, NULL, 110, 110, 25, 40},
  {cont__8_3, &frame__8_2, 110, 110, 40, 40},
  {entry__8_1, NULL, 110, 110, 3, 40},
  {cont__8_4, &frame__8_1, 111, 111, 3, 10},
  {entry__9_3, NULL, 116, 116, 42, 48},
  {cont__9_4, &frame__9_3, 116, 116, 32, 49},
  {cont__9_5, &frame__9_3, 116, 116, 20, 49},
  {cont__9_6, &frame__9_3, 116, 116, 49, 49},
  {entry__9_1, NULL, 115, 115, 3, 20},
  {cont__9_2, &frame__9_1, 116, 116, 3, 49},
  {cont__9_7, &frame__9_1, 117, 117, 3, 8},
  {entry__10_2, NULL, 129, 129, 7, 15},
  {entry__10_3, NULL, 131, 131, 7, 17},
  {entry__10_6, NULL, 133, 133, 17, 50},
  {entry__10_13, NULL, 138, 138, 18, 32},
  {cont__10_14, &frame__10_13, 138, 138, 11, 32},
  {entry__10_15, NULL, 140, 140, 18, 37},
  {cont__10_16, &frame__10_15, 140, 140, 11, 37},
  {entry__10_4, NULL, 133, 133, 10, 14},
  {cont__10_5, &frame__10_4, 133, 133, 7, 50},
  {cont__10_8, &frame__10_4, 134, 134, 7, 18},
  {cont__10_9, &frame__10_4, 135, 135, 7, 22},
  {cont__10_10, &frame__10_4, 137, 137, 9, 11},
  {cont__10_11, &frame__10_4, 137, 137, 9, 16},
  {cont__10_12, &frame__10_4, 136, 140, 7, 38},
  {entry__10_1, NULL, 126, 140, 3, 40},
  {cont__10_17, &frame__10_1, 140, 140, 40, 40},
  {entry__11_6, NULL, 158, 158, 5, 27},
  {cont__11_7, &frame__11_6, 159, 159, 33, 37},
  {cont__11_8, &frame__11_6, 159, 159, 33, 45},
  {cont__11_9, &frame__11_6, 159, 159, 33, 47},
  {cont__11_10, &frame__11_6, 159, 159, 33, 61},
  {cont__11_11, &frame__11_6, 159, 159, 25, 62},
  {cont__11_12, &frame__11_6, 159, 159, 66, 70},
  {cont__11_13, &frame__11_6, 159, 159, 19, 71},
  {cont__11_14, &frame__11_6, 159, 159, 12, 77},
  {cont__11_15, &frame__11_6, 159, 159, 5, 77},
  {entry__11_1, NULL, 155, 155, 3, 22},
  {cont__11_3, &frame__11_1, 156, 156, 3, 22},
  {cont__11_4, &frame__11_1, 157, 157, 6, 12},
  {cont__11_5, &frame__11_1, 157, 159, 3, 77},
  {cont__11_16, &frame__11_1, 160, 160, 3, 9},
  {entry__12_6, NULL, 178, 178, 5, 27},
  {cont__12_7, &frame__12_6, 179, 179, 38, 42},
  {cont__12_8, &frame__12_6, 179, 179, 38, 50},
  {cont__12_9, &frame__12_6, 179, 179, 38, 52},
  {cont__12_10, &frame__12_6, 179, 179, 38, 66},
  {cont__12_11, &frame__12_6, 179, 179, 30, 67},
  {cont__12_12, &frame__12_6, 179, 179, 71, 75},
  {cont__12_13, &frame__12_6, 179, 179, 24, 76},
  {cont__12_14, &frame__12_6, 179, 179, 12, 77},
  {cont__12_15, &frame__12_6, 179, 179, 5, 77},
  {entry__12_1, NULL, 175, 175, 3, 22},
  {cont__12_3, &frame__12_1, 176, 176, 3, 22},
  {cont__12_4, &frame__12_1, 177, 177, 6, 12},
  {cont__12_5, &frame__12_1, 177, 179, 3, 77},
  {cont__12_16, &frame__12_1, 180, 180, 3, 9},
  {entry__13_5, NULL, 194, 194, 15, 21},
  {entry__13_6, NULL, 194, 194, 27, 41},
  {cont__13_7, &frame__13_6, 194, 194, 24, 41},
  {entry__13_1, NULL, 192, 192, 3, 22},
  {cont__13_2, &frame__13_1, 193, 193, 3, 22},
  {cont__13_3, &frame__13_1, 194, 194, 6, 12},
  {cont__13_4, &frame__13_1, 194, 194, 3, 41},
  {entry__14_5, NULL, 209, 209, 38, 42},
  {cont__14_6, &frame__14_5, 209, 209, 30, 43},
  {cont__14_8, &frame__14_5, 209, 209, 18, 44},
  {cont__14_9, &frame__14_5, 209, 209, 15, 44},
  {entry__14_10, NULL, 209, 209, 50, 64},
  {cont__14_11, &frame__14_10, 209, 209, 47, 64},
  {entry__14_1, NULL, 207, 207, 3, 22},
  {cont__14_2, &frame__14_1, 208, 208, 3, 22},
  {cont__14_3, &frame__14_1, 209, 209, 6, 12},
  {cont__14_4, &frame__14_1, 209, 209, 3, 64},
  {entry__15_4, NULL, 212, 212, 29, 35},
  {cont__15_5, &frame__15_4, 212, 212, 29, 42},
  {cont__15_6, &frame__15_4, 212, 212, 29, 42},
  {entry__15_8, NULL, 212, 212, 45, 48},
  {entry__15_9, NULL, 212, 212, 51, 62},
  {entry__15_1, NULL, 212, 212, 6, 20},
  {cont__15_2, &frame__15_1, 212, 212, 6, 24},
  {cont__15_3, &frame__15_1, 212, 212, 6, 42},
  {cont__15_7, &frame__15_1, 212, 212, 3, 62},
  {entry__16_4, NULL, 221, 221, 43, 58},
  {entry__16_8, NULL, 222, 222, 35, 44},
  {entry__16_1, NULL, 220, 220, 3, 22},
  {cont__16_2, &frame__16_1, 221, 221, 10, 40},
  {cont__16_3, &frame__16_1, 221, 221, 3, 58},
  {cont__16_5, &frame__16_1, 222, 222, 6, 24},
  {cont__16_6, &frame__16_1, 222, 222, 6, 32},
  {cont__16_7, &frame__16_1, 222, 222, 3, 44},
  {cont__16_9, &frame__16_1, 223, 223, 3, 14},
  {entry__17_5, NULL, 233, 233, 39, 68},
  {entry__17_1, NULL, 232, 232, 3, 32},
  {cont__17_2, &frame__17_1, 233, 233, 6, 31},
  {cont__17_3, &frame__17_1, 233, 233, 6, 36},
  {cont__17_4, &frame__17_1, 233, 233, 3, 68},
  {cont__17_6, &frame__17_1, 234, 234, 3, 6},
  {entry__18_6, NULL, 246, 246, 12, 16},
  {cont__18_7, &frame__18_6, 246, 246, 9, 16},
  {entry__18_8, NULL, 247, 247, 43, 43},
  {cont__18_9, &frame__18_8, 247, 247, 29, 44},
  {cont__18_10, &frame__18_8, 247, 247, 50, 54},
  {cont__18_11, &frame__18_8, 247, 247, 12, 55},
  {cont__18_12, &frame__18_8, 247, 247, 9, 55},
  {entry__18_3, NULL, 245, 245, 9, 15},
  {cont__18_4, &frame__18_3, 245, 245, 9, 22},
  {cont__18_5, &frame__18_3, 244, 247, 7, 55},
  {entry__18_13, NULL, 248, 248, 5, 16},
  {entry__18_1, NULL, 243, 243, 5, 31},
  {cont__18_2, &frame__18_1, 242, 248, 3, 16},
  {entry__19_1, NULL, 259, 259, 3, 39},
  {cont__19_2, &frame__19_1, 260, 260, 3, 12},
  {entry__20_4, NULL, 298, 298, 26, 30},
  {cont__20_5, &frame__20_4, 298, 298, 14, 31},
  {cont__20_6, &frame__20_4, 298, 298, 7, 31},
  {entry__20_7, NULL, 300, 300, 7, 15},
  {entry__20_1, NULL, 295, 295, 3, 41},
  {cont__20_2, &frame__20_1, 297, 297, 5, 18},
  {cont__20_3, &frame__20_1, 296, 300, 3, 16},
  {cont__20_8, &frame__20_1, 300, 300, 16, 16},
  {entry__21_4, NULL, 329, 329, 26, 30},
  {cont__21_5, &frame__21_4, 329, 329, 14, 31},
  {cont__21_6, &frame__21_4, 329, 329, 7, 31},
  {entry__21_7, NULL, 331, 331, 7, 16},
  {entry__21_1, NULL, 326, 326, 3, 41},
  {cont__21_2, &frame__21_1, 328, 328, 5, 18},
  {cont__21_3, &frame__21_1, 327, 331, 3, 17},
  {cont__21_8, &frame__21_1, 331, 331, 17, 17},
  {entry__22_4, NULL, 367, 367, 24, 30},
  {cont__22_5, &frame__22_4, 367, 367, 33, 33},
  {cont__22_6, &frame__22_4, 367, 367, 14, 34},
  {cont__22_7, &frame__22_4, 367, 367, 7, 34},
  {entry__22_8, NULL, 369, 369, 7, 15},
  {entry__22_1, NULL, 364, 364, 3, 40},
  {cont__22_2, &frame__22_1, 366, 366, 5, 18},
  {cont__22_3, &frame__22_1, 365, 369, 3, 16},
  {cont__22_9, &frame__22_1, 369, 369, 16, 16},
  {entry__23_4, NULL, 398, 398, 24, 30},
  {cont__23_5, &frame__23_4, 398, 398, 33, 33},
  {cont__23_6, &frame__23_4, 398, 398, 14, 34},
  {cont__23_7, &frame__23_4, 398, 398, 7, 34},
  {entry__23_8, NULL, 400, 400, 7, 16},
  {entry__23_1, NULL, 395, 395, 3, 40},
  {cont__23_2, &frame__23_1, 397, 397, 5, 18},
  {cont__23_3, &frame__23_1, 396, 400, 3, 17},
  {cont__23_9, &frame__23_1, 400, 400, 17, 17},
  {entry__24_4, NULL, 432, 432, 29, 29},
  {cont__24_5, &frame__24_4, 432, 432, 14, 30},
  {cont__24_6, &frame__24_4, 432, 432, 7, 30},
  {entry__24_7, NULL, 434, 434, 7, 15},
  {entry__24_1, NULL, 429, 429, 3, 41},
  {cont__24_2, &frame__24_1, 431, 431, 5, 18},
  {cont__24_3, &frame__24_1, 430, 434, 3, 16},
  {cont__24_8, &frame__24_1, 434, 434, 16, 16},
  {entry__25_4, NULL, 454, 454, 29, 29},
  {cont__25_5, &frame__25_4, 454, 454, 14, 30},
  {cont__25_6, &frame__25_4, 454, 454, 7, 30},
  {entry__25_7, NULL, 456, 456, 7, 16},
  {entry__25_1, NULL, 451, 451, 3, 41},
  {cont__25_2, &frame__25_1, 453, 453, 5, 18},
  {cont__25_3, &frame__25_1, 452, 456, 3, 17},
  {cont__25_8, &frame__25_1, 456, 456, 17, 17},
  {entry__26_4, NULL, 484, 484, 26, 32},
  {cont__26_5, &frame__26_4, 484, 484, 26, 34},
  {cont__26_6, &frame__26_4, 484, 484, 14, 35},
  {cont__26_7, &frame__26_4, 484, 484, 7, 35},
  {entry__26_8, NULL, 486, 486, 7, 15},
  {entry__26_1, NULL, 481, 481, 3, 40},
  {cont__26_2, &frame__26_1, 483, 483, 5, 18},
  {cont__26_3, &frame__26_1, 482, 486, 3, 16},
  {cont__26_9, &frame__26_1, 486, 486, 16, 16},
  {entry__27_4, NULL, 506, 506, 26, 32},
  {cont__27_5, &frame__27_4, 506, 506, 26, 34},
  {cont__27_6, &frame__27_4, 506, 506, 14, 35},
  {cont__27_7, &frame__27_4, 506, 506, 7, 35},
  {entry__27_8, NULL, 508, 508, 7, 16},
  {entry__27_1, NULL, 503, 503, 3, 40},
  {cont__27_2, &frame__27_1, 505, 505, 5, 18},
  {cont__27_3, &frame__27_1, 504, 508, 3, 17},
  {cont__27_9, &frame__27_1, 508, 508, 17, 17},
  {entry__28_1, NULL, 525, 525, 6, 27},
  {cont__28_2, &frame__28_1, 525, 525, 6, 43},
  {cont__28_3, &frame__28_1, 525, 525, 3, 43},
  {entry__29_1, NULL, 536, 536, 6, 23},
  {cont__29_2, &frame__29_1, 536, 536, 6, 34},
  {cont__29_3, &frame__29_1, 536, 536, 3, 34},
  {entry__30_10, NULL, 550, 550, 51, 61},
  {entry__30_3, NULL, 550, 550, 28, 28},
  {cont__30_4, &frame__30_3, 550, 550, 14, 29},
  {cont__30_5, &frame__30_3, 550, 550, 8, 37},
  {cont__30_6, &frame__30_3, 550, 550, 42, 46},
  {cont__30_7, &frame__30_3, 550, 550, 42, 48},
  {cont__30_8, &frame__30_3, 550, 550, 8, 48},
  {cont__30_9, &frame__30_3, 550, 550, 5, 61},
  {entry__30_1, NULL, 548, 548, 3, 22},
  {cont__30_2, &frame__30_1, 549, 550, 3, 61},
  {cont__30_11, &frame__30_1, 551, 551, 3, 10},
  {entry__31_4, NULL, 564, 564, 38, 40},
  {cont__31_5, &frame__31_4, 564, 564, 43, 43},
  {cont__31_6, &frame__31_4, 564, 564, 27, 44},
  {cont__31_7, &frame__31_4, 564, 564, 20, 44},
  {entry__31_1, NULL, 563, 563, 3, 23},
  {cont__31_2, &frame__31_1, 564, 564, 6, 17},
  {cont__31_3, &frame__31_1, 564, 564, 3, 44},
  {cont__31_8, &frame__31_1, 565, 565, 3, 9},
  {entry__32_10, NULL, 579, 579, 71, 73},
  {cont__32_11, &frame__32_10, 579, 579, 58, 74},
  {cont__32_12, &frame__32_10, 579, 579, 51, 74},
  {entry__32_3, NULL, 579, 579, 28, 28},
  {cont__32_4, &frame__32_3, 579, 579, 14, 29},
  {cont__32_5, &frame__32_3, 579, 579, 8, 37},
  {cont__32_6, &frame__32_3, 579, 579, 42, 46},
  {cont__32_7, &frame__32_3, 579, 579, 42, 48},
  {cont__32_8, &frame__32_3, 579, 579, 8, 48},
  {cont__32_9, &frame__32_3, 579, 579, 5, 74},
  {entry__32_1, NULL, 577, 577, 3, 22},
  {cont__32_2, &frame__32_1, 578, 579, 3, 74},
  {cont__32_13, &frame__32_1, 580, 580, 3, 9},
  {entry__33_6, NULL, 585, 585, 22, 27},
  {cont__33_7, &frame__33_6, 585, 585, 22, 34},
  {cont__33_8, &frame__33_6, 585, 585, 22, 34},
  {cont__33_9, &frame__33_6, 585, 585, 22, 34},
  {entry__33_11, NULL, 585, 585, 37, 45},
  {cont__33_12, &frame__33_11, 585, 585, 45, 45},
  {entry__33_3, NULL, 585, 585, 12, 17},
  {cont__33_4, &frame__33_3, 585, 585, 12, 17},
  {cont__33_5, &frame__33_3, 585, 585, 12, 34},
  {cont__33_10, &frame__33_3, 585, 585, 9, 45},
  {entry__33_17, NULL, 586, 586, 22, 27},
  {cont__33_18, &frame__33_17, 586, 586, 22, 34},
  {cont__33_19, &frame__33_17, 586, 586, 22, 34},
  {cont__33_20, &frame__33_17, 586, 586, 22, 34},
  {entry__33_22, NULL, 586, 586, 37, 46},
  {cont__33_23, &frame__33_22, 586, 586, 46, 46},
  {entry__33_14, NULL, 586, 586, 12, 17},
  {cont__33_15, &frame__33_14, 586, 586, 12, 17},
  {cont__33_16, &frame__33_14, 586, 586, 12, 34},
  {cont__33_21, &frame__33_14, 586, 586, 9, 46},
  {entry__33_1, NULL, 584, 584, 3, 20},
  {cont__33_2, &frame__33_1, 585, 585, 3, 45},
  {cont__33_13, &frame__33_1, 586, 586, 3, 46},
  {cont__33_24, &frame__33_1, 587, 587, 3, 16},
  {cont__33_25, &frame__33_1, 587, 587, 16, 16},
  {entry__34_1, NULL, 590, 590, 3, 11},
  {cont__34_2, &frame__34_1, 591, 591, 25, 53},
  {cont__34_3, &frame__34_1, 591, 591, 20, 54},
  {cont__34_4, &frame__34_1, 591, 591, 20, 60},
  {cont__34_6, &frame__34_1, 591, 591, 3, 60},
  {cont__34_7, &frame__34_1, 591, 591, 60, 60},
  {entry__35_7, NULL, 602, 602, 32, 36},
  {cont__35_8, &frame__35_7, 602, 602, 19, 37},
  {cont__35_9, &frame__35_7, 602, 602, 7, 37},
  {cont__35_10, &frame__35_7, 603, 603, 19, 25},
  {cont__35_11, &frame__35_7, 603, 603, 28, 28},
  {cont__35_12, &frame__35_7, 603, 603, 7, 28},
  {cont__35_13, &frame__35_7, 603, 603, 28, 28},
  {entry__35_4, NULL, 600, 600, 5, 44},
  {cont__35_5, &frame__35_4, 601, 601, 8, 21},
  {cont__35_6, &frame__35_4, 601, 603, 5, 28},
  {cont__35_14, &frame__35_4, 604, 604, 8, 21},
  {cont__35_15, &frame__35_4, 604, 604, 5, 21},
  {entry__35_19, NULL, 605, 605, 27, 42},
  {cont__35_20, &frame__35_19, 605, 605, 42, 42},
  {entry__35_1, NULL, 596, 596, 5, 13},
  {cont__35_3, &frame__35_1, },
  {cont__35_2, &frame__35_1, 599, 604, 3, 21},
  {cont__35_16, &frame__35_1, 605, 605, 6, 20},
  {cont__35_17, &frame__35_1, 605, 605, 6, 24},
  {cont__35_18, &frame__35_1, 605, 605, 3, 42},
  {cont__35_21, &frame__35_1, 606, 606, 3, 10},
  {entry__36_3, NULL, 616, 616, 7, 23},
  {cont__36_4, &frame__36_3, 616, 616, 23, 23},
  {entry__36_5, NULL, 618, 618, 7, 28},
  {cont__36_6, &frame__36_5, 618, 618, 28, 28},
  {entry__36_1, NULL, 614, 618, 3, 29},
  {cont__36_7, &frame__36_1, 619, 619, 3, 9},
  {entry__37_5, NULL, 626, 626, 19, 25},
  {cont__37_6, &frame__37_5, 626, 626, 28, 28},
  {cont__37_7, &frame__37_5, 626, 626, 7, 28},
  {cont__37_8, &frame__37_5, 627, 627, 7, 12},
  {cont__37_9, &frame__37_5, 627, 627, 12, 12},
  {entry__37_2, NULL, 624, 624, 5, 39},
  {cont__37_3, &frame__37_2, 625, 625, 8, 21},
  {cont__37_4, &frame__37_2, 625, 627, 5, 12},
  {cont__37_10, &frame__37_2, 628, 628, 8, 21},
  {cont__37_11, &frame__37_2, 628, 628, 5, 21},
  {entry__37_1, NULL, 623, 628, 3, 21},
  {cont__37_12, &frame__37_1, 629, 629, 3, 6},
  {entry__38_1, NULL, 632, 632, 6, 30},
  {cont__38_2, &frame__38_1, 632, 632, 35, 49},
  {cont__38_3, &frame__38_1, 632, 632, 6, 49},
  {cont__38_4, &frame__38_1, 632, 632, 3, 49},
  {entry__39_1, NULL, 635, 635, 3, 38},
  {cont__39_2, &frame__39_1, 636, 636, 6, 19},
  {cont__39_3, &frame__39_1, 636, 636, 3, 19},
  {entry__41_2, NULL, 940, 940, 20, 36},
  {cont__41_3, &frame__41_2, 940, 940, 5, 36},
  {cont__41_4, &frame__41_2, 941, 941, 5, 12},
  {cont__41_5, &frame__41_2, 941, 941, 12, 12},
  {entry__41_17, NULL, 951, 951, 15, 39},
  {cont__41_18, &frame__41_17, 951, 951, 39, 39},
  {entry__41_19, NULL, 953, 953, 15, 30},
  {cont__41_20, &frame__41_19, 953, 953, 30, 30},
  {entry__41_12, NULL, 947, 947, 16, 20},
  {cont__41_13, &frame__41_12, 947, 947, 11, 20},
  {cont__41_14, &frame__41_12, 948, 948, 11, 45},
  {cont__41_15, &frame__41_12, 950, 950, 13, 33},
  {cont__41_16, &frame__41_12, 949, 953, 11, 31},
  {entry__41_21, NULL, 955, 955, 16, 20},
  {cont__41_22, &frame__41_21, 955, 955, 11, 20},
  {cont__41_23, &frame__41_21, 956, 956, 24, 31},
  {cont__41_24, &frame__41_21, 956, 956, 11, 31},
  {cont__41_25, &frame__41_21, 956, 956, 31, 31},
  {entry__41_9, NULL, 946, 946, 9, 18},
  {cont__41_10, &frame__41_9, 946, 946, 9, 18},
  {cont__41_11, &frame__41_9, 945, 956, 7, 32},
  {entry__41_6, NULL, 944, 944, 8, 22},
  {cont__41_7, &frame__41_6, 944, 944, 8, 22},
  {cont__41_8, &frame__41_6, 944, 956, 5, 33},
  {entry__41_1, NULL, 943, 956, 3, 34},
  {cont__41_26, &frame__41_1, 957, 957, 8, 22},
  {cont__41_27, &frame__41_1, 957, 957, 3, 22},
  {cont__41_28, &frame__41_1, 958, 958, 3, 11},
  {entry__42_14, NULL, 991, 991, 15, 42},
  {cont__42_15, &frame__42_14, 991, 991, 42, 42},
  {entry__42_16, NULL, 993, 993, 44, 60},
  {cont__42_17, &frame__42_16, 993, 993, 32, 61},
  {cont__42_18, &frame__42_16, 993, 993, 15, 61},
  {cont__42_19, &frame__42_16, 993, 993, 61, 61},
  {entry__42_12, NULL, 990, 990, 13, 35},
  {cont__42_13, &frame__42_12, 989, 993, 11, 62},
  {cont__42_20, &frame__42_12, 994, 994, 23, 27},
  {cont__42_21, &frame__42_12, 994, 994, 30, 30},
  {cont__42_22, &frame__42_12, 994, 994, 11, 30},
  {cont__42_23, &frame__42_12, 995, 995, 11, 15},
  {entry__42_7, NULL, 985, 985, 9, 31},
  {cont__42_8, &frame__42_7, 986, 986, 9, 34},
  {cont__42_9, &frame__42_7, 987, 987, 9, 43},
  {cont__42_10, &frame__42_7, 988, 988, 12, 25},
  {cont__42_11, &frame__42_7, 988, 995, 9, 15},
  {entry__42_6, NULL, 984, 995, 7, 16},
  {cont__42_24, &frame__42_6, 996, 996, 22, 28},
  {cont__42_25, &frame__42_6, 996, 996, 7, 28},
  {cont__42_26, &frame__42_6, 997, 997, 22, 22},
  {cont__42_27, &frame__42_6, 997, 997, 7, 22},
  {cont__42_28, &frame__42_6, 997, 997, 22, 22},
  {entry__42_5, NULL, 983, 997, 5, 22},
  {entry__42_2, NULL, 982, 982, 12, 26},
  {cont__42_3, &frame__42_2, 982, 982, 12, 30},
  {cont__42_4, &frame__42_2, 982, 997, 9, 23},
  {entry__42_1, NULL, 982, 997, 3, 23},
  {cont__42_29, &frame__42_1, 998, 998, 3, 13},
  {entry__44_3, NULL, 1005, 1005, 33, 42},
  {cont__44_5, &frame__44_3, 1005, 1005, 30, 42},
  {entry__44_6, NULL, 1005, 1005, 48, 71},
  {cont__44_7, &frame__44_6, 1005, 1005, 45, 71},
  {entry__44_1, NULL, 1005, 1005, 22, 27},
  {cont__44_2, &frame__44_1, 1005, 1005, 19, 71},
  {entry__45_14, NULL, 1013, 1013, 36, 42},
  {cont__45_15, &frame__45_14, 1013, 1013, 36, 52},
  {cont__45_16, &frame__45_14, 1013, 1013, 36, 52},
  {entry__45_18, NULL, 1013, 1013, 55, 78},
  {cont__45_19, &frame__45_18, 1013, 1013, 78, 78},
  {entry__45_3, NULL, 1009, 1009, 5, 31},
  {cont__45_4, &frame__45_3, 1012, 1012, 31, 53},
  {cont__45_5, &frame__45_3, 1012, 1012, 15, 54},
  {cont__45_6, &frame__45_3, 1012, 1012, 7, 54},
  {cont__45_7, &frame__45_3, 1012, 1012, 58, 77},
  {cont__45_9, &frame__45_3, 1012, 1012, 7, 77},
  {cont__45_10, &frame__45_3, 1010, 1012, 5, 77},
  {cont__45_11, &frame__45_3, 1013, 1013, 12, 26},
  {cont__45_12, &frame__45_3, 1013, 1013, 12, 31},
  {cont__45_13, &frame__45_3, 1013, 1013, 12, 52},
  {cont__45_17, &frame__45_3, 1013, 1013, 5, 78},
  {entry__45_1, NULL, 1008, 1008, 6, 15},
  {cont__45_2, &frame__45_1, 1008, 1013, 3, 78},
  {cont__45_20, &frame__45_1, 1014, 1014, 3, 9},
  {entry__46_7, NULL, 1028, 1028, 32, 36},
  {cont__46_8, &frame__46_7, 1028, 1028, 19, 37},
  {cont__46_9, &frame__46_7, 1028, 1028, 11, 37},
  {entry__46_10, NULL, 1030, 1030, 29, 33},
  {cont__46_11, &frame__46_10, 1030, 1030, 16, 34},
  {cont__46_12, &frame__46_10, 1030, 1030, 11, 34},
  {entry__46_18, NULL, 1032, 1032, 30, 56},
  {cont__46_19, &frame__46_18, 1032, 1032, 30, 56},
  {entry__46_4, NULL, 1027, 1027, 9, 32},
  {cont__46_5, &frame__46_4, 1027, 1027, 9, 37},
  {cont__46_6, &frame__46_4, 1026, 1030, 7, 35},
  {cont__46_13, &frame__46_4, 1031, 1031, 24, 28},
  {cont__46_14, &frame__46_4, 1031, 1031, 31, 31},
  {cont__46_15, &frame__46_4, 1031, 1031, 7, 32},
  {cont__46_16, &frame__46_4, 1032, 1032, 10, 25},
  {cont__46_17, &frame__46_4, 1032, 1032, 10, 56},
  {cont__46_20, &frame__46_4, 1032, 1032, 7, 62},
  {cont__46_21, &frame__46_4, 1033, 1033, 37, 40},
  {cont__46_22, &frame__46_4, 1033, 1033, 7, 40},
  {entry__46_29, NULL, 1038, 1038, 13, 24},
  {entry__46_30, NULL, 1040, 1040, 13, 21},
  {entry__46_26, NULL, 1037, 1037, 11, 34},
  {cont__46_27, &frame__46_26, 1037, 1037, 11, 39},
  {cont__46_28, &frame__46_26, 1036, 1040, 9, 22},
  {entry__46_23, NULL, 1035, 1035, 10, 24},
  {cont__46_24, &frame__46_23, 1035, 1035, 10, 28},
  {cont__46_25, &frame__46_23, 1035, 1040, 7, 23},
  {entry__46_1, NULL, 1023, 1023, 3, 31},
  {cont__46_2, &frame__46_1, 1025, 1025, 5, 18},
  {cont__46_3, &frame__46_1, 1024, 1040, 3, 25},
  {entry__47_1, NULL, 1042, 1042, 41, 63},
  {cont__47_2, &frame__47_1, 1042, 1042, 38, 63},
  {entry__48_1, NULL, 1044, 1044, 41, 63},
  {cont__48_2, &frame__48_1, 1044, 1044, 38, 63},
  {entry__49_5, NULL, 1054, 1054, 23, 39},
  {cont__49_6, &frame__49_5, 1054, 1054, 13, 39},
  {cont__49_7, &frame__49_5, 1055, 1055, 27, 27},
  {entry__49_8, NULL, 1057, 1057, 23, 39},
  {cont__49_9, &frame__49_8, 1057, 1057, 13, 39},
  {cont__49_10, &frame__49_8, 1057, 1057, 39, 39},
  {entry__49_4, NULL, 1052, 1057, 9, 40},
  {entry__49_11, NULL, 1059, 1059, 9, 21},
  {cont__49_12, &frame__49_11, 1060, 1060, 22, 22},
  {entry__49_2, NULL, 1051, 1051, 7, 31},
  {cont__49_3, &frame__49_2, 1050, 1060, 5, 23},
  {entry__49_1, NULL, 1049, 1060, 3, 24},
  {cont__49_13, &frame__49_1, 1061, 1061, 3, 8},
  {entry__50_1, NULL, 1128, 1128, 52, 73},
  {entry__51_1, NULL, 1130, 1130, 57, 78},
  {entry__52_2, NULL, 1137, 1137, 24, 43},
  {cont__52_3, &frame__52_2, 1137, 1137, 43, 43},
  {entry__52_1, NULL, 1139, 1139, 3, 6},
  {cont__52_4, &frame__52_1, 1139, 1139, 6, 6},
  {entry__53_4, NULL, 1145, 1145, 43, 51},
  {cont__53_5, &frame__53_4, 1145, 1145, 31, 51},
  {cont__53_6, &frame__53_4, 1145, 1145, 51, 51},
  {entry__53_3, NULL, 1145, 1145, 7, 51},
  {entry__53_8, NULL, 1147, 1147, 31, 45},
  {cont__53_9, &frame__53_8, 1147, 1147, 45, 45},
  {entry__53_7, NULL, 1147, 1147, 7, 45},
  {entry__53_1, NULL, 1144, 1144, 5, 19},
  {cont__53_2, &frame__53_1, 1143, 1147, 3, 46},
  {cont__53_10, &frame__53_1, 1148, 1148, 3, 8}
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
  allocate_initialized_frame_gc(0, 294);
  // 640: '¡' = "!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__161;
  arguments->slots[1] = string__93_1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_2;
}
static void cont__93_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 641: '¢' = "(cent)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__162;
  arguments->slots[1] = string__93_3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_4;
}
static void cont__93_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 642: '£' = "(pound)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__163;
  arguments->slots[1] = string__93_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_6;
}
static void cont__93_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 643: '¤' = "?"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__164;
  arguments->slots[1] = string__93_7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_8;
}
static void cont__93_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 644: '¥' = "(yen)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__165;
  arguments->slots[1] = string__93_9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_10;
}
static void cont__93_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 645: '¦' = "|"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__166;
  arguments->slots[1] = string__93_11;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_12;
}
static void cont__93_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 646: '§' = "$"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__167;
  arguments->slots[1] = string__93_13;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_14;
}
static void cont__93_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 647: '¨' = "@quot;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__168;
  arguments->slots[1] = string__93_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_16;
}
static void cont__93_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 648: '©' = "(c)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__169;
  arguments->slots[1] = string__93_17;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_18;
}
static void cont__93_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 649: 'ª' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__170;
  arguments->slots[1] = string__93_19;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_20;
}
static void cont__93_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 650: '«' = "<<"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__171;
  arguments->slots[1] = string__93_21;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_22;
}
static void cont__93_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 651: '¬' = "(not)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__172;
  arguments->slots[1] = string__93_23;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_24;
}
static void cont__93_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 652: '­' = "(shy)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__173;
  arguments->slots[1] = string__93_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_26;
}
static void cont__93_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 653: '®' = "(r)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__174;
  arguments->slots[1] = string__93_27;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_28;
}
static void cont__93_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 654: '¯' = "~"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__175;
  arguments->slots[1] = string__93_29;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_30;
}
static void cont__93_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 655: '°' = "(grad)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__176;
  arguments->slots[1] = string__93_31;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_32;
}
static void cont__93_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 656: '±' = "+/-"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__177;
  arguments->slots[1] = string__93_33;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_34;
}
static void cont__93_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  // 657: '²' = "^2"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__178;
  arguments->slots[1] = string__93_35;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_36;
}
static void cont__93_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 658: '³' = "^3"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__179;
  arguments->slots[1] = string__93_37;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_38;
}
static void cont__93_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__19 */ = arguments->slots[0];
  // 659: '´' = "'"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__180;
  arguments->slots[1] = string__93_39;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_40;
}
static void cont__93_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__20 */ = arguments->slots[0];
  // 660: 'µ' = "(mu)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__181;
  arguments->slots[1] = string__93_41;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_42;
}
static void cont__93_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__21 */ = arguments->slots[0];
  // 661: '¶' = "(par)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__182;
  arguments->slots[1] = string__93_43;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_44;
}
static void cont__93_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__22 */ = arguments->slots[0];
  // 662: '·' = "."
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__183;
  arguments->slots[1] = string__93_45;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_46;
}
static void cont__93_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__23 */ = arguments->slots[0];
  // 663: '¸' = ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__184;
  arguments->slots[1] = string__93_47;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_48;
}
static void cont__93_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__24 */ = arguments->slots[0];
  // 664: '¹' = "^1"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__185;
  arguments->slots[1] = string__93_49;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_50;
}
static void cont__93_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[24] /* temp__25 */ = arguments->slots[0];
  // 665: 'º' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__186;
  arguments->slots[1] = string__93_51;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_52;
}
static void cont__93_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[25] /* temp__26 */ = arguments->slots[0];
  // 666: '»' = ">>"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__187;
  arguments->slots[1] = string__93_53;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_54;
}
static void cont__93_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[26] /* temp__27 */ = arguments->slots[0];
  // 667: '¼' = "1/4"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__188;
  arguments->slots[1] = string__93_55;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_56;
}
static void cont__93_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[27] /* temp__28 */ = arguments->slots[0];
  // 668: '½' = "1/2"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__189;
  arguments->slots[1] = string__93_57;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_58;
}
static void cont__93_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[28] /* temp__29 */ = arguments->slots[0];
  // 669: '¾' = "3/4"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__190;
  arguments->slots[1] = string__93_59;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_60;
}
static void cont__93_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[29] /* temp__30 */ = arguments->slots[0];
  // 670: '¿' = "?"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__191;
  arguments->slots[1] = string__93_61;
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
  frame->slots[30] /* temp__31 */ = arguments->slots[0];
  // 671: 'À' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__192;
  arguments->slots[1] = string__93_63;
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
  frame->slots[31] /* temp__32 */ = arguments->slots[0];
  // 672: 'Á' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__193;
  arguments->slots[1] = string__93_65;
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
  frame->slots[32] /* temp__33 */ = arguments->slots[0];
  // 673: 'Â' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__194;
  arguments->slots[1] = string__93_67;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_68;
}
static void cont__93_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__34 */ = arguments->slots[0];
  // 674: 'Ã' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__195;
  arguments->slots[1] = string__93_69;
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
  frame->slots[34] /* temp__35 */ = arguments->slots[0];
  // 675: 'Ä' = "Ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__196;
  arguments->slots[1] = string__93_71;
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
  frame->slots[35] /* temp__36 */ = arguments->slots[0];
  // 676: 'Å' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__197;
  arguments->slots[1] = string__93_73;
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
  frame->slots[36] /* temp__37 */ = arguments->slots[0];
  // 677: 'Æ' = "AE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__198;
  arguments->slots[1] = string__93_75;
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
  frame->slots[37] /* temp__38 */ = arguments->slots[0];
  // 678: 'Ç' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__199;
  arguments->slots[1] = string__93_77;
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
  frame->slots[38] /* temp__39 */ = arguments->slots[0];
  // 679: 'È' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__200;
  arguments->slots[1] = string__93_79;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_80;
}
static void cont__93_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[39] /* temp__40 */ = arguments->slots[0];
  // 680: 'É' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__201;
  arguments->slots[1] = string__93_81;
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
  frame->slots[40] /* temp__41 */ = arguments->slots[0];
  // 681: 'Ê' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__202;
  arguments->slots[1] = string__93_83;
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
  frame->slots[41] /* temp__42 */ = arguments->slots[0];
  // 682: 'Ë' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__203;
  arguments->slots[1] = string__93_85;
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
  frame->slots[42] /* temp__43 */ = arguments->slots[0];
  // 683: 'Ì' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__204;
  arguments->slots[1] = string__93_87;
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
  frame->slots[43] /* temp__44 */ = arguments->slots[0];
  // 684: 'Í' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__205;
  arguments->slots[1] = string__93_89;
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
  frame->slots[44] /* temp__45 */ = arguments->slots[0];
  // 685: 'Î' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__206;
  arguments->slots[1] = string__93_91;
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
  frame->slots[45] /* temp__46 */ = arguments->slots[0];
  // 686: 'Ï' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__207;
  arguments->slots[1] = string__93_93;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_94;
}
static void cont__93_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[46] /* temp__47 */ = arguments->slots[0];
  // 687: 'Ð' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__208;
  arguments->slots[1] = string__93_95;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_96;
}
static void cont__93_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[47] /* temp__48 */ = arguments->slots[0];
  // 688: 'Ñ' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__209;
  arguments->slots[1] = string__93_97;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_98;
}
static void cont__93_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[48] /* temp__49 */ = arguments->slots[0];
  // 689: 'Ò' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__210;
  arguments->slots[1] = string__93_99;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_100;
}
static void cont__93_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[49] /* temp__50 */ = arguments->slots[0];
  // 690: 'Ó' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__211;
  arguments->slots[1] = string__93_101;
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
  frame->slots[50] /* temp__51 */ = arguments->slots[0];
  // 691: 'Ô' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__212;
  arguments->slots[1] = string__93_103;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_104;
}
static void cont__93_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[51] /* temp__52 */ = arguments->slots[0];
  // 692: 'Õ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__213;
  arguments->slots[1] = string__93_105;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_106;
}
static void cont__93_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[52] /* temp__53 */ = arguments->slots[0];
  // 693: 'Ö' = "Oe"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__214;
  arguments->slots[1] = string__93_107;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_108;
}
static void cont__93_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[53] /* temp__54 */ = arguments->slots[0];
  // 694: '×' = "x"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__215;
  arguments->slots[1] = string__93_109;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_110;
}
static void cont__93_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[54] /* temp__55 */ = arguments->slots[0];
  // 695: 'Ø' = "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__216;
  arguments->slots[1] = string__93_111;
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
  frame->slots[55] /* temp__56 */ = arguments->slots[0];
  // 696: 'Ù' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__217;
  arguments->slots[1] = string__93_113;
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
  frame->slots[56] /* temp__57 */ = arguments->slots[0];
  // 697: 'Ú' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__218;
  arguments->slots[1] = string__93_115;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_116;
}
static void cont__93_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[57] /* temp__58 */ = arguments->slots[0];
  // 698: 'Û' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__219;
  arguments->slots[1] = string__93_117;
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
  frame->slots[58] /* temp__59 */ = arguments->slots[0];
  // 699: 'Ü' = "Ue"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__220;
  arguments->slots[1] = string__93_119;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_120;
}
static void cont__93_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[59] /* temp__60 */ = arguments->slots[0];
  // 700: 'Ý' = "Y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__221;
  arguments->slots[1] = string__93_121;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_122;
}
static void cont__93_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[60] /* temp__61 */ = arguments->slots[0];
  // 701: 'Þ' = "p"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__222;
  arguments->slots[1] = string__93_123;
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
  frame->slots[61] /* temp__62 */ = arguments->slots[0];
  // 702: 'ß' = "ss"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__223;
  arguments->slots[1] = string__93_125;
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
  frame->slots[62] /* temp__63 */ = arguments->slots[0];
  // 703: 'à' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__224;
  arguments->slots[1] = string__93_127;
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
  frame->slots[63] /* temp__64 */ = arguments->slots[0];
  // 704: 'á' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__225;
  arguments->slots[1] = string__93_129;
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
  frame->slots[64] /* temp__65 */ = arguments->slots[0];
  // 705: 'â' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__226;
  arguments->slots[1] = string__93_131;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_132;
}
static void cont__93_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[65] /* temp__66 */ = arguments->slots[0];
  // 706: 'ã' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__227;
  arguments->slots[1] = string__93_133;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_134;
}
static void cont__93_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[66] /* temp__67 */ = arguments->slots[0];
  // 707: 'ä' = "ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__228;
  arguments->slots[1] = string__93_135;
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
  frame->slots[67] /* temp__68 */ = arguments->slots[0];
  // 708: 'å' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__229;
  arguments->slots[1] = string__93_137;
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
  frame->slots[68] /* temp__69 */ = arguments->slots[0];
  // 709: 'æ' = "ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__230;
  arguments->slots[1] = string__93_139;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_140;
}
static void cont__93_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[69] /* temp__70 */ = arguments->slots[0];
  // 710: 'ç' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__231;
  arguments->slots[1] = string__93_141;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_142;
}
static void cont__93_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[70] /* temp__71 */ = arguments->slots[0];
  // 711: 'è' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__232;
  arguments->slots[1] = string__93_143;
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
  frame->slots[71] /* temp__72 */ = arguments->slots[0];
  // 712: 'é' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__233;
  arguments->slots[1] = string__93_145;
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
  frame->slots[72] /* temp__73 */ = arguments->slots[0];
  // 713: 'ê' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__234;
  arguments->slots[1] = string__93_147;
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
  frame->slots[73] /* temp__74 */ = arguments->slots[0];
  // 714: 'ë' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__235;
  arguments->slots[1] = string__93_149;
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
  frame->slots[74] /* temp__75 */ = arguments->slots[0];
  // 715: 'ì' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__236;
  arguments->slots[1] = string__93_151;
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
  frame->slots[75] /* temp__76 */ = arguments->slots[0];
  // 716: 'í' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__237;
  arguments->slots[1] = string__93_153;
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
  frame->slots[76] /* temp__77 */ = arguments->slots[0];
  // 717: 'î' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__238;
  arguments->slots[1] = string__93_155;
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
  frame->slots[77] /* temp__78 */ = arguments->slots[0];
  // 718: 'ï' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__239;
  arguments->slots[1] = string__93_157;
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
  frame->slots[78] /* temp__79 */ = arguments->slots[0];
  // 719: 'ð' = "d"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__240;
  arguments->slots[1] = string__93_159;
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
  frame->slots[79] /* temp__80 */ = arguments->slots[0];
  // 720: 'ñ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__241;
  arguments->slots[1] = string__93_161;
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
  frame->slots[80] /* temp__81 */ = arguments->slots[0];
  // 721: 'ò' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__242;
  arguments->slots[1] = string__93_163;
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
  frame->slots[81] /* temp__82 */ = arguments->slots[0];
  // 722: 'ó' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__243;
  arguments->slots[1] = string__93_165;
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
  frame->slots[82] /* temp__83 */ = arguments->slots[0];
  // 723: 'ô' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__244;
  arguments->slots[1] = string__93_167;
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
  frame->slots[83] /* temp__84 */ = arguments->slots[0];
  // 724: 'õ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__245;
  arguments->slots[1] = string__93_169;
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
  frame->slots[84] /* temp__85 */ = arguments->slots[0];
  // 725: 'ö' = "oe"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__246;
  arguments->slots[1] = string__93_171;
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
  frame->slots[85] /* temp__86 */ = arguments->slots[0];
  // 726: '÷' = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__247;
  arguments->slots[1] = string__93_173;
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
  frame->slots[86] /* temp__87 */ = arguments->slots[0];
  // 727: 'ø' = "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__248;
  arguments->slots[1] = string__93_175;
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
  frame->slots[87] /* temp__88 */ = arguments->slots[0];
  // 728: 'ù' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__249;
  arguments->slots[1] = string__93_177;
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
  frame->slots[88] /* temp__89 */ = arguments->slots[0];
  // 729: 'ú' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__250;
  arguments->slots[1] = string__93_179;
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
  frame->slots[89] /* temp__90 */ = arguments->slots[0];
  // 730: 'û' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__251;
  arguments->slots[1] = string__93_181;
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
  frame->slots[90] /* temp__91 */ = arguments->slots[0];
  // 731: 'ü' = "ue"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__252;
  arguments->slots[1] = string__93_183;
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
  frame->slots[91] /* temp__92 */ = arguments->slots[0];
  // 732: 'ý' = "y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__253;
  arguments->slots[1] = string__93_185;
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
  frame->slots[92] /* temp__93 */ = arguments->slots[0];
  // 733: 'þ' = "p"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__254;
  arguments->slots[1] = string__93_187;
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
  frame->slots[93] /* temp__94 */ = arguments->slots[0];
  // 734: 'ÿ' = "y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__255;
  arguments->slots[1] = string__93_189;
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
  frame->slots[94] /* temp__95 */ = arguments->slots[0];
  // 735: 'Ā' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__256;
  arguments->slots[1] = string__93_191;
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
  frame->slots[95] /* temp__96 */ = arguments->slots[0];
  // 736: 'ā' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__257;
  arguments->slots[1] = string__93_193;
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
  frame->slots[96] /* temp__97 */ = arguments->slots[0];
  // 737: 'Ă' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__258;
  arguments->slots[1] = string__93_195;
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
  frame->slots[97] /* temp__98 */ = arguments->slots[0];
  // 738: 'ă' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__259;
  arguments->slots[1] = string__93_197;
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
  frame->slots[98] /* temp__99 */ = arguments->slots[0];
  // 739: 'Ą' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__260;
  arguments->slots[1] = string__93_199;
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
  frame->slots[99] /* temp__100 */ = arguments->slots[0];
  // 740: 'ą' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__261;
  arguments->slots[1] = string__93_201;
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
  frame->slots[100] /* temp__101 */ = arguments->slots[0];
  // 741: 'Ć' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__262;
  arguments->slots[1] = string__93_203;
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
  frame->slots[101] /* temp__102 */ = arguments->slots[0];
  // 742: 'ć' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__263;
  arguments->slots[1] = string__93_205;
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
  frame->slots[102] /* temp__103 */ = arguments->slots[0];
  // 743: 'Ĉ' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__264;
  arguments->slots[1] = string__93_207;
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
  frame->slots[103] /* temp__104 */ = arguments->slots[0];
  // 744: 'ĉ' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__265;
  arguments->slots[1] = string__93_209;
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
  frame->slots[104] /* temp__105 */ = arguments->slots[0];
  // 745: 'Ċ' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__266;
  arguments->slots[1] = string__93_211;
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
  frame->slots[105] /* temp__106 */ = arguments->slots[0];
  // 746: 'ċ' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__267;
  arguments->slots[1] = string__93_213;
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
  frame->slots[106] /* temp__107 */ = arguments->slots[0];
  // 747: 'Č' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__268;
  arguments->slots[1] = string__93_215;
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
  frame->slots[107] /* temp__108 */ = arguments->slots[0];
  // 748: 'č' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__269;
  arguments->slots[1] = string__93_217;
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
  frame->slots[108] /* temp__109 */ = arguments->slots[0];
  // 749: 'Ď' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__270;
  arguments->slots[1] = string__93_219;
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
  frame->slots[109] /* temp__110 */ = arguments->slots[0];
  // 750: 'ď' = "d"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__271;
  arguments->slots[1] = string__93_221;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_222;
}
static void cont__93_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[110] /* temp__111 */ = arguments->slots[0];
  // 751: 'Đ' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__272;
  arguments->slots[1] = string__93_223;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_224;
}
static void cont__93_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[111] /* temp__112 */ = arguments->slots[0];
  // 752: 'đ' = "d"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__273;
  arguments->slots[1] = string__93_225;
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
  frame->slots[112] /* temp__113 */ = arguments->slots[0];
  // 753: 'Ē' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__274;
  arguments->slots[1] = string__93_227;
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
  frame->slots[113] /* temp__114 */ = arguments->slots[0];
  // 754: 'ē' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__275;
  arguments->slots[1] = string__93_229;
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
  frame->slots[114] /* temp__115 */ = arguments->slots[0];
  // 755: 'Ĕ' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__276;
  arguments->slots[1] = string__93_231;
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
  frame->slots[115] /* temp__116 */ = arguments->slots[0];
  // 756: 'ĕ' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__277;
  arguments->slots[1] = string__93_233;
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
  frame->slots[116] /* temp__117 */ = arguments->slots[0];
  // 757: 'Ė' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__278;
  arguments->slots[1] = string__93_235;
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
  frame->slots[117] /* temp__118 */ = arguments->slots[0];
  // 758: 'ė' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__279;
  arguments->slots[1] = string__93_237;
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
  frame->slots[118] /* temp__119 */ = arguments->slots[0];
  // 759: 'Ę' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__280;
  arguments->slots[1] = string__93_239;
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
  frame->slots[119] /* temp__120 */ = arguments->slots[0];
  // 760: 'ę' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__281;
  arguments->slots[1] = string__93_241;
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
  frame->slots[120] /* temp__121 */ = arguments->slots[0];
  // 761: 'Ě' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__282;
  arguments->slots[1] = string__93_243;
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
  frame->slots[121] /* temp__122 */ = arguments->slots[0];
  // 762: 'ě' = "e"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__283;
  arguments->slots[1] = string__93_245;
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
  frame->slots[122] /* temp__123 */ = arguments->slots[0];
  // 763: 'Ĝ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__284;
  arguments->slots[1] = string__93_247;
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
  frame->slots[123] /* temp__124 */ = arguments->slots[0];
  // 764: 'ĝ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__285;
  arguments->slots[1] = string__93_249;
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
  frame->slots[124] /* temp__125 */ = arguments->slots[0];
  // 765: 'Ğ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__286;
  arguments->slots[1] = string__93_251;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_252;
}
static void cont__93_252(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[125] /* temp__126 */ = arguments->slots[0];
  // 766: 'ğ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__287;
  arguments->slots[1] = string__93_253;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_254;
}
static void cont__93_254(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[126] /* temp__127 */ = arguments->slots[0];
  // 767: 'Ġ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__288;
  arguments->slots[1] = string__93_255;
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
  frame->slots[127] /* temp__128 */ = arguments->slots[0];
  // 768: 'ġ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__289;
  arguments->slots[1] = string__93_257;
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
  frame->slots[128] /* temp__129 */ = arguments->slots[0];
  // 769: 'Ģ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__290;
  arguments->slots[1] = string__93_259;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_260;
}
static void cont__93_260(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[129] /* temp__130 */ = arguments->slots[0];
  // 770: 'ģ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__291;
  arguments->slots[1] = string__93_261;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_262;
}
static void cont__93_262(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[130] /* temp__131 */ = arguments->slots[0];
  // 771: 'Ĥ' = "H"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__292;
  arguments->slots[1] = string__93_263;
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
  frame->slots[131] /* temp__132 */ = arguments->slots[0];
  // 772: 'ĥ' = "h"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__293;
  arguments->slots[1] = string__93_265;
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
  frame->slots[132] /* temp__133 */ = arguments->slots[0];
  // 773: 'Ħ' = "H"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__294;
  arguments->slots[1] = string__93_267;
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
  frame->slots[133] /* temp__134 */ = arguments->slots[0];
  // 774: 'ħ' = "h"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__295;
  arguments->slots[1] = string__93_269;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_270;
}
static void cont__93_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[134] /* temp__135 */ = arguments->slots[0];
  // 775: 'Ĩ' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__296;
  arguments->slots[1] = string__93_271;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_272;
}
static void cont__93_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[135] /* temp__136 */ = arguments->slots[0];
  // 776: 'ĩ' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__297;
  arguments->slots[1] = string__93_273;
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
  frame->slots[136] /* temp__137 */ = arguments->slots[0];
  // 777: 'Ī' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__298;
  arguments->slots[1] = string__93_275;
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
  frame->slots[137] /* temp__138 */ = arguments->slots[0];
  // 778: 'ī' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__299;
  arguments->slots[1] = string__93_277;
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
  frame->slots[138] /* temp__139 */ = arguments->slots[0];
  // 779: 'Ĭ' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__300;
  arguments->slots[1] = string__93_279;
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
  frame->slots[139] /* temp__140 */ = arguments->slots[0];
  // 780: 'ĭ' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__301;
  arguments->slots[1] = string__93_281;
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
  frame->slots[140] /* temp__141 */ = arguments->slots[0];
  // 781: 'Į' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__302;
  arguments->slots[1] = string__93_283;
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
  frame->slots[141] /* temp__142 */ = arguments->slots[0];
  // 782: 'į' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__303;
  arguments->slots[1] = string__93_285;
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
  frame->slots[142] /* temp__143 */ = arguments->slots[0];
  // 783: 'İ' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__304;
  arguments->slots[1] = string__93_287;
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
  frame->slots[143] /* temp__144 */ = arguments->slots[0];
  // 784: 'ı' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__305;
  arguments->slots[1] = string__93_289;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_290;
}
static void cont__93_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[144] /* temp__145 */ = arguments->slots[0];
  // 785: 'Ĳ' = "IJ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__306;
  arguments->slots[1] = string__93_291;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_292;
}
static void cont__93_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[145] /* temp__146 */ = arguments->slots[0];
  // 786: 'ĳ' = "ij"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__307;
  arguments->slots[1] = string__93_293;
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
  frame->slots[146] /* temp__147 */ = arguments->slots[0];
  // 787: 'Ĵ' = "J"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__308;
  arguments->slots[1] = string__93_295;
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
  frame->slots[147] /* temp__148 */ = arguments->slots[0];
  // 788: 'ĵ' = "j"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__309;
  arguments->slots[1] = string__93_297;
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
  frame->slots[148] /* temp__149 */ = arguments->slots[0];
  // 789: 'Ķ' = "K"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__310;
  arguments->slots[1] = string__93_299;
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
  frame->slots[149] /* temp__150 */ = arguments->slots[0];
  // 790: 'ķ' = "k"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__311;
  arguments->slots[1] = string__93_301;
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
  frame->slots[150] /* temp__151 */ = arguments->slots[0];
  // 791: 'ĸ' = "k"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__312;
  arguments->slots[1] = string__93_303;
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
  frame->slots[151] /* temp__152 */ = arguments->slots[0];
  // 792: 'Ĺ' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__313;
  arguments->slots[1] = string__93_305;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_306;
}
static void cont__93_306(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[152] /* temp__153 */ = arguments->slots[0];
  // 793: 'ĺ' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__314;
  arguments->slots[1] = string__93_307;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_308;
}
static void cont__93_308(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[153] /* temp__154 */ = arguments->slots[0];
  // 794: 'Ļ' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__315;
  arguments->slots[1] = string__93_309;
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
  frame->slots[154] /* temp__155 */ = arguments->slots[0];
  // 795: 'ļ' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__316;
  arguments->slots[1] = string__93_311;
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
  frame->slots[155] /* temp__156 */ = arguments->slots[0];
  // 796: 'Ľ' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__317;
  arguments->slots[1] = string__93_313;
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
  frame->slots[156] /* temp__157 */ = arguments->slots[0];
  // 797: 'ľ' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__318;
  arguments->slots[1] = string__93_315;
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
  frame->slots[157] /* temp__158 */ = arguments->slots[0];
  // 798: 'Ŀ' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__319;
  arguments->slots[1] = string__93_317;
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
  frame->slots[158] /* temp__159 */ = arguments->slots[0];
  // 799: 'ŀ' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__320;
  arguments->slots[1] = string__93_319;
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
  frame->slots[159] /* temp__160 */ = arguments->slots[0];
  // 800: 'Ł' = "L"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__321;
  arguments->slots[1] = string__93_321;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_322;
}
static void cont__93_322(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[160] /* temp__161 */ = arguments->slots[0];
  // 801: 'ł' = "l"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__322;
  arguments->slots[1] = string__93_323;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_324;
}
static void cont__93_324(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[161] /* temp__162 */ = arguments->slots[0];
  // 802: 'Ń' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__323;
  arguments->slots[1] = string__93_325;
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
  frame->slots[162] /* temp__163 */ = arguments->slots[0];
  // 803: 'ń' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__324;
  arguments->slots[1] = string__93_327;
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
  frame->slots[163] /* temp__164 */ = arguments->slots[0];
  // 804: 'Ņ' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__325;
  arguments->slots[1] = string__93_329;
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
  frame->slots[164] /* temp__165 */ = arguments->slots[0];
  // 805: 'ņ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__326;
  arguments->slots[1] = string__93_331;
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
  frame->slots[165] /* temp__166 */ = arguments->slots[0];
  // 806: 'Ň' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__327;
  arguments->slots[1] = string__93_333;
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
  frame->slots[166] /* temp__167 */ = arguments->slots[0];
  // 807: 'ň' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__328;
  arguments->slots[1] = string__93_335;
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
  frame->slots[167] /* temp__168 */ = arguments->slots[0];
  // 808: 'ŉ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__329;
  arguments->slots[1] = string__93_337;
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
  frame->slots[168] /* temp__169 */ = arguments->slots[0];
  // 809: 'Ŋ' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__330;
  arguments->slots[1] = string__93_339;
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
  frame->slots[169] /* temp__170 */ = arguments->slots[0];
  // 810: 'ŋ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__331;
  arguments->slots[1] = string__93_341;
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
  frame->slots[170] /* temp__171 */ = arguments->slots[0];
  // 811: 'Ō' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__332;
  arguments->slots[1] = string__93_343;
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
  frame->slots[171] /* temp__172 */ = arguments->slots[0];
  // 812: 'ō' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__333;
  arguments->slots[1] = string__93_345;
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
  frame->slots[172] /* temp__173 */ = arguments->slots[0];
  // 813: 'Ŏ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__334;
  arguments->slots[1] = string__93_347;
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
  frame->slots[173] /* temp__174 */ = arguments->slots[0];
  // 814: 'ŏ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__335;
  arguments->slots[1] = string__93_349;
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
  frame->slots[174] /* temp__175 */ = arguments->slots[0];
  // 815: 'Ő' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__336;
  arguments->slots[1] = string__93_351;
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
  frame->slots[175] /* temp__176 */ = arguments->slots[0];
  // 816: 'ő' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__337;
  arguments->slots[1] = string__93_353;
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
  frame->slots[176] /* temp__177 */ = arguments->slots[0];
  // 817: 'Œ' = "OE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__338;
  arguments->slots[1] = string__93_355;
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
  frame->slots[177] /* temp__178 */ = arguments->slots[0];
  // 818: 'œ' = "oe"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__339;
  arguments->slots[1] = string__93_357;
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
  frame->slots[178] /* temp__179 */ = arguments->slots[0];
  // 819: 'Ŕ' = "R"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__340;
  arguments->slots[1] = string__93_359;
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
  frame->slots[179] /* temp__180 */ = arguments->slots[0];
  // 820: 'ŕ' = "r"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__341;
  arguments->slots[1] = string__93_361;
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
  frame->slots[180] /* temp__181 */ = arguments->slots[0];
  // 821: 'Ŗ' = "R"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__342;
  arguments->slots[1] = string__93_363;
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
  frame->slots[181] /* temp__182 */ = arguments->slots[0];
  // 822: 'ŗ' = "r"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__343;
  arguments->slots[1] = string__93_365;
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
  frame->slots[182] /* temp__183 */ = arguments->slots[0];
  // 823: 'Ř' = "R"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__344;
  arguments->slots[1] = string__93_367;
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
  frame->slots[183] /* temp__184 */ = arguments->slots[0];
  // 824: 'ř' = "r"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__345;
  arguments->slots[1] = string__93_369;
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
  frame->slots[184] /* temp__185 */ = arguments->slots[0];
  // 825: 'Ś' = "S"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__346;
  arguments->slots[1] = string__93_371;
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
  frame->slots[185] /* temp__186 */ = arguments->slots[0];
  // 826: 'ś' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__347;
  arguments->slots[1] = string__93_373;
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
  frame->slots[186] /* temp__187 */ = arguments->slots[0];
  // 827: 'Ŝ' = "S"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__348;
  arguments->slots[1] = string__93_375;
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
  frame->slots[187] /* temp__188 */ = arguments->slots[0];
  // 828: 'ŝ' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__349;
  arguments->slots[1] = string__93_377;
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
  frame->slots[188] /* temp__189 */ = arguments->slots[0];
  // 829: 'Ş' = "S"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__350;
  arguments->slots[1] = string__93_379;
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
  frame->slots[189] /* temp__190 */ = arguments->slots[0];
  // 830: 'ş' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__351;
  arguments->slots[1] = string__93_381;
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
  frame->slots[190] /* temp__191 */ = arguments->slots[0];
  // 831: 'Š' = "S"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__352;
  arguments->slots[1] = string__93_383;
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
  frame->slots[191] /* temp__192 */ = arguments->slots[0];
  // 832: 'š' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__353;
  arguments->slots[1] = string__93_385;
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
  frame->slots[192] /* temp__193 */ = arguments->slots[0];
  // 833: 'Ţ' = "T"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__354;
  arguments->slots[1] = string__93_387;
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
  frame->slots[193] /* temp__194 */ = arguments->slots[0];
  // 834: 'ţ' = "t"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__355;
  arguments->slots[1] = string__93_389;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_390;
}
static void cont__93_390(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[194] /* temp__195 */ = arguments->slots[0];
  // 835: 'Ť' = "T"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__356;
  arguments->slots[1] = string__93_391;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_392;
}
static void cont__93_392(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[195] /* temp__196 */ = arguments->slots[0];
  // 836: 'ť' = "t"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__357;
  arguments->slots[1] = string__93_393;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_394;
}
static void cont__93_394(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[196] /* temp__197 */ = arguments->slots[0];
  // 837: 'Ŧ' = "T"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__358;
  arguments->slots[1] = string__93_395;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_396;
}
static void cont__93_396(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[197] /* temp__198 */ = arguments->slots[0];
  // 838: 'ŧ' = "t"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__359;
  arguments->slots[1] = string__93_397;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_398;
}
static void cont__93_398(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[198] /* temp__199 */ = arguments->slots[0];
  // 839: 'Ũ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__360;
  arguments->slots[1] = string__93_399;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_400;
}
static void cont__93_400(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[199] /* temp__200 */ = arguments->slots[0];
  // 840: 'ũ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__361;
  arguments->slots[1] = string__93_401;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_402;
}
static void cont__93_402(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[200] /* temp__201 */ = arguments->slots[0];
  // 841: 'Ū' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__362;
  arguments->slots[1] = string__93_403;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_404;
}
static void cont__93_404(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[201] /* temp__202 */ = arguments->slots[0];
  // 842: 'ū' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__363;
  arguments->slots[1] = string__93_405;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_406;
}
static void cont__93_406(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[202] /* temp__203 */ = arguments->slots[0];
  // 843: 'Ŭ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__364;
  arguments->slots[1] = string__93_407;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_408;
}
static void cont__93_408(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[203] /* temp__204 */ = arguments->slots[0];
  // 844: 'ŭ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__365;
  arguments->slots[1] = string__93_409;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_410;
}
static void cont__93_410(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[204] /* temp__205 */ = arguments->slots[0];
  // 845: 'Ů' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__366;
  arguments->slots[1] = string__93_411;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_412;
}
static void cont__93_412(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[205] /* temp__206 */ = arguments->slots[0];
  // 846: 'ů' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__367;
  arguments->slots[1] = string__93_413;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_414;
}
static void cont__93_414(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[206] /* temp__207 */ = arguments->slots[0];
  // 847: 'Ű' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__368;
  arguments->slots[1] = string__93_415;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_416;
}
static void cont__93_416(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[207] /* temp__208 */ = arguments->slots[0];
  // 848: 'ű' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__369;
  arguments->slots[1] = string__93_417;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_418;
}
static void cont__93_418(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[208] /* temp__209 */ = arguments->slots[0];
  // 849: 'Ų' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__370;
  arguments->slots[1] = string__93_419;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_420;
}
static void cont__93_420(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[209] /* temp__210 */ = arguments->slots[0];
  // 850: 'ų' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__371;
  arguments->slots[1] = string__93_421;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_422;
}
static void cont__93_422(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[210] /* temp__211 */ = arguments->slots[0];
  // 851: 'Ŵ' = "W"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__372;
  arguments->slots[1] = string__93_423;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_424;
}
static void cont__93_424(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[211] /* temp__212 */ = arguments->slots[0];
  // 852: 'ŵ' = "w"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__373;
  arguments->slots[1] = string__93_425;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_426;
}
static void cont__93_426(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[212] /* temp__213 */ = arguments->slots[0];
  // 853: 'Ŷ' = "Y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__374;
  arguments->slots[1] = string__93_427;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_428;
}
static void cont__93_428(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[213] /* temp__214 */ = arguments->slots[0];
  // 854: 'ŷ' = "y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__375;
  arguments->slots[1] = string__93_429;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_430;
}
static void cont__93_430(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[214] /* temp__215 */ = arguments->slots[0];
  // 855: 'Ÿ' = "Y"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__376;
  arguments->slots[1] = string__93_431;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_432;
}
static void cont__93_432(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[215] /* temp__216 */ = arguments->slots[0];
  // 856: 'Ź' = "Z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__377;
  arguments->slots[1] = string__93_433;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_434;
}
static void cont__93_434(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[216] /* temp__217 */ = arguments->slots[0];
  // 857: 'ź' = "z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__378;
  arguments->slots[1] = string__93_435;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_436;
}
static void cont__93_436(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[217] /* temp__218 */ = arguments->slots[0];
  // 858: 'Ż' = "Z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__379;
  arguments->slots[1] = string__93_437;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_438;
}
static void cont__93_438(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[218] /* temp__219 */ = arguments->slots[0];
  // 859: 'ż' = "z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__380;
  arguments->slots[1] = string__93_439;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_440;
}
static void cont__93_440(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[219] /* temp__220 */ = arguments->slots[0];
  // 860: 'Ž' = "Z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__381;
  arguments->slots[1] = string__93_441;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_442;
}
static void cont__93_442(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[220] /* temp__221 */ = arguments->slots[0];
  // 861: 'ž' = "z"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__382;
  arguments->slots[1] = string__93_443;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_444;
}
static void cont__93_444(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[221] /* temp__222 */ = arguments->slots[0];
  // 862: 'ſ' = "s"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__383;
  arguments->slots[1] = string__93_445;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_446;
}
static void cont__93_446(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[222] /* temp__223 */ = arguments->slots[0];
  // 863: 'ƀ' = "b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__384;
  arguments->slots[1] = string__93_447;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_448;
}
static void cont__93_448(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[223] /* temp__224 */ = arguments->slots[0];
  // 864: 'Ɓ' = "B"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__385;
  arguments->slots[1] = string__93_449;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_450;
}
static void cont__93_450(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[224] /* temp__225 */ = arguments->slots[0];
  // 865: 'Ƃ' = "B"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__386;
  arguments->slots[1] = string__93_451;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_452;
}
static void cont__93_452(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[225] /* temp__226 */ = arguments->slots[0];
  // 866: 'ƃ' = "b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__387;
  arguments->slots[1] = string__93_453;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_454;
}
static void cont__93_454(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[226] /* temp__227 */ = arguments->slots[0];
  // 867: 'Ƅ' = "b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__388;
  arguments->slots[1] = string__93_455;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_456;
}
static void cont__93_456(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[227] /* temp__228 */ = arguments->slots[0];
  // 868: 'ƅ' = "b"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__389;
  arguments->slots[1] = string__93_457;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_458;
}
static void cont__93_458(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[228] /* temp__229 */ = arguments->slots[0];
  // 869: 'Ƈ' = "C"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__391;
  arguments->slots[1] = string__93_459;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_460;
}
static void cont__93_460(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[229] /* temp__230 */ = arguments->slots[0];
  // 870: 'ƈ' = "c"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__392;
  arguments->slots[1] = string__93_461;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_462;
}
static void cont__93_462(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[230] /* temp__231 */ = arguments->slots[0];
  // 871: 'Ɖ' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__393;
  arguments->slots[1] = string__93_463;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_464;
}
static void cont__93_464(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[231] /* temp__232 */ = arguments->slots[0];
  // 872: 'Ɗ' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__394;
  arguments->slots[1] = string__93_465;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_466;
}
static void cont__93_466(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[232] /* temp__233 */ = arguments->slots[0];
  // 873: 'Ƌ' = "D"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__395;
  arguments->slots[1] = string__93_467;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_468;
}
static void cont__93_468(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[233] /* temp__234 */ = arguments->slots[0];
  // 874: 'ƌ' = "d"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__396;
  arguments->slots[1] = string__93_469;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_470;
}
static void cont__93_470(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[234] /* temp__235 */ = arguments->slots[0];
  // 875: 'ƍ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__397;
  arguments->slots[1] = string__93_471;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_472;
}
static void cont__93_472(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[235] /* temp__236 */ = arguments->slots[0];
  // 876: 'Ɛ' = "E"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__400;
  arguments->slots[1] = string__93_473;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_474;
}
static void cont__93_474(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[236] /* temp__237 */ = arguments->slots[0];
  // 877: 'Ƒ' = "F"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__401;
  arguments->slots[1] = string__93_475;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_476;
}
static void cont__93_476(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[237] /* temp__238 */ = arguments->slots[0];
  // 878: 'ƒ' = "f"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__402;
  arguments->slots[1] = string__93_477;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_478;
}
static void cont__93_478(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[238] /* temp__239 */ = arguments->slots[0];
  // 879: 'Ɠ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__403;
  arguments->slots[1] = string__93_479;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_480;
}
static void cont__93_480(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[239] /* temp__240 */ = arguments->slots[0];
  // 880: 'Ǆ' = "DZ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__452;
  arguments->slots[1] = string__93_481;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_482;
}
static void cont__93_482(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[240] /* temp__241 */ = arguments->slots[0];
  // 881: 'ǅ' = "Dz"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__453;
  arguments->slots[1] = string__93_483;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_484;
}
static void cont__93_484(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[241] /* temp__242 */ = arguments->slots[0];
  // 882: 'ǆ' = "dz"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__454;
  arguments->slots[1] = string__93_485;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_486;
}
static void cont__93_486(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[242] /* temp__243 */ = arguments->slots[0];
  // 883: 'Ǉ' = "LJ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__455;
  arguments->slots[1] = string__93_487;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_488;
}
static void cont__93_488(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[243] /* temp__244 */ = arguments->slots[0];
  // 884: 'ǈ' = "Lj"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__456;
  arguments->slots[1] = string__93_489;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_490;
}
static void cont__93_490(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[244] /* temp__245 */ = arguments->slots[0];
  // 885: 'ǉ' = "lj"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__457;
  arguments->slots[1] = string__93_491;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_492;
}
static void cont__93_492(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[245] /* temp__246 */ = arguments->slots[0];
  // 886: 'Ǌ' = "NJ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__458;
  arguments->slots[1] = string__93_493;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_494;
}
static void cont__93_494(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[246] /* temp__247 */ = arguments->slots[0];
  // 887: 'ǋ' = "Nj"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__459;
  arguments->slots[1] = string__93_495;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_496;
}
static void cont__93_496(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[247] /* temp__248 */ = arguments->slots[0];
  // 888: 'ǌ' = "nj"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__460;
  arguments->slots[1] = string__93_497;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_498;
}
static void cont__93_498(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[248] /* temp__249 */ = arguments->slots[0];
  // 889: 'Ǎ' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__461;
  arguments->slots[1] = string__93_499;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_500;
}
static void cont__93_500(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[249] /* temp__250 */ = arguments->slots[0];
  // 890: 'ǎ' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__462;
  arguments->slots[1] = string__93_501;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_502;
}
static void cont__93_502(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[250] /* temp__251 */ = arguments->slots[0];
  // 891: 'Ǐ' = "I"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__463;
  arguments->slots[1] = string__93_503;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_504;
}
static void cont__93_504(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[251] /* temp__252 */ = arguments->slots[0];
  // 892: 'ǐ' = "i"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__464;
  arguments->slots[1] = string__93_505;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_506;
}
static void cont__93_506(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[252] /* temp__253 */ = arguments->slots[0];
  // 893: 'Ǒ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__465;
  arguments->slots[1] = string__93_507;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_508;
}
static void cont__93_508(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[253] /* temp__254 */ = arguments->slots[0];
  // 894: 'ǒ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__466;
  arguments->slots[1] = string__93_509;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_510;
}
static void cont__93_510(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[254] /* temp__255 */ = arguments->slots[0];
  // 895: 'Ǔ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__467;
  arguments->slots[1] = string__93_511;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_512;
}
static void cont__93_512(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[255] /* temp__256 */ = arguments->slots[0];
  // 896: 'ǔ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__468;
  arguments->slots[1] = string__93_513;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_514;
}
static void cont__93_514(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[256] /* temp__257 */ = arguments->slots[0];
  // 897: 'Ǖ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__469;
  arguments->slots[1] = string__93_515;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_516;
}
static void cont__93_516(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[257] /* temp__258 */ = arguments->slots[0];
  // 898: 'ǖ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__470;
  arguments->slots[1] = string__93_517;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_518;
}
static void cont__93_518(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[258] /* temp__259 */ = arguments->slots[0];
  // 899: 'Ǘ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__471;
  arguments->slots[1] = string__93_519;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_520;
}
static void cont__93_520(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[259] /* temp__260 */ = arguments->slots[0];
  // 900: 'ǘ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__472;
  arguments->slots[1] = string__93_521;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_522;
}
static void cont__93_522(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[260] /* temp__261 */ = arguments->slots[0];
  // 901: 'Ǚ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__473;
  arguments->slots[1] = string__93_523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_524;
}
static void cont__93_524(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[261] /* temp__262 */ = arguments->slots[0];
  // 902: 'ǚ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__474;
  arguments->slots[1] = string__93_525;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_526;
}
static void cont__93_526(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[262] /* temp__263 */ = arguments->slots[0];
  // 903: 'Ǜ' = "U"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__475;
  arguments->slots[1] = string__93_527;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_528;
}
static void cont__93_528(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[263] /* temp__264 */ = arguments->slots[0];
  // 904: 'ǜ' = "u"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__476;
  arguments->slots[1] = string__93_529;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_530;
}
static void cont__93_530(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[264] /* temp__265 */ = arguments->slots[0];
  // 905: 'Ǟ' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__478;
  arguments->slots[1] = string__93_531;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_532;
}
static void cont__93_532(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[265] /* temp__266 */ = arguments->slots[0];
  // 906: 'ǟ' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__479;
  arguments->slots[1] = string__93_533;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_534;
}
static void cont__93_534(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[266] /* temp__267 */ = arguments->slots[0];
  // 907: 'Ǡ' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__480;
  arguments->slots[1] = string__93_535;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_536;
}
static void cont__93_536(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[267] /* temp__268 */ = arguments->slots[0];
  // 908: 'ǡ' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__481;
  arguments->slots[1] = string__93_537;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_538;
}
static void cont__93_538(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[268] /* temp__269 */ = arguments->slots[0];
  // 909: 'Ǣ' = "AE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__482;
  arguments->slots[1] = string__93_539;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_540;
}
static void cont__93_540(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[269] /* temp__270 */ = arguments->slots[0];
  // 910: 'ǣ' = "ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__483;
  arguments->slots[1] = string__93_541;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_542;
}
static void cont__93_542(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[270] /* temp__271 */ = arguments->slots[0];
  // 911: 'Ǥ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__484;
  arguments->slots[1] = string__93_543;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_544;
}
static void cont__93_544(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[271] /* temp__272 */ = arguments->slots[0];
  // 912: 'ǥ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__485;
  arguments->slots[1] = string__93_545;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_546;
}
static void cont__93_546(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[272] /* temp__273 */ = arguments->slots[0];
  // 913: 'Ǧ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__486;
  arguments->slots[1] = string__93_547;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_548;
}
static void cont__93_548(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[273] /* temp__274 */ = arguments->slots[0];
  // 914: 'ǧ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__487;
  arguments->slots[1] = string__93_549;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_550;
}
static void cont__93_550(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[274] /* temp__275 */ = arguments->slots[0];
  // 915: 'Ǩ' = "K"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__488;
  arguments->slots[1] = string__93_551;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_552;
}
static void cont__93_552(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[275] /* temp__276 */ = arguments->slots[0];
  // 916: 'ǩ' = "k"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__489;
  arguments->slots[1] = string__93_553;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_554;
}
static void cont__93_554(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[276] /* temp__277 */ = arguments->slots[0];
  // 917: 'Ǫ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__490;
  arguments->slots[1] = string__93_555;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_556;
}
static void cont__93_556(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[277] /* temp__278 */ = arguments->slots[0];
  // 918: 'ǫ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__491;
  arguments->slots[1] = string__93_557;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_558;
}
static void cont__93_558(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[278] /* temp__279 */ = arguments->slots[0];
  // 919: 'Ǭ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__492;
  arguments->slots[1] = string__93_559;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_560;
}
static void cont__93_560(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[279] /* temp__280 */ = arguments->slots[0];
  // 920: 'ǭ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__493;
  arguments->slots[1] = string__93_561;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_562;
}
static void cont__93_562(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[280] /* temp__281 */ = arguments->slots[0];
  // 921: 'Ǳ' = "DZ"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__497;
  arguments->slots[1] = string__93_563;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_564;
}
static void cont__93_564(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[281] /* temp__282 */ = arguments->slots[0];
  // 922: 'ǲ' = "Dz"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__498;
  arguments->slots[1] = string__93_565;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_566;
}
static void cont__93_566(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[282] /* temp__283 */ = arguments->slots[0];
  // 923: 'ǳ' = "dz"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__499;
  arguments->slots[1] = string__93_567;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_568;
}
static void cont__93_568(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[283] /* temp__284 */ = arguments->slots[0];
  // 924: 'Ǵ' = "G"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__500;
  arguments->slots[1] = string__93_569;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_570;
}
static void cont__93_570(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[284] /* temp__285 */ = arguments->slots[0];
  // 925: 'ǵ' = "g"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__501;
  arguments->slots[1] = string__93_571;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_572;
}
static void cont__93_572(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[285] /* temp__286 */ = arguments->slots[0];
  // 926: 'Ǹ' = "N"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__504;
  arguments->slots[1] = string__93_573;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_574;
}
static void cont__93_574(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[286] /* temp__287 */ = arguments->slots[0];
  // 927: 'ǹ' = "n"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__505;
  arguments->slots[1] = string__93_575;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_576;
}
static void cont__93_576(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[287] /* temp__288 */ = arguments->slots[0];
  // 928: 'Ǻ' = "A"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__506;
  arguments->slots[1] = string__93_577;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_578;
}
static void cont__93_578(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[288] /* temp__289 */ = arguments->slots[0];
  // 929: 'ǻ' = "a"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__507;
  arguments->slots[1] = string__93_579;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_580;
}
static void cont__93_580(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[289] /* temp__290 */ = arguments->slots[0];
  // 930: 'Ǽ' = "AE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__508;
  arguments->slots[1] = string__93_581;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_582;
}
static void cont__93_582(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[290] /* temp__291 */ = arguments->slots[0];
  // 931: 'ǽ' = "ae"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__509;
  arguments->slots[1] = string__93_583;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_584;
}
static void cont__93_584(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[291] /* temp__292 */ = arguments->slots[0];
  // 932: 'Ǿ' = "O"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__510;
  arguments->slots[1] = string__93_585;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_586;
}
static void cont__93_586(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[292] /* temp__293 */ = arguments->slots[0];
  // 933: 'ǿ' = "o"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__511;
  arguments->slots[1] = string__93_587;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__93_588;
}
static void cont__93_588(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[293] /* temp__294 */ = arguments->slots[0];
  // 638: $umlaut_conversions
  // 639:   table
  // 640:     '¡' = "!"
  // 641:     '¢' = "(cent)"
  // 642:     '£' = "(pound)"
  // 643:     '¤' = "?"
  // 644:     '¥' = "(yen)"
  // 645:     '¦' = "|"
  // 646:     '§' = "$"
  // 647:     '¨' = "@quot;"
  // ...
  argument_count = 294;
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
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__93_589;
}
static void cont__93_589(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._umlaut_conversions, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__1_1(void) {
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
  // 28: parse_integer &self $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = get__parse_integer();
  func = myself->type;
  frame->cont = cont__1_2;
}
static void cont__1_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 28: ... value
  initialize_future(frame->slots[2] /* value */, frame->slots[3] /* temp__1 */);
  // 29: ... self != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__1_3;
}
static void cont__1_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 29: ... self != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__1_4;
}
static void cont__1_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 29: ... : return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__1_5, 0);
  // 29: if self != "": return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__1_6;
}
static void entry__1_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 29: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__1_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 30: -> value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* value */;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__2_1(void) {
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
  // 37: parse_real &self $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = get__parse_real();
  func = myself->type;
  frame->cont = cont__2_2;
}
static void cont__2_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 37: ... value
  initialize_future(frame->slots[2] /* value */, frame->slots[3] /* temp__1 */);
  // 38: ... self != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__2_3;
}
static void cont__2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 38: ... self != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__2_4;
}
static void cont__2_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 38: ... : return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__2_5, 0);
  // 38: if self != "": return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__2_6;
}
static void entry__2_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 38: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__2_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 39: -> value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* value */;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__3_24(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 48: parse_real self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = frame->caller_result_count;
  myself = get__parse_real();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 50: parse_integer self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = frame->caller_result_count;
  myself = get__parse_integer();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_1(void) {
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
  // 42: $$i 1
  ((CELL *)frame->slots[1])->contents /* i */ = number__1;
  // 43: $n length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__3_2;
}
static void cont__3_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* n */, arguments->slots[0]);
  // 44: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__3_3;
}
static void cont__3_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 44: ... self(1) == '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__3_4;
}
static void cont__3_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 44: ... : inc &i
  frame->slots[5] /* temp__3 */ = create_closure(entry__3_5, 0);
  // 44: if self(1) == '-': inc &i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__3_7;
}
static void entry__3_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // i: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 44: ... inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__3_6;
}
static void cont__3_6(void) {
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
static void cont__3_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 45: ... -> i <= n && self(i).is_a_digit: inc &i
  frame->slots[3] /* temp__1 */ = create_closure(entry__3_8, 0);
  // 45: while -> i <= n && self(i).is_a_digit: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__3_17;
}
static void entry__3_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // i: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: ... inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__3_16;
}
static void cont__3_16(void) {
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
static void entry__3_8(void) {
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
  // 45: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_9;
}
static void cont__3_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 45: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__3_10;
}
static void cont__3_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 45: ... self(i).is_a_digit
  frame->slots[6] /* temp__4 */ = create_closure(entry__3_11, 0);
  // 45: ... i <= n && self(i).is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__3_14;
}
static void entry__3_11(void) {
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
  // 45: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__3_12;
}
static void cont__3_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 45: ... self(i).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__3_13;
}
static void cont__3_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 45: ... self(i).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 45: ... : inc &i
  frame->slots[7] /* temp__5 */ = create_closure(entry__3_15, 0);
  // 45: ... -> i <= n && self(i).is_a_digit: inc &i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 47: i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_18;
}
static void cont__3_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 47: i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__3_19;
}
static void cont__3_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 47: ... self(i) == '.'
  frame->slots[6] /* temp__4 */ = create_closure(entry__3_20, 0);
  // 47: i <= n && self(i) == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__3_23;
}
static void entry__3_20(void) {
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
  // 47: ... self(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__3_21;
}
static void cont__3_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 47: ... self(i) == '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__3_22;
}
static void cont__3_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 47: ... self(i) == '.'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 47: ... :
  // 48:   parse_real self
  frame->slots[7] /* temp__5 */ = create_closure(entry__3_24, 0);
  // 49: :
  // 50:   parse_integer self
  frame->slots[8] /* temp__6 */ = create_closure(entry__3_25, 0);
  // 46: if
  // 47:   i <= n && self(i) == '.':
  // 48:     parse_real self
  // 49:   :
  // 50:     parse_integer self
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
static void entry__4_1(void) {
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
  // 57: parse_number &self $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = get__parse_number();
  func = myself->type;
  frame->cont = cont__4_2;
}
static void cont__4_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 57: ... value
  initialize_future(frame->slots[2] /* value */, frame->slots[3] /* temp__1 */);
  // 58: ... self != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__4_3;
}
static void cont__4_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 58: ... self != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__4_4;
}
static void cont__4_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 58: ... : return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__4_5, 0);
  // 58: if self != "": return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__4_6;
}
static void entry__4_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 58: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 59: -> value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* value */;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__5_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // chr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 61: ... chr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 61: ... append(chr.to_string self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__5_3;
}
static void cont__5_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 61: ... -> append(chr.to_string self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_1(void) {
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
  // 68: ... : (arg) append &self arg.to_string
  frame->slots[2] /* temp__1 */ = create_closure(entry__6_2, 1);
  // 68: for_each args: (arg) append &self arg.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__6_5;
}
static void entry__6_2(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // arg: 0
  // self: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 68: ... arg.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__6_3;
}
static void cont__6_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 68: ... append &self arg.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__6_4;
}
static void cont__6_4(void) {
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
static void cont__6_5(void) {
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
static void entry__7_1(void) {
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
  // 76: $left_len length_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__7_2;
}
static void cont__7_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* left_len */, arguments->slots[0]);
  // 77: $right_len length_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__7_3;
}
static void cont__7_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* right_len */, arguments->slots[0]);
  // 78: ... min(left_len right_len)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* left_len */;
  arguments->slots[1] = frame->slots[4] /* right_len */;
  result_count = 1;
  myself = get__min();
  func = myself->type;
  frame->cont = cont__7_4;
}
static void cont__7_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 78: ... : (i)
  // 79:   $left_chr left(i)
  // 80:   $right_chr right(i)
  // 81:   if left_chr != right_chr:
  // 82:     if
  // 83:       &&
  // 84:         left_chr >= '1'
  // 85:         left_chr <= '9'
  // 86:         right_chr >= '1'
  // 87:         right_chr <= '9'
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__7_5, 1);
  // 78: from_to 1 min(left_len right_len): (i)
  // 79:   $left_chr left(i)
  // 80:   $right_chr right(i)
  // 81:   if left_chr != right_chr:
  // 82:     if
  // 83:       &&
  // 84:         left_chr >= '1'
  // 85:         left_chr <= '9'
  // 86:         right_chr >= '1'
  // 87:         right_chr <= '9'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__7_58;
}
static void entry__7_10(void) {
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
  // 84: left_chr >= '1'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left_chr */;
  arguments->slots[1] = character__49;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_11;
}
static void cont__7_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__3 */ = arguments->slots[0];
  // 84: left_chr >= '1'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_12;
}
static void cont__7_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  frame->slots[11] /* temp__4 */ = create_closure(entry__7_13, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_24;
}
static void entry__7_13(void) {
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
  // 85: left_chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[0] /* left_chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_14;
}
static void cont__7_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 85: left_chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_15;
}
static void cont__7_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_16, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_23;
}
static void entry__7_16(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // right_chr: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 86: right_chr >= '1'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* right_chr */;
  arguments->slots[1] = character__49;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_17;
}
static void cont__7_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 86: right_chr >= '1'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_18;
}
static void cont__7_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 87: right_chr <= '9'
  frame->slots[4] /* temp__4 */ = create_closure(entry__7_19, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_22;
}
static void entry__7_19(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // right_chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* right_chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: right_chr <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[0] /* right_chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_20;
}
static void cont__7_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 87: right_chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_21;
}
static void cont__7_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 87: right_chr <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_22(void) {
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
static void cont__7_23(void) {
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
static void cont__7_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 88: :
  // 89:   $$j i+1
  // 90:   forever:
  // 91:     if
  // 92:       j <= left_len && left(j).is_a_digit:
  // 93:         if
  // 94:           j <= right_len && right(j).is_a_digit:
  // 95:             !j j+1
  // 96:           :
  // 97:             return false
  // ...
  frame->slots[12] /* temp__5 */ = create_closure(entry__7_25, 0);
  // 104: :
  // 105:   return left_chr < right_chr
  frame->slots[13] /* temp__6 */ = create_closure(entry__7_54, 0);
  // 82: if
  // 83:   &&
  // 84:     left_chr >= '1'
  // 85:     left_chr <= '9'
  // 86:     right_chr >= '1'
  // 87:     right_chr <= '9'
  // 88:   :
  // 89:     $$j i+1
  // 90:     forever:
  // 91:       if
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__5 */;
  arguments->slots[2] = frame->slots[13] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_56;
}
static void entry__7_51(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 101: return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_52(void) {
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
  // 103: ... left_chr < right_chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* left_chr */;
  arguments->slots[1] = frame->slots[2] /* right_chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_53;
}
static void cont__7_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 103: return left_chr < right_chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_41(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // j: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* j */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 95: !j j+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* j */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_42;
}
static void cont__7_42(void) {
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
static void entry__7_43(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 97: return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_34(void) {
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
  // 94: j <= right_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* right_len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_35;
}
static void cont__7_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 94: j <= right_len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_36;
}
static void cont__7_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 94: ... right(j).is_a_digit
  frame->slots[7] /* temp__4 */ = create_closure(entry__7_37, 0);
  // 94: j <= right_len && right(j).is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_40;
}
static void entry__7_37(void) {
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
  // 94: ... right(j)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = frame->slots[0] /* right */;
  func = myself->type;
  frame->cont = cont__7_38;
}
static void cont__7_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 94: ... right(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__7_39;
}
static void cont__7_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 94: ... right(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 94: ... :
  // 95:   !j j+1
  frame->slots[8] /* temp__5 */ = create_closure(entry__7_41, 0);
  // 96: :
  // 97:   return false
  frame->slots[9] /* temp__6 */ = create_closure(entry__7_43, 0);
  // 93: if
  // 94:   j <= right_len && right(j).is_a_digit:
  // 95:     !j j+1
  // 96:   :
  // 97:     return false
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
static void entry__7_44(void) {
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
  // 100: j <= right_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* right_len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_45;
}
static void cont__7_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 100: j <= right_len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_46;
}
static void cont__7_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 100: ... right(j).is_a_digit
  frame->slots[9] /* temp__4 */ = create_closure(entry__7_47, 0);
  // 100: j <= right_len && right(j).is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_50;
}
static void entry__7_47(void) {
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
  // 100: ... right(j)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = frame->slots[0] /* right */;
  func = myself->type;
  frame->cont = cont__7_48;
}
static void cont__7_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 100: ... right(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__7_49;
}
static void cont__7_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 100: ... right(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 100: ... :
  // 101:   return true
  frame->slots[10] /* temp__5 */ = create_closure(entry__7_51, 0);
  // 102: :
  // 103:   return left_chr < right_chr
  frame->slots[11] /* temp__6 */ = create_closure(entry__7_52, 0);
  //  99: if
  // 100:   j <= right_len && right(j).is_a_digit:
  // 101:     return true
  // 102:   :
  // 103:     return left_chr < right_chr
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
static void entry__7_27(void) {
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
  // 92: j <= left_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left_len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_28;
}
static void cont__7_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__3 */ = arguments->slots[0];
  // 92: j <= left_len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_29;
}
static void cont__7_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 92: ... left(j).is_a_digit
  frame->slots[11] /* temp__4 */ = create_closure(entry__7_30, 0);
  // 92: j <= left_len && left(j).is_a_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_33;
}
static void entry__7_30(void) {
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
  // 92: ... left(j)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = frame->slots[0] /* left */;
  func = myself->type;
  frame->cont = cont__7_31;
}
static void cont__7_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 92: ... left(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_digit();
  func = myself->type;
  frame->cont = cont__7_32;
}
static void cont__7_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 92: ... left(j).is_a_digit
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 92: ... :
  // 93:   if
  // 94:     j <= right_len && right(j).is_a_digit:
  // 95:       !j j+1
  // 96:     :
  // 97:       return false
  frame->slots[12] /* temp__5 */ = create_closure(entry__7_34, 0);
  //  98: :
  //  99:   if
  // 100:     j <= right_len && right(j).is_a_digit:
  // 101:       return true
  // 102:     :
  // 103:       return left_chr < right_chr
  frame->slots[13] /* temp__6 */ = create_closure(entry__7_44, 0);
  //  91: if
  //  92:   j <= left_len && left(j).is_a_digit:
  //  93:     if
  //  94:       j <= right_len && right(j).is_a_digit:
  //  95:         !j j+1
  //  96:       :
  //  97:         return false
  //  98:   :
  //  99:     if
  // 100:       j <= right_len && right(j).is_a_digit:
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
static void entry__7_25(void) {
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
  // 89: $$j i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_26;
}
static void cont__7_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* j */ = arguments->slots[0];
  // 90: ... :
  // 91:   if
  // 92:     j <= left_len && left(j).is_a_digit:
  // 93:       if
  // 94:         j <= right_len && right(j).is_a_digit:
  // 95:           !j j+1
  // 96:         :
  // 97:           return false
  // 98:     :
  // 99:       if
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__7_27, 0);
  // 90: forever:
  // 91:   if
  // 92:     j <= left_len && left(j).is_a_digit:
  // 93:       if
  // 94:         j <= right_len && right(j).is_a_digit:
  // 95:           !j j+1
  // 96:         :
  // 97:           return false
  // 98:     :
  // 99:       if
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_54(void) {
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
  // 105: ... left_chr < right_chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* left_chr */;
  arguments->slots[1] = frame->slots[2] /* right_chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_55;
}
static void cont__7_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 105: return left_chr < right_chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 106: ... left_len < right_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* left_len */;
  arguments->slots[1] = frame->slots[5] /* right_len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_57;
}
static void cont__7_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 106: return left_len < right_len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[7] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_5(void) {
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
  // 79: $left_chr left(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[1] /* left */;
  func = myself->type;
  frame->cont = cont__7_6;
}
static void cont__7_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* left_chr */, arguments->slots[0]);
  // 80: $right_chr right(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[2] /* right */;
  func = myself->type;
  frame->cont = cont__7_7;
}
static void cont__7_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* right_chr */, arguments->slots[0]);
  // 81: ... left_chr != right_chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* left_chr */;
  arguments->slots[1] = frame->slots[7] /* right_chr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_8;
}
static void cont__7_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 81: ... left_chr != right_chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_9;
}
static void cont__7_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 81: ... :
  // 82:   if
  // 83:     &&
  // 84:       left_chr >= '1'
  // 85:       left_chr <= '9'
  // 86:       right_chr >= '1'
  // 87:       right_chr <= '9'
  // 88:     :
  // 89:       $$j i+1
  // 90:       forever:
  // ...
  frame->slots[10] /* temp__3 */ = create_closure(entry__7_10, 0);
  // 81: if left_chr != right_chr:
  // 82:   if
  // 83:     &&
  // 84:       left_chr >= '1'
  // 85:       left_chr <= '9'
  // 86:       right_chr >= '1'
  // 87:       right_chr <= '9'
  // 88:     :
  // 89:       $$j i+1
  // 90:       forever:
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
static void cont__7_58(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__8_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // items: 1
  frame->slots[1] /* items */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 109: $$items empty_list
  ((CELL *)frame->slots[1])->contents /* items */ = get__empty_list();
  // 110: ... : (item) push &items item
  frame->slots[2] /* temp__1 */ = create_closure(entry__8_2, 1);
  // 110: for_each self: (item) push &items item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__8_4;
}
static void entry__8_2(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // items: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* items */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 110: ... push &items item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* items */;
  arguments->slots[1] = frame->slots[0] /* item */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__8_3;
}
static void cont__8_3(void) {
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
static void cont__8_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 111: -> items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* items */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // args: 0
  // buf: 1
  // n: 2
  frame->slots[1] /* buf */ = create_cell();
  frame->slots[2] /* n */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 114: $$buf ""
  ((CELL *)frame->slots[1])->contents /* buf */ = empty_string;
  // 115: $n length_of(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__9_2;
}
static void cont__9_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* n */, arguments->slots[0]);
  // 116: ... : (i) append &buf to_string(args(i))
  frame->slots[3] /* temp__1 */ = create_closure(entry__9_3, 1);
  // 116: from_to 1 n: (i) append &buf to_string(args(i))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[2] /* n */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__9_7;
}
static void entry__9_3(void) {
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
  // 116: ... args(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[2] /* args */;
  func = myself->type;
  frame->cont = cont__9_4;
}
static void cont__9_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 116: ... to_string(args(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__9_5;
}
static void cont__9_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 116: ... append &buf to_string(args(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__9_6;
}
static void cont__9_6(void) {
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
static void cont__9_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 117: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_1(void) {
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
  // 128: ... :
  // 129:   return ""
  frame->slots[3] /* temp__1 */ = create_closure(entry__10_2, 0);
  // 130: ... :
  // 131:   return self
  frame->slots[4] /* temp__2 */ = create_closure(entry__10_3, 0);
  // 132: :
  // 133:   if n < 0: Error "Negative argument for dup!"
  // 134:   $h n .div. 2
  // 135:   $str dup(self h)
  // 136:   if
  // 137:     2*h == n:
  // 138:       return string(str str)
  // 139:     :
  // 140:       return string(str str self)
  frame->slots[5] /* temp__3 */ = create_closure(entry__10_4, 0);
  // 126: case
  // 127:   n
  // 128:   0:
  // 129:     return ""
  // 130:   1:
  // 131:     return self
  // 132:   :
  // 133:     if n < 0: Error "Negative argument for dup!"
  // 134:     $h n .div. 2
  // 135:     $str dup(self h)
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
  frame->cont = cont__10_17;
}
static void entry__10_13(void) {
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
  // 138: ... string(str str)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[1] /* str */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__10_14;
}
static void cont__10_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 138: return string(str str)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_15(void) {
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
  // 140: ... string(str str self)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[1] /* str */;
  arguments->slots[2] = frame->slots[2] /* self */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__10_16;
}
static void cont__10_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 140: return string(str str self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 129: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_3(void) {
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
  // 131: return self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_4(void) {
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
  // 133: ... n < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 133: if n < 0: Error "Negative argument for dup!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__10_6;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_8;
}
static void entry__10_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 133: ... Error "Negative argument for dup!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__10_7;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__10_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 134: $h n .div. 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__10_9;
}
static void cont__10_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* h */, arguments->slots[0]);
  // 135: $str dup(self h)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[3] /* h */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__10_10;
}
static void cont__10_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* str */, arguments->slots[0]);
  // 137: 2*h
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[3] /* h */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__10_11;
}
static void cont__10_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 137: 2*h == n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__10_12;
}
static void cont__10_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 137: ... :
  // 138:   return string(str str)
  frame->slots[7] /* temp__3 */ = create_closure(entry__10_13, 0);
  // 139: :
  // 140:   return string(str str self)
  frame->slots[8] /* temp__4 */ = create_closure(entry__10_15, 0);
  // 136: if
  // 137:   2*h == n:
  // 138:     return string(str str)
  // 139:   :
  // 140:     return string(str str self)
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
static void cont__10_17(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__11_1(void) {
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
    case 2: frame->slots[2] /* pad */ = string__11_2;
  }
  // 155: $text expr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* text */, arguments->slots[0]);
  // 156: $len length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__11_4;
}
static void cont__11_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* len */, arguments->slots[0]);
  // 157: ... len < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_5;
}
static void cont__11_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 157: ... :
  // 158:   $pad_len length_of(pad)
  // 159:   return string(range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len) text)
  frame->slots[7] /* temp__2 */ = create_closure(entry__11_6, 0);
  // 157: if len < n:
  // 158:   $pad_len length_of(pad)
  // 159:   return string(range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len) text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_16;
}
static void entry__11_6(void) {
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
  // 158: $pad_len length_of(pad)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pad */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__11_7;
}
static void cont__11_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* pad_len */, arguments->slots[0]);
  // 159: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__11_8;
}
static void cont__11_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 159: ... n-len+pad_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[5] /* pad_len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__11_9;
}
static void cont__11_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__6 */ = arguments->slots[0];
  // 159: ... n-len+pad_len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__11_10;
}
static void cont__11_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 159: ... n-len+pad_len-1 .div. pad_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* pad_len */;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__11_11;
}
static void cont__11_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  // 159: ... dup(pad n-len+pad_len-1 .div. pad_len)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pad */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__11_12;
}
static void cont__11_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 159: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__11_13;
}
static void cont__11_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__8 */ = arguments->slots[0];
  // 159: ... range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[13] /* temp__8 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__11_14;
}
static void cont__11_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 159: ... string(range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len) text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* text */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__11_15;
}
static void cont__11_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 159: return string(range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len) text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__11_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 160: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__12_1(void) {
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
    case 2: frame->slots[2] /* pad */ = string__12_2;
  }
  // 175: $text expr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* text */, arguments->slots[0]);
  // 176: $len length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__12_4;
}
static void cont__12_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* len */, arguments->slots[0]);
  // 177: ... len < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__12_5;
}
static void cont__12_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 177: ... :
  // 178:   $pad_len length_of(pad)
  // 179:   return string(text range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len))
  frame->slots[7] /* temp__2 */ = create_closure(entry__12_6, 0);
  // 177: if len < n:
  // 178:   $pad_len length_of(pad)
  // 179:   return string(text range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_16;
}
static void entry__12_6(void) {
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
  // 178: $pad_len length_of(pad)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pad */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__12_7;
}
static void cont__12_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* pad_len */, arguments->slots[0]);
  // 179: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__12_8;
}
static void cont__12_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 179: ... n-len+pad_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[5] /* pad_len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__12_9;
}
static void cont__12_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__6 */ = arguments->slots[0];
  // 179: ... n-len+pad_len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__12_10;
}
static void cont__12_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 179: ... n-len+pad_len-1 .div. pad_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* pad_len */;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__12_11;
}
static void cont__12_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  // 179: ... dup(pad n-len+pad_len-1 .div. pad_len)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pad */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__12_12;
}
static void cont__12_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 179: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__12_13;
}
static void cont__12_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__8 */ = arguments->slots[0];
  // 179: ... range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[13] /* temp__8 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__12_14;
}
static void cont__12_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 179: ... string(text range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__12_15;
}
static void cont__12_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 179: return string(text range(dup(pad n-len+pad_len-1 .div. pad_len) 1 n-len))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__12_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 180: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__13_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: ... -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_6(void) {
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
  // 194: ... range(text 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__13_7;
}
static void cont__13_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 194: ... -> range(text 1 n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_1(void) {
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
  // 192: $text expr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__13_2;
}
static void cont__13_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* text */, arguments->slots[0]);
  // 193: $len length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__13_3;
}
static void cont__13_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 194: ... len < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__13_4;
}
static void cont__13_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 194: ... -> text
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_5, 0);
  // 194: ... -> range(text 1 n)
  frame->slots[6] /* temp__3 */ = create_closure(entry__13_6, 0);
  // 194: if len < n (-> text) -> range(text 1 n)
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
static void entry__14_5(void) {
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
  // 209: ... n-len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__14_6;
}
static void cont__14_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 209: ... dup(" " n-len)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__14_7;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__14_8;
}
static void cont__14_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 209: ... string(text dup(" " n-len))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__14_9;
}
static void cont__14_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 209: ... -> string(text dup(" " n-len))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_10(void) {
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
  // 209: ... range(text 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__14_11;
}
static void cont__14_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 209: ... -> range(text 1 n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_1(void) {
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
  // 207: $text expr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__14_2;
}
static void cont__14_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* text */, arguments->slots[0]);
  // 208: $len length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__14_3;
}
static void cont__14_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 209: ... len < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__14_4;
}
static void cont__14_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 209: ... -> string(text dup(" " n-len))
  frame->slots[5] /* temp__2 */ = create_closure(entry__14_5, 0);
  // 209: ... -> range(text 1 n)
  frame->slots[6] /* temp__3 */ = create_closure(entry__14_10, 0);
  // 209: if len < n (-> string(text dup(" " n-len))) -> range(text 1 n)
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
static void entry__15_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: ... -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // chr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 212: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__15_2;
}
static void cont__15_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 212: ... length_of(self) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__15_3;
}
static void cont__15_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 212: ... self(1) == chr
  frame->slots[5] /* temp__4 */ = create_closure(entry__15_4, 0);
  // 212: ... length_of(self) > 0 && self(1) == chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__15_7;
}
static void entry__15_4(void) {
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
  // 212: ... self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__15_5;
}
static void cont__15_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 212: ... self(1) == chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__15_6;
}
static void cont__15_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 212: ... self(1) == chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__15_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 212: if length_of(self) > 0 && self(1) == chr (-> 1) -> undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__15_8;
  arguments->slots[2] = func__15_9;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__16_1(void) {
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
  // 220: $len length_of(expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__16_2;
}
static void cont__16_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 221: ... stream .has_minimum_length. len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__16_3;
}
static void cont__16_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 221: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__16_4, 0);
  // 221: unless stream .has_minimum_length. len: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__16_5;
}
static void entry__16_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 221: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__16_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 222: ... range(stream 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__16_6;
}
static void cont__16_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 222: ... range(stream 1 len) == expr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__16_7;
}
static void cont__16_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 222: ... : return len
  frame->slots[6] /* temp__3 */ = create_closure(entry__16_8, 0);
  // 222: if range(stream 1 len) == expr: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__16_9;
}
static void entry__16_8(void) {
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
  // 222: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__16_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 223: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__17_1(void) {
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
  // 231: %%grammar::current_node types::grammar_node
  set__grammar__current_node(get__types__grammar_node());
  // 232: $n grammar::match(expr stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* stream */;
  result_count = 1;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__17_2;
}
static void cont__17_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 233: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__17_3;
}
static void cont__17_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 233: ... parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
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
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 233: ... : return n grammar::current_node
  frame->slots[6] /* temp__3 */ = create_closure(entry__17_5, 0);
  // 233: if parameter_count_of(return) == 2: return n grammar::current_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__17_6;
}
static void entry__17_5(void) {
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
  // 233: ... return n grammar::current_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = get__grammar__current_node();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__17_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 234: -> n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__18_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // sum: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* sum */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 246: ... sum+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sum */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void cont__18_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 246: -> sum+1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_8(void) {
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
  // 247: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__18_9;
}
static void cont__18_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 247: ... range(self 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__18_10;
}
static void cont__18_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 247: ... sum+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* sum */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__18_11;
}
static void cont__18_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 247: ... search_character(range(self 2 -1) chr sum+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__search_character();
  func = myself->type;
  frame->cont = cont__18_12;
}
static void cont__18_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 247: -> search_character(range(self 2 -1) chr sum+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_3(void) {
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
  // 245: self(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* self */;
  func = myself->type;
  frame->cont = cont__18_4;
}
static void cont__18_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 245: self(1) == chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 246: -> sum+1
  frame->slots[5] /* temp__3 */ = create_closure(entry__18_6, 0);
  // 247: -> search_character(range(self 2 -1) chr sum+1)
  frame->slots[6] /* temp__4 */ = create_closure(entry__18_8, 0);
  // 244: if
  // 245:   self(1) == chr
  // 246:   -> sum+1
  // 247:   -> search_character(range(self 2 -1) chr sum+1)
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
static void entry__18_13(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 248: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1(void) {
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
  // 243: self .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__18_2;
}
static void cont__18_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 243: ... :
  // 244:   if
  // 245:     self(1) == chr
  // 246:     -> sum+1
  // 247:     -> search_character(range(self 2 -1) chr sum+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__18_3, 0);
  // 242: if
  // 243:   self .has_minimum_length. 1:
  // 244:     if
  // 245:       self(1) == chr
  // 246:       -> sum+1
  // 247:       -> search_character(range(self 2 -1) chr sum+1)
  // 248:   -> undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = func__18_13;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1(void) {
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
  // 258: %%grammar::current_node types::grammar_node
  set__grammar__current_node(get__types__grammar_node());
  // 259: grammar::search $pos $len expr stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* stream */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__19_2;
}
static void cont__19_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 259: ... pos
  initialize_future(frame->slots[3] /* pos */, frame->slots[5] /* temp__1 */);
  // 259: ... len
  initialize_future(frame->slots[4] /* len */, frame->slots[6] /* temp__2 */);
  // 260: -> pos len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  arguments->slots[1] = frame->slots[4] /* len */;
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__20_1(void) {
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
  // 295: grammar::search $pos $_len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 295: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 295: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 297: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__20_3;
}
static void cont__20_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 297: ... :
  // 298:   return range(str 1 pos-1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__20_4, 0);
  // 299: :
  // 300:   return ""
  frame->slots[8] /* temp__3 */ = create_closure(entry__20_7, 0);
  // 296: if
  // 297:   pos.is_defined:
  // 298:     return range(str 1 pos-1)
  // 299:   :
  // 300:     return ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__20_8;
}
static void entry__20_4(void) {
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
  // 298: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__20_5;
}
static void cont__20_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 298: ... range(str 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__20_6;
}
static void cont__20_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 298: return range(str 1 pos-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 300: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__20_8(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__21_1(void) {
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
  // 326: grammar::search $pos $_len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__21_2;
}
static void cont__21_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 326: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 326: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 328: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_3;
}
static void cont__21_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 328: ... :
  // 329:   return range(str 1 pos-1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__21_4, 0);
  // 330: :
  // 331:   return str
  frame->slots[8] /* temp__3 */ = create_closure(entry__21_7, 0);
  // 327: if
  // 328:   pos.is_defined:
  // 329:     return range(str 1 pos-1)
  // 330:   :
  // 331:     return str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_8;
}
static void entry__21_4(void) {
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
  // 329: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__21_5;
}
static void cont__21_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 329: ... range(str 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__21_6;
}
static void cont__21_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 329: return range(str 1 pos-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_7(void) {
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
  // 331: return str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_8(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__22_1(void) {
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
  // 364: grammar::search $pos $len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__22_2;
}
static void cont__22_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 364: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 364: ... len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 366: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_3;
}
static void cont__22_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 366: ... :
  // 367:   return range(str pos+len -1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__22_4, 0);
  // 368: :
  // 369:   return ""
  frame->slots[8] /* temp__3 */ = create_closure(entry__22_8, 0);
  // 365: if
  // 366:   pos.is_defined:
  // 367:     return range(str pos+len -1)
  // 368:   :
  // 369:     return ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_9;
}
static void entry__22_4(void) {
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
  // 367: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__22_5;
}
static void cont__22_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 367: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__22_6;
}
static void cont__22_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 367: ... range(str pos+len -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__22_7;
}
static void cont__22_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 367: return range(str pos+len -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 369: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__22_9(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__23_1(void) {
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
  // 395: grammar::search $pos $len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 395: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 395: ... len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 397: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__23_3;
}
static void cont__23_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 397: ... :
  // 398:   return range(str pos+len -1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__23_4, 0);
  // 399: :
  // 400:   return str
  frame->slots[8] /* temp__3 */ = create_closure(entry__23_8, 0);
  // 396: if
  // 397:   pos.is_defined:
  // 398:     return range(str pos+len -1)
  // 399:   :
  // 400:     return str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__23_9;
}
static void entry__23_4(void) {
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
  // 398: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__23_5;
}
static void cont__23_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 398: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__23_6;
}
static void cont__23_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 398: ... range(str pos+len -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__23_7;
}
static void cont__23_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 398: return range(str pos+len -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_8(void) {
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
  // 400: return str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__23_9(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__24_1(void) {
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
  // 429: grammar::search $pos $_len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 429: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 429: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 431: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_3;
}
static void cont__24_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 431: ... :
  // 432:   return range(str pos -1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__24_4, 0);
  // 433: :
  // 434:   return ""
  frame->slots[8] /* temp__3 */ = create_closure(entry__24_7, 0);
  // 430: if
  // 431:   pos.is_defined:
  // 432:     return range(str pos -1)
  // 433:   :
  // 434:     return ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_8;
}
static void entry__24_4(void) {
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
  // 432: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void cont__24_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 432: ... range(str pos -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[2] /* pos */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__24_6;
}
static void cont__24_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 432: return range(str pos -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 434: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_8(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__25_1(void) {
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
  // 451: grammar::search $pos $_len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 451: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 451: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 453: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_3;
}
static void cont__25_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 453: ... :
  // 454:   return range(str pos -1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__25_4, 0);
  // 455: :
  // 456:   return str
  frame->slots[8] /* temp__3 */ = create_closure(entry__25_7, 0);
  // 452: if
  // 453:   pos.is_defined:
  // 454:     return range(str pos -1)
  // 455:   :
  // 456:     return str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_8;
}
static void entry__25_4(void) {
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
  // 454: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__25_5;
}
static void cont__25_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 454: ... range(str pos -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = frame->slots[2] /* pos */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__25_6;
}
static void cont__25_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 454: return range(str pos -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_7(void) {
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
  // 456: return str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_8(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__26_1(void) {
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
  // 481: grammar::search $pos $len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__26_2;
}
static void cont__26_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 481: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 481: ... len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 483: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__26_3;
}
static void cont__26_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 483: ... :
  // 484:   return range(str 1 pos+len-1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__26_4, 0);
  // 485: :
  // 486:   return ""
  frame->slots[8] /* temp__3 */ = create_closure(entry__26_8, 0);
  // 482: if
  // 483:   pos.is_defined:
  // 484:     return range(str 1 pos+len-1)
  // 485:   :
  // 486:     return ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__26_9;
}
static void entry__26_4(void) {
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
  // 484: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__26_5;
}
static void cont__26_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 484: ... pos+len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__26_6;
}
static void cont__26_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 484: ... range(str 1 pos+len-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__26_7;
}
static void cont__26_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 484: return range(str 1 pos+len-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 486: return ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_9(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__27_1(void) {
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
  // 503: grammar::search $pos $len expr str nth
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* str */;
  arguments->slots[2] = frame->slots[2] /* nth */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 503: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 503: ... len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 505: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 505: ... :
  // 506:   return range(str 1 pos+len-1)
  frame->slots[7] /* temp__2 */ = create_closure(entry__27_4, 0);
  // 507: :
  // 508:   return str
  frame->slots[8] /* temp__3 */ = create_closure(entry__27_8, 0);
  // 504: if
  // 505:   pos.is_defined:
  // 506:     return range(str 1 pos+len-1)
  // 507:   :
  // 508:     return str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__27_9;
}
static void entry__27_4(void) {
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
  // 506: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__27_5;
}
static void cont__27_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 506: ... pos+len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__27_6;
}
static void cont__27_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 506: ... range(str 1 pos+len-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__27_7;
}
static void cont__27_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 506: return range(str 1 pos+len-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__27_8(void) {
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
  // 508: return str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_9(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__28_1(void) {
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
  // 525: ... behind(str expr_1 nth)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* str */;
  arguments->slots[1] = frame->slots[1] /* expr_1 */;
  arguments->slots[2] = frame->slots[3] /* nth */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__28_2;
}
static void cont__28_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 525: ... behind(str expr_1 nth) .before. expr_2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* expr_2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__28_3;
}
static void cont__28_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 525: -> behind(str expr_1 nth) .before. expr_2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // prefix: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 536: ... match(self prefix)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* prefix */;
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 536: ... match(self prefix).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 536: -> match(self prefix).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_1(void) {
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
  // 548: $len length_of(self)
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
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 549: ... : (i)
  // 550:   if match(range(self i -1) suffix) == len-i+1: return true
  frame->slots[4] /* temp__1 */ = create_closure(entry__30_3, 1);
  // 549: from_down_to len 1: (i)
  // 550:   if match(range(self i -1) suffix) == len-i+1: return true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__from_down_to();
  func = myself->type;
  frame->cont = cont__30_11;
}
static void entry__30_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 550: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_3(void) {
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
  // 550: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__30_4;
}
static void cont__30_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 550: ... range(self i -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[0] /* i */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__30_5;
}
static void cont__30_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 550: ... match(range(self i -1) suffix)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__30_6;
}
static void cont__30_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 550: ... len-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[0] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__30_7;
}
static void cont__30_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 550: ... len-i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__30_8;
}
static void cont__30_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 550: ... match(range(self i -1) suffix) == len-i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_9;
}
static void cont__30_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 550: ... : return true
  frame->slots[11] /* temp__7 */ = create_closure(entry__30_10, 0);
  // 550: if match(range(self i -1) suffix) == len-i+1: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 551: -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__31_1(void) {
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
  // 563: $n match(self prefix)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* prefix */;
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__31_2;
}
static void cont__31_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 564: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__31_3;
}
static void cont__31_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 564: ... : return range(self n+1 -1)
  frame->slots[5] /* temp__2 */ = create_closure(entry__31_4, 0);
  // 564: if n.is_defined: return range(self n+1 -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__31_8;
}
static void entry__31_4(void) {
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
  // 564: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__31_5;
}
static void cont__31_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 564: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__31_6;
}
static void cont__31_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 564: ... range(self n+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__31_7;
}
static void cont__31_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 564: ... return range(self n+1 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__31_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 565: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__32_1(void) {
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
  // 577: $len length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__32_2;
}
static void cont__32_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 578: ... : (i)
  // 579:   if match(range(self i -1) suffix) == len-i+1: return range(self 1 i-1)
  frame->slots[4] /* temp__1 */ = create_closure(entry__32_3, 1);
  // 578: from_to 1 len: (i)
  // 579:   if match(range(self i -1) suffix) == len-i+1: return range(self 1 i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* len */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__32_13;
}
static void entry__32_10(void) {
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
  // 579: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__32_11;
}
static void cont__32_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 579: ... range(self 1 i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__32_12;
}
static void cont__32_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 579: ... return range(self 1 i-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_3(void) {
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
  // 579: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__32_4;
}
static void cont__32_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 579: ... range(self i -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[0] /* i */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__32_5;
}
static void cont__32_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 579: ... match(range(self i -1) suffix)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[2] /* suffix */;
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__32_6;
}
static void cont__32_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 579: ... len-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[0] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__32_7;
}
static void cont__32_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 579: ... len-i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__32_8;
}
static void cont__32_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 579: ... match(range(self i -1) suffix) == len-i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__32_9;
}
static void cont__32_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 579: ... : return range(self 1 i-1)
  frame->slots[11] /* temp__7 */ = create_closure(entry__32_10, 0);
  // 579: if match(range(self i -1) suffix) == len-i+1: return range(self 1 i-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__32_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 580: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__33_1(void) {
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
  // 583: $$s 1
  ((CELL *)frame->slots[1])->contents /* s */ = number__1;
  // 584: $$e length_of(str)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__33_2;
}
static void cont__33_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* e */ = arguments->slots[0];
  // 585: ... -> s <= e && str(s) <= ' ': plus &s 1
  frame->slots[3] /* temp__1 */ = create_closure(entry__33_3, 0);
  // 585: while -> s <= e && str(s) <= ' ': plus &s 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__33_13;
}
static void entry__33_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // s: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 585: ... plus &s 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__33_12;
}
static void cont__33_12(void) {
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
static void entry__33_3(void) {
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
  // 585: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* e */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__33_4;
}
static void cont__33_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 585: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__33_5;
}
static void cont__33_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 585: ... str(s) <= ' '
  frame->slots[6] /* temp__4 */ = create_closure(entry__33_6, 0);
  // 585: ... s <= e && str(s) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__33_10;
}
static void entry__33_6(void) {
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
  // 585: ... str(s)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* str */;
  func = myself->type;
  frame->cont = cont__33_7;
}
static void cont__33_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 585: ... str(s) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
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
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 585: ... str(s) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__33_9;
}
static void cont__33_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 585: ... str(s) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 585: ... : plus &s 1
  frame->slots[7] /* temp__5 */ = create_closure(entry__33_11, 0);
  // 585: ... -> s <= e && str(s) <= ' ': plus &s 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 586: ... -> e >= s && str(e) <= ' ': minus &e 1
  frame->slots[3] /* temp__1 */ = create_closure(entry__33_14, 0);
  // 586: while -> e >= s && str(e) <= ' ': minus &e 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__33_24;
}
static void entry__33_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // e: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 586: ... minus &e 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* e */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__33_23;
}
static void cont__33_23(void) {
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
static void entry__33_14(void) {
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
  // 586: ... e >= s
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* e */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__33_15;
}
static void cont__33_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 586: ... e >= s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__33_16;
}
static void cont__33_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 586: ... str(e) <= ' '
  frame->slots[6] /* temp__4 */ = create_closure(entry__33_17, 0);
  // 586: ... e >= s && str(e) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__33_21;
}
static void entry__33_17(void) {
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
  // 586: ... str(e)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* e */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* str */;
  func = myself->type;
  frame->cont = cont__33_18;
}
static void cont__33_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 586: ... str(e) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__33_19;
}
static void cont__33_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 586: ... str(e) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__33_20;
}
static void cont__33_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 586: ... str(e) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 586: ... : minus &e 1
  frame->slots[7] /* temp__5 */ = create_closure(entry__33_22, 0);
  // 586: ... -> e >= s && str(e) <= ' ': minus &e 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 587: range &str s e
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* e */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__33_25;
}
static void cont__33_25(void) {
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
static void entry__34_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // str: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* str */ = create_cell_with_contents(arguments->slots[0]);
  // 590: trim &str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_2;
}
static void cont__34_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  // 591: ... alt(' ' '@ht;' '@nl;' '@cr;')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__9;
  arguments->slots[2] = character__10;
  arguments->slots[3] = character__13;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__34_3;
}
static void cont__34_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 591: ... many(alt(' ' '@ht;' '@nl;' '@cr;'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__34_4;
}
static void cont__34_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 591: ... many(alt(' ' '@ht;' '@nl;' '@cr;')) = " "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__34_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_6;
}
static void cont__34_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 591: replace_all &str many(alt(' ' '@ht;' '@nl;' '@cr;')) = " "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__34_7;
}
static void cont__34_7(void) {
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
static void entry__35_1(void) {
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
      func = cont__35_2;
      return;
    case 1:;
  }
  // 596: separator
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__35_3;
}
static void cont__35_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* separator */, arguments->slots[0]);
  func = cont__35_2;
}
static void cont__35_2(void) {
  // 598: $$items empty_list
  ((CELL *)frame->slots[2])->contents /* items */ = get__empty_list();
  // 599: ... :
  // 600:   grammar::search $pos $len separator text
  // 601:   if pos.is_defined:
  // 602:     push &items range(text 1 pos-1)
  // 603:     range &text pos+len -1
  // 604:   -> pos.is_defined
  frame->slots[3] /* temp__1 */ = create_closure(entry__35_4, 0);
  // 599: do_while:
  // 600:   grammar::search $pos $len separator text
  // 601:   if pos.is_defined:
  // 602:     push &items range(text 1 pos-1)
  // 603:     range &text pos+len -1
  // 604:   -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do_while();
  func = myself->type;
  frame->cont = cont__35_16;
}
static void entry__35_4(void) {
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
  // 600: grammar::search $pos $len separator text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* separator */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__35_5;
}
static void cont__35_5(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 600: ... pos
  initialize_future(frame->slots[3] /* pos */, frame->slots[5] /* temp__1 */);
  // 600: ... len
  initialize_future(frame->slots[4] /* len */, frame->slots[6] /* temp__2 */);
  // 601: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__35_6;
}
static void cont__35_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 601: ... :
  // 602:   push &items range(text 1 pos-1)
  // 603:   range &text pos+len -1
  frame->slots[6] /* temp__2 */ = create_closure(entry__35_7, 0);
  // 601: if pos.is_defined:
  // 602:   push &items range(text 1 pos-1)
  // 603:   range &text pos+len -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__35_14;
}
static void entry__35_7(void) {
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
  // 602: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__35_8;
}
static void cont__35_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 602: ... range(text 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_9;
}
static void cont__35_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 602: push &items range(text 1 pos-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* items */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__35_10;
}
static void cont__35_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* items */ = arguments->slots[0];
  // 603: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__35_11;
}
static void cont__35_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 603: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__35_12;
}
static void cont__35_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 603: range &text pos+len -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_13;
}
static void cont__35_13(void) {
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
static void cont__35_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 604: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__35_15;
}
static void cont__35_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 604: -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 605: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__35_17;
}
static void cont__35_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 605: ... length_of(text) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__35_18;
}
static void cont__35_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 605: ... : push &items text
  frame->slots[5] /* temp__3 */ = create_closure(entry__35_19, 0);
  // 605: if length_of(text) > 0: push &items text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__35_21;
}
static void entry__35_19(void) {
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
  // 605: ... push &items text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* items */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__35_20;
}
static void cont__35_20(void) {
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
static void cont__35_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 606: -> items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* items */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_1(void) {
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
    case 1: frame->slots[1] /* separator */ = string__36_2;
  }
  // 613: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 615: ... : (word)
  // 616:   append &text word
  frame->slots[3] /* temp__1 */ = create_closure(entry__36_3, 1);
  // 617: :
  // 618:   append &text separator
  frame->slots[4] /* temp__2 */ = create_closure(entry__36_5, 0);
  // 614: for_each
  // 615:   words: (word)
  // 616:     append &text word
  // 617:   :
  // 618:     append &text separator
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* words */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__36_7;
}
static void entry__36_3(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // word: 0
  // text: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 616: append &text word
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = frame->slots[0] /* word */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
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
static void entry__36_5(void) {
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
  // 618: append &text separator
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* separator */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__36_6;
}
static void cont__36_6(void) {
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
static void cont__36_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 619: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_1(void) {
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
  // 622: $$n 0
  ((CELL *)frame->slots[2])->contents /* n */ = number__0;
  // 623: ... :
  // 624:   grammar::search $pos $len expr text
  // 625:   if pos.is_defined:
  // 626:     range &text pos+len -1
  // 627:     inc &n
  // 628:   -> pos.is_defined
  frame->slots[3] /* temp__1 */ = create_closure(entry__37_2, 0);
  // 623: do_while:
  // 624:   grammar::search $pos $len expr text
  // 625:   if pos.is_defined:
  // 626:     range &text pos+len -1
  // 627:     inc &n
  // 628:   -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do_while();
  func = myself->type;
  frame->cont = cont__37_12;
}
static void entry__37_2(void) {
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
  // 624: grammar::search $pos $len expr text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__37_3;
}
static void cont__37_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 624: ... pos
  initialize_future(frame->slots[3] /* pos */, frame->slots[5] /* temp__1 */);
  // 624: ... len
  initialize_future(frame->slots[4] /* len */, frame->slots[6] /* temp__2 */);
  // 625: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_4;
}
static void cont__37_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 625: ... :
  // 626:   range &text pos+len -1
  // 627:   inc &n
  frame->slots[6] /* temp__2 */ = create_closure(entry__37_5, 0);
  // 625: if pos.is_defined:
  // 626:   range &text pos+len -1
  // 627:   inc &n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_10;
}
static void entry__37_5(void) {
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
  // 626: ... pos+len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* pos */;
  arguments->slots[1] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__37_6;
}
static void cont__37_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 626: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__37_7;
}
static void cont__37_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 626: range &text pos+len -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__37_8;
}
static void cont__37_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 627: inc &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* n */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__37_9;
}
static void cont__37_9(void) {
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
static void cont__37_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 628: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_11;
}
static void cont__37_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 628: -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 629: -> n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* n */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // text: 0
  // expr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 632: ... grammar::match(expr text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* text */;
  result_count = 1;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__38_2;
}
static void cont__38_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 632: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__38_3;
}
static void cont__38_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 632: ... grammar::match(expr text) == length_of(text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_4;
}
static void cont__38_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 632: -> grammar::match(expr text) == length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_1(void) {
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
  // 635: grammar::search $pos $_len expr text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[0] /* text */;
  result_count = 2;
  myself = get__grammar__search();
  func = myself->type;
  frame->cont = cont__39_2;
}
static void cont__39_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  frame->slots[5] /* temp__2 */ = arguments->slots[1];
  // 635: ... pos
  initialize_future(frame->slots[2] /* pos */, frame->slots[4] /* temp__1 */);
  // 635: ... _len
  initialize_future(frame->slots[3] /* len */, frame->slots[5] /* temp__2 */);
  // 636: ... pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_3;
}
static void cont__39_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 636: -> pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__41_1(void) {
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
  // 939: ... : (idx)
  // 940:   append &result range(text s idx)
  // 941:   !s idx+2
  frame->slots[4] /* temp__1 */ = create_closure(entry__41_2, 1);
  // 939: $copy: (idx)
  // 940:   append &result range(text s idx)
  // 941:   !s idx+2
  initialize_future(frame->slots[3] /* copy */, frame->slots[4] /* temp__1 */);
  // 936: $$s 1
  ((CELL *)frame->slots[1])->contents /* s */ = number__1;
  // 937: $$result ""
  ((CELL *)frame->slots[2])->contents /* result */ = empty_string;
  // 943: ... : (idx chr)
  // 944:   if chr >= '@0x80;':
  // 945:     if
  // 946:       chr >= ' ':
  // 947:         copy idx-1
  // 948:         $conversion umlaut_conversions(chr)
  // 949:         if
  // 950:           conversion.is_defined:
  // 951:             append &result conversion
  // 952:           :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__41_6, 2);
  // 943: for_each text: (idx chr)
  // 944:   if chr >= '@0x80;':
  // 945:     if
  // 946:       chr >= ' ':
  // 947:         copy idx-1
  // 948:         $conversion umlaut_conversions(chr)
  // 949:         if
  // 950:           conversion.is_defined:
  // 951:             append &result conversion
  // 952:           :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__41_26;
}
static void entry__41_17(void) {
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
  // 951: append &result conversion
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[1] /* conversion */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__41_18;
}
static void cont__41_18(void) {
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
static void entry__41_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // result: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 953: push &result '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__41_20;
}
static void cont__41_20(void) {
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
static void entry__41_12(void) {
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
  // 947: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__41_13;
}
static void cont__41_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 947: copy idx-1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* copy */;
  func = myself->type;
  frame->cont = cont__41_14;
}
static void cont__41_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 948: $conversion umlaut_conversions(chr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* chr */;
  result_count = 1;
  myself = var._umlaut_conversions;
  func = myself->type;
  frame->cont = cont__41_15;
}
static void cont__41_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* conversion */, arguments->slots[0]);
  // 950: conversion.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* conversion */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__41_16;
}
static void cont__41_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 950: ... :
  // 951:   append &result conversion
  frame->slots[6] /* temp__2 */ = create_closure(entry__41_17, 0);
  // 952: :
  // 953:   push &result '?'
  frame->slots[7] /* temp__3 */ = create_closure(entry__41_19, 0);
  // 949: if
  // 950:   conversion.is_defined:
  // 951:     append &result conversion
  // 952:   :
  // 953:     push &result '?'
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
static void entry__41_21(void) {
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
  // 955: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__41_22;
}
static void cont__41_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 955: copy idx-1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* copy */;
  func = myself->type;
  frame->cont = cont__41_23;
}
static void cont__41_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 956: ... chr-0x80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* chr */;
  arguments->slots[1] = number__0x80;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__41_24;
}
static void cont__41_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 956: push &result chr-0x80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__41_25;
}
static void cont__41_25(void) {
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
static void entry__41_9(void) {
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
  // 946: chr >= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__160;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__41_10;
}
static void cont__41_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 946: chr >= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__41_11;
}
static void cont__41_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 946: ... :
  // 947:   copy idx-1
  // 948:   $conversion umlaut_conversions(chr)
  // 949:   if
  // 950:     conversion.is_defined:
  // 951:       append &result conversion
  // 952:     :
  // 953:       push &result '?'
  frame->slots[6] /* temp__3 */ = create_closure(entry__41_12, 0);
  // 954: :
  // 955:   copy idx-1
  // 956:   push &result chr-0x80
  frame->slots[7] /* temp__4 */ = create_closure(entry__41_21, 0);
  // 945: if
  // 946:   chr >= ' ':
  // 947:     copy idx-1
  // 948:     $conversion umlaut_conversions(chr)
  // 949:     if
  // 950:       conversion.is_defined:
  // 951:         append &result conversion
  // 952:       :
  // 953:         push &result '?'
  // 954:   :
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
static void entry__41_2(void) {
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
  // 940: ... range(text s idx)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[2] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__41_3;
}
static void cont__41_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 940: append &result range(text s idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__41_4;
}
static void cont__41_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* result */ = arguments->slots[0];
  // 941: !s idx+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__41_5;
}
static void cont__41_5(void) {
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
static void entry__41_6(void) {
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
  // 944: ... chr >= '@0x80;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__128;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__41_7;
}
static void cont__41_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 944: ... chr >= '@0x80;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__41_8;
}
static void cont__41_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 944: ... :
  // 945:   if
  // 946:     chr >= ' ':
  // 947:       copy idx-1
  // 948:       $conversion umlaut_conversions(chr)
  // 949:       if
  // 950:         conversion.is_defined:
  // 951:           append &result conversion
  // 952:         :
  // 953:           push &result '?'
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__41_9, 0);
  // 944: if chr >= '@0x80;':
  // 945:   if
  // 946:     chr >= ' ':
  // 947:       copy idx-1
  // 948:       $conversion umlaut_conversions(chr)
  // 949:       if
  // 950:         conversion.is_defined:
  // 951:           append &result conversion
  // 952:         :
  // 953:           push &result '?'
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
static void cont__41_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 957: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__41_27;
}
static void cont__41_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 957: copy length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[3] /* copy */;
  func = myself->type;
  frame->cont = cont__41_28;
}
static void cont__41_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 958: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__42_1(void) {
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
  // 981: $$new_text ""
  ((CELL *)frame->slots[2])->contents /* new_text */ = empty_string;
  // 982: ... -> length_of(text) > 0:
  // 983:   do: (-> break)
  // 984:     for_each args: (arg)
  // 985:       $expression key_of(arg)
  // 986:       $replacement value_of(arg)
  // 987:       grammar::match $len expression text
  // 988:       if len.is_defined:
  // 989:         if
  // 990:           replacement.is_a_string:
  // 991:             append &new_text replacement
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_2, 0);
  // 982: while -> length_of(text) > 0:
  // 983:   do: (-> break)
  // 984:     for_each args: (arg)
  // 985:       $expression key_of(arg)
  // 986:       $replacement value_of(arg)
  // 987:       grammar::match $len expression text
  // 988:       if len.is_defined:
  // 989:         if
  // 990:           replacement.is_a_string:
  // 991:             append &new_text replacement
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__42_29;
}
static void entry__42_6(void) {
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
  // 984: ... : (arg)
  // 985:   $expression key_of(arg)
  // 986:   $replacement value_of(arg)
  // 987:   grammar::match $len expression text
  // 988:   if len.is_defined:
  // 989:     if
  // 990:       replacement.is_a_string:
  // 991:         append &new_text replacement
  // 992:       :
  // 993:         append &new_text replacement(range(text 1 len))
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__42_7, 1);
  // 984: for_each args: (arg)
  // 985:   $expression key_of(arg)
  // 986:   $replacement value_of(arg)
  // 987:   grammar::match $len expression text
  // 988:   if len.is_defined:
  // 989:     if
  // 990:       replacement.is_a_string:
  // 991:         append &new_text replacement
  // 992:       :
  // 993:         append &new_text replacement(range(text 1 len))
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__42_24;
}
static void entry__42_12(void) {
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
  // 990: replacement.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* replacement */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__42_13;
}
static void cont__42_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 990: ... :
  // 991:   append &new_text replacement
  frame->slots[6] /* temp__2 */ = create_closure(entry__42_14, 0);
  // 992: :
  // 993:   append &new_text replacement(range(text 1 len))
  frame->slots[7] /* temp__3 */ = create_closure(entry__42_16, 0);
  // 989: if
  // 990:   replacement.is_a_string:
  // 991:     append &new_text replacement
  // 992:   :
  // 993:     append &new_text replacement(range(text 1 len))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__42_20;
}
static void entry__42_14(void) {
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
  // 991: append &new_text replacement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_text */;
  arguments->slots[1] = frame->slots[1] /* replacement */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__42_15;
}
static void cont__42_15(void) {
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
static void entry__42_16(void) {
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
  // 993: ... range(text 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__42_17;
}
static void cont__42_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 993: ... replacement(range(text 1 len))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[1] /* replacement */;
  func = myself->type;
  frame->cont = cont__42_18;
}
static void cont__42_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 993: append &new_text replacement(range(text 1 len))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__42_19;
}
static void cont__42_19(void) {
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
static void cont__42_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 994: ... len+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__42_21;
}
static void cont__42_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 994: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__42_22;
}
static void cont__42_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 994: range &text len+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__42_23;
}
static void cont__42_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* text */ = arguments->slots[0];
  // 995: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__42_7(void) {
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
  // 985: $expression key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__42_8;
}
static void cont__42_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* expression */, arguments->slots[0]);
  // 986: $replacement value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__42_9;
}
static void cont__42_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* replacement */, arguments->slots[0]);
  // 987: grammar::match $len expression text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* expression */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__42_10;
}
static void cont__42_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* len */, arguments->slots[0]);
  // 988: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__42_11;
}
static void cont__42_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 988: ... :
  // 989:   if
  // 990:     replacement.is_a_string:
  // 991:       append &new_text replacement
  // 992:     :
  // 993:       append &new_text replacement(range(text 1 len))
  // 994:   range &text len+1 -1
  // 995:   break
  frame->slots[8] /* temp__2 */ = create_closure(entry__42_12, 0);
  // 988: if len.is_defined:
  // 989:   if
  // 990:     replacement.is_a_string:
  // 991:       append &new_text replacement
  // 992:     :
  // 993:       append &new_text replacement(range(text 1 len))
  // 994:   range &text len+1 -1
  // 995:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__42_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 996: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* text */;
  func = myself->type;
  frame->cont = cont__42_25;
}
static void cont__42_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 996: push &new_text text(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* new_text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__42_26;
}
static void cont__42_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* new_text */ = arguments->slots[0];
  // 997: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__42_27;
}
static void cont__42_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 997: range &text 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__42_28;
}
static void cont__42_28(void) {
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
static void entry__42_5(void) {
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
  // 983: ... : (-> break)
  // 984:   for_each args: (arg)
  // 985:     $expression key_of(arg)
  // 986:     $replacement value_of(arg)
  // 987:     grammar::match $len expression text
  // 988:     if len.is_defined:
  // 989:       if
  // 990:         replacement.is_a_string:
  // 991:           append &new_text replacement
  // 992:         :
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__42_6, 0);
  // 983: do: (-> break)
  // 984:   for_each args: (arg)
  // 985:     $expression key_of(arg)
  // 986:     $replacement value_of(arg)
  // 987:     grammar::match $len expression text
  // 988:     if len.is_defined:
  // 989:       if
  // 990:         replacement.is_a_string:
  // 991:           append &new_text replacement
  // 992:         :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__42_2(void) {
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
  // 982: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
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
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 982: ... length_of(text) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__42_4;
}
static void cont__42_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 982: ... :
  // 983:   do: (-> break)
  // 984:     for_each args: (arg)
  // 985:       $expression key_of(arg)
  // 986:       $replacement value_of(arg)
  // 987:       grammar::match $len expression text
  // 988:       if len.is_defined:
  // 989:         if
  // 990:           replacement.is_a_string:
  // 991:             append &new_text replacement
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__42_5, 0);
  // 982: ... -> length_of(text) > 0:
  // 983:   do: (-> break)
  // 984:     for_each args: (arg)
  // 985:       $expression key_of(arg)
  // 986:       $replacement value_of(arg)
  // 987:       grammar::match $len expression text
  // 988:       if len.is_defined:
  // 989:         if
  // 990:           replacement.is_a_string:
  // 991:             append &new_text replacement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__42_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 998: -> new_text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__44_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // n: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1005: ... dup(" " n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__44_4;
  arguments->slots[1] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__44_5;
}
static void cont__44_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1005: ... -> dup(" " n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__44_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // n: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1005: ... range(eighty_spaces 1 n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._eighty_spaces;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__44_7;
}
static void cont__44_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1005: ... -> range(eighty_spaces 1 n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__44_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // n: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1005: ... n > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__80;
  arguments->slots[1] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__44_2;
}
static void cont__44_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1005: ... -> dup(" " n)
  frame->slots[2] /* temp__2 */ = create_closure(entry__44_3, 0);
  // 1005: ... -> range(eighty_spaces 1 n)
  frame->slots[3] /* temp__3 */ = create_closure(entry__44_6, 0);
  // 1005: ... if n > 80 (-> dup(" " n)) -> range(eighty_spaces 1 n)
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
static void entry__45_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // indent: 0
  // text: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* text */ = create_cell_with_contents(arguments->slots[1]);
  // 1008: ... indent > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__45_2;
}
static void cont__45_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1008: ... :
  // 1009:   $indentation spaces(indent)
  // 1010:   replace_all
  // 1011:     &text
  // 1012:     '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT)) = "@nl;@(indentation)"
  // 1013:   unless length_of(text) == 0 || text(1) == '@nl;': append indentation &text
  frame->slots[3] /* temp__2 */ = create_closure(entry__45_3, 0);
  // 1008: if indent > 0:
  // 1009:   $indentation spaces(indent)
  // 1010:   replace_all
  // 1011:     &text
  // 1012:     '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT)) = "@nl;@(indentation)"
  // 1013:   unless length_of(text) == 0 || text(1) == '@nl;': append indentation &text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__45_20;
}
static void entry__45_18(void) {
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
  // 1013: ... append indentation &text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indentation */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__45_19;
}
static void cont__45_19(void) {
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
static void entry__45_3(void) {
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
  // 1009: $indentation spaces(indent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__45_4;
}
static void cont__45_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* indentation */, arguments->slots[0]);
  // 1012: ... alt('@nl;' END_OF_TEXT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__10;
  arguments->slots[1] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__45_5;
}
static void cont__45_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 1012: ... not_followed_by(alt('@nl;' END_OF_TEXT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__45_6;
}
static void cont__45_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1012: '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__10;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__45_7;
}
static void cont__45_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1012: ... "@nl;@(indentation)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__45_8;
  arguments->slots[1] = frame->slots[2] /* indentation */;
  result_count = 1;
  myself = var.std__string;
  func = myself->type;
  frame->cont = cont__45_9;
}
static void cont__45_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 1012: '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT)) = "@nl;@(indentation)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__45_10;
}
static void cont__45_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1010: replace_all
  // 1011:   &text
  // 1012:   '@nl;', not_followed_by(alt('@nl;' END_OF_TEXT)) = "@nl;@(indentation)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__45_11;
}
static void cont__45_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* text */ = arguments->slots[0];
  // 1013: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__45_12;
}
static void cont__45_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1013: ... length_of(text) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__45_13;
}
static void cont__45_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1013: ... text(1) == '@nl;'
  frame->slots[6] /* temp__4 */ = create_closure(entry__45_14, 0);
  // 1013: ... length_of(text) == 0 || text(1) == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__45_17;
}
static void entry__45_14(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1013: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__45_15;
}
static void cont__45_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1013: ... text(1) == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__45_16;
}
static void cont__45_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1013: ... text(1) == '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__45_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1013: ... : append indentation &text
  frame->slots[7] /* temp__5 */ = create_closure(entry__45_18, 0);
  // 1013: unless length_of(text) == 0 || text(1) == '@nl;': append indentation &text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__45_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1014: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__46_29(void) {
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
  // 1038: body no text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* no */;
  arguments->slots[1] = frame->slots[2] /* text */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__46_30(void) {
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
  // 1040: body text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* text */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__46_26(void) {
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
  // 1037: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__46_27;
}
static void cont__46_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1037: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__46_28;
}
static void cont__46_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1037: ... :
  // 1038:   body no text
  frame->slots[5] /* temp__3 */ = create_closure(entry__46_29, 0);
  // 1039: :
  // 1040:   body text
  frame->slots[6] /* temp__4 */ = create_closure(entry__46_30, 0);
  // 1036: if
  // 1037:   parameter_count_of(body) == 2:
  // 1038:     body no text
  // 1039:   :
  // 1040:     body text
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
static void entry__46_4(void) {
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
  // 1027: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__46_5;
}
static void cont__46_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1027: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__46_6;
}
static void cont__46_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1027: ... :
  // 1028:   body no range(text 1 pos-1)
  frame->slots[8] /* temp__3 */ = create_closure(entry__46_7, 0);
  // 1029: :
  // 1030:   body range(text 1 pos-1)
  frame->slots[9] /* temp__4 */ = create_closure(entry__46_10, 0);
  // 1026: if
  // 1027:   parameter_count_of(body) == 2:
  // 1028:     body no range(text 1 pos-1)
  // 1029:   :
  // 1030:     body range(text 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__46_13;
}
static void entry__46_7(void) {
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
  // 1028: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__46_8;
}
static void cont__46_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1028: ... range(text 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__46_9;
}
static void cont__46_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1028: body no range(text 1 pos-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* no */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__46_10(void) {
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
  // 1030: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__46_11;
}
static void cont__46_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1030: ... range(text 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__46_12;
}
static void cont__46_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1030: body range(text 1 pos-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__46_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1031: ... pos+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__46_14;
}
static void cont__46_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1031: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__46_15;
}
static void cont__46_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1031: $rest range(text pos+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__46_16;
}
static void cont__46_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* rest */, arguments->slots[0]);
  // 1032: ... body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__46_17;
}
static void cont__46_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1032: ... rest .has_minimum_length. 1
  frame->slots[8] /* temp__3 */ = create_closure(entry__46_18, 0);
  // 1032: ... body2.is_defined && rest .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__46_20;
}
static void entry__46_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // rest: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* rest */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1032: ... rest .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* rest */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__46_19;
}
static void cont__46_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1032: ... rest .has_minimum_length. 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__46_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1032: if body2.is_defined && rest .has_minimum_length. 1 body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* body2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__46_21;
}
static void cont__46_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1033: ... no+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* no */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__46_22;
}
static void cont__46_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1033: for_each_line rest body body2 no+1
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
static void entry__46_23(void) {
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
  // 1035: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__46_24;
}
static void cont__46_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1035: ... length_of(text) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__46_25;
}
static void cont__46_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1035: ... :
  // 1036:   if
  // 1037:     parameter_count_of(body) == 2:
  // 1038:       body no text
  // 1039:     :
  // 1040:       body text
  frame->slots[5] /* temp__3 */ = create_closure(entry__46_26, 0);
  // 1035: if length_of(text) > 0:
  // 1036:   if
  // 1037:     parameter_count_of(body) == 2:
  // 1038:       body no text
  // 1039:     :
  // 1040:       body text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__46_1(void) {
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
  // 1023: search text '@nl;' $pos $_len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = character__10;
  result_count = 2;
  myself = get__search();
  func = myself->type;
  frame->cont = cont__46_2;
}
static void cont__46_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  frame->slots[7] /* temp__2 */ = arguments->slots[1];
  // 1023: ... pos
  initialize_future(frame->slots[4] /* pos */, frame->slots[6] /* temp__1 */);
  // 1023: ... _len
  initialize_future(frame->slots[5] /* len */, frame->slots[7] /* temp__2 */);
  // 1025: pos.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* pos */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__46_3;
}
static void cont__46_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1025: ... :
  // 1026:   if
  // 1027:     parameter_count_of(body) == 2:
  // 1028:       body no range(text 1 pos-1)
  // 1029:     :
  // 1030:       body range(text 1 pos-1)
  // 1031:   $rest range(text pos+1 -1)
  // 1032:   if body2.is_defined && rest .has_minimum_length. 1 body2
  // 1033:   for_each_line rest body body2 no+1
  frame->slots[7] /* temp__2 */ = create_closure(entry__46_4, 0);
  // 1034: :
  // 1035:   if length_of(text) > 0:
  // 1036:     if
  // 1037:       parameter_count_of(body) == 2:
  // 1038:         body no text
  // 1039:       :
  // 1040:         body text
  frame->slots[8] /* temp__3 */ = create_closure(entry__46_23, 0);
  // 1024: if
  // 1025:   pos.is_defined:
  // 1026:     if
  // 1027:       parameter_count_of(body) == 2:
  // 1028:         body no range(text 1 pos-1)
  // 1029:       :
  // 1030:         body range(text 1 pos-1)
  // 1031:     $rest range(text pos+1 -1)
  // 1032:     if body2.is_defined && rest .has_minimum_length. 1 body2
  // 1033:     for_each_line rest body body2 no+1
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
static void entry__47_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // text: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1042: ... map(text to_lower_case)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = get__to_lower_case();
  result_count = 1;
  myself = get__map();
  func = myself->type;
  frame->cont = cont__47_2;
}
static void cont__47_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1042: ... -> map(text to_lower_case)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__48_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // text: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1044: ... map(text to_upper_case)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = get__to_upper_case();
  result_count = 1;
  myself = get__map();
  func = myself->type;
  frame->cont = cont__48_2;
}
static void cont__48_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1044: ... -> map(text to_upper_case)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__49_1(void) {
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
  // 1047: $$out ""
  ((CELL *)frame->slots[1])->contents /* out */ = empty_string;
  // 1048: $$to_upper true
  ((CELL *)frame->slots[2])->contents /* to_upper */ = get__true();
  // 1049: ... : (chr)
  // 1050:   if
  // 1051:     chr.is_a_letter_character:
  // 1052:       if
  // 1053:         to_upper:
  // 1054:           push &out chr.to_upper_case
  // 1055:           !to_upper false
  // 1056:         :
  // 1057:           push &out chr.to_lower_case
  // 1058:     :
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__49_2, 1);
  // 1049: for_each text: (chr)
  // 1050:   if
  // 1051:     chr.is_a_letter_character:
  // 1052:       if
  // 1053:         to_upper:
  // 1054:           push &out chr.to_upper_case
  // 1055:           !to_upper false
  // 1056:         :
  // 1057:           push &out chr.to_lower_case
  // 1058:     :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__49_13;
}
static void entry__49_5(void) {
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
  // 1054: ... chr.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__49_6;
}
static void cont__49_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1054: push &out chr.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* out */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__49_7;
}
static void cont__49_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* out */ = arguments->slots[0];
  // 1055: !to_upper false
  ((CELL *)frame->slots[2])->contents /* to_upper */ = get__false();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__49_8(void) {
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
  // 1057: ... chr.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__49_9;
}
static void cont__49_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1057: push &out chr.to_lower_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* out */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__49_10;
}
static void cont__49_10(void) {
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
static void entry__49_4(void) {
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
  // 1053: ... :
  // 1054:   push &out chr.to_upper_case
  // 1055:   !to_upper false
  frame->slots[3] /* temp__1 */ = create_closure(entry__49_5, 0);
  // 1056: :
  // 1057:   push &out chr.to_lower_case
  frame->slots[4] /* temp__2 */ = create_closure(entry__49_8, 0);
  // 1052: if
  // 1053:   to_upper:
  // 1054:     push &out chr.to_upper_case
  // 1055:     !to_upper false
  // 1056:   :
  // 1057:     push &out chr.to_lower_case
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
static void entry__49_11(void) {
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
  // 1059: push &out chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* out */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__49_12;
}
static void cont__49_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* out */ = arguments->slots[0];
  // 1060: !to_upper true
  ((CELL *)frame->slots[2])->contents /* to_upper */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__49_2(void) {
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
  // 1051: chr.is_a_letter_character
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = 1;
  myself = get__is_a_letter_character();
  func = myself->type;
  frame->cont = cont__49_3;
}
static void cont__49_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1051: ... :
  // 1052:   if
  // 1053:     to_upper:
  // 1054:       push &out chr.to_upper_case
  // 1055:       !to_upper false
  // 1056:     :
  // 1057:       push &out chr.to_lower_case
  frame->slots[4] /* temp__2 */ = create_closure(entry__49_4, 0);
  // 1058: :
  // 1059:   push &out chr
  // 1060:   !to_upper true
  frame->slots[5] /* temp__3 */ = create_closure(entry__49_11, 0);
  // 1050: if
  // 1051:   chr.is_a_letter_character:
  // 1052:     if
  // 1053:       to_upper:
  // 1054:         push &out chr.to_upper_case
  // 1055:         !to_upper false
  // 1056:       :
  // 1057:         push &out chr.to_lower_case
  // 1058:   :
  // 1059:     push &out chr
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
static void cont__49_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1061: -> out
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* out */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__50_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1128: ... -> types::octet_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__types__octet_string();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__51_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1130: ... -> types::octet_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__types__octet_string();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__52_1(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // self: 0
  // body: 1
  // return__1: 2
  frame->slots[2] /* return__1 */ = create_continuation_with_exit(exit__52_1);
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
  // 1137: ... : (args*) write_to &self args*
  frame->slots[3] /* temp__1 */ = create_closure(entry__52_2, -1);
  // 1137: %std::write: (args*) write_to &self args*
  initialize_future(get__std__write(), frame->slots[3] /* temp__1 */);
  // 1139: body
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__52_4;
}
static void entry__52_2(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // args: 0
  // self: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 1137: ... write_to &self args*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = ((CELL *)frame->slots[1])->contents /* self */;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__52_3;
}
static void cont__52_3(void) {
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
static void cont__52_4(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__52_1(void) {
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
static void entry__53_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // strings: 0
  // func: 1
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
    default: frame->slots[1] /* func */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* func */ = undefined;
  }
  // 1142: $$buf ""
  ((CELL *)frame->slots[2])->contents /* buf */ = empty_string;
  // 1144: func.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* func */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__53_2;
}
static void cont__53_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1144: ... :
  // 1145:   for_each strings: (str) append &buf func(str)
  frame->slots[4] /* temp__2 */ = create_closure(entry__53_3, 0);
  // 1146: :
  // 1147:   for_each strings: (str) append &buf str
  frame->slots[5] /* temp__3 */ = create_closure(entry__53_7, 0);
  // 1143: if
  // 1144:   func.is_defined:
  // 1145:     for_each strings: (str) append &buf func(str)
  // 1146:   :
  // 1147:     for_each strings: (str) append &buf str
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__53_10;
}
static void entry__53_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // str: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1147: ... append &buf str
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[0] /* str */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__53_9;
}
static void cont__53_9(void) {
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
static void entry__53_4(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // str: 0
  // buf: 1
  // func: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[2]; /* func */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1145: ... func(str)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* str */;
  result_count = 1;
  myself = frame->slots[2] /* func */;
  func = myself->type;
  frame->cont = cont__53_5;
}
static void cont__53_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1145: ... append &buf func(str)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__53_6;
}
static void cont__53_6(void) {
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
static void entry__53_3(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // strings: 0
  // buf: 1
  // func: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* strings */
  frame->slots[1] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[1]; /* func */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1145: ... : (str) append &buf func(str)
  frame->slots[3] /* temp__1 */ = create_closure(entry__53_4, 1);
  // 1145: for_each strings: (str) append &buf func(str)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* strings */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__53_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // strings: 0
  // buf: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* strings */
  frame->slots[1] = myself->closure.frame->slots[2]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1147: ... : (str) append &buf str
  frame->slots[2] /* temp__1 */ = create_closure(entry__53_8, 1);
  // 1147: for_each strings: (str) append &buf str
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* strings */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__53_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1148: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__string(void) {
  func__1_1 = collect_node(func__1_1);
  func__2_1 = collect_node(func__2_1);
  func__3_1 = collect_node(func__3_1);
  func__4_1 = collect_node(func__4_1);
  func__5_1 = collect_node(func__5_1);
  func__6_1 = collect_node(func__6_1);
  func__7_1 = collect_node(func__7_1);
  func__8_1 = collect_node(func__8_1);
  var.std__string = collect_node(var.std__string);
  func__9_1 = collect_node(func__9_1);
  string__10_7 = collect_node(string__10_7);
  func__10_6 = collect_node(func__10_6);
  func__10_1 = collect_node(func__10_1);
  var.std__pad_left = collect_node(var.std__pad_left);
  string__11_2 = collect_node(string__11_2);
  func__11_1 = collect_node(func__11_1);
  var.std__pad_right = collect_node(var.std__pad_right);
  string__12_2 = collect_node(string__12_2);
  func__12_1 = collect_node(func__12_1);
  var.std__truncate = collect_node(var.std__truncate);
  func__13_1 = collect_node(func__13_1);
  var.std__pad_or_truncate = collect_node(var.std__pad_or_truncate);
  string__14_7 = collect_node(string__14_7);
  func__14_1 = collect_node(func__14_1);
  func__15_8 = collect_node(func__15_8);
  func__15_9 = collect_node(func__15_9);
  func__15_1 = collect_node(func__15_1);
  func__16_1 = collect_node(func__16_1);
  func__17_1 = collect_node(func__17_1);
  func__18_13 = collect_node(func__18_13);
  func__18_1 = collect_node(func__18_1);
  func__19_1 = collect_node(func__19_1);
  func__20_1 = collect_node(func__20_1);
  func__21_1 = collect_node(func__21_1);
  func__22_1 = collect_node(func__22_1);
  func__23_1 = collect_node(func__23_1);
  func__24_1 = collect_node(func__24_1);
  func__25_1 = collect_node(func__25_1);
  func__26_1 = collect_node(func__26_1);
  func__27_1 = collect_node(func__27_1);
  func__28_1 = collect_node(func__28_1);
  func__29_1 = collect_node(func__29_1);
  func__30_1 = collect_node(func__30_1);
  func__31_1 = collect_node(func__31_1);
  func__32_1 = collect_node(func__32_1);
  var.std__trim = collect_node(var.std__trim);
  func__33_1 = collect_node(func__33_1);
  var.std__normalize = collect_node(var.std__normalize);
  string__34_5 = collect_node(string__34_5);
  func__34_1 = collect_node(func__34_1);
  var.std__split = collect_node(var.std__split);
  func__35_1 = collect_node(func__35_1);
  var.std__join = collect_node(var.std__join);
  string__36_2 = collect_node(string__36_2);
  func__36_1 = collect_node(func__36_1);
  var.std__count_occurrences = collect_node(var.std__count_occurrences);
  func__37_1 = collect_node(func__37_1);
  func__38_1 = collect_node(func__38_1);
  func__39_1 = collect_node(func__39_1);
  var._umlaut_conversions = collect_node(var._umlaut_conversions);
  var.std__replace_umlauts = collect_node(var.std__replace_umlauts);
  func__41_1 = collect_node(func__41_1);
  var.std__replace_all = collect_node(var.std__replace_all);
  func__42_1 = collect_node(func__42_1);
  var._eighty_spaces = collect_node(var._eighty_spaces);
  string__43_1 = collect_node(string__43_1);
  var.std__spaces = collect_node(var.std__spaces);
  string__44_4 = collect_node(string__44_4);
  func__44_1 = collect_node(func__44_1);
  var.std__indented = collect_node(var.std__indented);
  string__45_8 = collect_node(string__45_8);
  func__45_1 = collect_node(func__45_1);
  var.std__for_each_line = collect_node(var.std__for_each_line);
  func__46_1 = collect_node(func__46_1);
  func__47_1 = collect_node(func__47_1);
  func__48_1 = collect_node(func__48_1);
  func__49_1 = collect_node(func__49_1);
  func__50_1 = collect_node(func__50_1);
  func__51_1 = collect_node(func__51_1);
  var.std__collect_output = collect_node(var.std__collect_output);
  func__52_1 = collect_node(func__52_1);
  var.std__concatenate = collect_node(var.std__concatenate);
  func__53_1 = collect_node(func__53_1);
  string__93_1 = collect_node(string__93_1);
  string__93_3 = collect_node(string__93_3);
  string__93_5 = collect_node(string__93_5);
  string__93_7 = collect_node(string__93_7);
  string__93_9 = collect_node(string__93_9);
  string__93_11 = collect_node(string__93_11);
  string__93_13 = collect_node(string__93_13);
  string__93_15 = collect_node(string__93_15);
  string__93_17 = collect_node(string__93_17);
  string__93_19 = collect_node(string__93_19);
  string__93_21 = collect_node(string__93_21);
  string__93_23 = collect_node(string__93_23);
  string__93_25 = collect_node(string__93_25);
  string__93_27 = collect_node(string__93_27);
  string__93_29 = collect_node(string__93_29);
  string__93_31 = collect_node(string__93_31);
  string__93_33 = collect_node(string__93_33);
  string__93_35 = collect_node(string__93_35);
  string__93_37 = collect_node(string__93_37);
  string__93_39 = collect_node(string__93_39);
  string__93_41 = collect_node(string__93_41);
  string__93_43 = collect_node(string__93_43);
  string__93_45 = collect_node(string__93_45);
  string__93_47 = collect_node(string__93_47);
  string__93_49 = collect_node(string__93_49);
  string__93_51 = collect_node(string__93_51);
  string__93_53 = collect_node(string__93_53);
  string__93_55 = collect_node(string__93_55);
  string__93_57 = collect_node(string__93_57);
  string__93_59 = collect_node(string__93_59);
  string__93_61 = collect_node(string__93_61);
  string__93_63 = collect_node(string__93_63);
  string__93_65 = collect_node(string__93_65);
  string__93_67 = collect_node(string__93_67);
  string__93_69 = collect_node(string__93_69);
  string__93_71 = collect_node(string__93_71);
  string__93_73 = collect_node(string__93_73);
  string__93_75 = collect_node(string__93_75);
  string__93_77 = collect_node(string__93_77);
  string__93_79 = collect_node(string__93_79);
  string__93_81 = collect_node(string__93_81);
  string__93_83 = collect_node(string__93_83);
  string__93_85 = collect_node(string__93_85);
  string__93_87 = collect_node(string__93_87);
  string__93_89 = collect_node(string__93_89);
  string__93_91 = collect_node(string__93_91);
  string__93_93 = collect_node(string__93_93);
  string__93_95 = collect_node(string__93_95);
  string__93_97 = collect_node(string__93_97);
  string__93_99 = collect_node(string__93_99);
  string__93_101 = collect_node(string__93_101);
  string__93_103 = collect_node(string__93_103);
  string__93_105 = collect_node(string__93_105);
  string__93_107 = collect_node(string__93_107);
  string__93_109 = collect_node(string__93_109);
  string__93_111 = collect_node(string__93_111);
  string__93_113 = collect_node(string__93_113);
  string__93_115 = collect_node(string__93_115);
  string__93_117 = collect_node(string__93_117);
  string__93_119 = collect_node(string__93_119);
  string__93_121 = collect_node(string__93_121);
  string__93_123 = collect_node(string__93_123);
  string__93_125 = collect_node(string__93_125);
  string__93_127 = collect_node(string__93_127);
  string__93_129 = collect_node(string__93_129);
  string__93_131 = collect_node(string__93_131);
  string__93_133 = collect_node(string__93_133);
  string__93_135 = collect_node(string__93_135);
  string__93_137 = collect_node(string__93_137);
  string__93_139 = collect_node(string__93_139);
  string__93_141 = collect_node(string__93_141);
  string__93_143 = collect_node(string__93_143);
  string__93_145 = collect_node(string__93_145);
  string__93_147 = collect_node(string__93_147);
  string__93_149 = collect_node(string__93_149);
  string__93_151 = collect_node(string__93_151);
  string__93_153 = collect_node(string__93_153);
  string__93_155 = collect_node(string__93_155);
  string__93_157 = collect_node(string__93_157);
  string__93_159 = collect_node(string__93_159);
  string__93_161 = collect_node(string__93_161);
  string__93_163 = collect_node(string__93_163);
  string__93_165 = collect_node(string__93_165);
  string__93_167 = collect_node(string__93_167);
  string__93_169 = collect_node(string__93_169);
  string__93_171 = collect_node(string__93_171);
  string__93_173 = collect_node(string__93_173);
  string__93_175 = collect_node(string__93_175);
  string__93_177 = collect_node(string__93_177);
  string__93_179 = collect_node(string__93_179);
  string__93_181 = collect_node(string__93_181);
  string__93_183 = collect_node(string__93_183);
  string__93_185 = collect_node(string__93_185);
  string__93_187 = collect_node(string__93_187);
  string__93_189 = collect_node(string__93_189);
  string__93_191 = collect_node(string__93_191);
  string__93_193 = collect_node(string__93_193);
  string__93_195 = collect_node(string__93_195);
  string__93_197 = collect_node(string__93_197);
  string__93_199 = collect_node(string__93_199);
  string__93_201 = collect_node(string__93_201);
  string__93_203 = collect_node(string__93_203);
  string__93_205 = collect_node(string__93_205);
  string__93_207 = collect_node(string__93_207);
  string__93_209 = collect_node(string__93_209);
  string__93_211 = collect_node(string__93_211);
  string__93_213 = collect_node(string__93_213);
  string__93_215 = collect_node(string__93_215);
  string__93_217 = collect_node(string__93_217);
  string__93_219 = collect_node(string__93_219);
  string__93_221 = collect_node(string__93_221);
  string__93_223 = collect_node(string__93_223);
  string__93_225 = collect_node(string__93_225);
  string__93_227 = collect_node(string__93_227);
  string__93_229 = collect_node(string__93_229);
  string__93_231 = collect_node(string__93_231);
  string__93_233 = collect_node(string__93_233);
  string__93_235 = collect_node(string__93_235);
  string__93_237 = collect_node(string__93_237);
  string__93_239 = collect_node(string__93_239);
  string__93_241 = collect_node(string__93_241);
  string__93_243 = collect_node(string__93_243);
  string__93_245 = collect_node(string__93_245);
  string__93_247 = collect_node(string__93_247);
  string__93_249 = collect_node(string__93_249);
  string__93_251 = collect_node(string__93_251);
  string__93_253 = collect_node(string__93_253);
  string__93_255 = collect_node(string__93_255);
  string__93_257 = collect_node(string__93_257);
  string__93_259 = collect_node(string__93_259);
  string__93_261 = collect_node(string__93_261);
  string__93_263 = collect_node(string__93_263);
  string__93_265 = collect_node(string__93_265);
  string__93_267 = collect_node(string__93_267);
  string__93_269 = collect_node(string__93_269);
  string__93_271 = collect_node(string__93_271);
  string__93_273 = collect_node(string__93_273);
  string__93_275 = collect_node(string__93_275);
  string__93_277 = collect_node(string__93_277);
  string__93_279 = collect_node(string__93_279);
  string__93_281 = collect_node(string__93_281);
  string__93_283 = collect_node(string__93_283);
  string__93_285 = collect_node(string__93_285);
  string__93_287 = collect_node(string__93_287);
  string__93_289 = collect_node(string__93_289);
  string__93_291 = collect_node(string__93_291);
  string__93_293 = collect_node(string__93_293);
  string__93_295 = collect_node(string__93_295);
  string__93_297 = collect_node(string__93_297);
  string__93_299 = collect_node(string__93_299);
  string__93_301 = collect_node(string__93_301);
  string__93_303 = collect_node(string__93_303);
  string__93_305 = collect_node(string__93_305);
  string__93_307 = collect_node(string__93_307);
  string__93_309 = collect_node(string__93_309);
  string__93_311 = collect_node(string__93_311);
  string__93_313 = collect_node(string__93_313);
  string__93_315 = collect_node(string__93_315);
  string__93_317 = collect_node(string__93_317);
  string__93_319 = collect_node(string__93_319);
  string__93_321 = collect_node(string__93_321);
  string__93_323 = collect_node(string__93_323);
  string__93_325 = collect_node(string__93_325);
  string__93_327 = collect_node(string__93_327);
  string__93_329 = collect_node(string__93_329);
  string__93_331 = collect_node(string__93_331);
  string__93_333 = collect_node(string__93_333);
  string__93_335 = collect_node(string__93_335);
  string__93_337 = collect_node(string__93_337);
  string__93_339 = collect_node(string__93_339);
  string__93_341 = collect_node(string__93_341);
  string__93_343 = collect_node(string__93_343);
  string__93_345 = collect_node(string__93_345);
  string__93_347 = collect_node(string__93_347);
  string__93_349 = collect_node(string__93_349);
  string__93_351 = collect_node(string__93_351);
  string__93_353 = collect_node(string__93_353);
  string__93_355 = collect_node(string__93_355);
  string__93_357 = collect_node(string__93_357);
  string__93_359 = collect_node(string__93_359);
  string__93_361 = collect_node(string__93_361);
  string__93_363 = collect_node(string__93_363);
  string__93_365 = collect_node(string__93_365);
  string__93_367 = collect_node(string__93_367);
  string__93_369 = collect_node(string__93_369);
  string__93_371 = collect_node(string__93_371);
  string__93_373 = collect_node(string__93_373);
  string__93_375 = collect_node(string__93_375);
  string__93_377 = collect_node(string__93_377);
  string__93_379 = collect_node(string__93_379);
  string__93_381 = collect_node(string__93_381);
  string__93_383 = collect_node(string__93_383);
  string__93_385 = collect_node(string__93_385);
  string__93_387 = collect_node(string__93_387);
  string__93_389 = collect_node(string__93_389);
  string__93_391 = collect_node(string__93_391);
  string__93_393 = collect_node(string__93_393);
  string__93_395 = collect_node(string__93_395);
  string__93_397 = collect_node(string__93_397);
  string__93_399 = collect_node(string__93_399);
  string__93_401 = collect_node(string__93_401);
  string__93_403 = collect_node(string__93_403);
  string__93_405 = collect_node(string__93_405);
  string__93_407 = collect_node(string__93_407);
  string__93_409 = collect_node(string__93_409);
  string__93_411 = collect_node(string__93_411);
  string__93_413 = collect_node(string__93_413);
  string__93_415 = collect_node(string__93_415);
  string__93_417 = collect_node(string__93_417);
  string__93_419 = collect_node(string__93_419);
  string__93_421 = collect_node(string__93_421);
  string__93_423 = collect_node(string__93_423);
  string__93_425 = collect_node(string__93_425);
  string__93_427 = collect_node(string__93_427);
  string__93_429 = collect_node(string__93_429);
  string__93_431 = collect_node(string__93_431);
  string__93_433 = collect_node(string__93_433);
  string__93_435 = collect_node(string__93_435);
  string__93_437 = collect_node(string__93_437);
  string__93_439 = collect_node(string__93_439);
  string__93_441 = collect_node(string__93_441);
  string__93_443 = collect_node(string__93_443);
  string__93_445 = collect_node(string__93_445);
  string__93_447 = collect_node(string__93_447);
  string__93_449 = collect_node(string__93_449);
  string__93_451 = collect_node(string__93_451);
  string__93_453 = collect_node(string__93_453);
  string__93_455 = collect_node(string__93_455);
  string__93_457 = collect_node(string__93_457);
  string__93_459 = collect_node(string__93_459);
  string__93_461 = collect_node(string__93_461);
  string__93_463 = collect_node(string__93_463);
  string__93_465 = collect_node(string__93_465);
  string__93_467 = collect_node(string__93_467);
  string__93_469 = collect_node(string__93_469);
  string__93_471 = collect_node(string__93_471);
  string__93_473 = collect_node(string__93_473);
  string__93_475 = collect_node(string__93_475);
  string__93_477 = collect_node(string__93_477);
  string__93_479 = collect_node(string__93_479);
  string__93_481 = collect_node(string__93_481);
  string__93_483 = collect_node(string__93_483);
  string__93_485 = collect_node(string__93_485);
  string__93_487 = collect_node(string__93_487);
  string__93_489 = collect_node(string__93_489);
  string__93_491 = collect_node(string__93_491);
  string__93_493 = collect_node(string__93_493);
  string__93_495 = collect_node(string__93_495);
  string__93_497 = collect_node(string__93_497);
  string__93_499 = collect_node(string__93_499);
  string__93_501 = collect_node(string__93_501);
  string__93_503 = collect_node(string__93_503);
  string__93_505 = collect_node(string__93_505);
  string__93_507 = collect_node(string__93_507);
  string__93_509 = collect_node(string__93_509);
  string__93_511 = collect_node(string__93_511);
  string__93_513 = collect_node(string__93_513);
  string__93_515 = collect_node(string__93_515);
  string__93_517 = collect_node(string__93_517);
  string__93_519 = collect_node(string__93_519);
  string__93_521 = collect_node(string__93_521);
  string__93_523 = collect_node(string__93_523);
  string__93_525 = collect_node(string__93_525);
  string__93_527 = collect_node(string__93_527);
  string__93_529 = collect_node(string__93_529);
  string__93_531 = collect_node(string__93_531);
  string__93_533 = collect_node(string__93_533);
  string__93_535 = collect_node(string__93_535);
  string__93_537 = collect_node(string__93_537);
  string__93_539 = collect_node(string__93_539);
  string__93_541 = collect_node(string__93_541);
  string__93_543 = collect_node(string__93_543);
  string__93_545 = collect_node(string__93_545);
  string__93_547 = collect_node(string__93_547);
  string__93_549 = collect_node(string__93_549);
  string__93_551 = collect_node(string__93_551);
  string__93_553 = collect_node(string__93_553);
  string__93_555 = collect_node(string__93_555);
  string__93_557 = collect_node(string__93_557);
  string__93_559 = collect_node(string__93_559);
  string__93_561 = collect_node(string__93_561);
  string__93_563 = collect_node(string__93_563);
  string__93_565 = collect_node(string__93_565);
  string__93_567 = collect_node(string__93_567);
  string__93_569 = collect_node(string__93_569);
  string__93_571 = collect_node(string__93_571);
  string__93_573 = collect_node(string__93_573);
  string__93_575 = collect_node(string__93_575);
  string__93_577 = collect_node(string__93_577);
  string__93_579 = collect_node(string__93_579);
  string__93_581 = collect_node(string__93_581);
  string__93_583 = collect_node(string__93_583);
  string__93_585 = collect_node(string__93_585);
  string__93_587 = collect_node(string__93_587);
  character__506 = collect_node(character__506);
  character__343 = collect_node(character__343);
  character__338 = collect_node(character__338);
  character__311 = collect_node(character__311);
  character__287 = collect_node(character__287);
  character__270 = collect_node(character__270);
  character__224 = collect_node(character__224);
  character__9 = collect_node(character__9);
  character__455 = collect_node(character__455);
  character__348 = collect_node(character__348);
  character__333 = collect_node(character__333);
  character__301 = collect_node(character__301);
  character__256 = collect_node(character__256);
  character__234 = collect_node(character__234);
  character__486 = collect_node(character__486);
  character__484 = collect_node(character__484);
  character__475 = collect_node(character__475);
  character__467 = collect_node(character__467);
  character__358 = collect_node(character__358);
  character__331 = collect_node(character__331);
  character__323 = collect_node(character__323);
  character__244 = collect_node(character__244);
  character__236 = collect_node(character__236);
  character__188 = collect_node(character__188);
  character__179 = collect_node(character__179);
  character__504 = collect_node(character__504);
  character__465 = collect_node(character__465);
  character__389 = collect_node(character__389);
  character__368 = collect_node(character__368);
  character__321 = collect_node(character__321);
  character__313 = collect_node(character__313);
  character__246 = collect_node(character__246);
  character__198 = collect_node(character__198);
  character__169 = collect_node(character__169);
  character__471 = collect_node(character__471);
  character__382 = collect_node(character__382);
  character__354 = collect_node(character__354);
  character__327 = collect_node(character__327);
  character__303 = collect_node(character__303);
  character__295 = collect_node(character__295);
  character__216 = collect_node(character__216);
  character__208 = collect_node(character__208);
  character__184 = collect_node(character__184);
  character__461 = collect_node(character__461);
  character__400 = collect_node(character__400);
  character__392 = collect_node(character__392);
  character__378 = collect_node(character__378);
  character__364 = collect_node(character__364);
  character__317 = collect_node(character__317);
  character__293 = collect_node(character__293);
  character__285 = collect_node(character__285);
  character__279 = collect_node(character__279);
  character__226 = collect_node(character__226);
  character__218 = collect_node(character__218);
  character__194 = collect_node(character__194);
  character__172 = collect_node(character__172);
  number__80 = collect_node(number__80);
  character__57 = collect_node(character__57);
  character__402 = collect_node(character__402);
  character__366 = collect_node(character__366);
  character__315 = collect_node(character__315);
  character__307 = collect_node(character__307);
  character__291 = collect_node(character__291);
  character__283 = collect_node(character__283);
  character__228 = collect_node(character__228);
  character__204 = collect_node(character__204);
  character__196 = collect_node(character__196);
  character__160 = collect_node(character__160);
  character__473 = collect_node(character__473);
  character__380 = collect_node(character__380);
  character__376 = collect_node(character__376);
  character__374 = collect_node(character__374);
  character__305 = collect_node(character__305);
  character__297 = collect_node(character__297);
  character__281 = collect_node(character__281);
  character__238 = collect_node(character__238);
  character__214 = collect_node(character__214);
  character__206 = collect_node(character__206);
  character__162 = collect_node(character__162);
  character__509 = collect_node(character__509);
  character__482 = collect_node(character__482);
  character__468 = collect_node(character__468);
  character__463 = collect_node(character__463);
  character__387 = collect_node(character__387);
  character__335 = collect_node(character__335);
  character__259 = collect_node(character__259);
  character__232 = collect_node(character__232);
  character__170 = collect_node(character__170);
  character__167 = collect_node(character__167);
  character__63 = collect_node(character__63);
  character__499 = collect_node(character__499);
  character__478 = collect_node(character__478);
  character__371 = collect_node(character__371);
  character__325 = collect_node(character__325);
  character__324 = collect_node(character__324);
  character__249 = collect_node(character__249);
  character__242 = collect_node(character__242);
  character__211 = collect_node(character__211);
  character__166 = collect_node(character__166);
  character__10 = collect_node(character__10);
  character__45 = collect_node(character__45);
  character__481 = collect_node(character__481);
  character__453 = collect_node(character__453);
  character__334 = collect_node(character__334);
  character__288 = collect_node(character__288);
  character__231 = collect_node(character__231);
  character__212 = collect_node(character__212);
  character__185 = collect_node(character__185);
  number__0 = collect_node(number__0);
  character__345 = collect_node(character__345);
  character__344 = collect_node(character__344);
  character__298 = collect_node(character__298);
  character__269 = collect_node(character__269);
  character__222 = collect_node(character__222);
  character__221 = collect_node(character__221);
  character__13 = collect_node(character__13);
  character__460 = collect_node(character__460);
  character__457 = collect_node(character__457);
  character__365 = collect_node(character__365);
  character__308 = collect_node(character__308);
  character__284 = collect_node(character__284);
  character__262 = collect_node(character__262);
  character__205 = collect_node(character__205);
  character__181 = collect_node(character__181);
  character__470 = collect_node(character__470);
  character__393 = collect_node(character__393);
  character__379 = collect_node(character__379);
  character__355 = collect_node(character__355);
  character__341 = collect_node(character__341);
  character__318 = collect_node(character__318);
  character__294 = collect_node(character__294);
  character__272 = collect_node(character__272);
  character__219 = collect_node(character__219);
  character__195 = collect_node(character__195);
  character__173 = collect_node(character__173);
  character__492 = collect_node(character__492);
  character__489 = collect_node(character__489);
  character__383 = collect_node(character__383);
  character__361 = collect_node(character__361);
  character__304 = collect_node(character__304);
  character__280 = collect_node(character__280);
  character__266 = collect_node(character__266);
  character__239 = collect_node(character__239);
  character__201 = collect_node(character__201);
  character__163 = collect_node(character__163);
  number__0x80 = collect_node(number__0x80);
  character__397 = collect_node(character__397);
  character__375 = collect_node(character__375);
  character__351 = collect_node(character__351);
  character__328 = collect_node(character__328);
  character__314 = collect_node(character__314);
  character__290 = collect_node(character__290);
  character__276 = collect_node(character__276);
  character__252 = collect_node(character__252);
  character__229 = collect_node(character__229);
  character__215 = collect_node(character__215);
  character__191 = collect_node(character__191);
  character__177 = collect_node(character__177);
  character__485 = collect_node(character__485);
  character__476 = collect_node(character__476);
  character__403 = collect_node(character__403);
  character__322 = collect_node(character__322);
  character__300 = collect_node(character__300);
  character__267 = collect_node(character__267);
  character__235 = collect_node(character__235);
  character__189 = collect_node(character__189);
  character__507 = collect_node(character__507);
  character__454 = collect_node(character__454);
  character__349 = collect_node(character__349);
  character__332 = collect_node(character__332);
  character__310 = collect_node(character__310);
  character__286 = collect_node(character__286);
  character__271 = collect_node(character__271);
  character__257 = collect_node(character__257);
  character__225 = collect_node(character__225);
  character__505 = collect_node(character__505);
  character__497 = collect_node(character__497);
  character__464 = collect_node(character__464);
  character__456 = collect_node(character__456);
  character__369 = collect_node(character__369);
  character__312 = collect_node(character__312);
  character__255 = collect_node(character__255);
  character__247 = collect_node(character__247);
  character__209 = collect_node(character__209);
  character__168 = collect_node(character__168);
  character__487 = collect_node(character__487);
  character__474 = collect_node(character__474);
  character__466 = collect_node(character__466);
  character__388 = collect_node(character__388);
  character__359 = collect_node(character__359);
  character__320 = collect_node(character__320);
  character__245 = collect_node(character__245);
  character__237 = collect_node(character__237);
  character__199 = collect_node(character__199);
  character__501 = collect_node(character__501);
  character__362 = collect_node(character__362);
  character__330 = collect_node(character__330);
  character__319 = collect_node(character__319);
  character__273 = collect_node(character__273);
  character__251 = collect_node(character__251);
  character__192 = collect_node(character__192);
  character__178 = collect_node(character__178);
  character__164 = collect_node(character__164);
  character__32 = collect_node(character__32);
  character__491 = collect_node(character__491);
  character__384 = collect_node(character__384);
  character__372 = collect_node(character__372);
  character__340 = collect_node(character__340);
  character__309 = collect_node(character__309);
  character__265 = collect_node(character__265);
  character__241 = collect_node(character__241);
  character__202 = collect_node(character__202);
  character__394 = collect_node(character__394);
  character__386 = collect_node(character__386);
  character__350 = collect_node(character__350);
  character__342 = collect_node(character__342);
  character__339 = collect_node(character__339);
  character__277 = collect_node(character__277);
  character__263 = collect_node(character__263);
  character__180 = collect_node(character__180);
  character__174 = collect_node(character__174);
  character__511 = collect_node(character__511);
  character__458 = collect_node(character__458);
  character__396 = collect_node(character__396);
  character__360 = collect_node(character__360);
  character__352 = collect_node(character__352);
  character__329 = collect_node(character__329);
  character__275 = collect_node(character__275);
  character__261 = collect_node(character__261);
  character__253 = collect_node(character__253);
  character__190 = collect_node(character__190);
  character__182 = collect_node(character__182);
  character__176 = collect_node(character__176);
  character__493 = collect_node(character__493);
  character__488 = collect_node(character__488);
  character__479 = collect_node(character__479);
  character__452 = collect_node(character__452);
  character__370 = collect_node(character__370);
  character__357 = collect_node(character__357);
  character__346 = collect_node(character__346);
  character__243 = collect_node(character__243);
  character__200 = collect_node(character__200);
  character__197 = collect_node(character__197);
  number__1 = collect_node(number__1);
  character__498 = collect_node(character__498);
  character__483 = collect_node(character__483);
  character__469 = collect_node(character__469);
  character__462 = collect_node(character__462);
  character__356 = collect_node(character__356);
  character__248 = collect_node(character__248);
  character__233 = collect_node(character__233);
  character__210 = collect_node(character__210);
  character__187 = collect_node(character__187);
  character__186 = collect_node(character__186);
  character__508 = collect_node(character__508);
  character__347 = collect_node(character__347);
  character__326 = collect_node(character__326);
  character__299 = collect_node(character__299);
  character__258 = collect_node(character__258);
  character__223 = collect_node(character__223);
  character__220 = collect_node(character__220);
  character__49 = collect_node(character__49);
  character__46 = collect_node(character__46);
  character__480 = collect_node(character__480);
  character__337 = collect_node(character__337);
  character__336 = collect_node(character__336);
  character__289 = collect_node(character__289);
  character__268 = collect_node(character__268);
  character__230 = collect_node(character__230);
  number__2 = collect_node(number__2);
  character__395 = collect_node(character__395);
  character__373 = collect_node(character__373);
  character__316 = collect_node(character__316);
  character__292 = collect_node(character__292);
  character__278 = collect_node(character__278);
  character__254 = collect_node(character__254);
  character__240 = collect_node(character__240);
  character__227 = collect_node(character__227);
  character__213 = collect_node(character__213);
  character__175 = collect_node(character__175);
  character__500 = collect_node(character__500);
  character__490 = collect_node(character__490);
  character__401 = collect_node(character__401);
  character__385 = collect_node(character__385);
  character__363 = collect_node(character__363);
  character__302 = collect_node(character__302);
  character__264 = collect_node(character__264);
  character__203 = collect_node(character__203);
  character__165 = collect_node(character__165);
  character__472 = collect_node(character__472);
  character__459 = collect_node(character__459);
  character__391 = collect_node(character__391);
  character__377 = collect_node(character__377);
  character__353 = collect_node(character__353);
  character__296 = collect_node(character__296);
  character__274 = collect_node(character__274);
  character__250 = collect_node(character__250);
  character__217 = collect_node(character__217);
  character__193 = collect_node(character__193);
  character__171 = collect_node(character__171);
  character__128 = collect_node(character__128);
  character__510 = collect_node(character__510);
  character__381 = collect_node(character__381);
  character__367 = collect_node(character__367);
  character__306 = collect_node(character__306);
  character__282 = collect_node(character__282);
  character__260 = collect_node(character__260);
  character__207 = collect_node(character__207);
  character__183 = collect_node(character__183);
  character__161 = collect_node(character__161);
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
  set_used_namespaces(used_namespaces);
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
  func__1_1 = create_future();
  func__2_1 = create_future();
  func__3_1 = create_future();
  func__4_1 = create_future();
  func__5_1 = create_future();
  func__6_1 = create_future();
  func__7_1 = create_future();
  func__8_1 = create_future();
  func__9_1 = create_future();
  define_single_assign_static("std", "string", get__std__string, &var.std__string);
  string__10_7 = from_latin_1_string("Negative argument for dup!", 26);
  func__10_6 = create_future();
  func__10_1 = create_future();
  string__11_2 = from_latin_1_string(" ", 1);
  func__11_1 = create_future();
  define_single_assign_static("std", "pad_left", get__std__pad_left, &var.std__pad_left);
  string__12_2 = from_latin_1_string(" ", 1);
  func__12_1 = create_future();
  define_single_assign_static("std", "pad_right", get__std__pad_right, &var.std__pad_right);
  func__13_1 = create_future();
  define_single_assign_static("std", "truncate", get__std__truncate, &var.std__truncate);
  string__14_7 = from_latin_1_string(" ", 1);
  func__14_1 = create_future();
  define_single_assign_static("std", "pad_or_truncate", get__std__pad_or_truncate, &var.std__pad_or_truncate);
  func__15_8 = create_future();
  func__15_9 = create_future();
  func__15_1 = create_future();
  func__16_1 = create_future();
  func__17_1 = create_future();
  func__18_13 = create_future();
  func__18_1 = create_future();
  func__19_1 = create_future();
  func__20_1 = create_future();
  func__21_1 = create_future();
  func__22_1 = create_future();
  func__23_1 = create_future();
  func__24_1 = create_future();
  func__25_1 = create_future();
  func__26_1 = create_future();
  func__27_1 = create_future();
  func__28_1 = create_future();
  func__29_1 = create_future();
  func__30_1 = create_future();
  func__31_1 = create_future();
  func__32_1 = create_future();
  func__33_1 = create_future();
  define_single_assign_static("std", "trim", get__std__trim, &var.std__trim);
  string__34_5 = from_latin_1_string(" ", 1);
  func__34_1 = create_future();
  define_single_assign_static("std", "normalize", get__std__normalize, &var.std__normalize);
  func__35_1 = create_future();
  define_single_assign_static("std", "split", get__std__split, &var.std__split);
  string__36_2 = from_latin_1_string(" ", 1);
  func__36_1 = create_future();
  define_single_assign_static("std", "join", get__std__join, &var.std__join);
  func__37_1 = create_future();
  define_single_assign_static("std", "count_occurrences", get__std__count_occurrences, &var.std__count_occurrences);
  func__38_1 = create_future();
  func__39_1 = create_future();
  var._umlaut_conversions = create_future();
  func__41_1 = create_future();
  define_single_assign_static("std", "replace_umlauts", get__std__replace_umlauts, &var.std__replace_umlauts);
  func__42_1 = create_future();
  define_single_assign_static("std", "replace_all", get__std__replace_all, &var.std__replace_all);
  string__43_1 = from_latin_1_string("                                                                                ", 80);
  string__44_4 = from_latin_1_string(" ", 1);
  func__44_1 = create_future();
  define_single_assign_static("std", "spaces", get__std__spaces, &var.std__spaces);
  string__45_8 = from_latin_1_string("\012", 1);
  func__45_1 = create_future();
  define_single_assign_static("std", "indented", get__std__indented, &var.std__indented);
  func__46_1 = create_future();
  define_single_assign_static("std", "for_each_line", get__std__for_each_line, &var.std__for_each_line);
  func__47_1 = create_future();
  func__48_1 = create_future();
  func__49_1 = create_future();
  func__50_1 = create_future();
  func__51_1 = create_future();
  func__52_1 = create_future();
  define_single_assign_static("std", "collect_output", get__std__collect_output, &var.std__collect_output);
  func__53_1 = create_future();
  define_single_assign_static("std", "concatenate", get__std__concatenate, &var.std__concatenate);
  string__93_1 = from_latin_1_string("!", 1);
  string__93_3 = from_latin_1_string("(cent)", 6);
  string__93_5 = from_latin_1_string("(pound)", 7);
  string__93_7 = from_latin_1_string("?", 1);
  string__93_9 = from_latin_1_string("(yen)", 5);
  string__93_11 = from_latin_1_string("|", 1);
  string__93_13 = from_latin_1_string("$", 1);
  string__93_15 = from_latin_1_string("\042", 1);
  string__93_17 = from_latin_1_string("(c)", 3);
  string__93_19 = from_latin_1_string("a", 1);
  string__93_21 = from_latin_1_string("<<", 2);
  string__93_23 = from_latin_1_string("(not)", 5);
  string__93_25 = from_latin_1_string("(shy)", 5);
  string__93_27 = from_latin_1_string("(r)", 3);
  string__93_29 = from_latin_1_string("~", 1);
  string__93_31 = from_latin_1_string("(grad)", 6);
  string__93_33 = from_latin_1_string("+/-", 3);
  string__93_35 = from_latin_1_string("^2", 2);
  string__93_37 = from_latin_1_string("^3", 2);
  string__93_39 = from_latin_1_string("'", 1);
  string__93_41 = from_latin_1_string("(mu)", 4);
  string__93_43 = from_latin_1_string("(par)", 5);
  string__93_45 = from_latin_1_string(".", 1);
  string__93_47 = from_latin_1_string(",", 1);
  string__93_49 = from_latin_1_string("^1", 2);
  string__93_51 = from_latin_1_string("o", 1);
  string__93_53 = from_latin_1_string(">>", 2);
  string__93_55 = from_latin_1_string("1/4", 3);
  string__93_57 = from_latin_1_string("1/2", 3);
  string__93_59 = from_latin_1_string("3/4", 3);
  string__93_61 = from_latin_1_string("?", 1);
  string__93_63 = from_latin_1_string("A", 1);
  string__93_65 = from_latin_1_string("A", 1);
  string__93_67 = from_latin_1_string("A", 1);
  string__93_69 = from_latin_1_string("A", 1);
  string__93_71 = from_latin_1_string("Ae", 2);
  string__93_73 = from_latin_1_string("A", 1);
  string__93_75 = from_latin_1_string("AE", 2);
  string__93_77 = from_latin_1_string("C", 1);
  string__93_79 = from_latin_1_string("E", 1);
  string__93_81 = from_latin_1_string("E", 1);
  string__93_83 = from_latin_1_string("E", 1);
  string__93_85 = from_latin_1_string("E", 1);
  string__93_87 = from_latin_1_string("I", 1);
  string__93_89 = from_latin_1_string("I", 1);
  string__93_91 = from_latin_1_string("I", 1);
  string__93_93 = from_latin_1_string("I", 1);
  string__93_95 = from_latin_1_string("D", 1);
  string__93_97 = from_latin_1_string("N", 1);
  string__93_99 = from_latin_1_string("O", 1);
  string__93_101 = from_latin_1_string("O", 1);
  string__93_103 = from_latin_1_string("O", 1);
  string__93_105 = from_latin_1_string("O", 1);
  string__93_107 = from_latin_1_string("Oe", 2);
  string__93_109 = from_latin_1_string("x", 1);
  string__93_111 = from_latin_1_string("0", 1);
  string__93_113 = from_latin_1_string("U", 1);
  string__93_115 = from_latin_1_string("U", 1);
  string__93_117 = from_latin_1_string("U", 1);
  string__93_119 = from_latin_1_string("Ue", 2);
  string__93_121 = from_latin_1_string("Y", 1);
  string__93_123 = from_latin_1_string("p", 1);
  string__93_125 = from_latin_1_string("ss", 2);
  string__93_127 = from_latin_1_string("a", 1);
  string__93_129 = from_latin_1_string("a", 1);
  string__93_131 = from_latin_1_string("a", 1);
  string__93_133 = from_latin_1_string("a", 1);
  string__93_135 = from_latin_1_string("ae", 2);
  string__93_137 = from_latin_1_string("a", 1);
  string__93_139 = from_latin_1_string("ae", 2);
  string__93_141 = from_latin_1_string("c", 1);
  string__93_143 = from_latin_1_string("e", 1);
  string__93_145 = from_latin_1_string("e", 1);
  string__93_147 = from_latin_1_string("e", 1);
  string__93_149 = from_latin_1_string("e", 1);
  string__93_151 = from_latin_1_string("i", 1);
  string__93_153 = from_latin_1_string("i", 1);
  string__93_155 = from_latin_1_string("i", 1);
  string__93_157 = from_latin_1_string("i", 1);
  string__93_159 = from_latin_1_string("d", 1);
  string__93_161 = from_latin_1_string("n", 1);
  string__93_163 = from_latin_1_string("o", 1);
  string__93_165 = from_latin_1_string("o", 1);
  string__93_167 = from_latin_1_string("o", 1);
  string__93_169 = from_latin_1_string("o", 1);
  string__93_171 = from_latin_1_string("oe", 2);
  string__93_173 = from_latin_1_string("/", 1);
  string__93_175 = from_latin_1_string("0", 1);
  string__93_177 = from_latin_1_string("u", 1);
  string__93_179 = from_latin_1_string("u", 1);
  string__93_181 = from_latin_1_string("u", 1);
  string__93_183 = from_latin_1_string("ue", 2);
  string__93_185 = from_latin_1_string("y", 1);
  string__93_187 = from_latin_1_string("p", 1);
  string__93_189 = from_latin_1_string("y", 1);
  string__93_191 = from_latin_1_string("A", 1);
  string__93_193 = from_latin_1_string("a", 1);
  string__93_195 = from_latin_1_string("A", 1);
  string__93_197 = from_latin_1_string("a", 1);
  string__93_199 = from_latin_1_string("A", 1);
  string__93_201 = from_latin_1_string("a", 1);
  string__93_203 = from_latin_1_string("C", 1);
  string__93_205 = from_latin_1_string("c", 1);
  string__93_207 = from_latin_1_string("C", 1);
  string__93_209 = from_latin_1_string("c", 1);
  string__93_211 = from_latin_1_string("C", 1);
  string__93_213 = from_latin_1_string("c", 1);
  string__93_215 = from_latin_1_string("C", 1);
  string__93_217 = from_latin_1_string("c", 1);
  string__93_219 = from_latin_1_string("D", 1);
  string__93_221 = from_latin_1_string("d", 1);
  string__93_223 = from_latin_1_string("D", 1);
  string__93_225 = from_latin_1_string("d", 1);
  string__93_227 = from_latin_1_string("E", 1);
  string__93_229 = from_latin_1_string("e", 1);
  string__93_231 = from_latin_1_string("E", 1);
  string__93_233 = from_latin_1_string("e", 1);
  string__93_235 = from_latin_1_string("E", 1);
  string__93_237 = from_latin_1_string("e", 1);
  string__93_239 = from_latin_1_string("E", 1);
  string__93_241 = from_latin_1_string("e", 1);
  string__93_243 = from_latin_1_string("E", 1);
  string__93_245 = from_latin_1_string("e", 1);
  string__93_247 = from_latin_1_string("G", 1);
  string__93_249 = from_latin_1_string("g", 1);
  string__93_251 = from_latin_1_string("G", 1);
  string__93_253 = from_latin_1_string("g", 1);
  string__93_255 = from_latin_1_string("G", 1);
  string__93_257 = from_latin_1_string("g", 1);
  string__93_259 = from_latin_1_string("G", 1);
  string__93_261 = from_latin_1_string("g", 1);
  string__93_263 = from_latin_1_string("H", 1);
  string__93_265 = from_latin_1_string("h", 1);
  string__93_267 = from_latin_1_string("H", 1);
  string__93_269 = from_latin_1_string("h", 1);
  string__93_271 = from_latin_1_string("I", 1);
  string__93_273 = from_latin_1_string("i", 1);
  string__93_275 = from_latin_1_string("I", 1);
  string__93_277 = from_latin_1_string("i", 1);
  string__93_279 = from_latin_1_string("I", 1);
  string__93_281 = from_latin_1_string("i", 1);
  string__93_283 = from_latin_1_string("I", 1);
  string__93_285 = from_latin_1_string("i", 1);
  string__93_287 = from_latin_1_string("I", 1);
  string__93_289 = from_latin_1_string("i", 1);
  string__93_291 = from_latin_1_string("IJ", 2);
  string__93_293 = from_latin_1_string("ij", 2);
  string__93_295 = from_latin_1_string("J", 1);
  string__93_297 = from_latin_1_string("j", 1);
  string__93_299 = from_latin_1_string("K", 1);
  string__93_301 = from_latin_1_string("k", 1);
  string__93_303 = from_latin_1_string("k", 1);
  string__93_305 = from_latin_1_string("L", 1);
  string__93_307 = from_latin_1_string("l", 1);
  string__93_309 = from_latin_1_string("L", 1);
  string__93_311 = from_latin_1_string("l", 1);
  string__93_313 = from_latin_1_string("L", 1);
  string__93_315 = from_latin_1_string("l", 1);
  string__93_317 = from_latin_1_string("L", 1);
  string__93_319 = from_latin_1_string("l", 1);
  string__93_321 = from_latin_1_string("L", 1);
  string__93_323 = from_latin_1_string("l", 1);
  string__93_325 = from_latin_1_string("N", 1);
  string__93_327 = from_latin_1_string("n", 1);
  string__93_329 = from_latin_1_string("N", 1);
  string__93_331 = from_latin_1_string("n", 1);
  string__93_333 = from_latin_1_string("N", 1);
  string__93_335 = from_latin_1_string("n", 1);
  string__93_337 = from_latin_1_string("n", 1);
  string__93_339 = from_latin_1_string("N", 1);
  string__93_341 = from_latin_1_string("n", 1);
  string__93_343 = from_latin_1_string("O", 1);
  string__93_345 = from_latin_1_string("o", 1);
  string__93_347 = from_latin_1_string("O", 1);
  string__93_349 = from_latin_1_string("o", 1);
  string__93_351 = from_latin_1_string("O", 1);
  string__93_353 = from_latin_1_string("O", 1);
  string__93_355 = from_latin_1_string("OE", 2);
  string__93_357 = from_latin_1_string("oe", 2);
  string__93_359 = from_latin_1_string("R", 1);
  string__93_361 = from_latin_1_string("r", 1);
  string__93_363 = from_latin_1_string("R", 1);
  string__93_365 = from_latin_1_string("r", 1);
  string__93_367 = from_latin_1_string("R", 1);
  string__93_369 = from_latin_1_string("r", 1);
  string__93_371 = from_latin_1_string("S", 1);
  string__93_373 = from_latin_1_string("s", 1);
  string__93_375 = from_latin_1_string("S", 1);
  string__93_377 = from_latin_1_string("s", 1);
  string__93_379 = from_latin_1_string("S", 1);
  string__93_381 = from_latin_1_string("s", 1);
  string__93_383 = from_latin_1_string("S", 1);
  string__93_385 = from_latin_1_string("s", 1);
  string__93_387 = from_latin_1_string("T", 1);
  string__93_389 = from_latin_1_string("t", 1);
  string__93_391 = from_latin_1_string("T", 1);
  string__93_393 = from_latin_1_string("t", 1);
  string__93_395 = from_latin_1_string("T", 1);
  string__93_397 = from_latin_1_string("t", 1);
  string__93_399 = from_latin_1_string("U", 1);
  string__93_401 = from_latin_1_string("u", 1);
  string__93_403 = from_latin_1_string("U", 1);
  string__93_405 = from_latin_1_string("u", 1);
  string__93_407 = from_latin_1_string("U", 1);
  string__93_409 = from_latin_1_string("u", 1);
  string__93_411 = from_latin_1_string("U", 1);
  string__93_413 = from_latin_1_string("u", 1);
  string__93_415 = from_latin_1_string("U", 1);
  string__93_417 = from_latin_1_string("u", 1);
  string__93_419 = from_latin_1_string("U", 1);
  string__93_421 = from_latin_1_string("u", 1);
  string__93_423 = from_latin_1_string("W", 1);
  string__93_425 = from_latin_1_string("w", 1);
  string__93_427 = from_latin_1_string("Y", 1);
  string__93_429 = from_latin_1_string("y", 1);
  string__93_431 = from_latin_1_string("Y", 1);
  string__93_433 = from_latin_1_string("Z", 1);
  string__93_435 = from_latin_1_string("z", 1);
  string__93_437 = from_latin_1_string("Z", 1);
  string__93_439 = from_latin_1_string("z", 1);
  string__93_441 = from_latin_1_string("Z", 1);
  string__93_443 = from_latin_1_string("z", 1);
  string__93_445 = from_latin_1_string("s", 1);
  string__93_447 = from_latin_1_string("b", 1);
  string__93_449 = from_latin_1_string("B", 1);
  string__93_451 = from_latin_1_string("B", 1);
  string__93_453 = from_latin_1_string("b", 1);
  string__93_455 = from_latin_1_string("b", 1);
  string__93_457 = from_latin_1_string("b", 1);
  string__93_459 = from_latin_1_string("C", 1);
  string__93_461 = from_latin_1_string("c", 1);
  string__93_463 = from_latin_1_string("D", 1);
  string__93_465 = from_latin_1_string("D", 1);
  string__93_467 = from_latin_1_string("D", 1);
  string__93_469 = from_latin_1_string("d", 1);
  string__93_471 = from_latin_1_string("g", 1);
  string__93_473 = from_latin_1_string("E", 1);
  string__93_475 = from_latin_1_string("F", 1);
  string__93_477 = from_latin_1_string("f", 1);
  string__93_479 = from_latin_1_string("G", 1);
  string__93_481 = from_latin_1_string("DZ", 2);
  string__93_483 = from_latin_1_string("Dz", 2);
  string__93_485 = from_latin_1_string("dz", 2);
  string__93_487 = from_latin_1_string("LJ", 2);
  string__93_489 = from_latin_1_string("Lj", 2);
  string__93_491 = from_latin_1_string("lj", 2);
  string__93_493 = from_latin_1_string("NJ", 2);
  string__93_495 = from_latin_1_string("Nj", 2);
  string__93_497 = from_latin_1_string("nj", 2);
  string__93_499 = from_latin_1_string("A", 1);
  string__93_501 = from_latin_1_string("a", 1);
  string__93_503 = from_latin_1_string("I", 1);
  string__93_505 = from_latin_1_string("i", 1);
  string__93_507 = from_latin_1_string("O", 1);
  string__93_509 = from_latin_1_string("o", 1);
  string__93_511 = from_latin_1_string("U", 1);
  string__93_513 = from_latin_1_string("u", 1);
  string__93_515 = from_latin_1_string("U", 1);
  string__93_517 = from_latin_1_string("u", 1);
  string__93_519 = from_latin_1_string("U", 1);
  string__93_521 = from_latin_1_string("u", 1);
  string__93_523 = from_latin_1_string("U", 1);
  string__93_525 = from_latin_1_string("u", 1);
  string__93_527 = from_latin_1_string("U", 1);
  string__93_529 = from_latin_1_string("u", 1);
  string__93_531 = from_latin_1_string("A", 1);
  string__93_533 = from_latin_1_string("a", 1);
  string__93_535 = from_latin_1_string("A", 1);
  string__93_537 = from_latin_1_string("a", 1);
  string__93_539 = from_latin_1_string("AE", 2);
  string__93_541 = from_latin_1_string("ae", 2);
  string__93_543 = from_latin_1_string("G", 1);
  string__93_545 = from_latin_1_string("g", 1);
  string__93_547 = from_latin_1_string("G", 1);
  string__93_549 = from_latin_1_string("g", 1);
  string__93_551 = from_latin_1_string("K", 1);
  string__93_553 = from_latin_1_string("k", 1);
  string__93_555 = from_latin_1_string("O", 1);
  string__93_557 = from_latin_1_string("o", 1);
  string__93_559 = from_latin_1_string("O", 1);
  string__93_561 = from_latin_1_string("o", 1);
  string__93_563 = from_latin_1_string("DZ", 2);
  string__93_565 = from_latin_1_string("Dz", 2);
  string__93_567 = from_latin_1_string("dz", 2);
  string__93_569 = from_latin_1_string("G", 1);
  string__93_571 = from_latin_1_string("g", 1);
  string__93_573 = from_latin_1_string("N", 1);
  string__93_575 = from_latin_1_string("n", 1);
  string__93_577 = from_latin_1_string("A", 1);
  string__93_579 = from_latin_1_string("a", 1);
  string__93_581 = from_latin_1_string("AE", 2);
  string__93_583 = from_latin_1_string("ae", 2);
  string__93_585 = from_latin_1_string("O", 1);
  string__93_587 = from_latin_1_string("o", 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__string(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
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
  define_method("types", "string", poly_idx__to_integer, func__1_1);
  define_method("types", "string", poly_idx__to_real, func__2_1);
  define_method("types", "string", poly_idx__parse_number, func__3_1);
  define_method("types", "string", poly_idx__to_number, func__4_1);
  define_method("types", "string", poly_idx__put, func__5_1);
  define_method("types", "string", poly_idx__write_to, func__6_1);
  define_method("types", "string", poly_idx__numerically_less, func__7_1);
  define_method("types", "string", poly_idx__to_list, func__8_1);
  define_method("types", "string", poly_idx__dup, func__10_1);
  define_method("types", "string", poly_idx__match_character, func__15_1);
  define_method("types", "string", poly_idx__grammar__match, func__16_1);
  define_method("types", "string", poly_idx__match, func__17_1);
  define_method("types", "string", poly_idx__search_character, func__18_1);
  define_method("types", "string", poly_idx__search, func__19_1);
  define_method("types", "string", poly_idx__before, func__20_1);
  define_method("types", "string", poly_idx__truncate_from, func__21_1);
  define_method("types", "string", poly_idx__behind, func__22_1);
  define_method("types", "string", poly_idx__truncate_until, func__23_1);
  define_method("types", "string", poly_idx__from, func__24_1);
  define_method("types", "string", poly_idx__truncate_before, func__25_1);
  define_method("types", "string", poly_idx__until, func__26_1);
  define_method("types", "string", poly_idx__truncate_behind, func__27_1);
  define_method("types", "string", poly_idx__between, func__28_1);
  define_method("types", "string", poly_idx__has_prefix, func__29_1);
  define_method("types", "string", poly_idx__has_suffix, func__30_1);
  define_method("types", "string", poly_idx__without_prefix, func__31_1);
  define_method("types", "string", poly_idx__without_suffix, func__32_1);
  define_method("types", "string", poly_idx__matches, func__38_1);
  define_method("types", "string", poly_idx__contains, func__39_1);
  define_method("types", "string", poly_idx__to_lower_case, func__47_1);
  define_method("types", "string", poly_idx__to_upper_case, func__48_1);
  define_method("types", "string", poly_idx__to_title_case, func__49_1);
  define_method("types", "octet_string", poly_idx__new_empty_collection, func__50_1);
  define_method("types", "quad_octet_string", poly_idx__new_empty_collection, func__51_1);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__string(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_variable(&var.std__string, &func__9_1);
  assign_variable(&var.std__pad_left, &func__11_1);
  assign_variable(&var.std__pad_right, &func__12_1);
  assign_variable(&var.std__truncate, &func__13_1);
  assign_variable(&var.std__pad_or_truncate, &func__14_1);
  assign_variable(&var.std__trim, &func__33_1);
  assign_variable(&var.std__normalize, &func__34_1);
  assign_variable(&var.std__split, &func__35_1);
  assign_variable(&var.std__join, &func__36_1);
  assign_variable(&var.std__count_occurrences, &func__37_1);
  assign_variable(&var.std__replace_umlauts, &func__41_1);
  assign_variable(&var.std__replace_all, &func__42_1);
  assign_value(&var._eighty_spaces, string__43_1);
  assign_variable(&var.std__spaces, &func__44_1);
  assign_variable(&var.std__indented, &func__45_1);
  assign_variable(&var.std__for_each_line, &func__46_1);
  assign_variable(&var.std__collect_output, &func__52_1);
  assign_variable(&var.std__concatenate, &func__53_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__string(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__1_1, create_function(entry__1_1, 1));
  assign_value(&func__2_1, create_function(entry__2_1, 1));
  assign_value(&func__3_1, create_function(entry__3_1, 1));
  assign_value(&func__4_1, create_function(entry__4_1, 1));
  assign_value(&func__5_1, create_function(entry__5_1, 2));
  assign_value(&func__6_1, create_function(entry__6_1, -1));
  assign_value(&func__7_1, create_function(entry__7_1, 2));
  assign_value(&func__8_1, create_function(entry__8_1, 1));
  assign_value(&func__9_1, create_function(entry__9_1, -1));
  assign_value(&func__10_6, create_function(entry__10_6, 0));
  assign_value(&func__10_1, create_function(entry__10_1, 2));
  assign_value(&func__11_1, create_function(entry__11_1, -1));
  assign_value(&func__12_1, create_function(entry__12_1, -1));
  assign_value(&func__13_1, create_function(entry__13_1, 2));
  assign_value(&func__14_1, create_function(entry__14_1, 2));
  assign_value(&func__15_8, create_function(entry__15_8, 0));
  assign_value(&func__15_9, create_function(entry__15_9, 0));
  assign_value(&func__15_1, create_function(entry__15_1, 2));
  assign_value(&func__16_1, create_function(entry__16_1, 2));
  assign_value(&func__17_1, create_function(entry__17_1, 2));
  assign_value(&func__18_13, create_function(entry__18_13, 0));
  assign_value(&func__18_1, create_function(entry__18_1, -1));
  assign_value(&func__19_1, create_function(entry__19_1, 2));
  assign_value(&func__20_1, create_function(entry__20_1, -1));
  assign_value(&func__21_1, create_function(entry__21_1, -1));
  assign_value(&func__22_1, create_function(entry__22_1, -1));
  assign_value(&func__23_1, create_function(entry__23_1, -1));
  assign_value(&func__24_1, create_function(entry__24_1, -1));
  assign_value(&func__25_1, create_function(entry__25_1, -1));
  assign_value(&func__26_1, create_function(entry__26_1, -1));
  assign_value(&func__27_1, create_function(entry__27_1, -1));
  assign_value(&func__28_1, create_function(entry__28_1, -1));
  assign_value(&func__29_1, create_function(entry__29_1, 2));
  assign_value(&func__30_1, create_function(entry__30_1, 2));
  assign_value(&func__31_1, create_function(entry__31_1, 2));
  assign_value(&func__32_1, create_function(entry__32_1, 2));
  assign_value(&func__33_1, create_function(entry__33_1, 1));
  assign_value(&func__34_1, create_function(entry__34_1, 1));
  assign_value(&func__35_1, create_function(entry__35_1, -1));
  assign_value(&func__36_1, create_function(entry__36_1, -1));
  assign_value(&func__37_1, create_function(entry__37_1, 2));
  assign_value(&func__38_1, create_function(entry__38_1, 2));
  assign_value(&func__39_1, create_function(entry__39_1, 2));
  assign_value(&func__41_1, create_function(entry__41_1, 1));
  assign_value(&func__42_1, create_function(entry__42_1, -1));
  assign_value(&func__44_1, create_function(entry__44_1, 1));
  assign_value(&func__45_1, create_function(entry__45_1, 2));
  assign_value(&func__46_1, create_function(entry__46_1, -1));
  assign_value(&func__47_1, create_function(entry__47_1, 1));
  assign_value(&func__48_1, create_function(entry__48_1, 1));
  assign_value(&func__49_1, create_function(entry__49_1, 1));
  assign_value(&func__50_1, create_function(entry__50_1, 1));
  assign_value(&func__51_1, create_function(entry__51_1, 1));
  assign_value(&func__52_1, create_function(entry__52_1, -1));
  assign_value(&func__53_1, create_function(entry__53_1, -1));
  register_collector(collect__basic__types__string);
}
