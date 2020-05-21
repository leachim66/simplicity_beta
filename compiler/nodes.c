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
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *empty_string;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_namespace(const char *namespace);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__NO_PARAMETER;
static NODE_GETTER get_value_or_future__NO_PARAMETER;
static NODE_GETTER get__STATIC_MULTI;
static NODE_GETTER get_value_or_future__STATIC_MULTI;
static NODE_GETTER get__STATIC_SINGLE;
static NODE_GETTER get_value_or_future__STATIC_SINGLE;
static int poly_idx__arguments_of;
static NODE_GETTER get__arguments_of;
static int poly_idx__attribute_kind_of;
static NODE_GETTER get__attribute_kind_of;
static int poly_idx__defined_names_of;
static NODE_GETTER get__defined_names_of;
static int poly_idx__defines_a_dynamic;
static NODE_GETTER get__defines_a_dynamic;
static int poly_idx__definitions_of;
static NODE_GETTER get__definitions_of;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__full_name_of;
static NODE_GETTER get__full_name_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__inherited_names_of;
static NODE_GETTER get__inherited_names_of;
static int poly_idx__is_a_backquoted_expression;
static NODE_GETTER get__is_a_backquoted_expression;
static int poly_idx__is_a_body;
static NODE_GETTER get__is_a_body;
static int poly_idx__is_a_c_body;
static NODE_GETTER get__is_a_c_body;
static int poly_idx__is_a_call;
static NODE_GETTER get__is_a_call;
static int poly_idx__is_a_character_literal;
static NODE_GETTER get__is_a_character_literal;
static int poly_idx__is_a_constant;
static NODE_GETTER get__is_a_constant;
static int poly_idx__is_a_definition;
static NODE_GETTER get__is_a_definition;
static int poly_idx__is_a_destination;
static NODE_GETTER get__is_a_destination;
static int poly_idx__is_a_dynamic_definition;
static NODE_GETTER get__is_a_dynamic_definition;
static int poly_idx__is_a_dynamic_multi_definition;
static NODE_GETTER get__is_a_dynamic_multi_definition;
static int poly_idx__is_a_dynamic_single_definition;
static NODE_GETTER get__is_a_dynamic_single_definition;
static int poly_idx__is_a_function_call;
static NODE_GETTER get__is_a_function_call;
static int poly_idx__is_a_meta_instruction;
static NODE_GETTER get__is_a_meta_instruction;
static int poly_idx__is_a_method_definition;
static NODE_GETTER get__is_a_method_definition;
static int poly_idx__is_a_multi_assign_definition;
static NODE_GETTER get__is_a_multi_assign_definition;
static int poly_idx__is_a_numeric_literal;
static NODE_GETTER get__is_a_numeric_literal;
static int poly_idx__is_a_polymorphic_function_constant;
static NODE_GETTER get__is_a_polymorphic_function_constant;
static int poly_idx__is_a_procedure_call;
static NODE_GETTER get__is_a_procedure_call;
static int poly_idx__is_a_remark;
static NODE_GETTER get__is_a_remark;
static int poly_idx__is_a_return;
static NODE_GETTER get__is_a_return;
static int poly_idx__is_a_setter;
static NODE_GETTER get__is_a_setter;
static int poly_idx__is_a_single_assign_definition;
static NODE_GETTER get__is_a_single_assign_definition;
static int poly_idx__is_a_static_definition;
static NODE_GETTER get__is_a_static_definition;
static int poly_idx__is_a_static_multi_definition;
static NODE_GETTER get__is_a_static_multi_definition;
static int poly_idx__is_a_static_single_definition;
static NODE_GETTER get__is_a_static_single_definition;
static int poly_idx__is_a_string_literal;
static NODE_GETTER get__is_a_string_literal;
static int poly_idx__is_a_string_template;
static NODE_GETTER get__is_a_string_template;
static int poly_idx__is_a_temporary;
static NODE_GETTER get__is_a_temporary;
static int poly_idx__is_a_unique_item_constant;
static NODE_GETTER get__is_a_unique_item_constant;
static int poly_idx__is_an_assignment;
static NODE_GETTER get__is_an_assignment;
static int poly_idx__is_an_attribute_access;
static NODE_GETTER get__is_an_attribute_access;
static int poly_idx__is_an_attribute_function_pair;
static NODE_GETTER get__is_an_attribute_function_pair;
static int poly_idx__is_an_attribute_value_pair;
static NODE_GETTER get__is_an_attribute_value_pair;
static int poly_idx__is_an_expanded_item;
static NODE_GETTER get__is_an_expanded_item;
static int poly_idx__is_an_expression;
static NODE_GETTER get__is_an_expression;
static int poly_idx__is_an_identifier;
static NODE_GETTER get__is_an_identifier;
static int poly_idx__is_an_initialization;
static NODE_GETTER get__is_an_initialization;
static int poly_idx__is_an_input_output_argument;
static NODE_GETTER get__is_an_input_output_argument;
static int poly_idx__is_an_operator_symbol;
static NODE_GETTER get__is_an_operator_symbol;
static int poly_idx__is_an_optional_item;
static NODE_GETTER get__is_an_optional_item;
static int poly_idx__is_c_code;
static NODE_GETTER get__is_c_code;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static int poly_idx__is_in_infix_notation;
static NODE_GETTER get__is_in_infix_notation;
static int poly_idx__is_in_numeric_notation;
static NODE_GETTER get__is_in_numeric_notation;
static int poly_idx__is_not_used;
static NODE_GETTER get__is_not_used;
static int poly_idx__is_used_as_a_destination;
static NODE_GETTER get__is_used_as_a_destination;
static int poly_idx__is_used_as_a_polymorphic_function;
static NODE_GETTER get__is_used_as_a_polymorphic_function;
static int poly_idx__mangled_name_of;
static NODE_GETTER get__mangled_name_of;
static NODE_GETTER get__name_of;
static NODE_GETTER get_value_or_future__name_of;
static NODE_GETTER get__namespace_of;
static NODE_GETTER get_value_or_future__namespace_of;
static int poly_idx__operators_of;
static NODE_GETTER get__operators_of;
static int poly_idx__parameter_kind_of;
static NODE_GETTER get__parameter_kind_of;
static int poly_idx__parameters_of;
static NODE_GETTER get__parameters_of;
static int poly_idx__remark_lines_of;
static NODE_GETTER get__remark_lines_of;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static int poly_idx__scope_of;
static NODE_GETTER get__scope_of;
static int poly_idx__statements_of;
static NODE_GETTER get__statements_of;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__grammar_node;
static NODE_GETTER get_value_or_future__types__grammar_node;
static NODE_GETTER get__types__insert_order_table;
static NODE_GETTER get_value_or_future__types__insert_order_table;
static int poly_idx__used_names_of;
static NODE_GETTER get__used_names_of;
static int poly_idx__variable_kind_of;
static NODE_GETTER get__variable_kind_of;
static struct {
  NODE *compiler__NONE;
  NODE *compiler__ATTRIBUTE_KIND;
  NODE *compiler__METHOD_KIND;
  NODE *compiler__NO_PARAMETER;
  NODE *compiler__IN_PARAMETER;
  NODE *compiler__IN_OUT_PARAMETER;
  NODE *compiler__OUT_PARAMETER;
  NODE *compiler__MYSELF_PARAMETER;
  NODE *compiler__CONTINUATION_PARAMETER;
  NODE *compiler__LEFT;
  NODE *compiler__RIGHT;
  NODE *compiler__POLYMORPHIC;
  NODE *compiler__STATIC_SINGLE;
  NODE *compiler__STATIC_MULTI;
  NODE *compiler__DYNAMIC_SINGLE;
  NODE *compiler__DYNAMIC_MULTI;
  NODE *compiler__C_NODE;
  NODE *node__argument_of;
  NODE *node__arguments_of;
  NODE *node__attribute_kind_of;
  NODE *node__attribute_of;
  NODE *node__base_of;
  NODE *node__default_value_of;
  NODE *node__defined_names_of;
  NODE *node__definitions_of;
  NODE *node__destination_of;
  NODE *node__end_position_of;
  NODE *node__expression_of;
  NODE *node__filemask_of;
  NODE *node__filename_of;
  NODE *node__fragment_of;
  NODE *node__full_name_of;
  NODE *node__functor_of;
  NODE *node__identifier_of;
  NODE *node__inherited_names_of;
  NODE *node__is_a_constant;
  NODE *node__is_a_dynamic_definition;
  NODE *node__is_a_method_definition;
  NODE *node__is_a_multi_assign_definition;
  NODE *node__is_an_expanded_item;
  NODE *node__is_an_optional_item;
  NODE *node__is_a_setter;
  NODE *node__is_a_single_assign_definition;
  NODE *node__is_a_static_definition;
  NODE *node__is_a_string_template;
  NODE *node__is_an_attribute_access;
  NODE *node__is_an_initialization;
  NODE *node__is_in_infix_notation;
  NODE *node__is_in_numeric_notation;
  NODE *node__is_mutable;
  NODE *node__is_not_used;
  NODE *node__kind_of;
  NODE *node__last_line_end_specifier_of;
  NODE *node__line_end_specifier_of;
  NODE *node__lowest_precedence_of;
  NODE *node__mangled_name_of;
  NODE *node__max_length_of;
  NODE *node__message_of;
  NODE *node__name_of;
  NODE *node__namespace_of;
  NODE *node__namespace_alias_of;
  NODE *node__node_of;
  NODE *node__operators_of;
  NODE *node__parameter_kind_of;
  NODE *node__parameters_of;
  NODE *node__parent_of;
  NODE *node__result_count_of;
  NODE *node__continuation_of;
  NODE *node__source_position_of;
  NODE *node__temporary_count_of;
  NODE *node__remark_lines_of;
  NODE *node__scope_of;
  NODE *node__section_of;
  NODE *node__statements_of;
  NODE *node__submodule_no_of;
  NODE *node__text_of;
  NODE *node__type_of;
  NODE *node__used_names_of;
  NODE *node__value_of;
  NODE *node__variable_kind_of;
  NODE *node__is_a_meta_instruction;
  NODE *compiler__meta_instruction;
  NODE *compiler__require_instruction;
  NODE *compiler__namespace_instruction;
  NODE *compiler__using_instruction;
  NODE *compiler__include_instruction;
  NODE *compiler__link_instruction;
  NODE *compiler__data_instruction;
  NODE *node__is_a_remark;
  NODE *compiler__remark_statement;
  NODE *node__is_a_body;
  NODE *node__defines_a_dynamic;
  NODE *compiler__body;
  NODE *compiler__statement;
  NODE *node__is_a_call;
  NODE *compiler__call;
  NODE *node__is_a_procedure_call;
  NODE *compiler__procedure_call;
  NODE *node__is_a_return;
  NODE *compiler__return_statement;
  NODE *node__is_an_assignment;
  NODE *compiler__assignment;
  NODE *node__is_a_definition;
  NODE *node__is_a_destination;
  NODE *node__is_an_input_output_argument;
  NODE *compiler__definition;
  NODE *node__is_a_static_single_definition;
  NODE *compiler__define_static_single;
  NODE *node__is_a_static_multi_definition;
  NODE *compiler__define_static_multi;
  NODE *node__is_a_dynamic_single_definition;
  NODE *compiler__define_dynamic_single;
  NODE *node__is_a_dynamic_multi_definition;
  NODE *compiler__define_dynamic_multi;
  NODE *node__is_a_function_call;
  NODE *compiler__function_call;
  NODE *node__is_an_expression;
  NODE *compiler__expression;
  NODE *compiler__remark_argument;
  NODE *node__is_a_backquoted_expression;
  NODE *compiler__backquoted;
  NODE *node__is_an_attribute_value_pair;
  NODE *compiler__attribute_value_pair;
  NODE *node__is_an_attribute_function_pair;
  NODE *compiler__attribute_function_pair;
  NODE *node__is_a_numeric_literal;
  NODE *compiler__numeric_literal;
  NODE *node__is_a_character_literal;
  NODE *compiler__character_literal;
  NODE *node__is_a_string_literal;
  NODE *compiler__string_literal;
  NODE *compiler__multi_line_string;
  NODE *node__is_a_unique_item_constant;
  NODE *compiler__unique_item;
  NODE *node__is_a_polymorphic_function_constant;
  NODE *compiler__polymorphic_function;
  NODE *compiler__polymorphic_function_with_setter;
  NODE *node__is_an_identifier;
  NODE *node__is_used_as_a_polymorphic_function;
  NODE *node__is_used_as_a_destination;
  NODE *compiler__identifier;
  NODE *node__is_a_temporary;
  NODE *compiler__temporary;
  NODE *node__is_an_operator_symbol;
  NODE *compiler__operator_symbol;
  NODE *node__is_c_code;
  NODE *compiler__c_code;
  NODE *node__is_a_c_body;
  NODE *compiler__c_body;
  NODE *compiler__is_a_parameter;
} var;
static const char *var_names[] = {
};
static NODE *unique__compiler__NONE;
static NODE *get__compiler__NONE(void) {
  return var.compiler__NONE;
}
static NODE *unique__compiler__ATTRIBUTE_KIND;
static NODE *get__compiler__ATTRIBUTE_KIND(void) {
  return var.compiler__ATTRIBUTE_KIND;
}
static NODE *unique__compiler__METHOD_KIND;
static NODE *get__compiler__METHOD_KIND(void) {
  return var.compiler__METHOD_KIND;
}
static NODE *unique__compiler__NO_PARAMETER;
static NODE *get__compiler__NO_PARAMETER(void) {
  return var.compiler__NO_PARAMETER;
}
static NODE *unique__compiler__IN_PARAMETER;
static NODE *get__compiler__IN_PARAMETER(void) {
  return var.compiler__IN_PARAMETER;
}
static NODE *unique__compiler__IN_OUT_PARAMETER;
static NODE *get__compiler__IN_OUT_PARAMETER(void) {
  return var.compiler__IN_OUT_PARAMETER;
}
static NODE *unique__compiler__OUT_PARAMETER;
static NODE *get__compiler__OUT_PARAMETER(void) {
  return var.compiler__OUT_PARAMETER;
}
static NODE *unique__compiler__MYSELF_PARAMETER;
static NODE *get__compiler__MYSELF_PARAMETER(void) {
  return var.compiler__MYSELF_PARAMETER;
}
static NODE *unique__compiler__CONTINUATION_PARAMETER;
static NODE *get__compiler__CONTINUATION_PARAMETER(void) {
  return var.compiler__CONTINUATION_PARAMETER;
}
static NODE *unique__compiler__LEFT;
static NODE *get__compiler__LEFT(void) {
  return var.compiler__LEFT;
}
static NODE *unique__compiler__RIGHT;
static NODE *get__compiler__RIGHT(void) {
  return var.compiler__RIGHT;
}
static NODE *unique__compiler__POLYMORPHIC;
static NODE *get__compiler__POLYMORPHIC(void) {
  return var.compiler__POLYMORPHIC;
}
static NODE *unique__compiler__STATIC_SINGLE;
static NODE *get__compiler__STATIC_SINGLE(void) {
  return var.compiler__STATIC_SINGLE;
}
static NODE *unique__compiler__STATIC_MULTI;
static NODE *get__compiler__STATIC_MULTI(void) {
  return var.compiler__STATIC_MULTI;
}
static NODE *unique__compiler__DYNAMIC_SINGLE;
static NODE *get__compiler__DYNAMIC_SINGLE(void) {
  return var.compiler__DYNAMIC_SINGLE;
}
static NODE *unique__compiler__DYNAMIC_MULTI;
static NODE *get__compiler__DYNAMIC_MULTI(void) {
  return var.compiler__DYNAMIC_MULTI;
}
static NODE *unique__compiler__C_NODE;
static NODE *get__compiler__C_NODE(void) {
  return var.compiler__C_NODE;
}
static int poly_idx__node__argument_of;
static void type__node__argument_of(void);
static NODE *get__node__argument_of(void) {
  return var.node__argument_of;
}
static int poly_idx__node__arguments_of;
static void type__node__arguments_of(void);
static NODE *get__node__arguments_of(void) {
  return var.node__arguments_of;
}
static int poly_idx__node__attribute_kind_of;
static void type__node__attribute_kind_of(void);
static NODE *get__node__attribute_kind_of(void) {
  return var.node__attribute_kind_of;
}
static int poly_idx__node__attribute_of;
static void type__node__attribute_of(void);
static NODE *get__node__attribute_of(void) {
  return var.node__attribute_of;
}
static int poly_idx__node__base_of;
static void type__node__base_of(void);
static NODE *get__node__base_of(void) {
  return var.node__base_of;
}
static int poly_idx__node__default_value_of;
static void type__node__default_value_of(void);
static NODE *get__node__default_value_of(void) {
  return var.node__default_value_of;
}
static int poly_idx__node__defined_names_of;
static void type__node__defined_names_of(void);
static NODE *get__node__defined_names_of(void) {
  return var.node__defined_names_of;
}
static int poly_idx__node__definitions_of;
static void type__node__definitions_of(void);
static NODE *get__node__definitions_of(void) {
  return var.node__definitions_of;
}
static int poly_idx__node__destination_of;
static void type__node__destination_of(void);
static NODE *get__node__destination_of(void) {
  return var.node__destination_of;
}
static int poly_idx__node__end_position_of;
static void type__node__end_position_of(void);
static NODE *get__node__end_position_of(void) {
  return var.node__end_position_of;
}
static int poly_idx__node__expression_of;
static void type__node__expression_of(void);
static NODE *get__node__expression_of(void) {
  return var.node__expression_of;
}
static int poly_idx__node__filemask_of;
static void type__node__filemask_of(void);
static NODE *get__node__filemask_of(void) {
  return var.node__filemask_of;
}
static int poly_idx__node__filename_of;
static void type__node__filename_of(void);
static NODE *get__node__filename_of(void) {
  return var.node__filename_of;
}
static int poly_idx__node__fragment_of;
static void type__node__fragment_of(void);
static NODE *get__node__fragment_of(void) {
  return var.node__fragment_of;
}
static int poly_idx__node__full_name_of;
static void type__node__full_name_of(void);
static NODE *get__node__full_name_of(void) {
  return var.node__full_name_of;
}
static int poly_idx__node__functor_of;
static void type__node__functor_of(void);
static NODE *get__node__functor_of(void) {
  return var.node__functor_of;
}
static int poly_idx__node__identifier_of;
static void type__node__identifier_of(void);
static NODE *get__node__identifier_of(void) {
  return var.node__identifier_of;
}
static int poly_idx__node__inherited_names_of;
static void type__node__inherited_names_of(void);
static NODE *get__node__inherited_names_of(void) {
  return var.node__inherited_names_of;
}
static int poly_idx__node__is_a_constant;
static void type__node__is_a_constant(void);
static NODE *get__node__is_a_constant(void) {
  return var.node__is_a_constant;
}
static int poly_idx__node__is_a_dynamic_definition;
static void type__node__is_a_dynamic_definition(void);
static NODE *get__node__is_a_dynamic_definition(void) {
  return var.node__is_a_dynamic_definition;
}
static int poly_idx__node__is_a_method_definition;
static void type__node__is_a_method_definition(void);
static NODE *get__node__is_a_method_definition(void) {
  return var.node__is_a_method_definition;
}
static int poly_idx__node__is_a_multi_assign_definition;
static void type__node__is_a_multi_assign_definition(void);
static NODE *get__node__is_a_multi_assign_definition(void) {
  return var.node__is_a_multi_assign_definition;
}
static int poly_idx__node__is_an_expanded_item;
static void type__node__is_an_expanded_item(void);
static NODE *get__node__is_an_expanded_item(void) {
  return var.node__is_an_expanded_item;
}
static int poly_idx__node__is_an_optional_item;
static void type__node__is_an_optional_item(void);
static NODE *get__node__is_an_optional_item(void) {
  return var.node__is_an_optional_item;
}
static int poly_idx__node__is_a_setter;
static void type__node__is_a_setter(void);
static NODE *get__node__is_a_setter(void) {
  return var.node__is_a_setter;
}
static int poly_idx__node__is_a_single_assign_definition;
static void type__node__is_a_single_assign_definition(void);
static NODE *get__node__is_a_single_assign_definition(void) {
  return var.node__is_a_single_assign_definition;
}
static int poly_idx__node__is_a_static_definition;
static void type__node__is_a_static_definition(void);
static NODE *get__node__is_a_static_definition(void) {
  return var.node__is_a_static_definition;
}
static int poly_idx__node__is_a_string_template;
static void type__node__is_a_string_template(void);
static NODE *get__node__is_a_string_template(void) {
  return var.node__is_a_string_template;
}
static int poly_idx__node__is_an_attribute_access;
static void type__node__is_an_attribute_access(void);
static NODE *get__node__is_an_attribute_access(void) {
  return var.node__is_an_attribute_access;
}
static int poly_idx__node__is_an_initialization;
static void type__node__is_an_initialization(void);
static NODE *get__node__is_an_initialization(void) {
  return var.node__is_an_initialization;
}
static int poly_idx__node__is_in_infix_notation;
static void type__node__is_in_infix_notation(void);
static NODE *get__node__is_in_infix_notation(void) {
  return var.node__is_in_infix_notation;
}
static int poly_idx__node__is_in_numeric_notation;
static void type__node__is_in_numeric_notation(void);
static NODE *get__node__is_in_numeric_notation(void) {
  return var.node__is_in_numeric_notation;
}
static int poly_idx__node__is_mutable;
static void type__node__is_mutable(void);
static NODE *get__node__is_mutable(void) {
  return var.node__is_mutable;
}
static int poly_idx__node__is_not_used;
static void type__node__is_not_used(void);
static NODE *get__node__is_not_used(void) {
  return var.node__is_not_used;
}
static int poly_idx__node__kind_of;
static void type__node__kind_of(void);
static NODE *get__node__kind_of(void) {
  return var.node__kind_of;
}
static int poly_idx__node__last_line_end_specifier_of;
static void type__node__last_line_end_specifier_of(void);
static NODE *get__node__last_line_end_specifier_of(void) {
  return var.node__last_line_end_specifier_of;
}
static int poly_idx__node__line_end_specifier_of;
static void type__node__line_end_specifier_of(void);
static NODE *get__node__line_end_specifier_of(void) {
  return var.node__line_end_specifier_of;
}
static int poly_idx__node__lowest_precedence_of;
static void type__node__lowest_precedence_of(void);
static NODE *get__node__lowest_precedence_of(void) {
  return var.node__lowest_precedence_of;
}
static int poly_idx__node__mangled_name_of;
static void type__node__mangled_name_of(void);
static NODE *get__node__mangled_name_of(void) {
  return var.node__mangled_name_of;
}
static int poly_idx__node__max_length_of;
static void type__node__max_length_of(void);
static NODE *get__node__max_length_of(void) {
  return var.node__max_length_of;
}
static int poly_idx__node__message_of;
static void type__node__message_of(void);
static NODE *get__node__message_of(void) {
  return var.node__message_of;
}
static int poly_idx__node__name_of;
static void type__node__name_of(void);
static NODE *get__node__name_of(void) {
  return var.node__name_of;
}
static int poly_idx__node__namespace_of;
static void type__node__namespace_of(void);
static NODE *get__node__namespace_of(void) {
  return var.node__namespace_of;
}
static int poly_idx__node__namespace_alias_of;
static void type__node__namespace_alias_of(void);
static NODE *get__node__namespace_alias_of(void) {
  return var.node__namespace_alias_of;
}
static int poly_idx__node__node_of;
static void type__node__node_of(void);
static NODE *get__node__node_of(void) {
  return var.node__node_of;
}
static int poly_idx__node__operators_of;
static void type__node__operators_of(void);
static NODE *get__node__operators_of(void) {
  return var.node__operators_of;
}
static int poly_idx__node__parameter_kind_of;
static void type__node__parameter_kind_of(void);
static NODE *get__node__parameter_kind_of(void) {
  return var.node__parameter_kind_of;
}
static int poly_idx__node__parameters_of;
static void type__node__parameters_of(void);
static NODE *get__node__parameters_of(void) {
  return var.node__parameters_of;
}
static int poly_idx__node__parent_of;
static void type__node__parent_of(void);
static NODE *get__node__parent_of(void) {
  return var.node__parent_of;
}
static int poly_idx__node__result_count_of;
static void type__node__result_count_of(void);
static NODE *get__node__result_count_of(void) {
  return var.node__result_count_of;
}
static int poly_idx__node__continuation_of;
static void type__node__continuation_of(void);
static NODE *get__node__continuation_of(void) {
  return var.node__continuation_of;
}
static int poly_idx__node__source_position_of;
static void type__node__source_position_of(void);
static NODE *get__node__source_position_of(void) {
  return var.node__source_position_of;
}
static int poly_idx__node__temporary_count_of;
static void type__node__temporary_count_of(void);
static NODE *get__node__temporary_count_of(void) {
  return var.node__temporary_count_of;
}
static int poly_idx__node__remark_lines_of;
static void type__node__remark_lines_of(void);
static NODE *get__node__remark_lines_of(void) {
  return var.node__remark_lines_of;
}
static int poly_idx__node__scope_of;
static void type__node__scope_of(void);
static NODE *get__node__scope_of(void) {
  return var.node__scope_of;
}
static int poly_idx__node__section_of;
static void type__node__section_of(void);
static NODE *get__node__section_of(void) {
  return var.node__section_of;
}
static int poly_idx__node__statements_of;
static void type__node__statements_of(void);
static NODE *get__node__statements_of(void) {
  return var.node__statements_of;
}
static int poly_idx__node__submodule_no_of;
static void type__node__submodule_no_of(void);
static NODE *get__node__submodule_no_of(void) {
  return var.node__submodule_no_of;
}
static int poly_idx__node__text_of;
static void type__node__text_of(void);
static NODE *get__node__text_of(void) {
  return var.node__text_of;
}
static int poly_idx__node__type_of;
static void type__node__type_of(void);
static NODE *get__node__type_of(void) {
  return var.node__type_of;
}
static int poly_idx__node__used_names_of;
static void type__node__used_names_of(void);
static NODE *get__node__used_names_of(void) {
  return var.node__used_names_of;
}
static int poly_idx__node__value_of;
static void type__node__value_of(void);
static NODE *get__node__value_of(void) {
  return var.node__value_of;
}
static int poly_idx__node__variable_kind_of;
static void type__node__variable_kind_of(void);
static NODE *get__node__variable_kind_of(void) {
  return var.node__variable_kind_of;
}
static int poly_idx__node__is_a_meta_instruction;
static void type__node__is_a_meta_instruction(void);
static NODE *get__node__is_a_meta_instruction(void) {
  return var.node__is_a_meta_instruction;
}
static NODE *get__compiler__meta_instruction(void) {
  return var.compiler__meta_instruction;
}
static NODE *get__compiler__require_instruction(void) {
  return var.compiler__require_instruction;
}
static NODE *get__compiler__namespace_instruction(void) {
  return var.compiler__namespace_instruction;
}
static NODE *get__compiler__using_instruction(void) {
  return var.compiler__using_instruction;
}
static NODE *get__compiler__include_instruction(void) {
  return var.compiler__include_instruction;
}
static NODE *get__compiler__link_instruction(void) {
  return var.compiler__link_instruction;
}
static NODE *get__compiler__data_instruction(void) {
  return var.compiler__data_instruction;
}
static int poly_idx__node__is_a_remark;
static void type__node__is_a_remark(void);
static NODE *get__node__is_a_remark(void) {
  return var.node__is_a_remark;
}
static NODE *get__compiler__remark_statement(void) {
  return var.compiler__remark_statement;
}
static int poly_idx__node__is_a_body;
static void type__node__is_a_body(void);
static NODE *get__node__is_a_body(void) {
  return var.node__is_a_body;
}
static int poly_idx__node__defines_a_dynamic;
static void type__node__defines_a_dynamic(void);
static NODE *get__node__defines_a_dynamic(void) {
  return var.node__defines_a_dynamic;
}
static NODE *get__compiler__body(void) {
  return var.compiler__body;
}
static NODE *get__compiler__statement(void) {
  return var.compiler__statement;
}
static int poly_idx__node__is_a_call;
static void type__node__is_a_call(void);
static NODE *get__node__is_a_call(void) {
  return var.node__is_a_call;
}
static NODE *get__compiler__call(void) {
  return var.compiler__call;
}
static int poly_idx__node__is_a_procedure_call;
static void type__node__is_a_procedure_call(void);
static NODE *get__node__is_a_procedure_call(void) {
  return var.node__is_a_procedure_call;
}
static NODE *get__compiler__procedure_call(void) {
  return var.compiler__procedure_call;
}
static int poly_idx__node__is_a_return;
static void type__node__is_a_return(void);
static NODE *get__node__is_a_return(void) {
  return var.node__is_a_return;
}
static NODE *get__compiler__return_statement(void) {
  return var.compiler__return_statement;
}
static int poly_idx__node__is_an_assignment;
static void type__node__is_an_assignment(void);
static NODE *get__node__is_an_assignment(void) {
  return var.node__is_an_assignment;
}
static NODE *get__compiler__assignment(void) {
  return var.compiler__assignment;
}
static int poly_idx__node__is_a_definition;
static void type__node__is_a_definition(void);
static NODE *get__node__is_a_definition(void) {
  return var.node__is_a_definition;
}
static int poly_idx__node__is_a_destination;
static void type__node__is_a_destination(void);
static NODE *get__node__is_a_destination(void) {
  return var.node__is_a_destination;
}
static int poly_idx__node__is_an_input_output_argument;
static void type__node__is_an_input_output_argument(void);
static NODE *get__node__is_an_input_output_argument(void) {
  return var.node__is_an_input_output_argument;
}
static NODE *get__compiler__definition(void) {
  return var.compiler__definition;
}
static int poly_idx__node__is_a_static_single_definition;
static void type__node__is_a_static_single_definition(void);
static NODE *get__node__is_a_static_single_definition(void) {
  return var.node__is_a_static_single_definition;
}
static NODE *get__compiler__define_static_single(void) {
  return var.compiler__define_static_single;
}
static int poly_idx__node__is_a_static_multi_definition;
static void type__node__is_a_static_multi_definition(void);
static NODE *get__node__is_a_static_multi_definition(void) {
  return var.node__is_a_static_multi_definition;
}
static NODE *get__compiler__define_static_multi(void) {
  return var.compiler__define_static_multi;
}
static int poly_idx__node__is_a_dynamic_single_definition;
static void type__node__is_a_dynamic_single_definition(void);
static NODE *get__node__is_a_dynamic_single_definition(void) {
  return var.node__is_a_dynamic_single_definition;
}
static NODE *get__compiler__define_dynamic_single(void) {
  return var.compiler__define_dynamic_single;
}
static int poly_idx__node__is_a_dynamic_multi_definition;
static void type__node__is_a_dynamic_multi_definition(void);
static NODE *get__node__is_a_dynamic_multi_definition(void) {
  return var.node__is_a_dynamic_multi_definition;
}
static NODE *get__compiler__define_dynamic_multi(void) {
  return var.compiler__define_dynamic_multi;
}
static int poly_idx__node__is_a_function_call;
static void type__node__is_a_function_call(void);
static NODE *get__node__is_a_function_call(void) {
  return var.node__is_a_function_call;
}
static NODE *get__compiler__function_call(void) {
  return var.compiler__function_call;
}
static int poly_idx__node__is_an_expression;
static void type__node__is_an_expression(void);
static NODE *get__node__is_an_expression(void) {
  return var.node__is_an_expression;
}
static NODE *get__compiler__expression(void) {
  return var.compiler__expression;
}
static NODE *get__compiler__remark_argument(void) {
  return var.compiler__remark_argument;
}
static int poly_idx__node__is_a_backquoted_expression;
static void type__node__is_a_backquoted_expression(void);
static NODE *get__node__is_a_backquoted_expression(void) {
  return var.node__is_a_backquoted_expression;
}
static NODE *get__compiler__backquoted(void) {
  return var.compiler__backquoted;
}
static int poly_idx__node__is_an_attribute_value_pair;
static void type__node__is_an_attribute_value_pair(void);
static NODE *get__node__is_an_attribute_value_pair(void) {
  return var.node__is_an_attribute_value_pair;
}
static NODE *get__compiler__attribute_value_pair(void) {
  return var.compiler__attribute_value_pair;
}
static int poly_idx__node__is_an_attribute_function_pair;
static void type__node__is_an_attribute_function_pair(void);
static NODE *get__node__is_an_attribute_function_pair(void) {
  return var.node__is_an_attribute_function_pair;
}
static NODE *get__compiler__attribute_function_pair(void) {
  return var.compiler__attribute_function_pair;
}
static int poly_idx__node__is_a_numeric_literal;
static void type__node__is_a_numeric_literal(void);
static NODE *get__node__is_a_numeric_literal(void) {
  return var.node__is_a_numeric_literal;
}
static NODE *get__compiler__numeric_literal(void) {
  return var.compiler__numeric_literal;
}
static NODE *func__compiler__numeric_literal__mangled_name_of_1;
static void entry__compiler__numeric_literal__mangled_name_of_1(void);
static FRAME_INFO frame__compiler__numeric_literal__mangled_name_of_1 = {1, {"self"}};
static void cont__compiler__numeric_literal__mangled_name_of_2(void);
static NODE *string__578a5af303e9cbe;
static void cont__compiler__numeric_literal__mangled_name_of_4(void);
static void cont__compiler__numeric_literal__mangled_name_of_5(void);
static void cont__compiler__numeric_literal__mangled_name_of_6(void);
static int poly_idx__node__is_a_character_literal;
static void type__node__is_a_character_literal(void);
static NODE *get__node__is_a_character_literal(void) {
  return var.node__is_a_character_literal;
}
static NODE *get__compiler__character_literal(void) {
  return var.compiler__character_literal;
}
static int poly_idx__node__is_a_string_literal;
static void type__node__is_a_string_literal(void);
static NODE *get__node__is_a_string_literal(void) {
  return var.node__is_a_string_literal;
}
static NODE *get__compiler__string_literal(void) {
  return var.compiler__string_literal;
}
static NODE *get__compiler__multi_line_string(void) {
  return var.compiler__multi_line_string;
}
static NODE *string__578a5af303e9ceb;
static int poly_idx__node__is_a_unique_item_constant;
static void type__node__is_a_unique_item_constant(void);
static NODE *get__node__is_a_unique_item_constant(void) {
  return var.node__is_a_unique_item_constant;
}
static NODE *get__compiler__unique_item(void) {
  return var.compiler__unique_item;
}
static int poly_idx__node__is_a_polymorphic_function_constant;
static void type__node__is_a_polymorphic_function_constant(void);
static NODE *get__node__is_a_polymorphic_function_constant(void) {
  return var.node__is_a_polymorphic_function_constant;
}
static NODE *get__compiler__polymorphic_function(void) {
  return var.compiler__polymorphic_function;
}
static NODE *get__compiler__polymorphic_function_with_setter(void) {
  return var.compiler__polymorphic_function_with_setter;
}
static int poly_idx__node__is_an_identifier;
static void type__node__is_an_identifier(void);
static NODE *get__node__is_an_identifier(void) {
  return var.node__is_an_identifier;
}
static int poly_idx__node__is_used_as_a_polymorphic_function;
static void type__node__is_used_as_a_polymorphic_function(void);
static NODE *get__node__is_used_as_a_polymorphic_function(void) {
  return var.node__is_used_as_a_polymorphic_function;
}
static int poly_idx__node__is_used_as_a_destination;
static void type__node__is_used_as_a_destination(void);
static NODE *get__node__is_used_as_a_destination(void) {
  return var.node__is_used_as_a_destination;
}
static NODE *get__compiler__identifier(void) {
  return var.compiler__identifier;
}
static NODE *func__compiler__identifier__full_name_of_1;
static void entry__compiler__identifier__full_name_of_1(void);
static FRAME_INFO frame__compiler__identifier__full_name_of_1 = {1, {"self"}};
static void cont__compiler__identifier__full_name_of_2(void);
static void cont__compiler__identifier__full_name_of_3(void);
static NODE *func__compiler__identifier__full_name_of_4;
static void entry__compiler__identifier__full_name_of_4(void);
static FRAME_INFO frame__compiler__identifier__full_name_of_4 = {1, {"self"}};
static void cont__compiler__identifier__full_name_of_5(void);
static NODE *string__2d7981f4e6d82bff;
static void cont__compiler__identifier__full_name_of_7(void);
static NODE *func__compiler__identifier__full_name_of_8;
static void entry__compiler__identifier__full_name_of_8(void);
static FRAME_INFO frame__compiler__identifier__full_name_of_8 = {0, {}};
static void cont__compiler__identifier__full_name_of_9(void);
static void cont__compiler__identifier__full_name_of_10(void);
static void cont__compiler__identifier__full_name_of_11(void);
static NODE *func__compiler__identifier__mangled_name_of_1;
static void entry__compiler__identifier__mangled_name_of_1(void);
static FRAME_INFO frame__compiler__identifier__mangled_name_of_1 = {1, {"self"}};
static void cont__compiler__identifier__mangled_name_of_2(void);
static void cont__compiler__identifier__mangled_name_of_3(void);
static NODE *func__compiler__identifier__mangled_name_of_4;
static void entry__compiler__identifier__mangled_name_of_4(void);
static FRAME_INFO frame__compiler__identifier__mangled_name_of_4 = {1, {"self"}};
static void cont__compiler__identifier__mangled_name_of_5(void);
static NODE *string__2d7981f4e5f02b9a;
static void cont__compiler__identifier__mangled_name_of_7(void);
static NODE *func__compiler__identifier__mangled_name_of_8;
static void entry__compiler__identifier__mangled_name_of_8(void);
static FRAME_INFO frame__compiler__identifier__mangled_name_of_8 = {0, {}};
static void cont__compiler__identifier__mangled_name_of_9(void);
static void cont__compiler__identifier__mangled_name_of_10(void);
static void cont__compiler__identifier__mangled_name_of_11(void);
static int poly_idx__node__is_a_temporary;
static void type__node__is_a_temporary(void);
static NODE *get__node__is_a_temporary(void) {
  return var.node__is_a_temporary;
}
static NODE *get__compiler__temporary(void) {
  return var.compiler__temporary;
}
static int poly_idx__node__is_an_operator_symbol;
static void type__node__is_an_operator_symbol(void);
static NODE *get__node__is_an_operator_symbol(void) {
  return var.node__is_an_operator_symbol;
}
static NODE *get__compiler__operator_symbol(void) {
  return var.compiler__operator_symbol;
}
static int poly_idx__node__is_c_code;
static void type__node__is_c_code(void);
static NODE *get__node__is_c_code(void) {
  return var.node__is_c_code;
}
static NODE *get__compiler__c_code(void) {
  return var.compiler__c_code;
}
static NODE *string__545aebc3eac0d03b;
static int poly_idx__node__is_a_c_body;
static void type__node__is_a_c_body(void);
static NODE *get__node__is_a_c_body(void) {
  return var.node__is_a_c_body;
}
static NODE *get__compiler__c_body(void) {
  return var.compiler__c_body;
}
static NODE *func__compiler__is_a_parameter_1;
static void entry__compiler__is_a_parameter_1(void);
static FRAME_INFO frame__compiler__is_a_parameter_1 = {1, {"self"}};
static void cont__compiler__is_a_parameter_2(void);
static void cont__compiler__is_a_parameter_3(void);
static void cont__compiler__is_a_parameter_4(void);
static NODE *get__compiler__is_a_parameter(void) {
  return var.compiler__is_a_parameter;
}
void run__nodes(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__node__argument_of, NULL, 58, 58, 2, 18},
  {type__node__arguments_of, NULL, 59, 59, 2, 19},
  {type__node__attribute_kind_of, NULL, 60, 60, 2, 24},
  {type__node__attribute_of, NULL, 61, 61, 2, 19},
  {type__node__base_of, NULL, 62, 62, 2, 14},
  {type__node__default_value_of, NULL, 63, 63, 2, 23},
  {type__node__defined_names_of, NULL, 64, 64, 2, 23},
  {type__node__definitions_of, NULL, 65, 65, 2, 21},
  {type__node__destination_of, NULL, 66, 66, 2, 21},
  {type__node__end_position_of, NULL, 67, 67, 2, 22},
  {type__node__expression_of, NULL, 68, 68, 2, 20},
  {type__node__filemask_of, NULL, 69, 69, 2, 18},
  {type__node__filename_of, NULL, 70, 70, 2, 18},
  {type__node__fragment_of, NULL, 71, 71, 2, 18},
  {type__node__full_name_of, NULL, 72, 72, 2, 19},
  {type__node__functor_of, NULL, 73, 73, 2, 17},
  {type__node__identifier_of, NULL, 74, 74, 2, 20},
  {type__node__inherited_names_of, NULL, 75, 75, 2, 25},
  {type__node__is_a_constant, NULL, 76, 76, 2, 20},
  {type__node__is_a_dynamic_definition, NULL, 77, 77, 2, 30},
  {type__node__is_a_method_definition, NULL, 78, 78, 2, 29},
  {type__node__is_a_multi_assign_definition, NULL, 79, 79, 2, 35},
  {type__node__is_an_expanded_item, NULL, 80, 80, 2, 26},
  {type__node__is_an_optional_item, NULL, 81, 81, 2, 26},
  {type__node__is_a_setter, NULL, 82, 82, 2, 18},
  {type__node__is_a_single_assign_definition, NULL, 83, 83, 2, 36},
  {type__node__is_a_static_definition, NULL, 84, 84, 2, 29},
  {type__node__is_a_string_template, NULL, 85, 85, 2, 27},
  {type__node__is_an_attribute_access, NULL, 86, 86, 2, 29},
  {type__node__is_an_initialization, NULL, 87, 87, 2, 27},
  {type__node__is_in_infix_notation, NULL, 88, 88, 2, 27},
  {type__node__is_in_numeric_notation, NULL, 89, 89, 2, 29},
  {type__node__is_mutable, NULL, 90, 90, 2, 17},
  {type__node__is_not_used, NULL, 91, 91, 2, 18},
  {type__node__kind_of, NULL, 92, 92, 2, 14},
  {type__node__last_line_end_specifier_of, NULL, 93, 93, 2, 33},
  {type__node__line_end_specifier_of, NULL, 94, 94, 2, 28},
  {type__node__lowest_precedence_of, NULL, 95, 95, 2, 27},
  {type__node__mangled_name_of, NULL, 96, 96, 2, 22},
  {type__node__max_length_of, NULL, 97, 97, 2, 20},
  {type__node__message_of, NULL, 98, 98, 2, 17},
  {type__node__name_of, NULL, 99, 99, 2, 14},
  {type__node__namespace_of, NULL, 100, 100, 2, 19},
  {type__node__namespace_alias_of, NULL, 101, 101, 2, 25},
  {type__node__node_of, NULL, 102, 102, 2, 14},
  {type__node__operators_of, NULL, 103, 103, 2, 19},
  {type__node__parameter_kind_of, NULL, 104, 104, 2, 24},
  {type__node__parameters_of, NULL, 105, 105, 2, 20},
  {type__node__parent_of, NULL, 106, 106, 2, 16},
  {type__node__result_count_of, NULL, 107, 107, 2, 22},
  {type__node__continuation_of, NULL, 108, 108, 2, 22},
  {type__node__source_position_of, NULL, 109, 109, 2, 25},
  {type__node__temporary_count_of, NULL, 110, 110, 2, 25},
  {type__node__remark_lines_of, NULL, 111, 111, 2, 22},
  {type__node__scope_of, NULL, 112, 112, 2, 15},
  {type__node__section_of, NULL, 113, 113, 2, 17},
  {type__node__statements_of, NULL, 114, 114, 2, 20},
  {type__node__submodule_no_of, NULL, 115, 115, 2, 22},
  {type__node__text_of, NULL, 116, 116, 2, 14},
  {type__node__type_of, NULL, 117, 117, 2, 14},
  {type__node__used_names_of, NULL, 118, 118, 2, 20},
  {type__node__value_of, NULL, 119, 119, 2, 15},
  {type__node__variable_kind_of, NULL, 120, 120, 2, 23},
  {type__node__is_a_meta_instruction, NULL, 141, 141, 2, 28},
  {type__node__is_a_remark, NULL, 180, 180, 2, 18},
  {type__node__is_a_body, NULL, 189, 189, 2, 16},
  {type__node__defines_a_dynamic, NULL, 194, 194, 2, 24},
  {type__node__is_a_call, NULL, 215, 215, 2, 16},
  {type__node__is_a_procedure_call, NULL, 225, 225, 2, 26},
  {type__node__is_a_return, NULL, 234, 234, 2, 18},
  {type__node__is_an_assignment, NULL, 243, 243, 2, 23},
  {type__node__is_a_definition, NULL, 252, 252, 2, 22},
  {type__node__is_a_destination, NULL, 253, 253, 2, 23},
  {type__node__is_an_input_output_argument, NULL, 254, 254, 2, 34},
  {type__node__is_a_static_single_definition, NULL, 268, 268, 2, 36},
  {type__node__is_a_static_multi_definition, NULL, 280, 280, 2, 35},
  {type__node__is_a_dynamic_single_definition, NULL, 292, 292, 2, 37},
  {type__node__is_a_dynamic_multi_definition, NULL, 304, 304, 2, 36},
  {type__node__is_a_function_call, NULL, 316, 316, 2, 25},
  {type__node__is_an_expression, NULL, 331, 331, 2, 23},
  {type__node__is_a_backquoted_expression, NULL, 348, 348, 2, 33},
  {type__node__is_an_attribute_value_pair, NULL, 357, 357, 2, 33},
  {type__node__is_an_attribute_function_pair, NULL, 367, 367, 2, 36},
  {type__node__is_a_numeric_literal, NULL, 376, 376, 2, 27},
  {type__node__is_a_character_literal, NULL, 389, 389, 2, 29},
  {type__node__is_a_string_literal, NULL, 400, 400, 2, 26},
  {type__node__is_a_unique_item_constant, NULL, 419, 419, 2, 32},
  {type__node__is_a_polymorphic_function_constant, NULL, 429, 429, 2, 41},
  {type__node__is_an_identifier, NULL, 446, 446, 2, 23},
  {type__node__is_used_as_a_polymorphic_function, NULL, 451, 451, 2, 40},
  {type__node__is_used_as_a_destination, NULL, 452, 452, 2, 31},
  {type__node__is_a_temporary, NULL, 480, 480, 2, 21},
  {type__node__is_an_operator_symbol, NULL, 489, 489, 2, 28},
  {type__node__is_c_code, NULL, 498, 498, 2, 16},
  {type__node__is_a_c_body, NULL, 509, 509, 2, 18},
  {run__nodes, NULL, 502, 502, 1, 37},
  {entry__compiler__numeric_literal__mangled_name_of_1, NULL, 384, 384, 18, 37},
  {cont__compiler__numeric_literal__mangled_name_of_2, &frame__compiler__numeric_literal__mangled_name_of_1, 384, 384, 39, 47},
  {cont__compiler__numeric_literal__mangled_name_of_4, &frame__compiler__numeric_literal__mangled_name_of_1, 384, 384, 49, 61},
  {cont__compiler__numeric_literal__mangled_name_of_5, &frame__compiler__numeric_literal__mangled_name_of_1, 384, 384, 6, 62},
  {cont__compiler__numeric_literal__mangled_name_of_6, &frame__compiler__numeric_literal__mangled_name_of_1, 384, 384, 3, 62},
  {entry__compiler__identifier__full_name_of_4, NULL, 464, 464, 19, 36},
  {cont__compiler__identifier__full_name_of_5, &frame__compiler__identifier__full_name_of_4, 464, 464, 12, 42},
  {cont__compiler__identifier__full_name_of_7, &frame__compiler__identifier__full_name_of_4, 464, 464, 9, 42},
  {entry__compiler__identifier__full_name_of_8, NULL, 465, 465, 9, 13},
  {entry__compiler__identifier__full_name_of_1, NULL, 463, 463, 9, 26},
  {cont__compiler__identifier__full_name_of_2, &frame__compiler__identifier__full_name_of_1, 463, 463, 9, 37},
  {cont__compiler__identifier__full_name_of_3, &frame__compiler__identifier__full_name_of_1, 464, 464, 9, 42},
  {cont__compiler__identifier__full_name_of_9, &frame__compiler__identifier__full_name_of_1, 466, 466, 7, 19},
  {cont__compiler__identifier__full_name_of_10, &frame__compiler__identifier__full_name_of_1, },
  {cont__compiler__identifier__full_name_of_11, &frame__compiler__identifier__full_name_of_1, 460, 466, 3, 20},
  {entry__compiler__identifier__mangled_name_of_4, NULL, 473, 473, 19, 36},
  {cont__compiler__identifier__mangled_name_of_5, &frame__compiler__identifier__mangled_name_of_4, 473, 473, 12, 42},
  {cont__compiler__identifier__mangled_name_of_7, &frame__compiler__identifier__mangled_name_of_4, 473, 473, 9, 42},
  {entry__compiler__identifier__mangled_name_of_8, NULL, 474, 474, 9, 13},
  {entry__compiler__identifier__mangled_name_of_1, NULL, 472, 472, 9, 26},
  {cont__compiler__identifier__mangled_name_of_2, &frame__compiler__identifier__mangled_name_of_1, 472, 472, 9, 37},
  {cont__compiler__identifier__mangled_name_of_3, &frame__compiler__identifier__mangled_name_of_1, 473, 473, 9, 42},
  {cont__compiler__identifier__mangled_name_of_9, &frame__compiler__identifier__mangled_name_of_1, 475, 475, 7, 19},
  {cont__compiler__identifier__mangled_name_of_10, &frame__compiler__identifier__mangled_name_of_1, },
  {cont__compiler__identifier__mangled_name_of_11, &frame__compiler__identifier__mangled_name_of_1, 469, 475, 3, 20},
  {entry__compiler__is_a_parameter_1, NULL, 519, 519, 38, 60},
  {cont__compiler__is_a_parameter_2, &frame__compiler__is_a_parameter_1, 519, 519, 38, 76},
  {cont__compiler__is_a_parameter_3, &frame__compiler__is_a_parameter_1, 519, 519, 38, 76},
  {cont__compiler__is_a_parameter_4, &frame__compiler__is_a_parameter_1, 519, 519, 35, 76}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__node__argument_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__argument_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__argument_of, attr);
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
static void type__node__arguments_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__arguments_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__arguments_of, attr);
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
static void type__node__attribute_kind_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__attribute_kind_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__attribute_kind_of, attr);
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
static void type__node__attribute_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__attribute_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__attribute_of, attr);
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
static void type__node__base_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__base_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__base_of, attr);
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
static void type__node__default_value_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__default_value_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__default_value_of, attr);
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
static void type__node__defined_names_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__defined_names_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__defined_names_of, attr);
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
static void type__node__definitions_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__definitions_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__definitions_of, attr);
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
static void type__node__destination_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__destination_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__destination_of, attr);
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
static void type__node__end_position_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__end_position_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__end_position_of, attr);
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
static void type__node__expression_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__expression_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__expression_of, attr);
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
static void type__node__filemask_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__filemask_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__filemask_of, attr);
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
static void type__node__filename_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__filename_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__filename_of, attr);
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
static void type__node__fragment_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__fragment_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__fragment_of, attr);
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
static void type__node__full_name_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__full_name_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__full_name_of, attr);
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
static void type__node__functor_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__functor_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__functor_of, attr);
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
static void type__node__identifier_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__identifier_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__identifier_of, attr);
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
static void type__node__inherited_names_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__inherited_names_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__inherited_names_of, attr);
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
static void type__node__is_a_constant(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_constant);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_constant, attr);
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
static void type__node__is_a_dynamic_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_dynamic_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_dynamic_definition, attr);
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
static void type__node__is_a_method_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_method_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_method_definition, attr);
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
static void type__node__is_a_multi_assign_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_multi_assign_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_multi_assign_definition, attr);
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
static void type__node__is_an_expanded_item(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_expanded_item);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_expanded_item, attr);
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
static void type__node__is_an_optional_item(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_optional_item);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_optional_item, attr);
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
static void type__node__is_a_setter(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_setter);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_setter, attr);
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
static void type__node__is_a_single_assign_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_single_assign_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_single_assign_definition, attr);
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
static void type__node__is_a_static_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_static_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_static_definition, attr);
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
static void type__node__is_a_string_template(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_string_template);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_string_template, attr);
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
static void type__node__is_an_attribute_access(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_attribute_access);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_attribute_access, attr);
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
static void type__node__is_an_initialization(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_initialization);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_initialization, attr);
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
static void type__node__is_in_infix_notation(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_in_infix_notation);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_in_infix_notation, attr);
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
static void type__node__is_in_numeric_notation(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_in_numeric_notation);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_in_numeric_notation, attr);
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
static void type__node__is_mutable(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_mutable);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_mutable, attr);
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
static void type__node__is_not_used(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_not_used);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_not_used, attr);
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
static void type__node__kind_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__kind_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__kind_of, attr);
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
static void type__node__last_line_end_specifier_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__last_line_end_specifier_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__last_line_end_specifier_of, attr);
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
static void type__node__line_end_specifier_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__line_end_specifier_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__line_end_specifier_of, attr);
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
static void type__node__lowest_precedence_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__lowest_precedence_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__lowest_precedence_of, attr);
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
static void type__node__mangled_name_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__mangled_name_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__mangled_name_of, attr);
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
static void type__node__max_length_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__max_length_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__max_length_of, attr);
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
static void type__node__message_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__message_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__message_of, attr);
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
static void type__node__name_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__name_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__name_of, attr);
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
static void type__node__namespace_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__namespace_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__namespace_of, attr);
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
static void type__node__namespace_alias_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__namespace_alias_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__namespace_alias_of, attr);
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
static void type__node__node_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__node_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__node_of, attr);
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
static void type__node__operators_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__operators_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__operators_of, attr);
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
static void type__node__parameter_kind_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__parameter_kind_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__parameter_kind_of, attr);
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
static void type__node__parameters_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__parameters_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__parameters_of, attr);
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
static void type__node__parent_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__parent_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__parent_of, attr);
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
static void type__node__result_count_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__result_count_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__result_count_of, attr);
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
static void type__node__continuation_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__continuation_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__continuation_of, attr);
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
static void type__node__source_position_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__source_position_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__source_position_of, attr);
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
static void type__node__temporary_count_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__temporary_count_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__temporary_count_of, attr);
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
static void type__node__remark_lines_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__remark_lines_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__remark_lines_of, attr);
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
static void type__node__scope_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__scope_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__scope_of, attr);
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
static void type__node__section_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__section_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__section_of, attr);
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
static void type__node__statements_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__statements_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__statements_of, attr);
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
static void type__node__submodule_no_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__submodule_no_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__submodule_no_of, attr);
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
static void type__node__text_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__text_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__text_of, attr);
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
static void type__node__type_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__type_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__type_of, attr);
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
static void type__node__used_names_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__used_names_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__used_names_of, attr);
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
static void type__node__value_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__value_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__value_of, attr);
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
static void type__node__variable_kind_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__variable_kind_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__variable_kind_of, attr);
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
static void type__node__is_a_meta_instruction(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_meta_instruction);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_meta_instruction, attr);
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
static void type__node__is_a_remark(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_remark);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_remark, attr);
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
static void type__node__is_a_body(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_body);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_body, attr);
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
static void type__node__defines_a_dynamic(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__defines_a_dynamic);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__defines_a_dynamic, attr);
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
static void type__node__is_a_call(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_call);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_call, attr);
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
static void type__node__is_a_procedure_call(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_procedure_call);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_procedure_call, attr);
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
static void type__node__is_a_return(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_return);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_return, attr);
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
static void type__node__is_an_assignment(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_assignment);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_assignment, attr);
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
static void type__node__is_a_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_definition, attr);
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
static void type__node__is_a_destination(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_destination);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_destination, attr);
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
static void type__node__is_an_input_output_argument(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_input_output_argument);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_input_output_argument, attr);
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
static void type__node__is_a_static_single_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_static_single_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_static_single_definition, attr);
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
static void type__node__is_a_static_multi_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_static_multi_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_static_multi_definition, attr);
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
static void type__node__is_a_dynamic_single_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_dynamic_single_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_dynamic_single_definition, attr);
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
static void type__node__is_a_dynamic_multi_definition(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_dynamic_multi_definition);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_dynamic_multi_definition, attr);
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
static void type__node__is_a_function_call(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_function_call);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_function_call, attr);
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
static void type__node__is_an_expression(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_expression);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_expression, attr);
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
static void type__node__is_a_backquoted_expression(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_backquoted_expression);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_backquoted_expression, attr);
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
static void type__node__is_an_attribute_value_pair(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_attribute_value_pair);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_attribute_value_pair, attr);
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
static void type__node__is_an_attribute_function_pair(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_attribute_function_pair);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_attribute_function_pair, attr);
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
static void type__node__is_a_numeric_literal(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_numeric_literal);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_numeric_literal, attr);
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
static void type__node__is_a_character_literal(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_character_literal);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_character_literal, attr);
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
static void type__node__is_a_string_literal(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_string_literal);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_string_literal, attr);
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
static void type__node__is_a_unique_item_constant(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_unique_item_constant);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_unique_item_constant, attr);
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
static void type__node__is_a_polymorphic_function_constant(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_polymorphic_function_constant);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_polymorphic_function_constant, attr);
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
static void type__node__is_an_identifier(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_identifier);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_identifier, attr);
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
static void type__node__is_used_as_a_polymorphic_function(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_used_as_a_polymorphic_function);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_used_as_a_polymorphic_function, attr);
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
static void type__node__is_used_as_a_destination(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_used_as_a_destination);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_used_as_a_destination, attr);
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
static void type__node__is_a_temporary(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_temporary);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_temporary, attr);
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
static void type__node__is_an_operator_symbol(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_an_operator_symbol);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_an_operator_symbol, attr);
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
static void type__node__is_c_code(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_c_code);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_c_code, attr);
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
static void type__node__is_a_c_body(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__node__is_a_c_body);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__node__is_a_c_body, attr);
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
static NODE *character__39;
static NODE *character__46;

