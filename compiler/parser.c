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
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
IMPORT NODE *get_dynamic_slot(int id);
IMPORT void define_dynamic_slot(int id, NODE *node);
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
REGISTER FUNC func ASM("r14");
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
REGISTER int argument_count ASM("ebx");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *undefined;
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *clone_object_and_attributes(NODE *node);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT void *update_start_p;
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT NODE *create_future(void);
IMPORT NODE *empty_string;
IMPORT NODE *create_cell(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_continuation_with_exit(FUNC exit_func);
IMPORT void continuation_type_function(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void register_dynamic(int *id_p);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void def_attribute(NODE **var_p, int idx, void *attr);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void maybe_initialize_future(NODE *var, NODE *val);
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
static NODE_GETTER get__ATTRIBUTE_KIND;
static NODE_GETTER get_value_or_future__ATTRIBUTE_KIND;
static NODE_GETTER get__CONTINUATION_PARAMETER;
static NODE_GETTER get_value_or_future__CONTINUATION_PARAMETER;
static NODE_GETTER get__DIGIT;
static NODE_GETTER get_value_or_future__DIGIT;
static NODE_GETTER get__END_OF_TEXT;
static NODE_GETTER get_value_or_future__END_OF_TEXT;
static NODE_GETTER get__INFIX_PRECEDENCE;
static NODE_GETTER get_value_or_future__INFIX_PRECEDENCE;
static NODE_GETTER get__IN_OUT_PARAMETER;
static NODE_GETTER get_value_or_future__IN_OUT_PARAMETER;
static NODE_GETTER get__IN_PARAMETER;
static NODE_GETTER get_value_or_future__IN_PARAMETER;
static NODE_GETTER get__LETTER;
static NODE_GETTER get_value_or_future__LETTER;
static NODE_GETTER get__METHOD_KIND;
static NODE_GETTER get_value_or_future__METHOD_KIND;
static NODE_GETTER get__MYSELF_PARAMETER;
static NODE_GETTER get_value_or_future__MYSELF_PARAMETER;
static NODE_GETTER get__NAME;
static NODE_GETTER get_value_or_future__NAME;
static NODE_GETTER get__NONE;
static NODE_GETTER get_value_or_future__NONE;
static NODE_GETTER get__OUT_PARAMETER;
static NODE_GETTER get_value_or_future__OUT_PARAMETER;
static NODE_GETTER get__POLYMORPHIC;
static NODE_GETTER get_value_or_future__POLYMORPHIC;
static NODE_GETTER get__PRINTABLE_CHARACTER;
static NODE_GETTER get_value_or_future__PRINTABLE_CHARACTER;
static NODE_GETTER get__SyntaxError;
static NODE_GETTER get_value_or_future__SyntaxError;
static NODE_GETTER get__all_of;
static NODE_GETTER get_value_or_future__all_of;
static NODE_GETTER get__alt;
static NODE_GETTER get_value_or_future__alt;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static int poly_idx__arguments_of;
static NODE_GETTER get__arguments_of;
static NODE_GETTER get__arguments_span;
static NODE_GETTER get_value_or_future__arguments_span;
static NODE_GETTER get__assignment;
static NODE_GETTER get_value_or_future__assignment;
static NODE_GETTER get__attribute_function_pair;
static NODE_GETTER get_value_or_future__attribute_function_pair;
static NODE_GETTER get__attribute_kind_of;
static NODE_GETTER get_value_or_future__attribute_kind_of;
static int poly_idx__attribute_of;
static NODE_GETTER get__attribute_of;
static NODE_GETTER get__attribute_value_pair;
static NODE_GETTER get_value_or_future__attribute_value_pair;
static NODE_GETTER get__backquoted;
static NODE_GETTER get_value_or_future__backquoted;
static NODE_GETTER get__base_of;
static NODE_GETTER get_value_or_future__base_of;
static NODE_GETTER get__behind;
static NODE_GETTER get_value_or_future__behind;
static NODE_GETTER get__body;
static NODE_GETTER get_value_or_future__body;
static NODE_GETTER get__c_body;
static NODE_GETTER get_value_or_future__c_body;
static NODE_GETTER get__c_code;
static NODE_GETTER get_value_or_future__c_code;
static NODE_GETTER get__capture;
static NODE_GETTER get_value_or_future__capture;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__character;
static NODE_GETTER get_value_or_future__character;
static NODE_GETTER get__character_literal;
static NODE_GETTER get_value_or_future__character_literal;
static NODE_GETTER get__character_names;
static NODE_GETTER get_value_or_future__character_names;
static NODE_GETTER get__check_node;
static NODE_GETTER get_value_or_future__check_node;
static NODE_GETTER get__compiler__current_fragment;
static NODE_SETTER define__compiler__current_fragment;
static NODE_GETTER get__compiler__source_of;
static NODE_GETTER get_value_or_future__compiler__source_of;
static NODE_GETTER get__compiler__text_of;
static NODE_GETTER get_value_or_future__compiler__text_of;
static NODE_GETTER get__continuation_of;
static NODE_GETTER get_value_or_future__continuation_of;
static NODE_GETTER get__count_occurrences;
static NODE_GETTER get_value_or_future__count_occurrences;
static NODE_GETTER get__current_fragment;
static NODE_GETTER get_value_or_future__current_fragment;
static NODE_GETTER get__data_instruction;
static NODE_GETTER get_value_or_future__data_instruction;
static NODE_GETTER get__dec;
static NODE_GETTER get_value_or_future__dec;
static NODE_GETTER get__default_value_of;
static NODE_GETTER get_value_or_future__default_value_of;
static NODE_GETTER get__define_dynamic_multi;
static NODE_GETTER get_value_or_future__define_dynamic_multi;
static NODE_GETTER get__define_dynamic_single;
static NODE_GETTER get_value_or_future__define_dynamic_single;
static NODE_GETTER get__define_static_multi;
static NODE_GETTER get_value_or_future__define_static_multi;
static NODE_GETTER get__define_static_single;
static NODE_GETTER get_value_or_future__define_static_single;
static int poly_idx__defined_names_of;
static NODE_GETTER get__defined_names_of;
static NODE_GETTER get__defined_namespaces;
static NODE_SETTER set__defined_namespaces;
static NODE_GETTER get__dependent_data;
static NODE_SETTER set__dependent_data;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__do_extract_documentation;
static NODE_GETTER get_value_or_future__do_extract_documentation;
static NODE_GETTER get__do_pretty_print;
static NODE_GETTER get_value_or_future__do_pretty_print;
static NODE_GETTER get__do_show_brief_messages;
static NODE_GETTER get_value_or_future__do_show_brief_messages;
static NODE_GETTER get__dup;
static NODE_GETTER get_value_or_future__dup;
static NODE_GETTER get__edump;
static NODE_GETTER get_value_or_future__edump;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static int poly_idx__end_position_of;
static NODE_GETTER get__end_position_of;
static NODE_GETTER get__eprint_source;
static NODE_GETTER get_value_or_future__eprint_source;
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__ewriteln;
static NODE_GETTER get_value_or_future__ewriteln;
static NODE_GETTER get__exit;
static NODE_GETTER get_value_or_future__exit;
static NODE_GETTER get__expression;
static NODE_GETTER get_value_or_future__expression;
static int poly_idx__expression_of;
static NODE_GETTER get__expression_of;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__followed_by;
static NODE_GETTER get_value_or_future__followed_by;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__for_each_from_to;
static NODE_GETTER get_value_or_future__for_each_from_to;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static int poly_idx__fragment_of;
static NODE_GETTER get__fragment_of;
static NODE_GETTER get__from_to;
static NODE_GETTER get_value_or_future__from_to;
static NODE_GETTER get__function_call;
static NODE_GETTER get_value_or_future__function_call;
static int poly_idx__functor_of;
static NODE_GETTER get__functor_of;
static NODE_GETTER get__grammar__current_node;
static NODE_GETTER get_value_or_future__grammar__current_node;
static int poly_idx__grammar__match;
static NODE_GETTER get__grammar__match;
static NODE_GETTER get__identifier;
static NODE_GETTER get_value_or_future__identifier;
static int poly_idx__identifier_of;
static NODE_GETTER get__identifier_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__include_instruction;
static NODE_GETTER get_value_or_future__include_instruction;
static NODE_GETTER get__included_files;
static NODE_SETTER set__included_files;
static NODE_GETTER get__indent_marker;
static NODE_GETTER get_value_or_future__indent_marker;
static int poly_idx__inherited_names_of;
static NODE_GETTER get__inherited_names_of;
static NODE_GETTER get__inspect_node;
static NODE_GETTER get_value_or_future__inspect_node;
static NODE_GETTER get__is_a_backquoted_expression;
static NODE_GETTER get_value_or_future__is_a_backquoted_expression;
static NODE_GETTER get__is_a_character;
static NODE_GETTER get_value_or_future__is_a_character;
static NODE_GETTER get__is_a_destination;
static NODE_GETTER get_value_or_future__is_a_destination;
static NODE_GETTER get__is_a_function_call;
static NODE_GETTER get_value_or_future__is_a_function_call;
static NODE_GETTER get__is_a_letter;
static NODE_GETTER get_value_or_future__is_a_letter;
static int poly_idx__is_a_method_definition;
static NODE_GETTER get__is_a_method_definition;
static NODE_GETTER get__is_a_polymorphic_function_constant;
static NODE_GETTER get_value_or_future__is_a_polymorphic_function_constant;
static NODE_GETTER get__is_a_remark;
static NODE_GETTER get_value_or_future__is_a_remark;
static NODE_GETTER get__is_a_return;
static NODE_GETTER get_value_or_future__is_a_return;
static NODE_GETTER get__is_a_static_single_definition;
static NODE_GETTER get_value_or_future__is_a_static_single_definition;
static NODE_GETTER get__is_a_string;
static NODE_GETTER get_value_or_future__is_a_string;
static int poly_idx__is_a_string_template;
static NODE_GETTER get__is_a_string_template;
static int poly_idx__is_an_attribute_access;
static NODE_GETTER get__is_an_attribute_access;
static NODE_GETTER get__is_an_attribute_value_pair;
static NODE_GETTER get_value_or_future__is_an_attribute_value_pair;
static NODE_GETTER get__is_an_expanded_item;
static NODE_GETTER get_value_or_future__is_an_expanded_item;
static NODE_GETTER get__is_an_identifier;
static NODE_GETTER get_value_or_future__is_an_identifier;
static NODE_GETTER get__is_an_input_output_argument;
static NODE_GETTER get_value_or_future__is_an_input_output_argument;
static NODE_GETTER get__is_an_optional_item;
static NODE_GETTER get_value_or_future__is_an_optional_item;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static int poly_idx__is_in_infix_notation;
static NODE_GETTER get__is_in_infix_notation;
static int poly_idx__is_in_numeric_notation;
static NODE_GETTER get__is_in_numeric_notation;
static NODE_GETTER get__is_left_associative;
static NODE_GETTER get_value_or_future__is_left_associative;
static int poly_idx__is_not_used;
static NODE_GETTER get__is_not_used;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__is_used_as_a_destination;
static NODE_GETTER get_value_or_future__is_used_as_a_destination;
static NODE_GETTER get__is_used_as_a_polymorphic_function;
static NODE_GETTER get_value_or_future__is_used_as_a_polymorphic_function;
static NODE_GETTER get__kind_of;
static NODE_GETTER get_value_or_future__kind_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__line_end_specifier_of;
static NODE_GETTER get_value_or_future__line_end_specifier_of;
static NODE_GETTER get__line_no_of;
static NODE_GETTER get_value_or_future__line_no_of;
static NODE_GETTER get__link_instruction;
static NODE_GETTER get_value_or_future__link_instruction;
static NODE_GETTER get__linked_libraries;
static NODE_SETTER set__linked_libraries;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static int poly_idx__lowest_precedence_of;
static NODE_GETTER get__lowest_precedence_of;
static NODE_GETTER get__many;
static NODE_GETTER get_value_or_future__many;
static NODE_GETTER get__match;
static NODE_GETTER get_value_or_future__match;
static int poly_idx__message_of;
static NODE_GETTER get__message_of;
static NODE_GETTER get__modify_node;
static NODE_GETTER get_value_or_future__modify_node;
static NODE_GETTER get__module_name;
static NODE_GETTER get_value_or_future__module_name;
static NODE_GETTER get__multi_capture;
static NODE_GETTER get_value_or_future__multi_capture;
static NODE_GETTER get__multi_line_string;
static NODE_GETTER get_value_or_future__multi_line_string;
static NODE_GETTER get__multi_span;
static NODE_GETTER get_value_or_future__multi_span;
static int poly_idx__name_of;
static NODE_GETTER get__name_of;
static int poly_idx__namespace_alias_of;
static NODE_GETTER get__namespace_alias_of;
static NODE_GETTER get__namespace_instruction;
static NODE_GETTER get_value_or_future__namespace_instruction;
static NODE_GETTER get__namespace_mappings;
static NODE_SETTER set__namespace_mappings;
static int poly_idx__namespace_of;
static NODE_GETTER get__namespace_of;
static NODE_GETTER get__newline;
static NODE_GETTER get_value_or_future__newline;
static NODE_GETTER get__node__filemask_of;
static NODE_GETTER get_value_or_future__node__filemask_of;
static NODE_GETTER get__node__filename_of;
static NODE_GETTER get_value_or_future__node__filename_of;
static NODE_GETTER get__node__scope_of;
static NODE_GETTER get_value_or_future__node__scope_of;
static int poly_idx__node__text_of;
static NODE_GETTER get__node__text_of;
static NODE_GETTER get__node__type_of;
static NODE_GETTER get_value_or_future__node__type_of;
static int poly_idx__node__value_of;
static NODE_GETTER get__node__value_of;
static NODE_GETTER get__node_of;
static NODE_GETTER get_value_or_future__node_of;
static NODE_GETTER get__not;
static NODE_GETTER get_value_or_future__not;
static NODE_GETTER get__not_followed_by;
static NODE_GETTER get_value_or_future__not_followed_by;
static NODE_GETTER get__numeric_literal;
static NODE_GETTER get_value_or_future__numeric_literal;
static NODE_GETTER get__operator_symbol;
static NODE_GETTER get_value_or_future__operator_symbol;
static NODE_GETTER get__operators_of;
static NODE_GETTER get_value_or_future__operators_of;
static NODE_GETTER get__optional;
static NODE_GETTER get_value_or_future__optional;
static NODE_GETTER get__outdent_marker;
static NODE_GETTER get_value_or_future__outdent_marker;
static NODE_GETTER get__parameter_kind_of;
static NODE_GETTER get_value_or_future__parameter_kind_of;
static int poly_idx__parameters_of;
static NODE_GETTER get__parameters_of;
static int poly_idx__parent_of;
static NODE_GETTER get__parent_of;
static NODE_GETTER get__peek;
static NODE_GETTER get_value_or_future__peek;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static NODE_GETTER get__polymorphic_function;
static NODE_GETTER get_value_or_future__polymorphic_function;
static NODE_GETTER get__polymorphic_function_with_setter;
static NODE_GETTER get_value_or_future__polymorphic_function_with_setter;
static NODE_GETTER get__pop;
static NODE_GETTER get_value_or_future__pop;
static NODE_GETTER get__precedence;
static NODE_GETTER get_value_or_future__precedence;
static NODE_GETTER get__procedure_call;
static NODE_GETTER get_value_or_future__procedure_call;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__put;
static NODE_GETTER get_value_or_future__put;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__remark_argument;
static NODE_GETTER get_value_or_future__remark_argument;
static int poly_idx__remark_lines_of;
static NODE_GETTER get__remark_lines_of;
static NODE_GETTER get__remark_statement;
static NODE_GETTER get_value_or_future__remark_statement;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static NODE_GETTER get__require_instruction;
static NODE_GETTER get_value_or_future__require_instruction;
static NODE_GETTER get__required_modules;
static NODE_SETTER set__required_modules;
static NODE_GETTER get__result_count_of;
static NODE_GETTER get_value_or_future__result_count_of;
static NODE_GETTER get__return_statement;
static NODE_GETTER get_value_or_future__return_statement;
static NODE_GETTER get__sequence;
static NODE_GETTER get_value_or_future__sequence;
static NODE_GETTER get__set_field;
static NODE_GETTER get_value_or_future__set_field;
static NODE_GETTER get__set_node;
static NODE_GETTER get_value_or_future__set_node;
static NODE_GETTER get__some;
static NODE_GETTER get_value_or_future__some;
static NODE_GETTER get__source_of;
static NODE_GETTER get_value_or_future__source_of;
static int poly_idx__source_position_of;
static NODE_GETTER get__source_position_of;
static NODE_GETTER get__span;
static NODE_GETTER get_value_or_future__span;
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
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__std__value_range;
static NODE_GETTER get_value_or_future__std__value_range;
static NODE_GETTER get__std_identifier;
static NODE_GETTER get_value_or_future__std_identifier;
static NODE_GETTER get__string_literal;
static NODE_GETTER get_value_or_future__string_literal;
static NODE_GETTER get__strip;
static NODE_GETTER get_value_or_future__strip;
static NODE_GETTER get__table;
static NODE_GETTER get_value_or_future__table;
static NODE_GETTER get__to_integer;
static NODE_GETTER get_value_or_future__to_integer;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static NODE_GETTER get__to_upper_case;
static NODE_GETTER get_value_or_future__to_upper_case;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__truncate_behind;
static NODE_GETTER get_value_or_future__truncate_behind;
static NODE_GETTER get__truncate_from;
static NODE_GETTER get_value_or_future__truncate_from;
static NODE_GETTER get__types__grammar_object;
static NODE_GETTER get_value_or_future__types__grammar_object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unique_item;
static NODE_GETTER get_value_or_future__unique_item;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__update_each;
static NODE_GETTER get_value_or_future__update_each;
static int poly_idx__used_names_of;
static NODE_GETTER get__used_names_of;
static NODE_GETTER get__used_namespaces;
static NODE_SETTER set__used_namespaces;
static NODE_GETTER get__using_instruction;
static NODE_GETTER get_value_or_future__using_instruction;
static int poly_idx__variable_kind_of;
static NODE_GETTER get__variable_kind_of;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *_print_message;
  NODE *_ExitWithSyntaxError;
  NODE *_ParseError;
  NODE *_syntax_error;
  NODE *_unexpected_input_error;
  NODE *_dump_stream;
  NODE *_dump;
  NODE *_dump3;
  NODE *_dump5;
  NODE *_precedence_table;
  NODE *_is_right_associative;
  NODE *_infix_operator;
  NODE *_interleaved;
  NODE *_store_arguments_index;
  NODE *_inline;
  NODE *_NOT_INLINE;
  NODE *_NEWLINE;
  NODE *_INDENT;
  NODE *_OUTDENT;
  NODE *_HASHTAG;
  NODE *_expect;
  NODE *_SEPARATOR;
  NODE *_NEWLINES;
  NODE *_STORE_POSITION;
  NODE *_STORE_POSITION_MINUS_1;
  NODE *_STORE_END_POSITION;
  NODE *_IDENTIFIER;
  NODE *_DEFINE_IDENTIFIER;
  NODE *_NAMESPACED_IDENTIFIER;
  NODE *_FILENAME;
  NODE *_REQUIRE;
  NODE *_NAMESPACE;
  NODE *_USING;
  NODE *_BASENAME;
  NODE *_C_FILENAME;
  NODE *_INCLUDE;
  NODE *_LINK;
  NODE *_MASK;
  NODE *_FILEMASK;
  NODE *_DATA;
  NODE *_META_INSTRUCTION;
  NODE *_REMARK_LINE;
  NODE *_REMARK_LINES;
  NODE *_REMARK_STATEMENT;
  NODE *_REMARK;
  NODE *_LINE_END_REMARK;
  NODE *_NEXT_LINE_REMARK;
  NODE *_REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING;
  NODE *_REMARK_ARGUMENT;
  NODE *_LINE_END_REMARK_ARGUMENT;
  NODE *_FUNCTION_CALL;
  NODE *_MAKE_ATTRIBUTE_ACCESS;
  NODE *_ATTRIBUTE_ACCESS;
  NODE *_ATTRIBUTE_WRITE;
  NODE *_EXTENSIONS;
  NODE *_READ_WRITE_EXTENSIONS;
  NODE *_IDENTIFIER_OR_FUNCTION_CALL;
  NODE *_READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL;
  NODE *_DECIMAL_NUMBER;
  NODE *_BINARY_DIGIT;
  NODE *_BINARY_NUMBER;
  NODE *_OCTAL_DIGIT;
  NODE *_OCTAL_NUMBER;
  NODE *_HEX_DIGIT;
  NODE *_HEX_NUMBER;
  NODE *_NUMBER;
  NODE *_SIMPLE_CHARACTER;
  NODE *_AT_CHARACTER;
  NODE *_NAMED_CHARACTER;
  NODE *_NUMERIC_CHARACTER;
  NODE *_SPECIAL_CHARACTER;
  NODE *_CHARACTER_SYMBOL;
  NODE *_CHARACTER;
  NODE *_STRING_CHARACTER;
  NODE *_STRING_INSERTION;
  NODE *_CHECK_INSERTIONS;
  NODE *_STRING;
  NODE *_STRING_LINE;
  NODE *_ADD_LINE_END;
  NODE *_MULTI_LINE_STRING;
  NODE *_UNIQUE_ITEM;
  NODE *_PARENTHESED_EXPRESSION;
  NODE *_OPTION;
  NODE *_NEGATION;
  NODE *_SIMPLE_OPERAND;
  NODE *_OPERAND;
  NODE *_INFIX_OPERATOR_SYMBOL;
  NODE *_SYMBOLIC_OPERATOR;
  NODE *_COMMA_OPERATOR;
  NODE *_NAMED_OPERATOR;
  NODE *_INFIX_OPERATOR;
  NODE *_EXTEND_EXPRESSION;
  NODE *_EXPRESSION;
  NODE *_DEFINED_VARIABLE;
  NODE *_NAME_OF_POLYMORPHIC;
  NODE *_DEFINED_VARIABLE_OR_ATTRIBUTE;
  NODE *_DEFINE_STATIC_SINGLE;
  NODE *_DEFINE_STATIC_MULTI;
  NODE *_DEFINE_DYNAMIC_SINGLE;
  NODE *_DEFINE_DYNAMIC_MULTI;
  NODE *_METHOD_DEFINITION;
  NODE *_ASSIGN;
  NODE *_DESTINATION;
  NODE *_BACKQUOTED;
  NODE *_EXPANSION;
  NODE *_OUTPUT_ARGUMENT;
  NODE *_INPUT_OUTPUT_ARGUMENT;
  NODE *_INPUT_ARGUMENT;
  NODE *_VALUE_ARGUMENT;
  NODE *_ATTRIBUTE_VALUE_PAIR;
  NODE *_OPERATORS_AND_OPERANDS;
  NODE *_MULTI_LINE_EXPRESSION;
  NODE *_PARAMETER_MODE;
  NODE *_PARAMETER_COUNT_OR_MYSELF;
  NODE *_NOT_USED;
  NODE *_PARAMETER_NAME;
  NODE *_PARAMETER;
  NODE *_MULTI_LINE_PARAMETER;
  NODE *_CONTINUATION;
  NODE *_MULTI_LINE_CONTINUATION;
  NODE *_INLINE_PARAMETERS;
  NODE *_MULTI_LINE_PARAMETERS;
  NODE *_COMPLETE_BODY;
  NODE *_RETURN_EXPRESSION;
  NODE *_BODY;
  NODE *_C_BODY;
  NODE *_LINE_END_EXPRESSION;
  NODE *_POLYMORPHIC_FUNCTION_WITHOUT_SETTER;
  NODE *_POLYMORPHIC_FUNCTION_WITH_SETTER;
  NODE *_POLYMORPHIC_FUNCTION;
  NODE *_FUNCTOR;
  NODE *_RESULT_COUNT_OR_CONTINUATION;
  NODE *_ARGUMENT;
  NODE *_FIRST_LINE_ARGUMENTS;
  NODE *_MULTI_LINE_FUNCTION_CALL;
  NODE *_ARGUMENT_LINE;
  NODE *_INLINE_ARGUMENTS;
  NODE *_INDENTED_ARGUMENTS;
  NODE *_ARGUMENTS;
  NODE *_ONE_OR_MORE;
  NODE *_check_functor;
  NODE *_check_arguments;
  NODE *_CHECK_ARGUMENTS;
  NODE *_ASSIGNMENT_STATEMENT;
  NODE *_PROCEDURE_STATEMENT;
  NODE *_RETURN_STATEMENT;
  NODE *_STATEMENT;
  NODE *_STATEMENTS;
  NODE *_BUILTIN_NAME;
  NODE *_C_EXPRESSION;
  NODE *_ARGUMENT_ANNOTATION;
  NODE *_BASE_ANNOTATION;
  NODE *_KIND_ANNOTATION;
  NODE *_NAME_ANNOTATION;
  NODE *_NODE_ANNOTATION;
  NODE *_SCOPE_ANNOTATION;
  NODE *_TYPE_ANNOTATION;
  NODE *_ANNOTATION_ITEM;
  NODE *_ANNOTATION;
  NODE *_ANNOTATIONS;
  NODE *_C_CODE_REMARK;
  NODE *_C_CODE_REMARKS;
  NODE *_SOURCE;
  NODE *_C_CODE;
  NODE *_META_FRAGMENT;
  NODE *_FRAGMENT;
  NODE *compiler__std_identifier;
  NODE *compiler__Warning;
  NODE *compiler__SyntaxError;
  NODE *types__syntax_error;
  NODE *types__unexpected_input_error;
  NODE *compiler__strip;
  NODE *compiler__HIGHEST_PRECEDENCE;
  NODE *compiler__INFIX_PRECEDENCE;
  NODE *compiler__precedence;
  NODE *compiler__is_left_associative;
  NODE *types__store_arguments_index;
  NODE *types__inline;
  NODE *compiler__arguments_span;
  NODE *compiler__WHITESPACE;
  NODE *compiler__parse_meta_instruction;
  NODE *compiler__parse_statement;
} var;
static const char *var_names[] = {
  "print_message",
  "ExitWithSyntaxError",
  "ParseError",
  "syntax_error",
  "unexpected_input_error",
  "dump_stream",
  "dump",
  "dump3",
  "dump5",
  "precedence_table",
  "is_right_associative",
  "infix_operator",
  "interleaved",
  "store_arguments_index",
  "inline",
  "NOT_INLINE",
  "NEWLINE",
  "INDENT",
  "OUTDENT",
  "HASHTAG",
  "expect",
  "SEPARATOR",
  "NEWLINES",
  "STORE_POSITION",
  "STORE_POSITION_MINUS_1",
  "STORE_END_POSITION",
  "IDENTIFIER",
  "DEFINE_IDENTIFIER",
  "NAMESPACED_IDENTIFIER",
  "FILENAME",
  "REQUIRE",
  "NAMESPACE",
  "USING",
  "BASENAME",
  "C_FILENAME",
  "INCLUDE",
  "LINK",
  "MASK",
  "FILEMASK",
  "DATA",
  "META_INSTRUCTION",
  "REMARK_LINE",
  "REMARK_LINES",
  "REMARK_STATEMENT",
  "REMARK",
  "LINE_END_REMARK",
  "NEXT_LINE_REMARK",
  "REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING",
  "REMARK_ARGUMENT",
  "LINE_END_REMARK_ARGUMENT",
  "FUNCTION_CALL",
  "MAKE_ATTRIBUTE_ACCESS",
  "ATTRIBUTE_ACCESS",
  "ATTRIBUTE_WRITE",
  "EXTENSIONS",
  "READ_WRITE_EXTENSIONS",
  "IDENTIFIER_OR_FUNCTION_CALL",
  "READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL",
  "DECIMAL_NUMBER",
  "BINARY_DIGIT",
  "BINARY_NUMBER",
  "OCTAL_DIGIT",
  "OCTAL_NUMBER",
  "HEX_DIGIT",
  "HEX_NUMBER",
  "NUMBER",
  "SIMPLE_CHARACTER",
  "AT_CHARACTER",
  "NAMED_CHARACTER",
  "NUMERIC_CHARACTER",
  "SPECIAL_CHARACTER",
  "CHARACTER_SYMBOL",
  "CHARACTER",
  "STRING_CHARACTER",
  "STRING_INSERTION",
  "CHECK_INSERTIONS",
  "STRING",
  "STRING_LINE",
  "ADD_LINE_END",
  "MULTI_LINE_STRING",
  "UNIQUE_ITEM",
  "PARENTHESED_EXPRESSION",
  "OPTION",
  "NEGATION",
  "SIMPLE_OPERAND",
  "OPERAND",
  "INFIX_OPERATOR_SYMBOL",
  "SYMBOLIC_OPERATOR",
  "COMMA_OPERATOR",
  "NAMED_OPERATOR",
  "INFIX_OPERATOR",
  "EXTEND_EXPRESSION",
  "EXPRESSION",
  "DEFINED_VARIABLE",
  "NAME_OF_POLYMORPHIC",
  "DEFINED_VARIABLE_OR_ATTRIBUTE",
  "DEFINE_STATIC_SINGLE",
  "DEFINE_STATIC_MULTI",
  "DEFINE_DYNAMIC_SINGLE",
  "DEFINE_DYNAMIC_MULTI",
  "METHOD_DEFINITION",
  "ASSIGN",
  "DESTINATION",
  "BACKQUOTED",
  "EXPANSION",
  "OUTPUT_ARGUMENT",
  "INPUT_OUTPUT_ARGUMENT",
  "INPUT_ARGUMENT",
  "VALUE_ARGUMENT",
  "ATTRIBUTE_VALUE_PAIR",
  "OPERATORS_AND_OPERANDS",
  "MULTI_LINE_EXPRESSION",
  "PARAMETER_MODE",
  "PARAMETER_COUNT_OR_MYSELF",
  "NOT_USED",
  "PARAMETER_NAME",
  "PARAMETER",
  "MULTI_LINE_PARAMETER",
  "CONTINUATION",
  "MULTI_LINE_CONTINUATION",
  "INLINE_PARAMETERS",
  "MULTI_LINE_PARAMETERS",
  "COMPLETE_BODY",
  "RETURN_EXPRESSION",
  "BODY",
  "C_BODY",
  "LINE_END_EXPRESSION",
  "POLYMORPHIC_FUNCTION_WITHOUT_SETTER",
  "POLYMORPHIC_FUNCTION_WITH_SETTER",
  "POLYMORPHIC_FUNCTION",
  "FUNCTOR",
  "RESULT_COUNT_OR_CONTINUATION",
  "ARGUMENT",
  "FIRST_LINE_ARGUMENTS",
  "MULTI_LINE_FUNCTION_CALL",
  "ARGUMENT_LINE",
  "INLINE_ARGUMENTS",
  "INDENTED_ARGUMENTS",
  "ARGUMENTS",
  "ONE_OR_MORE",
  "check_functor",
  "check_arguments",
  "CHECK_ARGUMENTS",
  "ASSIGNMENT_STATEMENT",
  "PROCEDURE_STATEMENT",
  "RETURN_STATEMENT",
  "STATEMENT",
  "STATEMENTS",
  "BUILTIN_NAME",
  "C_EXPRESSION",
  "ARGUMENT_ANNOTATION",
  "BASE_ANNOTATION",
  "KIND_ANNOTATION",
  "NAME_ANNOTATION",
  "NODE_ANNOTATION",
  "SCOPE_ANNOTATION",
  "TYPE_ANNOTATION",
  "ANNOTATION_ITEM",
  "ANNOTATION",
  "ANNOTATIONS",
  "C_CODE_REMARK",
  "C_CODE_REMARKS",
  "SOURCE",
  "C_CODE",
  "META_FRAGMENT",
  "FRAGMENT"
};
static NODE *func__compiler__std_identifier_1;
static void entry__compiler__std_identifier_1(void);
static FRAME_INFO frame__compiler__std_identifier_1 = {1, {"name"}};
static NODE *string__fa724815d896ba8;
static NODE *get__compiler__std_identifier(void) {
  return var.compiler__std_identifier;
}
static NODE *func__print_message_1;
static void entry__print_message_1(void);
static FRAME_INFO frame__print_message_1 = {12, {"fragment", "offset", "msg_type", "msg", "source", "pos", "line_no", "line_offset", "n", "text", "rest", "line"}};
static void cont__print_message_2(void);
static void cont__print_message_3(void);
static void cont__print_message_4(void);
static void cont__print_message_5(void);
static void cont__print_message_6(void);
static void cont__print_message_7(void);
static void cont__print_message_8(void);
static void cont__print_message_9(void);
static void cont__print_message_10(void);
static void cont__print_message_11(void);
static void cont__print_message_12(void);
static NODE *func__print_message_13;
static void entry__print_message_13(void);
static FRAME_INFO frame__print_message_13 = {2, {"source", "line_offset"}};
static void cont__print_message_14(void);
static void cont__print_message_15(void);
static void cont__print_message_16(void);
static void cont__print_message_17(void);
static void cont__print_message_18(void);
static NODE *func__print_message_19;
static void entry__print_message_19(void);
static FRAME_INFO frame__print_message_19 = {2, {"n", "source"}};
static void cont__print_message_20(void);
static NODE *func__print_message_21;
static void entry__print_message_21(void);
static FRAME_INFO frame__print_message_21 = {2, {"source", "n"}};
static void cont__print_message_22(void);
static void cont__print_message_23(void);
static void cont__print_message_24(void);
static NODE *func__print_message_25;
static void entry__print_message_25(void);
static FRAME_INFO frame__print_message_25 = {1, {"n"}};
static void cont__print_message_26(void);
static void cont__print_message_27(void);
static void cont__print_message_28(void);
static void cont__print_message_29(void);
static NODE *func__print_message_30;
static void entry__print_message_30(void);
static FRAME_INFO frame__print_message_30 = {2, {"text", "line_offset"}};
static void cont__print_message_31(void);
static NODE *func__print_message_32;
static void entry__print_message_32(void);
static FRAME_INFO frame__print_message_32 = {1, {"text"}};
static void cont__print_message_33(void);
static void cont__print_message_34(void);
static void cont__print_message_35(void);
static NODE *string__ef94bdf606d19800;
static void cont__print_message_37(void);
static void cont__print_message_38(void);
static NODE *func__print_message_39;
static void entry__print_message_39(void);
static FRAME_INFO frame__print_message_39 = {3, {"break", "line", "n"}};
static NODE *func__print_message_40;
static void entry__print_message_40(void);
static FRAME_INFO frame__print_message_40 = {3, {"chr", "break", "n"}};
static void cont__print_message_41(void);
static void cont__print_message_42(void);
static void cont__print_message_43(void);
static void cont__print_message_44(void);
static void cont__print_message_45(void);
static void cont__print_message_46(void);
static void cont__print_message_47(void);
static void cont__print_message_48(void);
static void cont__print_message_49(void);
static NODE *func__print_message_50;
static void entry__print_message_50(void);
static FRAME_INFO frame__print_message_50 = {3, {"line_no", "n", "msg"}};
static void cont__print_message_51(void);
static NODE *string__578a5af303e9cdb;
static NODE *string__2d7981f4e6d82be5;
static NODE *string__578a5af303e9ceb;
static void cont__print_message_55(void);
static NODE *func__print_message_56;
static void entry__print_message_56(void);
static FRAME_INFO frame__print_message_56 = {5, {"msg_type", "line_no", "msg", "line", "n"}};
static NODE *string__3c655ae2e30c5e7c;
static NODE *string__3c082d0cc329b1a5;
static NODE *string__6c6619488b29e163;
static NODE *string__fa730c15ff96bc6;
static NODE *string__2d7981f4e6002bcf;
static void cont__print_message_62(void);
static void cont__print_message_63(void);
static void cont__print_message_64(void);
static NODE *string__578a5af303e9cc1;
static void cont__print_message_66(void);
static NODE *string__578a5af303e9cbf;
static NODE *func__compiler__Warning_1;
static void entry__compiler__Warning_1(void);
static FRAME_INFO frame__compiler__Warning_1 = {2, {"obj", "msg"}};
static void cont__compiler__Warning_2(void);
static void cont__compiler__Warning_3(void);
static NODE *string__eed8078214c9e0bd;
static NODE *get__compiler__Warning(void) {
  return var.compiler__Warning;
}
static NODE *func__ExitWithSyntaxError_1;
static void entry__ExitWithSyntaxError_1(void);
static FRAME_INFO frame__ExitWithSyntaxError_1 = {3, {"fragment", "offset", "msg"}};
static NODE *string__ae3c04ed6f185295;
static void cont__ExitWithSyntaxError_3(void);
static NODE *func__compiler__SyntaxError_1;
static void entry__compiler__SyntaxError_1(void);
static FRAME_INFO frame__compiler__SyntaxError_1 = {2, {"obj", "msg"}};
static void cont__compiler__SyntaxError_2(void);
static void cont__compiler__SyntaxError_3(void);
static NODE *get__compiler__SyntaxError(void) {
  return var.compiler__SyntaxError;
}
static NODE *func__ParseError_1;
static void entry__ParseError_1(void);
static FRAME_INFO frame__ParseError_1 = {2, {"stream", "msg"}};
static void cont__ParseError_2(void);
static NODE *get__types__syntax_error(void) {
  return var.types__syntax_error;
}
static NODE *func__types__syntax_error__grammar__match_1;
static void entry__types__syntax_error__grammar__match_1(void);
static FRAME_INFO frame__types__syntax_error__grammar__match_1 = {2, {"self", "stream"}};
static void cont__types__syntax_error__grammar__match_2(void);
static NODE *func__syntax_error_1;
static void entry__syntax_error_1(void);
static FRAME_INFO frame__syntax_error_1 = {1, {"message"}};
static NODE *get__types__unexpected_input_error(void) {
  return var.types__unexpected_input_error;
}
static NODE *func__types__unexpected_input_error__grammar__match_1;
static void entry__types__unexpected_input_error__grammar__match_1(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_1 = {3, {"self", "stream", "expression"}};
static void cont__types__unexpected_input_error__grammar__match_2(void);
static void cont__types__unexpected_input_error__grammar__match_3(void);
static NODE *func__types__unexpected_input_error__grammar__match_4;
static void entry__types__unexpected_input_error__grammar__match_4(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_4 = {1, {"expression"}};
static void cont__types__unexpected_input_error__grammar__match_5(void);
static void cont__types__unexpected_input_error__grammar__match_6(void);
static NODE *func__types__unexpected_input_error__grammar__match_7;
static void entry__types__unexpected_input_error__grammar__match_7(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_7 = {2, {"expression", "stream"}};
static NODE *func__types__unexpected_input_error__grammar__match_8;
static void entry__types__unexpected_input_error__grammar__match_8(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_8 = {1, {"stream"}};
static NODE *string__9a64e069c352dc6a;
static NODE *func__types__unexpected_input_error__grammar__match_10;
static void entry__types__unexpected_input_error__grammar__match_10(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_10 = {1, {"stream"}};
static NODE *string__927507b8d9967cca;
static NODE *func__types__unexpected_input_error__grammar__match_12;
static void entry__types__unexpected_input_error__grammar__match_12(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_12 = {1, {"stream"}};
static NODE *string__9be468e9e34a9c6a;
static NODE *func__types__unexpected_input_error__grammar__match_14;
static void entry__types__unexpected_input_error__grammar__match_14(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_14 = {1, {"stream"}};
static NODE *string__ab853eb411a7faea;
static NODE *func__types__unexpected_input_error__grammar__match_16;
static void entry__types__unexpected_input_error__grammar__match_16(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_16 = {2, {"expression", "stream"}};
static void cont__types__unexpected_input_error__grammar__match_17(void);
static void cont__types__unexpected_input_error__grammar__match_18(void);
static void cont__types__unexpected_input_error__grammar__match_19(void);
static NODE *func__types__unexpected_input_error__grammar__match_20;
static void entry__types__unexpected_input_error__grammar__match_20(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_20 = {1, {"expression"}};
static NODE *string__578a5af303e9cc3;
static void cont__types__unexpected_input_error__grammar__match_22(void);
static void cont__types__unexpected_input_error__grammar__match_23(void);
static NODE *string__68d023a4c22b2461;
static void cont__types__unexpected_input_error__grammar__match_25(void);
static NODE *func__types__unexpected_input_error__grammar__match_26;
static void entry__types__unexpected_input_error__grammar__match_26(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_26 = {1, {"stream"}};
static NODE *string__4914d002f7e03078;
static NODE *func__unexpected_input_error_1;
static void entry__unexpected_input_error_1(void);
static FRAME_INFO frame__unexpected_input_error_1 = {1, {"expression"}};
static NODE *func__dump_stream__grammar__match_1;
static void entry__dump_stream__grammar__match_1(void);
static FRAME_INFO frame__dump_stream__grammar__match_1 = {2, {"self", "stream"}};
static NODE *string__8c16e735f8cebe3d;
static void cont__dump_stream__grammar__match_3(void);
static void cont__dump_stream__grammar__match_4(void);
static void cont__dump_stream__grammar__match_5(void);
static NODE *string__881ef7b4fade9e7f;
static void cont__dump_stream__grammar__match_7(void);
static NODE *func__compiler__strip_1;
static void entry__compiler__strip_1(void);
static FRAME_INFO frame__compiler__strip_1 = {1, {"node"}};
static void cont__compiler__strip_2(void);
static void cont__compiler__strip_3(void);
static NODE *func__compiler__strip_4;
static void entry__compiler__strip_4(void);
static FRAME_INFO frame__compiler__strip_4 = {1, {"node"}};
static void cont__compiler__strip_5(void);
static void cont__compiler__strip_6(void);
static void cont__compiler__strip_7(void);
static void cont__compiler__strip_8(void);
static void cont__compiler__strip_9(void);
static NODE *func__compiler__strip_10;
static void entry__compiler__strip_10(void);
static FRAME_INFO frame__compiler__strip_10 = {1, {"node"}};
static void cont__compiler__strip_11(void);
static void cont__compiler__strip_12(void);
static void cont__compiler__strip_13(void);
static void cont__compiler__strip_14(void);
static void cont__compiler__strip_15(void);
static NODE *func__compiler__strip_16;
static void entry__compiler__strip_16(void);
static FRAME_INFO frame__compiler__strip_16 = {1, {"node"}};
static void cont__compiler__strip_17(void);
static NODE *func__compiler__strip_18;
static void entry__compiler__strip_18(void);
static FRAME_INFO frame__compiler__strip_18 = {1, {"statement"}};
static void cont__compiler__strip_19(void);
static void cont__compiler__strip_20(void);
static void cont__compiler__strip_21(void);
static void cont__compiler__strip_22(void);
static void cont__compiler__strip_23(void);
static NODE *func__compiler__strip_24;
static void entry__compiler__strip_24(void);
static FRAME_INFO frame__compiler__strip_24 = {1, {"node"}};
static void cont__compiler__strip_25(void);
static NODE *func__compiler__strip_26;
static void entry__compiler__strip_26(void);
static FRAME_INFO frame__compiler__strip_26 = {1, {"parameter"}};
static void cont__compiler__strip_27(void);
static void cont__compiler__strip_28(void);
static void cont__compiler__strip_29(void);
static void cont__compiler__strip_30(void);
static void cont__compiler__strip_31(void);
static NODE *func__compiler__strip_32;
static void entry__compiler__strip_32(void);
static FRAME_INFO frame__compiler__strip_32 = {1, {"node"}};
static void cont__compiler__strip_33(void);
static NODE *func__compiler__strip_34;
static void entry__compiler__strip_34(void);
static FRAME_INFO frame__compiler__strip_34 = {1, {"argument"}};
static void cont__compiler__strip_35(void);
static void cont__compiler__strip_36(void);
static void cont__compiler__strip_37(void);
static void cont__compiler__strip_38(void);
static void cont__compiler__strip_39(void);
static NODE *func__compiler__strip_40;
static void entry__compiler__strip_40(void);
static FRAME_INFO frame__compiler__strip_40 = {1, {"node"}};
static void cont__compiler__strip_41(void);
static void cont__compiler__strip_42(void);
static void cont__compiler__strip_43(void);
static void cont__compiler__strip_44(void);
static void cont__compiler__strip_45(void);
static NODE *func__compiler__strip_46;
static void entry__compiler__strip_46(void);
static FRAME_INFO frame__compiler__strip_46 = {1, {"node"}};
static void cont__compiler__strip_47(void);
static void cont__compiler__strip_48(void);
static void cont__compiler__strip_49(void);
static NODE *get__compiler__strip(void) {
  return var.compiler__strip;
}
static NODE *func__dump__grammar__match_1;
static void entry__dump__grammar__match_1(void);
static FRAME_INFO frame__dump__grammar__match_1 = {2, {"self", "stream"}};
static void cont__dump__grammar__match_2(void);
static NODE *string__665e06ec4dcad6be;
static void cont__dump__grammar__match_4(void);
static NODE *func__dump3__grammar__match_1;
static void entry__dump3__grammar__match_1(void);
static FRAME_INFO frame__dump3__grammar__match_1 = {2, {"self", "stream"}};
static void cont__dump3__grammar__match_2(void);
static void cont__dump3__grammar__match_3(void);
static NODE *func__dump5__grammar__match_1;
static void entry__dump5__grammar__match_1(void);
static FRAME_INFO frame__dump5__grammar__match_1 = {2, {"self", "stream"}};
static void cont__dump5__grammar__match_2(void);
static void cont__dump5__grammar__match_3(void);
static NODE *get__compiler__HIGHEST_PRECEDENCE(void) {
  return var.compiler__HIGHEST_PRECEDENCE;
}
static NODE *get__compiler__INFIX_PRECEDENCE(void) {
  return var.compiler__INFIX_PRECEDENCE;
}
static NODE *func__compiler__precedence_1;
static void entry__compiler__precedence_1(void);
static FRAME_INFO frame__compiler__precedence_1 = {1, {"op"}};
static void cont__compiler__precedence_2(void);
static NODE *func__compiler__precedence_3;
static void entry__compiler__precedence_3(void);
static FRAME_INFO frame__compiler__precedence_3 = {1, {"op"}};
static void cont__compiler__precedence_4(void);
static NODE *func__compiler__precedence_5;
static void entry__compiler__precedence_5(void);
static FRAME_INFO frame__compiler__precedence_5 = {0, {}};
static NODE *get__compiler__precedence(void) {
  return var.compiler__precedence;
}
static NODE *func__compiler__is_left_associative_1;
static void entry__compiler__is_left_associative_1(void);
static FRAME_INFO frame__compiler__is_left_associative_1 = {1, {"prec"}};
static void cont__compiler__is_left_associative_2(void);
static NODE *get__compiler__is_left_associative(void) {
  return var.compiler__is_left_associative;
}
static NODE *func__is_right_associative_1;
static void entry__is_right_associative_1(void);
static FRAME_INFO frame__is_right_associative_1 = {1, {"prec"}};
static void cont__is_right_associative_2(void);
static void cont__is_right_associative_3(void);
static NODE *func__infix_operator_1;
static void entry__infix_operator_1(void);
static FRAME_INFO frame__infix_operator_1 = {1, {"operator"}};
static void cont__infix_operator_2(void);
static void cont__infix_operator_3(void);
static NODE *func__interleaved_1;
static void entry__interleaved_1(void);
static FRAME_INFO frame__interleaved_1 = {2, {"expression", "separator"}};
static void cont__interleaved_2(void);
static void cont__interleaved_3(void);
static void cont__interleaved_4(void);
static int dyna_idx__arguments_index;
static NODE *get__arguments_index(void) {
  return get_dynamic_slot(dyna_idx__arguments_index);
}
static void define__arguments_index(NODE *node) {
  define_dynamic_slot(dyna_idx__arguments_index, node);
}
static NODE *get__types__store_arguments_index(void) {
  return var.types__store_arguments_index;
}
static NODE *func__types__store_arguments_index__grammar__match_1;
static void entry__types__store_arguments_index__grammar__match_1(void);
static FRAME_INFO frame__types__store_arguments_index__grammar__match_1 = {3, {"self", "stream", "return__1"}};
static void cont__types__store_arguments_index__grammar__match_2(void);
static void cont__types__store_arguments_index__grammar__match_3(void);
static void cont__types__store_arguments_index__grammar__match_4(void);
static void cont__types__store_arguments_index__grammar__match_5(void);
static NODE *func__store_arguments_index_1;
static void entry__store_arguments_index_1(void);
static FRAME_INFO frame__store_arguments_index_1 = {1, {"expression"}};
static int dyna_idx__within_inline_expression;
static NODE *get__within_inline_expression(void) {
  return get_dynamic_slot(dyna_idx__within_inline_expression);
}
static void define__within_inline_expression(NODE *node) {
  define_dynamic_slot(dyna_idx__within_inline_expression, node);
}
static NODE *get__types__inline(void) {
  return var.types__inline;
}
static NODE *func__types__inline__grammar__match_1;
static void entry__types__inline__grammar__match_1(void);
static FRAME_INFO frame__types__inline__grammar__match_1 = {3, {"self", "stream", "return__1"}};
static void cont__types__inline__grammar__match_2(void);
static void cont__types__inline__grammar__match_3(void);
static NODE *func__inline_1;
static void entry__inline_1(void);
static FRAME_INFO frame__inline_1 = {1, {"expression"}};
static NODE *func__expect_1;
static void entry__expect_1(void);
static FRAME_INFO frame__expect_1 = {2, {"expression", "description"}};
static void cont__expect_2(void);
static NODE *func__expect_3;
static void entry__expect_3(void);
static FRAME_INFO frame__expect_3 = {2, {"expression", "description"}};
static void cont__expect_4(void);
static void cont__expect_5(void);
static void cont__expect_6(void);
static NODE *func__expect_7;
static void entry__expect_7(void);
static FRAME_INFO frame__expect_7 = {1, {"expression"}};
static void cont__expect_8(void);
static void cont__expect_9(void);
static NODE *func__compiler__arguments_span_1;
static void entry__compiler__arguments_span_1(void);
static FRAME_INFO frame__compiler__arguments_span_1 = {1, {"expression"}};
static void cont__compiler__arguments_span_2(void);
static NODE *get__compiler__arguments_span(void) {
  return var.compiler__arguments_span;
}
static NODE *get__compiler__WHITESPACE(void) {
  return var.compiler__WHITESPACE;
}
static NODE *unique__ONE_OR_MORE;
static NODE *func__check_functor_1;
static void entry__check_functor_1(void);
static FRAME_INFO frame__check_functor_1 = {1, {"functor"}};
static void cont__check_functor_2(void);
static NODE *func__check_functor_3;
static void entry__check_functor_3(void);
static FRAME_INFO frame__check_functor_3 = {1, {"functor"}};
static void cont__check_functor_4(void);
static NODE *func__check_functor_5;
static void entry__check_functor_5(void);
static FRAME_INFO frame__check_functor_5 = {1, {"functor"}};
static void cont__check_functor_6(void);
static void cont__check_functor_7(void);
static void cont__check_functor_8(void);
static void cont__check_functor_9(void);
static NODE *func__check_functor_10;
static void entry__check_functor_10(void);
static FRAME_INFO frame__check_functor_10 = {1, {"functor"}};
static NODE *string__120dee9a1dcec47c;
static NODE *func__check_arguments_1;
static void entry__check_arguments_1(void);
static FRAME_INFO frame__check_arguments_1 = {9, {"node", "kind", "wanted_outputs", "wanted_inputs", "outputs", "inputs", "contains_attribute_value_pair", "contains_simple_input_argument", "add_argument"}};
static NODE *func__check_arguments_2;
static void entry__check_arguments_2(void);
static FRAME_INFO frame__check_arguments_2 = {5, {"argument", "outputs", "contains_simple_input_argument", "contains_attribute_value_pair", "inputs"}};
static void cont__check_arguments_3(void);
static NODE *func__check_arguments_4;
static void entry__check_arguments_4(void);
static FRAME_INFO frame__check_arguments_4 = {1, {"outputs"}};
static void cont__check_arguments_5(void);
static void cont__check_arguments_6(void);
static void cont__check_arguments_7(void);
static void cont__check_arguments_8(void);
static NODE *func__check_arguments_9;
static void entry__check_arguments_9(void);
static FRAME_INFO frame__check_arguments_9 = {1, {"argument"}};
static void cont__check_arguments_10(void);
static void cont__check_arguments_11(void);
static NODE *func__check_arguments_12;
static void entry__check_arguments_12(void);
static FRAME_INFO frame__check_arguments_12 = {4, {"argument", "contains_simple_input_argument", "contains_attribute_value_pair", "inputs"}};
static void cont__check_arguments_13(void);
static NODE *func__check_arguments_14;
static void entry__check_arguments_14(void);
static FRAME_INFO frame__check_arguments_14 = {3, {"contains_simple_input_argument", "argument", "contains_attribute_value_pair"}};
static NODE *func__check_arguments_15;
static void entry__check_arguments_15(void);
static FRAME_INFO frame__check_arguments_15 = {1, {"argument"}};
static NODE *string__c5acb93e4d23cfd9;
static void cont__check_arguments_17(void);
static NODE *func__check_arguments_18;
static void entry__check_arguments_18(void);
static FRAME_INFO frame__check_arguments_18 = {3, {"contains_attribute_value_pair", "argument", "contains_simple_input_argument"}};
static NODE *func__check_arguments_19;
static void entry__check_arguments_19(void);
static FRAME_INFO frame__check_arguments_19 = {1, {"argument"}};
static NODE *string__687da0cc5622be9c;
static void cont__check_arguments_21(void);
static void cont__check_arguments_22(void);
static void cont__check_arguments_23(void);
static void cont__check_arguments_24(void);
static NODE *func__check_arguments_25;
static void entry__check_arguments_25(void);
static FRAME_INFO frame__check_arguments_25 = {2, {"argument", "add_argument"}};
static void cont__check_arguments_26(void);
static NODE *func__check_arguments_27;
static void entry__check_arguments_27(void);
static FRAME_INFO frame__check_arguments_27 = {2, {"argument", "add_argument"}};
static void cont__check_arguments_28(void);
static NODE *func__check_arguments_29;
static void entry__check_arguments_29(void);
static FRAME_INFO frame__check_arguments_29 = {2, {"add_argument", "argument"}};
static void cont__check_arguments_30(void);
static void cont__check_arguments_31(void);
static void cont__check_arguments_32(void);
static NODE *func__check_arguments_33;
static void entry__check_arguments_33(void);
static FRAME_INFO frame__check_arguments_33 = {2, {"add_argument", "argument"}};
static void cont__check_arguments_34(void);
static void cont__check_arguments_35(void);
static NODE *func__check_arguments_36;
static void entry__check_arguments_36(void);
static FRAME_INFO frame__check_arguments_36 = {4, {"wanted_outputs", "outputs", "node", "kind"}};
static void cont__check_arguments_37(void);
static NODE *func__check_arguments_38;
static void entry__check_arguments_38(void);
static FRAME_INFO frame__check_arguments_38 = {2, {"node", "kind"}};
static NODE *string__5fa0d5b2a9ee383d;
static void cont__check_arguments_40(void);
static void cont__check_arguments_41(void);
static void cont__check_arguments_42(void);
static NODE *func__check_arguments_43;
static void entry__check_arguments_43(void);
static FRAME_INFO frame__check_arguments_43 = {2, {"node", "kind"}};
static NODE *string__1b6e5ce3b21cbf2f;
static void cont__check_arguments_45(void);
static void cont__check_arguments_46(void);
static void cont__check_arguments_47(void);
static NODE *func__check_arguments_48;
static void entry__check_arguments_48(void);
static FRAME_INFO frame__check_arguments_48 = {6, {"wanted_inputs", "inputs", "node", "kind", "min_inputs", "max_inputs"}};
static void cont__check_arguments_49(void);
static NODE *func__check_arguments_50;
static void entry__check_arguments_50(void);
static FRAME_INFO frame__check_arguments_50 = {1, {"wanted_inputs"}};
static NODE *func__check_arguments_51;
static void entry__check_arguments_51(void);
static FRAME_INFO frame__check_arguments_51 = {0, {}};
static void cont__check_arguments_52(void);
static void cont__check_arguments_53(void);
static NODE *func__check_arguments_54;
static void entry__check_arguments_54(void);
static FRAME_INFO frame__check_arguments_54 = {1, {"wanted_inputs"}};
static NODE *func__check_arguments_55;
static void entry__check_arguments_55(void);
static FRAME_INFO frame__check_arguments_55 = {0, {}};
static void cont__check_arguments_56(void);
static void cont__check_arguments_57(void);
static NODE *func__check_arguments_58;
static void entry__check_arguments_58(void);
static FRAME_INFO frame__check_arguments_58 = {2, {"max_inputs", "inputs"}};
static void cont__check_arguments_59(void);
static void cont__check_arguments_60(void);
static NODE *func__check_arguments_61;
static void entry__check_arguments_61(void);
static FRAME_INFO frame__check_arguments_61 = {3, {"node", "kind", "first_input_argument"}};
static NODE *func__check_arguments_62;
static void entry__check_arguments_62(void);
static FRAME_INFO frame__check_arguments_62 = {3, {"break", "node", "first_input_argument"}};
static void cont__check_arguments_63(void);
static NODE *func__check_arguments_64;
static void entry__check_arguments_64(void);
static FRAME_INFO frame__check_arguments_64 = {3, {"argument", "first_input_argument", "break"}};
static void cont__check_arguments_65(void);
static NODE *func__check_arguments_66;
static void entry__check_arguments_66(void);
static FRAME_INFO frame__check_arguments_66 = {3, {"first_input_argument", "argument", "break"}};
static void cont__check_arguments_67(void);
static void cont__check_arguments_68(void);
static void cont__check_arguments_69(void);
static NODE *func__check_arguments_70;
static void entry__check_arguments_70(void);
static FRAME_INFO frame__check_arguments_70 = {2, {"node", "kind"}};
static NODE *string__ebee6487b4b0342b;
static void cont__check_arguments_72(void);
static void cont__check_arguments_73(void);
static void cont__check_arguments_74(void);
static NODE *func__check_arguments_75;
static void entry__check_arguments_75(void);
static FRAME_INFO frame__check_arguments_75 = {2, {"inputs", "min_inputs"}};
static void cont__check_arguments_76(void);
static void cont__check_arguments_77(void);
static NODE *func__check_arguments_78;
static void entry__check_arguments_78(void);
static FRAME_INFO frame__check_arguments_78 = {2, {"node", "kind"}};
static NODE *string__bb0c2c1e659a1755;
static void cont__check_arguments_80(void);
static NODE *func__CHECK_ARGUMENTS_1;
static void entry__CHECK_ARGUMENTS_1(void);
static FRAME_INFO frame__CHECK_ARGUMENTS_1 = {3, {"kind", "wanted_outputs", "wanted_inputs"}};
static NODE *func__CHECK_ARGUMENTS_2;
static void entry__CHECK_ARGUMENTS_2(void);
static FRAME_INFO frame__CHECK_ARGUMENTS_2 = {4, {"node", "kind", "wanted_outputs", "wanted_inputs"}};
static NODE *func__compiler__parse_meta_instruction_1;
static void entry__compiler__parse_meta_instruction_1(void);
static FRAME_INFO frame__compiler__parse_meta_instruction_1 = {5, {"fragment", "return__1", "source", "len", "cap"}};
static void cont__compiler__parse_meta_instruction_2(void);
static void cont__compiler__parse_meta_instruction_3(void);
static void cont__compiler__parse_meta_instruction_4(void);
static void cont__compiler__parse_meta_instruction_5(void);
static void cont__compiler__parse_meta_instruction_6(void);
static NODE *func__compiler__parse_meta_instruction_7;
static void entry__compiler__parse_meta_instruction_7(void);
static FRAME_INFO frame__compiler__parse_meta_instruction_7 = {1, {"source"}};
static NODE *string__12eb1acbffa2ae01;
static void cont__compiler__parse_meta_instruction_9(void);
static NODE *get__compiler__parse_meta_instruction(void) {
  return var.compiler__parse_meta_instruction;
}
static NODE *func__compiler__parse_statement_1;
static void entry__compiler__parse_statement_1(void);
static FRAME_INFO frame__compiler__parse_statement_1 = {5, {"fragment", "return__1", "source", "len", "cap"}};
static void cont__compiler__parse_statement_2(void);
static void cont__compiler__parse_statement_3(void);
static void cont__compiler__parse_statement_4(void);
static NODE *func__compiler__parse_statement_5;
static void entry__compiler__parse_statement_5(void);
static FRAME_INFO frame__compiler__parse_statement_5 = {2, {"len", "source"}};
static void cont__compiler__parse_statement_6(void);
static void cont__compiler__parse_statement_7(void);
static void cont__compiler__parse_statement_8(void);
static NODE *func__compiler__parse_statement_9;
static void entry__compiler__parse_statement_9(void);
static FRAME_INFO frame__compiler__parse_statement_9 = {1, {"source"}};
static NODE *string__482d004bd19ca8db;
static NODE *func__compiler__parse_statement_11;
static void entry__compiler__parse_statement_11(void);
static FRAME_INFO frame__compiler__parse_statement_11 = {1, {"source"}};
static NODE *string__5278dd75c73e18e3;
static void cont__compiler__parse_statement_13(void);
static void cont__compiler__parse_statement_14(void);
static NODE *string__6ca8a8f604cd4188;
static void cont__compiler__parse_statement_16(void);
static void cont__compiler__parse_statement_17(void);
static NODE *get__compiler__parse_statement(void) {
  return var.compiler__parse_statement;
}
static NODE *string__578a5af303e9ccb;
static void cont__216_2(void);
static NODE *string__578a5af303e9cce;
static void cont__216_4(void);
static NODE *string__578a5af303e9cca;
static void cont__216_6(void);
static NODE *string__578a5af303e9ccc;
static void cont__216_8(void);
static NODE *string__2d7981f4e6e82bf9;
static void cont__216_10(void);
static NODE *string__2d7981f4e6f82bfb;
static void cont__216_12(void);
static NODE *string__578a5af303e9cc7;
static void cont__216_14(void);
static void cont__216_15(void);
static NODE *string__578a5af303e9c9d;
static void cont__216_17(void);
static NODE *string__2d7981f4e6e82bf8;
static void cont__216_19(void);
static NODE *string__578a5af303e9cdd;
static void cont__216_21(void);
static NODE *string__2d7981f4e6f82bf8;
static void cont__216_23(void);
static NODE *string__578a5af303e9cdf;
static void cont__216_25(void);
static NODE *string__2d7981f4e6e02bf8;
static void cont__216_27(void);
static NODE *string__2d7981f4e6002bf8;
static void cont__216_29(void);
static NODE *string__2d7981f4e6382be3;
static void cont__216_31(void);
static NODE *string__2d7981f4e4e82bb9;
static void cont__216_33(void);
static NODE *string__2d7981f4e6782beb;
static void cont__216_35(void);
static NODE *string__578a5af303e9ccd;
static void cont__216_37(void);
static NODE *string__578a5af303e9cdc;
static void cont__216_39(void);
static void cont__216_40(void);
static NODE *func__230_1;
static void entry__230_1(void);
static FRAME_INFO frame__230_1 = {2, {"node", "stream"}};
static NODE *func__230_2;
static void entry__230_2(void);
static FRAME_INFO frame__230_2 = {1, {"stream"}};
static NODE *string__ccbf6d451aa8563f;
static void cont__230_4(void);
static void cont__230_5(void);
static void cont__231_1(void);
static void cont__231_2(void);
static void cont__232_1(void);
static void cont__232_2(void);
static void cont__233_1(void);
static void cont__233_2(void);
static void cont__234_1(void);
static void cont__234_2(void);
static void cont__237_1(void);
static void cont__238_1(void);
static void cont__238_2(void);
static void cont__239_1(void);
static NODE *func__240_1;
static void entry__240_1(void);
static FRAME_INFO frame__240_1 = {2, {"node", "stream"}};
static void cont__240_2(void);
static void cont__240_3(void);
static NODE *func__241_1;
static void entry__241_1(void);
static FRAME_INFO frame__241_1 = {2, {"node", "stream"}};
static void cont__241_2(void);
static void cont__241_3(void);
static void cont__241_4(void);
static NODE *func__242_1;
static void entry__242_1(void);
static FRAME_INFO frame__242_1 = {2, {"node", "stream"}};
static void cont__242_2(void);
static void cont__242_3(void);
static void cont__243_1(void);
static void cont__243_2(void);
static NODE *func__243_3;
static void entry__243_3(void);
static FRAME_INFO frame__243_3 = {1, {"node"}};
static void cont__243_4(void);
static void cont__243_5(void);
static void cont__243_6(void);
static NODE *string__2d7981f4e6d82bff;
static void cont__243_8(void);
static void cont__243_9(void);
static void cont__243_10(void);
static void cont__244_1(void);
static void cont__244_2(void);
static void cont__244_3(void);
static NODE *func__244_4;
static void entry__244_4(void);
static FRAME_INFO frame__244_4 = {1, {"node"}};
static void cont__244_5(void);
static NODE *func__244_6;
static void entry__244_6(void);
static FRAME_INFO frame__244_6 = {1, {"node"}};
static NODE *string__958c1dda41e5a79c;
static void cont__244_8(void);
static void cont__244_9(void);
static void cont__244_10(void);
static void cont__244_11(void);
static void cont__244_12(void);
static void cont__244_13(void);
static void cont__244_14(void);
static void cont__245_1(void);
static void cont__245_2(void);
static void cont__245_3(void);
static void cont__245_4(void);
static void cont__245_5(void);
static NODE *string__2d7981f4e6782bea;
static void cont__246_2(void);
static void cont__246_3(void);
static void cont__246_4(void);
static void cont__246_5(void);
static void cont__247_1(void);
static void cont__247_2(void);
static NODE *func__247_3;
static void entry__247_3(void);
static FRAME_INFO frame__247_3 = {3, {"node", "stream", "filename"}};
static void cont__247_4(void);
static void cont__247_5(void);
static void cont__247_6(void);
static NODE *func__247_7;
static void entry__247_7(void);
static FRAME_INFO frame__247_7 = {2, {"stream", "filename"}};
static NODE *string__92e1510f182d5769;
static NODE *string__fd365ba9213c93f1;
static void cont__247_10(void);
static void cont__247_11(void);
static void cont__247_12(void);
static void cont__247_13(void);
static NODE *string__44dcaf9484448bc5;
static void cont__247_15(void);
static void cont__248_1(void);
static void cont__248_2(void);
static void cont__248_3(void);
static NODE *func__248_4;
static void entry__248_4(void);
static FRAME_INFO frame__248_4 = {1, {"node"}};
static void cont__248_5(void);
static void cont__248_6(void);
static void cont__248_7(void);
static void cont__248_8(void);
static void cont__248_9(void);
static NODE *func__248_10;
static void entry__248_10(void);
static FRAME_INFO frame__248_10 = {4, {"node", "stream", "namespace", "alias"}};
static void cont__248_11(void);
static void cont__248_12(void);
static void cont__248_13(void);
static NODE *func__248_14;
static void entry__248_14(void);
static FRAME_INFO frame__248_14 = {3, {"alias", "stream", "namespace"}};
static void cont__248_15(void);
static void cont__248_16(void);
static NODE *func__248_17;
static void entry__248_17(void);
static FRAME_INFO frame__248_17 = {2, {"stream", "alias"}};
static NODE *string__e13e5990aea4c8f3;
static NODE *string__54767964cc2066c4;
static void cont__248_20(void);
static void cont__248_21(void);
static void cont__248_22(void);
static NODE *func__248_23;
static void entry__248_23(void);
static FRAME_INFO frame__248_23 = {2, {"namespace", "stream"}};
static void cont__248_24(void);
static NODE *func__248_25;
static void entry__248_25(void);
static FRAME_INFO frame__248_25 = {2, {"stream", "namespace"}};
static NODE *string__9159abe89634488c;
static void cont__248_27(void);
static void cont__248_28(void);
static void cont__248_29(void);
static void cont__248_30(void);
static NODE *string__1552f059283245c4;
static void cont__248_32(void);
static void cont__249_1(void);
static void cont__249_2(void);
static NODE *func__249_3;
static void entry__249_3(void);
static FRAME_INFO frame__249_3 = {3, {"node", "stream", "namespace"}};
static void cont__249_4(void);
static void cont__249_5(void);
static NODE *func__249_6;
static void entry__249_6(void);
static FRAME_INFO frame__249_6 = {2, {"stream", "namespace"}};
static NODE *string__1d0508008a8a40d8;
static void cont__249_8(void);
static void cont__249_9(void);
static void cont__249_10(void);
static void cont__249_11(void);
static NODE *string__7e1f542e81cb02b0;
static void cont__249_13(void);
static void cont__250_1(void);
static void cont__250_2(void);
static NODE *string__fa733c15f596be3;
static void cont__251_2(void);
static void cont__251_3(void);
static void cont__251_4(void);
static void cont__251_5(void);
static void cont__251_6(void);
static void cont__252_1(void);
static void cont__252_2(void);
static NODE *func__252_3;
static void entry__252_3(void);
static FRAME_INFO frame__252_3 = {3, {"node", "stream", "filename"}};
static void cont__252_4(void);
static void cont__252_5(void);
static NODE *func__252_6;
static void entry__252_6(void);
static FRAME_INFO frame__252_6 = {2, {"stream", "filename"}};
static NODE *string__2c64b158ac2be503;
static NODE *string__b0b6bb19371893f7;
static void cont__252_9(void);
static void cont__252_10(void);
static void cont__252_11(void);
static void cont__252_12(void);
static NODE *string__76b0a89104f5abc5;
static void cont__252_14(void);
static void cont__253_1(void);
static void cont__253_2(void);
static NODE *func__253_3;
static void entry__253_3(void);
static FRAME_INFO frame__253_3 = {3, {"node", "stream", "filename"}};
static void cont__253_4(void);
static void cont__253_5(void);
static NODE *func__253_6;
static void entry__253_6(void);
static FRAME_INFO frame__253_6 = {2, {"stream", "filename"}};
static NODE *string__a660d7293a5c47e8;
static NODE *string__ad06d2ccd69d8e1;
static void cont__253_9(void);
static void cont__253_10(void);
static void cont__253_11(void);
static void cont__253_12(void);
static NODE *string__525ae943eabdd03c;
static void cont__253_14(void);
static void cont__254_1(void);
static void cont__254_2(void);
static void cont__255_1(void);
static void cont__255_2(void);
static void cont__255_3(void);
static void cont__255_4(void);
static void cont__255_5(void);
static void cont__256_1(void);
static void cont__256_2(void);
static NODE *func__256_3;
static void entry__256_3(void);
static FRAME_INFO frame__256_3 = {3, {"node", "stream", "filemask"}};
static void cont__256_4(void);
static void cont__256_5(void);
static NODE *func__256_6;
static void entry__256_6(void);
static FRAME_INFO frame__256_6 = {2, {"stream", "filemask"}};
static NODE *string__e720c6242e8cd532;
static void cont__256_8(void);
static void cont__256_9(void);
static void cont__256_10(void);
static void cont__256_11(void);
static NODE *string__425aeb43ea6dd036;
static void cont__256_13(void);
static void cont__257_1(void);
static void cont__257_2(void);
static void cont__257_3(void);
static void cont__257_4(void);
static void cont__257_5(void);
static void cont__257_6(void);
static void cont__258_1(void);
static void cont__258_2(void);
static void cont__259_1(void);
static void cont__259_2(void);
static void cont__259_3(void);
static void cont__259_4(void);
static void cont__259_5(void);
static void cont__260_1(void);
static void cont__260_2(void);
static void cont__261_1(void);
static void cont__262_1(void);
static void cont__263_1(void);
static NODE *func__264_1;
static void entry__264_1(void);
static FRAME_INFO frame__264_1 = {1, {"node"}};
static NODE *func__264_2;
static void entry__264_2(void);
static FRAME_INFO frame__264_2 = {0, {}};
static void cont__264_3(void);
static NODE *func__264_4;
static void entry__264_4(void);
static FRAME_INFO frame__264_4 = {1, {"node"}};
static void cont__264_5(void);
static void cont__264_6(void);
static void cont__264_7(void);
static void cont__264_8(void);
static void cont__264_9(void);
static void cont__265_1(void);
static void cont__265_2(void);
static void cont__265_3(void);
static void cont__265_4(void);
static void cont__266_1(void);
static void cont__266_2(void);
static void cont__266_3(void);
static void cont__266_4(void);
static NODE *func__267_1;
static void entry__267_1(void);
static FRAME_INFO frame__267_1 = {1, {"node"}};
static void cont__267_2(void);
static void cont__267_3(void);
static void cont__267_4(void);
static void cont__267_5(void);
static void cont__267_6(void);
static void cont__267_7(void);
static NODE *string__4456c807200257a4;
static void cont__267_9(void);
static void cont__267_10(void);
static void cont__267_11(void);
static NODE *func__268_1;
static void entry__268_1(void);
static FRAME_INFO frame__268_1 = {1, {"node"}};
static void cont__268_2(void);
static void cont__268_3(void);
static void cont__268_4(void);
static void cont__268_5(void);
static void cont__269_1(void);
static void cont__269_2(void);
static void cont__270_1(void);
static void cont__270_2(void);
static void cont__271_1(void);
static void cont__271_2(void);
static void cont__272_1(void);
static void cont__272_2(void);
static void cont__273_1(void);
static void cont__274_1(void);
static void cont__274_2(void);
static void cont__275_1(void);
static void cont__275_2(void);
static void cont__275_3(void);
static void cont__275_4(void);
static void cont__275_5(void);
static void cont__275_6(void);
static void cont__275_7(void);
static void cont__275_8(void);
static void cont__275_9(void);
static void cont__275_10(void);
static void cont__275_11(void);
static void cont__275_12(void);
static void cont__276_1(void);
static void cont__277_1(void);
static void cont__277_2(void);
static NODE *string__2d7981f4e6882ba7;
static void cont__277_4(void);
static void cont__278_1(void);
static void cont__279_1(void);
static void cont__279_2(void);
static NODE *string__2d7981f4e6882baa;
static void cont__279_4(void);
static void cont__280_1(void);
static void cont__280_2(void);
static void cont__280_3(void);
static void cont__281_1(void);
static void cont__281_2(void);
static NODE *string__2d7981f4e6882bbd;
static void cont__281_4(void);
static void cont__282_1(void);
static void cont__282_2(void);
static void cont__282_3(void);
static void cont__282_4(void);
static void cont__283_1(void);
static NODE *func__283_2;
static void entry__283_2(void);
static FRAME_INFO frame__283_2 = {1, {"node"}};
static void cont__283_3(void);
static void cont__283_4(void);
static void cont__283_5(void);
static void cont__283_6(void);
static NODE *func__284_1;
static void entry__284_1(void);
static FRAME_INFO frame__284_1 = {1, {"node"}};
static void cont__284_2(void);
static void cont__284_3(void);
static void cont__285_1(void);
static NODE *func__285_2;
static void entry__285_2(void);
static FRAME_INFO frame__285_2 = {3, {"node", "stream", "chr"}};
static void cont__285_3(void);
static void cont__285_4(void);
static void cont__285_5(void);
static NODE *func__285_6;
static void entry__285_6(void);
static FRAME_INFO frame__285_6 = {1, {"stream"}};
static NODE *string__dea962eab6ac8f23;
static void cont__285_8(void);
static void cont__285_9(void);
static void cont__285_10(void);
static void cont__286_1(void);
static void cont__286_2(void);
static void cont__286_3(void);
static void cont__286_4(void);
static void cont__286_5(void);
static void cont__286_6(void);
static void cont__286_7(void);
static void cont__286_8(void);
static void cont__286_9(void);
static NODE *func__286_10;
static void entry__286_10(void);
static FRAME_INFO frame__286_10 = {1, {"node"}};
static void cont__286_11(void);
static void cont__286_12(void);
static void cont__286_13(void);
static void cont__286_14(void);
static void cont__286_15(void);
static NODE *string__4313674f4741806a;
static void cont__287_2(void);
static void cont__287_3(void);
static void cont__288_1(void);
static void cont__288_2(void);
static void cont__289_1(void);
static void cont__289_2(void);
static void cont__289_3(void);
static NODE *func__290_1;
static void entry__290_1(void);
static FRAME_INFO frame__290_1 = {1, {"node"}};
static void cont__290_2(void);
static void cont__290_3(void);
static void cont__290_4(void);
static void cont__290_5(void);
static void cont__290_6(void);
static NODE *string__2d7981f4e5082bfe;
static void cont__290_8(void);
static NODE *func__291_1;
static void entry__291_1(void);
static FRAME_INFO frame__291_1 = {1, {"node"}};
static void cont__291_2(void);
static void cont__291_3(void);
static void cont__291_4(void);
static NODE *func__291_5;
static void entry__291_5(void);
static FRAME_INFO frame__291_5 = {1, {"node"}};
static void cont__291_6(void);
static void cont__291_7(void);
static void cont__291_8(void);
static void cont__291_9(void);
static void cont__291_10(void);
static void cont__291_11(void);
static void cont__291_12(void);
static NODE *string__2d7981f4e5082bed;
static void cont__291_14(void);
static NODE *func__292_1;
static void entry__292_1(void);
static FRAME_INFO frame__292_1 = {1, {"node"}};
static void cont__292_2(void);
static void cont__292_3(void);
static void cont__292_4(void);
static NODE *func__292_5;
static void entry__292_5(void);
static FRAME_INFO frame__292_5 = {1, {"node"}};
static void cont__292_6(void);
static void cont__292_7(void);
static void cont__292_8(void);
static NODE *func__292_9;
static void entry__292_9(void);
static FRAME_INFO frame__292_9 = {1, {"node"}};
static void cont__292_10(void);
static void cont__292_11(void);
static void cont__292_12(void);
static NODE *string__7c1f540901cb12b0;
static void cont__292_14(void);
static void cont__292_15(void);
static void cont__292_16(void);
static void cont__292_17(void);
static void cont__292_18(void);
static void cont__292_19(void);
static void cont__292_20(void);
static void cont__293_1(void);
static void cont__293_2(void);
static void cont__293_3(void);
static void cont__293_4(void);
static void cont__293_5(void);
static void cont__293_6(void);
static void cont__293_7(void);
static void cont__293_8(void);
static void cont__294_1(void);
static void cont__294_2(void);
static void cont__294_3(void);
static void cont__294_4(void);
static void cont__294_5(void);
static void cont__294_6(void);
static void cont__294_7(void);
static NODE *func__295_1;
static void entry__295_1(void);
static FRAME_INFO frame__295_1 = {1, {"node"}};
static void cont__295_2(void);
static void cont__295_3(void);
static void cont__295_4(void);
static void cont__295_5(void);
static void cont__296_1(void);
static void cont__296_2(void);
static void cont__296_3(void);
static void cont__296_4(void);
static void cont__296_5(void);
static void cont__296_6(void);
static void cont__296_7(void);
static void cont__296_8(void);
static void cont__297_1(void);
static void cont__297_2(void);
static void cont__297_3(void);
static NODE *string__55df65a142fc9536;
static void cont__298_2(void);
static void cont__298_3(void);
static void cont__298_4(void);
static void cont__298_5(void);
static void cont__298_6(void);
static NODE *func__299_1;
static void entry__299_1(void);
static FRAME_INFO frame__299_1 = {1, {"node"}};
static NODE *string__64d512703527e2ab;
static void cont__299_3(void);
static NODE *string__2a0aedcb5dc87d5c;
static void cont__299_5(void);
static void cont__299_6(void);
static void cont__299_7(void);
static void cont__299_8(void);
static void cont__299_9(void);
static void cont__299_10(void);
static NODE *string__2d7981f4e6602be8;
static void cont__299_12(void);
static NODE *func__300_1;
static void entry__300_1(void);
static FRAME_INFO frame__300_1 = {1, {"node"}};
static void cont__300_2(void);
static void cont__300_3(void);
static void cont__300_4(void);
static void cont__300_5(void);
static void cont__300_6(void);
static void cont__301_1(void);
static void cont__302_1(void);
static void cont__302_2(void);
static void cont__302_3(void);
static void cont__303_1(void);
static void cont__304_1(void);
static void cont__304_2(void);
static void cont__305_1(void);
static void cont__305_2(void);
static void cont__306_1(void);
static void cont__306_2(void);
static void cont__306_3(void);
static void cont__307_1(void);
static NODE *func__307_2;
static void entry__307_2(void);
static FRAME_INFO frame__307_2 = {3, {"node", "operator_precedence", "lowest_precedence"}};
static void cont__307_3(void);
static void cont__307_4(void);
static void cont__307_5(void);
static void cont__307_6(void);
static void cont__307_7(void);
static void cont__307_8(void);
static NODE *func__307_9;
static void entry__307_9(void);
static FRAME_INFO frame__307_9 = {2, {"operator_precedence", "lowest_precedence"}};
static void cont__307_10(void);
static void cont__307_11(void);
static NODE *func__307_12;
static void entry__307_12(void);
static FRAME_INFO frame__307_12 = {2, {"node", "operator_precedence"}};
static void cont__307_13(void);
static void cont__307_14(void);
static void cont__307_15(void);
static NODE *func__308_1;
static void entry__308_1(void);
static FRAME_INFO frame__308_1 = {4, {"node", "parent", "arguments", "n"}};
static void cont__308_2(void);
static void cont__308_3(void);
static void cont__308_4(void);
static void cont__308_5(void);
static NODE *func__308_6;
static void entry__308_6(void);
static FRAME_INFO frame__308_6 = {2, {"node", "arguments"}};
static void cont__308_7(void);
static NODE *func__308_8;
static void entry__308_8(void);
static FRAME_INFO frame__308_8 = {7, {"node", "arguments", "n", "operators", "operand_stack", "operator_stack", "update_stack"}};
static NODE *func__308_9;
static void entry__308_9(void);
static FRAME_INFO frame__308_9 = {5, {"right", "next_operator", "operator_stack", "operand_stack", "next_prec"}};
static void cont__308_10(void);
static NODE *func__308_11;
static void entry__308_11(void);
static FRAME_INFO frame__308_11 = {1, {"next_operator"}};
static void cont__308_12(void);
static NODE *func__308_13;
static void entry__308_13(void);
static FRAME_INFO frame__308_13 = {0, {}};
static void cont__308_14(void);
static NODE *func__308_15;
static void entry__308_15(void);
static FRAME_INFO frame__308_15 = {5, {"break", "operator_stack", "next_prec", "operand_stack", "right"}};
static NODE *func__308_16;
static void entry__308_16(void);
static FRAME_INFO frame__308_16 = {10, {"operator_stack", "next_prec", "break", "operand_stack", "right", "operator", "prec", "functor", "left", "dummy"}};
static void cont__308_17(void);
static void cont__308_18(void);
static void cont__308_19(void);
static void cont__308_20(void);
static void cont__308_21(void);
static NODE *func__308_22;
static void entry__308_22(void);
static FRAME_INFO frame__308_22 = {1, {"prec"}};
static void cont__308_23(void);
static void cont__308_24(void);
static void cont__308_25(void);
static void cont__308_26(void);
static NODE *func__308_27;
static void entry__308_27(void);
static FRAME_INFO frame__308_27 = {1, {"operator"}};
static NODE *func__308_28;
static void entry__308_28(void);
static FRAME_INFO frame__308_28 = {1, {"operator"}};
static void cont__308_29(void);
static void cont__308_30(void);
static void cont__308_31(void);
static void cont__308_32(void);
static void cont__308_33(void);
static void cont__308_34(void);
static void cont__308_35(void);
static void cont__308_36(void);
static void cont__308_37(void);
static void cont__308_38(void);
static void cont__308_39(void);
static void cont__308_40(void);
static void cont__308_41(void);
static void cont__308_42(void);
static void cont__308_43(void);
static void cont__308_44(void);
static void cont__308_45(void);
static void cont__308_46(void);
static NODE *func__308_47;
static void entry__308_47(void);
static FRAME_INFO frame__308_47 = {5, {"i", "update_stack", "arguments", "n", "operators"}};
static void cont__308_48(void);
static void cont__308_49(void);
static NODE *func__308_50;
static void entry__308_50(void);
static FRAME_INFO frame__308_50 = {2, {"operators", "i"}};
static void cont__308_51(void);
static NODE *func__308_52;
static void entry__308_52(void);
static FRAME_INFO frame__308_52 = {0, {}};
static void cont__308_53(void);
static void cont__308_54(void);
static void cont__308_55(void);
static void cont__308_56(void);
static void cont__308_57(void);
static NODE *func__308_58;
static void entry__308_58(void);
static FRAME_INFO frame__308_58 = {2, {"node", "parent"}};
static void cont__308_59(void);
static void cont__308_60(void);
static void cont__308_61(void);
static void cont__308_62(void);
static void cont__309_1(void);
static void cont__309_2(void);
static void cont__309_3(void);
static void cont__309_4(void);
static void cont__309_5(void);
static void cont__309_6(void);
static void cont__309_7(void);
static void cont__309_8(void);
static void cont__309_9(void);
static void cont__309_10(void);
static void cont__310_1(void);
static NODE *string__395c5a51a203e553;
static void cont__310_3(void);
static void cont__311_1(void);
static void cont__311_2(void);
static void cont__312_1(void);
static void cont__312_2(void);
static void cont__312_3(void);
static void cont__312_4(void);
static void cont__312_5(void);
static void cont__312_6(void);
static void cont__312_7(void);
static void cont__312_8(void);
static void cont__312_9(void);
static void cont__312_10(void);
static void cont__312_11(void);
static void cont__312_12(void);
static void cont__312_13(void);
static void cont__313_1(void);
static void cont__313_2(void);
static void cont__314_1(void);
static NODE *string__2d7981f4e6282be1;
static void cont__314_3(void);
static void cont__315_1(void);
static void cont__315_2(void);
static void cont__316_1(void);
static NODE *string__2d7981f4e6202be0;
static void cont__316_3(void);
static NODE *func__317_1;
static void entry__317_1(void);
static FRAME_INFO frame__317_1 = {1, {"node"}};
static void cont__317_2(void);
static void cont__317_3(void);
static void cont__317_4(void);
static void cont__317_5(void);
static void cont__317_6(void);
static void cont__317_7(void);
static void cont__317_8(void);
static void cont__317_9(void);
static void cont__318_1(void);
static void cont__318_2(void);
static void cont__318_3(void);
static void cont__319_1(void);
static void cont__320_1(void);
static void cont__320_2(void);
static void cont__320_3(void);
static void cont__320_4(void);
static void cont__320_5(void);
static void cont__321_1(void);
static void cont__321_2(void);
static void cont__321_3(void);
static void cont__321_4(void);
static void cont__321_5(void);
static void cont__322_1(void);
static void cont__322_2(void);
static void cont__323_1(void);
static void cont__323_2(void);
static void cont__323_3(void);
static void cont__323_4(void);
static void cont__324_1(void);
static void cont__324_2(void);
static void cont__325_1(void);
static void cont__325_2(void);
static void cont__325_3(void);
static NODE *string__5b01b0908c396eea;
static void cont__325_5(void);
static void cont__325_6(void);
static void cont__325_7(void);
static void cont__325_8(void);
static void cont__325_9(void);
static void cont__326_1(void);
static void cont__326_2(void);
static void cont__326_3(void);
static void cont__326_4(void);
static void cont__326_5(void);
static void cont__326_6(void);
static void cont__326_7(void);
static void cont__326_8(void);
static void cont__326_9(void);
static void cont__326_10(void);
static void cont__326_11(void);
static void cont__326_12(void);
static void cont__326_13(void);
static void cont__326_14(void);
static void cont__326_15(void);
static void cont__326_16(void);
static void cont__327_1(void);
static void cont__327_2(void);
static void cont__327_3(void);
static void cont__328_1(void);
static void cont__328_2(void);
static NODE *func__328_3;
static void entry__328_3(void);
static FRAME_INFO frame__328_3 = {1, {"node"}};
static void cont__328_4(void);
static void cont__328_5(void);
static void cont__328_6(void);
static void cont__328_7(void);
static void cont__328_8(void);
static NODE *string__137554cc13b7640e;
static void cont__328_10(void);
static NODE *func__328_11;
static void entry__328_11(void);
static FRAME_INFO frame__328_11 = {4, {"node", "stream", "return", "arguments"}};
static void exit__328_11(void);
static void cont__328_12(void);
static void cont__328_13(void);
static void cont__328_14(void);
static NODE *func__328_15;
static void entry__328_15(void);
static FRAME_INFO frame__328_15 = {1, {"stream"}};
static NODE *string__733ccdbfc49ced05;
static void cont__328_17(void);
static void cont__328_18(void);
static void cont__328_19(void);
static NODE *func__328_20;
static void entry__328_20(void);
static FRAME_INFO frame__328_20 = {4, {"node", "arguments", "return", "functor"}};
static void cont__328_21(void);
static void cont__328_22(void);
static void cont__328_23(void);
static void cont__328_24(void);
static NODE *func__328_25;
static void entry__328_25(void);
static FRAME_INFO frame__328_25 = {4, {"node", "functor", "arguments", "return"}};
static NODE *func__328_26;
static void entry__328_26(void);
static FRAME_INFO frame__328_26 = {4, {"node", "functor", "arguments", "return"}};
static void cont__328_27(void);
static void cont__328_28(void);
static void cont__328_29(void);
static void cont__328_30(void);
static void cont__328_31(void);
static void cont__328_32(void);
static void cont__328_33(void);
static NODE *func__328_34;
static void entry__328_34(void);
static FRAME_INFO frame__328_34 = {4, {"node", "functor", "arguments", "return"}};
static NODE *func__328_35;
static void entry__328_35(void);
static FRAME_INFO frame__328_35 = {4, {"node", "functor", "arguments", "return"}};
static void cont__328_36(void);
static void cont__328_37(void);
static void cont__328_38(void);
static void cont__328_39(void);
static void cont__328_40(void);
static void cont__328_41(void);
static void cont__328_42(void);
static void cont__328_43(void);
static void cont__328_44(void);
static void cont__328_45(void);
static void cont__328_46(void);
static void cont__328_47(void);
static void cont__329_1(void);
static void cont__329_2(void);
static void cont__329_3(void);
static void cont__329_4(void);
static void cont__329_5(void);
static void cont__329_6(void);
static void cont__329_7(void);
static void cont__329_8(void);
static void cont__329_9(void);
static void cont__329_10(void);
static void cont__329_11(void);
static void cont__329_12(void);
static void cont__329_13(void);
static void cont__329_14(void);
static void cont__330_1(void);
static void cont__330_2(void);
static void cont__330_3(void);
static void cont__330_4(void);
static void cont__330_5(void);
static void cont__330_6(void);
static void cont__330_7(void);
static void cont__330_8(void);
static NODE *func__331_1;
static void entry__331_1(void);
static FRAME_INFO frame__331_1 = {1, {"node"}};
static void cont__331_2(void);
static void cont__331_3(void);
static void cont__332_1(void);
static void cont__332_2(void);
static void cont__332_3(void);
static void cont__332_4(void);
static void cont__332_5(void);
static void cont__333_1(void);
static void cont__334_1(void);
static void cont__334_2(void);
static void cont__334_3(void);
static void cont__334_4(void);
static void cont__335_1(void);
static void cont__335_2(void);
static NODE *string__2d7981f4e6602bfb;
static void cont__335_4(void);
static void cont__336_1(void);
static void cont__336_2(void);
static void cont__336_3(void);
static void cont__336_4(void);
static void cont__337_1(void);
static void cont__337_2(void);
static void cont__337_3(void);
static void cont__337_4(void);
static void cont__337_5(void);
static void cont__337_6(void);
static void cont__337_7(void);
static void cont__337_8(void);
static void cont__337_9(void);
static void cont__337_10(void);
static void cont__337_11(void);
static void cont__338_1(void);
static void cont__338_2(void);
static void cont__338_3(void);
static void cont__338_4(void);
static void cont__338_5(void);
static void cont__338_6(void);
static void cont__338_7(void);
static void cont__338_8(void);
static void cont__338_9(void);
static void cont__338_10(void);
static void cont__338_11(void);
static void cont__338_12(void);
static void cont__339_1(void);
static void cont__339_2(void);
static void cont__339_3(void);
static void cont__339_4(void);
static void cont__339_5(void);
static NODE *func__339_6;
static void entry__339_6(void);
static FRAME_INFO frame__339_6 = {1, {"node"}};
static void cont__339_7(void);
static NODE *func__339_8;
static void entry__339_8(void);
static FRAME_INFO frame__339_8 = {2, {"remark_statement", "node"}};
static void cont__339_9(void);
static void cont__339_10(void);
static void cont__339_11(void);
static void cont__339_12(void);
static void cont__339_13(void);
static void cont__339_14(void);
static void cont__339_15(void);
static void cont__339_16(void);
static void cont__339_17(void);
static void cont__339_18(void);
static void cont__339_19(void);
static void cont__339_20(void);
static void cont__339_21(void);
static void cont__339_22(void);
static void cont__339_23(void);
static void cont__339_24(void);
static void cont__339_25(void);
static void cont__339_26(void);
static void cont__339_27(void);
static void cont__339_28(void);
static void cont__339_29(void);
static void cont__339_30(void);
static void cont__340_1(void);
static void cont__340_2(void);
static void cont__340_3(void);
static void cont__340_4(void);
static void cont__341_1(void);
static void cont__342_1(void);
static void cont__342_2(void);
static void cont__342_3(void);
static void cont__342_4(void);
static void cont__342_5(void);
static void cont__342_6(void);
static void cont__342_7(void);
static void cont__342_8(void);
static void cont__342_9(void);
static void cont__342_10(void);
static void cont__343_1(void);
static void cont__343_2(void);
static void cont__344_1(void);
static NODE *string__2d7981f4e6482bec;
static void cont__344_3(void);
static void cont__345_1(void);
static NODE *string__fa732415f216be5;
static void cont__345_3(void);
static void cont__346_1(void);
static void cont__347_1(void);
static void cont__348_1(void);
static NODE *string__2d7981f4e6782bed;
static void cont__348_3(void);
static void cont__348_4(void);
static void cont__348_5(void);
static void cont__348_6(void);
static void cont__349_1(void);
static void cont__349_2(void);
static void cont__349_3(void);
static void cont__349_4(void);
static void cont__349_5(void);
static void cont__349_6(void);
static void cont__349_7(void);
static void cont__349_8(void);
static void cont__349_9(void);
static void cont__349_10(void);
static void cont__349_11(void);
static void cont__349_12(void);
static NODE *string__e1e3be9ec64af0e1;
static void cont__349_14(void);
static void cont__349_15(void);
static void cont__350_1(void);
static void cont__350_2(void);
static void cont__350_3(void);
static void cont__350_4(void);
static void cont__351_1(void);
static void cont__351_2(void);
static NODE *func__351_3;
static void entry__351_3(void);
static FRAME_INFO frame__351_3 = {4, {"node", "arguments", "functor", "argument"}};
static void cont__351_4(void);
static void cont__351_5(void);
static void cont__351_6(void);
static void cont__351_7(void);
static void cont__351_8(void);
static void cont__351_9(void);
static void cont__351_10(void);
static void cont__351_11(void);
static void cont__351_12(void);
static void cont__351_13(void);
static NODE *func__351_14;
static void entry__351_14(void);
static FRAME_INFO frame__351_14 = {1, {"argument"}};
static void cont__351_15(void);
static NODE *func__351_16;
static void entry__351_16(void);
static FRAME_INFO frame__351_16 = {2, {"argument", "functor"}};
static NODE *func__351_17;
static void entry__351_17(void);
static FRAME_INFO frame__351_17 = {1, {"argument"}};
static void cont__351_18(void);
static void cont__351_19(void);
static void cont__351_20(void);
static NODE *func__351_21;
static void entry__351_21(void);
static FRAME_INFO frame__351_21 = {1, {"functor"}};
static void cont__351_22(void);
static void cont__351_23(void);
static void cont__351_24(void);
static void cont__351_25(void);
static void cont__351_26(void);
static void cont__351_27(void);
static void cont__351_28(void);
static void cont__351_29(void);
static void cont__352_1(void);
static void cont__352_2(void);
static void cont__352_3(void);
static void cont__352_4(void);
static void cont__352_5(void);
static void cont__352_6(void);
static void cont__352_7(void);
static void cont__352_8(void);
static void cont__352_9(void);
static void cont__352_10(void);
static void cont__352_11(void);
static void cont__352_12(void);
static void cont__352_13(void);
static void cont__352_14(void);
static void cont__352_15(void);
static void cont__353_1(void);
static void cont__353_2(void);
static void cont__353_3(void);
static void cont__353_4(void);
static void cont__353_5(void);
static void cont__353_6(void);
static void cont__353_7(void);
static void cont__354_1(void);
static void cont__354_2(void);
static void cont__354_3(void);
static void cont__355_1(void);
static void cont__355_2(void);
static void cont__355_3(void);
static void cont__360_1(void);
static void cont__360_2(void);
static NODE *string__2f401958355b9795;
static void cont__360_4(void);
static NODE *func__360_5;
static void entry__360_5(void);
static FRAME_INFO frame__360_5 = {1, {"node"}};
static NODE *func__360_6;
static void entry__360_6(void);
static FRAME_INFO frame__360_6 = {2, {"break", "node"}};
static void cont__360_7(void);
static void cont__360_8(void);
static NODE *func__360_9;
static void entry__360_9(void);
static FRAME_INFO frame__360_9 = {3, {"source", "node", "break"}};
static void cont__360_10(void);
static NODE *func__360_11;
static void entry__360_11(void);
static FRAME_INFO frame__360_11 = {3, {"source", "node", "break"}};
static void cont__360_12(void);
static NODE *func__360_13;
static void entry__360_13(void);
static FRAME_INFO frame__360_13 = {2, {"node", "destination"}};
static void cont__360_14(void);
static void cont__360_15(void);
static void cont__360_16(void);
static NODE *func__360_17;
static void entry__360_17(void);
static FRAME_INFO frame__360_17 = {1, {"destination"}};
static void cont__360_18(void);
static void cont__360_19(void);
static void cont__360_20(void);
static NODE *func__360_21;
static void entry__360_21(void);
static FRAME_INFO frame__360_21 = {1, {"node"}};
static NODE *string__bade31b19fa2fd8a;
static void cont__360_23(void);
static void cont__360_24(void);
static void cont__360_25(void);
static void cont__360_26(void);
static void cont__360_27(void);
static void cont__360_28(void);
static void cont__360_29(void);
static void cont__360_30(void);
static void cont__360_31(void);
static void cont__360_32(void);
static void cont__361_1(void);
static void cont__361_2(void);
static NODE *string__4f498b003024119a;
static void cont__361_4(void);
static void cont__361_5(void);
static void cont__362_1(void);
static NODE *string__8782cdb8103cde5a;
static void cont__362_3(void);
static void cont__362_4(void);
static NODE *string__5ed2969d8211684f;
static void cont__363_2(void);
static void cont__363_3(void);
static void cont__364_1(void);
static void cont__364_2(void);
static NODE *func__364_3;
static void entry__364_3(void);
static FRAME_INFO frame__364_3 = {3, {"node", "return_statement", "statement_found"}};
static void cont__364_4(void);
static NODE *func__364_5;
static void entry__364_5(void);
static FRAME_INFO frame__364_5 = {3, {"statement", "return_statement", "statement_found"}};
static void cont__364_6(void);
static NODE *func__364_7;
static void entry__364_7(void);
static FRAME_INFO frame__364_7 = {3, {"return_statement", "statement", "statement_found"}};
static void cont__364_8(void);
static NODE *func__364_9;
static void entry__364_9(void);
static FRAME_INFO frame__364_9 = {1, {"return_statement"}};
static NODE *string__51cbf656a5622dd3;
static void cont__364_11(void);
static void cont__364_12(void);
static NODE *func__364_13;
static void entry__364_13(void);
static FRAME_INFO frame__364_13 = {2, {"return_statement", "statement"}};
static void cont__364_14(void);
static void cont__364_15(void);
static NODE *func__364_16;
static void entry__364_16(void);
static FRAME_INFO frame__364_16 = {1, {"node"}};
static NODE *string__e72d5b3e0e5238e;
static void cont__364_18(void);
static void cont__364_19(void);
static void cont__365_1(void);
static NODE *string__2d7981f4e5f02b9a;
static void cont__365_3(void);
static void cont__365_4(void);
static void cont__365_5(void);
static void cont__365_6(void);
static void cont__365_7(void);
static void cont__365_8(void);
static void cont__366_1(void);
static void cont__366_2(void);
static void cont__366_3(void);
static void cont__367_1(void);
static void cont__367_2(void);
static void cont__367_3(void);
static NODE *string__74dcac9584a4c074;
static void cont__367_5(void);
static void cont__368_1(void);
static void cont__368_2(void);
static void cont__368_3(void);
static NODE *string__60ae90b5df87d5c;
static void cont__368_5(void);
static void cont__369_1(void);
static void cont__369_2(void);
static void cont__369_3(void);
static NODE *string__140aeb0b5d107d5d;
static void cont__369_5(void);
static void cont__370_1(void);
static void cont__370_2(void);
static void cont__370_3(void);
static NODE *string__1e0ae90b5d087d5c;
static void cont__370_5(void);
static void cont__371_1(void);
static void cont__371_2(void);
static void cont__371_3(void);
static NODE *string__1e0aea8b5d407d5c;
static void cont__371_5(void);
static NODE *string__9a4c0f9815d2209f;
static NODE *string__461f56c301b292bb;
static NODE *string__545aebc3eac0d03b;
static NODE *string__701f5702012bd2b9;
static void cont__372_5(void);
static void cont__372_6(void);
static void cont__372_7(void);
static void cont__372_8(void);
static NODE *string__4c5ae8c3ea492032;
static void cont__372_10(void);
static void cont__373_1(void);
static void cont__373_2(void);
static void cont__373_3(void);
static NODE *string__2a0aef0b5de07d5c;
static void cont__373_5(void);
static NODE *string__399cfc434d66f26;
static void cont__374_2(void);
static void cont__374_3(void);
static void cont__375_1(void);
static void cont__375_2(void);
static void cont__376_1(void);
static NODE *string__2d7981f4e6702bea;
static void cont__377_2(void);
static void cont__378_1(void);
static void cont__378_2(void);
static void cont__378_3(void);
static void cont__378_4(void);
static void cont__379_1(void);
static void cont__379_2(void);
static void cont__379_3(void);
static void cont__379_4(void);
static void cont__379_5(void);
static void cont__380_1(void);
static void cont__380_2(void);
static void cont__380_3(void);
static void cont__380_4(void);
static void cont__380_5(void);
static void cont__380_6(void);
static void cont__380_7(void);
static void cont__380_8(void);
static void cont__380_9(void);
static void cont__380_10(void);
static void cont__380_11(void);
static void cont__381_1(void);
static void cont__381_2(void);
static void cont__381_3(void);
static NODE *string__227de92deba39b6b;
static void cont__382_2(void);
static void cont__382_3(void);
static void cont__382_4(void);
static void cont__382_5(void);
static void cont__382_6(void);
void run__parser(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__parser, NULL, 209, 209, 5, 12},
  {cont__216_2, NULL, 210, 210, 5, 12},
  {cont__216_4, NULL, 211, 211, 5, 12},
  {cont__216_6, NULL, 212, 212, 5, 12},
  {cont__216_8, NULL, 213, 213, 5, 13},
  {cont__216_10, NULL, 214, 214, 5, 13},
  {cont__216_12, NULL, 215, 215, 5, 12},
  {cont__216_14, NULL, 216, 216, 5, 12},
  {cont__216_15, NULL, 217, 217, 5, 11},
  {cont__216_17, NULL, 218, 218, 5, 12},
  {cont__216_19, NULL, 219, 219, 5, 11},
  {cont__216_21, NULL, 220, 220, 5, 12},
  {cont__216_23, NULL, 221, 221, 5, 11},
  {cont__216_25, NULL, 222, 222, 5, 12},
  {cont__216_27, NULL, 223, 223, 5, 12},
  {cont__216_29, NULL, 224, 224, 5, 12},
  {cont__216_31, NULL, 225, 225, 5, 12},
  {cont__216_33, NULL, 226, 226, 5, 12},
  {cont__216_35, NULL, 227, 227, 5, 11},
  {cont__216_37, NULL, 228, 228, 5, 11},
  {cont__216_39, NULL, 207, 228, 1, 12},
  {cont__216_40, NULL, 267, 273, 1, 15},
  {cont__230_5, NULL, 275, 275, 10, 29},
  {cont__231_1, NULL, 275, 275, 1, 50},
  {cont__231_2, NULL, 276, 276, 9, 34},
  {cont__232_1, NULL, 276, 276, 1, 61},
  {cont__232_2, NULL, 277, 277, 10, 36},
  {cont__233_1, NULL, 277, 277, 1, 64},
  {cont__233_2, NULL, 278, 278, 10, 25},
  {cont__234_1, NULL, 278, 278, 1, 42},
  {cont__234_2, NULL, 288, 288, 1, 31},
  {cont__237_1, NULL, 289, 289, 37, 52},
  {cont__238_1, NULL, 289, 289, 1, 53},
  {cont__238_2, NULL, 290, 290, 1, 23},
  {cont__239_1, NULL, 292, 300, 1, 42},
  {cont__240_3, NULL, 302, 310, 1, 42},
  {cont__241_4, NULL, 312, 319, 1, 47},
  {cont__242_3, NULL, 323, 323, 5, 24},
  {cont__243_1, NULL, 325, 325, 5, 25},
  {cont__243_2, NULL, },
  {cont__243_5, NULL, 332, 332, 9, 29},
  {cont__243_6, NULL, },
  {cont__243_8, NULL, },
  {cont__243_9, NULL, 321, 333, 1, 23},
  {cont__243_10, NULL, 337, 337, 5, 24},
  {cont__244_1, NULL, 339, 339, 5, 22},
  {cont__244_2, NULL, 340, 340, 5, 25},
  {cont__244_3, NULL, },
  {cont__244_10, NULL, 349, 349, 9, 29},
  {cont__244_11, NULL, },
  {cont__244_12, NULL, },
  {cont__244_13, NULL, 335, 350, 1, 23},
  {cont__244_14, NULL, 354, 354, 5, 24},
  {cont__245_1, NULL, 356, 356, 5, 30},
  {cont__245_2, NULL, 357, 357, 5, 16},
  {cont__245_3, NULL, 358, 358, 5, 25},
  {cont__245_4, NULL, 352, 358, 1, 26},
  {cont__245_5, NULL, 363, 363, 11, 24},
  {cont__246_2, NULL, 363, 363, 38, 46},
  {cont__246_3, NULL, 363, 363, 33, 47},
  {cont__246_4, NULL, 363, 363, 1, 47},
  {cont__246_5, NULL, 368, 368, 5, 33},
  {cont__247_1, NULL, 371, 371, 5, 39},
  {cont__247_2, NULL, },
  {cont__247_13, NULL, 365, 380, 1, 43},
  {cont__247_15, NULL, 386, 386, 5, 35},
  {cont__248_1, NULL, 387, 387, 5, 30},
  {cont__248_2, NULL, 390, 390, 9, 27},
  {cont__248_3, NULL, },
  {cont__248_6, NULL, 394, 394, 9, 34},
  {cont__248_7, NULL, },
  {cont__248_8, NULL, },
  {cont__248_9, NULL, },
  {cont__248_30, NULL, 382, 410, 1, 52},
  {cont__248_32, NULL, 416, 416, 5, 31},
  {cont__249_1, NULL, 417, 417, 5, 30},
  {cont__249_2, NULL, },
  {cont__249_11, NULL, 412, 425, 1, 43},
  {cont__249_13, NULL, 427, 427, 16, 40},
  {cont__250_1, NULL, 427, 427, 1, 41},
  {cont__250_2, NULL, 428, 428, 26, 36},
  {cont__251_2, NULL, 428, 428, 13, 37},
  {cont__251_3, NULL, 428, 428, 55, 67},
  {cont__251_4, NULL, 428, 428, 50, 68},
  {cont__251_5, NULL, 428, 428, 1, 68},
  {cont__251_6, NULL, 434, 434, 5, 33},
  {cont__252_1, NULL, 435, 435, 5, 41},
  {cont__252_2, NULL, },
  {cont__252_12, NULL, 430, 443, 1, 41},
  {cont__252_14, NULL, 449, 449, 5, 30},
  {cont__253_1, NULL, 450, 450, 5, 41},
  {cont__253_2, NULL, },
  {cont__253_12, NULL, 445, 458, 1, 43},
  {cont__253_14, NULL, 460, 460, 12, 44},
  {cont__254_1, NULL, 460, 460, 1, 45},
  {cont__254_2, NULL, 461, 461, 24, 34},
  {cont__255_1, NULL, 461, 461, 11, 35},
  {cont__255_2, NULL, 461, 461, 49, 57},
  {cont__255_3, NULL, 461, 461, 44, 58},
  {cont__255_4, NULL, 461, 461, 1, 58},
  {cont__255_5, NULL, 467, 467, 5, 30},
  {cont__256_1, NULL, 468, 468, 5, 39},
  {cont__256_2, NULL, },
  {cont__256_11, NULL, 463, 476, 1, 41},
  {cont__256_13, NULL, 480, 480, 5, 50},
  {cont__257_1, NULL, 481, 481, 52, 73},
  {cont__257_2, NULL, 481, 481, 34, 73},
  {cont__257_3, NULL, 481, 481, 14, 74},
  {cont__257_4, NULL, 481, 481, 5, 75},
  {cont__257_5, NULL, 478, 481, 1, 76},
  {cont__257_6, NULL, 502, 502, 44, 68},
  {cont__258_1, NULL, 502, 503, 1, 40},
  {cont__258_2, NULL, 510, 510, 22, 53},
  {cont__259_1, NULL, 510, 510, 56, 77},
  {cont__259_2, NULL, 510, 510, 14, 77},
  {cont__259_3, NULL, 510, 510, 5, 78},
  {cont__259_4, NULL, 505, 510, 1, 79},
  {cont__259_5, NULL, 512, 512, 28, 53},
  {cont__260_1, NULL, 512, 512, 1, 67},
  {cont__260_2, NULL, 513, 513, 1, 29},
  {cont__261_1, NULL, 514, 514, 1, 59},
  {cont__262_1, NULL, 515, 515, 1, 32},
  {cont__263_1, NULL, 517, 521, 1, 40},
  {cont__264_9, NULL, 526, 526, 20, 44},
  {cont__265_1, NULL, 526, 526, 20, 58},
  {cont__265_2, NULL, 526, 526, 5, 59},
  {cont__265_3, NULL, 523, 527, 1, 48},
  {cont__265_4, NULL, 532, 532, 20, 44},
  {cont__266_1, NULL, 532, 532, 20, 57},
  {cont__266_2, NULL, 532, 532, 5, 58},
  {cont__266_3, NULL, 529, 533, 1, 48},
  {cont__266_4, NULL, },
  {cont__267_4, NULL, 548, 548, 14, 33},
  {cont__267_5, NULL, 548, 548, 14, 51},
  {cont__267_6, NULL, 548, 548, 5, 52},
  {cont__267_7, NULL, 549, 549, 5, 36},
  {cont__267_9, NULL, 550, 550, 5, 15},
  {cont__267_10, NULL, 538, 551, 1, 23},
  {cont__267_11, NULL, 553, 561, 1, 58},
  {cont__268_5, NULL, 567, 567, 5, 31},
  {cont__269_1, NULL, 563, 568, 1, 23},
  {cont__269_2, NULL, 574, 574, 5, 40},
  {cont__270_1, NULL, 570, 575, 1, 23},
  {cont__270_2, NULL, 577, 577, 18, 52},
  {cont__271_1, NULL, 577, 577, 1, 53},
  {cont__271_2, NULL, 578, 578, 29, 62},
  {cont__272_1, NULL, 578, 578, 1, 63},
  {cont__272_2, NULL, 579, 579, 1, 51},
  {cont__273_1, NULL, 582, 582, 15, 54},
  {cont__274_1, NULL, 581, 582, 1, 77},
  {cont__274_2, NULL, 586, 586, 17, 27},
  {cont__275_1, NULL, 586, 586, 5, 37},
  {cont__275_2, NULL, 587, 587, 19, 29},
  {cont__275_3, NULL, 587, 587, 14, 29},
  {cont__275_4, NULL, 587, 587, 5, 30},
  {cont__275_5, NULL, 588, 588, 14, 25},
  {cont__275_6, NULL, 588, 588, 37, 48},
  {cont__275_7, NULL, 588, 588, 28, 49},
  {cont__275_8, NULL, 588, 588, 52, 62},
  {cont__275_9, NULL, 588, 588, 14, 62},
  {cont__275_10, NULL, 588, 588, 5, 63},
  {cont__275_11, NULL, 584, 588, 1, 64},
  {cont__275_12, NULL, 590, 590, 1, 26},
  {cont__276_1, NULL, 591, 591, 34, 51},
  {cont__277_1, NULL, 591, 591, 22, 61},
  {cont__277_2, NULL, 591, 591, 1, 61},
  {cont__277_4, NULL, 592, 592, 1, 23},
  {cont__278_1, NULL, 593, 593, 33, 49},
  {cont__279_1, NULL, 593, 593, 21, 59},
  {cont__279_2, NULL, 593, 593, 1, 59},
  {cont__279_4, NULL, 594, 594, 22, 31},
  {cont__280_1, NULL, 594, 594, 33, 42},
  {cont__280_2, NULL, 594, 594, 1, 43},
  {cont__280_3, NULL, 595, 595, 31, 45},
  {cont__281_1, NULL, 595, 595, 19, 55},
  {cont__281_2, NULL, 595, 595, 1, 55},
  {cont__281_4, NULL, 599, 599, 5, 29},
  {cont__282_1, NULL, 603, 603, 7, 63},
  {cont__282_2, NULL, },
  {cont__282_3, NULL, 597, 604, 1, 23},
  {cont__282_4, NULL, 608, 608, 5, 47},
  {cont__283_1, NULL, },
  {cont__283_5, NULL, 606, 611, 1, 55},
  {cont__283_6, NULL, },
  {cont__284_2, NULL, 613, 618, 1, 36},
  {cont__284_3, NULL, 622, 622, 5, 32},
  {cont__285_1, NULL, },
  {cont__285_9, NULL, 620, 632, 1, 35},
  {cont__285_10, NULL, 639, 639, 15, 32},
  {cont__286_1, NULL, 639, 639, 9, 32},
  {cont__286_2, NULL, 640, 640, 15, 31},
  {cont__286_3, NULL, 640, 640, 9, 31},
  {cont__286_4, NULL, 641, 641, 15, 29},
  {cont__286_5, NULL, 641, 641, 9, 29},
  {cont__286_6, NULL, 642, 642, 9, 19},
  {cont__286_7, NULL, },
  {cont__286_8, NULL, },
  {cont__286_9, NULL, },
  {cont__286_14, NULL, 634, 648, 1, 42},
  {cont__286_15, NULL, 655, 655, 5, 45},
  {cont__287_2, NULL, 650, 655, 1, 46},
  {cont__287_3, NULL, 657, 657, 23, 45},
  {cont__288_1, NULL, 657, 657, 1, 63},
  {cont__288_2, NULL, 662, 662, 5, 31},
  {cont__289_1, NULL, 665, 665, 5, 20},
  {cont__289_2, NULL, 659, 666, 1, 23},
  {cont__289_3, NULL, },
  {cont__290_5, NULL, },
  {cont__290_6, NULL, 668, 675, 1, 59},
  {cont__290_8, NULL, },
  {cont__291_9, NULL, 685, 685, 17, 42},
  {cont__291_10, NULL, 685, 685, 5, 64},
  {cont__291_11, NULL, 686, 686, 5, 15},
  {cont__291_12, NULL, 677, 686, 1, 16},
  {cont__291_14, NULL, 688, 701, 1, 55},
  {cont__292_20, NULL, 706, 706, 5, 34},
  {cont__293_1, NULL, 707, 707, 5, 28},
  {cont__293_2, NULL, 709, 709, 10, 34},
  {cont__293_3, NULL, 709, 709, 37, 74},
  {cont__293_4, NULL, 709, 709, 10, 74},
  {cont__293_5, NULL, 709, 709, 5, 75},
  {cont__293_6, NULL, 710, 710, 5, 20},
  {cont__293_7, NULL, 703, 712, 1, 21},
  {cont__293_8, NULL, 717, 717, 19, 31},
  {cont__294_1, NULL, 717, 717, 7, 32},
  {cont__294_2, NULL, 718, 718, 7, 32},
  {cont__294_3, NULL, 719, 719, 7, 35},
  {cont__294_4, NULL, 720, 720, 7, 35},
  {cont__294_5, NULL, },
  {cont__294_6, NULL, 714, 720, 1, 37},
  {cont__294_7, NULL, 722, 725, 1, 62},
  {cont__295_5, NULL, 730, 730, 5, 31},
  {cont__296_1, NULL, 734, 734, 10, 43},
  {cont__296_2, NULL, 734, 734, 5, 44},
  {cont__296_3, NULL, 735, 735, 9, 21},
  {cont__296_4, NULL, 735, 735, 23, 44},
  {cont__296_5, NULL, 735, 735, 23, 58},
  {cont__296_6, NULL, 735, 735, 5, 59},
  {cont__296_7, NULL, 727, 737, 1, 21},
  {cont__296_8, NULL, 739, 739, 19, 41},
  {cont__297_1, NULL, 739, 739, 44, 64},
  {cont__297_2, NULL, 739, 739, 1, 64},
  {cont__297_3, NULL, 744, 744, 32, 66},
  {cont__298_2, NULL, 744, 744, 12, 67},
  {cont__298_3, NULL, 744, 744, 5, 68},
  {cont__298_4, NULL, 745, 745, 5, 15},
  {cont__298_5, NULL, 741, 745, 1, 16},
  {cont__298_6, NULL, },
  {cont__299_10, NULL, 747, 759, 1, 23},
  {cont__299_12, NULL, },
  {cont__300_5, NULL, 761, 774, 1, 23},
  {cont__300_6, NULL, 776, 784, 1, 13},
  {cont__301_1, NULL, 786, 786, 58, 79},
  {cont__302_1, NULL, 786, 786, 42, 79},
  {cont__302_2, NULL, 786, 786, 1, 80},
  {cont__302_3, NULL, 788, 808, 1, 9},
  {cont__303_1, NULL, 811, 811, 18, 66},
  {cont__304_1, NULL, 810, 811, 1, 67},
  {cont__304_2, NULL, 813, 813, 17, 47},
  {cont__305_1, NULL, 813, 813, 1, 69},
  {cont__305_2, NULL, 819, 819, 5, 39},
  {cont__306_1, NULL, 821, 821, 5, 32},
  {cont__306_2, NULL, 815, 821, 1, 33},
  {cont__306_3, NULL, 825, 825, 5, 56},
  {cont__307_1, NULL, },
  {cont__307_14, NULL, 823, 835, 1, 63},
  {cont__307_15, NULL, 837, 894, 1, 70},
  {cont__308_62, NULL, 898, 898, 5, 24},
  {cont__309_1, NULL, 899, 899, 5, 27},
  {cont__309_2, NULL, 900, 900, 26, 48},
  {cont__309_3, NULL, 900, 900, 10, 48},
  {cont__309_4, NULL, 900, 900, 5, 49},
  {cont__309_5, NULL, 902, 902, 22, 52},
  {cont__309_6, NULL, 902, 902, 7, 53},
  {cont__309_7, NULL, 902, 902, 7, 74},
  {cont__309_8, NULL, },
  {cont__309_9, NULL, 896, 903, 1, 22},
  {cont__309_10, NULL, 905, 905, 26, 62},
  {cont__310_1, NULL, 905, 905, 1, 76},
  {cont__310_3, NULL, 908, 908, 15, 63},
  {cont__311_1, NULL, 907, 908, 1, 63},
  {cont__311_2, NULL, 918, 918, 13, 55},
  {cont__312_1, NULL, 919, 919, 13, 50},
  {cont__312_2, NULL, },
  {cont__312_3, NULL, 922, 922, 13, 28},
  {cont__312_4, NULL, 923, 923, 13, 52},
  {cont__312_5, NULL, },
  {cont__312_6, NULL, 926, 926, 13, 52},
  {cont__312_7, NULL, 927, 927, 13, 50},
  {cont__312_8, NULL, },
  {cont__312_9, NULL, },
  {cont__312_10, NULL, },
  {cont__312_11, NULL, },
  {cont__312_12, NULL, 910, 927, 1, 55},
  {cont__312_13, NULL, 930, 930, 8, 37},
  {cont__313_1, NULL, 929, 930, 1, 68},
  {cont__313_2, NULL, 932, 932, 28, 56},
  {cont__314_1, NULL, 932, 932, 1, 74},
  {cont__314_3, NULL, 933, 933, 29, 59},
  {cont__315_1, NULL, 933, 933, 1, 77},
  {cont__315_2, NULL, 934, 934, 29, 58},
  {cont__316_1, NULL, 934, 934, 1, 76},
  {cont__316_3, NULL, },
  {cont__317_5, NULL, 948, 948, 9, 24},
  {cont__317_6, NULL, 948, 948, 26, 61},
  {cont__317_7, NULL, 948, 948, 5, 62},
  {cont__317_8, NULL, 936, 949, 1, 23},
  {cont__317_9, NULL, 955, 955, 5, 31},
  {cont__318_1, NULL, 956, 956, 5, 36},
  {cont__318_2, NULL, 951, 956, 1, 37},
  {cont__318_3, NULL, 958, 964, 1, 11},
  {cont__319_1, NULL, 969, 969, 5, 24},
  {cont__320_1, NULL, 970, 970, 46, 69},
  {cont__320_2, NULL, 970, 970, 27, 70},
  {cont__320_3, NULL, 970, 970, 5, 71},
  {cont__320_4, NULL, 966, 970, 1, 72},
  {cont__320_5, NULL, 974, 974, 10, 44},
  {cont__321_1, NULL, 974, 974, 5, 44},
  {cont__321_2, NULL, 975, 975, 10, 44},
  {cont__321_3, NULL, 975, 975, 5, 44},
  {cont__321_4, NULL, 972, 975, 1, 45},
  {cont__321_5, NULL, 977, 977, 31, 49},
  {cont__322_1, NULL, 977, 977, 1, 49},
  {cont__322_2, NULL, 983, 983, 5, 36},
  {cont__323_1, NULL, 984, 984, 5, 47},
  {cont__323_2, NULL, 985, 985, 5, 23},
  {cont__323_3, NULL, 979, 985, 1, 24},
  {cont__323_4, NULL, 987, 987, 32, 69},
  {cont__324_1, NULL, 987, 987, 1, 70},
  {cont__324_2, NULL, 992, 992, 5, 43},
  {cont__325_1, NULL, 993, 993, 14, 59},
  {cont__325_2, NULL, 993, 993, 5, 60},
  {cont__325_3, NULL, 995, 995, 27, 64},
  {cont__325_5, NULL, 995, 995, 7, 64},
  {cont__325_6, NULL, 996, 996, 7, 31},
  {cont__325_7, NULL, },
  {cont__325_8, NULL, 989, 997, 1, 23},
  {cont__325_9, NULL, 1004, 1004, 33, 62},
  {cont__326_1, NULL, 1004, 1004, 24, 78},
  {cont__326_2, NULL, 1004, 1004, 9, 79},
  {cont__326_3, NULL, },
  {cont__326_4, NULL, 1007, 1007, 9, 24},
  {cont__326_5, NULL, 1010, 1010, 13, 45},
  {cont__326_6, NULL, 1012, 1012, 13, 32},
  {cont__326_7, NULL, },
  {cont__326_8, NULL, },
  {cont__326_9, NULL, },
  {cont__326_10, NULL, 1018, 1018, 20, 52},
  {cont__326_11, NULL, 1018, 1018, 11, 68},
  {cont__326_12, NULL, },
  {cont__326_13, NULL, },
  {cont__326_14, NULL, },
  {cont__326_15, NULL, 999, 1018, 1, 72},
  {cont__326_16, NULL, 1022, 1022, 29, 51},
  {cont__327_1, NULL, 1022, 1022, 5, 75},
  {cont__327_2, NULL, 1020, 1023, 1, 22},
  {cont__327_3, NULL, 1027, 1027, 5, 29},
  {cont__328_1, NULL, 1029, 1029, 5, 42},
  {cont__328_2, NULL, },
  {cont__328_6, NULL, 1037, 1037, 14, 59},
  {cont__328_7, NULL, 1037, 1037, 5, 60},
  {cont__328_8, NULL, 1040, 1040, 5, 46},
  {cont__328_10, NULL, },
  {cont__328_46, NULL, 1025, 1069, 1, 66},
  {cont__328_47, NULL, 1076, 1076, 9, 37},
  {cont__329_1, NULL, 1077, 1077, 9, 49},
  {cont__329_2, NULL, },
  {cont__329_3, NULL, 1080, 1080, 9, 37},
  {cont__329_4, NULL, 1081, 1081, 9, 50},
  {cont__329_5, NULL, },
  {cont__329_6, NULL, 1084, 1084, 9, 37},
  {cont__329_7, NULL, 1085, 1085, 9, 53},
  {cont__329_8, NULL, },
  {cont__329_9, NULL, 1086, 1086, 7, 36},
  {cont__329_10, NULL, 1086, 1086, 39, 79},
  {cont__329_11, NULL, 1086, 1086, 7, 79},
  {cont__329_12, NULL, },
  {cont__329_13, NULL, 1071, 1086, 1, 81},
  {cont__329_14, NULL, 1093, 1093, 9, 27},
  {cont__330_1, NULL, 1094, 1094, 9, 43},
  {cont__330_2, NULL, 1095, 1095, 9, 41},
  {cont__330_3, NULL, },
  {cont__330_4, NULL, 1096, 1096, 12, 56},
  {cont__330_5, NULL, 1096, 1096, 7, 56},
  {cont__330_6, NULL, },
  {cont__330_7, NULL, 1088, 1096, 1, 58},
  {cont__330_8, NULL, },
  {cont__331_2, NULL, 1098, 1103, 1, 33},
  {cont__331_3, NULL, 1109, 1109, 7, 26},
  {cont__332_1, NULL, 1111, 1111, 7, 24},
  {cont__332_2, NULL, 1112, 1112, 7, 27},
  {cont__332_3, NULL, },
  {cont__332_4, NULL, 1105, 1113, 1, 26},
  {cont__332_5, NULL, 1115, 1115, 1, 68},
  {cont__333_1, NULL, 1118, 1118, 14, 38},
  {cont__334_1, NULL, 1118, 1118, 50, 72},
  {cont__334_2, NULL, 1118, 1118, 41, 73},
  {cont__334_3, NULL, 1117, 1118, 1, 73},
  {cont__334_4, NULL, 1124, 1124, 5, 34},
  {cont__335_1, NULL, 1125, 1125, 5, 55},
  {cont__335_2, NULL, 1120, 1126, 1, 19},
  {cont__335_4, NULL, 1129, 1129, 17, 41},
  {cont__336_1, NULL, 1129, 1129, 53, 75},
  {cont__336_2, NULL, 1129, 1129, 44, 76},
  {cont__336_3, NULL, 1128, 1129, 1, 76},
  {cont__336_4, NULL, 1137, 1137, 23, 57},
  {cont__337_1, NULL, 1137, 1137, 11, 79},
  {cont__337_2, NULL, 1138, 1138, 42, 79},
  {cont__337_3, NULL, 1138, 1138, 20, 79},
  {cont__337_4, NULL, 1138, 1138, 11, 80},
  {cont__337_5, NULL, },
  {cont__337_6, NULL, 1139, 1139, 9, 46},
  {cont__337_7, NULL, },
  {cont__337_8, NULL, },
  {cont__337_9, NULL, 1140, 1140, 5, 15},
  {cont__337_10, NULL, 1131, 1140, 1, 16},
  {cont__337_11, NULL, 1148, 1148, 21, 66},
  {cont__338_1, NULL, 1148, 1148, 9, 75},
  {cont__338_2, NULL, 1149, 1149, 27, 75},
  {cont__338_3, NULL, 1149, 1149, 18, 75},
  {cont__338_4, NULL, 1149, 1149, 9, 76},
  {cont__338_5, NULL, },
  {cont__338_6, NULL, 1150, 1150, 7, 55},
  {cont__338_7, NULL, },
  {cont__338_8, NULL, 1151, 1151, 5, 26},
  {cont__338_9, NULL, 1152, 1152, 5, 19},
  {cont__338_10, NULL, 1153, 1153, 5, 15},
  {cont__338_11, NULL, 1142, 1153, 1, 16},
  {cont__338_12, NULL, 1158, 1158, 5, 18},
  {cont__339_1, NULL, 1162, 1162, 9, 33},
  {cont__339_2, NULL, 1164, 1164, 14, 55},
  {cont__339_3, NULL, 1164, 1164, 14, 65},
  {cont__339_4, NULL, 1164, 1164, 9, 66},
  {cont__339_5, NULL, },
  {cont__339_13, NULL, },
  {cont__339_14, NULL, },
  {cont__339_15, NULL, 1174, 1174, 9, 26},
  {cont__339_16, NULL, 1176, 1176, 9, 30},
  {cont__339_17, NULL, },
  {cont__339_18, NULL, 1178, 1178, 18, 56},
  {cont__339_19, NULL, 1178, 1178, 9, 57},
  {cont__339_20, NULL, 1179, 1179, 9, 33},
  {cont__339_21, NULL, 1181, 1181, 33, 67},
  {cont__339_22, NULL, 1181, 1181, 11, 67},
  {cont__339_23, NULL, 1182, 1182, 27, 44},
  {cont__339_24, NULL, 1182, 1182, 57, 78},
  {cont__339_25, NULL, 1182, 1182, 11, 79},
  {cont__339_26, NULL, },
  {cont__339_27, NULL, },
  {cont__339_28, NULL, },
  {cont__339_29, NULL, 1155, 1183, 1, 23},
  {cont__339_30, NULL, 1187, 1187, 5, 21},
  {cont__340_1, NULL, 1188, 1188, 5, 18},
  {cont__340_2, NULL, 1190, 1190, 5, 46},
  {cont__340_3, NULL, 1185, 1191, 1, 23},
  {cont__340_4, NULL, 1193, 1193, 1, 42},
  {cont__341_1, NULL, 1198, 1198, 5, 20},
  {cont__342_1, NULL, 1200, 1200, 5, 25},
  {cont__342_2, NULL, 1201, 1201, 28, 51},
  {cont__342_3, NULL, 1201, 1201, 28, 66},
  {cont__342_4, NULL, 1201, 1201, 23, 67},
  {cont__342_5, NULL, 1201, 1201, 5, 68},
  {cont__342_6, NULL, 1202, 1202, 5, 26},
  {cont__342_7, NULL, 1203, 1203, 5, 19},
  {cont__342_8, NULL, 1204, 1204, 5, 15},
  {cont__342_9, NULL, 1195, 1205, 1, 23},
  {cont__342_10, NULL, 1207, 1207, 37, 70},
  {cont__343_1, NULL, 1207, 1207, 1, 71},
  {cont__343_2, NULL, 1208, 1208, 44, 73},
  {cont__344_1, NULL, 1208, 1208, 1, 73},
  {cont__344_3, NULL, 1211, 1211, 10, 51},
  {cont__345_1, NULL, 1210, 1211, 1, 51},
  {cont__345_3, NULL, 1213, 1214, 1, 75},
  {cont__346_1, NULL, 1216, 1216, 1, 53},
  {cont__347_1, NULL, 1220, 1220, 11, 42},
  {cont__348_1, NULL, 1220, 1220, 5, 47},
  {cont__348_3, NULL, 1221, 1221, 10, 41},
  {cont__348_4, NULL, 1221, 1221, 5, 41},
  {cont__348_5, NULL, 1218, 1221, 1, 42},
  {cont__348_6, NULL, 1228, 1228, 21, 39},
  {cont__349_1, NULL, 1228, 1228, 9, 39},
  {cont__349_2, NULL, 1231, 1231, 22, 40},
  {cont__349_3, NULL, 1231, 1231, 9, 40},
  {cont__349_4, NULL, },
  {cont__349_5, NULL, },
  {cont__349_6, NULL, 1233, 1233, 17, 39},
  {cont__349_7, NULL, 1233, 1233, 5, 40},
  {cont__349_8, NULL, 1234, 1234, 5, 20},
  {cont__349_9, NULL, 1235, 1235, 5, 20},
  {cont__349_10, NULL, 1236, 1236, 5, 20},
  {cont__349_11, NULL, 1237, 1237, 5, 21},
  {cont__349_12, NULL, 1238, 1238, 5, 37},
  {cont__349_14, NULL, 1223, 1238, 1, 38},
  {cont__349_15, NULL, 1242, 1242, 10, 39},
  {cont__350_1, NULL, 1242, 1242, 5, 40},
  {cont__350_2, NULL, 1243, 1243, 5, 38},
  {cont__350_3, NULL, 1240, 1243, 1, 39},
  {cont__350_4, NULL, 1249, 1249, 18, 63},
  {cont__351_1, NULL, 1249, 1249, 9, 64},
  {cont__351_2, NULL, },
  {cont__351_26, NULL, },
  {cont__351_27, NULL, },
  {cont__351_28, NULL, 1245, 1277, 1, 23},
  {cont__351_29, NULL, 1282, 1282, 5, 41},
  {cont__352_1, NULL, 1290, 1290, 55, 79},
  {cont__352_2, NULL, 1290, 1290, 24, 79},
  {cont__352_3, NULL, 1290, 1290, 15, 80},
  {cont__352_4, NULL, },
  {cont__352_5, NULL, },
  {cont__352_6, NULL, },
  {cont__352_7, NULL, 1294, 1294, 16, 45},
  {cont__352_8, NULL, 1294, 1294, 11, 46},
  {cont__352_9, NULL, 1295, 1295, 20, 68},
  {cont__352_10, NULL, 1295, 1295, 11, 69},
  {cont__352_11, NULL, },
  {cont__352_12, NULL, },
  {cont__352_13, NULL, },
  {cont__352_14, NULL, 1279, 1295, 1, 73},
  {cont__352_15, NULL, 1300, 1300, 7, 26},
  {cont__353_1, NULL, 1302, 1302, 9, 50},
  {cont__353_2, NULL, 1303, 1303, 18, 37},
  {cont__353_3, NULL, 1303, 1303, 9, 38},
  {cont__353_4, NULL, },
  {cont__353_5, NULL, },
  {cont__353_6, NULL, 1297, 1303, 1, 41},
  {cont__353_7, NULL, 1306, 1306, 19, 31},
  {cont__354_1, NULL, 1306, 1306, 33, 67},
  {cont__354_2, NULL, 1305, 1306, 1, 76},
  {cont__354_3, NULL, 1311, 1311, 14, 56},
  {cont__355_1, NULL, 1311, 1311, 5, 57},
  {cont__355_2, NULL, 1308, 1311, 1, 58},
  {cont__355_3, NULL, 1386, 1386, 5, 24},
  {cont__360_1, NULL, 1388, 1388, 5, 35},
  {cont__360_2, NULL, 1391, 1391, 5, 37},
  {cont__360_4, NULL, },
  {cont__360_31, NULL, 1384, 1411, 1, 25},
  {cont__360_32, NULL, 1415, 1415, 5, 28},
  {cont__361_1, NULL, 1418, 1418, 5, 42},
  {cont__361_2, NULL, 1421, 1421, 5, 37},
  {cont__361_4, NULL, 1413, 1421, 1, 38},
  {cont__361_5, NULL, 1425, 1425, 5, 30},
  {cont__362_1, NULL, 1430, 1430, 5, 53},
  {cont__362_3, NULL, 1423, 1430, 1, 54},
  {cont__362_4, NULL, 1438, 1438, 5, 38},
  {cont__363_2, NULL, 1432, 1438, 1, 39},
  {cont__363_3, NULL, 1442, 1442, 17, 51},
  {cont__364_1, NULL, 1442, 1442, 5, 61},
  {cont__364_2, NULL, },
  {cont__364_18, NULL, 1440, 1456, 1, 83},
  {cont__364_19, NULL, 1461, 1461, 5, 24},
  {cont__365_1, NULL, 1461, 1461, 54, 63},
  {cont__365_3, NULL, 1461, 1461, 49, 64},
  {cont__365_4, NULL, 1461, 1461, 43, 64},
  {cont__365_5, NULL, 1461, 1461, 27, 65},
  {cont__365_6, NULL, 1461, 1461, 5, 65},
  {cont__365_7, NULL, 1458, 1461, 1, 66},
  {cont__365_8, NULL, 1463, 1463, 20, 39},
  {cont__366_1, NULL, 1463, 1463, 20, 54},
  {cont__366_2, NULL, 1463, 1463, 1, 55},
  {cont__366_3, NULL, 1468, 1468, 34, 73},
  {cont__367_1, NULL, 1468, 1468, 12, 73},
  {cont__367_2, NULL, 1468, 1468, 5, 74},
  {cont__367_3, NULL, 1465, 1468, 1, 75},
  {cont__367_5, NULL, 1471, 1471, 40, 74},
  {cont__368_1, NULL, 1471, 1471, 18, 74},
  {cont__368_2, NULL, 1471, 1471, 11, 75},
  {cont__368_3, NULL, 1470, 1471, 1, 75},
  {cont__368_5, NULL, 1473, 1473, 55, 75},
  {cont__369_1, NULL, 1473, 1473, 33, 75},
  {cont__369_2, NULL, 1473, 1473, 26, 76},
  {cont__369_3, NULL, 1473, 1473, 1, 76},
  {cont__369_5, NULL, 1479, 1479, 29, 75},
  {cont__370_1, NULL, 1479, 1479, 7, 75},
  {cont__370_2, NULL, },
  {cont__370_3, NULL, 1475, 1479, 1, 77},
  {cont__370_5, NULL, 1481, 1481, 55, 75},
  {cont__371_1, NULL, 1481, 1481, 33, 75},
  {cont__371_2, NULL, 1481, 1481, 26, 76},
  {cont__371_3, NULL, 1481, 1481, 1, 76},
  {cont__371_5, NULL, 1489, 1489, 32, 71},
  {cont__372_5, NULL, 1489, 1489, 9, 72},
  {cont__372_6, NULL, },
  {cont__372_7, NULL, },
  {cont__372_8, NULL, 1483, 1489, 1, 75},
  {cont__372_10, NULL, 1494, 1494, 34, 74},
  {cont__373_1, NULL, 1494, 1494, 12, 74},
  {cont__373_2, NULL, 1494, 1494, 5, 75},
  {cont__373_3, NULL, 1491, 1494, 1, 76},
  {cont__373_5, NULL, 1505, 1505, 5, 42},
  {cont__374_2, NULL, 1496, 1505, 1, 43},
  {cont__374_3, NULL, 1507, 1507, 35, 45},
  {cont__375_1, NULL, 1507, 1507, 1, 45},
  {cont__375_2, NULL, 1508, 1508, 1, 45},
  {cont__376_1, NULL, 1509, 1509, 1, 32},
  {cont__377_2, NULL, 1510, 1510, 50, 69},
  {cont__378_1, NULL, 1510, 1510, 37, 70},
  {cont__378_2, NULL, 1510, 1510, 22, 70},
  {cont__378_3, NULL, 1510, 1510, 1, 71},
  {cont__378_4, NULL, 1515, 1515, 28, 51},
  {cont__379_1, NULL, 1515, 1515, 28, 66},
  {cont__379_2, NULL, 1515, 1515, 23, 67},
  {cont__379_3, NULL, 1515, 1515, 5, 68},
  {cont__379_4, NULL, 1512, 1515, 1, 69},
  {cont__379_5, NULL, 1520, 1520, 5, 20},
  {cont__380_1, NULL, 1521, 1521, 5, 25},
  {cont__380_2, NULL, 1522, 1522, 31, 46},
  {cont__380_3, NULL, 1522, 1522, 22, 47},
  {cont__380_4, NULL, 1522, 1522, 9, 47},
  {cont__380_5, NULL, 1522, 1522, 5, 55},
  {cont__380_6, NULL, 1523, 1523, 5, 26},
  {cont__380_7, NULL, 1524, 1524, 5, 19},
  {cont__380_8, NULL, 1525, 1525, 5, 17},
  {cont__380_9, NULL, 1526, 1526, 5, 15},
  {cont__380_10, NULL, 1517, 1526, 1, 16},
  {cont__380_11, NULL, 1528, 1528, 41, 60},
  {cont__381_1, NULL, 1528, 1528, 34, 61},
  {cont__381_2, NULL, 1528, 1528, 1, 61},
  {cont__381_3, NULL, 1532, 1532, 26, 69},
  {cont__382_2, NULL, 1532, 1532, 5, 70},
  {cont__382_3, NULL, 1533, 1533, 12, 31},
  {cont__382_4, NULL, 1533, 1533, 5, 32},
  {cont__382_5, NULL, 1530, 1533, 1, 33},
  {cont__382_6, NULL, },
  {entry__compiler__std_identifier_1, NULL, 31, 31, 3, 50},
  {entry__print_message_13, NULL, 61, 61, 38, 63},
  {cont__print_message_14, &frame__print_message_13, 61, 61, 23, 75},
  {cont__print_message_15, &frame__print_message_13, 61, 61, 75, 75},
  {entry__print_message_21, NULL, 63, 63, 21, 29},
  {cont__print_message_22, &frame__print_message_21, 63, 63, 21, 35},
  {cont__print_message_23, &frame__print_message_21, 63, 63, 21, 35},
  {entry__print_message_25, NULL, 63, 63, 38, 43},
  {cont__print_message_26, &frame__print_message_25, 63, 63, 43, 43},
  {entry__print_message_19, NULL, 63, 63, 12, 16},
  {cont__print_message_20, &frame__print_message_19, 63, 63, 12, 35},
  {cont__print_message_24, &frame__print_message_19, 63, 63, 9, 43},
  {entry__print_message_30, NULL, 69, 69, 10, 40},
  {cont__print_message_31, &frame__print_message_30, 69, 69, 7, 40},
  {entry__print_message_32, NULL, 70, 70, 7, 13},
  {entry__print_message_40, NULL, 75, 75, 10, 19},
  {cont__print_message_41, &frame__print_message_40, 75, 75, 10, 19},
  {cont__print_message_42, &frame__print_message_40, 75, 75, 7, 25},
  {cont__print_message_43, &frame__print_message_40, 76, 76, 7, 12},
  {cont__print_message_44, &frame__print_message_40, 76, 76, 12, 12},
  {entry__print_message_39, NULL, 74, 76, 5, 12},
  {cont__print_message_45, &frame__print_message_39, 76, 76, 12, 12},
  {entry__print_message_50, NULL, 80, 80, 43, 45},
  {cont__print_message_51, &frame__print_message_50, 80, 80, 14, 59},
  {cont__print_message_55, &frame__print_message_50, 80, 80, 7, 59},
  {entry__print_message_56, NULL, 82, 84, 14, 80},
  {cont__print_message_62, &frame__print_message_56, 82, 84, 7, 80},
  {cont__print_message_63, &frame__print_message_56, 85, 85, 7, 19},
  {cont__print_message_64, &frame__print_message_56, 86, 86, 16, 25},
  {cont__print_message_66, &frame__print_message_56, 86, 86, 7, 29},
  {entry__print_message_1, NULL, 53, 53, 3, 40},
  {cont__print_message_2, &frame__print_message_1, 54, 54, 8, 24},
  {cont__print_message_3, &frame__print_message_1, 54, 54, 8, 31},
  {cont__print_message_4, &frame__print_message_1, 54, 54, 3, 33},
  {cont__print_message_5, &frame__print_message_1, 55, 55, 3, 32},
  {cont__print_message_6, &frame__print_message_1, 58, 58, 38, 42},
  {cont__print_message_7, &frame__print_message_1, 58, 58, 23, 43},
  {cont__print_message_8, &frame__print_message_1, 58, 58, 45, 70},
  {cont__print_message_9, &frame__print_message_1, 57, 58, 3, 71},
  {cont__print_message_10, &frame__print_message_1, 60, 60, 3, 27},
  {cont__print_message_11, &frame__print_message_1, 61, 61, 6, 20},
  {cont__print_message_12, &frame__print_message_1, 61, 61, 3, 75},
  {cont__print_message_16, &frame__print_message_1, 62, 62, 7, 23},
  {cont__print_message_17, &frame__print_message_1, 62, 62, 3, 30},
  {cont__print_message_18, &frame__print_message_1, 63, 63, 3, 43},
  {cont__print_message_27, &frame__print_message_1, 64, 64, 3, 35},
  {cont__print_message_28, &frame__print_message_1, 68, 68, 7, 21},
  {cont__print_message_29, &frame__print_message_1, 66, 70, 3, 14},
  {cont__print_message_33, &frame__print_message_1, 72, 72, 42, 59},
  {cont__print_message_34, &frame__print_message_1, 72, 72, 21, 59},
  {cont__print_message_35, &frame__print_message_1, 72, 72, 61, 79},
  {cont__print_message_37, &frame__print_message_1, 72, 72, 3, 80},
  {cont__print_message_38, &frame__print_message_1, 73, 76, 3, 13},
  {cont__print_message_46, &frame__print_message_1, 77, 77, 18, 23},
  {cont__print_message_47, &frame__print_message_1, 77, 77, 3, 23},
  {cont__print_message_48, &frame__print_message_1, 77, 77, 17, 23},
  {cont__print_message_49, &frame__print_message_1, 78, 86, 3, 30},
  {entry__compiler__Warning_1, NULL, 89, 89, 17, 32},
  {cont__compiler__Warning_2, &frame__compiler__Warning_1, 89, 89, 34, 56},
  {cont__compiler__Warning_3, &frame__compiler__Warning_1, 89, 89, 3, 70},
  {entry__ExitWithSyntaxError_1, NULL, 92, 92, 3, 50},
  {cont__ExitWithSyntaxError_3, &frame__ExitWithSyntaxError_1, 93, 93, 3, 8},
  {entry__compiler__SyntaxError_1, NULL, 96, 96, 23, 38},
  {cont__compiler__SyntaxError_2, &frame__compiler__SyntaxError_1, 96, 96, 40, 62},
  {cont__compiler__SyntaxError_3, &frame__compiler__SyntaxError_1, 96, 96, 3, 66},
  {entry__ParseError_1, NULL, 99, 99, 40, 56},
  {cont__ParseError_2, &frame__ParseError_1, 99, 99, 3, 60},
  {entry__types__syntax_error__grammar__match_1, NULL, 104, 104, 21, 36},
  {cont__types__syntax_error__grammar__match_2, &frame__types__syntax_error__grammar__match_1, 104, 104, 3, 36},
  {entry__syntax_error_1, NULL, 106, 106, 26, 68},
  {entry__types__unexpected_input_error__grammar__match_4, NULL, 116, 116, 34, 55},
  {cont__types__unexpected_input_error__grammar__match_5, &frame__types__unexpected_input_error__grammar__match_4, 116, 116, 34, 55},
  {entry__types__unexpected_input_error__grammar__match_8, NULL, 120, 120, 11, 46},
  {entry__types__unexpected_input_error__grammar__match_10, NULL, 122, 122, 11, 45},
  {entry__types__unexpected_input_error__grammar__match_12, NULL, 124, 124, 11, 46},
  {entry__types__unexpected_input_error__grammar__match_14, NULL, 126, 126, 11, 61},
  {entry__types__unexpected_input_error__grammar__match_20, NULL, 130, 130, 13, 51},
  {cont__types__unexpected_input_error__grammar__match_22, &frame__types__unexpected_input_error__grammar__match_20, 130, 130, 51, 51},
  {entry__types__unexpected_input_error__grammar__match_16, NULL, 128, 128, 11, 31},
  {cont__types__unexpected_input_error__grammar__match_17, &frame__types__unexpected_input_error__grammar__match_16, 129, 129, 18, 30},
  {cont__types__unexpected_input_error__grammar__match_18, &frame__types__unexpected_input_error__grammar__match_16, 129, 129, 18, 42},
  {cont__types__unexpected_input_error__grammar__match_19, &frame__types__unexpected_input_error__grammar__match_16, 129, 130, 11, 51},
  {cont__types__unexpected_input_error__grammar__match_23, &frame__types__unexpected_input_error__grammar__match_16, 131, 131, 29, 52},
  {cont__types__unexpected_input_error__grammar__match_25, &frame__types__unexpected_input_error__grammar__match_16, 131, 131, 11, 52},
  {entry__types__unexpected_input_error__grammar__match_7, NULL, 117, 131, 7, 53},
  {entry__types__unexpected_input_error__grammar__match_26, NULL, 133, 133, 7, 42},
  {entry__types__unexpected_input_error__grammar__match_1, NULL, 114, 114, 3, 34},
  {cont__types__unexpected_input_error__grammar__match_2, &frame__types__unexpected_input_error__grammar__match_1, 116, 116, 5, 29},
  {cont__types__unexpected_input_error__grammar__match_3, &frame__types__unexpected_input_error__grammar__match_1, 116, 116, 5, 55},
  {cont__types__unexpected_input_error__grammar__match_6, &frame__types__unexpected_input_error__grammar__match_1, 115, 133, 3, 43},
  {entry__unexpected_input_error_1, NULL, 136, 136, 3, 61},
  {entry__dump_stream__grammar__match_1, NULL, 155, 155, 3, 23},
  {cont__dump_stream__grammar__match_3, &frame__dump_stream__grammar__match_1, 156, 156, 17, 48},
  {cont__dump_stream__grammar__match_4, &frame__dump_stream__grammar__match_1, 156, 156, 3, 48},
  {cont__dump_stream__grammar__match_5, &frame__dump_stream__grammar__match_1, 157, 157, 3, 23},
  {cont__dump_stream__grammar__match_7, &frame__dump_stream__grammar__match_1, 158, 158, 3, 6},
  {entry__compiler__strip_4, NULL, 171, 171, 42, 56},
  {cont__compiler__strip_5, &frame__compiler__strip_4, 171, 171, 35, 56},
  {cont__compiler__strip_6, &frame__compiler__strip_4, 171, 171, 56, 56},
  {entry__compiler__strip_10, NULL, 172, 172, 44, 60},
  {cont__compiler__strip_11, &frame__compiler__strip_10, 172, 172, 37, 60},
  {cont__compiler__strip_12, &frame__compiler__strip_10, 172, 172, 60, 60},
  {entry__compiler__strip_18, NULL, 174, 174, 51, 66},
  {cont__compiler__strip_19, &frame__compiler__strip_18, 174, 174, 66, 66},
  {entry__compiler__strip_16, NULL, 174, 174, 18, 35},
  {cont__compiler__strip_17, &frame__compiler__strip_16, 174, 174, 5, 66},
  {cont__compiler__strip_20, &frame__compiler__strip_16, 174, 174, 66, 66},
  {entry__compiler__strip_26, NULL, 176, 176, 51, 66},
  {cont__compiler__strip_27, &frame__compiler__strip_26, 176, 176, 66, 66},
  {entry__compiler__strip_24, NULL, 176, 176, 18, 35},
  {cont__compiler__strip_25, &frame__compiler__strip_24, 176, 176, 5, 66},
  {cont__compiler__strip_28, &frame__compiler__strip_24, 176, 176, 66, 66},
  {entry__compiler__strip_34, NULL, 178, 178, 49, 63},
  {cont__compiler__strip_35, &frame__compiler__strip_34, 178, 178, 63, 63},
  {entry__compiler__strip_32, NULL, 178, 178, 18, 34},
  {cont__compiler__strip_33, &frame__compiler__strip_32, 178, 178, 5, 63},
  {cont__compiler__strip_36, &frame__compiler__strip_32, 178, 178, 63, 63},
  {entry__compiler__strip_40, NULL, 179, 179, 41, 54},
  {cont__compiler__strip_41, &frame__compiler__strip_40, 179, 179, 34, 54},
  {cont__compiler__strip_42, &frame__compiler__strip_40, 179, 179, 54, 54},
  {entry__compiler__strip_46, NULL, 180, 180, 45, 62},
  {cont__compiler__strip_47, &frame__compiler__strip_46, 180, 180, 38, 62},
  {cont__compiler__strip_48, &frame__compiler__strip_46, 180, 180, 62, 62},
  {entry__compiler__strip_1, NULL, 171, 171, 6, 21},
  {cont__compiler__strip_2, &frame__compiler__strip_1, 171, 171, 6, 32},
  {cont__compiler__strip_3, &frame__compiler__strip_1, 171, 171, 3, 56},
  {cont__compiler__strip_7, &frame__compiler__strip_1, 172, 172, 6, 23},
  {cont__compiler__strip_8, &frame__compiler__strip_1, 172, 172, 6, 34},
  {cont__compiler__strip_9, &frame__compiler__strip_1, 172, 172, 3, 60},
  {cont__compiler__strip_13, &frame__compiler__strip_1, 173, 173, 6, 24},
  {cont__compiler__strip_14, &frame__compiler__strip_1, 173, 173, 6, 35},
  {cont__compiler__strip_15, &frame__compiler__strip_1, 173, 174, 3, 66},
  {cont__compiler__strip_21, &frame__compiler__strip_1, 175, 175, 6, 24},
  {cont__compiler__strip_22, &frame__compiler__strip_1, 175, 175, 6, 35},
  {cont__compiler__strip_23, &frame__compiler__strip_1, 175, 176, 3, 66},
  {cont__compiler__strip_29, &frame__compiler__strip_1, 177, 177, 6, 23},
  {cont__compiler__strip_30, &frame__compiler__strip_1, 177, 177, 6, 34},
  {cont__compiler__strip_31, &frame__compiler__strip_1, 177, 178, 3, 63},
  {cont__compiler__strip_37, &frame__compiler__strip_1, 179, 179, 6, 20},
  {cont__compiler__strip_38, &frame__compiler__strip_1, 179, 179, 6, 31},
  {cont__compiler__strip_39, &frame__compiler__strip_1, 179, 179, 3, 54},
  {cont__compiler__strip_43, &frame__compiler__strip_1, 180, 180, 6, 24},
  {cont__compiler__strip_44, &frame__compiler__strip_1, 180, 180, 6, 35},
  {cont__compiler__strip_45, &frame__compiler__strip_1, 180, 180, 3, 62},
  {cont__compiler__strip_49, &frame__compiler__strip_1, },
  {entry__dump__grammar__match_1, NULL, 185, 185, 10, 37},
  {cont__dump__grammar__match_2, &frame__dump__grammar__match_1, 185, 185, 3, 37},
  {cont__dump__grammar__match_4, &frame__dump__grammar__match_1, 186, 186, 3, 6},
  {entry__dump3__grammar__match_1, NULL, 191, 191, 12, 39},
  {cont__dump3__grammar__match_2, &frame__dump3__grammar__match_1, 191, 191, 3, 39},
  {cont__dump3__grammar__match_3, &frame__dump3__grammar__match_1, 192, 192, 3, 6},
  {entry__dump5__grammar__match_1, NULL, 197, 197, 12, 39},
  {cont__dump5__grammar__match_2, &frame__dump5__grammar__match_1, 197, 197, 3, 39},
  {cont__dump5__grammar__match_3, &frame__dump5__grammar__match_1, 198, 198, 3, 6},
  {entry__compiler__precedence_3, NULL, 231, 231, 25, 44},
  {cont__compiler__precedence_4, &frame__compiler__precedence_3, 231, 231, 22, 44},
  {entry__compiler__precedence_5, NULL, 231, 231, 47, 65},
  {entry__compiler__precedence_1, NULL, 231, 231, 6, 19},
  {cont__compiler__precedence_2, &frame__compiler__precedence_1, 231, 231, 3, 65},
  {entry__compiler__is_left_associative_1, NULL, 233, 233, 43, 50},
  {cont__compiler__is_left_associative_2, &frame__compiler__is_left_associative_1, 233, 233, 40, 50},
  {entry__is_right_associative_1, NULL, 235, 235, 34, 42},
  {cont__is_right_associative_2, &frame__is_right_associative_1, 235, 235, 34, 42},
  {cont__is_right_associative_3, &frame__is_right_associative_1, 235, 235, 31, 42},
  {entry__infix_operator_1, NULL, 238, 238, 19, 70},
  {cont__infix_operator_2, &frame__infix_operator_1, 238, 238, 6, 71},
  {cont__infix_operator_3, &frame__infix_operator_1, 238, 238, 3, 71},
  {entry__interleaved_1, NULL, 240, 240, 58, 78},
  {cont__interleaved_2, &frame__interleaved_1, 240, 240, 53, 79},
  {cont__interleaved_3, &frame__interleaved_1, 240, 240, 41, 79},
  {cont__interleaved_4, &frame__interleaved_1, 240, 240, 38, 79},
  {entry__types__store_arguments_index__grammar__match_1, NULL, 249, 249, 30, 64},
  {cont__types__store_arguments_index__grammar__match_2, &frame__types__store_arguments_index__grammar__match_1, 249, 249, 3, 65},
  {cont__types__store_arguments_index__grammar__match_3, &frame__types__store_arguments_index__grammar__match_1, 250, 250, 18, 36},
  {cont__types__store_arguments_index__grammar__match_4, &frame__types__store_arguments_index__grammar__match_1, 250, 250, 3, 43},
  {cont__types__store_arguments_index__grammar__match_5, &frame__types__store_arguments_index__grammar__match_1, 250, 250, 43, 43},
  {entry__store_arguments_index_1, NULL, 253, 253, 3, 60},
  {entry__types__inline__grammar__match_1, NULL, 263, 263, 18, 36},
  {cont__types__inline__grammar__match_2, &frame__types__inline__grammar__match_1, 263, 263, 3, 43},
  {cont__types__inline__grammar__match_3, &frame__types__inline__grammar__match_1, 263, 263, 43, 43},
  {entry__inline_1, NULL, 265, 265, 23, 65},
  {entry__expect_3, NULL, 283, 283, 36, 60},
  {cont__expect_4, &frame__expect_3, 283, 283, 23, 61},
  {cont__expect_5, &frame__expect_3, 283, 283, 8, 62},
  {cont__expect_6, &frame__expect_3, 283, 283, 5, 62},
  {entry__expect_7, NULL, 284, 284, 23, 56},
  {cont__expect_8, &frame__expect_7, 284, 284, 8, 57},
  {cont__expect_9, &frame__expect_7, 284, 284, 5, 57},
  {entry__expect_1, NULL, 282, 282, 5, 26},
  {cont__expect_2, &frame__expect_1, 281, 284, 3, 57},
  {entry__compiler__arguments_span_1, NULL, 286, 286, 44, 78},
  {cont__compiler__arguments_span_2, &frame__compiler__arguments_span_1, 286, 286, 41, 78},
  {entry__check_functor_5, NULL, 1319, 1319, 41, 68},
  {cont__check_functor_6, &frame__check_functor_5, 1319, 1319, 37, 69},
  {cont__check_functor_7, &frame__check_functor_5, 1319, 1319, 37, 69},
  {entry__check_functor_3, NULL, 1319, 1319, 7, 32},
  {cont__check_functor_4, &frame__check_functor_3, 1319, 1319, 7, 69},
  {cont__check_functor_8, &frame__check_functor_3, 1319, 1319, 7, 69},
  {entry__check_functor_10, NULL, 1321, 1321, 7, 43},
  {entry__check_functor_1, NULL, 1318, 1318, 7, 30},
  {cont__check_functor_2, &frame__check_functor_1, 1317, 1319, 5, 69},
  {cont__check_functor_9, &frame__check_functor_1, 1316, 1321, 3, 44},
  {entry__check_arguments_4, NULL, 1330, 1330, 35, 46},
  {cont__check_arguments_5, &frame__check_arguments_4, 1330, 1330, 46, 46},
  {entry__check_arguments_9, NULL, 1331, 1331, 42, 77},
  {cont__check_arguments_10, &frame__check_arguments_9, 1331, 1331, 42, 77},
  {entry__check_arguments_15, NULL, 1335, 1335, 13, 66},
  {entry__check_arguments_14, NULL, 1334, 1335, 11, 66},
  {cont__check_arguments_17, &frame__check_arguments_14, 1336, 1336, 45, 45},
  {entry__check_arguments_19, NULL, 1339, 1339, 13, 78},
  {entry__check_arguments_18, NULL, 1338, 1339, 11, 78},
  {cont__check_arguments_21, &frame__check_arguments_18, 1340, 1340, 46, 46},
  {entry__check_arguments_12, NULL, 1333, 1333, 9, 43},
  {cont__check_arguments_13, &frame__check_arguments_12, 1332, 1340, 7, 47},
  {cont__check_arguments_22, &frame__check_arguments_12, 1341, 1341, 7, 17},
  {cont__check_arguments_23, &frame__check_arguments_12, 1341, 1341, 17, 17},
  {entry__check_arguments_2, NULL, 1330, 1330, 8, 32},
  {cont__check_arguments_3, &frame__check_arguments_2, 1330, 1330, 5, 46},
  {cont__check_arguments_6, &frame__check_arguments_2, 1331, 1331, 12, 36},
  {cont__check_arguments_7, &frame__check_arguments_2, 1331, 1331, 8, 37},
  {cont__check_arguments_8, &frame__check_arguments_2, 1331, 1331, 8, 77},
  {cont__check_arguments_11, &frame__check_arguments_2, 1331, 1341, 5, 17},
  {entry__check_arguments_29, NULL, 1347, 1347, 54, 76},
  {cont__check_arguments_30, &frame__check_arguments_29, 1347, 1347, 11, 77},
  {cont__check_arguments_31, &frame__check_arguments_29, 1348, 1348, 24, 46},
  {cont__check_arguments_32, &frame__check_arguments_29, 1348, 1348, 11, 46},
  {entry__check_arguments_33, NULL, 1350, 1350, 11, 31},
  {entry__check_arguments_27, NULL, 1346, 1346, 9, 43},
  {cont__check_arguments_28, &frame__check_arguments_27, 1345, 1350, 7, 32},
  {entry__check_arguments_25, NULL, 1344, 1344, 12, 31},
  {cont__check_arguments_26, &frame__check_arguments_25, 1344, 1350, 5, 33},
  {entry__check_arguments_38, NULL, 1353, 1353, 24, 62},
  {cont__check_arguments_40, &frame__check_arguments_38, 1353, 1353, 7, 62},
  {entry__check_arguments_43, NULL, 1355, 1355, 24, 61},
  {cont__check_arguments_45, &frame__check_arguments_43, 1355, 1355, 7, 61},
  {entry__check_arguments_36, NULL, 1352, 1352, 8, 31},
  {cont__check_arguments_37, &frame__check_arguments_36, 1352, 1353, 5, 62},
  {cont__check_arguments_41, &frame__check_arguments_36, 1354, 1354, 8, 31},
  {cont__check_arguments_42, &frame__check_arguments_36, 1354, 1355, 5, 61},
  {entry__check_arguments_50, NULL, 1361, 1361, 9, 24},
  {entry__check_arguments_51, NULL, 1360, 1360, 9, 12},
  {entry__check_arguments_54, NULL, 1367, 1367, 9, 24},
  {entry__check_arguments_55, NULL, 1366, 1366, 9, 20},
  {entry__check_arguments_58, NULL, 1369, 1369, 33, 51},
  {cont__check_arguments_59, &frame__check_arguments_58, 1369, 1369, 33, 51},
  {entry__check_arguments_66, NULL, 1375, 1375, 13, 17},
  {entry__check_arguments_64, NULL, 1373, 1373, 18, 42},
  {cont__check_arguments_65, &frame__check_arguments_64, 1373, 1375, 11, 17},
  {entry__check_arguments_62, NULL, 1372, 1372, 18, 35},
  {cont__check_arguments_63, &frame__check_arguments_62, 1372, 1375, 9, 18},
  {cont__check_arguments_67, &frame__check_arguments_62, 1375, 1375, 18, 18},
  {entry__check_arguments_70, NULL, 1377, 1377, 26, 63},
  {cont__check_arguments_72, &frame__check_arguments_70, 1377, 1377, 9, 63},
  {entry__check_arguments_61, NULL, 1371, 1375, 7, 19},
  {cont__check_arguments_68, &frame__check_arguments_61, 1376, 1376, 14, 60},
  {cont__check_arguments_69, &frame__check_arguments_61, 1376, 1377, 7, 63},
  {entry__check_arguments_75, NULL, 1378, 1378, 33, 51},
  {cont__check_arguments_76, &frame__check_arguments_75, 1378, 1378, 33, 51},
  {entry__check_arguments_78, NULL, 1379, 1379, 24, 60},
  {cont__check_arguments_80, &frame__check_arguments_78, 1379, 1379, 7, 60},
  {entry__check_arguments_48, NULL, 1359, 1359, 9, 36},
  {cont__check_arguments_49, &frame__check_arguments_48, 1357, 1361, 5, 25},
  {cont__check_arguments_52, &frame__check_arguments_48, 1365, 1365, 9, 36},
  {cont__check_arguments_53, &frame__check_arguments_48, 1363, 1367, 5, 25},
  {cont__check_arguments_56, &frame__check_arguments_48, 1369, 1369, 8, 28},
  {cont__check_arguments_57, &frame__check_arguments_48, 1369, 1369, 8, 51},
  {cont__check_arguments_60, &frame__check_arguments_48, 1369, 1377, 5, 64},
  {cont__check_arguments_73, &frame__check_arguments_48, 1378, 1378, 8, 28},
  {cont__check_arguments_74, &frame__check_arguments_48, 1378, 1378, 8, 51},
  {cont__check_arguments_77, &frame__check_arguments_48, 1378, 1379, 5, 60},
  {entry__check_arguments_1, NULL, 1343, 1343, 12, 29},
  {cont__check_arguments_24, &frame__check_arguments_1, 1343, 1350, 3, 34},
  {cont__check_arguments_34, &frame__check_arguments_1, 1351, 1351, 6, 30},
  {cont__check_arguments_35, &frame__check_arguments_1, 1351, 1355, 3, 62},
  {cont__check_arguments_46, &frame__check_arguments_1, 1356, 1356, 6, 29},
  {cont__check_arguments_47, &frame__check_arguments_1, 1356, 1379, 3, 61},
  {entry__CHECK_ARGUMENTS_2, NULL, 1382, 1382, 24, 77},
  {entry__CHECK_ARGUMENTS_1, NULL, 1382, 1382, 3, 77},
  {entry__compiler__parse_meta_instruction_7, NULL, 1544, 1544, 32, 75},
  {entry__compiler__parse_meta_instruction_1, NULL, 1542, 1542, 3, 39},
  {cont__compiler__parse_meta_instruction_2, &frame__compiler__parse_meta_instruction_1, 1543, 1543, 3, 38},
  {cont__compiler__parse_meta_instruction_3, &frame__compiler__parse_meta_instruction_1, 1544, 1544, 13, 29},
  {cont__compiler__parse_meta_instruction_4, &frame__compiler__parse_meta_instruction_1, 1544, 1544, 6, 29},
  {cont__compiler__parse_meta_instruction_5, &frame__compiler__parse_meta_instruction_1, 1544, 1544, 6, 29},
  {cont__compiler__parse_meta_instruction_6, &frame__compiler__parse_meta_instruction_1, 1544, 1544, 3, 75},
  {cont__compiler__parse_meta_instruction_9, &frame__compiler__parse_meta_instruction_1, 1545, 1545, 3, 8},
  {entry__compiler__parse_statement_9, NULL, 1556, 1556, 9, 67},
  {entry__compiler__parse_statement_5, NULL, 1555, 1555, 17, 33},
  {cont__compiler__parse_statement_6, &frame__compiler__parse_statement_5, 1555, 1555, 10, 33},
  {cont__compiler__parse_statement_7, &frame__compiler__parse_statement_5, 1555, 1555, 10, 33},
  {cont__compiler__parse_statement_8, &frame__compiler__parse_statement_5, 1555, 1556, 7, 67},
  {entry__compiler__parse_statement_11, NULL, 1558, 1558, 7, 57},
  {cont__compiler__parse_statement_13, &frame__compiler__parse_statement_11, 1559, 1559, 7, 26},
  {cont__compiler__parse_statement_14, &frame__compiler__parse_statement_11, 1560, 1560, 7, 25},
  {cont__compiler__parse_statement_16, &frame__compiler__parse_statement_11, 1561, 1561, 7, 12},
  {entry__compiler__parse_statement_1, NULL, 1551, 1551, 3, 39},
  {cont__compiler__parse_statement_2, &frame__compiler__parse_statement_1, 1552, 1552, 3, 33},
  {cont__compiler__parse_statement_3, &frame__compiler__parse_statement_1, 1554, 1554, 5, 18},
  {cont__compiler__parse_statement_4, &frame__compiler__parse_statement_1, 1553, 1561, 3, 13},
  {cont__compiler__parse_statement_17, &frame__compiler__parse_statement_1, 1562, 1562, 3, 8},
  {entry__230_2, NULL, 271, 272, 9, 23},
  {entry__230_1, NULL, 270, 272, 7, 24},
  {cont__230_4, &frame__230_1, 273, 273, 7, 13},
  {entry__240_1, NULL, 299, 299, 7, 48},
  {cont__240_2, &frame__240_1, 300, 300, 40, 40},
  {entry__241_1, NULL, 309, 309, 32, 48},
  {cont__241_2, &frame__241_1, 309, 309, 7, 50},
  {cont__241_3, &frame__241_1, 310, 310, 40, 40},
  {entry__242_1, NULL, 319, 319, 7, 45},
  {cont__242_2, &frame__242_1, 319, 319, 45, 45},
  {entry__243_3, NULL, 331, 331, 13, 43},
  {cont__243_4, &frame__243_3, 331, 331, 43, 43},
  {entry__244_6, NULL, 347, 347, 15, 76},
  {entry__244_4, NULL, 346, 346, 16, 31},
  {cont__244_5, &frame__244_4, 346, 347, 13, 76},
  {cont__244_8, &frame__244_4, 348, 348, 13, 43},
  {cont__244_9, &frame__244_4, 348, 348, 43, 43},
  {entry__247_7, NULL, 378, 379, 29, 55},
  {cont__247_10, &frame__247_7, 378, 379, 11, 55},
  {entry__247_3, NULL, 376, 376, 9, 41},
  {cont__247_4, &frame__247_3, 377, 377, 12, 37},
  {cont__247_5, &frame__247_3, 377, 377, 12, 48},
  {cont__247_6, &frame__247_3, 377, 379, 9, 56},
  {cont__247_11, &frame__247_3, 380, 380, 9, 35},
  {cont__247_12, &frame__247_3, 380, 380, 40, 40},
  {entry__248_4, NULL, 393, 393, 13, 54},
  {cont__248_5, &frame__248_4, 393, 393, 54, 54},
  {entry__248_17, NULL, 403, 404, 33, 64},
  {cont__248_20, &frame__248_17, 403, 404, 15, 64},
  {entry__248_14, NULL, 402, 402, 16, 40},
  {cont__248_15, &frame__248_14, 402, 402, 16, 51},
  {cont__248_16, &frame__248_14, 402, 404, 13, 65},
  {cont__248_21, &frame__248_14, 405, 405, 13, 38},
  {cont__248_22, &frame__248_14, 405, 405, 48, 48},
  {entry__248_25, NULL, 408, 409, 33, 62},
  {cont__248_27, &frame__248_25, 408, 409, 15, 62},
  {entry__248_23, NULL, 407, 407, 16, 44},
  {cont__248_24, &frame__248_23, 407, 409, 13, 63},
  {cont__248_28, &frame__248_23, 410, 410, 13, 42},
  {cont__248_29, &frame__248_23, 410, 410, 47, 47},
  {entry__248_10, NULL, 398, 398, 9, 37},
  {cont__248_11, &frame__248_10, 399, 399, 9, 39},
  {cont__248_12, &frame__248_10, 401, 401, 11, 26},
  {cont__248_13, &frame__248_10, 400, 410, 9, 48},
  {entry__249_6, NULL, 423, 424, 29, 55},
  {cont__249_8, &frame__249_6, 423, 424, 11, 55},
  {entry__249_3, NULL, 421, 421, 9, 37},
  {cont__249_4, &frame__249_3, 422, 422, 12, 37},
  {cont__249_5, &frame__249_3, 422, 424, 9, 56},
  {cont__249_9, &frame__249_3, 425, 425, 9, 35},
  {cont__249_10, &frame__249_3, 425, 425, 40, 40},
  {entry__252_6, NULL, 441, 442, 29, 53},
  {cont__252_9, &frame__252_6, 441, 442, 11, 53},
  {entry__252_3, NULL, 439, 439, 9, 41},
  {cont__252_4, &frame__252_3, 440, 440, 12, 35},
  {cont__252_5, &frame__252_3, 440, 442, 9, 54},
  {cont__252_10, &frame__252_3, 443, 443, 9, 33},
  {cont__252_11, &frame__252_3, 443, 443, 38, 38},
  {entry__253_6, NULL, 456, 457, 29, 54},
  {cont__253_9, &frame__253_6, 456, 457, 11, 54},
  {entry__253_3, NULL, 454, 454, 9, 41},
  {cont__253_4, &frame__253_3, 455, 455, 12, 37},
  {cont__253_5, &frame__253_3, 455, 457, 9, 55},
  {cont__253_10, &frame__253_3, 458, 458, 9, 35},
  {cont__253_11, &frame__253_3, 458, 458, 40, 40},
  {entry__256_6, NULL, 474, 475, 29, 63},
  {cont__256_8, &frame__256_6, 474, 475, 11, 63},
  {entry__256_3, NULL, 472, 472, 9, 41},
  {cont__256_4, &frame__256_3, 473, 473, 12, 35},
  {cont__256_5, &frame__256_3, 473, 475, 9, 64},
  {cont__256_9, &frame__256_3, 476, 476, 9, 33},
  {cont__256_10, &frame__256_3, 476, 476, 38, 38},
  {entry__264_2, NULL, 520, 520, 33, 56},
  {entry__264_4, NULL, 521, 521, 16, 32},
  {cont__264_5, &frame__264_4, 521, 521, 37, 37},
  {cont__264_6, &frame__264_4, 521, 521, 9, 37},
  {cont__264_7, &frame__264_4, 521, 521, 37, 37},
  {entry__264_1, NULL, 520, 520, 14, 56},
  {cont__264_3, &frame__264_1, 520, 521, 7, 37},
  {cont__264_8, &frame__264_1, },
  {entry__267_1, NULL, 546, 546, 26, 42},
  {cont__267_2, &frame__267_1, 547, 547, 33, 56},
  {cont__267_3, &frame__267_1, 543, 547, 9, 57},
  {entry__268_1, NULL, 558, 558, 25, 34},
  {cont__268_2, &frame__268_1, 560, 560, 24, 40},
  {cont__268_3, &frame__268_1, 561, 561, 31, 54},
  {cont__268_4, &frame__268_1, 561, 561, 56, 56},
  {entry__283_2, NULL, 611, 611, 30, 49},
  {cont__283_3, &frame__283_2, 611, 611, 9, 52},
  {cont__283_4, &frame__283_2, 611, 611, 52, 52},
  {entry__284_1, NULL, 618, 618, 33, 33},
  {entry__285_6, NULL, 631, 631, 32, 73},
  {entry__285_2, NULL, 630, 630, 30, 49},
  {cont__285_3, &frame__285_2, 630, 630, 9, 50},
  {cont__285_4, &frame__285_2, 631, 631, 16, 29},
  {cont__285_5, &frame__285_2, 631, 631, 9, 73},
  {cont__285_8, &frame__285_2, 632, 632, 32, 32},
  {entry__286_10, NULL, 647, 647, 37, 56},
  {cont__286_11, &frame__286_10, 647, 647, 37, 67},
  {cont__286_12, &frame__286_10, 647, 647, 27, 68},
  {cont__286_13, &frame__286_10, 648, 648, 39, 39},
  {entry__290_1, NULL, 675, 675, 17, 34},
  {cont__290_2, &frame__290_1, 675, 675, 36, 55},
  {cont__290_3, &frame__290_1, 675, 675, 11, 55},
  {cont__290_4, &frame__290_1, 675, 675, 55, 55},
  {entry__291_5, NULL, 683, 683, 17, 33},
  {cont__291_6, &frame__291_5, 683, 683, 11, 63},
  {cont__291_7, &frame__291_5, 683, 683, 63, 63},
  {entry__291_1, NULL, 682, 682, 12, 30},
  {cont__291_2, &frame__291_1, 682, 682, 12, 36},
  {cont__291_3, &frame__291_1, 682, 682, 12, 36},
  {cont__291_4, &frame__291_1, 682, 683, 9, 63},
  {cont__291_8, &frame__291_1, 684, 684, 30, 30},
  {entry__292_9, NULL, 693, 693, 17, 33},
  {cont__292_10, &frame__292_9, 693, 693, 11, 63},
  {cont__292_11, &frame__292_9, 693, 693, 63, 63},
  {entry__292_5, NULL, 692, 692, 12, 30},
  {cont__292_6, &frame__292_5, 692, 692, 12, 36},
  {cont__292_7, &frame__292_5, 692, 692, 12, 36},
  {cont__292_8, &frame__292_5, 692, 693, 9, 63},
  {cont__292_12, &frame__292_5, 696, 696, 25, 48},
  {cont__292_14, &frame__292_5, 697, 697, 27, 44},
  {cont__292_15, &frame__292_5, 699, 699, 26, 42},
  {cont__292_16, &frame__292_5, 700, 700, 33, 56},
  {cont__292_17, &frame__292_5, 701, 701, 30, 50},
  {cont__292_18, &frame__292_5, 701, 701, 52, 52},
  {entry__292_1, NULL, 691, 691, 20, 37},
  {cont__292_2, &frame__292_1, 691, 691, 10, 38},
  {cont__292_3, &frame__292_1, 691, 691, 10, 42},
  {cont__292_4, &frame__292_1, 691, 701, 7, 52},
  {cont__292_19, &frame__292_1, },
  {entry__295_1, NULL, 725, 725, 15, 32},
  {cont__295_2, &frame__295_1, 725, 725, 34, 60},
  {cont__295_3, &frame__295_1, 725, 725, 7, 60},
  {cont__295_4, &frame__295_1, 725, 725, 60, 60},
  {entry__299_1, NULL, 755, 755, 25, 56},
  {cont__299_3, &frame__299_1, 756, 756, 37, 58},
  {cont__299_5, &frame__299_1, 756, 756, 27, 59},
  {cont__299_6, &frame__299_1, 757, 757, 26, 42},
  {cont__299_7, &frame__299_1, 758, 758, 33, 56},
  {cont__299_8, &frame__299_1, 758, 758, 33, 58},
  {cont__299_9, &frame__299_1, 753, 758, 9, 59},
  {entry__300_1, NULL, 771, 771, 27, 36},
  {cont__300_2, &frame__300_1, 772, 772, 26, 42},
  {cont__300_3, &frame__300_1, 773, 773, 33, 56},
  {cont__300_4, &frame__300_1, 768, 773, 9, 57},
  {entry__307_9, NULL, 833, 833, 13, 51},
  {cont__307_10, &frame__307_9, 833, 833, 13, 51},
  {entry__307_12, NULL, 835, 835, 58, 58},
  {entry__307_2, NULL, 828, 828, 61, 61},
  {cont__307_3, &frame__307_2, 828, 828, 41, 58},
  {cont__307_4, &frame__307_2, 828, 828, 41, 62},
  {cont__307_5, &frame__307_2, 828, 828, 9, 63},
  {cont__307_6, &frame__307_2, 829, 829, 9, 53},
  {cont__307_7, &frame__307_2, 832, 832, 13, 42},
  {cont__307_8, &frame__307_2, 831, 833, 11, 51},
  {cont__307_11, &frame__307_2, 830, 835, 9, 59},
  {cont__307_13, &frame__307_2, },
  {entry__308_6, NULL, 845, 845, 11, 28},
  {cont__308_7, &frame__308_6, 845, 845, 28, 28},
  {entry__308_11, NULL, 855, 855, 20, 44},
  {cont__308_12, &frame__308_11, 855, 855, 17, 44},
  {entry__308_13, NULL, 856, 856, 17, 20},
  {entry__308_22, NULL, 863, 863, 41, 66},
  {cont__308_23, &frame__308_22, 863, 863, 41, 66},
  {entry__308_27, NULL, 868, 868, 21, 57},
  {entry__308_28, NULL, 869, 869, 21, 31},
  {entry__308_16, NULL, 860, 860, 17, 46},
  {cont__308_17, &frame__308_16, 861, 861, 17, 42},
  {cont__308_18, &frame__308_16, 862, 862, 20, 35},
  {cont__308_19, &frame__308_16, 862, 862, 17, 41},
  {cont__308_20, &frame__308_16, 863, 863, 20, 36},
  {cont__308_21, &frame__308_16, 863, 863, 20, 66},
  {cont__308_24, &frame__308_16, 863, 863, 17, 72},
  {cont__308_25, &frame__308_16, 867, 867, 21, 40},
  {cont__308_26, &frame__308_16, 865, 869, 17, 32},
  {cont__308_29, &frame__308_16, 871, 871, 17, 41},
  {cont__308_30, &frame__308_16, 875, 875, 35, 50},
  {cont__308_31, &frame__308_16, 877, 877, 34, 50},
  {cont__308_32, &frame__308_16, 878, 878, 41, 64},
  {cont__308_33, &frame__308_16, 879, 879, 38, 59},
  {cont__308_34, &frame__308_16, 880, 880, 17, 43},
  {cont__308_35, &frame__308_16, 881, 881, 20, 44},
  {cont__308_36, &frame__308_16, 881, 881, 20, 49},
  {cont__308_37, &frame__308_16, 881, 881, 17, 55},
  {entry__308_15, NULL, 859, 881, 15, 55},
  {cont__308_38, &frame__308_15, 881, 881, 55, 55},
  {entry__308_9, NULL, 854, 854, 17, 40},
  {cont__308_10, &frame__308_9, 852, 856, 13, 21},
  {cont__308_14, &frame__308_9, 858, 881, 13, 56},
  {cont__308_39, &frame__308_9, 882, 882, 13, 37},
  {cont__308_40, &frame__308_9, 883, 883, 13, 46},
  {cont__308_41, &frame__308_9, 883, 883, 46, 46},
  {entry__308_50, NULL, 890, 890, 20, 31},
  {cont__308_51, &frame__308_50, 890, 890, 17, 31},
  {entry__308_52, NULL, 891, 891, 17, 28},
  {entry__308_47, NULL, 887, 887, 15, 26},
  {cont__308_48, &frame__308_47, 889, 889, 17, 21},
  {cont__308_49, &frame__308_47, 890, 890, 17, 31},
  {cont__308_53, &frame__308_47, 886, 891, 13, 29},
  {entry__308_8, NULL, 847, 847, 11, 39},
  {cont__308_42, &frame__308_8, 848, 848, 32, 43},
  {cont__308_43, &frame__308_8, 848, 848, 11, 44},
  {cont__308_44, &frame__308_8, 849, 849, 33, 44},
  {cont__308_45, &frame__308_8, 849, 849, 11, 45},
  {cont__308_46, &frame__308_8, 885, 891, 11, 30},
  {cont__308_54, &frame__308_8, 892, 892, 11, 35},
  {cont__308_55, &frame__308_8, 892, 892, 35, 35},
  {entry__308_58, NULL, 894, 894, 41, 60},
  {cont__308_59, &frame__308_58, 894, 894, 36, 66},
  {cont__308_60, &frame__308_58, 894, 894, 67, 67},
  {entry__308_1, NULL, 840, 840, 7, 29},
  {cont__308_2, &frame__308_1, 841, 841, 7, 35},
  {cont__308_3, &frame__308_1, 842, 842, 7, 29},
  {cont__308_4, &frame__308_1, 844, 844, 9, 14},
  {cont__308_5, &frame__308_1, 843, 892, 7, 36},
  {cont__308_56, &frame__308_1, 893, 893, 10, 26},
  {cont__308_57, &frame__308_1, 893, 894, 7, 67},
  {cont__308_61, &frame__308_1, },
  {entry__317_1, NULL, 943, 943, 27, 36},
  {cont__317_2, &frame__317_1, 946, 946, 26, 42},
  {cont__317_3, &frame__317_1, 947, 947, 33, 56},
  {cont__317_4, &frame__317_1, 947, 947, 58, 58},
  {entry__328_3, NULL, 1035, 1035, 26, 42},
  {cont__328_4, &frame__328_3, 1036, 1036, 33, 56},
  {cont__328_5, &frame__328_3, 1032, 1036, 9, 57},
  {entry__328_15, NULL, 1050, 1050, 11, 72},
  {entry__328_26, NULL, 1059, 1059, 35, 54},
  {cont__328_27, &frame__328_26, 1060, 1060, 20, 39},
  {cont__328_28, &frame__328_26, 1060, 1060, 20, 44},
  {cont__328_29, &frame__328_26, 1060, 1060, 17, 51},
  {cont__328_30, &frame__328_26, 1061, 1061, 51, 51},
  {cont__328_31, &frame__328_26, 1061, 1061, 32, 52},
  {cont__328_32, &frame__328_26, 1061, 1061, 17, 58},
  {cont__328_33, &frame__328_26, 1061, 1061, 58, 58},
  {entry__328_25, NULL, 1055, 1061, 15, 58},
  {entry__328_35, NULL, 1067, 1067, 52, 52},
  {cont__328_36, &frame__328_35, 1067, 1067, 55, 55},
  {cont__328_37, &frame__328_35, 1067, 1067, 35, 56},
  {cont__328_38, &frame__328_35, 1068, 1068, 20, 39},
  {cont__328_39, &frame__328_35, 1068, 1068, 20, 44},
  {cont__328_40, &frame__328_35, 1068, 1068, 17, 51},
  {cont__328_41, &frame__328_35, 1069, 1069, 52, 52},
  {cont__328_42, &frame__328_35, 1069, 1069, 33, 53},
  {cont__328_43, &frame__328_35, 1069, 1069, 17, 59},
  {cont__328_44, &frame__328_35, 1069, 1069, 59, 59},
  {entry__328_34, NULL, 1063, 1069, 15, 59},
  {entry__328_20, NULL, 1052, 1052, 11, 35},
  {cont__328_21, &frame__328_20, 1054, 1054, 24, 39},
  {cont__328_22, &frame__328_20, 1054, 1054, 13, 40},
  {cont__328_23, &frame__328_20, 1054, 1054, 13, 60},
  {cont__328_24, &frame__328_20, 1053, 1069, 11, 61},
  {entry__328_11, NULL, 1048, 1048, 9, 38},
  {cont__328_12, &frame__328_11, 1049, 1049, 12, 31},
  {cont__328_13, &frame__328_11, 1049, 1049, 12, 35},
  {cont__328_14, &frame__328_11, 1049, 1050, 9, 72},
  {cont__328_17, &frame__328_11, 1051, 1051, 12, 31},
  {cont__328_18, &frame__328_11, 1051, 1051, 12, 35},
  {cont__328_19, &frame__328_11, 1051, 1069, 9, 62},
  {cont__328_45, &frame__328_11, 1069, 1069, 62, 62},
  {entry__331_1, NULL, 1103, 1103, 30, 30},
  {entry__339_8, NULL, 1172, 1172, 27, 46},
  {cont__339_9, &frame__339_8, 1172, 1172, 48, 80},
  {cont__339_10, &frame__339_8, 1172, 1172, 19, 80},
  {cont__339_11, &frame__339_8, 1172, 1172, 80, 80},
  {entry__339_6, NULL, 1171, 1171, 26, 44},
  {cont__339_7, &frame__339_6, 1171, 1172, 17, 80},
  {cont__339_12, &frame__339_6, 1173, 1173, 46, 46},
  {entry__351_14, NULL, 1266, 1267, 17, 54},
  {cont__351_15, &frame__351_14, 1267, 1267, 55, 55},
  {entry__351_17, NULL, 1270, 1270, 45, 66},
  {cont__351_18, &frame__351_17, 1270, 1270, 38, 79},
  {cont__351_19, &frame__351_17, 1270, 1270, 38, 79},
  {entry__351_21, NULL, 1272, 1272, 21, 41},
  {entry__351_16, NULL, 1270, 1270, 19, 79},
  {cont__351_20, &frame__351_16, 1269, 1272, 17, 42},
  {entry__351_3, NULL, 1253, 1253, 13, 41},
  {cont__351_4, &frame__351_3, 1254, 1254, 13, 47},
  {cont__351_5, &frame__351_3, 1259, 1259, 47, 63},
  {cont__351_6, &frame__351_3, 1259, 1259, 66, 66},
  {cont__351_7, &frame__351_3, 1259, 1259, 31, 67},
  {cont__351_8, &frame__351_3, 1260, 1260, 30, 46},
  {cont__351_9, &frame__351_3, 1261, 1261, 37, 60},
  {cont__351_10, &frame__351_3, 1263, 1263, 13, 52},
  {cont__351_11, &frame__351_3, 1265, 1265, 15, 36},
  {cont__351_12, &frame__351_3, 1265, 1265, 15, 45},
  {cont__351_13, &frame__351_3, 1264, 1272, 13, 44},
  {cont__351_22, &frame__351_3, 1276, 1276, 42, 58},
  {cont__351_23, &frame__351_3, 1276, 1276, 24, 59},
  {cont__351_24, &frame__351_3, 1276, 1276, 19, 69},
  {cont__351_25, &frame__351_3, 1273, 1276, 13, 71},
  {entry__360_17, NULL, 1402, 1402, 21, 50},
  {cont__360_18, &frame__360_17, 1402, 1402, 21, 58},
  {cont__360_19, &frame__360_17, 1402, 1402, 21, 58},
  {entry__360_21, NULL, 1404, 1406, 21, 58},
  {entry__360_13, NULL, 1398, 1398, 30, 47},
  {cont__360_14, &frame__360_13, 1398, 1398, 17, 50},
  {cont__360_15, &frame__360_13, 1401, 1401, 21, 61},
  {cont__360_16, &frame__360_13, 1400, 1402, 19, 58},
  {cont__360_20, &frame__360_13, 1399, 1406, 17, 60},
  {cont__360_23, &frame__360_13, 1409, 1409, 27, 44},
  {cont__360_24, &frame__360_13, 1409, 1409, 49, 49},
  {cont__360_25, &frame__360_13, 1409, 1409, 21, 50},
  {cont__360_26, &frame__360_13, 1407, 1410, 17, 63},
  {cont__360_27, &frame__360_13, 1410, 1410, 64, 64},
  {entry__360_11, NULL, 1397, 1397, 18, 58},
  {cont__360_12, &frame__360_11, 1397, 1410, 15, 64},
  {cont__360_28, &frame__360_11, 1411, 1411, 15, 19},
  {entry__360_9, NULL, 1396, 1396, 20, 37},
  {cont__360_10, &frame__360_9, 1396, 1411, 13, 19},
  {entry__360_6, NULL, 1395, 1395, 28, 45},
  {cont__360_7, &frame__360_6, 1395, 1395, 50, 50},
  {cont__360_8, &frame__360_6, 1395, 1411, 11, 20},
  {cont__360_29, &frame__360_6, 1411, 1411, 20, 20},
  {entry__360_5, NULL, 1394, 1411, 9, 21},
  {cont__360_30, &frame__360_5, },
  {entry__364_9, NULL, 1450, 1452, 15, 67},
  {entry__364_13, NULL, 1453, 1453, 65, 65},
  {entry__364_7, NULL, 1449, 1449, 16, 42},
  {cont__364_8, &frame__364_7, 1449, 1452, 13, 68},
  {cont__364_11, &frame__364_7, 1453, 1453, 16, 36},
  {cont__364_12, &frame__364_7, 1453, 1453, 13, 65},
  {cont__364_14, &frame__364_7, 1454, 1454, 33, 33},
  {entry__364_5, NULL, 1448, 1448, 18, 38},
  {cont__364_6, &frame__364_5, 1448, 1454, 11, 33},
  {entry__364_16, NULL, 1456, 1456, 11, 79},
  {entry__364_3, NULL, 1447, 1447, 18, 36},
  {cont__364_4, &frame__364_3, 1447, 1454, 9, 34},
  {cont__364_15, &frame__364_3, 1455, 1456, 9, 79}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *character__9;
static NODE *character__35;
static NODE *number__6;
static NODE *number__99;
static NODE *character__38;
static NODE *character__47;
static NODE *character__94;
static NODE *character__96;
static NODE *character__55;
static NODE *character__65;
static NODE *character__63;
static NODE *number__12;
static NODE *character__44;
static NODE *character__45;
static NODE *character__10;
static NODE *character__58;
static NODE *number__0;
static NODE *character__70;
static NODE *character__48;
static NODE *number__3;
static NODE *character__13;
static NODE *character__37;
static NODE *character__102;
static NODE *number__4;
static NODE *character__60;
static NODE *character__95;
static NODE *character__33;
static NODE *number__8;
static NODE *character__64;
static NODE *character__40;
static NODE *number__7;
static NODE *character__34;
static NODE *character__36;
static NODE *number__5;
static NODE *character__123;
static NODE *character__39;
static NODE *number__9;
static NODE *character__32;
static NODE *character__61;
static NODE *number__11;
static NODE *character__125;
static NODE *character__43;
static NODE *character__101;
static NODE *number__13;
static NODE *character__41;
static NODE *character__124;
static NODE *character__59;
static NODE *character__97;
static NODE *number__1;
static NODE *character__69;
static NODE *character__49;
static NODE *character__46;
static NODE *number__2;
static NODE *character__42;
static NODE *number__10;
static NODE *character__62;
static NODE *number__14;

static const char *used_namespaces[] = {
  "std",
  "compiler",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "parser",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("parser.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__parser(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 22);
  // 101: $types::syntax_error types::grammar_object
  initialize_maybe_future(var.types__syntax_error, get__types__grammar_object());
  // 111: $types::unexpected_input_error types::grammar_object
  initialize_maybe_future(var.types__unexpected_input_error, get__types__grammar_object());
  // 152: $dump_stream types::grammar_object
  initialize_maybe_future(var._dump_stream, get__types__grammar_object());
  // 182: $dump types::grammar_object
  initialize_maybe_future(var._dump, get__types__grammar_object());
  // 188: $dump3 types::grammar_object
  initialize_maybe_future(var._dump3, get__types__grammar_object());
  // 194: $dump5 types::grammar_object
  initialize_maybe_future(var._dump5, get__types__grammar_object());
  // 209: "*" = 14
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccb;
  arguments->slots[1] = number__14;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_2;
}
static void cont__216_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 210: "/" = 14
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cce;
  arguments->slots[1] = number__14;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_4;
}
static void cont__216_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 211: "+" = 13
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cca;
  arguments->slots[1] = number__13;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_6;
}
static void cont__216_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 212: "-" = 13
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccc;
  arguments->slots[1] = number__13;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_8;
}
static void cont__216_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 213: "<<" = 12
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6e82bf9;
  arguments->slots[1] = number__12;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_10;
}
static void cont__216_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 214: ">>" = 12
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6f82bfb;
  arguments->slots[1] = number__12;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_12;
}
static void cont__216_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 215: "&" = 11
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc7;
  arguments->slots[1] = number__11;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_14;
}
static void cont__216_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 216: "^" = 10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cbf;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_15;
}
static void cont__216_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 217: "|" = 9
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9c9d;
  arguments->slots[1] = number__9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_17;
}
static void cont__216_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 218: "<=" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6e82bf8;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_19;
}
static void cont__216_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 219: "<" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdd;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_21;
}
static void cont__216_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 220: ">=" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6f82bf8;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_23;
}
static void cont__216_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 221: ">" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdf;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_25;
}
static void cont__216_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 222: "==" = 7
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6e02bf8;
  arguments->slots[1] = number__7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_27;
}
static void cont__216_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 223: "!=" = 7
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6002bf8;
  arguments->slots[1] = number__7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_29;
}
static void cont__216_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 224: "&&" = 5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6382be3;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_31;
}
static void cont__216_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 225: "||" = 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4e82bb9;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_33;
}
static void cont__216_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  // 226: ".." = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6782beb;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_35;
}
static void cont__216_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 227: "," = 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccd;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_37;
}
static void cont__216_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__19 */ = arguments->slots[0];
  // 228: "=" = 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdc;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__216_39;
}
static void cont__216_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__20 */ = arguments->slots[0];
  // 207: $precedence_table
  // 208:   table
  // 209:     "*" = 14
  // 210:     "/" = 14
  // 211:     "+" = 13
  // 212:     "-" = 13
  // 213:     "<<" = 12
  // 214:     ">>" = 12
  // 215:     "&" = 11
  // 216:     "^" = 10
  // ...
  argument_count = 20;
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
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__216_40;
}
static void cont__216_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._precedence_table, arguments->slots[0]);
  // 245: %arguments_index undefined
  initialize_maybe_future(get__arguments_index(), get__undefined());
  // 246: $types::store_arguments_index types::grammar_object
  initialize_maybe_future(var.types__store_arguments_index, get__types__grammar_object());
  // 258: %within_inline_expression false
  initialize_maybe_future(get__within_inline_expression(), get__false());
  // 259: $types::inline types::grammar_object
  initialize_maybe_future(var.types__inline, get__types__grammar_object());
  // 267: $NOT_INLINE
  // 268:   check_node
  // 269:     : (_node stream)
  // 270:       if within_inline_expression:
  // 271:         ParseError stream "
  // 272:           ")" expected@
  // 273:       -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__230_1;
  result_count = 1;
  myself = get__check_node();
  func = myself->type;
  frame->cont = cont__230_5;
}
static void entry__230_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 270: ... :
  // 271:   ParseError stream "
  // 272:     ")" expected@
  frame->slots[2] /* temp__1 */ = create_closure(entry__230_2, 0);
  // 270: if within_inline_expression:
  // 271:   ParseError stream "
  // 272:     ")" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__within_inline_expression();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__230_4;
}
static void entry__230_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 271: ParseError stream "
  // 272:   ")" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__ccbf6d451aa8563f;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__230_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 273: -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__230_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NOT_INLINE, arguments->slots[0]);
  // 275: ... followed_by(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__231_1;
}
static void cont__231_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 275: $NEWLINE followed_by(newline), NOT_INLINE, newline
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__newline();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__231_2;
}
static void cont__231_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEWLINE, arguments->slots[0]);
  // 276: ... followed_by(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__232_1;
}
static void cont__232_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 276: $INDENT followed_by(indent_marker), NOT_INLINE, indent_marker
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__indent_marker();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__232_2;
}
static void cont__232_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INDENT, arguments->slots[0]);
  // 277: ... followed_by(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__233_1;
}
static void cont__233_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 277: $OUTDENT followed_by(outdent_marker), NOT_INLINE, outdent_marker
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__outdent_marker();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__233_2;
}
static void cont__233_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OUTDENT, arguments->slots[0]);
  // 278: ... followed_by('#')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__35;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__234_1;
}
static void cont__234_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 278: $HASHTAG followed_by('#'), NOT_INLINE, '#'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = character__35;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__234_2;
}
static void cont__234_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._HASHTAG, arguments->slots[0]);
  // 288: $compiler::WHITESPACE many(' ')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__237_1;
}
static void cont__237_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.compiler__WHITESPACE, arguments->slots[0]);
  // 289: ... followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__238_1;
}
static void cont__238_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 289: $SEPARATOR alt(compiler::WHITESPACE followed_by(':'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__238_2;
}
static void cont__238_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SEPARATOR, arguments->slots[0]);
  // 290: $NEWLINES many(NEWLINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__239_1;
}
static void cont__239_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEWLINES, arguments->slots[0]);
  // 292: $STORE_POSITION
  // 293:   modify_node
  // 294:     :
  // 295:       (
  // 296:         &node
  // 297:         stream
  // 298:       )
  // 299:       !node.source_position_of length_of(stream)
  // 300:       !node.fragment_of current_fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__240_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__240_3;
}
static void entry__240_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 299: !node.source_position_of length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__240_2;
}
static void cont__240_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 299: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 300: !node.fragment_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__fragment_of, get__current_fragment());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__240_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_POSITION, arguments->slots[0]);
  // 302: $STORE_POSITION_MINUS_1
  // 303:   modify_node
  // 304:     :
  // 305:       (
  // 306:         &node
  // 307:         stream
  // 308:       )
  // 309:       !node.source_position_of length_of(stream)+1
  // 310:       !node.fragment_of current_fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__241_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__241_4;
}
static void entry__241_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 309: ... length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__241_2;
}
static void cont__241_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 309: !node.source_position_of length_of(stream)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__241_3;
}
static void cont__241_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 309: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 310: !node.fragment_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__fragment_of, get__current_fragment());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__241_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_POSITION_MINUS_1, arguments->slots[0]);
  // 312: $STORE_END_POSITION
  // 313:   modify_node
  // 314:     :
  // 315:       (
  // 316:         &node
  // 317:         stream
  // 318:       )
  // 319:       !node.end_position_of length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__242_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__242_3;
}
static void entry__242_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 319: !node.end_position_of length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__242_2;
}
static void cont__242_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 319: !node.end_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__242_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_END_POSITION, arguments->slots[0]);
  // 323: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__243_1;
}
static void cont__243_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 325: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__243_2;
}
static void cont__243_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__243_3;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__243_5;
}
static void entry__243_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 331: !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__243_4;
}
static void cont__243_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 331: !node.namespace_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__namespace_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__243_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 332: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__243_6;
}
static void cont__243_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__243_8;
}
static void cont__243_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__243_9;
}
static void cont__243_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 321: $IDENTIFIER
  // 322:   sequence
  // 323:     set_node(identifier)
  // 324:     STORE_POSITION
  // 325:     capture(name_of NAME)
  // 326:     optional
  // 327:       sequence
  // 328:         "::"
  // 329:         modify_node
  // 330:           : (&node)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[2] /* temp__3 */;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__243_10;
}
static void cont__243_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._IDENTIFIER, arguments->slots[0]);
  // 337: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__244_1;
}
static void cont__244_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 339: optional(NOT_USED)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NOT_USED;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__244_2;
}
static void cont__244_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 340: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__244_3;
}
static void cont__244_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__244_4;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__244_10;
}
static void entry__244_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 346: ... node.is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_not_used();
  func = myself->type;
  frame->cont = cont__244_5;
}
static void cont__244_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 346: ... :
  // 347:   SyntaxError node "namespace must not start with an underscore"
  frame->slots[2] /* temp__2 */ = create_closure(entry__244_6, 0);
  // 346: if node.is_not_used:
  // 347:   SyntaxError node "namespace must not start with an underscore"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__244_8;
}
static void entry__244_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 347: SyntaxError node "namespace must not start with an underscore"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  arguments->slots[1] = string__958c1dda41e5a79c;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__244_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 348: !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__244_9;
}
static void cont__244_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 348: !node.namespace_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__namespace_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__244_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 349: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__244_11;
}
static void cont__244_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__244_12;
}
static void cont__244_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__244_13;
}
static void cont__244_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 335: $DEFINE_IDENTIFIER
  // 336:   sequence
  // 337:     set_node(identifier)
  // 338:     STORE_POSITION
  // 339:     optional(NOT_USED)
  // 340:     capture(name_of NAME)
  // 341:     optional
  // 342:       sequence
  // 343:         "::"
  // 344:         modify_node
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[2] /* temp__3 */;
  arguments->slots[4] = frame->slots[3] /* temp__4 */;
  arguments->slots[5] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__244_14;
}
static void cont__244_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_IDENTIFIER, arguments->slots[0]);
  // 354: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__245_1;
}
static void cont__245_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 356: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__245_2;
}
static void cont__245_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 357: expect("::")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__245_3;
}
static void cont__245_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 358: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__245_4;
}
static void cont__245_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 352: $NAMESPACED_IDENTIFIER
  // 353:   sequence
  // 354:     set_node(identifier)
  // 355:     STORE_POSITION
  // 356:     capture(namespace_of NAME)
  // 357:     expect("::")
  // 358:     capture(name_of NAME)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[2] /* temp__3 */;
  arguments->slots[4] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__245_5;
}
static void cont__245_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMESPACED_IDENTIFIER, arguments->slots[0]);
  // 363: ... optional("./")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6782bea;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__246_2;
}
static void cont__246_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 363: ... "/", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cce;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__246_3;
}
static void cont__246_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 363: ... some("/", NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__246_4;
}
static void cont__246_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 363: $FILENAME optional("./"), NAME, some("/", NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__246_5;
}
static void cont__246_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FILENAME, arguments->slots[0]);
  // 368: set_node(require_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__require_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__247_1;
}
static void cont__247_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 371: capture(node::filename_of FILENAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filename_of();
  arguments->slots[1] = var._FILENAME;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__247_2;
}
static void cont__247_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__247_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__247_13;
}
static void entry__247_3(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // node: 0
  // stream: 1
  // filename: 2
  frame->slots[2] /* filename */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 376: $filename node::filename_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filename_of();
  func = myself->type;
  frame->cont = cont__247_4;
}
static void cont__247_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 377: ... required_modules(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__247_5;
}
static void cont__247_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 377: ... required_modules(filename).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__247_6;
}
static void cont__247_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 377: ... :
  // 378:   ParseError stream "
  // 379:     the module "@(filename)" is required twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__247_7, 0);
  // 377: if required_modules(filename).is_defined:
  // 378:   ParseError stream "
  // 379:     the module "@(filename)" is required twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__247_11;
}
static void entry__247_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // filename: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[1] = myself->closure.frame->slots[2]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 378: ... "
  // 379:   the module "@(filename)" is required twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__92e1510f182d5769;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__fd365ba9213c93f1;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__247_10;
}
static void cont__247_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 378: ParseError stream "
  // 379:   the module "@(filename)" is required twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__247_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 380: !required_modules(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__247_12;
}
static void cont__247_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__required_modules(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__247_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 365: $REQUIRE
  // 366:   sequence
  // 367:     "<require"
  // 368:     set_node(require_instruction)
  // 369:     STORE_POSITION
  // 370:     compiler::WHITESPACE
  // 371:     capture(node::filename_of FILENAME)
  // 372:     ">"
  // 373:     STORE_END_POSITION
  // 374:     inspect_node
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = string__44dcaf9484448bc5;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._STORE_POSITION;
  arguments->slots[3] = var.compiler__WHITESPACE;
  arguments->slots[4] = frame->slots[1] /* temp__2 */;
  arguments->slots[5] = string__578a5af303e9cdf;
  arguments->slots[6] = var._STORE_END_POSITION;
  arguments->slots[7] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__247_15;
}
static void cont__247_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REQUIRE, arguments->slots[0]);
  // 386: set_node(namespace_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__namespace_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__248_1;
}
static void cont__248_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 387: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__248_2;
}
static void cont__248_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 390: infix_operator("=")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdc;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__248_3;
}
static void cont__248_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__248_4;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__248_6;
}
static void entry__248_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 393: !node.namespace_alias_of node.namespace_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__248_5;
}
static void cont__248_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 393: !node.namespace_alias_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__namespace_alias_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__248_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 394: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__248_7;
}
static void cont__248_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__248_8;
}
static void cont__248_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__248_9;
}
static void cont__248_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__248_10;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__248_30;
}
static void entry__248_14(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // alias: 0
  // stream: 1
  // namespace: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* alias */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[2] = myself->closure.frame->slots[2]; /* namespace */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 402: ... namespace_mappings(alias)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alias */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__248_15;
}
static void cont__248_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 402: ... namespace_mappings(alias).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__248_16;
}
static void cont__248_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 402: ... :
  // 403:   ParseError stream "
  // 404:     the namespace alias "@(alias)" is defined twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__248_17, 0);
  // 402: if namespace_mappings(alias).is_defined:
  // 403:   ParseError stream "
  // 404:     the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__248_21;
}
static void entry__248_17(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // alias: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[1] = myself->closure.frame->slots[0]; /* alias */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 403: ... "
  // 404:   the namespace alias "@(alias)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__e13e5990aea4c8f3;
  arguments->slots[1] = frame->slots[1] /* alias */;
  arguments->slots[2] = string__54767964cc2066c4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__248_20;
}
static void cont__248_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 403: ParseError stream "
  // 404:   the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__248_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 405: !namespace_mappings(alias)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alias */;
  arguments->slots[1] = frame->slots[2] /* namespace */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__248_22;
}
static void cont__248_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__namespace_mappings(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__248_23(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // namespace: 0
  // stream: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 407: ... defined_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__defined_namespaces();
  func = myself->type;
  frame->cont = cont__248_24;
}
static void cont__248_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 407: ... :
  // 408:   ParseError stream "
  // 409:     the namespace "@(namespace)" is defined twice@
  frame->slots[3] /* temp__2 */ = create_closure(entry__248_25, 0);
  // 407: if defined_namespaces(namespace):
  // 408:   ParseError stream "
  // 409:     the namespace "@(namespace)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__248_28;
}
static void entry__248_25(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // namespace: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[1] = myself->closure.frame->slots[0]; /* namespace */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 408: ... "
  // 409:   the namespace "@(namespace)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9159abe89634488c;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__54767964cc2066c4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__248_27;
}
static void cont__248_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 408: ParseError stream "
  // 409:   the namespace "@(namespace)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__248_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 410: !defined_namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__defined_namespaces();
  func = myself->type;
  frame->cont = cont__248_29;
}
static void cont__248_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_namespaces(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__248_10(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // node: 0
  // stream: 1
  // namespace: 2
  // alias: 3
  frame->slots[2] /* namespace */ = create_future();
  frame->slots[3] /* alias */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 398: $namespace namespace_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__248_11;
}
static void cont__248_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 399: $alias namespace_alias_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_alias_of();
  func = myself->type;
  frame->cont = cont__248_12;
}
static void cont__248_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* alias */, arguments->slots[0]);
  // 401: alias.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* alias */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__248_13;
}
static void cont__248_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 401: ... :
  // 402:   if namespace_mappings(alias).is_defined:
  // 403:     ParseError stream "
  // 404:       the namespace alias "@(alias)" is defined twice@
  // 405:   !namespace_mappings(alias) namespace
  frame->slots[5] /* temp__2 */ = create_closure(entry__248_14, 0);
  // 406: :
  // 407:   if defined_namespaces(namespace):
  // 408:     ParseError stream "
  // 409:       the namespace "@(namespace)" is defined twice@
  // 410:   !defined_namespaces(namespace) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__248_23, 0);
  // 400: if
  // 401:   alias.is_defined:
  // 402:     if namespace_mappings(alias).is_defined:
  // 403:       ParseError stream "
  // 404:         the namespace alias "@(alias)" is defined twice@
  // 405:     !namespace_mappings(alias) namespace
  // 406:   :
  // 407:     if defined_namespaces(namespace):
  // 408:       ParseError stream "
  // 409:         the namespace "@(namespace)" is defined twice@
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
static void cont__248_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 382: $NAMESPACE
  // 383:   sequence
  // 384:     "<namespace"
  // 385:     compiler::WHITESPACE
  // 386:     set_node(namespace_instruction)
  // 387:     capture(namespace_of NAME)
  // 388:     optional
  // 389:       sequence
  // 390:         infix_operator("=")
  // 391:         modify_node
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__1552f059283245c4;
  arguments->slots[1] = var.compiler__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = frame->slots[2] /* temp__3 */;
  arguments->slots[5] = string__578a5af303e9cdf;
  arguments->slots[6] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__248_32;
}
static void cont__248_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMESPACE, arguments->slots[0]);
  // 416: set_node(using_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__using_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__249_1;
}
static void cont__249_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 417: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__249_2;
}
static void cont__249_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__249_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__249_11;
}
static void entry__249_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // node: 0
  // stream: 1
  // namespace: 2
  frame->slots[2] /* namespace */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 421: $namespace namespace_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__249_4;
}
static void cont__249_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 422: ... used_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__249_5;
}
static void cont__249_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 422: ... :
  // 423:   ParseError stream "
  // 424:     the namespace "@(namespace)" is used twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__249_6, 0);
  // 422: if used_namespaces(namespace):
  // 423:   ParseError stream "
  // 424:     the namespace "@(namespace)" is used twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__249_9;
}
static void entry__249_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // namespace: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[1] = myself->closure.frame->slots[2]; /* namespace */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 423: ... "
  // 424:   the namespace "@(namespace)" is used twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9159abe89634488c;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__1d0508008a8a40d8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__249_8;
}
static void cont__249_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 423: ParseError stream "
  // 424:   the namespace "@(namespace)" is used twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__249_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 425: !used_namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__249_10;
}
static void cont__249_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_namespaces(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__249_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 412: $USING
  // 413:   sequence
  // 414:     "<using"
  // 415:     compiler::WHITESPACE
  // 416:     set_node(using_instruction)
  // 417:     capture(namespace_of NAME)
  // 418:     ">"
  // 419:     inspect_node
  // 420:       : (node stream)
  // 421:         $namespace namespace_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__7e1f542e81cb02b0;
  arguments->slots[1] = var.compiler__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9cdf;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__249_13;
}
static void cont__249_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._USING, arguments->slots[0]);
  // 427: ... alt(LETTER DIGIT '_' '.')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  arguments->slots[1] = get__DIGIT();
  arguments->slots[2] = character__95;
  arguments->slots[3] = character__46;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__250_1;
}
static void cont__250_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 427: $BASENAME many(alt(LETTER DIGIT '_' '.'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__250_2;
}
static void cont__250_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BASENAME, arguments->slots[0]);
  // 428: ... some("../")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa733c15f596be3;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__251_2;
}
static void cont__251_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 428: ... alt('/' "./" some("../"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__2d7981f4e6782bea;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__251_3;
}
static void cont__251_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 428: ... '/', BASENAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = var._BASENAME;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__251_4;
}
static void cont__251_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 428: ... some('/', BASENAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__251_5;
}
static void cont__251_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 428: $C_FILENAME alt('/' "./" some("../")), BASENAME, some('/', BASENAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._BASENAME;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__251_6;
}
static void cont__251_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_FILENAME, arguments->slots[0]);
  // 434: set_node(include_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__include_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__252_1;
}
static void cont__252_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 435: capture(node::filename_of C_FILENAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filename_of();
  arguments->slots[1] = var._C_FILENAME;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__252_2;
}
static void cont__252_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__252_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__252_12;
}
static void entry__252_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // node: 0
  // stream: 1
  // filename: 2
  frame->slots[2] /* filename */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 439: $filename node::filename_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filename_of();
  func = myself->type;
  frame->cont = cont__252_4;
}
static void cont__252_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 440: ... included_files(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__252_5;
}
static void cont__252_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   ParseError stream "
  // 442:     the file "@(filename)" is included twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__252_6, 0);
  // 440: if included_files(filename):
  // 441:   ParseError stream "
  // 442:     the file "@(filename)" is included twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__252_10;
}
static void entry__252_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // filename: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[1] = myself->closure.frame->slots[2]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... "
  // 442:   the file "@(filename)" is included twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2c64b158ac2be503;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__b0b6bb19371893f7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__252_9;
}
static void cont__252_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 441: ParseError stream "
  // 442:   the file "@(filename)" is included twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__252_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 443: !included_files(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__252_11;
}
static void cont__252_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__included_files(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__252_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 430: $INCLUDE
  // 431:   sequence
  // 432:     "<include"
  // 433:     compiler::WHITESPACE
  // 434:     set_node(include_instruction)
  // 435:     capture(node::filename_of C_FILENAME)
  // 436:     ">"
  // 437:     inspect_node
  // 438:       : (node stream)
  // 439:         $filename node::filename_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__76b0a89104f5abc5;
  arguments->slots[1] = var.compiler__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9cdf;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__252_14;
}
static void cont__252_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INCLUDE, arguments->slots[0]);
  // 449: set_node(link_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__link_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__253_1;
}
static void cont__253_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 450: capture(node::filename_of C_FILENAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filename_of();
  arguments->slots[1] = var._C_FILENAME;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__253_2;
}
static void cont__253_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__253_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__253_12;
}
static void entry__253_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // node: 0
  // stream: 1
  // filename: 2
  frame->slots[2] /* filename */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 454: $filename node::filename_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filename_of();
  func = myself->type;
  frame->cont = cont__253_4;
}
static void cont__253_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 455: ... linked_libraries(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__linked_libraries();
  func = myself->type;
  frame->cont = cont__253_5;
}
static void cont__253_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 455: ... :
  // 456:   ParseError stream "
  // 457:     the library "@(filename)" is linked twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__253_6, 0);
  // 455: if linked_libraries(filename):
  // 456:   ParseError stream "
  // 457:     the library "@(filename)" is linked twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__253_10;
}
static void entry__253_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // filename: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[1] = myself->closure.frame->slots[2]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 456: ... "
  // 457:   the library "@(filename)" is linked twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__a660d7293a5c47e8;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__ad06d2ccd69d8e1;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__253_9;
}
static void cont__253_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 456: ParseError stream "
  // 457:   the library "@(filename)" is linked twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__253_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 458: !linked_libraries(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__linked_libraries();
  func = myself->type;
  frame->cont = cont__253_11;
}
static void cont__253_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__linked_libraries(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__253_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 445: $LINK
  // 446:   sequence
  // 447:     "<link"
  // 448:     compiler::WHITESPACE
  // 449:     set_node(link_instruction)
  // 450:     capture(node::filename_of C_FILENAME)
  // 451:     ">"
  // 452:     inspect_node
  // 453:       : (node stream)
  // 454:         $filename node::filename_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__525ae943eabdd03c;
  arguments->slots[1] = var.compiler__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9cdf;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__253_14;
}
static void cont__253_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINK, arguments->slots[0]);
  // 460: ... alt(LETTER DIGIT '_' '.' '*' '?')
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  arguments->slots[1] = get__DIGIT();
  arguments->slots[2] = character__95;
  arguments->slots[3] = character__46;
  arguments->slots[4] = character__42;
  arguments->slots[5] = character__63;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__254_1;
}
static void cont__254_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 460: $MASK many(alt(LETTER DIGIT '_' '.' '*' '?'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__254_2;
}
static void cont__254_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MASK, arguments->slots[0]);
  // 461: ... some("../")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa733c15f596be3;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__255_1;
}
static void cont__255_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 461: ... alt('/' "./" some("../"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__2d7981f4e6782bea;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__255_2;
}
static void cont__255_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 461: ... '/', MASK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = var._MASK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__255_3;
}
static void cont__255_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 461: ... some('/', MASK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__255_4;
}
static void cont__255_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 461: $FILEMASK alt('/' "./" some("../")), MASK, some('/', MASK)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._MASK;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__255_5;
}
static void cont__255_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FILEMASK, arguments->slots[0]);
  // 467: set_node(data_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__data_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__256_1;
}
static void cont__256_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 468: capture(node::filemask_of FILEMASK)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filemask_of();
  arguments->slots[1] = var._FILEMASK;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__256_2;
}
static void cont__256_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__256_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__256_11;
}
static void entry__256_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // node: 0
  // stream: 1
  // filemask: 2
  frame->slots[2] /* filemask */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 472: $filemask node::filemask_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filemask_of();
  func = myself->type;
  frame->cont = cont__256_4;
}
static void cont__256_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filemask */, arguments->slots[0]);
  // 473: ... dependent_data(filemask)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filemask */;
  result_count = 1;
  myself = get__dependent_data();
  func = myself->type;
  frame->cont = cont__256_5;
}
static void cont__256_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 473: ... :
  // 474:   ParseError stream "
  // 475:     the data dependency "@(filemask)" is defined twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__256_6, 0);
  // 473: if dependent_data(filemask):
  // 474:   ParseError stream "
  // 475:     the data dependency "@(filemask)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__256_9;
}
static void entry__256_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // filemask: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[1] = myself->closure.frame->slots[2]; /* filemask */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 474: ... "
  // 475:   the data dependency "@(filemask)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__e720c6242e8cd532;
  arguments->slots[1] = frame->slots[1] /* filemask */;
  arguments->slots[2] = string__54767964cc2066c4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__256_8;
}
static void cont__256_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 474: ParseError stream "
  // 475:   the data dependency "@(filemask)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__256_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 476: !dependent_data(filemask)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filemask */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__dependent_data();
  func = myself->type;
  frame->cont = cont__256_10;
}
static void cont__256_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__dependent_data(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__256_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 463: $DATA
  // 464:   sequence
  // 465:     "<data"
  // 466:     compiler::WHITESPACE
  // 467:     set_node(data_instruction)
  // 468:     capture(node::filemask_of FILEMASK)
  // 469:     ">"
  // 470:     inspect_node
  // 471:       : (node stream)
  // 472:         $filemask node::filemask_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__425aeb43ea6dd036;
  arguments->slots[1] = var.compiler__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9cdf;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__256_13;
}
static void cont__256_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DATA, arguments->slots[0]);
  // 480: alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = var._REQUIRE;
  arguments->slots[1] = var._NAMESPACE;
  arguments->slots[2] = var._USING;
  arguments->slots[3] = var._INCLUDE;
  arguments->slots[4] = var._LINK;
  arguments->slots[5] = var._DATA;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__257_1;
}
static void cont__257_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 481: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__257_2;
}
static void cont__257_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 481: ... NEXT_LINE_REMARK, expect(outdent_marker)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE_REMARK;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__257_3;
}
static void cont__257_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 481: ... alt(LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__257_4;
}
static void cont__257_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 481: optional(alt(LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__257_5;
}
static void cont__257_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 478: $META_INSTRUCTION
  // 479:   sequence
  // 480:     alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
  // 481:     optional(alt(LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__257_6;
}
static void cont__257_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._META_INSTRUCTION, arguments->slots[0]);
  // 502: ... some(PRINTABLE_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__PRINTABLE_CHARACTER();
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__258_1;
}
static void cont__258_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 502: $REMARK_LINE multi_capture(remark_lines_of some(PRINTABLE_CHARACTER))
  // 503:   # a single line containing remark text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__remark_lines_of();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__258_2;
}
static void cont__258_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_LINE, arguments->slots[0]);
  // 510: ... interleaved(REMARK_LINE NEWLINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_LINE;
  arguments->slots[1] = var._NEWLINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__259_1;
}
static void cont__259_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 510: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__259_2;
}
static void cont__259_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 510: ... INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__259_3;
}
static void cont__259_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 510: optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__259_4;
}
static void cont__259_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 505: $REMARK_LINES
  // 506:   #
  // 507:     a remark potentially spanning multipe lines
  // 508:   sequence
  // 509:     REMARK_LINE
  // 510:     optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_LINE;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__259_5;
}
static void cont__259_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_LINES, arguments->slots[0]);
  // 512: ... set_node(remark_statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__remark_statement();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__260_1;
}
static void cont__260_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 512: $REMARK_STATEMENT HASHTAG, set_node(remark_statement), REMARK_LINES
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._REMARK_LINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__260_2;
}
static void cont__260_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_STATEMENT, arguments->slots[0]);
  // 513: $REMARK HASHTAG, REMARK_LINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = var._REMARK_LINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__261_1;
}
static void cont__261_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK, arguments->slots[0]);
  // 514: $LINE_END_REMARK compiler::WHITESPACE, HASHTAG, REMARK_LINE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = var._HASHTAG;
  arguments->slots[2] = var._REMARK_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__262_1;
}
static void cont__262_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINE_END_REMARK, arguments->slots[0]);
  // 515: $NEXT_LINE_REMARK INDENT, REMARK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = var._REMARK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__263_1;
}
static void cont__263_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEXT_LINE_REMARK, arguments->slots[0]);
  // 517: $REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING
  // 518:   modify_node
  // 519:     : (&node)
  // 520:       unless do_pretty_print || do_extract_documentation:
  // 521:         range &node.arguments_of 1 -2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__264_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__264_9;
}
static void entry__264_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 520: ... do_pretty_print || do_extract_documentation
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = func__264_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__264_3;
}
static void entry__264_2(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 520: ... do_extract_documentation
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__264_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 520: ... :
  // 521:   range &node.arguments_of 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__264_4, 0);
  // 520: unless do_pretty_print || do_extract_documentation:
  // 521:   range &node.arguments_of 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__264_8;
}
static void entry__264_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 521: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__264_5;
}
static void cont__264_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 521: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__264_6;
}
static void cont__264_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 521: range &node.arguments_of 1 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__264_7;
}
static void cont__264_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 521: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__264_8(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__264_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING, arguments->slots[0]);
  // 526: ... set_node(remark_argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__remark_argument();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__265_1;
}
static void cont__265_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 526: ... set_node(remark_argument), REMARK_LINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = var._REMARK_LINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__265_2;
}
static void cont__265_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 526: arguments_span(set_node(remark_argument), REMARK_LINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__265_3;
}
static void cont__265_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 523: $REMARK_ARGUMENT
  // 524:   sequence
  // 525:     HASHTAG
  // 526:     arguments_span(set_node(remark_argument), REMARK_LINES)
  // 527:     REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__265_4;
}
static void cont__265_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_ARGUMENT, arguments->slots[0]);
  // 532: ... set_node(remark_argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__remark_argument();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__266_1;
}
static void cont__266_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 532: ... set_node(remark_argument), REMARK_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = var._REMARK_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__266_2;
}
static void cont__266_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 532: arguments_span(set_node(remark_argument), REMARK_LINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__266_3;
}
static void cont__266_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 529: $LINE_END_REMARK_ARGUMENT
  // 530:   sequence
  // 531:     HASHTAG
  // 532:     arguments_span(set_node(remark_argument), REMARK_LINE)
  // 533:     REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__266_4;
}
static void cont__266_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINE_END_REMARK_ARGUMENT, arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__267_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__267_4;
}
static void entry__267_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 546: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__267_2;
}
static void cont__267_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 547: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__267_3;
}
static void cont__267_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* node */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 543: ->
  // 544:   function_call
  // 545:     .functor_of node
  // 546:     .fragment_of fragment_of(node)
  // 547:     .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__267_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 548: ... not_followed_by(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__267_5;
}
static void cont__267_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 548: ... not_followed_by(')'), INLINE_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._INLINE_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__267_6;
}
static void cont__267_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 548: optional(not_followed_by(')'), INLINE_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__267_7;
}
static void cont__267_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 549: CHECK_ARGUMENTS("function call")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4456c807200257a4;
  result_count = 1;
  myself = var._CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__267_9;
}
static void cont__267_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 550: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__267_10;
}
static void cont__267_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 538: $FUNCTION_CALL
  // 539:   sequence
  // 540:     '('
  // 541:     modify_node
  // 542:       : (node)
  // 543:         ->
  // 544:           function_call
  // 545:             .functor_of node
  // 546:             .fragment_of fragment_of(node)
  // 547:             .source_position_of source_position_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[4] /* temp__5 */;
  arguments->slots[4] = frame->slots[5] /* temp__6 */;
  arguments->slots[5] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__267_11;
}
static void cont__267_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FUNCTION_CALL, arguments->slots[0]);
  // 553: $MAKE_ATTRIBUTE_ACCESS
  // 554:   modify_node
  // 555:     : (&node)
  // 556:       !node
  // 557:         function_call
  // 558:           .arguments_of list(node)
  // 559:           .is_an_attribute_access true
  // 560:           .fragment_of fragment_of(node)
  // 561:           .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__268_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__268_5;
}
static void entry__268_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 558: ... list(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__268_2;
}
static void cont__268_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 560: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__268_3;
}
static void cont__268_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 561: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__268_4;
}
static void cont__268_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 556: !node
  // 557:   function_call
  // 558:     .arguments_of list(node)
  // 559:     .is_an_attribute_access true
  // 560:     .fragment_of fragment_of(node)
  // 561:     .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[1] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__is_an_attribute_access, get__true());
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__268_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAKE_ATTRIBUTE_ACCESS, arguments->slots[0]);
  // 567: span(functor_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__269_1;
}
static void cont__269_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 563: $ATTRIBUTE_ACCESS
  // 564:   sequence
  // 565:     '.'
  // 566:     MAKE_ATTRIBUTE_ACCESS
  // 567:     span(functor_of IDENTIFIER)
  // 568:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = var._MAKE_ATTRIBUTE_ACCESS;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__269_2;
}
static void cont__269_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ATTRIBUTE_ACCESS, arguments->slots[0]);
  // 574: span(functor_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__270_1;
}
static void cont__270_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 570: $ATTRIBUTE_WRITE
  // 571:   sequence
  // 572:     '.'
  // 573:     MAKE_ATTRIBUTE_ACCESS
  // 574:     span(functor_of NAME_OF_POLYMORPHIC)
  // 575:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = var._MAKE_ATTRIBUTE_ACCESS;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__270_2;
}
static void cont__270_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ATTRIBUTE_WRITE, arguments->slots[0]);
  // 577: ... alt(FUNCTION_CALL ATTRIBUTE_ACCESS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._FUNCTION_CALL;
  arguments->slots[1] = var._ATTRIBUTE_ACCESS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__271_1;
}
static void cont__271_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 577: $EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_ACCESS))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__271_2;
}
static void cont__271_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXTENSIONS, arguments->slots[0]);
  // 578: ... alt(FUNCTION_CALL ATTRIBUTE_WRITE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._FUNCTION_CALL;
  arguments->slots[1] = var._ATTRIBUTE_WRITE;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__272_1;
}
static void cont__272_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 578: $READ_WRITE_EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_WRITE))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__272_2;
}
static void cont__272_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._READ_WRITE_EXTENSIONS, arguments->slots[0]);
  // 579: $IDENTIFIER_OR_FUNCTION_CALL IDENTIFIER, EXTENSIONS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER;
  arguments->slots[1] = var._EXTENSIONS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__273_1;
}
static void cont__273_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._IDENTIFIER_OR_FUNCTION_CALL, arguments->slots[0]);
  // 582: ... set_field(is_used_as_a_destination true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_used_as_a_destination();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__274_1;
}
static void cont__274_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 581: $READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 582:   IDENTIFIER, set_field(is_used_as_a_destination true), READ_WRITE_EXTENSIONS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._READ_WRITE_EXTENSIONS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__274_2;
}
static void cont__274_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, arguments->slots[0]);
  // 586: ... many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__275_1;
}
static void cont__275_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 586: interleaved(many(DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__275_2;
}
static void cont__275_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 587: ... many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__275_3;
}
static void cont__275_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 587: ... '.', many(DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__275_4;
}
static void cont__275_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 587: optional('.', many(DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__275_5;
}
static void cont__275_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 588: ... alt('e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__101;
  arguments->slots[1] = character__69;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__275_6;
}
static void cont__275_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 588: ... alt('+' '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__43;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__275_7;
}
static void cont__275_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 588: ... optional(alt('+' '-'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__275_8;
}
static void cont__275_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 588: ... many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__275_9;
}
static void cont__275_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 588: ... alt('e' 'E'), optional(alt('+' '-')), many(DIGIT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  arguments->slots[2] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__275_10;
}
static void cont__275_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 588: optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__275_11;
}
static void cont__275_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 584: $DECIMAL_NUMBER
  // 585:   sequence
  // 586:     interleaved(many(DIGIT) '@apos;')
  // 587:     optional('.', many(DIGIT))
  // 588:     optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__275_12;
}
static void cont__275_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DECIMAL_NUMBER, arguments->slots[0]);
  // 590: $BINARY_DIGIT alt('0' '1')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__49;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__276_1;
}
static void cont__276_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BINARY_DIGIT, arguments->slots[0]);
  // 591: ... many(BINARY_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._BINARY_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__277_1;
}
static void cont__277_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 591: ... interleaved(many(BINARY_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__277_2;
}
static void cont__277_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 591: $BINARY_NUMBER "0b", interleaved(many(BINARY_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882ba7;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__277_4;
}
static void cont__277_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BINARY_NUMBER, arguments->slots[0]);
  // 592: $OCTAL_DIGIT '0' .. '7'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__55;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__278_1;
}
static void cont__278_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OCTAL_DIGIT, arguments->slots[0]);
  // 593: ... many(OCTAL_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OCTAL_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__279_1;
}
static void cont__279_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 593: ... interleaved(many(OCTAL_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__279_2;
}
static void cont__279_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 593: $OCTAL_NUMBER "0o", interleaved(many(OCTAL_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882baa;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__279_4;
}
static void cont__279_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OCTAL_NUMBER, arguments->slots[0]);
  // 594: ... 'a' .. 'f'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__102;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__280_1;
}
static void cont__280_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 594: ... 'A' .. 'F'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__65;
  arguments->slots[1] = character__70;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__280_2;
}
static void cont__280_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 594: $HEX_DIGIT alt(DIGIT 'a' .. 'f' 'A' .. 'F')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__280_3;
}
static void cont__280_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._HEX_DIGIT, arguments->slots[0]);
  // 595: ... many(HEX_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._HEX_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__281_1;
}
static void cont__281_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 595: ... interleaved(many(HEX_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__281_2;
}
static void cont__281_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 595: $HEX_NUMBER "0x", interleaved(many(HEX_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882bbd;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__281_4;
}
static void cont__281_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._HEX_NUMBER, arguments->slots[0]);
  // 599: set_node(numeric_literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__numeric_literal();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__282_1;
}
static void cont__282_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 603: alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._HEX_NUMBER;
  arguments->slots[1] = var._OCTAL_NUMBER;
  arguments->slots[2] = var._BINARY_NUMBER;
  arguments->slots[3] = var._DECIMAL_NUMBER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__282_2;
}
static void cont__282_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__282_3;
}
static void cont__282_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 597: $NUMBER
  // 598:   sequence
  // 599:     set_node(numeric_literal)
  // 600:     STORE_POSITION
  // 601:     capture
  // 602:       node::value_of
  // 603:       alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  // 604:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__282_4;
}
static void cont__282_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NUMBER, arguments->slots[0]);
  // 608: capture(node::value_of PRINTABLE_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = get__PRINTABLE_CHARACTER();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__283_1;
}
static void cont__283_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__283_2;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__283_5;
}
static void entry__283_2(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 611: ... node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__283_3;
}
static void cont__283_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 611: !node.node::value_of node::value_of(node)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__283_4;
}
static void cont__283_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 611: !node.node::value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__value_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__283_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 606: $SIMPLE_CHARACTER
  // 607:   sequence
  // 608:     capture(node::value_of PRINTABLE_CHARACTER)
  // 609:     modify_node
  // 610:       : (&node)
  // 611:         !node.node::value_of node::value_of(node)(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__283_6;
}
static void cont__283_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMPLE_CHARACTER, arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__284_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__284_2;
}
static void entry__284_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 618: !node.node::value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__value_of, character__64);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__284_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 613: $AT_CHARACTER
  // 614:   sequence
  // 615:     '@@'
  // 616:     modify_node
  // 617:       : (&node)
  // 618:         !node.node::value_of '@@'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__284_3;
}
static void cont__284_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._AT_CHARACTER, arguments->slots[0]);
  // 622: capture(node::value_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__285_1;
}
static void cont__285_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__285_2;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__285_9;
}
static void entry__285_2(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // node: 0
  // stream: 1
  // chr: 2
  frame->slots[2] /* chr */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 630: ... node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__285_3;
}
static void cont__285_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 630: $chr character_names(node::value_of(node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__character_names();
  func = myself->type;
  frame->cont = cont__285_4;
}
static void cont__285_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* chr */, arguments->slots[0]);
  // 631: ... chr.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* chr */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__285_5;
}
static void cont__285_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 631: ... : ParseError stream "invalid character name"
  frame->slots[4] /* temp__2 */ = create_closure(entry__285_6, 0);
  // 631: unless chr.is_defined: ParseError stream "invalid character name"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__285_8;
}
static void entry__285_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 631: ... ParseError stream "invalid character name"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__dea962eab6ac8f23;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__285_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 632: !node.node::value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__value_of, frame->slots[2] /* chr */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__285_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 620: $NAMED_CHARACTER
  // 621:   sequence
  // 622:     capture(node::value_of NAME)
  // 623:     ';'
  // 624:     modify_node
  // 625:       :
  // 626:         (
  // 627:           &node
  // 628:           stream
  // 629:         )
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__59;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__285_10;
}
static void cont__285_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMED_CHARACTER, arguments->slots[0]);
  // 639: ... many(BINARY_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._BINARY_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__286_1;
}
static void cont__286_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 639: "0b", many(BINARY_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882ba7;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__286_2;
}
static void cont__286_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 640: ... many(OCTAL_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OCTAL_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__286_3;
}
static void cont__286_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 640: "0o", many(OCTAL_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882baa;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__286_4;
}
static void cont__286_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 641: ... many(HEX_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._HEX_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__286_5;
}
static void cont__286_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 641: "0x", many(HEX_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882bbd;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__286_6;
}
static void cont__286_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 642: many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__286_7;
}
static void cont__286_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  arguments->slots[3] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__286_8;
}
static void cont__286_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__286_9;
}
static void cont__286_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__286_10;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__286_14;
}
static void entry__286_10(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 647: ... node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__286_11;
}
static void cont__286_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 647: ... node::value_of(node).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__286_12;
}
static void cont__286_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 647: ... character(node::value_of(node).to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__character();
  func = myself->type;
  frame->cont = cont__286_13;
}
static void cont__286_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 646: !node
  // 647:   .node::value_of character(node::value_of(node).to_integer)
  // 648:   .is_in_numeric_notation true
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__value_of, frame->slots[1] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__is_in_numeric_notation, get__true());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__286_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 634: $NUMERIC_CHARACTER
  // 635:   sequence
  // 636:     capture
  // 637:       node::value_of
  // 638:       alt
  // 639:         "0b", many(BINARY_DIGIT)
  // 640:         "0o", many(OCTAL_DIGIT)
  // 641:         "0x", many(HEX_DIGIT)
  // 642:         many(DIGIT)
  // 643:     ';'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__59;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__286_15;
}
static void cont__286_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NUMERIC_CHARACTER, arguments->slots[0]);
  // 655: syntax_error("invalid special character")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4313674f4741806a;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__287_2;
}
static void cont__287_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 650: $SPECIAL_CHARACTER
  // 651:   alt
  // 652:     AT_CHARACTER
  // 653:     NAMED_CHARACTER
  // 654:     NUMERIC_CHARACTER
  // 655:     syntax_error("invalid special character")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._AT_CHARACTER;
  arguments->slots[1] = var._NAMED_CHARACTER;
  arguments->slots[2] = var._NUMERIC_CHARACTER;
  arguments->slots[3] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__287_3;
}
static void cont__287_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SPECIAL_CHARACTER, arguments->slots[0]);
  // 657: ... '@@', SPECIAL_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = var._SPECIAL_CHARACTER;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__288_1;
}
static void cont__288_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 657: $CHARACTER_SYMBOL alt('@@', SPECIAL_CHARACTER SIMPLE_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._SIMPLE_CHARACTER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__288_2;
}
static void cont__288_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._CHARACTER_SYMBOL, arguments->slots[0]);
  // 662: set_node(character_literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__character_literal();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__289_1;
}
static void cont__289_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 665: expect('@apos;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__39;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__289_2;
}
static void cont__289_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 659: $CHARACTER
  // 660:   sequence
  // 661:     '@apos;'
  // 662:     set_node(character_literal)
  // 663:     STORE_POSITION_MINUS_1
  // 664:     CHARACTER_SYMBOL
  // 665:     expect('@apos;')
  // 666:     STORE_END_POSITION
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = character__39;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = var._CHARACTER_SYMBOL;
  arguments->slots[4] = frame->slots[1] /* temp__2 */;
  arguments->slots[5] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__289_3;
}
static void cont__289_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._CHARACTER, arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__290_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__290_5;
}
static void entry__290_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 675: ... node.node::text_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__290_2;
}
static void cont__290_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 675: ... node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__290_3;
}
static void cont__290_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 675: push &node.node::text_of node::value_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__290_4;
}
static void cont__290_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 675: ... &node.node::text_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, frame->slots[3] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__290_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._CHARACTER_SYMBOL;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__290_6;
}
static void cont__290_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 668: $STRING_CHARACTER
  // 669:   alt
  // 670:     "@@;"
  // 671:     sequence
  // 672:       CHARACTER_SYMBOL
  // 673:       modify_node
  // 674:         : (&node)
  // 675:           push &node.node::text_of node::value_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5082bfe;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__290_8;
}
static void cont__290_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING_CHARACTER, arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__291_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__291_9;
}
static void entry__291_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 682: ... node::text_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__291_2;
}
static void cont__291_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 682: ... node::text_of(node) != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__291_3;
}
static void cont__291_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 682: ... node::text_of(node) != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__291_4;
}
static void cont__291_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 682: ... :
  // 683:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__291_5, 0);
  // 682: if node::text_of(node) != "":
  // 683:   push &node.arguments_of node(.arguments_of undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__291_8;
}
static void entry__291_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 683: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__291_6;
}
static void cont__291_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 683: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 683: push &node.arguments_of node(.arguments_of undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__291_7;
}
static void cont__291_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 683: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__291_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 684: !node.node::text_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, empty_string);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__291_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 685: ... arguments_span(EXPRESSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__291_10;
}
static void cont__291_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 685: interleaved(arguments_span(EXPRESSION) compiler::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__291_11;
}
static void cont__291_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 686: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__291_12;
}
static void cont__291_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 677: $STRING_INSERTION
  // 678:   sequence
  // 679:     "@@("
  // 680:     modify_node
  // 681:       : (&node)
  // 682:         if node::text_of(node) != "":
  // 683:           push &node.arguments_of node(.arguments_of undefined)
  // 684:         !node.node::text_of ""
  // 685:     interleaved(arguments_span(EXPRESSION) compiler::WHITESPACE)
  // 686:     expect(')')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5082bed;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__291_14;
}
static void cont__291_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING_INSERTION, arguments->slots[0]);
  // 688: $CHECK_INSERTIONS
  // 689:   modify_node
  // 690:     : (&node)
  // 691:       if length_of(arguments_of(node)) > 0:
  // 692:         if node::text_of(node) != "":
  // 693:           push &node.arguments_of node(.arguments_of undefined)
  // 694:         !node
  // 695:           function_call
  // 696:             .functor_of std_identifier("string")
  // 697:             .arguments_of arguments_of(node)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__292_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__292_20;
}
static void entry__292_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 691: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__292_2;
}
static void cont__292_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 691: ... length_of(arguments_of(node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__292_3;
}
static void cont__292_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 691: ... length_of(arguments_of(node)) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__292_4;
}
static void cont__292_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 691: ... :
  // 692:   if node::text_of(node) != "":
  // 693:     push &node.arguments_of node(.arguments_of undefined)
  // 694:   !node
  // 695:     function_call
  // 696:       .functor_of std_identifier("string")
  // 697:       .arguments_of arguments_of(node)
  // 698:       .is_a_string_template true
  // 699:       .fragment_of fragment_of(node)
  // 700:       .source_position_of source_position_of(node)
  // ...
  frame->slots[4] /* temp__4 */ = create_closure(entry__292_5, 0);
  // 691: if length_of(arguments_of(node)) > 0:
  // 692:   if node::text_of(node) != "":
  // 693:     push &node.arguments_of node(.arguments_of undefined)
  // 694:   !node
  // 695:     function_call
  // 696:       .functor_of std_identifier("string")
  // 697:       .arguments_of arguments_of(node)
  // 698:       .is_a_string_template true
  // 699:       .fragment_of fragment_of(node)
  // 700:       .source_position_of source_position_of(node)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__292_19;
}
static void entry__292_5(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 692: ... node::text_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__292_6;
}
static void cont__292_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 692: ... node::text_of(node) != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__292_7;
}
static void cont__292_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 692: ... node::text_of(node) != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__292_8;
}
static void cont__292_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 692: ... :
  // 693:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__292_9, 0);
  // 692: if node::text_of(node) != "":
  // 693:   push &node.arguments_of node(.arguments_of undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__292_12;
}
static void entry__292_9(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 693: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__292_10;
}
static void cont__292_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 693: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 693: push &node.arguments_of node(.arguments_of undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__292_11;
}
static void cont__292_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 693: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__292_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 696: ... std_identifier("string")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7c1f540901cb12b0;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__292_14;
}
static void cont__292_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 697: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__292_15;
}
static void cont__292_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 699: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__292_16;
}
static void cont__292_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 700: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__292_17;
}
static void cont__292_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 701: ... end_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__292_18;
}
static void cont__292_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 694: !node
  // 695:   function_call
  // 696:     .functor_of std_identifier("string")
  // 697:     .arguments_of arguments_of(node)
  // 698:     .is_a_string_template true
  // 699:     .fragment_of fragment_of(node)
  // 700:     .source_position_of source_position_of(node)
  // 701:     .end_position_of end_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__is_a_string_template, get__true());
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[4] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[5] /* temp__5 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__292_19(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__292_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._CHECK_INSERTIONS, arguments->slots[0]);
  // 706: not_followed_by(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__293_1;
}
static void cont__293_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 707: set_node(string_literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__string_literal();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__293_2;
}
static void cont__293_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 709: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__293_3;
}
static void cont__293_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 709: ... alt(STRING_INSERTION STRING_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STRING_INSERTION;
  arguments->slots[1] = var._STRING_CHARACTER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__293_4;
}
static void cont__293_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 709: ... not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__293_5;
}
static void cont__293_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 709: some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__293_6;
}
static void cont__293_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 710: expect('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__293_7;
}
static void cont__293_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 703: $STRING # This code has an astonishing capability to flatten template expressions!
  // 704:   sequence
  // 705:     '@quot;'
  // 706:     not_followed_by(indent_marker)
  // 707:     set_node(string_literal)
  // 708:     STORE_POSITION_MINUS_1
  // 709:     some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
  // 710:     expect('@quot;')
  // 711:     STORE_END_POSITION
  // 712:     CHECK_INSERTIONS
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = var._STORE_POSITION_MINUS_1;
  arguments->slots[4] = frame->slots[2] /* temp__3 */;
  arguments->slots[5] = frame->slots[6] /* temp__7 */;
  arguments->slots[6] = var._STORE_END_POSITION;
  arguments->slots[7] = var._CHECK_INSERTIONS;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__293_8;
}
static void cont__293_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING, arguments->slots[0]);
  // 717: ... '@@', OUTDENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__294_1;
}
static void cont__294_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 717: followed_by('@@', OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__294_2;
}
static void cont__294_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 718: '@@', NEWLINE, STRING_LINE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = var._NEWLINE;
  arguments->slots[2] = var._STRING_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__294_3;
}
static void cont__294_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 719: STRING_INSERTION, STRING_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STRING_INSERTION;
  arguments->slots[1] = var._STRING_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__294_4;
}
static void cont__294_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 720: STRING_CHARACTER, STRING_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STRING_CHARACTER;
  arguments->slots[1] = var._STRING_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__294_5;
}
static void cont__294_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  arguments->slots[2] = frame->slots[4] /* temp__5 */;
  arguments->slots[3] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__294_6;
}
static void cont__294_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 714: $STRING_LINE
  // 715:   optional
  // 716:     alt
  // 717:       followed_by('@@', OUTDENT)
  // 718:       '@@', NEWLINE, STRING_LINE
  // 719:       STRING_INSERTION, STRING_LINE
  // 720:       STRING_CHARACTER, STRING_LINE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__294_7;
}
static void cont__294_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING_LINE, arguments->slots[0]);
  // 722: $ADD_LINE_END
  // 723:   modify_node
  // 724:     : (&node)
  // 725:       append &node.node::text_of line_end_specifier_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__295_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__295_5;
}
static void entry__295_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 725: ... node.node::text_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__295_2;
}
static void cont__295_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 725: ... line_end_specifier_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__line_end_specifier_of();
  func = myself->type;
  frame->cont = cont__295_3;
}
static void cont__295_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 725: append &node.node::text_of line_end_specifier_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__295_4;
}
static void cont__295_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 725: ... &node.node::text_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, frame->slots[3] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__295_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ADD_LINE_END, arguments->slots[0]);
  // 730: set_node(multi_line_string)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__multi_line_string();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__296_1;
}
static void cont__296_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 734: ... NEWLINE, ADD_LINE_END, STRING_LINE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  arguments->slots[1] = var._ADD_LINE_END;
  arguments->slots[2] = var._STRING_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__296_2;
}
static void cont__296_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 734: some(NEWLINE, ADD_LINE_END, STRING_LINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__296_3;
}
static void cont__296_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 735: ... '@@', OUTDENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__296_4;
}
static void cont__296_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 735: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__296_5;
}
static void cont__296_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 735: ... expect(outdent_marker), ADD_LINE_END
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  arguments->slots[1] = var._ADD_LINE_END;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__296_6;
}
static void cont__296_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 735: alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__296_7;
}
static void cont__296_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 727: $MULTI_LINE_STRING
  // 728:   sequence
  // 729:     '@quot;'
  // 730:     set_node(multi_line_string)
  // 731:     STORE_POSITION_MINUS_1
  // 732:     INDENT
  // 733:     STRING_LINE
  // 734:     some(NEWLINE, ADD_LINE_END, STRING_LINE)
  // 735:     alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
  // 736:     STORE_END_POSITION
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = var._INDENT;
  arguments->slots[4] = var._STRING_LINE;
  arguments->slots[5] = frame->slots[1] /* temp__2 */;
  arguments->slots[6] = frame->slots[3] /* temp__4 */;
  arguments->slots[7] = var._STORE_END_POSITION;
  arguments->slots[8] = var._CHECK_INSERTIONS;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__296_8;
}
static void cont__296_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_STRING, arguments->slots[0]);
  // 739: ... not_followed_by(LETTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__297_1;
}
static void cont__297_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 739: ... set_node(unique_item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__unique_item();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__297_2;
}
static void cont__297_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 739: $UNIQUE_ITEM '.', not_followed_by(LETTER), set_node(unique_item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__297_3;
}
static void cont__297_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._UNIQUE_ITEM, arguments->slots[0]);
  // 744: ... syntax_error("expression expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__55df65a142fc9536;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__298_2;
}
static void cont__298_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 744: ... alt(EXPRESSION BODY syntax_error("expression expected"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = var._BODY;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__298_3;
}
static void cont__298_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 744: inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._inline;
  func = myself->type;
  frame->cont = cont__298_4;
}
static void cont__298_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 745: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__298_5;
}
static void cont__298_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 741: $PARENTHESED_EXPRESSION
  // 742:   sequence
  // 743:     '('
  // 744:     inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  // 745:     expect(')')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__298_6;
}
static void cont__298_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARENTHESED_EXPRESSION, arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__299_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__299_10;
}
static void entry__299_1(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 755: ... std_identifier("key_value_pair")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__64d512703527e2ab;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__299_3;
}
static void cont__299_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 756: ... std_identifier("true")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2a0aedcb5dc87d5c;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__299_5;
}
static void cont__299_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 756: ... list(node std_identifier("true"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__299_6;
}
static void cont__299_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 757: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__299_7;
}
static void cont__299_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 758: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__299_8;
}
static void cont__299_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__7 */ = arguments->slots[0];
  // 758: ... source_position_of(node)+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__7 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__299_9;
}
static void cont__299_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__6 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 753: ->
  // 754:   function_call
  // 755:     .functor_of std_identifier("key_value_pair")
  // 756:     .arguments_of list(node std_identifier("true"))
  // 757:     .fragment_of fragment_of(node)
  // 758:     .source_position_of source_position_of(node)+2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__299_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 747: $OPTION
  // 748:   sequence
  // 749:     "--"
  // 750:     IDENTIFIER
  // 751:     modify_node
  // 752:       : (node)
  // 753:         ->
  // 754:           function_call
  // 755:             .functor_of std_identifier("key_value_pair")
  // 756:             .arguments_of list(node std_identifier("true"))
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602be8;
  arguments->slots[1] = var._IDENTIFIER;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__299_12;
}
static void cont__299_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OPTION, arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__300_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__300_5;
}
static void entry__300_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 770: ... operator_symbol(.name_of "-")
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, string__578a5af303e9ccc);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 771: ... list(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__300_2;
}
static void cont__300_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 772: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__300_3;
}
static void cont__300_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 773: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__300_4;
}
static void cont__300_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[4] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[5] /* temp__5 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 768: ->
  // 769:   function_call
  // 770:     .functor_of operator_symbol(.name_of "-")
  // 771:     .arguments_of list(node)
  // 772:     .fragment_of fragment_of(node)
  // 773:     .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__300_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 761: $NEGATION
  // 762:   sequence
  // 763:     '-'
  // 764:     STORE_POSITION_MINUS_1
  // 765:     OPERAND
  // 766:     modify_node
  // 767:       : (node)
  // 768:         ->
  // 769:           function_call
  // 770:             .functor_of operator_symbol(.name_of "-")
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = var._STORE_POSITION_MINUS_1;
  arguments->slots[2] = var._OPERAND;
  arguments->slots[3] = frame->slots[0] /* temp__1 */;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__300_6;
}
static void cont__300_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEGATION, arguments->slots[0]);
  // 776: $SIMPLE_OPERAND
  // 777:   alt
  // 778:     NUMBER
  // 779:     CHARACTER
  // 780:     STRING
  // 781:     UNIQUE_ITEM
  // 782:     PARENTHESED_EXPRESSION
  // 783:     OPTION
  // 784:     NEGATION
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = var._NUMBER;
  arguments->slots[1] = var._CHARACTER;
  arguments->slots[2] = var._STRING;
  arguments->slots[3] = var._UNIQUE_ITEM;
  arguments->slots[4] = var._PARENTHESED_EXPRESSION;
  arguments->slots[5] = var._OPTION;
  arguments->slots[6] = var._NEGATION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__301_1;
}
static void cont__301_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMPLE_OPERAND, arguments->slots[0]);
  // 786: ... some(ATTRIBUTE_ACCESS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._ATTRIBUTE_ACCESS;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__302_1;
}
static void cont__302_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 786: ... SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMPLE_OPERAND;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__302_2;
}
static void cont__302_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 786: $OPERAND alt(IDENTIFIER_OR_FUNCTION_CALL SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__302_3;
}
static void cont__302_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OPERAND, arguments->slots[0]);
  // 788: $INFIX_OPERATOR_SYMBOL
  // 789:   alt
  // 790:     '*'
  // 791:     '/'
  // 792:     '+'
  // 793:     '-'
  // 794:     "<<"
  // 795:     "<="
  // 796:     "<"
  // 797:     ">>"
  // ...
  argument_count = 19;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__47;
  arguments->slots[2] = character__43;
  arguments->slots[3] = character__45;
  arguments->slots[4] = string__2d7981f4e6e82bf9;
  arguments->slots[5] = string__2d7981f4e6e82bf8;
  arguments->slots[6] = string__578a5af303e9cdd;
  arguments->slots[7] = string__2d7981f4e6f82bfb;
  arguments->slots[8] = string__2d7981f4e6f82bf8;
  arguments->slots[9] = string__578a5af303e9cdf;
  arguments->slots[10] = string__2d7981f4e6382be3;
  arguments->slots[11] = character__38;
  arguments->slots[12] = character__94;
  arguments->slots[13] = string__2d7981f4e4e82bb9;
  arguments->slots[14] = character__124;
  arguments->slots[15] = string__2d7981f4e6e02bf8;
  arguments->slots[16] = character__61;
  arguments->slots[17] = string__2d7981f4e6002bf8;
  arguments->slots[18] = string__2d7981f4e6782beb;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__303_1;
}
static void cont__303_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INFIX_OPERATOR_SYMBOL, arguments->slots[0]);
  // 811: ... multi_capture(operators_of INFIX_OPERATOR_SYMBOL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = var._INFIX_OPERATOR_SYMBOL;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__304_1;
}
static void cont__304_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 810: $SYMBOLIC_OPERATOR
  // 811:   infix_operator(multi_capture(operators_of INFIX_OPERATOR_SYMBOL))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__304_2;
}
static void cont__304_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SYMBOLIC_OPERATOR, arguments->slots[0]);
  // 813: ... multi_capture(operators_of ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__305_1;
}
static void cont__305_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 813: $COMMA_OPERATOR multi_capture(operators_of ','), compiler::WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__305_2;
}
static void cont__305_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._COMMA_OPERATOR, arguments->slots[0]);
  // 819: multi_span(operators_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = var._IDENTIFIER;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__306_1;
}
static void cont__306_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 821: expect(compiler::WHITESPACE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__306_2;
}
static void cont__306_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 815: $NAMED_OPERATOR
  // 816:   sequence
  // 817:     compiler::WHITESPACE
  // 818:     '.'
  // 819:     multi_span(operators_of IDENTIFIER)
  // 820:     '.'
  // 821:     expect(compiler::WHITESPACE)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = character__46;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = character__46;
  arguments->slots[4] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__306_3;
}
static void cont__306_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMED_OPERATOR, arguments->slots[0]);
  // 825: alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._SYMBOLIC_OPERATOR;
  arguments->slots[1] = var._COMMA_OPERATOR;
  arguments->slots[2] = var._NAMED_OPERATOR;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__307_1;
}
static void cont__307_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__307_2;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__307_14;
}
static void entry__307_2(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // node: 0
  // operator_precedence: 1
  // lowest_precedence: 2
  frame->slots[1] /* operator_precedence */ = create_future();
  frame->slots[2] /* lowest_precedence */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 828: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__307_3;
}
static void cont__307_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 828: ... operators_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__operators_of();
  func = myself->type;
  frame->cont = cont__307_4;
}
static void cont__307_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 828: ... operators_of(node)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__307_5;
}
static void cont__307_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 828: $operator_precedence precedence(operators_of(node)(-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__precedence();
  func = myself->type;
  frame->cont = cont__307_6;
}
static void cont__307_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* operator_precedence */, arguments->slots[0]);
  // 829: $lowest_precedence lowest_precedence_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__lowest_precedence_of();
  func = myself->type;
  frame->cont = cont__307_7;
}
static void cont__307_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* lowest_precedence */, arguments->slots[0]);
  // 832: lowest_precedence.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* lowest_precedence */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__307_8;
}
static void cont__307_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 833: operator_precedence < lowest_precedence
  frame->slots[5] /* temp__3 */ = create_closure(entry__307_9, 0);
  // 831: ||
  // 832:   lowest_precedence.is_undefined
  // 833:   operator_precedence < lowest_precedence
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__307_11;
}
static void entry__307_9(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // operator_precedence: 0
  // lowest_precedence: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* operator_precedence */
  frame->slots[1] = myself->closure.frame->slots[2]; /* lowest_precedence */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 833: operator_precedence < lowest_precedence
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* operator_precedence */;
  arguments->slots[1] = frame->slots[1] /* lowest_precedence */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__307_10;
}
static void cont__307_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 833: operator_precedence < lowest_precedence
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__307_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 834: :
  // 835:   !node.lowest_precedence_of operator_precedence
  frame->slots[6] /* temp__4 */ = create_closure(entry__307_12, 0);
  // 830: if
  // 831:   ||
  // 832:     lowest_precedence.is_undefined
  // 833:     operator_precedence < lowest_precedence
  // 834:   :
  // 835:     !node.lowest_precedence_of operator_precedence
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__307_13;
}
static void entry__307_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // node: 0
  // operator_precedence: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* operator_precedence */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 835: !node.lowest_precedence_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__lowest_precedence_of, frame->slots[1] /* operator_precedence */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__307_13(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__307_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 823: $INFIX_OPERATOR
  // 824:   sequence
  // 825:     alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
  // 826:     modify_node
  // 827:       : (&node)
  // 828:         $operator_precedence precedence(operators_of(node)(-1))
  // 829:         $lowest_precedence lowest_precedence_of(node)
  // 830:         if
  // 831:           ||
  // 832:             lowest_precedence.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__307_15;
}
static void cont__307_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INFIX_OPERATOR, arguments->slots[0]);
  // 837: $EXTEND_EXPRESSION
  // 838:   modify_node
  // 839:     : (&node)
  // 840:       $parent parent_of(node)
  // 841:       $arguments arguments_of(node)
  // 842:       $n length_of(arguments)
  // 843:       if
  // 844:         n == 1:
  // 845:           !node arguments(1)
  // 846:         :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__308_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__308_62;
}
static void entry__308_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // node: 0
  // parent: 1
  // arguments: 2
  // n: 3
  frame->slots[1] /* parent */ = create_future();
  frame->slots[2] /* arguments */ = create_future();
  frame->slots[3] /* n */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 840: $parent parent_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parent_of();
  func = myself->type;
  frame->cont = cont__308_2;
}
static void cont__308_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* parent */, arguments->slots[0]);
  // 841: $arguments arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__308_3;
}
static void cont__308_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* arguments */, arguments->slots[0]);
  // 842: $n length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__308_4;
}
static void cont__308_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 844: n == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__308_5;
}
static void cont__308_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 844: ... :
  // 845:   !node arguments(1)
  frame->slots[5] /* temp__2 */ = create_closure(entry__308_6, 0);
  // 846: :
  // 847:   $operators operators_of(node)
  // 848:   $$operand_stack list(arguments(1))
  // 849:   $$operator_stack list(operators(1))
  // 850:   
  // 851:   $update_stack: ($right next_operator)
  // 852:     $next_prec
  // 853:       if
  // 854:         next_operator.is_defined
  // 855:         -> precedence(next_operator)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__308_8, 0);
  // 843: if
  // 844:   n == 1:
  // 845:     !node arguments(1)
  // 846:   :
  // 847:     $operators operators_of(node)
  // 848:     $$operand_stack list(arguments(1))
  // 849:     $$operator_stack list(operators(1))
  // 850:     
  // 851:     $update_stack: ($right next_operator)
  // 852:       $next_prec
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__308_56;
}
static void entry__308_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // node: 0
  // arguments: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[2]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 845: !node arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__308_7;
}
static void cont__308_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* node */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__308_8(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // node: 0
  // arguments: 1
  // n: 2
  // operators: 3
  // operand_stack: 4
  // operator_stack: 5
  // update_stack: 6
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[2]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[3]; /* n */
  frame->slots[6] /* update_stack */ = create_future();
  frame->slots[3] /* operators */ = create_future();
  frame->slots[4] /* operand_stack */ = create_cell();
  frame->slots[5] /* operator_stack */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 851: ... : ($right next_operator)
  // 852:   $next_prec
  // 853:     if
  // 854:       next_operator.is_defined
  // 855:       -> precedence(next_operator)
  // 856:       -> 0
  // 857:   
  // 858:   do: (-> break)
  // 859:     forever:
  // 860:       $operator peek(operator_stack)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__308_9, 2);
  // 851: $update_stack: ($right next_operator)
  // 852:   $next_prec
  // 853:     if
  // 854:       next_operator.is_defined
  // 855:       -> precedence(next_operator)
  // 856:       -> 0
  // 857:   
  // 858:   do: (-> break)
  // 859:     forever:
  // 860:       $operator peek(operator_stack)
  // ...
  initialize_future(frame->slots[6] /* update_stack */, frame->slots[7] /* temp__1 */);
  // 847: $operators operators_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__operators_of();
  func = myself->type;
  frame->cont = cont__308_42;
}
static void entry__308_9(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // right: 0
  // next_operator: 1
  // operator_stack: 2
  // operand_stack: 3
  // next_prec: 4
  frame->slots[2] = myself->closure.frame->slots[5]; /* operator_stack */
  frame->slots[3] = myself->closure.frame->slots[4]; /* operand_stack */
  frame->slots[4] /* next_prec */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* right */ = create_cell_with_contents(arguments->slots[0]);
  // 854: next_operator.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* next_operator */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__308_10;
}
static void cont__308_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 855: -> precedence(next_operator)
  frame->slots[6] /* temp__2 */ = create_closure(entry__308_11, 0);
  // 852: $next_prec
  // 853:   if
  // 854:     next_operator.is_defined
  // 855:     -> precedence(next_operator)
  // 856:     -> 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = func__308_13;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__308_14;
}
static void entry__308_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // next_operator: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* next_operator */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 855: ... precedence(next_operator)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* next_operator */;
  result_count = 1;
  myself = get__precedence();
  func = myself->type;
  frame->cont = cont__308_12;
}
static void cont__308_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 855: -> precedence(next_operator)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__308_13(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 856: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* next_prec */, arguments->slots[0]);
  // 858: ... : (-> break)
  // 859:   forever:
  // 860:     $operator peek(operator_stack)
  // 861:     $prec precedence(operator)
  // 862:     if next_prec > prec break
  // 863:     if next_prec == prec && is_right_associative(prec) break
  // 864:     
  // 865:     $functor
  // 866:       if
  // 867:         operator.is_a_string
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__308_15, 0);
  // 858: do: (-> break)
  // 859:   forever:
  // 860:     $operator peek(operator_stack)
  // 861:     $prec precedence(operator)
  // 862:     if next_prec > prec break
  // 863:     if next_prec == prec && is_right_associative(prec) break
  // 864:     
  // 865:     $functor
  // 866:       if
  // 867:         operator.is_a_string
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__308_39;
}
static void entry__308_15(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // break: 0
  // operator_stack: 1
  // next_prec: 2
  // operand_stack: 3
  // right: 4
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[2]; /* operator_stack */
  frame->slots[2] = myself->closure.frame->slots[4]; /* next_prec */
  frame->slots[3] = myself->closure.frame->slots[3]; /* operand_stack */
  frame->slots[4] = myself->closure.frame->slots[0]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 859: ... :
  // 860:   $operator peek(operator_stack)
  // 861:   $prec precedence(operator)
  // 862:   if next_prec > prec break
  // 863:   if next_prec == prec && is_right_associative(prec) break
  // 864:   
  // 865:   $functor
  // 866:     if
  // 867:       operator.is_a_string
  // 868:       -> operator_symbol(.name_of operator)
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__308_16, 0);
  // 859: forever:
  // 860:   $operator peek(operator_stack)
  // 861:   $prec precedence(operator)
  // 862:   if next_prec > prec break
  // 863:   if next_prec == prec && is_right_associative(prec) break
  // 864:   
  // 865:   $functor
  // 866:     if
  // 867:       operator.is_a_string
  // 868:       -> operator_symbol(.name_of operator)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__308_38;
}
static void entry__308_16(void) {
  allocate_initialized_frame_gc(5, 14);
  // slot allocations:
  // operator_stack: 0
  // next_prec: 1
  // break: 2
  // operand_stack: 3
  // right: 4
  // operator: 5
  // prec: 6
  // functor: 7
  // left: 8
  // dummy: 9
  frame->slots[0] = myself->closure.frame->slots[1]; /* operator_stack */
  frame->slots[1] = myself->closure.frame->slots[2]; /* next_prec */
  frame->slots[2] = myself->closure.frame->slots[0]; /* break */
  frame->slots[3] = myself->closure.frame->slots[3]; /* operand_stack */
  frame->slots[4] = myself->closure.frame->slots[4]; /* right */
  frame->slots[5] /* operator */ = create_future();
  frame->slots[6] /* prec */ = create_future();
  frame->slots[7] /* functor */ = create_future();
  frame->slots[8] /* left */ = create_future();
  frame->slots[9] /* dummy */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 860: $operator peek(operator_stack)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* operator_stack */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__308_17;
}
static void cont__308_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* operator */, arguments->slots[0]);
  // 861: $prec precedence(operator)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* operator */;
  result_count = 1;
  myself = get__precedence();
  func = myself->type;
  frame->cont = cont__308_18;
}
static void cont__308_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* prec */, arguments->slots[0]);
  // 862: ... next_prec > prec
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* prec */;
  arguments->slots[1] = frame->slots[1] /* next_prec */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__308_19;
}
static void cont__308_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 862: if next_prec > prec break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__308_20;
}
static void cont__308_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 863: ... next_prec == prec
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* next_prec */;
  arguments->slots[1] = frame->slots[6] /* prec */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__308_21;
}
static void cont__308_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 863: ... is_right_associative(prec)
  frame->slots[12] /* temp__3 */ = create_closure(entry__308_22, 0);
  // 863: ... next_prec == prec && is_right_associative(prec)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__2 */;
  arguments->slots[1] = frame->slots[12] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__308_24;
}
static void entry__308_22(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // prec: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* prec */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 863: ... is_right_associative(prec)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* prec */;
  result_count = 1;
  myself = var._is_right_associative;
  func = myself->type;
  frame->cont = cont__308_23;
}
static void cont__308_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 863: ... is_right_associative(prec)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 863: if next_prec == prec && is_right_associative(prec) break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__308_25;
}
static void cont__308_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 867: operator.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* operator */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__308_26;
}
static void cont__308_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 868: -> operator_symbol(.name_of operator)
  frame->slots[11] /* temp__2 */ = create_closure(entry__308_27, 0);
  // 869: -> operator
  frame->slots[12] /* temp__3 */ = create_closure(entry__308_28, 0);
  // 865: $functor
  // 866:   if
  // 867:     operator.is_a_string
  // 868:     -> operator_symbol(.name_of operator)
  // 869:     -> operator
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  arguments->slots[2] = frame->slots[12] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__308_29;
}
static void entry__308_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // operator: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* operator */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 868: ... operator_symbol(.name_of operator)
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[0] /* operator */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 868: -> operator_symbol(.name_of operator)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__308_28(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // operator: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* operator */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 869: -> operator
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* operator */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* functor */, arguments->slots[0]);
  // 871: $left pop(&operand_stack)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* operand_stack */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__308_30;
}
static void cont__308_30(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* operand_stack */ = arguments->slots[0];
  initialize_future(frame->slots[8] /* left */, arguments->slots[1]);
  // 875: ... list(left right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* left */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* right */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__308_31;
}
static void cont__308_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 877: ... fragment_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* left */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__308_32;
}
static void cont__308_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 878: ... source_position_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* left */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__308_33;
}
static void cont__308_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 879: ... end_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* right */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__308_34;
}
static void cont__308_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__4 */ = arguments->slots[0];
  // 872: !right
  // 873:   function_call
  // 874:     .functor_of functor
  // 875:     .arguments_of list(left right)
  // 876:     .is_in_infix_notation true
  // 877:     .fragment_of fragment_of(left)
  // 878:     .source_position_of source_position_of(left)
  // 879:     .end_position_of end_position_of(right)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[7] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[10] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__is_in_infix_notation, get__true());
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[11] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[12] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[13] /* temp__4 */);
    ((CELL *)frame->slots[4])->contents /* right */ = temp;

  }
  // 880: pop &operator_stack $_dummy
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* operator_stack */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__308_35;
}
static void cont__308_35(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* operator_stack */ = arguments->slots[0];
  initialize_future(frame->slots[9] /* dummy */, arguments->slots[1]);
  // 881: ... length_of(operator_stack)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* operator_stack */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__308_36;
}
static void cont__308_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 881: ... length_of(operator_stack) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__308_37;
}
static void cont__308_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 881: if length_of(operator_stack) == 0 break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__308_38(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__308_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 882: push &operand_stack right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* operand_stack */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__308_40;
}
static void cont__308_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* operand_stack */ = arguments->slots[0];
  // 883: push &operator_stack next_operator
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* operator_stack */;
  arguments->slots[1] = frame->slots[1] /* next_operator */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__308_41;
}
static void cont__308_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* operator_stack */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* operators */, arguments->slots[0]);
  // 848: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__308_43;
}
static void cont__308_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 848: $$operand_stack list(arguments(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__308_44;
}
static void cont__308_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* operand_stack */ = arguments->slots[0];
  // 849: ... operators(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* operators */;
  func = myself->type;
  frame->cont = cont__308_45;
}
static void cont__308_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 849: $$operator_stack list(operators(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__308_46;
}
static void cont__308_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* operator_stack */ = arguments->slots[0];
  // 885: ... : (i)
  // 886:   update_stack
  // 887:     arguments(i)
  // 888:     if
  // 889:       i < n
  // 890:       -> operators(i)
  // 891:       -> undefined
  frame->slots[7] /* temp__1 */ = create_closure(entry__308_47, 1);
  // 885: from_to 2 n: (i)
  // 886:   update_stack
  // 887:     arguments(i)
  // 888:     if
  // 889:       i < n
  // 890:       -> operators(i)
  // 891:       -> undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[2] /* n */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__308_54;
}
static void entry__308_47(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // i: 0
  // update_stack: 1
  // arguments: 2
  // n: 3
  // operators: 4
  frame->slots[1] = myself->closure.frame->slots[6]; /* update_stack */
  frame->slots[2] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[3] = myself->closure.frame->slots[2]; /* n */
  frame->slots[4] = myself->closure.frame->slots[3]; /* operators */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 887: arguments(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[2] /* arguments */;
  func = myself->type;
  frame->cont = cont__308_48;
}
static void cont__308_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 889: i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__308_49;
}
static void cont__308_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 890: -> operators(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__308_50, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = func__308_52;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__308_53;
}
static void entry__308_50(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // operators: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* operators */
  frame->slots[1] = myself->closure.frame->slots[0]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 890: ... operators(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* i */;
  result_count = 1;
  myself = frame->slots[0] /* operators */;
  func = myself->type;
  frame->cont = cont__308_51;
}
static void cont__308_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 890: -> operators(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__308_52(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 891: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 886: update_stack
  // 887:   arguments(i)
  // 888:   if
  // 889:     i < n
  // 890:     -> operators(i)
  // 891:     -> undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* update_stack */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__308_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 892: !node peek(operand_stack)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* operand_stack */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__308_55;
}
static void cont__308_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* node */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 893: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__308_57;
}
static void cont__308_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 893: ... :
  // 894:   !node parent(.arguments_of push(arguments_of(parent) node))
  frame->slots[5] /* temp__2 */ = create_closure(entry__308_58, 0);
  // 893: if parent.is_defined:
  // 894:   !node parent(.arguments_of push(arguments_of(parent) node))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__308_61;
}
static void entry__308_58(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // node: 0
  // parent: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* parent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 894: ... arguments_of(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parent */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__308_59;
}
static void cont__308_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 894: ... push(arguments_of(parent) node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__308_60;
}
static void cont__308_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 894: !node parent(.arguments_of push(arguments_of(parent) node))
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* parent */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_61(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXTEND_EXPRESSION, arguments->slots[0]);
  // 898: set_node(expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__expression();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__309_1;
}
static void cont__309_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 899: arguments_span(OPERAND)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__309_2;
}
static void cont__309_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 900: ... arguments_span(OPERAND)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__309_3;
}
static void cont__309_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 900: ... INFIX_OPERATOR, arguments_span(OPERAND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._INFIX_OPERATOR;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__309_4;
}
static void cont__309_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 900: some(INFIX_OPERATOR, arguments_span(OPERAND))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__309_5;
}
static void cont__309_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 902: ... multi_capture(operators_of '=')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__309_6;
}
static void cont__309_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 902: infix_operator(multi_capture(operators_of '='))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__309_7;
}
static void cont__309_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 902: infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = var._LINE_END_EXPRESSION;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__309_8;
}
static void cont__309_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__309_9;
}
static void cont__309_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 896: $EXPRESSION
  // 897:   sequence
  // 898:     set_node(expression)
  // 899:     arguments_span(OPERAND)
  // 900:     some(INFIX_OPERATOR, arguments_span(OPERAND))
  // 901:     optional
  // 902:       infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  // 903:     EXTEND_EXPRESSION
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  arguments->slots[3] = frame->slots[5] /* temp__6 */;
  arguments->slots[4] = var._EXTEND_EXPRESSION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__309_10;
}
static void cont__309_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXPRESSION, arguments->slots[0]);
  // 905: ... span(identifier_of DEFINE_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = var._DEFINE_IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__310_1;
}
static void cont__310_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 905: $DEFINED_VARIABLE expect(span(identifier_of DEFINE_IDENTIFIER) "identifier")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__395c5a51a203e553;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__310_3;
}
static void cont__310_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINED_VARIABLE, arguments->slots[0]);
  // 908: ... set_field(is_used_as_a_polymorphic_function true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_used_as_a_polymorphic_function();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__311_1;
}
static void cont__311_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 907: $NAME_OF_POLYMORPHIC
  // 908:   IDENTIFIER, set_field(is_used_as_a_polymorphic_function true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__311_2;
}
static void cont__311_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAME_OF_POLYMORPHIC, arguments->slots[0]);
  // 918: set_field(attribute_kind_of ATTRIBUTE_KIND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_kind_of();
  arguments->slots[1] = get__ATTRIBUTE_KIND();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__312_1;
}
static void cont__312_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 919: span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__312_2;
}
static void cont__312_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__312_3;
}
static void cont__312_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 922: followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__312_4;
}
static void cont__312_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 923: set_field(attribute_kind_of METHOD_KIND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_kind_of();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__312_5;
}
static void cont__312_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  arguments->slots[2] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__312_6;
}
static void cont__312_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 926: set_field(attribute_kind_of METHOD_KIND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_kind_of();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__312_7;
}
static void cont__312_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 927: span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__312_8;
}
static void cont__312_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[10] /* temp__11 */;
  arguments->slots[2] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__312_9;
}
static void cont__312_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__312_10;
}
static void cont__312_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__312_11;
}
static void cont__312_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__312_12;
}
static void cont__312_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 910: $DEFINED_VARIABLE_OR_ATTRIBUTE
  // 911:   sequence
  // 912:     DEFINED_VARIABLE
  // 913:     optional
  // 914:       sequence
  // 915:         alt
  // 916:           sequence
  // 917:             '.'
  // 918:             set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 919:             span(attribute_of NAME_OF_POLYMORPHIC)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._DEFINED_VARIABLE;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__312_13;
}
static void cont__312_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINED_VARIABLE_OR_ATTRIBUTE, arguments->slots[0]);
  // 930: ... set_node(define_static_single)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_single();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__313_1;
}
static void cont__313_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 929: $DEFINE_STATIC_SINGLE
  // 930:   '$', set_node(define_static_single), DEFINED_VARIABLE_OR_ATTRIBUTE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__36;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._DEFINED_VARIABLE_OR_ATTRIBUTE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__313_2;
}
static void cont__313_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_STATIC_SINGLE, arguments->slots[0]);
  // 932: ... set_node(define_static_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__314_1;
}
static void cont__314_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 932: $DEFINE_STATIC_MULTI "$$", set_node(define_static_multi), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6282be1;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._DEFINED_VARIABLE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__314_3;
}
static void cont__314_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_STATIC_MULTI, arguments->slots[0]);
  // 933: ... set_node(define_dynamic_single)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_dynamic_single();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__315_1;
}
static void cont__315_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 933: $DEFINE_DYNAMIC_SINGLE '%', set_node(define_dynamic_single), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__37;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._DEFINED_VARIABLE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__315_2;
}
static void cont__315_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_DYNAMIC_SINGLE, arguments->slots[0]);
  // 934: ... set_node(define_dynamic_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_dynamic_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__316_1;
}
static void cont__316_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 934: $DEFINE_DYNAMIC_MULTI "%%", set_node(define_dynamic_multi), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6202be0;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._DEFINED_VARIABLE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__316_3;
}
static void cont__316_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_DYNAMIC_MULTI, arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__317_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__317_5;
}
static void entry__317_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 943: ... list(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__317_2;
}
static void cont__317_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 946: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__317_3;
}
static void cont__317_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 947: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__317_4;
}
static void cont__317_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 941: !node
  // 942:   function_call
  // 943:     .arguments_of list(node)
  // 944:     .is_an_attribute_access true
  // 945:     .is_a_method_definition true
  // 946:     .fragment_of fragment_of(node)
  // 947:     .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[1] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__is_an_attribute_access, get__true());
    set_attribute_value(temp->attributes, poly_idx__is_a_method_definition, get__true());
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__317_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 948: ... followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__317_6;
}
static void cont__317_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 948: ... span(functor_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__317_7;
}
static void cont__317_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 948: alt(followed_by(':') span(functor_of NAME_OF_POLYMORPHIC))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__317_8;
}
static void cont__317_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 936: $METHOD_DEFINITION
  // 937:   sequence
  // 938:     '/'
  // 939:     modify_node
  // 940:       : (&node)
  // 941:         !node
  // 942:           function_call
  // 943:             .arguments_of list(node)
  // 944:             .is_an_attribute_access true
  // 945:             .is_a_method_definition true
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__317_9;
}
static void cont__317_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._METHOD_DEFINITION, arguments->slots[0]);
  // 955: optional(METHOD_DEFINITION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._METHOD_DEFINITION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__318_1;
}
static void cont__318_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 956: set_field(is_a_destination true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_a_destination();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__318_2;
}
static void cont__318_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 951: $ASSIGN
  // 952:   sequence
  // 953:     '!'
  // 954:     READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 955:     optional(METHOD_DEFINITION)
  // 956:     set_field(is_a_destination true)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__33;
  arguments->slots[1] = var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__318_3;
}
static void cont__318_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ASSIGN, arguments->slots[0]);
  // 958: $DESTINATION
  // 959:   alt
  // 960:     DEFINE_STATIC_MULTI
  // 961:     DEFINE_STATIC_SINGLE
  // 962:     DEFINE_DYNAMIC_MULTI
  // 963:     DEFINE_DYNAMIC_SINGLE
  // 964:     ASSIGN
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_STATIC_MULTI;
  arguments->slots[1] = var._DEFINE_STATIC_SINGLE;
  arguments->slots[2] = var._DEFINE_DYNAMIC_MULTI;
  arguments->slots[3] = var._DEFINE_DYNAMIC_SINGLE;
  arguments->slots[4] = var._ASSIGN;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__319_1;
}
static void cont__319_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DESTINATION, arguments->slots[0]);
  // 969: set_node(backquoted)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__backquoted();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__320_1;
}
static void cont__320_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 970: ... alt(OPERAND DESTINATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  arguments->slots[1] = var._DESTINATION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__320_2;
}
static void cont__320_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 970: ... span(expression_of alt(OPERAND DESTINATION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__expression_of();
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__320_3;
}
static void cont__320_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 970: capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__text_of();
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__320_4;
}
static void cont__320_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 966: $BACKQUOTED
  // 967:   sequence
  // 968:     '`'
  // 969:     set_node(backquoted)
  // 970:     capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__96;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__320_5;
}
static void cont__320_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BACKQUOTED, arguments->slots[0]);
  // 974: ... set_field(is_an_optional_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_an_optional_item();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__321_1;
}
static void cont__321_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 974: '?', set_field(is_an_optional_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__63;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__321_2;
}
static void cont__321_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 975: ... set_field(is_an_expanded_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_an_expanded_item();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__321_3;
}
static void cont__321_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 975: '*', set_field(is_an_expanded_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__321_4;
}
static void cont__321_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 972: $EXPANSION
  // 973:   alt
  // 974:     '?', set_field(is_an_optional_item true)
  // 975:     '*', set_field(is_an_expanded_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__321_5;
}
static void cont__321_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXPANSION, arguments->slots[0]);
  // 977: ... optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__322_1;
}
static void cont__322_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 977: $OUTPUT_ARGUMENT DESTINATION, optional(EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._DESTINATION;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__322_2;
}
static void cont__322_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OUTPUT_ARGUMENT, arguments->slots[0]);
  // 983: set_field(is_a_destination true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_a_destination();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__323_1;
}
static void cont__323_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 984: set_field(is_an_input_output_argument true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_an_input_output_argument();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__323_2;
}
static void cont__323_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 985: optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__323_3;
}
static void cont__323_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 979: $INPUT_OUTPUT_ARGUMENT
  // 980:   sequence
  // 981:     '&'
  // 982:     READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 983:     set_field(is_a_destination true)
  // 984:     set_field(is_an_input_output_argument true)
  // 985:     optional(EXPANSION)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = character__38;
  arguments->slots[1] = var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__323_4;
}
static void cont__323_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INPUT_OUTPUT_ARGUMENT, arguments->slots[0]);
  // 987: ... alt(EXPRESSION BODY MULTI_LINE_STRING)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = var._BODY;
  arguments->slots[2] = var._MULTI_LINE_STRING;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__324_1;
}
static void cont__324_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 987: $INPUT_ARGUMENT arguments_span(alt(EXPRESSION BODY MULTI_LINE_STRING))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__324_2;
}
static void cont__324_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INPUT_ARGUMENT, arguments->slots[0]);
  // 992: span(identifier_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__325_1;
}
static void cont__325_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 993: ... compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = var._LINE_END_REMARK_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__325_2;
}
static void cont__325_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 993: optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__325_3;
}
static void cont__325_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 995: ... CHECK_ARGUMENTS("attribute value" 0 1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__5b01b0908c396eea;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__1;
  result_count = 1;
  myself = var._CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__325_5;
}
static void cont__325_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 995: INDENTED_ARGUMENTS, CHECK_ARGUMENTS("attribute value" 0 1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._INDENTED_ARGUMENTS;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__325_6;
}
static void cont__325_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 996: SEPARATOR, INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SEPARATOR;
  arguments->slots[1] = var._INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__325_7;
}
static void cont__325_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__325_8;
}
static void cont__325_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 989: $VALUE_ARGUMENT
  // 990:   sequence
  // 991:     STORE_POSITION_MINUS_1
  // 992:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 993:     optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
  // 994:     alt
  // 995:       INDENTED_ARGUMENTS, CHECK_ARGUMENTS("attribute value" 0 1)
  // 996:       SEPARATOR, INPUT_ARGUMENT
  // 997:     STORE_END_POSITION
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._STORE_POSITION_MINUS_1;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__325_9;
}
static void cont__325_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._VALUE_ARGUMENT, arguments->slots[0]);
  // 1004: ... set_node(attribute_value_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_value_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__326_1;
}
static void cont__326_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1004: ... sequence(set_node(attribute_value_pair) VALUE_ARGUMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = var._VALUE_ARGUMENT;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__326_2;
}
static void cont__326_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1004: arguments_span(sequence(set_node(attribute_value_pair) VALUE_ARGUMENT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__326_3;
}
static void cont__326_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__326_4;
}
static void cont__326_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1007: followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__326_5;
}
static void cont__326_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1010: set_node(attribute_function_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__326_6;
}
static void cont__326_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1012: arguments_span(BODY)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._BODY;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__326_7;
}
static void cont__326_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__10 */;
  arguments->slots[1] = var._STORE_POSITION_MINUS_1;
  arguments->slots[2] = frame->slots[10] /* temp__11 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__326_8;
}
static void cont__326_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__326_9;
}
static void cont__326_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  arguments->slots[2] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__326_10;
}
static void cont__326_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1018: ... set_node(attribute_function_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__326_11;
}
static void cont__326_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 1018: sequence(set_node(attribute_function_pair) VALUE_ARGUMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__15 */;
  arguments->slots[1] = var._VALUE_ARGUMENT;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__326_12;
}
static void cont__326_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__14 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__326_13;
}
static void cont__326_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = var._STORE_POSITION_MINUS_1;
  arguments->slots[2] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__326_14;
}
static void cont__326_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__326_15;
}
static void cont__326_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  //  999: $ATTRIBUTE_VALUE_PAIR
  // 1000:   sequence
  // 1001:     alt
  // 1002:       sequence
  // 1003:         '.'
  // 1004:         arguments_span(sequence(set_node(attribute_value_pair) VALUE_ARGUMENT))
  // 1005:       sequence
  // 1006:         '/'
  // 1007:         followed_by(':')
  // 1008:         arguments_span
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__326_16;
}
static void cont__326_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ATTRIBUTE_VALUE_PAIR, arguments->slots[0]);
  // 1022: ... arguments_span(OPERAND)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__327_1;
}
static void cont__327_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1022: sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INFIX_OPERATOR;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = var._OPERATORS_AND_OPERANDS;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__327_2;
}
static void cont__327_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1020: $OPERATORS_AND_OPERANDS
  // 1021:   alt
  // 1022:     sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
  // 1023:     EXTEND_EXPRESSION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._EXTEND_EXPRESSION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__327_3;
}
static void cont__327_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OPERATORS_AND_OPERANDS, arguments->slots[0]);
  // 1027: set_node(operator_symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__operator_symbol();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__328_1;
}
static void cont__328_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1029: capture(name_of INFIX_OPERATOR_SYMBOL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = var._INFIX_OPERATOR_SYMBOL;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__328_2;
}
static void cont__328_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__328_3;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__328_6;
}
static void entry__328_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1035: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__328_4;
}
static void cont__328_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1036: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__328_5;
}
static void cont__328_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* node */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1032: ->
  // 1033:   function_call
  // 1034:     .functor_of node
  // 1035:     .fragment_of fragment_of(node)
  // 1036:     .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__328_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1037: ... compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = var._LINE_END_REMARK_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__328_7;
}
static void cont__328_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1037: optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__328_8;
}
static void cont__328_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1040: CHECK_ARGUMENTS("multi line expression" 0)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__137554cc13b7640e;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = var._CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__328_10;
}
static void cont__328_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__328_11;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__328_46;
}
static void entry__328_11(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // node: 0
  // stream: 1
  // return: 2
  // arguments: 3
  frame->slots[2] /* return */ = create_continuation_with_exit(exit__328_11);
  frame->slots[3] /* arguments */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1048: $$arguments arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__328_12;
}
static void cont__328_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* arguments */ = arguments->slots[0];
  // 1049: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__328_13;
}
static void cont__328_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1049: ... length_of(arguments) < 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__328_14;
}
static void cont__328_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1049: ... :
  // 1050:   ParseError stream "too few arguments in multi-line expression"
  frame->slots[6] /* temp__3 */ = create_closure(entry__328_15, 0);
  // 1049: if length_of(arguments) < 2:
  // 1050:   ParseError stream "too few arguments in multi-line expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__328_17;
}
static void entry__328_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1050: ParseError stream "too few arguments in multi-line expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__733ccdbfc49ced05;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__328_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1051: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__328_18;
}
static void cont__328_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1051: ... length_of(arguments) > 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__328_19;
}
static void cont__328_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1051: ... :
  // 1052:   $functor functor_of(node)
  // 1053:   if
  // 1054:     precedence(name_of(functor)).is_left_associative:
  // 1055:       forever:
  // 1056:         !node
  // 1057:           function_call
  // 1058:             .functor_of functor
  // 1059:             .arguments_of range(arguments 1 2)
  // 1060:         if length_of(arguments) == 2 return
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__328_20, 0);
  // 1051: if length_of(arguments) > 2:
  // 1052:   $functor functor_of(node)
  // 1053:   if
  // 1054:     precedence(name_of(functor)).is_left_associative:
  // 1055:       forever:
  // 1056:         !node
  // 1057:           function_call
  // 1058:             .functor_of functor
  // 1059:             .arguments_of range(arguments 1 2)
  // 1060:         if length_of(arguments) == 2 return
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__328_45;
}
static void entry__328_35(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // node: 0
  // functor: 1
  // arguments: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* functor */
  frame->slots[2] = myself->closure.frame->slots[2]; /* arguments */
  frame->slots[3] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1067: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__328_36;
}
static void cont__328_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1067: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__328_37;
}
static void cont__328_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 1067: ... range(arguments -2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__328_38;
}
static void cont__328_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1064: !node
  // 1065:   function_call
  // 1066:     .functor_of functor
  // 1067:     .arguments_of range(arguments -2 -1)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1068: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__328_39;
}
static void cont__328_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1068: ... length_of(arguments) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__328_40;
}
static void cont__328_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1068: if length_of(arguments) == 2 return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__328_41;
}
static void cont__328_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1069: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__328_42;
}
static void cont__328_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1069: ... range(arguments 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__328_43;
}
static void cont__328_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1069: !arguments push(range(arguments 1 -3) node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__328_44;
}
static void cont__328_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__328_26(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // node: 0
  // functor: 1
  // arguments: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* functor */
  frame->slots[2] = myself->closure.frame->slots[2]; /* arguments */
  frame->slots[3] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1059: ... range(arguments 1 2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = number__2;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__328_27;
}
static void cont__328_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1056: !node
  // 1057:   function_call
  // 1058:     .functor_of functor
  // 1059:     .arguments_of range(arguments 1 2)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1060: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__328_28;
}
static void cont__328_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1060: ... length_of(arguments) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__328_29;
}
static void cont__328_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1060: if length_of(arguments) == 2 return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__328_30;
}
static void cont__328_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1061: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__328_31;
}
static void cont__328_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1061: ... range(arguments 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__328_32;
}
static void cont__328_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1061: !arguments put(range(arguments 3 -1) node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__328_33;
}
static void cont__328_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__328_25(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // node: 0
  // functor: 1
  // arguments: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[3]; /* functor */
  frame->slots[2] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1055: ... :
  // 1056:   !node
  // 1057:     function_call
  // 1058:       .functor_of functor
  // 1059:       .arguments_of range(arguments 1 2)
  // 1060:   if length_of(arguments) == 2 return
  // 1061:   !arguments put(range(arguments 3 -1) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__328_26, 0);
  // 1055: forever:
  // 1056:   !node
  // 1057:     function_call
  // 1058:       .functor_of functor
  // 1059:       .arguments_of range(arguments 1 2)
  // 1060:   if length_of(arguments) == 2 return
  // 1061:   !arguments put(range(arguments 3 -1) node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__328_34(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // node: 0
  // functor: 1
  // arguments: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[3]; /* functor */
  frame->slots[2] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1063: ... :
  // 1064:   !node
  // 1065:     function_call
  // 1066:       .functor_of functor
  // 1067:       .arguments_of range(arguments -2 -1)
  // 1068:   if length_of(arguments) == 2 return
  // 1069:   !arguments push(range(arguments 1 -3) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__328_35, 0);
  // 1063: forever:
  // 1064:   !node
  // 1065:     function_call
  // 1066:       .functor_of functor
  // 1067:       .arguments_of range(arguments -2 -1)
  // 1068:   if length_of(arguments) == 2 return
  // 1069:   !arguments push(range(arguments 1 -3) node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__328_20(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // node: 0
  // arguments: 1
  // return: 2
  // functor: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[3]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* functor */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1052: $functor functor_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__328_21;
}
static void cont__328_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* functor */, arguments->slots[0]);
  // 1054: ... name_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* functor */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__328_22;
}
static void cont__328_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 1054: precedence(name_of(functor))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__precedence();
  func = myself->type;
  frame->cont = cont__328_23;
}
static void cont__328_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1054: precedence(name_of(functor)).is_left_associative
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_left_associative();
  func = myself->type;
  frame->cont = cont__328_24;
}
static void cont__328_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1054: ... :
  // 1055:   forever:
  // 1056:     !node
  // 1057:       function_call
  // 1058:         .functor_of functor
  // 1059:         .arguments_of range(arguments 1 2)
  // 1060:     if length_of(arguments) == 2 return
  // 1061:     !arguments put(range(arguments 3 -1) node)
  frame->slots[7] /* temp__4 */ = create_closure(entry__328_25, 0);
  // 1062: :
  // 1063:   forever:
  // 1064:     !node
  // 1065:       function_call
  // 1066:         .functor_of functor
  // 1067:         .arguments_of range(arguments -2 -1)
  // 1068:     if length_of(arguments) == 2 return
  // 1069:     !arguments push(range(arguments 1 -3) node)
  frame->slots[8] /* temp__5 */ = create_closure(entry__328_34, 0);
  // 1053: if
  // 1054:   precedence(name_of(functor)).is_left_associative:
  // 1055:     forever:
  // 1056:       !node
  // 1057:         function_call
  // 1058:           .functor_of functor
  // 1059:           .arguments_of range(arguments 1 2)
  // 1060:       if length_of(arguments) == 2 return
  // 1061:       !arguments put(range(arguments 3 -1) node)
  // 1062:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__328_45(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__328_11(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  func = continuation_type_function;
}
static void cont__328_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1025: $MULTI_LINE_EXPRESSION
  // 1026:   sequence
  // 1027:     set_node(operator_symbol)
  // 1028:     STORE_POSITION
  // 1029:     capture(name_of INFIX_OPERATOR_SYMBOL)
  // 1030:     modify_node
  // 1031:       : (node)
  // 1032:         ->
  // 1033:           function_call
  // 1034:             .functor_of node
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[2] /* temp__3 */;
  arguments->slots[4] = frame->slots[3] /* temp__4 */;
  arguments->slots[5] = var._INDENTED_ARGUMENTS;
  arguments->slots[6] = var._STORE_END_POSITION;
  arguments->slots[7] = frame->slots[5] /* temp__6 */;
  arguments->slots[8] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__328_47;
}
static void cont__328_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_EXPRESSION, arguments->slots[0]);
  // 1076: set_node(define_static_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__329_1;
}
static void cont__329_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1077: set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__IN_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__329_2;
}
static void cont__329_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__36;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__329_3;
}
static void cont__329_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1080: set_node(define_static_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__329_4;
}
static void cont__329_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1081: set_field(parameter_kind_of OUT_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__OUT_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__329_5;
}
static void cont__329_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__33;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__329_6;
}
static void cont__329_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1084: set_node(define_static_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__329_7;
}
static void cont__329_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1085: set_field(parameter_kind_of IN_OUT_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__IN_OUT_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__329_8;
}
static void cont__329_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__38;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__329_9;
}
static void cont__329_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1086: set_node(define_static_single)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_single();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__329_10;
}
static void cont__329_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1086: ... set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__IN_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__329_11;
}
static void cont__329_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1086: set_node(define_static_single), set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__12 */;
  arguments->slots[1] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__329_12;
}
static void cont__329_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[7] /* temp__8 */;
  arguments->slots[3] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__329_13;
}
static void cont__329_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1071: $PARAMETER_MODE
  // 1072:   optional
  // 1073:     alt
  // 1074:       sequence
  // 1075:         '$'
  // 1076:         set_node(define_static_multi)
  // 1077:         set_field(parameter_kind_of IN_PARAMETER)
  // 1078:       sequence
  // 1079:         '!'
  // 1080:         set_node(define_static_multi)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__329_14;
}
static void cont__329_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_MODE, arguments->slots[0]);
  // 1093: infix_operator('=')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__61;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__330_1;
}
static void cont__330_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1094: set_field(is_an_optional_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_an_optional_item();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__330_2;
}
static void cont__330_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1095: span(default_value_of EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__default_value_of();
  arguments->slots[1] = var._EXPRESSION;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__330_3;
}
static void cont__330_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  arguments->slots[2] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__330_4;
}
static void cont__330_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1096: ... set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__MYSELF_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__330_5;
}
static void cont__330_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1096: '^', set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__94;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__330_6;
}
static void cont__330_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__330_7;
}
static void cont__330_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1088: $PARAMETER_COUNT_OR_MYSELF
  // 1089:   optional
  // 1090:     alt
  // 1091:       EXPANSION
  // 1092:       sequence
  // 1093:         infix_operator('=')
  // 1094:         set_field(is_an_optional_item true)
  // 1095:         span(default_value_of EXPRESSION)
  // 1096:       '^', set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__330_8;
}
static void cont__330_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_COUNT_OR_MYSELF, arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__331_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__331_2;
}
static void entry__331_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1103: !node.is_not_used
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_not_used, get__true());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__331_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1098: $NOT_USED
  // 1099:   sequence
  // 1100:     '_'
  // 1101:     modify_node
  // 1102:       : (&node)
  // 1103:         !node.is_not_used true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__95;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__331_3;
}
static void cont__331_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NOT_USED, arguments->slots[0]);
  // 1109: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__332_1;
}
static void cont__332_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1111: optional(NOT_USED)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NOT_USED;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__332_2;
}
static void cont__332_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1112: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__332_3;
}
static void cont__332_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__332_4;
}
static void cont__332_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1105: $PARAMETER_NAME
  // 1106:   span
  // 1107:     identifier_of
  // 1108:     sequence
  // 1109:       set_node(identifier)
  // 1110:       STORE_POSITION
  // 1111:       optional(NOT_USED)
  // 1112:       capture(name_of NAME)
  // 1113:       STORE_END_POSITION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__332_5;
}
static void cont__332_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_NAME, arguments->slots[0]);
  // 1115: $PARAMETER PARAMETER_MODE, PARAMETER_NAME, PARAMETER_COUNT_OR_MYSELF
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_MODE;
  arguments->slots[1] = var._PARAMETER_NAME;
  arguments->slots[2] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__333_1;
}
static void cont__333_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER, arguments->slots[0]);
  // 1118: ... optional(LINE_END_REMARK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__334_1;
}
static void cont__334_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1118: ... INDENT, REMARK, OUTDENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = var._REMARK;
  arguments->slots[2] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__334_2;
}
static void cont__334_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1118: ... optional(INDENT, REMARK, OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__334_3;
}
static void cont__334_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1117: $MULTI_LINE_PARAMETER
  // 1118:   PARAMETER, optional(LINE_END_REMARK), optional(INDENT, REMARK, OUTDENT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__334_4;
}
static void cont__334_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_PARAMETER, arguments->slots[0]);
  // 1124: set_node(define_static_single)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_single();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__335_1;
}
static void cont__335_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1125: set_field(parameter_kind_of CONTINUATION_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__335_2;
}
static void cont__335_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1120: $CONTINUATION
  // 1121:   sequence
  // 1122:     "->"
  // 1123:     compiler::WHITESPACE
  // 1124:     set_node(define_static_single)
  // 1125:     set_field(parameter_kind_of CONTINUATION_PARAMETER)
  // 1126:     PARAMETER_NAME
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602bfb;
  arguments->slots[1] = var.compiler__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = var._PARAMETER_NAME;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__335_4;
}
static void cont__335_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._CONTINUATION, arguments->slots[0]);
  // 1129: ... optional(LINE_END_REMARK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__336_1;
}
static void cont__336_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1129: ... INDENT, REMARK, OUTDENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = var._REMARK;
  arguments->slots[2] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__336_2;
}
static void cont__336_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1129: ... optional(INDENT, REMARK, OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__336_3;
}
static void cont__336_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1128: $MULTI_LINE_CONTINUATION
  // 1129:   CONTINUATION, optional(LINE_END_REMARK), optional(INDENT, REMARK, OUTDENT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._CONTINUATION;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__336_4;
}
static void cont__336_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_CONTINUATION, arguments->slots[0]);
  // 1137: ... multi_span(parameters_of PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._PARAMETER;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__337_1;
}
static void cont__337_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1137: interleaved(multi_span(parameters_of PARAMETER) compiler::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__337_2;
}
static void cont__337_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1138: ... multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._CONTINUATION;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__337_3;
}
static void cont__337_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1138: ... compiler::WHITESPACE, multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__337_4;
}
static void cont__337_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1138: optional(compiler::WHITESPACE, multi_span(parameters_of CONTINUATION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__337_5;
}
static void cont__337_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__337_6;
}
static void cont__337_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1139: multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._CONTINUATION;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__337_7;
}
static void cont__337_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__337_8;
}
static void cont__337_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__337_9;
}
static void cont__337_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1140: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__337_10;
}
static void cont__337_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1131: $INLINE_PARAMETERS
  // 1132:   sequence
  // 1133:     '('
  // 1134:     optional
  // 1135:       alt
  // 1136:         sequence
  // 1137:           interleaved(multi_span(parameters_of PARAMETER) compiler::WHITESPACE)
  // 1138:           optional(compiler::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1139:         multi_span(parameters_of CONTINUATION)
  // 1140:     expect(')')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__337_11;
}
static void cont__337_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INLINE_PARAMETERS, arguments->slots[0]);
  // 1148: ... multi_span(parameters_of MULTI_LINE_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._MULTI_LINE_PARAMETER;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__338_1;
}
static void cont__338_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1148: interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._NEWLINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__338_2;
}
static void cont__338_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1149: ... multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._MULTI_LINE_CONTINUATION;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__338_3;
}
static void cont__338_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1149: ... NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__338_4;
}
static void cont__338_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1149: optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__338_5;
}
static void cont__338_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__338_6;
}
static void cont__338_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1150: multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._MULTI_LINE_CONTINUATION;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__338_7;
}
static void cont__338_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__338_8;
}
static void cont__338_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1151: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__338_9;
}
static void cont__338_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1152: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__338_10;
}
static void cont__338_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1153: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__338_11;
}
static void cont__338_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1142: $MULTI_LINE_PARAMETERS
  // 1143:   sequence
  // 1144:     '('
  // 1145:     INDENT
  // 1146:     alt
  // 1147:       sequence
  // 1148:         interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1149:         optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  // 1150:       multi_span(parameters_of MULTI_LINE_CONTINUATION)
  // 1151:     expect(outdent_marker)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = var._INDENT;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[8] /* temp__9 */;
  arguments->slots[4] = frame->slots[9] /* temp__10 */;
  arguments->slots[5] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__338_12;
}
static void cont__338_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_PARAMETERS, arguments->slots[0]);
  // 1158: set_node(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__body();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__339_1;
}
static void cont__339_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1162: optional(LINE_END_REMARK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__339_2;
}
static void cont__339_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1164: ... multi_span(statements_of REMARK_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = var._REMARK_STATEMENT;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__339_3;
}
static void cont__339_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1164: ... multi_span(statements_of REMARK_STATEMENT), NEWLINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__339_4;
}
static void cont__339_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1164: some(multi_span(statements_of REMARK_STATEMENT), NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__339_5;
}
static void cont__339_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__339_6;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__339_13;
}
static void entry__339_6(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1171: ... statements_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__339_7;
}
static void cont__339_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1171: ... : (remark_statement)
  // 1172:   append &node.remark_lines_of remark_lines_of(remark_statement)
  frame->slots[2] /* temp__2 */ = create_closure(entry__339_8, 1);
  // 1171: for_each statements_of(node): (remark_statement)
  // 1172:   append &node.remark_lines_of remark_lines_of(remark_statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__339_12;
}
static void entry__339_8(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // remark_statement: 0
  // node: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1172: ... node.remark_lines_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__339_9;
}
static void cont__339_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1172: ... remark_lines_of(remark_statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__339_10;
}
static void cont__339_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1172: append &node.remark_lines_of remark_lines_of(remark_statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__339_11;
}
static void cont__339_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1172: ... &node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[4] /* temp__3 */);
    ((CELL *)frame->slots[1])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__339_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1173: !node.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, get__empty_list());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__339_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._MULTI_LINE_PARAMETERS;
  arguments->slots[1] = var._NEWLINE;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__339_14;
}
static void cont__339_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__339_15;
}
static void cont__339_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1174: optional(NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__339_16;
}
static void cont__339_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1176: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__339_17;
}
static void cont__339_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._INDENT;
  arguments->slots[2] = frame->slots[4] /* temp__5 */;
  arguments->slots[3] = frame->slots[7] /* temp__8 */;
  arguments->slots[4] = frame->slots[10] /* temp__11 */;
  arguments->slots[5] = var._STATEMENTS;
  arguments->slots[6] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__339_18;
}
static void cont__339_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1178: ... compiler::WHITESPACE, INLINE_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = var._INLINE_PARAMETERS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__339_19;
}
static void cont__339_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 1178: optional(compiler::WHITESPACE, INLINE_PARAMETERS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__15 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__339_20;
}
static void cont__339_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 1179: optional(LINE_END_REMARK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__339_21;
}
static void cont__339_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 1181: ... multi_span(statements_of STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = var._STATEMENT;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__339_22;
}
static void cont__339_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__19 */ = arguments->slots[0];
  // 1181: compiler::WHITESPACE, multi_span(statements_of STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[18] /* temp__19 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__339_23;
}
static void cont__339_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 1182: ... optional(NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__339_24;
}
static void cont__339_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__21 */ = arguments->slots[0];
  // 1182: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__339_25;
}
static void cont__339_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__22 */ = arguments->slots[0];
  // 1182: sequence(INDENT optional(NEWLINES) STATEMENTS expect(outdent_marker))
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[20] /* temp__21 */;
  arguments->slots[2] = var._STATEMENTS;
  arguments->slots[3] = frame->slots[21] /* temp__22 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__339_26;
}
static void cont__339_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__20 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__18 */;
  arguments->slots[1] = frame->slots[19] /* temp__20 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__339_27;
}
static void cont__339_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__14 */;
  arguments->slots[1] = frame->slots[15] /* temp__16 */;
  arguments->slots[2] = frame->slots[16] /* temp__17 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__339_28;
}
static void cont__339_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__339_29;
}
static void cont__339_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1155: $COMPLETE_BODY
  // 1156:   sequence
  // 1157:     ':'
  // 1158:     set_node(body)
  // 1159:     STORE_POSITION_MINUS_1
  // 1160:     alt
  // 1161:       sequence
  // 1162:         optional(LINE_END_REMARK)
  // 1163:         INDENT
  // 1164:         some(multi_span(statements_of REMARK_STATEMENT), NEWLINES)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = character__58;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__339_30;
}
static void cont__339_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._COMPLETE_BODY, arguments->slots[0]);
  // 1187: followed_by("->")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602bfb;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__340_1;
}
static void cont__340_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1188: set_node(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__body();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__340_2;
}
static void cont__340_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1190: multi_span(statements_of RETURN_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = var._RETURN_STATEMENT;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__340_3;
}
static void cont__340_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1185: $RETURN_EXPRESSION
  // 1186:   sequence
  // 1187:     followed_by("->")
  // 1188:     set_node(body)
  // 1189:     STORE_POSITION
  // 1190:     multi_span(statements_of RETURN_STATEMENT)
  // 1191:     STORE_END_POSITION
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = var._STORE_POSITION;
  arguments->slots[3] = frame->slots[2] /* temp__3 */;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__340_4;
}
static void cont__340_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RETURN_EXPRESSION, arguments->slots[0]);
  // 1193: $BODY alt(COMPLETE_BODY RETURN_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._COMPLETE_BODY;
  arguments->slots[1] = var._RETURN_EXPRESSION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__341_1;
}
static void cont__341_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BODY, arguments->slots[0]);
  // 1198: set_node(c_body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__c_body();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__342_1;
}
static void cont__342_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1200: expect(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__342_2;
}
static void cont__342_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1201: ... not_followed_by(OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OUTDENT;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__342_3;
}
static void cont__342_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1201: ... not_followed_by(OUTDENT), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__342_4;
}
static void cont__342_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1201: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__342_5;
}
static void cont__342_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1201: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__source_of();
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__342_6;
}
static void cont__342_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1202: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__342_7;
}
static void cont__342_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1203: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__342_8;
}
static void cont__342_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1204: expect('}')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__125;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__342_9;
}
static void cont__342_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1195: $C_BODY
  // 1196:   sequence
  // 1197:     '{'
  // 1198:     set_node(c_body)
  // 1199:     STORE_POSITION_MINUS_1
  // 1200:     expect(indent_marker)
  // 1201:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  // 1202:     expect(outdent_marker)
  // 1203:     expect(newline)
  // 1204:     expect('}')
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__123;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = frame->slots[2] /* temp__3 */;
  arguments->slots[5] = frame->slots[6] /* temp__7 */;
  arguments->slots[6] = frame->slots[7] /* temp__8 */;
  arguments->slots[7] = frame->slots[8] /* temp__9 */;
  arguments->slots[8] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__342_10;
}
static void cont__342_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_BODY, arguments->slots[0]);
  // 1207: ... alt(BODY C_BODY MULTI_LINE_STRING)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._BODY;
  arguments->slots[1] = var._C_BODY;
  arguments->slots[2] = var._MULTI_LINE_STRING;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__343_1;
}
static void cont__343_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1207: $LINE_END_EXPRESSION arguments_span(alt(BODY C_BODY MULTI_LINE_STRING))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__343_2;
}
static void cont__343_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINE_END_EXPRESSION, arguments->slots[0]);
  // 1208: ... set_node(polymorphic_function)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__polymorphic_function();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__344_1;
}
static void cont__344_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1208: $POLYMORPHIC_FUNCTION_WITHOUT_SETTER "()", set_node(polymorphic_function)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6482bec;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__344_3;
}
static void cont__344_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER, arguments->slots[0]);
  // 1211: ... set_node(polymorphic_function_with_setter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__polymorphic_function_with_setter();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__345_1;
}
static void cont__345_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1210: $POLYMORPHIC_FUNCTION_WITH_SETTER
  // 1211:   "(!)", set_node(polymorphic_function_with_setter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa732415f216be5;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__345_3;
}
static void cont__345_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._POLYMORPHIC_FUNCTION_WITH_SETTER, arguments->slots[0]);
  // 1213: $POLYMORPHIC_FUNCTION
  // 1214:   alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER;
  arguments->slots[1] = var._POLYMORPHIC_FUNCTION_WITH_SETTER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__346_1;
}
static void cont__346_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._POLYMORPHIC_FUNCTION, arguments->slots[0]);
  // 1216: $FUNCTOR span(functor_of IDENTIFIER_OR_FUNCTION_CALL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._IDENTIFIER_OR_FUNCTION_CALL;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__347_1;
}
static void cont__347_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FUNCTOR, arguments->slots[0]);
  // 1220: ... span(result_count_of EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__result_count_of();
  arguments->slots[1] = var._EXPRESSION;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__348_1;
}
static void cont__348_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1220: ".(", span(result_count_of EXPRESSION), ')'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6782bed;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = character__41;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__348_3;
}
static void cont__348_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1221: ... span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__continuation_of();
  arguments->slots[1] = var._IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__348_4;
}
static void cont__348_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1221: '/', span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__348_5;
}
static void cont__348_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1218: $RESULT_COUNT_OR_CONTINUATION
  // 1219:   alt
  // 1220:     ".(", span(result_count_of EXPRESSION), ')'
  // 1221:     '/', span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__348_6;
}
static void cont__348_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RESULT_COUNT_OR_CONTINUATION, arguments->slots[0]);
  // 1228: ... optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__349_1;
}
static void cont__349_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1228: EXPRESSION, optional(EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__349_2;
}
static void cont__349_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1231: ... optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__349_3;
}
static void cont__349_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1231: DESTINATION, optional(EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._DESTINATION;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__349_4;
}
static void cont__349_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  arguments->slots[2] = var._INPUT_OUTPUT_ARGUMENT;
  arguments->slots[3] = var._BACKQUOTED;
  arguments->slots[4] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__349_5;
}
static void cont__349_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__349_6;
}
static void cont__349_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1233: ... '@quot;', indent_marker
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = get__indent_marker();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__349_7;
}
static void cont__349_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1233: followed_by('@quot;', indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__349_8;
}
static void cont__349_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1234: followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__349_9;
}
static void cont__349_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1235: followed_by('#')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__35;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__349_10;
}
static void cont__349_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1236: followed_by('{')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__123;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__349_11;
}
static void cont__349_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1237: followed_by("->")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602bfb;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__349_12;
}
static void cont__349_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1238: syntax_error("argument expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__e1e3be9ec64af0e1;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__349_14;
}
static void cont__349_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1223: $ARGUMENT
  // 1224:   alt
  // 1225:     arguments_span
  // 1226:       alt
  // 1227:         POLYMORPHIC_FUNCTION
  // 1228:         EXPRESSION, optional(EXPANSION)
  // 1229:         INPUT_OUTPUT_ARGUMENT
  // 1230:         BACKQUOTED
  // 1231:         DESTINATION, optional(EXPANSION)
  // 1232:     ATTRIBUTE_VALUE_PAIR
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._ATTRIBUTE_VALUE_PAIR;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  arguments->slots[3] = frame->slots[8] /* temp__9 */;
  arguments->slots[4] = frame->slots[9] /* temp__10 */;
  arguments->slots[5] = frame->slots[10] /* temp__11 */;
  arguments->slots[6] = frame->slots[11] /* temp__12 */;
  arguments->slots[7] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__349_15;
}
static void cont__349_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENT, arguments->slots[0]);
  // 1242: ... compiler::WHITESPACE, ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = var._ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__350_1;
}
static void cont__350_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1242: some(compiler::WHITESPACE, ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__350_2;
}
static void cont__350_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1243: optional(LINE_END_REMARK_ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK_ARGUMENT;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__350_3;
}
static void cont__350_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1240: $FIRST_LINE_ARGUMENTS
  // 1241:   sequence
  // 1242:     some(compiler::WHITESPACE, ARGUMENT)
  // 1243:     optional(LINE_END_REMARK_ARGUMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__350_4;
}
static void cont__350_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FIRST_LINE_ARGUMENTS, arguments->slots[0]);
  // 1249: ... compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = var._LINE_END_REMARK_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__351_1;
}
static void cont__351_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1249: optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__351_2;
}
static void cont__351_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__351_3;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__351_26;
}
static void entry__351_3(void) {
  allocate_initialized_frame_gc(1, 9);
  // slot allocations:
  // node: 0
  // arguments: 1
  // functor: 2
  // argument: 3
  frame->slots[1] /* arguments */ = create_future();
  frame->slots[2] /* functor */ = create_future();
  frame->slots[3] /* argument */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1253: $arguments arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__351_4;
}
static void cont__351_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* arguments */, arguments->slots[0]);
  // 1254: $functor arguments(arguments_index)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__arguments_index();
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__351_5;
}
static void cont__351_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* functor */, arguments->slots[0]);
  // 1259: ... arguments_index+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__arguments_index();
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__351_6;
}
static void cont__351_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1259: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__351_7;
}
static void cont__351_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 1259: ... range(arguments arguments_index+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* arguments */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__351_8;
}
static void cont__351_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1260: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__351_9;
}
static void cont__351_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 1261: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__351_10;
}
static void cont__351_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 1256: $$argument
  // 1257:   function_call
  // 1258:     .functor_of functor
  // 1259:     .arguments_of range(arguments arguments_index+1 -1)
  // 1260:     .fragment_of fragment_of(node)
  // 1261:     .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[7] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[8] /* temp__5 */);
    ((CELL *)frame->slots[3])->contents /* argument */ = temp;

  }
  // 1263: check_arguments argument "function call"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* argument */;
  arguments->slots[1] = string__4456c807200257a4;
  result_count = 0;
  myself = var._check_arguments;
  func = myself->type;
  frame->cont = cont__351_11;
}
static void cont__351_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1265: arguments_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* argument */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__351_12;
}
static void cont__351_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1265: arguments_of(argument).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__351_13;
}
static void cont__351_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1265: ... :
  // 1266:   !argument functor_of(argument)
  // 1267:     # The "arguments" were just remarks!
  frame->slots[6] /* temp__3 */ = create_closure(entry__351_14, 0);
  // 1268: :
  // 1269:   unless
  // 1270:     do_pretty_print && all_of(arguments_of(argument) is_a_remark)
  // 1271:     :
  // 1272:       check_functor functor
  frame->slots[7] /* temp__4 */ = create_closure(entry__351_16, 0);
  // 1264: if
  // 1265:   arguments_of(argument).is_empty:
  // 1266:     !argument functor_of(argument)
  // 1267:       # The "arguments" were just remarks!
  // 1268:   :
  // 1269:     unless
  // 1270:       do_pretty_print && all_of(arguments_of(argument) is_a_remark)
  // 1271:       :
  // 1272:         check_functor functor
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__351_22;
}
static void entry__351_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1272: check_functor functor
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  result_count = frame->caller_result_count;
  myself = var._check_functor;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__351_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1266: !argument functor_of(argument)
  // 1267:   # The "arguments" were just remarks!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__351_15;
}
static void cont__351_15(void) {
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
static void entry__351_16(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // argument: 0
  // functor: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1270: ... all_of(arguments_of(argument) is_a_remark)
  frame->slots[3] /* temp__2 */ = create_closure(entry__351_17, 0);
  // 1270: do_pretty_print && all_of(arguments_of(argument) is_a_remark)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__351_20;
}
static void entry__351_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1270: ... arguments_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__351_18;
}
static void cont__351_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1270: ... all_of(arguments_of(argument) is_a_remark)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__is_a_remark();
  result_count = 1;
  myself = get__all_of();
  func = myself->type;
  frame->cont = cont__351_19;
}
static void cont__351_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1270: ... all_of(arguments_of(argument) is_a_remark)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__351_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1271: :
  // 1272:   check_functor functor
  frame->slots[4] /* temp__3 */ = create_closure(entry__351_21, 0);
  // 1269: unless
  // 1270:   do_pretty_print && all_of(arguments_of(argument) is_a_remark)
  // 1271:   :
  // 1272:     check_functor functor
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__351_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1276: ... arguments_index-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__arguments_index();
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__351_23;
}
static void cont__351_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 1276: ... range(arguments 1 arguments_index-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* arguments */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__351_24;
}
static void cont__351_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 1276: push(range(arguments 1 arguments_index-1) argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__351_25;
}
static void cont__351_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[5] /* temp__2 */);
    frame->slots[4] /* temp__1 */ = temp;

  }
  // 1273: ->
  // 1274:   node
  // 1275:     .arguments_of
  // 1276:       push(range(arguments 1 arguments_index-1) argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__351_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = var._INDENTED_ARGUMENTS;
  arguments->slots[2] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__351_27;
}
static void cont__351_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._store_arguments_index;
  func = myself->type;
  frame->cont = cont__351_28;
}
static void cont__351_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1245: $MULTI_LINE_FUNCTION_CALL
  // 1246:   sequence
  // 1247:     store_arguments_index
  // 1248:       sequence
  // 1249:         optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
  // 1250:         INDENTED_ARGUMENTS
  // 1251:         modify_node
  // 1252:           : (node)
  // 1253:             $arguments arguments_of(node)
  // 1254:             $functor arguments(arguments_index)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__351_29;
}
static void cont__351_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_FUNCTION_CALL, arguments->slots[0]);
  // 1282: arguments_span(MULTI_LINE_EXPRESSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._MULTI_LINE_EXPRESSION;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__352_1;
}
static void cont__352_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1290: ... some(PRINTABLE_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__PRINTABLE_CHARACTER();
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__352_2;
}
static void cont__352_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1290: ... compiler::WHITESPACE, HASHTAG, some(PRINTABLE_CHARACTER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = var._HASHTAG;
  arguments->slots[2] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__352_3;
}
static void cont__352_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1290: optional(compiler::WHITESPACE, HASHTAG, some(PRINTABLE_CHARACTER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__352_4;
}
static void cont__352_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  arguments->slots[1] = var._INDENT;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__352_5;
}
static void cont__352_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__352_6;
}
static void cont__352_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = var._MULTI_LINE_FUNCTION_CALL;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__352_7;
}
static void cont__352_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1294: ... compiler::WHITESPACE, ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = var._ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__352_8;
}
static void cont__352_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1294: some(compiler::WHITESPACE, ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__352_9;
}
static void cont__352_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1295: ... alt(LINE_END_REMARK_ARGUMENT LINE_END_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK_ARGUMENT;
  arguments->slots[1] = var._LINE_END_EXPRESSION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__352_10;
}
static void cont__352_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 1295: optional(alt(LINE_END_REMARK_ARGUMENT LINE_END_EXPRESSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__14 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__352_11;
}
static void cont__352_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__11 */;
  arguments->slots[1] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__352_12;
}
static void cont__352_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__352_13;
}
static void cont__352_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__352_14;
}
static void cont__352_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1279: $ARGUMENT_LINE
  // 1280:   alt
  // 1281:     LINE_END_EXPRESSION
  // 1282:     arguments_span(MULTI_LINE_EXPRESSION)
  // 1283:     REMARK_ARGUMENT
  // 1284:     sequence
  // 1285:       ARGUMENT
  // 1286:       alt
  // 1287:         sequence
  // 1288:           followed_by
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_EXPRESSION;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._REMARK_ARGUMENT;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__352_15;
}
static void cont__352_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENT_LINE, arguments->slots[0]);
  // 1300: arguments_span(BODY)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._BODY;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__353_1;
}
static void cont__353_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1302: interleaved(ARGUMENT compiler::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT;
  arguments->slots[1] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__353_2;
}
static void cont__353_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1303: ... arguments_span(BODY)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._BODY;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__353_3;
}
static void cont__353_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1303: optional(arguments_span(BODY))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__353_4;
}
static void cont__353_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__353_5;
}
static void cont__353_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__353_6;
}
static void cont__353_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1297: $INLINE_ARGUMENTS
  // 1298:   inline
  // 1299:     alt
  // 1300:       arguments_span(BODY)
  // 1301:       sequence
  // 1302:         interleaved(ARGUMENT compiler::WHITESPACE)
  // 1303:         optional(arguments_span(BODY))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = var._inline;
  func = myself->type;
  frame->cont = cont__353_7;
}
static void cont__353_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INLINE_ARGUMENTS, arguments->slots[0]);
  // 1306: ... some(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__354_1;
}
static void cont__354_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1306: ... interleaved(ARGUMENT_LINE NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_LINE;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__354_2;
}
static void cont__354_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1305: $INDENTED_ARGUMENTS
  // 1306:   sequence(INDENT some(newline) interleaved(ARGUMENT_LINE NEWLINES) OUTDENT)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = var._OUTDENT;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__354_3;
}
static void cont__354_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INDENTED_ARGUMENTS, arguments->slots[0]);
  // 1311: ... alt(LINE_END_EXPRESSION INDENTED_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_EXPRESSION;
  arguments->slots[1] = var._INDENTED_ARGUMENTS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__355_1;
}
static void cont__355_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1311: optional(alt(LINE_END_EXPRESSION INDENTED_ARGUMENTS))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__355_2;
}
static void cont__355_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1308: $ARGUMENTS
  // 1309:   sequence
  // 1310:     FIRST_LINE_ARGUMENTS
  // 1311:     optional(alt(LINE_END_EXPRESSION INDENTED_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._FIRST_LINE_ARGUMENTS;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__355_3;
}
static void cont__355_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENTS, arguments->slots[0]);
  // 1386: set_node(assignment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__assignment();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__360_1;
}
static void cont__360_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1388: arguments_span(OUTPUT_ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OUTPUT_ARGUMENT;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__360_2;
}
static void cont__360_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1391: CHECK_ARGUMENTS("assignment" 1 1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2f401958355b9795;
  arguments->slots[1] = number__1;
  arguments->slots[2] = number__1;
  result_count = 1;
  myself = var._CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__360_4;
}
static void cont__360_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__360_5;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__360_31;
}
static void entry__360_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1394: ... : (-> break)
  // 1395:   for_each_from_to arguments_of(node) 2 -1: (source)
  // 1396:     unless source.is_a_remark:
  // 1397:       if source.is_a_polymorphic_function_constant:
  // 1398:         $destination arguments_of(node)(1)
  // 1399:         unless
  // 1400:           &&
  // 1401:             destination.is_a_static_single_definition
  // 1402:             attribute_kind_of(destination) == NONE
  // 1403:           :
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__360_6, 0);
  // 1394: do: (-> break)
  // 1395:   for_each_from_to arguments_of(node) 2 -1: (source)
  // 1396:     unless source.is_a_remark:
  // 1397:       if source.is_a_polymorphic_function_constant:
  // 1398:         $destination arguments_of(node)(1)
  // 1399:         unless
  // 1400:           &&
  // 1401:             destination.is_a_static_single_definition
  // 1402:             attribute_kind_of(destination) == NONE
  // 1403:           :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__360_30;
}
static void entry__360_6(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // break: 0
  // node: 1
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1395: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__360_7;
}
static void cont__360_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1395: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__360_8;
}
static void cont__360_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1395: ... : (source)
  // 1396:   unless source.is_a_remark:
  // 1397:     if source.is_a_polymorphic_function_constant:
  // 1398:       $destination arguments_of(node)(1)
  // 1399:       unless
  // 1400:         &&
  // 1401:           destination.is_a_static_single_definition
  // 1402:           attribute_kind_of(destination) == NONE
  // 1403:         :
  // 1404:           SyntaxError node "
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__360_9, 1);
  // 1395: for_each_from_to arguments_of(node) 2 -1: (source)
  // 1396:   unless source.is_a_remark:
  // 1397:     if source.is_a_polymorphic_function_constant:
  // 1398:       $destination arguments_of(node)(1)
  // 1399:       unless
  // 1400:         &&
  // 1401:           destination.is_a_static_single_definition
  // 1402:           attribute_kind_of(destination) == NONE
  // 1403:         :
  // 1404:           SyntaxError node "
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_from_to();
  func = myself->type;
  frame->cont = cont__360_29;
}
static void entry__360_11(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // node: 1
  // break: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* node */
  frame->slots[2] = myself->closure.frame->slots[2]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1397: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__360_12;
}
static void cont__360_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1397: ... :
  // 1398:   $destination arguments_of(node)(1)
  // 1399:   unless
  // 1400:     &&
  // 1401:       destination.is_a_static_single_definition
  // 1402:       attribute_kind_of(destination) == NONE
  // 1403:     :
  // 1404:       SyntaxError node "
  // 1405:         invalid polymorphic function definition (destination @
  // 1406:         must be a single assignment static)@
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__360_13, 0);
  // 1397: if source.is_a_polymorphic_function_constant:
  // 1398:   $destination arguments_of(node)(1)
  // 1399:   unless
  // 1400:     &&
  // 1401:       destination.is_a_static_single_definition
  // 1402:       attribute_kind_of(destination) == NONE
  // 1403:     :
  // 1404:       SyntaxError node "
  // 1405:         invalid polymorphic function definition (destination @
  // 1406:         must be a single assignment static)@
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__360_28;
}
static void entry__360_13(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // node: 0
  // destination: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* node */
  frame->slots[1] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1398: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__360_14;
}
static void cont__360_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1398: $destination arguments_of(node)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__360_15;
}
static void cont__360_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* destination */, arguments->slots[0]);
  // 1401: destination.is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__360_16;
}
static void cont__360_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1402: attribute_kind_of(destination) == NONE
  frame->slots[4] /* temp__3 */ = create_closure(entry__360_17, 0);
  // 1400: &&
  // 1401:   destination.is_a_static_single_definition
  // 1402:   attribute_kind_of(destination) == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__360_20;
}
static void entry__360_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1402: attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__360_18;
}
static void cont__360_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1402: attribute_kind_of(destination) == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__360_19;
}
static void cont__360_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1402: attribute_kind_of(destination) == NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__360_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1403: :
  // 1404:   SyntaxError node "
  // 1405:     invalid polymorphic function definition (destination @
  // 1406:     must be a single assignment static)@
  frame->slots[5] /* temp__4 */ = create_closure(entry__360_21, 0);
  // 1399: unless
  // 1400:   &&
  // 1401:     destination.is_a_static_single_definition
  // 1402:     attribute_kind_of(destination) == NONE
  // 1403:   :
  // 1404:     SyntaxError node "
  // 1405:       invalid polymorphic function definition (destination @
  // 1406:       must be a single assignment static)@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__360_23;
}
static void entry__360_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1404: SyntaxError node "
  // 1405:   invalid polymorphic function definition (destination @
  // 1406:   must be a single assignment static)@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  arguments->slots[1] = string__bade31b19fa2fd8a;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__360_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1409: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__360_24;
}
static void cont__360_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1409: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__360_25;
}
static void cont__360_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1409: range(arguments_of(node) 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__360_26;
}
static void cont__360_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1410: destination(.variable_kind_of POLYMORPHIC)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* destination */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__POLYMORPHIC());
    frame->slots[5] /* temp__4 */ = temp;

  }
  // 1407: !node.arguments_of
  // 1408:   put
  // 1409:     range(arguments_of(node) 2 -1)
  // 1410:     destination(.variable_kind_of POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__360_27;
}
static void cont__360_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 1407: !node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__5 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__360_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1411: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__360_9(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // node: 1
  // break: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* node */
  frame->slots[2] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1396: ... source.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__360_10;
}
static void cont__360_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1396: ... :
  // 1397:   if source.is_a_polymorphic_function_constant:
  // 1398:     $destination arguments_of(node)(1)
  // 1399:     unless
  // 1400:       &&
  // 1401:         destination.is_a_static_single_definition
  // 1402:         attribute_kind_of(destination) == NONE
  // 1403:       :
  // 1404:         SyntaxError node "
  // 1405:           invalid polymorphic function definition (destination @
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__360_11, 0);
  // 1396: unless source.is_a_remark:
  // 1397:   if source.is_a_polymorphic_function_constant:
  // 1398:     $destination arguments_of(node)(1)
  // 1399:     unless
  // 1400:       &&
  // 1401:         destination.is_a_static_single_definition
  // 1402:         attribute_kind_of(destination) == NONE
  // 1403:       :
  // 1404:         SyntaxError node "
  // 1405:           invalid polymorphic function definition (destination @
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__360_29(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__360_30(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__360_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1384: $ASSIGNMENT_STATEMENT
  // 1385:   sequence
  // 1386:     set_node(assignment)
  // 1387:     STORE_POSITION
  // 1388:     arguments_span(OUTPUT_ARGUMENT)
  // 1389:     ARGUMENTS
  // 1390:     STORE_END_POSITION
  // 1391:     CHECK_ARGUMENTS("assignment" 1 1)
  // 1392:     modify_node
  // 1393:       : (&node)
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = var._ARGUMENTS;
  arguments->slots[4] = var._STORE_END_POSITION;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  arguments->slots[6] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__360_32;
}
static void cont__360_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ASSIGNMENT_STATEMENT, arguments->slots[0]);
  // 1415: set_node(procedure_call)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__procedure_call();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__361_1;
}
static void cont__361_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1418: optional(RESULT_COUNT_OR_CONTINUATION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._RESULT_COUNT_OR_CONTINUATION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__361_2;
}
static void cont__361_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1421: CHECK_ARGUMENTS("procedure call")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4f498b003024119a;
  result_count = 1;
  myself = var._CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__361_4;
}
static void cont__361_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1413: $PROCEDURE_STATEMENT
  // 1414:   sequence
  // 1415:     set_node(procedure_call)
  // 1416:     STORE_POSITION
  // 1417:     FUNCTOR
  // 1418:     optional(RESULT_COUNT_OR_CONTINUATION)
  // 1419:     ARGUMENTS
  // 1420:     STORE_END_POSITION
  // 1421:     CHECK_ARGUMENTS("procedure call")
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = var._FUNCTOR;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = var._ARGUMENTS;
  arguments->slots[5] = var._STORE_END_POSITION;
  arguments->slots[6] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__361_5;
}
static void cont__361_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PROCEDURE_STATEMENT, arguments->slots[0]);
  // 1425: set_node(return_statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__return_statement();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__362_1;
}
static void cont__362_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1430: CHECK_ARGUMENTS("return statement" 0 ONE_OR_MORE)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__8782cdb8103cde5a;
  arguments->slots[1] = number__0;
  arguments->slots[2] = var._ONE_OR_MORE;
  result_count = 1;
  myself = var._CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__362_3;
}
static void cont__362_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1423: $RETURN_STATEMENT
  // 1424:   sequence
  // 1425:     set_node(return_statement)
  // 1426:     STORE_POSITION
  // 1427:     "->"
  // 1428:     ARGUMENTS
  // 1429:     STORE_END_POSITION
  // 1430:     CHECK_ARGUMENTS("return statement" 0 ONE_OR_MORE)
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = string__2d7981f4e6602bfb;
  arguments->slots[3] = var._ARGUMENTS;
  arguments->slots[4] = var._STORE_END_POSITION;
  arguments->slots[5] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__362_4;
}
static void cont__362_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RETURN_STATEMENT, arguments->slots[0]);
  // 1438: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5ed2969d8211684f;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__363_2;
}
static void cont__363_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1432: $STATEMENT
  // 1433:   alt
  // 1434:     REMARK_STATEMENT
  // 1435:     PROCEDURE_STATEMENT
  // 1436:     ASSIGNMENT_STATEMENT
  // 1437:     RETURN_STATEMENT
  // 1438:     syntax_error("statement expected")
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_STATEMENT;
  arguments->slots[1] = var._PROCEDURE_STATEMENT;
  arguments->slots[2] = var._ASSIGNMENT_STATEMENT;
  arguments->slots[3] = var._RETURN_STATEMENT;
  arguments->slots[4] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__363_3;
}
static void cont__363_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STATEMENT, arguments->slots[0]);
  // 1442: ... multi_span(statements_of STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = var._STATEMENT;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__364_1;
}
static void cont__364_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1442: interleaved(multi_span(statements_of STATEMENT) NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__364_2;
}
static void cont__364_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__364_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__364_18;
}
static void entry__364_16(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1456: SyntaxError node "missing statement in body (there are only remarks)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = string__e72d5b3e0e5238e;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__364_3(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // node: 0
  // return_statement: 1
  // statement_found: 2
  frame->slots[1] /* return_statement */ = create_cell();
  frame->slots[2] /* statement_found */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1445: $$return_statement undefined
  ((CELL *)frame->slots[1])->contents /* return_statement */ = get__undefined();
  // 1446: $$statement_found false
  ((CELL *)frame->slots[2])->contents /* statement_found */ = get__false();
  // 1447: ... statements_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__364_4;
}
static void cont__364_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1447: ... : (statement)
  // 1448:   unless statement.is_a_remark:
  // 1449:     if return_statement.is_defined:
  // 1450:       SyntaxError
  // 1451:         return_statement
  // 1452:         "return statement is followed by another statement"
  // 1453:     if statement.is_a_return: !return_statement statement
  // 1454:     !statement_found true
  frame->slots[4] /* temp__2 */ = create_closure(entry__364_5, 1);
  // 1447: for_each statements_of(node): (statement)
  // 1448:   unless statement.is_a_remark:
  // 1449:     if return_statement.is_defined:
  // 1450:       SyntaxError
  // 1451:         return_statement
  // 1452:         "return statement is followed by another statement"
  // 1453:     if statement.is_a_return: !return_statement statement
  // 1454:     !statement_found true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__364_15;
}
static void entry__364_7(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return_statement: 0
  // statement: 1
  // statement_found: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* return_statement */
  frame->slots[1] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[2]; /* statement_found */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1449: ... return_statement.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_statement */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__364_8;
}
static void cont__364_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1449: ... :
  // 1450:   SyntaxError
  // 1451:     return_statement
  // 1452:     "return statement is followed by another statement"
  frame->slots[4] /* temp__2 */ = create_closure(entry__364_9, 0);
  // 1449: if return_statement.is_defined:
  // 1450:   SyntaxError
  // 1451:     return_statement
  // 1452:     "return statement is followed by another statement"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__364_11;
}
static void entry__364_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return_statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1450: SyntaxError
  // 1451:   return_statement
  // 1452:   "return statement is followed by another statement"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_statement */;
  arguments->slots[1] = string__51cbf656a5622dd3;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__364_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1453: ... statement.is_a_return
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__is_a_return();
  func = myself->type;
  frame->cont = cont__364_12;
}
static void cont__364_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1453: ... : !return_statement statement
  frame->slots[4] /* temp__2 */ = create_closure(entry__364_13, 0);
  // 1453: if statement.is_a_return: !return_statement statement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__364_14;
}
static void entry__364_13(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return_statement: 0
  // statement: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1453: ... !return_statement statement
  ((CELL *)frame->slots[0])->contents /* return_statement */ = frame->slots[1] /* statement */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__364_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1454: !statement_found true
  ((CELL *)frame->slots[2])->contents /* statement_found */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__364_5(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // statement: 0
  // return_statement: 1
  // statement_found: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* return_statement */
  frame->slots[2] = myself->closure.frame->slots[2]; /* statement_found */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1448: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__364_6;
}
static void cont__364_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1448: ... :
  // 1449:   if return_statement.is_defined:
  // 1450:     SyntaxError
  // 1451:       return_statement
  // 1452:       "return statement is followed by another statement"
  // 1453:   if statement.is_a_return: !return_statement statement
  // 1454:   !statement_found true
  frame->slots[4] /* temp__2 */ = create_closure(entry__364_7, 0);
  // 1448: unless statement.is_a_remark:
  // 1449:   if return_statement.is_defined:
  // 1450:     SyntaxError
  // 1451:       return_statement
  // 1452:       "return statement is followed by another statement"
  // 1453:   if statement.is_a_return: !return_statement statement
  // 1454:   !statement_found true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__364_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1455: ... :
  // 1456:   SyntaxError node "missing statement in body (there are only remarks)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__364_16, 0);
  // 1455: unless statement_found:
  // 1456:   SyntaxError node "missing statement in body (there are only remarks)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* statement_found */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__364_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1440: $STATEMENTS
  // 1441:   sequence
  // 1442:     interleaved(multi_span(statements_of STATEMENT) NEWLINES)
  // 1443:     inspect_node
  // 1444:       : (node)
  // 1445:         $$return_statement undefined
  // 1446:         $$statement_found false
  // 1447:         for_each statements_of(node): (statement)
  // 1448:           unless statement.is_a_remark:
  // 1449:             if return_statement.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__364_19;
}
static void cont__364_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STATEMENTS, arguments->slots[0]);
  // 1461: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__365_1;
}
static void cont__365_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1461: ... "__", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5f02b9a;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__365_3;
}
static void cont__365_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1461: ... many("__", NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__365_4;
}
static void cont__365_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1461: ... NAME, many("__", NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__NAME();
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__365_5;
}
static void cont__365_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1461: ... capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__365_6;
}
static void cont__365_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1461: set_node(identifier), capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__365_7;
}
static void cont__365_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1458: $BUILTIN_NAME
  // 1459:   span
  // 1460:     identifier_of
  // 1461:     set_node(identifier), capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__365_8;
}
static void cont__365_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BUILTIN_NAME, arguments->slots[0]);
  // 1463: ... not_followed_by('>')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__62;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__366_1;
}
static void cont__366_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1463: ... not_followed_by('>'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__366_2;
}
static void cont__366_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1463: $C_EXPRESSION many(not_followed_by('>'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__366_3;
}
static void cont__366_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_EXPRESSION, arguments->slots[0]);
  // 1468: ... multi_capture(arguments_of C_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__arguments_of();
  arguments->slots[1] = var._C_EXPRESSION;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__367_1;
}
static void cont__367_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1468: ... compiler::WHITESPACE, multi_capture(arguments_of C_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__367_2;
}
static void cont__367_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1468: expect(compiler::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__367_3;
}
static void cont__367_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1465: $ARGUMENT_ANNOTATION
  // 1466:   sequence
  // 1467:     "argument"
  // 1468:     expect(compiler::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74dcac9584a4c074;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__367_5;
}
static void cont__367_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENT_ANNOTATION, arguments->slots[0]);
  // 1471: ... span(base_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__base_of();
  arguments->slots[1] = var._NAMESPACED_IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__368_1;
}
static void cont__368_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1471: ... compiler::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__368_2;
}
static void cont__368_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1471: ... expect(compiler::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__368_3;
}
static void cont__368_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1470: $BASE_ANNOTATION
  // 1471:   "base", expect(compiler::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__60ae90b5df87d5c;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__368_5;
}
static void cont__368_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BASE_ANNOTATION, arguments->slots[0]);
  // 1473: ... capture(kind_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__kind_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__369_1;
}
static void cont__369_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1473: ... compiler::WHITESPACE, capture(kind_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__369_2;
}
static void cont__369_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1473: ... expect(compiler::WHITESPACE, capture(kind_of NAME))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__369_3;
}
static void cont__369_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1473: $KIND_ANNOTATION "kind", expect(compiler::WHITESPACE, capture(kind_of NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__140aeb0b5d107d5d;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__369_5;
}
static void cont__369_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._KIND_ANNOTATION, arguments->slots[0]);
  // 1479: ... alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._BUILTIN_NAME;
  arguments->slots[1] = var._DEFINED_VARIABLE_OR_ATTRIBUTE;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__370_1;
}
static void cont__370_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1479: compiler::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__370_2;
}
static void cont__370_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__370_3;
}
static void cont__370_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1475: $NAME_ANNOTATION
  // 1476:   sequence
  // 1477:     "name"
  // 1478:     expect
  // 1479:       compiler::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1e0ae90b5d087d5c;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__370_5;
}
static void cont__370_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAME_ANNOTATION, arguments->slots[0]);
  // 1481: ... capture(node_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__371_1;
}
static void cont__371_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1481: ... compiler::WHITESPACE, capture(node_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__371_2;
}
static void cont__371_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1481: ... expect(compiler::WHITESPACE, capture(node_of NAME))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__371_3;
}
static void cont__371_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1481: $NODE_ANNOTATION "node", expect(compiler::WHITESPACE, capture(node_of NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1e0aea8b5d407d5c;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__371_5;
}
static void cont__371_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NODE_ANNOTATION, arguments->slots[0]);
  // 1489: ... alt("runtime" "global" "local" "extern")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__9a4c0f9815d2209f;
  arguments->slots[1] = string__461f56c301b292bb;
  arguments->slots[2] = string__545aebc3eac0d03b;
  arguments->slots[3] = string__701f5702012bd2b9;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__372_5;
}
static void cont__372_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1489: capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__scope_of();
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__372_6;
}
static void cont__372_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__372_7;
}
static void cont__372_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__372_8;
}
static void cont__372_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1483: $SCOPE_ANNOTATION
  // 1484:   sequence
  // 1485:     "scope"
  // 1486:     expect
  // 1487:       sequence
  // 1488:         compiler::WHITESPACE
  // 1489:         capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4c5ae8c3ea492032;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__372_10;
}
static void cont__372_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SCOPE_ANNOTATION, arguments->slots[0]);
  // 1494: ... span(node::type_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__type_of();
  arguments->slots[1] = var._NAMESPACED_IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__373_1;
}
static void cont__373_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1494: ... compiler::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__373_2;
}
static void cont__373_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1494: expect(compiler::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__373_3;
}
static void cont__373_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1491: $TYPE_ANNOTATION
  // 1492:   sequence
  // 1493:     "type"
  // 1494:     expect(compiler::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2a0aef0b5de07d5c;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__373_5;
}
static void cont__373_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TYPE_ANNOTATION, arguments->slots[0]);
  // 1505: syntax_error("invalid annotation tag")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__399cfc434d66f26;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__374_2;
}
static void cont__374_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1496: $ANNOTATION_ITEM
  // 1497:   alt
  // 1498:     ARGUMENT_ANNOTATION
  // 1499:     BASE_ANNOTATION
  // 1500:     KIND_ANNOTATION
  // 1501:     NAME_ANNOTATION
  // 1502:     NODE_ANNOTATION
  // 1503:     SCOPE_ANNOTATION
  // 1504:     TYPE_ANNOTATION
  // 1505:     syntax_error("invalid annotation tag")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_ANNOTATION;
  arguments->slots[1] = var._BASE_ANNOTATION;
  arguments->slots[2] = var._KIND_ANNOTATION;
  arguments->slots[3] = var._NAME_ANNOTATION;
  arguments->slots[4] = var._NODE_ANNOTATION;
  arguments->slots[5] = var._SCOPE_ANNOTATION;
  arguments->slots[6] = var._TYPE_ANNOTATION;
  arguments->slots[7] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__374_3;
}
static void cont__374_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATION_ITEM, arguments->slots[0]);
  // 1507: ... expect('>')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__62;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__375_1;
}
static void cont__375_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1507: $ANNOTATION '<', ANNOTATION_ITEM, expect('>')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = var._ANNOTATION_ITEM;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__375_2;
}
static void cont__375_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATION, arguments->slots[0]);
  // 1508: $ANNOTATIONS interleaved(ANNOTATION NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ANNOTATION;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__376_1;
}
static void cont__376_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATIONS, arguments->slots[0]);
  // 1509: $C_CODE_REMARK "//", REMARK_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6702bea;
  arguments->slots[1] = var._REMARK_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__377_2;
}
static void cont__377_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_CODE_REMARK, arguments->slots[0]);
  // 1510: ... followed_by(OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OUTDENT;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__378_1;
}
static void cont__378_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1510: ... alt(NEWLINES followed_by(OUTDENT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__378_2;
}
static void cont__378_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1510: ... C_CODE_REMARK, alt(NEWLINES followed_by(OUTDENT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._C_CODE_REMARK;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__378_3;
}
static void cont__378_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1510: $C_CODE_REMARKS some(C_CODE_REMARK, alt(NEWLINES followed_by(OUTDENT)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__378_4;
}
static void cont__378_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_CODE_REMARKS, arguments->slots[0]);
  // 1515: ... not_followed_by(OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OUTDENT;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__379_1;
}
static void cont__379_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1515: ... not_followed_by(OUTDENT), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__379_2;
}
static void cont__379_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1515: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__379_3;
}
static void cont__379_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1515: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__source_of();
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__379_4;
}
static void cont__379_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1512: $SOURCE
  // 1513:   sequence
  // 1514:     C_CODE_REMARKS
  // 1515:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._C_CODE_REMARKS;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__379_5;
}
static void cont__379_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SOURCE, arguments->slots[0]);
  // 1520: set_node(c_code)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__c_code();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__380_1;
}
static void cont__380_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1521: expect(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__380_2;
}
static void cont__380_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1522: ... NEWLINES, SOURCE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._SOURCE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__380_3;
}
static void cont__380_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1522: ... optional(NEWLINES, SOURCE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__380_4;
}
static void cont__380_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1522: ... ANNOTATIONS, optional(NEWLINES, SOURCE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ANNOTATIONS;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__380_5;
}
static void cont__380_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1522: alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._SOURCE;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__380_6;
}
static void cont__380_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1523: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__380_7;
}
static void cont__380_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1524: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__380_8;
}
static void cont__380_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1525: some(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__380_9;
}
static void cont__380_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1526: expect('}')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__125;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__380_10;
}
static void cont__380_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1517: $C_CODE
  // 1518:   sequence
  // 1519:     '{'
  // 1520:     set_node(c_code)
  // 1521:     expect(indent_marker)
  // 1522:     alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
  // 1523:     expect(outdent_marker)
  // 1524:     expect(newline)
  // 1525:     some(newline)
  // 1526:     expect('}')
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = character__123;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[2] /* temp__3 */;
  arguments->slots[4] = frame->slots[6] /* temp__7 */;
  arguments->slots[5] = frame->slots[7] /* temp__8 */;
  arguments->slots[6] = frame->slots[8] /* temp__9 */;
  arguments->slots[7] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_11;
}
static void cont__380_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_CODE, arguments->slots[0]);
  // 1528: ... newline, END_OF_TEXT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  arguments->slots[1] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__381_1;
}
static void cont__381_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1528: ... expect(newline, END_OF_TEXT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__381_2;
}
static void cont__381_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1528: $META_FRAGMENT META_INSTRUCTION, expect(newline, END_OF_TEXT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._META_INSTRUCTION;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__381_3;
}
static void cont__381_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._META_FRAGMENT, arguments->slots[0]);
  // 1532: ... syntax_error("top-level statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__227de92deba39b6b;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__382_2;
}
static void cont__382_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1532: alt(C_CODE STATEMENT syntax_error("top-level statement expected"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._C_CODE;
  arguments->slots[1] = var._STATEMENT;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__382_3;
}
static void cont__382_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1533: ... newline, END_OF_TEXT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  arguments->slots[1] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__382_4;
}
static void cont__382_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1533: expect(newline, END_OF_TEXT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__382_5;
}
static void cont__382_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1530: $FRAGMENT
  // 1531:   sequence
  // 1532:     alt(C_CODE STATEMENT syntax_error("top-level statement expected"))
  // 1533:     expect(newline, END_OF_TEXT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__382_6;
}
static void cont__382_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FRAGMENT, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__std_identifier_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 31: ... identifier(.namespace_of "std" .name_of name)
  {
    NODE *temp = clone_object_and_attributes(get__identifier());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__namespace_of, string__fa724815d896ba8);
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[0] /* name */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 31: -> identifier(.namespace_of "std" .name_of name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__print_message_50(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // line_no: 0
  // n: 1
  // msg: 2
  frame->slots[0] = myself->closure.frame->slots[6]; /* line_no */
  frame->slots[1] = myself->closure.frame->slots[8]; /* n */
  frame->slots[2] = myself->closure.frame->slots[3]; /* msg */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 80: ... n+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__print_message_51;
}
static void cont__print_message_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 80: ... "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__578a5af303e9cdb;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* line_no */;
  arguments->slots[3] = string__578a5af303e9cdb;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = string__2d7981f4e6d82be5;
  arguments->slots[6] = ((CELL *)frame->slots[2])->contents /* msg */;
  arguments->slots[7] = string__578a5af303e9ceb;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__print_message_55;
}
static void cont__print_message_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 80: ewrite "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__print_message_56(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // msg_type: 0
  // line_no: 1
  // msg: 2
  // line: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* msg_type */
  frame->slots[1] = myself->closure.frame->slots[6]; /* line_no */
  frame->slots[2] = myself->closure.frame->slots[3]; /* msg */
  frame->slots[3] = myself->closure.frame->slots[11]; /* line */
  frame->slots[4] = myself->closure.frame->slots[8]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 82: ... "
  // 83:   ____________________________________
  // 84:   @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)@quot;:@nl;@(msg)!
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__3c655ae2e30c5e7c;
  arguments->slots[1] = frame->slots[0] /* msg_type */;
  arguments->slots[2] = string__3c082d0cc329b1a5;
  arguments->slots[3] = ((CELL *)frame->slots[1])->contents /* line_no */;
  arguments->slots[4] = string__6c6619488b29e163;
  arguments->slots[5] = get__module_name();
  arguments->slots[6] = string__fa730c15ff96bc6;
  arguments->slots[7] = ((CELL *)frame->slots[2])->contents /* msg */;
  arguments->slots[8] = string__2d7981f4e6002bcf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__print_message_62;
}
static void cont__print_message_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 82: ewrite "
  // 83:   ____________________________________
  // 84:   @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)@quot;:@nl;@(msg)!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__print_message_63;
}
static void cont__print_message_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 85: ewriteln line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* line */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__print_message_64;
}
static void cont__print_message_64(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 86: ... dup(" " n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* n */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__print_message_66;
}
static void cont__print_message_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 86: ewriteln dup(" " n) "^"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__578a5af303e9cbf;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__print_message_1(void) {
  allocate_initialized_frame_gc(4, 15);
  // slot allocations:
  // fragment: 0
  // offset: 1
  // msg_type: 2
  // msg: 3
  // source: 4
  // pos: 5
  // line_no: 6
  // line_offset: 7
  // n: 8
  // text: 9
  // rest: 10
  // line: 11
  frame->slots[4] /* source */ = create_cell();
  frame->slots[5] /* pos */ = create_future();
  frame->slots[6] /* line_no */ = create_cell();
  frame->slots[7] /* line_offset */ = create_future();
  frame->slots[8] /* n */ = create_cell();
  frame->slots[9] /* text */ = create_future();
  frame->slots[10] /* rest */ = create_future();
  frame->slots[11] /* line */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[3] /* msg */ = create_cell_with_contents(arguments->slots[3]);
  // 53: $$source compiler::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__compiler__source_of();
  func = myself->type;
  frame->cont = cont__print_message_2;
}
static void cont__print_message_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* source */ = arguments->slots[0];
  // 54: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__print_message_3;
}
static void cont__print_message_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__2 */ = arguments->slots[0];
  // 54: ... length_of(source)-offset
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* offset */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__print_message_4;
}
static void cont__print_message_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 54: $pos length_of(source)-offset+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__print_message_5;
}
static void cont__print_message_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* pos */, arguments->slots[0]);
  // 55: $$line_no line_no_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__line_no_of();
  func = myself->type;
  frame->cont = cont__print_message_6;
}
static void cont__print_message_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* line_no */ = arguments->slots[0];
  // 58: ... pos-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* pos */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__print_message_7;
}
static void cont__print_message_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__2 */ = arguments->slots[0];
  // 58: ... range(source 1 pos-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* source */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[13] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__print_message_8;
}
static void cont__print_message_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 58: ... alt(newline indent_marker)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  arguments->slots[1] = get__indent_marker();
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__print_message_9;
}
static void cont__print_message_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__3 */ = arguments->slots[0];
  // 57: $line_offset
  // 58:   count_occurrences(range(source 1 pos-1) alt(newline indent_marker))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__3 */;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__print_message_10;
}
static void cont__print_message_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* line_offset */, arguments->slots[0]);
  // 60: plus &line_no line_offset
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* line_no */;
  arguments->slots[1] = frame->slots[7] /* line_offset */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__print_message_11;
}
static void cont__print_message_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* line_no */ = arguments->slots[0];
  // 61: ... line_offset > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[7] /* line_offset */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__print_message_12;
}
static void cont__print_message_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 61: ... : behind &source alt(newline indent_marker) line_offset
  frame->slots[13] /* temp__2 */ = create_closure(entry__print_message_13, 0);
  // 61: if line_offset > 0: behind &source alt(newline indent_marker) line_offset
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__print_message_16;
}
static void entry__print_message_13(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // source: 0
  // line_offset: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* source */
  frame->slots[1] = myself->closure.frame->slots[7]; /* line_offset */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: ... alt(newline indent_marker)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  arguments->slots[1] = get__indent_marker();
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__print_message_14;
}
static void cont__print_message_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 61: ... behind &source alt(newline indent_marker) line_offset
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* line_offset */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__print_message_15;
}
static void cont__print_message_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* source */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__print_message_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 62: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__print_message_17;
}
static void cont__print_message_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 62: $$n length_of(source)-offset
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* offset */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__print_message_18;
}
static void cont__print_message_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* n */ = arguments->slots[0];
  // 63: ... -> n > 0 && source(n) < ' ': dec &n
  frame->slots[12] /* temp__1 */ = create_closure(entry__print_message_19, 0);
  // 63: while -> n > 0 && source(n) < ' ': dec &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__print_message_27;
}
static void entry__print_message_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // n: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: ... dec &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__print_message_26;
}
static void cont__print_message_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* n */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__print_message_19(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // n: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[8]; /* n */
  frame->slots[1] = myself->closure.frame->slots[4]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: ... n > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__print_message_20;
}
static void cont__print_message_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 63: ... source(n) < ' '
  frame->slots[4] /* temp__3 */ = create_closure(entry__print_message_21, 0);
  // 63: ... n > 0 && source(n) < ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__print_message_24;
}
static void entry__print_message_21(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // source: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  frame->slots[1] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: ... source(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* n */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* source */;
  func = myself->type;
  frame->cont = cont__print_message_22;
}
static void cont__print_message_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 63: ... source(n) < ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__print_message_23;
}
static void cont__print_message_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 63: ... source(n) < ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__print_message_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 63: ... : dec &n
  frame->slots[5] /* temp__4 */ = create_closure(entry__print_message_25, 0);
  // 63: ... -> n > 0 && source(n) < ' ': dec &n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__print_message_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 64: $text compiler::text_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__compiler__text_of();
  func = myself->type;
  frame->cont = cont__print_message_28;
}
static void cont__print_message_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* text */, arguments->slots[0]);
  // 68: line_offset > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[7] /* line_offset */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__print_message_29;
}
static void cont__print_message_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 69: -> behind(text '@nl;' line_offset)
  frame->slots[13] /* temp__2 */ = create_closure(entry__print_message_30, 0);
  // 70: -> text
  frame->slots[14] /* temp__3 */ = create_closure(entry__print_message_32, 0);
  // 66: $rest
  // 67:   if
  // 68:     line_offset > 0
  // 69:     -> behind(text '@nl;' line_offset)
  // 70:     -> text
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  arguments->slots[2] = frame->slots[14] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__print_message_33;
}
static void entry__print_message_30(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // text: 0
  // line_offset: 1
  frame->slots[0] = myself->closure.frame->slots[9]; /* text */
  frame->slots[1] = myself->closure.frame->slots[7]; /* line_offset */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... behind(text '@nl;' line_offset)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = character__10;
  arguments->slots[2] = frame->slots[1] /* line_offset */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__print_message_31;
}
static void cont__print_message_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 69: -> behind(text '@nl;' line_offset)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__print_message_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: -> text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__print_message_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[10] /* rest */, arguments->slots[0]);
  // 72: ... alt('@cr;' '@nl;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__13;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__print_message_34;
}
static void cont__print_message_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__2 */ = arguments->slots[0];
  // 72: ... rest .truncate_from. alt('@cr;' '@nl;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* rest */;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__print_message_35;
}
static void cont__print_message_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 72: ... '@ht;' = "        "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__9;
  arguments->slots[1] = string__ef94bdf606d19800;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__print_message_37;
}
static void cont__print_message_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__3 */ = arguments->slots[0];
  // 72: $line replace_all(rest .truncate_from. alt('@cr;' '@nl;') '@ht;' = "        ")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__print_message_38;
}
static void cont__print_message_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* line */, arguments->slots[0]);
  // 73: ... : (-> break)
  // 74:   for_each line: (chr)
  // 75:     if chr != ' ' break
  // 76:     inc &n
  frame->slots[12] /* temp__1 */ = create_closure(entry__print_message_39, 0);
  // 73: do: (-> break)
  // 74:   for_each line: (chr)
  // 75:     if chr != ' ' break
  // 76:     inc &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__print_message_46;
}
static void entry__print_message_39(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // line: 1
  // n: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[11]; /* line */
  frame->slots[2] = myself->closure.frame->slots[8]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: ... : (chr)
  // 75:   if chr != ' ' break
  // 76:   inc &n
  frame->slots[3] /* temp__1 */ = create_closure(entry__print_message_40, 1);
  // 74: for_each line: (chr)
  // 75:   if chr != ' ' break
  // 76:   inc &n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* line */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__print_message_45;
}
static void entry__print_message_40(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // chr: 0
  // break: 1
  // n: 2
  frame->slots[1] = myself->closure.frame->slots[0]; /* break */
  frame->slots[2] = myself->closure.frame->slots[2]; /* n */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 75: ... chr != ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__print_message_41;
}
static void cont__print_message_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 75: ... chr != ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__print_message_42;
}
static void cont__print_message_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 75: if chr != ' ' break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__print_message_43;
}
static void cont__print_message_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 76: inc &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* n */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__print_message_44;
}
static void cont__print_message_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* n */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__print_message_45(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__print_message_46(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 77: ... msg(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* msg */;
  func = myself->type;
  frame->cont = cont__print_message_47;
}
static void cont__print_message_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 77: to_upper_case &msg(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__print_message_48;
}
static void cont__print_message_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__2 */ = arguments->slots[0];
  // 77: ... &msg(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* msg */;
  func = myself->type;
  frame->cont = cont__print_message_49;
}
static void cont__print_message_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* msg */ = arguments->slots[0];
  // 79: ... :
  // 80:   ewrite "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  frame->slots[12] /* temp__1 */ = create_closure(entry__print_message_50, 0);
  // 81: :
  // 82:   ewrite "
  // 83:     ____________________________________
  // 84:     @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)@quot;:@nl;@(msg)!
  // 85:   ewriteln line
  // 86:   ewriteln dup(" " n) "^"
  frame->slots[13] /* temp__2 */ = create_closure(entry__print_message_56, 0);
  // 78: if
  // 79:   do_show_brief_messages:
  // 80:     ewrite "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  // 81:   :
  // 82:     ewrite "
  // 83:       ____________________________________
  // 84:       @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)@quot;:@nl;@(msg)!
  // 85:     ewriteln line
  // 86:     ewriteln dup(" " n) "^"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_show_brief_messages();
  arguments->slots[1] = frame->slots[12] /* temp__1 */;
  arguments->slots[2] = frame->slots[13] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__Warning_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // obj: 0
  // msg: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 89: ... fragment_of(obj)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* obj */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__Warning_2;
}
static void cont__compiler__Warning_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: ... source_position_of(obj)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* obj */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__Warning_3;
}
static void cont__compiler__Warning_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 89: print_message fragment_of(obj) source_position_of(obj) "WARNING" msg
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = string__eed8078214c9e0bd;
  arguments->slots[3] = frame->slots[1] /* msg */;
  result_count = frame->caller_result_count;
  myself = var._print_message;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__ExitWithSyntaxError_1(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // fragment: 0
  // offset: 1
  // msg: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 92: print_message fragment offset "SYNTAX ERROR" msg
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  arguments->slots[1] = frame->slots[1] /* offset */;
  arguments->slots[2] = string__ae3c04ed6f185295;
  arguments->slots[3] = frame->slots[2] /* msg */;
  result_count = 0;
  myself = var._print_message;
  func = myself->type;
  frame->cont = cont__ExitWithSyntaxError_3;
}
static void cont__ExitWithSyntaxError_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 93: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__SyntaxError_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // obj: 0
  // msg: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 96: ... fragment_of(obj)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* obj */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__SyntaxError_2;
}
static void cont__compiler__SyntaxError_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 96: ... source_position_of(obj)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* obj */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__SyntaxError_3;
}
static void cont__compiler__SyntaxError_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 96: ExitWithSyntaxError fragment_of(obj) source_position_of(obj) msg
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[1] /* msg */;
  result_count = frame->caller_result_count;
  myself = var._ExitWithSyntaxError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__ParseError_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // msg: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 99: ... length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__ParseError_2;
}
static void cont__ParseError_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 99: ExitWithSyntaxError current_fragment length_of(stream) msg
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__current_fragment();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* msg */;
  result_count = frame->caller_result_count;
  myself = var._ExitWithSyntaxError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__syntax_error__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 104: ... message_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__message_of();
  func = myself->type;
  frame->cont = cont__types__syntax_error__grammar__match_2;
}
static void cont__types__syntax_error__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 104: ParseError stream message_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__syntax_error_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // message: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 106: ... types::syntax_error(.message_of message)
  {
    NODE *temp = clone_object_and_attributes(var.types__syntax_error);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__message_of, frame->slots[0] /* message */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 106: ... -> types::syntax_error(.message_of message)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__unexpected_input_error__grammar__match_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: ParseError stream "newline expected"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__9a64e069c352dc6a;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unexpected_input_error__grammar__match_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 122: ParseError stream "indent expected"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__927507b8d9967cca;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unexpected_input_error__grammar__match_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 124: ParseError stream "outdent expected"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__9be468e9e34a9c6a;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unexpected_input_error__grammar__match_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 126: ParseError stream "closing quotation mark expected"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__ab853eb411a7faea;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unexpected_input_error__grammar__match_16(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // expression: 0
  // stream: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* expression */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 128: to_string &expression
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* expression */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_17;
}
static void cont__types__unexpected_input_error__grammar__match_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* expression */ = arguments->slots[0];
  // 129: ... expression(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* expression */;
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_18;
}
static void cont__types__unexpected_input_error__grammar__match_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 129: ... expression(1).is_a_letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_letter();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_19;
}
static void cont__types__unexpected_input_error__grammar__match_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 129: ... :
  // 130:   !expression "@quot;@(expression)@quot;"
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__unexpected_input_error__grammar__match_20, 0);
  // 129: unless expression(1).is_a_letter:
  // 130:   !expression "@quot;@(expression)@quot;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_23;
}
static void entry__types__unexpected_input_error__grammar__match_20(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // expression: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* expression */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: !expression "@quot;@(expression)@quot;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc3;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* expression */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_22;
}
static void cont__types__unexpected_input_error__grammar__match_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* expression */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__unexpected_input_error__grammar__match_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 131: ... "@(expression) expected"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* expression */;
  arguments->slots[1] = string__68d023a4c22b2461;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_25;
}
static void cont__types__unexpected_input_error__grammar__match_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 131: ParseError stream "@(expression) expected"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unexpected_input_error__grammar__match_7(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // expression: 0
  // stream: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* expression */
  frame->slots[1] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... :
  // 120:   ParseError stream "newline expected"
  frame->slots[2] /* temp__1 */ = create_closure(entry__types__unexpected_input_error__grammar__match_8, 0);
  // 121: ... :
  // 122:   ParseError stream "indent expected"
  frame->slots[3] /* temp__2 */ = create_closure(entry__types__unexpected_input_error__grammar__match_10, 0);
  // 123: ... :
  // 124:   ParseError stream "outdent expected"
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__unexpected_input_error__grammar__match_12, 0);
  // 125: ... :
  // 126:   ParseError stream "closing quotation mark expected"
  frame->slots[5] /* temp__4 */ = create_closure(entry__types__unexpected_input_error__grammar__match_14, 0);
  // 127: :
  // 128:   to_string &expression
  // 129:   unless expression(1).is_a_letter:
  // 130:     !expression "@quot;@(expression)@quot;"
  // 131:   ParseError stream "@(expression) expected"
  frame->slots[6] /* temp__5 */ = create_closure(entry__types__unexpected_input_error__grammar__match_16, 0);
  // 117: case
  // 118:   expression
  // 119:   newline:
  // 120:     ParseError stream "newline expected"
  // 121:   indent_marker:
  // 122:     ParseError stream "indent expected"
  // 123:   outdent_marker:
  // 124:     ParseError stream "outdent expected"
  // 125:   '@quot;':
  // 126:     ParseError stream "closing quotation mark expected"
  // ...
  argument_count = 10;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* expression */;
  arguments->slots[1] = get__newline();
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = get__indent_marker();
  arguments->slots[4] = frame->slots[3] /* temp__2 */;
  arguments->slots[5] = get__outdent_marker();
  arguments->slots[6] = frame->slots[4] /* temp__3 */;
  arguments->slots[7] = character__34;
  arguments->slots[8] = frame->slots[5] /* temp__4 */;
  arguments->slots[9] = frame->slots[6] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unexpected_input_error__grammar__match_26(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 133: ParseError stream "unexpected input"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__4914d002f7e03078;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unexpected_input_error__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // self: 0
  // stream: 1
  // expression: 2
  frame->slots[2] /* expression */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 114: $$expression expression_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__expression_of();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_2;
}
static void cont__types__unexpected_input_error__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* expression */ = arguments->slots[0];
  // 116: expression.is_a_character
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* expression */;
  result_count = 1;
  myself = get__is_a_character();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_3;
}
static void cont__types__unexpected_input_error__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 116: ... expression.is_a_string
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__unexpected_input_error__grammar__match_4, 0);
  // 116: expression.is_a_character || expression.is_a_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_6;
}
static void entry__types__unexpected_input_error__grammar__match_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* expression */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: ... expression.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* expression */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_5;
}
static void cont__types__unexpected_input_error__grammar__match_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 116: ... expression.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__unexpected_input_error__grammar__match_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 116: ... :
  // 117:   case
  // 118:     expression
  // 119:     newline:
  // 120:       ParseError stream "newline expected"
  // 121:     indent_marker:
  // 122:       ParseError stream "indent expected"
  // 123:     outdent_marker:
  // 124:       ParseError stream "outdent expected"
  // 125:     '@quot;':
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__unexpected_input_error__grammar__match_7, 0);
  // 132: :
  // 133:   ParseError stream "unexpected input"
  frame->slots[7] /* temp__5 */ = create_closure(entry__types__unexpected_input_error__grammar__match_26, 0);
  // 115: if
  // 116:   expression.is_a_character || expression.is_a_string:
  // 117:     case
  // 118:       expression
  // 119:       newline:
  // 120:         ParseError stream "newline expected"
  // 121:       indent_marker:
  // 122:         ParseError stream "indent expected"
  // 123:       outdent_marker:
  // 124:         ParseError stream "outdent expected"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  arguments->slots[2] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__unexpected_input_error_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 136: ... types::unexpected_input_error(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__unexpected_input_error);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 136: -> types::unexpected_input_error(.expression_of expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__dump_stream__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 155: ewriteln "<<<<<<<<<<"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8c16e735f8cebe3d;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__dump_stream__grammar__match_3;
}
static void cont__dump_stream__grammar__match_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 156: ... truncate_behind(stream '@nl;' 2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  arguments->slots[1] = character__10;
  arguments->slots[2] = number__2;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__dump_stream__grammar__match_4;
}
static void cont__dump_stream__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 156: eprint_source truncate_behind(stream '@nl;' 2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__eprint_source();
  func = myself->type;
  frame->cont = cont__dump_stream__grammar__match_5;
}
static void cont__dump_stream__grammar__match_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 157: ewriteln ">>>>>>>>>>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__881ef7b4fade9e7f;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__dump_stream__grammar__match_7;
}
static void cont__dump_stream__grammar__match_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 158: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__strip_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 165: !node.fragment_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__fragment_of, get__undefined());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 166: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, get__undefined());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 167: !node.end_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__end_position_of, get__undefined());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 168: !node.inherited_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__inherited_names_of, get__undefined());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 169: !node.defined_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__defined_names_of, get__undefined());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 170: !node.used_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__used_names_of, get__undefined());
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 171: ... functor_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_2;
}
static void cont__compiler__strip_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 171: ... functor_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__strip_3;
}
static void cont__compiler__strip_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 171: ... : strip &node.functor_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__strip_4, 0);
  // 171: if functor_of(node).is_defined: strip &node.functor_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__strip_7;
}
static void entry__compiler__strip_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: ... node.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_5;
}
static void cont__compiler__strip_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 171: ... strip &node.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__strip_6;
}
static void cont__compiler__strip_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 171: ... &node.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: ... attribute_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_8;
}
static void cont__compiler__strip_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 172: ... attribute_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__strip_9;
}
static void cont__compiler__strip_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 172: ... : strip &node.attribute_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__strip_10, 0);
  // 172: if attribute_of(node).is_defined: strip &node.attribute_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__strip_13;
}
static void entry__compiler__strip_10(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: ... node.attribute_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_11;
}
static void cont__compiler__strip_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 172: ... strip &node.attribute_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__strip_12;
}
static void cont__compiler__strip_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 172: ... &node.attribute_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__attribute_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 173: ... statements_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_14;
}
static void cont__compiler__strip_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 173: ... statements_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__strip_15;
}
static void cont__compiler__strip_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 173: ... :
  // 174:   update_each &node.statements_of: (&statement) strip &statement
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__strip_16, 0);
  // 173: if statements_of(node).is_defined:
  // 174:   update_each &node.statements_of: (&statement) strip &statement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__strip_21;
}
static void entry__compiler__strip_16(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... node.statements_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_17;
}
static void cont__compiler__strip_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: update_each &node.statements_of: (&statement) strip &statement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__compiler__strip_18;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__strip_20;
}
static void entry__compiler__strip_18(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // statement: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* statement */ = create_cell_with_contents(arguments->slots[0]);
  // 174: ... strip &statement
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* statement */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__strip_19;
}
static void cont__compiler__strip_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* statement */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* statement */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... &node.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 175: ... parameters_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_22;
}
static void cont__compiler__strip_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 175: ... parameters_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__strip_23;
}
static void cont__compiler__strip_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 175: ... :
  // 176:   update_each &node.parameters_of: (&parameter) strip &parameter
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__strip_24, 0);
  // 175: if parameters_of(node).is_defined:
  // 176:   update_each &node.parameters_of: (&parameter) strip &parameter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__strip_29;
}
static void entry__compiler__strip_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: ... node.parameters_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_25;
}
static void cont__compiler__strip_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 176: update_each &node.parameters_of: (&parameter) strip &parameter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__compiler__strip_26;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__strip_28;
}
static void entry__compiler__strip_26(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* parameter */ = create_cell_with_contents(arguments->slots[0]);
  // 176: ... strip &parameter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__strip_27;
}
static void cont__compiler__strip_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* parameter */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 176: ... &node.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_30;
}
static void cont__compiler__strip_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 177: ... arguments_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__strip_31;
}
static void cont__compiler__strip_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 177: ... :
  // 178:   update_each &node.arguments_of: (&argument) strip &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__strip_32, 0);
  // 177: if arguments_of(node).is_defined:
  // 178:   update_each &node.arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__strip_37;
}
static void entry__compiler__strip_32(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 178: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_33;
}
static void cont__compiler__strip_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 178: update_each &node.arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__compiler__strip_34;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__strip_36;
}
static void entry__compiler__strip_34(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 178: ... strip &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__strip_35;
}
static void cont__compiler__strip_35(void) {
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
static void cont__compiler__strip_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 178: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 179: ... parent_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parent_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_38;
}
static void cont__compiler__strip_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 179: ... parent_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__strip_39;
}
static void cont__compiler__strip_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 179: ... : strip &node.parent_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__strip_40, 0);
  // 179: if parent_of(node).is_defined: strip &node.parent_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__strip_43;
}
static void entry__compiler__strip_40(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... node.parent_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parent_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_41;
}
static void cont__compiler__strip_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 179: ... strip &node.parent_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__strip_42;
}
static void cont__compiler__strip_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 179: ... &node.parent_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parent_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 180: ... identifier_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_44;
}
static void cont__compiler__strip_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: ... identifier_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__strip_45;
}
static void cont__compiler__strip_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: ... : strip &node.identifier_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__strip_46, 0);
  // 180: if identifier_of(node).is_defined: strip &node.identifier_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__strip_49;
}
static void entry__compiler__strip_46(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... node.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__strip_47;
}
static void cont__compiler__strip_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: ... strip &node.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__strip_48;
}
static void cont__compiler__strip_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: ... &node.identifier_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__strip_49(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__dump__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 185: ... strip(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__dump__grammar__match_2;
}
static void cont__dump__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 185: edump `strip(grammar::current_node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__665e06ec4dcad6be;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__edump();
  func = myself->type;
  frame->cont = cont__dump__grammar__match_4;
}
static void cont__dump__grammar__match_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 186: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__dump3__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 191: ... strip(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__dump3__grammar__match_2;
}
static void cont__dump3__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 191: edump 3 `strip(grammar::current_node)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = string__665e06ec4dcad6be;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__edump();
  func = myself->type;
  frame->cont = cont__dump3__grammar__match_3;
}
static void cont__dump3__grammar__match_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 192: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__dump5__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 197: ... strip(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__dump5__grammar__match_2;
}
static void cont__dump5__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 197: edump 5 `strip(grammar::current_node)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__5;
  arguments->slots[1] = string__665e06ec4dcad6be;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__edump();
  func = myself->type;
  frame->cont = cont__dump5__grammar__match_3;
}
static void cont__dump5__grammar__match_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 198: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__precedence_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // op: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* op */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 231: ... precedence_table(op)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* op */;
  result_count = 1;
  myself = var._precedence_table;
  func = myself->type;
  frame->cont = cont__compiler__precedence_4;
}
static void cont__compiler__precedence_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 231: ... -> precedence_table(op)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__precedence_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 231: ... -> INFIX_PRECEDENCE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__INFIX_PRECEDENCE();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__precedence_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // op: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 231: ... op.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* op */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__compiler__precedence_2;
}
static void cont__compiler__precedence_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 231: ... -> precedence_table(op)
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__precedence_3, 0);
  // 231: if op.is_a_string (-> precedence_table(op)) -> INFIX_PRECEDENCE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = func__compiler__precedence_5;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__is_left_associative_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // prec: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 233: ... prec > 5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__5;
  arguments->slots[1] = frame->slots[0] /* prec */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__is_left_associative_2;
}
static void cont__compiler__is_left_associative_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 233: ... -> prec > 5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__is_right_associative_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // prec: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 235: ... prec <= 5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__5;
  arguments->slots[1] = frame->slots[0] /* prec */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__is_right_associative_2;
}
static void cont__is_right_associative_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 235: ... prec <= 5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__is_right_associative_3;
}
static void cont__is_right_associative_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 235: ... -> prec <= 5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__infix_operator_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // operator: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 238: ... compiler::WHITESPACE, operator, compiler::WHITESPACE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  arguments->slots[1] = frame->slots[0] /* operator */;
  arguments->slots[2] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__infix_operator_2;
}
static void cont__infix_operator_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 238: ... alt(operator compiler::WHITESPACE, operator, compiler::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* operator */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__infix_operator_3;
}
static void cont__infix_operator_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 238: -> alt(operator compiler::WHITESPACE, operator, compiler::WHITESPACE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__interleaved_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // expression: 0
  // separator: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 240: ... separator, expression
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* separator */;
  arguments->slots[1] = frame->slots[0] /* expression */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__interleaved_2;
}
static void cont__interleaved_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 240: ... some(separator, expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__interleaved_3;
}
static void cont__interleaved_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 240: ... expression, some(separator, expression)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__interleaved_4;
}
static void cont__interleaved_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 240: ... -> expression, some(separator, expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__store_arguments_index__grammar__match_1(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // self: 0
  // stream: 1
  // return__1: 2
  frame->slots[2] /* return__1 */ = create_continuation();
  define__arguments_index(create_future());
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 249: ... arguments_of(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__types__store_arguments_index__grammar__match_2;
}
static void cont__types__store_arguments_index__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 249: %arguments_index length_of(arguments_of(grammar::current_node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__store_arguments_index__grammar__match_3;
}
static void cont__types__store_arguments_index__grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__arguments_index(), arguments->slots[0]);
  // 250: ... expression_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__expression_of();
  func = myself->type;
  frame->cont = cont__types__store_arguments_index__grammar__match_4;
}
static void cont__types__store_arguments_index__grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 250: grammar::match expression_of(self) stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = frame->caller_result_count;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__types__store_arguments_index__grammar__match_5;
}
static void cont__types__store_arguments_index__grammar__match_5(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__store_arguments_index_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 253: ... types::store_arguments_index(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__store_arguments_index);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 253: -> types::store_arguments_index(.expression_of expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__inline__grammar__match_1(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // self: 0
  // stream: 1
  // return__1: 2
  frame->slots[2] /* return__1 */ = create_continuation();
  // _define %within_inline_expression true
  define__within_inline_expression(get_value_or_future__true());
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 262: %within_inline_expression true
  initialize_maybe_future(get__within_inline_expression(), get__true());
  // 263: ... expression_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__expression_of();
  func = myself->type;
  frame->cont = cont__types__inline__grammar__match_2;
}
static void cont__types__inline__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 263: grammar::match expression_of(self) stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = frame->caller_result_count;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__types__inline__grammar__match_3;
}
static void cont__types__inline__grammar__match_3(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__inline_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 265: ... types::inline(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__inline);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 265: ... -> types::inline(.expression_of expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__expect_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // expression: 0
  // description: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* expression */
  frame->slots[1] = myself->closure.frame->slots[1]; /* description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 283: ... "@(description) expected"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = string__68d023a4c22b2461;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__expect_4;
}
static void cont__expect_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 283: ... syntax_error("@(description) expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__expect_5;
}
static void cont__expect_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 283: ... alt(expression syntax_error("@(description) expected"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__expect_6;
}
static void cont__expect_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 283: -> alt(expression syntax_error("@(description) expected"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__expect_7(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // expression: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* expression */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: ... unexpected_input_error(expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  result_count = 1;
  myself = var._unexpected_input_error;
  func = myself->type;
  frame->cont = cont__expect_8;
}
static void cont__expect_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 284: ... alt(expression unexpected_input_error(expression))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__expect_9;
}
static void cont__expect_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 284: -> alt(expression unexpected_input_error(expression))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__expect_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // expression: 0
  // description: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* description */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* description */ = undefined;
  }
  // 282: description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__expect_2;
}
static void cont__expect_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 283: -> alt(expression syntax_error("@(description) expected"))
  frame->slots[3] /* temp__2 */ = create_closure(entry__expect_3, 0);
  // 284: -> alt(expression unexpected_input_error(expression))
  frame->slots[4] /* temp__3 */ = create_closure(entry__expect_7, 0);
  // 281: if
  // 282:   description.is_defined
  // 283:   -> alt(expression syntax_error("@(description) expected"))
  // 284:   -> alt(expression unexpected_input_error(expression))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__arguments_span_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 286: ... multi_span(arguments_of expression)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__arguments_of();
  arguments->slots[1] = frame->slots[0] /* expression */;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__compiler__arguments_span_2;
}
static void cont__compiler__arguments_span_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 286: ... -> multi_span(arguments_of expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_functor_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1321: SyntaxError functor "invalid functor"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  arguments->slots[1] = string__120dee9a1dcec47c;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_functor_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // functor: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1318: functor.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__check_functor_2;
}
static void cont__check_functor_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1319: functor.is_a_function_call && not(functor.is_in_infix_notation)
  frame->slots[3] /* temp__3 */ = create_closure(entry__check_functor_3, 0);
  // 1317: ||
  // 1318:   functor.is_an_identifier
  // 1319:   functor.is_a_function_call && not(functor.is_in_infix_notation)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__check_functor_9;
}
static void entry__check_functor_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1319: functor.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__check_functor_4;
}
static void cont__check_functor_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1319: ... not(functor.is_in_infix_notation)
  frame->slots[3] /* temp__3 */ = create_closure(entry__check_functor_5, 0);
  // 1319: functor.is_a_function_call && not(functor.is_in_infix_notation)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_functor_8;
}
static void entry__check_functor_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1319: ... functor.is_in_infix_notation
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  result_count = 1;
  myself = get__is_in_infix_notation();
  func = myself->type;
  frame->cont = cont__check_functor_6;
}
static void cont__check_functor_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1319: ... not(functor.is_in_infix_notation)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__check_functor_7;
}
static void cont__check_functor_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1319: ... not(functor.is_in_infix_notation)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_functor_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1319: functor.is_a_function_call && not(functor.is_in_infix_notation)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_functor_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1320: :
  // 1321:   SyntaxError functor "invalid functor"
  frame->slots[4] /* temp__4 */ = create_closure(entry__check_functor_10, 0);
  // 1316: unless
  // 1317:   ||
  // 1318:     functor.is_an_identifier
  // 1319:     functor.is_a_function_call && not(functor.is_in_infix_notation)
  // 1320:   :
  // 1321:     SyntaxError functor "invalid functor"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_78(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // kind: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* node */
  frame->slots[1] = myself->closure.frame->slots[3]; /* kind */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1379: ... "too few input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__bb0c2c1e659a1755;
  arguments->slots[1] = frame->slots[1] /* kind */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_80;
}
static void cont__check_arguments_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1379: SyntaxError node "too few input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_48(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // wanted_inputs: 0
  // inputs: 1
  // node: 2
  // kind: 3
  // min_inputs: 4
  // max_inputs: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* wanted_inputs */
  frame->slots[1] = myself->closure.frame->slots[5]; /* inputs */
  frame->slots[2] = myself->closure.frame->slots[0]; /* node */
  frame->slots[3] = myself->closure.frame->slots[1]; /* kind */
  frame->slots[4] /* min_inputs */ = create_future();
  frame->slots[5] /* max_inputs */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1359: wanted_inputs == ONE_OR_MORE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* wanted_inputs */;
  arguments->slots[1] = var._ONE_OR_MORE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_49;
}
static void cont__check_arguments_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1361: -> wanted_inputs
  frame->slots[7] /* temp__2 */ = create_closure(entry__check_arguments_50, 0);
  // 1357: $min_inputs
  // 1358:   if
  // 1359:     wanted_inputs == ONE_OR_MORE
  // 1360:     -> 1
  // 1361:     -> wanted_inputs
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__check_arguments_51;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_52;
}
static void entry__check_arguments_50(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // wanted_inputs: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* wanted_inputs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1361: -> wanted_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* wanted_inputs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1360: -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* min_inputs */, arguments->slots[0]);
  // 1365: wanted_inputs == ONE_OR_MORE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* wanted_inputs */;
  arguments->slots[1] = var._ONE_OR_MORE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_53;
}
static void cont__check_arguments_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1367: -> wanted_inputs
  frame->slots[7] /* temp__2 */ = create_closure(entry__check_arguments_54, 0);
  // 1363: $max_inputs
  // 1364:   if
  // 1365:     wanted_inputs == ONE_OR_MORE
  // 1366:     -> undefined
  // 1367:     -> wanted_inputs
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__check_arguments_55;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_56;
}
static void entry__check_arguments_54(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // wanted_inputs: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* wanted_inputs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1367: -> wanted_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* wanted_inputs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_55(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1366: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* max_inputs */, arguments->slots[0]);
  // 1369: ... max_inputs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* max_inputs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_57;
}
static void cont__check_arguments_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1369: ... inputs > max_inputs
  frame->slots[8] /* temp__3 */ = create_closure(entry__check_arguments_58, 0);
  // 1369: ... max_inputs.is_defined && inputs > max_inputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_arguments_60;
}
static void entry__check_arguments_58(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // max_inputs: 0
  // inputs: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* max_inputs */
  frame->slots[1] = myself->closure.frame->slots[1]; /* inputs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1369: ... inputs > max_inputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* max_inputs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* inputs */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_59;
}
static void cont__check_arguments_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1369: ... inputs > max_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1369: ... :
  // 1370:   $$first_input_argument undefined
  // 1371:   do: (-> break)
  // 1372:     for_each arguments_of(node): (argument)
  // 1373:       unless argument.is_a_destination:
  // 1374:         !first_input_argument argument
  // 1375:         break
  // 1376:   unless first_input_argument.is_an_attribute_value_pair:
  // 1377:     SyntaxError node "too many input arguments for @(kind)"
  frame->slots[9] /* temp__4 */ = create_closure(entry__check_arguments_61, 0);
  // 1369: if max_inputs.is_defined && inputs > max_inputs:
  // 1370:   $$first_input_argument undefined
  // 1371:   do: (-> break)
  // 1372:     for_each arguments_of(node): (argument)
  // 1373:       unless argument.is_a_destination:
  // 1374:         !first_input_argument argument
  // 1375:         break
  // 1376:   unless first_input_argument.is_an_attribute_value_pair:
  // 1377:     SyntaxError node "too many input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_73;
}
static void entry__check_arguments_70(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // kind: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* kind */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1377: ... "too many input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ebee6487b4b0342b;
  arguments->slots[1] = frame->slots[1] /* kind */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_72;
}
static void cont__check_arguments_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1377: SyntaxError node "too many input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_61(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // node: 0
  // kind: 1
  // first_input_argument: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* node */
  frame->slots[1] = myself->closure.frame->slots[3]; /* kind */
  frame->slots[2] /* first_input_argument */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1370: $$first_input_argument undefined
  ((CELL *)frame->slots[2])->contents /* first_input_argument */ = get__undefined();
  // 1371: ... : (-> break)
  // 1372:   for_each arguments_of(node): (argument)
  // 1373:     unless argument.is_a_destination:
  // 1374:       !first_input_argument argument
  // 1375:       break
  frame->slots[3] /* temp__1 */ = create_closure(entry__check_arguments_62, 0);
  // 1371: do: (-> break)
  // 1372:   for_each arguments_of(node): (argument)
  // 1373:     unless argument.is_a_destination:
  // 1374:       !first_input_argument argument
  // 1375:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__check_arguments_68;
}
static void entry__check_arguments_62(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // break: 0
  // node: 1
  // first_input_argument: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* node */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first_input_argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1372: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__check_arguments_63;
}
static void cont__check_arguments_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1372: ... : (argument)
  // 1373:   unless argument.is_a_destination:
  // 1374:     !first_input_argument argument
  // 1375:     break
  frame->slots[4] /* temp__2 */ = create_closure(entry__check_arguments_64, 1);
  // 1372: for_each arguments_of(node): (argument)
  // 1373:   unless argument.is_a_destination:
  // 1374:     !first_input_argument argument
  // 1375:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_67;
}
static void entry__check_arguments_66(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // first_input_argument: 0
  // argument: 1
  // break: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* first_input_argument */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[2] = myself->closure.frame->slots[2]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1374: !first_input_argument argument
  ((CELL *)frame->slots[0])->contents /* first_input_argument */ = frame->slots[1] /* argument */;
  // 1375: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_64(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // argument: 0
  // first_input_argument: 1
  // break: 2
  frame->slots[1] = myself->closure.frame->slots[2]; /* first_input_argument */
  frame->slots[2] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1373: ... argument.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_destination();
  func = myself->type;
  frame->cont = cont__check_arguments_65;
}
static void cont__check_arguments_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1373: ... :
  // 1374:   !first_input_argument argument
  // 1375:   break
  frame->slots[4] /* temp__2 */ = create_closure(entry__check_arguments_66, 0);
  // 1373: unless argument.is_a_destination:
  // 1374:   !first_input_argument argument
  // 1375:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_67(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1376: ... first_input_argument.is_an_attribute_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* first_input_argument */;
  result_count = 1;
  myself = get__is_an_attribute_value_pair();
  func = myself->type;
  frame->cont = cont__check_arguments_69;
}
static void cont__check_arguments_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1376: ... :
  // 1377:   SyntaxError node "too many input arguments for @(kind)"
  frame->slots[4] /* temp__2 */ = create_closure(entry__check_arguments_70, 0);
  // 1376: unless first_input_argument.is_an_attribute_value_pair:
  // 1377:   SyntaxError node "too many input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1378: ... min_inputs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* min_inputs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_74;
}
static void cont__check_arguments_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1378: ... inputs < min_inputs
  frame->slots[8] /* temp__3 */ = create_closure(entry__check_arguments_75, 0);
  // 1378: ... min_inputs.is_defined && inputs < min_inputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_arguments_77;
}
static void entry__check_arguments_75(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // inputs: 0
  // min_inputs: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* inputs */
  frame->slots[1] = myself->closure.frame->slots[4]; /* min_inputs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1378: ... inputs < min_inputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* inputs */;
  arguments->slots[1] = frame->slots[1] /* min_inputs */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_76;
}
static void cont__check_arguments_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1378: ... inputs < min_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1378: ... :
  // 1379:   SyntaxError node "too few input arguments for @(kind)"
  frame->slots[9] /* temp__4 */ = create_closure(entry__check_arguments_78, 0);
  // 1378: if min_inputs.is_defined && inputs < min_inputs:
  // 1379:   SyntaxError node "too few input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_1(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // node: 0
  // kind: 1
  // wanted_outputs: 2
  // wanted_inputs: 3
  // outputs: 4
  // inputs: 5
  // contains_attribute_value_pair: 6
  // contains_simple_input_argument: 7
  // add_argument: 8
  frame->slots[8] /* add_argument */ = create_future();
  frame->slots[4] /* outputs */ = create_cell();
  frame->slots[5] /* inputs */ = create_cell();
  frame->slots[6] /* contains_attribute_value_pair */ = create_cell();
  frame->slots[7] /* contains_simple_input_argument */ = create_cell();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* wanted_inputs */ = arguments->slots[3];
    case 3: frame->slots[2] /* wanted_outputs */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* wanted_outputs */ = undefined;
    case 3: frame->slots[3] /* wanted_inputs */ = undefined;
  }
  // 1329: ... : (argument)
  // 1330:   if argument.is_a_destination: inc &outputs
  // 1331:   if not(argument.is_a_destination) || argument.is_an_input_output_argument:
  // 1332:     if
  // 1333:       argument.is_an_attribute_value_pair:
  // 1334:         if contains_simple_input_argument:
  // 1335:           SyntaxError argument "unexpected attribute-value-pair"
  // 1336:         !contains_attribute_value_pair true
  // 1337:       :
  // 1338:         if contains_attribute_value_pair:
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__check_arguments_2, 1);
  // 1329: $add_argument: (argument)
  // 1330:   if argument.is_a_destination: inc &outputs
  // 1331:   if not(argument.is_a_destination) || argument.is_an_input_output_argument:
  // 1332:     if
  // 1333:       argument.is_an_attribute_value_pair:
  // 1334:         if contains_simple_input_argument:
  // 1335:           SyntaxError argument "unexpected attribute-value-pair"
  // 1336:         !contains_attribute_value_pair true
  // 1337:       :
  // 1338:         if contains_attribute_value_pair:
  // ...
  initialize_future(frame->slots[8] /* add_argument */, frame->slots[9] /* temp__1 */);
  // 1324: $$outputs 0
  ((CELL *)frame->slots[4])->contents /* outputs */ = number__0;
  // 1325: $$inputs 0
  ((CELL *)frame->slots[5])->contents /* inputs */ = number__0;
  // 1326: $$contains_attribute_value_pair false
  ((CELL *)frame->slots[6])->contents /* contains_attribute_value_pair */ = get__false();
  // 1327: $$contains_simple_input_argument false
  ((CELL *)frame->slots[7])->contents /* contains_simple_input_argument */ = get__false();
  // 1343: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__check_arguments_24;
}
static void entry__check_arguments_12(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // argument: 0
  // contains_simple_input_argument: 1
  // contains_attribute_value_pair: 2
  // inputs: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* contains_simple_input_argument */
  frame->slots[2] = myself->closure.frame->slots[3]; /* contains_attribute_value_pair */
  frame->slots[3] = myself->closure.frame->slots[4]; /* inputs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1333: argument.is_an_attribute_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_an_attribute_value_pair();
  func = myself->type;
  frame->cont = cont__check_arguments_13;
}
static void cont__check_arguments_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1333: ... :
  // 1334:   if contains_simple_input_argument:
  // 1335:     SyntaxError argument "unexpected attribute-value-pair"
  // 1336:   !contains_attribute_value_pair true
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_14, 0);
  // 1337: :
  // 1338:   if contains_attribute_value_pair:
  // 1339:     SyntaxError argument "simple argument within attribute definition"
  // 1340:   !contains_simple_input_argument true
  frame->slots[6] /* temp__3 */ = create_closure(entry__check_arguments_18, 0);
  // 1332: if
  // 1333:   argument.is_an_attribute_value_pair:
  // 1334:     if contains_simple_input_argument:
  // 1335:       SyntaxError argument "unexpected attribute-value-pair"
  // 1336:     !contains_attribute_value_pair true
  // 1337:   :
  // 1338:     if contains_attribute_value_pair:
  // 1339:       SyntaxError argument "simple argument within attribute definition"
  // 1340:     !contains_simple_input_argument true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_22;
}
static void entry__check_arguments_14(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // contains_simple_input_argument: 0
  // argument: 1
  // contains_attribute_value_pair: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* contains_simple_input_argument */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[2] = myself->closure.frame->slots[2]; /* contains_attribute_value_pair */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1334: ... :
  // 1335:   SyntaxError argument "unexpected attribute-value-pair"
  frame->slots[3] /* temp__1 */ = create_closure(entry__check_arguments_15, 0);
  // 1334: if contains_simple_input_argument:
  // 1335:   SyntaxError argument "unexpected attribute-value-pair"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* contains_simple_input_argument */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_17;
}
static void entry__check_arguments_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1335: SyntaxError argument "unexpected attribute-value-pair"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__c5acb93e4d23cfd9;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1336: !contains_attribute_value_pair true
  ((CELL *)frame->slots[2])->contents /* contains_attribute_value_pair */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_18(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // contains_attribute_value_pair: 0
  // argument: 1
  // contains_simple_input_argument: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* contains_attribute_value_pair */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[2] = myself->closure.frame->slots[1]; /* contains_simple_input_argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1338: ... :
  // 1339:   SyntaxError argument "simple argument within attribute definition"
  frame->slots[3] /* temp__1 */ = create_closure(entry__check_arguments_19, 0);
  // 1338: if contains_attribute_value_pair:
  // 1339:   SyntaxError argument "simple argument within attribute definition"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* contains_attribute_value_pair */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_21;
}
static void entry__check_arguments_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1339: SyntaxError argument "simple argument within attribute definition"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__687da0cc5622be9c;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1340: !contains_simple_input_argument true
  ((CELL *)frame->slots[2])->contents /* contains_simple_input_argument */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1341: inc &inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* inputs */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__check_arguments_23;
}
static void cont__check_arguments_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* inputs */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_2(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // argument: 0
  // outputs: 1
  // contains_simple_input_argument: 2
  // contains_attribute_value_pair: 3
  // inputs: 4
  frame->slots[1] = myself->closure.frame->slots[4]; /* outputs */
  frame->slots[2] = myself->closure.frame->slots[7]; /* contains_simple_input_argument */
  frame->slots[3] = myself->closure.frame->slots[6]; /* contains_attribute_value_pair */
  frame->slots[4] = myself->closure.frame->slots[5]; /* inputs */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1330: ... argument.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_destination();
  func = myself->type;
  frame->cont = cont__check_arguments_3;
}
static void cont__check_arguments_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1330: ... : inc &outputs
  frame->slots[6] /* temp__2 */ = create_closure(entry__check_arguments_4, 0);
  // 1330: if argument.is_a_destination: inc &outputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_6;
}
static void entry__check_arguments_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // outputs: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* outputs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1330: ... inc &outputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* outputs */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__check_arguments_5;
}
static void cont__check_arguments_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* outputs */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1331: ... argument.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_destination();
  func = myself->type;
  frame->cont = cont__check_arguments_7;
}
static void cont__check_arguments_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 1331: ... not(argument.is_a_destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__check_arguments_8;
}
static void cont__check_arguments_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1331: ... argument.is_an_input_output_argument
  frame->slots[8] /* temp__4 */ = create_closure(entry__check_arguments_9, 0);
  // 1331: ... not(argument.is_a_destination) || argument.is_an_input_output_argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__check_arguments_11;
}
static void entry__check_arguments_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1331: ... argument.is_an_input_output_argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_an_input_output_argument();
  func = myself->type;
  frame->cont = cont__check_arguments_10;
}
static void cont__check_arguments_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1331: ... argument.is_an_input_output_argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1331: ... :
  // 1332:   if
  // 1333:     argument.is_an_attribute_value_pair:
  // 1334:       if contains_simple_input_argument:
  // 1335:         SyntaxError argument "unexpected attribute-value-pair"
  // 1336:       !contains_attribute_value_pair true
  // 1337:     :
  // 1338:       if contains_attribute_value_pair:
  // 1339:         SyntaxError argument "simple argument within attribute definition"
  // 1340:       !contains_simple_input_argument true
  // ...
  frame->slots[9] /* temp__5 */ = create_closure(entry__check_arguments_12, 0);
  // 1331: if not(argument.is_a_destination) || argument.is_an_input_output_argument:
  // 1332:   if
  // 1333:     argument.is_an_attribute_value_pair:
  // 1334:       if contains_simple_input_argument:
  // 1335:         SyntaxError argument "unexpected attribute-value-pair"
  // 1336:       !contains_attribute_value_pair true
  // 1337:     :
  // 1338:       if contains_attribute_value_pair:
  // 1339:         SyntaxError argument "simple argument within attribute definition"
  // 1340:       !contains_simple_input_argument true
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1343: ... : (argument)
  // 1344:   unless argument.is_a_remark:
  // 1345:     if
  // 1346:       argument.is_a_backquoted_expression:
  // 1347:         add_argument string_literal(.node::text_of node::text_of(argument))
  // 1348:         add_argument expression_of(argument)
  // 1349:       :
  // 1350:         add_argument argument
  frame->slots[10] /* temp__2 */ = create_closure(entry__check_arguments_25, 1);
  // 1343: for_each arguments_of(node): (argument)
  // 1344:   unless argument.is_a_remark:
  // 1345:     if
  // 1346:       argument.is_a_backquoted_expression:
  // 1347:         add_argument string_literal(.node::text_of node::text_of(argument))
  // 1348:         add_argument expression_of(argument)
  // 1349:       :
  // 1350:         add_argument argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_34;
}
static void entry__check_arguments_29(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // add_argument: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* add_argument */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1347: ... node::text_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__check_arguments_30;
}
static void cont__check_arguments_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1347: ... string_literal(.node::text_of node::text_of(argument))
  {
    NODE *temp = clone_object_and_attributes(get__string_literal());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, frame->slots[3] /* temp__2 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 1347: add_argument string_literal(.node::text_of node::text_of(argument))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* add_argument */;
  func = myself->type;
  frame->cont = cont__check_arguments_31;
}
static void cont__check_arguments_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1348: ... expression_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__expression_of();
  func = myself->type;
  frame->cont = cont__check_arguments_32;
}
static void cont__check_arguments_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1348: add_argument expression_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* add_argument */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_33(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // add_argument: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* add_argument */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1350: add_argument argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* add_argument */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_27(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // argument: 0
  // add_argument: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* add_argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1346: argument.is_a_backquoted_expression
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_backquoted_expression();
  func = myself->type;
  frame->cont = cont__check_arguments_28;
}
static void cont__check_arguments_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1346: ... :
  // 1347:   add_argument string_literal(.node::text_of node::text_of(argument))
  // 1348:   add_argument expression_of(argument)
  frame->slots[3] /* temp__2 */ = create_closure(entry__check_arguments_29, 0);
  // 1349: :
  // 1350:   add_argument argument
  frame->slots[4] /* temp__3 */ = create_closure(entry__check_arguments_33, 0);
  // 1345: if
  // 1346:   argument.is_a_backquoted_expression:
  // 1347:     add_argument string_literal(.node::text_of node::text_of(argument))
  // 1348:     add_argument expression_of(argument)
  // 1349:   :
  // 1350:     add_argument argument
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_25(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // argument: 0
  // add_argument: 1
  frame->slots[1] = myself->closure.frame->slots[8]; /* add_argument */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1344: ... argument.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__check_arguments_26;
}
static void cont__check_arguments_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1344: ... :
  // 1345:   if
  // 1346:     argument.is_a_backquoted_expression:
  // 1347:       add_argument string_literal(.node::text_of node::text_of(argument))
  // 1348:       add_argument expression_of(argument)
  // 1349:     :
  // 1350:       add_argument argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__check_arguments_27, 0);
  // 1344: unless argument.is_a_remark:
  // 1345:   if
  // 1346:     argument.is_a_backquoted_expression:
  // 1347:       add_argument string_literal(.node::text_of node::text_of(argument))
  // 1348:       add_argument expression_of(argument)
  // 1349:     :
  // 1350:       add_argument argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1351: ... wanted_outputs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* wanted_outputs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_35;
}
static void cont__check_arguments_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1351: ... :
  // 1352:   if outputs > wanted_outputs:
  // 1353:     SyntaxError node "too many output arguments for @(kind)"
  // 1354:   if outputs < wanted_outputs:
  // 1355:     SyntaxError node "too few output arguments for @(kind)"
  frame->slots[10] /* temp__2 */ = create_closure(entry__check_arguments_36, 0);
  // 1351: if wanted_outputs.is_defined:
  // 1352:   if outputs > wanted_outputs:
  // 1353:     SyntaxError node "too many output arguments for @(kind)"
  // 1354:   if outputs < wanted_outputs:
  // 1355:     SyntaxError node "too few output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_46;
}
static void entry__check_arguments_43(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // kind: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* node */
  frame->slots[1] = myself->closure.frame->slots[3]; /* kind */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1355: ... "too few output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1b6e5ce3b21cbf2f;
  arguments->slots[1] = frame->slots[1] /* kind */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_45;
}
static void cont__check_arguments_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1355: SyntaxError node "too few output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_36(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // wanted_outputs: 0
  // outputs: 1
  // node: 2
  // kind: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* wanted_outputs */
  frame->slots[1] = myself->closure.frame->slots[4]; /* outputs */
  frame->slots[2] = myself->closure.frame->slots[0]; /* node */
  frame->slots[3] = myself->closure.frame->slots[1]; /* kind */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1352: ... outputs > wanted_outputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* wanted_outputs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* outputs */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_37;
}
static void cont__check_arguments_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1352: ... :
  // 1353:   SyntaxError node "too many output arguments for @(kind)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_38, 0);
  // 1352: if outputs > wanted_outputs:
  // 1353:   SyntaxError node "too many output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_41;
}
static void entry__check_arguments_38(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // kind: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* node */
  frame->slots[1] = myself->closure.frame->slots[3]; /* kind */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1353: ... "too many output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5fa0d5b2a9ee383d;
  arguments->slots[1] = frame->slots[1] /* kind */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_40;
}
static void cont__check_arguments_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1353: SyntaxError node "too many output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1354: ... outputs < wanted_outputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* outputs */;
  arguments->slots[1] = frame->slots[0] /* wanted_outputs */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_42;
}
static void cont__check_arguments_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1354: ... :
  // 1355:   SyntaxError node "too few output arguments for @(kind)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_43, 0);
  // 1354: if outputs < wanted_outputs:
  // 1355:   SyntaxError node "too few output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_46(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1356: ... wanted_inputs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* wanted_inputs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_47;
}
static void cont__check_arguments_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1356: ... :
  // 1357:   $min_inputs
  // 1358:     if
  // 1359:       wanted_inputs == ONE_OR_MORE
  // 1360:       -> 1
  // 1361:       -> wanted_inputs
  // 1362:   
  // 1363:   $max_inputs
  // 1364:     if
  // 1365:       wanted_inputs == ONE_OR_MORE
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__check_arguments_48, 0);
  // 1356: if wanted_inputs.is_defined:
  // 1357:   $min_inputs
  // 1358:     if
  // 1359:       wanted_inputs == ONE_OR_MORE
  // 1360:       -> 1
  // 1361:       -> wanted_inputs
  // 1362:   
  // 1363:   $max_inputs
  // 1364:     if
  // 1365:       wanted_inputs == ONE_OR_MORE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__CHECK_ARGUMENTS_2(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // node: 0
  // kind: 1
  // wanted_outputs: 2
  // wanted_inputs: 3
  frame->slots[1] = myself->closure.frame->slots[0]; /* kind */
  frame->slots[2] = myself->closure.frame->slots[1]; /* wanted_outputs */
  frame->slots[3] = myself->closure.frame->slots[2]; /* wanted_inputs */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1382: ... check_arguments node kind wanted_outputs wanted_inputs
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[1] /* kind */;
  arguments->slots[2] = frame->slots[2] /* wanted_outputs */;
  arguments->slots[3] = frame->slots[3] /* wanted_inputs */;
  result_count = frame->caller_result_count;
  myself = var._check_arguments;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__CHECK_ARGUMENTS_1(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // kind: 0
  // wanted_outputs: 1
  // wanted_inputs: 2
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* wanted_inputs */ = arguments->slots[2];
    case 2: frame->slots[1] /* wanted_outputs */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* wanted_outputs */ = undefined;
    case 2: frame->slots[2] /* wanted_inputs */ = undefined;
  }
  // 1382: ... : (node) check_arguments node kind wanted_outputs wanted_inputs
  frame->slots[3] /* temp__1 */ = create_closure(entry__CHECK_ARGUMENTS_2, 1);
  // 1382: inspect_node: (node) check_arguments node kind wanted_outputs wanted_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__inspect_node();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__parse_meta_instruction_1(void) {
  allocate_initialized_frame_gc(2, 9);
  // slot allocations:
  // fragment: 0
  // return__1: 1
  // source: 2
  // len: 3
  // cap: 4
  frame->slots[1] /* return__1 */ = create_continuation();
  // _define %compiler::current_fragment fragment
  define__compiler__current_fragment(frame->slots[0] /* fragment */);
  frame->slots[2] /* source */ = create_future();
  frame->slots[3] /* len */ = create_future();
  frame->slots[4] /* cap */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1539: %compiler::current_fragment fragment
  // 1540:   # used to generate meaningful error messages
  initialize_maybe_future(get__compiler__current_fragment(), frame->slots[0] /* fragment */);
  // 1542: $source compiler::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__compiler__source_of();
  func = myself->type;
  frame->cont = cont__compiler__parse_meta_instruction_2;
}
static void cont__compiler__parse_meta_instruction_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* source */, arguments->slots[0]);
  // 1543: match source META_FRAGMENT $len $cap
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  arguments->slots[1] = var._META_FRAGMENT;
  result_count = 2;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__compiler__parse_meta_instruction_3;
}
static void cont__compiler__parse_meta_instruction_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  initialize_future(frame->slots[4] /* cap */, arguments->slots[1]);
  // 1544: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__parse_meta_instruction_4;
}
static void cont__compiler__parse_meta_instruction_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 1544: ... len != length_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__parse_meta_instruction_5;
}
static void cont__compiler__parse_meta_instruction_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1544: ... len != length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__parse_meta_instruction_6;
}
static void cont__compiler__parse_meta_instruction_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1544: ... : ParseError source "invalid meta instruction"
  frame->slots[8] /* temp__4 */ = create_closure(entry__compiler__parse_meta_instruction_7, 0);
  // 1544: if len != length_of(source): ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__parse_meta_instruction_9;
}
static void entry__compiler__parse_meta_instruction_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1544: ... ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__12eb1acbffa2ae01;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__parse_meta_instruction_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1545: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__parse_statement_1(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // fragment: 0
  // return__1: 1
  // source: 2
  // len: 3
  // cap: 4
  frame->slots[1] /* return__1 */ = create_continuation();
  // _define %compiler::current_fragment fragment
  define__compiler__current_fragment(frame->slots[0] /* fragment */);
  frame->slots[2] /* source */ = create_future();
  frame->slots[3] /* len */ = create_future();
  frame->slots[4] /* cap */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1548: %compiler::current_fragment fragment
  // 1549:   # used to generate meaningful error messages
  initialize_maybe_future(get__compiler__current_fragment(), frame->slots[0] /* fragment */);
  // 1551: $source compiler::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__compiler__source_of();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_2;
}
static void cont__compiler__parse_statement_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* source */, arguments->slots[0]);
  // 1552: match source FRAGMENT $len $cap
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  arguments->slots[1] = var._FRAGMENT;
  result_count = 2;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_3;
}
static void cont__compiler__parse_statement_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  initialize_future(frame->slots[4] /* cap */, arguments->slots[1]);
  // 1554: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_4;
}
static void cont__compiler__parse_statement_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1554: ... :
  // 1555:   if len != length_of(source):
  // 1556:     ParseError source "superficious input at end of expression"
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__parse_statement_5, 0);
  // 1557: :
  // 1558:   ewriteln "________________________________________"
  // 1559:   eprint_source source
  // 1560:   ewriteln "no match"
  // 1561:   exit 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__parse_statement_11, 0);
  // 1553: if
  // 1554:   len.is_defined:
  // 1555:     if len != length_of(source):
  // 1556:       ParseError source "superficious input at end of expression"
  // 1557:   :
  // 1558:     ewriteln "________________________________________"
  // 1559:     eprint_source source
  // 1560:     ewriteln "no match"
  // 1561:     exit 1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_17;
}
static void entry__compiler__parse_statement_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1556: ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__482d004bd19ca8db;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__parse_statement_5(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // len: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* len */
  frame->slots[1] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1555: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_6;
}
static void cont__compiler__parse_statement_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1555: ... len != length_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_7;
}
static void cont__compiler__parse_statement_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1555: ... len != length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_8;
}
static void cont__compiler__parse_statement_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1555: ... :
  // 1556:   ParseError source "superficious input at end of expression"
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__parse_statement_9, 0);
  // 1555: if len != length_of(source):
  // 1556:   ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__parse_statement_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1558: ewriteln "________________________________________"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5278dd75c73e18e3;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_13;
}
static void cont__compiler__parse_statement_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1559: eprint_source source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 0;
  myself = get__eprint_source();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_14;
}
static void cont__compiler__parse_statement_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1560: ewriteln "no match"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6ca8a8f604cd4188;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__compiler__parse_statement_16;
}
static void cont__compiler__parse_statement_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1561: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__parse_statement_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1562: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__parser(void) {
  var.compiler__std_identifier = collect_node(var.compiler__std_identifier);
  var._print_message = collect_node(var._print_message);
  var.compiler__Warning = collect_node(var.compiler__Warning);
  var._ExitWithSyntaxError = collect_node(var._ExitWithSyntaxError);
  var.compiler__SyntaxError = collect_node(var.compiler__SyntaxError);
  var._ParseError = collect_node(var._ParseError);
  var.types__syntax_error = collect_node(var.types__syntax_error);
  var._syntax_error = collect_node(var._syntax_error);
  var.types__unexpected_input_error = collect_node(var.types__unexpected_input_error);
  var._unexpected_input_error = collect_node(var._unexpected_input_error);
  var._dump_stream = collect_node(var._dump_stream);
  var.compiler__strip = collect_node(var.compiler__strip);
  var._dump = collect_node(var._dump);
  var._dump3 = collect_node(var._dump3);
  var._dump5 = collect_node(var._dump5);
  var.compiler__HIGHEST_PRECEDENCE = collect_node(var.compiler__HIGHEST_PRECEDENCE);
  var.compiler__INFIX_PRECEDENCE = collect_node(var.compiler__INFIX_PRECEDENCE);
  var._precedence_table = collect_node(var._precedence_table);
  var.compiler__precedence = collect_node(var.compiler__precedence);
  var.compiler__is_left_associative = collect_node(var.compiler__is_left_associative);
  var._is_right_associative = collect_node(var._is_right_associative);
  var._infix_operator = collect_node(var._infix_operator);
  var._interleaved = collect_node(var._interleaved);
  var.types__store_arguments_index = collect_node(var.types__store_arguments_index);
  var._store_arguments_index = collect_node(var._store_arguments_index);
  var.types__inline = collect_node(var.types__inline);
  var._inline = collect_node(var._inline);
  var._NOT_INLINE = collect_node(var._NOT_INLINE);
  var._NEWLINE = collect_node(var._NEWLINE);
  var._INDENT = collect_node(var._INDENT);
  var._OUTDENT = collect_node(var._OUTDENT);
  var._HASHTAG = collect_node(var._HASHTAG);
  var._expect = collect_node(var._expect);
  var.compiler__arguments_span = collect_node(var.compiler__arguments_span);
  var.compiler__WHITESPACE = collect_node(var.compiler__WHITESPACE);
  var._SEPARATOR = collect_node(var._SEPARATOR);
  var._NEWLINES = collect_node(var._NEWLINES);
  var._STORE_POSITION = collect_node(var._STORE_POSITION);
  var._STORE_POSITION_MINUS_1 = collect_node(var._STORE_POSITION_MINUS_1);
  var._STORE_END_POSITION = collect_node(var._STORE_END_POSITION);
  var._IDENTIFIER = collect_node(var._IDENTIFIER);
  var._DEFINE_IDENTIFIER = collect_node(var._DEFINE_IDENTIFIER);
  var._NAMESPACED_IDENTIFIER = collect_node(var._NAMESPACED_IDENTIFIER);
  var._FILENAME = collect_node(var._FILENAME);
  var._REQUIRE = collect_node(var._REQUIRE);
  var._NAMESPACE = collect_node(var._NAMESPACE);
  var._USING = collect_node(var._USING);
  var._BASENAME = collect_node(var._BASENAME);
  var._C_FILENAME = collect_node(var._C_FILENAME);
  var._INCLUDE = collect_node(var._INCLUDE);
  var._LINK = collect_node(var._LINK);
  var._MASK = collect_node(var._MASK);
  var._FILEMASK = collect_node(var._FILEMASK);
  var._DATA = collect_node(var._DATA);
  var._META_INSTRUCTION = collect_node(var._META_INSTRUCTION);
  var._REMARK_LINE = collect_node(var._REMARK_LINE);
  var._REMARK_LINES = collect_node(var._REMARK_LINES);
  var._REMARK_STATEMENT = collect_node(var._REMARK_STATEMENT);
  var._REMARK = collect_node(var._REMARK);
  var._LINE_END_REMARK = collect_node(var._LINE_END_REMARK);
  var._NEXT_LINE_REMARK = collect_node(var._NEXT_LINE_REMARK);
  var._REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING = collect_node(var._REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING);
  var._REMARK_ARGUMENT = collect_node(var._REMARK_ARGUMENT);
  var._LINE_END_REMARK_ARGUMENT = collect_node(var._LINE_END_REMARK_ARGUMENT);
  var._FUNCTION_CALL = collect_node(var._FUNCTION_CALL);
  var._MAKE_ATTRIBUTE_ACCESS = collect_node(var._MAKE_ATTRIBUTE_ACCESS);
  var._ATTRIBUTE_ACCESS = collect_node(var._ATTRIBUTE_ACCESS);
  var._ATTRIBUTE_WRITE = collect_node(var._ATTRIBUTE_WRITE);
  var._EXTENSIONS = collect_node(var._EXTENSIONS);
  var._READ_WRITE_EXTENSIONS = collect_node(var._READ_WRITE_EXTENSIONS);
  var._IDENTIFIER_OR_FUNCTION_CALL = collect_node(var._IDENTIFIER_OR_FUNCTION_CALL);
  var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL = collect_node(var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL);
  var._DECIMAL_NUMBER = collect_node(var._DECIMAL_NUMBER);
  var._BINARY_DIGIT = collect_node(var._BINARY_DIGIT);
  var._BINARY_NUMBER = collect_node(var._BINARY_NUMBER);
  var._OCTAL_DIGIT = collect_node(var._OCTAL_DIGIT);
  var._OCTAL_NUMBER = collect_node(var._OCTAL_NUMBER);
  var._HEX_DIGIT = collect_node(var._HEX_DIGIT);
  var._HEX_NUMBER = collect_node(var._HEX_NUMBER);
  var._NUMBER = collect_node(var._NUMBER);
  var._SIMPLE_CHARACTER = collect_node(var._SIMPLE_CHARACTER);
  var._AT_CHARACTER = collect_node(var._AT_CHARACTER);
  var._NAMED_CHARACTER = collect_node(var._NAMED_CHARACTER);
  var._NUMERIC_CHARACTER = collect_node(var._NUMERIC_CHARACTER);
  var._SPECIAL_CHARACTER = collect_node(var._SPECIAL_CHARACTER);
  var._CHARACTER_SYMBOL = collect_node(var._CHARACTER_SYMBOL);
  var._CHARACTER = collect_node(var._CHARACTER);
  var._STRING_CHARACTER = collect_node(var._STRING_CHARACTER);
  var._STRING_INSERTION = collect_node(var._STRING_INSERTION);
  var._CHECK_INSERTIONS = collect_node(var._CHECK_INSERTIONS);
  var._STRING = collect_node(var._STRING);
  var._STRING_LINE = collect_node(var._STRING_LINE);
  var._ADD_LINE_END = collect_node(var._ADD_LINE_END);
  var._MULTI_LINE_STRING = collect_node(var._MULTI_LINE_STRING);
  var._UNIQUE_ITEM = collect_node(var._UNIQUE_ITEM);
  var._PARENTHESED_EXPRESSION = collect_node(var._PARENTHESED_EXPRESSION);
  var._OPTION = collect_node(var._OPTION);
  var._NEGATION = collect_node(var._NEGATION);
  var._SIMPLE_OPERAND = collect_node(var._SIMPLE_OPERAND);
  var._OPERAND = collect_node(var._OPERAND);
  var._INFIX_OPERATOR_SYMBOL = collect_node(var._INFIX_OPERATOR_SYMBOL);
  var._SYMBOLIC_OPERATOR = collect_node(var._SYMBOLIC_OPERATOR);
  var._COMMA_OPERATOR = collect_node(var._COMMA_OPERATOR);
  var._NAMED_OPERATOR = collect_node(var._NAMED_OPERATOR);
  var._INFIX_OPERATOR = collect_node(var._INFIX_OPERATOR);
  var._EXTEND_EXPRESSION = collect_node(var._EXTEND_EXPRESSION);
  var._EXPRESSION = collect_node(var._EXPRESSION);
  var._DEFINED_VARIABLE = collect_node(var._DEFINED_VARIABLE);
  var._NAME_OF_POLYMORPHIC = collect_node(var._NAME_OF_POLYMORPHIC);
  var._DEFINED_VARIABLE_OR_ATTRIBUTE = collect_node(var._DEFINED_VARIABLE_OR_ATTRIBUTE);
  var._DEFINE_STATIC_SINGLE = collect_node(var._DEFINE_STATIC_SINGLE);
  var._DEFINE_STATIC_MULTI = collect_node(var._DEFINE_STATIC_MULTI);
  var._DEFINE_DYNAMIC_SINGLE = collect_node(var._DEFINE_DYNAMIC_SINGLE);
  var._DEFINE_DYNAMIC_MULTI = collect_node(var._DEFINE_DYNAMIC_MULTI);
  var._METHOD_DEFINITION = collect_node(var._METHOD_DEFINITION);
  var._ASSIGN = collect_node(var._ASSIGN);
  var._DESTINATION = collect_node(var._DESTINATION);
  var._BACKQUOTED = collect_node(var._BACKQUOTED);
  var._EXPANSION = collect_node(var._EXPANSION);
  var._OUTPUT_ARGUMENT = collect_node(var._OUTPUT_ARGUMENT);
  var._INPUT_OUTPUT_ARGUMENT = collect_node(var._INPUT_OUTPUT_ARGUMENT);
  var._INPUT_ARGUMENT = collect_node(var._INPUT_ARGUMENT);
  var._VALUE_ARGUMENT = collect_node(var._VALUE_ARGUMENT);
  var._ATTRIBUTE_VALUE_PAIR = collect_node(var._ATTRIBUTE_VALUE_PAIR);
  var._OPERATORS_AND_OPERANDS = collect_node(var._OPERATORS_AND_OPERANDS);
  var._MULTI_LINE_EXPRESSION = collect_node(var._MULTI_LINE_EXPRESSION);
  var._PARAMETER_MODE = collect_node(var._PARAMETER_MODE);
  var._PARAMETER_COUNT_OR_MYSELF = collect_node(var._PARAMETER_COUNT_OR_MYSELF);
  var._NOT_USED = collect_node(var._NOT_USED);
  var._PARAMETER_NAME = collect_node(var._PARAMETER_NAME);
  var._PARAMETER = collect_node(var._PARAMETER);
  var._MULTI_LINE_PARAMETER = collect_node(var._MULTI_LINE_PARAMETER);
  var._CONTINUATION = collect_node(var._CONTINUATION);
  var._MULTI_LINE_CONTINUATION = collect_node(var._MULTI_LINE_CONTINUATION);
  var._INLINE_PARAMETERS = collect_node(var._INLINE_PARAMETERS);
  var._MULTI_LINE_PARAMETERS = collect_node(var._MULTI_LINE_PARAMETERS);
  var._COMPLETE_BODY = collect_node(var._COMPLETE_BODY);
  var._RETURN_EXPRESSION = collect_node(var._RETURN_EXPRESSION);
  var._BODY = collect_node(var._BODY);
  var._C_BODY = collect_node(var._C_BODY);
  var._LINE_END_EXPRESSION = collect_node(var._LINE_END_EXPRESSION);
  var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER = collect_node(var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER);
  var._POLYMORPHIC_FUNCTION_WITH_SETTER = collect_node(var._POLYMORPHIC_FUNCTION_WITH_SETTER);
  var._POLYMORPHIC_FUNCTION = collect_node(var._POLYMORPHIC_FUNCTION);
  var._FUNCTOR = collect_node(var._FUNCTOR);
  var._RESULT_COUNT_OR_CONTINUATION = collect_node(var._RESULT_COUNT_OR_CONTINUATION);
  var._ARGUMENT = collect_node(var._ARGUMENT);
  var._FIRST_LINE_ARGUMENTS = collect_node(var._FIRST_LINE_ARGUMENTS);
  var._MULTI_LINE_FUNCTION_CALL = collect_node(var._MULTI_LINE_FUNCTION_CALL);
  var._ARGUMENT_LINE = collect_node(var._ARGUMENT_LINE);
  var._INLINE_ARGUMENTS = collect_node(var._INLINE_ARGUMENTS);
  var._INDENTED_ARGUMENTS = collect_node(var._INDENTED_ARGUMENTS);
  var._ARGUMENTS = collect_node(var._ARGUMENTS);
  var._ONE_OR_MORE = collect_node(var._ONE_OR_MORE);
  var._check_functor = collect_node(var._check_functor);
  var._check_arguments = collect_node(var._check_arguments);
  var._CHECK_ARGUMENTS = collect_node(var._CHECK_ARGUMENTS);
  var._ASSIGNMENT_STATEMENT = collect_node(var._ASSIGNMENT_STATEMENT);
  var._PROCEDURE_STATEMENT = collect_node(var._PROCEDURE_STATEMENT);
  var._RETURN_STATEMENT = collect_node(var._RETURN_STATEMENT);
  var._STATEMENT = collect_node(var._STATEMENT);
  var._STATEMENTS = collect_node(var._STATEMENTS);
  var._BUILTIN_NAME = collect_node(var._BUILTIN_NAME);
  var._C_EXPRESSION = collect_node(var._C_EXPRESSION);
  var._ARGUMENT_ANNOTATION = collect_node(var._ARGUMENT_ANNOTATION);
  var._BASE_ANNOTATION = collect_node(var._BASE_ANNOTATION);
  var._KIND_ANNOTATION = collect_node(var._KIND_ANNOTATION);
  var._NAME_ANNOTATION = collect_node(var._NAME_ANNOTATION);
  var._NODE_ANNOTATION = collect_node(var._NODE_ANNOTATION);
  var._SCOPE_ANNOTATION = collect_node(var._SCOPE_ANNOTATION);
  var._TYPE_ANNOTATION = collect_node(var._TYPE_ANNOTATION);
  var._ANNOTATION_ITEM = collect_node(var._ANNOTATION_ITEM);
  var._ANNOTATION = collect_node(var._ANNOTATION);
  var._ANNOTATIONS = collect_node(var._ANNOTATIONS);
  var._C_CODE_REMARK = collect_node(var._C_CODE_REMARK);
  var._C_CODE_REMARKS = collect_node(var._C_CODE_REMARKS);
  var._SOURCE = collect_node(var._SOURCE);
  var._C_CODE = collect_node(var._C_CODE);
  var._META_FRAGMENT = collect_node(var._META_FRAGMENT);
  var._FRAGMENT = collect_node(var._FRAGMENT);
  var.compiler__parse_meta_instruction = collect_node(var.compiler__parse_meta_instruction);
  var.compiler__parse_statement = collect_node(var.compiler__parse_statement);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__parser(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__parser(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("parser");
  character__9 = from_uchar32(9);
  character__35 = from_uchar32(35);
  number__6 = from_uint32(6U);
  number__99 = from_uint32(99U);
  character__38 = from_uchar32(38);
  character__47 = from_uchar32(47);
  character__94 = from_uchar32(94);
  character__96 = from_uchar32(96);
  character__55 = from_uchar32(55);
  character__65 = from_uchar32(65);
  character__63 = from_uchar32(63);
  number__12 = from_uint32(12U);
  character__44 = from_uchar32(44);
  character__45 = from_uchar32(45);
  character__10 = from_uchar32(10);
  character__58 = from_uchar32(58);
  number__0 = from_uint32(0U);
  character__70 = from_uchar32(70);
  character__48 = from_uchar32(48);
  number__3 = from_uint32(3U);
  character__13 = from_uchar32(13);
  character__37 = from_uchar32(37);
  character__102 = from_uchar32(102);
  number__4 = from_uint32(4U);
  character__60 = from_uchar32(60);
  character__95 = from_uchar32(95);
  character__33 = from_uchar32(33);
  number__8 = from_uint32(8U);
  character__64 = from_uchar32(64);
  character__40 = from_uchar32(40);
  number__7 = from_uint32(7U);
  character__34 = from_uchar32(34);
  character__36 = from_uchar32(36);
  number__5 = from_uint32(5U);
  character__123 = from_uchar32(123);
  character__39 = from_uchar32(39);
  number__9 = from_uint32(9U);
  character__32 = from_uchar32(32);
  character__61 = from_uchar32(61);
  number__11 = from_uint32(11U);
  character__125 = from_uchar32(125);
  character__43 = from_uchar32(43);
  character__101 = from_uchar32(101);
  number__13 = from_uint32(13U);
  character__41 = from_uchar32(41);
  character__124 = from_uchar32(124);
  character__59 = from_uchar32(59);
  character__97 = from_uchar32(97);
  number__1 = from_uint32(1U);
  character__69 = from_uchar32(69);
  character__49 = from_uchar32(49);
  character__46 = from_uchar32(46);
  number__2 = from_uint32(2U);
  character__42 = from_uchar32(42);
  number__10 = from_uint32(10U);
  character__62 = from_uchar32(62);
  number__14 = from_uint32(14U);
  string__fa724815d896ba8 = from_latin_1_string("std", 3);
  func__compiler__std_identifier_1 = create_function(entry__compiler__std_identifier_1, 1);
  string__ef94bdf606d19800 = from_latin_1_string("        ", 8);
  string__578a5af303e9cdb = from_latin_1_string(":", 1);
  string__2d7981f4e6d82be5 = from_latin_1_string(": ", 2);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  string__3c655ae2e30c5e7c = from_latin_1_string("____________________________________\012", 37);
  string__3c082d0cc329b1a5 = from_latin_1_string(" IN LINE ", 9);
  string__6c6619488b29e163 = from_latin_1_string(" OF FILE \042", 10);
  string__fa730c15ff96bc6 = from_latin_1_string("\042:\012", 3);
  string__2d7981f4e6002bcf = from_latin_1_string("!\012", 2);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  string__578a5af303e9cbf = from_latin_1_string("^", 1);
  func__print_message_1 = create_function(entry__print_message_1, 4);
  string__eed8078214c9e0bd = from_latin_1_string("WARNING", 7);
  func__compiler__Warning_1 = create_function(entry__compiler__Warning_1, 2);
  string__ae3c04ed6f185295 = from_latin_1_string("SYNTAX ERROR", 12);
  func__ExitWithSyntaxError_1 = create_function(entry__ExitWithSyntaxError_1, 3);
  func__compiler__SyntaxError_1 = create_function(entry__compiler__SyntaxError_1, 2);
  func__ParseError_1 = create_function(entry__ParseError_1, 2);
  func__types__syntax_error__grammar__match_1 = create_function(entry__types__syntax_error__grammar__match_1, 2);
  func__syntax_error_1 = create_function(entry__syntax_error_1, 1);
  string__9a64e069c352dc6a = from_latin_1_string("newline expected", 16);
  string__927507b8d9967cca = from_latin_1_string("indent expected", 15);
  string__9be468e9e34a9c6a = from_latin_1_string("outdent expected", 16);
  string__ab853eb411a7faea = from_latin_1_string("closing quotation mark expected", 31);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__68d023a4c22b2461 = from_latin_1_string(" expected", 9);
  string__4914d002f7e03078 = from_latin_1_string("unexpected input", 16);
  func__types__unexpected_input_error__grammar__match_1 = create_function(entry__types__unexpected_input_error__grammar__match_1, 2);
  func__unexpected_input_error_1 = create_function(entry__unexpected_input_error_1, 1);
  string__8c16e735f8cebe3d = from_latin_1_string("<<<<<<<<<<", 10);
  string__881ef7b4fade9e7f = from_latin_1_string(">>>>>>>>>>", 10);
  func__dump_stream__grammar__match_1 = create_function(entry__dump_stream__grammar__match_1, 2);
  func__compiler__strip_18 = create_function(entry__compiler__strip_18, 1);
  func__compiler__strip_26 = create_function(entry__compiler__strip_26, 1);
  func__compiler__strip_34 = create_function(entry__compiler__strip_34, 1);
  func__compiler__strip_1 = create_function(entry__compiler__strip_1, 1);
  string__665e06ec4dcad6be = from_latin_1_string("strip(grammar::current_node)", 28);
  func__dump__grammar__match_1 = create_function(entry__dump__grammar__match_1, 2);
  func__dump3__grammar__match_1 = create_function(entry__dump3__grammar__match_1, 2);
  func__dump5__grammar__match_1 = create_function(entry__dump5__grammar__match_1, 2);
  func__compiler__precedence_5 = create_function(entry__compiler__precedence_5, 0);
  func__compiler__precedence_1 = create_function(entry__compiler__precedence_1, 1);
  func__compiler__is_left_associative_1 = create_function(entry__compiler__is_left_associative_1, 1);
  func__is_right_associative_1 = create_function(entry__is_right_associative_1, 1);
  func__infix_operator_1 = create_function(entry__infix_operator_1, 1);
  func__interleaved_1 = create_function(entry__interleaved_1, 2);
  func__types__store_arguments_index__grammar__match_1 = create_function(entry__types__store_arguments_index__grammar__match_1, 2);
  func__store_arguments_index_1 = create_function(entry__store_arguments_index_1, 1);
  func__types__inline__grammar__match_1 = create_function(entry__types__inline__grammar__match_1, 2);
  func__inline_1 = create_function(entry__inline_1, 1);
  func__expect_1 = create_function(entry__expect_1, -1);
  func__compiler__arguments_span_1 = create_function(entry__compiler__arguments_span_1, 1);
  unique__ONE_OR_MORE = register_unique_item("ONE_OR_MORE");
  string__120dee9a1dcec47c = from_latin_1_string("invalid functor", 15);
  func__check_functor_1 = create_function(entry__check_functor_1, 1);
  string__c5acb93e4d23cfd9 = from_latin_1_string("unexpected attribute-value-pair", 31);
  string__687da0cc5622be9c = from_latin_1_string("simple argument within attribute definition", 43);
  string__5fa0d5b2a9ee383d = from_latin_1_string("too many output arguments for ", 30);
  string__1b6e5ce3b21cbf2f = from_latin_1_string("too few output arguments for ", 29);
  func__check_arguments_51 = create_function(entry__check_arguments_51, 0);
  func__check_arguments_55 = create_function(entry__check_arguments_55, 0);
  string__ebee6487b4b0342b = from_latin_1_string("too many input arguments for ", 29);
  string__bb0c2c1e659a1755 = from_latin_1_string("too few input arguments for ", 28);
  func__check_arguments_1 = create_function(entry__check_arguments_1, -1);
  func__CHECK_ARGUMENTS_1 = create_function(entry__CHECK_ARGUMENTS_1, -1);
  string__12eb1acbffa2ae01 = from_latin_1_string("invalid meta instruction", 24);
  func__compiler__parse_meta_instruction_1 = create_function(entry__compiler__parse_meta_instruction_1, 1);
  string__482d004bd19ca8db = from_latin_1_string("superficious input at end of expression", 39);
  string__5278dd75c73e18e3 = from_latin_1_string("________________________________________", 40);
  string__6ca8a8f604cd4188 = from_latin_1_string("no match", 8);
  func__compiler__parse_statement_1 = create_function(entry__compiler__parse_statement_1, 1);
  string__578a5af303e9ccb = from_latin_1_string("*", 1);
  string__578a5af303e9cce = from_latin_1_string("/", 1);
  string__578a5af303e9cca = from_latin_1_string("+", 1);
  string__578a5af303e9ccc = from_latin_1_string("-", 1);
  string__2d7981f4e6e82bf9 = from_latin_1_string("<<", 2);
  string__2d7981f4e6f82bfb = from_latin_1_string(">>", 2);
  string__578a5af303e9cc7 = from_latin_1_string("&", 1);
  string__578a5af303e9c9d = from_latin_1_string("|", 1);
  string__2d7981f4e6e82bf8 = from_latin_1_string("<=", 2);
  string__578a5af303e9cdd = from_latin_1_string("<", 1);
  string__2d7981f4e6f82bf8 = from_latin_1_string(">=", 2);
  string__578a5af303e9cdf = from_latin_1_string(">", 1);
  string__2d7981f4e6e02bf8 = from_latin_1_string("==", 2);
  string__2d7981f4e6002bf8 = from_latin_1_string("!=", 2);
  string__2d7981f4e6382be3 = from_latin_1_string("&&", 2);
  string__2d7981f4e4e82bb9 = from_latin_1_string("||", 2);
  string__2d7981f4e6782beb = from_latin_1_string("..", 2);
  string__578a5af303e9ccd = from_latin_1_string(",", 1);
  string__578a5af303e9cdc = from_latin_1_string("=", 1);
  string__ccbf6d451aa8563f = from_latin_1_string("\042)\042 expected", 12);
  func__230_1 = create_function(entry__230_1, 2);
  func__240_1 = create_function(entry__240_1, 2);
  func__241_1 = create_function(entry__241_1, 2);
  func__242_1 = create_function(entry__242_1, 2);
  func__243_3 = create_function(entry__243_3, 1);
  string__2d7981f4e6d82bff = from_latin_1_string("::", 2);
  string__958c1dda41e5a79c = from_latin_1_string("namespace must not start with an underscore", 43);
  func__244_4 = create_function(entry__244_4, 1);
  string__2d7981f4e6782bea = from_latin_1_string("./", 2);
  string__92e1510f182d5769 = from_latin_1_string("the module \042", 12);
  string__fd365ba9213c93f1 = from_latin_1_string("\042 is required twice", 19);
  func__247_3 = create_function(entry__247_3, 2);
  string__44dcaf9484448bc5 = from_latin_1_string("<require", 8);
  func__248_4 = create_function(entry__248_4, 1);
  string__e13e5990aea4c8f3 = from_latin_1_string("the namespace alias \042", 21);
  string__54767964cc2066c4 = from_latin_1_string("\042 is defined twice", 18);
  string__9159abe89634488c = from_latin_1_string("the namespace \042", 15);
  func__248_10 = create_function(entry__248_10, 2);
  string__1552f059283245c4 = from_latin_1_string("<namespace", 10);
  string__1d0508008a8a40d8 = from_latin_1_string("\042 is used twice", 15);
  func__249_3 = create_function(entry__249_3, 2);
  string__7e1f542e81cb02b0 = from_latin_1_string("<using", 6);
  string__fa733c15f596be3 = from_latin_1_string("../", 3);
  string__2c64b158ac2be503 = from_latin_1_string("the file \042", 10);
  string__b0b6bb19371893f7 = from_latin_1_string("\042 is included twice", 19);
  func__252_3 = create_function(entry__252_3, 2);
  string__76b0a89104f5abc5 = from_latin_1_string("<include", 8);
  string__a660d7293a5c47e8 = from_latin_1_string("the library \042", 13);
  string__ad06d2ccd69d8e1 = from_latin_1_string("\042 is linked twice", 17);
  func__253_3 = create_function(entry__253_3, 2);
  string__525ae943eabdd03c = from_latin_1_string("<link", 5);
  string__e720c6242e8cd532 = from_latin_1_string("the data dependency \042", 21);
  func__256_3 = create_function(entry__256_3, 2);
  string__425aeb43ea6dd036 = from_latin_1_string("<data", 5);
  func__264_2 = create_function(entry__264_2, 0);
  func__264_1 = create_function(entry__264_1, 1);
  func__267_1 = create_function(entry__267_1, 1);
  string__4456c807200257a4 = from_latin_1_string("function call", 13);
  func__268_1 = create_function(entry__268_1, 1);
  string__2d7981f4e6882ba7 = from_latin_1_string("0b", 2);
  string__2d7981f4e6882baa = from_latin_1_string("0o", 2);
  string__2d7981f4e6882bbd = from_latin_1_string("0x", 2);
  func__283_2 = create_function(entry__283_2, 1);
  func__284_1 = create_function(entry__284_1, 1);
  string__dea962eab6ac8f23 = from_latin_1_string("invalid character name", 22);
  func__285_2 = create_function(entry__285_2, 2);
  func__286_10 = create_function(entry__286_10, 1);
  string__4313674f4741806a = from_latin_1_string("invalid special character", 25);
  func__290_1 = create_function(entry__290_1, 1);
  string__2d7981f4e5082bfe = from_latin_1_string("@;", 2);
  func__291_1 = create_function(entry__291_1, 1);
  string__2d7981f4e5082bed = from_latin_1_string("@(", 2);
  string__7c1f540901cb12b0 = from_latin_1_string("string", 6);
  func__292_1 = create_function(entry__292_1, 1);
  func__295_1 = create_function(entry__295_1, 1);
  string__55df65a142fc9536 = from_latin_1_string("expression expected", 19);
  string__64d512703527e2ab = from_latin_1_string("key_value_pair", 14);
  string__2a0aedcb5dc87d5c = from_latin_1_string("true", 4);
  func__299_1 = create_function(entry__299_1, 1);
  string__2d7981f4e6602be8 = from_latin_1_string("--", 2);
  func__300_1 = create_function(entry__300_1, 1);
  func__307_2 = create_function(entry__307_2, 1);
  func__308_13 = create_function(entry__308_13, 0);
  func__308_52 = create_function(entry__308_52, 0);
  func__308_1 = create_function(entry__308_1, 1);
  string__395c5a51a203e553 = from_latin_1_string("identifier", 10);
  string__2d7981f4e6282be1 = from_latin_1_string("$$", 2);
  string__2d7981f4e6202be0 = from_latin_1_string("%%", 2);
  func__317_1 = create_function(entry__317_1, 1);
  string__5b01b0908c396eea = from_latin_1_string("attribute value", 15);
  func__328_3 = create_function(entry__328_3, 1);
  string__137554cc13b7640e = from_latin_1_string("multi line expression", 21);
  string__733ccdbfc49ced05 = from_latin_1_string("too few arguments in multi-line expression", 42);
  func__328_11 = create_function(entry__328_11, 2);
  func__331_1 = create_function(entry__331_1, 1);
  string__2d7981f4e6602bfb = from_latin_1_string("->", 2);
  func__339_6 = create_function(entry__339_6, 1);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  string__fa732415f216be5 = from_latin_1_string("(!)", 3);
  string__2d7981f4e6782bed = from_latin_1_string(".(", 2);
  string__e1e3be9ec64af0e1 = from_latin_1_string("argument expected", 17);
  func__351_3 = create_function(entry__351_3, 1);
  string__2f401958355b9795 = from_latin_1_string("assignment", 10);
  string__bade31b19fa2fd8a = from_latin_1_string("invalid polymorphic function definition (destination must be a single assignment static)", 88);
  func__360_5 = create_function(entry__360_5, 1);
  string__4f498b003024119a = from_latin_1_string("procedure call", 14);
  string__8782cdb8103cde5a = from_latin_1_string("return statement", 16);
  string__5ed2969d8211684f = from_latin_1_string("statement expected", 18);
  string__51cbf656a5622dd3 = from_latin_1_string("return statement is followed by another statement", 49);
  string__e72d5b3e0e5238e = from_latin_1_string("missing statement in body (there are only remarks)", 50);
  func__364_3 = create_function(entry__364_3, 1);
  string__2d7981f4e5f02b9a = from_latin_1_string("__", 2);
  string__74dcac9584a4c074 = from_latin_1_string("argument", 8);
  string__60ae90b5df87d5c = from_latin_1_string("base", 4);
  string__140aeb0b5d107d5d = from_latin_1_string("kind", 4);
  string__1e0ae90b5d087d5c = from_latin_1_string("name", 4);
  string__1e0aea8b5d407d5c = from_latin_1_string("node", 4);
  string__9a4c0f9815d2209f = from_latin_1_string("runtime", 7);
  string__461f56c301b292bb = from_latin_1_string("global", 6);
  string__545aebc3eac0d03b = from_latin_1_string("local", 5);
  string__701f5702012bd2b9 = from_latin_1_string("extern", 6);
  string__4c5ae8c3ea492032 = from_latin_1_string("scope", 5);
  string__2a0aef0b5de07d5c = from_latin_1_string("type", 4);
  string__399cfc434d66f26 = from_latin_1_string("invalid annotation tag", 22);
  string__2d7981f4e6702bea = from_latin_1_string("//", 2);
  string__227de92deba39b6b = from_latin_1_string("top-level statement expected", 28);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__parser(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("parser");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("compiler", "std_identifier", get__compiler__std_identifier, &var.compiler__std_identifier);
  define_single_assign_static("compiler", "Warning", get__compiler__Warning, &var.compiler__Warning);
  define_single_assign_static("compiler", "SyntaxError", get__compiler__SyntaxError, &var.compiler__SyntaxError);
  define_single_assign_static("types", "syntax_error", get__types__syntax_error, &var.types__syntax_error);
  define_single_assign_static("types", "unexpected_input_error", get__types__unexpected_input_error, &var.types__unexpected_input_error);
  define_single_assign_static("compiler", "strip", get__compiler__strip, &var.compiler__strip);
  define_single_assign_static("compiler", "HIGHEST_PRECEDENCE", get__compiler__HIGHEST_PRECEDENCE, &var.compiler__HIGHEST_PRECEDENCE);
  define_single_assign_static("compiler", "INFIX_PRECEDENCE", get__compiler__INFIX_PRECEDENCE, &var.compiler__INFIX_PRECEDENCE);
  var._precedence_table = create_future();
  define_single_assign_static("compiler", "precedence", get__compiler__precedence, &var.compiler__precedence);
  define_single_assign_static("compiler", "is_left_associative", get__compiler__is_left_associative, &var.compiler__is_left_associative);
  register_dynamic(&dyna_idx__arguments_index);
  define__arguments_index(create_future());
  define_single_assign_static("types", "store_arguments_index", get__types__store_arguments_index, &var.types__store_arguments_index);
  register_dynamic(&dyna_idx__within_inline_expression);
  define__within_inline_expression(create_future());
  define_single_assign_static("types", "inline", get__types__inline, &var.types__inline);
  var._NOT_INLINE = create_future();
  var._NEWLINE = create_future();
  var._INDENT = create_future();
  var._OUTDENT = create_future();
  var._HASHTAG = create_future();
  define_single_assign_static("compiler", "arguments_span", get__compiler__arguments_span, &var.compiler__arguments_span);
  define_single_assign_static("compiler", "WHITESPACE", get__compiler__WHITESPACE, &var.compiler__WHITESPACE);
  var._SEPARATOR = create_future();
  var._NEWLINES = create_future();
  var._STORE_POSITION = create_future();
  var._STORE_POSITION_MINUS_1 = create_future();
  var._STORE_END_POSITION = create_future();
  var._IDENTIFIER = create_future();
  var._DEFINE_IDENTIFIER = create_future();
  var._NAMESPACED_IDENTIFIER = create_future();
  var._FILENAME = create_future();
  var._REQUIRE = create_future();
  var._NAMESPACE = create_future();
  var._USING = create_future();
  var._BASENAME = create_future();
  var._C_FILENAME = create_future();
  var._INCLUDE = create_future();
  var._LINK = create_future();
  var._MASK = create_future();
  var._FILEMASK = create_future();
  var._DATA = create_future();
  var._META_INSTRUCTION = create_future();
  var._REMARK_LINE = create_future();
  var._REMARK_LINES = create_future();
  var._REMARK_STATEMENT = create_future();
  var._REMARK = create_future();
  var._LINE_END_REMARK = create_future();
  var._NEXT_LINE_REMARK = create_future();
  var._REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING = create_future();
  var._REMARK_ARGUMENT = create_future();
  var._LINE_END_REMARK_ARGUMENT = create_future();
  var._FUNCTION_CALL = create_future();
  var._MAKE_ATTRIBUTE_ACCESS = create_future();
  var._ATTRIBUTE_ACCESS = create_future();
  var._ATTRIBUTE_WRITE = create_future();
  var._EXTENSIONS = create_future();
  var._READ_WRITE_EXTENSIONS = create_future();
  var._IDENTIFIER_OR_FUNCTION_CALL = create_future();
  var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL = create_future();
  var._DECIMAL_NUMBER = create_future();
  var._BINARY_DIGIT = create_future();
  var._BINARY_NUMBER = create_future();
  var._OCTAL_DIGIT = create_future();
  var._OCTAL_NUMBER = create_future();
  var._HEX_DIGIT = create_future();
  var._HEX_NUMBER = create_future();
  var._NUMBER = create_future();
  var._SIMPLE_CHARACTER = create_future();
  var._AT_CHARACTER = create_future();
  var._NAMED_CHARACTER = create_future();
  var._NUMERIC_CHARACTER = create_future();
  var._SPECIAL_CHARACTER = create_future();
  var._CHARACTER_SYMBOL = create_future();
  var._CHARACTER = create_future();
  var._STRING_CHARACTER = create_future();
  var._STRING_INSERTION = create_future();
  var._CHECK_INSERTIONS = create_future();
  var._STRING = create_future();
  var._STRING_LINE = create_future();
  var._ADD_LINE_END = create_future();
  var._MULTI_LINE_STRING = create_future();
  var._UNIQUE_ITEM = create_future();
  var._PARENTHESED_EXPRESSION = create_future();
  var._OPTION = create_future();
  var._NEGATION = create_future();
  var._SIMPLE_OPERAND = create_future();
  var._OPERAND = create_future();
  var._INFIX_OPERATOR_SYMBOL = create_future();
  var._SYMBOLIC_OPERATOR = create_future();
  var._COMMA_OPERATOR = create_future();
  var._NAMED_OPERATOR = create_future();
  var._INFIX_OPERATOR = create_future();
  var._EXTEND_EXPRESSION = create_future();
  var._EXPRESSION = create_future();
  var._DEFINED_VARIABLE = create_future();
  var._NAME_OF_POLYMORPHIC = create_future();
  var._DEFINED_VARIABLE_OR_ATTRIBUTE = create_future();
  var._DEFINE_STATIC_SINGLE = create_future();
  var._DEFINE_STATIC_MULTI = create_future();
  var._DEFINE_DYNAMIC_SINGLE = create_future();
  var._DEFINE_DYNAMIC_MULTI = create_future();
  var._METHOD_DEFINITION = create_future();
  var._ASSIGN = create_future();
  var._DESTINATION = create_future();
  var._BACKQUOTED = create_future();
  var._EXPANSION = create_future();
  var._OUTPUT_ARGUMENT = create_future();
  var._INPUT_OUTPUT_ARGUMENT = create_future();
  var._INPUT_ARGUMENT = create_future();
  var._VALUE_ARGUMENT = create_future();
  var._ATTRIBUTE_VALUE_PAIR = create_future();
  var._OPERATORS_AND_OPERANDS = create_future();
  var._MULTI_LINE_EXPRESSION = create_future();
  var._PARAMETER_MODE = create_future();
  var._PARAMETER_COUNT_OR_MYSELF = create_future();
  var._NOT_USED = create_future();
  var._PARAMETER_NAME = create_future();
  var._PARAMETER = create_future();
  var._MULTI_LINE_PARAMETER = create_future();
  var._CONTINUATION = create_future();
  var._MULTI_LINE_CONTINUATION = create_future();
  var._INLINE_PARAMETERS = create_future();
  var._MULTI_LINE_PARAMETERS = create_future();
  var._COMPLETE_BODY = create_future();
  var._RETURN_EXPRESSION = create_future();
  var._BODY = create_future();
  var._C_BODY = create_future();
  var._LINE_END_EXPRESSION = create_future();
  var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER = create_future();
  var._POLYMORPHIC_FUNCTION_WITH_SETTER = create_future();
  var._POLYMORPHIC_FUNCTION = create_future();
  var._FUNCTOR = create_future();
  var._RESULT_COUNT_OR_CONTINUATION = create_future();
  var._ARGUMENT = create_future();
  var._FIRST_LINE_ARGUMENTS = create_future();
  var._MULTI_LINE_FUNCTION_CALL = create_future();
  var._ARGUMENT_LINE = create_future();
  var._INLINE_ARGUMENTS = create_future();
  var._INDENTED_ARGUMENTS = create_future();
  var._ARGUMENTS = create_future();
  assign_value(&var._ONE_OR_MORE, unique__ONE_OR_MORE);
  var._ASSIGNMENT_STATEMENT = create_future();
  var._PROCEDURE_STATEMENT = create_future();
  var._RETURN_STATEMENT = create_future();
  var._STATEMENT = create_future();
  var._STATEMENTS = create_future();
  var._BUILTIN_NAME = create_future();
  var._C_EXPRESSION = create_future();
  var._ARGUMENT_ANNOTATION = create_future();
  var._BASE_ANNOTATION = create_future();
  var._KIND_ANNOTATION = create_future();
  var._NAME_ANNOTATION = create_future();
  var._NODE_ANNOTATION = create_future();
  var._SCOPE_ANNOTATION = create_future();
  var._TYPE_ANNOTATION = create_future();
  var._ANNOTATION_ITEM = create_future();
  var._ANNOTATION = create_future();
  var._ANNOTATIONS = create_future();
  var._C_CODE_REMARK = create_future();
  var._C_CODE_REMARKS = create_future();
  var._SOURCE = create_future();
  var._C_CODE = create_future();
  var._META_FRAGMENT = create_future();
  var._FRAGMENT = create_future();
  define_single_assign_static("compiler", "parse_meta_instruction", get__compiler__parse_meta_instruction, &var.compiler__parse_meta_instruction);
  define_single_assign_static("compiler", "parse_statement", get__compiler__parse_statement, &var.compiler__parse_statement);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__parser(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("parser");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "ANY_CHARACTER", &get__ANY_CHARACTER, &get_value_or_future__ANY_CHARACTER);
  use_read_only(NULL, "ATTRIBUTE_KIND", &get__ATTRIBUTE_KIND, &get_value_or_future__ATTRIBUTE_KIND);
  use_read_only(NULL, "CONTINUATION_PARAMETER", &get__CONTINUATION_PARAMETER, &get_value_or_future__CONTINUATION_PARAMETER);
  use_read_only(NULL, "DIGIT", &get__DIGIT, &get_value_or_future__DIGIT);
  use_read_only(NULL, "END_OF_TEXT", &get__END_OF_TEXT, &get_value_or_future__END_OF_TEXT);
  use_read_only(NULL, "INFIX_PRECEDENCE", &get__INFIX_PRECEDENCE, &get_value_or_future__INFIX_PRECEDENCE);
  use_read_only(NULL, "IN_OUT_PARAMETER", &get__IN_OUT_PARAMETER, &get_value_or_future__IN_OUT_PARAMETER);
  use_read_only(NULL, "IN_PARAMETER", &get__IN_PARAMETER, &get_value_or_future__IN_PARAMETER);
  use_read_only(NULL, "LETTER", &get__LETTER, &get_value_or_future__LETTER);
  use_read_only(NULL, "METHOD_KIND", &get__METHOD_KIND, &get_value_or_future__METHOD_KIND);
  use_read_only(NULL, "MYSELF_PARAMETER", &get__MYSELF_PARAMETER, &get_value_or_future__MYSELF_PARAMETER);
  use_read_only(NULL, "NAME", &get__NAME, &get_value_or_future__NAME);
  use_read_only(NULL, "NONE", &get__NONE, &get_value_or_future__NONE);
  use_read_only(NULL, "OUT_PARAMETER", &get__OUT_PARAMETER, &get_value_or_future__OUT_PARAMETER);
  use_read_only(NULL, "POLYMORPHIC", &get__POLYMORPHIC, &get_value_or_future__POLYMORPHIC);
  use_read_only(NULL, "PRINTABLE_CHARACTER", &get__PRINTABLE_CHARACTER, &get_value_or_future__PRINTABLE_CHARACTER);
  use_read_only(NULL, "SyntaxError", &get__SyntaxError, &get_value_or_future__SyntaxError);
  use_read_only(NULL, "all_of", &get__all_of, &get_value_or_future__all_of);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_read_only(NULL, "arguments_span", &get__arguments_span, &get_value_or_future__arguments_span);
  use_read_only(NULL, "assignment", &get__assignment, &get_value_or_future__assignment);
  use_read_only(NULL, "attribute_function_pair", &get__attribute_function_pair, &get_value_or_future__attribute_function_pair);
  use_read_only(NULL, "attribute_kind_of", &get__attribute_kind_of, &get_value_or_future__attribute_kind_of);
  use_polymorphic_function(NULL, "attribute_of", &get__attribute_of, &poly_idx__attribute_of);
  use_read_only(NULL, "attribute_value_pair", &get__attribute_value_pair, &get_value_or_future__attribute_value_pair);
  use_read_only(NULL, "backquoted", &get__backquoted, &get_value_or_future__backquoted);
  use_read_only(NULL, "base_of", &get__base_of, &get_value_or_future__base_of);
  use_read_only(NULL, "behind", &get__behind, &get_value_or_future__behind);
  use_read_only(NULL, "body", &get__body, &get_value_or_future__body);
  use_read_only(NULL, "c_body", &get__c_body, &get_value_or_future__c_body);
  use_read_only(NULL, "c_code", &get__c_code, &get_value_or_future__c_code);
  use_read_only(NULL, "capture", &get__capture, &get_value_or_future__capture);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "character", &get__character, &get_value_or_future__character);
  use_read_only(NULL, "character_literal", &get__character_literal, &get_value_or_future__character_literal);
  use_read_only(NULL, "character_names", &get__character_names, &get_value_or_future__character_names);
  use_read_only(NULL, "check_node", &get__check_node, &get_value_or_future__check_node);
  use_single_assign_dynamic("compiler", "current_fragment", &get__compiler__current_fragment, &define__compiler__current_fragment);
  use_read_only("compiler", "source_of", &get__compiler__source_of, &get_value_or_future__compiler__source_of);
  use_read_only("compiler", "text_of", &get__compiler__text_of, &get_value_or_future__compiler__text_of);
  use_read_only(NULL, "continuation_of", &get__continuation_of, &get_value_or_future__continuation_of);
  use_read_only(NULL, "count_occurrences", &get__count_occurrences, &get_value_or_future__count_occurrences);
  use_read_only(NULL, "current_fragment", &get__current_fragment, &get_value_or_future__current_fragment);
  use_read_only(NULL, "data_instruction", &get__data_instruction, &get_value_or_future__data_instruction);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "default_value_of", &get__default_value_of, &get_value_or_future__default_value_of);
  use_read_only(NULL, "define_dynamic_multi", &get__define_dynamic_multi, &get_value_or_future__define_dynamic_multi);
  use_read_only(NULL, "define_dynamic_single", &get__define_dynamic_single, &get_value_or_future__define_dynamic_single);
  use_read_only(NULL, "define_static_multi", &get__define_static_multi, &get_value_or_future__define_static_multi);
  use_read_only(NULL, "define_static_single", &get__define_static_single, &get_value_or_future__define_static_single);
  use_polymorphic_function(NULL, "defined_names_of", &get__defined_names_of, &poly_idx__defined_names_of);
  use_read_write(NULL, "defined_namespaces", &get__defined_namespaces, &set__defined_namespaces);
  use_read_write(NULL, "dependent_data", &get__dependent_data, &set__dependent_data);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "do_extract_documentation", &get__do_extract_documentation, &get_value_or_future__do_extract_documentation);
  use_read_only(NULL, "do_pretty_print", &get__do_pretty_print, &get_value_or_future__do_pretty_print);
  use_read_only(NULL, "do_show_brief_messages", &get__do_show_brief_messages, &get_value_or_future__do_show_brief_messages);
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_read_only(NULL, "edump", &get__edump, &get_value_or_future__edump);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_polymorphic_function(NULL, "end_position_of", &get__end_position_of, &poly_idx__end_position_of);
  use_read_only(NULL, "eprint_source", &get__eprint_source, &get_value_or_future__eprint_source);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "ewriteln", &get__ewriteln, &get_value_or_future__ewriteln);
  use_read_only(NULL, "exit", &get__exit, &get_value_or_future__exit);
  use_read_only(NULL, "expression", &get__expression, &get_value_or_future__expression);
  use_polymorphic_function(NULL, "expression_of", &get__expression_of, &poly_idx__expression_of);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "followed_by", &get__followed_by, &get_value_or_future__followed_by);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "for_each_from_to", &get__for_each_from_to, &get_value_or_future__for_each_from_to);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_polymorphic_function(NULL, "fragment_of", &get__fragment_of, &poly_idx__fragment_of);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
  use_read_only(NULL, "function_call", &get__function_call, &get_value_or_future__function_call);
  use_polymorphic_function(NULL, "functor_of", &get__functor_of, &poly_idx__functor_of);
  use_read_only("grammar", "current_node", &get__grammar__current_node, &get_value_or_future__grammar__current_node);
  use_polymorphic_function("grammar", "match", &get__grammar__match, &poly_idx__grammar__match);
  use_read_only(NULL, "identifier", &get__identifier, &get_value_or_future__identifier);
  use_polymorphic_function(NULL, "identifier_of", &get__identifier_of, &poly_idx__identifier_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "include_instruction", &get__include_instruction, &get_value_or_future__include_instruction);
  use_read_write(NULL, "included_files", &get__included_files, &set__included_files);
  use_read_only(NULL, "indent_marker", &get__indent_marker, &get_value_or_future__indent_marker);
  use_polymorphic_function(NULL, "inherited_names_of", &get__inherited_names_of, &poly_idx__inherited_names_of);
  use_read_only(NULL, "inspect_node", &get__inspect_node, &get_value_or_future__inspect_node);
  use_read_only(NULL, "is_a_backquoted_expression", &get__is_a_backquoted_expression, &get_value_or_future__is_a_backquoted_expression);
  use_read_only(NULL, "is_a_character", &get__is_a_character, &get_value_or_future__is_a_character);
  use_read_only(NULL, "is_a_destination", &get__is_a_destination, &get_value_or_future__is_a_destination);
  use_read_only(NULL, "is_a_function_call", &get__is_a_function_call, &get_value_or_future__is_a_function_call);
  use_read_only(NULL, "is_a_letter", &get__is_a_letter, &get_value_or_future__is_a_letter);
  use_polymorphic_function(NULL, "is_a_method_definition", &get__is_a_method_definition, &poly_idx__is_a_method_definition);
  use_read_only(NULL, "is_a_polymorphic_function_constant", &get__is_a_polymorphic_function_constant, &get_value_or_future__is_a_polymorphic_function_constant);
  use_read_only(NULL, "is_a_remark", &get__is_a_remark, &get_value_or_future__is_a_remark);
  use_read_only(NULL, "is_a_return", &get__is_a_return, &get_value_or_future__is_a_return);
  use_read_only(NULL, "is_a_static_single_definition", &get__is_a_static_single_definition, &get_value_or_future__is_a_static_single_definition);
  use_read_only(NULL, "is_a_string", &get__is_a_string, &get_value_or_future__is_a_string);
  use_polymorphic_function(NULL, "is_a_string_template", &get__is_a_string_template, &poly_idx__is_a_string_template);
  use_polymorphic_function(NULL, "is_an_attribute_access", &get__is_an_attribute_access, &poly_idx__is_an_attribute_access);
  use_read_only(NULL, "is_an_attribute_value_pair", &get__is_an_attribute_value_pair, &get_value_or_future__is_an_attribute_value_pair);
  use_read_only(NULL, "is_an_expanded_item", &get__is_an_expanded_item, &get_value_or_future__is_an_expanded_item);
  use_read_only(NULL, "is_an_identifier", &get__is_an_identifier, &get_value_or_future__is_an_identifier);
  use_read_only(NULL, "is_an_input_output_argument", &get__is_an_input_output_argument, &get_value_or_future__is_an_input_output_argument);
  use_read_only(NULL, "is_an_optional_item", &get__is_an_optional_item, &get_value_or_future__is_an_optional_item);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_polymorphic_function(NULL, "is_in_infix_notation", &get__is_in_infix_notation, &poly_idx__is_in_infix_notation);
  use_polymorphic_function(NULL, "is_in_numeric_notation", &get__is_in_numeric_notation, &poly_idx__is_in_numeric_notation);
  use_read_only(NULL, "is_left_associative", &get__is_left_associative, &get_value_or_future__is_left_associative);
  use_polymorphic_function(NULL, "is_not_used", &get__is_not_used, &poly_idx__is_not_used);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "is_used_as_a_destination", &get__is_used_as_a_destination, &get_value_or_future__is_used_as_a_destination);
  use_read_only(NULL, "is_used_as_a_polymorphic_function", &get__is_used_as_a_polymorphic_function, &get_value_or_future__is_used_as_a_polymorphic_function);
  use_read_only(NULL, "kind_of", &get__kind_of, &get_value_or_future__kind_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "line_end_specifier_of", &get__line_end_specifier_of, &get_value_or_future__line_end_specifier_of);
  use_read_only(NULL, "line_no_of", &get__line_no_of, &get_value_or_future__line_no_of);
  use_read_only(NULL, "link_instruction", &get__link_instruction, &get_value_or_future__link_instruction);
  use_read_write(NULL, "linked_libraries", &get__linked_libraries, &set__linked_libraries);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_polymorphic_function(NULL, "lowest_precedence_of", &get__lowest_precedence_of, &poly_idx__lowest_precedence_of);
  use_read_only(NULL, "many", &get__many, &get_value_or_future__many);
  use_read_only(NULL, "match", &get__match, &get_value_or_future__match);
  use_polymorphic_function(NULL, "message_of", &get__message_of, &poly_idx__message_of);
  use_read_only(NULL, "modify_node", &get__modify_node, &get_value_or_future__modify_node);
  use_read_only(NULL, "module_name", &get__module_name, &get_value_or_future__module_name);
  use_read_only(NULL, "multi_capture", &get__multi_capture, &get_value_or_future__multi_capture);
  use_read_only(NULL, "multi_line_string", &get__multi_line_string, &get_value_or_future__multi_line_string);
  use_read_only(NULL, "multi_span", &get__multi_span, &get_value_or_future__multi_span);
  use_polymorphic_function(NULL, "name_of", &get__name_of, &poly_idx__name_of);
  use_polymorphic_function(NULL, "namespace_alias_of", &get__namespace_alias_of, &poly_idx__namespace_alias_of);
  use_read_only(NULL, "namespace_instruction", &get__namespace_instruction, &get_value_or_future__namespace_instruction);
  use_read_write(NULL, "namespace_mappings", &get__namespace_mappings, &set__namespace_mappings);
  use_polymorphic_function(NULL, "namespace_of", &get__namespace_of, &poly_idx__namespace_of);
  use_read_only(NULL, "newline", &get__newline, &get_value_or_future__newline);
  use_read_only("node", "filemask_of", &get__node__filemask_of, &get_value_or_future__node__filemask_of);
  use_read_only("node", "filename_of", &get__node__filename_of, &get_value_or_future__node__filename_of);
  use_read_only("node", "scope_of", &get__node__scope_of, &get_value_or_future__node__scope_of);
  use_polymorphic_function("node", "text_of", &get__node__text_of, &poly_idx__node__text_of);
  use_read_only("node", "type_of", &get__node__type_of, &get_value_or_future__node__type_of);
  use_polymorphic_function("node", "value_of", &get__node__value_of, &poly_idx__node__value_of);
  use_read_only(NULL, "node_of", &get__node_of, &get_value_or_future__node_of);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_read_only(NULL, "not_followed_by", &get__not_followed_by, &get_value_or_future__not_followed_by);
  use_read_only(NULL, "numeric_literal", &get__numeric_literal, &get_value_or_future__numeric_literal);
  use_read_only(NULL, "operator_symbol", &get__operator_symbol, &get_value_or_future__operator_symbol);
  use_read_only(NULL, "operators_of", &get__operators_of, &get_value_or_future__operators_of);
  use_read_only(NULL, "optional", &get__optional, &get_value_or_future__optional);
  use_read_only(NULL, "outdent_marker", &get__outdent_marker, &get_value_or_future__outdent_marker);
  use_read_only(NULL, "parameter_kind_of", &get__parameter_kind_of, &get_value_or_future__parameter_kind_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_polymorphic_function(NULL, "parent_of", &get__parent_of, &poly_idx__parent_of);
  use_read_only(NULL, "peek", &get__peek, &get_value_or_future__peek);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_read_only(NULL, "polymorphic_function", &get__polymorphic_function, &get_value_or_future__polymorphic_function);
  use_read_only(NULL, "polymorphic_function_with_setter", &get__polymorphic_function_with_setter, &get_value_or_future__polymorphic_function_with_setter);
  use_read_only(NULL, "pop", &get__pop, &get_value_or_future__pop);
  use_read_only(NULL, "precedence", &get__precedence, &get_value_or_future__precedence);
  use_read_only(NULL, "procedure_call", &get__procedure_call, &get_value_or_future__procedure_call);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "put", &get__put, &get_value_or_future__put);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "remark_argument", &get__remark_argument, &get_value_or_future__remark_argument);
  use_polymorphic_function(NULL, "remark_lines_of", &get__remark_lines_of, &poly_idx__remark_lines_of);
  use_read_only(NULL, "remark_statement", &get__remark_statement, &get_value_or_future__remark_statement);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_read_only(NULL, "require_instruction", &get__require_instruction, &get_value_or_future__require_instruction);
  use_read_write(NULL, "required_modules", &get__required_modules, &set__required_modules);
  use_read_only(NULL, "result_count_of", &get__result_count_of, &get_value_or_future__result_count_of);
  use_read_only(NULL, "return_statement", &get__return_statement, &get_value_or_future__return_statement);
  use_read_only(NULL, "sequence", &get__sequence, &get_value_or_future__sequence);
  use_read_only(NULL, "set_field", &get__set_field, &get_value_or_future__set_field);
  use_read_only(NULL, "set_node", &get__set_node, &get_value_or_future__set_node);
  use_read_only(NULL, "some", &get__some, &get_value_or_future__some);
  use_read_only(NULL, "source_of", &get__source_of, &get_value_or_future__source_of);
  use_polymorphic_function(NULL, "source_position_of", &get__source_position_of, &poly_idx__source_position_of);
  use_read_only(NULL, "span", &get__span, &get_value_or_future__span);
  use_polymorphic_function(NULL, "statements_of", &get__statements_of, &poly_idx__statements_of);
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
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only("std", "value_range", &get__std__value_range, &get_value_or_future__std__value_range);
  use_read_only(NULL, "std_identifier", &get__std_identifier, &get_value_or_future__std_identifier);
  use_read_only(NULL, "string_literal", &get__string_literal, &get_value_or_future__string_literal);
  use_read_only(NULL, "strip", &get__strip, &get_value_or_future__strip);
  use_read_only(NULL, "table", &get__table, &get_value_or_future__table);
  use_read_only(NULL, "to_integer", &get__to_integer, &get_value_or_future__to_integer);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_read_only(NULL, "to_upper_case", &get__to_upper_case, &get_value_or_future__to_upper_case);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "truncate_behind", &get__truncate_behind, &get_value_or_future__truncate_behind);
  use_read_only(NULL, "truncate_from", &get__truncate_from, &get_value_or_future__truncate_from);
  use_read_only("types", "grammar_object", &get__types__grammar_object, &get_value_or_future__types__grammar_object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unique_item", &get__unique_item, &get_value_or_future__unique_item);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "update_each", &get__update_each, &get_value_or_future__update_each);
  use_polymorphic_function(NULL, "used_names_of", &get__used_names_of, &poly_idx__used_names_of);
  use_read_write(NULL, "used_namespaces", &get__used_namespaces, &set__used_namespaces);
  use_read_only(NULL, "using_instruction", &get__using_instruction, &get_value_or_future__using_instruction);
  use_polymorphic_function(NULL, "variable_kind_of", &get__variable_kind_of, &poly_idx__variable_kind_of);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  define_method("types", "syntax_error", poly_idx__grammar__match, func__types__syntax_error__grammar__match_1);
  define_method("types", "unexpected_input_error", poly_idx__grammar__match, func__types__unexpected_input_error__grammar__match_1);
  update_start_p = node_p;
  def_attribute(&var._dump_stream, poly_idx__grammar__match, func__dump_stream__grammar__match_1);
  update_start_p = node_p;
  def_attribute(&var._dump, poly_idx__grammar__match, func__dump__grammar__match_1);
  update_start_p = node_p;
  def_attribute(&var._dump3, poly_idx__grammar__match, func__dump3__grammar__match_1);
  update_start_p = node_p;
  def_attribute(&var._dump5, poly_idx__grammar__match, func__dump5__grammar__match_1);
  define_method("types", "store_arguments_index", poly_idx__grammar__match, func__types__store_arguments_index__grammar__match_1);
  define_method("types", "inline", poly_idx__grammar__match, func__types__inline__grammar__match_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__parser(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.compiler__std_identifier, &func__compiler__std_identifier_1);
  assign_variable(&var._print_message, &func__print_message_1);
  assign_variable(&var.compiler__Warning, &func__compiler__Warning_1);
  assign_variable(&var._ExitWithSyntaxError, &func__ExitWithSyntaxError_1);
  assign_variable(&var.compiler__SyntaxError, &func__compiler__SyntaxError_1);
  assign_variable(&var._ParseError, &func__ParseError_1);
  assign_value(&var.types__syntax_error, get__types__grammar_object());
  assign_variable(&var._syntax_error, &func__syntax_error_1);
  assign_value(&var.types__unexpected_input_error, get__types__grammar_object());
  assign_variable(&var._unexpected_input_error, &func__unexpected_input_error_1);
  assign_value(&var._dump_stream, get__types__grammar_object());
  assign_variable(&var.compiler__strip, &func__compiler__strip_1);
  assign_value(&var._dump, get__types__grammar_object());
  assign_value(&var._dump3, get__types__grammar_object());
  assign_value(&var._dump5, get__types__grammar_object());
  assign_value(&var.compiler__HIGHEST_PRECEDENCE, number__99);
  assign_value(&var.compiler__INFIX_PRECEDENCE, number__6);
  assign_variable(&var.compiler__precedence, &func__compiler__precedence_1);
  assign_variable(&var.compiler__is_left_associative, &func__compiler__is_left_associative_1);
  assign_variable(&var._is_right_associative, &func__is_right_associative_1);
  assign_variable(&var._infix_operator, &func__infix_operator_1);
  assign_variable(&var._interleaved, &func__interleaved_1);
  maybe_initialize_future(get__arguments_index(), get__undefined());
  assign_value(&var.types__store_arguments_index, get__types__grammar_object());
  assign_variable(&var._store_arguments_index, &func__store_arguments_index_1);
  maybe_initialize_future(get__within_inline_expression(), get__false());
  assign_value(&var.types__inline, get__types__grammar_object());
  assign_variable(&var._inline, &func__inline_1);
  assign_variable(&var._expect, &func__expect_1);
  assign_variable(&var.compiler__arguments_span, &func__compiler__arguments_span_1);
  assign_variable(&var._check_functor, &func__check_functor_1);
  assign_variable(&var._check_arguments, &func__check_arguments_1);
  assign_variable(&var._CHECK_ARGUMENTS, &func__CHECK_ARGUMENTS_1);
  assign_variable(&var.compiler__parse_meta_instruction, &func__compiler__parse_meta_instruction_1);
  assign_variable(&var.compiler__parse_statement, &func__compiler__parse_statement_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__parser(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__parser);
}
