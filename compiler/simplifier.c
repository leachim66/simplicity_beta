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
IMPORT NODE *get_dynamic_slot(int id);
IMPORT void define_dynamic_slot(int id, NODE *node);
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define REGISTER register
#else
  #define REGISTER IMPORT
#endif
typedef struct FRAME {
  FUNC cont;
  struct FRAME *caller_frame;
  long caller_result_count;
  long slot_count;
  NODE *slots[0];
} FRAME;
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define ASM(x) asm(x)
#else
  #define ASM(x)
#endif
REGISTER FRAME *arguments ASM("r12");
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
IMPORT NODE *create_future(void);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *undefined;
IMPORT NODE *create_continuation(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void register_dynamic(int *id_p);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
);
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void use_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void maybe_initialize_future(NODE *var, NODE *val);
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
static NODE_GETTER get__DYNAMIC_MULTI;
static NODE_GETTER get_value_or_future__DYNAMIC_MULTI;
static NODE_GETTER get__DYNAMIC_SINGLE;
static NODE_GETTER get_value_or_future__DYNAMIC_SINGLE;
static NODE_GETTER get__NONE;
static NODE_GETTER get_value_or_future__NONE;
static NODE_GETTER get__POLYMORPHIC;
static NODE_GETTER get_value_or_future__POLYMORPHIC;
static NODE_GETTER get__STATIC_MULTI;
static NODE_GETTER get_value_or_future__STATIC_MULTI;
static NODE_GETTER get__STATIC_SINGLE;
static NODE_GETTER get_value_or_future__STATIC_SINGLE;
static NODE_GETTER get__SyntaxError;
static NODE_GETTER get_value_or_future__SyntaxError;
static NODE_GETTER get__actions;
static NODE_SETTER set__actions;
static NODE_GETTER get__already_defined_names;
static NODE_SETTER define__already_defined_names;
static NODE_GETTER get__alt;
static NODE_GETTER get_value_or_future__alt;
static int poly_idx__arguments_of;
static NODE_GETTER get__arguments_of;
static NODE_GETTER get__assignment;
static NODE_GETTER get_value_or_future__assignment;
static NODE_GETTER get__attribute_function_pair;
static NODE_GETTER get_value_or_future__attribute_function_pair;
static NODE_GETTER get__attribute_kind_of;
static NODE_GETTER get_value_or_future__attribute_kind_of;
static NODE_GETTER get__attribute_value_pair;
static NODE_GETTER get_value_or_future__attribute_value_pair;
static NODE_GETTER get__before;
static NODE_GETTER get_value_or_future__before;
static NODE_GETTER get__behind;
static NODE_GETTER get_value_or_future__behind;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__check_usage;
static NODE_GETTER get_value_or_future__check_usage;
static NODE_GETTER get__compiler__attribute_function_pair;
static NODE_GETTER get_value_or_future__compiler__attribute_function_pair;
static NODE_GETTER get__compiler__attribute_value_pair;
static NODE_GETTER get_value_or_future__compiler__attribute_value_pair;
static NODE_GETTER get__compiler__body;
static NODE_GETTER get_value_or_future__compiler__body;
static NODE_GETTER get__compiler__c_body;
static NODE_GETTER get_value_or_future__compiler__c_body;
static NODE_GETTER get__compiler__c_code;
static NODE_GETTER get_value_or_future__compiler__c_code;
static NODE_GETTER get__compiler__call;
static NODE_GETTER get_value_or_future__compiler__call;
static NODE_GETTER get__compiler__function_call;
static NODE_GETTER get_value_or_future__compiler__function_call;
static NODE_GETTER get__compiler__temp_idx;
static NODE_SETTER set__compiler__temp_idx;
static NODE_SETTER define__compiler__temp_idx;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static int poly_idx__continuation_of;
static NODE_GETTER get__continuation_of;
static int poly_idx__default_value_of;
static NODE_GETTER get__default_value_of;
static NODE_GETTER get__defined_functions;
static NODE_SETTER set__defined_functions;
static NODE_GETTER get__defined_names_of;
static NODE_GETTER get_value_or_future__defined_names_of;
static NODE_GETTER get__defined_nodes;
static NODE_SETTER set__defined_nodes;
static NODE_GETTER get__defined_structs;
static NODE_SETTER set__defined_structs;
static NODE_GETTER get__definitions;
static NODE_SETTER set__definitions;
static NODE_SETTER define__definitions;
static int poly_idx__definitions_of;
static NODE_GETTER get__definitions_of;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__drop;
static NODE_GETTER get_value_or_future__drop;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static int poly_idx__end_position_of;
static NODE_GETTER get__end_position_of;
static NODE_GETTER get__extend_to;
static NODE_GETTER get_value_or_future__extend_to;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static int poly_idx__fragment_of;
static NODE_GETTER get__fragment_of;
static int poly_idx__functor_of;
static NODE_GETTER get__functor_of;
static int poly_idx__identifier_of;
static NODE_GETTER get__identifier_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static int poly_idx__inherited_names_of;
static NODE_GETTER get__inherited_names_of;
static NODE_GETTER get__is_a_constant;
static NODE_GETTER get_value_or_future__is_a_constant;
static NODE_GETTER get__is_a_definition;
static NODE_GETTER get_value_or_future__is_a_definition;
static NODE_GETTER get__is_a_function_call;
static NODE_GETTER get_value_or_future__is_a_function_call;
static NODE_GETTER get__is_a_list;
static NODE_GETTER get_value_or_future__is_a_list;
static NODE_GETTER get__is_a_method_definition;
static NODE_GETTER get_value_or_future__is_a_method_definition;
static NODE_GETTER get__is_a_multi_assign_definition;
static NODE_GETTER get_value_or_future__is_a_multi_assign_definition;
static NODE_GETTER get__is_a_remark;
static NODE_GETTER get_value_or_future__is_a_remark;
static NODE_GETTER get__is_a_single_assign_definition;
static NODE_GETTER get_value_or_future__is_a_single_assign_definition;
static NODE_GETTER get__is_a_static_single_definition;
static NODE_GETTER get_value_or_future__is_a_static_single_definition;
static NODE_GETTER get__is_a_temporary;
static NODE_GETTER get_value_or_future__is_a_temporary;
static NODE_GETTER get__is_an_assignment;
static NODE_GETTER get_value_or_future__is_an_assignment;
static NODE_GETTER get__is_an_attribute_access;
static NODE_GETTER get_value_or_future__is_an_attribute_access;
static int poly_idx__is_an_expanded_item;
static NODE_GETTER get__is_an_expanded_item;
static NODE_GETTER get__is_an_identifier;
static NODE_GETTER get_value_or_future__is_an_identifier;
static int poly_idx__is_an_initialization;
static NODE_GETTER get__is_an_initialization;
static int poly_idx__is_an_optional_item;
static NODE_GETTER get__is_an_optional_item;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__is_single_assign;
static NODE_GETTER get_value_or_future__is_single_assign;
static NODE_GETTER get__kind_of;
static NODE_GETTER get_value_or_future__kind_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__might_be_constant;
static NODE_GETTER get_value_or_future__might_be_constant;
static int poly_idx__name_of;
static NODE_GETTER get__name_of;
static int poly_idx__output_arguments_of;
static NODE_GETTER get__output_arguments_of;
static int poly_idx__parameters_of;
static NODE_GETTER get__parameters_of;
static NODE_GETTER get__peek;
static NODE_GETTER get_value_or_future__peek;
static NODE_GETTER get__pop;
static NODE_GETTER get_value_or_future__pop;
static NODE_GETTER get__procedure_call;
static NODE_GETTER get_value_or_future__procedure_call;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static int poly_idx__result_count_of;
static NODE_GETTER get__result_count_of;
static NODE_GETTER get__show_compiler_debug_info;
static NODE_GETTER get_value_or_future__show_compiler_debug_info;
static int poly_idx__simplify_expression;
static NODE_GETTER get__simplify_expression;
static int poly_idx__simplify_statement;
static NODE_GETTER get__simplify_statement;
static NODE_GETTER get__source_of;
static NODE_GETTER get_value_or_future__source_of;
static int poly_idx__source_position_of;
static NODE_GETTER get__source_position_of;
static NODE_GETTER get__statements;
static NODE_SETTER set__statements;
static NODE_SETTER define__statements;
static int poly_idx__statements_of;
static NODE_GETTER get__statements_of;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
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
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__temp_idx;
static NODE_SETTER set__temp_idx;
static NODE_GETTER get__temporary;
static NODE_GETTER get_value_or_future__temporary;
static int poly_idx__temporary_count_of;
static NODE_GETTER get__temporary_count_of;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__grammar_node;
static NODE_GETTER get_value_or_future__types__grammar_node;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__update_each;
static NODE_GETTER get_value_or_future__update_each;
static NODE_GETTER get__use_inline_c;
static NODE_SETTER set__use_inline_c;
static NODE_GETTER get__used_names_of;
static NODE_GETTER get_value_or_future__used_names_of;
static NODE_GETTER get__variable_kind_of;
static NODE_GETTER get_value_or_future__variable_kind_of;
static struct {
  NODE *_temporary_identifier;
  NODE *_simplify_arguments;
  NODE *_do_store;
  NODE *_store_result;
  NODE *compiler__simplify_statement;
  NODE *compiler__simplify_expression;
  NODE *compiler__check_usage;
} var;
static const char *var_names[] = {
  "temporary_identifier",
  "simplify_arguments",
  "do_store",
  "store_result"
};
static int poly_idx__compiler__simplify_statement;
static void type__compiler__simplify_statement(void);
static NODE *get__compiler__simplify_statement(void) {
  return var.compiler__simplify_statement;
}
static int poly_idx__compiler__simplify_expression;
static void type__compiler__simplify_expression(void);
static NODE *get__compiler__simplify_expression(void) {
  return var.compiler__simplify_expression;
}
static int dyna_idx__defined_names;
static NODE *get__defined_names(void) {
  return get_dynamic_slot(dyna_idx__defined_names);
}
static void define__defined_names(NODE *node) {
  define_dynamic_slot(dyna_idx__defined_names, node);
}
static int dyna_idx__inherited_names;
static NODE *get__inherited_names(void) {
  return get_dynamic_slot(dyna_idx__inherited_names);
}
static void define__inherited_names(NODE *node) {
  define_dynamic_slot(dyna_idx__inherited_names, node);
}
static NODE *func__temporary_identifier_1;
static void entry__temporary_identifier_1(void);
static FRAME_INFO frame__temporary_identifier_1 = {1, {"id"}};
static void cont__temporary_identifier_2(void);
static NODE *string__421f524a80420288;
static void cont__temporary_identifier_4(void);
static NODE *func__simplify_arguments_1;
static void entry__simplify_arguments_1(void);
static FRAME_INFO frame__simplify_arguments_1 = {4, {"self", "arguments", "final_destinations", "output_arguments"}};
static void cont__simplify_arguments_2(void);
static NODE *func__simplify_arguments_3;
static void entry__simplify_arguments_3(void);
static FRAME_INFO frame__simplify_arguments_3 = {1, {"argument"}};
static NODE *func__simplify_arguments_4;
static void entry__simplify_arguments_4(void);
static FRAME_INFO frame__simplify_arguments_4 = {1, {"argument"}};
static void cont__simplify_arguments_5(void);
static NODE *func__simplify_arguments_6;
static void entry__simplify_arguments_6(void);
static FRAME_INFO frame__simplify_arguments_6 = {1, {"argument"}};
static void cont__simplify_arguments_7(void);
static NODE *func__simplify_arguments_8;
static void entry__simplify_arguments_8(void);
static FRAME_INFO frame__simplify_arguments_8 = {1, {"argument"}};
static void cont__simplify_arguments_9(void);
static NODE *func__simplify_arguments_10;
static void entry__simplify_arguments_10(void);
static FRAME_INFO frame__simplify_arguments_10 = {1, {"argument"}};
static void cont__simplify_arguments_11(void);
static NODE *func__simplify_arguments_12;
static void entry__simplify_arguments_12(void);
static FRAME_INFO frame__simplify_arguments_12 = {1, {"argument"}};
static void cont__simplify_arguments_13(void);
static void cont__simplify_arguments_14(void);
static void cont__simplify_arguments_15(void);
static void cont__simplify_arguments_16(void);
static void cont__simplify_arguments_17(void);
static NODE *func__simplify_arguments_18;
static void entry__simplify_arguments_18(void);
static FRAME_INFO frame__simplify_arguments_18 = {4, {"output_arguments", "final_destinations", "self", "first_temporary_index"}};
static NODE *func__simplify_arguments_19;
static void entry__simplify_arguments_19(void);
static FRAME_INFO frame__simplify_arguments_19 = {3, {"break", "output_arguments", "first_temporary_index"}};
static NODE *func__simplify_arguments_20;
static void entry__simplify_arguments_20(void);
static FRAME_INFO frame__simplify_arguments_20 = {5, {"idx", "argument", "output_arguments", "first_temporary_index", "break"}};
static void cont__simplify_arguments_21(void);
static NODE *func__simplify_arguments_22;
static void entry__simplify_arguments_22(void);
static FRAME_INFO frame__simplify_arguments_22 = {2, {"argument", "output_arguments"}};
static void cont__simplify_arguments_23(void);
static NODE *func__simplify_arguments_24;
static void entry__simplify_arguments_24(void);
static FRAME_INFO frame__simplify_arguments_24 = {1, {"output_arguments"}};
static void cont__simplify_arguments_25(void);
static void cont__simplify_arguments_26(void);
static void cont__simplify_arguments_27(void);
static NODE *func__simplify_arguments_28;
static void entry__simplify_arguments_28(void);
static FRAME_INFO frame__simplify_arguments_28 = {1, {"argument"}};
static void cont__simplify_arguments_29(void);
static void cont__simplify_arguments_30(void);
static void cont__simplify_arguments_31(void);
static NODE *func__simplify_arguments_32;
static void entry__simplify_arguments_32(void);
static FRAME_INFO frame__simplify_arguments_32 = {3, {"first_temporary_index", "idx", "break"}};
static void cont__simplify_arguments_33(void);
static void cont__simplify_arguments_34(void);
static void cont__simplify_arguments_35(void);
static NODE *func__simplify_arguments_36;
static void entry__simplify_arguments_36(void);
static FRAME_INFO frame__simplify_arguments_36 = {3, {"final_destinations", "output_arguments", "first_temporary_index"}};
static NODE *func__simplify_arguments_37;
static void entry__simplify_arguments_37(void);
static FRAME_INFO frame__simplify_arguments_37 = {4, {"idx", "argument", "first_temporary_index", "final_destinations"}};
static void cont__simplify_arguments_38(void);
static NODE *func__simplify_arguments_39;
static void entry__simplify_arguments_39(void);
static FRAME_INFO frame__simplify_arguments_39 = {1, {"argument"}};
static void cont__simplify_arguments_40(void);
static void cont__simplify_arguments_41(void);
static NODE *func__simplify_arguments_42;
static void entry__simplify_arguments_42(void);
static FRAME_INFO frame__simplify_arguments_42 = {1, {"final_destinations"}};
static void cont__simplify_arguments_43(void);
static NODE *func__simplify_arguments_44;
static void entry__simplify_arguments_44(void);
static FRAME_INFO frame__simplify_arguments_44 = {3, {"argument", "final_destinations", "temp"}};
static void cont__simplify_arguments_45(void);
static NODE *func__simplify_arguments_46;
static void entry__simplify_arguments_46(void);
static FRAME_INFO frame__simplify_arguments_46 = {2, {"argument", "temp"}};
static void cont__simplify_arguments_47(void);
static NODE *func__simplify_arguments_48;
static void entry__simplify_arguments_48(void);
static FRAME_INFO frame__simplify_arguments_48 = {2, {"argument", "temp"}};
static NODE *func__simplify_arguments_49;
static void entry__simplify_arguments_49(void);
static FRAME_INFO frame__simplify_arguments_49 = {2, {"argument", "temp"}};
static void cont__simplify_arguments_50(void);
static NODE *func__simplify_arguments_51;
static void entry__simplify_arguments_51(void);
static FRAME_INFO frame__simplify_arguments_51 = {2, {"argument", "temp"}};
static void cont__simplify_arguments_52(void);
static void cont__simplify_arguments_53(void);
static void cont__simplify_arguments_54(void);
static void cont__simplify_arguments_55(void);
static void cont__simplify_arguments_56(void);
static void cont__simplify_arguments_57(void);
static NODE *func__compiler__check_usage_1;
static void entry__compiler__check_usage_1(void);
static FRAME_INFO frame__compiler__check_usage_1 = {3, {"name", "definition", "info"}};
static void cont__compiler__check_usage_2(void);
static NODE *func__compiler__check_usage_3;
static void entry__compiler__check_usage_3(void);
static FRAME_INFO frame__compiler__check_usage_3 = {2, {"info", "name"}};
static void cont__compiler__check_usage_4(void);
static void cont__compiler__check_usage_5(void);
static NODE *func__compiler__check_usage_6;
static void entry__compiler__check_usage_6(void);
static FRAME_INFO frame__compiler__check_usage_6 = {2, {"info", "name"}};
static void cont__compiler__check_usage_7(void);
static NODE *string__9ee981055a49a5fe;
static NODE *string__578a5af303e9cc3;
static void cont__compiler__check_usage_10(void);
static NODE *func__compiler__check_usage_11;
static void entry__compiler__check_usage_11(void);
static FRAME_INFO frame__compiler__check_usage_11 = {2, {"info", "name"}};
static void cont__compiler__check_usage_12(void);
static void cont__compiler__check_usage_13(void);
static NODE *func__compiler__check_usage_14;
static void entry__compiler__check_usage_14(void);
static FRAME_INFO frame__compiler__check_usage_14 = {2, {"info", "name"}};
static void cont__compiler__check_usage_15(void);
static NODE *string__6b008858b3a1b4b2;
static void cont__compiler__check_usage_17(void);
static NODE *func__compiler__check_usage_18;
static void entry__compiler__check_usage_18(void);
static FRAME_INFO frame__compiler__check_usage_18 = {2, {"info", "name"}};
static void cont__compiler__check_usage_19(void);
static void cont__compiler__check_usage_20(void);
static NODE *func__compiler__check_usage_21;
static void entry__compiler__check_usage_21(void);
static FRAME_INFO frame__compiler__check_usage_21 = {2, {"info", "name"}};
static void cont__compiler__check_usage_22(void);
static NODE *string__2ddd7194c0185268;
static void cont__compiler__check_usage_24(void);
static NODE *func__compiler__check_usage_25;
static void entry__compiler__check_usage_25(void);
static FRAME_INFO frame__compiler__check_usage_25 = {2, {"info", "name"}};
static void cont__compiler__check_usage_26(void);
static void cont__compiler__check_usage_27(void);
static NODE *func__compiler__check_usage_28;
static void entry__compiler__check_usage_28(void);
static FRAME_INFO frame__compiler__check_usage_28 = {2, {"info", "name"}};
static void cont__compiler__check_usage_29(void);
static NODE *string__e971e37f901b36b;
static void cont__compiler__check_usage_31(void);
static NODE *func__compiler__check_usage_32;
static void entry__compiler__check_usage_32(void);
static FRAME_INFO frame__compiler__check_usage_32 = {2, {"info", "name"}};
static void cont__compiler__check_usage_33(void);
static void cont__compiler__check_usage_34(void);
static NODE *func__compiler__check_usage_35;
static void entry__compiler__check_usage_35(void);
static FRAME_INFO frame__compiler__check_usage_35 = {2, {"info", "name"}};
static void cont__compiler__check_usage_36(void);
static NODE *string__611f619f08c2e7ef;
static void cont__compiler__check_usage_38(void);
static NODE *get__compiler__check_usage(void) {
  return var.compiler__check_usage;
}
static NODE *func__types__grammar_node__simplify_statement_1;
static void entry__types__grammar_node__simplify_statement_1(void);
static FRAME_INFO frame__types__grammar_node__simplify_statement_1 = {1, {"self"}};
static NODE *string__4a1f5794bff5c237;
static void cont__types__grammar_node__simplify_statement_3(void);
static void cont__types__grammar_node__simplify_statement_4(void);
static NODE *func__types__grammar_node__simplify_expression_1;
static void entry__types__grammar_node__simplify_expression_1(void);
static FRAME_INFO frame__types__grammar_node__simplify_expression_1 = {1, {"self"}};
static NODE *string__5af95dddc656868;
static void cont__types__grammar_node__simplify_expression_3(void);
static NODE *func__compiler__body__simplify_expression_1;
static void entry__compiler__body__simplify_expression_1(void);
static FRAME_INFO frame__compiler__body__simplify_expression_1 = {2, {"self", "all_defined_names"}};
static NODE *string__867252dcb87a57b1;
static void cont__compiler__body__simplify_expression_3(void);
static void cont__compiler__body__simplify_expression_4(void);
static NODE *func__compiler__body__simplify_expression_5;
static void entry__compiler__body__simplify_expression_5(void);
static FRAME_INFO frame__compiler__body__simplify_expression_5 = {4, {"name", "info", "all_defined_names", "outer_info"}};
static void cont__compiler__body__simplify_expression_6(void);
static void cont__compiler__body__simplify_expression_7(void);
static NODE *func__compiler__body__simplify_expression_8;
static void entry__compiler__body__simplify_expression_8(void);
static FRAME_INFO frame__compiler__body__simplify_expression_8 = {2, {"info", "name"}};
static void cont__compiler__body__simplify_expression_9(void);
static NODE *string__b18861f6a8c886ba;
static NODE *string__ff65db3940410371;
static void cont__compiler__body__simplify_expression_12(void);
static NODE *func__compiler__body__simplify_expression_13;
static void entry__compiler__body__simplify_expression_13(void);
static FRAME_INFO frame__compiler__body__simplify_expression_13 = {3, {"all_defined_names", "name", "info"}};
static void cont__compiler__body__simplify_expression_14(void);
static void cont__compiler__body__simplify_expression_15(void);
static void cont__compiler__body__simplify_expression_16(void);
static NODE *func__compiler__body__simplify_expression_17;
static void entry__compiler__body__simplify_expression_17(void);
static FRAME_INFO frame__compiler__body__simplify_expression_17 = {5, {"name", "info", "all_defined_names", "self", "definition"}};
static void cont__compiler__body__simplify_expression_18(void);
static void cont__compiler__body__simplify_expression_19(void);
static NODE *func__compiler__body__simplify_expression_20;
static void entry__compiler__body__simplify_expression_20(void);
static FRAME_INFO frame__compiler__body__simplify_expression_20 = {4, {"name", "definition", "info", "self"}};
static void cont__compiler__body__simplify_expression_21(void);
static void cont__compiler__body__simplify_expression_22(void);
static void cont__compiler__body__simplify_expression_23(void);
static NODE *func__compiler__body__simplify_expression_24;
static void entry__compiler__body__simplify_expression_24(void);
static FRAME_INFO frame__compiler__body__simplify_expression_24 = {1, {"name"}};
static void cont__compiler__body__simplify_expression_25(void);
static void cont__compiler__body__simplify_expression_26(void);
static void cont__compiler__body__simplify_expression_27(void);
static NODE *func__compiler__body__simplify_expression_28;
static void entry__compiler__body__simplify_expression_28(void);
static FRAME_INFO frame__compiler__body__simplify_expression_28 = {3, {"self", "name", "info"}};
static void cont__compiler__body__simplify_expression_29(void);
static void cont__compiler__body__simplify_expression_30(void);
static void cont__compiler__body__simplify_expression_31(void);
static NODE *func__compiler__body__simplify_expression_32;
static void entry__compiler__body__simplify_expression_32(void);
static FRAME_INFO frame__compiler__body__simplify_expression_32 = {4, {"return__4", "self", "all_defined_names", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_33(void);
static void cont__compiler__body__simplify_expression_34(void);
static void cont__compiler__body__simplify_expression_35(void);
static NODE *func__compiler__body__simplify_expression_36;
static void entry__compiler__body__simplify_expression_36(void);
static FRAME_INFO frame__compiler__body__simplify_expression_36 = {3, {"parameter", "max_temp_idx", "default_value"}};
static void cont__compiler__body__simplify_expression_37(void);
static void cont__compiler__body__simplify_expression_38(void);
static NODE *func__compiler__body__simplify_expression_39;
static void entry__compiler__body__simplify_expression_39(void);
static FRAME_INFO frame__compiler__body__simplify_expression_39 = {3, {"default_value", "parameter", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_40(void);
static NODE *func__compiler__body__simplify_expression_41;
static void entry__compiler__body__simplify_expression_41(void);
static FRAME_INFO frame__compiler__body__simplify_expression_41 = {5, {"return__1", "parameter", "default_value", "max_temp_idx", "identifier"}};
static void cont__compiler__body__simplify_expression_42(void);
static void cont__compiler__body__simplify_expression_43(void);
static void cont__compiler__body__simplify_expression_44(void);
static void cont__compiler__body__simplify_expression_45(void);
static void cont__compiler__body__simplify_expression_46(void);
static void cont__compiler__body__simplify_expression_47(void);
static void cont__compiler__body__simplify_expression_48(void);
static void cont__compiler__body__simplify_expression_49(void);
static NODE *func__compiler__body__simplify_expression_50;
static void entry__compiler__body__simplify_expression_50(void);
static FRAME_INFO frame__compiler__body__simplify_expression_50 = {2, {"default_value", "parameter"}};
static void cont__compiler__body__simplify_expression_51(void);
static void cont__compiler__body__simplify_expression_52(void);
static void cont__compiler__body__simplify_expression_53(void);
static void cont__compiler__body__simplify_expression_54(void);
static NODE *func__compiler__body__simplify_expression_55;
static void entry__compiler__body__simplify_expression_55(void);
static FRAME_INFO frame__compiler__body__simplify_expression_55 = {2, {"statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_56(void);
static NODE *func__compiler__body__simplify_expression_57;
static void entry__compiler__body__simplify_expression_57(void);
static FRAME_INFO frame__compiler__body__simplify_expression_57 = {2, {"statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_58(void);
static NODE *func__compiler__body__simplify_expression_59;
static void entry__compiler__body__simplify_expression_59(void);
static FRAME_INFO frame__compiler__body__simplify_expression_59 = {1, {"statement"}};
static void cont__compiler__body__simplify_expression_60(void);
static void cont__compiler__body__simplify_expression_61(void);
static void cont__compiler__body__simplify_expression_62(void);
static NODE *func__compiler__body__simplify_expression_63;
static void entry__compiler__body__simplify_expression_63(void);
static FRAME_INFO frame__compiler__body__simplify_expression_63 = {1, {"statement"}};
static void cont__compiler__body__simplify_expression_64(void);
static void cont__compiler__body__simplify_expression_65(void);
static void cont__compiler__body__simplify_expression_66(void);
static void cont__compiler__body__simplify_expression_67(void);
static void cont__compiler__body__simplify_expression_68(void);
static NODE *func__compiler__body__simplify_expression_69;
static void entry__compiler__body__simplify_expression_69(void);
static FRAME_INFO frame__compiler__body__simplify_expression_69 = {3, {"return__2", "statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_70(void);
static void cont__compiler__body__simplify_expression_71(void);
static void cont__compiler__body__simplify_expression_72(void);
static void cont__compiler__body__simplify_expression_73(void);
static NODE *func__compiler__body__simplify_expression_74;
static void entry__compiler__body__simplify_expression_74(void);
static FRAME_INFO frame__compiler__body__simplify_expression_74 = {2, {"statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_75(void);
static NODE *func__compiler__body__simplify_expression_76;
static void entry__compiler__body__simplify_expression_76(void);
static FRAME_INFO frame__compiler__body__simplify_expression_76 = {2, {"statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_77(void);
static NODE *func__compiler__body__simplify_expression_78;
static void entry__compiler__body__simplify_expression_78(void);
static FRAME_INFO frame__compiler__body__simplify_expression_78 = {1, {"statement"}};
static void cont__compiler__body__simplify_expression_79(void);
static void cont__compiler__body__simplify_expression_80(void);
static void cont__compiler__body__simplify_expression_81(void);
static NODE *func__compiler__body__simplify_expression_82;
static void entry__compiler__body__simplify_expression_82(void);
static FRAME_INFO frame__compiler__body__simplify_expression_82 = {1, {"statement"}};
static void cont__compiler__body__simplify_expression_83(void);
static void cont__compiler__body__simplify_expression_84(void);
static void cont__compiler__body__simplify_expression_85(void);
static void cont__compiler__body__simplify_expression_86(void);
static void cont__compiler__body__simplify_expression_87(void);
static NODE *func__compiler__body__simplify_expression_88;
static void entry__compiler__body__simplify_expression_88(void);
static FRAME_INFO frame__compiler__body__simplify_expression_88 = {3, {"return__3", "statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_89(void);
static void cont__compiler__body__simplify_expression_90(void);
static void cont__compiler__body__simplify_expression_91(void);
static void cont__compiler__body__simplify_expression_92(void);
static void cont__compiler__body__simplify_expression_93(void);
static void cont__compiler__body__simplify_expression_94(void);
static NODE *func__compiler__body__simplify_expression_95;
static void entry__compiler__body__simplify_expression_95(void);
static FRAME_INFO frame__compiler__body__simplify_expression_95 = {2, {"self", "temp"}};
static void cont__compiler__body__simplify_expression_96(void);
static void cont__compiler__body__simplify_expression_97(void);
static void cont__compiler__body__simplify_expression_98(void);
static void cont__compiler__body__simplify_expression_99(void);
static void cont__compiler__body__simplify_expression_100(void);
static void cont__compiler__body__simplify_expression_101(void);
static void cont__compiler__body__simplify_expression_102(void);
static void cont__compiler__body__simplify_expression_103(void);
static NODE *func__do_store_1;
static void entry__do_store_1(void);
static FRAME_INFO frame__do_store_1 = {6, {"functor", "arguments", "result", "rest", "infos", "info"}};
static void cont__do_store_2(void);
static void cont__do_store_3(void);
static NODE *func__do_store_4;
static void entry__do_store_4(void);
static FRAME_INFO frame__do_store_4 = {6, {"arguments", "rest", "functor", "info", "result", "infos"}};
static NODE *func__do_store_5;
static void entry__do_store_5(void);
static FRAME_INFO frame__do_store_5 = {1, {"argument"}};
static void cont__do_store_6(void);
static void cont__do_store_7(void);
static void cont__do_store_8(void);
static void cont__do_store_9(void);
static NODE *func__do_store_10;
static void entry__do_store_10(void);
static FRAME_INFO frame__do_store_10 = {7, {"functor", "arguments", "info", "rest", "result", "infos", "temp"}};
static void cont__do_store_11(void);
static void cont__do_store_12(void);
static void cont__do_store_13(void);
static void cont__do_store_14(void);
static void cont__do_store_15(void);
static void cont__do_store_16(void);
static void cont__do_store_17(void);
static void cont__do_store_18(void);
static void cont__do_store_19(void);
static void cont__do_store_20(void);
static void cont__do_store_21(void);
static void cont__do_store_22(void);
static void cont__do_store_23(void);
static void cont__do_store_24(void);
static void cont__do_store_25(void);
static void cont__do_store_26(void);
static void cont__do_store_27(void);
static NODE *func__do_store_28;
static void entry__do_store_28(void);
static FRAME_INFO frame__do_store_28 = {7, {"rest", "arguments", "functor", "info", "result", "infos", "attribute_pair"}};
static void cont__do_store_29(void);
static void cont__do_store_30(void);
static NODE *func__do_store_31;
static void entry__do_store_31(void);
static FRAME_INFO frame__do_store_31 = {7, {"arguments", "functor", "info", "rest", "result", "infos", "temp"}};
static void cont__do_store_32(void);
static void cont__do_store_33(void);
static void cont__do_store_34(void);
static void cont__do_store_35(void);
static void cont__do_store_36(void);
static void cont__do_store_37(void);
static void cont__do_store_38(void);
static void cont__do_store_39(void);
static void cont__do_store_40(void);
static void cont__do_store_41(void);
static void cont__do_store_42(void);
static void cont__do_store_43(void);
static void cont__do_store_44(void);
static NODE *func__do_store_45;
static void entry__do_store_45(void);
static FRAME_INFO frame__do_store_45 = {0, {}};
static NODE *func__do_store_46;
static void entry__do_store_46(void);
static FRAME_INFO frame__do_store_46 = {0, {}};
static void cont__do_store_47(void);
static void cont__do_store_48(void);
static void cont__do_store_49(void);
static void cont__do_store_50(void);
static void cont__do_store_51(void);
static void cont__do_store_52(void);
static void cont__do_store_53(void);
static void cont__do_store_54(void);
static void cont__do_store_55(void);
static void cont__do_store_56(void);
static NODE *func__store_result_1;
static void entry__store_result_1(void);
static FRAME_INFO frame__store_result_1 = {5, {"destination", "result", "rest", "infos", "arguments"}};
static void cont__store_result_2(void);
static void cont__store_result_3(void);
static void cont__store_result_4(void);
static NODE *func__store_result_5;
static void entry__store_result_5(void);
static FRAME_INFO frame__store_result_5 = {5, {"arguments", "destination", "result", "rest", "infos"}};
static void cont__store_result_6(void);
static void cont__store_result_7(void);
static NODE *func__store_result_8;
static void entry__store_result_8(void);
static FRAME_INFO frame__store_result_8 = {5, {"arguments", "destination", "result", "rest", "infos"}};
static void cont__store_result_9(void);
static NODE *func__store_result_10;
static void entry__store_result_10(void);
static FRAME_INFO frame__store_result_10 = {5, {"arguments", "result", "rest", "destination", "infos"}};
static void cont__store_result_11(void);
static void cont__store_result_12(void);
static NODE *func__store_result_13;
static void entry__store_result_13(void);
static FRAME_INFO frame__store_result_13 = {6, {"destination", "arguments", "result", "rest", "infos", "functor"}};
static void cont__store_result_14(void);
static void cont__store_result_15(void);
static NODE *func__store_result_16;
static void entry__store_result_16(void);
static FRAME_INFO frame__store_result_16 = {5, {"functor", "arguments", "result", "rest", "infos"}};
static NODE *func__store_result_17;
static void entry__store_result_17(void);
static FRAME_INFO frame__store_result_17 = {5, {"functor", "result", "rest", "arguments", "infos"}};
static void cont__store_result_18(void);
static NODE *func__compiler__call__simplify_statement_1;
static void entry__compiler__call__simplify_statement_1(void);
static FRAME_INFO frame__compiler__call__simplify_statement_1 = {3, {"self", "return", "final_destinations"}};
static NODE *string__8629329e514f7a7a;
static void cont__compiler__call__simplify_statement_3(void);
static void cont__compiler__call__simplify_statement_4(void);
static NODE *func__compiler__call__simplify_statement_5;
static void entry__compiler__call__simplify_statement_5(void);
static FRAME_INFO frame__compiler__call__simplify_statement_5 = {1, {"self"}};
static void cont__compiler__call__simplify_statement_6(void);
static void cont__compiler__call__simplify_statement_7(void);
static void cont__compiler__call__simplify_statement_8(void);
static void cont__compiler__call__simplify_statement_9(void);
static NODE *func__compiler__call__simplify_statement_10;
static void entry__compiler__call__simplify_statement_10(void);
static FRAME_INFO frame__compiler__call__simplify_statement_10 = {2, {"self", "source"}};
static void cont__compiler__call__simplify_statement_11(void);
static void cont__compiler__call__simplify_statement_12(void);
static void cont__compiler__call__simplify_statement_13(void);
static NODE *func__compiler__call__simplify_statement_14;
static void entry__compiler__call__simplify_statement_14(void);
static FRAME_INFO frame__compiler__call__simplify_statement_14 = {2, {"self", "source"}};
static void cont__compiler__call__simplify_statement_15(void);
static void cont__compiler__call__simplify_statement_16(void);
static void cont__compiler__call__simplify_statement_17(void);
static void cont__compiler__call__simplify_statement_18(void);
static void cont__compiler__call__simplify_statement_19(void);
static void cont__compiler__call__simplify_statement_20(void);
static void cont__compiler__call__simplify_statement_21(void);
static void cont__compiler__call__simplify_statement_22(void);
static void cont__compiler__call__simplify_statement_23(void);
static void cont__compiler__call__simplify_statement_24(void);
static void cont__compiler__call__simplify_statement_25(void);
static void cont__compiler__call__simplify_statement_26(void);
static void cont__compiler__call__simplify_statement_27(void);
static NODE *func__compiler__call__simplify_statement_28;
static void entry__compiler__call__simplify_statement_28(void);
static FRAME_INFO frame__compiler__call__simplify_statement_28 = {1, {"self"}};
static void cont__compiler__call__simplify_statement_29(void);
static void cont__compiler__call__simplify_statement_30(void);
static NODE *func__compiler__call__simplify_statement_31;
static void entry__compiler__call__simplify_statement_31(void);
static FRAME_INFO frame__compiler__call__simplify_statement_31 = {1, {"self"}};
static void cont__compiler__call__simplify_statement_32(void);
static void cont__compiler__call__simplify_statement_33(void);
static void cont__compiler__call__simplify_statement_34(void);
static void cont__compiler__call__simplify_statement_35(void);
static void cont__compiler__call__simplify_statement_36(void);
static NODE *func__compiler__call__simplify_statement_37;
static void entry__compiler__call__simplify_statement_37(void);
static FRAME_INFO frame__compiler__call__simplify_statement_37 = {1, {"self"}};
static void cont__compiler__call__simplify_statement_38(void);
static void cont__compiler__call__simplify_statement_39(void);
static void cont__compiler__call__simplify_statement_40(void);
static void cont__compiler__call__simplify_statement_41(void);
static void cont__compiler__call__simplify_statement_42(void);
static void cont__compiler__call__simplify_statement_43(void);
static void cont__compiler__call__simplify_statement_44(void);
static NODE *func__compiler__call__simplify_statement_45;
static void entry__compiler__call__simplify_statement_45(void);
static FRAME_INFO frame__compiler__call__simplify_statement_45 = {3, {"self", "return", "destination"}};
static void cont__compiler__call__simplify_statement_46(void);
static void cont__compiler__call__simplify_statement_47(void);
static void cont__compiler__call__simplify_statement_48(void);
static NODE *func__compiler__call__simplify_statement_49;
static void entry__compiler__call__simplify_statement_49(void);
static FRAME_INFO frame__compiler__call__simplify_statement_49 = {3, {"destination", "self", "return"}};
static void cont__compiler__call__simplify_statement_50(void);
static NODE *func__compiler__call__simplify_statement_51;
static void entry__compiler__call__simplify_statement_51(void);
static FRAME_INFO frame__compiler__call__simplify_statement_51 = {4, {"self", "destination", "return", "source"}};
static void cont__compiler__call__simplify_statement_52(void);
static void cont__compiler__call__simplify_statement_53(void);
static void cont__compiler__call__simplify_statement_54(void);
static void cont__compiler__call__simplify_statement_55(void);
static void cont__compiler__call__simplify_statement_56(void);
static NODE *func__compiler__call__simplify_statement_57;
static void entry__compiler__call__simplify_statement_57(void);
static FRAME_INFO frame__compiler__call__simplify_statement_57 = {3, {"destination", "source", "return"}};
static void cont__compiler__call__simplify_statement_58(void);
static void cont__compiler__call__simplify_statement_59(void);
static void cont__compiler__call__simplify_statement_60(void);
static NODE *func__compiler__call__simplify_statement_61;
static void entry__compiler__call__simplify_statement_61(void);
static FRAME_INFO frame__compiler__call__simplify_statement_61 = {3, {"source", "destination", "return"}};
static void cont__compiler__call__simplify_statement_62(void);
static NODE *func__compiler__call__simplify_statement_63;
static void entry__compiler__call__simplify_statement_63(void);
static FRAME_INFO frame__compiler__call__simplify_statement_63 = {1, {"source"}};
static void cont__compiler__call__simplify_statement_64(void);
static void cont__compiler__call__simplify_statement_65(void);
static NODE *func__compiler__call__simplify_statement_66;
static void entry__compiler__call__simplify_statement_66(void);
static FRAME_INFO frame__compiler__call__simplify_statement_66 = {3, {"destination", "source", "return"}};
static void cont__compiler__call__simplify_statement_67(void);
static void cont__compiler__call__simplify_statement_68(void);
static NODE *func__compiler__call__simplify_statement_69;
static void entry__compiler__call__simplify_statement_69(void);
static FRAME_INFO frame__compiler__call__simplify_statement_69 = {3, {"source", "destination", "self"}};
static void cont__compiler__call__simplify_statement_70(void);
static NODE *func__compiler__call__simplify_statement_71;
static void entry__compiler__call__simplify_statement_71(void);
static FRAME_INFO frame__compiler__call__simplify_statement_71 = {3, {"destination", "source", "self"}};
static void cont__compiler__call__simplify_statement_72(void);
static void cont__compiler__call__simplify_statement_73(void);
static void cont__compiler__call__simplify_statement_74(void);
static void cont__compiler__call__simplify_statement_75(void);
static void cont__compiler__call__simplify_statement_76(void);
static NODE *func__compiler__call__simplify_statement_77;
static void entry__compiler__call__simplify_statement_77(void);
static FRAME_INFO frame__compiler__call__simplify_statement_77 = {2, {"destination", "self"}};
static void cont__compiler__call__simplify_statement_78(void);
static void cont__compiler__call__simplify_statement_79(void);
static void cont__compiler__call__simplify_statement_80(void);
static void cont__compiler__call__simplify_statement_81(void);
static NODE *func__compiler__call__simplify_statement_82;
static void entry__compiler__call__simplify_statement_82(void);
static FRAME_INFO frame__compiler__call__simplify_statement_82 = {2, {"destination", "self"}};
static void cont__compiler__call__simplify_statement_83(void);
static void cont__compiler__call__simplify_statement_84(void);
static void cont__compiler__call__simplify_statement_85(void);
static void cont__compiler__call__simplify_statement_86(void);
static NODE *func__compiler__call__simplify_statement_87;
static void entry__compiler__call__simplify_statement_87(void);
static FRAME_INFO frame__compiler__call__simplify_statement_87 = {1, {"self"}};
static void cont__compiler__call__simplify_statement_88(void);
static NODE *func__compiler__call__simplify_statement_89;
static void entry__compiler__call__simplify_statement_89(void);
static FRAME_INFO frame__compiler__call__simplify_statement_89 = {1, {"argument"}};
static void cont__compiler__call__simplify_statement_90(void);
static NODE *func__compiler__call__simplify_statement_91;
static void entry__compiler__call__simplify_statement_91(void);
static FRAME_INFO frame__compiler__call__simplify_statement_91 = {1, {"argument"}};
static void cont__compiler__call__simplify_statement_92(void);
static void cont__compiler__call__simplify_statement_93(void);
static void cont__compiler__call__simplify_statement_94(void);
static void cont__compiler__call__simplify_statement_95(void);
static void cont__compiler__call__simplify_statement_96(void);
static void cont__compiler__call__simplify_statement_97(void);
static NODE *func__compiler__call__simplify_statement_98;
static void entry__compiler__call__simplify_statement_98(void);
static FRAME_INFO frame__compiler__call__simplify_statement_98 = {2, {"final_destinations", "self"}};
static NODE *func__compiler__call__simplify_statement_99;
static void entry__compiler__call__simplify_statement_99(void);
static FRAME_INFO frame__compiler__call__simplify_statement_99 = {3, {"idx", "destination", "self"}};
static void cont__compiler__call__simplify_statement_100(void);
static NODE *func__compiler__call__simplify_statement_101;
static void entry__compiler__call__simplify_statement_101(void);
static FRAME_INFO frame__compiler__call__simplify_statement_101 = {4, {"self", "idx", "destination", "result"}};
static void cont__compiler__call__simplify_statement_102(void);
static void cont__compiler__call__simplify_statement_103(void);
static void cont__compiler__call__simplify_statement_104(void);
static NODE *func__compiler__call__simplify_statement_105;
static void entry__compiler__call__simplify_statement_105(void);
static FRAME_INFO frame__compiler__call__simplify_statement_105 = {2, {"destination", "result"}};
static NODE *func__compiler__call__simplify_statement_106;
static void entry__compiler__call__simplify_statement_106(void);
static FRAME_INFO frame__compiler__call__simplify_statement_106 = {3, {"destination", "result", "identifier"}};
static void cont__compiler__call__simplify_statement_107(void);
static NODE *func__compiler__call__simplify_statement_108;
static void entry__compiler__call__simplify_statement_108(void);
static FRAME_INFO frame__compiler__call__simplify_statement_108 = {1, {"destination"}};
static NODE *func__compiler__call__simplify_statement_109;
static void entry__compiler__call__simplify_statement_109(void);
static FRAME_INFO frame__compiler__call__simplify_statement_109 = {1, {"destination"}};
static void cont__compiler__call__simplify_statement_110(void);
static void cont__compiler__call__simplify_statement_111(void);
static void cont__compiler__call__simplify_statement_112(void);
static void cont__compiler__call__simplify_statement_113(void);
static void cont__compiler__call__simplify_statement_114(void);
static void cont__compiler__call__simplify_statement_115(void);
static void cont__compiler__call__simplify_statement_116(void);
static void cont__compiler__call__simplify_statement_117(void);
static NODE *func__compiler__function_call__simplify_expression_1;
static void entry__compiler__function_call__simplify_expression_1(void);
static FRAME_INFO frame__compiler__function_call__simplify_expression_1 = {2, {"self", "temp"}};
static NODE *string__95014404e5c0e88d;
static void cont__compiler__function_call__simplify_expression_3(void);
static void cont__compiler__function_call__simplify_expression_4(void);
static void cont__compiler__function_call__simplify_expression_5(void);
static void cont__compiler__function_call__simplify_expression_6(void);
static void cont__compiler__function_call__simplify_expression_7(void);
static void cont__compiler__function_call__simplify_expression_8(void);
static void cont__compiler__function_call__simplify_expression_9(void);
static void cont__compiler__function_call__simplify_expression_10(void);
static void cont__compiler__function_call__simplify_expression_11(void);
static void cont__compiler__function_call__simplify_expression_12(void);
static NODE *func__compiler__attribute_value_pair__simplify_expression_1;
static void entry__compiler__attribute_value_pair__simplify_expression_1(void);
static FRAME_INFO frame__compiler__attribute_value_pair__simplify_expression_1 = {2, {"self", "dummy_destinations"}};
static NODE *string__cced2f4d969d3d03;
static void cont__compiler__attribute_value_pair__simplify_expression_3(void);
static void cont__compiler__attribute_value_pair__simplify_expression_4(void);
static NODE *func__compiler__attribute_function_pair__simplify_expression_1;
static void entry__compiler__attribute_function_pair__simplify_expression_1(void);
static FRAME_INFO frame__compiler__attribute_function_pair__simplify_expression_1 = {2, {"self", "dummy_destinations"}};
static NODE *string__83e573190949a328;
static void cont__compiler__attribute_function_pair__simplify_expression_3(void);
static void cont__compiler__attribute_function_pair__simplify_expression_4(void);
static NODE *func__compiler__c_code__simplify_statement_1;
static void entry__compiler__c_code__simplify_statement_1(void);
static FRAME_INFO frame__compiler__c_code__simplify_statement_1 = {1, {"self"}};
static NODE *string__1095e9f11fb0974b;
static void cont__compiler__c_code__simplify_statement_3(void);
static NODE *func__compiler__c_code__simplify_statement_4;
static void entry__compiler__c_code__simplify_statement_4(void);
static FRAME_INFO frame__compiler__c_code__simplify_statement_4 = {0, {}};
static void cont__compiler__c_code__simplify_statement_5(void);
static void cont__compiler__c_code__simplify_statement_6(void);
static NODE *func__compiler__c_code__simplify_statement_7;
static void entry__compiler__c_code__simplify_statement_7(void);
static FRAME_INFO frame__compiler__c_code__simplify_statement_7 = {2, {"self", "name"}};
static void cont__compiler__c_code__simplify_statement_8(void);
static void cont__compiler__c_code__simplify_statement_9(void);
static NODE *func__compiler__c_code__simplify_statement_10;
static void entry__compiler__c_code__simplify_statement_10(void);
static FRAME_INFO frame__compiler__c_code__simplify_statement_10 = {1, {"name"}};
static void cont__compiler__c_code__simplify_statement_11(void);
static void cont__compiler__c_code__simplify_statement_12(void);
static NODE *func__compiler__c_code__simplify_statement_13;
static void entry__compiler__c_code__simplify_statement_13(void);
static FRAME_INFO frame__compiler__c_code__simplify_statement_13 = {2, {"self", "name"}};
static void cont__compiler__c_code__simplify_statement_14(void);
static void cont__compiler__c_code__simplify_statement_15(void);
static NODE *func__compiler__c_code__simplify_statement_16;
static void entry__compiler__c_code__simplify_statement_16(void);
static FRAME_INFO frame__compiler__c_code__simplify_statement_16 = {2, {"name", "self"}};
static void cont__compiler__c_code__simplify_statement_17(void);
static void cont__compiler__c_code__simplify_statement_18(void);
static NODE *func__compiler__c_code__simplify_statement_19;
static void entry__compiler__c_code__simplify_statement_19(void);
static FRAME_INFO frame__compiler__c_code__simplify_statement_19 = {2, {"self", "name"}};
static void cont__compiler__c_code__simplify_statement_20(void);
static void cont__compiler__c_code__simplify_statement_21(void);
static void cont__compiler__c_code__simplify_statement_22(void);
static void cont__compiler__c_code__simplify_statement_23(void);
static void cont__compiler__c_code__simplify_statement_24(void);
static NODE *func__compiler__c_code__simplify_statement_25;
static void entry__compiler__c_code__simplify_statement_25(void);
static FRAME_INFO frame__compiler__c_code__simplify_statement_25 = {1, {"name"}};
static void cont__compiler__c_code__simplify_statement_26(void);
static void cont__compiler__c_code__simplify_statement_27(void);
static NODE *string__7c1f530901a312a3;
static NODE *string__1e0aea8b5d407d5c;
static NODE *string__46c0af9104ada08e;
static void cont__compiler__c_code__simplify_statement_31(void);
static void cont__compiler__c_code__simplify_statement_32(void);
static NODE *func__compiler__c_body__simplify_expression_1;
static void entry__compiler__c_body__simplify_expression_1(void);
static FRAME_INFO frame__compiler__c_body__simplify_expression_1 = {1, {"self"}};
static NODE *string__1295e9f11fb09757;
static void cont__compiler__c_body__simplify_expression_3(void);
static NODE *func__compiler__c_body__simplify_expression_4;
static void entry__compiler__c_body__simplify_expression_4(void);
static FRAME_INFO frame__compiler__c_body__simplify_expression_4 = {0, {}};
static void cont__compiler__c_body__simplify_expression_5(void);
void run__simplifier(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__compiler__simplify_statement, NULL, 30, 30, 2, 29},
  {type__compiler__simplify_expression, NULL, 31, 31, 2, 30},
  {run__simplifier, NULL, 34, 34, 1, 28},
  {entry__temporary_identifier_1, NULL, 37, 37, 3, 15},
  {cont__temporary_identifier_2, &frame__temporary_identifier_1, 38, 38, 26, 44},
  {cont__temporary_identifier_4, &frame__temporary_identifier_1, 39, 39, 3, 7},
  {entry__simplify_arguments_6, NULL, 47, 47, 9, 37},
  {cont__simplify_arguments_7, &frame__simplify_arguments_6, 48, 48, 42, 42},
  {entry__simplify_arguments_4, NULL, 45, 45, 10, 37},
  {cont__simplify_arguments_5, &frame__simplify_arguments_4, 45, 48, 7, 42},
  {entry__simplify_arguments_10, NULL, 51, 51, 9, 37},
  {cont__simplify_arguments_11, &frame__simplify_arguments_10, 52, 52, 42, 42},
  {entry__simplify_arguments_8, NULL, 49, 49, 10, 37},
  {cont__simplify_arguments_9, &frame__simplify_arguments_8, 49, 52, 7, 42},
  {entry__simplify_arguments_12, NULL, 54, 54, 9, 37},
  {cont__simplify_arguments_13, &frame__simplify_arguments_12, 54, 54, 37, 37},
  {entry__simplify_arguments_3, NULL, 44, 54, 5, 38},
  {cont__simplify_arguments_14, &frame__simplify_arguments_3, },
  {entry__simplify_arguments_24, NULL, 71, 71, 15, 41},
  {cont__simplify_arguments_25, &frame__simplify_arguments_24, 71, 71, 15, 46},
  {cont__simplify_arguments_26, &frame__simplify_arguments_24, 71, 71, 15, 46},
  {entry__simplify_arguments_28, NULL, 72, 72, 13, 49},
  {cont__simplify_arguments_29, &frame__simplify_arguments_28, 72, 72, 13, 49},
  {entry__simplify_arguments_22, NULL, 70, 70, 15, 52},
  {cont__simplify_arguments_23, &frame__simplify_arguments_22, 69, 71, 13, 45},
  {cont__simplify_arguments_27, &frame__simplify_arguments_22, 72, 72, 13, 49},
  {cont__simplify_arguments_30, &frame__simplify_arguments_22, },
  {entry__simplify_arguments_32, NULL, 75, 75, 13, 17},
  {entry__simplify_arguments_20, NULL, 68, 68, 13, 37},
  {cont__simplify_arguments_21, &frame__simplify_arguments_20, },
  {cont__simplify_arguments_31, &frame__simplify_arguments_20, 66, 75, 9, 18},
  {entry__simplify_arguments_19, NULL, 65, 75, 7, 19},
  {cont__simplify_arguments_33, &frame__simplify_arguments_19, 75, 75, 19, 19},
  {entry__simplify_arguments_39, NULL, 84, 84, 42, 64},
  {cont__simplify_arguments_40, &frame__simplify_arguments_39, 84, 84, 42, 64},
  {entry__simplify_arguments_42, NULL, 85, 85, 13, 46},
  {cont__simplify_arguments_43, &frame__simplify_arguments_42, 85, 85, 46, 46},
  {entry__simplify_arguments_48, NULL, 91, 91, 46, 46},
  {entry__simplify_arguments_46, NULL, 89, 89, 18, 45},
  {cont__simplify_arguments_47, &frame__simplify_arguments_46, 89, 91, 15, 46},
  {entry__simplify_arguments_51, NULL, 94, 94, 46, 46},
  {entry__simplify_arguments_49, NULL, 92, 92, 18, 45},
  {cont__simplify_arguments_50, &frame__simplify_arguments_49, 92, 94, 15, 46},
  {entry__simplify_arguments_44, NULL, 87, 87, 13, 41},
  {cont__simplify_arguments_45, &frame__simplify_arguments_44, 88, 94, 13, 47},
  {cont__simplify_arguments_52, &frame__simplify_arguments_44, 95, 95, 13, 45},
  {cont__simplify_arguments_53, &frame__simplify_arguments_44, 96, 96, 26, 26},
  {entry__simplify_arguments_37, NULL, 84, 84, 11, 37},
  {cont__simplify_arguments_38, &frame__simplify_arguments_37, 84, 84, 11, 64},
  {cont__simplify_arguments_41, &frame__simplify_arguments_37, 83, 96, 9, 27},
  {cont__simplify_arguments_54, &frame__simplify_arguments_37, },
  {entry__simplify_arguments_36, NULL, 78, 96, 7, 28},
  {cont__simplify_arguments_55, &frame__simplify_arguments_36, 96, 96, 29, 29},
  {entry__simplify_arguments_18, NULL, 64, 75, 5, 20},
  {cont__simplify_arguments_34, &frame__simplify_arguments_18, 76, 76, 8, 39},
  {cont__simplify_arguments_35, &frame__simplify_arguments_18, 76, 96, 5, 29},
  {cont__simplify_arguments_56, &frame__simplify_arguments_18, 97, 97, 46, 46},
  {entry__simplify_arguments_1, NULL, 42, 42, 3, 32},
  {cont__simplify_arguments_2, &frame__simplify_arguments_1, 43, 54, 3, 39},
  {cont__simplify_arguments_15, &frame__simplify_arguments_1, 61, 61, 3, 46},
  {cont__simplify_arguments_16, &frame__simplify_arguments_1, 62, 62, 6, 32},
  {cont__simplify_arguments_17, &frame__simplify_arguments_1, 62, 97, 3, 46},
  {cont__simplify_arguments_57, &frame__simplify_arguments_1, 98, 98, 3, 23},
  {entry__compiler__check_usage_6, NULL, 105, 105, 21, 39},
  {cont__compiler__check_usage_7, &frame__compiler__check_usage_6, 105, 106, 41, 64},
  {cont__compiler__check_usage_10, &frame__compiler__check_usage_6, 105, 106, 9, 64},
  {entry__compiler__check_usage_3, NULL, 104, 104, 12, 33},
  {cont__compiler__check_usage_4, &frame__compiler__check_usage_3, 104, 104, 35, 77},
  {cont__compiler__check_usage_5, &frame__compiler__check_usage_3, 104, 106, 7, 65},
  {entry__compiler__check_usage_14, NULL, 109, 109, 21, 39},
  {cont__compiler__check_usage_15, &frame__compiler__check_usage_14, 109, 110, 41, 62},
  {cont__compiler__check_usage_17, &frame__compiler__check_usage_14, 109, 110, 9, 62},
  {entry__compiler__check_usage_11, NULL, 108, 108, 12, 33},
  {cont__compiler__check_usage_12, &frame__compiler__check_usage_11, 108, 108, 35, 90},
  {cont__compiler__check_usage_13, &frame__compiler__check_usage_11, 108, 110, 7, 63},
  {entry__compiler__check_usage_21, NULL, 113, 113, 21, 39},
  {cont__compiler__check_usage_22, &frame__compiler__check_usage_21, 113, 114, 41, 70},
  {cont__compiler__check_usage_24, &frame__compiler__check_usage_21, 113, 114, 9, 70},
  {entry__compiler__check_usage_18, NULL, 112, 112, 12, 33},
  {cont__compiler__check_usage_19, &frame__compiler__check_usage_18, 112, 112, 35, 76},
  {cont__compiler__check_usage_20, &frame__compiler__check_usage_18, 112, 114, 7, 71},
  {entry__compiler__check_usage_28, NULL, 117, 117, 21, 39},
  {cont__compiler__check_usage_29, &frame__compiler__check_usage_28, 117, 118, 41, 70},
  {cont__compiler__check_usage_31, &frame__compiler__check_usage_28, 117, 118, 9, 70},
  {entry__compiler__check_usage_25, NULL, 116, 116, 12, 33},
  {cont__compiler__check_usage_26, &frame__compiler__check_usage_25, 116, 116, 35, 87},
  {cont__compiler__check_usage_27, &frame__compiler__check_usage_25, 116, 118, 7, 71},
  {entry__compiler__check_usage_35, NULL, 121, 121, 21, 39},
  {cont__compiler__check_usage_36, &frame__compiler__check_usage_35, 121, 122, 41, 71},
  {cont__compiler__check_usage_38, &frame__compiler__check_usage_35, 121, 122, 9, 71},
  {entry__compiler__check_usage_32, NULL, 120, 120, 12, 33},
  {cont__compiler__check_usage_33, &frame__compiler__check_usage_32, 120, 120, 35, 74},
  {cont__compiler__check_usage_34, &frame__compiler__check_usage_32, 120, 122, 7, 72},
  {entry__compiler__check_usage_1, NULL, 102, 102, 5, 32},
  {cont__compiler__check_usage_2, &frame__compiler__check_usage_1, 101, 122, 3, 74},
  {entry__types__grammar_node__simplify_statement_1, NULL, 128, 128, 3, 57},
  {cont__types__grammar_node__simplify_statement_3, &frame__types__grammar_node__simplify_statement_1, 129, 129, 3, 23},
  {cont__types__grammar_node__simplify_statement_4, &frame__types__grammar_node__simplify_statement_1, 129, 129, 23, 23},
  {entry__types__grammar_node__simplify_expression_1, NULL, 132, 132, 3, 58},
  {cont__types__grammar_node__simplify_expression_3, &frame__types__grammar_node__simplify_expression_1, },
  {entry__compiler__body__simplify_expression_8, NULL, 144, 144, 21, 39},
  {cont__compiler__body__simplify_expression_9, &frame__compiler__body__simplify_expression_8, 144, 146, 41, 33},
  {cont__compiler__body__simplify_expression_12, &frame__compiler__body__simplify_expression_8, 144, 146, 9, 33},
  {entry__compiler__body__simplify_expression_13, NULL, 148, 148, 9, 32},
  {cont__compiler__body__simplify_expression_14, &frame__compiler__body__simplify_expression_13, 148, 148, 37, 37},
  {entry__compiler__body__simplify_expression_5, NULL, 141, 141, 5, 43},
  {cont__compiler__body__simplify_expression_6, &frame__compiler__body__simplify_expression_5, 143, 143, 7, 27},
  {cont__compiler__body__simplify_expression_7, &frame__compiler__body__simplify_expression_5, 142, 148, 5, 38},
  {entry__compiler__body__simplify_expression_24, NULL, 153, 153, 44, 64},
  {cont__compiler__body__simplify_expression_25, &frame__compiler__body__simplify_expression_24, 153, 153, 44, 75},
  {cont__compiler__body__simplify_expression_26, &frame__compiler__body__simplify_expression_24, 153, 153, 44, 75},
  {entry__compiler__body__simplify_expression_28, NULL, 154, 154, 10, 32},
  {cont__compiler__body__simplify_expression_29, &frame__compiler__body__simplify_expression_28, 154, 154, 9, 38},
  {cont__compiler__body__simplify_expression_30, &frame__compiler__body__simplify_expression_28, 154, 154, 43, 43},
  {entry__compiler__body__simplify_expression_20, NULL, 152, 152, 7, 38},
  {cont__compiler__body__simplify_expression_21, &frame__compiler__body__simplify_expression_20, 153, 153, 10, 28},
  {cont__compiler__body__simplify_expression_22, &frame__compiler__body__simplify_expression_20, 153, 153, 10, 39},
  {cont__compiler__body__simplify_expression_23, &frame__compiler__body__simplify_expression_20, 153, 153, 10, 75},
  {cont__compiler__body__simplify_expression_27, &frame__compiler__body__simplify_expression_20, 153, 154, 7, 43},
  {entry__compiler__body__simplify_expression_17, NULL, 150, 150, 5, 39},
  {cont__compiler__body__simplify_expression_18, &frame__compiler__body__simplify_expression_17, 151, 151, 8, 28},
  {cont__compiler__body__simplify_expression_19, &frame__compiler__body__simplify_expression_17, 151, 154, 5, 44},
  {entry__compiler__body__simplify_expression_41, NULL, 169, 169, 13, 48},
  {cont__compiler__body__simplify_expression_42, &frame__compiler__body__simplify_expression_41, 172, 172, 38, 80},
  {cont__compiler__body__simplify_expression_43, &frame__compiler__body__simplify_expression_41, 173, 173, 31, 49},
  {cont__compiler__body__simplify_expression_44, &frame__compiler__body__simplify_expression_41, 174, 174, 30, 52},
  {cont__compiler__body__simplify_expression_45, &frame__compiler__body__simplify_expression_41, 175, 175, 37, 66},
  {cont__compiler__body__simplify_expression_46, &frame__compiler__body__simplify_expression_41, 176, 176, 34, 60},
  {cont__compiler__body__simplify_expression_47, &frame__compiler__body__simplify_expression_41, 170, 176, 13, 61},
  {cont__compiler__body__simplify_expression_48, &frame__compiler__body__simplify_expression_41, 177, 177, 13, 44},
  {cont__compiler__body__simplify_expression_49, &frame__compiler__body__simplify_expression_41, 178, 178, 13, 36},
  {entry__compiler__body__simplify_expression_50, NULL, 180, 180, 13, 46},
  {cont__compiler__body__simplify_expression_51, &frame__compiler__body__simplify_expression_50, 181, 181, 53, 53},
  {entry__compiler__body__simplify_expression_39, NULL, 166, 166, 11, 42},
  {cont__compiler__body__simplify_expression_40, &frame__compiler__body__simplify_expression_39, 165, 181, 9, 54},
  {entry__compiler__body__simplify_expression_36, NULL, 163, 163, 7, 49},
  {cont__compiler__body__simplify_expression_37, &frame__compiler__body__simplify_expression_36, 164, 164, 10, 33},
  {cont__compiler__body__simplify_expression_38, &frame__compiler__body__simplify_expression_36, 164, 181, 7, 55},
  {cont__compiler__body__simplify_expression_52, &frame__compiler__body__simplify_expression_36, },
  {entry__compiler__body__simplify_expression_63, NULL, 191, 191, 13, 35},
  {cont__compiler__body__simplify_expression_64, &frame__compiler__body__simplify_expression_63, 191, 191, 13, 38},
  {cont__compiler__body__simplify_expression_65, &frame__compiler__body__simplify_expression_63, 191, 191, 13, 52},
  {cont__compiler__body__simplify_expression_66, &frame__compiler__body__simplify_expression_63, 191, 191, 13, 52},
  {entry__compiler__body__simplify_expression_59, NULL, 190, 190, 13, 42},
  {cont__compiler__body__simplify_expression_60, &frame__compiler__body__simplify_expression_59, 190, 190, 13, 45},
  {cont__compiler__body__simplify_expression_61, &frame__compiler__body__simplify_expression_59, 190, 190, 13, 75},
  {cont__compiler__body__simplify_expression_62, &frame__compiler__body__simplify_expression_59, 191, 191, 13, 52},
  {cont__compiler__body__simplify_expression_67, &frame__compiler__body__simplify_expression_59, },
  {entry__compiler__body__simplify_expression_69, NULL, 194, 194, 13, 40},
  {cont__compiler__body__simplify_expression_70, &frame__compiler__body__simplify_expression_69, 195, 195, 13, 44},
  {cont__compiler__body__simplify_expression_71, &frame__compiler__body__simplify_expression_69, },
  {entry__compiler__body__simplify_expression_57, NULL, 189, 189, 13, 38},
  {cont__compiler__body__simplify_expression_58, &frame__compiler__body__simplify_expression_57, },
  {cont__compiler__body__simplify_expression_68, &frame__compiler__body__simplify_expression_57, 187, 195, 9, 45},
  {entry__compiler__body__simplify_expression_55, NULL, 186, 186, 14, 34},
  {cont__compiler__body__simplify_expression_56, &frame__compiler__body__simplify_expression_55, 186, 195, 7, 46},
  {entry__compiler__body__simplify_expression_82, NULL, 205, 205, 13, 35},
  {cont__compiler__body__simplify_expression_83, &frame__compiler__body__simplify_expression_82, 205, 205, 13, 38},
  {cont__compiler__body__simplify_expression_84, &frame__compiler__body__simplify_expression_82, 205, 205, 13, 52},
  {cont__compiler__body__simplify_expression_85, &frame__compiler__body__simplify_expression_82, 205, 205, 13, 52},
  {entry__compiler__body__simplify_expression_78, NULL, 204, 204, 13, 42},
  {cont__compiler__body__simplify_expression_79, &frame__compiler__body__simplify_expression_78, 204, 204, 13, 45},
  {cont__compiler__body__simplify_expression_80, &frame__compiler__body__simplify_expression_78, 204, 204, 13, 75},
  {cont__compiler__body__simplify_expression_81, &frame__compiler__body__simplify_expression_78, 205, 205, 13, 52},
  {cont__compiler__body__simplify_expression_86, &frame__compiler__body__simplify_expression_78, },
  {entry__compiler__body__simplify_expression_88, NULL, 208, 208, 13, 40},
  {cont__compiler__body__simplify_expression_89, &frame__compiler__body__simplify_expression_88, 209, 209, 13, 44},
  {cont__compiler__body__simplify_expression_90, &frame__compiler__body__simplify_expression_88, },
  {entry__compiler__body__simplify_expression_76, NULL, 203, 203, 13, 38},
  {cont__compiler__body__simplify_expression_77, &frame__compiler__body__simplify_expression_76, },
  {cont__compiler__body__simplify_expression_87, &frame__compiler__body__simplify_expression_76, 201, 209, 9, 45},
  {entry__compiler__body__simplify_expression_74, NULL, 200, 200, 14, 34},
  {cont__compiler__body__simplify_expression_75, &frame__compiler__body__simplify_expression_74, 200, 209, 7, 46},
  {entry__compiler__body__simplify_expression_32, NULL, 156, 156, 5, 41},
  {cont__compiler__body__simplify_expression_33, &frame__compiler__body__simplify_expression_32, 157, 157, 5, 45},
  {cont__compiler__body__simplify_expression_34, &frame__compiler__body__simplify_expression_32, 162, 162, 18, 35},
  {cont__compiler__body__simplify_expression_35, &frame__compiler__body__simplify_expression_32, 162, 181, 5, 56},
  {cont__compiler__body__simplify_expression_53, &frame__compiler__body__simplify_expression_32, 185, 185, 14, 32},
  {cont__compiler__body__simplify_expression_54, &frame__compiler__body__simplify_expression_32, 185, 195, 5, 47},
  {cont__compiler__body__simplify_expression_72, &frame__compiler__body__simplify_expression_32, 199, 199, 14, 32},
  {cont__compiler__body__simplify_expression_73, &frame__compiler__body__simplify_expression_32, 199, 209, 5, 47},
  {cont__compiler__body__simplify_expression_91, &frame__compiler__body__simplify_expression_32, 212, 212, 5, 28},
  {entry__compiler__body__simplify_expression_95, NULL, 218, 218, 5, 32},
  {cont__compiler__body__simplify_expression_96, &frame__compiler__body__simplify_expression_95, 222, 222, 30, 39},
  {cont__compiler__body__simplify_expression_97, &frame__compiler__body__simplify_expression_95, 223, 223, 23, 32},
  {cont__compiler__body__simplify_expression_98, &frame__compiler__body__simplify_expression_95, 224, 224, 22, 38},
  {cont__compiler__body__simplify_expression_99, &frame__compiler__body__simplify_expression_95, 225, 225, 29, 52},
  {cont__compiler__body__simplify_expression_100, &frame__compiler__body__simplify_expression_95, 226, 226, 26, 46},
  {cont__compiler__body__simplify_expression_101, &frame__compiler__body__simplify_expression_95, 219, 226, 5, 47},
  {cont__compiler__body__simplify_expression_102, &frame__compiler__body__simplify_expression_95, 227, 227, 14, 14},
  {entry__compiler__body__simplify_expression_1, NULL, 138, 138, 3, 42},
  {cont__compiler__body__simplify_expression_3, &frame__compiler__body__simplify_expression_1, 140, 140, 12, 33},
  {cont__compiler__body__simplify_expression_4, &frame__compiler__body__simplify_expression_1, 140, 148, 3, 39},
  {cont__compiler__body__simplify_expression_15, &frame__compiler__body__simplify_expression_1, 149, 149, 12, 30},
  {cont__compiler__body__simplify_expression_16, &frame__compiler__body__simplify_expression_1, 149, 154, 3, 45},
  {cont__compiler__body__simplify_expression_31, &frame__compiler__body__simplify_expression_1, 155, 212, 3, 41},
  {cont__compiler__body__simplify_expression_92, &frame__compiler__body__simplify_expression_1, 213, 213, 10, 33},
  {cont__compiler__body__simplify_expression_93, &frame__compiler__body__simplify_expression_1, 213, 213, 10, 42},
  {cont__compiler__body__simplify_expression_94, &frame__compiler__body__simplify_expression_1, 213, 227, 3, 14},
  {cont__compiler__body__simplify_expression_103, &frame__compiler__body__simplify_expression_1, },
  {entry__do_store_5, NULL, 236, 236, 43, 71},
  {cont__do_store_6, &frame__do_store_5, 236, 236, 71, 71},
  {entry__do_store_10, NULL, 238, 238, 9, 36},
  {cont__do_store_11, &frame__do_store_10, 244, 244, 34, 43},
  {cont__do_store_12, &frame__do_store_10, 245, 245, 26, 42},
  {cont__do_store_13, &frame__do_store_10, 246, 246, 33, 56},
  {cont__do_store_14, &frame__do_store_10, 247, 247, 30, 50},
  {cont__do_store_15, &frame__do_store_10, 239, 247, 9, 51},
  {cont__do_store_16, &frame__do_store_10, 248, 248, 23, 31},
  {cont__do_store_17, &frame__do_store_10, 248, 248, 40, 48},
  {cont__do_store_18, &frame__do_store_10, 248, 248, 9, 54},
  {cont__do_store_19, &frame__do_store_10, 249, 249, 20, 20},
  {entry__do_store_4, NULL, 236, 236, 7, 71},
  {cont__do_store_7, &frame__do_store_4, 237, 237, 10, 24},
  {cont__do_store_8, &frame__do_store_4, 237, 237, 10, 28},
  {cont__do_store_9, &frame__do_store_4, 237, 249, 7, 20},
  {cont__do_store_20, &frame__do_store_4, 254, 254, 25, 46},
  {cont__do_store_21, &frame__do_store_4, 255, 255, 32, 44},
  {cont__do_store_22, &frame__do_store_4, 256, 256, 24, 40},
  {cont__do_store_23, &frame__do_store_4, 257, 257, 31, 54},
  {cont__do_store_24, &frame__do_store_4, 257, 257, 31, 56},
  {cont__do_store_25, &frame__do_store_4, 258, 258, 28, 48},
  {cont__do_store_26, &frame__do_store_4, 250, 258, 7, 49},
  {cont__do_store_27, &frame__do_store_4, 258, 258, 50, 50},
  {entry__do_store_31, NULL, 261, 261, 9, 36},
  {cont__do_store_32, &frame__do_store_31, 265, 265, 25, 45},
  {cont__do_store_33, &frame__do_store_31, 266, 266, 27, 39},
  {cont__do_store_34, &frame__do_store_31, 267, 267, 34, 43},
  {cont__do_store_35, &frame__do_store_31, 268, 268, 26, 42},
  {cont__do_store_36, &frame__do_store_31, 269, 269, 33, 56},
  {cont__do_store_37, &frame__do_store_31, 270, 270, 30, 50},
  {cont__do_store_38, &frame__do_store_31, 262, 270, 9, 51},
  {cont__do_store_39, &frame__do_store_31, 271, 271, 23, 31},
  {cont__do_store_40, &frame__do_store_31, 271, 271, 40, 48},
  {cont__do_store_41, &frame__do_store_31, 271, 271, 9, 54},
  {cont__do_store_42, &frame__do_store_31, 272, 272, 20, 20},
  {entry__do_store_45, NULL, 277, 277, 11, 36},
  {entry__do_store_46, NULL, 278, 278, 11, 33},
  {entry__do_store_28, NULL, 260, 260, 10, 24},
  {cont__do_store_29, &frame__do_store_28, 260, 260, 10, 28},
  {cont__do_store_30, &frame__do_store_28, 260, 272, 7, 20},
  {cont__do_store_43, &frame__do_store_28, 276, 276, 11, 42},
  {cont__do_store_44, &frame__do_store_28, 274, 278, 7, 34},
  {cont__do_store_47, &frame__do_store_28, 283, 283, 32, 44},
  {cont__do_store_48, &frame__do_store_28, 287, 287, 32, 52},
  {cont__do_store_49, &frame__do_store_28, 288, 288, 31, 42},
  {cont__do_store_50, &frame__do_store_28, 285, 288, 13, 42},
  {cont__do_store_51, &frame__do_store_28, 289, 289, 24, 40},
  {cont__do_store_52, &frame__do_store_28, 290, 290, 31, 54},
  {cont__do_store_53, &frame__do_store_28, 290, 290, 31, 56},
  {cont__do_store_54, &frame__do_store_28, 291, 291, 28, 48},
  {cont__do_store_55, &frame__do_store_28, 280, 291, 7, 49},
  {cont__do_store_56, &frame__do_store_28, 291, 291, 50, 50},
  {entry__do_store_1, NULL, 233, 233, 3, 18},
  {cont__do_store_2, &frame__do_store_1, 235, 235, 5, 23},
  {cont__do_store_3, &frame__do_store_1, 234, 291, 3, 51},
  {entry__store_result_8, NULL, 306, 306, 20, 31},
  {cont__store_result_9, &frame__store_result_8, 306, 306, 11, 61},
  {entry__store_result_10, NULL, 308, 308, 24, 35},
  {cont__store_result_11, &frame__store_result_10, 308, 308, 44, 65},
  {cont__store_result_12, &frame__store_result_10, 308, 308, 11, 71},
  {entry__store_result_5, NULL, 305, 305, 9, 20},
  {cont__store_result_6, &frame__store_result_5, 305, 305, 9, 37},
  {cont__store_result_7, &frame__store_result_5, 304, 308, 7, 72},
  {entry__store_result_16, NULL, 313, 313, 11, 54},
  {entry__store_result_17, NULL, 315, 315, 39, 58},
  {cont__store_result_18, &frame__store_result_17, 315, 315, 11, 64},
  {entry__store_result_13, NULL, 310, 310, 7, 38},
  {cont__store_result_14, &frame__store_result_13, 312, 312, 9, 32},
  {cont__store_result_15, &frame__store_result_13, 311, 315, 7, 65},
  {entry__store_result_1, NULL, 300, 300, 3, 25},
  {cont__store_result_2, &frame__store_result_1, 301, 301, 3, 38},
  {cont__store_result_3, &frame__store_result_1, 303, 303, 5, 38},
  {cont__store_result_4, &frame__store_result_1, 302, 315, 3, 67},
  {entry__compiler__call__simplify_statement_5, NULL, 323, 323, 41, 58},
  {cont__compiler__call__simplify_statement_6, &frame__compiler__call__simplify_statement_5, 323, 323, 31, 59},
  {cont__compiler__call__simplify_statement_7, &frame__compiler__call__simplify_statement_5, 323, 323, 31, 64},
  {cont__compiler__call__simplify_statement_8, &frame__compiler__call__simplify_statement_5, 323, 323, 31, 64},
  {entry__compiler__call__simplify_statement_14, NULL, 328, 328, 23, 40},
  {cont__compiler__call__simplify_statement_15, &frame__compiler__call__simplify_statement_14, 330, 330, 18, 44},
  {cont__compiler__call__simplify_statement_16, &frame__compiler__call__simplify_statement_14, 330, 330, 46, 70},
  {cont__compiler__call__simplify_statement_17, &frame__compiler__call__simplify_statement_14, 330, 330, 46, 73},
  {cont__compiler__call__simplify_statement_18, &frame__compiler__call__simplify_statement_14, 330, 330, 13, 74},
  {cont__compiler__call__simplify_statement_19, &frame__compiler__call__simplify_statement_14, 331, 331, 25, 44},
  {cont__compiler__call__simplify_statement_20, &frame__compiler__call__simplify_statement_14, 332, 332, 24, 40},
  {cont__compiler__call__simplify_statement_21, &frame__compiler__call__simplify_statement_14, 333, 333, 31, 54},
  {cont__compiler__call__simplify_statement_22, &frame__compiler__call__simplify_statement_14, 334, 334, 28, 48},
  {cont__compiler__call__simplify_statement_23, &frame__compiler__call__simplify_statement_14, 334, 334, 50, 50},
  {entry__compiler__call__simplify_statement_10, NULL, 324, 324, 13, 30},
  {cont__compiler__call__simplify_statement_11, &frame__compiler__call__simplify_statement_10, 324, 324, 5, 33},
  {cont__compiler__call__simplify_statement_12, &frame__compiler__call__simplify_statement_10, 325, 325, 8, 32},
  {cont__compiler__call__simplify_statement_13, &frame__compiler__call__simplify_statement_10, 325, 334, 5, 50},
  {entry__compiler__call__simplify_statement_31, NULL, 338, 338, 28, 47},
  {cont__compiler__call__simplify_statement_32, &frame__compiler__call__simplify_statement_31, 338, 338, 7, 47},
  {cont__compiler__call__simplify_statement_33, &frame__compiler__call__simplify_statement_31, 338, 338, 47, 47},
  {entry__compiler__call__simplify_statement_37, NULL, 340, 340, 28, 47},
  {cont__compiler__call__simplify_statement_38, &frame__compiler__call__simplify_statement_37, 340, 340, 7, 47},
  {cont__compiler__call__simplify_statement_39, &frame__compiler__call__simplify_statement_37, 340, 340, 47, 47},
  {entry__compiler__call__simplify_statement_28, NULL, 337, 337, 8, 28},
  {cont__compiler__call__simplify_statement_29, &frame__compiler__call__simplify_statement_28, 337, 337, 8, 39},
  {cont__compiler__call__simplify_statement_30, &frame__compiler__call__simplify_statement_28, 337, 338, 5, 47},
  {cont__compiler__call__simplify_statement_34, &frame__compiler__call__simplify_statement_28, 339, 339, 8, 28},
  {cont__compiler__call__simplify_statement_35, &frame__compiler__call__simplify_statement_28, 339, 339, 8, 39},
  {cont__compiler__call__simplify_statement_36, &frame__compiler__call__simplify_statement_28, 339, 340, 5, 47},
  {cont__compiler__call__simplify_statement_40, &frame__compiler__call__simplify_statement_28, 341, 341, 26, 40},
  {cont__compiler__call__simplify_statement_41, &frame__compiler__call__simplify_statement_28, 341, 341, 5, 40},
  {cont__compiler__call__simplify_statement_42, &frame__compiler__call__simplify_statement_28, 341, 341, 40, 40},
  {entry__compiler__call__simplify_statement_57, NULL, 350, 350, 33, 52},
  {cont__compiler__call__simplify_statement_58, &frame__compiler__call__simplify_statement_57, 350, 350, 15, 52},
  {cont__compiler__call__simplify_statement_59, &frame__compiler__call__simplify_statement_57, 351, 351, 15, 20},
  {entry__compiler__call__simplify_statement_63, NULL, 353, 353, 42, 64},
  {cont__compiler__call__simplify_statement_64, &frame__compiler__call__simplify_statement_63, 353, 353, 42, 64},
  {entry__compiler__call__simplify_statement_66, NULL, 354, 354, 35, 54},
  {cont__compiler__call__simplify_statement_67, &frame__compiler__call__simplify_statement_66, 354, 354, 17, 54},
  {cont__compiler__call__simplify_statement_68, &frame__compiler__call__simplify_statement_66, 355, 355, 17, 22},
  {entry__compiler__call__simplify_statement_61, NULL, 353, 353, 18, 37},
  {cont__compiler__call__simplify_statement_62, &frame__compiler__call__simplify_statement_61, 353, 353, 18, 64},
  {cont__compiler__call__simplify_statement_65, &frame__compiler__call__simplify_statement_61, 353, 355, 15, 22},
  {entry__compiler__call__simplify_statement_71, NULL, 357, 357, 35, 54},
  {cont__compiler__call__simplify_statement_72, &frame__compiler__call__simplify_statement_71, 357, 357, 17, 54},
  {cont__compiler__call__simplify_statement_73, &frame__compiler__call__simplify_statement_71, 358, 358, 18, 41},
  {cont__compiler__call__simplify_statement_74, &frame__compiler__call__simplify_statement_71, 358, 358, 18, 44},
  {cont__compiler__call__simplify_statement_75, &frame__compiler__call__simplify_statement_71, 358, 358, 17, 44},
  {cont__compiler__call__simplify_statement_76, &frame__compiler__call__simplify_statement_71, 358, 358, 70, 70},
  {entry__compiler__call__simplify_statement_69, NULL, 356, 356, 18, 41},
  {cont__compiler__call__simplify_statement_70, &frame__compiler__call__simplify_statement_69, 356, 358, 15, 70},
  {entry__compiler__call__simplify_statement_77, NULL, 360, 360, 17, 45},
  {cont__compiler__call__simplify_statement_78, &frame__compiler__call__simplify_statement_77, 361, 361, 18, 41},
  {cont__compiler__call__simplify_statement_79, &frame__compiler__call__simplify_statement_77, 361, 361, 18, 44},
  {cont__compiler__call__simplify_statement_80, &frame__compiler__call__simplify_statement_77, 361, 361, 17, 44},
  {cont__compiler__call__simplify_statement_81, &frame__compiler__call__simplify_statement_77, 361, 361, 70, 70},
  {entry__compiler__call__simplify_statement_51, NULL, 348, 348, 21, 38},
  {cont__compiler__call__simplify_statement_52, &frame__compiler__call__simplify_statement_51, 348, 348, 13, 41},
  {cont__compiler__call__simplify_statement_53, &frame__compiler__call__simplify_statement_51, 349, 349, 16, 45},
  {cont__compiler__call__simplify_statement_54, &frame__compiler__call__simplify_statement_51, 349, 349, 16, 53},
  {cont__compiler__call__simplify_statement_55, &frame__compiler__call__simplify_statement_51, 349, 349, 16, 53},
  {cont__compiler__call__simplify_statement_56, &frame__compiler__call__simplify_statement_51, 349, 351, 13, 20},
  {cont__compiler__call__simplify_statement_60, &frame__compiler__call__simplify_statement_51, 352, 361, 13, 71},
  {entry__compiler__call__simplify_statement_82, NULL, 363, 363, 13, 41},
  {cont__compiler__call__simplify_statement_83, &frame__compiler__call__simplify_statement_82, 364, 364, 14, 37},
  {cont__compiler__call__simplify_statement_84, &frame__compiler__call__simplify_statement_82, 364, 364, 14, 40},
  {cont__compiler__call__simplify_statement_85, &frame__compiler__call__simplify_statement_82, 364, 364, 13, 40},
  {cont__compiler__call__simplify_statement_86, &frame__compiler__call__simplify_statement_82, 364, 364, 66, 66},
  {entry__compiler__call__simplify_statement_49, NULL, 347, 347, 11, 51},
  {cont__compiler__call__simplify_statement_50, &frame__compiler__call__simplify_statement_49, 346, 364, 9, 67},
  {entry__compiler__call__simplify_statement_45, NULL, 344, 344, 20, 44},
  {cont__compiler__call__simplify_statement_46, &frame__compiler__call__simplify_statement_45, 344, 344, 7, 47},
  {cont__compiler__call__simplify_statement_47, &frame__compiler__call__simplify_statement_45, 345, 345, 10, 36},
  {cont__compiler__call__simplify_statement_48, &frame__compiler__call__simplify_statement_45, 345, 364, 7, 68},
  {entry__compiler__call__simplify_statement_91, NULL, 368, 368, 11, 36},
  {cont__compiler__call__simplify_statement_92, &frame__compiler__call__simplify_statement_91, 369, 369, 45, 45},
  {entry__compiler__call__simplify_statement_89, NULL, 367, 367, 12, 35},
  {cont__compiler__call__simplify_statement_90, &frame__compiler__call__simplify_statement_89, 367, 369, 9, 45},
  {cont__compiler__call__simplify_statement_93, &frame__compiler__call__simplify_statement_89, },
  {entry__compiler__call__simplify_statement_87, NULL, 366, 366, 20, 43},
  {cont__compiler__call__simplify_statement_88, &frame__compiler__call__simplify_statement_87, 366, 369, 7, 46},
  {cont__compiler__call__simplify_statement_94, &frame__compiler__call__simplify_statement_87, 369, 369, 47, 47},
  {entry__compiler__call__simplify_statement_105, NULL, 381, 381, 13, 43},
  {entry__compiler__call__simplify_statement_108, NULL, 390, 390, 17, 30},
  {entry__compiler__call__simplify_statement_109, NULL, 391, 391, 20, 45},
  {cont__compiler__call__simplify_statement_110, &frame__compiler__call__simplify_statement_109, 391, 391, 17, 45},
  {entry__compiler__call__simplify_statement_106, NULL, 389, 389, 17, 44},
  {cont__compiler__call__simplify_statement_107, &frame__compiler__call__simplify_statement_106, 387, 391, 13, 46},
  {cont__compiler__call__simplify_statement_111, &frame__compiler__call__simplify_statement_106, 395, 395, 38, 54},
  {cont__compiler__call__simplify_statement_112, &frame__compiler__call__simplify_statement_106, 396, 396, 31, 42},
  {cont__compiler__call__simplify_statement_113, &frame__compiler__call__simplify_statement_106, 397, 397, 30, 52},
  {cont__compiler__call__simplify_statement_114, &frame__compiler__call__simplify_statement_106, 398, 398, 37, 66},
  {cont__compiler__call__simplify_statement_115, &frame__compiler__call__simplify_statement_106, 399, 399, 34, 60},
  {cont__compiler__call__simplify_statement_116, &frame__compiler__call__simplify_statement_106, 393, 399, 13, 61},
  {entry__compiler__call__simplify_statement_101, NULL, 375, 375, 11, 35},
  {cont__compiler__call__simplify_statement_102, &frame__compiler__call__simplify_statement_101, 375, 375, 11, 40},
  {cont__compiler__call__simplify_statement_103, &frame__compiler__call__simplify_statement_101, 380, 380, 11, 40},
  {cont__compiler__call__simplify_statement_104, &frame__compiler__call__simplify_statement_101, 379, 399, 9, 63},
  {entry__compiler__call__simplify_statement_99, NULL, 373, 373, 10, 31},
  {cont__compiler__call__simplify_statement_100, &frame__compiler__call__simplify_statement_99, 373, 399, 7, 64},
  {entry__compiler__call__simplify_statement_98, NULL, 372, 399, 5, 65},
  {entry__compiler__call__simplify_statement_1, NULL, 322, 322, 3, 47},
  {cont__compiler__call__simplify_statement_3, &frame__compiler__call__simplify_statement_1, 323, 323, 6, 26},
  {cont__compiler__call__simplify_statement_4, &frame__compiler__call__simplify_statement_1, 323, 323, 6, 64},
  {cont__compiler__call__simplify_statement_9, &frame__compiler__call__simplify_statement_1, 323, 334, 3, 51},
  {cont__compiler__call__simplify_statement_24, &frame__compiler__call__simplify_statement_1, 335, 335, 3, 47},
  {cont__compiler__call__simplify_statement_25, &frame__compiler__call__simplify_statement_1, 336, 336, 6, 21},
  {cont__compiler__call__simplify_statement_26, &frame__compiler__call__simplify_statement_1, 336, 336, 6, 32},
  {cont__compiler__call__simplify_statement_27, &frame__compiler__call__simplify_statement_1, 336, 341, 3, 40},
  {cont__compiler__call__simplify_statement_43, &frame__compiler__call__simplify_statement_1, 343, 343, 5, 25},
  {cont__compiler__call__simplify_statement_44, &frame__compiler__call__simplify_statement_1, 342, 369, 3, 48},
  {cont__compiler__call__simplify_statement_95, &frame__compiler__call__simplify_statement_1, 370, 370, 3, 23},
  {cont__compiler__call__simplify_statement_96, &frame__compiler__call__simplify_statement_1, 371, 371, 6, 34},
  {cont__compiler__call__simplify_statement_97, &frame__compiler__call__simplify_statement_1, 371, 399, 3, 66},
  {cont__compiler__call__simplify_statement_117, &frame__compiler__call__simplify_statement_1, 399, 399, 66, 66},
  {entry__compiler__function_call__simplify_expression_1, NULL, 405, 405, 3, 51},
  {cont__compiler__function_call__simplify_expression_3, &frame__compiler__function_call__simplify_expression_1, 406, 406, 3, 30},
  {cont__compiler__function_call__simplify_expression_4, &frame__compiler__function_call__simplify_expression_1, 409, 409, 19, 34},
  {cont__compiler__function_call__simplify_expression_5, &frame__compiler__function_call__simplify_expression_1, 410, 410, 33, 57},
  {cont__compiler__function_call__simplify_expression_6, &frame__compiler__function_call__simplify_expression_1, 410, 410, 28, 63},
  {cont__compiler__function_call__simplify_expression_7, &frame__compiler__function_call__simplify_expression_1, 411, 411, 21, 38},
  {cont__compiler__function_call__simplify_expression_8, &frame__compiler__function_call__simplify_expression_1, 412, 412, 20, 36},
  {cont__compiler__function_call__simplify_expression_9, &frame__compiler__function_call__simplify_expression_1, 413, 413, 27, 50},
  {cont__compiler__function_call__simplify_expression_10, &frame__compiler__function_call__simplify_expression_1, 414, 414, 24, 44},
  {cont__compiler__function_call__simplify_expression_11, &frame__compiler__function_call__simplify_expression_1, 407, 414, 3, 45},
  {cont__compiler__function_call__simplify_expression_12, &frame__compiler__function_call__simplify_expression_1, 415, 415, 3, 9},
  {entry__compiler__attribute_value_pair__simplify_expression_1, NULL, 421, 421, 3, 58},
  {cont__compiler__attribute_value_pair__simplify_expression_3, &frame__compiler__attribute_value_pair__simplify_expression_1, 422, 423, 3, 47},
  {cont__compiler__attribute_value_pair__simplify_expression_4, &frame__compiler__attribute_value_pair__simplify_expression_1, 423, 423, 48, 48},
  {entry__compiler__attribute_function_pair__simplify_expression_1, NULL, 429, 429, 3, 61},
  {cont__compiler__attribute_function_pair__simplify_expression_3, &frame__compiler__attribute_function_pair__simplify_expression_1, 430, 431, 3, 47},
  {cont__compiler__attribute_function_pair__simplify_expression_4, &frame__compiler__attribute_function_pair__simplify_expression_1, 431, 431, 48, 48},
  {entry__compiler__c_code__simplify_statement_4, NULL, 438, 438, 35, 35},
  {entry__compiler__c_code__simplify_statement_10, NULL, 443, 443, 22, 43},
  {cont__compiler__c_code__simplify_statement_11, &frame__compiler__c_code__simplify_statement_10, 443, 443, 48, 48},
  {entry__compiler__c_code__simplify_statement_7, NULL, 442, 442, 21, 39},
  {cont__compiler__c_code__simplify_statement_8, &frame__compiler__c_code__simplify_statement_7, 442, 442, 7, 40},
  {cont__compiler__c_code__simplify_statement_9, &frame__compiler__c_code__simplify_statement_7, 443, 443, 7, 48},
  {cont__compiler__c_code__simplify_statement_12, &frame__compiler__c_code__simplify_statement_7, 443, 443, 48, 48},
  {entry__compiler__c_code__simplify_statement_16, NULL, 446, 446, 22, 41},
  {cont__compiler__c_code__simplify_statement_17, &frame__compiler__c_code__simplify_statement_16, 446, 446, 46, 46},
  {entry__compiler__c_code__simplify_statement_13, NULL, 445, 445, 21, 39},
  {cont__compiler__c_code__simplify_statement_14, &frame__compiler__c_code__simplify_statement_13, 445, 445, 7, 40},
  {cont__compiler__c_code__simplify_statement_15, &frame__compiler__c_code__simplify_statement_13, 446, 446, 7, 46},
  {cont__compiler__c_code__simplify_statement_18, &frame__compiler__c_code__simplify_statement_13, 446, 446, 46, 46},
  {entry__compiler__c_code__simplify_statement_25, NULL, 449, 449, 22, 45},
  {cont__compiler__c_code__simplify_statement_26, &frame__compiler__c_code__simplify_statement_25, 449, 449, 50, 50},
  {entry__compiler__c_code__simplify_statement_19, NULL, 448, 448, 20, 34},
  {cont__compiler__c_code__simplify_statement_20, &frame__compiler__c_code__simplify_statement_19, 448, 448, 20, 47},
  {cont__compiler__c_code__simplify_statement_21, &frame__compiler__c_code__simplify_statement_19, 448, 448, 49, 60},
  {cont__compiler__c_code__simplify_statement_22, &frame__compiler__c_code__simplify_statement_19, 448, 448, 63, 63},
  {cont__compiler__c_code__simplify_statement_23, &frame__compiler__c_code__simplify_statement_19, 448, 448, 7, 64},
  {cont__compiler__c_code__simplify_statement_24, &frame__compiler__c_code__simplify_statement_19, 449, 449, 7, 50},
  {cont__compiler__c_code__simplify_statement_27, &frame__compiler__c_code__simplify_statement_19, 449, 449, 50, 50},
  {entry__compiler__c_code__simplify_statement_1, NULL, 437, 437, 3, 44},
  {cont__compiler__c_code__simplify_statement_3, &frame__compiler__c_code__simplify_statement_1, 438, 438, 3, 35},
  {cont__compiler__c_code__simplify_statement_5, &frame__compiler__c_code__simplify_statement_1, 440, 440, 5, 17},
  {cont__compiler__c_code__simplify_statement_6, &frame__compiler__c_code__simplify_statement_1, 439, 449, 3, 51},
  {cont__compiler__c_code__simplify_statement_31, &frame__compiler__c_code__simplify_statement_1, 450, 450, 3, 24},
  {cont__compiler__c_code__simplify_statement_32, &frame__compiler__c_code__simplify_statement_1, 450, 450, 24, 24},
  {entry__compiler__c_body__simplify_expression_4, NULL, 457, 457, 35, 35},
  {entry__compiler__c_body__simplify_expression_1, NULL, 456, 456, 3, 44},
  {cont__compiler__c_body__simplify_expression_3, &frame__compiler__c_body__simplify_expression_1, 457, 457, 3, 35},
  {cont__compiler__c_body__simplify_expression_5, &frame__compiler__c_body__simplify_expression_1, 457, 457, 35, 35}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__compiler__simplify_statement(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__simplify_statement);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__simplify_statement, attr);
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
static void type__compiler__simplify_expression(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__simplify_expression);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__simplify_expression, attr);
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
static NODE *number__0;
static NODE *character__40;
static NODE *character__32;
static NODE *number__1;
static NODE *character__42;

static const char *used_namespaces[] = {
  "std",
  "compiler",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "simplifier",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("simplifier.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__simplifier(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 33: %defined_names empty_table
  initialize_maybe_future(get__defined_names(), get__empty_table());
  // 34: %inherited_names empty_table
  initialize_maybe_future(get__inherited_names(), get__empty_table());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__temporary_identifier_1(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // id: 0
  frame->slots[0] /* id */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 37: inc &temp_idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__temp_idx();
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__temporary_identifier_2;
}
static void cont__temporary_identifier_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__temp_idx(arguments->slots[0]);
  // 38: ... "temp__@(temp_idx)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__421f524a80420288;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__temporary_identifier_4;
}
static void cont__temporary_identifier_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 38: $id temporary(.name_of "temp__@(temp_idx)")
  {
    NODE *temp = clone_object_and_attributes(get__temporary());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[1] /* temp__1 */);
    initialize_future(frame->slots[0] /* id */, temp);

  }
  // 39: -> id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* id */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  // arguments: 1
  // final_destinations: 2
  // output_arguments: 3
  frame->slots[1] /* arguments */ = create_cell();
  frame->slots[2] /* final_destinations */ = create_cell();
  frame->slots[3] /* output_arguments */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 42: $$arguments arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__simplify_arguments_2;
}
static void cont__simplify_arguments_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 43: update_each &arguments: (&argument)
  // 44:   cond
  // 45:     -> argument.is_an_optional_item:
  // 46:       !argument.is_an_optional_item false
  // 47:       simplify_expression &argument
  // 48:       !argument.is_an_optional_item true
  // 49:     -> argument.is_an_expanded_item:
  // 50:       !argument.is_an_expanded_item false
  // 51:       simplify_expression &argument
  // 52:       !argument.is_an_expanded_item true
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = func__simplify_arguments_3;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__simplify_arguments_15;
}
static void entry__simplify_arguments_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 45: -> argument.is_an_optional_item:
  // 46:   !argument.is_an_optional_item false
  // 47:   simplify_expression &argument
  // 48:   !argument.is_an_optional_item true
  frame->slots[1] /* temp__1 */ = create_closure(entry__simplify_arguments_4, 0);
  // 49: -> argument.is_an_expanded_item:
  // 50:   !argument.is_an_expanded_item false
  // 51:   simplify_expression &argument
  // 52:   !argument.is_an_expanded_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__simplify_arguments_8, 0);
  // 53: :
  // 54:   simplify_expression &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__simplify_arguments_12, 0);
  // 44: cond
  // 45:   -> argument.is_an_optional_item:
  // 46:     !argument.is_an_optional_item false
  // 47:     simplify_expression &argument
  // 48:     !argument.is_an_optional_item true
  // 49:   -> argument.is_an_expanded_item:
  // 50:     !argument.is_an_expanded_item false
  // 51:     simplify_expression &argument
  // 52:     !argument.is_an_expanded_item true
  // 53:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__simplify_arguments_14;
}
static void entry__simplify_arguments_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 50: !argument.is_an_expanded_item false
  frame->slots[1] /* temp__1 */ = get__false();
  // 50: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 51: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__simplify_arguments_11;
}
static void cont__simplify_arguments_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  // 52: !argument.is_an_expanded_item true
  frame->slots[1] /* temp__1 */ = get__true();
  // 52: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 46: !argument.is_an_optional_item false
  frame->slots[1] /* temp__1 */ = get__false();
  // 46: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 47: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__simplify_arguments_7;
}
static void cont__simplify_arguments_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  // 48: !argument.is_an_optional_item true
  frame->slots[1] /* temp__1 */ = get__true();
  // 48: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: ... argument.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__simplify_arguments_5;
}
static void cont__simplify_arguments_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 45: ... :
  // 46:   !argument.is_an_optional_item false
  // 47:   simplify_expression &argument
  // 48:   !argument.is_an_optional_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__simplify_arguments_6, 0);
  // 45: -> argument.is_an_optional_item:
  // 46:   !argument.is_an_optional_item false
  // 47:   simplify_expression &argument
  // 48:   !argument.is_an_optional_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 49: ... argument.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__simplify_arguments_9;
}
static void cont__simplify_arguments_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 49: ... :
  // 50:   !argument.is_an_expanded_item false
  // 51:   simplify_expression &argument
  // 52:   !argument.is_an_expanded_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__simplify_arguments_10, 0);
  // 49: -> argument.is_an_expanded_item:
  // 50:   !argument.is_an_expanded_item false
  // 51:   simplify_expression &argument
  // 52:   !argument.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 54: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__simplify_arguments_13;
}
static void cont__simplify_arguments_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_14(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 55: !self.arguments_of arguments
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* arguments */;
  // 55: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 60: $$final_destinations undefined
  ((CELL *)frame->slots[2])->contents /* final_destinations */ = get__undefined();
  // 61: $$output_arguments output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__simplify_arguments_16;
}
static void cont__simplify_arguments_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* output_arguments */ = arguments->slots[0];
  // 62: ... output_arguments.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* output_arguments */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__simplify_arguments_17;
}
static void cont__simplify_arguments_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 62: ... :
  // 63:   $$first_temporary_index undefined
  // 64:   do: (-> break)
  // 65:     for_each output_arguments: (idx argument)
  // 66:       unless
  // 67:         ||
  // 68:           argument.is_an_identifier
  // 69:           &&
  // 70:             argument.is_a_single_assign_definition
  // 71:             length_of(output_arguments) == 1
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__simplify_arguments_18, 0);
  // 62: if output_arguments.is_defined:
  // 63:   $$first_temporary_index undefined
  // 64:   do: (-> break)
  // 65:     for_each output_arguments: (idx argument)
  // 66:       unless
  // 67:         ||
  // 68:           argument.is_an_identifier
  // 69:           &&
  // 70:             argument.is_a_single_assign_definition
  // 71:             length_of(output_arguments) == 1
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__simplify_arguments_57;
}
static void entry__simplify_arguments_18(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // output_arguments: 0
  // final_destinations: 1
  // self: 2
  // first_temporary_index: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* output_arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* final_destinations */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  frame->slots[3] /* first_temporary_index */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: $$first_temporary_index undefined
  ((CELL *)frame->slots[3])->contents /* first_temporary_index */ = get__undefined();
  // 64: ... : (-> break)
  // 65:   for_each output_arguments: (idx argument)
  // 66:     unless
  // 67:       ||
  // 68:         argument.is_an_identifier
  // 69:         &&
  // 70:           argument.is_a_single_assign_definition
  // 71:           length_of(output_arguments) == 1
  // 72:         argument.is_a_multi_assign_definition
  // 73:       :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__simplify_arguments_19, 0);
  // 64: do: (-> break)
  // 65:   for_each output_arguments: (idx argument)
  // 66:     unless
  // 67:       ||
  // 68:         argument.is_an_identifier
  // 69:         &&
  // 70:           argument.is_a_single_assign_definition
  // 71:           length_of(output_arguments) == 1
  // 72:         argument.is_a_multi_assign_definition
  // 73:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__simplify_arguments_34;
}
static void entry__simplify_arguments_19(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // output_arguments: 1
  // first_temporary_index: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[3]; /* first_temporary_index */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 65: ... : (idx argument)
  // 66:   unless
  // 67:     ||
  // 68:       argument.is_an_identifier
  // 69:       &&
  // 70:         argument.is_a_single_assign_definition
  // 71:         length_of(output_arguments) == 1
  // 72:       argument.is_a_multi_assign_definition
  // 73:     :
  // 74:       !first_temporary_index idx
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__simplify_arguments_20, 2);
  // 65: for_each output_arguments: (idx argument)
  // 66:   unless
  // 67:     ||
  // 68:       argument.is_an_identifier
  // 69:       &&
  // 70:         argument.is_a_single_assign_definition
  // 71:         length_of(output_arguments) == 1
  // 72:       argument.is_a_multi_assign_definition
  // 73:     :
  // 74:       !first_temporary_index idx
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__simplify_arguments_33;
}
static void entry__simplify_arguments_32(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // first_temporary_index: 0
  // idx: 1
  // break: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* first_temporary_index */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: !first_temporary_index idx
  ((CELL *)frame->slots[0])->contents /* first_temporary_index */ = frame->slots[1] /* idx */;
  // 75: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__simplify_arguments_20(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // idx: 0
  // argument: 1
  // output_arguments: 2
  // first_temporary_index: 3
  // break: 4
  frame->slots[2] = myself->closure.frame->slots[1]; /* output_arguments */
  frame->slots[3] = myself->closure.frame->slots[2]; /* first_temporary_index */
  frame->slots[4] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 68: argument.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__simplify_arguments_21;
}
static void cont__simplify_arguments_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  frame->slots[7] /* temp__3 */ = create_closure(entry__simplify_arguments_22, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__simplify_arguments_31;
}
static void entry__simplify_arguments_22(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // argument: 0
  // output_arguments: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: argument.is_a_single_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_single_assign_definition();
  func = myself->type;
  frame->cont = cont__simplify_arguments_23;
}
static void cont__simplify_arguments_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 71: length_of(output_arguments) == 1
  frame->slots[5] /* temp__4 */ = create_closure(entry__simplify_arguments_24, 0);
  // 69: &&
  // 70:   argument.is_a_single_assign_definition
  // 71:   length_of(output_arguments) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__simplify_arguments_27;
}
static void entry__simplify_arguments_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // output_arguments: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 71: length_of(output_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__simplify_arguments_25;
}
static void cont__simplify_arguments_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 71: length_of(output_arguments) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__simplify_arguments_26;
}
static void cont__simplify_arguments_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 71: length_of(output_arguments) == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 72: argument.is_a_multi_assign_definition
  frame->slots[6] /* temp__5 */ = create_closure(entry__simplify_arguments_28, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__simplify_arguments_30;
}
static void entry__simplify_arguments_28(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 72: argument.is_a_multi_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_multi_assign_definition();
  func = myself->type;
  frame->cont = cont__simplify_arguments_29;
}
static void cont__simplify_arguments_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 72: argument.is_a_multi_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_30(void) {
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
static void cont__simplify_arguments_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 73: :
  // 74:   !first_temporary_index idx
  // 75:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__simplify_arguments_32, 0);
  // 66: unless
  // 67:   ||
  // 68:     argument.is_an_identifier
  // 69:     &&
  // 70:       argument.is_a_single_assign_definition
  // 71:       length_of(output_arguments) == 1
  // 72:     argument.is_a_multi_assign_definition
  // 73:   :
  // 74:     !first_temporary_index idx
  // 75:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__simplify_arguments_33(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 76: ... first_temporary_index.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* first_temporary_index */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__simplify_arguments_35;
}
static void cont__simplify_arguments_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 76: ... :
  // 77:   !final_destinations empty_list
  // 78:   update_each &output_arguments:
  // 79:     (
  // 80:       idx
  // 81:       &argument
  // 82:     )
  // 83:     if
  // 84:       idx < first_temporary_index || argument.is_a_temporary:
  // 85:         push &final_destinations undefined
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__simplify_arguments_36, 0);
  // 76: if first_temporary_index.is_defined:
  // 77:   !final_destinations empty_list
  // 78:   update_each &output_arguments:
  // 79:     (
  // 80:       idx
  // 81:       &argument
  // 82:     )
  // 83:     if
  // 84:       idx < first_temporary_index || argument.is_a_temporary:
  // 85:         push &final_destinations undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__simplify_arguments_56;
}
static void entry__simplify_arguments_36(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // final_destinations: 0
  // output_arguments: 1
  // first_temporary_index: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* final_destinations */
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[3]; /* first_temporary_index */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 77: !final_destinations empty_list
  ((CELL *)frame->slots[0])->contents /* final_destinations */ = get__empty_list();
  // 78: ... :
  // 79:   (
  // 80:     idx
  // 81:     &argument
  // 82:   )
  // 83:   if
  // 84:     idx < first_temporary_index || argument.is_a_temporary:
  // 85:       push &final_destinations undefined
  // 86:     :
  // 87:       $$temp temporary_identifier()
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__simplify_arguments_37, 2);
  // 78: update_each &output_arguments:
  // 79:   (
  // 80:     idx
  // 81:     &argument
  // 82:   )
  // 83:   if
  // 84:     idx < first_temporary_index || argument.is_a_temporary:
  // 85:       push &final_destinations undefined
  // 86:     :
  // 87:       $$temp temporary_identifier()
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__simplify_arguments_55;
}
static void entry__simplify_arguments_37(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // idx: 0
  // argument: 1
  // first_temporary_index: 2
  // final_destinations: 3
  frame->slots[2] = myself->closure.frame->slots[2]; /* first_temporary_index */
  frame->slots[3] = myself->closure.frame->slots[0]; /* final_destinations */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* argument */ = create_cell_with_contents(arguments->slots[1]);
  // 84: idx < first_temporary_index
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* first_temporary_index */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__simplify_arguments_38;
}
static void cont__simplify_arguments_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 84: ... argument.is_a_temporary
  frame->slots[6] /* temp__3 */ = create_closure(entry__simplify_arguments_39, 0);
  // 84: idx < first_temporary_index || argument.is_a_temporary
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__simplify_arguments_41;
}
static void entry__simplify_arguments_39(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 84: ... argument.is_a_temporary
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_a_temporary();
  func = myself->type;
  frame->cont = cont__simplify_arguments_40;
}
static void cont__simplify_arguments_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 84: ... argument.is_a_temporary
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 84: ... :
  // 85:   push &final_destinations undefined
  frame->slots[7] /* temp__4 */ = create_closure(entry__simplify_arguments_42, 0);
  // 86: :
  // 87:   $$temp temporary_identifier()
  // 88:   cond
  // 89:     -> argument.is_an_optional_item:
  // 90:       !argument.is_an_optional_item false
  // 91:       !temp.is_an_optional_item true
  // 92:     -> argument.is_an_expanded_item:
  // 93:       !argument.is_an_expanded_item false
  // 94:       !temp.is_an_expanded_item true
  // 95:   push &final_destinations argument
  // ...
  frame->slots[8] /* temp__5 */ = create_closure(entry__simplify_arguments_44, 0);
  // 83: if
  // 84:   idx < first_temporary_index || argument.is_a_temporary:
  // 85:     push &final_destinations undefined
  // 86:   :
  // 87:     $$temp temporary_identifier()
  // 88:     cond
  // 89:       -> argument.is_an_optional_item:
  // 90:         !argument.is_an_optional_item false
  // 91:         !temp.is_an_optional_item true
  // 92:       -> argument.is_an_expanded_item:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__simplify_arguments_54;
}
static void entry__simplify_arguments_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // final_destinations: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* final_destinations */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 85: push &final_destinations undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* final_destinations */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__simplify_arguments_43;
}
static void cont__simplify_arguments_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* final_destinations */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_44(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // argument: 0
  // final_destinations: 1
  // temp: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[3]; /* final_destinations */
  frame->slots[2] /* temp */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: $$temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__simplify_arguments_45;
}
static void cont__simplify_arguments_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* temp */ = arguments->slots[0];
  // 89: -> argument.is_an_optional_item:
  // 90:   !argument.is_an_optional_item false
  // 91:   !temp.is_an_optional_item true
  frame->slots[3] /* temp__1 */ = create_closure(entry__simplify_arguments_46, 0);
  // 92: -> argument.is_an_expanded_item:
  // 93:   !argument.is_an_expanded_item false
  // 94:   !temp.is_an_expanded_item true
  frame->slots[4] /* temp__2 */ = create_closure(entry__simplify_arguments_49, 0);
  // 88: cond
  // 89:   -> argument.is_an_optional_item:
  // 90:     !argument.is_an_optional_item false
  // 91:     !temp.is_an_optional_item true
  // 92:   -> argument.is_an_expanded_item:
  // 93:     !argument.is_an_expanded_item false
  // 94:     !temp.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__simplify_arguments_52;
}
static void entry__simplify_arguments_51(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 93: !argument.is_an_expanded_item false
  frame->slots[2] /* temp__1 */ = get__false();
  // 93: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 94: !temp.is_an_expanded_item true
  frame->slots[2] /* temp__1 */ = get__true();
  // 94: !temp.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* temp */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_48(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: !argument.is_an_optional_item false
  frame->slots[2] /* temp__1 */ = get__false();
  // 90: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 91: !temp.is_an_optional_item true
  frame->slots[2] /* temp__1 */ = get__true();
  // 91: !temp.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* temp */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_46(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 89: ... argument.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__simplify_arguments_47;
}
static void cont__simplify_arguments_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: ... :
  // 90:   !argument.is_an_optional_item false
  // 91:   !temp.is_an_optional_item true
  frame->slots[3] /* temp__2 */ = create_closure(entry__simplify_arguments_48, 0);
  // 89: -> argument.is_an_optional_item:
  // 90:   !argument.is_an_optional_item false
  // 91:   !temp.is_an_optional_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_arguments_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 92: ... argument.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__simplify_arguments_50;
}
static void cont__simplify_arguments_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 92: ... :
  // 93:   !argument.is_an_expanded_item false
  // 94:   !temp.is_an_expanded_item true
  frame->slots[3] /* temp__2 */ = create_closure(entry__simplify_arguments_51, 0);
  // 92: -> argument.is_an_expanded_item:
  // 93:   !argument.is_an_expanded_item false
  // 94:   !temp.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 95: push &final_destinations argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* final_destinations */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__simplify_arguments_53;
}
static void cont__simplify_arguments_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* final_destinations */ = arguments->slots[0];
  // 96: !argument temp
  ((CELL *)frame->slots[0])->contents /* argument */ = ((CELL *)frame->slots[2])->contents /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_54(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* argument */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* output_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 97: !self.output_arguments_of output_arguments
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  // 97: !self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_arguments_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 98: -> final_destinations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* final_destinations */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__check_usage_35(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_36;
}
static void cont__compiler__check_usage_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 121: ... "
  // 122:   Invalid access to dynamic read-write variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__611f619f08c2e7ef;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_38;
}
static void cont__compiler__check_usage_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 121: SyntaxError identifier_of(info) "
  // 122:   Invalid access to dynamic read-write variable "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_28(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_29;
}
static void cont__compiler__check_usage_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 117: ... "
  // 118:   Invalid access to dynamic read-only variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__e971e37f901b36b;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_31;
}
static void cont__compiler__check_usage_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 117: SyntaxError identifier_of(info) "
  // 118:   Invalid access to dynamic read-only variable "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_21(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 113: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_22;
}
static void cont__compiler__check_usage_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 113: ... "
  // 114:   Invalid access to static read-write variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2ddd7194c0185268;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_24;
}
static void cont__compiler__check_usage_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 113: SyntaxError identifier_of(info) "
  // 114:   Invalid access to static read-write variable "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_14(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_15;
}
static void cont__compiler__check_usage_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 109: ... "
  // 110:   Invalid access to read-only variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6b008858b3a1b4b2;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_17;
}
static void cont__compiler__check_usage_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 109: SyntaxError identifier_of(info) "
  // 110:   Invalid access to read-only variable "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_6(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_7;
}
static void cont__compiler__check_usage_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 105: ... "
  // 106:   Invalid access to polymorphic function "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9ee981055a49a5fe;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_10;
}
static void cont__compiler__check_usage_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 105: SyntaxError identifier_of(info) "
  // 106:   Invalid access to polymorphic function "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_4;
}
static void cont__compiler__check_usage_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 104: ... STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_MULTI();
  arguments->slots[1] = get__DYNAMIC_SINGLE();
  arguments->slots[2] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_5;
}
static void cont__compiler__check_usage_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 104: ... :
  // 105:   SyntaxError identifier_of(info) "
  // 106:     Invalid access to polymorphic function "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_6, 0);
  // 104: case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 105:   SyntaxError identifier_of(info) "
  // 106:     Invalid access to polymorphic function "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_11(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_12;
}
static void cont__compiler__check_usage_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 108: ... STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_MULTI();
  arguments->slots[1] = get__DYNAMIC_SINGLE();
  arguments->slots[2] = get__DYNAMIC_MULTI();
  arguments->slots[3] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_13;
}
static void cont__compiler__check_usage_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 108: ... :
  // 109:   SyntaxError identifier_of(info) "
  // 110:     Invalid access to read-only variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_14, 0);
  // 108: case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 109:   SyntaxError identifier_of(info) "
  // 110:     Invalid access to read-only variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_18(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 112: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_19;
}
static void cont__compiler__check_usage_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 112: ... DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__DYNAMIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  arguments->slots[2] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_20;
}
static void cont__compiler__check_usage_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 112: ... :
  // 113:   SyntaxError identifier_of(info) "
  // 114:     Invalid access to static read-write variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_21, 0);
  // 112: case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 113:   SyntaxError identifier_of(info) "
  // 114:     Invalid access to static read-write variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_25(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_26;
}
static void cont__compiler__check_usage_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 116: ... POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI, POLYMORPHIC
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = get__POLYMORPHIC();
  arguments->slots[1] = get__STATIC_MULTI();
  arguments->slots[2] = get__DYNAMIC_MULTI();
  arguments->slots[3] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_27;
}
static void cont__compiler__check_usage_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 116: ... :
  // 117:   SyntaxError identifier_of(info) "
  // 118:     Invalid access to dynamic read-only variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_28, 0);
  // 116: case variable_kind_of(info) POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI, POLYMORPHIC:
  // 117:   SyntaxError identifier_of(info) "
  // 118:     Invalid access to dynamic read-only variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_32(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_33;
}
static void cont__compiler__check_usage_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 120: ... POLYMORPHIC, DYNAMIC_SINGLE, POLYMORPHIC
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__POLYMORPHIC();
  arguments->slots[1] = get__DYNAMIC_SINGLE();
  arguments->slots[2] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_34;
}
static void cont__compiler__check_usage_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 120: ... :
  // 121:   SyntaxError identifier_of(info) "
  // 122:     Invalid access to dynamic read-write variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_35, 0);
  // 120: case variable_kind_of(info) POLYMORPHIC, DYNAMIC_SINGLE, POLYMORPHIC:
  // 121:   SyntaxError identifier_of(info) "
  // 122:     Invalid access to dynamic read-write variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_usage_1(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // name: 0
  // definition: 1
  // info: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 102: variable_kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* definition */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__check_usage_2;
}
static void cont__compiler__check_usage_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 103: ... :
  // 104:   case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 105:     SyntaxError identifier_of(info) "
  // 106:       Invalid access to polymorphic function "@(name)@quot;@
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__check_usage_3, 0);
  // 107: ... :
  // 108:   case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 109:     SyntaxError identifier_of(info) "
  // 110:       Invalid access to read-only variable "@(name)@quot;@
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__check_usage_11, 0);
  // 111: ... :
  // 112:   case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 113:     SyntaxError identifier_of(info) "
  // 114:       Invalid access to static read-write variable "@(name)@quot;@
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__check_usage_18, 0);
  // 115: ... :
  // 116:   case variable_kind_of(info) POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI, POLYMORPHIC:
  // 117:     SyntaxError identifier_of(info) "
  // 118:       Invalid access to dynamic read-only variable "@(name)@quot;@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__check_usage_25, 0);
  // 119: ... :
  // 120:   case variable_kind_of(info) POLYMORPHIC, DYNAMIC_SINGLE, POLYMORPHIC:
  // 121:     SyntaxError identifier_of(info) "
  // 122:       Invalid access to dynamic read-write variable "@(name)@quot;@
  frame->slots[8] /* temp__6 */ = create_closure(entry__compiler__check_usage_32, 0);
  // 101: case
  // 102:   variable_kind_of(definition)
  // 103:   POLYMORPHIC:
  // 104:     case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 105:       SyntaxError identifier_of(info) "
  // 106:         Invalid access to polymorphic function "@(name)@quot;@
  // 107:   STATIC_SINGLE:
  // 108:     case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 109:       SyntaxError identifier_of(info) "
  // 110:         Invalid access to read-only variable "@(name)@quot;@
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__POLYMORPHIC();
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = get__STATIC_SINGLE();
  arguments->slots[4] = frame->slots[5] /* temp__3 */;
  arguments->slots[5] = get__STATIC_MULTI();
  arguments->slots[6] = frame->slots[6] /* temp__4 */;
  arguments->slots[7] = get__DYNAMIC_SINGLE();
  arguments->slots[8] = frame->slots[7] /* temp__5 */;
  arguments->slots[9] = get__DYNAMIC_MULTI();
  arguments->slots[10] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__grammar_node__simplify_statement_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 128: show_compiler_debug_info "simplify statement (default)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4a1f5794bff5c237;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__types__grammar_node__simplify_statement_3;
}
static void cont__types__grammar_node__simplify_statement_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 129: push &statements self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__grammar_node__simplify_statement_4;
}
static void cont__types__grammar_node__simplify_statement_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__grammar_node__simplify_expression_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 132: show_compiler_debug_info "simplify expression (default)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5af95dddc656868;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__types__grammar_node__simplify_expression_3;
}
static void cont__types__grammar_node__simplify_expression_3(void) {
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
static void entry__compiler__body__simplify_expression_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  // all_defined_names: 1
  frame->slots[1] /* all_defined_names */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 138: show_compiler_debug_info "simplify body"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__867252dcb87a57b1;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_3;
}
static void cont__compiler__body__simplify_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 139: $$all_defined_names already_defined_names
  ((CELL *)frame->slots[1])->contents /* all_defined_names */ = get__already_defined_names();
  // 140: ... defined_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__defined_names_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_4;
}
static void cont__compiler__body__simplify_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 140: ... : (name info)
  // 141:   $outer_info already_defined_names(name)
  // 142:   if
  // 143:     outer_info.is_defined:
  // 144:       SyntaxError identifier_of(info) "
  // 145:         An identifier named "@(name)" was already defined in an outer scope @
  // 146:         or in a used namespace@
  // 147:     :
  // 148:       !all_defined_names(name) info
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_5, 2);
  // 140: for_each defined_names_of(self): (name info)
  // 141:   $outer_info already_defined_names(name)
  // 142:   if
  // 143:     outer_info.is_defined:
  // 144:       SyntaxError identifier_of(info) "
  // 145:         An identifier named "@(name)" was already defined in an outer scope @
  // 146:         or in a used namespace@
  // 147:     :
  // 148:       !all_defined_names(name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_15;
}
static void entry__compiler__body__simplify_expression_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 144: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_9;
}
static void cont__compiler__body__simplify_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 144: ... "
  // 145:   An identifier named "@(name)" was already defined in an outer scope @
  // 146:   or in a used namespace@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b18861f6a8c886ba;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__ff65db3940410371;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_12;
}
static void cont__compiler__body__simplify_expression_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 144: SyntaxError identifier_of(info) "
  // 145:   An identifier named "@(name)" was already defined in an outer scope @
  // 146:   or in a used namespace@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__body__simplify_expression_13(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // all_defined_names: 0
  // name: 1
  // info: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* all_defined_names */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 148: !all_defined_names(name) info
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* info */;
  // 148: !all_defined_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* all_defined_names */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_14;
}
static void cont__compiler__body__simplify_expression_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* all_defined_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__body__simplify_expression_5(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // all_defined_names: 2
  // outer_info: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* all_defined_names */
  frame->slots[3] /* outer_info */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 141: $outer_info already_defined_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__already_defined_names();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_6;
}
static void cont__compiler__body__simplify_expression_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* outer_info */, arguments->slots[0]);
  // 143: outer_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* outer_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_7;
}
static void cont__compiler__body__simplify_expression_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 143: ... :
  // 144:   SyntaxError identifier_of(info) "
  // 145:     An identifier named "@(name)" was already defined in an outer scope @
  // 146:     or in a used namespace@
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_8, 0);
  // 147: :
  // 148:   !all_defined_names(name) info
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_13, 0);
  // 142: if
  // 143:   outer_info.is_defined:
  // 144:     SyntaxError identifier_of(info) "
  // 145:       An identifier named "@(name)" was already defined in an outer scope @
  // 146:       or in a used namespace@
  // 147:   :
  // 148:     !all_defined_names(name) info
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
static void cont__compiler__body__simplify_expression_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 149: ... used_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__used_names_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_16;
}
static void cont__compiler__body__simplify_expression_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 149: ... : (name info)
  // 150:   $definition all_defined_names(name)
  // 151:   if definition.is_defined:
  // 152:     check_usage name definition info
  // 153:     if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 154:       !self.inherited_names_of(name) info
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_17, 2);
  // 149: for_each used_names_of(self): (name info)
  // 150:   $definition all_defined_names(name)
  // 151:   if definition.is_defined:
  // 152:     check_usage name definition info
  // 153:     if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 154:       !self.inherited_names_of(name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_31;
}
static void entry__compiler__body__simplify_expression_28(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // name: 1
  // info: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* self */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 154: !self.inherited_names_of(name) info
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* info */;
  // 154: ... self.inherited_names_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__inherited_names_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_29;
}
static void cont__compiler__body__simplify_expression_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 154: !self.inherited_names_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_30;
}
static void cont__compiler__body__simplify_expression_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 154: !self.inherited_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__inherited_names_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__body__simplify_expression_20(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // name: 0
  // definition: 1
  // info: 2
  // self: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[4]; /* definition */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  frame->slots[3] = myself->closure.frame->slots[3]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 152: check_usage name definition info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* definition */;
  arguments->slots[2] = frame->slots[2] /* info */;
  result_count = 0;
  myself = get__check_usage();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_21;
}
static void cont__compiler__body__simplify_expression_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 153: ... defined_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__defined_names();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_22;
}
static void cont__compiler__body__simplify_expression_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 153: ... defined_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_23;
}
static void cont__compiler__body__simplify_expression_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 153: ... inherited_names(name).is_defined
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__body__simplify_expression_24, 0);
  // 153: ... defined_names(name).is_defined || inherited_names(name).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_27;
}
static void entry__compiler__body__simplify_expression_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 153: ... inherited_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__inherited_names();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_25;
}
static void cont__compiler__body__simplify_expression_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 153: ... inherited_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_26;
}
static void cont__compiler__body__simplify_expression_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 153: ... inherited_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 153: ... :
  // 154:   !self.inherited_names_of(name) info
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__body__simplify_expression_28, 0);
  // 153: if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 154:   !self.inherited_names_of(name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__body__simplify_expression_17(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // all_defined_names: 2
  // self: 3
  // definition: 4
  frame->slots[2] = myself->closure.frame->slots[1]; /* all_defined_names */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] /* definition */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 150: $definition all_defined_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* all_defined_names */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_18;
}
static void cont__compiler__body__simplify_expression_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* definition */, arguments->slots[0]);
  // 151: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_19;
}
static void cont__compiler__body__simplify_expression_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 151: ... :
  // 152:   check_usage name definition info
  // 153:   if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 154:     !self.inherited_names_of(name) info
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_20, 0);
  // 151: if definition.is_defined:
  // 152:   check_usage name definition info
  // 153:   if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 154:     !self.inherited_names_of(name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__body__simplify_expression_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 155: ... :
  // 156:   %defined_names defined_names_of(self)
  // 157:   %inherited_names inherited_names_of(self)
  // 158:   %already_defined_names all_defined_names
  // 159:   %%definitions empty_list
  // 160:   %%statements empty_list
  // 161:   $$max_temp_idx 0
  // 162:   update_each &self.parameters_of: (&parameter)
  // 163:     $$default_value default_value_of(parameter)
  // 164:     if default_value.is_defined:
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__body__simplify_expression_32, 0);
  // 155: do:
  // 156:   %defined_names defined_names_of(self)
  // 157:   %inherited_names inherited_names_of(self)
  // 158:   %already_defined_names all_defined_names
  // 159:   %%definitions empty_list
  // 160:   %%statements empty_list
  // 161:   $$max_temp_idx 0
  // 162:   update_each &self.parameters_of: (&parameter)
  // 163:     $$default_value default_value_of(parameter)
  // 164:     if default_value.is_defined:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_92;
}
static void entry__compiler__body__simplify_expression_32(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // return__4: 0
  // self: 1
  // all_defined_names: 2
  // max_temp_idx: 3
  frame->slots[0] /* return__4 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* all_defined_names */
  define__defined_names(create_future());
  define__inherited_names(create_future());
  // _define %already_defined_names all_defined_names
  define__already_defined_names(create_future());
  define__definitions(undefined);
  define__statements(undefined);
  frame->slots[3] /* max_temp_idx */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 156: %defined_names defined_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__defined_names_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_33;
}
static void cont__compiler__body__simplify_expression_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__defined_names(), arguments->slots[0]);
  // 157: %inherited_names inherited_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__inherited_names_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_34;
}
static void cont__compiler__body__simplify_expression_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__inherited_names(), arguments->slots[0]);
  // 158: %already_defined_names all_defined_names
  initialize_maybe_future(get__already_defined_names(), ((CELL *)frame->slots[2])->contents /* all_defined_names */);
  // 159: %%definitions empty_list
  set__definitions(get__empty_list());
  // 160: %%statements empty_list
  set__statements(get__empty_list());
  // 161: $$max_temp_idx 0
  ((CELL *)frame->slots[3])->contents /* max_temp_idx */ = number__0;
  // 162: ... self.parameters_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_35;
}
static void cont__compiler__body__simplify_expression_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 162: ... : (&parameter)
  // 163:   $$default_value default_value_of(parameter)
  // 164:   if default_value.is_defined:
  // 165:     if
  // 166:       default_value.is_a_function_call:
  // 167:         %%statements empty_list
  // 168:         %%compiler::temp_idx 0
  // 169:         $identifier identifier_of(parameter)
  // 170:         simplify_statement
  // 171:           assignment
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_36, 1);
  // 162: update_each &self.parameters_of: (&parameter)
  // 163:   $$default_value default_value_of(parameter)
  // 164:   if default_value.is_defined:
  // 165:     if
  // 166:       default_value.is_a_function_call:
  // 167:         %%statements empty_list
  // 168:         %%compiler::temp_idx 0
  // 169:         $identifier identifier_of(parameter)
  // 170:         simplify_statement
  // 171:           assignment
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_53;
}
static void entry__compiler__body__simplify_expression_36(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // max_temp_idx: 1
  // default_value: 2
  frame->slots[1] = myself->closure.frame->slots[3]; /* max_temp_idx */
  frame->slots[2] /* default_value */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* parameter */ = create_cell_with_contents(arguments->slots[0]);
  // 163: $$default_value default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_37;
}
static void cont__compiler__body__simplify_expression_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* default_value */ = arguments->slots[0];
  // 164: ... default_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* default_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_38;
}
static void cont__compiler__body__simplify_expression_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 164: ... :
  // 165:   if
  // 166:     default_value.is_a_function_call:
  // 167:       %%statements empty_list
  // 168:       %%compiler::temp_idx 0
  // 169:       $identifier identifier_of(parameter)
  // 170:       simplify_statement
  // 171:         assignment
  // 172:           .output_arguments_of list(parameter(.is_an_optional_item false))
  // 173:           .arguments_of list(default_value)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_39, 0);
  // 164: if default_value.is_defined:
  // 165:   if
  // 166:     default_value.is_a_function_call:
  // 167:       %%statements empty_list
  // 168:       %%compiler::temp_idx 0
  // 169:       $identifier identifier_of(parameter)
  // 170:       simplify_statement
  // 171:         assignment
  // 172:           .output_arguments_of list(parameter(.is_an_optional_item false))
  // 173:           .arguments_of list(default_value)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_52;
}
static void entry__compiler__body__simplify_expression_41(void) {
  allocate_initialized_frame_gc(4, 12);
  // slot allocations:
  // return__1: 0
  // parameter: 1
  // default_value: 2
  // max_temp_idx: 3
  // identifier: 4
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameter */
  frame->slots[2] = myself->closure.frame->slots[0]; /* default_value */
  frame->slots[3] = myself->closure.frame->slots[2]; /* max_temp_idx */
  define__statements(undefined);
  define__compiler__temp_idx(undefined);
  frame->slots[4] /* identifier */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 167: %%statements empty_list
  set__statements(get__empty_list());
  // 168: %%compiler::temp_idx 0
  set__compiler__temp_idx(number__0);
  // 169: $identifier identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_42;
}
static void cont__compiler__body__simplify_expression_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* identifier */, arguments->slots[0]);
  // 172: ... parameter(.is_an_optional_item false)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__false());
    frame->slots[7] /* temp__3 */ = temp;

  }
  // 172: ... list(parameter(.is_an_optional_item false))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_43;
}
static void cont__compiler__body__simplify_expression_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 173: ... list(default_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* default_value */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_44;
}
static void cont__compiler__body__simplify_expression_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 174: ... fragment_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_45;
}
static void cont__compiler__body__simplify_expression_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 175: ... source_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_46;
}
static void cont__compiler__body__simplify_expression_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 176: ... end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_47;
}
static void cont__compiler__body__simplify_expression_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__7 */ = arguments->slots[0];
  // 171: assignment
  // 172:   .output_arguments_of list(parameter(.is_an_optional_item false))
  // 173:   .arguments_of list(default_value)
  // 174:   .fragment_of fragment_of(identifier)
  // 175:   .source_position_of source_position_of(identifier)
  // 176:   .end_position_of end_position_of(identifier)
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[6] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[8] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[9] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[10] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[11] /* temp__7 */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 170: simplify_statement
  // 171:   assignment
  // 172:     .output_arguments_of list(parameter(.is_an_optional_item false))
  // 173:     .arguments_of list(default_value)
  // 174:     .fragment_of fragment_of(identifier)
  // 175:     .source_position_of source_position_of(identifier)
  // 176:     .end_position_of end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_48;
}
static void cont__compiler__body__simplify_expression_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_49;
}
static void cont__compiler__body__simplify_expression_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* max_temp_idx */ = arguments->slots[0];
  // 178: !parameter.statements_of statements
  frame->slots[5] /* temp__1 */ = get__statements();
  // 178: !parameter.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* parameter */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__body__simplify_expression_50(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // default_value: 0
  // parameter: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* default_value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: simplify_expression &default_value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* default_value */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_51;
}
static void cont__compiler__body__simplify_expression_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* default_value */ = arguments->slots[0];
  // 181: !parameter.default_value_of default_value
  frame->slots[2] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* default_value */;
  // 181: !parameter.default_value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__default_value_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* parameter */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__body__simplify_expression_39(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // default_value: 0
  // parameter: 1
  // max_temp_idx: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* default_value */
  frame->slots[1] = myself->closure.frame->slots[0]; /* parameter */
  frame->slots[2] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 166: default_value.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* default_value */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_40;
}
static void cont__compiler__body__simplify_expression_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 166: ... :
  // 167:   %%statements empty_list
  // 168:   %%compiler::temp_idx 0
  // 169:   $identifier identifier_of(parameter)
  // 170:   simplify_statement
  // 171:     assignment
  // 172:       .output_arguments_of list(parameter(.is_an_optional_item false))
  // 173:       .arguments_of list(default_value)
  // 174:       .fragment_of fragment_of(identifier)
  // 175:       .source_position_of source_position_of(identifier)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_41, 0);
  // 179: :
  // 180:   simplify_expression &default_value
  // 181:   !parameter.default_value_of default_value
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_50, 0);
  // 165: if
  // 166:   default_value.is_a_function_call:
  // 167:     %%statements empty_list
  // 168:     %%compiler::temp_idx 0
  // 169:     $identifier identifier_of(parameter)
  // 170:     simplify_statement
  // 171:       assignment
  // 172:         .output_arguments_of list(parameter(.is_an_optional_item false))
  // 173:         .arguments_of list(default_value)
  // 174:         .fragment_of fragment_of(identifier)
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
static void cont__compiler__body__simplify_expression_52(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 162: ... &self.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[6] /* temp__3 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 185: ... statements_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_54;
}
static void cont__compiler__body__simplify_expression_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 185: ... : (statement)
  // 186:   unless statement.is_a_remark:
  // 187:     if
  // 188:       &&
  // 189:         statement.is_an_assignment
  // 190:         output_arguments_of(statement)(1).is_a_static_single_definition
  // 191:         arguments_of(statement)(1).is_a_constant
  // 192:       :
  // 193:         %%compiler::temp_idx 0
  // 194:         simplify_statement statement
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_55, 1);
  // 185: for_each statements_of(self): (statement)
  // 186:   unless statement.is_a_remark:
  // 187:     if
  // 188:       &&
  // 189:         statement.is_an_assignment
  // 190:         output_arguments_of(statement)(1).is_a_static_single_definition
  // 191:         arguments_of(statement)(1).is_a_constant
  // 192:       :
  // 193:         %%compiler::temp_idx 0
  // 194:         simplify_statement statement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_72;
}
static void entry__compiler__body__simplify_expression_69(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return__2: 0
  // statement: 1
  // max_temp_idx: 2
  frame->slots[0] /* return__2 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[1]; /* max_temp_idx */
  define__compiler__temp_idx(undefined);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 193: %%compiler::temp_idx 0
  set__compiler__temp_idx(number__0);
  // 194: simplify_statement statement
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_70;
}
static void cont__compiler__body__simplify_expression_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 195: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_71;
}
static void cont__compiler__body__simplify_expression_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* max_temp_idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__2 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__body__simplify_expression_57(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_58;
}
static void cont__compiler__body__simplify_expression_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_59, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_68;
}
static void entry__compiler__body__simplify_expression_59(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 190: output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_60;
}
static void cont__compiler__body__simplify_expression_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 190: output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_61;
}
static void cont__compiler__body__simplify_expression_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 190: output_arguments_of(statement)(1).is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_62;
}
static void cont__compiler__body__simplify_expression_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 191: arguments_of(statement)(1).is_a_constant
  frame->slots[5] /* temp__5 */ = create_closure(entry__compiler__body__simplify_expression_63, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_67;
}
static void entry__compiler__body__simplify_expression_63(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 191: arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_64;
}
static void cont__compiler__body__simplify_expression_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 191: arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_65;
}
static void cont__compiler__body__simplify_expression_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 191: arguments_of(statement)(1).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_66;
}
static void cont__compiler__body__simplify_expression_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 191: arguments_of(statement)(1).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_67(void) {
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
static void cont__compiler__body__simplify_expression_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 192: :
  // 193:   %%compiler::temp_idx 0
  // 194:   simplify_statement statement
  // 195:   extend_to &max_temp_idx temp_idx
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__body__simplify_expression_69, 0);
  // 187: if
  // 188:   &&
  // 189:     statement.is_an_assignment
  // 190:     output_arguments_of(statement)(1).is_a_static_single_definition
  // 191:     arguments_of(statement)(1).is_a_constant
  // 192:   :
  // 193:     %%compiler::temp_idx 0
  // 194:     simplify_statement statement
  // 195:     extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__body__simplify_expression_55(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[1] = myself->closure.frame->slots[3]; /* max_temp_idx */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 186: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_56;
}
static void cont__compiler__body__simplify_expression_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 186: ... :
  // 187:   if
  // 188:     &&
  // 189:       statement.is_an_assignment
  // 190:       output_arguments_of(statement)(1).is_a_static_single_definition
  // 191:       arguments_of(statement)(1).is_a_constant
  // 192:     :
  // 193:       %%compiler::temp_idx 0
  // 194:       simplify_statement statement
  // 195:       extend_to &max_temp_idx temp_idx
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_57, 0);
  // 186: unless statement.is_a_remark:
  // 187:   if
  // 188:     &&
  // 189:       statement.is_an_assignment
  // 190:       output_arguments_of(statement)(1).is_a_static_single_definition
  // 191:       arguments_of(statement)(1).is_a_constant
  // 192:     :
  // 193:       %%compiler::temp_idx 0
  // 194:       simplify_statement statement
  // 195:       extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__body__simplify_expression_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 199: ... statements_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_73;
}
static void cont__compiler__body__simplify_expression_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 199: ... : (statement)
  // 200:   unless statement.is_a_remark:
  // 201:     unless
  // 202:       &&
  // 203:         statement.is_an_assignment
  // 204:         output_arguments_of(statement)(1).is_a_static_single_definition
  // 205:         arguments_of(statement)(1).is_a_constant
  // 206:       :
  // 207:         %%compiler::temp_idx 0
  // 208:         simplify_statement statement
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_74, 1);
  // 199: for_each statements_of(self): (statement)
  // 200:   unless statement.is_a_remark:
  // 201:     unless
  // 202:       &&
  // 203:         statement.is_an_assignment
  // 204:         output_arguments_of(statement)(1).is_a_static_single_definition
  // 205:         arguments_of(statement)(1).is_a_constant
  // 206:       :
  // 207:         %%compiler::temp_idx 0
  // 208:         simplify_statement statement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_91;
}
static void entry__compiler__body__simplify_expression_88(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return__3: 0
  // statement: 1
  // max_temp_idx: 2
  frame->slots[0] /* return__3 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[1]; /* max_temp_idx */
  define__compiler__temp_idx(undefined);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: %%compiler::temp_idx 0
  set__compiler__temp_idx(number__0);
  // 208: simplify_statement statement
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_89;
}
static void cont__compiler__body__simplify_expression_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 209: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_90;
}
static void cont__compiler__body__simplify_expression_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* max_temp_idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__3 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__body__simplify_expression_76(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 203: statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_77;
}
static void cont__compiler__body__simplify_expression_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_78, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_87;
}
static void entry__compiler__body__simplify_expression_78(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 204: output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_79;
}
static void cont__compiler__body__simplify_expression_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 204: output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_80;
}
static void cont__compiler__body__simplify_expression_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 204: output_arguments_of(statement)(1).is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_81;
}
static void cont__compiler__body__simplify_expression_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 205: arguments_of(statement)(1).is_a_constant
  frame->slots[5] /* temp__5 */ = create_closure(entry__compiler__body__simplify_expression_82, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_86;
}
static void entry__compiler__body__simplify_expression_82(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 205: arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_83;
}
static void cont__compiler__body__simplify_expression_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 205: arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_84;
}
static void cont__compiler__body__simplify_expression_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 205: arguments_of(statement)(1).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_85;
}
static void cont__compiler__body__simplify_expression_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 205: arguments_of(statement)(1).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_86(void) {
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
static void cont__compiler__body__simplify_expression_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 206: :
  // 207:   %%compiler::temp_idx 0
  // 208:   simplify_statement statement
  // 209:   extend_to &max_temp_idx temp_idx
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__body__simplify_expression_88, 0);
  // 201: unless
  // 202:   &&
  // 203:     statement.is_an_assignment
  // 204:     output_arguments_of(statement)(1).is_a_static_single_definition
  // 205:     arguments_of(statement)(1).is_a_constant
  // 206:   :
  // 207:     %%compiler::temp_idx 0
  // 208:     simplify_statement statement
  // 209:     extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__body__simplify_expression_74(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[1] = myself->closure.frame->slots[3]; /* max_temp_idx */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 200: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_75;
}
static void cont__compiler__body__simplify_expression_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 200: ... :
  // 201:   unless
  // 202:     &&
  // 203:       statement.is_an_assignment
  // 204:       output_arguments_of(statement)(1).is_a_static_single_definition
  // 205:       arguments_of(statement)(1).is_a_constant
  // 206:     :
  // 207:       %%compiler::temp_idx 0
  // 208:       simplify_statement statement
  // 209:       extend_to &max_temp_idx temp_idx
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_76, 0);
  // 200: unless statement.is_a_remark:
  // 201:   unless
  // 202:     &&
  // 203:       statement.is_an_assignment
  // 204:       output_arguments_of(statement)(1).is_a_static_single_definition
  // 205:       arguments_of(statement)(1).is_a_constant
  // 206:     :
  // 207:       %%compiler::temp_idx 0
  // 208:       simplify_statement statement
  // 209:       extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__body__simplify_expression_91(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 210: !self.definitions_of definitions
  frame->slots[4] /* temp__1 */ = get__definitions();
  // 210: !self.definitions_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__definitions_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 211: !self.statements_of statements
  frame->slots[4] /* temp__1 */ = get__statements();
  // 211: !self.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 212: !self.temporary_count_of max_temp_idx
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* max_temp_idx */;
  // 212: !self.temporary_count_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__temporary_count_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__4 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_92(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 213: ... inherited_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__inherited_names_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_93;
}
static void cont__compiler__body__simplify_expression_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 213: ... inherited_names_of(self).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_94;
}
static void cont__compiler__body__simplify_expression_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 213: ... :
  // 214:   #
  // 215:     a closure must be created in a separate step because it is not really
  // 216:     a constant
  // 217:   
  // 218:   $temp temporary_identifier()
  // 219:   push
  // 220:     &statements
  // 221:     assignment
  // 222:       .output_arguments_of list(temp)
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_95, 0);
  // 213: unless inherited_names_of(self).is_empty:
  // 214:   #
  // 215:     a closure must be created in a separate step because it is not really
  // 216:     a constant
  // 217:   
  // 218:   $temp temporary_identifier()
  // 219:   push
  // 220:     &statements
  // 221:     assignment
  // 222:       .output_arguments_of list(temp)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_103;
}
static void entry__compiler__body__simplify_expression_95(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // self: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* temp */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 218: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_96;
}
static void cont__compiler__body__simplify_expression_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* temp */, arguments->slots[0]);
  // 222: ... list(temp)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_97;
}
static void cont__compiler__body__simplify_expression_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 223: ... list(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_98;
}
static void cont__compiler__body__simplify_expression_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 224: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_99;
}
static void cont__compiler__body__simplify_expression_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 225: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_100;
}
static void cont__compiler__body__simplify_expression_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 226: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_101;
}
static void cont__compiler__body__simplify_expression_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 221: assignment
  // 222:   .output_arguments_of list(temp)
  // 223:   .arguments_of list(self)
  // 224:   .fragment_of fragment_of(self)
  // 225:   .source_position_of source_position_of(self)
  // 226:   .end_position_of end_position_of(self)
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[7] /* temp__6 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 219: push
  // 220:   &statements
  // 221:   assignment
  // 222:     .output_arguments_of list(temp)
  // 223:     .arguments_of list(self)
  // 224:     .fragment_of fragment_of(self)
  // 225:     .source_position_of source_position_of(self)
  // 226:     .end_position_of end_position_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_102;
}
static void cont__compiler__body__simplify_expression_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 227: !self temp
  ((CELL *)frame->slots[0])->contents /* self */ = frame->slots[1] /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_103(void) {
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
static void entry__do_store_4(void) {
  allocate_initialized_frame_gc(6, 13);
  // slot allocations:
  // arguments: 0
  // rest: 1
  // functor: 2
  // info: 3
  // result: 4
  // infos: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[2] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[3] = myself->closure.frame->slots[5]; /* info */
  frame->slots[4] = myself->closure.frame->slots[2]; /* result */
  frame->slots[5] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 236: update_each &arguments: (&argument) simplify_expression &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = func__do_store_5;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__do_store_7;
}
static void entry__do_store_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 236: ... simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__do_store_6;
}
static void cont__do_store_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__do_store_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  // 237: ... length_of(rest)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* rest */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__do_store_8;
}
static void cont__do_store_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 237: ... length_of(rest) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__do_store_9;
}
static void cont__do_store_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 237: ... :
  // 238:   $temp temporary_identifier()
  // 239:   push
  // 240:     &statements
  // 241:     procedure_call
  // 242:       .functor_of functor
  // 243:       .arguments_of arguments
  // 244:       .output_arguments_of list(temp)
  // 245:       .fragment_of fragment_of(info)
  // 246:       .source_position_of source_position_of(info)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__do_store_10, 0);
  // 237: if length_of(rest) > 0:
  // 238:   $temp temporary_identifier()
  // 239:   push
  // 240:     &statements
  // 241:     procedure_call
  // 242:       .functor_of functor
  // 243:       .arguments_of arguments
  // 244:       .output_arguments_of list(temp)
  // 245:       .fragment_of fragment_of(info)
  // 246:       .source_position_of source_position_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__do_store_20;
}
static void entry__do_store_10(void) {
  allocate_initialized_frame_gc(6, 12);
  // slot allocations:
  // functor: 0
  // arguments: 1
  // info: 2
  // rest: 3
  // result: 4
  // infos: 5
  // temp: 6
  frame->slots[0] = myself->closure.frame->slots[2]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[3]; /* info */
  frame->slots[3] = myself->closure.frame->slots[1]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[4]; /* result */
  frame->slots[5] = myself->closure.frame->slots[5]; /* infos */
  frame->slots[6] /* temp */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 238: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__do_store_11;
}
static void cont__do_store_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* temp */, arguments->slots[0]);
  // 244: ... list(temp)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__do_store_12;
}
static void cont__do_store_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 245: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__do_store_13;
}
static void cont__do_store_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 246: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__do_store_14;
}
static void cont__do_store_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 247: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__do_store_15;
}
static void cont__do_store_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 241: procedure_call
  // 242:   .functor_of functor
  // 243:   .arguments_of arguments
  // 244:   .output_arguments_of list(temp)
  // 245:   .fragment_of fragment_of(info)
  // 246:   .source_position_of source_position_of(info)
  // 247:   .end_position_of end_position_of(info)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, ((CELL *)frame->slots[1])->contents /* arguments */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[9] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[10] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[11] /* temp__5 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 239: push
  // 240:   &statements
  // 241:   procedure_call
  // 242:     .functor_of functor
  // 243:     .arguments_of arguments
  // 244:     .output_arguments_of list(temp)
  // 245:     .fragment_of fragment_of(info)
  // 246:     .source_position_of source_position_of(info)
  // 247:     .end_position_of end_position_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__do_store_16;
}
static void cont__do_store_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 248: ... rest.peek
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__do_store_17;
}
static void cont__do_store_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 248: ... rest.drop
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__drop();
  func = myself->type;
  frame->cont = cont__do_store_18;
}
static void cont__do_store_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 248: do_store temp rest.peek result rest.drop infos
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[4])->contents /* result */;
  arguments->slots[3] = frame->slots[8] /* temp__2 */;
  arguments->slots[4] = ((CELL *)frame->slots[5])->contents /* infos */;
  result_count = 0;
  myself = var._do_store;
  func = myself->type;
  frame->cont = cont__do_store_19;
}
static void cont__do_store_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 249: !result temp
  ((CELL *)frame->slots[4])->contents /* result */ = frame->slots[6] /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__do_store_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 254: ... push(arguments result)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* result */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__do_store_21;
}
static void cont__do_store_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 255: ... list(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* functor */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__do_store_22;
}
static void cont__do_store_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 256: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__do_store_23;
}
static void cont__do_store_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  // 257: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__do_store_24;
}
static void cont__do_store_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__6 */ = arguments->slots[0];
  // 257: ... source_position_of(info)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__do_store_25;
}
static void cont__do_store_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 258: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__do_store_26;
}
static void cont__do_store_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 252: procedure_call
  // 253:   .functor_of functor
  // 254:   .arguments_of push(arguments result)
  // 255:   .output_arguments_of list(functor)
  // 256:   .fragment_of fragment_of(info)
  // 257:   .source_position_of source_position_of(info)+1
  // 258:   .end_position_of end_position_of(info)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[8] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[9] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[10] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[12] /* temp__7 */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 250: push
  // 251:   &statements
  // 252:   procedure_call
  // 253:     .functor_of functor
  // 254:     .arguments_of push(arguments result)
  // 255:     .output_arguments_of list(functor)
  // 256:     .fragment_of fragment_of(info)
  // 257:     .source_position_of source_position_of(info)+1
  // 258:     .end_position_of end_position_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__do_store_27;
}
static void cont__do_store_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__do_store_28(void) {
  allocate_initialized_frame_gc(6, 17);
  // slot allocations:
  // rest: 0
  // arguments: 1
  // functor: 2
  // info: 3
  // result: 4
  // infos: 5
  // attribute_pair: 6
  frame->slots[0] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[1] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[3] = myself->closure.frame->slots[5]; /* info */
  frame->slots[4] = myself->closure.frame->slots[2]; /* result */
  frame->slots[5] = myself->closure.frame->slots[4]; /* infos */
  frame->slots[6] /* attribute_pair */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 260: ... length_of(rest)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* rest */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__do_store_29;
}
static void cont__do_store_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 260: ... length_of(rest) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__do_store_30;
}
static void cont__do_store_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 260: ... :
  // 261:   $temp temporary_identifier()
  // 262:   push
  // 263:     &statements
  // 264:     procedure_call
  // 265:       .functor_of functor_of(arguments)
  // 266:       .arguments_of list(functor)
  // 267:       .output_arguments_of list(temp)
  // 268:       .fragment_of fragment_of(info)
  // 269:       .source_position_of source_position_of(info)
  // ...
  frame->slots[9] /* temp__3 */ = create_closure(entry__do_store_31, 0);
  // 260: if length_of(rest) > 0:
  // 261:   $temp temporary_identifier()
  // 262:   push
  // 263:     &statements
  // 264:     procedure_call
  // 265:       .functor_of functor_of(arguments)
  // 266:       .arguments_of list(functor)
  // 267:       .output_arguments_of list(temp)
  // 268:       .fragment_of fragment_of(info)
  // 269:       .source_position_of source_position_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__do_store_43;
}
static void entry__do_store_31(void) {
  allocate_initialized_frame_gc(6, 14);
  // slot allocations:
  // arguments: 0
  // functor: 1
  // info: 2
  // rest: 3
  // result: 4
  // infos: 5
  // temp: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* functor */
  frame->slots[2] = myself->closure.frame->slots[3]; /* info */
  frame->slots[3] = myself->closure.frame->slots[0]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[4]; /* result */
  frame->slots[5] = myself->closure.frame->slots[5]; /* infos */
  frame->slots[6] /* temp */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 261: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__do_store_32;
}
static void cont__do_store_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* temp */, arguments->slots[0]);
  // 265: ... functor_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__do_store_33;
}
static void cont__do_store_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 266: ... list(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* functor */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__do_store_34;
}
static void cont__do_store_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 267: ... list(temp)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__do_store_35;
}
static void cont__do_store_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 268: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__do_store_36;
}
static void cont__do_store_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 269: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__do_store_37;
}
static void cont__do_store_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__6 */ = arguments->slots[0];
  // 270: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__do_store_38;
}
static void cont__do_store_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__7 */ = arguments->slots[0];
  // 264: procedure_call
  // 265:   .functor_of functor_of(arguments)
  // 266:   .arguments_of list(functor)
  // 267:   .output_arguments_of list(temp)
  // 268:   .fragment_of fragment_of(info)
  // 269:   .source_position_of source_position_of(info)
  // 270:   .end_position_of end_position_of(info)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[10] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[11] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[12] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[13] /* temp__7 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 262: push
  // 263:   &statements
  // 264:   procedure_call
  // 265:     .functor_of functor_of(arguments)
  // 266:     .arguments_of list(functor)
  // 267:     .output_arguments_of list(temp)
  // 268:     .fragment_of fragment_of(info)
  // 269:     .source_position_of source_position_of(info)
  // 270:     .end_position_of end_position_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__do_store_39;
}
static void cont__do_store_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 271: ... rest.peek
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__do_store_40;
}
static void cont__do_store_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 271: ... rest.drop
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__drop();
  func = myself->type;
  frame->cont = cont__do_store_41;
}
static void cont__do_store_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 271: do_store temp rest.peek result rest.drop infos
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[4])->contents /* result */;
  arguments->slots[3] = frame->slots[8] /* temp__2 */;
  arguments->slots[4] = ((CELL *)frame->slots[5])->contents /* infos */;
  result_count = 0;
  myself = var._do_store;
  func = myself->type;
  frame->cont = cont__do_store_42;
}
static void cont__do_store_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 272: !result temp
  ((CELL *)frame->slots[4])->contents /* result */ = frame->slots[6] /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__do_store_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 276: arguments.is_a_method_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__is_a_method_definition();
  func = myself->type;
  frame->cont = cont__do_store_44;
}
static void cont__do_store_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 274: $attribute_pair
  // 275:   if
  // 276:     arguments.is_a_method_definition
  // 277:     -> attribute_function_pair
  // 278:     -> attribute_value_pair
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__do_store_45;
  arguments->slots[2] = func__do_store_46;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__do_store_47;
}
static void entry__do_store_45(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 277: -> attribute_function_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__do_store_46(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 278: -> attribute_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_value_pair();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__do_store_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* attribute_pair */, arguments->slots[0]);
  // 283: ... list(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* functor */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__do_store_48;
}
static void cont__do_store_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 287: ... functor_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__do_store_49;
}
static void cont__do_store_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 288: ... list(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* result */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__do_store_50;
}
static void cont__do_store_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__6 */ = arguments->slots[0];
  // 286: attribute_pair
  // 287:   .identifier_of functor_of(arguments)
  // 288:   .arguments_of list(result)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* attribute_pair */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[11] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[12] /* temp__6 */);
    frame->slots[10] /* temp__4 */ = temp;

  }
  // 285: list
  // 286:   attribute_pair
  // 287:     .identifier_of functor_of(arguments)
  // 288:     .arguments_of list(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__do_store_51;
}
static void cont__do_store_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 289: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__do_store_52;
}
static void cont__do_store_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__7 */ = arguments->slots[0];
  // 290: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__do_store_53;
}
static void cont__do_store_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__9 */ = arguments->slots[0];
  // 290: ... source_position_of(info)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__9 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__do_store_54;
}
static void cont__do_store_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__8 */ = arguments->slots[0];
  // 291: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__do_store_55;
}
static void cont__do_store_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__10 */ = arguments->slots[0];
  // 282: assignment
  // 283:   .output_arguments_of list(functor)
  // 284:   .arguments_of
  // 285:     list
  // 286:       attribute_pair
  // 287:         .identifier_of functor_of(arguments)
  // 288:         .arguments_of list(result)
  // 289:   .fragment_of fragment_of(info)
  // 290:   .source_position_of source_position_of(info)+1
  // 291:   .end_position_of end_position_of(info)
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[13] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[14] /* temp__8 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[16] /* temp__10 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 280: push
  // 281:   &statements
  // 282:   assignment
  // 283:     .output_arguments_of list(functor)
  // 284:     .arguments_of
  // 285:       list
  // 286:         attribute_pair
  // 287:           .identifier_of functor_of(arguments)
  // 288:           .arguments_of list(result)
  // 289:     .fragment_of fragment_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__do_store_56;
}
static void cont__do_store_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__do_store_1(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // functor: 0
  // arguments: 1
  // result: 2
  // rest: 3
  // infos: 4
  // info: 5
  frame->slots[5] /* info */ = create_future();
  if (argument_count != 5) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* arguments */ = create_cell_with_contents(arguments->slots[1]);
  frame->slots[2] /* result */ = create_cell_with_contents(arguments->slots[2]);
  frame->slots[4] /* infos */ = create_cell_with_contents(arguments->slots[4]);
  // 233: pop &infos $info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__do_store_2;
}
static void cont__do_store_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* infos */ = arguments->slots[0];
  frame->slots[6] /* temp__1 */ = arguments->slots[1];
  // 233: ... info
  initialize_future(frame->slots[5] /* info */, frame->slots[6] /* temp__1 */);
  // 235: arguments.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__do_store_3;
}
static void cont__do_store_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 235: ... : # container access
  // 236:   update_each &arguments: (&argument) simplify_expression &argument
  // 237:   if length_of(rest) > 0:
  // 238:     $temp temporary_identifier()
  // 239:     push
  // 240:       &statements
  // 241:       procedure_call
  // 242:         .functor_of functor
  // 243:         .arguments_of arguments
  // 244:         .output_arguments_of list(temp)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__do_store_4, 0);
  // 259: : # attribute value or attribute function definition
  // 260:   if length_of(rest) > 0:
  // 261:     $temp temporary_identifier()
  // 262:     push
  // 263:       &statements
  // 264:       procedure_call
  // 265:         .functor_of functor_of(arguments)
  // 266:         .arguments_of list(functor)
  // 267:         .output_arguments_of list(temp)
  // 268:         .fragment_of fragment_of(info)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__do_store_28, 0);
  // 234: if
  // 235:   arguments.is_a_list: # container access
  // 236:     update_each &arguments: (&argument) simplify_expression &argument
  // 237:     if length_of(rest) > 0:
  // 238:       $temp temporary_identifier()
  // 239:       push
  // 240:         &statements
  // 241:         procedure_call
  // 242:           .functor_of functor
  // 243:           .arguments_of arguments
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
static void entry__store_result_16(void) {
  allocate_initialized_frame_gc(5, 5);
  // slot allocations:
  // functor: 0
  // arguments: 1
  // result: 2
  // rest: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* result */
  frame->slots[3] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 313: do_store functor arguments result rest infos
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  arguments->slots[1] = frame->slots[1] /* arguments */;
  arguments->slots[2] = frame->slots[2] /* result */;
  arguments->slots[3] = frame->slots[3] /* rest */;
  arguments->slots[4] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = frame->caller_result_count;
  myself = var._do_store;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__store_result_17(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // functor: 0
  // result: 1
  // rest: 2
  // arguments: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[2]; /* result */
  frame->slots[2] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[3] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[4] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 315: ... push(rest arguments)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* rest */;
  arguments->slots[1] = frame->slots[3] /* arguments */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__store_result_18;
}
static void cont__store_result_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 315: store_result functor result push(rest arguments) infos
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  arguments->slots[1] = frame->slots[1] /* result */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  arguments->slots[3] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = frame->caller_result_count;
  myself = var._store_result;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__store_result_8(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // arguments: 0
  // destination: 1
  // result: 2
  // rest: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[2]; /* result */
  frame->slots[3] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__store_result_9;
}
static void cont__store_result_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 306: do_store arguments(1) destination result rest infos
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* destination */;
  arguments->slots[2] = frame->slots[2] /* result */;
  arguments->slots[3] = frame->slots[3] /* rest */;
  arguments->slots[4] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = frame->caller_result_count;
  myself = var._do_store;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__store_result_10(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // arguments: 0
  // result: 1
  // rest: 2
  // destination: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* result */
  frame->slots[2] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[3] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[4] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 308: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__store_result_11;
}
static void cont__store_result_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 308: ... push(rest destination)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* rest */;
  arguments->slots[1] = frame->slots[3] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__store_result_12;
}
static void cont__store_result_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 308: store_result arguments(1) result push(rest destination) infos
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* result */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = frame->caller_result_count;
  myself = var._store_result;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__store_result_5(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // arguments: 0
  // destination: 1
  // result: 2
  // rest: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[1]; /* result */
  frame->slots[3] = myself->closure.frame->slots[2]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[3]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 305: arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__store_result_6;
}
static void cont__store_result_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 305: arguments(1).is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__store_result_7;
}
static void cont__store_result_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 305: ... :
  // 306:   do_store arguments(1) destination result rest infos
  frame->slots[7] /* temp__3 */ = create_closure(entry__store_result_8, 0);
  // 307: :
  // 308:   store_result arguments(1) result push(rest destination) infos
  frame->slots[8] /* temp__4 */ = create_closure(entry__store_result_10, 0);
  // 304: if
  // 305:   arguments(1).is_an_identifier:
  // 306:     do_store arguments(1) destination result rest infos
  // 307:   :
  // 308:     store_result arguments(1) result push(rest destination) infos
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
static void entry__store_result_13(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // destination: 0
  // arguments: 1
  // result: 2
  // rest: 3
  // infos: 4
  // functor: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[1]; /* result */
  frame->slots[3] = myself->closure.frame->slots[2]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[3]; /* infos */
  frame->slots[5] /* functor */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 310: $functor functor_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__store_result_14;
}
static void cont__store_result_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* functor */, arguments->slots[0]);
  // 312: functor.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* functor */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__store_result_15;
}
static void cont__store_result_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 312: ... :
  // 313:   do_store functor arguments result rest infos
  frame->slots[7] /* temp__2 */ = create_closure(entry__store_result_16, 0);
  // 314: :
  // 315:   store_result functor result push(rest arguments) infos
  frame->slots[8] /* temp__3 */ = create_closure(entry__store_result_17, 0);
  // 311: if
  // 312:   functor.is_an_identifier:
  // 313:     do_store functor arguments result rest infos
  // 314:   :
  // 315:     store_result functor result push(rest arguments) infos
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
static void entry__store_result_1(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // destination: 0
  // result: 1
  // rest: 2
  // infos: 3
  // arguments: 4
  frame->slots[4] /* arguments */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* infos */ = create_cell_with_contents(arguments->slots[3]);
    case 3: frame->slots[2] /* rest */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* rest */ = get__empty_list();
    case 3: frame->slots[3] /* infos */ = create_cell_with_contents(get__empty_list());
  }
  // 300: push &infos destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* infos */;
  arguments->slots[1] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__store_result_2;
}
static void cont__store_result_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* infos */ = arguments->slots[0];
  // 301: $arguments arguments_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__store_result_3;
}
static void cont__store_result_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* arguments */, arguments->slots[0]);
  // 303: destination.is_an_attribute_access
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__is_an_attribute_access();
  func = myself->type;
  frame->cont = cont__store_result_4;
}
static void cont__store_result_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 303: ... :
  // 304:   if
  // 305:     arguments(1).is_an_identifier:
  // 306:       do_store arguments(1) destination result rest infos
  // 307:     :
  // 308:       store_result arguments(1) result push(rest destination) infos
  frame->slots[6] /* temp__2 */ = create_closure(entry__store_result_5, 0);
  // 309: :
  // 310:   $functor functor_of(destination)
  // 311:   if
  // 312:     functor.is_an_identifier:
  // 313:       do_store functor arguments result rest infos
  // 314:     :
  // 315:       store_result functor result push(rest arguments) infos
  frame->slots[7] /* temp__3 */ = create_closure(entry__store_result_13, 0);
  // 302: if
  // 303:   destination.is_an_attribute_access:
  // 304:     if
  // 305:       arguments(1).is_an_identifier:
  // 306:         do_store arguments(1) destination result rest infos
  // 307:       :
  // 308:         store_result arguments(1) result push(rest destination) infos
  // 309:   :
  // 310:     $functor functor_of(destination)
  // 311:     if
  // ...
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
static void entry__compiler__call__simplify_statement_1(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // return: 1
  // final_destinations: 2
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[2] /* final_destinations */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 322: show_compiler_debug_info "simplify statement"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8629329e514f7a7a;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_3;
}
static void cont__compiler__call__simplify_statement_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 323: ... self.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_4;
}
static void cont__compiler__call__simplify_statement_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 323: ... length_of(arguments_of(self)) == 1
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_5, 0);
  // 323: ... self.is_an_assignment && length_of(arguments_of(self)) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_9;
}
static void entry__compiler__call__simplify_statement_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 323: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_6;
}
static void cont__compiler__call__simplify_statement_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 323: ... length_of(arguments_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_7;
}
static void cont__compiler__call__simplify_statement_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 323: ... length_of(arguments_of(self)) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_8;
}
static void cont__compiler__call__simplify_statement_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 323: ... length_of(arguments_of(self)) == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 323: ... :
  // 324:   $source arguments_of(self)(1)
  // 325:   if source.is_a_function_call:
  // 326:     !self
  // 327:       procedure_call
  // 328:         .functor_of functor_of(source)
  // 329:         .output_arguments_of
  // 330:           push(output_arguments_of(source) output_arguments_of(self)(1))
  // 331:         .arguments_of arguments_of(source)
  // 332:         .fragment_of fragment_of(self)
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__call__simplify_statement_10, 0);
  // 323: if self.is_an_assignment && length_of(arguments_of(self)) == 1:
  // 324:   $source arguments_of(self)(1)
  // 325:   if source.is_a_function_call:
  // 326:     !self
  // 327:       procedure_call
  // 328:         .functor_of functor_of(source)
  // 329:         .output_arguments_of
  // 330:           push(output_arguments_of(source) output_arguments_of(self)(1))
  // 331:         .arguments_of arguments_of(source)
  // 332:         .fragment_of fragment_of(self)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_24;
}
static void entry__compiler__call__simplify_statement_14(void) {
  allocate_initialized_frame_gc(2, 11);
  // slot allocations:
  // self: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 328: ... functor_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_15;
}
static void cont__compiler__call__simplify_statement_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 330: ... output_arguments_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_16;
}
static void cont__compiler__call__simplify_statement_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 330: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_17;
}
static void cont__compiler__call__simplify_statement_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 330: ... output_arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[6] /* temp__5 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_18;
}
static void cont__compiler__call__simplify_statement_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 330: push(output_arguments_of(source) output_arguments_of(self)(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_19;
}
static void cont__compiler__call__simplify_statement_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 331: ... arguments_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_20;
}
static void cont__compiler__call__simplify_statement_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 332: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_21;
}
static void cont__compiler__call__simplify_statement_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 333: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_22;
}
static void cont__compiler__call__simplify_statement_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 334: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_23;
}
static void cont__compiler__call__simplify_statement_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 326: !self
  // 327:   procedure_call
  // 328:     .functor_of functor_of(source)
  // 329:     .output_arguments_of
  // 330:       push(output_arguments_of(source) output_arguments_of(self)(1))
  // 331:     .arguments_of arguments_of(source)
  // 332:     .fragment_of fragment_of(self)
  // 333:     .source_position_of source_position_of(self)
  // 334:     .end_position_of end_position_of(self)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[8] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[9] /* temp__8 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[10] /* temp__9 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_10(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 324: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_11;
}
static void cont__compiler__call__simplify_statement_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 324: $source arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_12;
}
static void cont__compiler__call__simplify_statement_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* source */, arguments->slots[0]);
  // 325: ... source.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_13;
}
static void cont__compiler__call__simplify_statement_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 325: ... :
  // 326:   !self
  // 327:     procedure_call
  // 328:       .functor_of functor_of(source)
  // 329:       .output_arguments_of
  // 330:         push(output_arguments_of(source) output_arguments_of(self)(1))
  // 331:       .arguments_of arguments_of(source)
  // 332:       .fragment_of fragment_of(self)
  // 333:       .source_position_of source_position_of(self)
  // 334:       .end_position_of end_position_of(self)
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_14, 0);
  // 325: if source.is_a_function_call:
  // 326:   !self
  // 327:     procedure_call
  // 328:       .functor_of functor_of(source)
  // 329:       .output_arguments_of
  // 330:         push(output_arguments_of(source) output_arguments_of(self)(1))
  // 331:       .arguments_of arguments_of(source)
  // 332:       .fragment_of fragment_of(self)
  // 333:       .source_position_of source_position_of(self)
  // 334:       .end_position_of end_position_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__call__simplify_statement_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 335: $final_destinations simplify_arguments(&self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = var._simplify_arguments;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_25;
}
static void cont__compiler__call__simplify_statement_25(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 335: ... final_destinations
  initialize_future(frame->slots[2] /* final_destinations */, frame->slots[3] /* temp__1 */);
  // 336: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_26;
}
static void cont__compiler__call__simplify_statement_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 336: ... functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_27;
}
static void cont__compiler__call__simplify_statement_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 336: ... :
  // 337:   if result_count_of(self).is_defined:
  // 338:     simplify_expression &self.result_count_of
  // 339:   if continuation_of(self).is_defined:
  // 340:     simplify_expression &self.continuation_of
  // 341:   simplify_expression &self.functor_of
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_28, 0);
  // 336: if functor_of(self).is_defined:
  // 337:   if result_count_of(self).is_defined:
  // 338:     simplify_expression &self.result_count_of
  // 339:   if continuation_of(self).is_defined:
  // 340:     simplify_expression &self.continuation_of
  // 341:   simplify_expression &self.functor_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_43;
}
static void entry__compiler__call__simplify_statement_28(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 337: ... result_count_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_29;
}
static void cont__compiler__call__simplify_statement_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 337: ... result_count_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_30;
}
static void cont__compiler__call__simplify_statement_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 337: ... :
  // 338:   simplify_expression &self.result_count_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_31, 0);
  // 337: if result_count_of(self).is_defined:
  // 338:   simplify_expression &self.result_count_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_34;
}
static void entry__compiler__call__simplify_statement_31(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 338: ... self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_32;
}
static void cont__compiler__call__simplify_statement_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 338: simplify_expression &self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_33;
}
static void cont__compiler__call__simplify_statement_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 338: ... &self.result_count_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__result_count_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 339: ... continuation_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_35;
}
static void cont__compiler__call__simplify_statement_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 339: ... continuation_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_36;
}
static void cont__compiler__call__simplify_statement_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 339: ... :
  // 340:   simplify_expression &self.continuation_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_37, 0);
  // 339: if continuation_of(self).is_defined:
  // 340:   simplify_expression &self.continuation_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_40;
}
static void entry__compiler__call__simplify_statement_37(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 340: ... self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_38;
}
static void cont__compiler__call__simplify_statement_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 340: simplify_expression &self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_39;
}
static void cont__compiler__call__simplify_statement_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 340: ... &self.continuation_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__continuation_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 341: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_41;
}
static void cont__compiler__call__simplify_statement_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 341: simplify_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_42;
}
static void cont__compiler__call__simplify_statement_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 341: ... &self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 343: self.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_44;
}
static void cont__compiler__call__simplify_statement_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 343: ... :
  // 344:   $destination output_arguments_of(self)(1)
  // 345:   if destination.is_a_definition:
  // 346:     if
  // 347:       destination.is_a_single_assign_definition:
  // 348:         $source arguments_of(self)(1)
  // 349:         if attribute_kind_of(destination) != NONE:
  // 350:           push &definitions destination = source
  // 351:           return
  // 352:         cond
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_45, 0);
  // 365: :
  // 366:   update_each &self.output_arguments_of: (&argument)
  // 367:     if argument.is_a_definition:
  // 368:       push &definitions argument
  // 369:       !argument.is_an_initialization true
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_87, 0);
  // 342: if
  // 343:   self.is_an_assignment:
  // 344:     $destination output_arguments_of(self)(1)
  // 345:     if destination.is_a_definition:
  // 346:       if
  // 347:         destination.is_a_single_assign_definition:
  // 348:           $source arguments_of(self)(1)
  // 349:           if attribute_kind_of(destination) != NONE:
  // 350:             push &definitions destination = source
  // 351:             return
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_95;
}
static void entry__compiler__call__simplify_statement_71(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // destination: 0
  // source: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 357: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_72;
}
static void cont__compiler__call__simplify_statement_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 357: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_73;
}
static void cont__compiler__call__simplify_statement_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 358: !self.output_arguments_of(1).is_an_initialization true
  frame->slots[3] /* temp__1 */ = get__true();
  // 358: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_74;
}
static void cont__compiler__call__simplify_statement_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 358: ... self.output_arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_75;
}
static void cont__compiler__call__simplify_statement_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 358: !self.output_arguments_of(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[5] /* temp__3 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, frame->slots[3] /* temp__1 */);
    frame->slots[5] /* temp__3 */ = temp;

  }
  // 358: !self.output_arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_76;
}
static void cont__compiler__call__simplify_statement_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 358: !self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_66(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // destination: 0
  // source: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 354: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_67;
}
static void cont__compiler__call__simplify_statement_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 354: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_68;
}
static void cont__compiler__call__simplify_statement_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 355: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_61(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // source: 0
  // destination: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 353: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_62;
}
static void cont__compiler__call__simplify_statement_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 353: ... source.is_single_assign
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_63, 0);
  // 353: ... source.is_a_constant || source.is_single_assign
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_65;
}
static void entry__compiler__call__simplify_statement_63(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 353: ... source.is_single_assign
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_single_assign();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_64;
}
static void cont__compiler__call__simplify_statement_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 353: ... source.is_single_assign
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 353: ... :
  // 354:   push &definitions destination = source
  // 355:   return
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__call__simplify_statement_66, 0);
  // 353: -> source.is_a_constant || source.is_single_assign:
  // 354:   push &definitions destination = source
  // 355:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_69(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // destination: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 356: ... source.might_be_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__might_be_constant();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_70;
}
static void cont__compiler__call__simplify_statement_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 356: ... :
  // 357:   push &definitions destination = source
  // 358:   !self.output_arguments_of(1).is_an_initialization true
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_71, 0);
  // 356: -> source.might_be_constant:
  // 357:   push &definitions destination = source
  // 358:   !self.output_arguments_of(1).is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_77(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // destination: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 360: push &definitions destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_78;
}
static void cont__compiler__call__simplify_statement_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 361: !self.output_arguments_of(1).is_an_initialization true
  frame->slots[2] /* temp__1 */ = get__true();
  // 361: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_79;
}
static void cont__compiler__call__simplify_statement_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 361: ... self.output_arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_80;
}
static void cont__compiler__call__simplify_statement_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 361: !self.output_arguments_of(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__3 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, frame->slots[2] /* temp__1 */);
    frame->slots[4] /* temp__3 */ = temp;

  }
  // 361: !self.output_arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_81;
}
static void cont__compiler__call__simplify_statement_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 361: !self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_51(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // self: 0
  // destination: 1
  // return: 2
  // source: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 348: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_52;
}
static void cont__compiler__call__simplify_statement_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 348: $source arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_53;
}
static void cont__compiler__call__simplify_statement_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* source */, arguments->slots[0]);
  // 349: ... attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_54;
}
static void cont__compiler__call__simplify_statement_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 349: ... attribute_kind_of(destination) != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_55;
}
static void cont__compiler__call__simplify_statement_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 349: ... attribute_kind_of(destination) != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_56;
}
static void cont__compiler__call__simplify_statement_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 349: ... :
  // 350:   push &definitions destination = source
  // 351:   return
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__call__simplify_statement_57, 0);
  // 349: if attribute_kind_of(destination) != NONE:
  // 350:   push &definitions destination = source
  // 351:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_60;
}
static void entry__compiler__call__simplify_statement_57(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // destination: 0
  // source: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 350: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_58;
}
static void cont__compiler__call__simplify_statement_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 350: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_59;
}
static void cont__compiler__call__simplify_statement_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 351: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__call__simplify_statement_60(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: -> source.is_a_constant || source.is_single_assign:
  // 354:   push &definitions destination = source
  // 355:   return
  frame->slots[4] /* temp__1 */ = create_closure(entry__compiler__call__simplify_statement_61, 0);
  // 356: -> source.might_be_constant:
  // 357:   push &definitions destination = source
  // 358:   !self.output_arguments_of(1).is_an_initialization true
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_69, 0);
  // 359: :
  // 360:   push &definitions destination
  // 361:   !self.output_arguments_of(1).is_an_initialization true
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_77, 0);
  // 352: cond
  // 353:   -> source.is_a_constant || source.is_single_assign:
  // 354:     push &definitions destination = source
  // 355:     return
  // 356:   -> source.might_be_constant:
  // 357:     push &definitions destination = source
  // 358:     !self.output_arguments_of(1).is_an_initialization true
  // 359:   :
  // 360:     push &definitions destination
  // 361:     !self.output_arguments_of(1).is_an_initialization true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_82(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // destination: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 363: push &definitions destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_83;
}
static void cont__compiler__call__simplify_statement_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 364: !self.output_arguments_of(1).is_an_initialization true
  frame->slots[2] /* temp__1 */ = get__true();
  // 364: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_84;
}
static void cont__compiler__call__simplify_statement_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 364: ... self.output_arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_85;
}
static void cont__compiler__call__simplify_statement_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 364: !self.output_arguments_of(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__3 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, frame->slots[2] /* temp__1 */);
    frame->slots[4] /* temp__3 */ = temp;

  }
  // 364: !self.output_arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_86;
}
static void cont__compiler__call__simplify_statement_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 364: !self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_49(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // destination: 0
  // self: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 347: destination.is_a_single_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__is_a_single_assign_definition();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_50;
}
static void cont__compiler__call__simplify_statement_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 347: ... :
  // 348:   $source arguments_of(self)(1)
  // 349:   if attribute_kind_of(destination) != NONE:
  // 350:     push &definitions destination = source
  // 351:     return
  // 352:   cond
  // 353:     -> source.is_a_constant || source.is_single_assign:
  // 354:       push &definitions destination = source
  // 355:       return
  // 356:     -> source.might_be_constant:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_51, 0);
  // 362: :
  // 363:   push &definitions destination
  // 364:   !self.output_arguments_of(1).is_an_initialization true
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_82, 0);
  // 346: if
  // 347:   destination.is_a_single_assign_definition:
  // 348:     $source arguments_of(self)(1)
  // 349:     if attribute_kind_of(destination) != NONE:
  // 350:       push &definitions destination = source
  // 351:       return
  // 352:     cond
  // 353:       -> source.is_a_constant || source.is_single_assign:
  // 354:         push &definitions destination = source
  // 355:         return
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
static void entry__compiler__call__simplify_statement_45(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // return: 1
  // destination: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 344: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_46;
}
static void cont__compiler__call__simplify_statement_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 344: $destination output_arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_47;
}
static void cont__compiler__call__simplify_statement_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* destination */, arguments->slots[0]);
  // 345: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_48;
}
static void cont__compiler__call__simplify_statement_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   if
  // 347:     destination.is_a_single_assign_definition:
  // 348:       $source arguments_of(self)(1)
  // 349:       if attribute_kind_of(destination) != NONE:
  // 350:         push &definitions destination = source
  // 351:         return
  // 352:       cond
  // 353:         -> source.is_a_constant || source.is_single_assign:
  // 354:           push &definitions destination = source
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_49, 0);
  // 345: if destination.is_a_definition:
  // 346:   if
  // 347:     destination.is_a_single_assign_definition:
  // 348:       $source arguments_of(self)(1)
  // 349:       if attribute_kind_of(destination) != NONE:
  // 350:         push &definitions destination = source
  // 351:         return
  // 352:       cond
  // 353:         -> source.is_a_constant || source.is_single_assign:
  // 354:           push &definitions destination = source
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_87(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 366: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_88;
}
static void cont__compiler__call__simplify_statement_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 366: update_each &self.output_arguments_of: (&argument)
  // 367:   if argument.is_a_definition:
  // 368:     push &definitions argument
  // 369:     !argument.is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__compiler__call__simplify_statement_89;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_94;
}
static void entry__compiler__call__simplify_statement_89(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 367: ... argument.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_90;
}
static void cont__compiler__call__simplify_statement_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 367: ... :
  // 368:   push &definitions argument
  // 369:   !argument.is_an_initialization true
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_91, 0);
  // 367: if argument.is_a_definition:
  // 368:   push &definitions argument
  // 369:   !argument.is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_93;
}
static void entry__compiler__call__simplify_statement_91(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 368: push &definitions argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_92;
}
static void cont__compiler__call__simplify_statement_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 369: !argument.is_an_initialization true
  frame->slots[1] /* temp__1 */ = get__true();
  // 369: !argument.is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_93(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 366: ... &self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_95(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 370: push &statements self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_96;
}
static void cont__compiler__call__simplify_statement_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 371: ... final_destinations.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* final_destinations */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_97;
}
static void cont__compiler__call__simplify_statement_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 371: ... :
  // 372:   for_each final_destinations: (idx destination)
  // 373:     if destination.is_defined:
  // 374:       $result
  // 375:         output_arguments_of(self)(idx)
  // 376:           .is_an_optional_item false
  // 377:           .is_an_expanded_item false
  // 378:       
  // 379:       if
  // 380:         destination.is_a_function_call:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_98, 0);
  // 371: if final_destinations.is_defined:
  // 372:   for_each final_destinations: (idx destination)
  // 373:     if destination.is_defined:
  // 374:       $result
  // 375:         output_arguments_of(self)(idx)
  // 376:           .is_an_optional_item false
  // 377:           .is_an_expanded_item false
  // 378:       
  // 379:       if
  // 380:         destination.is_a_function_call:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_117;
}
static void entry__compiler__call__simplify_statement_105(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // destination: 0
  // result: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 381: store_result destination result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* result */;
  result_count = frame->caller_result_count;
  myself = var._store_result;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_106(void) {
  allocate_initialized_frame_gc(2, 9);
  // slot allocations:
  // destination: 0
  // result: 1
  // identifier: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* result */
  frame->slots[2] /* identifier */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 389: destination.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_107;
}
static void cont__compiler__call__simplify_statement_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 390: -> destination
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_108, 0);
  // 391: -> identifier_of(destination)
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_109, 0);
  // 387: $identifier
  // 388:   if
  // 389:     destination.is_an_identifier
  // 390:     -> destination
  // 391:     -> identifier_of(destination)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_111;
}
static void entry__compiler__call__simplify_statement_108(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 390: -> destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_109(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 391: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_110;
}
static void cont__compiler__call__simplify_statement_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 391: -> identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* identifier */, arguments->slots[0]);
  // 395: ... list(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_112;
}
static void cont__compiler__call__simplify_statement_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 396: ... list(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* result */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_113;
}
static void cont__compiler__call__simplify_statement_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 397: ... fragment_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_114;
}
static void cont__compiler__call__simplify_statement_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 398: ... source_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_115;
}
static void cont__compiler__call__simplify_statement_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 399: ... end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_116;
}
static void cont__compiler__call__simplify_statement_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__6 */ = arguments->slots[0];
  // 394: assignment
  // 395:   .output_arguments_of list(destination)
  // 396:   .arguments_of list(result)
  // 397:   .fragment_of fragment_of(identifier)
  // 398:   .source_position_of source_position_of(identifier)
  // 399:   .end_position_of end_position_of(identifier)
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[5] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[6] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[7] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[8] /* temp__6 */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 393: simplify_statement
  // 394:   assignment
  // 395:     .output_arguments_of list(destination)
  // 396:     .arguments_of list(result)
  // 397:     .fragment_of fragment_of(identifier)
  // 398:     .source_position_of source_position_of(identifier)
  // 399:     .end_position_of end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__simplify_statement();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_101(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // self: 0
  // idx: 1
  // destination: 2
  // result: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* self */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[3] /* result */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 375: output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_102;
}
static void cont__compiler__call__simplify_statement_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 375: output_arguments_of(self)(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[5] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_103;
}
static void cont__compiler__call__simplify_statement_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 374: $result
  // 375:   output_arguments_of(self)(idx)
  // 376:     .is_an_optional_item false
  // 377:     .is_an_expanded_item false
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__false());
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, get__false());
    initialize_future(frame->slots[3] /* result */, temp);

  }
  // 380: destination.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_104;
}
static void cont__compiler__call__simplify_statement_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 380: ... :
  // 381:   store_result destination result
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_105, 0);
  // 382: :
  // 383:   #
  // 384:     ATTENTION: strange - only two source code files have destinations
  // 385:     that actually are identifier nodes - maybe an error in the AST?
  // 386:   
  // 387:   $identifier
  // 388:     if
  // 389:       destination.is_an_identifier
  // 390:       -> destination
  // 391:       -> identifier_of(destination)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_106, 0);
  // 379: if
  // 380:   destination.is_a_function_call:
  // 381:     store_result destination result
  // 382:   :
  // 383:     #
  // 384:       ATTENTION: strange - only two source code files have destinations
  // 385:       that actually are identifier nodes - maybe an error in the AST?
  // 386:     
  // 387:     $identifier
  // 388:       if
  // ...
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
static void entry__compiler__call__simplify_statement_99(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // idx: 0
  // destination: 1
  // self: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 373: ... destination.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_100;
}
static void cont__compiler__call__simplify_statement_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 373: ... :
  // 374:   $result
  // 375:     output_arguments_of(self)(idx)
  // 376:       .is_an_optional_item false
  // 377:       .is_an_expanded_item false
  // 378:   
  // 379:   if
  // 380:     destination.is_a_function_call:
  // 381:       store_result destination result
  // 382:     :
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_101, 0);
  // 373: if destination.is_defined:
  // 374:   $result
  // 375:     output_arguments_of(self)(idx)
  // 376:       .is_an_optional_item false
  // 377:       .is_an_expanded_item false
  // 378:   
  // 379:   if
  // 380:     destination.is_a_function_call:
  // 381:       store_result destination result
  // 382:     :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_98(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // final_destinations: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* final_destinations */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 372: ... : (idx destination)
  // 373:   if destination.is_defined:
  // 374:     $result
  // 375:       output_arguments_of(self)(idx)
  // 376:         .is_an_optional_item false
  // 377:         .is_an_expanded_item false
  // 378:     
  // 379:     if
  // 380:       destination.is_a_function_call:
  // 381:         store_result destination result
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__call__simplify_statement_99, 2);
  // 372: for_each final_destinations: (idx destination)
  // 373:   if destination.is_defined:
  // 374:     $result
  // 375:       output_arguments_of(self)(idx)
  // 376:         .is_an_optional_item false
  // 377:         .is_an_expanded_item false
  // 378:     
  // 379:     if
  // 380:       destination.is_a_function_call:
  // 381:         store_result destination result
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* final_destinations */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__call__simplify_statement_117(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__function_call__simplify_expression_1(void) {
  allocate_initialized_frame_gc(1, 10);
  // slot allocations:
  // self: 0
  // temp: 1
  frame->slots[1] /* temp */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 405: show_compiler_debug_info "simplify function call"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__95014404e5c0e88d;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_3;
}
static void cont__compiler__function_call__simplify_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 406: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_4;
}
static void cont__compiler__function_call__simplify_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* temp */, arguments->slots[0]);
  // 409: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_5;
}
static void cont__compiler__function_call__simplify_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 410: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_6;
}
static void cont__compiler__function_call__simplify_expression_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 410: ... push(output_arguments_of(self) temp)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  arguments->slots[1] = frame->slots[1] /* temp */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_7;
}
static void cont__compiler__function_call__simplify_expression_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 411: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_8;
}
static void cont__compiler__function_call__simplify_expression_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 412: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_9;
}
static void cont__compiler__function_call__simplify_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 413: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_10;
}
static void cont__compiler__function_call__simplify_expression_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 414: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_11;
}
static void cont__compiler__function_call__simplify_expression_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 408: procedure_call
  // 409:   .functor_of functor_of(self)
  // 410:   .output_arguments_of push(output_arguments_of(self) temp)
  // 411:   .arguments_of arguments_of(self)
  // 412:   .fragment_of fragment_of(self)
  // 413:   .source_position_of source_position_of(self)
  // 414:   .end_position_of end_position_of(self)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[3] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[7] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[8] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[9] /* temp__8 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 407: simplify_statement
  // 408:   procedure_call
  // 409:     .functor_of functor_of(self)
  // 410:     .output_arguments_of push(output_arguments_of(self) temp)
  // 411:     .arguments_of arguments_of(self)
  // 412:     .fragment_of fragment_of(self)
  // 413:     .source_position_of source_position_of(self)
  // 414:     .end_position_of end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_12;
}
static void cont__compiler__function_call__simplify_expression_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 415: -> temp
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__attribute_value_pair__simplify_expression_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // dummy_destinations: 1
  frame->slots[1] /* dummy_destinations */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 421: show_compiler_debug_info "simplify attribute-value pair"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__cced2f4d969d3d03;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair__simplify_expression_3;
}
static void cont__compiler__attribute_value_pair__simplify_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 422: simplify_arguments &self $_dummy_destinations
  // 423:   # There must not be any output arguments!!!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = var._simplify_arguments;
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair__simplify_expression_4;
}
static void cont__compiler__attribute_value_pair__simplify_expression_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 422: ... _dummy_destinations
  initialize_future(frame->slots[1] /* dummy_destinations */, frame->slots[2] /* temp__1 */);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__attribute_function_pair__simplify_expression_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // dummy_destinations: 1
  frame->slots[1] /* dummy_destinations */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 429: show_compiler_debug_info "simplify attribute-function pair"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__83e573190949a328;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__simplify_expression_3;
}
static void cont__compiler__attribute_function_pair__simplify_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 430: simplify_arguments &self $_dummy_destinations
  // 431:   # There must not be any output arguments!!!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = var._simplify_arguments;
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__simplify_expression_4;
}
static void cont__compiler__attribute_function_pair__simplify_expression_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 430: ... _dummy_destinations
  initialize_future(frame->slots[1] /* dummy_destinations */, frame->slots[2] /* temp__1 */);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__c_code__simplify_statement_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 437: show_compiler_debug_info "simplify C-code"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1095e9f11fb0974b;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_3;
}
static void cont__compiler__c_code__simplify_statement_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 438: push &actions: !use_inline_c true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = func__compiler__c_code__simplify_statement_4;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_5;
}
static void entry__compiler__c_code__simplify_statement_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 438: ... !use_inline_c true
  set__use_inline_c(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__c_code__simplify_statement_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 440: kind_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_6;
}
static void cont__compiler__c_code__simplify_statement_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 441: ... :
  // 442:   $name name_of(identifier_of(self))
  // 443:   push &actions: !defined_structs(name) true
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__c_code__simplify_statement_7, 0);
  // 444: ... :
  // 445:   $name name_of(identifier_of(self))
  // 446:   push &actions: !defined_nodes(name) self
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__c_code__simplify_statement_13, 0);
  // 447: ... :
  // 448:   $name behind(source_of(self) .before. '(' alt(' ' '*') -1)
  // 449:   push &actions: !defined_functions(name) true
  frame->slots[4] /* temp__4 */ = create_closure(entry__compiler__c_code__simplify_statement_19, 0);
  // 439: case
  // 440:   kind_of(self)
  // 441:   "struct":
  // 442:     $name name_of(identifier_of(self))
  // 443:     push &actions: !defined_structs(name) true
  // 444:   "node":
  // 445:     $name name_of(identifier_of(self))
  // 446:     push &actions: !defined_nodes(name) self
  // 447:   "function":
  // 448:     $name behind(source_of(self) .before. '(' alt(' ' '*') -1)
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__7c1f530901a312a3;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  arguments->slots[3] = string__1e0aea8b5d407d5c;
  arguments->slots[4] = frame->slots[3] /* temp__3 */;
  arguments->slots[5] = string__46c0af9104ada08e;
  arguments->slots[6] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_31;
}
static void entry__compiler__c_code__simplify_statement_7(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: ... identifier_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_8;
}
static void cont__compiler__c_code__simplify_statement_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 442: $name name_of(identifier_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_9;
}
static void cont__compiler__c_code__simplify_statement_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 443: ... : !defined_structs(name) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__c_code__simplify_statement_10, 0);
  // 443: push &actions: !defined_structs(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_12;
}
static void entry__compiler__c_code__simplify_statement_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 443: ... !defined_structs(name) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 443: ... !defined_structs(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__defined_structs();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_11;
}
static void cont__compiler__c_code__simplify_statement_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_structs(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__c_code__simplify_statement_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__c_code__simplify_statement_13(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 445: ... identifier_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_14;
}
static void cont__compiler__c_code__simplify_statement_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 445: $name name_of(identifier_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_15;
}
static void cont__compiler__c_code__simplify_statement_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 446: ... : !defined_nodes(name) self
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__c_code__simplify_statement_16, 0);
  // 446: push &actions: !defined_nodes(name) self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_18;
}
static void entry__compiler__c_code__simplify_statement_16(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 446: ... !defined_nodes(name) self
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* self */;
  // 446: ... !defined_nodes(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__defined_nodes();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_17;
}
static void cont__compiler__c_code__simplify_statement_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_nodes(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__c_code__simplify_statement_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__c_code__simplify_statement_19(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 448: ... source_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_20;
}
static void cont__compiler__c_code__simplify_statement_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 448: ... source_of(self) .before. '('
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__40;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_21;
}
static void cont__compiler__c_code__simplify_statement_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 448: ... alt(' ' '*')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_22;
}
static void cont__compiler__c_code__simplify_statement_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 448: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_23;
}
static void cont__compiler__c_code__simplify_statement_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 448: $name behind(source_of(self) .before. '(' alt(' ' '*') -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_24;
}
static void cont__compiler__c_code__simplify_statement_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 449: ... : !defined_functions(name) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__c_code__simplify_statement_25, 0);
  // 449: push &actions: !defined_functions(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_27;
}
static void entry__compiler__c_code__simplify_statement_25(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 449: ... !defined_functions(name) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 449: ... !defined_functions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__defined_functions();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_26;
}
static void cont__compiler__c_code__simplify_statement_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_functions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__c_code__simplify_statement_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__c_code__simplify_statement_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 450: push &definitions self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__c_code__simplify_statement_32;
}
static void cont__compiler__c_code__simplify_statement_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__c_body__simplify_expression_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 456: show_compiler_debug_info "simplify C-body"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1295e9f11fb09757;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__c_body__simplify_expression_3;
}
static void cont__compiler__c_body__simplify_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 457: push &actions: !use_inline_c true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = func__compiler__c_body__simplify_expression_4;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__c_body__simplify_expression_5;
}
static void entry__compiler__c_body__simplify_expression_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 457: ... !use_inline_c true
  set__use_inline_c(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__c_body__simplify_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__simplifier(void) {
  var.compiler__simplify_statement = collect_node(var.compiler__simplify_statement);
  var.compiler__simplify_expression = collect_node(var.compiler__simplify_expression);
  var._temporary_identifier = collect_node(var._temporary_identifier);
  var._simplify_arguments = collect_node(var._simplify_arguments);
  var.compiler__check_usage = collect_node(var.compiler__check_usage);
  var._do_store = collect_node(var._do_store);
  var._store_result = collect_node(var._store_result);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__simplifier(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__simplifier(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("simplifier");
  number__0 = from_uint32(0U);
  character__40 = from_uchar32(40);
  character__32 = from_uchar32(32);
  number__1 = from_uint32(1U);
  character__42 = from_uchar32(42);
  define_polymorphic_function("compiler", "simplify_statement", get__compiler__simplify_statement, &poly_idx__compiler__simplify_statement, &var.compiler__simplify_statement);
  define_polymorphic_function("compiler", "simplify_expression", get__compiler__simplify_expression, &poly_idx__compiler__simplify_expression, &var.compiler__simplify_expression);
  string__421f524a80420288 = from_latin_1_string("temp__", 6);
  func__temporary_identifier_1 = create_function(entry__temporary_identifier_1, 0);
  func__simplify_arguments_3 = create_function(entry__simplify_arguments_3, 1);
  func__simplify_arguments_1 = create_function(entry__simplify_arguments_1, 1);
  string__9ee981055a49a5fe = from_latin_1_string("Invalid access to polymorphic function \042", 40);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__6b008858b3a1b4b2 = from_latin_1_string("Invalid access to read-only variable \042", 38);
  string__2ddd7194c0185268 = from_latin_1_string("Invalid access to static read-write variable \042", 46);
  string__e971e37f901b36b = from_latin_1_string("Invalid access to dynamic read-only variable \042", 46);
  string__611f619f08c2e7ef = from_latin_1_string("Invalid access to dynamic read-write variable \042", 47);
  func__compiler__check_usage_1 = create_function(entry__compiler__check_usage_1, 3);
  string__4a1f5794bff5c237 = from_latin_1_string("simplify statement (default)", 28);
  func__types__grammar_node__simplify_statement_1 = create_function(entry__types__grammar_node__simplify_statement_1, 1);
  string__5af95dddc656868 = from_latin_1_string("simplify expression (default)", 29);
  func__types__grammar_node__simplify_expression_1 = create_function(entry__types__grammar_node__simplify_expression_1, 1);
  string__867252dcb87a57b1 = from_latin_1_string("simplify body", 13);
  string__b18861f6a8c886ba = from_latin_1_string("An identifier named \042", 21);
  string__ff65db3940410371 = from_latin_1_string("\042 was already defined in an outer scope or in a used namespace", 62);
  func__compiler__body__simplify_expression_1 = create_function(entry__compiler__body__simplify_expression_1, 1);
  func__do_store_5 = create_function(entry__do_store_5, 1);
  func__do_store_45 = create_function(entry__do_store_45, 0);
  func__do_store_46 = create_function(entry__do_store_46, 0);
  func__do_store_1 = create_function(entry__do_store_1, 5);
  func__store_result_1 = create_function(entry__store_result_1, -1);
  string__8629329e514f7a7a = from_latin_1_string("simplify statement", 18);
  func__compiler__call__simplify_statement_89 = create_function(entry__compiler__call__simplify_statement_89, 1);
  func__compiler__call__simplify_statement_1 = create_function(entry__compiler__call__simplify_statement_1, 1);
  string__95014404e5c0e88d = from_latin_1_string("simplify function call", 22);
  func__compiler__function_call__simplify_expression_1 = create_function(entry__compiler__function_call__simplify_expression_1, 1);
  string__cced2f4d969d3d03 = from_latin_1_string("simplify attribute-value pair", 29);
  func__compiler__attribute_value_pair__simplify_expression_1 = create_function(entry__compiler__attribute_value_pair__simplify_expression_1, 1);
  string__83e573190949a328 = from_latin_1_string("simplify attribute-function pair", 32);
  func__compiler__attribute_function_pair__simplify_expression_1 = create_function(entry__compiler__attribute_function_pair__simplify_expression_1, 1);
  string__1095e9f11fb0974b = from_latin_1_string("simplify C-code", 15);
  func__compiler__c_code__simplify_statement_4 = create_function(entry__compiler__c_code__simplify_statement_4, 0);
  string__7c1f530901a312a3 = from_latin_1_string("struct", 6);
  string__1e0aea8b5d407d5c = from_latin_1_string("node", 4);
  string__46c0af9104ada08e = from_latin_1_string("function", 8);
  func__compiler__c_code__simplify_statement_1 = create_function(entry__compiler__c_code__simplify_statement_1, 1);
  string__1295e9f11fb09757 = from_latin_1_string("simplify C-body", 15);
  func__compiler__c_body__simplify_expression_4 = create_function(entry__compiler__c_body__simplify_expression_4, 0);
  func__compiler__c_body__simplify_expression_1 = create_function(entry__compiler__c_body__simplify_expression_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__simplifier(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("simplifier");
  set_used_namespaces(used_namespaces);
  register_dynamic(&dyna_idx__defined_names);
  define__defined_names(create_future());
  register_dynamic(&dyna_idx__inherited_names);
  define__inherited_names(create_future());
  define_single_assign_static("compiler", "check_usage", get__compiler__check_usage, &var.compiler__check_usage);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__simplifier(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("simplifier");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "DYNAMIC_MULTI", &get__DYNAMIC_MULTI, &get_value_or_future__DYNAMIC_MULTI);
  use_read_only(NULL, "DYNAMIC_SINGLE", &get__DYNAMIC_SINGLE, &get_value_or_future__DYNAMIC_SINGLE);
  use_read_only(NULL, "NONE", &get__NONE, &get_value_or_future__NONE);
  use_read_only(NULL, "POLYMORPHIC", &get__POLYMORPHIC, &get_value_or_future__POLYMORPHIC);
  use_read_only(NULL, "STATIC_MULTI", &get__STATIC_MULTI, &get_value_or_future__STATIC_MULTI);
  use_read_only(NULL, "STATIC_SINGLE", &get__STATIC_SINGLE, &get_value_or_future__STATIC_SINGLE);
  use_read_only(NULL, "SyntaxError", &get__SyntaxError, &get_value_or_future__SyntaxError);
  use_read_write(NULL, "actions", &get__actions, &set__actions);
  use_single_assign_dynamic(NULL, "already_defined_names", &get__already_defined_names, &define__already_defined_names);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_read_only(NULL, "assignment", &get__assignment, &get_value_or_future__assignment);
  use_read_only(NULL, "attribute_function_pair", &get__attribute_function_pair, &get_value_or_future__attribute_function_pair);
  use_read_only(NULL, "attribute_kind_of", &get__attribute_kind_of, &get_value_or_future__attribute_kind_of);
  use_read_only(NULL, "attribute_value_pair", &get__attribute_value_pair, &get_value_or_future__attribute_value_pair);
  use_read_only(NULL, "before", &get__before, &get_value_or_future__before);
  use_read_only(NULL, "behind", &get__behind, &get_value_or_future__behind);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "check_usage", &get__check_usage, &get_value_or_future__check_usage);
  use_read_only("compiler", "attribute_function_pair", &get__compiler__attribute_function_pair, &get_value_or_future__compiler__attribute_function_pair);
  use_read_only("compiler", "attribute_value_pair", &get__compiler__attribute_value_pair, &get_value_or_future__compiler__attribute_value_pair);
  use_read_only("compiler", "body", &get__compiler__body, &get_value_or_future__compiler__body);
  use_read_only("compiler", "c_body", &get__compiler__c_body, &get_value_or_future__compiler__c_body);
  use_read_only("compiler", "c_code", &get__compiler__c_code, &get_value_or_future__compiler__c_code);
  use_read_only("compiler", "call", &get__compiler__call, &get_value_or_future__compiler__call);
  use_read_only("compiler", "function_call", &get__compiler__function_call, &get_value_or_future__compiler__function_call);
  use_multi_assign_dynamic("compiler", "temp_idx", &get__compiler__temp_idx, &set__compiler__temp_idx, &define__compiler__temp_idx);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_polymorphic_function(NULL, "continuation_of", &get__continuation_of, &poly_idx__continuation_of);
  use_polymorphic_function(NULL, "default_value_of", &get__default_value_of, &poly_idx__default_value_of);
  use_read_write(NULL, "defined_functions", &get__defined_functions, &set__defined_functions);
  use_read_only(NULL, "defined_names_of", &get__defined_names_of, &get_value_or_future__defined_names_of);
  use_read_write(NULL, "defined_nodes", &get__defined_nodes, &set__defined_nodes);
  use_read_write(NULL, "defined_structs", &get__defined_structs, &set__defined_structs);
  use_multi_assign_dynamic(NULL, "definitions", &get__definitions, &set__definitions, &define__definitions);
  use_polymorphic_function(NULL, "definitions_of", &get__definitions_of, &poly_idx__definitions_of);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "drop", &get__drop, &get_value_or_future__drop);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_polymorphic_function(NULL, "end_position_of", &get__end_position_of, &poly_idx__end_position_of);
  use_read_only(NULL, "extend_to", &get__extend_to, &get_value_or_future__extend_to);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_polymorphic_function(NULL, "fragment_of", &get__fragment_of, &poly_idx__fragment_of);
  use_polymorphic_function(NULL, "functor_of", &get__functor_of, &poly_idx__functor_of);
  use_polymorphic_function(NULL, "identifier_of", &get__identifier_of, &poly_idx__identifier_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_polymorphic_function(NULL, "inherited_names_of", &get__inherited_names_of, &poly_idx__inherited_names_of);
  use_read_only(NULL, "is_a_constant", &get__is_a_constant, &get_value_or_future__is_a_constant);
  use_read_only(NULL, "is_a_definition", &get__is_a_definition, &get_value_or_future__is_a_definition);
  use_read_only(NULL, "is_a_function_call", &get__is_a_function_call, &get_value_or_future__is_a_function_call);
  use_read_only(NULL, "is_a_list", &get__is_a_list, &get_value_or_future__is_a_list);
  use_read_only(NULL, "is_a_method_definition", &get__is_a_method_definition, &get_value_or_future__is_a_method_definition);
  use_read_only(NULL, "is_a_multi_assign_definition", &get__is_a_multi_assign_definition, &get_value_or_future__is_a_multi_assign_definition);
  use_read_only(NULL, "is_a_remark", &get__is_a_remark, &get_value_or_future__is_a_remark);
  use_read_only(NULL, "is_a_single_assign_definition", &get__is_a_single_assign_definition, &get_value_or_future__is_a_single_assign_definition);
  use_read_only(NULL, "is_a_static_single_definition", &get__is_a_static_single_definition, &get_value_or_future__is_a_static_single_definition);
  use_read_only(NULL, "is_a_temporary", &get__is_a_temporary, &get_value_or_future__is_a_temporary);
  use_read_only(NULL, "is_an_assignment", &get__is_an_assignment, &get_value_or_future__is_an_assignment);
  use_read_only(NULL, "is_an_attribute_access", &get__is_an_attribute_access, &get_value_or_future__is_an_attribute_access);
  use_polymorphic_function(NULL, "is_an_expanded_item", &get__is_an_expanded_item, &poly_idx__is_an_expanded_item);
  use_read_only(NULL, "is_an_identifier", &get__is_an_identifier, &get_value_or_future__is_an_identifier);
  use_polymorphic_function(NULL, "is_an_initialization", &get__is_an_initialization, &poly_idx__is_an_initialization);
  use_polymorphic_function(NULL, "is_an_optional_item", &get__is_an_optional_item, &poly_idx__is_an_optional_item);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_single_assign", &get__is_single_assign, &get_value_or_future__is_single_assign);
  use_read_only(NULL, "kind_of", &get__kind_of, &get_value_or_future__kind_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "might_be_constant", &get__might_be_constant, &get_value_or_future__might_be_constant);
  use_polymorphic_function(NULL, "name_of", &get__name_of, &poly_idx__name_of);
  use_polymorphic_function(NULL, "output_arguments_of", &get__output_arguments_of, &poly_idx__output_arguments_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_read_only(NULL, "peek", &get__peek, &get_value_or_future__peek);
  use_read_only(NULL, "pop", &get__pop, &get_value_or_future__pop);
  use_read_only(NULL, "procedure_call", &get__procedure_call, &get_value_or_future__procedure_call);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "result_count_of", &get__result_count_of, &poly_idx__result_count_of);
  use_read_only(NULL, "show_compiler_debug_info", &get__show_compiler_debug_info, &get_value_or_future__show_compiler_debug_info);
  use_polymorphic_function(NULL, "simplify_expression", &get__simplify_expression, &poly_idx__simplify_expression);
  use_polymorphic_function(NULL, "simplify_statement", &get__simplify_statement, &poly_idx__simplify_statement);
  use_read_only(NULL, "source_of", &get__source_of, &get_value_or_future__source_of);
  use_polymorphic_function(NULL, "source_position_of", &get__source_position_of, &poly_idx__source_position_of);
  use_multi_assign_dynamic(NULL, "statements", &get__statements, &set__statements, &define__statements);
  use_polymorphic_function(NULL, "statements_of", &get__statements_of, &poly_idx__statements_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_write(NULL, "temp_idx", &get__temp_idx, &set__temp_idx);
  use_read_only(NULL, "temporary", &get__temporary, &get_value_or_future__temporary);
  use_polymorphic_function(NULL, "temporary_count_of", &get__temporary_count_of, &poly_idx__temporary_count_of);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "grammar_node", &get__types__grammar_node, &get_value_or_future__types__grammar_node);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "update_each", &get__update_each, &get_value_or_future__update_each);
  use_read_write(NULL, "use_inline_c", &get__use_inline_c, &set__use_inline_c);
  use_read_only(NULL, "used_names_of", &get__used_names_of, &get_value_or_future__used_names_of);
  use_read_only(NULL, "variable_kind_of", &get__variable_kind_of, &get_value_or_future__variable_kind_of);
  define_method("types", "grammar_node", poly_idx__simplify_statement, func__types__grammar_node__simplify_statement_1);
  define_method("types", "grammar_node", poly_idx__simplify_expression, func__types__grammar_node__simplify_expression_1);
  define_method("compiler", "body", poly_idx__simplify_expression, func__compiler__body__simplify_expression_1);
  define_method("compiler", "call", poly_idx__simplify_statement, func__compiler__call__simplify_statement_1);
  define_method("compiler", "function_call", poly_idx__simplify_expression, func__compiler__function_call__simplify_expression_1);
  define_method("compiler", "attribute_value_pair", poly_idx__simplify_expression, func__compiler__attribute_value_pair__simplify_expression_1);
  define_method("compiler", "attribute_function_pair", poly_idx__simplify_expression, func__compiler__attribute_function_pair__simplify_expression_1);
  define_method("compiler", "c_code", poly_idx__simplify_statement, func__compiler__c_code__simplify_statement_1);
  define_method("compiler", "c_body", poly_idx__simplify_expression, func__compiler__c_body__simplify_expression_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__simplifier(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.compiler__simplify_statement, create_function(type__compiler__simplify_statement, -1));
  assign_value(&var.compiler__simplify_expression, create_function(type__compiler__simplify_expression, -1));
  maybe_initialize_future(get__defined_names(), get__empty_table());
  maybe_initialize_future(get__inherited_names(), get__empty_table());
  assign_variable(&var._temporary_identifier, &func__temporary_identifier_1);
  assign_variable(&var._simplify_arguments, &func__simplify_arguments_1);
  assign_variable(&var.compiler__check_usage, &func__compiler__check_usage_1);
  assign_variable(&var._do_store, &func__do_store_1);
  assign_variable(&var._store_result, &func__store_result_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__simplifier(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__simplifier);
}
