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
IMPORT void register_polymorphic_function(const char *name, int *id_p);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
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
static NODE *func__1_1_sim2c__std_identifier;
static void entry__1_1_sim2c__std_identifier(void);
static FRAME_INFO frame__1_1_sim2c__std_identifier = {1, {"name"}};
static NODE *string__1_2;
static NODE *get__sim2c__std_identifier(void) {
  return var.sim2c__std_identifier;
}
static NODE *func__2_1_print_message;
static void entry__2_1_print_message(void);
static FRAME_INFO frame__2_1_print_message = {12, {"fragment", "offset", "msg_type", "msg", "source", "pos", "line_no", "line_offset", "n", "text", "rest", "line"}};
static void cont__2_2(void);
static void cont__2_3(void);
static void cont__2_4(void);
static void cont__2_5(void);
static void cont__2_6(void);
static void cont__2_7(void);
static void cont__2_8(void);
static void cont__2_9(void);
static void cont__2_10(void);
static void cont__2_11(void);
static void cont__2_12(void);
static NODE *func__2_13;
static void entry__2_13(void);
static FRAME_INFO frame__2_13 = {2, {"source", "line_offset"}};
static void cont__2_14(void);
static void cont__2_15(void);
static void cont__2_16(void);
static void cont__2_17(void);
static void cont__2_18(void);
static NODE *func__2_19;
static void entry__2_19(void);
static FRAME_INFO frame__2_19 = {2, {"n", "source"}};
static void cont__2_20(void);
static NODE *func__2_21;
static void entry__2_21(void);
static FRAME_INFO frame__2_21 = {2, {"source", "n"}};
static void cont__2_22(void);
static void cont__2_23(void);
static void cont__2_24(void);
static NODE *func__2_25;
static void entry__2_25(void);
static FRAME_INFO frame__2_25 = {1, {"n"}};
static void cont__2_26(void);
static void cont__2_27(void);
static void cont__2_28(void);
static void cont__2_29(void);
static NODE *func__2_30;
static void entry__2_30(void);
static FRAME_INFO frame__2_30 = {2, {"text", "line_offset"}};
static void cont__2_31(void);
static NODE *func__2_32;
static void entry__2_32(void);
static FRAME_INFO frame__2_32 = {1, {"text"}};
static void cont__2_33(void);
static void cont__2_34(void);
static void cont__2_35(void);
static NODE *string__2_36;
static void cont__2_37(void);
static void cont__2_38(void);
static NODE *func__2_39;
static void entry__2_39(void);
static FRAME_INFO frame__2_39 = {3, {"break", "line", "n"}};
static NODE *func__2_40;
static void entry__2_40(void);
static FRAME_INFO frame__2_40 = {3, {"chr", "break", "n"}};
static void cont__2_41(void);
static void cont__2_42(void);
static void cont__2_43(void);
static void cont__2_44(void);
static void cont__2_45(void);
static void cont__2_46(void);
static void cont__2_47(void);
static void cont__2_48(void);
static void cont__2_49(void);
static NODE *func__2_50;
static void entry__2_50(void);
static FRAME_INFO frame__2_50 = {3, {"line_no", "n", "msg"}};
static void cont__2_51(void);
static NODE *string__2_52;
static NODE *string__2_53;
static NODE *string__2_54;
static void cont__2_55(void);
static NODE *func__2_56;
static void entry__2_56(void);
static FRAME_INFO frame__2_56 = {5, {"msg_type", "line_no", "msg", "line", "n"}};
static NODE *string__2_57;
static NODE *string__2_58;
static NODE *string__2_59;
static NODE *string__2_60;
static NODE *string__2_61;
static void cont__2_62(void);
static void cont__2_63(void);
static void cont__2_64(void);
static NODE *string__2_65;
static void cont__2_66(void);
static NODE *string__2_67;
static NODE *func__3_1_sim2c__Warning;
static void entry__3_1_sim2c__Warning(void);
static FRAME_INFO frame__3_1_sim2c__Warning = {2, {"obj", "msg"}};
static void cont__3_2(void);
static void cont__3_3(void);
static NODE *string__3_4;
static NODE *get__sim2c__Warning(void) {
  return var.sim2c__Warning;
}
static NODE *func__4_1_ExitWithSyntaxError;
static void entry__4_1_ExitWithSyntaxError(void);
static FRAME_INFO frame__4_1_ExitWithSyntaxError = {3, {"fragment", "offset", "msg"}};
static NODE *string__4_2;
static void cont__4_3(void);
static NODE *func__5_1_sim2c__SyntaxError;
static void entry__5_1_sim2c__SyntaxError(void);
static FRAME_INFO frame__5_1_sim2c__SyntaxError = {2, {"obj", "msg"}};
static void cont__5_2(void);
static void cont__5_3(void);
static NODE *get__sim2c__SyntaxError(void) {
  return var.sim2c__SyntaxError;
}
static NODE *func__6_1_ParseError;
static void entry__6_1_ParseError(void);
static FRAME_INFO frame__6_1_ParseError = {2, {"stream", "msg"}};
static void cont__6_2(void);
static NODE *get__types__syntax_error(void) {
  return var.types__syntax_error;
}
static NODE *func__8_1_types__syntax_error_grammar__match;
static void entry__8_1_types__syntax_error_grammar__match(void);
static FRAME_INFO frame__8_1_types__syntax_error_grammar__match = {2, {"self", "stream"}};
static void cont__8_2(void);
static NODE *func__9_1_syntax_error;
static void entry__9_1_syntax_error(void);
static FRAME_INFO frame__9_1_syntax_error = {1, {"message"}};
static NODE *get__types__unexpected_input_error(void) {
  return var.types__unexpected_input_error;
}
static NODE *func__11_1_types__unexpected_input_error_grammar__match;
static void entry__11_1_types__unexpected_input_error_grammar__match(void);
static FRAME_INFO frame__11_1_types__unexpected_input_error_grammar__match = {3, {"self", "stream", "expression"}};
static void cont__11_2(void);
static void cont__11_3(void);
static NODE *func__11_4;
static void entry__11_4(void);
static FRAME_INFO frame__11_4 = {1, {"expression"}};
static void cont__11_5(void);
static void cont__11_6(void);
static NODE *func__11_7;
static void entry__11_7(void);
static FRAME_INFO frame__11_7 = {2, {"expression", "stream"}};
static NODE *func__11_8;
static void entry__11_8(void);
static FRAME_INFO frame__11_8 = {1, {"stream"}};
static NODE *string__11_9;
static NODE *func__11_10;
static void entry__11_10(void);
static FRAME_INFO frame__11_10 = {1, {"stream"}};
static NODE *string__11_11;
static NODE *func__11_12;
static void entry__11_12(void);
static FRAME_INFO frame__11_12 = {1, {"stream"}};
static NODE *string__11_13;
static NODE *func__11_14;
static void entry__11_14(void);
static FRAME_INFO frame__11_14 = {1, {"stream"}};
static NODE *string__11_15;
static NODE *func__11_16;
static void entry__11_16(void);
static FRAME_INFO frame__11_16 = {2, {"stream", "expression"}};
static NODE *string__11_17;
static NODE *string__11_18;
static void cont__11_19(void);
static NODE *func__11_20;
static void entry__11_20(void);
static FRAME_INFO frame__11_20 = {1, {"stream"}};
static NODE *string__11_21;
static NODE *func__12_1_unexpected_input_error;
static void entry__12_1_unexpected_input_error(void);
static FRAME_INFO frame__12_1_unexpected_input_error = {1, {"expression"}};
static NODE *get__types__print(void) {
  return var.types__print;
}
static NODE *func__14_1_types__print_grammar__match;
static void entry__14_1_types__print_grammar__match(void);
static FRAME_INFO frame__14_1_types__print_grammar__match = {2, {"self", "stream"}};
static void cont__14_2(void);
static void cont__14_3(void);
static NODE *func__15_1_print;
static void entry__15_1_print(void);
static FRAME_INFO frame__15_1_print = {1, {"message"}};
static NODE *func__17_1_dump_stream_grammar__match;
static void entry__17_1_dump_stream_grammar__match(void);
static FRAME_INFO frame__17_1_dump_stream_grammar__match = {2, {"self", "stream"}};
static NODE *string__17_2;
static void cont__17_3(void);
static void cont__17_4(void);
static void cont__17_5(void);
static NODE *string__17_6;
static void cont__17_7(void);
static NODE *func__18_1_sim2c__strip;
static void entry__18_1_sim2c__strip(void);
static FRAME_INFO frame__18_1_sim2c__strip = {1, {"node"}};
static void cont__18_2(void);
static void cont__18_3(void);
static NODE *func__18_4;
static void entry__18_4(void);
static FRAME_INFO frame__18_4 = {1, {"node"}};
static void cont__18_5(void);
static void cont__18_6(void);
static void cont__18_7(void);
static void cont__18_8(void);
static void cont__18_9(void);
static NODE *func__18_10;
static void entry__18_10(void);
static FRAME_INFO frame__18_10 = {1, {"node"}};
static void cont__18_11(void);
static void cont__18_12(void);
static void cont__18_13(void);
static void cont__18_14(void);
static void cont__18_15(void);
static NODE *func__18_16;
static void entry__18_16(void);
static FRAME_INFO frame__18_16 = {1, {"node"}};
static void cont__18_17(void);
static NODE *func__18_18;
static void entry__18_18(void);
static FRAME_INFO frame__18_18 = {1, {"statement"}};
static void cont__18_19(void);
static void cont__18_20(void);
static void cont__18_21(void);
static void cont__18_22(void);
static void cont__18_23(void);
static NODE *func__18_24;
static void entry__18_24(void);
static FRAME_INFO frame__18_24 = {1, {"node"}};
static void cont__18_25(void);
static NODE *func__18_26;
static void entry__18_26(void);
static FRAME_INFO frame__18_26 = {1, {"parameter"}};
static void cont__18_27(void);
static void cont__18_28(void);
static void cont__18_29(void);
static void cont__18_30(void);
static void cont__18_31(void);
static NODE *func__18_32;
static void entry__18_32(void);
static FRAME_INFO frame__18_32 = {1, {"node"}};
static void cont__18_33(void);
static NODE *func__18_34;
static void entry__18_34(void);
static FRAME_INFO frame__18_34 = {1, {"argument"}};
static void cont__18_35(void);
static void cont__18_36(void);
static void cont__18_37(void);
static void cont__18_38(void);
static void cont__18_39(void);
static NODE *func__18_40;
static void entry__18_40(void);
static FRAME_INFO frame__18_40 = {1, {"node"}};
static void cont__18_41(void);
static NODE *func__18_42;
static void entry__18_42(void);
static FRAME_INFO frame__18_42 = {1, {"argument"}};
static void cont__18_43(void);
static void cont__18_44(void);
static void cont__18_45(void);
static void cont__18_46(void);
static void cont__18_47(void);
static NODE *func__18_48;
static void entry__18_48(void);
static FRAME_INFO frame__18_48 = {1, {"node"}};
static void cont__18_49(void);
static void cont__18_50(void);
static void cont__18_51(void);
static void cont__18_52(void);
static void cont__18_53(void);
static NODE *func__18_54;
static void entry__18_54(void);
static FRAME_INFO frame__18_54 = {1, {"node"}};
static void cont__18_55(void);
static void cont__18_56(void);
static void cont__18_57(void);
static NODE *get__sim2c__strip(void) {
  return var.sim2c__strip;
}
static NODE *func__20_1_dump_grammar__match;
static void entry__20_1_dump_grammar__match(void);
static FRAME_INFO frame__20_1_dump_grammar__match = {2, {"self", "stream"}};
static void cont__20_2(void);
static NODE *string__20_3;
static void cont__20_4(void);
static NODE *func__22_1_dump3_grammar__match;
static void entry__22_1_dump3_grammar__match(void);
static FRAME_INFO frame__22_1_dump3_grammar__match = {2, {"self", "stream"}};
static void cont__22_2(void);
static void cont__22_3(void);
static NODE *func__24_1_dump5_grammar__match;
static void entry__24_1_dump5_grammar__match(void);
static FRAME_INFO frame__24_1_dump5_grammar__match = {2, {"self", "stream"}};
static void cont__24_2(void);
static void cont__24_3(void);
static NODE *get__sim2c__HIGHEST_PRECEDENCE(void) {
  return var.sim2c__HIGHEST_PRECEDENCE;
}
static NODE *get__sim2c__INFIX_PRECEDENCE(void) {
  return var.sim2c__INFIX_PRECEDENCE;
}
static NODE *func__28_1_sim2c__precedence;
static void entry__28_1_sim2c__precedence(void);
static FRAME_INFO frame__28_1_sim2c__precedence = {1, {"op"}};
static void cont__28_2(void);
static NODE *func__28_3;
static void entry__28_3(void);
static FRAME_INFO frame__28_3 = {1, {"op"}};
static void cont__28_4(void);
static NODE *func__28_5;
static void entry__28_5(void);
static FRAME_INFO frame__28_5 = {0, {}};
static NODE *get__sim2c__precedence(void) {
  return var.sim2c__precedence;
}
static NODE *func__29_1_sim2c__is_left_associative;
static void entry__29_1_sim2c__is_left_associative(void);
static FRAME_INFO frame__29_1_sim2c__is_left_associative = {1, {"prec"}};
static void cont__29_2(void);
static NODE *get__sim2c__is_left_associative(void) {
  return var.sim2c__is_left_associative;
}
static NODE *func__30_1_is_right_associative;
static void entry__30_1_is_right_associative(void);
static FRAME_INFO frame__30_1_is_right_associative = {1, {"prec"}};
static void cont__30_2(void);
static void cont__30_3(void);
static NODE *func__31_1_infix_operator;
static void entry__31_1_infix_operator(void);
static FRAME_INFO frame__31_1_infix_operator = {1, {"operator"}};
static void cont__31_2(void);
static void cont__31_3(void);
static NODE *func__32_1_interleaved;
static void entry__32_1_interleaved(void);
static FRAME_INFO frame__32_1_interleaved = {2, {"expression", "separator"}};
static void cont__32_2(void);
static void cont__32_3(void);
static void cont__32_4(void);
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
static NODE *func__35_1_types__inline_grammar__match;
static void entry__35_1_types__inline_grammar__match(void);
static FRAME_INFO frame__35_1_types__inline_grammar__match = {3, {"self", "stream", "return__1"}};
static void cont__35_2(void);
static void cont__35_3(void);
static NODE *func__36_1_inline;
static void entry__36_1_inline(void);
static FRAME_INFO frame__36_1_inline = {1, {"expression"}};
static NODE *func__42_1_expect;
static void entry__42_1_expect(void);
static FRAME_INFO frame__42_1_expect = {2, {"expression", "description"}};
static void cont__42_2(void);
static NODE *func__42_3;
static void entry__42_3(void);
static FRAME_INFO frame__42_3 = {2, {"expression", "description"}};
static NODE *string__42_4;
static void cont__42_5(void);
static void cont__42_6(void);
static void cont__42_7(void);
static NODE *func__42_8;
static void entry__42_8(void);
static FRAME_INFO frame__42_8 = {1, {"expression"}};
static void cont__42_9(void);
static void cont__42_10(void);
static NODE *func__45_1_sim2c__arguments_span;
static void entry__45_1_sim2c__arguments_span(void);
static FRAME_INFO frame__45_1_sim2c__arguments_span = {1, {"expression"}};
static void cont__45_2(void);
static void cont__45_3(void);
static NODE *get__sim2c__arguments_span(void) {
  return var.sim2c__arguments_span;
}
static NODE *func__46_1_sim2c__output_arguments_span;
static void entry__46_1_sim2c__output_arguments_span(void);
static FRAME_INFO frame__46_1_sim2c__output_arguments_span = {1, {"expression"}};
static void cont__46_2(void);
static void cont__46_3(void);
static NODE *get__sim2c__output_arguments_span(void) {
  return var.sim2c__output_arguments_span;
}
static NODE *get__sim2c__WHITESPACE(void) {
  return var.sim2c__WHITESPACE;
}
static int poly_idx__original_remark_lines_of;
static void type__original_remark_lines_of(void);
static NODE *func__208_1_sim2c__parse_meta_instruction;
static void entry__208_1_sim2c__parse_meta_instruction(void);
static FRAME_INFO frame__208_1_sim2c__parse_meta_instruction = {5, {"fragment", "return__1", "source", "len", "cap"}};
static void cont__208_2(void);
static void cont__208_3(void);
static void cont__208_4(void);
static void cont__208_5(void);
static void cont__208_6(void);
static NODE *func__208_7;
static void entry__208_7(void);
static FRAME_INFO frame__208_7 = {1, {"source"}};
static NODE *string__208_8;
static void cont__208_9(void);
static NODE *get__sim2c__parse_meta_instruction(void) {
  return var.sim2c__parse_meta_instruction;
}
static NODE *func__209_1_sim2c__parse_statement;
static void entry__209_1_sim2c__parse_statement(void);
static FRAME_INFO frame__209_1_sim2c__parse_statement = {5, {"fragment", "return__1", "source", "len", "cap"}};
static void cont__209_2(void);
static void cont__209_3(void);
static void cont__209_4(void);
static NODE *func__209_5;
static void entry__209_5(void);
static FRAME_INFO frame__209_5 = {2, {"len", "source"}};
static void cont__209_6(void);
static void cont__209_7(void);
static void cont__209_8(void);
static NODE *func__209_9;
static void entry__209_9(void);
static FRAME_INFO frame__209_9 = {1, {"source"}};
static NODE *string__209_10;
static NODE *func__209_11;
static void entry__209_11(void);
static FRAME_INFO frame__209_11 = {1, {"source"}};
static NODE *string__209_12;
static void cont__209_13(void);
static void cont__209_14(void);
static NODE *string__209_15;
static void cont__209_16(void);
static void cont__209_17(void);
static NODE *get__sim2c__parse_statement(void) {
  return var.sim2c__parse_statement;
}
static NODE *string__236_1;
static void cont__236_2(void);
static NODE *string__236_3;
static void cont__236_4(void);
static NODE *string__236_5;
static void cont__236_6(void);
static NODE *string__236_7;
static void cont__236_8(void);
static NODE *string__236_9;
static void cont__236_10(void);
static NODE *string__236_11;
static void cont__236_12(void);
static NODE *string__236_13;
static void cont__236_14(void);
static void cont__236_15(void);
static NODE *string__236_16;
static void cont__236_17(void);
static NODE *string__236_18;
static void cont__236_19(void);
static NODE *string__236_20;
static void cont__236_21(void);
static NODE *string__236_22;
static void cont__236_23(void);
static NODE *string__236_24;
static void cont__236_25(void);
static NODE *string__236_26;
static void cont__236_27(void);
static NODE *string__236_28;
static void cont__236_29(void);
static NODE *string__236_30;
static void cont__236_31(void);
static NODE *string__236_32;
static void cont__236_33(void);
static NODE *string__236_34;
static void cont__236_35(void);
static NODE *string__236_36;
static void cont__236_37(void);
static NODE *string__236_38;
static void cont__236_39(void);
static void cont__236_40(void);
static NODE *func__246_1;
static void entry__246_1(void);
static FRAME_INFO frame__246_1 = {2, {"node", "stream"}};
static NODE *func__246_2;
static void entry__246_2(void);
static FRAME_INFO frame__246_2 = {1, {"stream"}};
static NODE *string__246_3;
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
static NODE *string__264_7;
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
static NODE *string__265_7;
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
static NODE *string__267_1;
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
static NODE *string__268_8;
static NODE *string__268_9;
static void cont__268_10(void);
static void cont__268_11(void);
static void cont__268_12(void);
static void cont__268_13(void);
static NODE *string__268_14;
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
static NODE *func__269_13;
static void entry__269_13(void);
static FRAME_INFO frame__269_13 = {2, {"stream", "namespace"}};
static NODE *string__269_14;
static NODE *string__269_15;
static void cont__269_16(void);
static void cont__269_17(void);
static void cont__269_18(void);
static void cont__269_19(void);
static void cont__269_20(void);
static NODE *func__269_21;
static void entry__269_21(void);
static FRAME_INFO frame__269_21 = {3, {"alias", "stream", "namespace"}};
static void cont__269_22(void);
static void cont__269_23(void);
static NODE *func__269_24;
static void entry__269_24(void);
static FRAME_INFO frame__269_24 = {2, {"stream", "alias"}};
static NODE *string__269_25;
static void cont__269_26(void);
static void cont__269_27(void);
static void cont__269_28(void);
static void cont__269_29(void);
static NODE *string__269_30;
static void cont__269_31(void);
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
static NODE *string__270_7;
static void cont__270_8(void);
static void cont__270_9(void);
static void cont__270_10(void);
static void cont__270_11(void);
static NODE *string__270_12;
static void cont__270_13(void);
static void cont__271_1(void);
static void cont__271_2(void);
static NODE *string__272_1;
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
static NODE *string__273_7;
static NODE *string__273_8;
static void cont__273_9(void);
static void cont__273_10(void);
static void cont__273_11(void);
static void cont__273_12(void);
static NODE *string__273_13;
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
static NODE *string__274_7;
static NODE *string__274_8;
static void cont__274_9(void);
static void cont__274_10(void);
static void cont__274_11(void);
static void cont__274_12(void);
static NODE *string__274_13;
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
static NODE *string__277_7;
static void cont__277_8(void);
static void cont__277_9(void);
static void cont__277_10(void);
static void cont__277_11(void);
static NODE *string__277_12;
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
static NODE *string__300_3;
static void cont__300_4(void);
static void cont__301_1(void);
static void cont__302_1(void);
static void cont__302_2(void);
static NODE *string__302_3;
static void cont__302_4(void);
static void cont__303_1(void);
static void cont__303_2(void);
static void cont__303_3(void);
static void cont__304_1(void);
static void cont__304_2(void);
static NODE *string__304_3;
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
static NODE *string__308_7;
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
static NODE *string__310_1;
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
static NODE *string__313_7;
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
static NODE *string__314_13;
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
static NODE *string__315_13;
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
static NODE *string__321_1;
static void cont__321_2(void);
static void cont__321_3(void);
static void cont__321_4(void);
static void cont__321_5(void);
static void cont__321_6(void);
static NODE *func__322_1;
static void entry__322_1(void);
static FRAME_INFO frame__322_1 = {1, {"node"}};
static NODE *string__322_2;
static void cont__322_3(void);
static NODE *string__322_4;
static void cont__322_5(void);
static void cont__322_6(void);
static void cont__322_7(void);
static void cont__322_8(void);
static void cont__322_9(void);
static void cont__322_10(void);
static NODE *string__322_11;
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
static NODE *func__331_9_update_stack;
static void entry__331_9_update_stack(void);
static FRAME_INFO frame__331_9_update_stack = {5, {"right", "next_operator", "operator_stack", "operand_stack", "next_prec"}};
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
static NODE *string__333_2;
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
static NODE *string__337_2;
static void cont__337_3(void);
static void cont__338_1(void);
static void cont__338_2(void);
static void cont__339_1(void);
static NODE *string__339_2;
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
static NODE *string__364_13;
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
static NODE *string__376_3;
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
static NODE *string__380_12;
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
static NODE *string__386_2;
static void cont__386_3(void);
static void cont__387_1(void);
static NODE *string__387_2;
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
static NODE *string__389_11;
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
static NODE *string__391_2;
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
static NODE *string__397_6;
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
static NODE *string__399_2;
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
static NODE *string__401_4;
static void cont__401_5(void);
static void cont__402_1(void);
static void cont__402_2(void);
static void cont__402_3(void);
static NODE *string__402_4;
static void cont__402_5(void);
static void cont__403_1(void);
static void cont__403_2(void);
static void cont__403_3(void);
static NODE *string__403_4;
static void cont__403_5(void);
static void cont__404_1(void);
static void cont__404_2(void);
static void cont__404_3(void);
static NODE *string__404_4;
static void cont__404_5(void);
static void cont__405_1(void);
static void cont__405_2(void);
static void cont__405_3(void);
static NODE *string__405_4;
static void cont__405_5(void);
static NODE *string__406_1;
static NODE *string__406_2;
static NODE *string__406_3;
static NODE *string__406_4;
static void cont__406_5(void);
static void cont__406_6(void);
static void cont__406_7(void);
static void cont__406_8(void);
static NODE *string__406_9;
static void cont__406_10(void);
static void cont__407_1(void);
static void cont__407_2(void);
static void cont__407_3(void);
static NODE *string__407_4;
static void cont__407_5(void);
static NODE *string__408_1;
static void cont__408_2(void);
static void cont__408_3(void);
static void cont__409_1(void);
static void cont__409_2(void);
static void cont__410_1(void);
static NODE *string__411_1;
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
static NODE *string__416_1;
static void cont__416_2(void);
static void cont__416_3(void);
static void cont__416_4(void);
static void cont__416_5(void);
static void cont__416_6(void);
void run__parser(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__original_remark_lines_of, NULL, 1150, 1150, 2, 25},
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
  {cont__269_9, NULL, 409, 421, 5, 47},
  {cont__269_29, NULL, 395, 421, 1, 50},
  {cont__269_31, NULL, 427, 427, 5, 31},
  {cont__270_1, NULL, 428, 428, 5, 30},
  {cont__270_2, NULL, 430, 436, 5, 40},
  {cont__270_11, NULL, 423, 436, 1, 43},
  {cont__270_13, NULL, 438, 438, 16, 40},
  {cont__271_1, NULL, 438, 438, 1, 41},
  {cont__271_2, NULL, 439, 439, 26, 36},
  {cont__272_2, NULL, 439, 439, 13, 37},
  {cont__272_3, NULL, 439, 439, 55, 67},
  {cont__272_4, NULL, 439, 439, 50, 68},
  {cont__272_5, NULL, 439, 439, 1, 68},
  {cont__272_6, NULL, 445, 445, 5, 33},
  {cont__273_1, NULL, 446, 446, 5, 41},
  {cont__273_2, NULL, 448, 454, 5, 38},
  {cont__273_12, NULL, 441, 454, 1, 41},
  {cont__273_14, NULL, 460, 460, 5, 30},
  {cont__274_1, NULL, 461, 461, 5, 41},
  {cont__274_2, NULL, 463, 469, 5, 40},
  {cont__274_12, NULL, 456, 469, 1, 43},
  {cont__274_14, NULL, 471, 471, 12, 44},
  {cont__275_1, NULL, 471, 471, 1, 45},
  {cont__275_2, NULL, 472, 472, 24, 34},
  {cont__276_1, NULL, 472, 472, 11, 35},
  {cont__276_2, NULL, 472, 472, 49, 57},
  {cont__276_3, NULL, 472, 472, 44, 58},
  {cont__276_4, NULL, 472, 472, 1, 58},
  {cont__276_5, NULL, 478, 478, 5, 30},
  {cont__277_1, NULL, 479, 479, 5, 39},
  {cont__277_2, NULL, 481, 487, 5, 38},
  {cont__277_11, NULL, 474, 487, 1, 41},
  {cont__277_13, NULL, 491, 491, 5, 50},
  {cont__278_1, NULL, 492, 492, 56, 77},
  {cont__278_2, NULL, 492, 492, 38, 77},
  {cont__278_3, NULL, 492, 492, 14, 78},
  {cont__278_4, NULL, 492, 492, 5, 79},
  {cont__278_5, NULL, 489, 492, 1, 80},
  {cont__278_6, NULL, 497, 497, 44, 68},
  {cont__279_1, NULL, 497, 497, 1, 69},
  {cont__279_2, NULL, 502, 502, 22, 53},
  {cont__280_1, NULL, 502, 502, 56, 77},
  {cont__280_2, NULL, 502, 502, 14, 77},
  {cont__280_3, NULL, 502, 502, 5, 78},
  {cont__280_4, NULL, 499, 502, 1, 79},
  {cont__280_5, NULL, 504, 504, 35, 60},
  {cont__281_1, NULL, 504, 504, 1, 74},
  {cont__281_2, NULL, 506, 506, 1, 67},
  {cont__282_1, NULL, 507, 507, 1, 29},
  {cont__283_1, NULL, 512, 521, 5, 43},
  {cont__284_23, NULL, 509, 521, 1, 46},
  {cont__284_24, NULL, 523, 523, 27, 65},
  {cont__285_1, NULL, 523, 523, 1, 66},
  {cont__285_2, NULL, 531, 539, 7, 48},
  {cont__286_22, NULL, 527, 539, 5, 49},
  {cont__286_23, NULL, 525, 539, 1, 52},
  {cont__286_24, NULL, 545, 551, 5, 46},
  {cont__287_22, NULL, 541, 551, 1, 49},
  {cont__287_23, NULL, 553, 553, 1, 60},
  {cont__288_1, NULL, 554, 554, 1, 32},
  {cont__289_1, NULL, 562, 568, 5, 58},
  {cont__290_4, NULL, 569, 569, 21, 63},
  {cont__290_5, NULL, 569, 569, 12, 64},
  {cont__290_6, NULL, 569, 569, 5, 65},
  {cont__290_7, NULL, 570, 570, 5, 15},
  {cont__290_8, NULL, 559, 571, 1, 23},
  {cont__290_9, NULL, 573, 581, 1, 58},
  {cont__291_5, NULL, 587, 587, 5, 31},
  {cont__292_1, NULL, 583, 588, 1, 23},
  {cont__292_2, NULL, 594, 594, 5, 40},
  {cont__293_1, NULL, 590, 595, 1, 23},
  {cont__293_2, NULL, 597, 597, 18, 52},
  {cont__294_1, NULL, 597, 597, 1, 53},
  {cont__294_2, NULL, 598, 598, 29, 62},
  {cont__295_1, NULL, 598, 598, 1, 63},
  {cont__295_2, NULL, 599, 599, 1, 51},
  {cont__296_1, NULL, 602, 602, 15, 46},
  {cont__297_1, NULL, 601, 602, 1, 69},
  {cont__297_2, NULL, 606, 606, 17, 27},
  {cont__298_1, NULL, 606, 606, 5, 37},
  {cont__298_2, NULL, 607, 607, 19, 29},
  {cont__298_3, NULL, 607, 607, 14, 29},
  {cont__298_4, NULL, 607, 607, 5, 30},
  {cont__298_5, NULL, 608, 608, 14, 25},
  {cont__298_6, NULL, 608, 608, 37, 48},
  {cont__298_7, NULL, 608, 608, 28, 49},
  {cont__298_8, NULL, 608, 608, 52, 62},
  {cont__298_9, NULL, 608, 608, 14, 62},
  {cont__298_10, NULL, 608, 608, 5, 63},
  {cont__298_11, NULL, 604, 608, 1, 64},
  {cont__298_12, NULL, 610, 610, 1, 26},
  {cont__299_1, NULL, 611, 611, 34, 51},
  {cont__300_1, NULL, 611, 611, 22, 61},
  {cont__300_2, NULL, 611, 611, 1, 61},
  {cont__300_4, NULL, 612, 612, 1, 23},
  {cont__301_1, NULL, 613, 613, 33, 49},
  {cont__302_1, NULL, 613, 613, 21, 59},
  {cont__302_2, NULL, 613, 613, 1, 59},
  {cont__302_4, NULL, 614, 614, 22, 31},
  {cont__303_1, NULL, 614, 614, 33, 42},
  {cont__303_2, NULL, 614, 614, 1, 43},
  {cont__303_3, NULL, 615, 615, 31, 45},
  {cont__304_1, NULL, 615, 615, 19, 55},
  {cont__304_2, NULL, 615, 615, 1, 55},
  {cont__304_4, NULL, 619, 619, 5, 29},
  {cont__305_1, NULL, 623, 623, 7, 63},
  {cont__305_2, NULL, 621, 623, 5, 62},
  {cont__305_3, NULL, 617, 624, 1, 23},
  {cont__305_4, NULL, 628, 628, 5, 47},
  {cont__306_1, NULL, 629, 631, 5, 52},
  {cont__306_5, NULL, 626, 631, 1, 55},
  {cont__306_6, NULL, 636, 638, 5, 33},
  {cont__307_2, NULL, 633, 638, 1, 36},
  {cont__307_3, NULL, 642, 642, 5, 32},
  {cont__308_1, NULL, 644, 652, 5, 32},
  {cont__308_9, NULL, 640, 652, 1, 35},
  {cont__308_10, NULL, 659, 659, 15, 32},
  {cont__309_1, NULL, 659, 659, 9, 32},
  {cont__309_2, NULL, 660, 660, 15, 31},
  {cont__309_3, NULL, 660, 660, 9, 31},
  {cont__309_4, NULL, 661, 661, 15, 29},
  {cont__309_5, NULL, 661, 661, 9, 29},
  {cont__309_6, NULL, 662, 662, 9, 19},
  {cont__309_7, NULL, 658, 662, 7, 18},
  {cont__309_8, NULL, 656, 662, 5, 19},
  {cont__309_9, NULL, 664, 666, 5, 71},
  {cont__309_14, NULL, 654, 666, 1, 74},
  {cont__309_15, NULL, 673, 673, 5, 45},
  {cont__310_2, NULL, 668, 673, 1, 46},
  {cont__310_3, NULL, 675, 675, 23, 45},
  {cont__311_1, NULL, 675, 675, 1, 63},
  {cont__311_2, NULL, 680, 680, 5, 31},
  {cont__312_1, NULL, 683, 683, 5, 20},
  {cont__312_2, NULL, 677, 684, 1, 23},
  {cont__312_3, NULL, 691, 693, 7, 55},
  {cont__313_5, NULL, 689, 693, 5, 56},
  {cont__313_6, NULL, 686, 693, 1, 59},
  {cont__313_8, NULL, 698, 702, 5, 30},
  {cont__314_9, NULL, 703, 703, 17, 42},
  {cont__314_10, NULL, 703, 703, 5, 61},
  {cont__314_11, NULL, 704, 704, 5, 15},
  {cont__314_12, NULL, 695, 704, 1, 16},
  {cont__314_14, NULL, 706, 719, 1, 55},
  {cont__315_20, NULL, 726, 726, 5, 34},
  {cont__316_1, NULL, 727, 727, 5, 28},
  {cont__316_2, NULL, 729, 729, 10, 34},
  {cont__316_3, NULL, 729, 729, 37, 74},
  {cont__316_4, NULL, 729, 729, 10, 74},
  {cont__316_5, NULL, 729, 729, 5, 75},
  {cont__316_6, NULL, 730, 730, 5, 20},
  {cont__316_7, NULL, 721, 732, 1, 21},
  {cont__316_8, NULL, 737, 737, 19, 31},
  {cont__317_1, NULL, 737, 737, 7, 32},
  {cont__317_2, NULL, 738, 738, 7, 32},
  {cont__317_3, NULL, 739, 739, 7, 35},
  {cont__317_4, NULL, 740, 740, 7, 35},
  {cont__317_5, NULL, 736, 740, 5, 34},
  {cont__317_6, NULL, 734, 740, 1, 37},
  {cont__317_7, NULL, 742, 745, 1, 62},
  {cont__318_5, NULL, 750, 750, 5, 31},
  {cont__319_1, NULL, 754, 754, 10, 43},
  {cont__319_2, NULL, 754, 754, 5, 44},
  {cont__319_3, NULL, 755, 755, 9, 21},
  {cont__319_4, NULL, 755, 755, 23, 44},
  {cont__319_5, NULL, 755, 755, 23, 58},
  {cont__319_6, NULL, 755, 755, 5, 59},
  {cont__319_7, NULL, 747, 757, 1, 21},
  {cont__319_8, NULL, 759, 759, 19, 41},
  {cont__320_1, NULL, 759, 759, 44, 64},
  {cont__320_2, NULL, 759, 759, 1, 64},
  {cont__320_3, NULL, 764, 764, 32, 66},
  {cont__321_2, NULL, 764, 764, 12, 67},
  {cont__321_3, NULL, 764, 764, 5, 68},
  {cont__321_4, NULL, 765, 765, 5, 15},
  {cont__321_5, NULL, 761, 765, 1, 16},
  {cont__321_6, NULL, 771, 778, 5, 60},
  {cont__322_10, NULL, 767, 779, 1, 23},
  {cont__322_12, NULL, 786, 793, 5, 58},
  {cont__323_5, NULL, 781, 794, 1, 23},
  {cont__323_6, NULL, 796, 804, 1, 13},
  {cont__324_1, NULL, 806, 806, 58, 79},
  {cont__325_1, NULL, 806, 806, 42, 79},
  {cont__325_2, NULL, 806, 806, 1, 80},
  {cont__325_3, NULL, 808, 828, 1, 9},
  {cont__326_1, NULL, 831, 831, 18, 66},
  {cont__327_1, NULL, 830, 831, 1, 67},
  {cont__327_2, NULL, 833, 833, 17, 47},
  {cont__328_1, NULL, 833, 833, 1, 66},
  {cont__328_2, NULL, 839, 839, 5, 39},
  {cont__329_1, NULL, 841, 841, 5, 29},
  {cont__329_2, NULL, 835, 841, 1, 30},
  {cont__329_3, NULL, 845, 845, 5, 56},
  {cont__330_1, NULL, 846, 855, 5, 60},
  {cont__330_14, NULL, 843, 855, 1, 63},
  {cont__330_15, NULL, 857, 907, 1, 70},
  {cont__331_63, NULL, 911, 911, 5, 24},
  {cont__332_1, NULL, 912, 912, 5, 27},
  {cont__332_2, NULL, 913, 913, 26, 48},
  {cont__332_3, NULL, 913, 913, 10, 48},
  {cont__332_4, NULL, 913, 913, 5, 49},
  {cont__332_5, NULL, 915, 915, 22, 52},
  {cont__332_6, NULL, 915, 915, 7, 53},
  {cont__332_7, NULL, 915, 915, 7, 74},
  {cont__332_8, NULL, 914, 915, 5, 73},
  {cont__332_9, NULL, 909, 916, 1, 22},
  {cont__332_10, NULL, 918, 918, 26, 62},
  {cont__333_1, NULL, 918, 918, 1, 76},
  {cont__333_3, NULL, 921, 921, 15, 63},
  {cont__334_1, NULL, 920, 921, 1, 63},
  {cont__334_2, NULL, 931, 931, 13, 55},
  {cont__335_1, NULL, 932, 932, 13, 50},
  {cont__335_2, NULL, 929, 932, 11, 49},
  {cont__335_3, NULL, 935, 935, 13, 28},
  {cont__335_4, NULL, 936, 936, 13, 52},
  {cont__335_5, NULL, 933, 936, 11, 51},
  {cont__335_6, NULL, 939, 939, 13, 52},
  {cont__335_7, NULL, 940, 940, 13, 50},
  {cont__335_8, NULL, 937, 940, 11, 49},
  {cont__335_9, NULL, 928, 940, 9, 50},
  {cont__335_10, NULL, 927, 940, 7, 51},
  {cont__335_11, NULL, 926, 940, 5, 52},
  {cont__335_12, NULL, 923, 940, 1, 55},
  {cont__335_13, NULL, 943, 943, 8, 37},
  {cont__336_1, NULL, 942, 943, 1, 68},
  {cont__336_2, NULL, 945, 945, 28, 56},
  {cont__337_1, NULL, 945, 945, 1, 74},
  {cont__337_3, NULL, 946, 946, 29, 59},
  {cont__338_1, NULL, 946, 946, 1, 77},
  {cont__338_2, NULL, 947, 947, 29, 58},
  {cont__339_1, NULL, 947, 947, 1, 76},
  {cont__339_3, NULL, 952, 960, 5, 58},
  {cont__340_5, NULL, 961, 961, 9, 24},
  {cont__340_6, NULL, 961, 961, 26, 61},
  {cont__340_7, NULL, 961, 961, 5, 62},
  {cont__340_8, NULL, 949, 962, 1, 23},
  {cont__340_9, NULL, 964, 964, 54, 80},
  {cont__341_1, NULL, 964, 964, 1, 80},
  {cont__341_2, NULL, 966, 972, 1, 11},
  {cont__342_1, NULL, 977, 977, 5, 24},
  {cont__343_1, NULL, 978, 978, 46, 69},
  {cont__343_2, NULL, 978, 978, 27, 70},
  {cont__343_3, NULL, 978, 978, 5, 71},
  {cont__343_4, NULL, 974, 978, 1, 72},
  {cont__343_5, NULL, 980, 980, 32, 51},
  {cont__344_1, NULL, 980, 980, 1, 52},
  {cont__344_2, NULL, 984, 984, 10, 44},
  {cont__345_1, NULL, 984, 984, 5, 44},
  {cont__345_2, NULL, 985, 985, 10, 44},
  {cont__345_3, NULL, 985, 985, 5, 44},
  {cont__345_4, NULL, 982, 985, 1, 45},
  {cont__345_5, NULL, 987, 987, 53, 71},
  {cont__346_1, NULL, 987, 987, 40, 71},
  {cont__346_2, NULL, 987, 987, 1, 72},
  {cont__346_3, NULL, 991, 991, 50, 68},
  {cont__347_1, NULL, 991, 991, 5, 68},
  {cont__347_2, NULL, 989, 991, 1, 69},
  {cont__347_3, NULL, 993, 1001, 1, 65},
  {cont__348_7, NULL, 1003, 1018, 1, 68},
  {cont__349_18, NULL, 1022, 1022, 32, 50},
  {cont__350_1, NULL, 1022, 1022, 20, 50},
  {cont__350_2, NULL, 1022, 1022, 5, 51},
  {cont__350_3, NULL, 1024, 1024, 5, 38},
  {cont__350_4, NULL, 1025, 1025, 5, 30},
  {cont__350_5, NULL, 1025, 1025, 5, 49},
  {cont__350_6, NULL, 1020, 1025, 1, 50},
  {cont__350_7, NULL, 1033, 1033, 11, 40},
  {cont__351_1, NULL, 1034, 1034, 11, 49},
  {cont__351_2, NULL, 1032, 1036, 9, 23},
  {cont__351_3, NULL, 1031, 1036, 7, 24},
  {cont__351_4, NULL, 1029, 1036, 5, 25},
  {cont__351_5, NULL, 1039, 1039, 7, 22},
  {cont__351_6, NULL, 1041, 1041, 9, 41},
  {cont__351_7, NULL, 1041, 1041, 9, 68},
  {cont__351_8, NULL, 1040, 1041, 7, 67},
  {cont__351_9, NULL, 1037, 1041, 5, 68},
  {cont__351_10, NULL, 1046, 1046, 11, 43},
  {cont__351_11, NULL, 1047, 1047, 11, 49},
  {cont__351_12, NULL, 1045, 1049, 9, 23},
  {cont__351_13, NULL, 1044, 1049, 7, 24},
  {cont__351_14, NULL, 1042, 1049, 5, 25},
  {cont__351_15, NULL, 1027, 1049, 1, 28},
  {cont__351_16, NULL, 1053, 1053, 10, 32},
  {cont__352_1, NULL, 1053, 1053, 5, 33},
  {cont__352_2, NULL, 1059, 1059, 13, 42},
  {cont__352_3, NULL, 1060, 1060, 13, 51},
  {cont__352_4, NULL, 1058, 1061, 11, 32},
  {cont__352_5, NULL, 1057, 1061, 9, 33},
  {cont__352_6, NULL, 1055, 1061, 7, 34},
  {cont__352_7, NULL, 1064, 1064, 9, 24},
  {cont__352_8, NULL, 1065, 1065, 24, 56},
  {cont__352_9, NULL, 1065, 1065, 24, 79},
  {cont__352_10, NULL, 1065, 1065, 9, 80},
  {cont__352_11, NULL, 1062, 1065, 7, 79},
  {cont__352_12, NULL, 1070, 1070, 13, 45},
  {cont__352_13, NULL, 1071, 1071, 13, 51},
  {cont__352_14, NULL, 1069, 1072, 11, 32},
  {cont__352_15, NULL, 1068, 1072, 9, 33},
  {cont__352_16, NULL, 1066, 1072, 7, 34},
  {cont__352_17, NULL, 1054, 1072, 5, 35},
  {cont__352_18, NULL, 1051, 1072, 1, 38},
  {cont__352_19, NULL, 1074, 1075, 1, 60},
  {cont__353_1, NULL, 1078, 1078, 11, 53},
  {cont__354_1, NULL, 1078, 1078, 56, 77},
  {cont__354_2, NULL, 1077, 1078, 1, 77},
  {cont__354_3, NULL, 1081, 1081, 7, 51},
  {cont__355_1, NULL, 1080, 1081, 1, 72},
  {cont__355_2, NULL, 1088, 1088, 33, 68},
  {cont__356_1, NULL, 1088, 1088, 9, 69},
  {cont__356_2, NULL, 1086, 1088, 7, 68},
  {cont__356_3, NULL, 1094, 1094, 13, 25},
  {cont__356_4, NULL, 1096, 1096, 13, 34},
  {cont__356_5, NULL, 1092, 1096, 11, 33},
  {cont__356_6, NULL, 1091, 1096, 9, 34},
  {cont__356_7, NULL, 1089, 1096, 7, 35},
  {cont__356_8, NULL, 1085, 1096, 5, 36},
  {cont__356_9, NULL, 1083, 1096, 1, 39},
  {cont__356_10, NULL, 1102, 1102, 16, 41},
  {cont__357_1, NULL, 1102, 1102, 7, 42},
  {cont__357_2, NULL, 1103, 1103, 16, 50},
  {cont__357_3, NULL, 1103, 1103, 7, 51},
  {cont__357_4, NULL, 1100, 1103, 5, 50},
  {cont__357_5, NULL, 1106, 1106, 11, 30},
  {cont__357_6, NULL, 1106, 1106, 41, 75},
  {cont__357_7, NULL, 1106, 1106, 32, 76},
  {cont__357_8, NULL, 1106, 1106, 7, 77},
  {cont__357_9, NULL, 1104, 1106, 5, 76},
  {cont__357_10, NULL, 1107, 1107, 39, 73},
  {cont__357_11, NULL, 1107, 1107, 30, 74},
  {cont__357_12, NULL, 1107, 1107, 5, 75},
  {cont__357_13, NULL, 1098, 1107, 1, 76},
  {cont__357_14, NULL, 1111, 1111, 29, 51},
  {cont__358_1, NULL, 1111, 1111, 5, 75},
  {cont__358_2, NULL, 1109, 1112, 1, 22},
  {cont__358_3, NULL, 1118, 1120, 5, 41},
  {cont__359_2, NULL, 1121, 1121, 30, 72},
  {cont__359_3, NULL, 1121, 1121, 5, 73},
  {cont__359_4, NULL, 1123, 1123, 5, 26},
  {cont__359_5, NULL, 1124, 1148, 5, 54},
  {cont__359_21, NULL, 1114, 1148, 1, 57},
  {cont__359_22, NULL, 1156, 1159, 7, 42},
  {cont__361_3, NULL, 1161, 1168, 7, 50},
  {cont__361_19, NULL, 1169, 1169, 11, 61},
  {cont__361_20, NULL, 1169, 1169, 7, 70},
  {cont__361_21, NULL, 1154, 1169, 5, 69},
  {cont__361_22, NULL, 1152, 1170, 1, 29},
  {cont__361_23, NULL, 1173, 1173, 11, 23},
  {cont__362_1, NULL, 1172, 1173, 1, 57},
  {cont__362_2, NULL, 1176, 1176, 28, 77},
  {cont__363_1, NULL, 1176, 1176, 16, 78},
  {cont__363_2, NULL, 1176, 1176, 11, 78},
  {cont__363_3, NULL, 1175, 1176, 1, 79},
  {cont__363_4, NULL, 1180, 1180, 5, 29},
  {cont__364_1, NULL, 1182, 1182, 5, 42},
  {cont__364_2, NULL, 1183, 1189, 5, 58},
  {cont__364_6, NULL, 1193, 1193, 5, 26},
  {cont__364_7, NULL, 1194, 1222, 5, 63},
  {cont__364_43, NULL, 1178, 1222, 1, 66},
  {cont__364_44, NULL, 1228, 1228, 38, 72},
  {cont__365_1, NULL, 1228, 1228, 9, 72},
  {cont__365_2, NULL, 1227, 1228, 7, 71},
  {cont__365_3, NULL, 1234, 1234, 17, 43},
  {cont__365_4, NULL, 1234, 1234, 17, 66},
  {cont__365_5, NULL, 1236, 1236, 17, 38},
  {cont__365_6, NULL, 1237, 1237, 17, 25},
  {cont__365_7, NULL, 1233, 1237, 15, 24},
  {cont__365_8, NULL, 1232, 1237, 13, 25},
  {cont__365_9, NULL, 1238, 1246, 13, 64},
  {cont__365_18, NULL, 1231, 1247, 11, 33},
  {cont__365_19, NULL, 1250, 1250, 22, 52},
  {cont__365_20, NULL, 1250, 1250, 13, 53},
  {cont__365_21, NULL, 1248, 1250, 11, 52},
  {cont__365_22, NULL, 1230, 1250, 9, 53},
  {cont__365_23, NULL, 1229, 1250, 7, 54},
  {cont__365_24, NULL, 1226, 1250, 5, 55},
  {cont__365_25, NULL, 1251, 1251, 32, 66},
  {cont__365_26, NULL, 1251, 1251, 20, 66},
  {cont__365_27, NULL, 1251, 1251, 5, 67},
  {cont__365_28, NULL, 1252, 1252, 5, 41},
  {cont__365_29, NULL, 1224, 1252, 1, 42},
  {cont__365_30, NULL, 1256, 1256, 35, 70},
  {cont__366_1, NULL, 1256, 1256, 26, 71},
  {cont__366_2, NULL, 1256, 1256, 5, 71},
  {cont__366_3, NULL, 1258, 1258, 7, 46},
  {cont__366_4, NULL, 1259, 1259, 11, 30},
  {cont__366_5, NULL, 1259, 1259, 41, 75},
  {cont__366_6, NULL, 1259, 1259, 32, 76},
  {cont__366_7, NULL, 1259, 1259, 7, 77},
  {cont__366_8, NULL, 1257, 1259, 5, 76},
  {cont__366_9, NULL, 1254, 1259, 1, 79},
  {cont__366_10, NULL, 1263, 1263, 29, 63},
  {cont__367_1, NULL, 1263, 1263, 20, 64},
  {cont__367_2, NULL, 1263, 1263, 5, 64},
  {cont__367_3, NULL, 1261, 1264, 1, 25},
  {cont__367_4, NULL, 1268, 1268, 22, 56},
  {cont__368_1, NULL, 1268, 1268, 13, 57},
  {cont__368_2, NULL, 1268, 1268, 5, 57},
  {cont__368_3, NULL, 1266, 1269, 1, 25},
  {cont__368_4, NULL, 1273, 1273, 5, 54},
  {cont__369_1, NULL, 1274, 1274, 5, 34},
  {cont__369_2, NULL, 1278, 1278, 12, 27},
  {cont__369_3, NULL, 1278, 1278, 7, 28},
  {cont__369_4, NULL, 1279, 1279, 7, 48},
  {cont__369_5, NULL, 1280, 1280, 7, 28},
  {cont__369_6, NULL, 1275, 1280, 5, 27},
  {cont__369_7, NULL, 1271, 1280, 1, 30},
  {cont__369_8, NULL, 1287, 1287, 9, 37},
  {cont__370_1, NULL, 1288, 1288, 9, 49},
  {cont__370_2, NULL, 1285, 1288, 7, 48},
  {cont__370_3, NULL, 1291, 1291, 9, 37},
  {cont__370_4, NULL, 1292, 1292, 9, 50},
  {cont__370_5, NULL, 1289, 1292, 7, 49},
  {cont__370_6, NULL, 1295, 1295, 9, 37},
  {cont__370_7, NULL, 1296, 1296, 9, 53},
  {cont__370_8, NULL, 1293, 1296, 7, 52},
  {cont__370_9, NULL, 1297, 1297, 7, 36},
  {cont__370_10, NULL, 1297, 1297, 39, 79},
  {cont__370_11, NULL, 1297, 1297, 7, 79},
  {cont__370_12, NULL, 1284, 1297, 5, 78},
  {cont__370_13, NULL, 1282, 1297, 1, 81},
  {cont__370_14, NULL, 1304, 1304, 9, 27},
  {cont__371_1, NULL, 1305, 1305, 9, 43},
  {cont__371_2, NULL, 1306, 1306, 9, 41},
  {cont__371_3, NULL, 1303, 1306, 7, 40},
  {cont__371_4, NULL, 1307, 1307, 12, 56},
  {cont__371_5, NULL, 1307, 1307, 7, 56},
  {cont__371_6, NULL, 1301, 1307, 5, 55},
  {cont__371_7, NULL, 1299, 1307, 1, 58},
  {cont__371_8, NULL, 1312, 1314, 5, 30},
  {cont__372_2, NULL, 1309, 1314, 1, 33},
  {cont__372_3, NULL, 1320, 1320, 7, 26},
  {cont__373_1, NULL, 1322, 1322, 7, 24},
  {cont__373_2, NULL, 1323, 1323, 7, 27},
  {cont__373_3, NULL, 1319, 1324, 5, 23},
  {cont__373_4, NULL, 1316, 1324, 1, 26},
  {cont__373_5, NULL, 1326, 1326, 1, 68},
  {cont__374_1, NULL, 1329, 1329, 49, 71},
  {cont__375_1, NULL, 1329, 1329, 40, 72},
  {cont__375_2, NULL, 1328, 1329, 1, 72},
  {cont__375_3, NULL, 1335, 1335, 5, 34},
  {cont__376_1, NULL, 1336, 1336, 5, 55},
  {cont__376_2, NULL, 1331, 1337, 1, 19},
  {cont__376_4, NULL, 1340, 1340, 52, 74},
  {cont__377_1, NULL, 1340, 1340, 43, 75},
  {cont__377_2, NULL, 1339, 1340, 1, 75},
  {cont__377_3, NULL, 1348, 1348, 23, 57},
  {cont__378_1, NULL, 1348, 1348, 11, 76},
  {cont__378_2, NULL, 1349, 1349, 39, 76},
  {cont__378_3, NULL, 1349, 1349, 20, 76},
  {cont__378_4, NULL, 1349, 1349, 11, 77},
  {cont__378_5, NULL, 1347, 1349, 9, 76},
  {cont__378_6, NULL, 1350, 1350, 9, 46},
  {cont__378_7, NULL, 1346, 1350, 7, 45},
  {cont__378_8, NULL, 1345, 1350, 5, 46},
  {cont__378_9, NULL, 1351, 1351, 5, 15},
  {cont__378_10, NULL, 1342, 1351, 1, 16},
  {cont__378_11, NULL, 1359, 1359, 21, 66},
  {cont__379_1, NULL, 1359, 1359, 9, 75},
  {cont__379_2, NULL, 1360, 1360, 27, 75},
  {cont__379_3, NULL, 1360, 1360, 18, 75},
  {cont__379_4, NULL, 1360, 1360, 9, 76},
  {cont__379_5, NULL, 1358, 1360, 7, 75},
  {cont__379_6, NULL, 1361, 1361, 7, 55},
  {cont__379_7, NULL, 1357, 1361, 5, 54},
  {cont__379_8, NULL, 1362, 1362, 5, 26},
  {cont__379_9, NULL, 1363, 1363, 5, 19},
  {cont__379_10, NULL, 1364, 1364, 5, 15},
  {cont__379_11, NULL, 1353, 1364, 1, 16},
  {cont__379_12, NULL, 1369, 1369, 5, 18},
  {cont__380_1, NULL, 1371, 1371, 5, 33},
  {cont__380_2, NULL, 1376, 1376, 16, 31},
  {cont__380_3, NULL, 1376, 1376, 11, 32},
  {cont__380_4, NULL, 1380, 1380, 11, 32},
  {cont__380_5, NULL, 1374, 1380, 9, 31},
  {cont__380_6, NULL, 1382, 1382, 20, 55},
  {cont__380_7, NULL, 1382, 1382, 11, 56},
  {cont__380_8, NULL, 1385, 1385, 21, 38},
  {cont__380_9, NULL, 1385, 1385, 53, 74},
  {cont__380_10, NULL, 1385, 1385, 13, 74},
  {cont__380_11, NULL, 1388, 1388, 46, 79},
  {cont__380_13, NULL, 1388, 1388, 15, 80},
  {cont__380_14, NULL, 1386, 1388, 13, 79},
  {cont__380_15, NULL, 1389, 1389, 13, 46},
  {cont__380_16, NULL, 1384, 1389, 11, 45},
  {cont__380_17, NULL, 1381, 1389, 9, 46},
  {cont__380_18, NULL, 1390, 1390, 9, 42},
  {cont__380_19, NULL, 1373, 1390, 7, 41},
  {cont__380_20, NULL, 1372, 1390, 5, 42},
  {cont__380_21, NULL, 1366, 1391, 1, 23},
  {cont__380_22, NULL, 1395, 1395, 5, 21},
  {cont__381_1, NULL, 1396, 1396, 5, 18},
  {cont__381_2, NULL, 1393, 1399, 1, 23},
  {cont__381_3, NULL, 1401, 1401, 1, 42},
  {cont__382_1, NULL, 1406, 1406, 5, 20},
  {cont__383_1, NULL, 1408, 1408, 5, 25},
  {cont__383_2, NULL, 1409, 1409, 28, 51},
  {cont__383_3, NULL, 1409, 1409, 28, 66},
  {cont__383_4, NULL, 1409, 1409, 23, 67},
  {cont__383_5, NULL, 1409, 1409, 5, 68},
  {cont__383_6, NULL, 1410, 1410, 5, 26},
  {cont__383_7, NULL, 1411, 1411, 5, 19},
  {cont__383_8, NULL, 1412, 1412, 5, 15},
  {cont__383_9, NULL, 1403, 1413, 1, 23},
  {cont__383_10, NULL, 1415, 1415, 37, 70},
  {cont__384_1, NULL, 1415, 1415, 1, 71},
  {cont__384_2, NULL, 1418, 1418, 5, 24},
  {cont__385_1, NULL, 1421, 1421, 7, 48},
  {cont__385_2, NULL, 1421, 1421, 7, 71},
  {cont__385_3, NULL, 1423, 1423, 9, 51},
  {cont__385_4, NULL, 1422, 1423, 7, 72},
  {cont__385_5, NULL, 1424, 1424, 7, 49},
  {cont__385_6, NULL, 1424, 1424, 7, 72},
  {cont__385_7, NULL, 1425, 1425, 7, 50},
  {cont__385_8, NULL, 1425, 1425, 7, 73},
  {cont__385_9, NULL, 1427, 1427, 9, 37},
  {cont__385_10, NULL, 1428, 1428, 9, 65},
  {cont__385_11, NULL, 1426, 1428, 7, 64},
  {cont__385_12, NULL, 1420, 1428, 5, 65},
  {cont__385_13, NULL, 1416, 1429, 1, 23},
  {cont__385_14, NULL, 1432, 1432, 9, 38},
  {cont__386_1, NULL, 1431, 1432, 1, 38},
  {cont__386_3, NULL, 1435, 1435, 10, 51},
  {cont__387_1, NULL, 1434, 1435, 1, 51},
  {cont__387_3, NULL, 1441, 1441, 7, 79},
  {cont__388_1, NULL, 1440, 1441, 5, 78},
  {cont__388_2, NULL, 1437, 1442, 1, 20},
  {cont__388_3, NULL, 1446, 1446, 5, 24},
  {cont__389_1, NULL, 1449, 1449, 7, 48},
  {cont__389_2, NULL, 1449, 1449, 7, 71},
  {cont__389_3, NULL, 1451, 1451, 9, 51},
  {cont__389_4, NULL, 1455, 1461, 13, 56},
  {cont__389_15, NULL, 1453, 1461, 11, 57},
  {cont__389_16, NULL, 1452, 1462, 9, 30},
  {cont__389_17, NULL, 1450, 1462, 7, 31},
  {cont__389_18, NULL, 1463, 1463, 7, 49},
  {cont__389_19, NULL, 1463, 1463, 7, 72},
  {cont__389_20, NULL, 1464, 1464, 7, 50},
  {cont__389_21, NULL, 1464, 1464, 7, 73},
  {cont__389_22, NULL, 1466, 1466, 9, 37},
  {cont__389_23, NULL, 1467, 1467, 9, 65},
  {cont__389_24, NULL, 1465, 1467, 7, 64},
  {cont__389_25, NULL, 1448, 1467, 5, 65},
  {cont__389_26, NULL, 1444, 1468, 1, 23},
  {cont__389_27, NULL, 1470, 1470, 1, 53},
  {cont__390_1, NULL, 1474, 1474, 11, 42},
  {cont__391_1, NULL, 1474, 1474, 5, 47},
  {cont__391_3, NULL, 1475, 1475, 10, 41},
  {cont__391_4, NULL, 1475, 1475, 5, 41},
  {cont__391_5, NULL, 1472, 1475, 1, 42},
  {cont__391_6, NULL, 1479, 1479, 5, 28},
  {cont__392_1, NULL, 1482, 1482, 5, 42},
  {cont__392_2, NULL, 1491, 1491, 13, 52},
  {cont__392_3, NULL, 1488, 1491, 11, 51},
  {cont__392_4, NULL, 1487, 1493, 9, 28},
  {cont__392_5, NULL, 1484, 1493, 7, 29},
  {cont__392_6, NULL, 1483, 1494, 5, 24},
  {cont__392_7, NULL, 1477, 1495, 1, 23},
  {cont__392_8, NULL, 1497, 1497, 27, 54},
  {cont__393_1, NULL, 1497, 1497, 1, 63},
  {cont__393_2, NULL, 1501, 1501, 5, 34},
  {cont__394_1, NULL, 1501, 1501, 37, 62},
  {cont__394_2, NULL, 1501, 1501, 5, 62},
  {cont__394_3, NULL, 1499, 1502, 1, 28},
  {cont__394_4, NULL, 1506, 1506, 5, 44},
  {cont__395_1, NULL, 1506, 1506, 47, 72},
  {cont__395_2, NULL, 1506, 1506, 5, 72},
  {cont__395_3, NULL, 1504, 1507, 1, 28},
  {cont__395_4, NULL, 1509, 1509, 1, 53},
  {cont__396_1, NULL, 1517, 1517, 9, 34},
  {cont__397_1, NULL, 1520, 1524, 9, 19},
  {cont__397_8, NULL, 1516, 1525, 7, 25},
  {cont__397_9, NULL, 1514, 1525, 5, 26},
  {cont__397_10, NULL, 1511, 1525, 1, 29},
  {cont__397_11, NULL, 1530, 1530, 7, 38},
  {cont__398_1, NULL, 1530, 1530, 50, 76},
  {cont__398_2, NULL, 1530, 1530, 41, 77},
  {cont__398_3, NULL, 1530, 1530, 7, 77},
  {cont__398_4, NULL, 1532, 1532, 7, 40},
  {cont__398_5, NULL, 1529, 1532, 5, 39},
  {cont__398_6, NULL, 1533, 1533, 10, 36},
  {cont__398_7, NULL, 1533, 1533, 5, 37},
  {cont__398_8, NULL, 1527, 1533, 1, 38},
  {cont__398_9, NULL, 1538, 1538, 5, 24},
  {cont__399_1, NULL, 1538, 1538, 54, 63},
  {cont__399_3, NULL, 1538, 1538, 49, 64},
  {cont__399_4, NULL, 1538, 1538, 43, 64},
  {cont__399_5, NULL, 1538, 1538, 27, 65},
  {cont__399_6, NULL, 1538, 1538, 5, 65},
  {cont__399_7, NULL, 1535, 1538, 1, 66},
  {cont__399_8, NULL, 1540, 1540, 20, 39},
  {cont__400_1, NULL, 1540, 1540, 20, 54},
  {cont__400_2, NULL, 1540, 1540, 1, 55},
  {cont__400_3, NULL, 1545, 1545, 31, 70},
  {cont__401_1, NULL, 1545, 1545, 12, 70},
  {cont__401_2, NULL, 1545, 1545, 5, 71},
  {cont__401_3, NULL, 1542, 1545, 1, 72},
  {cont__401_5, NULL, 1548, 1548, 37, 71},
  {cont__402_1, NULL, 1548, 1548, 18, 71},
  {cont__402_2, NULL, 1548, 1548, 11, 72},
  {cont__402_3, NULL, 1547, 1548, 1, 72},
  {cont__402_5, NULL, 1550, 1550, 52, 72},
  {cont__403_1, NULL, 1550, 1550, 33, 72},
  {cont__403_2, NULL, 1550, 1550, 26, 73},
  {cont__403_3, NULL, 1550, 1550, 1, 73},
  {cont__403_5, NULL, 1555, 1555, 31, 77},
  {cont__404_1, NULL, 1555, 1555, 12, 77},
  {cont__404_2, NULL, 1555, 1555, 5, 78},
  {cont__404_3, NULL, 1552, 1555, 1, 79},
  {cont__404_5, NULL, 1557, 1557, 52, 72},
  {cont__405_1, NULL, 1557, 1557, 33, 72},
  {cont__405_2, NULL, 1557, 1557, 26, 73},
  {cont__405_3, NULL, 1557, 1557, 1, 73},
  {cont__405_5, NULL, 1565, 1565, 32, 71},
  {cont__406_5, NULL, 1565, 1565, 9, 72},
  {cont__406_6, NULL, 1563, 1565, 7, 71},
  {cont__406_7, NULL, 1562, 1565, 5, 72},
  {cont__406_8, NULL, 1559, 1565, 1, 75},
  {cont__406_10, NULL, 1568, 1568, 37, 77},
  {cont__407_1, NULL, 1568, 1568, 18, 77},
  {cont__407_2, NULL, 1568, 1568, 11, 78},
  {cont__407_3, NULL, 1567, 1568, 1, 78},
  {cont__407_5, NULL, 1579, 1579, 5, 42},
  {cont__408_2, NULL, 1570, 1579, 1, 43},
  {cont__408_3, NULL, 1581, 1581, 35, 45},
  {cont__409_1, NULL, 1581, 1581, 1, 45},
  {cont__409_2, NULL, 1582, 1582, 1, 45},
  {cont__410_1, NULL, 1583, 1583, 1, 32},
  {cont__411_2, NULL, 1584, 1584, 50, 69},
  {cont__412_1, NULL, 1584, 1584, 37, 70},
  {cont__412_2, NULL, 1584, 1584, 22, 70},
  {cont__412_3, NULL, 1584, 1584, 1, 71},
  {cont__412_4, NULL, 1589, 1589, 28, 51},
  {cont__413_1, NULL, 1589, 1589, 28, 66},
  {cont__413_2, NULL, 1589, 1589, 23, 67},
  {cont__413_3, NULL, 1589, 1589, 5, 68},
  {cont__413_4, NULL, 1586, 1589, 1, 69},
  {cont__413_5, NULL, 1594, 1594, 5, 20},
  {cont__414_1, NULL, 1595, 1595, 5, 25},
  {cont__414_2, NULL, 1596, 1596, 31, 46},
  {cont__414_3, NULL, 1596, 1596, 22, 47},
  {cont__414_4, NULL, 1596, 1596, 9, 47},
  {cont__414_5, NULL, 1596, 1596, 5, 55},
  {cont__414_6, NULL, 1597, 1597, 5, 26},
  {cont__414_7, NULL, 1598, 1598, 5, 19},
  {cont__414_8, NULL, 1599, 1599, 5, 15},
  {cont__414_9, NULL, 1591, 1599, 1, 16},
  {cont__414_10, NULL, 1601, 1601, 41, 60},
  {cont__415_1, NULL, 1601, 1601, 34, 61},
  {cont__415_2, NULL, 1601, 1601, 1, 61},
  {cont__415_3, NULL, 1609, 1609, 7, 50},
  {cont__416_2, NULL, 1605, 1609, 5, 49},
  {cont__416_3, NULL, 1610, 1610, 12, 31},
  {cont__416_4, NULL, 1610, 1610, 5, 32},
  {cont__416_5, NULL, 1603, 1610, 1, 33},
  {cont__416_6, NULL, },
  {entry__1_1_sim2c__std_identifier, NULL, 30, 30, 32, 79},
  {entry__2_13, NULL, 60, 60, 38, 63},
  {cont__2_14, &frame__2_13, 60, 60, 23, 75},
  {cont__2_15, &frame__2_13, 60, 60, 75, 75},
  {entry__2_21, NULL, 62, 62, 21, 29},
  {cont__2_22, &frame__2_21, 62, 62, 21, 35},
  {cont__2_23, &frame__2_21, 62, 62, 21, 35},
  {entry__2_25, NULL, 62, 62, 38, 43},
  {cont__2_26, &frame__2_25, 62, 62, 43, 43},
  {entry__2_19, NULL, 62, 62, 12, 16},
  {cont__2_20, &frame__2_19, 62, 62, 12, 35},
  {cont__2_24, &frame__2_19, 62, 62, 9, 43},
  {entry__2_30, NULL, 64, 64, 32, 62},
  {cont__2_31, &frame__2_30, 64, 64, 29, 62},
  {entry__2_32, NULL, 64, 64, 65, 71},
  {entry__2_40, NULL, 68, 68, 10, 19},
  {cont__2_41, &frame__2_40, 68, 68, 10, 19},
  {cont__2_42, &frame__2_40, 68, 68, 7, 25},
  {cont__2_43, &frame__2_40, 69, 69, 7, 12},
  {cont__2_44, &frame__2_40, 69, 69, 12, 12},
  {entry__2_39, NULL, 67, 69, 5, 12},
  {cont__2_45, &frame__2_39, 69, 69, 12, 12},
  {entry__2_50, NULL, 73, 73, 43, 45},
  {cont__2_51, &frame__2_50, 73, 73, 14, 59},
  {cont__2_55, &frame__2_50, 73, 73, 7, 59},
  {entry__2_56, NULL, 75, 77, 14, 75},
  {cont__2_62, &frame__2_56, 75, 77, 7, 75},
  {cont__2_63, &frame__2_56, 78, 78, 7, 19},
  {cont__2_64, &frame__2_56, 79, 79, 16, 25},
  {cont__2_66, &frame__2_56, 79, 79, 7, 29},
  {entry__2_1_print_message, NULL, 52, 52, 3, 37},
  {cont__2_2, &frame__2_1_print_message, 53, 53, 8, 24},
  {cont__2_3, &frame__2_1_print_message, 53, 53, 8, 31},
  {cont__2_4, &frame__2_1_print_message, 53, 53, 3, 33},
  {cont__2_5, &frame__2_1_print_message, 54, 54, 3, 32},
  {cont__2_6, &frame__2_1_print_message, 57, 57, 38, 42},
  {cont__2_7, &frame__2_1_print_message, 57, 57, 23, 43},
  {cont__2_8, &frame__2_1_print_message, 57, 57, 45, 70},
  {cont__2_9, &frame__2_1_print_message, 56, 57, 3, 71},
  {cont__2_10, &frame__2_1_print_message, 59, 59, 3, 27},
  {cont__2_11, &frame__2_1_print_message, 60, 60, 6, 20},
  {cont__2_12, &frame__2_1_print_message, 60, 60, 3, 75},
  {cont__2_16, &frame__2_1_print_message, 61, 61, 7, 23},
  {cont__2_17, &frame__2_1_print_message, 61, 61, 3, 30},
  {cont__2_18, &frame__2_1_print_message, 62, 62, 3, 43},
  {cont__2_27, &frame__2_1_print_message, 63, 63, 3, 32},
  {cont__2_28, &frame__2_1_print_message, 64, 64, 12, 26},
  {cont__2_29, &frame__2_1_print_message, 64, 64, 3, 72},
  {cont__2_33, &frame__2_1_print_message, 65, 65, 42, 59},
  {cont__2_34, &frame__2_1_print_message, 65, 65, 21, 59},
  {cont__2_35, &frame__2_1_print_message, 65, 65, 61, 79},
  {cont__2_37, &frame__2_1_print_message, 65, 65, 3, 80},
  {cont__2_38, &frame__2_1_print_message, 66, 69, 3, 13},
  {cont__2_46, &frame__2_1_print_message, 70, 70, 18, 23},
  {cont__2_47, &frame__2_1_print_message, 70, 70, 3, 23},
  {cont__2_48, &frame__2_1_print_message, 70, 70, 17, 23},
  {cont__2_49, &frame__2_1_print_message, 71, 79, 3, 30},
  {entry__3_1_sim2c__Warning, NULL, 82, 82, 17, 32},
  {cont__3_2, &frame__3_1_sim2c__Warning, 82, 82, 34, 56},
  {cont__3_3, &frame__3_1_sim2c__Warning, 82, 82, 3, 70},
  {entry__4_1_ExitWithSyntaxError, NULL, 85, 85, 3, 50},
  {cont__4_3, &frame__4_1_ExitWithSyntaxError, 86, 86, 3, 8},
  {entry__5_1_sim2c__SyntaxError, NULL, 89, 89, 23, 38},
  {cont__5_2, &frame__5_1_sim2c__SyntaxError, 89, 89, 40, 62},
  {cont__5_3, &frame__5_1_sim2c__SyntaxError, 89, 89, 3, 66},
  {entry__6_1_ParseError, NULL, 92, 92, 40, 56},
  {cont__6_2, &frame__6_1_ParseError, 92, 92, 3, 60},
  {entry__8_1_types__syntax_error_grammar__match, NULL, 97, 97, 21, 36},
  {cont__8_2, &frame__8_1_types__syntax_error_grammar__match, 97, 97, 3, 36},
  {entry__9_1_syntax_error, NULL, 99, 99, 26, 68},
  {entry__11_4, NULL, 109, 109, 34, 55},
  {cont__11_5, &frame__11_4, 109, 109, 34, 55},
  {entry__11_8, NULL, 113, 113, 11, 46},
  {entry__11_10, NULL, 115, 115, 11, 45},
  {entry__11_12, NULL, 117, 117, 11, 46},
  {entry__11_14, NULL, 119, 119, 11, 61},
  {entry__11_16, NULL, 121, 122, 29, 42},
  {cont__11_19, &frame__11_16, 121, 122, 11, 42},
  {entry__11_7, NULL, 110, 122, 7, 44},
  {entry__11_20, NULL, 124, 124, 7, 42},
  {entry__11_1_types__unexpected_input_error_grammar__match, NULL, 107, 107, 3, 33},
  {cont__11_2, &frame__11_1_types__unexpected_input_error_grammar__match, 109, 109, 5, 29},
  {cont__11_3, &frame__11_1_types__unexpected_input_error_grammar__match, 109, 109, 5, 55},
  {cont__11_6, &frame__11_1_types__unexpected_input_error_grammar__match, 108, 124, 3, 43},
  {entry__12_1_unexpected_input_error, NULL, 127, 127, 3, 61},
  {entry__14_1_types__print_grammar__match, NULL, 136, 136, 12, 27},
  {cont__14_2, &frame__14_1_types__print_grammar__match, 136, 136, 3, 27},
  {cont__14_3, &frame__14_1_types__print_grammar__match, 137, 137, 3, 6},
  {entry__15_1_print, NULL, 139, 139, 19, 54},
  {entry__17_1_dump_stream_grammar__match, NULL, 148, 148, 3, 23},
  {cont__17_3, &frame__17_1_dump_stream_grammar__match, 149, 149, 17, 48},
  {cont__17_4, &frame__17_1_dump_stream_grammar__match, 149, 149, 3, 48},
  {cont__17_5, &frame__17_1_dump_stream_grammar__match, 150, 150, 3, 23},
  {cont__17_7, &frame__17_1_dump_stream_grammar__match, 151, 151, 3, 6},
  {entry__18_4, NULL, 164, 164, 42, 56},
  {cont__18_5, &frame__18_4, 164, 164, 35, 56},
  {cont__18_6, &frame__18_4, 164, 164, 56, 56},
  {entry__18_10, NULL, 165, 165, 44, 60},
  {cont__18_11, &frame__18_10, 165, 165, 37, 60},
  {cont__18_12, &frame__18_10, 165, 165, 60, 60},
  {entry__18_18, NULL, 167, 167, 51, 66},
  {cont__18_19, &frame__18_18, 167, 167, 66, 66},
  {entry__18_16, NULL, 167, 167, 18, 35},
  {cont__18_17, &frame__18_16, 167, 167, 5, 66},
  {cont__18_20, &frame__18_16, 167, 167, 66, 66},
  {entry__18_26, NULL, 169, 169, 51, 66},
  {cont__18_27, &frame__18_26, 169, 169, 66, 66},
  {entry__18_24, NULL, 169, 169, 18, 35},
  {cont__18_25, &frame__18_24, 169, 169, 5, 66},
  {cont__18_28, &frame__18_24, 169, 169, 66, 66},
  {entry__18_34, NULL, 171, 171, 56, 70},
  {cont__18_35, &frame__18_34, 171, 171, 70, 70},
  {entry__18_32, NULL, 171, 171, 18, 41},
  {cont__18_33, &frame__18_32, 171, 171, 5, 70},
  {cont__18_36, &frame__18_32, 171, 171, 70, 70},
  {entry__18_42, NULL, 173, 173, 49, 63},
  {cont__18_43, &frame__18_42, 173, 173, 63, 63},
  {entry__18_40, NULL, 173, 173, 18, 34},
  {cont__18_41, &frame__18_40, 173, 173, 5, 63},
  {cont__18_44, &frame__18_40, 173, 173, 63, 63},
  {entry__18_48, NULL, 174, 174, 41, 54},
  {cont__18_49, &frame__18_48, 174, 174, 34, 54},
  {cont__18_50, &frame__18_48, 174, 174, 54, 54},
  {entry__18_54, NULL, 175, 175, 45, 62},
  {cont__18_55, &frame__18_54, 175, 175, 38, 62},
  {cont__18_56, &frame__18_54, 175, 175, 62, 62},
  {entry__18_1_sim2c__strip, NULL, 164, 164, 6, 21},
  {cont__18_2, &frame__18_1_sim2c__strip, 164, 164, 6, 32},
  {cont__18_3, &frame__18_1_sim2c__strip, 164, 164, 3, 56},
  {cont__18_7, &frame__18_1_sim2c__strip, 165, 165, 6, 23},
  {cont__18_8, &frame__18_1_sim2c__strip, 165, 165, 6, 34},
  {cont__18_9, &frame__18_1_sim2c__strip, 165, 165, 3, 60},
  {cont__18_13, &frame__18_1_sim2c__strip, 166, 166, 6, 24},
  {cont__18_14, &frame__18_1_sim2c__strip, 166, 166, 6, 35},
  {cont__18_15, &frame__18_1_sim2c__strip, 166, 167, 3, 66},
  {cont__18_21, &frame__18_1_sim2c__strip, 168, 168, 6, 24},
  {cont__18_22, &frame__18_1_sim2c__strip, 168, 168, 6, 35},
  {cont__18_23, &frame__18_1_sim2c__strip, 168, 169, 3, 66},
  {cont__18_29, &frame__18_1_sim2c__strip, 170, 170, 6, 30},
  {cont__18_30, &frame__18_1_sim2c__strip, 170, 170, 6, 41},
  {cont__18_31, &frame__18_1_sim2c__strip, 170, 171, 3, 70},
  {cont__18_37, &frame__18_1_sim2c__strip, 172, 172, 6, 23},
  {cont__18_38, &frame__18_1_sim2c__strip, 172, 172, 6, 34},
  {cont__18_39, &frame__18_1_sim2c__strip, 172, 173, 3, 63},
  {cont__18_45, &frame__18_1_sim2c__strip, 174, 174, 6, 20},
  {cont__18_46, &frame__18_1_sim2c__strip, 174, 174, 6, 31},
  {cont__18_47, &frame__18_1_sim2c__strip, 174, 174, 3, 54},
  {cont__18_51, &frame__18_1_sim2c__strip, 175, 175, 6, 24},
  {cont__18_52, &frame__18_1_sim2c__strip, 175, 175, 6, 35},
  {cont__18_53, &frame__18_1_sim2c__strip, 175, 175, 3, 62},
  {cont__18_57, &frame__18_1_sim2c__strip, },
  {entry__20_1_dump_grammar__match, NULL, 180, 180, 10, 37},
  {cont__20_2, &frame__20_1_dump_grammar__match, 180, 180, 3, 37},
  {cont__20_4, &frame__20_1_dump_grammar__match, 181, 181, 3, 6},
  {entry__22_1_dump3_grammar__match, NULL, 186, 186, 12, 39},
  {cont__22_2, &frame__22_1_dump3_grammar__match, 186, 186, 3, 39},
  {cont__22_3, &frame__22_1_dump3_grammar__match, 187, 187, 3, 6},
  {entry__24_1_dump5_grammar__match, NULL, 192, 192, 12, 39},
  {cont__24_2, &frame__24_1_dump5_grammar__match, 192, 192, 3, 39},
  {cont__24_3, &frame__24_1_dump5_grammar__match, 193, 193, 3, 6},
  {entry__28_3, NULL, 226, 226, 25, 44},
  {cont__28_4, &frame__28_3, 226, 226, 22, 44},
  {entry__28_5, NULL, 226, 226, 47, 65},
  {entry__28_1_sim2c__precedence, NULL, 226, 226, 6, 19},
  {cont__28_2, &frame__28_1_sim2c__precedence, 226, 226, 3, 65},
  {entry__29_1_sim2c__is_left_associative, NULL, 228, 228, 40, 47},
  {cont__29_2, &frame__29_1_sim2c__is_left_associative, 228, 228, 37, 47},
  {entry__30_1_is_right_associative, NULL, 230, 230, 34, 42},
  {cont__30_2, &frame__30_1_is_right_associative, 230, 230, 34, 42},
  {cont__30_3, &frame__30_1_is_right_associative, 230, 230, 31, 42},
  {entry__31_1_infix_operator, NULL, 233, 233, 19, 64},
  {cont__31_2, &frame__31_1_infix_operator, 233, 233, 6, 65},
  {cont__31_3, &frame__31_1_infix_operator, 233, 233, 3, 65},
  {entry__32_1_interleaved, NULL, 235, 235, 58, 78},
  {cont__32_2, &frame__32_1_interleaved, 235, 235, 53, 79},
  {cont__32_3, &frame__32_1_interleaved, 235, 235, 41, 79},
  {cont__32_4, &frame__32_1_interleaved, 235, 235, 38, 79},
  {entry__35_1_types__inline_grammar__match, NULL, 245, 245, 18, 36},
  {cont__35_2, &frame__35_1_types__inline_grammar__match, 245, 245, 3, 43},
  {cont__35_3, &frame__35_1_types__inline_grammar__match, 245, 245, 43, 43},
  {entry__36_1_inline, NULL, 247, 247, 23, 65},
  {entry__42_3, NULL, 265, 265, 36, 60},
  {cont__42_5, &frame__42_3, 265, 265, 23, 61},
  {cont__42_6, &frame__42_3, 265, 265, 8, 62},
  {cont__42_7, &frame__42_3, 265, 265, 5, 62},
  {entry__42_8, NULL, 266, 266, 23, 56},
  {cont__42_9, &frame__42_8, 266, 266, 8, 57},
  {cont__42_10, &frame__42_8, 266, 266, 5, 57},
  {entry__42_1_expect, NULL, 264, 264, 5, 26},
  {cont__42_2, &frame__42_1_expect, 263, 266, 3, 57},
  {entry__45_1_sim2c__arguments_span, NULL, 285, 285, 30, 50},
  {cont__45_2, &frame__45_1_sim2c__arguments_span, 285, 285, 6, 51},
  {cont__45_3, &frame__45_1_sim2c__arguments_span, 285, 285, 3, 51},
  {entry__46_1_sim2c__output_arguments_span, NULL, 288, 288, 37, 77},
  {cont__46_2, &frame__46_1_sim2c__output_arguments_span, 288, 288, 6, 78},
  {cont__46_3, &frame__46_1_sim2c__output_arguments_span, 288, 288, 3, 78},
  {entry__208_7, NULL, 1619, 1619, 32, 75},
  {entry__208_1_sim2c__parse_meta_instruction, NULL, 1617, 1617, 3, 36},
  {cont__208_2, &frame__208_1_sim2c__parse_meta_instruction, 1618, 1618, 3, 38},
  {cont__208_3, &frame__208_1_sim2c__parse_meta_instruction, 1619, 1619, 13, 29},
  {cont__208_4, &frame__208_1_sim2c__parse_meta_instruction, 1619, 1619, 6, 29},
  {cont__208_5, &frame__208_1_sim2c__parse_meta_instruction, 1619, 1619, 6, 29},
  {cont__208_6, &frame__208_1_sim2c__parse_meta_instruction, 1619, 1619, 3, 75},
  {cont__208_9, &frame__208_1_sim2c__parse_meta_instruction, 1620, 1620, 3, 8},
  {entry__209_9, NULL, 1629, 1629, 9, 67},
  {entry__209_5, NULL, 1628, 1628, 17, 33},
  {cont__209_6, &frame__209_5, 1628, 1628, 10, 33},
  {cont__209_7, &frame__209_5, 1628, 1628, 10, 33},
  {cont__209_8, &frame__209_5, 1628, 1629, 7, 67},
  {entry__209_11, NULL, 1631, 1631, 7, 57},
  {cont__209_13, &frame__209_11, 1632, 1632, 7, 26},
  {cont__209_14, &frame__209_11, 1633, 1633, 7, 25},
  {cont__209_16, &frame__209_11, 1634, 1634, 7, 12},
  {entry__209_1_sim2c__parse_statement, NULL, 1624, 1624, 3, 36},
  {cont__209_2, &frame__209_1_sim2c__parse_statement, 1625, 1625, 3, 33},
  {cont__209_3, &frame__209_1_sim2c__parse_statement, 1627, 1627, 5, 18},
  {cont__209_4, &frame__209_1_sim2c__parse_statement, 1626, 1634, 3, 13},
  {cont__209_17, &frame__209_1_sim2c__parse_statement, 1635, 1635, 3, 8},
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
  {entry__269_13, NULL, 413, 414, 29, 58},
  {cont__269_16, &frame__269_13, 413, 414, 11, 58},
  {entry__269_24, NULL, 419, 420, 31, 62},
  {cont__269_26, &frame__269_24, 419, 420, 13, 62},
  {entry__269_21, NULL, 418, 418, 14, 38},
  {cont__269_22, &frame__269_21, 418, 418, 14, 49},
  {cont__269_23, &frame__269_21, 418, 420, 11, 63},
  {cont__269_27, &frame__269_21, 421, 421, 11, 36},
  {cont__269_28, &frame__269_21, 421, 421, 46, 46},
  {entry__269_10, NULL, 411, 411, 9, 37},
  {cont__269_11, &frame__269_10, 412, 412, 12, 40},
  {cont__269_12, &frame__269_10, 412, 414, 9, 59},
  {cont__269_17, &frame__269_10, 415, 415, 9, 38},
  {cont__269_18, &frame__269_10, 416, 416, 9, 39},
  {cont__269_19, &frame__269_10, 417, 417, 12, 27},
  {cont__269_20, &frame__269_10, 417, 421, 9, 46},
  {entry__270_6, NULL, 434, 435, 29, 55},
  {cont__270_8, &frame__270_6, 434, 435, 11, 55},
  {entry__270_3, NULL, 432, 432, 9, 37},
  {cont__270_4, &frame__270_3, 433, 433, 12, 37},
  {cont__270_5, &frame__270_3, 433, 435, 9, 56},
  {cont__270_9, &frame__270_3, 436, 436, 9, 35},
  {cont__270_10, &frame__270_3, 436, 436, 40, 40},
  {entry__273_6, NULL, 452, 453, 29, 53},
  {cont__273_9, &frame__273_6, 452, 453, 11, 53},
  {entry__273_3, NULL, 450, 450, 9, 41},
  {cont__273_4, &frame__273_3, 451, 451, 12, 35},
  {cont__273_5, &frame__273_3, 451, 453, 9, 54},
  {cont__273_10, &frame__273_3, 454, 454, 9, 33},
  {cont__273_11, &frame__273_3, 454, 454, 38, 38},
  {entry__274_6, NULL, 467, 468, 29, 54},
  {cont__274_9, &frame__274_6, 467, 468, 11, 54},
  {entry__274_3, NULL, 465, 465, 9, 41},
  {cont__274_4, &frame__274_3, 466, 466, 12, 37},
  {cont__274_5, &frame__274_3, 466, 468, 9, 55},
  {cont__274_10, &frame__274_3, 469, 469, 9, 35},
  {cont__274_11, &frame__274_3, 469, 469, 40, 40},
  {entry__277_6, NULL, 485, 486, 29, 63},
  {cont__277_8, &frame__277_6, 485, 486, 11, 63},
  {entry__277_3, NULL, 483, 483, 9, 41},
  {cont__277_4, &frame__277_3, 484, 484, 12, 35},
  {cont__277_5, &frame__277_3, 484, 486, 9, 64},
  {cont__277_9, &frame__277_3, 487, 487, 9, 33},
  {cont__277_10, &frame__277_3, 487, 487, 38, 38},
  {entry__284_3, NULL, 514, 514, 40, 65},
  {cont__284_4, &frame__284_3, 514, 514, 40, 65},
  {entry__284_10, NULL, 518, 518, 55, 55},
  {entry__284_11, NULL, 520, 520, 42, 42},
  {cont__284_12, &frame__284_11, 520, 520, 23, 39},
  {cont__284_13, &frame__284_11, 520, 520, 23, 43},
  {cont__284_14, &frame__284_11, 520, 520, 23, 66},
  {cont__284_15, &frame__284_11, 520, 520, 15, 79},
  {cont__284_16, &frame__284_11, 520, 520, 23, 39},
  {cont__284_17, &frame__284_11, 520, 520, 42, 42},
  {cont__284_18, &frame__284_11, 520, 520, 23, 43},
  {cont__284_19, &frame__284_11, 520, 520, 22, 43},
  {cont__284_20, &frame__284_11, 520, 520, 79, 79},
  {entry__284_6, NULL, 515, 515, 11, 45},
  {cont__284_7, &frame__284_6, 517, 517, 13, 30},
  {cont__284_8, &frame__284_6, 517, 517, 13, 39},
  {cont__284_9, &frame__284_6, 516, 520, 11, 80},
  {cont__284_21, &frame__284_6, 521, 521, 42, 42},
  {entry__284_1, NULL, 514, 514, 16, 35},
  {cont__284_2, &frame__284_1, 514, 514, 16, 65},
  {cont__284_5, &frame__284_1, 514, 521, 9, 42},
  {cont__284_22, &frame__284_1, },
  {entry__286_7, NULL, 537, 537, 18, 34},
  {cont__286_8, &frame__286_7, 537, 537, 18, 37},
  {cont__286_9, &frame__286_7, 537, 537, 18, 53},
  {cont__286_10, &frame__286_7, 538, 538, 40, 40},
  {cont__286_11, &frame__286_7, 538, 538, 17, 37},
  {cont__286_12, &frame__286_7, 538, 538, 17, 41},
  {cont__286_13, &frame__286_7, 536, 538, 15, 41},
  {cont__286_14, &frame__286_7, 537, 537, 18, 34},
  {cont__286_15, &frame__286_7, 537, 537, 18, 37},
  {cont__286_16, &frame__286_7, 537, 537, 17, 37},
  {cont__286_17, &frame__286_7, 539, 539, 22, 41},
  {cont__286_18, &frame__286_7, 539, 539, 46, 46},
  {cont__286_19, &frame__286_7, 539, 539, 15, 46},
  {cont__286_20, &frame__286_7, 539, 539, 46, 46},
  {entry__286_3, NULL, 534, 534, 26, 43},
  {cont__286_4, &frame__286_3, 534, 534, 13, 44},
  {cont__286_5, &frame__286_3, 535, 535, 16, 20},
  {cont__286_6, &frame__286_3, 535, 539, 13, 46},
  {entry__286_1, NULL, 533, 533, 18, 37},
  {cont__286_2, &frame__286_1, 533, 539, 11, 47},
  {cont__286_21, &frame__286_1, },
  {entry__287_7, NULL, 550, 550, 19, 35},
  {cont__287_8, &frame__287_7, 550, 550, 19, 38},
  {cont__287_9, &frame__287_7, 550, 550, 19, 54},
  {cont__287_10, &frame__287_7, 550, 550, 79, 79},
  {cont__287_11, &frame__287_7, 550, 550, 56, 76},
  {cont__287_12, &frame__287_7, 550, 550, 56, 80},
  {cont__287_13, &frame__287_7, 550, 550, 13, 80},
  {cont__287_14, &frame__287_7, 550, 550, 19, 35},
  {cont__287_15, &frame__287_7, 550, 550, 19, 38},
  {cont__287_16, &frame__287_7, 550, 550, 18, 38},
  {cont__287_17, &frame__287_7, 551, 551, 20, 39},
  {cont__287_18, &frame__287_7, 551, 551, 44, 44},
  {cont__287_19, &frame__287_7, 551, 551, 13, 44},
  {cont__287_20, &frame__287_7, 551, 551, 44, 44},
  {entry__287_3, NULL, 548, 548, 24, 41},
  {cont__287_4, &frame__287_3, 548, 548, 11, 42},
  {cont__287_5, &frame__287_3, 549, 549, 14, 18},
  {cont__287_6, &frame__287_3, 549, 551, 11, 44},
  {entry__287_1, NULL, 547, 547, 16, 35},
  {cont__287_2, &frame__287_1, 547, 551, 9, 45},
  {cont__287_21, &frame__287_1, },
  {entry__290_1, NULL, 567, 567, 26, 42},
  {cont__290_2, &frame__290_1, 568, 568, 33, 56},
  {cont__290_3, &frame__290_1, 564, 568, 9, 57},
  {entry__291_1, NULL, 578, 578, 25, 34},
  {cont__291_2, &frame__291_1, 580, 580, 24, 40},
  {cont__291_3, &frame__291_1, 581, 581, 31, 54},
  {cont__291_4, &frame__291_1, 581, 581, 56, 56},
  {entry__306_2, NULL, 631, 631, 30, 49},
  {cont__306_3, &frame__306_2, 631, 631, 9, 52},
  {cont__306_4, &frame__306_2, 631, 631, 52, 52},
  {entry__307_1, NULL, 638, 638, 33, 33},
  {entry__308_6, NULL, 651, 651, 32, 73},
  {entry__308_2, NULL, 650, 650, 30, 49},
  {cont__308_3, &frame__308_2, 650, 650, 9, 50},
  {cont__308_4, &frame__308_2, 651, 651, 16, 29},
  {cont__308_5, &frame__308_2, 651, 651, 9, 73},
  {cont__308_8, &frame__308_2, 652, 652, 32, 32},
  {entry__309_10, NULL, 666, 666, 40, 59},
  {cont__309_11, &frame__309_10, 666, 666, 40, 70},
  {cont__309_12, &frame__309_10, 666, 666, 9, 71},
  {cont__309_13, &frame__309_10, 666, 666, 71, 71},
  {entry__313_1, NULL, 693, 693, 17, 34},
  {cont__313_2, &frame__313_1, 693, 693, 36, 55},
  {cont__313_3, &frame__313_1, 693, 693, 11, 55},
  {cont__313_4, &frame__313_1, 693, 693, 55, 55},
  {entry__314_5, NULL, 701, 701, 17, 33},
  {cont__314_6, &frame__314_5, 701, 701, 11, 63},
  {cont__314_7, &frame__314_5, 701, 701, 63, 63},
  {entry__314_1, NULL, 700, 700, 12, 30},
  {cont__314_2, &frame__314_1, 700, 700, 12, 36},
  {cont__314_3, &frame__314_1, 700, 700, 12, 36},
  {cont__314_4, &frame__314_1, 700, 701, 9, 63},
  {cont__314_8, &frame__314_1, 702, 702, 30, 30},
  {entry__315_9, NULL, 711, 711, 17, 33},
  {cont__315_10, &frame__315_9, 711, 711, 11, 63},
  {cont__315_11, &frame__315_9, 711, 711, 63, 63},
  {entry__315_5, NULL, 710, 710, 12, 30},
  {cont__315_6, &frame__315_5, 710, 710, 12, 36},
  {cont__315_7, &frame__315_5, 710, 710, 12, 36},
  {cont__315_8, &frame__315_5, 710, 711, 9, 63},
  {cont__315_12, &frame__315_5, 714, 714, 25, 48},
  {cont__315_14, &frame__315_5, 715, 715, 27, 44},
  {cont__315_15, &frame__315_5, 717, 717, 26, 42},
  {cont__315_16, &frame__315_5, 718, 718, 33, 56},
  {cont__315_17, &frame__315_5, 719, 719, 30, 50},
  {cont__315_18, &frame__315_5, 719, 719, 52, 52},
  {entry__315_1, NULL, 709, 709, 20, 37},
  {cont__315_2, &frame__315_1, 709, 709, 10, 38},
  {cont__315_3, &frame__315_1, 709, 709, 10, 42},
  {cont__315_4, &frame__315_1, 709, 719, 7, 52},
  {cont__315_19, &frame__315_1, },
  {entry__318_1, NULL, 745, 745, 15, 32},
  {cont__318_2, &frame__318_1, 745, 745, 34, 60},
  {cont__318_3, &frame__318_1, 745, 745, 7, 60},
  {cont__318_4, &frame__318_1, 745, 745, 60, 60},
  {entry__322_1, NULL, 775, 775, 25, 56},
  {cont__322_3, &frame__322_1, 776, 776, 37, 58},
  {cont__322_5, &frame__322_1, 776, 776, 27, 59},
  {cont__322_6, &frame__322_1, 777, 777, 26, 42},
  {cont__322_7, &frame__322_1, 778, 778, 33, 56},
  {cont__322_8, &frame__322_1, 778, 778, 33, 58},
  {cont__322_9, &frame__322_1, 773, 778, 9, 59},
  {entry__323_1, NULL, 791, 791, 27, 36},
  {cont__323_2, &frame__323_1, 792, 792, 26, 42},
  {cont__323_3, &frame__323_1, 793, 793, 33, 56},
  {cont__323_4, &frame__323_1, 788, 793, 9, 57},
  {entry__330_9, NULL, 853, 853, 13, 51},
  {cont__330_10, &frame__330_9, 853, 853, 13, 51},
  {entry__330_12, NULL, 855, 855, 58, 58},
  {entry__330_2, NULL, 848, 848, 61, 61},
  {cont__330_3, &frame__330_2, 848, 848, 41, 58},
  {cont__330_4, &frame__330_2, 848, 848, 41, 62},
  {cont__330_5, &frame__330_2, 848, 848, 9, 63},
  {cont__330_6, &frame__330_2, 849, 849, 9, 53},
  {cont__330_7, &frame__330_2, 852, 852, 13, 42},
  {cont__330_8, &frame__330_2, 851, 853, 11, 50},
  {cont__330_11, &frame__330_2, 850, 855, 9, 59},
  {cont__330_13, &frame__330_2, },
  {entry__331_6, NULL, 865, 865, 11, 28},
  {cont__331_7, &frame__331_6, 865, 865, 28, 28},
  {entry__331_11, NULL, 873, 873, 47, 71},
  {cont__331_12, &frame__331_11, 873, 873, 44, 71},
  {entry__331_13, NULL, 873, 873, 74, 77},
  {entry__331_22, NULL, 880, 880, 41, 66},
  {cont__331_23, &frame__331_22, 880, 880, 41, 66},
  {entry__331_27, NULL, 885, 885, 21, 57},
  {entry__331_28, NULL, 886, 886, 21, 31},
  {entry__331_16, NULL, 877, 877, 17, 46},
  {cont__331_17, &frame__331_16, 878, 878, 17, 42},
  {cont__331_18, &frame__331_16, 879, 879, 20, 35},
  {cont__331_19, &frame__331_16, 879, 879, 17, 41},
  {cont__331_20, &frame__331_16, 880, 880, 20, 36},
  {cont__331_21, &frame__331_16, 880, 880, 20, 66},
  {cont__331_24, &frame__331_16, 880, 880, 17, 72},
  {cont__331_25, &frame__331_16, 884, 884, 21, 40},
  {cont__331_26, &frame__331_16, 882, 886, 17, 32},
  {cont__331_29, &frame__331_16, 888, 888, 17, 41},
  {cont__331_30, &frame__331_16, 892, 892, 35, 50},
  {cont__331_31, &frame__331_16, 894, 894, 40, 62},
  {cont__331_32, &frame__331_16, 895, 895, 34, 50},
  {cont__331_33, &frame__331_16, 896, 896, 41, 64},
  {cont__331_34, &frame__331_16, 897, 897, 38, 59},
  {cont__331_35, &frame__331_16, 898, 898, 17, 43},
  {cont__331_36, &frame__331_16, 899, 899, 20, 44},
  {cont__331_37, &frame__331_16, 899, 899, 20, 49},
  {cont__331_38, &frame__331_16, 899, 899, 17, 55},
  {entry__331_15, NULL, 876, 899, 15, 55},
  {cont__331_39, &frame__331_15, 899, 899, 55, 55},
  {entry__331_9_update_stack, NULL, 873, 873, 18, 41},
  {cont__331_10, &frame__331_9_update_stack, 872, 873, 13, 78},
  {cont__331_14, &frame__331_9_update_stack, 875, 899, 13, 56},
  {cont__331_40, &frame__331_9_update_stack, 900, 900, 13, 37},
  {cont__331_41, &frame__331_9_update_stack, 901, 901, 13, 46},
  {cont__331_42, &frame__331_9_update_stack, 901, 901, 46, 46},
  {entry__331_51, NULL, 904, 904, 52, 63},
  {cont__331_52, &frame__331_51, 904, 904, 49, 63},
  {entry__331_53, NULL, 904, 904, 66, 77},
  {entry__331_48, NULL, 904, 904, 26, 37},
  {cont__331_49, &frame__331_48, 904, 904, 42, 46},
  {cont__331_50, &frame__331_48, 904, 904, 39, 78},
  {cont__331_54, &frame__331_48, 904, 904, 13, 78},
  {entry__331_8, NULL, 867, 867, 11, 39},
  {cont__331_43, &frame__331_8, 868, 868, 32, 43},
  {cont__331_44, &frame__331_8, 868, 868, 11, 44},
  {cont__331_45, &frame__331_8, 869, 869, 33, 44},
  {cont__331_46, &frame__331_8, 869, 869, 11, 45},
  {cont__331_47, &frame__331_8, 903, 904, 11, 78},
  {cont__331_55, &frame__331_8, 905, 905, 11, 35},
  {cont__331_56, &frame__331_8, 905, 905, 35, 35},
  {entry__331_59, NULL, 907, 907, 41, 60},
  {cont__331_60, &frame__331_59, 907, 907, 36, 66},
  {cont__331_61, &frame__331_59, 907, 907, 67, 67},
  {entry__331_1, NULL, 860, 860, 7, 29},
  {cont__331_2, &frame__331_1, 861, 861, 7, 35},
  {cont__331_3, &frame__331_1, 862, 862, 7, 29},
  {cont__331_4, &frame__331_1, 864, 864, 9, 14},
  {cont__331_5, &frame__331_1, 863, 905, 7, 36},
  {cont__331_57, &frame__331_1, 906, 906, 10, 26},
  {cont__331_58, &frame__331_1, 906, 907, 7, 67},
  {cont__331_62, &frame__331_1, },
  {entry__340_1, NULL, 956, 956, 27, 36},
  {cont__340_2, &frame__340_1, 959, 959, 26, 42},
  {cont__340_3, &frame__340_1, 960, 960, 33, 56},
  {cont__340_4, &frame__340_1, 960, 960, 58, 58},
  {entry__348_1, NULL, 1000, 1000, 10, 26},
  {cont__348_2, &frame__348_1, 1001, 1001, 36, 36},
  {cont__348_3, &frame__348_1, 1001, 1001, 9, 33},
  {cont__348_4, &frame__348_1, 1001, 1001, 9, 37},
  {cont__348_5, &frame__348_1, 999, 1001, 7, 62},
  {cont__348_6, &frame__348_1, 1001, 1001, 63, 63},
  {entry__349_7, NULL, 1015, 1015, 40, 66},
  {cont__349_8, &frame__349_7, 1015, 1015, 40, 66},
  {entry__349_10, NULL, 1016, 1016, 15, 38},
  {cont__349_11, &frame__349_10, 1016, 1016, 9, 49},
  {cont__349_12, &frame__349_10, 1018, 1018, 41, 63},
  {cont__349_13, &frame__349_10, 1017, 1017, 10, 26},
  {cont__349_14, &frame__349_10, 1017, 1017, 29, 29},
  {cont__349_15, &frame__349_10, 1017, 1017, 9, 30},
  {cont__349_16, &frame__349_10, 1018, 1018, 65, 65},
  {entry__349_1, NULL, 1013, 1013, 37, 37},
  {cont__349_2, &frame__349_1, 1013, 1013, 17, 34},
  {cont__349_3, &frame__349_1, 1013, 1013, 7, 38},
  {cont__349_4, &frame__349_1, 1014, 1014, 7, 41},
  {cont__349_5, &frame__349_1, 1015, 1015, 10, 35},
  {cont__349_6, &frame__349_1, 1015, 1015, 10, 66},
  {cont__349_9, &frame__349_1, 1015, 1018, 7, 65},
  {cont__349_17, &frame__349_1, },
  {entry__359_1, NULL, 1120, 1120, 9, 41},
  {entry__359_6, NULL, 1128, 1128, 9, 39},
  {cont__359_7, &frame__359_6, 1129, 1129, 9, 57},
  {cont__359_8, &frame__359_6, 1130, 1130, 39, 39},
  {cont__359_9, &frame__359_6, 1130, 1130, 9, 40},
  {cont__359_10, &frame__359_6, 1134, 1134, 42, 42},
  {cont__359_11, &frame__359_6, 1134, 1134, 13, 43},
  {cont__359_12, &frame__359_6, 1140, 1140, 29, 46},
  {cont__359_13, &frame__359_6, 1141, 1141, 36, 60},
  {cont__359_14, &frame__359_6, 1142, 1142, 34, 59},
  {cont__359_15, &frame__359_6, 1143, 1143, 32, 55},
  {cont__359_16, &frame__359_6, 1144, 1144, 28, 47},
  {cont__359_17, &frame__359_6, 1145, 1145, 35, 61},
  {cont__359_18, &frame__359_6, 1146, 1146, 32, 52},
  {cont__359_19, &frame__359_6, 1132, 1146, 9, 54},
  {cont__359_20, &frame__359_6, 1148, 1148, 9, 54},
  {entry__361_1, NULL, 1158, 1158, 11, 62},
  {cont__361_2, &frame__361_1, 1159, 1159, 42, 42},
  {entry__361_8, NULL, 1165, 1165, 21, 37},
  {cont__361_9, &frame__361_8, 1165, 1165, 21, 40},
  {cont__361_10, &frame__361_8, 1165, 1165, 21, 56},
  {cont__361_11, &frame__361_8, 1165, 1165, 58, 78},
  {cont__361_12, &frame__361_8, 1165, 1165, 13, 78},
  {cont__361_13, &frame__361_8, 1165, 1165, 21, 37},
  {cont__361_14, &frame__361_8, 1165, 1165, 21, 40},
  {cont__361_15, &frame__361_8, 1165, 1165, 20, 40},
  {cont__361_16, &frame__361_8, 1166, 1166, 44, 44},
  {entry__361_4, NULL, 1163, 1163, 24, 41},
  {cont__361_5, &frame__361_4, 1163, 1163, 11, 42},
  {cont__361_6, &frame__361_4, 1164, 1164, 14, 18},
  {cont__361_7, &frame__361_4, 1164, 1166, 11, 44},
  {cont__361_17, &frame__361_4, 1167, 1167, 11, 62},
  {cont__361_18, &frame__361_4, 1168, 1168, 50, 50},
  {entry__364_3, NULL, 1188, 1188, 26, 42},
  {cont__364_4, &frame__364_3, 1189, 1189, 33, 56},
  {cont__364_5, &frame__364_3, 1185, 1189, 9, 57},
  {entry__364_12, NULL, 1203, 1203, 11, 72},
  {entry__364_23, NULL, 1212, 1212, 35, 54},
  {cont__364_24, &frame__364_23, 1213, 1213, 20, 39},
  {cont__364_25, &frame__364_23, 1213, 1213, 20, 44},
  {cont__364_26, &frame__364_23, 1213, 1213, 17, 51},
  {cont__364_27, &frame__364_23, 1214, 1214, 51, 51},
  {cont__364_28, &frame__364_23, 1214, 1214, 32, 52},
  {cont__364_29, &frame__364_23, 1214, 1214, 17, 58},
  {cont__364_30, &frame__364_23, 1214, 1214, 58, 58},
  {entry__364_22, NULL, 1208, 1214, 15, 58},
  {entry__364_32, NULL, 1220, 1220, 52, 52},
  {cont__364_33, &frame__364_32, 1220, 1220, 55, 55},
  {cont__364_34, &frame__364_32, 1220, 1220, 35, 56},
  {cont__364_35, &frame__364_32, 1221, 1221, 20, 39},
  {cont__364_36, &frame__364_32, 1221, 1221, 20, 44},
  {cont__364_37, &frame__364_32, 1221, 1221, 17, 51},
  {cont__364_38, &frame__364_32, 1222, 1222, 52, 52},
  {cont__364_39, &frame__364_32, 1222, 1222, 33, 53},
  {cont__364_40, &frame__364_32, 1222, 1222, 17, 59},
  {cont__364_41, &frame__364_32, 1222, 1222, 59, 59},
  {entry__364_31, NULL, 1216, 1222, 15, 59},
  {entry__364_17, NULL, 1205, 1205, 11, 35},
  {cont__364_18, &frame__364_17, 1207, 1207, 24, 39},
  {cont__364_19, &frame__364_17, 1207, 1207, 13, 40},
  {cont__364_20, &frame__364_17, 1207, 1207, 13, 60},
  {cont__364_21, &frame__364_17, 1206, 1222, 11, 61},
  {entry__364_8, NULL, 1201, 1201, 9, 38},
  {cont__364_9, &frame__364_8, 1202, 1202, 12, 31},
  {cont__364_10, &frame__364_8, 1202, 1202, 12, 35},
  {cont__364_11, &frame__364_8, 1202, 1203, 9, 72},
  {cont__364_14, &frame__364_8, 1204, 1204, 12, 31},
  {cont__364_15, &frame__364_8, 1204, 1204, 12, 35},
  {cont__364_16, &frame__364_8, 1204, 1222, 9, 62},
  {cont__364_42, &frame__364_8, 1222, 1222, 62, 62},
  {entry__365_10, NULL, 1245, 1245, 48, 65},
  {cont__365_11, &frame__365_10, 1245, 1245, 70, 70},
  {cont__365_12, &frame__365_10, 1245, 1245, 42, 71},
  {cont__365_13, &frame__365_10, 1246, 1246, 60, 60},
  {cont__365_14, &frame__365_10, 1246, 1246, 40, 57},
  {cont__365_15, &frame__365_10, 1246, 1246, 40, 61},
  {cont__365_16, &frame__365_10, 1246, 1246, 35, 62},
  {cont__365_17, &frame__365_10, 1242, 1246, 17, 63},
  {entry__372_1, NULL, 1314, 1314, 30, 30},
  {entry__389_10, NULL, 1459, 1459, 19, 76},
  {entry__389_5, NULL, 1457, 1457, 31, 55},
  {cont__389_6, &frame__389_5, 1457, 1457, 17, 58},
  {cont__389_7, &frame__389_5, 1458, 1458, 20, 44},
  {cont__389_8, &frame__389_5, 1458, 1458, 20, 55},
  {cont__389_9, &frame__389_5, 1458, 1459, 17, 76},
  {cont__389_12, &frame__389_5, 1461, 1461, 18, 41},
  {cont__389_13, &frame__389_5, 1461, 1461, 17, 44},
  {cont__389_14, &frame__389_5, 1461, 1461, 56, 56},
  {entry__397_5, NULL, 1523, 1523, 15, 77},
  {entry__397_2, NULL, 1522, 1522, 16, 33},
  {cont__397_3, &frame__397_2, 1522, 1522, 16, 42},
  {cont__397_4, &frame__397_2, 1522, 1523, 13, 77},
  {cont__397_7, &frame__397_2, 1524, 1524, 13, 19}
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
  arguments->slots[0] = string__236_1;
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
  arguments->slots[0] = string__236_3;
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
  arguments->slots[0] = string__236_5;
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
  arguments->slots[0] = string__236_7;
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
  arguments->slots[0] = string__236_9;
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
  arguments->slots[0] = string__236_11;
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
  arguments->slots[0] = string__236_13;
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
  arguments->slots[0] = string__2_67;
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
  arguments->slots[0] = string__236_16;
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
  arguments->slots[0] = string__236_18;
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
  arguments->slots[0] = string__236_20;
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
  arguments->slots[0] = string__236_22;
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
  arguments->slots[0] = string__236_24;
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
  arguments->slots[0] = string__236_26;
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
  arguments->slots[0] = string__236_28;
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
  arguments->slots[0] = string__236_30;
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
  arguments->slots[0] = string__236_32;
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
  arguments->slots[0] = string__236_34;
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
  arguments->slots[0] = string__236_36;
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
  arguments->slots[0] = string__236_38;
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
  arguments->slots[1] = string__246_3;
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
  arguments->slots[0] = string__264_7;
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
  arguments->slots[1] = string__265_7;
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
  arguments->slots[0] = string__264_7;
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
  arguments->slots[0] = string__264_7;
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
  arguments->slots[0] = string__267_1;
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
  arguments->slots[0] = string__236_3;
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
  arguments->slots[0] = string__268_8;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__268_9;
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
  arguments->slots[0] = string__268_14;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = var._STORE_POSITION;
  arguments->slots[3] = var.sim2c__WHITESPACE;
  arguments->slots[4] = frame->slots[1] /* temp__2 */;
  arguments->slots[5] = string__236_24;
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
  arguments->slots[0] = string__236_38;
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
  // 412:     if defined_namespaces(namespace):
  // 413:       ParseError stream "
  // 414:         the namespace "@(namespace)" is defined twice@
  // 415:     !defined_namespaces(namespace) true
  // 416:     $alias namespace_alias_of(node)
  // 417:     if alias.is_defined:
  // 418:       if namespace_mappings(alias).is_defined:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__269_10;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__269_29;
}
static void entry__269_21(void) {
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
  // 418: ... namespace_mappings(alias)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alias */;
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
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 418: ... namespace_mappings(alias).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__269_23;
}
static void cont__269_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 418: ... :
  // 419:   ParseError stream "
  // 420:     the namespace alias "@(alias)" is defined twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__269_24, 0);
  // 418: if namespace_mappings(alias).is_defined:
  // 419:   ParseError stream "
  // 420:     the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__269_27;
}
static void entry__269_24(void) {
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
  // 419: ... "
  // 420:   the namespace alias "@(alias)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__269_25;
  arguments->slots[1] = frame->slots[1] /* alias */;
  arguments->slots[2] = string__269_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__269_26;
}
static void cont__269_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 419: ParseError stream "
  // 420:   the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__269_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 421: !namespace_mappings(alias) namespace
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* namespace */;
  // 421: !namespace_mappings(alias)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alias */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__269_28;
}
static void cont__269_28(void) {
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
static void entry__269_10(void) {
  allocate_initialized_frame_gc(2, 6);
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
  // 412: ... defined_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  result_count = 1;
  myself = get__defined_namespaces();
  func = myself->type;
  frame->cont = cont__269_12;
}
static void cont__269_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 412: ... :
  // 413:   ParseError stream "
  // 414:     the namespace "@(namespace)" is defined twice@
  frame->slots[5] /* temp__2 */ = create_closure(entry__269_13, 0);
  // 412: if defined_namespaces(namespace):
  // 413:   ParseError stream "
  // 414:     the namespace "@(namespace)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__269_17;
}
static void entry__269_13(void) {
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
  // 413: ... "
  // 414:   the namespace "@(namespace)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__269_14;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__269_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__269_16;
}
static void cont__269_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 413: ParseError stream "
  // 414:   the namespace "@(namespace)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__269_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 415: !defined_namespaces(namespace) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 415: !defined_namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__defined_namespaces();
  func = myself->type;
  frame->cont = cont__269_18;
}
static void cont__269_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_namespaces(arguments->slots[0]);
  // 416: $alias namespace_alias_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_alias_of();
  func = myself->type;
  frame->cont = cont__269_19;
}
static void cont__269_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* alias */, arguments->slots[0]);
  // 417: ... alias.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* alias */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__269_20;
}
static void cont__269_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 417: ... :
  // 418:   if namespace_mappings(alias).is_defined:
  // 419:     ParseError stream "
  // 420:       the namespace alias "@(alias)" is defined twice@
  // 421:   !namespace_mappings(alias) namespace
  frame->slots[5] /* temp__2 */ = create_closure(entry__269_21, 0);
  // 417: if alias.is_defined:
  // 418:   if namespace_mappings(alias).is_defined:
  // 419:     ParseError stream "
  // 420:       the namespace alias "@(alias)" is defined twice@
  // 421:   !namespace_mappings(alias) namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__269_29(void) {
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
  arguments->slots[0] = string__269_30;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = frame->slots[2] /* temp__3 */;
  arguments->slots[5] = string__236_24;
  arguments->slots[6] = frame->slots[7] /* temp__8 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__269_31;
}
static void cont__269_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMESPACE, arguments->slots[0]);
  // 427: set_node(using_instruction)
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
  // 428: capture(namespace_of NAME)
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
  // 430: inspect_node
  // 431:   : (node stream)
  // 432:     $namespace namespace_of(node)
  // 433:     if used_namespaces(namespace):
  // 434:       ParseError stream "
  // 435:         the namespace "@(namespace)" is used twice@
  // 436:     !used_namespaces(namespace) true
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
  // 432: $namespace namespace_of(node)
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
  // 433: ... used_namespaces(namespace)
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
  // 433: ... :
  // 434:   ParseError stream "
  // 435:     the namespace "@(namespace)" is used twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__270_6, 0);
  // 433: if used_namespaces(namespace):
  // 434:   ParseError stream "
  // 435:     the namespace "@(namespace)" is used twice@
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
  // 434: ... "
  // 435:   the namespace "@(namespace)" is used twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__269_14;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__270_7;
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
  // 434: ParseError stream "
  // 435:   the namespace "@(namespace)" is used twice@
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
  // 436: !used_namespaces(namespace) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 436: !used_namespaces(namespace)
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
  // 423: $USING
  // 424:   sequence
  // 425:     "<using"
  // 426:     sim2c::WHITESPACE
  // 427:     set_node(using_instruction)
  // 428:     capture(namespace_of NAME)
  // 429:     ">"
  // 430:     inspect_node
  // 431:       : (node stream)
  // 432:         $namespace namespace_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__270_12;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__236_24;
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
  // 438: ... alt(LETTER DIGIT '_' '.')
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
  // 438: $BASENAME many(alt(LETTER DIGIT '_' '.'))
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
  // 439: ... some("../")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__272_1;
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
  // 439: ... alt('/' "./" some("../"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__267_1;
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
  // 439: ... '/', BASENAME
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
  // 439: ... some('/', BASENAME)
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
  // 439: $C_FILENAME alt('/' "./" some("../")), BASENAME, some('/', BASENAME)
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
  // 445: set_node(include_instruction)
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
  // 446: capture(node::filename_of C_FILENAME)
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
  // 448: inspect_node
  // 449:   : (node stream)
  // 450:     $filename node::filename_of(node)
  // 451:     if included_files(filename):
  // 452:       ParseError stream "
  // 453:         the file "@(filename)" is included twice@
  // 454:     !included_files(filename) true
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
  // 450: $filename node::filename_of(node)
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
  // 451: ... included_files(filename)
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
  // 451: ... :
  // 452:   ParseError stream "
  // 453:     the file "@(filename)" is included twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__273_6, 0);
  // 451: if included_files(filename):
  // 452:   ParseError stream "
  // 453:     the file "@(filename)" is included twice@
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
  // 452: ... "
  // 453:   the file "@(filename)" is included twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__273_7;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__273_8;
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
  // 452: ParseError stream "
  // 453:   the file "@(filename)" is included twice@
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
  // 454: !included_files(filename) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 454: !included_files(filename)
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
  // 441: $INCLUDE
  // 442:   sequence
  // 443:     "<include"
  // 444:     sim2c::WHITESPACE
  // 445:     set_node(include_instruction)
  // 446:     capture(node::filename_of C_FILENAME)
  // 447:     ">"
  // 448:     inspect_node
  // 449:       : (node stream)
  // 450:         $filename node::filename_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__273_13;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__236_24;
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
  // 460: set_node(link_instruction)
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
  // 461: capture(node::filename_of C_FILENAME)
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
  // 463: inspect_node
  // 464:   : (node stream)
  // 465:     $filename node::filename_of(node)
  // 466:     if linked_libraries(filename):
  // 467:       ParseError stream "
  // 468:         the library "@(filename)" is linked twice@
  // 469:     !linked_libraries(filename) true
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
  // 465: $filename node::filename_of(node)
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
  // 466: ... linked_libraries(filename)
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
  // 466: ... :
  // 467:   ParseError stream "
  // 468:     the library "@(filename)" is linked twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__274_6, 0);
  // 466: if linked_libraries(filename):
  // 467:   ParseError stream "
  // 468:     the library "@(filename)" is linked twice@
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
  // 467: ... "
  // 468:   the library "@(filename)" is linked twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__274_7;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__274_8;
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
  // 467: ParseError stream "
  // 468:   the library "@(filename)" is linked twice@
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
  // 469: !linked_libraries(filename) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 469: !linked_libraries(filename)
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
  // 456: $LINK
  // 457:   sequence
  // 458:     "<link"
  // 459:     sim2c::WHITESPACE
  // 460:     set_node(link_instruction)
  // 461:     capture(node::filename_of C_FILENAME)
  // 462:     ">"
  // 463:     inspect_node
  // 464:       : (node stream)
  // 465:         $filename node::filename_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__274_13;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__236_24;
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
  // 471: ... alt(LETTER DIGIT '_' '.' '*' '?')
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
  // 471: $MASK many(alt(LETTER DIGIT '_' '.' '*' '?'))
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
  // 472: ... some("../")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__272_1;
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
  // 472: ... alt('/' "./" some("../"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__267_1;
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
  // 472: ... '/', MASK
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
  // 472: ... some('/', MASK)
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
  // 472: $FILEMASK alt('/' "./" some("../")), MASK, some('/', MASK)
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
  // 478: set_node(data_instruction)
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
  // 479: capture(node::filemask_of FILEMASK)
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
  // 481: inspect_node
  // 482:   : (node stream)
  // 483:     $filemask node::filemask_of(node)
  // 484:     if dependent_data(filemask):
  // 485:       ParseError stream "
  // 486:         the data dependency "@(filemask)" is defined twice@
  // 487:     !dependent_data(filemask) true
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
  // 483: $filemask node::filemask_of(node)
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
  // 484: ... dependent_data(filemask)
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
  // 484: ... :
  // 485:   ParseError stream "
  // 486:     the data dependency "@(filemask)" is defined twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__277_6, 0);
  // 484: if dependent_data(filemask):
  // 485:   ParseError stream "
  // 486:     the data dependency "@(filemask)" is defined twice@
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
  // 485: ... "
  // 486:   the data dependency "@(filemask)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__277_7;
  arguments->slots[1] = frame->slots[1] /* filemask */;
  arguments->slots[2] = string__269_15;
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
  // 485: ParseError stream "
  // 486:   the data dependency "@(filemask)" is defined twice@
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
  // 487: !dependent_data(filemask) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 487: !dependent_data(filemask)
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
  // 474: $DATA
  // 475:   sequence
  // 476:     "<data"
  // 477:     sim2c::WHITESPACE
  // 478:     set_node(data_instruction)
  // 479:     capture(node::filemask_of FILEMASK)
  // 480:     ">"
  // 481:     inspect_node
  // 482:       : (node stream)
  // 483:         $filemask node::filemask_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__277_12;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  arguments->slots[3] = frame->slots[1] /* temp__2 */;
  arguments->slots[4] = string__236_24;
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
  // 491: alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
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
  // 492: ... expect(outdent_marker)
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
  // 492: ... NEXT_LINE_REMARK, expect(outdent_marker)
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
  // 492: ... alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker))
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
  // 492: optional(alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
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
  // 489: $META_INSTRUCTION
  // 490:   sequence
  // 491:     alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
  // 492:     optional(alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
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
  // 497: ... some(PRINTABLE_CHARACTER)
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
  // 497: $REMARK_LINE multi_capture(remark_lines_of some(PRINTABLE_CHARACTER))
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
  // 502: ... interleaved(REMARK_LINE NEWLINE)
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
  // 502: ... expect(outdent_marker)
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
  // 502: ... INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker)
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
  // 502: optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
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
  // 499: $REMARK_LINES
  // 500:   sequence
  // 501:     REMARK_LINE
  // 502:     optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
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
  // 504: ... set_node(remark_statement)
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
  // 504: $SINGLE_REMARK_STATEMENT HASHTAG, set_node(remark_statement), REMARK_LINES
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
  // 506: $REMARK_STATEMENT multi_span(statements_of SINGLE_REMARK_STATEMENT)
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
  // 507: $REMARK HASHTAG, REMARK_LINES
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
  // 512: modify_node
  // 513:   : (&node)
  // 514:     unless node.is_a_definition || node.is_a_meta_instruction:
  // 515:       $remark_lines remark_lines_of(node)
  // 516:       if
  // 517:         arguments_of(node).is_empty:
  // 518:           !node.remark_lines_behind_of remark_lines
  // 519:         :
  // 520:           append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 521:       !node.remark_lines_of empty_list
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
  // 514: ... node.is_a_definition
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
  // 514: ... node.is_a_meta_instruction
  frame->slots[3] /* temp__3 */ = create_closure(entry__284_3, 0);
  // 514: ... node.is_a_definition || node.is_a_meta_instruction
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
  // 514: ... node.is_a_meta_instruction
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
  // 514: ... node.is_a_meta_instruction
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
  // 514: ... :
  // 515:   $remark_lines remark_lines_of(node)
  // 516:   if
  // 517:     arguments_of(node).is_empty:
  // 518:       !node.remark_lines_behind_of remark_lines
  // 519:     :
  // 520:       append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 521:   !node.remark_lines_of empty_list
  frame->slots[4] /* temp__4 */ = create_closure(entry__284_6, 0);
  // 514: unless node.is_a_definition || node.is_a_meta_instruction:
  // 515:   $remark_lines remark_lines_of(node)
  // 516:   if
  // 517:     arguments_of(node).is_empty:
  // 518:       !node.remark_lines_behind_of remark_lines
  // 519:     :
  // 520:       append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 521:   !node.remark_lines_of empty_list
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
  // 515: $remark_lines remark_lines_of(node)
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
  // 517: arguments_of(node)
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
  // 517: arguments_of(node).is_empty
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
  // 517: ... :
  // 518:   !node.remark_lines_behind_of remark_lines
  frame->slots[4] /* temp__3 */ = create_closure(entry__284_10, 0);
  // 519: :
  // 520:   append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  frame->slots[5] /* temp__4 */ = create_closure(entry__284_11, 0);
  // 516: if
  // 517:   arguments_of(node).is_empty:
  // 518:     !node.remark_lines_behind_of remark_lines
  // 519:   :
  // 520:     append &node.arguments_of(-1).remark_lines_behind_of remark_lines
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
  // 518: !node.remark_lines_behind_of remark_lines
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* remark_lines */;
  // 518: !node.remark_lines_behind_of
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
  // 520: ... 1
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
  // 520: ... node.arguments_of
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
  // 520: ... node.arguments_of(-1)
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
  // 520: ... node.arguments_of(-1).remark_lines_behind_of
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
  // 520: append &node.arguments_of(-1).remark_lines_behind_of remark_lines
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
  // 520: ... node.arguments_of
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
  // 520: ... 1
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
  // 520: ... node.arguments_of(-1)
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
  // 520: ... &node.arguments_of(-1).remark_lines_behind_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[9] /* temp__8 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_behind_of, frame->slots[6] /* temp__5 */);
    frame->slots[9] /* temp__8 */ = temp;

  }
  // 520: ... &node.arguments_of(-1)
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
  // 520: ... &node.arguments_of
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
  // 521: !node.remark_lines_of empty_list
  frame->slots[2] /* temp__1 */ = get__empty_list();
  // 521: !node.remark_lines_of
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
  // 509: $REMARK_BEHIND
  // 510:   sequence
  // 511:     REMARK
  // 512:     modify_node
  // 513:       : (&node)
  // 514:         unless node.is_a_definition || node.is_a_meta_instruction:
  // 515:           $remark_lines remark_lines_of(node)
  // 516:           if
  // 517:             arguments_of(node).is_empty:
  // 518:               !node.remark_lines_behind_of remark_lines
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
  // 523: ... sim2c::WHITESPACE, HASHTAG, REMARK_LINE
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
  // 523: $LINE_END_REMARK optional(sim2c::WHITESPACE, HASHTAG, REMARK_LINE)
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
  // 531: modify_node
  // 532:   : (&node)
  // 533:     unless node.is_a_definition:
  // 534:       $n length_of(arguments_of(node))
  // 535:       if n > 0:
  // 536:         push
  // 537:           &node.arguments_of(n).remark_lines_of
  // 538:           remark_lines_of(node)(-1)
  // 539:         range &node.remark_lines_of 1 -2
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
  // 533: ... node.is_a_definition
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
  // 533: ... :
  // 534:   $n length_of(arguments_of(node))
  // 535:   if n > 0:
  // 536:     push
  // 537:       &node.arguments_of(n).remark_lines_of
  // 538:       remark_lines_of(node)(-1)
  // 539:     range &node.remark_lines_of 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__286_3, 0);
  // 533: unless node.is_a_definition:
  // 534:   $n length_of(arguments_of(node))
  // 535:   if n > 0:
  // 536:     push
  // 537:       &node.arguments_of(n).remark_lines_of
  // 538:       remark_lines_of(node)(-1)
  // 539:     range &node.remark_lines_of 1 -2
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
  // 537: ... node.arguments_of
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
  // 537: ... node.arguments_of(n)
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
  // 537: ... node.arguments_of(n).remark_lines_of
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
  // 538: ... 1
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
  // 538: remark_lines_of(node)
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
  // 538: remark_lines_of(node)(-1)
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
  // 536: push
  // 537:   &node.arguments_of(n).remark_lines_of
  // 538:   remark_lines_of(node)(-1)
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
  // 537: ... node.arguments_of
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
  // 537: ... node.arguments_of(n)
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
  // 537: &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[10] /* temp__9 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[8] /* temp__7 */);
    frame->slots[10] /* temp__9 */ = temp;

  }
  // 537: &node.arguments_of(n)
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
  // 537: &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__8 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 539: ... node.remark_lines_of
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
  // 539: ... 2
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
  // 539: range &node.remark_lines_of 1 -2
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
  // 539: ... &node.remark_lines_of
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
  // 534: ... arguments_of(node)
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
  // 534: $n length_of(arguments_of(node))
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
  // 535: ... n > 0
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
  // 535: ... :
  // 536:   push
  // 537:     &node.arguments_of(n).remark_lines_of
  // 538:     remark_lines_of(node)(-1)
  // 539:   range &node.remark_lines_of 1 -2
  frame->slots[3] /* temp__2 */ = create_closure(entry__286_7, 0);
  // 535: if n > 0:
  // 536:   push
  // 537:     &node.arguments_of(n).remark_lines_of
  // 538:     remark_lines_of(node)(-1)
  // 539:   range &node.remark_lines_of 1 -2
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
  // 527: sequence
  // 528:   sim2c::WHITESPACE
  // 529:   HASHTAG
  // 530:   REMARK_LINE
  // 531:   modify_node
  // 532:     : (&node)
  // 533:       unless node.is_a_definition:
  // 534:         $n length_of(arguments_of(node))
  // 535:         if n > 0:
  // 536:           push
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
  // 525: $ARGUMENT_LINE_END_REMARK
  // 526:   optional
  // 527:     sequence
  // 528:       sim2c::WHITESPACE
  // 529:       HASHTAG
  // 530:       REMARK_LINE
  // 531:       modify_node
  // 532:         : (&node)
  // 533:           unless node.is_a_definition:
  // 534:             $n length_of(arguments_of(node))
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
  // 545: modify_node
  // 546:   : (&node)
  // 547:     unless node.is_a_definition:
  // 548:       $n length_of(arguments_of(node))
  // 549:       if n > 0:
  // 550:         push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 551:         range &node.remark_lines_of 1 -2
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
  // 547: ... node.is_a_definition
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
  // 547: ... :
  // 548:   $n length_of(arguments_of(node))
  // 549:   if n > 0:
  // 550:     push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 551:     range &node.remark_lines_of 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__287_3, 0);
  // 547: unless node.is_a_definition:
  // 548:   $n length_of(arguments_of(node))
  // 549:   if n > 0:
  // 550:     push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 551:     range &node.remark_lines_of 1 -2
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
  // 550: ... node.arguments_of
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
  // 550: ... node.arguments_of(n)
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
  // 550: ... node.arguments_of(n).remark_lines_of
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
  // 550: ... 1
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
  // 550: ... remark_lines_of(node)
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
  // 550: ... remark_lines_of(node)(-1)
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
  // 550: push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
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
  // 550: ... node.arguments_of
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
  // 550: ... node.arguments_of(n)
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
  // 550: ... &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[10] /* temp__9 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[8] /* temp__7 */);
    frame->slots[10] /* temp__9 */ = temp;

  }
  // 550: ... &node.arguments_of(n)
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
  // 550: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__8 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 551: ... node.remark_lines_of
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
  // 551: ... 2
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
  // 551: range &node.remark_lines_of 1 -2
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
  // 551: ... &node.remark_lines_of
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
  // 548: ... arguments_of(node)
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
  // 548: $n length_of(arguments_of(node))
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
  // 549: ... n > 0
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
  // 549: ... :
  // 550:   push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 551:   range &node.remark_lines_of 1 -2
  frame->slots[3] /* temp__2 */ = create_closure(entry__287_7, 0);
  // 549: if n > 0:
  // 550:   push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 551:   range &node.remark_lines_of 1 -2
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
  // 541: $ARGUMENT_REMARK
  // 542:   sequence
  // 543:     HASHTAG
  // 544:     REMARK_LINE
  // 545:     modify_node
  // 546:       : (&node)
  // 547:         unless node.is_a_definition:
  // 548:           $n length_of(arguments_of(node))
  // 549:           if n > 0:
  // 550:             push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
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
  // 553: $NEW_LINE_END_REMARK sim2c::WHITESPACE, HASHTAG, REMARK_LINE
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
  // 554: $NEXT_LINE_REMARK INDENT, REMARK
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
  // 562: modify_node
  // 563:   : (node)
  // 564:     ->
  // 565:       function_call
  // 566:         .functor_of node
  // 567:         .fragment_of fragment_of(node)
  // 568:         .source_position_of source_position_of(node)
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
  // 567: ... fragment_of(node)
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
  // 568: ... source_position_of(node)
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
  // 565: function_call
  // 566:   .functor_of node
  // 567:   .fragment_of fragment_of(node)
  // 568:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* node */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 564: ->
  // 565:   function_call
  // 566:     .functor_of node
  // 567:     .fragment_of fragment_of(node)
  // 568:     .source_position_of source_position_of(node)
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
  // 569: ... alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS)
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
  // 569: ... optional(alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS))
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
  // 569: inline(optional(alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS)))
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
  // 570: expect(')')
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
  // 559: $FUNCTION_CALL
  // 560:   sequence
  // 561:     '('
  // 562:     modify_node
  // 563:       : (node)
  // 564:         ->
  // 565:           function_call
  // 566:             .functor_of node
  // 567:             .fragment_of fragment_of(node)
  // 568:             .source_position_of source_position_of(node)
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
  // 573: $MAKE_ATTRIBUTE_ACCESS
  // 574:   modify_node
  // 575:     : (&node)
  // 576:       !node
  // 577:         function_call
  // 578:           .arguments_of list(node)
  // 579:           .is_an_attribute_access true
  // 580:           .fragment_of fragment_of(node)
  // 581:           .source_position_of source_position_of(node)
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
  // 578: ... list(node)
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
  // 580: ... fragment_of(node)
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
  // 581: ... source_position_of(node)
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
  // 576: !node
  // 577:   function_call
  // 578:     .arguments_of list(node)
  // 579:     .is_an_attribute_access true
  // 580:     .fragment_of fragment_of(node)
  // 581:     .source_position_of source_position_of(node)
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
  // 587: span(functor_of IDENTIFIER)
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
  // 583: $ATTRIBUTE_ACCESS
  // 584:   sequence
  // 585:     '.'
  // 586:     MAKE_ATTRIBUTE_ACCESS
  // 587:     span(functor_of IDENTIFIER)
  // 588:     STORE_END_POSITION
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
  // 594: span(functor_of NAME_OF_POLYMORPHIC)
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
  // 590: $ATTRIBUTE_WRITE
  // 591:   sequence
  // 592:     '.'
  // 593:     MAKE_ATTRIBUTE_ACCESS
  // 594:     span(functor_of NAME_OF_POLYMORPHIC)
  // 595:     STORE_END_POSITION
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
  // 597: ... alt(FUNCTION_CALL ATTRIBUTE_ACCESS)
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
  // 597: $EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_ACCESS))
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
  // 598: ... alt(FUNCTION_CALL ATTRIBUTE_WRITE)
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
  // 598: $READ_WRITE_EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_WRITE))
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
  // 599: $IDENTIFIER_OR_FUNCTION_CALL IDENTIFIER, EXTENSIONS
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
  // 602: ... set_field(is_a_destination true)
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
  // 601: $READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 602:   IDENTIFIER, set_field(is_a_destination true), READ_WRITE_EXTENSIONS
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
  // 606: ... many(DIGIT)
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
  // 606: interleaved(many(DIGIT) '@apos;')
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
  // 607: ... many(DIGIT)
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
  // 607: ... '.', many(DIGIT)
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
  // 607: optional('.', many(DIGIT))
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
  // 608: ... alt('e' 'E')
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
  // 608: ... alt('+' '-')
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
  // 608: ... optional(alt('+' '-'))
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
  // 608: ... many(DIGIT)
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
  // 608: ... alt('e' 'E'), optional(alt('+' '-')), many(DIGIT)
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
  // 608: optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
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
  // 604: $DECIMAL_NUMBER
  // 605:   sequence
  // 606:     interleaved(many(DIGIT) '@apos;')
  // 607:     optional('.', many(DIGIT))
  // 608:     optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
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
  // 610: $BINARY_DIGIT alt('0' '1')
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
  // 611: ... many(BINARY_DIGIT)
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
  // 611: ... interleaved(many(BINARY_DIGIT) '@apos;')
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
  // 611: $BINARY_NUMBER "0b", interleaved(many(BINARY_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__300_3;
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
  // 612: $OCTAL_DIGIT '0' .. '7'
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
  // 613: ... many(OCTAL_DIGIT)
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
  // 613: ... interleaved(many(OCTAL_DIGIT) '@apos;')
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
  // 613: $OCTAL_NUMBER "0o", interleaved(many(OCTAL_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__302_3;
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
  // 614: ... 'a' .. 'f'
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
  // 614: ... 'A' .. 'F'
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
  // 614: $HEX_DIGIT alt(DIGIT 'a' .. 'f' 'A' .. 'F')
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
  // 615: ... many(HEX_DIGIT)
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
  // 615: ... interleaved(many(HEX_DIGIT) '@apos;')
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
  // 615: $HEX_NUMBER "0x", interleaved(many(HEX_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__304_3;
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
  // 619: set_node(numeric_literal)
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
  // 623: alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
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
  // 621: capture
  // 622:   node::value_of
  // 623:   alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
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
  // 617: $NUMBER
  // 618:   sequence
  // 619:     set_node(numeric_literal)
  // 620:     STORE_POSITION
  // 621:     capture
  // 622:       node::value_of
  // 623:       alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  // 624:     STORE_END_POSITION
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
  // 628: capture(node::value_of PRINTABLE_CHARACTER)
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
  // 629: modify_node
  // 630:   : (&node)
  // 631:     !node.node::value_of node::value_of(node)(1)
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
  // 631: ... node::value_of(node)
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
  // 631: !node.node::value_of node::value_of(node)(1)
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
  // 631: !node.node::value_of
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
  // 626: $SIMPLE_CHARACTER
  // 627:   sequence
  // 628:     capture(node::value_of PRINTABLE_CHARACTER)
  // 629:     modify_node
  // 630:       : (&node)
  // 631:         !node.node::value_of node::value_of(node)(1)
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
  // 636: modify_node
  // 637:   : (&node)
  // 638:     !node.node::value_of '@@'
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
  // 638: !node.node::value_of '@@'
  frame->slots[1] /* temp__1 */ = character__64;
  // 638: !node.node::value_of
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
  // 633: $AT_CHARACTER
  // 634:   sequence
  // 635:     '@@'
  // 636:     modify_node
  // 637:       : (&node)
  // 638:         !node.node::value_of '@@'
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
  // 642: capture(node::value_of NAME)
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
  // 644: modify_node
  // 645:   :
  // 646:     (
  // 647:       &node
  // 648:       stream
  // 649:     )
  // 650:     $chr character_names(node::value_of(node))
  // 651:     unless chr.is_defined: ParseError stream "invalid character name"
  // 652:     !node.node::value_of chr
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
  // 650: ... node::value_of(node)
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
  // 650: $chr character_names(node::value_of(node))
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
  // 651: ... chr.is_defined
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
  // 651: ... : ParseError stream "invalid character name"
  frame->slots[4] /* temp__2 */ = create_closure(entry__308_6, 0);
  // 651: unless chr.is_defined: ParseError stream "invalid character name"
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
  // 651: ... ParseError stream "invalid character name"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__308_7;
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
  // 652: !node.node::value_of chr
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* chr */;
  // 652: !node.node::value_of
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
  // 640: $NAMED_CHARACTER
  // 641:   sequence
  // 642:     capture(node::value_of NAME)
  // 643:     ';'
  // 644:     modify_node
  // 645:       :
  // 646:         (
  // 647:           &node
  // 648:           stream
  // 649:         )
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
  // 659: ... many(BINARY_DIGIT)
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
  // 659: "0b", many(BINARY_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__300_3;
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
  // 660: ... many(OCTAL_DIGIT)
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
  // 660: "0o", many(OCTAL_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__302_3;
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
  // 661: ... many(HEX_DIGIT)
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
  // 661: "0x", many(HEX_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__304_3;
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
  // 662: many(DIGIT)
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
  // 658: alt
  // 659:   "0b", many(BINARY_DIGIT)
  // 660:   "0o", many(OCTAL_DIGIT)
  // 661:   "0x", many(HEX_DIGIT)
  // 662:   many(DIGIT)
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
  // 656: capture
  // 657:   node::value_of
  // 658:   alt
  // 659:     "0b", many(BINARY_DIGIT)
  // 660:     "0o", many(OCTAL_DIGIT)
  // 661:     "0x", many(HEX_DIGIT)
  // 662:     many(DIGIT)
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
  // 664: modify_node
  // 665:   : (&node)
  // 666:     !node.node::value_of character(node::value_of(node).to_integer)
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
  // 666: ... node::value_of(node)
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
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 666: ... node::value_of(node).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 666: !node.node::value_of character(node::value_of(node).to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
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
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 666: !node.node::value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__value_of, frame->slots[3] /* temp__3 */);
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
  // 654: $NUMERIC_CHARACTER
  // 655:   sequence
  // 656:     capture
  // 657:       node::value_of
  // 658:       alt
  // 659:         "0b", many(BINARY_DIGIT)
  // 660:         "0o", many(OCTAL_DIGIT)
  // 661:         "0x", many(HEX_DIGIT)
  // 662:         many(DIGIT)
  // 663:     ';'
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
  // 673: syntax_error("invalid special character")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__310_1;
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
  // 668: $SPECIAL_CHARACTER
  // 669:   alt
  // 670:     AT_CHARACTER
  // 671:     NAMED_CHARACTER
  // 672:     NUMERIC_CHARACTER
  // 673:     syntax_error("invalid special character")
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
  // 675: ... '@@', SPECIAL_CHARACTER
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
  // 675: $CHARACTER_SYMBOL alt('@@', SPECIAL_CHARACTER SIMPLE_CHARACTER)
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
  // 680: set_node(character_literal)
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
  // 683: expect('@apos;')
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
  // 677: $CHARACTER
  // 678:   sequence
  // 679:     '@apos;'
  // 680:     set_node(character_literal)
  // 681:     STORE_POSITION_MINUS_1
  // 682:     CHARACTER_SYMBOL
  // 683:     expect('@apos;')
  // 684:     STORE_END_POSITION
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
  // 691: modify_node
  // 692:   : (&node)
  // 693:     push &node.node::text_of node::value_of(node)
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
  // 693: ... node.node::text_of
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
  // 693: ... node::value_of(node)
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
  // 693: push &node.node::text_of node::value_of(node)
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
  // 693: ... &node.node::text_of
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
  // 689: sequence
  // 690:   CHARACTER_SYMBOL
  // 691:   modify_node
  // 692:     : (&node)
  // 693:       push &node.node::text_of node::value_of(node)
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
  // 686: $STRING_CHARACTER
  // 687:   alt
  // 688:     "@@;"
  // 689:     sequence
  // 690:       CHARACTER_SYMBOL
  // 691:       modify_node
  // 692:         : (&node)
  // 693:           push &node.node::text_of node::value_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__313_7;
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
  // 698: modify_node
  // 699:   : (&node)
  // 700:     if node::text_of(node) != "":
  // 701:       push &node.arguments_of node(.arguments_of undefined)
  // 702:     !node.node::text_of ""
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
  // 700: ... node::text_of(node)
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
  // 700: ... node::text_of(node) != ""
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
  // 700: ... node::text_of(node) != ""
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
  // 700: ... :
  // 701:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__314_5, 0);
  // 700: if node::text_of(node) != "":
  // 701:   push &node.arguments_of node(.arguments_of undefined)
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
  // 701: ... node.arguments_of
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
  // 701: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 701: push &node.arguments_of node(.arguments_of undefined)
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
  // 701: ... &node.arguments_of
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
  // 702: !node.node::text_of ""
  frame->slots[1] /* temp__1 */ = empty_string;
  // 702: !node.node::text_of
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
  // 703: ... arguments_span(EXPRESSION)
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
  // 703: interleaved(arguments_span(EXPRESSION) sim2c::WHITESPACE)
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
  // 704: expect(')')
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
  // 695: $STRING_INSERTION
  // 696:   sequence
  // 697:     "@@("
  // 698:     modify_node
  // 699:       : (&node)
  // 700:         if node::text_of(node) != "":
  // 701:           push &node.arguments_of node(.arguments_of undefined)
  // 702:         !node.node::text_of ""
  // 703:     interleaved(arguments_span(EXPRESSION) sim2c::WHITESPACE)
  // 704:     expect(')')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__314_13;
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
  // 706: $CHECK_INSERTIONS
  // 707:   modify_node
  // 708:     : (&node)
  // 709:       if length_of(arguments_of(node)) > 0:
  // 710:         if node::text_of(node) != "":
  // 711:           push &node.arguments_of node(.arguments_of undefined)
  // 712:         !node
  // 713:           function_call
  // 714:             .functor_of std_identifier("string")
  // 715:             .arguments_of arguments_of(node)
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
  // 709: ... arguments_of(node)
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
  // 709: ... length_of(arguments_of(node))
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
  // 709: ... length_of(arguments_of(node)) > 0
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
  // 709: ... :
  // 710:   if node::text_of(node) != "":
  // 711:     push &node.arguments_of node(.arguments_of undefined)
  // 712:   !node
  // 713:     function_call
  // 714:       .functor_of std_identifier("string")
  // 715:       .arguments_of arguments_of(node)
  // 716:       .is_a_string_template true
  // 717:       .fragment_of fragment_of(node)
  // 718:       .source_position_of source_position_of(node)
  // ...
  frame->slots[4] /* temp__4 */ = create_closure(entry__315_5, 0);
  // 709: if length_of(arguments_of(node)) > 0:
  // 710:   if node::text_of(node) != "":
  // 711:     push &node.arguments_of node(.arguments_of undefined)
  // 712:   !node
  // 713:     function_call
  // 714:       .functor_of std_identifier("string")
  // 715:       .arguments_of arguments_of(node)
  // 716:       .is_a_string_template true
  // 717:       .fragment_of fragment_of(node)
  // 718:       .source_position_of source_position_of(node)
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
  // 710: ... node::text_of(node)
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
  // 710: ... node::text_of(node) != ""
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
  // 710: ... node::text_of(node) != ""
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
  // 710: ... :
  // 711:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__315_9, 0);
  // 710: if node::text_of(node) != "":
  // 711:   push &node.arguments_of node(.arguments_of undefined)
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
  // 711: ... node.arguments_of
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
  // 711: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 711: push &node.arguments_of node(.arguments_of undefined)
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
  // 711: ... &node.arguments_of
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
  // 714: ... std_identifier("string")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__315_13;
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
  // 715: ... arguments_of(node)
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
  // 717: ... fragment_of(node)
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
  // 718: ... source_position_of(node)
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
  // 719: ... end_position_of(node)
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
  // 712: !node
  // 713:   function_call
  // 714:     .functor_of std_identifier("string")
  // 715:     .arguments_of arguments_of(node)
  // 716:     .is_a_string_template true
  // 717:     .fragment_of fragment_of(node)
  // 718:     .source_position_of source_position_of(node)
  // 719:     .end_position_of end_position_of(node)
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
  // 726: not_followed_by(indent_marker)
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
  // 727: set_node(string_literal)
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
  // 729: ... not_followed_by('@quot;')
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
  // 729: ... alt(STRING_INSERTION STRING_CHARACTER)
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
  // 729: ... not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER)
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
  // 729: some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
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
  // 730: expect('@quot;')
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
  // 721: $STRING
  // 722:   # This code has an astonishing capability to flatten template expressions!
  // 723:   
  // 724:   sequence
  // 725:     '@quot;'
  // 726:     not_followed_by(indent_marker)
  // 727:     set_node(string_literal)
  // 728:     STORE_POSITION_MINUS_1
  // 729:     some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
  // 730:     expect('@quot;')
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
  // 737: ... '@@', OUTDENT
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
  // 737: followed_by('@@', OUTDENT)
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
  // 738: '@@', NEWLINE, STRING_LINE
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
  // 739: STRING_INSERTION, STRING_LINE
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
  // 740: STRING_CHARACTER, STRING_LINE
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
  // 736: alt
  // 737:   followed_by('@@', OUTDENT)
  // 738:   '@@', NEWLINE, STRING_LINE
  // 739:   STRING_INSERTION, STRING_LINE
  // 740:   STRING_CHARACTER, STRING_LINE
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
  // 734: $STRING_LINE
  // 735:   optional
  // 736:     alt
  // 737:       followed_by('@@', OUTDENT)
  // 738:       '@@', NEWLINE, STRING_LINE
  // 739:       STRING_INSERTION, STRING_LINE
  // 740:       STRING_CHARACTER, STRING_LINE
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
  // 742: $ADD_LINE_END
  // 743:   modify_node
  // 744:     : (&node)
  // 745:       append &node.node::text_of line_end_specifier_of(node)
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
  // 745: ... node.node::text_of
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
  // 745: ... line_end_specifier_of(node)
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
  // 745: append &node.node::text_of line_end_specifier_of(node)
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
  // 745: ... &node.node::text_of
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
  // 750: set_node(multi_line_string)
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
  // 754: ... NEWLINE, ADD_LINE_END, STRING_LINE
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
  // 754: some(NEWLINE, ADD_LINE_END, STRING_LINE)
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
  // 755: ... '@@', OUTDENT
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
  // 755: ... expect(outdent_marker)
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
  // 755: ... expect(outdent_marker), ADD_LINE_END
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
  // 755: alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
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
  // 747: $MULTI_LINE_STRING
  // 748:   sequence
  // 749:     '@quot;'
  // 750:     set_node(multi_line_string)
  // 751:     STORE_POSITION_MINUS_1
  // 752:     INDENT
  // 753:     STRING_LINE
  // 754:     some(NEWLINE, ADD_LINE_END, STRING_LINE)
  // 755:     alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
  // 756:     STORE_END_POSITION
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
  // 759: ... not_followed_by(LETTER)
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
  // 759: ... set_node(unique_item)
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
  // 759: $UNIQUE_ITEM '.', not_followed_by(LETTER), set_node(unique_item)
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
  // 764: ... syntax_error("expression expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__321_1;
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
  // 764: ... alt(EXPRESSION BODY syntax_error("expression expected"))
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
  // 764: inline(alt(EXPRESSION BODY syntax_error("expression expected")))
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
  // 765: expect(')')
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
  // 761: $PARENTHESED_EXPRESSION
  // 762:   sequence
  // 763:     '('
  // 764:     inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  // 765:     expect(')')
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
  // 771: modify_node
  // 772:   : (node)
  // 773:     ->
  // 774:       function_call
  // 775:         .functor_of std_identifier("key_value_pair")
  // 776:         .arguments_of list(node std_identifier("true"))
  // 777:         .fragment_of fragment_of(node)
  // 778:         .source_position_of source_position_of(node)+2
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
  // 775: ... std_identifier("key_value_pair")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__322_2;
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
  // 776: ... std_identifier("true")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__322_4;
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
  // 776: ... list(node std_identifier("true"))
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
  // 777: ... fragment_of(node)
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
  // 778: ... source_position_of(node)
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
  // 778: ... source_position_of(node)+2
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
  // 774: function_call
  // 775:   .functor_of std_identifier("key_value_pair")
  // 776:   .arguments_of list(node std_identifier("true"))
  // 777:   .fragment_of fragment_of(node)
  // 778:   .source_position_of source_position_of(node)+2
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__6 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 773: ->
  // 774:   function_call
  // 775:     .functor_of std_identifier("key_value_pair")
  // 776:     .arguments_of list(node std_identifier("true"))
  // 777:     .fragment_of fragment_of(node)
  // 778:     .source_position_of source_position_of(node)+2
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
  // 767: $OPTION
  // 768:   sequence
  // 769:     "--"
  // 770:     IDENTIFIER
  // 771:     modify_node
  // 772:       : (node)
  // 773:         ->
  // 774:           function_call
  // 775:             .functor_of std_identifier("key_value_pair")
  // 776:             .arguments_of list(node std_identifier("true"))
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__322_11;
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
  // 786: modify_node
  // 787:   : (node)
  // 788:     ->
  // 789:       function_call
  // 790:         .functor_of operator_symbol(.name_of "-")
  // 791:         .arguments_of list(node)
  // 792:         .fragment_of fragment_of(node)
  // 793:         .source_position_of source_position_of(node)
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
  // 790: ... operator_symbol(.name_of "-")
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, string__236_7);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 791: ... list(node)
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
  // 792: ... fragment_of(node)
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
  // 793: ... source_position_of(node)
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
  // 789: function_call
  // 790:   .functor_of operator_symbol(.name_of "-")
  // 791:   .arguments_of list(node)
  // 792:   .fragment_of fragment_of(node)
  // 793:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[4] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[5] /* temp__5 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 788: ->
  // 789:   function_call
  // 790:     .functor_of operator_symbol(.name_of "-")
  // 791:     .arguments_of list(node)
  // 792:     .fragment_of fragment_of(node)
  // 793:     .source_position_of source_position_of(node)
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
  // 781: $NEGATION
  // 782:   sequence
  // 783:     '-'
  // 784:     STORE_POSITION_MINUS_1
  // 785:     OPERAND
  // 786:     modify_node
  // 787:       : (node)
  // 788:         ->
  // 789:           function_call
  // 790:             .functor_of operator_symbol(.name_of "-")
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
  // 796: $SIMPLE_OPERAND
  // 797:   alt
  // 798:     NUMBER
  // 799:     CHARACTER
  // 800:     STRING
  // 801:     UNIQUE_ITEM
  // 802:     PARENTHESED_EXPRESSION
  // 803:     OPTION
  // 804:     NEGATION
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
  // 806: ... some(ATTRIBUTE_ACCESS)
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
  // 806: ... SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS)
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
  // 806: $OPERAND alt(IDENTIFIER_OR_FUNCTION_CALL SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS))
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
  // 808: $INFIX_OPERATOR_SYMBOL
  // 809:   alt
  // 810:     '*'
  // 811:     '/'
  // 812:     '+'
  // 813:     '-'
  // 814:     "<<"
  // 815:     "<="
  // 816:     "<"
  // 817:     ">>"
  // ...
  argument_count = 19;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__47;
  arguments->slots[2] = character__43;
  arguments->slots[3] = character__45;
  arguments->slots[4] = string__236_9;
  arguments->slots[5] = string__236_18;
  arguments->slots[6] = string__236_20;
  arguments->slots[7] = string__236_11;
  arguments->slots[8] = string__236_22;
  arguments->slots[9] = string__236_24;
  arguments->slots[10] = string__236_30;
  arguments->slots[11] = character__38;
  arguments->slots[12] = character__94;
  arguments->slots[13] = string__236_32;
  arguments->slots[14] = character__124;
  arguments->slots[15] = string__236_26;
  arguments->slots[16] = character__61;
  arguments->slots[17] = string__236_28;
  arguments->slots[18] = string__236_34;
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
  // 831: ... multi_capture(operators_of INFIX_OPERATOR_SYMBOL)
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
  // 830: $SYMBOLIC_OPERATOR
  // 831:   infix_operator(multi_capture(operators_of INFIX_OPERATOR_SYMBOL))
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
  // 833: ... multi_capture(operators_of ',')
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
  // 833: $COMMA_OPERATOR multi_capture(operators_of ','), sim2c::WHITESPACE
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
  // 839: multi_span(operators_of IDENTIFIER)
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
  // 841: expect(sim2c::WHITESPACE)
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
  // 835: $NAMED_OPERATOR
  // 836:   sequence
  // 837:     sim2c::WHITESPACE
  // 838:     '.'
  // 839:     multi_span(operators_of IDENTIFIER)
  // 840:     '.'
  // 841:     expect(sim2c::WHITESPACE)
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
  // 845: alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
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
  // 846: modify_node
  // 847:   : (&node)
  // 848:     $operator_precedence precedence(operators_of(node)(-1))
  // 849:     $lowest_precedence lowest_precedence_of(node)
  // 850:     if
  // 851:       ||
  // 852:         lowest_precedence.is_undefined
  // 853:         operator_precedence < lowest_precedence
  // 854:       :
  // 855:         !node.lowest_precedence_of operator_precedence
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
  // 848: ... 1
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
  // 848: ... operators_of(node)
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
  // 848: ... operators_of(node)(-1)
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
  // 848: $operator_precedence precedence(operators_of(node)(-1))
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
  // 849: $lowest_precedence lowest_precedence_of(node)
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
  // 852: lowest_precedence.is_undefined
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
  // 853: operator_precedence < lowest_precedence
  frame->slots[5] /* temp__3 */ = create_closure(entry__330_9, 0);
  // 851: ||
  // 852:   lowest_precedence.is_undefined
  // 853:   operator_precedence < lowest_precedence
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
  // 853: operator_precedence < lowest_precedence
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
  // 853: operator_precedence < lowest_precedence
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
  // 854: :
  // 855:   !node.lowest_precedence_of operator_precedence
  frame->slots[6] /* temp__4 */ = create_closure(entry__330_12, 0);
  // 850: if
  // 851:   ||
  // 852:     lowest_precedence.is_undefined
  // 853:     operator_precedence < lowest_precedence
  // 854:   :
  // 855:     !node.lowest_precedence_of operator_precedence
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
  // 855: !node.lowest_precedence_of operator_precedence
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* operator_precedence */;
  // 855: !node.lowest_precedence_of
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
  // 843: $INFIX_OPERATOR
  // 844:   sequence
  // 845:     alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
  // 846:     modify_node
  // 847:       : (&node)
  // 848:         $operator_precedence precedence(operators_of(node)(-1))
  // 849:         $lowest_precedence lowest_precedence_of(node)
  // 850:         if
  // 851:           ||
  // 852:             lowest_precedence.is_undefined
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
  // 857: $EXTEND_EXPRESSION
  // 858:   modify_node
  // 859:     : (&node)
  // 860:       $parent parent_of(node)
  // 861:       $arguments arguments_of(node)
  // 862:       $n length_of(arguments)
  // 863:       if
  // 864:         n == 1:
  // 865:           !node arguments(1)
  // 866:         : # build syntax tree according to operator precedences
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
  // 860: $parent parent_of(node)
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
  // 861: $arguments arguments_of(node)
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
  // 862: $n length_of(arguments)
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
  // 864: n == 1
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
  // 864: ... :
  // 865:   !node arguments(1)
  frame->slots[5] /* temp__2 */ = create_closure(entry__331_6, 0);
  // 866: : # build syntax tree according to operator precedences
  // 867:   $operators operators_of(node)
  // 868:   $$operand_stack list(arguments(1))
  // 869:   $$operator_stack list(operators(1))
  // 870:   
  // 871:   $update_stack: ($right next_operator)
  // 872:     $next_prec
  // 873:       if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 874:     
  // 875:     do: (-> break)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__331_8, 0);
  // 863: if
  // 864:   n == 1:
  // 865:     !node arguments(1)
  // 866:   : # build syntax tree according to operator precedences
  // 867:     $operators operators_of(node)
  // 868:     $$operand_stack list(arguments(1))
  // 869:     $$operator_stack list(operators(1))
  // 870:     
  // 871:     $update_stack: ($right next_operator)
  // 872:       $next_prec
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
  // 865: !node arguments(1)
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
  // 871: ... : ($right next_operator)
  // 872:   $next_prec
  // 873:     if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 874:   
  // 875:   do: (-> break)
  // 876:     forever:
  // 877:       $operator peek(operator_stack)
  // 878:       $prec precedence(operator)
  // 879:       if next_prec > prec break
  // 880:       if next_prec == prec && is_right_associative(prec) break
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__331_9_update_stack, 2);
  // 871: $update_stack: ($right next_operator)
  // 872:   $next_prec
  // 873:     if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 874:   
  // 875:   do: (-> break)
  // 876:     forever:
  // 877:       $operator peek(operator_stack)
  // 878:       $prec precedence(operator)
  // 879:       if next_prec > prec break
  // 880:       if next_prec == prec && is_right_associative(prec) break
  // ...
  initialize_future(frame->slots[6] /* update_stack */, frame->slots[7] /* temp__1 */);
  // 867: $operators operators_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__operators_of();
  func = myself->type;
  frame->cont = cont__331_43;
}
static void entry__331_9_update_stack(void) {
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
  // 873: ... next_operator.is_defined
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
  // 873: ... -> precedence(next_operator)
  frame->slots[6] /* temp__2 */ = create_closure(entry__331_11, 0);
  // 872: $next_prec
  // 873:   if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
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
  // 873: ... precedence(next_operator)
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
  // 873: ... -> precedence(next_operator)
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
  // 873: ... -> 0
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
  // 875: ... : (-> break)
  // 876:   forever:
  // 877:     $operator peek(operator_stack)
  // 878:     $prec precedence(operator)
  // 879:     if next_prec > prec break
  // 880:     if next_prec == prec && is_right_associative(prec) break
  // 881:     
  // 882:     $functor
  // 883:       if
  // 884:         operator.is_a_string
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__331_15, 0);
  // 875: do: (-> break)
  // 876:   forever:
  // 877:     $operator peek(operator_stack)
  // 878:     $prec precedence(operator)
  // 879:     if next_prec > prec break
  // 880:     if next_prec == prec && is_right_associative(prec) break
  // 881:     
  // 882:     $functor
  // 883:       if
  // 884:         operator.is_a_string
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
  // 876: ... :
  // 877:   $operator peek(operator_stack)
  // 878:   $prec precedence(operator)
  // 879:   if next_prec > prec break
  // 880:   if next_prec == prec && is_right_associative(prec) break
  // 881:   
  // 882:   $functor
  // 883:     if
  // 884:       operator.is_a_string
  // 885:       -> operator_symbol(.name_of operator)
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__331_16, 0);
  // 876: forever:
  // 877:   $operator peek(operator_stack)
  // 878:   $prec precedence(operator)
  // 879:   if next_prec > prec break
  // 880:   if next_prec == prec && is_right_associative(prec) break
  // 881:   
  // 882:   $functor
  // 883:     if
  // 884:       operator.is_a_string
  // 885:       -> operator_symbol(.name_of operator)
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
  // 877: $operator peek(operator_stack)
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
  // 878: $prec precedence(operator)
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
  // 879: ... next_prec > prec
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
  // 879: if next_prec > prec break
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
  // 880: ... next_prec == prec
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
  // 880: ... is_right_associative(prec)
  frame->slots[12] /* temp__3 */ = create_closure(entry__331_22, 0);
  // 880: ... next_prec == prec && is_right_associative(prec)
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
  // 880: ... is_right_associative(prec)
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
  // 880: ... is_right_associative(prec)
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
  // 880: if next_prec == prec && is_right_associative(prec) break
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
  // 884: operator.is_a_string
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
  // 885: -> operator_symbol(.name_of operator)
  frame->slots[11] /* temp__2 */ = create_closure(entry__331_27, 0);
  // 886: -> operator
  frame->slots[12] /* temp__3 */ = create_closure(entry__331_28, 0);
  // 882: $functor
  // 883:   if
  // 884:     operator.is_a_string
  // 885:     -> operator_symbol(.name_of operator)
  // 886:     -> operator
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
  // 885: ... operator_symbol(.name_of operator)
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[0] /* operator */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 885: -> operator_symbol(.name_of operator)
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
  // 886: -> operator
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
  // 888: $left pop(&operand_stack)
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
  // 888: ... left
  initialize_future(frame->slots[8] /* left */, frame->slots[10] /* temp__1 */);
  // 892: ... list(left right)
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
  // 894: ... enumeration_no_of(left)
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
  // 895: ... fragment_of(left)
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
  // 896: ... source_position_of(left)
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
  // 897: ... end_position_of(right)
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
  // 889: !right
  // 890:   function_call
  // 891:     .functor_of functor
  // 892:     .arguments_of list(left right)
  // 893:     .is_in_infix_notation true
  // 894:     .enumeration_no_of enumeration_no_of(left)
  // 895:     .fragment_of fragment_of(left)
  // 896:     .source_position_of source_position_of(left)
  // 897:     .end_position_of end_position_of(right)
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
  // 898: pop &operator_stack $_dummy
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
  // 898: ... _dummy
  initialize_future(frame->slots[9] /* dummy */, frame->slots[10] /* temp__1 */);
  // 899: ... length_of(operator_stack)
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
  // 899: ... length_of(operator_stack) == 0
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
  // 899: if length_of(operator_stack) == 0 break
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
  // 900: push &operand_stack right
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
  // 901: push &operator_stack next_operator
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
  // 868: ... arguments(1)
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
  // 868: $$operand_stack list(arguments(1))
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
  // 869: ... operators(1)
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
  // 869: $$operator_stack list(operators(1))
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
  // 903: ... : (i)
  // 904:   update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
  frame->slots[7] /* temp__1 */ = create_closure(entry__331_48, 1);
  // 903: from_to 2 n: (i)
  // 904:   update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
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
  // 904: ... arguments(i)
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
  // 904: ... i < n
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
  // 904: ... -> operators(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__331_51, 0);
  // 904: ... if(i < n (-> operators(i)) -> undefined)
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
  // 904: ... operators(i)
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
  // 904: ... -> operators(i)
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
  // 904: ... -> undefined
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
  // 904: update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
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
  // 905: !node peek(operand_stack)
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
  // 906: ... parent.is_defined
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
  // 906: ... :
  // 907:   !node parent(.arguments_of push(arguments_of(parent) node))
  frame->slots[5] /* temp__2 */ = create_closure(entry__331_59, 0);
  // 906: if parent.is_defined:
  // 907:   !node parent(.arguments_of push(arguments_of(parent) node))
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
  // 907: ... arguments_of(parent)
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
  // 907: ... push(arguments_of(parent) node)
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
  // 907: !node parent(.arguments_of push(arguments_of(parent) node))
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
  // 911: set_node(expression)
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
  // 912: arguments_span(OPERAND)
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
  // 913: ... arguments_span(OPERAND)
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
  // 913: ... INFIX_OPERATOR, arguments_span(OPERAND)
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
  // 913: some(INFIX_OPERATOR, arguments_span(OPERAND))
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
  // 915: ... multi_capture(operators_of '=')
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
  // 915: infix_operator(multi_capture(operators_of '='))
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
  // 915: infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
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
  // 914: optional
  // 915:   infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
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
  // 909: $EXPRESSION
  // 910:   sequence
  // 911:     set_node(expression)
  // 912:     arguments_span(OPERAND)
  // 913:     some(INFIX_OPERATOR, arguments_span(OPERAND))
  // 914:     optional
  // 915:       infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  // 916:     EXTEND_EXPRESSION
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
  // 918: ... span(identifier_of DEFINE_IDENTIFIER)
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
  // 918: $DEFINED_VARIABLE expect(span(identifier_of DEFINE_IDENTIFIER) "identifier")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__333_2;
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
  // 921: ... set_field(is_used_as_a_polymorphic_function true)
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
  // 920: $NAME_OF_POLYMORPHIC
  // 921:   IDENTIFIER, set_field(is_used_as_a_polymorphic_function true)
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
  // 931: set_field(attribute_kind_of ATTRIBUTE_KIND)
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
  // 932: span(attribute_of NAME_OF_POLYMORPHIC)
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
  // 929: sequence
  // 930:   '.'
  // 931:   set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 932:   span(attribute_of NAME_OF_POLYMORPHIC)
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
  // 935: followed_by(':')
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
  // 936: set_field(attribute_kind_of METHOD_KIND)
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
  // 933: sequence
  // 934:   '/'
  // 935:   followed_by(':')
  // 936:   set_field(attribute_kind_of METHOD_KIND)
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
  // 939: set_field(attribute_kind_of METHOD_KIND)
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
  // 940: span(attribute_of NAME_OF_POLYMORPHIC)
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
  // 937: sequence
  // 938:   '/'
  // 939:   set_field(attribute_kind_of METHOD_KIND)
  // 940:   span(attribute_of NAME_OF_POLYMORPHIC)
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
  // 928: alt
  // 929:   sequence
  // 930:     '.'
  // 931:     set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 932:     span(attribute_of NAME_OF_POLYMORPHIC)
  // 933:   sequence
  // 934:     '/'
  // 935:     followed_by(':')
  // 936:     set_field(attribute_kind_of METHOD_KIND)
  // 937:   sequence
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
  // 927: sequence
  // 928:   alt
  // 929:     sequence
  // 930:       '.'
  // 931:       set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 932:       span(attribute_of NAME_OF_POLYMORPHIC)
  // 933:     sequence
  // 934:       '/'
  // 935:       followed_by(':')
  // 936:       set_field(attribute_kind_of METHOD_KIND)
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
  // 926: optional
  // 927:   sequence
  // 928:     alt
  // 929:       sequence
  // 930:         '.'
  // 931:         set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 932:         span(attribute_of NAME_OF_POLYMORPHIC)
  // 933:       sequence
  // 934:         '/'
  // 935:         followed_by(':')
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
  // 923: $DEFINED_VARIABLE_OR_ATTRIBUTE
  // 924:   sequence
  // 925:     DEFINED_VARIABLE
  // 926:     optional
  // 927:       sequence
  // 928:         alt
  // 929:           sequence
  // 930:             '.'
  // 931:             set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 932:             span(attribute_of NAME_OF_POLYMORPHIC)
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
  // 943: ... set_node(define_static_single)
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
  // 942: $DEFINE_STATIC_SINGLE
  // 943:   '$', set_node(define_static_single), DEFINED_VARIABLE_OR_ATTRIBUTE
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
  // 945: ... set_node(define_static_multi)
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
  // 945: $DEFINE_STATIC_MULTI "$$", set_node(define_static_multi), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__337_2;
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
  // 946: ... set_node(define_dynamic_single)
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
  // 946: $DEFINE_DYNAMIC_SINGLE '%', set_node(define_dynamic_single), DEFINED_VARIABLE
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
  // 947: ... set_node(define_dynamic_multi)
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
  // 947: $DEFINE_DYNAMIC_MULTI "%%", set_node(define_dynamic_multi), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__339_2;
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
  // 952: modify_node
  // 953:   : (&node)
  // 954:     !node
  // 955:       function_call
  // 956:         .arguments_of list(node)
  // 957:         .is_an_attribute_access true
  // 958:         .is_a_method_definition true
  // 959:         .fragment_of fragment_of(node)
  // 960:         .source_position_of source_position_of(node)
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
  // 956: ... list(node)
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
  // 959: ... fragment_of(node)
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
  // 960: ... source_position_of(node)
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
  // 954: !node
  // 955:   function_call
  // 956:     .arguments_of list(node)
  // 957:     .is_an_attribute_access true
  // 958:     .is_a_method_definition true
  // 959:     .fragment_of fragment_of(node)
  // 960:     .source_position_of source_position_of(node)
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
  // 961: ... followed_by(':')
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
  // 961: ... span(functor_of NAME_OF_POLYMORPHIC)
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
  // 961: alt(followed_by(':') span(functor_of NAME_OF_POLYMORPHIC))
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
  // 949: $METHOD_DEFINITION
  // 950:   sequence
  // 951:     '/'
  // 952:     modify_node
  // 953:       : (&node)
  // 954:         !node
  // 955:           function_call
  // 956:             .arguments_of list(node)
  // 957:             .is_an_attribute_access true
  // 958:             .is_a_method_definition true
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
  // 964: ... optional(METHOD_DEFINITION)
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
  // 964: $ASSIGN '!', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(METHOD_DEFINITION)
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
  // 966: $DESTINATION
  // 967:   alt
  // 968:     DEFINE_STATIC_MULTI
  // 969:     DEFINE_STATIC_SINGLE
  // 970:     DEFINE_DYNAMIC_MULTI
  // 971:     DEFINE_DYNAMIC_SINGLE
  // 972:     ASSIGN
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
  // 977: set_node(backquoted)
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
  // 978: ... alt(OPERAND DESTINATION)
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
  // 978: ... span(expression_of alt(OPERAND DESTINATION))
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
  // 978: capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
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
  // 974: $BACKQUOTED
  // 975:   sequence
  // 976:     '`'
  // 977:     set_node(backquoted)
  // 978:     capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
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
  // 980: ... alt(EXPRESSION BODY)
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
  // 980: $INPUT_ARGUMENT arguments_span(alt(EXPRESSION BODY))
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
  // 984: ... set_field(is_an_optional_item true)
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
  // 984: '?', set_field(is_an_optional_item true)
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
  // 985: ... set_field(is_an_expanded_item true)
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
  // 985: '*', set_field(is_an_expanded_item true)
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
  // 982: $EXPANSION
  // 983:   alt
  // 984:     '?', set_field(is_an_optional_item true)
  // 985:     '*', set_field(is_an_expanded_item true)
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
  // 987: ... optional(EXPANSION)
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
  // 987: ... DESTINATION, optional(EXPANSION)
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
  // 987: $OUTPUT_ARGUMENT output_arguments_span(DESTINATION, optional(EXPANSION))
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
  // 991: ... optional(EXPANSION)
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
  // 991: '&', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(EXPANSION)
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
  // 989: $INPUT_OUTPUT_ARGUMENT
  // 990:   output_arguments_span
  // 991:     '&', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(EXPANSION)
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
  //  993: $COPY_OUTPUT
  //  994:   #
  //  995:     copy an input-output argument as an additional input argument
  //  996:   
  //  997:   modify_node
  //  998:     : (&node)
  //  999:       push
  // 1000:         &node.arguments_of
  // 1001:         output_arguments_of(node)(-1)(.is_a_destination false)
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
  // 1000: ... node.arguments_of
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
  // 1001: ... 1
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
  // 1001: output_arguments_of(node)
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
  // 1001: output_arguments_of(node)(-1)
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
  // 1001: output_arguments_of(node)(-1)(.is_a_destination false)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[3] /* temp__3 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_a_destination, get__false());
    frame->slots[2] /* temp__2 */ = temp;

  }
  //  999: push
  // 1000:   &node.arguments_of
  // 1001:   output_arguments_of(node)(-1)(.is_a_destination false)
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
  // 1000: &node.arguments_of
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
  // 1003: $MAYBE_SPLIT_INPUT
  // 1004:   #
  // 1005:     split things like
  // 1006:     
  // 1007:     `$var
  // 1008:     
  // 1009:     into an input and an output argument
  // 1010:   
  // 1011:   modify_node
  // 1012:     : (&node)
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
  // 1013: ... 1
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
  // 1013: ... arguments_of(node)
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
  // 1013: $argument arguments_of(node)(-1)
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
  // 1014: $expression expression_of(argument)
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
  // 1015: ... expression.is_a_definition
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
  // 1015: ... expression.is_a_destination
  frame->slots[5] /* temp__3 */ = create_closure(entry__349_7, 0);
  // 1015: ... expression.is_a_definition || expression.is_a_destination
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
  // 1015: ... expression.is_a_destination
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
  // 1015: ... expression.is_a_destination
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
  // 1015: ... :
  // 1016:   push &node.output_arguments_of expression
  // 1017:   !node.arguments_of(-1)
  // 1018:     string_literal(.node::text_of node::text_of(argument))
  frame->slots[6] /* temp__4 */ = create_closure(entry__349_10, 0);
  // 1015: if expression.is_a_definition || expression.is_a_destination:
  // 1016:   push &node.output_arguments_of expression
  // 1017:   !node.arguments_of(-1)
  // 1018:     string_literal(.node::text_of node::text_of(argument))
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
  // 1016: ... node.output_arguments_of
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
  // 1016: push &node.output_arguments_of expression
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
  // 1016: ... &node.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1018: ... node::text_of(argument)
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
  // 1017: !node.arguments_of(-1)
  // 1018:   string_literal(.node::text_of node::text_of(argument))
  {
    NODE *temp = clone_object_and_attributes(get__string_literal());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, frame->slots[3] /* temp__1 */);
    frame->slots[4] /* temp__2 */ = temp;

  }
  // 1017: ... node.arguments_of
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
  // 1017: ... 1
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
  // 1017: !node.arguments_of(-1)
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
  // 1017: !node.arguments_of
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
  // 1022: ... optional(EXPANSION)
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
  // 1022: ... EXPRESSION, optional(EXPANSION)
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
  // 1022: arguments_span(EXPRESSION, optional(EXPANSION))
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
  // 1024: INPUT_OUTPUT_ARGUMENT, COPY_OUTPUT
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
  // 1025: arguments_span(BACKQUOTED)
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
  // 1025: arguments_span(BACKQUOTED), MAYBE_SPLIT_INPUT
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
  // 1020: $SIMPLE_ARGUMENT
  // 1021:   alt
  // 1022:     arguments_span(EXPRESSION, optional(EXPANSION))
  // 1023:     OUTPUT_ARGUMENT
  // 1024:     INPUT_OUTPUT_ARGUMENT, COPY_OUTPUT
  // 1025:     arguments_span(BACKQUOTED), MAYBE_SPLIT_INPUT
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
  // 1033: set_node(attribute_value_pair)
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
  // 1034: span(identifier_of NAME_OF_POLYMORPHIC)
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
  // 1032: sequence
  // 1033:   set_node(attribute_value_pair)
  // 1034:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1035:   sim2c::WHITESPACE
  // 1036:   INPUT_ARGUMENT
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
  // 1031: arguments_span
  // 1032:   sequence
  // 1033:     set_node(attribute_value_pair)
  // 1034:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1035:     sim2c::WHITESPACE
  // 1036:     INPUT_ARGUMENT
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
  // 1029: sequence
  // 1030:   '.'
  // 1031:   arguments_span
  // 1032:     sequence
  // 1033:       set_node(attribute_value_pair)
  // 1034:       span(identifier_of NAME_OF_POLYMORPHIC)
  // 1035:       sim2c::WHITESPACE
  // 1036:       INPUT_ARGUMENT
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
  // 1039: followed_by(':')
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
  // 1041: set_node(attribute_function_pair)
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
  // 1041: set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
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
  // 1040: arguments_span
  // 1041:   set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
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
  // 1037: sequence
  // 1038:   '/'
  // 1039:   followed_by(':')
  // 1040:   arguments_span
  // 1041:     set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
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
  // 1046: set_node(attribute_function_pair)
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
  // 1047: span(identifier_of NAME_OF_POLYMORPHIC)
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
  // 1045: sequence
  // 1046:   set_node(attribute_function_pair)
  // 1047:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1048:   SEPARATOR
  // 1049:   INPUT_ARGUMENT
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
  // 1044: arguments_span
  // 1045:   sequence
  // 1046:     set_node(attribute_function_pair)
  // 1047:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1048:     SEPARATOR
  // 1049:     INPUT_ARGUMENT
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
  // 1042: sequence
  // 1043:   '/'
  // 1044:   arguments_span
  // 1045:     sequence
  // 1046:       set_node(attribute_function_pair)
  // 1047:       span(identifier_of NAME_OF_POLYMORPHIC)
  // 1048:       SEPARATOR
  // 1049:       INPUT_ARGUMENT
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
  // 1027: $INLINE_ATTRIBUTE_VALUE_PAIR
  // 1028:   alt
  // 1029:     sequence
  // 1030:       '.'
  // 1031:       arguments_span
  // 1032:         sequence
  // 1033:           set_node(attribute_value_pair)
  // 1034:           span(identifier_of NAME_OF_POLYMORPHIC)
  // 1035:           sim2c::WHITESPACE
  // 1036:           INPUT_ARGUMENT
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
  // 1053: ... REMARK_BEHIND, NEWLINES
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
  // 1053: some(REMARK_BEHIND, NEWLINES)
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
  // 1059: set_node(attribute_value_pair)
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
  // 1060: span(identifier_of NAME_OF_POLYMORPHIC)
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
  // 1058: sequence
  // 1059:   set_node(attribute_value_pair)
  // 1060:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1061:   SINGLE_INPUT_ARGUMENT
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
  // 1057: arguments_span
  // 1058:   sequence
  // 1059:     set_node(attribute_value_pair)
  // 1060:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1061:     SINGLE_INPUT_ARGUMENT
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
  // 1055: sequence
  // 1056:   '.'
  // 1057:   arguments_span
  // 1058:     sequence
  // 1059:       set_node(attribute_value_pair)
  // 1060:       span(identifier_of NAME_OF_POLYMORPHIC)
  // 1061:       SINGLE_INPUT_ARGUMENT
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
  // 1064: followed_by(':')
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
  // 1065: ... set_node(attribute_function_pair)
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
  // 1065: ... set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT
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
  // 1065: arguments_span(set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT)
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
  // 1062: sequence
  // 1063:   '/'
  // 1064:   followed_by(':')
  // 1065:   arguments_span(set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT)
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
  // 1070: set_node(attribute_function_pair)
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
  // 1071: span(identifier_of NAME_OF_POLYMORPHIC)
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
  // 1069: sequence
  // 1070:   set_node(attribute_function_pair)
  // 1071:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1072:   SINGLE_INPUT_ARGUMENT
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
  // 1068: arguments_span
  // 1069:   sequence
  // 1070:     set_node(attribute_function_pair)
  // 1071:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1072:     SINGLE_INPUT_ARGUMENT
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
  // 1066: sequence
  // 1067:   '/'
  // 1068:   arguments_span
  // 1069:     sequence
  // 1070:       set_node(attribute_function_pair)
  // 1071:       span(identifier_of NAME_OF_POLYMORPHIC)
  // 1072:       SINGLE_INPUT_ARGUMENT
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
  // 1054: alt
  // 1055:   sequence
  // 1056:     '.'
  // 1057:     arguments_span
  // 1058:       sequence
  // 1059:         set_node(attribute_value_pair)
  // 1060:         span(identifier_of NAME_OF_POLYMORPHIC)
  // 1061:         SINGLE_INPUT_ARGUMENT
  // 1062:   sequence
  // 1063:     '/'
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
  // 1051: $ATTRIBUTE_VALUE_PAIR
  // 1052:   sequence
  // 1053:     some(REMARK_BEHIND, NEWLINES)
  // 1054:     alt
  // 1055:       sequence
  // 1056:         '.'
  // 1057:         arguments_span
  // 1058:           sequence
  // 1059:             set_node(attribute_value_pair)
  // 1060:             span(identifier_of NAME_OF_POLYMORPHIC)
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
  // 1074: $INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1075:   interleaved(INLINE_ATTRIBUTE_VALUE_PAIR sim2c::WHITESPACE)
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
  // 1078: ... interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE)
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
  // 1078: ... expect(outdent_marker)
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
  // 1077: $INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1078:   INDENT, interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE), expect(outdent_marker)
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
  // 1081: ... LINE_START_ARGUMENT, ARGUMENT_LINE_END_REMARK
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
  // 1080: $SINGLE_EXPRESSION_LINE
  // 1081:   alt(LINE_START_ARGUMENT, ARGUMENT_LINE_END_REMARK LINE_END_EXPRESSION)
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
  // 1088: ... SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS
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
  // 1088: alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
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
  // 1086: sequence
  // 1087:   SEPARATOR
  // 1088:   alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
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
  // 1094: some(NEWLINE)
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
  // 1096: expect(outdent_marker)
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
  // 1092: sequence
  // 1093:   INDENT
  // 1094:   some(NEWLINE)
  // 1095:   FIRST_LINE_START_ARGUMENTS
  // 1096:   expect(outdent_marker)
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
  // 1091: optional
  // 1092:   sequence
  // 1093:     INDENT
  // 1094:     some(NEWLINE)
  // 1095:     FIRST_LINE_START_ARGUMENTS
  // 1096:     expect(outdent_marker)
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
  // 1089: sequence
  // 1090:   LINE_END_REMARK
  // 1091:   optional
  // 1092:     sequence
  // 1093:       INDENT
  // 1094:       some(NEWLINE)
  // 1095:       FIRST_LINE_START_ARGUMENTS
  // 1096:       expect(outdent_marker)
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
  // 1085: alt
  // 1086:   sequence
  // 1087:     SEPARATOR
  // 1088:     alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
  // 1089:   sequence
  // 1090:     LINE_END_REMARK
  // 1091:     optional
  // 1092:       sequence
  // 1093:         INDENT
  // 1094:         some(NEWLINE)
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
  // 1083: $PROCEDURE_ARGUMENTS
  // 1084:   optional
  // 1085:     alt
  // 1086:       sequence
  // 1087:         SEPARATOR
  // 1088:         alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
  // 1089:       sequence
  // 1090:         LINE_END_REMARK
  // 1091:         optional
  // 1092:           sequence
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
  // 1102: ... SEPARATOR, ARGUMENT_REMARK
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
  // 1102: optional(SEPARATOR, ARGUMENT_REMARK)
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
  // 1103: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  // 1103: optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1100: sequence
  // 1101:   LINE_END_EXPRESSION
  // 1102:   optional(SEPARATOR, ARGUMENT_REMARK)
  // 1103:   optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1106: ... SEPARATOR, ARGUMENTS
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
  // 1106: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  // 1106: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1106: alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
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
  // 1104: sequence
  // 1105:   SIMPLE_ARGUMENT
  // 1106:   alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
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
  // 1107: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  // 1107: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1107: sequence(ARGUMENT_REMARK optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
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
  // 1098: $ARGUMENTS
  // 1099:   alt
  // 1100:     sequence
  // 1101:       LINE_END_EXPRESSION
  // 1102:       optional(SEPARATOR, ARGUMENT_REMARK)
  // 1103:       optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  // 1104:     sequence
  // 1105:       SIMPLE_ARGUMENT
  // 1106:       alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  // 1107:     sequence(ARGUMENT_REMARK optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
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
  // 1111: ... arguments_span(OPERAND)
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
  // 1111: sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
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
  // 1109: $OPERATORS_AND_OPERANDS
  // 1110:   alt
  // 1111:     sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
  // 1112:     EXTEND_EXPRESSION
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
  // 1118: modify_node
  // 1119:   : (node)
  // 1120:     -> function_call(.parent_of node)
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
  // 1120: ... function_call(.parent_of node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parent_of, frame->slots[0] /* node */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1120: -> function_call(.parent_of node)
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
  // 1121: ... interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE)
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
  // 1121: alt(LINE_START_ARGUMENTS interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE))
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
  // 1123: expect(outdent_marker)
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
  // 1124: modify_node
  // 1125:   : (node)
  // 1126:     # rotate the subnodes to generate the correct function call argument
  // 1127:     
  // 1128:     $top_level_node parent_of(node)
  // 1129:     $top_level_arguments arguments_of(top_level_node)
  // 1130:     $functor top_level_arguments(-1)
  // 1131:     
  // 1132:     $new_arguments
  // 1133:       push
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
  // 1128: $top_level_node parent_of(node)
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
  // 1129: $top_level_arguments arguments_of(top_level_node)
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
  // 1130: ... 1
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
  // 1130: $functor top_level_arguments(-1)
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
  // 1134: ... 2
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
  // 1134: range(top_level_arguments 1 -2)
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
  // 1137: functor
  // 1138:   .enumeration_no_of undefined
  // 1139:   .remark_lines_of empty_list
  {
    NODE *temp = clone_object_and_attributes(frame->slots[3] /* functor */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__enumeration_no_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, get__empty_list());
    frame->slots[8] /* temp__4 */ = temp;

  }
  // 1140: ... arguments_of(node)
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
  // 1141: ... output_arguments_of(node)
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
  // 1142: ... enumeration_no_of(functor)
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
  // 1143: ... remark_lines_of(functor)
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
  // 1144: ... fragment_of(functor)
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
  // 1145: ... source_position_of(functor)
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
  // 1146: ... end_position_of(node)
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
  // 1135: function_call
  // 1136:   .functor_of
  // 1137:     functor
  // 1138:       .enumeration_no_of undefined
  // 1139:       .remark_lines_of empty_list
  // 1140:   .arguments_of arguments_of(node)
  // 1141:   .output_arguments_of output_arguments_of(node)
  // 1142:   .enumeration_no_of enumeration_no_of(functor)
  // 1143:   .remark_lines_of remark_lines_of(functor)
  // 1144:   .fragment_of fragment_of(functor)
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
  // 1132: $new_arguments
  // 1133:   push
  // 1134:     range(top_level_arguments 1 -2)
  // 1135:     function_call
  // 1136:       .functor_of
  // 1137:         functor
  // 1138:           .enumeration_no_of undefined
  // 1139:           .remark_lines_of empty_list
  // 1140:       .arguments_of arguments_of(node)
  // 1141:       .output_arguments_of output_arguments_of(node)
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
  // 1148: ... top_level_node(.arguments_of new_arguments)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* top_level_node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* new_arguments */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 1148: -> top_level_node(.arguments_of new_arguments)
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
  // 1114: $MULTI_LINE_FUNCTION_CALL
  // 1115:   # store the current node in the parent slot for later retrieval
  // 1116:   
  // 1117:   sequence
  // 1118:     modify_node
  // 1119:       : (node)
  // 1120:         -> function_call(.parent_of node)
  // 1121:     alt(LINE_START_ARGUMENTS interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE))
  // 1122:     STORE_END_POSITION
  // 1123:     expect(outdent_marker)
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
  // 1156: modify_node
  // 1157:   : (&node)
  // 1158:     !node.original_remark_lines_of remark_lines_of(node)
  // 1159:     !node.remark_lines_of empty_list
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
  // 1158: !node.original_remark_lines_of remark_lines_of(node)
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
  // 1158: !node.original_remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__original_remark_lines_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1159: !node.remark_lines_of empty_list
  frame->slots[1] /* temp__1 */ = get__empty_list();
  // 1159: !node.remark_lines_of
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
  // 1161: modify_node
  // 1162:   : (&node)
  // 1163:     $n length_of(arguments_of(node))
  // 1164:     if n > 0:
  // 1165:       append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1166:       !node.remark_lines_of empty_list
  // 1167:     !node.remark_lines_of original_remark_lines_of(node)
  // 1168:     !node.original_remark_lines_of undefined
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
  // 1163: ... arguments_of(node)
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
  // 1163: $n length_of(arguments_of(node))
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
  // 1164: ... n > 0
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
  // 1164: ... :
  // 1165:   append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1166:   !node.remark_lines_of empty_list
  frame->slots[3] /* temp__2 */ = create_closure(entry__361_8, 0);
  // 1164: if n > 0:
  // 1165:   append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1166:   !node.remark_lines_of empty_list
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
  // 1165: ... node.arguments_of
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
  // 1165: ... node.arguments_of(n)
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
  // 1165: ... node.arguments_of(n).remark_lines_of
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
  // 1165: ... remark_lines_of(node)
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
  // 1165: append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
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
  // 1165: ... node.arguments_of
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
  // 1165: ... node.arguments_of(n)
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
  // 1165: ... &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[8] /* temp__7 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[6] /* temp__5 */);
    frame->slots[8] /* temp__7 */ = temp;

  }
  // 1165: ... &node.arguments_of(n)
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
  // 1165: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__6 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1166: !node.remark_lines_of empty_list
  frame->slots[2] /* temp__1 */ = get__empty_list();
  // 1166: !node.remark_lines_of
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
  // 1167: !node.remark_lines_of original_remark_lines_of(node)
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
  // 1167: !node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1168: !node.original_remark_lines_of undefined
  frame->slots[2] /* temp__1 */ = get__undefined();
  // 1168: !node.original_remark_lines_of
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
  // 1169: ... sequence(NEWLINES INDENTED_FUNCTION_CALL_OR_REMARK)
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
  // 1169: alt(sequence(NEWLINES INDENTED_FUNCTION_CALL_OR_REMARK) OUTDENT)
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
  // 1154: sequence
  // 1155:   # ATTENTION: very dirty fix!
  // 1156:   modify_node
  // 1157:     : (&node)
  // 1158:       !node.original_remark_lines_of remark_lines_of(node)
  // 1159:       !node.remark_lines_of empty_list
  // 1160:   REMARK
  // 1161:   modify_node
  // 1162:     : (&node)
  // 1163:       $n length_of(arguments_of(node))
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
  // 1152: $INDENTED_FUNCTION_CALL_OR_REMARK
  // 1153:   alt
  // 1154:     sequence
  // 1155:       # ATTENTION: very dirty fix!
  // 1156:       modify_node
  // 1157:         : (&node)
  // 1158:           !node.original_remark_lines_of remark_lines_of(node)
  // 1159:           !node.remark_lines_of empty_list
  // 1160:       REMARK
  // 1161:       modify_node
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
  // 1173: ... some(NEWLINE)
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
  // 1172: $MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK
  // 1173:   INDENT, some(NEWLINE), INDENTED_FUNCTION_CALL_OR_REMARK
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
  // 1176: ... alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT)
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
  // 1176: ... followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT))
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
  // 1176: ... '*', followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT))
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
  // 1175: $ARGUMENT_EXPANSION
  // 1176:   alt('?' '*', followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT)))
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
  // 1180: set_node(operator_symbol)
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
  // 1182: capture(name_of INFIX_OPERATOR_SYMBOL)
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
  // 1183: modify_node
  // 1184:   : (node)
  // 1185:     ->
  // 1186:       function_call
  // 1187:         .functor_of node
  // 1188:         .fragment_of fragment_of(node)
  // 1189:         .source_position_of source_position_of(node)
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
  // 1188: ... fragment_of(node)
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
  // 1189: ... source_position_of(node)
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
  // 1186: function_call
  // 1187:   .functor_of node
  // 1188:   .fragment_of fragment_of(node)
  // 1189:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* node */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1185: ->
  // 1186:   function_call
  // 1187:     .functor_of node
  // 1188:     .fragment_of fragment_of(node)
  // 1189:     .source_position_of source_position_of(node)
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
  // 1193: expect(outdent_marker)
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
  // 1194: modify_node
  // 1195:   :
  // 1196:     (
  // 1197:       &node
  // 1198:       stream
  // 1199:       -> return
  // 1200:     )
  // 1201:     $$arguments arguments_of(node)
  // 1202:     if length_of(arguments) < 2:
  // 1203:       ParseError stream "too few arguments in multi-line expression"
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
  // 1201: $$arguments arguments_of(node)
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
  // 1202: ... length_of(arguments)
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
  // 1202: ... length_of(arguments) < 2
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
  // 1202: ... :
  // 1203:   ParseError stream "too few arguments in multi-line expression"
  frame->slots[6] /* temp__3 */ = create_closure(entry__364_12, 0);
  // 1202: if length_of(arguments) < 2:
  // 1203:   ParseError stream "too few arguments in multi-line expression"
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
  // 1203: ParseError stream "too few arguments in multi-line expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__364_13;
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
  // 1204: ... length_of(arguments)
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
  // 1204: ... length_of(arguments) > 2
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
  // 1204: ... :
  // 1205:   $functor functor_of(node)
  // 1206:   if
  // 1207:     precedence(name_of(functor)).is_left_associative:
  // 1208:       forever:
  // 1209:         !node
  // 1210:           function_call
  // 1211:             .functor_of functor
  // 1212:             .arguments_of range(arguments 1 2)
  // 1213:         if length_of(arguments) == 2 return
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__364_17, 0);
  // 1204: if length_of(arguments) > 2:
  // 1205:   $functor functor_of(node)
  // 1206:   if
  // 1207:     precedence(name_of(functor)).is_left_associative:
  // 1208:       forever:
  // 1209:         !node
  // 1210:           function_call
  // 1211:             .functor_of functor
  // 1212:             .arguments_of range(arguments 1 2)
  // 1213:         if length_of(arguments) == 2 return
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
  // 1220: ... 2
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
  // 1220: ... 1
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
  // 1220: ... range(arguments -2 -1)
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
  // 1217: !node
  // 1218:   function_call
  // 1219:     .functor_of functor
  // 1220:     .arguments_of range(arguments -2 -1)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1221: ... length_of(arguments)
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
  // 1221: ... length_of(arguments) == 2
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
  // 1221: if length_of(arguments) == 2 return
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
  // 1222: ... 3
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
  // 1222: ... range(arguments 1 -3)
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
  // 1222: !arguments push(range(arguments 1 -3) node)
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
  // 1212: ... range(arguments 1 2)
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
  // 1209: !node
  // 1210:   function_call
  // 1211:     .functor_of functor
  // 1212:     .arguments_of range(arguments 1 2)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1213: ... length_of(arguments)
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
  // 1213: ... length_of(arguments) == 2
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
  // 1213: if length_of(arguments) == 2 return
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
  // 1214: ... 1
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
  // 1214: ... range(arguments 3 -1)
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
  // 1214: !arguments put(range(arguments 3 -1) node)
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
  // 1208: ... :
  // 1209:   !node
  // 1210:     function_call
  // 1211:       .functor_of functor
  // 1212:       .arguments_of range(arguments 1 2)
  // 1213:   if length_of(arguments) == 2 return
  // 1214:   !arguments put(range(arguments 3 -1) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__364_23, 0);
  // 1208: forever:
  // 1209:   !node
  // 1210:     function_call
  // 1211:       .functor_of functor
  // 1212:       .arguments_of range(arguments 1 2)
  // 1213:   if length_of(arguments) == 2 return
  // 1214:   !arguments put(range(arguments 3 -1) node)
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
  // 1216: ... :
  // 1217:   !node
  // 1218:     function_call
  // 1219:       .functor_of functor
  // 1220:       .arguments_of range(arguments -2 -1)
  // 1221:   if length_of(arguments) == 2 return
  // 1222:   !arguments push(range(arguments 1 -3) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__364_32, 0);
  // 1216: forever:
  // 1217:   !node
  // 1218:     function_call
  // 1219:       .functor_of functor
  // 1220:       .arguments_of range(arguments -2 -1)
  // 1221:   if length_of(arguments) == 2 return
  // 1222:   !arguments push(range(arguments 1 -3) node)
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
  // 1205: $functor functor_of(node)
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
  // 1207: ... name_of(functor)
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
  // 1207: precedence(name_of(functor))
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
  // 1207: precedence(name_of(functor)).is_left_associative
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
  // 1207: ... :
  // 1208:   forever:
  // 1209:     !node
  // 1210:       function_call
  // 1211:         .functor_of functor
  // 1212:         .arguments_of range(arguments 1 2)
  // 1213:     if length_of(arguments) == 2 return
  // 1214:     !arguments put(range(arguments 3 -1) node)
  frame->slots[7] /* temp__4 */ = create_closure(entry__364_22, 0);
  // 1215: :
  // 1216:   forever:
  // 1217:     !node
  // 1218:       function_call
  // 1219:         .functor_of functor
  // 1220:         .arguments_of range(arguments -2 -1)
  // 1221:     if length_of(arguments) == 2 return
  // 1222:     !arguments push(range(arguments 1 -3) node)
  frame->slots[8] /* temp__5 */ = create_closure(entry__364_31, 0);
  // 1206: if
  // 1207:   precedence(name_of(functor)).is_left_associative:
  // 1208:     forever:
  // 1209:       !node
  // 1210:         function_call
  // 1211:           .functor_of functor
  // 1212:           .arguments_of range(arguments 1 2)
  // 1213:       if length_of(arguments) == 2 return
  // 1214:       !arguments put(range(arguments 3 -1) node)
  // 1215:   :
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
  // 1178: $MULTI_LINE_EXPRESSION
  // 1179:   sequence
  // 1180:     set_node(operator_symbol)
  // 1181:     STORE_POSITION
  // 1182:     capture(name_of INFIX_OPERATOR_SYMBOL)
  // 1183:     modify_node
  // 1184:       : (node)
  // 1185:         ->
  // 1186:           function_call
  // 1187:             .functor_of node
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
  // 1228: ... not_followed_by(ARGUMENT_EXPANSION)
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
  // 1228: IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
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
  // 1227: arguments_span
  // 1228:   IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
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
  // 1234: optional(sim2c::WHITESPACE)
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
  // 1234: optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
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
  // 1236: sim2c::WHITESPACE, '.'
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
  // 1237: NAME, '.'
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
  // 1233: alt
  // 1234:   optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1235:   ','
  // 1236:   sim2c::WHITESPACE, '.'
  // 1237:   NAME, '.'
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
  // 1232: followed_by
  // 1233:   alt
  // 1234:     optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1235:     ','
  // 1236:     sim2c::WHITESPACE, '.'
  // 1237:     NAME, '.'
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
  // 1238: modify_node
  // 1239:   : (node)
  // 1240:     # store the current node in the parent slot for later retrieval
  // 1241:     
  // 1242:     ->
  // 1243:       expression
  // 1244:         .parent_of
  // 1245:           node(.arguments_of range(arguments_of(node) 1 -2))
  // 1246:         .arguments_of list(arguments_of(node)(-1))
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
  // 1245: ... arguments_of(node)
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
  // 1245: ... 2
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
  // 1245: ... range(arguments_of(node) 1 -2)
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
  // 1245: node(.arguments_of range(arguments_of(node) 1 -2))
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 1246: ... 1
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
  // 1246: ... arguments_of(node)
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
  // 1246: ... arguments_of(node)(-1)
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
  // 1246: ... list(arguments_of(node)(-1))
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
  // 1243: expression
  // 1244:   .parent_of
  // 1245:     node(.arguments_of range(arguments_of(node) 1 -2))
  // 1246:   .arguments_of list(arguments_of(node)(-1))
  {
    NODE *temp = clone_object_and_attributes(get__expression());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parent_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__6 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1242: ->
  // 1243:   expression
  // 1244:     .parent_of
  // 1245:       node(.arguments_of range(arguments_of(node) 1 -2))
  // 1246:     .arguments_of list(arguments_of(node)(-1))
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
  // 1231: sequence
  // 1232:   followed_by
  // 1233:     alt
  // 1234:       optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1235:       ','
  // 1236:       sim2c::WHITESPACE, '.'
  // 1237:       NAME, '.'
  // 1238:   modify_node
  // 1239:     : (node)
  // 1240:       # store the current node in the parent slot for later retrieval
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
  // 1250: ... NEXT_LINE, LINE_START_ARGUMENTS
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
  // 1250: optional(NEXT_LINE, LINE_START_ARGUMENTS)
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
  // 1248: sequence
  // 1249:   MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK
  // 1250:   optional(NEXT_LINE, LINE_START_ARGUMENTS)
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
  // 1230: alt
  // 1231:   sequence
  // 1232:     followed_by
  // 1233:       alt
  // 1234:         optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1235:         ','
  // 1236:         sim2c::WHITESPACE, '.'
  // 1237:         NAME, '.'
  // 1238:     modify_node
  // 1239:       : (node)
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
  // 1229: optional
  // 1230:   alt
  // 1231:     sequence
  // 1232:       followed_by
  // 1233:         alt
  // 1234:           optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1235:           ','
  // 1236:           sim2c::WHITESPACE, '.'
  // 1237:           NAME, '.'
  // 1238:       modify_node
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
  // 1226: sequence
  // 1227:   arguments_span
  // 1228:     IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  // 1229:   optional
  // 1230:     alt
  // 1231:       sequence
  // 1232:         followed_by
  // 1233:           alt
  // 1234:             optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1235:             ','
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
  // 1251: ... not_followed_by(ARGUMENT_EXPANSION)
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
  // 1251: ... EXPRESSION, not_followed_by(ARGUMENT_EXPANSION)
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
  // 1251: arguments_span(EXPRESSION, not_followed_by(ARGUMENT_EXPANSION))
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
  // 1252: arguments_span(MULTI_LINE_EXPRESSION)
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
  // 1224: $LINE_START_ARGUMENT
  // 1225:   alt
  // 1226:     sequence
  // 1227:       arguments_span
  // 1228:         IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  // 1229:       optional
  // 1230:         alt
  // 1231:           sequence
  // 1232:             followed_by
  // 1233:               alt
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
  // 1256: ... NEXT_LINE, MORE_LINE_START_ARGUMENTS
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
  // 1256: ... optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
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
  // 1256: LINE_END_EXPRESSION, optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
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
  // 1258: alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
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
  // 1259: ... SEPARATOR, ARGUMENTS
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
  // 1259: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  // 1259: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1259: alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
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
  // 1257: sequence
  // 1258:   alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
  // 1259:   alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
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
  // 1254: $LINE_START_ARGUMENTS
  // 1255:   alt
  // 1256:     LINE_END_EXPRESSION, optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
  // 1257:     sequence
  // 1258:       alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
  // 1259:       alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
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
  // 1263: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  // 1263: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1263: REMARK_BEHIND, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1261: $MORE_LINE_START_ARGUMENTS
  // 1262:   alt
  // 1263:     REMARK_BEHIND, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  // 1264:     LINE_START_ARGUMENTS
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
  // 1268: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  // 1268: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1268: REMARK, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
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
  // 1266: $FIRST_LINE_START_ARGUMENTS
  // 1267:   alt
  // 1268:     REMARK, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  // 1269:     LINE_START_ARGUMENTS
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
  // 1273: sim2c::WHITESPACE, INPUT_ARGUMENT, LINE_END_REMARK
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
  // 1274: SEPARATOR, LINE_END_EXPRESSION
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
  // 1278: ... REMARK, NEWLINES
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
  // 1278: some(REMARK, NEWLINES)
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
  // 1279: alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
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
  // 1280: expect(outdent_marker)
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
  // 1275: sequence
  // 1276:   LINE_END_REMARK
  // 1277:   INDENT
  // 1278:   some(REMARK, NEWLINES)
  // 1279:   alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
  // 1280:   expect(outdent_marker)
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
  // 1271: $SINGLE_INPUT_ARGUMENT
  // 1272:   alt
  // 1273:     sim2c::WHITESPACE, INPUT_ARGUMENT, LINE_END_REMARK
  // 1274:     SEPARATOR, LINE_END_EXPRESSION
  // 1275:     sequence
  // 1276:       LINE_END_REMARK
  // 1277:       INDENT
  // 1278:       some(REMARK, NEWLINES)
  // 1279:       alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
  // 1280:       expect(outdent_marker)
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
  // 1287: set_node(define_static_multi)
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
  // 1288: set_field(parameter_kind_of IN_PARAMETER)
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
  // 1285: sequence
  // 1286:   '$'
  // 1287:   set_node(define_static_multi)
  // 1288:   set_field(parameter_kind_of IN_PARAMETER)
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
  // 1291: set_node(define_static_multi)
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
  // 1292: set_field(parameter_kind_of OUT_PARAMETER)
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
  // 1289: sequence
  // 1290:   '!'
  // 1291:   set_node(define_static_multi)
  // 1292:   set_field(parameter_kind_of OUT_PARAMETER)
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
  // 1295: set_node(define_static_multi)
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
  // 1296: set_field(parameter_kind_of IN_OUT_PARAMETER)
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
  // 1293: sequence
  // 1294:   '&'
  // 1295:   set_node(define_static_multi)
  // 1296:   set_field(parameter_kind_of IN_OUT_PARAMETER)
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
  // 1297: set_node(define_static_single)
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
  // 1297: ... set_field(parameter_kind_of IN_PARAMETER)
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
  // 1297: set_node(define_static_single), set_field(parameter_kind_of IN_PARAMETER)
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
  // 1284: alt
  // 1285:   sequence
  // 1286:     '$'
  // 1287:     set_node(define_static_multi)
  // 1288:     set_field(parameter_kind_of IN_PARAMETER)
  // 1289:   sequence
  // 1290:     '!'
  // 1291:     set_node(define_static_multi)
  // 1292:     set_field(parameter_kind_of OUT_PARAMETER)
  // 1293:   sequence
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
  // 1282: $PARAMETER_MODE
  // 1283:   optional
  // 1284:     alt
  // 1285:       sequence
  // 1286:         '$'
  // 1287:         set_node(define_static_multi)
  // 1288:         set_field(parameter_kind_of IN_PARAMETER)
  // 1289:       sequence
  // 1290:         '!'
  // 1291:         set_node(define_static_multi)
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
  // 1304: infix_operator('=')
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
  // 1305: set_field(is_an_optional_item true)
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
  // 1306: span(default_value_of EXPRESSION)
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
  // 1303: sequence
  // 1304:   infix_operator('=')
  // 1305:   set_field(is_an_optional_item true)
  // 1306:   span(default_value_of EXPRESSION)
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
  // 1307: ... set_field(parameter_kind_of MYSELF_PARAMETER)
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
  // 1307: '^', set_field(parameter_kind_of MYSELF_PARAMETER)
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
  // 1301: alt
  // 1302:   EXPANSION
  // 1303:   sequence
  // 1304:     infix_operator('=')
  // 1305:     set_field(is_an_optional_item true)
  // 1306:     span(default_value_of EXPRESSION)
  // 1307:   '^', set_field(parameter_kind_of MYSELF_PARAMETER)
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
  // 1299: $PARAMETER_COUNT_OR_MYSELF
  // 1300:   optional
  // 1301:     alt
  // 1302:       EXPANSION
  // 1303:       sequence
  // 1304:         infix_operator('=')
  // 1305:         set_field(is_an_optional_item true)
  // 1306:         span(default_value_of EXPRESSION)
  // 1307:       '^', set_field(parameter_kind_of MYSELF_PARAMETER)
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
  // 1312: modify_node
  // 1313:   : (&node)
  // 1314:     !node.is_not_used true
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
  // 1314: !node.is_not_used true
  frame->slots[1] /* temp__1 */ = get__true();
  // 1314: !node.is_not_used
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
  // 1309: $NOT_USED
  // 1310:   sequence
  // 1311:     '_'
  // 1312:     modify_node
  // 1313:       : (&node)
  // 1314:         !node.is_not_used true
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
  // 1320: set_node(identifier)
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
  // 1322: optional(NOT_USED)
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
  // 1323: capture(name_of NAME)
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
  // 1319: sequence
  // 1320:   set_node(identifier)
  // 1321:   STORE_POSITION
  // 1322:   optional(NOT_USED)
  // 1323:   capture(name_of NAME)
  // 1324:   STORE_END_POSITION
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
  // 1316: $PARAMETER_NAME
  // 1317:   span
  // 1318:     identifier_of
  // 1319:     sequence
  // 1320:       set_node(identifier)
  // 1321:       STORE_POSITION
  // 1322:       optional(NOT_USED)
  // 1323:       capture(name_of NAME)
  // 1324:       STORE_END_POSITION
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
  // 1326: $PARAMETER PARAMETER_MODE, PARAMETER_NAME, PARAMETER_COUNT_OR_MYSELF
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
  // 1329: ... INDENT, REMARK, OUTDENT
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
  // 1329: ... optional(INDENT, REMARK, OUTDENT)
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
  // 1328: $MULTI_LINE_PARAMETER
  // 1329:   PARAMETER, ARGUMENT_LINE_END_REMARK, optional(INDENT, REMARK, OUTDENT)
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
  // 1335: set_node(define_static_single)
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
  // 1336: set_field(parameter_kind_of CONTINUATION_PARAMETER)
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
  // 1331: $CONTINUATION
  // 1332:   sequence
  // 1333:     "->"
  // 1334:     sim2c::WHITESPACE
  // 1335:     set_node(define_static_single)
  // 1336:     set_field(parameter_kind_of CONTINUATION_PARAMETER)
  // 1337:     PARAMETER_NAME
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__376_3;
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
  // 1340: ... INDENT, REMARK, OUTDENT
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
  // 1340: ... optional(INDENT, REMARK, OUTDENT)
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
  // 1339: $MULTI_LINE_CONTINUATION
  // 1340:   CONTINUATION, ARGUMENT_LINE_END_REMARK, optional(INDENT, REMARK, OUTDENT)
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
  // 1348: ... multi_span(parameters_of PARAMETER)
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
  // 1348: interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
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
  // 1349: ... multi_span(parameters_of CONTINUATION)
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
  // 1349: ... sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION)
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
  // 1349: optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
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
  // 1347: sequence
  // 1348:   interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1349:   optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
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
  // 1350: multi_span(parameters_of CONTINUATION)
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
  // 1346: alt
  // 1347:   sequence
  // 1348:     interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1349:     optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1350:   multi_span(parameters_of CONTINUATION)
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
  // 1345: optional
  // 1346:   alt
  // 1347:     sequence
  // 1348:       interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1349:       optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1350:     multi_span(parameters_of CONTINUATION)
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
  // 1351: expect(')')
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
  // 1342: $INLINE_PARAMETERS
  // 1343:   sequence
  // 1344:     '('
  // 1345:     optional
  // 1346:       alt
  // 1347:         sequence
  // 1348:           interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1349:           optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1350:         multi_span(parameters_of CONTINUATION)
  // 1351:     expect(')')
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
  // 1359: ... multi_span(parameters_of MULTI_LINE_PARAMETER)
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
  // 1359: interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
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
  // 1360: ... multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  // 1360: ... NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  // 1360: optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
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
  // 1358: sequence
  // 1359:   interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1360:   optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
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
  // 1361: multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  // 1357: alt
  // 1358:   sequence
  // 1359:     interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1360:     optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  // 1361:   multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  // 1362: expect(outdent_marker)
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
  // 1363: expect(newline)
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
  // 1364: expect(')')
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
  // 1353: $MULTI_LINE_PARAMETERS
  // 1354:   sequence
  // 1355:     '('
  // 1356:     INDENT
  // 1357:     alt
  // 1358:       sequence
  // 1359:         interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1360:         optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  // 1361:       multi_span(parameters_of MULTI_LINE_CONTINUATION)
  // 1362:     expect(outdent_marker)
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
  // 1369: set_node(body)
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
  // 1371: optional(NEW_LINE_END_REMARK)
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
  // 1376: ... REMARK, NEWLINES
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
  // 1376: some(REMARK, NEWLINES)
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
  // 1380: expect(outdent_marker)
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
  // 1374: sequence
  // 1375:   INDENT
  // 1376:   some(REMARK, NEWLINES)
  // 1377:   MULTI_LINE_PARAMETERS
  // 1378:   NEWLINES
  // 1379:   STATEMENTS
  // 1380:   expect(outdent_marker)
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
  // 1382: ... sim2c::WHITESPACE, INLINE_PARAMETERS
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
  // 1382: optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
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
  // 1385: ... optional(NEWLINES)
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
  // 1385: ... expect(outdent_marker)
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
  // 1385: INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
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
  // 1388: ... syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__380_12;
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
  // 1388: alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
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
  // 1386: sequence
  // 1387:   sim2c::WHITESPACE
  // 1388:   alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
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
  // 1389: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__380_12;
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
  // 1384: alt
  // 1385:   INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
  // 1386:   sequence
  // 1387:     sim2c::WHITESPACE
  // 1388:     alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  // 1389:   syntax_error("statement expected")
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
  // 1381: sequence
  // 1382:   optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
  // 1383:   LINE_END_REMARK
  // 1384:   alt
  // 1385:     INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
  // 1386:     sequence
  // 1387:       sim2c::WHITESPACE
  // 1388:       alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  // 1389:     syntax_error("statement expected")
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
  // 1390: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__380_12;
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
  // 1373: alt
  // 1374:   sequence
  // 1375:     INDENT
  // 1376:     some(REMARK, NEWLINES)
  // 1377:     MULTI_LINE_PARAMETERS
  // 1378:     NEWLINES
  // 1379:     STATEMENTS
  // 1380:     expect(outdent_marker)
  // 1381:   sequence
  // 1382:     optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
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
  // 1372: sequence
  // 1373:   alt
  // 1374:     sequence
  // 1375:       INDENT
  // 1376:       some(REMARK, NEWLINES)
  // 1377:       MULTI_LINE_PARAMETERS
  // 1378:       NEWLINES
  // 1379:       STATEMENTS
  // 1380:       expect(outdent_marker)
  // 1381:     sequence
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
  // 1366: $COMPLETE_BODY
  // 1367:   sequence
  // 1368:     ':'
  // 1369:     set_node(body)
  // 1370:     STORE_POSITION_MINUS_1
  // 1371:     optional(NEW_LINE_END_REMARK)
  // 1372:     sequence
  // 1373:       alt
  // 1374:         sequence
  // 1375:           INDENT
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
  // 1395: followed_by("->")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__376_3;
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
  // 1396: set_node(body)
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
  // 1393: $RETURN_EXPRESSION
  // 1394:   sequence
  // 1395:     followed_by("->")
  // 1396:     set_node(body)
  // 1397:     STORE_POSITION
  // 1398:     RETURN_STATEMENT
  // 1399:     STORE_END_POSITION
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
  // 1401: $BODY alt(COMPLETE_BODY RETURN_EXPRESSION)
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
  // 1406: set_node(c_body)
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
  // 1408: expect(indent_marker)
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
  // 1409: ... not_followed_by(OUTDENT)
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
  // 1409: ... not_followed_by(OUTDENT), ANY_CHARACTER
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
  // 1409: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
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
  // 1409: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
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
  // 1410: expect(outdent_marker)
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
  // 1411: expect(newline)
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
  // 1412: expect('}')
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
  // 1403: $C_BODY
  // 1404:   sequence
  // 1405:     '{'
  // 1406:     set_node(c_body)
  // 1407:     STORE_POSITION_MINUS_1
  // 1408:     expect(indent_marker)
  // 1409:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  // 1410:     expect(outdent_marker)
  // 1411:     expect(newline)
  // 1412:     expect('}')
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
  // 1415: ... alt(BODY C_BODY MULTI_LINE_STRING)
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
  // 1415: $LINE_END_EXPRESSION arguments_span(alt(BODY C_BODY MULTI_LINE_STRING))
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
  // 1418: set_node(assignment)
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
  // 1421: output_arguments_span(DEFINE_STATIC_MULTI)
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
  // 1421: output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
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
  // 1423: output_arguments_span(DEFINE_STATIC_SINGLE)
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
  // 1422: sequence
  // 1423:   output_arguments_span(DEFINE_STATIC_SINGLE) SINGLE_INPUT_ARGUMENT
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
  // 1424: output_arguments_span(DEFINE_DYNAMIC_MULTI)
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
  // 1424: output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
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
  // 1425: output_arguments_span(DEFINE_DYNAMIC_SINGLE)
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
  // 1425: output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
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
  // 1427: output_arguments_span(ASSIGN)
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
  // 1428: alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
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
  // 1426: sequence
  // 1427:   output_arguments_span(ASSIGN)
  // 1428:   alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
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
  // 1420: alt
  // 1421:   output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1422:   sequence
  // 1423:     output_arguments_span(DEFINE_STATIC_SINGLE) SINGLE_INPUT_ARGUMENT
  // 1424:   output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1425:   output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
  // 1426:   sequence
  // 1427:     output_arguments_span(ASSIGN)
  // 1428:     alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
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
  // 1416: $ASSIGNMENT
  // 1417:   sequence
  // 1418:     set_node(assignment)
  // 1419:     STORE_POSITION
  // 1420:     alt
  // 1421:       output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1422:       sequence
  // 1423:         output_arguments_span(DEFINE_STATIC_SINGLE) SINGLE_INPUT_ARGUMENT
  // 1424:       output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1425:       output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
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
  // 1432: ... set_node(polymorphic_function)
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
  // 1431: $POLYMORPHIC_FUNCTION_WITHOUT_SETTER
  // 1432:   "()", set_node(polymorphic_function)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__386_2;
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
  // 1435: ... set_node(polymorphic_function_with_setter)
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
  // 1434: $POLYMORPHIC_FUNCTION_WITH_SETTER
  // 1435:   "(!)", set_node(polymorphic_function_with_setter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__387_2;
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
  // 1441: alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
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
  // 1440: arguments_span
  // 1441:   alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
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
  // 1437: $POLYMORPHIC_FUNCTION
  // 1438:   sequence
  // 1439:     sim2c::WHITESPACE
  // 1440:     arguments_span
  // 1441:       alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
  // 1442:     LINE_END_REMARK
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
  // 1446: set_node(assignment)
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
  // 1449: output_arguments_span(DEFINE_STATIC_MULTI)
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
  // 1449: output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
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
  // 1451: output_arguments_span(DEFINE_STATIC_SINGLE)
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
  // 1455: modify_node
  // 1456:   : (&node)
  // 1457:     $$destination output_arguments_of(node)(1)
  // 1458:     if attribute_of(destination).is_defined:
  // 1459:       SyntaxError node "invalid polymorphic function definition"
  // 1460:     !destination.variable_kind_of POLYMORPHIC
  // 1461:     !node.output_arguments_of(1) destination
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
  // 1457: ... output_arguments_of(node)
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
  // 1457: $$destination output_arguments_of(node)(1)
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
  // 1458: ... attribute_of(destination)
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
  // 1458: ... attribute_of(destination).is_defined
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
  // 1458: ... :
  // 1459:   SyntaxError node "invalid polymorphic function definition"
  frame->slots[4] /* temp__3 */ = create_closure(entry__389_10, 0);
  // 1458: if attribute_of(destination).is_defined:
  // 1459:   SyntaxError node "invalid polymorphic function definition"
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
  // 1459: SyntaxError node "invalid polymorphic function definition"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  arguments->slots[1] = string__389_11;
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
  // 1460: !destination.variable_kind_of POLYMORPHIC
  frame->slots[2] /* temp__1 */ = get__POLYMORPHIC();
  // 1460: !destination.variable_kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* destination */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* destination */ = temp;

  }
  // 1461: !node.output_arguments_of(1) destination
  frame->slots[2] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* destination */;
  // 1461: ... node.output_arguments_of
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
  // 1461: !node.output_arguments_of(1)
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
  // 1461: !node.output_arguments_of
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
  // 1453: sequence
  // 1454:   POLYMORPHIC_FUNCTION
  // 1455:   modify_node
  // 1456:     : (&node)
  // 1457:       $$destination output_arguments_of(node)(1)
  // 1458:       if attribute_of(destination).is_defined:
  // 1459:         SyntaxError node "invalid polymorphic function definition"
  // 1460:       !destination.variable_kind_of POLYMORPHIC
  // 1461:       !node.output_arguments_of(1) destination
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
  // 1452: alt
  // 1453:   sequence
  // 1454:     POLYMORPHIC_FUNCTION
  // 1455:     modify_node
  // 1456:       : (&node)
  // 1457:         $$destination output_arguments_of(node)(1)
  // 1458:         if attribute_of(destination).is_defined:
  // 1459:           SyntaxError node "invalid polymorphic function definition"
  // 1460:         !destination.variable_kind_of POLYMORPHIC
  // 1461:         !node.output_arguments_of(1) destination
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
  // 1450: sequence
  // 1451:   output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1452:   alt
  // 1453:     sequence
  // 1454:       POLYMORPHIC_FUNCTION
  // 1455:       modify_node
  // 1456:         : (&node)
  // 1457:           $$destination output_arguments_of(node)(1)
  // 1458:           if attribute_of(destination).is_defined:
  // 1459:             SyntaxError node "invalid polymorphic function definition"
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
  // 1463: output_arguments_span(DEFINE_DYNAMIC_MULTI)
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
  // 1463: output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
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
  // 1464: output_arguments_span(DEFINE_DYNAMIC_SINGLE)
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
  // 1464: output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
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
  // 1466: output_arguments_span(ASSIGN)
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
  // 1467: alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
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
  // 1465: sequence
  // 1466:   output_arguments_span(ASSIGN)
  // 1467:   alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
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
  // 1448: alt
  // 1449:   output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1450:   sequence
  // 1451:     output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1452:     alt
  // 1453:       sequence
  // 1454:         POLYMORPHIC_FUNCTION
  // 1455:         modify_node
  // 1456:           : (&node)
  // 1457:             $$destination output_arguments_of(node)(1)
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
  // 1444: $TOP_LEVEL_ASSIGNMENT
  // 1445:   sequence
  // 1446:     set_node(assignment)
  // 1447:     STORE_POSITION
  // 1448:     alt
  // 1449:       output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1450:       sequence
  // 1451:         output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1452:         alt
  // 1453:           sequence
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
  // 1470: $FUNCTOR span(functor_of IDENTIFIER_OR_FUNCTION_CALL)
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
  // 1474: ... span(result_count_of EXPRESSION)
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
  // 1474: ".(", span(result_count_of EXPRESSION), ')'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__391_2;
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
  // 1475: ... span(continuation_of IDENTIFIER)
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
  // 1475: '/', span(continuation_of IDENTIFIER)
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
  // 1472: $RESULT_COUNT_OR_CONTINUATION
  // 1473:   alt
  // 1474:     ".(", span(result_count_of EXPRESSION), ')'
  // 1475:     '/', span(continuation_of IDENTIFIER)
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
  // 1479: set_node(procedure_call)
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
  // 1482: optional(RESULT_COUNT_OR_CONTINUATION)
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
  // 1491: optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
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
  // 1488: sequence
  // 1489:   sim2c::WHITESPACE
  // 1490:   INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1491:   optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
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
  // 1487: alt
  // 1488:   sequence
  // 1489:     sim2c::WHITESPACE
  // 1490:     INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1491:     optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1492:   INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1493:   PROCEDURE_ARGUMENTS
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
  // 1484: sequence
  // 1485:   sim2c::WHITESPACE
  // 1486:   OUTPUT_ARGUMENT
  // 1487:   alt
  // 1488:     sequence
  // 1489:       sim2c::WHITESPACE
  // 1490:       INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1491:       optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1492:     INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1493:     PROCEDURE_ARGUMENTS
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
  // 1483: alt
  // 1484:   sequence
  // 1485:     sim2c::WHITESPACE
  // 1486:     OUTPUT_ARGUMENT
  // 1487:     alt
  // 1488:       sequence
  // 1489:         sim2c::WHITESPACE
  // 1490:         INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1491:         optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1492:       INDENTED_ATTRIBUTE_VALUE_PAIRS
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
  // 1477: $PROCEDURE_CALL
  // 1478:   sequence
  // 1479:     set_node(procedure_call)
  // 1480:     STORE_POSITION
  // 1481:     FUNCTOR
  // 1482:     optional(RESULT_COUNT_OR_CONTINUATION)
  // 1483:     alt
  // 1484:       sequence
  // 1485:         sim2c::WHITESPACE
  // 1486:         OUTPUT_ARGUMENT
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
  // 1497: ... interleaved(REMARK NEWLINES)
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
  // 1497: $INDENTED_REMARKS INDENT, interleaved(REMARK NEWLINES), OUTDENT
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
  // 1501: alt(ASSIGNMENT PROCEDURE_CALL)
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
  // 1501: ... optional(INDENTED_REMARKS)
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
  // 1501: alt(ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
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
  // 1499: $SINGLE_STATEMENT
  // 1500:   alt
  // 1501:     alt(ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
  // 1502:     SINGLE_REMARK_STATEMENT
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
  // 1506: alt(TOP_LEVEL_ASSIGNMENT PROCEDURE_CALL)
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
  // 1506: ... optional(INDENTED_REMARKS)
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
  // 1506: alt(TOP_LEVEL_ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
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
  // 1504: $TOP_LEVEL_STATEMENT
  // 1505:   alt
  // 1506:     alt(TOP_LEVEL_ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
  // 1507:     SINGLE_REMARK_STATEMENT
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
  // 1509: $STATEMENT multi_span(statements_of SINGLE_STATEMENT)
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
  // 1517: set_node(return_statement)
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
  // 1520: check_node
  // 1521:   : (node)
  // 1522:     if arguments_of(node).is_empty:
  // 1523:       SyntaxError node "return statement needs at least one argument"
  // 1524:     -> true
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
  // 1522: ... arguments_of(node)
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
  // 1522: ... arguments_of(node).is_empty
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
  // 1522: ... :
  // 1523:   SyntaxError node "return statement needs at least one argument"
  frame->slots[3] /* temp__3 */ = create_closure(entry__397_5, 0);
  // 1522: if arguments_of(node).is_empty:
  // 1523:   SyntaxError node "return statement needs at least one argument"
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
  // 1523: SyntaxError node "return statement needs at least one argument"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  arguments->slots[1] = string__397_6;
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
  // 1524: -> true
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
  // 1516: sequence
  // 1517:   set_node(return_statement)
  // 1518:   STORE_POSITION_MINUS_2
  // 1519:   PROCEDURE_ARGUMENTS
  // 1520:   check_node
  // 1521:     : (node)
  // 1522:       if arguments_of(node).is_empty:
  // 1523:         SyntaxError node "return statement needs at least one argument"
  // 1524:       -> true
  // 1525:   STORE_END_POSITION
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
  // 1514: multi_span
  // 1515:   statements_of
  // 1516:   sequence
  // 1517:     set_node(return_statement)
  // 1518:     STORE_POSITION_MINUS_2
  // 1519:     PROCEDURE_ARGUMENTS
  // 1520:     check_node
  // 1521:       : (node)
  // 1522:         if arguments_of(node).is_empty:
  // 1523:           SyntaxError node "return statement needs at least one argument"
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
  // 1511: $RETURN_STATEMENT
  // 1512:   sequence
  // 1513:     "->"
  // 1514:     multi_span
  // 1515:       statements_of
  // 1516:       sequence
  // 1517:         set_node(return_statement)
  // 1518:         STORE_POSITION_MINUS_2
  // 1519:         PROCEDURE_ARGUMENTS
  // 1520:         check_node
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__376_3;
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
  // 1530: interleaved(STATEMENT NEXT_LINE)
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
  // 1530: ... NEXT_LINE, RETURN_STATEMENT
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
  // 1530: ... optional(NEXT_LINE, RETURN_STATEMENT)
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
  // 1530: interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
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
  // 1532: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__380_12;
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
  // 1529: alt
  // 1530:   interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
  // 1531:   RETURN_STATEMENT
  // 1532:   syntax_error("statement expected")
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
  // 1533: ... NEXT_LINE, REMARK_STATEMENT
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
  // 1533: some(NEXT_LINE, REMARK_STATEMENT)
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
  // 1527: $STATEMENTS
  // 1528:   sequence
  // 1529:     alt
  // 1530:       interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
  // 1531:       RETURN_STATEMENT
  // 1532:       syntax_error("statement expected")
  // 1533:     some(NEXT_LINE, REMARK_STATEMENT)
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
  // 1538: set_node(identifier)
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
  // 1538: ... "__", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__399_2;
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
  // 1538: ... many("__", NAME)
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
  // 1538: ... NAME, many("__", NAME)
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
  // 1538: ... capture(name_of NAME, many("__", NAME))
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
  // 1538: set_node(identifier), capture(name_of NAME, many("__", NAME))
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
  // 1535: $BUILTIN_NAME
  // 1536:   span
  // 1537:     identifier_of
  // 1538:     set_node(identifier), capture(name_of NAME, many("__", NAME))
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
  // 1540: ... not_followed_by('>')
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
  // 1540: ... not_followed_by('>'), ANY_CHARACTER
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
  // 1540: $C_EXPRESSION many(not_followed_by('>'), ANY_CHARACTER)
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
  // 1545: ... multi_capture(arguments_of C_EXPRESSION)
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
  // 1545: ... sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION)
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
  // 1545: expect(sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
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
  // 1542: $ARGUMENT_ANNOTATION
  // 1543:   sequence
  // 1544:     "argument"
  // 1545:     expect(sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__401_4;
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
  // 1548: ... span(base_of NAMESPACED_IDENTIFIER)
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
  // 1548: ... sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER)
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
  // 1548: ... expect(sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
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
  // 1547: $BASE_ANNOTATION
  // 1548:   "base", expect(sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__402_4;
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
  // 1550: ... capture(kind_of NAME)
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
  // 1550: ... sim2c::WHITESPACE, capture(kind_of NAME)
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
  // 1550: ... expect(sim2c::WHITESPACE, capture(kind_of NAME))
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
  // 1550: $KIND_ANNOTATION "kind", expect(sim2c::WHITESPACE, capture(kind_of NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__403_4;
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
  // 1555: ... alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
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
  // 1555: ... sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
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
  // 1555: expect(sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE))
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
  // 1552: $NAME_ANNOTATION
  // 1553:   sequence
  // 1554:     "name"
  // 1555:     expect(sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__404_4;
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
  // 1557: ... capture(node_of NAME)
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
  // 1557: ... sim2c::WHITESPACE, capture(node_of NAME)
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
  // 1557: ... expect(sim2c::WHITESPACE, capture(node_of NAME))
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
  // 1557: $NODE_ANNOTATION "node", expect(sim2c::WHITESPACE, capture(node_of NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__405_4;
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
  // 1565: ... alt("runtime" "global" "local" "extern")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__406_1;
  arguments->slots[1] = string__406_2;
  arguments->slots[2] = string__406_3;
  arguments->slots[3] = string__406_4;
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
  // 1565: capture(node::scope_of alt("runtime" "global" "local" "extern"))
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
  // 1563: sequence
  // 1564:   sim2c::WHITESPACE
  // 1565:   capture(node::scope_of alt("runtime" "global" "local" "extern"))
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
  // 1562: expect
  // 1563:   sequence
  // 1564:     sim2c::WHITESPACE
  // 1565:     capture(node::scope_of alt("runtime" "global" "local" "extern"))
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
  // 1559: $SCOPE_ANNOTATION
  // 1560:   sequence
  // 1561:     "scope"
  // 1562:     expect
  // 1563:       sequence
  // 1564:         sim2c::WHITESPACE
  // 1565:         capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__406_9;
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
  // 1568: ... span(node::type_of NAMESPACED_IDENTIFIER)
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
  // 1568: ... sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER)
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
  // 1568: ... expect(sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
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
  // 1567: $TYPE_ANNOTATION
  // 1568:   "type", expect(sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__407_4;
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
  // 1579: syntax_error("invalid annotation tag")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__408_1;
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
  // 1570: $ANNOTATION_ITEM
  // 1571:   alt
  // 1572:     ARGUMENT_ANNOTATION
  // 1573:     BASE_ANNOTATION
  // 1574:     KIND_ANNOTATION
  // 1575:     NAME_ANNOTATION
  // 1576:     NODE_ANNOTATION
  // 1577:     SCOPE_ANNOTATION
  // 1578:     TYPE_ANNOTATION
  // 1579:     syntax_error("invalid annotation tag")
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
  // 1581: ... expect('>')
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
  // 1581: $ANNOTATION '<', ANNOTATION_ITEM, expect('>')
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
  // 1582: $ANNOTATIONS interleaved(ANNOTATION NEWLINES)
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
  // 1583: $C_CODE_REMARK "//", REMARK_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__411_1;
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
  // 1584: ... followed_by(OUTDENT)
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
  // 1584: ... alt(NEWLINES followed_by(OUTDENT))
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
  // 1584: ... C_CODE_REMARK, alt(NEWLINES followed_by(OUTDENT))
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
  // 1584: $C_CODE_REMARKS some(C_CODE_REMARK, alt(NEWLINES followed_by(OUTDENT)))
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
  // 1589: ... not_followed_by(OUTDENT)
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
  // 1589: ... not_followed_by(OUTDENT), ANY_CHARACTER
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
  // 1589: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
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
  // 1589: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
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
  // 1586: $SOURCE
  // 1587:   sequence
  // 1588:     C_CODE_REMARKS
  // 1589:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
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
  // 1594: set_node(c_code)
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
  // 1595: expect(indent_marker)
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
  // 1596: ... NEWLINES, SOURCE
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
  // 1596: ... optional(NEWLINES, SOURCE)
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
  // 1596: ... ANNOTATIONS, optional(NEWLINES, SOURCE)
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
  // 1596: alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
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
  // 1597: expect(outdent_marker)
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
  // 1598: expect(newline)
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
  // 1599: expect('}')
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
  // 1591: $C_CODE
  // 1592:   sequence
  // 1593:     '{'
  // 1594:     set_node(c_code)
  // 1595:     expect(indent_marker)
  // 1596:     alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
  // 1597:     expect(outdent_marker)
  // 1598:     expect(newline)
  // 1599:     expect('}')
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
  // 1601: ... newline, END_OF_TEXT
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
  // 1601: ... expect(newline, END_OF_TEXT)
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
  // 1601: $META_FRAGMENT META_INSTRUCTION, expect(newline, END_OF_TEXT)
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
  // 1609: syntax_error("top-level statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__416_1;
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
  // 1605: alt
  // 1606:   SINGLE_REMARK_STATEMENT
  // 1607:   TOP_LEVEL_STATEMENT
  // 1608:   C_CODE
  // 1609:   syntax_error("top-level statement expected")
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
  // 1610: ... newline, END_OF_TEXT
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
  // 1610: expect(newline, END_OF_TEXT)
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
  // 1603: $FRAGMENT
  // 1604:   sequence
  // 1605:     alt
  // 1606:       SINGLE_REMARK_STATEMENT
  // 1607:       TOP_LEVEL_STATEMENT
  // 1608:       C_CODE
  // 1609:       syntax_error("top-level statement expected")
  // 1610:     expect(newline, END_OF_TEXT)
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
static void entry__1_1_sim2c__std_identifier(void) {
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
    set_attribute_value(temp->attributes, poly_idx__namespace_of, string__1_2);
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
static void entry__2_50(void) {
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
  frame->cont = cont__2_51;
}
static void cont__2_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 73: ... "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__2_52;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* line_no */;
  arguments->slots[3] = string__2_52;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = string__2_53;
  arguments->slots[6] = ((CELL *)frame->slots[2])->contents /* msg */;
  arguments->slots[7] = string__2_54;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__2_55;
}
static void cont__2_55(void) {
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
static void entry__2_56(void) {
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
  arguments->slots[0] = string__2_57;
  arguments->slots[1] = frame->slots[0] /* msg_type */;
  arguments->slots[2] = string__2_58;
  arguments->slots[3] = ((CELL *)frame->slots[1])->contents /* line_no */;
  arguments->slots[4] = string__2_59;
  arguments->slots[5] = get__module_name();
  arguments->slots[6] = string__2_60;
  arguments->slots[7] = ((CELL *)frame->slots[2])->contents /* msg */;
  arguments->slots[8] = string__2_61;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__2_62;
}
static void cont__2_62(void) {
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
  frame->cont = cont__2_63;
}
static void cont__2_63(void) {
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
  frame->cont = cont__2_64;
}
static void cont__2_64(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 79: ... dup(" " n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_65;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* n */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__2_66;
}
static void cont__2_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 79: ewriteln dup(" " n) "^"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__2_67;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_1_print_message(void) {
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
  frame->cont = cont__2_2;
}
static void cont__2_2(void) {
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
  frame->cont = cont__2_3;
}
static void cont__2_3(void) {
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
  frame->cont = cont__2_4;
}
static void cont__2_4(void) {
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
  frame->cont = cont__2_5;
}
static void cont__2_5(void) {
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
  frame->cont = cont__2_6;
}
static void cont__2_6(void) {
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
  frame->cont = cont__2_7;
}
static void cont__2_7(void) {
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
  frame->cont = cont__2_8;
}
static void cont__2_8(void) {
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
  frame->cont = cont__2_9;
}
static void cont__2_9(void) {
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
  frame->cont = cont__2_10;
}
static void cont__2_10(void) {
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
  frame->cont = cont__2_11;
}
static void cont__2_11(void) {
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
  frame->cont = cont__2_12;
}
static void cont__2_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 60: ... : behind &source alt(newline indent_marker) line_offset
  frame->slots[13] /* temp__2 */ = create_closure(entry__2_13, 0);
  // 60: if line_offset > 0: behind &source alt(newline indent_marker) line_offset
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__2_16;
}
static void entry__2_13(void) {
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
  frame->cont = cont__2_14;
}
static void cont__2_14(void) {
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
  frame->cont = cont__2_15;
}
static void cont__2_15(void) {
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
static void cont__2_16(void) {
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
  frame->cont = cont__2_17;
}
static void cont__2_17(void) {
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
  frame->cont = cont__2_18;
}
static void cont__2_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[8])->contents /* n */ = arguments->slots[0];
  // 62: ... -> n > 0 && source(n) < ' ': dec &n
  frame->slots[12] /* temp__1 */ = create_closure(entry__2_19, 0);
  // 62: while -> n > 0 && source(n) < ' ': dec &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__2_27;
}
static void entry__2_25(void) {
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
  frame->cont = cont__2_26;
}
static void cont__2_26(void) {
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
static void entry__2_19(void) {
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
  frame->cont = cont__2_20;
}
static void cont__2_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 62: ... source(n) < ' '
  frame->slots[4] /* temp__3 */ = create_closure(entry__2_21, 0);
  // 62: ... n > 0 && source(n) < ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__2_24;
}
static void entry__2_21(void) {
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
  frame->cont = cont__2_22;
}
static void cont__2_22(void) {
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
  frame->cont = cont__2_23;
}
static void cont__2_23(void) {
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
static void cont__2_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 62: ... : dec &n
  frame->slots[5] /* temp__4 */ = create_closure(entry__2_25, 0);
  // 62: ... -> n > 0 && source(n) < ' ': dec &n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__2_27(void) {
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
  frame->cont = cont__2_28;
}
static void cont__2_28(void) {
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
  frame->cont = cont__2_29;
}
static void cont__2_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 64: ... -> behind(text '@nl;' line_offset)
  frame->slots[13] /* temp__2 */ = create_closure(entry__2_30, 0);
  // 64: ... -> text
  frame->slots[14] /* temp__3 */ = create_closure(entry__2_32, 0);
  // 64: $rest if(line_offset > 0 (-> behind(text '@nl;' line_offset)) -> text)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  arguments->slots[2] = frame->slots[14] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__2_33;
}
static void entry__2_30(void) {
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
  frame->cont = cont__2_31;
}
static void cont__2_31(void) {
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
static void entry__2_32(void) {
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
static void cont__2_33(void) {
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
  frame->cont = cont__2_34;
}
static void cont__2_34(void) {
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
  frame->cont = cont__2_35;
}
static void cont__2_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 65: ... '@ht;' = "        "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__9;
  arguments->slots[1] = string__2_36;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_37;
}
static void cont__2_37(void) {
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
  frame->cont = cont__2_38;
}
static void cont__2_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* line */, arguments->slots[0]);
  // 66: ... : (-> break)
  // 67:   for_each line: (chr)
  // 68:     if chr != ' ' break
  // 69:     inc &n
  frame->slots[12] /* temp__1 */ = create_closure(entry__2_39, 0);
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
  frame->cont = cont__2_46;
}
static void entry__2_39(void) {
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
  frame->slots[3] /* temp__1 */ = create_closure(entry__2_40, 1);
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
  frame->cont = cont__2_45;
}
static void entry__2_40(void) {
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
  frame->cont = cont__2_41;
}
static void cont__2_41(void) {
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
  frame->cont = cont__2_42;
}
static void cont__2_42(void) {
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
  frame->cont = cont__2_43;
}
static void cont__2_43(void) {
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
  frame->cont = cont__2_44;
}
static void cont__2_44(void) {
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
static void cont__2_45(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__2_46(void) {
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
  frame->cont = cont__2_47;
}
static void cont__2_47(void) {
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
  frame->cont = cont__2_48;
}
static void cont__2_48(void) {
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
  frame->cont = cont__2_49;
}
static void cont__2_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* msg */ = arguments->slots[0];
  // 72: ... :
  // 73:   ewrite "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  frame->slots[12] /* temp__1 */ = create_closure(entry__2_50, 0);
  // 74: :
  // 75:   ewrite "
  // 76:     ____________________________________
  // 77:     @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)":@nl;@(msg)!
  // 78:   ewriteln line
  // 79:   ewriteln dup(" " n) "^"
  frame->slots[13] /* temp__2 */ = create_closure(entry__2_56, 0);
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
static void entry__3_1_sim2c__Warning(void) {
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
  frame->cont = cont__3_2;
}
static void cont__3_2(void) {
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
  frame->cont = cont__3_3;
}
static void cont__3_3(void) {
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
  arguments->slots[2] = string__3_4;
  arguments->slots[3] = frame->slots[1] /* msg */;
  result_count = frame->caller_result_count;
  myself = var._print_message;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_1_ExitWithSyntaxError(void) {
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
  arguments->slots[2] = string__4_2;
  arguments->slots[3] = frame->slots[2] /* msg */;
  result_count = 0;
  myself = var._print_message;
  func = myself->type;
  frame->cont = cont__4_3;
}
static void cont__4_3(void) {
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
static void entry__5_1_sim2c__SyntaxError(void) {
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
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
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
  frame->cont = cont__5_3;
}
static void cont__5_3(void) {
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
static void entry__6_1_ParseError(void) {
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
  frame->cont = cont__6_2;
}
static void cont__6_2(void) {
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
static void entry__8_1_types__syntax_error_grammar__match(void) {
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
  frame->cont = cont__8_2;
}
static void cont__8_2(void) {
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
static void entry__9_1_syntax_error(void) {
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
static void entry__11_8(void) {
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
  arguments->slots[1] = string__11_9;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_10(void) {
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
  arguments->slots[1] = string__11_11;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_12(void) {
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
  arguments->slots[1] = string__11_13;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_14(void) {
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
  arguments->slots[1] = string__11_15;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_16(void) {
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
  arguments->slots[0] = string__11_17;
  arguments->slots[1] = frame->slots[1] /* expression */;
  arguments->slots[2] = string__11_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__11_19;
}
static void cont__11_19(void) {
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
static void entry__11_7(void) {
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
  frame->slots[2] /* temp__1 */ = create_closure(entry__11_8, 0);
  // 114: ... :
  // 115:   ParseError stream "indent expected"
  frame->slots[3] /* temp__2 */ = create_closure(entry__11_10, 0);
  // 116: ... :
  // 117:   ParseError stream "outdent expected"
  frame->slots[4] /* temp__3 */ = create_closure(entry__11_12, 0);
  // 118: ... :
  // 119:   ParseError stream "closing quotation mark expected"
  frame->slots[5] /* temp__4 */ = create_closure(entry__11_14, 0);
  // 120: :
  // 121:   ParseError stream "
  // 122:     @quot;@(expression)" expected@
  frame->slots[6] /* temp__5 */ = create_closure(entry__11_16, 0);
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
static void entry__11_20(void) {
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
  arguments->slots[1] = string__11_21;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_1_types__unexpected_input_error_grammar__match(void) {
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
  frame->cont = cont__11_2;
}
static void cont__11_2(void) {
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
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 109: ... expression.is_a_string
  frame->slots[5] /* temp__3 */ = create_closure(entry__11_4, 0);
  // 109: expression.is_a_character || expression.is_a_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__11_6;
}
static void entry__11_4(void) {
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
  frame->cont = cont__11_5;
}
static void cont__11_5(void) {
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
static void cont__11_6(void) {
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
  frame->slots[6] /* temp__4 */ = create_closure(entry__11_7, 0);
  // 123: :
  // 124:   ParseError stream "unexpected input"
  frame->slots[7] /* temp__5 */ = create_closure(entry__11_20, 0);
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
static void entry__12_1_unexpected_input_error(void) {
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
static void entry__14_1_types__print_grammar__match(void) {
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
  frame->cont = cont__14_2;
}
static void cont__14_2(void) {
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
  frame->cont = cont__14_3;
}
static void cont__14_3(void) {
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
static void entry__15_1_print(void) {
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
static void entry__17_1_dump_stream_grammar__match(void) {
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
  arguments->slots[0] = string__17_2;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__17_3;
}
static void cont__17_3(void) {
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
  frame->cont = cont__17_4;
}
static void cont__17_4(void) {
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
  frame->cont = cont__17_5;
}
static void cont__17_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 150: ewriteln ">>>>>>>>>>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__17_6;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__17_7;
}
static void cont__17_7(void) {
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
static void entry__18_1_sim2c__strip(void) {
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
  frame->cont = cont__18_2;
}
static void cont__18_2(void) {
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
  frame->cont = cont__18_3;
}
static void cont__18_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 164: ... : strip &node.functor_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_4, 0);
  // 164: if functor_of(node).is_defined: strip &node.functor_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void entry__18_4(void) {
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
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
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
  frame->cont = cont__18_6;
}
static void cont__18_6(void) {
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
static void cont__18_7(void) {
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
  frame->cont = cont__18_8;
}
static void cont__18_8(void) {
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
  frame->cont = cont__18_9;
}
static void cont__18_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 165: ... : strip &node.attribute_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_10, 0);
  // 165: if attribute_of(node).is_defined: strip &node.attribute_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_13;
}
static void entry__18_10(void) {
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
  frame->cont = cont__18_11;
}
static void cont__18_11(void) {
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
  frame->cont = cont__18_12;
}
static void cont__18_12(void) {
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
static void cont__18_13(void) {
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
  frame->cont = cont__18_14;
}
static void cont__18_14(void) {
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
  frame->cont = cont__18_15;
}
static void cont__18_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 166: ... :
  // 167:   update_each &node.statements_of: (&statement) strip &statement
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_16, 0);
  // 166: if statements_of(node).is_defined:
  // 167:   update_each &node.statements_of: (&statement) strip &statement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_21;
}
static void entry__18_16(void) {
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
  frame->cont = cont__18_17;
}
static void cont__18_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 167: update_each &node.statements_of: (&statement) strip &statement
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__18_18;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__18_20;
}
static void entry__18_18(void) {
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
  frame->cont = cont__18_19;
}
static void cont__18_19(void) {
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
static void cont__18_20(void) {
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
static void cont__18_21(void) {
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
  frame->cont = cont__18_22;
}
static void cont__18_22(void) {
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
  frame->cont = cont__18_23;
}
static void cont__18_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 168: ... :
  // 169:   update_each &node.parameters_of: (&parameter) strip &parameter
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_24, 0);
  // 168: if parameters_of(node).is_defined:
  // 169:   update_each &node.parameters_of: (&parameter) strip &parameter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_29;
}
static void entry__18_24(void) {
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
  frame->cont = cont__18_25;
}
static void cont__18_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 169: update_each &node.parameters_of: (&parameter) strip &parameter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__18_26;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__18_28;
}
static void entry__18_26(void) {
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
  frame->cont = cont__18_27;
}
static void cont__18_27(void) {
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
static void cont__18_28(void) {
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
static void cont__18_29(void) {
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
  frame->cont = cont__18_30;
}
static void cont__18_30(void) {
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
  frame->cont = cont__18_31;
}
static void cont__18_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 170: ... :
  // 171:   update_each &node.output_arguments_of: (&argument) strip &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_32, 0);
  // 170: if output_arguments_of(node).is_defined:
  // 171:   update_each &node.output_arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_37;
}
static void entry__18_32(void) {
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
  frame->cont = cont__18_33;
}
static void cont__18_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 171: update_each &node.output_arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__18_34;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__18_36;
}
static void entry__18_34(void) {
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
  frame->cont = cont__18_35;
}
static void cont__18_35(void) {
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
static void cont__18_36(void) {
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
static void cont__18_37(void) {
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
  frame->cont = cont__18_38;
}
static void cont__18_38(void) {
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
  frame->cont = cont__18_39;
}
static void cont__18_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 172: ... :
  // 173:   update_each &node.arguments_of: (&argument) strip &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_40, 0);
  // 172: if arguments_of(node).is_defined:
  // 173:   update_each &node.arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_45;
}
static void entry__18_40(void) {
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
  frame->cont = cont__18_41;
}
static void cont__18_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 173: update_each &node.arguments_of: (&argument) strip &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__18_42;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__18_44;
}
static void entry__18_42(void) {
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
  frame->cont = cont__18_43;
}
static void cont__18_43(void) {
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
static void cont__18_44(void) {
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
static void cont__18_45(void) {
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
  frame->cont = cont__18_46;
}
static void cont__18_46(void) {
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
  frame->cont = cont__18_47;
}
static void cont__18_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: ... : strip &node.parent_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_48, 0);
  // 174: if parent_of(node).is_defined: strip &node.parent_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_51;
}
static void entry__18_48(void) {
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
  frame->cont = cont__18_49;
}
static void cont__18_49(void) {
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
  frame->cont = cont__18_50;
}
static void cont__18_50(void) {
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
static void cont__18_51(void) {
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
  frame->cont = cont__18_52;
}
static void cont__18_52(void) {
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
  frame->cont = cont__18_53;
}
static void cont__18_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 175: ... : strip &node.identifier_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_54, 0);
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
  frame->cont = cont__18_57;
}
static void entry__18_54(void) {
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
  frame->cont = cont__18_55;
}
static void cont__18_55(void) {
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
  frame->cont = cont__18_56;
}
static void cont__18_56(void) {
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
static void cont__18_57(void) {
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
static void entry__20_1_dump_grammar__match(void) {
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
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 180: edump `strip(grammar::current_node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__20_3;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__edump();
  func = myself->type;
  frame->cont = cont__20_4;
}
static void cont__20_4(void) {
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
static void entry__22_1_dump3_grammar__match(void) {
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
  frame->cont = cont__22_2;
}
static void cont__22_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 186: edump 3 `strip(grammar::current_node)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = string__20_3;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__edump();
  func = myself->type;
  frame->cont = cont__22_3;
}
static void cont__22_3(void) {
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
static void entry__24_1_dump5_grammar__match(void) {
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
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 192: edump 5 `strip(grammar::current_node)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__5;
  arguments->slots[1] = string__20_3;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__edump();
  func = myself->type;
  frame->cont = cont__24_3;
}
static void cont__24_3(void) {
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
static void entry__28_3(void) {
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
  frame->cont = cont__28_4;
}
static void cont__28_4(void) {
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
static void entry__28_5(void) {
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
static void entry__28_1_sim2c__precedence(void) {
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
  frame->cont = cont__28_2;
}
static void cont__28_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 226: ... -> precedence_table(op)
  frame->slots[2] /* temp__2 */ = create_closure(entry__28_3, 0);
  // 226: if op.is_a_string (-> precedence_table(op)) -> INFIX_PRECEDENCE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = func__28_5;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_1_sim2c__is_left_associative(void) {
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
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
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
static void entry__30_1_is_right_associative(void) {
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
  frame->cont = cont__30_2;
}
static void cont__30_2(void) {
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
  frame->cont = cont__30_3;
}
static void cont__30_3(void) {
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
static void entry__31_1_infix_operator(void) {
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
  frame->cont = cont__31_2;
}
static void cont__31_2(void) {
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
  frame->cont = cont__31_3;
}
static void cont__31_3(void) {
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
static void entry__32_1_interleaved(void) {
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
  frame->cont = cont__32_2;
}
static void cont__32_2(void) {
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
  frame->cont = cont__32_3;
}
static void cont__32_3(void) {
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
  frame->cont = cont__32_4;
}
static void cont__32_4(void) {
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
static void entry__35_1_types__inline_grammar__match(void) {
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
  frame->cont = cont__35_2;
}
static void cont__35_2(void) {
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
  frame->cont = cont__35_3;
}
static void cont__35_3(void) {
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__36_1_inline(void) {
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
static void entry__42_3(void) {
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
  arguments->slots[1] = string__42_4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__42_5;
}
static void cont__42_5(void) {
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
  frame->cont = cont__42_6;
}
static void cont__42_6(void) {
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
  frame->cont = cont__42_7;
}
static void cont__42_7(void) {
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
static void entry__42_8(void) {
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
  frame->cont = cont__42_9;
}
static void cont__42_9(void) {
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
  frame->cont = cont__42_10;
}
static void cont__42_10(void) {
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
static void entry__42_1_expect(void) {
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
  frame->cont = cont__42_2;
}
static void cont__42_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 265: -> alt(expression syntax_error("@(description) expected"))
  frame->slots[3] /* temp__2 */ = create_closure(entry__42_3, 0);
  // 266: -> alt(expression unexpected_input_error(expression))
  frame->slots[4] /* temp__3 */ = create_closure(entry__42_8, 0);
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
static void entry__45_1_sim2c__arguments_span(void) {
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
  frame->cont = cont__45_2;
}
static void cont__45_2(void) {
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
  frame->cont = cont__45_3;
}
static void cont__45_3(void) {
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
static void entry__46_1_sim2c__output_arguments_span(void) {
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
  frame->cont = cont__46_2;
}
static void cont__46_2(void) {
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
  frame->cont = cont__46_3;
}
static void cont__46_3(void) {
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
static void entry__208_1_sim2c__parse_meta_instruction(void) {
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
  // 1616: %sim2c::current_fragment fragment # used to generate meaningful error messages
  initialize_maybe_future(get__sim2c__current_fragment(), frame->slots[0] /* fragment */);
  // 1617: $source sim2c::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__sim2c__source_of();
  func = myself->type;
  frame->cont = cont__208_2;
}
static void cont__208_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* source */, arguments->slots[0]);
  // 1618: match source META_FRAGMENT $len $cap
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  arguments->slots[1] = var._META_FRAGMENT;
  result_count = 2;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__208_3;
}
static void cont__208_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 1618: ... len
  initialize_future(frame->slots[3] /* len */, frame->slots[5] /* temp__1 */);
  // 1618: ... cap
  initialize_future(frame->slots[4] /* cap */, frame->slots[6] /* temp__2 */);
  // 1619: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__208_4;
}
static void cont__208_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 1619: ... len != length_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__208_5;
}
static void cont__208_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1619: ... len != length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__208_6;
}
static void cont__208_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1619: ... : ParseError source "invalid meta instruction"
  frame->slots[8] /* temp__4 */ = create_closure(entry__208_7, 0);
  // 1619: if len != length_of(source): ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__208_9;
}
static void entry__208_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1619: ... ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__208_8;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__208_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1620: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__209_1_sim2c__parse_statement(void) {
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
  // 1623: %sim2c::current_fragment fragment # used to generate meaningful error messages
  initialize_maybe_future(get__sim2c__current_fragment(), frame->slots[0] /* fragment */);
  // 1624: $source sim2c::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__sim2c__source_of();
  func = myself->type;
  frame->cont = cont__209_2;
}
static void cont__209_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* source */, arguments->slots[0]);
  // 1625: match source FRAGMENT $len $cap
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  arguments->slots[1] = var._FRAGMENT;
  result_count = 2;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__209_3;
}
static void cont__209_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 1625: ... len
  initialize_future(frame->slots[3] /* len */, frame->slots[5] /* temp__1 */);
  // 1625: ... cap
  initialize_future(frame->slots[4] /* cap */, frame->slots[6] /* temp__2 */);
  // 1627: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__209_4;
}
static void cont__209_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1627: ... :
  // 1628:   if len != length_of(source):
  // 1629:     ParseError source "superficious input at end of expression"
  frame->slots[6] /* temp__2 */ = create_closure(entry__209_5, 0);
  // 1630: :
  // 1631:   ewriteln "________________________________________"
  // 1632:   eprint_source source
  // 1633:   ewriteln "no match"
  // 1634:   exit 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__209_11, 0);
  // 1626: if
  // 1627:   len.is_defined:
  // 1628:     if len != length_of(source):
  // 1629:       ParseError source "superficious input at end of expression"
  // 1630:   :
  // 1631:     ewriteln "________________________________________"
  // 1632:     eprint_source source
  // 1633:     ewriteln "no match"
  // 1634:     exit 1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__209_17;
}
static void entry__209_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1629: ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__209_10;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__209_5(void) {
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
  // 1628: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__209_6;
}
static void cont__209_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1628: ... len != length_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__209_7;
}
static void cont__209_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1628: ... len != length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__209_8;
}
static void cont__209_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1628: ... :
  // 1629:   ParseError source "superficious input at end of expression"
  frame->slots[5] /* temp__4 */ = create_closure(entry__209_9, 0);
  // 1628: if len != length_of(source):
  // 1629:   ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__209_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1631: ewriteln "________________________________________"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__209_12;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__209_13;
}
static void cont__209_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1632: eprint_source source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 0;
  myself = get__eprint_source();
  func = myself->type;
  frame->cont = cont__209_14;
}
static void cont__209_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1633: ewriteln "no match"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__209_15;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__209_16;
}
static void cont__209_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1634: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__209_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1635: -> cap
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
  register_polymorphic_function("_parser::original_remark_lines_of", &poly_idx__original_remark_lines_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__parser(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
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
  string__1_2 = from_latin_1_string("std", 3);
  func__1_1_sim2c__std_identifier = create_function(entry__1_1_sim2c__std_identifier, 1);
  string__2_36 = from_latin_1_string("        ", 8);
  string__2_52 = from_latin_1_string(":", 1);
  string__2_53 = from_latin_1_string(": ", 2);
  string__2_54 = from_latin_1_string("\012", 1);
  string__2_57 = from_latin_1_string("____________________________________\012", 37);
  string__2_58 = from_latin_1_string(" IN LINE ", 9);
  string__2_59 = from_latin_1_string(" OF FILE \042", 10);
  string__2_60 = from_latin_1_string("\042:\012", 3);
  string__2_61 = from_latin_1_string("!\012", 2);
  string__2_65 = from_latin_1_string(" ", 1);
  string__2_67 = from_latin_1_string("^", 1);
  func__2_1_print_message = create_function(entry__2_1_print_message, 4);
  string__3_4 = from_latin_1_string("WARNING", 7);
  func__3_1_sim2c__Warning = create_function(entry__3_1_sim2c__Warning, 2);
  string__4_2 = from_latin_1_string("SYNTAX ERROR", 12);
  func__4_1_ExitWithSyntaxError = create_function(entry__4_1_ExitWithSyntaxError, 3);
  func__5_1_sim2c__SyntaxError = create_function(entry__5_1_sim2c__SyntaxError, 2);
  func__6_1_ParseError = create_function(entry__6_1_ParseError, 2);
  func__8_1_types__syntax_error_grammar__match = create_function(entry__8_1_types__syntax_error_grammar__match, 2);
  func__9_1_syntax_error = create_function(entry__9_1_syntax_error, 1);
  string__11_9 = from_latin_1_string("newline expected", 16);
  string__11_11 = from_latin_1_string("indent expected", 15);
  string__11_13 = from_latin_1_string("outdent expected", 16);
  string__11_15 = from_latin_1_string("closing quotation mark expected", 31);
  string__11_17 = from_latin_1_string("\042", 1);
  string__11_18 = from_latin_1_string("\042 expected", 10);
  string__11_21 = from_latin_1_string("unexpected input", 16);
  func__11_1_types__unexpected_input_error_grammar__match = create_function(entry__11_1_types__unexpected_input_error_grammar__match, 2);
  func__12_1_unexpected_input_error = create_function(entry__12_1_unexpected_input_error, 1);
  func__14_1_types__print_grammar__match = create_function(entry__14_1_types__print_grammar__match, 2);
  func__15_1_print = create_function(entry__15_1_print, 1);
  string__17_2 = from_latin_1_string("<<<<<<<<<<", 10);
  string__17_6 = from_latin_1_string(">>>>>>>>>>", 10);
  func__17_1_dump_stream_grammar__match = create_function(entry__17_1_dump_stream_grammar__match, 2);
  func__18_18 = create_function(entry__18_18, 1);
  func__18_26 = create_function(entry__18_26, 1);
  func__18_34 = create_function(entry__18_34, 1);
  func__18_42 = create_function(entry__18_42, 1);
  func__18_1_sim2c__strip = create_function(entry__18_1_sim2c__strip, 1);
  string__20_3 = from_latin_1_string("strip(grammar::current_node)", 28);
  func__20_1_dump_grammar__match = create_function(entry__20_1_dump_grammar__match, 2);
  func__22_1_dump3_grammar__match = create_function(entry__22_1_dump3_grammar__match, 2);
  func__24_1_dump5_grammar__match = create_function(entry__24_1_dump5_grammar__match, 2);
  func__28_5 = create_function(entry__28_5, 0);
  func__28_1_sim2c__precedence = create_function(entry__28_1_sim2c__precedence, 1);
  func__29_1_sim2c__is_left_associative = create_function(entry__29_1_sim2c__is_left_associative, 1);
  func__30_1_is_right_associative = create_function(entry__30_1_is_right_associative, 1);
  func__31_1_infix_operator = create_function(entry__31_1_infix_operator, 1);
  func__32_1_interleaved = create_function(entry__32_1_interleaved, 2);
  func__35_1_types__inline_grammar__match = create_function(entry__35_1_types__inline_grammar__match, 2);
  func__36_1_inline = create_function(entry__36_1_inline, 1);
  string__42_4 = from_latin_1_string(" expected", 9);
  func__42_1_expect = create_function(entry__42_1_expect, -1);
  func__45_1_sim2c__arguments_span = create_function(entry__45_1_sim2c__arguments_span, 1);
  func__46_1_sim2c__output_arguments_span = create_function(entry__46_1_sim2c__output_arguments_span, 1);
  string__208_8 = from_latin_1_string("invalid meta instruction", 24);
  func__208_1_sim2c__parse_meta_instruction = create_function(entry__208_1_sim2c__parse_meta_instruction, 1);
  string__209_10 = from_latin_1_string("superficious input at end of expression", 39);
  string__209_12 = from_latin_1_string("________________________________________", 40);
  string__209_15 = from_latin_1_string("no match", 8);
  func__209_1_sim2c__parse_statement = create_function(entry__209_1_sim2c__parse_statement, 1);
  string__236_1 = from_latin_1_string("*", 1);
  string__236_3 = from_latin_1_string("/", 1);
  string__236_5 = from_latin_1_string("+", 1);
  string__236_7 = from_latin_1_string("-", 1);
  string__236_9 = from_latin_1_string("<<", 2);
  string__236_11 = from_latin_1_string(">>", 2);
  string__236_13 = from_latin_1_string("&", 1);
  string__236_16 = from_latin_1_string("|", 1);
  string__236_18 = from_latin_1_string("<=", 2);
  string__236_20 = from_latin_1_string("<", 1);
  string__236_22 = from_latin_1_string(">=", 2);
  string__236_24 = from_latin_1_string(">", 1);
  string__236_26 = from_latin_1_string("==", 2);
  string__236_28 = from_latin_1_string("!=", 2);
  string__236_30 = from_latin_1_string("&&", 2);
  string__236_32 = from_latin_1_string("||", 2);
  string__236_34 = from_latin_1_string("..", 2);
  string__236_36 = from_latin_1_string(",", 1);
  string__236_38 = from_latin_1_string("=", 1);
  string__246_3 = from_latin_1_string("\042)\042 expected", 12);
  func__246_1 = create_function(entry__246_1, 2);
  func__252_1 = create_function(entry__252_1, 1);
  func__253_1 = create_function(entry__253_1, 1);
  func__260_1 = create_function(entry__260_1, 2);
  func__261_1 = create_function(entry__261_1, 2);
  func__262_1 = create_function(entry__262_1, 2);
  func__263_1 = create_function(entry__263_1, 2);
  func__264_3 = create_function(entry__264_3, 1);
  string__264_7 = from_latin_1_string("::", 2);
  string__265_7 = from_latin_1_string("namespace must not start with an underscore", 43);
  func__265_4 = create_function(entry__265_4, 1);
  string__267_1 = from_latin_1_string("./", 2);
  string__268_8 = from_latin_1_string("the module \042", 12);
  string__268_9 = from_latin_1_string("\042 is required twice", 19);
  func__268_3 = create_function(entry__268_3, 2);
  string__268_14 = from_latin_1_string("<require", 8);
  func__269_4 = create_function(entry__269_4, 1);
  string__269_14 = from_latin_1_string("the namespace \042", 15);
  string__269_15 = from_latin_1_string("\042 is defined twice", 18);
  string__269_25 = from_latin_1_string("the namespace alias \042", 21);
  func__269_10 = create_function(entry__269_10, 2);
  string__269_30 = from_latin_1_string("<namespace", 10);
  string__270_7 = from_latin_1_string("\042 is used twice", 15);
  func__270_3 = create_function(entry__270_3, 2);
  string__270_12 = from_latin_1_string("<using", 6);
  string__272_1 = from_latin_1_string("../", 3);
  string__273_7 = from_latin_1_string("the file \042", 10);
  string__273_8 = from_latin_1_string("\042 is included twice", 19);
  func__273_3 = create_function(entry__273_3, 2);
  string__273_13 = from_latin_1_string("<include", 8);
  string__274_7 = from_latin_1_string("the library \042", 13);
  string__274_8 = from_latin_1_string("\042 is linked twice", 17);
  func__274_3 = create_function(entry__274_3, 2);
  string__274_13 = from_latin_1_string("<link", 5);
  string__277_7 = from_latin_1_string("the data dependency \042", 21);
  func__277_3 = create_function(entry__277_3, 2);
  string__277_12 = from_latin_1_string("<data", 5);
  func__284_1 = create_function(entry__284_1, 1);
  func__286_1 = create_function(entry__286_1, 1);
  func__287_1 = create_function(entry__287_1, 1);
  func__290_1 = create_function(entry__290_1, 1);
  func__291_1 = create_function(entry__291_1, 1);
  string__300_3 = from_latin_1_string("0b", 2);
  string__302_3 = from_latin_1_string("0o", 2);
  string__304_3 = from_latin_1_string("0x", 2);
  func__306_2 = create_function(entry__306_2, 1);
  func__307_1 = create_function(entry__307_1, 1);
  string__308_7 = from_latin_1_string("invalid character name", 22);
  func__308_2 = create_function(entry__308_2, 2);
  func__309_10 = create_function(entry__309_10, 1);
  string__310_1 = from_latin_1_string("invalid special character", 25);
  func__313_1 = create_function(entry__313_1, 1);
  string__313_7 = from_latin_1_string("@;", 2);
  func__314_1 = create_function(entry__314_1, 1);
  string__314_13 = from_latin_1_string("@(", 2);
  string__315_13 = from_latin_1_string("string", 6);
  func__315_1 = create_function(entry__315_1, 1);
  func__318_1 = create_function(entry__318_1, 1);
  string__321_1 = from_latin_1_string("expression expected", 19);
  string__322_2 = from_latin_1_string("key_value_pair", 14);
  string__322_4 = from_latin_1_string("true", 4);
  func__322_1 = create_function(entry__322_1, 1);
  string__322_11 = from_latin_1_string("--", 2);
  func__323_1 = create_function(entry__323_1, 1);
  func__330_2 = create_function(entry__330_2, 1);
  func__331_13 = create_function(entry__331_13, 0);
  func__331_53 = create_function(entry__331_53, 0);
  func__331_1 = create_function(entry__331_1, 1);
  string__333_2 = from_latin_1_string("identifier", 10);
  string__337_2 = from_latin_1_string("$$", 2);
  string__339_2 = from_latin_1_string("%%", 2);
  func__340_1 = create_function(entry__340_1, 1);
  func__348_1 = create_function(entry__348_1, 1);
  func__349_1 = create_function(entry__349_1, 1);
  func__359_1 = create_function(entry__359_1, 1);
  func__359_6 = create_function(entry__359_6, 1);
  func__361_1 = create_function(entry__361_1, 1);
  func__361_4 = create_function(entry__361_4, 1);
  func__364_3 = create_function(entry__364_3, 1);
  string__364_13 = from_latin_1_string("too few arguments in multi-line expression", 42);
  func__364_8 = create_function(entry__364_8, 2);
  func__365_10 = create_function(entry__365_10, 1);
  func__372_1 = create_function(entry__372_1, 1);
  string__376_3 = from_latin_1_string("->", 2);
  string__380_12 = from_latin_1_string("statement expected", 18);
  string__386_2 = from_latin_1_string("()", 2);
  string__387_2 = from_latin_1_string("(!)", 3);
  string__389_11 = from_latin_1_string("invalid polymorphic function definition", 39);
  func__389_5 = create_function(entry__389_5, 1);
  string__391_2 = from_latin_1_string(".(", 2);
  string__397_6 = from_latin_1_string("return statement needs at least one argument", 44);
  func__397_2 = create_function(entry__397_2, 1);
  string__399_2 = from_latin_1_string("__", 2);
  string__401_4 = from_latin_1_string("argument", 8);
  string__402_4 = from_latin_1_string("base", 4);
  string__403_4 = from_latin_1_string("kind", 4);
  string__404_4 = from_latin_1_string("name", 4);
  string__405_4 = from_latin_1_string("node", 4);
  string__406_1 = from_latin_1_string("runtime", 7);
  string__406_2 = from_latin_1_string("global", 6);
  string__406_3 = from_latin_1_string("local", 5);
  string__406_4 = from_latin_1_string("extern", 6);
  string__406_9 = from_latin_1_string("scope", 5);
  string__407_4 = from_latin_1_string("type", 4);
  string__408_1 = from_latin_1_string("invalid annotation tag", 22);
  string__411_1 = from_latin_1_string("//", 2);
  string__416_1 = from_latin_1_string("top-level statement expected", 28);
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
  define_method("types", "syntax_error", poly_idx__grammar__match, func__8_1_types__syntax_error_grammar__match);
  define_method("types", "unexpected_input_error", poly_idx__grammar__match, func__11_1_types__unexpected_input_error_grammar__match);
  define_method("types", "print", poly_idx__grammar__match, func__14_1_types__print_grammar__match);
  update_start_p = node_p;
  def_attribute(&var._dump_stream, poly_idx__grammar__match, func__17_1_dump_stream_grammar__match);
  update_start_p = node_p;
  def_attribute(&var._dump, poly_idx__grammar__match, func__20_1_dump_grammar__match);
  update_start_p = node_p;
  def_attribute(&var._dump3, poly_idx__grammar__match, func__22_1_dump3_grammar__match);
  update_start_p = node_p;
  def_attribute(&var._dump5, poly_idx__grammar__match, func__24_1_dump5_grammar__match);
  define_method("types", "inline", poly_idx__grammar__match, func__35_1_types__inline_grammar__match);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__parser(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.sim2c__std_identifier, &func__1_1_sim2c__std_identifier);
  assign_variable(&var._print_message, &func__2_1_print_message);
  assign_variable(&var.sim2c__Warning, &func__3_1_sim2c__Warning);
  assign_variable(&var._ExitWithSyntaxError, &func__4_1_ExitWithSyntaxError);
  assign_variable(&var.sim2c__SyntaxError, &func__5_1_sim2c__SyntaxError);
  assign_variable(&var._ParseError, &func__6_1_ParseError);
  assign_value(&var.types__syntax_error, get__types__grammar_object());
  assign_variable(&var._syntax_error, &func__9_1_syntax_error);
  assign_value(&var.types__unexpected_input_error, get__types__grammar_object());
  assign_variable(&var._unexpected_input_error, &func__12_1_unexpected_input_error);
  assign_value(&var.types__print, get__types__grammar_object());
  assign_variable(&var._print, &func__15_1_print);
  assign_value(&var._dump_stream, get__types__grammar_object());
  assign_variable(&var.sim2c__strip, &func__18_1_sim2c__strip);
  assign_value(&var._dump, get__types__grammar_object());
  assign_value(&var._dump3, get__types__grammar_object());
  assign_value(&var._dump5, get__types__grammar_object());
  assign_value(&var.sim2c__HIGHEST_PRECEDENCE, number__99);
  assign_value(&var.sim2c__INFIX_PRECEDENCE, number__6);
  assign_variable(&var.sim2c__precedence, &func__28_1_sim2c__precedence);
  assign_variable(&var.sim2c__is_left_associative, &func__29_1_sim2c__is_left_associative);
  assign_variable(&var._is_right_associative, &func__30_1_is_right_associative);
  assign_variable(&var._infix_operator, &func__31_1_infix_operator);
  assign_variable(&var._interleaved, &func__32_1_interleaved);
  maybe_initialize_future(get__within_inline_expression(), get__false());
  assign_value(&var.types__inline, get__types__grammar_object());
  assign_variable(&var._inline, &func__36_1_inline);
  assign_variable(&var._expect, &func__42_1_expect);
  assign_variable(&var.sim2c__arguments_span, &func__45_1_sim2c__arguments_span);
  assign_variable(&var.sim2c__output_arguments_span, &func__46_1_sim2c__output_arguments_span);
  assign_value(&var._original_remark_lines_of, create_function(type__original_remark_lines_of, -1));
  assign_variable(&var.sim2c__parse_meta_instruction, &func__208_1_sim2c__parse_meta_instruction);
  assign_variable(&var.sim2c__parse_statement, &func__209_1_sim2c__parse_statement);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__parser(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__parser);
}
