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
  NODE *_dump_stream;
  NODE *_dump;
  NODE *_dump3;
  NODE *_dump5;
  NODE *_precedence_table;
  NODE *_NOT_INLINE;
  NODE *_NEWLINE;
  NODE *_INDENT;
  NODE *_OUTDENT;
  NODE *_HASHTAG;
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
  "dump_stream",
  "dump",
  "dump3",
  "dump5",
  "precedence_table",
  "NOT_INLINE",
  "NEWLINE",
  "INDENT",
  "OUTDENT",
  "HASHTAG",
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
static NODE *func__compiler__std_identifier;
static void entry__compiler__std_identifier(void);
static FRAME_INFO frame__compiler__std_identifier = {1, {"name"}};
static NODE *string__fa724815d896ba8;
static NODE *get__compiler__std_identifier(void) {
  return var.compiler__std_identifier;
}
static NODE *func__print_message;
static void entry__print_message(void);
static FRAME_INFO frame__print_message = {12, {"fragment", "offset", "msg_type", "msg", "source", "pos", "line_no", "line_offset", "n", "text", "rest", "line"}};
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
static NODE *func__compiler__Warning;
static void entry__compiler__Warning(void);
static FRAME_INFO frame__compiler__Warning = {2, {"obj", "msg"}};
static void cont__compiler__Warning_2(void);
static void cont__compiler__Warning_3(void);
static NODE *string__eed8078214c9e0bd;
static NODE *get__compiler__Warning(void) {
  return var.compiler__Warning;
}
static NODE *func__ExitWithSyntaxError;
static void entry__ExitWithSyntaxError(void);
static FRAME_INFO frame__ExitWithSyntaxError = {3, {"fragment", "offset", "msg"}};
static NODE *string__ae3c04ed6f185295;
static void cont__ExitWithSyntaxError_3(void);
static NODE *func__compiler__SyntaxError;
static void entry__compiler__SyntaxError(void);
static FRAME_INFO frame__compiler__SyntaxError = {2, {"obj", "msg"}};
static void cont__compiler__SyntaxError_2(void);
static void cont__compiler__SyntaxError_3(void);
static NODE *get__compiler__SyntaxError(void) {
  return var.compiler__SyntaxError;
}
static NODE *func__ParseError;
static void entry__ParseError(void);
static FRAME_INFO frame__ParseError = {2, {"stream", "msg"}};
static void cont__ParseError_2(void);
static NODE *get__types__syntax_error(void) {
  return var.types__syntax_error;
}
static NODE *func__types__syntax_error___grammar__match;
static void entry__types__syntax_error___grammar__match(void);
static FRAME_INFO frame__types__syntax_error___grammar__match = {2, {"self", "stream"}};
static void cont__types__syntax_error___grammar__match_2(void);
static NODE *func__syntax_error;
static void entry__syntax_error(void);
static FRAME_INFO frame__syntax_error = {1, {"message"}};
static NODE *get__types__unexpected_input_error(void) {
  return var.types__unexpected_input_error;
}
static NODE *func__types__unexpected_input_error___grammar__match;
static void entry__types__unexpected_input_error___grammar__match(void);
static FRAME_INFO frame__types__unexpected_input_error___grammar__match = {3, {"self", "stream", "expression"}};
static void cont__types__unexpected_input_error___grammar__match_2(void);
static void cont__types__unexpected_input_error___grammar__match_3(void);
static NODE *func__types__unexpected_input_error__grammar__match_4;
static void entry__types__unexpected_input_error__grammar__match_4(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_4 = {1, {"expression"}};
static void cont__types__unexpected_input_error__grammar__match_5(void);
static void cont__types__unexpected_input_error___grammar__match_6(void);
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
static NODE *func__unexpected_input_error;
static void entry__unexpected_input_error(void);
static FRAME_INFO frame__unexpected_input_error = {1, {"expression"}};
static NODE *func__dump_stream___grammar__match;
static void entry__dump_stream___grammar__match(void);
static FRAME_INFO frame__dump_stream___grammar__match = {2, {"self", "stream"}};
static NODE *string__8c16e735f8cebe3d;
static void cont__dump_stream___grammar__match_3(void);
static void cont__dump_stream___grammar__match_4(void);
static void cont__dump_stream___grammar__match_5(void);
static NODE *string__881ef7b4fade9e7f;
static void cont__dump_stream___grammar__match_7(void);
static NODE *func__compiler__strip;
static void entry__compiler__strip(void);
static FRAME_INFO frame__compiler__strip = {1, {"node"}};
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
static NODE *func__dump___grammar__match;
static void entry__dump___grammar__match(void);
static FRAME_INFO frame__dump___grammar__match = {2, {"self", "stream"}};
static void cont__dump___grammar__match_2(void);
static NODE *string__665e06ec4dcad6be;
static void cont__dump___grammar__match_4(void);
static NODE *func__dump3___grammar__match;
static void entry__dump3___grammar__match(void);
static FRAME_INFO frame__dump3___grammar__match = {2, {"self", "stream"}};
static void cont__dump3___grammar__match_2(void);
static void cont__dump3___grammar__match_3(void);
static NODE *func__dump5___grammar__match;
static void entry__dump5___grammar__match(void);
static FRAME_INFO frame__dump5___grammar__match = {2, {"self", "stream"}};
static void cont__dump5___grammar__match_2(void);
static void cont__dump5___grammar__match_3(void);
static NODE *get__compiler__HIGHEST_PRECEDENCE(void) {
  return var.compiler__HIGHEST_PRECEDENCE;
}
static NODE *get__compiler__INFIX_PRECEDENCE(void) {
  return var.compiler__INFIX_PRECEDENCE;
}
static NODE *func__compiler__precedence;
static void entry__compiler__precedence(void);
static FRAME_INFO frame__compiler__precedence = {1, {"op"}};
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
static NODE *func__compiler__is_left_associative;
static void entry__compiler__is_left_associative(void);
static FRAME_INFO frame__compiler__is_left_associative = {1, {"prec"}};
static void cont__compiler__is_left_associative_2(void);
static NODE *get__compiler__is_left_associative(void) {
  return var.compiler__is_left_associative;
}
static NODE *func__is_right_associative;
static void entry__is_right_associative(void);
static FRAME_INFO frame__is_right_associative = {1, {"prec"}};
static void cont__is_right_associative_2(void);
static void cont__is_right_associative_3(void);
static NODE *func__infix_operator;
static void entry__infix_operator(void);
static FRAME_INFO frame__infix_operator = {1, {"operator"}};
static void cont__infix_operator_2(void);
static void cont__infix_operator_3(void);
static NODE *func__interleaved;
static void entry__interleaved(void);
static FRAME_INFO frame__interleaved = {2, {"expression", "separator"}};
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
static NODE *func__types__store_arguments_index___grammar__match;
static void entry__types__store_arguments_index___grammar__match(void);
static FRAME_INFO frame__types__store_arguments_index___grammar__match = {3, {"self", "stream", "return__1"}};
static void cont__types__store_arguments_index___grammar__match_2(void);
static void cont__types__store_arguments_index___grammar__match_3(void);
static void cont__types__store_arguments_index___grammar__match_4(void);
static void cont__types__store_arguments_index___grammar__match_5(void);
static NODE *func__store_arguments_index;
static void entry__store_arguments_index(void);
static FRAME_INFO frame__store_arguments_index = {1, {"expression"}};
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
static NODE *func__types__inline___grammar__match;
static void entry__types__inline___grammar__match(void);
static FRAME_INFO frame__types__inline___grammar__match = {3, {"self", "stream", "return__1"}};
static void cont__types__inline___grammar__match_2(void);
static void cont__types__inline___grammar__match_3(void);
static NODE *func__inline;
static void entry__inline(void);
static FRAME_INFO frame__inline = {1, {"expression"}};
static NODE *func__expect;
static void entry__expect(void);
static FRAME_INFO frame__expect = {2, {"expression", "description"}};
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
static NODE *func__compiler__arguments_span;
static void entry__compiler__arguments_span(void);
static FRAME_INFO frame__compiler__arguments_span = {1, {"expression"}};
static void cont__compiler__arguments_span_2(void);
static NODE *get__compiler__arguments_span(void) {
  return var.compiler__arguments_span;
}
static NODE *get__compiler__WHITESPACE(void) {
  return var.compiler__WHITESPACE;
}
static NODE *func__check_functor;
static void entry__check_functor(void);
static FRAME_INFO frame__check_functor = {1, {"functor"}};
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
static NODE *func__check_arguments;
static void entry__check_arguments(void);
static FRAME_INFO frame__check_arguments = {9, {"node", "kind", "wanted_outputs", "wanted_inputs", "outputs", "inputs", "contains_attribute_value_pair", "contains_simple_input_argument", "add_argument"}};
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
static NODE *string__4f498b003024119a;
static void cont__check_arguments_36(void);
static NODE *func__check_arguments_37;
static void entry__check_arguments_37(void);
static FRAME_INFO frame__check_arguments_37 = {1, {"contains_attribute_value_pair"}};
static void cont__check_arguments_38(void);
static NODE *func__check_arguments_39;
static void entry__check_arguments_39(void);
static FRAME_INFO frame__check_arguments_39 = {2, {"kind", "wanted_outputs"}};
static NODE *string__47a9393383380498;
static void cont__check_arguments_41(void);
static void cont__check_arguments_42(void);
static NODE *func__check_arguments_43;
static void entry__check_arguments_43(void);
static FRAME_INFO frame__check_arguments_43 = {4, {"wanted_outputs", "outputs", "node", "kind"}};
static void cont__check_arguments_44(void);
static NODE *func__check_arguments_45;
static void entry__check_arguments_45(void);
static FRAME_INFO frame__check_arguments_45 = {2, {"node", "kind"}};
static NODE *string__5fa0d5b2a9ee383d;
static void cont__check_arguments_47(void);
static void cont__check_arguments_48(void);
static void cont__check_arguments_49(void);
static NODE *func__check_arguments_50;
static void entry__check_arguments_50(void);
static FRAME_INFO frame__check_arguments_50 = {2, {"node", "kind"}};
static NODE *string__1b6e5ce3b21cbf2f;
static void cont__check_arguments_52(void);
static void cont__check_arguments_53(void);
static void cont__check_arguments_54(void);
static NODE *func__check_arguments_55;
static void entry__check_arguments_55(void);
static FRAME_INFO frame__check_arguments_55 = {6, {"wanted_inputs", "inputs", "node", "kind", "min_inputs", "max_inputs"}};
static NODE *unique__ONE_OR_MORE;
static void cont__check_arguments_56(void);
static NODE *func__check_arguments_57;
static void entry__check_arguments_57(void);
static FRAME_INFO frame__check_arguments_57 = {1, {"wanted_inputs"}};
static NODE *func__check_arguments_58;
static void entry__check_arguments_58(void);
static FRAME_INFO frame__check_arguments_58 = {0, {}};
static void cont__check_arguments_59(void);
static void cont__check_arguments_60(void);
static NODE *func__check_arguments_61;
static void entry__check_arguments_61(void);
static FRAME_INFO frame__check_arguments_61 = {1, {"wanted_inputs"}};
static NODE *func__check_arguments_62;
static void entry__check_arguments_62(void);
static FRAME_INFO frame__check_arguments_62 = {0, {}};
static void cont__check_arguments_63(void);
static void cont__check_arguments_64(void);
static NODE *func__check_arguments_65;
static void entry__check_arguments_65(void);
static FRAME_INFO frame__check_arguments_65 = {2, {"max_inputs", "inputs"}};
static void cont__check_arguments_66(void);
static void cont__check_arguments_67(void);
static NODE *func__check_arguments_68;
static void entry__check_arguments_68(void);
static FRAME_INFO frame__check_arguments_68 = {3, {"node", "kind", "first_input_argument"}};
static NODE *func__check_arguments_69;
static void entry__check_arguments_69(void);
static FRAME_INFO frame__check_arguments_69 = {3, {"break", "node", "first_input_argument"}};
static void cont__check_arguments_70(void);
static NODE *func__check_arguments_71;
static void entry__check_arguments_71(void);
static FRAME_INFO frame__check_arguments_71 = {3, {"argument", "first_input_argument", "break"}};
static void cont__check_arguments_72(void);
static NODE *func__check_arguments_73;
static void entry__check_arguments_73(void);
static FRAME_INFO frame__check_arguments_73 = {3, {"first_input_argument", "argument", "break"}};
static void cont__check_arguments_74(void);
static void cont__check_arguments_75(void);
static void cont__check_arguments_76(void);
static NODE *func__check_arguments_77;
static void entry__check_arguments_77(void);
static FRAME_INFO frame__check_arguments_77 = {2, {"node", "kind"}};
static NODE *string__ebee6487b4b0342b;
static void cont__check_arguments_79(void);
static void cont__check_arguments_80(void);
static void cont__check_arguments_81(void);
static NODE *func__check_arguments_82;
static void entry__check_arguments_82(void);
static FRAME_INFO frame__check_arguments_82 = {2, {"inputs", "min_inputs"}};
static void cont__check_arguments_83(void);
static void cont__check_arguments_84(void);
static NODE *func__check_arguments_85;
static void entry__check_arguments_85(void);
static FRAME_INFO frame__check_arguments_85 = {2, {"node", "kind"}};
static NODE *string__bb0c2c1e659a1755;
static void cont__check_arguments_87(void);
static NODE *func__CHECK_ARGUMENTS;
static void entry__CHECK_ARGUMENTS(void);
static FRAME_INFO frame__CHECK_ARGUMENTS = {3, {"kind", "wanted_outputs", "wanted_inputs"}};
static NODE *func__CHECK_ARGUMENTS_2;
static void entry__CHECK_ARGUMENTS_2(void);
static FRAME_INFO frame__CHECK_ARGUMENTS_2 = {4, {"node", "kind", "wanted_outputs", "wanted_inputs"}};
static NODE *func__compiler__parse_meta_instruction;
static void entry__compiler__parse_meta_instruction(void);
static FRAME_INFO frame__compiler__parse_meta_instruction = {5, {"fragment", "return__1", "source", "len", "cap"}};
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
static NODE *func__compiler__parse_statement;
static void entry__compiler__parse_statement(void);
static FRAME_INFO frame__compiler__parse_statement = {5, {"fragment", "return__1", "source", "len", "cap"}};
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
static void cont__361_3(void);
static void cont__361_4(void);
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
  {cont__216_40, NULL, 270, 276, 1, 15},
  {cont__230_5, NULL, 278, 278, 10, 29},
  {cont__231_1, NULL, 278, 278, 1, 50},
  {cont__231_2, NULL, 279, 279, 9, 34},
  {cont__232_1, NULL, 279, 279, 1, 61},
  {cont__232_2, NULL, 280, 280, 10, 36},
  {cont__233_1, NULL, 280, 280, 1, 64},
  {cont__233_2, NULL, 281, 281, 10, 25},
  {cont__234_1, NULL, 281, 281, 1, 42},
  {cont__234_2, NULL, 291, 291, 1, 31},
  {cont__237_1, NULL, 292, 292, 37, 52},
  {cont__238_1, NULL, 292, 292, 1, 53},
  {cont__238_2, NULL, 293, 293, 1, 23},
  {cont__239_1, NULL, 295, 303, 1, 42},
  {cont__240_3, NULL, 305, 313, 1, 42},
  {cont__241_4, NULL, 315, 322, 1, 47},
  {cont__242_3, NULL, 326, 326, 5, 24},
  {cont__243_1, NULL, 328, 328, 5, 25},
  {cont__243_2, NULL, },
  {cont__243_5, NULL, 335, 335, 9, 29},
  {cont__243_6, NULL, },
  {cont__243_8, NULL, },
  {cont__243_9, NULL, 324, 336, 1, 23},
  {cont__243_10, NULL, 340, 340, 5, 24},
  {cont__244_1, NULL, 342, 342, 5, 22},
  {cont__244_2, NULL, 343, 343, 5, 25},
  {cont__244_3, NULL, },
  {cont__244_10, NULL, 352, 352, 9, 29},
  {cont__244_11, NULL, },
  {cont__244_12, NULL, },
  {cont__244_13, NULL, 338, 353, 1, 23},
  {cont__244_14, NULL, 357, 357, 5, 24},
  {cont__245_1, NULL, 359, 359, 5, 30},
  {cont__245_2, NULL, 360, 360, 5, 16},
  {cont__245_3, NULL, 361, 361, 5, 25},
  {cont__245_4, NULL, 355, 361, 1, 26},
  {cont__245_5, NULL, 366, 366, 11, 24},
  {cont__246_2, NULL, 366, 366, 38, 46},
  {cont__246_3, NULL, 366, 366, 33, 47},
  {cont__246_4, NULL, 366, 366, 1, 47},
  {cont__246_5, NULL, 371, 371, 5, 33},
  {cont__247_1, NULL, 374, 374, 5, 39},
  {cont__247_2, NULL, },
  {cont__247_13, NULL, 368, 383, 1, 43},
  {cont__247_15, NULL, 389, 389, 5, 35},
  {cont__248_1, NULL, 390, 390, 5, 30},
  {cont__248_2, NULL, 393, 393, 9, 27},
  {cont__248_3, NULL, },
  {cont__248_6, NULL, 397, 397, 9, 34},
  {cont__248_7, NULL, },
  {cont__248_8, NULL, },
  {cont__248_9, NULL, },
  {cont__248_30, NULL, 385, 413, 1, 52},
  {cont__248_32, NULL, 419, 419, 5, 31},
  {cont__249_1, NULL, 420, 420, 5, 30},
  {cont__249_2, NULL, },
  {cont__249_11, NULL, 415, 428, 1, 43},
  {cont__249_13, NULL, 430, 430, 16, 40},
  {cont__250_1, NULL, 430, 430, 1, 41},
  {cont__250_2, NULL, 431, 431, 26, 36},
  {cont__251_2, NULL, 431, 431, 13, 37},
  {cont__251_3, NULL, 431, 431, 55, 67},
  {cont__251_4, NULL, 431, 431, 50, 68},
  {cont__251_5, NULL, 431, 431, 1, 68},
  {cont__251_6, NULL, 437, 437, 5, 33},
  {cont__252_1, NULL, 438, 438, 5, 41},
  {cont__252_2, NULL, },
  {cont__252_12, NULL, 433, 446, 1, 41},
  {cont__252_14, NULL, 452, 452, 5, 30},
  {cont__253_1, NULL, 453, 453, 5, 41},
  {cont__253_2, NULL, },
  {cont__253_12, NULL, 448, 461, 1, 43},
  {cont__253_14, NULL, 463, 463, 12, 44},
  {cont__254_1, NULL, 463, 463, 1, 45},
  {cont__254_2, NULL, 464, 464, 24, 34},
  {cont__255_1, NULL, 464, 464, 11, 35},
  {cont__255_2, NULL, 464, 464, 49, 57},
  {cont__255_3, NULL, 464, 464, 44, 58},
  {cont__255_4, NULL, 464, 464, 1, 58},
  {cont__255_5, NULL, 470, 470, 5, 30},
  {cont__256_1, NULL, 471, 471, 5, 39},
  {cont__256_2, NULL, },
  {cont__256_11, NULL, 466, 479, 1, 41},
  {cont__256_13, NULL, 483, 483, 5, 50},
  {cont__257_1, NULL, 484, 484, 52, 73},
  {cont__257_2, NULL, 484, 484, 34, 73},
  {cont__257_3, NULL, 484, 484, 14, 74},
  {cont__257_4, NULL, 484, 484, 5, 75},
  {cont__257_5, NULL, 481, 484, 1, 76},
  {cont__257_6, NULL, 505, 505, 44, 68},
  {cont__258_1, NULL, 505, 506, 1, 40},
  {cont__258_2, NULL, 513, 513, 22, 53},
  {cont__259_1, NULL, 513, 513, 56, 77},
  {cont__259_2, NULL, 513, 513, 14, 77},
  {cont__259_3, NULL, 513, 513, 5, 78},
  {cont__259_4, NULL, 508, 513, 1, 79},
  {cont__259_5, NULL, 515, 515, 28, 53},
  {cont__260_1, NULL, 515, 515, 1, 67},
  {cont__260_2, NULL, 516, 516, 1, 29},
  {cont__261_1, NULL, 517, 517, 1, 59},
  {cont__262_1, NULL, 518, 518, 1, 32},
  {cont__263_1, NULL, 520, 524, 1, 40},
  {cont__264_9, NULL, 529, 529, 20, 44},
  {cont__265_1, NULL, 529, 529, 20, 58},
  {cont__265_2, NULL, 529, 529, 5, 59},
  {cont__265_3, NULL, 526, 530, 1, 48},
  {cont__265_4, NULL, 535, 535, 20, 44},
  {cont__266_1, NULL, 535, 535, 20, 57},
  {cont__266_2, NULL, 535, 535, 5, 58},
  {cont__266_3, NULL, 532, 536, 1, 48},
  {cont__266_4, NULL, },
  {cont__267_4, NULL, 551, 551, 14, 33},
  {cont__267_5, NULL, 551, 551, 14, 51},
  {cont__267_6, NULL, 551, 551, 5, 52},
  {cont__267_7, NULL, 552, 552, 5, 36},
  {cont__267_9, NULL, 553, 553, 5, 15},
  {cont__267_10, NULL, 541, 554, 1, 23},
  {cont__267_11, NULL, 556, 564, 1, 58},
  {cont__268_5, NULL, 570, 570, 5, 31},
  {cont__269_1, NULL, 566, 571, 1, 23},
  {cont__269_2, NULL, 577, 577, 5, 40},
  {cont__270_1, NULL, 573, 578, 1, 23},
  {cont__270_2, NULL, 580, 580, 18, 52},
  {cont__271_1, NULL, 580, 580, 1, 53},
  {cont__271_2, NULL, 581, 581, 29, 62},
  {cont__272_1, NULL, 581, 581, 1, 63},
  {cont__272_2, NULL, 582, 582, 1, 51},
  {cont__273_1, NULL, 585, 585, 15, 54},
  {cont__274_1, NULL, 584, 585, 1, 77},
  {cont__274_2, NULL, 589, 589, 17, 27},
  {cont__275_1, NULL, 589, 589, 5, 37},
  {cont__275_2, NULL, 590, 590, 19, 29},
  {cont__275_3, NULL, 590, 590, 14, 29},
  {cont__275_4, NULL, 590, 590, 5, 30},
  {cont__275_5, NULL, 591, 591, 14, 25},
  {cont__275_6, NULL, 591, 591, 37, 48},
  {cont__275_7, NULL, 591, 591, 28, 49},
  {cont__275_8, NULL, 591, 591, 52, 62},
  {cont__275_9, NULL, 591, 591, 14, 62},
  {cont__275_10, NULL, 591, 591, 5, 63},
  {cont__275_11, NULL, 587, 591, 1, 64},
  {cont__275_12, NULL, 593, 593, 1, 26},
  {cont__276_1, NULL, 594, 594, 34, 51},
  {cont__277_1, NULL, 594, 594, 22, 61},
  {cont__277_2, NULL, 594, 594, 1, 61},
  {cont__277_4, NULL, 595, 595, 1, 23},
  {cont__278_1, NULL, 596, 596, 33, 49},
  {cont__279_1, NULL, 596, 596, 21, 59},
  {cont__279_2, NULL, 596, 596, 1, 59},
  {cont__279_4, NULL, 597, 597, 22, 31},
  {cont__280_1, NULL, 597, 597, 33, 42},
  {cont__280_2, NULL, 597, 597, 1, 43},
  {cont__280_3, NULL, 598, 598, 31, 45},
  {cont__281_1, NULL, 598, 598, 19, 55},
  {cont__281_2, NULL, 598, 598, 1, 55},
  {cont__281_4, NULL, 602, 602, 5, 29},
  {cont__282_1, NULL, 606, 606, 7, 63},
  {cont__282_2, NULL, },
  {cont__282_3, NULL, 600, 607, 1, 23},
  {cont__282_4, NULL, 611, 611, 5, 47},
  {cont__283_1, NULL, },
  {cont__283_5, NULL, 609, 614, 1, 55},
  {cont__283_6, NULL, },
  {cont__284_2, NULL, 616, 621, 1, 36},
  {cont__284_3, NULL, 625, 625, 5, 32},
  {cont__285_1, NULL, },
  {cont__285_9, NULL, 623, 635, 1, 35},
  {cont__285_10, NULL, 642, 642, 15, 32},
  {cont__286_1, NULL, 642, 642, 9, 32},
  {cont__286_2, NULL, 643, 643, 15, 31},
  {cont__286_3, NULL, 643, 643, 9, 31},
  {cont__286_4, NULL, 644, 644, 15, 29},
  {cont__286_5, NULL, 644, 644, 9, 29},
  {cont__286_6, NULL, 645, 645, 9, 19},
  {cont__286_7, NULL, },
  {cont__286_8, NULL, },
  {cont__286_9, NULL, },
  {cont__286_14, NULL, 637, 651, 1, 42},
  {cont__286_15, NULL, 658, 658, 5, 45},
  {cont__287_2, NULL, 653, 658, 1, 46},
  {cont__287_3, NULL, 660, 660, 23, 45},
  {cont__288_1, NULL, 660, 660, 1, 63},
  {cont__288_2, NULL, 665, 665, 5, 31},
  {cont__289_1, NULL, 668, 668, 5, 20},
  {cont__289_2, NULL, 662, 669, 1, 23},
  {cont__289_3, NULL, },
  {cont__290_5, NULL, },
  {cont__290_6, NULL, 671, 678, 1, 59},
  {cont__290_8, NULL, },
  {cont__291_9, NULL, 688, 688, 17, 42},
  {cont__291_10, NULL, 688, 688, 5, 64},
  {cont__291_11, NULL, 689, 689, 5, 15},
  {cont__291_12, NULL, 680, 689, 1, 16},
  {cont__291_14, NULL, 691, 704, 1, 55},
  {cont__292_20, NULL, 709, 709, 5, 34},
  {cont__293_1, NULL, 710, 710, 5, 28},
  {cont__293_2, NULL, 712, 712, 10, 34},
  {cont__293_3, NULL, 712, 712, 37, 74},
  {cont__293_4, NULL, 712, 712, 10, 74},
  {cont__293_5, NULL, 712, 712, 5, 75},
  {cont__293_6, NULL, 713, 713, 5, 20},
  {cont__293_7, NULL, 706, 715, 1, 21},
  {cont__293_8, NULL, 720, 720, 19, 31},
  {cont__294_1, NULL, 720, 720, 7, 32},
  {cont__294_2, NULL, 721, 721, 7, 32},
  {cont__294_3, NULL, 722, 722, 7, 35},
  {cont__294_4, NULL, 723, 723, 7, 35},
  {cont__294_5, NULL, },
  {cont__294_6, NULL, 717, 723, 1, 37},
  {cont__294_7, NULL, 725, 728, 1, 62},
  {cont__295_5, NULL, 733, 733, 5, 31},
  {cont__296_1, NULL, 737, 737, 10, 43},
  {cont__296_2, NULL, 737, 737, 5, 44},
  {cont__296_3, NULL, 738, 738, 9, 21},
  {cont__296_4, NULL, 738, 738, 23, 44},
  {cont__296_5, NULL, 738, 738, 23, 58},
  {cont__296_6, NULL, 738, 738, 5, 59},
  {cont__296_7, NULL, 730, 740, 1, 21},
  {cont__296_8, NULL, 742, 742, 19, 41},
  {cont__297_1, NULL, 742, 742, 44, 64},
  {cont__297_2, NULL, 742, 742, 1, 64},
  {cont__297_3, NULL, 747, 747, 32, 66},
  {cont__298_2, NULL, 747, 747, 12, 67},
  {cont__298_3, NULL, 747, 747, 5, 68},
  {cont__298_4, NULL, 748, 748, 5, 15},
  {cont__298_5, NULL, 744, 748, 1, 16},
  {cont__298_6, NULL, },
  {cont__299_10, NULL, 750, 762, 1, 23},
  {cont__299_12, NULL, },
  {cont__300_5, NULL, 764, 777, 1, 23},
  {cont__300_6, NULL, 779, 787, 1, 13},
  {cont__301_1, NULL, 789, 789, 58, 79},
  {cont__302_1, NULL, 789, 789, 42, 79},
  {cont__302_2, NULL, 789, 789, 1, 80},
  {cont__302_3, NULL, 791, 811, 1, 9},
  {cont__303_1, NULL, 814, 814, 18, 66},
  {cont__304_1, NULL, 813, 814, 1, 67},
  {cont__304_2, NULL, 816, 816, 17, 47},
  {cont__305_1, NULL, 816, 816, 1, 69},
  {cont__305_2, NULL, 822, 822, 5, 39},
  {cont__306_1, NULL, 824, 824, 5, 32},
  {cont__306_2, NULL, 818, 824, 1, 33},
  {cont__306_3, NULL, 828, 828, 5, 56},
  {cont__307_1, NULL, },
  {cont__307_14, NULL, 826, 838, 1, 63},
  {cont__307_15, NULL, 840, 897, 1, 70},
  {cont__308_62, NULL, 901, 901, 5, 24},
  {cont__309_1, NULL, 902, 902, 5, 27},
  {cont__309_2, NULL, 903, 903, 26, 48},
  {cont__309_3, NULL, 903, 903, 10, 48},
  {cont__309_4, NULL, 903, 903, 5, 49},
  {cont__309_5, NULL, 905, 905, 22, 52},
  {cont__309_6, NULL, 905, 905, 7, 53},
  {cont__309_7, NULL, 905, 905, 7, 74},
  {cont__309_8, NULL, },
  {cont__309_9, NULL, 899, 906, 1, 22},
  {cont__309_10, NULL, 908, 908, 26, 62},
  {cont__310_1, NULL, 908, 908, 1, 76},
  {cont__310_3, NULL, 911, 911, 15, 63},
  {cont__311_1, NULL, 910, 911, 1, 63},
  {cont__311_2, NULL, 921, 921, 13, 55},
  {cont__312_1, NULL, 922, 922, 13, 50},
  {cont__312_2, NULL, },
  {cont__312_3, NULL, 925, 925, 13, 28},
  {cont__312_4, NULL, 926, 926, 13, 52},
  {cont__312_5, NULL, },
  {cont__312_6, NULL, 929, 929, 13, 52},
  {cont__312_7, NULL, 930, 930, 13, 50},
  {cont__312_8, NULL, },
  {cont__312_9, NULL, },
  {cont__312_10, NULL, },
  {cont__312_11, NULL, },
  {cont__312_12, NULL, 913, 930, 1, 55},
  {cont__312_13, NULL, 933, 933, 8, 37},
  {cont__313_1, NULL, 932, 933, 1, 68},
  {cont__313_2, NULL, 935, 935, 28, 56},
  {cont__314_1, NULL, 935, 935, 1, 74},
  {cont__314_3, NULL, 936, 936, 29, 59},
  {cont__315_1, NULL, 936, 936, 1, 77},
  {cont__315_2, NULL, 937, 937, 29, 58},
  {cont__316_1, NULL, 937, 937, 1, 76},
  {cont__316_3, NULL, },
  {cont__317_5, NULL, 951, 951, 9, 24},
  {cont__317_6, NULL, 951, 951, 26, 61},
  {cont__317_7, NULL, 951, 951, 5, 62},
  {cont__317_8, NULL, 939, 952, 1, 23},
  {cont__317_9, NULL, 958, 958, 5, 31},
  {cont__318_1, NULL, 959, 959, 5, 36},
  {cont__318_2, NULL, 954, 959, 1, 37},
  {cont__318_3, NULL, 961, 967, 1, 11},
  {cont__319_1, NULL, 972, 972, 5, 24},
  {cont__320_1, NULL, 973, 973, 46, 69},
  {cont__320_2, NULL, 973, 973, 27, 70},
  {cont__320_3, NULL, 973, 973, 5, 71},
  {cont__320_4, NULL, 969, 973, 1, 72},
  {cont__320_5, NULL, 977, 977, 10, 44},
  {cont__321_1, NULL, 977, 977, 5, 44},
  {cont__321_2, NULL, 978, 978, 10, 44},
  {cont__321_3, NULL, 978, 978, 5, 44},
  {cont__321_4, NULL, 975, 978, 1, 45},
  {cont__321_5, NULL, 980, 980, 31, 49},
  {cont__322_1, NULL, 980, 980, 1, 49},
  {cont__322_2, NULL, 986, 986, 5, 36},
  {cont__323_1, NULL, 987, 987, 5, 47},
  {cont__323_2, NULL, 988, 988, 5, 23},
  {cont__323_3, NULL, 982, 988, 1, 24},
  {cont__323_4, NULL, 990, 990, 32, 69},
  {cont__324_1, NULL, 990, 990, 1, 70},
  {cont__324_2, NULL, 995, 995, 5, 43},
  {cont__325_1, NULL, 996, 996, 14, 59},
  {cont__325_2, NULL, 996, 996, 5, 60},
  {cont__325_3, NULL, 998, 998, 27, 64},
  {cont__325_5, NULL, 998, 998, 7, 64},
  {cont__325_6, NULL, 999, 999, 7, 31},
  {cont__325_7, NULL, },
  {cont__325_8, NULL, 992, 1000, 1, 23},
  {cont__325_9, NULL, 1007, 1007, 33, 62},
  {cont__326_1, NULL, 1007, 1007, 24, 78},
  {cont__326_2, NULL, 1007, 1007, 9, 79},
  {cont__326_3, NULL, },
  {cont__326_4, NULL, 1010, 1010, 9, 24},
  {cont__326_5, NULL, 1013, 1013, 13, 45},
  {cont__326_6, NULL, 1015, 1015, 13, 32},
  {cont__326_7, NULL, },
  {cont__326_8, NULL, },
  {cont__326_9, NULL, },
  {cont__326_10, NULL, 1021, 1021, 20, 52},
  {cont__326_11, NULL, 1021, 1021, 11, 68},
  {cont__326_12, NULL, },
  {cont__326_13, NULL, },
  {cont__326_14, NULL, },
  {cont__326_15, NULL, 1002, 1021, 1, 72},
  {cont__326_16, NULL, 1025, 1025, 29, 51},
  {cont__327_1, NULL, 1025, 1025, 5, 75},
  {cont__327_2, NULL, 1023, 1026, 1, 22},
  {cont__327_3, NULL, 1030, 1030, 5, 29},
  {cont__328_1, NULL, 1032, 1032, 5, 42},
  {cont__328_2, NULL, },
  {cont__328_6, NULL, 1040, 1040, 14, 59},
  {cont__328_7, NULL, 1040, 1040, 5, 60},
  {cont__328_8, NULL, 1043, 1043, 5, 46},
  {cont__328_10, NULL, },
  {cont__328_46, NULL, 1028, 1072, 1, 66},
  {cont__328_47, NULL, 1079, 1079, 9, 37},
  {cont__329_1, NULL, 1080, 1080, 9, 49},
  {cont__329_2, NULL, },
  {cont__329_3, NULL, 1083, 1083, 9, 37},
  {cont__329_4, NULL, 1084, 1084, 9, 50},
  {cont__329_5, NULL, },
  {cont__329_6, NULL, 1087, 1087, 9, 37},
  {cont__329_7, NULL, 1088, 1088, 9, 53},
  {cont__329_8, NULL, },
  {cont__329_9, NULL, 1089, 1089, 7, 36},
  {cont__329_10, NULL, 1089, 1089, 39, 79},
  {cont__329_11, NULL, 1089, 1089, 7, 79},
  {cont__329_12, NULL, },
  {cont__329_13, NULL, 1074, 1089, 1, 81},
  {cont__329_14, NULL, 1096, 1096, 9, 27},
  {cont__330_1, NULL, 1097, 1097, 9, 43},
  {cont__330_2, NULL, 1098, 1098, 9, 41},
  {cont__330_3, NULL, },
  {cont__330_4, NULL, 1099, 1099, 12, 56},
  {cont__330_5, NULL, 1099, 1099, 7, 56},
  {cont__330_6, NULL, },
  {cont__330_7, NULL, 1091, 1099, 1, 58},
  {cont__330_8, NULL, },
  {cont__331_2, NULL, 1101, 1106, 1, 33},
  {cont__331_3, NULL, 1112, 1112, 7, 26},
  {cont__332_1, NULL, 1114, 1114, 7, 24},
  {cont__332_2, NULL, 1115, 1115, 7, 27},
  {cont__332_3, NULL, },
  {cont__332_4, NULL, 1108, 1116, 1, 26},
  {cont__332_5, NULL, 1118, 1118, 1, 68},
  {cont__333_1, NULL, 1121, 1121, 14, 38},
  {cont__334_1, NULL, 1121, 1121, 50, 72},
  {cont__334_2, NULL, 1121, 1121, 41, 73},
  {cont__334_3, NULL, 1120, 1121, 1, 73},
  {cont__334_4, NULL, 1127, 1127, 5, 34},
  {cont__335_1, NULL, 1128, 1128, 5, 55},
  {cont__335_2, NULL, 1123, 1129, 1, 19},
  {cont__335_4, NULL, 1132, 1132, 17, 41},
  {cont__336_1, NULL, 1132, 1132, 53, 75},
  {cont__336_2, NULL, 1132, 1132, 44, 76},
  {cont__336_3, NULL, 1131, 1132, 1, 76},
  {cont__336_4, NULL, 1140, 1140, 23, 57},
  {cont__337_1, NULL, 1140, 1140, 11, 79},
  {cont__337_2, NULL, 1141, 1141, 42, 79},
  {cont__337_3, NULL, 1141, 1141, 20, 79},
  {cont__337_4, NULL, 1141, 1141, 11, 80},
  {cont__337_5, NULL, },
  {cont__337_6, NULL, 1142, 1142, 9, 46},
  {cont__337_7, NULL, },
  {cont__337_8, NULL, },
  {cont__337_9, NULL, 1143, 1143, 5, 15},
  {cont__337_10, NULL, 1134, 1143, 1, 16},
  {cont__337_11, NULL, 1151, 1151, 21, 66},
  {cont__338_1, NULL, 1151, 1151, 9, 75},
  {cont__338_2, NULL, 1152, 1152, 27, 75},
  {cont__338_3, NULL, 1152, 1152, 18, 75},
  {cont__338_4, NULL, 1152, 1152, 9, 76},
  {cont__338_5, NULL, },
  {cont__338_6, NULL, 1153, 1153, 7, 55},
  {cont__338_7, NULL, },
  {cont__338_8, NULL, 1154, 1154, 5, 26},
  {cont__338_9, NULL, 1155, 1155, 5, 19},
  {cont__338_10, NULL, 1156, 1156, 5, 15},
  {cont__338_11, NULL, 1145, 1156, 1, 16},
  {cont__338_12, NULL, 1161, 1161, 5, 18},
  {cont__339_1, NULL, 1165, 1165, 9, 33},
  {cont__339_2, NULL, 1167, 1167, 14, 55},
  {cont__339_3, NULL, 1167, 1167, 14, 65},
  {cont__339_4, NULL, 1167, 1167, 9, 66},
  {cont__339_5, NULL, },
  {cont__339_13, NULL, },
  {cont__339_14, NULL, },
  {cont__339_15, NULL, 1177, 1177, 9, 26},
  {cont__339_16, NULL, 1179, 1179, 9, 30},
  {cont__339_17, NULL, },
  {cont__339_18, NULL, 1181, 1181, 18, 56},
  {cont__339_19, NULL, 1181, 1181, 9, 57},
  {cont__339_20, NULL, 1182, 1182, 9, 33},
  {cont__339_21, NULL, 1184, 1184, 33, 67},
  {cont__339_22, NULL, 1184, 1184, 11, 67},
  {cont__339_23, NULL, 1185, 1185, 27, 44},
  {cont__339_24, NULL, 1185, 1185, 57, 78},
  {cont__339_25, NULL, 1185, 1185, 11, 79},
  {cont__339_26, NULL, },
  {cont__339_27, NULL, },
  {cont__339_28, NULL, },
  {cont__339_29, NULL, 1158, 1186, 1, 23},
  {cont__339_30, NULL, 1190, 1190, 5, 21},
  {cont__340_1, NULL, 1191, 1191, 5, 18},
  {cont__340_2, NULL, 1193, 1193, 5, 46},
  {cont__340_3, NULL, 1188, 1194, 1, 23},
  {cont__340_4, NULL, 1196, 1196, 1, 42},
  {cont__341_1, NULL, 1201, 1201, 5, 20},
  {cont__342_1, NULL, 1203, 1203, 5, 25},
  {cont__342_2, NULL, 1204, 1204, 28, 51},
  {cont__342_3, NULL, 1204, 1204, 28, 66},
  {cont__342_4, NULL, 1204, 1204, 23, 67},
  {cont__342_5, NULL, 1204, 1204, 5, 68},
  {cont__342_6, NULL, 1205, 1205, 5, 26},
  {cont__342_7, NULL, 1206, 1206, 5, 19},
  {cont__342_8, NULL, 1207, 1207, 5, 15},
  {cont__342_9, NULL, 1198, 1208, 1, 23},
  {cont__342_10, NULL, 1210, 1210, 37, 70},
  {cont__343_1, NULL, 1210, 1210, 1, 71},
  {cont__343_2, NULL, 1211, 1211, 44, 73},
  {cont__344_1, NULL, 1211, 1211, 1, 73},
  {cont__344_3, NULL, 1214, 1214, 10, 51},
  {cont__345_1, NULL, 1213, 1214, 1, 51},
  {cont__345_3, NULL, 1216, 1217, 1, 75},
  {cont__346_1, NULL, 1219, 1219, 1, 53},
  {cont__347_1, NULL, 1223, 1223, 11, 42},
  {cont__348_1, NULL, 1223, 1223, 5, 47},
  {cont__348_3, NULL, 1224, 1224, 10, 41},
  {cont__348_4, NULL, 1224, 1224, 5, 41},
  {cont__348_5, NULL, 1221, 1224, 1, 42},
  {cont__348_6, NULL, 1231, 1231, 21, 39},
  {cont__349_1, NULL, 1231, 1231, 9, 39},
  {cont__349_2, NULL, 1234, 1234, 22, 40},
  {cont__349_3, NULL, 1234, 1234, 9, 40},
  {cont__349_4, NULL, },
  {cont__349_5, NULL, },
  {cont__349_6, NULL, 1236, 1236, 17, 39},
  {cont__349_7, NULL, 1236, 1236, 5, 40},
  {cont__349_8, NULL, 1237, 1237, 5, 20},
  {cont__349_9, NULL, 1238, 1238, 5, 20},
  {cont__349_10, NULL, 1239, 1239, 5, 20},
  {cont__349_11, NULL, 1240, 1240, 5, 21},
  {cont__349_12, NULL, 1241, 1241, 5, 37},
  {cont__349_14, NULL, 1226, 1241, 1, 38},
  {cont__349_15, NULL, 1245, 1245, 10, 39},
  {cont__350_1, NULL, 1245, 1245, 5, 40},
  {cont__350_2, NULL, 1246, 1246, 5, 38},
  {cont__350_3, NULL, 1243, 1246, 1, 39},
  {cont__350_4, NULL, 1252, 1252, 18, 63},
  {cont__351_1, NULL, 1252, 1252, 9, 64},
  {cont__351_2, NULL, },
  {cont__351_26, NULL, },
  {cont__351_27, NULL, },
  {cont__351_28, NULL, 1248, 1280, 1, 23},
  {cont__351_29, NULL, 1285, 1285, 5, 41},
  {cont__352_1, NULL, 1293, 1293, 55, 79},
  {cont__352_2, NULL, 1293, 1293, 24, 79},
  {cont__352_3, NULL, 1293, 1293, 15, 80},
  {cont__352_4, NULL, },
  {cont__352_5, NULL, },
  {cont__352_6, NULL, },
  {cont__352_7, NULL, 1297, 1297, 16, 45},
  {cont__352_8, NULL, 1297, 1297, 11, 46},
  {cont__352_9, NULL, 1298, 1298, 20, 68},
  {cont__352_10, NULL, 1298, 1298, 11, 69},
  {cont__352_11, NULL, },
  {cont__352_12, NULL, },
  {cont__352_13, NULL, },
  {cont__352_14, NULL, 1282, 1298, 1, 73},
  {cont__352_15, NULL, 1303, 1303, 7, 26},
  {cont__353_1, NULL, 1305, 1305, 9, 50},
  {cont__353_2, NULL, 1306, 1306, 18, 37},
  {cont__353_3, NULL, 1306, 1306, 9, 38},
  {cont__353_4, NULL, },
  {cont__353_5, NULL, },
  {cont__353_6, NULL, 1300, 1306, 1, 41},
  {cont__353_7, NULL, 1309, 1309, 19, 31},
  {cont__354_1, NULL, 1309, 1309, 33, 67},
  {cont__354_2, NULL, 1308, 1309, 1, 76},
  {cont__354_3, NULL, 1314, 1314, 14, 56},
  {cont__355_1, NULL, 1314, 1314, 5, 57},
  {cont__355_2, NULL, 1311, 1314, 1, 58},
  {cont__355_3, NULL, 1392, 1392, 5, 24},
  {cont__360_1, NULL, 1394, 1394, 5, 35},
  {cont__360_2, NULL, 1397, 1397, 5, 37},
  {cont__360_4, NULL, },
  {cont__360_31, NULL, 1390, 1417, 1, 25},
  {cont__360_32, NULL, 1421, 1421, 5, 28},
  {cont__361_1, NULL, 1424, 1424, 5, 42},
  {cont__361_2, NULL, 1427, 1427, 5, 37},
  {cont__361_3, NULL, 1419, 1427, 1, 38},
  {cont__361_4, NULL, 1431, 1431, 5, 30},
  {cont__362_1, NULL, 1436, 1436, 5, 53},
  {cont__362_3, NULL, 1429, 1436, 1, 54},
  {cont__362_4, NULL, 1444, 1444, 5, 38},
  {cont__363_2, NULL, 1438, 1444, 1, 39},
  {cont__363_3, NULL, 1448, 1448, 17, 51},
  {cont__364_1, NULL, 1448, 1448, 5, 61},
  {cont__364_2, NULL, },
  {cont__364_18, NULL, 1446, 1462, 1, 83},
  {cont__364_19, NULL, 1467, 1467, 5, 24},
  {cont__365_1, NULL, 1467, 1467, 54, 63},
  {cont__365_3, NULL, 1467, 1467, 49, 64},
  {cont__365_4, NULL, 1467, 1467, 43, 64},
  {cont__365_5, NULL, 1467, 1467, 27, 65},
  {cont__365_6, NULL, 1467, 1467, 5, 65},
  {cont__365_7, NULL, 1464, 1467, 1, 66},
  {cont__365_8, NULL, 1469, 1469, 20, 39},
  {cont__366_1, NULL, 1469, 1469, 20, 54},
  {cont__366_2, NULL, 1469, 1469, 1, 55},
  {cont__366_3, NULL, 1474, 1474, 34, 73},
  {cont__367_1, NULL, 1474, 1474, 12, 73},
  {cont__367_2, NULL, 1474, 1474, 5, 74},
  {cont__367_3, NULL, 1471, 1474, 1, 75},
  {cont__367_5, NULL, 1477, 1477, 40, 74},
  {cont__368_1, NULL, 1477, 1477, 18, 74},
  {cont__368_2, NULL, 1477, 1477, 11, 75},
  {cont__368_3, NULL, 1476, 1477, 1, 75},
  {cont__368_5, NULL, 1479, 1479, 55, 75},
  {cont__369_1, NULL, 1479, 1479, 33, 75},
  {cont__369_2, NULL, 1479, 1479, 26, 76},
  {cont__369_3, NULL, 1479, 1479, 1, 76},
  {cont__369_5, NULL, 1485, 1485, 29, 75},
  {cont__370_1, NULL, 1485, 1485, 7, 75},
  {cont__370_2, NULL, },
  {cont__370_3, NULL, 1481, 1485, 1, 77},
  {cont__370_5, NULL, 1487, 1487, 55, 75},
  {cont__371_1, NULL, 1487, 1487, 33, 75},
  {cont__371_2, NULL, 1487, 1487, 26, 76},
  {cont__371_3, NULL, 1487, 1487, 1, 76},
  {cont__371_5, NULL, 1495, 1495, 32, 71},
  {cont__372_5, NULL, 1495, 1495, 9, 72},
  {cont__372_6, NULL, },
  {cont__372_7, NULL, },
  {cont__372_8, NULL, 1489, 1495, 1, 75},
  {cont__372_10, NULL, 1500, 1500, 34, 74},
  {cont__373_1, NULL, 1500, 1500, 12, 74},
  {cont__373_2, NULL, 1500, 1500, 5, 75},
  {cont__373_3, NULL, 1497, 1500, 1, 76},
  {cont__373_5, NULL, 1511, 1511, 5, 42},
  {cont__374_2, NULL, 1502, 1511, 1, 43},
  {cont__374_3, NULL, 1513, 1513, 35, 45},
  {cont__375_1, NULL, 1513, 1513, 1, 45},
  {cont__375_2, NULL, 1514, 1514, 1, 45},
  {cont__376_1, NULL, 1515, 1515, 1, 32},
  {cont__377_2, NULL, 1516, 1516, 50, 69},
  {cont__378_1, NULL, 1516, 1516, 37, 70},
  {cont__378_2, NULL, 1516, 1516, 22, 70},
  {cont__378_3, NULL, 1516, 1516, 1, 71},
  {cont__378_4, NULL, 1521, 1521, 28, 51},
  {cont__379_1, NULL, 1521, 1521, 28, 66},
  {cont__379_2, NULL, 1521, 1521, 23, 67},
  {cont__379_3, NULL, 1521, 1521, 5, 68},
  {cont__379_4, NULL, 1518, 1521, 1, 69},
  {cont__379_5, NULL, 1526, 1526, 5, 20},
  {cont__380_1, NULL, 1527, 1527, 5, 25},
  {cont__380_2, NULL, 1528, 1528, 31, 46},
  {cont__380_3, NULL, 1528, 1528, 22, 47},
  {cont__380_4, NULL, 1528, 1528, 9, 47},
  {cont__380_5, NULL, 1528, 1528, 5, 55},
  {cont__380_6, NULL, 1529, 1529, 5, 26},
  {cont__380_7, NULL, 1530, 1530, 5, 19},
  {cont__380_8, NULL, 1531, 1531, 5, 17},
  {cont__380_9, NULL, 1532, 1532, 5, 15},
  {cont__380_10, NULL, 1523, 1532, 1, 16},
  {cont__380_11, NULL, 1534, 1534, 41, 60},
  {cont__381_1, NULL, 1534, 1534, 34, 61},
  {cont__381_2, NULL, 1534, 1534, 1, 61},
  {cont__381_3, NULL, 1538, 1538, 26, 69},
  {cont__382_2, NULL, 1538, 1538, 5, 70},
  {cont__382_3, NULL, 1539, 1539, 12, 31},
  {cont__382_4, NULL, 1539, 1539, 5, 32},
  {cont__382_5, NULL, 1536, 1539, 1, 33},
  {cont__382_6, NULL, },
  {entry__compiler__std_identifier, NULL, 31, 31, 3, 50},
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
  {entry__print_message, NULL, 53, 53, 3, 40},
  {cont__print_message_2, &frame__print_message, 54, 54, 8, 24},
  {cont__print_message_3, &frame__print_message, 54, 54, 8, 31},
  {cont__print_message_4, &frame__print_message, 54, 54, 3, 33},
  {cont__print_message_5, &frame__print_message, 55, 55, 3, 32},
  {cont__print_message_6, &frame__print_message, 58, 58, 38, 42},
  {cont__print_message_7, &frame__print_message, 58, 58, 23, 43},
  {cont__print_message_8, &frame__print_message, 58, 58, 45, 70},
  {cont__print_message_9, &frame__print_message, 57, 58, 3, 71},
  {cont__print_message_10, &frame__print_message, 60, 60, 3, 27},
  {cont__print_message_11, &frame__print_message, 61, 61, 6, 20},
  {cont__print_message_12, &frame__print_message, 61, 61, 3, 75},
  {cont__print_message_16, &frame__print_message, 62, 62, 7, 23},
  {cont__print_message_17, &frame__print_message, 62, 62, 3, 30},
  {cont__print_message_18, &frame__print_message, 63, 63, 3, 43},
  {cont__print_message_27, &frame__print_message, 64, 64, 3, 35},
  {cont__print_message_28, &frame__print_message, 68, 68, 7, 21},
  {cont__print_message_29, &frame__print_message, 66, 70, 3, 14},
  {cont__print_message_33, &frame__print_message, 72, 72, 42, 59},
  {cont__print_message_34, &frame__print_message, 72, 72, 21, 59},
  {cont__print_message_35, &frame__print_message, 72, 72, 61, 79},
  {cont__print_message_37, &frame__print_message, 72, 72, 3, 80},
  {cont__print_message_38, &frame__print_message, 73, 76, 3, 13},
  {cont__print_message_46, &frame__print_message, 77, 77, 18, 23},
  {cont__print_message_47, &frame__print_message, 77, 77, 3, 23},
  {cont__print_message_48, &frame__print_message, 77, 77, 17, 23},
  {cont__print_message_49, &frame__print_message, 78, 86, 3, 30},
  {entry__compiler__Warning, NULL, 89, 89, 17, 32},
  {cont__compiler__Warning_2, &frame__compiler__Warning, 89, 89, 34, 56},
  {cont__compiler__Warning_3, &frame__compiler__Warning, 89, 89, 3, 70},
  {entry__ExitWithSyntaxError, NULL, 92, 92, 3, 50},
  {cont__ExitWithSyntaxError_3, &frame__ExitWithSyntaxError, 93, 93, 3, 8},
  {entry__compiler__SyntaxError, NULL, 96, 96, 23, 38},
  {cont__compiler__SyntaxError_2, &frame__compiler__SyntaxError, 96, 96, 40, 62},
  {cont__compiler__SyntaxError_3, &frame__compiler__SyntaxError, 96, 96, 3, 66},
  {entry__ParseError, NULL, 99, 99, 40, 56},
  {cont__ParseError_2, &frame__ParseError, 99, 99, 3, 60},
  {entry__types__syntax_error___grammar__match, NULL, 104, 104, 21, 36},
  {cont__types__syntax_error___grammar__match_2, &frame__types__syntax_error___grammar__match, 104, 104, 3, 36},
  {entry__syntax_error, NULL, 106, 106, 26, 68},
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
  {entry__types__unexpected_input_error___grammar__match, NULL, 114, 114, 3, 34},
  {cont__types__unexpected_input_error___grammar__match_2, &frame__types__unexpected_input_error___grammar__match, 116, 116, 5, 29},
  {cont__types__unexpected_input_error___grammar__match_3, &frame__types__unexpected_input_error___grammar__match, 116, 116, 5, 55},
  {cont__types__unexpected_input_error___grammar__match_6, &frame__types__unexpected_input_error___grammar__match, 115, 133, 3, 43},
  {entry__unexpected_input_error, NULL, 136, 136, 3, 61},
  {entry__dump_stream___grammar__match, NULL, 155, 155, 3, 23},
  {cont__dump_stream___grammar__match_3, &frame__dump_stream___grammar__match, 156, 156, 17, 48},
  {cont__dump_stream___grammar__match_4, &frame__dump_stream___grammar__match, 156, 156, 3, 48},
  {cont__dump_stream___grammar__match_5, &frame__dump_stream___grammar__match, 157, 157, 3, 23},
  {cont__dump_stream___grammar__match_7, &frame__dump_stream___grammar__match, 158, 158, 3, 6},
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
  {entry__compiler__strip, NULL, 171, 171, 6, 21},
  {cont__compiler__strip_2, &frame__compiler__strip, 171, 171, 6, 32},
  {cont__compiler__strip_3, &frame__compiler__strip, 171, 171, 3, 56},
  {cont__compiler__strip_7, &frame__compiler__strip, 172, 172, 6, 23},
  {cont__compiler__strip_8, &frame__compiler__strip, 172, 172, 6, 34},
  {cont__compiler__strip_9, &frame__compiler__strip, 172, 172, 3, 60},
  {cont__compiler__strip_13, &frame__compiler__strip, 173, 173, 6, 24},
  {cont__compiler__strip_14, &frame__compiler__strip, 173, 173, 6, 35},
  {cont__compiler__strip_15, &frame__compiler__strip, 173, 174, 3, 66},
  {cont__compiler__strip_21, &frame__compiler__strip, 175, 175, 6, 24},
  {cont__compiler__strip_22, &frame__compiler__strip, 175, 175, 6, 35},
  {cont__compiler__strip_23, &frame__compiler__strip, 175, 176, 3, 66},
  {cont__compiler__strip_29, &frame__compiler__strip, 177, 177, 6, 23},
  {cont__compiler__strip_30, &frame__compiler__strip, 177, 177, 6, 34},
  {cont__compiler__strip_31, &frame__compiler__strip, 177, 178, 3, 63},
  {cont__compiler__strip_37, &frame__compiler__strip, 179, 179, 6, 20},
  {cont__compiler__strip_38, &frame__compiler__strip, 179, 179, 6, 31},
  {cont__compiler__strip_39, &frame__compiler__strip, 179, 179, 3, 54},
  {cont__compiler__strip_43, &frame__compiler__strip, 180, 180, 6, 24},
  {cont__compiler__strip_44, &frame__compiler__strip, 180, 180, 6, 35},
  {cont__compiler__strip_45, &frame__compiler__strip, 180, 180, 3, 62},
  {cont__compiler__strip_49, &frame__compiler__strip, },
  {entry__dump___grammar__match, NULL, 185, 185, 10, 37},
  {cont__dump___grammar__match_2, &frame__dump___grammar__match, 185, 185, 3, 37},
  {cont__dump___grammar__match_4, &frame__dump___grammar__match, 186, 186, 3, 6},
  {entry__dump3___grammar__match, NULL, 191, 191, 12, 39},
  {cont__dump3___grammar__match_2, &frame__dump3___grammar__match, 191, 191, 3, 39},
  {cont__dump3___grammar__match_3, &frame__dump3___grammar__match, 192, 192, 3, 6},
  {entry__dump5___grammar__match, NULL, 197, 197, 12, 39},
  {cont__dump5___grammar__match_2, &frame__dump5___grammar__match, 197, 197, 3, 39},
  {cont__dump5___grammar__match_3, &frame__dump5___grammar__match, 198, 198, 3, 6},
  {entry__compiler__precedence_3, NULL, 233, 233, 8, 27},
  {cont__compiler__precedence_4, &frame__compiler__precedence_3, 233, 233, 5, 27},
  {entry__compiler__precedence_5, NULL, 234, 234, 5, 23},
  {entry__compiler__precedence, NULL, 232, 232, 5, 18},
  {cont__compiler__precedence_2, &frame__compiler__precedence, 231, 234, 3, 23},
  {entry__compiler__is_left_associative, NULL, 236, 236, 43, 50},
  {cont__compiler__is_left_associative_2, &frame__compiler__is_left_associative, 236, 236, 40, 50},
  {entry__is_right_associative, NULL, 238, 238, 34, 42},
  {cont__is_right_associative_2, &frame__is_right_associative, 238, 238, 34, 42},
  {cont__is_right_associative_3, &frame__is_right_associative, 238, 238, 31, 42},
  {entry__infix_operator, NULL, 241, 241, 19, 70},
  {cont__infix_operator_2, &frame__infix_operator, 241, 241, 6, 71},
  {cont__infix_operator_3, &frame__infix_operator, 241, 241, 3, 71},
  {entry__interleaved, NULL, 243, 243, 58, 78},
  {cont__interleaved_2, &frame__interleaved, 243, 243, 53, 79},
  {cont__interleaved_3, &frame__interleaved, 243, 243, 41, 79},
  {cont__interleaved_4, &frame__interleaved, 243, 243, 38, 79},
  {entry__types__store_arguments_index___grammar__match, NULL, 252, 252, 30, 64},
  {cont__types__store_arguments_index___grammar__match_2, &frame__types__store_arguments_index___grammar__match, 252, 252, 3, 65},
  {cont__types__store_arguments_index___grammar__match_3, &frame__types__store_arguments_index___grammar__match, 253, 253, 18, 36},
  {cont__types__store_arguments_index___grammar__match_4, &frame__types__store_arguments_index___grammar__match, 253, 253, 3, 43},
  {cont__types__store_arguments_index___grammar__match_5, &frame__types__store_arguments_index___grammar__match, 253, 253, 43, 43},
  {entry__store_arguments_index, NULL, 256, 256, 3, 60},
  {entry__types__inline___grammar__match, NULL, 266, 266, 18, 36},
  {cont__types__inline___grammar__match_2, &frame__types__inline___grammar__match, 266, 266, 3, 43},
  {cont__types__inline___grammar__match_3, &frame__types__inline___grammar__match, 266, 266, 43, 43},
  {entry__inline, NULL, 268, 268, 23, 65},
  {entry__expect_3, NULL, 286, 286, 36, 60},
  {cont__expect_4, &frame__expect_3, 286, 286, 23, 61},
  {cont__expect_5, &frame__expect_3, 286, 286, 8, 62},
  {cont__expect_6, &frame__expect_3, 286, 286, 5, 62},
  {entry__expect_7, NULL, 287, 287, 23, 56},
  {cont__expect_8, &frame__expect_7, 287, 287, 8, 57},
  {cont__expect_9, &frame__expect_7, 287, 287, 5, 57},
  {entry__expect, NULL, 285, 285, 5, 26},
  {cont__expect_2, &frame__expect, 284, 287, 3, 57},
  {entry__compiler__arguments_span, NULL, 289, 289, 44, 78},
  {cont__compiler__arguments_span_2, &frame__compiler__arguments_span, 289, 289, 41, 78},
  {entry__check_functor_5, NULL, 1322, 1322, 41, 68},
  {cont__check_functor_6, &frame__check_functor_5, 1322, 1322, 37, 69},
  {cont__check_functor_7, &frame__check_functor_5, 1322, 1322, 37, 69},
  {entry__check_functor_3, NULL, 1322, 1322, 7, 32},
  {cont__check_functor_4, &frame__check_functor_3, 1322, 1322, 7, 69},
  {cont__check_functor_8, &frame__check_functor_3, 1322, 1322, 7, 69},
  {entry__check_functor_10, NULL, 1324, 1324, 7, 43},
  {entry__check_functor, NULL, 1321, 1321, 7, 30},
  {cont__check_functor_2, &frame__check_functor, 1320, 1322, 5, 69},
  {cont__check_functor_9, &frame__check_functor, 1319, 1324, 3, 44},
  {entry__check_arguments_4, NULL, 1333, 1333, 35, 46},
  {cont__check_arguments_5, &frame__check_arguments_4, 1333, 1333, 46, 46},
  {entry__check_arguments_9, NULL, 1334, 1334, 42, 77},
  {cont__check_arguments_10, &frame__check_arguments_9, 1334, 1334, 42, 77},
  {entry__check_arguments_15, NULL, 1338, 1338, 13, 66},
  {entry__check_arguments_14, NULL, 1337, 1338, 11, 66},
  {cont__check_arguments_17, &frame__check_arguments_14, 1339, 1339, 45, 45},
  {entry__check_arguments_19, NULL, 1342, 1342, 13, 78},
  {entry__check_arguments_18, NULL, 1341, 1342, 11, 78},
  {cont__check_arguments_21, &frame__check_arguments_18, 1343, 1343, 46, 46},
  {entry__check_arguments_12, NULL, 1336, 1336, 9, 43},
  {cont__check_arguments_13, &frame__check_arguments_12, 1335, 1343, 7, 47},
  {cont__check_arguments_22, &frame__check_arguments_12, 1344, 1344, 7, 17},
  {cont__check_arguments_23, &frame__check_arguments_12, 1344, 1344, 17, 17},
  {entry__check_arguments_2, NULL, 1333, 1333, 8, 32},
  {cont__check_arguments_3, &frame__check_arguments_2, 1333, 1333, 5, 46},
  {cont__check_arguments_6, &frame__check_arguments_2, 1334, 1334, 12, 36},
  {cont__check_arguments_7, &frame__check_arguments_2, 1334, 1334, 8, 37},
  {cont__check_arguments_8, &frame__check_arguments_2, 1334, 1334, 8, 77},
  {cont__check_arguments_11, &frame__check_arguments_2, 1334, 1344, 5, 17},
  {entry__check_arguments_29, NULL, 1350, 1350, 54, 76},
  {cont__check_arguments_30, &frame__check_arguments_29, 1350, 1350, 11, 77},
  {cont__check_arguments_31, &frame__check_arguments_29, 1351, 1351, 24, 46},
  {cont__check_arguments_32, &frame__check_arguments_29, 1351, 1351, 11, 46},
  {entry__check_arguments_33, NULL, 1353, 1353, 11, 31},
  {entry__check_arguments_27, NULL, 1349, 1349, 9, 43},
  {cont__check_arguments_28, &frame__check_arguments_27, 1348, 1353, 7, 32},
  {entry__check_arguments_25, NULL, 1347, 1347, 12, 31},
  {cont__check_arguments_26, &frame__check_arguments_25, 1347, 1353, 5, 33},
  {entry__check_arguments_37, NULL, 1354, 1354, 34, 62},
  {entry__check_arguments_39, NULL, 1356, 1356, 21, 21},
  {entry__check_arguments_45, NULL, 1359, 1359, 24, 62},
  {cont__check_arguments_47, &frame__check_arguments_45, 1359, 1359, 7, 62},
  {entry__check_arguments_50, NULL, 1361, 1361, 24, 61},
  {cont__check_arguments_52, &frame__check_arguments_50, 1361, 1361, 7, 61},
  {entry__check_arguments_43, NULL, 1358, 1358, 8, 31},
  {cont__check_arguments_44, &frame__check_arguments_43, 1358, 1359, 5, 62},
  {cont__check_arguments_48, &frame__check_arguments_43, 1360, 1360, 8, 31},
  {cont__check_arguments_49, &frame__check_arguments_43, 1360, 1361, 5, 61},
  {entry__check_arguments_57, NULL, 1367, 1367, 9, 24},
  {entry__check_arguments_58, NULL, 1366, 1366, 9, 12},
  {entry__check_arguments_61, NULL, 1373, 1373, 9, 24},
  {entry__check_arguments_62, NULL, 1372, 1372, 9, 20},
  {entry__check_arguments_65, NULL, 1375, 1375, 33, 51},
  {cont__check_arguments_66, &frame__check_arguments_65, 1375, 1375, 33, 51},
  {entry__check_arguments_73, NULL, 1381, 1381, 13, 17},
  {entry__check_arguments_71, NULL, 1379, 1379, 18, 42},
  {cont__check_arguments_72, &frame__check_arguments_71, 1379, 1381, 11, 17},
  {entry__check_arguments_69, NULL, 1378, 1378, 18, 35},
  {cont__check_arguments_70, &frame__check_arguments_69, 1378, 1381, 9, 18},
  {cont__check_arguments_74, &frame__check_arguments_69, 1381, 1381, 18, 18},
  {entry__check_arguments_77, NULL, 1383, 1383, 26, 63},
  {cont__check_arguments_79, &frame__check_arguments_77, 1383, 1383, 9, 63},
  {entry__check_arguments_68, NULL, 1377, 1381, 7, 19},
  {cont__check_arguments_75, &frame__check_arguments_68, 1382, 1382, 14, 60},
  {cont__check_arguments_76, &frame__check_arguments_68, 1382, 1383, 7, 63},
  {entry__check_arguments_82, NULL, 1384, 1384, 33, 51},
  {cont__check_arguments_83, &frame__check_arguments_82, 1384, 1384, 33, 51},
  {entry__check_arguments_85, NULL, 1385, 1385, 24, 60},
  {cont__check_arguments_87, &frame__check_arguments_85, 1385, 1385, 7, 60},
  {entry__check_arguments_55, NULL, 1365, 1365, 9, 36},
  {cont__check_arguments_56, &frame__check_arguments_55, 1363, 1367, 5, 25},
  {cont__check_arguments_59, &frame__check_arguments_55, 1371, 1371, 9, 36},
  {cont__check_arguments_60, &frame__check_arguments_55, 1369, 1373, 5, 25},
  {cont__check_arguments_63, &frame__check_arguments_55, 1375, 1375, 8, 28},
  {cont__check_arguments_64, &frame__check_arguments_55, 1375, 1375, 8, 51},
  {cont__check_arguments_67, &frame__check_arguments_55, 1375, 1383, 5, 64},
  {cont__check_arguments_80, &frame__check_arguments_55, 1384, 1384, 8, 28},
  {cont__check_arguments_81, &frame__check_arguments_55, 1384, 1384, 8, 51},
  {cont__check_arguments_84, &frame__check_arguments_55, 1384, 1385, 5, 60},
  {entry__check_arguments, NULL, 1346, 1346, 12, 29},
  {cont__check_arguments_24, &frame__check_arguments, 1346, 1353, 3, 34},
  {cont__check_arguments_34, &frame__check_arguments, 1354, 1354, 6, 29},
  {cont__check_arguments_36, &frame__check_arguments, 1354, 1354, 6, 62},
  {cont__check_arguments_38, &frame__check_arguments, 1354, 1356, 3, 21},
  {cont__check_arguments_41, &frame__check_arguments, 1357, 1357, 6, 30},
  {cont__check_arguments_42, &frame__check_arguments, 1357, 1361, 3, 62},
  {cont__check_arguments_53, &frame__check_arguments, 1362, 1362, 6, 29},
  {cont__check_arguments_54, &frame__check_arguments, 1362, 1385, 3, 61},
  {entry__CHECK_ARGUMENTS_2, NULL, 1388, 1388, 24, 77},
  {entry__CHECK_ARGUMENTS, NULL, 1388, 1388, 3, 77},
  {entry__compiler__parse_meta_instruction_7, NULL, 1550, 1550, 32, 75},
  {entry__compiler__parse_meta_instruction, NULL, 1548, 1548, 3, 39},
  {cont__compiler__parse_meta_instruction_2, &frame__compiler__parse_meta_instruction, 1549, 1549, 3, 38},
  {cont__compiler__parse_meta_instruction_3, &frame__compiler__parse_meta_instruction, 1550, 1550, 13, 29},
  {cont__compiler__parse_meta_instruction_4, &frame__compiler__parse_meta_instruction, 1550, 1550, 6, 29},
  {cont__compiler__parse_meta_instruction_5, &frame__compiler__parse_meta_instruction, 1550, 1550, 6, 29},
  {cont__compiler__parse_meta_instruction_6, &frame__compiler__parse_meta_instruction, 1550, 1550, 3, 75},
  {cont__compiler__parse_meta_instruction_9, &frame__compiler__parse_meta_instruction, 1551, 1551, 3, 8},
  {entry__compiler__parse_statement_9, NULL, 1562, 1562, 9, 67},
  {entry__compiler__parse_statement_5, NULL, 1561, 1561, 17, 33},
  {cont__compiler__parse_statement_6, &frame__compiler__parse_statement_5, 1561, 1561, 10, 33},
  {cont__compiler__parse_statement_7, &frame__compiler__parse_statement_5, 1561, 1561, 10, 33},
  {cont__compiler__parse_statement_8, &frame__compiler__parse_statement_5, 1561, 1562, 7, 67},
  {entry__compiler__parse_statement_11, NULL, 1564, 1564, 7, 57},
  {cont__compiler__parse_statement_13, &frame__compiler__parse_statement_11, 1565, 1565, 7, 26},
  {cont__compiler__parse_statement_14, &frame__compiler__parse_statement_11, 1566, 1566, 7, 25},
  {cont__compiler__parse_statement_16, &frame__compiler__parse_statement_11, 1567, 1567, 7, 12},
  {entry__compiler__parse_statement, NULL, 1557, 1557, 3, 39},
  {cont__compiler__parse_statement_2, &frame__compiler__parse_statement, 1558, 1558, 3, 33},
  {cont__compiler__parse_statement_3, &frame__compiler__parse_statement, 1560, 1560, 5, 18},
  {cont__compiler__parse_statement_4, &frame__compiler__parse_statement, 1559, 1567, 3, 13},
  {cont__compiler__parse_statement_17, &frame__compiler__parse_statement, 1568, 1568, 3, 8},
  {entry__230_2, NULL, 274, 275, 9, 23},
  {entry__230_1, NULL, 273, 275, 7, 24},
  {cont__230_4, &frame__230_1, 276, 276, 7, 13},
  {entry__240_1, NULL, 302, 302, 7, 48},
  {cont__240_2, &frame__240_1, 303, 303, 40, 40},
  {entry__241_1, NULL, 312, 312, 32, 48},
  {cont__241_2, &frame__241_1, 312, 312, 7, 50},
  {cont__241_3, &frame__241_1, 313, 313, 40, 40},
  {entry__242_1, NULL, 322, 322, 7, 45},
  {cont__242_2, &frame__242_1, 322, 322, 45, 45},
  {entry__243_3, NULL, 334, 334, 13, 43},
  {cont__243_4, &frame__243_3, 334, 334, 43, 43},
  {entry__244_6, NULL, 350, 350, 15, 76},
  {entry__244_4, NULL, 349, 349, 16, 31},
  {cont__244_5, &frame__244_4, 349, 350, 13, 76},
  {cont__244_8, &frame__244_4, 351, 351, 13, 43},
  {cont__244_9, &frame__244_4, 351, 351, 43, 43},
  {entry__247_7, NULL, 381, 382, 29, 55},
  {cont__247_10, &frame__247_7, 381, 382, 11, 55},
  {entry__247_3, NULL, 379, 379, 9, 41},
  {cont__247_4, &frame__247_3, 380, 380, 12, 37},
  {cont__247_5, &frame__247_3, 380, 380, 12, 48},
  {cont__247_6, &frame__247_3, 380, 382, 9, 56},
  {cont__247_11, &frame__247_3, 383, 383, 9, 35},
  {cont__247_12, &frame__247_3, 383, 383, 40, 40},
  {entry__248_4, NULL, 396, 396, 13, 54},
  {cont__248_5, &frame__248_4, 396, 396, 54, 54},
  {entry__248_17, NULL, 406, 407, 33, 64},
  {cont__248_20, &frame__248_17, 406, 407, 15, 64},
  {entry__248_14, NULL, 405, 405, 16, 40},
  {cont__248_15, &frame__248_14, 405, 405, 16, 51},
  {cont__248_16, &frame__248_14, 405, 407, 13, 65},
  {cont__248_21, &frame__248_14, 408, 408, 13, 38},
  {cont__248_22, &frame__248_14, 408, 408, 48, 48},
  {entry__248_25, NULL, 411, 412, 33, 62},
  {cont__248_27, &frame__248_25, 411, 412, 15, 62},
  {entry__248_23, NULL, 410, 410, 16, 44},
  {cont__248_24, &frame__248_23, 410, 412, 13, 63},
  {cont__248_28, &frame__248_23, 413, 413, 13, 42},
  {cont__248_29, &frame__248_23, 413, 413, 47, 47},
  {entry__248_10, NULL, 401, 401, 9, 37},
  {cont__248_11, &frame__248_10, 402, 402, 9, 39},
  {cont__248_12, &frame__248_10, 404, 404, 11, 26},
  {cont__248_13, &frame__248_10, 403, 413, 9, 48},
  {entry__249_6, NULL, 426, 427, 29, 55},
  {cont__249_8, &frame__249_6, 426, 427, 11, 55},
  {entry__249_3, NULL, 424, 424, 9, 37},
  {cont__249_4, &frame__249_3, 425, 425, 12, 37},
  {cont__249_5, &frame__249_3, 425, 427, 9, 56},
  {cont__249_9, &frame__249_3, 428, 428, 9, 35},
  {cont__249_10, &frame__249_3, 428, 428, 40, 40},
  {entry__252_6, NULL, 444, 445, 29, 53},
  {cont__252_9, &frame__252_6, 444, 445, 11, 53},
  {entry__252_3, NULL, 442, 442, 9, 41},
  {cont__252_4, &frame__252_3, 443, 443, 12, 35},
  {cont__252_5, &frame__252_3, 443, 445, 9, 54},
  {cont__252_10, &frame__252_3, 446, 446, 9, 33},
  {cont__252_11, &frame__252_3, 446, 446, 38, 38},
  {entry__253_6, NULL, 459, 460, 29, 54},
  {cont__253_9, &frame__253_6, 459, 460, 11, 54},
  {entry__253_3, NULL, 457, 457, 9, 41},
  {cont__253_4, &frame__253_3, 458, 458, 12, 37},
  {cont__253_5, &frame__253_3, 458, 460, 9, 55},
  {cont__253_10, &frame__253_3, 461, 461, 9, 35},
  {cont__253_11, &frame__253_3, 461, 461, 40, 40},
  {entry__256_6, NULL, 477, 478, 29, 63},
  {cont__256_8, &frame__256_6, 477, 478, 11, 63},
  {entry__256_3, NULL, 475, 475, 9, 41},
  {cont__256_4, &frame__256_3, 476, 476, 12, 35},
  {cont__256_5, &frame__256_3, 476, 478, 9, 64},
  {cont__256_9, &frame__256_3, 479, 479, 9, 33},
  {cont__256_10, &frame__256_3, 479, 479, 38, 38},
  {entry__264_2, NULL, 523, 523, 33, 56},
  {entry__264_4, NULL, 524, 524, 16, 32},
  {cont__264_5, &frame__264_4, 524, 524, 37, 37},
  {cont__264_6, &frame__264_4, 524, 524, 9, 37},
  {cont__264_7, &frame__264_4, 524, 524, 37, 37},
  {entry__264_1, NULL, 523, 523, 14, 56},
  {cont__264_3, &frame__264_1, 523, 524, 7, 37},
  {cont__264_8, &frame__264_1, },
  {entry__267_1, NULL, 549, 549, 26, 42},
  {cont__267_2, &frame__267_1, 550, 550, 33, 56},
  {cont__267_3, &frame__267_1, 546, 550, 9, 57},
  {entry__268_1, NULL, 561, 561, 25, 34},
  {cont__268_2, &frame__268_1, 563, 563, 24, 40},
  {cont__268_3, &frame__268_1, 564, 564, 31, 54},
  {cont__268_4, &frame__268_1, 564, 564, 56, 56},
  {entry__283_2, NULL, 614, 614, 30, 49},
  {cont__283_3, &frame__283_2, 614, 614, 9, 52},
  {cont__283_4, &frame__283_2, 614, 614, 52, 52},
  {entry__284_1, NULL, 621, 621, 33, 33},
  {entry__285_6, NULL, 634, 634, 32, 73},
  {entry__285_2, NULL, 633, 633, 30, 49},
  {cont__285_3, &frame__285_2, 633, 633, 9, 50},
  {cont__285_4, &frame__285_2, 634, 634, 16, 29},
  {cont__285_5, &frame__285_2, 634, 634, 9, 73},
  {cont__285_8, &frame__285_2, 635, 635, 32, 32},
  {entry__286_10, NULL, 650, 650, 37, 56},
  {cont__286_11, &frame__286_10, 650, 650, 37, 67},
  {cont__286_12, &frame__286_10, 650, 650, 27, 68},
  {cont__286_13, &frame__286_10, 651, 651, 39, 39},
  {entry__290_1, NULL, 678, 678, 17, 34},
  {cont__290_2, &frame__290_1, 678, 678, 36, 55},
  {cont__290_3, &frame__290_1, 678, 678, 11, 55},
  {cont__290_4, &frame__290_1, 678, 678, 55, 55},
  {entry__291_5, NULL, 686, 686, 17, 33},
  {cont__291_6, &frame__291_5, 686, 686, 11, 63},
  {cont__291_7, &frame__291_5, 686, 686, 63, 63},
  {entry__291_1, NULL, 685, 685, 12, 30},
  {cont__291_2, &frame__291_1, 685, 685, 12, 36},
  {cont__291_3, &frame__291_1, 685, 685, 12, 36},
  {cont__291_4, &frame__291_1, 685, 686, 9, 63},
  {cont__291_8, &frame__291_1, 687, 687, 30, 30},
  {entry__292_9, NULL, 696, 696, 17, 33},
  {cont__292_10, &frame__292_9, 696, 696, 11, 63},
  {cont__292_11, &frame__292_9, 696, 696, 63, 63},
  {entry__292_5, NULL, 695, 695, 12, 30},
  {cont__292_6, &frame__292_5, 695, 695, 12, 36},
  {cont__292_7, &frame__292_5, 695, 695, 12, 36},
  {cont__292_8, &frame__292_5, 695, 696, 9, 63},
  {cont__292_12, &frame__292_5, 699, 699, 25, 48},
  {cont__292_14, &frame__292_5, 700, 700, 27, 44},
  {cont__292_15, &frame__292_5, 702, 702, 26, 42},
  {cont__292_16, &frame__292_5, 703, 703, 33, 56},
  {cont__292_17, &frame__292_5, 704, 704, 30, 50},
  {cont__292_18, &frame__292_5, 704, 704, 52, 52},
  {entry__292_1, NULL, 694, 694, 20, 37},
  {cont__292_2, &frame__292_1, 694, 694, 10, 38},
  {cont__292_3, &frame__292_1, 694, 694, 10, 42},
  {cont__292_4, &frame__292_1, 694, 704, 7, 52},
  {cont__292_19, &frame__292_1, },
  {entry__295_1, NULL, 728, 728, 15, 32},
  {cont__295_2, &frame__295_1, 728, 728, 34, 60},
  {cont__295_3, &frame__295_1, 728, 728, 7, 60},
  {cont__295_4, &frame__295_1, 728, 728, 60, 60},
  {entry__299_1, NULL, 758, 758, 25, 56},
  {cont__299_3, &frame__299_1, 759, 759, 37, 58},
  {cont__299_5, &frame__299_1, 759, 759, 27, 59},
  {cont__299_6, &frame__299_1, 760, 760, 26, 42},
  {cont__299_7, &frame__299_1, 761, 761, 33, 56},
  {cont__299_8, &frame__299_1, 761, 761, 33, 58},
  {cont__299_9, &frame__299_1, 756, 761, 9, 59},
  {entry__300_1, NULL, 774, 774, 27, 36},
  {cont__300_2, &frame__300_1, 775, 775, 26, 42},
  {cont__300_3, &frame__300_1, 776, 776, 33, 56},
  {cont__300_4, &frame__300_1, 771, 776, 9, 57},
  {entry__307_9, NULL, 836, 836, 13, 51},
  {cont__307_10, &frame__307_9, 836, 836, 13, 51},
  {entry__307_12, NULL, 838, 838, 58, 58},
  {entry__307_2, NULL, 831, 831, 61, 61},
  {cont__307_3, &frame__307_2, 831, 831, 41, 58},
  {cont__307_4, &frame__307_2, 831, 831, 41, 62},
  {cont__307_5, &frame__307_2, 831, 831, 9, 63},
  {cont__307_6, &frame__307_2, 832, 832, 9, 53},
  {cont__307_7, &frame__307_2, 835, 835, 13, 42},
  {cont__307_8, &frame__307_2, 834, 836, 11, 51},
  {cont__307_11, &frame__307_2, 833, 838, 9, 59},
  {cont__307_13, &frame__307_2, },
  {entry__308_6, NULL, 848, 848, 11, 28},
  {cont__308_7, &frame__308_6, 848, 848, 28, 28},
  {entry__308_11, NULL, 858, 858, 20, 44},
  {cont__308_12, &frame__308_11, 858, 858, 17, 44},
  {entry__308_13, NULL, 859, 859, 17, 20},
  {entry__308_22, NULL, 866, 866, 41, 66},
  {cont__308_23, &frame__308_22, 866, 866, 41, 66},
  {entry__308_27, NULL, 871, 871, 21, 57},
  {entry__308_28, NULL, 872, 872, 21, 31},
  {entry__308_16, NULL, 863, 863, 17, 46},
  {cont__308_17, &frame__308_16, 864, 864, 17, 42},
  {cont__308_18, &frame__308_16, 865, 865, 20, 35},
  {cont__308_19, &frame__308_16, 865, 865, 17, 41},
  {cont__308_20, &frame__308_16, 866, 866, 20, 36},
  {cont__308_21, &frame__308_16, 866, 866, 20, 66},
  {cont__308_24, &frame__308_16, 866, 866, 17, 72},
  {cont__308_25, &frame__308_16, 870, 870, 21, 40},
  {cont__308_26, &frame__308_16, 868, 872, 17, 32},
  {cont__308_29, &frame__308_16, 874, 874, 17, 41},
  {cont__308_30, &frame__308_16, 878, 878, 35, 50},
  {cont__308_31, &frame__308_16, 880, 880, 34, 50},
  {cont__308_32, &frame__308_16, 881, 881, 41, 64},
  {cont__308_33, &frame__308_16, 882, 882, 38, 59},
  {cont__308_34, &frame__308_16, 883, 883, 17, 43},
  {cont__308_35, &frame__308_16, 884, 884, 20, 44},
  {cont__308_36, &frame__308_16, 884, 884, 20, 49},
  {cont__308_37, &frame__308_16, 884, 884, 17, 55},
  {entry__308_15, NULL, 862, 884, 15, 55},
  {cont__308_38, &frame__308_15, 884, 884, 55, 55},
  {entry__308_9, NULL, 857, 857, 17, 40},
  {cont__308_10, &frame__308_9, 855, 859, 13, 21},
  {cont__308_14, &frame__308_9, 861, 884, 13, 56},
  {cont__308_39, &frame__308_9, 885, 885, 13, 37},
  {cont__308_40, &frame__308_9, 886, 886, 13, 46},
  {cont__308_41, &frame__308_9, 886, 886, 46, 46},
  {entry__308_50, NULL, 893, 893, 20, 31},
  {cont__308_51, &frame__308_50, 893, 893, 17, 31},
  {entry__308_52, NULL, 894, 894, 17, 28},
  {entry__308_47, NULL, 890, 890, 15, 26},
  {cont__308_48, &frame__308_47, 892, 892, 17, 21},
  {cont__308_49, &frame__308_47, 893, 893, 17, 31},
  {cont__308_53, &frame__308_47, 889, 894, 13, 29},
  {entry__308_8, NULL, 850, 850, 11, 39},
  {cont__308_42, &frame__308_8, 851, 851, 32, 43},
  {cont__308_43, &frame__308_8, 851, 851, 11, 44},
  {cont__308_44, &frame__308_8, 852, 852, 33, 44},
  {cont__308_45, &frame__308_8, 852, 852, 11, 45},
  {cont__308_46, &frame__308_8, 888, 894, 11, 30},
  {cont__308_54, &frame__308_8, 895, 895, 11, 35},
  {cont__308_55, &frame__308_8, 895, 895, 35, 35},
  {entry__308_58, NULL, 897, 897, 41, 60},
  {cont__308_59, &frame__308_58, 897, 897, 36, 66},
  {cont__308_60, &frame__308_58, 897, 897, 67, 67},
  {entry__308_1, NULL, 843, 843, 7, 29},
  {cont__308_2, &frame__308_1, 844, 844, 7, 35},
  {cont__308_3, &frame__308_1, 845, 845, 7, 29},
  {cont__308_4, &frame__308_1, 847, 847, 9, 14},
  {cont__308_5, &frame__308_1, 846, 895, 7, 36},
  {cont__308_56, &frame__308_1, 896, 896, 10, 26},
  {cont__308_57, &frame__308_1, 896, 897, 7, 67},
  {cont__308_61, &frame__308_1, },
  {entry__317_1, NULL, 946, 946, 27, 36},
  {cont__317_2, &frame__317_1, 949, 949, 26, 42},
  {cont__317_3, &frame__317_1, 950, 950, 33, 56},
  {cont__317_4, &frame__317_1, 950, 950, 58, 58},
  {entry__328_3, NULL, 1038, 1038, 26, 42},
  {cont__328_4, &frame__328_3, 1039, 1039, 33, 56},
  {cont__328_5, &frame__328_3, 1035, 1039, 9, 57},
  {entry__328_15, NULL, 1053, 1053, 11, 72},
  {entry__328_26, NULL, 1062, 1062, 35, 54},
  {cont__328_27, &frame__328_26, 1063, 1063, 20, 39},
  {cont__328_28, &frame__328_26, 1063, 1063, 20, 44},
  {cont__328_29, &frame__328_26, 1063, 1063, 17, 51},
  {cont__328_30, &frame__328_26, 1064, 1064, 51, 51},
  {cont__328_31, &frame__328_26, 1064, 1064, 32, 52},
  {cont__328_32, &frame__328_26, 1064, 1064, 17, 58},
  {cont__328_33, &frame__328_26, 1064, 1064, 58, 58},
  {entry__328_25, NULL, 1058, 1064, 15, 58},
  {entry__328_35, NULL, 1070, 1070, 52, 52},
  {cont__328_36, &frame__328_35, 1070, 1070, 55, 55},
  {cont__328_37, &frame__328_35, 1070, 1070, 35, 56},
  {cont__328_38, &frame__328_35, 1071, 1071, 20, 39},
  {cont__328_39, &frame__328_35, 1071, 1071, 20, 44},
  {cont__328_40, &frame__328_35, 1071, 1071, 17, 51},
  {cont__328_41, &frame__328_35, 1072, 1072, 52, 52},
  {cont__328_42, &frame__328_35, 1072, 1072, 33, 53},
  {cont__328_43, &frame__328_35, 1072, 1072, 17, 59},
  {cont__328_44, &frame__328_35, 1072, 1072, 59, 59},
  {entry__328_34, NULL, 1066, 1072, 15, 59},
  {entry__328_20, NULL, 1055, 1055, 11, 35},
  {cont__328_21, &frame__328_20, 1057, 1057, 24, 39},
  {cont__328_22, &frame__328_20, 1057, 1057, 13, 40},
  {cont__328_23, &frame__328_20, 1057, 1057, 13, 60},
  {cont__328_24, &frame__328_20, 1056, 1072, 11, 61},
  {entry__328_11, NULL, 1051, 1051, 9, 38},
  {cont__328_12, &frame__328_11, 1052, 1052, 12, 31},
  {cont__328_13, &frame__328_11, 1052, 1052, 12, 35},
  {cont__328_14, &frame__328_11, 1052, 1053, 9, 72},
  {cont__328_17, &frame__328_11, 1054, 1054, 12, 31},
  {cont__328_18, &frame__328_11, 1054, 1054, 12, 35},
  {cont__328_19, &frame__328_11, 1054, 1072, 9, 62},
  {cont__328_45, &frame__328_11, 1072, 1072, 62, 62},
  {entry__331_1, NULL, 1106, 1106, 30, 30},
  {entry__339_8, NULL, 1175, 1175, 27, 46},
  {cont__339_9, &frame__339_8, 1175, 1175, 48, 80},
  {cont__339_10, &frame__339_8, 1175, 1175, 19, 80},
  {cont__339_11, &frame__339_8, 1175, 1175, 80, 80},
  {entry__339_6, NULL, 1174, 1174, 26, 44},
  {cont__339_7, &frame__339_6, 1174, 1175, 17, 80},
  {cont__339_12, &frame__339_6, 1176, 1176, 46, 46},
  {entry__351_14, NULL, 1269, 1270, 17, 54},
  {cont__351_15, &frame__351_14, 1270, 1270, 55, 55},
  {entry__351_17, NULL, 1273, 1273, 45, 66},
  {cont__351_18, &frame__351_17, 1273, 1273, 38, 79},
  {cont__351_19, &frame__351_17, 1273, 1273, 38, 79},
  {entry__351_21, NULL, 1275, 1275, 21, 41},
  {entry__351_16, NULL, 1273, 1273, 19, 79},
  {cont__351_20, &frame__351_16, 1272, 1275, 17, 42},
  {entry__351_3, NULL, 1256, 1256, 13, 41},
  {cont__351_4, &frame__351_3, 1257, 1257, 13, 47},
  {cont__351_5, &frame__351_3, 1262, 1262, 47, 63},
  {cont__351_6, &frame__351_3, 1262, 1262, 66, 66},
  {cont__351_7, &frame__351_3, 1262, 1262, 31, 67},
  {cont__351_8, &frame__351_3, 1263, 1263, 30, 46},
  {cont__351_9, &frame__351_3, 1264, 1264, 37, 60},
  {cont__351_10, &frame__351_3, 1266, 1266, 13, 52},
  {cont__351_11, &frame__351_3, 1268, 1268, 15, 36},
  {cont__351_12, &frame__351_3, 1268, 1268, 15, 45},
  {cont__351_13, &frame__351_3, 1267, 1275, 13, 44},
  {cont__351_22, &frame__351_3, 1279, 1279, 42, 58},
  {cont__351_23, &frame__351_3, 1279, 1279, 24, 59},
  {cont__351_24, &frame__351_3, 1279, 1279, 19, 69},
  {cont__351_25, &frame__351_3, 1276, 1279, 13, 71},
  {entry__360_17, NULL, 1408, 1408, 21, 50},
  {cont__360_18, &frame__360_17, 1408, 1408, 21, 58},
  {cont__360_19, &frame__360_17, 1408, 1408, 21, 58},
  {entry__360_21, NULL, 1410, 1412, 21, 58},
  {entry__360_13, NULL, 1404, 1404, 30, 47},
  {cont__360_14, &frame__360_13, 1404, 1404, 17, 50},
  {cont__360_15, &frame__360_13, 1407, 1407, 21, 61},
  {cont__360_16, &frame__360_13, 1406, 1408, 19, 58},
  {cont__360_20, &frame__360_13, 1405, 1412, 17, 60},
  {cont__360_23, &frame__360_13, 1415, 1415, 27, 44},
  {cont__360_24, &frame__360_13, 1415, 1415, 49, 49},
  {cont__360_25, &frame__360_13, 1415, 1415, 21, 50},
  {cont__360_26, &frame__360_13, 1413, 1416, 17, 63},
  {cont__360_27, &frame__360_13, 1416, 1416, 64, 64},
  {entry__360_11, NULL, 1403, 1403, 18, 58},
  {cont__360_12, &frame__360_11, 1403, 1416, 15, 64},
  {cont__360_28, &frame__360_11, 1417, 1417, 15, 19},
  {entry__360_9, NULL, 1402, 1402, 20, 37},
  {cont__360_10, &frame__360_9, 1402, 1417, 13, 19},
  {entry__360_6, NULL, 1401, 1401, 28, 45},
  {cont__360_7, &frame__360_6, 1401, 1401, 50, 50},
  {cont__360_8, &frame__360_6, 1401, 1417, 11, 20},
  {cont__360_29, &frame__360_6, 1417, 1417, 20, 20},
  {entry__360_5, NULL, 1400, 1417, 9, 21},
  {cont__360_30, &frame__360_5, },
  {entry__364_9, NULL, 1456, 1458, 15, 67},
  {entry__364_13, NULL, 1459, 1459, 65, 65},
  {entry__364_7, NULL, 1455, 1455, 16, 42},
  {cont__364_8, &frame__364_7, 1455, 1458, 13, 68},
  {cont__364_11, &frame__364_7, 1459, 1459, 16, 36},
  {cont__364_12, &frame__364_7, 1459, 1459, 13, 65},
  {cont__364_14, &frame__364_7, 1460, 1460, 33, 33},
  {entry__364_5, NULL, 1454, 1454, 18, 38},
  {cont__364_6, &frame__364_5, 1454, 1460, 11, 33},
  {entry__364_16, NULL, 1462, 1462, 11, 79},
  {entry__364_3, NULL, 1453, 1453, 18, 36},
  {cont__364_4, &frame__364_3, 1453, 1460, 9, 34},
  {cont__364_15, &frame__364_3, 1461, 1462, 9, 79}
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
  // 248: %arguments_index undefined
  initialize_maybe_future(get__arguments_index(), get__undefined());
  // 249: $types::store_arguments_index types::grammar_object
  initialize_maybe_future(var.types__store_arguments_index, get__types__grammar_object());
  // 261: %within_inline_expression false
  initialize_maybe_future(get__within_inline_expression(), get__false());
  // 262: $types::inline types::grammar_object
  initialize_maybe_future(var.types__inline, get__types__grammar_object());
  // 270: $NOT_INLINE
  // 271:   check_node
  // 272:     : (_node stream)
  // 273:       if within_inline_expression:
  // 274:         ParseError stream "
  // 275:           ")" expected@
  // 276:       -> true
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
  // 273: ... :
  // 274:   ParseError stream "
  // 275:     ")" expected@
  frame->slots[2] /* temp__1 */ = create_closure(entry__230_2, 0);
  // 273: if within_inline_expression:
  // 274:   ParseError stream "
  // 275:     ")" expected@
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
  // 274: ParseError stream "
  // 275:   ")" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__ccbf6d451aa8563f;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__230_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 276: -> true
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
  // 278: ... followed_by(newline)
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
  // 278: $NEWLINE followed_by(newline), NOT_INLINE, newline
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
  // 279: ... followed_by(indent_marker)
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
  // 279: $INDENT followed_by(indent_marker), NOT_INLINE, indent_marker
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
  // 280: ... followed_by(outdent_marker)
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
  // 280: $OUTDENT followed_by(outdent_marker), NOT_INLINE, outdent_marker
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
  // 281: ... followed_by('#')
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
  // 281: $HASHTAG followed_by('#'), NOT_INLINE, '#'
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
  // 291: $compiler::WHITESPACE many(' ')
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
  // 292: ... followed_by(':')
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
  // 292: $SEPARATOR alt(compiler::WHITESPACE followed_by(':'))
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
  // 293: $NEWLINES many(NEWLINE)
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
  // 295: $STORE_POSITION
  // 296:   modify_node
  // 297:     :
  // 298:       (
  // 299:         &node
  // 300:         stream
  // 301:       )
  // 302:       !node.source_position_of length_of(stream)
  // 303:       !node.fragment_of current_fragment
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
  // 302: !node.source_position_of length_of(stream)
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
  // 302: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 303: !node.fragment_of
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
  // 305: $STORE_POSITION_MINUS_1
  // 306:   modify_node
  // 307:     :
  // 308:       (
  // 309:         &node
  // 310:         stream
  // 311:       )
  // 312:       !node.source_position_of length_of(stream)+1
  // 313:       !node.fragment_of current_fragment
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
  // 312: ... length_of(stream)
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
  // 312: !node.source_position_of length_of(stream)+1
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
  // 312: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 313: !node.fragment_of
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
  // 315: $STORE_END_POSITION
  // 316:   modify_node
  // 317:     :
  // 318:       (
  // 319:         &node
  // 320:         stream
  // 321:       )
  // 322:       !node.end_position_of length_of(stream)
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
  // 322: !node.end_position_of length_of(stream)
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
  // 322: !node.end_position_of
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
  // 326: set_node(identifier)
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
  // 328: capture(name_of NAME)
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
  // 334: !node.namespace_of node.name_of
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
  // 334: !node.namespace_of
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
  // 335: capture(name_of NAME)
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
  // 324: $IDENTIFIER
  // 325:   sequence
  // 326:     set_node(identifier)
  // 327:     STORE_POSITION
  // 328:     capture(name_of NAME)
  // 329:     optional
  // 330:       sequence
  // 331:         "::"
  // 332:         modify_node
  // 333:           : (&node)
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
  // 340: set_node(identifier)
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
  // 342: optional(NOT_USED)
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
  // 343: capture(name_of NAME)
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
  // 349: ... node.is_not_used
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
  // 349: ... :
  // 350:   SyntaxError node "namespace must not start with an underscore"
  frame->slots[2] /* temp__2 */ = create_closure(entry__244_6, 0);
  // 349: if node.is_not_used:
  // 350:   SyntaxError node "namespace must not start with an underscore"
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
  // 350: SyntaxError node "namespace must not start with an underscore"
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
  // 351: !node.namespace_of node.name_of
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
  // 351: !node.namespace_of
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
  // 352: capture(name_of NAME)
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
  // 338: $DEFINE_IDENTIFIER
  // 339:   sequence
  // 340:     set_node(identifier)
  // 341:     STORE_POSITION
  // 342:     optional(NOT_USED)
  // 343:     capture(name_of NAME)
  // 344:     optional
  // 345:       sequence
  // 346:         "::"
  // 347:         modify_node
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
  // 357: set_node(identifier)
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
  // 359: capture(namespace_of NAME)
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
  // 360: expect("::")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__245_3;
}
static void cont__245_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 361: capture(name_of NAME)
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
  // 355: $NAMESPACED_IDENTIFIER
  // 356:   sequence
  // 357:     set_node(identifier)
  // 358:     STORE_POSITION
  // 359:     capture(namespace_of NAME)
  // 360:     expect("::")
  // 361:     capture(name_of NAME)
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
  // 366: ... optional("./")
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
  // 366: ... "/", NAME
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
  // 366: ... some("/", NAME)
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
  // 366: $FILENAME optional("./"), NAME, some("/", NAME)
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
  // 371: set_node(require_instruction)
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
  // 374: capture(node::filename_of FILENAME)
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
  // 379: $filename node::filename_of(node)
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
  // 380: ... required_modules(filename)
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
  // 380: ... required_modules(filename).is_defined
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
  // 380: ... :
  // 381:   ParseError stream "
  // 382:     the module "@(filename)" is required twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__247_7, 0);
  // 380: if required_modules(filename).is_defined:
  // 381:   ParseError stream "
  // 382:     the module "@(filename)" is required twice@
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
  // 381: ... "
  // 382:   the module "@(filename)" is required twice@
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
  // 381: ParseError stream "
  // 382:   the module "@(filename)" is required twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__247_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 383: !required_modules(filename)
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
  // 368: $REQUIRE
  // 369:   sequence
  // 370:     "<require"
  // 371:     set_node(require_instruction)
  // 372:     STORE_POSITION
  // 373:     compiler::WHITESPACE
  // 374:     capture(node::filename_of FILENAME)
  // 375:     ">"
  // 376:     STORE_END_POSITION
  // 377:     inspect_node
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
  // 389: set_node(namespace_instruction)
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
  // 390: capture(namespace_of NAME)
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
  // 393: infix_operator("=")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdc;
  result_count = 1;
  myself = func__infix_operator;
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
  // 396: !node.namespace_alias_of node.namespace_of
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
  // 396: !node.namespace_alias_of
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
  // 397: capture(namespace_of NAME)
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
  // 405: ... namespace_mappings(alias)
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
  // 405: ... namespace_mappings(alias).is_defined
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
  // 405: ... :
  // 406:   ParseError stream "
  // 407:     the namespace alias "@(alias)" is defined twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__248_17, 0);
  // 405: if namespace_mappings(alias).is_defined:
  // 406:   ParseError stream "
  // 407:     the namespace alias "@(alias)" is defined twice@
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
  // 406: ... "
  // 407:   the namespace alias "@(alias)" is defined twice@
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
  // 406: ParseError stream "
  // 407:   the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__248_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 408: !namespace_mappings(alias)
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
  // 410: ... defined_namespaces(namespace)
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
  // 410: ... :
  // 411:   ParseError stream "
  // 412:     the namespace "@(namespace)" is defined twice@
  frame->slots[3] /* temp__2 */ = create_closure(entry__248_25, 0);
  // 410: if defined_namespaces(namespace):
  // 411:   ParseError stream "
  // 412:     the namespace "@(namespace)" is defined twice@
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
  // 411: ... "
  // 412:   the namespace "@(namespace)" is defined twice@
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
  // 411: ParseError stream "
  // 412:   the namespace "@(namespace)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__248_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 413: !defined_namespaces(namespace)
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
  // 401: $namespace namespace_of(node)
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
  // 402: $alias namespace_alias_of(node)
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
  // 404: alias.is_defined
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
  // 404: ... :
  // 405:   if namespace_mappings(alias).is_defined:
  // 406:     ParseError stream "
  // 407:       the namespace alias "@(alias)" is defined twice@
  // 408:   !namespace_mappings(alias) namespace
  frame->slots[5] /* temp__2 */ = create_closure(entry__248_14, 0);
  // 409: :
  // 410:   if defined_namespaces(namespace):
  // 411:     ParseError stream "
  // 412:       the namespace "@(namespace)" is defined twice@
  // 413:   !defined_namespaces(namespace) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__248_23, 0);
  // 403: if
  // 404:   alias.is_defined:
  // 405:     if namespace_mappings(alias).is_defined:
  // 406:       ParseError stream "
  // 407:         the namespace alias "@(alias)" is defined twice@
  // 408:     !namespace_mappings(alias) namespace
  // 409:   :
  // 410:     if defined_namespaces(namespace):
  // 411:       ParseError stream "
  // 412:         the namespace "@(namespace)" is defined twice@
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
  // 385: $NAMESPACE
  // 386:   sequence
  // 387:     "<namespace"
  // 388:     compiler::WHITESPACE
  // 389:     set_node(namespace_instruction)
  // 390:     capture(namespace_of NAME)
  // 391:     optional
  // 392:       sequence
  // 393:         infix_operator("=")
  // 394:         modify_node
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
  // 419: set_node(using_instruction)
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
  // 420: capture(namespace_of NAME)
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
  // 424: $namespace namespace_of(node)
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
  // 425: ... used_namespaces(namespace)
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
  // 425: ... :
  // 426:   ParseError stream "
  // 427:     the namespace "@(namespace)" is used twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__249_6, 0);
  // 425: if used_namespaces(namespace):
  // 426:   ParseError stream "
  // 427:     the namespace "@(namespace)" is used twice@
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
  // 426: ... "
  // 427:   the namespace "@(namespace)" is used twice@
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
  // 426: ParseError stream "
  // 427:   the namespace "@(namespace)" is used twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__249_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 428: !used_namespaces(namespace)
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
  // 415: $USING
  // 416:   sequence
  // 417:     "<using"
  // 418:     compiler::WHITESPACE
  // 419:     set_node(using_instruction)
  // 420:     capture(namespace_of NAME)
  // 421:     ">"
  // 422:     inspect_node
  // 423:       : (node stream)
  // 424:         $namespace namespace_of(node)
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
  // 430: ... alt(LETTER DIGIT '_' '.')
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
  // 430: $BASENAME many(alt(LETTER DIGIT '_' '.'))
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
  // 431: ... some("../")
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
  // 431: ... alt('/' "./" some("../"))
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
  // 431: ... '/', BASENAME
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
  // 431: ... some('/', BASENAME)
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
  // 431: $C_FILENAME alt('/' "./" some("../")), BASENAME, some('/', BASENAME)
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
  // 437: set_node(include_instruction)
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
  // 438: capture(node::filename_of C_FILENAME)
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
  // 442: $filename node::filename_of(node)
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
  // 443: ... included_files(filename)
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
  // 443: ... :
  // 444:   ParseError stream "
  // 445:     the file "@(filename)" is included twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__252_6, 0);
  // 443: if included_files(filename):
  // 444:   ParseError stream "
  // 445:     the file "@(filename)" is included twice@
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
  // 444: ... "
  // 445:   the file "@(filename)" is included twice@
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
  // 444: ParseError stream "
  // 445:   the file "@(filename)" is included twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__252_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 446: !included_files(filename)
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
  // 433: $INCLUDE
  // 434:   sequence
  // 435:     "<include"
  // 436:     compiler::WHITESPACE
  // 437:     set_node(include_instruction)
  // 438:     capture(node::filename_of C_FILENAME)
  // 439:     ">"
  // 440:     inspect_node
  // 441:       : (node stream)
  // 442:         $filename node::filename_of(node)
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
  // 452: set_node(link_instruction)
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
  // 453: capture(node::filename_of C_FILENAME)
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
  // 457: $filename node::filename_of(node)
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
  // 458: ... linked_libraries(filename)
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
  // 458: ... :
  // 459:   ParseError stream "
  // 460:     the library "@(filename)" is linked twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__253_6, 0);
  // 458: if linked_libraries(filename):
  // 459:   ParseError stream "
  // 460:     the library "@(filename)" is linked twice@
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
  // 459: ... "
  // 460:   the library "@(filename)" is linked twice@
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
  // 459: ParseError stream "
  // 460:   the library "@(filename)" is linked twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__253_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 461: !linked_libraries(filename)
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
  // 448: $LINK
  // 449:   sequence
  // 450:     "<link"
  // 451:     compiler::WHITESPACE
  // 452:     set_node(link_instruction)
  // 453:     capture(node::filename_of C_FILENAME)
  // 454:     ">"
  // 455:     inspect_node
  // 456:       : (node stream)
  // 457:         $filename node::filename_of(node)
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
  // 463: ... alt(LETTER DIGIT '_' '.' '*' '?')
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
  // 463: $MASK many(alt(LETTER DIGIT '_' '.' '*' '?'))
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
  // 464: ... some("../")
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
  // 464: ... alt('/' "./" some("../"))
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
  // 464: ... '/', MASK
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
  // 464: ... some('/', MASK)
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
  // 464: $FILEMASK alt('/' "./" some("../")), MASK, some('/', MASK)
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
  // 470: set_node(data_instruction)
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
  // 471: capture(node::filemask_of FILEMASK)
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
  // 475: $filemask node::filemask_of(node)
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
  // 476: ... dependent_data(filemask)
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
  // 476: ... :
  // 477:   ParseError stream "
  // 478:     the data dependency "@(filemask)" is defined twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__256_6, 0);
  // 476: if dependent_data(filemask):
  // 477:   ParseError stream "
  // 478:     the data dependency "@(filemask)" is defined twice@
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
  // 477: ... "
  // 478:   the data dependency "@(filemask)" is defined twice@
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
  // 477: ParseError stream "
  // 478:   the data dependency "@(filemask)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__256_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 479: !dependent_data(filemask)
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
  // 466: $DATA
  // 467:   sequence
  // 468:     "<data"
  // 469:     compiler::WHITESPACE
  // 470:     set_node(data_instruction)
  // 471:     capture(node::filemask_of FILEMASK)
  // 472:     ">"
  // 473:     inspect_node
  // 474:       : (node stream)
  // 475:         $filemask node::filemask_of(node)
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
  // 483: alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
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
  // 484: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__257_2;
}
static void cont__257_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 484: ... NEXT_LINE_REMARK, expect(outdent_marker)
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
  // 484: ... alt(LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker))
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
  // 484: optional(alt(LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
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
  // 481: $META_INSTRUCTION
  // 482:   sequence
  // 483:     alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
  // 484:     optional(alt(LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
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
  // 505: ... some(PRINTABLE_CHARACTER)
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
  // 505: $REMARK_LINE multi_capture(remark_lines_of some(PRINTABLE_CHARACTER))
  // 506:   # a single line containing remark text
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
  // 513: ... interleaved(REMARK_LINE NEWLINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_LINE;
  arguments->slots[1] = var._NEWLINE;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__259_1;
}
static void cont__259_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 513: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__259_2;
}
static void cont__259_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 513: ... INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker)
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
  // 513: optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
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
  // 508: $REMARK_LINES
  // 509:   #
  // 510:     a remark potentially spanning multipe lines
  // 511:   sequence
  // 512:     REMARK_LINE
  // 513:     optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
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
  // 515: ... set_node(remark_statement)
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
  // 515: $REMARK_STATEMENT HASHTAG, set_node(remark_statement), REMARK_LINES
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
  // 516: $REMARK HASHTAG, REMARK_LINES
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
  // 517: $LINE_END_REMARK compiler::WHITESPACE, HASHTAG, REMARK_LINE
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
  // 518: $NEXT_LINE_REMARK INDENT, REMARK
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
  // 520: $REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING
  // 521:   modify_node
  // 522:     : (&node)
  // 523:       unless do_pretty_print || do_extract_documentation:
  // 524:         range &node.arguments_of 1 -2
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
  // 523: ... do_pretty_print || do_extract_documentation
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
  // 523: ... do_extract_documentation
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
  // 523: ... :
  // 524:   range &node.arguments_of 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__264_4, 0);
  // 523: unless do_pretty_print || do_extract_documentation:
  // 524:   range &node.arguments_of 1 -2
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
  // 524: ... node.arguments_of
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
  // 524: ... 2
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
  // 524: range &node.arguments_of 1 -2
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
  // 524: ... &node.arguments_of
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
  // 529: ... set_node(remark_argument)
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
  // 529: ... set_node(remark_argument), REMARK_LINES
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
  // 529: arguments_span(set_node(remark_argument), REMARK_LINES)
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
  // 526: $REMARK_ARGUMENT
  // 527:   sequence
  // 528:     HASHTAG
  // 529:     arguments_span(set_node(remark_argument), REMARK_LINES)
  // 530:     REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING
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
  // 535: ... set_node(remark_argument)
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
  // 535: ... set_node(remark_argument), REMARK_LINE
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
  // 535: arguments_span(set_node(remark_argument), REMARK_LINE)
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
  // 532: $LINE_END_REMARK_ARGUMENT
  // 533:   sequence
  // 534:     HASHTAG
  // 535:     arguments_span(set_node(remark_argument), REMARK_LINE)
  // 536:     REMOVE_LAST_ARGUMENT_IF_NOT_PRETTY_PRINTING
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
  // 549: ... fragment_of(node)
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
  // 550: ... source_position_of(node)
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
  // 546: ->
  // 547:   function_call
  // 548:     .functor_of node
  // 549:     .fragment_of fragment_of(node)
  // 550:     .source_position_of source_position_of(node)
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
  // 551: ... not_followed_by(')')
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
  // 551: ... not_followed_by(')'), INLINE_ARGUMENTS
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
  // 551: optional(not_followed_by(')'), INLINE_ARGUMENTS)
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
  // 552: CHECK_ARGUMENTS("function call")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4456c807200257a4;
  result_count = 1;
  myself = func__CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__267_9;
}
static void cont__267_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 553: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__267_10;
}
static void cont__267_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 541: $FUNCTION_CALL
  // 542:   sequence
  // 543:     '('
  // 544:     modify_node
  // 545:       : (node)
  // 546:         ->
  // 547:           function_call
  // 548:             .functor_of node
  // 549:             .fragment_of fragment_of(node)
  // 550:             .source_position_of source_position_of(node)
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
  // 556: $MAKE_ATTRIBUTE_ACCESS
  // 557:   modify_node
  // 558:     : (&node)
  // 559:       !node
  // 560:         function_call
  // 561:           .arguments_of list(node)
  // 562:           .is_an_attribute_access true
  // 563:           .fragment_of fragment_of(node)
  // 564:           .source_position_of source_position_of(node)
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
  // 561: ... list(node)
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
  // 563: ... fragment_of(node)
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
  // 564: ... source_position_of(node)
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
  // 559: !node
  // 560:   function_call
  // 561:     .arguments_of list(node)
  // 562:     .is_an_attribute_access true
  // 563:     .fragment_of fragment_of(node)
  // 564:     .source_position_of source_position_of(node)
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
  // 570: span(functor_of IDENTIFIER)
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
  // 566: $ATTRIBUTE_ACCESS
  // 567:   sequence
  // 568:     '.'
  // 569:     MAKE_ATTRIBUTE_ACCESS
  // 570:     span(functor_of IDENTIFIER)
  // 571:     STORE_END_POSITION
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
  // 577: span(functor_of NAME_OF_POLYMORPHIC)
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
  // 573: $ATTRIBUTE_WRITE
  // 574:   sequence
  // 575:     '.'
  // 576:     MAKE_ATTRIBUTE_ACCESS
  // 577:     span(functor_of NAME_OF_POLYMORPHIC)
  // 578:     STORE_END_POSITION
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
  // 580: ... alt(FUNCTION_CALL ATTRIBUTE_ACCESS)
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
  // 580: $EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_ACCESS))
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
  // 581: ... alt(FUNCTION_CALL ATTRIBUTE_WRITE)
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
  // 581: $READ_WRITE_EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_WRITE))
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
  // 582: $IDENTIFIER_OR_FUNCTION_CALL IDENTIFIER, EXTENSIONS
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
  // 585: ... set_field(is_used_as_a_destination true)
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
  // 584: $READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 585:   IDENTIFIER, set_field(is_used_as_a_destination true), READ_WRITE_EXTENSIONS
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
  // 589: ... many(DIGIT)
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
  // 589: interleaved(many(DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__275_2;
}
static void cont__275_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 590: ... many(DIGIT)
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
  // 590: ... '.', many(DIGIT)
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
  // 590: optional('.', many(DIGIT))
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
  // 591: ... alt('e' 'E')
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
  // 591: ... alt('+' '-')
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
  // 591: ... optional(alt('+' '-'))
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
  // 591: ... many(DIGIT)
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
  // 591: ... alt('e' 'E'), optional(alt('+' '-')), many(DIGIT)
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
  // 591: optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
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
  // 587: $DECIMAL_NUMBER
  // 588:   sequence
  // 589:     interleaved(many(DIGIT) '@apos;')
  // 590:     optional('.', many(DIGIT))
  // 591:     optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
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
  // 593: $BINARY_DIGIT alt('0' '1')
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
  // 594: ... many(BINARY_DIGIT)
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
  // 594: ... interleaved(many(BINARY_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__277_2;
}
static void cont__277_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 594: $BINARY_NUMBER "0b", interleaved(many(BINARY_DIGIT) '@apos;')
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
  // 595: $OCTAL_DIGIT '0' .. '7'
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
  // 596: ... many(OCTAL_DIGIT)
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
  // 596: ... interleaved(many(OCTAL_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__279_2;
}
static void cont__279_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 596: $OCTAL_NUMBER "0o", interleaved(many(OCTAL_DIGIT) '@apos;')
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
  // 597: ... 'a' .. 'f'
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
  // 597: ... 'A' .. 'F'
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
  // 597: $HEX_DIGIT alt(DIGIT 'a' .. 'f' 'A' .. 'F')
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
  // 598: ... many(HEX_DIGIT)
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
  // 598: ... interleaved(many(HEX_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__281_2;
}
static void cont__281_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 598: $HEX_NUMBER "0x", interleaved(many(HEX_DIGIT) '@apos;')
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
  // 602: set_node(numeric_literal)
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
  // 606: alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
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
  // 600: $NUMBER
  // 601:   sequence
  // 602:     set_node(numeric_literal)
  // 603:     STORE_POSITION
  // 604:     capture
  // 605:       node::value_of
  // 606:       alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  // 607:     STORE_END_POSITION
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
  // 611: capture(node::value_of PRINTABLE_CHARACTER)
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
  // 614: ... node::value_of(node)
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
  // 614: !node.node::value_of node::value_of(node)(1)
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
  // 614: !node.node::value_of
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
  // 609: $SIMPLE_CHARACTER
  // 610:   sequence
  // 611:     capture(node::value_of PRINTABLE_CHARACTER)
  // 612:     modify_node
  // 613:       : (&node)
  // 614:         !node.node::value_of node::value_of(node)(1)
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
  // 621: !node.node::value_of
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
  // 616: $AT_CHARACTER
  // 617:   sequence
  // 618:     '@@'
  // 619:     modify_node
  // 620:       : (&node)
  // 621:         !node.node::value_of '@@'
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
  // 625: capture(node::value_of NAME)
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
  // 633: ... node::value_of(node)
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
  // 633: $chr character_names(node::value_of(node))
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
  // 634: ... chr.is_defined
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
  // 634: ... : ParseError stream "invalid character name"
  frame->slots[4] /* temp__2 */ = create_closure(entry__285_6, 0);
  // 634: unless chr.is_defined: ParseError stream "invalid character name"
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
  // 634: ... ParseError stream "invalid character name"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__dea962eab6ac8f23;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__285_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 635: !node.node::value_of
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
  // 623: $NAMED_CHARACTER
  // 624:   sequence
  // 625:     capture(node::value_of NAME)
  // 626:     ';'
  // 627:     modify_node
  // 628:       :
  // 629:         (
  // 630:           &node
  // 631:           stream
  // 632:         )
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
  // 642: ... many(BINARY_DIGIT)
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
  // 642: "0b", many(BINARY_DIGIT)
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
  // 643: ... many(OCTAL_DIGIT)
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
  // 643: "0o", many(OCTAL_DIGIT)
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
  // 644: ... many(HEX_DIGIT)
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
  // 644: "0x", many(HEX_DIGIT)
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
  // 645: many(DIGIT)
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
  // 650: ... node::value_of(node)
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
  // 650: ... node::value_of(node).to_integer
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
  // 650: ... character(node::value_of(node).to_integer)
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
  // 649: !node
  // 650:   .node::value_of character(node::value_of(node).to_integer)
  // 651:   .is_in_numeric_notation true
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
  // 637: $NUMERIC_CHARACTER
  // 638:   sequence
  // 639:     capture
  // 640:       node::value_of
  // 641:       alt
  // 642:         "0b", many(BINARY_DIGIT)
  // 643:         "0o", many(OCTAL_DIGIT)
  // 644:         "0x", many(HEX_DIGIT)
  // 645:         many(DIGIT)
  // 646:     ';'
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
  // 658: syntax_error("invalid special character")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4313674f4741806a;
  result_count = 1;
  myself = func__syntax_error;
  func = myself->type;
  frame->cont = cont__287_2;
}
static void cont__287_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 653: $SPECIAL_CHARACTER
  // 654:   alt
  // 655:     AT_CHARACTER
  // 656:     NAMED_CHARACTER
  // 657:     NUMERIC_CHARACTER
  // 658:     syntax_error("invalid special character")
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
  // 660: ... '@@', SPECIAL_CHARACTER
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
  // 660: $CHARACTER_SYMBOL alt('@@', SPECIAL_CHARACTER SIMPLE_CHARACTER)
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
  // 665: set_node(character_literal)
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
  // 668: expect('@apos;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__39;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__289_2;
}
static void cont__289_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 662: $CHARACTER
  // 663:   sequence
  // 664:     '@apos;'
  // 665:     set_node(character_literal)
  // 666:     STORE_POSITION_MINUS_1
  // 667:     CHARACTER_SYMBOL
  // 668:     expect('@apos;')
  // 669:     STORE_END_POSITION
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
  // 678: ... node.node::text_of
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
  // 678: ... node::value_of(node)
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
  // 678: push &node.node::text_of node::value_of(node)
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
  // 678: ... &node.node::text_of
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
  // 671: $STRING_CHARACTER
  // 672:   alt
  // 673:     "@@;"
  // 674:     sequence
  // 675:       CHARACTER_SYMBOL
  // 676:       modify_node
  // 677:         : (&node)
  // 678:           push &node.node::text_of node::value_of(node)
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
  // 685: ... node::text_of(node)
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
  // 685: ... node::text_of(node) != ""
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
  // 685: ... node::text_of(node) != ""
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
  // 685: ... :
  // 686:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__291_5, 0);
  // 685: if node::text_of(node) != "":
  // 686:   push &node.arguments_of node(.arguments_of undefined)
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
  // 686: ... node.arguments_of
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
  // 686: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 686: push &node.arguments_of node(.arguments_of undefined)
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
  // 686: ... &node.arguments_of
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
  // 687: !node.node::text_of
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
  // 688: ... arguments_span(EXPRESSION)
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
  // 688: interleaved(arguments_span(EXPRESSION) compiler::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__291_11;
}
static void cont__291_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 689: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__291_12;
}
static void cont__291_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 680: $STRING_INSERTION
  // 681:   sequence
  // 682:     "@@("
  // 683:     modify_node
  // 684:       : (&node)
  // 685:         if node::text_of(node) != "":
  // 686:           push &node.arguments_of node(.arguments_of undefined)
  // 687:         !node.node::text_of ""
  // 688:     interleaved(arguments_span(EXPRESSION) compiler::WHITESPACE)
  // 689:     expect(')')
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
  // 691: $CHECK_INSERTIONS
  // 692:   modify_node
  // 693:     : (&node)
  // 694:       if length_of(arguments_of(node)) > 0:
  // 695:         if node::text_of(node) != "":
  // 696:           push &node.arguments_of node(.arguments_of undefined)
  // 697:         !node
  // 698:           function_call
  // 699:             .functor_of std_identifier("string")
  // 700:             .arguments_of arguments_of(node)
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
  // 694: ... arguments_of(node)
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
  // 694: ... length_of(arguments_of(node))
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
  // 694: ... length_of(arguments_of(node)) > 0
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
  // 694: ... :
  // 695:   if node::text_of(node) != "":
  // 696:     push &node.arguments_of node(.arguments_of undefined)
  // 697:   !node
  // 698:     function_call
  // 699:       .functor_of std_identifier("string")
  // 700:       .arguments_of arguments_of(node)
  // 701:       .is_a_string_template true
  // 702:       .fragment_of fragment_of(node)
  // 703:       .source_position_of source_position_of(node)
  // ...
  frame->slots[4] /* temp__4 */ = create_closure(entry__292_5, 0);
  // 694: if length_of(arguments_of(node)) > 0:
  // 695:   if node::text_of(node) != "":
  // 696:     push &node.arguments_of node(.arguments_of undefined)
  // 697:   !node
  // 698:     function_call
  // 699:       .functor_of std_identifier("string")
  // 700:       .arguments_of arguments_of(node)
  // 701:       .is_a_string_template true
  // 702:       .fragment_of fragment_of(node)
  // 703:       .source_position_of source_position_of(node)
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
  // 695: ... node::text_of(node)
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
  // 695: ... node::text_of(node) != ""
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
  // 695: ... node::text_of(node) != ""
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
  // 695: ... :
  // 696:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__292_9, 0);
  // 695: if node::text_of(node) != "":
  // 696:   push &node.arguments_of node(.arguments_of undefined)
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
  // 696: ... node.arguments_of
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
  // 696: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 696: push &node.arguments_of node(.arguments_of undefined)
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
  // 696: ... &node.arguments_of
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
  // 699: ... std_identifier("string")
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
  // 700: ... arguments_of(node)
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
  // 702: ... fragment_of(node)
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
  // 703: ... source_position_of(node)
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
  // 704: ... end_position_of(node)
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
  // 697: !node
  // 698:   function_call
  // 699:     .functor_of std_identifier("string")
  // 700:     .arguments_of arguments_of(node)
  // 701:     .is_a_string_template true
  // 702:     .fragment_of fragment_of(node)
  // 703:     .source_position_of source_position_of(node)
  // 704:     .end_position_of end_position_of(node)
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
  // 709: not_followed_by(indent_marker)
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
  // 710: set_node(string_literal)
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
  // 712: ... not_followed_by('@quot;')
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
  // 712: ... alt(STRING_INSERTION STRING_CHARACTER)
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
  // 712: ... not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER)
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
  // 712: some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
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
  // 713: expect('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__293_7;
}
static void cont__293_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 706: $STRING # This code has an astonishing capability to flatten template expressions!
  // 707:   sequence
  // 708:     '@quot;'
  // 709:     not_followed_by(indent_marker)
  // 710:     set_node(string_literal)
  // 711:     STORE_POSITION_MINUS_1
  // 712:     some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
  // 713:     expect('@quot;')
  // 714:     STORE_END_POSITION
  // 715:     CHECK_INSERTIONS
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
  // 720: ... '@@', OUTDENT
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
  // 720: followed_by('@@', OUTDENT)
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
  // 721: '@@', NEWLINE, STRING_LINE
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
  // 722: STRING_INSERTION, STRING_LINE
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
  // 723: STRING_CHARACTER, STRING_LINE
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
  // 717: $STRING_LINE
  // 718:   optional
  // 719:     alt
  // 720:       followed_by('@@', OUTDENT)
  // 721:       '@@', NEWLINE, STRING_LINE
  // 722:       STRING_INSERTION, STRING_LINE
  // 723:       STRING_CHARACTER, STRING_LINE
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
  // 725: $ADD_LINE_END
  // 726:   modify_node
  // 727:     : (&node)
  // 728:       append &node.node::text_of line_end_specifier_of(node)
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
  // 728: ... node.node::text_of
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
  // 728: ... line_end_specifier_of(node)
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
  // 728: append &node.node::text_of line_end_specifier_of(node)
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
  // 728: ... &node.node::text_of
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
  // 733: set_node(multi_line_string)
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
  // 737: ... NEWLINE, ADD_LINE_END, STRING_LINE
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
  // 737: some(NEWLINE, ADD_LINE_END, STRING_LINE)
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
  // 738: ... '@@', OUTDENT
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
  // 738: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__296_5;
}
static void cont__296_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 738: ... expect(outdent_marker), ADD_LINE_END
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
  // 738: alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
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
  // 730: $MULTI_LINE_STRING
  // 731:   sequence
  // 732:     '@quot;'
  // 733:     set_node(multi_line_string)
  // 734:     STORE_POSITION_MINUS_1
  // 735:     INDENT
  // 736:     STRING_LINE
  // 737:     some(NEWLINE, ADD_LINE_END, STRING_LINE)
  // 738:     alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
  // 739:     STORE_END_POSITION
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
  // 742: ... not_followed_by(LETTER)
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
  // 742: ... set_node(unique_item)
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
  // 742: $UNIQUE_ITEM '.', not_followed_by(LETTER), set_node(unique_item)
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
  // 747: ... syntax_error("expression expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__55df65a142fc9536;
  result_count = 1;
  myself = func__syntax_error;
  func = myself->type;
  frame->cont = cont__298_2;
}
static void cont__298_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 747: ... alt(EXPRESSION BODY syntax_error("expression expected"))
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
  // 747: inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = func__inline;
  func = myself->type;
  frame->cont = cont__298_4;
}
static void cont__298_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 748: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__298_5;
}
static void cont__298_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 744: $PARENTHESED_EXPRESSION
  // 745:   sequence
  // 746:     '('
  // 747:     inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  // 748:     expect(')')
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
  // 758: ... std_identifier("key_value_pair")
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
  // 759: ... std_identifier("true")
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
  // 759: ... list(node std_identifier("true"))
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
  // 760: ... fragment_of(node)
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
  // 761: ... source_position_of(node)
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
  // 761: ... source_position_of(node)+2
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
  // 756: ->
  // 757:   function_call
  // 758:     .functor_of std_identifier("key_value_pair")
  // 759:     .arguments_of list(node std_identifier("true"))
  // 760:     .fragment_of fragment_of(node)
  // 761:     .source_position_of source_position_of(node)+2
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
  // 750: $OPTION
  // 751:   sequence
  // 752:     "--"
  // 753:     IDENTIFIER
  // 754:     modify_node
  // 755:       : (node)
  // 756:         ->
  // 757:           function_call
  // 758:             .functor_of std_identifier("key_value_pair")
  // 759:             .arguments_of list(node std_identifier("true"))
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
  // 773: ... operator_symbol(.name_of "-")
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, string__578a5af303e9ccc);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 774: ... list(node)
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
  // 775: ... fragment_of(node)
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
  // 776: ... source_position_of(node)
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
  // 771: ->
  // 772:   function_call
  // 773:     .functor_of operator_symbol(.name_of "-")
  // 774:     .arguments_of list(node)
  // 775:     .fragment_of fragment_of(node)
  // 776:     .source_position_of source_position_of(node)
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
  // 764: $NEGATION
  // 765:   sequence
  // 766:     '-'
  // 767:     STORE_POSITION_MINUS_1
  // 768:     OPERAND
  // 769:     modify_node
  // 770:       : (node)
  // 771:         ->
  // 772:           function_call
  // 773:             .functor_of operator_symbol(.name_of "-")
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
  // 779: $SIMPLE_OPERAND
  // 780:   alt
  // 781:     NUMBER
  // 782:     CHARACTER
  // 783:     STRING
  // 784:     UNIQUE_ITEM
  // 785:     PARENTHESED_EXPRESSION
  // 786:     OPTION
  // 787:     NEGATION
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
  // 789: ... some(ATTRIBUTE_ACCESS)
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
  // 789: ... SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS)
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
  // 789: $OPERAND alt(IDENTIFIER_OR_FUNCTION_CALL SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS))
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
  // 791: $INFIX_OPERATOR_SYMBOL
  // 792:   alt
  // 793:     '*'
  // 794:     '/'
  // 795:     '+'
  // 796:     '-'
  // 797:     "<<"
  // 798:     "<="
  // 799:     "<"
  // 800:     ">>"
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
  // 814: ... multi_capture(operators_of INFIX_OPERATOR_SYMBOL)
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
  // 813: $SYMBOLIC_OPERATOR
  // 814:   infix_operator(multi_capture(operators_of INFIX_OPERATOR_SYMBOL))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = func__infix_operator;
  func = myself->type;
  frame->cont = cont__304_2;
}
static void cont__304_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SYMBOLIC_OPERATOR, arguments->slots[0]);
  // 816: ... multi_capture(operators_of ',')
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
  // 816: $COMMA_OPERATOR multi_capture(operators_of ','), compiler::WHITESPACE
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
  // 822: multi_span(operators_of IDENTIFIER)
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
  // 824: expect(compiler::WHITESPACE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__306_2;
}
static void cont__306_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 818: $NAMED_OPERATOR
  // 819:   sequence
  // 820:     compiler::WHITESPACE
  // 821:     '.'
  // 822:     multi_span(operators_of IDENTIFIER)
  // 823:     '.'
  // 824:     expect(compiler::WHITESPACE)
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
  // 828: alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
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
  // 831: ... 1
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
  // 831: ... operators_of(node)
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
  // 831: ... operators_of(node)(-1)
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
  // 831: $operator_precedence precedence(operators_of(node)(-1))
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
  // 832: $lowest_precedence lowest_precedence_of(node)
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
  // 835: lowest_precedence.is_undefined
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
  // 836: operator_precedence < lowest_precedence
  frame->slots[5] /* temp__3 */ = create_closure(entry__307_9, 0);
  // 834: ||
  // 835:   lowest_precedence.is_undefined
  // 836:   operator_precedence < lowest_precedence
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
  // 836: operator_precedence < lowest_precedence
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
  // 836: operator_precedence < lowest_precedence
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
  // 837: :
  // 838:   !node.lowest_precedence_of operator_precedence
  frame->slots[6] /* temp__4 */ = create_closure(entry__307_12, 0);
  // 833: if
  // 834:   ||
  // 835:     lowest_precedence.is_undefined
  // 836:     operator_precedence < lowest_precedence
  // 837:   :
  // 838:     !node.lowest_precedence_of operator_precedence
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
  // 838: !node.lowest_precedence_of
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
  // 826: $INFIX_OPERATOR
  // 827:   sequence
  // 828:     alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
  // 829:     modify_node
  // 830:       : (&node)
  // 831:         $operator_precedence precedence(operators_of(node)(-1))
  // 832:         $lowest_precedence lowest_precedence_of(node)
  // 833:         if
  // 834:           ||
  // 835:             lowest_precedence.is_undefined
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
  // 840: $EXTEND_EXPRESSION
  // 841:   modify_node
  // 842:     : (&node)
  // 843:       $parent parent_of(node)
  // 844:       $arguments arguments_of(node)
  // 845:       $n length_of(arguments)
  // 846:       if
  // 847:         n == 1:
  // 848:           !node arguments(1)
  // 849:         :
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
  // 843: $parent parent_of(node)
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
  // 844: $arguments arguments_of(node)
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
  // 845: $n length_of(arguments)
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
  // 847: n == 1
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
  // 847: ... :
  // 848:   !node arguments(1)
  frame->slots[5] /* temp__2 */ = create_closure(entry__308_6, 0);
  // 849: :
  // 850:   $operators operators_of(node)
  // 851:   $$operand_stack list(arguments(1))
  // 852:   $$operator_stack list(operators(1))
  // 853:   
  // 854:   $update_stack: ($right next_operator)
  // 855:     $next_prec
  // 856:       if
  // 857:         next_operator.is_defined
  // 858:         -> precedence(next_operator)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__308_8, 0);
  // 846: if
  // 847:   n == 1:
  // 848:     !node arguments(1)
  // 849:   :
  // 850:     $operators operators_of(node)
  // 851:     $$operand_stack list(arguments(1))
  // 852:     $$operator_stack list(operators(1))
  // 853:     
  // 854:     $update_stack: ($right next_operator)
  // 855:       $next_prec
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
  // 848: !node arguments(1)
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
  // 854: ... : ($right next_operator)
  // 855:   $next_prec
  // 856:     if
  // 857:       next_operator.is_defined
  // 858:       -> precedence(next_operator)
  // 859:       -> 0
  // 860:   
  // 861:   do: (-> break)
  // 862:     forever:
  // 863:       $operator peek(operator_stack)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__308_9, 2);
  // 854: $update_stack: ($right next_operator)
  // 855:   $next_prec
  // 856:     if
  // 857:       next_operator.is_defined
  // 858:       -> precedence(next_operator)
  // 859:       -> 0
  // 860:   
  // 861:   do: (-> break)
  // 862:     forever:
  // 863:       $operator peek(operator_stack)
  // ...
  initialize_future(frame->slots[6] /* update_stack */, frame->slots[7] /* temp__1 */);
  // 850: $operators operators_of(node)
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
  // 857: next_operator.is_defined
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
  // 858: -> precedence(next_operator)
  frame->slots[6] /* temp__2 */ = create_closure(entry__308_11, 0);
  // 855: $next_prec
  // 856:   if
  // 857:     next_operator.is_defined
  // 858:     -> precedence(next_operator)
  // 859:     -> 0
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
  // 858: ... precedence(next_operator)
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
  // 858: -> precedence(next_operator)
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
  // 859: -> 0
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
  // 861: ... : (-> break)
  // 862:   forever:
  // 863:     $operator peek(operator_stack)
  // 864:     $prec precedence(operator)
  // 865:     if next_prec > prec break
  // 866:     if next_prec == prec && is_right_associative(prec) break
  // 867:     
  // 868:     $functor
  // 869:       if
  // 870:         operator.is_a_string
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__308_15, 0);
  // 861: do: (-> break)
  // 862:   forever:
  // 863:     $operator peek(operator_stack)
  // 864:     $prec precedence(operator)
  // 865:     if next_prec > prec break
  // 866:     if next_prec == prec && is_right_associative(prec) break
  // 867:     
  // 868:     $functor
  // 869:       if
  // 870:         operator.is_a_string
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
  // 862: ... :
  // 863:   $operator peek(operator_stack)
  // 864:   $prec precedence(operator)
  // 865:   if next_prec > prec break
  // 866:   if next_prec == prec && is_right_associative(prec) break
  // 867:   
  // 868:   $functor
  // 869:     if
  // 870:       operator.is_a_string
  // 871:       -> operator_symbol(.name_of operator)
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__308_16, 0);
  // 862: forever:
  // 863:   $operator peek(operator_stack)
  // 864:   $prec precedence(operator)
  // 865:   if next_prec > prec break
  // 866:   if next_prec == prec && is_right_associative(prec) break
  // 867:   
  // 868:   $functor
  // 869:     if
  // 870:       operator.is_a_string
  // 871:       -> operator_symbol(.name_of operator)
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
  // 863: $operator peek(operator_stack)
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
  // 864: $prec precedence(operator)
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
  // 865: ... next_prec > prec
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
  // 865: if next_prec > prec break
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
  // 866: ... next_prec == prec
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
  // 866: ... is_right_associative(prec)
  frame->slots[12] /* temp__3 */ = create_closure(entry__308_22, 0);
  // 866: ... next_prec == prec && is_right_associative(prec)
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
  // 866: ... is_right_associative(prec)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* prec */;
  result_count = 1;
  myself = func__is_right_associative;
  func = myself->type;
  frame->cont = cont__308_23;
}
static void cont__308_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 866: ... is_right_associative(prec)
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
  // 866: if next_prec == prec && is_right_associative(prec) break
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
  // 870: operator.is_a_string
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
  // 871: -> operator_symbol(.name_of operator)
  frame->slots[11] /* temp__2 */ = create_closure(entry__308_27, 0);
  // 872: -> operator
  frame->slots[12] /* temp__3 */ = create_closure(entry__308_28, 0);
  // 868: $functor
  // 869:   if
  // 870:     operator.is_a_string
  // 871:     -> operator_symbol(.name_of operator)
  // 872:     -> operator
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
  // 871: ... operator_symbol(.name_of operator)
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[0] /* operator */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 871: -> operator_symbol(.name_of operator)
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
  // 872: -> operator
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
  // 874: $left pop(&operand_stack)
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
  // 878: ... list(left right)
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
  // 880: ... fragment_of(left)
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
  // 881: ... source_position_of(left)
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
  // 882: ... end_position_of(right)
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
  // 875: !right
  // 876:   function_call
  // 877:     .functor_of functor
  // 878:     .arguments_of list(left right)
  // 879:     .is_in_infix_notation true
  // 880:     .fragment_of fragment_of(left)
  // 881:     .source_position_of source_position_of(left)
  // 882:     .end_position_of end_position_of(right)
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
  // 883: pop &operator_stack $_dummy
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
  // 884: ... length_of(operator_stack)
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
  // 884: ... length_of(operator_stack) == 0
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
  // 884: if length_of(operator_stack) == 0 break
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
  // 885: push &operand_stack right
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
  // 886: push &operator_stack next_operator
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
  // 851: ... arguments(1)
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
  // 851: $$operand_stack list(arguments(1))
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
  // 852: ... operators(1)
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
  // 852: $$operator_stack list(operators(1))
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
  // 888: ... : (i)
  // 889:   update_stack
  // 890:     arguments(i)
  // 891:     if
  // 892:       i < n
  // 893:       -> operators(i)
  // 894:       -> undefined
  frame->slots[7] /* temp__1 */ = create_closure(entry__308_47, 1);
  // 888: from_to 2 n: (i)
  // 889:   update_stack
  // 890:     arguments(i)
  // 891:     if
  // 892:       i < n
  // 893:       -> operators(i)
  // 894:       -> undefined
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
  // 890: arguments(i)
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
  // 892: i < n
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
  // 893: -> operators(i)
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
  // 893: ... operators(i)
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
  // 893: -> operators(i)
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
  // 894: -> undefined
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
  // 889: update_stack
  // 890:   arguments(i)
  // 891:   if
  // 892:     i < n
  // 893:     -> operators(i)
  // 894:     -> undefined
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
  // 895: !node peek(operand_stack)
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
  // 896: ... parent.is_defined
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
  // 896: ... :
  // 897:   !node parent(.arguments_of push(arguments_of(parent) node))
  frame->slots[5] /* temp__2 */ = create_closure(entry__308_58, 0);
  // 896: if parent.is_defined:
  // 897:   !node parent(.arguments_of push(arguments_of(parent) node))
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
  // 897: ... arguments_of(parent)
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
  // 897: ... push(arguments_of(parent) node)
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
  // 897: !node parent(.arguments_of push(arguments_of(parent) node))
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
  // 901: set_node(expression)
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
  // 902: arguments_span(OPERAND)
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
  // 903: ... arguments_span(OPERAND)
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
  // 903: ... INFIX_OPERATOR, arguments_span(OPERAND)
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
  // 903: some(INFIX_OPERATOR, arguments_span(OPERAND))
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
  // 905: ... multi_capture(operators_of '=')
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
  // 905: infix_operator(multi_capture(operators_of '='))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = func__infix_operator;
  func = myself->type;
  frame->cont = cont__309_7;
}
static void cont__309_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 905: infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
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
  // 899: $EXPRESSION
  // 900:   sequence
  // 901:     set_node(expression)
  // 902:     arguments_span(OPERAND)
  // 903:     some(INFIX_OPERATOR, arguments_span(OPERAND))
  // 904:     optional
  // 905:       infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  // 906:     EXTEND_EXPRESSION
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
  // 908: ... span(identifier_of DEFINE_IDENTIFIER)
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
  // 908: $DEFINED_VARIABLE expect(span(identifier_of DEFINE_IDENTIFIER) "identifier")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__395c5a51a203e553;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__310_3;
}
static void cont__310_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINED_VARIABLE, arguments->slots[0]);
  // 911: ... set_field(is_used_as_a_polymorphic_function true)
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
  // 910: $NAME_OF_POLYMORPHIC
  // 911:   IDENTIFIER, set_field(is_used_as_a_polymorphic_function true)
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
  // 921: set_field(attribute_kind_of ATTRIBUTE_KIND)
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
  // 922: span(attribute_of NAME_OF_POLYMORPHIC)
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
  // 925: followed_by(':')
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
  // 926: set_field(attribute_kind_of METHOD_KIND)
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
  // 929: set_field(attribute_kind_of METHOD_KIND)
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
  // 930: span(attribute_of NAME_OF_POLYMORPHIC)
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
  // 913: $DEFINED_VARIABLE_OR_ATTRIBUTE
  // 914:   sequence
  // 915:     DEFINED_VARIABLE
  // 916:     optional
  // 917:       sequence
  // 918:         alt
  // 919:           sequence
  // 920:             '.'
  // 921:             set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 922:             span(attribute_of NAME_OF_POLYMORPHIC)
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
  // 933: ... set_node(define_static_single)
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
  // 932: $DEFINE_STATIC_SINGLE
  // 933:   '$', set_node(define_static_single), DEFINED_VARIABLE_OR_ATTRIBUTE
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
  // 935: ... set_node(define_static_multi)
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
  // 935: $DEFINE_STATIC_MULTI "$$", set_node(define_static_multi), DEFINED_VARIABLE
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
  // 936: ... set_node(define_dynamic_single)
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
  // 936: $DEFINE_DYNAMIC_SINGLE '%', set_node(define_dynamic_single), DEFINED_VARIABLE
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
  // 937: ... set_node(define_dynamic_multi)
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
  // 937: $DEFINE_DYNAMIC_MULTI "%%", set_node(define_dynamic_multi), DEFINED_VARIABLE
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
  // 946: ... list(node)
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
  // 949: ... fragment_of(node)
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
  // 950: ... source_position_of(node)
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
  // 944: !node
  // 945:   function_call
  // 946:     .arguments_of list(node)
  // 947:     .is_an_attribute_access true
  // 948:     .is_a_method_definition true
  // 949:     .fragment_of fragment_of(node)
  // 950:     .source_position_of source_position_of(node)
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
  // 951: ... followed_by(':')
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
  // 951: ... span(functor_of NAME_OF_POLYMORPHIC)
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
  // 951: alt(followed_by(':') span(functor_of NAME_OF_POLYMORPHIC))
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
  // 939: $METHOD_DEFINITION
  // 940:   sequence
  // 941:     '/'
  // 942:     modify_node
  // 943:       : (&node)
  // 944:         !node
  // 945:           function_call
  // 946:             .arguments_of list(node)
  // 947:             .is_an_attribute_access true
  // 948:             .is_a_method_definition true
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
  // 958: optional(METHOD_DEFINITION)
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
  // 959: set_field(is_a_destination true)
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
  // 954: $ASSIGN
  // 955:   sequence
  // 956:     '!'
  // 957:     READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 958:     optional(METHOD_DEFINITION)
  // 959:     set_field(is_a_destination true)
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
  // 961: $DESTINATION
  // 962:   alt
  // 963:     DEFINE_STATIC_MULTI
  // 964:     DEFINE_STATIC_SINGLE
  // 965:     DEFINE_DYNAMIC_MULTI
  // 966:     DEFINE_DYNAMIC_SINGLE
  // 967:     ASSIGN
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
  // 972: set_node(backquoted)
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
  // 973: ... alt(OPERAND DESTINATION)
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
  // 973: ... span(expression_of alt(OPERAND DESTINATION))
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
  // 973: capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
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
  // 969: $BACKQUOTED
  // 970:   sequence
  // 971:     '`'
  // 972:     set_node(backquoted)
  // 973:     capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
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
  // 977: ... set_field(is_an_optional_item true)
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
  // 977: '?', set_field(is_an_optional_item true)
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
  // 978: ... set_field(is_an_expanded_item true)
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
  // 978: '*', set_field(is_an_expanded_item true)
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
  // 975: $EXPANSION
  // 976:   alt
  // 977:     '?', set_field(is_an_optional_item true)
  // 978:     '*', set_field(is_an_expanded_item true)
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
  // 980: ... optional(EXPANSION)
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
  // 980: $OUTPUT_ARGUMENT DESTINATION, optional(EXPANSION)
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
  // 986: set_field(is_a_destination true)
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
  // 987: set_field(is_an_input_output_argument true)
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
  // 988: optional(EXPANSION)
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
  // 982: $INPUT_OUTPUT_ARGUMENT
  // 983:   sequence
  // 984:     '&'
  // 985:     READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 986:     set_field(is_a_destination true)
  // 987:     set_field(is_an_input_output_argument true)
  // 988:     optional(EXPANSION)
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
  // 990: ... alt(EXPRESSION BODY MULTI_LINE_STRING)
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
  // 990: $INPUT_ARGUMENT arguments_span(alt(EXPRESSION BODY MULTI_LINE_STRING))
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
  // 995: span(identifier_of NAME_OF_POLYMORPHIC)
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
  // 996: ... compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT
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
  // 996: optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
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
  // 998: ... CHECK_ARGUMENTS("attribute value" 0 1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__5b01b0908c396eea;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__1;
  result_count = 1;
  myself = func__CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__325_5;
}
static void cont__325_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 998: INDENTED_ARGUMENTS, CHECK_ARGUMENTS("attribute value" 0 1)
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
  // 999: SEPARATOR, INPUT_ARGUMENT
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
  //  992: $VALUE_ARGUMENT
  //  993:   sequence
  //  994:     STORE_POSITION_MINUS_1
  //  995:     span(identifier_of NAME_OF_POLYMORPHIC)
  //  996:     optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
  //  997:     alt
  //  998:       INDENTED_ARGUMENTS, CHECK_ARGUMENTS("attribute value" 0 1)
  //  999:       SEPARATOR, INPUT_ARGUMENT
  // 1000:     STORE_END_POSITION
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
  // 1007: ... set_node(attribute_value_pair)
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
  // 1007: ... sequence(set_node(attribute_value_pair) VALUE_ARGUMENT)
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
  // 1007: arguments_span(sequence(set_node(attribute_value_pair) VALUE_ARGUMENT))
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
  // 1010: followed_by(':')
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
  // 1013: set_node(attribute_function_pair)
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
  // 1015: arguments_span(BODY)
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
  // 1021: ... set_node(attribute_function_pair)
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
  // 1021: sequence(set_node(attribute_function_pair) VALUE_ARGUMENT)
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
  // 1002: $ATTRIBUTE_VALUE_PAIR
  // 1003:   sequence
  // 1004:     alt
  // 1005:       sequence
  // 1006:         '.'
  // 1007:         arguments_span(sequence(set_node(attribute_value_pair) VALUE_ARGUMENT))
  // 1008:       sequence
  // 1009:         '/'
  // 1010:         followed_by(':')
  // 1011:         arguments_span
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
  // 1025: ... arguments_span(OPERAND)
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
  // 1025: sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
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
  // 1023: $OPERATORS_AND_OPERANDS
  // 1024:   alt
  // 1025:     sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
  // 1026:     EXTEND_EXPRESSION
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
  // 1030: set_node(operator_symbol)
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
  // 1032: capture(name_of INFIX_OPERATOR_SYMBOL)
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
  // 1038: ... fragment_of(node)
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
  // 1039: ... source_position_of(node)
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
  // 1035: ->
  // 1036:   function_call
  // 1037:     .functor_of node
  // 1038:     .fragment_of fragment_of(node)
  // 1039:     .source_position_of source_position_of(node)
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
  // 1040: ... compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT
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
  // 1040: optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
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
  // 1043: CHECK_ARGUMENTS("multi line expression" 0)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__137554cc13b7640e;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = func__CHECK_ARGUMENTS;
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
  // 1051: $$arguments arguments_of(node)
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
  // 1052: ... length_of(arguments)
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
  // 1052: ... length_of(arguments) < 2
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
  // 1052: ... :
  // 1053:   ParseError stream "too few arguments in multi-line expression"
  frame->slots[6] /* temp__3 */ = create_closure(entry__328_15, 0);
  // 1052: if length_of(arguments) < 2:
  // 1053:   ParseError stream "too few arguments in multi-line expression"
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
  // 1053: ParseError stream "too few arguments in multi-line expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__733ccdbfc49ced05;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__328_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1054: ... length_of(arguments)
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
  // 1054: ... length_of(arguments) > 2
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
  // 1054: ... :
  // 1055:   $functor functor_of(node)
  // 1056:   if
  // 1057:     precedence(name_of(functor)).is_left_associative:
  // 1058:       forever:
  // 1059:         !node
  // 1060:           function_call
  // 1061:             .functor_of functor
  // 1062:             .arguments_of range(arguments 1 2)
  // 1063:         if length_of(arguments) == 2 return
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__328_20, 0);
  // 1054: if length_of(arguments) > 2:
  // 1055:   $functor functor_of(node)
  // 1056:   if
  // 1057:     precedence(name_of(functor)).is_left_associative:
  // 1058:       forever:
  // 1059:         !node
  // 1060:           function_call
  // 1061:             .functor_of functor
  // 1062:             .arguments_of range(arguments 1 2)
  // 1063:         if length_of(arguments) == 2 return
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
  // 1070: ... 2
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
  // 1070: ... 1
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
  // 1070: ... range(arguments -2 -1)
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
  // 1067: !node
  // 1068:   function_call
  // 1069:     .functor_of functor
  // 1070:     .arguments_of range(arguments -2 -1)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1071: ... length_of(arguments)
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
  // 1071: ... length_of(arguments) == 2
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
  // 1071: if length_of(arguments) == 2 return
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
  // 1072: ... 3
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
  // 1072: ... range(arguments 1 -3)
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
  // 1072: !arguments push(range(arguments 1 -3) node)
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
  // 1062: ... range(arguments 1 2)
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
  // 1059: !node
  // 1060:   function_call
  // 1061:     .functor_of functor
  // 1062:     .arguments_of range(arguments 1 2)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1063: ... length_of(arguments)
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
  // 1063: ... length_of(arguments) == 2
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
  // 1063: if length_of(arguments) == 2 return
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
  // 1064: ... 1
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
  // 1064: ... range(arguments 3 -1)
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
  // 1064: !arguments put(range(arguments 3 -1) node)
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
  // 1058: ... :
  // 1059:   !node
  // 1060:     function_call
  // 1061:       .functor_of functor
  // 1062:       .arguments_of range(arguments 1 2)
  // 1063:   if length_of(arguments) == 2 return
  // 1064:   !arguments put(range(arguments 3 -1) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__328_26, 0);
  // 1058: forever:
  // 1059:   !node
  // 1060:     function_call
  // 1061:       .functor_of functor
  // 1062:       .arguments_of range(arguments 1 2)
  // 1063:   if length_of(arguments) == 2 return
  // 1064:   !arguments put(range(arguments 3 -1) node)
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
  // 1066: ... :
  // 1067:   !node
  // 1068:     function_call
  // 1069:       .functor_of functor
  // 1070:       .arguments_of range(arguments -2 -1)
  // 1071:   if length_of(arguments) == 2 return
  // 1072:   !arguments push(range(arguments 1 -3) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__328_35, 0);
  // 1066: forever:
  // 1067:   !node
  // 1068:     function_call
  // 1069:       .functor_of functor
  // 1070:       .arguments_of range(arguments -2 -1)
  // 1071:   if length_of(arguments) == 2 return
  // 1072:   !arguments push(range(arguments 1 -3) node)
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
  // 1055: $functor functor_of(node)
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
  // 1057: ... name_of(functor)
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
  // 1057: precedence(name_of(functor))
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
  // 1057: precedence(name_of(functor)).is_left_associative
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
  // 1057: ... :
  // 1058:   forever:
  // 1059:     !node
  // 1060:       function_call
  // 1061:         .functor_of functor
  // 1062:         .arguments_of range(arguments 1 2)
  // 1063:     if length_of(arguments) == 2 return
  // 1064:     !arguments put(range(arguments 3 -1) node)
  frame->slots[7] /* temp__4 */ = create_closure(entry__328_25, 0);
  // 1065: :
  // 1066:   forever:
  // 1067:     !node
  // 1068:       function_call
  // 1069:         .functor_of functor
  // 1070:         .arguments_of range(arguments -2 -1)
  // 1071:     if length_of(arguments) == 2 return
  // 1072:     !arguments push(range(arguments 1 -3) node)
  frame->slots[8] /* temp__5 */ = create_closure(entry__328_34, 0);
  // 1056: if
  // 1057:   precedence(name_of(functor)).is_left_associative:
  // 1058:     forever:
  // 1059:       !node
  // 1060:         function_call
  // 1061:           .functor_of functor
  // 1062:           .arguments_of range(arguments 1 2)
  // 1063:       if length_of(arguments) == 2 return
  // 1064:       !arguments put(range(arguments 3 -1) node)
  // 1065:   :
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
  // 1028: $MULTI_LINE_EXPRESSION
  // 1029:   sequence
  // 1030:     set_node(operator_symbol)
  // 1031:     STORE_POSITION
  // 1032:     capture(name_of INFIX_OPERATOR_SYMBOL)
  // 1033:     modify_node
  // 1034:       : (node)
  // 1035:         ->
  // 1036:           function_call
  // 1037:             .functor_of node
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
  // 1079: set_node(define_static_multi)
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
  // 1080: set_field(parameter_kind_of IN_PARAMETER)
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
  // 1083: set_node(define_static_multi)
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
  // 1084: set_field(parameter_kind_of OUT_PARAMETER)
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
  // 1087: set_node(define_static_multi)
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
  // 1088: set_field(parameter_kind_of IN_OUT_PARAMETER)
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
  // 1089: set_node(define_static_single)
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
  // 1089: ... set_field(parameter_kind_of IN_PARAMETER)
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
  // 1089: set_node(define_static_single), set_field(parameter_kind_of IN_PARAMETER)
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
  // 1074: $PARAMETER_MODE
  // 1075:   optional
  // 1076:     alt
  // 1077:       sequence
  // 1078:         '$'
  // 1079:         set_node(define_static_multi)
  // 1080:         set_field(parameter_kind_of IN_PARAMETER)
  // 1081:       sequence
  // 1082:         '!'
  // 1083:         set_node(define_static_multi)
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
  // 1096: infix_operator('=')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__61;
  result_count = 1;
  myself = func__infix_operator;
  func = myself->type;
  frame->cont = cont__330_1;
}
static void cont__330_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1097: set_field(is_an_optional_item true)
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
  // 1098: span(default_value_of EXPRESSION)
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
  // 1099: ... set_field(parameter_kind_of MYSELF_PARAMETER)
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
  // 1099: '^', set_field(parameter_kind_of MYSELF_PARAMETER)
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
  // 1091: $PARAMETER_COUNT_OR_MYSELF
  // 1092:   optional
  // 1093:     alt
  // 1094:       EXPANSION
  // 1095:       sequence
  // 1096:         infix_operator('=')
  // 1097:         set_field(is_an_optional_item true)
  // 1098:         span(default_value_of EXPRESSION)
  // 1099:       '^', set_field(parameter_kind_of MYSELF_PARAMETER)
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
  // 1106: !node.is_not_used
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
  // 1101: $NOT_USED
  // 1102:   sequence
  // 1103:     '_'
  // 1104:     modify_node
  // 1105:       : (&node)
  // 1106:         !node.is_not_used true
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
  // 1112: set_node(identifier)
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
  // 1114: optional(NOT_USED)
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
  // 1115: capture(name_of NAME)
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
  // 1108: $PARAMETER_NAME
  // 1109:   span
  // 1110:     identifier_of
  // 1111:     sequence
  // 1112:       set_node(identifier)
  // 1113:       STORE_POSITION
  // 1114:       optional(NOT_USED)
  // 1115:       capture(name_of NAME)
  // 1116:       STORE_END_POSITION
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
  // 1118: $PARAMETER PARAMETER_MODE, PARAMETER_NAME, PARAMETER_COUNT_OR_MYSELF
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
  // 1121: ... optional(LINE_END_REMARK)
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
  // 1121: ... INDENT, REMARK, OUTDENT
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
  // 1121: ... optional(INDENT, REMARK, OUTDENT)
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
  // 1120: $MULTI_LINE_PARAMETER
  // 1121:   PARAMETER, optional(LINE_END_REMARK), optional(INDENT, REMARK, OUTDENT)
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
  // 1127: set_node(define_static_single)
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
  // 1128: set_field(parameter_kind_of CONTINUATION_PARAMETER)
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
  // 1123: $CONTINUATION
  // 1124:   sequence
  // 1125:     "->"
  // 1126:     compiler::WHITESPACE
  // 1127:     set_node(define_static_single)
  // 1128:     set_field(parameter_kind_of CONTINUATION_PARAMETER)
  // 1129:     PARAMETER_NAME
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
  // 1132: ... optional(LINE_END_REMARK)
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
  // 1132: ... INDENT, REMARK, OUTDENT
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
  // 1132: ... optional(INDENT, REMARK, OUTDENT)
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
  // 1131: $MULTI_LINE_CONTINUATION
  // 1132:   CONTINUATION, optional(LINE_END_REMARK), optional(INDENT, REMARK, OUTDENT)
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
  // 1140: ... multi_span(parameters_of PARAMETER)
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
  // 1140: interleaved(multi_span(parameters_of PARAMETER) compiler::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__337_2;
}
static void cont__337_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1141: ... multi_span(parameters_of CONTINUATION)
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
  // 1141: ... compiler::WHITESPACE, multi_span(parameters_of CONTINUATION)
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
  // 1141: optional(compiler::WHITESPACE, multi_span(parameters_of CONTINUATION))
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
  // 1142: multi_span(parameters_of CONTINUATION)
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
  // 1143: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__337_10;
}
static void cont__337_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1134: $INLINE_PARAMETERS
  // 1135:   sequence
  // 1136:     '('
  // 1137:     optional
  // 1138:       alt
  // 1139:         sequence
  // 1140:           interleaved(multi_span(parameters_of PARAMETER) compiler::WHITESPACE)
  // 1141:           optional(compiler::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1142:         multi_span(parameters_of CONTINUATION)
  // 1143:     expect(')')
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
  // 1151: ... multi_span(parameters_of MULTI_LINE_PARAMETER)
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
  // 1151: interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._NEWLINE;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__338_2;
}
static void cont__338_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1152: ... multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  // 1152: ... NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  // 1152: optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
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
  // 1153: multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  // 1154: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__338_9;
}
static void cont__338_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1155: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__338_10;
}
static void cont__338_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1156: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__338_11;
}
static void cont__338_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1145: $MULTI_LINE_PARAMETERS
  // 1146:   sequence
  // 1147:     '('
  // 1148:     INDENT
  // 1149:     alt
  // 1150:       sequence
  // 1151:         interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1152:         optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  // 1153:       multi_span(parameters_of MULTI_LINE_CONTINUATION)
  // 1154:     expect(outdent_marker)
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
  // 1161: set_node(body)
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
  // 1165: optional(LINE_END_REMARK)
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
  // 1167: ... multi_span(statements_of REMARK_STATEMENT)
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
  // 1167: ... multi_span(statements_of REMARK_STATEMENT), NEWLINES
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
  // 1167: some(multi_span(statements_of REMARK_STATEMENT), NEWLINES)
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
  // 1174: ... statements_of(node)
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
  // 1174: ... : (remark_statement)
  // 1175:   append &node.remark_lines_of remark_lines_of(remark_statement)
  frame->slots[2] /* temp__2 */ = create_closure(entry__339_8, 1);
  // 1174: for_each statements_of(node): (remark_statement)
  // 1175:   append &node.remark_lines_of remark_lines_of(remark_statement)
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
  // 1175: ... node.remark_lines_of
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
  // 1175: ... remark_lines_of(remark_statement)
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
  // 1175: append &node.remark_lines_of remark_lines_of(remark_statement)
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
  // 1175: ... &node.remark_lines_of
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
  // 1176: !node.statements_of
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
  // 1177: optional(NEWLINES)
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
  // 1179: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = func__expect;
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
  // 1181: ... compiler::WHITESPACE, INLINE_PARAMETERS
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
  // 1181: optional(compiler::WHITESPACE, INLINE_PARAMETERS)
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
  // 1182: optional(LINE_END_REMARK)
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
  // 1184: ... multi_span(statements_of STATEMENT)
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
  // 1184: compiler::WHITESPACE, multi_span(statements_of STATEMENT)
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
  // 1185: ... optional(NEWLINES)
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
  // 1185: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__339_25;
}
static void cont__339_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__22 */ = arguments->slots[0];
  // 1185: sequence(INDENT optional(NEWLINES) STATEMENTS expect(outdent_marker))
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
  // 1158: $COMPLETE_BODY
  // 1159:   sequence
  // 1160:     ':'
  // 1161:     set_node(body)
  // 1162:     STORE_POSITION_MINUS_1
  // 1163:     alt
  // 1164:       sequence
  // 1165:         optional(LINE_END_REMARK)
  // 1166:         INDENT
  // 1167:         some(multi_span(statements_of REMARK_STATEMENT), NEWLINES)
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
  // 1190: followed_by("->")
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
  // 1191: set_node(body)
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
  // 1193: multi_span(statements_of RETURN_STATEMENT)
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
  // 1188: $RETURN_EXPRESSION
  // 1189:   sequence
  // 1190:     followed_by("->")
  // 1191:     set_node(body)
  // 1192:     STORE_POSITION
  // 1193:     multi_span(statements_of RETURN_STATEMENT)
  // 1194:     STORE_END_POSITION
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
  // 1196: $BODY alt(COMPLETE_BODY RETURN_EXPRESSION)
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
  // 1201: set_node(c_body)
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
  // 1203: expect(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__342_2;
}
static void cont__342_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1204: ... not_followed_by(OUTDENT)
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
  // 1204: ... not_followed_by(OUTDENT), ANY_CHARACTER
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
  // 1204: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
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
  // 1204: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
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
  // 1205: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__342_7;
}
static void cont__342_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1206: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__342_8;
}
static void cont__342_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1207: expect('}')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__125;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__342_9;
}
static void cont__342_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1198: $C_BODY
  // 1199:   sequence
  // 1200:     '{'
  // 1201:     set_node(c_body)
  // 1202:     STORE_POSITION_MINUS_1
  // 1203:     expect(indent_marker)
  // 1204:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  // 1205:     expect(outdent_marker)
  // 1206:     expect(newline)
  // 1207:     expect('}')
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
  // 1210: ... alt(BODY C_BODY MULTI_LINE_STRING)
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
  // 1210: $LINE_END_EXPRESSION arguments_span(alt(BODY C_BODY MULTI_LINE_STRING))
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
  // 1211: ... set_node(polymorphic_function)
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
  // 1211: $POLYMORPHIC_FUNCTION_WITHOUT_SETTER "()", set_node(polymorphic_function)
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
  // 1214: ... set_node(polymorphic_function_with_setter)
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
  // 1213: $POLYMORPHIC_FUNCTION_WITH_SETTER
  // 1214:   "(!)", set_node(polymorphic_function_with_setter)
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
  // 1216: $POLYMORPHIC_FUNCTION
  // 1217:   alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
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
  // 1219: $FUNCTOR span(functor_of IDENTIFIER_OR_FUNCTION_CALL)
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
  // 1223: ... span(result_count_of EXPRESSION)
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
  // 1223: ".(", span(result_count_of EXPRESSION), ')'
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
  // 1224: ... span(continuation_of IDENTIFIER)
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
  // 1224: '/', span(continuation_of IDENTIFIER)
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
  // 1221: $RESULT_COUNT_OR_CONTINUATION
  // 1222:   alt
  // 1223:     ".(", span(result_count_of EXPRESSION), ')'
  // 1224:     '/', span(continuation_of IDENTIFIER)
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
  // 1231: ... optional(EXPANSION)
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
  // 1231: EXPRESSION, optional(EXPANSION)
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
  // 1234: ... optional(EXPANSION)
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
  // 1234: DESTINATION, optional(EXPANSION)
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
  // 1236: ... '@quot;', indent_marker
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
  // 1236: followed_by('@quot;', indent_marker)
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
  // 1237: followed_by(':')
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
  // 1238: followed_by('#')
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
  // 1239: followed_by('{')
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
  // 1240: followed_by("->")
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
  // 1241: syntax_error("argument expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__e1e3be9ec64af0e1;
  result_count = 1;
  myself = func__syntax_error;
  func = myself->type;
  frame->cont = cont__349_14;
}
static void cont__349_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1226: $ARGUMENT
  // 1227:   alt
  // 1228:     arguments_span
  // 1229:       alt
  // 1230:         POLYMORPHIC_FUNCTION
  // 1231:         EXPRESSION, optional(EXPANSION)
  // 1232:         INPUT_OUTPUT_ARGUMENT
  // 1233:         BACKQUOTED
  // 1234:         DESTINATION, optional(EXPANSION)
  // 1235:     ATTRIBUTE_VALUE_PAIR
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
  // 1245: ... compiler::WHITESPACE, ARGUMENT
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
  // 1245: some(compiler::WHITESPACE, ARGUMENT)
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
  // 1246: optional(LINE_END_REMARK_ARGUMENT)
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
  // 1243: $FIRST_LINE_ARGUMENTS
  // 1244:   sequence
  // 1245:     some(compiler::WHITESPACE, ARGUMENT)
  // 1246:     optional(LINE_END_REMARK_ARGUMENT)
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
  // 1252: ... compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT
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
  // 1252: optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
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
  // 1256: $arguments arguments_of(node)
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
  // 1257: $functor arguments(arguments_index)
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
  // 1262: ... arguments_index+1
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
  // 1262: ... 1
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
  // 1262: ... range(arguments arguments_index+1 -1)
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
  // 1263: ... fragment_of(node)
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
  // 1264: ... source_position_of(node)
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
  // 1259: $$argument
  // 1260:   function_call
  // 1261:     .functor_of functor
  // 1262:     .arguments_of range(arguments arguments_index+1 -1)
  // 1263:     .fragment_of fragment_of(node)
  // 1264:     .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[7] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[8] /* temp__5 */);
    ((CELL *)frame->slots[3])->contents /* argument */ = temp;

  }
  // 1266: check_arguments argument "function call"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* argument */;
  arguments->slots[1] = string__4456c807200257a4;
  result_count = 0;
  myself = func__check_arguments;
  func = myself->type;
  frame->cont = cont__351_11;
}
static void cont__351_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1268: arguments_of(argument)
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
  // 1268: arguments_of(argument).is_empty
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
  // 1268: ... :
  // 1269:   !argument functor_of(argument)
  // 1270:     # The "arguments" were just remarks!
  frame->slots[6] /* temp__3 */ = create_closure(entry__351_14, 0);
  // 1271: :
  // 1272:   unless
  // 1273:     do_pretty_print && all_of(arguments_of(argument) is_a_remark)
  // 1274:     :
  // 1275:       check_functor functor
  frame->slots[7] /* temp__4 */ = create_closure(entry__351_16, 0);
  // 1267: if
  // 1268:   arguments_of(argument).is_empty:
  // 1269:     !argument functor_of(argument)
  // 1270:       # The "arguments" were just remarks!
  // 1271:   :
  // 1272:     unless
  // 1273:       do_pretty_print && all_of(arguments_of(argument) is_a_remark)
  // 1274:       :
  // 1275:         check_functor functor
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
  // 1275: check_functor functor
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  result_count = frame->caller_result_count;
  myself = func__check_functor;
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
  // 1269: !argument functor_of(argument)
  // 1270:   # The "arguments" were just remarks!
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
  // 1273: ... all_of(arguments_of(argument) is_a_remark)
  frame->slots[3] /* temp__2 */ = create_closure(entry__351_17, 0);
  // 1273: do_pretty_print && all_of(arguments_of(argument) is_a_remark)
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
  // 1273: ... arguments_of(argument)
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
  // 1273: ... all_of(arguments_of(argument) is_a_remark)
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
  // 1273: ... all_of(arguments_of(argument) is_a_remark)
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
  // 1274: :
  // 1275:   check_functor functor
  frame->slots[4] /* temp__3 */ = create_closure(entry__351_21, 0);
  // 1272: unless
  // 1273:   do_pretty_print && all_of(arguments_of(argument) is_a_remark)
  // 1274:   :
  // 1275:     check_functor functor
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
  // 1279: ... arguments_index-1
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
  // 1279: ... range(arguments 1 arguments_index-1)
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
  // 1279: push(range(arguments 1 arguments_index-1) argument)
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
  // 1276: ->
  // 1277:   node
  // 1278:     .arguments_of
  // 1279:       push(range(arguments 1 arguments_index-1) argument)
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
  myself = func__store_arguments_index;
  func = myself->type;
  frame->cont = cont__351_28;
}
static void cont__351_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1248: $MULTI_LINE_FUNCTION_CALL
  // 1249:   sequence
  // 1250:     store_arguments_index
  // 1251:       sequence
  // 1252:         optional(compiler::WHITESPACE, LINE_END_REMARK_ARGUMENT)
  // 1253:         INDENTED_ARGUMENTS
  // 1254:         modify_node
  // 1255:           : (node)
  // 1256:             $arguments arguments_of(node)
  // 1257:             $functor arguments(arguments_index)
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
  // 1285: arguments_span(MULTI_LINE_EXPRESSION)
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
  // 1293: ... some(PRINTABLE_CHARACTER)
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
  // 1293: ... compiler::WHITESPACE, HASHTAG, some(PRINTABLE_CHARACTER)
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
  // 1293: optional(compiler::WHITESPACE, HASHTAG, some(PRINTABLE_CHARACTER))
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
  // 1297: ... compiler::WHITESPACE, ARGUMENT
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
  // 1297: some(compiler::WHITESPACE, ARGUMENT)
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
  // 1298: ... alt(LINE_END_REMARK_ARGUMENT LINE_END_EXPRESSION)
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
  // 1298: optional(alt(LINE_END_REMARK_ARGUMENT LINE_END_EXPRESSION))
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
  // 1282: $ARGUMENT_LINE
  // 1283:   alt
  // 1284:     LINE_END_EXPRESSION
  // 1285:     arguments_span(MULTI_LINE_EXPRESSION)
  // 1286:     REMARK_ARGUMENT
  // 1287:     sequence
  // 1288:       ARGUMENT
  // 1289:       alt
  // 1290:         sequence
  // 1291:           followed_by
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
  // 1303: arguments_span(BODY)
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
  // 1305: interleaved(ARGUMENT compiler::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT;
  arguments->slots[1] = var.compiler__WHITESPACE;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__353_2;
}
static void cont__353_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1306: ... arguments_span(BODY)
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
  // 1306: optional(arguments_span(BODY))
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
  // 1300: $INLINE_ARGUMENTS
  // 1301:   inline
  // 1302:     alt
  // 1303:       arguments_span(BODY)
  // 1304:       sequence
  // 1305:         interleaved(ARGUMENT compiler::WHITESPACE)
  // 1306:         optional(arguments_span(BODY))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = func__inline;
  func = myself->type;
  frame->cont = cont__353_7;
}
static void cont__353_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INLINE_ARGUMENTS, arguments->slots[0]);
  // 1309: ... some(newline)
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
  // 1309: ... interleaved(ARGUMENT_LINE NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_LINE;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__354_2;
}
static void cont__354_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1308: $INDENTED_ARGUMENTS
  // 1309:   sequence(INDENT some(newline) interleaved(ARGUMENT_LINE NEWLINES) OUTDENT)
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
  // 1314: ... alt(LINE_END_EXPRESSION INDENTED_ARGUMENTS)
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
  // 1314: optional(alt(LINE_END_EXPRESSION INDENTED_ARGUMENTS))
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
  // 1311: $ARGUMENTS
  // 1312:   sequence
  // 1313:     FIRST_LINE_ARGUMENTS
  // 1314:     optional(alt(LINE_END_EXPRESSION INDENTED_ARGUMENTS))
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
  // 1392: set_node(assignment)
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
  // 1394: arguments_span(OUTPUT_ARGUMENT)
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
  // 1397: CHECK_ARGUMENTS("assignment" 1 1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2f401958355b9795;
  arguments->slots[1] = number__1;
  arguments->slots[2] = number__1;
  result_count = 1;
  myself = func__CHECK_ARGUMENTS;
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
  // 1400: ... : (-> break)
  // 1401:   for_each_from_to arguments_of(node) 2 -1: (source)
  // 1402:     unless source.is_a_remark:
  // 1403:       if source.is_a_polymorphic_function_constant:
  // 1404:         $destination arguments_of(node)(1)
  // 1405:         unless
  // 1406:           &&
  // 1407:             destination.is_a_static_single_definition
  // 1408:             attribute_kind_of(destination) == NONE
  // 1409:           :
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__360_6, 0);
  // 1400: do: (-> break)
  // 1401:   for_each_from_to arguments_of(node) 2 -1: (source)
  // 1402:     unless source.is_a_remark:
  // 1403:       if source.is_a_polymorphic_function_constant:
  // 1404:         $destination arguments_of(node)(1)
  // 1405:         unless
  // 1406:           &&
  // 1407:             destination.is_a_static_single_definition
  // 1408:             attribute_kind_of(destination) == NONE
  // 1409:           :
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
  // 1401: ... arguments_of(node)
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
  // 1401: ... 1
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
  // 1401: ... : (source)
  // 1402:   unless source.is_a_remark:
  // 1403:     if source.is_a_polymorphic_function_constant:
  // 1404:       $destination arguments_of(node)(1)
  // 1405:       unless
  // 1406:         &&
  // 1407:           destination.is_a_static_single_definition
  // 1408:           attribute_kind_of(destination) == NONE
  // 1409:         :
  // 1410:           SyntaxError node "
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__360_9, 1);
  // 1401: for_each_from_to arguments_of(node) 2 -1: (source)
  // 1402:   unless source.is_a_remark:
  // 1403:     if source.is_a_polymorphic_function_constant:
  // 1404:       $destination arguments_of(node)(1)
  // 1405:       unless
  // 1406:         &&
  // 1407:           destination.is_a_static_single_definition
  // 1408:           attribute_kind_of(destination) == NONE
  // 1409:         :
  // 1410:           SyntaxError node "
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
  // 1403: ... source.is_a_polymorphic_function_constant
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
  // 1403: ... :
  // 1404:   $destination arguments_of(node)(1)
  // 1405:   unless
  // 1406:     &&
  // 1407:       destination.is_a_static_single_definition
  // 1408:       attribute_kind_of(destination) == NONE
  // 1409:     :
  // 1410:       SyntaxError node "
  // 1411:         invalid polymorphic function definition (destination @
  // 1412:         must be a single assignment static)@
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__360_13, 0);
  // 1403: if source.is_a_polymorphic_function_constant:
  // 1404:   $destination arguments_of(node)(1)
  // 1405:   unless
  // 1406:     &&
  // 1407:       destination.is_a_static_single_definition
  // 1408:       attribute_kind_of(destination) == NONE
  // 1409:     :
  // 1410:       SyntaxError node "
  // 1411:         invalid polymorphic function definition (destination @
  // 1412:         must be a single assignment static)@
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
  // 1404: ... arguments_of(node)
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
  // 1404: $destination arguments_of(node)(1)
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
  // 1407: destination.is_a_static_single_definition
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
  // 1408: attribute_kind_of(destination) == NONE
  frame->slots[4] /* temp__3 */ = create_closure(entry__360_17, 0);
  // 1406: &&
  // 1407:   destination.is_a_static_single_definition
  // 1408:   attribute_kind_of(destination) == NONE
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
  // 1408: attribute_kind_of(destination)
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
  // 1408: attribute_kind_of(destination) == NONE
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
  // 1408: attribute_kind_of(destination) == NONE
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
  // 1409: :
  // 1410:   SyntaxError node "
  // 1411:     invalid polymorphic function definition (destination @
  // 1412:     must be a single assignment static)@
  frame->slots[5] /* temp__4 */ = create_closure(entry__360_21, 0);
  // 1405: unless
  // 1406:   &&
  // 1407:     destination.is_a_static_single_definition
  // 1408:     attribute_kind_of(destination) == NONE
  // 1409:   :
  // 1410:     SyntaxError node "
  // 1411:       invalid polymorphic function definition (destination @
  // 1412:       must be a single assignment static)@
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
  // 1410: SyntaxError node "
  // 1411:   invalid polymorphic function definition (destination @
  // 1412:   must be a single assignment static)@
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
  // 1415: ... arguments_of(node)
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
  // 1415: ... 1
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
  // 1415: range(arguments_of(node) 2 -1)
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
  // 1416: destination(.variable_kind_of POLYMORPHIC)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* destination */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__POLYMORPHIC());
    frame->slots[5] /* temp__4 */ = temp;

  }
  // 1413: !node.arguments_of
  // 1414:   put
  // 1415:     range(arguments_of(node) 2 -1)
  // 1416:     destination(.variable_kind_of POLYMORPHIC)
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
  // 1413: !node.arguments_of
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
  // 1417: break
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
  // 1402: ... source.is_a_remark
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
  // 1402: ... :
  // 1403:   if source.is_a_polymorphic_function_constant:
  // 1404:     $destination arguments_of(node)(1)
  // 1405:     unless
  // 1406:       &&
  // 1407:         destination.is_a_static_single_definition
  // 1408:         attribute_kind_of(destination) == NONE
  // 1409:       :
  // 1410:         SyntaxError node "
  // 1411:           invalid polymorphic function definition (destination @
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__360_11, 0);
  // 1402: unless source.is_a_remark:
  // 1403:   if source.is_a_polymorphic_function_constant:
  // 1404:     $destination arguments_of(node)(1)
  // 1405:     unless
  // 1406:       &&
  // 1407:         destination.is_a_static_single_definition
  // 1408:         attribute_kind_of(destination) == NONE
  // 1409:       :
  // 1410:         SyntaxError node "
  // 1411:           invalid polymorphic function definition (destination @
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
  // 1390: $ASSIGNMENT_STATEMENT
  // 1391:   sequence
  // 1392:     set_node(assignment)
  // 1393:     STORE_POSITION
  // 1394:     arguments_span(OUTPUT_ARGUMENT)
  // 1395:     ARGUMENTS
  // 1396:     STORE_END_POSITION
  // 1397:     CHECK_ARGUMENTS("assignment" 1 1)
  // 1398:     modify_node
  // 1399:       : (&node)
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
  // 1421: set_node(procedure_call)
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
  // 1424: optional(RESULT_COUNT_OR_CONTINUATION)
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
  // 1427: CHECK_ARGUMENTS("procedure call")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4f498b003024119a;
  result_count = 1;
  myself = func__CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__361_3;
}
static void cont__361_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1419: $PROCEDURE_STATEMENT
  // 1420:   sequence
  // 1421:     set_node(procedure_call)
  // 1422:     STORE_POSITION
  // 1423:     FUNCTOR
  // 1424:     optional(RESULT_COUNT_OR_CONTINUATION)
  // 1425:     ARGUMENTS
  // 1426:     STORE_END_POSITION
  // 1427:     CHECK_ARGUMENTS("procedure call")
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
  frame->cont = cont__361_4;
}
static void cont__361_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PROCEDURE_STATEMENT, arguments->slots[0]);
  // 1431: set_node(return_statement)
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
  // 1436: CHECK_ARGUMENTS("return statement" 0 ONE_OR_MORE)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__8782cdb8103cde5a;
  arguments->slots[1] = number__0;
  arguments->slots[2] = unique__ONE_OR_MORE;
  result_count = 1;
  myself = func__CHECK_ARGUMENTS;
  func = myself->type;
  frame->cont = cont__362_3;
}
static void cont__362_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1429: $RETURN_STATEMENT
  // 1430:   sequence
  // 1431:     set_node(return_statement)
  // 1432:     STORE_POSITION
  // 1433:     "->"
  // 1434:     ARGUMENTS
  // 1435:     STORE_END_POSITION
  // 1436:     CHECK_ARGUMENTS("return statement" 0 ONE_OR_MORE)
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
  // 1444: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5ed2969d8211684f;
  result_count = 1;
  myself = func__syntax_error;
  func = myself->type;
  frame->cont = cont__363_2;
}
static void cont__363_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1438: $STATEMENT
  // 1439:   alt
  // 1440:     REMARK_STATEMENT
  // 1441:     PROCEDURE_STATEMENT
  // 1442:     ASSIGNMENT_STATEMENT
  // 1443:     RETURN_STATEMENT
  // 1444:     syntax_error("statement expected")
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
  // 1448: ... multi_span(statements_of STATEMENT)
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
  // 1448: interleaved(multi_span(statements_of STATEMENT) NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = func__interleaved;
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
  // 1462: SyntaxError node "missing statement in body (there are only remarks)"
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
  // 1451: $$return_statement undefined
  ((CELL *)frame->slots[1])->contents /* return_statement */ = get__undefined();
  // 1452: $$statement_found false
  ((CELL *)frame->slots[2])->contents /* statement_found */ = get__false();
  // 1453: ... statements_of(node)
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
  // 1453: ... : (statement)
  // 1454:   unless statement.is_a_remark:
  // 1455:     if return_statement.is_defined:
  // 1456:       SyntaxError
  // 1457:         return_statement
  // 1458:         "return statement is followed by another statement"
  // 1459:     if statement.is_a_return: !return_statement statement
  // 1460:     !statement_found true
  frame->slots[4] /* temp__2 */ = create_closure(entry__364_5, 1);
  // 1453: for_each statements_of(node): (statement)
  // 1454:   unless statement.is_a_remark:
  // 1455:     if return_statement.is_defined:
  // 1456:       SyntaxError
  // 1457:         return_statement
  // 1458:         "return statement is followed by another statement"
  // 1459:     if statement.is_a_return: !return_statement statement
  // 1460:     !statement_found true
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
  // 1455: ... return_statement.is_defined
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
  // 1455: ... :
  // 1456:   SyntaxError
  // 1457:     return_statement
  // 1458:     "return statement is followed by another statement"
  frame->slots[4] /* temp__2 */ = create_closure(entry__364_9, 0);
  // 1455: if return_statement.is_defined:
  // 1456:   SyntaxError
  // 1457:     return_statement
  // 1458:     "return statement is followed by another statement"
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
  // 1456: SyntaxError
  // 1457:   return_statement
  // 1458:   "return statement is followed by another statement"
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
  // 1459: ... statement.is_a_return
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
  // 1459: ... : !return_statement statement
  frame->slots[4] /* temp__2 */ = create_closure(entry__364_13, 0);
  // 1459: if statement.is_a_return: !return_statement statement
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
  // 1459: ... !return_statement statement
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
  // 1460: !statement_found true
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
  // 1454: ... statement.is_a_remark
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
  // 1454: ... :
  // 1455:   if return_statement.is_defined:
  // 1456:     SyntaxError
  // 1457:       return_statement
  // 1458:       "return statement is followed by another statement"
  // 1459:   if statement.is_a_return: !return_statement statement
  // 1460:   !statement_found true
  frame->slots[4] /* temp__2 */ = create_closure(entry__364_7, 0);
  // 1454: unless statement.is_a_remark:
  // 1455:   if return_statement.is_defined:
  // 1456:     SyntaxError
  // 1457:       return_statement
  // 1458:       "return statement is followed by another statement"
  // 1459:   if statement.is_a_return: !return_statement statement
  // 1460:   !statement_found true
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
  // 1461: ... :
  // 1462:   SyntaxError node "missing statement in body (there are only remarks)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__364_16, 0);
  // 1461: unless statement_found:
  // 1462:   SyntaxError node "missing statement in body (there are only remarks)"
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
  // 1446: $STATEMENTS
  // 1447:   sequence
  // 1448:     interleaved(multi_span(statements_of STATEMENT) NEWLINES)
  // 1449:     inspect_node
  // 1450:       : (node)
  // 1451:         $$return_statement undefined
  // 1452:         $$statement_found false
  // 1453:         for_each statements_of(node): (statement)
  // 1454:           unless statement.is_a_remark:
  // 1455:             if return_statement.is_defined:
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
  // 1467: set_node(identifier)
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
  // 1467: ... "__", NAME
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
  // 1467: ... many("__", NAME)
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
  // 1467: ... NAME, many("__", NAME)
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
  // 1467: ... capture(name_of NAME, many("__", NAME))
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
  // 1467: set_node(identifier), capture(name_of NAME, many("__", NAME))
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
  // 1464: $BUILTIN_NAME
  // 1465:   span
  // 1466:     identifier_of
  // 1467:     set_node(identifier), capture(name_of NAME, many("__", NAME))
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
  // 1469: ... not_followed_by('>')
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
  // 1469: ... not_followed_by('>'), ANY_CHARACTER
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
  // 1469: $C_EXPRESSION many(not_followed_by('>'), ANY_CHARACTER)
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
  // 1474: ... multi_capture(arguments_of C_EXPRESSION)
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
  // 1474: ... compiler::WHITESPACE, multi_capture(arguments_of C_EXPRESSION)
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
  // 1474: expect(compiler::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__367_3;
}
static void cont__367_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1471: $ARGUMENT_ANNOTATION
  // 1472:   sequence
  // 1473:     "argument"
  // 1474:     expect(compiler::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
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
  // 1477: ... span(base_of NAMESPACED_IDENTIFIER)
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
  // 1477: ... compiler::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER)
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
  // 1477: ... expect(compiler::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__368_3;
}
static void cont__368_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1476: $BASE_ANNOTATION
  // 1477:   "base", expect(compiler::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
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
  // 1479: ... capture(kind_of NAME)
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
  // 1479: ... compiler::WHITESPACE, capture(kind_of NAME)
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
  // 1479: ... expect(compiler::WHITESPACE, capture(kind_of NAME))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__369_3;
}
static void cont__369_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1479: $KIND_ANNOTATION "kind", expect(compiler::WHITESPACE, capture(kind_of NAME))
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
  // 1485: ... alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
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
  // 1485: compiler::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
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
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__370_3;
}
static void cont__370_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1481: $NAME_ANNOTATION
  // 1482:   sequence
  // 1483:     "name"
  // 1484:     expect
  // 1485:       compiler::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
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
  // 1487: ... capture(node_of NAME)
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
  // 1487: ... compiler::WHITESPACE, capture(node_of NAME)
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
  // 1487: ... expect(compiler::WHITESPACE, capture(node_of NAME))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__371_3;
}
static void cont__371_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1487: $NODE_ANNOTATION "node", expect(compiler::WHITESPACE, capture(node_of NAME))
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
  // 1495: ... alt("runtime" "global" "local" "extern")
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
  // 1495: capture(node::scope_of alt("runtime" "global" "local" "extern"))
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
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__372_8;
}
static void cont__372_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1489: $SCOPE_ANNOTATION
  // 1490:   sequence
  // 1491:     "scope"
  // 1492:     expect
  // 1493:       sequence
  // 1494:         compiler::WHITESPACE
  // 1495:         capture(node::scope_of alt("runtime" "global" "local" "extern"))
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
  // 1500: ... span(node::type_of NAMESPACED_IDENTIFIER)
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
  // 1500: ... compiler::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER)
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
  // 1500: expect(compiler::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__373_3;
}
static void cont__373_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1497: $TYPE_ANNOTATION
  // 1498:   sequence
  // 1499:     "type"
  // 1500:     expect(compiler::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
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
  // 1511: syntax_error("invalid annotation tag")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__399cfc434d66f26;
  result_count = 1;
  myself = func__syntax_error;
  func = myself->type;
  frame->cont = cont__374_2;
}
static void cont__374_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1502: $ANNOTATION_ITEM
  // 1503:   alt
  // 1504:     ARGUMENT_ANNOTATION
  // 1505:     BASE_ANNOTATION
  // 1506:     KIND_ANNOTATION
  // 1507:     NAME_ANNOTATION
  // 1508:     NODE_ANNOTATION
  // 1509:     SCOPE_ANNOTATION
  // 1510:     TYPE_ANNOTATION
  // 1511:     syntax_error("invalid annotation tag")
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
  // 1513: ... expect('>')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__62;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__375_1;
}
static void cont__375_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1513: $ANNOTATION '<', ANNOTATION_ITEM, expect('>')
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
  // 1514: $ANNOTATIONS interleaved(ANNOTATION NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ANNOTATION;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = func__interleaved;
  func = myself->type;
  frame->cont = cont__376_1;
}
static void cont__376_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATIONS, arguments->slots[0]);
  // 1515: $C_CODE_REMARK "//", REMARK_LINE
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
  // 1516: ... followed_by(OUTDENT)
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
  // 1516: ... alt(NEWLINES followed_by(OUTDENT))
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
  // 1516: ... C_CODE_REMARK, alt(NEWLINES followed_by(OUTDENT))
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
  // 1516: $C_CODE_REMARKS some(C_CODE_REMARK, alt(NEWLINES followed_by(OUTDENT)))
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
  // 1521: ... not_followed_by(OUTDENT)
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
  // 1521: ... not_followed_by(OUTDENT), ANY_CHARACTER
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
  // 1521: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
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
  // 1521: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
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
  // 1518: $SOURCE
  // 1519:   sequence
  // 1520:     C_CODE_REMARKS
  // 1521:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
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
  // 1526: set_node(c_code)
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
  // 1527: expect(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__380_2;
}
static void cont__380_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1528: ... NEWLINES, SOURCE
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
  // 1528: ... optional(NEWLINES, SOURCE)
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
  // 1528: ... ANNOTATIONS, optional(NEWLINES, SOURCE)
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
  // 1528: alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
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
  // 1529: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__380_7;
}
static void cont__380_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1530: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__380_8;
}
static void cont__380_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1531: some(newline)
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
  // 1532: expect('}')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__125;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__380_10;
}
static void cont__380_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1523: $C_CODE
  // 1524:   sequence
  // 1525:     '{'
  // 1526:     set_node(c_code)
  // 1527:     expect(indent_marker)
  // 1528:     alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
  // 1529:     expect(outdent_marker)
  // 1530:     expect(newline)
  // 1531:     some(newline)
  // 1532:     expect('}')
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
  // 1534: ... newline, END_OF_TEXT
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
  // 1534: ... expect(newline, END_OF_TEXT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__381_2;
}
static void cont__381_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1534: $META_FRAGMENT META_INSTRUCTION, expect(newline, END_OF_TEXT)
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
  // 1538: ... syntax_error("top-level statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__227de92deba39b6b;
  result_count = 1;
  myself = func__syntax_error;
  func = myself->type;
  frame->cont = cont__382_2;
}
static void cont__382_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1538: alt(C_CODE STATEMENT syntax_error("top-level statement expected"))
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
  // 1539: ... newline, END_OF_TEXT
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
  // 1539: expect(newline, END_OF_TEXT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = func__expect;
  func = myself->type;
  frame->cont = cont__382_5;
}
static void cont__382_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1536: $FRAGMENT
  // 1537:   sequence
  // 1538:     alt(C_CODE STATEMENT syntax_error("top-level statement expected"))
  // 1539:     expect(newline, END_OF_TEXT)
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
static void entry__compiler__std_identifier(void) {
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
static void entry__print_message(void) {
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
static void entry__compiler__Warning(void) {
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
  myself = func__print_message;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__ExitWithSyntaxError(void) {
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
  myself = func__print_message;
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
static void entry__compiler__SyntaxError(void) {
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
  myself = func__ExitWithSyntaxError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__ParseError(void) {
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
  myself = func__ExitWithSyntaxError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__syntax_error___grammar__match(void) {
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
  frame->cont = cont__types__syntax_error___grammar__match_2;
}
static void cont__types__syntax_error___grammar__match_2(void) {
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
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__syntax_error(void) {
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
  myself = func__ParseError;
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
  myself = func__ParseError;
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
  myself = func__ParseError;
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
  myself = func__ParseError;
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
  myself = func__ParseError;
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
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unexpected_input_error___grammar__match(void) {
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
  frame->cont = cont__types__unexpected_input_error___grammar__match_2;
}
static void cont__types__unexpected_input_error___grammar__match_2(void) {
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
  frame->cont = cont__types__unexpected_input_error___grammar__match_3;
}
static void cont__types__unexpected_input_error___grammar__match_3(void) {
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
  frame->cont = cont__types__unexpected_input_error___grammar__match_6;
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
static void cont__types__unexpected_input_error___grammar__match_6(void) {
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
static void entry__unexpected_input_error(void) {
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
static void entry__dump_stream___grammar__match(void) {
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
  frame->cont = cont__dump_stream___grammar__match_3;
}
static void cont__dump_stream___grammar__match_3(void) {
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
  frame->cont = cont__dump_stream___grammar__match_4;
}
static void cont__dump_stream___grammar__match_4(void) {
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
  frame->cont = cont__dump_stream___grammar__match_5;
}
static void cont__dump_stream___grammar__match_5(void) {
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
  frame->cont = cont__dump_stream___grammar__match_7;
}
static void cont__dump_stream___grammar__match_7(void) {
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
static void entry__compiler__strip(void) {
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
static void entry__dump___grammar__match(void) {
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
  frame->cont = cont__dump___grammar__match_2;
}
static void cont__dump___grammar__match_2(void) {
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
  frame->cont = cont__dump___grammar__match_4;
}
static void cont__dump___grammar__match_4(void) {
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
static void entry__dump3___grammar__match(void) {
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
  frame->cont = cont__dump3___grammar__match_2;
}
static void cont__dump3___grammar__match_2(void) {
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
  frame->cont = cont__dump3___grammar__match_3;
}
static void cont__dump3___grammar__match_3(void) {
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
static void entry__dump5___grammar__match(void) {
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
  frame->cont = cont__dump5___grammar__match_2;
}
static void cont__dump5___grammar__match_2(void) {
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
  frame->cont = cont__dump5___grammar__match_3;
}
static void cont__dump5___grammar__match_3(void) {
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
  // 233: ... precedence_table(op)
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
  // 233: -> precedence_table(op)
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
  // 234: -> INFIX_PRECEDENCE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__INFIX_PRECEDENCE();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__precedence(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // op: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 232: op.is_a_string
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
  // 233: -> precedence_table(op)
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__precedence_3, 0);
  // 231: if
  // 232:   op.is_a_string
  // 233:   -> precedence_table(op)
  // 234:   -> INFIX_PRECEDENCE
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
static void entry__compiler__is_left_associative(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // prec: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 236: ... prec > 5
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
  // 236: ... -> prec > 5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__is_right_associative(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // prec: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 238: ... prec <= 5
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
  // 238: ... prec <= 5
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
  // 238: ... -> prec <= 5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__infix_operator(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // operator: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 241: ... compiler::WHITESPACE, operator, compiler::WHITESPACE
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
  // 241: ... alt(operator compiler::WHITESPACE, operator, compiler::WHITESPACE)
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
  // 241: -> alt(operator compiler::WHITESPACE, operator, compiler::WHITESPACE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__interleaved(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // expression: 0
  // separator: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 243: ... separator, expression
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
  // 243: ... some(separator, expression)
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
  // 243: ... expression, some(separator, expression)
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
  // 243: ... -> expression, some(separator, expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__store_arguments_index___grammar__match(void) {
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
  // 252: ... arguments_of(grammar::current_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__grammar__current_node();
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__types__store_arguments_index___grammar__match_2;
}
static void cont__types__store_arguments_index___grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 252: %arguments_index length_of(arguments_of(grammar::current_node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__store_arguments_index___grammar__match_3;
}
static void cont__types__store_arguments_index___grammar__match_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__arguments_index(), arguments->slots[0]);
  // 253: ... expression_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__expression_of();
  func = myself->type;
  frame->cont = cont__types__store_arguments_index___grammar__match_4;
}
static void cont__types__store_arguments_index___grammar__match_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 253: grammar::match expression_of(self) stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = frame->caller_result_count;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__types__store_arguments_index___grammar__match_5;
}
static void cont__types__store_arguments_index___grammar__match_5(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__store_arguments_index(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 256: ... types::store_arguments_index(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__store_arguments_index);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 256: -> types::store_arguments_index(.expression_of expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__inline___grammar__match(void) {
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
  // 265: %within_inline_expression true
  initialize_maybe_future(get__within_inline_expression(), get__true());
  // 266: ... expression_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__expression_of();
  func = myself->type;
  frame->cont = cont__types__inline___grammar__match_2;
}
static void cont__types__inline___grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 266: grammar::match expression_of(self) stream
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* stream */;
  result_count = frame->caller_result_count;
  myself = get__grammar__match();
  func = myself->type;
  frame->cont = cont__types__inline___grammar__match_3;
}
static void cont__types__inline___grammar__match_3(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__inline(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 268: ... types::inline(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__inline);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 268: ... -> types::inline(.expression_of expression)
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
  // 286: ... "@(description) expected"
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
  // 286: ... syntax_error("@(description) expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = func__syntax_error;
  func = myself->type;
  frame->cont = cont__expect_5;
}
static void cont__expect_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 286: ... alt(expression syntax_error("@(description) expected"))
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
  // 286: -> alt(expression syntax_error("@(description) expected"))
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
  // 287: ... unexpected_input_error(expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  result_count = 1;
  myself = func__unexpected_input_error;
  func = myself->type;
  frame->cont = cont__expect_8;
}
static void cont__expect_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 287: ... alt(expression unexpected_input_error(expression))
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
  // 287: -> alt(expression unexpected_input_error(expression))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__expect(void) {
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
  // 285: description.is_defined
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
  // 286: -> alt(expression syntax_error("@(description) expected"))
  frame->slots[3] /* temp__2 */ = create_closure(entry__expect_3, 0);
  // 287: -> alt(expression unexpected_input_error(expression))
  frame->slots[4] /* temp__3 */ = create_closure(entry__expect_7, 0);
  // 284: if
  // 285:   description.is_defined
  // 286:   -> alt(expression syntax_error("@(description) expected"))
  // 287:   -> alt(expression unexpected_input_error(expression))
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
static void entry__compiler__arguments_span(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 289: ... multi_span(arguments_of expression)
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
  // 289: ... -> multi_span(arguments_of expression)
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
  // 1324: SyntaxError functor "invalid functor"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  arguments->slots[1] = string__120dee9a1dcec47c;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_functor(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // functor: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1321: functor.is_an_identifier
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
  // 1322: functor.is_a_function_call && not(functor.is_in_infix_notation)
  frame->slots[3] /* temp__3 */ = create_closure(entry__check_functor_3, 0);
  // 1320: ||
  // 1321:   functor.is_an_identifier
  // 1322:   functor.is_a_function_call && not(functor.is_in_infix_notation)
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
  // 1322: functor.is_a_function_call
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
  // 1322: ... not(functor.is_in_infix_notation)
  frame->slots[3] /* temp__3 */ = create_closure(entry__check_functor_5, 0);
  // 1322: functor.is_a_function_call && not(functor.is_in_infix_notation)
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
  // 1322: ... functor.is_in_infix_notation
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
  // 1322: ... not(functor.is_in_infix_notation)
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
  // 1322: ... not(functor.is_in_infix_notation)
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
  // 1322: functor.is_a_function_call && not(functor.is_in_infix_notation)
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
  // 1323: :
  // 1324:   SyntaxError functor "invalid functor"
  frame->slots[4] /* temp__4 */ = create_closure(entry__check_functor_10, 0);
  // 1319: unless
  // 1320:   ||
  // 1321:     functor.is_an_identifier
  // 1322:     functor.is_a_function_call && not(functor.is_in_infix_notation)
  // 1323:   :
  // 1324:     SyntaxError functor "invalid functor"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_85(void) {
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
  // 1385: ... "too few input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__bb0c2c1e659a1755;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* kind */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_87;
}
static void cont__check_arguments_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1385: SyntaxError node "too few input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_55(void) {
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
  // 1365: wanted_inputs == ONE_OR_MORE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* wanted_inputs */;
  arguments->slots[1] = unique__ONE_OR_MORE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_56;
}
static void cont__check_arguments_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1367: -> wanted_inputs
  frame->slots[7] /* temp__2 */ = create_closure(entry__check_arguments_57, 0);
  // 1363: $min_inputs
  // 1364:   if
  // 1365:     wanted_inputs == ONE_OR_MORE
  // 1366:     -> 1
  // 1367:     -> wanted_inputs
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__check_arguments_58;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_59;
}
static void entry__check_arguments_57(void) {
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
static void entry__check_arguments_58(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1366: -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* min_inputs */, arguments->slots[0]);
  // 1371: wanted_inputs == ONE_OR_MORE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* wanted_inputs */;
  arguments->slots[1] = unique__ONE_OR_MORE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_60;
}
static void cont__check_arguments_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1373: -> wanted_inputs
  frame->slots[7] /* temp__2 */ = create_closure(entry__check_arguments_61, 0);
  // 1369: $max_inputs
  // 1370:   if
  // 1371:     wanted_inputs == ONE_OR_MORE
  // 1372:     -> undefined
  // 1373:     -> wanted_inputs
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__check_arguments_62;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_63;
}
static void entry__check_arguments_61(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // wanted_inputs: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* wanted_inputs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1373: -> wanted_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* wanted_inputs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_62(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1372: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* max_inputs */, arguments->slots[0]);
  // 1375: ... max_inputs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* max_inputs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_64;
}
static void cont__check_arguments_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1375: ... inputs > max_inputs
  frame->slots[8] /* temp__3 */ = create_closure(entry__check_arguments_65, 0);
  // 1375: ... max_inputs.is_defined && inputs > max_inputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_arguments_67;
}
static void entry__check_arguments_65(void) {
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
  // 1375: ... inputs > max_inputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* max_inputs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* inputs */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_66;
}
static void cont__check_arguments_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1375: ... inputs > max_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1375: ... :
  // 1376:   $$first_input_argument undefined
  // 1377:   do: (-> break)
  // 1378:     for_each arguments_of(node): (argument)
  // 1379:       unless argument.is_a_destination:
  // 1380:         !first_input_argument argument
  // 1381:         break
  // 1382:   unless first_input_argument.is_an_attribute_value_pair:
  // 1383:     SyntaxError node "too many input arguments for @(kind)"
  frame->slots[9] /* temp__4 */ = create_closure(entry__check_arguments_68, 0);
  // 1375: if max_inputs.is_defined && inputs > max_inputs:
  // 1376:   $$first_input_argument undefined
  // 1377:   do: (-> break)
  // 1378:     for_each arguments_of(node): (argument)
  // 1379:       unless argument.is_a_destination:
  // 1380:         !first_input_argument argument
  // 1381:         break
  // 1382:   unless first_input_argument.is_an_attribute_value_pair:
  // 1383:     SyntaxError node "too many input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_80;
}
static void entry__check_arguments_77(void) {
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
  // 1383: ... "too many input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ebee6487b4b0342b;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* kind */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_79;
}
static void cont__check_arguments_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1383: SyntaxError node "too many input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_68(void) {
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
  // 1376: $$first_input_argument undefined
  ((CELL *)frame->slots[2])->contents /* first_input_argument */ = get__undefined();
  // 1377: ... : (-> break)
  // 1378:   for_each arguments_of(node): (argument)
  // 1379:     unless argument.is_a_destination:
  // 1380:       !first_input_argument argument
  // 1381:       break
  frame->slots[3] /* temp__1 */ = create_closure(entry__check_arguments_69, 0);
  // 1377: do: (-> break)
  // 1378:   for_each arguments_of(node): (argument)
  // 1379:     unless argument.is_a_destination:
  // 1380:       !first_input_argument argument
  // 1381:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__check_arguments_75;
}
static void entry__check_arguments_69(void) {
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
  // 1378: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__check_arguments_70;
}
static void cont__check_arguments_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1378: ... : (argument)
  // 1379:   unless argument.is_a_destination:
  // 1380:     !first_input_argument argument
  // 1381:     break
  frame->slots[4] /* temp__2 */ = create_closure(entry__check_arguments_71, 1);
  // 1378: for_each arguments_of(node): (argument)
  // 1379:   unless argument.is_a_destination:
  // 1380:     !first_input_argument argument
  // 1381:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_74;
}
static void entry__check_arguments_73(void) {
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
  // 1380: !first_input_argument argument
  ((CELL *)frame->slots[0])->contents /* first_input_argument */ = frame->slots[1] /* argument */;
  // 1381: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_71(void) {
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
  // 1379: ... argument.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_destination();
  func = myself->type;
  frame->cont = cont__check_arguments_72;
}
static void cont__check_arguments_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1379: ... :
  // 1380:   !first_input_argument argument
  // 1381:   break
  frame->slots[4] /* temp__2 */ = create_closure(entry__check_arguments_73, 0);
  // 1379: unless argument.is_a_destination:
  // 1380:   !first_input_argument argument
  // 1381:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_74(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_75(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1382: ... first_input_argument.is_an_attribute_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* first_input_argument */;
  result_count = 1;
  myself = get__is_an_attribute_value_pair();
  func = myself->type;
  frame->cont = cont__check_arguments_76;
}
static void cont__check_arguments_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1382: ... :
  // 1383:   SyntaxError node "too many input arguments for @(kind)"
  frame->slots[4] /* temp__2 */ = create_closure(entry__check_arguments_77, 0);
  // 1382: unless first_input_argument.is_an_attribute_value_pair:
  // 1383:   SyntaxError node "too many input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_80(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1384: ... min_inputs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* min_inputs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_81;
}
static void cont__check_arguments_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1384: ... inputs < min_inputs
  frame->slots[8] /* temp__3 */ = create_closure(entry__check_arguments_82, 0);
  // 1384: ... min_inputs.is_defined && inputs < min_inputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_arguments_84;
}
static void entry__check_arguments_82(void) {
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
  // 1384: ... inputs < min_inputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* inputs */;
  arguments->slots[1] = frame->slots[1] /* min_inputs */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_83;
}
static void cont__check_arguments_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1384: ... inputs < min_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1384: ... :
  // 1385:   SyntaxError node "too few input arguments for @(kind)"
  frame->slots[9] /* temp__4 */ = create_closure(entry__check_arguments_85, 0);
  // 1384: if min_inputs.is_defined && inputs < min_inputs:
  // 1385:   SyntaxError node "too few input arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments(void) {
  allocate_initialized_frame_gc(4, 13);
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
  frame->slots[1] /* kind */ = create_cell_with_contents(arguments->slots[1]);
  switch(argument_count) {
    default: frame->slots[3] /* wanted_inputs */ = arguments->slots[3];
    case 3: frame->slots[2] /* wanted_outputs */ = create_cell_with_contents(arguments->slots[2]);
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* wanted_outputs */ = create_cell_with_contents(undefined);
    case 3: frame->slots[3] /* wanted_inputs */ = undefined;
  }
  // 1332: ... : (argument)
  // 1333:   if argument.is_a_destination: inc &outputs
  // 1334:   if not(argument.is_a_destination) || argument.is_an_input_output_argument:
  // 1335:     if
  // 1336:       argument.is_an_attribute_value_pair:
  // 1337:         if contains_simple_input_argument:
  // 1338:           SyntaxError argument "unexpected attribute-value-pair"
  // 1339:         !contains_attribute_value_pair true
  // 1340:       :
  // 1341:         if contains_attribute_value_pair:
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__check_arguments_2, 1);
  // 1332: $add_argument: (argument)
  // 1333:   if argument.is_a_destination: inc &outputs
  // 1334:   if not(argument.is_a_destination) || argument.is_an_input_output_argument:
  // 1335:     if
  // 1336:       argument.is_an_attribute_value_pair:
  // 1337:         if contains_simple_input_argument:
  // 1338:           SyntaxError argument "unexpected attribute-value-pair"
  // 1339:         !contains_attribute_value_pair true
  // 1340:       :
  // 1341:         if contains_attribute_value_pair:
  // ...
  initialize_future(frame->slots[8] /* add_argument */, frame->slots[9] /* temp__1 */);
  // 1327: $$outputs 0
  ((CELL *)frame->slots[4])->contents /* outputs */ = number__0;
  // 1328: $$inputs 0
  ((CELL *)frame->slots[5])->contents /* inputs */ = number__0;
  // 1329: $$contains_attribute_value_pair false
  ((CELL *)frame->slots[6])->contents /* contains_attribute_value_pair */ = get__false();
  // 1330: $$contains_simple_input_argument false
  ((CELL *)frame->slots[7])->contents /* contains_simple_input_argument */ = get__false();
  // 1346: ... arguments_of(node)
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
  // 1336: argument.is_an_attribute_value_pair
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
  // 1336: ... :
  // 1337:   if contains_simple_input_argument:
  // 1338:     SyntaxError argument "unexpected attribute-value-pair"
  // 1339:   !contains_attribute_value_pair true
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_14, 0);
  // 1340: :
  // 1341:   if contains_attribute_value_pair:
  // 1342:     SyntaxError argument "simple argument within attribute definition"
  // 1343:   !contains_simple_input_argument true
  frame->slots[6] /* temp__3 */ = create_closure(entry__check_arguments_18, 0);
  // 1335: if
  // 1336:   argument.is_an_attribute_value_pair:
  // 1337:     if contains_simple_input_argument:
  // 1338:       SyntaxError argument "unexpected attribute-value-pair"
  // 1339:     !contains_attribute_value_pair true
  // 1340:   :
  // 1341:     if contains_attribute_value_pair:
  // 1342:       SyntaxError argument "simple argument within attribute definition"
  // 1343:     !contains_simple_input_argument true
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
  // 1337: ... :
  // 1338:   SyntaxError argument "unexpected attribute-value-pair"
  frame->slots[3] /* temp__1 */ = create_closure(entry__check_arguments_15, 0);
  // 1337: if contains_simple_input_argument:
  // 1338:   SyntaxError argument "unexpected attribute-value-pair"
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
  // 1338: SyntaxError argument "unexpected attribute-value-pair"
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
  // 1339: !contains_attribute_value_pair true
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
  // 1341: ... :
  // 1342:   SyntaxError argument "simple argument within attribute definition"
  frame->slots[3] /* temp__1 */ = create_closure(entry__check_arguments_19, 0);
  // 1341: if contains_attribute_value_pair:
  // 1342:   SyntaxError argument "simple argument within attribute definition"
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
  // 1342: SyntaxError argument "simple argument within attribute definition"
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
  // 1343: !contains_simple_input_argument true
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
  // 1344: inc &inputs
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
  // 1333: ... argument.is_a_destination
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
  // 1333: ... : inc &outputs
  frame->slots[6] /* temp__2 */ = create_closure(entry__check_arguments_4, 0);
  // 1333: if argument.is_a_destination: inc &outputs
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
  // 1333: ... inc &outputs
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
  // 1334: ... argument.is_a_destination
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
  // 1334: ... not(argument.is_a_destination)
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
  // 1334: ... argument.is_an_input_output_argument
  frame->slots[8] /* temp__4 */ = create_closure(entry__check_arguments_9, 0);
  // 1334: ... not(argument.is_a_destination) || argument.is_an_input_output_argument
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
  // 1334: ... argument.is_an_input_output_argument
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
  // 1334: ... argument.is_an_input_output_argument
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
  // 1334: ... :
  // 1335:   if
  // 1336:     argument.is_an_attribute_value_pair:
  // 1337:       if contains_simple_input_argument:
  // 1338:         SyntaxError argument "unexpected attribute-value-pair"
  // 1339:       !contains_attribute_value_pair true
  // 1340:     :
  // 1341:       if contains_attribute_value_pair:
  // 1342:         SyntaxError argument "simple argument within attribute definition"
  // 1343:       !contains_simple_input_argument true
  // ...
  frame->slots[9] /* temp__5 */ = create_closure(entry__check_arguments_12, 0);
  // 1334: if not(argument.is_a_destination) || argument.is_an_input_output_argument:
  // 1335:   if
  // 1336:     argument.is_an_attribute_value_pair:
  // 1337:       if contains_simple_input_argument:
  // 1338:         SyntaxError argument "unexpected attribute-value-pair"
  // 1339:       !contains_attribute_value_pair true
  // 1340:     :
  // 1341:       if contains_attribute_value_pair:
  // 1342:         SyntaxError argument "simple argument within attribute definition"
  // 1343:       !contains_simple_input_argument true
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
  // 1346: ... : (argument)
  // 1347:   unless argument.is_a_remark:
  // 1348:     if
  // 1349:       argument.is_a_backquoted_expression:
  // 1350:         add_argument string_literal(.node::text_of node::text_of(argument))
  // 1351:         add_argument expression_of(argument)
  // 1352:       :
  // 1353:         add_argument argument
  frame->slots[10] /* temp__2 */ = create_closure(entry__check_arguments_25, 1);
  // 1346: for_each arguments_of(node): (argument)
  // 1347:   unless argument.is_a_remark:
  // 1348:     if
  // 1349:       argument.is_a_backquoted_expression:
  // 1350:         add_argument string_literal(.node::text_of node::text_of(argument))
  // 1351:         add_argument expression_of(argument)
  // 1352:       :
  // 1353:         add_argument argument
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
  // 1350: ... node::text_of(argument)
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
  // 1350: ... string_literal(.node::text_of node::text_of(argument))
  {
    NODE *temp = clone_object_and_attributes(get__string_literal());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, frame->slots[3] /* temp__2 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 1350: add_argument string_literal(.node::text_of node::text_of(argument))
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
  // 1351: ... expression_of(argument)
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
  // 1351: add_argument expression_of(argument)
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
  // 1353: add_argument argument
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
  // 1349: argument.is_a_backquoted_expression
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
  // 1349: ... :
  // 1350:   add_argument string_literal(.node::text_of node::text_of(argument))
  // 1351:   add_argument expression_of(argument)
  frame->slots[3] /* temp__2 */ = create_closure(entry__check_arguments_29, 0);
  // 1352: :
  // 1353:   add_argument argument
  frame->slots[4] /* temp__3 */ = create_closure(entry__check_arguments_33, 0);
  // 1348: if
  // 1349:   argument.is_a_backquoted_expression:
  // 1350:     add_argument string_literal(.node::text_of node::text_of(argument))
  // 1351:     add_argument expression_of(argument)
  // 1352:   :
  // 1353:     add_argument argument
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
  // 1347: ... argument.is_a_remark
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
  // 1347: ... :
  // 1348:   if
  // 1349:     argument.is_a_backquoted_expression:
  // 1350:       add_argument string_literal(.node::text_of node::text_of(argument))
  // 1351:       add_argument expression_of(argument)
  // 1352:     :
  // 1353:       add_argument argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__check_arguments_27, 0);
  // 1347: unless argument.is_a_remark:
  // 1348:   if
  // 1349:     argument.is_a_backquoted_expression:
  // 1350:       add_argument string_literal(.node::text_of node::text_of(argument))
  // 1351:       add_argument expression_of(argument)
  // 1352:     :
  // 1353:       add_argument argument
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
  // 1354: ... kind == "procedure call"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* kind */;
  arguments->slots[1] = string__4f498b003024119a;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_36;
}
static void cont__check_arguments_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 1354: ... contains_attribute_value_pair
  frame->slots[11] /* temp__3 */ = create_closure(entry__check_arguments_37, 0);
  // 1354: ... kind == "procedure call" && contains_attribute_value_pair
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_arguments_38;
}
static void entry__check_arguments_37(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // contains_attribute_value_pair: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* contains_attribute_value_pair */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1354: ... contains_attribute_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* contains_attribute_value_pair */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1354: ... :
  // 1355:   !kind "object definition"
  // 1356:   !wanted_outputs 1
  frame->slots[12] /* temp__4 */ = create_closure(entry__check_arguments_39, 0);
  // 1354: if kind == "procedure call" && contains_attribute_value_pair:
  // 1355:   !kind "object definition"
  // 1356:   !wanted_outputs 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_41;
}
static void entry__check_arguments_39(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // kind: 0
  // wanted_outputs: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* kind */
  frame->slots[1] = myself->closure.frame->slots[2]; /* wanted_outputs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1355: !kind "object definition"
  ((CELL *)frame->slots[0])->contents /* kind */ = string__47a9393383380498;
  // 1356: !wanted_outputs 1
  ((CELL *)frame->slots[1])->contents /* wanted_outputs */ = number__1;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1357: ... wanted_outputs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* wanted_outputs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_42;
}
static void cont__check_arguments_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1357: ... :
  // 1358:   if outputs > wanted_outputs:
  // 1359:     SyntaxError node "too many output arguments for @(kind)"
  // 1360:   if outputs < wanted_outputs:
  // 1361:     SyntaxError node "too few output arguments for @(kind)"
  frame->slots[10] /* temp__2 */ = create_closure(entry__check_arguments_43, 0);
  // 1357: if wanted_outputs.is_defined:
  // 1358:   if outputs > wanted_outputs:
  // 1359:     SyntaxError node "too many output arguments for @(kind)"
  // 1360:   if outputs < wanted_outputs:
  // 1361:     SyntaxError node "too few output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_53;
}
static void entry__check_arguments_50(void) {
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
  // 1361: ... "too few output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1b6e5ce3b21cbf2f;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* kind */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_52;
}
static void cont__check_arguments_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1361: SyntaxError node "too few output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_43(void) {
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
  // 1358: ... outputs > wanted_outputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* wanted_outputs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* outputs */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_44;
}
static void cont__check_arguments_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1358: ... :
  // 1359:   SyntaxError node "too many output arguments for @(kind)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_45, 0);
  // 1358: if outputs > wanted_outputs:
  // 1359:   SyntaxError node "too many output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_48;
}
static void entry__check_arguments_45(void) {
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
  // 1359: ... "too many output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5fa0d5b2a9ee383d;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* kind */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_47;
}
static void cont__check_arguments_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1359: SyntaxError node "too many output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1360: ... outputs < wanted_outputs
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* outputs */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* wanted_outputs */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_49;
}
static void cont__check_arguments_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1360: ... :
  // 1361:   SyntaxError node "too few output arguments for @(kind)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_50, 0);
  // 1360: if outputs < wanted_outputs:
  // 1361:   SyntaxError node "too few output arguments for @(kind)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1362: ... wanted_inputs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* wanted_inputs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_54;
}
static void cont__check_arguments_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 1362: ... :
  // 1363:   $min_inputs
  // 1364:     if
  // 1365:       wanted_inputs == ONE_OR_MORE
  // 1366:       -> 1
  // 1367:       -> wanted_inputs
  // 1368:   
  // 1369:   $max_inputs
  // 1370:     if
  // 1371:       wanted_inputs == ONE_OR_MORE
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__check_arguments_55, 0);
  // 1362: if wanted_inputs.is_defined:
  // 1363:   $min_inputs
  // 1364:     if
  // 1365:       wanted_inputs == ONE_OR_MORE
  // 1366:       -> 1
  // 1367:       -> wanted_inputs
  // 1368:   
  // 1369:   $max_inputs
  // 1370:     if
  // 1371:       wanted_inputs == ONE_OR_MORE
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
  // 1388: ... check_arguments node kind wanted_outputs wanted_inputs
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[1] /* kind */;
  arguments->slots[2] = frame->slots[2] /* wanted_outputs */;
  arguments->slots[3] = frame->slots[3] /* wanted_inputs */;
  result_count = frame->caller_result_count;
  myself = func__check_arguments;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__CHECK_ARGUMENTS(void) {
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
  // 1388: ... : (node) check_arguments node kind wanted_outputs wanted_inputs
  frame->slots[3] /* temp__1 */ = create_closure(entry__CHECK_ARGUMENTS_2, 1);
  // 1388: inspect_node: (node) check_arguments node kind wanted_outputs wanted_inputs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__inspect_node();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__parse_meta_instruction(void) {
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
  // 1545: %compiler::current_fragment fragment
  // 1546:   # used to generate meaningful error messages
  initialize_maybe_future(get__compiler__current_fragment(), frame->slots[0] /* fragment */);
  // 1548: $source compiler::source_of(fragment)
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
  // 1549: match source META_FRAGMENT $len $cap
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
  // 1550: ... length_of(source)
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
  // 1550: ... len != length_of(source)
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
  // 1550: ... len != length_of(source)
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
  // 1550: ... : ParseError source "invalid meta instruction"
  frame->slots[8] /* temp__4 */ = create_closure(entry__compiler__parse_meta_instruction_7, 0);
  // 1550: if len != length_of(source): ParseError source "invalid meta instruction"
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
  // 1550: ... ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__12eb1acbffa2ae01;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__parse_meta_instruction_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1551: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__parse_statement(void) {
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
  // 1554: %compiler::current_fragment fragment
  // 1555:   # used to generate meaningful error messages
  initialize_maybe_future(get__compiler__current_fragment(), frame->slots[0] /* fragment */);
  // 1557: $source compiler::source_of(fragment)
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
  // 1558: match source FRAGMENT $len $cap
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
  // 1560: len.is_defined
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
  // 1560: ... :
  // 1561:   if len != length_of(source):
  // 1562:     ParseError source "superficious input at end of expression"
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__parse_statement_5, 0);
  // 1563: :
  // 1564:   ewriteln "________________________________________"
  // 1565:   eprint_source source
  // 1566:   ewriteln "no match"
  // 1567:   exit 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__parse_statement_11, 0);
  // 1559: if
  // 1560:   len.is_defined:
  // 1561:     if len != length_of(source):
  // 1562:       ParseError source "superficious input at end of expression"
  // 1563:   :
  // 1564:     ewriteln "________________________________________"
  // 1565:     eprint_source source
  // 1566:     ewriteln "no match"
  // 1567:     exit 1
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
  // 1562: ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__482d004bd19ca8db;
  result_count = frame->caller_result_count;
  myself = func__ParseError;
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
  // 1561: ... length_of(source)
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
  // 1561: ... len != length_of(source)
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
  // 1561: ... len != length_of(source)
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
  // 1561: ... :
  // 1562:   ParseError source "superficious input at end of expression"
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__parse_statement_9, 0);
  // 1561: if len != length_of(source):
  // 1562:   ParseError source "superficious input at end of expression"
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
  // 1564: ewriteln "________________________________________"
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
  // 1565: eprint_source source
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
  // 1566: ewriteln "no match"
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
  // 1567: exit 1
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
  // 1568: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__parser(void) {
  var.compiler__std_identifier = collect_node(var.compiler__std_identifier);
  var.compiler__Warning = collect_node(var.compiler__Warning);
  var.compiler__SyntaxError = collect_node(var.compiler__SyntaxError);
  var.types__syntax_error = collect_node(var.types__syntax_error);
  var.types__unexpected_input_error = collect_node(var.types__unexpected_input_error);
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
  var.types__store_arguments_index = collect_node(var.types__store_arguments_index);
  var.types__inline = collect_node(var.types__inline);
  var._NOT_INLINE = collect_node(var._NOT_INLINE);
  var._NEWLINE = collect_node(var._NEWLINE);
  var._INDENT = collect_node(var._INDENT);
  var._OUTDENT = collect_node(var._OUTDENT);
  var._HASHTAG = collect_node(var._HASHTAG);
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
  func__compiler__std_identifier = create_function(entry__compiler__std_identifier, 1);
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
  func__print_message = create_function(entry__print_message, 4);
  string__eed8078214c9e0bd = from_latin_1_string("WARNING", 7);
  func__compiler__Warning = create_function(entry__compiler__Warning, 2);
  string__ae3c04ed6f185295 = from_latin_1_string("SYNTAX ERROR", 12);
  func__ExitWithSyntaxError = create_function(entry__ExitWithSyntaxError, 3);
  func__compiler__SyntaxError = create_function(entry__compiler__SyntaxError, 2);
  func__ParseError = create_function(entry__ParseError, 2);
  func__types__syntax_error___grammar__match = create_function(entry__types__syntax_error___grammar__match, 2);
  func__syntax_error = create_function(entry__syntax_error, 1);
  string__9a64e069c352dc6a = from_latin_1_string("newline expected", 16);
  string__927507b8d9967cca = from_latin_1_string("indent expected", 15);
  string__9be468e9e34a9c6a = from_latin_1_string("outdent expected", 16);
  string__ab853eb411a7faea = from_latin_1_string("closing quotation mark expected", 31);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__68d023a4c22b2461 = from_latin_1_string(" expected", 9);
  string__4914d002f7e03078 = from_latin_1_string("unexpected input", 16);
  func__types__unexpected_input_error___grammar__match = create_function(entry__types__unexpected_input_error___grammar__match, 2);
  func__unexpected_input_error = create_function(entry__unexpected_input_error, 1);
  string__8c16e735f8cebe3d = from_latin_1_string("<<<<<<<<<<", 10);
  string__881ef7b4fade9e7f = from_latin_1_string(">>>>>>>>>>", 10);
  func__dump_stream___grammar__match = create_function(entry__dump_stream___grammar__match, 2);
  func__compiler__strip_18 = create_function(entry__compiler__strip_18, 1);
  func__compiler__strip_26 = create_function(entry__compiler__strip_26, 1);
  func__compiler__strip_34 = create_function(entry__compiler__strip_34, 1);
  func__compiler__strip = create_function(entry__compiler__strip, 1);
  string__665e06ec4dcad6be = from_latin_1_string("strip(grammar::current_node)", 28);
  func__dump___grammar__match = create_function(entry__dump___grammar__match, 2);
  func__dump3___grammar__match = create_function(entry__dump3___grammar__match, 2);
  func__dump5___grammar__match = create_function(entry__dump5___grammar__match, 2);
  func__compiler__precedence_5 = create_function(entry__compiler__precedence_5, 0);
  func__compiler__precedence = create_function(entry__compiler__precedence, 1);
  func__compiler__is_left_associative = create_function(entry__compiler__is_left_associative, 1);
  func__is_right_associative = create_function(entry__is_right_associative, 1);
  func__infix_operator = create_function(entry__infix_operator, 1);
  func__interleaved = create_function(entry__interleaved, 2);
  func__types__store_arguments_index___grammar__match = create_function(entry__types__store_arguments_index___grammar__match, 2);
  func__store_arguments_index = create_function(entry__store_arguments_index, 1);
  func__types__inline___grammar__match = create_function(entry__types__inline___grammar__match, 2);
  func__inline = create_function(entry__inline, 1);
  func__expect = create_function(entry__expect, -1);
  func__compiler__arguments_span = create_function(entry__compiler__arguments_span, 1);
  string__120dee9a1dcec47c = from_latin_1_string("invalid functor", 15);
  func__check_functor = create_function(entry__check_functor, 1);
  string__c5acb93e4d23cfd9 = from_latin_1_string("unexpected attribute-value-pair", 31);
  string__687da0cc5622be9c = from_latin_1_string("simple argument within attribute definition", 43);
  string__4f498b003024119a = from_latin_1_string("procedure call", 14);
  string__47a9393383380498 = from_latin_1_string("object definition", 17);
  string__5fa0d5b2a9ee383d = from_latin_1_string("too many output arguments for ", 30);
  string__1b6e5ce3b21cbf2f = from_latin_1_string("too few output arguments for ", 29);
  unique__ONE_OR_MORE = register_unique_item("ONE_OR_MORE");
  func__check_arguments_58 = create_function(entry__check_arguments_58, 0);
  func__check_arguments_62 = create_function(entry__check_arguments_62, 0);
  string__ebee6487b4b0342b = from_latin_1_string("too many input arguments for ", 29);
  string__bb0c2c1e659a1755 = from_latin_1_string("too few input arguments for ", 28);
  func__check_arguments = create_function(entry__check_arguments, -1);
  func__CHECK_ARGUMENTS = create_function(entry__CHECK_ARGUMENTS, -1);
  string__12eb1acbffa2ae01 = from_latin_1_string("invalid meta instruction", 24);
  func__compiler__parse_meta_instruction = create_function(entry__compiler__parse_meta_instruction, 1);
  string__482d004bd19ca8db = from_latin_1_string("superficious input at end of expression", 39);
  string__5278dd75c73e18e3 = from_latin_1_string("________________________________________", 40);
  string__6ca8a8f604cd4188 = from_latin_1_string("no match", 8);
  func__compiler__parse_statement = create_function(entry__compiler__parse_statement, 1);
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
  var.compiler__std_identifier = create_future();
  define_single_assign_static("compiler", "std_identifier", get__compiler__std_identifier, &var.compiler__std_identifier);
  var.compiler__Warning = create_future();
  define_single_assign_static("compiler", "Warning", get__compiler__Warning, &var.compiler__Warning);
  var.compiler__SyntaxError = create_future();
  define_single_assign_static("compiler", "SyntaxError", get__compiler__SyntaxError, &var.compiler__SyntaxError);
  var.types__syntax_error = create_future();
  define_single_assign_static("types", "syntax_error", get__types__syntax_error, &var.types__syntax_error);
  var.types__unexpected_input_error = create_future();
  define_single_assign_static("types", "unexpected_input_error", get__types__unexpected_input_error, &var.types__unexpected_input_error);
  var._dump_stream = create_future();
  var.compiler__strip = create_future();
  define_single_assign_static("compiler", "strip", get__compiler__strip, &var.compiler__strip);
  var._dump = create_future();
  var._dump3 = create_future();
  var._dump5 = create_future();
  var.compiler__HIGHEST_PRECEDENCE = create_future();
  define_single_assign_static("compiler", "HIGHEST_PRECEDENCE", get__compiler__HIGHEST_PRECEDENCE, &var.compiler__HIGHEST_PRECEDENCE);
  var.compiler__INFIX_PRECEDENCE = create_future();
  define_single_assign_static("compiler", "INFIX_PRECEDENCE", get__compiler__INFIX_PRECEDENCE, &var.compiler__INFIX_PRECEDENCE);
  var._precedence_table = create_future();
  var.compiler__precedence = create_future();
  define_single_assign_static("compiler", "precedence", get__compiler__precedence, &var.compiler__precedence);
  var.compiler__is_left_associative = create_future();
  define_single_assign_static("compiler", "is_left_associative", get__compiler__is_left_associative, &var.compiler__is_left_associative);
  register_dynamic(&dyna_idx__arguments_index);
  define__arguments_index(create_future());
  var.types__store_arguments_index = create_future();
  define_single_assign_static("types", "store_arguments_index", get__types__store_arguments_index, &var.types__store_arguments_index);
  register_dynamic(&dyna_idx__within_inline_expression);
  define__within_inline_expression(create_future());
  var.types__inline = create_future();
  define_single_assign_static("types", "inline", get__types__inline, &var.types__inline);
  var._NOT_INLINE = create_future();
  var._NEWLINE = create_future();
  var._INDENT = create_future();
  var._OUTDENT = create_future();
  var._HASHTAG = create_future();
  var.compiler__arguments_span = create_future();
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
  var.compiler__parse_meta_instruction = create_future();
  define_single_assign_static("compiler", "parse_meta_instruction", get__compiler__parse_meta_instruction, &var.compiler__parse_meta_instruction);
  var.compiler__parse_statement = create_future();
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
  define_method("types", "syntax_error", poly_idx__grammar__match, func__types__syntax_error___grammar__match);
  define_method("types", "unexpected_input_error", poly_idx__grammar__match, func__types__unexpected_input_error___grammar__match);
  update_start_p = node_p;
  def_attribute(&var._dump_stream, poly_idx__grammar__match, func__dump_stream___grammar__match);
  update_start_p = node_p;
  def_attribute(&var._dump, poly_idx__grammar__match, func__dump___grammar__match);
  update_start_p = node_p;
  def_attribute(&var._dump3, poly_idx__grammar__match, func__dump3___grammar__match);
  update_start_p = node_p;
  def_attribute(&var._dump5, poly_idx__grammar__match, func__dump5___grammar__match);
  define_method("types", "store_arguments_index", poly_idx__grammar__match, func__types__store_arguments_index___grammar__match);
  define_method("types", "inline", poly_idx__grammar__match, func__types__inline___grammar__match);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__parser(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  initialize_future(var.compiler__std_identifier, func__compiler__std_identifier);
  initialize_future(var.compiler__Warning, func__compiler__Warning);
  initialize_future(var.compiler__SyntaxError, func__compiler__SyntaxError);
  initialize_future(var.types__syntax_error, get__types__grammar_object());
  initialize_future(var.types__unexpected_input_error, get__types__grammar_object());
  initialize_future(var._dump_stream, get__types__grammar_object());
  initialize_future(var.compiler__strip, func__compiler__strip);
  initialize_future(var._dump, get__types__grammar_object());
  initialize_future(var._dump3, get__types__grammar_object());
  initialize_future(var._dump5, get__types__grammar_object());
  initialize_future(var.compiler__HIGHEST_PRECEDENCE, number__99);
  initialize_future(var.compiler__INFIX_PRECEDENCE, number__6);
  initialize_future(var.compiler__precedence, func__compiler__precedence);
  initialize_future(var.compiler__is_left_associative, func__compiler__is_left_associative);
  maybe_initialize_future(get__arguments_index(), get__undefined());
  initialize_future(var.types__store_arguments_index, get__types__grammar_object());
  maybe_initialize_future(get__within_inline_expression(), get__false());
  initialize_future(var.types__inline, get__types__grammar_object());
  initialize_future(var.compiler__arguments_span, func__compiler__arguments_span);
  initialize_future(var.compiler__parse_meta_instruction, func__compiler__parse_meta_instruction);
  initialize_future(var.compiler__parse_statement, func__compiler__parse_statement);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__parser(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__parser);
}
