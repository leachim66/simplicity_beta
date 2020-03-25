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
IMPORT NODE *get_dynamic_cell(int id);
IMPORT void set_dynamic_cell(int id, NODE *node);
IMPORT void define_dynamic_cell(int id, NODE *node);
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
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT NODE *undefined;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
typedef void (*NODE_SETTER)(NODE *);
IMPORT void define_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter, NODE_SETTER definer,
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
static NODE_GETTER get__WHITESPACE_CHARACTER;
static NODE_GETTER get_value_or_future__WHITESPACE_CHARACTER;
static NODE_GETTER get__default_value;
static NODE_GETTER get_value_or_future__default_value;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__has_minimum_length;
static NODE_GETTER get_value_or_future__has_minimum_length;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__lower_bound_of;
static NODE_GETTER get_value_or_future__lower_bound_of;
static NODE_GETTER get__many;
static NODE_GETTER get_value_or_future__many;
static NODE_GETTER get__match_character;
static NODE_GETTER get_value_or_future__match_character;
static NODE_GETTER get__minus;
static NODE_GETTER get_value_or_future__minus;
static NODE_GETTER get__negate;
static NODE_GETTER get_value_or_future__negate;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
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
static NODE_GETTER get__types__character;
static NODE_GETTER get_value_or_future__types__character;
static NODE_GETTER get__types__list;
static NODE_GETTER get_value_or_future__types__list;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__types__value_range;
static NODE_GETTER get_value_or_future__types__value_range;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__upper_bound_of;
static NODE_GETTER get_value_or_future__upper_bound_of;
static struct {
  NODE *_expr_of;
  NODE *_alternatives_of;
  NODE *_setter_of;
  NODE *_node_of;
  NODE *_function_of;
  NODE *grammar__match;
  NODE *grammar__search;
  NODE *types__grammar_object;
  NODE *types__grammar_node;
  NODE *types__optional;
  NODE *std__optional;
  NODE *types__many;
  NODE *std__many;
  NODE *types__some;
  NODE *std__some;
  NODE *types__alt;
  NODE *std__alt;
  NODE *types__followed_by;
  NODE *std__followed_by;
  NODE *types__not_followed_by;
  NODE *std__not_followed_by;
  NODE *types__capture;
  NODE *std__capture;
  NODE *types__multi_capture;
  NODE *std__multi_capture;
  NODE *types__span;
  NODE *std__span;
  NODE *types__multi_span;
  NODE *std__multi_span;
  NODE *types__set_node;
  NODE *std__set_node;
  NODE *types__inspect_node;
  NODE *std__inspect_node;
  NODE *types__modify_node;
  NODE *std__modify_node;
  NODE *types__check_node;
  NODE *std__check_node;
  NODE *types__grammar_action;
  NODE *std__grammar_action;
  NODE *types__set_field;
  NODE *std__set_field;
  NODE *std__END_OF_TEXT;
  NODE *std__LETTER;
  NODE *std__UPPER_CASE_LETTER;
  NODE *std__LOWER_CASE_LETTER;
  NODE *std__DIGIT;
  NODE *std__WHITESPACE_CHARACTER;
  NODE *std__WHITESPACE;
  NODE *std__PRINTABLE_CHARACTER;
  NODE *std__NON_SPACE_CHARACTER;
  NODE *std__ANY_CHARACTER;
} var;
static const char *var_names[] = {
  "expr_of",
  "alternatives_of",
  "setter_of",
  "node_of",
  "function_of"
};
static int poly_idx__grammar__match;
static void type__grammar__match(void);
static NODE *get__grammar__match(void) {
  return var.grammar__match;
}
static int poly_idx__grammar__search;
static void type__grammar__search(void);
static NODE *get__grammar__search(void) {
  return var.grammar__search;
}
static NODE *get__types__grammar_object(void) {
  return var.types__grammar_object;
}
static NODE *get__types__grammar_node(void) {
  return var.types__grammar_node;
}
static int dyna_idx__grammar__current_node;
static NODE *get__grammar__current_node(void) {
  return get_dynamic_cell(dyna_idx__grammar__current_node);
}
static void set__grammar__current_node(NODE *node) {
  set_dynamic_cell(dyna_idx__grammar__current_node, node);
}
static void define__grammar__current_node(NODE *node) {
  define_dynamic_cell(dyna_idx__grammar__current_node, node);
}
static int poly_idx__expr_of;
static void type__expr_of(void);
static int poly_idx__alternatives_of;
static void type__alternatives_of(void);
static int poly_idx__setter_of;
static void type__setter_of(void);
static int poly_idx__node_of;
static void type__node_of(void);
static int poly_idx__function_of;
static void type__function_of(void);
static NODE *get__types__optional(void) {
  return var.types__optional;
}
static NODE *func__12_1_types__optional_grammar__match;
static void entry__12_1_types__optional_grammar__match(void);
static FRAME_INFO frame__12_1_types__optional_grammar__match = {2, {"self", "stream"}};
static void cont__12_2(void);
static void cont__12_3(void);
static void cont__12_4(void);
static NODE *func__13_1_std__optional;
static void entry__13_1_std__optional(void);
static FRAME_INFO frame__13_1_std__optional = {1, {"expr"}};
static NODE *get__std__optional(void) {
  return var.std__optional;
}
static NODE *get__types__many(void) {
  return var.types__many;
}
static NODE *func__15_1_types__many_grammar__match;
static void entry__15_1_types__many_grammar__match(void);
static FRAME_INFO frame__15_1_types__many_grammar__match = {4, {"self", "stream", "return", "len"}};
static NODE *func__15_2;
static void entry__15_2(void);
static FRAME_INFO frame__15_2 = {5, {"self", "stream", "return", "len", "n"}};
static void cont__15_3(void);
static void cont__15_4(void);
static void cont__15_5(void);
static NODE *func__15_6;
static void entry__15_6(void);
static FRAME_INFO frame__15_6 = {2, {"return", "len"}};
static void cont__15_7(void);
static void cont__15_8(void);
static NODE *func__15_9;
static void entry__15_9(void);
static FRAME_INFO frame__15_9 = {2, {"len", "n"}};
static void cont__15_10(void);
static NODE *func__15_11;
static void entry__15_11(void);
static FRAME_INFO frame__15_11 = {2, {"len", "n"}};
static void cont__15_12(void);
static void cont__15_13(void);
static NODE *func__15_14;
static void entry__15_14(void);
static FRAME_INFO frame__15_14 = {2, {"return", "len"}};
static void cont__15_15(void);
static void cont__15_16(void);
static void cont__15_17(void);
static void cont__15_18(void);
static void cont__15_19(void);
static NODE *func__16_1_std__many;
static void entry__16_1_std__many(void);
static FRAME_INFO frame__16_1_std__many = {1, {"expr"}};
static NODE *get__std__many(void) {
  return var.std__many;
}
static NODE *get__types__some(void) {
  return var.types__some;
}
static NODE *func__18_1_types__some_grammar__match;
static void entry__18_1_types__some_grammar__match(void);
static FRAME_INFO frame__18_1_types__some_grammar__match = {4, {"self", "stream", "return", "len"}};
static NODE *func__18_2;
static void entry__18_2(void);
static FRAME_INFO frame__18_2 = {5, {"self", "stream", "return", "len", "n"}};
static void cont__18_3(void);
static void cont__18_4(void);
static void cont__18_5(void);
static NODE *func__18_6;
static void entry__18_6(void);
static FRAME_INFO frame__18_6 = {2, {"return", "len"}};
static void cont__18_7(void);
static void cont__18_8(void);
static NODE *func__18_9;
static void entry__18_9(void);
static FRAME_INFO frame__18_9 = {2, {"len", "n"}};
static void cont__18_10(void);
static NODE *func__18_11;
static void entry__18_11(void);
static FRAME_INFO frame__18_11 = {2, {"len", "n"}};
static void cont__18_12(void);
static void cont__18_13(void);
static NODE *func__18_14;
static void entry__18_14(void);
static FRAME_INFO frame__18_14 = {2, {"return", "len"}};
static void cont__18_15(void);
static void cont__18_16(void);
static void cont__18_17(void);
static void cont__18_18(void);
static void cont__18_19(void);
static NODE *func__19_1_std__some;
static void entry__19_1_std__some(void);
static FRAME_INFO frame__19_1_std__some = {1, {"expr"}};
static NODE *get__std__some(void) {
  return var.std__some;
}
static NODE *get__types__alt(void) {
  return var.types__alt;
}
static NODE *func__21_1_types__alt_grammar__match;
static void entry__21_1_types__alt_grammar__match(void);
static FRAME_INFO frame__21_1_types__alt_grammar__match = {4, {"self", "stream", "return", "alternatives"}};
static void cont__21_2(void);
static NODE *func__21_3;
static void entry__21_3(void);
static FRAME_INFO frame__21_3 = {4, {"alternative", "stream", "return", "n"}};
static void cont__21_4(void);
static void cont__21_5(void);
static NODE *func__21_6;
static void entry__21_6(void);
static FRAME_INFO frame__21_6 = {2, {"return", "n"}};
static void cont__21_7(void);
static NODE *func__22_1_std__alt;
static void entry__22_1_std__alt(void);
static FRAME_INFO frame__22_1_std__alt = {1, {"alternatives"}};
static NODE *get__std__alt(void) {
  return var.std__alt;
}
static NODE *get__types__followed_by(void) {
  return var.types__followed_by;
}
static NODE *func__24_1_types__followed_by_grammar__match;
static void entry__24_1_types__followed_by_grammar__match(void);
static FRAME_INFO frame__24_1_types__followed_by_grammar__match = {4, {"self", "stream", "return", "original_node"}};
static void cont__24_2(void);
static void cont__24_3(void);
static void cont__24_4(void);
static NODE *func__24_5;
static void entry__24_5(void);
static FRAME_INFO frame__24_5 = {2, {"original_node", "return"}};
static NODE *func__24_6;
static void entry__24_6(void);
static FRAME_INFO frame__24_6 = {1, {"return"}};
static void cont__24_7(void);
static NODE *func__25_1_std__followed_by;
static void entry__25_1_std__followed_by(void);
static FRAME_INFO frame__25_1_std__followed_by = {1, {"expr"}};
static NODE *get__std__followed_by(void) {
  return var.std__followed_by;
}
static NODE *get__types__not_followed_by(void) {
  return var.types__not_followed_by;
}
static NODE *func__27_1_types__not_followed_by_grammar__match;
static void entry__27_1_types__not_followed_by_grammar__match(void);
static FRAME_INFO frame__27_1_types__not_followed_by_grammar__match = {4, {"self", "stream", "return", "original_node"}};
static void cont__27_2(void);
static void cont__27_3(void);
static void cont__27_4(void);
static NODE *func__27_5;
static void entry__27_5(void);
static FRAME_INFO frame__27_5 = {2, {"original_node", "return"}};
static NODE *func__27_6;
static void entry__27_6(void);
static FRAME_INFO frame__27_6 = {1, {"return"}};
static void cont__27_7(void);
static NODE *func__28_1_std__not_followed_by;
static void entry__28_1_std__not_followed_by(void);
static FRAME_INFO frame__28_1_std__not_followed_by = {1, {"expr"}};
static NODE *get__std__not_followed_by(void) {
  return var.std__not_followed_by;
}
static NODE *get__types__capture(void) {
  return var.types__capture;
}
static NODE *func__30_1_types__capture_grammar__match;
static void entry__30_1_types__capture_grammar__match(void);
static FRAME_INFO frame__30_1_types__capture_grammar__match = {3, {"self", "stream", "len"}};
static void cont__30_2(void);
static void cont__30_3(void);
static void cont__30_4(void);
static NODE *func__30_5;
static void entry__30_5(void);
static FRAME_INFO frame__30_5 = {5, {"self", "stream", "len", "setter", "value"}};
static void cont__30_6(void);
static void cont__30_7(void);
static void cont__30_8(void);
static NODE *func__30_9;
static void entry__30_9(void);
static FRAME_INFO frame__30_9 = {2, {"setter", "value"}};
static void cont__30_10(void);
static NODE *func__30_11;
static void entry__30_11(void);
static FRAME_INFO frame__30_11 = {1, {"value"}};
static void cont__30_12(void);
static NODE *func__31_1_std__capture;
static void entry__31_1_std__capture(void);
static FRAME_INFO frame__31_1_std__capture = {2, {"setter", "expr"}};
static NODE *get__std__capture(void) {
  return var.std__capture;
}
static NODE *get__types__multi_capture(void) {
  return var.types__multi_capture;
}
static NODE *func__33_1_types__multi_capture_grammar__match;
static void entry__33_1_types__multi_capture_grammar__match(void);
static FRAME_INFO frame__33_1_types__multi_capture_grammar__match = {3, {"self", "stream", "len"}};
static void cont__33_2(void);
static void cont__33_3(void);
static void cont__33_4(void);
static NODE *func__33_5;
static void entry__33_5(void);
static FRAME_INFO frame__33_5 = {5, {"self", "stream", "len", "setter", "value"}};
static void cont__33_6(void);
static void cont__33_7(void);
static void cont__33_8(void);
static NODE *func__33_9;
static void entry__33_9(void);
static FRAME_INFO frame__33_9 = {3, {"setter", "self", "value"}};
static void cont__33_10(void);
static void cont__33_11(void);
static void cont__33_12(void);
static void cont__33_13(void);
static NODE *func__33_14;
static void entry__33_14(void);
static FRAME_INFO frame__33_14 = {1, {"value"}};
static void cont__33_15(void);
static void cont__33_16(void);
static NODE *func__34_1_std__multi_capture;
static void entry__34_1_std__multi_capture(void);
static FRAME_INFO frame__34_1_std__multi_capture = {2, {"setter", "expr"}};
static NODE *get__std__multi_capture(void) {
  return var.std__multi_capture;
}
static NODE *get__types__span(void) {
  return var.types__span;
}
static NODE *func__36_1_types__span_grammar__match;
static void entry__36_1_types__span_grammar__match(void);
static FRAME_INFO frame__36_1_types__span_grammar__match = {5, {"self", "stream", "return", "outer_node", "len"}};
static NODE *func__36_2;
static void entry__36_2(void);
static FRAME_INFO frame__36_2 = {6, {"return__1", "len", "self", "stream", "return", "outer_node"}};
static void cont__36_3(void);
static void cont__36_4(void);
static void cont__36_5(void);
static NODE *func__36_6;
static void entry__36_6(void);
static FRAME_INFO frame__36_6 = {1, {"return"}};
static void cont__36_7(void);
static void cont__36_8(void);
static void cont__36_9(void);
static void cont__36_10(void);
static NODE *func__37_1_std__span;
static void entry__37_1_std__span(void);
static FRAME_INFO frame__37_1_std__span = {2, {"setter", "expr"}};
static NODE *get__std__span(void) {
  return var.std__span;
}
static NODE *get__types__multi_span(void) {
  return var.types__multi_span;
}
static NODE *func__39_1_types__multi_span_grammar__match;
static void entry__39_1_types__multi_span_grammar__match(void);
static FRAME_INFO frame__39_1_types__multi_span_grammar__match = {5, {"self", "stream", "return", "outer_node", "len"}};
static NODE *func__39_2;
static void entry__39_2(void);
static FRAME_INFO frame__39_2 = {7, {"return__1", "len", "self", "stream", "return", "outer_node", "setter"}};
static void cont__39_3(void);
static void cont__39_4(void);
static void cont__39_5(void);
static NODE *func__39_6;
static void entry__39_6(void);
static FRAME_INFO frame__39_6 = {1, {"return"}};
static void cont__39_7(void);
static void cont__39_8(void);
static void cont__39_9(void);
static NODE *func__39_10;
static void entry__39_10(void);
static FRAME_INFO frame__39_10 = {2, {"setter", "outer_node"}};
static void cont__39_11(void);
static void cont__39_12(void);
static void cont__39_13(void);
static NODE *func__39_14;
static void entry__39_14(void);
static FRAME_INFO frame__39_14 = {1, {"outer_node"}};
static void cont__39_15(void);
static void cont__39_16(void);
static void cont__39_17(void);
static NODE *func__40_1_std__multi_span;
static void entry__40_1_std__multi_span(void);
static FRAME_INFO frame__40_1_std__multi_span = {2, {"setter", "expr"}};
static NODE *get__std__multi_span(void) {
  return var.std__multi_span;
}
static NODE *get__types__set_node(void) {
  return var.types__set_node;
}
static NODE *func__42_1_types__set_node_grammar__match;
static void entry__42_1_types__set_node_grammar__match(void);
static FRAME_INFO frame__42_1_types__set_node_grammar__match = {2, {"self", "stream"}};
static void cont__42_2(void);
static NODE *func__43_1_std__set_node;
static void entry__43_1_std__set_node(void);
static FRAME_INFO frame__43_1_std__set_node = {1, {"node"}};
static NODE *get__std__set_node(void) {
  return var.std__set_node;
}
static NODE *get__types__inspect_node(void) {
  return var.types__inspect_node;
}
static NODE *func__45_1_types__inspect_node_grammar__match;
static void entry__45_1_types__inspect_node_grammar__match(void);
static FRAME_INFO frame__45_1_types__inspect_node_grammar__match = {3, {"self", "stream", "func"}};
static void cont__45_2(void);
static void cont__45_3(void);
static void cont__45_4(void);
static NODE *func__45_5;
static void entry__45_5(void);
static FRAME_INFO frame__45_5 = {2, {"func", "stream"}};
static NODE *func__45_6;
static void entry__45_6(void);
static FRAME_INFO frame__45_6 = {1, {"func"}};
static void cont__45_7(void);
static NODE *func__46_1_std__inspect_node;
static void entry__46_1_std__inspect_node(void);
static FRAME_INFO frame__46_1_std__inspect_node = {1, {"func"}};
static NODE *get__std__inspect_node(void) {
  return var.std__inspect_node;
}
static NODE *get__types__modify_node(void) {
  return var.types__modify_node;
}
static NODE *func__48_1_types__modify_node_grammar__match;
static void entry__48_1_types__modify_node_grammar__match(void);
static FRAME_INFO frame__48_1_types__modify_node_grammar__match = {3, {"self", "stream", "func"}};
static void cont__48_2(void);
static void cont__48_3(void);
static void cont__48_4(void);
static NODE *func__48_5;
static void entry__48_5(void);
static FRAME_INFO frame__48_5 = {2, {"func", "stream"}};
static void cont__48_6(void);
static NODE *func__48_7;
static void entry__48_7(void);
static FRAME_INFO frame__48_7 = {1, {"func"}};
static void cont__48_8(void);
static void cont__48_9(void);
static NODE *func__49_1_std__modify_node;
static void entry__49_1_std__modify_node(void);
static FRAME_INFO frame__49_1_std__modify_node = {1, {"func"}};
static NODE *get__std__modify_node(void) {
  return var.std__modify_node;
}
static NODE *get__types__check_node(void) {
  return var.types__check_node;
}
static NODE *func__51_1_types__check_node_grammar__match;
static void entry__51_1_types__check_node_grammar__match(void);
static FRAME_INFO frame__51_1_types__check_node_grammar__match = {4, {"self", "stream", "return", "func"}};
static void cont__51_2(void);
static void cont__51_3(void);
static void cont__51_4(void);
static NODE *func__51_5;
static void entry__51_5(void);
static FRAME_INFO frame__51_5 = {3, {"func", "stream", "return"}};
static void cont__51_6(void);
static NODE *func__51_7;
static void entry__51_7(void);
static FRAME_INFO frame__51_7 = {1, {"return"}};
static NODE *func__51_8;
static void entry__51_8(void);
static FRAME_INFO frame__51_8 = {2, {"func", "return"}};
static void cont__51_9(void);
static NODE *func__51_10;
static void entry__51_10(void);
static FRAME_INFO frame__51_10 = {1, {"return"}};
static void cont__51_11(void);
static NODE *func__52_1_std__check_node;
static void entry__52_1_std__check_node(void);
static FRAME_INFO frame__52_1_std__check_node = {1, {"func"}};
static NODE *get__std__check_node(void) {
  return var.std__check_node;
}
static NODE *get__types__grammar_action(void) {
  return var.types__grammar_action;
}
static NODE *func__54_1_types__grammar_action_grammar__match;
static void entry__54_1_types__grammar_action_grammar__match(void);
static FRAME_INFO frame__54_1_types__grammar_action_grammar__match = {2, {"self", "stream"}};
static void cont__54_2(void);
static void cont__54_3(void);
static NODE *func__55_1_std__grammar_action;
static void entry__55_1_std__grammar_action(void);
static FRAME_INFO frame__55_1_std__grammar_action = {1, {"func"}};
static NODE *get__std__grammar_action(void) {
  return var.std__grammar_action;
}
static NODE *get__types__set_field(void) {
  return var.types__set_field;
}
static NODE *func__57_1_types__set_field_grammar__match;
static void entry__57_1_types__set_field_grammar__match(void);
static FRAME_INFO frame__57_1_types__set_field_grammar__match = {2, {"self", "stream"}};
static void cont__57_2(void);
static void cont__57_3(void);
static void cont__57_4(void);
static NODE *func__58_1_std__set_field;
static void entry__58_1_std__set_field(void);
static FRAME_INFO frame__58_1_std__set_field = {2, {"setter", "expr"}};
static NODE *get__std__set_field(void) {
  return var.std__set_field;
}
static NODE *get__std__END_OF_TEXT(void) {
  return var.std__END_OF_TEXT;
}
static NODE *func__60_1_std__END_OF_TEXT_grammar__match;
static void entry__60_1_std__END_OF_TEXT_grammar__match(void);
static FRAME_INFO frame__60_1_std__END_OF_TEXT_grammar__match = {2, {"self", "stream"}};
static void cont__60_2(void);
static NODE *func__60_3;
static void entry__60_3(void);
static FRAME_INFO frame__60_3 = {0, {}};
static NODE *func__60_4;
static void entry__60_4(void);
static FRAME_INFO frame__60_4 = {0, {}};
static NODE *get__std__LETTER(void) {
  return var.std__LETTER;
}
static NODE *func__62_1_std__LETTER_grammar__match;
static void entry__62_1_std__LETTER_grammar__match(void);
static FRAME_INFO frame__62_1_std__LETTER_grammar__match = {3, {"self", "stream", "return"}};
static void cont__62_2(void);
static NODE *func__62_3;
static void entry__62_3(void);
static FRAME_INFO frame__62_3 = {1, {"return"}};
static void cont__62_4(void);
static void cont__62_5(void);
static void cont__62_6(void);
static void cont__62_7(void);
static NODE *func__62_8;
static void entry__62_8(void);
static FRAME_INFO frame__62_8 = {1, {"stream"}};
static void cont__62_9(void);
static void cont__62_10(void);
static void cont__62_11(void);
static void cont__62_12(void);
static NODE *func__62_13;
static void entry__62_13(void);
static FRAME_INFO frame__62_13 = {1, {"stream"}};
static void cont__62_14(void);
static void cont__62_15(void);
static void cont__62_16(void);
static NODE *func__62_17;
static void entry__62_17(void);
static FRAME_INFO frame__62_17 = {1, {"stream"}};
static void cont__62_18(void);
static void cont__62_19(void);
static void cont__62_20(void);
static void cont__62_21(void);
static void cont__62_22(void);
static NODE *func__62_23;
static void entry__62_23(void);
static FRAME_INFO frame__62_23 = {1, {"return"}};
static void cont__62_24(void);
static NODE *get__std__UPPER_CASE_LETTER(void) {
  return var.std__UPPER_CASE_LETTER;
}
static NODE *func__64_1_std__UPPER_CASE_LETTER_grammar__match;
static void entry__64_1_std__UPPER_CASE_LETTER_grammar__match(void);
static FRAME_INFO frame__64_1_std__UPPER_CASE_LETTER_grammar__match = {3, {"self", "stream", "return"}};
static void cont__64_2(void);
static NODE *func__64_3;
static void entry__64_3(void);
static FRAME_INFO frame__64_3 = {1, {"return"}};
static void cont__64_4(void);
static void cont__64_5(void);
static void cont__64_6(void);
static void cont__64_7(void);
static NODE *func__64_8;
static void entry__64_8(void);
static FRAME_INFO frame__64_8 = {1, {"stream"}};
static void cont__64_9(void);
static void cont__64_10(void);
static void cont__64_11(void);
static void cont__64_12(void);
static NODE *func__64_13;
static void entry__64_13(void);
static FRAME_INFO frame__64_13 = {1, {"return"}};
static void cont__64_14(void);
static NODE *get__std__LOWER_CASE_LETTER(void) {
  return var.std__LOWER_CASE_LETTER;
}
static NODE *func__66_1_std__LOWER_CASE_LETTER_grammar__match;
static void entry__66_1_std__LOWER_CASE_LETTER_grammar__match(void);
static FRAME_INFO frame__66_1_std__LOWER_CASE_LETTER_grammar__match = {3, {"self", "stream", "return"}};
static void cont__66_2(void);
static NODE *func__66_3;
static void entry__66_3(void);
static FRAME_INFO frame__66_3 = {1, {"return"}};
static void cont__66_4(void);
static void cont__66_5(void);
static void cont__66_6(void);
static void cont__66_7(void);
static NODE *func__66_8;
static void entry__66_8(void);
static FRAME_INFO frame__66_8 = {1, {"stream"}};
static void cont__66_9(void);
static void cont__66_10(void);
static void cont__66_11(void);
static void cont__66_12(void);
static NODE *func__66_13;
static void entry__66_13(void);
static FRAME_INFO frame__66_13 = {1, {"return"}};
static void cont__66_14(void);
static NODE *get__std__DIGIT(void) {
  return var.std__DIGIT;
}
static NODE *func__68_1_std__DIGIT_grammar__match;
static void entry__68_1_std__DIGIT_grammar__match(void);
static FRAME_INFO frame__68_1_std__DIGIT_grammar__match = {3, {"self", "stream", "return"}};
static void cont__68_2(void);
static NODE *func__68_3;
static void entry__68_3(void);
static FRAME_INFO frame__68_3 = {1, {"return"}};
static void cont__68_4(void);
static void cont__68_5(void);
static void cont__68_6(void);
static void cont__68_7(void);
static NODE *func__68_8;
static void entry__68_8(void);
static FRAME_INFO frame__68_8 = {1, {"stream"}};
static void cont__68_9(void);
static void cont__68_10(void);
static void cont__68_11(void);
static void cont__68_12(void);
static NODE *func__68_13;
static void entry__68_13(void);
static FRAME_INFO frame__68_13 = {1, {"return"}};
static void cont__68_14(void);
static NODE *get__std__WHITESPACE_CHARACTER(void) {
  return var.std__WHITESPACE_CHARACTER;
}
static NODE *func__70_1_std__WHITESPACE_CHARACTER_grammar__match;
static void entry__70_1_std__WHITESPACE_CHARACTER_grammar__match(void);
static FRAME_INFO frame__70_1_std__WHITESPACE_CHARACTER_grammar__match = {4, {"self", "stream", "return", "chr"}};
static void cont__70_2(void);
static NODE *func__70_3;
static void entry__70_3(void);
static FRAME_INFO frame__70_3 = {1, {"return"}};
static void cont__70_4(void);
static void cont__70_5(void);
static void cont__70_6(void);
static void cont__70_7(void);
static NODE *func__70_8;
static void entry__70_8(void);
static FRAME_INFO frame__70_8 = {1, {"chr"}};
static void cont__70_9(void);
static void cont__70_10(void);
static NODE *func__70_11;
static void entry__70_11(void);
static FRAME_INFO frame__70_11 = {1, {"return"}};
static void cont__70_12(void);
static NODE *get__std__WHITESPACE(void) {
  return var.std__WHITESPACE;
}
static NODE *get__std__PRINTABLE_CHARACTER(void) {
  return var.std__PRINTABLE_CHARACTER;
}
static NODE *func__73_1_std__PRINTABLE_CHARACTER_grammar__match;
static void entry__73_1_std__PRINTABLE_CHARACTER_grammar__match(void);
static FRAME_INFO frame__73_1_std__PRINTABLE_CHARACTER_grammar__match = {4, {"self", "stream", "return", "chr"}};
static void cont__73_2(void);
static NODE *func__73_3;
static void entry__73_3(void);
static FRAME_INFO frame__73_3 = {1, {"return"}};
static void cont__73_4(void);
static void cont__73_5(void);
static void cont__73_6(void);
static void cont__73_7(void);
static NODE *func__73_8;
static void entry__73_8(void);
static FRAME_INFO frame__73_8 = {1, {"chr"}};
static void cont__73_9(void);
static void cont__73_10(void);
static NODE *func__73_11;
static void entry__73_11(void);
static FRAME_INFO frame__73_11 = {1, {"chr"}};
static void cont__73_12(void);
static void cont__73_13(void);
static void cont__73_14(void);
static NODE *func__73_15;
static void entry__73_15(void);
static FRAME_INFO frame__73_15 = {1, {"return"}};
static void cont__73_16(void);
static NODE *get__std__NON_SPACE_CHARACTER(void) {
  return var.std__NON_SPACE_CHARACTER;
}
static NODE *func__75_1_std__NON_SPACE_CHARACTER_grammar__match;
static void entry__75_1_std__NON_SPACE_CHARACTER_grammar__match(void);
static FRAME_INFO frame__75_1_std__NON_SPACE_CHARACTER_grammar__match = {4, {"self", "stream", "return", "chr"}};
static void cont__75_2(void);
static NODE *func__75_3;
static void entry__75_3(void);
static FRAME_INFO frame__75_3 = {1, {"return"}};
static void cont__75_4(void);
static void cont__75_5(void);
static void cont__75_6(void);
static NODE *func__75_7;
static void entry__75_7(void);
static FRAME_INFO frame__75_7 = {1, {"chr"}};
static void cont__75_8(void);
static void cont__75_9(void);
static NODE *func__75_10;
static void entry__75_10(void);
static FRAME_INFO frame__75_10 = {1, {"chr"}};
static void cont__75_11(void);
static void cont__75_12(void);
static void cont__75_13(void);
static NODE *func__75_14;
static void entry__75_14(void);
static FRAME_INFO frame__75_14 = {1, {"return"}};
static void cont__75_15(void);
static NODE *get__std__ANY_CHARACTER(void) {
  return var.std__ANY_CHARACTER;
}
static NODE *func__77_1_std__ANY_CHARACTER_grammar__match;
static void entry__77_1_std__ANY_CHARACTER_grammar__match(void);
static FRAME_INFO frame__77_1_std__ANY_CHARACTER_grammar__match = {3, {"self", "stream", "return"}};
static void cont__77_2(void);
static NODE *func__77_3;
static void entry__77_3(void);
static FRAME_INFO frame__77_3 = {1, {"return"}};
static void cont__77_4(void);
static NODE *func__78_1_types__character_grammar__match;
static void entry__78_1_types__character_grammar__match(void);
static FRAME_INFO frame__78_1_types__character_grammar__match = {2, {"chr", "stream"}};
static NODE *func__79_1_types__value_range_grammar__match;
static void entry__79_1_types__value_range_grammar__match(void);
static FRAME_INFO frame__79_1_types__value_range_grammar__match = {4, {"self", "stream", "return", "chr"}};
static void cont__79_2(void);
static NODE *func__79_3;
static void entry__79_3(void);
static FRAME_INFO frame__79_3 = {1, {"return"}};
static void cont__79_4(void);
static void cont__79_5(void);
static void cont__79_6(void);
static void cont__79_7(void);
static void cont__79_8(void);
static NODE *func__79_9;
static void entry__79_9(void);
static FRAME_INFO frame__79_9 = {2, {"self", "chr"}};
static void cont__79_10(void);
static void cont__79_11(void);
static void cont__79_12(void);
static void cont__79_13(void);
static NODE *func__79_14;
static void entry__79_14(void);
static FRAME_INFO frame__79_14 = {1, {"return"}};
static void cont__79_15(void);
static NODE *func__80_1_types__list_grammar__match;
static void entry__80_1_types__list_grammar__match(void);
static FRAME_INFO frame__80_1_types__list_grammar__match = {5, {"self", "stream", "return", "len", "original_node"}};
static NODE *func__80_2;
static void entry__80_2(void);
static FRAME_INFO frame__80_2 = {6, {"expr", "stream", "original_node", "return", "len", "n"}};
static void cont__80_3(void);
static void cont__80_4(void);
static NODE *func__80_5;
static void entry__80_5(void);
static FRAME_INFO frame__80_5 = {2, {"original_node", "return"}};
static void cont__80_6(void);
static void cont__80_7(void);
static void cont__80_8(void);
static void cont__80_9(void);
static void cont__80_10(void);
static void cont__80_11(void);
static NODE *func__81_1_types__object_grammar__search;
static void entry__81_1_types__object_grammar__search(void);
static FRAME_INFO frame__81_1_types__object_grammar__search = {6, {"expr", "stream", "nth", "return", "pos", "s"}};
static void cont__81_2(void);
static NODE *func__81_3;
static void entry__81_3(void);
static FRAME_INFO frame__81_3 = {5, {"expr", "s", "nth", "return", "pos"}};
static NODE *func__81_4;
static void entry__81_4(void);
static FRAME_INFO frame__81_4 = {6, {"expr", "s", "nth", "return", "pos", "len"}};
static void cont__81_5(void);
static void cont__81_6(void);
static NODE *func__81_7;
static void entry__81_7(void);
static FRAME_INFO frame__81_7 = {5, {"nth", "return", "pos", "len", "s"}};
static void cont__81_8(void);
static NODE *func__81_9;
static void entry__81_9(void);
static FRAME_INFO frame__81_9 = {3, {"return", "pos", "len"}};
static void cont__81_10(void);
static void cont__81_11(void);
static NODE *func__81_12;
static void entry__81_12(void);
static FRAME_INFO frame__81_12 = {3, {"pos", "len", "s"}};
static void cont__81_13(void);
static void cont__81_14(void);
static void cont__81_15(void);
static void cont__81_16(void);
static void cont__81_17(void);
static void cont__81_18(void);
static void cont__81_19(void);
static void cont__81_20(void);
static NODE *func__81_21;
static void entry__81_21(void);
static FRAME_INFO frame__81_21 = {1, {"return"}};
static void cont__81_22(void);
static void cont__81_23(void);
static void cont__81_24(void);
static void cont__81_25(void);
static NODE *func__81_26;
static void entry__81_26(void);
static FRAME_INFO frame__81_26 = {7, {"nth", "expr", "s", "pos", "return", "positions", "lengths"}};
static void cont__81_27(void);
static NODE *func__81_28;
static void entry__81_28(void);
static FRAME_INFO frame__81_28 = {8, {"expr", "s", "positions", "nth", "lengths", "pos", "return", "len"}};
static void cont__81_29(void);
static void cont__81_30(void);
static NODE *func__81_31;
static void entry__81_31(void);
static FRAME_INFO frame__81_31 = {6, {"positions", "nth", "lengths", "pos", "len", "s"}};
static void cont__81_32(void);
static void cont__81_33(void);
static void cont__81_34(void);
static NODE *func__81_35;
static void entry__81_35(void);
static FRAME_INFO frame__81_35 = {2, {"positions", "lengths"}};
static void cont__81_36(void);
static void cont__81_37(void);
static void cont__81_38(void);
static void cont__81_39(void);
static void cont__81_40(void);
static void cont__81_41(void);
static void cont__81_42(void);
static void cont__81_43(void);
static NODE *func__81_44;
static void entry__81_44(void);
static FRAME_INFO frame__81_44 = {3, {"pos", "len", "s"}};
static void cont__81_45(void);
static void cont__81_46(void);
static void cont__81_47(void);
static void cont__81_48(void);
static void cont__81_49(void);
static void cont__81_50(void);
static NODE *func__81_51;
static void entry__81_51(void);
static FRAME_INFO frame__81_51 = {4, {"positions", "nth", "return", "lengths"}};
static void cont__81_52(void);
static void cont__81_53(void);
static NODE *func__81_54;
static void entry__81_54(void);
static FRAME_INFO frame__81_54 = {1, {"return"}};
static void cont__81_55(void);
static void cont__81_56(void);
static void cont__81_57(void);
static void cont__81_58(void);
static void cont__81_59(void);
static void cont__81_60(void);
static void cont__81_61(void);
static void cont__81_62(void);
static void cont__152_1(void);
void run__basic__grammar(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__grammar__match, NULL, 23, 23, 2, 15},
  {type__grammar__search, NULL, 24, 24, 2, 16},
  {type__expr_of, NULL, 30, 30, 2, 8},
  {type__alternatives_of, NULL, 31, 31, 2, 16},
  {type__setter_of, NULL, 32, 32, 2, 10},
  {type__node_of, NULL, 33, 33, 2, 8},
  {type__function_of, NULL, 34, 34, 2, 12},
  {run__basic__grammar, NULL, 426, 426, 1, 43},
  {cont__152_1, NULL, },
  {entry__12_1_types__optional_grammar__match, NULL, 42, 42, 21, 33},
  {cont__12_2, &frame__12_1_types__optional_grammar__match, 42, 42, 6, 41},
  {cont__12_3, &frame__12_1_types__optional_grammar__match, 42, 42, 6, 59},
  {cont__12_4, &frame__12_1_types__optional_grammar__match, 42, 42, 3, 59},
  {entry__13_1_std__optional, NULL, 44, 44, 24, 56},
  {entry__15_6, NULL, 60, 60, 26, 35},
  {entry__15_9, NULL, 63, 63, 9, 19},
  {cont__15_10, &frame__15_9, 63, 63, 19, 19},
  {entry__15_11, NULL, 65, 65, 14, 14},
  {entry__15_14, NULL, 66, 66, 16, 25},
  {entry__15_2, NULL, 59, 59, 23, 35},
  {cont__15_3, &frame__15_2, 59, 59, 5, 43},
  {cont__15_4, &frame__15_2, 60, 60, 12, 23},
  {cont__15_5, &frame__15_2, 60, 60, 5, 35},
  {cont__15_7, &frame__15_2, 62, 62, 7, 20},
  {cont__15_8, &frame__15_2, 61, 65, 5, 15},
  {cont__15_12, &frame__15_2, 66, 66, 8, 13},
  {cont__15_13, &frame__15_2, 66, 66, 5, 25},
  {cont__15_15, &frame__15_2, 67, 67, 19, 21},
  {cont__15_16, &frame__15_2, 67, 67, 24, 24},
  {cont__15_17, &frame__15_2, 67, 67, 5, 24},
  {cont__15_18, &frame__15_2, 67, 67, 24, 24},
  {entry__15_1_types__many_grammar__match, NULL, 58, 67, 3, 24},
  {cont__15_19, &frame__15_1_types__many_grammar__match, 67, 67, 24, 24},
  {entry__16_1_std__many, NULL, 69, 69, 20, 48},
  {entry__18_6, NULL, 85, 85, 26, 35},
  {entry__18_9, NULL, 88, 88, 9, 19},
  {cont__18_10, &frame__18_9, 88, 88, 19, 19},
  {entry__18_11, NULL, 90, 90, 14, 14},
  {entry__18_14, NULL, 91, 91, 16, 25},
  {entry__18_2, NULL, 84, 84, 23, 35},
  {cont__18_3, &frame__18_2, 84, 84, 5, 43},
  {cont__18_4, &frame__18_2, 85, 85, 12, 23},
  {cont__18_5, &frame__18_2, 85, 85, 5, 35},
  {cont__18_7, &frame__18_2, 87, 87, 7, 20},
  {cont__18_8, &frame__18_2, 86, 90, 5, 15},
  {cont__18_12, &frame__18_2, 91, 91, 8, 13},
  {cont__18_13, &frame__18_2, 91, 91, 5, 25},
  {cont__18_15, &frame__18_2, 92, 92, 19, 21},
  {cont__18_16, &frame__18_2, 92, 92, 24, 24},
  {cont__18_17, &frame__18_2, 92, 92, 5, 24},
  {cont__18_18, &frame__18_2, 92, 92, 24, 24},
  {entry__18_1_types__some_grammar__match, NULL, 83, 92, 3, 24},
  {cont__18_19, &frame__18_1_types__some_grammar__match, 92, 92, 24, 24},
  {entry__19_1_std__some, NULL, 94, 94, 20, 48},
  {entry__21_6, NULL, 110, 110, 22, 29},
  {entry__21_3, NULL, 109, 109, 5, 41},
  {cont__21_4, &frame__21_3, 110, 110, 8, 19},
  {cont__21_5, &frame__21_3, 110, 110, 5, 29},
  {entry__21_1_types__alt_grammar__match, NULL, 107, 107, 3, 37},
  {cont__21_2, &frame__21_1_types__alt_grammar__match, 108, 110, 3, 29},
  {cont__21_7, &frame__21_1_types__alt_grammar__match, 111, 111, 3, 14},
  {entry__22_1_std__alt, NULL, 113, 113, 28, 71},
  {entry__24_5, NULL, 130, 130, 7, 14},
  {entry__24_6, NULL, 132, 132, 7, 22},
  {entry__24_1_types__followed_by_grammar__match, NULL, 128, 128, 20, 32},
  {cont__24_2, &frame__24_1_types__followed_by_grammar__match, 128, 128, 5, 40},
  {cont__24_3, &frame__24_1_types__followed_by_grammar__match, 128, 128, 5, 51},
  {cont__24_4, &frame__24_1_types__followed_by_grammar__match, 127, 132, 3, 23},
  {cont__24_7, &frame__24_1_types__followed_by_grammar__match, 132, 132, 23, 23},
  {entry__25_1_std__followed_by, NULL, 134, 134, 27, 62},
  {entry__27_5, NULL, 151, 151, 7, 22},
  {entry__27_6, NULL, 153, 153, 7, 14},
  {entry__27_1_types__not_followed_by_grammar__match, NULL, 149, 149, 20, 32},
  {cont__27_2, &frame__27_1_types__not_followed_by_grammar__match, 149, 149, 5, 40},
  {cont__27_3, &frame__27_1_types__not_followed_by_grammar__match, 149, 149, 5, 51},
  {cont__27_4, &frame__27_1_types__not_followed_by_grammar__match, 148, 153, 3, 15},
  {cont__27_7, &frame__27_1_types__not_followed_by_grammar__match, 153, 153, 15, 15},
  {entry__28_1_std__not_followed_by, NULL, 155, 155, 31, 70},
  {entry__30_9, NULL, 169, 169, 9, 43},
  {cont__30_10, &frame__30_9, 169, 169, 43, 43},
  {entry__30_11, NULL, 171, 171, 36, 36},
  {entry__30_5, NULL, 165, 165, 5, 27},
  {cont__30_6, &frame__30_5, 166, 166, 5, 30},
  {cont__30_7, &frame__30_5, 168, 168, 7, 23},
  {cont__30_8, &frame__30_5, 167, 171, 5, 37},
  {entry__30_1_types__capture_grammar__match, NULL, 163, 163, 23, 35},
  {cont__30_2, &frame__30_1_types__capture_grammar__match, 163, 163, 3, 43},
  {cont__30_3, &frame__30_1_types__capture_grammar__match, 164, 164, 6, 19},
  {cont__30_4, &frame__30_1_types__capture_grammar__match, 164, 171, 3, 38},
  {cont__30_12, &frame__30_1_types__capture_grammar__match, 172, 172, 3, 8},
  {entry__31_1_std__capture, NULL, 174, 174, 31, 80},
  {entry__33_9, NULL, 190, 190, 16, 30},
  {cont__33_10, &frame__33_9, 190, 190, 16, 53},
  {cont__33_11, &frame__33_9, 190, 190, 11, 60},
  {cont__33_12, &frame__33_9, 188, 190, 9, 60},
  {cont__33_13, &frame__33_9, 190, 190, 61, 61},
  {entry__33_14, NULL, 192, 192, 9, 41},
  {cont__33_15, &frame__33_14, 192, 192, 41, 41},
  {entry__33_5, NULL, 184, 184, 5, 27},
  {cont__33_6, &frame__33_5, 185, 185, 5, 30},
  {cont__33_7, &frame__33_5, 187, 187, 7, 23},
  {cont__33_8, &frame__33_5, 186, 192, 5, 42},
  {entry__33_1_types__multi_capture_grammar__match, NULL, 182, 182, 23, 35},
  {cont__33_2, &frame__33_1_types__multi_capture_grammar__match, 182, 182, 3, 43},
  {cont__33_3, &frame__33_1_types__multi_capture_grammar__match, 183, 183, 6, 19},
  {cont__33_4, &frame__33_1_types__multi_capture_grammar__match, 183, 192, 3, 43},
  {cont__33_16, &frame__33_1_types__multi_capture_grammar__match, 193, 193, 3, 8},
  {entry__34_1_std__multi_capture, NULL, 196, 196, 3, 58},
  {entry__36_6, NULL, 214, 214, 28, 43},
  {entry__36_2, NULL, 213, 213, 25, 37},
  {cont__36_3, &frame__36_2, 213, 213, 5, 45},
  {cont__36_4, &frame__36_2, 214, 214, 12, 25},
  {cont__36_5, &frame__36_2, 214, 214, 5, 43},
  {cont__36_7, &frame__36_2, 215, 215, 5, 19},
  {cont__36_8, &frame__36_2, 215, 215, 5, 53},
  {cont__36_9, &frame__36_2, },
  {entry__36_1_types__span_grammar__match, NULL, 211, 215, 3, 53},
  {cont__36_10, &frame__36_1_types__span_grammar__match, 217, 217, 3, 8},
  {entry__37_1_std__span, NULL, 219, 219, 27, 73},
  {entry__39_6, NULL, 237, 237, 28, 43},
  {entry__39_10, NULL, 241, 241, 33, 50},
  {cont__39_11, &frame__39_10, 241, 241, 28, 73},
  {cont__39_12, &frame__39_10, 241, 241, 9, 73},
  {cont__39_13, &frame__39_10, 241, 241, 73, 73},
  {entry__39_14, NULL, 243, 243, 9, 46},
  {cont__39_15, &frame__39_14, 243, 243, 46, 46},
  {entry__39_2, NULL, 236, 236, 25, 37},
  {cont__39_3, &frame__39_2, 236, 236, 5, 45},
  {cont__39_4, &frame__39_2, 237, 237, 12, 25},
  {cont__39_5, &frame__39_2, 237, 237, 5, 43},
  {cont__39_7, &frame__39_2, 238, 238, 5, 27},
  {cont__39_8, &frame__39_2, 240, 240, 7, 23},
  {cont__39_9, &frame__39_2, 239, 243, 5, 47},
  {cont__39_16, &frame__39_2, 243, 243, 47, 47},
  {entry__39_1_types__multi_span_grammar__match, NULL, 234, 243, 3, 48},
  {cont__39_17, &frame__39_1_types__multi_span_grammar__match, 245, 245, 3, 8},
  {entry__40_1_std__multi_span, NULL, 248, 248, 3, 55},
  {entry__42_1_types__set_node_grammar__match, NULL, 256, 256, 3, 38},
  {cont__42_2, &frame__42_1_types__set_node_grammar__match, 257, 257, 3, 6},
  {entry__43_1_std__set_node, NULL, 259, 259, 24, 56},
  {entry__45_5, NULL, 270, 270, 7, 39},
  {entry__45_6, NULL, 272, 272, 7, 32},
  {entry__45_1_types__inspect_node_grammar__match, NULL, 267, 267, 3, 25},
  {cont__45_2, &frame__45_1_types__inspect_node_grammar__match, 269, 269, 5, 28},
  {cont__45_3, &frame__45_1_types__inspect_node_grammar__match, 269, 269, 5, 33},
  {cont__45_4, &frame__45_1_types__inspect_node_grammar__match, 268, 272, 3, 33},
  {cont__45_7, &frame__45_1_types__inspect_node_grammar__match, 273, 273, 3, 6},
  {entry__46_1_std__inspect_node, NULL, 275, 275, 28, 68},
  {entry__48_5, NULL, 286, 286, 7, 40},
  {cont__48_6, &frame__48_5, 286, 286, 40, 40},
  {entry__48_7, NULL, 288, 288, 7, 33},
  {cont__48_8, &frame__48_7, 288, 288, 33, 33},
  {entry__48_1_types__modify_node_grammar__match, NULL, 283, 283, 3, 25},
  {cont__48_2, &frame__48_1_types__modify_node_grammar__match, 285, 285, 5, 28},
  {cont__48_3, &frame__48_1_types__modify_node_grammar__match, 285, 285, 5, 33},
  {cont__48_4, &frame__48_1_types__modify_node_grammar__match, 284, 288, 3, 34},
  {cont__48_9, &frame__48_1_types__modify_node_grammar__match, 289, 289, 3, 6},
  {entry__49_1_std__modify_node, NULL, 291, 291, 27, 66},
  {entry__51_7, NULL, 307, 307, 50, 65},
  {entry__51_5, NULL, 307, 307, 14, 47},
  {cont__51_6, &frame__51_5, 307, 307, 7, 65},
  {entry__51_10, NULL, 309, 309, 43, 58},
  {entry__51_8, NULL, 309, 309, 14, 40},
  {cont__51_9, &frame__51_8, 309, 309, 7, 58},
  {entry__51_1_types__check_node_grammar__match, NULL, 304, 304, 3, 25},
  {cont__51_2, &frame__51_1_types__check_node_grammar__match, 306, 306, 5, 28},
  {cont__51_3, &frame__51_1_types__check_node_grammar__match, 306, 306, 5, 33},
  {cont__51_4, &frame__51_1_types__check_node_grammar__match, 305, 309, 3, 59},
  {cont__51_11, &frame__51_1_types__check_node_grammar__match, 310, 310, 3, 6},
  {entry__52_1_std__check_node, NULL, 312, 312, 26, 64},
  {entry__54_1_types__grammar_action_grammar__match, NULL, 320, 320, 6, 22},
  {cont__54_2, &frame__54_1_types__grammar_action_grammar__match, 320, 320, 6, 30},
  {cont__54_3, &frame__54_1_types__grammar_action_grammar__match, 320, 320, 3, 30},
  {entry__55_1_std__grammar_action, NULL, 322, 322, 30, 72},
  {entry__57_1_types__set_field_grammar__match, NULL, 330, 330, 42, 54},
  {cont__57_2, &frame__57_1_types__set_field_grammar__match, 330, 330, 3, 17},
  {cont__57_3, &frame__57_1_types__set_field_grammar__match, 330, 330, 3, 54},
  {cont__57_4, &frame__57_1_types__set_field_grammar__match, 331, 331, 3, 6},
  {entry__58_1_std__set_field, NULL, 334, 334, 3, 54},
  {entry__60_3, NULL, 342, 342, 37, 48},
  {entry__60_4, NULL, 342, 342, 51, 54},
  {entry__60_1_std__END_OF_TEXT_grammar__match, NULL, 342, 342, 6, 34},
  {cont__60_2, &frame__60_1_std__END_OF_TEXT_grammar__match, 342, 342, 3, 54},
  {entry__62_3, NULL, 355, 355, 41, 56},
  {entry__62_8, NULL, 357, 357, 25, 33},
  {cont__62_9, &frame__62_8, 357, 357, 25, 40},
  {cont__62_10, &frame__62_8, 357, 357, 25, 40},
  {cont__62_11, &frame__62_8, 357, 357, 25, 40},
  {entry__62_17, NULL, 357, 357, 65, 73},
  {cont__62_18, &frame__62_17, 357, 357, 65, 80},
  {cont__62_19, &frame__62_17, 357, 357, 65, 80},
  {cont__62_20, &frame__62_17, 357, 357, 65, 80},
  {entry__62_13, NULL, 357, 357, 45, 53},
  {cont__62_14, &frame__62_13, 357, 357, 45, 60},
  {cont__62_15, &frame__62_13, 357, 357, 45, 60},
  {cont__62_16, &frame__62_13, 357, 357, 45, 80},
  {cont__62_21, &frame__62_13, 357, 357, 45, 80},
  {entry__62_23, NULL, 359, 359, 7, 14},
  {entry__62_1_std__LETTER_grammar__match, NULL, 355, 355, 10, 38},
  {cont__62_2, &frame__62_1_std__LETTER_grammar__match, 355, 355, 3, 56},
  {cont__62_4, &frame__62_1_std__LETTER_grammar__match, 357, 357, 5, 13},
  {cont__62_5, &frame__62_1_std__LETTER_grammar__match, 357, 357, 5, 20},
  {cont__62_6, &frame__62_1_std__LETTER_grammar__match, 357, 357, 5, 20},
  {cont__62_7, &frame__62_1_std__LETTER_grammar__match, 357, 357, 5, 40},
  {cont__62_12, &frame__62_1_std__LETTER_grammar__match, 357, 357, 5, 80},
  {cont__62_22, &frame__62_1_std__LETTER_grammar__match, 356, 359, 3, 15},
  {cont__62_24, &frame__62_1_std__LETTER_grammar__match, 360, 360, 3, 14},
  {entry__64_3, NULL, 373, 373, 41, 56},
  {entry__64_8, NULL, 374, 374, 26, 34},
  {cont__64_9, &frame__64_8, 374, 374, 26, 41},
  {cont__64_10, &frame__64_8, 374, 374, 26, 41},
  {cont__64_11, &frame__64_8, 374, 374, 26, 41},
  {entry__64_13, NULL, 374, 374, 44, 51},
  {entry__64_1_std__UPPER_CASE_LETTER_grammar__match, NULL, 373, 373, 10, 38},
  {cont__64_2, &frame__64_1_std__UPPER_CASE_LETTER_grammar__match, 373, 373, 3, 56},
  {cont__64_4, &frame__64_1_std__UPPER_CASE_LETTER_grammar__match, 374, 374, 6, 14},
  {cont__64_5, &frame__64_1_std__UPPER_CASE_LETTER_grammar__match, 374, 374, 6, 21},
  {cont__64_6, &frame__64_1_std__UPPER_CASE_LETTER_grammar__match, 374, 374, 6, 21},
  {cont__64_7, &frame__64_1_std__UPPER_CASE_LETTER_grammar__match, 374, 374, 6, 41},
  {cont__64_12, &frame__64_1_std__UPPER_CASE_LETTER_grammar__match, 374, 374, 3, 51},
  {cont__64_14, &frame__64_1_std__UPPER_CASE_LETTER_grammar__match, 375, 375, 3, 14},
  {entry__66_3, NULL, 388, 388, 41, 56},
  {entry__66_8, NULL, 389, 389, 26, 34},
  {cont__66_9, &frame__66_8, 389, 389, 26, 41},
  {cont__66_10, &frame__66_8, 389, 389, 26, 41},
  {cont__66_11, &frame__66_8, 389, 389, 26, 41},
  {entry__66_13, NULL, 389, 389, 44, 51},
  {entry__66_1_std__LOWER_CASE_LETTER_grammar__match, NULL, 388, 388, 10, 38},
  {cont__66_2, &frame__66_1_std__LOWER_CASE_LETTER_grammar__match, 388, 388, 3, 56},
  {cont__66_4, &frame__66_1_std__LOWER_CASE_LETTER_grammar__match, 389, 389, 6, 14},
  {cont__66_5, &frame__66_1_std__LOWER_CASE_LETTER_grammar__match, 389, 389, 6, 21},
  {cont__66_6, &frame__66_1_std__LOWER_CASE_LETTER_grammar__match, 389, 389, 6, 21},
  {cont__66_7, &frame__66_1_std__LOWER_CASE_LETTER_grammar__match, 389, 389, 6, 41},
  {cont__66_12, &frame__66_1_std__LOWER_CASE_LETTER_grammar__match, 389, 389, 3, 51},
  {cont__66_14, &frame__66_1_std__LOWER_CASE_LETTER_grammar__match, 390, 390, 3, 14},
  {entry__68_3, NULL, 403, 403, 41, 56},
  {entry__68_8, NULL, 404, 404, 26, 34},
  {cont__68_9, &frame__68_8, 404, 404, 26, 41},
  {cont__68_10, &frame__68_8, 404, 404, 26, 41},
  {cont__68_11, &frame__68_8, 404, 404, 26, 41},
  {entry__68_13, NULL, 404, 404, 44, 51},
  {entry__68_1_std__DIGIT_grammar__match, NULL, 403, 403, 10, 38},
  {cont__68_2, &frame__68_1_std__DIGIT_grammar__match, 403, 403, 3, 56},
  {cont__68_4, &frame__68_1_std__DIGIT_grammar__match, 404, 404, 6, 14},
  {cont__68_5, &frame__68_1_std__DIGIT_grammar__match, 404, 404, 6, 21},
  {cont__68_6, &frame__68_1_std__DIGIT_grammar__match, 404, 404, 6, 21},
  {cont__68_7, &frame__68_1_std__DIGIT_grammar__match, 404, 404, 6, 41},
  {cont__68_12, &frame__68_1_std__DIGIT_grammar__match, 404, 404, 3, 51},
  {cont__68_14, &frame__68_1_std__DIGIT_grammar__match, 405, 405, 3, 14},
  {entry__70_3, NULL, 418, 418, 41, 56},
  {entry__70_8, NULL, 420, 420, 20, 33},
  {cont__70_9, &frame__70_8, 420, 420, 20, 33},
  {entry__70_11, NULL, 420, 420, 36, 43},
  {entry__70_1_std__WHITESPACE_CHARACTER_grammar__match, NULL, 418, 418, 10, 38},
  {cont__70_2, &frame__70_1_std__WHITESPACE_CHARACTER_grammar__match, 418, 418, 3, 56},
  {cont__70_4, &frame__70_1_std__WHITESPACE_CHARACTER_grammar__match, 419, 419, 3, 16},
  {cont__70_5, &frame__70_1_std__WHITESPACE_CHARACTER_grammar__match, 420, 420, 6, 15},
  {cont__70_6, &frame__70_1_std__WHITESPACE_CHARACTER_grammar__match, 420, 420, 6, 15},
  {cont__70_7, &frame__70_1_std__WHITESPACE_CHARACTER_grammar__match, 420, 420, 6, 33},
  {cont__70_10, &frame__70_1_std__WHITESPACE_CHARACTER_grammar__match, 420, 420, 3, 43},
  {cont__70_12, &frame__70_1_std__WHITESPACE_CHARACTER_grammar__match, 421, 421, 3, 14},
  {entry__73_3, NULL, 439, 439, 41, 56},
  {entry__73_8, NULL, 441, 441, 20, 32},
  {cont__73_9, &frame__73_8, 441, 441, 20, 32},
  {entry__73_11, NULL, 441, 441, 37, 51},
  {cont__73_12, &frame__73_11, 441, 441, 37, 51},
  {cont__73_13, &frame__73_11, 441, 441, 37, 51},
  {entry__73_15, NULL, 441, 441, 54, 61},
  {entry__73_1_std__PRINTABLE_CHARACTER_grammar__match, NULL, 439, 439, 10, 38},
  {cont__73_2, &frame__73_1_std__PRINTABLE_CHARACTER_grammar__match, 439, 439, 3, 56},
  {cont__73_4, &frame__73_1_std__PRINTABLE_CHARACTER_grammar__match, 440, 440, 3, 16},
  {cont__73_5, &frame__73_1_std__PRINTABLE_CHARACTER_grammar__match, 441, 441, 6, 15},
  {cont__73_6, &frame__73_1_std__PRINTABLE_CHARACTER_grammar__match, 441, 441, 6, 15},
  {cont__73_7, &frame__73_1_std__PRINTABLE_CHARACTER_grammar__match, 441, 441, 6, 32},
  {cont__73_10, &frame__73_1_std__PRINTABLE_CHARACTER_grammar__match, 441, 441, 6, 51},
  {cont__73_14, &frame__73_1_std__PRINTABLE_CHARACTER_grammar__match, 441, 441, 3, 61},
  {cont__73_16, &frame__73_1_std__PRINTABLE_CHARACTER_grammar__match, 442, 442, 3, 14},
  {entry__75_3, NULL, 455, 455, 41, 56},
  {entry__75_7, NULL, 457, 457, 19, 31},
  {cont__75_8, &frame__75_7, 457, 457, 19, 31},
  {entry__75_10, NULL, 457, 457, 36, 50},
  {cont__75_11, &frame__75_10, 457, 457, 36, 50},
  {cont__75_12, &frame__75_10, 457, 457, 36, 50},
  {entry__75_14, NULL, 457, 457, 53, 60},
  {entry__75_1_std__NON_SPACE_CHARACTER_grammar__match, NULL, 455, 455, 10, 38},
  {cont__75_2, &frame__75_1_std__NON_SPACE_CHARACTER_grammar__match, 455, 455, 3, 56},
  {cont__75_4, &frame__75_1_std__NON_SPACE_CHARACTER_grammar__match, 456, 456, 3, 16},
  {cont__75_5, &frame__75_1_std__NON_SPACE_CHARACTER_grammar__match, 457, 457, 6, 14},
  {cont__75_6, &frame__75_1_std__NON_SPACE_CHARACTER_grammar__match, 457, 457, 6, 31},
  {cont__75_9, &frame__75_1_std__NON_SPACE_CHARACTER_grammar__match, 457, 457, 6, 50},
  {cont__75_13, &frame__75_1_std__NON_SPACE_CHARACTER_grammar__match, 457, 457, 3, 60},
  {cont__75_15, &frame__75_1_std__NON_SPACE_CHARACTER_grammar__match, 458, 458, 3, 14},
  {entry__77_3, NULL, 471, 471, 41, 56},
  {entry__77_1_std__ANY_CHARACTER_grammar__match, NULL, 471, 471, 10, 38},
  {cont__77_2, &frame__77_1_std__ANY_CHARACTER_grammar__match, 471, 471, 3, 56},
  {cont__77_4, &frame__77_1_std__ANY_CHARACTER_grammar__match, 472, 472, 3, 6},
  {entry__78_1_types__character_grammar__match, NULL, 477, 477, 48, 73},
  {entry__79_3, NULL, 485, 485, 41, 56},
  {entry__79_9, NULL, 487, 487, 44, 63},
  {cont__79_10, &frame__79_9, 487, 487, 37, 63},
  {cont__79_11, &frame__79_9, 487, 487, 37, 63},
  {cont__79_12, &frame__79_9, 487, 487, 37, 63},
  {entry__79_14, NULL, 487, 487, 66, 73},
  {entry__79_1_types__value_range_grammar__match, NULL, 485, 485, 10, 38},
  {cont__79_2, &frame__79_1_types__value_range_grammar__match, 485, 485, 3, 56},
  {cont__79_4, &frame__79_1_types__value_range_grammar__match, 486, 486, 3, 16},
  {cont__79_5, &frame__79_1_types__value_range_grammar__match, 487, 487, 13, 32},
  {cont__79_6, &frame__79_1_types__value_range_grammar__match, 487, 487, 6, 32},
  {cont__79_7, &frame__79_1_types__value_range_grammar__match, 487, 487, 6, 32},
  {cont__79_8, &frame__79_1_types__value_range_grammar__match, 487, 487, 6, 63},
  {cont__79_13, &frame__79_1_types__value_range_grammar__match, 487, 487, 3, 73},
  {cont__79_15, &frame__79_1_types__value_range_grammar__match, 488, 488, 3, 14},
  {entry__80_5, NULL, 502, 502, 7, 22},
  {entry__80_2, NULL, 499, 499, 5, 34},
  {cont__80_3, &frame__80_2, 500, 500, 12, 23},
  {cont__80_4, &frame__80_2, 500, 502, 5, 22},
  {cont__80_6, &frame__80_2, 503, 503, 19, 21},
  {cont__80_7, &frame__80_2, 503, 503, 24, 24},
  {cont__80_8, &frame__80_2, 503, 503, 5, 24},
  {cont__80_9, &frame__80_2, 504, 504, 5, 15},
  {cont__80_10, &frame__80_2, 504, 504, 15, 15},
  {entry__80_1_types__list_grammar__match, NULL, 498, 504, 3, 15},
  {cont__80_11, &frame__80_1_types__list_grammar__match, 505, 505, 3, 8},
  {entry__81_9, NULL, 521, 521, 24, 37},
  {entry__81_12, NULL, 523, 523, 23, 27},
  {cont__81_13, &frame__81_12, 523, 523, 13, 27},
  {cont__81_14, &frame__81_12, 524, 524, 27, 27},
  {cont__81_15, &frame__81_12, 524, 524, 13, 27},
  {cont__81_16, &frame__81_12, 524, 524, 27, 27},
  {entry__81_7, NULL, 521, 521, 14, 21},
  {cont__81_8, &frame__81_7, 521, 521, 11, 37},
  {cont__81_10, &frame__81_7, 522, 522, 14, 20},
  {cont__81_11, &frame__81_7, 522, 524, 11, 27},
  {cont__81_17, &frame__81_7, 525, 525, 11, 22},
  {cont__81_18, &frame__81_7, 525, 525, 22, 22},
  {entry__81_21, NULL, 526, 526, 42, 67},
  {entry__81_4, NULL, 519, 519, 9, 35},
  {cont__81_5, &frame__81_4, 520, 520, 12, 25},
  {cont__81_6, &frame__81_4, 520, 525, 9, 22},
  {cont__81_19, &frame__81_4, 526, 526, 16, 39},
  {cont__81_20, &frame__81_4, 526, 526, 9, 67},
  {cont__81_22, &frame__81_4, 527, 527, 9, 19},
  {cont__81_23, &frame__81_4, 528, 528, 21, 21},
  {cont__81_24, &frame__81_4, 528, 528, 9, 21},
  {cont__81_25, &frame__81_4, 528, 528, 21, 21},
  {entry__81_3, NULL, 518, 528, 7, 21},
  {entry__81_35, NULL, 537, 537, 33, 33},
  {cont__81_36, &frame__81_35, 537, 537, 13, 33},
  {cont__81_37, &frame__81_35, 538, 538, 31, 31},
  {cont__81_38, &frame__81_35, 538, 538, 13, 31},
  {cont__81_39, &frame__81_35, 538, 538, 31, 31},
  {entry__81_44, NULL, 542, 542, 23, 27},
  {cont__81_45, &frame__81_44, 542, 542, 13, 27},
  {cont__81_46, &frame__81_44, 543, 543, 27, 27},
  {cont__81_47, &frame__81_44, 543, 543, 13, 27},
  {cont__81_48, &frame__81_44, 543, 543, 27, 27},
  {entry__81_31, NULL, 536, 536, 14, 33},
  {cont__81_32, &frame__81_31, 536, 536, 14, 40},
  {cont__81_33, &frame__81_31, 536, 536, 14, 40},
  {cont__81_34, &frame__81_31, 536, 538, 11, 31},
  {cont__81_40, &frame__81_31, 539, 539, 11, 29},
  {cont__81_41, &frame__81_31, 540, 540, 11, 27},
  {cont__81_42, &frame__81_31, 541, 541, 14, 20},
  {cont__81_43, &frame__81_31, 541, 543, 11, 27},
  {entry__81_54, NULL, 545, 545, 42, 67},
  {entry__81_51, NULL, 545, 545, 14, 33},
  {cont__81_52, &frame__81_51, 545, 545, 14, 39},
  {cont__81_53, &frame__81_51, 545, 545, 11, 67},
  {cont__81_55, &frame__81_51, 546, 546, 18, 29},
  {cont__81_56, &frame__81_51, 546, 546, 31, 40},
  {cont__81_57, &frame__81_51, 546, 546, 11, 40},
  {entry__81_28, NULL, 534, 534, 9, 35},
  {cont__81_29, &frame__81_28, 535, 535, 12, 25},
  {cont__81_30, &frame__81_28, 535, 543, 9, 28},
  {cont__81_49, &frame__81_28, 544, 544, 16, 39},
  {cont__81_50, &frame__81_28, 544, 546, 9, 40},
  {cont__81_58, &frame__81_28, 547, 547, 9, 19},
  {cont__81_59, &frame__81_28, 548, 548, 21, 21},
  {cont__81_60, &frame__81_28, 548, 548, 9, 21},
  {cont__81_61, &frame__81_28, 548, 548, 21, 21},
  {entry__81_26, NULL, 530, 530, 7, 17},
  {cont__81_27, &frame__81_26, 533, 548, 7, 21},
  {entry__81_1_types__object_grammar__search, NULL, 517, 517, 5, 11},
  {cont__81_2, &frame__81_1_types__object_grammar__search, 516, 548, 3, 23},
  {cont__81_62, &frame__81_1_types__object_grammar__search, 548, 548, 23, 23}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__grammar__match(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__grammar__match);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__grammar__match, attr);
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
static void type__grammar__search(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__grammar__search);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__grammar__search, attr);
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
static void type__expr_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__expr_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__expr_of, attr);
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
static void type__alternatives_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__alternatives_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__alternatives_of, attr);
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
static void type__setter_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__setter_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__setter_of, attr);
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
static void type__node_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__node_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node_of, attr);
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
static void type__function_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__function_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__function_of, attr);
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
static NODE *character__90;
static NODE *character__122;
static NODE *character__57;
static NODE *character__160;
static NODE *character__65;
static NODE *number__0;
static NODE *character__48;
static NODE *character__32;
static NODE *character__127;
static NODE *character__97;
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__grammar",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/grammar.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__grammar(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 26: $types::grammar_object types::object # an object used for matching strings
  initialize_maybe_future(var.types__grammar_object, get__types__object());
  // 27: $types::grammar_node types::object
  initialize_maybe_future(var.types__grammar_node, get__types__object());
  // 28: %%grammar::current_node undefined
  set__grammar__current_node(get__undefined());
  // 426: $std::WHITESPACE many(WHITESPACE_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__WHITESPACE_CHARACTER();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__152_1;
}
static void cont__152_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.std__WHITESPACE, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_1_types__optional_grammar__match(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 42: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__12_2;
}
static void cont__12_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 42: ... grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 42: ... grammar::match(expr_of(self) stream) .default_value. 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__12_4;
}
static void cont__12_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 42: -> grammar::match(expr_of(self) stream) .default_value. 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_1_std__optional(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 44: ... types::optional(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__optional);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 44: ... -> types::optional(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_1_types__many_grammar__match(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // len: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* len */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* stream */ = create_cell_with_contents(arguments->slots[1]);
  // 57: $$len undefined
  ((CELL *)frame->slots[3])->contents /* len */ = get__undefined();
  // 58: ... :
  // 59:   $n grammar::match(expr_of(self) stream)
  // 60:   unless n.is_defined: return len
  // 61:   if
  // 62:     len.is_defined:
  // 63:       plus &len n
  // 64:     :
  // 65:       !len n
  // 66:   if n == 0: return len
  // 67:   range &stream n+1 -1
  frame->slots[4] /* temp__1 */ = create_closure(entry__15_2, 0);
  // 58: forever:
  // 59:   $n grammar::match(expr_of(self) stream)
  // 60:   unless n.is_defined: return len
  // 61:   if
  // 62:     len.is_defined:
  // 63:       plus &len n
  // 64:     :
  // 65:       !len n
  // 66:   if n == 0: return len
  // 67:   range &stream n+1 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__15_19;
}
static void entry__15_2(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // len: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[3]; /* len */
  frame->slots[4] /* n */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 59: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__15_3;
}
static void cont__15_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 59: $n grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__15_4;
}
static void cont__15_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* n */, arguments->slots[0]);
  // 60: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__15_5;
}
static void cont__15_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 60: ... : return len
  frame->slots[6] /* temp__2 */ = create_closure(entry__15_6, 0);
  // 60: unless n.is_defined: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__15_7;
}
static void entry__15_6(void) {
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
  // 60: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__15_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 62: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__15_8;
}
static void cont__15_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 62: ... :
  // 63:   plus &len n
  frame->slots[6] /* temp__2 */ = create_closure(entry__15_9, 0);
  // 64: :
  // 65:   !len n
  frame->slots[7] /* temp__3 */ = create_closure(entry__15_11, 0);
  // 61: if
  // 62:   len.is_defined:
  // 63:     plus &len n
  // 64:   :
  // 65:     !len n
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__15_12;
}
static void entry__15_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // len: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* len */
  frame->slots[1] = myself->closure.frame->slots[4]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: plus &len n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__15_10;
}
static void cont__15_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* len */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_11(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // len: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* len */
  frame->slots[1] = myself->closure.frame->slots[4]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 65: !len n
  ((CELL *)frame->slots[0])->contents /* len */ = frame->slots[1] /* n */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__15_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 66: ... n == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__15_13;
}
static void cont__15_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 66: ... : return len
  frame->slots[6] /* temp__2 */ = create_closure(entry__15_14, 0);
  // 66: if n == 0: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__15_15;
}
static void entry__15_14(void) {
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
  // 66: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__15_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 67: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__15_16;
}
static void cont__15_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 67: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__15_17;
}
static void cont__15_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 67: range &stream n+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* stream */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__15_18;
}
static void cont__15_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* stream */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__15_19(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__16_1_std__many(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 69: ... types::many(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__many);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 69: ... -> types::many(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1_types__some_grammar__match(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // len: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* len */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* stream */ = create_cell_with_contents(arguments->slots[1]);
  // 82: $$len 0
  ((CELL *)frame->slots[3])->contents /* len */ = number__0;
  // 83: ... :
  // 84:   $n grammar::match(expr_of(self) stream)
  // 85:   unless n.is_defined: return len
  // 86:   if
  // 87:     len.is_defined:
  // 88:       plus &len n
  // 89:     :
  // 90:       !len n
  // 91:   if n == 0: return len
  // 92:   range &stream n+1 -1
  frame->slots[4] /* temp__1 */ = create_closure(entry__18_2, 0);
  // 83: forever:
  // 84:   $n grammar::match(expr_of(self) stream)
  // 85:   unless n.is_defined: return len
  // 86:   if
  // 87:     len.is_defined:
  // 88:       plus &len n
  // 89:     :
  // 90:       !len n
  // 91:   if n == 0: return len
  // 92:   range &stream n+1 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__18_19;
}
static void entry__18_2(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // len: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[3]; /* len */
  frame->slots[4] /* n */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 84: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__18_3;
}
static void cont__18_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 84: $n grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__18_4;
}
static void cont__18_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* n */, arguments->slots[0]);
  // 85: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 85: ... : return len
  frame->slots[6] /* temp__2 */ = create_closure(entry__18_6, 0);
  // 85: unless n.is_defined: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void entry__18_6(void) {
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
  // 85: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 87: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_8;
}
static void cont__18_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 87: ... :
  // 88:   plus &len n
  frame->slots[6] /* temp__2 */ = create_closure(entry__18_9, 0);
  // 89: :
  // 90:   !len n
  frame->slots[7] /* temp__3 */ = create_closure(entry__18_11, 0);
  // 86: if
  // 87:   len.is_defined:
  // 88:     plus &len n
  // 89:   :
  // 90:     !len n
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_12;
}
static void entry__18_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // len: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* len */
  frame->slots[1] = myself->closure.frame->slots[4]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 88: plus &len n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__18_10;
}
static void cont__18_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* len */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_11(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // len: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* len */
  frame->slots[1] = myself->closure.frame->slots[4]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: !len n
  ((CELL *)frame->slots[0])->contents /* len */ = frame->slots[1] /* n */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__18_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 91: ... n == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__18_13;
}
static void cont__18_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 91: ... : return len
  frame->slots[6] /* temp__2 */ = create_closure(entry__18_14, 0);
  // 91: if n == 0: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_15;
}
static void entry__18_14(void) {
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
  // 91: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 92: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__18_16;
}
static void cont__18_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 92: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__18_17;
}
static void cont__18_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 92: range &stream n+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* stream */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__18_18;
}
static void cont__18_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* stream */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__18_19(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__19_1_std__some(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 94: ... types::some(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__some);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 94: ... -> types::some(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_1_types__alt_grammar__match(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // alternatives: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* alternatives */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 107: $alternatives alternatives_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._alternatives_of;
  func = myself->type;
  frame->cont = cont__21_2;
}
static void cont__21_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* alternatives */, arguments->slots[0]);
  // 108: ... : (alternative)
  // 109:   $n grammar::match(alternative stream)
  // 110:   if n.is_defined: return n
  frame->slots[4] /* temp__1 */ = create_closure(entry__21_3, 1);
  // 108: for_each alternatives: (alternative)
  // 109:   $n grammar::match(alternative stream)
  // 110:   if n.is_defined: return n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* alternatives */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_7;
}
static void entry__21_6(void) {
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
  // 110: ... return n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_3(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // alternative: 0
  // stream: 1
  // return: 2
  // n: 3
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* n */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 109: $n grammar::match(alternative stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alternative */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__21_4;
}
static void cont__21_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 110: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_5;
}
static void cont__21_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 110: ... : return n
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_6, 0);
  // 110: if n.is_defined: return n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 111: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__22_1_std__alt(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // alternatives: 0
  frame->slots[0] /* alternatives */ = from_arguments(0, argument_count-0);
  // 113: ... types::alt(.alternatives_of alternatives)
  {
    NODE *temp = clone_object_and_attributes(var.types__alt);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__alternatives_of, frame->slots[0] /* alternatives */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 113: ... -> types::alt(.alternatives_of alternatives)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_1_types__followed_by_grammar__match(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // original_node: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* original_node */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 126: $original_node grammar::current_node
  initialize_future(frame->slots[3] /* original_node */, get__grammar__current_node());
  // 128: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 128: grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__24_3;
}
static void cont__24_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 128: grammar::match(expr_of(self) stream).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 128: ... :
  // 129:   !grammar::current_node original_node
  // 130:   return 0
  frame->slots[7] /* temp__4 */ = create_closure(entry__24_5, 0);
  // 131: :
  // 132:   return undefined
  frame->slots[8] /* temp__5 */ = create_closure(entry__24_6, 0);
  // 127: if
  // 128:   grammar::match(expr_of(self) stream).is_defined:
  // 129:     !grammar::current_node original_node
  // 130:     return 0
  // 131:   :
  // 132:     return undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_7;
}
static void entry__24_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // original_node: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* original_node */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 129: !grammar::current_node original_node
  set__grammar__current_node(frame->slots[0] /* original_node */);
  // 130: return 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 132: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_7(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__25_1_std__followed_by(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 134: ... types::followed_by(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__followed_by);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 134: ... -> types::followed_by(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1_types__not_followed_by_grammar__match(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // original_node: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* original_node */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 147: $original_node grammar::current_node
  initialize_future(frame->slots[3] /* original_node */, get__grammar__current_node());
  // 149: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 149: grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 149: grammar::match(expr_of(self) stream).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 149: ... :
  // 150:   !grammar::current_node original_node
  // 151:   return undefined
  frame->slots[7] /* temp__4 */ = create_closure(entry__27_5, 0);
  // 152: :
  // 153:   return 0
  frame->slots[8] /* temp__5 */ = create_closure(entry__27_6, 0);
  // 148: if
  // 149:   grammar::match(expr_of(self) stream).is_defined:
  // 150:     !grammar::current_node original_node
  // 151:     return undefined
  // 152:   :
  // 153:     return 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__27_7;
}
static void entry__27_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // original_node: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* original_node */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: !grammar::current_node original_node
  set__grammar__current_node(frame->slots[0] /* original_node */);
  // 151: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__27_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 153: return 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_7(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__28_1_std__not_followed_by(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 155: ... types::not_followed_by(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__not_followed_by);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 155: ... -> types::not_followed_by(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_1_types__capture_grammar__match(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // stream: 1
  // len: 2
  frame->slots[2] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 163: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__30_2;
}
static void cont__30_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 163: $len grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__30_3;
}
static void cont__30_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* len */, arguments->slots[0]);
  // 164: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_4;
}
static void cont__30_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 164: ... :
  // 165:   $setter setter_of(self)
  // 166:   $value range(stream 1 len)
  // 167:   if
  // 168:     setter.is_defined:
  // 169:       setter &grammar::current_node value
  // 170:     :
  // 171:       !grammar::current_node value
  frame->slots[4] /* temp__2 */ = create_closure(entry__30_5, 0);
  // 164: if len.is_defined:
  // 165:   $setter setter_of(self)
  // 166:   $value range(stream 1 len)
  // 167:   if
  // 168:     setter.is_defined:
  // 169:       setter &grammar::current_node value
  // 170:     :
  // 171:       !grammar::current_node value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_12;
}
static void entry__30_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // setter: 0
  // value: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* setter */
  frame->slots[1] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 169: setter &grammar::current_node value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[1] /* value */;
  result_count = 1;
  myself = frame->slots[0] /* setter */;
  func = myself->type;
  frame->cont = cont__30_10;
}
static void cont__30_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: !grammar::current_node value
  set__grammar__current_node(frame->slots[0] /* value */);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_5(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // self: 0
  // stream: 1
  // len: 2
  // setter: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[2] = myself->closure.frame->slots[2]; /* len */
  frame->slots[3] /* setter */ = create_future();
  frame->slots[4] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 165: $setter setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__30_6;
}
static void cont__30_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* setter */, arguments->slots[0]);
  // 166: $value range(stream 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__30_7;
}
static void cont__30_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* value */, arguments->slots[0]);
  // 168: setter.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* setter */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_8;
}
static void cont__30_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 168: ... :
  // 169:   setter &grammar::current_node value
  frame->slots[6] /* temp__2 */ = create_closure(entry__30_9, 0);
  // 170: :
  // 171:   !grammar::current_node value
  frame->slots[7] /* temp__3 */ = create_closure(entry__30_11, 0);
  // 167: if
  // 168:   setter.is_defined:
  // 169:     setter &grammar::current_node value
  // 170:   :
  // 171:     !grammar::current_node value
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
static void cont__30_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__31_1_std__capture(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // setter: 0
  // expr: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  frame->slots[1] /* expr */ = arguments->slots[argument_count-1];
  switch(argument_count) {
    default: frame->slots[0] /* setter */ = arguments->slots[0];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[0] /* setter */ = undefined;
  }
  // 174: ... types::capture(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__capture);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 174: ... -> types::capture(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_1_types__multi_capture_grammar__match(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // stream: 1
  // len: 2
  frame->slots[2] /* len */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 182: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__33_2;
}
static void cont__33_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 182: $len grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__33_3;
}
static void cont__33_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* len */, arguments->slots[0]);
  // 183: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_4;
}
static void cont__33_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 183: ... :
  // 184:   $setter setter_of(self)
  // 185:   $value range(stream 1 len)
  // 186:   if
  // 187:     setter.is_defined:
  // 188:       setter
  // 189:         &grammar::current_node
  // 190:         push(setter_of(self)(grammar::current_node) value)
  // 191:     :
  // 192:       push &grammar::current_node value
  frame->slots[4] /* temp__2 */ = create_closure(entry__33_5, 0);
  // 183: if len.is_defined:
  // 184:   $setter setter_of(self)
  // 185:   $value range(stream 1 len)
  // 186:   if
  // 187:     setter.is_defined:
  // 188:       setter
  // 189:         &grammar::current_node
  // 190:         push(setter_of(self)(grammar::current_node) value)
  // 191:     :
  // 192:       push &grammar::current_node value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_16;
}
static void entry__33_9(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // setter: 0
  // self: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* setter */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 190: ... setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__33_10;
}
static void cont__33_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 190: ... setter_of(self)(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__33_11;
}
static void cont__33_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 190: push(setter_of(self)(grammar::current_node) value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* value */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_12;
}
static void cont__33_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 188: setter
  // 189:   &grammar::current_node
  // 190:   push(setter_of(self)(grammar::current_node) value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[0] /* setter */;
  func = myself->type;
  frame->cont = cont__33_13;
}
static void cont__33_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 192: push &grammar::current_node value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_15;
}
static void cont__33_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_5(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // self: 0
  // stream: 1
  // len: 2
  // setter: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[2] = myself->closure.frame->slots[2]; /* len */
  frame->slots[3] /* setter */ = create_future();
  frame->slots[4] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 184: $setter setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__33_6;
}
static void cont__33_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* setter */, arguments->slots[0]);
  // 185: $value range(stream 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__33_7;
}
static void cont__33_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* value */, arguments->slots[0]);
  // 187: setter.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* setter */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_8;
}
static void cont__33_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 187: ... :
  // 188:   setter
  // 189:     &grammar::current_node
  // 190:     push(setter_of(self)(grammar::current_node) value)
  frame->slots[6] /* temp__2 */ = create_closure(entry__33_9, 0);
  // 191: :
  // 192:   push &grammar::current_node value
  frame->slots[7] /* temp__3 */ = create_closure(entry__33_14, 0);
  // 186: if
  // 187:   setter.is_defined:
  // 188:     setter
  // 189:       &grammar::current_node
  // 190:       push(setter_of(self)(grammar::current_node) value)
  // 191:   :
  // 192:     push &grammar::current_node value
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
static void cont__33_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 193: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_1_std__multi_capture(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // setter: 0
  // expr: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  frame->slots[1] /* expr */ = arguments->slots[argument_count-1];
  switch(argument_count) {
    default: frame->slots[0] /* setter */ = arguments->slots[0];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[0] /* setter */ = undefined;
  }
  // 196: ... types::multi_capture(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__multi_capture);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 196: -> types::multi_capture(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_1_types__span_grammar__match(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // outer_node: 3
  // len: 4
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* outer_node */ = create_cell();
  frame->slots[4] /* len */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 209: $$outer_node grammar::current_node
  ((CELL *)frame->slots[3])->contents /* outer_node */ = get__grammar__current_node();
  // 210: $$len undefined
  ((CELL *)frame->slots[4])->contents /* len */ = get__undefined();
  // 211: ... :
  // 212:   %%grammar::current_node types::grammar_node
  // 213:   !len grammar::match(expr_of(self) stream)
  // 214:   unless len.is_defined: return undefined
  // 215:   setter_of(self) &outer_node grammar::current_node
  frame->slots[5] /* temp__1 */ = create_closure(entry__36_2, 0);
  // 211: do:
  // 212:   %%grammar::current_node types::grammar_node
  // 213:   !len grammar::match(expr_of(self) stream)
  // 214:   unless len.is_defined: return undefined
  // 215:   setter_of(self) &outer_node grammar::current_node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__36_10;
}
static void entry__36_2(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // return__1: 0
  // len: 1
  // self: 2
  // stream: 3
  // return: 4
  // outer_node: 5
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[4]; /* len */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  frame->slots[3] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[4] = myself->closure.frame->slots[2]; /* return */
  frame->slots[5] = myself->closure.frame->slots[3]; /* outer_node */
  define__grammar__current_node(undefined);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: %%grammar::current_node types::grammar_node
  set__grammar__current_node(var.types__grammar_node);
  // 213: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__36_3;
}
static void cont__36_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 213: !len grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* len */ = arguments->slots[0];
  // 214: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_5;
}
static void cont__36_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 214: ... : return undefined
  frame->slots[7] /* temp__2 */ = create_closure(entry__36_6, 0);
  // 214: unless len.is_defined: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__36_7;
}
static void entry__36_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 215: setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__36_8;
}
static void cont__36_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 215: setter_of(self) &outer_node grammar::current_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* outer_node */;
  arguments->slots[1] = get__grammar__current_node();
  result_count = 1;
  myself = frame->slots[6] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__36_9;
}
static void cont__36_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* outer_node */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__36_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 216: !grammar::current_node outer_node
  set__grammar__current_node(((CELL *)frame->slots[3])->contents /* outer_node */);
  // 217: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* len */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__37_1_std__span(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // setter: 0
  // expr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 219: ... types::span(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__span);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 219: ... -> types::span(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_1_types__multi_span_grammar__match(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // outer_node: 3
  // len: 4
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* outer_node */ = create_cell();
  frame->slots[4] /* len */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 232: $$outer_node grammar::current_node
  ((CELL *)frame->slots[3])->contents /* outer_node */ = get__grammar__current_node();
  // 233: $$len undefined
  ((CELL *)frame->slots[4])->contents /* len */ = get__undefined();
  // 234: ... :
  // 235:   %%grammar::current_node types::grammar_node
  // 236:   !len grammar::match(expr_of(self) stream)
  // 237:   unless len.is_defined: return undefined
  // 238:   $setter setter_of(self)
  // 239:   if
  // 240:     setter.is_defined:
  // 241:       setter &outer_node push(setter(outer_node) grammar::current_node)
  // 242:     :
  // 243:       push &outer_node grammar::current_node
  frame->slots[5] /* temp__1 */ = create_closure(entry__39_2, 0);
  // 234: do:
  // 235:   %%grammar::current_node types::grammar_node
  // 236:   !len grammar::match(expr_of(self) stream)
  // 237:   unless len.is_defined: return undefined
  // 238:   $setter setter_of(self)
  // 239:   if
  // 240:     setter.is_defined:
  // 241:       setter &outer_node push(setter(outer_node) grammar::current_node)
  // 242:     :
  // 243:       push &outer_node grammar::current_node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__39_17;
}
static void entry__39_2(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // return__1: 0
  // len: 1
  // self: 2
  // stream: 3
  // return: 4
  // outer_node: 5
  // setter: 6
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[4]; /* len */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  frame->slots[3] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[4] = myself->closure.frame->slots[2]; /* return */
  frame->slots[5] = myself->closure.frame->slots[3]; /* outer_node */
  define__grammar__current_node(undefined);
  frame->slots[6] /* setter */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 235: %%grammar::current_node types::grammar_node
  set__grammar__current_node(var.types__grammar_node);
  // 236: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__39_3;
}
static void cont__39_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 236: !len grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__39_4;
}
static void cont__39_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* len */ = arguments->slots[0];
  // 237: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_5;
}
static void cont__39_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 237: ... : return undefined
  frame->slots[8] /* temp__2 */ = create_closure(entry__39_6, 0);
  // 237: unless len.is_defined: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__39_7;
}
static void entry__39_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 237: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 238: $setter setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__39_8;
}
static void cont__39_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* setter */, arguments->slots[0]);
  // 240: setter.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* setter */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_9;
}
static void cont__39_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 240: ... :
  // 241:   setter &outer_node push(setter(outer_node) grammar::current_node)
  frame->slots[8] /* temp__2 */ = create_closure(entry__39_10, 0);
  // 242: :
  // 243:   push &outer_node grammar::current_node
  frame->slots[9] /* temp__3 */ = create_closure(entry__39_14, 0);
  // 239: if
  // 240:   setter.is_defined:
  // 241:     setter &outer_node push(setter(outer_node) grammar::current_node)
  // 242:   :
  // 243:     push &outer_node grammar::current_node
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_16;
}
static void entry__39_10(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // setter: 0
  // outer_node: 1
  frame->slots[0] = myself->closure.frame->slots[6]; /* setter */
  frame->slots[1] = myself->closure.frame->slots[5]; /* outer_node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 241: ... setter(outer_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* outer_node */;
  result_count = 1;
  myself = frame->slots[0] /* setter */;
  func = myself->type;
  frame->cont = cont__39_11;
}
static void cont__39_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 241: ... push(setter(outer_node) grammar::current_node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__grammar__current_node();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__39_12;
}
static void cont__39_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 241: setter &outer_node push(setter(outer_node) grammar::current_node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* outer_node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[0] /* setter */;
  func = myself->type;
  frame->cont = cont__39_13;
}
static void cont__39_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* outer_node */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // outer_node: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* outer_node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 243: push &outer_node grammar::current_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* outer_node */;
  arguments->slots[1] = get__grammar__current_node();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__39_15;
}
static void cont__39_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* outer_node */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_16(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__39_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 244: !grammar::current_node outer_node
  set__grammar__current_node(((CELL *)frame->slots[3])->contents /* outer_node */);
  // 245: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* len */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__40_1_std__multi_span(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // setter: 0
  // expr: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  frame->slots[1] /* expr */ = arguments->slots[argument_count-1];
  switch(argument_count) {
    default: frame->slots[0] /* setter */ = arguments->slots[0];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[0] /* setter */ = undefined;
  }
  // 248: ... types::multi_span(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__multi_span);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 248: -> types::multi_span(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__42_1_types__set_node_grammar__match(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 256: !grammar::current_node node_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._node_of;
  func = myself->type;
  frame->cont = cont__42_2;
}
static void cont__42_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  // 257: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_1_std__set_node(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 259: ... types::set_node(.node_of node)
  {
    NODE *temp = clone_object_and_attributes(var.types__set_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node_of, frame->slots[0] /* node */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 259: ... -> types::set_node(.node_of node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__45_1_types__inspect_node_grammar__match(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // stream: 1
  // func: 2
  frame->slots[2] /* func */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 267: $func function_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._function_of;
  func = myself->type;
  frame->cont = cont__45_2;
}
static void cont__45_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* func */, arguments->slots[0]);
  // 269: parameter_count_of(func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* func */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__45_3;
}
static void cont__45_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 269: parameter_count_of(func) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__45_4;
}
static void cont__45_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 269: ... :
  // 270:   func grammar::current_node stream
  frame->slots[5] /* temp__3 */ = create_closure(entry__45_5, 0);
  // 271: :
  // 272:   func grammar::current_node
  frame->slots[6] /* temp__4 */ = create_closure(entry__45_6, 0);
  // 268: if
  // 269:   parameter_count_of(func) == 2:
  // 270:     func grammar::current_node stream
  // 271:   :
  // 272:     func grammar::current_node
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__45_7;
}
static void entry__45_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // func: 0
  // stream: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* func */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 270: func grammar::current_node stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__45_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // func: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* func */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 272: func grammar::current_node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__45_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 273: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__46_1_std__inspect_node(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 275: ... types::inspect_node(.function_of func)
  {
    NODE *temp = clone_object_and_attributes(var.types__inspect_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__function_of, frame->slots[0] /* func */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 275: ... -> types::inspect_node(.function_of func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__48_1_types__modify_node_grammar__match(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // stream: 1
  // func: 2
  frame->slots[2] /* func */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 283: $func function_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._function_of;
  func = myself->type;
  frame->cont = cont__48_2;
}
static void cont__48_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* func */, arguments->slots[0]);
  // 285: parameter_count_of(func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* func */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__48_3;
}
static void cont__48_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 285: parameter_count_of(func) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__48_4;
}
static void cont__48_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 285: ... :
  // 286:   func &grammar::current_node stream
  frame->slots[5] /* temp__3 */ = create_closure(entry__48_5, 0);
  // 287: :
  // 288:   func &grammar::current_node
  frame->slots[6] /* temp__4 */ = create_closure(entry__48_7, 0);
  // 284: if
  // 285:   parameter_count_of(func) == 2:
  // 286:     func &grammar::current_node stream
  // 287:   :
  // 288:     func &grammar::current_node
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__48_9;
}
static void entry__48_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // func: 0
  // stream: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* func */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 286: func &grammar::current_node stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__48_6;
}
static void cont__48_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__48_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // func: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* func */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 288: func &grammar::current_node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__48_8;
}
static void cont__48_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__48_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 289: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__49_1_std__modify_node(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 291: ... types::modify_node(.function_of func)
  {
    NODE *temp = clone_object_and_attributes(var.types__modify_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__function_of, frame->slots[0] /* func */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 291: ... -> types::modify_node(.function_of func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__51_1_types__check_node_grammar__match(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // func: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* func */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 304: $func function_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._function_of;
  func = myself->type;
  frame->cont = cont__51_2;
}
static void cont__51_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* func */, arguments->slots[0]);
  // 306: parameter_count_of(func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* func */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__51_3;
}
static void cont__51_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 306: parameter_count_of(func) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__51_4;
}
static void cont__51_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 306: ... :
  // 307:   unless func(grammar::current_node stream): return undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__51_5, 0);
  // 308: :
  // 309:   unless func(grammar::current_node): return undefined
  frame->slots[7] /* temp__4 */ = create_closure(entry__51_8, 0);
  // 305: if
  // 306:   parameter_count_of(func) == 2:
  // 307:     unless func(grammar::current_node stream): return undefined
  // 308:   :
  // 309:     unless func(grammar::current_node): return undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__51_11;
}
static void entry__51_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 309: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__51_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 307: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__51_5(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // func: 0
  // stream: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* func */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 307: ... func(grammar::current_node stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__51_6;
}
static void cont__51_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 307: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__51_7, 0);
  // 307: unless func(grammar::current_node stream): return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__51_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // func: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* func */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 309: ... func(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__51_9;
}
static void cont__51_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 309: ... : return undefined
  frame->slots[3] /* temp__2 */ = create_closure(entry__51_10, 0);
  // 309: unless func(grammar::current_node): return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__51_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 310: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__52_1_std__check_node(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 312: ... types::check_node(.function_of func)
  {
    NODE *temp = clone_object_and_attributes(var.types__check_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__function_of, frame->slots[0] /* func */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 312: ... -> types::check_node(.function_of func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__54_1_types__grammar_action_grammar__match(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 320: ... function_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._function_of;
  func = myself->type;
  frame->cont = cont__54_2;
}
static void cont__54_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 320: ... function_of(self)(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__54_3;
}
static void cont__54_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 320: -> function_of(self)(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__55_1_std__grammar_action(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 322: ... types::grammar_action(.function_of func)
  {
    NODE *temp = clone_object_and_attributes(var.types__grammar_action);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__function_of, frame->slots[0] /* func */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 322: ... -> types::grammar_action(.function_of func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__57_1_types__set_field_grammar__match(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 330: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__57_2;
}
static void cont__57_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 330: setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__57_3;
}
static void cont__57_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 330: setter_of(self) &grammar::current_node expr_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__57_4;
}
static void cont__57_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  // 331: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__58_1_std__set_field(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // setter: 0
  // expr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 334: ... types::set_field(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__set_field);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 334: -> types::set_field(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__60_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 342: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__60_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 342: ... -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__60_1_std__END_OF_TEXT_grammar__match(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 342: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__60_2;
}
static void cont__60_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 342: if stream .has_minimum_length. 1 (-> undefined) -> 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__60_3;
  arguments->slots[2] = func__60_4;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__62_1_std__LETTER_grammar__match(void) {
  allocate_initialized_frame_gc(3, 11);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 355: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__62_2;
}
static void cont__62_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 355: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__62_3, 0);
  // 355: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__62_4;
}
static void entry__62_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 355: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__62_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 357: stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__62_5;
}
static void cont__62_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 357: stream(1) >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__62_6;
}
static void cont__62_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 357: stream(1) >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__62_7;
}
static void cont__62_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 357: ... stream(1) <= 'z'
  frame->slots[8] /* temp__6 */ = create_closure(entry__62_8, 0);
  // 357: stream(1) >= 'a' && stream(1) <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__62_12;
}
static void entry__62_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 357: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__62_9;
}
static void cont__62_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 357: ... stream(1) <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__62_10;
}
static void cont__62_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 357: ... stream(1) <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__62_11;
}
static void cont__62_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 357: ... stream(1) <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__62_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 357: ... stream(1) >= 'A' && stream(1) <= 'Z'
  frame->slots[9] /* temp__7 */ = create_closure(entry__62_13, 0);
  // 357: stream(1) >= 'a' && stream(1) <= 'z' || stream(1) >= 'A' && stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__7 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__62_22;
}
static void entry__62_13(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 357: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__62_14;
}
static void cont__62_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 357: ... stream(1) >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__62_15;
}
static void cont__62_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 357: ... stream(1) >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__62_16;
}
static void cont__62_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 357: ... stream(1) <= 'Z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__62_17, 0);
  // 357: ... stream(1) >= 'A' && stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__62_21;
}
static void entry__62_17(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 357: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__62_18;
}
static void cont__62_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 357: ... stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__62_19;
}
static void cont__62_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 357: ... stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__62_20;
}
static void cont__62_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 357: ... stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__62_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 357: ... stream(1) >= 'A' && stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__62_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 358: :
  // 359:   return 1
  frame->slots[10] /* temp__8 */ = create_closure(entry__62_23, 0);
  // 356: if
  // 357:   stream(1) >= 'a' && stream(1) <= 'z' || stream(1) >= 'A' && stream(1) <= 'Z'
  // 358:   :
  // 359:     return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__8 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__62_24;
}
static void entry__62_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 359: return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__62_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 360: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__64_1_std__UPPER_CASE_LETTER_grammar__match(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 373: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__64_2;
}
static void cont__64_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 373: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__64_3, 0);
  // 373: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__64_4;
}
static void entry__64_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 373: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 374: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__64_5;
}
static void cont__64_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 374: ... stream(1) >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__64_6;
}
static void cont__64_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 374: ... stream(1) >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__64_7;
}
static void cont__64_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 374: ... stream(1) <= 'Z'
  frame->slots[7] /* temp__5 */ = create_closure(entry__64_8, 0);
  // 374: ... stream(1) >= 'A' && stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__64_12;
}
static void entry__64_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 374: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__64_9;
}
static void cont__64_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 374: ... stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__64_10;
}
static void cont__64_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 374: ... stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__64_11;
}
static void cont__64_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 374: ... stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__64_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 374: ... : return 1
  frame->slots[8] /* temp__6 */ = create_closure(entry__64_13, 0);
  // 374: if stream(1) >= 'A' && stream(1) <= 'Z': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__64_14;
}
static void entry__64_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 374: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__64_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 375: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__66_1_std__LOWER_CASE_LETTER_grammar__match(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 388: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__66_2;
}
static void cont__66_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 388: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__66_3, 0);
  // 388: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__66_4;
}
static void entry__66_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 388: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__66_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 389: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__66_5;
}
static void cont__66_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 389: ... stream(1) >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__66_6;
}
static void cont__66_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 389: ... stream(1) >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__66_7;
}
static void cont__66_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 389: ... stream(1) <= 'z'
  frame->slots[7] /* temp__5 */ = create_closure(entry__66_8, 0);
  // 389: ... stream(1) >= 'a' && stream(1) <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__66_12;
}
static void entry__66_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 389: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__66_9;
}
static void cont__66_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 389: ... stream(1) <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__66_10;
}
static void cont__66_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 389: ... stream(1) <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__66_11;
}
static void cont__66_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 389: ... stream(1) <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__66_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 389: ... : return 1
  frame->slots[8] /* temp__6 */ = create_closure(entry__66_13, 0);
  // 389: if stream(1) >= 'a' && stream(1) <= 'z': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__66_14;
}
static void entry__66_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 389: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__66_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 390: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__68_1_std__DIGIT_grammar__match(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 403: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__68_2;
}
static void cont__68_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 403: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__68_3, 0);
  // 403: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__68_4;
}
static void entry__68_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 403: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 404: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__68_5;
}
static void cont__68_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 404: ... stream(1) >= '0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_6;
}
static void cont__68_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 404: ... stream(1) >= '0'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__68_7;
}
static void cont__68_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 404: ... stream(1) <= '9'
  frame->slots[7] /* temp__5 */ = create_closure(entry__68_8, 0);
  // 404: ... stream(1) >= '0' && stream(1) <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__68_12;
}
static void entry__68_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 404: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__68_9;
}
static void cont__68_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 404: ... stream(1) <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__68_10;
}
static void cont__68_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 404: ... stream(1) <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__68_11;
}
static void cont__68_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 404: ... stream(1) <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__68_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 404: ... : return 1
  frame->slots[8] /* temp__6 */ = create_closure(entry__68_13, 0);
  // 404: if stream(1) >= '0' && stream(1) <= '9': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__68_14;
}
static void entry__68_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 404: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__68_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 405: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__70_1_std__WHITESPACE_CHARACTER_grammar__match(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // chr: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* chr */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 418: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__70_2;
}
static void cont__70_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 418: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__70_3, 0);
  // 418: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__70_4;
}
static void entry__70_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 418: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 419: $chr stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__70_5;
}
static void cont__70_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 420: ... chr <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[3] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__70_6;
}
static void cont__70_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 420: ... chr <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__70_7;
}
static void cont__70_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 420: ... chr == '@del;'
  frame->slots[7] /* temp__4 */ = create_closure(entry__70_8, 0);
  // 420: ... chr <= ' ' || chr == '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__70_10;
}
static void entry__70_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 420: ... chr == '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__127;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__70_9;
}
static void cont__70_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 420: ... chr == '@del;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__70_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 420: ... : return 1
  frame->slots[8] /* temp__5 */ = create_closure(entry__70_11, 0);
  // 420: if chr <= ' ' || chr == '@del;': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__70_12;
}
static void entry__70_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 420: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__70_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 421: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__73_1_std__PRINTABLE_CHARACTER_grammar__match(void) {
  allocate_initialized_frame_gc(3, 11);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // chr: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* chr */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 439: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__73_2;
}
static void cont__73_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 439: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__73_3, 0);
  // 439: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__73_4;
}
static void entry__73_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 439: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 440: $chr stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__73_5;
}
static void cont__73_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 441: ... chr >= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_6;
}
static void cont__73_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 441: ... chr >= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__73_7;
}
static void cont__73_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 441: ... chr < '@del;'
  frame->slots[8] /* temp__5 */ = create_closure(entry__73_8, 0);
  // 441: ... chr >= ' ' && chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__73_10;
}
static void entry__73_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__127;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_9;
}
static void cont__73_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 441: ... chr < '@del;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 441: ... chr >= '@nbsp;'
  frame->slots[9] /* temp__6 */ = create_closure(entry__73_11, 0);
  // 441: ... chr >= ' ' && chr < '@del;' || chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__73_14;
}
static void entry__73_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__160;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__73_12;
}
static void cont__73_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 441: ... chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__73_13;
}
static void cont__73_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 441: ... chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__73_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 441: ... : return 1
  frame->slots[10] /* temp__7 */ = create_closure(entry__73_15, 0);
  // 441: if chr >= ' ' && chr < '@del;' || chr >= '@nbsp;': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__7 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__73_16;
}
static void entry__73_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__73_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 442: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__75_1_std__NON_SPACE_CHARACTER_grammar__match(void) {
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // chr: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* chr */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 455: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__75_2;
}
static void cont__75_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 455: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__75_3, 0);
  // 455: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__75_4;
}
static void entry__75_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 455: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 456: $chr stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__75_5;
}
static void cont__75_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 457: ... chr > ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[3] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__75_6;
}
static void cont__75_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 457: ... chr < '@del;'
  frame->slots[7] /* temp__4 */ = create_closure(entry__75_7, 0);
  // 457: ... chr > ' ' && chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__75_9;
}
static void entry__75_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 457: ... chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__127;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__75_8;
}
static void cont__75_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 457: ... chr < '@del;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 457: ... chr >= '@nbsp;'
  frame->slots[8] /* temp__5 */ = create_closure(entry__75_10, 0);
  // 457: ... chr > ' ' && chr < '@del;' || chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__75_13;
}
static void entry__75_10(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 457: ... chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__160;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__75_11;
}
static void cont__75_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 457: ... chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__75_12;
}
static void cont__75_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 457: ... chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__75_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 457: ... : return 1
  frame->slots[9] /* temp__6 */ = create_closure(entry__75_14, 0);
  // 457: if chr > ' ' && chr < '@del;' || chr >= '@nbsp;': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__75_15;
}
static void entry__75_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 457: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__75_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 458: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__77_1_std__ANY_CHARACTER_grammar__match(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 471: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__77_2;
}
static void cont__77_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 471: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__77_3, 0);
  // 471: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__77_4;
}
static void entry__77_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 471: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__77_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 472: -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__78_1_types__character_grammar__match(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // chr: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 477: ... match_character stream chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = frame->caller_result_count;
  myself = get__match_character();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__79_1_types__value_range_grammar__match(void) {
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // chr: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* chr */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 485: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__79_2;
}
static void cont__79_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 485: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__79_3, 0);
  // 485: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__79_4;
}
static void entry__79_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 485: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 486: $chr stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__79_5;
}
static void cont__79_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 487: ... lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__79_6;
}
static void cont__79_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 487: ... chr >= lower_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* chr */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__79_7;
}
static void cont__79_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 487: ... chr >= lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__79_8;
}
static void cont__79_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 487: ... chr <= upper_bound_of(self)
  frame->slots[8] /* temp__5 */ = create_closure(entry__79_9, 0);
  // 487: ... chr >= lower_bound_of(self) && chr <= upper_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__79_13;
}
static void entry__79_9(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 487: ... upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__79_10;
}
static void cont__79_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 487: ... chr <= upper_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__79_11;
}
static void cont__79_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 487: ... chr <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__79_12;
}
static void cont__79_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 487: ... chr <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__79_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 487: ... : return 1
  frame->slots[9] /* temp__6 */ = create_closure(entry__79_14, 0);
  // 487: if chr >= lower_bound_of(self) && chr <= upper_bound_of(self): return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__79_15;
}
static void entry__79_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 487: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__79_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 488: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__80_1_types__list_grammar__match(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // stream: 1
  // return: 2
  // len: 3
  // original_node: 4
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* len */ = create_cell();
  frame->slots[4] /* original_node */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* stream */ = create_cell_with_contents(arguments->slots[1]);
  // 496: $$len 0
  ((CELL *)frame->slots[3])->contents /* len */ = number__0;
  // 497: $original_node grammar::current_node
  initialize_future(frame->slots[4] /* original_node */, get__grammar__current_node());
  // 498: ... : (expr)
  // 499:   $n grammar::match(expr stream)
  // 500:   unless n.is_defined:
  // 501:     !grammar::current_node original_node
  // 502:     return undefined
  // 503:   range &stream n+1 -1
  // 504:   plus &len n
  frame->slots[5] /* temp__1 */ = create_closure(entry__80_2, 1);
  // 498: for_each self: (expr)
  // 499:   $n grammar::match(expr stream)
  // 500:   unless n.is_defined:
  // 501:     !grammar::current_node original_node
  // 502:     return undefined
  // 503:   range &stream n+1 -1
  // 504:   plus &len n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__80_11;
}
static void entry__80_2(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // expr: 0
  // stream: 1
  // original_node: 2
  // return: 3
  // len: 4
  // n: 5
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[2] = myself->closure.frame->slots[4]; /* original_node */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  frame->slots[4] = myself->closure.frame->slots[3]; /* len */
  frame->slots[5] /* n */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 499: $n grammar::match(expr stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__80_3;
}
static void cont__80_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* n */, arguments->slots[0]);
  // 500: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__80_4;
}
static void cont__80_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 500: ... :
  // 501:   !grammar::current_node original_node
  // 502:   return undefined
  frame->slots[7] /* temp__2 */ = create_closure(entry__80_5, 0);
  // 500: unless n.is_defined:
  // 501:   !grammar::current_node original_node
  // 502:   return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__80_6;
}
static void entry__80_5(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // original_node: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* original_node */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 501: !grammar::current_node original_node
  set__grammar__current_node(frame->slots[0] /* original_node */);
  // 502: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__80_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 503: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__80_7;
}
static void cont__80_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 503: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__80_8;
}
static void cont__80_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 503: range &stream n+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* stream */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__80_9;
}
static void cont__80_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* stream */ = arguments->slots[0];
  // 504: plus &len n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* len */;
  arguments->slots[1] = frame->slots[5] /* n */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__80_10;
}
static void cont__80_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* len */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__80_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 505: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* len */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__81_1_types__object_grammar__search(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // expr: 0
  // stream: 1
  // nth: 2
  // return: 3
  // pos: 4
  // s: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* pos */ = create_cell();
  frame->slots[5] /* s */ = create_cell();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* nth */ = create_cell_with_contents(arguments->slots[2]);
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* nth */ = create_cell_with_contents(number__1);
  }
  // 514: $$pos 1
  ((CELL *)frame->slots[4])->contents /* pos */ = number__1;
  // 515: $$s stream
  ((CELL *)frame->slots[5])->contents /* s */ = frame->slots[1] /* stream */;
  // 517: nth > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* nth */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__81_2;
}
static void cont__81_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 517: ... :
  // 518:   forever:
  // 519:     $len grammar::match(expr s)
  // 520:     if len.is_defined:
  // 521:       if nth == 1: return pos len
  // 522:       if len > 0:
  // 523:         plus &pos len-1
  // 524:         range &s len -1
  // 525:       minus &nth 1
  // 526:     unless s .has_minimum_length. 1: return undefined undefined
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__81_3, 0);
  // 529: :
  // 530:   negate &nth
  // 531:   $$positions empty_list
  // 532:   $$lengths empty_list
  // 533:   forever:
  // 534:     $len grammar::match(expr s)
  // 535:     if len.is_defined:
  // 536:       if length_of(positions) >= nth:
  // 537:         range &positions 2 -1
  // 538:         range &lengths 2 -1
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__81_26, 0);
  // 516: if
  // 517:   nth > 0:
  // 518:     forever:
  // 519:       $len grammar::match(expr s)
  // 520:       if len.is_defined:
  // 521:         if nth == 1: return pos len
  // 522:         if len > 0:
  // 523:           plus &pos len-1
  // 524:           range &s len -1
  // 525:         minus &nth 1
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_62;
}
static void entry__81_28(void) {
  allocate_initialized_frame_gc(7, 10);
  // slot allocations:
  // expr: 0
  // s: 1
  // positions: 2
  // nth: 3
  // lengths: 4
  // pos: 5
  // return: 6
  // len: 7
  frame->slots[0] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[1] = myself->closure.frame->slots[2]; /* s */
  frame->slots[2] = myself->closure.frame->slots[5]; /* positions */
  frame->slots[3] = myself->closure.frame->slots[0]; /* nth */
  frame->slots[4] = myself->closure.frame->slots[6]; /* lengths */
  frame->slots[5] = myself->closure.frame->slots[3]; /* pos */
  frame->slots[6] = myself->closure.frame->slots[4]; /* return */
  frame->slots[7] /* len */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 534: $len grammar::match(expr s)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__81_29;
}
static void cont__81_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* len */, arguments->slots[0]);
  // 535: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__81_30;
}
static void cont__81_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 535: ... :
  // 536:   if length_of(positions) >= nth:
  // 537:     range &positions 2 -1
  // 538:     range &lengths 2 -1
  // 539:   push &positions pos
  // 540:   push &lengths len
  // 541:   if len > 0:
  // 542:     plus &pos len-1
  // 543:     range &s len -1
  frame->slots[9] /* temp__2 */ = create_closure(entry__81_31, 0);
  // 535: if len.is_defined:
  // 536:   if length_of(positions) >= nth:
  // 537:     range &positions 2 -1
  // 538:     range &lengths 2 -1
  // 539:   push &positions pos
  // 540:   push &lengths len
  // 541:   if len > 0:
  // 542:     plus &pos len-1
  // 543:     range &s len -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_49;
}
static void entry__81_44(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // pos: 0
  // len: 1
  // s: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* pos */
  frame->slots[1] = myself->closure.frame->slots[4]; /* len */
  frame->slots[2] = myself->closure.frame->slots[5]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 542: ... len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__81_45;
}
static void cont__81_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 542: plus &pos len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pos */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__81_46;
}
static void cont__81_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pos */ = arguments->slots[0];
  // 543: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_47;
}
static void cont__81_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 543: range &s len -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  arguments->slots[1] = frame->slots[1] /* len */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__81_48;
}
static void cont__81_48(void) {
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
static void entry__81_31(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // positions: 0
  // nth: 1
  // lengths: 2
  // pos: 3
  // len: 4
  // s: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* positions */
  frame->slots[1] = myself->closure.frame->slots[3]; /* nth */
  frame->slots[2] = myself->closure.frame->slots[4]; /* lengths */
  frame->slots[3] = myself->closure.frame->slots[5]; /* pos */
  frame->slots[4] = myself->closure.frame->slots[7]; /* len */
  frame->slots[5] = myself->closure.frame->slots[1]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 536: ... length_of(positions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* positions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__81_32;
}
static void cont__81_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 536: ... length_of(positions) >= nth
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* nth */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__81_33;
}
static void cont__81_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 536: ... length_of(positions) >= nth
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__81_34;
}
static void cont__81_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 536: ... :
  // 537:   range &positions 2 -1
  // 538:   range &lengths 2 -1
  frame->slots[9] /* temp__4 */ = create_closure(entry__81_35, 0);
  // 536: if length_of(positions) >= nth:
  // 537:   range &positions 2 -1
  // 538:   range &lengths 2 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_40;
}
static void entry__81_35(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // positions: 0
  // lengths: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* positions */
  frame->slots[1] = myself->closure.frame->slots[2]; /* lengths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 537: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_36;
}
static void cont__81_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 537: range &positions 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* positions */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__81_37;
}
static void cont__81_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* positions */ = arguments->slots[0];
  // 538: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_38;
}
static void cont__81_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 538: range &lengths 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* lengths */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__81_39;
}
static void cont__81_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* lengths */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 539: push &positions pos
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* positions */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* pos */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__81_41;
}
static void cont__81_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* positions */ = arguments->slots[0];
  // 540: push &lengths len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* lengths */;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__81_42;
}
static void cont__81_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* lengths */ = arguments->slots[0];
  // 541: ... len > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__81_43;
}
static void cont__81_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 541: ... :
  // 542:   plus &pos len-1
  // 543:   range &s len -1
  frame->slots[7] /* temp__2 */ = create_closure(entry__81_44, 0);
  // 541: if len > 0:
  // 542:   plus &pos len-1
  // 543:   range &s len -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 544: ... s .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__81_50;
}
static void cont__81_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 544: ... :
  // 545:   if length_of(positions) < nth: return undefined undefined
  // 546:   return positions(1) lengths(1)
  frame->slots[9] /* temp__2 */ = create_closure(entry__81_51, 0);
  // 544: unless s .has_minimum_length. 1:
  // 545:   if length_of(positions) < nth: return undefined undefined
  // 546:   return positions(1) lengths(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__81_58;
}
static void entry__81_51(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // positions: 0
  // nth: 1
  // return: 2
  // lengths: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* positions */
  frame->slots[1] = myself->closure.frame->slots[3]; /* nth */
  frame->slots[2] = myself->closure.frame->slots[6]; /* return */
  frame->slots[3] = myself->closure.frame->slots[4]; /* lengths */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 545: ... length_of(positions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* positions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__81_52;
}
static void cont__81_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 545: ... length_of(positions) < nth
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* nth */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__81_53;
}
static void cont__81_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 545: ... : return undefined undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__81_54, 0);
  // 545: if length_of(positions) < nth: return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_55;
}
static void entry__81_54(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 545: ... return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 546: ... positions(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* positions */;
  func = myself->type;
  frame->cont = cont__81_56;
}
static void cont__81_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 546: ... lengths(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* lengths */;
  func = myself->type;
  frame->cont = cont__81_57;
}
static void cont__81_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 546: return positions(1) lengths(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 547: plus &pos 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__81_59;
}
static void cont__81_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* pos */ = arguments->slots[0];
  // 548: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_60;
}
static void cont__81_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 548: range &s 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__81_61;
}
static void cont__81_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* s */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_4(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // expr: 0
  // s: 1
  // nth: 2
  // return: 3
  // pos: 4
  // len: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* expr */
  frame->slots[1] = myself->closure.frame->slots[1]; /* s */
  frame->slots[2] = myself->closure.frame->slots[2]; /* nth */
  frame->slots[3] = myself->closure.frame->slots[3]; /* return */
  frame->slots[4] = myself->closure.frame->slots[4]; /* pos */
  frame->slots[5] /* len */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 519: $len grammar::match(expr s)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__81_5;
}
static void cont__81_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* len */, arguments->slots[0]);
  // 520: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__81_6;
}
static void cont__81_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 520: ... :
  // 521:   if nth == 1: return pos len
  // 522:   if len > 0:
  // 523:     plus &pos len-1
  // 524:     range &s len -1
  // 525:   minus &nth 1
  frame->slots[7] /* temp__2 */ = create_closure(entry__81_7, 0);
  // 520: if len.is_defined:
  // 521:   if nth == 1: return pos len
  // 522:   if len > 0:
  // 523:     plus &pos len-1
  // 524:     range &s len -1
  // 525:   minus &nth 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_19;
}
static void entry__81_7(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // nth: 0
  // return: 1
  // pos: 2
  // len: 3
  // s: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* nth */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] = myself->closure.frame->slots[4]; /* pos */
  frame->slots[3] = myself->closure.frame->slots[5]; /* len */
  frame->slots[4] = myself->closure.frame->slots[1]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 521: ... nth == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* nth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__81_8;
}
static void cont__81_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 521: ... : return pos len
  frame->slots[6] /* temp__2 */ = create_closure(entry__81_9, 0);
  // 521: if nth == 1: return pos len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_10;
}
static void entry__81_9(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // pos: 1
  // len: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* pos */
  frame->slots[2] = myself->closure.frame->slots[3]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 521: ... return pos len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* pos */;
  arguments->slots[1] = frame->slots[2] /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 522: ... len > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__81_11;
}
static void cont__81_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 522: ... :
  // 523:   plus &pos len-1
  // 524:   range &s len -1
  frame->slots[6] /* temp__2 */ = create_closure(entry__81_12, 0);
  // 522: if len > 0:
  // 523:   plus &pos len-1
  // 524:   range &s len -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__81_17;
}
static void entry__81_12(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // pos: 0
  // len: 1
  // s: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* pos */
  frame->slots[1] = myself->closure.frame->slots[3]; /* len */
  frame->slots[2] = myself->closure.frame->slots[4]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 523: ... len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__81_13;
}
static void cont__81_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 523: plus &pos len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pos */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__81_14;
}
static void cont__81_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pos */ = arguments->slots[0];
  // 524: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_15;
}
static void cont__81_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 524: range &s len -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  arguments->slots[1] = frame->slots[1] /* len */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__81_16;
}
static void cont__81_16(void) {
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
static void cont__81_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 525: minus &nth 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* nth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__81_18;
}
static void cont__81_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* nth */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 526: ... s .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__81_20;
}
static void cont__81_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 526: ... : return undefined undefined
  frame->slots[7] /* temp__2 */ = create_closure(entry__81_21, 0);
  // 526: unless s .has_minimum_length. 1: return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__81_22;
}
static void entry__81_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 526: ... return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 527: plus &pos 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__81_23;
}
static void cont__81_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* pos */ = arguments->slots[0];
  // 528: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__81_24;
}
static void cont__81_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 528: range &s 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__81_25;
}
static void cont__81_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* s */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_3(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // expr: 0
  // s: 1
  // nth: 2
  // return: 3
  // pos: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* expr */
  frame->slots[1] = myself->closure.frame->slots[5]; /* s */
  frame->slots[2] = myself->closure.frame->slots[2]; /* nth */
  frame->slots[3] = myself->closure.frame->slots[3]; /* return */
  frame->slots[4] = myself->closure.frame->slots[4]; /* pos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 518: ... :
  // 519:   $len grammar::match(expr s)
  // 520:   if len.is_defined:
  // 521:     if nth == 1: return pos len
  // 522:     if len > 0:
  // 523:       plus &pos len-1
  // 524:       range &s len -1
  // 525:     minus &nth 1
  // 526:   unless s .has_minimum_length. 1: return undefined undefined
  // 527:   plus &pos 1
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__81_4, 0);
  // 518: forever:
  // 519:   $len grammar::match(expr s)
  // 520:   if len.is_defined:
  // 521:     if nth == 1: return pos len
  // 522:     if len > 0:
  // 523:       plus &pos len-1
  // 524:       range &s len -1
  // 525:     minus &nth 1
  // 526:   unless s .has_minimum_length. 1: return undefined undefined
  // 527:   plus &pos 1
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__81_26(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // nth: 0
  // expr: 1
  // s: 2
  // pos: 3
  // return: 4
  // positions: 5
  // lengths: 6
  frame->slots[0] = myself->closure.frame->slots[2]; /* nth */
  frame->slots[1] = myself->closure.frame->slots[0]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[5]; /* s */
  frame->slots[3] = myself->closure.frame->slots[4]; /* pos */
  frame->slots[4] = myself->closure.frame->slots[3]; /* return */
  frame->slots[5] /* positions */ = create_cell();
  frame->slots[6] /* lengths */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 530: negate &nth
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* nth */;
  result_count = 1;
  myself = get__negate();
  func = myself->type;
  frame->cont = cont__81_27;
}
static void cont__81_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* nth */ = arguments->slots[0];
  // 531: $$positions empty_list
  ((CELL *)frame->slots[5])->contents /* positions */ = get__empty_list();
  // 532: $$lengths empty_list
  ((CELL *)frame->slots[6])->contents /* lengths */ = get__empty_list();
  // 533: ... :
  // 534:   $len grammar::match(expr s)
  // 535:   if len.is_defined:
  // 536:     if length_of(positions) >= nth:
  // 537:       range &positions 2 -1
  // 538:       range &lengths 2 -1
  // 539:     push &positions pos
  // 540:     push &lengths len
  // 541:     if len > 0:
  // 542:       plus &pos len-1
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__81_28, 0);
  // 533: forever:
  // 534:   $len grammar::match(expr s)
  // 535:   if len.is_defined:
  // 536:     if length_of(positions) >= nth:
  // 537:       range &positions 2 -1
  // 538:       range &lengths 2 -1
  // 539:     push &positions pos
  // 540:     push &lengths len
  // 541:     if len > 0:
  // 542:       plus &pos len-1
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__81_62(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__grammar(void) {
  var.grammar__match = collect_node(var.grammar__match);
  var.grammar__search = collect_node(var.grammar__search);
  var.types__grammar_object = collect_node(var.types__grammar_object);
  var.types__grammar_node = collect_node(var.types__grammar_node);
  var._expr_of = collect_node(var._expr_of);
  var._alternatives_of = collect_node(var._alternatives_of);
  var._setter_of = collect_node(var._setter_of);
  var._node_of = collect_node(var._node_of);
  var._function_of = collect_node(var._function_of);
  var.types__optional = collect_node(var.types__optional);
  var.std__optional = collect_node(var.std__optional);
  var.types__many = collect_node(var.types__many);
  var.std__many = collect_node(var.std__many);
  var.types__some = collect_node(var.types__some);
  var.std__some = collect_node(var.std__some);
  var.types__alt = collect_node(var.types__alt);
  var.std__alt = collect_node(var.std__alt);
  var.types__followed_by = collect_node(var.types__followed_by);
  var.std__followed_by = collect_node(var.std__followed_by);
  var.types__not_followed_by = collect_node(var.types__not_followed_by);
  var.std__not_followed_by = collect_node(var.std__not_followed_by);
  var.types__capture = collect_node(var.types__capture);
  var.std__capture = collect_node(var.std__capture);
  var.types__multi_capture = collect_node(var.types__multi_capture);
  var.std__multi_capture = collect_node(var.std__multi_capture);
  var.types__span = collect_node(var.types__span);
  var.std__span = collect_node(var.std__span);
  var.types__multi_span = collect_node(var.types__multi_span);
  var.std__multi_span = collect_node(var.std__multi_span);
  var.types__set_node = collect_node(var.types__set_node);
  var.std__set_node = collect_node(var.std__set_node);
  var.types__inspect_node = collect_node(var.types__inspect_node);
  var.std__inspect_node = collect_node(var.std__inspect_node);
  var.types__modify_node = collect_node(var.types__modify_node);
  var.std__modify_node = collect_node(var.std__modify_node);
  var.types__check_node = collect_node(var.types__check_node);
  var.std__check_node = collect_node(var.std__check_node);
  var.types__grammar_action = collect_node(var.types__grammar_action);
  var.std__grammar_action = collect_node(var.std__grammar_action);
  var.types__set_field = collect_node(var.types__set_field);
  var.std__set_field = collect_node(var.std__set_field);
  var.std__END_OF_TEXT = collect_node(var.std__END_OF_TEXT);
  var.std__LETTER = collect_node(var.std__LETTER);
  var.std__UPPER_CASE_LETTER = collect_node(var.std__UPPER_CASE_LETTER);
  var.std__LOWER_CASE_LETTER = collect_node(var.std__LOWER_CASE_LETTER);
  var.std__DIGIT = collect_node(var.std__DIGIT);
  var.std__WHITESPACE_CHARACTER = collect_node(var.std__WHITESPACE_CHARACTER);
  var.std__WHITESPACE = collect_node(var.std__WHITESPACE);
  var.std__PRINTABLE_CHARACTER = collect_node(var.std__PRINTABLE_CHARACTER);
  var.std__NON_SPACE_CHARACTER = collect_node(var.std__NON_SPACE_CHARACTER);
  var.std__ANY_CHARACTER = collect_node(var.std__ANY_CHARACTER);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__grammar(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("grammar", "match", get__grammar__match, &poly_idx__grammar__match, &var.grammar__match);
  define_polymorphic_function("grammar", "search", get__grammar__search, &poly_idx__grammar__search, &var.grammar__search);
  register_polymorphic_function_with_setter("_basic__grammar::expr_of", &poly_idx__expr_of);
  register_polymorphic_function_with_setter("_basic__grammar::alternatives_of", &poly_idx__alternatives_of);
  register_polymorphic_function_with_setter("_basic__grammar::setter_of", &poly_idx__setter_of);
  register_polymorphic_function_with_setter("_basic__grammar::node_of", &poly_idx__node_of);
  register_polymorphic_function_with_setter("_basic__grammar::function_of", &poly_idx__function_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__grammar(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__90 = from_uchar32(90);
  character__122 = from_uchar32(122);
  character__57 = from_uchar32(57);
  character__160 = from_uchar32(160);
  character__65 = from_uchar32(65);
  number__0 = from_uint32(0U);
  character__48 = from_uchar32(48);
  character__32 = from_uchar32(32);
  character__127 = from_uchar32(127);
  character__97 = from_uchar32(97);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__12_1_types__optional_grammar__match = create_function(entry__12_1_types__optional_grammar__match, 2);
  func__13_1_std__optional = create_function(entry__13_1_std__optional, 1);
  func__15_1_types__many_grammar__match = create_function(entry__15_1_types__many_grammar__match, 2);
  func__16_1_std__many = create_function(entry__16_1_std__many, 1);
  func__18_1_types__some_grammar__match = create_function(entry__18_1_types__some_grammar__match, 2);
  func__19_1_std__some = create_function(entry__19_1_std__some, 1);
  func__21_1_types__alt_grammar__match = create_function(entry__21_1_types__alt_grammar__match, 2);
  func__22_1_std__alt = create_function(entry__22_1_std__alt, -1);
  func__24_1_types__followed_by_grammar__match = create_function(entry__24_1_types__followed_by_grammar__match, 2);
  func__25_1_std__followed_by = create_function(entry__25_1_std__followed_by, 1);
  func__27_1_types__not_followed_by_grammar__match = create_function(entry__27_1_types__not_followed_by_grammar__match, 2);
  func__28_1_std__not_followed_by = create_function(entry__28_1_std__not_followed_by, 1);
  func__30_1_types__capture_grammar__match = create_function(entry__30_1_types__capture_grammar__match, 2);
  func__31_1_std__capture = create_function(entry__31_1_std__capture, -1);
  func__33_1_types__multi_capture_grammar__match = create_function(entry__33_1_types__multi_capture_grammar__match, 2);
  func__34_1_std__multi_capture = create_function(entry__34_1_std__multi_capture, -1);
  func__36_1_types__span_grammar__match = create_function(entry__36_1_types__span_grammar__match, 2);
  func__37_1_std__span = create_function(entry__37_1_std__span, 2);
  func__39_1_types__multi_span_grammar__match = create_function(entry__39_1_types__multi_span_grammar__match, 2);
  func__40_1_std__multi_span = create_function(entry__40_1_std__multi_span, -1);
  func__42_1_types__set_node_grammar__match = create_function(entry__42_1_types__set_node_grammar__match, 2);
  func__43_1_std__set_node = create_function(entry__43_1_std__set_node, 1);
  func__45_1_types__inspect_node_grammar__match = create_function(entry__45_1_types__inspect_node_grammar__match, 2);
  func__46_1_std__inspect_node = create_function(entry__46_1_std__inspect_node, 1);
  func__48_1_types__modify_node_grammar__match = create_function(entry__48_1_types__modify_node_grammar__match, 2);
  func__49_1_std__modify_node = create_function(entry__49_1_std__modify_node, 1);
  func__51_1_types__check_node_grammar__match = create_function(entry__51_1_types__check_node_grammar__match, 2);
  func__52_1_std__check_node = create_function(entry__52_1_std__check_node, 1);
  func__54_1_types__grammar_action_grammar__match = create_function(entry__54_1_types__grammar_action_grammar__match, 2);
  func__55_1_std__grammar_action = create_function(entry__55_1_std__grammar_action, 1);
  func__57_1_types__set_field_grammar__match = create_function(entry__57_1_types__set_field_grammar__match, 2);
  func__58_1_std__set_field = create_function(entry__58_1_std__set_field, 2);
  func__60_3 = create_function(entry__60_3, 0);
  func__60_4 = create_function(entry__60_4, 0);
  func__60_1_std__END_OF_TEXT_grammar__match = create_function(entry__60_1_std__END_OF_TEXT_grammar__match, 2);
  func__62_1_std__LETTER_grammar__match = create_function(entry__62_1_std__LETTER_grammar__match, 2);
  func__64_1_std__UPPER_CASE_LETTER_grammar__match = create_function(entry__64_1_std__UPPER_CASE_LETTER_grammar__match, 2);
  func__66_1_std__LOWER_CASE_LETTER_grammar__match = create_function(entry__66_1_std__LOWER_CASE_LETTER_grammar__match, 2);
  func__68_1_std__DIGIT_grammar__match = create_function(entry__68_1_std__DIGIT_grammar__match, 2);
  func__70_1_std__WHITESPACE_CHARACTER_grammar__match = create_function(entry__70_1_std__WHITESPACE_CHARACTER_grammar__match, 2);
  func__73_1_std__PRINTABLE_CHARACTER_grammar__match = create_function(entry__73_1_std__PRINTABLE_CHARACTER_grammar__match, 2);
  func__75_1_std__NON_SPACE_CHARACTER_grammar__match = create_function(entry__75_1_std__NON_SPACE_CHARACTER_grammar__match, 2);
  func__77_1_std__ANY_CHARACTER_grammar__match = create_function(entry__77_1_std__ANY_CHARACTER_grammar__match, 2);
  func__78_1_types__character_grammar__match = create_function(entry__78_1_types__character_grammar__match, 2);
  func__79_1_types__value_range_grammar__match = create_function(entry__79_1_types__value_range_grammar__match, 2);
  func__80_1_types__list_grammar__match = create_function(entry__80_1_types__list_grammar__match, 2);
  func__81_1_types__object_grammar__search = create_function(entry__81_1_types__object_grammar__search, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__grammar(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__grammar");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("types", "grammar_object", get__types__grammar_object, &var.types__grammar_object);
  define_single_assign_static("types", "grammar_node", get__types__grammar_node, &var.types__grammar_node);
  define_multi_assign_dynamic("grammar", "current_node", get__grammar__current_node, set__grammar__current_node, define__grammar__current_node, &dyna_idx__grammar__current_node);
  define__grammar__current_node(undefined);
  define_single_assign_static("types", "optional", get__types__optional, &var.types__optional);
  define_single_assign_static("std", "optional", get__std__optional, &var.std__optional);
  define_single_assign_static("types", "many", get__types__many, &var.types__many);
  define_single_assign_static("std", "many", get__std__many, &var.std__many);
  define_single_assign_static("types", "some", get__types__some, &var.types__some);
  define_single_assign_static("std", "some", get__std__some, &var.std__some);
  define_single_assign_static("types", "alt", get__types__alt, &var.types__alt);
  define_single_assign_static("std", "alt", get__std__alt, &var.std__alt);
  define_single_assign_static("types", "followed_by", get__types__followed_by, &var.types__followed_by);
  define_single_assign_static("std", "followed_by", get__std__followed_by, &var.std__followed_by);
  define_single_assign_static("types", "not_followed_by", get__types__not_followed_by, &var.types__not_followed_by);
  define_single_assign_static("std", "not_followed_by", get__std__not_followed_by, &var.std__not_followed_by);
  define_single_assign_static("types", "capture", get__types__capture, &var.types__capture);
  define_single_assign_static("std", "capture", get__std__capture, &var.std__capture);
  define_single_assign_static("types", "multi_capture", get__types__multi_capture, &var.types__multi_capture);
  define_single_assign_static("std", "multi_capture", get__std__multi_capture, &var.std__multi_capture);
  define_single_assign_static("types", "span", get__types__span, &var.types__span);
  define_single_assign_static("std", "span", get__std__span, &var.std__span);
  define_single_assign_static("types", "multi_span", get__types__multi_span, &var.types__multi_span);
  define_single_assign_static("std", "multi_span", get__std__multi_span, &var.std__multi_span);
  define_single_assign_static("types", "set_node", get__types__set_node, &var.types__set_node);
  define_single_assign_static("std", "set_node", get__std__set_node, &var.std__set_node);
  define_single_assign_static("types", "inspect_node", get__types__inspect_node, &var.types__inspect_node);
  define_single_assign_static("std", "inspect_node", get__std__inspect_node, &var.std__inspect_node);
  define_single_assign_static("types", "modify_node", get__types__modify_node, &var.types__modify_node);
  define_single_assign_static("std", "modify_node", get__std__modify_node, &var.std__modify_node);
  define_single_assign_static("types", "check_node", get__types__check_node, &var.types__check_node);
  define_single_assign_static("std", "check_node", get__std__check_node, &var.std__check_node);
  define_single_assign_static("types", "grammar_action", get__types__grammar_action, &var.types__grammar_action);
  define_single_assign_static("std", "grammar_action", get__std__grammar_action, &var.std__grammar_action);
  define_single_assign_static("types", "set_field", get__types__set_field, &var.types__set_field);
  define_single_assign_static("std", "set_field", get__std__set_field, &var.std__set_field);
  define_single_assign_static("std", "END_OF_TEXT", get__std__END_OF_TEXT, &var.std__END_OF_TEXT);
  define_single_assign_static("std", "LETTER", get__std__LETTER, &var.std__LETTER);
  define_single_assign_static("std", "UPPER_CASE_LETTER", get__std__UPPER_CASE_LETTER, &var.std__UPPER_CASE_LETTER);
  define_single_assign_static("std", "LOWER_CASE_LETTER", get__std__LOWER_CASE_LETTER, &var.std__LOWER_CASE_LETTER);
  define_single_assign_static("std", "DIGIT", get__std__DIGIT, &var.std__DIGIT);
  define_single_assign_static("std", "WHITESPACE_CHARACTER", get__std__WHITESPACE_CHARACTER, &var.std__WHITESPACE_CHARACTER);
  define_single_assign_static("std", "WHITESPACE", get__std__WHITESPACE, &var.std__WHITESPACE);
  define_single_assign_static("std", "PRINTABLE_CHARACTER", get__std__PRINTABLE_CHARACTER, &var.std__PRINTABLE_CHARACTER);
  define_single_assign_static("std", "NON_SPACE_CHARACTER", get__std__NON_SPACE_CHARACTER, &var.std__NON_SPACE_CHARACTER);
  define_single_assign_static("std", "ANY_CHARACTER", get__std__ANY_CHARACTER, &var.std__ANY_CHARACTER);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__grammar(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__grammar");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "WHITESPACE_CHARACTER", &get__WHITESPACE_CHARACTER, &get_value_or_future__WHITESPACE_CHARACTER);
  use_read_only(NULL, "default_value", &get__default_value, &get_value_or_future__default_value);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "has_minimum_length", &get__has_minimum_length, &get_value_or_future__has_minimum_length);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "lower_bound_of", &get__lower_bound_of, &get_value_or_future__lower_bound_of);
  use_read_only(NULL, "many", &get__many, &get_value_or_future__many);
  use_read_only(NULL, "match_character", &get__match_character, &get_value_or_future__match_character);
  use_read_only(NULL, "minus", &get__minus, &get_value_or_future__minus);
  use_read_only(NULL, "negate", &get__negate, &get_value_or_future__negate);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("types", "character", &get__types__character, &get_value_or_future__types__character);
  use_read_only("types", "list", &get__types__list, &get_value_or_future__types__list);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only("types", "value_range", &get__types__value_range, &get_value_or_future__types__value_range);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "upper_bound_of", &get__upper_bound_of, &get_value_or_future__upper_bound_of);
  define_method("types", "optional", poly_idx__grammar__match, func__12_1_types__optional_grammar__match);
  define_method("types", "many", poly_idx__grammar__match, func__15_1_types__many_grammar__match);
  define_method("types", "some", poly_idx__grammar__match, func__18_1_types__some_grammar__match);
  define_method("types", "alt", poly_idx__grammar__match, func__21_1_types__alt_grammar__match);
  define_method("types", "followed_by", poly_idx__grammar__match, func__24_1_types__followed_by_grammar__match);
  define_method("types", "not_followed_by", poly_idx__grammar__match, func__27_1_types__not_followed_by_grammar__match);
  define_method("types", "capture", poly_idx__grammar__match, func__30_1_types__capture_grammar__match);
  define_method("types", "multi_capture", poly_idx__grammar__match, func__33_1_types__multi_capture_grammar__match);
  define_method("types", "span", poly_idx__grammar__match, func__36_1_types__span_grammar__match);
  define_method("types", "multi_span", poly_idx__grammar__match, func__39_1_types__multi_span_grammar__match);
  define_method("types", "set_node", poly_idx__grammar__match, func__42_1_types__set_node_grammar__match);
  define_method("types", "inspect_node", poly_idx__grammar__match, func__45_1_types__inspect_node_grammar__match);
  define_method("types", "modify_node", poly_idx__grammar__match, func__48_1_types__modify_node_grammar__match);
  define_method("types", "check_node", poly_idx__grammar__match, func__51_1_types__check_node_grammar__match);
  define_method("types", "grammar_action", poly_idx__grammar__match, func__54_1_types__grammar_action_grammar__match);
  define_method("types", "set_field", poly_idx__grammar__match, func__57_1_types__set_field_grammar__match);
  define_method("std", "END_OF_TEXT", poly_idx__grammar__match, func__60_1_std__END_OF_TEXT_grammar__match);
  define_method("std", "LETTER", poly_idx__grammar__match, func__62_1_std__LETTER_grammar__match);
  define_method("std", "UPPER_CASE_LETTER", poly_idx__grammar__match, func__64_1_std__UPPER_CASE_LETTER_grammar__match);
  define_method("std", "LOWER_CASE_LETTER", poly_idx__grammar__match, func__66_1_std__LOWER_CASE_LETTER_grammar__match);
  define_method("std", "DIGIT", poly_idx__grammar__match, func__68_1_std__DIGIT_grammar__match);
  define_method("std", "WHITESPACE_CHARACTER", poly_idx__grammar__match, func__70_1_std__WHITESPACE_CHARACTER_grammar__match);
  define_method("std", "PRINTABLE_CHARACTER", poly_idx__grammar__match, func__73_1_std__PRINTABLE_CHARACTER_grammar__match);
  define_method("std", "NON_SPACE_CHARACTER", poly_idx__grammar__match, func__75_1_std__NON_SPACE_CHARACTER_grammar__match);
  define_method("std", "ANY_CHARACTER", poly_idx__grammar__match, func__77_1_std__ANY_CHARACTER_grammar__match);
  define_method("types", "character", poly_idx__grammar__match, func__78_1_types__character_grammar__match);
  define_method("types", "value_range", poly_idx__grammar__match, func__79_1_types__value_range_grammar__match);
  define_method("types", "list", poly_idx__grammar__match, func__80_1_types__list_grammar__match);
  define_method("types", "object", poly_idx__grammar__search, func__81_1_types__object_grammar__search);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__grammar(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.grammar__match, create_function(type__grammar__match, -1));
  assign_value(&var.grammar__search, create_function(type__grammar__search, -1));
  assign_value(&var.types__grammar_object, get__types__object());
  assign_value(&var.types__grammar_node, get__types__object());
  assign_value(&var._expr_of, create_function(type__expr_of, -1));
  assign_value(&var._alternatives_of, create_function(type__alternatives_of, -1));
  assign_value(&var._setter_of, create_function(type__setter_of, -1));
  assign_value(&var._node_of, create_function(type__node_of, -1));
  assign_value(&var._function_of, create_function(type__function_of, -1));
  assign_variable(&var.types__optional, &var.types__grammar_object);
  assign_variable(&var.std__optional, &func__13_1_std__optional);
  assign_variable(&var.types__many, &var.types__grammar_object);
  assign_variable(&var.std__many, &func__16_1_std__many);
  assign_variable(&var.types__some, &var.types__grammar_object);
  assign_variable(&var.std__some, &func__19_1_std__some);
  assign_variable(&var.types__alt, &var.types__grammar_object);
  assign_variable(&var.std__alt, &func__22_1_std__alt);
  assign_variable(&var.types__followed_by, &var.types__grammar_object);
  assign_variable(&var.std__followed_by, &func__25_1_std__followed_by);
  assign_variable(&var.types__not_followed_by, &var.types__grammar_object);
  assign_variable(&var.std__not_followed_by, &func__28_1_std__not_followed_by);
  assign_variable(&var.types__capture, &var.types__grammar_object);
  assign_variable(&var.std__capture, &func__31_1_std__capture);
  assign_variable(&var.types__multi_capture, &var.types__grammar_object);
  assign_variable(&var.std__multi_capture, &func__34_1_std__multi_capture);
  assign_variable(&var.types__span, &var.types__grammar_object);
  assign_variable(&var.std__span, &func__37_1_std__span);
  assign_variable(&var.types__multi_span, &var.types__grammar_object);
  assign_variable(&var.std__multi_span, &func__40_1_std__multi_span);
  assign_variable(&var.types__set_node, &var.types__grammar_object);
  assign_variable(&var.std__set_node, &func__43_1_std__set_node);
  assign_variable(&var.types__inspect_node, &var.types__grammar_object);
  assign_variable(&var.std__inspect_node, &func__46_1_std__inspect_node);
  assign_variable(&var.types__modify_node, &var.types__grammar_object);
  assign_variable(&var.std__modify_node, &func__49_1_std__modify_node);
  assign_variable(&var.types__check_node, &var.types__grammar_object);
  assign_variable(&var.std__check_node, &func__52_1_std__check_node);
  assign_variable(&var.types__grammar_action, &var.types__grammar_object);
  assign_variable(&var.std__grammar_action, &func__55_1_std__grammar_action);
  assign_variable(&var.types__set_field, &var.types__grammar_object);
  assign_variable(&var.std__set_field, &func__58_1_std__set_field);
  assign_variable(&var.std__END_OF_TEXT, &var.types__grammar_object);
  assign_variable(&var.std__LETTER, &var.types__grammar_object);
  assign_variable(&var.std__UPPER_CASE_LETTER, &var.types__grammar_object);
  assign_variable(&var.std__LOWER_CASE_LETTER, &var.types__grammar_object);
  assign_variable(&var.std__DIGIT, &var.types__grammar_object);
  assign_variable(&var.std__WHITESPACE_CHARACTER, &var.types__grammar_object);
  assign_variable(&var.std__PRINTABLE_CHARACTER, &var.types__grammar_object);
  assign_variable(&var.std__NON_SPACE_CHARACTER, &var.types__grammar_object);
  assign_variable(&var.std__ANY_CHARACTER, &var.types__grammar_object);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__grammar(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__grammar);
}
