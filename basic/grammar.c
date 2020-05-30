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
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_namespace(const char *namespace);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *create_function(FUNC func, int par_count);
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
static NODE *func__types__optional__grammar__match_1;
static void entry__types__optional__grammar__match_1(void);
static FRAME_INFO frame__types__optional__grammar__match_1 = {2, {"self", "stream"}};
static void cont__types__optional__grammar__match_2(void);
static void cont__types__optional__grammar__match_3(void);
static void cont__types__optional__grammar__match_4(void);
static NODE *func__std__optional_1;
static void entry__std__optional_1(void);
static FRAME_INFO frame__std__optional_1 = {1, {"expr"}};
static NODE *get__std__optional(void) {
  return var.std__optional;
}
static NODE *get__types__many(void) {
  return var.types__many;
}
static NODE *func__types__many__grammar__match_1;
static void entry__types__many__grammar__match_1(void);
static FRAME_INFO frame__types__many__grammar__match_1 = {4, {"self", "stream", "return", "len"}};
static NODE *func__types__many__grammar__match_2;
static void entry__types__many__grammar__match_2(void);
static FRAME_INFO frame__types__many__grammar__match_2 = {5, {"self", "stream", "return", "len", "n"}};
static void cont__types__many__grammar__match_3(void);
static void cont__types__many__grammar__match_4(void);
static void cont__types__many__grammar__match_5(void);
static NODE *func__types__many__grammar__match_6;
static void entry__types__many__grammar__match_6(void);
static FRAME_INFO frame__types__many__grammar__match_6 = {2, {"return", "len"}};
static void cont__types__many__grammar__match_7(void);
static void cont__types__many__grammar__match_8(void);
static NODE *func__types__many__grammar__match_9;
static void entry__types__many__grammar__match_9(void);
static FRAME_INFO frame__types__many__grammar__match_9 = {2, {"len", "n"}};
static void cont__types__many__grammar__match_10(void);
static NODE *func__types__many__grammar__match_11;
static void entry__types__many__grammar__match_11(void);
static FRAME_INFO frame__types__many__grammar__match_11 = {2, {"len", "n"}};
static void cont__types__many__grammar__match_12(void);
static void cont__types__many__grammar__match_13(void);
static NODE *func__types__many__grammar__match_14;
static void entry__types__many__grammar__match_14(void);
static FRAME_INFO frame__types__many__grammar__match_14 = {2, {"return", "len"}};
static void cont__types__many__grammar__match_15(void);
static void cont__types__many__grammar__match_16(void);
static void cont__types__many__grammar__match_17(void);
static void cont__types__many__grammar__match_18(void);
static void cont__types__many__grammar__match_19(void);
static NODE *func__std__many_1;
static void entry__std__many_1(void);
static FRAME_INFO frame__std__many_1 = {1, {"expr"}};
static NODE *get__std__many(void) {
  return var.std__many;
}
static NODE *get__types__some(void) {
  return var.types__some;
}
static NODE *func__types__some__grammar__match_1;
static void entry__types__some__grammar__match_1(void);
static FRAME_INFO frame__types__some__grammar__match_1 = {4, {"self", "stream", "return", "len"}};
static NODE *func__types__some__grammar__match_2;
static void entry__types__some__grammar__match_2(void);
static FRAME_INFO frame__types__some__grammar__match_2 = {5, {"self", "stream", "return", "len", "n"}};
static void cont__types__some__grammar__match_3(void);
static void cont__types__some__grammar__match_4(void);
static void cont__types__some__grammar__match_5(void);
static NODE *func__types__some__grammar__match_6;
static void entry__types__some__grammar__match_6(void);
static FRAME_INFO frame__types__some__grammar__match_6 = {2, {"return", "len"}};
static void cont__types__some__grammar__match_7(void);
static void cont__types__some__grammar__match_8(void);
static NODE *func__types__some__grammar__match_9;
static void entry__types__some__grammar__match_9(void);
static FRAME_INFO frame__types__some__grammar__match_9 = {2, {"len", "n"}};
static void cont__types__some__grammar__match_10(void);
static NODE *func__types__some__grammar__match_11;
static void entry__types__some__grammar__match_11(void);
static FRAME_INFO frame__types__some__grammar__match_11 = {2, {"len", "n"}};
static void cont__types__some__grammar__match_12(void);
static void cont__types__some__grammar__match_13(void);
static NODE *func__types__some__grammar__match_14;
static void entry__types__some__grammar__match_14(void);
static FRAME_INFO frame__types__some__grammar__match_14 = {2, {"return", "len"}};
static void cont__types__some__grammar__match_15(void);
static void cont__types__some__grammar__match_16(void);
static void cont__types__some__grammar__match_17(void);
static void cont__types__some__grammar__match_18(void);
static void cont__types__some__grammar__match_19(void);
static NODE *func__std__some_1;
static void entry__std__some_1(void);
static FRAME_INFO frame__std__some_1 = {1, {"expr"}};
static NODE *get__std__some(void) {
  return var.std__some;
}
static NODE *get__types__alt(void) {
  return var.types__alt;
}
static NODE *func__types__alt__grammar__match_1;
static void entry__types__alt__grammar__match_1(void);
static FRAME_INFO frame__types__alt__grammar__match_1 = {4, {"self", "stream", "return", "alternatives"}};
static void cont__types__alt__grammar__match_2(void);
static NODE *func__types__alt__grammar__match_3;
static void entry__types__alt__grammar__match_3(void);
static FRAME_INFO frame__types__alt__grammar__match_3 = {4, {"alternative", "stream", "return", "n"}};
static void cont__types__alt__grammar__match_4(void);
static void cont__types__alt__grammar__match_5(void);
static NODE *func__types__alt__grammar__match_6;
static void entry__types__alt__grammar__match_6(void);
static FRAME_INFO frame__types__alt__grammar__match_6 = {2, {"return", "n"}};
static void cont__types__alt__grammar__match_7(void);
static NODE *func__std__alt_1;
static void entry__std__alt_1(void);
static FRAME_INFO frame__std__alt_1 = {1, {"alternatives"}};
static NODE *get__std__alt(void) {
  return var.std__alt;
}
static NODE *get__types__followed_by(void) {
  return var.types__followed_by;
}
static NODE *func__types__followed_by__grammar__match_1;
static void entry__types__followed_by__grammar__match_1(void);
static FRAME_INFO frame__types__followed_by__grammar__match_1 = {4, {"self", "stream", "return", "original_node"}};
static void cont__types__followed_by__grammar__match_2(void);
static void cont__types__followed_by__grammar__match_3(void);
static void cont__types__followed_by__grammar__match_4(void);
static NODE *func__types__followed_by__grammar__match_5;
static void entry__types__followed_by__grammar__match_5(void);
static FRAME_INFO frame__types__followed_by__grammar__match_5 = {2, {"original_node", "return"}};
static NODE *func__types__followed_by__grammar__match_6;
static void entry__types__followed_by__grammar__match_6(void);
static FRAME_INFO frame__types__followed_by__grammar__match_6 = {1, {"return"}};
static void cont__types__followed_by__grammar__match_7(void);
static NODE *func__std__followed_by_1;
static void entry__std__followed_by_1(void);
static FRAME_INFO frame__std__followed_by_1 = {1, {"expr"}};
static NODE *get__std__followed_by(void) {
  return var.std__followed_by;
}
static NODE *get__types__not_followed_by(void) {
  return var.types__not_followed_by;
}
static NODE *func__types__not_followed_by__grammar__match_1;
static void entry__types__not_followed_by__grammar__match_1(void);
static FRAME_INFO frame__types__not_followed_by__grammar__match_1 = {4, {"self", "stream", "return", "original_node"}};
static void cont__types__not_followed_by__grammar__match_2(void);
static void cont__types__not_followed_by__grammar__match_3(void);
static void cont__types__not_followed_by__grammar__match_4(void);
static NODE *func__types__not_followed_by__grammar__match_5;
static void entry__types__not_followed_by__grammar__match_5(void);
static FRAME_INFO frame__types__not_followed_by__grammar__match_5 = {2, {"original_node", "return"}};
static NODE *func__types__not_followed_by__grammar__match_6;
static void entry__types__not_followed_by__grammar__match_6(void);
static FRAME_INFO frame__types__not_followed_by__grammar__match_6 = {1, {"return"}};
static void cont__types__not_followed_by__grammar__match_7(void);
static NODE *func__std__not_followed_by_1;
static void entry__std__not_followed_by_1(void);
static FRAME_INFO frame__std__not_followed_by_1 = {1, {"expr"}};
static NODE *get__std__not_followed_by(void) {
  return var.std__not_followed_by;
}
static NODE *get__types__capture(void) {
  return var.types__capture;
}
static NODE *func__types__capture__grammar__match_1;
static void entry__types__capture__grammar__match_1(void);
static FRAME_INFO frame__types__capture__grammar__match_1 = {3, {"self", "stream", "len"}};
static void cont__types__capture__grammar__match_2(void);
static void cont__types__capture__grammar__match_3(void);
static void cont__types__capture__grammar__match_4(void);
static NODE *func__types__capture__grammar__match_5;
static void entry__types__capture__grammar__match_5(void);
static FRAME_INFO frame__types__capture__grammar__match_5 = {5, {"self", "stream", "len", "setter", "value"}};
static void cont__types__capture__grammar__match_6(void);
static void cont__types__capture__grammar__match_7(void);
static void cont__types__capture__grammar__match_8(void);
static NODE *func__types__capture__grammar__match_9;
static void entry__types__capture__grammar__match_9(void);
static FRAME_INFO frame__types__capture__grammar__match_9 = {2, {"setter", "value"}};
static void cont__types__capture__grammar__match_10(void);
static NODE *func__types__capture__grammar__match_11;
static void entry__types__capture__grammar__match_11(void);
static FRAME_INFO frame__types__capture__grammar__match_11 = {1, {"value"}};
static void cont__types__capture__grammar__match_12(void);
static NODE *func__std__capture_1;
static void entry__std__capture_1(void);
static FRAME_INFO frame__std__capture_1 = {2, {"setter", "expr"}};
static NODE *get__std__capture(void) {
  return var.std__capture;
}
static NODE *get__types__multi_capture(void) {
  return var.types__multi_capture;
}
static NODE *func__types__multi_capture__grammar__match_1;
static void entry__types__multi_capture__grammar__match_1(void);
static FRAME_INFO frame__types__multi_capture__grammar__match_1 = {3, {"self", "stream", "len"}};
static void cont__types__multi_capture__grammar__match_2(void);
static void cont__types__multi_capture__grammar__match_3(void);
static void cont__types__multi_capture__grammar__match_4(void);
static NODE *func__types__multi_capture__grammar__match_5;
static void entry__types__multi_capture__grammar__match_5(void);
static FRAME_INFO frame__types__multi_capture__grammar__match_5 = {5, {"self", "stream", "len", "setter", "value"}};
static void cont__types__multi_capture__grammar__match_6(void);
static void cont__types__multi_capture__grammar__match_7(void);
static void cont__types__multi_capture__grammar__match_8(void);
static NODE *func__types__multi_capture__grammar__match_9;
static void entry__types__multi_capture__grammar__match_9(void);
static FRAME_INFO frame__types__multi_capture__grammar__match_9 = {3, {"setter", "self", "value"}};
static void cont__types__multi_capture__grammar__match_10(void);
static void cont__types__multi_capture__grammar__match_11(void);
static void cont__types__multi_capture__grammar__match_12(void);
static void cont__types__multi_capture__grammar__match_13(void);
static NODE *func__types__multi_capture__grammar__match_14;
static void entry__types__multi_capture__grammar__match_14(void);
static FRAME_INFO frame__types__multi_capture__grammar__match_14 = {1, {"value"}};
static void cont__types__multi_capture__grammar__match_15(void);
static void cont__types__multi_capture__grammar__match_16(void);
static NODE *func__std__multi_capture_1;
static void entry__std__multi_capture_1(void);
static FRAME_INFO frame__std__multi_capture_1 = {2, {"setter", "expr"}};
static NODE *get__std__multi_capture(void) {
  return var.std__multi_capture;
}
static NODE *get__types__span(void) {
  return var.types__span;
}
static NODE *func__types__span__grammar__match_1;
static void entry__types__span__grammar__match_1(void);
static FRAME_INFO frame__types__span__grammar__match_1 = {5, {"self", "stream", "return", "outer_node", "len"}};
static NODE *func__types__span__grammar__match_2;
static void entry__types__span__grammar__match_2(void);
static FRAME_INFO frame__types__span__grammar__match_2 = {6, {"return__1", "len", "self", "stream", "return", "outer_node"}};
static void cont__types__span__grammar__match_3(void);
static void cont__types__span__grammar__match_4(void);
static void cont__types__span__grammar__match_5(void);
static NODE *func__types__span__grammar__match_6;
static void entry__types__span__grammar__match_6(void);
static FRAME_INFO frame__types__span__grammar__match_6 = {1, {"return"}};
static void cont__types__span__grammar__match_7(void);
static void cont__types__span__grammar__match_8(void);
static void cont__types__span__grammar__match_9(void);
static void cont__types__span__grammar__match_10(void);
static NODE *func__std__span_1;
static void entry__std__span_1(void);
static FRAME_INFO frame__std__span_1 = {2, {"setter", "expr"}};
static NODE *get__std__span(void) {
  return var.std__span;
}
static NODE *get__types__multi_span(void) {
  return var.types__multi_span;
}
static NODE *func__types__multi_span__grammar__match_1;
static void entry__types__multi_span__grammar__match_1(void);
static FRAME_INFO frame__types__multi_span__grammar__match_1 = {5, {"self", "stream", "return", "outer_node", "len"}};
static NODE *func__types__multi_span__grammar__match_2;
static void entry__types__multi_span__grammar__match_2(void);
static FRAME_INFO frame__types__multi_span__grammar__match_2 = {7, {"return__1", "len", "self", "stream", "return", "outer_node", "setter"}};
static void cont__types__multi_span__grammar__match_3(void);
static void cont__types__multi_span__grammar__match_4(void);
static void cont__types__multi_span__grammar__match_5(void);
static NODE *func__types__multi_span__grammar__match_6;
static void entry__types__multi_span__grammar__match_6(void);
static FRAME_INFO frame__types__multi_span__grammar__match_6 = {1, {"return"}};
static void cont__types__multi_span__grammar__match_7(void);
static void cont__types__multi_span__grammar__match_8(void);
static void cont__types__multi_span__grammar__match_9(void);
static NODE *func__types__multi_span__grammar__match_10;
static void entry__types__multi_span__grammar__match_10(void);
static FRAME_INFO frame__types__multi_span__grammar__match_10 = {2, {"setter", "outer_node"}};
static void cont__types__multi_span__grammar__match_11(void);
static void cont__types__multi_span__grammar__match_12(void);
static void cont__types__multi_span__grammar__match_13(void);
static NODE *func__types__multi_span__grammar__match_14;
static void entry__types__multi_span__grammar__match_14(void);
static FRAME_INFO frame__types__multi_span__grammar__match_14 = {1, {"outer_node"}};
static void cont__types__multi_span__grammar__match_15(void);
static void cont__types__multi_span__grammar__match_16(void);
static void cont__types__multi_span__grammar__match_17(void);
static NODE *func__std__multi_span_1;
static void entry__std__multi_span_1(void);
static FRAME_INFO frame__std__multi_span_1 = {2, {"setter", "expr"}};
static NODE *get__std__multi_span(void) {
  return var.std__multi_span;
}
static NODE *get__types__set_node(void) {
  return var.types__set_node;
}
static NODE *func__types__set_node__grammar__match_1;
static void entry__types__set_node__grammar__match_1(void);
static FRAME_INFO frame__types__set_node__grammar__match_1 = {2, {"self", "stream"}};
static void cont__types__set_node__grammar__match_2(void);
static NODE *func__std__set_node_1;
static void entry__std__set_node_1(void);
static FRAME_INFO frame__std__set_node_1 = {1, {"node"}};
static NODE *get__std__set_node(void) {
  return var.std__set_node;
}
static NODE *get__types__inspect_node(void) {
  return var.types__inspect_node;
}
static NODE *func__types__inspect_node__grammar__match_1;
static void entry__types__inspect_node__grammar__match_1(void);
static FRAME_INFO frame__types__inspect_node__grammar__match_1 = {3, {"self", "stream", "func"}};
static void cont__types__inspect_node__grammar__match_2(void);
static void cont__types__inspect_node__grammar__match_3(void);
static void cont__types__inspect_node__grammar__match_4(void);
static NODE *func__types__inspect_node__grammar__match_5;
static void entry__types__inspect_node__grammar__match_5(void);
static FRAME_INFO frame__types__inspect_node__grammar__match_5 = {2, {"func", "stream"}};
static NODE *func__types__inspect_node__grammar__match_6;
static void entry__types__inspect_node__grammar__match_6(void);
static FRAME_INFO frame__types__inspect_node__grammar__match_6 = {1, {"func"}};
static void cont__types__inspect_node__grammar__match_7(void);
static NODE *func__std__inspect_node_1;
static void entry__std__inspect_node_1(void);
static FRAME_INFO frame__std__inspect_node_1 = {1, {"func"}};
static NODE *get__std__inspect_node(void) {
  return var.std__inspect_node;
}
static NODE *get__types__modify_node(void) {
  return var.types__modify_node;
}
static NODE *func__types__modify_node__grammar__match_1;
static void entry__types__modify_node__grammar__match_1(void);
static FRAME_INFO frame__types__modify_node__grammar__match_1 = {3, {"self", "stream", "func"}};
static void cont__types__modify_node__grammar__match_2(void);
static void cont__types__modify_node__grammar__match_3(void);
static void cont__types__modify_node__grammar__match_4(void);
static NODE *func__types__modify_node__grammar__match_5;
static void entry__types__modify_node__grammar__match_5(void);
static FRAME_INFO frame__types__modify_node__grammar__match_5 = {2, {"func", "stream"}};
static void cont__types__modify_node__grammar__match_6(void);
static NODE *func__types__modify_node__grammar__match_7;
static void entry__types__modify_node__grammar__match_7(void);
static FRAME_INFO frame__types__modify_node__grammar__match_7 = {1, {"func"}};
static void cont__types__modify_node__grammar__match_8(void);
static void cont__types__modify_node__grammar__match_9(void);
static NODE *func__std__modify_node_1;
static void entry__std__modify_node_1(void);
static FRAME_INFO frame__std__modify_node_1 = {1, {"func"}};
static NODE *get__std__modify_node(void) {
  return var.std__modify_node;
}
static NODE *get__types__check_node(void) {
  return var.types__check_node;
}
static NODE *func__types__check_node__grammar__match_1;
static void entry__types__check_node__grammar__match_1(void);
static FRAME_INFO frame__types__check_node__grammar__match_1 = {4, {"self", "stream", "return", "func"}};
static void cont__types__check_node__grammar__match_2(void);
static void cont__types__check_node__grammar__match_3(void);
static void cont__types__check_node__grammar__match_4(void);
static NODE *func__types__check_node__grammar__match_5;
static void entry__types__check_node__grammar__match_5(void);
static FRAME_INFO frame__types__check_node__grammar__match_5 = {3, {"func", "stream", "return"}};
static void cont__types__check_node__grammar__match_6(void);
static NODE *func__types__check_node__grammar__match_7;
static void entry__types__check_node__grammar__match_7(void);
static FRAME_INFO frame__types__check_node__grammar__match_7 = {1, {"return"}};
static NODE *func__types__check_node__grammar__match_8;
static void entry__types__check_node__grammar__match_8(void);
static FRAME_INFO frame__types__check_node__grammar__match_8 = {2, {"func", "return"}};
static void cont__types__check_node__grammar__match_9(void);
static NODE *func__types__check_node__grammar__match_10;
static void entry__types__check_node__grammar__match_10(void);
static FRAME_INFO frame__types__check_node__grammar__match_10 = {1, {"return"}};
static void cont__types__check_node__grammar__match_11(void);
static NODE *func__std__check_node_1;
static void entry__std__check_node_1(void);
static FRAME_INFO frame__std__check_node_1 = {1, {"func"}};
static NODE *get__std__check_node(void) {
  return var.std__check_node;
}
static NODE *get__types__grammar_action(void) {
  return var.types__grammar_action;
}
static NODE *func__types__grammar_action__grammar__match_1;
static void entry__types__grammar_action__grammar__match_1(void);
static FRAME_INFO frame__types__grammar_action__grammar__match_1 = {2, {"self", "stream"}};
static void cont__types__grammar_action__grammar__match_2(void);
static void cont__types__grammar_action__grammar__match_3(void);
static NODE *func__std__grammar_action_1;
static void entry__std__grammar_action_1(void);
static FRAME_INFO frame__std__grammar_action_1 = {1, {"func"}};
static NODE *get__std__grammar_action(void) {
  return var.std__grammar_action;
}
static NODE *get__types__set_field(void) {
  return var.types__set_field;
}
static NODE *func__types__set_field__grammar__match_1;
static void entry__types__set_field__grammar__match_1(void);
static FRAME_INFO frame__types__set_field__grammar__match_1 = {2, {"self", "stream"}};
static void cont__types__set_field__grammar__match_2(void);
static void cont__types__set_field__grammar__match_3(void);
static void cont__types__set_field__grammar__match_4(void);
static NODE *func__std__set_field_1;
static void entry__std__set_field_1(void);
static FRAME_INFO frame__std__set_field_1 = {2, {"setter", "expr"}};
static NODE *get__std__set_field(void) {
  return var.std__set_field;
}
static NODE *get__std__END_OF_TEXT(void) {
  return var.std__END_OF_TEXT;
}
static NODE *func__std__END_OF_TEXT__grammar__match_1;
static void entry__std__END_OF_TEXT__grammar__match_1(void);
static FRAME_INFO frame__std__END_OF_TEXT__grammar__match_1 = {2, {"self", "stream"}};
static void cont__std__END_OF_TEXT__grammar__match_2(void);
static NODE *func__std__END_OF_TEXT__grammar__match_3;
static void entry__std__END_OF_TEXT__grammar__match_3(void);
static FRAME_INFO frame__std__END_OF_TEXT__grammar__match_3 = {0, {}};
static NODE *func__std__END_OF_TEXT__grammar__match_4;
static void entry__std__END_OF_TEXT__grammar__match_4(void);
static FRAME_INFO frame__std__END_OF_TEXT__grammar__match_4 = {0, {}};
static NODE *get__std__LETTER(void) {
  return var.std__LETTER;
}
static NODE *func__std__LETTER__grammar__match_1;
static void entry__std__LETTER__grammar__match_1(void);
static FRAME_INFO frame__std__LETTER__grammar__match_1 = {3, {"self", "stream", "return"}};
static void cont__std__LETTER__grammar__match_2(void);
static NODE *func__std__LETTER__grammar__match_3;
static void entry__std__LETTER__grammar__match_3(void);
static FRAME_INFO frame__std__LETTER__grammar__match_3 = {1, {"return"}};
static void cont__std__LETTER__grammar__match_4(void);
static void cont__std__LETTER__grammar__match_5(void);
static void cont__std__LETTER__grammar__match_6(void);
static void cont__std__LETTER__grammar__match_7(void);
static NODE *func__std__LETTER__grammar__match_8;
static void entry__std__LETTER__grammar__match_8(void);
static FRAME_INFO frame__std__LETTER__grammar__match_8 = {1, {"stream"}};
static void cont__std__LETTER__grammar__match_9(void);
static void cont__std__LETTER__grammar__match_10(void);
static void cont__std__LETTER__grammar__match_11(void);
static void cont__std__LETTER__grammar__match_12(void);
static NODE *func__std__LETTER__grammar__match_13;
static void entry__std__LETTER__grammar__match_13(void);
static FRAME_INFO frame__std__LETTER__grammar__match_13 = {1, {"stream"}};
static void cont__std__LETTER__grammar__match_14(void);
static void cont__std__LETTER__grammar__match_15(void);
static void cont__std__LETTER__grammar__match_16(void);
static NODE *func__std__LETTER__grammar__match_17;
static void entry__std__LETTER__grammar__match_17(void);
static FRAME_INFO frame__std__LETTER__grammar__match_17 = {1, {"stream"}};
static void cont__std__LETTER__grammar__match_18(void);
static void cont__std__LETTER__grammar__match_19(void);
static void cont__std__LETTER__grammar__match_20(void);
static void cont__std__LETTER__grammar__match_21(void);
static void cont__std__LETTER__grammar__match_22(void);
static NODE *func__std__LETTER__grammar__match_23;
static void entry__std__LETTER__grammar__match_23(void);
static FRAME_INFO frame__std__LETTER__grammar__match_23 = {1, {"return"}};
static void cont__std__LETTER__grammar__match_24(void);
static NODE *get__std__UPPER_CASE_LETTER(void) {
  return var.std__UPPER_CASE_LETTER;
}
static NODE *func__std__UPPER_CASE_LETTER__grammar__match_1;
static void entry__std__UPPER_CASE_LETTER__grammar__match_1(void);
static FRAME_INFO frame__std__UPPER_CASE_LETTER__grammar__match_1 = {3, {"self", "stream", "return"}};
static void cont__std__UPPER_CASE_LETTER__grammar__match_2(void);
static NODE *func__std__UPPER_CASE_LETTER__grammar__match_3;
static void entry__std__UPPER_CASE_LETTER__grammar__match_3(void);
static FRAME_INFO frame__std__UPPER_CASE_LETTER__grammar__match_3 = {1, {"return"}};
static void cont__std__UPPER_CASE_LETTER__grammar__match_4(void);
static void cont__std__UPPER_CASE_LETTER__grammar__match_5(void);
static void cont__std__UPPER_CASE_LETTER__grammar__match_6(void);
static void cont__std__UPPER_CASE_LETTER__grammar__match_7(void);
static NODE *func__std__UPPER_CASE_LETTER__grammar__match_8;
static void entry__std__UPPER_CASE_LETTER__grammar__match_8(void);
static FRAME_INFO frame__std__UPPER_CASE_LETTER__grammar__match_8 = {1, {"stream"}};
static void cont__std__UPPER_CASE_LETTER__grammar__match_9(void);
static void cont__std__UPPER_CASE_LETTER__grammar__match_10(void);
static void cont__std__UPPER_CASE_LETTER__grammar__match_11(void);
static void cont__std__UPPER_CASE_LETTER__grammar__match_12(void);
static NODE *func__std__UPPER_CASE_LETTER__grammar__match_13;
static void entry__std__UPPER_CASE_LETTER__grammar__match_13(void);
static FRAME_INFO frame__std__UPPER_CASE_LETTER__grammar__match_13 = {1, {"return"}};
static void cont__std__UPPER_CASE_LETTER__grammar__match_14(void);
static NODE *get__std__LOWER_CASE_LETTER(void) {
  return var.std__LOWER_CASE_LETTER;
}
static NODE *func__std__LOWER_CASE_LETTER__grammar__match_1;
static void entry__std__LOWER_CASE_LETTER__grammar__match_1(void);
static FRAME_INFO frame__std__LOWER_CASE_LETTER__grammar__match_1 = {3, {"self", "stream", "return"}};
static void cont__std__LOWER_CASE_LETTER__grammar__match_2(void);
static NODE *func__std__LOWER_CASE_LETTER__grammar__match_3;
static void entry__std__LOWER_CASE_LETTER__grammar__match_3(void);
static FRAME_INFO frame__std__LOWER_CASE_LETTER__grammar__match_3 = {1, {"return"}};
static void cont__std__LOWER_CASE_LETTER__grammar__match_4(void);
static void cont__std__LOWER_CASE_LETTER__grammar__match_5(void);
static void cont__std__LOWER_CASE_LETTER__grammar__match_6(void);
static void cont__std__LOWER_CASE_LETTER__grammar__match_7(void);
static NODE *func__std__LOWER_CASE_LETTER__grammar__match_8;
static void entry__std__LOWER_CASE_LETTER__grammar__match_8(void);
static FRAME_INFO frame__std__LOWER_CASE_LETTER__grammar__match_8 = {1, {"stream"}};
static void cont__std__LOWER_CASE_LETTER__grammar__match_9(void);
static void cont__std__LOWER_CASE_LETTER__grammar__match_10(void);
static void cont__std__LOWER_CASE_LETTER__grammar__match_11(void);
static void cont__std__LOWER_CASE_LETTER__grammar__match_12(void);
static NODE *func__std__LOWER_CASE_LETTER__grammar__match_13;
static void entry__std__LOWER_CASE_LETTER__grammar__match_13(void);
static FRAME_INFO frame__std__LOWER_CASE_LETTER__grammar__match_13 = {1, {"return"}};
static void cont__std__LOWER_CASE_LETTER__grammar__match_14(void);
static NODE *get__std__DIGIT(void) {
  return var.std__DIGIT;
}
static NODE *func__std__DIGIT__grammar__match_1;
static void entry__std__DIGIT__grammar__match_1(void);
static FRAME_INFO frame__std__DIGIT__grammar__match_1 = {3, {"self", "stream", "return"}};
static void cont__std__DIGIT__grammar__match_2(void);
static NODE *func__std__DIGIT__grammar__match_3;
static void entry__std__DIGIT__grammar__match_3(void);
static FRAME_INFO frame__std__DIGIT__grammar__match_3 = {1, {"return"}};
static void cont__std__DIGIT__grammar__match_4(void);
static void cont__std__DIGIT__grammar__match_5(void);
static void cont__std__DIGIT__grammar__match_6(void);
static void cont__std__DIGIT__grammar__match_7(void);
static NODE *func__std__DIGIT__grammar__match_8;
static void entry__std__DIGIT__grammar__match_8(void);
static FRAME_INFO frame__std__DIGIT__grammar__match_8 = {1, {"stream"}};
static void cont__std__DIGIT__grammar__match_9(void);
static void cont__std__DIGIT__grammar__match_10(void);
static void cont__std__DIGIT__grammar__match_11(void);
static void cont__std__DIGIT__grammar__match_12(void);
static NODE *func__std__DIGIT__grammar__match_13;
static void entry__std__DIGIT__grammar__match_13(void);
static FRAME_INFO frame__std__DIGIT__grammar__match_13 = {1, {"return"}};
static void cont__std__DIGIT__grammar__match_14(void);
static NODE *get__std__WHITESPACE_CHARACTER(void) {
  return var.std__WHITESPACE_CHARACTER;
}
static NODE *func__std__WHITESPACE_CHARACTER__grammar__match_1;
static void entry__std__WHITESPACE_CHARACTER__grammar__match_1(void);
static FRAME_INFO frame__std__WHITESPACE_CHARACTER__grammar__match_1 = {4, {"self", "stream", "return", "chr"}};
static void cont__std__WHITESPACE_CHARACTER__grammar__match_2(void);
static NODE *func__std__WHITESPACE_CHARACTER__grammar__match_3;
static void entry__std__WHITESPACE_CHARACTER__grammar__match_3(void);
static FRAME_INFO frame__std__WHITESPACE_CHARACTER__grammar__match_3 = {1, {"return"}};
static void cont__std__WHITESPACE_CHARACTER__grammar__match_4(void);
static void cont__std__WHITESPACE_CHARACTER__grammar__match_5(void);
static void cont__std__WHITESPACE_CHARACTER__grammar__match_6(void);
static void cont__std__WHITESPACE_CHARACTER__grammar__match_7(void);
static NODE *func__std__WHITESPACE_CHARACTER__grammar__match_8;
static void entry__std__WHITESPACE_CHARACTER__grammar__match_8(void);
static FRAME_INFO frame__std__WHITESPACE_CHARACTER__grammar__match_8 = {1, {"chr"}};
static void cont__std__WHITESPACE_CHARACTER__grammar__match_9(void);
static void cont__std__WHITESPACE_CHARACTER__grammar__match_10(void);
static NODE *func__std__WHITESPACE_CHARACTER__grammar__match_11;
static void entry__std__WHITESPACE_CHARACTER__grammar__match_11(void);
static FRAME_INFO frame__std__WHITESPACE_CHARACTER__grammar__match_11 = {1, {"return"}};
static void cont__std__WHITESPACE_CHARACTER__grammar__match_12(void);
static NODE *get__std__WHITESPACE(void) {
  return var.std__WHITESPACE;
}
static NODE *get__std__PRINTABLE_CHARACTER(void) {
  return var.std__PRINTABLE_CHARACTER;
}
static NODE *func__std__PRINTABLE_CHARACTER__grammar__match_1;
static void entry__std__PRINTABLE_CHARACTER__grammar__match_1(void);
static FRAME_INFO frame__std__PRINTABLE_CHARACTER__grammar__match_1 = {4, {"self", "stream", "return", "chr"}};
static void cont__std__PRINTABLE_CHARACTER__grammar__match_2(void);
static NODE *func__std__PRINTABLE_CHARACTER__grammar__match_3;
static void entry__std__PRINTABLE_CHARACTER__grammar__match_3(void);
static FRAME_INFO frame__std__PRINTABLE_CHARACTER__grammar__match_3 = {1, {"return"}};
static void cont__std__PRINTABLE_CHARACTER__grammar__match_4(void);
static void cont__std__PRINTABLE_CHARACTER__grammar__match_5(void);
static void cont__std__PRINTABLE_CHARACTER__grammar__match_6(void);
static void cont__std__PRINTABLE_CHARACTER__grammar__match_7(void);
static NODE *func__std__PRINTABLE_CHARACTER__grammar__match_8;
static void entry__std__PRINTABLE_CHARACTER__grammar__match_8(void);
static FRAME_INFO frame__std__PRINTABLE_CHARACTER__grammar__match_8 = {1, {"chr"}};
static void cont__std__PRINTABLE_CHARACTER__grammar__match_9(void);
static void cont__std__PRINTABLE_CHARACTER__grammar__match_10(void);
static NODE *func__std__PRINTABLE_CHARACTER__grammar__match_11;
static void entry__std__PRINTABLE_CHARACTER__grammar__match_11(void);
static FRAME_INFO frame__std__PRINTABLE_CHARACTER__grammar__match_11 = {1, {"chr"}};
static void cont__std__PRINTABLE_CHARACTER__grammar__match_12(void);
static void cont__std__PRINTABLE_CHARACTER__grammar__match_13(void);
static void cont__std__PRINTABLE_CHARACTER__grammar__match_14(void);
static NODE *func__std__PRINTABLE_CHARACTER__grammar__match_15;
static void entry__std__PRINTABLE_CHARACTER__grammar__match_15(void);
static FRAME_INFO frame__std__PRINTABLE_CHARACTER__grammar__match_15 = {1, {"return"}};
static void cont__std__PRINTABLE_CHARACTER__grammar__match_16(void);
static NODE *get__std__NON_SPACE_CHARACTER(void) {
  return var.std__NON_SPACE_CHARACTER;
}
static NODE *func__std__NON_SPACE_CHARACTER__grammar__match_1;
static void entry__std__NON_SPACE_CHARACTER__grammar__match_1(void);
static FRAME_INFO frame__std__NON_SPACE_CHARACTER__grammar__match_1 = {4, {"self", "stream", "return", "chr"}};
static void cont__std__NON_SPACE_CHARACTER__grammar__match_2(void);
static NODE *func__std__NON_SPACE_CHARACTER__grammar__match_3;
static void entry__std__NON_SPACE_CHARACTER__grammar__match_3(void);
static FRAME_INFO frame__std__NON_SPACE_CHARACTER__grammar__match_3 = {1, {"return"}};
static void cont__std__NON_SPACE_CHARACTER__grammar__match_4(void);
static void cont__std__NON_SPACE_CHARACTER__grammar__match_5(void);
static void cont__std__NON_SPACE_CHARACTER__grammar__match_6(void);
static NODE *func__std__NON_SPACE_CHARACTER__grammar__match_7;
static void entry__std__NON_SPACE_CHARACTER__grammar__match_7(void);
static FRAME_INFO frame__std__NON_SPACE_CHARACTER__grammar__match_7 = {1, {"chr"}};
static void cont__std__NON_SPACE_CHARACTER__grammar__match_8(void);
static void cont__std__NON_SPACE_CHARACTER__grammar__match_9(void);
static NODE *func__std__NON_SPACE_CHARACTER__grammar__match_10;
static void entry__std__NON_SPACE_CHARACTER__grammar__match_10(void);
static FRAME_INFO frame__std__NON_SPACE_CHARACTER__grammar__match_10 = {1, {"chr"}};
static void cont__std__NON_SPACE_CHARACTER__grammar__match_11(void);
static void cont__std__NON_SPACE_CHARACTER__grammar__match_12(void);
static void cont__std__NON_SPACE_CHARACTER__grammar__match_13(void);
static NODE *func__std__NON_SPACE_CHARACTER__grammar__match_14;
static void entry__std__NON_SPACE_CHARACTER__grammar__match_14(void);
static FRAME_INFO frame__std__NON_SPACE_CHARACTER__grammar__match_14 = {1, {"return"}};
static void cont__std__NON_SPACE_CHARACTER__grammar__match_15(void);
static NODE *get__std__ANY_CHARACTER(void) {
  return var.std__ANY_CHARACTER;
}
static NODE *func__std__ANY_CHARACTER__grammar__match_1;
static void entry__std__ANY_CHARACTER__grammar__match_1(void);
static FRAME_INFO frame__std__ANY_CHARACTER__grammar__match_1 = {3, {"self", "stream", "return"}};
static void cont__std__ANY_CHARACTER__grammar__match_2(void);
static NODE *func__std__ANY_CHARACTER__grammar__match_3;
static void entry__std__ANY_CHARACTER__grammar__match_3(void);
static FRAME_INFO frame__std__ANY_CHARACTER__grammar__match_3 = {1, {"return"}};
static void cont__std__ANY_CHARACTER__grammar__match_4(void);
static NODE *func__types__character__grammar__match_1;
static void entry__types__character__grammar__match_1(void);
static FRAME_INFO frame__types__character__grammar__match_1 = {2, {"chr", "stream"}};
static NODE *func__types__value_range__grammar__match_1;
static void entry__types__value_range__grammar__match_1(void);
static FRAME_INFO frame__types__value_range__grammar__match_1 = {4, {"self", "stream", "return", "chr"}};
static void cont__types__value_range__grammar__match_2(void);
static NODE *func__types__value_range__grammar__match_3;
static void entry__types__value_range__grammar__match_3(void);
static FRAME_INFO frame__types__value_range__grammar__match_3 = {1, {"return"}};
static void cont__types__value_range__grammar__match_4(void);
static void cont__types__value_range__grammar__match_5(void);
static void cont__types__value_range__grammar__match_6(void);
static void cont__types__value_range__grammar__match_7(void);
static void cont__types__value_range__grammar__match_8(void);
static NODE *func__types__value_range__grammar__match_9;
static void entry__types__value_range__grammar__match_9(void);
static FRAME_INFO frame__types__value_range__grammar__match_9 = {2, {"self", "chr"}};
static void cont__types__value_range__grammar__match_10(void);
static void cont__types__value_range__grammar__match_11(void);
static void cont__types__value_range__grammar__match_12(void);
static void cont__types__value_range__grammar__match_13(void);
static NODE *func__types__value_range__grammar__match_14;
static void entry__types__value_range__grammar__match_14(void);
static FRAME_INFO frame__types__value_range__grammar__match_14 = {1, {"return"}};
static void cont__types__value_range__grammar__match_15(void);
static NODE *func__types__list__grammar__match_1;
static void entry__types__list__grammar__match_1(void);
static FRAME_INFO frame__types__list__grammar__match_1 = {5, {"self", "stream", "return", "len", "original_node"}};
static NODE *func__types__list__grammar__match_2;
static void entry__types__list__grammar__match_2(void);
static FRAME_INFO frame__types__list__grammar__match_2 = {6, {"expr", "stream", "original_node", "return", "len", "n"}};
static void cont__types__list__grammar__match_3(void);
static void cont__types__list__grammar__match_4(void);
static NODE *func__types__list__grammar__match_5;
static void entry__types__list__grammar__match_5(void);
static FRAME_INFO frame__types__list__grammar__match_5 = {2, {"original_node", "return"}};
static void cont__types__list__grammar__match_6(void);
static void cont__types__list__grammar__match_7(void);
static void cont__types__list__grammar__match_8(void);
static void cont__types__list__grammar__match_9(void);
static void cont__types__list__grammar__match_10(void);
static void cont__types__list__grammar__match_11(void);
static NODE *func__types__object__grammar__search_1;
static void entry__types__object__grammar__search_1(void);
static FRAME_INFO frame__types__object__grammar__search_1 = {6, {"expr", "stream", "nth", "return", "pos", "s"}};
static void cont__types__object__grammar__search_2(void);
static NODE *func__types__object__grammar__search_3;
static void entry__types__object__grammar__search_3(void);
static FRAME_INFO frame__types__object__grammar__search_3 = {5, {"expr", "s", "nth", "return", "pos"}};
static NODE *func__types__object__grammar__search_4;
static void entry__types__object__grammar__search_4(void);
static FRAME_INFO frame__types__object__grammar__search_4 = {6, {"expr", "s", "nth", "return", "pos", "len"}};
static void cont__types__object__grammar__search_5(void);
static void cont__types__object__grammar__search_6(void);
static NODE *func__types__object__grammar__search_7;
static void entry__types__object__grammar__search_7(void);
static FRAME_INFO frame__types__object__grammar__search_7 = {5, {"nth", "return", "pos", "len", "s"}};
static void cont__types__object__grammar__search_8(void);
static NODE *func__types__object__grammar__search_9;
static void entry__types__object__grammar__search_9(void);
static FRAME_INFO frame__types__object__grammar__search_9 = {3, {"return", "pos", "len"}};
static void cont__types__object__grammar__search_10(void);
static void cont__types__object__grammar__search_11(void);
static NODE *func__types__object__grammar__search_12;
static void entry__types__object__grammar__search_12(void);
static FRAME_INFO frame__types__object__grammar__search_12 = {3, {"pos", "len", "s"}};
static void cont__types__object__grammar__search_13(void);
static void cont__types__object__grammar__search_14(void);
static void cont__types__object__grammar__search_15(void);
static void cont__types__object__grammar__search_16(void);
static void cont__types__object__grammar__search_17(void);
static void cont__types__object__grammar__search_18(void);
static void cont__types__object__grammar__search_19(void);
static void cont__types__object__grammar__search_20(void);
static NODE *func__types__object__grammar__search_21;
static void entry__types__object__grammar__search_21(void);
static FRAME_INFO frame__types__object__grammar__search_21 = {1, {"return"}};
static void cont__types__object__grammar__search_22(void);
static void cont__types__object__grammar__search_23(void);
static void cont__types__object__grammar__search_24(void);
static void cont__types__object__grammar__search_25(void);
static NODE *func__types__object__grammar__search_26;
static void entry__types__object__grammar__search_26(void);
static FRAME_INFO frame__types__object__grammar__search_26 = {7, {"nth", "expr", "s", "pos", "return", "positions", "lengths"}};
static void cont__types__object__grammar__search_27(void);
static NODE *func__types__object__grammar__search_28;
static void entry__types__object__grammar__search_28(void);
static FRAME_INFO frame__types__object__grammar__search_28 = {8, {"expr", "s", "positions", "nth", "lengths", "pos", "return", "len"}};
static void cont__types__object__grammar__search_29(void);
static void cont__types__object__grammar__search_30(void);
static NODE *func__types__object__grammar__search_31;
static void entry__types__object__grammar__search_31(void);
static FRAME_INFO frame__types__object__grammar__search_31 = {6, {"positions", "nth", "lengths", "pos", "len", "s"}};
static void cont__types__object__grammar__search_32(void);
static void cont__types__object__grammar__search_33(void);
static void cont__types__object__grammar__search_34(void);
static NODE *func__types__object__grammar__search_35;
static void entry__types__object__grammar__search_35(void);
static FRAME_INFO frame__types__object__grammar__search_35 = {2, {"positions", "lengths"}};
static void cont__types__object__grammar__search_36(void);
static void cont__types__object__grammar__search_37(void);
static void cont__types__object__grammar__search_38(void);
static void cont__types__object__grammar__search_39(void);
static void cont__types__object__grammar__search_40(void);
static void cont__types__object__grammar__search_41(void);
static void cont__types__object__grammar__search_42(void);
static void cont__types__object__grammar__search_43(void);
static NODE *func__types__object__grammar__search_44;
static void entry__types__object__grammar__search_44(void);
static FRAME_INFO frame__types__object__grammar__search_44 = {3, {"pos", "len", "s"}};
static void cont__types__object__grammar__search_45(void);
static void cont__types__object__grammar__search_46(void);
static void cont__types__object__grammar__search_47(void);
static void cont__types__object__grammar__search_48(void);
static void cont__types__object__grammar__search_49(void);
static void cont__types__object__grammar__search_50(void);
static NODE *func__types__object__grammar__search_51;
static void entry__types__object__grammar__search_51(void);
static FRAME_INFO frame__types__object__grammar__search_51 = {4, {"positions", "nth", "return", "lengths"}};
static void cont__types__object__grammar__search_52(void);
static void cont__types__object__grammar__search_53(void);
static NODE *func__types__object__grammar__search_54;
static void entry__types__object__grammar__search_54(void);
static FRAME_INFO frame__types__object__grammar__search_54 = {1, {"return"}};
static void cont__types__object__grammar__search_55(void);
static void cont__types__object__grammar__search_56(void);
static void cont__types__object__grammar__search_57(void);
static void cont__types__object__grammar__search_58(void);
static void cont__types__object__grammar__search_59(void);
static void cont__types__object__grammar__search_60(void);
static void cont__types__object__grammar__search_61(void);
static void cont__types__object__grammar__search_62(void);
static void cont__152_1(void);
void run__basic__grammar(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__grammar__match, NULL, 25, 25, 2, 15},
  {type__grammar__search, NULL, 31, 31, 2, 16},
  {type__expr_of, NULL, 55, 55, 2, 8},
  {type__alternatives_of, NULL, 56, 56, 2, 16},
  {type__setter_of, NULL, 57, 57, 2, 10},
  {type__node_of, NULL, 58, 58, 2, 8},
  {type__function_of, NULL, 59, 59, 2, 12},
  {run__basic__grammar, NULL, 793, 797, 1, 19},
  {cont__152_1, NULL, },
  {entry__types__optional__grammar__match_1, NULL, 77, 77, 21, 33},
  {cont__types__optional__grammar__match_2, &frame__types__optional__grammar__match_1, 77, 77, 6, 41},
  {cont__types__optional__grammar__match_3, &frame__types__optional__grammar__match_1, 77, 77, 6, 59},
  {cont__types__optional__grammar__match_4, &frame__types__optional__grammar__match_1, 77, 77, 3, 59},
  {entry__std__optional_1, NULL, 89, 89, 3, 35},
  {entry__types__many__grammar__match_6, NULL, 109, 109, 26, 35},
  {entry__types__many__grammar__match_9, NULL, 112, 112, 9, 19},
  {cont__types__many__grammar__match_10, &frame__types__many__grammar__match_9, 112, 112, 19, 19},
  {entry__types__many__grammar__match_11, NULL, 114, 114, 14, 14},
  {entry__types__many__grammar__match_14, NULL, 115, 115, 16, 25},
  {entry__types__many__grammar__match_2, NULL, 108, 108, 23, 35},
  {cont__types__many__grammar__match_3, &frame__types__many__grammar__match_2, 108, 108, 5, 43},
  {cont__types__many__grammar__match_4, &frame__types__many__grammar__match_2, 109, 109, 12, 23},
  {cont__types__many__grammar__match_5, &frame__types__many__grammar__match_2, 109, 109, 5, 35},
  {cont__types__many__grammar__match_7, &frame__types__many__grammar__match_2, 111, 111, 7, 20},
  {cont__types__many__grammar__match_8, &frame__types__many__grammar__match_2, 110, 114, 5, 15},
  {cont__types__many__grammar__match_12, &frame__types__many__grammar__match_2, 115, 115, 8, 13},
  {cont__types__many__grammar__match_13, &frame__types__many__grammar__match_2, 115, 115, 5, 25},
  {cont__types__many__grammar__match_15, &frame__types__many__grammar__match_2, 116, 116, 19, 21},
  {cont__types__many__grammar__match_16, &frame__types__many__grammar__match_2, 116, 116, 24, 24},
  {cont__types__many__grammar__match_17, &frame__types__many__grammar__match_2, 116, 116, 5, 24},
  {cont__types__many__grammar__match_18, &frame__types__many__grammar__match_2, 116, 116, 24, 24},
  {entry__types__many__grammar__match_1, NULL, 107, 116, 3, 24},
  {cont__types__many__grammar__match_19, &frame__types__many__grammar__match_1, 116, 116, 24, 24},
  {entry__std__many_1, NULL, 128, 128, 3, 31},
  {entry__types__some__grammar__match_6, NULL, 150, 150, 26, 35},
  {entry__types__some__grammar__match_9, NULL, 153, 153, 9, 19},
  {cont__types__some__grammar__match_10, &frame__types__some__grammar__match_9, 153, 153, 19, 19},
  {entry__types__some__grammar__match_11, NULL, 155, 155, 14, 14},
  {entry__types__some__grammar__match_14, NULL, 156, 156, 16, 25},
  {entry__types__some__grammar__match_2, NULL, 149, 149, 23, 35},
  {cont__types__some__grammar__match_3, &frame__types__some__grammar__match_2, 149, 149, 5, 43},
  {cont__types__some__grammar__match_4, &frame__types__some__grammar__match_2, 150, 150, 12, 23},
  {cont__types__some__grammar__match_5, &frame__types__some__grammar__match_2, 150, 150, 5, 35},
  {cont__types__some__grammar__match_7, &frame__types__some__grammar__match_2, 152, 152, 7, 20},
  {cont__types__some__grammar__match_8, &frame__types__some__grammar__match_2, 151, 155, 5, 15},
  {cont__types__some__grammar__match_12, &frame__types__some__grammar__match_2, 156, 156, 8, 13},
  {cont__types__some__grammar__match_13, &frame__types__some__grammar__match_2, 156, 156, 5, 25},
  {cont__types__some__grammar__match_15, &frame__types__some__grammar__match_2, 157, 157, 19, 21},
  {cont__types__some__grammar__match_16, &frame__types__some__grammar__match_2, 157, 157, 24, 24},
  {cont__types__some__grammar__match_17, &frame__types__some__grammar__match_2, 157, 157, 5, 24},
  {cont__types__some__grammar__match_18, &frame__types__some__grammar__match_2, 157, 157, 24, 24},
  {entry__types__some__grammar__match_1, NULL, 148, 157, 3, 24},
  {cont__types__some__grammar__match_19, &frame__types__some__grammar__match_1, 157, 157, 24, 24},
  {entry__std__some_1, NULL, 169, 169, 3, 31},
  {entry__types__alt__grammar__match_6, NULL, 191, 191, 22, 29},
  {entry__types__alt__grammar__match_3, NULL, 190, 190, 5, 41},
  {cont__types__alt__grammar__match_4, &frame__types__alt__grammar__match_3, 191, 191, 8, 19},
  {cont__types__alt__grammar__match_5, &frame__types__alt__grammar__match_3, 191, 191, 5, 29},
  {entry__types__alt__grammar__match_1, NULL, 188, 188, 3, 37},
  {cont__types__alt__grammar__match_2, &frame__types__alt__grammar__match_1, 189, 191, 3, 29},
  {cont__types__alt__grammar__match_7, &frame__types__alt__grammar__match_1, 192, 192, 3, 14},
  {entry__std__alt_1, NULL, 200, 200, 3, 46},
  {entry__types__followed_by__grammar__match_5, NULL, 223, 223, 7, 14},
  {entry__types__followed_by__grammar__match_6, NULL, 225, 225, 7, 22},
  {entry__types__followed_by__grammar__match_1, NULL, 221, 221, 20, 32},
  {cont__types__followed_by__grammar__match_2, &frame__types__followed_by__grammar__match_1, 221, 221, 5, 40},
  {cont__types__followed_by__grammar__match_3, &frame__types__followed_by__grammar__match_1, 221, 221, 5, 51},
  {cont__types__followed_by__grammar__match_4, &frame__types__followed_by__grammar__match_1, 220, 225, 3, 23},
  {cont__types__followed_by__grammar__match_7, &frame__types__followed_by__grammar__match_1, 225, 225, 23, 23},
  {entry__std__followed_by_1, NULL, 240, 240, 3, 38},
  {entry__types__not_followed_by__grammar__match_5, NULL, 263, 263, 7, 22},
  {entry__types__not_followed_by__grammar__match_6, NULL, 265, 265, 7, 14},
  {entry__types__not_followed_by__grammar__match_1, NULL, 261, 261, 20, 32},
  {cont__types__not_followed_by__grammar__match_2, &frame__types__not_followed_by__grammar__match_1, 261, 261, 5, 40},
  {cont__types__not_followed_by__grammar__match_3, &frame__types__not_followed_by__grammar__match_1, 261, 261, 5, 51},
  {cont__types__not_followed_by__grammar__match_4, &frame__types__not_followed_by__grammar__match_1, 260, 265, 3, 15},
  {cont__types__not_followed_by__grammar__match_7, &frame__types__not_followed_by__grammar__match_1, 265, 265, 15, 15},
  {entry__std__not_followed_by_1, NULL, 280, 280, 3, 42},
  {entry__types__capture__grammar__match_9, NULL, 304, 304, 9, 43},
  {cont__types__capture__grammar__match_10, &frame__types__capture__grammar__match_9, 304, 304, 43, 43},
  {entry__types__capture__grammar__match_11, NULL, 306, 306, 36, 36},
  {entry__types__capture__grammar__match_5, NULL, 300, 300, 5, 27},
  {cont__types__capture__grammar__match_6, &frame__types__capture__grammar__match_5, 301, 301, 5, 30},
  {cont__types__capture__grammar__match_7, &frame__types__capture__grammar__match_5, 303, 303, 7, 23},
  {cont__types__capture__grammar__match_8, &frame__types__capture__grammar__match_5, 302, 306, 5, 37},
  {entry__types__capture__grammar__match_1, NULL, 298, 298, 23, 35},
  {cont__types__capture__grammar__match_2, &frame__types__capture__grammar__match_1, 298, 298, 3, 43},
  {cont__types__capture__grammar__match_3, &frame__types__capture__grammar__match_1, 299, 299, 6, 19},
  {cont__types__capture__grammar__match_4, &frame__types__capture__grammar__match_1, 299, 306, 3, 38},
  {cont__types__capture__grammar__match_12, &frame__types__capture__grammar__match_1, 307, 307, 3, 8},
  {entry__std__capture_1, NULL, 320, 320, 3, 52},
  {entry__types__multi_capture__grammar__match_9, NULL, 346, 346, 16, 30},
  {cont__types__multi_capture__grammar__match_10, &frame__types__multi_capture__grammar__match_9, 346, 346, 16, 53},
  {cont__types__multi_capture__grammar__match_11, &frame__types__multi_capture__grammar__match_9, 346, 346, 11, 60},
  {cont__types__multi_capture__grammar__match_12, &frame__types__multi_capture__grammar__match_9, 344, 346, 9, 60},
  {cont__types__multi_capture__grammar__match_13, &frame__types__multi_capture__grammar__match_9, 346, 346, 61, 61},
  {entry__types__multi_capture__grammar__match_14, NULL, 348, 348, 9, 41},
  {cont__types__multi_capture__grammar__match_15, &frame__types__multi_capture__grammar__match_14, 348, 348, 41, 41},
  {entry__types__multi_capture__grammar__match_5, NULL, 340, 340, 5, 27},
  {cont__types__multi_capture__grammar__match_6, &frame__types__multi_capture__grammar__match_5, 341, 341, 5, 30},
  {cont__types__multi_capture__grammar__match_7, &frame__types__multi_capture__grammar__match_5, 343, 343, 7, 23},
  {cont__types__multi_capture__grammar__match_8, &frame__types__multi_capture__grammar__match_5, 342, 348, 5, 42},
  {entry__types__multi_capture__grammar__match_1, NULL, 338, 338, 23, 35},
  {cont__types__multi_capture__grammar__match_2, &frame__types__multi_capture__grammar__match_1, 338, 338, 3, 43},
  {cont__types__multi_capture__grammar__match_3, &frame__types__multi_capture__grammar__match_1, 339, 339, 6, 19},
  {cont__types__multi_capture__grammar__match_4, &frame__types__multi_capture__grammar__match_1, 339, 348, 3, 43},
  {cont__types__multi_capture__grammar__match_16, &frame__types__multi_capture__grammar__match_1, 349, 349, 3, 8},
  {entry__std__multi_capture_1, NULL, 367, 367, 3, 58},
  {entry__types__span__grammar__match_6, NULL, 391, 391, 28, 43},
  {entry__types__span__grammar__match_2, NULL, 390, 390, 25, 37},
  {cont__types__span__grammar__match_3, &frame__types__span__grammar__match_2, 390, 390, 5, 45},
  {cont__types__span__grammar__match_4, &frame__types__span__grammar__match_2, 391, 391, 12, 25},
  {cont__types__span__grammar__match_5, &frame__types__span__grammar__match_2, 391, 391, 5, 43},
  {cont__types__span__grammar__match_7, &frame__types__span__grammar__match_2, 392, 392, 5, 19},
  {cont__types__span__grammar__match_8, &frame__types__span__grammar__match_2, 392, 392, 5, 53},
  {cont__types__span__grammar__match_9, &frame__types__span__grammar__match_2, },
  {entry__types__span__grammar__match_1, NULL, 388, 392, 3, 53},
  {cont__types__span__grammar__match_10, &frame__types__span__grammar__match_1, 394, 394, 3, 8},
  {entry__std__span_1, NULL, 409, 409, 3, 49},
  {entry__types__multi_span__grammar__match_6, NULL, 433, 433, 28, 43},
  {entry__types__multi_span__grammar__match_10, NULL, 437, 437, 33, 50},
  {cont__types__multi_span__grammar__match_11, &frame__types__multi_span__grammar__match_10, 437, 437, 28, 73},
  {cont__types__multi_span__grammar__match_12, &frame__types__multi_span__grammar__match_10, 437, 437, 9, 73},
  {cont__types__multi_span__grammar__match_13, &frame__types__multi_span__grammar__match_10, 437, 437, 73, 73},
  {entry__types__multi_span__grammar__match_14, NULL, 439, 439, 9, 46},
  {cont__types__multi_span__grammar__match_15, &frame__types__multi_span__grammar__match_14, 439, 439, 46, 46},
  {entry__types__multi_span__grammar__match_2, NULL, 432, 432, 25, 37},
  {cont__types__multi_span__grammar__match_3, &frame__types__multi_span__grammar__match_2, 432, 432, 5, 45},
  {cont__types__multi_span__grammar__match_4, &frame__types__multi_span__grammar__match_2, 433, 433, 12, 25},
  {cont__types__multi_span__grammar__match_5, &frame__types__multi_span__grammar__match_2, 433, 433, 5, 43},
  {cont__types__multi_span__grammar__match_7, &frame__types__multi_span__grammar__match_2, 434, 434, 5, 27},
  {cont__types__multi_span__grammar__match_8, &frame__types__multi_span__grammar__match_2, 436, 436, 7, 23},
  {cont__types__multi_span__grammar__match_9, &frame__types__multi_span__grammar__match_2, 435, 439, 5, 47},
  {cont__types__multi_span__grammar__match_16, &frame__types__multi_span__grammar__match_2, 439, 439, 47, 47},
  {entry__types__multi_span__grammar__match_1, NULL, 430, 439, 3, 48},
  {cont__types__multi_span__grammar__match_17, &frame__types__multi_span__grammar__match_1, 441, 441, 3, 8},
  {entry__std__multi_span_1, NULL, 461, 461, 3, 55},
  {entry__types__set_node__grammar__match_1, NULL, 479, 479, 3, 38},
  {cont__types__set_node__grammar__match_2, &frame__types__set_node__grammar__match_1, 480, 480, 3, 6},
  {entry__std__set_node_1, NULL, 488, 488, 3, 35},
  {entry__types__inspect_node__grammar__match_5, NULL, 509, 509, 7, 39},
  {entry__types__inspect_node__grammar__match_6, NULL, 511, 511, 7, 32},
  {entry__types__inspect_node__grammar__match_1, NULL, 506, 506, 3, 25},
  {cont__types__inspect_node__grammar__match_2, &frame__types__inspect_node__grammar__match_1, 508, 508, 5, 28},
  {cont__types__inspect_node__grammar__match_3, &frame__types__inspect_node__grammar__match_1, 508, 508, 5, 33},
  {cont__types__inspect_node__grammar__match_4, &frame__types__inspect_node__grammar__match_1, 507, 511, 3, 33},
  {cont__types__inspect_node__grammar__match_7, &frame__types__inspect_node__grammar__match_1, 512, 512, 3, 6},
  {entry__std__inspect_node_1, NULL, 524, 524, 3, 43},
  {entry__types__modify_node__grammar__match_5, NULL, 545, 545, 7, 40},
  {cont__types__modify_node__grammar__match_6, &frame__types__modify_node__grammar__match_5, 545, 545, 40, 40},
  {entry__types__modify_node__grammar__match_7, NULL, 547, 547, 7, 33},
  {cont__types__modify_node__grammar__match_8, &frame__types__modify_node__grammar__match_7, 547, 547, 33, 33},
  {entry__types__modify_node__grammar__match_1, NULL, 542, 542, 3, 25},
  {cont__types__modify_node__grammar__match_2, &frame__types__modify_node__grammar__match_1, 544, 544, 5, 28},
  {cont__types__modify_node__grammar__match_3, &frame__types__modify_node__grammar__match_1, 544, 544, 5, 33},
  {cont__types__modify_node__grammar__match_4, &frame__types__modify_node__grammar__match_1, 543, 547, 3, 34},
  {cont__types__modify_node__grammar__match_9, &frame__types__modify_node__grammar__match_1, 548, 548, 3, 6},
  {entry__std__modify_node_1, NULL, 560, 560, 3, 42},
  {entry__types__check_node__grammar__match_7, NULL, 582, 582, 50, 65},
  {entry__types__check_node__grammar__match_5, NULL, 582, 582, 14, 47},
  {cont__types__check_node__grammar__match_6, &frame__types__check_node__grammar__match_5, 582, 582, 7, 65},
  {entry__types__check_node__grammar__match_10, NULL, 584, 584, 43, 58},
  {entry__types__check_node__grammar__match_8, NULL, 584, 584, 14, 40},
  {cont__types__check_node__grammar__match_9, &frame__types__check_node__grammar__match_8, 584, 584, 7, 58},
  {entry__types__check_node__grammar__match_1, NULL, 579, 579, 3, 25},
  {cont__types__check_node__grammar__match_2, &frame__types__check_node__grammar__match_1, 581, 581, 5, 28},
  {cont__types__check_node__grammar__match_3, &frame__types__check_node__grammar__match_1, 581, 581, 5, 33},
  {cont__types__check_node__grammar__match_4, &frame__types__check_node__grammar__match_1, 580, 584, 3, 59},
  {cont__types__check_node__grammar__match_11, &frame__types__check_node__grammar__match_1, 585, 585, 3, 6},
  {entry__std__check_node_1, NULL, 597, 597, 3, 41},
  {entry__types__grammar_action__grammar__match_1, NULL, 613, 613, 6, 22},
  {cont__types__grammar_action__grammar__match_2, &frame__types__grammar_action__grammar__match_1, 613, 613, 6, 30},
  {cont__types__grammar_action__grammar__match_3, &frame__types__grammar_action__grammar__match_1, 613, 613, 3, 30},
  {entry__std__grammar_action_1, NULL, 626, 626, 3, 45},
  {entry__types__set_field__grammar__match_1, NULL, 644, 644, 42, 54},
  {cont__types__set_field__grammar__match_2, &frame__types__set_field__grammar__match_1, 644, 644, 3, 17},
  {cont__types__set_field__grammar__match_3, &frame__types__set_field__grammar__match_1, 644, 644, 3, 54},
  {cont__types__set_field__grammar__match_4, &frame__types__set_field__grammar__match_1, 645, 645, 3, 6},
  {entry__std__set_field_1, NULL, 658, 658, 3, 54},
  {entry__std__END_OF_TEXT__grammar__match_3, NULL, 678, 678, 5, 16},
  {entry__std__END_OF_TEXT__grammar__match_4, NULL, 679, 679, 5, 8},
  {entry__std__END_OF_TEXT__grammar__match_1, NULL, 677, 677, 5, 33},
  {cont__std__END_OF_TEXT__grammar__match_2, &frame__std__END_OF_TEXT__grammar__match_1, 676, 679, 3, 8},
  {entry__std__LETTER__grammar__match_3, NULL, 698, 698, 41, 56},
  {entry__std__LETTER__grammar__match_8, NULL, 700, 700, 25, 33},
  {cont__std__LETTER__grammar__match_9, &frame__std__LETTER__grammar__match_8, 700, 700, 25, 40},
  {cont__std__LETTER__grammar__match_10, &frame__std__LETTER__grammar__match_8, 700, 700, 25, 40},
  {cont__std__LETTER__grammar__match_11, &frame__std__LETTER__grammar__match_8, 700, 700, 25, 40},
  {entry__std__LETTER__grammar__match_17, NULL, 700, 700, 65, 73},
  {cont__std__LETTER__grammar__match_18, &frame__std__LETTER__grammar__match_17, 700, 700, 65, 80},
  {cont__std__LETTER__grammar__match_19, &frame__std__LETTER__grammar__match_17, 700, 700, 65, 80},
  {cont__std__LETTER__grammar__match_20, &frame__std__LETTER__grammar__match_17, 700, 700, 65, 80},
  {entry__std__LETTER__grammar__match_13, NULL, 700, 700, 45, 53},
  {cont__std__LETTER__grammar__match_14, &frame__std__LETTER__grammar__match_13, 700, 700, 45, 60},
  {cont__std__LETTER__grammar__match_15, &frame__std__LETTER__grammar__match_13, 700, 700, 45, 60},
  {cont__std__LETTER__grammar__match_16, &frame__std__LETTER__grammar__match_13, 700, 700, 45, 80},
  {cont__std__LETTER__grammar__match_21, &frame__std__LETTER__grammar__match_13, 700, 700, 45, 80},
  {entry__std__LETTER__grammar__match_23, NULL, 702, 702, 7, 14},
  {entry__std__LETTER__grammar__match_1, NULL, 698, 698, 10, 38},
  {cont__std__LETTER__grammar__match_2, &frame__std__LETTER__grammar__match_1, 698, 698, 3, 56},
  {cont__std__LETTER__grammar__match_4, &frame__std__LETTER__grammar__match_1, 700, 700, 5, 13},
  {cont__std__LETTER__grammar__match_5, &frame__std__LETTER__grammar__match_1, 700, 700, 5, 20},
  {cont__std__LETTER__grammar__match_6, &frame__std__LETTER__grammar__match_1, 700, 700, 5, 20},
  {cont__std__LETTER__grammar__match_7, &frame__std__LETTER__grammar__match_1, 700, 700, 5, 40},
  {cont__std__LETTER__grammar__match_12, &frame__std__LETTER__grammar__match_1, 700, 700, 5, 80},
  {cont__std__LETTER__grammar__match_22, &frame__std__LETTER__grammar__match_1, 699, 702, 3, 15},
  {cont__std__LETTER__grammar__match_24, &frame__std__LETTER__grammar__match_1, 703, 703, 3, 14},
  {entry__std__UPPER_CASE_LETTER__grammar__match_3, NULL, 722, 722, 41, 56},
  {entry__std__UPPER_CASE_LETTER__grammar__match_8, NULL, 723, 723, 26, 34},
  {cont__std__UPPER_CASE_LETTER__grammar__match_9, &frame__std__UPPER_CASE_LETTER__grammar__match_8, 723, 723, 26, 41},
  {cont__std__UPPER_CASE_LETTER__grammar__match_10, &frame__std__UPPER_CASE_LETTER__grammar__match_8, 723, 723, 26, 41},
  {cont__std__UPPER_CASE_LETTER__grammar__match_11, &frame__std__UPPER_CASE_LETTER__grammar__match_8, 723, 723, 26, 41},
  {entry__std__UPPER_CASE_LETTER__grammar__match_13, NULL, 723, 723, 44, 51},
  {entry__std__UPPER_CASE_LETTER__grammar__match_1, NULL, 722, 722, 10, 38},
  {cont__std__UPPER_CASE_LETTER__grammar__match_2, &frame__std__UPPER_CASE_LETTER__grammar__match_1, 722, 722, 3, 56},
  {cont__std__UPPER_CASE_LETTER__grammar__match_4, &frame__std__UPPER_CASE_LETTER__grammar__match_1, 723, 723, 6, 14},
  {cont__std__UPPER_CASE_LETTER__grammar__match_5, &frame__std__UPPER_CASE_LETTER__grammar__match_1, 723, 723, 6, 21},
  {cont__std__UPPER_CASE_LETTER__grammar__match_6, &frame__std__UPPER_CASE_LETTER__grammar__match_1, 723, 723, 6, 21},
  {cont__std__UPPER_CASE_LETTER__grammar__match_7, &frame__std__UPPER_CASE_LETTER__grammar__match_1, 723, 723, 6, 41},
  {cont__std__UPPER_CASE_LETTER__grammar__match_12, &frame__std__UPPER_CASE_LETTER__grammar__match_1, 723, 723, 3, 51},
  {cont__std__UPPER_CASE_LETTER__grammar__match_14, &frame__std__UPPER_CASE_LETTER__grammar__match_1, 724, 724, 3, 14},
  {entry__std__LOWER_CASE_LETTER__grammar__match_3, NULL, 743, 743, 41, 56},
  {entry__std__LOWER_CASE_LETTER__grammar__match_8, NULL, 744, 744, 26, 34},
  {cont__std__LOWER_CASE_LETTER__grammar__match_9, &frame__std__LOWER_CASE_LETTER__grammar__match_8, 744, 744, 26, 41},
  {cont__std__LOWER_CASE_LETTER__grammar__match_10, &frame__std__LOWER_CASE_LETTER__grammar__match_8, 744, 744, 26, 41},
  {cont__std__LOWER_CASE_LETTER__grammar__match_11, &frame__std__LOWER_CASE_LETTER__grammar__match_8, 744, 744, 26, 41},
  {entry__std__LOWER_CASE_LETTER__grammar__match_13, NULL, 744, 744, 44, 51},
  {entry__std__LOWER_CASE_LETTER__grammar__match_1, NULL, 743, 743, 10, 38},
  {cont__std__LOWER_CASE_LETTER__grammar__match_2, &frame__std__LOWER_CASE_LETTER__grammar__match_1, 743, 743, 3, 56},
  {cont__std__LOWER_CASE_LETTER__grammar__match_4, &frame__std__LOWER_CASE_LETTER__grammar__match_1, 744, 744, 6, 14},
  {cont__std__LOWER_CASE_LETTER__grammar__match_5, &frame__std__LOWER_CASE_LETTER__grammar__match_1, 744, 744, 6, 21},
  {cont__std__LOWER_CASE_LETTER__grammar__match_6, &frame__std__LOWER_CASE_LETTER__grammar__match_1, 744, 744, 6, 21},
  {cont__std__LOWER_CASE_LETTER__grammar__match_7, &frame__std__LOWER_CASE_LETTER__grammar__match_1, 744, 744, 6, 41},
  {cont__std__LOWER_CASE_LETTER__grammar__match_12, &frame__std__LOWER_CASE_LETTER__grammar__match_1, 744, 744, 3, 51},
  {cont__std__LOWER_CASE_LETTER__grammar__match_14, &frame__std__LOWER_CASE_LETTER__grammar__match_1, 745, 745, 3, 14},
  {entry__std__DIGIT__grammar__match_3, NULL, 764, 764, 41, 56},
  {entry__std__DIGIT__grammar__match_8, NULL, 765, 765, 26, 34},
  {cont__std__DIGIT__grammar__match_9, &frame__std__DIGIT__grammar__match_8, 765, 765, 26, 41},
  {cont__std__DIGIT__grammar__match_10, &frame__std__DIGIT__grammar__match_8, 765, 765, 26, 41},
  {cont__std__DIGIT__grammar__match_11, &frame__std__DIGIT__grammar__match_8, 765, 765, 26, 41},
  {entry__std__DIGIT__grammar__match_13, NULL, 765, 765, 44, 51},
  {entry__std__DIGIT__grammar__match_1, NULL, 764, 764, 10, 38},
  {cont__std__DIGIT__grammar__match_2, &frame__std__DIGIT__grammar__match_1, 764, 764, 3, 56},
  {cont__std__DIGIT__grammar__match_4, &frame__std__DIGIT__grammar__match_1, 765, 765, 6, 14},
  {cont__std__DIGIT__grammar__match_5, &frame__std__DIGIT__grammar__match_1, 765, 765, 6, 21},
  {cont__std__DIGIT__grammar__match_6, &frame__std__DIGIT__grammar__match_1, 765, 765, 6, 21},
  {cont__std__DIGIT__grammar__match_7, &frame__std__DIGIT__grammar__match_1, 765, 765, 6, 41},
  {cont__std__DIGIT__grammar__match_12, &frame__std__DIGIT__grammar__match_1, 765, 765, 3, 51},
  {cont__std__DIGIT__grammar__match_14, &frame__std__DIGIT__grammar__match_1, 766, 766, 3, 14},
  {entry__std__WHITESPACE_CHARACTER__grammar__match_3, NULL, 785, 785, 41, 56},
  {entry__std__WHITESPACE_CHARACTER__grammar__match_8, NULL, 787, 787, 20, 33},
  {cont__std__WHITESPACE_CHARACTER__grammar__match_9, &frame__std__WHITESPACE_CHARACTER__grammar__match_8, 787, 787, 20, 33},
  {entry__std__WHITESPACE_CHARACTER__grammar__match_11, NULL, 787, 787, 36, 43},
  {entry__std__WHITESPACE_CHARACTER__grammar__match_1, NULL, 785, 785, 10, 38},
  {cont__std__WHITESPACE_CHARACTER__grammar__match_2, &frame__std__WHITESPACE_CHARACTER__grammar__match_1, 785, 785, 3, 56},
  {cont__std__WHITESPACE_CHARACTER__grammar__match_4, &frame__std__WHITESPACE_CHARACTER__grammar__match_1, 786, 786, 3, 16},
  {cont__std__WHITESPACE_CHARACTER__grammar__match_5, &frame__std__WHITESPACE_CHARACTER__grammar__match_1, 787, 787, 6, 15},
  {cont__std__WHITESPACE_CHARACTER__grammar__match_6, &frame__std__WHITESPACE_CHARACTER__grammar__match_1, 787, 787, 6, 15},
  {cont__std__WHITESPACE_CHARACTER__grammar__match_7, &frame__std__WHITESPACE_CHARACTER__grammar__match_1, 787, 787, 6, 33},
  {cont__std__WHITESPACE_CHARACTER__grammar__match_10, &frame__std__WHITESPACE_CHARACTER__grammar__match_1, 787, 787, 3, 43},
  {cont__std__WHITESPACE_CHARACTER__grammar__match_12, &frame__std__WHITESPACE_CHARACTER__grammar__match_1, 788, 788, 3, 14},
  {entry__std__PRINTABLE_CHARACTER__grammar__match_3, NULL, 816, 816, 41, 56},
  {entry__std__PRINTABLE_CHARACTER__grammar__match_8, NULL, 818, 818, 20, 32},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_9, &frame__std__PRINTABLE_CHARACTER__grammar__match_8, 818, 818, 20, 32},
  {entry__std__PRINTABLE_CHARACTER__grammar__match_11, NULL, 818, 818, 37, 51},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_12, &frame__std__PRINTABLE_CHARACTER__grammar__match_11, 818, 818, 37, 51},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_13, &frame__std__PRINTABLE_CHARACTER__grammar__match_11, 818, 818, 37, 51},
  {entry__std__PRINTABLE_CHARACTER__grammar__match_15, NULL, 818, 818, 54, 61},
  {entry__std__PRINTABLE_CHARACTER__grammar__match_1, NULL, 816, 816, 10, 38},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_2, &frame__std__PRINTABLE_CHARACTER__grammar__match_1, 816, 816, 3, 56},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_4, &frame__std__PRINTABLE_CHARACTER__grammar__match_1, 817, 817, 3, 16},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_5, &frame__std__PRINTABLE_CHARACTER__grammar__match_1, 818, 818, 6, 15},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_6, &frame__std__PRINTABLE_CHARACTER__grammar__match_1, 818, 818, 6, 15},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_7, &frame__std__PRINTABLE_CHARACTER__grammar__match_1, 818, 818, 6, 32},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_10, &frame__std__PRINTABLE_CHARACTER__grammar__match_1, 818, 818, 6, 51},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_14, &frame__std__PRINTABLE_CHARACTER__grammar__match_1, 818, 818, 3, 61},
  {cont__std__PRINTABLE_CHARACTER__grammar__match_16, &frame__std__PRINTABLE_CHARACTER__grammar__match_1, 819, 819, 3, 14},
  {entry__std__NON_SPACE_CHARACTER__grammar__match_3, NULL, 838, 838, 41, 56},
  {entry__std__NON_SPACE_CHARACTER__grammar__match_7, NULL, 840, 840, 19, 31},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_8, &frame__std__NON_SPACE_CHARACTER__grammar__match_7, 840, 840, 19, 31},
  {entry__std__NON_SPACE_CHARACTER__grammar__match_10, NULL, 840, 840, 36, 50},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_11, &frame__std__NON_SPACE_CHARACTER__grammar__match_10, 840, 840, 36, 50},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_12, &frame__std__NON_SPACE_CHARACTER__grammar__match_10, 840, 840, 36, 50},
  {entry__std__NON_SPACE_CHARACTER__grammar__match_14, NULL, 840, 840, 53, 60},
  {entry__std__NON_SPACE_CHARACTER__grammar__match_1, NULL, 838, 838, 10, 38},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_2, &frame__std__NON_SPACE_CHARACTER__grammar__match_1, 838, 838, 3, 56},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_4, &frame__std__NON_SPACE_CHARACTER__grammar__match_1, 839, 839, 3, 16},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_5, &frame__std__NON_SPACE_CHARACTER__grammar__match_1, 840, 840, 6, 14},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_6, &frame__std__NON_SPACE_CHARACTER__grammar__match_1, 840, 840, 6, 31},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_9, &frame__std__NON_SPACE_CHARACTER__grammar__match_1, 840, 840, 6, 50},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_13, &frame__std__NON_SPACE_CHARACTER__grammar__match_1, 840, 840, 3, 60},
  {cont__std__NON_SPACE_CHARACTER__grammar__match_15, &frame__std__NON_SPACE_CHARACTER__grammar__match_1, 841, 841, 3, 14},
  {entry__std__ANY_CHARACTER__grammar__match_3, NULL, 860, 860, 41, 56},
  {entry__std__ANY_CHARACTER__grammar__match_1, NULL, 860, 860, 10, 38},
  {cont__std__ANY_CHARACTER__grammar__match_2, &frame__std__ANY_CHARACTER__grammar__match_1, 860, 860, 3, 56},
  {cont__std__ANY_CHARACTER__grammar__match_4, &frame__std__ANY_CHARACTER__grammar__match_1, 861, 861, 3, 6},
  {entry__types__character__grammar__match_1, NULL, 875, 875, 3, 28},
  {entry__types__value_range__grammar__match_3, NULL, 890, 890, 41, 56},
  {entry__types__value_range__grammar__match_9, NULL, 892, 892, 44, 63},
  {cont__types__value_range__grammar__match_10, &frame__types__value_range__grammar__match_9, 892, 892, 37, 63},
  {cont__types__value_range__grammar__match_11, &frame__types__value_range__grammar__match_9, 892, 892, 37, 63},
  {cont__types__value_range__grammar__match_12, &frame__types__value_range__grammar__match_9, 892, 892, 37, 63},
  {entry__types__value_range__grammar__match_14, NULL, 892, 892, 66, 73},
  {entry__types__value_range__grammar__match_1, NULL, 890, 890, 10, 38},
  {cont__types__value_range__grammar__match_2, &frame__types__value_range__grammar__match_1, 890, 890, 3, 56},
  {cont__types__value_range__grammar__match_4, &frame__types__value_range__grammar__match_1, 891, 891, 3, 16},
  {cont__types__value_range__grammar__match_5, &frame__types__value_range__grammar__match_1, 892, 892, 13, 32},
  {cont__types__value_range__grammar__match_6, &frame__types__value_range__grammar__match_1, 892, 892, 6, 32},
  {cont__types__value_range__grammar__match_7, &frame__types__value_range__grammar__match_1, 892, 892, 6, 32},
  {cont__types__value_range__grammar__match_8, &frame__types__value_range__grammar__match_1, 892, 892, 6, 63},
  {cont__types__value_range__grammar__match_13, &frame__types__value_range__grammar__match_1, 892, 892, 3, 73},
  {cont__types__value_range__grammar__match_15, &frame__types__value_range__grammar__match_1, 893, 893, 3, 14},
  {entry__types__list__grammar__match_5, NULL, 915, 915, 7, 22},
  {entry__types__list__grammar__match_2, NULL, 912, 912, 5, 34},
  {cont__types__list__grammar__match_3, &frame__types__list__grammar__match_2, 913, 913, 12, 23},
  {cont__types__list__grammar__match_4, &frame__types__list__grammar__match_2, 913, 915, 5, 22},
  {cont__types__list__grammar__match_6, &frame__types__list__grammar__match_2, 916, 916, 19, 21},
  {cont__types__list__grammar__match_7, &frame__types__list__grammar__match_2, 916, 916, 24, 24},
  {cont__types__list__grammar__match_8, &frame__types__list__grammar__match_2, 916, 916, 5, 24},
  {cont__types__list__grammar__match_9, &frame__types__list__grammar__match_2, 917, 917, 5, 15},
  {cont__types__list__grammar__match_10, &frame__types__list__grammar__match_2, 917, 917, 15, 15},
  {entry__types__list__grammar__match_1, NULL, 911, 917, 3, 15},
  {cont__types__list__grammar__match_11, &frame__types__list__grammar__match_1, 918, 918, 3, 8},
  {entry__types__object__grammar__search_9, NULL, 938, 938, 24, 37},
  {entry__types__object__grammar__search_12, NULL, 940, 940, 23, 27},
  {cont__types__object__grammar__search_13, &frame__types__object__grammar__search_12, 940, 940, 13, 27},
  {cont__types__object__grammar__search_14, &frame__types__object__grammar__search_12, 941, 941, 27, 27},
  {cont__types__object__grammar__search_15, &frame__types__object__grammar__search_12, 941, 941, 13, 27},
  {cont__types__object__grammar__search_16, &frame__types__object__grammar__search_12, 941, 941, 27, 27},
  {entry__types__object__grammar__search_7, NULL, 938, 938, 14, 21},
  {cont__types__object__grammar__search_8, &frame__types__object__grammar__search_7, 938, 938, 11, 37},
  {cont__types__object__grammar__search_10, &frame__types__object__grammar__search_7, 939, 939, 14, 20},
  {cont__types__object__grammar__search_11, &frame__types__object__grammar__search_7, 939, 941, 11, 27},
  {cont__types__object__grammar__search_17, &frame__types__object__grammar__search_7, 942, 942, 11, 22},
  {cont__types__object__grammar__search_18, &frame__types__object__grammar__search_7, 942, 942, 22, 22},
  {entry__types__object__grammar__search_21, NULL, 943, 943, 42, 67},
  {entry__types__object__grammar__search_4, NULL, 936, 936, 9, 35},
  {cont__types__object__grammar__search_5, &frame__types__object__grammar__search_4, 937, 937, 12, 25},
  {cont__types__object__grammar__search_6, &frame__types__object__grammar__search_4, 937, 942, 9, 22},
  {cont__types__object__grammar__search_19, &frame__types__object__grammar__search_4, 943, 943, 16, 39},
  {cont__types__object__grammar__search_20, &frame__types__object__grammar__search_4, 943, 943, 9, 67},
  {cont__types__object__grammar__search_22, &frame__types__object__grammar__search_4, 944, 944, 9, 19},
  {cont__types__object__grammar__search_23, &frame__types__object__grammar__search_4, 945, 945, 21, 21},
  {cont__types__object__grammar__search_24, &frame__types__object__grammar__search_4, 945, 945, 9, 21},
  {cont__types__object__grammar__search_25, &frame__types__object__grammar__search_4, 945, 945, 21, 21},
  {entry__types__object__grammar__search_3, NULL, 935, 945, 7, 21},
  {entry__types__object__grammar__search_35, NULL, 954, 954, 33, 33},
  {cont__types__object__grammar__search_36, &frame__types__object__grammar__search_35, 954, 954, 13, 33},
  {cont__types__object__grammar__search_37, &frame__types__object__grammar__search_35, 955, 955, 31, 31},
  {cont__types__object__grammar__search_38, &frame__types__object__grammar__search_35, 955, 955, 13, 31},
  {cont__types__object__grammar__search_39, &frame__types__object__grammar__search_35, 955, 955, 31, 31},
  {entry__types__object__grammar__search_44, NULL, 959, 959, 23, 27},
  {cont__types__object__grammar__search_45, &frame__types__object__grammar__search_44, 959, 959, 13, 27},
  {cont__types__object__grammar__search_46, &frame__types__object__grammar__search_44, 960, 960, 27, 27},
  {cont__types__object__grammar__search_47, &frame__types__object__grammar__search_44, 960, 960, 13, 27},
  {cont__types__object__grammar__search_48, &frame__types__object__grammar__search_44, 960, 960, 27, 27},
  {entry__types__object__grammar__search_31, NULL, 953, 953, 14, 33},
  {cont__types__object__grammar__search_32, &frame__types__object__grammar__search_31, 953, 953, 14, 40},
  {cont__types__object__grammar__search_33, &frame__types__object__grammar__search_31, 953, 953, 14, 40},
  {cont__types__object__grammar__search_34, &frame__types__object__grammar__search_31, 953, 955, 11, 31},
  {cont__types__object__grammar__search_40, &frame__types__object__grammar__search_31, 956, 956, 11, 29},
  {cont__types__object__grammar__search_41, &frame__types__object__grammar__search_31, 957, 957, 11, 27},
  {cont__types__object__grammar__search_42, &frame__types__object__grammar__search_31, 958, 958, 14, 20},
  {cont__types__object__grammar__search_43, &frame__types__object__grammar__search_31, 958, 960, 11, 27},
  {entry__types__object__grammar__search_54, NULL, 962, 962, 42, 67},
  {entry__types__object__grammar__search_51, NULL, 962, 962, 14, 33},
  {cont__types__object__grammar__search_52, &frame__types__object__grammar__search_51, 962, 962, 14, 39},
  {cont__types__object__grammar__search_53, &frame__types__object__grammar__search_51, 962, 962, 11, 67},
  {cont__types__object__grammar__search_55, &frame__types__object__grammar__search_51, 963, 963, 18, 29},
  {cont__types__object__grammar__search_56, &frame__types__object__grammar__search_51, 963, 963, 31, 40},
  {cont__types__object__grammar__search_57, &frame__types__object__grammar__search_51, 963, 963, 11, 40},
  {entry__types__object__grammar__search_28, NULL, 951, 951, 9, 35},
  {cont__types__object__grammar__search_29, &frame__types__object__grammar__search_28, 952, 952, 12, 25},
  {cont__types__object__grammar__search_30, &frame__types__object__grammar__search_28, 952, 960, 9, 28},
  {cont__types__object__grammar__search_49, &frame__types__object__grammar__search_28, 961, 961, 16, 39},
  {cont__types__object__grammar__search_50, &frame__types__object__grammar__search_28, 961, 963, 9, 40},
  {cont__types__object__grammar__search_58, &frame__types__object__grammar__search_28, 964, 964, 9, 19},
  {cont__types__object__grammar__search_59, &frame__types__object__grammar__search_28, 965, 965, 21, 21},
  {cont__types__object__grammar__search_60, &frame__types__object__grammar__search_28, 965, 965, 9, 21},
  {cont__types__object__grammar__search_61, &frame__types__object__grammar__search_28, 965, 965, 21, 21},
  {entry__types__object__grammar__search_26, NULL, 947, 947, 7, 17},
  {cont__types__object__grammar__search_27, &frame__types__object__grammar__search_26, 950, 965, 7, 21},
  {entry__types__object__grammar__search_1, NULL, 934, 934, 5, 11},
  {cont__types__object__grammar__search_2, &frame__types__object__grammar__search_1, 933, 965, 3, 23},
  {cont__types__object__grammar__search_62, &frame__types__object__grammar__search_1, 965, 965, 23, 23}
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  // 37: $types::grammar_object types::object
  // 38:   #
  // 39:     the prototype for all grammar objects
  // 40:     
  // 41:     Topic: Grammar
  initialize_maybe_future(var.types__grammar_object, get__types__object());
  // 43: $types::grammar_node types::object
  // 44:   #
  // 45:     the prototype for nodes of the asyntax tree
  // 46:     
  // 47:     Topic: Grammar
  initialize_maybe_future(var.types__grammar_node, get__types__object());
  // 49: %%grammar::current_node undefined
  // 50:   #
  // 51:     the current node of the syntax tree
  // 52:     
  // 53:     Topic: Grammar
  set__grammar__current_node(get__undefined());
  // 793: $std::WHITESPACE many(WHITESPACE_CHARACTER)
  // 794:   #
  // 795:     matches one or more whitespace characters
  // 796:     
  // 797:     Topic: Grammar
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
static void entry__types__optional__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 77: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__optional__grammar__match_2;
}
static void cont__types__optional__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 77: ... grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__optional__grammar__match_3;
}
static void cont__types__optional__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 77: ... grammar::match(expr_of(self) stream) .default_value. 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__types__optional__grammar__match_4;
}
static void cont__types__optional__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 77: -> grammar::match(expr_of(self) stream) .default_value. 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__optional_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 89: ... types::optional(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__optional);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 89: -> types::optional(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__many__grammar__match_1(void) {
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
  // 106: $$len undefined
  ((CELL *)frame->slots[3])->contents /* len */ = get__undefined();
  // 107: ... :
  // 108:   $n grammar::match(expr_of(self) stream)
  // 109:   unless n.is_defined: return len
  // 110:   if
  // 111:     len.is_defined:
  // 112:       plus &len n
  // 113:     :
  // 114:       !len n
  // 115:   if n == 0: return len
  // 116:   range &stream n+1 -1
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__many__grammar__match_2, 0);
  // 107: forever:
  // 108:   $n grammar::match(expr_of(self) stream)
  // 109:   unless n.is_defined: return len
  // 110:   if
  // 111:     len.is_defined:
  // 112:       plus &len n
  // 113:     :
  // 114:       !len n
  // 115:   if n == 0: return len
  // 116:   range &stream n+1 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_19;
}
static void entry__types__many__grammar__match_2(void) {
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
  // 108: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_3;
}
static void cont__types__many__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 108: $n grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_4;
}
static void cont__types__many__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* n */, arguments->slots[0]);
  // 109: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_5;
}
static void cont__types__many__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 109: ... : return len
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__many__grammar__match_6, 0);
  // 109: unless n.is_defined: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_7;
}
static void entry__types__many__grammar__match_6(void) {
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
  // 109: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__many__grammar__match_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 111: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_8;
}
static void cont__types__many__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 111: ... :
  // 112:   plus &len n
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__many__grammar__match_9, 0);
  // 113: :
  // 114:   !len n
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__many__grammar__match_11, 0);
  // 110: if
  // 111:   len.is_defined:
  // 112:     plus &len n
  // 113:   :
  // 114:     !len n
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_12;
}
static void entry__types__many__grammar__match_9(void) {
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
  // 112: plus &len n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_10;
}
static void cont__types__many__grammar__match_10(void) {
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
static void entry__types__many__grammar__match_11(void) {
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
  // 114: !len n
  ((CELL *)frame->slots[0])->contents /* len */ = frame->slots[1] /* n */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__many__grammar__match_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 115: ... n == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_13;
}
static void cont__types__many__grammar__match_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 115: ... : return len
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__many__grammar__match_14, 0);
  // 115: if n == 0: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_15;
}
static void entry__types__many__grammar__match_14(void) {
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
  // 115: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__many__grammar__match_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 116: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_16;
}
static void cont__types__many__grammar__match_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 116: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_17;
}
static void cont__types__many__grammar__match_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 116: range &stream n+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* stream */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__many__grammar__match_18;
}
static void cont__types__many__grammar__match_18(void) {
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
static void cont__types__many__grammar__match_19(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__many_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 128: ... types::many(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__many);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 128: -> types::many(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__some__grammar__match_1(void) {
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
  // 147: $$len 0
  ((CELL *)frame->slots[3])->contents /* len */ = number__0;
  // 148: ... :
  // 149:   $n grammar::match(expr_of(self) stream)
  // 150:   unless n.is_defined: return len
  // 151:   if
  // 152:     len.is_defined:
  // 153:       plus &len n
  // 154:     :
  // 155:       !len n
  // 156:   if n == 0: return len
  // 157:   range &stream n+1 -1
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__some__grammar__match_2, 0);
  // 148: forever:
  // 149:   $n grammar::match(expr_of(self) stream)
  // 150:   unless n.is_defined: return len
  // 151:   if
  // 152:     len.is_defined:
  // 153:       plus &len n
  // 154:     :
  // 155:       !len n
  // 156:   if n == 0: return len
  // 157:   range &stream n+1 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_19;
}
static void entry__types__some__grammar__match_2(void) {
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
  // 149: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_3;
}
static void cont__types__some__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 149: $n grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_4;
}
static void cont__types__some__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* n */, arguments->slots[0]);
  // 150: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_5;
}
static void cont__types__some__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 150: ... : return len
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__some__grammar__match_6, 0);
  // 150: unless n.is_defined: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_7;
}
static void entry__types__some__grammar__match_6(void) {
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
  // 150: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__some__grammar__match_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 152: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_8;
}
static void cont__types__some__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 152: ... :
  // 153:   plus &len n
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__some__grammar__match_9, 0);
  // 154: :
  // 155:   !len n
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__some__grammar__match_11, 0);
  // 151: if
  // 152:   len.is_defined:
  // 153:     plus &len n
  // 154:   :
  // 155:     !len n
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_12;
}
static void entry__types__some__grammar__match_9(void) {
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
  // 153: plus &len n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* len */;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_10;
}
static void cont__types__some__grammar__match_10(void) {
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
static void entry__types__some__grammar__match_11(void) {
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
  // 155: !len n
  ((CELL *)frame->slots[0])->contents /* len */ = frame->slots[1] /* n */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__some__grammar__match_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 156: ... n == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_13;
}
static void cont__types__some__grammar__match_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 156: ... : return len
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__some__grammar__match_14, 0);
  // 156: if n == 0: return len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_15;
}
static void entry__types__some__grammar__match_14(void) {
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
  // 156: ... return len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__some__grammar__match_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 157: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_16;
}
static void cont__types__some__grammar__match_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 157: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_17;
}
static void cont__types__some__grammar__match_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 157: range &stream n+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* stream */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__some__grammar__match_18;
}
static void cont__types__some__grammar__match_18(void) {
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
static void cont__types__some__grammar__match_19(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__some_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 169: ... types::some(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__some);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 169: -> types::some(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__alt__grammar__match_1(void) {
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
  // 188: $alternatives alternatives_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._alternatives_of;
  func = myself->type;
  frame->cont = cont__types__alt__grammar__match_2;
}
static void cont__types__alt__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* alternatives */, arguments->slots[0]);
  // 189: ... : (alternative)
  // 190:   $n grammar::match(alternative stream)
  // 191:   if n.is_defined: return n
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__alt__grammar__match_3, 1);
  // 189: for_each alternatives: (alternative)
  // 190:   $n grammar::match(alternative stream)
  // 191:   if n.is_defined: return n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* alternatives */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__alt__grammar__match_7;
}
static void entry__types__alt__grammar__match_6(void) {
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
  // 191: ... return n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__alt__grammar__match_3(void) {
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
  // 190: $n grammar::match(alternative stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alternative */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__alt__grammar__match_4;
}
static void cont__types__alt__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 191: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__alt__grammar__match_5;
}
static void cont__types__alt__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 191: ... : return n
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__alt__grammar__match_6, 0);
  // 191: if n.is_defined: return n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__alt__grammar__match_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 192: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__alt_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // alternatives: 0
  frame->slots[0] /* alternatives */ = from_arguments(0, argument_count-0);
  // 200: ... types::alt(.alternatives_of alternatives)
  {
    NODE *temp = clone_object_and_attributes(var.types__alt);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__alternatives_of, frame->slots[0] /* alternatives */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 200: -> types::alt(.alternatives_of alternatives)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__followed_by__grammar__match_1(void) {
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
  // 219: $original_node grammar::current_node
  initialize_future(frame->slots[3] /* original_node */, get__grammar__current_node());
  // 221: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__followed_by__grammar__match_2;
}
static void cont__types__followed_by__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 221: grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__followed_by__grammar__match_3;
}
static void cont__types__followed_by__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 221: grammar::match(expr_of(self) stream).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__followed_by__grammar__match_4;
}
static void cont__types__followed_by__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 221: ... :
  // 222:   !grammar::current_node original_node
  // 223:   return 0
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__followed_by__grammar__match_5, 0);
  // 224: :
  // 225:   return undefined
  frame->slots[8] /* temp__5 */ = create_closure(entry__types__followed_by__grammar__match_6, 0);
  // 220: if
  // 221:   grammar::match(expr_of(self) stream).is_defined:
  // 222:     !grammar::current_node original_node
  // 223:     return 0
  // 224:   :
  // 225:     return undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__followed_by__grammar__match_7;
}
static void entry__types__followed_by__grammar__match_5(void) {
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
  // 222: !grammar::current_node original_node
  set__grammar__current_node(frame->slots[0] /* original_node */);
  // 223: return 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__followed_by__grammar__match_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 225: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__followed_by__grammar__match_7(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__followed_by_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 240: ... types::followed_by(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__followed_by);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 240: -> types::followed_by(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__not_followed_by__grammar__match_1(void) {
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
  // 259: $original_node grammar::current_node
  initialize_future(frame->slots[3] /* original_node */, get__grammar__current_node());
  // 261: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__not_followed_by__grammar__match_2;
}
static void cont__types__not_followed_by__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 261: grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__not_followed_by__grammar__match_3;
}
static void cont__types__not_followed_by__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 261: grammar::match(expr_of(self) stream).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__not_followed_by__grammar__match_4;
}
static void cont__types__not_followed_by__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 261: ... :
  // 262:   !grammar::current_node original_node
  // 263:   return undefined
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__not_followed_by__grammar__match_5, 0);
  // 264: :
  // 265:   return 0
  frame->slots[8] /* temp__5 */ = create_closure(entry__types__not_followed_by__grammar__match_6, 0);
  // 260: if
  // 261:   grammar::match(expr_of(self) stream).is_defined:
  // 262:     !grammar::current_node original_node
  // 263:     return undefined
  // 264:   :
  // 265:     return 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__not_followed_by__grammar__match_7;
}
static void entry__types__not_followed_by__grammar__match_5(void) {
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
  // 262: !grammar::current_node original_node
  set__grammar__current_node(frame->slots[0] /* original_node */);
  // 263: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__not_followed_by__grammar__match_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 265: return 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__not_followed_by__grammar__match_7(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__not_followed_by_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 280: ... types::not_followed_by(.expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__not_followed_by);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[0] /* expr */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 280: -> types::not_followed_by(.expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__capture__grammar__match_1(void) {
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
  // 298: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__capture__grammar__match_2;
}
static void cont__types__capture__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 298: $len grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__capture__grammar__match_3;
}
static void cont__types__capture__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* len */, arguments->slots[0]);
  // 299: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__capture__grammar__match_4;
}
static void cont__types__capture__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 299: ... :
  // 300:   $setter setter_of(self)
  // 301:   $value range(stream 1 len)
  // 302:   if
  // 303:     setter.is_defined:
  // 304:       setter &grammar::current_node value
  // 305:     :
  // 306:       !grammar::current_node value
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__capture__grammar__match_5, 0);
  // 299: if len.is_defined:
  // 300:   $setter setter_of(self)
  // 301:   $value range(stream 1 len)
  // 302:   if
  // 303:     setter.is_defined:
  // 304:       setter &grammar::current_node value
  // 305:     :
  // 306:       !grammar::current_node value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__capture__grammar__match_12;
}
static void entry__types__capture__grammar__match_9(void) {
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
  // 304: setter &grammar::current_node value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[1] /* value */;
  result_count = 1;
  myself = frame->slots[0] /* setter */;
  func = myself->type;
  frame->cont = cont__types__capture__grammar__match_10;
}
static void cont__types__capture__grammar__match_10(void) {
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
static void entry__types__capture__grammar__match_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: !grammar::current_node value
  set__grammar__current_node(frame->slots[0] /* value */);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__capture__grammar__match_5(void) {
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
  // 300: $setter setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__types__capture__grammar__match_6;
}
static void cont__types__capture__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* setter */, arguments->slots[0]);
  // 301: $value range(stream 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__capture__grammar__match_7;
}
static void cont__types__capture__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* value */, arguments->slots[0]);
  // 303: setter.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* setter */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__capture__grammar__match_8;
}
static void cont__types__capture__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 303: ... :
  // 304:   setter &grammar::current_node value
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__capture__grammar__match_9, 0);
  // 305: :
  // 306:   !grammar::current_node value
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__capture__grammar__match_11, 0);
  // 302: if
  // 303:   setter.is_defined:
  // 304:     setter &grammar::current_node value
  // 305:   :
  // 306:     !grammar::current_node value
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
static void cont__types__capture__grammar__match_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 307: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__capture_1(void) {
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
  // 320: ... types::capture(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__capture);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 320: -> types::capture(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__multi_capture__grammar__match_1(void) {
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
  // 338: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_2;
}
static void cont__types__multi_capture__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 338: $len grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_3;
}
static void cont__types__multi_capture__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* len */, arguments->slots[0]);
  // 339: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_4;
}
static void cont__types__multi_capture__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 339: ... :
  // 340:   $setter setter_of(self)
  // 341:   $value range(stream 1 len)
  // 342:   if
  // 343:     setter.is_defined:
  // 344:       setter
  // 345:         &grammar::current_node
  // 346:         push(setter_of(self)(grammar::current_node) value)
  // 347:     :
  // 348:       push &grammar::current_node value
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__multi_capture__grammar__match_5, 0);
  // 339: if len.is_defined:
  // 340:   $setter setter_of(self)
  // 341:   $value range(stream 1 len)
  // 342:   if
  // 343:     setter.is_defined:
  // 344:       setter
  // 345:         &grammar::current_node
  // 346:         push(setter_of(self)(grammar::current_node) value)
  // 347:     :
  // 348:       push &grammar::current_node value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_16;
}
static void entry__types__multi_capture__grammar__match_9(void) {
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
  // 346: ... setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_10;
}
static void cont__types__multi_capture__grammar__match_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 346: ... setter_of(self)(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_11;
}
static void cont__types__multi_capture__grammar__match_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 346: push(setter_of(self)(grammar::current_node) value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* value */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_12;
}
static void cont__types__multi_capture__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 344: setter
  // 345:   &grammar::current_node
  // 346:   push(setter_of(self)(grammar::current_node) value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[0] /* setter */;
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_13;
}
static void cont__types__multi_capture__grammar__match_13(void) {
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
static void entry__types__multi_capture__grammar__match_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 348: push &grammar::current_node value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_15;
}
static void cont__types__multi_capture__grammar__match_15(void) {
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
static void entry__types__multi_capture__grammar__match_5(void) {
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
  // 340: $setter setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_6;
}
static void cont__types__multi_capture__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* setter */, arguments->slots[0]);
  // 341: $value range(stream 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_7;
}
static void cont__types__multi_capture__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* value */, arguments->slots[0]);
  // 343: setter.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* setter */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__multi_capture__grammar__match_8;
}
static void cont__types__multi_capture__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 343: ... :
  // 344:   setter
  // 345:     &grammar::current_node
  // 346:     push(setter_of(self)(grammar::current_node) value)
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__multi_capture__grammar__match_9, 0);
  // 347: :
  // 348:   push &grammar::current_node value
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__multi_capture__grammar__match_14, 0);
  // 342: if
  // 343:   setter.is_defined:
  // 344:     setter
  // 345:       &grammar::current_node
  // 346:       push(setter_of(self)(grammar::current_node) value)
  // 347:   :
  // 348:     push &grammar::current_node value
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
static void cont__types__multi_capture__grammar__match_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 349: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__multi_capture_1(void) {
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
  // 367: ... types::multi_capture(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__multi_capture);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 367: -> types::multi_capture(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__span__grammar__match_1(void) {
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
  // 386: $$outer_node grammar::current_node
  ((CELL *)frame->slots[3])->contents /* outer_node */ = get__grammar__current_node();
  // 387: $$len undefined
  ((CELL *)frame->slots[4])->contents /* len */ = get__undefined();
  // 388: ... :
  // 389:   %%grammar::current_node types::grammar_node
  // 390:   !len grammar::match(expr_of(self) stream)
  // 391:   unless len.is_defined: return undefined
  // 392:   setter_of(self) &outer_node grammar::current_node
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__span__grammar__match_2, 0);
  // 388: do:
  // 389:   %%grammar::current_node types::grammar_node
  // 390:   !len grammar::match(expr_of(self) stream)
  // 391:   unless len.is_defined: return undefined
  // 392:   setter_of(self) &outer_node grammar::current_node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__types__span__grammar__match_10;
}
static void entry__types__span__grammar__match_2(void) {
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
  // 389: %%grammar::current_node types::grammar_node
  set__grammar__current_node(var.types__grammar_node);
  // 390: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__span__grammar__match_3;
}
static void cont__types__span__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 390: !len grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__span__grammar__match_4;
}
static void cont__types__span__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* len */ = arguments->slots[0];
  // 391: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__span__grammar__match_5;
}
static void cont__types__span__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 391: ... : return undefined
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__span__grammar__match_6, 0);
  // 391: unless len.is_defined: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__span__grammar__match_7;
}
static void entry__types__span__grammar__match_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 391: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__span__grammar__match_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 392: setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__types__span__grammar__match_8;
}
static void cont__types__span__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 392: setter_of(self) &outer_node grammar::current_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* outer_node */;
  arguments->slots[1] = get__grammar__current_node();
  result_count = 1;
  myself = frame->slots[6] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__types__span__grammar__match_9;
}
static void cont__types__span__grammar__match_9(void) {
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
static void cont__types__span__grammar__match_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 393: !grammar::current_node outer_node
  set__grammar__current_node(((CELL *)frame->slots[3])->contents /* outer_node */);
  // 394: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* len */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__span_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // setter: 0
  // expr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 409: ... types::span(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__span);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 409: -> types::span(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__multi_span__grammar__match_1(void) {
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
  // 428: $$outer_node grammar::current_node
  ((CELL *)frame->slots[3])->contents /* outer_node */ = get__grammar__current_node();
  // 429: $$len undefined
  ((CELL *)frame->slots[4])->contents /* len */ = get__undefined();
  // 430: ... :
  // 431:   %%grammar::current_node types::grammar_node
  // 432:   !len grammar::match(expr_of(self) stream)
  // 433:   unless len.is_defined: return undefined
  // 434:   $setter setter_of(self)
  // 435:   if
  // 436:     setter.is_defined:
  // 437:       setter &outer_node push(setter(outer_node) grammar::current_node)
  // 438:     :
  // 439:       push &outer_node grammar::current_node
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__multi_span__grammar__match_2, 0);
  // 430: do:
  // 431:   %%grammar::current_node types::grammar_node
  // 432:   !len grammar::match(expr_of(self) stream)
  // 433:   unless len.is_defined: return undefined
  // 434:   $setter setter_of(self)
  // 435:   if
  // 436:     setter.is_defined:
  // 437:       setter &outer_node push(setter(outer_node) grammar::current_node)
  // 438:     :
  // 439:       push &outer_node grammar::current_node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_17;
}
static void entry__types__multi_span__grammar__match_2(void) {
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
  // 431: %%grammar::current_node types::grammar_node
  set__grammar__current_node(var.types__grammar_node);
  // 432: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_3;
}
static void cont__types__multi_span__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 432: !len grammar::match(expr_of(self) stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_4;
}
static void cont__types__multi_span__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* len */ = arguments->slots[0];
  // 433: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_5;
}
static void cont__types__multi_span__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 433: ... : return undefined
  frame->slots[8] /* temp__2 */ = create_closure(entry__types__multi_span__grammar__match_6, 0);
  // 433: unless len.is_defined: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_7;
}
static void entry__types__multi_span__grammar__match_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 433: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__multi_span__grammar__match_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 434: $setter setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_8;
}
static void cont__types__multi_span__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* setter */, arguments->slots[0]);
  // 436: setter.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* setter */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_9;
}
static void cont__types__multi_span__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 436: ... :
  // 437:   setter &outer_node push(setter(outer_node) grammar::current_node)
  frame->slots[8] /* temp__2 */ = create_closure(entry__types__multi_span__grammar__match_10, 0);
  // 438: :
  // 439:   push &outer_node grammar::current_node
  frame->slots[9] /* temp__3 */ = create_closure(entry__types__multi_span__grammar__match_14, 0);
  // 435: if
  // 436:   setter.is_defined:
  // 437:     setter &outer_node push(setter(outer_node) grammar::current_node)
  // 438:   :
  // 439:     push &outer_node grammar::current_node
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_16;
}
static void entry__types__multi_span__grammar__match_10(void) {
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
  // 437: ... setter(outer_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* outer_node */;
  result_count = 1;
  myself = frame->slots[0] /* setter */;
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_11;
}
static void cont__types__multi_span__grammar__match_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 437: ... push(setter(outer_node) grammar::current_node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__grammar__current_node();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_12;
}
static void cont__types__multi_span__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 437: setter &outer_node push(setter(outer_node) grammar::current_node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* outer_node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[0] /* setter */;
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_13;
}
static void cont__types__multi_span__grammar__match_13(void) {
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
static void entry__types__multi_span__grammar__match_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // outer_node: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* outer_node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 439: push &outer_node grammar::current_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* outer_node */;
  arguments->slots[1] = get__grammar__current_node();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__multi_span__grammar__match_15;
}
static void cont__types__multi_span__grammar__match_15(void) {
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
static void cont__types__multi_span__grammar__match_16(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__types__multi_span__grammar__match_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 440: !grammar::current_node outer_node
  set__grammar__current_node(((CELL *)frame->slots[3])->contents /* outer_node */);
  // 441: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* len */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__multi_span_1(void) {
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
  // 461: ... types::multi_span(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__multi_span);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 461: -> types::multi_span(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__set_node__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 479: !grammar::current_node node_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._node_of;
  func = myself->type;
  frame->cont = cont__types__set_node__grammar__match_2;
}
static void cont__types__set_node__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  // 480: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__set_node_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 488: ... types::set_node(.node_of node)
  {
    NODE *temp = clone_object_and_attributes(var.types__set_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node_of, frame->slots[0] /* node */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 488: -> types::set_node(.node_of node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__inspect_node__grammar__match_1(void) {
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
  // 506: $func function_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._function_of;
  func = myself->type;
  frame->cont = cont__types__inspect_node__grammar__match_2;
}
static void cont__types__inspect_node__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* func */, arguments->slots[0]);
  // 508: parameter_count_of(func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* func */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__inspect_node__grammar__match_3;
}
static void cont__types__inspect_node__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 508: parameter_count_of(func) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__inspect_node__grammar__match_4;
}
static void cont__types__inspect_node__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 508: ... :
  // 509:   func grammar::current_node stream
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__inspect_node__grammar__match_5, 0);
  // 510: :
  // 511:   func grammar::current_node
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__inspect_node__grammar__match_6, 0);
  // 507: if
  // 508:   parameter_count_of(func) == 2:
  // 509:     func grammar::current_node stream
  // 510:   :
  // 511:     func grammar::current_node
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__inspect_node__grammar__match_7;
}
static void entry__types__inspect_node__grammar__match_5(void) {
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
  // 509: func grammar::current_node stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__inspect_node__grammar__match_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // func: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* func */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 511: func grammar::current_node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__inspect_node__grammar__match_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 512: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__inspect_node_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 524: ... types::inspect_node(.function_of func)
  {
    NODE *temp = clone_object_and_attributes(var.types__inspect_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__function_of, frame->slots[0] /* func */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 524: -> types::inspect_node(.function_of func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__modify_node__grammar__match_1(void) {
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
  // 542: $func function_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._function_of;
  func = myself->type;
  frame->cont = cont__types__modify_node__grammar__match_2;
}
static void cont__types__modify_node__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* func */, arguments->slots[0]);
  // 544: parameter_count_of(func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* func */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__modify_node__grammar__match_3;
}
static void cont__types__modify_node__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 544: parameter_count_of(func) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__modify_node__grammar__match_4;
}
static void cont__types__modify_node__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 544: ... :
  // 545:   func &grammar::current_node stream
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__modify_node__grammar__match_5, 0);
  // 546: :
  // 547:   func &grammar::current_node
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__modify_node__grammar__match_7, 0);
  // 543: if
  // 544:   parameter_count_of(func) == 2:
  // 545:     func &grammar::current_node stream
  // 546:   :
  // 547:     func &grammar::current_node
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__modify_node__grammar__match_9;
}
static void entry__types__modify_node__grammar__match_5(void) {
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
  // 545: func &grammar::current_node stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__types__modify_node__grammar__match_6;
}
static void cont__types__modify_node__grammar__match_6(void) {
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
static void entry__types__modify_node__grammar__match_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // func: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* func */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 547: func &grammar::current_node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__types__modify_node__grammar__match_8;
}
static void cont__types__modify_node__grammar__match_8(void) {
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
static void cont__types__modify_node__grammar__match_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 548: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__modify_node_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 560: ... types::modify_node(.function_of func)
  {
    NODE *temp = clone_object_and_attributes(var.types__modify_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__function_of, frame->slots[0] /* func */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 560: -> types::modify_node(.function_of func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__check_node__grammar__match_1(void) {
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
  // 579: $func function_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._function_of;
  func = myself->type;
  frame->cont = cont__types__check_node__grammar__match_2;
}
static void cont__types__check_node__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* func */, arguments->slots[0]);
  // 581: parameter_count_of(func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* func */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__check_node__grammar__match_3;
}
static void cont__types__check_node__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 581: parameter_count_of(func) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__check_node__grammar__match_4;
}
static void cont__types__check_node__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 581: ... :
  // 582:   unless func(grammar::current_node stream): return undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__check_node__grammar__match_5, 0);
  // 583: :
  // 584:   unless func(grammar::current_node): return undefined
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__check_node__grammar__match_8, 0);
  // 580: if
  // 581:   parameter_count_of(func) == 2:
  // 582:     unless func(grammar::current_node stream): return undefined
  // 583:   :
  // 584:     unless func(grammar::current_node): return undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__check_node__grammar__match_11;
}
static void entry__types__check_node__grammar__match_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 584: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__check_node__grammar__match_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 582: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__check_node__grammar__match_5(void) {
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
  // 582: ... func(grammar::current_node stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__types__check_node__grammar__match_6;
}
static void cont__types__check_node__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 582: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__check_node__grammar__match_7, 0);
  // 582: unless func(grammar::current_node stream): return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__check_node__grammar__match_8(void) {
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
  // 584: ... func(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame->cont = cont__types__check_node__grammar__match_9;
}
static void cont__types__check_node__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 584: ... : return undefined
  frame->slots[3] /* temp__2 */ = create_closure(entry__types__check_node__grammar__match_10, 0);
  // 584: unless func(grammar::current_node): return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__check_node__grammar__match_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 585: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__check_node_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 597: ... types::check_node(.function_of func)
  {
    NODE *temp = clone_object_and_attributes(var.types__check_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__function_of, frame->slots[0] /* func */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 597: -> types::check_node(.function_of func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__grammar_action__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 613: ... function_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._function_of;
  func = myself->type;
  frame->cont = cont__types__grammar_action__grammar__match_2;
}
static void cont__types__grammar_action__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 613: ... function_of(self)(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__types__grammar_action__grammar__match_3;
}
static void cont__types__grammar_action__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 613: -> function_of(self)(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__grammar_action_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 626: ... types::grammar_action(.function_of func)
  {
    NODE *temp = clone_object_and_attributes(var.types__grammar_action);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__function_of, frame->slots[0] /* func */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 626: -> types::grammar_action(.function_of func)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__set_field__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 644: ... expr_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._expr_of;
  func = myself->type;
  frame->cont = cont__types__set_field__grammar__match_2;
}
static void cont__types__set_field__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 644: setter_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._setter_of;
  func = myself->type;
  frame->cont = cont__types__set_field__grammar__match_3;
}
static void cont__types__set_field__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 644: setter_of(self) &grammar::current_node expr_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__types__set_field__grammar__match_4;
}
static void cont__types__set_field__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__grammar__current_node(arguments->slots[0]);
  // 645: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__set_field_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // setter: 0
  // expr: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 658: ... types::set_field(.setter_of setter .expr_of expr)
  {
    NODE *temp = clone_object_and_attributes(var.types__set_field);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__setter_of, frame->slots[0] /* setter */);
    set_attribute_value(temp->attributes, poly_idx__expr_of, frame->slots[1] /* expr */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 658: -> types::set_field(.setter_of setter .expr_of expr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__END_OF_TEXT__grammar__match_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 678: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__END_OF_TEXT__grammar__match_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 679: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__END_OF_TEXT__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 677: stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__END_OF_TEXT__grammar__match_2;
}
static void cont__std__END_OF_TEXT__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 676: if
  // 677:   stream .has_minimum_length. 1
  // 678:   -> undefined
  // 679:   -> 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__std__END_OF_TEXT__grammar__match_3;
  arguments->slots[2] = func__std__END_OF_TEXT__grammar__match_4;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__LETTER__grammar__match_1(void) {
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
  // 698: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_2;
}
static void cont__std__LETTER__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 698: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__LETTER__grammar__match_3, 0);
  // 698: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_4;
}
static void entry__std__LETTER__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 698: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__LETTER__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 700: stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_5;
}
static void cont__std__LETTER__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 700: stream(1) >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_6;
}
static void cont__std__LETTER__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 700: stream(1) >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_7;
}
static void cont__std__LETTER__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 700: ... stream(1) <= 'z'
  frame->slots[8] /* temp__6 */ = create_closure(entry__std__LETTER__grammar__match_8, 0);
  // 700: stream(1) >= 'a' && stream(1) <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_12;
}
static void entry__std__LETTER__grammar__match_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_9;
}
static void cont__std__LETTER__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 700: ... stream(1) <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_10;
}
static void cont__std__LETTER__grammar__match_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 700: ... stream(1) <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_11;
}
static void cont__std__LETTER__grammar__match_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 700: ... stream(1) <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__LETTER__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 700: ... stream(1) >= 'A' && stream(1) <= 'Z'
  frame->slots[9] /* temp__7 */ = create_closure(entry__std__LETTER__grammar__match_13, 0);
  // 700: stream(1) >= 'a' && stream(1) <= 'z' || stream(1) >= 'A' && stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__7 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_22;
}
static void entry__std__LETTER__grammar__match_13(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_14;
}
static void cont__std__LETTER__grammar__match_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 700: ... stream(1) >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_15;
}
static void cont__std__LETTER__grammar__match_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 700: ... stream(1) >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_16;
}
static void cont__std__LETTER__grammar__match_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 700: ... stream(1) <= 'Z'
  frame->slots[5] /* temp__5 */ = create_closure(entry__std__LETTER__grammar__match_17, 0);
  // 700: ... stream(1) >= 'A' && stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_21;
}
static void entry__std__LETTER__grammar__match_17(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_18;
}
static void cont__std__LETTER__grammar__match_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 700: ... stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_19;
}
static void cont__std__LETTER__grammar__match_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 700: ... stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_20;
}
static void cont__std__LETTER__grammar__match_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 700: ... stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__LETTER__grammar__match_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 700: ... stream(1) >= 'A' && stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__LETTER__grammar__match_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 701: :
  // 702:   return 1
  frame->slots[10] /* temp__8 */ = create_closure(entry__std__LETTER__grammar__match_23, 0);
  // 699: if
  // 700:   stream(1) >= 'a' && stream(1) <= 'z' || stream(1) >= 'A' && stream(1) <= 'Z'
  // 701:   :
  // 702:     return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__8 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__LETTER__grammar__match_24;
}
static void entry__std__LETTER__grammar__match_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 702: return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__LETTER__grammar__match_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 703: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__UPPER_CASE_LETTER__grammar__match_1(void) {
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
  // 722: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_2;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 722: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__UPPER_CASE_LETTER__grammar__match_3, 0);
  // 722: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_4;
}
static void entry__std__UPPER_CASE_LETTER__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 722: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 723: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_5;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 723: ... stream(1) >= 'A'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = character__65;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_6;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 723: ... stream(1) >= 'A'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_7;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 723: ... stream(1) <= 'Z'
  frame->slots[7] /* temp__5 */ = create_closure(entry__std__UPPER_CASE_LETTER__grammar__match_8, 0);
  // 723: ... stream(1) >= 'A' && stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_12;
}
static void entry__std__UPPER_CASE_LETTER__grammar__match_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 723: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_9;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 723: ... stream(1) <= 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__90;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_10;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 723: ... stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_11;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 723: ... stream(1) <= 'Z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 723: ... : return 1
  frame->slots[8] /* temp__6 */ = create_closure(entry__std__UPPER_CASE_LETTER__grammar__match_13, 0);
  // 723: if stream(1) >= 'A' && stream(1) <= 'Z': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__UPPER_CASE_LETTER__grammar__match_14;
}
static void entry__std__UPPER_CASE_LETTER__grammar__match_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 723: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__UPPER_CASE_LETTER__grammar__match_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 724: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__LOWER_CASE_LETTER__grammar__match_1(void) {
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
  // 743: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_2;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 743: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__LOWER_CASE_LETTER__grammar__match_3, 0);
  // 743: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_4;
}
static void entry__std__LOWER_CASE_LETTER__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 743: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 744: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_5;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 744: ... stream(1) >= 'a'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = character__97;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_6;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 744: ... stream(1) >= 'a'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_7;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 744: ... stream(1) <= 'z'
  frame->slots[7] /* temp__5 */ = create_closure(entry__std__LOWER_CASE_LETTER__grammar__match_8, 0);
  // 744: ... stream(1) >= 'a' && stream(1) <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_12;
}
static void entry__std__LOWER_CASE_LETTER__grammar__match_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_9;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 744: ... stream(1) <= 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__122;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_10;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 744: ... stream(1) <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_11;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 744: ... stream(1) <= 'z'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 744: ... : return 1
  frame->slots[8] /* temp__6 */ = create_closure(entry__std__LOWER_CASE_LETTER__grammar__match_13, 0);
  // 744: if stream(1) >= 'a' && stream(1) <= 'z': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__LOWER_CASE_LETTER__grammar__match_14;
}
static void entry__std__LOWER_CASE_LETTER__grammar__match_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__LOWER_CASE_LETTER__grammar__match_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__DIGIT__grammar__match_1(void) {
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
  // 764: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_2;
}
static void cont__std__DIGIT__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 764: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__DIGIT__grammar__match_3, 0);
  // 764: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_4;
}
static void entry__std__DIGIT__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 764: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__DIGIT__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 765: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_5;
}
static void cont__std__DIGIT__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 765: ... stream(1) >= '0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_6;
}
static void cont__std__DIGIT__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 765: ... stream(1) >= '0'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_7;
}
static void cont__std__DIGIT__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 765: ... stream(1) <= '9'
  frame->slots[7] /* temp__5 */ = create_closure(entry__std__DIGIT__grammar__match_8, 0);
  // 765: ... stream(1) >= '0' && stream(1) <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_12;
}
static void entry__std__DIGIT__grammar__match_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 765: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* stream */;
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_9;
}
static void cont__std__DIGIT__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 765: ... stream(1) <= '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__57;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_10;
}
static void cont__std__DIGIT__grammar__match_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 765: ... stream(1) <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_11;
}
static void cont__std__DIGIT__grammar__match_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 765: ... stream(1) <= '9'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__DIGIT__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 765: ... : return 1
  frame->slots[8] /* temp__6 */ = create_closure(entry__std__DIGIT__grammar__match_13, 0);
  // 765: if stream(1) >= '0' && stream(1) <= '9': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__DIGIT__grammar__match_14;
}
static void entry__std__DIGIT__grammar__match_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 765: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__DIGIT__grammar__match_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 766: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__WHITESPACE_CHARACTER__grammar__match_1(void) {
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
  // 785: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__WHITESPACE_CHARACTER__grammar__match_2;
}
static void cont__std__WHITESPACE_CHARACTER__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 785: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__WHITESPACE_CHARACTER__grammar__match_3, 0);
  // 785: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__WHITESPACE_CHARACTER__grammar__match_4;
}
static void entry__std__WHITESPACE_CHARACTER__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 785: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__WHITESPACE_CHARACTER__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 786: $chr stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__std__WHITESPACE_CHARACTER__grammar__match_5;
}
static void cont__std__WHITESPACE_CHARACTER__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 787: ... chr <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[3] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__WHITESPACE_CHARACTER__grammar__match_6;
}
static void cont__std__WHITESPACE_CHARACTER__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 787: ... chr <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__WHITESPACE_CHARACTER__grammar__match_7;
}
static void cont__std__WHITESPACE_CHARACTER__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 787: ... chr == '@del;'
  frame->slots[7] /* temp__4 */ = create_closure(entry__std__WHITESPACE_CHARACTER__grammar__match_8, 0);
  // 787: ... chr <= ' ' || chr == '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__WHITESPACE_CHARACTER__grammar__match_10;
}
static void entry__std__WHITESPACE_CHARACTER__grammar__match_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 787: ... chr == '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__127;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__WHITESPACE_CHARACTER__grammar__match_9;
}
static void cont__std__WHITESPACE_CHARACTER__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 787: ... chr == '@del;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__WHITESPACE_CHARACTER__grammar__match_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 787: ... : return 1
  frame->slots[8] /* temp__5 */ = create_closure(entry__std__WHITESPACE_CHARACTER__grammar__match_11, 0);
  // 787: if chr <= ' ' || chr == '@del;': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__WHITESPACE_CHARACTER__grammar__match_12;
}
static void entry__std__WHITESPACE_CHARACTER__grammar__match_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 787: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__WHITESPACE_CHARACTER__grammar__match_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 788: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__PRINTABLE_CHARACTER__grammar__match_1(void) {
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
  // 816: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_2;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 816: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__PRINTABLE_CHARACTER__grammar__match_3, 0);
  // 816: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_4;
}
static void entry__std__PRINTABLE_CHARACTER__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 816: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 817: $chr stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_5;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 818: ... chr >= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_6;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 818: ... chr >= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_7;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 818: ... chr < '@del;'
  frame->slots[8] /* temp__5 */ = create_closure(entry__std__PRINTABLE_CHARACTER__grammar__match_8, 0);
  // 818: ... chr >= ' ' && chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_10;
}
static void entry__std__PRINTABLE_CHARACTER__grammar__match_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 818: ... chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__127;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_9;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 818: ... chr < '@del;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 818: ... chr >= '@nbsp;'
  frame->slots[9] /* temp__6 */ = create_closure(entry__std__PRINTABLE_CHARACTER__grammar__match_11, 0);
  // 818: ... chr >= ' ' && chr < '@del;' || chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_14;
}
static void entry__std__PRINTABLE_CHARACTER__grammar__match_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 818: ... chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__160;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_12;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 818: ... chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_13;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 818: ... chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 818: ... : return 1
  frame->slots[10] /* temp__7 */ = create_closure(entry__std__PRINTABLE_CHARACTER__grammar__match_15, 0);
  // 818: if chr >= ' ' && chr < '@del;' || chr >= '@nbsp;': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__7 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__PRINTABLE_CHARACTER__grammar__match_16;
}
static void entry__std__PRINTABLE_CHARACTER__grammar__match_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 818: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__PRINTABLE_CHARACTER__grammar__match_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 819: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__NON_SPACE_CHARACTER__grammar__match_1(void) {
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
  // 838: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_2;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 838: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__NON_SPACE_CHARACTER__grammar__match_3, 0);
  // 838: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_4;
}
static void entry__std__NON_SPACE_CHARACTER__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 838: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 839: $chr stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_5;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 840: ... chr > ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[3] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_6;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 840: ... chr < '@del;'
  frame->slots[7] /* temp__4 */ = create_closure(entry__std__NON_SPACE_CHARACTER__grammar__match_7, 0);
  // 840: ... chr > ' ' && chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_9;
}
static void entry__std__NON_SPACE_CHARACTER__grammar__match_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 840: ... chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__127;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_8;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 840: ... chr < '@del;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 840: ... chr >= '@nbsp;'
  frame->slots[8] /* temp__5 */ = create_closure(entry__std__NON_SPACE_CHARACTER__grammar__match_10, 0);
  // 840: ... chr > ' ' && chr < '@del;' || chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_13;
}
static void entry__std__NON_SPACE_CHARACTER__grammar__match_10(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 840: ... chr >= '@nbsp;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__160;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_11;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 840: ... chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_12;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 840: ... chr >= '@nbsp;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 840: ... : return 1
  frame->slots[9] /* temp__6 */ = create_closure(entry__std__NON_SPACE_CHARACTER__grammar__match_14, 0);
  // 840: if chr > ' ' && chr < '@del;' || chr >= '@nbsp;': return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__NON_SPACE_CHARACTER__grammar__match_15;
}
static void entry__std__NON_SPACE_CHARACTER__grammar__match_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 840: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__NON_SPACE_CHARACTER__grammar__match_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 841: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__ANY_CHARACTER__grammar__match_1(void) {
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
  // 860: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__std__ANY_CHARACTER__grammar__match_2;
}
static void cont__std__ANY_CHARACTER__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 860: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__ANY_CHARACTER__grammar__match_3, 0);
  // 860: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__ANY_CHARACTER__grammar__match_4;
}
static void entry__std__ANY_CHARACTER__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 860: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__ANY_CHARACTER__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 861: -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__character__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // chr: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 875: match_character stream chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = frame->slots[0] /* chr */;
  result_count = frame->caller_result_count;
  myself = get__match_character();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__value_range__grammar__match_1(void) {
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
  // 890: ... stream .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_2;
}
static void cont__types__value_range__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 890: ... : return undefined
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__value_range__grammar__match_3, 0);
  // 890: unless stream .has_minimum_length. 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_4;
}
static void entry__types__value_range__grammar__match_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 890: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__value_range__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 891: $chr stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_5;
}
static void cont__types__value_range__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 892: ... lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_6;
}
static void cont__types__value_range__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 892: ... chr >= lower_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* chr */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_7;
}
static void cont__types__value_range__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 892: ... chr >= lower_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_8;
}
static void cont__types__value_range__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 892: ... chr <= upper_bound_of(self)
  frame->slots[8] /* temp__5 */ = create_closure(entry__types__value_range__grammar__match_9, 0);
  // 892: ... chr >= lower_bound_of(self) && chr <= upper_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_13;
}
static void entry__types__value_range__grammar__match_9(void) {
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
  // 892: ... upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_10;
}
static void cont__types__value_range__grammar__match_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 892: ... chr <= upper_bound_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_11;
}
static void cont__types__value_range__grammar__match_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 892: ... chr <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_12;
}
static void cont__types__value_range__grammar__match_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 892: ... chr <= upper_bound_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__value_range__grammar__match_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 892: ... : return 1
  frame->slots[9] /* temp__6 */ = create_closure(entry__types__value_range__grammar__match_14, 0);
  // 892: if chr >= lower_bound_of(self) && chr <= upper_bound_of(self): return 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__value_range__grammar__match_15;
}
static void entry__types__value_range__grammar__match_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 892: ... return 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__value_range__grammar__match_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 893: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__list__grammar__match_1(void) {
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
  // 909: $$len 0
  ((CELL *)frame->slots[3])->contents /* len */ = number__0;
  // 910: $original_node grammar::current_node
  initialize_future(frame->slots[4] /* original_node */, get__grammar__current_node());
  // 911: ... : (expr)
  // 912:   $n grammar::match(expr stream)
  // 913:   unless n.is_defined:
  // 914:     !grammar::current_node original_node
  // 915:     return undefined
  // 916:   range &stream n+1 -1
  // 917:   plus &len n
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__list__grammar__match_2, 1);
  // 911: for_each self: (expr)
  // 912:   $n grammar::match(expr stream)
  // 913:   unless n.is_defined:
  // 914:     !grammar::current_node original_node
  // 915:     return undefined
  // 916:   range &stream n+1 -1
  // 917:   plus &len n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__list__grammar__match_11;
}
static void entry__types__list__grammar__match_2(void) {
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
  // 912: $n grammar::match(expr stream)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* stream */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__list__grammar__match_3;
}
static void cont__types__list__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* n */, arguments->slots[0]);
  // 913: ... n.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* n */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__list__grammar__match_4;
}
static void cont__types__list__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 913: ... :
  // 914:   !grammar::current_node original_node
  // 915:   return undefined
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__list__grammar__match_5, 0);
  // 913: unless n.is_defined:
  // 914:   !grammar::current_node original_node
  // 915:   return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__list__grammar__match_6;
}
static void entry__types__list__grammar__match_5(void) {
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
  // 914: !grammar::current_node original_node
  set__grammar__current_node(frame->slots[0] /* original_node */);
  // 915: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__list__grammar__match_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 916: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__list__grammar__match_7;
}
static void cont__types__list__grammar__match_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 916: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__list__grammar__match_8;
}
static void cont__types__list__grammar__match_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 916: range &stream n+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* stream */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__list__grammar__match_9;
}
static void cont__types__list__grammar__match_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* stream */ = arguments->slots[0];
  // 917: plus &len n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* len */;
  arguments->slots[1] = frame->slots[5] /* n */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__list__grammar__match_10;
}
static void cont__types__list__grammar__match_10(void) {
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
static void cont__types__list__grammar__match_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 918: -> len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* len */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__object__grammar__search_1(void) {
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
  // 931: $$pos 1
  ((CELL *)frame->slots[4])->contents /* pos */ = number__1;
  // 932: $$s stream
  ((CELL *)frame->slots[5])->contents /* s */ = frame->slots[1] /* stream */;
  // 934: nth > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* nth */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_2;
}
static void cont__types__object__grammar__search_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 934: ... :
  // 935:   forever:
  // 936:     $len grammar::match(expr s)
  // 937:     if len.is_defined:
  // 938:       if nth == 1: return pos len
  // 939:       if len > 0:
  // 940:         plus &pos len-1
  // 941:         range &s len -1
  // 942:       minus &nth 1
  // 943:     unless s .has_minimum_length. 1: return undefined undefined
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__object__grammar__search_3, 0);
  // 946: :
  // 947:   negate &nth
  // 948:   $$positions empty_list
  // 949:   $$lengths empty_list
  // 950:   forever:
  // 951:     $len grammar::match(expr s)
  // 952:     if len.is_defined:
  // 953:       if length_of(positions) >= nth:
  // 954:         range &positions 2 -1
  // 955:         range &lengths 2 -1
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__object__grammar__search_26, 0);
  // 933: if
  // 934:   nth > 0:
  // 935:     forever:
  // 936:       $len grammar::match(expr s)
  // 937:       if len.is_defined:
  // 938:         if nth == 1: return pos len
  // 939:         if len > 0:
  // 940:           plus &pos len-1
  // 941:           range &s len -1
  // 942:         minus &nth 1
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_62;
}
static void entry__types__object__grammar__search_28(void) {
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
  // 951: $len grammar::match(expr s)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_29;
}
static void cont__types__object__grammar__search_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* len */, arguments->slots[0]);
  // 952: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_30;
}
static void cont__types__object__grammar__search_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 952: ... :
  // 953:   if length_of(positions) >= nth:
  // 954:     range &positions 2 -1
  // 955:     range &lengths 2 -1
  // 956:   push &positions pos
  // 957:   push &lengths len
  // 958:   if len > 0:
  // 959:     plus &pos len-1
  // 960:     range &s len -1
  frame->slots[9] /* temp__2 */ = create_closure(entry__types__object__grammar__search_31, 0);
  // 952: if len.is_defined:
  // 953:   if length_of(positions) >= nth:
  // 954:     range &positions 2 -1
  // 955:     range &lengths 2 -1
  // 956:   push &positions pos
  // 957:   push &lengths len
  // 958:   if len > 0:
  // 959:     plus &pos len-1
  // 960:     range &s len -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_49;
}
static void entry__types__object__grammar__search_44(void) {
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
  // 959: ... len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_45;
}
static void cont__types__object__grammar__search_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 959: plus &pos len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pos */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_46;
}
static void cont__types__object__grammar__search_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pos */ = arguments->slots[0];
  // 960: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_47;
}
static void cont__types__object__grammar__search_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 960: range &s len -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  arguments->slots[1] = frame->slots[1] /* len */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_48;
}
static void cont__types__object__grammar__search_48(void) {
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
static void entry__types__object__grammar__search_31(void) {
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
  // 953: ... length_of(positions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* positions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_32;
}
static void cont__types__object__grammar__search_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 953: ... length_of(positions) >= nth
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* nth */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_33;
}
static void cont__types__object__grammar__search_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 953: ... length_of(positions) >= nth
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_34;
}
static void cont__types__object__grammar__search_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 953: ... :
  // 954:   range &positions 2 -1
  // 955:   range &lengths 2 -1
  frame->slots[9] /* temp__4 */ = create_closure(entry__types__object__grammar__search_35, 0);
  // 953: if length_of(positions) >= nth:
  // 954:   range &positions 2 -1
  // 955:   range &lengths 2 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_40;
}
static void entry__types__object__grammar__search_35(void) {
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
  // 954: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_36;
}
static void cont__types__object__grammar__search_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 954: range &positions 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* positions */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_37;
}
static void cont__types__object__grammar__search_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* positions */ = arguments->slots[0];
  // 955: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_38;
}
static void cont__types__object__grammar__search_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 955: range &lengths 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* lengths */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_39;
}
static void cont__types__object__grammar__search_39(void) {
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
static void cont__types__object__grammar__search_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 956: push &positions pos
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* positions */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* pos */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_41;
}
static void cont__types__object__grammar__search_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* positions */ = arguments->slots[0];
  // 957: push &lengths len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* lengths */;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_42;
}
static void cont__types__object__grammar__search_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* lengths */ = arguments->slots[0];
  // 958: ... len > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_43;
}
static void cont__types__object__grammar__search_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 958: ... :
  // 959:   plus &pos len-1
  // 960:   range &s len -1
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__object__grammar__search_44, 0);
  // 958: if len > 0:
  // 959:   plus &pos len-1
  // 960:   range &s len -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__object__grammar__search_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 961: ... s .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_50;
}
static void cont__types__object__grammar__search_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 961: ... :
  // 962:   if length_of(positions) < nth: return undefined undefined
  // 963:   return positions(1) lengths(1)
  frame->slots[9] /* temp__2 */ = create_closure(entry__types__object__grammar__search_51, 0);
  // 961: unless s .has_minimum_length. 1:
  // 962:   if length_of(positions) < nth: return undefined undefined
  // 963:   return positions(1) lengths(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_58;
}
static void entry__types__object__grammar__search_51(void) {
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
  // 962: ... length_of(positions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* positions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_52;
}
static void cont__types__object__grammar__search_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 962: ... length_of(positions) < nth
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* nth */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_53;
}
static void cont__types__object__grammar__search_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 962: ... : return undefined undefined
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__object__grammar__search_54, 0);
  // 962: if length_of(positions) < nth: return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_55;
}
static void entry__types__object__grammar__search_54(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 962: ... return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__object__grammar__search_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 963: ... positions(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* positions */;
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_56;
}
static void cont__types__object__grammar__search_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 963: ... lengths(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* lengths */;
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_57;
}
static void cont__types__object__grammar__search_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 963: return positions(1) lengths(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__object__grammar__search_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 964: plus &pos 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_59;
}
static void cont__types__object__grammar__search_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* pos */ = arguments->slots[0];
  // 965: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_60;
}
static void cont__types__object__grammar__search_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 965: range &s 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_61;
}
static void cont__types__object__grammar__search_61(void) {
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
static void entry__types__object__grammar__search_4(void) {
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
  // 936: $len grammar::match(expr s)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  result_count = 1;
  myself = var.grammar__match;
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_5;
}
static void cont__types__object__grammar__search_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* len */, arguments->slots[0]);
  // 937: ... len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_6;
}
static void cont__types__object__grammar__search_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 937: ... :
  // 938:   if nth == 1: return pos len
  // 939:   if len > 0:
  // 940:     plus &pos len-1
  // 941:     range &s len -1
  // 942:   minus &nth 1
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__object__grammar__search_7, 0);
  // 937: if len.is_defined:
  // 938:   if nth == 1: return pos len
  // 939:   if len > 0:
  // 940:     plus &pos len-1
  // 941:     range &s len -1
  // 942:   minus &nth 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_19;
}
static void entry__types__object__grammar__search_7(void) {
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
  // 938: ... nth == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* nth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_8;
}
static void cont__types__object__grammar__search_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 938: ... : return pos len
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__object__grammar__search_9, 0);
  // 938: if nth == 1: return pos len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_10;
}
static void entry__types__object__grammar__search_9(void) {
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
  // 938: ... return pos len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* pos */;
  arguments->slots[1] = frame->slots[2] /* len */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__object__grammar__search_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 939: ... len > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_11;
}
static void cont__types__object__grammar__search_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 939: ... :
  // 940:   plus &pos len-1
  // 941:   range &s len -1
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__object__grammar__search_12, 0);
  // 939: if len > 0:
  // 940:   plus &pos len-1
  // 941:   range &s len -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_17;
}
static void entry__types__object__grammar__search_12(void) {
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
  // 940: ... len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_13;
}
static void cont__types__object__grammar__search_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 940: plus &pos len-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pos */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_14;
}
static void cont__types__object__grammar__search_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pos */ = arguments->slots[0];
  // 941: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_15;
}
static void cont__types__object__grammar__search_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 941: range &s len -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  arguments->slots[1] = frame->slots[1] /* len */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_16;
}
static void cont__types__object__grammar__search_16(void) {
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
static void cont__types__object__grammar__search_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 942: minus &nth 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* nth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_18;
}
static void cont__types__object__grammar__search_18(void) {
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
static void cont__types__object__grammar__search_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 943: ... s .has_minimum_length. 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__has_minimum_length();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_20;
}
static void cont__types__object__grammar__search_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 943: ... : return undefined undefined
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__object__grammar__search_21, 0);
  // 943: unless s .has_minimum_length. 1: return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_22;
}
static void entry__types__object__grammar__search_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 943: ... return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__object__grammar__search_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 944: plus &pos 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_23;
}
static void cont__types__object__grammar__search_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* pos */ = arguments->slots[0];
  // 945: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_24;
}
static void cont__types__object__grammar__search_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 945: range &s 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_25;
}
static void cont__types__object__grammar__search_25(void) {
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
static void entry__types__object__grammar__search_3(void) {
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
  // 935: ... :
  // 936:   $len grammar::match(expr s)
  // 937:   if len.is_defined:
  // 938:     if nth == 1: return pos len
  // 939:     if len > 0:
  // 940:       plus &pos len-1
  // 941:       range &s len -1
  // 942:     minus &nth 1
  // 943:   unless s .has_minimum_length. 1: return undefined undefined
  // 944:   plus &pos 1
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__object__grammar__search_4, 0);
  // 935: forever:
  // 936:   $len grammar::match(expr s)
  // 937:   if len.is_defined:
  // 938:     if nth == 1: return pos len
  // 939:     if len > 0:
  // 940:       plus &pos len-1
  // 941:       range &s len -1
  // 942:     minus &nth 1
  // 943:   unless s .has_minimum_length. 1: return undefined undefined
  // 944:   plus &pos 1
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__object__grammar__search_26(void) {
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
  // 947: negate &nth
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* nth */;
  result_count = 1;
  myself = get__negate();
  func = myself->type;
  frame->cont = cont__types__object__grammar__search_27;
}
static void cont__types__object__grammar__search_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* nth */ = arguments->slots[0];
  // 948: $$positions empty_list
  ((CELL *)frame->slots[5])->contents /* positions */ = get__empty_list();
  // 949: $$lengths empty_list
  ((CELL *)frame->slots[6])->contents /* lengths */ = get__empty_list();
  // 950: ... :
  // 951:   $len grammar::match(expr s)
  // 952:   if len.is_defined:
  // 953:     if length_of(positions) >= nth:
  // 954:       range &positions 2 -1
  // 955:       range &lengths 2 -1
  // 956:     push &positions pos
  // 957:     push &lengths len
  // 958:     if len > 0:
  // 959:       plus &pos len-1
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__types__object__grammar__search_28, 0);
  // 950: forever:
  // 951:   $len grammar::match(expr s)
  // 952:   if len.is_defined:
  // 953:     if length_of(positions) >= nth:
  // 954:       range &positions 2 -1
  // 955:       range &lengths 2 -1
  // 956:     push &positions pos
  // 957:     push &lengths len
  // 958:     if len > 0:
  // 959:       plus &pos len-1
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__object__grammar__search_62(void) {
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
  define_namespace("grammar");
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__grammar(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__grammar");
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
  define_polymorphic_function("grammar", "match", get__grammar__match, &poly_idx__grammar__match, &var.grammar__match);
  define_polymorphic_function("grammar", "search", get__grammar__search, &poly_idx__grammar__search, &var.grammar__search);
  register_polymorphic_function_with_setter("_basic__grammar::expr_of", &poly_idx__expr_of);
  register_polymorphic_function_with_setter("_basic__grammar::alternatives_of", &poly_idx__alternatives_of);
  register_polymorphic_function_with_setter("_basic__grammar::setter_of", &poly_idx__setter_of);
  register_polymorphic_function_with_setter("_basic__grammar::node_of", &poly_idx__node_of);
  register_polymorphic_function_with_setter("_basic__grammar::function_of", &poly_idx__function_of);
  func__types__optional__grammar__match_1 = create_function(entry__types__optional__grammar__match_1, 2);
  func__std__optional_1 = create_function(entry__std__optional_1, 1);
  func__types__many__grammar__match_1 = create_function(entry__types__many__grammar__match_1, 2);
  func__std__many_1 = create_function(entry__std__many_1, 1);
  func__types__some__grammar__match_1 = create_function(entry__types__some__grammar__match_1, 2);
  func__std__some_1 = create_function(entry__std__some_1, 1);
  func__types__alt__grammar__match_1 = create_function(entry__types__alt__grammar__match_1, 2);
  func__std__alt_1 = create_function(entry__std__alt_1, -1);
  func__types__followed_by__grammar__match_1 = create_function(entry__types__followed_by__grammar__match_1, 2);
  func__std__followed_by_1 = create_function(entry__std__followed_by_1, 1);
  func__types__not_followed_by__grammar__match_1 = create_function(entry__types__not_followed_by__grammar__match_1, 2);
  func__std__not_followed_by_1 = create_function(entry__std__not_followed_by_1, 1);
  func__types__capture__grammar__match_1 = create_function(entry__types__capture__grammar__match_1, 2);
  func__std__capture_1 = create_function(entry__std__capture_1, -1);
  func__types__multi_capture__grammar__match_1 = create_function(entry__types__multi_capture__grammar__match_1, 2);
  func__std__multi_capture_1 = create_function(entry__std__multi_capture_1, -1);
  func__types__span__grammar__match_1 = create_function(entry__types__span__grammar__match_1, 2);
  func__std__span_1 = create_function(entry__std__span_1, 2);
  func__types__multi_span__grammar__match_1 = create_function(entry__types__multi_span__grammar__match_1, 2);
  func__std__multi_span_1 = create_function(entry__std__multi_span_1, -1);
  func__types__set_node__grammar__match_1 = create_function(entry__types__set_node__grammar__match_1, 2);
  func__std__set_node_1 = create_function(entry__std__set_node_1, 1);
  func__types__inspect_node__grammar__match_1 = create_function(entry__types__inspect_node__grammar__match_1, 2);
  func__std__inspect_node_1 = create_function(entry__std__inspect_node_1, 1);
  func__types__modify_node__grammar__match_1 = create_function(entry__types__modify_node__grammar__match_1, 2);
  func__std__modify_node_1 = create_function(entry__std__modify_node_1, 1);
  func__types__check_node__grammar__match_1 = create_function(entry__types__check_node__grammar__match_1, 2);
  func__std__check_node_1 = create_function(entry__std__check_node_1, 1);
  func__types__grammar_action__grammar__match_1 = create_function(entry__types__grammar_action__grammar__match_1, 2);
  func__std__grammar_action_1 = create_function(entry__std__grammar_action_1, 1);
  func__types__set_field__grammar__match_1 = create_function(entry__types__set_field__grammar__match_1, 2);
  func__std__set_field_1 = create_function(entry__std__set_field_1, 2);
  func__std__END_OF_TEXT__grammar__match_3 = create_function(entry__std__END_OF_TEXT__grammar__match_3, 0);
  func__std__END_OF_TEXT__grammar__match_4 = create_function(entry__std__END_OF_TEXT__grammar__match_4, 0);
  func__std__END_OF_TEXT__grammar__match_1 = create_function(entry__std__END_OF_TEXT__grammar__match_1, 2);
  func__std__LETTER__grammar__match_1 = create_function(entry__std__LETTER__grammar__match_1, 2);
  func__std__UPPER_CASE_LETTER__grammar__match_1 = create_function(entry__std__UPPER_CASE_LETTER__grammar__match_1, 2);
  func__std__LOWER_CASE_LETTER__grammar__match_1 = create_function(entry__std__LOWER_CASE_LETTER__grammar__match_1, 2);
  func__std__DIGIT__grammar__match_1 = create_function(entry__std__DIGIT__grammar__match_1, 2);
  func__std__WHITESPACE_CHARACTER__grammar__match_1 = create_function(entry__std__WHITESPACE_CHARACTER__grammar__match_1, 2);
  func__std__PRINTABLE_CHARACTER__grammar__match_1 = create_function(entry__std__PRINTABLE_CHARACTER__grammar__match_1, 2);
  func__std__NON_SPACE_CHARACTER__grammar__match_1 = create_function(entry__std__NON_SPACE_CHARACTER__grammar__match_1, 2);
  func__std__ANY_CHARACTER__grammar__match_1 = create_function(entry__std__ANY_CHARACTER__grammar__match_1, 2);
  func__types__character__grammar__match_1 = create_function(entry__types__character__grammar__match_1, 2);
  func__types__value_range__grammar__match_1 = create_function(entry__types__value_range__grammar__match_1, 2);
  func__types__list__grammar__match_1 = create_function(entry__types__list__grammar__match_1, 2);
  func__types__object__grammar__search_1 = create_function(entry__types__object__grammar__search_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__grammar(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__grammar");
  set_used_namespaces(used_namespaces);
  var.types__grammar_object = create_future();
  define_single_assign_static("types", "grammar_object", get__types__grammar_object, &var.types__grammar_object);
  var.types__grammar_node = create_future();
  define_single_assign_static("types", "grammar_node", get__types__grammar_node, &var.types__grammar_node);
  define_multi_assign_dynamic("grammar", "current_node", get__grammar__current_node, set__grammar__current_node, define__grammar__current_node, &dyna_idx__grammar__current_node);
  define__grammar__current_node(undefined);
  var.types__optional = create_future();
  define_single_assign_static("types", "optional", get__types__optional, &var.types__optional);
  var.std__optional = create_future();
  define_single_assign_static("std", "optional", get__std__optional, &var.std__optional);
  var.types__many = create_future();
  define_single_assign_static("types", "many", get__types__many, &var.types__many);
  var.std__many = create_future();
  define_single_assign_static("std", "many", get__std__many, &var.std__many);
  var.types__some = create_future();
  define_single_assign_static("types", "some", get__types__some, &var.types__some);
  var.std__some = create_future();
  define_single_assign_static("std", "some", get__std__some, &var.std__some);
  var.types__alt = create_future();
  define_single_assign_static("types", "alt", get__types__alt, &var.types__alt);
  var.std__alt = create_future();
  define_single_assign_static("std", "alt", get__std__alt, &var.std__alt);
  var.types__followed_by = create_future();
  define_single_assign_static("types", "followed_by", get__types__followed_by, &var.types__followed_by);
  var.std__followed_by = create_future();
  define_single_assign_static("std", "followed_by", get__std__followed_by, &var.std__followed_by);
  var.types__not_followed_by = create_future();
  define_single_assign_static("types", "not_followed_by", get__types__not_followed_by, &var.types__not_followed_by);
  var.std__not_followed_by = create_future();
  define_single_assign_static("std", "not_followed_by", get__std__not_followed_by, &var.std__not_followed_by);
  var.types__capture = create_future();
  define_single_assign_static("types", "capture", get__types__capture, &var.types__capture);
  var.std__capture = create_future();
  define_single_assign_static("std", "capture", get__std__capture, &var.std__capture);
  var.types__multi_capture = create_future();
  define_single_assign_static("types", "multi_capture", get__types__multi_capture, &var.types__multi_capture);
  var.std__multi_capture = create_future();
  define_single_assign_static("std", "multi_capture", get__std__multi_capture, &var.std__multi_capture);
  var.types__span = create_future();
  define_single_assign_static("types", "span", get__types__span, &var.types__span);
  var.std__span = create_future();
  define_single_assign_static("std", "span", get__std__span, &var.std__span);
  var.types__multi_span = create_future();
  define_single_assign_static("types", "multi_span", get__types__multi_span, &var.types__multi_span);
  var.std__multi_span = create_future();
  define_single_assign_static("std", "multi_span", get__std__multi_span, &var.std__multi_span);
  var.types__set_node = create_future();
  define_single_assign_static("types", "set_node", get__types__set_node, &var.types__set_node);
  var.std__set_node = create_future();
  define_single_assign_static("std", "set_node", get__std__set_node, &var.std__set_node);
  var.types__inspect_node = create_future();
  define_single_assign_static("types", "inspect_node", get__types__inspect_node, &var.types__inspect_node);
  var.std__inspect_node = create_future();
  define_single_assign_static("std", "inspect_node", get__std__inspect_node, &var.std__inspect_node);
  var.types__modify_node = create_future();
  define_single_assign_static("types", "modify_node", get__types__modify_node, &var.types__modify_node);
  var.std__modify_node = create_future();
  define_single_assign_static("std", "modify_node", get__std__modify_node, &var.std__modify_node);
  var.types__check_node = create_future();
  define_single_assign_static("types", "check_node", get__types__check_node, &var.types__check_node);
  var.std__check_node = create_future();
  define_single_assign_static("std", "check_node", get__std__check_node, &var.std__check_node);
  var.types__grammar_action = create_future();
  define_single_assign_static("types", "grammar_action", get__types__grammar_action, &var.types__grammar_action);
  var.std__grammar_action = create_future();
  define_single_assign_static("std", "grammar_action", get__std__grammar_action, &var.std__grammar_action);
  var.types__set_field = create_future();
  define_single_assign_static("types", "set_field", get__types__set_field, &var.types__set_field);
  var.std__set_field = create_future();
  define_single_assign_static("std", "set_field", get__std__set_field, &var.std__set_field);
  var.std__END_OF_TEXT = create_future();
  define_single_assign_static("std", "END_OF_TEXT", get__std__END_OF_TEXT, &var.std__END_OF_TEXT);
  var.std__LETTER = create_future();
  define_single_assign_static("std", "LETTER", get__std__LETTER, &var.std__LETTER);
  var.std__UPPER_CASE_LETTER = create_future();
  define_single_assign_static("std", "UPPER_CASE_LETTER", get__std__UPPER_CASE_LETTER, &var.std__UPPER_CASE_LETTER);
  var.std__LOWER_CASE_LETTER = create_future();
  define_single_assign_static("std", "LOWER_CASE_LETTER", get__std__LOWER_CASE_LETTER, &var.std__LOWER_CASE_LETTER);
  var.std__DIGIT = create_future();
  define_single_assign_static("std", "DIGIT", get__std__DIGIT, &var.std__DIGIT);
  var.std__WHITESPACE_CHARACTER = create_future();
  define_single_assign_static("std", "WHITESPACE_CHARACTER", get__std__WHITESPACE_CHARACTER, &var.std__WHITESPACE_CHARACTER);
  define_single_assign_static("std", "WHITESPACE", get__std__WHITESPACE, &var.std__WHITESPACE);
  var.std__PRINTABLE_CHARACTER = create_future();
  define_single_assign_static("std", "PRINTABLE_CHARACTER", get__std__PRINTABLE_CHARACTER, &var.std__PRINTABLE_CHARACTER);
  var.std__NON_SPACE_CHARACTER = create_future();
  define_single_assign_static("std", "NON_SPACE_CHARACTER", get__std__NON_SPACE_CHARACTER, &var.std__NON_SPACE_CHARACTER);
  var.std__ANY_CHARACTER = create_future();
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
  define_method("types", "optional", poly_idx__grammar__match, func__types__optional__grammar__match_1);
  define_method("types", "many", poly_idx__grammar__match, func__types__many__grammar__match_1);
  define_method("types", "some", poly_idx__grammar__match, func__types__some__grammar__match_1);
  define_method("types", "alt", poly_idx__grammar__match, func__types__alt__grammar__match_1);
  define_method("types", "followed_by", poly_idx__grammar__match, func__types__followed_by__grammar__match_1);
  define_method("types", "not_followed_by", poly_idx__grammar__match, func__types__not_followed_by__grammar__match_1);
  define_method("types", "capture", poly_idx__grammar__match, func__types__capture__grammar__match_1);
  define_method("types", "multi_capture", poly_idx__grammar__match, func__types__multi_capture__grammar__match_1);
  define_method("types", "span", poly_idx__grammar__match, func__types__span__grammar__match_1);
  define_method("types", "multi_span", poly_idx__grammar__match, func__types__multi_span__grammar__match_1);
  define_method("types", "set_node", poly_idx__grammar__match, func__types__set_node__grammar__match_1);
  define_method("types", "inspect_node", poly_idx__grammar__match, func__types__inspect_node__grammar__match_1);
  define_method("types", "modify_node", poly_idx__grammar__match, func__types__modify_node__grammar__match_1);
  define_method("types", "check_node", poly_idx__grammar__match, func__types__check_node__grammar__match_1);
  define_method("types", "grammar_action", poly_idx__grammar__match, func__types__grammar_action__grammar__match_1);
  define_method("types", "set_field", poly_idx__grammar__match, func__types__set_field__grammar__match_1);
  define_method("std", "END_OF_TEXT", poly_idx__grammar__match, func__std__END_OF_TEXT__grammar__match_1);
  define_method("std", "LETTER", poly_idx__grammar__match, func__std__LETTER__grammar__match_1);
  define_method("std", "UPPER_CASE_LETTER", poly_idx__grammar__match, func__std__UPPER_CASE_LETTER__grammar__match_1);
  define_method("std", "LOWER_CASE_LETTER", poly_idx__grammar__match, func__std__LOWER_CASE_LETTER__grammar__match_1);
  define_method("std", "DIGIT", poly_idx__grammar__match, func__std__DIGIT__grammar__match_1);
  define_method("std", "WHITESPACE_CHARACTER", poly_idx__grammar__match, func__std__WHITESPACE_CHARACTER__grammar__match_1);
  define_method("std", "PRINTABLE_CHARACTER", poly_idx__grammar__match, func__std__PRINTABLE_CHARACTER__grammar__match_1);
  define_method("std", "NON_SPACE_CHARACTER", poly_idx__grammar__match, func__std__NON_SPACE_CHARACTER__grammar__match_1);
  define_method("std", "ANY_CHARACTER", poly_idx__grammar__match, func__std__ANY_CHARACTER__grammar__match_1);
  define_method("types", "character", poly_idx__grammar__match, func__types__character__grammar__match_1);
  define_method("types", "value_range", poly_idx__grammar__match, func__types__value_range__grammar__match_1);
  define_method("types", "list", poly_idx__grammar__match, func__types__list__grammar__match_1);
  define_method("types", "object", poly_idx__grammar__search, func__types__object__grammar__search_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__grammar(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.grammar__match, create_function(type__grammar__match, -1));
  assign_value(&var.grammar__search, create_function(type__grammar__search, -1));
  initialize_future(var.types__grammar_object, get__types__object());
  initialize_future(var.types__grammar_node, get__types__object());
  assign_value(&var._expr_of, create_function(type__expr_of, -1));
  assign_value(&var._alternatives_of, create_function(type__alternatives_of, -1));
  assign_value(&var._setter_of, create_function(type__setter_of, -1));
  assign_value(&var._node_of, create_function(type__node_of, -1));
  assign_value(&var._function_of, create_function(type__function_of, -1));
  initialize_future(var.types__optional, var.types__grammar_object);
  initialize_future(var.std__optional, func__std__optional_1);
  initialize_future(var.types__many, var.types__grammar_object);
  initialize_future(var.std__many, func__std__many_1);
  initialize_future(var.types__some, var.types__grammar_object);
  initialize_future(var.std__some, func__std__some_1);
  initialize_future(var.types__alt, var.types__grammar_object);
  initialize_future(var.std__alt, func__std__alt_1);
  initialize_future(var.types__followed_by, var.types__grammar_object);
  initialize_future(var.std__followed_by, func__std__followed_by_1);
  initialize_future(var.types__not_followed_by, var.types__grammar_object);
  initialize_future(var.std__not_followed_by, func__std__not_followed_by_1);
  initialize_future(var.types__capture, var.types__grammar_object);
  initialize_future(var.std__capture, func__std__capture_1);
  initialize_future(var.types__multi_capture, var.types__grammar_object);
  initialize_future(var.std__multi_capture, func__std__multi_capture_1);
  initialize_future(var.types__span, var.types__grammar_object);
  initialize_future(var.std__span, func__std__span_1);
  initialize_future(var.types__multi_span, var.types__grammar_object);
  initialize_future(var.std__multi_span, func__std__multi_span_1);
  initialize_future(var.types__set_node, var.types__grammar_object);
  initialize_future(var.std__set_node, func__std__set_node_1);
  initialize_future(var.types__inspect_node, var.types__grammar_object);
  initialize_future(var.std__inspect_node, func__std__inspect_node_1);
  initialize_future(var.types__modify_node, var.types__grammar_object);
  initialize_future(var.std__modify_node, func__std__modify_node_1);
  initialize_future(var.types__check_node, var.types__grammar_object);
  initialize_future(var.std__check_node, func__std__check_node_1);
  initialize_future(var.types__grammar_action, var.types__grammar_object);
  initialize_future(var.std__grammar_action, func__std__grammar_action_1);
  initialize_future(var.types__set_field, var.types__grammar_object);
  initialize_future(var.std__set_field, func__std__set_field_1);
  initialize_future(var.std__END_OF_TEXT, var.types__grammar_object);
  initialize_future(var.std__LETTER, var.types__grammar_object);
  initialize_future(var.std__UPPER_CASE_LETTER, var.types__grammar_object);
  initialize_future(var.std__LOWER_CASE_LETTER, var.types__grammar_object);
  initialize_future(var.std__DIGIT, var.types__grammar_object);
  initialize_future(var.std__WHITESPACE_CHARACTER, var.types__grammar_object);
  initialize_future(var.std__PRINTABLE_CHARACTER, var.types__grammar_object);
  initialize_future(var.std__NON_SPACE_CHARACTER, var.types__grammar_object);
  initialize_future(var.std__ANY_CHARACTER, var.types__grammar_object);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__grammar(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__grammar);
}
