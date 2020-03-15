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
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
REGISTER int argument_count ASM("ebx");
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT NODE *get_attribute(NODE *node, int idx);
IMPORT NODE *clone_object_and_attributes(NODE *node);
IMPORT void *update_start_p;
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT NODE *create_continuation(void);
IMPORT NODE *undefined;
IMPORT NODE *create_cell(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *empty_string;
typedef struct SIMPLE_NODE {
  FUNC type;
  struct ATTRIBUTES *attributes;
} SIMPLE_NODE;
IMPORT void terminate(int exit_code);
IMPORT NODE *create_continuation_with_exit(FUNC exit_func);
IMPORT void continuation_type_function(void);
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void define_type_function(
  const char *namespace, const char *name, FUNC type, int par_cnt
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *collect_node(NODE *node);
IMPORT int main_argc;
IMPORT char **main_argv;
IMPORT void initialize_runtime(void);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void resolve_symbols(void);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void initialize_phase_3(void);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
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
IMPORT void use_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
);
IMPORT void resolve_attributes(void);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *from_double(double val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint64(uint64_t val);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_digit_string(const char *str);
IMPORT void initialize_function_attributes(void);
IMPORT void register_collector(FUNC collector);
IMPORT __attribute__ ((noreturn)) void execute(FUNC entry);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT NODE *create_function(FUNC func, int par_count);


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
static NODE_GETTER get__ATTRIBUTE_KIND;
static NODE_GETTER get_value_or_future__ATTRIBUTE_KIND;
static NODE_GETTER get__DYNAMIC_MULTI;
static NODE_GETTER get_value_or_future__DYNAMIC_MULTI;
static NODE_GETTER get__DYNAMIC_SINGLE;
static NODE_GETTER get_value_or_future__DYNAMIC_SINGLE;
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__METHOD_KIND;
static NODE_GETTER get_value_or_future__METHOD_KIND;
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
static NODE_GETTER get__annotate_statement;
static NODE_GETTER get_value_or_future__annotate_statement;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__attribute_kind_of;
static NODE_GETTER get_value_or_future__attribute_kind_of;
static NODE_GETTER get__attribute_of;
static NODE_GETTER get_value_or_future__attribute_of;
static NODE_GETTER get__before;
static NODE_GETTER get_value_or_future__before;
static NODE_GETTER get__begin_continuation;
static NODE_GETTER get_value_or_future__begin_continuation;
static NODE_GETTER get__behind;
static NODE_GETTER get_value_or_future__behind;
static NODE_GETTER get__c_code;
static NODE_GETTER get_value_or_future__c_code;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__check_definitions;
static NODE_GETTER get_value_or_future__check_definitions;
static NODE_GETTER get__check_usage;
static NODE_GETTER get_value_or_future__check_usage;
static NODE_GETTER get__collect_output;
static NODE_GETTER get_value_or_future__collect_output;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__contains;
static NODE_GETTER get_value_or_future__contains;
static NODE_GETTER get__count_occurrences;
static NODE_GETTER get_value_or_future__count_occurrences;
static NODE_GETTER get__cut_into_fragments;
static NODE_GETTER get_value_or_future__cut_into_fragments;
static NODE_GETTER get__debug_string;
static NODE_GETTER get_value_or_future__debug_string;
static NODE_GETTER get__define_attribute;
static NODE_GETTER get_value_or_future__define_attribute;
static NODE_GETTER get__define_c_code;
static NODE_GETTER get_value_or_future__define_c_code;
static NODE_GETTER get__define_method;
static NODE_GETTER get_value_or_future__define_method;
static NODE_GETTER get__define_polymorphic_function;
static NODE_GETTER get_value_or_future__define_polymorphic_function;
static NODE_GETTER get__define_type_function;
static NODE_GETTER get_value_or_future__define_type_function;
static NODE_GETTER get__define_variable;
static NODE_GETTER get_value_or_future__define_variable;
static NODE_GETTER get__defined_nodes;
static NODE_GETTER get_value_or_future__defined_nodes;
static NODE_GETTER get__definitions;
static NODE_SETTER set__definitions;
static NODE_SETTER define__definitions;
static NODE_GETTER get__delayed_code;
static NODE_GETTER get_value_or_future__delayed_code;
static NODE_GETTER get__dependent_data;
static NODE_GETTER get_value_or_future__dependent_data;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__do_check_only;
static NODE_GETTER get_value_or_future__do_check_only;
static NODE_GETTER get__do_dump_trees;
static NODE_GETTER get_value_or_future__do_dump_trees;
static NODE_GETTER get__do_pretty_print;
static NODE_GETTER get_value_or_future__do_pretty_print;
static NODE_GETTER get__do_print_simplified_source;
static NODE_GETTER get_value_or_future__do_print_simplified_source;
static NODE_GETTER get__do_print_warnings;
static NODE_GETTER get_value_or_future__do_print_warnings;
static NODE_GETTER get__do_show_debug_infos;
static NODE_GETTER get_value_or_future__do_show_debug_infos;
static NODE_GETTER get__do_time_passes;
static NODE_GETTER get_value_or_future__do_time_passes;
static NODE_GETTER get__empty_insert_order_set;
static NODE_GETTER get_value_or_future__empty_insert_order_set;
static NODE_GETTER get__empty_insert_order_table;
static NODE_GETTER get_value_or_future__empty_insert_order_table;
static NODE_GETTER get__empty_key_order_table;
static NODE_GETTER get_value_or_future__empty_key_order_table;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_set;
static NODE_GETTER get_value_or_future__empty_set;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static NODE_GETTER get__end_continuation;
static NODE_GETTER get_value_or_future__end_continuation;
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__ewriteln;
static NODE_GETTER get_value_or_future__ewriteln;
static NODE_GETTER get__expand_statement;
static NODE_GETTER get_value_or_future__expand_statement;
static NODE_GETTER get__exported_names;
static NODE_SETTER set__exported_names;
static NODE_GETTER get__extend_to;
static NODE_GETTER get_value_or_future__extend_to;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__from_to;
static NODE_GETTER get_value_or_future__from_to;
static NODE_GETTER get__from_utf8;
static NODE_GETTER get_value_or_future__from_utf8;
static int poly_idx__functor_of;
static NODE_GETTER get__functor_of;
static NODE_GETTER get__generate_statement;
static NODE_GETTER get_value_or_future__generate_statement;
static NODE_GETTER get__global_names;
static NODE_SETTER set__global_names;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__identifier_of;
static NODE_GETTER get_value_or_future__identifier_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__included_files;
static NODE_SETTER set__included_files;
static NODE_GETTER get__indent_marker;
static NODE_GETTER get_value_or_future__indent_marker;
static NODE_GETTER get__is_a_character_literal;
static NODE_GETTER get_value_or_future__is_a_character_literal;
static NODE_GETTER get__is_a_key_value_pair;
static NODE_GETTER get_value_or_future__is_a_key_value_pair;
static NODE_GETTER get__is_a_meta_instruction;
static NODE_GETTER get_value_or_future__is_a_meta_instruction;
static NODE_GETTER get__is_a_numeric_literal;
static NODE_GETTER get_value_or_future__is_a_numeric_literal;
static NODE_GETTER get__is_a_polymorphic_function_constant;
static NODE_GETTER get_value_or_future__is_a_polymorphic_function_constant;
static NODE_GETTER get__is_a_remark;
static NODE_GETTER get_value_or_future__is_a_remark;
static NODE_GETTER get__is_a_setter;
static NODE_GETTER get_value_or_future__is_a_setter;
static NODE_GETTER get__is_a_static_single_definition;
static NODE_GETTER get_value_or_future__is_a_static_single_definition;
static NODE_GETTER get__is_c_code;
static NODE_GETTER get_value_or_future__is_c_code;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__key_of;
static NODE_GETTER get_value_or_future__key_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__linked_libraries;
static NODE_GETTER get_value_or_future__linked_libraries;
static NODE_GETTER get__load;
static NODE_GETTER get_value_or_future__load;
static NODE_GETTER get__module_name;
static NODE_GETTER get_value_or_future__module_name;
static NODE_GETTER get__name_of;
static NODE_GETTER get_value_or_future__name_of;
static NODE_GETTER get__namespace_of;
static NODE_GETTER get_value_or_future__namespace_of;
static NODE_GETTER get__needed_names;
static NODE_SETTER set__needed_names;
static NODE_GETTER get__newline;
static NODE_GETTER get_value_or_future__newline;
static NODE_GETTER get__next_continuation;
static NODE_GETTER get_value_or_future__next_continuation;
static NODE_GETTER get__node__value_of;
static NODE_GETTER get_value_or_future__node__value_of;
static NODE_GETTER get__not;
static NODE_GETTER get_value_or_future__not;
static NODE_GETTER get__outdent_marker;
static NODE_GETTER get_value_or_future__outdent_marker;
static NODE_GETTER get__parse_meta_instruction;
static NODE_GETTER get_value_or_future__parse_meta_instruction;
static NODE_GETTER get__parse_statement;
static NODE_GETTER get_value_or_future__parse_statement;
static NODE_GETTER get__print_trees;
static NODE_GETTER get_value_or_future__print_trees;
static NODE_GETTER get__privileged_polymorphic_functions;
static NODE_GETTER get_value_or_future__privileged_polymorphic_functions;
static NODE_GETTER get__procedure_call;
static NODE_GETTER get_value_or_future__procedure_call;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static NODE_GETTER get__required_modules;
static NODE_SETTER set__required_modules;
static NODE_GETTER get__set;
static NODE_GETTER get_value_or_future__set;
static NODE_GETTER get__show_compiler_debug_info;
static NODE_GETTER get_value_or_future__show_compiler_debug_info;
static NODE_GETTER get__sim2c__actions;
static NODE_SETTER set__sim2c__actions;
static NODE_SETTER define__sim2c__actions;
static NODE_GETTER get__sim2c__assigned_names;
static NODE_SETTER set__sim2c__assigned_names;
static NODE_SETTER define__sim2c__assigned_names;
static NODE_GETTER get__sim2c__current_continuation_info;
static NODE_SETTER set__sim2c__current_continuation_info;
static NODE_SETTER define__sim2c__current_continuation_info;
static NODE_GETTER get__sim2c__defined_functions;
static NODE_SETTER set__sim2c__defined_functions;
static NODE_SETTER define__sim2c__defined_functions;
static NODE_GETTER get__sim2c__defined_names;
static NODE_SETTER set__sim2c__defined_names;
static NODE_SETTER define__sim2c__defined_names;
static NODE_GETTER get__sim2c__defined_namespaces;
static NODE_SETTER set__sim2c__defined_namespaces;
static NODE_SETTER define__sim2c__defined_namespaces;
static NODE_GETTER get__sim2c__defined_nodes;
static NODE_SETTER set__sim2c__defined_nodes;
static NODE_SETTER define__sim2c__defined_nodes;
static NODE_GETTER get__sim2c__defined_structs;
static NODE_SETTER set__sim2c__defined_structs;
static NODE_SETTER define__sim2c__defined_structs;
static NODE_GETTER get__sim2c__delayed_code;
static NODE_SETTER set__sim2c__delayed_code;
static NODE_SETTER define__sim2c__delayed_code;
static NODE_GETTER get__sim2c__dependent_data;
static NODE_SETTER set__sim2c__dependent_data;
static NODE_SETTER define__sim2c__dependent_data;
static NODE_GETTER get__sim2c__enumeration_count;
static NODE_SETTER set__sim2c__enumeration_count;
static NODE_SETTER define__sim2c__enumeration_count;
static NODE_GETTER get__sim2c__exported_names;
static NODE_SETTER set__sim2c__exported_names;
static NODE_SETTER define__sim2c__exported_names;
static NODE_GETTER get__sim2c__global_names;
static NODE_SETTER set__sim2c__global_names;
static NODE_SETTER define__sim2c__global_names;
static NODE_GETTER get__sim2c__included_files;
static NODE_SETTER set__sim2c__included_files;
static NODE_SETTER define__sim2c__included_files;
static NODE_GETTER get__sim2c__index;
static NODE_SETTER set__sim2c__index;
static NODE_SETTER define__sim2c__index;
static NODE_GETTER get__sim2c__linked_libraries;
static NODE_SETTER set__sim2c__linked_libraries;
static NODE_SETTER define__sim2c__linked_libraries;
static NODE_GETTER get__sim2c__namespace_mappings;
static NODE_SETTER set__sim2c__namespace_mappings;
static NODE_SETTER define__sim2c__namespace_mappings;
static NODE_GETTER get__sim2c__needed_names;
static NODE_SETTER set__sim2c__needed_names;
static NODE_SETTER define__sim2c__needed_names;
static NODE_GETTER get__sim2c__required_modules;
static NODE_SETTER set__sim2c__required_modules;
static NODE_SETTER define__sim2c__required_modules;
static NODE_GETTER get__sim2c__submodule_no;
static NODE_SETTER define__sim2c__submodule_no;
static NODE_GETTER get__sim2c__suffix;
static NODE_SETTER define__sim2c__suffix;
static NODE_GETTER get__sim2c__temp_idx;
static NODE_SETTER set__sim2c__temp_idx;
static NODE_SETTER define__sim2c__temp_idx;
static NODE_GETTER get__sim2c__use_identifier;
static NODE_SETTER define__sim2c__use_identifier;
static NODE_GETTER get__sim2c__use_inline_c;
static NODE_SETTER set__sim2c__use_inline_c;
static NODE_SETTER define__sim2c__use_inline_c;
static NODE_GETTER get__sim2c__use_literal;
static NODE_SETTER define__sim2c__use_literal;
static NODE_GETTER get__sim2c__used_names;
static NODE_SETTER set__sim2c__used_names;
static NODE_SETTER define__sim2c__used_names;
static NODE_GETTER get__sim2c__used_namespaces;
static NODE_SETTER set__sim2c__used_namespaces;
static NODE_SETTER define__sim2c__used_namespaces;
static NODE_GETTER get__sim2c__write_to_continuation_table;
static NODE_SETTER define__sim2c__write_to_continuation_table;
static NODE_GETTER get__sim2c__write_to_declarations;
static NODE_SETTER define__sim2c__write_to_declarations;
static NODE_GETTER get__sim2c__write_to_delayed_continuation_table;
static NODE_SETTER define__sim2c__write_to_delayed_continuation_table;
static NODE_GETTER get__sim2c__write_to_delayed_statements;
static NODE_SETTER define__sim2c__write_to_delayed_statements;
static NODE_GETTER get__sim2c__write_to_functions;
static NODE_SETTER define__sim2c__write_to_functions;
static NODE_GETTER get__sim2c__write_to_generated_collections;
static NODE_SETTER define__sim2c__write_to_generated_collections;
static NODE_GETTER get__sim2c__write_to_global_variable_declarations;
static NODE_SETTER define__sim2c__write_to_global_variable_declarations;
static NODE_GETTER get__sim2c__write_to_phase_1;
static NODE_SETTER define__sim2c__write_to_phase_1;
static NODE_GETTER get__sim2c__write_to_phase_2;
static NODE_SETTER define__sim2c__write_to_phase_2;
static NODE_GETTER get__sim2c__write_to_phase_3;
static NODE_SETTER define__sim2c__write_to_phase_3;
static NODE_GETTER get__sim2c__write_to_phase_4;
static NODE_SETTER define__sim2c__write_to_phase_4;
static NODE_GETTER get__sim2c__write_to_phase_5;
static NODE_SETTER define__sim2c__write_to_phase_5;
static NODE_GETTER get__sim2c__write_to_top_level_variable_declarations;
static NODE_SETTER define__sim2c__write_to_top_level_variable_declarations;
static NODE_GETTER get__sim2c__write_to_top_level_variable_names;
static NODE_SETTER define__sim2c__write_to_top_level_variable_names;
static NODE_GETTER get__simplify_statement;
static NODE_GETTER get_value_or_future__simplify_statement;
static int poly_idx__source_of;
static NODE_GETTER get__source_of;
static NODE_GETTER get__statements;
static NODE_SETTER set__statements;
static NODE_SETTER define__statements;
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
static NODE_GETTER get__std__value_of;
static NODE_GETTER get_value_or_future__std__value_of;
static NODE_GETTER get__std_identifier;
static NODE_GETTER get_value_or_future__std_identifier;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__strip;
static NODE_GETTER get_value_or_future__strip;
static NODE_GETTER get__table;
static NODE_GETTER get_value_or_future__table;
static NODE_GETTER get__temp_idx;
static NODE_GETTER get_value_or_future__temp_idx;
static NODE_GETTER get__terminate;
static NODE_GETTER get_value_or_future__terminate;
static NODE_GETTER get__to_integer;
static NODE_GETTER get_value_or_future__to_integer;
static NODE_GETTER get__to_lower_case;
static NODE_GETTER get_value_or_future__to_lower_case;
static NODE_GETTER get__tokenize;
static NODE_GETTER get_value_or_future__tokenize;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__truncate_until;
static NODE_GETTER get_value_or_future__truncate_until;
static NODE_GETTER get__try;
static NODE_GETTER get_value_or_future__try;
static NODE_GETTER get__types__grammar_node;
static NODE_GETTER get_value_or_future__types__grammar_node;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__update_each;
static NODE_GETTER get_value_or_future__update_each;
static NODE_GETTER get__update_info;
static NODE_GETTER get_value_or_future__update_info;
static NODE_GETTER get__use_inline_c;
static NODE_GETTER get_value_or_future__use_inline_c;
static NODE_GETTER get__used_namespaces;
static NODE_SETTER set__used_namespaces;
static int poly_idx__variable_kind_of;
static NODE_GETTER get__variable_kind_of;
static NODE_GETTER get__write;
static NODE_GETTER get_value_or_future__write;
static NODE_GETTER get__write_source_as_remark;
static NODE_GETTER get_value_or_future__write_source_as_remark;
static NODE_GETTER get__write_timing_info;
static NODE_GETTER get_value_or_future__write_timing_info;
static NODE_GETTER get__write_to_continuation_table;
static NODE_GETTER get_value_or_future__write_to_continuation_table;
static NODE_GETTER get__write_to_declarations;
static NODE_GETTER get_value_or_future__write_to_declarations;
static NODE_GETTER get__write_to_delayed_statements;
static NODE_GETTER get_value_or_future__write_to_delayed_statements;
static NODE_GETTER get__write_to_functions;
static NODE_GETTER get_value_or_future__write_to_functions;
static NODE_GETTER get__writeln;
static NODE_GETTER get_value_or_future__writeln;
static struct {
  NODE *_demangled;
  NODE *sim2c__print_source;
  NODE *sim2c__eprint_source;
  NODE *sim2c__privileged_polymorphic_functions;
  NODE *sim2c__generate_dispatcher_function;
  NODE *sim2c__update_info;
  NODE *sim2c__sim2c;
} var;
static const char *var_names[] = {
  "demangled"
};
static NODE *func__1_1;
static void entry__1_1(void);
static FRAME_INFO frame__1_1 = {1, {"source"}};
static NODE *func__1_2;
static void entry__1_2(void);
static FRAME_INFO frame__1_2 = {1, {"chr"}};
static NODE *func__1_3;
static void entry__1_3(void);
static FRAME_INFO frame__1_3 = {1, {"chr"}};
static NODE *func__1_4;
static void entry__1_4(void);
static FRAME_INFO frame__1_4 = {0, {}};
static NODE *string__1_5;
static NODE *func__1_6;
static void entry__1_6(void);
static FRAME_INFO frame__1_6 = {0, {}};
static NODE *string__1_7;
static NODE *func__1_8;
static void entry__1_8(void);
static FRAME_INFO frame__1_8 = {0, {}};
static NODE *string__1_9;
static NODE *get__sim2c__print_source(void) {
  return var.sim2c__print_source;
}
static NODE *func__2_1;
static void entry__2_1(void);
static FRAME_INFO frame__2_1 = {1, {"source"}};
static NODE *func__2_2;
static void entry__2_2(void);
static FRAME_INFO frame__2_2 = {1, {"chr"}};
static NODE *func__2_3;
static void entry__2_3(void);
static FRAME_INFO frame__2_3 = {1, {"chr"}};
static NODE *func__2_4;
static void entry__2_4(void);
static FRAME_INFO frame__2_4 = {0, {}};
static NODE *string__2_5;
static NODE *func__2_6;
static void entry__2_6(void);
static FRAME_INFO frame__2_6 = {0, {}};
static NODE *string__2_7;
static NODE *func__2_8;
static void entry__2_8(void);
static FRAME_INFO frame__2_8 = {0, {}};
static NODE *string__2_9;
static NODE *get__sim2c__eprint_source(void) {
  return var.sim2c__eprint_source;
}
static NODE *get__sim2c__privileged_polymorphic_functions(void) {
  return var.sim2c__privileged_polymorphic_functions;
}
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {2, {"name", "id"}};
static NODE *string__4_2;
static NODE *string__4_3;
static void cont__4_4(void);
static void cont__4_5(void);
static NODE *string__4_6;
static NODE *string__4_7;
static void cont__4_8(void);
static void cont__4_9(void);
static void cont__4_10(void);
static void cont__4_11(void);
static NODE *func__4_12;
static void entry__4_12(void);
static FRAME_INFO frame__4_12 = {2, {"name", "id"}};
static NODE *string__4_13;
static NODE *string__4_14;
static NODE *string__4_15;
static void cont__4_16(void);
static NODE *func__4_17;
static void entry__4_17(void);
static FRAME_INFO frame__4_17 = {1, {"name"}};
static NODE *string__4_18;
static NODE *string__4_19;
static void cont__4_20(void);
static void cont__4_21(void);
static NODE *string__4_22;
static NODE *string__4_23;
static void cont__4_24(void);
static NODE *get__sim2c__generate_dispatcher_function(void) {
  return var.sim2c__generate_dispatcher_function;
}
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {1, {"name"}};
static NODE *string__5_2;
static NODE *string__5_3;
static void cont__5_4(void);
static void cont__5_5(void);
static NODE *func__6_1;
static void entry__6_1(void);
static FRAME_INFO frame__6_1 = {4, {"name", "curr_info", "info", "return"}};
static void cont__6_2(void);
static NODE *func__6_3;
static void entry__6_3(void);
static FRAME_INFO frame__6_3 = {4, {"curr_info", "info", "return", "name"}};
static void cont__6_4(void);
static NODE *func__6_5;
static void entry__6_5(void);
static FRAME_INFO frame__6_5 = {3, {"info", "return", "name"}};
static void cont__6_6(void);
static void cont__6_7(void);
static NODE *func__6_8;
static void entry__6_8(void);
static FRAME_INFO frame__6_8 = {1, {"return"}};
static NODE *func__6_9;
static void entry__6_9(void);
static FRAME_INFO frame__6_9 = {1, {"name"}};
static void cont__6_10(void);
static NODE *string__6_11;
static NODE *string__6_12;
static void cont__6_13(void);
static NODE *func__6_14;
static void entry__6_14(void);
static FRAME_INFO frame__6_14 = {2, {"info", "return"}};
static void cont__6_15(void);
static NODE *func__6_16;
static void entry__6_16(void);
static FRAME_INFO frame__6_16 = {1, {"return"}};
static NODE *func__6_17;
static void entry__6_17(void);
static FRAME_INFO frame__6_17 = {2, {"return", "info"}};
static NODE *func__6_18;
static void entry__6_18(void);
static FRAME_INFO frame__6_18 = {3, {"info", "name", "return"}};
static void cont__6_19(void);
static NODE *func__6_20;
static void entry__6_20(void);
static FRAME_INFO frame__6_20 = {1, {"name"}};
static void cont__6_21(void);
static NODE *string__6_22;
static NODE *string__6_23;
static void cont__6_24(void);
static void cont__6_25(void);
static NODE *func__6_26;
static void entry__6_26(void);
static FRAME_INFO frame__6_26 = {1, {"return"}};
static NODE *func__6_27;
static void entry__6_27(void);
static FRAME_INFO frame__6_27 = {1, {"name"}};
static void cont__6_28(void);
static NODE *string__6_29;
static NODE *string__6_30;
static void cont__6_31(void);
static NODE *func__6_32;
static void entry__6_32(void);
static FRAME_INFO frame__6_32 = {2, {"return", "info"}};
static NODE *func__6_33;
static void entry__6_33(void);
static FRAME_INFO frame__6_33 = {3, {"info", "name", "return"}};
static void cont__6_34(void);
static NODE *func__6_35;
static void entry__6_35(void);
static FRAME_INFO frame__6_35 = {1, {"name"}};
static void cont__6_36(void);
static NODE *string__6_37;
static NODE *string__6_38;
static void cont__6_39(void);
static void cont__6_40(void);
static NODE *func__6_41;
static void entry__6_41(void);
static FRAME_INFO frame__6_41 = {1, {"return"}};
static NODE *func__6_42;
static void entry__6_42(void);
static FRAME_INFO frame__6_42 = {1, {"name"}};
static void cont__6_43(void);
static NODE *string__6_44;
static NODE *string__6_45;
static void cont__6_46(void);
static NODE *func__6_47;
static void entry__6_47(void);
static FRAME_INFO frame__6_47 = {1, {"name"}};
static void cont__6_48(void);
static NODE *string__6_49;
static NODE *string__6_50;
static void cont__6_51(void);
static NODE *func__6_52;
static void entry__6_52(void);
static FRAME_INFO frame__6_52 = {3, {"info", "name", "return"}};
static void cont__6_53(void);
static NODE *func__6_54;
static void entry__6_54(void);
static FRAME_INFO frame__6_54 = {1, {"name"}};
static void cont__6_55(void);
static NODE *string__6_56;
static NODE *string__6_57;
static void cont__6_58(void);
static void cont__6_59(void);
static NODE *func__6_60;
static void entry__6_60(void);
static FRAME_INFO frame__6_60 = {1, {"return"}};
static NODE *func__6_61;
static void entry__6_61(void);
static FRAME_INFO frame__6_61 = {1, {"name"}};
static void cont__6_62(void);
static NODE *string__6_63;
static NODE *string__6_64;
static void cont__6_65(void);
static NODE *func__6_66;
static void entry__6_66(void);
static FRAME_INFO frame__6_66 = {2, {"return", "info"}};
static NODE *func__6_67;
static void entry__6_67(void);
static FRAME_INFO frame__6_67 = {2, {"return", "info"}};
static void cont__6_68(void);
static NODE *get__sim2c__update_info(void) {
  return var.sim2c__update_info;
}
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {32, {"filenames", "is_main", "return__9", "mangle_filename", "fragments", "trees", "all_defined_names", "all_used_names", "all_actions", "top_level_names", "all_definitions", "all_statements", "max_temp_idx", "need", "generated_declarations", "generated_top_level_variable_names", "generated_top_level_variable_declarations", "generated_global_variable_declarations", "generated_continuation_table", "generated_delayed_continuation_table", "generated_functions", "generated_phase_1", "generated_phase_2", "generated_phase_3", "generated_phase_4", "generated_phase_5", "generated_code", "generated_collections", "delayed_statements", "used_literals", "def_count", "depth"}};
static NODE *func__7_2;
static void entry__7_2(void);
static FRAME_INFO frame__7_2 = {1, {"name"}};
static NODE *string__7_3;
static void cont__7_4(void);
static NODE *func__7_5;
static void entry__7_5(void);
static FRAME_INFO frame__7_5 = {1, {"name"}};
static NODE *string__7_6;
static void cont__7_7(void);
static NODE *func__7_8;
static void entry__7_8(void);
static FRAME_INFO frame__7_8 = {1, {"name"}};
static void cont__7_9(void);
static NODE *string__7_10;
static void cont__7_11(void);
static void cont__7_12(void);
static void cont__7_13(void);
static void cont__7_14(void);
static NODE *func__7_15;
static void entry__7_15(void);
static FRAME_INFO frame__7_15 = {1, {"name"}};
static void cont__7_16(void);
static void cont__7_17(void);
static void cont__7_18(void);
static NODE *string__7_19;
static void cont__7_20(void);
static void cont__7_21(void);
static NODE *func__7_22;
static void entry__7_22(void);
static FRAME_INFO frame__7_22 = {4, {"mangled_name", "info", "return", "updated_info"}};
static NODE *string__7_23;
static void cont__7_24(void);
static NODE *func__7_25;
static void entry__7_25(void);
static FRAME_INFO frame__7_25 = {5, {"mangled_name", "return", "namespace", "name", "namespaces"}};
static NODE *string__7_26;
static void cont__7_27(void);
static NODE *string__7_28;
static void cont__7_29(void);
static void cont__7_30(void);
static void cont__7_31(void);
static NODE *func__7_32;
static void entry__7_32(void);
static FRAME_INFO frame__7_32 = {2, {"namespaces", "namespace"}};
static void cont__7_33(void);
static void cont__7_34(void);
static void cont__7_35(void);
static NODE *func__7_36;
static void entry__7_36(void);
static FRAME_INFO frame__7_36 = {4, {"mangled_name", "info", "return", "definition"}};
static void cont__7_37(void);
static void cont__7_38(void);
static NODE *func__7_39;
static void entry__7_39(void);
static FRAME_INFO frame__7_39 = {4, {"mangled_name", "definition", "info", "return"}};
static void cont__7_40(void);
static void cont__7_41(void);
static void cont__7_42(void);
static void cont__7_43(void);
static void cont__7_44(void);
static NODE *func__7_45;
static void entry__7_45(void);
static FRAME_INFO frame__7_45 = {2, {"mangled_name", "updated_info"}};
static void cont__7_46(void);
static void cont__7_47(void);
static NODE *string__7_48;
static void cont__7_49(void);
static NODE *string__7_50;
static void cont__7_51(void);
static void cont__7_52(void);
static NODE *func__7_53;
static void entry__7_53(void);
static FRAME_INFO frame__7_53 = {9, {"no", "filename", "return__1", "is_main", "trees", "fragments", "buf", "submodule_fragments", "first_idx"}};
static void cont__7_54(void);
static NODE *func__7_55;
static void entry__7_55(void);
static FRAME_INFO frame__7_55 = {1, {"buf"}};
static void cont__7_56(void);
static NODE *func__7_57;
static void entry__7_57(void);
static FRAME_INFO frame__7_57 = {0, {}};
static NODE *string__7_58;
static void cont__7_59(void);
static NODE *func__7_60;
static void entry__7_60(void);
static FRAME_INFO frame__7_60 = {1, {"filename"}};
static NODE *string__7_61;
static NODE *string__7_62;
static void cont__7_63(void);
static void cont__7_64(void);
static NODE *func__7_65;
static void entry__7_65(void);
static FRAME_INFO frame__7_65 = {1, {"filename"}};
static NODE *string__7_66;
static void cont__7_67(void);
static void cont__7_68(void);
static void cont__7_69(void);
static NODE *func__7_70;
static void entry__7_70(void);
static FRAME_INFO frame__7_70 = {0, {}};
static NODE *string__7_71;
static void cont__7_72(void);
static void cont__7_73(void);
static void cont__7_74(void);
static void cont__7_75(void);
static NODE *func__7_76;
static void entry__7_76(void);
static FRAME_INFO frame__7_76 = {0, {}};
static NODE *string__7_77;
static void cont__7_78(void);
static void cont__7_79(void);
static void cont__7_80(void);
static void cont__7_81(void);
static void cont__7_82(void);
static NODE *func__7_83;
static void entry__7_83(void);
static FRAME_INFO frame__7_83 = {0, {}};
static NODE *string__7_84;
static void cont__7_85(void);
static NODE *string__7_86;
static void cont__7_87(void);
static NODE *func__7_88;
static void entry__7_88(void);
static FRAME_INFO frame__7_88 = {1, {"is_main"}};
static void cont__7_89(void);
static void cont__7_90(void);
static void cont__7_91(void);
static NODE *func__7_92;
static void entry__7_92(void);
static FRAME_INFO frame__7_92 = {1, {"filename"}};
static NODE *string__7_93;
static void cont__7_94(void);
static NODE *func__7_95;
static void entry__7_95(void);
static FRAME_INFO frame__7_95 = {1, {"fragment"}};
static void cont__7_96(void);
static void cont__7_97(void);
static NODE *func__7_98;
static void entry__7_98(void);
static FRAME_INFO frame__7_98 = {1, {"filename"}};
static NODE *string__7_99;
static void cont__7_100(void);
static NODE *func__7_101;
static void entry__7_101(void);
static FRAME_INFO frame__7_101 = {4, {"done", "submodule_fragments", "first_idx", "trees"}};
static NODE *func__7_102;
static void entry__7_102(void);
static FRAME_INFO frame__7_102 = {5, {"idx", "fragment", "first_idx", "trees", "done"}};
static void cont__7_103(void);
static void cont__7_104(void);
static NODE *func__7_105;
static void entry__7_105(void);
static FRAME_INFO frame__7_105 = {4, {"first_idx", "idx", "trees", "fragment"}};
static void cont__7_106(void);
static void cont__7_107(void);
static void cont__7_108(void);
static NODE *func__7_109;
static void entry__7_109(void);
static FRAME_INFO frame__7_109 = {4, {"first_idx", "idx", "trees", "fragment"}};
static void cont__7_110(void);
static void cont__7_111(void);
static void cont__7_112(void);
static NODE *func__7_113;
static void entry__7_113(void);
static FRAME_INFO frame__7_113 = {1, {"done"}};
static void cont__7_114(void);
static void cont__7_115(void);
static void cont__7_116(void);
static void cont__7_117(void);
static void cont__7_118(void);
static void cont__7_119(void);
static NODE *func__7_120;
static void entry__7_120(void);
static FRAME_INFO frame__7_120 = {2, {"fragment", "trees"}};
static void cont__7_121(void);
static void cont__7_122(void);
static void cont__7_123(void);
static NODE *func__7_124;
static void entry__7_124(void);
static FRAME_INFO frame__7_124 = {1, {"filenames"}};
static void cont__7_125(void);
static NODE *string__7_126;
static void cont__7_127(void);
static NODE *func__7_128;
static void entry__7_128(void);
static FRAME_INFO frame__7_128 = {1, {"trees"}};
static void cont__7_129(void);
static void cont__7_130(void);
static NODE *func__7_131;
static void entry__7_131(void);
static FRAME_INFO frame__7_131 = {1, {"trees"}};
static NODE *string__7_132;
static void cont__7_133(void);
static void cont__7_134(void);
static void cont__7_135(void);
static NODE *func__7_136;
static void entry__7_136(void);
static FRAME_INFO frame__7_136 = {2, {"tree", "return__2"}};
static void exit__7_136(void);
static void cont__7_137(void);
static void cont__7_138(void);
static NODE *func__7_139;
static void entry__7_139(void);
static FRAME_INFO frame__7_139 = {1, {"filenames"}};
static void cont__7_140(void);
static NODE *string__7_141;
static void cont__7_142(void);
static NODE *func__7_143;
static void entry__7_143(void);
static FRAME_INFO frame__7_143 = {4, {"tree", "return__3", "all_defined_names", "all_used_names"}};
static void exit__7_143(void);
static void cont__7_144(void);
static void cont__7_145(void);
static void cont__7_146(void);
static void cont__7_147(void);
static NODE *func__7_148;
static void entry__7_148(void);
static FRAME_INFO frame__7_148 = {1, {"filenames"}};
static void cont__7_149(void);
static NODE *string__7_150;
static void cont__7_151(void);
static NODE *func__7_152;
static void entry__7_152(void);
static FRAME_INFO frame__7_152 = {0, {}};
static NODE *func__7_153;
static void entry__7_153(void);
static FRAME_INFO frame__7_153 = {0, {}};
static void cont__7_154(void);
static void cont__7_155(void);
static NODE *func__7_156;
static void entry__7_156(void);
static FRAME_INFO frame__7_156 = {1, {"is_main"}};
static void cont__7_157(void);
static NODE *func__7_158;
static void entry__7_158(void);
static FRAME_INFO frame__7_158 = {0, {}};
static NODE *string__7_159;
static void cont__7_160(void);
static NODE *string__7_161;
static void cont__7_162(void);
static void cont__7_163(void);
static NODE *string__7_164;
static void cont__7_165(void);
static void cont__7_166(void);
static NODE *func__7_167;
static void entry__7_167(void);
static FRAME_INFO frame__7_167 = {0, {}};
static NODE *string__7_168;
static void cont__7_169(void);
static void cont__7_170(void);
static NODE *string__7_171;
static void cont__7_172(void);
static NODE *func__7_173;
static void entry__7_173(void);
static FRAME_INFO frame__7_173 = {2, {"defined_names", "top_level_names"}};
static NODE *func__7_174;
static void entry__7_174(void);
static FRAME_INFO frame__7_174 = {3, {"info", "top_level_names", "ident"}};
static void cont__7_175(void);
static void cont__7_176(void);
static NODE *func__7_177;
static void entry__7_177(void);
static FRAME_INFO frame__7_177 = {1, {"info"}};
static void cont__7_178(void);
static void cont__7_179(void);
static void cont__7_180(void);
static NODE *func__7_181;
static void entry__7_181(void);
static FRAME_INFO frame__7_181 = {5, {"ident", "info", "top_level_names", "namespace", "name"}};
static void cont__7_182(void);
static void cont__7_183(void);
static void cont__7_184(void);
static NODE *func__7_185;
static void entry__7_185(void);
static FRAME_INFO frame__7_185 = {5, {"name", "namespace", "info", "top_level_names", "namespaces"}};
static void cont__7_186(void);
static void cont__7_187(void);
static NODE *func__7_188;
static void entry__7_188(void);
static FRAME_INFO frame__7_188 = {1, {"namespaces"}};
static void cont__7_189(void);
static void cont__7_190(void);
static void cont__7_191(void);
static void cont__7_192(void);
static NODE *func__7_193;
static void entry__7_193(void);
static FRAME_INFO frame__7_193 = {3, {"info", "namespace", "name"}};
static void cont__7_194(void);
static NODE *string__7_195;
static NODE *string__7_196;
static NODE *string__7_197;
static void cont__7_198(void);
static void cont__7_199(void);
static void cont__7_200(void);
static NODE *func__7_201;
static void entry__7_201(void);
static FRAME_INFO frame__7_201 = {5, {"name", "info", "namespace", "top_level_names", "info_1"}};
static void cont__7_202(void);
static void cont__7_203(void);
static NODE *func__7_204;
static void entry__7_204(void);
static FRAME_INFO frame__7_204 = {3, {"info", "namespace", "name"}};
static void cont__7_205(void);
static NODE *string__7_206;
static NODE *string__7_207;
static NODE *string__7_208;
static NODE *string__7_209;
static void cont__7_210(void);
static void cont__7_211(void);
static void cont__7_212(void);
static void cont__7_213(void);
static NODE *func__7_214;
static void entry__7_214(void);
static FRAME_INFO frame__7_214 = {4, {"info", "namespace", "name", "info_1"}};
static void cont__7_215(void);
static void cont__7_216(void);
static void cont__7_217(void);
static NODE *string__7_218;
static NODE *string__7_219;
static NODE *string__7_220;
static NODE *string__7_221;
static NODE *string__7_222;
static void cont__7_223(void);
static void cont__7_224(void);
static void cont__7_225(void);
static void cont__7_226(void);
static void cont__7_227(void);
static void cont__7_228(void);
static NODE *func__7_229;
static void entry__7_229(void);
static FRAME_INFO frame__7_229 = {4, {"name", "info", "top_level_names", "namespaces"}};
static void cont__7_230(void);
static void cont__7_231(void);
static NODE *func__7_232;
static void entry__7_232(void);
static FRAME_INFO frame__7_232 = {2, {"info", "name"}};
static void cont__7_233(void);
static NODE *string__7_234;
static NODE *string__7_235;
static void cont__7_236(void);
static void cont__7_237(void);
static void cont__7_238(void);
static void cont__7_239(void);
static NODE *func__7_240;
static void entry__7_240(void);
static FRAME_INFO frame__7_240 = {3, {"namespaces", "info", "name"}};
static NODE *func__7_241;
static void entry__7_241(void);
static FRAME_INFO frame__7_241 = {4, {"nspace", "dummy", "info", "name"}};
static void cont__7_242(void);
static NODE *func__7_243;
static void entry__7_243(void);
static FRAME_INFO frame__7_243 = {3, {"info", "name", "nspace"}};
static void cont__7_244(void);
static NODE *string__7_245;
static NODE *string__7_246;
static NODE *string__7_247;
static NODE *string__7_248;
static void cont__7_249(void);
static void cont__7_250(void);
static void cont__7_251(void);
static void cont__7_252(void);
static void cont__7_253(void);
static NODE *func__7_254;
static void entry__7_254(void);
static FRAME_INFO frame__7_254 = {3, {"all_used_names", "top_level_names", "top_level_used_names"}};
static NODE *func__7_255;
static void entry__7_255(void);
static FRAME_INFO frame__7_255 = {2, {"used_names", "top_level_used_names"}};
static NODE *func__7_256;
static void entry__7_256(void);
static FRAME_INFO frame__7_256 = {3, {"mangled_name", "info", "top_level_used_names"}};
static void cont__7_257(void);
static void cont__7_258(void);
static void cont__7_259(void);
static NODE *func__7_260;
static void entry__7_260(void);
static FRAME_INFO frame__7_260 = {1, {"filenames"}};
static void cont__7_261(void);
static NODE *string__7_262;
static void cont__7_263(void);
static NODE *func__7_264;
static void entry__7_264(void);
static FRAME_INFO frame__7_264 = {1, {"trees"}};
static NODE *func__7_265;
static void entry__7_265(void);
static FRAME_INFO frame__7_265 = {1, {"tree"}};
static void cont__7_266(void);
static void cont__7_267(void);
static void cont__7_268(void);
static void cont__7_269(void);
static NODE *func__7_270;
static void entry__7_270(void);
static FRAME_INFO frame__7_270 = {6, {"tree", "top_level_names", "all_statements", "all_definitions", "max_temp_idx", "all_actions"}};
static void cont__7_271(void);
static NODE *func__7_272;
static void entry__7_272(void);
static FRAME_INFO frame__7_272 = {1, {"tree"}};
static void cont__7_273(void);
static void cont__7_274(void);
static NODE *func__7_275;
static void entry__7_275(void);
static FRAME_INFO frame__7_275 = {8, {"return__4", "top_level_names", "tree", "all_statements", "all_definitions", "max_temp_idx", "all_actions", "tmp_idx"}};
static void cont__7_276(void);
static void cont__7_277(void);
static void cont__7_278(void);
static NODE *func__7_279;
static void entry__7_279(void);
static FRAME_INFO frame__7_279 = {2, {"max_temp_idx", "tmp_idx"}};
static void cont__7_280(void);
static void cont__7_281(void);
static void cont__7_282(void);
static void cont__7_283(void);
static NODE *func__7_284;
static void entry__7_284(void);
static FRAME_INFO frame__7_284 = {1, {"stmt_actions"}};
static NODE *func__7_285;
static void entry__7_285(void);
static FRAME_INFO frame__7_285 = {1, {"action"}};
static void cont__7_286(void);
static NODE *func__7_287;
static void entry__7_287(void);
static FRAME_INFO frame__7_287 = {1, {"filenames"}};
static void cont__7_288(void);
static NODE *string__7_289;
static void cont__7_290(void);
static NODE *func__7_291;
static void entry__7_291(void);
static FRAME_INFO frame__7_291 = {2, {"all_definitions", "all_statements"}};
static NODE *func__7_292;
static void entry__7_292(void);
static FRAME_INFO frame__7_292 = {1, {"defs"}};
static NODE *func__7_293;
static void entry__7_293(void);
static FRAME_INFO frame__7_293 = {1, {"def"}};
static void cont__7_294(void);
static NODE *func__7_295;
static void entry__7_295(void);
static FRAME_INFO frame__7_295 = {1, {"def"}};
static void cont__7_296(void);
static void cont__7_297(void);
static NODE *string__7_298;
static NODE *func__7_299;
static void entry__7_299(void);
static FRAME_INFO frame__7_299 = {1, {"def"}};
static NODE *string__7_300;
static void cont__7_301(void);
static NODE *func__7_302;
static void entry__7_302(void);
static FRAME_INFO frame__7_302 = {1, {"stmts"}};
static void cont__7_303(void);
static void cont__7_304(void);
static NODE *func__7_305;
static void entry__7_305(void);
static FRAME_INFO frame__7_305 = {2, {"used_names", "need"}};
static NODE *func__7_306;
static void entry__7_306(void);
static FRAME_INFO frame__7_306 = {3, {"mangled_name", "info", "need"}};
static void cont__7_307(void);
static NODE *func__7_308;
static void entry__7_308(void);
static FRAME_INFO frame__7_308 = {1, {"filenames"}};
static void cont__7_309(void);
static NODE *string__7_310;
static void cont__7_311(void);
static void cont__7_312(void);
static NODE *func__7_313;
static void entry__7_313(void);
static FRAME_INFO frame__7_313 = {3, {"args", "generated_declarations", "txt"}};
static void cont__7_314(void);
static NODE *func__7_315;
static void entry__7_315(void);
static FRAME_INFO frame__7_315 = {2, {"generated_declarations", "txt"}};
static void cont__7_316(void);
static void cont__7_317(void);
static NODE *func__7_318;
static void entry__7_318(void);
static FRAME_INFO frame__7_318 = {3, {"args", "generated_top_level_variable_names", "txt"}};
static void cont__7_319(void);
static NODE *func__7_320;
static void entry__7_320(void);
static FRAME_INFO frame__7_320 = {2, {"generated_top_level_variable_names", "txt"}};
static void cont__7_321(void);
static void cont__7_322(void);
static NODE *func__7_323;
static void entry__7_323(void);
static FRAME_INFO frame__7_323 = {3, {"args", "generated_top_level_variable_declarations", "txt"}};
static void cont__7_324(void);
static NODE *func__7_325;
static void entry__7_325(void);
static FRAME_INFO frame__7_325 = {2, {"generated_top_level_variable_declarations", "txt"}};
static void cont__7_326(void);
static void cont__7_327(void);
static NODE *func__7_328;
static void entry__7_328(void);
static FRAME_INFO frame__7_328 = {3, {"args", "generated_global_variable_declarations", "txt"}};
static void cont__7_329(void);
static NODE *func__7_330;
static void entry__7_330(void);
static FRAME_INFO frame__7_330 = {2, {"generated_global_variable_declarations", "txt"}};
static void cont__7_331(void);
static void cont__7_332(void);
static NODE *func__7_333;
static void entry__7_333(void);
static FRAME_INFO frame__7_333 = {3, {"args", "generated_continuation_table", "txt"}};
static void cont__7_334(void);
static NODE *func__7_335;
static void entry__7_335(void);
static FRAME_INFO frame__7_335 = {2, {"generated_continuation_table", "txt"}};
static void cont__7_336(void);
static void cont__7_337(void);
static NODE *func__7_338;
static void entry__7_338(void);
static FRAME_INFO frame__7_338 = {3, {"args", "generated_delayed_continuation_table", "txt"}};
static void cont__7_339(void);
static NODE *func__7_340;
static void entry__7_340(void);
static FRAME_INFO frame__7_340 = {2, {"generated_delayed_continuation_table", "txt"}};
static void cont__7_341(void);
static void cont__7_342(void);
static NODE *func__7_343;
static void entry__7_343(void);
static FRAME_INFO frame__7_343 = {3, {"args", "generated_functions", "txt"}};
static void cont__7_344(void);
static NODE *func__7_345;
static void entry__7_345(void);
static FRAME_INFO frame__7_345 = {2, {"generated_functions", "txt"}};
static void cont__7_346(void);
static void cont__7_347(void);
static NODE *func__7_348;
static void entry__7_348(void);
static FRAME_INFO frame__7_348 = {3, {"args", "generated_phase_1", "txt"}};
static void cont__7_349(void);
static NODE *func__7_350;
static void entry__7_350(void);
static FRAME_INFO frame__7_350 = {2, {"generated_phase_1", "txt"}};
static void cont__7_351(void);
static void cont__7_352(void);
static NODE *func__7_353;
static void entry__7_353(void);
static FRAME_INFO frame__7_353 = {3, {"args", "generated_phase_2", "txt"}};
static void cont__7_354(void);
static NODE *func__7_355;
static void entry__7_355(void);
static FRAME_INFO frame__7_355 = {2, {"generated_phase_2", "txt"}};
static void cont__7_356(void);
static void cont__7_357(void);
static NODE *func__7_358;
static void entry__7_358(void);
static FRAME_INFO frame__7_358 = {3, {"args", "generated_phase_3", "txt"}};
static void cont__7_359(void);
static NODE *func__7_360;
static void entry__7_360(void);
static FRAME_INFO frame__7_360 = {2, {"generated_phase_3", "txt"}};
static void cont__7_361(void);
static void cont__7_362(void);
static NODE *func__7_363;
static void entry__7_363(void);
static FRAME_INFO frame__7_363 = {3, {"args", "generated_phase_4", "txt"}};
static void cont__7_364(void);
static NODE *func__7_365;
static void entry__7_365(void);
static FRAME_INFO frame__7_365 = {2, {"generated_phase_4", "txt"}};
static void cont__7_366(void);
static void cont__7_367(void);
static NODE *func__7_368;
static void entry__7_368(void);
static FRAME_INFO frame__7_368 = {3, {"args", "generated_phase_5", "txt"}};
static void cont__7_369(void);
static NODE *func__7_370;
static void entry__7_370(void);
static FRAME_INFO frame__7_370 = {2, {"generated_phase_5", "txt"}};
static void cont__7_371(void);
static void cont__7_372(void);
static NODE *func__7_373;
static void entry__7_373(void);
static FRAME_INFO frame__7_373 = {3, {"name", "literal", "used_literals"}};
static NODE *func__7_374;
static void entry__7_374(void);
static FRAME_INFO frame__7_374 = {3, {"used_literals", "name", "literal"}};
static void cont__7_375(void);
static void cont__7_376(void);
static NODE *func__7_377;
static void entry__7_377(void);
static FRAME_INFO frame__7_377 = {3, {"args", "generated_collections", "txt"}};
static void cont__7_378(void);
static NODE *func__7_379;
static void entry__7_379(void);
static FRAME_INFO frame__7_379 = {2, {"generated_collections", "txt"}};
static void cont__7_380(void);
static void cont__7_381(void);
static NODE *func__7_382;
static void entry__7_382(void);
static FRAME_INFO frame__7_382 = {3, {"args", "delayed_statements", "txt"}};
static void cont__7_383(void);
static NODE *func__7_384;
static void entry__7_384(void);
static FRAME_INFO frame__7_384 = {2, {"delayed_statements", "txt"}};
static void cont__7_385(void);
static void cont__7_386(void);
static NODE *func__7_387;
static void entry__7_387(void);
static FRAME_INFO frame__7_387 = {2, {"ident", "need"}};
static NODE *string__7_388;
static void cont__7_389(void);
static NODE *func__7_390;
static void entry__7_390(void);
static FRAME_INFO frame__7_390 = {3, {"ident", "need", "name"}};
static void cont__7_391(void);
static void cont__7_392(void);
static NODE *string__7_393;
static void cont__7_394(void);
static NODE *func__7_395;
static void entry__7_395(void);
static FRAME_INFO frame__7_395 = {6, {"stmt_idx", "defs", "return__5", "generated_code", "all_actions", "code"}};
static NODE *string__7_396;
static void cont__7_397(void);
static NODE *func__7_398;
static void entry__7_398(void);
static FRAME_INFO frame__7_398 = {1, {"defs"}};
static NODE *func__7_399;
static void entry__7_399(void);
static FRAME_INFO frame__7_399 = {2, {"definition", "source"}};
static void cont__7_400(void);
static NODE *func__7_401;
static void entry__7_401(void);
static FRAME_INFO frame__7_401 = {2, {"source", "definition"}};
static void cont__7_402(void);
static void cont__7_403(void);
static void cont__7_404(void);
static void cont__7_405(void);
static NODE *func__7_406;
static void entry__7_406(void);
static FRAME_INFO frame__7_406 = {1, {"definition"}};
static NODE *func__7_407;
static void entry__7_407(void);
static FRAME_INFO frame__7_407 = {2, {"source", "definition"}};
static void cont__7_408(void);
static NODE *func__7_409;
static void entry__7_409(void);
static FRAME_INFO frame__7_409 = {1, {"source"}};
static void cont__7_410(void);
static void cont__7_411(void);
static NODE *func__7_412;
static void entry__7_412(void);
static FRAME_INFO frame__7_412 = {2, {"definition", "source"}};
static void cont__7_413(void);
static NODE *func__7_414;
static void entry__7_414(void);
static FRAME_INFO frame__7_414 = {2, {"definition", "source"}};
static void cont__7_415(void);
static NODE *func__7_416;
static void entry__7_416(void);
static FRAME_INFO frame__7_416 = {2, {"definition", "source"}};
static NODE *func__7_417;
static void entry__7_417(void);
static FRAME_INFO frame__7_417 = {2, {"definition", "source"}};
static void cont__7_418(void);
static void cont__7_419(void);
static NODE *func__7_420;
static void entry__7_420(void);
static FRAME_INFO frame__7_420 = {2, {"definition", "source"}};
static NODE *func__7_421;
static void entry__7_421(void);
static FRAME_INFO frame__7_421 = {2, {"definition", "source"}};
static NODE *func__7_422;
static void entry__7_422(void);
static FRAME_INFO frame__7_422 = {2, {"definition", "source"}};
static void cont__7_423(void);
static void cont__7_424(void);
static void cont__7_425(void);
static NODE *func__7_426;
static void entry__7_426(void);
static FRAME_INFO frame__7_426 = {0, {}};
static void cont__7_427(void);
static NODE *func__7_428;
static void entry__7_428(void);
static FRAME_INFO frame__7_428 = {2, {"generated_code", "code"}};
static void cont__7_429(void);
static void cont__7_430(void);
static void cont__7_431(void);
static void cont__7_432(void);
static NODE *string__7_433;
static void cont__7_434(void);
static NODE *func__7_435;
static void entry__7_435(void);
static FRAME_INFO frame__7_435 = {6, {"return__6", "is_main", "mangle_filename", "generated_code", "all_actions", "code"}};
static NODE *func__7_436;
static void entry__7_436(void);
static FRAME_INFO frame__7_436 = {2, {"is_main", "mangle_filename"}};
static NODE *func__7_437;
static void entry__7_437(void);
static FRAME_INFO frame__7_437 = {0, {}};
static NODE *string__7_438;
static NODE *func__7_439;
static void entry__7_439(void);
static FRAME_INFO frame__7_439 = {0, {}};
static NODE *string__7_440;
static NODE *string__7_441;
static void cont__7_442(void);
static void cont__7_443(void);
static NODE *string__7_444;
static NODE *string__7_445;
static void cont__7_446(void);
static void cont__7_447(void);
static NODE *func__7_448;
static void entry__7_448(void);
static FRAME_INFO frame__7_448 = {4, {"name", "info", "mangle_filename", "continuation"}};
static void cont__7_449(void);
static void cont__7_450(void);
static void cont__7_451(void);
static NODE *string__7_452;
static NODE *string__7_453;
static NODE *string__7_454;
static void cont__7_455(void);
static void cont__7_456(void);
static void cont__7_457(void);
static NODE *string__7_458;
static void cont__7_459(void);
static void cont__7_460(void);
static NODE *func__7_461;
static void entry__7_461(void);
static FRAME_INFO frame__7_461 = {2, {"generated_code", "code"}};
static void cont__7_462(void);
static void cont__7_463(void);
static void cont__7_464(void);
static void cont__7_465(void);
static void cont__7_466(void);
static NODE *func__7_467;
static void entry__7_467(void);
static FRAME_INFO frame__7_467 = {7, {"stmt_idx", "stmts", "return__7", "def_count", "generated_code", "all_actions", "code"}};
static void cont__7_468(void);
static NODE *string__7_469;
static void cont__7_470(void);
static NODE *func__7_471;
static void entry__7_471(void);
static FRAME_INFO frame__7_471 = {1, {"stmts"}};
static NODE *func__7_472;
static void entry__7_472(void);
static FRAME_INFO frame__7_472 = {1, {"stmt"}};
static void cont__7_473(void);
static void cont__7_474(void);
static void cont__7_475(void);
static NODE *func__7_476;
static void entry__7_476(void);
static FRAME_INFO frame__7_476 = {0, {}};
static void cont__7_477(void);
static NODE *func__7_478;
static void entry__7_478(void);
static FRAME_INFO frame__7_478 = {2, {"generated_code", "code"}};
static void cont__7_479(void);
static void cont__7_480(void);
static void cont__7_481(void);
static void cont__7_482(void);
static NODE *func__7_483;
static void entry__7_483(void);
static FRAME_INFO frame__7_483 = {5, {"return__8", "is_main", "generated_code", "all_actions", "code"}};
static NODE *func__7_484;
static void entry__7_484(void);
static FRAME_INFO frame__7_484 = {1, {"is_main"}};
static NODE *func__7_485;
static void entry__7_485(void);
static FRAME_INFO frame__7_485 = {0, {}};
static NODE *string__7_486;
static NODE *func__7_487;
static void entry__7_487(void);
static FRAME_INFO frame__7_487 = {0, {}};
static NODE *string__7_488;
static void cont__7_489(void);
static void cont__7_490(void);
static NODE *func__7_491;
static void entry__7_491(void);
static FRAME_INFO frame__7_491 = {2, {"generated_code", "code"}};
static void cont__7_492(void);
static void cont__7_493(void);
static void cont__7_494(void);
static void cont__7_495(void);
static NODE *func__7_496;
static void entry__7_496(void);
static FRAME_INFO frame__7_496 = {1, {"stmt_actions"}};
static NODE *func__7_497;
static void entry__7_497(void);
static FRAME_INFO frame__7_497 = {1, {"action"}};
static void cont__7_498(void);
static NODE *func__7_499;
static void entry__7_499(void);
static FRAME_INFO frame__7_499 = {2, {"name", "info"}};
static NODE *string__7_500;
static void cont__7_501(void);
static void cont__7_502(void);
static NODE *func__7_503;
static void entry__7_503(void);
static FRAME_INFO frame__7_503 = {1, {"name"}};
static NODE *string__7_504;
static void cont__7_505(void);
static void cont__7_506(void);
static NODE *func__7_507;
static void entry__7_507(void);
static FRAME_INFO frame__7_507 = {1, {"filemask"}};
static NODE *string__7_508;
static void cont__7_509(void);
static void cont__7_510(void);
static void cont__7_511(void);
static void cont__7_512(void);
static NODE *func__7_513;
static void entry__7_513(void);
static FRAME_INFO frame__7_513 = {0, {}};
static NODE *string__7_514;
static void cont__7_515(void);
static NODE *string__7_516;
static void cont__7_517(void);
static void cont__7_518(void);
static NODE *func__7_519;
static void entry__7_519(void);
static FRAME_INFO frame__7_519 = {1, {"name"}};
static NODE *string__7_520;
static NODE *string__7_521;
static void cont__7_522(void);
static void cont__7_523(void);
static NODE *string__7_524;
static void cont__7_525(void);
static NODE *string__7_526;
static void cont__7_527(void);
static NODE *func__7_528;
static void entry__7_528(void);
static FRAME_INFO frame__7_528 = {0, {}};
static NODE *string__7_529;
static void cont__7_530(void);
static NODE *string__7_531;
static void cont__7_532(void);
static NODE *func__7_533;
static void entry__7_533(void);
static FRAME_INFO frame__7_533 = {0, {}};
static NODE *string__7_534;
static void cont__7_535(void);
static void cont__7_536(void);
static NODE *func__7_537;
static void entry__7_537(void);
static FRAME_INFO frame__7_537 = {0, {}};
static NODE *string__7_538;
static void cont__7_539(void);
static NODE *string__7_540;
static void cont__7_541(void);
static NODE *func__7_542;
static void entry__7_542(void);
static FRAME_INFO frame__7_542 = {1, {"idx"}};
static NODE *string__7_543;
static NODE *string__7_544;
static void cont__7_545(void);
static void cont__7_546(void);
static NODE *func__7_547;
static void entry__7_547(void);
static FRAME_INFO frame__7_547 = {2, {"name", "info"}};
static void cont__7_548(void);
static void cont__7_549(void);
static NODE *func__7_550;
static void entry__7_550(void);
static FRAME_INFO frame__7_550 = {1, {"name"}};
static NODE *string__7_551;
static NODE *string__7_552;
static void cont__7_553(void);
static void cont__7_554(void);
static NODE *string__7_555;
static NODE *string__7_556;
static void cont__7_557(void);
static void cont__7_558(void);
static void cont__7_559(void);
static void cont__7_560(void);
static NODE *func__7_561;
static void entry__7_561(void);
static FRAME_INFO frame__7_561 = {1, {"name"}};
static NODE *string__7_562;
static NODE *string__7_563;
static void cont__7_564(void);
static void cont__7_565(void);
static void cont__7_566(void);
static void cont__7_567(void);
static NODE *func__7_568;
static void entry__7_568(void);
static FRAME_INFO frame__7_568 = {1, {"name"}};
static NODE *string__7_569;
static NODE *string__7_570;
static void cont__7_571(void);
static void cont__7_572(void);
static void cont__7_573(void);
static void cont__7_574(void);
static NODE *func__7_575;
static void entry__7_575(void);
static FRAME_INFO frame__7_575 = {1, {"name"}};
static NODE *string__7_576;
static NODE *string__7_577;
static void cont__7_578(void);
static void cont__7_579(void);
static NODE *string__7_580;
static void cont__7_581(void);
static void cont__7_582(void);
static void cont__7_583(void);
static NODE *string__7_584;
static void cont__7_585(void);
static NODE *string__7_586;
static void cont__7_587(void);
static void cont__7_588(void);
static void cont__7_589(void);
static NODE *func__7_590;
static void entry__7_590(void);
static FRAME_INFO frame__7_590 = {1, {"generated_top_level_variable_names"}};
static void cont__7_591(void);
static void cont__7_592(void);
static void cont__7_593(void);
static NODE *string__7_594;
static void cont__7_595(void);
static void cont__7_596(void);
static NODE *func__7_597;
static void entry__7_597(void);
static FRAME_INFO frame__7_597 = {0, {}};
static NODE *string__7_598;
static NODE *func__7_599;
static void entry__7_599(void);
static FRAME_INFO frame__7_599 = {0, {}};
static NODE *string__7_600;
static NODE *string__7_601;
static void cont__7_602(void);
static void cont__7_603(void);
static NODE *string__7_604;
static void cont__7_605(void);
static void cont__7_606(void);
static void cont__7_607(void);
static void cont__7_608(void);
static NODE *func__7_609;
static void entry__7_609(void);
static FRAME_INFO frame__7_609 = {1, {"generated_continuation_table"}};
static void cont__7_610(void);
static void cont__7_611(void);
static void cont__7_612(void);
static NODE *string__7_613;
static void cont__7_614(void);
static NODE *string__7_615;
static void cont__7_616(void);
static NODE *func__7_617;
static void entry__7_617(void);
static FRAME_INFO frame__7_617 = {0, {}};
static NODE *func__7_618;
static void entry__7_618(void);
static FRAME_INFO frame__7_618 = {2, {"name", "node"}};
static void cont__7_619(void);
static NODE *string__7_620;
static NODE *string__7_621;
static NODE *string__7_622;
static void cont__7_623(void);
static void cont__7_624(void);
static NODE *string__7_625;
static void cont__7_626(void);
static void cont__7_627(void);
static NODE *func__7_628;
static void entry__7_628(void);
static FRAME_INFO frame__7_628 = {2, {"name", "literal"}};
static NODE *string__7_629;
static NODE *string__7_630;
static void cont__7_631(void);
static void cont__7_632(void);
static NODE *string__7_633;
static void cont__7_634(void);
static NODE *func__7_635;
static void entry__7_635(void);
static FRAME_INFO frame__7_635 = {1, {"name"}};
static NODE *string__7_636;
static NODE *string__7_637;
static void cont__7_638(void);
static void cont__7_639(void);
static NODE *string__7_640;
static NODE *string__7_641;
static void cont__7_642(void);
static void cont__7_643(void);
static NODE *string__7_644;
static void cont__7_645(void);
static NODE *func__7_646;
static void entry__7_646(void);
static FRAME_INFO frame__7_646 = {2, {"filename", "depth"}};
static void cont__7_647(void);
static void cont__7_648(void);
static void cont__7_649(void);
static NODE *string__7_650;
static NODE *string__7_651;
static void cont__7_652(void);
static NODE *func__7_653;
static void entry__7_653(void);
static FRAME_INFO frame__7_653 = {0, {}};
static NODE *string__7_654;
static void cont__7_655(void);
static NODE *string__7_656;
static void cont__7_657(void);
static NODE *func__7_658;
static void entry__7_658(void);
static FRAME_INFO frame__7_658 = {4, {"name", "info", "mangle_filename", "fname"}};
static void cont__7_659(void);
static NODE *string__7_660;
static NODE *string__7_661;
static NODE *string__7_662;
static NODE *string__7_663;
static NODE *string__7_664;
static NODE *string__7_665;
static NODE *string__7_666;
static NODE *string__7_667;
static void cont__7_668(void);
static void cont__7_669(void);
static void cont__7_670(void);
static void cont__7_671(void);
static NODE *string__7_672;
static NODE *string__7_673;
static void cont__7_674(void);
static void cont__7_675(void);
static NODE *func__7_676;
static void entry__7_676(void);
static FRAME_INFO frame__7_676 = {1, {"idx"}};
static NODE *string__7_677;
static NODE *string__7_678;
static NODE *string__7_679;
static void cont__7_680(void);
static void cont__7_681(void);
static void cont__7_682(void);
static NODE *func__7_683;
static void entry__7_683(void);
static FRAME_INFO frame__7_683 = {2, {"name", "literal"}};
static NODE *string__7_684;
static NODE *string__7_685;
static NODE *string__7_686;
static void cont__7_687(void);
static void cont__7_688(void);
static NODE *string__7_689;
static void cont__7_690(void);
static NODE *func__7_691;
static void entry__7_691(void);
static FRAME_INFO frame__7_691 = {0, {}};
static NODE *string__7_692;
static NODE *func__7_693;
static void entry__7_693(void);
static FRAME_INFO frame__7_693 = {0, {}};
static NODE *string__7_694;
static NODE *string__7_695;
static void cont__7_696(void);
static void cont__7_697(void);
static NODE *func__7_698;
static void entry__7_698(void);
static FRAME_INFO frame__7_698 = {4, {"name", "info", "mangle_filename", "mangled_name"}};
static void cont__7_699(void);
static NODE *string__7_700;
static NODE *string__7_701;
static void cont__7_702(void);
static void cont__7_703(void);
static NODE *string__7_704;
static void cont__7_705(void);
static void cont__7_706(void);
static NODE *func__7_707;
static void entry__7_707(void);
static FRAME_INFO frame__7_707 = {0, {}};
static NODE *string__7_708;
static NODE *func__7_709;
static void entry__7_709(void);
static FRAME_INFO frame__7_709 = {0, {}};
static NODE *string__7_710;
static NODE *string__7_711;
static void cont__7_712(void);
static void cont__7_713(void);
static NODE *func__7_714;
static void entry__7_714(void);
static FRAME_INFO frame__7_714 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_715(void);
static NODE *string__7_716;
static NODE *string__7_717;
static void cont__7_718(void);
static void cont__7_719(void);
static NODE *string__7_720;
static NODE *string__7_721;
static void cont__7_722(void);
static void cont__7_723(void);
static NODE *func__7_724;
static void entry__7_724(void);
static FRAME_INFO frame__7_724 = {2, {"name", "literal"}};
static NODE *string__7_725;
static NODE *string__7_726;
static void cont__7_727(void);
static void cont__7_728(void);
static void cont__7_729(void);
static NODE *func__7_730;
static void entry__7_730(void);
static FRAME_INFO frame__7_730 = {0, {}};
static NODE *string__7_731;
static NODE *func__7_732;
static void entry__7_732(void);
static FRAME_INFO frame__7_732 = {0, {}};
static NODE *string__7_733;
static NODE *string__7_734;
static void cont__7_735(void);
static void cont__7_736(void);
static NODE *func__7_737;
static void entry__7_737(void);
static FRAME_INFO frame__7_737 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_738(void);
static NODE *string__7_739;
static NODE *string__7_740;
static void cont__7_741(void);
static void cont__7_742(void);
static NODE *string__7_743;
static NODE *string__7_744;
static void cont__7_745(void);
static void cont__7_746(void);
static NODE *func__7_747;
static void entry__7_747(void);
static FRAME_INFO frame__7_747 = {2, {"name", "info"}};
static void cont__7_748(void);
static void cont__7_749(void);
static NODE *func__7_750;
static void entry__7_750(void);
static FRAME_INFO frame__7_750 = {4, {"name", "info", "namespace", "basename"}};
static NODE *string__7_751;
static void cont__7_752(void);
static NODE *func__7_753;
static void entry__7_753(void);
static FRAME_INFO frame__7_753 = {1, {"name"}};
static NODE *string__7_754;
static void cont__7_755(void);
static void cont__7_756(void);
static NODE *func__7_757;
static void entry__7_757(void);
static FRAME_INFO frame__7_757 = {0, {}};
static NODE *string__7_758;
static void cont__7_759(void);
static NODE *string__7_760;
static void cont__7_761(void);
static void cont__7_762(void);
static NODE *func__7_763;
static void entry__7_763(void);
static FRAME_INFO frame__7_763 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_764;
static NODE *string__7_765;
static NODE *string__7_766;
static NODE *string__7_767;
static NODE *string__7_768;
static void cont__7_769(void);
static NODE *func__7_770;
static void entry__7_770(void);
static FRAME_INFO frame__7_770 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_771;
static NODE *string__7_772;
static NODE *string__7_773;
static NODE *string__7_774;
static NODE *string__7_775;
static void cont__7_776(void);
static NODE *func__7_777;
static void entry__7_777(void);
static FRAME_INFO frame__7_777 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_778;
static NODE *string__7_779;
static NODE *string__7_780;
static NODE *string__7_781;
static NODE *string__7_782;
static void cont__7_783(void);
static NODE *func__7_784;
static void entry__7_784(void);
static FRAME_INFO frame__7_784 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_785;
static NODE *string__7_786;
static NODE *string__7_787;
static NODE *string__7_788;
static NODE *string__7_789;
static void cont__7_790(void);
static NODE *func__7_791;
static void entry__7_791(void);
static FRAME_INFO frame__7_791 = {3, {"namespace", "basename", "name"}};
static NODE *string__7_792;
static NODE *string__7_793;
static NODE *string__7_794;
static NODE *string__7_795;
static NODE *string__7_796;
static NODE *string__7_797;
static void cont__7_798(void);
static void cont__7_799(void);
static void cont__7_800(void);
static NODE *func__7_801;
static void entry__7_801(void);
static FRAME_INFO frame__7_801 = {0, {}};
static NODE *string__7_802;
static void cont__7_803(void);
static NODE *func__7_804;
static void entry__7_804(void);
static FRAME_INFO frame__7_804 = {0, {}};
static NODE *string__7_805;
static NODE *func__7_806;
static void entry__7_806(void);
static FRAME_INFO frame__7_806 = {0, {}};
static NODE *string__7_807;
static NODE *string__7_808;
static void cont__7_809(void);
static void cont__7_810(void);
static NODE *func__7_811;
static void entry__7_811(void);
static FRAME_INFO frame__7_811 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_812(void);
static NODE *string__7_813;
static NODE *string__7_814;
static void cont__7_815(void);
static void cont__7_816(void);
static NODE *func__7_817;
static void entry__7_817(void);
static FRAME_INFO frame__7_817 = {2, {"name", "literal"}};
static NODE *string__7_818;
static NODE *string__7_819;
static void cont__7_820(void);
static void cont__7_821(void);
static NODE *func__7_822;
static void entry__7_822(void);
static FRAME_INFO frame__7_822 = {1, {"literal"}};
static void cont__7_823(void);
static NODE *func__7_824;
static void entry__7_824(void);
static FRAME_INFO frame__7_824 = {2, {"literal", "value"}};
static void cont__7_825(void);
static void cont__7_826(void);
static void cont__7_827(void);
static NODE *string__7_828;
static void cont__7_829(void);
static void cont__7_830(void);
static NODE *func__7_831;
static void entry__7_831(void);
static FRAME_INFO frame__7_831 = {1, {"value"}};
static void cont__7_832(void);
static void cont__7_833(void);
static void cont__7_834(void);
static NODE *func__7_835;
static void entry__7_835(void);
static FRAME_INFO frame__7_835 = {1, {"value"}};
static NODE *string__7_836;
static NODE *string__7_837;
static void cont__7_838(void);
static NODE *func__7_839;
static void entry__7_839(void);
static FRAME_INFO frame__7_839 = {2, {"value", "int_val"}};
static void cont__7_840(void);
static NODE *func__7_841;
static void entry__7_841(void);
static FRAME_INFO frame__7_841 = {1, {"int_val"}};
static void cont__7_842(void);
static void cont__7_843(void);
static NODE *func__7_844;
static void entry__7_844(void);
static FRAME_INFO frame__7_844 = {1, {"int_val"}};
static NODE *string__7_845;
static NODE *string__7_846;
static void cont__7_847(void);
static NODE *func__7_848;
static void entry__7_848(void);
static FRAME_INFO frame__7_848 = {1, {"int_val"}};
static void cont__7_849(void);
static void cont__7_850(void);
static NODE *func__7_851;
static void entry__7_851(void);
static FRAME_INFO frame__7_851 = {1, {"int_val"}};
static NODE *string__7_852;
static NODE *string__7_853;
static void cont__7_854(void);
static NODE *func__7_855;
static void entry__7_855(void);
static FRAME_INFO frame__7_855 = {1, {"value"}};
static NODE *string__7_856;
static NODE *string__7_857;
static void cont__7_858(void);
static NODE *func__7_859;
static void entry__7_859(void);
static FRAME_INFO frame__7_859 = {1, {"literal"}};
static void cont__7_860(void);
static NODE *func__7_861;
static void entry__7_861(void);
static FRAME_INFO frame__7_861 = {1, {"literal"}};
static void cont__7_862(void);
static void cont__7_863(void);
static NODE *string__7_864;
static NODE *string__7_865;
static void cont__7_866(void);
static void cont__7_867(void);
static void cont__7_868(void);
static NODE *func__7_869;
static void entry__7_869(void);
static FRAME_INFO frame__7_869 = {0, {}};
static NODE *string__7_870;
static NODE *func__7_871;
static void entry__7_871(void);
static FRAME_INFO frame__7_871 = {0, {}};
static NODE *string__7_872;
static NODE *string__7_873;
static void cont__7_874(void);
static void cont__7_875(void);
static NODE *func__7_876;
static void entry__7_876(void);
static FRAME_INFO frame__7_876 = {3, {"name", "info", "mangle_filename"}};
static void cont__7_877(void);
static NODE *string__7_878;
static NODE *string__7_879;
static void cont__7_880(void);
static void cont__7_881(void);
static void cont__7_882(void);
static NODE *string__7_883;
static NODE *string__7_884;
static void cont__7_885(void);
static void cont__7_886(void);
static NODE *func__7_887;
static void entry__7_887(void);
static FRAME_INFO frame__7_887 = {0, {}};
static NODE *string__7_888;
static void cont__7_889(void);
static NODE *string__7_890;
static void cont__7_891(void);
static NODE *func__7_892;
static void entry__7_892(void);
static FRAME_INFO frame__7_892 = {1, {"filenames"}};
static void cont__7_893(void);
static NODE *string__7_894;
static void cont__7_895(void);
static NODE *get__sim2c__sim2c(void) {
  return var.sim2c__sim2c;
}
static NODE *string__10_1;
static void cont__10_2(void);
static NODE *string__10_3;
static void cont__10_4(void);
static NODE *string__10_5;
static void cont__10_6(void);
static NODE *string__10_7;
static void cont__10_8(void);
static NODE *string__10_9;
static void cont__10_10(void);
static NODE *string__10_11;
static void cont__10_12(void);
static NODE *string__10_13;
static void cont__10_14(void);
static void cont__10_15(void);
void run__sim2c(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__sim2c, NULL, 57, 57, 5, 17},
  {cont__10_2, NULL, 58, 58, 5, 25},
  {cont__10_4, NULL, 59, 59, 5, 20},
  {cont__10_6, NULL, 60, 60, 5, 19},
  {cont__10_8, NULL, 61, 61, 5, 24},
  {cont__10_10, NULL, 62, 62, 5, 23},
  {cont__10_12, NULL, 63, 63, 5, 21},
  {cont__10_14, NULL, 55, 63, 1, 22},
  {cont__10_15, NULL, },
  {entry__1_3, NULL, 40, 40, 9, 17},
  {entry__1_4, NULL, 34, 34, 9, 27},
  {entry__1_6, NULL, 36, 36, 9, 33},
  {entry__1_8, NULL, 38, 38, 9, 34},
  {entry__1_2, NULL, 31, 40, 5, 18},
  {entry__1_1, NULL, 30, 40, 3, 19},
  {entry__2_3, NULL, 53, 53, 9, 18},
  {entry__2_4, NULL, 47, 47, 9, 28},
  {entry__2_6, NULL, 49, 49, 9, 34},
  {entry__2_8, NULL, 51, 51, 9, 35},
  {entry__2_2, NULL, 44, 53, 5, 19},
  {entry__2_1, NULL, 43, 53, 3, 20},
  {entry__4_12, NULL, 87, 90, 26, 18},
  {cont__4_16, &frame__4_12, 87, 90, 7, 18},
  {entry__4_17, NULL, 93, 93, 9, 79},
  {cont__4_20, &frame__4_17, 92, 93, 7, 79},
  {entry__4_1, NULL, 66, 67, 25, 36},
  {cont__4_4, &frame__4_1, 66, 67, 3, 36},
  {cont__4_5, &frame__4_1, 68, 69, 22, 37},
  {cont__4_8, &frame__4_1, 68, 69, 3, 37},
  {cont__4_9, &frame__4_1, 70, 70, 3, 44},
  {cont__4_10, &frame__4_1, 72, 72, 5, 17},
  {cont__4_11, &frame__4_1, 71, 93, 3, 81},
  {cont__4_21, &frame__4_1, 98, 118, 22, 5},
  {cont__4_24, &frame__4_1, 98, 118, 3, 5},
  {entry__5_1, NULL, 120, 120, 40, 50},
  {cont__5_4, &frame__5_1, 120, 120, 23, 51},
  {cont__5_5, &frame__5_1, 120, 120, 20, 51},
  {entry__6_8, NULL, 137, 137, 15, 30},
  {entry__6_9, NULL, 140, 140, 31, 44},
  {cont__6_10, &frame__6_9, 139, 141, 21, 55},
  {cont__6_13, &frame__6_9, 139, 141, 15, 55},
  {entry__6_5, NULL, 135, 135, 13, 34},
  {cont__6_6, &frame__6_5, 136, 136, 13, 38},
  {cont__6_7, &frame__6_5, 134, 141, 11, 57},
  {entry__6_16, NULL, 146, 146, 15, 30},
  {entry__6_17, NULL, 148, 148, 15, 25},
  {entry__6_14, NULL, 144, 144, 13, 34},
  {cont__6_15, &frame__6_14, 143, 148, 11, 26},
  {entry__6_20, NULL, 154, 154, 31, 44},
  {cont__6_21, &frame__6_20, 153, 155, 21, 45},
  {cont__6_24, &frame__6_20, 153, 155, 15, 45},
  {entry__6_26, NULL, 157, 157, 15, 30},
  {entry__6_27, NULL, 160, 160, 31, 44},
  {cont__6_28, &frame__6_27, 159, 161, 21, 44},
  {cont__6_31, &frame__6_27, 159, 161, 15, 44},
  {entry__6_32, NULL, 163, 163, 15, 25},
  {entry__6_18, NULL, 151, 151, 13, 34},
  {cont__6_19, &frame__6_18, 156, 156, 13, 39},
  {cont__6_25, &frame__6_18, 150, 163, 11, 26},
  {entry__6_35, NULL, 169, 169, 31, 44},
  {cont__6_36, &frame__6_35, 168, 170, 21, 57},
  {cont__6_39, &frame__6_35, 168, 170, 15, 57},
  {entry__6_41, NULL, 172, 172, 15, 30},
  {entry__6_42, NULL, 175, 175, 31, 44},
  {cont__6_43, &frame__6_42, 174, 176, 21, 44},
  {cont__6_46, &frame__6_42, 174, 176, 15, 44},
  {entry__6_47, NULL, 179, 179, 31, 44},
  {cont__6_48, &frame__6_47, 178, 180, 21, 55},
  {cont__6_51, &frame__6_47, 178, 180, 15, 55},
  {entry__6_33, NULL, 166, 166, 13, 34},
  {cont__6_34, &frame__6_33, 171, 171, 13, 41},
  {cont__6_40, &frame__6_33, 165, 180, 11, 57},
  {entry__6_54, NULL, 186, 186, 31, 44},
  {cont__6_55, &frame__6_54, 185, 187, 21, 56},
  {cont__6_58, &frame__6_54, 185, 187, 15, 56},
  {entry__6_60, NULL, 189, 189, 15, 30},
  {entry__6_61, NULL, 192, 192, 31, 44},
  {cont__6_62, &frame__6_61, 191, 193, 21, 55},
  {cont__6_65, &frame__6_61, 191, 193, 15, 55},
  {entry__6_66, NULL, 195, 195, 15, 25},
  {entry__6_52, NULL, 183, 183, 13, 34},
  {cont__6_53, &frame__6_52, 188, 188, 13, 54},
  {cont__6_59, &frame__6_52, 182, 195, 11, 26},
  {entry__6_3, NULL, 132, 132, 9, 35},
  {cont__6_4, &frame__6_3, 131, 195, 7, 28},
  {entry__6_67, NULL, 197, 197, 7, 17},
  {entry__6_1, NULL, 130, 130, 5, 24},
  {cont__6_2, &frame__6_1, 129, 197, 3, 18},
  {cont__6_68, &frame__6_1, 197, 197, 18, 18},
  {entry__7_8, NULL, 214, 214, 42, 42},
  {cont__7_9, &frame__7_8, 214, 214, 17, 43},
  {cont__7_11, &frame__7_8, 214, 214, 68, 68},
  {cont__7_12, &frame__7_8, 214, 214, 54, 69},
  {cont__7_13, &frame__7_8, 214, 214, 11, 69},
  {cont__7_14, &frame__7_8, 214, 214, 69, 69},
  {entry__7_15, NULL, 216, 216, 31, 31},
  {cont__7_16, &frame__7_15, 216, 216, 11, 32},
  {cont__7_17, &frame__7_15, 216, 216, 32, 32},
  {entry__7_5, NULL, 213, 213, 9, 35},
  {cont__7_7, &frame__7_5, 212, 216, 7, 33},
  {entry__7_2, NULL, 211, 211, 8, 29},
  {cont__7_4, &frame__7_2, 211, 216, 5, 34},
  {cont__7_18, &frame__7_2, 217, 217, 25, 34},
  {cont__7_20, &frame__7_2, 217, 217, 8, 35},
  {cont__7_21, &frame__7_2, 217, 217, 5, 35},
  {entry__7_32, NULL, 404, 404, 37, 57},
  {cont__7_33, &frame__7_32, 404, 404, 37, 68},
  {cont__7_34, &frame__7_32, 404, 404, 37, 68},
  {entry__7_25, NULL, 401, 401, 9, 45},
  {cont__7_27, &frame__7_25, 402, 402, 9, 40},
  {cont__7_29, &frame__7_25, 403, 403, 9, 40},
  {cont__7_30, &frame__7_25, 404, 404, 12, 32},
  {cont__7_31, &frame__7_25, 404, 404, 12, 68},
  {cont__7_35, &frame__7_25, 404, 404, 9, 75},
  {entry__7_39, NULL, 408, 408, 11, 50},
  {cont__7_40, &frame__7_39, 409, 409, 11, 16},
  {entry__7_36, NULL, 406, 406, 9, 46},
  {cont__7_37, &frame__7_36, 407, 407, 12, 32},
  {cont__7_38, &frame__7_36, 407, 409, 9, 16},
  {entry__7_45, NULL, 411, 411, 33, 59},
  {cont__7_46, &frame__7_45, 411, 411, 72, 72},
  {entry__7_22, NULL, 400, 400, 7, 34},
  {cont__7_24, &frame__7_22, 399, 409, 5, 18},
  {cont__7_41, &frame__7_22, 410, 410, 44, 69},
  {cont__7_42, &frame__7_22, 410, 410, 5, 75},
  {cont__7_43, &frame__7_22, 411, 411, 8, 30},
  {cont__7_44, &frame__7_22, 411, 411, 5, 72},
  {cont__7_47, &frame__7_22, 411, 411, 72, 72},
  {entry__7_55, NULL, 243, 243, 9, 22},
  {cont__7_56, &frame__7_55, 243, 243, 22, 22},
  {entry__7_57, NULL, 245, 245, 9, 61},
  {entry__7_60, NULL, 247, 248, 14, 31},
  {cont__7_63, &frame__7_60, 247, 248, 7, 31},
  {entry__7_65, NULL, 249, 249, 24, 59},
  {entry__7_70, NULL, 250, 250, 29, 54},
  {entry__7_76, NULL, 251, 251, 23, 65},
  {entry__7_83, NULL, 252, 252, 28, 73},
  {entry__7_88, NULL, 253, 253, 43, 43},
  {entry__7_92, NULL, 256, 256, 24, 63},
  {entry__7_95, NULL, 257, 257, 51, 68},
  {cont__7_96, &frame__7_95, 257, 257, 68, 68},
  {entry__7_98, NULL, 258, 258, 24, 62},
  {entry__7_105, NULL, 265, 265, 13, 28},
  {cont__7_106, &frame__7_105, 266, 266, 25, 49},
  {cont__7_107, &frame__7_105, 266, 266, 13, 49},
  {cont__7_108, &frame__7_105, 266, 266, 49, 49},
  {entry__7_109, NULL, 268, 268, 13, 28},
  {cont__7_110, &frame__7_109, 269, 269, 25, 56},
  {cont__7_111, &frame__7_109, 269, 269, 13, 56},
  {cont__7_112, &frame__7_109, 269, 269, 56, 56},
  {entry__7_113, NULL, 271, 271, 13, 16},
  {entry__7_102, NULL, 263, 263, 11, 29},
  {cont__7_103, &frame__7_102, 263, 263, 11, 32},
  {cont__7_104, &frame__7_102, 262, 271, 9, 17},
  {entry__7_101, NULL, 261, 271, 7, 18},
  {cont__7_114, &frame__7_101, 271, 271, 18, 18},
  {entry__7_53, NULL, 240, 240, 5, 24},
  {cont__7_54, &frame__7_53, 241, 245, 5, 62},
  {cont__7_59, &frame__7_53, 246, 248, 5, 32},
  {cont__7_64, &frame__7_53, 249, 249, 5, 59},
  {cont__7_67, &frame__7_53, 250, 250, 8, 21},
  {cont__7_68, &frame__7_53, 250, 250, 8, 26},
  {cont__7_69, &frame__7_53, 250, 250, 5, 54},
  {cont__7_72, &frame__7_53, 251, 251, 8, 13},
  {cont__7_73, &frame__7_53, 251, 251, 8, 20},
  {cont__7_74, &frame__7_53, 251, 251, 8, 20},
  {cont__7_75, &frame__7_53, 251, 251, 5, 65},
  {cont__7_78, &frame__7_53, 252, 252, 13, 13},
  {cont__7_79, &frame__7_53, 252, 252, 8, 14},
  {cont__7_80, &frame__7_53, 252, 252, 8, 25},
  {cont__7_81, &frame__7_53, 252, 252, 8, 25},
  {cont__7_82, &frame__7_53, 252, 252, 5, 73},
  {cont__7_85, &frame__7_53, 253, 253, 8, 28},
  {cont__7_87, &frame__7_53, 253, 253, 5, 43},
  {cont__7_89, &frame__7_53, 254, 254, 5, 29},
  {cont__7_90, &frame__7_53, 255, 255, 5, 49},
  {cont__7_91, &frame__7_53, 256, 256, 5, 63},
  {cont__7_94, &frame__7_53, 257, 257, 5, 68},
  {cont__7_97, &frame__7_53, 258, 258, 5, 62},
  {cont__7_100, &frame__7_53, 260, 271, 5, 19},
  {cont__7_115, &frame__7_53, 272, 272, 60, 60},
  {cont__7_116, &frame__7_53, 272, 272, 23, 61},
  {cont__7_117, &frame__7_53, 272, 272, 5, 61},
  {cont__7_118, &frame__7_53, },
  {entry__7_120, NULL, 273, 273, 46, 70},
  {cont__7_121, &frame__7_120, 273, 273, 34, 70},
  {cont__7_122, &frame__7_120, 273, 273, 70, 70},
  {entry__7_124, NULL, 274, 274, 50, 61},
  {cont__7_125, &frame__7_124, 274, 274, 22, 61},
  {entry__7_128, NULL, 284, 284, 5, 21},
  {cont__7_129, &frame__7_128, 285, 285, 5, 13},
  {entry__7_131, NULL, 287, 287, 44, 70},
  {cont__7_133, &frame__7_131, 287, 287, 5, 71},
  {cont__7_134, &frame__7_131, 287, 287, 71, 71},
  {entry__7_136, NULL, 290, 290, 5, 26},
  {cont__7_137, &frame__7_136, },
  {entry__7_139, NULL, 291, 291, 52, 63},
  {cont__7_140, &frame__7_139, 291, 291, 22, 63},
  {entry__7_143, NULL, 296, 296, 5, 28},
  {cont__7_144, &frame__7_143, 297, 297, 5, 48},
  {cont__7_145, &frame__7_143, 298, 298, 5, 42},
  {cont__7_146, &frame__7_143, },
  {entry__7_148, NULL, 299, 299, 53, 64},
  {cont__7_149, &frame__7_148, 299, 299, 22, 64},
  {entry__7_152, NULL, 303, 303, 27, 53},
  {entry__7_153, NULL, 303, 303, 56, 69},
  {entry__7_156, NULL, 305, 305, 35, 41},
  {entry__7_158, NULL, 306, 306, 5, 37},
  {cont__7_160, &frame__7_158, 307, 307, 5, 38},
  {cont__7_162, &frame__7_158, 307, 307, 58, 58},
  {entry__7_167, NULL, 309, 309, 32, 54},
  {cont__7_169, &frame__7_167, 309, 309, 59, 59},
  {entry__7_177, NULL, 315, 315, 47, 64},
  {cont__7_178, &frame__7_177, 315, 315, 47, 75},
  {cont__7_179, &frame__7_177, 315, 315, 47, 75},
  {entry__7_188, NULL, 321, 321, 45, 63},
  {cont__7_189, &frame__7_188, 321, 321, 63, 63},
  {entry__7_193, NULL, 323, 323, 29, 47},
  {cont__7_194, &frame__7_193, 323, 325, 49, 26},
  {cont__7_198, &frame__7_193, 323, 325, 17, 26},
  {entry__7_204, NULL, 328, 328, 31, 49},
  {cont__7_205, &frame__7_204, 328, 330, 51, 62},
  {cont__7_210, &frame__7_204, 328, 330, 19, 62},
  {entry__7_214, NULL, 333, 333, 31, 49},
  {cont__7_215, &frame__7_214, 335, 335, 51, 71},
  {cont__7_216, &frame__7_214, 335, 335, 38, 72},
  {cont__7_217, &frame__7_214, 333, 336, 51, 64},
  {cont__7_223, &frame__7_214, 333, 336, 19, 64},
  {entry__7_201, NULL, 327, 327, 20, 37},
  {cont__7_202, &frame__7_201, 327, 327, 20, 48},
  {cont__7_203, &frame__7_201, 327, 330, 17, 63},
  {cont__7_211, &frame__7_201, 331, 331, 17, 45},
  {cont__7_212, &frame__7_201, 332, 332, 20, 36},
  {cont__7_213, &frame__7_201, 332, 336, 17, 65},
  {cont__7_224, &frame__7_201, 337, 337, 17, 38},
  {cont__7_225, &frame__7_201, 337, 337, 43, 43},
  {entry__7_185, NULL, 320, 320, 15, 47},
  {cont__7_186, &frame__7_185, 321, 321, 22, 42},
  {cont__7_187, &frame__7_185, 321, 321, 15, 63},
  {cont__7_190, &frame__7_185, 322, 322, 18, 38},
  {cont__7_191, &frame__7_185, 322, 322, 18, 49},
  {cont__7_192, &frame__7_185, 322, 325, 15, 27},
  {cont__7_199, &frame__7_185, 326, 326, 18, 43},
  {cont__7_200, &frame__7_185, 326, 337, 15, 43},
  {cont__7_226, &frame__7_185, 338, 338, 15, 36},
  {cont__7_227, &frame__7_185, 339, 339, 15, 35},
  {cont__7_228, &frame__7_185, 339, 339, 46, 46},
  {entry__7_232, NULL, 342, 342, 29, 47},
  {cont__7_233, &frame__7_232, 342, 343, 49, 68},
  {cont__7_236, &frame__7_232, 342, 343, 17, 68},
  {entry__7_243, NULL, 348, 348, 33, 51},
  {cont__7_244, &frame__7_243, 348, 350, 53, 67},
  {cont__7_249, &frame__7_243, 348, 350, 21, 67},
  {entry__7_241, NULL, 347, 347, 22, 44},
  {cont__7_242, &frame__7_241, 347, 350, 19, 68},
  {entry__7_240, NULL, 346, 350, 17, 69},
  {entry__7_229, NULL, 341, 341, 18, 35},
  {cont__7_230, &frame__7_229, 341, 341, 18, 46},
  {cont__7_231, &frame__7_229, 341, 343, 15, 69},
  {cont__7_237, &frame__7_229, 344, 344, 15, 46},
  {cont__7_238, &frame__7_229, 345, 345, 18, 38},
  {cont__7_239, &frame__7_229, 345, 350, 15, 70},
  {cont__7_250, &frame__7_229, 351, 351, 15, 33},
  {cont__7_251, &frame__7_229, 352, 352, 15, 36},
  {cont__7_252, &frame__7_229, 352, 352, 41, 41},
  {entry__7_181, NULL, 316, 316, 11, 40},
  {cont__7_182, &frame__7_181, 317, 317, 11, 30},
  {cont__7_183, &frame__7_181, 319, 319, 13, 32},
  {cont__7_184, &frame__7_181, 318, 352, 11, 42},
  {entry__7_174, NULL, 313, 313, 7, 32},
  {cont__7_175, &frame__7_174, 315, 315, 9, 42},
  {cont__7_176, &frame__7_174, 315, 315, 9, 75},
  {cont__7_180, &frame__7_174, 314, 352, 7, 44},
  {entry__7_173, NULL, 312, 352, 5, 45},
  {entry__7_256, NULL, 357, 357, 9, 43},
  {cont__7_257, &frame__7_256, 357, 357, 48, 48},
  {entry__7_255, NULL, 356, 357, 7, 48},
  {entry__7_254, NULL, 355, 357, 5, 49},
  {cont__7_258, &frame__7_254, 358, 358, 5, 58},
  {entry__7_260, NULL, 359, 359, 52, 63},
  {cont__7_261, &frame__7_260, 359, 359, 22, 63},
  {entry__7_265, NULL, 361, 361, 47, 57},
  {cont__7_266, &frame__7_265, 361, 361, 34, 63},
  {cont__7_267, &frame__7_265, 361, 361, 28, 63},
  {entry__7_264, NULL, 361, 361, 5, 63},
  {cont__7_268, &frame__7_264, 362, 362, 5, 13},
  {entry__7_272, NULL, 367, 367, 32, 57},
  {cont__7_273, &frame__7_272, 367, 367, 32, 57},
  {entry__7_279, NULL, 377, 377, 22, 52},
  {cont__7_280, &frame__7_279, 377, 377, 52, 52},
  {entry__7_275, NULL, 373, 373, 7, 29},
  {cont__7_276, &frame__7_275, 374, 374, 7, 37},
  {cont__7_277, &frame__7_275, 375, 375, 7, 39},
  {cont__7_278, &frame__7_275, 377, 377, 7, 52},
  {cont__7_281, &frame__7_275, 378, 378, 7, 31},
  {cont__7_282, &frame__7_275, },
  {entry__7_270, NULL, 367, 367, 12, 27},
  {cont__7_271, &frame__7_270, 367, 367, 12, 57},
  {cont__7_274, &frame__7_270, 367, 378, 5, 31},
  {entry__7_285, NULL, 379, 379, 72, 77},
  {entry__7_284, NULL, 379, 379, 40, 77},
  {entry__7_287, NULL, 381, 381, 54, 65},
  {cont__7_288, &frame__7_287, 381, 381, 22, 65},
  {entry__7_295, NULL, 387, 387, 32, 42},
  {cont__7_296, &frame__7_295, 387, 387, 48, 65},
  {cont__7_297, &frame__7_295, 387, 387, 13, 65},
  {entry__7_299, NULL, 389, 389, 13, 34},
  {entry__7_293, NULL, 386, 386, 11, 33},
  {cont__7_294, &frame__7_293, 385, 389, 9, 35},
  {entry__7_292, NULL, 384, 389, 7, 36},
  {entry__7_302, NULL, 390, 390, 38, 54},
  {entry__7_291, NULL, 383, 389, 5, 37},
  {cont__7_301, &frame__7_291, 390, 390, 5, 54},
  {cont__7_303, &frame__7_291, 391, 391, 5, 13},
  {entry__7_306, NULL, 414, 414, 46, 67},
  {entry__7_305, NULL, 414, 414, 5, 67},
  {entry__7_308, NULL, 415, 415, 51, 62},
  {cont__7_309, &frame__7_308, 415, 415, 22, 62},
  {entry__7_315, NULL, 486, 486, 20, 53},
  {cont__7_316, &frame__7_315, 486, 486, 53, 53},
  {entry__7_313, NULL, 485, 485, 5, 22},
  {cont__7_314, &frame__7_313, 486, 486, 5, 53},
  {cont__7_317, &frame__7_313, 486, 486, 53, 53},
  {entry__7_320, NULL, 490, 490, 20, 65},
  {cont__7_321, &frame__7_320, 490, 490, 65, 65},
  {entry__7_318, NULL, 489, 489, 5, 22},
  {cont__7_319, &frame__7_318, 490, 490, 5, 65},
  {cont__7_322, &frame__7_318, 490, 490, 65, 65},
  {entry__7_325, NULL, 494, 494, 20, 72},
  {cont__7_326, &frame__7_325, 494, 494, 72, 72},
  {entry__7_323, NULL, 493, 493, 5, 22},
  {cont__7_324, &frame__7_323, 494, 494, 5, 72},
  {cont__7_327, &frame__7_323, 494, 494, 72, 72},
  {entry__7_330, NULL, 498, 498, 20, 69},
  {cont__7_331, &frame__7_330, 498, 498, 69, 69},
  {entry__7_328, NULL, 497, 497, 5, 22},
  {cont__7_329, &frame__7_328, 498, 498, 5, 69},
  {cont__7_332, &frame__7_328, 498, 498, 69, 69},
  {entry__7_335, NULL, 502, 502, 20, 59},
  {cont__7_336, &frame__7_335, 502, 502, 59, 59},
  {entry__7_333, NULL, 501, 501, 5, 22},
  {cont__7_334, &frame__7_333, 502, 502, 5, 59},
  {cont__7_337, &frame__7_333, 502, 502, 59, 59},
  {entry__7_340, NULL, 506, 506, 20, 67},
  {cont__7_341, &frame__7_340, 506, 506, 67, 67},
  {entry__7_338, NULL, 505, 505, 5, 22},
  {cont__7_339, &frame__7_338, 506, 506, 5, 67},
  {cont__7_342, &frame__7_338, 506, 506, 67, 67},
  {entry__7_345, NULL, 510, 510, 20, 50},
  {cont__7_346, &frame__7_345, 510, 510, 50, 50},
  {entry__7_343, NULL, 509, 509, 5, 22},
  {cont__7_344, &frame__7_343, 510, 510, 5, 50},
  {cont__7_347, &frame__7_343, 510, 510, 50, 50},
  {entry__7_350, NULL, 514, 514, 20, 48},
  {cont__7_351, &frame__7_350, 514, 514, 48, 48},
  {entry__7_348, NULL, 513, 513, 5, 22},
  {cont__7_349, &frame__7_348, 514, 514, 5, 48},
  {cont__7_352, &frame__7_348, 514, 514, 48, 48},
  {entry__7_355, NULL, 518, 518, 20, 48},
  {cont__7_356, &frame__7_355, 518, 518, 48, 48},
  {entry__7_353, NULL, 517, 517, 5, 22},
  {cont__7_354, &frame__7_353, 518, 518, 5, 48},
  {cont__7_357, &frame__7_353, 518, 518, 48, 48},
  {entry__7_360, NULL, 522, 522, 20, 48},
  {cont__7_361, &frame__7_360, 522, 522, 48, 48},
  {entry__7_358, NULL, 521, 521, 5, 22},
  {cont__7_359, &frame__7_358, 522, 522, 5, 48},
  {cont__7_362, &frame__7_358, 522, 522, 48, 48},
  {entry__7_365, NULL, 526, 526, 20, 48},
  {cont__7_366, &frame__7_365, 526, 526, 48, 48},
  {entry__7_363, NULL, 525, 525, 5, 22},
  {cont__7_364, &frame__7_363, 526, 526, 5, 48},
  {cont__7_367, &frame__7_363, 526, 526, 48, 48},
  {entry__7_370, NULL, 530, 530, 20, 48},
  {cont__7_371, &frame__7_370, 530, 530, 48, 48},
  {entry__7_368, NULL, 529, 529, 5, 22},
  {cont__7_369, &frame__7_368, 530, 530, 5, 48},
  {cont__7_372, &frame__7_368, 530, 530, 48, 48},
  {entry__7_374, NULL, 533, 533, 20, 39},
  {cont__7_375, &frame__7_374, 533, 533, 47, 47},
  {entry__7_373, NULL, 533, 533, 5, 47},
  {cont__7_376, &frame__7_373, 533, 533, 47, 47},
  {entry__7_379, NULL, 537, 537, 20, 52},
  {cont__7_380, &frame__7_379, 537, 537, 52, 52},
  {entry__7_377, NULL, 536, 536, 5, 22},
  {cont__7_378, &frame__7_377, 537, 537, 5, 52},
  {cont__7_381, &frame__7_377, 537, 537, 52, 52},
  {entry__7_384, NULL, 541, 541, 20, 49},
  {cont__7_385, &frame__7_384, 541, 541, 49, 49},
  {entry__7_382, NULL, 540, 540, 5, 22},
  {cont__7_383, &frame__7_382, 541, 541, 5, 49},
  {cont__7_386, &frame__7_382, 541, 541, 49, 49},
  {entry__7_390, NULL, 545, 545, 28, 28},
  {cont__7_391, &frame__7_390, 545, 545, 7, 29},
  {cont__7_392, &frame__7_390, 546, 546, 7, 68},
  {entry__7_387, NULL, 544, 544, 8, 33},
  {cont__7_389, &frame__7_387, 544, 546, 5, 68},
  {entry__7_401, NULL, 558, 558, 11, 43},
  {cont__7_402, &frame__7_401, 559, 559, 11, 40},
  {cont__7_403, &frame__7_401, 559, 559, 40, 40},
  {entry__7_406, NULL, 562, 562, 13, 36},
  {entry__7_409, NULL, 565, 565, 36, 76},
  {cont__7_410, &frame__7_409, 565, 565, 36, 76},
  {entry__7_412, NULL, 566, 566, 56, 73},
  {cont__7_413, &frame__7_412, 566, 566, 17, 73},
  {entry__7_416, NULL, 571, 571, 21, 54},
  {entry__7_420, NULL, 575, 575, 25, 55},
  {entry__7_421, NULL, 577, 577, 25, 62},
  {entry__7_417, NULL, 574, 574, 23, 46},
  {cont__7_418, &frame__7_417, 574, 574, 23, 57},
  {cont__7_419, &frame__7_417, 573, 577, 21, 63},
  {entry__7_422, NULL, 579, 579, 21, 53},
  {entry__7_414, NULL, 569, 569, 19, 47},
  {cont__7_415, &frame__7_414, 568, 579, 17, 54},
  {entry__7_407, NULL, 565, 565, 15, 31},
  {cont__7_408, &frame__7_407, 565, 565, 15, 76},
  {cont__7_411, &frame__7_407, 564, 579, 13, 56},
  {entry__7_399, NULL, 557, 557, 12, 41},
  {cont__7_400, &frame__7_399, 557, 559, 9, 40},
  {cont__7_404, &frame__7_399, 561, 561, 11, 30},
  {cont__7_405, &frame__7_399, 560, 579, 9, 58},
  {entry__7_398, NULL, 555, 579, 7, 59},
  {entry__7_426, NULL, 580, 580, 28, 67},
  {entry__7_428, NULL, 581, 581, 20, 46},
  {cont__7_429, &frame__7_428, 581, 581, 46, 46},
  {entry__7_395, NULL, 552, 552, 5, 40},
  {cont__7_397, &frame__7_395, 554, 579, 5, 60},
  {cont__7_423, &frame__7_395, 580, 580, 8, 25},
  {cont__7_424, &frame__7_395, 580, 580, 8, 25},
  {cont__7_425, &frame__7_395, 580, 580, 5, 67},
  {cont__7_427, &frame__7_395, 581, 581, 5, 46},
  {cont__7_430, &frame__7_395, 582, 582, 5, 29},
  {cont__7_431, &frame__7_395, },
  {entry__7_437, NULL, 591, 591, 11, 41},
  {entry__7_439, NULL, 593, 593, 39, 70},
  {cont__7_442, &frame__7_439, 593, 593, 11, 70},
  {cont__7_443, &frame__7_439, 594, 604, 17, 52},
  {cont__7_446, &frame__7_439, 594, 604, 11, 52},
  {entry__7_448, NULL, 606, 606, 9, 35},
  {cont__7_449, &frame__7_448, 608, 608, 29, 49},
  {cont__7_450, &frame__7_448, 609, 609, 42, 62},
  {cont__7_451, &frame__7_448, 607, 610, 15, 11},
  {cont__7_455, &frame__7_448, 607, 610, 9, 11},
  {cont__7_456, &frame__7_448, 611, 611, 37, 57},
  {cont__7_457, &frame__7_448, 611, 611, 9, 59},
  {cont__7_459, &frame__7_448, 612, 612, 9, 38},
  {entry__7_436, NULL, 589, 604, 7, 54},
  {cont__7_447, &frame__7_436, 605, 612, 7, 38},
  {entry__7_461, NULL, 613, 613, 20, 46},
  {cont__7_462, &frame__7_461, 613, 613, 46, 46},
  {entry__7_435, NULL, 588, 612, 5, 39},
  {cont__7_460, &frame__7_435, 613, 613, 5, 46},
  {cont__7_463, &frame__7_435, 614, 614, 5, 29},
  {cont__7_464, &frame__7_435, },
  {entry__7_472, NULL, 621, 621, 50, 72},
  {entry__7_471, NULL, 621, 621, 27, 72},
  {entry__7_476, NULL, 622, 622, 28, 67},
  {entry__7_478, NULL, 623, 623, 20, 46},
  {cont__7_479, &frame__7_478, 623, 623, 46, 46},
  {entry__7_467, NULL, 619, 619, 32, 49},
  {cont__7_468, &frame__7_467, 619, 619, 5, 50},
  {cont__7_470, &frame__7_467, 621, 621, 5, 72},
  {cont__7_473, &frame__7_467, 622, 622, 8, 25},
  {cont__7_474, &frame__7_467, 622, 622, 8, 25},
  {cont__7_475, &frame__7_467, 622, 622, 5, 67},
  {cont__7_477, &frame__7_467, 623, 623, 5, 46},
  {cont__7_480, &frame__7_467, 624, 624, 5, 29},
  {cont__7_481, &frame__7_467, },
  {entry__7_485, NULL, 630, 632, 11, 13},
  {entry__7_487, NULL, 634, 638, 11, 13},
  {entry__7_484, NULL, 628, 638, 7, 15},
  {cont__7_489, &frame__7_484, 639, 639, 7, 22},
  {entry__7_491, NULL, 640, 640, 20, 46},
  {cont__7_492, &frame__7_491, 640, 640, 46, 46},
  {entry__7_483, NULL, 627, 639, 5, 22},
  {cont__7_490, &frame__7_483, 640, 640, 5, 46},
  {cont__7_493, &frame__7_483, 641, 641, 5, 29},
  {cont__7_494, &frame__7_483, },
  {entry__7_497, NULL, 642, 642, 72, 77},
  {entry__7_496, NULL, 642, 642, 40, 77},
  {entry__7_499, NULL, 643, 643, 51, 71},
  {cont__7_501, &frame__7_499, 643, 643, 43, 71},
  {entry__7_503, NULL, 644, 644, 45, 62},
  {cont__7_505, &frame__7_503, 644, 644, 37, 62},
  {entry__7_507, NULL, 645, 645, 47, 68},
  {cont__7_509, &frame__7_507, 645, 645, 39, 68},
  {entry__7_513, NULL, 648, 648, 5, 31},
  {cont__7_515, &frame__7_513, 649, 649, 5, 31},
  {cont__7_517, &frame__7_513, 649, 649, 36, 36},
  {entry__7_519, NULL, 650, 650, 43, 62},
  {cont__7_522, &frame__7_519, 650, 650, 35, 62},
  {entry__7_528, NULL, 670, 705, 5, 12},
  {entry__7_533, NULL, 706, 706, 40, 65},
  {cont__7_535, &frame__7_533, 706, 706, 40, 65},
  {entry__7_537, NULL, 707, 708, 5, 35},
  {entry__7_542, NULL, 750, 750, 41, 68},
  {cont__7_545, &frame__7_542, 750, 750, 33, 68},
  {entry__7_550, NULL, 753, 753, 15, 45},
  {cont__7_553, &frame__7_550, 753, 753, 7, 45},
  {entry__7_561, NULL, 756, 756, 15, 64},
  {cont__7_564, &frame__7_561, 756, 756, 7, 64},
  {entry__7_568, NULL, 758, 758, 15, 48},
  {cont__7_571, &frame__7_568, 758, 758, 7, 48},
  {entry__7_575, NULL, 760, 760, 15, 51},
  {cont__7_578, &frame__7_575, 760, 760, 7, 51},
  {entry__7_547, NULL, 752, 752, 8, 29},
  {cont__7_548, &frame__7_547, 752, 752, 8, 44},
  {cont__7_549, &frame__7_547, 752, 753, 5, 45},
  {cont__7_554, &frame__7_547, 754, 754, 13, 46},
  {cont__7_557, &frame__7_547, 754, 754, 5, 46},
  {cont__7_558, &frame__7_547, 755, 755, 8, 29},
  {cont__7_559, &frame__7_547, 755, 755, 8, 46},
  {cont__7_560, &frame__7_547, 755, 756, 5, 64},
  {cont__7_565, &frame__7_547, 757, 757, 10, 31},
  {cont__7_566, &frame__7_547, 757, 757, 33, 59},
  {cont__7_567, &frame__7_547, 757, 758, 5, 48},
  {cont__7_572, &frame__7_547, 759, 759, 10, 31},
  {cont__7_573, &frame__7_547, 759, 759, 33, 61},
  {cont__7_574, &frame__7_547, 759, 760, 5, 51},
  {entry__7_590, NULL, 770, 770, 57, 57},
  {cont__7_591, &frame__7_590, 770, 770, 13, 58},
  {cont__7_592, &frame__7_590, 770, 770, 5, 58},
  {entry__7_597, NULL, 782, 782, 7, 45},
  {entry__7_599, NULL, 784, 784, 15, 47},
  {cont__7_602, &frame__7_599, 784, 784, 7, 47},
  {entry__7_609, NULL, 790, 790, 51, 51},
  {cont__7_610, &frame__7_609, 790, 790, 13, 52},
  {cont__7_611, &frame__7_609, 790, 790, 5, 52},
  {entry__7_618, NULL, 804, 804, 26, 43},
  {cont__7_619, &frame__7_618, 804, 804, 13, 50},
  {cont__7_623, &frame__7_618, 804, 804, 7, 50},
  {entry__7_617, NULL, 803, 804, 5, 50},
  {entry__7_628, NULL, 807, 807, 49, 75},
  {cont__7_631, &frame__7_628, 807, 807, 43, 75},
  {entry__7_635, NULL, 811, 811, 42, 69},
  {cont__7_638, &frame__7_635, 811, 811, 36, 69},
  {entry__7_646, NULL, 829, 829, 38, 44},
  {cont__7_647, &frame__7_646, 829, 829, 38, 45},
  {cont__7_648, &frame__7_646, 829, 829, 7, 45},
  {cont__7_649, &frame__7_646, 830, 831, 13, 43},
  {cont__7_652, &frame__7_646, 830, 831, 7, 43},
  {entry__7_653, NULL, 833, 833, 7, 16},
  {entry__7_658, NULL, 843, 843, 5, 32},
  {cont__7_659, &frame__7_658, 844, 851, 11, 38},
  {cont__7_668, &frame__7_658, 844, 851, 5, 38},
  {entry__7_676, NULL, 857, 857, 13, 58},
  {cont__7_680, &frame__7_676, 857, 857, 5, 58},
  {entry__7_683, NULL, 860, 860, 13, 48},
  {cont__7_687, &frame__7_683, 860, 860, 5, 48},
  {entry__7_691, NULL, 864, 872, 7, 10},
  {entry__7_693, NULL, 874, 880, 13, 39},
  {cont__7_696, &frame__7_693, 874, 880, 7, 39},
  {entry__7_698, NULL, 882, 882, 5, 39},
  {cont__7_699, &frame__7_698, 883, 883, 13, 43},
  {cont__7_702, &frame__7_698, 883, 883, 5, 43},
  {entry__7_707, NULL, 890, 895, 7, 30},
  {entry__7_709, NULL, 897, 904, 13, 39},
  {cont__7_712, &frame__7_709, 897, 904, 7, 39},
  {entry__7_714, NULL, 906, 906, 27, 47},
  {cont__7_715, &frame__7_714, 906, 906, 13, 52},
  {cont__7_718, &frame__7_714, 906, 906, 5, 52},
  {entry__7_724, NULL, 914, 914, 13, 42},
  {cont__7_727, &frame__7_724, 914, 914, 5, 42},
  {entry__7_730, NULL, 918, 923, 7, 33},
  {entry__7_732, NULL, 925, 932, 13, 39},
  {cont__7_735, &frame__7_732, 925, 932, 7, 39},
  {entry__7_737, NULL, 934, 934, 27, 47},
  {cont__7_738, &frame__7_737, 934, 934, 13, 52},
  {cont__7_741, &frame__7_737, 934, 934, 5, 52},
  {entry__7_753, NULL, 944, 944, 30, 47},
  {cont__7_755, &frame__7_753, 944, 944, 14, 57},
  {cont__7_756, &frame__7_753, 944, 944, 11, 57},
  {entry__7_757, NULL, 945, 945, 11, 19},
  {entry__7_763, NULL, 951, 954, 17, 47},
  {cont__7_769, &frame__7_763, 951, 954, 11, 47},
  {entry__7_770, NULL, 956, 959, 17, 43},
  {cont__7_776, &frame__7_770, 956, 959, 11, 43},
  {entry__7_777, NULL, 961, 964, 17, 27},
  {cont__7_783, &frame__7_777, 961, 964, 11, 27},
  {entry__7_784, NULL, 966, 969, 17, 45},
  {cont__7_790, &frame__7_784, 966, 969, 11, 45},
  {entry__7_791, NULL, 971, 974, 17, 60},
  {cont__7_798, &frame__7_791, 971, 974, 11, 60},
  {entry__7_750, NULL, 943, 943, 11, 30},
  {cont__7_752, &frame__7_750, 941, 945, 7, 20},
  {cont__7_759, &frame__7_750, 947, 947, 7, 42},
  {cont__7_761, &frame__7_750, 949, 949, 9, 30},
  {cont__7_762, &frame__7_750, 948, 974, 7, 62},
  {entry__7_747, NULL, 940, 940, 12, 29},
  {cont__7_748, &frame__7_747, 940, 940, 12, 40},
  {cont__7_749, &frame__7_747, 940, 974, 5, 63},
  {entry__7_801, NULL, 977, 979, 5, 31},
  {entry__7_804, NULL, 982, 985, 7, 10},
  {entry__7_806, NULL, 987, 994, 13, 39},
  {cont__7_809, &frame__7_806, 987, 994, 7, 39},
  {entry__7_811, NULL, 996, 996, 27, 47},
  {cont__7_812, &frame__7_811, 996, 996, 13, 52},
  {cont__7_815, &frame__7_811, 996, 996, 5, 52},
  {entry__7_831, NULL, 1003, 1003, 60, 75},
  {cont__7_832, &frame__7_831, 1003, 1003, 43, 75},
  {cont__7_833, &frame__7_831, 1003, 1003, 43, 75},
  {entry__7_835, NULL, 1004, 1005, 19, 37},
  {cont__7_838, &frame__7_835, 1004, 1005, 13, 37},
  {entry__7_844, NULL, 1010, 1011, 23, 44},
  {cont__7_847, &frame__7_844, 1010, 1011, 17, 44},
  {entry__7_841, NULL, 1009, 1009, 18, 38},
  {cont__7_842, &frame__7_841, 1009, 1009, 18, 38},
  {cont__7_843, &frame__7_841, 1009, 1011, 15, 45},
  {entry__7_851, NULL, 1013, 1014, 23, 46},
  {cont__7_854, &frame__7_851, 1013, 1014, 17, 46},
  {entry__7_848, NULL, 1012, 1012, 18, 46},
  {cont__7_849, &frame__7_848, 1012, 1012, 18, 46},
  {cont__7_850, &frame__7_848, 1012, 1014, 15, 47},
  {entry__7_855, NULL, 1016, 1017, 23, 49},
  {cont__7_858, &frame__7_855, 1016, 1017, 17, 49},
  {entry__7_839, NULL, 1007, 1007, 13, 37},
  {cont__7_840, &frame__7_839, 1008, 1017, 13, 51},
  {entry__7_824, NULL, 1001, 1001, 28, 50},
  {cont__7_825, &frame__7_824, 1001, 1001, 52, 64},
  {cont__7_826, &frame__7_824, 1001, 1001, 9, 65},
  {cont__7_827, &frame__7_824, 1003, 1003, 15, 37},
  {cont__7_829, &frame__7_824, 1003, 1003, 11, 38},
  {cont__7_830, &frame__7_824, 1003, 1003, 11, 75},
  {cont__7_834, &frame__7_824, 1002, 1017, 9, 53},
  {entry__7_822, NULL, 1000, 1000, 10, 37},
  {cont__7_823, &frame__7_822, 1000, 1017, 7, 54},
  {entry__7_861, NULL, 1019, 1019, 33, 55},
  {cont__7_862, &frame__7_861, 1019, 1019, 33, 66},
  {cont__7_863, &frame__7_861, 1019, 1019, 17, 71},
  {cont__7_866, &frame__7_861, 1019, 1019, 9, 71},
  {entry__7_859, NULL, 1018, 1018, 10, 39},
  {cont__7_860, &frame__7_859, 1018, 1019, 7, 71},
  {entry__7_817, NULL, 998, 998, 11, 37},
  {cont__7_820, &frame__7_817, 998, 998, 5, 37},
  {cont__7_821, &frame__7_817, 999, 1019, 5, 72},
  {entry__7_869, NULL, 1023, 1027, 7, 10},
  {entry__7_871, NULL, 1029, 1036, 13, 39},
  {cont__7_874, &frame__7_871, 1029, 1036, 7, 39},
  {entry__7_876, NULL, 1038, 1038, 27, 47},
  {cont__7_877, &frame__7_876, 1038, 1038, 13, 52},
  {cont__7_880, &frame__7_876, 1038, 1038, 5, 52},
  {entry__7_887, NULL, 1042, 1044, 5, 30},
  {entry__7_892, NULL, 1046, 1046, 53, 64},
  {cont__7_893, &frame__7_892, 1046, 1046, 22, 64},
  {entry__7_1, NULL, 231, 231, 3, 38},
  {cont__7_49, &frame__7_1, 232, 232, 32, 68},
  {cont__7_51, &frame__7_1, 232, 232, 3, 69},
  {cont__7_52, &frame__7_1, 239, 272, 3, 61},
  {cont__7_119, &frame__7_1, 273, 273, 3, 70},
  {cont__7_123, &frame__7_1, 274, 274, 3, 61},
  {cont__7_127, &frame__7_1, 275, 285, 3, 13},
  {cont__7_130, &frame__7_1, 286, 287, 3, 71},
  {cont__7_135, &frame__7_1, 288, 290, 3, 26},
  {cont__7_138, &frame__7_1, 291, 291, 3, 63},
  {cont__7_142, &frame__7_1, 292, 298, 3, 42},
  {cont__7_147, &frame__7_1, 299, 299, 3, 64},
  {cont__7_151, &frame__7_1, 302, 303, 3, 70},
  {cont__7_154, &frame__7_1, 305, 305, 6, 30},
  {cont__7_155, &frame__7_1, 305, 305, 6, 41},
  {cont__7_157, &frame__7_1, 305, 307, 3, 58},
  {cont__7_163, &frame__7_1, 308, 308, 3, 30},
  {cont__7_165, &frame__7_1, 309, 309, 6, 29},
  {cont__7_166, &frame__7_1, 309, 309, 3, 59},
  {cont__7_170, &frame__7_1, 310, 310, 3, 29},
  {cont__7_172, &frame__7_1, 311, 352, 3, 46},
  {cont__7_253, &frame__7_1, 353, 358, 3, 58},
  {cont__7_259, &frame__7_1, 359, 359, 3, 63},
  {cont__7_263, &frame__7_1, 360, 362, 3, 13},
  {cont__7_269, &frame__7_1, 366, 378, 3, 32},
  {cont__7_283, &frame__7_1, 379, 379, 3, 77},
  {cont__7_286, &frame__7_1, 381, 381, 3, 65},
  {cont__7_290, &frame__7_1, 382, 391, 3, 13},
  {cont__7_304, &frame__7_1, 413, 414, 3, 67},
  {cont__7_307, &frame__7_1, 415, 415, 3, 62},
  {cont__7_311, &frame__7_1, 416, 416, 3, 28},
  {cont__7_312, &frame__7_1, 548, 548, 3, 49},
  {cont__7_394, &frame__7_1, 549, 582, 3, 29},
  {cont__7_432, &frame__7_1, 583, 583, 3, 48},
  {cont__7_434, &frame__7_1, 585, 614, 3, 29},
  {cont__7_465, &frame__7_1, 615, 615, 3, 39},
  {cont__7_466, &frame__7_1, 616, 624, 3, 29},
  {cont__7_482, &frame__7_1, 625, 641, 3, 29},
  {cont__7_495, &frame__7_1, 642, 642, 3, 77},
  {cont__7_498, &frame__7_1, 643, 643, 3, 71},
  {cont__7_502, &frame__7_1, 644, 644, 3, 62},
  {cont__7_506, &frame__7_1, 645, 645, 3, 68},
  {cont__7_510, &frame__7_1, 646, 646, 10, 34},
  {cont__7_511, &frame__7_1, 646, 646, 3, 42},
  {cont__7_512, &frame__7_1, 647, 649, 3, 36},
  {cont__7_518, &frame__7_1, 650, 650, 3, 62},
  {cont__7_523, &frame__7_1, 651, 668, 3, 18},
  {cont__7_525, &frame__7_1, 669, 669, 10, 35},
  {cont__7_527, &frame__7_1, 669, 705, 3, 13},
  {cont__7_530, &frame__7_1, 706, 706, 10, 35},
  {cont__7_532, &frame__7_1, 706, 706, 10, 65},
  {cont__7_536, &frame__7_1, 706, 708, 3, 36},
  {cont__7_539, &frame__7_1, 709, 749, 3, 10},
  {cont__7_541, &frame__7_1, 750, 750, 3, 68},
  {cont__7_546, &frame__7_1, 751, 760, 3, 52},
  {cont__7_579, &frame__7_1, 761, 762, 3, 19},
  {cont__7_581, &frame__7_1, 763, 763, 3, 49},
  {cont__7_582, &frame__7_1, 764, 764, 3, 46},
  {cont__7_583, &frame__7_1, 765, 766, 3, 10},
  {cont__7_585, &frame__7_1, 767, 768, 3, 38},
  {cont__7_587, &frame__7_1, 769, 769, 6, 45},
  {cont__7_588, &frame__7_1, 769, 769, 6, 45},
  {cont__7_589, &frame__7_1, 769, 770, 3, 58},
  {cont__7_593, &frame__7_1, 771, 771, 3, 16},
  {cont__7_595, &frame__7_1, 772, 772, 3, 30},
  {cont__7_596, &frame__7_1, 780, 784, 3, 48},
  {cont__7_603, &frame__7_1, 785, 787, 3, 52},
  {cont__7_605, &frame__7_1, 788, 788, 3, 75},
  {cont__7_606, &frame__7_1, 789, 789, 6, 39},
  {cont__7_607, &frame__7_1, 789, 789, 6, 39},
  {cont__7_608, &frame__7_1, 789, 790, 3, 52},
  {cont__7_612, &frame__7_1, 791, 793, 3, 6},
  {cont__7_614, &frame__7_1, 794, 801, 3, 24},
  {cont__7_616, &frame__7_1, 802, 804, 3, 51},
  {cont__7_624, &frame__7_1, 805, 805, 3, 16},
  {cont__7_626, &frame__7_1, 806, 806, 3, 27},
  {cont__7_627, &frame__7_1, 807, 807, 3, 75},
  {cont__7_632, &frame__7_1, 808, 810, 3, 44},
  {cont__7_634, &frame__7_1, 811, 811, 3, 69},
  {cont__7_639, &frame__7_1, 812, 825, 9, 10},
  {cont__7_642, &frame__7_1, 812, 825, 3, 10},
  {cont__7_643, &frame__7_1, 826, 826, 3, 44},
  {cont__7_645, &frame__7_1, 827, 833, 3, 17},
  {cont__7_655, &frame__7_1, 834, 841, 3, 6},
  {cont__7_657, &frame__7_1, 842, 851, 3, 39},
  {cont__7_669, &frame__7_1, 852, 852, 3, 22},
  {cont__7_670, &frame__7_1, 853, 853, 3, 26},
  {cont__7_671, &frame__7_1, 854, 855, 9, 47},
  {cont__7_674, &frame__7_1, 854, 855, 3, 47},
  {cont__7_675, &frame__7_1, 856, 857, 3, 58},
  {cont__7_681, &frame__7_1, 858, 858, 3, 29},
  {cont__7_682, &frame__7_1, 859, 860, 3, 48},
  {cont__7_688, &frame__7_1, 861, 861, 3, 15},
  {cont__7_690, &frame__7_1, 862, 880, 3, 41},
  {cont__7_697, &frame__7_1, 881, 883, 3, 43},
  {cont__7_703, &frame__7_1, 884, 886, 3, 43},
  {cont__7_705, &frame__7_1, 887, 887, 3, 25},
  {cont__7_706, &frame__7_1, 888, 904, 3, 41},
  {cont__7_713, &frame__7_1, 905, 906, 3, 52},
  {cont__7_719, &frame__7_1, 907, 910, 9, 45},
  {cont__7_722, &frame__7_1, 907, 910, 3, 45},
  {cont__7_723, &frame__7_1, 911, 914, 3, 42},
  {cont__7_728, &frame__7_1, 915, 915, 3, 25},
  {cont__7_729, &frame__7_1, 916, 932, 3, 41},
  {cont__7_736, &frame__7_1, 933, 934, 3, 52},
  {cont__7_742, &frame__7_1, 935, 938, 9, 45},
  {cont__7_745, &frame__7_1, 935, 938, 3, 45},
  {cont__7_746, &frame__7_1, 939, 974, 3, 64},
  {cont__7_799, &frame__7_1, 975, 975, 3, 25},
  {cont__7_800, &frame__7_1, 976, 979, 3, 32},
  {cont__7_803, &frame__7_1, 980, 994, 3, 41},
  {cont__7_810, &frame__7_1, 995, 996, 3, 52},
  {cont__7_816, &frame__7_1, 997, 1019, 3, 73},
  {cont__7_867, &frame__7_1, 1020, 1020, 3, 25},
  {cont__7_868, &frame__7_1, 1021, 1036, 3, 41},
  {cont__7_875, &frame__7_1, 1037, 1038, 3, 52},
  {cont__7_881, &frame__7_1, 1039, 1039, 3, 25},
  {cont__7_882, &frame__7_1, 1040, 1040, 11, 58},
  {cont__7_885, &frame__7_1, 1040, 1040, 3, 58},
  {cont__7_886, &frame__7_1, 1041, 1044, 3, 31},
  {cont__7_889, &frame__7_1, 1045, 1045, 3, 15},
  {cont__7_891, &frame__7_1, 1046, 1046, 3, 64},
  {cont__7_895, &frame__7_1, 1046, 1046, 64, 64}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *number__6;
static NODE *character__35;
static NODE *number__99;
static NODE *character__47;
static NODE *number__0;
static NODE *number__3;
static NODE *number__4;
static NODE *number__0xffffffffffffffff;
static NODE *number__0xffffffff;
static NODE *character__60;
static NODE *character__34;
static NODE *number__5;
static NODE *character__39;
static NODE *character__32;
static NODE *character__101;
static NODE *number__1;
static NODE *character__69;
static NODE *character__46;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  "sim2c",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "sim2c",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("sim2c.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__sim2c(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 57: "std__if" = 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10_1;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 58: "std__is_defined" = 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10_3;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void cont__10_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 59: "std__equal" = 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10_5;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_6;
}
static void cont__10_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 60: "std__less" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10_7;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_8;
}
static void cont__10_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 61: "std__length_of" = 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10_9;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_10;
}
static void cont__10_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 62: "std__is_empty" = 5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10_11;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_12;
}
static void cont__10_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 63: "std__unless" = 6
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10_13;
  arguments->slots[1] = number__6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_14;
}
static void cont__10_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__7 = arguments->slots[0];
  // 55: $sim2c::privileged_polymorphic_functions
  // 56:   table
  // 57:     "std__if" = 0
  // 58:     "std__is_defined" = 1
  // 59:     "std__equal" = 2
  // 60:     "std__less" = 3
  // 61:     "std__length_of" = 4
  // 62:     "std__is_empty" = 5
  // 63:     "std__unless" = 6
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = temp__3;
  arguments->slots[3] = temp__4;
  arguments->slots[4] = temp__5;
  arguments->slots[5] = temp__6;
  arguments->slots[6] = temp__7;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__10_15;
}
static void cont__10_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.sim2c__privileged_polymorphic_functions, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__1_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 40: write chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 34: writeln "<newline>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1_5;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 36: writeln "<indent_marker>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1_7;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 38: writeln "<outdent_marker>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1_9;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 39: :
  // 40:   write chr
  frame->slots[1] /* temp__1 */ = create_closure(entry__1_3, 0);
  // 31: case
  // 32:   chr
  // 33:   newline:
  // 34:     writeln "<newline>"
  // 35:   indent_marker:
  // 36:     writeln "<indent_marker>"
  // 37:   outdent_marker:
  // 38:     writeln "<outdent_marker>"
  // 39:   :
  // 40:     write chr
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = get__newline();
  arguments->slots[2] = func__1_4;
  arguments->slots[3] = get__indent_marker();
  arguments->slots[4] = func__1_6;
  arguments->slots[5] = get__outdent_marker();
  arguments->slots[6] = func__1_8;
  arguments->slots[7] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 30: for_each source: (chr)
  // 31:   case
  // 32:     chr
  // 33:     newline:
  // 34:       writeln "<newline>"
  // 35:     indent_marker:
  // 36:       writeln "<indent_marker>"
  // 37:     outdent_marker:
  // 38:       writeln "<outdent_marker>"
  // 39:     :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = func__1_2;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 53: ewrite chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 47: ewriteln "<newline>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2_5;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 49: ewriteln "<indent_marker>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2_7;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 51: ewriteln "<outdent_marker>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2_9;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 52: :
  // 53:   ewrite chr
  frame->slots[1] /* temp__1 */ = create_closure(entry__2_3, 0);
  // 44: case
  // 45:   chr
  // 46:   newline:
  // 47:     ewriteln "<newline>"
  // 48:   indent_marker:
  // 49:     ewriteln "<indent_marker>"
  // 50:   outdent_marker:
  // 51:     ewriteln "<outdent_marker>"
  // 52:   :
  // 53:     ewrite chr
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = get__newline();
  arguments->slots[2] = func__2_4;
  arguments->slots[3] = get__indent_marker();
  arguments->slots[4] = func__2_6;
  arguments->slots[5] = get__outdent_marker();
  arguments->slots[6] = func__2_8;
  arguments->slots[7] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // source: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 43: for_each source: (chr)
  // 44:   case
  // 45:     chr
  // 46:     newline:
  // 47:       ewriteln "<newline>"
  // 48:     indent_marker:
  // 49:       ewriteln "<indent_marker>"
  // 50:     outdent_marker:
  // 51:       ewriteln "<outdent_marker>"
  // 52:     :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  arguments->slots[1] = func__2_2;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  // id: 1
  frame->slots[1] /* id */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 66: ... "
  // 67:   static void type__@(name)(void);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__4_2;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__4_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__4_4;
}
static void cont__4_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 66: write_to_declarations "
  // 67:   static void type__@(name)(void);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__write_to_declarations();
  func = myself->type;
  frame->cont = cont__4_5;
}
static void cont__4_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 68: ... "
  // 69:   static void type__@(name)(void) {
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__4_6;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__4_7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__4_8;
}
static void cont__4_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 68: write_to_functions "
  // 69:   static void type__@(name)(void) {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__write_to_functions();
  func = myself->type;
  frame->cont = cont__4_9;
}
static void cont__4_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 70: $id privileged_polymorphic_functions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__privileged_polymorphic_functions();
  func = myself->type;
  frame->cont = cont__4_10;
}
static void cont__4_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* id */, arguments->slots[0]);
  // 72: id.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* id */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__4_11;
}
static void cont__4_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 72: ... :
  // 73:   # ATTENTION: do not optimize to get better error messages
  // 74:   
  // 75:   #if
  // 76:     id < 8:
  // 77:       write_to_functions "
  // 78:         @
  // 79:           myself = (NODE @
  // 80:         *)arguments->slots[0]->attributes->nodes[0]->nodes[@(id)];
  // 81:     :
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__4_12, 0);
  // 91: :
  // 92:   write_to_functions
  // 93:     "  myself = get_attribute(arguments->slots[0], poly_idx__@(name));@nl;"
  frame->slots[4] /* temp__3 */ = create_closure(entry__4_17, 0);
  // 71: if
  // 72:   id.is_defined:
  // 73:     # ATTENTION: do not optimize to get better error messages
  // 74:     
  // 75:     #if
  // 76:       id < 8:
  // 77:         write_to_functions "
  // 78:           @
  // 79:             myself = (NODE @
  // 80:           *)arguments->slots[0]->attributes->nodes[0]->nodes[@(id)];
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__4_21;
}
static void entry__4_12(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // id: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: ... "
  // 88:   @
  // 89:     myself = get_attribute(arguments->slots[0], poly_idx__@(name)); // @
  // 90:   @(id)@nl;@
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__4_13;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__4_14;
  arguments->slots[3] = frame->slots[1] /* id */;
  arguments->slots[4] = string__4_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__4_16;
}
static void cont__4_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 87: write_to_functions "
  // 88:   @
  // 89:     myself = get_attribute(arguments->slots[0], poly_idx__@(name)); // @
  // 90:   @(id)@nl;@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_to_functions();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_17(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 93: "  myself = get_attribute(arguments->slots[0], poly_idx__@(name));@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__4_18;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__4_19;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__4_20;
}
static void cont__4_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 92: write_to_functions
  // 93:   "  myself = get_attribute(arguments->slots[0], poly_idx__@(name));@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_to_functions();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  //  98: ... "
  //  99:     if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
  // 100:       if (argument_count != 1) {
  // 101:         if (argument_count != 2) invalid_arguments_error();
  // 102:         NODE *attr = arguments->slots[1];
  // 103:         NODE *temp = clone_object_and_attributes(arguments->slots[0]);
  // 104:         update_start_p = node_p;
  // 105:         set_attribute_value(temp->attributes, poly_idx__@(name), attr);
  // 106:         arguments = node_p;
  // 107:         argument_count = 1;
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__4_22;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__4_23;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__4_24;
}
static void cont__4_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  //  98: write_to_functions "
  //  99:     if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
  // 100:       if (argument_count != 1) {
  // 101:         if (argument_count != 2) invalid_arguments_error();
  // 102:         NODE *attr = arguments->slots[1];
  // 103:         NODE *temp = clone_object_and_attributes(arguments->slots[0]);
  // 104:         update_start_p = node_p;
  // 105:         set_attribute_value(temp->attributes, poly_idx__@(name), attr);
  // 106:         arguments = node_p;
  // 107:         argument_count = 1;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_to_functions();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__5_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 120: ... "__" = "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5_2;
  arguments->slots[1] = string__5_3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__5_4;
}
static void cont__5_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 120: ... replace_all(name "__" = "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__5_5;
}
static void cont__5_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 120: ... -> replace_all(name "__" = "::")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_1(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // name: 0
  // curr_info: 1
  // info: 2
  // return: 3
  frame->slots[3] /* return */ = create_continuation();
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 130: curr_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* curr_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__6_2;
}
static void cont__6_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 130: ... :
  // 131:   case
  // 132:     variable_kind_of(curr_info)
  // 133:     POLYMORPHIC:
  // 134:       case
  // 135:         variable_kind_of(info)
  // 136:         POLYMORPHIC, STATIC_SINGLE:
  // 137:           return undefined
  // 138:         :
  // 139:           Error "
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__6_3, 0);
  // 196: :
  // 197:   return info
  frame->slots[6] /* temp__3 */ = create_closure(entry__6_67, 0);
  // 129: if
  // 130:   curr_info.is_defined:
  // 131:     case
  // 132:       variable_kind_of(curr_info)
  // 133:       POLYMORPHIC:
  // 134:         case
  // 135:           variable_kind_of(info)
  // 136:           POLYMORPHIC, STATIC_SINGLE:
  // 137:             return undefined
  // 138:           :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__6_68;
}
static void entry__6_60(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_61(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 192: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._demangled;
  func = myself->type;
  frame->cont = cont__6_62;
}
static void cont__6_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 191: ... "
  // 192:   The symbol "@(name.demangled)" is used as a single-assign @
  // 193:   dynamic and as a multi-assign dynamic!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6_63;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__6_64;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__6_65;
}
static void cont__6_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 191: Error "
  // 192:   The symbol "@(name.demangled)" is used as a single-assign @
  // 193:   dynamic and as a multi-assign dynamic!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_66(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: return info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_41(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_42(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._demangled;
  func = myself->type;
  frame->cont = cont__6_43;
}
static void cont__6_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... "
  // 175:   The symbol "@(name.demangled)" is used as a single-assign @
  // 176:   dynamic and is assigned to!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6_44;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__6_45;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__6_46;
}
static void cont__6_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: Error "
  // 175:   The symbol "@(name.demangled)" is used as a single-assign @
  // 176:   dynamic and is assigned to!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_47(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._demangled;
  func = myself->type;
  frame->cont = cont__6_48;
}
static void cont__6_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 178: ... "
  // 179:   The symbol "@(name.demangled)" is used as a single-assign @
  // 180:   dynamic and as a multi-assign dynamic!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6_49;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__6_50;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__6_51;
}
static void cont__6_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 178: Error "
  // 179:   The symbol "@(name.demangled)" is used as a single-assign @
  // 180:   dynamic and as a multi-assign dynamic!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_26(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 157: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_27(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 160: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._demangled;
  func = myself->type;
  frame->cont = cont__6_28;
}
static void cont__6_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 159: ... "
  // 160:   The symbol "@(name.demangled)" is used as a single-assign @
  // 161:   dynamic and is assigned to!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6_29;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__6_30;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__6_31;
}
static void cont__6_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 159: Error "
  // 160:   The symbol "@(name.demangled)" is used as a single-assign @
  // 161:   dynamic and is assigned to!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_32(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: return info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_16(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 146: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_17(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 148: return info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 137: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_9(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 140: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._demangled;
  func = myself->type;
  frame->cont = cont__6_10;
}
static void cont__6_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 139: ... "
  // 140:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 141:   function and cannot be used otherwise!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6_11;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__6_12;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__6_13;
}
static void cont__6_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 139: Error "
  // 140:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 141:   function and cannot be used otherwise!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_5(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // info: 0
  // return: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  frame->slots[2] = myself->closure.frame->slots[3]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 135: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__6_6;
}
static void cont__6_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 136: POLYMORPHIC, STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__POLYMORPHIC();
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__6_7;
}
static void cont__6_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 136: ... :
  // 137:   return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__6_8, 0);
  // 138: :
  // 139:   Error "
  // 140:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 141:     function and cannot be used otherwise!@
  frame->slots[6] /* temp__4 */ = create_closure(entry__6_9, 0);
  // 134: case
  // 135:   variable_kind_of(info)
  // 136:   POLYMORPHIC, STATIC_SINGLE:
  // 137:     return undefined
  // 138:   :
  // 139:     Error "
  // 140:       The symbol "@(name.demangled)" is used as a polymorphic @
  // 141:       function and cannot be used otherwise!@
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  arguments->slots[3] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_14(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 144: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__6_15;
}
static void cont__6_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 145: ... :
  // 146:   return undefined
  frame->slots[3] /* temp__2 */ = create_closure(entry__6_16, 0);
  // 147: :
  // 148:   return info
  frame->slots[4] /* temp__3 */ = create_closure(entry__6_17, 0);
  // 143: case
  // 144:   variable_kind_of(info)
  // 145:   STATIC_SINGLE:
  // 146:     return undefined
  // 147:   :
  // 148:     return info
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_18(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // info: 0
  // name: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 151: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__6_19;
}
static void cont__6_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 152: ... :
  // 153:   Error "
  // 154:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 155:     function and id assigned to!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__6_20, 0);
  // 156: STATIC_SINGLE, STATIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_SINGLE();
  arguments->slots[1] = get__STATIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__6_25;
}
static void entry__6_20(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 154: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._demangled;
  func = myself->type;
  frame->cont = cont__6_21;
}
static void cont__6_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 153: ... "
  // 154:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 155:   function and id assigned to!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6_22;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__6_23;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__6_24;
}
static void cont__6_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 153: Error "
  // 154:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 155:   function and id assigned to!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__6_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 156: ... :
  // 157:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__6_26, 0);
  // 158: ... :
  // 159:   Error "
  // 160:     The symbol "@(name.demangled)" is used as a single-assign @
  // 161:     dynamic and is assigned to!@
  frame->slots[7] /* temp__5 */ = create_closure(entry__6_27, 0);
  // 162: ... :
  // 163:   return info
  frame->slots[8] /* temp__6 */ = create_closure(entry__6_32, 0);
  // 150: case
  // 151:   variable_kind_of(info)
  // 152:   POLYMORPHIC:
  // 153:     Error "
  // 154:       The symbol "@(name.demangled)" is used as a polymorphic @
  // 155:       function and id assigned to!@
  // 156:   STATIC_SINGLE, STATIC_MULTI:
  // 157:     return undefined
  // 158:   DYNAMIC_SINGLE:
  // 159:     Error "
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__POLYMORPHIC();
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = frame->slots[5] /* temp__3 */;
  arguments->slots[4] = frame->slots[6] /* temp__4 */;
  arguments->slots[5] = get__DYNAMIC_SINGLE();
  arguments->slots[6] = frame->slots[7] /* temp__5 */;
  arguments->slots[7] = get__DYNAMIC_MULTI();
  arguments->slots[8] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_33(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // info: 0
  // name: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 166: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__6_34;
}
static void cont__6_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 167: ... :
  // 168:   Error "
  // 169:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 170:     function and as a single-assign dynamic!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__6_35, 0);
  // 171: STATIC_SINGLE, DYNAMIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_SINGLE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__6_40;
}
static void entry__6_35(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 169: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._demangled;
  func = myself->type;
  frame->cont = cont__6_36;
}
static void cont__6_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 168: ... "
  // 169:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 170:   function and as a single-assign dynamic!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6_37;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__6_38;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__6_39;
}
static void cont__6_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 168: Error "
  // 169:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 170:   function and as a single-assign dynamic!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__6_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 171: ... :
  // 172:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__6_41, 0);
  // 173: ... :
  // 174:   Error "
  // 175:     The symbol "@(name.demangled)" is used as a single-assign @
  // 176:     dynamic and is assigned to!@
  frame->slots[7] /* temp__5 */ = create_closure(entry__6_42, 0);
  // 177: ... :
  // 178:   Error "
  // 179:     The symbol "@(name.demangled)" is used as a single-assign @
  // 180:     dynamic and as a multi-assign dynamic!@
  frame->slots[8] /* temp__6 */ = create_closure(entry__6_47, 0);
  // 165: case
  // 166:   variable_kind_of(info)
  // 167:   POLYMORPHIC:
  // 168:     Error "
  // 169:       The symbol "@(name.demangled)" is used as a polymorphic @
  // 170:       function and as a single-assign dynamic!@
  // 171:   STATIC_SINGLE, DYNAMIC_SINGLE:
  // 172:     return undefined
  // 173:   STATIC_MULTI:
  // 174:     Error "
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__POLYMORPHIC();
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = frame->slots[5] /* temp__3 */;
  arguments->slots[4] = frame->slots[6] /* temp__4 */;
  arguments->slots[5] = get__STATIC_MULTI();
  arguments->slots[6] = frame->slots[7] /* temp__5 */;
  arguments->slots[7] = get__DYNAMIC_MULTI();
  arguments->slots[8] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_52(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // info: 0
  // name: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__6_53;
}
static void cont__6_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 184: ... :
  // 185:   Error "
  // 186:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 187:     function and as a multi-assign dynamic!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__6_54, 0);
  // 188: STATIC_SINGLE, STATIC_MULTI, DYNAMIC_MULTI
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_SINGLE();
  arguments->slots[1] = get__STATIC_MULTI();
  arguments->slots[2] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__6_59;
}
static void entry__6_54(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: ... name.demangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._demangled;
  func = myself->type;
  frame->cont = cont__6_55;
}
static void cont__6_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 185: ... "
  // 186:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 187:   function and as a multi-assign dynamic!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6_56;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__6_57;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__6_58;
}
static void cont__6_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 185: Error "
  // 186:   The symbol "@(name.demangled)" is used as a polymorphic @
  // 187:   function and as a multi-assign dynamic!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__6_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 188: ... :
  // 189:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__6_60, 0);
  // 190: ... :
  // 191:   Error "
  // 192:     The symbol "@(name.demangled)" is used as a single-assign @
  // 193:     dynamic and as a multi-assign dynamic!@
  frame->slots[7] /* temp__5 */ = create_closure(entry__6_61, 0);
  // 194: :
  // 195:   return info
  frame->slots[8] /* temp__6 */ = create_closure(entry__6_66, 0);
  // 182: case
  // 183:   variable_kind_of(info)
  // 184:   POLYMORPHIC:
  // 185:     Error "
  // 186:       The symbol "@(name.demangled)" is used as a polymorphic @
  // 187:       function and as a multi-assign dynamic!@
  // 188:   STATIC_SINGLE, STATIC_MULTI, DYNAMIC_MULTI:
  // 189:     return undefined
  // 190:   DYNAMIC_SINGLE:
  // 191:     Error "
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__POLYMORPHIC();
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = frame->slots[5] /* temp__3 */;
  arguments->slots[4] = frame->slots[6] /* temp__4 */;
  arguments->slots[5] = get__DYNAMIC_SINGLE();
  arguments->slots[6] = frame->slots[7] /* temp__5 */;
  arguments->slots[7] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_3(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // curr_info: 0
  // info: 1
  // return: 2
  // name: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* curr_info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 132: variable_kind_of(curr_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* curr_info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__6_4;
}
static void cont__6_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 133: ... :
  // 134:   case
  // 135:     variable_kind_of(info)
  // 136:     POLYMORPHIC, STATIC_SINGLE:
  // 137:       return undefined
  // 138:     :
  // 139:       Error "
  // 140:         The symbol "@(name.demangled)" is used as a polymorphic @
  // 141:         function and cannot be used otherwise!@
  frame->slots[5] /* temp__2 */ = create_closure(entry__6_5, 0);
  // 142: ... :
  // 143:   case
  // 144:     variable_kind_of(info)
  // 145:     STATIC_SINGLE:
  // 146:       return undefined
  // 147:     :
  // 148:       return info
  frame->slots[6] /* temp__3 */ = create_closure(entry__6_14, 0);
  // 149: ... :
  // 150:   case
  // 151:     variable_kind_of(info)
  // 152:     POLYMORPHIC:
  // 153:       Error "
  // 154:         The symbol "@(name.demangled)" is used as a polymorphic @
  // 155:         function and id assigned to!@
  // 156:     STATIC_SINGLE, STATIC_MULTI:
  // 157:       return undefined
  // 158:     DYNAMIC_SINGLE:
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__6_18, 0);
  // 164: ... :
  // 165:   case
  // 166:     variable_kind_of(info)
  // 167:     POLYMORPHIC:
  // 168:       Error "
  // 169:         The symbol "@(name.demangled)" is used as a polymorphic @
  // 170:         function and as a single-assign dynamic!@
  // 171:     STATIC_SINGLE, DYNAMIC_SINGLE:
  // 172:       return undefined
  // 173:     STATIC_MULTI:
  // ...
  frame->slots[8] /* temp__5 */ = create_closure(entry__6_33, 0);
  // 181: ... :
  // 182:   case
  // 183:     variable_kind_of(info)
  // 184:     POLYMORPHIC:
  // 185:       Error "
  // 186:         The symbol "@(name.demangled)" is used as a polymorphic @
  // 187:         function and as a multi-assign dynamic!@
  // 188:     STATIC_SINGLE, STATIC_MULTI, DYNAMIC_MULTI:
  // 189:       return undefined
  // 190:     DYNAMIC_SINGLE:
  // ...
  frame->slots[9] /* temp__6 */ = create_closure(entry__6_52, 0);
  // 131: case
  // 132:   variable_kind_of(curr_info)
  // 133:   POLYMORPHIC:
  // 134:     case
  // 135:       variable_kind_of(info)
  // 136:       POLYMORPHIC, STATIC_SINGLE:
  // 137:         return undefined
  // 138:       :
  // 139:         Error "
  // 140:           The symbol "@(name.demangled)" is used as a polymorphic @
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__POLYMORPHIC();
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  arguments->slots[3] = get__STATIC_SINGLE();
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  arguments->slots[5] = get__STATIC_MULTI();
  arguments->slots[6] = frame->slots[7] /* temp__4 */;
  arguments->slots[7] = get__DYNAMIC_SINGLE();
  arguments->slots[8] = frame->slots[8] /* temp__5 */;
  arguments->slots[9] = get__DYNAMIC_MULTI();
  arguments->slots[10] = frame->slots[9] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_67(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 197: return info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__6_68(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__7_1(void) {
  allocate_initialized_frame_gc(3, 35);
  // slot allocations:
  // filenames: 0
  // is_main: 1
  // return__9: 2
  // mangle_filename: 3
  // fragments: 4
  // trees: 5
  // all_defined_names: 6
  // all_used_names: 7
  // all_actions: 8
  // top_level_names: 9
  // all_definitions: 10
  // all_statements: 11
  // max_temp_idx: 12
  // need: 13
  // generated_declarations: 14
  // generated_top_level_variable_names: 15
  // generated_top_level_variable_declarations: 16
  // generated_global_variable_declarations: 17
  // generated_continuation_table: 18
  // generated_delayed_continuation_table: 19
  // generated_functions: 20
  // generated_phase_1: 21
  // generated_phase_2: 22
  // generated_phase_3: 23
  // generated_phase_4: 24
  // generated_phase_5: 25
  // generated_code: 26
  // generated_collections: 27
  // delayed_statements: 28
  // used_literals: 29
  // def_count: 30
  // depth: 31
  frame->slots[2] /* return__9 */ = create_continuation();
  // _define $mangle_filename 
  // : ($name)
  // has_prefix temp__1 name "./"
  // 
  // temp__2:
  // contains temp__1 module_name "__"
  // 
  // temp__2:
  // std::negate temp__2 1
  // before temp__1 module_name "__" temp__2
  // std::negate temp__4 1
  // range temp__3 name 2 temp__4
  // append temp__1 temp__3 !name
  // 
  // temp__3:
  // std::negate temp__1 1
  // range !name name 3 temp__1
  // 
  // if temp__1 temp__2 temp__3
  // 
  // if temp__1 temp__2
  // std::key_value_pair temp__2 '/' "__"
  // replace_all temp__1 name temp__2
  // -> temp__1
  frame->slots[3] /* mangle_filename */ = func__7_2;
  // _define $need 
  // :
  // (
  // mangled_name
  // info
  // -> return
  // )
  // contains temp__1 mangled_name "__"
  // 
  // temp__2:
  // before $namespace mangled_name "__"
  // behind $name mangled_name "__"
  // exported_names $namespaces name
  // is_defined temp__2 namespaces
  // 
  // temp__3:
  // namespaces temp__2 namespace
  // is_defined temp__1 temp__2
  // -> temp__1
  // 
  // std::and temp__1 temp__2 temp__3
  // if temp__1 return
  // 
  // temp__3:
  // global_names $definition mangled_name
  // is_defined temp__1 definition
  // 
  // temp__2:
  // check_usage mangled_name definition info
  // return
  // 
  // if temp__1 temp__2
  // 
  // if temp__1 temp__2 temp__3
  // needed_names temp__1 mangled_name
  // update_info $updated_info mangled_name temp__1 info
  // is_defined temp__1 updated_info
  // 
  // temp__2:
  // temp__1 updated_info
  // needed_names !needed_names mangled_name temp__1
  // 
  // if temp__1 temp__2
  frame->slots[13] /* need */ = func__7_22;
  define__sim2c__required_modules(undefined);
  define__sim2c__used_namespaces(undefined);
  define__sim2c__defined_namespaces(undefined);
  define__sim2c__namespace_mappings(undefined);
  define__sim2c__included_files(undefined);
  define__sim2c__linked_libraries(undefined);
  define__sim2c__dependent_data(undefined);
  define__sim2c__global_names(undefined);
  define__sim2c__exported_names(undefined);
  define__sim2c__needed_names(undefined);
  define__sim2c__assigned_names(undefined);
  define__sim2c__use_inline_c(undefined);
  define__sim2c__defined_structs(undefined);
  define__sim2c__defined_nodes(undefined);
  define__sim2c__defined_functions(undefined);
  define__sim2c__enumeration_count(undefined);
  frame->slots[4] /* fragments */ = create_cell();
  frame->slots[5] /* trees */ = create_cell();
  frame->slots[6] /* all_defined_names */ = create_cell();
  frame->slots[7] /* all_used_names */ = create_cell();
  frame->slots[8] /* all_actions */ = create_cell();
  frame->slots[9] /* top_level_names */ = create_cell();
  frame->slots[10] /* all_definitions */ = create_cell();
  frame->slots[11] /* all_statements */ = create_cell();
  frame->slots[12] /* max_temp_idx */ = create_cell();
  frame->slots[14] /* generated_declarations */ = create_cell();
  frame->slots[15] /* generated_top_level_variable_names */ = create_cell();
  frame->slots[16] /* generated_top_level_variable_declarations */ = create_cell();
  frame->slots[17] /* generated_global_variable_declarations */ = create_cell();
  frame->slots[18] /* generated_continuation_table */ = create_cell();
  frame->slots[19] /* generated_delayed_continuation_table */ = create_cell();
  frame->slots[20] /* generated_functions */ = create_cell();
  frame->slots[21] /* generated_phase_1 */ = create_cell();
  frame->slots[22] /* generated_phase_2 */ = create_cell();
  frame->slots[23] /* generated_phase_3 */ = create_cell();
  frame->slots[24] /* generated_phase_4 */ = create_cell();
  frame->slots[25] /* generated_phase_5 */ = create_cell();
  frame->slots[26] /* generated_code */ = create_cell();
  frame->slots[27] /* generated_collections */ = create_cell();
  frame->slots[28] /* delayed_statements */ = create_cell();
  frame->slots[29] /* used_literals */ = create_cell();
  define__sim2c__write_to_declarations(create_future());
  define__sim2c__write_to_top_level_variable_names(create_future());
  define__sim2c__write_to_top_level_variable_declarations(create_future());
  define__sim2c__write_to_global_variable_declarations(create_future());
  define__sim2c__write_to_continuation_table(create_future());
  define__sim2c__write_to_delayed_continuation_table(create_future());
  define__sim2c__write_to_functions(create_future());
  define__sim2c__write_to_phase_1(create_future());
  define__sim2c__write_to_phase_2(create_future());
  define__sim2c__write_to_phase_3(create_future());
  define__sim2c__write_to_phase_4(create_future());
  define__sim2c__write_to_phase_5(create_future());
  define__sim2c__use_literal(create_future());
  define__sim2c__write_to_generated_collections(create_future());
  define__sim2c__write_to_delayed_statements(create_future());
  define__sim2c__use_identifier(create_future());
  define__sim2c__current_continuation_info(undefined);
  frame->slots[30] /* def_count */ = create_future();
  frame->slots[31] /* depth */ = create_future();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* is_main */ = create_cell_with_contents(arguments->slots[1]);
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* is_main */ = create_cell_with_contents(get__false());
  }
  // 219: %%sim2c::required_modules empty_insert_order_table
  set__sim2c__required_modules(get__empty_insert_order_table());
  // 220: %%sim2c::used_namespaces empty_insert_order_set
  set__sim2c__used_namespaces(get__empty_insert_order_set());
  // 221: %%sim2c::defined_namespaces empty_insert_order_set
  set__sim2c__defined_namespaces(get__empty_insert_order_set());
  // 222: %%sim2c::namespace_mappings empty_insert_order_table
  set__sim2c__namespace_mappings(get__empty_insert_order_table());
  // 223: %%sim2c::included_files empty_insert_order_set
  set__sim2c__included_files(get__empty_insert_order_set());
  // 224: %%sim2c::linked_libraries empty_insert_order_set
  set__sim2c__linked_libraries(get__empty_insert_order_set());
  // 225: %%sim2c::dependent_data empty_insert_order_set
  set__sim2c__dependent_data(get__empty_insert_order_set());
  // 226: %%sim2c::global_names empty_key_order_table
  set__sim2c__global_names(get__empty_key_order_table());
  // 227: %%sim2c::exported_names empty_key_order_table
  set__sim2c__exported_names(get__empty_key_order_table());
  // 228: %%sim2c::needed_names empty_key_order_table
  set__sim2c__needed_names(get__empty_key_order_table());
  // 229: %%sim2c::assigned_names empty_set
  set__sim2c__assigned_names(get__empty_set());
  // 230: %%sim2c::use_inline_c false # set, if an inline-C expression is encountered
  set__sim2c__use_inline_c(get__false());
  // 231: %%sim2c::defined_structs set("NODE")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_48;
  result_count = 1;
  myself = get__set();
  func = myself->type;
  frame->cont = cont__7_49;
}
static void entry__7_2(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* name */ = create_cell_with_contents(arguments->slots[0]);
  // 211: ... name .has_prefix. "./"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__7_3;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__7_4;
}
static void cont__7_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 211: ... :
  // 212:   if
  // 213:     module_name .contains. "__":
  // 214:       !name before(module_name "__" -1) .append. range(name 2 -1)
  // 215:     :
  // 216:       !name range(name 3 -1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__7_5, 0);
  // 211: if name .has_prefix. "./":
  // 212:   if
  // 213:     module_name .contains. "__":
  // 214:       !name before(module_name "__" -1) .append. range(name 2 -1)
  // 215:     :
  // 216:       !name range(name 3 -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_18;
}
static void entry__7_8(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_9;
}
static void cont__7_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 214: ... before(module_name "__" -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__7_10;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__7_11;
}
static void cont__7_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 214: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_12;
}
static void cont__7_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 214: ... range(name 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_13;
}
static void cont__7_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 214: !name before(module_name "__" -1) .append. range(name 2 -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_14;
}
static void cont__7_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* name */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_15(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 216: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_16;
}
static void cont__7_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 216: !name range(name 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_17;
}
static void cont__7_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* name */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 213: module_name .contains. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__7_6;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__7_7;
}
static void cont__7_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 213: ... :
  // 214:   !name before(module_name "__" -1) .append. range(name 2 -1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__7_8, 0);
  // 215: :
  // 216:   !name range(name 3 -1)
  frame->slots[3] /* temp__3 */ = create_closure(entry__7_15, 0);
  // 212: if
  // 213:   module_name .contains. "__":
  // 214:     !name before(module_name "__" -1) .append. range(name 2 -1)
  // 215:   :
  // 216:     !name range(name 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 217: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__7_19;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__7_20;
}
static void cont__7_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 217: ... replace_all(name '/' = "__")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__7_21;
}
static void cont__7_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 217: -> replace_all(name '/' = "__")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_22(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // mangled_name: 0
  // info: 1
  // return: 2
  // updated_info: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* updated_info */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 400: mangled_name .contains. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = string__7_23;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__7_24;
}
static void cont__7_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 400: ... :
  // 401:   $namespace mangled_name .before. "__"
  // 402:   $name mangled_name .behind. "__"
  // 403:   $namespaces exported_names(name)
  // 404:   if namespaces.is_defined && namespaces(namespace).is_defined return
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_25, 0);
  // 405: :
  // 406:   $definition global_names(mangled_name)
  // 407:   if definition.is_defined:
  // 408:     check_usage mangled_name definition info
  // 409:     return
  frame->slots[6] /* temp__3 */ = create_closure(entry__7_36, 0);
  // 399: if
  // 400:   mangled_name .contains. "__":
  // 401:     $namespace mangled_name .before. "__"
  // 402:     $name mangled_name .behind. "__"
  // 403:     $namespaces exported_names(name)
  // 404:     if namespaces.is_defined && namespaces(namespace).is_defined return
  // 405:   :
  // 406:     $definition global_names(mangled_name)
  // 407:     if definition.is_defined:
  // 408:       check_usage mangled_name definition info
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_41;
}
static void entry__7_39(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // mangled_name: 0
  // definition: 1
  // info: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* mangled_name */
  frame->slots[1] = myself->closure.frame->slots[3]; /* definition */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 408: check_usage mangled_name definition info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[1] /* definition */;
  arguments->slots[2] = frame->slots[2] /* info */;
  result_count = 0;
  myself = get__check_usage();
  func = myself->type;
  frame->cont = cont__7_40;
}
static void cont__7_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 409: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_25(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // mangled_name: 0
  // return: 1
  // namespace: 2
  // name: 3
  // namespaces: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* mangled_name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  frame->slots[2] /* namespace */ = create_future();
  frame->slots[3] /* name */ = create_future();
  frame->slots[4] /* namespaces */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 401: $namespace mangled_name .before. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = string__7_26;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__7_27;
}
static void cont__7_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 402: $name mangled_name .behind. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = string__7_28;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__7_29;
}
static void cont__7_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* name */, arguments->slots[0]);
  // 403: $namespaces exported_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* name */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__7_30;
}
static void cont__7_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* namespaces */, arguments->slots[0]);
  // 404: ... namespaces.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* namespaces */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_31;
}
static void cont__7_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 404: ... namespaces(namespace).is_defined
  frame->slots[7] /* temp__3 */ = create_closure(entry__7_32, 0);
  // 404: ... namespaces.is_defined && namespaces(namespace).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_35;
}
static void entry__7_32(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // namespaces: 0
  // namespace: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* namespaces */
  frame->slots[1] = myself->closure.frame->slots[2]; /* namespace */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 404: ... namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = frame->slots[0] /* namespaces */;
  func = myself->type;
  frame->cont = cont__7_33;
}
static void cont__7_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 404: ... namespaces(namespace).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_34;
}
static void cont__7_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 404: ... namespaces(namespace).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 404: if namespaces.is_defined && namespaces(namespace).is_defined return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_36(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // mangled_name: 0
  // info: 1
  // return: 2
  // definition: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* mangled_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* definition */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 406: $definition global_names(mangled_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__7_37;
}
static void cont__7_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* definition */, arguments->slots[0]);
  // 407: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_38;
}
static void cont__7_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 407: ... :
  // 408:   check_usage mangled_name definition info
  // 409:   return
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_39, 0);
  // 407: if definition.is_defined:
  // 408:   check_usage mangled_name definition info
  // 409:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 410: ... needed_names(mangled_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  result_count = 1;
  myself = get__needed_names();
  func = myself->type;
  frame->cont = cont__7_42;
}
static void cont__7_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 410: $updated_info update_info(mangled_name needed_names(mangled_name) info)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__update_info();
  func = myself->type;
  frame->cont = cont__7_43;
}
static void cont__7_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* updated_info */, arguments->slots[0]);
  // 411: ... updated_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* updated_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_44;
}
static void cont__7_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 411: ... : !needed_names(mangled_name) updated_info
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_45, 0);
  // 411: if updated_info.is_defined: !needed_names(mangled_name) updated_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_47;
}
static void entry__7_45(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // mangled_name: 0
  // updated_info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* mangled_name */
  frame->slots[1] = myself->closure.frame->slots[3]; /* updated_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 411: ... !needed_names(mangled_name) updated_info
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* updated_info */;
  // 411: ... !needed_names(mangled_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__needed_names();
  func = myself->type;
  frame->cont = cont__7_46;
}
static void cont__7_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__needed_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_47(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__7_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__sim2c__defined_structs(arguments->slots[0]);
  // 232: ... c_code(.source_of "")
  {
    NODE *temp = clone_object_and_attributes(get__c_code());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_of, empty_string);
    frame->slots[33] /* temp__2 */ = temp;

  }
  // 232: ... "SIMPLE_NODE" = c_code(.source_of "")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_50;
  arguments->slots[1] = frame->slots[33] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__7_51;
}
static void cont__7_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 232: %%sim2c::defined_nodes table("SIMPLE_NODE" = c_code(.source_of ""))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__7_52;
}
static void cont__7_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__sim2c__defined_nodes(arguments->slots[0]);
  // 233: %%sim2c::defined_functions empty_set
  set__sim2c__defined_functions(get__empty_set());
  // 234: %%sim2c::enumeration_count 0
  set__sim2c__enumeration_count(number__0);
  // 235: $$fragments empty_list
  ((CELL *)frame->slots[4])->contents /* fragments */ = get__empty_list();
  // 236: $$trees empty_list
  ((CELL *)frame->slots[5])->contents /* trees */ = get__empty_list();
  // 237: $$all_defined_names empty_list
  ((CELL *)frame->slots[6])->contents /* all_defined_names */ = get__empty_list();
  // 238: $$all_used_names empty_list
  ((CELL *)frame->slots[7])->contents /* all_used_names */ = get__empty_list();
  // 239: ... : (no filename)
  // 240:   $$buf load(filename)
  // 241:   try
  // 242:     :
  // 243:       from_utf8 &buf
  // 244:     :
  // 245:       Error "Source file is not in a valid utf-8-encoding!"
  // 246:   if do_show_debug_infos:
  // 247:     ewrite "
  // 248:       load "@(filename)@quot;
  // ...
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_53, 2);
  // 239: for_each filenames: (no filename)
  // 240:   $$buf load(filename)
  // 241:   try
  // 242:     :
  // 243:       from_utf8 &buf
  // 244:     :
  // 245:       Error "Source file is not in a valid utf-8-encoding!"
  // 246:   if do_show_debug_infos:
  // 247:     ewrite "
  // 248:       load "@(filename)@quot;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filenames */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_119;
}
static void entry__7_53(void) {
  allocate_initialized_frame_gc(6, 13);
  // slot allocations:
  // no: 0
  // filename: 1
  // return__1: 2
  // is_main: 3
  // trees: 4
  // fragments: 5
  // buf: 6
  // submodule_fragments: 7
  // first_idx: 8
  frame->slots[2] /* return__1 */ = create_continuation();
  frame->slots[3] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[4] = myself->closure.frame->slots[5]; /* trees */
  frame->slots[5] = myself->closure.frame->slots[4]; /* fragments */
  frame->slots[6] /* buf */ = create_cell();
  define__sim2c__submodule_no(create_future());
  frame->slots[7] /* submodule_fragments */ = create_cell();
  frame->slots[8] /* first_idx */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 240: $$buf load(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__7_54;
}
static void cont__7_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* buf */ = arguments->slots[0];
  // 242: :
  // 243:   from_utf8 &buf
  frame->slots[9] /* temp__1 */ = create_closure(entry__7_55, 0);
  // 241: try
  // 242:   :
  // 243:     from_utf8 &buf
  // 244:   :
  // 245:     Error "Source file is not in a valid utf-8-encoding!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = func__7_57;
  result_count = 0;
  myself = get__try();
  func = myself->type;
  frame->cont = cont__7_59;
}
static void entry__7_55(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 243: from_utf8 &buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__7_56;
}
static void cont__7_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_57(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 245: Error "Source file is not in a valid utf-8-encoding!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_58;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 246: ... :
  // 247:   ewrite "
  // 248:     load "@(filename)@quot;
  frame->slots[9] /* temp__1 */ = create_closure(entry__7_60, 0);
  // 246: if do_show_debug_infos:
  // 247:   ewrite "
  // 248:     load "@(filename)@quot;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_64;
}
static void entry__7_60(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 247: ... "
  // 248:   load "@(filename)@quot;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_61;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__7_62;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_63;
}
static void cont__7_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 247: ewrite "
  // 248:   load "@(filename)@quot;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_64(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 249: ... : write_timing_info "loading" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__7_65, 0);
  // 249: if do_time_passes: write_timing_info "loading" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_67;
}
static void entry__7_65(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 249: ... write_timing_info "loading" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_66;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 250: ... length_of(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* buf */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__7_68;
}
static void cont__7_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 250: ... length_of(buf) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_69;
}
static void cont__7_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 250: if length_of(buf) == 0: Error "Empty source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = func__7_70;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_72;
}
static void entry__7_70(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 250: ... Error "Empty source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_71;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 251: ... buf(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[6])->contents /* buf */;
  func = myself->type;
  frame->cont = cont__7_73;
}
static void cont__7_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 251: ... buf(1) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_74;
}
static void cont__7_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 251: ... buf(1) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_75;
}
static void cont__7_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 251: if buf(1) <= ' ': Error "Whitespace at start of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = func__7_76;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_78;
}
static void entry__7_76(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 251: ... Error "Whitespace at start of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_77;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 252: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_79;
}
static void cont__7_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 252: ... buf(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[6])->contents /* buf */;
  func = myself->type;
  frame->cont = cont__7_80;
}
static void cont__7_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 252: ... buf(-1) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_81;
}
static void cont__7_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 252: ... buf(-1) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_82;
}
static void cont__7_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 252: if buf(-1) != newline: Error "Missing newline at end of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = func__7_83;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_85;
}
static void entry__7_83(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 252: ... Error "Missing newline at end of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_84;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 253: ... buf .has_prefix. "#!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* buf */;
  arguments->slots[1] = string__7_86;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__7_87;
}
static void cont__7_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 253: ... : !is_main true
  frame->slots[10] /* temp__2 */ = create_closure(entry__7_88, 0);
  // 253: if buf .has_prefix. "#!": !is_main true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_89;
}
static void entry__7_88(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 253: ... !is_main true
  ((CELL *)frame->slots[0])->contents /* is_main */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 254: %sim2c::submodule_no no-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* no */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__7_90;
}
static void cont__7_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__submodule_no(), arguments->slots[0]);
  // 255: $$submodule_fragments cut_into_fragments(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* buf */;
  result_count = 1;
  myself = get__cut_into_fragments();
  func = myself->type;
  frame->cont = cont__7_91;
}
static void cont__7_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* submodule_fragments */ = arguments->slots[0];
  // 256: ... : write_timing_info "fragmenting" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__7_92, 0);
  // 256: if do_time_passes: write_timing_info "fragmenting" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_94;
}
static void entry__7_92(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 256: ... write_timing_info "fragmenting" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_93;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_94(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 257: update_each &submodule_fragments: (&fragment) tokenize &fragment
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* submodule_fragments */;
  arguments->slots[1] = func__7_95;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__7_97;
}
static void entry__7_95(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fragment: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* fragment */ = create_cell_with_contents(arguments->slots[0]);
  // 257: ... tokenize &fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  result_count = 1;
  myself = get__tokenize();
  func = myself->type;
  frame->cont = cont__7_96;
}
static void cont__7_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* fragment */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* submodule_fragments */ = arguments->slots[0];
  // 258: ... : write_timing_info "tokenizing" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__7_98, 0);
  // 258: if do_time_passes: write_timing_info "tokenizing" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_100;
}
static void entry__7_98(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 258: ... write_timing_info "tokenizing" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_99;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_100(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 259: $$first_idx 1
  ((CELL *)frame->slots[8])->contents /* first_idx */ = number__1;
  // 260: ... : (-> done)
  // 261:   for_each submodule_fragments: (idx fragment)
  // 262:     case
  // 263:       source_of(fragment)(1)
  // 264:       '#':
  // 265:         !first_idx idx+1
  // 266:         push &trees parse_statement(fragment)
  // 267:       '<':
  // 268:         !first_idx idx+1
  // 269:         push &trees parse_meta_instruction(fragment)
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__7_101, 0);
  // 260: do: (-> done)
  // 261:   for_each submodule_fragments: (idx fragment)
  // 262:     case
  // 263:       source_of(fragment)(1)
  // 264:       '#':
  // 265:         !first_idx idx+1
  // 266:         push &trees parse_statement(fragment)
  // 267:       '<':
  // 268:         !first_idx idx+1
  // 269:         push &trees parse_meta_instruction(fragment)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__7_115;
}
static void entry__7_101(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // done: 0
  // submodule_fragments: 1
  // first_idx: 2
  // trees: 3
  frame->slots[0] /* done */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[7]; /* submodule_fragments */
  frame->slots[2] = myself->closure.frame->slots[8]; /* first_idx */
  frame->slots[3] = myself->closure.frame->slots[4]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 261: ... : (idx fragment)
  // 262:   case
  // 263:     source_of(fragment)(1)
  // 264:     '#':
  // 265:       !first_idx idx+1
  // 266:       push &trees parse_statement(fragment)
  // 267:     '<':
  // 268:       !first_idx idx+1
  // 269:       push &trees parse_meta_instruction(fragment)
  // 270:     :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__7_102, 2);
  // 261: for_each submodule_fragments: (idx fragment)
  // 262:   case
  // 263:     source_of(fragment)(1)
  // 264:     '#':
  // 265:       !first_idx idx+1
  // 266:       push &trees parse_statement(fragment)
  // 267:     '<':
  // 268:       !first_idx idx+1
  // 269:       push &trees parse_meta_instruction(fragment)
  // 270:     :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* submodule_fragments */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_114;
}
static void entry__7_105(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // first_idx: 0
  // idx: 1
  // trees: 2
  // fragment: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* first_idx */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[3]; /* trees */
  frame->slots[3] = myself->closure.frame->slots[1]; /* fragment */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 265: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_106;
}
static void cont__7_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 266: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__7_107;
}
static void cont__7_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 266: push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* trees */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_108;
}
static void cont__7_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* trees */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_109(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // first_idx: 0
  // idx: 1
  // trees: 2
  // fragment: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* first_idx */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[3]; /* trees */
  frame->slots[3] = myself->closure.frame->slots[1]; /* fragment */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 268: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_110;
}
static void cont__7_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 269: ... parse_meta_instruction(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* fragment */;
  result_count = 1;
  myself = get__parse_meta_instruction();
  func = myself->type;
  frame->cont = cont__7_111;
}
static void cont__7_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 269: push &trees parse_meta_instruction(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* trees */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_112;
}
static void cont__7_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* trees */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_113(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // done: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* done */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 271: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_102(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // idx: 0
  // fragment: 1
  // first_idx: 2
  // trees: 3
  // done: 4
  frame->slots[2] = myself->closure.frame->slots[2]; /* first_idx */
  frame->slots[3] = myself->closure.frame->slots[3]; /* trees */
  frame->slots[4] = myself->closure.frame->slots[0]; /* done */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 263: source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fragment */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__7_103;
}
static void cont__7_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 263: source_of(fragment)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[6] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__7_104;
}
static void cont__7_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 264: ... :
  // 265:   !first_idx idx+1
  // 266:   push &trees parse_statement(fragment)
  frame->slots[7] /* temp__3 */ = create_closure(entry__7_105, 0);
  // 267: ... :
  // 268:   !first_idx idx+1
  // 269:   push &trees parse_meta_instruction(fragment)
  frame->slots[8] /* temp__4 */ = create_closure(entry__7_109, 0);
  // 270: :
  // 271:   done
  frame->slots[9] /* temp__5 */ = create_closure(entry__7_113, 0);
  // 262: case
  // 263:   source_of(fragment)(1)
  // 264:   '#':
  // 265:     !first_idx idx+1
  // 266:     push &trees parse_statement(fragment)
  // 267:   '<':
  // 268:     !first_idx idx+1
  // 269:     push &trees parse_meta_instruction(fragment)
  // 270:   :
  // 271:     done
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = character__35;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  arguments->slots[3] = character__60;
  arguments->slots[4] = frame->slots[8] /* temp__4 */;
  arguments->slots[5] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_114(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__7_115(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 272: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_116;
}
static void cont__7_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 272: ... range(submodule_fragments first_idx -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* submodule_fragments */;
  arguments->slots[1] = ((CELL *)frame->slots[8])->contents /* first_idx */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_117;
}
static void cont__7_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 272: append &fragments range(submodule_fragments first_idx -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* fragments */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_118;
}
static void cont__7_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* fragments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[2] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__7_119(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 273: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_120, 1);
  // 273: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* fragments */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_123;
}
static void entry__7_120(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fragment: 0
  // trees: 1
  frame->slots[1] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 273: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__7_121;
}
static void cont__7_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 273: ... push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* trees */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_122;
}
static void cont__7_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* trees */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_123(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 274: ... : write_timing_info "parsing" filenames(1)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_124, 0);
  // 274: if do_time_passes: write_timing_info "parsing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_127;
}
static void entry__7_124(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 274: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__7_125;
}
static void cont__7_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 274: ... write_timing_info "parsing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_126;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_127(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 275: ... :
  // 276:   #if do_show_compiler_debug_infos:
  // 277:     $$header_printed false
  // 278:     for_each global_names: (name type)
  // 279:       unless header_printed:
  // 280:         print_line "# Global variables"
  // 281:         !header_printed true
  // 282:       print_line "  " name
  // 283:   
  // 284:   print_trees trees
  // ...
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_128, 0);
  // 275: if do_pretty_print:
  // 276:   #if do_show_compiler_debug_infos:
  // 277:     $$header_printed false
  // 278:     for_each global_names: (name type)
  // 279:       unless header_printed:
  // 280:         print_line "# Global variables"
  // 281:         !header_printed true
  // 282:       print_line "  " name
  // 283:   
  // 284:   print_trees trees
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_130;
}
static void entry__7_128(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: print_trees trees
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  result_count = 0;
  myself = get__print_trees();
  func = myself->type;
  frame->cont = cont__7_129;
}
static void cont__7_129(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 285: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_130(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 286: ... : # the main program should terminate cleanly
  // 287:   push &trees procedure_call(.functor_of std_identifier("terminate"))
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_131, 0);
  // 286: if is_main: # the main program should terminate cleanly
  // 287:   push &trees procedure_call(.functor_of std_identifier("terminate"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_135;
}
static void entry__7_131(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 287: ... std_identifier("terminate")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_132;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__7_133;
}
static void cont__7_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 287: ... procedure_call(.functor_of std_identifier("terminate"))
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 287: push &trees procedure_call(.functor_of std_identifier("terminate"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_134;
}
static void cont__7_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* trees */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_135(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 288: update_each &trees: (&tree)
  // 289:   %%sim2c::index 1
  // 290:   expand_statement &tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = func__7_136;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__7_138;
}
static void entry__7_136(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // tree: 0
  // return__2: 1
  frame->slots[1] /* return__2 */ = create_continuation_with_exit(exit__7_136);
  define__sim2c__index(undefined);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* tree */ = create_cell_with_contents(arguments->slots[0]);
  // 289: %%sim2c::index 1
  set__sim2c__index(number__1);
  // 290: expand_statement &tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  result_count = 1;
  myself = get__expand_statement();
  func = myself->type;
  frame->cont = cont__7_137;
}
static void cont__7_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[1] /* return__2 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__7_136(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  func = continuation_type_function;
}
static void cont__7_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* trees */ = arguments->slots[0];
  // 291: ... : write_timing_info "expanding" filenames(1)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_139, 0);
  // 291: if do_time_passes: write_timing_info "expanding" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_142;
}
static void entry__7_139(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 291: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__7_140;
}
static void cont__7_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 291: ... write_timing_info "expanding" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_141;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_142(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 292: ... : (&tree)
  // 293:   %%sim2c::defined_names empty_list
  // 294:   %%sim2c::used_names empty_insert_order_table
  // 295:   %%sim2c::index 1
  // 296:   annotate_statement &tree
  // 297:   push &all_defined_names sim2c::defined_names
  // 298:   push &all_used_names sim2c::used_names
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_143, 1);
  // 292: update_each &trees: (&tree)
  // 293:   %%sim2c::defined_names empty_list
  // 294:   %%sim2c::used_names empty_insert_order_table
  // 295:   %%sim2c::index 1
  // 296:   annotate_statement &tree
  // 297:   push &all_defined_names sim2c::defined_names
  // 298:   push &all_used_names sim2c::used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__7_147;
}
static void entry__7_143(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // tree: 0
  // return__3: 1
  // all_defined_names: 2
  // all_used_names: 3
  frame->slots[1] /* return__3 */ = create_continuation_with_exit(exit__7_143);
  frame->slots[2] = myself->closure.frame->slots[6]; /* all_defined_names */
  frame->slots[3] = myself->closure.frame->slots[7]; /* all_used_names */
  define__sim2c__defined_names(undefined);
  define__sim2c__used_names(undefined);
  define__sim2c__index(undefined);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* tree */ = create_cell_with_contents(arguments->slots[0]);
  // 293: %%sim2c::defined_names empty_list
  set__sim2c__defined_names(get__empty_list());
  // 294: %%sim2c::used_names empty_insert_order_table
  set__sim2c__used_names(get__empty_insert_order_table());
  // 295: %%sim2c::index 1
  set__sim2c__index(number__1);
  // 296: annotate_statement &tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  result_count = 1;
  myself = get__annotate_statement();
  func = myself->type;
  frame->cont = cont__7_144;
}
static void cont__7_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  // 297: push &all_defined_names sim2c::defined_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* all_defined_names */;
  arguments->slots[1] = get__sim2c__defined_names();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_145;
}
static void cont__7_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* all_defined_names */ = arguments->slots[0];
  // 298: push &all_used_names sim2c::used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_used_names */;
  arguments->slots[1] = get__sim2c__used_names();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_146;
}
static void cont__7_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* all_used_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[1] /* return__3 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__7_143(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  func = continuation_type_function;
}
static void cont__7_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* trees */ = arguments->slots[0];
  // 299: ... : write_timing_info "annotating" filenames(1)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_148, 0);
  // 299: if do_time_passes: write_timing_info "annotating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_151;
}
static void entry__7_148(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__7_149;
}
static void cont__7_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 299: ... write_timing_info "annotating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_150;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_151(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 300: $$all_actions empty_list
  ((CELL *)frame->slots[8])->contents /* all_actions */ = get__empty_list();
  // 302: $$top_level_names
  // 303:   if(do_print_warnings (-> empty_insert_order_table) -> empty_table)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = func__7_152;
  arguments->slots[2] = func__7_153;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_154;
}
static void entry__7_152(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 303: ... -> empty_insert_order_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_insert_order_table();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_153(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 303: ... -> empty_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_table();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* top_level_names */ = arguments->slots[0];
  // 305: ... required_modules.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__7_155;
}
static void cont__7_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__2 */ = arguments->slots[0];
  // 305: ... is_main
  frame->slots[34] /* temp__3 */ = create_closure(entry__7_156, 0);
  // 305: ... required_modules.is_empty && is_main
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__2 */;
  arguments->slots[1] = frame->slots[34] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_157;
}
static void entry__7_156(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 305: ... is_main
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 305: if required_modules.is_empty && is_main:
  // 306:   !required_modules("basic/stdlib") types::grammar_node
  // 307:   !required_modules("system/stdlib") types::grammar_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  arguments->slots[1] = func__7_158;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_163;
}
static void entry__7_158(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: !required_modules("basic/stdlib") types::grammar_node
  frame->slots[0] /* temp__1 */ = get__types__grammar_node();
  // 306: !required_modules("basic/stdlib")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_159;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__7_160;
}
static void cont__7_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__required_modules(arguments->slots[0]);
  // 307: !required_modules("system/stdlib") types::grammar_node
  frame->slots[0] /* temp__1 */ = get__types__grammar_node();
  // 307: !required_modules("system/stdlib")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_161;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__7_162;
}
static void cont__7_162(void) {
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
static void cont__7_163(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 308: !required_modules("nothing") undefined
  frame->slots[32] /* temp__1 */ = get__undefined();
  // 308: !required_modules("nothing")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_164;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__7_165;
}
static void cont__7_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__required_modules(arguments->slots[0]);
  // 309: ... used_namespaces.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__7_166;
}
static void cont__7_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 309: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  arguments->slots[1] = func__7_167;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_170;
}
static void entry__7_167(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 309: ... !used_namespaces("std") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 309: ... !used_namespaces("std")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_168;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__7_169;
}
static void cont__7_169(void) {
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
static void cont__7_170(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 310: !used_namespaces("nothing") false
  frame->slots[32] /* temp__1 */ = get__false();
  // 310: !used_namespaces("nothing")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_171;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__7_172;
}
static void cont__7_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_namespaces(arguments->slots[0]);
  // 311: ... : (defined_names)
  // 312:   for_each defined_names: (info)
  // 313:     $ident identifier_of(info)
  // 314:     unless
  // 315:       info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 316:         $namespace namespace_of(ident)
  // 317:         $name name_of(ident)
  // 318:         if
  // 319:           namespace.is_defined:
  // 320:             $$namespaces exported_names(name)
  // ...
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_173, 1);
  // 311: for_each all_defined_names: (defined_names)
  // 312:   for_each defined_names: (info)
  // 313:     $ident identifier_of(info)
  // 314:     unless
  // 315:       info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 316:         $namespace namespace_of(ident)
  // 317:         $name name_of(ident)
  // 318:         if
  // 319:           namespace.is_defined:
  // 320:             $$namespaces exported_names(name)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* all_defined_names */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_253;
}
static void entry__7_185(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // name: 0
  // namespace: 1
  // info: 2
  // top_level_names: 3
  // namespaces: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  frame->slots[1] = myself->closure.frame->slots[3]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  frame->slots[3] = myself->closure.frame->slots[2]; /* top_level_names */
  frame->slots[4] /* namespaces */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 320: $$namespaces exported_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__7_186;
}
static void cont__7_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* namespaces */ = arguments->slots[0];
  // 321: ... namespaces.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* namespaces */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_187;
}
static void cont__7_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 321: ... : !namespaces table()
  frame->slots[6] /* temp__2 */ = create_closure(entry__7_188, 0);
  // 321: unless namespaces.is_defined: !namespaces table()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__7_190;
}
static void entry__7_188(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // namespaces: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* namespaces */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 321: ... !namespaces table()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__7_189;
}
static void cont__7_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* namespaces */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_190(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 322: ... namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* namespaces */;
  func = myself->type;
  frame->cont = cont__7_191;
}
static void cont__7_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 322: ... namespaces(namespace).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_192;
}
static void cont__7_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 322: ... :
  // 323:   SyntaxError identifier_of(info) "
  // 324:     An identifier named "@(namespace)::@(name)" was already @
  // 325:     defined@
  frame->slots[7] /* temp__3 */ = create_closure(entry__7_193, 0);
  // 322: if namespaces(namespace).is_defined:
  // 323:   SyntaxError identifier_of(info) "
  // 324:     An identifier named "@(namespace)::@(name)" was already @
  // 325:     defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_199;
}
static void entry__7_193(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // info: 0
  // namespace: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 323: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_194;
}
static void cont__7_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 323: ... "
  // 324:   An identifier named "@(namespace)::@(name)" was already @
  // 325:   defined@
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__7_195;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__7_196;
  arguments->slots[3] = frame->slots[2] /* name */;
  arguments->slots[4] = string__7_197;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_198;
}
static void cont__7_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 323: SyntaxError identifier_of(info) "
  // 324:   An identifier named "@(namespace)::@(name)" was already @
  // 325:   defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_199(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 326: ... used_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__7_200;
}
static void cont__7_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 326: ... :
  // 327:   if global_names(name).is_defined:
  // 328:     SyntaxError identifier_of(info) "
  // 329:       The definition of "@(namespace)::@(name)" clashes with the @
  // 330:       already defined identifier "@(name)@quot;@
  // 331:   $info_1 top_level_names(name)
  // 332:   if info_1.is_defined:
  // 333:     SyntaxError identifier_of(info) "
  // 334:       The definition of "@(namespace)::@(name)" clashes with the @
  // 335:       definition of "@(namespace_of(identifier_of(info_1)))@
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__7_201, 0);
  // 326: if used_namespaces(namespace):
  // 327:   if global_names(name).is_defined:
  // 328:     SyntaxError identifier_of(info) "
  // 329:       The definition of "@(namespace)::@(name)" clashes with the @
  // 330:       already defined identifier "@(name)@quot;@
  // 331:   $info_1 top_level_names(name)
  // 332:   if info_1.is_defined:
  // 333:     SyntaxError identifier_of(info) "
  // 334:       The definition of "@(namespace)::@(name)" clashes with the @
  // 335:       definition of "@(namespace_of(identifier_of(info_1)))@
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_226;
}
static void entry__7_201(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // name: 0
  // info: 1
  // namespace: 2
  // top_level_names: 3
  // info_1: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[1]; /* namespace */
  frame->slots[3] = myself->closure.frame->slots[3]; /* top_level_names */
  frame->slots[4] /* info_1 */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 327: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__7_202;
}
static void cont__7_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 327: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_203;
}
static void cont__7_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 327: ... :
  // 328:   SyntaxError identifier_of(info) "
  // 329:     The definition of "@(namespace)::@(name)" clashes with the @
  // 330:     already defined identifier "@(name)@quot;@
  frame->slots[7] /* temp__3 */ = create_closure(entry__7_204, 0);
  // 327: if global_names(name).is_defined:
  // 328:   SyntaxError identifier_of(info) "
  // 329:     The definition of "@(namespace)::@(name)" clashes with the @
  // 330:     already defined identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_211;
}
static void entry__7_204(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // info: 0
  // namespace: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 328: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_205;
}
static void cont__7_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 328: ... "
  // 329:   The definition of "@(namespace)::@(name)" clashes with the @
  // 330:   already defined identifier "@(name)@quot;@
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__7_206;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__7_207;
  arguments->slots[3] = frame->slots[2] /* name */;
  arguments->slots[4] = string__7_208;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_209;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_210;
}
static void cont__7_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 328: SyntaxError identifier_of(info) "
  // 329:   The definition of "@(namespace)::@(name)" clashes with the @
  // 330:   already defined identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_211(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 331: $info_1 top_level_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__7_212;
}
static void cont__7_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* info_1 */, arguments->slots[0]);
  // 332: ... info_1.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* info_1 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_213;
}
static void cont__7_213(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 332: ... :
  // 333:   SyntaxError identifier_of(info) "
  // 334:     The definition of "@(namespace)::@(name)" clashes with the @
  // 335:     definition of "@(namespace_of(identifier_of(info_1)))@
  // 336:     ::@(name)" because both namespaces are used@
  frame->slots[6] /* temp__2 */ = create_closure(entry__7_214, 0);
  // 332: if info_1.is_defined:
  // 333:   SyntaxError identifier_of(info) "
  // 334:     The definition of "@(namespace)::@(name)" clashes with the @
  // 335:     definition of "@(namespace_of(identifier_of(info_1)))@
  // 336:     ::@(name)" because both namespaces are used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_224;
}
static void entry__7_214(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // info: 0
  // namespace: 1
  // name: 2
  // info_1: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  frame->slots[3] = myself->closure.frame->slots[4]; /* info_1 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_215;
}
static void cont__7_215(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 335: ... identifier_of(info_1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info_1 */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_216;
}
static void cont__7_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 335: ... namespace_of(identifier_of(info_1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__7_217;
}
static void cont__7_217(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 333: ... "
  // 334:   The definition of "@(namespace)::@(name)" clashes with the @
  // 335:   definition of "@(namespace_of(identifier_of(info_1)))@
  // 336:   ::@(name)" because both namespaces are used@
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_218;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__7_219;
  arguments->slots[3] = frame->slots[2] /* name */;
  arguments->slots[4] = string__7_220;
  arguments->slots[5] = frame->slots[6] /* temp__3 */;
  arguments->slots[6] = string__7_221;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_222;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_223;
}
static void cont__7_223(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 333: SyntaxError identifier_of(info) "
  // 334:   The definition of "@(namespace)::@(name)" clashes with the @
  // 335:   definition of "@(namespace_of(identifier_of(info_1)))@
  // 336:   ::@(name)" because both namespaces are used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_224(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 337: !top_level_names(name) info
  frame->slots[5] /* temp__1 */ = frame->slots[1] /* info */;
  // 337: !top_level_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__7_225;
}
static void cont__7_225(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* top_level_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_226(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 338: !namespaces(namespace) info
  frame->slots[5] /* temp__1 */ = frame->slots[2] /* info */;
  // 338: !namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* namespaces */;
  func = myself->type;
  frame->cont = cont__7_227;
}
static void cont__7_227(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* namespaces */ = arguments->slots[0];
  // 339: !exported_names(name) namespaces
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* namespaces */;
  // 339: !exported_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__7_228;
}
static void cont__7_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__exported_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_229(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // top_level_names: 2
  // namespaces: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* top_level_names */
  frame->slots[3] /* namespaces */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 341: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__7_230;
}
static void cont__7_230(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 341: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_231;
}
static void cont__7_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 341: ... :
  // 342:   SyntaxError identifier_of(info) "
  // 343:     An identifier named "@(name)" was already defined@
  frame->slots[6] /* temp__3 */ = create_closure(entry__7_232, 0);
  // 341: if global_names(name).is_defined:
  // 342:   SyntaxError identifier_of(info) "
  // 343:     An identifier named "@(name)" was already defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_237;
}
static void entry__7_232(void) {
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
  // 342: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_233;
}
static void cont__7_233(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 342: ... "
  // 343:   An identifier named "@(name)" was already defined@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_234;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__7_235;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_236;
}
static void cont__7_236(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 342: SyntaxError identifier_of(info) "
  // 343:   An identifier named "@(name)" was already defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_237(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 344: $namespaces exported_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__7_238;
}
static void cont__7_238(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespaces */, arguments->slots[0]);
  // 345: ... namespaces.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespaces */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_239;
}
static void cont__7_239(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   for_each namespaces: (nspace _dummy)
  // 347:     if used_namespaces(nspace):
  // 348:       SyntaxError identifier_of(info) "
  // 349:         The definition of "@(name)" clashes with the already @
  // 350:         defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_240, 0);
  // 345: if namespaces.is_defined:
  // 346:   for_each namespaces: (nspace _dummy)
  // 347:     if used_namespaces(nspace):
  // 348:       SyntaxError identifier_of(info) "
  // 349:         The definition of "@(name)" clashes with the already @
  // 350:         defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_250;
}
static void entry__7_243(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // info: 0
  // name: 1
  // nspace: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* nspace */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 348: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_244;
}
static void cont__7_244(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 348: ... "
  // 349:   The definition of "@(name)" clashes with the already @
  // 350:   defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__7_245;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__7_246;
  arguments->slots[3] = frame->slots[2] /* nspace */;
  arguments->slots[4] = string__7_247;
  arguments->slots[5] = frame->slots[1] /* name */;
  arguments->slots[6] = string__7_248;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_249;
}
static void cont__7_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 348: SyntaxError identifier_of(info) "
  // 349:   The definition of "@(name)" clashes with the already @
  // 350:   defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_241(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // nspace: 0
  // dummy: 1
  // info: 2
  // name: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  frame->slots[3] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 347: ... used_namespaces(nspace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* nspace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__7_242;
}
static void cont__7_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 347: ... :
  // 348:   SyntaxError identifier_of(info) "
  // 349:     The definition of "@(name)" clashes with the already @
  // 350:     defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_243, 0);
  // 347: if used_namespaces(nspace):
  // 348:   SyntaxError identifier_of(info) "
  // 349:     The definition of "@(name)" clashes with the already @
  // 350:     defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_240(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // namespaces: 0
  // info: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* namespaces */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 346: ... : (nspace _dummy)
  // 347:   if used_namespaces(nspace):
  // 348:     SyntaxError identifier_of(info) "
  // 349:       The definition of "@(name)" clashes with the already @
  // 350:       defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_241, 2);
  // 346: for_each namespaces: (nspace _dummy)
  // 347:   if used_namespaces(nspace):
  // 348:     SyntaxError identifier_of(info) "
  // 349:       The definition of "@(name)" clashes with the already @
  // 350:       defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespaces */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_250(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 351: !global_names(name) info
  frame->slots[4] /* temp__1 */ = frame->slots[1] /* info */;
  // 351: !global_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__7_251;
}
static void cont__7_251(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__global_names(arguments->slots[0]);
  // 352: !top_level_names(name) info
  frame->slots[4] /* temp__1 */ = frame->slots[1] /* info */;
  // 352: !top_level_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__7_252;
}
static void cont__7_252(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* top_level_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_181(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // ident: 0
  // info: 1
  // top_level_names: 2
  // namespace: 3
  // name: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* ident */
  frame->slots[1] = myself->closure.frame->slots[0]; /* info */
  frame->slots[2] = myself->closure.frame->slots[1]; /* top_level_names */
  frame->slots[3] /* namespace */ = create_future();
  frame->slots[4] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 316: $namespace namespace_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__7_182;
}
static void cont__7_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespace */, arguments->slots[0]);
  // 317: $name name_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__7_183;
}
static void cont__7_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 319: namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_184;
}
static void cont__7_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 319: ... :
  // 320:   $$namespaces exported_names(name)
  // 321:   unless namespaces.is_defined: !namespaces table()
  // 322:   if namespaces(namespace).is_defined:
  // 323:     SyntaxError identifier_of(info) "
  // 324:       An identifier named "@(namespace)::@(name)" was already @
  // 325:       defined@
  // 326:   if used_namespaces(namespace):
  // 327:     if global_names(name).is_defined:
  // 328:       SyntaxError identifier_of(info) "
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__7_185, 0);
  // 340: :
  // 341:   if global_names(name).is_defined:
  // 342:     SyntaxError identifier_of(info) "
  // 343:       An identifier named "@(name)" was already defined@
  // 344:   $namespaces exported_names(name)
  // 345:   if namespaces.is_defined:
  // 346:     for_each namespaces: (nspace _dummy)
  // 347:       if used_namespaces(nspace):
  // 348:         SyntaxError identifier_of(info) "
  // 349:           The definition of "@(name)" clashes with the already @
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__7_229, 0);
  // 318: if
  // 319:   namespace.is_defined:
  // 320:     $$namespaces exported_names(name)
  // 321:     unless namespaces.is_defined: !namespaces table()
  // 322:     if namespaces(namespace).is_defined:
  // 323:       SyntaxError identifier_of(info) "
  // 324:         An identifier named "@(namespace)::@(name)" was already @
  // 325:         defined@
  // 326:     if used_namespaces(namespace):
  // 327:       if global_names(name).is_defined:
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
static void entry__7_174(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // info: 0
  // top_level_names: 1
  // ident: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* top_level_names */
  frame->slots[2] /* ident */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 313: $ident identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_175;
}
static void cont__7_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ident */, arguments->slots[0]);
  // 315: info.is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__7_176;
}
static void cont__7_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 315: ... attribute_of(info).is_defined
  frame->slots[5] /* temp__3 */ = create_closure(entry__7_177, 0);
  // 315: info.is_a_static_single_definition && attribute_of(info).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_180;
}
static void entry__7_177(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 315: ... attribute_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__7_178;
}
static void cont__7_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 315: ... attribute_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_179;
}
static void cont__7_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 315: ... attribute_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 315: ... :
  // 316:   $namespace namespace_of(ident)
  // 317:   $name name_of(ident)
  // 318:   if
  // 319:     namespace.is_defined:
  // 320:       $$namespaces exported_names(name)
  // 321:       unless namespaces.is_defined: !namespaces table()
  // 322:       if namespaces(namespace).is_defined:
  // 323:         SyntaxError identifier_of(info) "
  // 324:           An identifier named "@(namespace)::@(name)" was already @
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__7_181, 0);
  // 314: unless
  // 315:   info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 316:     $namespace namespace_of(ident)
  // 317:     $name name_of(ident)
  // 318:     if
  // 319:       namespace.is_defined:
  // 320:         $$namespaces exported_names(name)
  // 321:         unless namespaces.is_defined: !namespaces table()
  // 322:         if namespaces(namespace).is_defined:
  // 323:           SyntaxError identifier_of(info) "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_173(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // defined_names: 0
  // top_level_names: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* top_level_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 312: ... : (info)
  // 313:   $ident identifier_of(info)
  // 314:   unless
  // 315:     info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 316:       $namespace namespace_of(ident)
  // 317:       $name name_of(ident)
  // 318:       if
  // 319:         namespace.is_defined:
  // 320:           $$namespaces exported_names(name)
  // 321:           unless namespaces.is_defined: !namespaces table()
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__7_174, 1);
  // 312: for_each defined_names: (info)
  // 313:   $ident identifier_of(info)
  // 314:   unless
  // 315:     info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 316:       $namespace namespace_of(ident)
  // 317:       $name name_of(ident)
  // 318:       if
  // 319:         namespace.is_defined:
  // 320:           $$namespaces exported_names(name)
  // 321:           unless namespaces.is_defined: !namespaces table()
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defined_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_253(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: ... :
  // 354:   $$top_level_used_names empty_insert_order_table
  // 355:   for_each all_used_names: (used_names)
  // 356:     for_each used_names: (mangled_name info)
  // 357:       !top_level_used_names(mangled_name) info
  // 358:   check_definitions top_level_names top_level_used_names
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_254, 0);
  // 353: if do_print_warnings:
  // 354:   $$top_level_used_names empty_insert_order_table
  // 355:   for_each all_used_names: (used_names)
  // 356:     for_each used_names: (mangled_name info)
  // 357:       !top_level_used_names(mangled_name) info
  // 358:   check_definitions top_level_names top_level_used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_259;
}
static void entry__7_254(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // all_used_names: 0
  // top_level_names: 1
  // top_level_used_names: 2
  frame->slots[0] = myself->closure.frame->slots[7]; /* all_used_names */
  frame->slots[1] = myself->closure.frame->slots[9]; /* top_level_names */
  frame->slots[2] /* top_level_used_names */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 354: $$top_level_used_names empty_insert_order_table
  ((CELL *)frame->slots[2])->contents /* top_level_used_names */ = get__empty_insert_order_table();
  // 355: ... : (used_names)
  // 356:   for_each used_names: (mangled_name info)
  // 357:     !top_level_used_names(mangled_name) info
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_255, 1);
  // 355: for_each all_used_names: (used_names)
  // 356:   for_each used_names: (mangled_name info)
  // 357:     !top_level_used_names(mangled_name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* all_used_names */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_258;
}
static void entry__7_256(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // mangled_name: 0
  // info: 1
  // top_level_used_names: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* top_level_used_names */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 357: !top_level_used_names(mangled_name) info
  frame->slots[3] /* temp__1 */ = frame->slots[1] /* info */;
  // 357: !top_level_used_names(mangled_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* top_level_used_names */;
  func = myself->type;
  frame->cont = cont__7_257;
}
static void cont__7_257(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* top_level_used_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_255(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // used_names: 0
  // top_level_used_names: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* top_level_used_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 356: ... : (mangled_name info)
  // 357:   !top_level_used_names(mangled_name) info
  frame->slots[2] /* temp__1 */ = create_closure(entry__7_256, 2);
  // 356: for_each used_names: (mangled_name info)
  // 357:   !top_level_used_names(mangled_name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* used_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_258(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 358: check_definitions top_level_names top_level_used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* top_level_names */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* top_level_used_names */;
  result_count = frame->caller_result_count;
  myself = get__check_definitions();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_259(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 359: ... : write_timing_info "analyzing" filenames(1)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_260, 0);
  // 359: if do_time_passes: write_timing_info "analyzing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_263;
}
static void entry__7_260(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 359: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__7_261;
}
static void cont__7_261(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 359: ... write_timing_info "analyzing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_262;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_263(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 360: ... :
  // 361:   for_each trees: (tree) write debug_string(strip(tree) 0 99)
  // 362:   terminate
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_264, 0);
  // 360: if do_dump_trees:
  // 361:   for_each trees: (tree) write debug_string(strip(tree) 0 99)
  // 362:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_269;
}
static void entry__7_264(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 361: for_each trees: (tree) write debug_string(strip(tree) 0 99)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  arguments->slots[1] = func__7_265;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_268;
}
static void entry__7_265(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // tree: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 361: ... strip(tree)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__7_266;
}
static void cont__7_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 361: ... debug_string(strip(tree) 0 99)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__99;
  result_count = 1;
  myself = get__debug_string();
  func = myself->type;
  frame->cont = cont__7_267;
}
static void cont__7_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 361: ... write debug_string(strip(tree) 0 99)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_268(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 362: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_269(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 363: $$all_definitions empty_list
  ((CELL *)frame->slots[10])->contents /* all_definitions */ = get__empty_list();
  // 364: $$all_statements empty_list
  ((CELL *)frame->slots[11])->contents /* all_statements */ = get__empty_list();
  // 365: $$max_temp_idx 0
  ((CELL *)frame->slots[12])->contents /* max_temp_idx */ = number__0;
  // 366: ... : (tree)
  // 367:   unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 368:     %%sim2c::temp_idx 0
  // 369:     %%sim2c::actions empty_list
  // 370:     %already_defined_names top_level_names
  // 371:     %%definitions empty_list
  // 372:     %%statements empty_list
  // 373:     simplify_statement tree
  // 374:     push &all_statements statements
  // 375:     push &all_definitions definitions
  // ...
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_270, 1);
  // 366: for_each trees: (tree)
  // 367:   unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 368:     %%sim2c::temp_idx 0
  // 369:     %%sim2c::actions empty_list
  // 370:     %already_defined_names top_level_names
  // 371:     %%definitions empty_list
  // 372:     %%statements empty_list
  // 373:     simplify_statement tree
  // 374:     push &all_statements statements
  // 375:     push &all_definitions definitions
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_283;
}
static void entry__7_275(void) {
  allocate_initialized_frame_gc(7, 9);
  // slot allocations:
  // return__4: 0
  // top_level_names: 1
  // tree: 2
  // all_statements: 3
  // all_definitions: 4
  // max_temp_idx: 5
  // all_actions: 6
  // tmp_idx: 7
  frame->slots[0] /* return__4 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* top_level_names */
  frame->slots[2] = myself->closure.frame->slots[0]; /* tree */
  frame->slots[3] = myself->closure.frame->slots[2]; /* all_statements */
  frame->slots[4] = myself->closure.frame->slots[3]; /* all_definitions */
  frame->slots[5] = myself->closure.frame->slots[4]; /* max_temp_idx */
  frame->slots[6] = myself->closure.frame->slots[5]; /* all_actions */
  define__sim2c__temp_idx(undefined);
  define__sim2c__actions(undefined);
  // _define %already_defined_names top_level_names
  define__already_defined_names(create_future());
  define__definitions(undefined);
  define__statements(undefined);
  // _define $tmp_idx temp_idx
  frame->slots[7] /* tmp_idx */ = get_value_or_future__temp_idx();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 368: %%sim2c::temp_idx 0
  set__sim2c__temp_idx(number__0);
  // 369: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 370: %already_defined_names top_level_names
  initialize_maybe_future(get__already_defined_names(), ((CELL *)frame->slots[1])->contents /* top_level_names */);
  // 371: %%definitions empty_list
  set__definitions(get__empty_list());
  // 372: %%statements empty_list
  set__statements(get__empty_list());
  // 373: simplify_statement tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* tree */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__7_276;
}
static void cont__7_276(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 374: push &all_statements statements
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_statements */;
  arguments->slots[1] = get__statements();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_277;
}
static void cont__7_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* all_statements */ = arguments->slots[0];
  // 375: push &all_definitions definitions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* all_definitions */;
  arguments->slots[1] = get__definitions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_278;
}
static void cont__7_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* all_definitions */ = arguments->slots[0];
  // 376: $tmp_idx temp_idx
  initialize_maybe_future(frame->slots[7] /* tmp_idx */, get__temp_idx());
  // 377: ... : extend_to &max_temp_idx tmp_idx
  frame->slots[8] /* temp__1 */ = create_closure(entry__7_279, 0);
  // 377: push &actions: extend_to &max_temp_idx tmp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_281;
}
static void entry__7_279(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // max_temp_idx: 0
  // tmp_idx: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* max_temp_idx */
  frame->slots[1] = myself->closure.frame->slots[7]; /* tmp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 377: ... extend_to &max_temp_idx tmp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  arguments->slots[1] = frame->slots[1] /* tmp_idx */;
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__7_280;
}
static void cont__7_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* max_temp_idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 378: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_282;
}
static void cont__7_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__4 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__7_270(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // tree: 0
  // top_level_names: 1
  // all_statements: 2
  // all_definitions: 3
  // max_temp_idx: 4
  // all_actions: 5
  frame->slots[1] = myself->closure.frame->slots[9]; /* top_level_names */
  frame->slots[2] = myself->closure.frame->slots[11]; /* all_statements */
  frame->slots[3] = myself->closure.frame->slots[10]; /* all_definitions */
  frame->slots[4] = myself->closure.frame->slots[12]; /* max_temp_idx */
  frame->slots[5] = myself->closure.frame->slots[8]; /* all_actions */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 367: ... tree.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__7_271;
}
static void cont__7_271(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 367: ... tree.is_a_meta_instruction
  frame->slots[8] /* temp__3 */ = create_closure(entry__7_272, 0);
  // 367: ... tree.is_a_remark || tree.is_a_meta_instruction
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__7_274;
}
static void entry__7_272(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tree: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tree */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 367: ... tree.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__is_a_meta_instruction();
  func = myself->type;
  frame->cont = cont__7_273;
}
static void cont__7_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 367: ... tree.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_274(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 367: ... :
  // 368:   %%sim2c::temp_idx 0
  // 369:   %%sim2c::actions empty_list
  // 370:   %already_defined_names top_level_names
  // 371:   %%definitions empty_list
  // 372:   %%statements empty_list
  // 373:   simplify_statement tree
  // 374:   push &all_statements statements
  // 375:   push &all_definitions definitions
  // 376:   $tmp_idx temp_idx
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__7_275, 0);
  // 367: unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 368:   %%sim2c::temp_idx 0
  // 369:   %%sim2c::actions empty_list
  // 370:   %already_defined_names top_level_names
  // 371:   %%definitions empty_list
  // 372:   %%statements empty_list
  // 373:   simplify_statement tree
  // 374:   push &all_statements statements
  // 375:   push &all_definitions definitions
  // 376:   $tmp_idx temp_idx
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_283(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 379: for_each all_actions: (stmt_actions) for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* all_actions */;
  arguments->slots[1] = func__7_284;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_286;
}
static void entry__7_285(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // action: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 379: ... action
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* action */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_284(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt_actions: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 379: ... for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_actions */;
  arguments->slots[1] = func__7_285;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_286(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 380: !all_actions empty_list
  ((CELL *)frame->slots[8])->contents /* all_actions */ = get__empty_list();
  // 381: ... : write_timing_info "simplifying" filenames(1)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_287, 0);
  // 381: if do_time_passes: write_timing_info "simplifying" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_290;
}
static void entry__7_287(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 381: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__7_288;
}
static void cont__7_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 381: ... write_timing_info "simplifying" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_289;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_290(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 382: ... :
  // 383:   for_each all_definitions: (defs)
  // 384:     for_each defs: (def)
  // 385:       if
  // 386:         def.is_a_key_value_pair:
  // 387:           writeln "_define " key_of(def) ' ' std::value_of(def)
  // 388:         :
  // 389:           writeln "_define " def
  // 390:   for_each all_statements: (stmts) print_trees stmts
  // 391:   terminate
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_291, 0);
  // 382: if do_print_simplified_source:
  // 383:   for_each all_definitions: (defs)
  // 384:     for_each defs: (def)
  // 385:       if
  // 386:         def.is_a_key_value_pair:
  // 387:           writeln "_define " key_of(def) ' ' std::value_of(def)
  // 388:         :
  // 389:           writeln "_define " def
  // 390:   for_each all_statements: (stmts) print_trees stmts
  // 391:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_304;
}
static void entry__7_291(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // all_definitions: 0
  // all_statements: 1
  frame->slots[0] = myself->closure.frame->slots[10]; /* all_definitions */
  frame->slots[1] = myself->closure.frame->slots[11]; /* all_statements */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: for_each all_definitions: (defs)
  // 384:   for_each defs: (def)
  // 385:     if
  // 386:       def.is_a_key_value_pair:
  // 387:         writeln "_define " key_of(def) ' ' std::value_of(def)
  // 388:       :
  // 389:         writeln "_define " def
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* all_definitions */;
  arguments->slots[1] = func__7_292;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_301;
}
static void entry__7_295(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // def: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* def */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 387: ... key_of(def)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__7_296;
}
static void cont__7_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 387: ... std::value_of(def)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__7_297;
}
static void cont__7_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 387: writeln "_define " key_of(def) ' ' std::value_of(def)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__7_298;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  arguments->slots[2] = character__32;
  arguments->slots[3] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_299(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // def: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* def */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 389: writeln "_define " def
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_300;
  arguments->slots[1] = frame->slots[0] /* def */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_293(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // def: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 386: def.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__7_294;
}
static void cont__7_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 386: ... :
  // 387:   writeln "_define " key_of(def) ' ' std::value_of(def)
  frame->slots[2] /* temp__2 */ = create_closure(entry__7_295, 0);
  // 388: :
  // 389:   writeln "_define " def
  frame->slots[3] /* temp__3 */ = create_closure(entry__7_299, 0);
  // 385: if
  // 386:   def.is_a_key_value_pair:
  // 387:     writeln "_define " key_of(def) ' ' std::value_of(def)
  // 388:   :
  // 389:     writeln "_define " def
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_292(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // defs: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 384: for_each defs: (def)
  // 385:   if
  // 386:     def.is_a_key_value_pair:
  // 387:       writeln "_define " key_of(def) ' ' std::value_of(def)
  // 388:     :
  // 389:       writeln "_define " def
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defs */;
  arguments->slots[1] = func__7_293;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_301(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 390: for_each all_statements: (stmts) print_trees stmts
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* all_statements */;
  arguments->slots[1] = func__7_302;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_303;
}
static void entry__7_302(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmts: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 390: ... print_trees stmts
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmts */;
  result_count = frame->caller_result_count;
  myself = get__print_trees();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_303(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 391: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_304(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 413: ... : (used_names)
  // 414:   for_each used_names: (mangled_name info) need mangled_name info
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_305, 1);
  // 413: for_each all_used_names: (used_names)
  // 414:   for_each used_names: (mangled_name info) need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* all_used_names */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_307;
}
static void entry__7_306(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // mangled_name: 0
  // info: 1
  // need: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* need */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 414: ... need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* need */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_305(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // used_names: 0
  // need: 1
  frame->slots[1] = myself->closure.frame->slots[13]; /* need */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 414: ... : (mangled_name info) need mangled_name info
  frame->slots[2] /* temp__1 */ = create_closure(entry__7_306, 2);
  // 414: for_each used_names: (mangled_name info) need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* used_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_307(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 415: ... : write_timing_info "mangling" filenames(1)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_308, 0);
  // 415: if do_time_passes: write_timing_info "mangling" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_311;
}
static void entry__7_308(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 415: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__7_309;
}
static void cont__7_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 415: ... write_timing_info "mangling" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_310;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_311(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 416: if do_check_only terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = get__terminate();
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_312;
}
static void cont__7_312(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 417: $$generated_declarations ""
  ((CELL *)frame->slots[14])->contents /* generated_declarations */ = empty_string;
  // 418: $$generated_top_level_variable_names ""
  ((CELL *)frame->slots[15])->contents /* generated_top_level_variable_names */ = empty_string;
  // 419: $$generated_top_level_variable_declarations ""
  ((CELL *)frame->slots[16])->contents /* generated_top_level_variable_declarations */ = empty_string;
  // 420: $$generated_global_variable_declarations ""
  ((CELL *)frame->slots[17])->contents /* generated_global_variable_declarations */ = empty_string;
  // 421: $$generated_continuation_table ""
  ((CELL *)frame->slots[18])->contents /* generated_continuation_table */ = empty_string;
  // 422: $$generated_delayed_continuation_table ""
  ((CELL *)frame->slots[19])->contents /* generated_delayed_continuation_table */ = empty_string;
  // 423: $$generated_functions ""
  ((CELL *)frame->slots[20])->contents /* generated_functions */ = empty_string;
  // 424: $$generated_phase_1 ""
  ((CELL *)frame->slots[21])->contents /* generated_phase_1 */ = empty_string;
  // 431: $$generated_phase_2 ""
  ((CELL *)frame->slots[22])->contents /* generated_phase_2 */ = empty_string;
  // 443: $$generated_phase_3 ""
  ((CELL *)frame->slots[23])->contents /* generated_phase_3 */ = empty_string;
  // 461: $$generated_phase_4 ""
  ((CELL *)frame->slots[24])->contents /* generated_phase_4 */ = empty_string;
  // 476: $$generated_phase_5 ""
  ((CELL *)frame->slots[25])->contents /* generated_phase_5 */ = empty_string;
  // 479: $$generated_code ""
  ((CELL *)frame->slots[26])->contents /* generated_code */ = empty_string;
  // 480: $$generated_collections ""
  ((CELL *)frame->slots[27])->contents /* generated_collections */ = empty_string;
  // 481: $$delayed_statements ""
  ((CELL *)frame->slots[28])->contents /* delayed_statements */ = empty_string;
  // 482: $$used_literals empty_table
  ((CELL *)frame->slots[29])->contents /* used_literals */ = get__empty_table();
  // 484: ... : (args*)
  // 485:   $txt string(args*)
  // 486:   push &actions: append &generated_declarations txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_313, -1);
  // 484: %sim2c::write_to_declarations: (args*)
  // 485:   $txt string(args*)
  // 486:   push &actions: append &generated_declarations txt
  initialize_future(get__sim2c__write_to_declarations(), frame->slots[32] /* temp__1 */);
  // 488: ... : (args*)
  // 489:   $txt string(args*)
  // 490:   push &actions: append &generated_top_level_variable_names txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_318, -1);
  // 488: %sim2c::write_to_top_level_variable_names: (args*)
  // 489:   $txt string(args*)
  // 490:   push &actions: append &generated_top_level_variable_names txt
  initialize_future(get__sim2c__write_to_top_level_variable_names(), frame->slots[32] /* temp__1 */);
  // 492: ... : (args*)
  // 493:   $txt string(args*)
  // 494:   push &actions: append &generated_top_level_variable_declarations txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_323, -1);
  // 492: %sim2c::write_to_top_level_variable_declarations: (args*)
  // 493:   $txt string(args*)
  // 494:   push &actions: append &generated_top_level_variable_declarations txt
  initialize_future(get__sim2c__write_to_top_level_variable_declarations(), frame->slots[32] /* temp__1 */);
  // 496: ... : (args*)
  // 497:   $txt string(args*)
  // 498:   push &actions: append &generated_global_variable_declarations txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_328, -1);
  // 496: %sim2c::write_to_global_variable_declarations: (args*)
  // 497:   $txt string(args*)
  // 498:   push &actions: append &generated_global_variable_declarations txt
  initialize_future(get__sim2c__write_to_global_variable_declarations(), frame->slots[32] /* temp__1 */);
  // 500: ... : (args*)
  // 501:   $txt string(args*)
  // 502:   push &actions: append &generated_continuation_table txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_333, -1);
  // 500: %sim2c::write_to_continuation_table: (args*)
  // 501:   $txt string(args*)
  // 502:   push &actions: append &generated_continuation_table txt
  initialize_future(get__sim2c__write_to_continuation_table(), frame->slots[32] /* temp__1 */);
  // 504: ... : (args*)
  // 505:   $txt string(args*)
  // 506:   push &actions: append &generated_delayed_continuation_table txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_338, -1);
  // 504: %sim2c::write_to_delayed_continuation_table: (args*)
  // 505:   $txt string(args*)
  // 506:   push &actions: append &generated_delayed_continuation_table txt
  initialize_future(get__sim2c__write_to_delayed_continuation_table(), frame->slots[32] /* temp__1 */);
  // 508: ... : (args*)
  // 509:   $txt string(args*)
  // 510:   push &actions: append &generated_functions txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_343, -1);
  // 508: %sim2c::write_to_functions: (args*)
  // 509:   $txt string(args*)
  // 510:   push &actions: append &generated_functions txt
  initialize_future(get__sim2c__write_to_functions(), frame->slots[32] /* temp__1 */);
  // 512: ... : (args*)
  // 513:   $txt string(args*)
  // 514:   push &actions: append &generated_phase_1 txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_348, -1);
  // 512: %sim2c::write_to_phase_1: (args*)
  // 513:   $txt string(args*)
  // 514:   push &actions: append &generated_phase_1 txt
  initialize_future(get__sim2c__write_to_phase_1(), frame->slots[32] /* temp__1 */);
  // 516: ... : (args*)
  // 517:   $txt string(args*)
  // 518:   push &actions: append &generated_phase_2 txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_353, -1);
  // 516: %sim2c::write_to_phase_2: (args*)
  // 517:   $txt string(args*)
  // 518:   push &actions: append &generated_phase_2 txt
  initialize_future(get__sim2c__write_to_phase_2(), frame->slots[32] /* temp__1 */);
  // 520: ... : (args*)
  // 521:   $txt string(args*)
  // 522:   push &actions: append &generated_phase_3 txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_358, -1);
  // 520: %sim2c::write_to_phase_3: (args*)
  // 521:   $txt string(args*)
  // 522:   push &actions: append &generated_phase_3 txt
  initialize_future(get__sim2c__write_to_phase_3(), frame->slots[32] /* temp__1 */);
  // 524: ... : (args*)
  // 525:   $txt string(args*)
  // 526:   push &actions: append &generated_phase_4 txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_363, -1);
  // 524: %sim2c::write_to_phase_4: (args*)
  // 525:   $txt string(args*)
  // 526:   push &actions: append &generated_phase_4 txt
  initialize_future(get__sim2c__write_to_phase_4(), frame->slots[32] /* temp__1 */);
  // 528: ... : (args*)
  // 529:   $txt string(args*)
  // 530:   push &actions: append &generated_phase_5 txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_368, -1);
  // 528: %sim2c::write_to_phase_5: (args*)
  // 529:   $txt string(args*)
  // 530:   push &actions: append &generated_phase_5 txt
  initialize_future(get__sim2c__write_to_phase_5(), frame->slots[32] /* temp__1 */);
  // 532: ... : (name literal)
  // 533:   push &actions: !used_literals(name) literal
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_373, 2);
  // 532: %sim2c::use_literal: (name literal)
  // 533:   push &actions: !used_literals(name) literal
  initialize_future(get__sim2c__use_literal(), frame->slots[32] /* temp__1 */);
  // 535: ... : (args*)
  // 536:   $txt string(args*)
  // 537:   push &actions: append &generated_collections txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_377, -1);
  // 535: %sim2c::write_to_generated_collections: (args*)
  // 536:   $txt string(args*)
  // 537:   push &actions: append &generated_collections txt
  initialize_future(get__sim2c__write_to_generated_collections(), frame->slots[32] /* temp__1 */);
  // 539: ... : (args*)
  // 540:   $txt string(args*)
  // 541:   push &actions: append &delayed_statements txt
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_382, -1);
  // 539: %sim2c::write_to_delayed_statements: (args*)
  // 540:   $txt string(args*)
  // 541:   push &actions: append &delayed_statements txt
  initialize_future(get__sim2c__write_to_delayed_statements(), frame->slots[32] /* temp__1 */);
  // 543: ... : (ident)
  // 544:   if ident .has_prefix. "get__":
  // 545:     $name range(ident 6 -1)
  // 546:     need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_387, 1);
  // 543: %sim2c::use_identifier: (ident)
  // 544:   if ident .has_prefix. "get__":
  // 545:     $name range(ident 6 -1)
  // 546:     need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  initialize_future(get__sim2c__use_identifier(), frame->slots[32] /* temp__1 */);
  // 548: show_compiler_debug_info "GENERATE DEFINITIONS"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_393;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__7_394;
}
static void entry__7_390(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // ident: 0
  // need: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* ident */
  frame->slots[1] = myself->closure.frame->slots[1]; /* need */
  frame->slots[2] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 545: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_391;
}
static void cont__7_391(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 545: $name range(ident 6 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = number__6;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_392;
}
static void cont__7_392(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 546: ... types::grammar_node(.variable_kind_of STATIC_SINGLE)
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_SINGLE());
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 546: need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* need */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_313(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[14]; /* generated_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 485: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_314;
}
static void cont__7_314(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 486: ... : append &generated_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_315, 0);
  // 486: push &actions: append &generated_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_317;
}
static void entry__7_315(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_declarations: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_declarations */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 486: ... append &generated_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_316;
}
static void cont__7_316(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_declarations */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_317(void) {
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
static void entry__7_318(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_top_level_variable_names: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[15]; /* generated_top_level_variable_names */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 489: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_319;
}
static void cont__7_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 490: ... : append &generated_top_level_variable_names txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_320, 0);
  // 490: push &actions: append &generated_top_level_variable_names txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_322;
}
static void entry__7_320(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_top_level_variable_names: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_top_level_variable_names */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 490: ... append &generated_top_level_variable_names txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_321;
}
static void cont__7_321(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_322(void) {
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
static void entry__7_323(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_top_level_variable_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[16]; /* generated_top_level_variable_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 493: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_324;
}
static void cont__7_324(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 494: ... : append &generated_top_level_variable_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_325, 0);
  // 494: push &actions: append &generated_top_level_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_327;
}
static void entry__7_325(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_top_level_variable_declarations: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_top_level_variable_declarations */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 494: ... append &generated_top_level_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_326;
}
static void cont__7_326(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_declarations */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_327(void) {
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
static void entry__7_328(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_global_variable_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[17]; /* generated_global_variable_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 497: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_329;
}
static void cont__7_329(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 498: ... : append &generated_global_variable_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_330, 0);
  // 498: push &actions: append &generated_global_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_332;
}
static void entry__7_330(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_global_variable_declarations: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_global_variable_declarations */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 498: ... append &generated_global_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_global_variable_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_331;
}
static void cont__7_331(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_global_variable_declarations */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_332(void) {
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
static void entry__7_333(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_continuation_table: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[18]; /* generated_continuation_table */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 501: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_334;
}
static void cont__7_334(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 502: ... : append &generated_continuation_table txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_335, 0);
  // 502: push &actions: append &generated_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_337;
}
static void entry__7_335(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_continuation_table: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_continuation_table */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 502: ... append &generated_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_continuation_table */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_336;
}
static void cont__7_336(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_continuation_table */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_337(void) {
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
static void entry__7_338(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_delayed_continuation_table: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[19]; /* generated_delayed_continuation_table */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 505: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_339;
}
static void cont__7_339(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 506: ... : append &generated_delayed_continuation_table txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_340, 0);
  // 506: push &actions: append &generated_delayed_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_342;
}
static void entry__7_340(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_delayed_continuation_table: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_delayed_continuation_table */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 506: ... append &generated_delayed_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_delayed_continuation_table */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_341;
}
static void cont__7_341(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_delayed_continuation_table */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_342(void) {
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
static void entry__7_343(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_functions: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[20]; /* generated_functions */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 509: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_344;
}
static void cont__7_344(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 510: ... : append &generated_functions txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_345, 0);
  // 510: push &actions: append &generated_functions txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_347;
}
static void entry__7_345(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_functions: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_functions */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 510: ... append &generated_functions txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_functions */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_346;
}
static void cont__7_346(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_functions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_347(void) {
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
static void entry__7_348(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_1: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[21]; /* generated_phase_1 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 513: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_349;
}
static void cont__7_349(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 514: ... : append &generated_phase_1 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_350, 0);
  // 514: push &actions: append &generated_phase_1 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_352;
}
static void entry__7_350(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_phase_1: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_phase_1 */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 514: ... append &generated_phase_1 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_1 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_351;
}
static void cont__7_351(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_phase_1 */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_352(void) {
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
static void entry__7_353(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_2: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[22]; /* generated_phase_2 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 517: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_354;
}
static void cont__7_354(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 518: ... : append &generated_phase_2 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_355, 0);
  // 518: push &actions: append &generated_phase_2 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_357;
}
static void entry__7_355(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_phase_2: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_phase_2 */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 518: ... append &generated_phase_2 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_2 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_356;
}
static void cont__7_356(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_phase_2 */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_357(void) {
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
static void entry__7_358(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_3: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[23]; /* generated_phase_3 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 521: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_359;
}
static void cont__7_359(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 522: ... : append &generated_phase_3 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_360, 0);
  // 522: push &actions: append &generated_phase_3 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_362;
}
static void entry__7_360(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_phase_3: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_phase_3 */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 522: ... append &generated_phase_3 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_3 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_361;
}
static void cont__7_361(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_phase_3 */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_362(void) {
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
static void entry__7_363(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_4: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[24]; /* generated_phase_4 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 525: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_364;
}
static void cont__7_364(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 526: ... : append &generated_phase_4 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_365, 0);
  // 526: push &actions: append &generated_phase_4 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_367;
}
static void entry__7_365(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_phase_4: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_phase_4 */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 526: ... append &generated_phase_4 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_4 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_366;
}
static void cont__7_366(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_phase_4 */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_367(void) {
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
static void entry__7_368(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_5: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[25]; /* generated_phase_5 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 529: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_369;
}
static void cont__7_369(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 530: ... : append &generated_phase_5 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_370, 0);
  // 530: push &actions: append &generated_phase_5 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_372;
}
static void entry__7_370(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_phase_5: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_phase_5 */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 530: ... append &generated_phase_5 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_5 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_371;
}
static void cont__7_371(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_phase_5 */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_372(void) {
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
static void entry__7_373(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // name: 0
  // literal: 1
  // used_literals: 2
  frame->slots[2] = myself->closure.frame->slots[29]; /* used_literals */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 533: ... : !used_literals(name) literal
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_374, 0);
  // 533: push &actions: !used_literals(name) literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_376;
}
static void entry__7_374(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // used_literals: 0
  // name: 1
  // literal: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* used_literals */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 533: ... !used_literals(name) literal
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* literal */;
  // 533: ... !used_literals(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_literals */;
  func = myself->type;
  frame->cont = cont__7_375;
}
static void cont__7_375(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* used_literals */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_376(void) {
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
static void entry__7_377(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_collections: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[27]; /* generated_collections */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 536: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_378;
}
static void cont__7_378(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 537: ... : append &generated_collections txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_379, 0);
  // 537: push &actions: append &generated_collections txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_381;
}
static void entry__7_379(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_collections: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_collections */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 537: ... append &generated_collections txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_collections */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_380;
}
static void cont__7_380(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_collections */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_381(void) {
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
static void entry__7_382(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // delayed_statements: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[28]; /* delayed_statements */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 540: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_383;
}
static void cont__7_383(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 541: ... : append &delayed_statements txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_384, 0);
  // 541: push &actions: append &delayed_statements txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_386;
}
static void entry__7_384(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // delayed_statements: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* delayed_statements */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 541: ... append &delayed_statements txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* delayed_statements */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_385;
}
static void cont__7_385(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* delayed_statements */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_386(void) {
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
static void entry__7_387(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // ident: 0
  // need: 1
  frame->slots[1] = myself->closure.frame->slots[13]; /* need */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 544: ... ident .has_prefix. "get__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = string__7_388;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__7_389;
}
static void cont__7_389(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 544: ... :
  // 545:   $name range(ident 6 -1)
  // 546:   need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_390, 0);
  // 544: if ident .has_prefix. "get__":
  // 545:   $name range(ident 6 -1)
  // 546:   need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_394(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 549: ... : (stmt_idx defs)
  // 550:   %%sim2c::actions empty_list
  // 551:   %%sim2c::delayed_code ""
  // 552:   %sim2c::suffix string("__" stmt_idx)
  // 553:   %%sim2c::index 0
  // 554:   collect_output $code:
  // 555:     for_each defs: ($definition)
  // 556:       $$source undefined
  // 557:       if definition.is_a_key_value_pair:
  // 558:         !source std::value_of(definition)
  // ...
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_395, 2);
  // 549: for_each all_definitions: (stmt_idx defs)
  // 550:   %%sim2c::actions empty_list
  // 551:   %%sim2c::delayed_code ""
  // 552:   %sim2c::suffix string("__" stmt_idx)
  // 553:   %%sim2c::index 0
  // 554:   collect_output $code:
  // 555:     for_each defs: ($definition)
  // 556:       $$source undefined
  // 557:       if definition.is_a_key_value_pair:
  // 558:         !source std::value_of(definition)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_432;
}
static void entry__7_395(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // stmt_idx: 0
  // defs: 1
  // return__5: 2
  // generated_code: 3
  // all_actions: 4
  // code: 5
  frame->slots[2] /* return__5 */ = create_continuation();
  frame->slots[3] = myself->closure.frame->slots[26]; /* generated_code */
  frame->slots[4] = myself->closure.frame->slots[8]; /* all_actions */
  define__sim2c__actions(undefined);
  define__sim2c__delayed_code(undefined);
  define__sim2c__suffix(create_future());
  define__sim2c__index(undefined);
  frame->slots[5] /* code */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 550: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 551: %%sim2c::delayed_code ""
  set__sim2c__delayed_code(empty_string);
  // 552: %sim2c::suffix string("__" stmt_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_396;
  arguments->slots[1] = frame->slots[0] /* stmt_idx */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_397;
}
static void cont__7_397(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__suffix(), arguments->slots[0]);
  // 553: %%sim2c::index 0
  set__sim2c__index(number__0);
  // 554: ... :
  // 555:   for_each defs: ($definition)
  // 556:     $$source undefined
  // 557:     if definition.is_a_key_value_pair:
  // 558:       !source std::value_of(definition)
  // 559:       !definition key_of(definition)
  // 560:     if
  // 561:       definition.is_c_code:
  // 562:         define_c_code definition
  // 563:       :
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__7_398, 0);
  // 554: collect_output $code:
  // 555:   for_each defs: ($definition)
  // 556:     $$source undefined
  // 557:     if definition.is_a_key_value_pair:
  // 558:       !source std::value_of(definition)
  // 559:       !definition key_of(definition)
  // 560:     if
  // 561:       definition.is_c_code:
  // 562:         define_c_code definition
  // 563:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__7_423;
}
static void entry__7_420(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 575: define_method definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_method();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_421(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 577: define_type_function definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_type_function();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_416(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 571: define_attribute definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_attribute();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_417(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 574: attribute_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__7_418;
}
static void cont__7_418(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 574: attribute_of(definition).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_419;
}
static void cont__7_419(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 574: ... :
  // 575:   define_method definition source
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_420, 0);
  // 576: :
  // 577:   define_type_function definition source
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_421, 0);
  // 573: if
  // 574:   attribute_of(definition).is_defined:
  // 575:     define_method definition source
  // 576:   :
  // 577:     define_type_function definition source
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_422(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 579: define_variable definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_variable();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_412(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 566: ... source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__7_413;
}
static void cont__7_413(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 566: define_polymorphic_function definition source.is_a_setter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__define_polymorphic_function();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_414(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 569: attribute_kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__7_415;
}
static void cont__7_415(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 570: ... :
  // 571:   define_attribute definition source
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_416, 0);
  // 572: ... :
  // 573:   if
  // 574:     attribute_of(definition).is_defined:
  // 575:       define_method definition source
  // 576:     :
  // 577:       define_type_function definition source
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_417, 0);
  // 578: :
  // 579:   define_variable definition source
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_422, 0);
  // 568: case
  // 569:   attribute_kind_of(definition)
  // 570:   ATTRIBUTE_KIND:
  // 571:     define_attribute definition source
  // 572:   METHOD_KIND:
  // 573:     if
  // 574:       attribute_of(definition).is_defined:
  // 575:         define_method definition source
  // 576:       :
  // 577:         define_type_function definition source
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__ATTRIBUTE_KIND();
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  arguments->slots[3] = get__METHOD_KIND();
  arguments->slots[4] = frame->slots[4] /* temp__3 */;
  arguments->slots[5] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_406(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // definition: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 562: define_c_code definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = frame->caller_result_count;
  myself = get__define_c_code();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_407(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // source: 0
  // definition: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  frame->slots[1] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 565: source.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_408;
}
static void cont__7_408(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 565: ... source.is_a_polymorphic_function_constant
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_409, 0);
  // 565: source.is_defined && source.is_a_polymorphic_function_constant
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_411;
}
static void entry__7_409(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 565: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__7_410;
}
static void cont__7_410(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 565: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_411(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 565: ... :
  // 566:   define_polymorphic_function definition source.is_a_setter
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_412, 0);
  // 567: :
  // 568:   case
  // 569:     attribute_kind_of(definition)
  // 570:     ATTRIBUTE_KIND:
  // 571:       define_attribute definition source
  // 572:     METHOD_KIND:
  // 573:       if
  // 574:         attribute_of(definition).is_defined:
  // 575:           define_method definition source
  // 576:         :
  // ...
  frame->slots[6] /* temp__5 */ = create_closure(entry__7_414, 0);
  // 564: if
  // 565:   source.is_defined && source.is_a_polymorphic_function_constant:
  // 566:     define_polymorphic_function definition source.is_a_setter
  // 567:   :
  // 568:     case
  // 569:       attribute_kind_of(definition)
  // 570:       ATTRIBUTE_KIND:
  // 571:         define_attribute definition source
  // 572:       METHOD_KIND:
  // 573:         if
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = frame->slots[6] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_399(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[1] /* source */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* definition */ = create_cell_with_contents(arguments->slots[0]);
  // 556: $$source undefined
  ((CELL *)frame->slots[1])->contents /* source */ = get__undefined();
  // 557: ... definition.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__7_400;
}
static void cont__7_400(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 557: ... :
  // 558:   !source std::value_of(definition)
  // 559:   !definition key_of(definition)
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_401, 0);
  // 557: if definition.is_a_key_value_pair:
  // 558:   !source std::value_of(definition)
  // 559:   !definition key_of(definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_404;
}
static void entry__7_401(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // source: 0
  // definition: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  frame->slots[1] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 558: !source std::value_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__7_402;
}
static void cont__7_402(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* source */ = arguments->slots[0];
  // 559: !definition key_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__7_403;
}
static void cont__7_403(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* definition */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_404(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 561: definition.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__7_405;
}
static void cont__7_405(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 561: ... :
  // 562:   define_c_code definition
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_406, 0);
  // 563: :
  // 564:   if
  // 565:     source.is_defined && source.is_a_polymorphic_function_constant:
  // 566:       define_polymorphic_function definition source.is_a_setter
  // 567:     :
  // 568:       case
  // 569:         attribute_kind_of(definition)
  // 570:         ATTRIBUTE_KIND:
  // 571:           define_attribute definition source
  // 572:         METHOD_KIND:
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_407, 0);
  // 560: if
  // 561:   definition.is_c_code:
  // 562:     define_c_code definition
  // 563:   :
  // 564:     if
  // 565:       source.is_defined && source.is_a_polymorphic_function_constant:
  // 566:         define_polymorphic_function definition source.is_a_setter
  // 567:       :
  // 568:         case
  // 569:           attribute_kind_of(definition)
  // ...
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
static void entry__7_398(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // defs: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* defs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 555: for_each defs: ($definition)
  // 556:   $$source undefined
  // 557:   if definition.is_a_key_value_pair:
  // 558:     !source std::value_of(definition)
  // 559:     !definition key_of(definition)
  // 560:   if
  // 561:     definition.is_c_code:
  // 562:       define_c_code definition
  // 563:     :
  // 564:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defs */;
  arguments->slots[1] = func__7_399;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_423(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* code */, arguments->slots[0]);
  // 580: ... delayed_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_424;
}
static void cont__7_424(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 580: ... delayed_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_425;
}
static void cont__7_425(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 580: if delayed_code != "": write_to_delayed_statements delayed_code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__7_426;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_427;
}
static void entry__7_426(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 580: ... write_to_delayed_statements delayed_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  result_count = frame->caller_result_count;
  myself = get__write_to_delayed_statements();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_427(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 581: ... : append &generated_code code
  frame->slots[6] /* temp__1 */ = create_closure(entry__7_428, 0);
  // 581: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_430;
}
static void entry__7_428(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_code: 0
  // code: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* generated_code */
  frame->slots[1] = myself->closure.frame->slots[5]; /* code */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 581: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_429;
}
static void cont__7_429(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_code */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_430(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 582: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_431;
}
static void cont__7_431(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[2] /* return__5 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__7_432(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 583: show_compiler_debug_info "GENERATE STATEMENTS"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_433;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__7_434;
}
static void cont__7_434(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 584: %%sim2c::current_continuation_info undefined
  set__sim2c__current_continuation_info(get__undefined());
  // 585: ... :
  // 586:   %%sim2c::actions empty_list
  // 587:   %%sim2c::delayed_code ""
  // 588:   collect_output $code:
  // 589:     if
  // 590:       is_main:
  // 591:         begin_continuation "main_entry"
  // 592:       :
  // 593:         write_to_continuation_table "  {run__@(module_name), NULL, "
  // 594:         write "
  // ...
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_435, 0);
  // 585: do:
  // 586:   %%sim2c::actions empty_list
  // 587:   %%sim2c::delayed_code ""
  // 588:   collect_output $code:
  // 589:     if
  // 590:       is_main:
  // 591:         begin_continuation "main_entry"
  // 592:       :
  // 593:         write_to_continuation_table "  {run__@(module_name), NULL, "
  // 594:         write "
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__7_465;
}
static void entry__7_435(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // return__6: 0
  // is_main: 1
  // mangle_filename: 2
  // generated_code: 3
  // all_actions: 4
  // code: 5
  frame->slots[0] /* return__6 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[2] = myself->closure.frame->slots[3]; /* mangle_filename */
  frame->slots[3] = myself->closure.frame->slots[26]; /* generated_code */
  frame->slots[4] = myself->closure.frame->slots[8]; /* all_actions */
  define__sim2c__actions(undefined);
  define__sim2c__delayed_code(undefined);
  frame->slots[5] /* code */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 586: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 587: %%sim2c::delayed_code ""
  set__sim2c__delayed_code(empty_string);
  // 588: ... :
  // 589:   if
  // 590:     is_main:
  // 591:       begin_continuation "main_entry"
  // 592:     :
  // 593:       write_to_continuation_table "  {run__@(module_name), NULL, "
  // 594:       write "
  // 595:         static int already_run = false;
  // 596:         
  // 597:         EXPORT void run__@(module_name)(void) {
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__7_436, 0);
  // 588: collect_output $code:
  // 589:   if
  // 590:     is_main:
  // 591:       begin_continuation "main_entry"
  // 592:     :
  // 593:       write_to_continuation_table "  {run__@(module_name), NULL, "
  // 594:       write "
  // 595:         static int already_run = false;
  // 596:         
  // 597:         EXPORT void run__@(module_name)(void) {
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__7_460;
}
static void entry__7_448(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // mangle_filename: 2
  // continuation: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* mangle_filename */
  frame->slots[3] /* continuation */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 606: write_source_as_remark info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 0;
  myself = get__write_source_as_remark();
  func = myself->type;
  frame->cont = cont__7_449;
}
static void cont__7_449(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 608: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_450;
}
static void cont__7_450(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 609: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_451;
}
static void cont__7_451(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 607: ... "
  // 608:     func = run__@(mangle_filename(name));
  // 609:     frame->cont = cont__run__@(mangle_filename(name));
  // 610:   }
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__7_452;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = string__7_453;
  arguments->slots[3] = frame->slots[6] /* temp__3 */;
  arguments->slots[4] = string__7_454;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_455;
}
static void cont__7_455(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 607: write "
  // 608:     func = run__@(mangle_filename(name));
  // 609:     frame->cont = cont__run__@(mangle_filename(name));
  // 610:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_456;
}
static void cont__7_456(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 611: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_457;
}
static void cont__7_457(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 611: $continuation "cont__run__@(mangle_filename(name))"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_458;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_459;
}
static void cont__7_459(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* continuation */, arguments->slots[0]);
  // 612: next_continuation continuation
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* continuation */;
  result_count = frame->caller_result_count;
  myself = get__next_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_436(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // is_main: 0
  // mangle_filename: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[1] = myself->closure.frame->slots[2]; /* mangle_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 589: if
  // 590:   is_main:
  // 591:     begin_continuation "main_entry"
  // 592:   :
  // 593:     write_to_continuation_table "  {run__@(module_name), NULL, "
  // 594:     write "
  // 595:       static int already_run = false;
  // 596:       
  // 597:       EXPORT void run__@(module_name)(void) {
  // 598:         if (already_run) {
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  arguments->slots[1] = func__7_437;
  arguments->slots[2] = func__7_439;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_447;
}
static void entry__7_437(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 591: begin_continuation "main_entry"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_438;
  result_count = frame->caller_result_count;
  myself = get__begin_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_439(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: ... "  {run__@(module_name), NULL, "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_440;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_441;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_442;
}
static void cont__7_442(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 593: write_to_continuation_table "  {run__@(module_name), NULL, "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 0;
  myself = get__write_to_continuation_table();
  func = myself->type;
  frame->cont = cont__7_443;
}
static void cont__7_443(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 594: ... "
  // 595:   static int already_run = false;
  // 596:   
  // 597:   EXPORT void run__@(module_name)(void) {
  // 598:     if (already_run) {
  // 599:       func = frame->cont;
  // 600:       frame->cont = invalid_continuation;
  // 601:       return;
  // 602:     }
  // 603:     already_run = true;
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_444;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_445;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_446;
}
static void cont__7_446(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 594: write "
  // 595:   static int already_run = false;
  // 596:   
  // 597:   EXPORT void run__@(module_name)(void) {
  // 598:     if (already_run) {
  // 599:       func = frame->cont;
  // 600:       frame->cont = invalid_continuation;
  // 601:       return;
  // 602:     }
  // 603:     already_run = true;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_447(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 605: ... : (name info)
  // 606:   write_source_as_remark info
  // 607:   write "
  // 608:       func = run__@(mangle_filename(name));
  // 609:       frame->cont = cont__run__@(mangle_filename(name));
  // 610:     }
  // 611:   $continuation "cont__run__@(mangle_filename(name))"
  // 612:   next_continuation continuation
  frame->slots[2] /* temp__1 */ = create_closure(entry__7_448, 2);
  // 605: for_each required_modules: (name info)
  // 606:   write_source_as_remark info
  // 607:   write "
  // 608:       func = run__@(mangle_filename(name));
  // 609:       frame->cont = cont__run__@(mangle_filename(name));
  // 610:     }
  // 611:   $continuation "cont__run__@(mangle_filename(name))"
  // 612:   next_continuation continuation
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_460(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* code */, arguments->slots[0]);
  // 613: ... : append &generated_code code
  frame->slots[6] /* temp__1 */ = create_closure(entry__7_461, 0);
  // 613: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_463;
}
static void entry__7_461(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_code: 0
  // code: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* generated_code */
  frame->slots[1] = myself->closure.frame->slots[5]; /* code */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 613: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_462;
}
static void cont__7_462(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_code */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_463(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 614: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_464;
}
static void cont__7_464(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__6 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__7_465(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 615: $def_count length_of(all_definitions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__7_466;
}
static void cont__7_466(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[30] /* def_count */, arguments->slots[0]);
  // 616: ... : (stmt_idx stmts)
  // 617:   %%sim2c::actions empty_list
  // 618:   %%sim2c::delayed_code ""
  // 619:   %sim2c::suffix string("__" stmt_idx+def_count)
  // 620:   %%sim2c::index 0
  // 621:   collect_output $code: for_each stmts: (stmt) generate_statement stmt
  // 622:   if delayed_code != "": write_to_delayed_statements delayed_code
  // 623:   push &actions: append &generated_code code
  // 624:   push &all_actions actions
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_467, 2);
  // 616: for_each all_statements: (stmt_idx stmts)
  // 617:   %%sim2c::actions empty_list
  // 618:   %%sim2c::delayed_code ""
  // 619:   %sim2c::suffix string("__" stmt_idx+def_count)
  // 620:   %%sim2c::index 0
  // 621:   collect_output $code: for_each stmts: (stmt) generate_statement stmt
  // 622:   if delayed_code != "": write_to_delayed_statements delayed_code
  // 623:   push &actions: append &generated_code code
  // 624:   push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* all_statements */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_482;
}
static void entry__7_467(void) {
  allocate_initialized_frame_gc(6, 9);
  // slot allocations:
  // stmt_idx: 0
  // stmts: 1
  // return__7: 2
  // def_count: 3
  // generated_code: 4
  // all_actions: 5
  // code: 6
  frame->slots[2] /* return__7 */ = create_continuation();
  frame->slots[3] = myself->closure.frame->slots[30]; /* def_count */
  frame->slots[4] = myself->closure.frame->slots[26]; /* generated_code */
  frame->slots[5] = myself->closure.frame->slots[8]; /* all_actions */
  define__sim2c__actions(undefined);
  define__sim2c__delayed_code(undefined);
  define__sim2c__suffix(create_future());
  define__sim2c__index(undefined);
  frame->slots[6] /* code */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 617: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 618: %%sim2c::delayed_code ""
  set__sim2c__delayed_code(empty_string);
  // 619: ... stmt_idx+def_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_idx */;
  arguments->slots[1] = frame->slots[3] /* def_count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_468;
}
static void cont__7_468(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 619: %sim2c::suffix string("__" stmt_idx+def_count)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_469;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_470;
}
static void cont__7_470(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__suffix(), arguments->slots[0]);
  // 620: %%sim2c::index 0
  set__sim2c__index(number__0);
  // 621: ... : for_each stmts: (stmt) generate_statement stmt
  frame->slots[7] /* temp__1 */ = create_closure(entry__7_471, 0);
  // 621: collect_output $code: for_each stmts: (stmt) generate_statement stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__7_473;
}
static void entry__7_472(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 621: ... generate_statement stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt */;
  result_count = frame->caller_result_count;
  myself = get__generate_statement();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_471(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmts: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stmts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 621: ... for_each stmts: (stmt) generate_statement stmt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmts */;
  arguments->slots[1] = func__7_472;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_473(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* code */, arguments->slots[0]);
  // 622: ... delayed_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_474;
}
static void cont__7_474(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 622: ... delayed_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_475;
}
static void cont__7_475(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 622: if delayed_code != "": write_to_delayed_statements delayed_code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__7_476;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_477;
}
static void entry__7_476(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 622: ... write_to_delayed_statements delayed_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  result_count = frame->caller_result_count;
  myself = get__write_to_delayed_statements();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_477(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 623: ... : append &generated_code code
  frame->slots[7] /* temp__1 */ = create_closure(entry__7_478, 0);
  // 623: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_480;
}
static void entry__7_478(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_code: 0
  // code: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* generated_code */
  frame->slots[1] = myself->closure.frame->slots[6]; /* code */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 623: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_479;
}
static void cont__7_479(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_code */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_480(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 624: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_481;
}
static void cont__7_481(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[2] /* return__7 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__7_482(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 625: ... :
  // 626:   %%sim2c::actions empty_list
  // 627:   collect_output $code:
  // 628:     if
  // 629:       is_main:
  // 630:         write "
  // 631:             terminate(0); // should never be reached
  // 632:           }
  // 633:       :
  // 634:         write "
  // ...
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_483, 0);
  // 625: do:
  // 626:   %%sim2c::actions empty_list
  // 627:   collect_output $code:
  // 628:     if
  // 629:       is_main:
  // 630:         write "
  // 631:             terminate(0); // should never be reached
  // 632:           }
  // 633:       :
  // 634:         write "
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__7_495;
}
static void entry__7_483(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // return__8: 0
  // is_main: 1
  // generated_code: 2
  // all_actions: 3
  // code: 4
  frame->slots[0] /* return__8 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[2] = myself->closure.frame->slots[26]; /* generated_code */
  frame->slots[3] = myself->closure.frame->slots[8]; /* all_actions */
  define__sim2c__actions(undefined);
  frame->slots[4] /* code */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 626: %%sim2c::actions empty_list
  set__sim2c__actions(get__empty_list());
  // 627: ... :
  // 628:   if
  // 629:     is_main:
  // 630:       write "
  // 631:           terminate(0); // should never be reached
  // 632:         }
  // 633:     :
  // 634:       write "
  // 635:           frame = frame->caller_frame;
  // 636:           func = frame->cont;
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__7_484, 0);
  // 627: collect_output $code:
  // 628:   if
  // 629:     is_main:
  // 630:       write "
  // 631:           terminate(0); // should never be reached
  // 632:         }
  // 633:     :
  // 634:       write "
  // 635:           frame = frame->caller_frame;
  // 636:           func = frame->cont;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__7_490;
}
static void entry__7_484(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 628: if
  // 629:   is_main:
  // 630:     write "
  // 631:         terminate(0); // should never be reached
  // 632:       }
  // 633:   :
  // 634:     write "
  // 635:         frame = frame->caller_frame;
  // 636:         func = frame->cont;
  // 637:         frame->cont = invalid_continuation;
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  arguments->slots[1] = func__7_485;
  arguments->slots[2] = func__7_487;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_489;
}
static void entry__7_485(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 630: write "
  // 631:     terminate(0); // should never be reached
  // 632:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_486;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_487(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 634: write "
  // 635:     frame = frame->caller_frame;
  // 636:     func = frame->cont;
  // 637:     frame->cont = invalid_continuation;
  // 638:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_488;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_489(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 639: end_continuation
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__end_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_490(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* code */, arguments->slots[0]);
  // 640: ... : append &generated_code code
  frame->slots[5] /* temp__1 */ = create_closure(entry__7_491, 0);
  // 640: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_493;
}
static void entry__7_491(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_code: 0
  // code: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* generated_code */
  frame->slots[1] = myself->closure.frame->slots[4]; /* code */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 640: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_492;
}
static void cont__7_492(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_code */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_493(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 641: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__7_494;
}
static void cont__7_494(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__8 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__7_495(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 642: for_each all_actions: (stmt_actions) for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* all_actions */;
  arguments->slots[1] = func__7_496;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_498;
}
static void entry__7_497(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // action: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 642: ... action
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* action */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_496(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt_actions: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 642: ... for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_actions */;
  arguments->slots[1] = func__7_497;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_498(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 643: for_each required_modules: (name _info) writeln "/// require @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = func__7_499;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_502;
}
static void entry__7_499(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 643: ... "/// require @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_500;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_501;
}
static void cont__7_501(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 643: ... writeln "/// require @(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_502(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 644: for_each linked_libraries: (name) writeln "/// link @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__linked_libraries();
  arguments->slots[1] = func__7_503;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_506;
}
static void entry__7_503(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 644: ... "/// link @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_504;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_505;
}
static void cont__7_505(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 644: ... writeln "/// link @(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_506(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 645: for_each dependent_data: (filemask) writeln "/// data @(filemask)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__dependent_data();
  arguments->slots[1] = func__7_507;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_510;
}
static void entry__7_507(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filemask: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 645: ... "/// data @(filemask)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_508;
  arguments->slots[1] = frame->slots[0] /* filemask */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_509;
}
static void cont__7_509(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 645: ... writeln "/// data @(filemask)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_510(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 646: ... required_modules.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__7_511;
}
static void cont__7_511(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 646: unless required_modules.is_empty writeln
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  arguments->slots[1] = get__writeln();
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__7_512;
}
static void cont__7_512(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 647: if use_inline_c:
  // 648:   !included_files("stdint.h") true
  // 649:   !included_files("stdlib.h") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__use_inline_c();
  arguments->slots[1] = func__7_513;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_518;
}
static void entry__7_513(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 648: !included_files("stdint.h") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 648: !included_files("stdint.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_514;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_515;
}
static void cont__7_515(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__included_files(arguments->slots[0]);
  // 649: !included_files("stdlib.h") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 649: !included_files("stdlib.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_516;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_517;
}
static void cont__7_517(void) {
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
static void cont__7_518(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 650: for_each included_files: (name) writeln "#include <@(name)>"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__included_files();
  arguments->slots[1] = func__7_519;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_523;
}
static void entry__7_519(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 650: ... "#include <@(name)>"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_520;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_521;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_522;
}
static void cont__7_522(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 650: ... writeln "#include <@(name)>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_523(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 651: write "
  // 652:   /**********************
  // 653:   D E C L A R A T I O N S
  // 654:   **********************/
  // 655:   
  // 656:   #ifndef IMPORT
  // 657:     #define IMPORT extern
  // 658:   #endif
  // 659:   
  // 660:   #ifndef EXPORT
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_524;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_525;
}
static void cont__7_525(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 669: ... included_files("stdint.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_526;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_527;
}
static void cont__7_527(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 669: unless included_files("stdint.h"):
  // 670:   write "
  // 671:     typedef __INT8_TYPE__ int8_t;
  // 672:     typedef __INT16_TYPE__ int16_t;
  // 673:     typedef __INT32_TYPE__ int32_t;
  // 674:     typedef __INT64_TYPE__ int64_t;
  // 675:     typedef __INTPTR_TYPE__ intptr_t;
  // 676:     
  // 677:     #ifdef __UINT8_TYPE__
  // 678:       typedef __UINT8_TYPE__ uint8_t;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  arguments->slots[1] = func__7_528;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__7_530;
}
static void entry__7_528(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 670: write "
  // 671:   typedef __INT8_TYPE__ int8_t;
  // 672:   typedef __INT16_TYPE__ int16_t;
  // 673:   typedef __INT32_TYPE__ int32_t;
  // 674:   typedef __INT64_TYPE__ int64_t;
  // 675:   typedef __INTPTR_TYPE__ intptr_t;
  // 676:   
  // 677:   #ifdef __UINT8_TYPE__
  // 678:     typedef __UINT8_TYPE__ uint8_t;
  // 679:   #else
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_529;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_530(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 706: ... included_files("stdlib.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_531;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_532;
}
static void cont__7_532(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__2 */ = arguments->slots[0];
  // 706: ... included_files("stdlib.h") || included_files("stddef.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__2 */;
  arguments->slots[1] = func__7_533;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__7_536;
}
static void entry__7_533(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 706: ... included_files("stddef.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_534;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__7_535;
}
static void cont__7_535(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 706: ... included_files("stddef.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_536(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 706: unless included_files("stdlib.h") || included_files("stddef.h"):
  // 707:   write "
  // 708:     typedef __SIZE_TYPE__ size_t;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  arguments->slots[1] = func__7_537;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__7_539;
}
static void entry__7_537(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 707: write "
  // 708:   typedef __SIZE_TYPE__ size_t;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_538;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_539(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 709: write "
  // 710:   // INSERT HERE //
  // 711:   
  // 712:   #if UINTPTR_MAX == 0xffffffffffffffff
  // 713:     #define FIRST_INVALID_ADDRESS 0xc000000000000000UL
  // 714:     #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)
  // 715:   #else
  // 716:     #define FIRST_INVALID_ADDRESS 0xc0000000
  // 717:     #define SAMPLE_POINTER ((void *)0x12345678)
  // 718:   #endif
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_540;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_541;
}
static void cont__7_541(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 750: from_to 1 max_temp_idx: (idx) writeln "static NODE *temp__@(idx);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = ((CELL *)frame->slots[12])->contents /* max_temp_idx */;
  arguments->slots[2] = func__7_542;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__7_546;
}
static void entry__7_542(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // idx: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 750: ... "static NODE *temp__@(idx);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_543;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = string__7_544;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_545;
}
static void cont__7_545(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 750: ... writeln "static NODE *temp__@(idx);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_546(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 751: for_each needed_names: (name info)
  // 752:   if variable_kind_of(info) == POLYMORPHIC:
  // 753:     writeln "static int poly_idx__@(name);"
  // 754:   writeln "static NODE_GETTER get__@(name);"
  // 755:   if variable_kind_of(info) == STATIC_SINGLE:
  // 756:     writeln "static NODE_GETTER get_value_or_future__@(name);"
  // 757:   case variable_kind_of(info) STATIC_MULTI, DYNAMIC_MULTI:
  // 758:     writeln "static NODE_SETTER set__@(name);"
  // 759:   case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 760:     writeln "static NODE_SETTER define__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__needed_names();
  arguments->slots[1] = func__7_547;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_579;
}
static void entry__7_575(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: ... "static NODE_SETTER define__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_576;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_577;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_578;
}
static void cont__7_578(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 760: writeln "static NODE_SETTER define__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_547(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 752: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_548;
}
static void cont__7_548(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 752: ... variable_kind_of(info) == POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_549;
}
static void cont__7_549(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 752: ... :
  // 753:   writeln "static int poly_idx__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_550, 0);
  // 752: if variable_kind_of(info) == POLYMORPHIC:
  // 753:   writeln "static int poly_idx__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_554;
}
static void entry__7_550(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 753: ... "static int poly_idx__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_551;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_552;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_553;
}
static void cont__7_553(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 753: writeln "static int poly_idx__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_554(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 754: ... "static NODE_GETTER get__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_555;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_556;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_557;
}
static void cont__7_557(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 754: writeln "static NODE_GETTER get__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__7_558;
}
static void cont__7_558(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 755: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_559;
}
static void cont__7_559(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 755: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_560;
}
static void cont__7_560(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 755: ... :
  // 756:   writeln "static NODE_GETTER get_value_or_future__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_561, 0);
  // 755: if variable_kind_of(info) == STATIC_SINGLE:
  // 756:   writeln "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_565;
}
static void entry__7_561(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 756: ... "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_562;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_563;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_564;
}
static void cont__7_564(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 756: writeln "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_565(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 757: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_566;
}
static void cont__7_566(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 757: ... STATIC_MULTI, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_MULTI();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__7_567;
}
static void cont__7_567(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 757: ... :
  // 758:   writeln "static NODE_SETTER set__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_568, 0);
  // 757: case variable_kind_of(info) STATIC_MULTI, DYNAMIC_MULTI:
  // 758:   writeln "static NODE_SETTER set__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__7_572;
}
static void entry__7_568(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 758: ... "static NODE_SETTER set__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_569;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_570;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_571;
}
static void cont__7_571(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 758: writeln "static NODE_SETTER set__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_572(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 759: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_573;
}
static void cont__7_573(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 759: ... DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__DYNAMIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__7_574;
}
static void cont__7_574(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 759: ... :
  // 760:   writeln "static NODE_SETTER define__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_575, 0);
  // 759: case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 760:   writeln "static NODE_SETTER define__@(name);"
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
static void cont__7_579(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 761: write "
  // 762:   static struct {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_580;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_581;
}
static void cont__7_581(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 763: write generated_top_level_variable_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[16])->contents /* generated_top_level_variable_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_582;
}
static void cont__7_582(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 764: write generated_global_variable_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[17])->contents /* generated_global_variable_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_583;
}
static void cont__7_583(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 765: write "
  // 766:   } var;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_584;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_585;
}
static void cont__7_585(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 767: write "
  // 768:   static const char *var_names[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_586;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_587;
}
static void cont__7_587(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 769: ... generated_top_level_variable_names != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[15])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_588;
}
static void cont__7_588(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__2 */ = arguments->slots[0];
  // 769: ... generated_top_level_variable_names != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_589;
}
static void cont__7_589(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 769: ... :
  // 770:   writeln range(generated_top_level_variable_names 1 -3)
  frame->slots[34] /* temp__3 */ = create_closure(entry__7_590, 0);
  // 769: if generated_top_level_variable_names != "":
  // 770:   writeln range(generated_top_level_variable_names 1 -3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  arguments->slots[1] = frame->slots[34] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_593;
}
static void entry__7_590(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // generated_top_level_variable_names: 0
  frame->slots[0] = myself->closure.frame->slots[15]; /* generated_top_level_variable_names */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 770: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_591;
}
static void cont__7_591(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 770: ... range(generated_top_level_variable_names 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_592;
}
static void cont__7_592(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 770: writeln range(generated_top_level_variable_names 1 -3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_593(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 771: write "};@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_594;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_595;
}
static void cont__7_595(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 772: write generated_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[14])->contents /* generated_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_596;
}
static void cont__7_596(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 780: if
  // 781:   is_main:
  // 782:     writeln "static void main_entry(void);"
  // 783:   :
  // 784:     writeln "void run__@(module_name)(void);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_597;
  arguments->slots[2] = func__7_599;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_603;
}
static void entry__7_597(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 782: writeln "static void main_entry(void);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_598;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_599(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 784: ... "void run__@(module_name)(void);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_600;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_601;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_602;
}
static void cont__7_602(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 784: writeln "void run__@(module_name)(void);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_603(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 785: write "
  // 786:   
  // 787:   static CONTINUATION_INFO continuation_info[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_604;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_605;
}
static void cont__7_605(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 788: append &generated_continuation_table generated_delayed_continuation_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* generated_continuation_table */;
  arguments->slots[1] = ((CELL *)frame->slots[19])->contents /* generated_delayed_continuation_table */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__7_606;
}
static void cont__7_606(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[18])->contents /* generated_continuation_table */ = arguments->slots[0];
  // 789: ... generated_continuation_table != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* generated_continuation_table */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_607;
}
static void cont__7_607(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__2 */ = arguments->slots[0];
  // 789: ... generated_continuation_table != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_608;
}
static void cont__7_608(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 789: ... :
  // 790:   writeln range(generated_continuation_table 1 -3)
  frame->slots[34] /* temp__3 */ = create_closure(entry__7_609, 0);
  // 789: if generated_continuation_table != "":
  // 790:   writeln range(generated_continuation_table 1 -3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  arguments->slots[1] = frame->slots[34] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_612;
}
static void entry__7_609(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // generated_continuation_table: 0
  frame->slots[0] = myself->closure.frame->slots[18]; /* generated_continuation_table */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 790: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_610;
}
static void cont__7_610(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 790: ... range(generated_continuation_table 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_continuation_table */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_611;
}
static void cont__7_611(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 790: writeln range(generated_continuation_table 1 -3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_612(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 791: write "
  // 792:   };
  // 793:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_613;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_614;
}
static void cont__7_614(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 794: write "
  // 795:   union NODE {
  // 796:     struct {
  // 797:       FUNC type;
  // 798:       ATTRIBUTES *attributes;
  // 799:     };
  // 800:     CONTINUATION continuation;
  // 801:     CLOSURE closure;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_615;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_616;
}
static void cont__7_616(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 802: if use_inline_c:
  // 803:   for_each defined_nodes: (name _node)
  // 804:     write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__use_inline_c();
  arguments->slots[1] = func__7_617;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_624;
}
static void entry__7_618(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // node: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 804: ... name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__7_619;
}
static void cont__7_619(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 804: ... "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__7_620;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_621;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__7_622;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_623;
}
static void cont__7_623(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 804: write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_617(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 803: for_each defined_nodes: (name _node)
  // 804:   write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_nodes();
  arguments->slots[1] = func__7_618;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_624(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 805: write "};@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_625;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_626;
}
static void cont__7_626(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 806: write generated_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[20])->contents /* generated_functions */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_627;
}
static void cont__7_627(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 807: for_each used_literals: (name _literal) write "static NODE *@(name);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[29])->contents /* used_literals */;
  arguments->slots[1] = func__7_628;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_632;
}
static void entry__7_628(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 807: ... "static NODE *@(name);@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_629;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_630;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_631;
}
static void cont__7_631(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 807: ... write "static NODE *@(name);@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_632(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 808: write "
  // 809:   
  // 810:   static const char *used_namespaces[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_633;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_634;
}
static void cont__7_634(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 811: for_each used_namespaces: (name) write "  @quot;@(name)@quot;,@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  arguments->slots[1] = func__7_635;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_639;
}
static void entry__7_635(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 811: ... "  @quot;@(name)@quot;,@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_636;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_637;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_638;
}
static void cont__7_638(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 811: ... write "  @quot;@(name)@quot;,@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_639(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 812: ... "
  // 813:     NULL
  // 814:   };
  // 815:   
  // 816:   static MODULE_INFO module_info = {
  // 817:     NULL,
  // 818:     "@(module_name)",
  // 819:     continuation_info,
  // 820:     sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  // 821:     (NODE **)&var,
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_640;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_641;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_642;
}
static void cont__7_642(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 812: write "
  // 813:     NULL
  // 814:   };
  // 815:   
  // 816:   static MODULE_INFO module_info = {
  // 817:     NULL,
  // 818:     "@(module_name)",
  // 819:     continuation_info,
  // 820:     sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  // 821:     (NODE **)&var,
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_643;
}
static void cont__7_643(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 826: $depth count_occurrences(module_name "__")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__7_644;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__7_645;
}
static void cont__7_645(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[31] /* depth */, arguments->slots[0]);
  // 828: ... : ($filename)
  // 829:   truncate_until &filename '/' -(depth+1)
  // 830:   write "
  // 831:     DEBUG_FILENAME("@(filename)@quot;)@
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_646, 1);
  // 827: for_each
  // 828:   filenames: ($filename)
  // 829:     truncate_until &filename '/' -(depth+1)
  // 830:     write "
  // 831:       DEBUG_FILENAME("@(filename)@quot;)@
  // 832:   :
  // 833:     write ", "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filenames */;
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  arguments->slots[2] = func__7_653;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_655;
}
static void entry__7_646(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // filename: 0
  // depth: 1
  frame->slots[1] = myself->closure.frame->slots[31]; /* depth */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* filename */ = create_cell_with_contents(arguments->slots[0]);
  // 829: ... depth+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* depth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_647;
}
static void cont__7_647(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 829: ... depth+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_648;
}
static void cont__7_648(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 829: truncate_until &filename '/' -(depth+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__7_649;
}
static void cont__7_649(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 830: ... "
  // 831:   DEBUG_FILENAME("@(filename)@quot;)@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_650;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[2] = string__7_651;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_652;
}
static void cont__7_652(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 830: write "
  // 831:   DEBUG_FILENAME("@(filename)@quot;)@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_653(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 833: write ", "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_654;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_655(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 834: write "
  // 835:   }
  // 836:   };
  // 837:   
  // 838:   /******
  // 839:   C O D E
  // 840:   ******/
  // 841:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_656;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_657;
}
static void cont__7_657(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 842: ... : (name _info)
  // 843:   $fname mangle_filename(name)
  // 844:   write "
  // 845:     IMPORT void collect__@(fname)(void);
  // 846:     IMPORT void phase_1__@(fname)(void);
  // 847:     IMPORT void phase_2__@(fname)(void);
  // 848:     IMPORT void phase_3__@(fname)(void);
  // 849:     IMPORT void phase_4__@(fname)(void);
  // 850:     IMPORT void phase_5__@(fname)(void);
  // 851:     IMPORT void run__@(fname)(void);
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_658, 2);
  // 842: for_each required_modules: (name _info)
  // 843:   $fname mangle_filename(name)
  // 844:   write "
  // 845:     IMPORT void collect__@(fname)(void);
  // 846:     IMPORT void phase_1__@(fname)(void);
  // 847:     IMPORT void phase_2__@(fname)(void);
  // 848:     IMPORT void phase_3__@(fname)(void);
  // 849:     IMPORT void phase_4__@(fname)(void);
  // 850:     IMPORT void phase_5__@(fname)(void);
  // 851:     IMPORT void run__@(fname)(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_669;
}
static void entry__7_658(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // info: 1
  // mangle_filename: 2
  // fname: 3
  frame->slots[2] = myself->closure.frame->slots[3]; /* mangle_filename */
  frame->slots[3] /* fname */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 843: $fname mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_659;
}
static void cont__7_659(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* fname */, arguments->slots[0]);
  // 844: ... "
  // 845:   IMPORT void collect__@(fname)(void);
  // 846:   IMPORT void phase_1__@(fname)(void);
  // 847:   IMPORT void phase_2__@(fname)(void);
  // 848:   IMPORT void phase_3__@(fname)(void);
  // 849:   IMPORT void phase_4__@(fname)(void);
  // 850:   IMPORT void phase_5__@(fname)(void);
  // 851:   IMPORT void run__@(fname)(void);
  argument_count = 15;
  arguments = node_p;
  arguments->slots[0] = string__7_660;
  arguments->slots[1] = frame->slots[3] /* fname */;
  arguments->slots[2] = string__7_661;
  arguments->slots[3] = frame->slots[3] /* fname */;
  arguments->slots[4] = string__7_662;
  arguments->slots[5] = frame->slots[3] /* fname */;
  arguments->slots[6] = string__7_663;
  arguments->slots[7] = frame->slots[3] /* fname */;
  arguments->slots[8] = string__7_664;
  arguments->slots[9] = frame->slots[3] /* fname */;
  arguments->slots[10] = string__7_665;
  arguments->slots[11] = frame->slots[3] /* fname */;
  arguments->slots[12] = string__7_666;
  arguments->slots[13] = frame->slots[3] /* fname */;
  arguments->slots[14] = string__7_667;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_668;
}
static void cont__7_668(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 844: write "
  // 845:   IMPORT void collect__@(fname)(void);
  // 846:   IMPORT void phase_1__@(fname)(void);
  // 847:   IMPORT void phase_2__@(fname)(void);
  // 848:   IMPORT void phase_3__@(fname)(void);
  // 849:   IMPORT void phase_4__@(fname)(void);
  // 850:   IMPORT void phase_5__@(fname)(void);
  // 851:   IMPORT void run__@(fname)(void);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_669(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 852: write generated_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[26])->contents /* generated_code */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_670;
}
static void cont__7_670(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 853: write delayed_statements
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[28])->contents /* delayed_statements */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_671;
}
static void cont__7_671(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 854: ... "
  // 855:   EXPORT void collect__@(module_name)(void) {
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_672;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_673;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_674;
}
static void cont__7_674(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 854: write "
  // 855:   EXPORT void collect__@(module_name)(void) {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_675;
}
static void cont__7_675(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 856: from_to 1 max_temp_idx: (idx)
  // 857:   writeln "  temp__@(idx) = collect_node(temp__@(idx));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = ((CELL *)frame->slots[12])->contents /* max_temp_idx */;
  arguments->slots[2] = func__7_676;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__7_681;
}
static void entry__7_676(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // idx: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 857: ... "  temp__@(idx) = collect_node(temp__@(idx));"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__7_677;
  arguments->slots[1] = frame->slots[0] /* idx */;
  arguments->slots[2] = string__7_678;
  arguments->slots[3] = frame->slots[0] /* idx */;
  arguments->slots[4] = string__7_679;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_680;
}
static void cont__7_680(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 857: writeln "  temp__@(idx) = collect_node(temp__@(idx));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_681(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 858: write generated_collections
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[27])->contents /* generated_collections */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_682;
}
static void cont__7_682(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 859: for_each used_literals: (name _literal)
  // 860:   writeln "  @(name) = collect_node(@(name));"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[29])->contents /* used_literals */;
  arguments->slots[1] = func__7_683;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_688;
}
static void entry__7_683(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 860: ... "  @(name) = collect_node(@(name));"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__7_684;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_685;
  arguments->slots[3] = frame->slots[0] /* name */;
  arguments->slots[4] = string__7_686;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_687;
}
static void cont__7_687(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 860: writeln "  @(name) = collect_node(@(name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_688(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 861: write "}@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_689;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_690;
}
static void cont__7_690(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 862: if
  // 863:   is_main:
  // 864:     write "
  // 865:       
  // 866:       int main(int argc, char **argv) {
  // 867:         main_argc = argc;
  // 868:         main_argv = argv;
  // 869:         initialize_runtime();
  // 870:       
  // 871:         // initialization phase 1
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_691;
  arguments->slots[2] = func__7_693;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_697;
}
static void entry__7_691(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 864: write "
  // 865:   
  // 866:   int main(int argc, char **argv) {
  // 867:     main_argc = argc;
  // 868:     main_argv = argv;
  // 869:     initialize_runtime();
  // 870:   
  // 871:     // initialization phase 1
  // 872:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_692;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_693(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 874: ... "
  // 875:   
  // 876:   static int already_run_phase_1 = false;
  // 877:   
  // 878:   EXPORT void phase_1__@(module_name)(void) {
  // 879:     if (already_run_phase_1) return;
  // 880:     already_run_phase_1 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_694;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_695;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_696;
}
static void cont__7_696(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 874: write "
  // 875:   
  // 876:   static int already_run_phase_1 = false;
  // 877:   
  // 878:   EXPORT void phase_1__@(module_name)(void) {
  // 879:     if (already_run_phase_1) return;
  // 880:     already_run_phase_1 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_697(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 881: ... : (name _info)
  // 882:   $mangled_name mangle_filename(name)
  // 883:   writeln "  phase_1__@(mangled_name)();"
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_698, 2);
  // 881: for_each required_modules: (name _info)
  // 882:   $mangled_name mangle_filename(name)
  // 883:   writeln "  phase_1__@(mangled_name)();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_703;
}
static void entry__7_698(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // info: 1
  // mangle_filename: 2
  // mangled_name: 3
  frame->slots[2] = myself->closure.frame->slots[3]; /* mangle_filename */
  frame->slots[3] /* mangled_name */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 882: $mangled_name mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_699;
}
static void cont__7_699(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mangled_name */, arguments->slots[0]);
  // 883: ... "  phase_1__@(mangled_name)();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_700;
  arguments->slots[1] = frame->slots[3] /* mangled_name */;
  arguments->slots[2] = string__7_701;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_702;
}
static void cont__7_702(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 883: writeln "  phase_1__@(mangled_name)();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_703(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 884: write "
  // 885:   @
  // 886:     register_module_info(&module_info);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_704;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_705;
}
static void cont__7_705(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 887: write generated_phase_1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[21])->contents /* generated_phase_1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_706;
}
static void cont__7_706(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 888: if
  // 889:   is_main:
  // 890:     write "
  // 891:       @
  // 892:       
  // 893:         // initialization phase 2
  // 894:       
  // 895:         resolve_symbols();
  // 896:   :
  // 897:     write "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_707;
  arguments->slots[2] = func__7_709;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_713;
}
static void entry__7_707(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 890: write "
  // 891:   @
  // 892:   
  // 893:     // initialization phase 2
  // 894:   
  // 895:     resolve_symbols();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_708;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_709(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 897: ... "
  // 898:   }
  // 899:   
  // 900:   static int already_run_phase_2 = false;
  // 901:   
  // 902:   EXPORT void phase_2__@(module_name)(void) {
  // 903:     if (already_run_phase_2) return;
  // 904:     already_run_phase_2 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_710;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_711;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_712;
}
static void cont__7_712(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 897: write "
  // 898:   }
  // 899:   
  // 900:   static int already_run_phase_2 = false;
  // 901:   
  // 902:   EXPORT void phase_2__@(module_name)(void) {
  // 903:     if (already_run_phase_2) return;
  // 904:     already_run_phase_2 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_713(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 905: ... : (name _info)
  // 906:   writeln "  phase_2__@(mangle_filename(name))();"
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_714, 2);
  // 905: for_each required_modules: (name _info)
  // 906:   writeln "  phase_2__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_719;
}
static void entry__7_714(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // info: 1
  // mangle_filename: 2
  frame->slots[2] = myself->closure.frame->slots[3]; /* mangle_filename */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 906: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_715;
}
static void cont__7_715(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 906: ... "  phase_2__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_716;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__7_717;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_718;
}
static void cont__7_718(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 906: writeln "  phase_2__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_719(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 907: ... "
  // 908:   @
  // 909:     set_module("@(module_name)");
  // 910:     set_used_namespaces(used_namespaces);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_720;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_721;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_722;
}
static void cont__7_722(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 907: write "
  // 908:   @
  // 909:     set_module("@(module_name)");
  // 910:     set_used_namespaces(used_namespaces);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_723;
}
static void cont__7_723(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 911: for_each used_literals: (name _literal)
  // 912:   # ATTENTION: only necessary if used in an attribute definition!
  // 913:   
  // 914:   writeln "  @(name) = create_future();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[29])->contents /* used_literals */;
  arguments->slots[1] = func__7_724;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_728;
}
static void entry__7_724(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 914: ... "  @(name) = create_future();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_725;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_726;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_727;
}
static void cont__7_727(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 914: writeln "  @(name) = create_future();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_728(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 915: write generated_phase_2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[22])->contents /* generated_phase_2 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_729;
}
static void cont__7_729(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 916: if
  // 917:   is_main:
  // 918:     write "
  // 919:       @
  // 920:       
  // 921:         // initialization phase 3
  // 922:       
  // 923:         initialize_phase_3();
  // 924:   :
  // 925:     write "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_730;
  arguments->slots[2] = func__7_732;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_736;
}
static void entry__7_730(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 918: write "
  // 919:   @
  // 920:   
  // 921:     // initialization phase 3
  // 922:   
  // 923:     initialize_phase_3();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_731;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_732(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 925: ... "
  // 926:   }
  // 927:   
  // 928:   static int already_run_phase_3 = false;
  // 929:   
  // 930:   EXPORT void phase_3__@(module_name)(void) {
  // 931:     if (already_run_phase_3) return;
  // 932:     already_run_phase_3 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_733;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_734;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_735;
}
static void cont__7_735(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 925: write "
  // 926:   }
  // 927:   
  // 928:   static int already_run_phase_3 = false;
  // 929:   
  // 930:   EXPORT void phase_3__@(module_name)(void) {
  // 931:     if (already_run_phase_3) return;
  // 932:     already_run_phase_3 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_736(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 933: ... : (name _info)
  // 934:   writeln "  phase_3__@(mangle_filename(name))();"
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_737, 2);
  // 933: for_each required_modules: (name _info)
  // 934:   writeln "  phase_3__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_742;
}
static void entry__7_737(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // info: 1
  // mangle_filename: 2
  frame->slots[2] = myself->closure.frame->slots[3]; /* mangle_filename */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 934: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_738;
}
static void cont__7_738(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 934: ... "  phase_3__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_739;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__7_740;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_741;
}
static void cont__7_741(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 934: writeln "  phase_3__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_742(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 935: ... "
  // 936:   @
  // 937:     set_module("@(module_name)");
  // 938:     set_used_namespaces(used_namespaces);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_743;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_744;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_745;
}
static void cont__7_745(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 935: write "
  // 936:   @
  // 937:     set_module("@(module_name)");
  // 938:     set_used_namespaces(used_namespaces);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_746;
}
static void cont__7_746(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 939: for_each needed_names: (name info)
  // 940:   unless global_names(name).is_defined:
  // 941:     $namespace
  // 942:       if
  // 943:         name .contains. "__"
  // 944:         -> string('@quot;' name .before. "__" '@quot;')
  // 945:         -> "NULL"
  // 946:     
  // 947:     $basename name .truncate_until. "__"
  // 948:     case
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__needed_names();
  arguments->slots[1] = func__7_747;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_799;
}
static void entry__7_763(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // namespace: 0
  // basename: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[3]; /* basename */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 951: ... "
  // 952:   @
  // 953:     use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 954:   &get__@(name), &poly_idx__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_764;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_765;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_766;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_767;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_768;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_769;
}
static void cont__7_769(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 951: write "
  // 952:   @
  // 953:     use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 954:   &get__@(name), &poly_idx__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_770(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // namespace: 0
  // basename: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[3]; /* basename */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 956: ... "
  // 957:   @
  // 958:     use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 959:   &get_value_or_future__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_771;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_772;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_773;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_774;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_775;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_776;
}
static void cont__7_776(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 956: write "
  // 957:   @
  // 958:     use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 959:   &get_value_or_future__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_777(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // namespace: 0
  // basename: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[3]; /* basename */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 961: ... "
  // 962:   @
  // 963:     use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 964:   &set__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_778;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_779;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_780;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_781;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_782;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_783;
}
static void cont__7_783(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 961: write "
  // 962:   @
  // 963:     use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 964:   &set__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_784(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // namespace: 0
  // basename: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[3]; /* basename */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 966: ... "
  // 967:   @
  // 968:     use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 969:   &get__@(name), &define__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__7_785;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_786;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_787;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_788;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_789;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_790;
}
static void cont__7_790(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 966: write "
  // 967:   @
  // 968:     use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 969:   &get__@(name), &define__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_791(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // namespace: 0
  // basename: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[3]; /* basename */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 971: ... "
  // 972:   @
  // 973:     use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 974:   &get__@(name), &set__@(name), &define__@(name));
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__7_792;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__7_793;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__7_794;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__7_795;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__7_796;
  arguments->slots[9] = frame->slots[2] /* name */;
  arguments->slots[10] = string__7_797;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_798;
}
static void cont__7_798(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 971: write "
  // 972:   @
  // 973:     use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 974:   &get__@(name), &set__@(name), &define__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_750(void) {
  allocate_initialized_frame_gc(2, 10);
  // slot allocations:
  // name: 0
  // info: 1
  // namespace: 2
  // basename: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] /* namespace */ = create_future();
  frame->slots[3] /* basename */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 943: name .contains. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__7_751;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__7_752;
}
static void cont__7_752(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 944: -> string('@quot;' name .before. "__" '@quot;')
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_753, 0);
  // 941: $namespace
  // 942:   if
  // 943:     name .contains. "__"
  // 944:     -> string('@quot;' name .before. "__" '@quot;')
  // 945:     -> "NULL"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = func__7_757;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_759;
}
static void entry__7_753(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 944: ... name .before. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__7_754;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__7_755;
}
static void cont__7_755(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 944: ... string('@quot;' name .before. "__" '@quot;')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__7_756;
}
static void cont__7_756(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 944: -> string('@quot;' name .before. "__" '@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_757(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 945: -> "NULL"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_758;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_759(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 947: $basename name .truncate_until. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__7_760;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__7_761;
}
static void cont__7_761(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* basename */, arguments->slots[0]);
  // 949: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_762;
}
static void cont__7_762(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 950: ... :
  // 951:   write "
  // 952:     @
  // 953:       use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 954:     &get__@(name), &poly_idx__@(name));
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_763, 0);
  // 955: ... :
  // 956:   write "
  // 957:     @
  // 958:       use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 959:     &get_value_or_future__@(name));
  frame->slots[6] /* temp__3 */ = create_closure(entry__7_770, 0);
  // 960: ... :
  // 961:   write "
  // 962:     @
  // 963:       use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 964:     &set__@(name));
  frame->slots[7] /* temp__4 */ = create_closure(entry__7_777, 0);
  // 965: ... :
  // 966:   write "
  // 967:     @
  // 968:       use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 969:     &get__@(name), &define__@(name));
  frame->slots[8] /* temp__5 */ = create_closure(entry__7_784, 0);
  // 970: ... :
  // 971:   write "
  // 972:     @
  // 973:       use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 974:     &get__@(name), &set__@(name), &define__@(name));
  frame->slots[9] /* temp__6 */ = create_closure(entry__7_791, 0);
  // 948: case
  // 949:   variable_kind_of(info)
  // 950:   POLYMORPHIC:
  // 951:     write "
  // 952:       @
  // 953:         use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 954:       &get__@(name), &poly_idx__@(name));
  // 955:   STATIC_SINGLE:
  // 956:     write "
  // 957:       @
  // ...
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__POLYMORPHIC();
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  arguments->slots[3] = get__STATIC_SINGLE();
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  arguments->slots[5] = get__STATIC_MULTI();
  arguments->slots[6] = frame->slots[7] /* temp__4 */;
  arguments->slots[7] = get__DYNAMIC_SINGLE();
  arguments->slots[8] = frame->slots[8] /* temp__5 */;
  arguments->slots[9] = get__DYNAMIC_MULTI();
  arguments->slots[10] = frame->slots[9] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_747(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 940: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__7_748;
}
static void cont__7_748(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 940: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_749;
}
static void cont__7_749(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 940: ... :
  // 941:   $namespace
  // 942:     if
  // 943:       name .contains. "__"
  // 944:       -> string('@quot;' name .before. "__" '@quot;')
  // 945:       -> "NULL"
  // 946:   
  // 947:   $basename name .truncate_until. "__"
  // 948:   case
  // 949:     variable_kind_of(info)
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_750, 0);
  // 940: unless global_names(name).is_defined:
  // 941:   $namespace
  // 942:     if
  // 943:       name .contains. "__"
  // 944:       -> string('@quot;' name .before. "__" '@quot;')
  // 945:       -> "NULL"
  // 946:   
  // 947:   $basename name .truncate_until. "__"
  // 948:   case
  // 949:     variable_kind_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_799(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 975: write generated_phase_3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[23])->contents /* generated_phase_3 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_800;
}
static void cont__7_800(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 976: if is_main:
  // 977:   write "
  // 978:     @
  // 979:       resolve_attributes();
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_801;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_803;
}
static void entry__7_801(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 977: write "
  // 978:   @
  // 979:     resolve_attributes();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_802;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_803(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 980: if
  // 981:   is_main:
  // 982:     write "
  // 983:       
  // 984:         // initialization phase 4
  // 985:       @;
  // 986:   :
  // 987:     write "
  // 988:       }
  // 989:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_804;
  arguments->slots[2] = func__7_806;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_810;
}
static void entry__7_804(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 982: write "
  // 983:   
  // 984:     // initialization phase 4
  // 985:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_805;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_806(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 987: ... "
  // 988:   }
  // 989:   
  // 990:   static int already_run_phase_4 = false;
  // 991:   
  // 992:   EXPORT void phase_4__@(module_name)(void) {
  // 993:     if (already_run_phase_4) return;
  // 994:     already_run_phase_4 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_807;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_808;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_809;
}
static void cont__7_809(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 987: write "
  // 988:   }
  // 989:   
  // 990:   static int already_run_phase_4 = false;
  // 991:   
  // 992:   EXPORT void phase_4__@(module_name)(void) {
  // 993:     if (already_run_phase_4) return;
  // 994:     already_run_phase_4 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_810(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 995: ... : (name _info)
  // 996:   writeln "  phase_4__@(mangle_filename(name))();"
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_811, 2);
  // 995: for_each required_modules: (name _info)
  // 996:   writeln "  phase_4__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_816;
}
static void entry__7_811(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // info: 1
  // mangle_filename: 2
  frame->slots[2] = myself->closure.frame->slots[3]; /* mangle_filename */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 996: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_812;
}
static void cont__7_812(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 996: ... "  phase_4__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_813;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__7_814;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_815;
}
static void cont__7_815(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 996: writeln "  phase_4__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_816(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  //  997: for_each used_literals: (name literal)
  //  998:   write "  assign_value(&@(name), "
  //  999:   cond
  // 1000:     -> literal.is_a_numeric_literal:
  // 1001:       $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1002:       if
  // 1003:         not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1004:           write "
  // 1005:             from_double(@(value)));
  // 1006:         :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[29])->contents /* used_literals */;
  arguments->slots[1] = func__7_817;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_867;
}
static void entry__7_861(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1019: ... node::value_of(literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__7_862;
}
static void cont__7_862(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1019: ... node::value_of(literal).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__7_863;
}
static void cont__7_863(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1019: ... "from_uchar32(@(node::value_of(literal).to_integer)));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_864;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__7_865;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_866;
}
static void cont__7_866(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1019: writeln "from_uchar32(@(node::value_of(literal).to_integer)));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_851(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1013: ... "
  // 1014:   from_uint64(@(int_val)ULL));
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_852;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  arguments->slots[2] = string__7_853;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_854;
}
static void cont__7_854(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1013: write "
  // 1014:   from_uint64(@(int_val)ULL));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_844(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1010: ... "
  // 1011:   from_uint32(@(int_val)U));
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_845;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  arguments->slots[2] = string__7_846;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_847;
}
static void cont__7_847(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1010: write "
  // 1011:   from_uint32(@(int_val)U));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_841(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1009: ... int_val <= 0xffffffff
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0xffffffff;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_842;
}
static void cont__7_842(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1009: ... int_val <= 0xffffffff
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_843;
}
static void cont__7_843(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1009: ... :
  // 1010:   write "
  // 1011:     from_uint32(@(int_val)U));
  frame->slots[3] /* temp__3 */ = create_closure(entry__7_844, 0);
  // 1009: -> int_val <= 0xffffffff:
  // 1010:   write "
  // 1011:     from_uint32(@(int_val)U));
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_848(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1012: ... int_val <= 0xffffffffffffffff
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0xffffffffffffffff;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_849;
}
static void cont__7_849(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1012: ... int_val <= 0xffffffffffffffff
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_850;
}
static void cont__7_850(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1012: ... :
  // 1013:   write "
  // 1014:     from_uint64(@(int_val)ULL));
  frame->slots[3] /* temp__3 */ = create_closure(entry__7_851, 0);
  // 1012: -> int_val <= 0xffffffffffffffff:
  // 1013:   write "
  // 1014:     from_uint64(@(int_val)ULL));
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_855(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1016: ... "
  // 1017:   from_digit_string("@(value)"));
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_856;
  arguments->slots[1] = frame->slots[0] /* value */;
  arguments->slots[2] = string__7_857;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_858;
}
static void cont__7_858(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1016: write "
  // 1017:   from_digit_string("@(value)"));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_835(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1004: ... "
  // 1005:   from_double(@(value)));
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_836;
  arguments->slots[1] = frame->slots[0] /* value */;
  arguments->slots[2] = string__7_837;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_838;
}
static void cont__7_838(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1004: write "
  // 1005:   from_double(@(value)));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_839(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // value: 0
  // int_val: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  frame->slots[1] /* int_val */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1007: $int_val value.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__7_840;
}
static void cont__7_840(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* int_val */, arguments->slots[0]);
  // 1009: -> int_val <= 0xffffffff:
  // 1010:   write "
  // 1011:     from_uint32(@(int_val)U));
  frame->slots[2] /* temp__1 */ = create_closure(entry__7_841, 0);
  // 1012: -> int_val <= 0xffffffffffffffff:
  // 1013:   write "
  // 1014:     from_uint64(@(int_val)ULL));
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_848, 0);
  // 1015: :
  // 1016:   write "
  // 1017:     from_digit_string("@(value)"));
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_855, 0);
  // 1008: cond
  // 1009:   -> int_val <= 0xffffffff:
  // 1010:     write "
  // 1011:       from_uint32(@(int_val)U));
  // 1012:   -> int_val <= 0xffffffffffffffff:
  // 1013:     write "
  // 1014:       from_uint64(@(int_val)ULL));
  // 1015:   :
  // 1016:     write "
  // 1017:       from_digit_string("@(value)"));
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_824(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // literal: 0
  // value: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* literal */
  frame->slots[1] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1001: ... node::value_of(literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__7_825;
}
static void cont__7_825(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1001: ... '@apos;' = ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__39;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__7_826;
}
static void cont__7_826(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1001: $value replace_all(node::value_of(literal) '@apos;' = "")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__7_827;
}
static void cont__7_827(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* value */, arguments->slots[0]);
  // 1003: ... value .has_prefix. "0x"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = string__7_828;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__7_829;
}
static void cont__7_829(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1003: not(value .has_prefix. "0x")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__7_830;
}
static void cont__7_830(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1003: ... value .contains. alt('.' 'e' 'E')
  frame->slots[5] /* temp__4 */ = create_closure(entry__7_831, 0);
  // 1003: not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_834;
}
static void entry__7_831(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1003: ... alt('.' 'e' 'E')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = character__101;
  arguments->slots[2] = character__69;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__7_832;
}
static void cont__7_832(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1003: ... value .contains. alt('.' 'e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__7_833;
}
static void cont__7_833(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1003: ... value .contains. alt('.' 'e' 'E')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_834(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1003: ... :
  // 1004:   write "
  // 1005:     from_double(@(value)));
  frame->slots[6] /* temp__5 */ = create_closure(entry__7_835, 0);
  // 1006: :
  // 1007:   $int_val value.to_integer
  // 1008:   cond
  // 1009:     -> int_val <= 0xffffffff:
  // 1010:       write "
  // 1011:         from_uint32(@(int_val)U));
  // 1012:     -> int_val <= 0xffffffffffffffff:
  // 1013:       write "
  // 1014:         from_uint64(@(int_val)ULL));
  // 1015:     :
  // ...
  frame->slots[7] /* temp__6 */ = create_closure(entry__7_839, 0);
  // 1002: if
  // 1003:   not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1004:     write "
  // 1005:       from_double(@(value)));
  // 1006:   :
  // 1007:     $int_val value.to_integer
  // 1008:     cond
  // 1009:       -> int_val <= 0xffffffff:
  // 1010:         write "
  // 1011:           from_uint32(@(int_val)U));
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  arguments->slots[2] = frame->slots[7] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_822(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1000: ... literal.is_a_numeric_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__is_a_numeric_literal();
  func = myself->type;
  frame->cont = cont__7_823;
}
static void cont__7_823(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1000: ... :
  // 1001:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1002:   if
  // 1003:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1004:       write "
  // 1005:         from_double(@(value)));
  // 1006:     :
  // 1007:       $int_val value.to_integer
  // 1008:       cond
  // 1009:         -> int_val <= 0xffffffff:
  // ...
  frame->slots[2] /* temp__2 */ = create_closure(entry__7_824, 0);
  // 1000: -> literal.is_a_numeric_literal:
  // 1001:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1002:   if
  // 1003:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1004:       write "
  // 1005:         from_double(@(value)));
  // 1006:     :
  // 1007:       $int_val value.to_integer
  // 1008:       cond
  // 1009:         -> int_val <= 0xffffffff:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_859(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1018: ... literal.is_a_character_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__is_a_character_literal();
  func = myself->type;
  frame->cont = cont__7_860;
}
static void cont__7_860(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1018: ... :
  // 1019:   writeln "from_uchar32(@(node::value_of(literal).to_integer)));"
  frame->slots[2] /* temp__2 */ = create_closure(entry__7_861, 0);
  // 1018: -> literal.is_a_character_literal:
  // 1019:   writeln "from_uchar32(@(node::value_of(literal).to_integer)));"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_817(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 998: ... "  assign_value(&@(name), "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_818;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_819;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_820;
}
static void cont__7_820(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 998: write "  assign_value(&@(name), "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_821;
}
static void cont__7_821(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1000: -> literal.is_a_numeric_literal:
  // 1001:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1002:   if
  // 1003:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1004:       write "
  // 1005:         from_double(@(value)));
  // 1006:     :
  // 1007:       $int_val value.to_integer
  // 1008:       cond
  // 1009:         -> int_val <= 0xffffffff:
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__7_822, 0);
  // 1018: -> literal.is_a_character_literal:
  // 1019:   writeln "from_uchar32(@(node::value_of(literal).to_integer)));"
  frame->slots[3] /* temp__2 */ = create_closure(entry__7_859, 0);
  //  999: cond
  // 1000:   -> literal.is_a_numeric_literal:
  // 1001:     $value replace_all(node::value_of(literal) '@apos;' = "")
  // 1002:     if
  // 1003:       not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 1004:         write "
  // 1005:           from_double(@(value)));
  // 1006:       :
  // 1007:         $int_val value.to_integer
  // 1008:         cond
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_867(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1020: write generated_phase_4
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[24])->contents /* generated_phase_4 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_868;
}
static void cont__7_868(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1021: if
  // 1022:   is_main:
  // 1023:     write "
  // 1024:         initialize_function_attributes();
  // 1025:       
  // 1026:         // initialization phase 5
  // 1027:       @;
  // 1028:   :
  // 1029:     write "
  // 1030:       }
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_869;
  arguments->slots[2] = func__7_871;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_875;
}
static void entry__7_869(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1023: write "
  // 1024:     initialize_function_attributes();
  // 1025:   
  // 1026:     // initialization phase 5
  // 1027:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_870;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_871(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1029: ... "
  // 1030:   }
  // 1031:   
  // 1032:   static int already_run_phase_5 = false;
  // 1033:   
  // 1034:   EXPORT void phase_5__@(module_name)(void) {
  // 1035:     if (already_run_phase_5) return;
  // 1036:     already_run_phase_5 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_872;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_873;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_874;
}
static void cont__7_874(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1029: write "
  // 1030:   }
  // 1031:   
  // 1032:   static int already_run_phase_5 = false;
  // 1033:   
  // 1034:   EXPORT void phase_5__@(module_name)(void) {
  // 1035:     if (already_run_phase_5) return;
  // 1036:     already_run_phase_5 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_875(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1037: ... : (name _info)
  // 1038:   writeln "  phase_5__@(mangle_filename(name))();"
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_876, 2);
  // 1037: for_each required_modules: (name _info)
  // 1038:   writeln "  phase_5__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__7_881;
}
static void entry__7_876(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // info: 1
  // mangle_filename: 2
  frame->slots[2] = myself->closure.frame->slots[3]; /* mangle_filename */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1038: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__7_877;
}
static void cont__7_877(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1038: ... "  phase_5__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_878;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__7_879;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_880;
}
static void cont__7_880(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1038: writeln "  phase_5__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_881(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1039: write generated_phase_5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[25])->contents /* generated_phase_5 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_882;
}
static void cont__7_882(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1040: ... "  register_collector(collect__@(module_name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_883;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__7_884;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_885;
}
static void cont__7_885(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__1 */ = arguments->slots[0];
  // 1040: writeln "  register_collector(collect__@(module_name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[32] /* temp__1 */;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__7_886;
}
static void cont__7_886(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1041: if is_main:
  // 1042:   write "
  // 1043:     @
  // 1044:       execute(main_entry);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__7_887;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_889;
}
static void entry__7_887(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1042: write "
  // 1043:   @
  // 1044:     execute(main_entry);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_888;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_889(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1045: write "}@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_890;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_891;
}
static void cont__7_891(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1046: ... : write_timing_info "generating" filenames(1)
  frame->slots[32] /* temp__1 */ = create_closure(entry__7_892, 0);
  // 1046: if do_time_passes: write_timing_info "generating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[32] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_895;
}
static void entry__7_892(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1046: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__7_893;
}
static void cont__7_893(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1046: ... write_timing_info "generating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_894;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_895(void) {
  myself = frame->slots[2] /* return__9 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__sim2c(void) {
  temp__1 = collect_node(temp__1);
  temp__2 = collect_node(temp__2);
  temp__3 = collect_node(temp__3);
  temp__4 = collect_node(temp__4);
  temp__5 = collect_node(temp__5);
  temp__6 = collect_node(temp__6);
  temp__7 = collect_node(temp__7);
  var.sim2c__print_source = collect_node(var.sim2c__print_source);
  string__1_5 = collect_node(string__1_5);
  func__1_4 = collect_node(func__1_4);
  string__1_7 = collect_node(string__1_7);
  func__1_6 = collect_node(func__1_6);
  string__1_9 = collect_node(string__1_9);
  func__1_8 = collect_node(func__1_8);
  func__1_2 = collect_node(func__1_2);
  func__1_1 = collect_node(func__1_1);
  var.sim2c__eprint_source = collect_node(var.sim2c__eprint_source);
  string__2_5 = collect_node(string__2_5);
  func__2_4 = collect_node(func__2_4);
  string__2_7 = collect_node(string__2_7);
  func__2_6 = collect_node(func__2_6);
  string__2_9 = collect_node(string__2_9);
  func__2_8 = collect_node(func__2_8);
  func__2_2 = collect_node(func__2_2);
  func__2_1 = collect_node(func__2_1);
  var.sim2c__privileged_polymorphic_functions = collect_node(var.sim2c__privileged_polymorphic_functions);
  var.sim2c__generate_dispatcher_function = collect_node(var.sim2c__generate_dispatcher_function);
  string__4_2 = collect_node(string__4_2);
  string__4_3 = collect_node(string__4_3);
  string__4_6 = collect_node(string__4_6);
  string__4_7 = collect_node(string__4_7);
  string__4_13 = collect_node(string__4_13);
  string__4_14 = collect_node(string__4_14);
  string__4_15 = collect_node(string__4_15);
  string__4_18 = collect_node(string__4_18);
  string__4_19 = collect_node(string__4_19);
  string__4_22 = collect_node(string__4_22);
  string__4_23 = collect_node(string__4_23);
  func__4_1 = collect_node(func__4_1);
  var._demangled = collect_node(var._demangled);
  string__5_2 = collect_node(string__5_2);
  string__5_3 = collect_node(string__5_3);
  func__5_1 = collect_node(func__5_1);
  var.sim2c__update_info = collect_node(var.sim2c__update_info);
  string__6_11 = collect_node(string__6_11);
  string__6_12 = collect_node(string__6_12);
  string__6_22 = collect_node(string__6_22);
  string__6_23 = collect_node(string__6_23);
  string__6_29 = collect_node(string__6_29);
  string__6_30 = collect_node(string__6_30);
  string__6_37 = collect_node(string__6_37);
  string__6_38 = collect_node(string__6_38);
  string__6_44 = collect_node(string__6_44);
  string__6_45 = collect_node(string__6_45);
  string__6_49 = collect_node(string__6_49);
  string__6_50 = collect_node(string__6_50);
  string__6_56 = collect_node(string__6_56);
  string__6_57 = collect_node(string__6_57);
  string__6_63 = collect_node(string__6_63);
  string__6_64 = collect_node(string__6_64);
  func__6_1 = collect_node(func__6_1);
  var.sim2c__sim2c = collect_node(var.sim2c__sim2c);
  string__7_3 = collect_node(string__7_3);
  string__7_6 = collect_node(string__7_6);
  string__7_10 = collect_node(string__7_10);
  string__7_19 = collect_node(string__7_19);
  func__7_2 = collect_node(func__7_2);
  string__7_23 = collect_node(string__7_23);
  string__7_26 = collect_node(string__7_26);
  string__7_28 = collect_node(string__7_28);
  func__7_22 = collect_node(func__7_22);
  string__7_48 = collect_node(string__7_48);
  string__7_50 = collect_node(string__7_50);
  string__7_58 = collect_node(string__7_58);
  func__7_57 = collect_node(func__7_57);
  string__7_61 = collect_node(string__7_61);
  string__7_62 = collect_node(string__7_62);
  string__7_66 = collect_node(string__7_66);
  string__7_71 = collect_node(string__7_71);
  func__7_70 = collect_node(func__7_70);
  string__7_77 = collect_node(string__7_77);
  func__7_76 = collect_node(func__7_76);
  string__7_84 = collect_node(string__7_84);
  func__7_83 = collect_node(func__7_83);
  string__7_86 = collect_node(string__7_86);
  string__7_93 = collect_node(string__7_93);
  func__7_95 = collect_node(func__7_95);
  string__7_99 = collect_node(string__7_99);
  string__7_126 = collect_node(string__7_126);
  string__7_132 = collect_node(string__7_132);
  func__7_136 = collect_node(func__7_136);
  string__7_141 = collect_node(string__7_141);
  string__7_150 = collect_node(string__7_150);
  func__7_152 = collect_node(func__7_152);
  func__7_153 = collect_node(func__7_153);
  string__7_159 = collect_node(string__7_159);
  string__7_161 = collect_node(string__7_161);
  func__7_158 = collect_node(func__7_158);
  string__7_164 = collect_node(string__7_164);
  string__7_168 = collect_node(string__7_168);
  func__7_167 = collect_node(func__7_167);
  string__7_171 = collect_node(string__7_171);
  string__7_195 = collect_node(string__7_195);
  string__7_196 = collect_node(string__7_196);
  string__7_197 = collect_node(string__7_197);
  string__7_206 = collect_node(string__7_206);
  string__7_207 = collect_node(string__7_207);
  string__7_208 = collect_node(string__7_208);
  string__7_209 = collect_node(string__7_209);
  string__7_218 = collect_node(string__7_218);
  string__7_219 = collect_node(string__7_219);
  string__7_220 = collect_node(string__7_220);
  string__7_221 = collect_node(string__7_221);
  string__7_222 = collect_node(string__7_222);
  string__7_234 = collect_node(string__7_234);
  string__7_235 = collect_node(string__7_235);
  string__7_245 = collect_node(string__7_245);
  string__7_246 = collect_node(string__7_246);
  string__7_247 = collect_node(string__7_247);
  string__7_248 = collect_node(string__7_248);
  string__7_262 = collect_node(string__7_262);
  func__7_265 = collect_node(func__7_265);
  func__7_285 = collect_node(func__7_285);
  func__7_284 = collect_node(func__7_284);
  string__7_289 = collect_node(string__7_289);
  string__7_298 = collect_node(string__7_298);
  string__7_300 = collect_node(string__7_300);
  func__7_293 = collect_node(func__7_293);
  func__7_292 = collect_node(func__7_292);
  func__7_302 = collect_node(func__7_302);
  string__7_310 = collect_node(string__7_310);
  string__7_388 = collect_node(string__7_388);
  string__7_393 = collect_node(string__7_393);
  string__7_396 = collect_node(string__7_396);
  func__7_399 = collect_node(func__7_399);
  func__7_426 = collect_node(func__7_426);
  string__7_433 = collect_node(string__7_433);
  string__7_438 = collect_node(string__7_438);
  func__7_437 = collect_node(func__7_437);
  string__7_440 = collect_node(string__7_440);
  string__7_441 = collect_node(string__7_441);
  string__7_444 = collect_node(string__7_444);
  string__7_445 = collect_node(string__7_445);
  func__7_439 = collect_node(func__7_439);
  string__7_452 = collect_node(string__7_452);
  string__7_453 = collect_node(string__7_453);
  string__7_454 = collect_node(string__7_454);
  string__7_458 = collect_node(string__7_458);
  string__7_469 = collect_node(string__7_469);
  func__7_472 = collect_node(func__7_472);
  func__7_476 = collect_node(func__7_476);
  string__7_486 = collect_node(string__7_486);
  func__7_485 = collect_node(func__7_485);
  string__7_488 = collect_node(string__7_488);
  func__7_487 = collect_node(func__7_487);
  func__7_497 = collect_node(func__7_497);
  func__7_496 = collect_node(func__7_496);
  string__7_500 = collect_node(string__7_500);
  func__7_499 = collect_node(func__7_499);
  string__7_504 = collect_node(string__7_504);
  func__7_503 = collect_node(func__7_503);
  string__7_508 = collect_node(string__7_508);
  func__7_507 = collect_node(func__7_507);
  string__7_514 = collect_node(string__7_514);
  string__7_516 = collect_node(string__7_516);
  func__7_513 = collect_node(func__7_513);
  string__7_520 = collect_node(string__7_520);
  string__7_521 = collect_node(string__7_521);
  func__7_519 = collect_node(func__7_519);
  string__7_524 = collect_node(string__7_524);
  string__7_526 = collect_node(string__7_526);
  string__7_529 = collect_node(string__7_529);
  func__7_528 = collect_node(func__7_528);
  string__7_531 = collect_node(string__7_531);
  string__7_534 = collect_node(string__7_534);
  func__7_533 = collect_node(func__7_533);
  string__7_538 = collect_node(string__7_538);
  func__7_537 = collect_node(func__7_537);
  string__7_540 = collect_node(string__7_540);
  string__7_543 = collect_node(string__7_543);
  string__7_544 = collect_node(string__7_544);
  func__7_542 = collect_node(func__7_542);
  string__7_551 = collect_node(string__7_551);
  string__7_552 = collect_node(string__7_552);
  string__7_555 = collect_node(string__7_555);
  string__7_556 = collect_node(string__7_556);
  string__7_562 = collect_node(string__7_562);
  string__7_563 = collect_node(string__7_563);
  string__7_569 = collect_node(string__7_569);
  string__7_570 = collect_node(string__7_570);
  string__7_576 = collect_node(string__7_576);
  string__7_577 = collect_node(string__7_577);
  func__7_547 = collect_node(func__7_547);
  string__7_580 = collect_node(string__7_580);
  string__7_584 = collect_node(string__7_584);
  string__7_586 = collect_node(string__7_586);
  string__7_594 = collect_node(string__7_594);
  string__7_598 = collect_node(string__7_598);
  func__7_597 = collect_node(func__7_597);
  string__7_600 = collect_node(string__7_600);
  string__7_601 = collect_node(string__7_601);
  func__7_599 = collect_node(func__7_599);
  string__7_604 = collect_node(string__7_604);
  string__7_613 = collect_node(string__7_613);
  string__7_615 = collect_node(string__7_615);
  string__7_620 = collect_node(string__7_620);
  string__7_621 = collect_node(string__7_621);
  string__7_622 = collect_node(string__7_622);
  func__7_618 = collect_node(func__7_618);
  func__7_617 = collect_node(func__7_617);
  string__7_625 = collect_node(string__7_625);
  string__7_629 = collect_node(string__7_629);
  string__7_630 = collect_node(string__7_630);
  func__7_628 = collect_node(func__7_628);
  string__7_633 = collect_node(string__7_633);
  string__7_636 = collect_node(string__7_636);
  string__7_637 = collect_node(string__7_637);
  func__7_635 = collect_node(func__7_635);
  string__7_640 = collect_node(string__7_640);
  string__7_641 = collect_node(string__7_641);
  string__7_644 = collect_node(string__7_644);
  string__7_650 = collect_node(string__7_650);
  string__7_651 = collect_node(string__7_651);
  string__7_654 = collect_node(string__7_654);
  func__7_653 = collect_node(func__7_653);
  string__7_656 = collect_node(string__7_656);
  string__7_660 = collect_node(string__7_660);
  string__7_661 = collect_node(string__7_661);
  string__7_662 = collect_node(string__7_662);
  string__7_663 = collect_node(string__7_663);
  string__7_664 = collect_node(string__7_664);
  string__7_665 = collect_node(string__7_665);
  string__7_666 = collect_node(string__7_666);
  string__7_667 = collect_node(string__7_667);
  string__7_672 = collect_node(string__7_672);
  string__7_673 = collect_node(string__7_673);
  string__7_677 = collect_node(string__7_677);
  string__7_678 = collect_node(string__7_678);
  string__7_679 = collect_node(string__7_679);
  func__7_676 = collect_node(func__7_676);
  string__7_684 = collect_node(string__7_684);
  string__7_685 = collect_node(string__7_685);
  string__7_686 = collect_node(string__7_686);
  func__7_683 = collect_node(func__7_683);
  string__7_689 = collect_node(string__7_689);
  string__7_692 = collect_node(string__7_692);
  func__7_691 = collect_node(func__7_691);
  string__7_694 = collect_node(string__7_694);
  string__7_695 = collect_node(string__7_695);
  func__7_693 = collect_node(func__7_693);
  string__7_700 = collect_node(string__7_700);
  string__7_701 = collect_node(string__7_701);
  string__7_704 = collect_node(string__7_704);
  string__7_708 = collect_node(string__7_708);
  func__7_707 = collect_node(func__7_707);
  string__7_710 = collect_node(string__7_710);
  string__7_711 = collect_node(string__7_711);
  func__7_709 = collect_node(func__7_709);
  string__7_716 = collect_node(string__7_716);
  string__7_717 = collect_node(string__7_717);
  string__7_720 = collect_node(string__7_720);
  string__7_721 = collect_node(string__7_721);
  string__7_725 = collect_node(string__7_725);
  string__7_726 = collect_node(string__7_726);
  func__7_724 = collect_node(func__7_724);
  string__7_731 = collect_node(string__7_731);
  func__7_730 = collect_node(func__7_730);
  string__7_733 = collect_node(string__7_733);
  string__7_734 = collect_node(string__7_734);
  func__7_732 = collect_node(func__7_732);
  string__7_739 = collect_node(string__7_739);
  string__7_740 = collect_node(string__7_740);
  string__7_743 = collect_node(string__7_743);
  string__7_744 = collect_node(string__7_744);
  string__7_751 = collect_node(string__7_751);
  string__7_754 = collect_node(string__7_754);
  string__7_758 = collect_node(string__7_758);
  func__7_757 = collect_node(func__7_757);
  string__7_760 = collect_node(string__7_760);
  string__7_764 = collect_node(string__7_764);
  string__7_765 = collect_node(string__7_765);
  string__7_766 = collect_node(string__7_766);
  string__7_767 = collect_node(string__7_767);
  string__7_768 = collect_node(string__7_768);
  string__7_771 = collect_node(string__7_771);
  string__7_772 = collect_node(string__7_772);
  string__7_773 = collect_node(string__7_773);
  string__7_774 = collect_node(string__7_774);
  string__7_775 = collect_node(string__7_775);
  string__7_778 = collect_node(string__7_778);
  string__7_779 = collect_node(string__7_779);
  string__7_780 = collect_node(string__7_780);
  string__7_781 = collect_node(string__7_781);
  string__7_782 = collect_node(string__7_782);
  string__7_785 = collect_node(string__7_785);
  string__7_786 = collect_node(string__7_786);
  string__7_787 = collect_node(string__7_787);
  string__7_788 = collect_node(string__7_788);
  string__7_789 = collect_node(string__7_789);
  string__7_792 = collect_node(string__7_792);
  string__7_793 = collect_node(string__7_793);
  string__7_794 = collect_node(string__7_794);
  string__7_795 = collect_node(string__7_795);
  string__7_796 = collect_node(string__7_796);
  string__7_797 = collect_node(string__7_797);
  func__7_747 = collect_node(func__7_747);
  string__7_802 = collect_node(string__7_802);
  func__7_801 = collect_node(func__7_801);
  string__7_805 = collect_node(string__7_805);
  func__7_804 = collect_node(func__7_804);
  string__7_807 = collect_node(string__7_807);
  string__7_808 = collect_node(string__7_808);
  func__7_806 = collect_node(func__7_806);
  string__7_813 = collect_node(string__7_813);
  string__7_814 = collect_node(string__7_814);
  string__7_818 = collect_node(string__7_818);
  string__7_819 = collect_node(string__7_819);
  string__7_828 = collect_node(string__7_828);
  string__7_836 = collect_node(string__7_836);
  string__7_837 = collect_node(string__7_837);
  string__7_845 = collect_node(string__7_845);
  string__7_846 = collect_node(string__7_846);
  string__7_852 = collect_node(string__7_852);
  string__7_853 = collect_node(string__7_853);
  string__7_856 = collect_node(string__7_856);
  string__7_857 = collect_node(string__7_857);
  string__7_864 = collect_node(string__7_864);
  string__7_865 = collect_node(string__7_865);
  func__7_817 = collect_node(func__7_817);
  string__7_870 = collect_node(string__7_870);
  func__7_869 = collect_node(func__7_869);
  string__7_872 = collect_node(string__7_872);
  string__7_873 = collect_node(string__7_873);
  func__7_871 = collect_node(func__7_871);
  string__7_878 = collect_node(string__7_878);
  string__7_879 = collect_node(string__7_879);
  string__7_883 = collect_node(string__7_883);
  string__7_884 = collect_node(string__7_884);
  string__7_888 = collect_node(string__7_888);
  func__7_887 = collect_node(func__7_887);
  string__7_890 = collect_node(string__7_890);
  string__7_894 = collect_node(string__7_894);
  func__7_1 = collect_node(func__7_1);
  string__10_1 = collect_node(string__10_1);
  string__10_3 = collect_node(string__10_3);
  string__10_5 = collect_node(string__10_5);
  string__10_7 = collect_node(string__10_7);
  string__10_9 = collect_node(string__10_9);
  string__10_11 = collect_node(string__10_11);
  string__10_13 = collect_node(string__10_13);
  number__6 = collect_node(number__6);
  character__35 = collect_node(character__35);
  number__99 = collect_node(number__99);
  character__47 = collect_node(character__47);
  number__0 = collect_node(number__0);
  number__3 = collect_node(number__3);
  number__4 = collect_node(number__4);
  number__0xffffffffffffffff = collect_node(number__0xffffffffffffffff);
  number__0xffffffff = collect_node(number__0xffffffff);
  character__60 = collect_node(character__60);
  character__34 = collect_node(character__34);
  number__5 = collect_node(number__5);
  character__39 = collect_node(character__39);
  character__32 = collect_node(character__32);
  character__101 = collect_node(character__101);
  number__1 = collect_node(number__1);
  character__69 = collect_node(character__69);
  character__46 = collect_node(character__46);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__sim2c(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__sim2c(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("sim2c");
  set_used_namespaces(used_namespaces);
  number__6 = create_future();
  character__35 = create_future();
  number__99 = create_future();
  character__47 = create_future();
  number__0 = create_future();
  number__3 = create_future();
  number__4 = create_future();
  number__0xffffffffffffffff = create_future();
  number__0xffffffff = create_future();
  character__60 = create_future();
  character__34 = create_future();
  number__5 = create_future();
  character__39 = create_future();
  character__32 = create_future();
  character__101 = create_future();
  number__1 = create_future();
  character__69 = create_future();
  character__46 = create_future();
  number__2 = create_future();
  string__1_5 = from_latin_1_string("<newline>", 9);
  func__1_4 = create_future();
  string__1_7 = from_latin_1_string("<indent_marker>", 15);
  func__1_6 = create_future();
  string__1_9 = from_latin_1_string("<outdent_marker>", 16);
  func__1_8 = create_future();
  func__1_2 = create_future();
  func__1_1 = create_future();
  define_single_assign_static("sim2c", "print_source", get__sim2c__print_source, &var.sim2c__print_source);
  string__2_5 = from_latin_1_string("<newline>", 9);
  func__2_4 = create_future();
  string__2_7 = from_latin_1_string("<indent_marker>", 15);
  func__2_6 = create_future();
  string__2_9 = from_latin_1_string("<outdent_marker>", 16);
  func__2_8 = create_future();
  func__2_2 = create_future();
  func__2_1 = create_future();
  define_single_assign_static("sim2c", "eprint_source", get__sim2c__eprint_source, &var.sim2c__eprint_source);
  define_single_assign_static("sim2c", "privileged_polymorphic_functions", get__sim2c__privileged_polymorphic_functions, &var.sim2c__privileged_polymorphic_functions);
  string__4_2 = from_latin_1_string("static void type__", 18);
  string__4_3 = from_latin_1_string("(void);\012", 8);
  string__4_6 = from_latin_1_string("static void type__", 18);
  string__4_7 = from_latin_1_string("(void) {\012", 9);
  string__4_13 = from_latin_1_string("  myself = get_attribute(arguments->slots[0], poly_idx__", 56);
  string__4_14 = from_latin_1_string("); // ", 6);
  string__4_15 = from_latin_1_string("\012", 1);
  string__4_18 = from_latin_1_string("  myself = get_attribute(arguments->slots[0], poly_idx__", 56);
  string__4_19 = from_latin_1_string(");\012", 3);
  string__4_22 = from_latin_1_string("  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {\012    if (argument_count != 1) {\012      if (argument_count != 2) invalid_arguments_error();\012      NODE *attr = arguments->slots[1];\012      NODE *temp = clone_object_and_attributes(arguments->slots[0]);\012      update_start_p = node_p;\012      set_attribute_value(temp->attributes, poly_idx__", 328);
  string__4_23 = from_latin_1_string(", attr);\012      arguments = node_p;\012      argument_count = 1;\012      arguments->slots[0] = temp;\012    } else {\012      arguments = node_p;\012      arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);\012    }\012    func = frame->cont;\012    frame->cont = invalid_continuation;\012  } else {\012    func = myself->type;\012  }\012}\012", 308);
  func__4_1 = create_future();
  define_single_assign_static("sim2c", "generate_dispatcher_function", get__sim2c__generate_dispatcher_function, &var.sim2c__generate_dispatcher_function);
  string__5_2 = from_latin_1_string("__", 2);
  string__5_3 = from_latin_1_string("::", 2);
  func__5_1 = create_future();
  string__6_11 = from_latin_1_string("The symbol \042", 12);
  string__6_12 = from_latin_1_string("\042 is used as a polymorphic function and cannot be used otherwise!", 65);
  string__6_22 = from_latin_1_string("The symbol \042", 12);
  string__6_23 = from_latin_1_string("\042 is used as a polymorphic function and id assigned to!", 55);
  string__6_29 = from_latin_1_string("The symbol \042", 12);
  string__6_30 = from_latin_1_string("\042 is used as a single-assign dynamic and is assigned to!", 56);
  string__6_37 = from_latin_1_string("The symbol \042", 12);
  string__6_38 = from_latin_1_string("\042 is used as a polymorphic function and as a single-assign dynamic!", 67);
  string__6_44 = from_latin_1_string("The symbol \042", 12);
  string__6_45 = from_latin_1_string("\042 is used as a single-assign dynamic and is assigned to!", 56);
  string__6_49 = from_latin_1_string("The symbol \042", 12);
  string__6_50 = from_latin_1_string("\042 is used as a single-assign dynamic and as a multi-assign dynamic!", 67);
  string__6_56 = from_latin_1_string("The symbol \042", 12);
  string__6_57 = from_latin_1_string("\042 is used as a polymorphic function and as a multi-assign dynamic!", 66);
  string__6_63 = from_latin_1_string("The symbol \042", 12);
  string__6_64 = from_latin_1_string("\042 is used as a single-assign dynamic and as a multi-assign dynamic!", 67);
  func__6_1 = create_future();
  define_single_assign_static("sim2c", "update_info", get__sim2c__update_info, &var.sim2c__update_info);
  string__7_3 = from_latin_1_string("./", 2);
  string__7_6 = from_latin_1_string("__", 2);
  string__7_10 = from_latin_1_string("__", 2);
  string__7_19 = from_latin_1_string("__", 2);
  func__7_2 = create_future();
  string__7_23 = from_latin_1_string("__", 2);
  string__7_26 = from_latin_1_string("__", 2);
  string__7_28 = from_latin_1_string("__", 2);
  func__7_22 = create_future();
  string__7_48 = from_latin_1_string("NODE", 4);
  string__7_50 = from_latin_1_string("SIMPLE_NODE", 11);
  string__7_58 = from_latin_1_string("Source file is not in a valid utf-8-encoding!", 45);
  func__7_57 = create_future();
  string__7_61 = from_latin_1_string("load \042", 6);
  string__7_62 = from_latin_1_string("\042\012", 2);
  string__7_66 = from_latin_1_string("loading", 7);
  string__7_71 = from_latin_1_string("Empty source text!", 18);
  func__7_70 = create_future();
  string__7_77 = from_latin_1_string("Whitespace at start of source text!", 35);
  func__7_76 = create_future();
  string__7_84 = from_latin_1_string("Missing newline at end of source text!", 38);
  func__7_83 = create_future();
  string__7_86 = from_latin_1_string("#!", 2);
  string__7_93 = from_latin_1_string("fragmenting", 11);
  func__7_95 = create_future();
  string__7_99 = from_latin_1_string("tokenizing", 10);
  string__7_126 = from_latin_1_string("parsing", 7);
  string__7_132 = from_latin_1_string("terminate", 9);
  func__7_136 = create_future();
  string__7_141 = from_latin_1_string("expanding", 9);
  string__7_150 = from_latin_1_string("annotating", 10);
  func__7_152 = create_future();
  func__7_153 = create_future();
  string__7_159 = from_latin_1_string("basic/stdlib", 12);
  string__7_161 = from_latin_1_string("system/stdlib", 13);
  func__7_158 = create_future();
  string__7_164 = from_latin_1_string("nothing", 7);
  string__7_168 = from_latin_1_string("std", 3);
  func__7_167 = create_future();
  string__7_171 = from_latin_1_string("nothing", 7);
  string__7_195 = from_latin_1_string("An identifier named \042", 21);
  string__7_196 = from_latin_1_string("::", 2);
  string__7_197 = from_latin_1_string("\042 was already defined", 21);
  string__7_206 = from_latin_1_string("The definition of \042", 19);
  string__7_207 = from_latin_1_string("::", 2);
  string__7_208 = from_latin_1_string("\042 clashes with the already defined identifier \042", 47);
  string__7_209 = from_latin_1_string("\042", 1);
  string__7_218 = from_latin_1_string("The definition of \042", 19);
  string__7_219 = from_latin_1_string("::", 2);
  string__7_220 = from_latin_1_string("\042 clashes with the definition of \042", 34);
  string__7_221 = from_latin_1_string("::", 2);
  string__7_222 = from_latin_1_string("\042 because both namespaces are used", 34);
  string__7_234 = from_latin_1_string("An identifier named \042", 21);
  string__7_235 = from_latin_1_string("\042 was already defined", 21);
  string__7_245 = from_latin_1_string("The definition of \042", 19);
  string__7_246 = from_latin_1_string("\042 clashes with the already defined identifier \042", 47);
  string__7_247 = from_latin_1_string("::", 2);
  string__7_248 = from_latin_1_string("\042", 1);
  string__7_262 = from_latin_1_string("analyzing", 9);
  func__7_265 = create_future();
  func__7_285 = create_future();
  func__7_284 = create_future();
  string__7_289 = from_latin_1_string("simplifying", 11);
  string__7_298 = from_latin_1_string("_define ", 8);
  string__7_300 = from_latin_1_string("_define ", 8);
  func__7_293 = create_future();
  func__7_292 = create_future();
  func__7_302 = create_future();
  string__7_310 = from_latin_1_string("mangling", 8);
  string__7_388 = from_latin_1_string("get__", 5);
  string__7_393 = from_latin_1_string("GENERATE DEFINITIONS", 20);
  string__7_396 = from_latin_1_string("__", 2);
  func__7_399 = create_future();
  func__7_426 = create_future();
  string__7_433 = from_latin_1_string("GENERATE STATEMENTS", 19);
  string__7_438 = from_latin_1_string("main_entry", 10);
  func__7_437 = create_future();
  string__7_440 = from_latin_1_string("  {run__", 8);
  string__7_441 = from_latin_1_string(", NULL, ", 8);
  string__7_444 = from_latin_1_string("static int already_run = false;\012\012EXPORT void run__", 50);
  string__7_445 = from_latin_1_string("(void) {\012  if (already_run) {\012    func = frame->cont;\012    frame->cont = invalid_continuation;\012    return;\012  }\012  already_run = true;\012  allocate_initialized_frame_gc(0, 0);\012", 171);
  func__7_439 = create_future();
  string__7_452 = from_latin_1_string("  func = run__", 14);
  string__7_453 = from_latin_1_string(";\012  frame->cont = cont__run__", 29);
  string__7_454 = from_latin_1_string(";\012}\012", 4);
  string__7_458 = from_latin_1_string("cont__run__", 11);
  string__7_469 = from_latin_1_string("__", 2);
  func__7_472 = create_future();
  func__7_476 = create_future();
  string__7_486 = from_latin_1_string("  terminate(0); // should never be reached\012}\012", 45);
  func__7_485 = create_future();
  string__7_488 = from_latin_1_string("  frame = frame->caller_frame;\012  func = frame->cont;\012  frame->cont = invalid_continuation;\012}\012", 93);
  func__7_487 = create_future();
  func__7_497 = create_future();
  func__7_496 = create_future();
  string__7_500 = from_latin_1_string("/// require ", 12);
  func__7_499 = create_future();
  string__7_504 = from_latin_1_string("/// link ", 9);
  func__7_503 = create_future();
  string__7_508 = from_latin_1_string("/// data ", 9);
  func__7_507 = create_future();
  string__7_514 = from_latin_1_string("stdint.h", 8);
  string__7_516 = from_latin_1_string("stdlib.h", 8);
  func__7_513 = create_future();
  string__7_520 = from_latin_1_string("#include <", 10);
  string__7_521 = from_latin_1_string(">", 1);
  func__7_519 = create_future();
  string__7_524 = from_latin_1_string("/**********************\012D E C L A R A T I O N S\012**********************/\012\012#ifndef IMPORT\012  #define IMPORT extern\012#endif\012\012#ifndef EXPORT\012  #define EXPORT\012#endif\012\012#ifndef NULL\012  #define NULL ((void *)0)\012#endif\012#define false 0\012#define true 1\012", 238);
  string__7_526 = from_latin_1_string("stdint.h", 8);
  string__7_529 = from_latin_1_string("typedef __INT8_TYPE__ int8_t;\012typedef __INT16_TYPE__ int16_t;\012typedef __INT32_TYPE__ int32_t;\012typedef __INT64_TYPE__ int64_t;\012typedef __INTPTR_TYPE__ intptr_t;\012\012#ifdef __UINT8_TYPE__\012  typedef __UINT8_TYPE__ uint8_t;\012#else\012  typedef unsigned __INT8_TYPE__ uint8_t;\012#endif\012\012#ifdef __UINT16_TYPE__\012  typedef __UINT16_TYPE__ uint16_t;\012#else\012  typedef unsigned __INT16_TYPE__ uint16_t;\012#endif\012\012#ifdef __UINT32_TYPE__\012  typedef __UINT32_TYPE__ uint32_t;\012#else\012  typedef unsigned __INT32_TYPE__ uint32_t;\012#endif\012\012#ifdef __UINT64_TYPE__\012  typedef __UINT64_TYPE__ uint64_t;\012#else\012  typedef unsigned __INT64_TYPE__ uint64_t;\012#endif\012\012#ifdef __UINTPTR_TYPE__\012  typedef __UINTPTR_TYPE__ uintptr_t;\012#else\012  typedef unsigned __INTPTR_TYPE__ uintptr_t;\012#endif\012", 745);
  func__7_528 = create_future();
  string__7_531 = from_latin_1_string("stdlib.h", 8);
  string__7_534 = from_latin_1_string("stddef.h", 8);
  func__7_533 = create_future();
  string__7_538 = from_latin_1_string("typedef __SIZE_TYPE__ size_t;\012", 30);
  func__7_537 = create_future();
  string__7_540 = from_latin_1_string("// INSERT HERE //\012\012#if UINTPTR_MAX == 0xffffffffffffffff\012  #define FIRST_INVALID_ADDRESS 0xc000000000000000UL\012  #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)\012#else\012  #define FIRST_INVALID_ADDRESS 0xc0000000\012  #define SAMPLE_POINTER ((void *)0x12345678)\012#endif\012\012#define MAKE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)+1))\012#define RETRIEVE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)-1))\012#define CONTAINS_AN_ATTRIBUTE_VALUE(node) (((uintptr_t)node)&1)\012\012#define ENCODE_ADDRESS(addr) ((void *)(FIRST_INVALID_ADDRESS|(uintptr_t)(addr) >> 2))\012#define DECODE_ADDRESS(addr) ((void *)((uintptr_t)(addr) << 2))\012#define IS_AN_INVALID_ADDRESS(addr) ((void *)(addr) >= (void *)FIRST_INVALID_ADDRESS)\012\012#define IS_COLLECTED(addr) (((void *)(addr)) >= coll_node_buf && ((void *)(addr)) < coll_node_buf_end)\012#define IS_OLD(addr) false\012#define MARK(addr) (((MEMORY_BLOCK *)(addr))-1)->mark = current_mark;\012\012#define ALLOCATION_SIZE(size) (((size)+sizeof(void *)-1)&-sizeof(void *))\012#define TYPEOF(node) (node)->type\012#define SIZEOF(node) (node)->attributes->vtable->size\012\012#ifdef WITHIN_LIBRARY\012  #define DEBUG_FILENAME(filename) filename\012#else\012  #define DEBUG_FILENAME(filename) \042./\042 filename\012#endif\012\012#ifdef __CYGWIN__\012  extern FUNC invalid_continuation;\012#else\012  extern void invalid_continuation(void);\012#endif\012", 1311);
  string__7_543 = from_latin_1_string("static NODE *temp__", 19);
  string__7_544 = from_latin_1_string(";", 1);
  func__7_542 = create_future();
  string__7_551 = from_latin_1_string("static int poly_idx__", 21);
  string__7_552 = from_latin_1_string(";", 1);
  string__7_555 = from_latin_1_string("static NODE_GETTER get__", 24);
  string__7_556 = from_latin_1_string(";", 1);
  string__7_562 = from_latin_1_string("static NODE_GETTER get_value_or_future__", 40);
  string__7_563 = from_latin_1_string(";", 1);
  string__7_569 = from_latin_1_string("static NODE_SETTER set__", 24);
  string__7_570 = from_latin_1_string(";", 1);
  string__7_576 = from_latin_1_string("static NODE_SETTER define__", 27);
  string__7_577 = from_latin_1_string(";", 1);
  func__7_547 = create_future();
  string__7_580 = from_latin_1_string("static struct {\012", 16);
  string__7_584 = from_latin_1_string("} var;\012", 7);
  string__7_586 = from_latin_1_string("static const char *var_names[] = {\012", 35);
  string__7_594 = from_latin_1_string("};\012", 3);
  string__7_598 = from_latin_1_string("static void main_entry(void);", 29);
  func__7_597 = create_future();
  string__7_600 = from_latin_1_string("void run__", 10);
  string__7_601 = from_latin_1_string("(void);", 7);
  func__7_599 = create_future();
  string__7_604 = from_latin_1_string("\012static CONTINUATION_INFO continuation_info[] = {\012", 50);
  string__7_613 = from_latin_1_string("};\012\012", 4);
  string__7_615 = from_latin_1_string("union NODE {\012  struct {\012    FUNC type;\012    ATTRIBUTES *attributes;\012  };\012  CONTINUATION continuation;\012  CLOSURE closure;\012", 120);
  string__7_620 = from_latin_1_string("  ", 2);
  string__7_621 = from_latin_1_string(" ", 1);
  string__7_622 = from_latin_1_string(";\012", 2);
  func__7_618 = create_future();
  func__7_617 = create_future();
  string__7_625 = from_latin_1_string("};\012", 3);
  string__7_629 = from_latin_1_string("static NODE *", 13);
  string__7_630 = from_latin_1_string(";\012", 2);
  func__7_628 = create_future();
  string__7_633 = from_latin_1_string("\012static const char *used_namespaces[] = {\012", 42);
  string__7_636 = from_latin_1_string("  \042", 3);
  string__7_637 = from_latin_1_string("\042,\012", 3);
  func__7_635 = create_future();
  string__7_640 = from_latin_1_string("  NULL\012};\012\012static MODULE_INFO module_info = {\012  NULL,\012  \042", 57);
  string__7_641 = from_latin_1_string("\042,\012  continuation_info,\012  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),\012  (NODE **)&var,\012  var_names,\012  sizeof(var_names)/sizeof(const char *),\012  used_namespaces,\012  {", 173);
  string__7_644 = from_latin_1_string("__", 2);
  string__7_650 = from_latin_1_string("DEBUG_FILENAME(\042", 16);
  string__7_651 = from_latin_1_string("\042)", 2);
  string__7_654 = from_latin_1_string(", ", 2);
  func__7_653 = create_future();
  string__7_656 = from_latin_1_string("}\012};\012\012/******\012C O D E\012******/\012\012", 31);
  string__7_660 = from_latin_1_string("IMPORT void collect__", 21);
  string__7_661 = from_latin_1_string("(void);\012IMPORT void phase_1__", 29);
  string__7_662 = from_latin_1_string("(void);\012IMPORT void phase_2__", 29);
  string__7_663 = from_latin_1_string("(void);\012IMPORT void phase_3__", 29);
  string__7_664 = from_latin_1_string("(void);\012IMPORT void phase_4__", 29);
  string__7_665 = from_latin_1_string("(void);\012IMPORT void phase_5__", 29);
  string__7_666 = from_latin_1_string("(void);\012IMPORT void run__", 25);
  string__7_667 = from_latin_1_string("(void);\012", 8);
  string__7_672 = from_latin_1_string("EXPORT void collect__", 21);
  string__7_673 = from_latin_1_string("(void) {\012", 9);
  string__7_677 = from_latin_1_string("  temp__", 8);
  string__7_678 = from_latin_1_string(" = collect_node(temp__", 22);
  string__7_679 = from_latin_1_string(");", 2);
  func__7_676 = create_future();
  string__7_684 = from_latin_1_string("  ", 2);
  string__7_685 = from_latin_1_string(" = collect_node(", 16);
  string__7_686 = from_latin_1_string(");", 2);
  func__7_683 = create_future();
  string__7_689 = from_latin_1_string("}\012", 2);
  string__7_692 = from_latin_1_string("\012int main(int argc, char **argv) {\012  main_argc = argc;\012  main_argv = argv;\012  initialize_runtime();\012\012  // initialization phase 1\012\012", 129);
  func__7_691 = create_future();
  string__7_694 = from_latin_1_string("\012static int already_run_phase_1 = false;\012\012EXPORT void phase_1__", 63);
  string__7_695 = from_latin_1_string("(void) {\012  if (already_run_phase_1) return;\012  already_run_phase_1 = true;\012", 74);
  func__7_693 = create_future();
  string__7_700 = from_latin_1_string("  phase_1__", 11);
  string__7_701 = from_latin_1_string("();", 3);
  string__7_704 = from_latin_1_string("  register_module_info(&module_info);\012", 38);
  string__7_708 = from_latin_1_string("\012  // initialization phase 2\012\012  resolve_symbols();\012", 51);
  func__7_707 = create_future();
  string__7_710 = from_latin_1_string("}\012\012static int already_run_phase_2 = false;\012\012EXPORT void phase_2__", 65);
  string__7_711 = from_latin_1_string("(void) {\012  if (already_run_phase_2) return;\012  already_run_phase_2 = true;\012", 74);
  func__7_709 = create_future();
  string__7_716 = from_latin_1_string("  phase_2__", 11);
  string__7_717 = from_latin_1_string("();", 3);
  string__7_720 = from_latin_1_string("  set_module(\042", 14);
  string__7_721 = from_latin_1_string("\042);\012  set_used_namespaces(used_namespaces);\012", 44);
  string__7_725 = from_latin_1_string("  ", 2);
  string__7_726 = from_latin_1_string(" = create_future();", 19);
  func__7_724 = create_future();
  string__7_731 = from_latin_1_string("\012  // initialization phase 3\012\012  initialize_phase_3();\012", 54);
  func__7_730 = create_future();
  string__7_733 = from_latin_1_string("}\012\012static int already_run_phase_3 = false;\012\012EXPORT void phase_3__", 65);
  string__7_734 = from_latin_1_string("(void) {\012  if (already_run_phase_3) return;\012  already_run_phase_3 = true;\012", 74);
  func__7_732 = create_future();
  string__7_739 = from_latin_1_string("  phase_3__", 11);
  string__7_740 = from_latin_1_string("();", 3);
  string__7_743 = from_latin_1_string("  set_module(\042", 14);
  string__7_744 = from_latin_1_string("\042);\012  set_used_namespaces(used_namespaces);\012", 44);
  string__7_751 = from_latin_1_string("__", 2);
  string__7_754 = from_latin_1_string("__", 2);
  string__7_758 = from_latin_1_string("NULL", 4);
  func__7_757 = create_future();
  string__7_760 = from_latin_1_string("__", 2);
  string__7_764 = from_latin_1_string("  use_polymorphic_function(", 27);
  string__7_765 = from_latin_1_string(", \042", 3);
  string__7_766 = from_latin_1_string("\042, &get__", 9);
  string__7_767 = from_latin_1_string(", &poly_idx__", 13);
  string__7_768 = from_latin_1_string(");\012", 3);
  string__7_771 = from_latin_1_string("  use_read_only(", 16);
  string__7_772 = from_latin_1_string(", \042", 3);
  string__7_773 = from_latin_1_string("\042, &get__", 9);
  string__7_774 = from_latin_1_string(", &get_value_or_future__", 24);
  string__7_775 = from_latin_1_string(");\012", 3);
  string__7_778 = from_latin_1_string("  use_read_write(", 17);
  string__7_779 = from_latin_1_string(", \042", 3);
  string__7_780 = from_latin_1_string("\042, &get__", 9);
  string__7_781 = from_latin_1_string(", &set__", 8);
  string__7_782 = from_latin_1_string(");\012", 3);
  string__7_785 = from_latin_1_string("  use_single_assign_dynamic(", 28);
  string__7_786 = from_latin_1_string(", \042", 3);
  string__7_787 = from_latin_1_string("\042, &get__", 9);
  string__7_788 = from_latin_1_string(", &define__", 11);
  string__7_789 = from_latin_1_string(");\012", 3);
  string__7_792 = from_latin_1_string("  use_multi_assign_dynamic(", 27);
  string__7_793 = from_latin_1_string(", \042", 3);
  string__7_794 = from_latin_1_string("\042, &get__", 9);
  string__7_795 = from_latin_1_string(", &set__", 8);
  string__7_796 = from_latin_1_string(", &define__", 11);
  string__7_797 = from_latin_1_string(");\012", 3);
  func__7_747 = create_future();
  string__7_802 = from_latin_1_string("  resolve_attributes();\012", 24);
  func__7_801 = create_future();
  string__7_805 = from_latin_1_string("\012  // initialization phase 4\012\012", 30);
  func__7_804 = create_future();
  string__7_807 = from_latin_1_string("}\012\012static int already_run_phase_4 = false;\012\012EXPORT void phase_4__", 65);
  string__7_808 = from_latin_1_string("(void) {\012  if (already_run_phase_4) return;\012  already_run_phase_4 = true;\012", 74);
  func__7_806 = create_future();
  string__7_813 = from_latin_1_string("  phase_4__", 11);
  string__7_814 = from_latin_1_string("();", 3);
  string__7_818 = from_latin_1_string("  assign_value(&", 16);
  string__7_819 = from_latin_1_string(", ", 2);
  string__7_828 = from_latin_1_string("0x", 2);
  string__7_836 = from_latin_1_string("from_double(", 12);
  string__7_837 = from_latin_1_string("));\012", 4);
  string__7_845 = from_latin_1_string("from_uint32(", 12);
  string__7_846 = from_latin_1_string("U));\012", 5);
  string__7_852 = from_latin_1_string("from_uint64(", 12);
  string__7_853 = from_latin_1_string("ULL));\012", 7);
  string__7_856 = from_latin_1_string("from_digit_string(\042", 19);
  string__7_857 = from_latin_1_string("\042));\012", 5);
  string__7_864 = from_latin_1_string("from_uchar32(", 13);
  string__7_865 = from_latin_1_string("));", 3);
  func__7_817 = create_future();
  string__7_870 = from_latin_1_string("  initialize_function_attributes();\012\012  // initialization phase 5\012\012", 66);
  func__7_869 = create_future();
  string__7_872 = from_latin_1_string("}\012\012static int already_run_phase_5 = false;\012\012EXPORT void phase_5__", 65);
  string__7_873 = from_latin_1_string("(void) {\012  if (already_run_phase_5) return;\012  already_run_phase_5 = true;\012", 74);
  func__7_871 = create_future();
  string__7_878 = from_latin_1_string("  phase_5__", 11);
  string__7_879 = from_latin_1_string("();", 3);
  string__7_883 = from_latin_1_string("  register_collector(collect__", 30);
  string__7_884 = from_latin_1_string(");", 2);
  string__7_888 = from_latin_1_string("  execute(main_entry);\012", 23);
  func__7_887 = create_future();
  string__7_890 = from_latin_1_string("}\012", 2);
  string__7_894 = from_latin_1_string("generating", 10);
  func__7_1 = create_future();
  define_single_assign_static("sim2c", "sim2c", get__sim2c__sim2c, &var.sim2c__sim2c);
  string__10_1 = from_latin_1_string("std__if", 7);
  string__10_3 = from_latin_1_string("std__is_defined", 15);
  string__10_5 = from_latin_1_string("std__equal", 10);
  string__10_7 = from_latin_1_string("std__less", 9);
  string__10_9 = from_latin_1_string("std__length_of", 14);
  string__10_11 = from_latin_1_string("std__is_empty", 13);
  string__10_13 = from_latin_1_string("std__unless", 11);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__sim2c(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("sim2c");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "ATTRIBUTE_KIND", &get__ATTRIBUTE_KIND, &get_value_or_future__ATTRIBUTE_KIND);
  use_read_only(NULL, "DYNAMIC_MULTI", &get__DYNAMIC_MULTI, &get_value_or_future__DYNAMIC_MULTI);
  use_read_only(NULL, "DYNAMIC_SINGLE", &get__DYNAMIC_SINGLE, &get_value_or_future__DYNAMIC_SINGLE);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "METHOD_KIND", &get__METHOD_KIND, &get_value_or_future__METHOD_KIND);
  use_read_only(NULL, "POLYMORPHIC", &get__POLYMORPHIC, &get_value_or_future__POLYMORPHIC);
  use_read_only(NULL, "STATIC_MULTI", &get__STATIC_MULTI, &get_value_or_future__STATIC_MULTI);
  use_read_only(NULL, "STATIC_SINGLE", &get__STATIC_SINGLE, &get_value_or_future__STATIC_SINGLE);
  use_read_only(NULL, "SyntaxError", &get__SyntaxError, &get_value_or_future__SyntaxError);
  use_read_write(NULL, "actions", &get__actions, &set__actions);
  use_single_assign_dynamic(NULL, "already_defined_names", &get__already_defined_names, &define__already_defined_names);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_read_only(NULL, "annotate_statement", &get__annotate_statement, &get_value_or_future__annotate_statement);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "attribute_kind_of", &get__attribute_kind_of, &get_value_or_future__attribute_kind_of);
  use_read_only(NULL, "attribute_of", &get__attribute_of, &get_value_or_future__attribute_of);
  use_read_only(NULL, "before", &get__before, &get_value_or_future__before);
  use_read_only(NULL, "begin_continuation", &get__begin_continuation, &get_value_or_future__begin_continuation);
  use_read_only(NULL, "behind", &get__behind, &get_value_or_future__behind);
  use_read_only(NULL, "c_code", &get__c_code, &get_value_or_future__c_code);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "check_definitions", &get__check_definitions, &get_value_or_future__check_definitions);
  use_read_only(NULL, "check_usage", &get__check_usage, &get_value_or_future__check_usage);
  use_read_only(NULL, "collect_output", &get__collect_output, &get_value_or_future__collect_output);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "contains", &get__contains, &get_value_or_future__contains);
  use_read_only(NULL, "count_occurrences", &get__count_occurrences, &get_value_or_future__count_occurrences);
  use_read_only(NULL, "cut_into_fragments", &get__cut_into_fragments, &get_value_or_future__cut_into_fragments);
  use_read_only(NULL, "debug_string", &get__debug_string, &get_value_or_future__debug_string);
  use_read_only(NULL, "define_attribute", &get__define_attribute, &get_value_or_future__define_attribute);
  use_read_only(NULL, "define_c_code", &get__define_c_code, &get_value_or_future__define_c_code);
  use_read_only(NULL, "define_method", &get__define_method, &get_value_or_future__define_method);
  use_read_only(NULL, "define_polymorphic_function", &get__define_polymorphic_function, &get_value_or_future__define_polymorphic_function);
  use_read_only(NULL, "define_type_function", &get__define_type_function, &get_value_or_future__define_type_function);
  use_read_only(NULL, "define_variable", &get__define_variable, &get_value_or_future__define_variable);
  use_read_only(NULL, "defined_nodes", &get__defined_nodes, &get_value_or_future__defined_nodes);
  use_multi_assign_dynamic(NULL, "definitions", &get__definitions, &set__definitions, &define__definitions);
  use_read_only(NULL, "delayed_code", &get__delayed_code, &get_value_or_future__delayed_code);
  use_read_only(NULL, "dependent_data", &get__dependent_data, &get_value_or_future__dependent_data);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "do_check_only", &get__do_check_only, &get_value_or_future__do_check_only);
  use_read_only(NULL, "do_dump_trees", &get__do_dump_trees, &get_value_or_future__do_dump_trees);
  use_read_only(NULL, "do_pretty_print", &get__do_pretty_print, &get_value_or_future__do_pretty_print);
  use_read_only(NULL, "do_print_simplified_source", &get__do_print_simplified_source, &get_value_or_future__do_print_simplified_source);
  use_read_only(NULL, "do_print_warnings", &get__do_print_warnings, &get_value_or_future__do_print_warnings);
  use_read_only(NULL, "do_show_debug_infos", &get__do_show_debug_infos, &get_value_or_future__do_show_debug_infos);
  use_read_only(NULL, "do_time_passes", &get__do_time_passes, &get_value_or_future__do_time_passes);
  use_read_only(NULL, "empty_insert_order_set", &get__empty_insert_order_set, &get_value_or_future__empty_insert_order_set);
  use_read_only(NULL, "empty_insert_order_table", &get__empty_insert_order_table, &get_value_or_future__empty_insert_order_table);
  use_read_only(NULL, "empty_key_order_table", &get__empty_key_order_table, &get_value_or_future__empty_key_order_table);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_set", &get__empty_set, &get_value_or_future__empty_set);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_read_only(NULL, "end_continuation", &get__end_continuation, &get_value_or_future__end_continuation);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "ewriteln", &get__ewriteln, &get_value_or_future__ewriteln);
  use_read_only(NULL, "expand_statement", &get__expand_statement, &get_value_or_future__expand_statement);
  use_read_write(NULL, "exported_names", &get__exported_names, &set__exported_names);
  use_read_only(NULL, "extend_to", &get__extend_to, &get_value_or_future__extend_to);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
  use_read_only(NULL, "from_utf8", &get__from_utf8, &get_value_or_future__from_utf8);
  use_polymorphic_function(NULL, "functor_of", &get__functor_of, &poly_idx__functor_of);
  use_read_only(NULL, "generate_statement", &get__generate_statement, &get_value_or_future__generate_statement);
  use_read_write(NULL, "global_names", &get__global_names, &set__global_names);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "identifier_of", &get__identifier_of, &get_value_or_future__identifier_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_write(NULL, "included_files", &get__included_files, &set__included_files);
  use_read_only(NULL, "indent_marker", &get__indent_marker, &get_value_or_future__indent_marker);
  use_read_only(NULL, "is_a_character_literal", &get__is_a_character_literal, &get_value_or_future__is_a_character_literal);
  use_read_only(NULL, "is_a_key_value_pair", &get__is_a_key_value_pair, &get_value_or_future__is_a_key_value_pair);
  use_read_only(NULL, "is_a_meta_instruction", &get__is_a_meta_instruction, &get_value_or_future__is_a_meta_instruction);
  use_read_only(NULL, "is_a_numeric_literal", &get__is_a_numeric_literal, &get_value_or_future__is_a_numeric_literal);
  use_read_only(NULL, "is_a_polymorphic_function_constant", &get__is_a_polymorphic_function_constant, &get_value_or_future__is_a_polymorphic_function_constant);
  use_read_only(NULL, "is_a_remark", &get__is_a_remark, &get_value_or_future__is_a_remark);
  use_read_only(NULL, "is_a_setter", &get__is_a_setter, &get_value_or_future__is_a_setter);
  use_read_only(NULL, "is_a_static_single_definition", &get__is_a_static_single_definition, &get_value_or_future__is_a_static_single_definition);
  use_read_only(NULL, "is_c_code", &get__is_c_code, &get_value_or_future__is_c_code);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "key_of", &get__key_of, &get_value_or_future__key_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "linked_libraries", &get__linked_libraries, &get_value_or_future__linked_libraries);
  use_read_only(NULL, "load", &get__load, &get_value_or_future__load);
  use_read_only(NULL, "module_name", &get__module_name, &get_value_or_future__module_name);
  use_read_only(NULL, "name_of", &get__name_of, &get_value_or_future__name_of);
  use_read_only(NULL, "namespace_of", &get__namespace_of, &get_value_or_future__namespace_of);
  use_read_write(NULL, "needed_names", &get__needed_names, &set__needed_names);
  use_read_only(NULL, "newline", &get__newline, &get_value_or_future__newline);
  use_read_only(NULL, "next_continuation", &get__next_continuation, &get_value_or_future__next_continuation);
  use_read_only("node", "value_of", &get__node__value_of, &get_value_or_future__node__value_of);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_read_only(NULL, "outdent_marker", &get__outdent_marker, &get_value_or_future__outdent_marker);
  use_read_only(NULL, "parse_meta_instruction", &get__parse_meta_instruction, &get_value_or_future__parse_meta_instruction);
  use_read_only(NULL, "parse_statement", &get__parse_statement, &get_value_or_future__parse_statement);
  use_read_only(NULL, "print_trees", &get__print_trees, &get_value_or_future__print_trees);
  use_read_only(NULL, "privileged_polymorphic_functions", &get__privileged_polymorphic_functions, &get_value_or_future__privileged_polymorphic_functions);
  use_read_only(NULL, "procedure_call", &get__procedure_call, &get_value_or_future__procedure_call);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_read_write(NULL, "required_modules", &get__required_modules, &set__required_modules);
  use_read_only(NULL, "set", &get__set, &get_value_or_future__set);
  use_read_only(NULL, "show_compiler_debug_info", &get__show_compiler_debug_info, &get_value_or_future__show_compiler_debug_info);
  use_multi_assign_dynamic("sim2c", "actions", &get__sim2c__actions, &set__sim2c__actions, &define__sim2c__actions);
  use_multi_assign_dynamic("sim2c", "assigned_names", &get__sim2c__assigned_names, &set__sim2c__assigned_names, &define__sim2c__assigned_names);
  use_multi_assign_dynamic("sim2c", "current_continuation_info", &get__sim2c__current_continuation_info, &set__sim2c__current_continuation_info, &define__sim2c__current_continuation_info);
  use_multi_assign_dynamic("sim2c", "defined_functions", &get__sim2c__defined_functions, &set__sim2c__defined_functions, &define__sim2c__defined_functions);
  use_multi_assign_dynamic("sim2c", "defined_names", &get__sim2c__defined_names, &set__sim2c__defined_names, &define__sim2c__defined_names);
  use_multi_assign_dynamic("sim2c", "defined_namespaces", &get__sim2c__defined_namespaces, &set__sim2c__defined_namespaces, &define__sim2c__defined_namespaces);
  use_multi_assign_dynamic("sim2c", "defined_nodes", &get__sim2c__defined_nodes, &set__sim2c__defined_nodes, &define__sim2c__defined_nodes);
  use_multi_assign_dynamic("sim2c", "defined_structs", &get__sim2c__defined_structs, &set__sim2c__defined_structs, &define__sim2c__defined_structs);
  use_multi_assign_dynamic("sim2c", "delayed_code", &get__sim2c__delayed_code, &set__sim2c__delayed_code, &define__sim2c__delayed_code);
  use_multi_assign_dynamic("sim2c", "dependent_data", &get__sim2c__dependent_data, &set__sim2c__dependent_data, &define__sim2c__dependent_data);
  use_multi_assign_dynamic("sim2c", "enumeration_count", &get__sim2c__enumeration_count, &set__sim2c__enumeration_count, &define__sim2c__enumeration_count);
  use_multi_assign_dynamic("sim2c", "exported_names", &get__sim2c__exported_names, &set__sim2c__exported_names, &define__sim2c__exported_names);
  use_multi_assign_dynamic("sim2c", "global_names", &get__sim2c__global_names, &set__sim2c__global_names, &define__sim2c__global_names);
  use_multi_assign_dynamic("sim2c", "included_files", &get__sim2c__included_files, &set__sim2c__included_files, &define__sim2c__included_files);
  use_multi_assign_dynamic("sim2c", "index", &get__sim2c__index, &set__sim2c__index, &define__sim2c__index);
  use_multi_assign_dynamic("sim2c", "linked_libraries", &get__sim2c__linked_libraries, &set__sim2c__linked_libraries, &define__sim2c__linked_libraries);
  use_multi_assign_dynamic("sim2c", "namespace_mappings", &get__sim2c__namespace_mappings, &set__sim2c__namespace_mappings, &define__sim2c__namespace_mappings);
  use_multi_assign_dynamic("sim2c", "needed_names", &get__sim2c__needed_names, &set__sim2c__needed_names, &define__sim2c__needed_names);
  use_multi_assign_dynamic("sim2c", "required_modules", &get__sim2c__required_modules, &set__sim2c__required_modules, &define__sim2c__required_modules);
  use_single_assign_dynamic("sim2c", "submodule_no", &get__sim2c__submodule_no, &define__sim2c__submodule_no);
  use_single_assign_dynamic("sim2c", "suffix", &get__sim2c__suffix, &define__sim2c__suffix);
  use_multi_assign_dynamic("sim2c", "temp_idx", &get__sim2c__temp_idx, &set__sim2c__temp_idx, &define__sim2c__temp_idx);
  use_single_assign_dynamic("sim2c", "use_identifier", &get__sim2c__use_identifier, &define__sim2c__use_identifier);
  use_multi_assign_dynamic("sim2c", "use_inline_c", &get__sim2c__use_inline_c, &set__sim2c__use_inline_c, &define__sim2c__use_inline_c);
  use_single_assign_dynamic("sim2c", "use_literal", &get__sim2c__use_literal, &define__sim2c__use_literal);
  use_multi_assign_dynamic("sim2c", "used_names", &get__sim2c__used_names, &set__sim2c__used_names, &define__sim2c__used_names);
  use_multi_assign_dynamic("sim2c", "used_namespaces", &get__sim2c__used_namespaces, &set__sim2c__used_namespaces, &define__sim2c__used_namespaces);
  use_single_assign_dynamic("sim2c", "write_to_continuation_table", &get__sim2c__write_to_continuation_table, &define__sim2c__write_to_continuation_table);
  use_single_assign_dynamic("sim2c", "write_to_declarations", &get__sim2c__write_to_declarations, &define__sim2c__write_to_declarations);
  use_single_assign_dynamic("sim2c", "write_to_delayed_continuation_table", &get__sim2c__write_to_delayed_continuation_table, &define__sim2c__write_to_delayed_continuation_table);
  use_single_assign_dynamic("sim2c", "write_to_delayed_statements", &get__sim2c__write_to_delayed_statements, &define__sim2c__write_to_delayed_statements);
  use_single_assign_dynamic("sim2c", "write_to_functions", &get__sim2c__write_to_functions, &define__sim2c__write_to_functions);
  use_single_assign_dynamic("sim2c", "write_to_generated_collections", &get__sim2c__write_to_generated_collections, &define__sim2c__write_to_generated_collections);
  use_single_assign_dynamic("sim2c", "write_to_global_variable_declarations", &get__sim2c__write_to_global_variable_declarations, &define__sim2c__write_to_global_variable_declarations);
  use_single_assign_dynamic("sim2c", "write_to_phase_1", &get__sim2c__write_to_phase_1, &define__sim2c__write_to_phase_1);
  use_single_assign_dynamic("sim2c", "write_to_phase_2", &get__sim2c__write_to_phase_2, &define__sim2c__write_to_phase_2);
  use_single_assign_dynamic("sim2c", "write_to_phase_3", &get__sim2c__write_to_phase_3, &define__sim2c__write_to_phase_3);
  use_single_assign_dynamic("sim2c", "write_to_phase_4", &get__sim2c__write_to_phase_4, &define__sim2c__write_to_phase_4);
  use_single_assign_dynamic("sim2c", "write_to_phase_5", &get__sim2c__write_to_phase_5, &define__sim2c__write_to_phase_5);
  use_single_assign_dynamic("sim2c", "write_to_top_level_variable_declarations", &get__sim2c__write_to_top_level_variable_declarations, &define__sim2c__write_to_top_level_variable_declarations);
  use_single_assign_dynamic("sim2c", "write_to_top_level_variable_names", &get__sim2c__write_to_top_level_variable_names, &define__sim2c__write_to_top_level_variable_names);
  use_read_only(NULL, "simplify_statement", &get__simplify_statement, &get_value_or_future__simplify_statement);
  use_polymorphic_function(NULL, "source_of", &get__source_of, &poly_idx__source_of);
  use_multi_assign_dynamic(NULL, "statements", &get__statements, &set__statements, &define__statements);
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
  use_read_only("std", "value_of", &get__std__value_of, &get_value_or_future__std__value_of);
  use_read_only(NULL, "std_identifier", &get__std_identifier, &get_value_or_future__std_identifier);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "strip", &get__strip, &get_value_or_future__strip);
  use_read_only(NULL, "table", &get__table, &get_value_or_future__table);
  use_read_only(NULL, "temp_idx", &get__temp_idx, &get_value_or_future__temp_idx);
  use_read_only(NULL, "terminate", &get__terminate, &get_value_or_future__terminate);
  use_read_only(NULL, "to_integer", &get__to_integer, &get_value_or_future__to_integer);
  use_read_only(NULL, "to_lower_case", &get__to_lower_case, &get_value_or_future__to_lower_case);
  use_read_only(NULL, "tokenize", &get__tokenize, &get_value_or_future__tokenize);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "truncate_until", &get__truncate_until, &get_value_or_future__truncate_until);
  use_read_only(NULL, "try", &get__try, &get_value_or_future__try);
  use_read_only("types", "grammar_node", &get__types__grammar_node, &get_value_or_future__types__grammar_node);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "update_each", &get__update_each, &get_value_or_future__update_each);
  use_read_only(NULL, "update_info", &get__update_info, &get_value_or_future__update_info);
  use_read_only(NULL, "use_inline_c", &get__use_inline_c, &get_value_or_future__use_inline_c);
  use_read_write(NULL, "used_namespaces", &get__used_namespaces, &set__used_namespaces);
  use_polymorphic_function(NULL, "variable_kind_of", &get__variable_kind_of, &poly_idx__variable_kind_of);
  use_read_only(NULL, "write", &get__write, &get_value_or_future__write);
  use_read_only(NULL, "write_source_as_remark", &get__write_source_as_remark, &get_value_or_future__write_source_as_remark);
  use_read_only(NULL, "write_timing_info", &get__write_timing_info, &get_value_or_future__write_timing_info);
  use_read_only(NULL, "write_to_continuation_table", &get__write_to_continuation_table, &get_value_or_future__write_to_continuation_table);
  use_read_only(NULL, "write_to_declarations", &get__write_to_declarations, &get_value_or_future__write_to_declarations);
  use_read_only(NULL, "write_to_delayed_statements", &get__write_to_delayed_statements, &get_value_or_future__write_to_delayed_statements);
  use_read_only(NULL, "write_to_functions", &get__write_to_functions, &get_value_or_future__write_to_functions);
  use_read_only(NULL, "writeln", &get__writeln, &get_value_or_future__writeln);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__sim2c(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&number__6, from_uint32(6U));
  assign_value(&character__35, from_uchar32(35));
  assign_value(&number__99, from_uint32(99U));
  assign_value(&character__47, from_uchar32(47));
  assign_value(&number__0, from_uint32(0U));
  assign_value(&number__3, from_uint32(3U));
  assign_value(&number__4, from_uint32(4U));
  assign_value(&number__0xffffffffffffffff, from_uint64(18446744073709551615ULL));
  assign_value(&number__0xffffffff, from_uint32(4294967295U));
  assign_value(&character__60, from_uchar32(60));
  assign_value(&character__34, from_uchar32(34));
  assign_value(&number__5, from_uint32(5U));
  assign_value(&character__39, from_uchar32(39));
  assign_value(&character__32, from_uchar32(32));
  assign_value(&character__101, from_uchar32(101));
  assign_value(&number__1, from_uint32(1U));
  assign_value(&character__69, from_uchar32(69));
  assign_value(&character__46, from_uchar32(46));
  assign_value(&number__2, from_uint32(2U));
  assign_variable(&var.sim2c__print_source, &func__1_1);
  assign_variable(&var.sim2c__eprint_source, &func__2_1);
  assign_variable(&var.sim2c__generate_dispatcher_function, &func__4_1);
  assign_variable(&var._demangled, &func__5_1);
  assign_variable(&var.sim2c__update_info, &func__6_1);
  assign_variable(&var.sim2c__sim2c, &func__7_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__sim2c(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__1_4, create_function(entry__1_4, 0));
  assign_value(&func__1_6, create_function(entry__1_6, 0));
  assign_value(&func__1_8, create_function(entry__1_8, 0));
  assign_value(&func__1_2, create_function(entry__1_2, 1));
  assign_value(&func__1_1, create_function(entry__1_1, 1));
  assign_value(&func__2_4, create_function(entry__2_4, 0));
  assign_value(&func__2_6, create_function(entry__2_6, 0));
  assign_value(&func__2_8, create_function(entry__2_8, 0));
  assign_value(&func__2_2, create_function(entry__2_2, 1));
  assign_value(&func__2_1, create_function(entry__2_1, 1));
  assign_value(&func__4_1, create_function(entry__4_1, 1));
  assign_value(&func__5_1, create_function(entry__5_1, 1));
  assign_value(&func__6_1, create_function(entry__6_1, 3));
  assign_value(&func__7_2, create_function(entry__7_2, 1));
  assign_value(&func__7_22, create_function(entry__7_22, 2));
  assign_value(&func__7_57, create_function(entry__7_57, 0));
  assign_value(&func__7_70, create_function(entry__7_70, 0));
  assign_value(&func__7_76, create_function(entry__7_76, 0));
  assign_value(&func__7_83, create_function(entry__7_83, 0));
  assign_value(&func__7_95, create_function(entry__7_95, 1));
  assign_value(&func__7_136, create_function(entry__7_136, 1));
  assign_value(&func__7_152, create_function(entry__7_152, 0));
  assign_value(&func__7_153, create_function(entry__7_153, 0));
  assign_value(&func__7_158, create_function(entry__7_158, 0));
  assign_value(&func__7_167, create_function(entry__7_167, 0));
  assign_value(&func__7_265, create_function(entry__7_265, 1));
  assign_value(&func__7_285, create_function(entry__7_285, 1));
  assign_value(&func__7_284, create_function(entry__7_284, 1));
  assign_value(&func__7_293, create_function(entry__7_293, 1));
  assign_value(&func__7_292, create_function(entry__7_292, 1));
  assign_value(&func__7_302, create_function(entry__7_302, 1));
  assign_value(&func__7_399, create_function(entry__7_399, 1));
  assign_value(&func__7_426, create_function(entry__7_426, 0));
  assign_value(&func__7_437, create_function(entry__7_437, 0));
  assign_value(&func__7_439, create_function(entry__7_439, 0));
  assign_value(&func__7_472, create_function(entry__7_472, 1));
  assign_value(&func__7_476, create_function(entry__7_476, 0));
  assign_value(&func__7_485, create_function(entry__7_485, 0));
  assign_value(&func__7_487, create_function(entry__7_487, 0));
  assign_value(&func__7_497, create_function(entry__7_497, 1));
  assign_value(&func__7_496, create_function(entry__7_496, 1));
  assign_value(&func__7_499, create_function(entry__7_499, 2));
  assign_value(&func__7_503, create_function(entry__7_503, 1));
  assign_value(&func__7_507, create_function(entry__7_507, 1));
  assign_value(&func__7_513, create_function(entry__7_513, 0));
  assign_value(&func__7_519, create_function(entry__7_519, 1));
  assign_value(&func__7_528, create_function(entry__7_528, 0));
  assign_value(&func__7_533, create_function(entry__7_533, 0));
  assign_value(&func__7_537, create_function(entry__7_537, 0));
  assign_value(&func__7_542, create_function(entry__7_542, 1));
  assign_value(&func__7_547, create_function(entry__7_547, 2));
  assign_value(&func__7_597, create_function(entry__7_597, 0));
  assign_value(&func__7_599, create_function(entry__7_599, 0));
  assign_value(&func__7_618, create_function(entry__7_618, 2));
  assign_value(&func__7_617, create_function(entry__7_617, 0));
  assign_value(&func__7_628, create_function(entry__7_628, 2));
  assign_value(&func__7_635, create_function(entry__7_635, 1));
  assign_value(&func__7_653, create_function(entry__7_653, 0));
  assign_value(&func__7_676, create_function(entry__7_676, 1));
  assign_value(&func__7_683, create_function(entry__7_683, 2));
  assign_value(&func__7_691, create_function(entry__7_691, 0));
  assign_value(&func__7_693, create_function(entry__7_693, 0));
  assign_value(&func__7_707, create_function(entry__7_707, 0));
  assign_value(&func__7_709, create_function(entry__7_709, 0));
  assign_value(&func__7_724, create_function(entry__7_724, 2));
  assign_value(&func__7_730, create_function(entry__7_730, 0));
  assign_value(&func__7_732, create_function(entry__7_732, 0));
  assign_value(&func__7_757, create_function(entry__7_757, 0));
  assign_value(&func__7_747, create_function(entry__7_747, 2));
  assign_value(&func__7_801, create_function(entry__7_801, 0));
  assign_value(&func__7_804, create_function(entry__7_804, 0));
  assign_value(&func__7_806, create_function(entry__7_806, 0));
  assign_value(&func__7_817, create_function(entry__7_817, 2));
  assign_value(&func__7_869, create_function(entry__7_869, 0));
  assign_value(&func__7_871, create_function(entry__7_871, 0));
  assign_value(&func__7_887, create_function(entry__7_887, 0));
  assign_value(&func__7_1, create_function(entry__7_1, -1));
  register_collector(collect__sim2c);
}
