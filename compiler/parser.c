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
IMPORT int print(char **buf_p, const char *format, ...);
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
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_future(void);
IMPORT NODE *undefined;
IMPORT NODE *empty_string;
IMPORT NODE *create_cell(void);
IMPORT NODE *create_continuation(void);
IMPORT void *copy(const void *buf, long size);
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
IMPORT void register_polymorphic_function(const char *name, int *id_p);
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
IMPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
);
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void def_attribute(NODE **var_p, int idx, void *attr);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__OUT_PARAMETER;
static NODE_GETTER get_value_or_future__OUT_PARAMETER;
static NODE_GETTER get__POLYMORPHIC;
static NODE_GETTER get_value_or_future__POLYMORPHIC;
static NODE_GETTER get__PRINTABLE_CHARACTER;
static NODE_GETTER get_value_or_future__PRINTABLE_CHARACTER;
static NODE_GETTER get__SyntaxError;
static NODE_GETTER get_value_or_future__SyntaxError;
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
static NODE_GETTER get__enumeration_count;
static NODE_SETTER set__enumeration_count;
static int poly_idx__enumeration_no_of;
static NODE_GETTER get__enumeration_no_of;
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
static NODE_GETTER get__is_a_character;
static NODE_GETTER get_value_or_future__is_a_character;
static NODE_GETTER get__is_a_definition;
static NODE_GETTER get_value_or_future__is_a_definition;
static int poly_idx__is_a_destination;
static NODE_GETTER get__is_a_destination;
static NODE_GETTER get__is_a_meta_instruction;
static NODE_GETTER get_value_or_future__is_a_meta_instruction;
static int poly_idx__is_a_method_definition;
static NODE_GETTER get__is_a_method_definition;
static NODE_GETTER get__is_a_string;
static NODE_GETTER get_value_or_future__is_a_string;
static int poly_idx__is_a_string_template;
static NODE_GETTER get__is_a_string_template;
static int poly_idx__is_an_attribute_access;
static NODE_GETTER get__is_an_attribute_access;
static NODE_GETTER get__is_an_expanded_item;
static NODE_GETTER get_value_or_future__is_an_expanded_item;
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
static int poly_idx__output_arguments_of;
static NODE_GETTER get__output_arguments_of;
static NODE_GETTER get__output_arguments_span;
static NODE_GETTER get_value_or_future__output_arguments_span;
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
static int poly_idx__remark_lines_behind_of;
static NODE_GETTER get__remark_lines_behind_of;
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
static NODE_GETTER get__sim2c__current_fragment;
static NODE_SETTER define__sim2c__current_fragment;
static NODE_GETTER get__sim2c__source_of;
static NODE_GETTER get_value_or_future__sim2c__source_of;
static NODE_GETTER get__sim2c__text_of;
static NODE_GETTER get_value_or_future__sim2c__text_of;
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
  NODE *_print;
  NODE *_dump_stream;
  NODE *_dump;
  NODE *_dump3;
  NODE *_dump5;
  NODE *_precedence_table;
  NODE *_is_right_associative;
  NODE *_infix_operator;
  NODE *_interleaved;
  NODE *_inline;
  NODE *_NOT_INLINE;
  NODE *_NEWLINE;
  NODE *_INDENT;
  NODE *_OUTDENT;
  NODE *_HASHTAG;
  NODE *_expect;
  NODE *_ENUMERATE;
  NODE *_MAKE_A_DESTINATION;
  NODE *_SEPARATOR;
  NODE *_NEWLINES;
  NODE *_NEXT_LINE;
  NODE *_STORE_POSITION;
  NODE *_STORE_POSITION_MINUS_1;
  NODE *_STORE_POSITION_MINUS_2;
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
  NODE *_SINGLE_REMARK_STATEMENT;
  NODE *_REMARK_STATEMENT;
  NODE *_REMARK;
  NODE *_REMARK_BEHIND;
  NODE *_LINE_END_REMARK;
  NODE *_ARGUMENT_LINE_END_REMARK;
  NODE *_ARGUMENT_REMARK;
  NODE *_NEW_LINE_END_REMARK;
  NODE *_NEXT_LINE_REMARK;
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
  NODE *_INPUT_ARGUMENT;
  NODE *_EXPANSION;
  NODE *_OUTPUT_ARGUMENT;
  NODE *_INPUT_OUTPUT_ARGUMENT;
  NODE *_COPY_OUTPUT;
  NODE *_MAYBE_SPLIT_INPUT;
  NODE *_SIMPLE_ARGUMENT;
  NODE *_INLINE_ATTRIBUTE_VALUE_PAIR;
  NODE *_ATTRIBUTE_VALUE_PAIR;
  NODE *_INLINE_ATTRIBUTE_VALUE_PAIRS;
  NODE *_INDENTED_ATTRIBUTE_VALUE_PAIRS;
  NODE *_SINGLE_EXPRESSION_LINE;
  NODE *_PROCEDURE_ARGUMENTS;
  NODE *_ARGUMENTS;
  NODE *_OPERATORS_AND_OPERANDS;
  NODE *_MULTI_LINE_FUNCTION_CALL;
  NODE *_original_remark_lines_of;
  NODE *_INDENTED_FUNCTION_CALL_OR_REMARK;
  NODE *_MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK;
  NODE *_ARGUMENT_EXPANSION;
  NODE *_MULTI_LINE_EXPRESSION;
  NODE *_LINE_START_ARGUMENT;
  NODE *_LINE_START_ARGUMENTS;
  NODE *_MORE_LINE_START_ARGUMENTS;
  NODE *_FIRST_LINE_START_ARGUMENTS;
  NODE *_SINGLE_INPUT_ARGUMENT;
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
  NODE *_ASSIGNMENT;
  NODE *_POLYMORPHIC_FUNCTION_WITHOUT_SETTER;
  NODE *_POLYMORPHIC_FUNCTION_WITH_SETTER;
  NODE *_POLYMORPHIC_FUNCTION;
  NODE *_TOP_LEVEL_ASSIGNMENT;
  NODE *_FUNCTOR;
  NODE *_RESULT_COUNT_OR_CONTINUATION;
  NODE *_PROCEDURE_CALL;
  NODE *_INDENTED_REMARKS;
  NODE *_SINGLE_STATEMENT;
  NODE *_TOP_LEVEL_STATEMENT;
  NODE *_STATEMENT;
  NODE *_RETURN_STATEMENT;
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
  NODE *sim2c__std_identifier;
  NODE *sim2c__Warning;
  NODE *sim2c__SyntaxError;
  NODE *types__syntax_error;
  NODE *types__unexpected_input_error;
  NODE *types__print;
  NODE *sim2c__strip;
  NODE *sim2c__HIGHEST_PRECEDENCE;
  NODE *sim2c__INFIX_PRECEDENCE;
  NODE *sim2c__precedence;
  NODE *sim2c__is_left_associative;
  NODE *types__inline;
  NODE *sim2c__arguments_span;
  NODE *sim2c__output_arguments_span;
  NODE *sim2c__WHITESPACE;
  NODE *sim2c__parse_meta_instruction;
  NODE *sim2c__parse_statement;
} var;
static const char *var_names[] = {
  "print_message",
  "ExitWithSyntaxError",
  "ParseError",
  "syntax_error",
  "unexpected_input_error",
  "print",
  "dump_stream",
  "dump",
  "dump3",
  "dump5",
  "precedence_table",
  "is_right_associative",
  "infix_operator",
  "interleaved",
  "inline",
  "NOT_INLINE",
  "NEWLINE",
  "INDENT",
  "OUTDENT",
  "HASHTAG",
  "expect",
  "ENUMERATE",
  "MAKE_A_DESTINATION",
  "SEPARATOR",
  "NEWLINES",
  "NEXT_LINE",
  "STORE_POSITION",
  "STORE_POSITION_MINUS_1",
  "STORE_POSITION_MINUS_2",
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
  "SINGLE_REMARK_STATEMENT",
  "REMARK_STATEMENT",
  "REMARK",
  "REMARK_BEHIND",
  "LINE_END_REMARK",
  "ARGUMENT_LINE_END_REMARK",
  "ARGUMENT_REMARK",
  "NEW_LINE_END_REMARK",
  "NEXT_LINE_REMARK",
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
  "INPUT_ARGUMENT",
  "EXPANSION",
  "OUTPUT_ARGUMENT",
  "INPUT_OUTPUT_ARGUMENT",
  "COPY_OUTPUT",
  "MAYBE_SPLIT_INPUT",
  "SIMPLE_ARGUMENT",
  "INLINE_ATTRIBUTE_VALUE_PAIR",
  "ATTRIBUTE_VALUE_PAIR",
  "INLINE_ATTRIBUTE_VALUE_PAIRS",
  "INDENTED_ATTRIBUTE_VALUE_PAIRS",
  "SINGLE_EXPRESSION_LINE",
  "PROCEDURE_ARGUMENTS",
  "ARGUMENTS",
  "OPERATORS_AND_OPERANDS",
  "MULTI_LINE_FUNCTION_CALL",
  "original_remark_lines_of",
  "INDENTED_FUNCTION_CALL_OR_REMARK",
  "MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK",
  "ARGUMENT_EXPANSION",
  "MULTI_LINE_EXPRESSION",
  "LINE_START_ARGUMENT",
  "LINE_START_ARGUMENTS",
  "MORE_LINE_START_ARGUMENTS",
  "FIRST_LINE_START_ARGUMENTS",
  "SINGLE_INPUT_ARGUMENT",
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
  "ASSIGNMENT",
  "POLYMORPHIC_FUNCTION_WITHOUT_SETTER",
  "POLYMORPHIC_FUNCTION_WITH_SETTER",
  "POLYMORPHIC_FUNCTION",
  "TOP_LEVEL_ASSIGNMENT",
  "FUNCTOR",
  "RESULT_COUNT_OR_CONTINUATION",
  "PROCEDURE_CALL",
  "INDENTED_REMARKS",
  "SINGLE_STATEMENT",
  "TOP_LEVEL_STATEMENT",
  "STATEMENT",
  "RETURN_STATEMENT",
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
static NODE *func__sim2c__std_identifier_1;
static void entry__sim2c__std_identifier_1(void);
static FRAME_INFO frame__sim2c__std_identifier_1 = {1, {"name"}};
static NODE *string__fa724815d896ba8;
static NODE *get__sim2c__std_identifier(void) {
  return var.sim2c__std_identifier;
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
static NODE *func__sim2c__Warning_1;
static void entry__sim2c__Warning_1(void);
static FRAME_INFO frame__sim2c__Warning_1 = {2, {"obj", "msg"}};
static void cont__sim2c__Warning_2(void);
static void cont__sim2c__Warning_3(void);
static NODE *string__eed8078214c9e0bd;
static NODE *get__sim2c__Warning(void) {
  return var.sim2c__Warning;
}
static NODE *func__ExitWithSyntaxError_1;
static void entry__ExitWithSyntaxError_1(void);
static FRAME_INFO frame__ExitWithSyntaxError_1 = {3, {"fragment", "offset", "msg"}};
static NODE *string__ae3c04ed6f185295;
static void cont__ExitWithSyntaxError_3(void);
static NODE *func__sim2c__SyntaxError_1;
static void entry__sim2c__SyntaxError_1(void);
static FRAME_INFO frame__sim2c__SyntaxError_1 = {2, {"obj", "msg"}};
static void cont__sim2c__SyntaxError_2(void);
static void cont__sim2c__SyntaxError_3(void);
static NODE *get__sim2c__SyntaxError(void) {
  return var.sim2c__SyntaxError;
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
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_16 = {2, {"stream", "expression"}};
static NODE *string__578a5af303e9cc3;
static NODE *string__33060513e6032545;
static void cont__types__unexpected_input_error__grammar__match_19(void);
static NODE *func__types__unexpected_input_error__grammar__match_20;
static void entry__types__unexpected_input_error__grammar__match_20(void);
static FRAME_INFO frame__types__unexpected_input_error__grammar__match_20 = {1, {"stream"}};
static NODE *string__4914d002f7e03078;
static NODE *func__unexpected_input_error_1;
static void entry__unexpected_input_error_1(void);
static FRAME_INFO frame__unexpected_input_error_1 = {1, {"expression"}};
static NODE *get__types__print(void) {
  return var.types__print;
}
static NODE *func__types__print__grammar__match_1;
static void entry__types__print__grammar__match_1(void);
static FRAME_INFO frame__types__print__grammar__match_1 = {2, {"self", "stream"}};
static void cont__types__print__grammar__match_2(void);
static void cont__types__print__grammar__match_3(void);
static NODE *func__print_1;
static void entry__print_1(void);
static FRAME_INFO frame__print_1 = {1, {"message"}};
static NODE *func__dump_stream__grammar__match_1;
static void entry__dump_stream__grammar__match_1(void);
static FRAME_INFO frame__dump_stream__grammar__match_1 = {2, {"self", "stream"}};
static NODE *string__8c16e735f8cebe3d;
static void cont__dump_stream__grammar__match_3(void);
static void cont__dump_stream__grammar__match_4(void);
static void cont__dump_stream__grammar__match_5(void);
static NODE *string__881ef7b4fade9e7f;
static void cont__dump_stream__grammar__match_7(void);
static NODE *func__sim2c__strip_1;
static void entry__sim2c__strip_1(void);
static FRAME_INFO frame__sim2c__strip_1 = {1, {"node"}};
static void cont__sim2c__strip_2(void);
static void cont__sim2c__strip_3(void);
static NODE *func__sim2c__strip_4;
static void entry__sim2c__strip_4(void);
static FRAME_INFO frame__sim2c__strip_4 = {1, {"node"}};
static void cont__sim2c__strip_5(void);
static void cont__sim2c__strip_6(void);
static void cont__sim2c__strip_7(void);
static void cont__sim2c__strip_8(void);
static void cont__sim2c__strip_9(void);
static NODE *func__sim2c__strip_10;
static void entry__sim2c__strip_10(void);
static FRAME_INFO frame__sim2c__strip_10 = {1, {"node"}};
static void cont__sim2c__strip_11(void);
static void cont__sim2c__strip_12(void);
static void cont__sim2c__strip_13(void);
static void cont__sim2c__strip_14(void);
static void cont__sim2c__strip_15(void);
static NODE *func__sim2c__strip_16;
static void entry__sim2c__strip_16(void);
static FRAME_INFO frame__sim2c__strip_16 = {1, {"node"}};
static void cont__sim2c__strip_17(void);
static NODE *func__sim2c__strip_18;
static void entry__sim2c__strip_18(void);
static FRAME_INFO frame__sim2c__strip_18 = {1, {"statement"}};
static void cont__sim2c__strip_19(void);
static void cont__sim2c__strip_20(void);
static void cont__sim2c__strip_21(void);
static void cont__sim2c__strip_22(void);
static void cont__sim2c__strip_23(void);
static NODE *func__sim2c__strip_24;
static void entry__sim2c__strip_24(void);
static FRAME_INFO frame__sim2c__strip_24 = {1, {"node"}};
static void cont__sim2c__strip_25(void);
static NODE *func__sim2c__strip_26;
static void entry__sim2c__strip_26(void);
static FRAME_INFO frame__sim2c__strip_26 = {1, {"parameter"}};
static void cont__sim2c__strip_27(void);
static void cont__sim2c__strip_28(void);
static void cont__sim2c__strip_29(void);
static void cont__sim2c__strip_30(void);
static void cont__sim2c__strip_31(void);
static NODE *func__sim2c__strip_32;
static void entry__sim2c__strip_32(void);
static FRAME_INFO frame__sim2c__strip_32 = {1, {"node"}};
static void cont__sim2c__strip_33(void);
static NODE *func__sim2c__strip_34;
static void entry__sim2c__strip_34(void);
static FRAME_INFO frame__sim2c__strip_34 = {1, {"argument"}};
static void cont__sim2c__strip_35(void);
static void cont__sim2c__strip_36(void);
static void cont__sim2c__strip_37(void);
static void cont__sim2c__strip_38(void);
static void cont__sim2c__strip_39(void);
static NODE *func__sim2c__strip_40;
static void entry__sim2c__strip_40(void);
static FRAME_INFO frame__sim2c__strip_40 = {1, {"node"}};
static void cont__sim2c__strip_41(void);
static NODE *func__sim2c__strip_42;
static void entry__sim2c__strip_42(void);
static FRAME_INFO frame__sim2c__strip_42 = {1, {"argument"}};
static void cont__sim2c__strip_43(void);
static void cont__sim2c__strip_44(void);
static void cont__sim2c__strip_45(void);
static void cont__sim2c__strip_46(void);
static void cont__sim2c__strip_47(void);
static NODE *func__sim2c__strip_48;
static void entry__sim2c__strip_48(void);
static FRAME_INFO frame__sim2c__strip_48 = {1, {"node"}};
static void cont__sim2c__strip_49(void);
static void cont__sim2c__strip_50(void);
static void cont__sim2c__strip_51(void);
static void cont__sim2c__strip_52(void);
static void cont__sim2c__strip_53(void);
static NODE *func__sim2c__strip_54;
static void entry__sim2c__strip_54(void);
static FRAME_INFO frame__sim2c__strip_54 = {1, {"node"}};
static void cont__sim2c__strip_55(void);
static void cont__sim2c__strip_56(void);
static void cont__sim2c__strip_57(void);
static NODE *get__sim2c__strip(void) {
  return var.sim2c__strip;
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
static NODE *get__sim2c__HIGHEST_PRECEDENCE(void) {
  return var.sim2c__HIGHEST_PRECEDENCE;
}
static NODE *get__sim2c__INFIX_PRECEDENCE(void) {
  return var.sim2c__INFIX_PRECEDENCE;
}
static NODE *func__sim2c__precedence_1;
static void entry__sim2c__precedence_1(void);
static FRAME_INFO frame__sim2c__precedence_1 = {1, {"op"}};
static void cont__sim2c__precedence_2(void);
static NODE *func__sim2c__precedence_3;
static void entry__sim2c__precedence_3(void);
static FRAME_INFO frame__sim2c__precedence_3 = {1, {"op"}};
static void cont__sim2c__precedence_4(void);
static NODE *func__sim2c__precedence_5;
static void entry__sim2c__precedence_5(void);
static FRAME_INFO frame__sim2c__precedence_5 = {0, {}};
static NODE *get__sim2c__precedence(void) {
  return var.sim2c__precedence;
}
static NODE *func__sim2c__is_left_associative_1;
static void entry__sim2c__is_left_associative_1(void);
static FRAME_INFO frame__sim2c__is_left_associative_1 = {1, {"prec"}};
static void cont__sim2c__is_left_associative_2(void);
static NODE *get__sim2c__is_left_associative(void) {
  return var.sim2c__is_left_associative;
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
static NODE *string__68d023a4c22b2461;
static void cont__expect_5(void);
static void cont__expect_6(void);
static void cont__expect_7(void);
static NODE *func__expect_8;
static void entry__expect_8(void);
static FRAME_INFO frame__expect_8 = {1, {"expression"}};
static void cont__expect_9(void);
static void cont__expect_10(void);
static NODE *func__sim2c__arguments_span_1;
static void entry__sim2c__arguments_span_1(void);
static FRAME_INFO frame__sim2c__arguments_span_1 = {1, {"expression"}};
static void cont__sim2c__arguments_span_2(void);
static void cont__sim2c__arguments_span_3(void);
static NODE *get__sim2c__arguments_span(void) {
  return var.sim2c__arguments_span;
}
static NODE *func__sim2c__output_arguments_span_1;
static void entry__sim2c__output_arguments_span_1(void);
static FRAME_INFO frame__sim2c__output_arguments_span_1 = {1, {"expression"}};
static void cont__sim2c__output_arguments_span_2(void);
static void cont__sim2c__output_arguments_span_3(void);
static NODE *get__sim2c__output_arguments_span(void) {
  return var.sim2c__output_arguments_span;
}
static NODE *get__sim2c__WHITESPACE(void) {
  return var.sim2c__WHITESPACE;
}
static int poly_idx__original_remark_lines_of;
static void type__original_remark_lines_of(void);
static NODE *func__sim2c__parse_meta_instruction_1;
static void entry__sim2c__parse_meta_instruction_1(void);
static FRAME_INFO frame__sim2c__parse_meta_instruction_1 = {5, {"fragment", "return__1", "source", "len", "cap"}};
static void cont__sim2c__parse_meta_instruction_2(void);
static void cont__sim2c__parse_meta_instruction_3(void);
static void cont__sim2c__parse_meta_instruction_4(void);
static void cont__sim2c__parse_meta_instruction_5(void);
static void cont__sim2c__parse_meta_instruction_6(void);
static NODE *func__sim2c__parse_meta_instruction_7;
static void entry__sim2c__parse_meta_instruction_7(void);
static FRAME_INFO frame__sim2c__parse_meta_instruction_7 = {1, {"source"}};
static NODE *string__12eb1acbffa2ae01;
static void cont__sim2c__parse_meta_instruction_9(void);
static NODE *get__sim2c__parse_meta_instruction(void) {
  return var.sim2c__parse_meta_instruction;
}
static NODE *func__sim2c__parse_statement_1;
static void entry__sim2c__parse_statement_1(void);
static FRAME_INFO frame__sim2c__parse_statement_1 = {5, {"fragment", "return__1", "source", "len", "cap"}};
static void cont__sim2c__parse_statement_2(void);
static void cont__sim2c__parse_statement_3(void);
static void cont__sim2c__parse_statement_4(void);
static NODE *func__sim2c__parse_statement_5;
static void entry__sim2c__parse_statement_5(void);
static FRAME_INFO frame__sim2c__parse_statement_5 = {2, {"len", "source"}};
static void cont__sim2c__parse_statement_6(void);
static void cont__sim2c__parse_statement_7(void);
static void cont__sim2c__parse_statement_8(void);
static NODE *func__sim2c__parse_statement_9;
static void entry__sim2c__parse_statement_9(void);
static FRAME_INFO frame__sim2c__parse_statement_9 = {1, {"source"}};
static NODE *string__482d004bd19ca8db;
static NODE *func__sim2c__parse_statement_11;
static void entry__sim2c__parse_statement_11(void);
static FRAME_INFO frame__sim2c__parse_statement_11 = {1, {"source"}};
static NODE *string__5278dd75c73e18e3;
static void cont__sim2c__parse_statement_13(void);
static void cont__sim2c__parse_statement_14(void);
static NODE *string__6ca8a8f604cd4188;
static void cont__sim2c__parse_statement_16(void);
static void cont__sim2c__parse_statement_17(void);
static NODE *get__sim2c__parse_statement(void) {
  return var.sim2c__parse_statement;
}
static NODE *string__578a5af303e9ccb;
static void cont__236_2(void);
static NODE *string__578a5af303e9cce;
static void cont__236_4(void);
static NODE *string__578a5af303e9cca;
static void cont__236_6(void);
static NODE *string__578a5af303e9ccc;
static void cont__236_8(void);
static NODE *string__2d7981f4e6e82bf9;
static void cont__236_10(void);
static NODE *string__2d7981f4e6f82bfb;
static void cont__236_12(void);
static NODE *string__578a5af303e9cc7;
static void cont__236_14(void);
static void cont__236_15(void);
static NODE *string__578a5af303e9c9d;
static void cont__236_17(void);
static NODE *string__2d7981f4e6e82bf8;
static void cont__236_19(void);
static NODE *string__578a5af303e9cdd;
static void cont__236_21(void);
static NODE *string__2d7981f4e6f82bf8;
static void cont__236_23(void);
static NODE *string__578a5af303e9cdf;
static void cont__236_25(void);
static NODE *string__2d7981f4e6e02bf8;
static void cont__236_27(void);
static NODE *string__2d7981f4e6002bf8;
static void cont__236_29(void);
static NODE *string__2d7981f4e6382be3;
static void cont__236_31(void);
static NODE *string__2d7981f4e4e82bb9;
static void cont__236_33(void);
static NODE *string__2d7981f4e6782beb;
static void cont__236_35(void);
static NODE *string__578a5af303e9ccd;
static void cont__236_37(void);
static NODE *string__578a5af303e9cdc;
static void cont__236_39(void);
static void cont__236_40(void);
static NODE *func__246_1;
static void entry__246_1(void);
static FRAME_INFO frame__246_1 = {2, {"node", "stream"}};
static NODE *func__246_2;
static void entry__246_2(void);
static FRAME_INFO frame__246_2 = {1, {"stream"}};
static NODE *string__ccbf6d451aa8563f;
static void cont__246_4(void);
static void cont__246_5(void);
static void cont__247_1(void);
static void cont__247_2(void);
static void cont__248_1(void);
static void cont__248_2(void);
static void cont__249_1(void);
static void cont__249_2(void);
static void cont__250_1(void);
static void cont__250_2(void);
static NODE *func__252_1;
static void entry__252_1(void);
static FRAME_INFO frame__252_1 = {1, {"node"}};
static void cont__252_2(void);
static void cont__252_3(void);
static NODE *func__253_1;
static void entry__253_1(void);
static FRAME_INFO frame__253_1 = {1, {"node"}};
static void cont__253_2(void);
static void cont__256_1(void);
static void cont__257_1(void);
static void cont__257_2(void);
static void cont__258_1(void);
static void cont__259_1(void);
static NODE *func__260_1;
static void entry__260_1(void);
static FRAME_INFO frame__260_1 = {2, {"node", "stream"}};
static void cont__260_2(void);
static void cont__260_3(void);
static NODE *func__261_1;
static void entry__261_1(void);
static FRAME_INFO frame__261_1 = {2, {"node", "stream"}};
static void cont__261_2(void);
static void cont__261_3(void);
static void cont__261_4(void);
static NODE *func__262_1;
static void entry__262_1(void);
static FRAME_INFO frame__262_1 = {2, {"node", "stream"}};
static void cont__262_2(void);
static void cont__262_3(void);
static void cont__262_4(void);
static NODE *func__263_1;
static void entry__263_1(void);
static FRAME_INFO frame__263_1 = {2, {"node", "stream"}};
static void cont__263_2(void);
static void cont__263_3(void);
static void cont__264_1(void);
static void cont__264_2(void);
static NODE *func__264_3;
static void entry__264_3(void);
static FRAME_INFO frame__264_3 = {1, {"node"}};
static void cont__264_4(void);
static void cont__264_5(void);
static void cont__264_6(void);
static NODE *string__2d7981f4e6d82bff;
static void cont__264_8(void);
static void cont__264_9(void);
static void cont__264_10(void);
static void cont__265_1(void);
static void cont__265_2(void);
static void cont__265_3(void);
static NODE *func__265_4;
static void entry__265_4(void);
static FRAME_INFO frame__265_4 = {1, {"node"}};
static void cont__265_5(void);
static NODE *func__265_6;
static void entry__265_6(void);
static FRAME_INFO frame__265_6 = {1, {"node"}};
static NODE *string__958c1dda41e5a79c;
static void cont__265_8(void);
static void cont__265_9(void);
static void cont__265_10(void);
static void cont__265_11(void);
static void cont__265_12(void);
static void cont__265_13(void);
static void cont__265_14(void);
static void cont__266_1(void);
static void cont__266_2(void);
static void cont__266_3(void);
static void cont__266_4(void);
static void cont__266_5(void);
static NODE *string__2d7981f4e6782bea;
static void cont__267_2(void);
static void cont__267_3(void);
static void cont__267_4(void);
static void cont__267_5(void);
static void cont__268_1(void);
static void cont__268_2(void);
static NODE *func__268_3;
static void entry__268_3(void);
static FRAME_INFO frame__268_3 = {3, {"node", "stream", "filename"}};
static void cont__268_4(void);
static void cont__268_5(void);
static void cont__268_6(void);
static NODE *func__268_7;
static void entry__268_7(void);
static FRAME_INFO frame__268_7 = {2, {"stream", "filename"}};
static NODE *string__92e1510f182d5769;
static NODE *string__fd365ba9213c93f1;
static void cont__268_10(void);
static void cont__268_11(void);
static void cont__268_12(void);
static void cont__268_13(void);
static NODE *string__44dcaf9484448bc5;
static void cont__268_15(void);
static void cont__269_1(void);
static void cont__269_2(void);
static void cont__269_3(void);
static NODE *func__269_4;
static void entry__269_4(void);
static FRAME_INFO frame__269_4 = {1, {"node"}};
static void cont__269_5(void);
static void cont__269_6(void);
static void cont__269_7(void);
static void cont__269_8(void);
static void cont__269_9(void);
static NODE *func__269_10;
static void entry__269_10(void);
static FRAME_INFO frame__269_10 = {4, {"node", "stream", "namespace", "alias"}};
static void cont__269_11(void);
static void cont__269_12(void);
static void cont__269_13(void);
static NODE *func__269_14;
static void entry__269_14(void);
static FRAME_INFO frame__269_14 = {3, {"alias", "stream", "namespace"}};
static void cont__269_15(void);
static void cont__269_16(void);
static NODE *func__269_17;
static void entry__269_17(void);
static FRAME_INFO frame__269_17 = {2, {"stream", "alias"}};
static NODE *string__e13e5990aea4c8f3;
static NODE *string__54767964cc2066c4;
static void cont__269_20(void);
static void cont__269_21(void);
static void cont__269_22(void);
static NODE *func__269_23;
static void entry__269_23(void);
static FRAME_INFO frame__269_23 = {2, {"namespace", "stream"}};
static void cont__269_24(void);
static NODE *func__269_25;
static void entry__269_25(void);
static FRAME_INFO frame__269_25 = {2, {"stream", "namespace"}};
static NODE *string__9159abe89634488c;
static void cont__269_27(void);
static void cont__269_28(void);
static void cont__269_29(void);
static void cont__269_30(void);
static NODE *string__1552f059283245c4;
static void cont__269_32(void);
static void cont__270_1(void);
static void cont__270_2(void);
static NODE *func__270_3;
static void entry__270_3(void);
static FRAME_INFO frame__270_3 = {3, {"node", "stream", "namespace"}};
static void cont__270_4(void);
static void cont__270_5(void);
static NODE *func__270_6;
static void entry__270_6(void);
static FRAME_INFO frame__270_6 = {2, {"stream", "namespace"}};
static NODE *string__1d0508008a8a40d8;
static void cont__270_8(void);
static void cont__270_9(void);
static void cont__270_10(void);
static void cont__270_11(void);
static NODE *string__7e1f542e81cb02b0;
static void cont__270_13(void);
static void cont__271_1(void);
static void cont__271_2(void);
static NODE *string__fa733c15f596be3;
static void cont__272_2(void);
static void cont__272_3(void);
static void cont__272_4(void);
static void cont__272_5(void);
static void cont__272_6(void);
static void cont__273_1(void);
static void cont__273_2(void);
static NODE *func__273_3;
static void entry__273_3(void);
static FRAME_INFO frame__273_3 = {3, {"node", "stream", "filename"}};
static void cont__273_4(void);
static void cont__273_5(void);
static NODE *func__273_6;
static void entry__273_6(void);
static FRAME_INFO frame__273_6 = {2, {"stream", "filename"}};
static NODE *string__2c64b158ac2be503;
static NODE *string__b0b6bb19371893f7;
static void cont__273_9(void);
static void cont__273_10(void);
static void cont__273_11(void);
static void cont__273_12(void);
static NODE *string__76b0a89104f5abc5;
static void cont__273_14(void);
static void cont__274_1(void);
static void cont__274_2(void);
static NODE *func__274_3;
static void entry__274_3(void);
static FRAME_INFO frame__274_3 = {3, {"node", "stream", "filename"}};
static void cont__274_4(void);
static void cont__274_5(void);
static NODE *func__274_6;
static void entry__274_6(void);
static FRAME_INFO frame__274_6 = {2, {"stream", "filename"}};
static NODE *string__a660d7293a5c47e8;
static NODE *string__ad06d2ccd69d8e1;
static void cont__274_9(void);
static void cont__274_10(void);
static void cont__274_11(void);
static void cont__274_12(void);
static NODE *string__525ae943eabdd03c;
static void cont__274_14(void);
static void cont__275_1(void);
static void cont__275_2(void);
static void cont__276_1(void);
static void cont__276_2(void);
static void cont__276_3(void);
static void cont__276_4(void);
static void cont__276_5(void);
static void cont__277_1(void);
static void cont__277_2(void);
static NODE *func__277_3;
static void entry__277_3(void);
static FRAME_INFO frame__277_3 = {3, {"node", "stream", "filemask"}};
static void cont__277_4(void);
static void cont__277_5(void);
static NODE *func__277_6;
static void entry__277_6(void);
static FRAME_INFO frame__277_6 = {2, {"stream", "filemask"}};
static NODE *string__e720c6242e8cd532;
static void cont__277_8(void);
static void cont__277_9(void);
static void cont__277_10(void);
static void cont__277_11(void);
static NODE *string__425aeb43ea6dd036;
static void cont__277_13(void);
static void cont__278_1(void);
static void cont__278_2(void);
static void cont__278_3(void);
static void cont__278_4(void);
static void cont__278_5(void);
static void cont__278_6(void);
static void cont__279_1(void);
static void cont__279_2(void);
static void cont__280_1(void);
static void cont__280_2(void);
static void cont__280_3(void);
static void cont__280_4(void);
static void cont__280_5(void);
static void cont__281_1(void);
static void cont__281_2(void);
static void cont__282_1(void);
static void cont__283_1(void);
static NODE *func__284_1;
static void entry__284_1(void);
static FRAME_INFO frame__284_1 = {1, {"node"}};
static void cont__284_2(void);
static NODE *func__284_3;
static void entry__284_3(void);
static FRAME_INFO frame__284_3 = {1, {"node"}};
static void cont__284_4(void);
static void cont__284_5(void);
static NODE *func__284_6;
static void entry__284_6(void);
static FRAME_INFO frame__284_6 = {2, {"node", "remark_lines"}};
static void cont__284_7(void);
static void cont__284_8(void);
static void cont__284_9(void);
static NODE *func__284_10;
static void entry__284_10(void);
static FRAME_INFO frame__284_10 = {2, {"node", "remark_lines"}};
static NODE *func__284_11;
static void entry__284_11(void);
static FRAME_INFO frame__284_11 = {2, {"node", "remark_lines"}};
static void cont__284_12(void);
static void cont__284_13(void);
static void cont__284_14(void);
static void cont__284_15(void);
static void cont__284_16(void);
static void cont__284_17(void);
static void cont__284_18(void);
static void cont__284_19(void);
static void cont__284_20(void);
static void cont__284_21(void);
static void cont__284_22(void);
static void cont__284_23(void);
static void cont__284_24(void);
static void cont__285_1(void);
static void cont__285_2(void);
static NODE *func__286_1;
static void entry__286_1(void);
static FRAME_INFO frame__286_1 = {1, {"node"}};
static void cont__286_2(void);
static NODE *func__286_3;
static void entry__286_3(void);
static FRAME_INFO frame__286_3 = {2, {"node", "n"}};
static void cont__286_4(void);
static void cont__286_5(void);
static void cont__286_6(void);
static NODE *func__286_7;
static void entry__286_7(void);
static FRAME_INFO frame__286_7 = {2, {"node", "n"}};
static void cont__286_8(void);
static void cont__286_9(void);
static void cont__286_10(void);
static void cont__286_11(void);
static void cont__286_12(void);
static void cont__286_13(void);
static void cont__286_14(void);
static void cont__286_15(void);
static void cont__286_16(void);
static void cont__286_17(void);
static void cont__286_18(void);
static void cont__286_19(void);
static void cont__286_20(void);
static void cont__286_21(void);
static void cont__286_22(void);
static void cont__286_23(void);
static void cont__286_24(void);
static NODE *func__287_1;
static void entry__287_1(void);
static FRAME_INFO frame__287_1 = {1, {"node"}};
static void cont__287_2(void);
static NODE *func__287_3;
static void entry__287_3(void);
static FRAME_INFO frame__287_3 = {2, {"node", "n"}};
static void cont__287_4(void);
static void cont__287_5(void);
static void cont__287_6(void);
static NODE *func__287_7;
static void entry__287_7(void);
static FRAME_INFO frame__287_7 = {2, {"node", "n"}};
static void cont__287_8(void);
static void cont__287_9(void);
static void cont__287_10(void);
static void cont__287_11(void);
static void cont__287_12(void);
static void cont__287_13(void);
static void cont__287_14(void);
static void cont__287_15(void);
static void cont__287_16(void);
static void cont__287_17(void);
static void cont__287_18(void);
static void cont__287_19(void);
static void cont__287_20(void);
static void cont__287_21(void);
static void cont__287_22(void);
static void cont__287_23(void);
static void cont__288_1(void);
static void cont__289_1(void);
static NODE *func__290_1;
static void entry__290_1(void);
static FRAME_INFO frame__290_1 = {1, {"node"}};
static void cont__290_2(void);
static void cont__290_3(void);
static void cont__290_4(void);
static void cont__290_5(void);
static void cont__290_6(void);
static void cont__290_7(void);
static void cont__290_8(void);
static void cont__290_9(void);
static NODE *func__291_1;
static void entry__291_1(void);
static FRAME_INFO frame__291_1 = {1, {"node"}};
static void cont__291_2(void);
static void cont__291_3(void);
static void cont__291_4(void);
static void cont__291_5(void);
static void cont__292_1(void);
static void cont__292_2(void);
static void cont__293_1(void);
static void cont__293_2(void);
static void cont__294_1(void);
static void cont__294_2(void);
static void cont__295_1(void);
static void cont__295_2(void);
static void cont__296_1(void);
static void cont__297_1(void);
static void cont__297_2(void);
static void cont__298_1(void);
static void cont__298_2(void);
static void cont__298_3(void);
static void cont__298_4(void);
static void cont__298_5(void);
static void cont__298_6(void);
static void cont__298_7(void);
static void cont__298_8(void);
static void cont__298_9(void);
static void cont__298_10(void);
static void cont__298_11(void);
static void cont__298_12(void);
static void cont__299_1(void);
static void cont__300_1(void);
static void cont__300_2(void);
static NODE *string__2d7981f4e6882ba7;
static void cont__300_4(void);
static void cont__301_1(void);
static void cont__302_1(void);
static void cont__302_2(void);
static NODE *string__2d7981f4e6882baa;
static void cont__302_4(void);
static void cont__303_1(void);
static void cont__303_2(void);
static void cont__303_3(void);
static void cont__304_1(void);
static void cont__304_2(void);
static NODE *string__2d7981f4e6882bbd;
static void cont__304_4(void);
static void cont__305_1(void);
static void cont__305_2(void);
static void cont__305_3(void);
static void cont__305_4(void);
static void cont__306_1(void);
static NODE *func__306_2;
static void entry__306_2(void);
static FRAME_INFO frame__306_2 = {1, {"node"}};
static void cont__306_3(void);
static void cont__306_4(void);
static void cont__306_5(void);
static void cont__306_6(void);
static NODE *func__307_1;
static void entry__307_1(void);
static FRAME_INFO frame__307_1 = {1, {"node"}};
static void cont__307_2(void);
static void cont__307_3(void);
static void cont__308_1(void);
static NODE *func__308_2;
static void entry__308_2(void);
static FRAME_INFO frame__308_2 = {3, {"node", "stream", "chr"}};
static void cont__308_3(void);
static void cont__308_4(void);
static void cont__308_5(void);
static NODE *func__308_6;
static void entry__308_6(void);
static FRAME_INFO frame__308_6 = {1, {"stream"}};
static NODE *string__dea962eab6ac8f23;
static void cont__308_8(void);
static void cont__308_9(void);
static void cont__308_10(void);
static void cont__309_1(void);
static void cont__309_2(void);
static void cont__309_3(void);
static void cont__309_4(void);
static void cont__309_5(void);
static void cont__309_6(void);
static void cont__309_7(void);
static void cont__309_8(void);
static void cont__309_9(void);
static NODE *func__309_10;
static void entry__309_10(void);
static FRAME_INFO frame__309_10 = {1, {"node"}};
static void cont__309_11(void);
static void cont__309_12(void);
static void cont__309_13(void);
static void cont__309_14(void);
static void cont__309_15(void);
static NODE *string__4313674f4741806a;
static void cont__310_2(void);
static void cont__310_3(void);
static void cont__311_1(void);
static void cont__311_2(void);
static void cont__312_1(void);
static void cont__312_2(void);
static void cont__312_3(void);
static NODE *func__313_1;
static void entry__313_1(void);
static FRAME_INFO frame__313_1 = {1, {"node"}};
static void cont__313_2(void);
static void cont__313_3(void);
static void cont__313_4(void);
static void cont__313_5(void);
static void cont__313_6(void);
static NODE *string__2d7981f4e5082bfe;
static void cont__313_8(void);
static NODE *func__314_1;
static void entry__314_1(void);
static FRAME_INFO frame__314_1 = {1, {"node"}};
static void cont__314_2(void);
static void cont__314_3(void);
static void cont__314_4(void);
static NODE *func__314_5;
static void entry__314_5(void);
static FRAME_INFO frame__314_5 = {1, {"node"}};
static void cont__314_6(void);
static void cont__314_7(void);
static void cont__314_8(void);
static void cont__314_9(void);
static void cont__314_10(void);
static void cont__314_11(void);
static void cont__314_12(void);
static NODE *string__2d7981f4e5082bed;
static void cont__314_14(void);
static NODE *func__315_1;
static void entry__315_1(void);
static FRAME_INFO frame__315_1 = {1, {"node"}};
static void cont__315_2(void);
static void cont__315_3(void);
static void cont__315_4(void);
static NODE *func__315_5;
static void entry__315_5(void);
static FRAME_INFO frame__315_5 = {1, {"node"}};
static void cont__315_6(void);
static void cont__315_7(void);
static void cont__315_8(void);
static NODE *func__315_9;
static void entry__315_9(void);
static FRAME_INFO frame__315_9 = {1, {"node"}};
static void cont__315_10(void);
static void cont__315_11(void);
static void cont__315_12(void);
static NODE *string__7c1f540901cb12b0;
static void cont__315_14(void);
static void cont__315_15(void);
static void cont__315_16(void);
static void cont__315_17(void);
static void cont__315_18(void);
static void cont__315_19(void);
static void cont__315_20(void);
static void cont__316_1(void);
static void cont__316_2(void);
static void cont__316_3(void);
static void cont__316_4(void);
static void cont__316_5(void);
static void cont__316_6(void);
static void cont__316_7(void);
static void cont__316_8(void);
static void cont__317_1(void);
static void cont__317_2(void);
static void cont__317_3(void);
static void cont__317_4(void);
static void cont__317_5(void);
static void cont__317_6(void);
static void cont__317_7(void);
static NODE *func__318_1;
static void entry__318_1(void);
static FRAME_INFO frame__318_1 = {1, {"node"}};
static void cont__318_2(void);
static void cont__318_3(void);
static void cont__318_4(void);
static void cont__318_5(void);
static void cont__319_1(void);
static void cont__319_2(void);
static void cont__319_3(void);
static void cont__319_4(void);
static void cont__319_5(void);
static void cont__319_6(void);
static void cont__319_7(void);
static void cont__319_8(void);
static void cont__320_1(void);
static void cont__320_2(void);
static void cont__320_3(void);
static NODE *string__55df65a142fc9536;
static void cont__321_2(void);
static void cont__321_3(void);
static void cont__321_4(void);
static void cont__321_5(void);
static void cont__321_6(void);
static NODE *func__322_1;
static void entry__322_1(void);
static FRAME_INFO frame__322_1 = {1, {"node"}};
static NODE *string__64d512703527e2ab;
static void cont__322_3(void);
static NODE *string__2a0aedcb5dc87d5c;
static void cont__322_5(void);
static void cont__322_6(void);
static void cont__322_7(void);
static void cont__322_8(void);
static void cont__322_9(void);
static void cont__322_10(void);
static NODE *string__2d7981f4e6602be8;
static void cont__322_12(void);
static NODE *func__323_1;
static void entry__323_1(void);
static FRAME_INFO frame__323_1 = {1, {"node"}};
static void cont__323_2(void);
static void cont__323_3(void);
static void cont__323_4(void);
static void cont__323_5(void);
static void cont__323_6(void);
static void cont__324_1(void);
static void cont__325_1(void);
static void cont__325_2(void);
static void cont__325_3(void);
static void cont__326_1(void);
static void cont__327_1(void);
static void cont__327_2(void);
static void cont__328_1(void);
static void cont__328_2(void);
static void cont__329_1(void);
static void cont__329_2(void);
static void cont__329_3(void);
static void cont__330_1(void);
static NODE *func__330_2;
static void entry__330_2(void);
static FRAME_INFO frame__330_2 = {3, {"node", "operator_precedence", "lowest_precedence"}};
static void cont__330_3(void);
static void cont__330_4(void);
static void cont__330_5(void);
static void cont__330_6(void);
static void cont__330_7(void);
static void cont__330_8(void);
static NODE *func__330_9;
static void entry__330_9(void);
static FRAME_INFO frame__330_9 = {2, {"operator_precedence", "lowest_precedence"}};
static void cont__330_10(void);
static void cont__330_11(void);
static NODE *func__330_12;
static void entry__330_12(void);
static FRAME_INFO frame__330_12 = {2, {"node", "operator_precedence"}};
static void cont__330_13(void);
static void cont__330_14(void);
static void cont__330_15(void);
static NODE *func__331_1;
static void entry__331_1(void);
static FRAME_INFO frame__331_1 = {4, {"node", "parent", "arguments", "n"}};
static void cont__331_2(void);
static void cont__331_3(void);
static void cont__331_4(void);
static void cont__331_5(void);
static NODE *func__331_6;
static void entry__331_6(void);
static FRAME_INFO frame__331_6 = {2, {"node", "arguments"}};
static void cont__331_7(void);
static NODE *func__331_8;
static void entry__331_8(void);
static FRAME_INFO frame__331_8 = {7, {"node", "arguments", "n", "operators", "operand_stack", "operator_stack", "update_stack"}};
static NODE *func__331_9;
static void entry__331_9(void);
static FRAME_INFO frame__331_9 = {5, {"right", "next_operator", "operator_stack", "operand_stack", "next_prec"}};
static void cont__331_10(void);
static NODE *func__331_11;
static void entry__331_11(void);
static FRAME_INFO frame__331_11 = {1, {"next_operator"}};
static void cont__331_12(void);
static NODE *func__331_13;
static void entry__331_13(void);
static FRAME_INFO frame__331_13 = {0, {}};
static void cont__331_14(void);
static NODE *func__331_15;
static void entry__331_15(void);
static FRAME_INFO frame__331_15 = {5, {"break", "operator_stack", "next_prec", "operand_stack", "right"}};
static NODE *func__331_16;
static void entry__331_16(void);
static FRAME_INFO frame__331_16 = {10, {"operator_stack", "next_prec", "break", "operand_stack", "right", "operator", "prec", "functor", "left", "dummy"}};
static void cont__331_17(void);
static void cont__331_18(void);
static void cont__331_19(void);
static void cont__331_20(void);
static void cont__331_21(void);
static NODE *func__331_22;
static void entry__331_22(void);
static FRAME_INFO frame__331_22 = {1, {"prec"}};
static void cont__331_23(void);
static void cont__331_24(void);
static void cont__331_25(void);
static void cont__331_26(void);
static NODE *func__331_27;
static void entry__331_27(void);
static FRAME_INFO frame__331_27 = {1, {"operator"}};
static NODE *func__331_28;
static void entry__331_28(void);
static FRAME_INFO frame__331_28 = {1, {"operator"}};
static void cont__331_29(void);
static void cont__331_30(void);
static void cont__331_31(void);
static void cont__331_32(void);
static void cont__331_33(void);
static void cont__331_34(void);
static void cont__331_35(void);
static void cont__331_36(void);
static void cont__331_37(void);
static void cont__331_38(void);
static void cont__331_39(void);
static void cont__331_40(void);
static void cont__331_41(void);
static void cont__331_42(void);
static void cont__331_43(void);
static void cont__331_44(void);
static void cont__331_45(void);
static void cont__331_46(void);
static void cont__331_47(void);
static NODE *func__331_48;
static void entry__331_48(void);
static FRAME_INFO frame__331_48 = {5, {"i", "update_stack", "arguments", "n", "operators"}};
static void cont__331_49(void);
static void cont__331_50(void);
static NODE *func__331_51;
static void entry__331_51(void);
static FRAME_INFO frame__331_51 = {2, {"operators", "i"}};
static void cont__331_52(void);
static NODE *func__331_53;
static void entry__331_53(void);
static FRAME_INFO frame__331_53 = {0, {}};
static void cont__331_54(void);
static void cont__331_55(void);
static void cont__331_56(void);
static void cont__331_57(void);
static void cont__331_58(void);
static NODE *func__331_59;
static void entry__331_59(void);
static FRAME_INFO frame__331_59 = {2, {"node", "parent"}};
static void cont__331_60(void);
static void cont__331_61(void);
static void cont__331_62(void);
static void cont__331_63(void);
static void cont__332_1(void);
static void cont__332_2(void);
static void cont__332_3(void);
static void cont__332_4(void);
static void cont__332_5(void);
static void cont__332_6(void);
static void cont__332_7(void);
static void cont__332_8(void);
static void cont__332_9(void);
static void cont__332_10(void);
static void cont__333_1(void);
static NODE *string__395c5a51a203e553;
static void cont__333_3(void);
static void cont__334_1(void);
static void cont__334_2(void);
static void cont__335_1(void);
static void cont__335_2(void);
static void cont__335_3(void);
static void cont__335_4(void);
static void cont__335_5(void);
static void cont__335_6(void);
static void cont__335_7(void);
static void cont__335_8(void);
static void cont__335_9(void);
static void cont__335_10(void);
static void cont__335_11(void);
static void cont__335_12(void);
static void cont__335_13(void);
static void cont__336_1(void);
static void cont__336_2(void);
static void cont__337_1(void);
static NODE *string__2d7981f4e6282be1;
static void cont__337_3(void);
static void cont__338_1(void);
static void cont__338_2(void);
static void cont__339_1(void);
static NODE *string__2d7981f4e6202be0;
static void cont__339_3(void);
static NODE *func__340_1;
static void entry__340_1(void);
static FRAME_INFO frame__340_1 = {1, {"node"}};
static void cont__340_2(void);
static void cont__340_3(void);
static void cont__340_4(void);
static void cont__340_5(void);
static void cont__340_6(void);
static void cont__340_7(void);
static void cont__340_8(void);
static void cont__340_9(void);
static void cont__341_1(void);
static void cont__341_2(void);
static void cont__342_1(void);
static void cont__343_1(void);
static void cont__343_2(void);
static void cont__343_3(void);
static void cont__343_4(void);
static void cont__343_5(void);
static void cont__344_1(void);
static void cont__344_2(void);
static void cont__345_1(void);
static void cont__345_2(void);
static void cont__345_3(void);
static void cont__345_4(void);
static void cont__345_5(void);
static void cont__346_1(void);
static void cont__346_2(void);
static void cont__346_3(void);
static void cont__347_1(void);
static void cont__347_2(void);
static void cont__347_3(void);
static NODE *func__348_1;
static void entry__348_1(void);
static FRAME_INFO frame__348_1 = {1, {"node"}};
static void cont__348_2(void);
static void cont__348_3(void);
static void cont__348_4(void);
static void cont__348_5(void);
static void cont__348_6(void);
static void cont__348_7(void);
static NODE *func__349_1;
static void entry__349_1(void);
static FRAME_INFO frame__349_1 = {3, {"node", "argument", "expression"}};
static void cont__349_2(void);
static void cont__349_3(void);
static void cont__349_4(void);
static void cont__349_5(void);
static void cont__349_6(void);
static NODE *func__349_7;
static void entry__349_7(void);
static FRAME_INFO frame__349_7 = {1, {"expression"}};
static void cont__349_8(void);
static void cont__349_9(void);
static NODE *func__349_10;
static void entry__349_10(void);
static FRAME_INFO frame__349_10 = {3, {"node", "expression", "argument"}};
static void cont__349_11(void);
static void cont__349_12(void);
static void cont__349_13(void);
static void cont__349_14(void);
static void cont__349_15(void);
static void cont__349_16(void);
static void cont__349_17(void);
static void cont__349_18(void);
static void cont__350_1(void);
static void cont__350_2(void);
static void cont__350_3(void);
static void cont__350_4(void);
static void cont__350_5(void);
static void cont__350_6(void);
static void cont__350_7(void);
static void cont__351_1(void);
static void cont__351_2(void);
static void cont__351_3(void);
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
static void cont__351_14(void);
static void cont__351_15(void);
static void cont__351_16(void);
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
static void cont__352_16(void);
static void cont__352_17(void);
static void cont__352_18(void);
static void cont__352_19(void);
static void cont__353_1(void);
static void cont__354_1(void);
static void cont__354_2(void);
static void cont__354_3(void);
static void cont__355_1(void);
static void cont__355_2(void);
static void cont__356_1(void);
static void cont__356_2(void);
static void cont__356_3(void);
static void cont__356_4(void);
static void cont__356_5(void);
static void cont__356_6(void);
static void cont__356_7(void);
static void cont__356_8(void);
static void cont__356_9(void);
static void cont__356_10(void);
static void cont__357_1(void);
static void cont__357_2(void);
static void cont__357_3(void);
static void cont__357_4(void);
static void cont__357_5(void);
static void cont__357_6(void);
static void cont__357_7(void);
static void cont__357_8(void);
static void cont__357_9(void);
static void cont__357_10(void);
static void cont__357_11(void);
static void cont__357_12(void);
static void cont__357_13(void);
static void cont__357_14(void);
static void cont__358_1(void);
static void cont__358_2(void);
static void cont__358_3(void);
static NODE *func__359_1;
static void entry__359_1(void);
static FRAME_INFO frame__359_1 = {1, {"node"}};
static void cont__359_2(void);
static void cont__359_3(void);
static void cont__359_4(void);
static void cont__359_5(void);
static NODE *func__359_6;
static void entry__359_6(void);
static FRAME_INFO frame__359_6 = {5, {"node", "top_level_node", "top_level_arguments", "functor", "new_arguments"}};
static void cont__359_7(void);
static void cont__359_8(void);
static void cont__359_9(void);
static void cont__359_10(void);
static void cont__359_11(void);
static void cont__359_12(void);
static void cont__359_13(void);
static void cont__359_14(void);
static void cont__359_15(void);
static void cont__359_16(void);
static void cont__359_17(void);
static void cont__359_18(void);
static void cont__359_19(void);
static void cont__359_20(void);
static void cont__359_21(void);
static void cont__359_22(void);
static NODE *func__361_1;
static void entry__361_1(void);
static FRAME_INFO frame__361_1 = {1, {"node"}};
static void cont__361_2(void);
static void cont__361_3(void);
static NODE *func__361_4;
static void entry__361_4(void);
static FRAME_INFO frame__361_4 = {2, {"node", "n"}};
static void cont__361_5(void);
static void cont__361_6(void);
static void cont__361_7(void);
static NODE *func__361_8;
static void entry__361_8(void);
static FRAME_INFO frame__361_8 = {2, {"node", "n"}};
static void cont__361_9(void);
static void cont__361_10(void);
static void cont__361_11(void);
static void cont__361_12(void);
static void cont__361_13(void);
static void cont__361_14(void);
static void cont__361_15(void);
static void cont__361_16(void);
static void cont__361_17(void);
static void cont__361_18(void);
static void cont__361_19(void);
static void cont__361_20(void);
static void cont__361_21(void);
static void cont__361_22(void);
static void cont__361_23(void);
static void cont__362_1(void);
static void cont__362_2(void);
static void cont__363_1(void);
static void cont__363_2(void);
static void cont__363_3(void);
static void cont__363_4(void);
static void cont__364_1(void);
static void cont__364_2(void);
static NODE *func__364_3;
static void entry__364_3(void);
static FRAME_INFO frame__364_3 = {1, {"node"}};
static void cont__364_4(void);
static void cont__364_5(void);
static void cont__364_6(void);
static void cont__364_7(void);
static NODE *func__364_8;
static void entry__364_8(void);
static FRAME_INFO frame__364_8 = {4, {"node", "stream", "return", "arguments"}};
static void exit__364_8(void);
static void cont__364_9(void);
static void cont__364_10(void);
static void cont__364_11(void);
static NODE *func__364_12;
static void entry__364_12(void);
static FRAME_INFO frame__364_12 = {1, {"stream"}};
static NODE *string__733ccdbfc49ced05;
static void cont__364_14(void);
static void cont__364_15(void);
static void cont__364_16(void);
static NODE *func__364_17;
static void entry__364_17(void);
static FRAME_INFO frame__364_17 = {4, {"node", "arguments", "return", "functor"}};
static void cont__364_18(void);
static void cont__364_19(void);
static void cont__364_20(void);
static void cont__364_21(void);
static NODE *func__364_22;
static void entry__364_22(void);
static FRAME_INFO frame__364_22 = {4, {"node", "functor", "arguments", "return"}};
static NODE *func__364_23;
static void entry__364_23(void);
static FRAME_INFO frame__364_23 = {4, {"node", "functor", "arguments", "return"}};
static void cont__364_24(void);
static void cont__364_25(void);
static void cont__364_26(void);
static void cont__364_27(void);
static void cont__364_28(void);
static void cont__364_29(void);
static void cont__364_30(void);
static NODE *func__364_31;
static void entry__364_31(void);
static FRAME_INFO frame__364_31 = {4, {"node", "functor", "arguments", "return"}};
static NODE *func__364_32;
static void entry__364_32(void);
static FRAME_INFO frame__364_32 = {4, {"node", "functor", "arguments", "return"}};
static void cont__364_33(void);
static void cont__364_34(void);
static void cont__364_35(void);
static void cont__364_36(void);
static void cont__364_37(void);
static void cont__364_38(void);
static void cont__364_39(void);
static void cont__364_40(void);
static void cont__364_41(void);
static void cont__364_42(void);
static void cont__364_43(void);
static void cont__364_44(void);
static void cont__365_1(void);
static void cont__365_2(void);
static void cont__365_3(void);
static void cont__365_4(void);
static void cont__365_5(void);
static void cont__365_6(void);
static void cont__365_7(void);
static void cont__365_8(void);
static void cont__365_9(void);
static NODE *func__365_10;
static void entry__365_10(void);
static FRAME_INFO frame__365_10 = {1, {"node"}};
static void cont__365_11(void);
static void cont__365_12(void);
static void cont__365_13(void);
static void cont__365_14(void);
static void cont__365_15(void);
static void cont__365_16(void);
static void cont__365_17(void);
static void cont__365_18(void);
static void cont__365_19(void);
static void cont__365_20(void);
static void cont__365_21(void);
static void cont__365_22(void);
static void cont__365_23(void);
static void cont__365_24(void);
static void cont__365_25(void);
static void cont__365_26(void);
static void cont__365_27(void);
static void cont__365_28(void);
static void cont__365_29(void);
static void cont__365_30(void);
static void cont__366_1(void);
static void cont__366_2(void);
static void cont__366_3(void);
static void cont__366_4(void);
static void cont__366_5(void);
static void cont__366_6(void);
static void cont__366_7(void);
static void cont__366_8(void);
static void cont__366_9(void);
static void cont__366_10(void);
static void cont__367_1(void);
static void cont__367_2(void);
static void cont__367_3(void);
static void cont__367_4(void);
static void cont__368_1(void);
static void cont__368_2(void);
static void cont__368_3(void);
static void cont__368_4(void);
static void cont__369_1(void);
static void cont__369_2(void);
static void cont__369_3(void);
static void cont__369_4(void);
static void cont__369_5(void);
static void cont__369_6(void);
static void cont__369_7(void);
static void cont__369_8(void);
static void cont__370_1(void);
static void cont__370_2(void);
static void cont__370_3(void);
static void cont__370_4(void);
static void cont__370_5(void);
static void cont__370_6(void);
static void cont__370_7(void);
static void cont__370_8(void);
static void cont__370_9(void);
static void cont__370_10(void);
static void cont__370_11(void);
static void cont__370_12(void);
static void cont__370_13(void);
static void cont__370_14(void);
static void cont__371_1(void);
static void cont__371_2(void);
static void cont__371_3(void);
static void cont__371_4(void);
static void cont__371_5(void);
static void cont__371_6(void);
static void cont__371_7(void);
static void cont__371_8(void);
static NODE *func__372_1;
static void entry__372_1(void);
static FRAME_INFO frame__372_1 = {1, {"node"}};
static void cont__372_2(void);
static void cont__372_3(void);
static void cont__373_1(void);
static void cont__373_2(void);
static void cont__373_3(void);
static void cont__373_4(void);
static void cont__373_5(void);
static void cont__374_1(void);
static void cont__375_1(void);
static void cont__375_2(void);
static void cont__375_3(void);
static void cont__376_1(void);
static void cont__376_2(void);
static NODE *string__2d7981f4e6602bfb;
static void cont__376_4(void);
static void cont__377_1(void);
static void cont__377_2(void);
static void cont__377_3(void);
static void cont__378_1(void);
static void cont__378_2(void);
static void cont__378_3(void);
static void cont__378_4(void);
static void cont__378_5(void);
static void cont__378_6(void);
static void cont__378_7(void);
static void cont__378_8(void);
static void cont__378_9(void);
static void cont__378_10(void);
static void cont__378_11(void);
static void cont__379_1(void);
static void cont__379_2(void);
static void cont__379_3(void);
static void cont__379_4(void);
static void cont__379_5(void);
static void cont__379_6(void);
static void cont__379_7(void);
static void cont__379_8(void);
static void cont__379_9(void);
static void cont__379_10(void);
static void cont__379_11(void);
static void cont__379_12(void);
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
static NODE *string__5ed2969d8211684f;
static void cont__380_13(void);
static void cont__380_14(void);
static void cont__380_15(void);
static void cont__380_16(void);
static void cont__380_17(void);
static void cont__380_18(void);
static void cont__380_19(void);
static void cont__380_20(void);
static void cont__380_21(void);
static void cont__380_22(void);
static void cont__381_1(void);
static void cont__381_2(void);
static void cont__381_3(void);
static void cont__382_1(void);
static void cont__383_1(void);
static void cont__383_2(void);
static void cont__383_3(void);
static void cont__383_4(void);
static void cont__383_5(void);
static void cont__383_6(void);
static void cont__383_7(void);
static void cont__383_8(void);
static void cont__383_9(void);
static void cont__383_10(void);
static void cont__384_1(void);
static void cont__384_2(void);
static void cont__385_1(void);
static void cont__385_2(void);
static void cont__385_3(void);
static void cont__385_4(void);
static void cont__385_5(void);
static void cont__385_6(void);
static void cont__385_7(void);
static void cont__385_8(void);
static void cont__385_9(void);
static void cont__385_10(void);
static void cont__385_11(void);
static void cont__385_12(void);
static void cont__385_13(void);
static void cont__385_14(void);
static void cont__386_1(void);
static NODE *string__2d7981f4e6482bec;
static void cont__386_3(void);
static void cont__387_1(void);
static NODE *string__fa732415f216be5;
static void cont__387_3(void);
static void cont__388_1(void);
static void cont__388_2(void);
static void cont__388_3(void);
static void cont__389_1(void);
static void cont__389_2(void);
static void cont__389_3(void);
static void cont__389_4(void);
static NODE *func__389_5;
static void entry__389_5(void);
static FRAME_INFO frame__389_5 = {2, {"node", "destination"}};
static void cont__389_6(void);
static void cont__389_7(void);
static void cont__389_8(void);
static void cont__389_9(void);
static NODE *func__389_10;
static void entry__389_10(void);
static FRAME_INFO frame__389_10 = {1, {"node"}};
static NODE *string__b6a1aa36d1f3b32e;
static void cont__389_12(void);
static void cont__389_13(void);
static void cont__389_14(void);
static void cont__389_15(void);
static void cont__389_16(void);
static void cont__389_17(void);
static void cont__389_18(void);
static void cont__389_19(void);
static void cont__389_20(void);
static void cont__389_21(void);
static void cont__389_22(void);
static void cont__389_23(void);
static void cont__389_24(void);
static void cont__389_25(void);
static void cont__389_26(void);
static void cont__389_27(void);
static void cont__390_1(void);
static void cont__391_1(void);
static NODE *string__2d7981f4e6782bed;
static void cont__391_3(void);
static void cont__391_4(void);
static void cont__391_5(void);
static void cont__391_6(void);
static void cont__392_1(void);
static void cont__392_2(void);
static void cont__392_3(void);
static void cont__392_4(void);
static void cont__392_5(void);
static void cont__392_6(void);
static void cont__392_7(void);
static void cont__392_8(void);
static void cont__393_1(void);
static void cont__393_2(void);
static void cont__394_1(void);
static void cont__394_2(void);
static void cont__394_3(void);
static void cont__394_4(void);
static void cont__395_1(void);
static void cont__395_2(void);
static void cont__395_3(void);
static void cont__395_4(void);
static void cont__396_1(void);
static void cont__397_1(void);
static NODE *func__397_2;
static void entry__397_2(void);
static FRAME_INFO frame__397_2 = {1, {"node"}};
static void cont__397_3(void);
static void cont__397_4(void);
static NODE *func__397_5;
static void entry__397_5(void);
static FRAME_INFO frame__397_5 = {1, {"node"}};
static NODE *string__a6b4597d46108e45;
static void cont__397_7(void);
static void cont__397_8(void);
static void cont__397_9(void);
static void cont__397_10(void);
static void cont__397_11(void);
static void cont__398_1(void);
static void cont__398_2(void);
static void cont__398_3(void);
static void cont__398_4(void);
static void cont__398_5(void);
static void cont__398_6(void);
static void cont__398_7(void);
static void cont__398_8(void);
static void cont__398_9(void);
static void cont__399_1(void);
static NODE *string__2d7981f4e5f02b9a;
static void cont__399_3(void);
static void cont__399_4(void);
static void cont__399_5(void);
static void cont__399_6(void);
static void cont__399_7(void);
static void cont__399_8(void);
static void cont__400_1(void);
static void cont__400_2(void);
static void cont__400_3(void);
static void cont__401_1(void);
static void cont__401_2(void);
static void cont__401_3(void);
static NODE *string__74dcac9584a4c074;
static void cont__401_5(void);
static void cont__402_1(void);
static void cont__402_2(void);
static void cont__402_3(void);
static NODE *string__60ae90b5df87d5c;
static void cont__402_5(void);
static void cont__403_1(void);
static void cont__403_2(void);
static void cont__403_3(void);
static NODE *string__140aeb0b5d107d5d;
static void cont__403_5(void);
static void cont__404_1(void);
static void cont__404_2(void);
static void cont__404_3(void);
static NODE *string__1e0ae90b5d087d5c;
static void cont__404_5(void);
static void cont__405_1(void);
static void cont__405_2(void);
static void cont__405_3(void);
static NODE *string__1e0aea8b5d407d5c;
static void cont__405_5(void);
static NODE *string__9a4c0f9815d2209f;
static NODE *string__461f56c301b292bb;
static NODE *string__545aebc3eac0d03b;
static NODE *string__701f5702012bd2b9;
static void cont__406_5(void);
static void cont__406_6(void);
static void cont__406_7(void);
static void cont__406_8(void);
static NODE *string__4c5ae8c3ea492032;
static void cont__406_10(void);
static void cont__407_1(void);
static void cont__407_2(void);
static void cont__407_3(void);
static NODE *string__2a0aef0b5de07d5c;
static void cont__407_5(void);
static NODE *string__399cfc434d66f26;
static void cont__408_2(void);
static void cont__408_3(void);
static void cont__409_1(void);
static void cont__409_2(void);
static void cont__410_1(void);
static NODE *string__2d7981f4e6702bea;
static void cont__411_2(void);
static void cont__412_1(void);
static void cont__412_2(void);
static void cont__412_3(void);
static void cont__412_4(void);
static void cont__413_1(void);
static void cont__413_2(void);
static void cont__413_3(void);
static void cont__413_4(void);
static void cont__413_5(void);
static void cont__414_1(void);
static void cont__414_2(void);
static void cont__414_3(void);
static void cont__414_4(void);
static void cont__414_5(void);
static void cont__414_6(void);
static void cont__414_7(void);
static void cont__414_8(void);
static void cont__414_9(void);
static void cont__414_10(void);
static void cont__415_1(void);
static void cont__415_2(void);
static void cont__415_3(void);
static NODE *string__227de92deba39b6b;
static void cont__416_2(void);
static void cont__416_3(void);
static void cont__416_4(void);
static void cont__416_5(void);
static void cont__416_6(void);
void run__parser(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__original_remark_lines_of, NULL, 1154, 1154, 2, 25},
  {run__parser, NULL, 204, 204, 5, 12},
  {cont__236_2, NULL, 205, 205, 5, 12},
  {cont__236_4, NULL, 206, 206, 5, 12},
  {cont__236_6, NULL, 207, 207, 5, 12},
  {cont__236_8, NULL, 208, 208, 5, 13},
  {cont__236_10, NULL, 209, 209, 5, 13},
  {cont__236_12, NULL, 210, 210, 5, 12},
  {cont__236_14, NULL, 211, 211, 5, 12},
  {cont__236_15, NULL, 212, 212, 5, 11},
  {cont__236_17, NULL, 213, 213, 5, 12},
  {cont__236_19, NULL, 214, 214, 5, 11},
  {cont__236_21, NULL, 215, 215, 5, 12},
  {cont__236_23, NULL, 216, 216, 5, 11},
  {cont__236_25, NULL, 217, 217, 5, 12},
  {cont__236_27, NULL, 218, 218, 5, 12},
  {cont__236_29, NULL, 219, 219, 5, 12},
  {cont__236_31, NULL, 220, 220, 5, 12},
  {cont__236_33, NULL, 221, 221, 5, 12},
  {cont__236_35, NULL, 222, 222, 5, 11},
  {cont__236_37, NULL, 223, 223, 5, 11},
  {cont__236_39, NULL, 202, 223, 1, 12},
  {cont__236_40, NULL, 249, 255, 1, 15},
  {cont__246_5, NULL, 257, 257, 10, 29},
  {cont__247_1, NULL, 257, 257, 1, 50},
  {cont__247_2, NULL, 258, 258, 9, 34},
  {cont__248_1, NULL, 258, 258, 1, 61},
  {cont__248_2, NULL, 259, 259, 10, 36},
  {cont__249_1, NULL, 259, 259, 1, 64},
  {cont__249_2, NULL, 260, 260, 10, 25},
  {cont__250_1, NULL, 260, 260, 1, 42},
  {cont__250_2, NULL, 268, 277, 1, 49},
  {cont__252_3, NULL, 279, 282, 1, 35},
  {cont__253_2, NULL, 290, 290, 1, 28},
  {cont__256_1, NULL, 291, 291, 34, 49},
  {cont__257_1, NULL, 291, 291, 1, 50},
  {cont__257_2, NULL, 292, 292, 1, 23},
  {cont__258_1, NULL, 293, 293, 1, 45},
  {cont__259_1, NULL, 295, 303, 1, 42},
  {cont__260_3, NULL, 305, 313, 1, 42},
  {cont__261_4, NULL, 315, 323, 1, 42},
  {cont__262_4, NULL, 325, 332, 1, 47},
  {cont__263_3, NULL, 336, 336, 5, 24},
  {cont__264_1, NULL, 338, 338, 5, 25},
  {cont__264_2, NULL, 342, 344, 9, 43},
  {cont__264_5, NULL, 345, 345, 9, 29},
  {cont__264_6, NULL, 340, 345, 7, 28},
  {cont__264_8, NULL, 339, 345, 5, 29},
  {cont__264_9, NULL, 334, 346, 1, 23},
  {cont__264_10, NULL, 350, 350, 5, 24},
  {cont__265_1, NULL, 352, 352, 5, 22},
  {cont__265_2, NULL, 353, 353, 5, 25},
  {cont__265_3, NULL, 357, 361, 9, 43},
  {cont__265_10, NULL, 362, 362, 9, 29},
  {cont__265_11, NULL, 355, 362, 7, 28},
  {cont__265_12, NULL, 354, 362, 5, 29},
  {cont__265_13, NULL, 348, 363, 1, 23},
  {cont__265_14, NULL, 367, 367, 5, 24},
  {cont__266_1, NULL, 369, 369, 5, 30},
  {cont__266_2, NULL, 370, 370, 5, 16},
  {cont__266_3, NULL, 371, 371, 5, 25},
  {cont__266_4, NULL, 365, 371, 1, 26},
  {cont__266_5, NULL, 376, 376, 11, 24},
  {cont__267_2, NULL, 376, 376, 38, 46},
  {cont__267_3, NULL, 376, 376, 33, 47},
  {cont__267_4, NULL, 376, 376, 1, 47},
  {cont__267_5, NULL, 381, 381, 5, 33},
  {cont__268_1, NULL, 384, 384, 5, 39},
  {cont__268_2, NULL, 387, 393, 5, 40},
  {cont__268_13, NULL, 378, 393, 1, 43},
  {cont__268_15, NULL, 399, 399, 5, 35},
  {cont__269_1, NULL, 400, 400, 5, 30},
  {cont__269_2, NULL, 403, 403, 9, 27},
  {cont__269_3, NULL, 404, 406, 9, 54},
  {cont__269_6, NULL, 407, 407, 9, 34},
  {cont__269_7, NULL, 402, 407, 7, 33},
  {cont__269_8, NULL, 401, 407, 5, 34},
  {cont__269_9, NULL, 409, 423, 5, 49},
  {cont__269_30, NULL, 395, 423, 1, 52},
  {cont__269_32, NULL, 429, 429, 5, 31},
  {cont__270_1, NULL, 430, 430, 5, 30},
  {cont__270_2, NULL, 432, 438, 5, 40},
  {cont__270_11, NULL, 425, 438, 1, 43},
  {cont__270_13, NULL, 440, 440, 16, 40},
  {cont__271_1, NULL, 440, 440, 1, 41},
  {cont__271_2, NULL, 441, 441, 26, 36},
  {cont__272_2, NULL, 441, 441, 13, 37},
  {cont__272_3, NULL, 441, 441, 55, 67},
  {cont__272_4, NULL, 441, 441, 50, 68},
  {cont__272_5, NULL, 441, 441, 1, 68},
  {cont__272_6, NULL, 447, 447, 5, 33},
  {cont__273_1, NULL, 448, 448, 5, 41},
  {cont__273_2, NULL, 450, 456, 5, 38},
  {cont__273_12, NULL, 443, 456, 1, 41},
  {cont__273_14, NULL, 462, 462, 5, 30},
  {cont__274_1, NULL, 463, 463, 5, 41},
  {cont__274_2, NULL, 465, 471, 5, 40},
  {cont__274_12, NULL, 458, 471, 1, 43},
  {cont__274_14, NULL, 473, 473, 12, 44},
  {cont__275_1, NULL, 473, 473, 1, 45},
  {cont__275_2, NULL, 474, 474, 24, 34},
  {cont__276_1, NULL, 474, 474, 11, 35},
  {cont__276_2, NULL, 474, 474, 49, 57},
  {cont__276_3, NULL, 474, 474, 44, 58},
  {cont__276_4, NULL, 474, 474, 1, 58},
  {cont__276_5, NULL, 480, 480, 5, 30},
  {cont__277_1, NULL, 481, 481, 5, 39},
  {cont__277_2, NULL, 483, 489, 5, 38},
  {cont__277_11, NULL, 476, 489, 1, 41},
  {cont__277_13, NULL, 493, 493, 5, 50},
  {cont__278_1, NULL, 494, 494, 56, 77},
  {cont__278_2, NULL, 494, 494, 38, 77},
  {cont__278_3, NULL, 494, 494, 14, 78},
  {cont__278_4, NULL, 494, 494, 5, 79},
  {cont__278_5, NULL, 491, 494, 1, 80},
  {cont__278_6, NULL, 499, 499, 44, 68},
  {cont__279_1, NULL, 499, 499, 1, 69},
  {cont__279_2, NULL, 504, 504, 22, 53},
  {cont__280_1, NULL, 504, 504, 56, 77},
  {cont__280_2, NULL, 504, 504, 14, 77},
  {cont__280_3, NULL, 504, 504, 5, 78},
  {cont__280_4, NULL, 501, 504, 1, 79},
  {cont__280_5, NULL, 506, 506, 35, 60},
  {cont__281_1, NULL, 506, 506, 1, 74},
  {cont__281_2, NULL, 508, 508, 1, 67},
  {cont__282_1, NULL, 509, 509, 1, 29},
  {cont__283_1, NULL, 514, 523, 5, 43},
  {cont__284_23, NULL, 511, 523, 1, 46},
  {cont__284_24, NULL, 525, 525, 27, 65},
  {cont__285_1, NULL, 525, 525, 1, 66},
  {cont__285_2, NULL, 533, 541, 7, 48},
  {cont__286_22, NULL, 529, 541, 5, 49},
  {cont__286_23, NULL, 527, 541, 1, 52},
  {cont__286_24, NULL, 547, 553, 5, 46},
  {cont__287_22, NULL, 543, 553, 1, 49},
  {cont__287_23, NULL, 555, 555, 1, 60},
  {cont__288_1, NULL, 556, 556, 1, 32},
  {cont__289_1, NULL, 564, 570, 5, 58},
  {cont__290_4, NULL, 571, 571, 21, 63},
  {cont__290_5, NULL, 571, 571, 12, 64},
  {cont__290_6, NULL, 571, 571, 5, 65},
  {cont__290_7, NULL, 572, 572, 5, 15},
  {cont__290_8, NULL, 561, 573, 1, 23},
  {cont__290_9, NULL, 575, 583, 1, 58},
  {cont__291_5, NULL, 589, 589, 5, 31},
  {cont__292_1, NULL, 585, 590, 1, 23},
  {cont__292_2, NULL, 596, 596, 5, 40},
  {cont__293_1, NULL, 592, 597, 1, 23},
  {cont__293_2, NULL, 599, 599, 18, 52},
  {cont__294_1, NULL, 599, 599, 1, 53},
  {cont__294_2, NULL, 600, 600, 29, 62},
  {cont__295_1, NULL, 600, 600, 1, 63},
  {cont__295_2, NULL, 601, 601, 1, 51},
  {cont__296_1, NULL, 604, 604, 15, 46},
  {cont__297_1, NULL, 603, 604, 1, 69},
  {cont__297_2, NULL, 608, 608, 17, 27},
  {cont__298_1, NULL, 608, 608, 5, 37},
  {cont__298_2, NULL, 609, 609, 19, 29},
  {cont__298_3, NULL, 609, 609, 14, 29},
  {cont__298_4, NULL, 609, 609, 5, 30},
  {cont__298_5, NULL, 610, 610, 14, 25},
  {cont__298_6, NULL, 610, 610, 37, 48},
  {cont__298_7, NULL, 610, 610, 28, 49},
  {cont__298_8, NULL, 610, 610, 52, 62},
  {cont__298_9, NULL, 610, 610, 14, 62},
  {cont__298_10, NULL, 610, 610, 5, 63},
  {cont__298_11, NULL, 606, 610, 1, 64},
  {cont__298_12, NULL, 612, 612, 1, 26},
  {cont__299_1, NULL, 613, 613, 34, 51},
  {cont__300_1, NULL, 613, 613, 22, 61},
  {cont__300_2, NULL, 613, 613, 1, 61},
  {cont__300_4, NULL, 614, 614, 1, 23},
  {cont__301_1, NULL, 615, 615, 33, 49},
  {cont__302_1, NULL, 615, 615, 21, 59},
  {cont__302_2, NULL, 615, 615, 1, 59},
  {cont__302_4, NULL, 616, 616, 22, 31},
  {cont__303_1, NULL, 616, 616, 33, 42},
  {cont__303_2, NULL, 616, 616, 1, 43},
  {cont__303_3, NULL, 617, 617, 31, 45},
  {cont__304_1, NULL, 617, 617, 19, 55},
  {cont__304_2, NULL, 617, 617, 1, 55},
  {cont__304_4, NULL, 621, 621, 5, 29},
  {cont__305_1, NULL, 625, 625, 7, 63},
  {cont__305_2, NULL, 623, 625, 5, 62},
  {cont__305_3, NULL, 619, 626, 1, 23},
  {cont__305_4, NULL, 630, 630, 5, 47},
  {cont__306_1, NULL, 631, 633, 5, 52},
  {cont__306_5, NULL, 628, 633, 1, 55},
  {cont__306_6, NULL, 638, 640, 5, 33},
  {cont__307_2, NULL, 635, 640, 1, 36},
  {cont__307_3, NULL, 644, 644, 5, 32},
  {cont__308_1, NULL, 646, 654, 5, 32},
  {cont__308_9, NULL, 642, 654, 1, 35},
  {cont__308_10, NULL, 661, 661, 15, 32},
  {cont__309_1, NULL, 661, 661, 9, 32},
  {cont__309_2, NULL, 662, 662, 15, 31},
  {cont__309_3, NULL, 662, 662, 9, 31},
  {cont__309_4, NULL, 663, 663, 15, 29},
  {cont__309_5, NULL, 663, 663, 9, 29},
  {cont__309_6, NULL, 664, 664, 9, 19},
  {cont__309_7, NULL, 660, 664, 7, 18},
  {cont__309_8, NULL, 658, 664, 5, 19},
  {cont__309_9, NULL, 666, 670, 5, 39},
  {cont__309_14, NULL, 656, 670, 1, 42},
  {cont__309_15, NULL, 677, 677, 5, 45},
  {cont__310_2, NULL, 672, 677, 1, 46},
  {cont__310_3, NULL, 679, 679, 23, 45},
  {cont__311_1, NULL, 679, 679, 1, 63},
  {cont__311_2, NULL, 684, 684, 5, 31},
  {cont__312_1, NULL, 687, 687, 5, 20},
  {cont__312_2, NULL, 681, 688, 1, 23},
  {cont__312_3, NULL, 695, 697, 7, 55},
  {cont__313_5, NULL, 693, 697, 5, 56},
  {cont__313_6, NULL, 690, 697, 1, 59},
  {cont__313_8, NULL, 702, 706, 5, 30},
  {cont__314_9, NULL, 707, 707, 17, 42},
  {cont__314_10, NULL, 707, 707, 5, 61},
  {cont__314_11, NULL, 708, 708, 5, 15},
  {cont__314_12, NULL, 699, 708, 1, 16},
  {cont__314_14, NULL, 710, 723, 1, 55},
  {cont__315_20, NULL, 730, 730, 5, 34},
  {cont__316_1, NULL, 731, 731, 5, 28},
  {cont__316_2, NULL, 733, 733, 10, 34},
  {cont__316_3, NULL, 733, 733, 37, 74},
  {cont__316_4, NULL, 733, 733, 10, 74},
  {cont__316_5, NULL, 733, 733, 5, 75},
  {cont__316_6, NULL, 734, 734, 5, 20},
  {cont__316_7, NULL, 725, 736, 1, 21},
  {cont__316_8, NULL, 741, 741, 19, 31},
  {cont__317_1, NULL, 741, 741, 7, 32},
  {cont__317_2, NULL, 742, 742, 7, 32},
  {cont__317_3, NULL, 743, 743, 7, 35},
  {cont__317_4, NULL, 744, 744, 7, 35},
  {cont__317_5, NULL, 740, 744, 5, 34},
  {cont__317_6, NULL, 738, 744, 1, 37},
  {cont__317_7, NULL, 746, 749, 1, 62},
  {cont__318_5, NULL, 754, 754, 5, 31},
  {cont__319_1, NULL, 758, 758, 10, 43},
  {cont__319_2, NULL, 758, 758, 5, 44},
  {cont__319_3, NULL, 759, 759, 9, 21},
  {cont__319_4, NULL, 759, 759, 23, 44},
  {cont__319_5, NULL, 759, 759, 23, 58},
  {cont__319_6, NULL, 759, 759, 5, 59},
  {cont__319_7, NULL, 751, 761, 1, 21},
  {cont__319_8, NULL, 763, 763, 19, 41},
  {cont__320_1, NULL, 763, 763, 44, 64},
  {cont__320_2, NULL, 763, 763, 1, 64},
  {cont__320_3, NULL, 768, 768, 32, 66},
  {cont__321_2, NULL, 768, 768, 12, 67},
  {cont__321_3, NULL, 768, 768, 5, 68},
  {cont__321_4, NULL, 769, 769, 5, 15},
  {cont__321_5, NULL, 765, 769, 1, 16},
  {cont__321_6, NULL, 775, 782, 5, 60},
  {cont__322_10, NULL, 771, 783, 1, 23},
  {cont__322_12, NULL, 790, 797, 5, 58},
  {cont__323_5, NULL, 785, 798, 1, 23},
  {cont__323_6, NULL, 800, 808, 1, 13},
  {cont__324_1, NULL, 810, 810, 58, 79},
  {cont__325_1, NULL, 810, 810, 42, 79},
  {cont__325_2, NULL, 810, 810, 1, 80},
  {cont__325_3, NULL, 812, 832, 1, 9},
  {cont__326_1, NULL, 835, 835, 18, 66},
  {cont__327_1, NULL, 834, 835, 1, 67},
  {cont__327_2, NULL, 837, 837, 17, 47},
  {cont__328_1, NULL, 837, 837, 1, 66},
  {cont__328_2, NULL, 843, 843, 5, 39},
  {cont__329_1, NULL, 845, 845, 5, 29},
  {cont__329_2, NULL, 839, 845, 1, 30},
  {cont__329_3, NULL, 849, 849, 5, 56},
  {cont__330_1, NULL, 850, 859, 5, 60},
  {cont__330_14, NULL, 847, 859, 1, 63},
  {cont__330_15, NULL, 861, 911, 1, 70},
  {cont__331_63, NULL, 915, 915, 5, 24},
  {cont__332_1, NULL, 916, 916, 5, 27},
  {cont__332_2, NULL, 917, 917, 26, 48},
  {cont__332_3, NULL, 917, 917, 10, 48},
  {cont__332_4, NULL, 917, 917, 5, 49},
  {cont__332_5, NULL, 919, 919, 22, 52},
  {cont__332_6, NULL, 919, 919, 7, 53},
  {cont__332_7, NULL, 919, 919, 7, 74},
  {cont__332_8, NULL, 918, 919, 5, 73},
  {cont__332_9, NULL, 913, 920, 1, 22},
  {cont__332_10, NULL, 922, 922, 26, 62},
  {cont__333_1, NULL, 922, 922, 1, 76},
  {cont__333_3, NULL, 925, 925, 15, 63},
  {cont__334_1, NULL, 924, 925, 1, 63},
  {cont__334_2, NULL, 935, 935, 13, 55},
  {cont__335_1, NULL, 936, 936, 13, 50},
  {cont__335_2, NULL, 933, 936, 11, 49},
  {cont__335_3, NULL, 939, 939, 13, 28},
  {cont__335_4, NULL, 940, 940, 13, 52},
  {cont__335_5, NULL, 937, 940, 11, 51},
  {cont__335_6, NULL, 943, 943, 13, 52},
  {cont__335_7, NULL, 944, 944, 13, 50},
  {cont__335_8, NULL, 941, 944, 11, 49},
  {cont__335_9, NULL, 932, 944, 9, 50},
  {cont__335_10, NULL, 931, 944, 7, 51},
  {cont__335_11, NULL, 930, 944, 5, 52},
  {cont__335_12, NULL, 927, 944, 1, 55},
  {cont__335_13, NULL, 947, 947, 8, 37},
  {cont__336_1, NULL, 946, 947, 1, 68},
  {cont__336_2, NULL, 949, 949, 28, 56},
  {cont__337_1, NULL, 949, 949, 1, 74},
  {cont__337_3, NULL, 950, 950, 29, 59},
  {cont__338_1, NULL, 950, 950, 1, 77},
  {cont__338_2, NULL, 951, 951, 29, 58},
  {cont__339_1, NULL, 951, 951, 1, 76},
  {cont__339_3, NULL, 956, 964, 5, 58},
  {cont__340_5, NULL, 965, 965, 9, 24},
  {cont__340_6, NULL, 965, 965, 26, 61},
  {cont__340_7, NULL, 965, 965, 5, 62},
  {cont__340_8, NULL, 953, 966, 1, 23},
  {cont__340_9, NULL, 968, 968, 54, 80},
  {cont__341_1, NULL, 968, 968, 1, 80},
  {cont__341_2, NULL, 970, 976, 1, 11},
  {cont__342_1, NULL, 981, 981, 5, 24},
  {cont__343_1, NULL, 982, 982, 46, 69},
  {cont__343_2, NULL, 982, 982, 27, 70},
  {cont__343_3, NULL, 982, 982, 5, 71},
  {cont__343_4, NULL, 978, 982, 1, 72},
  {cont__343_5, NULL, 984, 984, 32, 51},
  {cont__344_1, NULL, 984, 984, 1, 52},
  {cont__344_2, NULL, 988, 988, 10, 44},
  {cont__345_1, NULL, 988, 988, 5, 44},
  {cont__345_2, NULL, 989, 989, 10, 44},
  {cont__345_3, NULL, 989, 989, 5, 44},
  {cont__345_4, NULL, 986, 989, 1, 45},
  {cont__345_5, NULL, 991, 991, 53, 71},
  {cont__346_1, NULL, 991, 991, 40, 71},
  {cont__346_2, NULL, 991, 991, 1, 72},
  {cont__346_3, NULL, 995, 995, 50, 68},
  {cont__347_1, NULL, 995, 995, 5, 68},
  {cont__347_2, NULL, 993, 995, 1, 69},
  {cont__347_3, NULL, 997, 1005, 1, 65},
  {cont__348_7, NULL, 1007, 1022, 1, 68},
  {cont__349_18, NULL, 1026, 1026, 32, 50},
  {cont__350_1, NULL, 1026, 1026, 20, 50},
  {cont__350_2, NULL, 1026, 1026, 5, 51},
  {cont__350_3, NULL, 1028, 1028, 5, 38},
  {cont__350_4, NULL, 1029, 1029, 5, 30},
  {cont__350_5, NULL, 1029, 1029, 5, 49},
  {cont__350_6, NULL, 1024, 1029, 1, 50},
  {cont__350_7, NULL, 1037, 1037, 11, 40},
  {cont__351_1, NULL, 1038, 1038, 11, 49},
  {cont__351_2, NULL, 1036, 1040, 9, 23},
  {cont__351_3, NULL, 1035, 1040, 7, 24},
  {cont__351_4, NULL, 1033, 1040, 5, 25},
  {cont__351_5, NULL, 1043, 1043, 7, 22},
  {cont__351_6, NULL, 1045, 1045, 9, 41},
  {cont__351_7, NULL, 1045, 1045, 9, 68},
  {cont__351_8, NULL, 1044, 1045, 7, 67},
  {cont__351_9, NULL, 1041, 1045, 5, 68},
  {cont__351_10, NULL, 1050, 1050, 11, 43},
  {cont__351_11, NULL, 1051, 1051, 11, 49},
  {cont__351_12, NULL, 1049, 1053, 9, 23},
  {cont__351_13, NULL, 1048, 1053, 7, 24},
  {cont__351_14, NULL, 1046, 1053, 5, 25},
  {cont__351_15, NULL, 1031, 1053, 1, 28},
  {cont__351_16, NULL, 1057, 1057, 10, 32},
  {cont__352_1, NULL, 1057, 1057, 5, 33},
  {cont__352_2, NULL, 1063, 1063, 13, 42},
  {cont__352_3, NULL, 1064, 1064, 13, 51},
  {cont__352_4, NULL, 1062, 1065, 11, 32},
  {cont__352_5, NULL, 1061, 1065, 9, 33},
  {cont__352_6, NULL, 1059, 1065, 7, 34},
  {cont__352_7, NULL, 1068, 1068, 9, 24},
  {cont__352_8, NULL, 1069, 1069, 24, 56},
  {cont__352_9, NULL, 1069, 1069, 24, 79},
  {cont__352_10, NULL, 1069, 1069, 9, 80},
  {cont__352_11, NULL, 1066, 1069, 7, 79},
  {cont__352_12, NULL, 1074, 1074, 13, 45},
  {cont__352_13, NULL, 1075, 1075, 13, 51},
  {cont__352_14, NULL, 1073, 1076, 11, 32},
  {cont__352_15, NULL, 1072, 1076, 9, 33},
  {cont__352_16, NULL, 1070, 1076, 7, 34},
  {cont__352_17, NULL, 1058, 1076, 5, 35},
  {cont__352_18, NULL, 1055, 1076, 1, 38},
  {cont__352_19, NULL, 1078, 1079, 1, 60},
  {cont__353_1, NULL, 1082, 1082, 11, 53},
  {cont__354_1, NULL, 1082, 1082, 56, 77},
  {cont__354_2, NULL, 1081, 1082, 1, 77},
  {cont__354_3, NULL, 1085, 1085, 7, 51},
  {cont__355_1, NULL, 1084, 1085, 1, 72},
  {cont__355_2, NULL, 1092, 1092, 33, 68},
  {cont__356_1, NULL, 1092, 1092, 9, 69},
  {cont__356_2, NULL, 1090, 1092, 7, 68},
  {cont__356_3, NULL, 1098, 1098, 13, 25},
  {cont__356_4, NULL, 1100, 1100, 13, 34},
  {cont__356_5, NULL, 1096, 1100, 11, 33},
  {cont__356_6, NULL, 1095, 1100, 9, 34},
  {cont__356_7, NULL, 1093, 1100, 7, 35},
  {cont__356_8, NULL, 1089, 1100, 5, 36},
  {cont__356_9, NULL, 1087, 1100, 1, 39},
  {cont__356_10, NULL, 1106, 1106, 16, 41},
  {cont__357_1, NULL, 1106, 1106, 7, 42},
  {cont__357_2, NULL, 1107, 1107, 16, 50},
  {cont__357_3, NULL, 1107, 1107, 7, 51},
  {cont__357_4, NULL, 1104, 1107, 5, 50},
  {cont__357_5, NULL, 1110, 1110, 11, 30},
  {cont__357_6, NULL, 1110, 1110, 41, 75},
  {cont__357_7, NULL, 1110, 1110, 32, 76},
  {cont__357_8, NULL, 1110, 1110, 7, 77},
  {cont__357_9, NULL, 1108, 1110, 5, 76},
  {cont__357_10, NULL, 1111, 1111, 39, 73},
  {cont__357_11, NULL, 1111, 1111, 30, 74},
  {cont__357_12, NULL, 1111, 1111, 5, 75},
  {cont__357_13, NULL, 1102, 1111, 1, 76},
  {cont__357_14, NULL, 1115, 1115, 29, 51},
  {cont__358_1, NULL, 1115, 1115, 5, 75},
  {cont__358_2, NULL, 1113, 1116, 1, 22},
  {cont__358_3, NULL, 1122, 1124, 5, 41},
  {cont__359_2, NULL, 1125, 1125, 30, 72},
  {cont__359_3, NULL, 1125, 1125, 5, 73},
  {cont__359_4, NULL, 1127, 1127, 5, 26},
  {cont__359_5, NULL, 1128, 1152, 5, 54},
  {cont__359_21, NULL, 1118, 1152, 1, 57},
  {cont__359_22, NULL, 1160, 1163, 7, 42},
  {cont__361_3, NULL, 1165, 1172, 7, 50},
  {cont__361_19, NULL, 1173, 1173, 11, 61},
  {cont__361_20, NULL, 1173, 1173, 7, 70},
  {cont__361_21, NULL, 1158, 1173, 5, 69},
  {cont__361_22, NULL, 1156, 1174, 1, 29},
  {cont__361_23, NULL, 1177, 1177, 11, 23},
  {cont__362_1, NULL, 1176, 1177, 1, 57},
  {cont__362_2, NULL, 1180, 1180, 28, 77},
  {cont__363_1, NULL, 1180, 1180, 16, 78},
  {cont__363_2, NULL, 1180, 1180, 11, 78},
  {cont__363_3, NULL, 1179, 1180, 1, 79},
  {cont__363_4, NULL, 1184, 1184, 5, 29},
  {cont__364_1, NULL, 1186, 1186, 5, 42},
  {cont__364_2, NULL, 1187, 1193, 5, 58},
  {cont__364_6, NULL, 1197, 1197, 5, 26},
  {cont__364_7, NULL, 1198, 1226, 5, 63},
  {cont__364_43, NULL, 1182, 1226, 1, 66},
  {cont__364_44, NULL, 1232, 1232, 38, 72},
  {cont__365_1, NULL, 1232, 1232, 9, 72},
  {cont__365_2, NULL, 1231, 1232, 7, 71},
  {cont__365_3, NULL, 1238, 1238, 17, 43},
  {cont__365_4, NULL, 1238, 1238, 17, 66},
  {cont__365_5, NULL, 1240, 1240, 17, 38},
  {cont__365_6, NULL, 1241, 1241, 17, 25},
  {cont__365_7, NULL, 1237, 1241, 15, 24},
  {cont__365_8, NULL, 1236, 1241, 13, 25},
  {cont__365_9, NULL, 1242, 1250, 13, 64},
  {cont__365_18, NULL, 1235, 1251, 11, 33},
  {cont__365_19, NULL, 1254, 1254, 22, 52},
  {cont__365_20, NULL, 1254, 1254, 13, 53},
  {cont__365_21, NULL, 1252, 1254, 11, 52},
  {cont__365_22, NULL, 1234, 1254, 9, 53},
  {cont__365_23, NULL, 1233, 1254, 7, 54},
  {cont__365_24, NULL, 1230, 1254, 5, 55},
  {cont__365_25, NULL, 1255, 1255, 32, 66},
  {cont__365_26, NULL, 1255, 1255, 20, 66},
  {cont__365_27, NULL, 1255, 1255, 5, 67},
  {cont__365_28, NULL, 1256, 1256, 5, 41},
  {cont__365_29, NULL, 1228, 1256, 1, 42},
  {cont__365_30, NULL, 1260, 1260, 35, 70},
  {cont__366_1, NULL, 1260, 1260, 26, 71},
  {cont__366_2, NULL, 1260, 1260, 5, 71},
  {cont__366_3, NULL, 1262, 1262, 7, 46},
  {cont__366_4, NULL, 1263, 1263, 11, 30},
  {cont__366_5, NULL, 1263, 1263, 41, 75},
  {cont__366_6, NULL, 1263, 1263, 32, 76},
  {cont__366_7, NULL, 1263, 1263, 7, 77},
  {cont__366_8, NULL, 1261, 1263, 5, 76},
  {cont__366_9, NULL, 1258, 1263, 1, 79},
  {cont__366_10, NULL, 1267, 1267, 29, 63},
  {cont__367_1, NULL, 1267, 1267, 20, 64},
  {cont__367_2, NULL, 1267, 1267, 5, 64},
  {cont__367_3, NULL, 1265, 1268, 1, 25},
  {cont__367_4, NULL, 1272, 1272, 22, 56},
  {cont__368_1, NULL, 1272, 1272, 13, 57},
  {cont__368_2, NULL, 1272, 1272, 5, 57},
  {cont__368_3, NULL, 1270, 1273, 1, 25},
  {cont__368_4, NULL, 1277, 1277, 5, 54},
  {cont__369_1, NULL, 1278, 1278, 5, 34},
  {cont__369_2, NULL, 1282, 1282, 12, 27},
  {cont__369_3, NULL, 1282, 1282, 7, 28},
  {cont__369_4, NULL, 1283, 1283, 7, 48},
  {cont__369_5, NULL, 1284, 1284, 7, 28},
  {cont__369_6, NULL, 1279, 1284, 5, 27},
  {cont__369_7, NULL, 1275, 1284, 1, 30},
  {cont__369_8, NULL, 1291, 1291, 9, 37},
  {cont__370_1, NULL, 1292, 1292, 9, 49},
  {cont__370_2, NULL, 1289, 1292, 7, 48},
  {cont__370_3, NULL, 1295, 1295, 9, 37},
  {cont__370_4, NULL, 1296, 1296, 9, 50},
  {cont__370_5, NULL, 1293, 1296, 7, 49},
  {cont__370_6, NULL, 1299, 1299, 9, 37},
  {cont__370_7, NULL, 1300, 1300, 9, 53},
  {cont__370_8, NULL, 1297, 1300, 7, 52},
  {cont__370_9, NULL, 1301, 1301, 7, 36},
  {cont__370_10, NULL, 1301, 1301, 39, 79},
  {cont__370_11, NULL, 1301, 1301, 7, 79},
  {cont__370_12, NULL, 1288, 1301, 5, 78},
  {cont__370_13, NULL, 1286, 1301, 1, 81},
  {cont__370_14, NULL, 1308, 1308, 9, 27},
  {cont__371_1, NULL, 1309, 1309, 9, 43},
  {cont__371_2, NULL, 1310, 1310, 9, 41},
  {cont__371_3, NULL, 1307, 1310, 7, 40},
  {cont__371_4, NULL, 1311, 1311, 12, 56},
  {cont__371_5, NULL, 1311, 1311, 7, 56},
  {cont__371_6, NULL, 1305, 1311, 5, 55},
  {cont__371_7, NULL, 1303, 1311, 1, 58},
  {cont__371_8, NULL, 1316, 1318, 5, 30},
  {cont__372_2, NULL, 1313, 1318, 1, 33},
  {cont__372_3, NULL, 1324, 1324, 7, 26},
  {cont__373_1, NULL, 1326, 1326, 7, 24},
  {cont__373_2, NULL, 1327, 1327, 7, 27},
  {cont__373_3, NULL, 1323, 1328, 5, 23},
  {cont__373_4, NULL, 1320, 1328, 1, 26},
  {cont__373_5, NULL, 1330, 1330, 1, 68},
  {cont__374_1, NULL, 1333, 1333, 49, 71},
  {cont__375_1, NULL, 1333, 1333, 40, 72},
  {cont__375_2, NULL, 1332, 1333, 1, 72},
  {cont__375_3, NULL, 1339, 1339, 5, 34},
  {cont__376_1, NULL, 1340, 1340, 5, 55},
  {cont__376_2, NULL, 1335, 1341, 1, 19},
  {cont__376_4, NULL, 1344, 1344, 52, 74},
  {cont__377_1, NULL, 1344, 1344, 43, 75},
  {cont__377_2, NULL, 1343, 1344, 1, 75},
  {cont__377_3, NULL, 1352, 1352, 23, 57},
  {cont__378_1, NULL, 1352, 1352, 11, 76},
  {cont__378_2, NULL, 1353, 1353, 39, 76},
  {cont__378_3, NULL, 1353, 1353, 20, 76},
  {cont__378_4, NULL, 1353, 1353, 11, 77},
  {cont__378_5, NULL, 1351, 1353, 9, 76},
  {cont__378_6, NULL, 1354, 1354, 9, 46},
  {cont__378_7, NULL, 1350, 1354, 7, 45},
  {cont__378_8, NULL, 1349, 1354, 5, 46},
  {cont__378_9, NULL, 1355, 1355, 5, 15},
  {cont__378_10, NULL, 1346, 1355, 1, 16},
  {cont__378_11, NULL, 1363, 1363, 21, 66},
  {cont__379_1, NULL, 1363, 1363, 9, 75},
  {cont__379_2, NULL, 1364, 1364, 27, 75},
  {cont__379_3, NULL, 1364, 1364, 18, 75},
  {cont__379_4, NULL, 1364, 1364, 9, 76},
  {cont__379_5, NULL, 1362, 1364, 7, 75},
  {cont__379_6, NULL, 1365, 1365, 7, 55},
  {cont__379_7, NULL, 1361, 1365, 5, 54},
  {cont__379_8, NULL, 1366, 1366, 5, 26},
  {cont__379_9, NULL, 1367, 1367, 5, 19},
  {cont__379_10, NULL, 1368, 1368, 5, 15},
  {cont__379_11, NULL, 1357, 1368, 1, 16},
  {cont__379_12, NULL, 1373, 1373, 5, 18},
  {cont__380_1, NULL, 1375, 1375, 5, 33},
  {cont__380_2, NULL, 1380, 1380, 16, 31},
  {cont__380_3, NULL, 1380, 1380, 11, 32},
  {cont__380_4, NULL, 1384, 1384, 11, 32},
  {cont__380_5, NULL, 1378, 1384, 9, 31},
  {cont__380_6, NULL, 1386, 1386, 20, 55},
  {cont__380_7, NULL, 1386, 1386, 11, 56},
  {cont__380_8, NULL, 1389, 1389, 21, 38},
  {cont__380_9, NULL, 1389, 1389, 53, 74},
  {cont__380_10, NULL, 1389, 1389, 13, 74},
  {cont__380_11, NULL, 1392, 1392, 46, 79},
  {cont__380_13, NULL, 1392, 1392, 15, 80},
  {cont__380_14, NULL, 1390, 1392, 13, 79},
  {cont__380_15, NULL, 1393, 1393, 13, 46},
  {cont__380_16, NULL, 1388, 1393, 11, 45},
  {cont__380_17, NULL, 1385, 1393, 9, 46},
  {cont__380_18, NULL, 1394, 1394, 9, 42},
  {cont__380_19, NULL, 1377, 1394, 7, 41},
  {cont__380_20, NULL, 1376, 1394, 5, 42},
  {cont__380_21, NULL, 1370, 1395, 1, 23},
  {cont__380_22, NULL, 1399, 1399, 5, 21},
  {cont__381_1, NULL, 1400, 1400, 5, 18},
  {cont__381_2, NULL, 1397, 1403, 1, 23},
  {cont__381_3, NULL, 1405, 1405, 1, 42},
  {cont__382_1, NULL, 1410, 1410, 5, 20},
  {cont__383_1, NULL, 1412, 1412, 5, 25},
  {cont__383_2, NULL, 1413, 1413, 28, 51},
  {cont__383_3, NULL, 1413, 1413, 28, 66},
  {cont__383_4, NULL, 1413, 1413, 23, 67},
  {cont__383_5, NULL, 1413, 1413, 5, 68},
  {cont__383_6, NULL, 1414, 1414, 5, 26},
  {cont__383_7, NULL, 1415, 1415, 5, 19},
  {cont__383_8, NULL, 1416, 1416, 5, 15},
  {cont__383_9, NULL, 1407, 1417, 1, 23},
  {cont__383_10, NULL, 1419, 1419, 37, 70},
  {cont__384_1, NULL, 1419, 1419, 1, 71},
  {cont__384_2, NULL, 1422, 1422, 5, 24},
  {cont__385_1, NULL, 1425, 1425, 7, 48},
  {cont__385_2, NULL, 1425, 1425, 7, 71},
  {cont__385_3, NULL, 1427, 1427, 9, 51},
  {cont__385_4, NULL, 1426, 1427, 7, 72},
  {cont__385_5, NULL, 1428, 1428, 7, 49},
  {cont__385_6, NULL, 1428, 1428, 7, 72},
  {cont__385_7, NULL, 1429, 1429, 7, 50},
  {cont__385_8, NULL, 1429, 1429, 7, 73},
  {cont__385_9, NULL, 1431, 1431, 9, 37},
  {cont__385_10, NULL, 1432, 1432, 9, 65},
  {cont__385_11, NULL, 1430, 1432, 7, 64},
  {cont__385_12, NULL, 1424, 1432, 5, 65},
  {cont__385_13, NULL, 1420, 1433, 1, 23},
  {cont__385_14, NULL, 1436, 1436, 9, 38},
  {cont__386_1, NULL, 1435, 1436, 1, 38},
  {cont__386_3, NULL, 1439, 1439, 10, 51},
  {cont__387_1, NULL, 1438, 1439, 1, 51},
  {cont__387_3, NULL, 1445, 1445, 7, 79},
  {cont__388_1, NULL, 1444, 1445, 5, 78},
  {cont__388_2, NULL, 1441, 1446, 1, 20},
  {cont__388_3, NULL, 1450, 1450, 5, 24},
  {cont__389_1, NULL, 1453, 1453, 7, 48},
  {cont__389_2, NULL, 1453, 1453, 7, 71},
  {cont__389_3, NULL, 1455, 1455, 9, 51},
  {cont__389_4, NULL, 1459, 1465, 13, 56},
  {cont__389_15, NULL, 1457, 1465, 11, 57},
  {cont__389_16, NULL, 1456, 1466, 9, 30},
  {cont__389_17, NULL, 1454, 1466, 7, 31},
  {cont__389_18, NULL, 1467, 1467, 7, 49},
  {cont__389_19, NULL, 1467, 1467, 7, 72},
  {cont__389_20, NULL, 1468, 1468, 7, 50},
  {cont__389_21, NULL, 1468, 1468, 7, 73},
  {cont__389_22, NULL, 1470, 1470, 9, 37},
  {cont__389_23, NULL, 1471, 1471, 9, 65},
  {cont__389_24, NULL, 1469, 1471, 7, 64},
  {cont__389_25, NULL, 1452, 1471, 5, 65},
  {cont__389_26, NULL, 1448, 1472, 1, 23},
  {cont__389_27, NULL, 1474, 1474, 1, 53},
  {cont__390_1, NULL, 1478, 1478, 11, 42},
  {cont__391_1, NULL, 1478, 1478, 5, 47},
  {cont__391_3, NULL, 1479, 1479, 10, 41},
  {cont__391_4, NULL, 1479, 1479, 5, 41},
  {cont__391_5, NULL, 1476, 1479, 1, 42},
  {cont__391_6, NULL, 1483, 1483, 5, 28},
  {cont__392_1, NULL, 1486, 1486, 5, 42},
  {cont__392_2, NULL, 1495, 1495, 13, 52},
  {cont__392_3, NULL, 1492, 1495, 11, 51},
  {cont__392_4, NULL, 1491, 1497, 9, 28},
  {cont__392_5, NULL, 1488, 1497, 7, 29},
  {cont__392_6, NULL, 1487, 1498, 5, 24},
  {cont__392_7, NULL, 1481, 1499, 1, 23},
  {cont__392_8, NULL, 1501, 1501, 27, 54},
  {cont__393_1, NULL, 1501, 1501, 1, 63},
  {cont__393_2, NULL, 1505, 1505, 5, 34},
  {cont__394_1, NULL, 1505, 1505, 37, 62},
  {cont__394_2, NULL, 1505, 1505, 5, 62},
  {cont__394_3, NULL, 1503, 1506, 1, 28},
  {cont__394_4, NULL, 1510, 1510, 5, 44},
  {cont__395_1, NULL, 1510, 1510, 47, 72},
  {cont__395_2, NULL, 1510, 1510, 5, 72},
  {cont__395_3, NULL, 1508, 1511, 1, 28},
  {cont__395_4, NULL, 1513, 1513, 1, 53},
  {cont__396_1, NULL, 1521, 1521, 9, 34},
  {cont__397_1, NULL, 1524, 1528, 9, 19},
  {cont__397_8, NULL, 1520, 1529, 7, 25},
  {cont__397_9, NULL, 1518, 1529, 5, 26},
  {cont__397_10, NULL, 1515, 1529, 1, 29},
  {cont__397_11, NULL, 1534, 1534, 7, 38},
  {cont__398_1, NULL, 1534, 1534, 50, 76},
  {cont__398_2, NULL, 1534, 1534, 41, 77},
  {cont__398_3, NULL, 1534, 1534, 7, 77},
  {cont__398_4, NULL, 1536, 1536, 7, 40},
  {cont__398_5, NULL, 1533, 1536, 5, 39},
  {cont__398_6, NULL, 1537, 1537, 10, 36},
  {cont__398_7, NULL, 1537, 1537, 5, 37},
  {cont__398_8, NULL, 1531, 1537, 1, 38},
  {cont__398_9, NULL, 1542, 1542, 5, 24},
  {cont__399_1, NULL, 1542, 1542, 54, 63},
  {cont__399_3, NULL, 1542, 1542, 49, 64},
  {cont__399_4, NULL, 1542, 1542, 43, 64},
  {cont__399_5, NULL, 1542, 1542, 27, 65},
  {cont__399_6, NULL, 1542, 1542, 5, 65},
  {cont__399_7, NULL, 1539, 1542, 1, 66},
  {cont__399_8, NULL, 1544, 1544, 20, 39},
  {cont__400_1, NULL, 1544, 1544, 20, 54},
  {cont__400_2, NULL, 1544, 1544, 1, 55},
  {cont__400_3, NULL, 1549, 1549, 31, 70},
  {cont__401_1, NULL, 1549, 1549, 12, 70},
  {cont__401_2, NULL, 1549, 1549, 5, 71},
  {cont__401_3, NULL, 1546, 1549, 1, 72},
  {cont__401_5, NULL, 1552, 1552, 37, 71},
  {cont__402_1, NULL, 1552, 1552, 18, 71},
  {cont__402_2, NULL, 1552, 1552, 11, 72},
  {cont__402_3, NULL, 1551, 1552, 1, 72},
  {cont__402_5, NULL, 1554, 1554, 52, 72},
  {cont__403_1, NULL, 1554, 1554, 33, 72},
  {cont__403_2, NULL, 1554, 1554, 26, 73},
  {cont__403_3, NULL, 1554, 1554, 1, 73},
  {cont__403_5, NULL, 1559, 1559, 31, 77},
  {cont__404_1, NULL, 1559, 1559, 12, 77},
  {cont__404_2, NULL, 1559, 1559, 5, 78},
  {cont__404_3, NULL, 1556, 1559, 1, 79},
  {cont__404_5, NULL, 1561, 1561, 52, 72},
  {cont__405_1, NULL, 1561, 1561, 33, 72},
  {cont__405_2, NULL, 1561, 1561, 26, 73},
  {cont__405_3, NULL, 1561, 1561, 1, 73},
  {cont__405_5, NULL, 1569, 1569, 32, 71},
  {cont__406_5, NULL, 1569, 1569, 9, 72},
  {cont__406_6, NULL, 1567, 1569, 7, 71},
  {cont__406_7, NULL, 1566, 1569, 5, 72},
  {cont__406_8, NULL, 1563, 1569, 1, 75},
  {cont__406_10, NULL, 1572, 1572, 37, 77},
  {cont__407_1, NULL, 1572, 1572, 18, 77},
  {cont__407_2, NULL, 1572, 1572, 11, 78},
  {cont__407_3, NULL, 1571, 1572, 1, 78},
  {cont__407_5, NULL, 1583, 1583, 5, 42},
  {cont__408_2, NULL, 1574, 1583, 1, 43},
  {cont__408_3, NULL, 1585, 1585, 35, 45},
  {cont__409_1, NULL, 1585, 1585, 1, 45},
  {cont__409_2, NULL, 1586, 1586, 1, 45},
  {cont__410_1, NULL, 1587, 1587, 1, 32},
  {cont__411_2, NULL, 1588, 1588, 50, 69},
  {cont__412_1, NULL, 1588, 1588, 37, 70},
  {cont__412_2, NULL, 1588, 1588, 22, 70},
  {cont__412_3, NULL, 1588, 1588, 1, 71},
  {cont__412_4, NULL, 1593, 1593, 28, 51},
  {cont__413_1, NULL, 1593, 1593, 28, 66},
  {cont__413_2, NULL, 1593, 1593, 23, 67},
  {cont__413_3, NULL, 1593, 1593, 5, 68},
  {cont__413_4, NULL, 1590, 1593, 1, 69},
  {cont__413_5, NULL, 1598, 1598, 5, 20},
  {cont__414_1, NULL, 1599, 1599, 5, 25},
  {cont__414_2, NULL, 1600, 1600, 31, 46},
  {cont__414_3, NULL, 1600, 1600, 22, 47},
  {cont__414_4, NULL, 1600, 1600, 9, 47},
  {cont__414_5, NULL, 1600, 1600, 5, 55},
  {cont__414_6, NULL, 1601, 1601, 5, 26},
  {cont__414_7, NULL, 1602, 1602, 5, 19},
  {cont__414_8, NULL, 1603, 1603, 5, 15},
  {cont__414_9, NULL, 1595, 1603, 1, 16},
  {cont__414_10, NULL, 1605, 1605, 41, 60},
  {cont__415_1, NULL, 1605, 1605, 34, 61},
  {cont__415_2, NULL, 1605, 1605, 1, 61},
  {cont__415_3, NULL, 1613, 1613, 7, 50},
  {cont__416_2, NULL, 1609, 1613, 5, 49},
  {cont__416_3, NULL, 1614, 1614, 12, 31},
  {cont__416_4, NULL, 1614, 1614, 5, 32},
  {cont__416_5, NULL, 1607, 1614, 1, 33},
  {cont__416_6, NULL, },
  {entry__sim2c__std_identifier_1, NULL, 30, 30, 32, 79},
  {entry__print_message_13, NULL, 60, 60, 38, 63},
  {cont__print_message_14, &frame__print_message_13, 60, 60, 23, 75},
  {cont__print_message_15, &frame__print_message_13, 60, 60, 75, 75},
  {entry__print_message_21, NULL, 62, 62, 21, 29},
  {cont__print_message_22, &frame__print_message_21, 62, 62, 21, 35},
  {cont__print_message_23, &frame__print_message_21, 62, 62, 21, 35},
  {entry__print_message_25, NULL, 62, 62, 38, 43},
  {cont__print_message_26, &frame__print_message_25, 62, 62, 43, 43},
  {entry__print_message_19, NULL, 62, 62, 12, 16},
  {cont__print_message_20, &frame__print_message_19, 62, 62, 12, 35},
  {cont__print_message_24, &frame__print_message_19, 62, 62, 9, 43},
  {entry__print_message_30, NULL, 64, 64, 32, 62},
  {cont__print_message_31, &frame__print_message_30, 64, 64, 29, 62},
  {entry__print_message_32, NULL, 64, 64, 65, 71},
  {entry__print_message_40, NULL, 68, 68, 10, 19},
  {cont__print_message_41, &frame__print_message_40, 68, 68, 10, 19},
  {cont__print_message_42, &frame__print_message_40, 68, 68, 7, 25},
  {cont__print_message_43, &frame__print_message_40, 69, 69, 7, 12},
  {cont__print_message_44, &frame__print_message_40, 69, 69, 12, 12},
  {entry__print_message_39, NULL, 67, 69, 5, 12},
  {cont__print_message_45, &frame__print_message_39, 69, 69, 12, 12},
  {entry__print_message_50, NULL, 73, 73, 43, 45},
  {cont__print_message_51, &frame__print_message_50, 73, 73, 14, 59},
  {cont__print_message_55, &frame__print_message_50, 73, 73, 7, 59},
  {entry__print_message_56, NULL, 75, 77, 14, 75},
  {cont__print_message_62, &frame__print_message_56, 75, 77, 7, 75},
  {cont__print_message_63, &frame__print_message_56, 78, 78, 7, 19},
  {cont__print_message_64, &frame__print_message_56, 79, 79, 16, 25},
  {cont__print_message_66, &frame__print_message_56, 79, 79, 7, 29},
  {entry__print_message_1, NULL, 52, 52, 3, 37},
  {cont__print_message_2, &frame__print_message_1, 53, 53, 8, 24},
  {cont__print_message_3, &frame__print_message_1, 53, 53, 8, 31},
  {cont__print_message_4, &frame__print_message_1, 53, 53, 3, 33},
  {cont__print_message_5, &frame__print_message_1, 54, 54, 3, 32},
  {cont__print_message_6, &frame__print_message_1, 57, 57, 38, 42},
  {cont__print_message_7, &frame__print_message_1, 57, 57, 23, 43},
  {cont__print_message_8, &frame__print_message_1, 57, 57, 45, 70},
  {cont__print_message_9, &frame__print_message_1, 56, 57, 3, 71},
  {cont__print_message_10, &frame__print_message_1, 59, 59, 3, 27},
  {cont__print_message_11, &frame__print_message_1, 60, 60, 6, 20},
  {cont__print_message_12, &frame__print_message_1, 60, 60, 3, 75},
  {cont__print_message_16, &frame__print_message_1, 61, 61, 7, 23},
  {cont__print_message_17, &frame__print_message_1, 61, 61, 3, 30},
  {cont__print_message_18, &frame__print_message_1, 62, 62, 3, 43},
  {cont__print_message_27, &frame__print_message_1, 63, 63, 3, 32},
  {cont__print_message_28, &frame__print_message_1, 64, 64, 12, 26},
  {cont__print_message_29, &frame__print_message_1, 64, 64, 3, 72},
  {cont__print_message_33, &frame__print_message_1, 65, 65, 42, 59},
  {cont__print_message_34, &frame__print_message_1, 65, 65, 21, 59},
  {cont__print_message_35, &frame__print_message_1, 65, 65, 61, 79},
  {cont__print_message_37, &frame__print_message_1, 65, 65, 3, 80},
  {cont__print_message_38, &frame__print_message_1, 66, 69, 3, 13},
  {cont__print_message_46, &frame__print_message_1, 70, 70, 18, 23},
  {cont__print_message_47, &frame__print_message_1, 70, 70, 3, 23},
  {cont__print_message_48, &frame__print_message_1, 70, 70, 17, 23},
  {cont__print_message_49, &frame__print_message_1, 71, 79, 3, 30},
  {entry__sim2c__Warning_1, NULL, 82, 82, 17, 32},
  {cont__sim2c__Warning_2, &frame__sim2c__Warning_1, 82, 82, 34, 56},
  {cont__sim2c__Warning_3, &frame__sim2c__Warning_1, 82, 82, 3, 70},
  {entry__ExitWithSyntaxError_1, NULL, 85, 85, 3, 50},
  {cont__ExitWithSyntaxError_3, &frame__ExitWithSyntaxError_1, 86, 86, 3, 8},
  {entry__sim2c__SyntaxError_1, NULL, 89, 89, 23, 38},
  {cont__sim2c__SyntaxError_2, &frame__sim2c__SyntaxError_1, 89, 89, 40, 62},
  {cont__sim2c__SyntaxError_3, &frame__sim2c__SyntaxError_1, 89, 89, 3, 66},
  {entry__ParseError_1, NULL, 92, 92, 40, 56},
  {cont__ParseError_2, &frame__ParseError_1, 92, 92, 3, 60},
  {entry__types__syntax_error__grammar__match_1, NULL, 97, 97, 21, 36},
  {cont__types__syntax_error__grammar__match_2, &frame__types__syntax_error__grammar__match_1, 97, 97, 3, 36},
  {entry__syntax_error_1, NULL, 99, 99, 26, 68},
  {entry__types__unexpected_input_error__grammar__match_4, NULL, 109, 109, 34, 55},
  {cont__types__unexpected_input_error__grammar__match_5, &frame__types__unexpected_input_error__grammar__match_4, 109, 109, 34, 55},
  {entry__types__unexpected_input_error__grammar__match_8, NULL, 113, 113, 11, 46},
  {entry__types__unexpected_input_error__grammar__match_10, NULL, 115, 115, 11, 45},
  {entry__types__unexpected_input_error__grammar__match_12, NULL, 117, 117, 11, 46},
  {entry__types__unexpected_input_error__grammar__match_14, NULL, 119, 119, 11, 61},
  {entry__types__unexpected_input_error__grammar__match_16, NULL, 121, 122, 29, 42},
  {cont__types__unexpected_input_error__grammar__match_19, &frame__types__unexpected_input_error__grammar__match_16, 121, 122, 11, 42},
  {entry__types__unexpected_input_error__grammar__match_7, NULL, 110, 122, 7, 44},
  {entry__types__unexpected_input_error__grammar__match_20, NULL, 124, 124, 7, 42},
  {entry__types__unexpected_input_error__grammar__match_1, NULL, 107, 107, 3, 33},
  {cont__types__unexpected_input_error__grammar__match_2, &frame__types__unexpected_input_error__grammar__match_1, 109, 109, 5, 29},
  {cont__types__unexpected_input_error__grammar__match_3, &frame__types__unexpected_input_error__grammar__match_1, 109, 109, 5, 55},
  {cont__types__unexpected_input_error__grammar__match_6, &frame__types__unexpected_input_error__grammar__match_1, 108, 124, 3, 43},
  {entry__unexpected_input_error_1, NULL, 127, 127, 3, 61},
  {entry__types__print__grammar__match_1, NULL, 136, 136, 12, 27},
  {cont__types__print__grammar__match_2, &frame__types__print__grammar__match_1, 136, 136, 3, 27},
  {cont__types__print__grammar__match_3, &frame__types__print__grammar__match_1, 137, 137, 3, 6},
  {entry__print_1, NULL, 139, 139, 19, 54},
  {entry__dump_stream__grammar__match_1, NULL, 148, 148, 3, 23},
  {cont__dump_stream__grammar__match_3, &frame__dump_stream__grammar__match_1, 149, 149, 17, 48},
  {cont__dump_stream__grammar__match_4, &frame__dump_stream__grammar__match_1, 149, 149, 3, 48},
  {cont__dump_stream__grammar__match_5, &frame__dump_stream__grammar__match_1, 150, 150, 3, 23},
  {cont__dump_stream__grammar__match_7, &frame__dump_stream__grammar__match_1, 151, 151, 3, 6},
  {entry__sim2c__strip_4, NULL, 164, 164, 42, 56},
  {cont__sim2c__strip_5, &frame__sim2c__strip_4, 164, 164, 35, 56},
  {cont__sim2c__strip_6, &frame__sim2c__strip_4, 164, 164, 56, 56},
  {entry__sim2c__strip_10, NULL, 165, 165, 44, 60},
  {cont__sim2c__strip_11, &frame__sim2c__strip_10, 165, 165, 37, 60},
  {cont__sim2c__strip_12, &frame__sim2c__strip_10, 165, 165, 60, 60},
  {entry__sim2c__strip_18, NULL, 167, 167, 51, 66},
  {cont__sim2c__strip_19, &frame__sim2c__strip_18, 167, 167, 66, 66},
  {entry__sim2c__strip_16, NULL, 167, 167, 18, 35},
  {cont__sim2c__strip_17, &frame__sim2c__strip_16, 167, 167, 5, 66},
  {cont__sim2c__strip_20, &frame__sim2c__strip_16, 167, 167, 66, 66},
  {entry__sim2c__strip_26, NULL, 169, 169, 51, 66},
  {cont__sim2c__strip_27, &frame__sim2c__strip_26, 169, 169, 66, 66},
  {entry__sim2c__strip_24, NULL, 169, 169, 18, 35},
  {cont__sim2c__strip_25, &frame__sim2c__strip_24, 169, 169, 5, 66},
  {cont__sim2c__strip_28, &frame__sim2c__strip_24, 169, 169, 66, 66},
  {entry__sim2c__strip_34, NULL, 171, 171, 56, 70},
  {cont__sim2c__strip_35, &frame__sim2c__strip_34, 171, 171, 70, 70},
  {entry__sim2c__strip_32, NULL, 171, 171, 18, 41},
  {cont__sim2c__strip_33, &frame__sim2c__strip_32, 171, 171, 5, 70},
  {cont__sim2c__strip_36, &frame__sim2c__strip_32, 171, 171, 70, 70},
  {entry__sim2c__strip_42, NULL, 173, 173, 49, 63},
  {cont__sim2c__strip_43, &frame__sim2c__strip_42, 173, 173, 63, 63},
  {entry__sim2c__strip_40, NULL, 173, 173, 18, 34},
  {cont__sim2c__strip_41, &frame__sim2c__strip_40, 173, 173, 5, 63},
  {cont__sim2c__strip_44, &frame__sim2c__strip_40, 173, 173, 63, 63},
  {entry__sim2c__strip_48, NULL, 174, 174, 41, 54},
  {cont__sim2c__strip_49, &frame__sim2c__strip_48, 174, 174, 34, 54},
  {cont__sim2c__strip_50, &frame__sim2c__strip_48, 174, 174, 54, 54},
  {entry__sim2c__strip_54, NULL, 175, 175, 45, 62},
  {cont__sim2c__strip_55, &frame__sim2c__strip_54, 175, 175, 38, 62},
  {cont__sim2c__strip_56, &frame__sim2c__strip_54, 175, 175, 62, 62},
  {entry__sim2c__strip_1, NULL, 164, 164, 6, 21},
  {cont__sim2c__strip_2, &frame__sim2c__strip_1, 164, 164, 6, 32},
  {cont__sim2c__strip_3, &frame__sim2c__strip_1, 164, 164, 3, 56},
  {cont__sim2c__strip_7, &frame__sim2c__strip_1, 165, 165, 6, 23},
  {cont__sim2c__strip_8, &frame__sim2c__strip_1, 165, 165, 6, 34},
  {cont__sim2c__strip_9, &frame__sim2c__strip_1, 165, 165, 3, 60},
  {cont__sim2c__strip_13, &frame__sim2c__strip_1, 166, 166, 6, 24},
  {cont__sim2c__strip_14, &frame__sim2c__strip_1, 166, 166, 6, 35},
  {cont__sim2c__strip_15, &frame__sim2c__strip_1, 166, 167, 3, 66},
  {cont__sim2c__strip_21, &frame__sim2c__strip_1, 168, 168, 6, 24},
  {cont__sim2c__strip_22, &frame__sim2c__strip_1, 168, 168, 6, 35},
  {cont__sim2c__strip_23, &frame__sim2c__strip_1, 168, 169, 3, 66},
  {cont__sim2c__strip_29, &frame__sim2c__strip_1, 170, 170, 6, 30},
  {cont__sim2c__strip_30, &frame__sim2c__strip_1, 170, 170, 6, 41},
  {cont__sim2c__strip_31, &frame__sim2c__strip_1, 170, 171, 3, 70},
  {cont__sim2c__strip_37, &frame__sim2c__strip_1, 172, 172, 6, 23},
  {cont__sim2c__strip_38, &frame__sim2c__strip_1, 172, 172, 6, 34},
  {cont__sim2c__strip_39, &frame__sim2c__strip_1, 172, 173, 3, 63},
  {cont__sim2c__strip_45, &frame__sim2c__strip_1, 174, 174, 6, 20},
  {cont__sim2c__strip_46, &frame__sim2c__strip_1, 174, 174, 6, 31},
  {cont__sim2c__strip_47, &frame__sim2c__strip_1, 174, 174, 3, 54},
  {cont__sim2c__strip_51, &frame__sim2c__strip_1, 175, 175, 6, 24},
  {cont__sim2c__strip_52, &frame__sim2c__strip_1, 175, 175, 6, 35},
  {cont__sim2c__strip_53, &frame__sim2c__strip_1, 175, 175, 3, 62},
  {cont__sim2c__strip_57, &frame__sim2c__strip_1, },
  {entry__dump__grammar__match_1, NULL, 180, 180, 10, 37},
  {cont__dump__grammar__match_2, &frame__dump__grammar__match_1, 180, 180, 3, 37},
  {cont__dump__grammar__match_4, &frame__dump__grammar__match_1, 181, 181, 3, 6},
  {entry__dump3__grammar__match_1, NULL, 186, 186, 12, 39},
  {cont__dump3__grammar__match_2, &frame__dump3__grammar__match_1, 186, 186, 3, 39},
  {cont__dump3__grammar__match_3, &frame__dump3__grammar__match_1, 187, 187, 3, 6},
  {entry__dump5__grammar__match_1, NULL, 192, 192, 12, 39},
  {cont__dump5__grammar__match_2, &frame__dump5__grammar__match_1, 192, 192, 3, 39},
  {cont__dump5__grammar__match_3, &frame__dump5__grammar__match_1, 193, 193, 3, 6},
  {entry__sim2c__precedence_3, NULL, 226, 226, 25, 44},
  {cont__sim2c__precedence_4, &frame__sim2c__precedence_3, 226, 226, 22, 44},
  {entry__sim2c__precedence_5, NULL, 226, 226, 47, 65},
  {entry__sim2c__precedence_1, NULL, 226, 226, 6, 19},
  {cont__sim2c__precedence_2, &frame__sim2c__precedence_1, 226, 226, 3, 65},
  {entry__sim2c__is_left_associative_1, NULL, 228, 228, 40, 47},
  {cont__sim2c__is_left_associative_2, &frame__sim2c__is_left_associative_1, 228, 228, 37, 47},
  {entry__is_right_associative_1, NULL, 230, 230, 34, 42},
  {cont__is_right_associative_2, &frame__is_right_associative_1, 230, 230, 34, 42},
  {cont__is_right_associative_3, &frame__is_right_associative_1, 230, 230, 31, 42},
  {entry__infix_operator_1, NULL, 233, 233, 19, 64},
  {cont__infix_operator_2, &frame__infix_operator_1, 233, 233, 6, 65},
  {cont__infix_operator_3, &frame__infix_operator_1, 233, 233, 3, 65},
  {entry__interleaved_1, NULL, 235, 235, 58, 78},
  {cont__interleaved_2, &frame__interleaved_1, 235, 235, 53, 79},
  {cont__interleaved_3, &frame__interleaved_1, 235, 235, 41, 79},
  {cont__interleaved_4, &frame__interleaved_1, 235, 235, 38, 79},
  {entry__types__inline__grammar__match_1, NULL, 245, 245, 18, 36},
  {cont__types__inline__grammar__match_2, &frame__types__inline__grammar__match_1, 245, 245, 3, 43},
  {cont__types__inline__grammar__match_3, &frame__types__inline__grammar__match_1, 245, 245, 43, 43},
  {entry__inline_1, NULL, 247, 247, 23, 65},
  {entry__expect_3, NULL, 265, 265, 36, 60},
  {cont__expect_5, &frame__expect_3, 265, 265, 23, 61},
  {cont__expect_6, &frame__expect_3, 265, 265, 8, 62},
  {cont__expect_7, &frame__expect_3, 265, 265, 5, 62},
  {entry__expect_8, NULL, 266, 266, 23, 56},
  {cont__expect_9, &frame__expect_8, 266, 266, 8, 57},
  {cont__expect_10, &frame__expect_8, 266, 266, 5, 57},
  {entry__expect_1, NULL, 264, 264, 5, 26},
  {cont__expect_2, &frame__expect_1, 263, 266, 3, 57},
  {entry__sim2c__arguments_span_1, NULL, 285, 285, 30, 50},
  {cont__sim2c__arguments_span_2, &frame__sim2c__arguments_span_1, 285, 285, 6, 51},
  {cont__sim2c__arguments_span_3, &frame__sim2c__arguments_span_1, 285, 285, 3, 51},
  {entry__sim2c__output_arguments_span_1, NULL, 288, 288, 37, 77},
  {cont__sim2c__output_arguments_span_2, &frame__sim2c__output_arguments_span_1, 288, 288, 6, 78},
  {cont__sim2c__output_arguments_span_3, &frame__sim2c__output_arguments_span_1, 288, 288, 3, 78},
  {entry__sim2c__parse_meta_instruction_7, NULL, 1623, 1623, 32, 75},
  {entry__sim2c__parse_meta_instruction_1, NULL, 1621, 1621, 3, 36},
  {cont__sim2c__parse_meta_instruction_2, &frame__sim2c__parse_meta_instruction_1, 1622, 1622, 3, 38},
  {cont__sim2c__parse_meta_instruction_3, &frame__sim2c__parse_meta_instruction_1, 1623, 1623, 13, 29},
  {cont__sim2c__parse_meta_instruction_4, &frame__sim2c__parse_meta_instruction_1, 1623, 1623, 6, 29},
  {cont__sim2c__parse_meta_instruction_5, &frame__sim2c__parse_meta_instruction_1, 1623, 1623, 6, 29},
  {cont__sim2c__parse_meta_instruction_6, &frame__sim2c__parse_meta_instruction_1, 1623, 1623, 3, 75},
  {cont__sim2c__parse_meta_instruction_9, &frame__sim2c__parse_meta_instruction_1, 1624, 1624, 3, 8},
  {entry__sim2c__parse_statement_9, NULL, 1633, 1633, 9, 67},
  {entry__sim2c__parse_statement_5, NULL, 1632, 1632, 17, 33},
  {cont__sim2c__parse_statement_6, &frame__sim2c__parse_statement_5, 1632, 1632, 10, 33},
  {cont__sim2c__parse_statement_7, &frame__sim2c__parse_statement_5, 1632, 1632, 10, 33},
  {cont__sim2c__parse_statement_8, &frame__sim2c__parse_statement_5, 1632, 1633, 7, 67},
  {entry__sim2c__parse_statement_11, NULL, 1635, 1635, 7, 57},
  {cont__sim2c__parse_statement_13, &frame__sim2c__parse_statement_11, 1636, 1636, 7, 26},
  {cont__sim2c__parse_statement_14, &frame__sim2c__parse_statement_11, 1637, 1637, 7, 25},
  {cont__sim2c__parse_statement_16, &frame__sim2c__parse_statement_11, 1638, 1638, 7, 12},
  {entry__sim2c__parse_statement_1, NULL, 1628, 1628, 3, 36},
  {cont__sim2c__parse_statement_2, &frame__sim2c__parse_statement_1, 1629, 1629, 3, 33},
  {cont__sim2c__parse_statement_3, &frame__sim2c__parse_statement_1, 1631, 1631, 5, 18},
  {cont__sim2c__parse_statement_4, &frame__sim2c__parse_statement_1, 1630, 1638, 3, 13},
  {cont__sim2c__parse_statement_17, &frame__sim2c__parse_statement_1, 1639, 1639, 3, 8},
  {entry__246_2, NULL, 253, 254, 9, 23},
  {entry__246_1, NULL, 252, 254, 7, 24},
  {cont__246_4, &frame__246_1, 255, 255, 7, 13},
  {entry__252_1, NULL, 276, 276, 7, 28},
  {cont__252_2, &frame__252_1, 277, 277, 47, 47},
  {entry__253_1, NULL, 282, 282, 33, 33},
  {entry__260_1, NULL, 302, 302, 7, 48},
  {cont__260_2, &frame__260_1, 303, 303, 40, 40},
  {entry__261_1, NULL, 312, 312, 32, 48},
  {cont__261_2, &frame__261_1, 312, 312, 7, 50},
  {cont__261_3, &frame__261_1, 313, 313, 40, 40},
  {entry__262_1, NULL, 322, 322, 32, 48},
  {cont__262_2, &frame__262_1, 322, 322, 7, 50},
  {cont__262_3, &frame__262_1, 323, 323, 40, 40},
  {entry__263_1, NULL, 332, 332, 7, 45},
  {cont__263_2, &frame__263_1, 332, 332, 45, 45},
  {entry__264_3, NULL, 344, 344, 13, 43},
  {cont__264_4, &frame__264_3, 344, 344, 43, 43},
  {entry__265_6, NULL, 360, 360, 15, 76},
  {entry__265_4, NULL, 359, 359, 16, 31},
  {cont__265_5, &frame__265_4, 359, 360, 13, 76},
  {cont__265_8, &frame__265_4, 361, 361, 13, 43},
  {cont__265_9, &frame__265_4, 361, 361, 43, 43},
  {entry__268_7, NULL, 391, 392, 29, 55},
  {cont__268_10, &frame__268_7, 391, 392, 11, 55},
  {entry__268_3, NULL, 389, 389, 9, 41},
  {cont__268_4, &frame__268_3, 390, 390, 12, 37},
  {cont__268_5, &frame__268_3, 390, 390, 12, 48},
  {cont__268_6, &frame__268_3, 390, 392, 9, 56},
  {cont__268_11, &frame__268_3, 393, 393, 9, 35},
  {cont__268_12, &frame__268_3, 393, 393, 40, 40},
  {entry__269_4, NULL, 406, 406, 13, 54},
  {cont__269_5, &frame__269_4, 406, 406, 54, 54},
  {entry__269_17, NULL, 416, 417, 33, 64},
  {cont__269_20, &frame__269_17, 416, 417, 15, 64},
  {entry__269_14, NULL, 415, 415, 16, 40},
  {cont__269_15, &frame__269_14, 415, 415, 16, 51},
  {cont__269_16, &frame__269_14, 415, 417, 13, 65},
  {cont__269_21, &frame__269_14, 418, 418, 13, 38},
  {cont__269_22, &frame__269_14, 418, 418, 48, 48},
  {entry__269_25, NULL, 421, 422, 33, 62},
  {cont__269_27, &frame__269_25, 421, 422, 15, 62},
  {entry__269_23, NULL, 420, 420, 16, 44},
  {cont__269_24, &frame__269_23, 420, 422, 13, 63},
  {cont__269_28, &frame__269_23, 423, 423, 13, 42},
  {cont__269_29, &frame__269_23, 423, 423, 47, 47},
  {entry__269_10, NULL, 411, 411, 9, 37},
  {cont__269_11, &frame__269_10, 412, 412, 9, 39},
  {cont__269_12, &frame__269_10, 414, 414, 11, 26},
  {cont__269_13, &frame__269_10, 413, 423, 9, 48},
  {entry__270_6, NULL, 436, 437, 29, 55},
  {cont__270_8, &frame__270_6, 436, 437, 11, 55},
  {entry__270_3, NULL, 434, 434, 9, 37},
  {cont__270_4, &frame__270_3, 435, 435, 12, 37},
  {cont__270_5, &frame__270_3, 435, 437, 9, 56},
  {cont__270_9, &frame__270_3, 438, 438, 9, 35},
  {cont__270_10, &frame__270_3, 438, 438, 40, 40},
  {entry__273_6, NULL, 454, 455, 29, 53},
  {cont__273_9, &frame__273_6, 454, 455, 11, 53},
  {entry__273_3, NULL, 452, 452, 9, 41},
  {cont__273_4, &frame__273_3, 453, 453, 12, 35},
  {cont__273_5, &frame__273_3, 453, 455, 9, 54},
  {cont__273_10, &frame__273_3, 456, 456, 9, 33},
  {cont__273_11, &frame__273_3, 456, 456, 38, 38},
  {entry__274_6, NULL, 469, 470, 29, 54},
  {cont__274_9, &frame__274_6, 469, 470, 11, 54},
  {entry__274_3, NULL, 467, 467, 9, 41},
  {cont__274_4, &frame__274_3, 468, 468, 12, 37},
  {cont__274_5, &frame__274_3, 468, 470, 9, 55},
  {cont__274_10, &frame__274_3, 471, 471, 9, 35},
  {cont__274_11, &frame__274_3, 471, 471, 40, 40},
  {entry__277_6, NULL, 487, 488, 29, 63},
  {cont__277_8, &frame__277_6, 487, 488, 11, 63},
  {entry__277_3, NULL, 485, 485, 9, 41},
  {cont__277_4, &frame__277_3, 486, 486, 12, 35},
  {cont__277_5, &frame__277_3, 486, 488, 9, 64},
  {cont__277_9, &frame__277_3, 489, 489, 9, 33},
  {cont__277_10, &frame__277_3, 489, 489, 38, 38},
  {entry__284_3, NULL, 516, 516, 40, 65},
  {cont__284_4, &frame__284_3, 516, 516, 40, 65},
  {entry__284_10, NULL, 520, 520, 55, 55},
  {entry__284_11, NULL, 522, 522, 42, 42},
  {cont__284_12, &frame__284_11, 522, 522, 23, 39},
  {cont__284_13, &frame__284_11, 522, 522, 23, 43},
  {cont__284_14, &frame__284_11, 522, 522, 23, 66},
  {cont__284_15, &frame__284_11, 522, 522, 15, 79},
  {cont__284_16, &frame__284_11, 522, 522, 23, 39},
  {cont__284_17, &frame__284_11, 522, 522, 42, 42},
  {cont__284_18, &frame__284_11, 522, 522, 23, 43},
  {cont__284_19, &frame__284_11, 522, 522, 22, 43},
  {cont__284_20, &frame__284_11, 522, 522, 79, 79},
  {entry__284_6, NULL, 517, 517, 11, 45},
  {cont__284_7, &frame__284_6, 519, 519, 13, 30},
  {cont__284_8, &frame__284_6, 519, 519, 13, 39},
  {cont__284_9, &frame__284_6, 518, 522, 11, 80},
  {cont__284_21, &frame__284_6, 523, 523, 42, 42},
  {entry__284_1, NULL, 516, 516, 16, 35},
  {cont__284_2, &frame__284_1, 516, 516, 16, 65},
  {cont__284_5, &frame__284_1, 516, 523, 9, 42},
  {cont__284_22, &frame__284_1, },
  {entry__286_7, NULL, 539, 539, 18, 34},
  {cont__286_8, &frame__286_7, 539, 539, 18, 37},
  {cont__286_9, &frame__286_7, 539, 539, 18, 53},
  {cont__286_10, &frame__286_7, 540, 540, 40, 40},
  {cont__286_11, &frame__286_7, 540, 540, 17, 37},
  {cont__286_12, &frame__286_7, 540, 540, 17, 41},
  {cont__286_13, &frame__286_7, 538, 540, 15, 41},
  {cont__286_14, &frame__286_7, 539, 539, 18, 34},
  {cont__286_15, &frame__286_7, 539, 539, 18, 37},
  {cont__286_16, &frame__286_7, 539, 539, 17, 37},
  {cont__286_17, &frame__286_7, 541, 541, 22, 41},
  {cont__286_18, &frame__286_7, 541, 541, 46, 46},
  {cont__286_19, &frame__286_7, 541, 541, 15, 46},
  {cont__286_20, &frame__286_7, 541, 541, 46, 46},
  {entry__286_3, NULL, 536, 536, 26, 43},
  {cont__286_4, &frame__286_3, 536, 536, 13, 44},
  {cont__286_5, &frame__286_3, 537, 537, 16, 20},
  {cont__286_6, &frame__286_3, 537, 541, 13, 46},
  {entry__286_1, NULL, 535, 535, 18, 37},
  {cont__286_2, &frame__286_1, 535, 541, 11, 47},
  {cont__286_21, &frame__286_1, },
  {entry__287_7, NULL, 552, 552, 19, 35},
  {cont__287_8, &frame__287_7, 552, 552, 19, 38},
  {cont__287_9, &frame__287_7, 552, 552, 19, 54},
  {cont__287_10, &frame__287_7, 552, 552, 79, 79},
  {cont__287_11, &frame__287_7, 552, 552, 56, 76},
  {cont__287_12, &frame__287_7, 552, 552, 56, 80},
  {cont__287_13, &frame__287_7, 552, 552, 13, 80},
  {cont__287_14, &frame__287_7, 552, 552, 19, 35},
  {cont__287_15, &frame__287_7, 552, 552, 19, 38},
  {cont__287_16, &frame__287_7, 552, 552, 18, 38},
  {cont__287_17, &frame__287_7, 553, 553, 20, 39},
  {cont__287_18, &frame__287_7, 553, 553, 44, 44},
  {cont__287_19, &frame__287_7, 553, 553, 13, 44},
  {cont__287_20, &frame__287_7, 553, 553, 44, 44},
  {entry__287_3, NULL, 550, 550, 24, 41},
  {cont__287_4, &frame__287_3, 550, 550, 11, 42},
  {cont__287_5, &frame__287_3, 551, 551, 14, 18},
  {cont__287_6, &frame__287_3, 551, 553, 11, 44},
  {entry__287_1, NULL, 549, 549, 16, 35},
  {cont__287_2, &frame__287_1, 549, 553, 9, 45},
  {cont__287_21, &frame__287_1, },
  {entry__290_1, NULL, 569, 569, 26, 42},
  {cont__290_2, &frame__290_1, 570, 570, 33, 56},
  {cont__290_3, &frame__290_1, 566, 570, 9, 57},
  {entry__291_1, NULL, 580, 580, 25, 34},
  {cont__291_2, &frame__291_1, 582, 582, 24, 40},
  {cont__291_3, &frame__291_1, 583, 583, 31, 54},
  {cont__291_4, &frame__291_1, 583, 583, 56, 56},
  {entry__306_2, NULL, 633, 633, 30, 49},
  {cont__306_3, &frame__306_2, 633, 633, 9, 52},
  {cont__306_4, &frame__306_2, 633, 633, 52, 52},
  {entry__307_1, NULL, 640, 640, 33, 33},
  {entry__308_6, NULL, 653, 653, 32, 73},
  {entry__308_2, NULL, 652, 652, 30, 49},
  {cont__308_3, &frame__308_2, 652, 652, 9, 50},
  {cont__308_4, &frame__308_2, 653, 653, 16, 29},
  {cont__308_5, &frame__308_2, 653, 653, 9, 73},
  {cont__308_8, &frame__308_2, 654, 654, 32, 32},
  {entry__309_10, NULL, 669, 669, 37, 56},
  {cont__309_11, &frame__309_10, 669, 669, 37, 67},
  {cont__309_12, &frame__309_10, 669, 669, 27, 68},
  {cont__309_13, &frame__309_10, 670, 670, 39, 39},
  {entry__313_1, NULL, 697, 697, 17, 34},
  {cont__313_2, &frame__313_1, 697, 697, 36, 55},
  {cont__313_3, &frame__313_1, 697, 697, 11, 55},
  {cont__313_4, &frame__313_1, 697, 697, 55, 55},
  {entry__314_5, NULL, 705, 705, 17, 33},
  {cont__314_6, &frame__314_5, 705, 705, 11, 63},
  {cont__314_7, &frame__314_5, 705, 705, 63, 63},
  {entry__314_1, NULL, 704, 704, 12, 30},
  {cont__314_2, &frame__314_1, 704, 704, 12, 36},
  {cont__314_3, &frame__314_1, 704, 704, 12, 36},
  {cont__314_4, &frame__314_1, 704, 705, 9, 63},
  {cont__314_8, &frame__314_1, 706, 706, 30, 30},
  {entry__315_9, NULL, 715, 715, 17, 33},
  {cont__315_10, &frame__315_9, 715, 715, 11, 63},
  {cont__315_11, &frame__315_9, 715, 715, 63, 63},
  {entry__315_5, NULL, 714, 714, 12, 30},
  {cont__315_6, &frame__315_5, 714, 714, 12, 36},
  {cont__315_7, &frame__315_5, 714, 714, 12, 36},
  {cont__315_8, &frame__315_5, 714, 715, 9, 63},
  {cont__315_12, &frame__315_5, 718, 718, 25, 48},
  {cont__315_14, &frame__315_5, 719, 719, 27, 44},
  {cont__315_15, &frame__315_5, 721, 721, 26, 42},
  {cont__315_16, &frame__315_5, 722, 722, 33, 56},
  {cont__315_17, &frame__315_5, 723, 723, 30, 50},
  {cont__315_18, &frame__315_5, 723, 723, 52, 52},
  {entry__315_1, NULL, 713, 713, 20, 37},
  {cont__315_2, &frame__315_1, 713, 713, 10, 38},
  {cont__315_3, &frame__315_1, 713, 713, 10, 42},
  {cont__315_4, &frame__315_1, 713, 723, 7, 52},
  {cont__315_19, &frame__315_1, },
  {entry__318_1, NULL, 749, 749, 15, 32},
  {cont__318_2, &frame__318_1, 749, 749, 34, 60},
  {cont__318_3, &frame__318_1, 749, 749, 7, 60},
  {cont__318_4, &frame__318_1, 749, 749, 60, 60},
  {entry__322_1, NULL, 779, 779, 25, 56},
  {cont__322_3, &frame__322_1, 780, 780, 37, 58},
  {cont__322_5, &frame__322_1, 780, 780, 27, 59},
  {cont__322_6, &frame__322_1, 781, 781, 26, 42},
  {cont__322_7, &frame__322_1, 782, 782, 33, 56},
  {cont__322_8, &frame__322_1, 782, 782, 33, 58},
  {cont__322_9, &frame__322_1, 777, 782, 9, 59},
  {entry__323_1, NULL, 795, 795, 27, 36},
  {cont__323_2, &frame__323_1, 796, 796, 26, 42},
  {cont__323_3, &frame__323_1, 797, 797, 33, 56},
  {cont__323_4, &frame__323_1, 792, 797, 9, 57},
  {entry__330_9, NULL, 857, 857, 13, 51},
  {cont__330_10, &frame__330_9, 857, 857, 13, 51},
  {entry__330_12, NULL, 859, 859, 58, 58},
  {entry__330_2, NULL, 852, 852, 61, 61},
  {cont__330_3, &frame__330_2, 852, 852, 41, 58},
  {cont__330_4, &frame__330_2, 852, 852, 41, 62},
  {cont__330_5, &frame__330_2, 852, 852, 9, 63},
  {cont__330_6, &frame__330_2, 853, 853, 9, 53},
  {cont__330_7, &frame__330_2, 856, 856, 13, 42},
  {cont__330_8, &frame__330_2, 855, 857, 11, 50},
  {cont__330_11, &frame__330_2, 854, 859, 9, 59},
  {cont__330_13, &frame__330_2, },
  {entry__331_6, NULL, 869, 869, 11, 28},
  {cont__331_7, &frame__331_6, 869, 869, 28, 28},
  {entry__331_11, NULL, 877, 877, 47, 71},
  {cont__331_12, &frame__331_11, 877, 877, 44, 71},
  {entry__331_13, NULL, 877, 877, 74, 77},
  {entry__331_22, NULL, 884, 884, 41, 66},
  {cont__331_23, &frame__331_22, 884, 884, 41, 66},
  {entry__331_27, NULL, 889, 889, 21, 57},
  {entry__331_28, NULL, 890, 890, 21, 31},
  {entry__331_16, NULL, 881, 881, 17, 46},
  {cont__331_17, &frame__331_16, 882, 882, 17, 42},
  {cont__331_18, &frame__331_16, 883, 883, 20, 35},
  {cont__331_19, &frame__331_16, 883, 883, 17, 41},
  {cont__331_20, &frame__331_16, 884, 884, 20, 36},
  {cont__331_21, &frame__331_16, 884, 884, 20, 66},
  {cont__331_24, &frame__331_16, 884, 884, 17, 72},
  {cont__331_25, &frame__331_16, 888, 888, 21, 40},
  {cont__331_26, &frame__331_16, 886, 890, 17, 32},
  {cont__331_29, &frame__331_16, 892, 892, 17, 41},
  {cont__331_30, &frame__331_16, 896, 896, 35, 50},
  {cont__331_31, &frame__331_16, 898, 898, 40, 62},
  {cont__331_32, &frame__331_16, 899, 899, 34, 50},
  {cont__331_33, &frame__331_16, 900, 900, 41, 64},
  {cont__331_34, &frame__331_16, 901, 901, 38, 59},
  {cont__331_35, &frame__331_16, 902, 902, 17, 43},
  {cont__331_36, &frame__331_16, 903, 903, 20, 44},
  {cont__331_37, &frame__331_16, 903, 903, 20, 49},
  {cont__331_38, &frame__331_16, 903, 903, 17, 55},
  {entry__331_15, NULL, 880, 903, 15, 55},
  {cont__331_39, &frame__331_15, 903, 903, 55, 55},
  {entry__331_9, NULL, 877, 877, 18, 41},
  {cont__331_10, &frame__331_9, 876, 877, 13, 78},
  {cont__331_14, &frame__331_9, 879, 903, 13, 56},
  {cont__331_40, &frame__331_9, 904, 904, 13, 37},
  {cont__331_41, &frame__331_9, 905, 905, 13, 46},
  {cont__331_42, &frame__331_9, 905, 905, 46, 46},
  {entry__331_51, NULL, 908, 908, 52, 63},
  {cont__331_52, &frame__331_51, 908, 908, 49, 63},
  {entry__331_53, NULL, 908, 908, 66, 77},
  {entry__331_48, NULL, 908, 908, 26, 37},
  {cont__331_49, &frame__331_48, 908, 908, 42, 46},
  {cont__331_50, &frame__331_48, 908, 908, 39, 78},
  {cont__331_54, &frame__331_48, 908, 908, 13, 78},
  {entry__331_8, NULL, 871, 871, 11, 39},
  {cont__331_43, &frame__331_8, 872, 872, 32, 43},
  {cont__331_44, &frame__331_8, 872, 872, 11, 44},
  {cont__331_45, &frame__331_8, 873, 873, 33, 44},
  {cont__331_46, &frame__331_8, 873, 873, 11, 45},
  {cont__331_47, &frame__331_8, 907, 908, 11, 78},
  {cont__331_55, &frame__331_8, 909, 909, 11, 35},
  {cont__331_56, &frame__331_8, 909, 909, 35, 35},
  {entry__331_59, NULL, 911, 911, 41, 60},
  {cont__331_60, &frame__331_59, 911, 911, 36, 66},
  {cont__331_61, &frame__331_59, 911, 911, 67, 67},
  {entry__331_1, NULL, 864, 864, 7, 29},
  {cont__331_2, &frame__331_1, 865, 865, 7, 35},
  {cont__331_3, &frame__331_1, 866, 866, 7, 29},
  {cont__331_4, &frame__331_1, 868, 868, 9, 14},
  {cont__331_5, &frame__331_1, 867, 909, 7, 36},
  {cont__331_57, &frame__331_1, 910, 910, 10, 26},
  {cont__331_58, &frame__331_1, 910, 911, 7, 67},
  {cont__331_62, &frame__331_1, },
  {entry__340_1, NULL, 960, 960, 27, 36},
  {cont__340_2, &frame__340_1, 963, 963, 26, 42},
  {cont__340_3, &frame__340_1, 964, 964, 33, 56},
  {cont__340_4, &frame__340_1, 964, 964, 58, 58},
  {entry__348_1, NULL, 1004, 1004, 10, 26},
  {cont__348_2, &frame__348_1, 1005, 1005, 36, 36},
  {cont__348_3, &frame__348_1, 1005, 1005, 9, 33},
  {cont__348_4, &frame__348_1, 1005, 1005, 9, 37},
  {cont__348_5, &frame__348_1, 1003, 1005, 7, 62},
  {cont__348_6, &frame__348_1, 1005, 1005, 63, 63},
  {entry__349_7, NULL, 1019, 1019, 40, 66},
  {cont__349_8, &frame__349_7, 1019, 1019, 40, 66},
  {entry__349_10, NULL, 1020, 1020, 15, 38},
  {cont__349_11, &frame__349_10, 1020, 1020, 9, 49},
  {cont__349_12, &frame__349_10, 1022, 1022, 41, 63},
  {cont__349_13, &frame__349_10, 1021, 1021, 10, 26},
  {cont__349_14, &frame__349_10, 1021, 1021, 29, 29},
  {cont__349_15, &frame__349_10, 1021, 1021, 9, 30},
  {cont__349_16, &frame__349_10, 1022, 1022, 65, 65},
  {entry__349_1, NULL, 1017, 1017, 37, 37},
  {cont__349_2, &frame__349_1, 1017, 1017, 17, 34},
  {cont__349_3, &frame__349_1, 1017, 1017, 7, 38},
  {cont__349_4, &frame__349_1, 1018, 1018, 7, 41},
  {cont__349_5, &frame__349_1, 1019, 1019, 10, 35},
  {cont__349_6, &frame__349_1, 1019, 1019, 10, 66},
  {cont__349_9, &frame__349_1, 1019, 1022, 7, 65},
  {cont__349_17, &frame__349_1, },
  {entry__359_1, NULL, 1124, 1124, 9, 41},
  {entry__359_6, NULL, 1132, 1132, 9, 39},
  {cont__359_7, &frame__359_6, 1133, 1133, 9, 57},
  {cont__359_8, &frame__359_6, 1134, 1134, 39, 39},
  {cont__359_9, &frame__359_6, 1134, 1134, 9, 40},
  {cont__359_10, &frame__359_6, 1138, 1138, 42, 42},
  {cont__359_11, &frame__359_6, 1138, 1138, 13, 43},
  {cont__359_12, &frame__359_6, 1144, 1144, 29, 46},
  {cont__359_13, &frame__359_6, 1145, 1145, 36, 60},
  {cont__359_14, &frame__359_6, 1146, 1146, 34, 59},
  {cont__359_15, &frame__359_6, 1147, 1147, 32, 55},
  {cont__359_16, &frame__359_6, 1148, 1148, 28, 47},
  {cont__359_17, &frame__359_6, 1149, 1149, 35, 61},
  {cont__359_18, &frame__359_6, 1150, 1150, 32, 52},
  {cont__359_19, &frame__359_6, 1136, 1150, 9, 54},
  {cont__359_20, &frame__359_6, 1152, 1152, 9, 54},
  {entry__361_1, NULL, 1162, 1162, 11, 62},
  {cont__361_2, &frame__361_1, 1163, 1163, 42, 42},
  {entry__361_8, NULL, 1169, 1169, 21, 37},
  {cont__361_9, &frame__361_8, 1169, 1169, 21, 40},
  {cont__361_10, &frame__361_8, 1169, 1169, 21, 56},
  {cont__361_11, &frame__361_8, 1169, 1169, 58, 78},
  {cont__361_12, &frame__361_8, 1169, 1169, 13, 78},
  {cont__361_13, &frame__361_8, 1169, 1169, 21, 37},
  {cont__361_14, &frame__361_8, 1169, 1169, 21, 40},
  {cont__361_15, &frame__361_8, 1169, 1169, 20, 40},
  {cont__361_16, &frame__361_8, 1170, 1170, 44, 44},
  {entry__361_4, NULL, 1167, 1167, 24, 41},
  {cont__361_5, &frame__361_4, 1167, 1167, 11, 42},
  {cont__361_6, &frame__361_4, 1168, 1168, 14, 18},
  {cont__361_7, &frame__361_4, 1168, 1170, 11, 44},
  {cont__361_17, &frame__361_4, 1171, 1171, 11, 62},
  {cont__361_18, &frame__361_4, 1172, 1172, 50, 50},
  {entry__364_3, NULL, 1192, 1192, 26, 42},
  {cont__364_4, &frame__364_3, 1193, 1193, 33, 56},
  {cont__364_5, &frame__364_3, 1189, 1193, 9, 57},
  {entry__364_12, NULL, 1207, 1207, 11, 72},
  {entry__364_23, NULL, 1216, 1216, 35, 54},
  {cont__364_24, &frame__364_23, 1217, 1217, 20, 39},
  {cont__364_25, &frame__364_23, 1217, 1217, 20, 44},
  {cont__364_26, &frame__364_23, 1217, 1217, 17, 51},
  {cont__364_27, &frame__364_23, 1218, 1218, 51, 51},
  {cont__364_28, &frame__364_23, 1218, 1218, 32, 52},
  {cont__364_29, &frame__364_23, 1218, 1218, 17, 58},
  {cont__364_30, &frame__364_23, 1218, 1218, 58, 58},
  {entry__364_22, NULL, 1212, 1218, 15, 58},
  {entry__364_32, NULL, 1224, 1224, 52, 52},
  {cont__364_33, &frame__364_32, 1224, 1224, 55, 55},
  {cont__364_34, &frame__364_32, 1224, 1224, 35, 56},
  {cont__364_35, &frame__364_32, 1225, 1225, 20, 39},
  {cont__364_36, &frame__364_32, 1225, 1225, 20, 44},
  {cont__364_37, &frame__364_32, 1225, 1225, 17, 51},
  {cont__364_38, &frame__364_32, 1226, 1226, 52, 52},
  {cont__364_39, &frame__364_32, 1226, 1226, 33, 53},
  {cont__364_40, &frame__364_32, 1226, 1226, 17, 59},
  {cont__364_41, &frame__364_32, 1226, 1226, 59, 59},
  {entry__364_31, NULL, 1220, 1226, 15, 59},
  {entry__364_17, NULL, 1209, 1209, 11, 35},
  {cont__364_18, &frame__364_17, 1211, 1211, 24, 39},
  {cont__364_19, &frame__364_17, 1211, 1211, 13, 40},
  {cont__364_20, &frame__364_17, 1211, 1211, 13, 60},
  {cont__364_21, &frame__364_17, 1210, 1226, 11, 61},
  {entry__364_8, NULL, 1205, 1205, 9, 38},
  {cont__364_9, &frame__364_8, 1206, 1206, 12, 31},
  {cont__364_10, &frame__364_8, 1206, 1206, 12, 35},
  {cont__364_11, &frame__364_8, 1206, 1207, 9, 72},
  {cont__364_14, &frame__364_8, 1208, 1208, 12, 31},
  {cont__364_15, &frame__364_8, 1208, 1208, 12, 35},
  {cont__364_16, &frame__364_8, 1208, 1226, 9, 62},
  {cont__364_42, &frame__364_8, 1226, 1226, 62, 62},
  {entry__365_10, NULL, 1249, 1249, 48, 65},
  {cont__365_11, &frame__365_10, 1249, 1249, 70, 70},
  {cont__365_12, &frame__365_10, 1249, 1249, 42, 71},
  {cont__365_13, &frame__365_10, 1250, 1250, 60, 60},
  {cont__365_14, &frame__365_10, 1250, 1250, 40, 57},
  {cont__365_15, &frame__365_10, 1250, 1250, 40, 61},
  {cont__365_16, &frame__365_10, 1250, 1250, 35, 62},
  {cont__365_17, &frame__365_10, 1246, 1250, 17, 63},
  {entry__372_1, NULL, 1318, 1318, 30, 30},
  {entry__389_10, NULL, 1463, 1463, 19, 76},
  {entry__389_5, NULL, 1461, 1461, 31, 55},
  {cont__389_6, &frame__389_5, 1461, 1461, 17, 58},
  {cont__389_7, &frame__389_5, 1462, 1462, 20, 44},
  {cont__389_8, &frame__389_5, 1462, 1462, 20, 55},
  {cont__389_9, &frame__389_5, 1462, 1463, 17, 76},
  {cont__389_12, &frame__389_5, 1465, 1465, 18, 41},
  {cont__389_13, &frame__389_5, 1465, 1465, 17, 44},
  {cont__389_14, &frame__389_5, 1465, 1465, 56, 56},
  {entry__397_5, NULL, 1527, 1527, 15, 77},
  {entry__397_2, NULL, 1526, 1526, 16, 33},
  {cont__397_3, &frame__397_2, 1526, 1526, 16, 42},
  {cont__397_4, &frame__397_2, 1526, 1527, 13, 77},
  {cont__397_7, &frame__397_2, 1528, 1528, 13, 19}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__original_remark_lines_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__original_remark_lines_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__original_remark_lines_of, attr);
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
  "sim2c",
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
  allocate_initialized_frame_gc(0, 21);
  // 94: $types::syntax_error types::grammar_object
  initialize_maybe_future(var.types__syntax_error, get__types__grammar_object());
  // 104: $types::unexpected_input_error types::grammar_object
  initialize_maybe_future(var.types__unexpected_input_error, get__types__grammar_object());
  // 133: $types::print types::grammar_object
  initialize_maybe_future(var.types__print, get__types__grammar_object());
  // 145: $dump_stream types::grammar_object
  initialize_maybe_future(var._dump_stream, get__types__grammar_object());
  // 177: $dump types::grammar_object
  initialize_maybe_future(var._dump, get__types__grammar_object());
  // 183: $dump3 types::grammar_object
  initialize_maybe_future(var._dump3, get__types__grammar_object());
  // 189: $dump5 types::grammar_object
  initialize_maybe_future(var._dump5, get__types__grammar_object());
  // 204: "*" = 14
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccb;
  arguments->slots[1] = number__14;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_2;
}
static void cont__236_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 205: "/" = 14
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cce;
  arguments->slots[1] = number__14;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_4;
}
static void cont__236_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 206: "+" = 13
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cca;
  arguments->slots[1] = number__13;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_6;
}
static void cont__236_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 207: "-" = 13
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccc;
  arguments->slots[1] = number__13;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_8;
}
static void cont__236_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 208: "<<" = 12
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6e82bf9;
  arguments->slots[1] = number__12;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_10;
}
static void cont__236_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 209: ">>" = 12
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6f82bfb;
  arguments->slots[1] = number__12;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_12;
}
static void cont__236_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 210: "&" = 11
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc7;
  arguments->slots[1] = number__11;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_14;
}
static void cont__236_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 211: "^" = 10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cbf;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_15;
}
static void cont__236_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 212: "|" = 9
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9c9d;
  arguments->slots[1] = number__9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_17;
}
static void cont__236_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 213: "<=" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6e82bf8;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_19;
}
static void cont__236_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 214: "<" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdd;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_21;
}
static void cont__236_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 215: ">=" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6f82bf8;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_23;
}
static void cont__236_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 216: ">" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdf;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_25;
}
static void cont__236_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 217: "==" = 7
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6e02bf8;
  arguments->slots[1] = number__7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_27;
}
static void cont__236_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 218: "!=" = 7
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6002bf8;
  arguments->slots[1] = number__7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_29;
}
static void cont__236_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 219: "&&" = 5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6382be3;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_31;
}
static void cont__236_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 220: "||" = 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4e82bb9;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_33;
}
static void cont__236_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  // 221: ".." = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6782beb;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_35;
}
static void cont__236_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 222: "," = 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccd;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_37;
}
static void cont__236_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__19 */ = arguments->slots[0];
  // 223: "=" = 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdc;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__236_39;
}
static void cont__236_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__20 */ = arguments->slots[0];
  // 202: $precedence_table
  // 203:   table
  // 204:     "*" = 14
  // 205:     "/" = 14
  // 206:     "+" = 13
  // 207:     "-" = 13
  // 208:     "<<" = 12
  // 209:     ">>" = 12
  // 210:     "&" = 11
  // 211:     "^" = 10
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
  frame->cont = cont__236_40;
}
static void cont__236_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._precedence_table, arguments->slots[0]);
  // 240: %within_inline_expression false
  initialize_maybe_future(get__within_inline_expression(), get__false());
  // 241: $types::inline types::grammar_object
  initialize_maybe_future(var.types__inline, get__types__grammar_object());
  // 249: $NOT_INLINE
  // 250:   check_node
  // 251:     : (_node stream)
  // 252:       if within_inline_expression:
  // 253:         ParseError stream "
  // 254:           ")" expected@
  // 255:       -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__246_1;
  result_count = 1;
  myself = get__check_node();
  func = myself->type;
  frame->cont = cont__246_5;
}
static void entry__246_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 252: ... :
  // 253:   ParseError stream "
  // 254:     ")" expected@
  frame->slots[2] /* temp__1 */ = create_closure(entry__246_2, 0);
  // 252: if within_inline_expression:
  // 253:   ParseError stream "
  // 254:     ")" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__within_inline_expression();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__246_4;
}
static void entry__246_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 253: ParseError stream "
  // 254:   ")" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__ccbf6d451aa8563f;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__246_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 255: -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__246_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NOT_INLINE, arguments->slots[0]);
  // 257: ... followed_by(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__247_1;
}
static void cont__247_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 257: $NEWLINE followed_by(newline), NOT_INLINE, newline
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__newline();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__247_2;
}
static void cont__247_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEWLINE, arguments->slots[0]);
  // 258: ... followed_by(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__248_1;
}
static void cont__248_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 258: $INDENT followed_by(indent_marker), NOT_INLINE, indent_marker
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__indent_marker();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__248_2;
}
static void cont__248_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INDENT, arguments->slots[0]);
  // 259: ... followed_by(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__249_1;
}
static void cont__249_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 259: $OUTDENT followed_by(outdent_marker), NOT_INLINE, outdent_marker
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__outdent_marker();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__249_2;
}
static void cont__249_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OUTDENT, arguments->slots[0]);
  // 260: ... followed_by('#')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__35;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__250_1;
}
static void cont__250_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 260: $HASHTAG followed_by('#'), NOT_INLINE, '#'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = character__35;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__250_2;
}
static void cont__250_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._HASHTAG, arguments->slots[0]);
  // 268: $ENUMERATE
  // 269:   modify_node
  // 270:     : (&node)
  // 271:       #
  // 272:         On a first look there seem to be too many enumeration numbers used,
  // 273:         but single nested nodes are flattened later on and there is no need
  // 274:         for enumeration numbers to be dense.
  // 275:       
  // 276:       inc &enumeration_count
  // 277:       !node.enumeration_no_of enumeration_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__252_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__252_3;
}
static void entry__252_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 276: inc &enumeration_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__enumeration_count();
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__252_2;
}
static void cont__252_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__enumeration_count(arguments->slots[0]);
  // 277: !node.enumeration_no_of enumeration_count
  frame->slots[1] /* temp__1 */ = get__enumeration_count();
  // 277: !node.enumeration_no_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__enumeration_no_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__252_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ENUMERATE, arguments->slots[0]);
  // 279: $MAKE_A_DESTINATION
  // 280:   modify_node
  // 281:     : (&node)
  // 282:       !node.is_a_destination true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__253_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__253_2;
}
static void entry__253_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 282: !node.is_a_destination true
  frame->slots[1] /* temp__1 */ = get__true();
  // 282: !node.is_a_destination
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__253_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAKE_A_DESTINATION, arguments->slots[0]);
  // 290: $sim2c::WHITESPACE many(' ')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__256_1;
}
static void cont__256_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.sim2c__WHITESPACE, arguments->slots[0]);
  // 291: ... followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__257_1;
}
static void cont__257_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 291: $SEPARATOR alt(sim2c::WHITESPACE followed_by(':'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__257_2;
}
static void cont__257_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SEPARATOR, arguments->slots[0]);
  // 292: $NEWLINES many(NEWLINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__258_1;
}
static void cont__258_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEWLINES, arguments->slots[0]);
  // 293: $NEXT_LINE ARGUMENT_LINE_END_REMARK, NEWLINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_LINE_END_REMARK;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__259_1;
}
static void cont__259_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEXT_LINE, arguments->slots[0]);
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
  arguments->slots[0] = func__260_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__260_3;
}
static void entry__260_1(void) {
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
  frame->cont = cont__260_2;
}
static void cont__260_2(void) {
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
  // 303: !node.fragment_of current_fragment
  frame->slots[2] /* temp__1 */ = get__current_fragment();
  // 303: !node.fragment_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__260_3(void) {
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
  arguments->slots[0] = func__261_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__261_4;
}
static void entry__261_1(void) {
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
  frame->cont = cont__261_2;
}
static void cont__261_2(void) {
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
  frame->cont = cont__261_3;
}
static void cont__261_3(void) {
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
  // 313: !node.fragment_of current_fragment
  frame->slots[2] /* temp__1 */ = get__current_fragment();
  // 313: !node.fragment_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__261_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_POSITION_MINUS_1, arguments->slots[0]);
  // 315: $STORE_POSITION_MINUS_2
  // 316:   modify_node
  // 317:     :
  // 318:       (
  // 319:         &node
  // 320:         stream
  // 321:       )
  // 322:       !node.source_position_of length_of(stream)+2
  // 323:       !node.fragment_of current_fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__262_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__262_4;
}
static void entry__262_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 322: ... length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__262_2;
}
static void cont__262_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 322: !node.source_position_of length_of(stream)+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__262_3;
}
static void cont__262_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 322: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 323: !node.fragment_of current_fragment
  frame->slots[2] /* temp__1 */ = get__current_fragment();
  // 323: !node.fragment_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__262_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_POSITION_MINUS_2, arguments->slots[0]);
  // 325: $STORE_END_POSITION
  // 326:   modify_node
  // 327:     :
  // 328:       (
  // 329:         &node
  // 330:         stream
  // 331:       )
  // 332:       !node.end_position_of length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__263_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__263_3;
}
static void entry__263_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 332: !node.end_position_of length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__263_2;
}
static void cont__263_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 332: !node.end_position_of
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
static void cont__263_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_END_POSITION, arguments->slots[0]);
  // 336: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__264_1;
}
static void cont__264_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 338: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__264_2;
}
static void cont__264_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 342: modify_node
  // 343:   : (&node)
  // 344:     !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__264_3;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__264_5;
}
static void entry__264_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 344: !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__264_4;
}
static void cont__264_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 344: !node.namespace_of
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
static void cont__264_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 345: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__264_6;
}
static void cont__264_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 340: sequence
  // 341:   "::"
  // 342:   modify_node
  // 343:     : (&node)
  // 344:       !node.namespace_of node.name_of
  // 345:   capture(name_of NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__264_8;
}
static void cont__264_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 339: optional
  // 340:   sequence
  // 341:     "::"
  // 342:     modify_node
  // 343:       : (&node)
  // 344:         !node.namespace_of node.name_of
  // 345:     capture(name_of NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__264_9;
}
static void cont__264_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 334: $IDENTIFIER
  // 335:   sequence
  // 336:     set_node(identifier)
  // 337:     STORE_POSITION
  // 338:     capture(name_of NAME)
  // 339:     optional
  // 340:       sequence
  // 341:         "::"
  // 342:         modify_node
  // 343:           : (&node)
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
  frame->cont = cont__264_10;
}
static void cont__264_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._IDENTIFIER, arguments->slots[0]);
  // 350: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 352: optional(NOT_USED)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NOT_USED;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__265_2;
}
static void cont__265_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 353: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__265_3;
}
static void cont__265_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 357: modify_node
  // 358:   : (&node)
  // 359:     if node.is_not_used:
  // 360:       SyntaxError node "namespace must not start with an underscore"
  // 361:     !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__265_4;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__265_10;
}
static void entry__265_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 359: ... node.is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_not_used();
  func = myself->type;
  frame->cont = cont__265_5;
}
static void cont__265_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 359: ... :
  // 360:   SyntaxError node "namespace must not start with an underscore"
  frame->slots[2] /* temp__2 */ = create_closure(entry__265_6, 0);
  // 359: if node.is_not_used:
  // 360:   SyntaxError node "namespace must not start with an underscore"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__265_8;
}
static void entry__265_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 360: SyntaxError node "namespace must not start with an underscore"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  arguments->slots[1] = string__958c1dda41e5a79c;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__265_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 361: !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__265_9;
}
static void cont__265_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 361: !node.namespace_of
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
static void cont__265_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 362: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__265_11;
}
static void cont__265_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 355: sequence
  // 356:   "::"
  // 357:   modify_node
  // 358:     : (&node)
  // 359:       if node.is_not_used:
  // 360:         SyntaxError node "namespace must not start with an underscore"
  // 361:       !node.namespace_of node.name_of
  // 362:   capture(name_of NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__265_12;
}
static void cont__265_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 354: optional
  // 355:   sequence
  // 356:     "::"
  // 357:     modify_node
  // 358:       : (&node)
  // 359:         if node.is_not_used:
  // 360:           SyntaxError node "namespace must not start with an underscore"
  // 361:         !node.namespace_of node.name_of
  // 362:     capture(name_of NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__265_13;
}
static void cont__265_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 348: $DEFINE_IDENTIFIER
  // 349:   sequence
  // 350:     set_node(identifier)
  // 351:     STORE_POSITION
  // 352:     optional(NOT_USED)
  // 353:     capture(name_of NAME)
  // 354:     optional
  // 355:       sequence
  // 356:         "::"
  // 357:         modify_node
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
  frame->cont = cont__265_14;
}
static void cont__265_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_IDENTIFIER, arguments->slots[0]);
  // 367: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 369: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__266_2;
}
static void cont__266_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 370: expect("::")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__266_3;
}
static void cont__266_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 371: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__266_4;
}
static void cont__266_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 365: $NAMESPACED_IDENTIFIER
  // 366:   sequence
  // 367:     set_node(identifier)
  // 368:     STORE_POSITION
  // 369:     capture(namespace_of NAME)
  // 370:     expect("::")
  // 371:     capture(name_of NAME)
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
  frame->cont = cont__266_5;
}
static void cont__266_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMESPACED_IDENTIFIER, arguments->slots[0]);
  // 376: ... optional("./")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6782bea;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__267_2;
}
static void cont__267_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 376: ... "/", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cce;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__267_3;
}
static void cont__267_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 376: ... some("/", NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__267_4;
}
static void cont__267_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 376: $FILENAME optional("./"), NAME, some("/", NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__267_5;
}
static void cont__267_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FILENAME, arguments->slots[0]);
  // 381: set_node(require_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__require_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__268_1;
}
static void cont__268_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 384: capture(node::filename_of FILENAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filename_of();
  arguments->slots[1] = var._FILENAME;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__268_2;
}
static void cont__268_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 387: inspect_node
  // 388:   : (node stream)
  // 389:     $filename node::filename_of(node)
  // 390:     if required_modules(filename).is_defined:
  // 391:       ParseError stream "
  // 392:         the module "@(filename)" is required twice@
  // 393:     !required_modules(filename) node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__268_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__268_13;
}
static void entry__268_3(void) {
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
  // 389: $filename node::filename_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filename_of();
  func = myself->type;
  frame->cont = cont__268_4;
}
static void cont__268_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 390: ... required_modules(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__268_5;
}
static void cont__268_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 390: ... required_modules(filename).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__268_6;
}
static void cont__268_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 390: ... :
  // 391:   ParseError stream "
  // 392:     the module "@(filename)" is required twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__268_7, 0);
  // 390: if required_modules(filename).is_defined:
  // 391:   ParseError stream "
  // 392:     the module "@(filename)" is required twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__268_11;
}
static void entry__268_7(void) {
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
  // 391: ... "
  // 392:   the module "@(filename)" is required twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__92e1510f182d5769;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__fd365ba9213c93f1;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__268_10;
}
static void cont__268_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 391: ParseError stream "
  // 392:   the module "@(filename)" is required twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__268_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 393: !required_modules(filename) node
  frame->slots[3] /* temp__1 */ = frame->slots[0] /* node */;
  // 393: !required_modules(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__268_12;
}
static void cont__268_12(void) {
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
static void cont__268_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 378: $REQUIRE
  // 379:   sequence
  // 380:     "<require"
  // 381:     set_node(require_instruction)
  // 382:     STORE_POSITION
  // 383:     sim2c::WHITESPACE
  // 384:     capture(node::filename_of FILENAME)
  // 385:     ">"
  // 386:     STORE_END_POSITION
  // 387:     inspect_node
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = string__44dcaf9484448bc5;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._STORE_POSITION;
  arguments->slots[3] = var.sim2c__WHITESPACE;
  arguments->slots[4] = frame->slots[1] /* temp__2 */;
  arguments->slots[5] = string__578a5af303e9cdf;
  arguments->slots[6] = var._STORE_END_POSITION;
  arguments->slots[7] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__268_15;
}
static void cont__268_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REQUIRE, arguments->slots[0]);
  // 399: set_node(namespace_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__namespace_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__269_1;
}
static void cont__269_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 400: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__269_2;
}
static void cont__269_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 403: infix_operator("=")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cdc;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__269_3;
}
static void cont__269_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 404: modify_node
  // 405:   : (&node)
  // 406:     !node.namespace_alias_of node.namespace_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__269_4;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__269_6;
}
static void entry__269_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 406: !node.namespace_alias_of node.namespace_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__269_5;
}
static void cont__269_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 406: !node.namespace_alias_of
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
static void cont__269_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 407: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__269_7;
}
static void cont__269_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 402: sequence
  // 403:   infix_operator("=")
  // 404:   modify_node
  // 405:     : (&node)
  // 406:       !node.namespace_alias_of node.namespace_of
  // 407:   capture(namespace_of NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__269_8;
}
static void cont__269_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 401: optional
  // 402:   sequence
  // 403:     infix_operator("=")
  // 404:     modify_node
  // 405:       : (&node)
  // 406:         !node.namespace_alias_of node.namespace_of
  // 407:     capture(namespace_of NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__269_9;
}
static void cont__269_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 409: inspect_node
  // 410:   : (node stream)
  // 411:     $namespace namespace_of(node)
  // 412:     $alias namespace_alias_of(node)
  // 413:     if
  // 414:       alias.is_defined:
  // 415:         if namespace_mappings(alias).is_defined:
  // 416:           ParseError stream "
  // 417:             the namespace alias "@(alias)" is defined twice@
  // 418:         !namespace_mappings(alias) namespace
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__269_10;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__269_30;
}
static void entry__269_14(void) {
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
  // 415: ... namespace_mappings(alias)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alias */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__269_15;
}
static void cont__269_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 415: ... namespace_mappings(alias).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__269_16;
}
static void cont__269_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 415: ... :
  // 416:   ParseError stream "
  // 417:     the namespace alias "@(alias)" is defined twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__269_17, 0);
  // 415: if namespace_mappings(alias).is_defined:
  // 416:   ParseError stream "
  // 417:     the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__269_21;
}
static void entry__269_17(void) {
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
  // 416: ... "
  // 417:   the namespace alias "@(alias)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__e13e5990aea4c8f3;
  arguments->slots[1] = frame->slots[1] /* alias */;
  arguments->slots[2] = string__54767964cc2066c4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__269_20;
}
static void cont__269_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 416: ParseError stream "
  // 417:   the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__269_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 418: !namespace_mappings(alias) namespace
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* namespace */;
  // 418: !namespace_mappings(alias)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alias */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__269_22;
}
static void cont__269_22(void) {
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
static void entry__269_23(void) {
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
  // 420: ... defined_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__defined_namespaces();
  func = myself->type;
  frame->cont = cont__269_24;
}
static void cont__269_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 420: ... :
  // 421:   ParseError stream "
  // 422:     the namespace "@(namespace)" is defined twice@
  frame->slots[3] /* temp__2 */ = create_closure(entry__269_25, 0);
  // 420: if defined_namespaces(namespace):
  // 421:   ParseError stream "
  // 422:     the namespace "@(namespace)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__269_28;
}
static void entry__269_25(void) {
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
  // 421: ... "
  // 422:   the namespace "@(namespace)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9159abe89634488c;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__54767964cc2066c4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__269_27;
}
static void cont__269_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 421: ParseError stream "
  // 422:   the namespace "@(namespace)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__269_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 423: !defined_namespaces(namespace) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 423: !defined_namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__defined_namespaces();
  func = myself->type;
  frame->cont = cont__269_29;
}
static void cont__269_29(void) {
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
static void entry__269_10(void) {
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
  // 411: $namespace namespace_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__269_11;
}
static void cont__269_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 412: $alias namespace_alias_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_alias_of();
  func = myself->type;
  frame->cont = cont__269_12;
}
static void cont__269_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* alias */, arguments->slots[0]);
  // 414: alias.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* alias */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__269_13;
}
static void cont__269_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 414: ... :
  // 415:   if namespace_mappings(alias).is_defined:
  // 416:     ParseError stream "
  // 417:       the namespace alias "@(alias)" is defined twice@
  // 418:   !namespace_mappings(alias) namespace
  frame->slots[5] /* temp__2 */ = create_closure(entry__269_14, 0);
  // 419: :
  // 420:   if defined_namespaces(namespace):
  // 421:     ParseError stream "
  // 422:       the namespace "@(namespace)" is defined twice@
  // 423:   !defined_namespaces(namespace) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__269_23, 0);
  // 413: if
  // 414:   alias.is_defined:
  // 415:     if namespace_mappings(alias).is_defined:
  // 416:       ParseError stream "
  // 417:         the namespace alias "@(alias)" is defined twice@
  // 418:     !namespace_mappings(alias) namespace
  // 419:   :
  // 420:     if defined_namespaces(namespace):
  // 421:       ParseError stream "
  // 422:         the namespace "@(namespace)" is defined twice@
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
static void cont__269_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 395: $NAMESPACE
  // 396:   sequence
  // 397:     "<namespace"
  // 398:     sim2c::WHITESPACE
  // 399:     set_node(namespace_instruction)
  // 400:     capture(namespace_of NAME)
  // 401:     optional
  // 402:       sequence
  // 403:         infix_operator("=")
  // 404:         modify_node
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__1552f059283245c4;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = frame->slots[2] /* temp__3 */;
  arguments->slots[5] = string__578a5af303e9cdf;
  arguments->slots[6] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__269_32;
}
static void cont__269_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMESPACE, arguments->slots[0]);
  // 429: set_node(using_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__using_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__270_1;
}
static void cont__270_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 430: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__270_2;
}
static void cont__270_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 432: inspect_node
  // 433:   : (node stream)
  // 434:     $namespace namespace_of(node)
  // 435:     if used_namespaces(namespace):
  // 436:       ParseError stream "
  // 437:         the namespace "@(namespace)" is used twice@
  // 438:     !used_namespaces(namespace) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__270_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__270_11;
}
static void entry__270_3(void) {
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
  // 434: $namespace namespace_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__270_4;
}
static void cont__270_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 435: ... used_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__270_5;
}
static void cont__270_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 435: ... :
  // 436:   ParseError stream "
  // 437:     the namespace "@(namespace)" is used twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__270_6, 0);
  // 435: if used_namespaces(namespace):
  // 436:   ParseError stream "
  // 437:     the namespace "@(namespace)" is used twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__270_9;
}
static void entry__270_6(void) {
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
  // 436: ... "
  // 437:   the namespace "@(namespace)" is used twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9159abe89634488c;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__1d0508008a8a40d8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__270_8;
}
static void cont__270_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 436: ParseError stream "
  // 437:   the namespace "@(namespace)" is used twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__270_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 438: !used_namespaces(namespace) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 438: !used_namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__270_10;
}
static void cont__270_10(void) {
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
static void cont__270_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 425: $USING
  // 426:   sequence
  // 427:     "<using"
  // 428:     sim2c::WHITESPACE
  // 429:     set_node(using_instruction)
  // 430:     capture(namespace_of NAME)
  // 431:     ">"
  // 432:     inspect_node
  // 433:       : (node stream)
  // 434:         $namespace namespace_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__7e1f542e81cb02b0;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9cdf;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__270_13;
}
static void cont__270_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._USING, arguments->slots[0]);
  // 440: ... alt(LETTER DIGIT '_' '.')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  arguments->slots[1] = get__DIGIT();
  arguments->slots[2] = character__95;
  arguments->slots[3] = character__46;
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
  // 440: $BASENAME many(alt(LETTER DIGIT '_' '.'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__271_2;
}
static void cont__271_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BASENAME, arguments->slots[0]);
  // 441: ... some("../")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa733c15f596be3;
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
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 441: ... alt('/' "./" some("../"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__2d7981f4e6782bea;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__272_3;
}
static void cont__272_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 441: ... '/', BASENAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = var._BASENAME;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__272_4;
}
static void cont__272_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 441: ... some('/', BASENAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__272_5;
}
static void cont__272_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 441: $C_FILENAME alt('/' "./" some("../")), BASENAME, some('/', BASENAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._BASENAME;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__272_6;
}
static void cont__272_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_FILENAME, arguments->slots[0]);
  // 447: set_node(include_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__include_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__273_1;
}
static void cont__273_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 448: capture(node::filename_of C_FILENAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filename_of();
  arguments->slots[1] = var._C_FILENAME;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__273_2;
}
static void cont__273_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 450: inspect_node
  // 451:   : (node stream)
  // 452:     $filename node::filename_of(node)
  // 453:     if included_files(filename):
  // 454:       ParseError stream "
  // 455:         the file "@(filename)" is included twice@
  // 456:     !included_files(filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__273_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__273_12;
}
static void entry__273_3(void) {
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
  // 452: $filename node::filename_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filename_of();
  func = myself->type;
  frame->cont = cont__273_4;
}
static void cont__273_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 453: ... included_files(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__273_5;
}
static void cont__273_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 453: ... :
  // 454:   ParseError stream "
  // 455:     the file "@(filename)" is included twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__273_6, 0);
  // 453: if included_files(filename):
  // 454:   ParseError stream "
  // 455:     the file "@(filename)" is included twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__273_10;
}
static void entry__273_6(void) {
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
  // 454: ... "
  // 455:   the file "@(filename)" is included twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2c64b158ac2be503;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__b0b6bb19371893f7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__273_9;
}
static void cont__273_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 454: ParseError stream "
  // 455:   the file "@(filename)" is included twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__273_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 456: !included_files(filename) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 456: !included_files(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__273_11;
}
static void cont__273_11(void) {
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
static void cont__273_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 443: $INCLUDE
  // 444:   sequence
  // 445:     "<include"
  // 446:     sim2c::WHITESPACE
  // 447:     set_node(include_instruction)
  // 448:     capture(node::filename_of C_FILENAME)
  // 449:     ">"
  // 450:     inspect_node
  // 451:       : (node stream)
  // 452:         $filename node::filename_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__76b0a89104f5abc5;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9cdf;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__273_14;
}
static void cont__273_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INCLUDE, arguments->slots[0]);
  // 462: set_node(link_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__link_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__274_1;
}
static void cont__274_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 463: capture(node::filename_of C_FILENAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filename_of();
  arguments->slots[1] = var._C_FILENAME;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__274_2;
}
static void cont__274_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 465: inspect_node
  // 466:   : (node stream)
  // 467:     $filename node::filename_of(node)
  // 468:     if linked_libraries(filename):
  // 469:       ParseError stream "
  // 470:         the library "@(filename)" is linked twice@
  // 471:     !linked_libraries(filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__274_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__274_12;
}
static void entry__274_3(void) {
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
  // 467: $filename node::filename_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filename_of();
  func = myself->type;
  frame->cont = cont__274_4;
}
static void cont__274_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 468: ... linked_libraries(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__linked_libraries();
  func = myself->type;
  frame->cont = cont__274_5;
}
static void cont__274_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 468: ... :
  // 469:   ParseError stream "
  // 470:     the library "@(filename)" is linked twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__274_6, 0);
  // 468: if linked_libraries(filename):
  // 469:   ParseError stream "
  // 470:     the library "@(filename)" is linked twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__274_10;
}
static void entry__274_6(void) {
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
  // 469: ... "
  // 470:   the library "@(filename)" is linked twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__a660d7293a5c47e8;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__ad06d2ccd69d8e1;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__274_9;
}
static void cont__274_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 469: ParseError stream "
  // 470:   the library "@(filename)" is linked twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__274_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 471: !linked_libraries(filename) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 471: !linked_libraries(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__linked_libraries();
  func = myself->type;
  frame->cont = cont__274_11;
}
static void cont__274_11(void) {
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
static void cont__274_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 458: $LINK
  // 459:   sequence
  // 460:     "<link"
  // 461:     sim2c::WHITESPACE
  // 462:     set_node(link_instruction)
  // 463:     capture(node::filename_of C_FILENAME)
  // 464:     ">"
  // 465:     inspect_node
  // 466:       : (node stream)
  // 467:         $filename node::filename_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__525ae943eabdd03c;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9cdf;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__274_14;
}
static void cont__274_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINK, arguments->slots[0]);
  // 473: ... alt(LETTER DIGIT '_' '.' '*' '?')
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
  frame->cont = cont__275_1;
}
static void cont__275_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 473: $MASK many(alt(LETTER DIGIT '_' '.' '*' '?'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__275_2;
}
static void cont__275_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MASK, arguments->slots[0]);
  // 474: ... some("../")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa733c15f596be3;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__276_1;
}
static void cont__276_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 474: ... alt('/' "./" some("../"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__2d7981f4e6782bea;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__276_2;
}
static void cont__276_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 474: ... '/', MASK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = var._MASK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__276_3;
}
static void cont__276_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 474: ... some('/', MASK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__276_4;
}
static void cont__276_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 474: $FILEMASK alt('/' "./" some("../")), MASK, some('/', MASK)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._MASK;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__276_5;
}
static void cont__276_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FILEMASK, arguments->slots[0]);
  // 480: set_node(data_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__data_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__277_1;
}
static void cont__277_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 481: capture(node::filemask_of FILEMASK)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filemask_of();
  arguments->slots[1] = var._FILEMASK;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__277_2;
}
static void cont__277_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 483: inspect_node
  // 484:   : (node stream)
  // 485:     $filemask node::filemask_of(node)
  // 486:     if dependent_data(filemask):
  // 487:       ParseError stream "
  // 488:         the data dependency "@(filemask)" is defined twice@
  // 489:     !dependent_data(filemask) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__277_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__277_11;
}
static void entry__277_3(void) {
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
  // 485: $filemask node::filemask_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filemask_of();
  func = myself->type;
  frame->cont = cont__277_4;
}
static void cont__277_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filemask */, arguments->slots[0]);
  // 486: ... dependent_data(filemask)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filemask */;
  result_count = 1;
  myself = get__dependent_data();
  func = myself->type;
  frame->cont = cont__277_5;
}
static void cont__277_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 486: ... :
  // 487:   ParseError stream "
  // 488:     the data dependency "@(filemask)" is defined twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__277_6, 0);
  // 486: if dependent_data(filemask):
  // 487:   ParseError stream "
  // 488:     the data dependency "@(filemask)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__277_9;
}
static void entry__277_6(void) {
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
  // 487: ... "
  // 488:   the data dependency "@(filemask)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__e720c6242e8cd532;
  arguments->slots[1] = frame->slots[1] /* filemask */;
  arguments->slots[2] = string__54767964cc2066c4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__277_8;
}
static void cont__277_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 487: ParseError stream "
  // 488:   the data dependency "@(filemask)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__277_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 489: !dependent_data(filemask) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 489: !dependent_data(filemask)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filemask */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__dependent_data();
  func = myself->type;
  frame->cont = cont__277_10;
}
static void cont__277_10(void) {
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
static void cont__277_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 476: $DATA
  // 477:   sequence
  // 478:     "<data"
  // 479:     sim2c::WHITESPACE
  // 480:     set_node(data_instruction)
  // 481:     capture(node::filemask_of FILEMASK)
  // 482:     ">"
  // 483:     inspect_node
  // 484:       : (node stream)
  // 485:         $filemask node::filemask_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__425aeb43ea6dd036;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__578a5af303e9cdf;
  arguments->slots[5] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__277_13;
}
static void cont__277_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DATA, arguments->slots[0]);
  // 493: alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
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
  frame->cont = cont__278_1;
}
static void cont__278_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 494: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__278_2;
}
static void cont__278_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 494: ... NEXT_LINE_REMARK, expect(outdent_marker)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE_REMARK;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__278_3;
}
static void cont__278_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 494: ... alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEW_LINE_END_REMARK;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__278_4;
}
static void cont__278_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 494: optional(alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__278_5;
}
static void cont__278_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 491: $META_INSTRUCTION
  // 492:   sequence
  // 493:     alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
  // 494:     optional(alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__278_6;
}
static void cont__278_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._META_INSTRUCTION, arguments->slots[0]);
  // 499: ... some(PRINTABLE_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__PRINTABLE_CHARACTER();
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__279_1;
}
static void cont__279_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 499: $REMARK_LINE multi_capture(remark_lines_of some(PRINTABLE_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__remark_lines_of();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__279_2;
}
static void cont__279_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_LINE, arguments->slots[0]);
  // 504: ... interleaved(REMARK_LINE NEWLINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_LINE;
  arguments->slots[1] = var._NEWLINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__280_1;
}
static void cont__280_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 504: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__280_2;
}
static void cont__280_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 504: ... INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__280_3;
}
static void cont__280_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 504: optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__280_4;
}
static void cont__280_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 501: $REMARK_LINES
  // 502:   sequence
  // 503:     REMARK_LINE
  // 504:     optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_LINE;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__280_5;
}
static void cont__280_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_LINES, arguments->slots[0]);
  // 506: ... set_node(remark_statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__remark_statement();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__281_1;
}
static void cont__281_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 506: $SINGLE_REMARK_STATEMENT HASHTAG, set_node(remark_statement), REMARK_LINES
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._REMARK_LINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__281_2;
}
static void cont__281_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SINGLE_REMARK_STATEMENT, arguments->slots[0]);
  // 508: $REMARK_STATEMENT multi_span(statements_of SINGLE_REMARK_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = var._SINGLE_REMARK_STATEMENT;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__282_1;
}
static void cont__282_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_STATEMENT, arguments->slots[0]);
  // 509: $REMARK HASHTAG, REMARK_LINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = var._REMARK_LINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__283_1;
}
static void cont__283_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK, arguments->slots[0]);
  // 514: modify_node
  // 515:   : (&node)
  // 516:     unless node.is_a_definition || node.is_a_meta_instruction:
  // 517:       $remark_lines remark_lines_of(node)
  // 518:       if
  // 519:         arguments_of(node).is_empty:
  // 520:           !node.remark_lines_behind_of remark_lines
  // 521:         :
  // 522:           append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 523:       !node.remark_lines_of empty_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__284_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__284_23;
}
static void entry__284_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 516: ... node.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__284_2;
}
static void cont__284_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 516: ... node.is_a_meta_instruction
  frame->slots[3] /* temp__3 */ = create_closure(entry__284_3, 0);
  // 516: ... node.is_a_definition || node.is_a_meta_instruction
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__284_5;
}
static void entry__284_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 516: ... node.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_a_meta_instruction();
  func = myself->type;
  frame->cont = cont__284_4;
}
static void cont__284_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 516: ... node.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__284_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 516: ... :
  // 517:   $remark_lines remark_lines_of(node)
  // 518:   if
  // 519:     arguments_of(node).is_empty:
  // 520:       !node.remark_lines_behind_of remark_lines
  // 521:     :
  // 522:       append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 523:   !node.remark_lines_of empty_list
  frame->slots[4] /* temp__4 */ = create_closure(entry__284_6, 0);
  // 516: unless node.is_a_definition || node.is_a_meta_instruction:
  // 517:   $remark_lines remark_lines_of(node)
  // 518:   if
  // 519:     arguments_of(node).is_empty:
  // 520:       !node.remark_lines_behind_of remark_lines
  // 521:     :
  // 522:       append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 523:   !node.remark_lines_of empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__284_22;
}
static void entry__284_6(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // node: 0
  // remark_lines: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] /* remark_lines */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 517: $remark_lines remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__284_7;
}
static void cont__284_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* remark_lines */, arguments->slots[0]);
  // 519: arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__284_8;
}
static void cont__284_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 519: arguments_of(node).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__284_9;
}
static void cont__284_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 519: ... :
  // 520:   !node.remark_lines_behind_of remark_lines
  frame->slots[4] /* temp__3 */ = create_closure(entry__284_10, 0);
  // 521: :
  // 522:   append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  frame->slots[5] /* temp__4 */ = create_closure(entry__284_11, 0);
  // 518: if
  // 519:   arguments_of(node).is_empty:
  // 520:     !node.remark_lines_behind_of remark_lines
  // 521:   :
  // 522:     append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__284_21;
}
static void entry__284_10(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // remark_lines: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 520: !node.remark_lines_behind_of remark_lines
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* remark_lines */;
  // 520: !node.remark_lines_behind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_behind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__284_11(void) {
  allocate_initialized_frame_gc(2, 10);
  // slot allocations:
  // node: 0
  // remark_lines: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 522: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__284_12;
}
static void cont__284_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 522: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__284_13;
}
static void cont__284_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 522: ... node.arguments_of(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__284_14;
}
static void cont__284_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 522: ... node.arguments_of(-1).remark_lines_behind_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__remark_lines_behind_of();
  func = myself->type;
  frame->cont = cont__284_15;
}
static void cont__284_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 522: append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__284_16;
}
static void cont__284_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 522: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__284_17;
}
static void cont__284_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 522: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__284_18;
}
static void cont__284_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 522: ... node.arguments_of(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = frame->slots[7] /* temp__6 */;
  func = myself->type;
  frame->cont = cont__284_19;
}
static void cont__284_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 522: ... &node.arguments_of(-1).remark_lines_behind_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[9] /* temp__8 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_behind_of, frame->slots[6] /* temp__5 */);
    frame->slots[9] /* temp__8 */ = temp;

  }
  // 522: ... &node.arguments_of(-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__7 */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = frame->slots[7] /* temp__6 */;
  func = myself->type;
  frame->cont = cont__284_20;
}
static void cont__284_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 522: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__6 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__284_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 523: !node.remark_lines_of empty_list
  frame->slots[2] /* temp__1 */ = get__empty_list();
  // 523: !node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__284_22(void) {
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
static void cont__284_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 511: $REMARK_BEHIND
  // 512:   sequence
  // 513:     REMARK
  // 514:     modify_node
  // 515:       : (&node)
  // 516:         unless node.is_a_definition || node.is_a_meta_instruction:
  // 517:           $remark_lines remark_lines_of(node)
  // 518:           if
  // 519:             arguments_of(node).is_empty:
  // 520:               !node.remark_lines_behind_of remark_lines
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__284_24;
}
static void cont__284_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_BEHIND, arguments->slots[0]);
  // 525: ... sim2c::WHITESPACE, HASHTAG, REMARK_LINE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._HASHTAG;
  arguments->slots[2] = var._REMARK_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__285_1;
}
static void cont__285_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 525: $LINE_END_REMARK optional(sim2c::WHITESPACE, HASHTAG, REMARK_LINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__285_2;
}
static void cont__285_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINE_END_REMARK, arguments->slots[0]);
  // 533: modify_node
  // 534:   : (&node)
  // 535:     unless node.is_a_definition:
  // 536:       $n length_of(arguments_of(node))
  // 537:       if n > 0:
  // 538:         push
  // 539:           &node.arguments_of(n).remark_lines_of
  // 540:           remark_lines_of(node)(-1)
  // 541:         range &node.remark_lines_of 1 -2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__286_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__286_22;
}
static void entry__286_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 535: ... node.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__286_2;
}
static void cont__286_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 535: ... :
  // 536:   $n length_of(arguments_of(node))
  // 537:   if n > 0:
  // 538:     push
  // 539:       &node.arguments_of(n).remark_lines_of
  // 540:       remark_lines_of(node)(-1)
  // 541:     range &node.remark_lines_of 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__286_3, 0);
  // 535: unless node.is_a_definition:
  // 536:   $n length_of(arguments_of(node))
  // 537:   if n > 0:
  // 538:     push
  // 539:       &node.arguments_of(n).remark_lines_of
  // 540:       remark_lines_of(node)(-1)
  // 541:     range &node.remark_lines_of 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__286_21;
}
static void entry__286_7(void) {
  allocate_initialized_frame_gc(2, 11);
  // slot allocations:
  // node: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 539: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__286_8;
}
static void cont__286_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 539: ... node.arguments_of(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  result_count = 1;
  myself = frame->slots[4] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__286_9;
}
static void cont__286_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 539: ... node.arguments_of(n).remark_lines_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__286_10;
}
static void cont__286_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 540: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__286_11;
}
static void cont__286_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 540: remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__286_12;
}
static void cont__286_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 540: remark_lines_of(node)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = frame->slots[7] /* temp__6 */;
  func = myself->type;
  frame->cont = cont__286_13;
}
static void cont__286_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 538: push
  // 539:   &node.arguments_of(n).remark_lines_of
  // 540:   remark_lines_of(node)(-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__286_14;
}
static void cont__286_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 539: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__286_15;
}
static void cont__286_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 539: ... node.arguments_of(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  result_count = 1;
  myself = frame->slots[9] /* temp__8 */;
  func = myself->type;
  frame->cont = cont__286_16;
}
static void cont__286_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 539: &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[10] /* temp__9 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[8] /* temp__7 */);
    frame->slots[10] /* temp__9 */ = temp;

  }
  // 539: &node.arguments_of(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[10] /* temp__9 */;
  result_count = 1;
  myself = frame->slots[9] /* temp__8 */;
  func = myself->type;
  frame->cont = cont__286_17;
}
static void cont__286_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 539: &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__8 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 541: ... node.remark_lines_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__286_18;
}
static void cont__286_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 541: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__286_19;
}
static void cont__286_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 541: range &node.remark_lines_of 1 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__286_20;
}
static void cont__286_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 541: ... &node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[4] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__286_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] /* n */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 536: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__286_4;
}
static void cont__286_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 536: $n length_of(arguments_of(node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__286_5;
}
static void cont__286_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* n */, arguments->slots[0]);
  // 537: ... n > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__286_6;
}
static void cont__286_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 537: ... :
  // 538:   push
  // 539:     &node.arguments_of(n).remark_lines_of
  // 540:     remark_lines_of(node)(-1)
  // 541:   range &node.remark_lines_of 1 -2
  frame->slots[3] /* temp__2 */ = create_closure(entry__286_7, 0);
  // 537: if n > 0:
  // 538:   push
  // 539:     &node.arguments_of(n).remark_lines_of
  // 540:     remark_lines_of(node)(-1)
  // 541:   range &node.remark_lines_of 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__286_21(void) {
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
static void cont__286_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 529: sequence
  // 530:   sim2c::WHITESPACE
  // 531:   HASHTAG
  // 532:   REMARK_LINE
  // 533:   modify_node
  // 534:     : (&node)
  // 535:       unless node.is_a_definition:
  // 536:         $n length_of(arguments_of(node))
  // 537:         if n > 0:
  // 538:           push
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._HASHTAG;
  arguments->slots[2] = var._REMARK_LINE;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__286_23;
}
static void cont__286_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 527: $ARGUMENT_LINE_END_REMARK
  // 528:   optional
  // 529:     sequence
  // 530:       sim2c::WHITESPACE
  // 531:       HASHTAG
  // 532:       REMARK_LINE
  // 533:       modify_node
  // 534:         : (&node)
  // 535:           unless node.is_a_definition:
  // 536:             $n length_of(arguments_of(node))
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__286_24;
}
static void cont__286_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENT_LINE_END_REMARK, arguments->slots[0]);
  // 547: modify_node
  // 548:   : (&node)
  // 549:     unless node.is_a_definition:
  // 550:       $n length_of(arguments_of(node))
  // 551:       if n > 0:
  // 552:         push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 553:         range &node.remark_lines_of 1 -2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__287_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__287_22;
}
static void entry__287_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 549: ... node.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__287_2;
}
static void cont__287_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 549: ... :
  // 550:   $n length_of(arguments_of(node))
  // 551:   if n > 0:
  // 552:     push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 553:     range &node.remark_lines_of 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__287_3, 0);
  // 549: unless node.is_a_definition:
  // 550:   $n length_of(arguments_of(node))
  // 551:   if n > 0:
  // 552:     push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 553:     range &node.remark_lines_of 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__287_21;
}
static void entry__287_7(void) {
  allocate_initialized_frame_gc(2, 11);
  // slot allocations:
  // node: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 552: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__287_8;
}
static void cont__287_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 552: ... node.arguments_of(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  result_count = 1;
  myself = frame->slots[4] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__287_9;
}
static void cont__287_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 552: ... node.arguments_of(n).remark_lines_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__287_10;
}
static void cont__287_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 552: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__287_11;
}
static void cont__287_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 552: ... remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__287_12;
}
static void cont__287_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 552: ... remark_lines_of(node)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = frame->slots[7] /* temp__6 */;
  func = myself->type;
  frame->cont = cont__287_13;
}
static void cont__287_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 552: push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__287_14;
}
static void cont__287_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 552: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__287_15;
}
static void cont__287_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 552: ... node.arguments_of(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  result_count = 1;
  myself = frame->slots[9] /* temp__8 */;
  func = myself->type;
  frame->cont = cont__287_16;
}
static void cont__287_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 552: ... &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[10] /* temp__9 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[8] /* temp__7 */);
    frame->slots[10] /* temp__9 */ = temp;

  }
  // 552: ... &node.arguments_of(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[10] /* temp__9 */;
  result_count = 1;
  myself = frame->slots[9] /* temp__8 */;
  func = myself->type;
  frame->cont = cont__287_17;
}
static void cont__287_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 552: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__8 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 553: ... node.remark_lines_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__287_18;
}
static void cont__287_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 553: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__287_19;
}
static void cont__287_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 553: range &node.remark_lines_of 1 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__287_20;
}
static void cont__287_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 553: ... &node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[4] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__287_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] /* n */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 550: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__287_4;
}
static void cont__287_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 550: $n length_of(arguments_of(node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__287_5;
}
static void cont__287_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* n */, arguments->slots[0]);
  // 551: ... n > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__287_6;
}
static void cont__287_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 551: ... :
  // 552:   push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 553:   range &node.remark_lines_of 1 -2
  frame->slots[3] /* temp__2 */ = create_closure(entry__287_7, 0);
  // 551: if n > 0:
  // 552:   push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 553:   range &node.remark_lines_of 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__287_21(void) {
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
static void cont__287_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 543: $ARGUMENT_REMARK
  // 544:   sequence
  // 545:     HASHTAG
  // 546:     REMARK_LINE
  // 547:     modify_node
  // 548:       : (&node)
  // 549:         unless node.is_a_definition:
  // 550:           $n length_of(arguments_of(node))
  // 551:           if n > 0:
  // 552:             push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = var._REMARK_LINE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__287_23;
}
static void cont__287_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENT_REMARK, arguments->slots[0]);
  // 555: $NEW_LINE_END_REMARK sim2c::WHITESPACE, HASHTAG, REMARK_LINE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._HASHTAG;
  arguments->slots[2] = var._REMARK_LINE;
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
  initialize_future(var._NEW_LINE_END_REMARK, arguments->slots[0]);
  // 556: $NEXT_LINE_REMARK INDENT, REMARK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = var._REMARK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__289_1;
}
static void cont__289_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEXT_LINE_REMARK, arguments->slots[0]);
  // 564: modify_node
  // 565:   : (node)
  // 566:     ->
  // 567:       function_call
  // 568:         .functor_of node
  // 569:         .fragment_of fragment_of(node)
  // 570:         .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__290_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__290_4;
}
static void entry__290_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 569: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__290_2;
}
static void cont__290_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 570: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__290_3;
}
static void cont__290_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 567: function_call
  // 568:   .functor_of node
  // 569:   .fragment_of fragment_of(node)
  // 570:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* node */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 566: ->
  // 567:   function_call
  // 568:     .functor_of node
  // 569:     .fragment_of fragment_of(node)
  // 570:     .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__290_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 571: ... alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENTS;
  arguments->slots[1] = var._INLINE_ATTRIBUTE_VALUE_PAIRS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__290_5;
}
static void cont__290_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 571: ... optional(alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__290_6;
}
static void cont__290_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 571: inline(optional(alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = var._inline;
  func = myself->type;
  frame->cont = cont__290_7;
}
static void cont__290_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 572: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__290_8;
}
static void cont__290_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 561: $FUNCTION_CALL
  // 562:   sequence
  // 563:     '('
  // 564:     modify_node
  // 565:       : (node)
  // 566:         ->
  // 567:           function_call
  // 568:             .functor_of node
  // 569:             .fragment_of fragment_of(node)
  // 570:             .source_position_of source_position_of(node)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[4] /* temp__5 */;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__290_9;
}
static void cont__290_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FUNCTION_CALL, arguments->slots[0]);
  // 575: $MAKE_ATTRIBUTE_ACCESS
  // 576:   modify_node
  // 577:     : (&node)
  // 578:       !node
  // 579:         function_call
  // 580:           .arguments_of list(node)
  // 581:           .is_an_attribute_access true
  // 582:           .fragment_of fragment_of(node)
  // 583:           .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__291_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__291_5;
}
static void entry__291_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 580: ... list(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__291_2;
}
static void cont__291_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 582: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__291_3;
}
static void cont__291_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 583: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__291_4;
}
static void cont__291_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 578: !node
  // 579:   function_call
  // 580:     .arguments_of list(node)
  // 581:     .is_an_attribute_access true
  // 582:     .fragment_of fragment_of(node)
  // 583:     .source_position_of source_position_of(node)
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
static void cont__291_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAKE_ATTRIBUTE_ACCESS, arguments->slots[0]);
  // 589: span(functor_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__292_1;
}
static void cont__292_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 585: $ATTRIBUTE_ACCESS
  // 586:   sequence
  // 587:     '.'
  // 588:     MAKE_ATTRIBUTE_ACCESS
  // 589:     span(functor_of IDENTIFIER)
  // 590:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = var._MAKE_ATTRIBUTE_ACCESS;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__292_2;
}
static void cont__292_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ATTRIBUTE_ACCESS, arguments->slots[0]);
  // 596: span(functor_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__293_1;
}
static void cont__293_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 592: $ATTRIBUTE_WRITE
  // 593:   sequence
  // 594:     '.'
  // 595:     MAKE_ATTRIBUTE_ACCESS
  // 596:     span(functor_of NAME_OF_POLYMORPHIC)
  // 597:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = var._MAKE_ATTRIBUTE_ACCESS;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__293_2;
}
static void cont__293_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ATTRIBUTE_WRITE, arguments->slots[0]);
  // 599: ... alt(FUNCTION_CALL ATTRIBUTE_ACCESS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._FUNCTION_CALL;
  arguments->slots[1] = var._ATTRIBUTE_ACCESS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__294_1;
}
static void cont__294_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 599: $EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_ACCESS))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__294_2;
}
static void cont__294_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXTENSIONS, arguments->slots[0]);
  // 600: ... alt(FUNCTION_CALL ATTRIBUTE_WRITE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._FUNCTION_CALL;
  arguments->slots[1] = var._ATTRIBUTE_WRITE;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__295_1;
}
static void cont__295_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 600: $READ_WRITE_EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_WRITE))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__295_2;
}
static void cont__295_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._READ_WRITE_EXTENSIONS, arguments->slots[0]);
  // 601: $IDENTIFIER_OR_FUNCTION_CALL IDENTIFIER, EXTENSIONS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER;
  arguments->slots[1] = var._EXTENSIONS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__296_1;
}
static void cont__296_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._IDENTIFIER_OR_FUNCTION_CALL, arguments->slots[0]);
  // 604: ... set_field(is_a_destination true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_a_destination();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__297_1;
}
static void cont__297_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 603: $READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 604:   IDENTIFIER, set_field(is_a_destination true), READ_WRITE_EXTENSIONS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._READ_WRITE_EXTENSIONS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__297_2;
}
static void cont__297_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, arguments->slots[0]);
  // 608: ... many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__298_1;
}
static void cont__298_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 608: interleaved(many(DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__298_2;
}
static void cont__298_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 609: ... many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__298_3;
}
static void cont__298_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 609: ... '.', many(DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__298_4;
}
static void cont__298_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 609: optional('.', many(DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__298_5;
}
static void cont__298_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 610: ... alt('e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__101;
  arguments->slots[1] = character__69;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__298_6;
}
static void cont__298_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 610: ... alt('+' '-')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__43;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__298_7;
}
static void cont__298_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 610: ... optional(alt('+' '-'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__298_8;
}
static void cont__298_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 610: ... many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__298_9;
}
static void cont__298_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 610: ... alt('e' 'E'), optional(alt('+' '-')), many(DIGIT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  arguments->slots[2] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__298_10;
}
static void cont__298_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 610: optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__298_11;
}
static void cont__298_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 606: $DECIMAL_NUMBER
  // 607:   sequence
  // 608:     interleaved(many(DIGIT) '@apos;')
  // 609:     optional('.', many(DIGIT))
  // 610:     optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__298_12;
}
static void cont__298_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DECIMAL_NUMBER, arguments->slots[0]);
  // 612: $BINARY_DIGIT alt('0' '1')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__49;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__299_1;
}
static void cont__299_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BINARY_DIGIT, arguments->slots[0]);
  // 613: ... many(BINARY_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._BINARY_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__300_1;
}
static void cont__300_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 613: ... interleaved(many(BINARY_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__300_2;
}
static void cont__300_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 613: $BINARY_NUMBER "0b", interleaved(many(BINARY_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882ba7;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__300_4;
}
static void cont__300_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BINARY_NUMBER, arguments->slots[0]);
  // 614: $OCTAL_DIGIT '0' .. '7'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__55;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__301_1;
}
static void cont__301_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OCTAL_DIGIT, arguments->slots[0]);
  // 615: ... many(OCTAL_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OCTAL_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__302_1;
}
static void cont__302_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 615: ... interleaved(many(OCTAL_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__302_2;
}
static void cont__302_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 615: $OCTAL_NUMBER "0o", interleaved(many(OCTAL_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882baa;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__302_4;
}
static void cont__302_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OCTAL_NUMBER, arguments->slots[0]);
  // 616: ... 'a' .. 'f'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__102;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__303_1;
}
static void cont__303_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 616: ... 'A' .. 'F'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__65;
  arguments->slots[1] = character__70;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__303_2;
}
static void cont__303_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 616: $HEX_DIGIT alt(DIGIT 'a' .. 'f' 'A' .. 'F')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__303_3;
}
static void cont__303_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._HEX_DIGIT, arguments->slots[0]);
  // 617: ... many(HEX_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._HEX_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__304_1;
}
static void cont__304_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 617: ... interleaved(many(HEX_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__304_2;
}
static void cont__304_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 617: $HEX_NUMBER "0x", interleaved(many(HEX_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882bbd;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__304_4;
}
static void cont__304_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._HEX_NUMBER, arguments->slots[0]);
  // 621: set_node(numeric_literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__numeric_literal();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__305_1;
}
static void cont__305_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 625: alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._HEX_NUMBER;
  arguments->slots[1] = var._OCTAL_NUMBER;
  arguments->slots[2] = var._BINARY_NUMBER;
  arguments->slots[3] = var._DECIMAL_NUMBER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__305_2;
}
static void cont__305_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 623: capture
  // 624:   node::value_of
  // 625:   alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__305_3;
}
static void cont__305_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 619: $NUMBER
  // 620:   sequence
  // 621:     set_node(numeric_literal)
  // 622:     STORE_POSITION
  // 623:     capture
  // 624:       node::value_of
  // 625:       alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  // 626:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__305_4;
}
static void cont__305_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NUMBER, arguments->slots[0]);
  // 630: capture(node::value_of PRINTABLE_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = get__PRINTABLE_CHARACTER();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__306_1;
}
static void cont__306_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 631: modify_node
  // 632:   : (&node)
  // 633:     !node.node::value_of node::value_of(node)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__306_2;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__306_5;
}
static void entry__306_2(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
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
  frame->cont = cont__306_3;
}
static void cont__306_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 633: !node.node::value_of node::value_of(node)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__306_4;
}
static void cont__306_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 633: !node.node::value_of
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
static void cont__306_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 628: $SIMPLE_CHARACTER
  // 629:   sequence
  // 630:     capture(node::value_of PRINTABLE_CHARACTER)
  // 631:     modify_node
  // 632:       : (&node)
  // 633:         !node.node::value_of node::value_of(node)(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__306_6;
}
static void cont__306_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMPLE_CHARACTER, arguments->slots[0]);
  // 638: modify_node
  // 639:   : (&node)
  // 640:     !node.node::value_of '@@'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__307_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__307_2;
}
static void entry__307_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 640: !node.node::value_of '@@'
  frame->slots[1] /* temp__1 */ = character__64;
  // 640: !node.node::value_of
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
static void cont__307_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 635: $AT_CHARACTER
  // 636:   sequence
  // 637:     '@@'
  // 638:     modify_node
  // 639:       : (&node)
  // 640:         !node.node::value_of '@@'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__307_3;
}
static void cont__307_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._AT_CHARACTER, arguments->slots[0]);
  // 644: capture(node::value_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__308_1;
}
static void cont__308_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 646: modify_node
  // 647:   :
  // 648:     (
  // 649:       &node
  // 650:       stream
  // 651:     )
  // 652:     $chr character_names(node::value_of(node))
  // 653:     unless chr.is_defined: ParseError stream "invalid character name"
  // 654:     !node.node::value_of chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__308_2;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__308_9;
}
static void entry__308_2(void) {
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
  // 652: ... node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__308_3;
}
static void cont__308_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 652: $chr character_names(node::value_of(node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__character_names();
  func = myself->type;
  frame->cont = cont__308_4;
}
static void cont__308_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* chr */, arguments->slots[0]);
  // 653: ... chr.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* chr */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__308_5;
}
static void cont__308_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 653: ... : ParseError stream "invalid character name"
  frame->slots[4] /* temp__2 */ = create_closure(entry__308_6, 0);
  // 653: unless chr.is_defined: ParseError stream "invalid character name"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__308_8;
}
static void entry__308_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 653: ... ParseError stream "invalid character name"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__dea962eab6ac8f23;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__308_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 654: !node.node::value_of chr
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* chr */;
  // 654: !node.node::value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__value_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__308_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 642: $NAMED_CHARACTER
  // 643:   sequence
  // 644:     capture(node::value_of NAME)
  // 645:     ';'
  // 646:     modify_node
  // 647:       :
  // 648:         (
  // 649:           &node
  // 650:           stream
  // 651:         )
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__59;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__308_10;
}
static void cont__308_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMED_CHARACTER, arguments->slots[0]);
  // 661: ... many(BINARY_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._BINARY_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__309_1;
}
static void cont__309_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 661: "0b", many(BINARY_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882ba7;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__309_2;
}
static void cont__309_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 662: ... many(OCTAL_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OCTAL_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__309_3;
}
static void cont__309_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 662: "0o", many(OCTAL_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882baa;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
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
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 663: ... many(HEX_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._HEX_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__309_5;
}
static void cont__309_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 663: "0x", many(HEX_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882bbd;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__309_6;
}
static void cont__309_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 664: many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__309_7;
}
static void cont__309_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 660: alt
  // 661:   "0b", many(BINARY_DIGIT)
  // 662:   "0o", many(OCTAL_DIGIT)
  // 663:   "0x", many(HEX_DIGIT)
  // 664:   many(DIGIT)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  arguments->slots[3] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__309_8;
}
static void cont__309_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 658: capture
  // 659:   node::value_of
  // 660:   alt
  // 661:     "0b", many(BINARY_DIGIT)
  // 662:     "0o", many(OCTAL_DIGIT)
  // 663:     "0x", many(HEX_DIGIT)
  // 664:     many(DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__309_9;
}
static void cont__309_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 666: modify_node
  // 667:   : (&node)
  // 668:     !node
  // 669:       .node::value_of character(node::value_of(node).to_integer)
  // 670:       .is_in_numeric_notation true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__309_10;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__309_14;
}
static void entry__309_10(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 669: ... node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__309_11;
}
static void cont__309_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 669: ... node::value_of(node).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__309_12;
}
static void cont__309_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 669: ... character(node::value_of(node).to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__character();
  func = myself->type;
  frame->cont = cont__309_13;
}
static void cont__309_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 668: !node
  // 669:   .node::value_of character(node::value_of(node).to_integer)
  // 670:   .is_in_numeric_notation true
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
static void cont__309_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 656: $NUMERIC_CHARACTER
  // 657:   sequence
  // 658:     capture
  // 659:       node::value_of
  // 660:       alt
  // 661:         "0b", many(BINARY_DIGIT)
  // 662:         "0o", many(OCTAL_DIGIT)
  // 663:         "0x", many(HEX_DIGIT)
  // 664:         many(DIGIT)
  // 665:     ';'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__59;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__309_15;
}
static void cont__309_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NUMERIC_CHARACTER, arguments->slots[0]);
  // 677: syntax_error("invalid special character")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4313674f4741806a;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__310_2;
}
static void cont__310_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 672: $SPECIAL_CHARACTER
  // 673:   alt
  // 674:     AT_CHARACTER
  // 675:     NAMED_CHARACTER
  // 676:     NUMERIC_CHARACTER
  // 677:     syntax_error("invalid special character")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._AT_CHARACTER;
  arguments->slots[1] = var._NAMED_CHARACTER;
  arguments->slots[2] = var._NUMERIC_CHARACTER;
  arguments->slots[3] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__310_3;
}
static void cont__310_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SPECIAL_CHARACTER, arguments->slots[0]);
  // 679: ... '@@', SPECIAL_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = var._SPECIAL_CHARACTER;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__311_1;
}
static void cont__311_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 679: $CHARACTER_SYMBOL alt('@@', SPECIAL_CHARACTER SIMPLE_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._SIMPLE_CHARACTER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__311_2;
}
static void cont__311_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._CHARACTER_SYMBOL, arguments->slots[0]);
  // 684: set_node(character_literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__character_literal();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__312_1;
}
static void cont__312_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 687: expect('@apos;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__39;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__312_2;
}
static void cont__312_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 681: $CHARACTER
  // 682:   sequence
  // 683:     '@apos;'
  // 684:     set_node(character_literal)
  // 685:     STORE_POSITION_MINUS_1
  // 686:     CHARACTER_SYMBOL
  // 687:     expect('@apos;')
  // 688:     STORE_END_POSITION
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
  frame->cont = cont__312_3;
}
static void cont__312_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._CHARACTER, arguments->slots[0]);
  // 695: modify_node
  // 696:   : (&node)
  // 697:     push &node.node::text_of node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__313_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__313_5;
}
static void entry__313_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 697: ... node.node::text_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__313_2;
}
static void cont__313_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 697: ... node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__313_3;
}
static void cont__313_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 697: push &node.node::text_of node::value_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__313_4;
}
static void cont__313_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 697: ... &node.node::text_of
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
static void cont__313_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 693: sequence
  // 694:   CHARACTER_SYMBOL
  // 695:   modify_node
  // 696:     : (&node)
  // 697:       push &node.node::text_of node::value_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._CHARACTER_SYMBOL;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__313_6;
}
static void cont__313_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 690: $STRING_CHARACTER
  // 691:   alt
  // 692:     "@@;"
  // 693:     sequence
  // 694:       CHARACTER_SYMBOL
  // 695:       modify_node
  // 696:         : (&node)
  // 697:           push &node.node::text_of node::value_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5082bfe;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__313_8;
}
static void cont__313_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING_CHARACTER, arguments->slots[0]);
  // 702: modify_node
  // 703:   : (&node)
  // 704:     if node::text_of(node) != "":
  // 705:       push &node.arguments_of node(.arguments_of undefined)
  // 706:     !node.node::text_of ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__314_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__314_9;
}
static void entry__314_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 704: ... node::text_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__314_2;
}
static void cont__314_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 704: ... node::text_of(node) != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__314_3;
}
static void cont__314_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 704: ... node::text_of(node) != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__314_4;
}
static void cont__314_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 704: ... :
  // 705:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__314_5, 0);
  // 704: if node::text_of(node) != "":
  // 705:   push &node.arguments_of node(.arguments_of undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__314_8;
}
static void entry__314_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 705: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__314_6;
}
static void cont__314_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 705: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 705: push &node.arguments_of node(.arguments_of undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__314_7;
}
static void cont__314_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 705: ... &node.arguments_of
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
static void cont__314_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 706: !node.node::text_of ""
  frame->slots[1] /* temp__1 */ = empty_string;
  // 706: !node.node::text_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__314_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 707: ... arguments_span(EXPRESSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__314_10;
}
static void cont__314_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 707: interleaved(arguments_span(EXPRESSION) sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__314_11;
}
static void cont__314_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 708: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__314_12;
}
static void cont__314_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 699: $STRING_INSERTION
  // 700:   sequence
  // 701:     "@@("
  // 702:     modify_node
  // 703:       : (&node)
  // 704:         if node::text_of(node) != "":
  // 705:           push &node.arguments_of node(.arguments_of undefined)
  // 706:         !node.node::text_of ""
  // 707:     interleaved(arguments_span(EXPRESSION) sim2c::WHITESPACE)
  // 708:     expect(')')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5082bed;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__314_14;
}
static void cont__314_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING_INSERTION, arguments->slots[0]);
  // 710: $CHECK_INSERTIONS
  // 711:   modify_node
  // 712:     : (&node)
  // 713:       if length_of(arguments_of(node)) > 0:
  // 714:         if node::text_of(node) != "":
  // 715:           push &node.arguments_of node(.arguments_of undefined)
  // 716:         !node
  // 717:           function_call
  // 718:             .functor_of std_identifier("string")
  // 719:             .arguments_of arguments_of(node)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__315_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__315_20;
}
static void entry__315_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 713: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__315_2;
}
static void cont__315_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 713: ... length_of(arguments_of(node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__315_3;
}
static void cont__315_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 713: ... length_of(arguments_of(node)) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__315_4;
}
static void cont__315_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 713: ... :
  // 714:   if node::text_of(node) != "":
  // 715:     push &node.arguments_of node(.arguments_of undefined)
  // 716:   !node
  // 717:     function_call
  // 718:       .functor_of std_identifier("string")
  // 719:       .arguments_of arguments_of(node)
  // 720:       .is_a_string_template true
  // 721:       .fragment_of fragment_of(node)
  // 722:       .source_position_of source_position_of(node)
  // ...
  frame->slots[4] /* temp__4 */ = create_closure(entry__315_5, 0);
  // 713: if length_of(arguments_of(node)) > 0:
  // 714:   if node::text_of(node) != "":
  // 715:     push &node.arguments_of node(.arguments_of undefined)
  // 716:   !node
  // 717:     function_call
  // 718:       .functor_of std_identifier("string")
  // 719:       .arguments_of arguments_of(node)
  // 720:       .is_a_string_template true
  // 721:       .fragment_of fragment_of(node)
  // 722:       .source_position_of source_position_of(node)
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
  frame->cont = cont__315_19;
}
static void entry__315_5(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 714: ... node::text_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__315_6;
}
static void cont__315_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 714: ... node::text_of(node) != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__315_7;
}
static void cont__315_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 714: ... node::text_of(node) != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__315_8;
}
static void cont__315_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 714: ... :
  // 715:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__315_9, 0);
  // 714: if node::text_of(node) != "":
  // 715:   push &node.arguments_of node(.arguments_of undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__315_12;
}
static void entry__315_9(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 715: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__315_10;
}
static void cont__315_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 715: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 715: push &node.arguments_of node(.arguments_of undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__315_11;
}
static void cont__315_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 715: ... &node.arguments_of
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
static void cont__315_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 718: ... std_identifier("string")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7c1f540901cb12b0;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__315_14;
}
static void cont__315_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 719: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__315_15;
}
static void cont__315_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 721: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__315_16;
}
static void cont__315_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 722: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__315_17;
}
static void cont__315_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 723: ... end_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__315_18;
}
static void cont__315_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 716: !node
  // 717:   function_call
  // 718:     .functor_of std_identifier("string")
  // 719:     .arguments_of arguments_of(node)
  // 720:     .is_a_string_template true
  // 721:     .fragment_of fragment_of(node)
  // 722:     .source_position_of source_position_of(node)
  // 723:     .end_position_of end_position_of(node)
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
static void cont__315_19(void) {
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
static void cont__315_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._CHECK_INSERTIONS, arguments->slots[0]);
  // 730: not_followed_by(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__316_1;
}
static void cont__316_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 731: set_node(string_literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__string_literal();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__316_2;
}
static void cont__316_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 733: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__316_3;
}
static void cont__316_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 733: ... alt(STRING_INSERTION STRING_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STRING_INSERTION;
  arguments->slots[1] = var._STRING_CHARACTER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__316_4;
}
static void cont__316_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 733: ... not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__316_5;
}
static void cont__316_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 733: some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__316_6;
}
static void cont__316_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 734: expect('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__316_7;
}
static void cont__316_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 725: $STRING
  // 726:   # This code has an astonishing capability to flatten template expressions!
  // 727:   
  // 728:   sequence
  // 729:     '@quot;'
  // 730:     not_followed_by(indent_marker)
  // 731:     set_node(string_literal)
  // 732:     STORE_POSITION_MINUS_1
  // 733:     some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
  // 734:     expect('@quot;')
  // ...
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
  frame->cont = cont__316_8;
}
static void cont__316_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING, arguments->slots[0]);
  // 741: ... '@@', OUTDENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__317_1;
}
static void cont__317_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 741: followed_by('@@', OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__317_2;
}
static void cont__317_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 742: '@@', NEWLINE, STRING_LINE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = var._NEWLINE;
  arguments->slots[2] = var._STRING_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__317_3;
}
static void cont__317_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 743: STRING_INSERTION, STRING_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STRING_INSERTION;
  arguments->slots[1] = var._STRING_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__317_4;
}
static void cont__317_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 744: STRING_CHARACTER, STRING_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STRING_CHARACTER;
  arguments->slots[1] = var._STRING_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__317_5;
}
static void cont__317_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 740: alt
  // 741:   followed_by('@@', OUTDENT)
  // 742:   '@@', NEWLINE, STRING_LINE
  // 743:   STRING_INSERTION, STRING_LINE
  // 744:   STRING_CHARACTER, STRING_LINE
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  arguments->slots[2] = frame->slots[4] /* temp__5 */;
  arguments->slots[3] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__317_6;
}
static void cont__317_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 738: $STRING_LINE
  // 739:   optional
  // 740:     alt
  // 741:       followed_by('@@', OUTDENT)
  // 742:       '@@', NEWLINE, STRING_LINE
  // 743:       STRING_INSERTION, STRING_LINE
  // 744:       STRING_CHARACTER, STRING_LINE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__317_7;
}
static void cont__317_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING_LINE, arguments->slots[0]);
  // 746: $ADD_LINE_END
  // 747:   modify_node
  // 748:     : (&node)
  // 749:       append &node.node::text_of line_end_specifier_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__318_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__318_5;
}
static void entry__318_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 749: ... node.node::text_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__318_2;
}
static void cont__318_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 749: ... line_end_specifier_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__line_end_specifier_of();
  func = myself->type;
  frame->cont = cont__318_3;
}
static void cont__318_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 749: append &node.node::text_of line_end_specifier_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__318_4;
}
static void cont__318_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 749: ... &node.node::text_of
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
static void cont__318_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ADD_LINE_END, arguments->slots[0]);
  // 754: set_node(multi_line_string)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__multi_line_string();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__319_1;
}
static void cont__319_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 758: ... NEWLINE, ADD_LINE_END, STRING_LINE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  arguments->slots[1] = var._ADD_LINE_END;
  arguments->slots[2] = var._STRING_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__319_2;
}
static void cont__319_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 758: some(NEWLINE, ADD_LINE_END, STRING_LINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__319_3;
}
static void cont__319_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 759: ... '@@', OUTDENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__319_4;
}
static void cont__319_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 759: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__319_5;
}
static void cont__319_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 759: ... expect(outdent_marker), ADD_LINE_END
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  arguments->slots[1] = var._ADD_LINE_END;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__319_6;
}
static void cont__319_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 759: alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__319_7;
}
static void cont__319_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 751: $MULTI_LINE_STRING
  // 752:   sequence
  // 753:     '@quot;'
  // 754:     set_node(multi_line_string)
  // 755:     STORE_POSITION_MINUS_1
  // 756:     INDENT
  // 757:     STRING_LINE
  // 758:     some(NEWLINE, ADD_LINE_END, STRING_LINE)
  // 759:     alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
  // 760:     STORE_END_POSITION
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
  frame->cont = cont__319_8;
}
static void cont__319_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_STRING, arguments->slots[0]);
  // 763: ... not_followed_by(LETTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__320_1;
}
static void cont__320_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 763: ... set_node(unique_item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__unique_item();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__320_2;
}
static void cont__320_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 763: $UNIQUE_ITEM '.', not_followed_by(LETTER), set_node(unique_item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__320_3;
}
static void cont__320_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._UNIQUE_ITEM, arguments->slots[0]);
  // 768: ... syntax_error("expression expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__55df65a142fc9536;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__321_2;
}
static void cont__321_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 768: ... alt(EXPRESSION BODY syntax_error("expression expected"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = var._BODY;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__321_3;
}
static void cont__321_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 768: inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._inline;
  func = myself->type;
  frame->cont = cont__321_4;
}
static void cont__321_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 769: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__321_5;
}
static void cont__321_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 765: $PARENTHESED_EXPRESSION
  // 766:   sequence
  // 767:     '('
  // 768:     inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  // 769:     expect(')')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__321_6;
}
static void cont__321_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARENTHESED_EXPRESSION, arguments->slots[0]);
  // 775: modify_node
  // 776:   : (node)
  // 777:     ->
  // 778:       function_call
  // 779:         .functor_of std_identifier("key_value_pair")
  // 780:         .arguments_of list(node std_identifier("true"))
  // 781:         .fragment_of fragment_of(node)
  // 782:         .source_position_of source_position_of(node)+2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__322_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__322_10;
}
static void entry__322_1(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 779: ... std_identifier("key_value_pair")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__64d512703527e2ab;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__322_3;
}
static void cont__322_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 780: ... std_identifier("true")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2a0aedcb5dc87d5c;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__322_5;
}
static void cont__322_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 780: ... list(node std_identifier("true"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__322_6;
}
static void cont__322_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 781: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__322_7;
}
static void cont__322_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 782: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__322_8;
}
static void cont__322_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__7 */ = arguments->slots[0];
  // 782: ... source_position_of(node)+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__7 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__322_9;
}
static void cont__322_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 778: function_call
  // 779:   .functor_of std_identifier("key_value_pair")
  // 780:   .arguments_of list(node std_identifier("true"))
  // 781:   .fragment_of fragment_of(node)
  // 782:   .source_position_of source_position_of(node)+2
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__6 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 777: ->
  // 778:   function_call
  // 779:     .functor_of std_identifier("key_value_pair")
  // 780:     .arguments_of list(node std_identifier("true"))
  // 781:     .fragment_of fragment_of(node)
  // 782:     .source_position_of source_position_of(node)+2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__322_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 771: $OPTION
  // 772:   sequence
  // 773:     "--"
  // 774:     IDENTIFIER
  // 775:     modify_node
  // 776:       : (node)
  // 777:         ->
  // 778:           function_call
  // 779:             .functor_of std_identifier("key_value_pair")
  // 780:             .arguments_of list(node std_identifier("true"))
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
  frame->cont = cont__322_12;
}
static void cont__322_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OPTION, arguments->slots[0]);
  // 790: modify_node
  // 791:   : (node)
  // 792:     ->
  // 793:       function_call
  // 794:         .functor_of operator_symbol(.name_of "-")
  // 795:         .arguments_of list(node)
  // 796:         .fragment_of fragment_of(node)
  // 797:         .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__323_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__323_5;
}
static void entry__323_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 794: ... operator_symbol(.name_of "-")
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, string__578a5af303e9ccc);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 795: ... list(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__323_2;
}
static void cont__323_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 796: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__323_3;
}
static void cont__323_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 797: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__323_4;
}
static void cont__323_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 793: function_call
  // 794:   .functor_of operator_symbol(.name_of "-")
  // 795:   .arguments_of list(node)
  // 796:   .fragment_of fragment_of(node)
  // 797:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[4] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[5] /* temp__5 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 792: ->
  // 793:   function_call
  // 794:     .functor_of operator_symbol(.name_of "-")
  // 795:     .arguments_of list(node)
  // 796:     .fragment_of fragment_of(node)
  // 797:     .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__323_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 785: $NEGATION
  // 786:   sequence
  // 787:     '-'
  // 788:     STORE_POSITION_MINUS_1
  // 789:     OPERAND
  // 790:     modify_node
  // 791:       : (node)
  // 792:         ->
  // 793:           function_call
  // 794:             .functor_of operator_symbol(.name_of "-")
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
  frame->cont = cont__323_6;
}
static void cont__323_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEGATION, arguments->slots[0]);
  // 800: $SIMPLE_OPERAND
  // 801:   alt
  // 802:     NUMBER
  // 803:     CHARACTER
  // 804:     STRING
  // 805:     UNIQUE_ITEM
  // 806:     PARENTHESED_EXPRESSION
  // 807:     OPTION
  // 808:     NEGATION
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
  frame->cont = cont__324_1;
}
static void cont__324_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMPLE_OPERAND, arguments->slots[0]);
  // 810: ... some(ATTRIBUTE_ACCESS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._ATTRIBUTE_ACCESS;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__325_1;
}
static void cont__325_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 810: ... SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMPLE_OPERAND;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 810: $OPERAND alt(IDENTIFIER_OR_FUNCTION_CALL SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__325_3;
}
static void cont__325_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OPERAND, arguments->slots[0]);
  // 812: $INFIX_OPERATOR_SYMBOL
  // 813:   alt
  // 814:     '*'
  // 815:     '/'
  // 816:     '+'
  // 817:     '-'
  // 818:     "<<"
  // 819:     "<="
  // 820:     "<"
  // 821:     ">>"
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
  frame->cont = cont__326_1;
}
static void cont__326_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INFIX_OPERATOR_SYMBOL, arguments->slots[0]);
  // 835: ... multi_capture(operators_of INFIX_OPERATOR_SYMBOL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = var._INFIX_OPERATOR_SYMBOL;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__327_1;
}
static void cont__327_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 834: $SYMBOLIC_OPERATOR
  // 835:   infix_operator(multi_capture(operators_of INFIX_OPERATOR_SYMBOL))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__327_2;
}
static void cont__327_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SYMBOLIC_OPERATOR, arguments->slots[0]);
  // 837: ... multi_capture(operators_of ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__328_1;
}
static void cont__328_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 837: $COMMA_OPERATOR multi_capture(operators_of ','), sim2c::WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__328_2;
}
static void cont__328_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._COMMA_OPERATOR, arguments->slots[0]);
  // 843: multi_span(operators_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = var._IDENTIFIER;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__329_1;
}
static void cont__329_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 845: expect(sim2c::WHITESPACE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__329_2;
}
static void cont__329_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 839: $NAMED_OPERATOR
  // 840:   sequence
  // 841:     sim2c::WHITESPACE
  // 842:     '.'
  // 843:     multi_span(operators_of IDENTIFIER)
  // 844:     '.'
  // 845:     expect(sim2c::WHITESPACE)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = character__46;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = character__46;
  arguments->slots[4] = frame->slots[1] /* temp__2 */;
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
  initialize_future(var._NAMED_OPERATOR, arguments->slots[0]);
  // 849: alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._SYMBOLIC_OPERATOR;
  arguments->slots[1] = var._COMMA_OPERATOR;
  arguments->slots[2] = var._NAMED_OPERATOR;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__330_1;
}
static void cont__330_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 850: modify_node
  // 851:   : (&node)
  // 852:     $operator_precedence precedence(operators_of(node)(-1))
  // 853:     $lowest_precedence lowest_precedence_of(node)
  // 854:     if
  // 855:       ||
  // 856:         lowest_precedence.is_undefined
  // 857:         operator_precedence < lowest_precedence
  // 858:       :
  // 859:         !node.lowest_precedence_of operator_precedence
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__330_2;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__330_14;
}
static void entry__330_2(void) {
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
  // 852: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__330_3;
}
static void cont__330_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 852: ... operators_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__operators_of();
  func = myself->type;
  frame->cont = cont__330_4;
}
static void cont__330_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 852: ... operators_of(node)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__330_5;
}
static void cont__330_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 852: $operator_precedence precedence(operators_of(node)(-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__precedence();
  func = myself->type;
  frame->cont = cont__330_6;
}
static void cont__330_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* operator_precedence */, arguments->slots[0]);
  // 853: $lowest_precedence lowest_precedence_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__lowest_precedence_of();
  func = myself->type;
  frame->cont = cont__330_7;
}
static void cont__330_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* lowest_precedence */, arguments->slots[0]);
  // 856: lowest_precedence.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* lowest_precedence */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__330_8;
}
static void cont__330_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 857: operator_precedence < lowest_precedence
  frame->slots[5] /* temp__3 */ = create_closure(entry__330_9, 0);
  // 855: ||
  // 856:   lowest_precedence.is_undefined
  // 857:   operator_precedence < lowest_precedence
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__330_11;
}
static void entry__330_9(void) {
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
  // 857: operator_precedence < lowest_precedence
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* operator_precedence */;
  arguments->slots[1] = frame->slots[1] /* lowest_precedence */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__330_10;
}
static void cont__330_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 857: operator_precedence < lowest_precedence
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__330_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 858: :
  // 859:   !node.lowest_precedence_of operator_precedence
  frame->slots[6] /* temp__4 */ = create_closure(entry__330_12, 0);
  // 854: if
  // 855:   ||
  // 856:     lowest_precedence.is_undefined
  // 857:     operator_precedence < lowest_precedence
  // 858:   :
  // 859:     !node.lowest_precedence_of operator_precedence
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__330_13;
}
static void entry__330_12(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // operator_precedence: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* operator_precedence */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 859: !node.lowest_precedence_of operator_precedence
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* operator_precedence */;
  // 859: !node.lowest_precedence_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__lowest_precedence_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__330_13(void) {
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
static void cont__330_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 847: $INFIX_OPERATOR
  // 848:   sequence
  // 849:     alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
  // 850:     modify_node
  // 851:       : (&node)
  // 852:         $operator_precedence precedence(operators_of(node)(-1))
  // 853:         $lowest_precedence lowest_precedence_of(node)
  // 854:         if
  // 855:           ||
  // 856:             lowest_precedence.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__330_15;
}
static void cont__330_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INFIX_OPERATOR, arguments->slots[0]);
  // 861: $EXTEND_EXPRESSION
  // 862:   modify_node
  // 863:     : (&node)
  // 864:       $parent parent_of(node)
  // 865:       $arguments arguments_of(node)
  // 866:       $n length_of(arguments)
  // 867:       if
  // 868:         n == 1:
  // 869:           !node arguments(1)
  // 870:         : # build syntax tree according to operator precedences
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__331_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__331_63;
}
static void entry__331_1(void) {
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
  // 864: $parent parent_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parent_of();
  func = myself->type;
  frame->cont = cont__331_2;
}
static void cont__331_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* parent */, arguments->slots[0]);
  // 865: $arguments arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__331_3;
}
static void cont__331_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* arguments */, arguments->slots[0]);
  // 866: $n length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__331_4;
}
static void cont__331_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 868: n == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__331_5;
}
static void cont__331_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 868: ... :
  // 869:   !node arguments(1)
  frame->slots[5] /* temp__2 */ = create_closure(entry__331_6, 0);
  // 870: : # build syntax tree according to operator precedences
  // 871:   $operators operators_of(node)
  // 872:   $$operand_stack list(arguments(1))
  // 873:   $$operator_stack list(operators(1))
  // 874:   
  // 875:   $update_stack: ($right next_operator)
  // 876:     $next_prec
  // 877:       if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 878:     
  // 879:     do: (-> break)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__331_8, 0);
  // 867: if
  // 868:   n == 1:
  // 869:     !node arguments(1)
  // 870:   : # build syntax tree according to operator precedences
  // 871:     $operators operators_of(node)
  // 872:     $$operand_stack list(arguments(1))
  // 873:     $$operator_stack list(operators(1))
  // 874:     
  // 875:     $update_stack: ($right next_operator)
  // 876:       $next_prec
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__331_57;
}
static void entry__331_6(void) {
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
  // 869: !node arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__331_7;
}
static void cont__331_7(void) {
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
static void entry__331_8(void) {
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
  // 875: ... : ($right next_operator)
  // 876:   $next_prec
  // 877:     if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 878:   
  // 879:   do: (-> break)
  // 880:     forever:
  // 881:       $operator peek(operator_stack)
  // 882:       $prec precedence(operator)
  // 883:       if next_prec > prec break
  // 884:       if next_prec == prec && is_right_associative(prec) break
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__331_9, 2);
  // 875: $update_stack: ($right next_operator)
  // 876:   $next_prec
  // 877:     if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 878:   
  // 879:   do: (-> break)
  // 880:     forever:
  // 881:       $operator peek(operator_stack)
  // 882:       $prec precedence(operator)
  // 883:       if next_prec > prec break
  // 884:       if next_prec == prec && is_right_associative(prec) break
  // ...
  initialize_future(frame->slots[6] /* update_stack */, frame->slots[7] /* temp__1 */);
  // 871: $operators operators_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__operators_of();
  func = myself->type;
  frame->cont = cont__331_43;
}
static void entry__331_9(void) {
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
  // 877: ... next_operator.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* next_operator */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__331_10;
}
static void cont__331_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 877: ... -> precedence(next_operator)
  frame->slots[6] /* temp__2 */ = create_closure(entry__331_11, 0);
  // 876: $next_prec
  // 877:   if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = func__331_13;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__331_14;
}
static void entry__331_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // next_operator: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* next_operator */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 877: ... precedence(next_operator)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* next_operator */;
  result_count = 1;
  myself = get__precedence();
  func = myself->type;
  frame->cont = cont__331_12;
}
static void cont__331_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 877: ... -> precedence(next_operator)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__331_13(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 877: ... -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__331_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* next_prec */, arguments->slots[0]);
  // 879: ... : (-> break)
  // 880:   forever:
  // 881:     $operator peek(operator_stack)
  // 882:     $prec precedence(operator)
  // 883:     if next_prec > prec break
  // 884:     if next_prec == prec && is_right_associative(prec) break
  // 885:     
  // 886:     $functor
  // 887:       if
  // 888:         operator.is_a_string
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__331_15, 0);
  // 879: do: (-> break)
  // 880:   forever:
  // 881:     $operator peek(operator_stack)
  // 882:     $prec precedence(operator)
  // 883:     if next_prec > prec break
  // 884:     if next_prec == prec && is_right_associative(prec) break
  // 885:     
  // 886:     $functor
  // 887:       if
  // 888:         operator.is_a_string
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__331_40;
}
static void entry__331_15(void) {
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
  // 880: ... :
  // 881:   $operator peek(operator_stack)
  // 882:   $prec precedence(operator)
  // 883:   if next_prec > prec break
  // 884:   if next_prec == prec && is_right_associative(prec) break
  // 885:   
  // 886:   $functor
  // 887:     if
  // 888:       operator.is_a_string
  // 889:       -> operator_symbol(.name_of operator)
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__331_16, 0);
  // 880: forever:
  // 881:   $operator peek(operator_stack)
  // 882:   $prec precedence(operator)
  // 883:   if next_prec > prec break
  // 884:   if next_prec == prec && is_right_associative(prec) break
  // 885:   
  // 886:   $functor
  // 887:     if
  // 888:       operator.is_a_string
  // 889:       -> operator_symbol(.name_of operator)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__331_39;
}
static void entry__331_16(void) {
  allocate_initialized_frame_gc(5, 15);
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
  // 881: $operator peek(operator_stack)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* operator_stack */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__331_17;
}
static void cont__331_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* operator */, arguments->slots[0]);
  // 882: $prec precedence(operator)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* operator */;
  result_count = 1;
  myself = get__precedence();
  func = myself->type;
  frame->cont = cont__331_18;
}
static void cont__331_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* prec */, arguments->slots[0]);
  // 883: ... next_prec > prec
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* prec */;
  arguments->slots[1] = frame->slots[1] /* next_prec */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__331_19;
}
static void cont__331_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 883: if next_prec > prec break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__331_20;
}
static void cont__331_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 884: ... next_prec == prec
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* next_prec */;
  arguments->slots[1] = frame->slots[6] /* prec */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__331_21;
}
static void cont__331_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 884: ... is_right_associative(prec)
  frame->slots[12] /* temp__3 */ = create_closure(entry__331_22, 0);
  // 884: ... next_prec == prec && is_right_associative(prec)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__2 */;
  arguments->slots[1] = frame->slots[12] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__331_24;
}
static void entry__331_22(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // prec: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* prec */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 884: ... is_right_associative(prec)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* prec */;
  result_count = 1;
  myself = var._is_right_associative;
  func = myself->type;
  frame->cont = cont__331_23;
}
static void cont__331_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 884: ... is_right_associative(prec)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__331_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 884: if next_prec == prec && is_right_associative(prec) break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__331_25;
}
static void cont__331_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 888: operator.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* operator */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__331_26;
}
static void cont__331_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 889: -> operator_symbol(.name_of operator)
  frame->slots[11] /* temp__2 */ = create_closure(entry__331_27, 0);
  // 890: -> operator
  frame->slots[12] /* temp__3 */ = create_closure(entry__331_28, 0);
  // 886: $functor
  // 887:   if
  // 888:     operator.is_a_string
  // 889:     -> operator_symbol(.name_of operator)
  // 890:     -> operator
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  arguments->slots[2] = frame->slots[12] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__331_29;
}
static void entry__331_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // operator: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* operator */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 889: ... operator_symbol(.name_of operator)
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[0] /* operator */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 889: -> operator_symbol(.name_of operator)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__331_28(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // operator: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* operator */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 890: -> operator
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* operator */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__331_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* functor */, arguments->slots[0]);
  // 892: $left pop(&operand_stack)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* operand_stack */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__331_30;
}
static void cont__331_30(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* operand_stack */ = arguments->slots[0];
  frame->slots[10] /* temp__1 */ = arguments->slots[1];
  // 892: ... left
  initialize_future(frame->slots[8] /* left */, frame->slots[10] /* temp__1 */);
  // 896: ... list(left right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* left */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* right */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__331_31;
}
static void cont__331_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 898: ... enumeration_no_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* left */;
  result_count = 1;
  myself = get__enumeration_no_of();
  func = myself->type;
  frame->cont = cont__331_32;
}
static void cont__331_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 899: ... fragment_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* left */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__331_33;
}
static void cont__331_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 900: ... source_position_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* left */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__331_34;
}
static void cont__331_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__4 */ = arguments->slots[0];
  // 901: ... end_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* right */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__331_35;
}
static void cont__331_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__5 */ = arguments->slots[0];
  // 893: !right
  // 894:   function_call
  // 895:     .functor_of functor
  // 896:     .arguments_of list(left right)
  // 897:     .is_in_infix_notation true
  // 898:     .enumeration_no_of enumeration_no_of(left)
  // 899:     .fragment_of fragment_of(left)
  // 900:     .source_position_of source_position_of(left)
  // 901:     .end_position_of end_position_of(right)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[7] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[10] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__is_in_infix_notation, get__true());
    set_attribute_value(temp->attributes, poly_idx__enumeration_no_of, frame->slots[11] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[12] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[13] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[14] /* temp__5 */);
    ((CELL *)frame->slots[4])->contents /* right */ = temp;

  }
  // 902: pop &operator_stack $_dummy
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* operator_stack */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__331_36;
}
static void cont__331_36(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* operator_stack */ = arguments->slots[0];
  frame->slots[10] /* temp__1 */ = arguments->slots[1];
  // 902: ... _dummy
  initialize_future(frame->slots[9] /* dummy */, frame->slots[10] /* temp__1 */);
  // 903: ... length_of(operator_stack)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* operator_stack */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__331_37;
}
static void cont__331_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 903: ... length_of(operator_stack) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__331_38;
}
static void cont__331_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 903: if length_of(operator_stack) == 0 break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__331_39(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__331_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 904: push &operand_stack right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* operand_stack */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__331_41;
}
static void cont__331_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* operand_stack */ = arguments->slots[0];
  // 905: push &operator_stack next_operator
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* operator_stack */;
  arguments->slots[1] = frame->slots[1] /* next_operator */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__331_42;
}
static void cont__331_42(void) {
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
static void cont__331_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* operators */, arguments->slots[0]);
  // 872: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__331_44;
}
static void cont__331_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 872: $$operand_stack list(arguments(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__331_45;
}
static void cont__331_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* operand_stack */ = arguments->slots[0];
  // 873: ... operators(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* operators */;
  func = myself->type;
  frame->cont = cont__331_46;
}
static void cont__331_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 873: $$operator_stack list(operators(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__331_47;
}
static void cont__331_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* operator_stack */ = arguments->slots[0];
  // 907: ... : (i)
  // 908:   update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
  frame->slots[7] /* temp__1 */ = create_closure(entry__331_48, 1);
  // 907: from_to 2 n: (i)
  // 908:   update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[2] /* n */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__331_55;
}
static void entry__331_48(void) {
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
  // 908: ... arguments(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[2] /* arguments */;
  func = myself->type;
  frame->cont = cont__331_49;
}
static void cont__331_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 908: ... i < n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__331_50;
}
static void cont__331_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 908: ... -> operators(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__331_51, 0);
  // 908: ... if(i < n (-> operators(i)) -> undefined)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = func__331_53;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__331_54;
}
static void entry__331_51(void) {
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
  // 908: ... operators(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* i */;
  result_count = 1;
  myself = frame->slots[0] /* operators */;
  func = myself->type;
  frame->cont = cont__331_52;
}
static void cont__331_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 908: ... -> operators(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__331_53(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 908: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__331_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 908: update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* update_stack */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__331_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 909: !node peek(operand_stack)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* operand_stack */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__331_56;
}
static void cont__331_56(void) {
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
static void cont__331_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 910: ... parent.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parent */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__331_58;
}
static void cont__331_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 910: ... :
  // 911:   !node parent(.arguments_of push(arguments_of(parent) node))
  frame->slots[5] /* temp__2 */ = create_closure(entry__331_59, 0);
  // 910: if parent.is_defined:
  // 911:   !node parent(.arguments_of push(arguments_of(parent) node))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__331_62;
}
static void entry__331_59(void) {
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
  // 911: ... arguments_of(parent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parent */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__331_60;
}
static void cont__331_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 911: ... push(arguments_of(parent) node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__331_61;
}
static void cont__331_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 911: !node parent(.arguments_of push(arguments_of(parent) node))
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
static void cont__331_62(void) {
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
static void cont__331_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXTEND_EXPRESSION, arguments->slots[0]);
  // 915: set_node(expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__expression();
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 916: arguments_span(OPERAND)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__332_2;
}
static void cont__332_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 917: ... arguments_span(OPERAND)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__332_3;
}
static void cont__332_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 917: ... INFIX_OPERATOR, arguments_span(OPERAND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._INFIX_OPERATOR;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__332_4;
}
static void cont__332_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 917: some(INFIX_OPERATOR, arguments_span(OPERAND))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__332_5;
}
static void cont__332_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 919: ... multi_capture(operators_of '=')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__332_6;
}
static void cont__332_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 919: infix_operator(multi_capture(operators_of '='))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__332_7;
}
static void cont__332_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 919: infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = var._LINE_END_EXPRESSION;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__332_8;
}
static void cont__332_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 918: optional
  // 919:   infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__332_9;
}
static void cont__332_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 913: $EXPRESSION
  // 914:   sequence
  // 915:     set_node(expression)
  // 916:     arguments_span(OPERAND)
  // 917:     some(INFIX_OPERATOR, arguments_span(OPERAND))
  // 918:     optional
  // 919:       infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  // 920:     EXTEND_EXPRESSION
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
  frame->cont = cont__332_10;
}
static void cont__332_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXPRESSION, arguments->slots[0]);
  // 922: ... span(identifier_of DEFINE_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = var._DEFINE_IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__333_1;
}
static void cont__333_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 922: $DEFINED_VARIABLE expect(span(identifier_of DEFINE_IDENTIFIER) "identifier")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__395c5a51a203e553;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__333_3;
}
static void cont__333_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINED_VARIABLE, arguments->slots[0]);
  // 925: ... set_field(is_used_as_a_polymorphic_function true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_used_as_a_polymorphic_function();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__334_1;
}
static void cont__334_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 924: $NAME_OF_POLYMORPHIC
  // 925:   IDENTIFIER, set_field(is_used_as_a_polymorphic_function true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
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
  initialize_future(var._NAME_OF_POLYMORPHIC, arguments->slots[0]);
  // 935: set_field(attribute_kind_of ATTRIBUTE_KIND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_kind_of();
  arguments->slots[1] = get__ATTRIBUTE_KIND();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__335_1;
}
static void cont__335_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 936: span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__335_2;
}
static void cont__335_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 933: sequence
  // 934:   '.'
  // 935:   set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 936:   span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__335_3;
}
static void cont__335_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 939: followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__335_4;
}
static void cont__335_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 940: set_field(attribute_kind_of METHOD_KIND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_kind_of();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__335_5;
}
static void cont__335_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 937: sequence
  // 938:   '/'
  // 939:   followed_by(':')
  // 940:   set_field(attribute_kind_of METHOD_KIND)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  arguments->slots[2] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__335_6;
}
static void cont__335_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 943: set_field(attribute_kind_of METHOD_KIND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_kind_of();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__335_7;
}
static void cont__335_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 944: span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__attribute_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__335_8;
}
static void cont__335_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 941: sequence
  // 942:   '/'
  // 943:   set_field(attribute_kind_of METHOD_KIND)
  // 944:   span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[10] /* temp__11 */;
  arguments->slots[2] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__335_9;
}
static void cont__335_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 932: alt
  // 933:   sequence
  // 934:     '.'
  // 935:     set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 936:     span(attribute_of NAME_OF_POLYMORPHIC)
  // 937:   sequence
  // 938:     '/'
  // 939:     followed_by(':')
  // 940:     set_field(attribute_kind_of METHOD_KIND)
  // 941:   sequence
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__335_10;
}
static void cont__335_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 931: sequence
  // 932:   alt
  // 933:     sequence
  // 934:       '.'
  // 935:       set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 936:       span(attribute_of NAME_OF_POLYMORPHIC)
  // 937:     sequence
  // 938:       '/'
  // 939:       followed_by(':')
  // 940:       set_field(attribute_kind_of METHOD_KIND)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__335_11;
}
static void cont__335_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 930: optional
  // 931:   sequence
  // 932:     alt
  // 933:       sequence
  // 934:         '.'
  // 935:         set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 936:         span(attribute_of NAME_OF_POLYMORPHIC)
  // 937:       sequence
  // 938:         '/'
  // 939:         followed_by(':')
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__335_12;
}
static void cont__335_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 927: $DEFINED_VARIABLE_OR_ATTRIBUTE
  // 928:   sequence
  // 929:     DEFINED_VARIABLE
  // 930:     optional
  // 931:       sequence
  // 932:         alt
  // 933:           sequence
  // 934:             '.'
  // 935:             set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 936:             span(attribute_of NAME_OF_POLYMORPHIC)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._DEFINED_VARIABLE;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__335_13;
}
static void cont__335_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINED_VARIABLE_OR_ATTRIBUTE, arguments->slots[0]);
  // 947: ... set_node(define_static_single)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_single();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__336_1;
}
static void cont__336_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 946: $DEFINE_STATIC_SINGLE
  // 947:   '$', set_node(define_static_single), DEFINED_VARIABLE_OR_ATTRIBUTE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__36;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._DEFINED_VARIABLE_OR_ATTRIBUTE;
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
  initialize_future(var._DEFINE_STATIC_SINGLE, arguments->slots[0]);
  // 949: ... set_node(define_static_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__337_1;
}
static void cont__337_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 949: $DEFINE_STATIC_MULTI "$$", set_node(define_static_multi), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6282be1;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._DEFINED_VARIABLE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__337_3;
}
static void cont__337_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_STATIC_MULTI, arguments->slots[0]);
  // 950: ... set_node(define_dynamic_single)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_dynamic_single();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__338_1;
}
static void cont__338_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 950: $DEFINE_DYNAMIC_SINGLE '%', set_node(define_dynamic_single), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__37;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._DEFINED_VARIABLE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__338_2;
}
static void cont__338_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_DYNAMIC_SINGLE, arguments->slots[0]);
  // 951: ... set_node(define_dynamic_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_dynamic_multi();
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
  // 951: $DEFINE_DYNAMIC_MULTI "%%", set_node(define_dynamic_multi), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6202be0;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._DEFINED_VARIABLE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__339_3;
}
static void cont__339_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_DYNAMIC_MULTI, arguments->slots[0]);
  // 956: modify_node
  // 957:   : (&node)
  // 958:     !node
  // 959:       function_call
  // 960:         .arguments_of list(node)
  // 961:         .is_an_attribute_access true
  // 962:         .is_a_method_definition true
  // 963:         .fragment_of fragment_of(node)
  // 964:         .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__340_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__340_5;
}
static void entry__340_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 960: ... list(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__340_2;
}
static void cont__340_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 963: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__340_3;
}
static void cont__340_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 964: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__340_4;
}
static void cont__340_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 958: !node
  // 959:   function_call
  // 960:     .arguments_of list(node)
  // 961:     .is_an_attribute_access true
  // 962:     .is_a_method_definition true
  // 963:     .fragment_of fragment_of(node)
  // 964:     .source_position_of source_position_of(node)
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
static void cont__340_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 965: ... followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__340_6;
}
static void cont__340_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 965: ... span(functor_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__340_7;
}
static void cont__340_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 965: alt(followed_by(':') span(functor_of NAME_OF_POLYMORPHIC))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__340_8;
}
static void cont__340_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 953: $METHOD_DEFINITION
  // 954:   sequence
  // 955:     '/'
  // 956:     modify_node
  // 957:       : (&node)
  // 958:         !node
  // 959:           function_call
  // 960:             .arguments_of list(node)
  // 961:             .is_an_attribute_access true
  // 962:             .is_a_method_definition true
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
  frame->cont = cont__340_9;
}
static void cont__340_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._METHOD_DEFINITION, arguments->slots[0]);
  // 968: ... optional(METHOD_DEFINITION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._METHOD_DEFINITION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__341_1;
}
static void cont__341_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 968: $ASSIGN '!', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(METHOD_DEFINITION)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__33;
  arguments->slots[1] = var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__341_2;
}
static void cont__341_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ASSIGN, arguments->slots[0]);
  // 970: $DESTINATION
  // 971:   alt
  // 972:     DEFINE_STATIC_MULTI
  // 973:     DEFINE_STATIC_SINGLE
  // 974:     DEFINE_DYNAMIC_MULTI
  // 975:     DEFINE_DYNAMIC_SINGLE
  // 976:     ASSIGN
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
  frame->cont = cont__342_1;
}
static void cont__342_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DESTINATION, arguments->slots[0]);
  // 981: set_node(backquoted)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__backquoted();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__343_1;
}
static void cont__343_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 982: ... alt(OPERAND DESTINATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  arguments->slots[1] = var._DESTINATION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__343_2;
}
static void cont__343_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 982: ... span(expression_of alt(OPERAND DESTINATION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__expression_of();
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__343_3;
}
static void cont__343_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 982: capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__text_of();
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__343_4;
}
static void cont__343_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 978: $BACKQUOTED
  // 979:   sequence
  // 980:     '`'
  // 981:     set_node(backquoted)
  // 982:     capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__96;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__343_5;
}
static void cont__343_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BACKQUOTED, arguments->slots[0]);
  // 984: ... alt(EXPRESSION BODY)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = var._BODY;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__344_1;
}
static void cont__344_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 984: $INPUT_ARGUMENT arguments_span(alt(EXPRESSION BODY))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__344_2;
}
static void cont__344_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INPUT_ARGUMENT, arguments->slots[0]);
  // 988: ... set_field(is_an_optional_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_an_optional_item();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__345_1;
}
static void cont__345_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 988: '?', set_field(is_an_optional_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__63;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__345_2;
}
static void cont__345_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 989: ... set_field(is_an_expanded_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_an_expanded_item();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__345_3;
}
static void cont__345_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 989: '*', set_field(is_an_expanded_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__345_4;
}
static void cont__345_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 986: $EXPANSION
  // 987:   alt
  // 988:     '?', set_field(is_an_optional_item true)
  // 989:     '*', set_field(is_an_expanded_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__345_5;
}
static void cont__345_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXPANSION, arguments->slots[0]);
  // 991: ... optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__346_1;
}
static void cont__346_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 991: ... DESTINATION, optional(EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._DESTINATION;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__346_2;
}
static void cont__346_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 991: $OUTPUT_ARGUMENT output_arguments_span(DESTINATION, optional(EXPANSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__346_3;
}
static void cont__346_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OUTPUT_ARGUMENT, arguments->slots[0]);
  // 995: ... optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__347_1;
}
static void cont__347_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 995: '&', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(EXPANSION)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__38;
  arguments->slots[1] = var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__347_2;
}
static void cont__347_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 993: $INPUT_OUTPUT_ARGUMENT
  // 994:   output_arguments_span
  // 995:     '&', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__347_3;
}
static void cont__347_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INPUT_OUTPUT_ARGUMENT, arguments->slots[0]);
  //  997: $COPY_OUTPUT
  //  998:   #
  //  999:     copy an input-output argument as an additional input argument
  // 1000:   
  // 1001:   modify_node
  // 1002:     : (&node)
  // 1003:       push
  // 1004:         &node.arguments_of
  // 1005:         output_arguments_of(node)(-1)(.is_a_destination false)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__348_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__348_7;
}
static void entry__348_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1004: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__348_2;
}
static void cont__348_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1005: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__348_3;
}
static void cont__348_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 1005: output_arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__348_4;
}
static void cont__348_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 1005: output_arguments_of(node)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__5 */;
  func = myself->type;
  frame->cont = cont__348_5;
}
static void cont__348_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1005: output_arguments_of(node)(-1)(.is_a_destination false)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[3] /* temp__3 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__false());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 1003: push
  // 1004:   &node.arguments_of
  // 1005:   output_arguments_of(node)(-1)(.is_a_destination false)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__348_6;
}
static void cont__348_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 1004: &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__6 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__348_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._COPY_OUTPUT, arguments->slots[0]);
  // 1007: $MAYBE_SPLIT_INPUT
  // 1008:   #
  // 1009:     split things like
  // 1010:     
  // 1011:     `$var
  // 1012:     
  // 1013:     into an input and an output argument
  // 1014:   
  // 1015:   modify_node
  // 1016:     : (&node)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__349_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__349_18;
}
static void entry__349_1(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // node: 0
  // argument: 1
  // expression: 2
  frame->slots[1] /* argument */ = create_future();
  frame->slots[2] /* expression */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1017: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__349_2;
}
static void cont__349_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1017: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__349_3;
}
static void cont__349_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1017: $argument arguments_of(node)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__349_4;
}
static void cont__349_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* argument */, arguments->slots[0]);
  // 1018: $expression expression_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__expression_of();
  func = myself->type;
  frame->cont = cont__349_5;
}
static void cont__349_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* expression */, arguments->slots[0]);
  // 1019: ... expression.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* expression */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__349_6;
}
static void cont__349_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1019: ... expression.is_a_destination
  frame->slots[5] /* temp__3 */ = create_closure(entry__349_7, 0);
  // 1019: ... expression.is_a_definition || expression.is_a_destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__349_9;
}
static void entry__349_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* expression */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1019: ... expression.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  result_count = 1;
  myself = get__is_a_destination();
  func = myself->type;
  frame->cont = cont__349_8;
}
static void cont__349_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1019: ... expression.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__349_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1019: ... :
  // 1020:   push &node.output_arguments_of expression
  // 1021:   !node.arguments_of(-1)
  // 1022:     string_literal(.node::text_of node::text_of(argument))
  frame->slots[6] /* temp__4 */ = create_closure(entry__349_10, 0);
  // 1019: if expression.is_a_definition || expression.is_a_destination:
  // 1020:   push &node.output_arguments_of expression
  // 1021:   !node.arguments_of(-1)
  // 1022:     string_literal(.node::text_of node::text_of(argument))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__349_17;
}
static void entry__349_10(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // node: 0
  // expression: 1
  // argument: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[2]; /* expression */
  frame->slots[2] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1020: ... node.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__349_11;
}
static void cont__349_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1020: push &node.output_arguments_of expression
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* expression */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__349_12;
}
static void cont__349_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1020: ... &node.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1022: ... node::text_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__349_13;
}
static void cont__349_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1021: !node.arguments_of(-1)
  // 1022:   string_literal(.node::text_of node::text_of(argument))
  {
    NODE *temp = clone_object_and_attributes(get__string_literal());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, frame->slots[3] /* temp__1 */);
    frame->slots[4] /* temp__2 */ = temp;

  }
  // 1021: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__349_14;
}
static void cont__349_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1021: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__349_15;
}
static void cont__349_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 1021: !node.arguments_of(-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__349_16;
}
static void cont__349_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1021: !node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[5] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__349_17(void) {
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
static void cont__349_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAYBE_SPLIT_INPUT, arguments->slots[0]);
  // 1026: ... optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__350_1;
}
static void cont__350_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1026: ... EXPRESSION, optional(EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__350_2;
}
static void cont__350_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1026: arguments_span(EXPRESSION, optional(EXPANSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__350_3;
}
static void cont__350_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1028: INPUT_OUTPUT_ARGUMENT, COPY_OUTPUT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._INPUT_OUTPUT_ARGUMENT;
  arguments->slots[1] = var._COPY_OUTPUT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__350_4;
}
static void cont__350_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1029: arguments_span(BACKQUOTED)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._BACKQUOTED;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__350_5;
}
static void cont__350_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1029: arguments_span(BACKQUOTED), MAYBE_SPLIT_INPUT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = var._MAYBE_SPLIT_INPUT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__350_6;
}
static void cont__350_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1024: $SIMPLE_ARGUMENT
  // 1025:   alt
  // 1026:     arguments_span(EXPRESSION, optional(EXPANSION))
  // 1027:     OUTPUT_ARGUMENT
  // 1028:     INPUT_OUTPUT_ARGUMENT, COPY_OUTPUT
  // 1029:     arguments_span(BACKQUOTED), MAYBE_SPLIT_INPUT
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._OUTPUT_ARGUMENT;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  arguments->slots[3] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__350_7;
}
static void cont__350_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMPLE_ARGUMENT, arguments->slots[0]);
  // 1037: set_node(attribute_value_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_value_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__351_1;
}
static void cont__351_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1038: span(identifier_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__351_2;
}
static void cont__351_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1036: sequence
  // 1037:   set_node(attribute_value_pair)
  // 1038:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1039:   sim2c::WHITESPACE
  // 1040:   INPUT_ARGUMENT
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = var.sim2c__WHITESPACE;
  arguments->slots[3] = var._INPUT_ARGUMENT;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__351_3;
}
static void cont__351_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1035: arguments_span
  // 1036:   sequence
  // 1037:     set_node(attribute_value_pair)
  // 1038:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1039:     sim2c::WHITESPACE
  // 1040:     INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__351_4;
}
static void cont__351_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1033: sequence
  // 1034:   '.'
  // 1035:   arguments_span
  // 1036:     sequence
  // 1037:       set_node(attribute_value_pair)
  // 1038:       span(identifier_of NAME_OF_POLYMORPHIC)
  // 1039:       sim2c::WHITESPACE
  // 1040:       INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__351_5;
}
static void cont__351_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1043: followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__351_6;
}
static void cont__351_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1045: set_node(attribute_function_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__351_7;
}
static void cont__351_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1045: set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__10 */;
  arguments->slots[1] = var._SEPARATOR;
  arguments->slots[2] = var._INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__351_8;
}
static void cont__351_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1044: arguments_span
  // 1045:   set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__351_9;
}
static void cont__351_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1041: sequence
  // 1042:   '/'
  // 1043:   followed_by(':')
  // 1044:   arguments_span
  // 1045:     set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  arguments->slots[2] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__351_10;
}
static void cont__351_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1050: set_node(attribute_function_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__351_11;
}
static void cont__351_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 1051: span(identifier_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__351_12;
}
static void cont__351_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 1049: sequence
  // 1050:   set_node(attribute_function_pair)
  // 1051:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1052:   SEPARATOR
  // 1053:   INPUT_ARGUMENT
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__14 */;
  arguments->slots[1] = frame->slots[14] /* temp__15 */;
  arguments->slots[2] = var._SEPARATOR;
  arguments->slots[3] = var._INPUT_ARGUMENT;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__351_13;
}
static void cont__351_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1048: arguments_span
  // 1049:   sequence
  // 1050:     set_node(attribute_function_pair)
  // 1051:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1052:     SEPARATOR
  // 1053:     INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__351_14;
}
static void cont__351_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1046: sequence
  // 1047:   '/'
  // 1048:   arguments_span
  // 1049:     sequence
  // 1050:       set_node(attribute_function_pair)
  // 1051:       span(identifier_of NAME_OF_POLYMORPHIC)
  // 1052:       SEPARATOR
  // 1053:       INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__351_15;
}
static void cont__351_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1031: $INLINE_ATTRIBUTE_VALUE_PAIR
  // 1032:   alt
  // 1033:     sequence
  // 1034:       '.'
  // 1035:       arguments_span
  // 1036:         sequence
  // 1037:           set_node(attribute_value_pair)
  // 1038:           span(identifier_of NAME_OF_POLYMORPHIC)
  // 1039:           sim2c::WHITESPACE
  // 1040:           INPUT_ARGUMENT
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__351_16;
}
static void cont__351_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INLINE_ATTRIBUTE_VALUE_PAIR, arguments->slots[0]);
  // 1057: ... REMARK_BEHIND, NEWLINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_BEHIND;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__352_1;
}
static void cont__352_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1057: some(REMARK_BEHIND, NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1063: set_node(attribute_value_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_value_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__352_3;
}
static void cont__352_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1064: span(identifier_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__352_4;
}
static void cont__352_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1062: sequence
  // 1063:   set_node(attribute_value_pair)
  // 1064:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1065:   SINGLE_INPUT_ARGUMENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  arguments->slots[2] = var._SINGLE_INPUT_ARGUMENT;
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
  // 1061: arguments_span
  // 1062:   sequence
  // 1063:     set_node(attribute_value_pair)
  // 1064:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1065:     SINGLE_INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__352_6;
}
static void cont__352_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1059: sequence
  // 1060:   '.'
  // 1061:   arguments_span
  // 1062:     sequence
  // 1063:       set_node(attribute_value_pair)
  // 1064:       span(identifier_of NAME_OF_POLYMORPHIC)
  // 1065:       SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
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
  // 1068: followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__352_8;
}
static void cont__352_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1069: ... set_node(attribute_function_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__352_9;
}
static void cont__352_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1069: ... set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__13 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__352_10;
}
static void cont__352_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1069: arguments_span(set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__352_11;
}
static void cont__352_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1066: sequence
  // 1067:   '/'
  // 1068:   followed_by(':')
  // 1069:   arguments_span(set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[9] /* temp__10 */;
  arguments->slots[2] = frame->slots[10] /* temp__11 */;
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
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1074: set_node(attribute_function_pair)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__352_13;
}
static void cont__352_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  // 1075: span(identifier_of NAME_OF_POLYMORPHIC)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = var._NAME_OF_POLYMORPHIC;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__352_14;
}
static void cont__352_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 1073: sequence
  // 1074:   set_node(attribute_function_pair)
  // 1075:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1076:   SINGLE_INPUT_ARGUMENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__17 */;
  arguments->slots[1] = frame->slots[17] /* temp__18 */;
  arguments->slots[2] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__352_15;
}
static void cont__352_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 1072: arguments_span
  // 1073:   sequence
  // 1074:     set_node(attribute_function_pair)
  // 1075:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1076:     SINGLE_INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__16 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__352_16;
}
static void cont__352_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 1070: sequence
  // 1071:   '/'
  // 1072:   arguments_span
  // 1073:     sequence
  // 1074:       set_node(attribute_function_pair)
  // 1075:       span(identifier_of NAME_OF_POLYMORPHIC)
  // 1076:       SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[14] /* temp__15 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__352_17;
}
static void cont__352_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 1058: alt
  // 1059:   sequence
  // 1060:     '.'
  // 1061:     arguments_span
  // 1062:       sequence
  // 1063:         set_node(attribute_value_pair)
  // 1064:         span(identifier_of NAME_OF_POLYMORPHIC)
  // 1065:         SINGLE_INPUT_ARGUMENT
  // 1066:   sequence
  // 1067:     '/'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  arguments->slots[2] = frame->slots[13] /* temp__14 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__352_18;
}
static void cont__352_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1055: $ATTRIBUTE_VALUE_PAIR
  // 1056:   sequence
  // 1057:     some(REMARK_BEHIND, NEWLINES)
  // 1058:     alt
  // 1059:       sequence
  // 1060:         '.'
  // 1061:         arguments_span
  // 1062:           sequence
  // 1063:             set_node(attribute_value_pair)
  // 1064:             span(identifier_of NAME_OF_POLYMORPHIC)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__352_19;
}
static void cont__352_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ATTRIBUTE_VALUE_PAIR, arguments->slots[0]);
  // 1078: $INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1079:   interleaved(INLINE_ATTRIBUTE_VALUE_PAIR sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._INLINE_ATTRIBUTE_VALUE_PAIR;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__353_1;
}
static void cont__353_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INLINE_ATTRIBUTE_VALUE_PAIRS, arguments->slots[0]);
  // 1082: ... interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ATTRIBUTE_VALUE_PAIR;
  arguments->slots[1] = var._NEXT_LINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__354_1;
}
static void cont__354_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1082: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__354_2;
}
static void cont__354_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1081: $INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1082:   INDENT, interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE), expect(outdent_marker)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__354_3;
}
static void cont__354_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INDENTED_ATTRIBUTE_VALUE_PAIRS, arguments->slots[0]);
  // 1085: ... LINE_START_ARGUMENT, ARGUMENT_LINE_END_REMARK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_START_ARGUMENT;
  arguments->slots[1] = var._ARGUMENT_LINE_END_REMARK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__355_1;
}
static void cont__355_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1084: $SINGLE_EXPRESSION_LINE
  // 1085:   alt(LINE_START_ARGUMENT, ARGUMENT_LINE_END_REMARK LINE_END_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._LINE_END_EXPRESSION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__355_2;
}
static void cont__355_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SINGLE_EXPRESSION_LINE, arguments->slots[0]);
  // 1092: ... SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMPLE_ARGUMENT;
  arguments->slots[1] = var._PROCEDURE_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__356_1;
}
static void cont__356_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1092: alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_EXPRESSION;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__356_2;
}
static void cont__356_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1090: sequence
  // 1091:   SEPARATOR
  // 1092:   alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SEPARATOR;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__356_3;
}
static void cont__356_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1098: some(NEWLINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__356_4;
}
static void cont__356_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1100: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__356_5;
}
static void cont__356_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1096: sequence
  // 1097:   INDENT
  // 1098:   some(NEWLINE)
  // 1099:   FIRST_LINE_START_ARGUMENTS
  // 1100:   expect(outdent_marker)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  arguments->slots[2] = var._FIRST_LINE_START_ARGUMENTS;
  arguments->slots[3] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__356_6;
}
static void cont__356_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1095: optional
  // 1096:   sequence
  // 1097:     INDENT
  // 1098:     some(NEWLINE)
  // 1099:     FIRST_LINE_START_ARGUMENTS
  // 1100:     expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__356_7;
}
static void cont__356_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1093: sequence
  // 1094:   LINE_END_REMARK
  // 1095:   optional
  // 1096:     sequence
  // 1097:       INDENT
  // 1098:       some(NEWLINE)
  // 1099:       FIRST_LINE_START_ARGUMENTS
  // 1100:       expect(outdent_marker)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__356_8;
}
static void cont__356_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1089: alt
  // 1090:   sequence
  // 1091:     SEPARATOR
  // 1092:     alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
  // 1093:   sequence
  // 1094:     LINE_END_REMARK
  // 1095:     optional
  // 1096:       sequence
  // 1097:         INDENT
  // 1098:         some(NEWLINE)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__356_9;
}
static void cont__356_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1087: $PROCEDURE_ARGUMENTS
  // 1088:   optional
  // 1089:     alt
  // 1090:       sequence
  // 1091:         SEPARATOR
  // 1092:         alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
  // 1093:       sequence
  // 1094:         LINE_END_REMARK
  // 1095:         optional
  // 1096:           sequence
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__356_10;
}
static void cont__356_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PROCEDURE_ARGUMENTS, arguments->slots[0]);
  // 1106: ... SEPARATOR, ARGUMENT_REMARK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SEPARATOR;
  arguments->slots[1] = var._ARGUMENT_REMARK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__357_1;
}
static void cont__357_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1106: optional(SEPARATOR, ARGUMENT_REMARK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__357_2;
}
static void cont__357_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1107: ... NEWLINES, MORE_LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._MORE_LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__357_3;
}
static void cont__357_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1107: optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__357_4;
}
static void cont__357_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1104: sequence
  // 1105:   LINE_END_EXPRESSION
  // 1106:   optional(SEPARATOR, ARGUMENT_REMARK)
  // 1107:   optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_EXPRESSION;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__357_5;
}
static void cont__357_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1110: ... SEPARATOR, ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SEPARATOR;
  arguments->slots[1] = var._ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__357_6;
}
static void cont__357_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1110: ... NEWLINES, MORE_LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._MORE_LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__357_7;
}
static void cont__357_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1110: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__357_8;
}
static void cont__357_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1110: alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__357_9;
}
static void cont__357_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1108: sequence
  // 1109:   SIMPLE_ARGUMENT
  // 1110:   alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMPLE_ARGUMENT;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__357_10;
}
static void cont__357_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1111: ... NEWLINES, MORE_LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._MORE_LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__357_11;
}
static void cont__357_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1111: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__357_12;
}
static void cont__357_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1111: sequence(ARGUMENT_REMARK optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_REMARK;
  arguments->slots[1] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__357_13;
}
static void cont__357_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1102: $ARGUMENTS
  // 1103:   alt
  // 1104:     sequence
  // 1105:       LINE_END_EXPRESSION
  // 1106:       optional(SEPARATOR, ARGUMENT_REMARK)
  // 1107:       optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  // 1108:     sequence
  // 1109:       SIMPLE_ARGUMENT
  // 1110:       alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  // 1111:     sequence(ARGUMENT_REMARK optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__357_14;
}
static void cont__357_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENTS, arguments->slots[0]);
  // 1115: ... arguments_span(OPERAND)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__358_1;
}
static void cont__358_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1115: sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INFIX_OPERATOR;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = var._OPERATORS_AND_OPERANDS;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__358_2;
}
static void cont__358_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1113: $OPERATORS_AND_OPERANDS
  // 1114:   alt
  // 1115:     sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
  // 1116:     EXTEND_EXPRESSION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._EXTEND_EXPRESSION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__358_3;
}
static void cont__358_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._OPERATORS_AND_OPERANDS, arguments->slots[0]);
  // 1122: modify_node
  // 1123:   : (node)
  // 1124:     -> function_call(.parent_of node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__359_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__359_2;
}
static void entry__359_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1124: ... function_call(.parent_of node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parent_of, frame->slots[0] /* node */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1124: -> function_call(.parent_of node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__359_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1125: ... interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ATTRIBUTE_VALUE_PAIR;
  arguments->slots[1] = var._NEXT_LINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__359_3;
}
static void cont__359_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1125: alt(LINE_START_ARGUMENTS interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_START_ARGUMENTS;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__359_4;
}
static void cont__359_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1127: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__359_5;
}
static void cont__359_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1128: modify_node
  // 1129:   : (node)
  // 1130:     # rotate the subnodes to generate the correct function call argument
  // 1131:     
  // 1132:     $top_level_node parent_of(node)
  // 1133:     $top_level_arguments arguments_of(top_level_node)
  // 1134:     $functor top_level_arguments(-1)
  // 1135:     
  // 1136:     $new_arguments
  // 1137:       push
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__359_6;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__359_21;
}
static void entry__359_6(void) {
  allocate_initialized_frame_gc(1, 16);
  // slot allocations:
  // node: 0
  // top_level_node: 1
  // top_level_arguments: 2
  // functor: 3
  // new_arguments: 4
  frame->slots[1] /* top_level_node */ = create_future();
  frame->slots[2] /* top_level_arguments */ = create_future();
  frame->slots[3] /* functor */ = create_future();
  frame->slots[4] /* new_arguments */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1132: $top_level_node parent_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__parent_of();
  func = myself->type;
  frame->cont = cont__359_7;
}
static void cont__359_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* top_level_node */, arguments->slots[0]);
  // 1133: $top_level_arguments arguments_of(top_level_node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* top_level_node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__359_8;
}
static void cont__359_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* top_level_arguments */, arguments->slots[0]);
  // 1134: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__359_9;
}
static void cont__359_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1134: $functor top_level_arguments(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[2] /* top_level_arguments */;
  func = myself->type;
  frame->cont = cont__359_10;
}
static void cont__359_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* functor */, arguments->slots[0]);
  // 1138: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__359_11;
}
static void cont__359_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1138: range(top_level_arguments 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* top_level_arguments */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__359_12;
}
static void cont__359_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1141: functor
  // 1142:   .enumeration_no_of undefined
  // 1143:   .remark_lines_of empty_list
  {
    NODE *temp = clone_object_and_attributes(frame->slots[3] /* functor */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__enumeration_no_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, get__empty_list());
    frame->slots[8] /* temp__4 */ = temp;

  }
  // 1144: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__359_13;
}
static void cont__359_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 1145: ... output_arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__359_14;
}
static void cont__359_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 1146: ... enumeration_no_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* functor */;
  result_count = 1;
  myself = get__enumeration_no_of();
  func = myself->type;
  frame->cont = cont__359_15;
}
static void cont__359_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__7 */ = arguments->slots[0];
  // 1147: ... remark_lines_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* functor */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__359_16;
}
static void cont__359_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__8 */ = arguments->slots[0];
  // 1148: ... fragment_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* functor */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__359_17;
}
static void cont__359_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__9 */ = arguments->slots[0];
  // 1149: ... source_position_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* functor */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__359_18;
}
static void cont__359_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__10 */ = arguments->slots[0];
  // 1150: ... end_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__359_19;
}
static void cont__359_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__11 */ = arguments->slots[0];
  // 1139: function_call
  // 1140:   .functor_of
  // 1141:     functor
  // 1142:       .enumeration_no_of undefined
  // 1143:       .remark_lines_of empty_list
  // 1144:   .arguments_of arguments_of(node)
  // 1145:   .output_arguments_of output_arguments_of(node)
  // 1146:   .enumeration_no_of enumeration_no_of(functor)
  // 1147:   .remark_lines_of remark_lines_of(functor)
  // 1148:   .fragment_of fragment_of(functor)
  // ...
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[8] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[10] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__enumeration_no_of, frame->slots[11] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[12] /* temp__8 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[13] /* temp__9 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[14] /* temp__10 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[15] /* temp__11 */);
    frame->slots[7] /* temp__3 */ = temp;

  }
  // 1136: $new_arguments
  // 1137:   push
  // 1138:     range(top_level_arguments 1 -2)
  // 1139:     function_call
  // 1140:       .functor_of
  // 1141:         functor
  // 1142:           .enumeration_no_of undefined
  // 1143:           .remark_lines_of empty_list
  // 1144:       .arguments_of arguments_of(node)
  // 1145:       .output_arguments_of output_arguments_of(node)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__359_20;
}
static void cont__359_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* new_arguments */, arguments->slots[0]);
  // 1152: ... top_level_node(.arguments_of new_arguments)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* top_level_node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* new_arguments */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 1152: -> top_level_node(.arguments_of new_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__359_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1118: $MULTI_LINE_FUNCTION_CALL
  // 1119:   # store the current node in the parent slot for later retrieval
  // 1120:   
  // 1121:   sequence
  // 1122:     modify_node
  // 1123:       : (node)
  // 1124:         -> function_call(.parent_of node)
  // 1125:     alt(LINE_START_ARGUMENTS interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE))
  // 1126:     STORE_END_POSITION
  // 1127:     expect(outdent_marker)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = var._STORE_END_POSITION;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  arguments->slots[4] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__359_22;
}
static void cont__359_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_FUNCTION_CALL, arguments->slots[0]);
  // 1160: modify_node
  // 1161:   : (&node)
  // 1162:     !node.original_remark_lines_of remark_lines_of(node)
  // 1163:     !node.remark_lines_of empty_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__361_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__361_3;
}
static void entry__361_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1162: !node.original_remark_lines_of remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__361_2;
}
static void cont__361_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1162: !node.original_remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__original_remark_lines_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1163: !node.remark_lines_of empty_list
  frame->slots[1] /* temp__1 */ = get__empty_list();
  // 1163: !node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__361_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1165: modify_node
  // 1166:   : (&node)
  // 1167:     $n length_of(arguments_of(node))
  // 1168:     if n > 0:
  // 1169:       append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1170:       !node.remark_lines_of empty_list
  // 1171:     !node.remark_lines_of original_remark_lines_of(node)
  // 1172:     !node.original_remark_lines_of undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__361_4;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__361_19;
}
static void entry__361_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  // n: 1
  frame->slots[1] /* n */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1167: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__361_5;
}
static void cont__361_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1167: $n length_of(arguments_of(node))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__361_6;
}
static void cont__361_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* n */, arguments->slots[0]);
  // 1168: ... n > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[1] /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__361_7;
}
static void cont__361_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1168: ... :
  // 1169:   append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1170:   !node.remark_lines_of empty_list
  frame->slots[3] /* temp__2 */ = create_closure(entry__361_8, 0);
  // 1168: if n > 0:
  // 1169:   append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1170:   !node.remark_lines_of empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__361_17;
}
static void entry__361_8(void) {
  allocate_initialized_frame_gc(2, 9);
  // slot allocations:
  // node: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1169: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__361_9;
}
static void cont__361_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1169: ... node.arguments_of(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  result_count = 1;
  myself = frame->slots[4] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__361_10;
}
static void cont__361_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1169: ... node.arguments_of(n).remark_lines_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__361_11;
}
static void cont__361_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1169: ... remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__361_12;
}
static void cont__361_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 1169: append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__361_13;
}
static void cont__361_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 1169: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__361_14;
}
static void cont__361_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 1169: ... node.arguments_of(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  result_count = 1;
  myself = frame->slots[7] /* temp__6 */;
  func = myself->type;
  frame->cont = cont__361_15;
}
static void cont__361_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 1169: ... &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[8] /* temp__7 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[6] /* temp__5 */);
    frame->slots[8] /* temp__7 */ = temp;

  }
  // 1169: ... &node.arguments_of(n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = frame->slots[7] /* temp__6 */;
  func = myself->type;
  frame->cont = cont__361_16;
}
static void cont__361_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 1169: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__6 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1170: !node.remark_lines_of empty_list
  frame->slots[2] /* temp__1 */ = get__empty_list();
  // 1170: !node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__361_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1171: !node.remark_lines_of original_remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = var._original_remark_lines_of;
  func = myself->type;
  frame->cont = cont__361_18;
}
static void cont__361_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1171: !node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1172: !node.original_remark_lines_of undefined
  frame->slots[2] /* temp__1 */ = get__undefined();
  // 1172: !node.original_remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__original_remark_lines_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__361_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1173: ... sequence(NEWLINES INDENTED_FUNCTION_CALL_OR_REMARK)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._INDENTED_FUNCTION_CALL_OR_REMARK;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__361_20;
}
static void cont__361_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1173: alt(sequence(NEWLINES INDENTED_FUNCTION_CALL_OR_REMARK) OUTDENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = var._OUTDENT;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__361_21;
}
static void cont__361_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1158: sequence
  // 1159:   # ATTENTION: very dirty fix!
  // 1160:   modify_node
  // 1161:     : (&node)
  // 1162:       !node.original_remark_lines_of remark_lines_of(node)
  // 1163:       !node.remark_lines_of empty_list
  // 1164:   REMARK
  // 1165:   modify_node
  // 1166:     : (&node)
  // 1167:       $n length_of(arguments_of(node))
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = var._REMARK;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__361_22;
}
static void cont__361_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1156: $INDENTED_FUNCTION_CALL_OR_REMARK
  // 1157:   alt
  // 1158:     sequence
  // 1159:       # ATTENTION: very dirty fix!
  // 1160:       modify_node
  // 1161:         : (&node)
  // 1162:           !node.original_remark_lines_of remark_lines_of(node)
  // 1163:           !node.remark_lines_of empty_list
  // 1164:       REMARK
  // 1165:       modify_node
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._MULTI_LINE_FUNCTION_CALL;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__361_23;
}
static void cont__361_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INDENTED_FUNCTION_CALL_OR_REMARK, arguments->slots[0]);
  // 1177: ... some(NEWLINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__362_1;
}
static void cont__362_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1176: $MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK
  // 1177:   INDENT, some(NEWLINE), INDENTED_FUNCTION_CALL_OR_REMARK
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._INDENTED_FUNCTION_CALL_OR_REMARK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__362_2;
}
static void cont__362_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK, arguments->slots[0]);
  // 1180: ... alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._NEWLINE;
  arguments->slots[2] = var._OUTDENT;
  arguments->slots[3] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__363_1;
}
static void cont__363_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1180: ... followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__363_2;
}
static void cont__363_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1180: ... '*', followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__363_3;
}
static void cont__363_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1179: $ARGUMENT_EXPANSION
  // 1180:   alt('?' '*', followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__63;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__363_4;
}
static void cont__363_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENT_EXPANSION, arguments->slots[0]);
  // 1184: set_node(operator_symbol)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__operator_symbol();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__364_1;
}
static void cont__364_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1186: capture(name_of INFIX_OPERATOR_SYMBOL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = var._INFIX_OPERATOR_SYMBOL;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__364_2;
}
static void cont__364_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1187: modify_node
  // 1188:   : (node)
  // 1189:     ->
  // 1190:       function_call
  // 1191:         .functor_of node
  // 1192:         .fragment_of fragment_of(node)
  // 1193:         .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__364_3;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__364_6;
}
static void entry__364_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1192: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__364_4;
}
static void cont__364_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1193: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__364_5;
}
static void cont__364_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1190: function_call
  // 1191:   .functor_of node
  // 1192:   .fragment_of fragment_of(node)
  // 1193:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* node */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1189: ->
  // 1190:   function_call
  // 1191:     .functor_of node
  // 1192:     .fragment_of fragment_of(node)
  // 1193:     .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__364_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1197: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__364_7;
}
static void cont__364_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1198: modify_node
  // 1199:   :
  // 1200:     (
  // 1201:       &node
  // 1202:       stream
  // 1203:       -> return
  // 1204:     )
  // 1205:     $$arguments arguments_of(node)
  // 1206:     if length_of(arguments) < 2:
  // 1207:       ParseError stream "too few arguments in multi-line expression"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__364_8;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__364_43;
}
static void entry__364_8(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // node: 0
  // stream: 1
  // return: 2
  // arguments: 3
  frame->slots[2] /* return */ = create_continuation_with_exit(exit__364_8);
  frame->slots[3] /* arguments */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1205: $$arguments arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__364_9;
}
static void cont__364_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* arguments */ = arguments->slots[0];
  // 1206: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__364_10;
}
static void cont__364_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1206: ... length_of(arguments) < 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__364_11;
}
static void cont__364_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1206: ... :
  // 1207:   ParseError stream "too few arguments in multi-line expression"
  frame->slots[6] /* temp__3 */ = create_closure(entry__364_12, 0);
  // 1206: if length_of(arguments) < 2:
  // 1207:   ParseError stream "too few arguments in multi-line expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__364_14;
}
static void entry__364_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1207: ParseError stream "too few arguments in multi-line expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__733ccdbfc49ced05;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__364_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1208: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__364_15;
}
static void cont__364_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1208: ... length_of(arguments) > 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__364_16;
}
static void cont__364_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1208: ... :
  // 1209:   $functor functor_of(node)
  // 1210:   if
  // 1211:     precedence(name_of(functor)).is_left_associative:
  // 1212:       forever:
  // 1213:         !node
  // 1214:           function_call
  // 1215:             .functor_of functor
  // 1216:             .arguments_of range(arguments 1 2)
  // 1217:         if length_of(arguments) == 2 return
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__364_17, 0);
  // 1208: if length_of(arguments) > 2:
  // 1209:   $functor functor_of(node)
  // 1210:   if
  // 1211:     precedence(name_of(functor)).is_left_associative:
  // 1212:       forever:
  // 1213:         !node
  // 1214:           function_call
  // 1215:             .functor_of functor
  // 1216:             .arguments_of range(arguments 1 2)
  // 1217:         if length_of(arguments) == 2 return
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
  frame->cont = cont__364_42;
}
static void entry__364_32(void) {
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
  // 1224: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__364_33;
}
static void cont__364_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1224: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__364_34;
}
static void cont__364_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 1224: ... range(arguments -2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__364_35;
}
static void cont__364_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1221: !node
  // 1222:   function_call
  // 1223:     .functor_of functor
  // 1224:     .arguments_of range(arguments -2 -1)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1225: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__364_36;
}
static void cont__364_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1225: ... length_of(arguments) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__364_37;
}
static void cont__364_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1225: if length_of(arguments) == 2 return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__364_38;
}
static void cont__364_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1226: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__364_39;
}
static void cont__364_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1226: ... range(arguments 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__364_40;
}
static void cont__364_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1226: !arguments push(range(arguments 1 -3) node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__364_41;
}
static void cont__364_41(void) {
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
static void entry__364_23(void) {
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
  // 1216: ... range(arguments 1 2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = number__2;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__364_24;
}
static void cont__364_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1213: !node
  // 1214:   function_call
  // 1215:     .functor_of functor
  // 1216:     .arguments_of range(arguments 1 2)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1217: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__364_25;
}
static void cont__364_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1217: ... length_of(arguments) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__364_26;
}
static void cont__364_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1217: if length_of(arguments) == 2 return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__364_27;
}
static void cont__364_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1218: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__364_28;
}
static void cont__364_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1218: ... range(arguments 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* arguments */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__364_29;
}
static void cont__364_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1218: !arguments put(range(arguments 3 -1) node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__364_30;
}
static void cont__364_30(void) {
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
static void entry__364_22(void) {
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
  // 1212: ... :
  // 1213:   !node
  // 1214:     function_call
  // 1215:       .functor_of functor
  // 1216:       .arguments_of range(arguments 1 2)
  // 1217:   if length_of(arguments) == 2 return
  // 1218:   !arguments put(range(arguments 3 -1) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__364_23, 0);
  // 1212: forever:
  // 1213:   !node
  // 1214:     function_call
  // 1215:       .functor_of functor
  // 1216:       .arguments_of range(arguments 1 2)
  // 1217:   if length_of(arguments) == 2 return
  // 1218:   !arguments put(range(arguments 3 -1) node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__364_31(void) {
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
  // 1220: ... :
  // 1221:   !node
  // 1222:     function_call
  // 1223:       .functor_of functor
  // 1224:       .arguments_of range(arguments -2 -1)
  // 1225:   if length_of(arguments) == 2 return
  // 1226:   !arguments push(range(arguments 1 -3) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__364_32, 0);
  // 1220: forever:
  // 1221:   !node
  // 1222:     function_call
  // 1223:       .functor_of functor
  // 1224:       .arguments_of range(arguments -2 -1)
  // 1225:   if length_of(arguments) == 2 return
  // 1226:   !arguments push(range(arguments 1 -3) node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__364_17(void) {
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
  // 1209: $functor functor_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__364_18;
}
static void cont__364_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* functor */, arguments->slots[0]);
  // 1211: ... name_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* functor */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__364_19;
}
static void cont__364_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 1211: precedence(name_of(functor))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__precedence();
  func = myself->type;
  frame->cont = cont__364_20;
}
static void cont__364_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1211: precedence(name_of(functor)).is_left_associative
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_left_associative();
  func = myself->type;
  frame->cont = cont__364_21;
}
static void cont__364_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1211: ... :
  // 1212:   forever:
  // 1213:     !node
  // 1214:       function_call
  // 1215:         .functor_of functor
  // 1216:         .arguments_of range(arguments 1 2)
  // 1217:     if length_of(arguments) == 2 return
  // 1218:     !arguments put(range(arguments 3 -1) node)
  frame->slots[7] /* temp__4 */ = create_closure(entry__364_22, 0);
  // 1219: :
  // 1220:   forever:
  // 1221:     !node
  // 1222:       function_call
  // 1223:         .functor_of functor
  // 1224:         .arguments_of range(arguments -2 -1)
  // 1225:     if length_of(arguments) == 2 return
  // 1226:     !arguments push(range(arguments 1 -3) node)
  frame->slots[8] /* temp__5 */ = create_closure(entry__364_31, 0);
  // 1210: if
  // 1211:   precedence(name_of(functor)).is_left_associative:
  // 1212:     forever:
  // 1213:       !node
  // 1214:         function_call
  // 1215:           .functor_of functor
  // 1216:           .arguments_of range(arguments 1 2)
  // 1217:       if length_of(arguments) == 2 return
  // 1218:       !arguments put(range(arguments 3 -1) node)
  // 1219:   :
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
static void cont__364_42(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__364_8(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  func = continuation_type_function;
}
static void cont__364_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1182: $MULTI_LINE_EXPRESSION
  // 1183:   sequence
  // 1184:     set_node(operator_symbol)
  // 1185:     STORE_POSITION
  // 1186:     capture(name_of INFIX_OPERATOR_SYMBOL)
  // 1187:     modify_node
  // 1188:       : (node)
  // 1189:         ->
  // 1190:           function_call
  // 1191:             .functor_of node
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[2] /* temp__3 */;
  arguments->slots[4] = var._INDENT;
  arguments->slots[5] = var._LINE_START_ARGUMENTS;
  arguments->slots[6] = var._STORE_END_POSITION;
  arguments->slots[7] = frame->slots[3] /* temp__4 */;
  arguments->slots[8] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__364_44;
}
static void cont__364_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_EXPRESSION, arguments->slots[0]);
  // 1232: ... not_followed_by(ARGUMENT_EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_EXPANSION;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__365_1;
}
static void cont__365_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1232: IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__365_2;
}
static void cont__365_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1231: arguments_span
  // 1232:   IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__365_3;
}
static void cont__365_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1238: optional(sim2c::WHITESPACE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__365_4;
}
static void cont__365_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1238: optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__11 */;
  arguments->slots[1] = var._INFIX_OPERATOR_SYMBOL;
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
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1240: sim2c::WHITESPACE, '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__365_6;
}
static void cont__365_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1241: NAME, '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__NAME();
  arguments->slots[1] = character__46;
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
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1237: alt
  // 1238:   optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1239:   ','
  // 1240:   sim2c::WHITESPACE, '.'
  // 1241:   NAME, '.'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__10 */;
  arguments->slots[1] = character__44;
  arguments->slots[2] = frame->slots[11] /* temp__12 */;
  arguments->slots[3] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__365_8;
}
static void cont__365_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1236: followed_by
  // 1237:   alt
  // 1238:     optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1239:     ','
  // 1240:     sim2c::WHITESPACE, '.'
  // 1241:     NAME, '.'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__365_9;
}
static void cont__365_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1242: modify_node
  // 1243:   : (node)
  // 1244:     # store the current node in the parent slot for later retrieval
  // 1245:     
  // 1246:     ->
  // 1247:       expression
  // 1248:         .parent_of
  // 1249:           node(.arguments_of range(arguments_of(node) 1 -2))
  // 1250:         .arguments_of list(arguments_of(node)(-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__365_10;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__365_18;
}
static void entry__365_10(void) {
  allocate_initialized_frame_gc(1, 10);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1249: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__365_11;
}
static void cont__365_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 1249: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__365_12;
}
static void cont__365_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 1249: ... range(arguments_of(node) 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__365_13;
}
static void cont__365_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1249: node(.arguments_of range(arguments_of(node) 1 -2))
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 1250: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__365_14;
}
static void cont__365_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__8 */ = arguments->slots[0];
  // 1250: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__365_15;
}
static void cont__365_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__9 */ = arguments->slots[0];
  // 1250: ... arguments_of(node)(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__8 */;
  result_count = 1;
  myself = frame->slots[9] /* temp__9 */;
  func = myself->type;
  frame->cont = cont__365_16;
}
static void cont__365_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__7 */ = arguments->slots[0];
  // 1250: ... list(arguments_of(node)(-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__7 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__365_17;
}
static void cont__365_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 1247: expression
  // 1248:   .parent_of
  // 1249:     node(.arguments_of range(arguments_of(node) 1 -2))
  // 1250:   .arguments_of list(arguments_of(node)(-1))
  {
    NODE *temp = clone_object_and_attributes(get__expression());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parent_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__6 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1246: ->
  // 1247:   expression
  // 1248:     .parent_of
  // 1249:       node(.arguments_of range(arguments_of(node) 1 -2))
  // 1250:     .arguments_of list(arguments_of(node)(-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__365_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 1235: sequence
  // 1236:   followed_by
  // 1237:     alt
  // 1238:       optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1239:       ','
  // 1240:       sim2c::WHITESPACE, '.'
  // 1241:       NAME, '.'
  // 1242:   modify_node
  // 1243:     : (node)
  // 1244:       # store the current node in the parent slot for later retrieval
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = frame->slots[13] /* temp__14 */;
  arguments->slots[2] = var._OPERATORS_AND_OPERANDS;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__365_19;
}
static void cont__365_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1254: ... NEXT_LINE, LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE;
  arguments->slots[1] = var._LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__365_20;
}
static void cont__365_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  // 1254: optional(NEXT_LINE, LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__17 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__365_21;
}
static void cont__365_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 1252: sequence
  // 1253:   MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK
  // 1254:   optional(NEXT_LINE, LINE_START_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK;
  arguments->slots[1] = frame->slots[15] /* temp__16 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__365_22;
}
static void cont__365_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 1234: alt
  // 1235:   sequence
  // 1236:     followed_by
  // 1237:       alt
  // 1238:         optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1239:         ','
  // 1240:         sim2c::WHITESPACE, '.'
  // 1241:         NAME, '.'
  // 1242:     modify_node
  // 1243:       : (node)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  arguments->slots[1] = frame->slots[14] /* temp__15 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__365_23;
}
static void cont__365_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1233: optional
  // 1234:   alt
  // 1235:     sequence
  // 1236:       followed_by
  // 1237:         alt
  // 1238:           optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1239:           ','
  // 1240:           sim2c::WHITESPACE, '.'
  // 1241:           NAME, '.'
  // 1242:       modify_node
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__365_24;
}
static void cont__365_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1230: sequence
  // 1231:   arguments_span
  // 1232:     IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  // 1233:   optional
  // 1234:     alt
  // 1235:       sequence
  // 1236:         followed_by
  // 1237:           alt
  // 1238:             optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1239:             ','
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__365_25;
}
static void cont__365_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1255: ... not_followed_by(ARGUMENT_EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_EXPANSION;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__365_26;
}
static void cont__365_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__20 */ = arguments->slots[0];
  // 1255: ... EXPRESSION, not_followed_by(ARGUMENT_EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = frame->slots[19] /* temp__20 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__365_27;
}
static void cont__365_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__19 */ = arguments->slots[0];
  // 1255: arguments_span(EXPRESSION, not_followed_by(ARGUMENT_EXPANSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__19 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__365_28;
}
static void cont__365_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 1256: arguments_span(MULTI_LINE_EXPRESSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._MULTI_LINE_EXPRESSION;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__365_29;
}
static void cont__365_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__21 */ = arguments->slots[0];
  // 1228: $LINE_START_ARGUMENT
  // 1229:   alt
  // 1230:     sequence
  // 1231:       arguments_span
  // 1232:         IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  // 1233:       optional
  // 1234:         alt
  // 1235:           sequence
  // 1236:             followed_by
  // 1237:               alt
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[17] /* temp__18 */;
  arguments->slots[2] = frame->slots[20] /* temp__21 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__365_30;
}
static void cont__365_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINE_START_ARGUMENT, arguments->slots[0]);
  // 1260: ... NEXT_LINE, MORE_LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE;
  arguments->slots[1] = var._MORE_LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__366_1;
}
static void cont__366_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1260: ... optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__366_2;
}
static void cont__366_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1260: LINE_END_EXPRESSION, optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_EXPRESSION;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__366_3;
}
static void cont__366_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1262: alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_START_ARGUMENT;
  arguments->slots[1] = var._SIMPLE_ARGUMENT;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__366_4;
}
static void cont__366_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1263: ... SEPARATOR, ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SEPARATOR;
  arguments->slots[1] = var._ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__366_5;
}
static void cont__366_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1263: ... NEWLINES, MORE_LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._MORE_LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__366_6;
}
static void cont__366_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1263: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__366_7;
}
static void cont__366_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1263: alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__366_8;
}
static void cont__366_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1261: sequence
  // 1262:   alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
  // 1263:   alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__366_9;
}
static void cont__366_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1258: $LINE_START_ARGUMENTS
  // 1259:   alt
  // 1260:     LINE_END_EXPRESSION, optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
  // 1261:     sequence
  // 1262:       alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
  // 1263:       alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__366_10;
}
static void cont__366_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINE_START_ARGUMENTS, arguments->slots[0]);
  // 1267: ... NEWLINES, MORE_LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._MORE_LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__367_1;
}
static void cont__367_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1267: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__367_2;
}
static void cont__367_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1267: REMARK_BEHIND, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_BEHIND;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__367_3;
}
static void cont__367_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1265: $MORE_LINE_START_ARGUMENTS
  // 1266:   alt
  // 1267:     REMARK_BEHIND, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  // 1268:     LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__367_4;
}
static void cont__367_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MORE_LINE_START_ARGUMENTS, arguments->slots[0]);
  // 1272: ... NEWLINES, MORE_LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._MORE_LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__368_1;
}
static void cont__368_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1272: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__368_2;
}
static void cont__368_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1272: REMARK, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__368_3;
}
static void cont__368_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1270: $FIRST_LINE_START_ARGUMENTS
  // 1271:   alt
  // 1272:     REMARK, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  // 1273:     LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._LINE_START_ARGUMENTS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__368_4;
}
static void cont__368_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FIRST_LINE_START_ARGUMENTS, arguments->slots[0]);
  // 1277: sim2c::WHITESPACE, INPUT_ARGUMENT, LINE_END_REMARK
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._INPUT_ARGUMENT;
  arguments->slots[2] = var._LINE_END_REMARK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__369_1;
}
static void cont__369_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1278: SEPARATOR, LINE_END_EXPRESSION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SEPARATOR;
  arguments->slots[1] = var._LINE_END_EXPRESSION;
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
  // 1282: ... REMARK, NEWLINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__369_3;
}
static void cont__369_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1282: some(REMARK, NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__369_4;
}
static void cont__369_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1283: alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SINGLE_EXPRESSION_LINE;
  arguments->slots[1] = var._INPUT_ARGUMENT;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__369_5;
}
static void cont__369_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1284: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__369_6;
}
static void cont__369_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1279: sequence
  // 1280:   LINE_END_REMARK
  // 1281:   INDENT
  // 1282:   some(REMARK, NEWLINES)
  // 1283:   alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
  // 1284:   expect(outdent_marker)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK;
  arguments->slots[1] = var._INDENT;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  arguments->slots[3] = frame->slots[5] /* temp__6 */;
  arguments->slots[4] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__369_7;
}
static void cont__369_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1275: $SINGLE_INPUT_ARGUMENT
  // 1276:   alt
  // 1277:     sim2c::WHITESPACE, INPUT_ARGUMENT, LINE_END_REMARK
  // 1278:     SEPARATOR, LINE_END_EXPRESSION
  // 1279:     sequence
  // 1280:       LINE_END_REMARK
  // 1281:       INDENT
  // 1282:       some(REMARK, NEWLINES)
  // 1283:       alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
  // 1284:       expect(outdent_marker)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__369_8;
}
static void cont__369_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SINGLE_INPUT_ARGUMENT, arguments->slots[0]);
  // 1291: set_node(define_static_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__370_1;
}
static void cont__370_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1292: set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__IN_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__370_2;
}
static void cont__370_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1289: sequence
  // 1290:   '$'
  // 1291:   set_node(define_static_multi)
  // 1292:   set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__36;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  arguments->slots[2] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__370_3;
}
static void cont__370_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1295: set_node(define_static_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__370_4;
}
static void cont__370_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1296: set_field(parameter_kind_of OUT_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__OUT_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__370_5;
}
static void cont__370_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1293: sequence
  // 1294:   '!'
  // 1295:   set_node(define_static_multi)
  // 1296:   set_field(parameter_kind_of OUT_PARAMETER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__33;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__370_6;
}
static void cont__370_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1299: set_node(define_static_multi)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_multi();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__370_7;
}
static void cont__370_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1300: set_field(parameter_kind_of IN_OUT_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__IN_OUT_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__370_8;
}
static void cont__370_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1297: sequence
  // 1298:   '&'
  // 1299:   set_node(define_static_multi)
  // 1300:   set_field(parameter_kind_of IN_OUT_PARAMETER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__38;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__370_9;
}
static void cont__370_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1301: set_node(define_static_single)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_single();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__370_10;
}
static void cont__370_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1301: ... set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__IN_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__370_11;
}
static void cont__370_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1301: set_node(define_static_single), set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__12 */;
  arguments->slots[1] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__370_12;
}
static void cont__370_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1288: alt
  // 1289:   sequence
  // 1290:     '$'
  // 1291:     set_node(define_static_multi)
  // 1292:     set_field(parameter_kind_of IN_PARAMETER)
  // 1293:   sequence
  // 1294:     '!'
  // 1295:     set_node(define_static_multi)
  // 1296:     set_field(parameter_kind_of OUT_PARAMETER)
  // 1297:   sequence
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[7] /* temp__8 */;
  arguments->slots[3] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__370_13;
}
static void cont__370_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1286: $PARAMETER_MODE
  // 1287:   optional
  // 1288:     alt
  // 1289:       sequence
  // 1290:         '$'
  // 1291:         set_node(define_static_multi)
  // 1292:         set_field(parameter_kind_of IN_PARAMETER)
  // 1293:       sequence
  // 1294:         '!'
  // 1295:         set_node(define_static_multi)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__370_14;
}
static void cont__370_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_MODE, arguments->slots[0]);
  // 1308: infix_operator('=')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__61;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__371_1;
}
static void cont__371_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1309: set_field(is_an_optional_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__is_an_optional_item();
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__371_2;
}
static void cont__371_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1310: span(default_value_of EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__default_value_of();
  arguments->slots[1] = var._EXPRESSION;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__371_3;
}
static void cont__371_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1307: sequence
  // 1308:   infix_operator('=')
  // 1309:   set_field(is_an_optional_item true)
  // 1310:   span(default_value_of EXPRESSION)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  arguments->slots[2] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__371_4;
}
static void cont__371_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1311: ... set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__MYSELF_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__371_5;
}
static void cont__371_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1311: '^', set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__94;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__371_6;
}
static void cont__371_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1305: alt
  // 1306:   EXPANSION
  // 1307:   sequence
  // 1308:     infix_operator('=')
  // 1309:     set_field(is_an_optional_item true)
  // 1310:     span(default_value_of EXPRESSION)
  // 1311:   '^', set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__371_7;
}
static void cont__371_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1303: $PARAMETER_COUNT_OR_MYSELF
  // 1304:   optional
  // 1305:     alt
  // 1306:       EXPANSION
  // 1307:       sequence
  // 1308:         infix_operator('=')
  // 1309:         set_field(is_an_optional_item true)
  // 1310:         span(default_value_of EXPRESSION)
  // 1311:       '^', set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__371_8;
}
static void cont__371_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_COUNT_OR_MYSELF, arguments->slots[0]);
  // 1316: modify_node
  // 1317:   : (&node)
  // 1318:     !node.is_not_used true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__372_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__372_2;
}
static void entry__372_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1318: !node.is_not_used true
  frame->slots[1] /* temp__1 */ = get__true();
  // 1318: !node.is_not_used
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_not_used, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__372_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1313: $NOT_USED
  // 1314:   sequence
  // 1315:     '_'
  // 1316:     modify_node
  // 1317:       : (&node)
  // 1318:         !node.is_not_used true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__95;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__372_3;
}
static void cont__372_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NOT_USED, arguments->slots[0]);
  // 1324: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__373_1;
}
static void cont__373_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1326: optional(NOT_USED)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NOT_USED;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__373_2;
}
static void cont__373_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1327: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__373_3;
}
static void cont__373_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1323: sequence
  // 1324:   set_node(identifier)
  // 1325:   STORE_POSITION
  // 1326:   optional(NOT_USED)
  // 1327:   capture(name_of NAME)
  // 1328:   STORE_END_POSITION
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
  frame->cont = cont__373_4;
}
static void cont__373_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1320: $PARAMETER_NAME
  // 1321:   span
  // 1322:     identifier_of
  // 1323:     sequence
  // 1324:       set_node(identifier)
  // 1325:       STORE_POSITION
  // 1326:       optional(NOT_USED)
  // 1327:       capture(name_of NAME)
  // 1328:       STORE_END_POSITION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__373_5;
}
static void cont__373_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_NAME, arguments->slots[0]);
  // 1330: $PARAMETER PARAMETER_MODE, PARAMETER_NAME, PARAMETER_COUNT_OR_MYSELF
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_MODE;
  arguments->slots[1] = var._PARAMETER_NAME;
  arguments->slots[2] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__374_1;
}
static void cont__374_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER, arguments->slots[0]);
  // 1333: ... INDENT, REMARK, OUTDENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = var._REMARK;
  arguments->slots[2] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__375_1;
}
static void cont__375_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1333: ... optional(INDENT, REMARK, OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__375_2;
}
static void cont__375_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1332: $MULTI_LINE_PARAMETER
  // 1333:   PARAMETER, ARGUMENT_LINE_END_REMARK, optional(INDENT, REMARK, OUTDENT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER;
  arguments->slots[1] = var._ARGUMENT_LINE_END_REMARK;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__375_3;
}
static void cont__375_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_PARAMETER, arguments->slots[0]);
  // 1339: set_node(define_static_single)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__define_static_single();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__376_1;
}
static void cont__376_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1340: set_field(parameter_kind_of CONTINUATION_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameter_kind_of();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__set_field();
  func = myself->type;
  frame->cont = cont__376_2;
}
static void cont__376_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1335: $CONTINUATION
  // 1336:   sequence
  // 1337:     "->"
  // 1338:     sim2c::WHITESPACE
  // 1339:     set_node(define_static_single)
  // 1340:     set_field(parameter_kind_of CONTINUATION_PARAMETER)
  // 1341:     PARAMETER_NAME
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602bfb;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = var._PARAMETER_NAME;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__376_4;
}
static void cont__376_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._CONTINUATION, arguments->slots[0]);
  // 1344: ... INDENT, REMARK, OUTDENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = var._REMARK;
  arguments->slots[2] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__377_1;
}
static void cont__377_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1344: ... optional(INDENT, REMARK, OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__377_2;
}
static void cont__377_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1343: $MULTI_LINE_CONTINUATION
  // 1344:   CONTINUATION, ARGUMENT_LINE_END_REMARK, optional(INDENT, REMARK, OUTDENT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._CONTINUATION;
  arguments->slots[1] = var._ARGUMENT_LINE_END_REMARK;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__377_3;
}
static void cont__377_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_CONTINUATION, arguments->slots[0]);
  // 1352: ... multi_span(parameters_of PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._PARAMETER;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__378_1;
}
static void cont__378_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1352: interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__378_2;
}
static void cont__378_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1353: ... multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._CONTINUATION;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__378_3;
}
static void cont__378_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1353: ... sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__378_4;
}
static void cont__378_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1353: optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__378_5;
}
static void cont__378_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1351: sequence
  // 1352:   interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1353:   optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__378_6;
}
static void cont__378_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1354: multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._CONTINUATION;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__378_7;
}
static void cont__378_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1350: alt
  // 1351:   sequence
  // 1352:     interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1353:     optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1354:   multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__378_8;
}
static void cont__378_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1349: optional
  // 1350:   alt
  // 1351:     sequence
  // 1352:       interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1353:       optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1354:     multi_span(parameters_of CONTINUATION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__378_9;
}
static void cont__378_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1355: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__378_10;
}
static void cont__378_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1346: $INLINE_PARAMETERS
  // 1347:   sequence
  // 1348:     '('
  // 1349:     optional
  // 1350:       alt
  // 1351:         sequence
  // 1352:           interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1353:           optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1354:         multi_span(parameters_of CONTINUATION)
  // 1355:     expect(')')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__378_11;
}
static void cont__378_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INLINE_PARAMETERS, arguments->slots[0]);
  // 1363: ... multi_span(parameters_of MULTI_LINE_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._MULTI_LINE_PARAMETER;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__379_1;
}
static void cont__379_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1363: interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._NEWLINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__379_2;
}
static void cont__379_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1364: ... multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._MULTI_LINE_CONTINUATION;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__379_3;
}
static void cont__379_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1364: ... NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__379_4;
}
static void cont__379_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1364: optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__379_5;
}
static void cont__379_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1362: sequence
  // 1363:   interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1364:   optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__379_6;
}
static void cont__379_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1365: multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__parameters_of();
  arguments->slots[1] = var._MULTI_LINE_CONTINUATION;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__379_7;
}
static void cont__379_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1361: alt
  // 1362:   sequence
  // 1363:     interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1364:     optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  // 1365:   multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__379_8;
}
static void cont__379_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1366: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__379_9;
}
static void cont__379_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1367: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__379_10;
}
static void cont__379_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1368: expect(')')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__41;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__379_11;
}
static void cont__379_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1357: $MULTI_LINE_PARAMETERS
  // 1358:   sequence
  // 1359:     '('
  // 1360:     INDENT
  // 1361:     alt
  // 1362:       sequence
  // 1363:         interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1364:         optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  // 1365:       multi_span(parameters_of MULTI_LINE_CONTINUATION)
  // 1366:     expect(outdent_marker)
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
  frame->cont = cont__379_12;
}
static void cont__379_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MULTI_LINE_PARAMETERS, arguments->slots[0]);
  // 1373: set_node(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__body();
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
  // 1375: optional(NEW_LINE_END_REMARK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NEW_LINE_END_REMARK;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__380_2;
}
static void cont__380_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1380: ... REMARK, NEWLINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK;
  arguments->slots[1] = var._NEWLINES;
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
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1380: some(REMARK, NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__380_4;
}
static void cont__380_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1384: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__380_5;
}
static void cont__380_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1378: sequence
  // 1379:   INDENT
  // 1380:   some(REMARK, NEWLINES)
  // 1381:   MULTI_LINE_PARAMETERS
  // 1382:   NEWLINES
  // 1383:   STATEMENTS
  // 1384:   expect(outdent_marker)
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[5] /* temp__6 */;
  arguments->slots[2] = var._MULTI_LINE_PARAMETERS;
  arguments->slots[3] = var._NEWLINES;
  arguments->slots[4] = var._STATEMENTS;
  arguments->slots[5] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_6;
}
static void cont__380_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1386: ... sim2c::WHITESPACE, INLINE_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._INLINE_PARAMETERS;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__380_7;
}
static void cont__380_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1386: optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__380_8;
}
static void cont__380_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1389: ... optional(NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__380_9;
}
static void cont__380_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 1389: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
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
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 1389: INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[13] /* temp__14 */;
  arguments->slots[2] = var._STATEMENTS;
  arguments->slots[3] = frame->slots[14] /* temp__15 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__380_11;
}
static void cont__380_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1392: ... syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5ed2969d8211684f;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__380_13;
}
static void cont__380_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 1392: alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._STATEMENT;
  arguments->slots[1] = var._RETURN_STATEMENT;
  arguments->slots[2] = frame->slots[17] /* temp__18 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__380_14;
}
static void cont__380_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  // 1390: sequence
  // 1391:   sim2c::WHITESPACE
  // 1392:   alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[16] /* temp__17 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_15;
}
static void cont__380_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 1393: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5ed2969d8211684f;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__380_16;
}
static void cont__380_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__19 */ = arguments->slots[0];
  // 1388: alt
  // 1389:   INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
  // 1390:   sequence
  // 1391:     sim2c::WHITESPACE
  // 1392:     alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  // 1393:   syntax_error("statement expected")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__13 */;
  arguments->slots[1] = frame->slots[15] /* temp__16 */;
  arguments->slots[2] = frame->slots[18] /* temp__19 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__380_17;
}
static void cont__380_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1385: sequence
  // 1386:   optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
  // 1387:   LINE_END_REMARK
  // 1388:   alt
  // 1389:     INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
  // 1390:     sequence
  // 1391:       sim2c::WHITESPACE
  // 1392:       alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  // 1393:     syntax_error("statement expected")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__10 */;
  arguments->slots[1] = var._LINE_END_REMARK;
  arguments->slots[2] = frame->slots[11] /* temp__12 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_18;
}
static void cont__380_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1394: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5ed2969d8211684f;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__380_19;
}
static void cont__380_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__20 */ = arguments->slots[0];
  // 1377: alt
  // 1378:   sequence
  // 1379:     INDENT
  // 1380:     some(REMARK, NEWLINES)
  // 1381:     MULTI_LINE_PARAMETERS
  // 1382:     NEWLINES
  // 1383:     STATEMENTS
  // 1384:     expect(outdent_marker)
  // 1385:   sequence
  // 1386:     optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  arguments->slots[2] = frame->slots[19] /* temp__20 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__380_20;
}
static void cont__380_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1376: sequence
  // 1377:   alt
  // 1378:     sequence
  // 1379:       INDENT
  // 1380:       some(REMARK, NEWLINES)
  // 1381:       MULTI_LINE_PARAMETERS
  // 1382:       NEWLINES
  // 1383:       STATEMENTS
  // 1384:       expect(outdent_marker)
  // 1385:     sequence
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_21;
}
static void cont__380_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1370: $COMPLETE_BODY
  // 1371:   sequence
  // 1372:     ':'
  // 1373:     set_node(body)
  // 1374:     STORE_POSITION_MINUS_1
  // 1375:     optional(NEW_LINE_END_REMARK)
  // 1376:     sequence
  // 1377:       alt
  // 1378:         sequence
  // 1379:           INDENT
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = character__58;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = frame->slots[2] /* temp__3 */;
  arguments->slots[5] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_22;
}
static void cont__380_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._COMPLETE_BODY, arguments->slots[0]);
  // 1399: followed_by("->")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602bfb;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__381_1;
}
static void cont__381_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1400: set_node(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__body();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__381_2;
}
static void cont__381_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1397: $RETURN_EXPRESSION
  // 1398:   sequence
  // 1399:     followed_by("->")
  // 1400:     set_node(body)
  // 1401:     STORE_POSITION
  // 1402:     RETURN_STATEMENT
  // 1403:     STORE_END_POSITION
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = var._STORE_POSITION;
  arguments->slots[3] = var._RETURN_STATEMENT;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__381_3;
}
static void cont__381_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RETURN_EXPRESSION, arguments->slots[0]);
  // 1405: $BODY alt(COMPLETE_BODY RETURN_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._COMPLETE_BODY;
  arguments->slots[1] = var._RETURN_EXPRESSION;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__382_1;
}
static void cont__382_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BODY, arguments->slots[0]);
  // 1410: set_node(c_body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__c_body();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__383_1;
}
static void cont__383_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1412: expect(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__383_2;
}
static void cont__383_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1413: ... not_followed_by(OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OUTDENT;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__383_3;
}
static void cont__383_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1413: ... not_followed_by(OUTDENT), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__383_4;
}
static void cont__383_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1413: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__383_5;
}
static void cont__383_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1413: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__source_of();
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__383_6;
}
static void cont__383_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1414: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__383_7;
}
static void cont__383_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1415: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__383_8;
}
static void cont__383_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1416: expect('}')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__125;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__383_9;
}
static void cont__383_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1407: $C_BODY
  // 1408:   sequence
  // 1409:     '{'
  // 1410:     set_node(c_body)
  // 1411:     STORE_POSITION_MINUS_1
  // 1412:     expect(indent_marker)
  // 1413:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  // 1414:     expect(outdent_marker)
  // 1415:     expect(newline)
  // 1416:     expect('}')
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
  frame->cont = cont__383_10;
}
static void cont__383_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_BODY, arguments->slots[0]);
  // 1419: ... alt(BODY C_BODY MULTI_LINE_STRING)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._BODY;
  arguments->slots[1] = var._C_BODY;
  arguments->slots[2] = var._MULTI_LINE_STRING;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__384_1;
}
static void cont__384_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1419: $LINE_END_EXPRESSION arguments_span(alt(BODY C_BODY MULTI_LINE_STRING))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__384_2;
}
static void cont__384_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINE_END_EXPRESSION, arguments->slots[0]);
  // 1422: set_node(assignment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__assignment();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__385_1;
}
static void cont__385_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1425: output_arguments_span(DEFINE_STATIC_MULTI)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_STATIC_MULTI;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__385_2;
}
static void cont__385_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1425: output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__385_3;
}
static void cont__385_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1427: output_arguments_span(DEFINE_STATIC_SINGLE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_STATIC_SINGLE;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__385_4;
}
static void cont__385_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1426: sequence
  // 1427:   output_arguments_span(DEFINE_STATIC_SINGLE) SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__385_5;
}
static void cont__385_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1428: output_arguments_span(DEFINE_DYNAMIC_MULTI)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_DYNAMIC_MULTI;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__385_6;
}
static void cont__385_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1428: output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__385_7;
}
static void cont__385_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1429: output_arguments_span(DEFINE_DYNAMIC_SINGLE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_DYNAMIC_SINGLE;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__385_8;
}
static void cont__385_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1429: output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__10 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__385_9;
}
static void cont__385_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1431: output_arguments_span(ASSIGN)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._ASSIGN;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__385_10;
}
static void cont__385_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1432: alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SINGLE_INPUT_ARGUMENT;
  arguments->slots[1] = var._INDENTED_ATTRIBUTE_VALUE_PAIRS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__385_11;
}
static void cont__385_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1430: sequence
  // 1431:   output_arguments_span(ASSIGN)
  // 1432:   alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__12 */;
  arguments->slots[1] = frame->slots[12] /* temp__13 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__385_12;
}
static void cont__385_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1424: alt
  // 1425:   output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1426:   sequence
  // 1427:     output_arguments_span(DEFINE_STATIC_SINGLE) SINGLE_INPUT_ARGUMENT
  // 1428:   output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1429:   output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
  // 1430:   sequence
  // 1431:     output_arguments_span(ASSIGN)
  // 1432:     alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  arguments->slots[3] = frame->slots[8] /* temp__9 */;
  arguments->slots[4] = frame->slots[10] /* temp__11 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__385_13;
}
static void cont__385_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1420: $ASSIGNMENT
  // 1421:   sequence
  // 1422:     set_node(assignment)
  // 1423:     STORE_POSITION
  // 1424:     alt
  // 1425:       output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1426:       sequence
  // 1427:         output_arguments_span(DEFINE_STATIC_SINGLE) SINGLE_INPUT_ARGUMENT
  // 1428:       output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1429:       output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__385_14;
}
static void cont__385_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ASSIGNMENT, arguments->slots[0]);
  // 1436: ... set_node(polymorphic_function)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__polymorphic_function();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__386_1;
}
static void cont__386_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1435: $POLYMORPHIC_FUNCTION_WITHOUT_SETTER
  // 1436:   "()", set_node(polymorphic_function)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6482bec;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__386_3;
}
static void cont__386_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER, arguments->slots[0]);
  // 1439: ... set_node(polymorphic_function_with_setter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__polymorphic_function_with_setter();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__387_1;
}
static void cont__387_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1438: $POLYMORPHIC_FUNCTION_WITH_SETTER
  // 1439:   "(!)", set_node(polymorphic_function_with_setter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa732415f216be5;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__387_3;
}
static void cont__387_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._POLYMORPHIC_FUNCTION_WITH_SETTER, arguments->slots[0]);
  // 1445: alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER;
  arguments->slots[1] = var._POLYMORPHIC_FUNCTION_WITH_SETTER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__388_1;
}
static void cont__388_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1444: arguments_span
  // 1445:   alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__388_2;
}
static void cont__388_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1441: $POLYMORPHIC_FUNCTION
  // 1442:   sequence
  // 1443:     sim2c::WHITESPACE
  // 1444:     arguments_span
  // 1445:       alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
  // 1446:     LINE_END_REMARK
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._LINE_END_REMARK;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__388_3;
}
static void cont__388_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._POLYMORPHIC_FUNCTION, arguments->slots[0]);
  // 1450: set_node(assignment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__assignment();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__389_1;
}
static void cont__389_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1453: output_arguments_span(DEFINE_STATIC_MULTI)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_STATIC_MULTI;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__389_2;
}
static void cont__389_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1453: output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__389_3;
}
static void cont__389_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1455: output_arguments_span(DEFINE_STATIC_SINGLE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_STATIC_SINGLE;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__389_4;
}
static void cont__389_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1459: modify_node
  // 1460:   : (&node)
  // 1461:     $$destination output_arguments_of(node)(1)
  // 1462:     if attribute_of(destination).is_defined:
  // 1463:       SyntaxError node "invalid polymorphic function definition"
  // 1464:     !destination.variable_kind_of POLYMORPHIC
  // 1465:     !node.output_arguments_of(1) destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__389_5;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__389_15;
}
static void entry__389_5(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // node: 0
  // destination: 1
  frame->slots[1] /* destination */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 1461: ... output_arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__389_6;
}
static void cont__389_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1461: $$destination output_arguments_of(node)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__389_7;
}
static void cont__389_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* destination */ = arguments->slots[0];
  // 1462: ... attribute_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* destination */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__389_8;
}
static void cont__389_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1462: ... attribute_of(destination).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__389_9;
}
static void cont__389_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1462: ... :
  // 1463:   SyntaxError node "invalid polymorphic function definition"
  frame->slots[4] /* temp__3 */ = create_closure(entry__389_10, 0);
  // 1462: if attribute_of(destination).is_defined:
  // 1463:   SyntaxError node "invalid polymorphic function definition"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__389_12;
}
static void entry__389_10(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1463: SyntaxError node "invalid polymorphic function definition"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  arguments->slots[1] = string__b6a1aa36d1f3b32e;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__389_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1464: !destination.variable_kind_of POLYMORPHIC
  frame->slots[2] /* temp__1 */ = get__POLYMORPHIC();
  // 1464: !destination.variable_kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* destination */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* destination */ = temp;

  }
  // 1465: !node.output_arguments_of(1) destination
  frame->slots[2] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* destination */;
  // 1465: ... node.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__389_13;
}
static void cont__389_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1465: !node.output_arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__389_14;
}
static void cont__389_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1465: !node.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__389_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1457: sequence
  // 1458:   POLYMORPHIC_FUNCTION
  // 1459:   modify_node
  // 1460:     : (&node)
  // 1461:       $$destination output_arguments_of(node)(1)
  // 1462:       if attribute_of(destination).is_defined:
  // 1463:         SyntaxError node "invalid polymorphic function definition"
  // 1464:       !destination.variable_kind_of POLYMORPHIC
  // 1465:       !node.output_arguments_of(1) destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[1] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__389_16;
}
static void cont__389_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1456: alt
  // 1457:   sequence
  // 1458:     POLYMORPHIC_FUNCTION
  // 1459:     modify_node
  // 1460:       : (&node)
  // 1461:         $$destination output_arguments_of(node)(1)
  // 1462:         if attribute_of(destination).is_defined:
  // 1463:           SyntaxError node "invalid polymorphic function definition"
  // 1464:         !destination.variable_kind_of POLYMORPHIC
  // 1465:         !node.output_arguments_of(1) destination
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__389_17;
}
static void cont__389_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1454: sequence
  // 1455:   output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1456:   alt
  // 1457:     sequence
  // 1458:       POLYMORPHIC_FUNCTION
  // 1459:       modify_node
  // 1460:         : (&node)
  // 1461:           $$destination output_arguments_of(node)(1)
  // 1462:           if attribute_of(destination).is_defined:
  // 1463:             SyntaxError node "invalid polymorphic function definition"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__389_18;
}
static void cont__389_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1467: output_arguments_span(DEFINE_DYNAMIC_MULTI)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_DYNAMIC_MULTI;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__389_19;
}
static void cont__389_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 1467: output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__11 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__389_20;
}
static void cont__389_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 1468: output_arguments_span(DEFINE_DYNAMIC_SINGLE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_DYNAMIC_SINGLE;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__389_21;
}
static void cont__389_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 1468: output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__13 */;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__389_22;
}
static void cont__389_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 1470: output_arguments_span(ASSIGN)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._ASSIGN;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__389_23;
}
static void cont__389_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 1471: alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SINGLE_INPUT_ARGUMENT;
  arguments->slots[1] = var._INDENTED_ATTRIBUTE_VALUE_PAIRS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__389_24;
}
static void cont__389_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 1469: sequence
  // 1470:   output_arguments_span(ASSIGN)
  // 1471:   alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__15 */;
  arguments->slots[1] = frame->slots[15] /* temp__16 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__389_25;
}
static void cont__389_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 1452: alt
  // 1453:   output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1454:   sequence
  // 1455:     output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1456:     alt
  // 1457:       sequence
  // 1458:         POLYMORPHIC_FUNCTION
  // 1459:         modify_node
  // 1460:           : (&node)
  // 1461:             $$destination output_arguments_of(node)(1)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  arguments->slots[2] = frame->slots[9] /* temp__10 */;
  arguments->slots[3] = frame->slots[11] /* temp__12 */;
  arguments->slots[4] = frame->slots[13] /* temp__14 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__389_26;
}
static void cont__389_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1448: $TOP_LEVEL_ASSIGNMENT
  // 1449:   sequence
  // 1450:     set_node(assignment)
  // 1451:     STORE_POSITION
  // 1452:     alt
  // 1453:       output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1454:       sequence
  // 1455:         output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1456:         alt
  // 1457:           sequence
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__389_27;
}
static void cont__389_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TOP_LEVEL_ASSIGNMENT, arguments->slots[0]);
  // 1474: $FUNCTOR span(functor_of IDENTIFIER_OR_FUNCTION_CALL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._IDENTIFIER_OR_FUNCTION_CALL;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__390_1;
}
static void cont__390_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FUNCTOR, arguments->slots[0]);
  // 1478: ... span(result_count_of EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__result_count_of();
  arguments->slots[1] = var._EXPRESSION;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__391_1;
}
static void cont__391_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1478: ".(", span(result_count_of EXPRESSION), ')'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6782bed;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = character__41;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__391_3;
}
static void cont__391_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1479: ... span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__continuation_of();
  arguments->slots[1] = var._IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__391_4;
}
static void cont__391_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1479: '/', span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__391_5;
}
static void cont__391_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1476: $RESULT_COUNT_OR_CONTINUATION
  // 1477:   alt
  // 1478:     ".(", span(result_count_of EXPRESSION), ')'
  // 1479:     '/', span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__391_6;
}
static void cont__391_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RESULT_COUNT_OR_CONTINUATION, arguments->slots[0]);
  // 1483: set_node(procedure_call)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__procedure_call();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__392_1;
}
static void cont__392_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1486: optional(RESULT_COUNT_OR_CONTINUATION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._RESULT_COUNT_OR_CONTINUATION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__392_2;
}
static void cont__392_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1495: optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._INDENTED_ATTRIBUTE_VALUE_PAIRS;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__392_3;
}
static void cont__392_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1492: sequence
  // 1493:   sim2c::WHITESPACE
  // 1494:   INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1495:   optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._INLINE_ATTRIBUTE_VALUE_PAIRS;
  arguments->slots[2] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__392_4;
}
static void cont__392_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1491: alt
  // 1492:   sequence
  // 1493:     sim2c::WHITESPACE
  // 1494:     INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1495:     optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1496:   INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1497:   PROCEDURE_ARGUMENTS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = var._INDENTED_ATTRIBUTE_VALUE_PAIRS;
  arguments->slots[2] = var._PROCEDURE_ARGUMENTS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__392_5;
}
static void cont__392_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1488: sequence
  // 1489:   sim2c::WHITESPACE
  // 1490:   OUTPUT_ARGUMENT
  // 1491:   alt
  // 1492:     sequence
  // 1493:       sim2c::WHITESPACE
  // 1494:       INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1495:       optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1496:     INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1497:     PROCEDURE_ARGUMENTS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._OUTPUT_ARGUMENT;
  arguments->slots[2] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__392_6;
}
static void cont__392_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1487: alt
  // 1488:   sequence
  // 1489:     sim2c::WHITESPACE
  // 1490:     OUTPUT_ARGUMENT
  // 1491:     alt
  // 1492:       sequence
  // 1493:         sim2c::WHITESPACE
  // 1494:         INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1495:         optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1496:       INDENTED_ATTRIBUTE_VALUE_PAIRS
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._PROCEDURE_ARGUMENTS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__392_7;
}
static void cont__392_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1481: $PROCEDURE_CALL
  // 1482:   sequence
  // 1483:     set_node(procedure_call)
  // 1484:     STORE_POSITION
  // 1485:     FUNCTOR
  // 1486:     optional(RESULT_COUNT_OR_CONTINUATION)
  // 1487:     alt
  // 1488:       sequence
  // 1489:         sim2c::WHITESPACE
  // 1490:         OUTPUT_ARGUMENT
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = var._FUNCTOR;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = frame->slots[2] /* temp__3 */;
  arguments->slots[5] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__392_8;
}
static void cont__392_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PROCEDURE_CALL, arguments->slots[0]);
  // 1501: ... interleaved(REMARK NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__393_1;
}
static void cont__393_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1501: $INDENTED_REMARKS INDENT, interleaved(REMARK NEWLINES), OUTDENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__393_2;
}
static void cont__393_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INDENTED_REMARKS, arguments->slots[0]);
  // 1505: alt(ASSIGNMENT PROCEDURE_CALL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ASSIGNMENT;
  arguments->slots[1] = var._PROCEDURE_CALL;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__394_1;
}
static void cont__394_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1505: ... optional(INDENTED_REMARKS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._INDENTED_REMARKS;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__394_2;
}
static void cont__394_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1505: alt(ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__394_3;
}
static void cont__394_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1503: $SINGLE_STATEMENT
  // 1504:   alt
  // 1505:     alt(ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
  // 1506:     SINGLE_REMARK_STATEMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._SINGLE_REMARK_STATEMENT;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__394_4;
}
static void cont__394_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SINGLE_STATEMENT, arguments->slots[0]);
  // 1510: alt(TOP_LEVEL_ASSIGNMENT PROCEDURE_CALL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._TOP_LEVEL_ASSIGNMENT;
  arguments->slots[1] = var._PROCEDURE_CALL;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__395_1;
}
static void cont__395_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1510: ... optional(INDENTED_REMARKS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._INDENTED_REMARKS;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__395_2;
}
static void cont__395_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1510: alt(TOP_LEVEL_ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__395_3;
}
static void cont__395_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1508: $TOP_LEVEL_STATEMENT
  // 1509:   alt
  // 1510:     alt(TOP_LEVEL_ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
  // 1511:     SINGLE_REMARK_STATEMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._SINGLE_REMARK_STATEMENT;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__395_4;
}
static void cont__395_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TOP_LEVEL_STATEMENT, arguments->slots[0]);
  // 1513: $STATEMENT multi_span(statements_of SINGLE_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = var._SINGLE_STATEMENT;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__396_1;
}
static void cont__396_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STATEMENT, arguments->slots[0]);
  // 1521: set_node(return_statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__return_statement();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__397_1;
}
static void cont__397_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1524: check_node
  // 1525:   : (node)
  // 1526:     if arguments_of(node).is_empty:
  // 1527:       SyntaxError node "return statement needs at least one argument"
  // 1528:     -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__397_2;
  result_count = 1;
  myself = get__check_node();
  func = myself->type;
  frame->cont = cont__397_8;
}
static void entry__397_2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1526: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__397_3;
}
static void cont__397_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1526: ... arguments_of(node).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__397_4;
}
static void cont__397_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1526: ... :
  // 1527:   SyntaxError node "return statement needs at least one argument"
  frame->slots[3] /* temp__3 */ = create_closure(entry__397_5, 0);
  // 1526: if arguments_of(node).is_empty:
  // 1527:   SyntaxError node "return statement needs at least one argument"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__397_7;
}
static void entry__397_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1527: SyntaxError node "return statement needs at least one argument"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = string__a6b4597d46108e45;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__397_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1528: -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__397_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1520: sequence
  // 1521:   set_node(return_statement)
  // 1522:   STORE_POSITION_MINUS_2
  // 1523:   PROCEDURE_ARGUMENTS
  // 1524:   check_node
  // 1525:     : (node)
  // 1526:       if arguments_of(node).is_empty:
  // 1527:         SyntaxError node "return statement needs at least one argument"
  // 1528:       -> true
  // 1529:   STORE_END_POSITION
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = var._STORE_POSITION_MINUS_2;
  arguments->slots[2] = var._PROCEDURE_ARGUMENTS;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__397_9;
}
static void cont__397_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1518: multi_span
  // 1519:   statements_of
  // 1520:   sequence
  // 1521:     set_node(return_statement)
  // 1522:     STORE_POSITION_MINUS_2
  // 1523:     PROCEDURE_ARGUMENTS
  // 1524:     check_node
  // 1525:       : (node)
  // 1526:         if arguments_of(node).is_empty:
  // 1527:           SyntaxError node "return statement needs at least one argument"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__397_10;
}
static void cont__397_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1515: $RETURN_STATEMENT
  // 1516:   sequence
  // 1517:     "->"
  // 1518:     multi_span
  // 1519:       statements_of
  // 1520:       sequence
  // 1521:         set_node(return_statement)
  // 1522:         STORE_POSITION_MINUS_2
  // 1523:         PROCEDURE_ARGUMENTS
  // 1524:         check_node
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602bfb;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__397_11;
}
static void cont__397_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RETURN_STATEMENT, arguments->slots[0]);
  // 1534: interleaved(STATEMENT NEXT_LINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STATEMENT;
  arguments->slots[1] = var._NEXT_LINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__398_1;
}
static void cont__398_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1534: ... NEXT_LINE, RETURN_STATEMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE;
  arguments->slots[1] = var._RETURN_STATEMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__398_2;
}
static void cont__398_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1534: ... optional(NEXT_LINE, RETURN_STATEMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__398_3;
}
static void cont__398_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1534: interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__398_4;
}
static void cont__398_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1536: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5ed2969d8211684f;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__398_5;
}
static void cont__398_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1533: alt
  // 1534:   interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
  // 1535:   RETURN_STATEMENT
  // 1536:   syntax_error("statement expected")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = var._RETURN_STATEMENT;
  arguments->slots[2] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__398_6;
}
static void cont__398_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1537: ... NEXT_LINE, REMARK_STATEMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE;
  arguments->slots[1] = var._REMARK_STATEMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__398_7;
}
static void cont__398_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1537: some(NEXT_LINE, REMARK_STATEMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__398_8;
}
static void cont__398_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1531: $STATEMENTS
  // 1532:   sequence
  // 1533:     alt
  // 1534:       interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
  // 1535:       RETURN_STATEMENT
  // 1536:       syntax_error("statement expected")
  // 1537:     some(NEXT_LINE, REMARK_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__7 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__398_9;
}
static void cont__398_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STATEMENTS, arguments->slots[0]);
  // 1542: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__399_1;
}
static void cont__399_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1542: ... "__", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5f02b9a;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__399_3;
}
static void cont__399_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1542: ... many("__", NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__399_4;
}
static void cont__399_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1542: ... NAME, many("__", NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__NAME();
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__399_5;
}
static void cont__399_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1542: ... capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__399_6;
}
static void cont__399_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1542: set_node(identifier), capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__399_7;
}
static void cont__399_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1539: $BUILTIN_NAME
  // 1540:   span
  // 1541:     identifier_of
  // 1542:     set_node(identifier), capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__399_8;
}
static void cont__399_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BUILTIN_NAME, arguments->slots[0]);
  // 1544: ... not_followed_by('>')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__62;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__400_1;
}
static void cont__400_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1544: ... not_followed_by('>'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__400_2;
}
static void cont__400_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1544: $C_EXPRESSION many(not_followed_by('>'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__400_3;
}
static void cont__400_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_EXPRESSION, arguments->slots[0]);
  // 1549: ... multi_capture(arguments_of C_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__arguments_of();
  arguments->slots[1] = var._C_EXPRESSION;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__401_1;
}
static void cont__401_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1549: ... sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__401_2;
}
static void cont__401_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1549: expect(sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__401_3;
}
static void cont__401_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1546: $ARGUMENT_ANNOTATION
  // 1547:   sequence
  // 1548:     "argument"
  // 1549:     expect(sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74dcac9584a4c074;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__401_5;
}
static void cont__401_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENT_ANNOTATION, arguments->slots[0]);
  // 1552: ... span(base_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__base_of();
  arguments->slots[1] = var._NAMESPACED_IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__402_1;
}
static void cont__402_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1552: ... sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__402_2;
}
static void cont__402_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1552: ... expect(sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__402_3;
}
static void cont__402_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1551: $BASE_ANNOTATION
  // 1552:   "base", expect(sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__60ae90b5df87d5c;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__402_5;
}
static void cont__402_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BASE_ANNOTATION, arguments->slots[0]);
  // 1554: ... capture(kind_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__kind_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__403_1;
}
static void cont__403_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1554: ... sim2c::WHITESPACE, capture(kind_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__403_2;
}
static void cont__403_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1554: ... expect(sim2c::WHITESPACE, capture(kind_of NAME))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__403_3;
}
static void cont__403_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1554: $KIND_ANNOTATION "kind", expect(sim2c::WHITESPACE, capture(kind_of NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__140aeb0b5d107d5d;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__403_5;
}
static void cont__403_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._KIND_ANNOTATION, arguments->slots[0]);
  // 1559: ... alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._BUILTIN_NAME;
  arguments->slots[1] = var._DEFINED_VARIABLE_OR_ATTRIBUTE;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__404_1;
}
static void cont__404_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1559: ... sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__404_2;
}
static void cont__404_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1559: expect(sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__404_3;
}
static void cont__404_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1556: $NAME_ANNOTATION
  // 1557:   sequence
  // 1558:     "name"
  // 1559:     expect(sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1e0ae90b5d087d5c;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__404_5;
}
static void cont__404_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAME_ANNOTATION, arguments->slots[0]);
  // 1561: ... capture(node_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__405_1;
}
static void cont__405_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1561: ... sim2c::WHITESPACE, capture(node_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__405_2;
}
static void cont__405_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1561: ... expect(sim2c::WHITESPACE, capture(node_of NAME))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__405_3;
}
static void cont__405_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1561: $NODE_ANNOTATION "node", expect(sim2c::WHITESPACE, capture(node_of NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1e0aea8b5d407d5c;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__405_5;
}
static void cont__405_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NODE_ANNOTATION, arguments->slots[0]);
  // 1569: ... alt("runtime" "global" "local" "extern")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__9a4c0f9815d2209f;
  arguments->slots[1] = string__461f56c301b292bb;
  arguments->slots[2] = string__545aebc3eac0d03b;
  arguments->slots[3] = string__701f5702012bd2b9;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__406_5;
}
static void cont__406_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1569: capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__scope_of();
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__406_6;
}
static void cont__406_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1567: sequence
  // 1568:   sim2c::WHITESPACE
  // 1569:   capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__406_7;
}
static void cont__406_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1566: expect
  // 1567:   sequence
  // 1568:     sim2c::WHITESPACE
  // 1569:     capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__406_8;
}
static void cont__406_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1563: $SCOPE_ANNOTATION
  // 1564:   sequence
  // 1565:     "scope"
  // 1566:     expect
  // 1567:       sequence
  // 1568:         sim2c::WHITESPACE
  // 1569:         capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4c5ae8c3ea492032;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__406_10;
}
static void cont__406_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SCOPE_ANNOTATION, arguments->slots[0]);
  // 1572: ... span(node::type_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__type_of();
  arguments->slots[1] = var._NAMESPACED_IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__407_1;
}
static void cont__407_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1572: ... sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__407_2;
}
static void cont__407_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1572: ... expect(sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__407_3;
}
static void cont__407_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1571: $TYPE_ANNOTATION
  // 1572:   "type", expect(sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2a0aef0b5de07d5c;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__407_5;
}
static void cont__407_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TYPE_ANNOTATION, arguments->slots[0]);
  // 1583: syntax_error("invalid annotation tag")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__399cfc434d66f26;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__408_2;
}
static void cont__408_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1574: $ANNOTATION_ITEM
  // 1575:   alt
  // 1576:     ARGUMENT_ANNOTATION
  // 1577:     BASE_ANNOTATION
  // 1578:     KIND_ANNOTATION
  // 1579:     NAME_ANNOTATION
  // 1580:     NODE_ANNOTATION
  // 1581:     SCOPE_ANNOTATION
  // 1582:     TYPE_ANNOTATION
  // 1583:     syntax_error("invalid annotation tag")
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
  frame->cont = cont__408_3;
}
static void cont__408_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATION_ITEM, arguments->slots[0]);
  // 1585: ... expect('>')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__62;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__409_1;
}
static void cont__409_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1585: $ANNOTATION '<', ANNOTATION_ITEM, expect('>')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = var._ANNOTATION_ITEM;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__409_2;
}
static void cont__409_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATION, arguments->slots[0]);
  // 1586: $ANNOTATIONS interleaved(ANNOTATION NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ANNOTATION;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__410_1;
}
static void cont__410_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATIONS, arguments->slots[0]);
  // 1587: $C_CODE_REMARK "//", REMARK_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6702bea;
  arguments->slots[1] = var._REMARK_LINE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__411_2;
}
static void cont__411_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_CODE_REMARK, arguments->slots[0]);
  // 1588: ... followed_by(OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OUTDENT;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__412_1;
}
static void cont__412_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1588: ... alt(NEWLINES followed_by(OUTDENT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__412_2;
}
static void cont__412_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1588: ... C_CODE_REMARK, alt(NEWLINES followed_by(OUTDENT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._C_CODE_REMARK;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__412_3;
}
static void cont__412_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1588: $C_CODE_REMARKS some(C_CODE_REMARK, alt(NEWLINES followed_by(OUTDENT)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__412_4;
}
static void cont__412_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_CODE_REMARKS, arguments->slots[0]);
  // 1593: ... not_followed_by(OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OUTDENT;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__413_1;
}
static void cont__413_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1593: ... not_followed_by(OUTDENT), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__413_2;
}
static void cont__413_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1593: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__413_3;
}
static void cont__413_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1593: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__source_of();
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__413_4;
}
static void cont__413_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1590: $SOURCE
  // 1591:   sequence
  // 1592:     C_CODE_REMARKS
  // 1593:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._C_CODE_REMARKS;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__413_5;
}
static void cont__413_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SOURCE, arguments->slots[0]);
  // 1598: set_node(c_code)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__c_code();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__414_1;
}
static void cont__414_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1599: expect(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__414_2;
}
static void cont__414_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1600: ... NEWLINES, SOURCE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._SOURCE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__414_3;
}
static void cont__414_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 1600: ... optional(NEWLINES, SOURCE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__414_4;
}
static void cont__414_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 1600: ... ANNOTATIONS, optional(NEWLINES, SOURCE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ANNOTATIONS;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__414_5;
}
static void cont__414_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1600: alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = var._SOURCE;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__414_6;
}
static void cont__414_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1601: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__414_7;
}
static void cont__414_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 1602: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__414_8;
}
static void cont__414_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 1603: expect('}')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__125;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__414_9;
}
static void cont__414_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 1595: $C_CODE
  // 1596:   sequence
  // 1597:     '{'
  // 1598:     set_node(c_code)
  // 1599:     expect(indent_marker)
  // 1600:     alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
  // 1601:     expect(outdent_marker)
  // 1602:     expect(newline)
  // 1603:     expect('}')
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = character__123;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  arguments->slots[3] = frame->slots[2] /* temp__3 */;
  arguments->slots[4] = frame->slots[6] /* temp__7 */;
  arguments->slots[5] = frame->slots[7] /* temp__8 */;
  arguments->slots[6] = frame->slots[8] /* temp__9 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__414_10;
}
static void cont__414_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_CODE, arguments->slots[0]);
  // 1605: ... newline, END_OF_TEXT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  arguments->slots[1] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__415_1;
}
static void cont__415_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1605: ... expect(newline, END_OF_TEXT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__415_2;
}
static void cont__415_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1605: $META_FRAGMENT META_INSTRUCTION, expect(newline, END_OF_TEXT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._META_INSTRUCTION;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__415_3;
}
static void cont__415_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._META_FRAGMENT, arguments->slots[0]);
  // 1613: syntax_error("top-level statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__227de92deba39b6b;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__416_2;
}
static void cont__416_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1609: alt
  // 1610:   SINGLE_REMARK_STATEMENT
  // 1611:   TOP_LEVEL_STATEMENT
  // 1612:   C_CODE
  // 1613:   syntax_error("top-level statement expected")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._SINGLE_REMARK_STATEMENT;
  arguments->slots[1] = var._TOP_LEVEL_STATEMENT;
  arguments->slots[2] = var._C_CODE;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__416_3;
}
static void cont__416_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1614: ... newline, END_OF_TEXT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  arguments->slots[1] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__416_4;
}
static void cont__416_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 1614: expect(newline, END_OF_TEXT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__416_5;
}
static void cont__416_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1607: $FRAGMENT
  // 1608:   sequence
  // 1609:     alt
  // 1610:       SINGLE_REMARK_STATEMENT
  // 1611:       TOP_LEVEL_STATEMENT
  // 1612:       C_CODE
  // 1613:       syntax_error("top-level statement expected")
  // 1614:     expect(newline, END_OF_TEXT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__416_6;
}
static void cont__416_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FRAGMENT, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__std_identifier_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 30: ... identifier(.namespace_of "std" .name_of name)
  {
    NODE *temp = clone_object_and_attributes(get__identifier());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__namespace_of, string__fa724815d896ba8);
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[0] /* name */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 30: ... -> identifier(.namespace_of "std" .name_of name)
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
  // 73: ... n+1
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
  // 73: ... "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
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
  // 73: ewrite "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
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
  // 75: ... "
  // 76:   ____________________________________
  // 77:   @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)":@nl;@(msg)!
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
  // 75: ewrite "
  // 76:   ____________________________________
  // 77:   @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)":@nl;@(msg)!
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
  // 78: ewriteln line
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
  // 79: ... dup(" " n)
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
  // 79: ewriteln dup(" " n) "^"
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
  // 52: $$source sim2c::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__sim2c__source_of();
  func = myself->type;
  frame->cont = cont__print_message_2;
}
static void cont__print_message_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* source */ = arguments->slots[0];
  // 53: ... length_of(source)
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
  // 53: ... length_of(source)-offset
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
  // 53: $pos length_of(source)-offset+1
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
  // 54: $$line_no line_no_of(fragment)
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
  // 57: ... pos-1
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
  // 57: ... range(source 1 pos-1)
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
  // 57: ... alt(newline indent_marker)
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
  // 56: $line_offset
  // 57:   count_occurrences(range(source 1 pos-1) alt(newline indent_marker))
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
  // 59: plus &line_no line_offset
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
  // 60: ... line_offset > 0
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
  // 60: ... : behind &source alt(newline indent_marker) line_offset
  frame->slots[13] /* temp__2 */ = create_closure(entry__print_message_13, 0);
  // 60: if line_offset > 0: behind &source alt(newline indent_marker) line_offset
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
  // 60: ... alt(newline indent_marker)
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
  // 60: ... behind &source alt(newline indent_marker) line_offset
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
  // 61: ... length_of(source)
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
  // 61: $$n length_of(source)-offset
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
  // 62: ... -> n > 0 && source(n) < ' ': dec &n
  frame->slots[12] /* temp__1 */ = create_closure(entry__print_message_19, 0);
  // 62: while -> n > 0 && source(n) < ' ': dec &n
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
  // 62: ... dec &n
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
  // 62: ... n > 0
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
  // 62: ... source(n) < ' '
  frame->slots[4] /* temp__3 */ = create_closure(entry__print_message_21, 0);
  // 62: ... n > 0 && source(n) < ' '
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
  // 62: ... source(n)
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
  // 62: ... source(n) < ' '
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
  // 62: ... source(n) < ' '
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
  // 62: ... : dec &n
  frame->slots[5] /* temp__4 */ = create_closure(entry__print_message_25, 0);
  // 62: ... -> n > 0 && source(n) < ' ': dec &n
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
  // 63: $text sim2c::text_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__sim2c__text_of();
  func = myself->type;
  frame->cont = cont__print_message_28;
}
static void cont__print_message_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* text */, arguments->slots[0]);
  // 64: ... line_offset > 0
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
  // 64: ... -> behind(text '@nl;' line_offset)
  frame->slots[13] /* temp__2 */ = create_closure(entry__print_message_30, 0);
  // 64: ... -> text
  frame->slots[14] /* temp__3 */ = create_closure(entry__print_message_32, 0);
  // 64: $rest if(line_offset > 0 (-> behind(text '@nl;' line_offset)) -> text)
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
  // 64: ... behind(text '@nl;' line_offset)
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
  // 64: ... -> behind(text '@nl;' line_offset)
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
  // 64: ... -> text
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
  // 65: ... alt('@cr;' '@nl;')
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
  // 65: ... rest .truncate_from. alt('@cr;' '@nl;')
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
  // 65: ... '@ht;' = "        "
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
  // 65: $line replace_all(rest .truncate_from. alt('@cr;' '@nl;') '@ht;' = "        ")
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
  // 66: ... : (-> break)
  // 67:   for_each line: (chr)
  // 68:     if chr != ' ' break
  // 69:     inc &n
  frame->slots[12] /* temp__1 */ = create_closure(entry__print_message_39, 0);
  // 66: do: (-> break)
  // 67:   for_each line: (chr)
  // 68:     if chr != ' ' break
  // 69:     inc &n
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
  // 67: ... : (chr)
  // 68:   if chr != ' ' break
  // 69:   inc &n
  frame->slots[3] /* temp__1 */ = create_closure(entry__print_message_40, 1);
  // 67: for_each line: (chr)
  // 68:   if chr != ' ' break
  // 69:   inc &n
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
  // 68: ... chr != ' '
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
  // 68: ... chr != ' '
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
  // 68: if chr != ' ' break
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
  // 69: inc &n
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
  // 70: ... msg(1)
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
  // 70: to_upper_case &msg(1)
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
  // 70: ... &msg(1)
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
  // 72: ... :
  // 73:   ewrite "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  frame->slots[12] /* temp__1 */ = create_closure(entry__print_message_50, 0);
  // 74: :
  // 75:   ewrite "
  // 76:     ____________________________________
  // 77:     @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)":@nl;@(msg)!
  // 78:   ewriteln line
  // 79:   ewriteln dup(" " n) "^"
  frame->slots[13] /* temp__2 */ = create_closure(entry__print_message_56, 0);
  // 71: if
  // 72:   do_show_brief_messages:
  // 73:     ewrite "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  // 74:   :
  // 75:     ewrite "
  // 76:       ____________________________________
  // 77:       @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)":@nl;@(msg)!
  // 78:     ewriteln line
  // 79:     ewriteln dup(" " n) "^"
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
static void entry__sim2c__Warning_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // obj: 0
  // msg: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 82: ... fragment_of(obj)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* obj */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__sim2c__Warning_2;
}
static void cont__sim2c__Warning_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 82: ... source_position_of(obj)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* obj */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__sim2c__Warning_3;
}
static void cont__sim2c__Warning_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 82: print_message fragment_of(obj) source_position_of(obj) "WARNING" msg
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
  // 85: print_message fragment offset "SYNTAX ERROR" msg
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
  // 86: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__sim2c__SyntaxError_1(void) {
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
  frame->cont = cont__sim2c__SyntaxError_2;
}
static void cont__sim2c__SyntaxError_2(void) {
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
  frame->cont = cont__sim2c__SyntaxError_3;
}
static void cont__sim2c__SyntaxError_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 89: ExitWithSyntaxError fragment_of(obj) source_position_of(obj) msg
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
  // 92: ... length_of(stream)
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
  // 92: ExitWithSyntaxError current_fragment length_of(stream) msg
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
  // 97: ... message_of(self)
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
  // 97: ParseError stream message_of(self)
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
  // 99: ... types::syntax_error(.message_of message)
  {
    NODE *temp = clone_object_and_attributes(var.types__syntax_error);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__message_of, frame->slots[0] /* message */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 99: ... -> types::syntax_error(.message_of message)
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
  // 113: ParseError stream "newline expected"
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
  // 115: ParseError stream "indent expected"
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
  // 117: ParseError stream "outdent expected"
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
  // 119: ParseError stream "closing quotation mark expected"
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
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // stream: 0
  // expression: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  frame->slots[1] = myself->closure.frame->slots[0]; /* expression */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: ... "
  // 122:   @quot;@(expression)" expected@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc3;
  arguments->slots[1] = frame->slots[1] /* expression */;
  arguments->slots[2] = string__33060513e6032545;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__types__unexpected_input_error__grammar__match_19;
}
static void cont__types__unexpected_input_error__grammar__match_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 121: ParseError stream "
  // 122:   @quot;@(expression)" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
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
  // 112: ... :
  // 113:   ParseError stream "newline expected"
  frame->slots[2] /* temp__1 */ = create_closure(entry__types__unexpected_input_error__grammar__match_8, 0);
  // 114: ... :
  // 115:   ParseError stream "indent expected"
  frame->slots[3] /* temp__2 */ = create_closure(entry__types__unexpected_input_error__grammar__match_10, 0);
  // 116: ... :
  // 117:   ParseError stream "outdent expected"
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__unexpected_input_error__grammar__match_12, 0);
  // 118: ... :
  // 119:   ParseError stream "closing quotation mark expected"
  frame->slots[5] /* temp__4 */ = create_closure(entry__types__unexpected_input_error__grammar__match_14, 0);
  // 120: :
  // 121:   ParseError stream "
  // 122:     @quot;@(expression)" expected@
  frame->slots[6] /* temp__5 */ = create_closure(entry__types__unexpected_input_error__grammar__match_16, 0);
  // 110: case
  // 111:   expression
  // 112:   newline:
  // 113:     ParseError stream "newline expected"
  // 114:   indent_marker:
  // 115:     ParseError stream "indent expected"
  // 116:   outdent_marker:
  // 117:     ParseError stream "outdent expected"
  // 118:   '@quot;':
  // 119:     ParseError stream "closing quotation mark expected"
  // ...
  argument_count = 10;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
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
static void entry__types__unexpected_input_error__grammar__match_20(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 124: ParseError stream "unexpected input"
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
  frame->slots[2] /* expression */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 107: $expression expression_of(self)
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
  initialize_future(frame->slots[2] /* expression */, arguments->slots[0]);
  // 109: expression.is_a_character
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* expression */;
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
  // 109: ... expression.is_a_string
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__unexpected_input_error__grammar__match_4, 0);
  // 109: expression.is_a_character || expression.is_a_string
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
  // 109: ... expression.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
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
  // 109: ... expression.is_a_string
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
  // 109: ... :
  // 110:   case
  // 111:     expression
  // 112:     newline:
  // 113:       ParseError stream "newline expected"
  // 114:     indent_marker:
  // 115:       ParseError stream "indent expected"
  // 116:     outdent_marker:
  // 117:       ParseError stream "outdent expected"
  // 118:     '@quot;':
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__types__unexpected_input_error__grammar__match_7, 0);
  // 123: :
  // 124:   ParseError stream "unexpected input"
  frame->slots[7] /* temp__5 */ = create_closure(entry__types__unexpected_input_error__grammar__match_20, 0);
  // 108: if
  // 109:   expression.is_a_character || expression.is_a_string:
  // 110:     case
  // 111:       expression
  // 112:       newline:
  // 113:         ParseError stream "newline expected"
  // 114:       indent_marker:
  // 115:         ParseError stream "indent expected"
  // 116:       outdent_marker:
  // 117:         ParseError stream "outdent expected"
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
  // 127: ... types::unexpected_input_error(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__unexpected_input_error);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 127: -> types::unexpected_input_error(.expression_of expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__print__grammar__match_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 136: ... message_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__message_of();
  func = myself->type;
  frame->cont = cont__types__print__grammar__match_2;
}
static void cont__types__print__grammar__match_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 136: ewriteln message_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__types__print__grammar__match_3;
}
static void cont__types__print__grammar__match_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 137: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__print_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // message: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 139: ... types::print(.message_of message)
  {
    NODE *temp = clone_object_and_attributes(var.types__print);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__message_of, frame->slots[0] /* message */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 139: ... -> types::print(.message_of message)
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
  // 148: ewriteln "<<<<<<<<<<"
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
  // 149: ... truncate_behind(stream '@nl;' 2)
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
  // 149: eprint_source truncate_behind(stream '@nl;' 2)
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
  // 150: ewriteln ">>>>>>>>>>"
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
  // 151: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__strip_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 158: !node.fragment_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 158: !node.fragment_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 159: !node.source_position_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 159: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 160: !node.end_position_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 160: !node.end_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 161: !node.inherited_names_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 161: !node.inherited_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__inherited_names_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 162: !node.defined_names_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 162: !node.defined_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__defined_names_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 163: !node.used_names_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 163: !node.used_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__used_names_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 164: ... functor_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_2;
}
static void cont__sim2c__strip_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 164: ... functor_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__strip_3;
}
static void cont__sim2c__strip_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 164: ... : strip &node.functor_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__sim2c__strip_4, 0);
  // 164: if functor_of(node).is_defined: strip &node.functor_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__strip_7;
}
static void entry__sim2c__strip_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 164: ... node.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_5;
}
static void cont__sim2c__strip_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 164: ... strip &node.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__sim2c__strip_6;
}
static void cont__sim2c__strip_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 164: ... &node.functor_of
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
static void cont__sim2c__strip_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 165: ... attribute_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_8;
}
static void cont__sim2c__strip_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 165: ... attribute_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__strip_9;
}
static void cont__sim2c__strip_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 165: ... : strip &node.attribute_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__sim2c__strip_10, 0);
  // 165: if attribute_of(node).is_defined: strip &node.attribute_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__strip_13;
}
static void entry__sim2c__strip_10(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 165: ... node.attribute_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_11;
}
static void cont__sim2c__strip_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 165: ... strip &node.attribute_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__sim2c__strip_12;
}
static void cont__sim2c__strip_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 165: ... &node.attribute_of
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
static void cont__sim2c__strip_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 166: ... statements_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_14;
}
static void cont__sim2c__strip_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 166: ... statements_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__strip_15;
}
static void cont__sim2c__strip_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 166: ... :
  // 167:   update_each &node.statements_of: (&statement) strip &statement
  frame->slots[3] /* temp__3 */ = create_closure(entry__sim2c__strip_16, 0);
  // 166: if statements_of(node).is_defined:
  // 167:   update_each &node.statements_of: (&statement) strip &statement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__strip_21;
}
static void entry__sim2c__strip_16(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 167: ... node.statements_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_17;
}
static void cont__sim2c__strip_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 167: update_each &node.statements_of: (&statement) strip &statement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__sim2c__strip_18;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__sim2c__strip_20;
}
static void entry__sim2c__strip_18(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // statement: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* statement */ = create_cell_with_contents(arguments->slots[0]);
  // 167: ... strip &statement
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* statement */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__sim2c__strip_19;
}
static void cont__sim2c__strip_19(void) {
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
static void cont__sim2c__strip_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 167: ... &node.statements_of
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
static void cont__sim2c__strip_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 168: ... parameters_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_22;
}
static void cont__sim2c__strip_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 168: ... parameters_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__strip_23;
}
static void cont__sim2c__strip_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 168: ... :
  // 169:   update_each &node.parameters_of: (&parameter) strip &parameter
  frame->slots[3] /* temp__3 */ = create_closure(entry__sim2c__strip_24, 0);
  // 168: if parameters_of(node).is_defined:
  // 169:   update_each &node.parameters_of: (&parameter) strip &parameter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__strip_29;
}
static void entry__sim2c__strip_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 169: ... node.parameters_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_25;
}
static void cont__sim2c__strip_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 169: update_each &node.parameters_of: (&parameter) strip &parameter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__sim2c__strip_26;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__sim2c__strip_28;
}
static void entry__sim2c__strip_26(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* parameter */ = create_cell_with_contents(arguments->slots[0]);
  // 169: ... strip &parameter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__sim2c__strip_27;
}
static void cont__sim2c__strip_27(void) {
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
static void cont__sim2c__strip_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 169: ... &node.parameters_of
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
static void cont__sim2c__strip_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 170: ... output_arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_30;
}
static void cont__sim2c__strip_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 170: ... output_arguments_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__strip_31;
}
static void cont__sim2c__strip_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 170: ... :
  // 171:   update_each &node.output_arguments_of: (&argument) strip &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__sim2c__strip_32, 0);
  // 170: if output_arguments_of(node).is_defined:
  // 171:   update_each &node.output_arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__strip_37;
}
static void entry__sim2c__strip_32(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: ... node.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_33;
}
static void cont__sim2c__strip_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 171: update_each &node.output_arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__sim2c__strip_34;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__sim2c__strip_36;
}
static void entry__sim2c__strip_34(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 171: ... strip &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__sim2c__strip_35;
}
static void cont__sim2c__strip_35(void) {
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
static void cont__sim2c__strip_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 171: ... &node.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__sim2c__strip_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_38;
}
static void cont__sim2c__strip_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 172: ... arguments_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__strip_39;
}
static void cont__sim2c__strip_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 172: ... :
  // 173:   update_each &node.arguments_of: (&argument) strip &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__sim2c__strip_40, 0);
  // 172: if arguments_of(node).is_defined:
  // 173:   update_each &node.arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__strip_45;
}
static void entry__sim2c__strip_40(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_41;
}
static void cont__sim2c__strip_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 173: update_each &node.arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__sim2c__strip_42;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__sim2c__strip_44;
}
static void entry__sim2c__strip_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 173: ... strip &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__sim2c__strip_43;
}
static void cont__sim2c__strip_43(void) {
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
static void cont__sim2c__strip_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 173: ... &node.arguments_of
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
static void cont__sim2c__strip_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 174: ... parent_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parent_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_46;
}
static void cont__sim2c__strip_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... parent_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__strip_47;
}
static void cont__sim2c__strip_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: ... : strip &node.parent_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__sim2c__strip_48, 0);
  // 174: if parent_of(node).is_defined: strip &node.parent_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__strip_51;
}
static void entry__sim2c__strip_48(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... node.parent_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__parent_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_49;
}
static void cont__sim2c__strip_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: ... strip &node.parent_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__sim2c__strip_50;
}
static void cont__sim2c__strip_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... &node.parent_of
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
static void cont__sim2c__strip_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 175: ... identifier_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_52;
}
static void cont__sim2c__strip_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 175: ... identifier_of(node).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__strip_53;
}
static void cont__sim2c__strip_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 175: ... : strip &node.identifier_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__sim2c__strip_54, 0);
  // 175: if identifier_of(node).is_defined: strip &node.identifier_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__strip_57;
}
static void entry__sim2c__strip_54(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: ... node.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__sim2c__strip_55;
}
static void cont__sim2c__strip_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 175: ... strip &node.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__sim2c__strip_56;
}
static void cont__sim2c__strip_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 175: ... &node.identifier_of
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
static void cont__sim2c__strip_57(void) {
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
  // 180: ... strip(grammar::current_node)
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
  // 180: edump `strip(grammar::current_node)
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
  // 181: -> 0
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
  // 186: ... strip(grammar::current_node)
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
  // 186: edump 3 `strip(grammar::current_node)
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
  // 187: -> 0
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
  // 192: ... strip(grammar::current_node)
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
  // 192: edump 5 `strip(grammar::current_node)
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
  // 193: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__precedence_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // op: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* op */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 226: ... precedence_table(op)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* op */;
  result_count = 1;
  myself = var._precedence_table;
  func = myself->type;
  frame->cont = cont__sim2c__precedence_4;
}
static void cont__sim2c__precedence_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 226: ... -> precedence_table(op)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__precedence_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 226: ... -> INFIX_PRECEDENCE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__INFIX_PRECEDENCE();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__precedence_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // op: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 226: ... op.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* op */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__sim2c__precedence_2;
}
static void cont__sim2c__precedence_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 226: ... -> precedence_table(op)
  frame->slots[2] /* temp__2 */ = create_closure(entry__sim2c__precedence_3, 0);
  // 226: if op.is_a_string (-> precedence_table(op)) -> INFIX_PRECEDENCE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = func__sim2c__precedence_5;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__sim2c__is_left_associative_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // prec: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 228: ... prec > 5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__5;
  arguments->slots[1] = frame->slots[0] /* prec */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__sim2c__is_left_associative_2;
}
static void cont__sim2c__is_left_associative_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 228: ... -> prec > 5
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
  // 230: ... prec <= 5
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
  // 230: ... prec <= 5
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
  // 230: ... -> prec <= 5
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
  // 233: ... sim2c::WHITESPACE, operator, sim2c::WHITESPACE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = frame->slots[0] /* operator */;
  arguments->slots[2] = var.sim2c__WHITESPACE;
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
  // 233: ... alt(operator sim2c::WHITESPACE, operator, sim2c::WHITESPACE)
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
  // 233: -> alt(operator sim2c::WHITESPACE, operator, sim2c::WHITESPACE)
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
  // 235: ... separator, expression
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
  // 235: ... some(separator, expression)
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
  // 235: ... expression, some(separator, expression)
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
  // 235: ... -> expression, some(separator, expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
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
  // 244: %within_inline_expression true
  initialize_maybe_future(get__within_inline_expression(), get__true());
  // 245: ... expression_of(self)
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
  // 245: grammar::match expression_of(self) stream
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
  // 247: ... types::inline(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__inline);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 247: ... -> types::inline(.expression_of expression)
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
  // 265: ... "@(description) expected"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  arguments->slots[1] = string__68d023a4c22b2461;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__expect_5;
}
static void cont__expect_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 265: ... syntax_error("@(description) expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__expect_6;
}
static void cont__expect_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 265: ... alt(expression syntax_error("@(description) expected"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__expect_7;
}
static void cont__expect_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 265: -> alt(expression syntax_error("@(description) expected"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__expect_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // expression: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* expression */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 266: ... unexpected_input_error(expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  result_count = 1;
  myself = var._unexpected_input_error;
  func = myself->type;
  frame->cont = cont__expect_9;
}
static void cont__expect_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 266: ... alt(expression unexpected_input_error(expression))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__expect_10;
}
static void cont__expect_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 266: -> alt(expression unexpected_input_error(expression))
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
  // 264: description.is_defined
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
  // 265: -> alt(expression syntax_error("@(description) expected"))
  frame->slots[3] /* temp__2 */ = create_closure(entry__expect_3, 0);
  // 266: -> alt(expression unexpected_input_error(expression))
  frame->slots[4] /* temp__3 */ = create_closure(entry__expect_8, 0);
  // 263: if
  // 264:   description.is_defined
  // 265:   -> alt(expression syntax_error("@(description) expected"))
  // 266:   -> alt(expression unexpected_input_error(expression))
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
static void entry__sim2c__arguments_span_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 285: ... expression, ENUMERATE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = var._ENUMERATE;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__sim2c__arguments_span_2;
}
static void cont__sim2c__arguments_span_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 285: ... multi_span(arguments_of expression, ENUMERATE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__arguments_of();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__sim2c__arguments_span_3;
}
static void cont__sim2c__arguments_span_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 285: -> multi_span(arguments_of expression, ENUMERATE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__output_arguments_span_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 288: ... expression, ENUMERATE, MAKE_A_DESTINATION
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = var._ENUMERATE;
  arguments->slots[2] = var._MAKE_A_DESTINATION;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__sim2c__output_arguments_span_2;
}
static void cont__sim2c__output_arguments_span_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 288: ... multi_span(output_arguments_of expression, ENUMERATE, MAKE_A_DESTINATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__output_arguments_of();
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__sim2c__output_arguments_span_3;
}
static void cont__sim2c__output_arguments_span_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 288: -> multi_span(output_arguments_of expression, ENUMERATE, MAKE_A_DESTINATION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__parse_meta_instruction_1(void) {
  allocate_initialized_frame_gc(2, 9);
  // slot allocations:
  // fragment: 0
  // return__1: 1
  // source: 2
  // len: 3
  // cap: 4
  frame->slots[1] /* return__1 */ = create_continuation();
  // _define %sim2c::current_fragment fragment
  define__sim2c__current_fragment(frame->slots[0] /* fragment */);
  frame->slots[2] /* source */ = create_future();
  frame->slots[3] /* len */ = create_future();
  frame->slots[4] /* cap */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1620: %sim2c::current_fragment fragment # used to generate meaningful error messages
  initialize_maybe_future(get__sim2c__current_fragment(), frame->slots[0] /* fragment */);
  // 1621: $source sim2c::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__sim2c__source_of();
  func = myself->type;
  frame->cont = cont__sim2c__parse_meta_instruction_2;
}
static void cont__sim2c__parse_meta_instruction_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* source */, arguments->slots[0]);
  // 1622: match source META_FRAGMENT $len $cap
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  arguments->slots[1] = var._META_FRAGMENT;
  result_count = 2;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__sim2c__parse_meta_instruction_3;
}
static void cont__sim2c__parse_meta_instruction_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 1622: ... len
  initialize_future(frame->slots[3] /* len */, frame->slots[5] /* temp__1 */);
  // 1622: ... cap
  initialize_future(frame->slots[4] /* cap */, frame->slots[6] /* temp__2 */);
  // 1623: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__sim2c__parse_meta_instruction_4;
}
static void cont__sim2c__parse_meta_instruction_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 1623: ... len != length_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__sim2c__parse_meta_instruction_5;
}
static void cont__sim2c__parse_meta_instruction_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1623: ... len != length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__sim2c__parse_meta_instruction_6;
}
static void cont__sim2c__parse_meta_instruction_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1623: ... : ParseError source "invalid meta instruction"
  frame->slots[8] /* temp__4 */ = create_closure(entry__sim2c__parse_meta_instruction_7, 0);
  // 1623: if len != length_of(source): ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__parse_meta_instruction_9;
}
static void entry__sim2c__parse_meta_instruction_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1623: ... ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__12eb1acbffa2ae01;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__sim2c__parse_meta_instruction_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1624: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__parse_statement_1(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // fragment: 0
  // return__1: 1
  // source: 2
  // len: 3
  // cap: 4
  frame->slots[1] /* return__1 */ = create_continuation();
  // _define %sim2c::current_fragment fragment
  define__sim2c__current_fragment(frame->slots[0] /* fragment */);
  frame->slots[2] /* source */ = create_future();
  frame->slots[3] /* len */ = create_future();
  frame->slots[4] /* cap */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1627: %sim2c::current_fragment fragment # used to generate meaningful error messages
  initialize_maybe_future(get__sim2c__current_fragment(), frame->slots[0] /* fragment */);
  // 1628: $source sim2c::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__sim2c__source_of();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_2;
}
static void cont__sim2c__parse_statement_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* source */, arguments->slots[0]);
  // 1629: match source FRAGMENT $len $cap
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  arguments->slots[1] = var._FRAGMENT;
  result_count = 2;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_3;
}
static void cont__sim2c__parse_statement_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 1629: ... len
  initialize_future(frame->slots[3] /* len */, frame->slots[5] /* temp__1 */);
  // 1629: ... cap
  initialize_future(frame->slots[4] /* cap */, frame->slots[6] /* temp__2 */);
  // 1631: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_4;
}
static void cont__sim2c__parse_statement_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1631: ... :
  // 1632:   if len != length_of(source):
  // 1633:     ParseError source "superficious input at end of expression"
  frame->slots[6] /* temp__2 */ = create_closure(entry__sim2c__parse_statement_5, 0);
  // 1634: :
  // 1635:   ewriteln "________________________________________"
  // 1636:   eprint_source source
  // 1637:   ewriteln "no match"
  // 1638:   exit 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__sim2c__parse_statement_11, 0);
  // 1630: if
  // 1631:   len.is_defined:
  // 1632:     if len != length_of(source):
  // 1633:       ParseError source "superficious input at end of expression"
  // 1634:   :
  // 1635:     ewriteln "________________________________________"
  // 1636:     eprint_source source
  // 1637:     ewriteln "no match"
  // 1638:     exit 1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_17;
}
static void entry__sim2c__parse_statement_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1633: ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__482d004bd19ca8db;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__sim2c__parse_statement_5(void) {
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
  // 1632: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_6;
}
static void cont__sim2c__parse_statement_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1632: ... len != length_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_7;
}
static void cont__sim2c__parse_statement_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1632: ... len != length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_8;
}
static void cont__sim2c__parse_statement_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1632: ... :
  // 1633:   ParseError source "superficious input at end of expression"
  frame->slots[5] /* temp__4 */ = create_closure(entry__sim2c__parse_statement_9, 0);
  // 1632: if len != length_of(source):
  // 1633:   ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__sim2c__parse_statement_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1635: ewriteln "________________________________________"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5278dd75c73e18e3;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_13;
}
static void cont__sim2c__parse_statement_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1636: eprint_source source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 0;
  myself = get__eprint_source();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_14;
}
static void cont__sim2c__parse_statement_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1637: ewriteln "no match"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6ca8a8f604cd4188;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__sim2c__parse_statement_16;
}
static void cont__sim2c__parse_statement_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1638: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__sim2c__parse_statement_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1639: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__parser(void) {
  var.sim2c__std_identifier = collect_node(var.sim2c__std_identifier);
  var._print_message = collect_node(var._print_message);
  var.sim2c__Warning = collect_node(var.sim2c__Warning);
  var._ExitWithSyntaxError = collect_node(var._ExitWithSyntaxError);
  var.sim2c__SyntaxError = collect_node(var.sim2c__SyntaxError);
  var._ParseError = collect_node(var._ParseError);
  var.types__syntax_error = collect_node(var.types__syntax_error);
  var._syntax_error = collect_node(var._syntax_error);
  var.types__unexpected_input_error = collect_node(var.types__unexpected_input_error);
  var._unexpected_input_error = collect_node(var._unexpected_input_error);
  var.types__print = collect_node(var.types__print);
  var._print = collect_node(var._print);
  var._dump_stream = collect_node(var._dump_stream);
  var.sim2c__strip = collect_node(var.sim2c__strip);
  var._dump = collect_node(var._dump);
  var._dump3 = collect_node(var._dump3);
  var._dump5 = collect_node(var._dump5);
  var.sim2c__HIGHEST_PRECEDENCE = collect_node(var.sim2c__HIGHEST_PRECEDENCE);
  var.sim2c__INFIX_PRECEDENCE = collect_node(var.sim2c__INFIX_PRECEDENCE);
  var._precedence_table = collect_node(var._precedence_table);
  var.sim2c__precedence = collect_node(var.sim2c__precedence);
  var.sim2c__is_left_associative = collect_node(var.sim2c__is_left_associative);
  var._is_right_associative = collect_node(var._is_right_associative);
  var._infix_operator = collect_node(var._infix_operator);
  var._interleaved = collect_node(var._interleaved);
  var.types__inline = collect_node(var.types__inline);
  var._inline = collect_node(var._inline);
  var._NOT_INLINE = collect_node(var._NOT_INLINE);
  var._NEWLINE = collect_node(var._NEWLINE);
  var._INDENT = collect_node(var._INDENT);
  var._OUTDENT = collect_node(var._OUTDENT);
  var._HASHTAG = collect_node(var._HASHTAG);
  var._expect = collect_node(var._expect);
  var._ENUMERATE = collect_node(var._ENUMERATE);
  var._MAKE_A_DESTINATION = collect_node(var._MAKE_A_DESTINATION);
  var.sim2c__arguments_span = collect_node(var.sim2c__arguments_span);
  var.sim2c__output_arguments_span = collect_node(var.sim2c__output_arguments_span);
  var.sim2c__WHITESPACE = collect_node(var.sim2c__WHITESPACE);
  var._SEPARATOR = collect_node(var._SEPARATOR);
  var._NEWLINES = collect_node(var._NEWLINES);
  var._NEXT_LINE = collect_node(var._NEXT_LINE);
  var._STORE_POSITION = collect_node(var._STORE_POSITION);
  var._STORE_POSITION_MINUS_1 = collect_node(var._STORE_POSITION_MINUS_1);
  var._STORE_POSITION_MINUS_2 = collect_node(var._STORE_POSITION_MINUS_2);
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
  var._SINGLE_REMARK_STATEMENT = collect_node(var._SINGLE_REMARK_STATEMENT);
  var._REMARK_STATEMENT = collect_node(var._REMARK_STATEMENT);
  var._REMARK = collect_node(var._REMARK);
  var._REMARK_BEHIND = collect_node(var._REMARK_BEHIND);
  var._LINE_END_REMARK = collect_node(var._LINE_END_REMARK);
  var._ARGUMENT_LINE_END_REMARK = collect_node(var._ARGUMENT_LINE_END_REMARK);
  var._ARGUMENT_REMARK = collect_node(var._ARGUMENT_REMARK);
  var._NEW_LINE_END_REMARK = collect_node(var._NEW_LINE_END_REMARK);
  var._NEXT_LINE_REMARK = collect_node(var._NEXT_LINE_REMARK);
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
  var._INPUT_ARGUMENT = collect_node(var._INPUT_ARGUMENT);
  var._EXPANSION = collect_node(var._EXPANSION);
  var._OUTPUT_ARGUMENT = collect_node(var._OUTPUT_ARGUMENT);
  var._INPUT_OUTPUT_ARGUMENT = collect_node(var._INPUT_OUTPUT_ARGUMENT);
  var._COPY_OUTPUT = collect_node(var._COPY_OUTPUT);
  var._MAYBE_SPLIT_INPUT = collect_node(var._MAYBE_SPLIT_INPUT);
  var._SIMPLE_ARGUMENT = collect_node(var._SIMPLE_ARGUMENT);
  var._INLINE_ATTRIBUTE_VALUE_PAIR = collect_node(var._INLINE_ATTRIBUTE_VALUE_PAIR);
  var._ATTRIBUTE_VALUE_PAIR = collect_node(var._ATTRIBUTE_VALUE_PAIR);
  var._INLINE_ATTRIBUTE_VALUE_PAIRS = collect_node(var._INLINE_ATTRIBUTE_VALUE_PAIRS);
  var._INDENTED_ATTRIBUTE_VALUE_PAIRS = collect_node(var._INDENTED_ATTRIBUTE_VALUE_PAIRS);
  var._SINGLE_EXPRESSION_LINE = collect_node(var._SINGLE_EXPRESSION_LINE);
  var._PROCEDURE_ARGUMENTS = collect_node(var._PROCEDURE_ARGUMENTS);
  var._ARGUMENTS = collect_node(var._ARGUMENTS);
  var._OPERATORS_AND_OPERANDS = collect_node(var._OPERATORS_AND_OPERANDS);
  var._MULTI_LINE_FUNCTION_CALL = collect_node(var._MULTI_LINE_FUNCTION_CALL);
  var._original_remark_lines_of = collect_node(var._original_remark_lines_of);
  var._INDENTED_FUNCTION_CALL_OR_REMARK = collect_node(var._INDENTED_FUNCTION_CALL_OR_REMARK);
  var._MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK = collect_node(var._MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK);
  var._ARGUMENT_EXPANSION = collect_node(var._ARGUMENT_EXPANSION);
  var._MULTI_LINE_EXPRESSION = collect_node(var._MULTI_LINE_EXPRESSION);
  var._LINE_START_ARGUMENT = collect_node(var._LINE_START_ARGUMENT);
  var._LINE_START_ARGUMENTS = collect_node(var._LINE_START_ARGUMENTS);
  var._MORE_LINE_START_ARGUMENTS = collect_node(var._MORE_LINE_START_ARGUMENTS);
  var._FIRST_LINE_START_ARGUMENTS = collect_node(var._FIRST_LINE_START_ARGUMENTS);
  var._SINGLE_INPUT_ARGUMENT = collect_node(var._SINGLE_INPUT_ARGUMENT);
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
  var._ASSIGNMENT = collect_node(var._ASSIGNMENT);
  var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER = collect_node(var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER);
  var._POLYMORPHIC_FUNCTION_WITH_SETTER = collect_node(var._POLYMORPHIC_FUNCTION_WITH_SETTER);
  var._POLYMORPHIC_FUNCTION = collect_node(var._POLYMORPHIC_FUNCTION);
  var._TOP_LEVEL_ASSIGNMENT = collect_node(var._TOP_LEVEL_ASSIGNMENT);
  var._FUNCTOR = collect_node(var._FUNCTOR);
  var._RESULT_COUNT_OR_CONTINUATION = collect_node(var._RESULT_COUNT_OR_CONTINUATION);
  var._PROCEDURE_CALL = collect_node(var._PROCEDURE_CALL);
  var._INDENTED_REMARKS = collect_node(var._INDENTED_REMARKS);
  var._SINGLE_STATEMENT = collect_node(var._SINGLE_STATEMENT);
  var._TOP_LEVEL_STATEMENT = collect_node(var._TOP_LEVEL_STATEMENT);
  var._STATEMENT = collect_node(var._STATEMENT);
  var._RETURN_STATEMENT = collect_node(var._RETURN_STATEMENT);
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
  var.sim2c__parse_meta_instruction = collect_node(var.sim2c__parse_meta_instruction);
  var.sim2c__parse_statement = collect_node(var.sim2c__parse_statement);
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
  func__sim2c__std_identifier_1 = create_function(entry__sim2c__std_identifier_1, 1);
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
  func__sim2c__Warning_1 = create_function(entry__sim2c__Warning_1, 2);
  string__ae3c04ed6f185295 = from_latin_1_string("SYNTAX ERROR", 12);
  func__ExitWithSyntaxError_1 = create_function(entry__ExitWithSyntaxError_1, 3);
  func__sim2c__SyntaxError_1 = create_function(entry__sim2c__SyntaxError_1, 2);
  func__ParseError_1 = create_function(entry__ParseError_1, 2);
  func__types__syntax_error__grammar__match_1 = create_function(entry__types__syntax_error__grammar__match_1, 2);
  func__syntax_error_1 = create_function(entry__syntax_error_1, 1);
  string__9a64e069c352dc6a = from_latin_1_string("newline expected", 16);
  string__927507b8d9967cca = from_latin_1_string("indent expected", 15);
  string__9be468e9e34a9c6a = from_latin_1_string("outdent expected", 16);
  string__ab853eb411a7faea = from_latin_1_string("closing quotation mark expected", 31);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__33060513e6032545 = from_latin_1_string("\042 expected", 10);
  string__4914d002f7e03078 = from_latin_1_string("unexpected input", 16);
  func__types__unexpected_input_error__grammar__match_1 = create_function(entry__types__unexpected_input_error__grammar__match_1, 2);
  func__unexpected_input_error_1 = create_function(entry__unexpected_input_error_1, 1);
  func__types__print__grammar__match_1 = create_function(entry__types__print__grammar__match_1, 2);
  func__print_1 = create_function(entry__print_1, 1);
  string__8c16e735f8cebe3d = from_latin_1_string("<<<<<<<<<<", 10);
  string__881ef7b4fade9e7f = from_latin_1_string(">>>>>>>>>>", 10);
  func__dump_stream__grammar__match_1 = create_function(entry__dump_stream__grammar__match_1, 2);
  func__sim2c__strip_18 = create_function(entry__sim2c__strip_18, 1);
  func__sim2c__strip_26 = create_function(entry__sim2c__strip_26, 1);
  func__sim2c__strip_34 = create_function(entry__sim2c__strip_34, 1);
  func__sim2c__strip_42 = create_function(entry__sim2c__strip_42, 1);
  func__sim2c__strip_1 = create_function(entry__sim2c__strip_1, 1);
  string__665e06ec4dcad6be = from_latin_1_string("strip(grammar::current_node)", 28);
  func__dump__grammar__match_1 = create_function(entry__dump__grammar__match_1, 2);
  func__dump3__grammar__match_1 = create_function(entry__dump3__grammar__match_1, 2);
  func__dump5__grammar__match_1 = create_function(entry__dump5__grammar__match_1, 2);
  func__sim2c__precedence_5 = create_function(entry__sim2c__precedence_5, 0);
  func__sim2c__precedence_1 = create_function(entry__sim2c__precedence_1, 1);
  func__sim2c__is_left_associative_1 = create_function(entry__sim2c__is_left_associative_1, 1);
  func__is_right_associative_1 = create_function(entry__is_right_associative_1, 1);
  func__infix_operator_1 = create_function(entry__infix_operator_1, 1);
  func__interleaved_1 = create_function(entry__interleaved_1, 2);
  func__types__inline__grammar__match_1 = create_function(entry__types__inline__grammar__match_1, 2);
  func__inline_1 = create_function(entry__inline_1, 1);
  string__68d023a4c22b2461 = from_latin_1_string(" expected", 9);
  func__expect_1 = create_function(entry__expect_1, -1);
  func__sim2c__arguments_span_1 = create_function(entry__sim2c__arguments_span_1, 1);
  func__sim2c__output_arguments_span_1 = create_function(entry__sim2c__output_arguments_span_1, 1);
  register_polymorphic_function("_parser::original_remark_lines_of", &poly_idx__original_remark_lines_of);
  string__12eb1acbffa2ae01 = from_latin_1_string("invalid meta instruction", 24);
  func__sim2c__parse_meta_instruction_1 = create_function(entry__sim2c__parse_meta_instruction_1, 1);
  string__482d004bd19ca8db = from_latin_1_string("superficious input at end of expression", 39);
  string__5278dd75c73e18e3 = from_latin_1_string("________________________________________", 40);
  string__6ca8a8f604cd4188 = from_latin_1_string("no match", 8);
  func__sim2c__parse_statement_1 = create_function(entry__sim2c__parse_statement_1, 1);
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
  func__246_1 = create_function(entry__246_1, 2);
  func__252_1 = create_function(entry__252_1, 1);
  func__253_1 = create_function(entry__253_1, 1);
  func__260_1 = create_function(entry__260_1, 2);
  func__261_1 = create_function(entry__261_1, 2);
  func__262_1 = create_function(entry__262_1, 2);
  func__263_1 = create_function(entry__263_1, 2);
  func__264_3 = create_function(entry__264_3, 1);
  string__2d7981f4e6d82bff = from_latin_1_string("::", 2);
  string__958c1dda41e5a79c = from_latin_1_string("namespace must not start with an underscore", 43);
  func__265_4 = create_function(entry__265_4, 1);
  string__2d7981f4e6782bea = from_latin_1_string("./", 2);
  string__92e1510f182d5769 = from_latin_1_string("the module \042", 12);
  string__fd365ba9213c93f1 = from_latin_1_string("\042 is required twice", 19);
  func__268_3 = create_function(entry__268_3, 2);
  string__44dcaf9484448bc5 = from_latin_1_string("<require", 8);
  func__269_4 = create_function(entry__269_4, 1);
  string__e13e5990aea4c8f3 = from_latin_1_string("the namespace alias \042", 21);
  string__54767964cc2066c4 = from_latin_1_string("\042 is defined twice", 18);
  string__9159abe89634488c = from_latin_1_string("the namespace \042", 15);
  func__269_10 = create_function(entry__269_10, 2);
  string__1552f059283245c4 = from_latin_1_string("<namespace", 10);
  string__1d0508008a8a40d8 = from_latin_1_string("\042 is used twice", 15);
  func__270_3 = create_function(entry__270_3, 2);
  string__7e1f542e81cb02b0 = from_latin_1_string("<using", 6);
  string__fa733c15f596be3 = from_latin_1_string("../", 3);
  string__2c64b158ac2be503 = from_latin_1_string("the file \042", 10);
  string__b0b6bb19371893f7 = from_latin_1_string("\042 is included twice", 19);
  func__273_3 = create_function(entry__273_3, 2);
  string__76b0a89104f5abc5 = from_latin_1_string("<include", 8);
  string__a660d7293a5c47e8 = from_latin_1_string("the library \042", 13);
  string__ad06d2ccd69d8e1 = from_latin_1_string("\042 is linked twice", 17);
  func__274_3 = create_function(entry__274_3, 2);
  string__525ae943eabdd03c = from_latin_1_string("<link", 5);
  string__e720c6242e8cd532 = from_latin_1_string("the data dependency \042", 21);
  func__277_3 = create_function(entry__277_3, 2);
  string__425aeb43ea6dd036 = from_latin_1_string("<data", 5);
  func__284_1 = create_function(entry__284_1, 1);
  func__286_1 = create_function(entry__286_1, 1);
  func__287_1 = create_function(entry__287_1, 1);
  func__290_1 = create_function(entry__290_1, 1);
  func__291_1 = create_function(entry__291_1, 1);
  string__2d7981f4e6882ba7 = from_latin_1_string("0b", 2);
  string__2d7981f4e6882baa = from_latin_1_string("0o", 2);
  string__2d7981f4e6882bbd = from_latin_1_string("0x", 2);
  func__306_2 = create_function(entry__306_2, 1);
  func__307_1 = create_function(entry__307_1, 1);
  string__dea962eab6ac8f23 = from_latin_1_string("invalid character name", 22);
  func__308_2 = create_function(entry__308_2, 2);
  func__309_10 = create_function(entry__309_10, 1);
  string__4313674f4741806a = from_latin_1_string("invalid special character", 25);
  func__313_1 = create_function(entry__313_1, 1);
  string__2d7981f4e5082bfe = from_latin_1_string("@;", 2);
  func__314_1 = create_function(entry__314_1, 1);
  string__2d7981f4e5082bed = from_latin_1_string("@(", 2);
  string__7c1f540901cb12b0 = from_latin_1_string("string", 6);
  func__315_1 = create_function(entry__315_1, 1);
  func__318_1 = create_function(entry__318_1, 1);
  string__55df65a142fc9536 = from_latin_1_string("expression expected", 19);
  string__64d512703527e2ab = from_latin_1_string("key_value_pair", 14);
  string__2a0aedcb5dc87d5c = from_latin_1_string("true", 4);
  func__322_1 = create_function(entry__322_1, 1);
  string__2d7981f4e6602be8 = from_latin_1_string("--", 2);
  func__323_1 = create_function(entry__323_1, 1);
  func__330_2 = create_function(entry__330_2, 1);
  func__331_13 = create_function(entry__331_13, 0);
  func__331_53 = create_function(entry__331_53, 0);
  func__331_1 = create_function(entry__331_1, 1);
  string__395c5a51a203e553 = from_latin_1_string("identifier", 10);
  string__2d7981f4e6282be1 = from_latin_1_string("$$", 2);
  string__2d7981f4e6202be0 = from_latin_1_string("%%", 2);
  func__340_1 = create_function(entry__340_1, 1);
  func__348_1 = create_function(entry__348_1, 1);
  func__349_1 = create_function(entry__349_1, 1);
  func__359_1 = create_function(entry__359_1, 1);
  func__359_6 = create_function(entry__359_6, 1);
  func__361_1 = create_function(entry__361_1, 1);
  func__361_4 = create_function(entry__361_4, 1);
  func__364_3 = create_function(entry__364_3, 1);
  string__733ccdbfc49ced05 = from_latin_1_string("too few arguments in multi-line expression", 42);
  func__364_8 = create_function(entry__364_8, 2);
  func__365_10 = create_function(entry__365_10, 1);
  func__372_1 = create_function(entry__372_1, 1);
  string__2d7981f4e6602bfb = from_latin_1_string("->", 2);
  string__5ed2969d8211684f = from_latin_1_string("statement expected", 18);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  string__fa732415f216be5 = from_latin_1_string("(!)", 3);
  string__b6a1aa36d1f3b32e = from_latin_1_string("invalid polymorphic function definition", 39);
  func__389_5 = create_function(entry__389_5, 1);
  string__2d7981f4e6782bed = from_latin_1_string(".(", 2);
  string__a6b4597d46108e45 = from_latin_1_string("return statement needs at least one argument", 44);
  func__397_2 = create_function(entry__397_2, 1);
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
  define_single_assign_static("sim2c", "std_identifier", get__sim2c__std_identifier, &var.sim2c__std_identifier);
  define_single_assign_static("sim2c", "Warning", get__sim2c__Warning, &var.sim2c__Warning);
  define_single_assign_static("sim2c", "SyntaxError", get__sim2c__SyntaxError, &var.sim2c__SyntaxError);
  define_single_assign_static("types", "syntax_error", get__types__syntax_error, &var.types__syntax_error);
  define_single_assign_static("types", "unexpected_input_error", get__types__unexpected_input_error, &var.types__unexpected_input_error);
  define_single_assign_static("types", "print", get__types__print, &var.types__print);
  define_single_assign_static("sim2c", "strip", get__sim2c__strip, &var.sim2c__strip);
  define_single_assign_static("sim2c", "HIGHEST_PRECEDENCE", get__sim2c__HIGHEST_PRECEDENCE, &var.sim2c__HIGHEST_PRECEDENCE);
  define_single_assign_static("sim2c", "INFIX_PRECEDENCE", get__sim2c__INFIX_PRECEDENCE, &var.sim2c__INFIX_PRECEDENCE);
  var._precedence_table = create_future();
  define_single_assign_static("sim2c", "precedence", get__sim2c__precedence, &var.sim2c__precedence);
  define_single_assign_static("sim2c", "is_left_associative", get__sim2c__is_left_associative, &var.sim2c__is_left_associative);
  register_dynamic(&dyna_idx__within_inline_expression);
  define__within_inline_expression(create_future());
  define_single_assign_static("types", "inline", get__types__inline, &var.types__inline);
  var._NOT_INLINE = create_future();
  var._NEWLINE = create_future();
  var._INDENT = create_future();
  var._OUTDENT = create_future();
  var._HASHTAG = create_future();
  var._ENUMERATE = create_future();
  var._MAKE_A_DESTINATION = create_future();
  define_single_assign_static("sim2c", "arguments_span", get__sim2c__arguments_span, &var.sim2c__arguments_span);
  define_single_assign_static("sim2c", "output_arguments_span", get__sim2c__output_arguments_span, &var.sim2c__output_arguments_span);
  define_single_assign_static("sim2c", "WHITESPACE", get__sim2c__WHITESPACE, &var.sim2c__WHITESPACE);
  var._SEPARATOR = create_future();
  var._NEWLINES = create_future();
  var._NEXT_LINE = create_future();
  var._STORE_POSITION = create_future();
  var._STORE_POSITION_MINUS_1 = create_future();
  var._STORE_POSITION_MINUS_2 = create_future();
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
  var._SINGLE_REMARK_STATEMENT = create_future();
  var._REMARK_STATEMENT = create_future();
  var._REMARK = create_future();
  var._REMARK_BEHIND = create_future();
  var._LINE_END_REMARK = create_future();
  var._ARGUMENT_LINE_END_REMARK = create_future();
  var._ARGUMENT_REMARK = create_future();
  var._NEW_LINE_END_REMARK = create_future();
  var._NEXT_LINE_REMARK = create_future();
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
  var._INPUT_ARGUMENT = create_future();
  var._EXPANSION = create_future();
  var._OUTPUT_ARGUMENT = create_future();
  var._INPUT_OUTPUT_ARGUMENT = create_future();
  var._COPY_OUTPUT = create_future();
  var._MAYBE_SPLIT_INPUT = create_future();
  var._SIMPLE_ARGUMENT = create_future();
  var._INLINE_ATTRIBUTE_VALUE_PAIR = create_future();
  var._ATTRIBUTE_VALUE_PAIR = create_future();
  var._INLINE_ATTRIBUTE_VALUE_PAIRS = create_future();
  var._INDENTED_ATTRIBUTE_VALUE_PAIRS = create_future();
  var._SINGLE_EXPRESSION_LINE = create_future();
  var._PROCEDURE_ARGUMENTS = create_future();
  var._ARGUMENTS = create_future();
  var._OPERATORS_AND_OPERANDS = create_future();
  var._MULTI_LINE_FUNCTION_CALL = create_future();
  var._INDENTED_FUNCTION_CALL_OR_REMARK = create_future();
  var._MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK = create_future();
  var._ARGUMENT_EXPANSION = create_future();
  var._MULTI_LINE_EXPRESSION = create_future();
  var._LINE_START_ARGUMENT = create_future();
  var._LINE_START_ARGUMENTS = create_future();
  var._MORE_LINE_START_ARGUMENTS = create_future();
  var._FIRST_LINE_START_ARGUMENTS = create_future();
  var._SINGLE_INPUT_ARGUMENT = create_future();
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
  var._ASSIGNMENT = create_future();
  var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER = create_future();
  var._POLYMORPHIC_FUNCTION_WITH_SETTER = create_future();
  var._POLYMORPHIC_FUNCTION = create_future();
  var._TOP_LEVEL_ASSIGNMENT = create_future();
  var._FUNCTOR = create_future();
  var._RESULT_COUNT_OR_CONTINUATION = create_future();
  var._PROCEDURE_CALL = create_future();
  var._INDENTED_REMARKS = create_future();
  var._SINGLE_STATEMENT = create_future();
  var._TOP_LEVEL_STATEMENT = create_future();
  var._STATEMENT = create_future();
  var._RETURN_STATEMENT = create_future();
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
  define_single_assign_static("sim2c", "parse_meta_instruction", get__sim2c__parse_meta_instruction, &var.sim2c__parse_meta_instruction);
  define_single_assign_static("sim2c", "parse_statement", get__sim2c__parse_statement, &var.sim2c__parse_statement);
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
  use_read_only(NULL, "OUT_PARAMETER", &get__OUT_PARAMETER, &get_value_or_future__OUT_PARAMETER);
  use_read_only(NULL, "POLYMORPHIC", &get__POLYMORPHIC, &get_value_or_future__POLYMORPHIC);
  use_read_only(NULL, "PRINTABLE_CHARACTER", &get__PRINTABLE_CHARACTER, &get_value_or_future__PRINTABLE_CHARACTER);
  use_read_only(NULL, "SyntaxError", &get__SyntaxError, &get_value_or_future__SyntaxError);
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
  use_read_only(NULL, "do_show_brief_messages", &get__do_show_brief_messages, &get_value_or_future__do_show_brief_messages);
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_read_only(NULL, "edump", &get__edump, &get_value_or_future__edump);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_polymorphic_function(NULL, "end_position_of", &get__end_position_of, &poly_idx__end_position_of);
  use_read_write(NULL, "enumeration_count", &get__enumeration_count, &set__enumeration_count);
  use_polymorphic_function(NULL, "enumeration_no_of", &get__enumeration_no_of, &poly_idx__enumeration_no_of);
  use_read_only(NULL, "eprint_source", &get__eprint_source, &get_value_or_future__eprint_source);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "ewriteln", &get__ewriteln, &get_value_or_future__ewriteln);
  use_read_only(NULL, "exit", &get__exit, &get_value_or_future__exit);
  use_read_only(NULL, "expression", &get__expression, &get_value_or_future__expression);
  use_polymorphic_function(NULL, "expression_of", &get__expression_of, &poly_idx__expression_of);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "followed_by", &get__followed_by, &get_value_or_future__followed_by);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
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
  use_read_only(NULL, "is_a_character", &get__is_a_character, &get_value_or_future__is_a_character);
  use_read_only(NULL, "is_a_definition", &get__is_a_definition, &get_value_or_future__is_a_definition);
  use_polymorphic_function(NULL, "is_a_destination", &get__is_a_destination, &poly_idx__is_a_destination);
  use_read_only(NULL, "is_a_meta_instruction", &get__is_a_meta_instruction, &get_value_or_future__is_a_meta_instruction);
  use_polymorphic_function(NULL, "is_a_method_definition", &get__is_a_method_definition, &poly_idx__is_a_method_definition);
  use_read_only(NULL, "is_a_string", &get__is_a_string, &get_value_or_future__is_a_string);
  use_polymorphic_function(NULL, "is_a_string_template", &get__is_a_string_template, &poly_idx__is_a_string_template);
  use_polymorphic_function(NULL, "is_an_attribute_access", &get__is_an_attribute_access, &poly_idx__is_an_attribute_access);
  use_read_only(NULL, "is_an_expanded_item", &get__is_an_expanded_item, &get_value_or_future__is_an_expanded_item);
  use_read_only(NULL, "is_an_optional_item", &get__is_an_optional_item, &get_value_or_future__is_an_optional_item);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_polymorphic_function(NULL, "is_in_infix_notation", &get__is_in_infix_notation, &poly_idx__is_in_infix_notation);
  use_polymorphic_function(NULL, "is_in_numeric_notation", &get__is_in_numeric_notation, &poly_idx__is_in_numeric_notation);
  use_read_only(NULL, "is_left_associative", &get__is_left_associative, &get_value_or_future__is_left_associative);
  use_polymorphic_function(NULL, "is_not_used", &get__is_not_used, &poly_idx__is_not_used);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
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
  use_read_only(NULL, "not_followed_by", &get__not_followed_by, &get_value_or_future__not_followed_by);
  use_read_only(NULL, "numeric_literal", &get__numeric_literal, &get_value_or_future__numeric_literal);
  use_read_only(NULL, "operator_symbol", &get__operator_symbol, &get_value_or_future__operator_symbol);
  use_read_only(NULL, "operators_of", &get__operators_of, &get_value_or_future__operators_of);
  use_read_only(NULL, "optional", &get__optional, &get_value_or_future__optional);
  use_read_only(NULL, "outdent_marker", &get__outdent_marker, &get_value_or_future__outdent_marker);
  use_polymorphic_function(NULL, "output_arguments_of", &get__output_arguments_of, &poly_idx__output_arguments_of);
  use_read_only(NULL, "output_arguments_span", &get__output_arguments_span, &get_value_or_future__output_arguments_span);
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
  use_polymorphic_function(NULL, "remark_lines_behind_of", &get__remark_lines_behind_of, &poly_idx__remark_lines_behind_of);
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
  use_single_assign_dynamic("sim2c", "current_fragment", &get__sim2c__current_fragment, &define__sim2c__current_fragment);
  use_read_only("sim2c", "source_of", &get__sim2c__source_of, &get_value_or_future__sim2c__source_of);
  use_read_only("sim2c", "text_of", &get__sim2c__text_of, &get_value_or_future__sim2c__text_of);
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
  define_method("types", "print", poly_idx__grammar__match, func__types__print__grammar__match_1);
  update_start_p = node_p;
  def_attribute(&var._dump_stream, poly_idx__grammar__match, func__dump_stream__grammar__match_1);
  update_start_p = node_p;
  def_attribute(&var._dump, poly_idx__grammar__match, func__dump__grammar__match_1);
  update_start_p = node_p;
  def_attribute(&var._dump3, poly_idx__grammar__match, func__dump3__grammar__match_1);
  update_start_p = node_p;
  def_attribute(&var._dump5, poly_idx__grammar__match, func__dump5__grammar__match_1);
  define_method("types", "inline", poly_idx__grammar__match, func__types__inline__grammar__match_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__parser(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.sim2c__std_identifier, &func__sim2c__std_identifier_1);
  assign_variable(&var._print_message, &func__print_message_1);
  assign_variable(&var.sim2c__Warning, &func__sim2c__Warning_1);
  assign_variable(&var._ExitWithSyntaxError, &func__ExitWithSyntaxError_1);
  assign_variable(&var.sim2c__SyntaxError, &func__sim2c__SyntaxError_1);
  assign_variable(&var._ParseError, &func__ParseError_1);
  assign_value(&var.types__syntax_error, get__types__grammar_object());
  assign_variable(&var._syntax_error, &func__syntax_error_1);
  assign_value(&var.types__unexpected_input_error, get__types__grammar_object());
  assign_variable(&var._unexpected_input_error, &func__unexpected_input_error_1);
  assign_value(&var.types__print, get__types__grammar_object());
  assign_variable(&var._print, &func__print_1);
  assign_value(&var._dump_stream, get__types__grammar_object());
  assign_variable(&var.sim2c__strip, &func__sim2c__strip_1);
  assign_value(&var._dump, get__types__grammar_object());
  assign_value(&var._dump3, get__types__grammar_object());
  assign_value(&var._dump5, get__types__grammar_object());
  assign_value(&var.sim2c__HIGHEST_PRECEDENCE, number__99);
  assign_value(&var.sim2c__INFIX_PRECEDENCE, number__6);
  assign_variable(&var.sim2c__precedence, &func__sim2c__precedence_1);
  assign_variable(&var.sim2c__is_left_associative, &func__sim2c__is_left_associative_1);
  assign_variable(&var._is_right_associative, &func__is_right_associative_1);
  assign_variable(&var._infix_operator, &func__infix_operator_1);
  assign_variable(&var._interleaved, &func__interleaved_1);
  maybe_initialize_future(get__within_inline_expression(), get__false());
  assign_value(&var.types__inline, get__types__grammar_object());
  assign_variable(&var._inline, &func__inline_1);
  assign_variable(&var._expect, &func__expect_1);
  assign_variable(&var.sim2c__arguments_span, &func__sim2c__arguments_span_1);
  assign_variable(&var.sim2c__output_arguments_span, &func__sim2c__output_arguments_span_1);
  assign_value(&var._original_remark_lines_of, create_function(type__original_remark_lines_of, -1));
  assign_variable(&var.sim2c__parse_meta_instruction, &func__sim2c__parse_meta_instruction_1);
  assign_variable(&var.sim2c__parse_statement, &func__sim2c__parse_statement_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__parser(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__parser);
}
