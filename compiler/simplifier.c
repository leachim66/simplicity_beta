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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
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
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_cell(void);
IMPORT NODE *undefined;
IMPORT NODE *create_continuation(void);
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
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
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
static int poly_idx__is_a_destination;
static NODE_GETTER get__is_a_destination;
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
static int poly_idx__is_an_input_output_argument;
static NODE_GETTER get__is_an_input_output_argument;
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
static NODE_GETTER get__not;
static NODE_GETTER get_value_or_future__not;
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
static NODE_GETTER get__put;
static NODE_GETTER get_value_or_future__put;
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
  NODE *_simplify_input_arguments;
  NODE *_simplify_output_arguments;
  NODE *_do_store;
  NODE *_store_result;
  NODE *compiler__simplify_statement;
  NODE *compiler__simplify_expression;
  NODE *compiler__check_usage;
} var;
static const char *var_names[] = {
  "temporary_identifier",
  "simplify_input_arguments",
  "simplify_output_arguments",
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
static NODE *func__simplify_input_arguments_1;
static void entry__simplify_input_arguments_1(void);
static FRAME_INFO frame__simplify_input_arguments_1 = {1, {"input_arguments"}};
static NODE *func__simplify_input_arguments_2;
static void entry__simplify_input_arguments_2(void);
static FRAME_INFO frame__simplify_input_arguments_2 = {1, {"argument"}};
static NODE *func__simplify_input_arguments_3;
static void entry__simplify_input_arguments_3(void);
static FRAME_INFO frame__simplify_input_arguments_3 = {1, {"argument"}};
static void cont__simplify_input_arguments_4(void);
static NODE *func__simplify_input_arguments_5;
static void entry__simplify_input_arguments_5(void);
static FRAME_INFO frame__simplify_input_arguments_5 = {1, {"argument"}};
static void cont__simplify_input_arguments_6(void);
static NODE *func__simplify_input_arguments_7;
static void entry__simplify_input_arguments_7(void);
static FRAME_INFO frame__simplify_input_arguments_7 = {1, {"argument"}};
static void cont__simplify_input_arguments_8(void);
static NODE *func__simplify_input_arguments_9;
static void entry__simplify_input_arguments_9(void);
static FRAME_INFO frame__simplify_input_arguments_9 = {1, {"argument"}};
static void cont__simplify_input_arguments_10(void);
static NODE *func__simplify_input_arguments_11;
static void entry__simplify_input_arguments_11(void);
static FRAME_INFO frame__simplify_input_arguments_11 = {1, {"argument"}};
static void cont__simplify_input_arguments_12(void);
static void cont__simplify_input_arguments_13(void);
static void cont__simplify_input_arguments_14(void);
static NODE *func__simplify_output_arguments_1;
static void entry__simplify_output_arguments_1(void);
static FRAME_INFO frame__simplify_output_arguments_1 = {2, {"output_arguments", "final_destinations"}};
static void cont__simplify_output_arguments_2(void);
static NODE *func__simplify_output_arguments_3;
static void entry__simplify_output_arguments_3(void);
static FRAME_INFO frame__simplify_output_arguments_3 = {3, {"output_arguments", "final_destinations", "first_temporary_index"}};
static NODE *func__simplify_output_arguments_4;
static void entry__simplify_output_arguments_4(void);
static FRAME_INFO frame__simplify_output_arguments_4 = {3, {"break", "output_arguments", "first_temporary_index"}};
static NODE *func__simplify_output_arguments_5;
static void entry__simplify_output_arguments_5(void);
static FRAME_INFO frame__simplify_output_arguments_5 = {5, {"idx", "argument", "output_arguments", "first_temporary_index", "break"}};
static void cont__simplify_output_arguments_6(void);
static void cont__simplify_output_arguments_7(void);
static NODE *func__simplify_output_arguments_8;
static void entry__simplify_output_arguments_8(void);
static FRAME_INFO frame__simplify_output_arguments_8 = {2, {"argument", "output_arguments"}};
static void cont__simplify_output_arguments_9(void);
static NODE *func__simplify_output_arguments_10;
static void entry__simplify_output_arguments_10(void);
static FRAME_INFO frame__simplify_output_arguments_10 = {1, {"output_arguments"}};
static void cont__simplify_output_arguments_11(void);
static void cont__simplify_output_arguments_12(void);
static void cont__simplify_output_arguments_13(void);
static NODE *func__simplify_output_arguments_14;
static void entry__simplify_output_arguments_14(void);
static FRAME_INFO frame__simplify_output_arguments_14 = {1, {"argument"}};
static void cont__simplify_output_arguments_15(void);
static void cont__simplify_output_arguments_16(void);
static void cont__simplify_output_arguments_17(void);
static NODE *func__simplify_output_arguments_18;
static void entry__simplify_output_arguments_18(void);
static FRAME_INFO frame__simplify_output_arguments_18 = {3, {"first_temporary_index", "idx", "break"}};
static void cont__simplify_output_arguments_19(void);
static void cont__simplify_output_arguments_20(void);
static void cont__simplify_output_arguments_21(void);
static NODE *func__simplify_output_arguments_22;
static void entry__simplify_output_arguments_22(void);
static FRAME_INFO frame__simplify_output_arguments_22 = {3, {"final_destinations", "output_arguments", "first_temporary_index"}};
static NODE *func__simplify_output_arguments_23;
static void entry__simplify_output_arguments_23(void);
static FRAME_INFO frame__simplify_output_arguments_23 = {4, {"idx", "argument", "first_temporary_index", "final_destinations"}};
static void cont__simplify_output_arguments_24(void);
static NODE *func__simplify_output_arguments_25;
static void entry__simplify_output_arguments_25(void);
static FRAME_INFO frame__simplify_output_arguments_25 = {1, {"argument"}};
static void cont__simplify_output_arguments_26(void);
static void cont__simplify_output_arguments_27(void);
static NODE *func__simplify_output_arguments_28;
static void entry__simplify_output_arguments_28(void);
static FRAME_INFO frame__simplify_output_arguments_28 = {1, {"final_destinations"}};
static void cont__simplify_output_arguments_29(void);
static NODE *func__simplify_output_arguments_30;
static void entry__simplify_output_arguments_30(void);
static FRAME_INFO frame__simplify_output_arguments_30 = {3, {"argument", "final_destinations", "temp"}};
static void cont__simplify_output_arguments_31(void);
static NODE *func__simplify_output_arguments_32;
static void entry__simplify_output_arguments_32(void);
static FRAME_INFO frame__simplify_output_arguments_32 = {2, {"argument", "temp"}};
static void cont__simplify_output_arguments_33(void);
static NODE *func__simplify_output_arguments_34;
static void entry__simplify_output_arguments_34(void);
static FRAME_INFO frame__simplify_output_arguments_34 = {2, {"argument", "temp"}};
static NODE *func__simplify_output_arguments_35;
static void entry__simplify_output_arguments_35(void);
static FRAME_INFO frame__simplify_output_arguments_35 = {2, {"argument", "temp"}};
static void cont__simplify_output_arguments_36(void);
static NODE *func__simplify_output_arguments_37;
static void entry__simplify_output_arguments_37(void);
static FRAME_INFO frame__simplify_output_arguments_37 = {2, {"argument", "temp"}};
static void cont__simplify_output_arguments_38(void);
static void cont__simplify_output_arguments_39(void);
static void cont__simplify_output_arguments_40(void);
static void cont__simplify_output_arguments_41(void);
static void cont__simplify_output_arguments_42(void);
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
static NODE *func__compiler__body__simplify_expression_49;
static void entry__compiler__body__simplify_expression_49(void);
static FRAME_INFO frame__compiler__body__simplify_expression_49 = {2, {"default_value", "parameter"}};
static void cont__compiler__body__simplify_expression_50(void);
static void cont__compiler__body__simplify_expression_51(void);
static void cont__compiler__body__simplify_expression_52(void);
static void cont__compiler__body__simplify_expression_53(void);
static NODE *func__compiler__body__simplify_expression_54;
static void entry__compiler__body__simplify_expression_54(void);
static FRAME_INFO frame__compiler__body__simplify_expression_54 = {2, {"statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_55(void);
static NODE *func__compiler__body__simplify_expression_56;
static void entry__compiler__body__simplify_expression_56(void);
static FRAME_INFO frame__compiler__body__simplify_expression_56 = {2, {"statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_57(void);
static NODE *func__compiler__body__simplify_expression_58;
static void entry__compiler__body__simplify_expression_58(void);
static FRAME_INFO frame__compiler__body__simplify_expression_58 = {1, {"statement"}};
static void cont__compiler__body__simplify_expression_59(void);
static void cont__compiler__body__simplify_expression_60(void);
static void cont__compiler__body__simplify_expression_61(void);
static NODE *func__compiler__body__simplify_expression_62;
static void entry__compiler__body__simplify_expression_62(void);
static FRAME_INFO frame__compiler__body__simplify_expression_62 = {1, {"statement"}};
static void cont__compiler__body__simplify_expression_63(void);
static void cont__compiler__body__simplify_expression_64(void);
static void cont__compiler__body__simplify_expression_65(void);
static void cont__compiler__body__simplify_expression_66(void);
static void cont__compiler__body__simplify_expression_67(void);
static NODE *func__compiler__body__simplify_expression_68;
static void entry__compiler__body__simplify_expression_68(void);
static FRAME_INFO frame__compiler__body__simplify_expression_68 = {3, {"return__2", "statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_69(void);
static void cont__compiler__body__simplify_expression_70(void);
static void cont__compiler__body__simplify_expression_71(void);
static void cont__compiler__body__simplify_expression_72(void);
static NODE *func__compiler__body__simplify_expression_73;
static void entry__compiler__body__simplify_expression_73(void);
static FRAME_INFO frame__compiler__body__simplify_expression_73 = {2, {"statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_74(void);
static NODE *func__compiler__body__simplify_expression_75;
static void entry__compiler__body__simplify_expression_75(void);
static FRAME_INFO frame__compiler__body__simplify_expression_75 = {2, {"statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_76(void);
static NODE *func__compiler__body__simplify_expression_77;
static void entry__compiler__body__simplify_expression_77(void);
static FRAME_INFO frame__compiler__body__simplify_expression_77 = {1, {"statement"}};
static void cont__compiler__body__simplify_expression_78(void);
static void cont__compiler__body__simplify_expression_79(void);
static void cont__compiler__body__simplify_expression_80(void);
static NODE *func__compiler__body__simplify_expression_81;
static void entry__compiler__body__simplify_expression_81(void);
static FRAME_INFO frame__compiler__body__simplify_expression_81 = {1, {"statement"}};
static void cont__compiler__body__simplify_expression_82(void);
static void cont__compiler__body__simplify_expression_83(void);
static void cont__compiler__body__simplify_expression_84(void);
static void cont__compiler__body__simplify_expression_85(void);
static void cont__compiler__body__simplify_expression_86(void);
static NODE *func__compiler__body__simplify_expression_87;
static void entry__compiler__body__simplify_expression_87(void);
static FRAME_INFO frame__compiler__body__simplify_expression_87 = {3, {"return__3", "statement", "max_temp_idx"}};
static void cont__compiler__body__simplify_expression_88(void);
static void cont__compiler__body__simplify_expression_89(void);
static void cont__compiler__body__simplify_expression_90(void);
static void cont__compiler__body__simplify_expression_91(void);
static void cont__compiler__body__simplify_expression_92(void);
static void cont__compiler__body__simplify_expression_93(void);
static NODE *func__compiler__body__simplify_expression_94;
static void entry__compiler__body__simplify_expression_94(void);
static FRAME_INFO frame__compiler__body__simplify_expression_94 = {2, {"self", "temp"}};
static void cont__compiler__body__simplify_expression_95(void);
static void cont__compiler__body__simplify_expression_96(void);
static void cont__compiler__body__simplify_expression_97(void);
static void cont__compiler__body__simplify_expression_98(void);
static void cont__compiler__body__simplify_expression_99(void);
static void cont__compiler__body__simplify_expression_100(void);
static void cont__compiler__body__simplify_expression_101(void);
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
static NODE *func__do_store_44;
static void entry__do_store_44(void);
static FRAME_INFO frame__do_store_44 = {0, {}};
static NODE *func__do_store_45;
static void entry__do_store_45(void);
static FRAME_INFO frame__do_store_45 = {0, {}};
static void cont__do_store_46(void);
static void cont__do_store_47(void);
static void cont__do_store_48(void);
static void cont__do_store_49(void);
static void cont__do_store_50(void);
static void cont__do_store_51(void);
static void cont__do_store_52(void);
static void cont__do_store_53(void);
static void cont__do_store_54(void);
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
static FRAME_INFO frame__compiler__call__simplify_statement_1 = {6, {"self", "return", "output_arguments", "input_arguments", "add_arguments", "final_destinations"}};
static NODE *func__compiler__call__simplify_statement_2;
static void entry__compiler__call__simplify_statement_2(void);
static FRAME_INFO frame__compiler__call__simplify_statement_2 = {3, {"arguments", "output_arguments", "input_arguments"}};
static NODE *func__compiler__call__simplify_statement_3;
static void entry__compiler__call__simplify_statement_3(void);
static FRAME_INFO frame__compiler__call__simplify_statement_3 = {3, {"argument", "output_arguments", "input_arguments"}};
static NODE *func__compiler__call__simplify_statement_4;
static void entry__compiler__call__simplify_statement_4(void);
static FRAME_INFO frame__compiler__call__simplify_statement_4 = {3, {"argument", "output_arguments", "input_arguments"}};
static void cont__compiler__call__simplify_statement_5(void);
static NODE *func__compiler__call__simplify_statement_6;
static void entry__compiler__call__simplify_statement_6(void);
static FRAME_INFO frame__compiler__call__simplify_statement_6 = {3, {"argument", "output_arguments", "input_arguments"}};
static void cont__compiler__call__simplify_statement_7(void);
static void cont__compiler__call__simplify_statement_8(void);
static NODE *func__compiler__call__simplify_statement_9;
static void entry__compiler__call__simplify_statement_9(void);
static FRAME_INFO frame__compiler__call__simplify_statement_9 = {2, {"argument", "output_arguments"}};
static void cont__compiler__call__simplify_statement_10(void);
static NODE *func__compiler__call__simplify_statement_11;
static void entry__compiler__call__simplify_statement_11(void);
static FRAME_INFO frame__compiler__call__simplify_statement_11 = {2, {"output_arguments", "argument"}};
static void cont__compiler__call__simplify_statement_12(void);
static NODE *func__compiler__call__simplify_statement_13;
static void entry__compiler__call__simplify_statement_13(void);
static FRAME_INFO frame__compiler__call__simplify_statement_13 = {2, {"input_arguments", "argument"}};
static void cont__compiler__call__simplify_statement_14(void);
static NODE *string__8629329e514f7a7a;
static void cont__compiler__call__simplify_statement_16(void);
static void cont__compiler__call__simplify_statement_17(void);
static void cont__compiler__call__simplify_statement_18(void);
static void cont__compiler__call__simplify_statement_19(void);
static NODE *func__compiler__call__simplify_statement_20;
static void entry__compiler__call__simplify_statement_20(void);
static FRAME_INFO frame__compiler__call__simplify_statement_20 = {1, {"input_arguments"}};
static void cont__compiler__call__simplify_statement_21(void);
static void cont__compiler__call__simplify_statement_22(void);
static void cont__compiler__call__simplify_statement_23(void);
static NODE *func__compiler__call__simplify_statement_24;
static void entry__compiler__call__simplify_statement_24(void);
static FRAME_INFO frame__compiler__call__simplify_statement_24 = {5, {"input_arguments", "output_arguments", "add_arguments", "self", "source"}};
static void cont__compiler__call__simplify_statement_25(void);
static void cont__compiler__call__simplify_statement_26(void);
static NODE *func__compiler__call__simplify_statement_27;
static void entry__compiler__call__simplify_statement_27(void);
static FRAME_INFO frame__compiler__call__simplify_statement_27 = {6, {"output_arguments", "input_arguments", "add_arguments", "source", "self", "destination"}};
static void cont__compiler__call__simplify_statement_28(void);
static void cont__compiler__call__simplify_statement_29(void);
static void cont__compiler__call__simplify_statement_30(void);
static void cont__compiler__call__simplify_statement_31(void);
static void cont__compiler__call__simplify_statement_32(void);
static void cont__compiler__call__simplify_statement_33(void);
static void cont__compiler__call__simplify_statement_34(void);
static void cont__compiler__call__simplify_statement_35(void);
static void cont__compiler__call__simplify_statement_36(void);
static void cont__compiler__call__simplify_statement_37(void);
static void cont__compiler__call__simplify_statement_38(void);
static NODE *func__compiler__call__simplify_statement_39;
static void entry__compiler__call__simplify_statement_39(void);
static FRAME_INFO frame__compiler__call__simplify_statement_39 = {1, {"output_arguments"}};
static void cont__compiler__call__simplify_statement_40(void);
static NODE *func__compiler__call__simplify_statement_41;
static void entry__compiler__call__simplify_statement_41(void);
static FRAME_INFO frame__compiler__call__simplify_statement_41 = {0, {}};
static void cont__compiler__call__simplify_statement_42(void);
static void cont__compiler__call__simplify_statement_43(void);
static void cont__compiler__call__simplify_statement_44(void);
static NODE *func__compiler__call__simplify_statement_45;
static void entry__compiler__call__simplify_statement_45(void);
static FRAME_INFO frame__compiler__call__simplify_statement_45 = {1, {"self"}};
static void cont__compiler__call__simplify_statement_46(void);
static void cont__compiler__call__simplify_statement_47(void);
static NODE *func__compiler__call__simplify_statement_48;
static void entry__compiler__call__simplify_statement_48(void);
static FRAME_INFO frame__compiler__call__simplify_statement_48 = {1, {"self"}};
static void cont__compiler__call__simplify_statement_49(void);
static void cont__compiler__call__simplify_statement_50(void);
static void cont__compiler__call__simplify_statement_51(void);
static void cont__compiler__call__simplify_statement_52(void);
static void cont__compiler__call__simplify_statement_53(void);
static NODE *func__compiler__call__simplify_statement_54;
static void entry__compiler__call__simplify_statement_54(void);
static FRAME_INFO frame__compiler__call__simplify_statement_54 = {1, {"self"}};
static void cont__compiler__call__simplify_statement_55(void);
static void cont__compiler__call__simplify_statement_56(void);
static void cont__compiler__call__simplify_statement_57(void);
static void cont__compiler__call__simplify_statement_58(void);
static void cont__compiler__call__simplify_statement_59(void);
static void cont__compiler__call__simplify_statement_60(void);
static void cont__compiler__call__simplify_statement_61(void);
static NODE *func__compiler__call__simplify_statement_62;
static void entry__compiler__call__simplify_statement_62(void);
static FRAME_INFO frame__compiler__call__simplify_statement_62 = {5, {"output_arguments", "input_arguments", "return", "self", "destination"}};
static void cont__compiler__call__simplify_statement_63(void);
static void cont__compiler__call__simplify_statement_64(void);
static NODE *func__compiler__call__simplify_statement_65;
static void entry__compiler__call__simplify_statement_65(void);
static FRAME_INFO frame__compiler__call__simplify_statement_65 = {4, {"destination", "input_arguments", "return", "output_arguments"}};
static void cont__compiler__call__simplify_statement_66(void);
static NODE *func__compiler__call__simplify_statement_67;
static void entry__compiler__call__simplify_statement_67(void);
static FRAME_INFO frame__compiler__call__simplify_statement_67 = {5, {"input_arguments", "destination", "return", "output_arguments", "source"}};
static void cont__compiler__call__simplify_statement_68(void);
static void cont__compiler__call__simplify_statement_69(void);
static void cont__compiler__call__simplify_statement_70(void);
static void cont__compiler__call__simplify_statement_71(void);
static NODE *func__compiler__call__simplify_statement_72;
static void entry__compiler__call__simplify_statement_72(void);
static FRAME_INFO frame__compiler__call__simplify_statement_72 = {3, {"destination", "source", "return"}};
static void cont__compiler__call__simplify_statement_73(void);
static void cont__compiler__call__simplify_statement_74(void);
static void cont__compiler__call__simplify_statement_75(void);
static NODE *func__compiler__call__simplify_statement_76;
static void entry__compiler__call__simplify_statement_76(void);
static FRAME_INFO frame__compiler__call__simplify_statement_76 = {3, {"source", "destination", "return"}};
static void cont__compiler__call__simplify_statement_77(void);
static NODE *func__compiler__call__simplify_statement_78;
static void entry__compiler__call__simplify_statement_78(void);
static FRAME_INFO frame__compiler__call__simplify_statement_78 = {1, {"source"}};
static void cont__compiler__call__simplify_statement_79(void);
static void cont__compiler__call__simplify_statement_80(void);
static NODE *func__compiler__call__simplify_statement_81;
static void entry__compiler__call__simplify_statement_81(void);
static FRAME_INFO frame__compiler__call__simplify_statement_81 = {3, {"destination", "source", "return"}};
static void cont__compiler__call__simplify_statement_82(void);
static void cont__compiler__call__simplify_statement_83(void);
static NODE *func__compiler__call__simplify_statement_84;
static void entry__compiler__call__simplify_statement_84(void);
static FRAME_INFO frame__compiler__call__simplify_statement_84 = {3, {"source", "destination", "output_arguments"}};
static void cont__compiler__call__simplify_statement_85(void);
static NODE *func__compiler__call__simplify_statement_86;
static void entry__compiler__call__simplify_statement_86(void);
static FRAME_INFO frame__compiler__call__simplify_statement_86 = {3, {"destination", "source", "output_arguments"}};
static void cont__compiler__call__simplify_statement_87(void);
static void cont__compiler__call__simplify_statement_88(void);
static void cont__compiler__call__simplify_statement_89(void);
static void cont__compiler__call__simplify_statement_90(void);
static NODE *func__compiler__call__simplify_statement_91;
static void entry__compiler__call__simplify_statement_91(void);
static FRAME_INFO frame__compiler__call__simplify_statement_91 = {2, {"destination", "output_arguments"}};
static void cont__compiler__call__simplify_statement_92(void);
static void cont__compiler__call__simplify_statement_93(void);
static void cont__compiler__call__simplify_statement_94(void);
static NODE *func__compiler__call__simplify_statement_95;
static void entry__compiler__call__simplify_statement_95(void);
static FRAME_INFO frame__compiler__call__simplify_statement_95 = {2, {"destination", "output_arguments"}};
static void cont__compiler__call__simplify_statement_96(void);
static void cont__compiler__call__simplify_statement_97(void);
static void cont__compiler__call__simplify_statement_98(void);
static void cont__compiler__call__simplify_statement_99(void);
static void cont__compiler__call__simplify_statement_100(void);
static NODE *func__compiler__call__simplify_statement_101;
static void entry__compiler__call__simplify_statement_101(void);
static FRAME_INFO frame__compiler__call__simplify_statement_101 = {2, {"destination", "input_arguments"}};
static void cont__compiler__call__simplify_statement_102(void);
static NODE *func__compiler__call__simplify_statement_103;
static void entry__compiler__call__simplify_statement_103(void);
static FRAME_INFO frame__compiler__call__simplify_statement_103 = {3, {"self", "output_arguments", "input_arguments"}};
static void cont__compiler__call__simplify_statement_104(void);
static void cont__compiler__call__simplify_statement_105(void);
static void cont__compiler__call__simplify_statement_106(void);
static NODE *func__compiler__call__simplify_statement_107;
static void entry__compiler__call__simplify_statement_107(void);
static FRAME_INFO frame__compiler__call__simplify_statement_107 = {1, {"output_arguments"}};
static NODE *func__compiler__call__simplify_statement_108;
static void entry__compiler__call__simplify_statement_108(void);
static FRAME_INFO frame__compiler__call__simplify_statement_108 = {1, {"argument"}};
static void cont__compiler__call__simplify_statement_109(void);
static NODE *func__compiler__call__simplify_statement_110;
static void entry__compiler__call__simplify_statement_110(void);
static FRAME_INFO frame__compiler__call__simplify_statement_110 = {1, {"argument"}};
static void cont__compiler__call__simplify_statement_111(void);
static void cont__compiler__call__simplify_statement_112(void);
static void cont__compiler__call__simplify_statement_113(void);
static void cont__compiler__call__simplify_statement_114(void);
static void cont__compiler__call__simplify_statement_115(void);
static void cont__compiler__call__simplify_statement_116(void);
static void cont__compiler__call__simplify_statement_117(void);
static NODE *func__compiler__call__simplify_statement_118;
static void entry__compiler__call__simplify_statement_118(void);
static FRAME_INFO frame__compiler__call__simplify_statement_118 = {2, {"final_destinations", "output_arguments"}};
static NODE *func__compiler__call__simplify_statement_119;
static void entry__compiler__call__simplify_statement_119(void);
static FRAME_INFO frame__compiler__call__simplify_statement_119 = {3, {"idx", "destination", "output_arguments"}};
static void cont__compiler__call__simplify_statement_120(void);
static NODE *func__compiler__call__simplify_statement_121;
static void entry__compiler__call__simplify_statement_121(void);
static FRAME_INFO frame__compiler__call__simplify_statement_121 = {4, {"output_arguments", "idx", "destination", "result"}};
static void cont__compiler__call__simplify_statement_122(void);
static void cont__compiler__call__simplify_statement_123(void);
static NODE *func__compiler__call__simplify_statement_124;
static void entry__compiler__call__simplify_statement_124(void);
static FRAME_INFO frame__compiler__call__simplify_statement_124 = {2, {"destination", "result"}};
static NODE *func__compiler__call__simplify_statement_125;
static void entry__compiler__call__simplify_statement_125(void);
static FRAME_INFO frame__compiler__call__simplify_statement_125 = {3, {"destination", "result", "identifier"}};
static void cont__compiler__call__simplify_statement_126(void);
static NODE *func__compiler__call__simplify_statement_127;
static void entry__compiler__call__simplify_statement_127(void);
static FRAME_INFO frame__compiler__call__simplify_statement_127 = {1, {"destination"}};
static NODE *func__compiler__call__simplify_statement_128;
static void entry__compiler__call__simplify_statement_128(void);
static FRAME_INFO frame__compiler__call__simplify_statement_128 = {1, {"destination"}};
static void cont__compiler__call__simplify_statement_129(void);
static void cont__compiler__call__simplify_statement_130(void);
static void cont__compiler__call__simplify_statement_131(void);
static void cont__compiler__call__simplify_statement_132(void);
static void cont__compiler__call__simplify_statement_133(void);
static void cont__compiler__call__simplify_statement_134(void);
static void cont__compiler__call__simplify_statement_135(void);
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
static NODE *func__compiler__attribute_value_pair__simplify_expression_1;
static void entry__compiler__attribute_value_pair__simplify_expression_1(void);
static FRAME_INFO frame__compiler__attribute_value_pair__simplify_expression_1 = {1, {"self"}};
static NODE *string__cced2f4d969d3d03;
static void cont__compiler__attribute_value_pair__simplify_expression_3(void);
static void cont__compiler__attribute_value_pair__simplify_expression_4(void);
static void cont__compiler__attribute_value_pair__simplify_expression_5(void);
static NODE *func__compiler__attribute_function_pair__simplify_expression_1;
static void entry__compiler__attribute_function_pair__simplify_expression_1(void);
static FRAME_INFO frame__compiler__attribute_function_pair__simplify_expression_1 = {1, {"self"}};
static NODE *string__83e573190949a328;
static void cont__compiler__attribute_function_pair__simplify_expression_3(void);
static void cont__compiler__attribute_function_pair__simplify_expression_4(void);
static void cont__compiler__attribute_function_pair__simplify_expression_5(void);
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
  {entry__simplify_input_arguments_5, NULL, 46, 46, 9, 37},
  {cont__simplify_input_arguments_6, &frame__simplify_input_arguments_5, 47, 47, 42, 42},
  {entry__simplify_input_arguments_3, NULL, 44, 44, 10, 37},
  {cont__simplify_input_arguments_4, &frame__simplify_input_arguments_3, 44, 47, 7, 42},
  {entry__simplify_input_arguments_9, NULL, 50, 50, 9, 37},
  {cont__simplify_input_arguments_10, &frame__simplify_input_arguments_9, 51, 51, 42, 42},
  {entry__simplify_input_arguments_7, NULL, 48, 48, 10, 37},
  {cont__simplify_input_arguments_8, &frame__simplify_input_arguments_7, 48, 51, 7, 42},
  {entry__simplify_input_arguments_11, NULL, 53, 53, 9, 37},
  {cont__simplify_input_arguments_12, &frame__simplify_input_arguments_11, 53, 53, 37, 37},
  {entry__simplify_input_arguments_2, NULL, 43, 53, 5, 38},
  {cont__simplify_input_arguments_13, &frame__simplify_input_arguments_2, },
  {entry__simplify_input_arguments_1, NULL, 42, 53, 3, 39},
  {cont__simplify_input_arguments_14, &frame__simplify_input_arguments_1, 53, 53, 40, 40},
  {entry__simplify_output_arguments_10, NULL, 69, 69, 15, 41},
  {cont__simplify_output_arguments_11, &frame__simplify_output_arguments_10, 69, 69, 15, 46},
  {cont__simplify_output_arguments_12, &frame__simplify_output_arguments_10, 69, 69, 15, 46},
  {entry__simplify_output_arguments_14, NULL, 70, 70, 13, 49},
  {cont__simplify_output_arguments_15, &frame__simplify_output_arguments_14, 70, 70, 13, 49},
  {entry__simplify_output_arguments_8, NULL, 68, 68, 15, 52},
  {cont__simplify_output_arguments_9, &frame__simplify_output_arguments_8, 67, 69, 13, 46},
  {cont__simplify_output_arguments_13, &frame__simplify_output_arguments_8, 70, 70, 13, 49},
  {cont__simplify_output_arguments_16, &frame__simplify_output_arguments_8, },
  {entry__simplify_output_arguments_18, NULL, 76, 76, 13, 17},
  {entry__simplify_output_arguments_5, NULL, 66, 66, 17, 43},
  {cont__simplify_output_arguments_6, &frame__simplify_output_arguments_5, 66, 66, 13, 44},
  {cont__simplify_output_arguments_7, &frame__simplify_output_arguments_5, },
  {cont__simplify_output_arguments_17, &frame__simplify_output_arguments_5, 64, 76, 9, 18},
  {entry__simplify_output_arguments_4, NULL, 63, 76, 7, 19},
  {cont__simplify_output_arguments_19, &frame__simplify_output_arguments_4, 76, 76, 19, 19},
  {entry__simplify_output_arguments_25, NULL, 85, 85, 42, 64},
  {cont__simplify_output_arguments_26, &frame__simplify_output_arguments_25, 85, 85, 42, 64},
  {entry__simplify_output_arguments_28, NULL, 86, 86, 13, 46},
  {cont__simplify_output_arguments_29, &frame__simplify_output_arguments_28, 86, 86, 46, 46},
  {entry__simplify_output_arguments_34, NULL, 92, 92, 46, 46},
  {entry__simplify_output_arguments_32, NULL, 90, 90, 18, 45},
  {cont__simplify_output_arguments_33, &frame__simplify_output_arguments_32, 90, 92, 15, 46},
  {entry__simplify_output_arguments_37, NULL, 95, 95, 46, 46},
  {entry__simplify_output_arguments_35, NULL, 93, 93, 18, 45},
  {cont__simplify_output_arguments_36, &frame__simplify_output_arguments_35, 93, 95, 15, 46},
  {entry__simplify_output_arguments_30, NULL, 88, 88, 13, 41},
  {cont__simplify_output_arguments_31, &frame__simplify_output_arguments_30, 89, 95, 13, 47},
  {cont__simplify_output_arguments_38, &frame__simplify_output_arguments_30, 96, 96, 13, 45},
  {cont__simplify_output_arguments_39, &frame__simplify_output_arguments_30, 97, 97, 50, 50},
  {entry__simplify_output_arguments_23, NULL, 85, 85, 11, 37},
  {cont__simplify_output_arguments_24, &frame__simplify_output_arguments_23, 85, 85, 11, 64},
  {cont__simplify_output_arguments_27, &frame__simplify_output_arguments_23, 84, 97, 9, 51},
  {cont__simplify_output_arguments_40, &frame__simplify_output_arguments_23, },
  {entry__simplify_output_arguments_22, NULL, 79, 97, 7, 52},
  {cont__simplify_output_arguments_41, &frame__simplify_output_arguments_22, 97, 97, 53, 53},
  {entry__simplify_output_arguments_3, NULL, 62, 76, 5, 20},
  {cont__simplify_output_arguments_20, &frame__simplify_output_arguments_3, 77, 77, 8, 39},
  {cont__simplify_output_arguments_21, &frame__simplify_output_arguments_3, 77, 97, 5, 53},
  {entry__simplify_output_arguments_1, NULL, 60, 60, 6, 32},
  {cont__simplify_output_arguments_2, &frame__simplify_output_arguments_1, 60, 97, 3, 54},
  {cont__simplify_output_arguments_42, &frame__simplify_output_arguments_1, 98, 98, 3, 23},
  {entry__compiler__check_usage_6, NULL, 104, 104, 21, 39},
  {cont__compiler__check_usage_7, &frame__compiler__check_usage_6, 104, 105, 41, 64},
  {cont__compiler__check_usage_10, &frame__compiler__check_usage_6, 104, 105, 9, 64},
  {entry__compiler__check_usage_3, NULL, 103, 103, 12, 33},
  {cont__compiler__check_usage_4, &frame__compiler__check_usage_3, 103, 103, 35, 77},
  {cont__compiler__check_usage_5, &frame__compiler__check_usage_3, 103, 105, 7, 65},
  {entry__compiler__check_usage_14, NULL, 110, 110, 23, 41},
  {cont__compiler__check_usage_15, &frame__compiler__check_usage_14, 110, 111, 43, 64},
  {cont__compiler__check_usage_17, &frame__compiler__check_usage_14, 110, 111, 11, 64},
  {entry__compiler__check_usage_11, NULL, 108, 108, 9, 30},
  {cont__compiler__check_usage_12, &frame__compiler__check_usage_11, 109, 109, 9, 64},
  {cont__compiler__check_usage_13, &frame__compiler__check_usage_11, 107, 111, 7, 66},
  {entry__compiler__check_usage_21, NULL, 114, 114, 21, 39},
  {cont__compiler__check_usage_22, &frame__compiler__check_usage_21, 114, 115, 41, 70},
  {cont__compiler__check_usage_24, &frame__compiler__check_usage_21, 114, 115, 9, 70},
  {entry__compiler__check_usage_18, NULL, 113, 113, 12, 33},
  {cont__compiler__check_usage_19, &frame__compiler__check_usage_18, 113, 113, 35, 76},
  {cont__compiler__check_usage_20, &frame__compiler__check_usage_18, 113, 115, 7, 71},
  {entry__compiler__check_usage_28, NULL, 120, 120, 23, 41},
  {cont__compiler__check_usage_29, &frame__compiler__check_usage_28, 120, 121, 43, 72},
  {cont__compiler__check_usage_31, &frame__compiler__check_usage_28, 120, 121, 11, 72},
  {entry__compiler__check_usage_25, NULL, 118, 118, 9, 30},
  {cont__compiler__check_usage_26, &frame__compiler__check_usage_25, 119, 119, 9, 61},
  {cont__compiler__check_usage_27, &frame__compiler__check_usage_25, 117, 121, 7, 74},
  {entry__compiler__check_usage_35, NULL, 124, 124, 21, 39},
  {cont__compiler__check_usage_36, &frame__compiler__check_usage_35, 124, 125, 41, 71},
  {cont__compiler__check_usage_38, &frame__compiler__check_usage_35, 124, 125, 9, 71},
  {entry__compiler__check_usage_32, NULL, 123, 123, 12, 33},
  {cont__compiler__check_usage_33, &frame__compiler__check_usage_32, 123, 123, 35, 74},
  {cont__compiler__check_usage_34, &frame__compiler__check_usage_32, 123, 125, 7, 72},
  {entry__compiler__check_usage_1, NULL, 101, 101, 8, 35},
  {cont__compiler__check_usage_2, &frame__compiler__check_usage_1, 101, 125, 3, 74},
  {entry__types__grammar_node__simplify_statement_1, NULL, 131, 131, 3, 57},
  {cont__types__grammar_node__simplify_statement_3, &frame__types__grammar_node__simplify_statement_1, 132, 132, 3, 23},
  {cont__types__grammar_node__simplify_statement_4, &frame__types__grammar_node__simplify_statement_1, 132, 132, 23, 23},
  {entry__types__grammar_node__simplify_expression_1, NULL, 135, 135, 3, 58},
  {cont__types__grammar_node__simplify_expression_3, &frame__types__grammar_node__simplify_expression_1, },
  {entry__compiler__body__simplify_expression_8, NULL, 147, 147, 21, 39},
  {cont__compiler__body__simplify_expression_9, &frame__compiler__body__simplify_expression_8, 147, 149, 41, 33},
  {cont__compiler__body__simplify_expression_12, &frame__compiler__body__simplify_expression_8, 147, 149, 9, 33},
  {entry__compiler__body__simplify_expression_13, NULL, 151, 151, 9, 32},
  {cont__compiler__body__simplify_expression_14, &frame__compiler__body__simplify_expression_13, 151, 151, 37, 37},
  {entry__compiler__body__simplify_expression_5, NULL, 144, 144, 5, 43},
  {cont__compiler__body__simplify_expression_6, &frame__compiler__body__simplify_expression_5, 146, 146, 7, 27},
  {cont__compiler__body__simplify_expression_7, &frame__compiler__body__simplify_expression_5, 145, 151, 5, 38},
  {entry__compiler__body__simplify_expression_24, NULL, 156, 156, 44, 64},
  {cont__compiler__body__simplify_expression_25, &frame__compiler__body__simplify_expression_24, 156, 156, 44, 75},
  {cont__compiler__body__simplify_expression_26, &frame__compiler__body__simplify_expression_24, 156, 156, 44, 75},
  {entry__compiler__body__simplify_expression_28, NULL, 157, 157, 10, 32},
  {cont__compiler__body__simplify_expression_29, &frame__compiler__body__simplify_expression_28, 157, 157, 9, 38},
  {cont__compiler__body__simplify_expression_30, &frame__compiler__body__simplify_expression_28, 157, 157, 43, 43},
  {entry__compiler__body__simplify_expression_20, NULL, 155, 155, 7, 38},
  {cont__compiler__body__simplify_expression_21, &frame__compiler__body__simplify_expression_20, 156, 156, 10, 28},
  {cont__compiler__body__simplify_expression_22, &frame__compiler__body__simplify_expression_20, 156, 156, 10, 39},
  {cont__compiler__body__simplify_expression_23, &frame__compiler__body__simplify_expression_20, 156, 156, 10, 75},
  {cont__compiler__body__simplify_expression_27, &frame__compiler__body__simplify_expression_20, 156, 157, 7, 43},
  {entry__compiler__body__simplify_expression_17, NULL, 153, 153, 5, 39},
  {cont__compiler__body__simplify_expression_18, &frame__compiler__body__simplify_expression_17, 154, 154, 8, 28},
  {cont__compiler__body__simplify_expression_19, &frame__compiler__body__simplify_expression_17, 154, 157, 5, 44},
  {entry__compiler__body__simplify_expression_41, NULL, 172, 172, 13, 48},
  {cont__compiler__body__simplify_expression_42, &frame__compiler__body__simplify_expression_41, 176, 176, 19, 75},
  {cont__compiler__body__simplify_expression_43, &frame__compiler__body__simplify_expression_41, 177, 177, 30, 52},
  {cont__compiler__body__simplify_expression_44, &frame__compiler__body__simplify_expression_41, 178, 178, 37, 66},
  {cont__compiler__body__simplify_expression_45, &frame__compiler__body__simplify_expression_41, 179, 179, 34, 60},
  {cont__compiler__body__simplify_expression_46, &frame__compiler__body__simplify_expression_41, 173, 179, 13, 61},
  {cont__compiler__body__simplify_expression_47, &frame__compiler__body__simplify_expression_41, 180, 180, 13, 44},
  {cont__compiler__body__simplify_expression_48, &frame__compiler__body__simplify_expression_41, 181, 181, 13, 36},
  {entry__compiler__body__simplify_expression_49, NULL, 183, 183, 13, 46},
  {cont__compiler__body__simplify_expression_50, &frame__compiler__body__simplify_expression_49, 184, 184, 53, 53},
  {entry__compiler__body__simplify_expression_39, NULL, 169, 169, 11, 42},
  {cont__compiler__body__simplify_expression_40, &frame__compiler__body__simplify_expression_39, 168, 184, 9, 54},
  {entry__compiler__body__simplify_expression_36, NULL, 166, 166, 7, 49},
  {cont__compiler__body__simplify_expression_37, &frame__compiler__body__simplify_expression_36, 167, 167, 10, 33},
  {cont__compiler__body__simplify_expression_38, &frame__compiler__body__simplify_expression_36, 167, 184, 7, 55},
  {cont__compiler__body__simplify_expression_51, &frame__compiler__body__simplify_expression_36, },
  {entry__compiler__body__simplify_expression_62, NULL, 194, 194, 13, 35},
  {cont__compiler__body__simplify_expression_63, &frame__compiler__body__simplify_expression_62, 194, 194, 13, 38},
  {cont__compiler__body__simplify_expression_64, &frame__compiler__body__simplify_expression_62, 194, 194, 13, 52},
  {cont__compiler__body__simplify_expression_65, &frame__compiler__body__simplify_expression_62, 194, 194, 13, 52},
  {entry__compiler__body__simplify_expression_58, NULL, 193, 193, 13, 35},
  {cont__compiler__body__simplify_expression_59, &frame__compiler__body__simplify_expression_58, 193, 193, 13, 38},
  {cont__compiler__body__simplify_expression_60, &frame__compiler__body__simplify_expression_58, 193, 193, 13, 68},
  {cont__compiler__body__simplify_expression_61, &frame__compiler__body__simplify_expression_58, 194, 194, 13, 52},
  {cont__compiler__body__simplify_expression_66, &frame__compiler__body__simplify_expression_58, },
  {entry__compiler__body__simplify_expression_68, NULL, 197, 197, 13, 40},
  {cont__compiler__body__simplify_expression_69, &frame__compiler__body__simplify_expression_68, 198, 198, 13, 44},
  {cont__compiler__body__simplify_expression_70, &frame__compiler__body__simplify_expression_68, },
  {entry__compiler__body__simplify_expression_56, NULL, 192, 192, 13, 38},
  {cont__compiler__body__simplify_expression_57, &frame__compiler__body__simplify_expression_56, },
  {cont__compiler__body__simplify_expression_67, &frame__compiler__body__simplify_expression_56, 190, 198, 9, 45},
  {entry__compiler__body__simplify_expression_54, NULL, 189, 189, 14, 34},
  {cont__compiler__body__simplify_expression_55, &frame__compiler__body__simplify_expression_54, 189, 198, 7, 46},
  {entry__compiler__body__simplify_expression_81, NULL, 208, 208, 13, 35},
  {cont__compiler__body__simplify_expression_82, &frame__compiler__body__simplify_expression_81, 208, 208, 13, 38},
  {cont__compiler__body__simplify_expression_83, &frame__compiler__body__simplify_expression_81, 208, 208, 13, 52},
  {cont__compiler__body__simplify_expression_84, &frame__compiler__body__simplify_expression_81, 208, 208, 13, 52},
  {entry__compiler__body__simplify_expression_77, NULL, 207, 207, 13, 35},
  {cont__compiler__body__simplify_expression_78, &frame__compiler__body__simplify_expression_77, 207, 207, 13, 38},
  {cont__compiler__body__simplify_expression_79, &frame__compiler__body__simplify_expression_77, 207, 207, 13, 68},
  {cont__compiler__body__simplify_expression_80, &frame__compiler__body__simplify_expression_77, 208, 208, 13, 52},
  {cont__compiler__body__simplify_expression_85, &frame__compiler__body__simplify_expression_77, },
  {entry__compiler__body__simplify_expression_87, NULL, 211, 211, 13, 40},
  {cont__compiler__body__simplify_expression_88, &frame__compiler__body__simplify_expression_87, 212, 212, 13, 44},
  {cont__compiler__body__simplify_expression_89, &frame__compiler__body__simplify_expression_87, },
  {entry__compiler__body__simplify_expression_75, NULL, 206, 206, 13, 38},
  {cont__compiler__body__simplify_expression_76, &frame__compiler__body__simplify_expression_75, },
  {cont__compiler__body__simplify_expression_86, &frame__compiler__body__simplify_expression_75, 204, 212, 9, 45},
  {entry__compiler__body__simplify_expression_73, NULL, 203, 203, 14, 34},
  {cont__compiler__body__simplify_expression_74, &frame__compiler__body__simplify_expression_73, 203, 212, 7, 46},
  {entry__compiler__body__simplify_expression_32, NULL, 159, 159, 5, 41},
  {cont__compiler__body__simplify_expression_33, &frame__compiler__body__simplify_expression_32, 160, 160, 5, 45},
  {cont__compiler__body__simplify_expression_34, &frame__compiler__body__simplify_expression_32, 165, 165, 18, 35},
  {cont__compiler__body__simplify_expression_35, &frame__compiler__body__simplify_expression_32, 165, 184, 5, 56},
  {cont__compiler__body__simplify_expression_52, &frame__compiler__body__simplify_expression_32, 188, 188, 14, 32},
  {cont__compiler__body__simplify_expression_53, &frame__compiler__body__simplify_expression_32, 188, 198, 5, 47},
  {cont__compiler__body__simplify_expression_71, &frame__compiler__body__simplify_expression_32, 202, 202, 14, 32},
  {cont__compiler__body__simplify_expression_72, &frame__compiler__body__simplify_expression_32, 202, 212, 5, 47},
  {cont__compiler__body__simplify_expression_90, &frame__compiler__body__simplify_expression_32, 215, 215, 5, 28},
  {entry__compiler__body__simplify_expression_94, NULL, 221, 221, 5, 32},
  {cont__compiler__body__simplify_expression_95, &frame__compiler__body__simplify_expression_94, 225, 225, 23, 61},
  {cont__compiler__body__simplify_expression_96, &frame__compiler__body__simplify_expression_94, 226, 226, 22, 38},
  {cont__compiler__body__simplify_expression_97, &frame__compiler__body__simplify_expression_94, 227, 227, 29, 52},
  {cont__compiler__body__simplify_expression_98, &frame__compiler__body__simplify_expression_94, 228, 228, 26, 46},
  {cont__compiler__body__simplify_expression_99, &frame__compiler__body__simplify_expression_94, 222, 228, 5, 47},
  {cont__compiler__body__simplify_expression_100, &frame__compiler__body__simplify_expression_94, 229, 229, 14, 14},
  {entry__compiler__body__simplify_expression_1, NULL, 141, 141, 3, 42},
  {cont__compiler__body__simplify_expression_3, &frame__compiler__body__simplify_expression_1, 143, 143, 12, 33},
  {cont__compiler__body__simplify_expression_4, &frame__compiler__body__simplify_expression_1, 143, 151, 3, 39},
  {cont__compiler__body__simplify_expression_15, &frame__compiler__body__simplify_expression_1, 152, 152, 12, 30},
  {cont__compiler__body__simplify_expression_16, &frame__compiler__body__simplify_expression_1, 152, 157, 3, 45},
  {cont__compiler__body__simplify_expression_31, &frame__compiler__body__simplify_expression_1, 158, 215, 3, 41},
  {cont__compiler__body__simplify_expression_91, &frame__compiler__body__simplify_expression_1, 216, 216, 10, 33},
  {cont__compiler__body__simplify_expression_92, &frame__compiler__body__simplify_expression_1, 216, 216, 10, 42},
  {cont__compiler__body__simplify_expression_93, &frame__compiler__body__simplify_expression_1, 216, 229, 3, 14},
  {cont__compiler__body__simplify_expression_101, &frame__compiler__body__simplify_expression_1, },
  {entry__do_store_5, NULL, 238, 238, 43, 71},
  {cont__do_store_6, &frame__do_store_5, 238, 238, 71, 71},
  {entry__do_store_10, NULL, 240, 240, 9, 36},
  {cont__do_store_11, &frame__do_store_10, 245, 245, 27, 69},
  {cont__do_store_12, &frame__do_store_10, 246, 246, 26, 42},
  {cont__do_store_13, &frame__do_store_10, 247, 247, 33, 56},
  {cont__do_store_14, &frame__do_store_10, 248, 248, 30, 50},
  {cont__do_store_15, &frame__do_store_10, 241, 248, 9, 51},
  {cont__do_store_16, &frame__do_store_10, 249, 249, 23, 31},
  {cont__do_store_17, &frame__do_store_10, 249, 249, 40, 48},
  {cont__do_store_18, &frame__do_store_10, 249, 249, 9, 54},
  {cont__do_store_19, &frame__do_store_10, 250, 250, 20, 20},
  {entry__do_store_4, NULL, 238, 238, 7, 71},
  {cont__do_store_7, &frame__do_store_4, 239, 239, 10, 24},
  {cont__do_store_8, &frame__do_store_4, 239, 239, 10, 28},
  {cont__do_store_9, &frame__do_store_4, 239, 250, 7, 20},
  {cont__do_store_20, &frame__do_store_4, 257, 257, 15, 60},
  {cont__do_store_21, &frame__do_store_4, 258, 258, 15, 45},
  {cont__do_store_22, &frame__do_store_4, 259, 259, 24, 40},
  {cont__do_store_23, &frame__do_store_4, 260, 260, 31, 54},
  {cont__do_store_24, &frame__do_store_4, 260, 260, 31, 56},
  {cont__do_store_25, &frame__do_store_4, 261, 261, 28, 48},
  {cont__do_store_26, &frame__do_store_4, 251, 261, 7, 49},
  {cont__do_store_27, &frame__do_store_4, 261, 261, 50, 50},
  {entry__do_store_31, NULL, 264, 264, 9, 36},
  {cont__do_store_32, &frame__do_store_31, 268, 268, 25, 45},
  {cont__do_store_33, &frame__do_store_31, 269, 269, 27, 68},
  {cont__do_store_34, &frame__do_store_31, 270, 270, 26, 42},
  {cont__do_store_35, &frame__do_store_31, 271, 271, 33, 56},
  {cont__do_store_36, &frame__do_store_31, 272, 272, 30, 50},
  {cont__do_store_37, &frame__do_store_31, 265, 272, 9, 51},
  {cont__do_store_38, &frame__do_store_31, 273, 273, 23, 31},
  {cont__do_store_39, &frame__do_store_31, 273, 273, 40, 48},
  {cont__do_store_40, &frame__do_store_31, 273, 273, 9, 54},
  {cont__do_store_41, &frame__do_store_31, 274, 274, 20, 20},
  {entry__do_store_44, NULL, 279, 279, 11, 36},
  {entry__do_store_45, NULL, 280, 280, 11, 33},
  {entry__do_store_28, NULL, 263, 263, 10, 24},
  {cont__do_store_29, &frame__do_store_28, 263, 263, 10, 28},
  {cont__do_store_30, &frame__do_store_28, 263, 274, 7, 20},
  {cont__do_store_42, &frame__do_store_28, 278, 278, 11, 42},
  {cont__do_store_43, &frame__do_store_28, 276, 280, 7, 34},
  {cont__do_store_46, &frame__do_store_28, 289, 289, 32, 52},
  {cont__do_store_47, &frame__do_store_28, 290, 290, 31, 42},
  {cont__do_store_48, &frame__do_store_28, },
  {cont__do_store_49, &frame__do_store_28, 291, 291, 24, 40},
  {cont__do_store_50, &frame__do_store_28, 292, 292, 31, 54},
  {cont__do_store_51, &frame__do_store_28, 292, 292, 31, 56},
  {cont__do_store_52, &frame__do_store_28, 293, 293, 28, 48},
  {cont__do_store_53, &frame__do_store_28, 282, 293, 7, 49},
  {cont__do_store_54, &frame__do_store_28, 293, 293, 50, 50},
  {entry__do_store_1, NULL, 235, 235, 3, 18},
  {cont__do_store_2, &frame__do_store_1, 237, 237, 5, 23},
  {cont__do_store_3, &frame__do_store_1, 236, 293, 3, 51},
  {entry__store_result_8, NULL, 308, 308, 20, 31},
  {cont__store_result_9, &frame__store_result_8, 308, 308, 11, 61},
  {entry__store_result_10, NULL, 310, 310, 24, 35},
  {cont__store_result_11, &frame__store_result_10, 310, 310, 44, 65},
  {cont__store_result_12, &frame__store_result_10, 310, 310, 11, 71},
  {entry__store_result_5, NULL, 307, 307, 9, 20},
  {cont__store_result_6, &frame__store_result_5, 307, 307, 9, 37},
  {cont__store_result_7, &frame__store_result_5, 306, 310, 7, 72},
  {entry__store_result_16, NULL, 315, 315, 11, 54},
  {entry__store_result_17, NULL, 317, 317, 39, 58},
  {cont__store_result_18, &frame__store_result_17, 317, 317, 11, 64},
  {entry__store_result_13, NULL, 312, 312, 7, 38},
  {cont__store_result_14, &frame__store_result_13, 314, 314, 9, 32},
  {cont__store_result_15, &frame__store_result_13, 313, 317, 7, 65},
  {entry__store_result_1, NULL, 302, 302, 3, 25},
  {cont__store_result_2, &frame__store_result_1, 303, 303, 3, 38},
  {cont__store_result_3, &frame__store_result_1, 305, 305, 5, 38},
  {cont__store_result_4, &frame__store_result_1, 304, 317, 3, 67},
  {entry__compiler__call__simplify_statement_6, NULL, 333, 333, 11, 41},
  {cont__compiler__call__simplify_statement_7, &frame__compiler__call__simplify_statement_6, 334, 334, 11, 65},
  {cont__compiler__call__simplify_statement_8, &frame__compiler__call__simplify_statement_6, 334, 334, 65, 65},
  {entry__compiler__call__simplify_statement_4, NULL, 331, 331, 12, 47},
  {cont__compiler__call__simplify_statement_5, &frame__compiler__call__simplify_statement_4, 331, 334, 9, 65},
  {entry__compiler__call__simplify_statement_11, NULL, 335, 335, 39, 69},
  {cont__compiler__call__simplify_statement_12, &frame__compiler__call__simplify_statement_11, 335, 335, 69, 69},
  {entry__compiler__call__simplify_statement_9, NULL, 335, 335, 12, 36},
  {cont__compiler__call__simplify_statement_10, &frame__compiler__call__simplify_statement_9, 335, 335, 9, 69},
  {entry__compiler__call__simplify_statement_13, NULL, 337, 337, 11, 40},
  {cont__compiler__call__simplify_statement_14, &frame__compiler__call__simplify_statement_13, 337, 337, 40, 40},
  {entry__compiler__call__simplify_statement_3, NULL, 330, 337, 7, 41},
  {entry__compiler__call__simplify_statement_2, NULL, 329, 337, 5, 42},
  {entry__compiler__call__simplify_statement_20, NULL, 340, 340, 31, 56},
  {cont__compiler__call__simplify_statement_21, &frame__compiler__call__simplify_statement_20, 340, 340, 31, 61},
  {cont__compiler__call__simplify_statement_22, &frame__compiler__call__simplify_statement_20, 340, 340, 31, 61},
  {entry__compiler__call__simplify_statement_27, NULL, 343, 343, 7, 38},
  {cont__compiler__call__simplify_statement_28, &frame__compiler__call__simplify_statement_27, 346, 346, 21, 40},
  {cont__compiler__call__simplify_statement_29, &frame__compiler__call__simplify_statement_27, 346, 346, 7, 40},
  {cont__compiler__call__simplify_statement_30, &frame__compiler__call__simplify_statement_27, 347, 347, 7, 40},
  {cont__compiler__call__simplify_statement_31, &frame__compiler__call__simplify_statement_27, 350, 350, 23, 40},
  {cont__compiler__call__simplify_statement_32, &frame__compiler__call__simplify_statement_27, 351, 351, 24, 40},
  {cont__compiler__call__simplify_statement_33, &frame__compiler__call__simplify_statement_27, 352, 352, 31, 54},
  {cont__compiler__call__simplify_statement_34, &frame__compiler__call__simplify_statement_27, 353, 353, 28, 48},
  {cont__compiler__call__simplify_statement_35, &frame__compiler__call__simplify_statement_27, 353, 353, 50, 50},
  {entry__compiler__call__simplify_statement_24, NULL, 341, 341, 5, 30},
  {cont__compiler__call__simplify_statement_25, &frame__compiler__call__simplify_statement_24, 342, 342, 8, 32},
  {cont__compiler__call__simplify_statement_26, &frame__compiler__call__simplify_statement_24, 342, 353, 5, 50},
  {entry__compiler__call__simplify_statement_39, NULL, 360, 360, 10, 53},
  {cont__compiler__call__simplify_statement_40, &frame__compiler__call__simplify_statement_39, 360, 360, 7, 53},
  {entry__compiler__call__simplify_statement_41, NULL, 359, 359, 7, 18},
  {entry__compiler__call__simplify_statement_48, NULL, 364, 364, 28, 47},
  {cont__compiler__call__simplify_statement_49, &frame__compiler__call__simplify_statement_48, 364, 364, 7, 47},
  {cont__compiler__call__simplify_statement_50, &frame__compiler__call__simplify_statement_48, 364, 364, 47, 47},
  {entry__compiler__call__simplify_statement_54, NULL, 366, 366, 28, 47},
  {cont__compiler__call__simplify_statement_55, &frame__compiler__call__simplify_statement_54, 366, 366, 7, 47},
  {cont__compiler__call__simplify_statement_56, &frame__compiler__call__simplify_statement_54, 366, 366, 47, 47},
  {entry__compiler__call__simplify_statement_45, NULL, 363, 363, 8, 28},
  {cont__compiler__call__simplify_statement_46, &frame__compiler__call__simplify_statement_45, 363, 363, 8, 39},
  {cont__compiler__call__simplify_statement_47, &frame__compiler__call__simplify_statement_45, 363, 364, 5, 47},
  {cont__compiler__call__simplify_statement_51, &frame__compiler__call__simplify_statement_45, 365, 365, 8, 28},
  {cont__compiler__call__simplify_statement_52, &frame__compiler__call__simplify_statement_45, 365, 365, 8, 39},
  {cont__compiler__call__simplify_statement_53, &frame__compiler__call__simplify_statement_45, 365, 366, 5, 47},
  {cont__compiler__call__simplify_statement_57, &frame__compiler__call__simplify_statement_45, 367, 367, 26, 40},
  {cont__compiler__call__simplify_statement_58, &frame__compiler__call__simplify_statement_45, 367, 367, 5, 40},
  {cont__compiler__call__simplify_statement_59, &frame__compiler__call__simplify_statement_45, 367, 367, 40, 40},
  {entry__compiler__call__simplify_statement_72, NULL, 376, 376, 33, 52},
  {cont__compiler__call__simplify_statement_73, &frame__compiler__call__simplify_statement_72, 376, 376, 15, 52},
  {cont__compiler__call__simplify_statement_74, &frame__compiler__call__simplify_statement_72, 377, 377, 15, 20},
  {entry__compiler__call__simplify_statement_78, NULL, 379, 379, 42, 64},
  {cont__compiler__call__simplify_statement_79, &frame__compiler__call__simplify_statement_78, 379, 379, 42, 64},
  {entry__compiler__call__simplify_statement_81, NULL, 380, 380, 35, 54},
  {cont__compiler__call__simplify_statement_82, &frame__compiler__call__simplify_statement_81, 380, 380, 17, 54},
  {cont__compiler__call__simplify_statement_83, &frame__compiler__call__simplify_statement_81, 381, 381, 17, 22},
  {entry__compiler__call__simplify_statement_76, NULL, 379, 379, 18, 37},
  {cont__compiler__call__simplify_statement_77, &frame__compiler__call__simplify_statement_76, 379, 379, 18, 64},
  {cont__compiler__call__simplify_statement_80, &frame__compiler__call__simplify_statement_76, 379, 381, 15, 22},
  {entry__compiler__call__simplify_statement_86, NULL, 383, 383, 35, 54},
  {cont__compiler__call__simplify_statement_87, &frame__compiler__call__simplify_statement_86, 383, 383, 17, 54},
  {cont__compiler__call__simplify_statement_88, &frame__compiler__call__simplify_statement_86, 384, 384, 18, 36},
  {cont__compiler__call__simplify_statement_89, &frame__compiler__call__simplify_statement_86, 384, 384, 17, 36},
  {cont__compiler__call__simplify_statement_90, &frame__compiler__call__simplify_statement_86, 384, 384, 62, 62},
  {entry__compiler__call__simplify_statement_84, NULL, 382, 382, 18, 41},
  {cont__compiler__call__simplify_statement_85, &frame__compiler__call__simplify_statement_84, 382, 384, 15, 62},
  {entry__compiler__call__simplify_statement_91, NULL, 386, 386, 17, 45},
  {cont__compiler__call__simplify_statement_92, &frame__compiler__call__simplify_statement_91, 387, 387, 18, 36},
  {cont__compiler__call__simplify_statement_93, &frame__compiler__call__simplify_statement_91, 387, 387, 17, 36},
  {cont__compiler__call__simplify_statement_94, &frame__compiler__call__simplify_statement_91, 387, 387, 62, 62},
  {entry__compiler__call__simplify_statement_67, NULL, 374, 374, 13, 38},
  {cont__compiler__call__simplify_statement_68, &frame__compiler__call__simplify_statement_67, 375, 375, 16, 45},
  {cont__compiler__call__simplify_statement_69, &frame__compiler__call__simplify_statement_67, 375, 375, 16, 53},
  {cont__compiler__call__simplify_statement_70, &frame__compiler__call__simplify_statement_67, 375, 375, 16, 53},
  {cont__compiler__call__simplify_statement_71, &frame__compiler__call__simplify_statement_67, 375, 377, 13, 20},
  {cont__compiler__call__simplify_statement_75, &frame__compiler__call__simplify_statement_67, 378, 387, 13, 63},
  {entry__compiler__call__simplify_statement_95, NULL, 389, 389, 13, 41},
  {cont__compiler__call__simplify_statement_96, &frame__compiler__call__simplify_statement_95, 390, 390, 14, 32},
  {cont__compiler__call__simplify_statement_97, &frame__compiler__call__simplify_statement_95, 390, 390, 13, 32},
  {cont__compiler__call__simplify_statement_98, &frame__compiler__call__simplify_statement_95, 390, 390, 58, 58},
  {entry__compiler__call__simplify_statement_65, NULL, 373, 373, 11, 51},
  {cont__compiler__call__simplify_statement_66, &frame__compiler__call__simplify_statement_65, 372, 390, 9, 59},
  {entry__compiler__call__simplify_statement_101, NULL, 393, 393, 36, 53},
  {cont__compiler__call__simplify_statement_102, &frame__compiler__call__simplify_statement_101, 393, 393, 11, 53},
  {entry__compiler__call__simplify_statement_103, NULL, 395, 395, 11, 69},
  {cont__compiler__call__simplify_statement_104, &frame__compiler__call__simplify_statement_103, 396, 396, 11, 31},
  {cont__compiler__call__simplify_statement_105, &frame__compiler__call__simplify_statement_103, 396, 396, 31, 31},
  {entry__compiler__call__simplify_statement_62, NULL, 370, 370, 7, 38},
  {cont__compiler__call__simplify_statement_63, &frame__compiler__call__simplify_statement_62, 371, 371, 10, 36},
  {cont__compiler__call__simplify_statement_64, &frame__compiler__call__simplify_statement_62, 371, 390, 7, 60},
  {cont__compiler__call__simplify_statement_99, &frame__compiler__call__simplify_statement_62, 392, 392, 9, 38},
  {cont__compiler__call__simplify_statement_100, &frame__compiler__call__simplify_statement_62, 391, 396, 7, 32},
  {cont__compiler__call__simplify_statement_106, &frame__compiler__call__simplify_statement_62, 397, 397, 7, 12},
  {entry__compiler__call__simplify_statement_110, NULL, 401, 401, 11, 36},
  {cont__compiler__call__simplify_statement_111, &frame__compiler__call__simplify_statement_110, 402, 402, 45, 45},
  {entry__compiler__call__simplify_statement_108, NULL, 400, 400, 12, 35},
  {cont__compiler__call__simplify_statement_109, &frame__compiler__call__simplify_statement_108, 400, 402, 9, 45},
  {cont__compiler__call__simplify_statement_112, &frame__compiler__call__simplify_statement_108, },
  {entry__compiler__call__simplify_statement_107, NULL, 399, 402, 7, 46},
  {cont__compiler__call__simplify_statement_113, &frame__compiler__call__simplify_statement_107, 402, 402, 47, 47},
  {entry__compiler__call__simplify_statement_124, NULL, 416, 416, 13, 43},
  {entry__compiler__call__simplify_statement_127, NULL, 425, 425, 17, 30},
  {entry__compiler__call__simplify_statement_128, NULL, 426, 426, 20, 45},
  {cont__compiler__call__simplify_statement_129, &frame__compiler__call__simplify_statement_128, 426, 426, 17, 45},
  {entry__compiler__call__simplify_statement_125, NULL, 424, 424, 17, 44},
  {cont__compiler__call__simplify_statement_126, &frame__compiler__call__simplify_statement_125, 422, 426, 13, 46},
  {cont__compiler__call__simplify_statement_130, &frame__compiler__call__simplify_statement_125, 430, 430, 31, 54},
  {cont__compiler__call__simplify_statement_131, &frame__compiler__call__simplify_statement_125, 431, 431, 30, 52},
  {cont__compiler__call__simplify_statement_132, &frame__compiler__call__simplify_statement_125, 432, 432, 37, 66},
  {cont__compiler__call__simplify_statement_133, &frame__compiler__call__simplify_statement_125, 433, 433, 34, 60},
  {cont__compiler__call__simplify_statement_134, &frame__compiler__call__simplify_statement_125, 428, 433, 13, 61},
  {entry__compiler__call__simplify_statement_121, NULL, 409, 409, 11, 31},
  {cont__compiler__call__simplify_statement_122, &frame__compiler__call__simplify_statement_121, 415, 415, 11, 40},
  {cont__compiler__call__simplify_statement_123, &frame__compiler__call__simplify_statement_121, 414, 433, 9, 63},
  {entry__compiler__call__simplify_statement_119, NULL, 407, 407, 10, 31},
  {cont__compiler__call__simplify_statement_120, &frame__compiler__call__simplify_statement_119, 407, 433, 7, 64},
  {entry__compiler__call__simplify_statement_118, NULL, 406, 433, 5, 65},
  {entry__compiler__call__simplify_statement_1, NULL, 324, 324, 3, 47},
  {cont__compiler__call__simplify_statement_16, &frame__compiler__call__simplify_statement_1, 339, 339, 17, 34},
  {cont__compiler__call__simplify_statement_17, &frame__compiler__call__simplify_statement_1, 339, 339, 3, 34},
  {cont__compiler__call__simplify_statement_18, &frame__compiler__call__simplify_statement_1, 340, 340, 6, 26},
  {cont__compiler__call__simplify_statement_19, &frame__compiler__call__simplify_statement_1, 340, 340, 6, 61},
  {cont__compiler__call__simplify_statement_23, &frame__compiler__call__simplify_statement_1, 340, 353, 3, 51},
  {cont__compiler__call__simplify_statement_36, &frame__compiler__call__simplify_statement_1, 354, 354, 3, 43},
  {cont__compiler__call__simplify_statement_37, &frame__compiler__call__simplify_statement_1, 358, 358, 7, 27},
  {cont__compiler__call__simplify_statement_38, &frame__compiler__call__simplify_statement_1, 356, 360, 3, 54},
  {cont__compiler__call__simplify_statement_42, &frame__compiler__call__simplify_statement_1, 362, 362, 6, 21},
  {cont__compiler__call__simplify_statement_43, &frame__compiler__call__simplify_statement_1, 362, 362, 6, 32},
  {cont__compiler__call__simplify_statement_44, &frame__compiler__call__simplify_statement_1, 362, 367, 3, 40},
  {cont__compiler__call__simplify_statement_60, &frame__compiler__call__simplify_statement_1, 369, 369, 5, 25},
  {cont__compiler__call__simplify_statement_61, &frame__compiler__call__simplify_statement_1, 368, 402, 3, 48},
  {cont__compiler__call__simplify_statement_114, &frame__compiler__call__simplify_statement_1, 403, 403, 3, 61},
  {cont__compiler__call__simplify_statement_115, &frame__compiler__call__simplify_statement_1, 404, 404, 3, 23},
  {cont__compiler__call__simplify_statement_116, &frame__compiler__call__simplify_statement_1, 405, 405, 6, 34},
  {cont__compiler__call__simplify_statement_117, &frame__compiler__call__simplify_statement_1, 405, 433, 3, 66},
  {cont__compiler__call__simplify_statement_135, &frame__compiler__call__simplify_statement_1, 433, 433, 66, 66},
  {entry__compiler__function_call__simplify_expression_1, NULL, 439, 439, 3, 51},
  {cont__compiler__function_call__simplify_expression_3, &frame__compiler__function_call__simplify_expression_1, 440, 440, 3, 30},
  {cont__compiler__function_call__simplify_expression_4, &frame__compiler__function_call__simplify_expression_1, 443, 443, 19, 34},
  {cont__compiler__function_call__simplify_expression_5, &frame__compiler__function_call__simplify_expression_1, 444, 444, 26, 43},
  {cont__compiler__function_call__simplify_expression_6, &frame__compiler__function_call__simplify_expression_1, 444, 444, 21, 73},
  {cont__compiler__function_call__simplify_expression_7, &frame__compiler__function_call__simplify_expression_1, 445, 445, 20, 36},
  {cont__compiler__function_call__simplify_expression_8, &frame__compiler__function_call__simplify_expression_1, 446, 446, 27, 50},
  {cont__compiler__function_call__simplify_expression_9, &frame__compiler__function_call__simplify_expression_1, 447, 447, 24, 44},
  {cont__compiler__function_call__simplify_expression_10, &frame__compiler__function_call__simplify_expression_1, 441, 447, 3, 45},
  {cont__compiler__function_call__simplify_expression_11, &frame__compiler__function_call__simplify_expression_1, 448, 448, 3, 9},
  {entry__compiler__attribute_value_pair__simplify_expression_1, NULL, 454, 454, 3, 58},
  {cont__compiler__attribute_value_pair__simplify_expression_3, &frame__compiler__attribute_value_pair__simplify_expression_1, 455, 455, 29, 45},
  {cont__compiler__attribute_value_pair__simplify_expression_4, &frame__compiler__attribute_value_pair__simplify_expression_1, 455, 456, 3, 47},
  {cont__compiler__attribute_value_pair__simplify_expression_5, &frame__compiler__attribute_value_pair__simplify_expression_1, 456, 456, 48, 48},
  {entry__compiler__attribute_function_pair__simplify_expression_1, NULL, 462, 462, 3, 61},
  {cont__compiler__attribute_function_pair__simplify_expression_3, &frame__compiler__attribute_function_pair__simplify_expression_1, 463, 463, 29, 45},
  {cont__compiler__attribute_function_pair__simplify_expression_4, &frame__compiler__attribute_function_pair__simplify_expression_1, 463, 464, 3, 47},
  {cont__compiler__attribute_function_pair__simplify_expression_5, &frame__compiler__attribute_function_pair__simplify_expression_1, 464, 464, 48, 48},
  {entry__compiler__c_code__simplify_statement_4, NULL, 471, 471, 35, 35},
  {entry__compiler__c_code__simplify_statement_10, NULL, 476, 476, 22, 43},
  {cont__compiler__c_code__simplify_statement_11, &frame__compiler__c_code__simplify_statement_10, 476, 476, 48, 48},
  {entry__compiler__c_code__simplify_statement_7, NULL, 475, 475, 21, 39},
  {cont__compiler__c_code__simplify_statement_8, &frame__compiler__c_code__simplify_statement_7, 475, 475, 7, 40},
  {cont__compiler__c_code__simplify_statement_9, &frame__compiler__c_code__simplify_statement_7, 476, 476, 7, 48},
  {cont__compiler__c_code__simplify_statement_12, &frame__compiler__c_code__simplify_statement_7, 476, 476, 48, 48},
  {entry__compiler__c_code__simplify_statement_16, NULL, 480, 480, 22, 41},
  {cont__compiler__c_code__simplify_statement_17, &frame__compiler__c_code__simplify_statement_16, 480, 480, 46, 46},
  {entry__compiler__c_code__simplify_statement_13, NULL, 479, 479, 21, 39},
  {cont__compiler__c_code__simplify_statement_14, &frame__compiler__c_code__simplify_statement_13, 479, 479, 7, 40},
  {cont__compiler__c_code__simplify_statement_15, &frame__compiler__c_code__simplify_statement_13, 480, 480, 7, 46},
  {cont__compiler__c_code__simplify_statement_18, &frame__compiler__c_code__simplify_statement_13, 480, 480, 46, 46},
  {entry__compiler__c_code__simplify_statement_25, NULL, 484, 484, 22, 45},
  {cont__compiler__c_code__simplify_statement_26, &frame__compiler__c_code__simplify_statement_25, 484, 484, 50, 50},
  {entry__compiler__c_code__simplify_statement_19, NULL, 483, 483, 20, 34},
  {cont__compiler__c_code__simplify_statement_20, &frame__compiler__c_code__simplify_statement_19, 483, 483, 20, 47},
  {cont__compiler__c_code__simplify_statement_21, &frame__compiler__c_code__simplify_statement_19, 483, 483, 49, 60},
  {cont__compiler__c_code__simplify_statement_22, &frame__compiler__c_code__simplify_statement_19, 483, 483, 63, 63},
  {cont__compiler__c_code__simplify_statement_23, &frame__compiler__c_code__simplify_statement_19, 483, 483, 7, 64},
  {cont__compiler__c_code__simplify_statement_24, &frame__compiler__c_code__simplify_statement_19, 484, 484, 7, 50},
  {cont__compiler__c_code__simplify_statement_27, &frame__compiler__c_code__simplify_statement_19, 484, 484, 50, 50},
  {entry__compiler__c_code__simplify_statement_1, NULL, 470, 470, 3, 44},
  {cont__compiler__c_code__simplify_statement_3, &frame__compiler__c_code__simplify_statement_1, 471, 471, 3, 35},
  {cont__compiler__c_code__simplify_statement_5, &frame__compiler__c_code__simplify_statement_1, 472, 472, 8, 20},
  {cont__compiler__c_code__simplify_statement_6, &frame__compiler__c_code__simplify_statement_1, 472, 484, 3, 51},
  {cont__compiler__c_code__simplify_statement_31, &frame__compiler__c_code__simplify_statement_1, 485, 485, 3, 24},
  {cont__compiler__c_code__simplify_statement_32, &frame__compiler__c_code__simplify_statement_1, 485, 485, 24, 24},
  {entry__compiler__c_body__simplify_expression_4, NULL, 492, 492, 35, 35},
  {entry__compiler__c_body__simplify_expression_1, NULL, 491, 491, 3, 44},
  {cont__compiler__c_body__simplify_expression_3, &frame__compiler__c_body__simplify_expression_1, 492, 492, 3, 35},
  {cont__compiler__c_body__simplify_expression_5, &frame__compiler__c_body__simplify_expression_1, 492, 492, 35, 35}
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
static NODE *number__2;
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
static void entry__simplify_input_arguments_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // input_arguments: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* input_arguments */ = create_cell_with_contents(arguments->slots[0]);
  // 42: update_each &input_arguments: (&argument)
  // 43:   cond
  // 44:     -> argument.is_an_optional_item:
  // 45:       !argument.is_an_optional_item false
  // 46:       simplify_expression &argument
  // 47:       !argument.is_an_optional_item true
  // 48:     -> argument.is_an_expanded_item:
  // 49:       !argument.is_an_expanded_item false
  // 50:       simplify_expression &argument
  // 51:       !argument.is_an_expanded_item true
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* input_arguments */;
  arguments->slots[1] = func__simplify_input_arguments_2;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__simplify_input_arguments_14;
}
static void entry__simplify_input_arguments_2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 44: -> argument.is_an_optional_item:
  // 45:   !argument.is_an_optional_item false
  // 46:   simplify_expression &argument
  // 47:   !argument.is_an_optional_item true
  frame->slots[1] /* temp__1 */ = create_closure(entry__simplify_input_arguments_3, 0);
  // 48: -> argument.is_an_expanded_item:
  // 49:   !argument.is_an_expanded_item false
  // 50:   simplify_expression &argument
  // 51:   !argument.is_an_expanded_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__simplify_input_arguments_7, 0);
  // 52: :
  // 53:   simplify_expression &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__simplify_input_arguments_11, 0);
  // 43: cond
  // 44:   -> argument.is_an_optional_item:
  // 45:     !argument.is_an_optional_item false
  // 46:     simplify_expression &argument
  // 47:     !argument.is_an_optional_item true
  // 48:   -> argument.is_an_expanded_item:
  // 49:     !argument.is_an_expanded_item false
  // 50:     simplify_expression &argument
  // 51:     !argument.is_an_expanded_item true
  // 52:   :
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
  frame->cont = cont__simplify_input_arguments_13;
}
static void entry__simplify_input_arguments_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 49: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, get__false());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 50: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__simplify_input_arguments_10;
}
static void cont__simplify_input_arguments_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  // 51: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, get__true());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_input_arguments_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__false());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 46: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__simplify_input_arguments_6;
}
static void cont__simplify_input_arguments_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  // 47: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__true());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_input_arguments_3(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 44: ... argument.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__simplify_input_arguments_4;
}
static void cont__simplify_input_arguments_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 44: ... :
  // 45:   !argument.is_an_optional_item false
  // 46:   simplify_expression &argument
  // 47:   !argument.is_an_optional_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__simplify_input_arguments_5, 0);
  // 44: -> argument.is_an_optional_item:
  // 45:   !argument.is_an_optional_item false
  // 46:   simplify_expression &argument
  // 47:   !argument.is_an_optional_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_input_arguments_7(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 48: ... argument.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__simplify_input_arguments_8;
}
static void cont__simplify_input_arguments_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 48: ... :
  // 49:   !argument.is_an_expanded_item false
  // 50:   simplify_expression &argument
  // 51:   !argument.is_an_expanded_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__simplify_input_arguments_9, 0);
  // 48: -> argument.is_an_expanded_item:
  // 49:   !argument.is_an_expanded_item false
  // 50:   simplify_expression &argument
  // 51:   !argument.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_input_arguments_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 53: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__simplify_input_arguments_12;
}
static void cont__simplify_input_arguments_12(void) {
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
static void cont__simplify_input_arguments_13(void) {
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
static void cont__simplify_input_arguments_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* input_arguments */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* input_arguments */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_output_arguments_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // output_arguments: 0
  // final_destinations: 1
  frame->slots[1] /* final_destinations */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* output_arguments */ = create_cell_with_contents(arguments->slots[0]);
  // 59: $$final_destinations undefined
  ((CELL *)frame->slots[1])->contents /* final_destinations */ = get__undefined();
  // 60: ... output_arguments.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_2;
}
static void cont__simplify_output_arguments_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 60: ... :
  // 61:   $$first_temporary_index undefined
  // 62:   do: (-> break)
  // 63:     for_each output_arguments: (idx argument)
  // 64:       unless
  // 65:         ||
  // 66:           not(argument.is_a_function_call)
  // 67:           &&
  // 68:             argument.is_a_single_assign_definition
  // 69:             length_of(output_arguments) == 1
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__simplify_output_arguments_3, 0);
  // 60: if output_arguments.is_defined:
  // 61:   $$first_temporary_index undefined
  // 62:   do: (-> break)
  // 63:     for_each output_arguments: (idx argument)
  // 64:       unless
  // 65:         ||
  // 66:           not(argument.is_a_function_call)
  // 67:           &&
  // 68:             argument.is_a_single_assign_definition
  // 69:             length_of(output_arguments) == 1
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_42;
}
static void entry__simplify_output_arguments_22(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // final_destinations: 0
  // output_arguments: 1
  // first_temporary_index: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* final_destinations */
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first_temporary_index */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 78: !final_destinations empty_list
  ((CELL *)frame->slots[0])->contents /* final_destinations */ = get__empty_list();
  // 79: ... :
  // 80:   (
  // 81:     idx
  // 82:     &argument
  // 83:   )
  // 84:   if
  // 85:     idx < first_temporary_index || argument.is_a_temporary:
  // 86:       push &final_destinations undefined
  // 87:     :
  // 88:       $$temp temporary_identifier()
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__simplify_output_arguments_23, 2);
  // 79: update_each &output_arguments:
  // 80:   (
  // 81:     idx
  // 82:     &argument
  // 83:   )
  // 84:   if
  // 85:     idx < first_temporary_index || argument.is_a_temporary:
  // 86:       push &final_destinations undefined
  // 87:     :
  // 88:       $$temp temporary_identifier()
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_41;
}
static void entry__simplify_output_arguments_23(void) {
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
  // 85: idx < first_temporary_index
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* first_temporary_index */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_24;
}
static void cont__simplify_output_arguments_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 85: ... argument.is_a_temporary
  frame->slots[6] /* temp__3 */ = create_closure(entry__simplify_output_arguments_25, 0);
  // 85: idx < first_temporary_index || argument.is_a_temporary
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_27;
}
static void entry__simplify_output_arguments_25(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 85: ... argument.is_a_temporary
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_a_temporary();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_26;
}
static void cont__simplify_output_arguments_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 85: ... argument.is_a_temporary
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_output_arguments_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 85: ... :
  // 86:   push &final_destinations undefined
  frame->slots[7] /* temp__4 */ = create_closure(entry__simplify_output_arguments_28, 0);
  // 87: :
  // 88:   $$temp temporary_identifier()
  // 89:   cond
  // 90:     -> argument.is_an_optional_item:
  // 91:       !argument.is_an_optional_item false
  // 92:       !temp.is_an_optional_item true
  // 93:     -> argument.is_an_expanded_item:
  // 94:       !argument.is_an_expanded_item false
  // 95:       !temp.is_an_expanded_item true
  // 96:   push &final_destinations argument
  // ...
  frame->slots[8] /* temp__5 */ = create_closure(entry__simplify_output_arguments_30, 0);
  // 84: if
  // 85:   idx < first_temporary_index || argument.is_a_temporary:
  // 86:     push &final_destinations undefined
  // 87:   :
  // 88:     $$temp temporary_identifier()
  // 89:     cond
  // 90:       -> argument.is_an_optional_item:
  // 91:         !argument.is_an_optional_item false
  // 92:         !temp.is_an_optional_item true
  // 93:       -> argument.is_an_expanded_item:
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
  frame->cont = cont__simplify_output_arguments_40;
}
static void entry__simplify_output_arguments_28(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // final_destinations: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* final_destinations */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 86: push &final_destinations undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* final_destinations */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_29;
}
static void cont__simplify_output_arguments_29(void) {
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
static void entry__simplify_output_arguments_30(void) {
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
  // 88: $$temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_31;
}
static void cont__simplify_output_arguments_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* temp */ = arguments->slots[0];
  // 90: -> argument.is_an_optional_item:
  // 91:   !argument.is_an_optional_item false
  // 92:   !temp.is_an_optional_item true
  frame->slots[3] /* temp__1 */ = create_closure(entry__simplify_output_arguments_32, 0);
  // 93: -> argument.is_an_expanded_item:
  // 94:   !argument.is_an_expanded_item false
  // 95:   !temp.is_an_expanded_item true
  frame->slots[4] /* temp__2 */ = create_closure(entry__simplify_output_arguments_35, 0);
  // 89: cond
  // 90:   -> argument.is_an_optional_item:
  // 91:     !argument.is_an_optional_item false
  // 92:     !temp.is_an_optional_item true
  // 93:   -> argument.is_an_expanded_item:
  // 94:     !argument.is_an_expanded_item false
  // 95:     !temp.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_38;
}
static void entry__simplify_output_arguments_37(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 94: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, get__false());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 95: !temp.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, get__true());
    ((CELL *)frame->slots[1])->contents /* temp */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_output_arguments_34(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 91: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__false());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 92: !temp.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__true());
    ((CELL *)frame->slots[1])->contents /* temp */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_output_arguments_32(void) {
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
  // 90: ... argument.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_33;
}
static void cont__simplify_output_arguments_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 90: ... :
  // 91:   !argument.is_an_optional_item false
  // 92:   !temp.is_an_optional_item true
  frame->slots[3] /* temp__2 */ = create_closure(entry__simplify_output_arguments_34, 0);
  // 90: -> argument.is_an_optional_item:
  // 91:   !argument.is_an_optional_item false
  // 92:   !temp.is_an_optional_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__simplify_output_arguments_35(void) {
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
  // 93: ... argument.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_36;
}
static void cont__simplify_output_arguments_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 93: ... :
  // 94:   !argument.is_an_expanded_item false
  // 95:   !temp.is_an_expanded_item true
  frame->slots[3] /* temp__2 */ = create_closure(entry__simplify_output_arguments_37, 0);
  // 93: -> argument.is_an_expanded_item:
  // 94:   !argument.is_an_expanded_item false
  // 95:   !temp.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_output_arguments_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 96: push &final_destinations argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* final_destinations */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_39;
}
static void cont__simplify_output_arguments_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* final_destinations */ = arguments->slots[0];
  // 97: !argument temp(.is_a_destination true)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__true());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_output_arguments_40(void) {
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
static void cont__simplify_output_arguments_41(void) {
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
static void entry__simplify_output_arguments_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // output_arguments: 0
  // final_destinations: 1
  // first_temporary_index: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* output_arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* final_destinations */
  frame->slots[2] /* first_temporary_index */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: $$first_temporary_index undefined
  ((CELL *)frame->slots[2])->contents /* first_temporary_index */ = get__undefined();
  // 62: ... : (-> break)
  // 63:   for_each output_arguments: (idx argument)
  // 64:     unless
  // 65:       ||
  // 66:         not(argument.is_a_function_call)
  // 67:         &&
  // 68:           argument.is_a_single_assign_definition
  // 69:           length_of(output_arguments) == 1
  // 70:         argument.is_a_multi_assign_definition
  // 71:         #&&
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__simplify_output_arguments_4, 0);
  // 62: do: (-> break)
  // 63:   for_each output_arguments: (idx argument)
  // 64:     unless
  // 65:       ||
  // 66:         not(argument.is_a_function_call)
  // 67:         &&
  // 68:           argument.is_a_single_assign_definition
  // 69:           length_of(output_arguments) == 1
  // 70:         argument.is_a_multi_assign_definition
  // 71:         #&&
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_20;
}
static void entry__simplify_output_arguments_4(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // output_arguments: 1
  // first_temporary_index: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first_temporary_index */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: ... : (idx argument)
  // 64:   unless
  // 65:     ||
  // 66:       not(argument.is_a_function_call)
  // 67:       &&
  // 68:         argument.is_a_single_assign_definition
  // 69:         length_of(output_arguments) == 1
  // 70:       argument.is_a_multi_assign_definition
  // 71:       #&&
  // 72:         argument.is_a_function_call
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__simplify_output_arguments_5, 2);
  // 63: for_each output_arguments: (idx argument)
  // 64:   unless
  // 65:     ||
  // 66:       not(argument.is_a_function_call)
  // 67:       &&
  // 68:         argument.is_a_single_assign_definition
  // 69:         length_of(output_arguments) == 1
  // 70:       argument.is_a_multi_assign_definition
  // 71:       #&&
  // 72:         argument.is_a_function_call
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_19;
}
static void entry__simplify_output_arguments_18(void) {
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
  // 75: !first_temporary_index idx
  ((CELL *)frame->slots[0])->contents /* first_temporary_index */ = frame->slots[1] /* idx */;
  // 76: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__simplify_output_arguments_5(void) {
  allocate_initialized_frame_gc(5, 10);
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
  // 66: ... argument.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_6;
}
static void cont__simplify_output_arguments_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 66: not(argument.is_a_function_call)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_7;
}
static void cont__simplify_output_arguments_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  frame->slots[8] /* temp__4 */ = create_closure(entry__simplify_output_arguments_8, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_17;
}
static void entry__simplify_output_arguments_8(void) {
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
  // 68: argument.is_a_single_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_single_assign_definition();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_9;
}
static void cont__simplify_output_arguments_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 69: length_of(output_arguments) == 1
  frame->slots[5] /* temp__4 */ = create_closure(entry__simplify_output_arguments_10, 0);
  // 67: &&
  // 68:   argument.is_a_single_assign_definition
  // 69:   length_of(output_arguments) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_13;
}
static void entry__simplify_output_arguments_10(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // output_arguments: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: length_of(output_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_11;
}
static void cont__simplify_output_arguments_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 69: length_of(output_arguments) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_12;
}
static void cont__simplify_output_arguments_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 69: length_of(output_arguments) == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_output_arguments_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 70: argument.is_a_multi_assign_definition
  frame->slots[6] /* temp__5 */ = create_closure(entry__simplify_output_arguments_14, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_16;
}
static void entry__simplify_output_arguments_14(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: argument.is_a_multi_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_multi_assign_definition();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_15;
}
static void cont__simplify_output_arguments_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 70: argument.is_a_multi_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__simplify_output_arguments_16(void) {
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
static void cont__simplify_output_arguments_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 74: :
  // 75:   !first_temporary_index idx
  // 76:   break
  frame->slots[9] /* temp__5 */ = create_closure(entry__simplify_output_arguments_18, 0);
  // 64: unless
  // 65:   ||
  // 66:     not(argument.is_a_function_call)
  // 67:     &&
  // 68:       argument.is_a_single_assign_definition
  // 69:       length_of(output_arguments) == 1
  // 70:     argument.is_a_multi_assign_definition
  // 71:     #&&
  // 72:       argument.is_a_function_call
  // 73:       functor_of(argument).is_used_as_a_polymorphic_function
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__simplify_output_arguments_19(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__simplify_output_arguments_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 77: ... first_temporary_index.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* first_temporary_index */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__simplify_output_arguments_21;
}
static void cont__simplify_output_arguments_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 77: ... :
  // 78:   !final_destinations empty_list
  // 79:   update_each &output_arguments:
  // 80:     (
  // 81:       idx
  // 82:       &argument
  // 83:     )
  // 84:     if
  // 85:       idx < first_temporary_index || argument.is_a_temporary:
  // 86:         push &final_destinations undefined
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__simplify_output_arguments_22, 0);
  // 77: if first_temporary_index.is_defined:
  // 78:   !final_destinations empty_list
  // 79:   update_each &output_arguments:
  // 80:     (
  // 81:       idx
  // 82:       &argument
  // 83:     )
  // 84:     if
  // 85:       idx < first_temporary_index || argument.is_a_temporary:
  // 86:         push &final_destinations undefined
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
static void cont__simplify_output_arguments_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 98: -> final_destinations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* final_destinations */;
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
  // 124: ... identifier_of(info)
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
  // 124: ... "
  // 125:   Invalid access to dynamic read-write variable "@(name)@quot;@
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
  // 124: SyntaxError identifier_of(info) "
  // 125:   Invalid access to dynamic read-write variable "@(name)@quot;@
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
  // 120: ... identifier_of(info)
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
  // 120: ... "
  // 121:   Invalid access to dynamic read-only variable "@(name)@quot;@
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
  // 120: SyntaxError identifier_of(info) "
  // 121:   Invalid access to dynamic read-only variable "@(name)@quot;@
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
  // 114: ... identifier_of(info)
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
  // 114: ... "
  // 115:   Invalid access to static read-write variable "@(name)@quot;@
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
  // 114: SyntaxError identifier_of(info) "
  // 115:   Invalid access to static read-write variable "@(name)@quot;@
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
  // 110: ... identifier_of(info)
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
  // 110: ... "
  // 111:   Invalid access to read-only variable "@(name)@quot;@
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
  // 110: SyntaxError identifier_of(info) "
  // 111:   Invalid access to read-only variable "@(name)@quot;@
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
  // 104: ... identifier_of(info)
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
  // 104: ... "
  // 105:   Invalid access to polymorphic function "@(name)@quot;@
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
  // 104: SyntaxError identifier_of(info) "
  // 105:   Invalid access to polymorphic function "@(name)@quot;@
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
  // 103: ... variable_kind_of(info)
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
  // 103: ... STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI
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
  // 103: ... :
  // 104:   SyntaxError identifier_of(info) "
  // 105:     Invalid access to polymorphic function "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_6, 0);
  // 103: case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 104:   SyntaxError identifier_of(info) "
  // 105:     Invalid access to polymorphic function "@(name)@quot;@
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
  // 108: variable_kind_of(info)
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
  // 109: STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC
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
  // 109: ... :
  // 110:   SyntaxError identifier_of(info) "
  // 111:     Invalid access to read-only variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_14, 0);
  // 107: case
  // 108:   variable_kind_of(info)
  // 109:   STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 110:     SyntaxError identifier_of(info) "
  // 111:       Invalid access to read-only variable "@(name)@quot;@
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
  // 113: ... variable_kind_of(info)
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
  // 113: ... DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC
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
  // 113: ... :
  // 114:   SyntaxError identifier_of(info) "
  // 115:     Invalid access to static read-write variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_21, 0);
  // 113: case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 114:   SyntaxError identifier_of(info) "
  // 115:     Invalid access to static read-write variable "@(name)@quot;@
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
  // 118: variable_kind_of(info)
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
  // 119: POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI, POLYMORPHIC
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
  // 119: ... :
  // 120:   SyntaxError identifier_of(info) "
  // 121:     Invalid access to dynamic read-only variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_28, 0);
  // 117: case
  // 118:   variable_kind_of(info)
  // 119:   POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI, POLYMORPHIC:
  // 120:     SyntaxError identifier_of(info) "
  // 121:       Invalid access to dynamic read-only variable "@(name)@quot;@
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
  // 123: ... variable_kind_of(info)
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
  // 123: ... POLYMORPHIC, DYNAMIC_SINGLE, POLYMORPHIC
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
  // 123: ... :
  // 124:   SyntaxError identifier_of(info) "
  // 125:     Invalid access to dynamic read-write variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__check_usage_35, 0);
  // 123: case variable_kind_of(info) POLYMORPHIC, DYNAMIC_SINGLE, POLYMORPHIC:
  // 124:   SyntaxError identifier_of(info) "
  // 125:     Invalid access to dynamic read-write variable "@(name)@quot;@
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
  // 101: ... variable_kind_of(definition)
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
  // 102: ... :
  // 103:   case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 104:     SyntaxError identifier_of(info) "
  // 105:       Invalid access to polymorphic function "@(name)@quot;@
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__check_usage_3, 0);
  // 106: ... :
  // 107:   case
  // 108:     variable_kind_of(info)
  // 109:     STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 110:       SyntaxError identifier_of(info) "
  // 111:         Invalid access to read-only variable "@(name)@quot;@
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__check_usage_11, 0);
  // 112: ... :
  // 113:   case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 114:     SyntaxError identifier_of(info) "
  // 115:       Invalid access to static read-write variable "@(name)@quot;@
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__check_usage_18, 0);
  // 116: ... :
  // 117:   case
  // 118:     variable_kind_of(info)
  // 119:     POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI, POLYMORPHIC:
  // 120:       SyntaxError identifier_of(info) "
  // 121:         Invalid access to dynamic read-only variable "@(name)@quot;@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__check_usage_25, 0);
  // 122: ... :
  // 123:   case variable_kind_of(info) POLYMORPHIC, DYNAMIC_SINGLE, POLYMORPHIC:
  // 124:     SyntaxError identifier_of(info) "
  // 125:       Invalid access to dynamic read-write variable "@(name)@quot;@
  frame->slots[8] /* temp__6 */ = create_closure(entry__compiler__check_usage_32, 0);
  // 101: case variable_kind_of(definition)
  // 102:   POLYMORPHIC:
  // 103:     case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 104:       SyntaxError identifier_of(info) "
  // 105:         Invalid access to polymorphic function "@(name)@quot;@
  // 106:   STATIC_SINGLE:
  // 107:     case
  // 108:       variable_kind_of(info)
  // 109:       STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI, POLYMORPHIC:
  // 110:         SyntaxError identifier_of(info) "
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
  // 131: show_compiler_debug_info "simplify statement (default)"
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
  // 132: push &statements self
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
  // 135: show_compiler_debug_info "simplify expression (default)"
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
  // 141: show_compiler_debug_info "simplify body"
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
  // 142: $$all_defined_names already_defined_names
  ((CELL *)frame->slots[1])->contents /* all_defined_names */ = get__already_defined_names();
  // 143: ... defined_names_of(self)
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
  // 143: ... : (name info)
  // 144:   $outer_info already_defined_names(name)
  // 145:   if
  // 146:     outer_info.is_defined:
  // 147:       SyntaxError identifier_of(info) "
  // 148:         An identifier named "@(name)" was already defined in an outer scope @
  // 149:         or in a used namespace@
  // 150:     :
  // 151:       !all_defined_names(name) info
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_5, 2);
  // 143: for_each defined_names_of(self): (name info)
  // 144:   $outer_info already_defined_names(name)
  // 145:   if
  // 146:     outer_info.is_defined:
  // 147:       SyntaxError identifier_of(info) "
  // 148:         An identifier named "@(name)" was already defined in an outer scope @
  // 149:         or in a used namespace@
  // 150:     :
  // 151:       !all_defined_names(name) info
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
  // 147: ... identifier_of(info)
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
  // 147: ... "
  // 148:   An identifier named "@(name)" was already defined in an outer scope @
  // 149:   or in a used namespace@
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
  // 147: SyntaxError identifier_of(info) "
  // 148:   An identifier named "@(name)" was already defined in an outer scope @
  // 149:   or in a used namespace@
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
  allocate_initialized_frame_gc(3, 3);
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
  // 151: !all_defined_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[2] /* info */;
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
  // 144: $outer_info already_defined_names(name)
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
  // 146: outer_info.is_defined
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
  // 146: ... :
  // 147:   SyntaxError identifier_of(info) "
  // 148:     An identifier named "@(name)" was already defined in an outer scope @
  // 149:     or in a used namespace@
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_8, 0);
  // 150: :
  // 151:   !all_defined_names(name) info
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_13, 0);
  // 145: if
  // 146:   outer_info.is_defined:
  // 147:     SyntaxError identifier_of(info) "
  // 148:       An identifier named "@(name)" was already defined in an outer scope @
  // 149:       or in a used namespace@
  // 150:   :
  // 151:     !all_defined_names(name) info
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
  // 152: ... used_names_of(self)
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
  // 152: ... : (name info)
  // 153:   $definition all_defined_names(name)
  // 154:   if definition.is_defined:
  // 155:     check_usage name definition info
  // 156:     if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 157:       !self.inherited_names_of(name) info
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_17, 2);
  // 152: for_each used_names_of(self): (name info)
  // 153:   $definition all_defined_names(name)
  // 154:   if definition.is_defined:
  // 155:     check_usage name definition info
  // 156:     if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 157:       !self.inherited_names_of(name) info
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
  allocate_initialized_frame_gc(3, 4);
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
  // 157: ... self.inherited_names_of
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
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 157: !self.inherited_names_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[2] /* info */;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_30;
}
static void cont__compiler__body__simplify_expression_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 157: !self.inherited_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__inherited_names_of, frame->slots[3] /* temp__1 */);
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
  // 155: check_usage name definition info
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
  // 156: ... defined_names(name)
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
  // 156: ... defined_names(name).is_defined
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
  // 156: ... inherited_names(name).is_defined
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__body__simplify_expression_24, 0);
  // 156: ... defined_names(name).is_defined || inherited_names(name).is_defined
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
  // 156: ... inherited_names(name)
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
  // 156: ... inherited_names(name).is_defined
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
  // 156: ... inherited_names(name).is_defined
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
  // 156: ... :
  // 157:   !self.inherited_names_of(name) info
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__body__simplify_expression_28, 0);
  // 156: if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 157:   !self.inherited_names_of(name) info
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
  // 153: $definition all_defined_names(name)
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
  // 154: ... definition.is_defined
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
  // 154: ... :
  // 155:   check_usage name definition info
  // 156:   if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 157:     !self.inherited_names_of(name) info
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_20, 0);
  // 154: if definition.is_defined:
  // 155:   check_usage name definition info
  // 156:   if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 157:     !self.inherited_names_of(name) info
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
  // 158: ... :
  // 159:   %defined_names defined_names_of(self)
  // 160:   %inherited_names inherited_names_of(self)
  // 161:   %already_defined_names all_defined_names
  // 162:   %%definitions empty_list
  // 163:   %%statements empty_list
  // 164:   $$max_temp_idx 0
  // 165:   update_each &self.parameters_of: (&parameter)
  // 166:     $$default_value default_value_of(parameter)
  // 167:     if default_value.is_defined:
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__body__simplify_expression_32, 0);
  // 158: do:
  // 159:   %defined_names defined_names_of(self)
  // 160:   %inherited_names inherited_names_of(self)
  // 161:   %already_defined_names all_defined_names
  // 162:   %%definitions empty_list
  // 163:   %%statements empty_list
  // 164:   $$max_temp_idx 0
  // 165:   update_each &self.parameters_of: (&parameter)
  // 166:     $$default_value default_value_of(parameter)
  // 167:     if default_value.is_defined:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_91;
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
  // 159: %defined_names defined_names_of(self)
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
  // 160: %inherited_names inherited_names_of(self)
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
  // 161: %already_defined_names all_defined_names
  initialize_maybe_future(get__already_defined_names(), ((CELL *)frame->slots[2])->contents /* all_defined_names */);
  // 162: %%definitions empty_list
  set__definitions(get__empty_list());
  // 163: %%statements empty_list
  set__statements(get__empty_list());
  // 164: $$max_temp_idx 0
  ((CELL *)frame->slots[3])->contents /* max_temp_idx */ = number__0;
  // 165: ... self.parameters_of
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
  // 165: ... : (&parameter)
  // 166:   $$default_value default_value_of(parameter)
  // 167:   if default_value.is_defined:
  // 168:     if
  // 169:       default_value.is_a_function_call:
  // 170:         %%statements empty_list
  // 171:         %%compiler::temp_idx 0
  // 172:         $identifier identifier_of(parameter)
  // 173:         simplify_statement
  // 174:           assignment
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_36, 1);
  // 165: update_each &self.parameters_of: (&parameter)
  // 166:   $$default_value default_value_of(parameter)
  // 167:   if default_value.is_defined:
  // 168:     if
  // 169:       default_value.is_a_function_call:
  // 170:         %%statements empty_list
  // 171:         %%compiler::temp_idx 0
  // 172:         $identifier identifier_of(parameter)
  // 173:         simplify_statement
  // 174:           assignment
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_52;
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
  // 166: $$default_value default_value_of(parameter)
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
  // 167: ... default_value.is_defined
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
  // 167: ... :
  // 168:   if
  // 169:     default_value.is_a_function_call:
  // 170:       %%statements empty_list
  // 171:       %%compiler::temp_idx 0
  // 172:       $identifier identifier_of(parameter)
  // 173:       simplify_statement
  // 174:         assignment
  // 175:           .arguments_of
  // 176:             list(parameter(.is_an_optional_item false) default_value)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_39, 0);
  // 167: if default_value.is_defined:
  // 168:   if
  // 169:     default_value.is_a_function_call:
  // 170:       %%statements empty_list
  // 171:       %%compiler::temp_idx 0
  // 172:       $identifier identifier_of(parameter)
  // 173:       simplify_statement
  // 174:         assignment
  // 175:           .arguments_of
  // 176:             list(parameter(.is_an_optional_item false) default_value)
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
  frame->cont = cont__compiler__body__simplify_expression_51;
}
static void entry__compiler__body__simplify_expression_41(void) {
  allocate_initialized_frame_gc(4, 11);
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
  // 170: %%statements empty_list
  set__statements(get__empty_list());
  // 171: %%compiler::temp_idx 0
  set__compiler__temp_idx(number__0);
  // 172: $identifier identifier_of(parameter)
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
  // 176: ... parameter(.is_an_optional_item false)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__false());
    frame->slots[7] /* temp__3 */ = temp;

  }
  // 176: list(parameter(.is_an_optional_item false) default_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* default_value */;
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
  // 177: ... fragment_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_44;
}
static void cont__compiler__body__simplify_expression_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 178: ... source_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_45;
}
static void cont__compiler__body__simplify_expression_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 179: ... end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_46;
}
static void cont__compiler__body__simplify_expression_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[8] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[9] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[10] /* temp__6 */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 173: simplify_statement
  // 174:   assignment
  // 175:     .arguments_of
  // 176:       list(parameter(.is_an_optional_item false) default_value)
  // 177:     .fragment_of fragment_of(identifier)
  // 178:     .source_position_of source_position_of(identifier)
  // 179:     .end_position_of end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_47;
}
static void cont__compiler__body__simplify_expression_47(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 180: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_48;
}
static void cont__compiler__body__simplify_expression_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* max_temp_idx */ = arguments->slots[0];
  // 181: !parameter.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, get__statements());
    ((CELL *)frame->slots[1])->contents /* parameter */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__body__simplify_expression_49(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // default_value: 0
  // parameter: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* default_value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: simplify_expression &default_value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* default_value */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_50;
}
static void cont__compiler__body__simplify_expression_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* default_value */ = arguments->slots[0];
  // 184: !parameter.default_value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__default_value_of, ((CELL *)frame->slots[0])->contents /* default_value */);
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
  // 169: default_value.is_a_function_call
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
  // 169: ... :
  // 170:   %%statements empty_list
  // 171:   %%compiler::temp_idx 0
  // 172:   $identifier identifier_of(parameter)
  // 173:   simplify_statement
  // 174:     assignment
  // 175:       .arguments_of
  // 176:         list(parameter(.is_an_optional_item false) default_value)
  // 177:       .fragment_of fragment_of(identifier)
  // 178:       .source_position_of source_position_of(identifier)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_41, 0);
  // 182: :
  // 183:   simplify_expression &default_value
  // 184:   !parameter.default_value_of default_value
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_49, 0);
  // 168: if
  // 169:   default_value.is_a_function_call:
  // 170:     %%statements empty_list
  // 171:     %%compiler::temp_idx 0
  // 172:     $identifier identifier_of(parameter)
  // 173:     simplify_statement
  // 174:       assignment
  // 175:         .arguments_of
  // 176:           list(parameter(.is_an_optional_item false) default_value)
  // 177:         .fragment_of fragment_of(identifier)
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
static void cont__compiler__body__simplify_expression_51(void) {
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
static void cont__compiler__body__simplify_expression_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 165: ... &self.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[6] /* temp__3 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 188: ... statements_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_53;
}
static void cont__compiler__body__simplify_expression_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 188: ... : (statement)
  // 189:   unless statement.is_a_remark:
  // 190:     if
  // 191:       &&
  // 192:         statement.is_an_assignment
  // 193:         arguments_of(statement)(1).is_a_static_single_definition
  // 194:         arguments_of(statement)(2).is_a_constant
  // 195:       :
  // 196:         %%compiler::temp_idx 0
  // 197:         simplify_statement statement
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_54, 1);
  // 188: for_each statements_of(self): (statement)
  // 189:   unless statement.is_a_remark:
  // 190:     if
  // 191:       &&
  // 192:         statement.is_an_assignment
  // 193:         arguments_of(statement)(1).is_a_static_single_definition
  // 194:         arguments_of(statement)(2).is_a_constant
  // 195:       :
  // 196:         %%compiler::temp_idx 0
  // 197:         simplify_statement statement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_71;
}
static void entry__compiler__body__simplify_expression_68(void) {
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
  // 196: %%compiler::temp_idx 0
  set__compiler__temp_idx(number__0);
  // 197: simplify_statement statement
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_69;
}
static void cont__compiler__body__simplify_expression_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 198: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_70;
}
static void cont__compiler__body__simplify_expression_70(void) {
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
static void entry__compiler__body__simplify_expression_56(void) {
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
  // 192: statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_57;
}
static void cont__compiler__body__simplify_expression_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_58, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_67;
}
static void entry__compiler__body__simplify_expression_58(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 193: arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_59;
}
static void cont__compiler__body__simplify_expression_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 193: arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_60;
}
static void cont__compiler__body__simplify_expression_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 193: arguments_of(statement)(1).is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_61;
}
static void cont__compiler__body__simplify_expression_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 194: arguments_of(statement)(2).is_a_constant
  frame->slots[5] /* temp__5 */ = create_closure(entry__compiler__body__simplify_expression_62, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_66;
}
static void entry__compiler__body__simplify_expression_62(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_63;
}
static void cont__compiler__body__simplify_expression_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 194: arguments_of(statement)(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_64;
}
static void cont__compiler__body__simplify_expression_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 194: arguments_of(statement)(2).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_65;
}
static void cont__compiler__body__simplify_expression_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 194: arguments_of(statement)(2).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_66(void) {
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
static void cont__compiler__body__simplify_expression_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 195: :
  // 196:   %%compiler::temp_idx 0
  // 197:   simplify_statement statement
  // 198:   extend_to &max_temp_idx temp_idx
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__body__simplify_expression_68, 0);
  // 190: if
  // 191:   &&
  // 192:     statement.is_an_assignment
  // 193:     arguments_of(statement)(1).is_a_static_single_definition
  // 194:     arguments_of(statement)(2).is_a_constant
  // 195:   :
  // 196:     %%compiler::temp_idx 0
  // 197:     simplify_statement statement
  // 198:     extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__body__simplify_expression_54(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[1] = myself->closure.frame->slots[3]; /* max_temp_idx */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 189: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_55;
}
static void cont__compiler__body__simplify_expression_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 189: ... :
  // 190:   if
  // 191:     &&
  // 192:       statement.is_an_assignment
  // 193:       arguments_of(statement)(1).is_a_static_single_definition
  // 194:       arguments_of(statement)(2).is_a_constant
  // 195:     :
  // 196:       %%compiler::temp_idx 0
  // 197:       simplify_statement statement
  // 198:       extend_to &max_temp_idx temp_idx
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_56, 0);
  // 189: unless statement.is_a_remark:
  // 190:   if
  // 191:     &&
  // 192:       statement.is_an_assignment
  // 193:       arguments_of(statement)(1).is_a_static_single_definition
  // 194:       arguments_of(statement)(2).is_a_constant
  // 195:     :
  // 196:       %%compiler::temp_idx 0
  // 197:       simplify_statement statement
  // 198:       extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__body__simplify_expression_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 202: ... statements_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_72;
}
static void cont__compiler__body__simplify_expression_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 202: ... : (statement)
  // 203:   unless statement.is_a_remark:
  // 204:     unless
  // 205:       &&
  // 206:         statement.is_an_assignment
  // 207:         arguments_of(statement)(1).is_a_static_single_definition
  // 208:         arguments_of(statement)(2).is_a_constant
  // 209:       :
  // 210:         %%compiler::temp_idx 0
  // 211:         simplify_statement statement
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_73, 1);
  // 202: for_each statements_of(self): (statement)
  // 203:   unless statement.is_a_remark:
  // 204:     unless
  // 205:       &&
  // 206:         statement.is_an_assignment
  // 207:         arguments_of(statement)(1).is_a_static_single_definition
  // 208:         arguments_of(statement)(2).is_a_constant
  // 209:       :
  // 210:         %%compiler::temp_idx 0
  // 211:         simplify_statement statement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_90;
}
static void entry__compiler__body__simplify_expression_87(void) {
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
  // 210: %%compiler::temp_idx 0
  set__compiler__temp_idx(number__0);
  // 211: simplify_statement statement
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_88;
}
static void cont__compiler__body__simplify_expression_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 212: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_89;
}
static void cont__compiler__body__simplify_expression_89(void) {
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
static void entry__compiler__body__simplify_expression_75(void) {
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
  // 206: statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_76;
}
static void cont__compiler__body__simplify_expression_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_77, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_86;
}
static void entry__compiler__body__simplify_expression_77(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_78;
}
static void cont__compiler__body__simplify_expression_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 207: arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_79;
}
static void cont__compiler__body__simplify_expression_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 207: arguments_of(statement)(1).is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_80;
}
static void cont__compiler__body__simplify_expression_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 208: arguments_of(statement)(2).is_a_constant
  frame->slots[5] /* temp__5 */ = create_closure(entry__compiler__body__simplify_expression_81, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_85;
}
static void entry__compiler__body__simplify_expression_81(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 208: arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_82;
}
static void cont__compiler__body__simplify_expression_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 208: arguments_of(statement)(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_83;
}
static void cont__compiler__body__simplify_expression_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 208: arguments_of(statement)(2).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_84;
}
static void cont__compiler__body__simplify_expression_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 208: arguments_of(statement)(2).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_85(void) {
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
static void cont__compiler__body__simplify_expression_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 209: :
  // 210:   %%compiler::temp_idx 0
  // 211:   simplify_statement statement
  // 212:   extend_to &max_temp_idx temp_idx
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__body__simplify_expression_87, 0);
  // 204: unless
  // 205:   &&
  // 206:     statement.is_an_assignment
  // 207:     arguments_of(statement)(1).is_a_static_single_definition
  // 208:     arguments_of(statement)(2).is_a_constant
  // 209:   :
  // 210:     %%compiler::temp_idx 0
  // 211:     simplify_statement statement
  // 212:     extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__body__simplify_expression_73(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[1] = myself->closure.frame->slots[3]; /* max_temp_idx */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 203: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_74;
}
static void cont__compiler__body__simplify_expression_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 203: ... :
  // 204:   unless
  // 205:     &&
  // 206:       statement.is_an_assignment
  // 207:       arguments_of(statement)(1).is_a_static_single_definition
  // 208:       arguments_of(statement)(2).is_a_constant
  // 209:     :
  // 210:       %%compiler::temp_idx 0
  // 211:       simplify_statement statement
  // 212:       extend_to &max_temp_idx temp_idx
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__body__simplify_expression_75, 0);
  // 203: unless statement.is_a_remark:
  // 204:   unless
  // 205:     &&
  // 206:       statement.is_an_assignment
  // 207:       arguments_of(statement)(1).is_a_static_single_definition
  // 208:       arguments_of(statement)(2).is_a_constant
  // 209:     :
  // 210:       %%compiler::temp_idx 0
  // 211:       simplify_statement statement
  // 212:       extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__body__simplify_expression_90(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 213: !self.definitions_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__definitions_of, get__definitions());
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 214: !self.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, get__statements());
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 215: !self.temporary_count_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__temporary_count_of, ((CELL *)frame->slots[3])->contents /* max_temp_idx */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__4 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_91(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 216: ... inherited_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__inherited_names_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_92;
}
static void cont__compiler__body__simplify_expression_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 216: ... inherited_names_of(self).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_93;
}
static void cont__compiler__body__simplify_expression_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 216: ... :
  // 217:   #
  // 218:     a closure must be created in a separate step because it is not really
  // 219:     a constant
  // 220:   
  // 221:   $temp temporary_identifier()
  // 222:   push
  // 223:     &statements
  // 224:     assignment
  // 225:       .arguments_of list(temp(.is_a_destination true) self)
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__body__simplify_expression_94, 0);
  // 216: unless inherited_names_of(self).is_empty:
  // 217:   #
  // 218:     a closure must be created in a separate step because it is not really
  // 219:     a constant
  // 220:   
  // 221:   $temp temporary_identifier()
  // 222:   push
  // 223:     &statements
  // 224:     assignment
  // 225:       .arguments_of list(temp(.is_a_destination true) self)
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
  frame->cont = cont__compiler__body__simplify_expression_101;
}
static void entry__compiler__body__simplify_expression_94(void) {
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
  // 221: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_95;
}
static void cont__compiler__body__simplify_expression_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* temp */, arguments->slots[0]);
  // 225: ... temp(.is_a_destination true)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__true());
    frame->slots[4] /* temp__3 */ = temp;

  }
  // 225: ... list(temp(.is_a_destination true) self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_96;
}
static void cont__compiler__body__simplify_expression_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 226: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_97;
}
static void cont__compiler__body__simplify_expression_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 227: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_98;
}
static void cont__compiler__body__simplify_expression_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 228: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_99;
}
static void cont__compiler__body__simplify_expression_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[7] /* temp__6 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 222: push
  // 223:   &statements
  // 224:   assignment
  // 225:     .arguments_of list(temp(.is_a_destination true) self)
  // 226:     .fragment_of fragment_of(self)
  // 227:     .source_position_of source_position_of(self)
  // 228:     .end_position_of end_position_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__body__simplify_expression_100;
}
static void cont__compiler__body__simplify_expression_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 229: !self temp
  ((CELL *)frame->slots[0])->contents /* self */ = frame->slots[1] /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body__simplify_expression_101(void) {
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
  allocate_initialized_frame_gc(6, 15);
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
  // 238: update_each &arguments: (&argument) simplify_expression &argument
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
  // 238: ... simplify_expression &argument
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
  // 239: ... length_of(rest)
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
  // 239: ... length_of(rest) > 0
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
  // 239: ... :
  // 240:   $temp temporary_identifier()
  // 241:   push
  // 242:     &statements
  // 243:     procedure_call
  // 244:       .functor_of functor
  // 245:       .arguments_of put(arguments temp(.is_a_destination true))
  // 246:       .fragment_of fragment_of(info)
  // 247:       .source_position_of source_position_of(info)
  // 248:       .end_position_of end_position_of(info)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__do_store_10, 0);
  // 239: if length_of(rest) > 0:
  // 240:   $temp temporary_identifier()
  // 241:   push
  // 242:     &statements
  // 243:     procedure_call
  // 244:       .functor_of functor
  // 245:       .arguments_of put(arguments temp(.is_a_destination true))
  // 246:       .fragment_of fragment_of(info)
  // 247:       .source_position_of source_position_of(info)
  // 248:       .end_position_of end_position_of(info)
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
  allocate_initialized_frame_gc(6, 13);
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
  // 240: $temp temporary_identifier()
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
  // 245: ... temp(.is_a_destination true)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__true());
    frame->slots[9] /* temp__3 */ = temp;

  }
  // 245: ... put(arguments temp(.is_a_destination true))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__do_store_12;
}
static void cont__do_store_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 246: ... fragment_of(info)
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
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 247: ... source_position_of(info)
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
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 248: ... end_position_of(info)
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
  frame->slots[12] /* temp__6 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[10] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[11] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[12] /* temp__6 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 241: push
  // 242:   &statements
  // 243:   procedure_call
  // 244:     .functor_of functor
  // 245:     .arguments_of put(arguments temp(.is_a_destination true))
  // 246:     .fragment_of fragment_of(info)
  // 247:     .source_position_of source_position_of(info)
  // 248:     .end_position_of end_position_of(info)
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
  // 249: ... rest.peek
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
  // 249: ... rest.drop
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
  // 249: do_store temp rest.peek result rest.drop infos
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
  // 250: !result temp
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
  // 257: ... functor(.is_a_destination true)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* functor */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__true());
    frame->slots[9] /* temp__4 */ = temp;

  }
  // 257: put(arguments functor(.is_a_destination true))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__do_store_21;
}
static void cont__do_store_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 258: result(.is_a_destination false)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* result */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__false());
    frame->slots[10] /* temp__5 */ = temp;

  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = frame->slots[10] /* temp__5 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__do_store_22;
}
static void cont__do_store_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 259: ... fragment_of(info)
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
  frame->slots[11] /* temp__6 */ = arguments->slots[0];
  // 260: ... source_position_of(info)
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
  frame->slots[13] /* temp__8 */ = arguments->slots[0];
  // 260: ... source_position_of(info)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__8 */;
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
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 261: ... end_position_of(info)
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
  frame->slots[14] /* temp__9 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[11] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[12] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[14] /* temp__9 */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 251: push
  // 252:   &statements
  // 253:   procedure_call
  // 254:     .functor_of functor
  // 255:     .arguments_of
  // 256:       push
  // 257:         put(arguments functor(.is_a_destination true))
  // 258:         result(.is_a_destination false)
  // 259:     .fragment_of fragment_of(info)
  // 260:     .source_position_of source_position_of(info)+1
  // ...
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
  // 263: ... length_of(rest)
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
  // 263: ... length_of(rest) > 0
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
  // 263: ... :
  // 264:   $temp temporary_identifier()
  // 265:   push
  // 266:     &statements
  // 267:     procedure_call
  // 268:       .functor_of functor_of(arguments)
  // 269:       .arguments_of list(temp(.is_a_destination true) functor)
  // 270:       .fragment_of fragment_of(info)
  // 271:       .source_position_of source_position_of(info)
  // 272:       .end_position_of end_position_of(info)
  // ...
  frame->slots[9] /* temp__3 */ = create_closure(entry__do_store_31, 0);
  // 263: if length_of(rest) > 0:
  // 264:   $temp temporary_identifier()
  // 265:   push
  // 266:     &statements
  // 267:     procedure_call
  // 268:       .functor_of functor_of(arguments)
  // 269:       .arguments_of list(temp(.is_a_destination true) functor)
  // 270:       .fragment_of fragment_of(info)
  // 271:       .source_position_of source_position_of(info)
  // 272:       .end_position_of end_position_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__do_store_42;
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
  // 264: $temp temporary_identifier()
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
  // 268: ... functor_of(arguments)
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
  // 269: ... temp(.is_a_destination true)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__true());
    frame->slots[10] /* temp__4 */ = temp;

  }
  // 269: ... list(temp(.is_a_destination true) functor)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__4 */;
  arguments->slots[1] = frame->slots[1] /* functor */;
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
  // 270: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__do_store_35;
}
static void cont__do_store_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 271: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__do_store_36;
}
static void cont__do_store_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__6 */ = arguments->slots[0];
  // 272: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__do_store_37;
}
static void cont__do_store_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__7 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[11] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[12] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[13] /* temp__7 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 265: push
  // 266:   &statements
  // 267:   procedure_call
  // 268:     .functor_of functor_of(arguments)
  // 269:     .arguments_of list(temp(.is_a_destination true) functor)
  // 270:     .fragment_of fragment_of(info)
  // 271:     .source_position_of source_position_of(info)
  // 272:     .end_position_of end_position_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__do_store_38;
}
static void cont__do_store_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 273: ... rest.peek
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__do_store_39;
}
static void cont__do_store_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 273: ... rest.drop
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__drop();
  func = myself->type;
  frame->cont = cont__do_store_40;
}
static void cont__do_store_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 273: do_store temp rest.peek result rest.drop infos
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
  frame->cont = cont__do_store_41;
}
static void cont__do_store_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 274: !result temp
  ((CELL *)frame->slots[4])->contents /* result */ = frame->slots[6] /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__do_store_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 278: arguments.is_a_method_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__is_a_method_definition();
  func = myself->type;
  frame->cont = cont__do_store_43;
}
static void cont__do_store_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 276: $attribute_pair
  // 277:   if
  // 278:     arguments.is_a_method_definition
  // 279:     -> attribute_function_pair
  // 280:     -> attribute_value_pair
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__do_store_44;
  arguments->slots[2] = func__do_store_45;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__do_store_46;
}
static void entry__do_store_44(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 279: -> attribute_function_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__do_store_45(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 280: -> attribute_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_value_pair();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__do_store_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* attribute_pair */, arguments->slots[0]);
  // 287: functor(.is_a_destination true)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* functor */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__true());
    frame->slots[9] /* temp__3 */ = temp;

  }
  // 289: ... functor_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__do_store_47;
}
static void cont__do_store_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 290: ... list(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* result */;
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
  frame->slots[12] /* temp__6 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* attribute_pair */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[11] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[12] /* temp__6 */);
    frame->slots[10] /* temp__4 */ = temp;

  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__do_store_49;
}
static void cont__do_store_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 291: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__do_store_50;
}
static void cont__do_store_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__7 */ = arguments->slots[0];
  // 292: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__do_store_51;
}
static void cont__do_store_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__9 */ = arguments->slots[0];
  // 292: ... source_position_of(info)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__9 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__do_store_52;
}
static void cont__do_store_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__8 */ = arguments->slots[0];
  // 293: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__do_store_53;
}
static void cont__do_store_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__10 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[13] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[14] /* temp__8 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[16] /* temp__10 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 282: push
  // 283:   &statements
  // 284:   assignment
  // 285:     .arguments_of
  // 286:       list
  // 287:         functor(.is_a_destination true)
  // 288:         attribute_pair
  // 289:           .identifier_of functor_of(arguments)
  // 290:           .arguments_of list(result)
  // 291:     .fragment_of fragment_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__do_store_54;
}
static void cont__do_store_54(void) {
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
  // 235: pop &infos $info
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
  initialize_future(frame->slots[5] /* info */, arguments->slots[1]);
  // 237: arguments.is_a_list
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
  // 237: ... :
  // 238:   update_each &arguments: (&argument) simplify_expression &argument
  // 239:   if length_of(rest) > 0:
  // 240:     $temp temporary_identifier()
  // 241:     push
  // 242:       &statements
  // 243:       procedure_call
  // 244:         .functor_of functor
  // 245:         .arguments_of put(arguments temp(.is_a_destination true))
  // 246:         .fragment_of fragment_of(info)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__do_store_4, 0);
  // 262: :
  // 263:   if length_of(rest) > 0:
  // 264:     $temp temporary_identifier()
  // 265:     push
  // 266:       &statements
  // 267:       procedure_call
  // 268:         .functor_of functor_of(arguments)
  // 269:         .arguments_of list(temp(.is_a_destination true) functor)
  // 270:         .fragment_of fragment_of(info)
  // 271:         .source_position_of source_position_of(info)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__do_store_28, 0);
  // 236: if
  // 237:   arguments.is_a_list:
  // 238:     update_each &arguments: (&argument) simplify_expression &argument
  // 239:     if length_of(rest) > 0:
  // 240:       $temp temporary_identifier()
  // 241:       push
  // 242:         &statements
  // 243:         procedure_call
  // 244:           .functor_of functor
  // 245:           .arguments_of put(arguments temp(.is_a_destination true))
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
  // 315: do_store functor arguments result rest infos
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
  // 317: ... push(rest arguments)
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
  // 317: store_result functor result push(rest arguments) infos
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
  // 308: ... arguments(1)
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
  // 308: do_store arguments(1) destination result rest infos
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
  // 310: ... arguments(1)
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
  // 310: ... push(rest destination)
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
  // 310: store_result arguments(1) result push(rest destination) infos
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
  // 307: arguments(1)
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
  // 307: arguments(1).is_an_identifier
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
  // 307: ... :
  // 308:   do_store arguments(1) destination result rest infos
  frame->slots[7] /* temp__3 */ = create_closure(entry__store_result_8, 0);
  // 309: :
  // 310:   store_result arguments(1) result push(rest destination) infos
  frame->slots[8] /* temp__4 */ = create_closure(entry__store_result_10, 0);
  // 306: if
  // 307:   arguments(1).is_an_identifier:
  // 308:     do_store arguments(1) destination result rest infos
  // 309:   :
  // 310:     store_result arguments(1) result push(rest destination) infos
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
  // 312: $functor functor_of(destination)
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
  // 314: functor.is_an_identifier
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
  // 314: ... :
  // 315:   do_store functor arguments result rest infos
  frame->slots[7] /* temp__2 */ = create_closure(entry__store_result_16, 0);
  // 316: :
  // 317:   store_result functor result push(rest arguments) infos
  frame->slots[8] /* temp__3 */ = create_closure(entry__store_result_17, 0);
  // 313: if
  // 314:   functor.is_an_identifier:
  // 315:     do_store functor arguments result rest infos
  // 316:   :
  // 317:     store_result functor result push(rest arguments) infos
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
  // 302: push &infos destination
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
  // 303: $arguments arguments_of(destination)
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
  // 305: destination.is_an_attribute_access
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
  // 305: ... :
  // 306:   if
  // 307:     arguments(1).is_an_identifier:
  // 308:       do_store arguments(1) destination result rest infos
  // 309:     :
  // 310:       store_result arguments(1) result push(rest destination) infos
  frame->slots[6] /* temp__2 */ = create_closure(entry__store_result_5, 0);
  // 311: :
  // 312:   $functor functor_of(destination)
  // 313:   if
  // 314:     functor.is_an_identifier:
  // 315:       do_store functor arguments result rest infos
  // 316:     :
  // 317:       store_result functor result push(rest arguments) infos
  frame->slots[7] /* temp__3 */ = create_closure(entry__store_result_13, 0);
  // 304: if
  // 305:   destination.is_an_attribute_access:
  // 306:     if
  // 307:       arguments(1).is_an_identifier:
  // 308:         do_store arguments(1) destination result rest infos
  // 309:       :
  // 310:         store_result arguments(1) result push(rest destination) infos
  // 311:   :
  // 312:     $functor functor_of(destination)
  // 313:     if
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
  allocate_initialized_frame_gc(2, 10);
  // slot allocations:
  // self: 0
  // return: 1
  // output_arguments: 2
  // input_arguments: 3
  // add_arguments: 4
  // final_destinations: 5
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[4] /* add_arguments */ = create_future();
  frame->slots[2] /* output_arguments */ = create_cell();
  frame->slots[3] /* input_arguments */ = create_cell();
  frame->slots[5] /* final_destinations */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 328: ... : (arguments)
  // 329:   for_each arguments: ($argument)
  // 330:     cond
  // 331:       -> argument.is_an_input_output_argument:
  // 332:         !argument.is_an_input_output_argument false
  // 333:         push &output_arguments argument
  // 334:         push &input_arguments argument(.is_a_destination false)
  // 335:       -> argument.is_a_destination: push &output_arguments argument
  // 336:       :
  // 337:         push &input_arguments argument
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__call__simplify_statement_2, 1);
  // 328: $add_arguments: (arguments)
  // 329:   for_each arguments: ($argument)
  // 330:     cond
  // 331:       -> argument.is_an_input_output_argument:
  // 332:         !argument.is_an_input_output_argument false
  // 333:         push &output_arguments argument
  // 334:         push &input_arguments argument(.is_a_destination false)
  // 335:       -> argument.is_a_destination: push &output_arguments argument
  // 336:       :
  // 337:         push &input_arguments argument
  initialize_future(frame->slots[4] /* add_arguments */, frame->slots[6] /* temp__1 */);
  // 324: show_compiler_debug_info "simplify statement"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8629329e514f7a7a;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_16;
}
static void entry__compiler__call__simplify_statement_11(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // output_arguments: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* output_arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 335: ... push &output_arguments argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_12;
}
static void cont__compiler__call__simplify_statement_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* output_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_6(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // argument: 0
  // output_arguments: 1
  // input_arguments: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* input_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 332: !argument.is_an_input_output_argument
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_input_output_argument, get__false());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 333: push &output_arguments argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_7;
}
static void cont__compiler__call__simplify_statement_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* output_arguments */ = arguments->slots[0];
  // 334: ... argument(.is_a_destination false)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__false());
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 334: push &input_arguments argument(.is_a_destination false)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* input_arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_8;
}
static void cont__compiler__call__simplify_statement_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* input_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // argument: 0
  // output_arguments: 1
  // input_arguments: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* input_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 331: ... argument.is_an_input_output_argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_input_output_argument();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_5;
}
static void cont__compiler__call__simplify_statement_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 331: ... :
  // 332:   !argument.is_an_input_output_argument false
  // 333:   push &output_arguments argument
  // 334:   push &input_arguments argument(.is_a_destination false)
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_6, 0);
  // 331: -> argument.is_an_input_output_argument:
  // 332:   !argument.is_an_input_output_argument false
  // 333:   push &output_arguments argument
  // 334:   push &input_arguments argument(.is_a_destination false)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_9(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // argument: 0
  // output_arguments: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 335: ... argument.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_a_destination();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_10;
}
static void cont__compiler__call__simplify_statement_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 335: ... : push &output_arguments argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_11, 0);
  // 335: -> argument.is_a_destination: push &output_arguments argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_13(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // input_arguments: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* input_arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 337: push &input_arguments argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* input_arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_14;
}
static void cont__compiler__call__simplify_statement_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* input_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_3(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // argument: 0
  // output_arguments: 1
  // input_arguments: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* input_arguments */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 331: -> argument.is_an_input_output_argument:
  // 332:   !argument.is_an_input_output_argument false
  // 333:   push &output_arguments argument
  // 334:   push &input_arguments argument(.is_a_destination false)
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__call__simplify_statement_4, 0);
  // 335: -> argument.is_a_destination: push &output_arguments argument
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_9, 0);
  // 336: :
  // 337:   push &input_arguments argument
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_13, 0);
  // 330: cond
  // 331:   -> argument.is_an_input_output_argument:
  // 332:     !argument.is_an_input_output_argument false
  // 333:     push &output_arguments argument
  // 334:     push &input_arguments argument(.is_a_destination false)
  // 335:   -> argument.is_a_destination: push &output_arguments argument
  // 336:   :
  // 337:     push &input_arguments argument
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_2(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // arguments: 0
  // output_arguments: 1
  // input_arguments: 2
  frame->slots[1] = myself->closure.frame->slots[2]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[3]; /* input_arguments */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 329: ... : ($argument)
  // 330:   cond
  // 331:     -> argument.is_an_input_output_argument:
  // 332:       !argument.is_an_input_output_argument false
  // 333:       push &output_arguments argument
  // 334:       push &input_arguments argument(.is_a_destination false)
  // 335:     -> argument.is_a_destination: push &output_arguments argument
  // 336:     :
  // 337:       push &input_arguments argument
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__call__simplify_statement_3, 1);
  // 329: for_each arguments: ($argument)
  // 330:   cond
  // 331:     -> argument.is_an_input_output_argument:
  // 332:       !argument.is_an_input_output_argument false
  // 333:       push &output_arguments argument
  // 334:       push &input_arguments argument(.is_a_destination false)
  // 335:     -> argument.is_a_destination: push &output_arguments argument
  // 336:     :
  // 337:       push &input_arguments argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__call__simplify_statement_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 325: $$output_arguments empty_list
  ((CELL *)frame->slots[2])->contents /* output_arguments */ = get__empty_list();
  // 326: $$input_arguments empty_list
  ((CELL *)frame->slots[3])->contents /* input_arguments */ = get__empty_list();
  // 339: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_17;
}
static void cont__compiler__call__simplify_statement_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 339: add_arguments arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[4] /* add_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_18;
}
static void cont__compiler__call__simplify_statement_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 340: ... self.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_19;
}
static void cont__compiler__call__simplify_statement_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 340: ... length_of(input_arguments) == 1
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_20, 0);
  // 340: ... self.is_an_assignment && length_of(input_arguments) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_23;
}
static void entry__compiler__call__simplify_statement_20(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // input_arguments: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* input_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 340: ... length_of(input_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* input_arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_21;
}
static void cont__compiler__call__simplify_statement_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 340: ... length_of(input_arguments) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_22;
}
static void cont__compiler__call__simplify_statement_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 340: ... length_of(input_arguments) == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 340: ... :
  // 341:   $source input_arguments(1)
  // 342:   if source.is_a_function_call:
  // 343:     $destination output_arguments(1)
  // 344:     !output_arguments empty_list
  // 345:     !input_arguments empty_list
  // 346:     add_arguments arguments_of(source)
  // 347:     push &output_arguments destination
  // 348:     !self
  // 349:       procedure_call
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__compiler__call__simplify_statement_24, 0);
  // 340: if self.is_an_assignment && length_of(input_arguments) == 1:
  // 341:   $source input_arguments(1)
  // 342:   if source.is_a_function_call:
  // 343:     $destination output_arguments(1)
  // 344:     !output_arguments empty_list
  // 345:     !input_arguments empty_list
  // 346:     add_arguments arguments_of(source)
  // 347:     push &output_arguments destination
  // 348:     !self
  // 349:       procedure_call
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_36;
}
static void entry__compiler__call__simplify_statement_27(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // output_arguments: 0
  // input_arguments: 1
  // add_arguments: 2
  // source: 3
  // self: 4
  // destination: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* output_arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* input_arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* add_arguments */
  frame->slots[3] = myself->closure.frame->slots[4]; /* source */
  frame->slots[4] = myself->closure.frame->slots[3]; /* self */
  frame->slots[5] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: $destination output_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_28;
}
static void cont__compiler__call__simplify_statement_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* destination */, arguments->slots[0]);
  // 344: !output_arguments empty_list
  ((CELL *)frame->slots[0])->contents /* output_arguments */ = get__empty_list();
  // 345: !input_arguments empty_list
  ((CELL *)frame->slots[1])->contents /* input_arguments */ = get__empty_list();
  // 346: ... arguments_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* source */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_29;
}
static void cont__compiler__call__simplify_statement_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 346: add_arguments arguments_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[2] /* add_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_30;
}
static void cont__compiler__call__simplify_statement_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 347: push &output_arguments destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  arguments->slots[1] = frame->slots[5] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_31;
}
static void cont__compiler__call__simplify_statement_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* output_arguments */ = arguments->slots[0];
  // 350: ... functor_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* source */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_32;
}
static void cont__compiler__call__simplify_statement_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 351: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_33;
}
static void cont__compiler__call__simplify_statement_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 352: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_34;
}
static void cont__compiler__call__simplify_statement_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 353: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_35;
}
static void cont__compiler__call__simplify_statement_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  // 348: !self
  // 349:   procedure_call
  // 350:     .functor_of functor_of(source)
  // 351:     .fragment_of fragment_of(self)
  // 352:     .source_position_of source_position_of(self)
  // 353:     .end_position_of end_position_of(self)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[6] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[7] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[8] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[9] /* temp__4 */);
    ((CELL *)frame->slots[4])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_24(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // input_arguments: 0
  // output_arguments: 1
  // add_arguments: 2
  // self: 3
  // source: 4
  frame->slots[0] = myself->closure.frame->slots[3]; /* input_arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[4]; /* add_arguments */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 341: $source input_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* input_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_25;
}
static void cont__compiler__call__simplify_statement_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* source */, arguments->slots[0]);
  // 342: ... source.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* source */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_26;
}
static void cont__compiler__call__simplify_statement_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 342: ... :
  // 343:   $destination output_arguments(1)
  // 344:   !output_arguments empty_list
  // 345:   !input_arguments empty_list
  // 346:   add_arguments arguments_of(source)
  // 347:   push &output_arguments destination
  // 348:   !self
  // 349:     procedure_call
  // 350:       .functor_of functor_of(source)
  // 351:       .fragment_of fragment_of(self)
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_27, 0);
  // 342: if source.is_a_function_call:
  // 343:   $destination output_arguments(1)
  // 344:   !output_arguments empty_list
  // 345:   !input_arguments empty_list
  // 346:   add_arguments arguments_of(source)
  // 347:   push &output_arguments destination
  // 348:   !self
  // 349:     procedure_call
  // 350:       .functor_of functor_of(source)
  // 351:       .fragment_of fragment_of(self)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__call__simplify_statement_36(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: simplify_input_arguments &input_arguments
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* input_arguments */;
  result_count = 1;
  myself = var._simplify_input_arguments;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_37;
}
static void cont__compiler__call__simplify_statement_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* input_arguments */ = arguments->slots[0];
  // 358: self.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_38;
}
static void cont__compiler__call__simplify_statement_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 360: -> simplify_output_arguments(&output_arguments)
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_39, 0);
  // 356: $final_destinations
  // 357:   if
  // 358:     self.is_an_assignment
  // 359:     -> undefined
  // 360:     -> simplify_output_arguments(&output_arguments)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__compiler__call__simplify_statement_41;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_42;
}
static void entry__compiler__call__simplify_statement_39(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // output_arguments: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 360: ... simplify_output_arguments(&output_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  result_count = 2;
  myself = var._simplify_output_arguments;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_40;
}
static void cont__compiler__call__simplify_statement_40(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* output_arguments */ = arguments->slots[0];
  frame->slots[1] /* temp__1 */ = arguments->slots[1];
  // 360: -> simplify_output_arguments(&output_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_41(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 359: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* final_destinations */, arguments->slots[0]);
  // 362: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_43;
}
static void cont__compiler__call__simplify_statement_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 362: ... functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_44;
}
static void cont__compiler__call__simplify_statement_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 362: ... :
  // 363:   if result_count_of(self).is_defined:
  // 364:     simplify_expression &self.result_count_of
  // 365:   if continuation_of(self).is_defined:
  // 366:     simplify_expression &self.continuation_of
  // 367:   simplify_expression &self.functor_of
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_45, 0);
  // 362: if functor_of(self).is_defined:
  // 363:   if result_count_of(self).is_defined:
  // 364:     simplify_expression &self.result_count_of
  // 365:   if continuation_of(self).is_defined:
  // 366:     simplify_expression &self.continuation_of
  // 367:   simplify_expression &self.functor_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_60;
}
static void entry__compiler__call__simplify_statement_45(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 363: ... result_count_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_46;
}
static void cont__compiler__call__simplify_statement_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 363: ... result_count_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_47;
}
static void cont__compiler__call__simplify_statement_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 363: ... :
  // 364:   simplify_expression &self.result_count_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_48, 0);
  // 363: if result_count_of(self).is_defined:
  // 364:   simplify_expression &self.result_count_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_51;
}
static void entry__compiler__call__simplify_statement_48(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: ... self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_49;
}
static void cont__compiler__call__simplify_statement_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 364: simplify_expression &self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_50;
}
static void cont__compiler__call__simplify_statement_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 364: ... &self.result_count_of
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
static void cont__compiler__call__simplify_statement_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 365: ... continuation_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_52;
}
static void cont__compiler__call__simplify_statement_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 365: ... continuation_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_53;
}
static void cont__compiler__call__simplify_statement_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 365: ... :
  // 366:   simplify_expression &self.continuation_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_54, 0);
  // 365: if continuation_of(self).is_defined:
  // 366:   simplify_expression &self.continuation_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_57;
}
static void entry__compiler__call__simplify_statement_54(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 366: ... self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_55;
}
static void cont__compiler__call__simplify_statement_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 366: simplify_expression &self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_56;
}
static void cont__compiler__call__simplify_statement_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 366: ... &self.continuation_of
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
static void cont__compiler__call__simplify_statement_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 367: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_58;
}
static void cont__compiler__call__simplify_statement_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 367: simplify_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_59;
}
static void cont__compiler__call__simplify_statement_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 367: ... &self.functor_of
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
static void cont__compiler__call__simplify_statement_60(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 369: self.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_61;
}
static void cont__compiler__call__simplify_statement_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 369: ... :
  // 370:   $destination output_arguments(1)
  // 371:   if destination.is_a_definition:
  // 372:     if
  // 373:       destination.is_a_single_assign_definition:
  // 374:         $source input_arguments(1)
  // 375:         if attribute_kind_of(destination) != NONE:
  // 376:           push &definitions destination = source
  // 377:           return
  // 378:         cond
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_62, 0);
  // 398: :
  // 399:   update_each &output_arguments: (&argument)
  // 400:     if argument.is_a_definition:
  // 401:       push &definitions argument
  // 402:       !argument.is_an_initialization true
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_107, 0);
  // 368: if
  // 369:   self.is_an_assignment:
  // 370:     $destination output_arguments(1)
  // 371:     if destination.is_a_definition:
  // 372:       if
  // 373:         destination.is_a_single_assign_definition:
  // 374:           $source input_arguments(1)
  // 375:           if attribute_kind_of(destination) != NONE:
  // 376:             push &definitions destination = source
  // 377:             return
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_114;
}
static void entry__compiler__call__simplify_statement_62(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // output_arguments: 0
  // input_arguments: 1
  // return: 2
  // self: 3
  // destination: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* output_arguments */
  frame->slots[1] = myself->closure.frame->slots[3]; /* input_arguments */
  frame->slots[2] = myself->closure.frame->slots[1]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 370: $destination output_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_63;
}
static void cont__compiler__call__simplify_statement_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* destination */, arguments->slots[0]);
  // 371: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_64;
}
static void cont__compiler__call__simplify_statement_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 371: ... :
  // 372:   if
  // 373:     destination.is_a_single_assign_definition:
  // 374:       $source input_arguments(1)
  // 375:       if attribute_kind_of(destination) != NONE:
  // 376:         push &definitions destination = source
  // 377:         return
  // 378:       cond
  // 379:         -> source.is_a_constant || source.is_single_assign:
  // 380:           push &definitions destination = source
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_65, 0);
  // 371: if destination.is_a_definition:
  // 372:   if
  // 373:     destination.is_a_single_assign_definition:
  // 374:       $source input_arguments(1)
  // 375:       if attribute_kind_of(destination) != NONE:
  // 376:         push &definitions destination = source
  // 377:         return
  // 378:       cond
  // 379:         -> source.is_a_constant || source.is_single_assign:
  // 380:           push &definitions destination = source
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_99;
}
static void entry__compiler__call__simplify_statement_86(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // destination: 0
  // source: 1
  // output_arguments: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_87;
}
static void cont__compiler__call__simplify_statement_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 383: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_88;
}
static void cont__compiler__call__simplify_statement_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 384: ... output_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_89;
}
static void cont__compiler__call__simplify_statement_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 384: !output_arguments(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[3] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, get__true());
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 384: !output_arguments(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_90;
}
static void cont__compiler__call__simplify_statement_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* output_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_81(void) {
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
  // 380: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_82;
}
static void cont__compiler__call__simplify_statement_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 380: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
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
  // 381: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_76(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // source: 0
  // destination: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 379: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_77;
}
static void cont__compiler__call__simplify_statement_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 379: ... source.is_single_assign
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_78, 0);
  // 379: ... source.is_a_constant || source.is_single_assign
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_80;
}
static void entry__compiler__call__simplify_statement_78(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 379: ... source.is_single_assign
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_single_assign();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_79;
}
static void cont__compiler__call__simplify_statement_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 379: ... source.is_single_assign
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 379: ... :
  // 380:   push &definitions destination = source
  // 381:   return
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__call__simplify_statement_81, 0);
  // 379: -> source.is_a_constant || source.is_single_assign:
  // 380:   push &definitions destination = source
  // 381:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_84(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // destination: 1
  // output_arguments: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[3]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 382: ... source.might_be_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__might_be_constant();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_85;
}
static void cont__compiler__call__simplify_statement_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 382: ... :
  // 383:   push &definitions destination = source
  // 384:   !output_arguments(1).is_an_initialization true
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_86, 0);
  // 382: -> source.might_be_constant:
  // 383:   push &definitions destination = source
  // 384:   !output_arguments(1).is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_91(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // destination: 0
  // output_arguments: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 386: push &definitions destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[0] /* destination */;
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
  // 387: ... output_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_93;
}
static void cont__compiler__call__simplify_statement_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 387: !output_arguments(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, get__true());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 387: !output_arguments(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_94;
}
static void cont__compiler__call__simplify_statement_94(void) {
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
static void entry__compiler__call__simplify_statement_67(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // input_arguments: 0
  // destination: 1
  // return: 2
  // output_arguments: 3
  // source: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* input_arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[3]; /* output_arguments */
  frame->slots[4] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 374: $source input_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* input_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_68;
}
static void cont__compiler__call__simplify_statement_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* source */, arguments->slots[0]);
  // 375: ... attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_69;
}
static void cont__compiler__call__simplify_statement_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 375: ... attribute_kind_of(destination) != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_70;
}
static void cont__compiler__call__simplify_statement_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 375: ... attribute_kind_of(destination) != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_71;
}
static void cont__compiler__call__simplify_statement_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 375: ... :
  // 376:   push &definitions destination = source
  // 377:   return
  frame->slots[8] /* temp__4 */ = create_closure(entry__compiler__call__simplify_statement_72, 0);
  // 375: if attribute_kind_of(destination) != NONE:
  // 376:   push &definitions destination = source
  // 377:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_75;
}
static void entry__compiler__call__simplify_statement_72(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // destination: 0
  // source: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[4]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 376: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_73;
}
static void cont__compiler__call__simplify_statement_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 376: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_74;
}
static void cont__compiler__call__simplify_statement_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 377: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__call__simplify_statement_75(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 379: -> source.is_a_constant || source.is_single_assign:
  // 380:   push &definitions destination = source
  // 381:   return
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__call__simplify_statement_76, 0);
  // 382: -> source.might_be_constant:
  // 383:   push &definitions destination = source
  // 384:   !output_arguments(1).is_an_initialization true
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_84, 0);
  // 385: :
  // 386:   push &definitions destination
  // 387:   !output_arguments(1).is_an_initialization true
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_91, 0);
  // 378: cond
  // 379:   -> source.is_a_constant || source.is_single_assign:
  // 380:     push &definitions destination = source
  // 381:     return
  // 382:   -> source.might_be_constant:
  // 383:     push &definitions destination = source
  // 384:     !output_arguments(1).is_an_initialization true
  // 385:   :
  // 386:     push &definitions destination
  // 387:     !output_arguments(1).is_an_initialization true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_95(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // destination: 0
  // output_arguments: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 389: push &definitions destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[0] /* destination */;
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
  set__definitions(arguments->slots[0]);
  // 390: ... output_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_97;
}
static void cont__compiler__call__simplify_statement_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 390: !output_arguments(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, get__true());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 390: !output_arguments(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_98;
}
static void cont__compiler__call__simplify_statement_98(void) {
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
static void entry__compiler__call__simplify_statement_65(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // destination: 0
  // input_arguments: 1
  // return: 2
  // output_arguments: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[1]; /* input_arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 373: destination.is_a_single_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__is_a_single_assign_definition();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_66;
}
static void cont__compiler__call__simplify_statement_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 373: ... :
  // 374:   $source input_arguments(1)
  // 375:   if attribute_kind_of(destination) != NONE:
  // 376:     push &definitions destination = source
  // 377:     return
  // 378:   cond
  // 379:     -> source.is_a_constant || source.is_single_assign:
  // 380:       push &definitions destination = source
  // 381:       return
  // 382:     -> source.might_be_constant:
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_67, 0);
  // 388: :
  // 389:   push &definitions destination
  // 390:   !output_arguments(1).is_an_initialization true
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_95, 0);
  // 372: if
  // 373:   destination.is_a_single_assign_definition:
  // 374:     $source input_arguments(1)
  // 375:     if attribute_kind_of(destination) != NONE:
  // 376:       push &definitions destination = source
  // 377:       return
  // 378:     cond
  // 379:       -> source.is_a_constant || source.is_single_assign:
  // 380:         push &definitions destination = source
  // 381:         return
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
static void cont__compiler__call__simplify_statement_99(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 392: destination.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* destination */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_100;
}
static void cont__compiler__call__simplify_statement_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 392: ... :
  // 393:   store_result destination input_arguments(1)
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_101, 0);
  // 394: :
  // 395:   !self.arguments_of append(output_arguments input_arguments)
  // 396:   push &statements self
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_103, 0);
  // 391: if
  // 392:   destination.is_a_function_call:
  // 393:     store_result destination input_arguments(1)
  // 394:   :
  // 395:     !self.arguments_of append(output_arguments input_arguments)
  // 396:     push &statements self
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_106;
}
static void entry__compiler__call__simplify_statement_101(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // destination: 0
  // input_arguments: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[1]; /* input_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 393: ... input_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* input_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_102;
}
static void cont__compiler__call__simplify_statement_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 393: store_result destination input_arguments(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._store_result;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_103(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // self: 0
  // output_arguments: 1
  // input_arguments: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* self */
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[1]; /* input_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 395: !self.arguments_of append(output_arguments input_arguments)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* input_arguments */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_104;
}
static void cont__compiler__call__simplify_statement_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 395: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 396: push &statements self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_105;
}
static void cont__compiler__call__simplify_statement_105(void) {
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
static void cont__compiler__call__simplify_statement_106(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 397: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_107(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // output_arguments: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 399: update_each &output_arguments: (&argument)
  // 400:   if argument.is_a_definition:
  // 401:     push &definitions argument
  // 402:     !argument.is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  arguments->slots[1] = func__compiler__call__simplify_statement_108;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_113;
}
static void entry__compiler__call__simplify_statement_108(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 400: ... argument.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_109;
}
static void cont__compiler__call__simplify_statement_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 400: ... :
  // 401:   push &definitions argument
  // 402:   !argument.is_an_initialization true
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_110, 0);
  // 400: if argument.is_a_definition:
  // 401:   push &definitions argument
  // 402:   !argument.is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_112;
}
static void entry__compiler__call__simplify_statement_110(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 401: push &definitions argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_111;
}
static void cont__compiler__call__simplify_statement_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 402: !argument.is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, get__true());
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_112(void) {
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
static void cont__compiler__call__simplify_statement_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* output_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_114(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 403: !self.arguments_of append(output_arguments input_arguments)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* output_arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* input_arguments */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_115;
}
static void cont__compiler__call__simplify_statement_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 403: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 404: push &statements self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_116;
}
static void cont__compiler__call__simplify_statement_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 405: ... final_destinations.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* final_destinations */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_117;
}
static void cont__compiler__call__simplify_statement_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 405: ... :
  // 406:   for_each final_destinations: (idx destination)
  // 407:     if destination.is_defined:
  // 408:       $result
  // 409:         output_arguments(idx)
  // 410:           .is_an_optional_item false
  // 411:           .is_an_expanded_item false
  // 412:           .is_a_destination false
  // 413:       
  // 414:       if
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_118, 0);
  // 405: if final_destinations.is_defined:
  // 406:   for_each final_destinations: (idx destination)
  // 407:     if destination.is_defined:
  // 408:       $result
  // 409:         output_arguments(idx)
  // 410:           .is_an_optional_item false
  // 411:           .is_an_expanded_item false
  // 412:           .is_a_destination false
  // 413:       
  // 414:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_135;
}
static void entry__compiler__call__simplify_statement_124(void) {
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
  // 416: store_result destination result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* result */;
  result_count = frame->caller_result_count;
  myself = var._store_result;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_125(void) {
  allocate_initialized_frame_gc(2, 8);
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
  // 424: destination.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_126;
}
static void cont__compiler__call__simplify_statement_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 425: -> destination
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_127, 0);
  // 426: -> identifier_of(destination)
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_128, 0);
  // 422: $identifier
  // 423:   if
  // 424:     destination.is_an_identifier
  // 425:     -> destination
  // 426:     -> identifier_of(destination)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_130;
}
static void entry__compiler__call__simplify_statement_127(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 425: -> destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__simplify_statement_128(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 426: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_129;
}
static void cont__compiler__call__simplify_statement_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 426: -> identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__simplify_statement_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* identifier */, arguments->slots[0]);
  // 430: ... list(destination result)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* result */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_131;
}
static void cont__compiler__call__simplify_statement_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 431: ... fragment_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_132;
}
static void cont__compiler__call__simplify_statement_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 432: ... source_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_133;
}
static void cont__compiler__call__simplify_statement_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 433: ... end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_134;
}
static void cont__compiler__call__simplify_statement_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[7] /* temp__5 */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 428: simplify_statement
  // 429:   assignment
  // 430:     .arguments_of list(destination result)
  // 431:     .fragment_of fragment_of(identifier)
  // 432:     .source_position_of source_position_of(identifier)
  // 433:     .end_position_of end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__simplify_statement();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__simplify_statement_121(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // output_arguments: 0
  // idx: 1
  // destination: 2
  // result: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* output_arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[3] /* result */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 409: output_arguments(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_122;
}
static void cont__compiler__call__simplify_statement_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 408: $result
  // 409:   output_arguments(idx)
  // 410:     .is_an_optional_item false
  // 411:     .is_an_expanded_item false
  // 412:     .is_a_destination false
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__false());
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, get__false());
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__false());
    initialize_future(frame->slots[3] /* result */, temp);

  }
  // 415: destination.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_123;
}
static void cont__compiler__call__simplify_statement_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 415: ... :
  // 416:   store_result destination result
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_124, 0);
  // 417: :
  // 418:   #
  // 419:     ATTENTION: strange - only two source code files have destinations
  // 420:     that actually are identifier nodes - maybe an error in the AST?
  // 421:   
  // 422:   $identifier
  // 423:     if
  // 424:       destination.is_an_identifier
  // 425:       -> destination
  // 426:       -> identifier_of(destination)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__call__simplify_statement_125, 0);
  // 414: if
  // 415:   destination.is_a_function_call:
  // 416:     store_result destination result
  // 417:   :
  // 418:     #
  // 419:       ATTENTION: strange - only two source code files have destinations
  // 420:       that actually are identifier nodes - maybe an error in the AST?
  // 421:     
  // 422:     $identifier
  // 423:       if
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
static void entry__compiler__call__simplify_statement_119(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // idx: 0
  // destination: 1
  // output_arguments: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* output_arguments */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 407: ... destination.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__simplify_statement_120;
}
static void cont__compiler__call__simplify_statement_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 407: ... :
  // 408:   $result
  // 409:     output_arguments(idx)
  // 410:       .is_an_optional_item false
  // 411:       .is_an_expanded_item false
  // 412:       .is_a_destination false
  // 413:   
  // 414:   if
  // 415:     destination.is_a_function_call:
  // 416:       store_result destination result
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__simplify_statement_121, 0);
  // 407: if destination.is_defined:
  // 408:   $result
  // 409:     output_arguments(idx)
  // 410:       .is_an_optional_item false
  // 411:       .is_an_expanded_item false
  // 412:       .is_a_destination false
  // 413:   
  // 414:   if
  // 415:     destination.is_a_function_call:
  // 416:       store_result destination result
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
static void entry__compiler__call__simplify_statement_118(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // final_destinations: 0
  // output_arguments: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* final_destinations */
  frame->slots[1] = myself->closure.frame->slots[2]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 406: ... : (idx destination)
  // 407:   if destination.is_defined:
  // 408:     $result
  // 409:       output_arguments(idx)
  // 410:         .is_an_optional_item false
  // 411:         .is_an_expanded_item false
  // 412:         .is_a_destination false
  // 413:     
  // 414:     if
  // 415:       destination.is_a_function_call:
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__call__simplify_statement_119, 2);
  // 406: for_each final_destinations: (idx destination)
  // 407:   if destination.is_defined:
  // 408:     $result
  // 409:       output_arguments(idx)
  // 410:         .is_an_optional_item false
  // 411:         .is_an_expanded_item false
  // 412:         .is_a_destination false
  // 413:     
  // 414:     if
  // 415:       destination.is_a_function_call:
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
static void cont__compiler__call__simplify_statement_135(void) {
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
  // 439: show_compiler_debug_info "simplify function call"
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
  // 440: $temp temporary_identifier()
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
  // 443: ... functor_of(self)
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
  // 444: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_6;
}
static void cont__compiler__function_call__simplify_expression_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 444: ... temp(.is_a_destination true)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__true());
    frame->slots[6] /* temp__5 */ = temp;

  }
  // 444: ... push(arguments_of(self) temp(.is_a_destination true))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
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
  // 445: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_8;
}
static void cont__compiler__function_call__simplify_expression_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 446: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_9;
}
static void cont__compiler__function_call__simplify_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 447: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_10;
}
static void cont__compiler__function_call__simplify_expression_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[3] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[7] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[8] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[9] /* temp__8 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 441: simplify_statement
  // 442:   procedure_call
  // 443:     .functor_of functor_of(self)
  // 444:     .arguments_of push(arguments_of(self) temp(.is_a_destination true))
  // 445:     .fragment_of fragment_of(self)
  // 446:     .source_position_of source_position_of(self)
  // 447:     .end_position_of end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__function_call__simplify_expression_11;
}
static void cont__compiler__function_call__simplify_expression_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 448: -> temp
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
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 454: show_compiler_debug_info "simplify attribute-value pair"
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
  // 455: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair__simplify_expression_4;
}
static void cont__compiler__attribute_value_pair__simplify_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 455: simplify_input_arguments &self.arguments_of
  // 456:   # There must not be any output arguments!!!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._simplify_input_arguments;
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair__simplify_expression_5;
}
static void cont__compiler__attribute_value_pair__simplify_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 455: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
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
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 462: show_compiler_debug_info "simplify attribute-function pair"
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
  // 463: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__simplify_expression_4;
}
static void cont__compiler__attribute_function_pair__simplify_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 463: simplify_input_arguments &self.arguments_of
  // 464:   # There must not be any output arguments!!!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._simplify_input_arguments;
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__simplify_expression_5;
}
static void cont__compiler__attribute_function_pair__simplify_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 463: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
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
  // 470: show_compiler_debug_info "simplify C-code"
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
  // 471: push &actions: !use_inline_c true
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
  // 471: ... !use_inline_c true
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
  // 472: ... kind_of(self)
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
  // 474: :
  // 475:   $name name_of(identifier_of(self))
  // 476:   push &actions: !defined_structs(name) true
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__c_code__simplify_statement_7, 0);
  // 478: :
  // 479:   $name name_of(identifier_of(self))
  // 480:   push &actions: !defined_nodes(name) self
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__c_code__simplify_statement_13, 0);
  // 482: :
  // 483:   $name behind(source_of(self) .before. '(' alt(' ' '*') -1)
  // 484:   push &actions: !defined_functions(name) true
  frame->slots[4] /* temp__4 */ = create_closure(entry__compiler__c_code__simplify_statement_19, 0);
  // 472: case kind_of(self)
  // 473:   "struct"
  // 474:   :
  // 475:     $name name_of(identifier_of(self))
  // 476:     push &actions: !defined_structs(name) true
  // 477:   "node"
  // 478:   :
  // 479:     $name name_of(identifier_of(self))
  // 480:     push &actions: !defined_nodes(name) self
  // 481:   "function"
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
  // 475: ... identifier_of(self)
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
  // 475: $name name_of(identifier_of(self))
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
  // 476: ... : !defined_structs(name) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__c_code__simplify_statement_10, 0);
  // 476: push &actions: !defined_structs(name) true
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
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 476: ... !defined_structs(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__true();
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
  // 479: ... identifier_of(self)
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
  // 479: $name name_of(identifier_of(self))
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
  // 480: ... : !defined_nodes(name) self
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__c_code__simplify_statement_16, 0);
  // 480: push &actions: !defined_nodes(name) self
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
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // name: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 480: ... !defined_nodes(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* self */;
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
  // 483: ... source_of(self)
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
  // 483: ... source_of(self) .before. '('
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
  // 483: ... alt(' ' '*')
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
  // 483: ... 1
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
  // 483: $name behind(source_of(self) .before. '(' alt(' ' '*') -1)
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
  // 484: ... : !defined_functions(name) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__c_code__simplify_statement_25, 0);
  // 484: push &actions: !defined_functions(name) true
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
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 484: ... !defined_functions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__true();
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
  // 485: push &definitions self
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
  // 491: show_compiler_debug_info "simplify C-body"
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
  // 492: push &actions: !use_inline_c true
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
  // 492: ... !use_inline_c true
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
  var._simplify_input_arguments = collect_node(var._simplify_input_arguments);
  var._simplify_output_arguments = collect_node(var._simplify_output_arguments);
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
  number__2 = from_uint32(2U);
  character__42 = from_uchar32(42);
  define_polymorphic_function("compiler", "simplify_statement", get__compiler__simplify_statement, &poly_idx__compiler__simplify_statement, &var.compiler__simplify_statement);
  define_polymorphic_function("compiler", "simplify_expression", get__compiler__simplify_expression, &poly_idx__compiler__simplify_expression, &var.compiler__simplify_expression);
  string__421f524a80420288 = from_latin_1_string("temp__", 6);
  func__temporary_identifier_1 = create_function(entry__temporary_identifier_1, 0);
  func__simplify_input_arguments_2 = create_function(entry__simplify_input_arguments_2, 1);
  func__simplify_input_arguments_1 = create_function(entry__simplify_input_arguments_1, 1);
  func__simplify_output_arguments_1 = create_function(entry__simplify_output_arguments_1, 1);
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
  func__do_store_44 = create_function(entry__do_store_44, 0);
  func__do_store_45 = create_function(entry__do_store_45, 0);
  func__do_store_1 = create_function(entry__do_store_1, 5);
  func__store_result_1 = create_function(entry__store_result_1, -1);
  string__8629329e514f7a7a = from_latin_1_string("simplify statement", 18);
  func__compiler__call__simplify_statement_41 = create_function(entry__compiler__call__simplify_statement_41, 0);
  func__compiler__call__simplify_statement_108 = create_function(entry__compiler__call__simplify_statement_108, 1);
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
  var.compiler__check_usage = create_future();
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
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
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
  use_polymorphic_function(NULL, "is_a_destination", &get__is_a_destination, &poly_idx__is_a_destination);
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
  use_polymorphic_function(NULL, "is_an_input_output_argument", &get__is_an_input_output_argument, &poly_idx__is_an_input_output_argument);
  use_polymorphic_function(NULL, "is_an_optional_item", &get__is_an_optional_item, &poly_idx__is_an_optional_item);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_single_assign", &get__is_single_assign, &get_value_or_future__is_single_assign);
  use_read_only(NULL, "kind_of", &get__kind_of, &get_value_or_future__kind_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "might_be_constant", &get__might_be_constant, &get_value_or_future__might_be_constant);
  use_polymorphic_function(NULL, "name_of", &get__name_of, &poly_idx__name_of);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_read_only(NULL, "peek", &get__peek, &get_value_or_future__peek);
  use_read_only(NULL, "pop", &get__pop, &get_value_or_future__pop);
  use_read_only(NULL, "procedure_call", &get__procedure_call, &get_value_or_future__procedure_call);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "put", &get__put, &get_value_or_future__put);
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
  assign_variable(&var._simplify_input_arguments, &func__simplify_input_arguments_1);
  assign_variable(&var._simplify_output_arguments, &func__simplify_output_arguments_1);
  initialize_future(var.compiler__check_usage, func__compiler__check_usage_1);
  assign_variable(&var._do_store, &func__do_store_1);
  assign_variable(&var._store_result, &func__store_result_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__simplifier(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__simplifier);
}
