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
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void maybe_initialize_future(NODE *var, NODE *val);
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

#define ENCODE_ADDRESS(addr) ((void *)(FIRST_INVALID_ADDRESS|(uintptr_t)(addr) >> 2))
#define DECODE_ADDRESS(addr) ((void *)((uintptr_t)(addr) << 2))
#define IS_AN_INVALID_ADDRESS(addr) ((void *)(addr) >= (void *)FIRST_INVALID_ADDRESS)

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
static NODE *temp__1;
static NODE *temp__2;
static NODE *temp__3;
static NODE *temp__4;
static NODE *temp__5;
static NODE *temp__6;
static NODE *temp__7;
static NODE *temp__8;
static NODE *temp__9;
static NODE *temp__10;
static NODE *temp__11;
static NODE *temp__12;
static NODE *temp__13;
static NODE *temp__14;
static NODE *temp__15;
static NODE *temp__16;
static NODE *temp__17;
static NODE *temp__18;
static NODE *temp__19;
static NODE *temp__20;
static NODE *temp__21;
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
  NODE *_REMARK_FIRST;
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
  NODE *_POLYMORPHIC_FUNCTION_WITHOUT_SETTER;
  NODE *_POLYMORPHIC_FUNCTION_WITH_SETTER;
  NODE *_POLYMORPHIC_FUNCTION;
  NODE *_ASSIGNMENT;
  NODE *_FUNCTOR;
  NODE *_RESULT_COUNT_OR_CONTINUATION;
  NODE *_PROCEDURE_CALL;
  NODE *_INDENTED_REMARKS;
  NODE *_SINGLE_STATEMENT;
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
  "REMARK_FIRST",
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
  "POLYMORPHIC_FUNCTION_WITHOUT_SETTER",
  "POLYMORPHIC_FUNCTION_WITH_SETTER",
  "POLYMORPHIC_FUNCTION",
  "ASSIGNMENT",
  "FUNCTOR",
  "RESULT_COUNT_OR_CONTINUATION",
  "PROCEDURE_CALL",
  "INDENTED_REMARKS",
  "SINGLE_STATEMENT",
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
static NODE *func__1_1;
static void entry__1_1(void);
static FRAME_INFO frame__1_1 = {1, {"name"}};
static NODE *string__1_2;
static NODE *get__sim2c__std_identifier(void) {
  return var.sim2c__std_identifier;
}
static NODE *func__2_1;
static void entry__2_1(void);
static FRAME_INFO frame__2_1 = {12, {"fragment", "offset", "msg_type", "msg", "source", "pos", "line_no", "line_offset", "n", "text", "rest", "line"}};
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
static NODE *string__2_55;
static void cont__2_56(void);
static NODE *func__2_57;
static void entry__2_57(void);
static FRAME_INFO frame__2_57 = {5, {"msg_type", "line_no", "msg", "line", "n"}};
static NODE *string__2_58;
static NODE *string__2_59;
static NODE *string__2_60;
static NODE *string__2_61;
static NODE *string__2_62;
static void cont__2_63(void);
static void cont__2_64(void);
static void cont__2_65(void);
static NODE *string__2_66;
static void cont__2_67(void);
static NODE *string__2_68;
static NODE *func__3_1;
static void entry__3_1(void);
static FRAME_INFO frame__3_1 = {2, {"obj", "msg"}};
static void cont__3_2(void);
static void cont__3_3(void);
static NODE *string__3_4;
static NODE *get__sim2c__Warning(void) {
  return var.sim2c__Warning;
}
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {3, {"fragment", "offset", "msg"}};
static NODE *string__4_2;
static void cont__4_3(void);
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {2, {"obj", "msg"}};
static void cont__5_2(void);
static void cont__5_3(void);
static NODE *get__sim2c__SyntaxError(void) {
  return var.sim2c__SyntaxError;
}
static NODE *func__6_1;
static void entry__6_1(void);
static FRAME_INFO frame__6_1 = {2, {"stream", "msg"}};
static void cont__6_2(void);
static NODE *get__types__syntax_error(void) {
  return var.types__syntax_error;
}
static NODE *func__8_1;
static void entry__8_1(void);
static FRAME_INFO frame__8_1 = {2, {"self", "stream"}};
static void cont__8_2(void);
static NODE *func__9_1;
static void entry__9_1(void);
static FRAME_INFO frame__9_1 = {1, {"message"}};
static NODE *get__types__unexpected_input_error(void) {
  return var.types__unexpected_input_error;
}
static NODE *func__11_1;
static void entry__11_1(void);
static FRAME_INFO frame__11_1 = {3, {"self", "stream", "expression"}};
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
static FRAME_INFO frame__11_14 = {2, {"stream", "expression"}};
static NODE *string__11_15;
static NODE *string__11_16;
static void cont__11_17(void);
static NODE *func__11_18;
static void entry__11_18(void);
static FRAME_INFO frame__11_18 = {1, {"stream"}};
static NODE *string__11_19;
static NODE *func__12_1;
static void entry__12_1(void);
static FRAME_INFO frame__12_1 = {1, {"expression"}};
static NODE *get__types__print(void) {
  return var.types__print;
}
static NODE *func__14_1;
static void entry__14_1(void);
static FRAME_INFO frame__14_1 = {2, {"self", "stream"}};
static void cont__14_2(void);
static void cont__14_3(void);
static NODE *func__15_1;
static void entry__15_1(void);
static FRAME_INFO frame__15_1 = {1, {"message"}};
static NODE *func__17_1;
static void entry__17_1(void);
static FRAME_INFO frame__17_1 = {2, {"self", "stream"}};
static NODE *string__17_2;
static void cont__17_3(void);
static void cont__17_4(void);
static void cont__17_5(void);
static NODE *string__17_6;
static void cont__17_7(void);
static NODE *func__18_1;
static void entry__18_1(void);
static FRAME_INFO frame__18_1 = {1, {"node"}};
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
static NODE *func__20_1;
static void entry__20_1(void);
static FRAME_INFO frame__20_1 = {2, {"self", "stream"}};
static void cont__20_2(void);
static NODE *string__20_3;
static void cont__20_4(void);
static NODE *func__22_1;
static void entry__22_1(void);
static FRAME_INFO frame__22_1 = {2, {"self", "stream"}};
static void cont__22_2(void);
static NODE *string__22_3;
static void cont__22_4(void);
static NODE *func__24_1;
static void entry__24_1(void);
static FRAME_INFO frame__24_1 = {2, {"self", "stream"}};
static void cont__24_2(void);
static NODE *string__24_3;
static void cont__24_4(void);
static NODE *get__sim2c__HIGHEST_PRECEDENCE(void) {
  return var.sim2c__HIGHEST_PRECEDENCE;
}
static NODE *get__sim2c__INFIX_PRECEDENCE(void) {
  return var.sim2c__INFIX_PRECEDENCE;
}
static NODE *func__28_1;
static void entry__28_1(void);
static FRAME_INFO frame__28_1 = {1, {"op"}};
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
static NODE *func__29_1;
static void entry__29_1(void);
static FRAME_INFO frame__29_1 = {1, {"prec"}};
static void cont__29_2(void);
static NODE *get__sim2c__is_left_associative(void) {
  return var.sim2c__is_left_associative;
}
static NODE *func__30_1;
static void entry__30_1(void);
static FRAME_INFO frame__30_1 = {1, {"prec"}};
static void cont__30_2(void);
static void cont__30_3(void);
static NODE *func__31_1;
static void entry__31_1(void);
static FRAME_INFO frame__31_1 = {1, {"operator"}};
static void cont__31_2(void);
static void cont__31_3(void);
static NODE *func__32_1;
static void entry__32_1(void);
static FRAME_INFO frame__32_1 = {2, {"expression", "separator"}};
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
static NODE *func__35_1;
static void entry__35_1(void);
static FRAME_INFO frame__35_1 = {3, {"self", "stream", "return__1"}};
static void cont__35_2(void);
static void cont__35_3(void);
static NODE *func__36_1;
static void entry__36_1(void);
static FRAME_INFO frame__36_1 = {1, {"expression"}};
static NODE *func__42_1;
static void entry__42_1(void);
static FRAME_INFO frame__42_1 = {2, {"expression", "description"}};
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
static NODE *func__45_1;
static void entry__45_1(void);
static FRAME_INFO frame__45_1 = {1, {"expression"}};
static void cont__45_2(void);
static void cont__45_3(void);
static NODE *get__sim2c__arguments_span(void) {
  return var.sim2c__arguments_span;
}
static NODE *func__46_1;
static void entry__46_1(void);
static FRAME_INFO frame__46_1 = {1, {"expression"}};
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
static NODE *func__207_1;
static void entry__207_1(void);
static FRAME_INFO frame__207_1 = {5, {"fragment", "return__1", "source", "len", "cap"}};
static void cont__207_2(void);
static void cont__207_3(void);
static void cont__207_4(void);
static void cont__207_5(void);
static void cont__207_6(void);
static NODE *func__207_7;
static void entry__207_7(void);
static FRAME_INFO frame__207_7 = {1, {"source"}};
static NODE *string__207_8;
static void cont__207_9(void);
static NODE *get__sim2c__parse_meta_instruction(void) {
  return var.sim2c__parse_meta_instruction;
}
static NODE *func__208_1;
static void entry__208_1(void);
static FRAME_INFO frame__208_1 = {5, {"fragment", "return__1", "source", "len", "cap"}};
static void cont__208_2(void);
static void cont__208_3(void);
static void cont__208_4(void);
static NODE *func__208_5;
static void entry__208_5(void);
static FRAME_INFO frame__208_5 = {2, {"len", "source"}};
static void cont__208_6(void);
static void cont__208_7(void);
static void cont__208_8(void);
static NODE *func__208_9;
static void entry__208_9(void);
static FRAME_INFO frame__208_9 = {1, {"source"}};
static NODE *string__208_10;
static NODE *func__208_11;
static void entry__208_11(void);
static FRAME_INFO frame__208_11 = {1, {"source"}};
static NODE *string__208_12;
static void cont__208_13(void);
static void cont__208_14(void);
static NODE *string__208_15;
static void cont__208_16(void);
static void cont__208_17(void);
static NODE *get__sim2c__parse_statement(void) {
  return var.sim2c__parse_statement;
}
static NODE *string__235_1;
static void cont__235_2(void);
static NODE *string__235_3;
static void cont__235_4(void);
static NODE *string__235_5;
static void cont__235_6(void);
static NODE *string__235_7;
static void cont__235_8(void);
static NODE *string__235_9;
static void cont__235_10(void);
static NODE *string__235_11;
static void cont__235_12(void);
static NODE *string__235_13;
static void cont__235_14(void);
static NODE *string__235_15;
static void cont__235_16(void);
static NODE *string__235_17;
static void cont__235_18(void);
static NODE *string__235_19;
static void cont__235_20(void);
static NODE *string__235_21;
static void cont__235_22(void);
static NODE *string__235_23;
static void cont__235_24(void);
static NODE *string__235_25;
static void cont__235_26(void);
static NODE *string__235_27;
static void cont__235_28(void);
static NODE *string__235_29;
static void cont__235_30(void);
static NODE *string__235_31;
static void cont__235_32(void);
static NODE *string__235_33;
static void cont__235_34(void);
static NODE *string__235_35;
static void cont__235_36(void);
static NODE *string__235_37;
static void cont__235_38(void);
static NODE *string__235_39;
static void cont__235_40(void);
static void cont__235_41(void);
static NODE *func__245_1;
static void entry__245_1(void);
static FRAME_INFO frame__245_1 = {2, {"node", "stream"}};
static NODE *func__245_2;
static void entry__245_2(void);
static FRAME_INFO frame__245_2 = {1, {"stream"}};
static NODE *string__245_3;
static void cont__245_4(void);
static void cont__245_5(void);
static void cont__246_1(void);
static void cont__246_2(void);
static void cont__247_1(void);
static void cont__247_2(void);
static void cont__248_1(void);
static void cont__248_2(void);
static void cont__249_1(void);
static void cont__249_2(void);
static NODE *func__251_1;
static void entry__251_1(void);
static FRAME_INFO frame__251_1 = {1, {"node"}};
static void cont__251_2(void);
static void cont__251_3(void);
static NODE *func__252_1;
static void entry__252_1(void);
static FRAME_INFO frame__252_1 = {1, {"node"}};
static void cont__252_2(void);
static void cont__255_1(void);
static void cont__256_1(void);
static void cont__256_2(void);
static void cont__257_1(void);
static void cont__258_1(void);
static NODE *func__259_1;
static void entry__259_1(void);
static FRAME_INFO frame__259_1 = {2, {"node", "stream"}};
static void cont__259_2(void);
static void cont__259_3(void);
static NODE *func__260_1;
static void entry__260_1(void);
static FRAME_INFO frame__260_1 = {2, {"node", "stream"}};
static void cont__260_2(void);
static void cont__260_3(void);
static void cont__260_4(void);
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
static void cont__263_1(void);
static void cont__263_2(void);
static NODE *func__263_3;
static void entry__263_3(void);
static FRAME_INFO frame__263_3 = {1, {"node"}};
static void cont__263_4(void);
static void cont__263_5(void);
static void cont__263_6(void);
static NODE *string__263_7;
static void cont__263_8(void);
static void cont__263_9(void);
static void cont__263_10(void);
static void cont__264_1(void);
static void cont__264_2(void);
static void cont__264_3(void);
static NODE *func__264_4;
static void entry__264_4(void);
static FRAME_INFO frame__264_4 = {1, {"node"}};
static void cont__264_5(void);
static NODE *func__264_6;
static void entry__264_6(void);
static FRAME_INFO frame__264_6 = {1, {"node"}};
static NODE *string__264_7;
static void cont__264_8(void);
static void cont__264_9(void);
static void cont__264_10(void);
static void cont__264_11(void);
static NODE *string__264_12;
static void cont__264_13(void);
static void cont__264_14(void);
static void cont__264_15(void);
static void cont__265_1(void);
static void cont__265_2(void);
static NODE *string__265_3;
static void cont__265_4(void);
static void cont__265_5(void);
static void cont__265_6(void);
static NODE *string__266_1;
static void cont__266_2(void);
static NODE *string__266_3;
static void cont__266_4(void);
static void cont__266_5(void);
static void cont__266_6(void);
static void cont__267_1(void);
static void cont__267_2(void);
static NODE *func__267_3;
static void entry__267_3(void);
static FRAME_INFO frame__267_3 = {3, {"node", "stream", "filename"}};
static void cont__267_4(void);
static void cont__267_5(void);
static void cont__267_6(void);
static NODE *func__267_7;
static void entry__267_7(void);
static FRAME_INFO frame__267_7 = {2, {"stream", "filename"}};
static NODE *string__267_8;
static NODE *string__267_9;
static void cont__267_10(void);
static void cont__267_11(void);
static void cont__267_12(void);
static void cont__267_13(void);
static NODE *string__267_14;
static NODE *string__267_15;
static void cont__267_16(void);
static void cont__268_1(void);
static void cont__268_2(void);
static NODE *string__268_3;
static void cont__268_4(void);
static NODE *func__268_5;
static void entry__268_5(void);
static FRAME_INFO frame__268_5 = {1, {"node"}};
static void cont__268_6(void);
static void cont__268_7(void);
static void cont__268_8(void);
static void cont__268_9(void);
static void cont__268_10(void);
static NODE *func__268_11;
static void entry__268_11(void);
static FRAME_INFO frame__268_11 = {4, {"node", "stream", "namespace", "alias"}};
static void cont__268_12(void);
static void cont__268_13(void);
static NODE *func__268_14;
static void entry__268_14(void);
static FRAME_INFO frame__268_14 = {2, {"stream", "namespace"}};
static NODE *string__268_15;
static NODE *string__268_16;
static void cont__268_17(void);
static void cont__268_18(void);
static void cont__268_19(void);
static void cont__268_20(void);
static void cont__268_21(void);
static NODE *func__268_22;
static void entry__268_22(void);
static FRAME_INFO frame__268_22 = {3, {"alias", "stream", "namespace"}};
static void cont__268_23(void);
static void cont__268_24(void);
static NODE *func__268_25;
static void entry__268_25(void);
static FRAME_INFO frame__268_25 = {2, {"stream", "alias"}};
static NODE *string__268_26;
static NODE *string__268_27;
static void cont__268_28(void);
static void cont__268_29(void);
static void cont__268_30(void);
static void cont__268_31(void);
static NODE *string__268_32;
static NODE *string__268_33;
static void cont__268_34(void);
static void cont__269_1(void);
static void cont__269_2(void);
static NODE *func__269_3;
static void entry__269_3(void);
static FRAME_INFO frame__269_3 = {3, {"node", "stream", "namespace"}};
static void cont__269_4(void);
static void cont__269_5(void);
static NODE *func__269_6;
static void entry__269_6(void);
static FRAME_INFO frame__269_6 = {2, {"stream", "namespace"}};
static NODE *string__269_7;
static NODE *string__269_8;
static void cont__269_9(void);
static void cont__269_10(void);
static void cont__269_11(void);
static void cont__269_12(void);
static NODE *string__269_13;
static NODE *string__269_14;
static void cont__269_15(void);
static void cont__270_1(void);
static void cont__270_2(void);
static NODE *string__271_1;
static void cont__271_2(void);
static NODE *string__271_3;
static void cont__271_4(void);
static void cont__271_5(void);
static void cont__271_6(void);
static void cont__271_7(void);
static void cont__272_1(void);
static void cont__272_2(void);
static NODE *func__272_3;
static void entry__272_3(void);
static FRAME_INFO frame__272_3 = {3, {"node", "stream", "filename"}};
static void cont__272_4(void);
static void cont__272_5(void);
static NODE *func__272_6;
static void entry__272_6(void);
static FRAME_INFO frame__272_6 = {2, {"stream", "filename"}};
static NODE *string__272_7;
static NODE *string__272_8;
static void cont__272_9(void);
static void cont__272_10(void);
static void cont__272_11(void);
static void cont__272_12(void);
static NODE *string__272_13;
static NODE *string__272_14;
static void cont__272_15(void);
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
static NODE *string__273_14;
static void cont__273_15(void);
static void cont__274_1(void);
static void cont__274_2(void);
static NODE *string__275_1;
static void cont__275_2(void);
static NODE *string__275_3;
static void cont__275_4(void);
static void cont__275_5(void);
static void cont__275_6(void);
static void cont__275_7(void);
static void cont__276_1(void);
static void cont__276_2(void);
static NODE *func__276_3;
static void entry__276_3(void);
static FRAME_INFO frame__276_3 = {3, {"node", "stream", "filemask"}};
static void cont__276_4(void);
static void cont__276_5(void);
static NODE *func__276_6;
static void entry__276_6(void);
static FRAME_INFO frame__276_6 = {2, {"stream", "filemask"}};
static NODE *string__276_7;
static NODE *string__276_8;
static void cont__276_9(void);
static void cont__276_10(void);
static void cont__276_11(void);
static void cont__276_12(void);
static NODE *string__276_13;
static NODE *string__276_14;
static void cont__276_15(void);
static void cont__277_1(void);
static void cont__277_2(void);
static void cont__277_3(void);
static void cont__277_4(void);
static void cont__277_5(void);
static void cont__277_6(void);
static void cont__278_1(void);
static void cont__278_2(void);
static void cont__279_1(void);
static void cont__279_2(void);
static void cont__279_3(void);
static void cont__279_4(void);
static void cont__279_5(void);
static void cont__280_1(void);
static void cont__280_2(void);
static void cont__281_1(void);
static void cont__282_1(void);
static NODE *func__283_1;
static void entry__283_1(void);
static FRAME_INFO frame__283_1 = {1, {"node"}};
static void cont__283_2(void);
static NODE *func__283_3;
static void entry__283_3(void);
static FRAME_INFO frame__283_3 = {1, {"node"}};
static void cont__283_4(void);
static void cont__283_5(void);
static NODE *func__283_6;
static void entry__283_6(void);
static FRAME_INFO frame__283_6 = {2, {"node", "remark_lines"}};
static void cont__283_7(void);
static void cont__283_8(void);
static void cont__283_9(void);
static NODE *func__283_10;
static void entry__283_10(void);
static FRAME_INFO frame__283_10 = {2, {"node", "remark_lines"}};
static NODE *func__283_11;
static void entry__283_11(void);
static FRAME_INFO frame__283_11 = {2, {"node", "remark_lines"}};
static void cont__283_12(void);
static void cont__283_13(void);
static void cont__283_14(void);
static void cont__283_15(void);
static void cont__283_16(void);
static void cont__283_17(void);
static void cont__283_18(void);
static void cont__283_19(void);
static void cont__283_20(void);
static void cont__283_21(void);
static void cont__283_22(void);
static void cont__283_23(void);
static void cont__283_24(void);
static NODE *func__284_1;
static void entry__284_1(void);
static FRAME_INFO frame__284_1 = {2, {"node", "stream"}};
static void cont__284_2(void);
static void cont__284_3(void);
static NODE *func__284_4;
static void entry__284_4(void);
static FRAME_INFO frame__284_4 = {1, {"node"}};
static void cont__284_5(void);
static void cont__284_6(void);
static void cont__284_7(void);
static void cont__284_8(void);
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
static NODE *string__309_2;
static void cont__309_3(void);
static void cont__309_4(void);
static NODE *string__309_5;
static void cont__309_6(void);
static void cont__309_7(void);
static NODE *string__309_8;
static void cont__309_9(void);
static void cont__309_10(void);
static void cont__309_11(void);
static void cont__309_12(void);
static NODE *func__309_13;
static void entry__309_13(void);
static FRAME_INFO frame__309_13 = {1, {"node"}};
static void cont__309_14(void);
static void cont__309_15(void);
static void cont__309_16(void);
static void cont__309_17(void);
static void cont__309_18(void);
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
static NODE *string__323_2;
static void cont__323_3(void);
static void cont__323_4(void);
static void cont__323_5(void);
static void cont__323_6(void);
static void cont__323_7(void);
static void cont__324_1(void);
static void cont__325_1(void);
static void cont__325_2(void);
static void cont__325_3(void);
static NODE *string__326_1;
static NODE *string__326_2;
static NODE *string__326_3;
static NODE *string__326_4;
static NODE *string__326_5;
static NODE *string__326_6;
static NODE *string__326_7;
static NODE *string__326_8;
static NODE *string__326_9;
static NODE *string__326_10;
static NODE *string__326_11;
static void cont__326_12(void);
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
static NODE *string__380_16;
static void cont__380_17(void);
static void cont__380_18(void);
static void cont__380_19(void);
static NODE *string__380_20;
static void cont__380_21(void);
static void cont__380_22(void);
static void cont__380_23(void);
static void cont__380_24(void);
static NODE *string__381_1;
static void cont__381_2(void);
static void cont__381_3(void);
static void cont__381_4(void);
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
static NODE *string__385_2;
static void cont__385_3(void);
static void cont__386_1(void);
static NODE *string__386_2;
static void cont__386_3(void);
static void cont__387_1(void);
static void cont__387_2(void);
static void cont__387_3(void);
static void cont__388_1(void);
static void cont__388_2(void);
static void cont__388_3(void);
static void cont__388_4(void);
static void cont__388_5(void);
static void cont__388_6(void);
static void cont__388_7(void);
static void cont__388_8(void);
static void cont__388_9(void);
static void cont__388_10(void);
static void cont__388_11(void);
static void cont__388_12(void);
static void cont__388_13(void);
static void cont__388_14(void);
static void cont__388_15(void);
static void cont__389_1(void);
static void cont__390_1(void);
static NODE *string__390_2;
static void cont__390_3(void);
static void cont__390_4(void);
static void cont__390_5(void);
static void cont__390_6(void);
static void cont__391_1(void);
static void cont__391_2(void);
static void cont__391_3(void);
static void cont__391_4(void);
static void cont__391_5(void);
static void cont__391_6(void);
static void cont__391_7(void);
static void cont__391_8(void);
static void cont__392_1(void);
static void cont__392_2(void);
static void cont__393_1(void);
static void cont__393_2(void);
static void cont__393_3(void);
static void cont__393_4(void);
static void cont__394_1(void);
static void cont__395_1(void);
static void cont__395_2(void);
static void cont__395_3(void);
static NODE *string__395_4;
static void cont__395_5(void);
static void cont__396_1(void);
static void cont__396_2(void);
static void cont__396_3(void);
static void cont__396_4(void);
static NODE *string__396_5;
static void cont__396_6(void);
static void cont__396_7(void);
static void cont__396_8(void);
static void cont__396_9(void);
static void cont__396_10(void);
static void cont__397_1(void);
static NODE *string__397_2;
static void cont__397_3(void);
static void cont__397_4(void);
static void cont__397_5(void);
static void cont__397_6(void);
static void cont__397_7(void);
static void cont__397_8(void);
static void cont__398_1(void);
static void cont__398_2(void);
static void cont__398_3(void);
static void cont__399_1(void);
static void cont__399_2(void);
static void cont__399_3(void);
static NODE *string__399_4;
static void cont__399_5(void);
static void cont__400_1(void);
static void cont__400_2(void);
static void cont__400_3(void);
static NODE *string__400_4;
static void cont__400_5(void);
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
static NODE *string__404_1;
static NODE *string__404_2;
static NODE *string__404_3;
static NODE *string__404_4;
static void cont__404_5(void);
static void cont__404_6(void);
static void cont__404_7(void);
static void cont__404_8(void);
static NODE *string__404_9;
static void cont__404_10(void);
static void cont__405_1(void);
static void cont__405_2(void);
static void cont__405_3(void);
static NODE *string__405_4;
static void cont__405_5(void);
static NODE *string__406_1;
static void cont__406_2(void);
static void cont__406_3(void);
static void cont__407_1(void);
static void cont__407_2(void);
static void cont__408_1(void);
static NODE *string__409_1;
static void cont__409_2(void);
static void cont__410_1(void);
static void cont__410_2(void);
static void cont__411_1(void);
static void cont__411_2(void);
static void cont__411_3(void);
static void cont__411_4(void);
static void cont__411_5(void);
static void cont__412_1(void);
static void cont__412_2(void);
static void cont__412_3(void);
static void cont__412_4(void);
static void cont__412_5(void);
static void cont__412_6(void);
static void cont__412_7(void);
static void cont__412_8(void);
static void cont__412_9(void);
static void cont__412_10(void);
static void cont__413_1(void);
static void cont__413_2(void);
static void cont__413_3(void);
static NODE *string__414_1;
static void cont__414_2(void);
static void cont__414_3(void);
static void cont__414_4(void);
static void cont__414_5(void);
static void cont__414_6(void);
void run__parser(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__original_remark_lines_of, NULL, 1148, 1148, 2, 25},
  {run__parser, NULL, 202, 202, 5, 12},
  {cont__235_2, NULL, 203, 203, 5, 12},
  {cont__235_4, NULL, 204, 204, 5, 12},
  {cont__235_6, NULL, 205, 205, 5, 12},
  {cont__235_8, NULL, 206, 206, 5, 13},
  {cont__235_10, NULL, 207, 207, 5, 13},
  {cont__235_12, NULL, 208, 208, 5, 12},
  {cont__235_14, NULL, 209, 209, 5, 12},
  {cont__235_16, NULL, 210, 210, 5, 11},
  {cont__235_18, NULL, 211, 211, 5, 12},
  {cont__235_20, NULL, 212, 212, 5, 11},
  {cont__235_22, NULL, 213, 213, 5, 12},
  {cont__235_24, NULL, 214, 214, 5, 11},
  {cont__235_26, NULL, 215, 215, 5, 12},
  {cont__235_28, NULL, 216, 216, 5, 12},
  {cont__235_30, NULL, 217, 217, 5, 12},
  {cont__235_32, NULL, 218, 218, 5, 12},
  {cont__235_34, NULL, 219, 219, 5, 12},
  {cont__235_36, NULL, 220, 220, 5, 11},
  {cont__235_38, NULL, 221, 221, 5, 11},
  {cont__235_40, NULL, 200, 221, 1, 12},
  {cont__235_41, NULL, 247, 253, 1, 15},
  {cont__245_5, NULL, 255, 255, 10, 29},
  {cont__246_1, NULL, 255, 255, 1, 50},
  {cont__246_2, NULL, 256, 256, 9, 34},
  {cont__247_1, NULL, 256, 256, 1, 61},
  {cont__247_2, NULL, 257, 257, 10, 36},
  {cont__248_1, NULL, 257, 257, 1, 64},
  {cont__248_2, NULL, 258, 258, 10, 25},
  {cont__249_1, NULL, 258, 258, 1, 42},
  {cont__249_2, NULL, 266, 275, 1, 49},
  {cont__251_3, NULL, 277, 280, 1, 35},
  {cont__252_2, NULL, 288, 288, 1, 28},
  {cont__255_1, NULL, 289, 289, 34, 49},
  {cont__256_1, NULL, 289, 289, 1, 50},
  {cont__256_2, NULL, 290, 290, 1, 23},
  {cont__257_1, NULL, 291, 291, 1, 45},
  {cont__258_1, NULL, 293, 301, 1, 42},
  {cont__259_3, NULL, 303, 311, 1, 42},
  {cont__260_4, NULL, 313, 321, 1, 42},
  {cont__261_4, NULL, 323, 330, 1, 47},
  {cont__262_3, NULL, 334, 334, 5, 24},
  {cont__263_1, NULL, 336, 336, 5, 25},
  {cont__263_2, NULL, 340, 342, 9, 43},
  {cont__263_5, NULL, 343, 343, 9, 29},
  {cont__263_6, NULL, 338, 343, 7, 28},
  {cont__263_8, NULL, 337, 343, 5, 29},
  {cont__263_9, NULL, 332, 344, 1, 23},
  {cont__263_10, NULL, 348, 348, 5, 24},
  {cont__264_1, NULL, 350, 350, 5, 22},
  {cont__264_2, NULL, 351, 351, 5, 25},
  {cont__264_3, NULL, 355, 359, 9, 43},
  {cont__264_10, NULL, 360, 360, 9, 29},
  {cont__264_11, NULL, 353, 360, 7, 28},
  {cont__264_13, NULL, 352, 360, 5, 29},
  {cont__264_14, NULL, 346, 361, 1, 23},
  {cont__264_15, NULL, 365, 365, 5, 24},
  {cont__265_1, NULL, 367, 367, 5, 30},
  {cont__265_2, NULL, 368, 368, 5, 16},
  {cont__265_4, NULL, 369, 369, 5, 25},
  {cont__265_5, NULL, 363, 369, 1, 26},
  {cont__265_6, NULL, 374, 374, 11, 24},
  {cont__266_2, NULL, 374, 374, 38, 46},
  {cont__266_4, NULL, 374, 374, 33, 47},
  {cont__266_5, NULL, 374, 374, 1, 47},
  {cont__266_6, NULL, 379, 379, 5, 33},
  {cont__267_1, NULL, 382, 382, 5, 39},
  {cont__267_2, NULL, 385, 391, 5, 40},
  {cont__267_13, NULL, 376, 391, 1, 43},
  {cont__267_16, NULL, 397, 397, 5, 35},
  {cont__268_1, NULL, 398, 398, 5, 30},
  {cont__268_2, NULL, 401, 401, 9, 27},
  {cont__268_4, NULL, 402, 404, 9, 54},
  {cont__268_7, NULL, 405, 405, 9, 34},
  {cont__268_8, NULL, 400, 405, 7, 33},
  {cont__268_9, NULL, 399, 405, 5, 34},
  {cont__268_10, NULL, 407, 419, 5, 47},
  {cont__268_31, NULL, 393, 419, 1, 50},
  {cont__268_34, NULL, 425, 425, 5, 31},
  {cont__269_1, NULL, 426, 426, 5, 30},
  {cont__269_2, NULL, 428, 434, 5, 40},
  {cont__269_12, NULL, 421, 434, 1, 43},
  {cont__269_15, NULL, 436, 436, 16, 40},
  {cont__270_1, NULL, 436, 436, 1, 41},
  {cont__270_2, NULL, 437, 437, 26, 36},
  {cont__271_2, NULL, 437, 437, 13, 37},
  {cont__271_4, NULL, 437, 437, 55, 67},
  {cont__271_5, NULL, 437, 437, 50, 68},
  {cont__271_6, NULL, 437, 437, 1, 68},
  {cont__271_7, NULL, 443, 443, 5, 33},
  {cont__272_1, NULL, 444, 444, 5, 41},
  {cont__272_2, NULL, 446, 452, 5, 38},
  {cont__272_12, NULL, 439, 452, 1, 41},
  {cont__272_15, NULL, 458, 458, 5, 30},
  {cont__273_1, NULL, 459, 459, 5, 41},
  {cont__273_2, NULL, 461, 467, 5, 40},
  {cont__273_12, NULL, 454, 467, 1, 43},
  {cont__273_15, NULL, 469, 469, 12, 44},
  {cont__274_1, NULL, 469, 469, 1, 45},
  {cont__274_2, NULL, 470, 470, 24, 34},
  {cont__275_2, NULL, 470, 470, 11, 35},
  {cont__275_4, NULL, 470, 470, 49, 57},
  {cont__275_5, NULL, 470, 470, 44, 58},
  {cont__275_6, NULL, 470, 470, 1, 58},
  {cont__275_7, NULL, 476, 476, 5, 30},
  {cont__276_1, NULL, 477, 477, 5, 39},
  {cont__276_2, NULL, 479, 485, 5, 38},
  {cont__276_12, NULL, 472, 485, 1, 41},
  {cont__276_15, NULL, 489, 489, 5, 50},
  {cont__277_1, NULL, 490, 490, 56, 77},
  {cont__277_2, NULL, 490, 490, 38, 77},
  {cont__277_3, NULL, 490, 490, 14, 78},
  {cont__277_4, NULL, 490, 490, 5, 79},
  {cont__277_5, NULL, 487, 490, 1, 80},
  {cont__277_6, NULL, 495, 495, 44, 68},
  {cont__278_1, NULL, 495, 495, 1, 69},
  {cont__278_2, NULL, 500, 500, 22, 53},
  {cont__279_1, NULL, 500, 500, 56, 77},
  {cont__279_2, NULL, 500, 500, 14, 77},
  {cont__279_3, NULL, 500, 500, 5, 78},
  {cont__279_4, NULL, 497, 500, 1, 79},
  {cont__279_5, NULL, 502, 502, 35, 60},
  {cont__280_1, NULL, 502, 502, 1, 74},
  {cont__280_2, NULL, 504, 504, 1, 67},
  {cont__281_1, NULL, 505, 505, 1, 29},
  {cont__282_1, NULL, 510, 519, 5, 43},
  {cont__283_23, NULL, 507, 519, 1, 46},
  {cont__283_24, NULL, 524, 532, 5, 43},
  {cont__284_7, NULL, 521, 532, 1, 46},
  {cont__284_8, NULL, 534, 534, 27, 65},
  {cont__285_1, NULL, 534, 534, 1, 66},
  {cont__285_2, NULL, 542, 550, 7, 48},
  {cont__286_22, NULL, 538, 550, 5, 49},
  {cont__286_23, NULL, 536, 550, 1, 52},
  {cont__286_24, NULL, 556, 562, 5, 46},
  {cont__287_22, NULL, 552, 562, 1, 49},
  {cont__287_23, NULL, 564, 564, 1, 60},
  {cont__288_1, NULL, 565, 565, 1, 32},
  {cont__289_1, NULL, 573, 579, 5, 58},
  {cont__290_4, NULL, 580, 580, 21, 63},
  {cont__290_5, NULL, 580, 580, 12, 64},
  {cont__290_6, NULL, 580, 580, 5, 65},
  {cont__290_7, NULL, 581, 581, 5, 15},
  {cont__290_8, NULL, 570, 582, 1, 23},
  {cont__290_9, NULL, 584, 592, 1, 58},
  {cont__291_5, NULL, 598, 598, 5, 31},
  {cont__292_1, NULL, 594, 599, 1, 23},
  {cont__292_2, NULL, 605, 605, 5, 40},
  {cont__293_1, NULL, 601, 606, 1, 23},
  {cont__293_2, NULL, 608, 608, 18, 52},
  {cont__294_1, NULL, 608, 608, 1, 53},
  {cont__294_2, NULL, 609, 609, 29, 62},
  {cont__295_1, NULL, 609, 609, 1, 63},
  {cont__295_2, NULL, 610, 610, 1, 51},
  {cont__296_1, NULL, 613, 613, 15, 46},
  {cont__297_1, NULL, 612, 613, 1, 69},
  {cont__297_2, NULL, 617, 617, 17, 27},
  {cont__298_1, NULL, 617, 617, 5, 37},
  {cont__298_2, NULL, 618, 618, 19, 29},
  {cont__298_3, NULL, 618, 618, 14, 29},
  {cont__298_4, NULL, 618, 618, 5, 30},
  {cont__298_5, NULL, 619, 619, 14, 25},
  {cont__298_6, NULL, 619, 619, 37, 48},
  {cont__298_7, NULL, 619, 619, 28, 49},
  {cont__298_8, NULL, 619, 619, 52, 62},
  {cont__298_9, NULL, 619, 619, 14, 62},
  {cont__298_10, NULL, 619, 619, 5, 63},
  {cont__298_11, NULL, 615, 619, 1, 64},
  {cont__298_12, NULL, 621, 621, 1, 26},
  {cont__299_1, NULL, 622, 622, 34, 51},
  {cont__300_1, NULL, 622, 622, 22, 61},
  {cont__300_2, NULL, 622, 622, 1, 61},
  {cont__300_4, NULL, 623, 623, 1, 23},
  {cont__301_1, NULL, 624, 624, 33, 49},
  {cont__302_1, NULL, 624, 624, 21, 59},
  {cont__302_2, NULL, 624, 624, 1, 59},
  {cont__302_4, NULL, 625, 625, 22, 31},
  {cont__303_1, NULL, 625, 625, 33, 42},
  {cont__303_2, NULL, 625, 625, 1, 43},
  {cont__303_3, NULL, 626, 626, 31, 45},
  {cont__304_1, NULL, 626, 626, 19, 55},
  {cont__304_2, NULL, 626, 626, 1, 55},
  {cont__304_4, NULL, 630, 630, 5, 29},
  {cont__305_1, NULL, 634, 634, 7, 63},
  {cont__305_2, NULL, 632, 634, 5, 62},
  {cont__305_3, NULL, 628, 635, 1, 23},
  {cont__305_4, NULL, 639, 639, 5, 47},
  {cont__306_1, NULL, 640, 642, 5, 52},
  {cont__306_5, NULL, 637, 642, 1, 55},
  {cont__306_6, NULL, 647, 649, 5, 33},
  {cont__307_2, NULL, 644, 649, 1, 36},
  {cont__307_3, NULL, 653, 653, 5, 32},
  {cont__308_1, NULL, 655, 663, 5, 32},
  {cont__308_9, NULL, 651, 663, 1, 35},
  {cont__308_10, NULL, 670, 670, 15, 32},
  {cont__309_1, NULL, 670, 670, 9, 32},
  {cont__309_3, NULL, 671, 671, 15, 31},
  {cont__309_4, NULL, 671, 671, 9, 31},
  {cont__309_6, NULL, 672, 672, 15, 29},
  {cont__309_7, NULL, 672, 672, 9, 29},
  {cont__309_9, NULL, 673, 673, 9, 19},
  {cont__309_10, NULL, 669, 673, 7, 18},
  {cont__309_11, NULL, 667, 673, 5, 19},
  {cont__309_12, NULL, 675, 677, 5, 71},
  {cont__309_17, NULL, 665, 677, 1, 74},
  {cont__309_18, NULL, 684, 684, 5, 45},
  {cont__310_2, NULL, 679, 684, 1, 46},
  {cont__310_3, NULL, 686, 686, 23, 45},
  {cont__311_1, NULL, 686, 686, 1, 63},
  {cont__311_2, NULL, 691, 691, 5, 31},
  {cont__312_1, NULL, 694, 694, 5, 20},
  {cont__312_2, NULL, 688, 695, 1, 23},
  {cont__312_3, NULL, 702, 704, 7, 55},
  {cont__313_5, NULL, 700, 704, 5, 56},
  {cont__313_6, NULL, 697, 704, 1, 59},
  {cont__313_8, NULL, 709, 713, 5, 30},
  {cont__314_9, NULL, 714, 714, 17, 42},
  {cont__314_10, NULL, 714, 714, 5, 61},
  {cont__314_11, NULL, 715, 715, 5, 15},
  {cont__314_12, NULL, 706, 715, 1, 16},
  {cont__314_14, NULL, 717, 730, 1, 55},
  {cont__315_20, NULL, 737, 737, 5, 28},
  {cont__316_1, NULL, 739, 739, 10, 34},
  {cont__316_2, NULL, 739, 739, 37, 74},
  {cont__316_3, NULL, 739, 739, 10, 74},
  {cont__316_4, NULL, 739, 739, 5, 75},
  {cont__316_5, NULL, 732, 742, 1, 21},
  {cont__316_6, NULL, 747, 747, 19, 31},
  {cont__317_1, NULL, 747, 747, 7, 32},
  {cont__317_2, NULL, 748, 748, 7, 32},
  {cont__317_3, NULL, 749, 749, 7, 35},
  {cont__317_4, NULL, 750, 750, 7, 35},
  {cont__317_5, NULL, 746, 750, 5, 34},
  {cont__317_6, NULL, 744, 750, 1, 37},
  {cont__317_7, NULL, 752, 755, 1, 62},
  {cont__318_5, NULL, 760, 760, 5, 31},
  {cont__319_1, NULL, 764, 764, 10, 43},
  {cont__319_2, NULL, 764, 764, 5, 44},
  {cont__319_3, NULL, 765, 765, 9, 21},
  {cont__319_4, NULL, 765, 765, 23, 44},
  {cont__319_5, NULL, 765, 765, 23, 58},
  {cont__319_6, NULL, 765, 765, 5, 59},
  {cont__319_7, NULL, 757, 767, 1, 21},
  {cont__319_8, NULL, 769, 769, 19, 41},
  {cont__320_1, NULL, 769, 769, 44, 64},
  {cont__320_2, NULL, 769, 769, 1, 64},
  {cont__320_3, NULL, 774, 774, 32, 66},
  {cont__321_2, NULL, 774, 774, 12, 67},
  {cont__321_3, NULL, 774, 774, 5, 68},
  {cont__321_4, NULL, 775, 775, 5, 15},
  {cont__321_5, NULL, 771, 775, 1, 16},
  {cont__321_6, NULL, 781, 788, 5, 60},
  {cont__322_10, NULL, 777, 789, 1, 23},
  {cont__322_12, NULL, 796, 803, 5, 58},
  {cont__323_6, NULL, 791, 804, 1, 23},
  {cont__323_7, NULL, 806, 807, 1, 81},
  {cont__324_1, NULL, 809, 809, 58, 79},
  {cont__325_1, NULL, 809, 809, 42, 79},
  {cont__325_2, NULL, 809, 809, 1, 80},
  {cont__325_3, NULL, 811, 831, 1, 9},
  {cont__326_12, NULL, 834, 834, 18, 66},
  {cont__327_1, NULL, 833, 834, 1, 67},
  {cont__327_2, NULL, 836, 836, 17, 47},
  {cont__328_1, NULL, 836, 836, 1, 66},
  {cont__328_2, NULL, 842, 842, 5, 39},
  {cont__329_1, NULL, 844, 844, 5, 29},
  {cont__329_2, NULL, 838, 844, 1, 30},
  {cont__329_3, NULL, 848, 848, 5, 56},
  {cont__330_1, NULL, 849, 858, 5, 60},
  {cont__330_14, NULL, 846, 858, 1, 63},
  {cont__330_15, NULL, 860, 910, 1, 70},
  {cont__331_63, NULL, 914, 914, 5, 24},
  {cont__332_1, NULL, 915, 915, 5, 27},
  {cont__332_2, NULL, 917, 917, 22, 52},
  {cont__332_3, NULL, 917, 917, 7, 53},
  {cont__332_4, NULL, 917, 917, 7, 74},
  {cont__332_5, NULL, 918, 918, 28, 50},
  {cont__332_6, NULL, 918, 918, 12, 50},
  {cont__332_7, NULL, 918, 918, 7, 51},
  {cont__332_8, NULL, 916, 918, 5, 50},
  {cont__332_9, NULL, 912, 919, 1, 22},
  {cont__332_10, NULL, 921, 921, 26, 62},
  {cont__333_1, NULL, 921, 921, 1, 76},
  {cont__333_3, NULL, 924, 924, 15, 63},
  {cont__334_1, NULL, 923, 924, 1, 63},
  {cont__334_2, NULL, 934, 934, 13, 55},
  {cont__335_1, NULL, 935, 935, 13, 50},
  {cont__335_2, NULL, 932, 935, 11, 49},
  {cont__335_3, NULL, 936, 936, 24, 39},
  {cont__335_4, NULL, 936, 936, 41, 80},
  {cont__335_5, NULL, 936, 936, 11, 81},
  {cont__335_6, NULL, 939, 939, 13, 52},
  {cont__335_7, NULL, 940, 940, 13, 50},
  {cont__335_8, NULL, 937, 940, 11, 49},
  {cont__335_9, NULL, 931, 940, 9, 50},
  {cont__335_10, NULL, 930, 940, 7, 51},
  {cont__335_11, NULL, 929, 940, 5, 52},
  {cont__335_12, NULL, 926, 940, 1, 55},
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
  {cont__359_5, NULL, 1124, 1146, 5, 54},
  {cont__359_21, NULL, 1114, 1146, 1, 57},
  {cont__359_22, NULL, 1154, 1157, 7, 42},
  {cont__361_3, NULL, 1159, 1166, 7, 50},
  {cont__361_19, NULL, 1167, 1167, 11, 61},
  {cont__361_20, NULL, 1167, 1167, 7, 70},
  {cont__361_21, NULL, 1152, 1167, 5, 69},
  {cont__361_22, NULL, 1150, 1168, 1, 29},
  {cont__361_23, NULL, 1171, 1171, 11, 23},
  {cont__362_1, NULL, 1170, 1171, 1, 57},
  {cont__362_2, NULL, 1174, 1174, 28, 77},
  {cont__363_1, NULL, 1174, 1174, 16, 78},
  {cont__363_2, NULL, 1174, 1174, 11, 78},
  {cont__363_3, NULL, 1173, 1174, 1, 79},
  {cont__363_4, NULL, 1178, 1178, 5, 29},
  {cont__364_1, NULL, 1180, 1180, 5, 42},
  {cont__364_2, NULL, 1181, 1187, 5, 58},
  {cont__364_6, NULL, 1191, 1191, 5, 26},
  {cont__364_7, NULL, 1192, 1220, 5, 63},
  {cont__364_43, NULL, 1176, 1220, 1, 66},
  {cont__364_44, NULL, 1226, 1226, 38, 72},
  {cont__365_1, NULL, 1226, 1226, 9, 72},
  {cont__365_2, NULL, 1225, 1226, 7, 71},
  {cont__365_3, NULL, 1232, 1232, 17, 43},
  {cont__365_4, NULL, 1232, 1232, 17, 66},
  {cont__365_5, NULL, 1234, 1234, 17, 38},
  {cont__365_6, NULL, 1235, 1235, 17, 25},
  {cont__365_7, NULL, 1231, 1235, 15, 24},
  {cont__365_8, NULL, 1230, 1235, 13, 25},
  {cont__365_9, NULL, 1236, 1244, 13, 64},
  {cont__365_18, NULL, 1229, 1245, 11, 33},
  {cont__365_19, NULL, 1248, 1248, 22, 52},
  {cont__365_20, NULL, 1248, 1248, 13, 53},
  {cont__365_21, NULL, 1246, 1248, 11, 52},
  {cont__365_22, NULL, 1228, 1248, 9, 53},
  {cont__365_23, NULL, 1227, 1248, 7, 54},
  {cont__365_24, NULL, 1224, 1248, 5, 55},
  {cont__365_25, NULL, 1249, 1249, 32, 66},
  {cont__365_26, NULL, 1249, 1249, 20, 66},
  {cont__365_27, NULL, 1249, 1249, 5, 67},
  {cont__365_28, NULL, 1250, 1250, 5, 41},
  {cont__365_29, NULL, 1222, 1250, 1, 42},
  {cont__365_30, NULL, 1254, 1254, 35, 70},
  {cont__366_1, NULL, 1254, 1254, 26, 71},
  {cont__366_2, NULL, 1254, 1254, 5, 71},
  {cont__366_3, NULL, 1256, 1256, 7, 46},
  {cont__366_4, NULL, 1257, 1257, 11, 30},
  {cont__366_5, NULL, 1257, 1257, 41, 75},
  {cont__366_6, NULL, 1257, 1257, 32, 76},
  {cont__366_7, NULL, 1257, 1257, 7, 77},
  {cont__366_8, NULL, 1255, 1257, 5, 76},
  {cont__366_9, NULL, 1252, 1257, 1, 79},
  {cont__366_10, NULL, 1261, 1261, 29, 63},
  {cont__367_1, NULL, 1261, 1261, 20, 64},
  {cont__367_2, NULL, 1261, 1261, 5, 64},
  {cont__367_3, NULL, 1259, 1262, 1, 25},
  {cont__367_4, NULL, 1266, 1266, 28, 62},
  {cont__368_1, NULL, 1266, 1266, 19, 63},
  {cont__368_2, NULL, 1266, 1266, 5, 63},
  {cont__368_3, NULL, 1264, 1267, 1, 25},
  {cont__368_4, NULL, 1271, 1271, 5, 54},
  {cont__369_1, NULL, 1272, 1272, 5, 34},
  {cont__369_2, NULL, 1276, 1276, 12, 27},
  {cont__369_3, NULL, 1276, 1276, 7, 28},
  {cont__369_4, NULL, 1277, 1277, 7, 48},
  {cont__369_5, NULL, 1278, 1278, 7, 28},
  {cont__369_6, NULL, 1273, 1278, 5, 27},
  {cont__369_7, NULL, 1269, 1278, 1, 30},
  {cont__369_8, NULL, 1285, 1285, 9, 37},
  {cont__370_1, NULL, 1286, 1286, 9, 49},
  {cont__370_2, NULL, 1283, 1286, 7, 48},
  {cont__370_3, NULL, 1289, 1289, 9, 37},
  {cont__370_4, NULL, 1290, 1290, 9, 50},
  {cont__370_5, NULL, 1287, 1290, 7, 49},
  {cont__370_6, NULL, 1293, 1293, 9, 37},
  {cont__370_7, NULL, 1294, 1294, 9, 53},
  {cont__370_8, NULL, 1291, 1294, 7, 52},
  {cont__370_9, NULL, 1295, 1295, 7, 36},
  {cont__370_10, NULL, 1295, 1295, 39, 79},
  {cont__370_11, NULL, 1295, 1295, 7, 79},
  {cont__370_12, NULL, 1282, 1295, 5, 78},
  {cont__370_13, NULL, 1280, 1295, 1, 81},
  {cont__370_14, NULL, 1302, 1302, 9, 27},
  {cont__371_1, NULL, 1303, 1303, 9, 43},
  {cont__371_2, NULL, 1304, 1304, 9, 41},
  {cont__371_3, NULL, 1301, 1304, 7, 40},
  {cont__371_4, NULL, 1305, 1305, 12, 56},
  {cont__371_5, NULL, 1305, 1305, 7, 56},
  {cont__371_6, NULL, 1299, 1305, 5, 55},
  {cont__371_7, NULL, 1297, 1305, 1, 58},
  {cont__371_8, NULL, 1310, 1312, 5, 30},
  {cont__372_2, NULL, 1307, 1312, 1, 33},
  {cont__372_3, NULL, 1318, 1318, 7, 26},
  {cont__373_1, NULL, 1320, 1320, 7, 24},
  {cont__373_2, NULL, 1321, 1321, 7, 27},
  {cont__373_3, NULL, 1317, 1322, 5, 23},
  {cont__373_4, NULL, 1314, 1322, 1, 26},
  {cont__373_5, NULL, 1324, 1324, 1, 68},
  {cont__374_1, NULL, 1327, 1327, 49, 71},
  {cont__375_1, NULL, 1327, 1327, 40, 72},
  {cont__375_2, NULL, 1326, 1327, 1, 72},
  {cont__375_3, NULL, 1333, 1333, 5, 34},
  {cont__376_1, NULL, 1334, 1334, 5, 55},
  {cont__376_2, NULL, 1329, 1335, 1, 19},
  {cont__376_4, NULL, 1338, 1338, 52, 74},
  {cont__377_1, NULL, 1338, 1338, 43, 75},
  {cont__377_2, NULL, 1337, 1338, 1, 75},
  {cont__377_3, NULL, 1346, 1346, 23, 57},
  {cont__378_1, NULL, 1346, 1346, 11, 76},
  {cont__378_2, NULL, 1347, 1347, 39, 76},
  {cont__378_3, NULL, 1347, 1347, 20, 76},
  {cont__378_4, NULL, 1347, 1347, 11, 77},
  {cont__378_5, NULL, 1345, 1347, 9, 76},
  {cont__378_6, NULL, 1348, 1348, 9, 46},
  {cont__378_7, NULL, 1344, 1348, 7, 45},
  {cont__378_8, NULL, 1343, 1348, 5, 46},
  {cont__378_9, NULL, 1349, 1349, 5, 15},
  {cont__378_10, NULL, 1340, 1349, 1, 16},
  {cont__378_11, NULL, 1357, 1357, 21, 66},
  {cont__379_1, NULL, 1357, 1357, 9, 75},
  {cont__379_2, NULL, 1358, 1358, 27, 75},
  {cont__379_3, NULL, 1358, 1358, 18, 75},
  {cont__379_4, NULL, 1358, 1358, 9, 76},
  {cont__379_5, NULL, 1356, 1358, 7, 75},
  {cont__379_6, NULL, 1359, 1359, 7, 55},
  {cont__379_7, NULL, 1355, 1359, 5, 54},
  {cont__379_8, NULL, 1360, 1360, 5, 26},
  {cont__379_9, NULL, 1361, 1361, 5, 19},
  {cont__379_10, NULL, 1362, 1362, 5, 15},
  {cont__379_11, NULL, 1351, 1362, 1, 16},
  {cont__379_12, NULL, 1367, 1367, 5, 18},
  {cont__380_1, NULL, 1369, 1369, 5, 33},
  {cont__380_2, NULL, 1374, 1374, 16, 31},
  {cont__380_3, NULL, 1374, 1374, 11, 32},
  {cont__380_4, NULL, 1378, 1378, 11, 32},
  {cont__380_5, NULL, 1372, 1378, 9, 31},
  {cont__380_6, NULL, 1380, 1380, 20, 55},
  {cont__380_7, NULL, 1380, 1380, 11, 56},
  {cont__380_8, NULL, 1383, 1383, 21, 38},
  {cont__380_9, NULL, 1383, 1383, 53, 74},
  {cont__380_10, NULL, 1383, 1383, 13, 74},
  {cont__380_11, NULL, 1386, 1386, 46, 79},
  {cont__380_13, NULL, 1386, 1386, 15, 80},
  {cont__380_14, NULL, 1384, 1386, 13, 79},
  {cont__380_15, NULL, 1387, 1387, 13, 46},
  {cont__380_17, NULL, 1382, 1387, 11, 45},
  {cont__380_18, NULL, 1379, 1387, 9, 46},
  {cont__380_19, NULL, 1388, 1388, 9, 42},
  {cont__380_21, NULL, 1371, 1388, 7, 41},
  {cont__380_22, NULL, 1370, 1388, 5, 42},
  {cont__380_23, NULL, 1364, 1389, 1, 23},
  {cont__380_24, NULL, 1393, 1393, 5, 21},
  {cont__381_2, NULL, 1394, 1394, 5, 18},
  {cont__381_3, NULL, 1391, 1397, 1, 23},
  {cont__381_4, NULL, 1399, 1399, 1, 42},
  {cont__382_1, NULL, 1404, 1404, 5, 20},
  {cont__383_1, NULL, 1406, 1406, 5, 25},
  {cont__383_2, NULL, 1407, 1407, 28, 51},
  {cont__383_3, NULL, 1407, 1407, 28, 66},
  {cont__383_4, NULL, 1407, 1407, 23, 67},
  {cont__383_5, NULL, 1407, 1407, 5, 68},
  {cont__383_6, NULL, 1408, 1408, 5, 26},
  {cont__383_7, NULL, 1409, 1409, 5, 19},
  {cont__383_8, NULL, 1410, 1410, 5, 15},
  {cont__383_9, NULL, 1401, 1411, 1, 23},
  {cont__383_10, NULL, 1413, 1413, 37, 70},
  {cont__384_1, NULL, 1413, 1413, 1, 71},
  {cont__384_2, NULL, 1414, 1414, 44, 73},
  {cont__385_1, NULL, 1414, 1414, 1, 73},
  {cont__385_3, NULL, 1417, 1417, 10, 51},
  {cont__386_1, NULL, 1416, 1417, 1, 51},
  {cont__386_3, NULL, 1423, 1423, 7, 79},
  {cont__387_1, NULL, 1422, 1423, 5, 78},
  {cont__387_2, NULL, 1419, 1424, 1, 20},
  {cont__387_3, NULL, 1428, 1428, 5, 24},
  {cont__388_1, NULL, 1431, 1431, 7, 48},
  {cont__388_2, NULL, 1431, 1431, 7, 71},
  {cont__388_3, NULL, 1433, 1433, 9, 51},
  {cont__388_4, NULL, 1434, 1434, 9, 55},
  {cont__388_5, NULL, 1432, 1434, 7, 54},
  {cont__388_6, NULL, 1435, 1435, 7, 49},
  {cont__388_7, NULL, 1435, 1435, 7, 72},
  {cont__388_8, NULL, 1436, 1436, 7, 50},
  {cont__388_9, NULL, 1436, 1436, 7, 73},
  {cont__388_10, NULL, 1438, 1438, 9, 37},
  {cont__388_11, NULL, 1439, 1439, 9, 65},
  {cont__388_12, NULL, 1437, 1439, 7, 64},
  {cont__388_13, NULL, 1430, 1439, 5, 65},
  {cont__388_14, NULL, 1426, 1440, 1, 23},
  {cont__388_15, NULL, 1442, 1442, 1, 53},
  {cont__389_1, NULL, 1446, 1446, 11, 42},
  {cont__390_1, NULL, 1446, 1446, 5, 47},
  {cont__390_3, NULL, 1447, 1447, 10, 41},
  {cont__390_4, NULL, 1447, 1447, 5, 41},
  {cont__390_5, NULL, 1444, 1447, 1, 42},
  {cont__390_6, NULL, 1451, 1451, 5, 28},
  {cont__391_1, NULL, 1454, 1454, 5, 42},
  {cont__391_2, NULL, 1463, 1463, 13, 52},
  {cont__391_3, NULL, 1460, 1463, 11, 51},
  {cont__391_4, NULL, 1459, 1465, 9, 28},
  {cont__391_5, NULL, 1456, 1465, 7, 29},
  {cont__391_6, NULL, 1455, 1466, 5, 24},
  {cont__391_7, NULL, 1449, 1467, 1, 23},
  {cont__391_8, NULL, 1469, 1469, 27, 54},
  {cont__392_1, NULL, 1469, 1469, 1, 63},
  {cont__392_2, NULL, 1475, 1475, 5, 34},
  {cont__393_1, NULL, 1475, 1475, 37, 62},
  {cont__393_2, NULL, 1475, 1475, 5, 62},
  {cont__393_3, NULL, 1471, 1476, 1, 28},
  {cont__393_4, NULL, 1478, 1478, 1, 53},
  {cont__394_1, NULL, 1486, 1486, 9, 34},
  {cont__395_1, NULL, 1485, 1489, 7, 25},
  {cont__395_2, NULL, 1483, 1489, 5, 26},
  {cont__395_3, NULL, 1480, 1489, 1, 29},
  {cont__395_5, NULL, 1494, 1494, 7, 38},
  {cont__396_1, NULL, 1494, 1494, 50, 76},
  {cont__396_2, NULL, 1494, 1494, 41, 77},
  {cont__396_3, NULL, 1494, 1494, 7, 77},
  {cont__396_4, NULL, 1496, 1496, 7, 40},
  {cont__396_6, NULL, 1493, 1496, 5, 39},
  {cont__396_7, NULL, 1497, 1497, 10, 36},
  {cont__396_8, NULL, 1497, 1497, 5, 37},
  {cont__396_9, NULL, 1491, 1497, 1, 38},
  {cont__396_10, NULL, 1502, 1502, 5, 24},
  {cont__397_1, NULL, 1502, 1502, 54, 63},
  {cont__397_3, NULL, 1502, 1502, 49, 64},
  {cont__397_4, NULL, 1502, 1502, 43, 64},
  {cont__397_5, NULL, 1502, 1502, 27, 65},
  {cont__397_6, NULL, 1502, 1502, 5, 65},
  {cont__397_7, NULL, 1499, 1502, 1, 66},
  {cont__397_8, NULL, 1504, 1504, 20, 39},
  {cont__398_1, NULL, 1504, 1504, 20, 54},
  {cont__398_2, NULL, 1504, 1504, 1, 55},
  {cont__398_3, NULL, 1509, 1509, 31, 70},
  {cont__399_1, NULL, 1509, 1509, 12, 70},
  {cont__399_2, NULL, 1509, 1509, 5, 71},
  {cont__399_3, NULL, 1506, 1509, 1, 72},
  {cont__399_5, NULL, 1512, 1512, 37, 71},
  {cont__400_1, NULL, 1512, 1512, 18, 71},
  {cont__400_2, NULL, 1512, 1512, 11, 72},
  {cont__400_3, NULL, 1511, 1512, 1, 72},
  {cont__400_5, NULL, 1514, 1514, 52, 72},
  {cont__401_1, NULL, 1514, 1514, 33, 72},
  {cont__401_2, NULL, 1514, 1514, 26, 73},
  {cont__401_3, NULL, 1514, 1514, 1, 73},
  {cont__401_5, NULL, 1519, 1519, 31, 77},
  {cont__402_1, NULL, 1519, 1519, 12, 77},
  {cont__402_2, NULL, 1519, 1519, 5, 78},
  {cont__402_3, NULL, 1516, 1519, 1, 79},
  {cont__402_5, NULL, 1521, 1521, 52, 72},
  {cont__403_1, NULL, 1521, 1521, 33, 72},
  {cont__403_2, NULL, 1521, 1521, 26, 73},
  {cont__403_3, NULL, 1521, 1521, 1, 73},
  {cont__403_5, NULL, 1529, 1529, 32, 71},
  {cont__404_5, NULL, 1529, 1529, 9, 72},
  {cont__404_6, NULL, 1527, 1529, 7, 71},
  {cont__404_7, NULL, 1526, 1529, 5, 72},
  {cont__404_8, NULL, 1523, 1529, 1, 75},
  {cont__404_10, NULL, 1532, 1532, 37, 77},
  {cont__405_1, NULL, 1532, 1532, 18, 77},
  {cont__405_2, NULL, 1532, 1532, 11, 78},
  {cont__405_3, NULL, 1531, 1532, 1, 78},
  {cont__405_5, NULL, 1543, 1543, 5, 42},
  {cont__406_2, NULL, 1534, 1543, 1, 43},
  {cont__406_3, NULL, 1545, 1545, 35, 45},
  {cont__407_1, NULL, 1545, 1545, 1, 45},
  {cont__407_2, NULL, 1546, 1546, 1, 45},
  {cont__408_1, NULL, 1547, 1547, 1, 32},
  {cont__409_2, NULL, 1548, 1548, 22, 44},
  {cont__410_1, NULL, 1548, 1548, 1, 45},
  {cont__410_2, NULL, 1553, 1553, 28, 51},
  {cont__411_1, NULL, 1553, 1553, 28, 66},
  {cont__411_2, NULL, 1553, 1553, 23, 67},
  {cont__411_3, NULL, 1553, 1553, 5, 68},
  {cont__411_4, NULL, 1550, 1553, 1, 69},
  {cont__411_5, NULL, 1558, 1558, 5, 20},
  {cont__412_1, NULL, 1559, 1559, 5, 25},
  {cont__412_2, NULL, 1560, 1560, 31, 46},
  {cont__412_3, NULL, 1560, 1560, 22, 47},
  {cont__412_4, NULL, 1560, 1560, 9, 47},
  {cont__412_5, NULL, 1560, 1560, 5, 55},
  {cont__412_6, NULL, 1561, 1561, 5, 26},
  {cont__412_7, NULL, 1562, 1562, 5, 19},
  {cont__412_8, NULL, 1563, 1563, 5, 15},
  {cont__412_9, NULL, 1555, 1563, 1, 16},
  {cont__412_10, NULL, 1565, 1565, 41, 60},
  {cont__413_1, NULL, 1565, 1565, 34, 61},
  {cont__413_2, NULL, 1565, 1565, 1, 61},
  {cont__413_3, NULL, 1573, 1573, 7, 50},
  {cont__414_2, NULL, 1569, 1573, 5, 49},
  {cont__414_3, NULL, 1574, 1574, 12, 31},
  {cont__414_4, NULL, 1574, 1574, 5, 32},
  {cont__414_5, NULL, 1567, 1574, 1, 33},
  {cont__414_6, NULL, },
  {entry__1_1, NULL, 30, 30, 32, 79},
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
  {cont__2_56, &frame__2_50, 73, 73, 7, 59},
  {entry__2_57, NULL, 75, 77, 14, 80},
  {cont__2_63, &frame__2_57, 75, 77, 7, 80},
  {cont__2_64, &frame__2_57, 78, 78, 7, 19},
  {cont__2_65, &frame__2_57, 79, 79, 16, 25},
  {cont__2_67, &frame__2_57, 79, 79, 7, 29},
  {entry__2_1, NULL, 52, 52, 3, 37},
  {cont__2_2, &frame__2_1, 53, 53, 8, 24},
  {cont__2_3, &frame__2_1, 53, 53, 8, 31},
  {cont__2_4, &frame__2_1, 53, 53, 3, 33},
  {cont__2_5, &frame__2_1, 54, 54, 3, 32},
  {cont__2_6, &frame__2_1, 57, 57, 38, 42},
  {cont__2_7, &frame__2_1, 57, 57, 23, 43},
  {cont__2_8, &frame__2_1, 57, 57, 45, 70},
  {cont__2_9, &frame__2_1, 56, 57, 3, 71},
  {cont__2_10, &frame__2_1, 59, 59, 3, 27},
  {cont__2_11, &frame__2_1, 60, 60, 6, 20},
  {cont__2_12, &frame__2_1, 60, 60, 3, 75},
  {cont__2_16, &frame__2_1, 61, 61, 7, 23},
  {cont__2_17, &frame__2_1, 61, 61, 3, 30},
  {cont__2_18, &frame__2_1, 62, 62, 3, 43},
  {cont__2_27, &frame__2_1, 63, 63, 3, 32},
  {cont__2_28, &frame__2_1, 64, 64, 12, 26},
  {cont__2_29, &frame__2_1, 64, 64, 3, 72},
  {cont__2_33, &frame__2_1, 65, 65, 42, 59},
  {cont__2_34, &frame__2_1, 65, 65, 21, 59},
  {cont__2_35, &frame__2_1, 65, 65, 61, 79},
  {cont__2_37, &frame__2_1, 65, 65, 3, 80},
  {cont__2_38, &frame__2_1, 66, 69, 3, 13},
  {cont__2_46, &frame__2_1, 70, 70, 18, 23},
  {cont__2_47, &frame__2_1, 70, 70, 3, 23},
  {cont__2_48, &frame__2_1, 70, 70, 17, 23},
  {cont__2_49, &frame__2_1, 71, 79, 3, 30},
  {entry__3_1, NULL, 82, 82, 17, 32},
  {cont__3_2, &frame__3_1, 82, 82, 34, 56},
  {cont__3_3, &frame__3_1, 82, 82, 3, 70},
  {entry__4_1, NULL, 85, 85, 3, 50},
  {cont__4_3, &frame__4_1, 86, 86, 3, 8},
  {entry__5_1, NULL, 89, 89, 23, 38},
  {cont__5_2, &frame__5_1, 89, 89, 40, 62},
  {cont__5_3, &frame__5_1, 89, 89, 3, 66},
  {entry__6_1, NULL, 92, 92, 40, 56},
  {cont__6_2, &frame__6_1, 92, 92, 3, 60},
  {entry__8_1, NULL, 97, 97, 21, 36},
  {cont__8_2, &frame__8_1, 97, 97, 3, 36},
  {entry__9_1, NULL, 99, 99, 26, 68},
  {entry__11_4, NULL, 109, 109, 34, 55},
  {cont__11_5, &frame__11_4, 109, 109, 34, 55},
  {entry__11_8, NULL, 113, 113, 11, 46},
  {entry__11_10, NULL, 115, 115, 11, 45},
  {entry__11_12, NULL, 117, 117, 11, 46},
  {entry__11_14, NULL, 119, 120, 29, 42},
  {cont__11_17, &frame__11_14, 119, 120, 11, 42},
  {entry__11_7, NULL, 110, 120, 7, 44},
  {entry__11_18, NULL, 122, 122, 7, 42},
  {entry__11_1, NULL, 107, 107, 3, 33},
  {cont__11_2, &frame__11_1, 109, 109, 5, 29},
  {cont__11_3, &frame__11_1, 109, 109, 5, 55},
  {cont__11_6, &frame__11_1, 108, 122, 3, 43},
  {entry__12_1, NULL, 125, 125, 3, 61},
  {entry__14_1, NULL, 134, 134, 12, 27},
  {cont__14_2, &frame__14_1, 134, 134, 3, 27},
  {cont__14_3, &frame__14_1, 135, 135, 3, 6},
  {entry__15_1, NULL, 137, 137, 19, 54},
  {entry__17_1, NULL, 146, 146, 3, 23},
  {cont__17_3, &frame__17_1, 147, 147, 17, 48},
  {cont__17_4, &frame__17_1, 147, 147, 3, 48},
  {cont__17_5, &frame__17_1, 148, 148, 3, 23},
  {cont__17_7, &frame__17_1, 149, 149, 3, 6},
  {entry__18_4, NULL, 162, 162, 42, 56},
  {cont__18_5, &frame__18_4, 162, 162, 35, 56},
  {cont__18_6, &frame__18_4, 162, 162, 56, 56},
  {entry__18_10, NULL, 163, 163, 44, 60},
  {cont__18_11, &frame__18_10, 163, 163, 37, 60},
  {cont__18_12, &frame__18_10, 163, 163, 60, 60},
  {entry__18_18, NULL, 165, 165, 51, 66},
  {cont__18_19, &frame__18_18, 165, 165, 66, 66},
  {entry__18_16, NULL, 165, 165, 18, 35},
  {cont__18_17, &frame__18_16, 165, 165, 5, 66},
  {cont__18_20, &frame__18_16, 165, 165, 66, 66},
  {entry__18_26, NULL, 167, 167, 51, 66},
  {cont__18_27, &frame__18_26, 167, 167, 66, 66},
  {entry__18_24, NULL, 167, 167, 18, 35},
  {cont__18_25, &frame__18_24, 167, 167, 5, 66},
  {cont__18_28, &frame__18_24, 167, 167, 66, 66},
  {entry__18_34, NULL, 169, 169, 56, 70},
  {cont__18_35, &frame__18_34, 169, 169, 70, 70},
  {entry__18_32, NULL, 169, 169, 18, 41},
  {cont__18_33, &frame__18_32, 169, 169, 5, 70},
  {cont__18_36, &frame__18_32, 169, 169, 70, 70},
  {entry__18_42, NULL, 171, 171, 49, 63},
  {cont__18_43, &frame__18_42, 171, 171, 63, 63},
  {entry__18_40, NULL, 171, 171, 18, 34},
  {cont__18_41, &frame__18_40, 171, 171, 5, 63},
  {cont__18_44, &frame__18_40, 171, 171, 63, 63},
  {entry__18_48, NULL, 172, 172, 41, 54},
  {cont__18_49, &frame__18_48, 172, 172, 34, 54},
  {cont__18_50, &frame__18_48, 172, 172, 54, 54},
  {entry__18_54, NULL, 173, 173, 45, 62},
  {cont__18_55, &frame__18_54, 173, 173, 38, 62},
  {cont__18_56, &frame__18_54, 173, 173, 62, 62},
  {entry__18_1, NULL, 162, 162, 6, 21},
  {cont__18_2, &frame__18_1, 162, 162, 6, 32},
  {cont__18_3, &frame__18_1, 162, 162, 3, 56},
  {cont__18_7, &frame__18_1, 163, 163, 6, 23},
  {cont__18_8, &frame__18_1, 163, 163, 6, 34},
  {cont__18_9, &frame__18_1, 163, 163, 3, 60},
  {cont__18_13, &frame__18_1, 164, 164, 6, 24},
  {cont__18_14, &frame__18_1, 164, 164, 6, 35},
  {cont__18_15, &frame__18_1, 164, 165, 3, 66},
  {cont__18_21, &frame__18_1, 166, 166, 6, 24},
  {cont__18_22, &frame__18_1, 166, 166, 6, 35},
  {cont__18_23, &frame__18_1, 166, 167, 3, 66},
  {cont__18_29, &frame__18_1, 168, 168, 6, 30},
  {cont__18_30, &frame__18_1, 168, 168, 6, 41},
  {cont__18_31, &frame__18_1, 168, 169, 3, 70},
  {cont__18_37, &frame__18_1, 170, 170, 6, 23},
  {cont__18_38, &frame__18_1, 170, 170, 6, 34},
  {cont__18_39, &frame__18_1, 170, 171, 3, 63},
  {cont__18_45, &frame__18_1, 172, 172, 6, 20},
  {cont__18_46, &frame__18_1, 172, 172, 6, 31},
  {cont__18_47, &frame__18_1, 172, 172, 3, 54},
  {cont__18_51, &frame__18_1, 173, 173, 6, 24},
  {cont__18_52, &frame__18_1, 173, 173, 6, 35},
  {cont__18_53, &frame__18_1, 173, 173, 3, 62},
  {cont__18_57, &frame__18_1, },
  {entry__20_1, NULL, 178, 178, 10, 37},
  {cont__20_2, &frame__20_1, 178, 178, 3, 37},
  {cont__20_4, &frame__20_1, 179, 179, 3, 6},
  {entry__22_1, NULL, 184, 184, 12, 39},
  {cont__22_2, &frame__22_1, 184, 184, 3, 39},
  {cont__22_4, &frame__22_1, 185, 185, 3, 6},
  {entry__24_1, NULL, 190, 190, 12, 39},
  {cont__24_2, &frame__24_1, 190, 190, 3, 39},
  {cont__24_4, &frame__24_1, 191, 191, 3, 6},
  {entry__28_3, NULL, 224, 224, 25, 44},
  {cont__28_4, &frame__28_3, 224, 224, 22, 44},
  {entry__28_5, NULL, 224, 224, 47, 65},
  {entry__28_1, NULL, 224, 224, 6, 19},
  {cont__28_2, &frame__28_1, 224, 224, 3, 65},
  {entry__29_1, NULL, 226, 226, 40, 47},
  {cont__29_2, &frame__29_1, 226, 226, 37, 47},
  {entry__30_1, NULL, 228, 228, 34, 42},
  {cont__30_2, &frame__30_1, 228, 228, 34, 42},
  {cont__30_3, &frame__30_1, 228, 228, 31, 42},
  {entry__31_1, NULL, 231, 231, 19, 64},
  {cont__31_2, &frame__31_1, 231, 231, 6, 65},
  {cont__31_3, &frame__31_1, 231, 231, 3, 65},
  {entry__32_1, NULL, 233, 233, 58, 78},
  {cont__32_2, &frame__32_1, 233, 233, 53, 79},
  {cont__32_3, &frame__32_1, 233, 233, 41, 79},
  {cont__32_4, &frame__32_1, 233, 233, 38, 79},
  {entry__35_1, NULL, 243, 243, 18, 36},
  {cont__35_2, &frame__35_1, 243, 243, 3, 43},
  {cont__35_3, &frame__35_1, 243, 243, 43, 43},
  {entry__36_1, NULL, 245, 245, 23, 65},
  {entry__42_3, NULL, 263, 263, 36, 60},
  {cont__42_5, &frame__42_3, 263, 263, 23, 61},
  {cont__42_6, &frame__42_3, 263, 263, 8, 62},
  {cont__42_7, &frame__42_3, 263, 263, 5, 62},
  {entry__42_8, NULL, 264, 264, 23, 56},
  {cont__42_9, &frame__42_8, 264, 264, 8, 57},
  {cont__42_10, &frame__42_8, 264, 264, 5, 57},
  {entry__42_1, NULL, 262, 262, 5, 26},
  {cont__42_2, &frame__42_1, 261, 264, 3, 57},
  {entry__45_1, NULL, 283, 283, 30, 50},
  {cont__45_2, &frame__45_1, 283, 283, 6, 51},
  {cont__45_3, &frame__45_1, 283, 283, 3, 51},
  {entry__46_1, NULL, 286, 286, 37, 77},
  {cont__46_2, &frame__46_1, 286, 286, 6, 78},
  {cont__46_3, &frame__46_1, 286, 286, 3, 78},
  {entry__207_7, NULL, 1583, 1583, 32, 75},
  {entry__207_1, NULL, 1581, 1581, 3, 36},
  {cont__207_2, &frame__207_1, 1582, 1582, 3, 38},
  {cont__207_3, &frame__207_1, 1583, 1583, 13, 29},
  {cont__207_4, &frame__207_1, 1583, 1583, 6, 29},
  {cont__207_5, &frame__207_1, 1583, 1583, 6, 29},
  {cont__207_6, &frame__207_1, 1583, 1583, 3, 75},
  {cont__207_9, &frame__207_1, 1584, 1584, 3, 8},
  {entry__208_9, NULL, 1593, 1593, 9, 67},
  {entry__208_5, NULL, 1592, 1592, 17, 33},
  {cont__208_6, &frame__208_5, 1592, 1592, 10, 33},
  {cont__208_7, &frame__208_5, 1592, 1592, 10, 33},
  {cont__208_8, &frame__208_5, 1592, 1593, 7, 67},
  {entry__208_11, NULL, 1595, 1595, 7, 57},
  {cont__208_13, &frame__208_11, 1596, 1596, 7, 26},
  {cont__208_14, &frame__208_11, 1597, 1597, 7, 25},
  {cont__208_16, &frame__208_11, 1598, 1598, 7, 12},
  {entry__208_1, NULL, 1588, 1588, 3, 36},
  {cont__208_2, &frame__208_1, 1589, 1589, 3, 33},
  {cont__208_3, &frame__208_1, 1591, 1591, 5, 18},
  {cont__208_4, &frame__208_1, 1590, 1598, 3, 13},
  {cont__208_17, &frame__208_1, 1599, 1599, 3, 8},
  {entry__245_2, NULL, 251, 252, 9, 23},
  {entry__245_1, NULL, 250, 252, 7, 24},
  {cont__245_4, &frame__245_1, 253, 253, 7, 13},
  {entry__251_1, NULL, 274, 274, 7, 28},
  {cont__251_2, &frame__251_1, 275, 275, 47, 47},
  {entry__252_1, NULL, 280, 280, 33, 33},
  {entry__259_1, NULL, 300, 300, 7, 48},
  {cont__259_2, &frame__259_1, 301, 301, 40, 40},
  {entry__260_1, NULL, 310, 310, 32, 48},
  {cont__260_2, &frame__260_1, 310, 310, 7, 50},
  {cont__260_3, &frame__260_1, 311, 311, 40, 40},
  {entry__261_1, NULL, 320, 320, 32, 48},
  {cont__261_2, &frame__261_1, 320, 320, 7, 50},
  {cont__261_3, &frame__261_1, 321, 321, 40, 40},
  {entry__262_1, NULL, 330, 330, 7, 45},
  {cont__262_2, &frame__262_1, 330, 330, 45, 45},
  {entry__263_3, NULL, 342, 342, 13, 43},
  {cont__263_4, &frame__263_3, 342, 342, 43, 43},
  {entry__264_6, NULL, 358, 358, 15, 76},
  {entry__264_4, NULL, 357, 357, 16, 31},
  {cont__264_5, &frame__264_4, 357, 358, 13, 76},
  {cont__264_8, &frame__264_4, 359, 359, 13, 43},
  {cont__264_9, &frame__264_4, 359, 359, 43, 43},
  {entry__267_7, NULL, 389, 390, 29, 55},
  {cont__267_10, &frame__267_7, 389, 390, 11, 55},
  {entry__267_3, NULL, 387, 387, 9, 41},
  {cont__267_4, &frame__267_3, 388, 388, 12, 37},
  {cont__267_5, &frame__267_3, 388, 388, 12, 48},
  {cont__267_6, &frame__267_3, 388, 390, 9, 56},
  {cont__267_11, &frame__267_3, 391, 391, 9, 35},
  {cont__267_12, &frame__267_3, 391, 391, 40, 40},
  {entry__268_5, NULL, 404, 404, 13, 54},
  {cont__268_6, &frame__268_5, 404, 404, 54, 54},
  {entry__268_14, NULL, 411, 412, 29, 58},
  {cont__268_17, &frame__268_14, 411, 412, 11, 58},
  {entry__268_25, NULL, 417, 418, 31, 62},
  {cont__268_28, &frame__268_25, 417, 418, 13, 62},
  {entry__268_22, NULL, 416, 416, 14, 38},
  {cont__268_23, &frame__268_22, 416, 416, 14, 49},
  {cont__268_24, &frame__268_22, 416, 418, 11, 63},
  {cont__268_29, &frame__268_22, 419, 419, 11, 36},
  {cont__268_30, &frame__268_22, 419, 419, 46, 46},
  {entry__268_11, NULL, 409, 409, 9, 37},
  {cont__268_12, &frame__268_11, 410, 410, 12, 40},
  {cont__268_13, &frame__268_11, 410, 412, 9, 59},
  {cont__268_18, &frame__268_11, 413, 413, 9, 38},
  {cont__268_19, &frame__268_11, 414, 414, 9, 39},
  {cont__268_20, &frame__268_11, 415, 415, 12, 27},
  {cont__268_21, &frame__268_11, 415, 419, 9, 46},
  {entry__269_6, NULL, 432, 433, 29, 55},
  {cont__269_9, &frame__269_6, 432, 433, 11, 55},
  {entry__269_3, NULL, 430, 430, 9, 37},
  {cont__269_4, &frame__269_3, 431, 431, 12, 37},
  {cont__269_5, &frame__269_3, 431, 433, 9, 56},
  {cont__269_10, &frame__269_3, 434, 434, 9, 35},
  {cont__269_11, &frame__269_3, 434, 434, 40, 40},
  {entry__272_6, NULL, 450, 451, 29, 53},
  {cont__272_9, &frame__272_6, 450, 451, 11, 53},
  {entry__272_3, NULL, 448, 448, 9, 41},
  {cont__272_4, &frame__272_3, 449, 449, 12, 35},
  {cont__272_5, &frame__272_3, 449, 451, 9, 54},
  {cont__272_10, &frame__272_3, 452, 452, 9, 33},
  {cont__272_11, &frame__272_3, 452, 452, 38, 38},
  {entry__273_6, NULL, 465, 466, 29, 54},
  {cont__273_9, &frame__273_6, 465, 466, 11, 54},
  {entry__273_3, NULL, 463, 463, 9, 41},
  {cont__273_4, &frame__273_3, 464, 464, 12, 37},
  {cont__273_5, &frame__273_3, 464, 466, 9, 55},
  {cont__273_10, &frame__273_3, 467, 467, 9, 35},
  {cont__273_11, &frame__273_3, 467, 467, 40, 40},
  {entry__276_6, NULL, 483, 484, 29, 63},
  {cont__276_9, &frame__276_6, 483, 484, 11, 63},
  {entry__276_3, NULL, 481, 481, 9, 41},
  {cont__276_4, &frame__276_3, 482, 482, 12, 35},
  {cont__276_5, &frame__276_3, 482, 484, 9, 64},
  {cont__276_10, &frame__276_3, 485, 485, 9, 33},
  {cont__276_11, &frame__276_3, 485, 485, 38, 38},
  {entry__283_3, NULL, 512, 512, 40, 65},
  {cont__283_4, &frame__283_3, 512, 512, 40, 65},
  {entry__283_10, NULL, 516, 516, 55, 55},
  {entry__283_11, NULL, 518, 518, 42, 42},
  {cont__283_12, &frame__283_11, 518, 518, 23, 39},
  {cont__283_13, &frame__283_11, 518, 518, 23, 43},
  {cont__283_14, &frame__283_11, 518, 518, 23, 66},
  {cont__283_15, &frame__283_11, 518, 518, 15, 79},
  {cont__283_16, &frame__283_11, 518, 518, 23, 39},
  {cont__283_17, &frame__283_11, 518, 518, 42, 42},
  {cont__283_18, &frame__283_11, 518, 518, 23, 43},
  {cont__283_19, &frame__283_11, 518, 518, 22, 43},
  {cont__283_20, &frame__283_11, 518, 518, 79, 79},
  {entry__283_6, NULL, 513, 513, 11, 45},
  {cont__283_7, &frame__283_6, 515, 515, 13, 30},
  {cont__283_8, &frame__283_6, 515, 515, 13, 39},
  {cont__283_9, &frame__283_6, 514, 518, 11, 80},
  {cont__283_21, &frame__283_6, 519, 519, 42, 42},
  {entry__283_1, NULL, 512, 512, 16, 35},
  {cont__283_2, &frame__283_1, 512, 512, 16, 65},
  {cont__283_5, &frame__283_1, 512, 519, 9, 42},
  {cont__283_22, &frame__283_1, },
  {entry__284_4, NULL, 531, 531, 11, 60},
  {cont__284_5, &frame__284_4, 532, 532, 42, 42},
  {entry__284_1, NULL, 530, 530, 16, 24},
  {cont__284_2, &frame__284_1, 530, 530, 16, 35},
  {cont__284_3, &frame__284_1, 530, 532, 9, 42},
  {cont__284_6, &frame__284_1, },
  {entry__286_7, NULL, 548, 548, 18, 34},
  {cont__286_8, &frame__286_7, 548, 548, 18, 37},
  {cont__286_9, &frame__286_7, 548, 548, 18, 53},
  {cont__286_10, &frame__286_7, 549, 549, 40, 40},
  {cont__286_11, &frame__286_7, 549, 549, 17, 37},
  {cont__286_12, &frame__286_7, 549, 549, 17, 41},
  {cont__286_13, &frame__286_7, 547, 549, 15, 41},
  {cont__286_14, &frame__286_7, 548, 548, 18, 34},
  {cont__286_15, &frame__286_7, 548, 548, 18, 37},
  {cont__286_16, &frame__286_7, 548, 548, 17, 37},
  {cont__286_17, &frame__286_7, 550, 550, 22, 41},
  {cont__286_18, &frame__286_7, 550, 550, 46, 46},
  {cont__286_19, &frame__286_7, 550, 550, 15, 46},
  {cont__286_20, &frame__286_7, 550, 550, 46, 46},
  {entry__286_3, NULL, 545, 545, 26, 43},
  {cont__286_4, &frame__286_3, 545, 545, 13, 44},
  {cont__286_5, &frame__286_3, 546, 546, 16, 20},
  {cont__286_6, &frame__286_3, 546, 550, 13, 46},
  {entry__286_1, NULL, 544, 544, 18, 37},
  {cont__286_2, &frame__286_1, 544, 550, 11, 47},
  {cont__286_21, &frame__286_1, },
  {entry__287_7, NULL, 561, 561, 19, 35},
  {cont__287_8, &frame__287_7, 561, 561, 19, 38},
  {cont__287_9, &frame__287_7, 561, 561, 19, 54},
  {cont__287_10, &frame__287_7, 561, 561, 79, 79},
  {cont__287_11, &frame__287_7, 561, 561, 56, 76},
  {cont__287_12, &frame__287_7, 561, 561, 56, 80},
  {cont__287_13, &frame__287_7, 561, 561, 13, 80},
  {cont__287_14, &frame__287_7, 561, 561, 19, 35},
  {cont__287_15, &frame__287_7, 561, 561, 19, 38},
  {cont__287_16, &frame__287_7, 561, 561, 18, 38},
  {cont__287_17, &frame__287_7, 562, 562, 20, 39},
  {cont__287_18, &frame__287_7, 562, 562, 44, 44},
  {cont__287_19, &frame__287_7, 562, 562, 13, 44},
  {cont__287_20, &frame__287_7, 562, 562, 44, 44},
  {entry__287_3, NULL, 559, 559, 24, 41},
  {cont__287_4, &frame__287_3, 559, 559, 11, 42},
  {cont__287_5, &frame__287_3, 560, 560, 14, 18},
  {cont__287_6, &frame__287_3, 560, 562, 11, 44},
  {entry__287_1, NULL, 558, 558, 16, 35},
  {cont__287_2, &frame__287_1, 558, 562, 9, 45},
  {cont__287_21, &frame__287_1, },
  {entry__290_1, NULL, 578, 578, 26, 42},
  {cont__290_2, &frame__290_1, 579, 579, 33, 56},
  {cont__290_3, &frame__290_1, 575, 579, 9, 57},
  {entry__291_1, NULL, 589, 589, 25, 34},
  {cont__291_2, &frame__291_1, 591, 591, 24, 40},
  {cont__291_3, &frame__291_1, 592, 592, 31, 54},
  {cont__291_4, &frame__291_1, 592, 592, 56, 56},
  {entry__306_2, NULL, 642, 642, 30, 49},
  {cont__306_3, &frame__306_2, 642, 642, 9, 52},
  {cont__306_4, &frame__306_2, 642, 642, 52, 52},
  {entry__307_1, NULL, 649, 649, 33, 33},
  {entry__308_6, NULL, 662, 662, 32, 73},
  {entry__308_2, NULL, 661, 661, 30, 49},
  {cont__308_3, &frame__308_2, 661, 661, 9, 50},
  {cont__308_4, &frame__308_2, 662, 662, 16, 29},
  {cont__308_5, &frame__308_2, 662, 662, 9, 73},
  {cont__308_8, &frame__308_2, 663, 663, 32, 32},
  {entry__309_13, NULL, 677, 677, 40, 59},
  {cont__309_14, &frame__309_13, 677, 677, 40, 70},
  {cont__309_15, &frame__309_13, 677, 677, 9, 71},
  {cont__309_16, &frame__309_13, 677, 677, 71, 71},
  {entry__313_1, NULL, 704, 704, 17, 34},
  {cont__313_2, &frame__313_1, 704, 704, 36, 55},
  {cont__313_3, &frame__313_1, 704, 704, 11, 55},
  {cont__313_4, &frame__313_1, 704, 704, 55, 55},
  {entry__314_5, NULL, 712, 712, 17, 33},
  {cont__314_6, &frame__314_5, 712, 712, 11, 63},
  {cont__314_7, &frame__314_5, 712, 712, 63, 63},
  {entry__314_1, NULL, 711, 711, 12, 30},
  {cont__314_2, &frame__314_1, 711, 711, 12, 36},
  {cont__314_3, &frame__314_1, 711, 711, 12, 36},
  {cont__314_4, &frame__314_1, 711, 712, 9, 63},
  {cont__314_8, &frame__314_1, 713, 713, 30, 30},
  {entry__315_9, NULL, 722, 722, 17, 33},
  {cont__315_10, &frame__315_9, 722, 722, 11, 63},
  {cont__315_11, &frame__315_9, 722, 722, 63, 63},
  {entry__315_5, NULL, 721, 721, 12, 30},
  {cont__315_6, &frame__315_5, 721, 721, 12, 36},
  {cont__315_7, &frame__315_5, 721, 721, 12, 36},
  {cont__315_8, &frame__315_5, 721, 722, 9, 63},
  {cont__315_12, &frame__315_5, 725, 725, 25, 48},
  {cont__315_14, &frame__315_5, 726, 726, 27, 44},
  {cont__315_15, &frame__315_5, 728, 728, 26, 42},
  {cont__315_16, &frame__315_5, 729, 729, 33, 56},
  {cont__315_17, &frame__315_5, 730, 730, 30, 50},
  {cont__315_18, &frame__315_5, 730, 730, 52, 52},
  {entry__315_1, NULL, 720, 720, 20, 37},
  {cont__315_2, &frame__315_1, 720, 720, 10, 38},
  {cont__315_3, &frame__315_1, 720, 720, 10, 42},
  {cont__315_4, &frame__315_1, 720, 730, 7, 52},
  {cont__315_19, &frame__315_1, },
  {entry__318_1, NULL, 755, 755, 15, 32},
  {cont__318_2, &frame__318_1, 755, 755, 34, 60},
  {cont__318_3, &frame__318_1, 755, 755, 7, 60},
  {cont__318_4, &frame__318_1, 755, 755, 60, 60},
  {entry__322_1, NULL, 785, 785, 25, 56},
  {cont__322_3, &frame__322_1, 786, 786, 37, 58},
  {cont__322_5, &frame__322_1, 786, 786, 27, 59},
  {cont__322_6, &frame__322_1, 787, 787, 26, 42},
  {cont__322_7, &frame__322_1, 788, 788, 33, 56},
  {cont__322_8, &frame__322_1, 788, 788, 33, 58},
  {cont__322_9, &frame__322_1, 783, 788, 9, 59},
  {entry__323_1, NULL, 801, 801, 27, 36},
  {cont__323_3, &frame__323_1, 802, 802, 26, 42},
  {cont__323_4, &frame__323_1, 803, 803, 33, 56},
  {cont__323_5, &frame__323_1, 798, 803, 9, 57},
  {entry__330_9, NULL, 856, 856, 13, 51},
  {cont__330_10, &frame__330_9, 856, 856, 13, 51},
  {entry__330_12, NULL, 858, 858, 58, 58},
  {entry__330_2, NULL, 851, 851, 61, 61},
  {cont__330_3, &frame__330_2, 851, 851, 41, 58},
  {cont__330_4, &frame__330_2, 851, 851, 41, 62},
  {cont__330_5, &frame__330_2, 851, 851, 9, 63},
  {cont__330_6, &frame__330_2, 852, 852, 9, 53},
  {cont__330_7, &frame__330_2, 855, 855, 13, 42},
  {cont__330_8, &frame__330_2, 854, 856, 11, 50},
  {cont__330_11, &frame__330_2, 853, 858, 9, 59},
  {cont__330_13, &frame__330_2, },
  {entry__331_6, NULL, 868, 868, 11, 28},
  {cont__331_7, &frame__331_6, 868, 868, 28, 28},
  {entry__331_11, NULL, 876, 876, 47, 71},
  {cont__331_12, &frame__331_11, 876, 876, 44, 71},
  {entry__331_13, NULL, 876, 876, 74, 77},
  {entry__331_22, NULL, 883, 883, 41, 66},
  {cont__331_23, &frame__331_22, 883, 883, 41, 66},
  {entry__331_27, NULL, 888, 888, 21, 57},
  {entry__331_28, NULL, 889, 889, 21, 31},
  {entry__331_16, NULL, 880, 880, 17, 46},
  {cont__331_17, &frame__331_16, 881, 881, 17, 42},
  {cont__331_18, &frame__331_16, 882, 882, 20, 35},
  {cont__331_19, &frame__331_16, 882, 882, 17, 41},
  {cont__331_20, &frame__331_16, 883, 883, 20, 36},
  {cont__331_21, &frame__331_16, 883, 883, 20, 66},
  {cont__331_24, &frame__331_16, 883, 883, 17, 72},
  {cont__331_25, &frame__331_16, 887, 887, 21, 40},
  {cont__331_26, &frame__331_16, 885, 889, 17, 32},
  {cont__331_29, &frame__331_16, 891, 891, 17, 41},
  {cont__331_30, &frame__331_16, 895, 895, 35, 50},
  {cont__331_31, &frame__331_16, 897, 897, 40, 62},
  {cont__331_32, &frame__331_16, 898, 898, 34, 50},
  {cont__331_33, &frame__331_16, 899, 899, 41, 64},
  {cont__331_34, &frame__331_16, 900, 900, 38, 59},
  {cont__331_35, &frame__331_16, 901, 901, 17, 43},
  {cont__331_36, &frame__331_16, 902, 902, 20, 44},
  {cont__331_37, &frame__331_16, 902, 902, 20, 49},
  {cont__331_38, &frame__331_16, 902, 902, 17, 55},
  {entry__331_15, NULL, 879, 902, 15, 55},
  {cont__331_39, &frame__331_15, 902, 902, 55, 55},
  {entry__331_9, NULL, 876, 876, 18, 41},
  {cont__331_10, &frame__331_9, 875, 876, 13, 78},
  {cont__331_14, &frame__331_9, 878, 902, 13, 56},
  {cont__331_40, &frame__331_9, 903, 903, 13, 37},
  {cont__331_41, &frame__331_9, 904, 904, 13, 46},
  {cont__331_42, &frame__331_9, 904, 904, 46, 46},
  {entry__331_51, NULL, 907, 907, 52, 63},
  {cont__331_52, &frame__331_51, 907, 907, 49, 63},
  {entry__331_53, NULL, 907, 907, 66, 77},
  {entry__331_48, NULL, 907, 907, 26, 37},
  {cont__331_49, &frame__331_48, 907, 907, 42, 46},
  {cont__331_50, &frame__331_48, 907, 907, 39, 78},
  {cont__331_54, &frame__331_48, 907, 907, 13, 78},
  {entry__331_8, NULL, 870, 870, 11, 39},
  {cont__331_43, &frame__331_8, 871, 871, 32, 43},
  {cont__331_44, &frame__331_8, 871, 871, 11, 44},
  {cont__331_45, &frame__331_8, 872, 872, 33, 44},
  {cont__331_46, &frame__331_8, 872, 872, 11, 45},
  {cont__331_47, &frame__331_8, 906, 907, 11, 78},
  {cont__331_55, &frame__331_8, 908, 908, 11, 35},
  {cont__331_56, &frame__331_8, 908, 908, 35, 35},
  {entry__331_59, NULL, 910, 910, 41, 60},
  {cont__331_60, &frame__331_59, 910, 910, 36, 66},
  {cont__331_61, &frame__331_59, 910, 910, 67, 67},
  {entry__331_1, NULL, 863, 863, 7, 29},
  {cont__331_2, &frame__331_1, 864, 864, 7, 35},
  {cont__331_3, &frame__331_1, 865, 865, 7, 29},
  {cont__331_4, &frame__331_1, 867, 867, 9, 14},
  {cont__331_5, &frame__331_1, 866, 908, 7, 36},
  {cont__331_57, &frame__331_1, 909, 909, 10, 26},
  {cont__331_58, &frame__331_1, 909, 910, 7, 67},
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
  {cont__359_12, &frame__359_6, 1138, 1138, 29, 46},
  {cont__359_13, &frame__359_6, 1139, 1139, 36, 60},
  {cont__359_14, &frame__359_6, 1140, 1140, 34, 59},
  {cont__359_15, &frame__359_6, 1141, 1141, 32, 55},
  {cont__359_16, &frame__359_6, 1142, 1142, 28, 47},
  {cont__359_17, &frame__359_6, 1143, 1143, 35, 61},
  {cont__359_18, &frame__359_6, 1144, 1144, 32, 52},
  {cont__359_19, &frame__359_6, 1132, 1144, 9, 54},
  {cont__359_20, &frame__359_6, 1146, 1146, 9, 54},
  {entry__361_1, NULL, 1156, 1156, 11, 62},
  {cont__361_2, &frame__361_1, 1157, 1157, 42, 42},
  {entry__361_8, NULL, 1163, 1163, 21, 37},
  {cont__361_9, &frame__361_8, 1163, 1163, 21, 40},
  {cont__361_10, &frame__361_8, 1163, 1163, 21, 56},
  {cont__361_11, &frame__361_8, 1163, 1163, 58, 78},
  {cont__361_12, &frame__361_8, 1163, 1163, 13, 78},
  {cont__361_13, &frame__361_8, 1163, 1163, 21, 37},
  {cont__361_14, &frame__361_8, 1163, 1163, 21, 40},
  {cont__361_15, &frame__361_8, 1163, 1163, 20, 40},
  {cont__361_16, &frame__361_8, 1164, 1164, 44, 44},
  {entry__361_4, NULL, 1161, 1161, 24, 41},
  {cont__361_5, &frame__361_4, 1161, 1161, 11, 42},
  {cont__361_6, &frame__361_4, 1162, 1162, 14, 18},
  {cont__361_7, &frame__361_4, 1162, 1164, 11, 44},
  {cont__361_17, &frame__361_4, 1165, 1165, 11, 62},
  {cont__361_18, &frame__361_4, 1166, 1166, 50, 50},
  {entry__364_3, NULL, 1186, 1186, 26, 42},
  {cont__364_4, &frame__364_3, 1187, 1187, 33, 56},
  {cont__364_5, &frame__364_3, 1183, 1187, 9, 57},
  {entry__364_12, NULL, 1201, 1201, 11, 72},
  {entry__364_23, NULL, 1210, 1210, 35, 54},
  {cont__364_24, &frame__364_23, 1211, 1211, 20, 39},
  {cont__364_25, &frame__364_23, 1211, 1211, 20, 44},
  {cont__364_26, &frame__364_23, 1211, 1211, 17, 51},
  {cont__364_27, &frame__364_23, 1212, 1212, 51, 51},
  {cont__364_28, &frame__364_23, 1212, 1212, 32, 52},
  {cont__364_29, &frame__364_23, 1212, 1212, 17, 58},
  {cont__364_30, &frame__364_23, 1212, 1212, 58, 58},
  {entry__364_22, NULL, 1206, 1212, 15, 58},
  {entry__364_32, NULL, 1218, 1218, 52, 52},
  {cont__364_33, &frame__364_32, 1218, 1218, 55, 55},
  {cont__364_34, &frame__364_32, 1218, 1218, 35, 56},
  {cont__364_35, &frame__364_32, 1219, 1219, 20, 39},
  {cont__364_36, &frame__364_32, 1219, 1219, 20, 44},
  {cont__364_37, &frame__364_32, 1219, 1219, 17, 51},
  {cont__364_38, &frame__364_32, 1220, 1220, 52, 52},
  {cont__364_39, &frame__364_32, 1220, 1220, 33, 53},
  {cont__364_40, &frame__364_32, 1220, 1220, 17, 59},
  {cont__364_41, &frame__364_32, 1220, 1220, 59, 59},
  {entry__364_31, NULL, 1214, 1220, 15, 59},
  {entry__364_17, NULL, 1203, 1203, 11, 35},
  {cont__364_18, &frame__364_17, 1205, 1205, 24, 39},
  {cont__364_19, &frame__364_17, 1205, 1205, 13, 40},
  {cont__364_20, &frame__364_17, 1205, 1205, 13, 60},
  {cont__364_21, &frame__364_17, 1204, 1220, 11, 61},
  {entry__364_8, NULL, 1199, 1199, 9, 38},
  {cont__364_9, &frame__364_8, 1200, 1200, 12, 31},
  {cont__364_10, &frame__364_8, 1200, 1200, 12, 35},
  {cont__364_11, &frame__364_8, 1200, 1201, 9, 72},
  {cont__364_14, &frame__364_8, 1202, 1202, 12, 31},
  {cont__364_15, &frame__364_8, 1202, 1202, 12, 35},
  {cont__364_16, &frame__364_8, 1202, 1220, 9, 62},
  {cont__364_42, &frame__364_8, 1220, 1220, 62, 62},
  {entry__365_10, NULL, 1243, 1243, 48, 65},
  {cont__365_11, &frame__365_10, 1243, 1243, 70, 70},
  {cont__365_12, &frame__365_10, 1243, 1243, 42, 71},
  {cont__365_13, &frame__365_10, 1244, 1244, 60, 60},
  {cont__365_14, &frame__365_10, 1244, 1244, 40, 57},
  {cont__365_15, &frame__365_10, 1244, 1244, 40, 61},
  {cont__365_16, &frame__365_10, 1244, 1244, 35, 62},
  {cont__365_17, &frame__365_10, 1240, 1244, 17, 63},
  {entry__372_1, NULL, 1312, 1312, 30, 30}
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
static NODE *character__34;
static NODE *number__7;
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
  allocate_initialized_frame_gc(0, 0);
  // 94: $types::syntax_error types::grammar_object
  initialize_maybe_future(var.types__syntax_error, get__types__grammar_object());
  // 104: $types::unexpected_input_error types::grammar_object
  initialize_maybe_future(var.types__unexpected_input_error, get__types__grammar_object());
  // 131: $types::print types::grammar_object
  initialize_maybe_future(var.types__print, get__types__grammar_object());
  // 143: $dump_stream types::grammar_object
  initialize_maybe_future(var._dump_stream, get__types__grammar_object());
  // 175: $dump types::grammar_object
  initialize_maybe_future(var._dump, get__types__grammar_object());
  // 181: $dump3 types::grammar_object
  initialize_maybe_future(var._dump3, get__types__grammar_object());
  // 187: $dump5 types::grammar_object
  initialize_maybe_future(var._dump5, get__types__grammar_object());
  // 202: "*" = 14
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_1;
  arguments->slots[1] = number__14;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_2;
}
static void cont__235_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 203: "/" = 14
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_3;
  arguments->slots[1] = number__14;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_4;
}
static void cont__235_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 204: "+" = 13
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_5;
  arguments->slots[1] = number__13;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_6;
}
static void cont__235_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 205: "-" = 13
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_7;
  arguments->slots[1] = number__13;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_8;
}
static void cont__235_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 206: "<<" = 12
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_9;
  arguments->slots[1] = number__12;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_10;
}
static void cont__235_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 207: ">>" = 12
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_11;
  arguments->slots[1] = number__12;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_12;
}
static void cont__235_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 208: "&" = 11
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_13;
  arguments->slots[1] = number__11;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_14;
}
static void cont__235_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 209: "^" = 10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_15;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_16;
}
static void cont__235_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__8 = arguments->slots[0];
  // 210: "|" = 9
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_17;
  arguments->slots[1] = number__9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_18;
}
static void cont__235_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__9 = arguments->slots[0];
  // 211: "<=" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_19;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_20;
}
static void cont__235_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__10 = arguments->slots[0];
  // 212: "<" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_21;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_22;
}
static void cont__235_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__11 = arguments->slots[0];
  // 213: ">=" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_23;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_24;
}
static void cont__235_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__12 = arguments->slots[0];
  // 214: ">" = 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_25;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_26;
}
static void cont__235_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__13 = arguments->slots[0];
  // 215: "==" = 7
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_27;
  arguments->slots[1] = number__7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_28;
}
static void cont__235_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__14 = arguments->slots[0];
  // 216: "!=" = 7
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_29;
  arguments->slots[1] = number__7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_30;
}
static void cont__235_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__15 = arguments->slots[0];
  // 217: "&&" = 5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_31;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_32;
}
static void cont__235_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__16 = arguments->slots[0];
  // 218: "||" = 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_33;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_34;
}
static void cont__235_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__17 = arguments->slots[0];
  // 219: ".." = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_35;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_36;
}
static void cont__235_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__18 = arguments->slots[0];
  // 220: "," = 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_37;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_38;
}
static void cont__235_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__19 = arguments->slots[0];
  // 221: "=" = 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__235_39;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__235_40;
}
static void cont__235_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__20 = arguments->slots[0];
  // 200: $precedence_table
  // 201:   table
  // 202:     "*" = 14
  // 203:     "/" = 14
  // 204:     "+" = 13
  // 205:     "-" = 13
  // 206:     "<<" = 12
  // 207:     ">>" = 12
  // 208:     "&" = 11
  // 209:     "^" = 10
  // ...
  argument_count = 20;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = temp__3;
  arguments->slots[3] = temp__4;
  arguments->slots[4] = temp__5;
  arguments->slots[5] = temp__6;
  arguments->slots[6] = temp__7;
  arguments->slots[7] = temp__8;
  arguments->slots[8] = temp__9;
  arguments->slots[9] = temp__10;
  arguments->slots[10] = temp__11;
  arguments->slots[11] = temp__12;
  arguments->slots[12] = temp__13;
  arguments->slots[13] = temp__14;
  arguments->slots[14] = temp__15;
  arguments->slots[15] = temp__16;
  arguments->slots[16] = temp__17;
  arguments->slots[17] = temp__18;
  arguments->slots[18] = temp__19;
  arguments->slots[19] = temp__20;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__235_41;
}
static void cont__235_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._precedence_table, arguments->slots[0]);
  // 238: %within_inline_expression false
  initialize_maybe_future(get__within_inline_expression(), get__false());
  // 239: $types::inline types::grammar_object
  initialize_maybe_future(var.types__inline, get__types__grammar_object());
  // 247: $NOT_INLINE
  // 248:   check_node
  // 249:     : (_node stream)
  // 250:       if within_inline_expression:
  // 251:         ParseError stream "
  // 252:           ")" expected@
  // 253:       -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__245_1;
  result_count = 1;
  myself = get__check_node();
  func = myself->type;
  frame->cont = cont__245_5;
}
static void entry__245_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 250: ... :
  // 251:   ParseError stream "
  // 252:     ")" expected@
  frame->slots[2] /* temp__1 */ = create_closure(entry__245_2, 0);
  // 250: if within_inline_expression:
  // 251:   ParseError stream "
  // 252:     ")" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__within_inline_expression();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__245_4;
}
static void entry__245_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 251: ParseError stream "
  // 252:   ")" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__245_3;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__245_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 253: -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__245_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NOT_INLINE, arguments->slots[0]);
  // 255: ... followed_by(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__246_1;
}
static void cont__246_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 255: $NEWLINE followed_by(newline), NOT_INLINE, newline
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__newline();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__246_2;
}
static void cont__246_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEWLINE, arguments->slots[0]);
  // 256: ... followed_by(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
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
  temp__1 = arguments->slots[0];
  // 256: $INDENT followed_by(indent_marker), NOT_INLINE, indent_marker
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__indent_marker();
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
  initialize_future(var._INDENT, arguments->slots[0]);
  // 257: ... followed_by(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
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
  temp__1 = arguments->slots[0];
  // 257: $OUTDENT followed_by(outdent_marker), NOT_INLINE, outdent_marker
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = get__outdent_marker();
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
  initialize_future(var._OUTDENT, arguments->slots[0]);
  // 258: ... followed_by('#')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__35;
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
  temp__1 = arguments->slots[0];
  // 258: $HASHTAG followed_by('#'), NOT_INLINE, '#'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._NOT_INLINE;
  arguments->slots[2] = character__35;
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
  initialize_future(var._HASHTAG, arguments->slots[0]);
  // 266: $ENUMERATE
  // 267:   modify_node
  // 268:     : (&node)
  // 269:       #
  // 270:         On a first look there seem to be too many enumeration numbers used,
  // 271:         but single nested nodes are flattened later on and there is no need
  // 272:         for enumeration numbers to be dense.
  // 273:       
  // 274:       inc &enumeration_count
  // 275:       !node.enumeration_no_of enumeration_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__251_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__251_3;
}
static void entry__251_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 274: inc &enumeration_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__enumeration_count();
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__251_2;
}
static void cont__251_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__enumeration_count(arguments->slots[0]);
  // 275: !node.enumeration_no_of enumeration_count
  frame->slots[1] /* temp__1 */ = get__enumeration_count();
  // 275: !node.enumeration_no_of
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
static void cont__251_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ENUMERATE, arguments->slots[0]);
  // 277: $MAKE_A_DESTINATION
  // 278:   modify_node
  // 279:     : (&node)
  // 280:       !node.is_a_destination true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__252_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__252_2;
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
  // 280: !node.is_a_destination true
  frame->slots[1] /* temp__1 */ = get__true();
  // 280: !node.is_a_destination
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
static void cont__252_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAKE_A_DESTINATION, arguments->slots[0]);
  // 288: $sim2c::WHITESPACE many(' ')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__255_1;
}
static void cont__255_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.sim2c__WHITESPACE, arguments->slots[0]);
  // 289: ... followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__256_1;
}
static void cont__256_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 289: $SEPARATOR alt(sim2c::WHITESPACE followed_by(':'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__256_2;
}
static void cont__256_2(void) {
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
  frame->cont = cont__257_1;
}
static void cont__257_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEWLINES, arguments->slots[0]);
  // 291: $NEXT_LINE ARGUMENT_LINE_END_REMARK, NEWLINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_LINE_END_REMARK;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__258_1;
}
static void cont__258_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEXT_LINE, arguments->slots[0]);
  // 293: $STORE_POSITION
  // 294:   modify_node
  // 295:     :
  // 296:       (
  // 297:         &node
  // 298:         stream
  // 299:       )
  // 300:       !node.source_position_of length_of(stream)
  // 301:       !node.fragment_of current_fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__259_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__259_3;
}
static void entry__259_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 300: !node.source_position_of length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* stream */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__259_2;
}
static void cont__259_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 300: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 301: !node.fragment_of current_fragment
  frame->slots[2] /* temp__1 */ = get__current_fragment();
  // 301: !node.fragment_of
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
static void cont__259_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_POSITION, arguments->slots[0]);
  // 303: $STORE_POSITION_MINUS_1
  // 304:   modify_node
  // 305:     :
  // 306:       (
  // 307:         &node
  // 308:         stream
  // 309:       )
  // 310:       !node.source_position_of length_of(stream)+1
  // 311:       !node.fragment_of current_fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__260_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__260_4;
}
static void entry__260_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 310: ... length_of(stream)
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
  // 310: !node.source_position_of length_of(stream)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__260_3;
}
static void cont__260_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 310: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 311: !node.fragment_of current_fragment
  frame->slots[2] /* temp__1 */ = get__current_fragment();
  // 311: !node.fragment_of
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
static void cont__260_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_POSITION_MINUS_1, arguments->slots[0]);
  // 313: $STORE_POSITION_MINUS_2
  // 314:   modify_node
  // 315:     :
  // 316:       (
  // 317:         &node
  // 318:         stream
  // 319:       )
  // 320:       !node.source_position_of length_of(stream)+2
  // 321:       !node.fragment_of current_fragment
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
  // 320: ... length_of(stream)
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
  // 320: !node.source_position_of length_of(stream)+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = number__2;
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
  // 320: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 321: !node.fragment_of current_fragment
  frame->slots[2] /* temp__1 */ = get__current_fragment();
  // 321: !node.fragment_of
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
  initialize_future(var._STORE_POSITION_MINUS_2, arguments->slots[0]);
  // 323: $STORE_END_POSITION
  // 324:   modify_node
  // 325:     :
  // 326:       (
  // 327:         &node
  // 328:         stream
  // 329:       )
  // 330:       !node.end_position_of length_of(stream)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__262_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__262_3;
}
static void entry__262_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 330: !node.end_position_of length_of(stream)
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
  // 330: !node.end_position_of
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
static void cont__262_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STORE_END_POSITION, arguments->slots[0]);
  // 334: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__263_1;
}
static void cont__263_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 336: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__263_2;
}
static void cont__263_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 340: modify_node
  // 341:   : (&node)
  // 342:     !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__263_3;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__263_5;
}
static void entry__263_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 342: !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__263_4;
}
static void cont__263_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 342: !node.namespace_of
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
static void cont__263_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 343: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__263_6;
}
static void cont__263_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 338: sequence
  // 339:   "::"
  // 340:   modify_node
  // 341:     : (&node)
  // 342:       !node.namespace_of node.name_of
  // 343:   capture(name_of NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__263_7;
  arguments->slots[1] = temp__5;
  arguments->slots[2] = temp__6;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__263_8;
}
static void cont__263_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 337: optional
  // 338:   sequence
  // 339:     "::"
  // 340:     modify_node
  // 341:       : (&node)
  // 342:         !node.namespace_of node.name_of
  // 343:     capture(name_of NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__263_9;
}
static void cont__263_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 332: $IDENTIFIER
  // 333:   sequence
  // 334:     set_node(identifier)
  // 335:     STORE_POSITION
  // 336:     capture(name_of NAME)
  // 337:     optional
  // 338:       sequence
  // 339:         "::"
  // 340:         modify_node
  // 341:           : (&node)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = temp__2;
  arguments->slots[3] = temp__3;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__263_10;
}
static void cont__263_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._IDENTIFIER, arguments->slots[0]);
  // 348: set_node(identifier)
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
  temp__1 = arguments->slots[0];
  // 350: optional(NOT_USED)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NOT_USED;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__264_2;
}
static void cont__264_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 351: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__264_3;
}
static void cont__264_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 355: modify_node
  // 356:   : (&node)
  // 357:     if node.is_not_used:
  // 358:       SyntaxError node "namespace must not start with an underscore"
  // 359:     !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__264_4;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__264_10;
}
static void entry__264_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 357: ... node.is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_not_used();
  func = myself->type;
  frame->cont = cont__264_5;
}
static void cont__264_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 357: ... :
  // 358:   SyntaxError node "namespace must not start with an underscore"
  frame->slots[2] /* temp__2 */ = create_closure(entry__264_6, 0);
  // 357: if node.is_not_used:
  // 358:   SyntaxError node "namespace must not start with an underscore"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__264_8;
}
static void entry__264_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 358: SyntaxError node "namespace must not start with an underscore"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  arguments->slots[1] = string__264_7;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__264_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 359: !node.namespace_of node.name_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__264_9;
}
static void cont__264_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 359: !node.namespace_of
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
static void cont__264_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 360: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__264_11;
}
static void cont__264_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 353: sequence
  // 354:   "::"
  // 355:   modify_node
  // 356:     : (&node)
  // 357:       if node.is_not_used:
  // 358:         SyntaxError node "namespace must not start with an underscore"
  // 359:       !node.namespace_of node.name_of
  // 360:   capture(name_of NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__264_12;
  arguments->slots[1] = temp__6;
  arguments->slots[2] = temp__7;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__264_13;
}
static void cont__264_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 352: optional
  // 353:   sequence
  // 354:     "::"
  // 355:     modify_node
  // 356:       : (&node)
  // 357:         if node.is_not_used:
  // 358:           SyntaxError node "namespace must not start with an underscore"
  // 359:         !node.namespace_of node.name_of
  // 360:     capture(name_of NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__5;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__264_14;
}
static void cont__264_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 346: $DEFINE_IDENTIFIER
  // 347:   sequence
  // 348:     set_node(identifier)
  // 349:     STORE_POSITION
  // 350:     optional(NOT_USED)
  // 351:     capture(name_of NAME)
  // 352:     optional
  // 353:       sequence
  // 354:         "::"
  // 355:         modify_node
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = temp__2;
  arguments->slots[3] = temp__3;
  arguments->slots[4] = temp__4;
  arguments->slots[5] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__264_15;
}
static void cont__264_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DEFINE_IDENTIFIER, arguments->slots[0]);
  // 365: set_node(identifier)
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
  temp__1 = arguments->slots[0];
  // 367: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__265_2;
}
static void cont__265_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 368: expect("::")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__265_3;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__265_4;
}
static void cont__265_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 369: capture(name_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__265_5;
}
static void cont__265_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 363: $NAMESPACED_IDENTIFIER
  // 364:   sequence
  // 365:     set_node(identifier)
  // 366:     STORE_POSITION
  // 367:     capture(namespace_of NAME)
  // 368:     expect("::")
  // 369:     capture(name_of NAME)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = temp__2;
  arguments->slots[3] = temp__3;
  arguments->slots[4] = temp__4;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__265_6;
}
static void cont__265_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMESPACED_IDENTIFIER, arguments->slots[0]);
  // 374: ... optional("./")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__266_1;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__266_2;
}
static void cont__266_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 374: ... "/", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__266_3;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__266_4;
}
static void cont__266_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 374: ... some("/", NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__266_5;
}
static void cont__266_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 374: $FILENAME optional("./"), NAME, some("/", NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = temp__2;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__266_6;
}
static void cont__266_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FILENAME, arguments->slots[0]);
  // 379: set_node(require_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__require_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__267_1;
}
static void cont__267_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 382: capture(node::filename_of FILENAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filename_of();
  arguments->slots[1] = var._FILENAME;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__267_2;
}
static void cont__267_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 385: inspect_node
  // 386:   : (node stream)
  // 387:     $filename node::filename_of(node)
  // 388:     if required_modules(filename).is_defined:
  // 389:       ParseError stream "
  // 390:         the module "@(filename)" is required twice@
  // 391:     !required_modules(filename) node
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__267_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__267_13;
}
static void entry__267_3(void) {
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
  // 387: $filename node::filename_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filename_of();
  func = myself->type;
  frame->cont = cont__267_4;
}
static void cont__267_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 388: ... required_modules(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__267_5;
}
static void cont__267_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 388: ... required_modules(filename).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__267_6;
}
static void cont__267_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 388: ... :
  // 389:   ParseError stream "
  // 390:     the module "@(filename)" is required twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__267_7, 0);
  // 388: if required_modules(filename).is_defined:
  // 389:   ParseError stream "
  // 390:     the module "@(filename)" is required twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__267_11;
}
static void entry__267_7(void) {
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
  // 389: ... "
  // 390:   the module "@(filename)" is required twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__267_8;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__267_9;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__267_10;
}
static void cont__267_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 389: ParseError stream "
  // 390:   the module "@(filename)" is required twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__267_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 391: !required_modules(filename) node
  frame->slots[3] /* temp__1 */ = frame->slots[0] /* node */;
  // 391: !required_modules(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__267_12;
}
static void cont__267_12(void) {
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
static void cont__267_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 376: $REQUIRE
  // 377:   sequence
  // 378:     "<require"
  // 379:     set_node(require_instruction)
  // 380:     STORE_POSITION
  // 381:     sim2c::WHITESPACE
  // 382:     capture(node::filename_of FILENAME)
  // 383:     ">"
  // 384:     STORE_END_POSITION
  // 385:     inspect_node
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = string__267_14;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._STORE_POSITION;
  arguments->slots[3] = var.sim2c__WHITESPACE;
  arguments->slots[4] = temp__2;
  arguments->slots[5] = string__267_15;
  arguments->slots[6] = var._STORE_END_POSITION;
  arguments->slots[7] = temp__3;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__267_16;
}
static void cont__267_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REQUIRE, arguments->slots[0]);
  // 397: set_node(namespace_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__namespace_instruction();
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
  temp__1 = arguments->slots[0];
  // 398: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
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
  temp__2 = arguments->slots[0];
  // 401: infix_operator("=")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__268_3;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__268_4;
}
static void cont__268_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 402: modify_node
  // 403:   : (&node)
  // 404:     !node.namespace_alias_of node.namespace_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__268_5;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__268_7;
}
static void entry__268_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 404: !node.namespace_alias_of node.namespace_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__268_6;
}
static void cont__268_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 404: !node.namespace_alias_of
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
static void cont__268_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 405: capture(namespace_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__namespace_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__268_8;
}
static void cont__268_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 400: sequence
  // 401:   infix_operator("=")
  // 402:   modify_node
  // 403:     : (&node)
  // 404:       !node.namespace_alias_of node.namespace_of
  // 405:   capture(namespace_of NAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__5;
  arguments->slots[1] = temp__6;
  arguments->slots[2] = temp__7;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__268_9;
}
static void cont__268_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 399: optional
  // 400:   sequence
  // 401:     infix_operator("=")
  // 402:     modify_node
  // 403:       : (&node)
  // 404:         !node.namespace_alias_of node.namespace_of
  // 405:     capture(namespace_of NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__268_10;
}
static void cont__268_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 407: inspect_node
  // 408:   : (node stream)
  // 409:     $namespace namespace_of(node)
  // 410:     if defined_namespaces(namespace):
  // 411:       ParseError stream "
  // 412:         the namespace "@(namespace)" is defined twice@
  // 413:     !defined_namespaces(namespace) true
  // 414:     $alias namespace_alias_of(node)
  // 415:     if alias.is_defined:
  // 416:       if namespace_mappings(alias).is_defined:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__268_11;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__268_31;
}
static void entry__268_22(void) {
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
  // 416: ... namespace_mappings(alias)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alias */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__268_23;
}
static void cont__268_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 416: ... namespace_mappings(alias).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__268_24;
}
static void cont__268_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 416: ... :
  // 417:   ParseError stream "
  // 418:     the namespace alias "@(alias)" is defined twice@
  frame->slots[5] /* temp__3 */ = create_closure(entry__268_25, 0);
  // 416: if namespace_mappings(alias).is_defined:
  // 417:   ParseError stream "
  // 418:     the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__268_29;
}
static void entry__268_25(void) {
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
  // 417: ... "
  // 418:   the namespace alias "@(alias)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__268_26;
  arguments->slots[1] = frame->slots[1] /* alias */;
  arguments->slots[2] = string__268_27;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__268_28;
}
static void cont__268_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 417: ParseError stream "
  // 418:   the namespace alias "@(alias)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__268_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 419: !namespace_mappings(alias) namespace
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* namespace */;
  // 419: !namespace_mappings(alias)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alias */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__268_30;
}
static void cont__268_30(void) {
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
static void entry__268_11(void) {
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
  // 409: $namespace namespace_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__268_12;
}
static void cont__268_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 410: ... defined_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  result_count = 1;
  myself = get__defined_namespaces();
  func = myself->type;
  frame->cont = cont__268_13;
}
static void cont__268_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 410: ... :
  // 411:   ParseError stream "
  // 412:     the namespace "@(namespace)" is defined twice@
  frame->slots[5] /* temp__2 */ = create_closure(entry__268_14, 0);
  // 410: if defined_namespaces(namespace):
  // 411:   ParseError stream "
  // 412:     the namespace "@(namespace)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__268_18;
}
static void entry__268_14(void) {
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
  // 411: ... "
  // 412:   the namespace "@(namespace)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__268_15;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__268_16;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__268_17;
}
static void cont__268_17(void) {
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
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__268_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 413: !defined_namespaces(namespace) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 413: !defined_namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__defined_namespaces();
  func = myself->type;
  frame->cont = cont__268_19;
}
static void cont__268_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_namespaces(arguments->slots[0]);
  // 414: $alias namespace_alias_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_alias_of();
  func = myself->type;
  frame->cont = cont__268_20;
}
static void cont__268_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* alias */, arguments->slots[0]);
  // 415: ... alias.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* alias */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__268_21;
}
static void cont__268_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 415: ... :
  // 416:   if namespace_mappings(alias).is_defined:
  // 417:     ParseError stream "
  // 418:       the namespace alias "@(alias)" is defined twice@
  // 419:   !namespace_mappings(alias) namespace
  frame->slots[5] /* temp__2 */ = create_closure(entry__268_22, 0);
  // 415: if alias.is_defined:
  // 416:   if namespace_mappings(alias).is_defined:
  // 417:     ParseError stream "
  // 418:       the namespace alias "@(alias)" is defined twice@
  // 419:   !namespace_mappings(alias) namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__268_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__8 = arguments->slots[0];
  // 393: $NAMESPACE
  // 394:   sequence
  // 395:     "<namespace"
  // 396:     sim2c::WHITESPACE
  // 397:     set_node(namespace_instruction)
  // 398:     capture(namespace_of NAME)
  // 399:     optional
  // 400:       sequence
  // 401:         infix_operator("=")
  // 402:         modify_node
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__268_32;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = temp__1;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = temp__3;
  arguments->slots[5] = string__268_33;
  arguments->slots[6] = temp__8;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__268_34;
}
static void cont__268_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAMESPACE, arguments->slots[0]);
  // 425: set_node(using_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__using_instruction();
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
  temp__1 = arguments->slots[0];
  // 426: capture(namespace_of NAME)
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
  temp__2 = arguments->slots[0];
  // 428: inspect_node
  // 429:   : (node stream)
  // 430:     $namespace namespace_of(node)
  // 431:     if used_namespaces(namespace):
  // 432:       ParseError stream "
  // 433:         the namespace "@(namespace)" is used twice@
  // 434:     !used_namespaces(namespace) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__269_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__269_12;
}
static void entry__269_3(void) {
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
  // 430: $namespace namespace_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__269_4;
}
static void cont__269_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 431: ... used_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__269_5;
}
static void cont__269_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 431: ... :
  // 432:   ParseError stream "
  // 433:     the namespace "@(namespace)" is used twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__269_6, 0);
  // 431: if used_namespaces(namespace):
  // 432:   ParseError stream "
  // 433:     the namespace "@(namespace)" is used twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__269_10;
}
static void entry__269_6(void) {
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
  // 432: ... "
  // 433:   the namespace "@(namespace)" is used twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__269_7;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__269_8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__269_9;
}
static void cont__269_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 432: ParseError stream "
  // 433:   the namespace "@(namespace)" is used twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__269_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 434: !used_namespaces(namespace) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 434: !used_namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__269_11;
}
static void cont__269_11(void) {
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
static void cont__269_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 421: $USING
  // 422:   sequence
  // 423:     "<using"
  // 424:     sim2c::WHITESPACE
  // 425:     set_node(using_instruction)
  // 426:     capture(namespace_of NAME)
  // 427:     ">"
  // 428:     inspect_node
  // 429:       : (node stream)
  // 430:         $namespace namespace_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__269_13;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = temp__1;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = string__269_14;
  arguments->slots[5] = temp__3;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__269_15;
}
static void cont__269_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._USING, arguments->slots[0]);
  // 436: ... alt(LETTER DIGIT '_' '.')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  arguments->slots[1] = get__DIGIT();
  arguments->slots[2] = character__95;
  arguments->slots[3] = character__46;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__270_1;
}
static void cont__270_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 436: $BASENAME many(alt(LETTER DIGIT '_' '.'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__270_2;
}
static void cont__270_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BASENAME, arguments->slots[0]);
  // 437: ... some("../")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__271_1;
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
  temp__2 = arguments->slots[0];
  // 437: ... alt('/' "./" some("../"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__271_3;
  arguments->slots[2] = temp__2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__271_4;
}
static void cont__271_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 437: ... '/', BASENAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = var._BASENAME;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__271_5;
}
static void cont__271_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 437: ... some('/', BASENAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__271_6;
}
static void cont__271_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 437: $C_FILENAME alt('/' "./" some("../")), BASENAME, some('/', BASENAME)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._BASENAME;
  arguments->slots[2] = temp__3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__271_7;
}
static void cont__271_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_FILENAME, arguments->slots[0]);
  // 443: set_node(include_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__include_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__272_1;
}
static void cont__272_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 444: capture(node::filename_of C_FILENAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filename_of();
  arguments->slots[1] = var._C_FILENAME;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__272_2;
}
static void cont__272_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 446: inspect_node
  // 447:   : (node stream)
  // 448:     $filename node::filename_of(node)
  // 449:     if included_files(filename):
  // 450:       ParseError stream "
  // 451:         the file "@(filename)" is included twice@
  // 452:     !included_files(filename) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__272_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__272_12;
}
static void entry__272_3(void) {
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
  // 448: $filename node::filename_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filename_of();
  func = myself->type;
  frame->cont = cont__272_4;
}
static void cont__272_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 449: ... included_files(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__272_5;
}
static void cont__272_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 449: ... :
  // 450:   ParseError stream "
  // 451:     the file "@(filename)" is included twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__272_6, 0);
  // 449: if included_files(filename):
  // 450:   ParseError stream "
  // 451:     the file "@(filename)" is included twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__272_10;
}
static void entry__272_6(void) {
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
  // 450: ... "
  // 451:   the file "@(filename)" is included twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__272_7;
  arguments->slots[1] = frame->slots[1] /* filename */;
  arguments->slots[2] = string__272_8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__272_9;
}
static void cont__272_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 450: ParseError stream "
  // 451:   the file "@(filename)" is included twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__272_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 452: !included_files(filename) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 452: !included_files(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__272_11;
}
static void cont__272_11(void) {
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
static void cont__272_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 439: $INCLUDE
  // 440:   sequence
  // 441:     "<include"
  // 442:     sim2c::WHITESPACE
  // 443:     set_node(include_instruction)
  // 444:     capture(node::filename_of C_FILENAME)
  // 445:     ">"
  // 446:     inspect_node
  // 447:       : (node stream)
  // 448:         $filename node::filename_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__272_13;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = temp__1;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = string__272_14;
  arguments->slots[5] = temp__3;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__272_15;
}
static void cont__272_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INCLUDE, arguments->slots[0]);
  // 458: set_node(link_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__link_instruction();
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
  temp__1 = arguments->slots[0];
  // 459: capture(node::filename_of C_FILENAME)
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
  temp__2 = arguments->slots[0];
  // 461: inspect_node
  // 462:   : (node stream)
  // 463:     $filename node::filename_of(node)
  // 464:     if linked_libraries(filename):
  // 465:       ParseError stream "
  // 466:         the library "@(filename)" is linked twice@
  // 467:     !linked_libraries(filename) true
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
  // 463: $filename node::filename_of(node)
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
  // 464: ... linked_libraries(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  result_count = 1;
  myself = get__linked_libraries();
  func = myself->type;
  frame->cont = cont__273_5;
}
static void cont__273_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 464: ... :
  // 465:   ParseError stream "
  // 466:     the library "@(filename)" is linked twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__273_6, 0);
  // 464: if linked_libraries(filename):
  // 465:   ParseError stream "
  // 466:     the library "@(filename)" is linked twice@
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
  // 465: ... "
  // 466:   the library "@(filename)" is linked twice@
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
  // 465: ParseError stream "
  // 466:   the library "@(filename)" is linked twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__273_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 467: !linked_libraries(filename) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 467: !linked_libraries(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filename */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__linked_libraries();
  func = myself->type;
  frame->cont = cont__273_11;
}
static void cont__273_11(void) {
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
static void cont__273_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 454: $LINK
  // 455:   sequence
  // 456:     "<link"
  // 457:     sim2c::WHITESPACE
  // 458:     set_node(link_instruction)
  // 459:     capture(node::filename_of C_FILENAME)
  // 460:     ">"
  // 461:     inspect_node
  // 462:       : (node stream)
  // 463:         $filename node::filename_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__273_13;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = temp__1;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = string__273_14;
  arguments->slots[5] = temp__3;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__273_15;
}
static void cont__273_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._LINK, arguments->slots[0]);
  // 469: ... alt(LETTER DIGIT '_' '.' '*' '?')
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
  frame->cont = cont__274_1;
}
static void cont__274_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 469: $MASK many(alt(LETTER DIGIT '_' '.' '*' '?'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__274_2;
}
static void cont__274_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MASK, arguments->slots[0]);
  // 470: ... some("../")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__275_1;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__275_2;
}
static void cont__275_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 470: ... alt('/' "./" some("../"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__275_3;
  arguments->slots[2] = temp__2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__275_4;
}
static void cont__275_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 470: ... '/', MASK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = var._MASK;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__275_5;
}
static void cont__275_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 470: ... some('/', MASK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__275_6;
}
static void cont__275_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 470: $FILEMASK alt('/' "./" some("../")), MASK, some('/', MASK)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._MASK;
  arguments->slots[2] = temp__3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__275_7;
}
static void cont__275_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FILEMASK, arguments->slots[0]);
  // 476: set_node(data_instruction)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__data_instruction();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__276_1;
}
static void cont__276_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 477: capture(node::filemask_of FILEMASK)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__filemask_of();
  arguments->slots[1] = var._FILEMASK;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__276_2;
}
static void cont__276_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 479: inspect_node
  // 480:   : (node stream)
  // 481:     $filemask node::filemask_of(node)
  // 482:     if dependent_data(filemask):
  // 483:       ParseError stream "
  // 484:         the data dependency "@(filemask)" is defined twice@
  // 485:     !dependent_data(filemask) true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__276_3;
  result_count = 1;
  myself = get__inspect_node();
  func = myself->type;
  frame->cont = cont__276_12;
}
static void entry__276_3(void) {
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
  // 481: $filemask node::filemask_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__node__filemask_of();
  func = myself->type;
  frame->cont = cont__276_4;
}
static void cont__276_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filemask */, arguments->slots[0]);
  // 482: ... dependent_data(filemask)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filemask */;
  result_count = 1;
  myself = get__dependent_data();
  func = myself->type;
  frame->cont = cont__276_5;
}
static void cont__276_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 482: ... :
  // 483:   ParseError stream "
  // 484:     the data dependency "@(filemask)" is defined twice@
  frame->slots[4] /* temp__2 */ = create_closure(entry__276_6, 0);
  // 482: if dependent_data(filemask):
  // 483:   ParseError stream "
  // 484:     the data dependency "@(filemask)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__276_10;
}
static void entry__276_6(void) {
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
  // 483: ... "
  // 484:   the data dependency "@(filemask)" is defined twice@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__276_7;
  arguments->slots[1] = frame->slots[1] /* filemask */;
  arguments->slots[2] = string__276_8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__276_9;
}
static void cont__276_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 483: ParseError stream "
  // 484:   the data dependency "@(filemask)" is defined twice@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__276_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 485: !dependent_data(filemask) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 485: !dependent_data(filemask)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* filemask */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__dependent_data();
  func = myself->type;
  frame->cont = cont__276_11;
}
static void cont__276_11(void) {
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
static void cont__276_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 472: $DATA
  // 473:   sequence
  // 474:     "<data"
  // 475:     sim2c::WHITESPACE
  // 476:     set_node(data_instruction)
  // 477:     capture(node::filemask_of FILEMASK)
  // 478:     ">"
  // 479:     inspect_node
  // 480:       : (node stream)
  // 481:         $filemask node::filemask_of(node)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__276_13;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = temp__1;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = string__276_14;
  arguments->slots[5] = temp__3;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__276_15;
}
static void cont__276_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._DATA, arguments->slots[0]);
  // 489: alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
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
  frame->cont = cont__277_1;
}
static void cont__277_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 490: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__277_2;
}
static void cont__277_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 490: ... NEXT_LINE_REMARK, expect(outdent_marker)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE_REMARK;
  arguments->slots[1] = temp__5;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__277_3;
}
static void cont__277_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 490: ... alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEW_LINE_END_REMARK;
  arguments->slots[1] = temp__4;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__277_4;
}
static void cont__277_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 490: optional(alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__277_5;
}
static void cont__277_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 487: $META_INSTRUCTION
  // 488:   sequence
  // 489:     alt(REQUIRE NAMESPACE USING INCLUDE LINK DATA)
  // 490:     optional(alt(NEW_LINE_END_REMARK NEXT_LINE_REMARK, expect(outdent_marker)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__277_6;
}
static void cont__277_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._META_INSTRUCTION, arguments->slots[0]);
  // 495: ... some(PRINTABLE_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__PRINTABLE_CHARACTER();
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__278_1;
}
static void cont__278_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 495: $REMARK_LINE multi_capture(remark_lines_of some(PRINTABLE_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__remark_lines_of();
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__278_2;
}
static void cont__278_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_LINE, arguments->slots[0]);
  // 500: ... interleaved(REMARK_LINE NEWLINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_LINE;
  arguments->slots[1] = var._NEWLINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__279_1;
}
static void cont__279_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 500: ... expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__279_2;
}
static void cont__279_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 500: ... INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = temp__3;
  arguments->slots[2] = temp__4;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__279_3;
}
static void cont__279_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 500: optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__279_4;
}
static void cont__279_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 497: $REMARK_LINES
  // 498:   sequence
  // 499:     REMARK_LINE
  // 500:     optional(INDENT, interleaved(REMARK_LINE NEWLINE), expect(outdent_marker))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_LINE;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__279_5;
}
static void cont__279_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_LINES, arguments->slots[0]);
  // 502: ... set_node(remark_statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__remark_statement();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__280_1;
}
static void cont__280_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 502: $SINGLE_REMARK_STATEMENT HASHTAG, set_node(remark_statement), REMARK_LINES
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._REMARK_LINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__280_2;
}
static void cont__280_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SINGLE_REMARK_STATEMENT, arguments->slots[0]);
  // 504: $REMARK_STATEMENT multi_span(statements_of SINGLE_REMARK_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = var._SINGLE_REMARK_STATEMENT;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__281_1;
}
static void cont__281_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_STATEMENT, arguments->slots[0]);
  // 505: $REMARK HASHTAG, REMARK_LINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = var._REMARK_LINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__282_1;
}
static void cont__282_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK, arguments->slots[0]);
  // 510: modify_node
  // 511:   : (&node)
  // 512:     unless node.is_a_definition || node.is_a_meta_instruction:
  // 513:       $remark_lines remark_lines_of(node)
  // 514:       if
  // 515:         arguments_of(node).is_empty:
  // 516:           !node.remark_lines_behind_of remark_lines
  // 517:         :
  // 518:           append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 519:       !node.remark_lines_of empty_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__283_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__283_23;
}
static void entry__283_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 512: ... node.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__283_2;
}
static void cont__283_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 512: ... node.is_a_meta_instruction
  frame->slots[3] /* temp__3 */ = create_closure(entry__283_3, 0);
  // 512: ... node.is_a_definition || node.is_a_meta_instruction
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__283_5;
}
static void entry__283_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 512: ... node.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__is_a_meta_instruction();
  func = myself->type;
  frame->cont = cont__283_4;
}
static void cont__283_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 512: ... node.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__283_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 512: ... :
  // 513:   $remark_lines remark_lines_of(node)
  // 514:   if
  // 515:     arguments_of(node).is_empty:
  // 516:       !node.remark_lines_behind_of remark_lines
  // 517:     :
  // 518:       append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 519:   !node.remark_lines_of empty_list
  frame->slots[4] /* temp__4 */ = create_closure(entry__283_6, 0);
  // 512: unless node.is_a_definition || node.is_a_meta_instruction:
  // 513:   $remark_lines remark_lines_of(node)
  // 514:   if
  // 515:     arguments_of(node).is_empty:
  // 516:       !node.remark_lines_behind_of remark_lines
  // 517:     :
  // 518:       append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  // 519:   !node.remark_lines_of empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__283_22;
}
static void entry__283_6(void) {
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
  // 513: $remark_lines remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__283_7;
}
static void cont__283_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* remark_lines */, arguments->slots[0]);
  // 515: arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__283_8;
}
static void cont__283_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 515: arguments_of(node).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__283_9;
}
static void cont__283_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 515: ... :
  // 516:   !node.remark_lines_behind_of remark_lines
  frame->slots[4] /* temp__3 */ = create_closure(entry__283_10, 0);
  // 517: :
  // 518:   append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  frame->slots[5] /* temp__4 */ = create_closure(entry__283_11, 0);
  // 514: if
  // 515:   arguments_of(node).is_empty:
  // 516:     !node.remark_lines_behind_of remark_lines
  // 517:   :
  // 518:     append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__283_21;
}
static void entry__283_10(void) {
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
  // 516: !node.remark_lines_behind_of remark_lines
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* remark_lines */;
  // 516: !node.remark_lines_behind_of
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
static void entry__283_11(void) {
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
  // 518: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__283_12;
}
static void cont__283_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 518: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__283_13;
}
static void cont__283_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 518: ... node.arguments_of(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__283_14;
}
static void cont__283_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 518: ... node.arguments_of(-1).remark_lines_behind_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__remark_lines_behind_of();
  func = myself->type;
  frame->cont = cont__283_15;
}
static void cont__283_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 518: append &node.arguments_of(-1).remark_lines_behind_of remark_lines
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__283_16;
}
static void cont__283_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 518: ... node.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__283_17;
}
static void cont__283_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 518: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__283_18;
}
static void cont__283_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 518: ... node.arguments_of(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = frame->slots[7] /* temp__6 */;
  func = myself->type;
  frame->cont = cont__283_19;
}
static void cont__283_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 518: ... &node.arguments_of(-1).remark_lines_behind_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[9] /* temp__8 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_behind_of, frame->slots[6] /* temp__5 */);
    frame->slots[9] /* temp__8 */ = temp;

  }
  // 518: ... &node.arguments_of(-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__7 */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = frame->slots[7] /* temp__6 */;
  func = myself->type;
  frame->cont = cont__283_20;
}
static void cont__283_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 518: ... &node.arguments_of
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
static void cont__283_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 519: !node.remark_lines_of empty_list
  frame->slots[2] /* temp__1 */ = get__empty_list();
  // 519: !node.remark_lines_of
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
static void cont__283_22(void) {
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
static void cont__283_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 507: $REMARK_BEHIND
  // 508:   sequence
  // 509:     REMARK
  // 510:     modify_node
  // 511:       : (&node)
  // 512:         unless node.is_a_definition || node.is_a_meta_instruction:
  // 513:           $remark_lines remark_lines_of(node)
  // 514:           if
  // 515:             arguments_of(node).is_empty:
  // 516:               !node.remark_lines_behind_of remark_lines
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__283_24;
}
static void cont__283_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_BEHIND, arguments->slots[0]);
  // 524: modify_node
  // 525:   :
  // 526:     (
  // 527:       &node
  // 528:       stream
  // 529:     )
  // 530:     unless stream(1) == OUTDENT: # very dirty fix
  // 531:       !node.remark_lines_behind_of remark_lines_of(node)
  // 532:       !node.remark_lines_of empty_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__284_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__284_7;
}
static void entry__284_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // node: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 530: ... stream(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* stream */;
  func = myself->type;
  frame->cont = cont__284_2;
}
static void cont__284_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 530: ... stream(1) == OUTDENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._OUTDENT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__284_3;
}
static void cont__284_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 530: ... : # very dirty fix
  // 531:   !node.remark_lines_behind_of remark_lines_of(node)
  // 532:   !node.remark_lines_of empty_list
  frame->slots[4] /* temp__3 */ = create_closure(entry__284_4, 0);
  // 530: unless stream(1) == OUTDENT: # very dirty fix
  // 531:   !node.remark_lines_behind_of remark_lines_of(node)
  // 532:   !node.remark_lines_of empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__284_6;
}
static void entry__284_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 531: !node.remark_lines_behind_of remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__284_5;
}
static void cont__284_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 531: !node.remark_lines_behind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_behind_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 532: !node.remark_lines_of empty_list
  frame->slots[1] /* temp__1 */ = get__empty_list();
  // 532: !node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__284_6(void) {
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
static void cont__284_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 521: $REMARK_FIRST
  // 522:   sequence
  // 523:     REMARK
  // 524:     modify_node
  // 525:       :
  // 526:         (
  // 527:           &node
  // 528:           stream
  // 529:         )
  // 530:         unless stream(1) == OUTDENT: # very dirty fix
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__284_8;
}
static void cont__284_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REMARK_FIRST, arguments->slots[0]);
  // 534: ... sim2c::WHITESPACE, HASHTAG, REMARK_LINE
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
  temp__1 = arguments->slots[0];
  // 534: $LINE_END_REMARK optional(sim2c::WHITESPACE, HASHTAG, REMARK_LINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 542: modify_node
  // 543:   : (&node)
  // 544:     unless node.is_a_definition:
  // 545:       $n length_of(arguments_of(node))
  // 546:       if n > 0:
  // 547:         push
  // 548:           &node.arguments_of(n).remark_lines_of
  // 549:           remark_lines_of(node)(-1)
  // 550:         range &node.remark_lines_of 1 -2
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
  // 544: ... node.is_a_definition
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
  // 544: ... :
  // 545:   $n length_of(arguments_of(node))
  // 546:   if n > 0:
  // 547:     push
  // 548:       &node.arguments_of(n).remark_lines_of
  // 549:       remark_lines_of(node)(-1)
  // 550:     range &node.remark_lines_of 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__286_3, 0);
  // 544: unless node.is_a_definition:
  // 545:   $n length_of(arguments_of(node))
  // 546:   if n > 0:
  // 547:     push
  // 548:       &node.arguments_of(n).remark_lines_of
  // 549:       remark_lines_of(node)(-1)
  // 550:     range &node.remark_lines_of 1 -2
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
  // 548: ... node.arguments_of
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
  // 548: ... node.arguments_of(n)
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
  // 548: ... node.arguments_of(n).remark_lines_of
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
  // 549: ... 1
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
  // 549: remark_lines_of(node)
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
  // 549: remark_lines_of(node)(-1)
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
  // 547: push
  // 548:   &node.arguments_of(n).remark_lines_of
  // 549:   remark_lines_of(node)(-1)
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
  // 548: ... node.arguments_of
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
  // 548: ... node.arguments_of(n)
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
  // 548: &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[10] /* temp__9 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[8] /* temp__7 */);
    frame->slots[10] /* temp__9 */ = temp;

  }
  // 548: &node.arguments_of(n)
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
  // 548: &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__8 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 550: ... node.remark_lines_of
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
  // 550: ... 2
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
  // 550: range &node.remark_lines_of 1 -2
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
  // 550: ... &node.remark_lines_of
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
  // 545: ... arguments_of(node)
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
  // 545: $n length_of(arguments_of(node))
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
  // 546: ... n > 0
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
  // 546: ... :
  // 547:   push
  // 548:     &node.arguments_of(n).remark_lines_of
  // 549:     remark_lines_of(node)(-1)
  // 550:   range &node.remark_lines_of 1 -2
  frame->slots[3] /* temp__2 */ = create_closure(entry__286_7, 0);
  // 546: if n > 0:
  // 547:   push
  // 548:     &node.arguments_of(n).remark_lines_of
  // 549:     remark_lines_of(node)(-1)
  // 550:   range &node.remark_lines_of 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  temp__2 = arguments->slots[0];
  // 538: sequence
  // 539:   sim2c::WHITESPACE
  // 540:   HASHTAG
  // 541:   REMARK_LINE
  // 542:   modify_node
  // 543:     : (&node)
  // 544:       unless node.is_a_definition:
  // 545:         $n length_of(arguments_of(node))
  // 546:         if n > 0:
  // 547:           push
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._HASHTAG;
  arguments->slots[2] = var._REMARK_LINE;
  arguments->slots[3] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 536: $ARGUMENT_LINE_END_REMARK
  // 537:   optional
  // 538:     sequence
  // 539:       sim2c::WHITESPACE
  // 540:       HASHTAG
  // 541:       REMARK_LINE
  // 542:       modify_node
  // 543:         : (&node)
  // 544:           unless node.is_a_definition:
  // 545:             $n length_of(arguments_of(node))
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 556: modify_node
  // 557:   : (&node)
  // 558:     unless node.is_a_definition:
  // 559:       $n length_of(arguments_of(node))
  // 560:       if n > 0:
  // 561:         push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 562:         range &node.remark_lines_of 1 -2
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
  // 558: ... node.is_a_definition
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
  // 558: ... :
  // 559:   $n length_of(arguments_of(node))
  // 560:   if n > 0:
  // 561:     push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 562:     range &node.remark_lines_of 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__287_3, 0);
  // 558: unless node.is_a_definition:
  // 559:   $n length_of(arguments_of(node))
  // 560:   if n > 0:
  // 561:     push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 562:     range &node.remark_lines_of 1 -2
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
  // 561: ... node.arguments_of
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
  // 561: ... node.arguments_of(n)
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
  // 561: ... node.arguments_of(n).remark_lines_of
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
  // 561: ... 1
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
  // 561: ... remark_lines_of(node)
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
  // 561: ... remark_lines_of(node)(-1)
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
  // 561: push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
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
  // 561: ... node.arguments_of
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
  // 561: ... node.arguments_of(n)
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
  // 561: ... &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[10] /* temp__9 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[8] /* temp__7 */);
    frame->slots[10] /* temp__9 */ = temp;

  }
  // 561: ... &node.arguments_of(n)
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
  // 561: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__8 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 562: ... node.remark_lines_of
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
  // 562: ... 2
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
  // 562: range &node.remark_lines_of 1 -2
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
  // 562: ... &node.remark_lines_of
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
  // 559: ... arguments_of(node)
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
  // 559: $n length_of(arguments_of(node))
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
  // 560: ... n > 0
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
  // 560: ... :
  // 561:   push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 562:   range &node.remark_lines_of 1 -2
  frame->slots[3] /* temp__2 */ = create_closure(entry__287_7, 0);
  // 560: if n > 0:
  // 561:   push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // 562:   range &node.remark_lines_of 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  temp__1 = arguments->slots[0];
  // 552: $ARGUMENT_REMARK
  // 553:   sequence
  // 554:     HASHTAG
  // 555:     REMARK_LINE
  // 556:     modify_node
  // 557:       : (&node)
  // 558:         unless node.is_a_definition:
  // 559:           $n length_of(arguments_of(node))
  // 560:           if n > 0:
  // 561:             push &node.arguments_of(n).remark_lines_of remark_lines_of(node)(-1)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._HASHTAG;
  arguments->slots[1] = var._REMARK_LINE;
  arguments->slots[2] = temp__1;
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
  // 564: $NEW_LINE_END_REMARK sim2c::WHITESPACE, HASHTAG, REMARK_LINE
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
  // 565: $NEXT_LINE_REMARK INDENT, REMARK
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
  // 573: modify_node
  // 574:   : (node)
  // 575:     ->
  // 576:       function_call
  // 577:         .functor_of node
  // 578:         .fragment_of fragment_of(node)
  // 579:         .source_position_of source_position_of(node)
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
  // 578: ... fragment_of(node)
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
  // 579: ... source_position_of(node)
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
  // 576: function_call
  // 577:   .functor_of node
  // 578:   .fragment_of fragment_of(node)
  // 579:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* node */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 575: ->
  // 576:   function_call
  // 577:     .functor_of node
  // 578:     .fragment_of fragment_of(node)
  // 579:     .source_position_of source_position_of(node)
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
  temp__1 = arguments->slots[0];
  // 580: ... alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS)
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
  temp__4 = arguments->slots[0];
  // 580: ... optional(alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 580: inline(optional(alt(ARGUMENTS INLINE_ATTRIBUTE_VALUE_PAIRS)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 581: expect(')')
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
  temp__5 = arguments->slots[0];
  // 570: $FUNCTION_CALL
  // 571:   sequence
  // 572:     '('
  // 573:     modify_node
  // 574:       : (node)
  // 575:         ->
  // 576:           function_call
  // 577:             .functor_of node
  // 578:             .fragment_of fragment_of(node)
  // 579:             .source_position_of source_position_of(node)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__2;
  arguments->slots[3] = temp__5;
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
  // 584: $MAKE_ATTRIBUTE_ACCESS
  // 585:   modify_node
  // 586:     : (&node)
  // 587:       !node
  // 588:         function_call
  // 589:           .arguments_of list(node)
  // 590:           .is_an_attribute_access true
  // 591:           .fragment_of fragment_of(node)
  // 592:           .source_position_of source_position_of(node)
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
  // 589: ... list(node)
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
  // 591: ... fragment_of(node)
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
  // 592: ... source_position_of(node)
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
  // 587: !node
  // 588:   function_call
  // 589:     .arguments_of list(node)
  // 590:     .is_an_attribute_access true
  // 591:     .fragment_of fragment_of(node)
  // 592:     .source_position_of source_position_of(node)
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
  // 598: span(functor_of IDENTIFIER)
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
  temp__1 = arguments->slots[0];
  // 594: $ATTRIBUTE_ACCESS
  // 595:   sequence
  // 596:     '.'
  // 597:     MAKE_ATTRIBUTE_ACCESS
  // 598:     span(functor_of IDENTIFIER)
  // 599:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = var._MAKE_ATTRIBUTE_ACCESS;
  arguments->slots[2] = temp__1;
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
  // 605: span(functor_of NAME_OF_POLYMORPHIC)
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
  temp__1 = arguments->slots[0];
  // 601: $ATTRIBUTE_WRITE
  // 602:   sequence
  // 603:     '.'
  // 604:     MAKE_ATTRIBUTE_ACCESS
  // 605:     span(functor_of NAME_OF_POLYMORPHIC)
  // 606:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = var._MAKE_ATTRIBUTE_ACCESS;
  arguments->slots[2] = temp__1;
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
  // 608: ... alt(FUNCTION_CALL ATTRIBUTE_ACCESS)
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
  temp__1 = arguments->slots[0];
  // 608: $EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_ACCESS))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 609: ... alt(FUNCTION_CALL ATTRIBUTE_WRITE)
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
  temp__1 = arguments->slots[0];
  // 609: $READ_WRITE_EXTENSIONS some(alt(FUNCTION_CALL ATTRIBUTE_WRITE))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 610: $IDENTIFIER_OR_FUNCTION_CALL IDENTIFIER, EXTENSIONS
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
  // 613: ... set_field(is_a_destination true)
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
  temp__1 = arguments->slots[0];
  // 612: $READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL
  // 613:   IDENTIFIER, set_field(is_a_destination true), READ_WRITE_EXTENSIONS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER;
  arguments->slots[1] = temp__1;
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
  // 617: ... many(DIGIT)
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
  temp__2 = arguments->slots[0];
  // 617: interleaved(many(DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 618: ... many(DIGIT)
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
  temp__5 = arguments->slots[0];
  // 618: ... '.', many(DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = temp__5;
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
  temp__4 = arguments->slots[0];
  // 618: optional('.', many(DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 619: ... alt('e' 'E')
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
  temp__8 = arguments->slots[0];
  // 619: ... alt('+' '-')
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
  temp__10 = arguments->slots[0];
  // 619: ... optional(alt('+' '-'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__10;
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
  temp__9 = arguments->slots[0];
  // 619: ... many(DIGIT)
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
  temp__11 = arguments->slots[0];
  // 619: ... alt('e' 'E'), optional(alt('+' '-')), many(DIGIT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__8;
  arguments->slots[1] = temp__9;
  arguments->slots[2] = temp__11;
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
  temp__7 = arguments->slots[0];
  // 619: optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__7;
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
  temp__6 = arguments->slots[0];
  // 615: $DECIMAL_NUMBER
  // 616:   sequence
  // 617:     interleaved(many(DIGIT) '@apos;')
  // 618:     optional('.', many(DIGIT))
  // 619:     optional(alt('e' 'E'), optional(alt('+' '-')), many(DIGIT))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__3;
  arguments->slots[2] = temp__6;
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
  // 621: $BINARY_DIGIT alt('0' '1')
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
  // 622: ... many(BINARY_DIGIT)
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
  temp__2 = arguments->slots[0];
  // 622: ... interleaved(many(BINARY_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 622: $BINARY_NUMBER "0b", interleaved(many(BINARY_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__300_3;
  arguments->slots[1] = temp__1;
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
  // 623: $OCTAL_DIGIT '0' .. '7'
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
  // 624: ... many(OCTAL_DIGIT)
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
  temp__2 = arguments->slots[0];
  // 624: ... interleaved(many(OCTAL_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 624: $OCTAL_NUMBER "0o", interleaved(many(OCTAL_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__302_3;
  arguments->slots[1] = temp__1;
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
  // 625: ... 'a' .. 'f'
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
  temp__1 = arguments->slots[0];
  // 625: ... 'A' .. 'F'
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
  temp__2 = arguments->slots[0];
  // 625: $HEX_DIGIT alt(DIGIT 'a' .. 'f' 'A' .. 'F')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__2;
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
  // 626: ... many(HEX_DIGIT)
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
  temp__2 = arguments->slots[0];
  // 626: ... interleaved(many(HEX_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 626: $HEX_NUMBER "0x", interleaved(many(HEX_DIGIT) '@apos;')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__304_3;
  arguments->slots[1] = temp__1;
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
  // 630: set_node(numeric_literal)
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
  temp__1 = arguments->slots[0];
  // 634: alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
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
  temp__3 = arguments->slots[0];
  // 632: capture
  // 633:   node::value_of
  // 634:   alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 628: $NUMBER
  // 629:   sequence
  // 630:     set_node(numeric_literal)
  // 631:     STORE_POSITION
  // 632:     capture
  // 633:       node::value_of
  // 634:       alt(HEX_NUMBER OCTAL_NUMBER BINARY_NUMBER DECIMAL_NUMBER)
  // 635:     STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = temp__2;
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
  // 639: capture(node::value_of PRINTABLE_CHARACTER)
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
  temp__1 = arguments->slots[0];
  // 640: modify_node
  // 641:   : (&node)
  // 642:     !node.node::value_of node::value_of(node)(1)
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
  // 642: ... node::value_of(node)
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
  // 642: !node.node::value_of node::value_of(node)(1)
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
  // 642: !node.node::value_of
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
  temp__2 = arguments->slots[0];
  // 637: $SIMPLE_CHARACTER
  // 638:   sequence
  // 639:     capture(node::value_of PRINTABLE_CHARACTER)
  // 640:     modify_node
  // 641:       : (&node)
  // 642:         !node.node::value_of node::value_of(node)(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
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
  // 647: modify_node
  // 648:   : (&node)
  // 649:     !node.node::value_of '@@'
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
  // 649: !node.node::value_of '@@'
  frame->slots[1] /* temp__1 */ = character__64;
  // 649: !node.node::value_of
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
  temp__1 = arguments->slots[0];
  // 644: $AT_CHARACTER
  // 645:   sequence
  // 646:     '@@'
  // 647:     modify_node
  // 648:       : (&node)
  // 649:         !node.node::value_of '@@'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__64;
  arguments->slots[1] = temp__1;
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
  // 653: capture(node::value_of NAME)
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
  temp__1 = arguments->slots[0];
  // 655: modify_node
  // 656:   :
  // 657:     (
  // 658:       &node
  // 659:       stream
  // 660:     )
  // 661:     $chr character_names(node::value_of(node))
  // 662:     unless chr.is_defined: ParseError stream "invalid character name"
  // 663:     !node.node::value_of chr
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
  // 661: ... node::value_of(node)
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
  // 661: $chr character_names(node::value_of(node))
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
  // 662: ... chr.is_defined
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
  // 662: ... : ParseError stream "invalid character name"
  frame->slots[4] /* temp__2 */ = create_closure(entry__308_6, 0);
  // 662: unless chr.is_defined: ParseError stream "invalid character name"
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
  // 662: ... ParseError stream "invalid character name"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__308_7;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__308_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: !node.node::value_of chr
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* chr */;
  // 663: !node.node::value_of
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
  temp__2 = arguments->slots[0];
  // 651: $NAMED_CHARACTER
  // 652:   sequence
  // 653:     capture(node::value_of NAME)
  // 654:     ';'
  // 655:     modify_node
  // 656:       :
  // 657:         (
  // 658:           &node
  // 659:           stream
  // 660:         )
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = character__59;
  arguments->slots[2] = temp__2;
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
  // 670: ... many(BINARY_DIGIT)
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
  temp__4 = arguments->slots[0];
  // 670: "0b", many(BINARY_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__309_2;
  arguments->slots[1] = temp__4;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__309_3;
}
static void cont__309_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 671: ... many(OCTAL_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OCTAL_DIGIT;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__309_4;
}
static void cont__309_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 671: "0o", many(OCTAL_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__309_5;
  arguments->slots[1] = temp__6;
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
  temp__5 = arguments->slots[0];
  // 672: ... many(HEX_DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._HEX_DIGIT;
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
  temp__8 = arguments->slots[0];
  // 672: "0x", many(HEX_DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__309_8;
  arguments->slots[1] = temp__8;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__309_9;
}
static void cont__309_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 673: many(DIGIT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__DIGIT();
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__309_10;
}
static void cont__309_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__9 = arguments->slots[0];
  // 669: alt
  // 670:   "0b", many(BINARY_DIGIT)
  // 671:   "0o", many(OCTAL_DIGIT)
  // 672:   "0x", many(HEX_DIGIT)
  // 673:   many(DIGIT)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  arguments->slots[1] = temp__5;
  arguments->slots[2] = temp__7;
  arguments->slots[3] = temp__9;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__309_11;
}
static void cont__309_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 667: capture
  // 668:   node::value_of
  // 669:   alt
  // 670:     "0b", many(BINARY_DIGIT)
  // 671:     "0o", many(OCTAL_DIGIT)
  // 672:     "0x", many(HEX_DIGIT)
  // 673:     many(DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__value_of();
  arguments->slots[1] = temp__2;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__309_12;
}
static void cont__309_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 675: modify_node
  // 676:   : (&node)
  // 677:     !node.node::value_of character(node::value_of(node).to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__309_13;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__309_17;
}
static void entry__309_13(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 677: ... node::value_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* node */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__309_14;
}
static void cont__309_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 677: ... node::value_of(node).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__309_15;
}
static void cont__309_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 677: !node.node::value_of character(node::value_of(node).to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__character();
  func = myself->type;
  frame->cont = cont__309_16;
}
static void cont__309_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 677: !node.node::value_of
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
static void cont__309_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__10 = arguments->slots[0];
  // 665: $NUMERIC_CHARACTER
  // 666:   sequence
  // 667:     capture
  // 668:       node::value_of
  // 669:       alt
  // 670:         "0b", many(BINARY_DIGIT)
  // 671:         "0o", many(OCTAL_DIGIT)
  // 672:         "0x", many(HEX_DIGIT)
  // 673:         many(DIGIT)
  // 674:     ';'
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = character__59;
  arguments->slots[2] = temp__10;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__309_18;
}
static void cont__309_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NUMERIC_CHARACTER, arguments->slots[0]);
  // 684: syntax_error("invalid special character")
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
  temp__1 = arguments->slots[0];
  // 679: $SPECIAL_CHARACTER
  // 680:   alt
  // 681:     AT_CHARACTER
  // 682:     NAMED_CHARACTER
  // 683:     NUMERIC_CHARACTER
  // 684:     syntax_error("invalid special character")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._AT_CHARACTER;
  arguments->slots[1] = var._NAMED_CHARACTER;
  arguments->slots[2] = var._NUMERIC_CHARACTER;
  arguments->slots[3] = temp__1;
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
  // 686: ... '@@', SPECIAL_CHARACTER
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
  temp__1 = arguments->slots[0];
  // 686: $CHARACTER_SYMBOL alt('@@', SPECIAL_CHARACTER SIMPLE_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 691: set_node(character_literal)
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
  temp__1 = arguments->slots[0];
  // 694: expect('@apos;')
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
  temp__2 = arguments->slots[0];
  // 688: $CHARACTER
  // 689:   sequence
  // 690:     '@apos;'
  // 691:     set_node(character_literal)
  // 692:     STORE_POSITION_MINUS_1
  // 693:     CHARACTER_SYMBOL
  // 694:     expect('@apos;')
  // 695:     STORE_END_POSITION
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = character__39;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = var._CHARACTER_SYMBOL;
  arguments->slots[4] = temp__2;
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
  // 702: modify_node
  // 703:   : (&node)
  // 704:     push &node.node::text_of node::value_of(node)
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
  // 704: ... node.node::text_of
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
  // 704: ... node::value_of(node)
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
  // 704: push &node.node::text_of node::value_of(node)
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
  // 704: ... &node.node::text_of
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
  temp__2 = arguments->slots[0];
  // 700: sequence
  // 701:   CHARACTER_SYMBOL
  // 702:   modify_node
  // 703:     : (&node)
  // 704:       push &node.node::text_of node::value_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._CHARACTER_SYMBOL;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 697: $STRING_CHARACTER
  // 698:   alt
  // 699:     "@@;"
  // 700:     sequence
  // 701:       CHARACTER_SYMBOL
  // 702:       modify_node
  // 703:         : (&node)
  // 704:           push &node.node::text_of node::value_of(node)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__313_7;
  arguments->slots[1] = temp__1;
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
  // 709: modify_node
  // 710:   : (&node)
  // 711:     if node::text_of(node) != "":
  // 712:       push &node.arguments_of node(.arguments_of undefined)
  // 713:     !node.node::text_of ""
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
  // 711: ... node::text_of(node)
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
  // 711: ... node::text_of(node) != ""
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
  // 711: ... node::text_of(node) != ""
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
  // 711: ... :
  // 712:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__314_5, 0);
  // 711: if node::text_of(node) != "":
  // 712:   push &node.arguments_of node(.arguments_of undefined)
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
  // 712: ... node.arguments_of
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
  // 712: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 712: push &node.arguments_of node(.arguments_of undefined)
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
  // 712: ... &node.arguments_of
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
  // 713: !node.node::text_of ""
  frame->slots[1] /* temp__1 */ = empty_string;
  // 713: !node.node::text_of
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
  temp__1 = arguments->slots[0];
  // 714: ... arguments_span(EXPRESSION)
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
  temp__3 = arguments->slots[0];
  // 714: interleaved(arguments_span(EXPRESSION) sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 715: expect(')')
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
  temp__4 = arguments->slots[0];
  // 706: $STRING_INSERTION
  // 707:   sequence
  // 708:     "@@("
  // 709:     modify_node
  // 710:       : (&node)
  // 711:         if node::text_of(node) != "":
  // 712:           push &node.arguments_of node(.arguments_of undefined)
  // 713:         !node.node::text_of ""
  // 714:     interleaved(arguments_span(EXPRESSION) sim2c::WHITESPACE)
  // 715:     expect(')')
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__314_13;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__2;
  arguments->slots[3] = temp__4;
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
  // 717: $CHECK_INSERTIONS
  // 718:   modify_node
  // 719:     : (&node)
  // 720:       if length_of(arguments_of(node)) > 0:
  // 721:         if node::text_of(node) != "":
  // 722:           push &node.arguments_of node(.arguments_of undefined)
  // 723:         !node
  // 724:           function_call
  // 725:             .functor_of std_identifier("string")
  // 726:             .arguments_of arguments_of(node)
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
  // 720: ... arguments_of(node)
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
  // 720: ... length_of(arguments_of(node))
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
  // 720: ... length_of(arguments_of(node)) > 0
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
  // 720: ... :
  // 721:   if node::text_of(node) != "":
  // 722:     push &node.arguments_of node(.arguments_of undefined)
  // 723:   !node
  // 724:     function_call
  // 725:       .functor_of std_identifier("string")
  // 726:       .arguments_of arguments_of(node)
  // 727:       .is_a_string_template true
  // 728:       .fragment_of fragment_of(node)
  // 729:       .source_position_of source_position_of(node)
  // ...
  frame->slots[4] /* temp__4 */ = create_closure(entry__315_5, 0);
  // 720: if length_of(arguments_of(node)) > 0:
  // 721:   if node::text_of(node) != "":
  // 722:     push &node.arguments_of node(.arguments_of undefined)
  // 723:   !node
  // 724:     function_call
  // 725:       .functor_of std_identifier("string")
  // 726:       .arguments_of arguments_of(node)
  // 727:       .is_a_string_template true
  // 728:       .fragment_of fragment_of(node)
  // 729:       .source_position_of source_position_of(node)
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
  // 721: ... node::text_of(node)
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
  // 721: ... node::text_of(node) != ""
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
  // 721: ... node::text_of(node) != ""
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
  // 721: ... :
  // 722:   push &node.arguments_of node(.arguments_of undefined)
  frame->slots[4] /* temp__4 */ = create_closure(entry__315_9, 0);
  // 721: if node::text_of(node) != "":
  // 722:   push &node.arguments_of node(.arguments_of undefined)
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
  // 722: ... node.arguments_of
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
  // 722: ... node(.arguments_of undefined)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, get__undefined());
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 722: push &node.arguments_of node(.arguments_of undefined)
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
  // 722: ... &node.arguments_of
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
  // 725: ... std_identifier("string")
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
  // 726: ... arguments_of(node)
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
  // 728: ... fragment_of(node)
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
  // 729: ... source_position_of(node)
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
  // 730: ... end_position_of(node)
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
  // 723: !node
  // 724:   function_call
  // 725:     .functor_of std_identifier("string")
  // 726:     .arguments_of arguments_of(node)
  // 727:     .is_a_string_template true
  // 728:     .fragment_of fragment_of(node)
  // 729:     .source_position_of source_position_of(node)
  // 730:     .end_position_of end_position_of(node)
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
  // 737: set_node(string_literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__string_literal();
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
  temp__1 = arguments->slots[0];
  // 739: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__316_2;
}
static void cont__316_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 739: ... alt(STRING_INSERTION STRING_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STRING_INSERTION;
  arguments->slots[1] = var._STRING_CHARACTER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__316_3;
}
static void cont__316_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 739: ... not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = temp__5;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__316_4;
}
static void cont__316_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 739: some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__316_5;
}
static void cont__316_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 732: $STRING
  // 733:   # This code has an astonishing capability to flatten template expressions!
  // 734:   
  // 735:   sequence
  // 736:     '@quot;'
  // 737:     set_node(string_literal)
  // 738:     STORE_POSITION_MINUS_1
  // 739:     some(not_followed_by('@quot;'), alt(STRING_INSERTION STRING_CHARACTER))
  // 740:     '@quot;'
  // 741:     STORE_END_POSITION
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = character__34;
  arguments->slots[5] = var._STORE_END_POSITION;
  arguments->slots[6] = var._CHECK_INSERTIONS;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__316_6;
}
static void cont__316_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STRING, arguments->slots[0]);
  // 747: ... '@@', OUTDENT
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
  temp__3 = arguments->slots[0];
  // 747: followed_by('@@', OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 748: '@@', NEWLINE, STRING_LINE
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
  temp__4 = arguments->slots[0];
  // 749: STRING_INSERTION, STRING_LINE
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
  temp__5 = arguments->slots[0];
  // 750: STRING_CHARACTER, STRING_LINE
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
  temp__6 = arguments->slots[0];
  // 746: alt
  // 747:   followed_by('@@', OUTDENT)
  // 748:   '@@', NEWLINE, STRING_LINE
  // 749:   STRING_INSERTION, STRING_LINE
  // 750:   STRING_CHARACTER, STRING_LINE
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = temp__4;
  arguments->slots[2] = temp__5;
  arguments->slots[3] = temp__6;
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
  temp__1 = arguments->slots[0];
  // 744: $STRING_LINE
  // 745:   optional
  // 746:     alt
  // 747:       followed_by('@@', OUTDENT)
  // 748:       '@@', NEWLINE, STRING_LINE
  // 749:       STRING_INSERTION, STRING_LINE
  // 750:       STRING_CHARACTER, STRING_LINE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 752: $ADD_LINE_END
  // 753:   modify_node
  // 754:     : (&node)
  // 755:       append &node.node::text_of line_end_specifier_of(node)
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
  // 755: ... node.node::text_of
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
  // 755: ... line_end_specifier_of(node)
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
  // 755: append &node.node::text_of line_end_specifier_of(node)
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
  // 755: ... &node.node::text_of
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
  // 760: set_node(multi_line_string)
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
  temp__1 = arguments->slots[0];
  // 764: ... NEWLINE, ADD_LINE_END, STRING_LINE
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
  temp__3 = arguments->slots[0];
  // 764: some(NEWLINE, ADD_LINE_END, STRING_LINE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 765: ... '@@', OUTDENT
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
  temp__5 = arguments->slots[0];
  // 765: ... expect(outdent_marker)
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
  temp__7 = arguments->slots[0];
  // 765: ... expect(outdent_marker), ADD_LINE_END
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__7;
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
  temp__6 = arguments->slots[0];
  // 765: alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__5;
  arguments->slots[1] = temp__6;
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
  temp__4 = arguments->slots[0];
  // 757: $MULTI_LINE_STRING
  // 758:   sequence
  // 759:     '@quot;'
  // 760:     set_node(multi_line_string)
  // 761:     STORE_POSITION_MINUS_1
  // 762:     INDENT
  // 763:     STRING_LINE
  // 764:     some(NEWLINE, ADD_LINE_END, STRING_LINE)
  // 765:     alt('@@', OUTDENT expect(outdent_marker), ADD_LINE_END)
  // 766:     STORE_END_POSITION
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = var._INDENT;
  arguments->slots[4] = var._STRING_LINE;
  arguments->slots[5] = temp__2;
  arguments->slots[6] = temp__4;
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
  // 769: ... not_followed_by(LETTER)
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
  temp__1 = arguments->slots[0];
  // 769: ... set_node(unique_item)
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
  temp__2 = arguments->slots[0];
  // 769: $UNIQUE_ITEM '.', not_followed_by(LETTER), set_node(unique_item)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__2;
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
  // 774: ... syntax_error("expression expected")
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
  temp__3 = arguments->slots[0];
  // 774: ... alt(EXPRESSION BODY syntax_error("expression expected"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = var._BODY;
  arguments->slots[2] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 774: inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 775: expect(')')
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
  temp__4 = arguments->slots[0];
  // 771: $PARENTHESED_EXPRESSION
  // 772:   sequence
  // 773:     '('
  // 774:     inline(alt(EXPRESSION BODY syntax_error("expression expected")))
  // 775:     expect(')')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__4;
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
  // 781: modify_node
  // 782:   : (node)
  // 783:     ->
  // 784:       function_call
  // 785:         .functor_of std_identifier("key_value_pair")
  // 786:         .arguments_of list(node std_identifier("true"))
  // 787:         .fragment_of fragment_of(node)
  // 788:         .source_position_of source_position_of(node)+2
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
  // 785: ... std_identifier("key_value_pair")
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
  // 786: ... std_identifier("true")
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
  // 786: ... list(node std_identifier("true"))
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
  // 787: ... fragment_of(node)
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
  // 788: ... source_position_of(node)
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
  // 788: ... source_position_of(node)+2
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
  // 784: function_call
  // 785:   .functor_of std_identifier("key_value_pair")
  // 786:   .arguments_of list(node std_identifier("true"))
  // 787:   .fragment_of fragment_of(node)
  // 788:   .source_position_of source_position_of(node)+2
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__6 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 783: ->
  // 784:   function_call
  // 785:     .functor_of std_identifier("key_value_pair")
  // 786:     .arguments_of list(node std_identifier("true"))
  // 787:     .fragment_of fragment_of(node)
  // 788:     .source_position_of source_position_of(node)+2
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
  temp__1 = arguments->slots[0];
  // 777: $OPTION
  // 778:   sequence
  // 779:     "--"
  // 780:     IDENTIFIER
  // 781:     modify_node
  // 782:       : (node)
  // 783:         ->
  // 784:           function_call
  // 785:             .functor_of std_identifier("key_value_pair")
  // 786:             .arguments_of list(node std_identifier("true"))
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__322_11;
  arguments->slots[1] = var._IDENTIFIER;
  arguments->slots[2] = temp__1;
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
  // 796: modify_node
  // 797:   : (node)
  // 798:     ->
  // 799:       function_call
  // 800:         .functor_of operator_symbol(.name_of "-")
  // 801:         .arguments_of list(node)
  // 802:         .fragment_of fragment_of(node)
  // 803:         .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__323_1;
  result_count = 1;
  myself = get__modify_node();
  func = myself->type;
  frame->cont = cont__323_6;
}
static void entry__323_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 800: ... operator_symbol(.name_of "-")
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, string__323_2);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 801: ... list(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__323_3;
}
static void cont__323_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 802: ... fragment_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__323_4;
}
static void cont__323_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 803: ... source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__323_5;
}
static void cont__323_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 799: function_call
  // 800:   .functor_of operator_symbol(.name_of "-")
  // 801:   .arguments_of list(node)
  // 802:   .fragment_of fragment_of(node)
  // 803:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[4] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[5] /* temp__5 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 798: ->
  // 799:   function_call
  // 800:     .functor_of operator_symbol(.name_of "-")
  // 801:     .arguments_of list(node)
  // 802:     .fragment_of fragment_of(node)
  // 803:     .source_position_of source_position_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__323_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 791: $NEGATION
  // 792:   sequence
  // 793:     '-'
  // 794:     STORE_POSITION_MINUS_1
  // 795:     OPERAND
  // 796:     modify_node
  // 797:       : (node)
  // 798:         ->
  // 799:           function_call
  // 800:             .functor_of operator_symbol(.name_of "-")
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = var._STORE_POSITION_MINUS_1;
  arguments->slots[2] = var._OPERAND;
  arguments->slots[3] = temp__1;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__323_7;
}
static void cont__323_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NEGATION, arguments->slots[0]);
  // 806: $SIMPLE_OPERAND
  // 807:   alt(NUMBER CHARACTER STRING UNIQUE_ITEM PARENTHESED_EXPRESSION OPTION NEGATION)
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
  // 809: ... some(ATTRIBUTE_ACCESS)
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
  temp__2 = arguments->slots[0];
  // 809: ... SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMPLE_OPERAND;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 809: $OPERAND alt(IDENTIFIER_OR_FUNCTION_CALL SIMPLE_OPERAND, some(ATTRIBUTE_ACCESS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[1] = temp__1;
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
  // 811: $INFIX_OPERATOR_SYMBOL
  // 812:   alt
  // 813:     '*'
  // 814:     '/'
  // 815:     '+'
  // 816:     '-'
  // 817:     "<<"
  // 818:     "<="
  // 819:     "<"
  // 820:     ">>"
  // ...
  argument_count = 19;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__47;
  arguments->slots[2] = character__43;
  arguments->slots[3] = character__45;
  arguments->slots[4] = string__326_1;
  arguments->slots[5] = string__326_2;
  arguments->slots[6] = string__326_3;
  arguments->slots[7] = string__326_4;
  arguments->slots[8] = string__326_5;
  arguments->slots[9] = string__326_6;
  arguments->slots[10] = string__326_7;
  arguments->slots[11] = character__38;
  arguments->slots[12] = character__94;
  arguments->slots[13] = string__326_8;
  arguments->slots[14] = character__124;
  arguments->slots[15] = string__326_9;
  arguments->slots[16] = character__61;
  arguments->slots[17] = string__326_10;
  arguments->slots[18] = string__326_11;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__326_12;
}
static void cont__326_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INFIX_OPERATOR_SYMBOL, arguments->slots[0]);
  // 834: ... multi_capture(operators_of INFIX_OPERATOR_SYMBOL)
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
  temp__1 = arguments->slots[0];
  // 833: $SYMBOLIC_OPERATOR
  // 834:   infix_operator(multi_capture(operators_of INFIX_OPERATOR_SYMBOL))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 836: ... multi_capture(operators_of ',')
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
  temp__1 = arguments->slots[0];
  // 836: $COMMA_OPERATOR multi_capture(operators_of ','), sim2c::WHITESPACE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 842: multi_span(operators_of IDENTIFIER)
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
  temp__1 = arguments->slots[0];
  // 844: expect(sim2c::WHITESPACE)
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
  temp__2 = arguments->slots[0];
  // 838: $NAMED_OPERATOR
  // 839:   sequence
  // 840:     sim2c::WHITESPACE
  // 841:     '.'
  // 842:     multi_span(operators_of IDENTIFIER)
  // 843:     '.'
  // 844:     expect(sim2c::WHITESPACE)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = character__46;
  arguments->slots[2] = temp__1;
  arguments->slots[3] = character__46;
  arguments->slots[4] = temp__2;
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
  // 848: alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
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
  temp__1 = arguments->slots[0];
  // 849: modify_node
  // 850:   : (&node)
  // 851:     $operator_precedence precedence(operators_of(node)(-1))
  // 852:     $lowest_precedence lowest_precedence_of(node)
  // 853:     if
  // 854:       ||
  // 855:         lowest_precedence.is_undefined
  // 856:         operator_precedence < lowest_precedence
  // 857:       :
  // 858:         !node.lowest_precedence_of operator_precedence
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
  // 851: ... 1
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
  // 851: ... operators_of(node)
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
  // 851: ... operators_of(node)(-1)
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
  // 851: $operator_precedence precedence(operators_of(node)(-1))
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
  // 852: $lowest_precedence lowest_precedence_of(node)
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
  // 855: lowest_precedence.is_undefined
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
  // 856: operator_precedence < lowest_precedence
  frame->slots[5] /* temp__3 */ = create_closure(entry__330_9, 0);
  // 854: ||
  // 855:   lowest_precedence.is_undefined
  // 856:   operator_precedence < lowest_precedence
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
  // 856: operator_precedence < lowest_precedence
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
  // 856: operator_precedence < lowest_precedence
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
  // 857: :
  // 858:   !node.lowest_precedence_of operator_precedence
  frame->slots[6] /* temp__4 */ = create_closure(entry__330_12, 0);
  // 853: if
  // 854:   ||
  // 855:     lowest_precedence.is_undefined
  // 856:     operator_precedence < lowest_precedence
  // 857:   :
  // 858:     !node.lowest_precedence_of operator_precedence
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
  // 858: !node.lowest_precedence_of operator_precedence
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* operator_precedence */;
  // 858: !node.lowest_precedence_of
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
  temp__2 = arguments->slots[0];
  // 846: $INFIX_OPERATOR
  // 847:   sequence
  // 848:     alt(SYMBOLIC_OPERATOR COMMA_OPERATOR NAMED_OPERATOR)
  // 849:     modify_node
  // 850:       : (&node)
  // 851:         $operator_precedence precedence(operators_of(node)(-1))
  // 852:         $lowest_precedence lowest_precedence_of(node)
  // 853:         if
  // 854:           ||
  // 855:             lowest_precedence.is_undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
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
  // 860: $EXTEND_EXPRESSION
  // 861:   modify_node
  // 862:     : (&node)
  // 863:       $parent parent_of(node)
  // 864:       $arguments arguments_of(node)
  // 865:       $n length_of(arguments)
  // 866:       if
  // 867:         n == 1:
  // 868:           !node arguments(1)
  // 869:         : # build syntax tree according to operator precedences
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
  // 863: $parent parent_of(node)
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
  // 864: $arguments arguments_of(node)
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
  // 865: $n length_of(arguments)
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
  // 867: n == 1
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
  // 867: ... :
  // 868:   !node arguments(1)
  frame->slots[5] /* temp__2 */ = create_closure(entry__331_6, 0);
  // 869: : # build syntax tree according to operator precedences
  // 870:   $operators operators_of(node)
  // 871:   $$operand_stack list(arguments(1))
  // 872:   $$operator_stack list(operators(1))
  // 873:   
  // 874:   $update_stack: ($right next_operator)
  // 875:     $next_prec
  // 876:       if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 877:     
  // 878:     do: (-> break)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__331_8, 0);
  // 866: if
  // 867:   n == 1:
  // 868:     !node arguments(1)
  // 869:   : # build syntax tree according to operator precedences
  // 870:     $operators operators_of(node)
  // 871:     $$operand_stack list(arguments(1))
  // 872:     $$operator_stack list(operators(1))
  // 873:     
  // 874:     $update_stack: ($right next_operator)
  // 875:       $next_prec
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
  // 868: !node arguments(1)
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
  // 874: ... : ($right next_operator)
  // 875:   $next_prec
  // 876:     if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 877:   
  // 878:   do: (-> break)
  // 879:     forever:
  // 880:       $operator peek(operator_stack)
  // 881:       $prec precedence(operator)
  // 882:       if next_prec > prec break
  // 883:       if next_prec == prec && is_right_associative(prec) break
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__331_9, 2);
  // 874: $update_stack: ($right next_operator)
  // 875:   $next_prec
  // 876:     if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
  // 877:   
  // 878:   do: (-> break)
  // 879:     forever:
  // 880:       $operator peek(operator_stack)
  // 881:       $prec precedence(operator)
  // 882:       if next_prec > prec break
  // 883:       if next_prec == prec && is_right_associative(prec) break
  // ...
  initialize_future(frame->slots[6] /* update_stack */, frame->slots[7] /* temp__1 */);
  // 870: $operators operators_of(node)
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
  // 876: ... next_operator.is_defined
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
  // 876: ... -> precedence(next_operator)
  frame->slots[6] /* temp__2 */ = create_closure(entry__331_11, 0);
  // 875: $next_prec
  // 876:   if(next_operator.is_defined (-> precedence(next_operator)) -> 0)
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
  // 876: ... precedence(next_operator)
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
  // 876: ... -> precedence(next_operator)
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
  // 876: ... -> 0
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
  // 878: ... : (-> break)
  // 879:   forever:
  // 880:     $operator peek(operator_stack)
  // 881:     $prec precedence(operator)
  // 882:     if next_prec > prec break
  // 883:     if next_prec == prec && is_right_associative(prec) break
  // 884:     
  // 885:     $functor
  // 886:       if
  // 887:         operator.is_a_string
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__331_15, 0);
  // 878: do: (-> break)
  // 879:   forever:
  // 880:     $operator peek(operator_stack)
  // 881:     $prec precedence(operator)
  // 882:     if next_prec > prec break
  // 883:     if next_prec == prec && is_right_associative(prec) break
  // 884:     
  // 885:     $functor
  // 886:       if
  // 887:         operator.is_a_string
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
  // 879: ... :
  // 880:   $operator peek(operator_stack)
  // 881:   $prec precedence(operator)
  // 882:   if next_prec > prec break
  // 883:   if next_prec == prec && is_right_associative(prec) break
  // 884:   
  // 885:   $functor
  // 886:     if
  // 887:       operator.is_a_string
  // 888:       -> operator_symbol(.name_of operator)
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__331_16, 0);
  // 879: forever:
  // 880:   $operator peek(operator_stack)
  // 881:   $prec precedence(operator)
  // 882:   if next_prec > prec break
  // 883:   if next_prec == prec && is_right_associative(prec) break
  // 884:   
  // 885:   $functor
  // 886:     if
  // 887:       operator.is_a_string
  // 888:       -> operator_symbol(.name_of operator)
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
  // 880: $operator peek(operator_stack)
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
  // 881: $prec precedence(operator)
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
  // 882: ... next_prec > prec
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
  // 882: if next_prec > prec break
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
  // 883: ... next_prec == prec
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
  // 883: ... is_right_associative(prec)
  frame->slots[12] /* temp__3 */ = create_closure(entry__331_22, 0);
  // 883: ... next_prec == prec && is_right_associative(prec)
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
  // 883: ... is_right_associative(prec)
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
  // 883: ... is_right_associative(prec)
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
  // 883: if next_prec == prec && is_right_associative(prec) break
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
  // 887: operator.is_a_string
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
  // 888: -> operator_symbol(.name_of operator)
  frame->slots[11] /* temp__2 */ = create_closure(entry__331_27, 0);
  // 889: -> operator
  frame->slots[12] /* temp__3 */ = create_closure(entry__331_28, 0);
  // 885: $functor
  // 886:   if
  // 887:     operator.is_a_string
  // 888:     -> operator_symbol(.name_of operator)
  // 889:     -> operator
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
  // 888: ... operator_symbol(.name_of operator)
  {
    NODE *temp = clone_object_and_attributes(get__operator_symbol());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[0] /* operator */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 888: -> operator_symbol(.name_of operator)
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
  // 889: -> operator
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
  // 891: $left pop(&operand_stack)
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
  // 891: ... left
  initialize_future(frame->slots[8] /* left */, frame->slots[10] /* temp__1 */);
  // 895: ... list(left right)
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
  // 897: ... enumeration_no_of(left)
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
  // 898: ... fragment_of(left)
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
  // 899: ... source_position_of(left)
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
  // 900: ... end_position_of(right)
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
  // 892: !right
  // 893:   function_call
  // 894:     .functor_of functor
  // 895:     .arguments_of list(left right)
  // 896:     .is_in_infix_notation true
  // 897:     .enumeration_no_of enumeration_no_of(left)
  // 898:     .fragment_of fragment_of(left)
  // 899:     .source_position_of source_position_of(left)
  // 900:     .end_position_of end_position_of(right)
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
  // 901: pop &operator_stack $_dummy
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
  // 901: ... _dummy
  initialize_future(frame->slots[9] /* dummy */, frame->slots[10] /* temp__1 */);
  // 902: ... length_of(operator_stack)
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
  // 902: ... length_of(operator_stack) == 0
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
  // 902: if length_of(operator_stack) == 0 break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 903: push &operand_stack right
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
  // 904: push &operator_stack next_operator
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
  // 871: ... arguments(1)
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
  // 871: $$operand_stack list(arguments(1))
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
  // 872: ... operators(1)
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
  // 872: $$operator_stack list(operators(1))
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
  // 906: ... : (i)
  // 907:   update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
  frame->slots[7] /* temp__1 */ = create_closure(entry__331_48, 1);
  // 906: from_to 2 n: (i)
  // 907:   update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
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
  // 907: ... arguments(i)
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
  // 907: ... i < n
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
  // 907: ... -> operators(i)
  frame->slots[8] /* temp__4 */ = create_closure(entry__331_51, 0);
  // 907: ... if(i < n (-> operators(i)) -> undefined)
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
  // 907: ... operators(i)
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
  // 907: ... -> operators(i)
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
  // 907: ... -> undefined
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
  // 907: update_stack arguments(i) if(i < n (-> operators(i)) -> undefined)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* update_stack */;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__331_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 908: !node peek(operand_stack)
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
  // 909: ... parent.is_defined
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
  // 909: ... :
  // 910:   !node parent(.arguments_of push(arguments_of(parent) node))
  frame->slots[5] /* temp__2 */ = create_closure(entry__331_59, 0);
  // 909: if parent.is_defined:
  // 910:   !node parent(.arguments_of push(arguments_of(parent) node))
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
  // 910: ... arguments_of(parent)
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
  // 910: ... push(arguments_of(parent) node)
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
  // 910: !node parent(.arguments_of push(arguments_of(parent) node))
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
  // 914: set_node(expression)
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
  temp__1 = arguments->slots[0];
  // 915: arguments_span(OPERAND)
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
  temp__2 = arguments->slots[0];
  // 917: ... multi_capture(operators_of '=')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__operators_of();
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__332_3;
}
static void cont__332_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 917: infix_operator(multi_capture(operators_of '='))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__6;
  result_count = 1;
  myself = var._infix_operator;
  func = myself->type;
  frame->cont = cont__332_4;
}
static void cont__332_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 917: infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__5;
  arguments->slots[1] = var._LINE_END_EXPRESSION;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__332_5;
}
static void cont__332_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 918: ... arguments_span(OPERAND)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OPERAND;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__332_6;
}
static void cont__332_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__9 = arguments->slots[0];
  // 918: ... INFIX_OPERATOR, arguments_span(OPERAND)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._INFIX_OPERATOR;
  arguments->slots[1] = temp__9;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__332_7;
}
static void cont__332_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__8 = arguments->slots[0];
  // 918: some(INFIX_OPERATOR, arguments_span(OPERAND))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__8;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__332_8;
}
static void cont__332_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 916: alt
  // 917:   infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  // 918:   some(INFIX_OPERATOR, arguments_span(OPERAND))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = temp__7;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__332_9;
}
static void cont__332_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 912: $EXPRESSION
  // 913:   sequence
  // 914:     set_node(expression)
  // 915:     arguments_span(OPERAND)
  // 916:     alt
  // 917:       infix_operator(multi_capture(operators_of '=')), LINE_END_EXPRESSION
  // 918:       some(INFIX_OPERATOR, arguments_span(OPERAND))
  // 919:     EXTEND_EXPRESSION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = temp__3;
  arguments->slots[3] = var._EXTEND_EXPRESSION;
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
  // 921: ... span(identifier_of DEFINE_IDENTIFIER)
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
  temp__1 = arguments->slots[0];
  // 921: $DEFINED_VARIABLE expect(span(identifier_of DEFINE_IDENTIFIER) "identifier")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 924: ... set_field(is_used_as_a_polymorphic_function true)
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
  temp__1 = arguments->slots[0];
  // 923: $NAME_OF_POLYMORPHIC
  // 924:   IDENTIFIER, set_field(is_used_as_a_polymorphic_function true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER;
  arguments->slots[1] = temp__1;
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
  // 934: set_field(attribute_kind_of ATTRIBUTE_KIND)
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
  temp__5 = arguments->slots[0];
  // 935: span(attribute_of NAME_OF_POLYMORPHIC)
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
  temp__6 = arguments->slots[0];
  // 932: sequence
  // 933:   '.'
  // 934:   set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 935:   span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = temp__5;
  arguments->slots[2] = temp__6;
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
  temp__4 = arguments->slots[0];
  // 936: ... followed_by(':')
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
  temp__8 = arguments->slots[0];
  // 936: ... set_field(attribute_kind_of METHOD_KIND)
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
  temp__9 = arguments->slots[0];
  // 936: sequence('/' followed_by(':') set_field(attribute_kind_of METHOD_KIND))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = temp__8;
  arguments->slots[2] = temp__9;
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
  temp__7 = arguments->slots[0];
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
  temp__11 = arguments->slots[0];
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
  temp__12 = arguments->slots[0];
  // 937: sequence
  // 938:   '/'
  // 939:   set_field(attribute_kind_of METHOD_KIND)
  // 940:   span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = temp__11;
  arguments->slots[2] = temp__12;
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
  temp__10 = arguments->slots[0];
  // 931: alt
  // 932:   sequence
  // 933:     '.'
  // 934:     set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 935:     span(attribute_of NAME_OF_POLYMORPHIC)
  // 936:   sequence('/' followed_by(':') set_field(attribute_kind_of METHOD_KIND))
  // 937:   sequence
  // 938:     '/'
  // 939:     set_field(attribute_kind_of METHOD_KIND)
  // 940:     span(attribute_of NAME_OF_POLYMORPHIC)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = temp__7;
  arguments->slots[2] = temp__10;
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
  temp__3 = arguments->slots[0];
  // 930: sequence
  // 931:   alt
  // 932:     sequence
  // 933:       '.'
  // 934:       set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 935:       span(attribute_of NAME_OF_POLYMORPHIC)
  // 936:     sequence('/' followed_by(':') set_field(attribute_kind_of METHOD_KIND))
  // 937:     sequence
  // 938:       '/'
  // 939:       set_field(attribute_kind_of METHOD_KIND)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 929: optional
  // 930:   sequence
  // 931:     alt
  // 932:       sequence
  // 933:         '.'
  // 934:         set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 935:         span(attribute_of NAME_OF_POLYMORPHIC)
  // 936:       sequence('/' followed_by(':') set_field(attribute_kind_of METHOD_KIND))
  // 937:       sequence
  // 938:         '/'
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 926: $DEFINED_VARIABLE_OR_ATTRIBUTE
  // 927:   sequence
  // 928:     DEFINED_VARIABLE
  // 929:     optional
  // 930:       sequence
  // 931:         alt
  // 932:           sequence
  // 933:             '.'
  // 934:             set_field(attribute_kind_of ATTRIBUTE_KIND)
  // 935:             span(attribute_of NAME_OF_POLYMORPHIC)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._DEFINED_VARIABLE;
  arguments->slots[1] = temp__1;
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
  temp__1 = arguments->slots[0];
  // 942: $DEFINE_STATIC_SINGLE
  // 943:   '$', set_node(define_static_single), DEFINED_VARIABLE_OR_ATTRIBUTE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__36;
  arguments->slots[1] = temp__1;
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
  temp__1 = arguments->slots[0];
  // 945: $DEFINE_STATIC_MULTI "$$", set_node(define_static_multi), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__337_2;
  arguments->slots[1] = temp__1;
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
  temp__1 = arguments->slots[0];
  // 946: $DEFINE_DYNAMIC_SINGLE '%', set_node(define_dynamic_single), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__37;
  arguments->slots[1] = temp__1;
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
  temp__1 = arguments->slots[0];
  // 947: $DEFINE_DYNAMIC_MULTI "%%", set_node(define_dynamic_multi), DEFINED_VARIABLE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__339_2;
  arguments->slots[1] = temp__1;
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
  temp__1 = arguments->slots[0];
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
  temp__3 = arguments->slots[0];
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
  temp__4 = arguments->slots[0];
  // 961: alt(followed_by(':') span(functor_of NAME_OF_POLYMORPHIC))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  arguments->slots[1] = temp__4;
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
  temp__2 = arguments->slots[0];
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
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 964: $ASSIGN '!', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(METHOD_DEFINITION)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__33;
  arguments->slots[1] = var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[2] = temp__1;
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
  temp__1 = arguments->slots[0];
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
  temp__4 = arguments->slots[0];
  // 978: ... span(expression_of alt(OPERAND DESTINATION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__expression_of();
  arguments->slots[1] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 978: capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__text_of();
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 974: $BACKQUOTED
  // 975:   sequence
  // 976:     '`'
  // 977:     set_node(backquoted)
  // 978:     capture(node::text_of span(expression_of alt(OPERAND DESTINATION)))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__96;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 980: $INPUT_ARGUMENT arguments_span(alt(EXPRESSION BODY))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  temp__2 = arguments->slots[0];
  // 984: '?', set_field(is_an_optional_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__63;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
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
  temp__4 = arguments->slots[0];
  // 985: '*', set_field(is_an_expanded_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 982: $EXPANSION
  // 983:   alt
  // 984:     '?', set_field(is_an_optional_item true)
  // 985:     '*', set_field(is_an_expanded_item true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 987: ... DESTINATION, optional(EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._DESTINATION;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 987: $OUTPUT_ARGUMENT output_arguments_span(DESTINATION, optional(EXPANSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  temp__2 = arguments->slots[0];
  // 991: '&', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(EXPANSION)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__38;
  arguments->slots[1] = var._READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[2] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 989: $INPUT_OUTPUT_ARGUMENT
  // 990:   output_arguments_span
  // 991:     '&', READ_WRITE_IDENTIFIER_OR_FUNCTION_CALL, optional(EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  temp__3 = arguments->slots[0];
  // 1022: ... EXPRESSION, optional(EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1022: arguments_span(EXPRESSION, optional(EXPANSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
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
  temp__4 = arguments->slots[0];
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
  temp__6 = arguments->slots[0];
  // 1025: arguments_span(BACKQUOTED), MAYBE_SPLIT_INPUT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__6;
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
  temp__5 = arguments->slots[0];
  // 1020: $SIMPLE_ARGUMENT
  // 1021:   alt
  // 1022:     arguments_span(EXPRESSION, optional(EXPANSION))
  // 1023:     OUTPUT_ARGUMENT
  // 1024:     INPUT_OUTPUT_ARGUMENT, COPY_OUTPUT
  // 1025:     arguments_span(BACKQUOTED), MAYBE_SPLIT_INPUT
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._OUTPUT_ARGUMENT;
  arguments->slots[2] = temp__4;
  arguments->slots[3] = temp__5;
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
  temp__4 = arguments->slots[0];
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
  temp__5 = arguments->slots[0];
  // 1032: sequence
  // 1033:   set_node(attribute_value_pair)
  // 1034:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1035:   sim2c::WHITESPACE
  // 1036:   INPUT_ARGUMENT
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = temp__5;
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
  temp__3 = arguments->slots[0];
  // 1031: arguments_span
  // 1032:   sequence
  // 1033:     set_node(attribute_value_pair)
  // 1034:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1035:     sim2c::WHITESPACE
  // 1036:     INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
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
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
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
  temp__7 = arguments->slots[0];
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
  temp__10 = arguments->slots[0];
  // 1041: set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__10;
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
  temp__9 = arguments->slots[0];
  // 1040: arguments_span
  // 1041:   set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__9;
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
  temp__8 = arguments->slots[0];
  // 1037: sequence
  // 1038:   '/'
  // 1039:   followed_by(':')
  // 1040:   arguments_span
  // 1041:     set_node(attribute_function_pair), SEPARATOR, INPUT_ARGUMENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = temp__7;
  arguments->slots[2] = temp__8;
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
  temp__6 = arguments->slots[0];
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
  temp__14 = arguments->slots[0];
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
  temp__15 = arguments->slots[0];
  // 1045: sequence
  // 1046:   set_node(attribute_function_pair)
  // 1047:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1048:   SEPARATOR
  // 1049:   INPUT_ARGUMENT
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__14;
  arguments->slots[1] = temp__15;
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
  temp__13 = arguments->slots[0];
  // 1044: arguments_span
  // 1045:   sequence
  // 1046:     set_node(attribute_function_pair)
  // 1047:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1048:     SEPARATOR
  // 1049:     INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__13;
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
  temp__12 = arguments->slots[0];
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
  arguments->slots[1] = temp__12;
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
  temp__11 = arguments->slots[0];
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
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__6;
  arguments->slots[2] = temp__11;
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
  temp__2 = arguments->slots[0];
  // 1053: some(REMARK_BEHIND, NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
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
  temp__7 = arguments->slots[0];
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
  temp__8 = arguments->slots[0];
  // 1058: sequence
  // 1059:   set_node(attribute_value_pair)
  // 1060:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1061:   SINGLE_INPUT_ARGUMENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__7;
  arguments->slots[1] = temp__8;
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
  temp__6 = arguments->slots[0];
  // 1057: arguments_span
  // 1058:   sequence
  // 1059:     set_node(attribute_value_pair)
  // 1060:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1061:     SINGLE_INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__6;
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
  temp__5 = arguments->slots[0];
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
  arguments->slots[1] = temp__5;
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
  temp__4 = arguments->slots[0];
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
  temp__10 = arguments->slots[0];
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
  temp__13 = arguments->slots[0];
  // 1065: ... set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__13;
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
  temp__12 = arguments->slots[0];
  // 1065: arguments_span(set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__12;
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
  temp__11 = arguments->slots[0];
  // 1062: sequence
  // 1063:   '/'
  // 1064:   followed_by(':')
  // 1065:   arguments_span(set_node(attribute_function_pair), SINGLE_INPUT_ARGUMENT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = temp__10;
  arguments->slots[2] = temp__11;
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
  temp__9 = arguments->slots[0];
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
  temp__17 = arguments->slots[0];
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
  temp__18 = arguments->slots[0];
  // 1069: sequence
  // 1070:   set_node(attribute_function_pair)
  // 1071:   span(identifier_of NAME_OF_POLYMORPHIC)
  // 1072:   SINGLE_INPUT_ARGUMENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__17;
  arguments->slots[1] = temp__18;
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
  temp__16 = arguments->slots[0];
  // 1068: arguments_span
  // 1069:   sequence
  // 1070:     set_node(attribute_function_pair)
  // 1071:     span(identifier_of NAME_OF_POLYMORPHIC)
  // 1072:     SINGLE_INPUT_ARGUMENT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__16;
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
  temp__15 = arguments->slots[0];
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
  arguments->slots[1] = temp__15;
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
  temp__14 = arguments->slots[0];
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
  arguments->slots[0] = temp__4;
  arguments->slots[1] = temp__9;
  arguments->slots[2] = temp__14;
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
  temp__3 = arguments->slots[0];
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
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__3;
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
  temp__1 = arguments->slots[0];
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
  temp__2 = arguments->slots[0];
  // 1077: $INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1078:   INDENT, interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE), expect(outdent_marker)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1080: $SINGLE_EXPRESSION_LINE
  // 1081:   alt(LINE_START_ARGUMENT, ARGUMENT_LINE_END_REMARK LINE_END_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  temp__4 = arguments->slots[0];
  // 1088: alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_EXPRESSION;
  arguments->slots[1] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 1086: sequence
  // 1087:   SEPARATOR
  // 1088:   alt(LINE_END_EXPRESSION SIMPLE_ARGUMENT, PROCEDURE_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SEPARATOR;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
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
  temp__8 = arguments->slots[0];
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
  temp__9 = arguments->slots[0];
  // 1092: sequence
  // 1093:   INDENT
  // 1094:   some(NEWLINE)
  // 1095:   FIRST_LINE_START_ARGUMENTS
  // 1096:   expect(outdent_marker)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = temp__8;
  arguments->slots[2] = var._FIRST_LINE_START_ARGUMENTS;
  arguments->slots[3] = temp__9;
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
  temp__7 = arguments->slots[0];
  // 1091: optional
  // 1092:   sequence
  // 1093:     INDENT
  // 1094:     some(NEWLINE)
  // 1095:     FIRST_LINE_START_ARGUMENTS
  // 1096:     expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__7;
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
  temp__6 = arguments->slots[0];
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
  arguments->slots[1] = temp__6;
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
  temp__5 = arguments->slots[0];
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
  arguments->slots[0] = temp__2;
  arguments->slots[1] = temp__5;
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
  temp__1 = arguments->slots[0];
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
  arguments->slots[0] = temp__1;
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
  temp__3 = arguments->slots[0];
  // 1102: optional(SEPARATOR, ARGUMENT_REMARK)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
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
  temp__5 = arguments->slots[0];
  // 1103: optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__5;
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
  temp__4 = arguments->slots[0];
  // 1100: sequence
  // 1101:   LINE_END_EXPRESSION
  // 1102:   optional(SEPARATOR, ARGUMENT_REMARK)
  // 1103:   optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_EXPRESSION;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = temp__4;
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
  temp__1 = arguments->slots[0];
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
  temp__8 = arguments->slots[0];
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
  temp__10 = arguments->slots[0];
  // 1106: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__10;
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
  temp__9 = arguments->slots[0];
  // 1106: alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__8;
  arguments->slots[1] = temp__9;
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
  temp__7 = arguments->slots[0];
  // 1104: sequence
  // 1105:   SIMPLE_ARGUMENT
  // 1106:   alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMPLE_ARGUMENT;
  arguments->slots[1] = temp__7;
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
  temp__6 = arguments->slots[0];
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
  temp__13 = arguments->slots[0];
  // 1107: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__13;
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
  temp__12 = arguments->slots[0];
  // 1107: sequence(ARGUMENT_REMARK optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_REMARK;
  arguments->slots[1] = temp__12;
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
  temp__11 = arguments->slots[0];
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
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__6;
  arguments->slots[2] = temp__11;
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
  temp__2 = arguments->slots[0];
  // 1111: sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INFIX_OPERATOR;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1109: $OPERATORS_AND_OPERANDS
  // 1110:   alt
  // 1111:     sequence(INFIX_OPERATOR arguments_span(OPERAND) OPERATORS_AND_OPERANDS)
  // 1112:     EXTEND_EXPRESSION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  temp__1 = arguments->slots[0];
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
  temp__3 = arguments->slots[0];
  // 1121: alt(LINE_START_ARGUMENTS interleaved(ATTRIBUTE_VALUE_PAIR NEXT_LINE))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_START_ARGUMENTS;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
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
  temp__4 = arguments->slots[0];
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
  // 1137: functor(.enumeration_no_of undefined .remark_lines_of empty_list)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[3] /* functor */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__enumeration_no_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, get__empty_list());
    frame->slots[8] /* temp__4 */ = temp;

  }
  // 1138: ... arguments_of(node)
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
  // 1139: ... output_arguments_of(node)
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
  // 1140: ... enumeration_no_of(functor)
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
  // 1141: ... remark_lines_of(functor)
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
  // 1142: ... fragment_of(functor)
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
  // 1143: ... source_position_of(functor)
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
  // 1144: ... end_position_of(node)
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
  // 1137:     functor(.enumeration_no_of undefined .remark_lines_of empty_list)
  // 1138:   .arguments_of arguments_of(node)
  // 1139:   .output_arguments_of output_arguments_of(node)
  // 1140:   .enumeration_no_of enumeration_no_of(functor)
  // 1141:   .remark_lines_of remark_lines_of(functor)
  // 1142:   .fragment_of fragment_of(functor)
  // 1143:   .source_position_of source_position_of(functor)
  // 1144:   .end_position_of end_position_of(node)
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
  // 1137:         functor(.enumeration_no_of undefined .remark_lines_of empty_list)
  // 1138:       .arguments_of arguments_of(node)
  // 1139:       .output_arguments_of output_arguments_of(node)
  // 1140:       .enumeration_no_of enumeration_no_of(functor)
  // 1141:       .remark_lines_of remark_lines_of(functor)
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
  // 1146: ... top_level_node(.arguments_of new_arguments)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[1] /* top_level_node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* new_arguments */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 1146: -> top_level_node(.arguments_of new_arguments)
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
  temp__5 = arguments->slots[0];
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
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = var._STORE_END_POSITION;
  arguments->slots[3] = temp__4;
  arguments->slots[4] = temp__5;
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
  // 1154: modify_node
  // 1155:   : (&node)
  // 1156:     !node.original_remark_lines_of remark_lines_of(node)
  // 1157:     !node.remark_lines_of empty_list
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
  // 1156: !node.original_remark_lines_of remark_lines_of(node)
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
  // 1156: !node.original_remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__original_remark_lines_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1157: !node.remark_lines_of empty_list
  frame->slots[1] /* temp__1 */ = get__empty_list();
  // 1157: !node.remark_lines_of
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
  temp__2 = arguments->slots[0];
  // 1159: modify_node
  // 1160:   : (&node)
  // 1161:     $n length_of(arguments_of(node))
  // 1162:     if n > 0:
  // 1163:       append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1164:       !node.remark_lines_of empty_list
  // 1165:     !node.remark_lines_of original_remark_lines_of(node)
  // 1166:     !node.original_remark_lines_of undefined
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
  // 1161: ... arguments_of(node)
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
  // 1161: $n length_of(arguments_of(node))
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
  // 1162: ... n > 0
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
  // 1162: ... :
  // 1163:   append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1164:   !node.remark_lines_of empty_list
  frame->slots[3] /* temp__2 */ = create_closure(entry__361_8, 0);
  // 1162: if n > 0:
  // 1163:   append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
  // 1164:   !node.remark_lines_of empty_list
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
  // 1163: ... node.arguments_of
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
  // 1163: ... node.arguments_of(n)
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
  // 1163: ... node.arguments_of(n).remark_lines_of
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
  // 1163: ... remark_lines_of(node)
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
  // 1163: append &node.arguments_of(n).remark_lines_of remark_lines_of(node)
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
  // 1163: ... node.arguments_of
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
  // 1163: ... node.arguments_of(n)
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
  // 1163: ... &node.arguments_of(n).remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[8] /* temp__7 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[6] /* temp__5 */);
    frame->slots[8] /* temp__7 */ = temp;

  }
  // 1163: ... &node.arguments_of(n)
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
  // 1163: ... &node.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__6 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1164: !node.remark_lines_of empty_list
  frame->slots[2] /* temp__1 */ = get__empty_list();
  // 1164: !node.remark_lines_of
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
  // 1165: !node.remark_lines_of original_remark_lines_of(node)
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
  // 1165: !node.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1166: !node.original_remark_lines_of undefined
  frame->slots[2] /* temp__1 */ = get__undefined();
  // 1166: !node.original_remark_lines_of
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
  temp__3 = arguments->slots[0];
  // 1167: ... sequence(NEWLINES INDENTED_FUNCTION_CALL_OR_REMARK)
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
  temp__5 = arguments->slots[0];
  // 1167: alt(sequence(NEWLINES INDENTED_FUNCTION_CALL_OR_REMARK) OUTDENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__5;
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
  temp__4 = arguments->slots[0];
  // 1152: sequence
  // 1153:   # ATTENTION: very dirty fix!
  // 1154:   modify_node
  // 1155:     : (&node)
  // 1156:       !node.original_remark_lines_of remark_lines_of(node)
  // 1157:       !node.remark_lines_of empty_list
  // 1158:   REMARK
  // 1159:   modify_node
  // 1160:     : (&node)
  // 1161:       $n length_of(arguments_of(node))
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = var._REMARK;
  arguments->slots[2] = temp__3;
  arguments->slots[3] = temp__4;
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
  temp__1 = arguments->slots[0];
  // 1150: $INDENTED_FUNCTION_CALL_OR_REMARK
  // 1151:   alt
  // 1152:     sequence
  // 1153:       # ATTENTION: very dirty fix!
  // 1154:       modify_node
  // 1155:         : (&node)
  // 1156:           !node.original_remark_lines_of remark_lines_of(node)
  // 1157:           !node.remark_lines_of empty_list
  // 1158:       REMARK
  // 1159:       modify_node
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 1171: ... some(NEWLINE)
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
  temp__1 = arguments->slots[0];
  // 1170: $MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK
  // 1171:   INDENT, some(NEWLINE), INDENTED_FUNCTION_CALL_OR_REMARK
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = temp__1;
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
  // 1174: ... alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT)
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
  temp__3 = arguments->slots[0];
  // 1174: ... followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1174: ... '*', followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1173: $ARGUMENT_EXPANSION
  // 1174:   alt('?' '*', followed_by(alt(sim2c::WHITESPACE NEWLINE OUTDENT END_OF_TEXT)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__63;
  arguments->slots[1] = temp__1;
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
  // 1178: set_node(operator_symbol)
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
  temp__1 = arguments->slots[0];
  // 1180: capture(name_of INFIX_OPERATOR_SYMBOL)
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
  temp__2 = arguments->slots[0];
  // 1181: modify_node
  // 1182:   : (node)
  // 1183:     ->
  // 1184:       function_call
  // 1185:         .functor_of node
  // 1186:         .fragment_of fragment_of(node)
  // 1187:         .source_position_of source_position_of(node)
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
  // 1186: ... fragment_of(node)
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
  // 1187: ... source_position_of(node)
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
  // 1184: function_call
  // 1185:   .functor_of node
  // 1186:   .fragment_of fragment_of(node)
  // 1187:   .source_position_of source_position_of(node)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* node */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[3] /* temp__3 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1183: ->
  // 1184:   function_call
  // 1185:     .functor_of node
  // 1186:     .fragment_of fragment_of(node)
  // 1187:     .source_position_of source_position_of(node)
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
  temp__3 = arguments->slots[0];
  // 1191: expect(outdent_marker)
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
  temp__4 = arguments->slots[0];
  // 1192: modify_node
  // 1193:   :
  // 1194:     (
  // 1195:       &node
  // 1196:       stream
  // 1197:       -> return
  // 1198:     )
  // 1199:     $$arguments arguments_of(node)
  // 1200:     if length_of(arguments) < 2:
  // 1201:       ParseError stream "too few arguments in multi-line expression"
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
  // 1199: $$arguments arguments_of(node)
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
  // 1200: ... length_of(arguments)
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
  // 1200: ... length_of(arguments) < 2
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
  // 1200: ... :
  // 1201:   ParseError stream "too few arguments in multi-line expression"
  frame->slots[6] /* temp__3 */ = create_closure(entry__364_12, 0);
  // 1200: if length_of(arguments) < 2:
  // 1201:   ParseError stream "too few arguments in multi-line expression"
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
  // 1201: ParseError stream "too few arguments in multi-line expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__364_13;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__364_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1202: ... length_of(arguments)
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
  // 1202: ... length_of(arguments) > 2
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
  // 1202: ... :
  // 1203:   $functor functor_of(node)
  // 1204:   if
  // 1205:     precedence(name_of(functor)).is_left_associative:
  // 1206:       forever:
  // 1207:         !node
  // 1208:           function_call
  // 1209:             .functor_of functor
  // 1210:             .arguments_of range(arguments 1 2)
  // 1211:         if length_of(arguments) == 2 return
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__364_17, 0);
  // 1202: if length_of(arguments) > 2:
  // 1203:   $functor functor_of(node)
  // 1204:   if
  // 1205:     precedence(name_of(functor)).is_left_associative:
  // 1206:       forever:
  // 1207:         !node
  // 1208:           function_call
  // 1209:             .functor_of functor
  // 1210:             .arguments_of range(arguments 1 2)
  // 1211:         if length_of(arguments) == 2 return
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
  // 1218: ... 2
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
  // 1218: ... 1
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
  // 1218: ... range(arguments -2 -1)
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
  // 1215: !node
  // 1216:   function_call
  // 1217:     .functor_of functor
  // 1218:     .arguments_of range(arguments -2 -1)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1219: ... length_of(arguments)
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
  // 1219: ... length_of(arguments) == 2
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
  // 1219: if length_of(arguments) == 2 return
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
  // 1220: ... 3
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
  // 1220: ... range(arguments 1 -3)
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
  // 1220: !arguments push(range(arguments 1 -3) node)
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
  // 1210: ... range(arguments 1 2)
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
  // 1207: !node
  // 1208:   function_call
  // 1209:     .functor_of functor
  // 1210:     .arguments_of range(arguments 1 2)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 1211: ... length_of(arguments)
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
  // 1211: ... length_of(arguments) == 2
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
  // 1211: if length_of(arguments) == 2 return
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
  // 1212: ... 1
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
  // 1212: ... range(arguments 3 -1)
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
  // 1212: !arguments put(range(arguments 3 -1) node)
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
  // 1206: ... :
  // 1207:   !node
  // 1208:     function_call
  // 1209:       .functor_of functor
  // 1210:       .arguments_of range(arguments 1 2)
  // 1211:   if length_of(arguments) == 2 return
  // 1212:   !arguments put(range(arguments 3 -1) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__364_23, 0);
  // 1206: forever:
  // 1207:   !node
  // 1208:     function_call
  // 1209:       .functor_of functor
  // 1210:       .arguments_of range(arguments 1 2)
  // 1211:   if length_of(arguments) == 2 return
  // 1212:   !arguments put(range(arguments 3 -1) node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 1214: ... :
  // 1215:   !node
  // 1216:     function_call
  // 1217:       .functor_of functor
  // 1218:       .arguments_of range(arguments -2 -1)
  // 1219:   if length_of(arguments) == 2 return
  // 1220:   !arguments push(range(arguments 1 -3) node)
  frame->slots[4] /* temp__1 */ = create_closure(entry__364_32, 0);
  // 1214: forever:
  // 1215:   !node
  // 1216:     function_call
  // 1217:       .functor_of functor
  // 1218:       .arguments_of range(arguments -2 -1)
  // 1219:   if length_of(arguments) == 2 return
  // 1220:   !arguments push(range(arguments 1 -3) node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 1203: $functor functor_of(node)
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
  // 1205: ... name_of(functor)
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
  // 1205: precedence(name_of(functor))
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
  // 1205: precedence(name_of(functor)).is_left_associative
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
  // 1205: ... :
  // 1206:   forever:
  // 1207:     !node
  // 1208:       function_call
  // 1209:         .functor_of functor
  // 1210:         .arguments_of range(arguments 1 2)
  // 1211:     if length_of(arguments) == 2 return
  // 1212:     !arguments put(range(arguments 3 -1) node)
  frame->slots[7] /* temp__4 */ = create_closure(entry__364_22, 0);
  // 1213: :
  // 1214:   forever:
  // 1215:     !node
  // 1216:       function_call
  // 1217:         .functor_of functor
  // 1218:         .arguments_of range(arguments -2 -1)
  // 1219:     if length_of(arguments) == 2 return
  // 1220:     !arguments push(range(arguments 1 -3) node)
  frame->slots[8] /* temp__5 */ = create_closure(entry__364_31, 0);
  // 1204: if
  // 1205:   precedence(name_of(functor)).is_left_associative:
  // 1206:     forever:
  // 1207:       !node
  // 1208:         function_call
  // 1209:           .functor_of functor
  // 1210:           .arguments_of range(arguments 1 2)
  // 1211:       if length_of(arguments) == 2 return
  // 1212:       !arguments put(range(arguments 3 -1) node)
  // 1213:   :
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
  frame->cont = frame->cont;
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
  temp__5 = arguments->slots[0];
  // 1176: $MULTI_LINE_EXPRESSION
  // 1177:   sequence
  // 1178:     set_node(operator_symbol)
  // 1179:     STORE_POSITION
  // 1180:     capture(name_of INFIX_OPERATOR_SYMBOL)
  // 1181:     modify_node
  // 1182:       : (node)
  // 1183:         ->
  // 1184:           function_call
  // 1185:             .functor_of node
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = temp__2;
  arguments->slots[3] = temp__3;
  arguments->slots[4] = var._INDENT;
  arguments->slots[5] = var._LINE_START_ARGUMENTS;
  arguments->slots[6] = var._STORE_END_POSITION;
  arguments->slots[7] = temp__4;
  arguments->slots[8] = temp__5;
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
  // 1226: ... not_followed_by(ARGUMENT_EXPANSION)
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
  temp__4 = arguments->slots[0];
  // 1226: IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._IDENTIFIER_OR_FUNCTION_CALL;
  arguments->slots[1] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 1225: arguments_span
  // 1226:   IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1232: optional(sim2c::WHITESPACE)
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
  temp__11 = arguments->slots[0];
  // 1232: optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__11;
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
  temp__10 = arguments->slots[0];
  // 1234: sim2c::WHITESPACE, '.'
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
  temp__12 = arguments->slots[0];
  // 1235: NAME, '.'
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
  temp__13 = arguments->slots[0];
  // 1231: alt
  // 1232:   optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1233:   ','
  // 1234:   sim2c::WHITESPACE, '.'
  // 1235:   NAME, '.'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__10;
  arguments->slots[1] = character__44;
  arguments->slots[2] = temp__12;
  arguments->slots[3] = temp__13;
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
  temp__9 = arguments->slots[0];
  // 1230: followed_by
  // 1231:   alt
  // 1232:     optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1233:     ','
  // 1234:     sim2c::WHITESPACE, '.'
  // 1235:     NAME, '.'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__9;
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
  temp__8 = arguments->slots[0];
  // 1236: modify_node
  // 1237:   : (node)
  // 1238:     # store the current node in the parent slot for later retrieval
  // 1239:     
  // 1240:     ->
  // 1241:       expression
  // 1242:         .parent_of
  // 1243:           node(.arguments_of range(arguments_of(node) 1 -2))
  // 1244:         .arguments_of list(arguments_of(node)(-1))
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
  // 1243: ... arguments_of(node)
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
  // 1243: ... 2
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
  // 1243: ... range(arguments_of(node) 1 -2)
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
  // 1243: node(.arguments_of range(arguments_of(node) 1 -2))
  {
    NODE *temp = clone_object_and_attributes(frame->slots[0] /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__3 */);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 1244: ... 1
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
  // 1244: ... arguments_of(node)
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
  // 1244: ... arguments_of(node)(-1)
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
  // 1244: ... list(arguments_of(node)(-1))
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
  // 1241: expression
  // 1242:   .parent_of
  // 1243:     node(.arguments_of range(arguments_of(node) 1 -2))
  // 1244:   .arguments_of list(arguments_of(node)(-1))
  {
    NODE *temp = clone_object_and_attributes(get__expression());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parent_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__6 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 1240: ->
  // 1241:   expression
  // 1242:     .parent_of
  // 1243:       node(.arguments_of range(arguments_of(node) 1 -2))
  // 1244:     .arguments_of list(arguments_of(node)(-1))
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
  temp__14 = arguments->slots[0];
  // 1229: sequence
  // 1230:   followed_by
  // 1231:     alt
  // 1232:       optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1233:       ','
  // 1234:       sim2c::WHITESPACE, '.'
  // 1235:       NAME, '.'
  // 1236:   modify_node
  // 1237:     : (node)
  // 1238:       # store the current node in the parent slot for later retrieval
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__8;
  arguments->slots[1] = temp__14;
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
  temp__7 = arguments->slots[0];
  // 1248: ... NEXT_LINE, LINE_START_ARGUMENTS
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
  temp__17 = arguments->slots[0];
  // 1248: optional(NEXT_LINE, LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__17;
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
  temp__16 = arguments->slots[0];
  // 1246: sequence
  // 1247:   MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK
  // 1248:   optional(NEXT_LINE, LINE_START_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._MULTI_LINE_FUNCTION_CALL_OR_INDENTED_REMARK;
  arguments->slots[1] = temp__16;
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
  temp__15 = arguments->slots[0];
  // 1228: alt
  // 1229:   sequence
  // 1230:     followed_by
  // 1231:       alt
  // 1232:         optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1233:         ','
  // 1234:         sim2c::WHITESPACE, '.'
  // 1235:         NAME, '.'
  // 1236:     modify_node
  // 1237:       : (node)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__7;
  arguments->slots[1] = temp__15;
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
  temp__6 = arguments->slots[0];
  // 1227: optional
  // 1228:   alt
  // 1229:     sequence
  // 1230:       followed_by
  // 1231:         alt
  // 1232:           optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1233:           ','
  // 1234:           sim2c::WHITESPACE, '.'
  // 1235:           NAME, '.'
  // 1236:       modify_node
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__6;
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
  temp__5 = arguments->slots[0];
  // 1224: sequence
  // 1225:   arguments_span
  // 1226:     IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  // 1227:   optional
  // 1228:     alt
  // 1229:       sequence
  // 1230:         followed_by
  // 1231:           alt
  // 1232:             optional(sim2c::WHITESPACE), INFIX_OPERATOR_SYMBOL
  // 1233:             ','
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = temp__5;
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
  temp__1 = arguments->slots[0];
  // 1249: ... not_followed_by(ARGUMENT_EXPANSION)
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
  temp__20 = arguments->slots[0];
  // 1249: ... EXPRESSION, not_followed_by(ARGUMENT_EXPANSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._EXPRESSION;
  arguments->slots[1] = temp__20;
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
  temp__19 = arguments->slots[0];
  // 1249: arguments_span(EXPRESSION, not_followed_by(ARGUMENT_EXPANSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__19;
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
  temp__18 = arguments->slots[0];
  // 1250: arguments_span(MULTI_LINE_EXPRESSION)
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
  temp__21 = arguments->slots[0];
  // 1222: $LINE_START_ARGUMENT
  // 1223:   alt
  // 1224:     sequence
  // 1225:       arguments_span
  // 1226:         IDENTIFIER_OR_FUNCTION_CALL, not_followed_by(ARGUMENT_EXPANSION)
  // 1227:       optional
  // 1228:         alt
  // 1229:           sequence
  // 1230:             followed_by
  // 1231:               alt
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__18;
  arguments->slots[2] = temp__21;
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
  // 1254: ... NEXT_LINE, MORE_LINE_START_ARGUMENTS
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
  temp__3 = arguments->slots[0];
  // 1254: ... optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1254: LINE_END_EXPRESSION, optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_EXPRESSION;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1256: alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
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
  temp__5 = arguments->slots[0];
  // 1257: ... SEPARATOR, ARGUMENTS
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
  temp__7 = arguments->slots[0];
  // 1257: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  temp__9 = arguments->slots[0];
  // 1257: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__9;
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
  temp__8 = arguments->slots[0];
  // 1257: alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__7;
  arguments->slots[1] = temp__8;
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
  temp__6 = arguments->slots[0];
  // 1255: sequence
  // 1256:   alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
  // 1257:   alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__5;
  arguments->slots[1] = temp__6;
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
  temp__4 = arguments->slots[0];
  // 1252: $LINE_START_ARGUMENTS
  // 1253:   alt
  // 1254:     LINE_END_EXPRESSION, optional(NEXT_LINE, MORE_LINE_START_ARGUMENTS)
  // 1255:     sequence
  // 1256:       alt(LINE_START_ARGUMENT SIMPLE_ARGUMENT)
  // 1257:       alt(SEPARATOR, ARGUMENTS optional(NEWLINES, MORE_LINE_START_ARGUMENTS))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__4;
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
  // 1261: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  temp__3 = arguments->slots[0];
  // 1261: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1261: REMARK_BEHIND, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_BEHIND;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1259: $MORE_LINE_START_ARGUMENTS
  // 1260:   alt
  // 1261:     REMARK_BEHIND, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  // 1262:     LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 1266: ... NEWLINES, MORE_LINE_START_ARGUMENTS
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
  temp__3 = arguments->slots[0];
  // 1266: ... optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1266: REMARK_FIRST, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK_FIRST;
  arguments->slots[1] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1264: $FIRST_LINE_START_ARGUMENTS
  // 1265:   alt
  // 1266:     REMARK_FIRST, optional(NEWLINES, MORE_LINE_START_ARGUMENTS)
  // 1267:     LINE_START_ARGUMENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 1271: sim2c::WHITESPACE, INPUT_ARGUMENT, LINE_END_REMARK
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
  temp__1 = arguments->slots[0];
  // 1272: SEPARATOR, LINE_END_EXPRESSION
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
  temp__2 = arguments->slots[0];
  // 1276: ... REMARK, NEWLINES
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
  temp__5 = arguments->slots[0];
  // 1276: some(REMARK, NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__5;
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
  temp__4 = arguments->slots[0];
  // 1277: alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
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
  temp__6 = arguments->slots[0];
  // 1278: expect(outdent_marker)
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
  temp__7 = arguments->slots[0];
  // 1273: sequence
  // 1274:   LINE_END_REMARK
  // 1275:   INDENT
  // 1276:   some(REMARK, NEWLINES)
  // 1277:   alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
  // 1278:   expect(outdent_marker)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._LINE_END_REMARK;
  arguments->slots[1] = var._INDENT;
  arguments->slots[2] = temp__4;
  arguments->slots[3] = temp__6;
  arguments->slots[4] = temp__7;
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
  temp__3 = arguments->slots[0];
  // 1269: $SINGLE_INPUT_ARGUMENT
  // 1270:   alt
  // 1271:     sim2c::WHITESPACE, INPUT_ARGUMENT, LINE_END_REMARK
  // 1272:     SEPARATOR, LINE_END_EXPRESSION
  // 1273:     sequence
  // 1274:       LINE_END_REMARK
  // 1275:       INDENT
  // 1276:       some(REMARK, NEWLINES)
  // 1277:       alt(SINGLE_EXPRESSION_LINE INPUT_ARGUMENT)
  // 1278:       expect(outdent_marker)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = temp__3;
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
  // 1285: set_node(define_static_multi)
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
  temp__3 = arguments->slots[0];
  // 1286: set_field(parameter_kind_of IN_PARAMETER)
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
  temp__4 = arguments->slots[0];
  // 1283: sequence
  // 1284:   '$'
  // 1285:   set_node(define_static_multi)
  // 1286:   set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__36;
  arguments->slots[1] = temp__3;
  arguments->slots[2] = temp__4;
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
  temp__2 = arguments->slots[0];
  // 1289: set_node(define_static_multi)
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
  temp__6 = arguments->slots[0];
  // 1290: set_field(parameter_kind_of OUT_PARAMETER)
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
  temp__7 = arguments->slots[0];
  // 1287: sequence
  // 1288:   '!'
  // 1289:   set_node(define_static_multi)
  // 1290:   set_field(parameter_kind_of OUT_PARAMETER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__33;
  arguments->slots[1] = temp__6;
  arguments->slots[2] = temp__7;
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
  temp__5 = arguments->slots[0];
  // 1293: set_node(define_static_multi)
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
  temp__9 = arguments->slots[0];
  // 1294: set_field(parameter_kind_of IN_OUT_PARAMETER)
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
  temp__10 = arguments->slots[0];
  // 1291: sequence
  // 1292:   '&'
  // 1293:   set_node(define_static_multi)
  // 1294:   set_field(parameter_kind_of IN_OUT_PARAMETER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__38;
  arguments->slots[1] = temp__9;
  arguments->slots[2] = temp__10;
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
  temp__8 = arguments->slots[0];
  // 1295: set_node(define_static_single)
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
  temp__12 = arguments->slots[0];
  // 1295: ... set_field(parameter_kind_of IN_PARAMETER)
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
  temp__13 = arguments->slots[0];
  // 1295: set_node(define_static_single), set_field(parameter_kind_of IN_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__12;
  arguments->slots[1] = temp__13;
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
  temp__11 = arguments->slots[0];
  // 1282: alt
  // 1283:   sequence
  // 1284:     '$'
  // 1285:     set_node(define_static_multi)
  // 1286:     set_field(parameter_kind_of IN_PARAMETER)
  // 1287:   sequence
  // 1288:     '!'
  // 1289:     set_node(define_static_multi)
  // 1290:     set_field(parameter_kind_of OUT_PARAMETER)
  // 1291:   sequence
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = temp__5;
  arguments->slots[2] = temp__8;
  arguments->slots[3] = temp__11;
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
  temp__1 = arguments->slots[0];
  // 1280: $PARAMETER_MODE
  // 1281:   optional
  // 1282:     alt
  // 1283:       sequence
  // 1284:         '$'
  // 1285:         set_node(define_static_multi)
  // 1286:         set_field(parameter_kind_of IN_PARAMETER)
  // 1287:       sequence
  // 1288:         '!'
  // 1289:         set_node(define_static_multi)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 1302: infix_operator('=')
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
  temp__3 = arguments->slots[0];
  // 1303: set_field(is_an_optional_item true)
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
  temp__4 = arguments->slots[0];
  // 1304: span(default_value_of EXPRESSION)
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
  temp__5 = arguments->slots[0];
  // 1301: sequence
  // 1302:   infix_operator('=')
  // 1303:   set_field(is_an_optional_item true)
  // 1304:   span(default_value_of EXPRESSION)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  arguments->slots[1] = temp__4;
  arguments->slots[2] = temp__5;
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
  temp__2 = arguments->slots[0];
  // 1305: ... set_field(parameter_kind_of MYSELF_PARAMETER)
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
  temp__7 = arguments->slots[0];
  // 1305: '^', set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__94;
  arguments->slots[1] = temp__7;
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
  temp__6 = arguments->slots[0];
  // 1299: alt
  // 1300:   EXPANSION
  // 1301:   sequence
  // 1302:     infix_operator('=')
  // 1303:     set_field(is_an_optional_item true)
  // 1304:     span(default_value_of EXPRESSION)
  // 1305:   '^', set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._EXPANSION;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = temp__6;
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
  temp__1 = arguments->slots[0];
  // 1297: $PARAMETER_COUNT_OR_MYSELF
  // 1298:   optional
  // 1299:     alt
  // 1300:       EXPANSION
  // 1301:       sequence
  // 1302:         infix_operator('=')
  // 1303:         set_field(is_an_optional_item true)
  // 1304:         span(default_value_of EXPRESSION)
  // 1305:       '^', set_field(parameter_kind_of MYSELF_PARAMETER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 1310: modify_node
  // 1311:   : (&node)
  // 1312:     !node.is_not_used true
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
  // 1312: !node.is_not_used true
  frame->slots[1] /* temp__1 */ = get__true();
  // 1312: !node.is_not_used
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
  temp__1 = arguments->slots[0];
  // 1307: $NOT_USED
  // 1308:   sequence
  // 1309:     '_'
  // 1310:     modify_node
  // 1311:       : (&node)
  // 1312:         !node.is_not_used true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__95;
  arguments->slots[1] = temp__1;
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
  // 1318: set_node(identifier)
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
  temp__2 = arguments->slots[0];
  // 1320: optional(NOT_USED)
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
  temp__3 = arguments->slots[0];
  // 1321: capture(name_of NAME)
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
  temp__4 = arguments->slots[0];
  // 1317: sequence
  // 1318:   set_node(identifier)
  // 1319:   STORE_POSITION
  // 1320:   optional(NOT_USED)
  // 1321:   capture(name_of NAME)
  // 1322:   STORE_END_POSITION
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = temp__3;
  arguments->slots[3] = temp__4;
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
  temp__1 = arguments->slots[0];
  // 1314: $PARAMETER_NAME
  // 1315:   span
  // 1316:     identifier_of
  // 1317:     sequence
  // 1318:       set_node(identifier)
  // 1319:       STORE_POSITION
  // 1320:       optional(NOT_USED)
  // 1321:       capture(name_of NAME)
  // 1322:       STORE_END_POSITION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = temp__1;
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
  // 1324: $PARAMETER PARAMETER_MODE, PARAMETER_NAME, PARAMETER_COUNT_OR_MYSELF
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
  // 1327: ... INDENT, REMARK, OUTDENT
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
  temp__2 = arguments->slots[0];
  // 1327: ... optional(INDENT, REMARK, OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1326: $MULTI_LINE_PARAMETER
  // 1327:   PARAMETER, ARGUMENT_LINE_END_REMARK, optional(INDENT, REMARK, OUTDENT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER;
  arguments->slots[1] = var._ARGUMENT_LINE_END_REMARK;
  arguments->slots[2] = temp__1;
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
  // 1333: set_node(define_static_single)
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
  temp__1 = arguments->slots[0];
  // 1334: set_field(parameter_kind_of CONTINUATION_PARAMETER)
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
  temp__2 = arguments->slots[0];
  // 1329: $CONTINUATION
  // 1330:   sequence
  // 1331:     "->"
  // 1332:     sim2c::WHITESPACE
  // 1333:     set_node(define_static_single)
  // 1334:     set_field(parameter_kind_of CONTINUATION_PARAMETER)
  // 1335:     PARAMETER_NAME
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__376_3;
  arguments->slots[1] = var.sim2c__WHITESPACE;
  arguments->slots[2] = temp__1;
  arguments->slots[3] = temp__2;
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
  // 1338: ... INDENT, REMARK, OUTDENT
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
  temp__2 = arguments->slots[0];
  // 1338: ... optional(INDENT, REMARK, OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1337: $MULTI_LINE_CONTINUATION
  // 1338:   CONTINUATION, ARGUMENT_LINE_END_REMARK, optional(INDENT, REMARK, OUTDENT)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._CONTINUATION;
  arguments->slots[1] = var._ARGUMENT_LINE_END_REMARK;
  arguments->slots[2] = temp__1;
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
  // 1346: ... multi_span(parameters_of PARAMETER)
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
  temp__5 = arguments->slots[0];
  // 1346: interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__5;
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
  temp__4 = arguments->slots[0];
  // 1347: ... multi_span(parameters_of CONTINUATION)
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
  temp__8 = arguments->slots[0];
  // 1347: ... sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__8;
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
  temp__7 = arguments->slots[0];
  // 1347: optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__7;
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
  temp__6 = arguments->slots[0];
  // 1345: sequence
  // 1346:   interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1347:   optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = temp__6;
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
  temp__3 = arguments->slots[0];
  // 1348: multi_span(parameters_of CONTINUATION)
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
  temp__9 = arguments->slots[0];
  // 1344: alt
  // 1345:   sequence
  // 1346:     interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1347:     optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1348:   multi_span(parameters_of CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  arguments->slots[1] = temp__9;
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
  temp__2 = arguments->slots[0];
  // 1343: optional
  // 1344:   alt
  // 1345:     sequence
  // 1346:       interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1347:       optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1348:     multi_span(parameters_of CONTINUATION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1349: expect(')')
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
  temp__10 = arguments->slots[0];
  // 1340: $INLINE_PARAMETERS
  // 1341:   sequence
  // 1342:     '('
  // 1343:     optional
  // 1344:       alt
  // 1345:         sequence
  // 1346:           interleaved(multi_span(parameters_of PARAMETER) sim2c::WHITESPACE)
  // 1347:           optional(sim2c::WHITESPACE, multi_span(parameters_of CONTINUATION))
  // 1348:         multi_span(parameters_of CONTINUATION)
  // 1349:     expect(')')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__10;
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
  // 1357: ... multi_span(parameters_of MULTI_LINE_PARAMETER)
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
  temp__4 = arguments->slots[0];
  // 1357: interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 1358: ... multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  temp__7 = arguments->slots[0];
  // 1358: ... NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINE;
  arguments->slots[1] = temp__7;
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
  temp__6 = arguments->slots[0];
  // 1358: optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__6;
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
  temp__5 = arguments->slots[0];
  // 1356: sequence
  // 1357:   interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1358:   optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  arguments->slots[1] = temp__5;
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
  temp__2 = arguments->slots[0];
  // 1359: multi_span(parameters_of MULTI_LINE_CONTINUATION)
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
  temp__8 = arguments->slots[0];
  // 1355: alt
  // 1356:   sequence
  // 1357:     interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1358:     optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  // 1359:   multi_span(parameters_of MULTI_LINE_CONTINUATION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = temp__8;
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
  temp__1 = arguments->slots[0];
  // 1360: expect(outdent_marker)
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
  temp__9 = arguments->slots[0];
  // 1361: expect(newline)
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
  temp__10 = arguments->slots[0];
  // 1362: expect(')')
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
  temp__11 = arguments->slots[0];
  // 1351: $MULTI_LINE_PARAMETERS
  // 1352:   sequence
  // 1353:     '('
  // 1354:     INDENT
  // 1355:     alt
  // 1356:       sequence
  // 1357:         interleaved(multi_span(parameters_of MULTI_LINE_PARAMETER) NEWLINE)
  // 1358:         optional(NEWLINE, multi_span(parameters_of MULTI_LINE_CONTINUATION))
  // 1359:       multi_span(parameters_of MULTI_LINE_CONTINUATION)
  // 1360:     expect(outdent_marker)
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = character__40;
  arguments->slots[1] = var._INDENT;
  arguments->slots[2] = temp__1;
  arguments->slots[3] = temp__9;
  arguments->slots[4] = temp__10;
  arguments->slots[5] = temp__11;
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
  // 1367: set_node(body)
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
  temp__1 = arguments->slots[0];
  // 1369: optional(NEW_LINE_END_REMARK)
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
  temp__2 = arguments->slots[0];
  // 1374: ... REMARK, NEWLINES
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
  temp__7 = arguments->slots[0];
  // 1374: some(REMARK, NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__7;
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
  temp__6 = arguments->slots[0];
  // 1378: expect(outdent_marker)
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
  temp__8 = arguments->slots[0];
  // 1372: sequence
  // 1373:   INDENT
  // 1374:   some(REMARK, NEWLINES)
  // 1375:   MULTI_LINE_PARAMETERS
  // 1376:   NEWLINES
  // 1377:   STATEMENTS
  // 1378:   expect(outdent_marker)
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = temp__6;
  arguments->slots[2] = var._MULTI_LINE_PARAMETERS;
  arguments->slots[3] = var._NEWLINES;
  arguments->slots[4] = var._STATEMENTS;
  arguments->slots[5] = temp__8;
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
  temp__5 = arguments->slots[0];
  // 1380: ... sim2c::WHITESPACE, INLINE_PARAMETERS
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
  temp__11 = arguments->slots[0];
  // 1380: optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__11;
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
  temp__10 = arguments->slots[0];
  // 1383: ... optional(NEWLINES)
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
  temp__14 = arguments->slots[0];
  // 1383: ... expect(outdent_marker)
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
  temp__15 = arguments->slots[0];
  // 1383: INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = temp__14;
  arguments->slots[2] = var._STATEMENTS;
  arguments->slots[3] = temp__15;
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
  temp__13 = arguments->slots[0];
  // 1386: ... syntax_error("statement expected")
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
  temp__18 = arguments->slots[0];
  // 1386: alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._STATEMENT;
  arguments->slots[1] = var._RETURN_STATEMENT;
  arguments->slots[2] = temp__18;
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
  temp__17 = arguments->slots[0];
  // 1384: sequence
  // 1385:   sim2c::WHITESPACE
  // 1386:   alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__17;
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
  temp__16 = arguments->slots[0];
  // 1387: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__380_16;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__380_17;
}
static void cont__380_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__19 = arguments->slots[0];
  // 1382: alt
  // 1383:   INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
  // 1384:   sequence
  // 1385:     sim2c::WHITESPACE
  // 1386:     alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  // 1387:   syntax_error("statement expected")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__13;
  arguments->slots[1] = temp__16;
  arguments->slots[2] = temp__19;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__380_18;
}
static void cont__380_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__12 = arguments->slots[0];
  // 1379: sequence
  // 1380:   optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
  // 1381:   LINE_END_REMARK
  // 1382:   alt
  // 1383:     INDENT, optional(NEWLINES), STATEMENTS, expect(outdent_marker)
  // 1384:     sequence
  // 1385:       sim2c::WHITESPACE
  // 1386:       alt(STATEMENT RETURN_STATEMENT syntax_error("statement expected"))
  // 1387:     syntax_error("statement expected")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__10;
  arguments->slots[1] = var._LINE_END_REMARK;
  arguments->slots[2] = temp__12;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_19;
}
static void cont__380_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__9 = arguments->slots[0];
  // 1388: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__380_20;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__380_21;
}
static void cont__380_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__20 = arguments->slots[0];
  // 1371: alt
  // 1372:   sequence
  // 1373:     INDENT
  // 1374:     some(REMARK, NEWLINES)
  // 1375:     MULTI_LINE_PARAMETERS
  // 1376:     NEWLINES
  // 1377:     STATEMENTS
  // 1378:     expect(outdent_marker)
  // 1379:   sequence
  // 1380:     optional(sim2c::WHITESPACE, INLINE_PARAMETERS)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__5;
  arguments->slots[1] = temp__9;
  arguments->slots[2] = temp__20;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__380_22;
}
static void cont__380_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1370: sequence
  // 1371:   alt
  // 1372:     sequence
  // 1373:       INDENT
  // 1374:       some(REMARK, NEWLINES)
  // 1375:       MULTI_LINE_PARAMETERS
  // 1376:       NEWLINES
  // 1377:       STATEMENTS
  // 1378:       expect(outdent_marker)
  // 1379:     sequence
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_23;
}
static void cont__380_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1364: $COMPLETE_BODY
  // 1365:   sequence
  // 1366:     ':'
  // 1367:     set_node(body)
  // 1368:     STORE_POSITION_MINUS_1
  // 1369:     optional(NEW_LINE_END_REMARK)
  // 1370:     sequence
  // 1371:       alt
  // 1372:         sequence
  // 1373:           INDENT
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = character__58;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = temp__3;
  arguments->slots[5] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__380_24;
}
static void cont__380_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._COMPLETE_BODY, arguments->slots[0]);
  // 1393: followed_by("->")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__381_1;
  result_count = 1;
  myself = get__followed_by();
  func = myself->type;
  frame->cont = cont__381_2;
}
static void cont__381_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1394: set_node(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__body();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__381_3;
}
static void cont__381_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1391: $RETURN_EXPRESSION
  // 1392:   sequence
  // 1393:     followed_by("->")
  // 1394:     set_node(body)
  // 1395:     STORE_POSITION
  // 1396:     RETURN_STATEMENT
  // 1397:     STORE_END_POSITION
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = var._STORE_POSITION;
  arguments->slots[3] = var._RETURN_STATEMENT;
  arguments->slots[4] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__381_4;
}
static void cont__381_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RETURN_EXPRESSION, arguments->slots[0]);
  // 1399: $BODY alt(COMPLETE_BODY RETURN_EXPRESSION)
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
  // 1404: set_node(c_body)
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
  temp__1 = arguments->slots[0];
  // 1406: expect(indent_marker)
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
  temp__2 = arguments->slots[0];
  // 1407: ... not_followed_by(OUTDENT)
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
  temp__6 = arguments->slots[0];
  // 1407: ... not_followed_by(OUTDENT), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__6;
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
  temp__5 = arguments->slots[0];
  // 1407: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__5;
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
  temp__4 = arguments->slots[0];
  // 1407: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__source_of();
  arguments->slots[1] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 1408: expect(outdent_marker)
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
  temp__7 = arguments->slots[0];
  // 1409: expect(newline)
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
  temp__8 = arguments->slots[0];
  // 1410: expect('}')
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
  temp__9 = arguments->slots[0];
  // 1401: $C_BODY
  // 1402:   sequence
  // 1403:     '{'
  // 1404:     set_node(c_body)
  // 1405:     STORE_POSITION_MINUS_1
  // 1406:     expect(indent_marker)
  // 1407:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  // 1408:     expect(outdent_marker)
  // 1409:     expect(newline)
  // 1410:     expect('}')
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__123;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._STORE_POSITION_MINUS_1;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = temp__3;
  arguments->slots[5] = temp__7;
  arguments->slots[6] = temp__8;
  arguments->slots[7] = temp__9;
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
  // 1413: ... alt(BODY C_BODY MULTI_LINE_STRING)
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
  temp__1 = arguments->slots[0];
  // 1413: $LINE_END_EXPRESSION arguments_span(alt(BODY C_BODY MULTI_LINE_STRING))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 1414: ... set_node(polymorphic_function)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__polymorphic_function();
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
  temp__1 = arguments->slots[0];
  // 1414: $POLYMORPHIC_FUNCTION_WITHOUT_SETTER "()", set_node(polymorphic_function)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__385_2;
  arguments->slots[1] = temp__1;
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
  initialize_future(var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER, arguments->slots[0]);
  // 1417: ... set_node(polymorphic_function_with_setter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__polymorphic_function_with_setter();
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
  temp__1 = arguments->slots[0];
  // 1416: $POLYMORPHIC_FUNCTION_WITH_SETTER
  // 1417:   "(!)", set_node(polymorphic_function_with_setter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__386_2;
  arguments->slots[1] = temp__1;
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
  initialize_future(var._POLYMORPHIC_FUNCTION_WITH_SETTER, arguments->slots[0]);
  // 1423: alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER;
  arguments->slots[1] = var._POLYMORPHIC_FUNCTION_WITH_SETTER;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__387_1;
}
static void cont__387_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1422: arguments_span
  // 1423:   alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  result_count = 1;
  myself = get__arguments_span();
  func = myself->type;
  frame->cont = cont__387_2;
}
static void cont__387_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1419: $POLYMORPHIC_FUNCTION
  // 1420:   sequence
  // 1421:     sim2c::WHITESPACE
  // 1422:     arguments_span
  // 1423:       alt(POLYMORPHIC_FUNCTION_WITHOUT_SETTER POLYMORPHIC_FUNCTION_WITH_SETTER)
  // 1424:     LINE_END_REMARK
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._LINE_END_REMARK;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__387_3;
}
static void cont__387_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._POLYMORPHIC_FUNCTION, arguments->slots[0]);
  // 1428: set_node(assignment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__assignment();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__388_1;
}
static void cont__388_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1431: output_arguments_span(DEFINE_STATIC_MULTI)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_STATIC_MULTI;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__388_2;
}
static void cont__388_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1431: output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__388_3;
}
static void cont__388_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1433: output_arguments_span(DEFINE_STATIC_SINGLE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_STATIC_SINGLE;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__388_4;
}
static void cont__388_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 1434: alt(POLYMORPHIC_FUNCTION SINGLE_INPUT_ARGUMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__388_5;
}
static void cont__388_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 1432: sequence
  // 1433:   output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1434:   alt(POLYMORPHIC_FUNCTION SINGLE_INPUT_ARGUMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__6;
  arguments->slots[1] = temp__7;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__388_6;
}
static void cont__388_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 1435: output_arguments_span(DEFINE_DYNAMIC_MULTI)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_DYNAMIC_MULTI;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__388_7;
}
static void cont__388_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__9 = arguments->slots[0];
  // 1435: output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__9;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__388_8;
}
static void cont__388_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__8 = arguments->slots[0];
  // 1436: output_arguments_span(DEFINE_DYNAMIC_SINGLE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._DEFINE_DYNAMIC_SINGLE;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__388_9;
}
static void cont__388_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__11 = arguments->slots[0];
  // 1436: output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__11;
  arguments->slots[1] = var._SINGLE_INPUT_ARGUMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__388_10;
}
static void cont__388_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__10 = arguments->slots[0];
  // 1438: output_arguments_span(ASSIGN)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._ASSIGN;
  result_count = 1;
  myself = get__output_arguments_span();
  func = myself->type;
  frame->cont = cont__388_11;
}
static void cont__388_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__13 = arguments->slots[0];
  // 1439: alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SINGLE_INPUT_ARGUMENT;
  arguments->slots[1] = var._INDENTED_ATTRIBUTE_VALUE_PAIRS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__388_12;
}
static void cont__388_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__14 = arguments->slots[0];
  // 1437: sequence
  // 1438:   output_arguments_span(ASSIGN)
  // 1439:   alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__13;
  arguments->slots[1] = temp__14;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__388_13;
}
static void cont__388_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__12 = arguments->slots[0];
  // 1430: alt
  // 1431:   output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1432:   sequence
  // 1433:     output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1434:     alt(POLYMORPHIC_FUNCTION SINGLE_INPUT_ARGUMENT)
  // 1435:   output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1436:   output_arguments_span(DEFINE_DYNAMIC_SINGLE), SINGLE_INPUT_ARGUMENT
  // 1437:   sequence
  // 1438:     output_arguments_span(ASSIGN)
  // 1439:     alt(SINGLE_INPUT_ARGUMENT INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  arguments->slots[1] = temp__5;
  arguments->slots[2] = temp__8;
  arguments->slots[3] = temp__10;
  arguments->slots[4] = temp__12;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__388_14;
}
static void cont__388_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1426: $ASSIGNMENT
  // 1427:   sequence
  // 1428:     set_node(assignment)
  // 1429:     STORE_POSITION
  // 1430:     alt
  // 1431:       output_arguments_span(DEFINE_STATIC_MULTI), SINGLE_INPUT_ARGUMENT
  // 1432:       sequence
  // 1433:         output_arguments_span(DEFINE_STATIC_SINGLE)
  // 1434:         alt(POLYMORPHIC_FUNCTION SINGLE_INPUT_ARGUMENT)
  // 1435:       output_arguments_span(DEFINE_DYNAMIC_MULTI), SINGLE_INPUT_ARGUMENT
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = temp__2;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__388_15;
}
static void cont__388_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ASSIGNMENT, arguments->slots[0]);
  // 1442: $FUNCTOR span(functor_of IDENTIFIER_OR_FUNCTION_CALL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__functor_of();
  arguments->slots[1] = var._IDENTIFIER_OR_FUNCTION_CALL;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__389_1;
}
static void cont__389_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FUNCTOR, arguments->slots[0]);
  // 1446: ... span(result_count_of EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__result_count_of();
  arguments->slots[1] = var._EXPRESSION;
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
  temp__2 = arguments->slots[0];
  // 1446: ".(", span(result_count_of EXPRESSION), ')'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__390_2;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = character__41;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__390_3;
}
static void cont__390_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1447: ... span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__continuation_of();
  arguments->slots[1] = var._IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__390_4;
}
static void cont__390_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1447: '/', span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = temp__4;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__390_5;
}
static void cont__390_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1444: $RESULT_COUNT_OR_CONTINUATION
  // 1445:   alt
  // 1446:     ".(", span(result_count_of EXPRESSION), ')'
  // 1447:     '/', span(continuation_of IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__3;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__390_6;
}
static void cont__390_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RESULT_COUNT_OR_CONTINUATION, arguments->slots[0]);
  // 1451: set_node(procedure_call)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__procedure_call();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__391_1;
}
static void cont__391_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1454: optional(RESULT_COUNT_OR_CONTINUATION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._RESULT_COUNT_OR_CONTINUATION;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__391_2;
}
static void cont__391_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1463: optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._INDENTED_ATTRIBUTE_VALUE_PAIRS;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__391_3;
}
static void cont__391_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 1460: sequence
  // 1461:   sim2c::WHITESPACE
  // 1462:   INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1463:   optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._INLINE_ATTRIBUTE_VALUE_PAIRS;
  arguments->slots[2] = temp__7;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__391_4;
}
static void cont__391_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 1459: alt
  // 1460:   sequence
  // 1461:     sim2c::WHITESPACE
  // 1462:     INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1463:     optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1464:   INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1465:   PROCEDURE_ARGUMENTS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__6;
  arguments->slots[1] = var._INDENTED_ATTRIBUTE_VALUE_PAIRS;
  arguments->slots[2] = var._PROCEDURE_ARGUMENTS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__391_5;
}
static void cont__391_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 1456: sequence
  // 1457:   sim2c::WHITESPACE
  // 1458:   OUTPUT_ARGUMENT
  // 1459:   alt
  // 1460:     sequence
  // 1461:       sim2c::WHITESPACE
  // 1462:       INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1463:       optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1464:     INDENTED_ATTRIBUTE_VALUE_PAIRS
  // 1465:     PROCEDURE_ARGUMENTS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = var._OUTPUT_ARGUMENT;
  arguments->slots[2] = temp__5;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__391_6;
}
static void cont__391_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1455: alt
  // 1456:   sequence
  // 1457:     sim2c::WHITESPACE
  // 1458:     OUTPUT_ARGUMENT
  // 1459:     alt
  // 1460:       sequence
  // 1461:         sim2c::WHITESPACE
  // 1462:         INLINE_ATTRIBUTE_VALUE_PAIRS
  // 1463:         optional(INDENTED_ATTRIBUTE_VALUE_PAIRS)
  // 1464:       INDENTED_ATTRIBUTE_VALUE_PAIRS
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = var._PROCEDURE_ARGUMENTS;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__391_7;
}
static void cont__391_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1449: $PROCEDURE_CALL
  // 1450:   sequence
  // 1451:     set_node(procedure_call)
  // 1452:     STORE_POSITION
  // 1453:     FUNCTOR
  // 1454:     optional(RESULT_COUNT_OR_CONTINUATION)
  // 1455:     alt
  // 1456:       sequence
  // 1457:         sim2c::WHITESPACE
  // 1458:         OUTPUT_ARGUMENT
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._STORE_POSITION;
  arguments->slots[2] = var._FUNCTOR;
  arguments->slots[3] = temp__2;
  arguments->slots[4] = temp__3;
  arguments->slots[5] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__391_8;
}
static void cont__391_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PROCEDURE_CALL, arguments->slots[0]);
  // 1469: ... interleaved(REMARK NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._REMARK;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__392_1;
}
static void cont__392_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1469: $INDENTED_REMARKS INDENT, interleaved(REMARK NEWLINES), OUTDENT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = var._INDENT;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = var._OUTDENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__392_2;
}
static void cont__392_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._INDENTED_REMARKS, arguments->slots[0]);
  // 1475: alt(ASSIGNMENT PROCEDURE_CALL)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ASSIGNMENT;
  arguments->slots[1] = var._PROCEDURE_CALL;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__393_1;
}
static void cont__393_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1475: ... optional(INDENTED_REMARKS)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._INDENTED_REMARKS;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__393_2;
}
static void cont__393_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1475: alt(ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = temp__3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__393_3;
}
static void cont__393_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1471: $SINGLE_STATEMENT
  // 1472:   # used for top-level statements (fragments)
  // 1473:   
  // 1474:   alt
  // 1475:     alt(ASSIGNMENT PROCEDURE_CALL), optional(INDENTED_REMARKS)
  // 1476:     SINGLE_REMARK_STATEMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = var._SINGLE_REMARK_STATEMENT;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__393_4;
}
static void cont__393_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SINGLE_STATEMENT, arguments->slots[0]);
  // 1478: $STATEMENT multi_span(statements_of SINGLE_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = var._SINGLE_STATEMENT;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__394_1;
}
static void cont__394_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STATEMENT, arguments->slots[0]);
  // 1486: set_node(return_statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__return_statement();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__395_1;
}
static void cont__395_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1485: sequence
  // 1486:   set_node(return_statement)
  // 1487:   STORE_POSITION_MINUS_2
  // 1488:   PROCEDURE_ARGUMENTS
  // 1489:   STORE_END_POSITION
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  arguments->slots[1] = var._STORE_POSITION_MINUS_2;
  arguments->slots[2] = var._PROCEDURE_ARGUMENTS;
  arguments->slots[3] = var._STORE_END_POSITION;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__395_2;
}
static void cont__395_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1483: multi_span
  // 1484:   statements_of
  // 1485:   sequence
  // 1486:     set_node(return_statement)
  // 1487:     STORE_POSITION_MINUS_2
  // 1488:     PROCEDURE_ARGUMENTS
  // 1489:     STORE_END_POSITION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements_of();
  arguments->slots[1] = temp__2;
  result_count = 1;
  myself = get__multi_span();
  func = myself->type;
  frame->cont = cont__395_3;
}
static void cont__395_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1480: $RETURN_STATEMENT
  // 1481:   sequence
  // 1482:     "->"
  // 1483:     multi_span
  // 1484:       statements_of
  // 1485:       sequence
  // 1486:         set_node(return_statement)
  // 1487:         STORE_POSITION_MINUS_2
  // 1488:         PROCEDURE_ARGUMENTS
  // 1489:         STORE_END_POSITION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__395_4;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__395_5;
}
static void cont__395_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._RETURN_STATEMENT, arguments->slots[0]);
  // 1494: interleaved(STATEMENT NEXT_LINE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._STATEMENT;
  arguments->slots[1] = var._NEXT_LINE;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__396_1;
}
static void cont__396_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1494: ... NEXT_LINE, RETURN_STATEMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE;
  arguments->slots[1] = var._RETURN_STATEMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__396_2;
}
static void cont__396_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 1494: ... optional(NEXT_LINE, RETURN_STATEMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__5;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__396_3;
}
static void cont__396_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1494: interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  arguments->slots[1] = temp__4;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__396_4;
}
static void cont__396_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1496: syntax_error("statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__396_5;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__396_6;
}
static void cont__396_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 1493: alt
  // 1494:   interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
  // 1495:   RETURN_STATEMENT
  // 1496:   syntax_error("statement expected")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = var._RETURN_STATEMENT;
  arguments->slots[2] = temp__6;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__396_7;
}
static void cont__396_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1497: ... NEXT_LINE, REMARK_STATEMENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEXT_LINE;
  arguments->slots[1] = var._REMARK_STATEMENT;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__396_8;
}
static void cont__396_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__8 = arguments->slots[0];
  // 1497: some(NEXT_LINE, REMARK_STATEMENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__8;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__396_9;
}
static void cont__396_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 1491: $STATEMENTS
  // 1492:   sequence
  // 1493:     alt
  // 1494:       interleaved(STATEMENT NEXT_LINE), optional(NEXT_LINE, RETURN_STATEMENT)
  // 1495:       RETURN_STATEMENT
  // 1496:       syntax_error("statement expected")
  // 1497:     some(NEXT_LINE, REMARK_STATEMENT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__7;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__396_10;
}
static void cont__396_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._STATEMENTS, arguments->slots[0]);
  // 1502: set_node(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__identifier();
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
  temp__2 = arguments->slots[0];
  // 1502: ... "__", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__397_2;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__397_3;
}
static void cont__397_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 1502: ... many("__", NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__6;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__397_4;
}
static void cont__397_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 1502: ... NAME, many("__", NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__NAME();
  arguments->slots[1] = temp__5;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__397_5;
}
static void cont__397_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1502: ... capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__name_of();
  arguments->slots[1] = temp__4;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__397_6;
}
static void cont__397_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1502: set_node(identifier), capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = temp__3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__397_7;
}
static void cont__397_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1499: $BUILTIN_NAME
  // 1500:   span
  // 1501:     identifier_of
  // 1502:     set_node(identifier), capture(name_of NAME, many("__", NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__identifier_of();
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__397_8;
}
static void cont__397_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BUILTIN_NAME, arguments->slots[0]);
  // 1504: ... not_followed_by('>')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__62;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__398_1;
}
static void cont__398_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1504: ... not_followed_by('>'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = get__ANY_CHARACTER();
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
  temp__1 = arguments->slots[0];
  // 1504: $C_EXPRESSION many(not_followed_by('>'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__398_3;
}
static void cont__398_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_EXPRESSION, arguments->slots[0]);
  // 1509: ... multi_capture(arguments_of C_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__arguments_of();
  arguments->slots[1] = var._C_EXPRESSION;
  result_count = 1;
  myself = get__multi_capture();
  func = myself->type;
  frame->cont = cont__399_1;
}
static void cont__399_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1509: ... sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__399_2;
}
static void cont__399_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1509: expect(sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__399_3;
}
static void cont__399_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1506: $ARGUMENT_ANNOTATION
  // 1507:   sequence
  // 1508:     "argument"
  // 1509:     expect(sim2c::WHITESPACE, multi_capture(arguments_of C_EXPRESSION))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__399_4;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__399_5;
}
static void cont__399_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ARGUMENT_ANNOTATION, arguments->slots[0]);
  // 1512: ... span(base_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__base_of();
  arguments->slots[1] = var._NAMESPACED_IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__400_1;
}
static void cont__400_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1512: ... sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1512: ... expect(sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__400_3;
}
static void cont__400_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1511: $BASE_ANNOTATION
  // 1512:   "base", expect(sim2c::WHITESPACE, span(base_of NAMESPACED_IDENTIFIER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__400_4;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__400_5;
}
static void cont__400_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._BASE_ANNOTATION, arguments->slots[0]);
  // 1514: ... capture(kind_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__kind_of();
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__401_1;
}
static void cont__401_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1514: ... sim2c::WHITESPACE, capture(kind_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1514: ... expect(sim2c::WHITESPACE, capture(kind_of NAME))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1514: $KIND_ANNOTATION "kind", expect(sim2c::WHITESPACE, capture(kind_of NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__401_4;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__401_5;
}
static void cont__401_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._KIND_ANNOTATION, arguments->slots[0]);
  // 1519: ... alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._BUILTIN_NAME;
  arguments->slots[1] = var._DEFINED_VARIABLE_OR_ATTRIBUTE;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__402_1;
}
static void cont__402_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1519: ... sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1519: expect(sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1516: $NAME_ANNOTATION
  // 1517:   sequence
  // 1518:     "name"
  // 1519:     expect(sim2c::WHITESPACE, alt(BUILTIN_NAME DEFINED_VARIABLE_OR_ATTRIBUTE))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__402_4;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__402_5;
}
static void cont__402_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._NAME_ANNOTATION, arguments->slots[0]);
  // 1521: ... capture(node_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node_of();
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
  temp__3 = arguments->slots[0];
  // 1521: ... sim2c::WHITESPACE, capture(node_of NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1521: ... expect(sim2c::WHITESPACE, capture(node_of NAME))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1521: $NODE_ANNOTATION "node", expect(sim2c::WHITESPACE, capture(node_of NAME))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__403_4;
  arguments->slots[1] = temp__1;
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
  initialize_future(var._NODE_ANNOTATION, arguments->slots[0]);
  // 1529: ... alt("runtime" "global" "local" "extern")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__404_1;
  arguments->slots[1] = string__404_2;
  arguments->slots[2] = string__404_3;
  arguments->slots[3] = string__404_4;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__404_5;
}
static void cont__404_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1529: capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__scope_of();
  arguments->slots[1] = temp__4;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__404_6;
}
static void cont__404_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1527: sequence
  // 1528:   sim2c::WHITESPACE
  // 1529:   capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__3;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__404_7;
}
static void cont__404_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1526: expect
  // 1527:   sequence
  // 1528:     sim2c::WHITESPACE
  // 1529:     capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__404_8;
}
static void cont__404_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1523: $SCOPE_ANNOTATION
  // 1524:   sequence
  // 1525:     "scope"
  // 1526:     expect
  // 1527:       sequence
  // 1528:         sim2c::WHITESPACE
  // 1529:         capture(node::scope_of alt("runtime" "global" "local" "extern"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__404_9;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__404_10;
}
static void cont__404_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SCOPE_ANNOTATION, arguments->slots[0]);
  // 1532: ... span(node::type_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__node__type_of();
  arguments->slots[1] = var._NAMESPACED_IDENTIFIER;
  result_count = 1;
  myself = get__span();
  func = myself->type;
  frame->cont = cont__405_1;
}
static void cont__405_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1532: ... sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.sim2c__WHITESPACE;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 1532: ... expect(sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
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
  temp__1 = arguments->slots[0];
  // 1531: $TYPE_ANNOTATION
  // 1532:   "type", expect(sim2c::WHITESPACE, span(node::type_of NAMESPACED_IDENTIFIER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__405_4;
  arguments->slots[1] = temp__1;
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
  initialize_future(var._TYPE_ANNOTATION, arguments->slots[0]);
  // 1543: syntax_error("invalid annotation tag")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__406_1;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__406_2;
}
static void cont__406_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1534: $ANNOTATION_ITEM
  // 1535:   alt
  // 1536:     ARGUMENT_ANNOTATION
  // 1537:     BASE_ANNOTATION
  // 1538:     KIND_ANNOTATION
  // 1539:     NAME_ANNOTATION
  // 1540:     NODE_ANNOTATION
  // 1541:     SCOPE_ANNOTATION
  // 1542:     TYPE_ANNOTATION
  // 1543:     syntax_error("invalid annotation tag")
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = var._ARGUMENT_ANNOTATION;
  arguments->slots[1] = var._BASE_ANNOTATION;
  arguments->slots[2] = var._KIND_ANNOTATION;
  arguments->slots[3] = var._NAME_ANNOTATION;
  arguments->slots[4] = var._NODE_ANNOTATION;
  arguments->slots[5] = var._SCOPE_ANNOTATION;
  arguments->slots[6] = var._TYPE_ANNOTATION;
  arguments->slots[7] = temp__1;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__406_3;
}
static void cont__406_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATION_ITEM, arguments->slots[0]);
  // 1545: ... expect('>')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__62;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__407_1;
}
static void cont__407_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1545: $ANNOTATION '<', ANNOTATION_ITEM, expect('>')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = var._ANNOTATION_ITEM;
  arguments->slots[2] = temp__1;
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
  initialize_future(var._ANNOTATION, arguments->slots[0]);
  // 1546: $ANNOTATIONS interleaved(ANNOTATION NEWLINES)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ANNOTATION;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = var._interleaved;
  func = myself->type;
  frame->cont = cont__408_1;
}
static void cont__408_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._ANNOTATIONS, arguments->slots[0]);
  // 1547: $C_CODE_REMARK "//", REMARK_LINE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__409_1;
  arguments->slots[1] = var._REMARK_LINE;
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
  initialize_future(var._C_CODE_REMARK, arguments->slots[0]);
  // 1548: ... C_CODE_REMARK, NEWLINES
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._C_CODE_REMARK;
  arguments->slots[1] = var._NEWLINES;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__410_1;
}
static void cont__410_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1548: $C_CODE_REMARKS some(C_CODE_REMARK, NEWLINES)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__410_2;
}
static void cont__410_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_CODE_REMARKS, arguments->slots[0]);
  // 1553: ... not_followed_by(OUTDENT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._OUTDENT;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__411_1;
}
static void cont__411_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1553: ... not_followed_by(OUTDENT), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = get__ANY_CHARACTER();
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
  temp__3 = arguments->slots[0];
  // 1553: ... some(not_followed_by(OUTDENT), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__411_3;
}
static void cont__411_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1553: capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__source_of();
  arguments->slots[1] = temp__2;
  result_count = 1;
  myself = get__capture();
  func = myself->type;
  frame->cont = cont__411_4;
}
static void cont__411_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1550: $SOURCE
  // 1551:   sequence
  // 1552:     C_CODE_REMARKS
  // 1553:     capture(source_of some(not_followed_by(OUTDENT), ANY_CHARACTER))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._C_CODE_REMARKS;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__411_5;
}
static void cont__411_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SOURCE, arguments->slots[0]);
  // 1558: set_node(c_code)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__c_code();
  result_count = 1;
  myself = get__set_node();
  func = myself->type;
  frame->cont = cont__412_1;
}
static void cont__412_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1559: expect(indent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__indent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__412_2;
}
static void cont__412_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1560: ... NEWLINES, SOURCE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NEWLINES;
  arguments->slots[1] = var._SOURCE;
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
  temp__6 = arguments->slots[0];
  // 1560: ... optional(NEWLINES, SOURCE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__6;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__412_4;
}
static void cont__412_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 1560: ... ANNOTATIONS, optional(NEWLINES, SOURCE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ANNOTATIONS;
  arguments->slots[1] = temp__5;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__412_5;
}
static void cont__412_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1560: alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  arguments->slots[1] = var._SOURCE;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__412_6;
}
static void cont__412_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1561: expect(outdent_marker)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__outdent_marker();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__412_7;
}
static void cont__412_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 1562: expect(newline)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__412_8;
}
static void cont__412_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__8 = arguments->slots[0];
  // 1563: expect('}')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__125;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__412_9;
}
static void cont__412_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__9 = arguments->slots[0];
  // 1555: $C_CODE
  // 1556:   sequence
  // 1557:     '{'
  // 1558:     set_node(c_code)
  // 1559:     expect(indent_marker)
  // 1560:     alt(ANNOTATIONS, optional(NEWLINES, SOURCE) SOURCE)
  // 1561:     expect(outdent_marker)
  // 1562:     expect(newline)
  // 1563:     expect('}')
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = character__123;
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__2;
  arguments->slots[3] = temp__3;
  arguments->slots[4] = temp__7;
  arguments->slots[5] = temp__8;
  arguments->slots[6] = temp__9;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__412_10;
}
static void cont__412_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._C_CODE, arguments->slots[0]);
  // 1565: ... newline, END_OF_TEXT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  arguments->slots[1] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__413_1;
}
static void cont__413_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1565: ... expect(newline, END_OF_TEXT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__413_2;
}
static void cont__413_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1565: $META_FRAGMENT META_INSTRUCTION, expect(newline, END_OF_TEXT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._META_INSTRUCTION;
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__413_3;
}
static void cont__413_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._META_FRAGMENT, arguments->slots[0]);
  // 1573: syntax_error("top-level statement expected")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__414_1;
  result_count = 1;
  myself = var._syntax_error;
  func = myself->type;
  frame->cont = cont__414_2;
}
static void cont__414_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 1569: alt
  // 1570:   SINGLE_REMARK_STATEMENT
  // 1571:   SINGLE_STATEMENT
  // 1572:   C_CODE
  // 1573:   syntax_error("top-level statement expected")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = var._SINGLE_REMARK_STATEMENT;
  arguments->slots[1] = var._SINGLE_STATEMENT;
  arguments->slots[2] = var._C_CODE;
  arguments->slots[3] = temp__2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__414_3;
}
static void cont__414_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 1574: ... newline, END_OF_TEXT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__newline();
  arguments->slots[1] = get__END_OF_TEXT();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__414_4;
}
static void cont__414_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 1574: expect(newline, END_OF_TEXT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  result_count = 1;
  myself = var._expect;
  func = myself->type;
  frame->cont = cont__414_5;
}
static void cont__414_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 1567: $FRAGMENT
  // 1568:   sequence
  // 1569:     alt
  // 1570:       SINGLE_REMARK_STATEMENT
  // 1571:       SINGLE_STATEMENT
  // 1572:       C_CODE
  // 1573:       syntax_error("top-level statement expected")
  // 1574:     expect(newline, END_OF_TEXT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__3;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__414_6;
}
static void cont__414_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._FRAGMENT, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__1_1(void) {
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
  arguments->slots[3] = string__2_53;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = string__2_54;
  arguments->slots[6] = ((CELL *)frame->slots[2])->contents /* msg */;
  arguments->slots[7] = string__2_55;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__2_56;
}
static void cont__2_56(void) {
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
  frame->cont = frame->cont;
}
static void entry__2_57(void) {
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
  // 77:   @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)@quot;:@nl;@(msg)!
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__2_58;
  arguments->slots[1] = frame->slots[0] /* msg_type */;
  arguments->slots[2] = string__2_59;
  arguments->slots[3] = ((CELL *)frame->slots[1])->contents /* line_no */;
  arguments->slots[4] = string__2_60;
  arguments->slots[5] = get__module_name();
  arguments->slots[6] = string__2_61;
  arguments->slots[7] = ((CELL *)frame->slots[2])->contents /* msg */;
  arguments->slots[8] = string__2_62;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__2_63;
}
static void cont__2_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 75: ewrite "
  // 76:   ____________________________________
  // 77:   @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)@quot;:@nl;@(msg)!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__2_64;
}
static void cont__2_64(void) {
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
  frame->cont = cont__2_65;
}
static void cont__2_65(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 79: ... dup(" " n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_66;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* n */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__2_67;
}
static void cont__2_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 79: ewriteln dup(" " n) "^"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__2_68;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__2_1(void) {
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
  // 77:     @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)@quot;:@nl;@(msg)!
  // 78:   ewriteln line
  // 79:   ewriteln dup(" " n) "^"
  frame->slots[13] /* temp__2 */ = create_closure(entry__2_57, 0);
  // 71: if
  // 72:   do_show_brief_messages:
  // 73:     ewrite "@(module_name):@(line_no):@(n+1): @(msg)@nl;"
  // 74:   :
  // 75:     ewrite "
  // 76:       ____________________________________
  // 77:       @(msg_type) IN LINE @(line_no) OF FILE "@(module_name)@quot;:@nl;@(msg)!
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
  frame->cont = frame->cont;
}
static void entry__3_1(void) {
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
  frame->cont = frame->cont;
}
static void entry__4_1(void) {
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
  frame->cont = frame->cont;
}
static void entry__5_1(void) {
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
  frame->cont = frame->cont;
}
static void entry__6_1(void) {
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
  frame->cont = frame->cont;
}
static void entry__8_1(void) {
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
  frame->cont = frame->cont;
}
static void entry__9_1(void) {
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  // 117: ParseError stream "unexpected input"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__11_13;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__11_14(void) {
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
  // 119: ... "
  // 120:   @quot;@(expression)" expected@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__11_15;
  arguments->slots[1] = frame->slots[1] /* expression */;
  arguments->slots[2] = string__11_16;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__11_17;
}
static void cont__11_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 119: ParseError stream "
  // 120:   @quot;@(expression)" expected@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__11_7(void) {
  allocate_initialized_frame_gc(2, 6);
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
  // 117:   ParseError stream "unexpected input"
  frame->slots[4] /* temp__3 */ = create_closure(entry__11_12, 0);
  // 118: :
  // 119:   ParseError stream "
  // 120:     @quot;@(expression)" expected@
  frame->slots[5] /* temp__4 */ = create_closure(entry__11_14, 0);
  // 110: case
  // 111:   expression
  // 112:   newline:
  // 113:     ParseError stream "newline expected"
  // 114:   indent_marker:
  // 115:     ParseError stream "indent expected"
  // 116:   outdent_marker:
  // 117:     ParseError stream "unexpected input"
  // 118:   :
  // 119:     ParseError stream "
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expression */;
  arguments->slots[1] = get__newline();
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = get__indent_marker();
  arguments->slots[4] = frame->slots[3] /* temp__2 */;
  arguments->slots[5] = get__outdent_marker();
  arguments->slots[6] = frame->slots[4] /* temp__3 */;
  arguments->slots[7] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__11_18(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stream: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stream */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 122: ParseError stream "unexpected input"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stream */;
  arguments->slots[1] = string__11_19;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__11_1(void) {
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
  // 117:       ParseError stream "unexpected input"
  // 118:     :
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__11_7, 0);
  // 121: :
  // 122:   ParseError stream "unexpected input"
  frame->slots[7] /* temp__5 */ = create_closure(entry__11_18, 0);
  // 108: if
  // 109:   expression.is_a_character || expression.is_a_string:
  // 110:     case
  // 111:       expression
  // 112:       newline:
  // 113:         ParseError stream "newline expected"
  // 114:       indent_marker:
  // 115:         ParseError stream "indent expected"
  // 116:       outdent_marker:
  // 117:         ParseError stream "unexpected input"
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
  frame->cont = frame->cont;
}
static void entry__12_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 125: ... types::unexpected_input_error(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__unexpected_input_error);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 125: -> types::unexpected_input_error(.expression_of expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 134: ... message_of(self)
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
  // 134: ewriteln message_of(self)
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
  // 135: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // message: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 137: ... types::print(.message_of message)
  {
    NODE *temp = clone_object_and_attributes(var.types__print);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__message_of, frame->slots[0] /* message */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 137: ... -> types::print(.message_of message)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__17_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 146: ewriteln "<<<<<<<<<<"
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
  // 147: ... truncate_behind(stream '@nl;' 2)
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
  // 147: eprint_source truncate_behind(stream '@nl;' 2)
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
  // 148: ewriteln ">>>>>>>>>>"
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
  // 149: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* node */ = create_cell_with_contents(arguments->slots[0]);
  // 156: !node.fragment_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 156: !node.fragment_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 157: !node.source_position_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 157: !node.source_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 158: !node.end_position_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 158: !node.end_position_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 159: !node.inherited_names_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 159: !node.inherited_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__inherited_names_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 160: !node.defined_names_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 160: !node.defined_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__defined_names_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 161: !node.used_names_of undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 161: !node.used_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* node */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__used_names_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* node */ = temp;

  }
  // 162: ... functor_of(node)
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
  // 162: ... functor_of(node).is_defined
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
  // 162: ... : strip &node.functor_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_4, 0);
  // 162: if functor_of(node).is_defined: strip &node.functor_of
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
  // 162: ... node.functor_of
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
  // 162: ... strip &node.functor_of
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
  // 162: ... &node.functor_of
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
  // 163: ... attribute_of(node)
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
  // 163: ... attribute_of(node).is_defined
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
  // 163: ... : strip &node.attribute_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_10, 0);
  // 163: if attribute_of(node).is_defined: strip &node.attribute_of
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
  // 163: ... node.attribute_of
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
  // 163: ... strip &node.attribute_of
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
  // 163: ... &node.attribute_of
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
  // 164: ... statements_of(node)
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
  // 164: ... statements_of(node).is_defined
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
  // 164: ... :
  // 165:   update_each &node.statements_of: (&statement) strip &statement
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_16, 0);
  // 164: if statements_of(node).is_defined:
  // 165:   update_each &node.statements_of: (&statement) strip &statement
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
  // 165: ... node.statements_of
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
  // 165: update_each &node.statements_of: (&statement) strip &statement
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
  // 165: ... strip &statement
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
  // 165: ... &node.statements_of
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
  // 166: ... parameters_of(node)
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
  // 166: ... parameters_of(node).is_defined
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
  // 166: ... :
  // 167:   update_each &node.parameters_of: (&parameter) strip &parameter
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_24, 0);
  // 166: if parameters_of(node).is_defined:
  // 167:   update_each &node.parameters_of: (&parameter) strip &parameter
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
  // 167: ... node.parameters_of
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
  // 167: update_each &node.parameters_of: (&parameter) strip &parameter
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
  // 167: ... strip &parameter
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
  // 167: ... &node.parameters_of
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
  // 168: ... output_arguments_of(node)
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
  // 168: ... output_arguments_of(node).is_defined
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
  // 168: ... :
  // 169:   update_each &node.output_arguments_of: (&argument) strip &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_32, 0);
  // 168: if output_arguments_of(node).is_defined:
  // 169:   update_each &node.output_arguments_of: (&argument) strip &argument
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
  // 169: ... node.output_arguments_of
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
  // 169: update_each &node.output_arguments_of: (&argument) strip &argument
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
  // 169: ... strip &argument
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
  // 169: ... &node.output_arguments_of
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
  // 170: ... arguments_of(node)
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
  // 170: ... arguments_of(node).is_defined
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
  // 170: ... :
  // 171:   update_each &node.arguments_of: (&argument) strip &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_40, 0);
  // 170: if arguments_of(node).is_defined:
  // 171:   update_each &node.arguments_of: (&argument) strip &argument
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
  // 171: ... node.arguments_of
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
  // 171: update_each &node.arguments_of: (&argument) strip &argument
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
  // 171: ... strip &argument
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
  // 171: ... &node.arguments_of
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
  // 172: ... parent_of(node)
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
  // 172: ... parent_of(node).is_defined
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
  // 172: ... : strip &node.parent_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_48, 0);
  // 172: if parent_of(node).is_defined: strip &node.parent_of
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
  // 172: ... node.parent_of
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
  // 172: ... strip &node.parent_of
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
  // 172: ... &node.parent_of
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
  // 173: ... identifier_of(node)
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
  // 173: ... identifier_of(node).is_defined
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
  // 173: ... : strip &node.identifier_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_54, 0);
  // 173: if identifier_of(node).is_defined: strip &node.identifier_of
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
  // 173: ... node.identifier_of
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
  // 173: ... strip &node.identifier_of
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
  // 173: ... &node.identifier_of
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
static void entry__20_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 178: ... strip(grammar::current_node)
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
  // 178: edump `strip(grammar::current_node)
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
  // 179: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 184: ... strip(grammar::current_node)
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
  // 184: edump 3 `strip(grammar::current_node)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = string__22_3;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__edump();
  func = myself->type;
  frame->cont = cont__22_4;
}
static void cont__22_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 185: -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // stream: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 190: ... strip(grammar::current_node)
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
  // 190: edump 5 `strip(grammar::current_node)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__5;
  arguments->slots[1] = string__24_3;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__edump();
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 191: -> 0
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
  // 224: ... precedence_table(op)
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
  // 224: ... -> precedence_table(op)
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
  // 224: ... -> INFIX_PRECEDENCE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__INFIX_PRECEDENCE();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // op: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 224: ... op.is_a_string
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
  // 224: ... -> precedence_table(op)
  frame->slots[2] /* temp__2 */ = create_closure(entry__28_3, 0);
  // 224: if op.is_a_string (-> precedence_table(op)) -> INFIX_PRECEDENCE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = func__28_5;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // prec: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 226: ... prec > 5
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
  // 226: ... -> prec > 5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // prec: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 228: ... prec <= 5
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
  // 228: ... prec <= 5
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
  // 228: ... -> prec <= 5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__31_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // operator: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 231: ... sim2c::WHITESPACE, operator, sim2c::WHITESPACE
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
  // 231: ... alt(operator sim2c::WHITESPACE, operator, sim2c::WHITESPACE)
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
  // 231: -> alt(operator sim2c::WHITESPACE, operator, sim2c::WHITESPACE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__32_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // expression: 0
  // separator: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 233: ... separator, expression
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
  // 233: ... some(separator, expression)
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
  // 233: ... expression, some(separator, expression)
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
  // 233: ... -> expression, some(separator, expression)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__35_1(void) {
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
  // 242: %within_inline_expression true
  initialize_maybe_future(get__within_inline_expression(), get__true());
  // 243: ... expression_of(self)
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
  // 243: grammar::match expression_of(self) stream
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
static void entry__36_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 245: ... types::inline(.expression_of expression)
  {
    NODE *temp = clone_object_and_attributes(var.types__inline);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__expression_of, frame->slots[0] /* expression */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 245: ... -> types::inline(.expression_of expression)
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
  // 263: ... "@(description) expected"
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
  // 263: ... syntax_error("@(description) expected")
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
  // 263: ... alt(expression syntax_error("@(description) expected"))
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
  // 263: -> alt(expression syntax_error("@(description) expected"))
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
  // 264: ... unexpected_input_error(expression)
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
  // 264: ... alt(expression unexpected_input_error(expression))
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
  // 264: -> alt(expression unexpected_input_error(expression))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__42_1(void) {
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
  // 262: description.is_defined
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
  // 263: -> alt(expression syntax_error("@(description) expected"))
  frame->slots[3] /* temp__2 */ = create_closure(entry__42_3, 0);
  // 264: -> alt(expression unexpected_input_error(expression))
  frame->slots[4] /* temp__3 */ = create_closure(entry__42_8, 0);
  // 261: if
  // 262:   description.is_defined
  // 263:   -> alt(expression syntax_error("@(description) expected"))
  // 264:   -> alt(expression unexpected_input_error(expression))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__45_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 283: ... expression, ENUMERATE
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
  // 283: ... multi_span(arguments_of expression, ENUMERATE)
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
  // 283: -> multi_span(arguments_of expression, ENUMERATE)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__46_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // expression: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 286: ... expression, ENUMERATE, MAKE_A_DESTINATION
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
  // 286: ... multi_span(output_arguments_of expression, ENUMERATE, MAKE_A_DESTINATION)
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
  // 286: -> multi_span(output_arguments_of expression, ENUMERATE, MAKE_A_DESTINATION)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__207_1(void) {
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
  // 1580: %sim2c::current_fragment fragment # used to generate meaningful error messages
  initialize_maybe_future(get__sim2c__current_fragment(), frame->slots[0] /* fragment */);
  // 1581: $source sim2c::source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__sim2c__source_of();
  func = myself->type;
  frame->cont = cont__207_2;
}
static void cont__207_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* source */, arguments->slots[0]);
  // 1582: match source META_FRAGMENT $len $cap
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  arguments->slots[1] = var._META_FRAGMENT;
  result_count = 2;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__207_3;
}
static void cont__207_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  // 1582: ... len
  initialize_future(frame->slots[3] /* len */, frame->slots[5] /* temp__1 */);
  // 1582: ... cap
  initialize_future(frame->slots[4] /* cap */, frame->slots[6] /* temp__2 */);
  // 1583: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__207_4;
}
static void cont__207_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 1583: ... len != length_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__207_5;
}
static void cont__207_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 1583: ... len != length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__207_6;
}
static void cont__207_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1583: ... : ParseError source "invalid meta instruction"
  frame->slots[8] /* temp__4 */ = create_closure(entry__207_7, 0);
  // 1583: if len != length_of(source): ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__207_9;
}
static void entry__207_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1583: ... ParseError source "invalid meta instruction"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__207_8;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__207_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1584: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__208_1(void) {
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
  // 1587: %sim2c::current_fragment fragment # used to generate meaningful error messages
  initialize_maybe_future(get__sim2c__current_fragment(), frame->slots[0] /* fragment */);
  // 1588: $source sim2c::source_of(fragment)
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
  // 1589: match source FRAGMENT $len $cap
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  arguments->slots[1] = var._FRAGMENT;
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
  // 1589: ... len
  initialize_future(frame->slots[3] /* len */, frame->slots[5] /* temp__1 */);
  // 1589: ... cap
  initialize_future(frame->slots[4] /* cap */, frame->slots[6] /* temp__2 */);
  // 1591: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__208_4;
}
static void cont__208_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1591: ... :
  // 1592:   if len != length_of(source):
  // 1593:     ParseError source "superficious input at end of expression"
  frame->slots[6] /* temp__2 */ = create_closure(entry__208_5, 0);
  // 1594: :
  // 1595:   ewriteln "________________________________________"
  // 1596:   eprint_source source
  // 1597:   ewriteln "no match"
  // 1598:   exit 1
  frame->slots[7] /* temp__3 */ = create_closure(entry__208_11, 0);
  // 1590: if
  // 1591:   len.is_defined:
  // 1592:     if len != length_of(source):
  // 1593:       ParseError source "superficious input at end of expression"
  // 1594:   :
  // 1595:     ewriteln "________________________________________"
  // 1596:     eprint_source source
  // 1597:     ewriteln "no match"
  // 1598:     exit 1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__208_17;
}
static void entry__208_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1593: ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = string__208_10;
  result_count = frame->caller_result_count;
  myself = var._ParseError;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__208_5(void) {
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
  // 1592: ... length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__208_6;
}
static void cont__208_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1592: ... len != length_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__208_7;
}
static void cont__208_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1592: ... len != length_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__208_8;
}
static void cont__208_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1592: ... :
  // 1593:   ParseError source "superficious input at end of expression"
  frame->slots[5] /* temp__4 */ = create_closure(entry__208_9, 0);
  // 1592: if len != length_of(source):
  // 1593:   ParseError source "superficious input at end of expression"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__208_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1595: ewriteln "________________________________________"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__208_12;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__208_13;
}
static void cont__208_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1596: eprint_source source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 0;
  myself = get__eprint_source();
  func = myself->type;
  frame->cont = cont__208_14;
}
static void cont__208_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1597: ewriteln "no match"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__208_15;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__208_16;
}
static void cont__208_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1598: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__208_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1599: -> cap
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* cap */;
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__parser(void) {
  temp__1 = collect_node(temp__1);
  temp__2 = collect_node(temp__2);
  temp__3 = collect_node(temp__3);
  temp__4 = collect_node(temp__4);
  temp__5 = collect_node(temp__5);
  temp__6 = collect_node(temp__6);
  temp__7 = collect_node(temp__7);
  temp__8 = collect_node(temp__8);
  temp__9 = collect_node(temp__9);
  temp__10 = collect_node(temp__10);
  temp__11 = collect_node(temp__11);
  temp__12 = collect_node(temp__12);
  temp__13 = collect_node(temp__13);
  temp__14 = collect_node(temp__14);
  temp__15 = collect_node(temp__15);
  temp__16 = collect_node(temp__16);
  temp__17 = collect_node(temp__17);
  temp__18 = collect_node(temp__18);
  temp__19 = collect_node(temp__19);
  temp__20 = collect_node(temp__20);
  temp__21 = collect_node(temp__21);
  var.sim2c__std_identifier = collect_node(var.sim2c__std_identifier);
  string__1_2 = collect_node(string__1_2);
  func__1_1 = collect_node(func__1_1);
  var._print_message = collect_node(var._print_message);
  string__2_36 = collect_node(string__2_36);
  string__2_52 = collect_node(string__2_52);
  string__2_53 = collect_node(string__2_53);
  string__2_54 = collect_node(string__2_54);
  string__2_55 = collect_node(string__2_55);
  string__2_58 = collect_node(string__2_58);
  string__2_59 = collect_node(string__2_59);
  string__2_60 = collect_node(string__2_60);
  string__2_61 = collect_node(string__2_61);
  string__2_62 = collect_node(string__2_62);
  string__2_66 = collect_node(string__2_66);
  string__2_68 = collect_node(string__2_68);
  func__2_1 = collect_node(func__2_1);
  var.sim2c__Warning = collect_node(var.sim2c__Warning);
  string__3_4 = collect_node(string__3_4);
  func__3_1 = collect_node(func__3_1);
  var._ExitWithSyntaxError = collect_node(var._ExitWithSyntaxError);
  string__4_2 = collect_node(string__4_2);
  func__4_1 = collect_node(func__4_1);
  var.sim2c__SyntaxError = collect_node(var.sim2c__SyntaxError);
  func__5_1 = collect_node(func__5_1);
  var._ParseError = collect_node(var._ParseError);
  func__6_1 = collect_node(func__6_1);
  var.types__syntax_error = collect_node(var.types__syntax_error);
  func__8_1 = collect_node(func__8_1);
  var._syntax_error = collect_node(var._syntax_error);
  func__9_1 = collect_node(func__9_1);
  var.types__unexpected_input_error = collect_node(var.types__unexpected_input_error);
  string__11_9 = collect_node(string__11_9);
  string__11_11 = collect_node(string__11_11);
  string__11_13 = collect_node(string__11_13);
  string__11_15 = collect_node(string__11_15);
  string__11_16 = collect_node(string__11_16);
  string__11_19 = collect_node(string__11_19);
  func__11_1 = collect_node(func__11_1);
  var._unexpected_input_error = collect_node(var._unexpected_input_error);
  func__12_1 = collect_node(func__12_1);
  var.types__print = collect_node(var.types__print);
  func__14_1 = collect_node(func__14_1);
  var._print = collect_node(var._print);
  func__15_1 = collect_node(func__15_1);
  var._dump_stream = collect_node(var._dump_stream);
  string__17_2 = collect_node(string__17_2);
  string__17_6 = collect_node(string__17_6);
  func__17_1 = collect_node(func__17_1);
  var.sim2c__strip = collect_node(var.sim2c__strip);
  func__18_18 = collect_node(func__18_18);
  func__18_26 = collect_node(func__18_26);
  func__18_34 = collect_node(func__18_34);
  func__18_42 = collect_node(func__18_42);
  func__18_1 = collect_node(func__18_1);
  var._dump = collect_node(var._dump);
  string__20_3 = collect_node(string__20_3);
  func__20_1 = collect_node(func__20_1);
  var._dump3 = collect_node(var._dump3);
  string__22_3 = collect_node(string__22_3);
  func__22_1 = collect_node(func__22_1);
  var._dump5 = collect_node(var._dump5);
  string__24_3 = collect_node(string__24_3);
  func__24_1 = collect_node(func__24_1);
  var.sim2c__HIGHEST_PRECEDENCE = collect_node(var.sim2c__HIGHEST_PRECEDENCE);
  var.sim2c__INFIX_PRECEDENCE = collect_node(var.sim2c__INFIX_PRECEDENCE);
  var._precedence_table = collect_node(var._precedence_table);
  var.sim2c__precedence = collect_node(var.sim2c__precedence);
  func__28_5 = collect_node(func__28_5);
  func__28_1 = collect_node(func__28_1);
  var.sim2c__is_left_associative = collect_node(var.sim2c__is_left_associative);
  func__29_1 = collect_node(func__29_1);
  var._is_right_associative = collect_node(var._is_right_associative);
  func__30_1 = collect_node(func__30_1);
  var._infix_operator = collect_node(var._infix_operator);
  func__31_1 = collect_node(func__31_1);
  var._interleaved = collect_node(var._interleaved);
  func__32_1 = collect_node(func__32_1);
  var.types__inline = collect_node(var.types__inline);
  func__35_1 = collect_node(func__35_1);
  var._inline = collect_node(var._inline);
  func__36_1 = collect_node(func__36_1);
  var._NOT_INLINE = collect_node(var._NOT_INLINE);
  var._NEWLINE = collect_node(var._NEWLINE);
  var._INDENT = collect_node(var._INDENT);
  var._OUTDENT = collect_node(var._OUTDENT);
  var._HASHTAG = collect_node(var._HASHTAG);
  var._expect = collect_node(var._expect);
  string__42_4 = collect_node(string__42_4);
  func__42_1 = collect_node(func__42_1);
  var._ENUMERATE = collect_node(var._ENUMERATE);
  var._MAKE_A_DESTINATION = collect_node(var._MAKE_A_DESTINATION);
  var.sim2c__arguments_span = collect_node(var.sim2c__arguments_span);
  func__45_1 = collect_node(func__45_1);
  var.sim2c__output_arguments_span = collect_node(var.sim2c__output_arguments_span);
  func__46_1 = collect_node(func__46_1);
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
  var._REMARK_FIRST = collect_node(var._REMARK_FIRST);
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
  var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER = collect_node(var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER);
  var._POLYMORPHIC_FUNCTION_WITH_SETTER = collect_node(var._POLYMORPHIC_FUNCTION_WITH_SETTER);
  var._POLYMORPHIC_FUNCTION = collect_node(var._POLYMORPHIC_FUNCTION);
  var._ASSIGNMENT = collect_node(var._ASSIGNMENT);
  var._FUNCTOR = collect_node(var._FUNCTOR);
  var._RESULT_COUNT_OR_CONTINUATION = collect_node(var._RESULT_COUNT_OR_CONTINUATION);
  var._PROCEDURE_CALL = collect_node(var._PROCEDURE_CALL);
  var._INDENTED_REMARKS = collect_node(var._INDENTED_REMARKS);
  var._SINGLE_STATEMENT = collect_node(var._SINGLE_STATEMENT);
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
  string__207_8 = collect_node(string__207_8);
  func__207_1 = collect_node(func__207_1);
  var.sim2c__parse_statement = collect_node(var.sim2c__parse_statement);
  string__208_10 = collect_node(string__208_10);
  string__208_12 = collect_node(string__208_12);
  string__208_15 = collect_node(string__208_15);
  func__208_1 = collect_node(func__208_1);
  string__235_1 = collect_node(string__235_1);
  string__235_3 = collect_node(string__235_3);
  string__235_5 = collect_node(string__235_5);
  string__235_7 = collect_node(string__235_7);
  string__235_9 = collect_node(string__235_9);
  string__235_11 = collect_node(string__235_11);
  string__235_13 = collect_node(string__235_13);
  string__235_15 = collect_node(string__235_15);
  string__235_17 = collect_node(string__235_17);
  string__235_19 = collect_node(string__235_19);
  string__235_21 = collect_node(string__235_21);
  string__235_23 = collect_node(string__235_23);
  string__235_25 = collect_node(string__235_25);
  string__235_27 = collect_node(string__235_27);
  string__235_29 = collect_node(string__235_29);
  string__235_31 = collect_node(string__235_31);
  string__235_33 = collect_node(string__235_33);
  string__235_35 = collect_node(string__235_35);
  string__235_37 = collect_node(string__235_37);
  string__235_39 = collect_node(string__235_39);
  string__245_3 = collect_node(string__245_3);
  func__245_1 = collect_node(func__245_1);
  func__251_1 = collect_node(func__251_1);
  func__252_1 = collect_node(func__252_1);
  func__259_1 = collect_node(func__259_1);
  func__260_1 = collect_node(func__260_1);
  func__261_1 = collect_node(func__261_1);
  func__262_1 = collect_node(func__262_1);
  func__263_3 = collect_node(func__263_3);
  string__263_7 = collect_node(string__263_7);
  string__264_7 = collect_node(string__264_7);
  func__264_4 = collect_node(func__264_4);
  string__264_12 = collect_node(string__264_12);
  string__265_3 = collect_node(string__265_3);
  string__266_1 = collect_node(string__266_1);
  string__266_3 = collect_node(string__266_3);
  string__267_8 = collect_node(string__267_8);
  string__267_9 = collect_node(string__267_9);
  func__267_3 = collect_node(func__267_3);
  string__267_14 = collect_node(string__267_14);
  string__267_15 = collect_node(string__267_15);
  string__268_3 = collect_node(string__268_3);
  func__268_5 = collect_node(func__268_5);
  string__268_15 = collect_node(string__268_15);
  string__268_16 = collect_node(string__268_16);
  string__268_26 = collect_node(string__268_26);
  string__268_27 = collect_node(string__268_27);
  func__268_11 = collect_node(func__268_11);
  string__268_32 = collect_node(string__268_32);
  string__268_33 = collect_node(string__268_33);
  string__269_7 = collect_node(string__269_7);
  string__269_8 = collect_node(string__269_8);
  func__269_3 = collect_node(func__269_3);
  string__269_13 = collect_node(string__269_13);
  string__269_14 = collect_node(string__269_14);
  string__271_1 = collect_node(string__271_1);
  string__271_3 = collect_node(string__271_3);
  string__272_7 = collect_node(string__272_7);
  string__272_8 = collect_node(string__272_8);
  func__272_3 = collect_node(func__272_3);
  string__272_13 = collect_node(string__272_13);
  string__272_14 = collect_node(string__272_14);
  string__273_7 = collect_node(string__273_7);
  string__273_8 = collect_node(string__273_8);
  func__273_3 = collect_node(func__273_3);
  string__273_13 = collect_node(string__273_13);
  string__273_14 = collect_node(string__273_14);
  string__275_1 = collect_node(string__275_1);
  string__275_3 = collect_node(string__275_3);
  string__276_7 = collect_node(string__276_7);
  string__276_8 = collect_node(string__276_8);
  func__276_3 = collect_node(func__276_3);
  string__276_13 = collect_node(string__276_13);
  string__276_14 = collect_node(string__276_14);
  func__283_1 = collect_node(func__283_1);
  func__284_1 = collect_node(func__284_1);
  func__286_1 = collect_node(func__286_1);
  func__287_1 = collect_node(func__287_1);
  func__290_1 = collect_node(func__290_1);
  func__291_1 = collect_node(func__291_1);
  string__300_3 = collect_node(string__300_3);
  string__302_3 = collect_node(string__302_3);
  string__304_3 = collect_node(string__304_3);
  func__306_2 = collect_node(func__306_2);
  func__307_1 = collect_node(func__307_1);
  string__308_7 = collect_node(string__308_7);
  func__308_2 = collect_node(func__308_2);
  string__309_2 = collect_node(string__309_2);
  string__309_5 = collect_node(string__309_5);
  string__309_8 = collect_node(string__309_8);
  func__309_13 = collect_node(func__309_13);
  string__310_1 = collect_node(string__310_1);
  func__313_1 = collect_node(func__313_1);
  string__313_7 = collect_node(string__313_7);
  func__314_1 = collect_node(func__314_1);
  string__314_13 = collect_node(string__314_13);
  string__315_13 = collect_node(string__315_13);
  func__315_1 = collect_node(func__315_1);
  func__318_1 = collect_node(func__318_1);
  string__321_1 = collect_node(string__321_1);
  string__322_2 = collect_node(string__322_2);
  string__322_4 = collect_node(string__322_4);
  func__322_1 = collect_node(func__322_1);
  string__322_11 = collect_node(string__322_11);
  string__323_2 = collect_node(string__323_2);
  func__323_1 = collect_node(func__323_1);
  string__326_1 = collect_node(string__326_1);
  string__326_2 = collect_node(string__326_2);
  string__326_3 = collect_node(string__326_3);
  string__326_4 = collect_node(string__326_4);
  string__326_5 = collect_node(string__326_5);
  string__326_6 = collect_node(string__326_6);
  string__326_7 = collect_node(string__326_7);
  string__326_8 = collect_node(string__326_8);
  string__326_9 = collect_node(string__326_9);
  string__326_10 = collect_node(string__326_10);
  string__326_11 = collect_node(string__326_11);
  func__330_2 = collect_node(func__330_2);
  func__331_13 = collect_node(func__331_13);
  func__331_53 = collect_node(func__331_53);
  func__331_1 = collect_node(func__331_1);
  string__333_2 = collect_node(string__333_2);
  string__337_2 = collect_node(string__337_2);
  string__339_2 = collect_node(string__339_2);
  func__340_1 = collect_node(func__340_1);
  func__348_1 = collect_node(func__348_1);
  func__349_1 = collect_node(func__349_1);
  func__359_1 = collect_node(func__359_1);
  func__359_6 = collect_node(func__359_6);
  func__361_1 = collect_node(func__361_1);
  func__361_4 = collect_node(func__361_4);
  func__364_3 = collect_node(func__364_3);
  string__364_13 = collect_node(string__364_13);
  func__364_8 = collect_node(func__364_8);
  func__365_10 = collect_node(func__365_10);
  func__372_1 = collect_node(func__372_1);
  string__376_3 = collect_node(string__376_3);
  string__380_12 = collect_node(string__380_12);
  string__380_16 = collect_node(string__380_16);
  string__380_20 = collect_node(string__380_20);
  string__381_1 = collect_node(string__381_1);
  string__385_2 = collect_node(string__385_2);
  string__386_2 = collect_node(string__386_2);
  string__390_2 = collect_node(string__390_2);
  string__395_4 = collect_node(string__395_4);
  string__396_5 = collect_node(string__396_5);
  string__397_2 = collect_node(string__397_2);
  string__399_4 = collect_node(string__399_4);
  string__400_4 = collect_node(string__400_4);
  string__401_4 = collect_node(string__401_4);
  string__402_4 = collect_node(string__402_4);
  string__403_4 = collect_node(string__403_4);
  string__404_1 = collect_node(string__404_1);
  string__404_2 = collect_node(string__404_2);
  string__404_3 = collect_node(string__404_3);
  string__404_4 = collect_node(string__404_4);
  string__404_9 = collect_node(string__404_9);
  string__405_4 = collect_node(string__405_4);
  string__406_1 = collect_node(string__406_1);
  string__409_1 = collect_node(string__409_1);
  string__414_1 = collect_node(string__414_1);
  character__9 = collect_node(character__9);
  character__35 = collect_node(character__35);
  number__6 = collect_node(number__6);
  number__99 = collect_node(number__99);
  character__38 = collect_node(character__38);
  character__47 = collect_node(character__47);
  character__94 = collect_node(character__94);
  character__96 = collect_node(character__96);
  character__55 = collect_node(character__55);
  character__65 = collect_node(character__65);
  character__63 = collect_node(character__63);
  number__12 = collect_node(number__12);
  character__44 = collect_node(character__44);
  character__45 = collect_node(character__45);
  character__10 = collect_node(character__10);
  character__58 = collect_node(character__58);
  number__0 = collect_node(number__0);
  character__70 = collect_node(character__70);
  character__48 = collect_node(character__48);
  number__3 = collect_node(number__3);
  character__13 = collect_node(character__13);
  character__37 = collect_node(character__37);
  character__102 = collect_node(character__102);
  number__4 = collect_node(number__4);
  character__60 = collect_node(character__60);
  character__95 = collect_node(character__95);
  character__33 = collect_node(character__33);
  number__8 = collect_node(number__8);
  character__64 = collect_node(character__64);
  character__40 = collect_node(character__40);
  character__34 = collect_node(character__34);
  number__7 = collect_node(number__7);
  character__36 = collect_node(character__36);
  number__5 = collect_node(number__5);
  character__123 = collect_node(character__123);
  character__39 = collect_node(character__39);
  number__9 = collect_node(number__9);
  character__32 = collect_node(character__32);
  character__61 = collect_node(character__61);
  number__11 = collect_node(number__11);
  character__125 = collect_node(character__125);
  character__43 = collect_node(character__43);
  character__101 = collect_node(character__101);
  number__13 = collect_node(number__13);
  character__41 = collect_node(character__41);
  character__124 = collect_node(character__124);
  character__59 = collect_node(character__59);
  character__97 = collect_node(character__97);
  number__1 = collect_node(number__1);
  character__69 = collect_node(character__69);
  character__49 = collect_node(character__49);
  character__46 = collect_node(character__46);
  number__2 = collect_node(number__2);
  character__42 = collect_node(character__42);
  number__10 = collect_node(number__10);
  character__62 = collect_node(character__62);
  number__14 = collect_node(number__14);
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
  set_module("parser");
  set_used_namespaces(used_namespaces);
  character__9 = create_future();
  character__35 = create_future();
  number__6 = create_future();
  number__99 = create_future();
  character__38 = create_future();
  character__47 = create_future();
  character__94 = create_future();
  character__96 = create_future();
  character__55 = create_future();
  character__65 = create_future();
  character__63 = create_future();
  number__12 = create_future();
  character__44 = create_future();
  character__45 = create_future();
  character__10 = create_future();
  character__58 = create_future();
  number__0 = create_future();
  character__70 = create_future();
  character__48 = create_future();
  number__3 = create_future();
  character__13 = create_future();
  character__37 = create_future();
  character__102 = create_future();
  number__4 = create_future();
  character__60 = create_future();
  character__95 = create_future();
  character__33 = create_future();
  number__8 = create_future();
  character__64 = create_future();
  character__40 = create_future();
  character__34 = create_future();
  number__7 = create_future();
  character__36 = create_future();
  number__5 = create_future();
  character__123 = create_future();
  character__39 = create_future();
  number__9 = create_future();
  character__32 = create_future();
  character__61 = create_future();
  number__11 = create_future();
  character__125 = create_future();
  character__43 = create_future();
  character__101 = create_future();
  number__13 = create_future();
  character__41 = create_future();
  character__124 = create_future();
  character__59 = create_future();
  character__97 = create_future();
  number__1 = create_future();
  character__69 = create_future();
  character__49 = create_future();
  character__46 = create_future();
  number__2 = create_future();
  character__42 = create_future();
  number__10 = create_future();
  character__62 = create_future();
  number__14 = create_future();
  string__1_2 = from_latin_1_string("std", 3);
  func__1_1 = create_future();
  define_single_assign_static("sim2c", "std_identifier", get__sim2c__std_identifier, &var.sim2c__std_identifier);
  string__2_36 = from_latin_1_string("        ", 8);
  string__2_52 = from_latin_1_string(":", 1);
  string__2_53 = from_latin_1_string(":", 1);
  string__2_54 = from_latin_1_string(": ", 2);
  string__2_55 = from_latin_1_string("\012", 1);
  string__2_58 = from_latin_1_string("____________________________________\012", 37);
  string__2_59 = from_latin_1_string(" IN LINE ", 9);
  string__2_60 = from_latin_1_string(" OF FILE \042", 10);
  string__2_61 = from_latin_1_string("\042:\012", 3);
  string__2_62 = from_latin_1_string("!\012", 2);
  string__2_66 = from_latin_1_string(" ", 1);
  string__2_68 = from_latin_1_string("^", 1);
  func__2_1 = create_future();
  string__3_4 = from_latin_1_string("WARNING", 7);
  func__3_1 = create_future();
  define_single_assign_static("sim2c", "Warning", get__sim2c__Warning, &var.sim2c__Warning);
  string__4_2 = from_latin_1_string("SYNTAX ERROR", 12);
  func__4_1 = create_future();
  func__5_1 = create_future();
  define_single_assign_static("sim2c", "SyntaxError", get__sim2c__SyntaxError, &var.sim2c__SyntaxError);
  func__6_1 = create_future();
  define_single_assign_static("types", "syntax_error", get__types__syntax_error, &var.types__syntax_error);
  func__8_1 = create_future();
  func__9_1 = create_future();
  define_single_assign_static("types", "unexpected_input_error", get__types__unexpected_input_error, &var.types__unexpected_input_error);
  string__11_9 = from_latin_1_string("newline expected", 16);
  string__11_11 = from_latin_1_string("indent expected", 15);
  string__11_13 = from_latin_1_string("unexpected input", 16);
  string__11_15 = from_latin_1_string("\042", 1);
  string__11_16 = from_latin_1_string("\042 expected", 10);
  string__11_19 = from_latin_1_string("unexpected input", 16);
  func__11_1 = create_future();
  func__12_1 = create_future();
  define_single_assign_static("types", "print", get__types__print, &var.types__print);
  func__14_1 = create_future();
  func__15_1 = create_future();
  string__17_2 = from_latin_1_string("<<<<<<<<<<", 10);
  string__17_6 = from_latin_1_string(">>>>>>>>>>", 10);
  func__17_1 = create_future();
  func__18_18 = create_future();
  func__18_26 = create_future();
  func__18_34 = create_future();
  func__18_42 = create_future();
  func__18_1 = create_future();
  define_single_assign_static("sim2c", "strip", get__sim2c__strip, &var.sim2c__strip);
  string__20_3 = from_latin_1_string("strip(grammar::current_node)", 28);
  func__20_1 = create_future();
  string__22_3 = from_latin_1_string("strip(grammar::current_node)", 28);
  func__22_1 = create_future();
  string__24_3 = from_latin_1_string("strip(grammar::current_node)", 28);
  func__24_1 = create_future();
  define_single_assign_static("sim2c", "HIGHEST_PRECEDENCE", get__sim2c__HIGHEST_PRECEDENCE, &var.sim2c__HIGHEST_PRECEDENCE);
  define_single_assign_static("sim2c", "INFIX_PRECEDENCE", get__sim2c__INFIX_PRECEDENCE, &var.sim2c__INFIX_PRECEDENCE);
  var._precedence_table = create_future();
  func__28_5 = create_future();
  func__28_1 = create_future();
  define_single_assign_static("sim2c", "precedence", get__sim2c__precedence, &var.sim2c__precedence);
  func__29_1 = create_future();
  define_single_assign_static("sim2c", "is_left_associative", get__sim2c__is_left_associative, &var.sim2c__is_left_associative);
  func__30_1 = create_future();
  func__31_1 = create_future();
  func__32_1 = create_future();
  register_dynamic(&dyna_idx__within_inline_expression);
  define__within_inline_expression(create_future());
  define_single_assign_static("types", "inline", get__types__inline, &var.types__inline);
  func__35_1 = create_future();
  func__36_1 = create_future();
  var._NOT_INLINE = create_future();
  var._NEWLINE = create_future();
  var._INDENT = create_future();
  var._OUTDENT = create_future();
  var._HASHTAG = create_future();
  string__42_4 = from_latin_1_string(" expected", 9);
  func__42_1 = create_future();
  var._ENUMERATE = create_future();
  var._MAKE_A_DESTINATION = create_future();
  func__45_1 = create_future();
  define_single_assign_static("sim2c", "arguments_span", get__sim2c__arguments_span, &var.sim2c__arguments_span);
  func__46_1 = create_future();
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
  var._REMARK_FIRST = create_future();
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
  var._POLYMORPHIC_FUNCTION_WITHOUT_SETTER = create_future();
  var._POLYMORPHIC_FUNCTION_WITH_SETTER = create_future();
  var._POLYMORPHIC_FUNCTION = create_future();
  var._ASSIGNMENT = create_future();
  var._FUNCTOR = create_future();
  var._RESULT_COUNT_OR_CONTINUATION = create_future();
  var._PROCEDURE_CALL = create_future();
  var._INDENTED_REMARKS = create_future();
  var._SINGLE_STATEMENT = create_future();
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
  string__207_8 = from_latin_1_string("invalid meta instruction", 24);
  func__207_1 = create_future();
  define_single_assign_static("sim2c", "parse_meta_instruction", get__sim2c__parse_meta_instruction, &var.sim2c__parse_meta_instruction);
  string__208_10 = from_latin_1_string("superficious input at end of expression", 39);
  string__208_12 = from_latin_1_string("________________________________________", 40);
  string__208_15 = from_latin_1_string("no match", 8);
  func__208_1 = create_future();
  define_single_assign_static("sim2c", "parse_statement", get__sim2c__parse_statement, &var.sim2c__parse_statement);
  string__235_1 = from_latin_1_string("*", 1);
  string__235_3 = from_latin_1_string("/", 1);
  string__235_5 = from_latin_1_string("+", 1);
  string__235_7 = from_latin_1_string("-", 1);
  string__235_9 = from_latin_1_string("<<", 2);
  string__235_11 = from_latin_1_string(">>", 2);
  string__235_13 = from_latin_1_string("&", 1);
  string__235_15 = from_latin_1_string("^", 1);
  string__235_17 = from_latin_1_string("|", 1);
  string__235_19 = from_latin_1_string("<=", 2);
  string__235_21 = from_latin_1_string("<", 1);
  string__235_23 = from_latin_1_string(">=", 2);
  string__235_25 = from_latin_1_string(">", 1);
  string__235_27 = from_latin_1_string("==", 2);
  string__235_29 = from_latin_1_string("!=", 2);
  string__235_31 = from_latin_1_string("&&", 2);
  string__235_33 = from_latin_1_string("||", 2);
  string__235_35 = from_latin_1_string("..", 2);
  string__235_37 = from_latin_1_string(",", 1);
  string__235_39 = from_latin_1_string("=", 1);
  string__245_3 = from_latin_1_string("\042)\042 expected", 12);
  func__245_1 = create_future();
  func__251_1 = create_future();
  func__252_1 = create_future();
  func__259_1 = create_future();
  func__260_1 = create_future();
  func__261_1 = create_future();
  func__262_1 = create_future();
  func__263_3 = create_future();
  string__263_7 = from_latin_1_string("::", 2);
  string__264_7 = from_latin_1_string("namespace must not start with an underscore", 43);
  func__264_4 = create_future();
  string__264_12 = from_latin_1_string("::", 2);
  string__265_3 = from_latin_1_string("::", 2);
  string__266_1 = from_latin_1_string("./", 2);
  string__266_3 = from_latin_1_string("/", 1);
  string__267_8 = from_latin_1_string("the module \042", 12);
  string__267_9 = from_latin_1_string("\042 is required twice", 19);
  func__267_3 = create_future();
  string__267_14 = from_latin_1_string("<require", 8);
  string__267_15 = from_latin_1_string(">", 1);
  string__268_3 = from_latin_1_string("=", 1);
  func__268_5 = create_future();
  string__268_15 = from_latin_1_string("the namespace \042", 15);
  string__268_16 = from_latin_1_string("\042 is defined twice", 18);
  string__268_26 = from_latin_1_string("the namespace alias \042", 21);
  string__268_27 = from_latin_1_string("\042 is defined twice", 18);
  func__268_11 = create_future();
  string__268_32 = from_latin_1_string("<namespace", 10);
  string__268_33 = from_latin_1_string(">", 1);
  string__269_7 = from_latin_1_string("the namespace \042", 15);
  string__269_8 = from_latin_1_string("\042 is used twice", 15);
  func__269_3 = create_future();
  string__269_13 = from_latin_1_string("<using", 6);
  string__269_14 = from_latin_1_string(">", 1);
  string__271_1 = from_latin_1_string("../", 3);
  string__271_3 = from_latin_1_string("./", 2);
  string__272_7 = from_latin_1_string("the file \042", 10);
  string__272_8 = from_latin_1_string("\042 is included twice", 19);
  func__272_3 = create_future();
  string__272_13 = from_latin_1_string("<include", 8);
  string__272_14 = from_latin_1_string(">", 1);
  string__273_7 = from_latin_1_string("the library \042", 13);
  string__273_8 = from_latin_1_string("\042 is linked twice", 17);
  func__273_3 = create_future();
  string__273_13 = from_latin_1_string("<link", 5);
  string__273_14 = from_latin_1_string(">", 1);
  string__275_1 = from_latin_1_string("../", 3);
  string__275_3 = from_latin_1_string("./", 2);
  string__276_7 = from_latin_1_string("the data dependency \042", 21);
  string__276_8 = from_latin_1_string("\042 is defined twice", 18);
  func__276_3 = create_future();
  string__276_13 = from_latin_1_string("<data", 5);
  string__276_14 = from_latin_1_string(">", 1);
  func__283_1 = create_future();
  func__284_1 = create_future();
  func__286_1 = create_future();
  func__287_1 = create_future();
  func__290_1 = create_future();
  func__291_1 = create_future();
  string__300_3 = from_latin_1_string("0b", 2);
  string__302_3 = from_latin_1_string("0o", 2);
  string__304_3 = from_latin_1_string("0x", 2);
  func__306_2 = create_future();
  func__307_1 = create_future();
  string__308_7 = from_latin_1_string("invalid character name", 22);
  func__308_2 = create_future();
  string__309_2 = from_latin_1_string("0b", 2);
  string__309_5 = from_latin_1_string("0o", 2);
  string__309_8 = from_latin_1_string("0x", 2);
  func__309_13 = create_future();
  string__310_1 = from_latin_1_string("invalid special character", 25);
  func__313_1 = create_future();
  string__313_7 = from_latin_1_string("@;", 2);
  func__314_1 = create_future();
  string__314_13 = from_latin_1_string("@(", 2);
  string__315_13 = from_latin_1_string("string", 6);
  func__315_1 = create_future();
  func__318_1 = create_future();
  string__321_1 = from_latin_1_string("expression expected", 19);
  string__322_2 = from_latin_1_string("key_value_pair", 14);
  string__322_4 = from_latin_1_string("true", 4);
  func__322_1 = create_future();
  string__322_11 = from_latin_1_string("--", 2);
  string__323_2 = from_latin_1_string("-", 1);
  func__323_1 = create_future();
  string__326_1 = from_latin_1_string("<<", 2);
  string__326_2 = from_latin_1_string("<=", 2);
  string__326_3 = from_latin_1_string("<", 1);
  string__326_4 = from_latin_1_string(">>", 2);
  string__326_5 = from_latin_1_string(">=", 2);
  string__326_6 = from_latin_1_string(">", 1);
  string__326_7 = from_latin_1_string("&&", 2);
  string__326_8 = from_latin_1_string("||", 2);
  string__326_9 = from_latin_1_string("==", 2);
  string__326_10 = from_latin_1_string("!=", 2);
  string__326_11 = from_latin_1_string("..", 2);
  func__330_2 = create_future();
  func__331_13 = create_future();
  func__331_53 = create_future();
  func__331_1 = create_future();
  string__333_2 = from_latin_1_string("identifier", 10);
  string__337_2 = from_latin_1_string("$$", 2);
  string__339_2 = from_latin_1_string("%%", 2);
  func__340_1 = create_future();
  func__348_1 = create_future();
  func__349_1 = create_future();
  func__359_1 = create_future();
  func__359_6 = create_future();
  func__361_1 = create_future();
  func__361_4 = create_future();
  func__364_3 = create_future();
  string__364_13 = from_latin_1_string("too few arguments in multi-line expression", 42);
  func__364_8 = create_future();
  func__365_10 = create_future();
  func__372_1 = create_future();
  string__376_3 = from_latin_1_string("->", 2);
  string__380_12 = from_latin_1_string("statement expected", 18);
  string__380_16 = from_latin_1_string("statement expected", 18);
  string__380_20 = from_latin_1_string("statement expected", 18);
  string__381_1 = from_latin_1_string("->", 2);
  string__385_2 = from_latin_1_string("()", 2);
  string__386_2 = from_latin_1_string("(!)", 3);
  string__390_2 = from_latin_1_string(".(", 2);
  string__395_4 = from_latin_1_string("->", 2);
  string__396_5 = from_latin_1_string("statement expected", 18);
  string__397_2 = from_latin_1_string("__", 2);
  string__399_4 = from_latin_1_string("argument", 8);
  string__400_4 = from_latin_1_string("base", 4);
  string__401_4 = from_latin_1_string("kind", 4);
  string__402_4 = from_latin_1_string("name", 4);
  string__403_4 = from_latin_1_string("node", 4);
  string__404_1 = from_latin_1_string("runtime", 7);
  string__404_2 = from_latin_1_string("global", 6);
  string__404_3 = from_latin_1_string("local", 5);
  string__404_4 = from_latin_1_string("extern", 6);
  string__404_9 = from_latin_1_string("scope", 5);
  string__405_4 = from_latin_1_string("type", 4);
  string__406_1 = from_latin_1_string("invalid annotation tag", 22);
  string__409_1 = from_latin_1_string("//", 2);
  string__414_1 = from_latin_1_string("top-level statement expected", 28);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__parser(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
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
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  define_method("types", "syntax_error", poly_idx__grammar__match, func__8_1);
  define_method("types", "unexpected_input_error", poly_idx__grammar__match, func__11_1);
  define_method("types", "print", poly_idx__grammar__match, func__14_1);
  update_start_p = node_p;
  def_attribute(&var._dump_stream, poly_idx__grammar__match, func__17_1);
  update_start_p = node_p;
  def_attribute(&var._dump, poly_idx__grammar__match, func__20_1);
  update_start_p = node_p;
  def_attribute(&var._dump3, poly_idx__grammar__match, func__22_1);
  update_start_p = node_p;
  def_attribute(&var._dump5, poly_idx__grammar__match, func__24_1);
  define_method("types", "inline", poly_idx__grammar__match, func__35_1);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__parser(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&character__9, from_uchar32(9));
  assign_value(&character__35, from_uchar32(35));
  assign_value(&number__6, from_uint32(6U));
  assign_value(&number__99, from_uint32(99U));
  assign_value(&character__38, from_uchar32(38));
  assign_value(&character__47, from_uchar32(47));
  assign_value(&character__94, from_uchar32(94));
  assign_value(&character__96, from_uchar32(96));
  assign_value(&character__55, from_uchar32(55));
  assign_value(&character__65, from_uchar32(65));
  assign_value(&character__63, from_uchar32(63));
  assign_value(&number__12, from_uint32(12U));
  assign_value(&character__44, from_uchar32(44));
  assign_value(&character__45, from_uchar32(45));
  assign_value(&character__10, from_uchar32(10));
  assign_value(&character__58, from_uchar32(58));
  assign_value(&number__0, from_uint32(0U));
  assign_value(&character__70, from_uchar32(70));
  assign_value(&character__48, from_uchar32(48));
  assign_value(&number__3, from_uint32(3U));
  assign_value(&character__13, from_uchar32(13));
  assign_value(&character__37, from_uchar32(37));
  assign_value(&character__102, from_uchar32(102));
  assign_value(&number__4, from_uint32(4U));
  assign_value(&character__60, from_uchar32(60));
  assign_value(&character__95, from_uchar32(95));
  assign_value(&character__33, from_uchar32(33));
  assign_value(&number__8, from_uint32(8U));
  assign_value(&character__64, from_uchar32(64));
  assign_value(&character__40, from_uchar32(40));
  assign_value(&character__34, from_uchar32(34));
  assign_value(&number__7, from_uint32(7U));
  assign_value(&character__36, from_uchar32(36));
  assign_value(&number__5, from_uint32(5U));
  assign_value(&character__123, from_uchar32(123));
  assign_value(&character__39, from_uchar32(39));
  assign_value(&number__9, from_uint32(9U));
  assign_value(&character__32, from_uchar32(32));
  assign_value(&character__61, from_uchar32(61));
  assign_value(&number__11, from_uint32(11U));
  assign_value(&character__125, from_uchar32(125));
  assign_value(&character__43, from_uchar32(43));
  assign_value(&character__101, from_uchar32(101));
  assign_value(&number__13, from_uint32(13U));
  assign_value(&character__41, from_uchar32(41));
  assign_value(&character__124, from_uchar32(124));
  assign_value(&character__59, from_uchar32(59));
  assign_value(&character__97, from_uchar32(97));
  assign_value(&number__1, from_uint32(1U));
  assign_value(&character__69, from_uchar32(69));
  assign_value(&character__49, from_uchar32(49));
  assign_value(&character__46, from_uchar32(46));
  assign_value(&number__2, from_uint32(2U));
  assign_value(&character__42, from_uchar32(42));
  assign_value(&number__10, from_uint32(10U));
  assign_value(&character__62, from_uchar32(62));
  assign_value(&number__14, from_uint32(14U));
  assign_variable(&var.sim2c__std_identifier, &func__1_1);
  assign_variable(&var._print_message, &func__2_1);
  assign_variable(&var.sim2c__Warning, &func__3_1);
  assign_variable(&var._ExitWithSyntaxError, &func__4_1);
  assign_variable(&var.sim2c__SyntaxError, &func__5_1);
  assign_variable(&var._ParseError, &func__6_1);
  assign_value(&var.types__syntax_error, get__types__grammar_object());
  assign_variable(&var._syntax_error, &func__9_1);
  assign_value(&var.types__unexpected_input_error, get__types__grammar_object());
  assign_variable(&var._unexpected_input_error, &func__12_1);
  assign_value(&var.types__print, get__types__grammar_object());
  assign_variable(&var._print, &func__15_1);
  assign_value(&var._dump_stream, get__types__grammar_object());
  assign_variable(&var.sim2c__strip, &func__18_1);
  assign_value(&var._dump, get__types__grammar_object());
  assign_value(&var._dump3, get__types__grammar_object());
  assign_value(&var._dump5, get__types__grammar_object());
  assign_value(&var.sim2c__HIGHEST_PRECEDENCE, number__99);
  assign_value(&var.sim2c__INFIX_PRECEDENCE, number__6);
  assign_variable(&var.sim2c__precedence, &func__28_1);
  assign_variable(&var.sim2c__is_left_associative, &func__29_1);
  assign_variable(&var._is_right_associative, &func__30_1);
  assign_variable(&var._infix_operator, &func__31_1);
  assign_variable(&var._interleaved, &func__32_1);
  maybe_initialize_future(get__within_inline_expression(), get__false());
  assign_value(&var.types__inline, get__types__grammar_object());
  assign_variable(&var._inline, &func__36_1);
  assign_variable(&var._expect, &func__42_1);
  assign_variable(&var.sim2c__arguments_span, &func__45_1);
  assign_variable(&var.sim2c__output_arguments_span, &func__46_1);
  assign_value(&var._original_remark_lines_of, create_function(type__original_remark_lines_of, -1));
  assign_variable(&var.sim2c__parse_meta_instruction, &func__207_1);
  assign_variable(&var.sim2c__parse_statement, &func__208_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__parser(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__1_1, create_function(entry__1_1, 1));
  assign_value(&func__2_1, create_function(entry__2_1, 4));
  assign_value(&func__3_1, create_function(entry__3_1, 2));
  assign_value(&func__4_1, create_function(entry__4_1, 3));
  assign_value(&func__5_1, create_function(entry__5_1, 2));
  assign_value(&func__6_1, create_function(entry__6_1, 2));
  assign_value(&func__8_1, create_function(entry__8_1, 2));
  assign_value(&func__9_1, create_function(entry__9_1, 1));
  assign_value(&func__11_1, create_function(entry__11_1, 2));
  assign_value(&func__12_1, create_function(entry__12_1, 1));
  assign_value(&func__14_1, create_function(entry__14_1, 2));
  assign_value(&func__15_1, create_function(entry__15_1, 1));
  assign_value(&func__17_1, create_function(entry__17_1, 2));
  assign_value(&func__18_18, create_function(entry__18_18, 1));
  assign_value(&func__18_26, create_function(entry__18_26, 1));
  assign_value(&func__18_34, create_function(entry__18_34, 1));
  assign_value(&func__18_42, create_function(entry__18_42, 1));
  assign_value(&func__18_1, create_function(entry__18_1, 1));
  assign_value(&func__20_1, create_function(entry__20_1, 2));
  assign_value(&func__22_1, create_function(entry__22_1, 2));
  assign_value(&func__24_1, create_function(entry__24_1, 2));
  assign_value(&func__28_5, create_function(entry__28_5, 0));
  assign_value(&func__28_1, create_function(entry__28_1, 1));
  assign_value(&func__29_1, create_function(entry__29_1, 1));
  assign_value(&func__30_1, create_function(entry__30_1, 1));
  assign_value(&func__31_1, create_function(entry__31_1, 1));
  assign_value(&func__32_1, create_function(entry__32_1, 2));
  assign_value(&func__35_1, create_function(entry__35_1, 2));
  assign_value(&func__36_1, create_function(entry__36_1, 1));
  assign_value(&func__42_1, create_function(entry__42_1, -1));
  assign_value(&func__45_1, create_function(entry__45_1, 1));
  assign_value(&func__46_1, create_function(entry__46_1, 1));
  assign_value(&func__207_1, create_function(entry__207_1, 1));
  assign_value(&func__208_1, create_function(entry__208_1, 1));
  assign_value(&func__245_1, create_function(entry__245_1, 2));
  assign_value(&func__251_1, create_function(entry__251_1, 1));
  assign_value(&func__252_1, create_function(entry__252_1, 1));
  assign_value(&func__259_1, create_function(entry__259_1, 2));
  assign_value(&func__260_1, create_function(entry__260_1, 2));
  assign_value(&func__261_1, create_function(entry__261_1, 2));
  assign_value(&func__262_1, create_function(entry__262_1, 2));
  assign_value(&func__263_3, create_function(entry__263_3, 1));
  assign_value(&func__264_4, create_function(entry__264_4, 1));
  assign_value(&func__267_3, create_function(entry__267_3, 2));
  assign_value(&func__268_5, create_function(entry__268_5, 1));
  assign_value(&func__268_11, create_function(entry__268_11, 2));
  assign_value(&func__269_3, create_function(entry__269_3, 2));
  assign_value(&func__272_3, create_function(entry__272_3, 2));
  assign_value(&func__273_3, create_function(entry__273_3, 2));
  assign_value(&func__276_3, create_function(entry__276_3, 2));
  assign_value(&func__283_1, create_function(entry__283_1, 1));
  assign_value(&func__284_1, create_function(entry__284_1, 2));
  assign_value(&func__286_1, create_function(entry__286_1, 1));
  assign_value(&func__287_1, create_function(entry__287_1, 1));
  assign_value(&func__290_1, create_function(entry__290_1, 1));
  assign_value(&func__291_1, create_function(entry__291_1, 1));
  assign_value(&func__306_2, create_function(entry__306_2, 1));
  assign_value(&func__307_1, create_function(entry__307_1, 1));
  assign_value(&func__308_2, create_function(entry__308_2, 2));
  assign_value(&func__309_13, create_function(entry__309_13, 1));
  assign_value(&func__313_1, create_function(entry__313_1, 1));
  assign_value(&func__314_1, create_function(entry__314_1, 1));
  assign_value(&func__315_1, create_function(entry__315_1, 1));
  assign_value(&func__318_1, create_function(entry__318_1, 1));
  assign_value(&func__322_1, create_function(entry__322_1, 1));
  assign_value(&func__323_1, create_function(entry__323_1, 1));
  assign_value(&func__330_2, create_function(entry__330_2, 1));
  assign_value(&func__331_13, create_function(entry__331_13, 0));
  assign_value(&func__331_53, create_function(entry__331_53, 0));
  assign_value(&func__331_1, create_function(entry__331_1, 1));
  assign_value(&func__340_1, create_function(entry__340_1, 1));
  assign_value(&func__348_1, create_function(entry__348_1, 1));
  assign_value(&func__349_1, create_function(entry__349_1, 1));
  assign_value(&func__359_1, create_function(entry__359_1, 1));
  assign_value(&func__359_6, create_function(entry__359_6, 1));
  assign_value(&func__361_1, create_function(entry__361_1, 1));
  assign_value(&func__361_4, create_function(entry__361_4, 1));
  assign_value(&func__364_3, create_function(entry__364_3, 1));
  assign_value(&func__364_8, create_function(entry__364_8, 2));
  assign_value(&func__365_10, create_function(entry__365_10, 1));
  assign_value(&func__372_1, create_function(entry__372_1, 1));
  register_collector(collect__parser);
}