static const char *used_namespaces[] = {
  "std",
  "compiler",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "nodes",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("nodes.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__nodes(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 145: $compiler::meta_instruction types::grammar_node
  initialize_maybe_future(var.compiler__meta_instruction, get__types__grammar_node());
  // 196: $compiler::body types::grammar_node
  initialize_maybe_future(var.compiler__body, get__types__grammar_node());
  // 210: $compiler::statement types::grammar_node
  initialize_maybe_future(var.compiler__statement, get__types__grammar_node());
  // 259: $compiler::definition types::grammar_node
  initialize_maybe_future(var.compiler__definition, get__types__grammar_node());
  // 320: $compiler::function_call types::grammar_node
  initialize_maybe_future(var.compiler__function_call, get__types__grammar_node());
  // 335: $compiler::expression types::grammar_node
  initialize_maybe_future(var.compiler__expression, get__types__grammar_node());
  // 343: $compiler::remark_argument types::grammar_node
  initialize_maybe_future(var.compiler__remark_argument, get__types__grammar_node());
  // 352: $compiler::backquoted types::grammar_node
  initialize_maybe_future(var.compiler__backquoted, get__types__grammar_node());
  // 361: $compiler::attribute_value_pair types::grammar_node
  initialize_maybe_future(var.compiler__attribute_value_pair, get__types__grammar_node());
  // 380: $compiler::numeric_literal types::grammar_node
  initialize_maybe_future(var.compiler__numeric_literal, get__types__grammar_node());
  // 393: $compiler::character_literal types::grammar_node
  initialize_maybe_future(var.compiler__character_literal, get__types__grammar_node());
  // 404: $compiler::string_literal types::grammar_node
  initialize_maybe_future(var.compiler__string_literal, get__types__grammar_node());
  // 423: $compiler::unique_item types::grammar_node
  initialize_maybe_future(var.compiler__unique_item, get__types__grammar_node());
  // 433: $compiler::polymorphic_function types::grammar_node
  initialize_maybe_future(var.compiler__polymorphic_function, get__types__grammar_node());
  // 457: $compiler::identifier types::grammar_node
  initialize_maybe_future(var.compiler__identifier, get__types__grammar_node());
  // 502: $compiler::c_code types::grammar_node
  initialize_maybe_future(var.compiler__c_code, get__types__grammar_node());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__numeric_literal__mangled_name_of_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 384: ... node::value_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var.node__value_of;
  func = myself->type;
  frame->cont = cont__compiler__numeric_literal__mangled_name_of_2;
}
static void cont__compiler__numeric_literal__mangled_name_of_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 384: ... '.' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__578a5af303e9cbe;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__numeric_literal__mangled_name_of_4;
}
static void cont__compiler__numeric_literal__mangled_name_of_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 384: ... '@apos;' = ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__39;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__numeric_literal__mangled_name_of_5;
}
static void cont__compiler__numeric_literal__mangled_name_of_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 384: ... replace_all(node::value_of(self) '.' = "_" '@apos;' = "")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__compiler__numeric_literal__mangled_name_of_6;
}
static void cont__compiler__numeric_literal__mangled_name_of_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 384: -> replace_all(node::value_of(self) '.' = "_" '@apos;' = "")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__identifier__full_name_of_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 463: namespace_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__full_name_of_2;
}
static void cont__compiler__identifier__full_name_of_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 463: namespace_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__identifier__full_name_of_3;
}
static void cont__compiler__identifier__full_name_of_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 464: -> string(namespace_of(self) "::")
  frame->slots[5] /* temp__5 */ = create_closure(entry__compiler__identifier__full_name_of_4, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  arguments->slots[2] = func__compiler__identifier__full_name_of_8;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__identifier__full_name_of_9;
}
static void entry__compiler__identifier__full_name_of_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 464: ... namespace_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__full_name_of_5;
}
static void cont__compiler__identifier__full_name_of_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 464: ... string(namespace_of(self) "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__identifier__full_name_of_7;
}
static void cont__compiler__identifier__full_name_of_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 464: -> string(namespace_of(self) "::")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__identifier__full_name_of_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 465: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__identifier__full_name_of_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 466: name_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__full_name_of_10;
}
static void cont__compiler__identifier__full_name_of_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__identifier__full_name_of_11;
}
static void cont__compiler__identifier__full_name_of_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 460: ->
  // 461:   string
  // 462:     if
  // 463:       namespace_of(self).is_defined
  // 464:       -> string(namespace_of(self) "::")
  // 465:       -> ""
  // 466:     name_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__identifier__mangled_name_of_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 472: namespace_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__mangled_name_of_2;
}
static void cont__compiler__identifier__mangled_name_of_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 472: namespace_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__identifier__mangled_name_of_3;
}
static void cont__compiler__identifier__mangled_name_of_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 473: -> string(namespace_of(self) "__")
  frame->slots[5] /* temp__5 */ = create_closure(entry__compiler__identifier__mangled_name_of_4, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  arguments->slots[2] = func__compiler__identifier__mangled_name_of_8;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__identifier__mangled_name_of_9;
}
static void entry__compiler__identifier__mangled_name_of_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 473: ... namespace_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__mangled_name_of_5;
}
static void cont__compiler__identifier__mangled_name_of_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 473: ... string(namespace_of(self) "__")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__identifier__mangled_name_of_7;
}
static void cont__compiler__identifier__mangled_name_of_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 473: -> string(namespace_of(self) "__")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__identifier__mangled_name_of_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 474: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__identifier__mangled_name_of_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 475: name_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__mangled_name_of_10;
}
static void cont__compiler__identifier__mangled_name_of_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__identifier__mangled_name_of_11;
}
static void cont__compiler__identifier__mangled_name_of_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 469: ->
  // 470:   string
  // 471:     if
  // 472:       namespace_of(self).is_defined
  // 473:       -> string(namespace_of(self) "__")
  // 474:       -> ""
  // 475:     name_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__is_a_parameter_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 519: ... parameter_kind_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__is_a_parameter_2;
}
static void cont__compiler__is_a_parameter_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 519: ... parameter_kind_of(self) != NO_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = get__NO_PARAMETER();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__is_a_parameter_3;
}
static void cont__compiler__is_a_parameter_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 519: ... parameter_kind_of(self) != NO_PARAMETER
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__is_a_parameter_4;
}
static void cont__compiler__is_a_parameter_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 519: ... -> parameter_kind_of(self) != NO_PARAMETER
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__nodes(void) {
  var.compiler__NONE = collect_node(var.compiler__NONE);
  var.compiler__ATTRIBUTE_KIND = collect_node(var.compiler__ATTRIBUTE_KIND);
  var.compiler__METHOD_KIND = collect_node(var.compiler__METHOD_KIND);
  var.compiler__NO_PARAMETER = collect_node(var.compiler__NO_PARAMETER);
  var.compiler__IN_PARAMETER = collect_node(var.compiler__IN_PARAMETER);
  var.compiler__IN_OUT_PARAMETER = collect_node(var.compiler__IN_OUT_PARAMETER);
  var.compiler__OUT_PARAMETER = collect_node(var.compiler__OUT_PARAMETER);
  var.compiler__MYSELF_PARAMETER = collect_node(var.compiler__MYSELF_PARAMETER);
  var.compiler__CONTINUATION_PARAMETER = collect_node(var.compiler__CONTINUATION_PARAMETER);
  var.compiler__LEFT = collect_node(var.compiler__LEFT);
  var.compiler__RIGHT = collect_node(var.compiler__RIGHT);
  var.compiler__POLYMORPHIC = collect_node(var.compiler__POLYMORPHIC);
  var.compiler__STATIC_SINGLE = collect_node(var.compiler__STATIC_SINGLE);
  var.compiler__STATIC_MULTI = collect_node(var.compiler__STATIC_MULTI);
  var.compiler__DYNAMIC_SINGLE = collect_node(var.compiler__DYNAMIC_SINGLE);
  var.compiler__DYNAMIC_MULTI = collect_node(var.compiler__DYNAMIC_MULTI);
  var.compiler__C_NODE = collect_node(var.compiler__C_NODE);
  var.node__argument_of = collect_node(var.node__argument_of);
  var.node__arguments_of = collect_node(var.node__arguments_of);
  var.node__attribute_kind_of = collect_node(var.node__attribute_kind_of);
  var.node__attribute_of = collect_node(var.node__attribute_of);
  var.node__base_of = collect_node(var.node__base_of);
  var.node__default_value_of = collect_node(var.node__default_value_of);
  var.node__defined_names_of = collect_node(var.node__defined_names_of);
  var.node__definitions_of = collect_node(var.node__definitions_of);
  var.node__destination_of = collect_node(var.node__destination_of);
  var.node__end_position_of = collect_node(var.node__end_position_of);
  var.node__expression_of = collect_node(var.node__expression_of);
  var.node__filemask_of = collect_node(var.node__filemask_of);
  var.node__filename_of = collect_node(var.node__filename_of);
  var.node__fragment_of = collect_node(var.node__fragment_of);
  var.node__full_name_of = collect_node(var.node__full_name_of);
  var.node__functor_of = collect_node(var.node__functor_of);
  var.node__identifier_of = collect_node(var.node__identifier_of);
  var.node__inherited_names_of = collect_node(var.node__inherited_names_of);
  var.node__is_a_constant = collect_node(var.node__is_a_constant);
  var.node__is_a_dynamic_definition = collect_node(var.node__is_a_dynamic_definition);
  var.node__is_a_method_definition = collect_node(var.node__is_a_method_definition);
  var.node__is_a_multi_assign_definition = collect_node(var.node__is_a_multi_assign_definition);
  var.node__is_an_expanded_item = collect_node(var.node__is_an_expanded_item);
  var.node__is_an_optional_item = collect_node(var.node__is_an_optional_item);
  var.node__is_a_setter = collect_node(var.node__is_a_setter);
  var.node__is_a_single_assign_definition = collect_node(var.node__is_a_single_assign_definition);
  var.node__is_a_static_definition = collect_node(var.node__is_a_static_definition);
  var.node__is_a_string_template = collect_node(var.node__is_a_string_template);
  var.node__is_an_attribute_access = collect_node(var.node__is_an_attribute_access);
  var.node__is_an_initialization = collect_node(var.node__is_an_initialization);
  var.node__is_in_infix_notation = collect_node(var.node__is_in_infix_notation);
  var.node__is_in_numeric_notation = collect_node(var.node__is_in_numeric_notation);
  var.node__is_mutable = collect_node(var.node__is_mutable);
  var.node__is_not_used = collect_node(var.node__is_not_used);
  var.node__kind_of = collect_node(var.node__kind_of);
  var.node__last_line_end_specifier_of = collect_node(var.node__last_line_end_specifier_of);
  var.node__line_end_specifier_of = collect_node(var.node__line_end_specifier_of);
  var.node__lowest_precedence_of = collect_node(var.node__lowest_precedence_of);
  var.node__mangled_name_of = collect_node(var.node__mangled_name_of);
  var.node__max_length_of = collect_node(var.node__max_length_of);
  var.node__message_of = collect_node(var.node__message_of);
  var.node__name_of = collect_node(var.node__name_of);
  var.node__namespace_of = collect_node(var.node__namespace_of);
  var.node__namespace_alias_of = collect_node(var.node__namespace_alias_of);
  var.node__node_of = collect_node(var.node__node_of);
  var.node__operators_of = collect_node(var.node__operators_of);
  var.node__parameter_kind_of = collect_node(var.node__parameter_kind_of);
  var.node__parameters_of = collect_node(var.node__parameters_of);
  var.node__parent_of = collect_node(var.node__parent_of);
  var.node__result_count_of = collect_node(var.node__result_count_of);
  var.node__continuation_of = collect_node(var.node__continuation_of);
  var.node__source_position_of = collect_node(var.node__source_position_of);
  var.node__temporary_count_of = collect_node(var.node__temporary_count_of);
  var.node__remark_lines_of = collect_node(var.node__remark_lines_of);
  var.node__scope_of = collect_node(var.node__scope_of);
  var.node__section_of = collect_node(var.node__section_of);
  var.node__statements_of = collect_node(var.node__statements_of);
  var.node__submodule_no_of = collect_node(var.node__submodule_no_of);
  var.node__text_of = collect_node(var.node__text_of);
  var.node__type_of = collect_node(var.node__type_of);
  var.node__used_names_of = collect_node(var.node__used_names_of);
  var.node__value_of = collect_node(var.node__value_of);
  var.node__variable_kind_of = collect_node(var.node__variable_kind_of);
  var.node__is_a_meta_instruction = collect_node(var.node__is_a_meta_instruction);
  var.compiler__meta_instruction = collect_node(var.compiler__meta_instruction);
  var.compiler__require_instruction = collect_node(var.compiler__require_instruction);
  var.compiler__namespace_instruction = collect_node(var.compiler__namespace_instruction);
  var.compiler__using_instruction = collect_node(var.compiler__using_instruction);
  var.compiler__include_instruction = collect_node(var.compiler__include_instruction);
  var.compiler__link_instruction = collect_node(var.compiler__link_instruction);
  var.compiler__data_instruction = collect_node(var.compiler__data_instruction);
  var.node__is_a_remark = collect_node(var.node__is_a_remark);
  var.compiler__remark_statement = collect_node(var.compiler__remark_statement);
  var.node__is_a_body = collect_node(var.node__is_a_body);
  var.node__defines_a_dynamic = collect_node(var.node__defines_a_dynamic);
  var.compiler__body = collect_node(var.compiler__body);
  var.compiler__statement = collect_node(var.compiler__statement);
  var.node__is_a_call = collect_node(var.node__is_a_call);
  var.compiler__call = collect_node(var.compiler__call);
  var.node__is_a_procedure_call = collect_node(var.node__is_a_procedure_call);
  var.compiler__procedure_call = collect_node(var.compiler__procedure_call);
  var.node__is_a_return = collect_node(var.node__is_a_return);
  var.compiler__return_statement = collect_node(var.compiler__return_statement);
  var.node__is_an_assignment = collect_node(var.node__is_an_assignment);
  var.compiler__assignment = collect_node(var.compiler__assignment);
  var.node__is_a_definition = collect_node(var.node__is_a_definition);
  var.node__is_a_destination = collect_node(var.node__is_a_destination);
  var.node__is_an_input_output_argument = collect_node(var.node__is_an_input_output_argument);
  var.compiler__definition = collect_node(var.compiler__definition);
  var.node__is_a_static_single_definition = collect_node(var.node__is_a_static_single_definition);
  var.compiler__define_static_single = collect_node(var.compiler__define_static_single);
  var.node__is_a_static_multi_definition = collect_node(var.node__is_a_static_multi_definition);
  var.compiler__define_static_multi = collect_node(var.compiler__define_static_multi);
  var.node__is_a_dynamic_single_definition = collect_node(var.node__is_a_dynamic_single_definition);
  var.compiler__define_dynamic_single = collect_node(var.compiler__define_dynamic_single);
  var.node__is_a_dynamic_multi_definition = collect_node(var.node__is_a_dynamic_multi_definition);
  var.compiler__define_dynamic_multi = collect_node(var.compiler__define_dynamic_multi);
  var.node__is_a_function_call = collect_node(var.node__is_a_function_call);
  var.compiler__function_call = collect_node(var.compiler__function_call);
  var.node__is_an_expression = collect_node(var.node__is_an_expression);
  var.compiler__expression = collect_node(var.compiler__expression);
  var.compiler__remark_argument = collect_node(var.compiler__remark_argument);
  var.node__is_a_backquoted_expression = collect_node(var.node__is_a_backquoted_expression);
  var.compiler__backquoted = collect_node(var.compiler__backquoted);
  var.node__is_an_attribute_value_pair = collect_node(var.node__is_an_attribute_value_pair);
  var.compiler__attribute_value_pair = collect_node(var.compiler__attribute_value_pair);
  var.node__is_an_attribute_function_pair = collect_node(var.node__is_an_attribute_function_pair);
  var.compiler__attribute_function_pair = collect_node(var.compiler__attribute_function_pair);
  var.node__is_a_numeric_literal = collect_node(var.node__is_a_numeric_literal);
  var.compiler__numeric_literal = collect_node(var.compiler__numeric_literal);
  var.node__is_a_character_literal = collect_node(var.node__is_a_character_literal);
  var.compiler__character_literal = collect_node(var.compiler__character_literal);
  var.node__is_a_string_literal = collect_node(var.node__is_a_string_literal);
  var.compiler__string_literal = collect_node(var.compiler__string_literal);
  var.compiler__multi_line_string = collect_node(var.compiler__multi_line_string);
  var.node__is_a_unique_item_constant = collect_node(var.node__is_a_unique_item_constant);
  var.compiler__unique_item = collect_node(var.compiler__unique_item);
  var.node__is_a_polymorphic_function_constant = collect_node(var.node__is_a_polymorphic_function_constant);
  var.compiler__polymorphic_function = collect_node(var.compiler__polymorphic_function);
  var.compiler__polymorphic_function_with_setter = collect_node(var.compiler__polymorphic_function_with_setter);
  var.node__is_an_identifier = collect_node(var.node__is_an_identifier);
  var.node__is_used_as_a_polymorphic_function = collect_node(var.node__is_used_as_a_polymorphic_function);
  var.node__is_used_as_a_destination = collect_node(var.node__is_used_as_a_destination);
  var.compiler__identifier = collect_node(var.compiler__identifier);
  var.node__is_a_temporary = collect_node(var.node__is_a_temporary);
  var.compiler__temporary = collect_node(var.compiler__temporary);
  var.node__is_an_operator_symbol = collect_node(var.node__is_an_operator_symbol);
  var.compiler__operator_symbol = collect_node(var.compiler__operator_symbol);
  var.node__is_c_code = collect_node(var.node__is_c_code);
  var.compiler__c_code = collect_node(var.compiler__c_code);
  var.node__is_a_c_body = collect_node(var.node__is_a_c_body);
  var.compiler__c_body = collect_node(var.compiler__c_body);
  var.compiler__is_a_parameter = collect_node(var.compiler__is_a_parameter);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__nodes(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_namespace("node");
}

static int already_run_phase_2 = false;

EXPORT void phase_2__nodes(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("nodes");
  character__39 = from_uchar32(39);
  character__46 = from_uchar32(46);
  unique__compiler__NONE = register_unique_item("compiler__NONE");
  unique__compiler__ATTRIBUTE_KIND = register_unique_item("compiler__ATTRIBUTE_KIND");
  unique__compiler__METHOD_KIND = register_unique_item("compiler__METHOD_KIND");
  unique__compiler__NO_PARAMETER = register_unique_item("compiler__NO_PARAMETER");
  unique__compiler__IN_PARAMETER = register_unique_item("compiler__IN_PARAMETER");
  unique__compiler__IN_OUT_PARAMETER = register_unique_item("compiler__IN_OUT_PARAMETER");
  unique__compiler__OUT_PARAMETER = register_unique_item("compiler__OUT_PARAMETER");
  unique__compiler__MYSELF_PARAMETER = register_unique_item("compiler__MYSELF_PARAMETER");
  unique__compiler__CONTINUATION_PARAMETER = register_unique_item("compiler__CONTINUATION_PARAMETER");
  unique__compiler__LEFT = register_unique_item("compiler__LEFT");
  unique__compiler__RIGHT = register_unique_item("compiler__RIGHT");
  unique__compiler__POLYMORPHIC = register_unique_item("compiler__POLYMORPHIC");
  unique__compiler__STATIC_SINGLE = register_unique_item("compiler__STATIC_SINGLE");
  unique__compiler__STATIC_MULTI = register_unique_item("compiler__STATIC_MULTI");
  unique__compiler__DYNAMIC_SINGLE = register_unique_item("compiler__DYNAMIC_SINGLE");
  unique__compiler__DYNAMIC_MULTI = register_unique_item("compiler__DYNAMIC_MULTI");
  unique__compiler__C_NODE = register_unique_item("compiler__C_NODE");
  define_polymorphic_function_with_setter("node", "argument_of", get__node__argument_of, &poly_idx__node__argument_of, &var.node__argument_of);
  define_polymorphic_function_with_setter("node", "arguments_of", get__node__arguments_of, &poly_idx__node__arguments_of, &var.node__arguments_of);
  define_polymorphic_function_with_setter("node", "attribute_kind_of", get__node__attribute_kind_of, &poly_idx__node__attribute_kind_of, &var.node__attribute_kind_of);
  define_polymorphic_function_with_setter("node", "attribute_of", get__node__attribute_of, &poly_idx__node__attribute_of, &var.node__attribute_of);
  define_polymorphic_function_with_setter("node", "base_of", get__node__base_of, &poly_idx__node__base_of, &var.node__base_of);
  define_polymorphic_function_with_setter("node", "default_value_of", get__node__default_value_of, &poly_idx__node__default_value_of, &var.node__default_value_of);
  define_polymorphic_function_with_setter("node", "defined_names_of", get__node__defined_names_of, &poly_idx__node__defined_names_of, &var.node__defined_names_of);
  define_polymorphic_function_with_setter("node", "definitions_of", get__node__definitions_of, &poly_idx__node__definitions_of, &var.node__definitions_of);
  define_polymorphic_function_with_setter("node", "destination_of", get__node__destination_of, &poly_idx__node__destination_of, &var.node__destination_of);
  define_polymorphic_function_with_setter("node", "end_position_of", get__node__end_position_of, &poly_idx__node__end_position_of, &var.node__end_position_of);
  define_polymorphic_function_with_setter("node", "expression_of", get__node__expression_of, &poly_idx__node__expression_of, &var.node__expression_of);
  define_polymorphic_function_with_setter("node", "filemask_of", get__node__filemask_of, &poly_idx__node__filemask_of, &var.node__filemask_of);
  define_polymorphic_function_with_setter("node", "filename_of", get__node__filename_of, &poly_idx__node__filename_of, &var.node__filename_of);
  define_polymorphic_function_with_setter("node", "fragment_of", get__node__fragment_of, &poly_idx__node__fragment_of, &var.node__fragment_of);
  define_polymorphic_function_with_setter("node", "full_name_of", get__node__full_name_of, &poly_idx__node__full_name_of, &var.node__full_name_of);
  define_polymorphic_function_with_setter("node", "functor_of", get__node__functor_of, &poly_idx__node__functor_of, &var.node__functor_of);
  define_polymorphic_function_with_setter("node", "identifier_of", get__node__identifier_of, &poly_idx__node__identifier_of, &var.node__identifier_of);
  define_polymorphic_function_with_setter("node", "inherited_names_of", get__node__inherited_names_of, &poly_idx__node__inherited_names_of, &var.node__inherited_names_of);
  define_polymorphic_function("node", "is_a_constant", get__node__is_a_constant, &poly_idx__node__is_a_constant, &var.node__is_a_constant);
  define_polymorphic_function("node", "is_a_dynamic_definition", get__node__is_a_dynamic_definition, &poly_idx__node__is_a_dynamic_definition, &var.node__is_a_dynamic_definition);
  define_polymorphic_function("node", "is_a_method_definition", get__node__is_a_method_definition, &poly_idx__node__is_a_method_definition, &var.node__is_a_method_definition);
  define_polymorphic_function("node", "is_a_multi_assign_definition", get__node__is_a_multi_assign_definition, &poly_idx__node__is_a_multi_assign_definition, &var.node__is_a_multi_assign_definition);
  define_polymorphic_function("node", "is_an_expanded_item", get__node__is_an_expanded_item, &poly_idx__node__is_an_expanded_item, &var.node__is_an_expanded_item);
  define_polymorphic_function("node", "is_an_optional_item", get__node__is_an_optional_item, &poly_idx__node__is_an_optional_item, &var.node__is_an_optional_item);
  define_polymorphic_function("node", "is_a_setter", get__node__is_a_setter, &poly_idx__node__is_a_setter, &var.node__is_a_setter);
  define_polymorphic_function("node", "is_a_single_assign_definition", get__node__is_a_single_assign_definition, &poly_idx__node__is_a_single_assign_definition, &var.node__is_a_single_assign_definition);
  define_polymorphic_function("node", "is_a_static_definition", get__node__is_a_static_definition, &poly_idx__node__is_a_static_definition, &var.node__is_a_static_definition);
  define_polymorphic_function("node", "is_a_string_template", get__node__is_a_string_template, &poly_idx__node__is_a_string_template, &var.node__is_a_string_template);
  define_polymorphic_function("node", "is_an_attribute_access", get__node__is_an_attribute_access, &poly_idx__node__is_an_attribute_access, &var.node__is_an_attribute_access);
  define_polymorphic_function("node", "is_an_initialization", get__node__is_an_initialization, &poly_idx__node__is_an_initialization, &var.node__is_an_initialization);
  define_polymorphic_function("node", "is_in_infix_notation", get__node__is_in_infix_notation, &poly_idx__node__is_in_infix_notation, &var.node__is_in_infix_notation);
  define_polymorphic_function("node", "is_in_numeric_notation", get__node__is_in_numeric_notation, &poly_idx__node__is_in_numeric_notation, &var.node__is_in_numeric_notation);
  define_polymorphic_function("node", "is_mutable", get__node__is_mutable, &poly_idx__node__is_mutable, &var.node__is_mutable);
  define_polymorphic_function("node", "is_not_used", get__node__is_not_used, &poly_idx__node__is_not_used, &var.node__is_not_used);
  define_polymorphic_function_with_setter("node", "kind_of", get__node__kind_of, &poly_idx__node__kind_of, &var.node__kind_of);
  define_polymorphic_function_with_setter("node", "last_line_end_specifier_of", get__node__last_line_end_specifier_of, &poly_idx__node__last_line_end_specifier_of, &var.node__last_line_end_specifier_of);
  define_polymorphic_function_with_setter("node", "line_end_specifier_of", get__node__line_end_specifier_of, &poly_idx__node__line_end_specifier_of, &var.node__line_end_specifier_of);
  define_polymorphic_function_with_setter("node", "lowest_precedence_of", get__node__lowest_precedence_of, &poly_idx__node__lowest_precedence_of, &var.node__lowest_precedence_of);
  define_polymorphic_function("node", "mangled_name_of", get__node__mangled_name_of, &poly_idx__node__mangled_name_of, &var.node__mangled_name_of);
  define_polymorphic_function_with_setter("node", "max_length_of", get__node__max_length_of, &poly_idx__node__max_length_of, &var.node__max_length_of);
  define_polymorphic_function_with_setter("node", "message_of", get__node__message_of, &poly_idx__node__message_of, &var.node__message_of);
  define_polymorphic_function_with_setter("node", "name_of", get__node__name_of, &poly_idx__node__name_of, &var.node__name_of);
  define_polymorphic_function_with_setter("node", "namespace_of", get__node__namespace_of, &poly_idx__node__namespace_of, &var.node__namespace_of);
  define_polymorphic_function_with_setter("node", "namespace_alias_of", get__node__namespace_alias_of, &poly_idx__node__namespace_alias_of, &var.node__namespace_alias_of);
  define_polymorphic_function_with_setter("node", "node_of", get__node__node_of, &poly_idx__node__node_of, &var.node__node_of);
  define_polymorphic_function_with_setter("node", "operators_of", get__node__operators_of, &poly_idx__node__operators_of, &var.node__operators_of);
  define_polymorphic_function_with_setter("node", "parameter_kind_of", get__node__parameter_kind_of, &poly_idx__node__parameter_kind_of, &var.node__parameter_kind_of);
  define_polymorphic_function_with_setter("node", "parameters_of", get__node__parameters_of, &poly_idx__node__parameters_of, &var.node__parameters_of);
  define_polymorphic_function_with_setter("node", "parent_of", get__node__parent_of, &poly_idx__node__parent_of, &var.node__parent_of);
  define_polymorphic_function_with_setter("node", "result_count_of", get__node__result_count_of, &poly_idx__node__result_count_of, &var.node__result_count_of);
  define_polymorphic_function_with_setter("node", "continuation_of", get__node__continuation_of, &poly_idx__node__continuation_of, &var.node__continuation_of);
  define_polymorphic_function_with_setter("node", "source_position_of", get__node__source_position_of, &poly_idx__node__source_position_of, &var.node__source_position_of);
  define_polymorphic_function_with_setter("node", "temporary_count_of", get__node__temporary_count_of, &poly_idx__node__temporary_count_of, &var.node__temporary_count_of);
  define_polymorphic_function("node", "remark_lines_of", get__node__remark_lines_of, &poly_idx__node__remark_lines_of, &var.node__remark_lines_of);
  define_polymorphic_function_with_setter("node", "scope_of", get__node__scope_of, &poly_idx__node__scope_of, &var.node__scope_of);
  define_polymorphic_function_with_setter("node", "section_of", get__node__section_of, &poly_idx__node__section_of, &var.node__section_of);
  define_polymorphic_function_with_setter("node", "statements_of", get__node__statements_of, &poly_idx__node__statements_of, &var.node__statements_of);
  define_polymorphic_function_with_setter("node", "submodule_no_of", get__node__submodule_no_of, &poly_idx__node__submodule_no_of, &var.node__submodule_no_of);
  define_polymorphic_function_with_setter("node", "text_of", get__node__text_of, &poly_idx__node__text_of, &var.node__text_of);
  define_polymorphic_function_with_setter("node", "type_of", get__node__type_of, &poly_idx__node__type_of, &var.node__type_of);
  define_polymorphic_function_with_setter("node", "used_names_of", get__node__used_names_of, &poly_idx__node__used_names_of, &var.node__used_names_of);
  define_polymorphic_function_with_setter("node", "value_of", get__node__value_of, &poly_idx__node__value_of, &var.node__value_of);
  define_polymorphic_function_with_setter("node", "variable_kind_of", get__node__variable_kind_of, &poly_idx__node__variable_kind_of, &var.node__variable_kind_of);
  define_polymorphic_function("node", "is_a_meta_instruction", get__node__is_a_meta_instruction, &poly_idx__node__is_a_meta_instruction, &var.node__is_a_meta_instruction);
  define_polymorphic_function("node", "is_a_remark", get__node__is_a_remark, &poly_idx__node__is_a_remark, &var.node__is_a_remark);
  define_polymorphic_function("node", "is_a_body", get__node__is_a_body, &poly_idx__node__is_a_body, &var.node__is_a_body);
  define_polymorphic_function("node", "defines_a_dynamic", get__node__defines_a_dynamic, &poly_idx__node__defines_a_dynamic, &var.node__defines_a_dynamic);
  define_polymorphic_function("node", "is_a_call", get__node__is_a_call, &poly_idx__node__is_a_call, &var.node__is_a_call);
  define_polymorphic_function("node", "is_a_procedure_call", get__node__is_a_procedure_call, &poly_idx__node__is_a_procedure_call, &var.node__is_a_procedure_call);
  define_polymorphic_function("node", "is_a_return", get__node__is_a_return, &poly_idx__node__is_a_return, &var.node__is_a_return);
  define_polymorphic_function("node", "is_an_assignment", get__node__is_an_assignment, &poly_idx__node__is_an_assignment, &var.node__is_an_assignment);
  define_polymorphic_function("node", "is_a_definition", get__node__is_a_definition, &poly_idx__node__is_a_definition, &var.node__is_a_definition);
  define_polymorphic_function("node", "is_a_destination", get__node__is_a_destination, &poly_idx__node__is_a_destination, &var.node__is_a_destination);
  define_polymorphic_function("node", "is_an_input_output_argument", get__node__is_an_input_output_argument, &poly_idx__node__is_an_input_output_argument, &var.node__is_an_input_output_argument);
  define_polymorphic_function("node", "is_a_static_single_definition", get__node__is_a_static_single_definition, &poly_idx__node__is_a_static_single_definition, &var.node__is_a_static_single_definition);
  define_polymorphic_function("node", "is_a_static_multi_definition", get__node__is_a_static_multi_definition, &poly_idx__node__is_a_static_multi_definition, &var.node__is_a_static_multi_definition);
  define_polymorphic_function("node", "is_a_dynamic_single_definition", get__node__is_a_dynamic_single_definition, &poly_idx__node__is_a_dynamic_single_definition, &var.node__is_a_dynamic_single_definition);
  define_polymorphic_function("node", "is_a_dynamic_multi_definition", get__node__is_a_dynamic_multi_definition, &poly_idx__node__is_a_dynamic_multi_definition, &var.node__is_a_dynamic_multi_definition);
  define_polymorphic_function("node", "is_a_function_call", get__node__is_a_function_call, &poly_idx__node__is_a_function_call, &var.node__is_a_function_call);
  define_polymorphic_function("node", "is_an_expression", get__node__is_an_expression, &poly_idx__node__is_an_expression, &var.node__is_an_expression);
  define_polymorphic_function("node", "is_a_backquoted_expression", get__node__is_a_backquoted_expression, &poly_idx__node__is_a_backquoted_expression, &var.node__is_a_backquoted_expression);
  define_polymorphic_function("node", "is_an_attribute_value_pair", get__node__is_an_attribute_value_pair, &poly_idx__node__is_an_attribute_value_pair, &var.node__is_an_attribute_value_pair);
  define_polymorphic_function("node", "is_an_attribute_function_pair", get__node__is_an_attribute_function_pair, &poly_idx__node__is_an_attribute_function_pair, &var.node__is_an_attribute_function_pair);
  define_polymorphic_function("node", "is_a_numeric_literal", get__node__is_a_numeric_literal, &poly_idx__node__is_a_numeric_literal, &var.node__is_a_numeric_literal);
  string__578a5af303e9cbe = from_latin_1_string("_", 1);
  func__compiler__numeric_literal__mangled_name_of_1 = create_function(entry__compiler__numeric_literal__mangled_name_of_1, 1);
  define_polymorphic_function("node", "is_a_character_literal", get__node__is_a_character_literal, &poly_idx__node__is_a_character_literal, &var.node__is_a_character_literal);
  define_polymorphic_function("node", "is_a_string_literal", get__node__is_a_string_literal, &poly_idx__node__is_a_string_literal, &var.node__is_a_string_literal);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  define_polymorphic_function("node", "is_a_unique_item_constant", get__node__is_a_unique_item_constant, &poly_idx__node__is_a_unique_item_constant, &var.node__is_a_unique_item_constant);
  define_polymorphic_function("node", "is_a_polymorphic_function_constant", get__node__is_a_polymorphic_function_constant, &poly_idx__node__is_a_polymorphic_function_constant, &var.node__is_a_polymorphic_function_constant);
  define_polymorphic_function("node", "is_an_identifier", get__node__is_an_identifier, &poly_idx__node__is_an_identifier, &var.node__is_an_identifier);
  define_polymorphic_function("node", "is_used_as_a_polymorphic_function", get__node__is_used_as_a_polymorphic_function, &poly_idx__node__is_used_as_a_polymorphic_function, &var.node__is_used_as_a_polymorphic_function);
  define_polymorphic_function("node", "is_used_as_a_destination", get__node__is_used_as_a_destination, &poly_idx__node__is_used_as_a_destination, &var.node__is_used_as_a_destination);
  string__2d7981f4e6d82bff = from_latin_1_string("::", 2);
  func__compiler__identifier__full_name_of_8 = create_function(entry__compiler__identifier__full_name_of_8, 0);
  func__compiler__identifier__full_name_of_1 = create_function(entry__compiler__identifier__full_name_of_1, 1);
  string__2d7981f4e5f02b9a = from_latin_1_string("__", 2);
  func__compiler__identifier__mangled_name_of_8 = create_function(entry__compiler__identifier__mangled_name_of_8, 0);
  func__compiler__identifier__mangled_name_of_1 = create_function(entry__compiler__identifier__mangled_name_of_1, 1);
  define_polymorphic_function("node", "is_a_temporary", get__node__is_a_temporary, &poly_idx__node__is_a_temporary, &var.node__is_a_temporary);
  define_polymorphic_function("node", "is_an_operator_symbol", get__node__is_an_operator_symbol, &poly_idx__node__is_an_operator_symbol, &var.node__is_an_operator_symbol);
  define_polymorphic_function("node", "is_c_code", get__node__is_c_code, &poly_idx__node__is_c_code, &var.node__is_c_code);
  string__545aebc3eac0d03b = from_latin_1_string("local", 5);
  define_polymorphic_function("node", "is_a_c_body", get__node__is_a_c_body, &poly_idx__node__is_a_c_body, &var.node__is_a_c_body);
  func__compiler__is_a_parameter_1 = create_function(entry__compiler__is_a_parameter_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__nodes(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("nodes");
  set_used_namespaces(used_namespaces);
  assign_value(&var.compiler__NONE, unique__compiler__NONE);
  define_single_assign_static("compiler", "NONE", get__compiler__NONE, &var.compiler__NONE);
  assign_value(&var.compiler__ATTRIBUTE_KIND, unique__compiler__ATTRIBUTE_KIND);
  define_single_assign_static("compiler", "ATTRIBUTE_KIND", get__compiler__ATTRIBUTE_KIND, &var.compiler__ATTRIBUTE_KIND);
  assign_value(&var.compiler__METHOD_KIND, unique__compiler__METHOD_KIND);
  define_single_assign_static("compiler", "METHOD_KIND", get__compiler__METHOD_KIND, &var.compiler__METHOD_KIND);
  assign_value(&var.compiler__NO_PARAMETER, unique__compiler__NO_PARAMETER);
  define_single_assign_static("compiler", "NO_PARAMETER", get__compiler__NO_PARAMETER, &var.compiler__NO_PARAMETER);
  assign_value(&var.compiler__IN_PARAMETER, unique__compiler__IN_PARAMETER);
  define_single_assign_static("compiler", "IN_PARAMETER", get__compiler__IN_PARAMETER, &var.compiler__IN_PARAMETER);
  assign_value(&var.compiler__IN_OUT_PARAMETER, unique__compiler__IN_OUT_PARAMETER);
  define_single_assign_static("compiler", "IN_OUT_PARAMETER", get__compiler__IN_OUT_PARAMETER, &var.compiler__IN_OUT_PARAMETER);
  assign_value(&var.compiler__OUT_PARAMETER, unique__compiler__OUT_PARAMETER);
  define_single_assign_static("compiler", "OUT_PARAMETER", get__compiler__OUT_PARAMETER, &var.compiler__OUT_PARAMETER);
  assign_value(&var.compiler__MYSELF_PARAMETER, unique__compiler__MYSELF_PARAMETER);
  define_single_assign_static("compiler", "MYSELF_PARAMETER", get__compiler__MYSELF_PARAMETER, &var.compiler__MYSELF_PARAMETER);
  assign_value(&var.compiler__CONTINUATION_PARAMETER, unique__compiler__CONTINUATION_PARAMETER);
  define_single_assign_static("compiler", "CONTINUATION_PARAMETER", get__compiler__CONTINUATION_PARAMETER, &var.compiler__CONTINUATION_PARAMETER);
  assign_value(&var.compiler__LEFT, unique__compiler__LEFT);
  define_single_assign_static("compiler", "LEFT", get__compiler__LEFT, &var.compiler__LEFT);
  assign_value(&var.compiler__RIGHT, unique__compiler__RIGHT);
  define_single_assign_static("compiler", "RIGHT", get__compiler__RIGHT, &var.compiler__RIGHT);
  assign_value(&var.compiler__POLYMORPHIC, unique__compiler__POLYMORPHIC);
  define_single_assign_static("compiler", "POLYMORPHIC", get__compiler__POLYMORPHIC, &var.compiler__POLYMORPHIC);
  assign_value(&var.compiler__STATIC_SINGLE, unique__compiler__STATIC_SINGLE);
  define_single_assign_static("compiler", "STATIC_SINGLE", get__compiler__STATIC_SINGLE, &var.compiler__STATIC_SINGLE);
  assign_value(&var.compiler__STATIC_MULTI, unique__compiler__STATIC_MULTI);
  define_single_assign_static("compiler", "STATIC_MULTI", get__compiler__STATIC_MULTI, &var.compiler__STATIC_MULTI);
  assign_value(&var.compiler__DYNAMIC_SINGLE, unique__compiler__DYNAMIC_SINGLE);
  define_single_assign_static("compiler", "DYNAMIC_SINGLE", get__compiler__DYNAMIC_SINGLE, &var.compiler__DYNAMIC_SINGLE);
  assign_value(&var.compiler__DYNAMIC_MULTI, unique__compiler__DYNAMIC_MULTI);
  define_single_assign_static("compiler", "DYNAMIC_MULTI", get__compiler__DYNAMIC_MULTI, &var.compiler__DYNAMIC_MULTI);
  assign_value(&var.compiler__C_NODE, unique__compiler__C_NODE);
  define_single_assign_static("compiler", "C_NODE", get__compiler__C_NODE, &var.compiler__C_NODE);
  define_single_assign_static("compiler", "meta_instruction", get__compiler__meta_instruction, &var.compiler__meta_instruction);
  define_single_assign_static("compiler", "require_instruction", get__compiler__require_instruction, &var.compiler__require_instruction);
  define_single_assign_static("compiler", "namespace_instruction", get__compiler__namespace_instruction, &var.compiler__namespace_instruction);
  define_single_assign_static("compiler", "using_instruction", get__compiler__using_instruction, &var.compiler__using_instruction);
  define_single_assign_static("compiler", "include_instruction", get__compiler__include_instruction, &var.compiler__include_instruction);
  define_single_assign_static("compiler", "link_instruction", get__compiler__link_instruction, &var.compiler__link_instruction);
  define_single_assign_static("compiler", "data_instruction", get__compiler__data_instruction, &var.compiler__data_instruction);
  define_single_assign_static("compiler", "remark_statement", get__compiler__remark_statement, &var.compiler__remark_statement);
  define_single_assign_static("compiler", "body", get__compiler__body, &var.compiler__body);
  define_single_assign_static("compiler", "statement", get__compiler__statement, &var.compiler__statement);
  define_single_assign_static("compiler", "call", get__compiler__call, &var.compiler__call);
  define_single_assign_static("compiler", "procedure_call", get__compiler__procedure_call, &var.compiler__procedure_call);
  define_single_assign_static("compiler", "return_statement", get__compiler__return_statement, &var.compiler__return_statement);
  define_single_assign_static("compiler", "assignment", get__compiler__assignment, &var.compiler__assignment);
  define_single_assign_static("compiler", "definition", get__compiler__definition, &var.compiler__definition);
  define_single_assign_static("compiler", "define_static_single", get__compiler__define_static_single, &var.compiler__define_static_single);
  define_single_assign_static("compiler", "define_static_multi", get__compiler__define_static_multi, &var.compiler__define_static_multi);
  define_single_assign_static("compiler", "define_dynamic_single", get__compiler__define_dynamic_single, &var.compiler__define_dynamic_single);
  define_single_assign_static("compiler", "define_dynamic_multi", get__compiler__define_dynamic_multi, &var.compiler__define_dynamic_multi);
  define_single_assign_static("compiler", "function_call", get__compiler__function_call, &var.compiler__function_call);
  define_single_assign_static("compiler", "expression", get__compiler__expression, &var.compiler__expression);
  define_single_assign_static("compiler", "remark_argument", get__compiler__remark_argument, &var.compiler__remark_argument);
  define_single_assign_static("compiler", "backquoted", get__compiler__backquoted, &var.compiler__backquoted);
  define_single_assign_static("compiler", "attribute_value_pair", get__compiler__attribute_value_pair, &var.compiler__attribute_value_pair);
  define_single_assign_static("compiler", "attribute_function_pair", get__compiler__attribute_function_pair, &var.compiler__attribute_function_pair);
  define_single_assign_static("compiler", "numeric_literal", get__compiler__numeric_literal, &var.compiler__numeric_literal);
  define_single_assign_static("compiler", "character_literal", get__compiler__character_literal, &var.compiler__character_literal);
  define_single_assign_static("compiler", "string_literal", get__compiler__string_literal, &var.compiler__string_literal);
  define_single_assign_static("compiler", "multi_line_string", get__compiler__multi_line_string, &var.compiler__multi_line_string);
  define_single_assign_static("compiler", "unique_item", get__compiler__unique_item, &var.compiler__unique_item);
  define_single_assign_static("compiler", "polymorphic_function", get__compiler__polymorphic_function, &var.compiler__polymorphic_function);
  define_single_assign_static("compiler", "polymorphic_function_with_setter", get__compiler__polymorphic_function_with_setter, &var.compiler__polymorphic_function_with_setter);
  define_single_assign_static("compiler", "identifier", get__compiler__identifier, &var.compiler__identifier);
  define_single_assign_static("compiler", "temporary", get__compiler__temporary, &var.compiler__temporary);
  define_single_assign_static("compiler", "operator_symbol", get__compiler__operator_symbol, &var.compiler__operator_symbol);
  define_single_assign_static("compiler", "c_code", get__compiler__c_code, &var.compiler__c_code);
  define_single_assign_static("compiler", "c_body", get__compiler__c_body, &var.compiler__c_body);
  define_single_assign_static("compiler", "is_a_parameter", get__compiler__is_a_parameter, &var.compiler__is_a_parameter);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__nodes(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("nodes");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "DYNAMIC_MULTI", &get__DYNAMIC_MULTI, &get_value_or_future__DYNAMIC_MULTI);
  use_read_only(NULL, "DYNAMIC_SINGLE", &get__DYNAMIC_SINGLE, &get_value_or_future__DYNAMIC_SINGLE);
  use_read_only(NULL, "NONE", &get__NONE, &get_value_or_future__NONE);
  use_read_only(NULL, "NO_PARAMETER", &get__NO_PARAMETER, &get_value_or_future__NO_PARAMETER);
  use_read_only(NULL, "STATIC_MULTI", &get__STATIC_MULTI, &get_value_or_future__STATIC_MULTI);
  use_read_only(NULL, "STATIC_SINGLE", &get__STATIC_SINGLE, &get_value_or_future__STATIC_SINGLE);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_polymorphic_function(NULL, "attribute_kind_of", &get__attribute_kind_of, &poly_idx__attribute_kind_of);
  use_polymorphic_function(NULL, "defined_names_of", &get__defined_names_of, &poly_idx__defined_names_of);
  use_polymorphic_function(NULL, "defines_a_dynamic", &get__defines_a_dynamic, &poly_idx__defines_a_dynamic);
  use_polymorphic_function(NULL, "definitions_of", &get__definitions_of, &poly_idx__definitions_of);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "full_name_of", &get__full_name_of, &poly_idx__full_name_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "inherited_names_of", &get__inherited_names_of, &poly_idx__inherited_names_of);
  use_polymorphic_function(NULL, "is_a_backquoted_expression", &get__is_a_backquoted_expression, &poly_idx__is_a_backquoted_expression);
  use_polymorphic_function(NULL, "is_a_body", &get__is_a_body, &poly_idx__is_a_body);
  use_polymorphic_function(NULL, "is_a_c_body", &get__is_a_c_body, &poly_idx__is_a_c_body);
  use_polymorphic_function(NULL, "is_a_call", &get__is_a_call, &poly_idx__is_a_call);
  use_polymorphic_function(NULL, "is_a_character_literal", &get__is_a_character_literal, &poly_idx__is_a_character_literal);
  use_polymorphic_function(NULL, "is_a_constant", &get__is_a_constant, &poly_idx__is_a_constant);
  use_polymorphic_function(NULL, "is_a_definition", &get__is_a_definition, &poly_idx__is_a_definition);
  use_polymorphic_function(NULL, "is_a_destination", &get__is_a_destination, &poly_idx__is_a_destination);
  use_polymorphic_function(NULL, "is_a_dynamic_definition", &get__is_a_dynamic_definition, &poly_idx__is_a_dynamic_definition);
  use_polymorphic_function(NULL, "is_a_dynamic_multi_definition", &get__is_a_dynamic_multi_definition, &poly_idx__is_a_dynamic_multi_definition);
  use_polymorphic_function(NULL, "is_a_dynamic_single_definition", &get__is_a_dynamic_single_definition, &poly_idx__is_a_dynamic_single_definition);
  use_polymorphic_function(NULL, "is_a_function_call", &get__is_a_function_call, &poly_idx__is_a_function_call);
  use_polymorphic_function(NULL, "is_a_meta_instruction", &get__is_a_meta_instruction, &poly_idx__is_a_meta_instruction);
  use_polymorphic_function(NULL, "is_a_method_definition", &get__is_a_method_definition, &poly_idx__is_a_method_definition);
  use_polymorphic_function(NULL, "is_a_multi_assign_definition", &get__is_a_multi_assign_definition, &poly_idx__is_a_multi_assign_definition);
  use_polymorphic_function(NULL, "is_a_numeric_literal", &get__is_a_numeric_literal, &poly_idx__is_a_numeric_literal);
  use_polymorphic_function(NULL, "is_a_polymorphic_function_constant", &get__is_a_polymorphic_function_constant, &poly_idx__is_a_polymorphic_function_constant);
  use_polymorphic_function(NULL, "is_a_procedure_call", &get__is_a_procedure_call, &poly_idx__is_a_procedure_call);
  use_polymorphic_function(NULL, "is_a_remark", &get__is_a_remark, &poly_idx__is_a_remark);
  use_polymorphic_function(NULL, "is_a_return", &get__is_a_return, &poly_idx__is_a_return);
  use_polymorphic_function(NULL, "is_a_setter", &get__is_a_setter, &poly_idx__is_a_setter);
  use_polymorphic_function(NULL, "is_a_single_assign_definition", &get__is_a_single_assign_definition, &poly_idx__is_a_single_assign_definition);
  use_polymorphic_function(NULL, "is_a_static_definition", &get__is_a_static_definition, &poly_idx__is_a_static_definition);
  use_polymorphic_function(NULL, "is_a_static_multi_definition", &get__is_a_static_multi_definition, &poly_idx__is_a_static_multi_definition);
  use_polymorphic_function(NULL, "is_a_static_single_definition", &get__is_a_static_single_definition, &poly_idx__is_a_static_single_definition);
  use_polymorphic_function(NULL, "is_a_string_literal", &get__is_a_string_literal, &poly_idx__is_a_string_literal);
  use_polymorphic_function(NULL, "is_a_string_template", &get__is_a_string_template, &poly_idx__is_a_string_template);
  use_polymorphic_function(NULL, "is_a_temporary", &get__is_a_temporary, &poly_idx__is_a_temporary);
  use_polymorphic_function(NULL, "is_a_unique_item_constant", &get__is_a_unique_item_constant, &poly_idx__is_a_unique_item_constant);
  use_polymorphic_function(NULL, "is_an_assignment", &get__is_an_assignment, &poly_idx__is_an_assignment);
  use_polymorphic_function(NULL, "is_an_attribute_access", &get__is_an_attribute_access, &poly_idx__is_an_attribute_access);
  use_polymorphic_function(NULL, "is_an_attribute_function_pair", &get__is_an_attribute_function_pair, &poly_idx__is_an_attribute_function_pair);
  use_polymorphic_function(NULL, "is_an_attribute_value_pair", &get__is_an_attribute_value_pair, &poly_idx__is_an_attribute_value_pair);
  use_polymorphic_function(NULL, "is_an_expanded_item", &get__is_an_expanded_item, &poly_idx__is_an_expanded_item);
  use_polymorphic_function(NULL, "is_an_expression", &get__is_an_expression, &poly_idx__is_an_expression);
  use_polymorphic_function(NULL, "is_an_identifier", &get__is_an_identifier, &poly_idx__is_an_identifier);
  use_polymorphic_function(NULL, "is_an_initialization", &get__is_an_initialization, &poly_idx__is_an_initialization);
  use_polymorphic_function(NULL, "is_an_input_output_argument", &get__is_an_input_output_argument, &poly_idx__is_an_input_output_argument);
  use_polymorphic_function(NULL, "is_an_operator_symbol", &get__is_an_operator_symbol, &poly_idx__is_an_operator_symbol);
  use_polymorphic_function(NULL, "is_an_optional_item", &get__is_an_optional_item, &poly_idx__is_an_optional_item);
  use_polymorphic_function(NULL, "is_c_code", &get__is_c_code, &poly_idx__is_c_code);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_polymorphic_function(NULL, "is_in_infix_notation", &get__is_in_infix_notation, &poly_idx__is_in_infix_notation);
  use_polymorphic_function(NULL, "is_in_numeric_notation", &get__is_in_numeric_notation, &poly_idx__is_in_numeric_notation);
  use_polymorphic_function(NULL, "is_not_used", &get__is_not_used, &poly_idx__is_not_used);
  use_polymorphic_function(NULL, "is_used_as_a_destination", &get__is_used_as_a_destination, &poly_idx__is_used_as_a_destination);
  use_polymorphic_function(NULL, "is_used_as_a_polymorphic_function", &get__is_used_as_a_polymorphic_function, &poly_idx__is_used_as_a_polymorphic_function);
  use_polymorphic_function(NULL, "mangled_name_of", &get__mangled_name_of, &poly_idx__mangled_name_of);
  use_read_only(NULL, "name_of", &get__name_of, &get_value_or_future__name_of);
  use_read_only(NULL, "namespace_of", &get__namespace_of, &get_value_or_future__namespace_of);
  use_polymorphic_function(NULL, "operators_of", &get__operators_of, &poly_idx__operators_of);
  use_polymorphic_function(NULL, "parameter_kind_of", &get__parameter_kind_of, &poly_idx__parameter_kind_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_polymorphic_function(NULL, "remark_lines_of", &get__remark_lines_of, &poly_idx__remark_lines_of);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_polymorphic_function(NULL, "scope_of", &get__scope_of, &poly_idx__scope_of);
  use_polymorphic_function(NULL, "statements_of", &get__statements_of, &poly_idx__statements_of);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "grammar_node", &get__types__grammar_node, &get_value_or_future__types__grammar_node);
  use_read_only("types", "insert_order_table", &get__types__insert_order_table, &get_value_or_future__types__insert_order_table);
  use_polymorphic_function(NULL, "used_names_of", &get__used_names_of, &poly_idx__used_names_of);
  use_polymorphic_function(NULL, "variable_kind_of", &get__variable_kind_of, &poly_idx__variable_kind_of);
  define_attribute("types", "grammar_node", poly_idx__remark_lines_of, get__empty_list());
  define_attribute("types", "grammar_node", poly_idx__is_a_constant, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_a_single_assign_definition, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_a_multi_assign_definition, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_a_static_definition, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_a_dynamic_definition, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_an_initialization, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_an_expanded_item, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_an_optional_item, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_a_meta_instruction, get__false());
  define_attribute("compiler", "meta_instruction", poly_idx__is_a_meta_instruction, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_a_remark, get__false());
  define_attribute("compiler", "remark_statement", poly_idx__is_a_remark, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_a_body, get__false());
  define_attribute("compiler", "body", poly_idx__is_a_body, get__true());
  define_attribute("compiler", "body", poly_idx__is_a_constant, get__true());
  define_attribute("compiler", "body", poly_idx__defines_a_dynamic, get__false());
  define_attribute("compiler", "body", poly_idx__definitions_of, get__empty_list());
  define_attribute("compiler", "body", poly_idx__statements_of, get__empty_list());
  define_attribute("compiler", "body", poly_idx__parameters_of, get__empty_list());
  define_attribute("compiler", "body", poly_idx__defined_names_of, get__types__insert_order_table());
  define_attribute("compiler", "body", poly_idx__inherited_names_of, get__types__insert_order_table());
  define_attribute("compiler", "body", poly_idx__used_names_of, get__types__insert_order_table());
  define_attribute("compiler", "body", poly_idx__arguments_of, get__empty_list());
  define_attribute("types", "grammar_node", poly_idx__is_a_call, get__false());
  define_attribute("compiler", "call", poly_idx__is_a_call, get__true());
  define_attribute("compiler", "call", poly_idx__arguments_of, get__empty_list());
  define_attribute("compiler", "call", poly_idx__is_a_procedure_call, get__false());
  define_attribute("compiler", "procedure_call", poly_idx__is_a_procedure_call, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_a_return, get__false());
  define_attribute("compiler", "return_statement", poly_idx__is_a_return, get__true());
  define_attribute("compiler", "call", poly_idx__is_an_assignment, get__false());
  define_attribute("compiler", "assignment", poly_idx__is_an_assignment, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_a_definition, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_a_destination, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_an_input_output_argument, get__false());
  define_attribute("compiler", "definition", poly_idx__is_a_definition, get__true());
  define_attribute("compiler", "definition", poly_idx__is_a_destination, get__true());
  define_attribute("compiler", "definition", poly_idx__attribute_kind_of, get__NONE());
  define_attribute("compiler", "definition", poly_idx__parameter_kind_of, get__NO_PARAMETER());
  define_attribute("types", "grammar_node", poly_idx__is_a_static_single_definition, get__false());
  define_attribute("compiler", "define_static_single", poly_idx__is_a_static_single_definition, get__true());
  define_attribute("compiler", "define_static_single", poly_idx__is_a_single_assign_definition, get__true());
  define_attribute("compiler", "define_static_single", poly_idx__is_a_static_definition, get__true());
  define_attribute("compiler", "define_static_single", poly_idx__variable_kind_of, get__STATIC_SINGLE());
  define_attribute("types", "grammar_node", poly_idx__is_a_static_multi_definition, get__false());
  define_attribute("compiler", "define_static_multi", poly_idx__is_a_static_multi_definition, get__true());
  define_attribute("compiler", "define_static_multi", poly_idx__is_a_multi_assign_definition, get__true());
  define_attribute("compiler", "define_static_multi", poly_idx__is_a_static_definition, get__true());
  define_attribute("compiler", "define_static_multi", poly_idx__variable_kind_of, get__STATIC_MULTI());
  define_attribute("types", "grammar_node", poly_idx__is_a_dynamic_single_definition, get__false());
  define_attribute("compiler", "define_dynamic_single", poly_idx__is_a_dynamic_single_definition, get__true());
  define_attribute("compiler", "define_dynamic_single", poly_idx__is_a_single_assign_definition, get__true());
  define_attribute("compiler", "define_dynamic_single", poly_idx__is_a_dynamic_definition, get__true());
  define_attribute("compiler", "define_dynamic_single", poly_idx__variable_kind_of, get__DYNAMIC_SINGLE());
  define_attribute("types", "grammar_node", poly_idx__is_a_dynamic_multi_definition, get__false());
  define_attribute("compiler", "define_dynamic_multi", poly_idx__is_a_dynamic_multi_definition, get__true());
  define_attribute("compiler", "define_dynamic_multi", poly_idx__is_a_multi_assign_definition, get__true());
  define_attribute("compiler", "define_dynamic_multi", poly_idx__is_a_dynamic_definition, get__true());
  define_attribute("compiler", "define_dynamic_multi", poly_idx__variable_kind_of, get__DYNAMIC_MULTI());
  define_attribute("types", "grammar_node", poly_idx__is_a_function_call, get__false());
  define_attribute("compiler", "function_call", poly_idx__is_a_function_call, get__true());
  define_attribute("compiler", "function_call", poly_idx__is_a_method_definition, get__false());
  define_attribute("compiler", "function_call", poly_idx__is_an_attribute_access, get__false());
  define_attribute("compiler", "function_call", poly_idx__is_in_infix_notation, get__false());
  define_attribute("compiler", "function_call", poly_idx__is_a_string_template, get__false());
  define_attribute("compiler", "function_call", poly_idx__arguments_of, get__empty_list());
  define_attribute("types", "grammar_node", poly_idx__is_an_expression, get__false());
  define_attribute("compiler", "expression", poly_idx__is_an_expression, get__true());
  define_attribute("compiler", "expression", poly_idx__arguments_of, get__empty_list());
  define_attribute("compiler", "expression", poly_idx__operators_of, get__empty_list());
  define_attribute("compiler", "remark_argument", poly_idx__is_a_remark, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_a_backquoted_expression, get__false());
  define_attribute("compiler", "backquoted", poly_idx__is_a_backquoted_expression, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_an_attribute_value_pair, get__false());
  define_attribute("compiler", "attribute_value_pair", poly_idx__is_an_attribute_value_pair, get__true());
  define_attribute("compiler", "attribute_value_pair", poly_idx__arguments_of, get__empty_list());
  define_attribute("types", "grammar_node", poly_idx__is_an_attribute_function_pair, get__false());
  define_attribute("compiler", "attribute_function_pair", poly_idx__is_an_attribute_function_pair, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_a_numeric_literal, get__false());
  define_attribute("compiler", "numeric_literal", poly_idx__is_a_numeric_literal, get__true());
  define_attribute("compiler", "numeric_literal", poly_idx__is_a_constant, get__true());
  define_method("compiler", "numeric_literal", poly_idx__mangled_name_of, func__compiler__numeric_literal__mangled_name_of_1);
  define_attribute("types", "grammar_node", poly_idx__is_a_character_literal, get__false());
  define_attribute("compiler", "character_literal", poly_idx__is_a_character_literal, get__true());
  define_attribute("compiler", "character_literal", poly_idx__is_a_constant, get__true());
  define_attribute("compiler", "character_literal", poly_idx__is_in_numeric_notation, get__false());
  define_attribute("types", "grammar_node", poly_idx__is_a_string_literal, get__false());
  define_attribute("compiler", "string_literal", poly_idx__is_a_string_literal, get__true());
  define_attribute("compiler", "string_literal", poly_idx__is_a_constant, get__true());
  define_attribute("compiler", "string_literal", poly_idx__node__text_of, empty_string);
  define_attribute("compiler", "string_literal", poly_idx__arguments_of, get__empty_list());
  define_attribute("compiler", "multi_line_string", poly_idx__node__line_end_specifier_of, string__578a5af303e9ceb);
  define_attribute("compiler", "multi_line_string", poly_idx__node__last_line_end_specifier_of, string__578a5af303e9ceb);
  define_attribute("types", "grammar_node", poly_idx__is_a_unique_item_constant, get__false());
  define_attribute("compiler", "unique_item", poly_idx__is_a_unique_item_constant, get__true());
  define_attribute("compiler", "unique_item", poly_idx__is_a_constant, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_a_polymorphic_function_constant, get__false());
  define_attribute("compiler", "polymorphic_function", poly_idx__is_a_polymorphic_function_constant, get__true());
  define_attribute("compiler", "polymorphic_function", poly_idx__is_a_constant, get__true());
  define_attribute("compiler", "polymorphic_function", poly_idx__is_a_setter, get__false());
  define_attribute("compiler", "polymorphic_function_with_setter", poly_idx__is_a_setter, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_an_identifier, get__false());
  define_attribute("compiler", "identifier", poly_idx__is_an_identifier, get__true());
  define_attribute("compiler", "identifier", poly_idx__is_used_as_a_polymorphic_function, get__false());
  define_attribute("compiler", "identifier", poly_idx__is_used_as_a_destination, get__false());
  define_attribute("compiler", "identifier", poly_idx__is_not_used, get__false());
  define_method("compiler", "identifier", poly_idx__full_name_of, func__compiler__identifier__full_name_of_1);
  define_method("compiler", "identifier", poly_idx__mangled_name_of, func__compiler__identifier__mangled_name_of_1);
  define_attribute("types", "grammar_node", poly_idx__is_a_temporary, get__false());
  define_attribute("compiler", "temporary", poly_idx__is_a_temporary, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_an_operator_symbol, get__false());
  define_attribute("compiler", "operator_symbol", poly_idx__is_an_operator_symbol, get__true());
  define_attribute("types", "grammar_node", poly_idx__is_c_code, get__false());
  define_attribute("compiler", "c_code", poly_idx__is_c_code, get__true());
  define_attribute("compiler", "c_code", poly_idx__scope_of, string__545aebc3eac0d03b);
  define_attribute("compiler", "c_code", poly_idx__arguments_of, get__empty_list());
  define_attribute("types", "grammar_node", poly_idx__is_a_c_body, get__false());
  define_attribute("compiler", "c_body", poly_idx__is_a_c_body, get__true());
  define_attribute("compiler", "c_body", poly_idx__is_a_constant, get__true());
}

static int already_run_phase_5 = false;

EXPORT void phase_5__nodes(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.node__argument_of, create_function(type__node__argument_of, -1));
  assign_value(&var.node__arguments_of, create_function(type__node__arguments_of, -1));
  assign_value(&var.node__attribute_kind_of, create_function(type__node__attribute_kind_of, -1));
  assign_value(&var.node__attribute_of, create_function(type__node__attribute_of, -1));
  assign_value(&var.node__base_of, create_function(type__node__base_of, -1));
  assign_value(&var.node__default_value_of, create_function(type__node__default_value_of, -1));
  assign_value(&var.node__defined_names_of, create_function(type__node__defined_names_of, -1));
  assign_value(&var.node__definitions_of, create_function(type__node__definitions_of, -1));
  assign_value(&var.node__destination_of, create_function(type__node__destination_of, -1));
  assign_value(&var.node__end_position_of, create_function(type__node__end_position_of, -1));
  assign_value(&var.node__expression_of, create_function(type__node__expression_of, -1));
  assign_value(&var.node__filemask_of, create_function(type__node__filemask_of, -1));
  assign_value(&var.node__filename_of, create_function(type__node__filename_of, -1));
  assign_value(&var.node__fragment_of, create_function(type__node__fragment_of, -1));
  assign_value(&var.node__full_name_of, create_function(type__node__full_name_of, -1));
  assign_value(&var.node__functor_of, create_function(type__node__functor_of, -1));
  assign_value(&var.node__identifier_of, create_function(type__node__identifier_of, -1));
  assign_value(&var.node__inherited_names_of, create_function(type__node__inherited_names_of, -1));
  assign_value(&var.node__is_a_constant, create_function(type__node__is_a_constant, -1));
  assign_value(&var.node__is_a_dynamic_definition, create_function(type__node__is_a_dynamic_definition, -1));
  assign_value(&var.node__is_a_method_definition, create_function(type__node__is_a_method_definition, -1));
  assign_value(&var.node__is_a_multi_assign_definition, create_function(type__node__is_a_multi_assign_definition, -1));
  assign_value(&var.node__is_an_expanded_item, create_function(type__node__is_an_expanded_item, -1));
  assign_value(&var.node__is_an_optional_item, create_function(type__node__is_an_optional_item, -1));
  assign_value(&var.node__is_a_setter, create_function(type__node__is_a_setter, -1));
  assign_value(&var.node__is_a_single_assign_definition, create_function(type__node__is_a_single_assign_definition, -1));
  assign_value(&var.node__is_a_static_definition, create_function(type__node__is_a_static_definition, -1));
  assign_value(&var.node__is_a_string_template, create_function(type__node__is_a_string_template, -1));
  assign_value(&var.node__is_an_attribute_access, create_function(type__node__is_an_attribute_access, -1));
  assign_value(&var.node__is_an_initialization, create_function(type__node__is_an_initialization, -1));
  assign_value(&var.node__is_in_infix_notation, create_function(type__node__is_in_infix_notation, -1));
  assign_value(&var.node__is_in_numeric_notation, create_function(type__node__is_in_numeric_notation, -1));
  assign_value(&var.node__is_mutable, create_function(type__node__is_mutable, -1));
  assign_value(&var.node__is_not_used, create_function(type__node__is_not_used, -1));
  assign_value(&var.node__kind_of, create_function(type__node__kind_of, -1));
  assign_value(&var.node__last_line_end_specifier_of, create_function(type__node__last_line_end_specifier_of, -1));
  assign_value(&var.node__line_end_specifier_of, create_function(type__node__line_end_specifier_of, -1));
  assign_value(&var.node__lowest_precedence_of, create_function(type__node__lowest_precedence_of, -1));
  assign_value(&var.node__mangled_name_of, create_function(type__node__mangled_name_of, -1));
  assign_value(&var.node__max_length_of, create_function(type__node__max_length_of, -1));
  assign_value(&var.node__message_of, create_function(type__node__message_of, -1));
  assign_value(&var.node__name_of, create_function(type__node__name_of, -1));
  assign_value(&var.node__namespace_of, create_function(type__node__namespace_of, -1));
  assign_value(&var.node__namespace_alias_of, create_function(type__node__namespace_alias_of, -1));
  assign_value(&var.node__node_of, create_function(type__node__node_of, -1));
  assign_value(&var.node__operators_of, create_function(type__node__operators_of, -1));
  assign_value(&var.node__parameter_kind_of, create_function(type__node__parameter_kind_of, -1));
  assign_value(&var.node__parameters_of, create_function(type__node__parameters_of, -1));
  assign_value(&var.node__parent_of, create_function(type__node__parent_of, -1));
  assign_value(&var.node__result_count_of, create_function(type__node__result_count_of, -1));
  assign_value(&var.node__continuation_of, create_function(type__node__continuation_of, -1));
  assign_value(&var.node__source_position_of, create_function(type__node__source_position_of, -1));
  assign_value(&var.node__temporary_count_of, create_function(type__node__temporary_count_of, -1));
  assign_value(&var.node__remark_lines_of, create_function(type__node__remark_lines_of, -1));
  assign_value(&var.node__scope_of, create_function(type__node__scope_of, -1));
  assign_value(&var.node__section_of, create_function(type__node__section_of, -1));
  assign_value(&var.node__statements_of, create_function(type__node__statements_of, -1));
  assign_value(&var.node__submodule_no_of, create_function(type__node__submodule_no_of, -1));
  assign_value(&var.node__text_of, create_function(type__node__text_of, -1));
  assign_value(&var.node__type_of, create_function(type__node__type_of, -1));
  assign_value(&var.node__used_names_of, create_function(type__node__used_names_of, -1));
  assign_value(&var.node__value_of, create_function(type__node__value_of, -1));
  assign_value(&var.node__variable_kind_of, create_function(type__node__variable_kind_of, -1));
  assign_value(&var.node__is_a_meta_instruction, create_function(type__node__is_a_meta_instruction, -1));
  assign_value(&var.compiler__meta_instruction, get__types__grammar_node());
  assign_variable(&var.compiler__require_instruction, &var.compiler__meta_instruction);
  assign_variable(&var.compiler__namespace_instruction, &var.compiler__meta_instruction);
  assign_variable(&var.compiler__using_instruction, &var.compiler__meta_instruction);
  assign_variable(&var.compiler__include_instruction, &var.compiler__meta_instruction);
  assign_variable(&var.compiler__link_instruction, &var.compiler__meta_instruction);
  assign_variable(&var.compiler__data_instruction, &var.compiler__meta_instruction);
  assign_value(&var.node__is_a_remark, create_function(type__node__is_a_remark, -1));
  assign_variable(&var.compiler__remark_statement, &var.compiler__statement);
  assign_value(&var.node__is_a_body, create_function(type__node__is_a_body, -1));
  assign_value(&var.node__defines_a_dynamic, create_function(type__node__defines_a_dynamic, -1));
  assign_value(&var.compiler__body, get__types__grammar_node());
  assign_value(&var.compiler__statement, get__types__grammar_node());
  assign_value(&var.node__is_a_call, create_function(type__node__is_a_call, -1));
  assign_variable(&var.compiler__call, &var.compiler__statement);
  assign_value(&var.node__is_a_procedure_call, create_function(type__node__is_a_procedure_call, -1));
  assign_variable(&var.compiler__procedure_call, &var.compiler__call);
  assign_value(&var.node__is_a_return, create_function(type__node__is_a_return, -1));
  assign_variable(&var.compiler__return_statement, &var.compiler__call);
  assign_value(&var.node__is_an_assignment, create_function(type__node__is_an_assignment, -1));
  assign_variable(&var.compiler__assignment, &var.compiler__call);
  assign_value(&var.node__is_a_definition, create_function(type__node__is_a_definition, -1));
  assign_value(&var.node__is_a_destination, create_function(type__node__is_a_destination, -1));
  assign_value(&var.node__is_an_input_output_argument, create_function(type__node__is_an_input_output_argument, -1));
  assign_value(&var.compiler__definition, get__types__grammar_node());
  assign_value(&var.node__is_a_static_single_definition, create_function(type__node__is_a_static_single_definition, -1));
  assign_variable(&var.compiler__define_static_single, &var.compiler__definition);
  assign_value(&var.node__is_a_static_multi_definition, create_function(type__node__is_a_static_multi_definition, -1));
  assign_variable(&var.compiler__define_static_multi, &var.compiler__definition);
  assign_value(&var.node__is_a_dynamic_single_definition, create_function(type__node__is_a_dynamic_single_definition, -1));
  assign_variable(&var.compiler__define_dynamic_single, &var.compiler__definition);
  assign_value(&var.node__is_a_dynamic_multi_definition, create_function(type__node__is_a_dynamic_multi_definition, -1));
  assign_variable(&var.compiler__define_dynamic_multi, &var.compiler__definition);
  assign_value(&var.node__is_a_function_call, create_function(type__node__is_a_function_call, -1));
  assign_value(&var.compiler__function_call, get__types__grammar_node());
  assign_value(&var.node__is_an_expression, create_function(type__node__is_an_expression, -1));
  assign_value(&var.compiler__expression, get__types__grammar_node());
  assign_value(&var.compiler__remark_argument, get__types__grammar_node());
  assign_value(&var.node__is_a_backquoted_expression, create_function(type__node__is_a_backquoted_expression, -1));
  assign_value(&var.compiler__backquoted, get__types__grammar_node());
  assign_value(&var.node__is_an_attribute_value_pair, create_function(type__node__is_an_attribute_value_pair, -1));
  assign_value(&var.compiler__attribute_value_pair, get__types__grammar_node());
  assign_value(&var.node__is_an_attribute_function_pair, create_function(type__node__is_an_attribute_function_pair, -1));
  assign_variable(&var.compiler__attribute_function_pair, &var.compiler__attribute_value_pair);
  assign_value(&var.node__is_a_numeric_literal, create_function(type__node__is_a_numeric_literal, -1));
  assign_value(&var.compiler__numeric_literal, get__types__grammar_node());
  assign_value(&var.node__is_a_character_literal, create_function(type__node__is_a_character_literal, -1));
  assign_value(&var.compiler__character_literal, get__types__grammar_node());
  assign_value(&var.node__is_a_string_literal, create_function(type__node__is_a_string_literal, -1));
  assign_value(&var.compiler__string_literal, get__types__grammar_node());
  assign_variable(&var.compiler__multi_line_string, &var.compiler__string_literal);
  assign_value(&var.node__is_a_unique_item_constant, create_function(type__node__is_a_unique_item_constant, -1));
  assign_value(&var.compiler__unique_item, get__types__grammar_node());
  assign_value(&var.node__is_a_polymorphic_function_constant, create_function(type__node__is_a_polymorphic_function_constant, -1));
  assign_value(&var.compiler__polymorphic_function, get__types__grammar_node());
  assign_variable(&var.compiler__polymorphic_function_with_setter, &var.compiler__polymorphic_function);
  assign_value(&var.node__is_an_identifier, create_function(type__node__is_an_identifier, -1));
  assign_value(&var.node__is_used_as_a_polymorphic_function, create_function(type__node__is_used_as_a_polymorphic_function, -1));
  assign_value(&var.node__is_used_as_a_destination, create_function(type__node__is_used_as_a_destination, -1));
  assign_value(&var.compiler__identifier, get__types__grammar_node());
  assign_value(&var.node__is_a_temporary, create_function(type__node__is_a_temporary, -1));
  assign_variable(&var.compiler__temporary, &var.compiler__identifier);
  assign_value(&var.node__is_an_operator_symbol, create_function(type__node__is_an_operator_symbol, -1));
  assign_variable(&var.compiler__operator_symbol, &var.compiler__identifier);
  assign_value(&var.node__is_c_code, create_function(type__node__is_c_code, -1));
  assign_value(&var.compiler__c_code, get__types__grammar_node());
  assign_value(&var.node__is_a_c_body, create_function(type__node__is_a_c_body, -1));
  assign_variable(&var.compiler__c_body, &var.compiler__c_code);
  assign_variable(&var.compiler__is_a_parameter, &func__compiler__is_a_parameter_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__nodes(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__nodes);
}
