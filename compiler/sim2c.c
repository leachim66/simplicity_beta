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
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void define_type_function(
  const char *namespace, const char *name, FUNC type, int par_cnt
);
IMPORT int main_argc;
IMPORT char **main_argv;
IMPORT void initialize_runtime(void);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_namespace(const char *namespace);
IMPORT void set_module(const char *name);
IMPORT NODE *from_double(double val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint64(uint64_t val);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_digit_string(const char *str);
IMPORT void initialize_phase_3(void);
IMPORT void resolve_symbols(void);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void initialize_phase_4(void);
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
IMPORT void initialize_function_attributes(void);
IMPORT void register_collector(FUNC collector);
IMPORT __attribute__ ((noreturn)) void execute(FUNC entry);
IMPORT NODE *collect_node(NODE *node);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void assign_variable(NODE **dest, NODE **var_p);


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
static NODE_GETTER get__compiler__actions;
static NODE_SETTER set__compiler__actions;
static NODE_SETTER define__compiler__actions;
static NODE_GETTER get__compiler__assigned_names;
static NODE_SETTER set__compiler__assigned_names;
static NODE_SETTER define__compiler__assigned_names;
static NODE_GETTER get__compiler__current_continuation_info;
static NODE_SETTER set__compiler__current_continuation_info;
static NODE_SETTER define__compiler__current_continuation_info;
static NODE_GETTER get__compiler__defined_functions;
static NODE_SETTER set__compiler__defined_functions;
static NODE_SETTER define__compiler__defined_functions;
static NODE_GETTER get__compiler__defined_names;
static NODE_SETTER set__compiler__defined_names;
static NODE_SETTER define__compiler__defined_names;
static NODE_GETTER get__compiler__defined_namespaces;
static NODE_SETTER set__compiler__defined_namespaces;
static NODE_SETTER define__compiler__defined_namespaces;
static NODE_GETTER get__compiler__defined_nodes;
static NODE_SETTER set__compiler__defined_nodes;
static NODE_SETTER define__compiler__defined_nodes;
static NODE_GETTER get__compiler__defined_structs;
static NODE_SETTER set__compiler__defined_structs;
static NODE_SETTER define__compiler__defined_structs;
static NODE_GETTER get__compiler__delayed_code;
static NODE_SETTER set__compiler__delayed_code;
static NODE_SETTER define__compiler__delayed_code;
static NODE_GETTER get__compiler__dependent_data;
static NODE_SETTER set__compiler__dependent_data;
static NODE_SETTER define__compiler__dependent_data;
static NODE_GETTER get__compiler__enumeration_count;
static NODE_SETTER set__compiler__enumeration_count;
static NODE_SETTER define__compiler__enumeration_count;
static NODE_GETTER get__compiler__exported_names;
static NODE_SETTER set__compiler__exported_names;
static NODE_SETTER define__compiler__exported_names;
static NODE_GETTER get__compiler__global_names;
static NODE_SETTER set__compiler__global_names;
static NODE_SETTER define__compiler__global_names;
static NODE_GETTER get__compiler__included_files;
static NODE_SETTER set__compiler__included_files;
static NODE_SETTER define__compiler__included_files;
static NODE_GETTER get__compiler__index;
static NODE_SETTER set__compiler__index;
static NODE_SETTER define__compiler__index;
static NODE_GETTER get__compiler__linked_libraries;
static NODE_SETTER set__compiler__linked_libraries;
static NODE_SETTER define__compiler__linked_libraries;
static NODE_GETTER get__compiler__namespace_mappings;
static NODE_SETTER set__compiler__namespace_mappings;
static NODE_SETTER define__compiler__namespace_mappings;
static NODE_GETTER get__compiler__needed_names;
static NODE_SETTER set__compiler__needed_names;
static NODE_SETTER define__compiler__needed_names;
static NODE_GETTER get__compiler__required_modules;
static NODE_SETTER set__compiler__required_modules;
static NODE_SETTER define__compiler__required_modules;
static NODE_GETTER get__compiler__string_literals;
static NODE_SETTER set__compiler__string_literals;
static NODE_SETTER define__compiler__string_literals;
static NODE_GETTER get__compiler__submodule_no;
static NODE_SETTER define__compiler__submodule_no;
static NODE_GETTER get__compiler__suffix;
static NODE_SETTER define__compiler__suffix;
static NODE_GETTER get__compiler__temp_idx;
static NODE_SETTER set__compiler__temp_idx;
static NODE_SETTER define__compiler__temp_idx;
static NODE_GETTER get__compiler__use_identifier;
static NODE_SETTER define__compiler__use_identifier;
static NODE_GETTER get__compiler__use_inline_c;
static NODE_SETTER set__compiler__use_inline_c;
static NODE_SETTER define__compiler__use_inline_c;
static NODE_GETTER get__compiler__use_literal;
static NODE_SETTER define__compiler__use_literal;
static NODE_GETTER get__compiler__used_names;
static NODE_SETTER set__compiler__used_names;
static NODE_SETTER define__compiler__used_names;
static NODE_GETTER get__compiler__used_namespaces;
static NODE_SETTER set__compiler__used_namespaces;
static NODE_SETTER define__compiler__used_namespaces;
static NODE_GETTER get__compiler__write_to_continuation_table;
static NODE_SETTER define__compiler__write_to_continuation_table;
static NODE_GETTER get__compiler__write_to_declarations;
static NODE_SETTER define__compiler__write_to_declarations;
static NODE_GETTER get__compiler__write_to_delayed_continuation_table;
static NODE_SETTER define__compiler__write_to_delayed_continuation_table;
static NODE_GETTER get__compiler__write_to_delayed_statements;
static NODE_SETTER define__compiler__write_to_delayed_statements;
static NODE_GETTER get__compiler__write_to_functions;
static NODE_SETTER define__compiler__write_to_functions;
static NODE_GETTER get__compiler__write_to_generated_collections;
static NODE_SETTER define__compiler__write_to_generated_collections;
static NODE_GETTER get__compiler__write_to_global_variable_declarations;
static NODE_SETTER define__compiler__write_to_global_variable_declarations;
static NODE_GETTER get__compiler__write_to_phase_1;
static NODE_SETTER define__compiler__write_to_phase_1;
static NODE_GETTER get__compiler__write_to_phase_2;
static NODE_SETTER define__compiler__write_to_phase_2;
static NODE_GETTER get__compiler__write_to_phase_3;
static NODE_SETTER define__compiler__write_to_phase_3;
static NODE_GETTER get__compiler__write_to_phase_4;
static NODE_SETTER define__compiler__write_to_phase_4;
static NODE_GETTER get__compiler__write_to_phase_5;
static NODE_SETTER define__compiler__write_to_phase_5;
static NODE_GETTER get__compiler__write_to_phase_6;
static NODE_SETTER define__compiler__write_to_phase_6;
static NODE_GETTER get__compiler__write_to_top_level_variable_declarations;
static NODE_SETTER define__compiler__write_to_top_level_variable_declarations;
static NODE_GETTER get__compiler__write_to_top_level_variable_names;
static NODE_SETTER define__compiler__write_to_top_level_variable_names;
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
static NODE_GETTER get__defined_namespaces;
static NODE_GETTER get_value_or_future__defined_namespaces;
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
static NODE_GETTER get__mangled_name_of;
static NODE_GETTER get_value_or_future__mangled_name_of;
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
static NODE_GETTER get__used_string_literals;
static NODE_SETTER set__used_string_literals;
static NODE_SETTER define__used_string_literals;
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
  NODE *compiler__print_source;
  NODE *compiler__eprint_source;
  NODE *compiler__privileged_polymorphic_functions;
  NODE *compiler__generate_dispatcher_function;
  NODE *compiler__update_info;
  NODE *compiler__sim2c;
} var;
static const char *var_names[] = {
  "demangled"
};
static NODE *func__compiler__print_source_1;
static void entry__compiler__print_source_1(void);
static FRAME_INFO frame__compiler__print_source_1 = {1, {"source"}};
static NODE *func__compiler__print_source_2;
static void entry__compiler__print_source_2(void);
static FRAME_INFO frame__compiler__print_source_2 = {1, {"chr"}};
static NODE *func__compiler__print_source_3;
static void entry__compiler__print_source_3(void);
static FRAME_INFO frame__compiler__print_source_3 = {1, {"chr"}};
static NODE *func__compiler__print_source_4;
static void entry__compiler__print_source_4(void);
static FRAME_INFO frame__compiler__print_source_4 = {0, {}};
static NODE *string__7ca425275e2bb55b;
static NODE *func__compiler__print_source_6;
static void entry__compiler__print_source_6(void);
static FRAME_INFO frame__compiler__print_source_6 = {0, {}};
static NODE *string__41a1d3500d2c5fd2;
static NODE *func__compiler__print_source_8;
static void entry__compiler__print_source_8(void);
static FRAME_INFO frame__compiler__print_source_8 = {0, {}};
static NODE *string__4b30bdab57f18372;
static NODE *get__compiler__print_source(void) {
  return var.compiler__print_source;
}
static NODE *func__compiler__eprint_source_1;
static void entry__compiler__eprint_source_1(void);
static FRAME_INFO frame__compiler__eprint_source_1 = {1, {"source"}};
static NODE *func__compiler__eprint_source_2;
static void entry__compiler__eprint_source_2(void);
static FRAME_INFO frame__compiler__eprint_source_2 = {1, {"chr"}};
static NODE *func__compiler__eprint_source_3;
static void entry__compiler__eprint_source_3(void);
static FRAME_INFO frame__compiler__eprint_source_3 = {1, {"chr"}};
static NODE *func__compiler__eprint_source_4;
static void entry__compiler__eprint_source_4(void);
static FRAME_INFO frame__compiler__eprint_source_4 = {0, {}};
static NODE *func__compiler__eprint_source_5;
static void entry__compiler__eprint_source_5(void);
static FRAME_INFO frame__compiler__eprint_source_5 = {0, {}};
static NODE *func__compiler__eprint_source_6;
static void entry__compiler__eprint_source_6(void);
static FRAME_INFO frame__compiler__eprint_source_6 = {0, {}};
static NODE *get__compiler__eprint_source(void) {
  return var.compiler__eprint_source;
}
static NODE *get__compiler__privileged_polymorphic_functions(void) {
  return var.compiler__privileged_polymorphic_functions;
}
static NODE *func__compiler__generate_dispatcher_function_1;
static void entry__compiler__generate_dispatcher_function_1(void);
static FRAME_INFO frame__compiler__generate_dispatcher_function_1 = {2, {"name", "id"}};
static NODE *string__7fb24a3fca4aa852;
static NODE *string__66ccbf91860d092a;
static void cont__compiler__generate_dispatcher_function_4(void);
static void cont__compiler__generate_dispatcher_function_5(void);
static NODE *string__fc8c36a84adb366f;
static void cont__compiler__generate_dispatcher_function_7(void);
static void cont__compiler__generate_dispatcher_function_8(void);
static void cont__compiler__generate_dispatcher_function_9(void);
static void cont__compiler__generate_dispatcher_function_10(void);
static NODE *func__compiler__generate_dispatcher_function_11;
static void entry__compiler__generate_dispatcher_function_11(void);
static FRAME_INFO frame__compiler__generate_dispatcher_function_11 = {2, {"name", "id"}};
static NODE *string__75f4eb726550b6de;
static NODE *string__d81f45a403c7e2f7;
static NODE *string__578a5af303e9ceb;
static void cont__compiler__generate_dispatcher_function_15(void);
static NODE *func__compiler__generate_dispatcher_function_16;
static void entry__compiler__generate_dispatcher_function_16(void);
static FRAME_INFO frame__compiler__generate_dispatcher_function_16 = {1, {"name"}};
static NODE *string__fa732015ff16bc6;
static void cont__compiler__generate_dispatcher_function_18(void);
static void cont__compiler__generate_dispatcher_function_19(void);
static NODE *string__3dbc7d1f8cf28ba6;
static NODE *string__9f2e0c02fff25101;
static void cont__compiler__generate_dispatcher_function_22(void);
static NODE *get__compiler__generate_dispatcher_function(void) {
  return var.compiler__generate_dispatcher_function;
}
static NODE *func__demangled_1;
static void entry__demangled_1(void);
static FRAME_INFO frame__demangled_1 = {1, {"name"}};
static NODE *string__2d7981f4e5f02b9a;
static NODE *string__2d7981f4e6d82bff;
static void cont__demangled_4(void);
static void cont__demangled_5(void);
static NODE *func__compiler__update_info_1;
static void entry__compiler__update_info_1(void);
static FRAME_INFO frame__compiler__update_info_1 = {4, {"name", "curr_info", "info", "return"}};
static void cont__compiler__update_info_2(void);
static NODE *func__compiler__update_info_3;
static void entry__compiler__update_info_3(void);
static FRAME_INFO frame__compiler__update_info_3 = {4, {"curr_info", "info", "return", "name"}};
static void cont__compiler__update_info_4(void);
static NODE *func__compiler__update_info_5;
static void entry__compiler__update_info_5(void);
static FRAME_INFO frame__compiler__update_info_5 = {3, {"info", "return", "name"}};
static void cont__compiler__update_info_6(void);
static void cont__compiler__update_info_7(void);
static NODE *func__compiler__update_info_8;
static void entry__compiler__update_info_8(void);
static FRAME_INFO frame__compiler__update_info_8 = {1, {"return"}};
static NODE *func__compiler__update_info_9;
static void entry__compiler__update_info_9(void);
static FRAME_INFO frame__compiler__update_info_9 = {1, {"name"}};
static void cont__compiler__update_info_10(void);
static NODE *string__94b9534b986c24a9;
static NODE *string__634c61c70382d128;
static void cont__compiler__update_info_13(void);
static NODE *func__compiler__update_info_14;
static void entry__compiler__update_info_14(void);
static FRAME_INFO frame__compiler__update_info_14 = {2, {"info", "return"}};
static void cont__compiler__update_info_15(void);
static NODE *func__compiler__update_info_16;
static void entry__compiler__update_info_16(void);
static FRAME_INFO frame__compiler__update_info_16 = {1, {"return"}};
static NODE *func__compiler__update_info_17;
static void entry__compiler__update_info_17(void);
static FRAME_INFO frame__compiler__update_info_17 = {2, {"return", "info"}};
static NODE *func__compiler__update_info_18;
static void entry__compiler__update_info_18(void);
static FRAME_INFO frame__compiler__update_info_18 = {3, {"info", "name", "return"}};
static void cont__compiler__update_info_19(void);
static NODE *func__compiler__update_info_20;
static void entry__compiler__update_info_20(void);
static FRAME_INFO frame__compiler__update_info_20 = {1, {"name"}};
static void cont__compiler__update_info_21(void);
static NODE *string__67c02c7b1bf18880;
static void cont__compiler__update_info_23(void);
static void cont__compiler__update_info_24(void);
static NODE *func__compiler__update_info_25;
static void entry__compiler__update_info_25(void);
static FRAME_INFO frame__compiler__update_info_25 = {1, {"return"}};
static NODE *func__compiler__update_info_26;
static void entry__compiler__update_info_26(void);
static FRAME_INFO frame__compiler__update_info_26 = {1, {"name"}};
static void cont__compiler__update_info_27(void);
static NODE *string__f8ba3c062f1b8631;
static void cont__compiler__update_info_29(void);
static NODE *func__compiler__update_info_30;
static void entry__compiler__update_info_30(void);
static FRAME_INFO frame__compiler__update_info_30 = {2, {"return", "info"}};
static NODE *func__compiler__update_info_31;
static void entry__compiler__update_info_31(void);
static FRAME_INFO frame__compiler__update_info_31 = {3, {"info", "name", "return"}};
static void cont__compiler__update_info_32(void);
static NODE *func__compiler__update_info_33;
static void entry__compiler__update_info_33(void);
static FRAME_INFO frame__compiler__update_info_33 = {1, {"name"}};
static void cont__compiler__update_info_34(void);
static NODE *string__aafcf41c458e8f41;
static void cont__compiler__update_info_36(void);
static void cont__compiler__update_info_37(void);
static NODE *func__compiler__update_info_38;
static void entry__compiler__update_info_38(void);
static FRAME_INFO frame__compiler__update_info_38 = {1, {"return"}};
static NODE *func__compiler__update_info_39;
static void entry__compiler__update_info_39(void);
static FRAME_INFO frame__compiler__update_info_39 = {1, {"name"}};
static void cont__compiler__update_info_40(void);
static void cont__compiler__update_info_41(void);
static NODE *func__compiler__update_info_42;
static void entry__compiler__update_info_42(void);
static FRAME_INFO frame__compiler__update_info_42 = {1, {"name"}};
static void cont__compiler__update_info_43(void);
static NODE *string__80670d894d05691d;
static void cont__compiler__update_info_45(void);
static NODE *func__compiler__update_info_46;
static void entry__compiler__update_info_46(void);
static FRAME_INFO frame__compiler__update_info_46 = {3, {"info", "name", "return"}};
static void cont__compiler__update_info_47(void);
static NODE *func__compiler__update_info_48;
static void entry__compiler__update_info_48(void);
static FRAME_INFO frame__compiler__update_info_48 = {1, {"name"}};
static void cont__compiler__update_info_49(void);
static NODE *string__a09d645d506640e9;
static void cont__compiler__update_info_51(void);
static void cont__compiler__update_info_52(void);
static NODE *func__compiler__update_info_53;
static void entry__compiler__update_info_53(void);
static FRAME_INFO frame__compiler__update_info_53 = {1, {"return"}};
static NODE *func__compiler__update_info_54;
static void entry__compiler__update_info_54(void);
static FRAME_INFO frame__compiler__update_info_54 = {1, {"name"}};
static void cont__compiler__update_info_55(void);
static void cont__compiler__update_info_56(void);
static NODE *func__compiler__update_info_57;
static void entry__compiler__update_info_57(void);
static FRAME_INFO frame__compiler__update_info_57 = {2, {"return", "info"}};
static NODE *func__compiler__update_info_58;
static void entry__compiler__update_info_58(void);
static FRAME_INFO frame__compiler__update_info_58 = {2, {"return", "info"}};
static void cont__compiler__update_info_59(void);
static NODE *get__compiler__update_info(void) {
  return var.compiler__update_info;
}
static NODE *func__compiler__sim2c_1;
static void entry__compiler__sim2c_1(void);
static FRAME_INFO frame__compiler__sim2c_1 = {33, {"filenames", "is_main", "return__10", "mangle_filename", "fragments", "trees", "all_defined_names", "all_used_names", "all_actions", "top_level_names", "all_definitions", "all_statements", "max_temp_idx", "need", "generated_declarations", "generated_top_level_variable_names", "generated_top_level_variable_declarations", "generated_global_variable_declarations", "generated_continuation_table", "generated_delayed_continuation_table", "generated_functions", "generated_phase_1", "generated_phase_2", "generated_phase_3", "generated_phase_4", "generated_phase_5", "generated_phase_6", "generated_code", "generated_collections", "delayed_statements", "used_literals", "def_count", "depth"}};
static NODE *func__compiler__sim2c_2;
static void entry__compiler__sim2c_2(void);
static FRAME_INFO frame__compiler__sim2c_2 = {1, {"name"}};
static NODE *string__2d7981f4e6782bea;
static void cont__compiler__sim2c_4(void);
static NODE *func__compiler__sim2c_5;
static void entry__compiler__sim2c_5(void);
static FRAME_INFO frame__compiler__sim2c_5 = {1, {"name"}};
static void cont__compiler__sim2c_6(void);
static NODE *func__compiler__sim2c_7;
static void entry__compiler__sim2c_7(void);
static FRAME_INFO frame__compiler__sim2c_7 = {1, {"name"}};
static void cont__compiler__sim2c_8(void);
static void cont__compiler__sim2c_9(void);
static void cont__compiler__sim2c_10(void);
static void cont__compiler__sim2c_11(void);
static void cont__compiler__sim2c_12(void);
static NODE *func__compiler__sim2c_13;
static void entry__compiler__sim2c_13(void);
static FRAME_INFO frame__compiler__sim2c_13 = {1, {"name"}};
static void cont__compiler__sim2c_14(void);
static void cont__compiler__sim2c_15(void);
static void cont__compiler__sim2c_16(void);
static void cont__compiler__sim2c_17(void);
static void cont__compiler__sim2c_18(void);
static NODE *func__compiler__sim2c_19;
static void entry__compiler__sim2c_19(void);
static FRAME_INFO frame__compiler__sim2c_19 = {4, {"mangled_name", "info", "return", "updated_info"}};
static void cont__compiler__sim2c_20(void);
static NODE *func__compiler__sim2c_21;
static void entry__compiler__sim2c_21(void);
static FRAME_INFO frame__compiler__sim2c_21 = {5, {"mangled_name", "return", "namespace", "name", "namespaces"}};
static void cont__compiler__sim2c_22(void);
static void cont__compiler__sim2c_23(void);
static void cont__compiler__sim2c_24(void);
static void cont__compiler__sim2c_25(void);
static NODE *func__compiler__sim2c_26;
static void entry__compiler__sim2c_26(void);
static FRAME_INFO frame__compiler__sim2c_26 = {2, {"namespaces", "namespace"}};
static void cont__compiler__sim2c_27(void);
static void cont__compiler__sim2c_28(void);
static void cont__compiler__sim2c_29(void);
static NODE *func__compiler__sim2c_30;
static void entry__compiler__sim2c_30(void);
static FRAME_INFO frame__compiler__sim2c_30 = {4, {"mangled_name", "info", "return", "definition"}};
static void cont__compiler__sim2c_31(void);
static void cont__compiler__sim2c_32(void);
static NODE *func__compiler__sim2c_33;
static void entry__compiler__sim2c_33(void);
static FRAME_INFO frame__compiler__sim2c_33 = {4, {"mangled_name", "definition", "info", "return"}};
static void cont__compiler__sim2c_34(void);
static void cont__compiler__sim2c_35(void);
static void cont__compiler__sim2c_36(void);
static void cont__compiler__sim2c_37(void);
static void cont__compiler__sim2c_38(void);
static NODE *func__compiler__sim2c_39;
static void entry__compiler__sim2c_39(void);
static FRAME_INFO frame__compiler__sim2c_39 = {2, {"mangled_name", "updated_info"}};
static void cont__compiler__sim2c_40(void);
static void cont__compiler__sim2c_41(void);
static NODE *string__5e0ae28b5c407d7c;
static void cont__compiler__sim2c_43(void);
static NODE *string__1c6c7289032a5d69;
static void cont__compiler__sim2c_45(void);
static void cont__compiler__sim2c_46(void);
static NODE *func__compiler__sim2c_47;
static void entry__compiler__sim2c_47(void);
static FRAME_INFO frame__compiler__sim2c_47 = {9, {"no", "filename", "return__1", "is_main", "trees", "fragments", "buf", "submodule_fragments", "first_idx"}};
static void cont__compiler__sim2c_48(void);
static NODE *func__compiler__sim2c_49;
static void entry__compiler__sim2c_49(void);
static FRAME_INFO frame__compiler__sim2c_49 = {1, {"buf"}};
static void cont__compiler__sim2c_50(void);
static NODE *func__compiler__sim2c_51;
static void entry__compiler__sim2c_51(void);
static FRAME_INFO frame__compiler__sim2c_51 = {0, {}};
static NODE *string__38b3477328e1d61b;
static void cont__compiler__sim2c_53(void);
static NODE *func__compiler__sim2c_54;
static void entry__compiler__sim2c_54(void);
static FRAME_INFO frame__compiler__sim2c_54 = {1, {"filename"}};
static NODE *string__5a1f574683baa2f5;
static NODE *string__2d7981f4e6182bcf;
static void cont__compiler__sim2c_57(void);
static void cont__compiler__sim2c_58(void);
static NODE *func__compiler__sim2c_59;
static void entry__compiler__sim2c_59(void);
static FRAME_INFO frame__compiler__sim2c_59 = {1, {"filename"}};
static NODE *string__ba340f9515cad09d;
static void cont__compiler__sim2c_61(void);
static void cont__compiler__sim2c_62(void);
static void cont__compiler__sim2c_63(void);
static NODE *func__compiler__sim2c_64;
static void entry__compiler__sim2c_64(void);
static FRAME_INFO frame__compiler__sim2c_64 = {0, {}};
static NODE *string__1cbf9967f0b4797a;
static void cont__compiler__sim2c_66(void);
static void cont__compiler__sim2c_67(void);
static void cont__compiler__sim2c_68(void);
static void cont__compiler__sim2c_69(void);
static NODE *func__compiler__sim2c_70;
static void entry__compiler__sim2c_70(void);
static FRAME_INFO frame__compiler__sim2c_70 = {0, {}};
static NODE *string__cdb2cfe249b97e8f;
static void cont__compiler__sim2c_72(void);
static void cont__compiler__sim2c_73(void);
static void cont__compiler__sim2c_74(void);
static void cont__compiler__sim2c_75(void);
static void cont__compiler__sim2c_76(void);
static NODE *func__compiler__sim2c_77;
static void entry__compiler__sim2c_77(void);
static FRAME_INFO frame__compiler__sim2c_77 = {0, {}};
static NODE *string__f5ba012e5873af55;
static void cont__compiler__sim2c_79(void);
static NODE *string__2d7981f4e6102be4;
static void cont__compiler__sim2c_81(void);
static NODE *func__compiler__sim2c_82;
static void entry__compiler__sim2c_82(void);
static FRAME_INFO frame__compiler__sim2c_82 = {1, {"is_main"}};
static void cont__compiler__sim2c_83(void);
static void cont__compiler__sim2c_84(void);
static void cont__compiler__sim2c_85(void);
static NODE *func__compiler__sim2c_86;
static void entry__compiler__sim2c_86(void);
static FRAME_INFO frame__compiler__sim2c_86 = {1, {"filename"}};
static NODE *string__28e9a3192e794ba6;
static void cont__compiler__sim2c_88(void);
static NODE *func__compiler__sim2c_89;
static void entry__compiler__sim2c_89(void);
static FRAME_INFO frame__compiler__sim2c_89 = {1, {"fragment"}};
static void cont__compiler__sim2c_90(void);
static void cont__compiler__sim2c_91(void);
static NODE *func__compiler__sim2c_92;
static void entry__compiler__sim2c_92(void);
static FRAME_INFO frame__compiler__sim2c_92 = {1, {"filename"}};
static NODE *string__170b25ca95be486;
static void cont__compiler__sim2c_94(void);
static NODE *func__compiler__sim2c_95;
static void entry__compiler__sim2c_95(void);
static FRAME_INFO frame__compiler__sim2c_95 = {4, {"done", "submodule_fragments", "first_idx", "trees"}};
static NODE *func__compiler__sim2c_96;
static void entry__compiler__sim2c_96(void);
static FRAME_INFO frame__compiler__sim2c_96 = {5, {"idx", "fragment", "first_idx", "trees", "done"}};
static void cont__compiler__sim2c_97(void);
static void cont__compiler__sim2c_98(void);
static NODE *func__compiler__sim2c_99;
static void entry__compiler__sim2c_99(void);
static FRAME_INFO frame__compiler__sim2c_99 = {4, {"first_idx", "idx", "trees", "fragment"}};
static void cont__compiler__sim2c_100(void);
static void cont__compiler__sim2c_101(void);
static void cont__compiler__sim2c_102(void);
static NODE *func__compiler__sim2c_103;
static void entry__compiler__sim2c_103(void);
static FRAME_INFO frame__compiler__sim2c_103 = {4, {"first_idx", "idx", "trees", "fragment"}};
static void cont__compiler__sim2c_104(void);
static void cont__compiler__sim2c_105(void);
static void cont__compiler__sim2c_106(void);
static NODE *func__compiler__sim2c_107;
static void entry__compiler__sim2c_107(void);
static FRAME_INFO frame__compiler__sim2c_107 = {1, {"done"}};
static void cont__compiler__sim2c_108(void);
static void cont__compiler__sim2c_109(void);
static void cont__compiler__sim2c_110(void);
static void cont__compiler__sim2c_111(void);
static void cont__compiler__sim2c_112(void);
static void cont__compiler__sim2c_113(void);
static NODE *func__compiler__sim2c_114;
static void entry__compiler__sim2c_114(void);
static FRAME_INFO frame__compiler__sim2c_114 = {2, {"fragment", "trees"}};
static void cont__compiler__sim2c_115(void);
static void cont__compiler__sim2c_116(void);
static void cont__compiler__sim2c_117(void);
static NODE *func__compiler__sim2c_118;
static void entry__compiler__sim2c_118(void);
static FRAME_INFO frame__compiler__sim2c_118 = {1, {"filenames"}};
static void cont__compiler__sim2c_119(void);
static NODE *string__94440f9215cbe09d;
static void cont__compiler__sim2c_121(void);
static NODE *func__compiler__sim2c_122;
static void entry__compiler__sim2c_122(void);
static FRAME_INFO frame__compiler__sim2c_122 = {1, {"trees"}};
static void cont__compiler__sim2c_123(void);
static void cont__compiler__sim2c_124(void);
static NODE *func__compiler__sim2c_125;
static void entry__compiler__sim2c_125(void);
static FRAME_INFO frame__compiler__sim2c_125 = {1, {"trees"}};
static NODE *string__72f826ea16a3e460;
static void cont__compiler__sim2c_127(void);
static void cont__compiler__sim2c_128(void);
static void cont__compiler__sim2c_129(void);
static NODE *func__compiler__sim2c_130;
static void entry__compiler__sim2c_130(void);
static FRAME_INFO frame__compiler__sim2c_130 = {2, {"tree", "return__2"}};
static void exit__compiler__sim2c_130(void);
static void cont__compiler__sim2c_131(void);
static void cont__compiler__sim2c_132(void);
static NODE *func__compiler__sim2c_133;
static void entry__compiler__sim2c_133(void);
static FRAME_INFO frame__compiler__sim2c_133 = {1, {"filenames"}};
static void cont__compiler__sim2c_134(void);
static NODE *string__66f024ec077397c2;
static void cont__compiler__sim2c_136(void);
static NODE *func__compiler__sim2c_137;
static void entry__compiler__sim2c_137(void);
static FRAME_INFO frame__compiler__sim2c_137 = {4, {"tree", "return__3", "all_defined_names", "all_used_names"}};
static void exit__compiler__sim2c_137(void);
static void cont__compiler__sim2c_138(void);
static void cont__compiler__sim2c_139(void);
static void cont__compiler__sim2c_140(void);
static void cont__compiler__sim2c_141(void);
static NODE *func__compiler__sim2c_142;
static void entry__compiler__sim2c_142(void);
static FRAME_INFO frame__compiler__sim2c_142 = {1, {"filenames"}};
static void cont__compiler__sim2c_143(void);
static NODE *string__1d581a51a85b6426;
static void cont__compiler__sim2c_145(void);
static NODE *func__compiler__sim2c_146;
static void entry__compiler__sim2c_146(void);
static FRAME_INFO frame__compiler__sim2c_146 = {0, {}};
static NODE *func__compiler__sim2c_147;
static void entry__compiler__sim2c_147(void);
static FRAME_INFO frame__compiler__sim2c_147 = {0, {}};
static void cont__compiler__sim2c_148(void);
static void cont__compiler__sim2c_149(void);
static NODE *func__compiler__sim2c_150;
static void entry__compiler__sim2c_150(void);
static FRAME_INFO frame__compiler__sim2c_150 = {1, {"is_main"}};
static void cont__compiler__sim2c_151(void);
static NODE *func__compiler__sim2c_152;
static void entry__compiler__sim2c_152(void);
static FRAME_INFO frame__compiler__sim2c_152 = {0, {}};
static NODE *string__c3e1e344d34946eb;
static void cont__compiler__sim2c_154(void);
static NODE *string__b567219b137172d;
static void cont__compiler__sim2c_156(void);
static void cont__compiler__sim2c_157(void);
static NODE *string__a23c0f9515cb809d;
static void cont__compiler__sim2c_159(void);
static void cont__compiler__sim2c_160(void);
static NODE *func__compiler__sim2c_161;
static void entry__compiler__sim2c_161(void);
static FRAME_INFO frame__compiler__sim2c_161 = {0, {}};
static NODE *string__fa724815d896ba8;
static void cont__compiler__sim2c_163(void);
static void cont__compiler__sim2c_164(void);
static void cont__compiler__sim2c_165(void);
static NODE *func__compiler__sim2c_166;
static void entry__compiler__sim2c_166(void);
static FRAME_INFO frame__compiler__sim2c_166 = {2, {"defined_names", "top_level_names"}};
static NODE *func__compiler__sim2c_167;
static void entry__compiler__sim2c_167(void);
static FRAME_INFO frame__compiler__sim2c_167 = {3, {"info", "top_level_names", "ident"}};
static void cont__compiler__sim2c_168(void);
static void cont__compiler__sim2c_169(void);
static NODE *func__compiler__sim2c_170;
static void entry__compiler__sim2c_170(void);
static FRAME_INFO frame__compiler__sim2c_170 = {1, {"info"}};
static void cont__compiler__sim2c_171(void);
static void cont__compiler__sim2c_172(void);
static void cont__compiler__sim2c_173(void);
static NODE *func__compiler__sim2c_174;
static void entry__compiler__sim2c_174(void);
static FRAME_INFO frame__compiler__sim2c_174 = {5, {"ident", "info", "top_level_names", "namespace", "name"}};
static void cont__compiler__sim2c_175(void);
static void cont__compiler__sim2c_176(void);
static void cont__compiler__sim2c_177(void);
static NODE *func__compiler__sim2c_178;
static void entry__compiler__sim2c_178(void);
static FRAME_INFO frame__compiler__sim2c_178 = {5, {"name", "namespace", "info", "top_level_names", "namespaces"}};
static void cont__compiler__sim2c_179(void);
static void cont__compiler__sim2c_180(void);
static NODE *func__compiler__sim2c_181;
static void entry__compiler__sim2c_181(void);
static FRAME_INFO frame__compiler__sim2c_181 = {1, {"namespaces"}};
static void cont__compiler__sim2c_182(void);
static void cont__compiler__sim2c_183(void);
static void cont__compiler__sim2c_184(void);
static void cont__compiler__sim2c_185(void);
static NODE *func__compiler__sim2c_186;
static void entry__compiler__sim2c_186(void);
static FRAME_INFO frame__compiler__sim2c_186 = {3, {"info", "namespace", "name"}};
static void cont__compiler__sim2c_187(void);
static NODE *string__b18861f6a8c886ba;
static NODE *string__95b7f6cc14260ab8;
static void cont__compiler__sim2c_190(void);
static void cont__compiler__sim2c_191(void);
static void cont__compiler__sim2c_192(void);
static NODE *func__compiler__sim2c_193;
static void entry__compiler__sim2c_193(void);
static FRAME_INFO frame__compiler__sim2c_193 = {5, {"name", "info", "namespace", "top_level_names", "info_1"}};
static void cont__compiler__sim2c_194(void);
static void cont__compiler__sim2c_195(void);
static NODE *func__compiler__sim2c_196;
static void entry__compiler__sim2c_196(void);
static FRAME_INFO frame__compiler__sim2c_196 = {3, {"info", "namespace", "name"}};
static void cont__compiler__sim2c_197(void);
static NODE *string__69658745890c070;
static NODE *string__c419bd2045fe53aa;
static NODE *string__578a5af303e9cc3;
static void cont__compiler__sim2c_201(void);
static void cont__compiler__sim2c_202(void);
static void cont__compiler__sim2c_203(void);
static void cont__compiler__sim2c_204(void);
static NODE *func__compiler__sim2c_205;
static void entry__compiler__sim2c_205(void);
static FRAME_INFO frame__compiler__sim2c_205 = {4, {"info", "namespace", "name", "info_1"}};
static void cont__compiler__sim2c_206(void);
static void cont__compiler__sim2c_207(void);
static void cont__compiler__sim2c_208(void);
static NODE *string__b5bb4d11daae5f7a;
static NODE *string__6de219341b32224c;
static void cont__compiler__sim2c_211(void);
static void cont__compiler__sim2c_212(void);
static void cont__compiler__sim2c_213(void);
static void cont__compiler__sim2c_214(void);
static void cont__compiler__sim2c_215(void);
static void cont__compiler__sim2c_216(void);
static NODE *func__compiler__sim2c_217;
static void entry__compiler__sim2c_217(void);
static FRAME_INFO frame__compiler__sim2c_217 = {4, {"name", "info", "top_level_names", "namespaces"}};
static void cont__compiler__sim2c_218(void);
static void cont__compiler__sim2c_219(void);
static NODE *func__compiler__sim2c_220;
static void entry__compiler__sim2c_220(void);
static FRAME_INFO frame__compiler__sim2c_220 = {2, {"info", "name"}};
static void cont__compiler__sim2c_221(void);
static void cont__compiler__sim2c_222(void);
static void cont__compiler__sim2c_223(void);
static void cont__compiler__sim2c_224(void);
static void cont__compiler__sim2c_225(void);
static NODE *func__compiler__sim2c_226;
static void entry__compiler__sim2c_226(void);
static FRAME_INFO frame__compiler__sim2c_226 = {3, {"namespaces", "info", "name"}};
static NODE *func__compiler__sim2c_227;
static void entry__compiler__sim2c_227(void);
static FRAME_INFO frame__compiler__sim2c_227 = {4, {"nspace", "dummy", "info", "name"}};
static void cont__compiler__sim2c_228(void);
static NODE *func__compiler__sim2c_229;
static void entry__compiler__sim2c_229(void);
static FRAME_INFO frame__compiler__sim2c_229 = {3, {"info", "name", "nspace"}};
static void cont__compiler__sim2c_230(void);
static void cont__compiler__sim2c_231(void);
static void cont__compiler__sim2c_232(void);
static void cont__compiler__sim2c_233(void);
static void cont__compiler__sim2c_234(void);
static void cont__compiler__sim2c_235(void);
static NODE *func__compiler__sim2c_236;
static void entry__compiler__sim2c_236(void);
static FRAME_INFO frame__compiler__sim2c_236 = {3, {"all_used_names", "top_level_names", "top_level_used_names"}};
static NODE *func__compiler__sim2c_237;
static void entry__compiler__sim2c_237(void);
static FRAME_INFO frame__compiler__sim2c_237 = {2, {"used_names", "top_level_used_names"}};
static NODE *func__compiler__sim2c_238;
static void entry__compiler__sim2c_238(void);
static FRAME_INFO frame__compiler__sim2c_238 = {3, {"mangled_name", "info", "top_level_used_names"}};
static void cont__compiler__sim2c_239(void);
static void cont__compiler__sim2c_240(void);
static void cont__compiler__sim2c_241(void);
static NODE *func__compiler__sim2c_242;
static void entry__compiler__sim2c_242(void);
static FRAME_INFO frame__compiler__sim2c_242 = {1, {"filenames"}};
static void cont__compiler__sim2c_243(void);
static NODE *string__5ab424ea8372e502;
static void cont__compiler__sim2c_245(void);
static NODE *func__compiler__sim2c_246;
static void entry__compiler__sim2c_246(void);
static FRAME_INFO frame__compiler__sim2c_246 = {1, {"trees"}};
static NODE *func__compiler__sim2c_247;
static void entry__compiler__sim2c_247(void);
static FRAME_INFO frame__compiler__sim2c_247 = {1, {"tree"}};
static void cont__compiler__sim2c_248(void);
static void cont__compiler__sim2c_249(void);
static void cont__compiler__sim2c_250(void);
static void cont__compiler__sim2c_251(void);
static NODE *func__compiler__sim2c_252;
static void entry__compiler__sim2c_252(void);
static FRAME_INFO frame__compiler__sim2c_252 = {6, {"tree", "top_level_names", "all_statements", "all_definitions", "max_temp_idx", "all_actions"}};
static void cont__compiler__sim2c_253(void);
static NODE *func__compiler__sim2c_254;
static void entry__compiler__sim2c_254(void);
static FRAME_INFO frame__compiler__sim2c_254 = {1, {"tree"}};
static void cont__compiler__sim2c_255(void);
static void cont__compiler__sim2c_256(void);
static NODE *func__compiler__sim2c_257;
static void entry__compiler__sim2c_257(void);
static FRAME_INFO frame__compiler__sim2c_257 = {8, {"return__4", "top_level_names", "tree", "all_statements", "all_definitions", "max_temp_idx", "all_actions", "tmp_idx"}};
static void cont__compiler__sim2c_258(void);
static void cont__compiler__sim2c_259(void);
static void cont__compiler__sim2c_260(void);
static NODE *func__compiler__sim2c_261;
static void entry__compiler__sim2c_261(void);
static FRAME_INFO frame__compiler__sim2c_261 = {2, {"max_temp_idx", "tmp_idx"}};
static void cont__compiler__sim2c_262(void);
static void cont__compiler__sim2c_263(void);
static void cont__compiler__sim2c_264(void);
static void cont__compiler__sim2c_265(void);
static NODE *func__compiler__sim2c_266;
static void entry__compiler__sim2c_266(void);
static FRAME_INFO frame__compiler__sim2c_266 = {1, {"stmt_actions"}};
static NODE *func__compiler__sim2c_267;
static void entry__compiler__sim2c_267(void);
static FRAME_INFO frame__compiler__sim2c_267 = {1, {"action"}};
static void cont__compiler__sim2c_268(void);
static NODE *func__compiler__sim2c_269;
static void entry__compiler__sim2c_269(void);
static FRAME_INFO frame__compiler__sim2c_269 = {1, {"filenames"}};
static void cont__compiler__sim2c_270(void);
static NODE *string__72ed7b1f2279c943;
static void cont__compiler__sim2c_272(void);
static NODE *func__compiler__sim2c_273;
static void entry__compiler__sim2c_273(void);
static FRAME_INFO frame__compiler__sim2c_273 = {2, {"all_definitions", "all_statements"}};
static NODE *func__compiler__sim2c_274;
static void entry__compiler__sim2c_274(void);
static FRAME_INFO frame__compiler__sim2c_274 = {1, {"defs"}};
static NODE *func__compiler__sim2c_275;
static void entry__compiler__sim2c_275(void);
static FRAME_INFO frame__compiler__sim2c_275 = {1, {"def"}};
static void cont__compiler__sim2c_276(void);
static NODE *func__compiler__sim2c_277;
static void entry__compiler__sim2c_277(void);
static FRAME_INFO frame__compiler__sim2c_277 = {1, {"def"}};
static void cont__compiler__sim2c_278(void);
static void cont__compiler__sim2c_279(void);
static NODE *string__7c84ae5484fdf7e0;
static NODE *func__compiler__sim2c_281;
static void entry__compiler__sim2c_281(void);
static FRAME_INFO frame__compiler__sim2c_281 = {1, {"def"}};
static void cont__compiler__sim2c_282(void);
static NODE *func__compiler__sim2c_283;
static void entry__compiler__sim2c_283(void);
static FRAME_INFO frame__compiler__sim2c_283 = {1, {"stmts"}};
static void cont__compiler__sim2c_284(void);
static void cont__compiler__sim2c_285(void);
static NODE *func__compiler__sim2c_286;
static void entry__compiler__sim2c_286(void);
static FRAME_INFO frame__compiler__sim2c_286 = {2, {"used_names", "need"}};
static NODE *func__compiler__sim2c_287;
static void entry__compiler__sim2c_287(void);
static FRAME_INFO frame__compiler__sim2c_287 = {3, {"mangled_name", "info", "need"}};
static void cont__compiler__sim2c_288(void);
static NODE *func__compiler__sim2c_289;
static void entry__compiler__sim2c_289(void);
static FRAME_INFO frame__compiler__sim2c_289 = {1, {"filenames"}};
static void cont__compiler__sim2c_290(void);
static NODE *string__7690af9104a5e1e7;
static void cont__compiler__sim2c_292(void);
static void cont__compiler__sim2c_293(void);
static NODE *func__compiler__sim2c_294;
static void entry__compiler__sim2c_294(void);
static FRAME_INFO frame__compiler__sim2c_294 = {3, {"args", "generated_declarations", "txt"}};
static void cont__compiler__sim2c_295(void);
static NODE *func__compiler__sim2c_296;
static void entry__compiler__sim2c_296(void);
static FRAME_INFO frame__compiler__sim2c_296 = {2, {"generated_declarations", "txt"}};
static void cont__compiler__sim2c_297(void);
static void cont__compiler__sim2c_298(void);
static NODE *func__compiler__sim2c_299;
static void entry__compiler__sim2c_299(void);
static FRAME_INFO frame__compiler__sim2c_299 = {3, {"args", "generated_top_level_variable_names", "txt"}};
static void cont__compiler__sim2c_300(void);
static NODE *func__compiler__sim2c_301;
static void entry__compiler__sim2c_301(void);
static FRAME_INFO frame__compiler__sim2c_301 = {2, {"generated_top_level_variable_names", "txt"}};
static void cont__compiler__sim2c_302(void);
static void cont__compiler__sim2c_303(void);
static NODE *func__compiler__sim2c_304;
static void entry__compiler__sim2c_304(void);
static FRAME_INFO frame__compiler__sim2c_304 = {3, {"args", "generated_top_level_variable_declarations", "txt"}};
static void cont__compiler__sim2c_305(void);
static NODE *func__compiler__sim2c_306;
static void entry__compiler__sim2c_306(void);
static FRAME_INFO frame__compiler__sim2c_306 = {2, {"generated_top_level_variable_declarations", "txt"}};
static void cont__compiler__sim2c_307(void);
static void cont__compiler__sim2c_308(void);
static NODE *func__compiler__sim2c_309;
static void entry__compiler__sim2c_309(void);
static FRAME_INFO frame__compiler__sim2c_309 = {3, {"args", "generated_global_variable_declarations", "txt"}};
static void cont__compiler__sim2c_310(void);
static NODE *func__compiler__sim2c_311;
static void entry__compiler__sim2c_311(void);
static FRAME_INFO frame__compiler__sim2c_311 = {2, {"generated_global_variable_declarations", "txt"}};
static void cont__compiler__sim2c_312(void);
static void cont__compiler__sim2c_313(void);
static NODE *func__compiler__sim2c_314;
static void entry__compiler__sim2c_314(void);
static FRAME_INFO frame__compiler__sim2c_314 = {3, {"args", "generated_continuation_table", "txt"}};
static void cont__compiler__sim2c_315(void);
static NODE *func__compiler__sim2c_316;
static void entry__compiler__sim2c_316(void);
static FRAME_INFO frame__compiler__sim2c_316 = {2, {"generated_continuation_table", "txt"}};
static void cont__compiler__sim2c_317(void);
static void cont__compiler__sim2c_318(void);
static NODE *func__compiler__sim2c_319;
static void entry__compiler__sim2c_319(void);
static FRAME_INFO frame__compiler__sim2c_319 = {3, {"args", "generated_delayed_continuation_table", "txt"}};
static void cont__compiler__sim2c_320(void);
static NODE *func__compiler__sim2c_321;
static void entry__compiler__sim2c_321(void);
static FRAME_INFO frame__compiler__sim2c_321 = {2, {"generated_delayed_continuation_table", "txt"}};
static void cont__compiler__sim2c_322(void);
static void cont__compiler__sim2c_323(void);
static NODE *func__compiler__sim2c_324;
static void entry__compiler__sim2c_324(void);
static FRAME_INFO frame__compiler__sim2c_324 = {3, {"args", "generated_functions", "txt"}};
static void cont__compiler__sim2c_325(void);
static NODE *func__compiler__sim2c_326;
static void entry__compiler__sim2c_326(void);
static FRAME_INFO frame__compiler__sim2c_326 = {2, {"generated_functions", "txt"}};
static void cont__compiler__sim2c_327(void);
static void cont__compiler__sim2c_328(void);
static NODE *func__compiler__sim2c_329;
static void entry__compiler__sim2c_329(void);
static FRAME_INFO frame__compiler__sim2c_329 = {3, {"args", "generated_phase_1", "txt"}};
static void cont__compiler__sim2c_330(void);
static NODE *func__compiler__sim2c_331;
static void entry__compiler__sim2c_331(void);
static FRAME_INFO frame__compiler__sim2c_331 = {2, {"generated_phase_1", "txt"}};
static void cont__compiler__sim2c_332(void);
static void cont__compiler__sim2c_333(void);
static NODE *func__compiler__sim2c_334;
static void entry__compiler__sim2c_334(void);
static FRAME_INFO frame__compiler__sim2c_334 = {3, {"args", "generated_phase_2", "txt"}};
static void cont__compiler__sim2c_335(void);
static NODE *func__compiler__sim2c_336;
static void entry__compiler__sim2c_336(void);
static FRAME_INFO frame__compiler__sim2c_336 = {2, {"generated_phase_2", "txt"}};
static void cont__compiler__sim2c_337(void);
static void cont__compiler__sim2c_338(void);
static NODE *func__compiler__sim2c_339;
static void entry__compiler__sim2c_339(void);
static FRAME_INFO frame__compiler__sim2c_339 = {3, {"args", "generated_phase_3", "txt"}};
static void cont__compiler__sim2c_340(void);
static NODE *func__compiler__sim2c_341;
static void entry__compiler__sim2c_341(void);
static FRAME_INFO frame__compiler__sim2c_341 = {2, {"generated_phase_3", "txt"}};
static void cont__compiler__sim2c_342(void);
static void cont__compiler__sim2c_343(void);
static NODE *func__compiler__sim2c_344;
static void entry__compiler__sim2c_344(void);
static FRAME_INFO frame__compiler__sim2c_344 = {3, {"args", "generated_phase_4", "txt"}};
static void cont__compiler__sim2c_345(void);
static NODE *func__compiler__sim2c_346;
static void entry__compiler__sim2c_346(void);
static FRAME_INFO frame__compiler__sim2c_346 = {2, {"generated_phase_4", "txt"}};
static void cont__compiler__sim2c_347(void);
static void cont__compiler__sim2c_348(void);
static NODE *func__compiler__sim2c_349;
static void entry__compiler__sim2c_349(void);
static FRAME_INFO frame__compiler__sim2c_349 = {3, {"args", "generated_phase_5", "txt"}};
static void cont__compiler__sim2c_350(void);
static NODE *func__compiler__sim2c_351;
static void entry__compiler__sim2c_351(void);
static FRAME_INFO frame__compiler__sim2c_351 = {2, {"generated_phase_5", "txt"}};
static void cont__compiler__sim2c_352(void);
static void cont__compiler__sim2c_353(void);
static NODE *func__compiler__sim2c_354;
static void entry__compiler__sim2c_354(void);
static FRAME_INFO frame__compiler__sim2c_354 = {3, {"args", "generated_phase_6", "txt"}};
static void cont__compiler__sim2c_355(void);
static NODE *func__compiler__sim2c_356;
static void entry__compiler__sim2c_356(void);
static FRAME_INFO frame__compiler__sim2c_356 = {2, {"generated_phase_6", "txt"}};
static void cont__compiler__sim2c_357(void);
static void cont__compiler__sim2c_358(void);
static NODE *func__compiler__sim2c_359;
static void entry__compiler__sim2c_359(void);
static FRAME_INFO frame__compiler__sim2c_359 = {3, {"name", "literal", "used_literals"}};
static NODE *func__compiler__sim2c_360;
static void entry__compiler__sim2c_360(void);
static FRAME_INFO frame__compiler__sim2c_360 = {3, {"used_literals", "name", "literal"}};
static void cont__compiler__sim2c_361(void);
static void cont__compiler__sim2c_362(void);
static NODE *func__compiler__sim2c_363;
static void entry__compiler__sim2c_363(void);
static FRAME_INFO frame__compiler__sim2c_363 = {3, {"args", "generated_collections", "txt"}};
static void cont__compiler__sim2c_364(void);
static NODE *func__compiler__sim2c_365;
static void entry__compiler__sim2c_365(void);
static FRAME_INFO frame__compiler__sim2c_365 = {2, {"generated_collections", "txt"}};
static void cont__compiler__sim2c_366(void);
static void cont__compiler__sim2c_367(void);
static NODE *func__compiler__sim2c_368;
static void entry__compiler__sim2c_368(void);
static FRAME_INFO frame__compiler__sim2c_368 = {3, {"args", "delayed_statements", "txt"}};
static void cont__compiler__sim2c_369(void);
static NODE *func__compiler__sim2c_370;
static void entry__compiler__sim2c_370(void);
static FRAME_INFO frame__compiler__sim2c_370 = {2, {"delayed_statements", "txt"}};
static void cont__compiler__sim2c_371(void);
static void cont__compiler__sim2c_372(void);
static NODE *func__compiler__sim2c_373;
static void entry__compiler__sim2c_373(void);
static FRAME_INFO frame__compiler__sim2c_373 = {2, {"ident", "need"}};
static NODE *string__405aee03eb306008;
static void cont__compiler__sim2c_375(void);
static NODE *func__compiler__sim2c_376;
static void entry__compiler__sim2c_376(void);
static FRAME_INFO frame__compiler__sim2c_376 = {3, {"ident", "need", "name"}};
static void cont__compiler__sim2c_377(void);
static void cont__compiler__sim2c_378(void);
static NODE *string__c44673b4643f1172;
static void cont__compiler__sim2c_380(void);
static NODE *func__compiler__sim2c_381;
static void entry__compiler__sim2c_381(void);
static FRAME_INFO frame__compiler__sim2c_381 = {6, {"stmt_idx", "defs", "return__6", "generated_code", "all_actions", "code"}};
static NODE *func__compiler__sim2c_382;
static void entry__compiler__sim2c_382(void);
static FRAME_INFO frame__compiler__sim2c_382 = {1, {"defs"}};
static NODE *func__compiler__sim2c_383;
static void entry__compiler__sim2c_383(void);
static FRAME_INFO frame__compiler__sim2c_383 = {2, {"definition", "source"}};
static void cont__compiler__sim2c_384(void);
static NODE *func__compiler__sim2c_385;
static void entry__compiler__sim2c_385(void);
static FRAME_INFO frame__compiler__sim2c_385 = {2, {"source", "definition"}};
static void cont__compiler__sim2c_386(void);
static void cont__compiler__sim2c_387(void);
static void cont__compiler__sim2c_388(void);
static void cont__compiler__sim2c_389(void);
static NODE *func__compiler__sim2c_390;
static void entry__compiler__sim2c_390(void);
static FRAME_INFO frame__compiler__sim2c_390 = {1, {"definition"}};
static NODE *func__compiler__sim2c_391;
static void entry__compiler__sim2c_391(void);
static FRAME_INFO frame__compiler__sim2c_391 = {5, {"return__5", "definition", "source", "name", "attribute"}};
static void cont__compiler__sim2c_392(void);
static void cont__compiler__sim2c_393(void);
static void cont__compiler__sim2c_394(void);
static void cont__compiler__sim2c_395(void);
static NODE *func__compiler__sim2c_396;
static void entry__compiler__sim2c_396(void);
static FRAME_INFO frame__compiler__sim2c_396 = {2, {"name", "attribute"}};
static void cont__compiler__sim2c_397(void);
static void cont__compiler__sim2c_398(void);
static void cont__compiler__sim2c_399(void);
static void cont__compiler__sim2c_400(void);
static void cont__compiler__sim2c_401(void);
static void cont__compiler__sim2c_402(void);
static NODE *func__compiler__sim2c_403;
static void entry__compiler__sim2c_403(void);
static FRAME_INFO frame__compiler__sim2c_403 = {1, {"source"}};
static void cont__compiler__sim2c_404(void);
static void cont__compiler__sim2c_405(void);
static NODE *func__compiler__sim2c_406;
static void entry__compiler__sim2c_406(void);
static FRAME_INFO frame__compiler__sim2c_406 = {2, {"definition", "source"}};
static void cont__compiler__sim2c_407(void);
static NODE *func__compiler__sim2c_408;
static void entry__compiler__sim2c_408(void);
static FRAME_INFO frame__compiler__sim2c_408 = {2, {"definition", "source"}};
static void cont__compiler__sim2c_409(void);
static NODE *func__compiler__sim2c_410;
static void entry__compiler__sim2c_410(void);
static FRAME_INFO frame__compiler__sim2c_410 = {2, {"definition", "source"}};
static NODE *func__compiler__sim2c_411;
static void entry__compiler__sim2c_411(void);
static FRAME_INFO frame__compiler__sim2c_411 = {2, {"definition", "source"}};
static void cont__compiler__sim2c_412(void);
static void cont__compiler__sim2c_413(void);
static NODE *func__compiler__sim2c_414;
static void entry__compiler__sim2c_414(void);
static FRAME_INFO frame__compiler__sim2c_414 = {2, {"definition", "source"}};
static NODE *func__compiler__sim2c_415;
static void entry__compiler__sim2c_415(void);
static FRAME_INFO frame__compiler__sim2c_415 = {2, {"definition", "source"}};
static NODE *func__compiler__sim2c_416;
static void entry__compiler__sim2c_416(void);
static FRAME_INFO frame__compiler__sim2c_416 = {2, {"definition", "source"}};
static void cont__compiler__sim2c_417(void);
static void cont__compiler__sim2c_418(void);
static void cont__compiler__sim2c_419(void);
static void cont__compiler__sim2c_420(void);
static NODE *func__compiler__sim2c_421;
static void entry__compiler__sim2c_421(void);
static FRAME_INFO frame__compiler__sim2c_421 = {0, {}};
static void cont__compiler__sim2c_422(void);
static NODE *func__compiler__sim2c_423;
static void entry__compiler__sim2c_423(void);
static FRAME_INFO frame__compiler__sim2c_423 = {2, {"generated_code", "code"}};
static void cont__compiler__sim2c_424(void);
static void cont__compiler__sim2c_425(void);
static void cont__compiler__sim2c_426(void);
static void cont__compiler__sim2c_427(void);
static NODE *string__c050814d5faecc7a;
static void cont__compiler__sim2c_429(void);
static NODE *func__compiler__sim2c_430;
static void entry__compiler__sim2c_430(void);
static FRAME_INFO frame__compiler__sim2c_430 = {7, {"return__7", "is_main", "max_temp_idx", "mangle_filename", "generated_code", "all_actions", "code"}};
static NODE *func__compiler__sim2c_431;
static void entry__compiler__sim2c_431(void);
static FRAME_INFO frame__compiler__sim2c_431 = {3, {"is_main", "max_temp_idx", "mangle_filename"}};
static NODE *func__compiler__sim2c_432;
static void entry__compiler__sim2c_432(void);
static FRAME_INFO frame__compiler__sim2c_432 = {1, {"max_temp_idx"}};
static NODE *string__295c7d0427bb24d8;
static void cont__compiler__sim2c_434(void);
static void cont__compiler__sim2c_435(void);
static NODE *func__compiler__sim2c_436;
static void entry__compiler__sim2c_436(void);
static FRAME_INFO frame__compiler__sim2c_436 = {1, {"max_temp_idx"}};
static NODE *string__41028e5a9545c479;
static NODE *string__2d7981f4e6402bfe;
static void cont__compiler__sim2c_439(void);
static NODE *func__compiler__sim2c_440;
static void entry__compiler__sim2c_440(void);
static FRAME_INFO frame__compiler__sim2c_440 = {1, {"max_temp_idx"}};
static NODE *string__4594ae5b852cb87f;
static NODE *string__3794a6c106b6c980;
static void cont__compiler__sim2c_443(void);
static void cont__compiler__sim2c_444(void);
static NODE *string__8eebb379fdb22853;
static NODE *string__bbab7a959fd798d;
static void cont__compiler__sim2c_447(void);
static void cont__compiler__sim2c_448(void);
static NODE *func__compiler__sim2c_449;
static void entry__compiler__sim2c_449(void);
static FRAME_INFO frame__compiler__sim2c_449 = {4, {"name", "info", "mangle_filename", "continuation"}};
static void cont__compiler__sim2c_450(void);
static void cont__compiler__sim2c_451(void);
static void cont__compiler__sim2c_452(void);
static NODE *string__ca75d5c2b6ab3b0c;
static NODE *string__3fab381eeea84c47;
static NODE *string__b40af3cb5d887d33;
static void cont__compiler__sim2c_456(void);
static void cont__compiler__sim2c_457(void);
static void cont__compiler__sim2c_458(void);
static NODE *string__6a214ac420f089ff;
static void cont__compiler__sim2c_460(void);
static void cont__compiler__sim2c_461(void);
static NODE *func__compiler__sim2c_462;
static void entry__compiler__sim2c_462(void);
static FRAME_INFO frame__compiler__sim2c_462 = {2, {"generated_code", "code"}};
static void cont__compiler__sim2c_463(void);
static void cont__compiler__sim2c_464(void);
static void cont__compiler__sim2c_465(void);
static void cont__compiler__sim2c_466(void);
static void cont__compiler__sim2c_467(void);
static NODE *func__compiler__sim2c_468;
static void entry__compiler__sim2c_468(void);
static FRAME_INFO frame__compiler__sim2c_468 = {7, {"stmt_idx", "stmts", "return__8", "def_count", "generated_code", "all_actions", "code"}};
static void cont__compiler__sim2c_469(void);
static void cont__compiler__sim2c_470(void);
static NODE *func__compiler__sim2c_471;
static void entry__compiler__sim2c_471(void);
static FRAME_INFO frame__compiler__sim2c_471 = {1, {"stmts"}};
static NODE *func__compiler__sim2c_472;
static void entry__compiler__sim2c_472(void);
static FRAME_INFO frame__compiler__sim2c_472 = {1, {"stmt"}};
static void cont__compiler__sim2c_473(void);
static void cont__compiler__sim2c_474(void);
static void cont__compiler__sim2c_475(void);
static NODE *func__compiler__sim2c_476;
static void entry__compiler__sim2c_476(void);
static FRAME_INFO frame__compiler__sim2c_476 = {0, {}};
static void cont__compiler__sim2c_477(void);
static NODE *func__compiler__sim2c_478;
static void entry__compiler__sim2c_478(void);
static FRAME_INFO frame__compiler__sim2c_478 = {2, {"generated_code", "code"}};
static void cont__compiler__sim2c_479(void);
static void cont__compiler__sim2c_480(void);
static void cont__compiler__sim2c_481(void);
static void cont__compiler__sim2c_482(void);
static NODE *func__compiler__sim2c_483;
static void entry__compiler__sim2c_483(void);
static FRAME_INFO frame__compiler__sim2c_483 = {5, {"return__9", "is_main", "generated_code", "all_actions", "code"}};
static NODE *func__compiler__sim2c_484;
static void entry__compiler__sim2c_484(void);
static FRAME_INFO frame__compiler__sim2c_484 = {1, {"is_main"}};
static NODE *func__compiler__sim2c_485;
static void entry__compiler__sim2c_485(void);
static FRAME_INFO frame__compiler__sim2c_485 = {0, {}};
static NODE *string__5c9d8231ad282235;
static NODE *func__compiler__sim2c_487;
static void entry__compiler__sim2c_487(void);
static FRAME_INFO frame__compiler__sim2c_487 = {0, {}};
static NODE *string__a61426acc3f10dab;
static void cont__compiler__sim2c_489(void);
static void cont__compiler__sim2c_490(void);
static NODE *func__compiler__sim2c_491;
static void entry__compiler__sim2c_491(void);
static FRAME_INFO frame__compiler__sim2c_491 = {2, {"generated_code", "code"}};
static void cont__compiler__sim2c_492(void);
static void cont__compiler__sim2c_493(void);
static void cont__compiler__sim2c_494(void);
static void cont__compiler__sim2c_495(void);
static NODE *func__compiler__sim2c_496;
static void entry__compiler__sim2c_496(void);
static FRAME_INFO frame__compiler__sim2c_496 = {1, {"stmt_actions"}};
static NODE *func__compiler__sim2c_497;
static void entry__compiler__sim2c_497(void);
static FRAME_INFO frame__compiler__sim2c_497 = {1, {"action"}};
static void cont__compiler__sim2c_498(void);
static NODE *func__compiler__sim2c_499;
static void entry__compiler__sim2c_499(void);
static FRAME_INFO frame__compiler__sim2c_499 = {2, {"name", "info"}};
static NODE *string__58cb04c59ab3549a;
static void cont__compiler__sim2c_501(void);
static void cont__compiler__sim2c_502(void);
static NODE *func__compiler__sim2c_503;
static void entry__compiler__sim2c_503(void);
static FRAME_INFO frame__compiler__sim2c_503 = {1, {"name"}};
static NODE *string__7d8c250ccd5bbd65;
static void cont__compiler__sim2c_505(void);
static void cont__compiler__sim2c_506(void);
static NODE *func__compiler__sim2c_507;
static void entry__compiler__sim2c_507(void);
static FRAME_INFO frame__compiler__sim2c_507 = {1, {"filemask"}};
static NODE *string__6d8c238ccd0b3d65;
static void cont__compiler__sim2c_509(void);
static void cont__compiler__sim2c_510(void);
static void cont__compiler__sim2c_511(void);
static void cont__compiler__sim2c_512(void);
static NODE *string__3ae3b0d72c49c8db;
static void cont__compiler__sim2c_514(void);
static NODE *func__compiler__sim2c_515;
static void entry__compiler__sim2c_515(void);
static FRAME_INFO frame__compiler__sim2c_515 = {0, {}};
static NODE *string__72c4a8d406a50228;
static void cont__compiler__sim2c_517(void);
static NODE *string__7cc4ad5406a55228;
static void cont__compiler__sim2c_519(void);
static void cont__compiler__sim2c_520(void);
static NODE *func__compiler__sim2c_521;
static void entry__compiler__sim2c_521(void);
static FRAME_INFO frame__compiler__sim2c_521 = {1, {"name"}};
static NODE *string__3d6a095dad2a247d;
static NODE *string__578a5af303e9cdf;
static void cont__compiler__sim2c_524(void);
static void cont__compiler__sim2c_525(void);
static void cont__compiler__sim2c_526(void);
static void cont__compiler__sim2c_527(void);
static NODE *string__36e833feb0906b55;
static void cont__compiler__sim2c_529(void);
static void cont__compiler__sim2c_530(void);
static NODE *func__compiler__sim2c_531;
static void entry__compiler__sim2c_531(void);
static FRAME_INFO frame__compiler__sim2c_531 = {0, {}};
static NODE *string__a047b2b18829c385;
static void cont__compiler__sim2c_533(void);
static void cont__compiler__sim2c_534(void);
static NODE *func__compiler__sim2c_535;
static void entry__compiler__sim2c_535(void);
static FRAME_INFO frame__compiler__sim2c_535 = {0, {}};
static NODE *string__64c4ac5406a5d228;
static void cont__compiler__sim2c_537(void);
static void cont__compiler__sim2c_538(void);
static NODE *func__compiler__sim2c_539;
static void entry__compiler__sim2c_539(void);
static FRAME_INFO frame__compiler__sim2c_539 = {0, {}};
static NODE *string__b0f44c3748f83ed0;
static void cont__compiler__sim2c_541(void);
static NODE *string__96a80854500bbe37;
static void cont__compiler__sim2c_543(void);
static NODE *func__compiler__sim2c_544;
static void entry__compiler__sim2c_544(void);
static FRAME_INFO frame__compiler__sim2c_544 = {2, {"name", "info"}};
static void cont__compiler__sim2c_545(void);
static void cont__compiler__sim2c_546(void);
static NODE *func__compiler__sim2c_547;
static void entry__compiler__sim2c_547(void);
static FRAME_INFO frame__compiler__sim2c_547 = {1, {"name"}};
static NODE *string__dd59fa996655f7be;
static NODE *string__578a5af303e9cda;
static void cont__compiler__sim2c_550(void);
static void cont__compiler__sim2c_551(void);
static NODE *string__7bc4c42d1b67ee3a;
static void cont__compiler__sim2c_553(void);
static void cont__compiler__sim2c_554(void);
static void cont__compiler__sim2c_555(void);
static void cont__compiler__sim2c_556(void);
static NODE *func__compiler__sim2c_557;
static void entry__compiler__sim2c_557(void);
static FRAME_INFO frame__compiler__sim2c_557 = {1, {"name"}};
static NODE *string__f144f4e2b96df7e3;
static void cont__compiler__sim2c_559(void);
static void cont__compiler__sim2c_560(void);
static void cont__compiler__sim2c_561(void);
static void cont__compiler__sim2c_562(void);
static NODE *func__compiler__sim2c_563;
static void entry__compiler__sim2c_563(void);
static FRAME_INFO frame__compiler__sim2c_563 = {1, {"name"}};
static NODE *string__7bc4c42d1b4eae3a;
static void cont__compiler__sim2c_565(void);
static void cont__compiler__sim2c_566(void);
static void cont__compiler__sim2c_567(void);
static void cont__compiler__sim2c_568(void);
static NODE *func__compiler__sim2c_569;
static void entry__compiler__sim2c_569(void);
static FRAME_INFO frame__compiler__sim2c_569 = {1, {"name"}};
static NODE *string__16f790c158cdffe3;
static void cont__compiler__sim2c_571(void);
static void cont__compiler__sim2c_572(void);
static NODE *string__ff4edce8b0a2fa27;
static void cont__compiler__sim2c_574(void);
static void cont__compiler__sim2c_575(void);
static void cont__compiler__sim2c_576(void);
static NODE *string__b07009729763a0f0;
static void cont__compiler__sim2c_578(void);
static NODE *string__75573d7e471fdc32;
static void cont__compiler__sim2c_580(void);
static void cont__compiler__sim2c_581(void);
static void cont__compiler__sim2c_582(void);
static NODE *func__compiler__sim2c_583;
static void entry__compiler__sim2c_583(void);
static FRAME_INFO frame__compiler__sim2c_583 = {1, {"generated_top_level_variable_names"}};
static void cont__compiler__sim2c_584(void);
static void cont__compiler__sim2c_585(void);
static void cont__compiler__sim2c_586(void);
static NODE *string__fa727015ff16bc6;
static void cont__compiler__sim2c_588(void);
static void cont__compiler__sim2c_589(void);
static NODE *func__compiler__sim2c_590;
static void entry__compiler__sim2c_590(void);
static FRAME_INFO frame__compiler__sim2c_590 = {0, {}};
static NODE *string__c3452dad239e6464;
static NODE *func__compiler__sim2c_592;
static void entry__compiler__sim2c_592(void);
static FRAME_INFO frame__compiler__sim2c_592 = {0, {}};
static NODE *string__1f74a3bba8d254fe;
static NODE *string__a1240cd997f230c1;
static void cont__compiler__sim2c_595(void);
static void cont__compiler__sim2c_596(void);
static NODE *string__b4688827b8af4941;
static void cont__compiler__sim2c_598(void);
static void cont__compiler__sim2c_599(void);
static void cont__compiler__sim2c_600(void);
static void cont__compiler__sim2c_601(void);
static NODE *func__compiler__sim2c_602;
static void entry__compiler__sim2c_602(void);
static FRAME_INFO frame__compiler__sim2c_602 = {1, {"generated_continuation_table"}};
static void cont__compiler__sim2c_603(void);
static void cont__compiler__sim2c_604(void);
static void cont__compiler__sim2c_605(void);
static NODE *string__380aff8b5e307d33;
static void cont__compiler__sim2c_607(void);
static NODE *string__817a259dab23f435;
static void cont__compiler__sim2c_609(void);
static NODE *func__compiler__sim2c_610;
static void entry__compiler__sim2c_610(void);
static FRAME_INFO frame__compiler__sim2c_610 = {0, {}};
static NODE *func__compiler__sim2c_611;
static void entry__compiler__sim2c_611(void);
static FRAME_INFO frame__compiler__sim2c_611 = {2, {"name", "node"}};
static void cont__compiler__sim2c_612(void);
static NODE *string__2d7981f4e6082be5;
static NODE *string__578a5af303e9cc1;
static NODE *string__2d7981f4e6d02bcf;
static void cont__compiler__sim2c_616(void);
static void cont__compiler__sim2c_617(void);
static void cont__compiler__sim2c_618(void);
static void cont__compiler__sim2c_619(void);
static NODE *func__compiler__sim2c_620;
static void entry__compiler__sim2c_620(void);
static FRAME_INFO frame__compiler__sim2c_620 = {2, {"name", "literal"}};
static NODE *string__cb6a78473f66a6a1;
static void cont__compiler__sim2c_622(void);
static void cont__compiler__sim2c_623(void);
static NODE *string__44a800d7e66fda5b;
static void cont__compiler__sim2c_625(void);
static NODE *func__compiler__sim2c_626;
static void entry__compiler__sim2c_626(void);
static FRAME_INFO frame__compiler__sim2c_626 = {1, {"name"}};
static NODE *string__fa730415f296bee;
static NODE *string__fa730c15f496bc6;
static void cont__compiler__sim2c_629(void);
static void cont__compiler__sim2c_630(void);
static NODE *string__5e3d918a06749390;
static NODE *string__b90701ef69cd6166;
static void cont__compiler__sim2c_633(void);
static void cont__compiler__sim2c_634(void);
static void cont__compiler__sim2c_635(void);
static NODE *func__compiler__sim2c_636;
static void entry__compiler__sim2c_636(void);
static FRAME_INFO frame__compiler__sim2c_636 = {2, {"filename", "depth"}};
static void cont__compiler__sim2c_637(void);
static void cont__compiler__sim2c_638(void);
static void cont__compiler__sim2c_639(void);
static NODE *string__9c11f7a3e8641900;
static NODE *string__2d7981f4e6182bec;
static void cont__compiler__sim2c_642(void);
static NODE *func__compiler__sim2c_643;
static void entry__compiler__sim2c_643(void);
static FRAME_INFO frame__compiler__sim2c_643 = {0, {}};
static NODE *string__2d7981f4e6682be5;
static void cont__compiler__sim2c_645(void);
static NODE *string__d1bc6cafcb964c0d;
static void cont__compiler__sim2c_647(void);
static NODE *func__compiler__sim2c_648;
static void entry__compiler__sim2c_648(void);
static FRAME_INFO frame__compiler__sim2c_648 = {4, {"name", "info", "mangle_filename", "fname"}};
static void cont__compiler__sim2c_649(void);
static NODE *string__7cb40b96062f3614;
static NODE *string__4b1f5385e2b9ec5c;
static NODE *string__4b1f5345e2b9ec5c;
static NODE *string__4b1f5305e2b9ec5c;
static NODE *string__4b1f52c5e2b9ec5c;
static NODE *string__4b1f5285e2b9ec5c;
static NODE *string__4b1f5245e2b9ec5c;
static NODE *string__fa3f5235fd3e2424;
static void cont__compiler__sim2c_658(void);
static void cont__compiler__sim2c_659(void);
static void cont__compiler__sim2c_660(void);
static void cont__compiler__sim2c_661(void);
static NODE *string__bcb42196062f3614;
static void cont__compiler__sim2c_663(void);
static void cont__compiler__sim2c_664(void);
static void cont__compiler__sim2c_665(void);
static NODE *string__2d7981f4e4e02bcf;
static void cont__compiler__sim2c_667(void);
static NODE *func__compiler__sim2c_668;
static void entry__compiler__sim2c_668(void);
static FRAME_INFO frame__compiler__sim2c_668 = {0, {}};
static NODE *string__25aa47136a75b74b;
static NODE *func__compiler__sim2c_670;
static void entry__compiler__sim2c_670(void);
static FRAME_INFO frame__compiler__sim2c_670 = {0, {}};
static NODE *string__1aafb345f496a1;
static NODE *string__d7e0d1a7b944caae;
static void cont__compiler__sim2c_673(void);
static void cont__compiler__sim2c_674(void);
static NODE *func__compiler__sim2c_675;
static void entry__compiler__sim2c_675(void);
static FRAME_INFO frame__compiler__sim2c_675 = {4, {"name", "info", "mangle_filename", "mangled_name"}};
static void cont__compiler__sim2c_676(void);
static NODE *string__fedb25123ef1fa6f;
static NODE *string__fa732415f616bf7;
static void cont__compiler__sim2c_679(void);
static void cont__compiler__sim2c_680(void);
static NODE *string__6759f0f7c95235d;
static void cont__compiler__sim2c_682(void);
static NODE *func__compiler__sim2c_683;
static void entry__compiler__sim2c_683(void);
static FRAME_INFO frame__compiler__sim2c_683 = {1, {"namespace"}};
static NODE *string__d93952e55b2e5d9;
static NODE *string__860afb0b5fb87d33;
static void cont__compiler__sim2c_686(void);
static void cont__compiler__sim2c_687(void);
static void cont__compiler__sim2c_688(void);
static NODE *func__compiler__sim2c_689;
static void entry__compiler__sim2c_689(void);
static FRAME_INFO frame__compiler__sim2c_689 = {0, {}};
static NODE *string__f5b495312d83add5;
static NODE *func__compiler__sim2c_691;
static void entry__compiler__sim2c_691(void);
static FRAME_INFO frame__compiler__sim2c_691 = {0, {}};
static NODE *string__b9a3b0acf1dfe8ab;
static NODE *string__d4e0c9a7b944caae;
static void cont__compiler__sim2c_694(void);
static void cont__compiler__sim2c_695(void);
static NODE *func__compiler__sim2c_696;
static void entry__compiler__sim2c_696(void);
static FRAME_INFO frame__compiler__sim2c_696 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_697(void);
static NODE *string__fedb25d23ef1fa6f;
static void cont__compiler__sim2c_699(void);
static void cont__compiler__sim2c_700(void);
static NODE *string__f93d0720893942d5;
static void cont__compiler__sim2c_702(void);
static void cont__compiler__sim2c_703(void);
static NODE *func__compiler__sim2c_704;
static void entry__compiler__sim2c_704(void);
static FRAME_INFO frame__compiler__sim2c_704 = {2, {"name", "literal"}};
static NODE *string__fa730415fc16bec;
static void cont__compiler__sim2c_706(void);
static void cont__compiler__sim2c_707(void);
static NODE *func__compiler__sim2c_708;
static void entry__compiler__sim2c_708(void);
static FRAME_INFO frame__compiler__sim2c_708 = {1, {"literal"}};
static void cont__compiler__sim2c_709(void);
static NODE *func__compiler__sim2c_710;
static void entry__compiler__sim2c_710(void);
static FRAME_INFO frame__compiler__sim2c_710 = {2, {"literal", "value"}};
static void cont__compiler__sim2c_711(void);
static void cont__compiler__sim2c_712(void);
static void cont__compiler__sim2c_713(void);
static NODE *string__2d7981f4e6882bbd;
static void cont__compiler__sim2c_715(void);
static void cont__compiler__sim2c_716(void);
static NODE *func__compiler__sim2c_717;
static void entry__compiler__sim2c_717(void);
static FRAME_INFO frame__compiler__sim2c_717 = {1, {"value"}};
static void cont__compiler__sim2c_718(void);
static void cont__compiler__sim2c_719(void);
static void cont__compiler__sim2c_720(void);
static NODE *func__compiler__sim2c_721;
static void entry__compiler__sim2c_721(void);
static FRAME_INFO frame__compiler__sim2c_721 = {1, {"value"}};
static NODE *string__ecd034ad7215125;
static void cont__compiler__sim2c_723(void);
static NODE *func__compiler__sim2c_724;
static void entry__compiler__sim2c_724(void);
static FRAME_INFO frame__compiler__sim2c_724 = {2, {"value", "int_val"}};
static void cont__compiler__sim2c_725(void);
static NODE *func__compiler__sim2c_726;
static void entry__compiler__sim2c_726(void);
static FRAME_INFO frame__compiler__sim2c_726 = {1, {"int_val"}};
static void cont__compiler__sim2c_727(void);
static void cont__compiler__sim2c_728(void);
static NODE *func__compiler__sim2c_729;
static void entry__compiler__sim2c_729(void);
static FRAME_INFO frame__compiler__sim2c_729 = {1, {"int_val"}};
static NODE *string__22891489d598e125;
static NODE *string__680afb0b5fb87d33;
static void cont__compiler__sim2c_732(void);
static NODE *func__compiler__sim2c_733;
static void entry__compiler__sim2c_733(void);
static FRAME_INFO frame__compiler__sim2c_733 = {1, {"int_val"}};
static void cont__compiler__sim2c_734(void);
static void cont__compiler__sim2c_735(void);
static NODE *func__compiler__sim2c_736;
static void entry__compiler__sim2c_736(void);
static FRAME_INFO frame__compiler__sim2c_736 = {1, {"int_val"}};
static NODE *string__228915c9d5a8e125;
static NODE *string__1f441a036092dd;
static void cont__compiler__sim2c_739(void);
static NODE *func__compiler__sim2c_740;
static void entry__compiler__sim2c_740(void);
static FRAME_INFO frame__compiler__sim2c_740 = {1, {"value"}};
static NODE *string__c470b0c3df48bfe1;
static void cont__compiler__sim2c_742(void);
static NODE *func__compiler__sim2c_743;
static void entry__compiler__sim2c_743(void);
static FRAME_INFO frame__compiler__sim2c_743 = {1, {"literal"}};
static void cont__compiler__sim2c_744(void);
static NODE *func__compiler__sim2c_745;
static void entry__compiler__sim2c_745(void);
static FRAME_INFO frame__compiler__sim2c_745 = {1, {"literal"}};
static void cont__compiler__sim2c_746(void);
static void cont__compiler__sim2c_747(void);
static NODE *string__2666ac8409f84460;
static void cont__compiler__sim2c_749(void);
static void cont__compiler__sim2c_750(void);
static void cont__compiler__sim2c_751(void);
static NODE *func__compiler__sim2c_752;
static void entry__compiler__sim2c_752(void);
static FRAME_INFO frame__compiler__sim2c_752 = {0, {}};
static NODE *string__cb22ed554b280fb1;
static NODE *func__compiler__sim2c_754;
static void entry__compiler__sim2c_754(void);
static FRAME_INFO frame__compiler__sim2c_754 = {0, {}};
static NODE *string__b9a3b0edf1dfe8ab;
static NODE *string__d5e0c1a7b944caae;
static void cont__compiler__sim2c_757(void);
static void cont__compiler__sim2c_758(void);
static NODE *func__compiler__sim2c_759;
static void entry__compiler__sim2c_759(void);
static FRAME_INFO frame__compiler__sim2c_759 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_760(void);
static NODE *string__fedb25923ef1fa6f;
static void cont__compiler__sim2c_762(void);
static void cont__compiler__sim2c_763(void);
static NODE *string__f647f212951f31f8;
static void cont__compiler__sim2c_765(void);
static void cont__compiler__sim2c_766(void);
static void cont__compiler__sim2c_767(void);
static NODE *func__compiler__sim2c_768;
static void entry__compiler__sim2c_768(void);
static FRAME_INFO frame__compiler__sim2c_768 = {0, {}};
static NODE *string__19b03dcd2fdc791;
static NODE *func__compiler__sim2c_770;
static void entry__compiler__sim2c_770(void);
static FRAME_INFO frame__compiler__sim2c_770 = {0, {}};
static NODE *string__b9a3b12af1dfe8ab;
static NODE *string__d2e0f9a7b944caae;
static void cont__compiler__sim2c_773(void);
static void cont__compiler__sim2c_774(void);
static NODE *func__compiler__sim2c_775;
static void entry__compiler__sim2c_775(void);
static FRAME_INFO frame__compiler__sim2c_775 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_776(void);
static NODE *string__fedb24523ef1fa6f;
static void cont__compiler__sim2c_778(void);
static void cont__compiler__sim2c_779(void);
static void cont__compiler__sim2c_780(void);
static void cont__compiler__sim2c_781(void);
static NODE *func__compiler__sim2c_782;
static void entry__compiler__sim2c_782(void);
static FRAME_INFO frame__compiler__sim2c_782 = {2, {"name", "info"}};
static void cont__compiler__sim2c_783(void);
static void cont__compiler__sim2c_784(void);
static NODE *func__compiler__sim2c_785;
static void entry__compiler__sim2c_785(void);
static FRAME_INFO frame__compiler__sim2c_785 = {4, {"name", "info", "namespace", "basename"}};
static void cont__compiler__sim2c_786(void);
static NODE *func__compiler__sim2c_787;
static void entry__compiler__sim2c_787(void);
static FRAME_INFO frame__compiler__sim2c_787 = {1, {"name"}};
static void cont__compiler__sim2c_788(void);
static void cont__compiler__sim2c_789(void);
static NODE *func__compiler__sim2c_790;
static void entry__compiler__sim2c_790(void);
static FRAME_INFO frame__compiler__sim2c_790 = {0, {}};
static NODE *string__5e0ae40b5c007d75;
static void cont__compiler__sim2c_792(void);
static void cont__compiler__sim2c_793(void);
static void cont__compiler__sim2c_794(void);
static NODE *func__compiler__sim2c_795;
static void entry__compiler__sim2c_795(void);
static FRAME_INFO frame__compiler__sim2c_795 = {3, {"namespace", "basename", "name"}};
static NODE *string__82877bb737e0bc50;
static NODE *string__fa733415f296bee;
static NODE *string__65b0238fc1fb0d7a;
static NODE *string__4a0e52ffba34c725;
static void cont__compiler__sim2c_800(void);
static NODE *func__compiler__sim2c_801;
static void entry__compiler__sim2c_801(void);
static FRAME_INFO frame__compiler__sim2c_801 = {3, {"namespace", "basename", "name"}};
static NODE *string__c1145f87c6ab68aa;
static NODE *string__f681eab2d5b5e9a9;
static void cont__compiler__sim2c_804(void);
static NODE *func__compiler__sim2c_805;
static void entry__compiler__sim2c_805(void);
static FRAME_INFO frame__compiler__sim2c_805 = {3, {"namespace", "basename", "name"}};
static NODE *string__f63e3617473fc88a;
static NODE *string__6594a8f5052ca9ff;
static void cont__compiler__sim2c_808(void);
static NODE *func__compiler__sim2c_809;
static void entry__compiler__sim2c_809(void);
static FRAME_INFO frame__compiler__sim2c_809 = {3, {"namespace", "basename", "name"}};
static NODE *string__b45bfb6d6d495155;
static NODE *string__9ccb3018e8f13bec;
static void cont__compiler__sim2c_812(void);
static NODE *func__compiler__sim2c_813;
static void entry__compiler__sim2c_813(void);
static FRAME_INFO frame__compiler__sim2c_813 = {3, {"namespace", "basename", "name"}};
static NODE *string__5b5ec7878e89a218;
static void cont__compiler__sim2c_815(void);
static void cont__compiler__sim2c_816(void);
static void cont__compiler__sim2c_817(void);
static NODE *func__compiler__sim2c_818;
static void entry__compiler__sim2c_818(void);
static FRAME_INFO frame__compiler__sim2c_818 = {0, {}};
static NODE *string__29050caaed294603;
static void cont__compiler__sim2c_820(void);
static NODE *func__compiler__sim2c_821;
static void entry__compiler__sim2c_821(void);
static FRAME_INFO frame__compiler__sim2c_821 = {0, {}};
static NODE *string__a9896ddd6eafadae;
static NODE *func__compiler__sim2c_823;
static void entry__compiler__sim2c_823(void);
static FRAME_INFO frame__compiler__sim2c_823 = {0, {}};
static NODE *string__b9a3b16bf1dfe8ab;
static NODE *string__d3e0f1a7b944caae;
static void cont__compiler__sim2c_826(void);
static void cont__compiler__sim2c_827(void);
static NODE *func__compiler__sim2c_828;
static void entry__compiler__sim2c_828(void);
static FRAME_INFO frame__compiler__sim2c_828 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_829(void);
static NODE *string__fedb24123ef1fa6f;
static void cont__compiler__sim2c_831(void);
static void cont__compiler__sim2c_832(void);
static void cont__compiler__sim2c_833(void);
static NODE *func__compiler__sim2c_834;
static void entry__compiler__sim2c_834(void);
static FRAME_INFO frame__compiler__sim2c_834 = {0, {}};
static NODE *string__1cd8a7b21f5517c3;
static NODE *func__compiler__sim2c_836;
static void entry__compiler__sim2c_836(void);
static FRAME_INFO frame__compiler__sim2c_836 = {0, {}};
static NODE *string__b9a3b1a8f1dfe8ab;
static NODE *string__d0e0e9a7b944caae;
static void cont__compiler__sim2c_839(void);
static void cont__compiler__sim2c_840(void);
static NODE *func__compiler__sim2c_841;
static void entry__compiler__sim2c_841(void);
static FRAME_INFO frame__compiler__sim2c_841 = {3, {"name", "info", "mangle_filename"}};
static void cont__compiler__sim2c_842(void);
static NODE *string__fedb24d23ef1fa6f;
static void cont__compiler__sim2c_844(void);
static void cont__compiler__sim2c_845(void);
static void cont__compiler__sim2c_846(void);
static NODE *string__476ac52a7f81f4a0;
static void cont__compiler__sim2c_848(void);
static void cont__compiler__sim2c_849(void);
static NODE *func__compiler__sim2c_850;
static void entry__compiler__sim2c_850(void);
static FRAME_INFO frame__compiler__sim2c_850 = {0, {}};
static NODE *string__3734ffa0d2ae2d12;
static void cont__compiler__sim2c_852(void);
static void cont__compiler__sim2c_853(void);
static NODE *func__compiler__sim2c_854;
static void entry__compiler__sim2c_854(void);
static FRAME_INFO frame__compiler__sim2c_854 = {1, {"filenames"}};
static void cont__compiler__sim2c_855(void);
static NODE *string__1d702a52a35b6426;
static void cont__compiler__sim2c_857(void);
static NODE *get__compiler__sim2c(void) {
  return var.compiler__sim2c;
}
static NODE *string__cc48021895f2809c;
static void cont__10_2(void);
static NODE *string__cb05e9320ae22386;
static void cont__10_4(void);
static NODE *string__17988d443223256d;
static void cont__10_6(void);
static NODE *string__76a027f311988656;
static void cont__10_8(void);
static NODE *string__58b854e1382f539f;
static void cont__10_10(void);
static NODE *string__d8272d0f8bc407b3;
static void cont__10_12(void);
static NODE *string__582190112b914cb7;
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
  {entry__compiler__print_source_3, NULL, 40, 40, 9, 17},
  {entry__compiler__print_source_4, NULL, 34, 34, 9, 27},
  {entry__compiler__print_source_6, NULL, 36, 36, 9, 33},
  {entry__compiler__print_source_8, NULL, 38, 38, 9, 34},
  {entry__compiler__print_source_2, NULL, 31, 40, 5, 18},
  {entry__compiler__print_source_1, NULL, 30, 40, 3, 19},
  {entry__compiler__eprint_source_3, NULL, 53, 53, 9, 18},
  {entry__compiler__eprint_source_4, NULL, 47, 47, 9, 28},
  {entry__compiler__eprint_source_5, NULL, 49, 49, 9, 34},
  {entry__compiler__eprint_source_6, NULL, 51, 51, 9, 35},
  {entry__compiler__eprint_source_2, NULL, 44, 53, 5, 19},
  {entry__compiler__eprint_source_1, NULL, 43, 53, 3, 20},
  {entry__compiler__generate_dispatcher_function_11, NULL, 87, 90, 26, 18},
  {cont__compiler__generate_dispatcher_function_15, &frame__compiler__generate_dispatcher_function_11, 87, 90, 7, 18},
  {entry__compiler__generate_dispatcher_function_16, NULL, 93, 93, 9, 79},
  {cont__compiler__generate_dispatcher_function_18, &frame__compiler__generate_dispatcher_function_16, 92, 93, 7, 79},
  {entry__compiler__generate_dispatcher_function_1, NULL, 66, 67, 25, 36},
  {cont__compiler__generate_dispatcher_function_4, &frame__compiler__generate_dispatcher_function_1, 66, 67, 3, 36},
  {cont__compiler__generate_dispatcher_function_5, &frame__compiler__generate_dispatcher_function_1, 68, 69, 22, 37},
  {cont__compiler__generate_dispatcher_function_7, &frame__compiler__generate_dispatcher_function_1, 68, 69, 3, 37},
  {cont__compiler__generate_dispatcher_function_8, &frame__compiler__generate_dispatcher_function_1, 70, 70, 3, 44},
  {cont__compiler__generate_dispatcher_function_9, &frame__compiler__generate_dispatcher_function_1, 72, 72, 5, 17},
  {cont__compiler__generate_dispatcher_function_10, &frame__compiler__generate_dispatcher_function_1, 71, 93, 3, 81},
  {cont__compiler__generate_dispatcher_function_19, &frame__compiler__generate_dispatcher_function_1, 98, 118, 22, 5},
  {cont__compiler__generate_dispatcher_function_22, &frame__compiler__generate_dispatcher_function_1, 98, 118, 3, 5},
  {entry__demangled_1, NULL, 120, 120, 40, 50},
  {cont__demangled_4, &frame__demangled_1, 120, 120, 23, 51},
  {cont__demangled_5, &frame__demangled_1, 120, 120, 20, 51},
  {entry__compiler__update_info_8, NULL, 137, 137, 15, 30},
  {entry__compiler__update_info_9, NULL, 140, 140, 31, 44},
  {cont__compiler__update_info_10, &frame__compiler__update_info_9, 139, 141, 21, 55},
  {cont__compiler__update_info_13, &frame__compiler__update_info_9, 139, 141, 15, 55},
  {entry__compiler__update_info_5, NULL, 135, 135, 13, 34},
  {cont__compiler__update_info_6, &frame__compiler__update_info_5, 136, 136, 13, 38},
  {cont__compiler__update_info_7, &frame__compiler__update_info_5, 134, 141, 11, 57},
  {entry__compiler__update_info_16, NULL, 146, 146, 15, 30},
  {entry__compiler__update_info_17, NULL, 148, 148, 15, 25},
  {entry__compiler__update_info_14, NULL, 144, 144, 13, 34},
  {cont__compiler__update_info_15, &frame__compiler__update_info_14, 143, 148, 11, 26},
  {entry__compiler__update_info_20, NULL, 154, 154, 31, 44},
  {cont__compiler__update_info_21, &frame__compiler__update_info_20, 153, 155, 21, 45},
  {cont__compiler__update_info_23, &frame__compiler__update_info_20, 153, 155, 15, 45},
  {entry__compiler__update_info_25, NULL, 157, 157, 15, 30},
  {entry__compiler__update_info_26, NULL, 160, 160, 31, 44},
  {cont__compiler__update_info_27, &frame__compiler__update_info_26, 159, 161, 21, 44},
  {cont__compiler__update_info_29, &frame__compiler__update_info_26, 159, 161, 15, 44},
  {entry__compiler__update_info_30, NULL, 163, 163, 15, 25},
  {entry__compiler__update_info_18, NULL, 151, 151, 13, 34},
  {cont__compiler__update_info_19, &frame__compiler__update_info_18, 156, 156, 13, 39},
  {cont__compiler__update_info_24, &frame__compiler__update_info_18, 150, 163, 11, 26},
  {entry__compiler__update_info_33, NULL, 169, 169, 31, 44},
  {cont__compiler__update_info_34, &frame__compiler__update_info_33, 168, 170, 21, 57},
  {cont__compiler__update_info_36, &frame__compiler__update_info_33, 168, 170, 15, 57},
  {entry__compiler__update_info_38, NULL, 172, 172, 15, 30},
  {entry__compiler__update_info_39, NULL, 175, 175, 31, 44},
  {cont__compiler__update_info_40, &frame__compiler__update_info_39, 174, 176, 21, 44},
  {cont__compiler__update_info_41, &frame__compiler__update_info_39, 174, 176, 15, 44},
  {entry__compiler__update_info_42, NULL, 179, 179, 31, 44},
  {cont__compiler__update_info_43, &frame__compiler__update_info_42, 178, 180, 21, 55},
  {cont__compiler__update_info_45, &frame__compiler__update_info_42, 178, 180, 15, 55},
  {entry__compiler__update_info_31, NULL, 166, 166, 13, 34},
  {cont__compiler__update_info_32, &frame__compiler__update_info_31, 171, 171, 13, 41},
  {cont__compiler__update_info_37, &frame__compiler__update_info_31, 165, 180, 11, 57},
  {entry__compiler__update_info_48, NULL, 186, 186, 31, 44},
  {cont__compiler__update_info_49, &frame__compiler__update_info_48, 185, 187, 21, 56},
  {cont__compiler__update_info_51, &frame__compiler__update_info_48, 185, 187, 15, 56},
  {entry__compiler__update_info_53, NULL, 189, 189, 15, 30},
  {entry__compiler__update_info_54, NULL, 192, 192, 31, 44},
  {cont__compiler__update_info_55, &frame__compiler__update_info_54, 191, 193, 21, 55},
  {cont__compiler__update_info_56, &frame__compiler__update_info_54, 191, 193, 15, 55},
  {entry__compiler__update_info_57, NULL, 195, 195, 15, 25},
  {entry__compiler__update_info_46, NULL, 183, 183, 13, 34},
  {cont__compiler__update_info_47, &frame__compiler__update_info_46, 188, 188, 13, 54},
  {cont__compiler__update_info_52, &frame__compiler__update_info_46, 182, 195, 11, 26},
  {entry__compiler__update_info_3, NULL, 132, 132, 9, 35},
  {cont__compiler__update_info_4, &frame__compiler__update_info_3, 131, 195, 7, 28},
  {entry__compiler__update_info_58, NULL, 197, 197, 7, 17},
  {entry__compiler__update_info_1, NULL, 130, 130, 5, 24},
  {cont__compiler__update_info_2, &frame__compiler__update_info_1, 129, 197, 3, 18},
  {cont__compiler__update_info_59, &frame__compiler__update_info_1, 197, 197, 18, 18},
  {entry__compiler__sim2c_7, NULL, 214, 214, 42, 42},
  {cont__compiler__sim2c_8, &frame__compiler__sim2c_7, 214, 214, 17, 43},
  {cont__compiler__sim2c_9, &frame__compiler__sim2c_7, 214, 214, 68, 68},
  {cont__compiler__sim2c_10, &frame__compiler__sim2c_7, 214, 214, 54, 69},
  {cont__compiler__sim2c_11, &frame__compiler__sim2c_7, 214, 214, 11, 69},
  {cont__compiler__sim2c_12, &frame__compiler__sim2c_7, 214, 214, 69, 69},
  {entry__compiler__sim2c_13, NULL, 216, 216, 31, 31},
  {cont__compiler__sim2c_14, &frame__compiler__sim2c_13, 216, 216, 11, 32},
  {cont__compiler__sim2c_15, &frame__compiler__sim2c_13, 216, 216, 32, 32},
  {entry__compiler__sim2c_5, NULL, 213, 213, 9, 35},
  {cont__compiler__sim2c_6, &frame__compiler__sim2c_5, 212, 216, 7, 33},
  {entry__compiler__sim2c_2, NULL, 211, 211, 8, 29},
  {cont__compiler__sim2c_4, &frame__compiler__sim2c_2, 211, 216, 5, 34},
  {cont__compiler__sim2c_16, &frame__compiler__sim2c_2, 217, 217, 25, 34},
  {cont__compiler__sim2c_17, &frame__compiler__sim2c_2, 217, 217, 8, 35},
  {cont__compiler__sim2c_18, &frame__compiler__sim2c_2, 217, 217, 5, 35},
  {entry__compiler__sim2c_26, NULL, 405, 405, 37, 57},
  {cont__compiler__sim2c_27, &frame__compiler__sim2c_26, 405, 405, 37, 68},
  {cont__compiler__sim2c_28, &frame__compiler__sim2c_26, 405, 405, 37, 68},
  {entry__compiler__sim2c_21, NULL, 402, 402, 9, 45},
  {cont__compiler__sim2c_22, &frame__compiler__sim2c_21, 403, 403, 9, 40},
  {cont__compiler__sim2c_23, &frame__compiler__sim2c_21, 404, 404, 9, 40},
  {cont__compiler__sim2c_24, &frame__compiler__sim2c_21, 405, 405, 12, 32},
  {cont__compiler__sim2c_25, &frame__compiler__sim2c_21, 405, 405, 12, 68},
  {cont__compiler__sim2c_29, &frame__compiler__sim2c_21, 405, 405, 9, 75},
  {entry__compiler__sim2c_33, NULL, 409, 409, 11, 50},
  {cont__compiler__sim2c_34, &frame__compiler__sim2c_33, 410, 410, 11, 16},
  {entry__compiler__sim2c_30, NULL, 407, 407, 9, 46},
  {cont__compiler__sim2c_31, &frame__compiler__sim2c_30, 408, 408, 12, 32},
  {cont__compiler__sim2c_32, &frame__compiler__sim2c_30, 408, 410, 9, 16},
  {entry__compiler__sim2c_39, NULL, 412, 412, 33, 59},
  {cont__compiler__sim2c_40, &frame__compiler__sim2c_39, 412, 412, 72, 72},
  {entry__compiler__sim2c_19, NULL, 401, 401, 7, 34},
  {cont__compiler__sim2c_20, &frame__compiler__sim2c_19, 400, 410, 5, 18},
  {cont__compiler__sim2c_35, &frame__compiler__sim2c_19, 411, 411, 44, 69},
  {cont__compiler__sim2c_36, &frame__compiler__sim2c_19, 411, 411, 5, 75},
  {cont__compiler__sim2c_37, &frame__compiler__sim2c_19, 412, 412, 8, 30},
  {cont__compiler__sim2c_38, &frame__compiler__sim2c_19, 412, 412, 5, 72},
  {cont__compiler__sim2c_41, &frame__compiler__sim2c_19, 412, 412, 72, 72},
  {entry__compiler__sim2c_49, NULL, 244, 244, 9, 22},
  {cont__compiler__sim2c_50, &frame__compiler__sim2c_49, 244, 244, 22, 22},
  {entry__compiler__sim2c_51, NULL, 246, 246, 9, 61},
  {entry__compiler__sim2c_54, NULL, 248, 249, 14, 31},
  {cont__compiler__sim2c_57, &frame__compiler__sim2c_54, 248, 249, 7, 31},
  {entry__compiler__sim2c_59, NULL, 250, 250, 24, 59},
  {entry__compiler__sim2c_64, NULL, 251, 251, 29, 54},
  {entry__compiler__sim2c_70, NULL, 252, 252, 23, 65},
  {entry__compiler__sim2c_77, NULL, 253, 253, 28, 73},
  {entry__compiler__sim2c_82, NULL, 254, 254, 43, 43},
  {entry__compiler__sim2c_86, NULL, 257, 257, 24, 63},
  {entry__compiler__sim2c_89, NULL, 258, 258, 51, 68},
  {cont__compiler__sim2c_90, &frame__compiler__sim2c_89, 258, 258, 68, 68},
  {entry__compiler__sim2c_92, NULL, 259, 259, 24, 62},
  {entry__compiler__sim2c_99, NULL, 266, 266, 13, 28},
  {cont__compiler__sim2c_100, &frame__compiler__sim2c_99, 267, 267, 25, 49},
  {cont__compiler__sim2c_101, &frame__compiler__sim2c_99, 267, 267, 13, 49},
  {cont__compiler__sim2c_102, &frame__compiler__sim2c_99, 267, 267, 49, 49},
  {entry__compiler__sim2c_103, NULL, 269, 269, 13, 28},
  {cont__compiler__sim2c_104, &frame__compiler__sim2c_103, 270, 270, 25, 56},
  {cont__compiler__sim2c_105, &frame__compiler__sim2c_103, 270, 270, 13, 56},
  {cont__compiler__sim2c_106, &frame__compiler__sim2c_103, 270, 270, 56, 56},
  {entry__compiler__sim2c_107, NULL, 272, 272, 13, 16},
  {entry__compiler__sim2c_96, NULL, 264, 264, 11, 29},
  {cont__compiler__sim2c_97, &frame__compiler__sim2c_96, 264, 264, 11, 32},
  {cont__compiler__sim2c_98, &frame__compiler__sim2c_96, 263, 272, 9, 17},
  {entry__compiler__sim2c_95, NULL, 262, 272, 7, 18},
  {cont__compiler__sim2c_108, &frame__compiler__sim2c_95, 272, 272, 18, 18},
  {entry__compiler__sim2c_47, NULL, 241, 241, 5, 24},
  {cont__compiler__sim2c_48, &frame__compiler__sim2c_47, 242, 246, 5, 62},
  {cont__compiler__sim2c_53, &frame__compiler__sim2c_47, 247, 249, 5, 32},
  {cont__compiler__sim2c_58, &frame__compiler__sim2c_47, 250, 250, 5, 59},
  {cont__compiler__sim2c_61, &frame__compiler__sim2c_47, 251, 251, 8, 21},
  {cont__compiler__sim2c_62, &frame__compiler__sim2c_47, 251, 251, 8, 26},
  {cont__compiler__sim2c_63, &frame__compiler__sim2c_47, 251, 251, 5, 54},
  {cont__compiler__sim2c_66, &frame__compiler__sim2c_47, 252, 252, 8, 13},
  {cont__compiler__sim2c_67, &frame__compiler__sim2c_47, 252, 252, 8, 20},
  {cont__compiler__sim2c_68, &frame__compiler__sim2c_47, 252, 252, 8, 20},
  {cont__compiler__sim2c_69, &frame__compiler__sim2c_47, 252, 252, 5, 65},
  {cont__compiler__sim2c_72, &frame__compiler__sim2c_47, 253, 253, 13, 13},
  {cont__compiler__sim2c_73, &frame__compiler__sim2c_47, 253, 253, 8, 14},
  {cont__compiler__sim2c_74, &frame__compiler__sim2c_47, 253, 253, 8, 25},
  {cont__compiler__sim2c_75, &frame__compiler__sim2c_47, 253, 253, 8, 25},
  {cont__compiler__sim2c_76, &frame__compiler__sim2c_47, 253, 253, 5, 73},
  {cont__compiler__sim2c_79, &frame__compiler__sim2c_47, 254, 254, 8, 28},
  {cont__compiler__sim2c_81, &frame__compiler__sim2c_47, 254, 254, 5, 43},
  {cont__compiler__sim2c_83, &frame__compiler__sim2c_47, 255, 255, 5, 32},
  {cont__compiler__sim2c_84, &frame__compiler__sim2c_47, 256, 256, 5, 49},
  {cont__compiler__sim2c_85, &frame__compiler__sim2c_47, 257, 257, 5, 63},
  {cont__compiler__sim2c_88, &frame__compiler__sim2c_47, 258, 258, 5, 68},
  {cont__compiler__sim2c_91, &frame__compiler__sim2c_47, 259, 259, 5, 62},
  {cont__compiler__sim2c_94, &frame__compiler__sim2c_47, 261, 272, 5, 19},
  {cont__compiler__sim2c_109, &frame__compiler__sim2c_47, 273, 273, 60, 60},
  {cont__compiler__sim2c_110, &frame__compiler__sim2c_47, 273, 273, 23, 61},
  {cont__compiler__sim2c_111, &frame__compiler__sim2c_47, 273, 273, 5, 61},
  {cont__compiler__sim2c_112, &frame__compiler__sim2c_47, },
  {entry__compiler__sim2c_114, NULL, 274, 274, 46, 70},
  {cont__compiler__sim2c_115, &frame__compiler__sim2c_114, 274, 274, 34, 70},
  {cont__compiler__sim2c_116, &frame__compiler__sim2c_114, 274, 274, 70, 70},
  {entry__compiler__sim2c_118, NULL, 275, 275, 50, 61},
  {cont__compiler__sim2c_119, &frame__compiler__sim2c_118, 275, 275, 22, 61},
  {entry__compiler__sim2c_122, NULL, 285, 285, 5, 21},
  {cont__compiler__sim2c_123, &frame__compiler__sim2c_122, 286, 286, 5, 13},
  {entry__compiler__sim2c_125, NULL, 288, 288, 44, 70},
  {cont__compiler__sim2c_127, &frame__compiler__sim2c_125, 288, 288, 5, 71},
  {cont__compiler__sim2c_128, &frame__compiler__sim2c_125, 288, 288, 71, 71},
  {entry__compiler__sim2c_130, NULL, 291, 291, 5, 26},
  {cont__compiler__sim2c_131, &frame__compiler__sim2c_130, },
  {entry__compiler__sim2c_133, NULL, 292, 292, 52, 63},
  {cont__compiler__sim2c_134, &frame__compiler__sim2c_133, 292, 292, 22, 63},
  {entry__compiler__sim2c_137, NULL, 297, 297, 5, 28},
  {cont__compiler__sim2c_138, &frame__compiler__sim2c_137, 298, 298, 5, 51},
  {cont__compiler__sim2c_139, &frame__compiler__sim2c_137, 299, 299, 5, 45},
  {cont__compiler__sim2c_140, &frame__compiler__sim2c_137, },
  {entry__compiler__sim2c_142, NULL, 300, 300, 53, 64},
  {cont__compiler__sim2c_143, &frame__compiler__sim2c_142, 300, 300, 22, 64},
  {entry__compiler__sim2c_146, NULL, 304, 304, 27, 53},
  {entry__compiler__sim2c_147, NULL, 304, 304, 56, 69},
  {entry__compiler__sim2c_150, NULL, 306, 306, 35, 41},
  {entry__compiler__sim2c_152, NULL, 307, 307, 5, 37},
  {cont__compiler__sim2c_154, &frame__compiler__sim2c_152, 308, 308, 5, 38},
  {cont__compiler__sim2c_156, &frame__compiler__sim2c_152, 308, 308, 58, 58},
  {entry__compiler__sim2c_161, NULL, 310, 310, 32, 54},
  {cont__compiler__sim2c_163, &frame__compiler__sim2c_161, 310, 310, 59, 59},
  {entry__compiler__sim2c_170, NULL, 316, 316, 47, 64},
  {cont__compiler__sim2c_171, &frame__compiler__sim2c_170, 316, 316, 47, 75},
  {cont__compiler__sim2c_172, &frame__compiler__sim2c_170, 316, 316, 47, 75},
  {entry__compiler__sim2c_181, NULL, 322, 322, 45, 63},
  {cont__compiler__sim2c_182, &frame__compiler__sim2c_181, 322, 322, 63, 63},
  {entry__compiler__sim2c_186, NULL, 324, 324, 29, 47},
  {cont__compiler__sim2c_187, &frame__compiler__sim2c_186, 324, 326, 49, 26},
  {cont__compiler__sim2c_190, &frame__compiler__sim2c_186, 324, 326, 17, 26},
  {entry__compiler__sim2c_196, NULL, 329, 329, 31, 49},
  {cont__compiler__sim2c_197, &frame__compiler__sim2c_196, 329, 331, 51, 62},
  {cont__compiler__sim2c_201, &frame__compiler__sim2c_196, 329, 331, 19, 62},
  {entry__compiler__sim2c_205, NULL, 334, 334, 31, 49},
  {cont__compiler__sim2c_206, &frame__compiler__sim2c_205, 336, 336, 51, 71},
  {cont__compiler__sim2c_207, &frame__compiler__sim2c_205, 336, 336, 38, 72},
  {cont__compiler__sim2c_208, &frame__compiler__sim2c_205, 334, 337, 51, 64},
  {cont__compiler__sim2c_211, &frame__compiler__sim2c_205, 334, 337, 19, 64},
  {entry__compiler__sim2c_193, NULL, 328, 328, 20, 37},
  {cont__compiler__sim2c_194, &frame__compiler__sim2c_193, 328, 328, 20, 48},
  {cont__compiler__sim2c_195, &frame__compiler__sim2c_193, 328, 331, 17, 63},
  {cont__compiler__sim2c_202, &frame__compiler__sim2c_193, 332, 332, 17, 45},
  {cont__compiler__sim2c_203, &frame__compiler__sim2c_193, 333, 333, 20, 36},
  {cont__compiler__sim2c_204, &frame__compiler__sim2c_193, 333, 337, 17, 65},
  {cont__compiler__sim2c_212, &frame__compiler__sim2c_193, 338, 338, 17, 38},
  {cont__compiler__sim2c_213, &frame__compiler__sim2c_193, 338, 338, 43, 43},
  {entry__compiler__sim2c_178, NULL, 321, 321, 15, 47},
  {cont__compiler__sim2c_179, &frame__compiler__sim2c_178, 322, 322, 22, 42},
  {cont__compiler__sim2c_180, &frame__compiler__sim2c_178, 322, 322, 15, 63},
  {cont__compiler__sim2c_183, &frame__compiler__sim2c_178, 323, 323, 18, 38},
  {cont__compiler__sim2c_184, &frame__compiler__sim2c_178, 323, 323, 18, 49},
  {cont__compiler__sim2c_185, &frame__compiler__sim2c_178, 323, 326, 15, 27},
  {cont__compiler__sim2c_191, &frame__compiler__sim2c_178, 327, 327, 18, 43},
  {cont__compiler__sim2c_192, &frame__compiler__sim2c_178, 327, 338, 15, 43},
  {cont__compiler__sim2c_214, &frame__compiler__sim2c_178, 339, 339, 15, 36},
  {cont__compiler__sim2c_215, &frame__compiler__sim2c_178, 340, 340, 15, 35},
  {cont__compiler__sim2c_216, &frame__compiler__sim2c_178, 340, 340, 46, 46},
  {entry__compiler__sim2c_220, NULL, 343, 343, 29, 47},
  {cont__compiler__sim2c_221, &frame__compiler__sim2c_220, 343, 344, 49, 68},
  {cont__compiler__sim2c_222, &frame__compiler__sim2c_220, 343, 344, 17, 68},
  {entry__compiler__sim2c_229, NULL, 349, 349, 33, 51},
  {cont__compiler__sim2c_230, &frame__compiler__sim2c_229, 349, 351, 53, 67},
  {cont__compiler__sim2c_231, &frame__compiler__sim2c_229, 349, 351, 21, 67},
  {entry__compiler__sim2c_227, NULL, 348, 348, 22, 44},
  {cont__compiler__sim2c_228, &frame__compiler__sim2c_227, 348, 351, 19, 68},
  {entry__compiler__sim2c_226, NULL, 347, 351, 17, 69},
  {entry__compiler__sim2c_217, NULL, 342, 342, 18, 35},
  {cont__compiler__sim2c_218, &frame__compiler__sim2c_217, 342, 342, 18, 46},
  {cont__compiler__sim2c_219, &frame__compiler__sim2c_217, 342, 344, 15, 69},
  {cont__compiler__sim2c_223, &frame__compiler__sim2c_217, 345, 345, 15, 46},
  {cont__compiler__sim2c_224, &frame__compiler__sim2c_217, 346, 346, 18, 38},
  {cont__compiler__sim2c_225, &frame__compiler__sim2c_217, 346, 351, 15, 70},
  {cont__compiler__sim2c_232, &frame__compiler__sim2c_217, 352, 352, 15, 33},
  {cont__compiler__sim2c_233, &frame__compiler__sim2c_217, 353, 353, 15, 36},
  {cont__compiler__sim2c_234, &frame__compiler__sim2c_217, 353, 353, 41, 41},
  {entry__compiler__sim2c_174, NULL, 317, 317, 11, 40},
  {cont__compiler__sim2c_175, &frame__compiler__sim2c_174, 318, 318, 11, 30},
  {cont__compiler__sim2c_176, &frame__compiler__sim2c_174, 320, 320, 13, 32},
  {cont__compiler__sim2c_177, &frame__compiler__sim2c_174, 319, 353, 11, 42},
  {entry__compiler__sim2c_167, NULL, 314, 314, 7, 32},
  {cont__compiler__sim2c_168, &frame__compiler__sim2c_167, 316, 316, 9, 42},
  {cont__compiler__sim2c_169, &frame__compiler__sim2c_167, 316, 316, 9, 75},
  {cont__compiler__sim2c_173, &frame__compiler__sim2c_167, 315, 353, 7, 44},
  {entry__compiler__sim2c_166, NULL, 313, 353, 5, 45},
  {entry__compiler__sim2c_238, NULL, 358, 358, 9, 43},
  {cont__compiler__sim2c_239, &frame__compiler__sim2c_238, 358, 358, 48, 48},
  {entry__compiler__sim2c_237, NULL, 357, 358, 7, 48},
  {entry__compiler__sim2c_236, NULL, 356, 358, 5, 49},
  {cont__compiler__sim2c_240, &frame__compiler__sim2c_236, 359, 359, 5, 58},
  {entry__compiler__sim2c_242, NULL, 360, 360, 52, 63},
  {cont__compiler__sim2c_243, &frame__compiler__sim2c_242, 360, 360, 22, 63},
  {entry__compiler__sim2c_247, NULL, 362, 362, 47, 57},
  {cont__compiler__sim2c_248, &frame__compiler__sim2c_247, 362, 362, 34, 63},
  {cont__compiler__sim2c_249, &frame__compiler__sim2c_247, 362, 362, 28, 63},
  {entry__compiler__sim2c_246, NULL, 362, 362, 5, 63},
  {cont__compiler__sim2c_250, &frame__compiler__sim2c_246, 363, 363, 5, 13},
  {entry__compiler__sim2c_254, NULL, 368, 368, 32, 57},
  {cont__compiler__sim2c_255, &frame__compiler__sim2c_254, 368, 368, 32, 57},
  {entry__compiler__sim2c_261, NULL, 378, 378, 22, 52},
  {cont__compiler__sim2c_262, &frame__compiler__sim2c_261, 378, 378, 52, 52},
  {entry__compiler__sim2c_257, NULL, 374, 374, 7, 29},
  {cont__compiler__sim2c_258, &frame__compiler__sim2c_257, 375, 375, 7, 37},
  {cont__compiler__sim2c_259, &frame__compiler__sim2c_257, 376, 376, 7, 39},
  {cont__compiler__sim2c_260, &frame__compiler__sim2c_257, 378, 378, 7, 52},
  {cont__compiler__sim2c_263, &frame__compiler__sim2c_257, 379, 379, 7, 31},
  {cont__compiler__sim2c_264, &frame__compiler__sim2c_257, },
  {entry__compiler__sim2c_252, NULL, 368, 368, 12, 27},
  {cont__compiler__sim2c_253, &frame__compiler__sim2c_252, 368, 368, 12, 57},
  {cont__compiler__sim2c_256, &frame__compiler__sim2c_252, 368, 379, 5, 31},
  {entry__compiler__sim2c_267, NULL, 380, 380, 72, 77},
  {entry__compiler__sim2c_266, NULL, 380, 380, 40, 77},
  {entry__compiler__sim2c_269, NULL, 382, 382, 54, 65},
  {cont__compiler__sim2c_270, &frame__compiler__sim2c_269, 382, 382, 22, 65},
  {entry__compiler__sim2c_277, NULL, 388, 388, 32, 42},
  {cont__compiler__sim2c_278, &frame__compiler__sim2c_277, 388, 388, 48, 65},
  {cont__compiler__sim2c_279, &frame__compiler__sim2c_277, 388, 388, 13, 65},
  {entry__compiler__sim2c_281, NULL, 390, 390, 13, 34},
  {entry__compiler__sim2c_275, NULL, 387, 387, 11, 33},
  {cont__compiler__sim2c_276, &frame__compiler__sim2c_275, 386, 390, 9, 35},
  {entry__compiler__sim2c_274, NULL, 385, 390, 7, 36},
  {entry__compiler__sim2c_283, NULL, 391, 391, 38, 54},
  {entry__compiler__sim2c_273, NULL, 384, 390, 5, 37},
  {cont__compiler__sim2c_282, &frame__compiler__sim2c_273, 391, 391, 5, 54},
  {cont__compiler__sim2c_284, &frame__compiler__sim2c_273, 392, 392, 5, 13},
  {entry__compiler__sim2c_287, NULL, 415, 415, 46, 67},
  {entry__compiler__sim2c_286, NULL, 415, 415, 5, 67},
  {entry__compiler__sim2c_289, NULL, 416, 416, 51, 62},
  {cont__compiler__sim2c_290, &frame__compiler__sim2c_289, 416, 416, 22, 62},
  {entry__compiler__sim2c_296, NULL, 494, 494, 20, 53},
  {cont__compiler__sim2c_297, &frame__compiler__sim2c_296, 494, 494, 53, 53},
  {entry__compiler__sim2c_294, NULL, 493, 493, 5, 22},
  {cont__compiler__sim2c_295, &frame__compiler__sim2c_294, 494, 494, 5, 53},
  {cont__compiler__sim2c_298, &frame__compiler__sim2c_294, 494, 494, 53, 53},
  {entry__compiler__sim2c_301, NULL, 498, 498, 20, 65},
  {cont__compiler__sim2c_302, &frame__compiler__sim2c_301, 498, 498, 65, 65},
  {entry__compiler__sim2c_299, NULL, 497, 497, 5, 22},
  {cont__compiler__sim2c_300, &frame__compiler__sim2c_299, 498, 498, 5, 65},
  {cont__compiler__sim2c_303, &frame__compiler__sim2c_299, 498, 498, 65, 65},
  {entry__compiler__sim2c_306, NULL, 502, 502, 20, 72},
  {cont__compiler__sim2c_307, &frame__compiler__sim2c_306, 502, 502, 72, 72},
  {entry__compiler__sim2c_304, NULL, 501, 501, 5, 22},
  {cont__compiler__sim2c_305, &frame__compiler__sim2c_304, 502, 502, 5, 72},
  {cont__compiler__sim2c_308, &frame__compiler__sim2c_304, 502, 502, 72, 72},
  {entry__compiler__sim2c_311, NULL, 506, 506, 20, 69},
  {cont__compiler__sim2c_312, &frame__compiler__sim2c_311, 506, 506, 69, 69},
  {entry__compiler__sim2c_309, NULL, 505, 505, 5, 22},
  {cont__compiler__sim2c_310, &frame__compiler__sim2c_309, 506, 506, 5, 69},
  {cont__compiler__sim2c_313, &frame__compiler__sim2c_309, 506, 506, 69, 69},
  {entry__compiler__sim2c_316, NULL, 510, 510, 20, 59},
  {cont__compiler__sim2c_317, &frame__compiler__sim2c_316, 510, 510, 59, 59},
  {entry__compiler__sim2c_314, NULL, 509, 509, 5, 22},
  {cont__compiler__sim2c_315, &frame__compiler__sim2c_314, 510, 510, 5, 59},
  {cont__compiler__sim2c_318, &frame__compiler__sim2c_314, 510, 510, 59, 59},
  {entry__compiler__sim2c_321, NULL, 514, 514, 20, 67},
  {cont__compiler__sim2c_322, &frame__compiler__sim2c_321, 514, 514, 67, 67},
  {entry__compiler__sim2c_319, NULL, 513, 513, 5, 22},
  {cont__compiler__sim2c_320, &frame__compiler__sim2c_319, 514, 514, 5, 67},
  {cont__compiler__sim2c_323, &frame__compiler__sim2c_319, 514, 514, 67, 67},
  {entry__compiler__sim2c_326, NULL, 518, 518, 20, 50},
  {cont__compiler__sim2c_327, &frame__compiler__sim2c_326, 518, 518, 50, 50},
  {entry__compiler__sim2c_324, NULL, 517, 517, 5, 22},
  {cont__compiler__sim2c_325, &frame__compiler__sim2c_324, 518, 518, 5, 50},
  {cont__compiler__sim2c_328, &frame__compiler__sim2c_324, 518, 518, 50, 50},
  {entry__compiler__sim2c_331, NULL, 522, 522, 20, 48},
  {cont__compiler__sim2c_332, &frame__compiler__sim2c_331, 522, 522, 48, 48},
  {entry__compiler__sim2c_329, NULL, 521, 521, 5, 22},
  {cont__compiler__sim2c_330, &frame__compiler__sim2c_329, 522, 522, 5, 48},
  {cont__compiler__sim2c_333, &frame__compiler__sim2c_329, 522, 522, 48, 48},
  {entry__compiler__sim2c_336, NULL, 526, 526, 20, 48},
  {cont__compiler__sim2c_337, &frame__compiler__sim2c_336, 526, 526, 48, 48},
  {entry__compiler__sim2c_334, NULL, 525, 525, 5, 22},
  {cont__compiler__sim2c_335, &frame__compiler__sim2c_334, 526, 526, 5, 48},
  {cont__compiler__sim2c_338, &frame__compiler__sim2c_334, 526, 526, 48, 48},
  {entry__compiler__sim2c_341, NULL, 530, 530, 20, 48},
  {cont__compiler__sim2c_342, &frame__compiler__sim2c_341, 530, 530, 48, 48},
  {entry__compiler__sim2c_339, NULL, 529, 529, 5, 22},
  {cont__compiler__sim2c_340, &frame__compiler__sim2c_339, 530, 530, 5, 48},
  {cont__compiler__sim2c_343, &frame__compiler__sim2c_339, 530, 530, 48, 48},
  {entry__compiler__sim2c_346, NULL, 534, 534, 20, 48},
  {cont__compiler__sim2c_347, &frame__compiler__sim2c_346, 534, 534, 48, 48},
  {entry__compiler__sim2c_344, NULL, 533, 533, 5, 22},
  {cont__compiler__sim2c_345, &frame__compiler__sim2c_344, 534, 534, 5, 48},
  {cont__compiler__sim2c_348, &frame__compiler__sim2c_344, 534, 534, 48, 48},
  {entry__compiler__sim2c_351, NULL, 538, 538, 20, 48},
  {cont__compiler__sim2c_352, &frame__compiler__sim2c_351, 538, 538, 48, 48},
  {entry__compiler__sim2c_349, NULL, 537, 537, 5, 22},
  {cont__compiler__sim2c_350, &frame__compiler__sim2c_349, 538, 538, 5, 48},
  {cont__compiler__sim2c_353, &frame__compiler__sim2c_349, 538, 538, 48, 48},
  {entry__compiler__sim2c_356, NULL, 542, 542, 20, 48},
  {cont__compiler__sim2c_357, &frame__compiler__sim2c_356, 542, 542, 48, 48},
  {entry__compiler__sim2c_354, NULL, 541, 541, 5, 22},
  {cont__compiler__sim2c_355, &frame__compiler__sim2c_354, 542, 542, 5, 48},
  {cont__compiler__sim2c_358, &frame__compiler__sim2c_354, 542, 542, 48, 48},
  {entry__compiler__sim2c_360, NULL, 545, 545, 20, 39},
  {cont__compiler__sim2c_361, &frame__compiler__sim2c_360, 545, 545, 47, 47},
  {entry__compiler__sim2c_359, NULL, 545, 545, 5, 47},
  {cont__compiler__sim2c_362, &frame__compiler__sim2c_359, 545, 545, 47, 47},
  {entry__compiler__sim2c_365, NULL, 549, 549, 20, 52},
  {cont__compiler__sim2c_366, &frame__compiler__sim2c_365, 549, 549, 52, 52},
  {entry__compiler__sim2c_363, NULL, 548, 548, 5, 22},
  {cont__compiler__sim2c_364, &frame__compiler__sim2c_363, 549, 549, 5, 52},
  {cont__compiler__sim2c_367, &frame__compiler__sim2c_363, 549, 549, 52, 52},
  {entry__compiler__sim2c_370, NULL, 553, 553, 20, 49},
  {cont__compiler__sim2c_371, &frame__compiler__sim2c_370, 553, 553, 49, 49},
  {entry__compiler__sim2c_368, NULL, 552, 552, 5, 22},
  {cont__compiler__sim2c_369, &frame__compiler__sim2c_368, 553, 553, 5, 49},
  {cont__compiler__sim2c_372, &frame__compiler__sim2c_368, 553, 553, 49, 49},
  {entry__compiler__sim2c_376, NULL, 557, 557, 28, 28},
  {cont__compiler__sim2c_377, &frame__compiler__sim2c_376, 557, 557, 7, 29},
  {cont__compiler__sim2c_378, &frame__compiler__sim2c_376, 558, 558, 7, 68},
  {entry__compiler__sim2c_373, NULL, 556, 556, 8, 33},
  {cont__compiler__sim2c_375, &frame__compiler__sim2c_373, 556, 558, 5, 68},
  {entry__compiler__sim2c_385, NULL, 569, 569, 11, 43},
  {cont__compiler__sim2c_386, &frame__compiler__sim2c_385, 570, 570, 11, 40},
  {cont__compiler__sim2c_387, &frame__compiler__sim2c_385, 570, 570, 40, 40},
  {entry__compiler__sim2c_390, NULL, 573, 573, 13, 36},
  {entry__compiler__sim2c_396, NULL, 578, 578, 15, 31},
  {cont__compiler__sim2c_397, &frame__compiler__sim2c_396, 579, 579, 28, 53},
  {cont__compiler__sim2c_398, &frame__compiler__sim2c_396, 579, 579, 15, 53},
  {cont__compiler__sim2c_399, &frame__compiler__sim2c_396, 579, 579, 53, 53},
  {entry__compiler__sim2c_403, NULL, 582, 582, 36, 76},
  {cont__compiler__sim2c_404, &frame__compiler__sim2c_403, 582, 582, 36, 76},
  {entry__compiler__sim2c_406, NULL, 583, 583, 56, 73},
  {cont__compiler__sim2c_407, &frame__compiler__sim2c_406, 583, 583, 17, 73},
  {entry__compiler__sim2c_410, NULL, 588, 588, 21, 54},
  {entry__compiler__sim2c_414, NULL, 592, 592, 25, 55},
  {entry__compiler__sim2c_415, NULL, 594, 594, 25, 62},
  {entry__compiler__sim2c_411, NULL, 591, 591, 23, 46},
  {cont__compiler__sim2c_412, &frame__compiler__sim2c_411, 591, 591, 23, 57},
  {cont__compiler__sim2c_413, &frame__compiler__sim2c_411, 590, 594, 21, 63},
  {entry__compiler__sim2c_416, NULL, 596, 596, 21, 53},
  {entry__compiler__sim2c_408, NULL, 586, 586, 19, 47},
  {cont__compiler__sim2c_409, &frame__compiler__sim2c_408, 585, 596, 17, 54},
  {entry__compiler__sim2c_391, NULL, 575, 575, 36, 60},
  {cont__compiler__sim2c_392, &frame__compiler__sim2c_391, 575, 575, 13, 61},
  {cont__compiler__sim2c_393, &frame__compiler__sim2c_391, 576, 576, 13, 47},
  {cont__compiler__sim2c_394, &frame__compiler__sim2c_391, 577, 577, 16, 35},
  {cont__compiler__sim2c_395, &frame__compiler__sim2c_391, 577, 579, 13, 53},
  {cont__compiler__sim2c_400, &frame__compiler__sim2c_391, 580, 580, 13, 47},
  {cont__compiler__sim2c_401, &frame__compiler__sim2c_391, 582, 582, 15, 31},
  {cont__compiler__sim2c_402, &frame__compiler__sim2c_391, 582, 582, 15, 76},
  {cont__compiler__sim2c_405, &frame__compiler__sim2c_391, 581, 596, 13, 56},
  {cont__compiler__sim2c_417, &frame__compiler__sim2c_391, 596, 596, 56, 56},
  {entry__compiler__sim2c_383, NULL, 568, 568, 12, 41},
  {cont__compiler__sim2c_384, &frame__compiler__sim2c_383, 568, 570, 9, 40},
  {cont__compiler__sim2c_388, &frame__compiler__sim2c_383, 572, 572, 11, 30},
  {cont__compiler__sim2c_389, &frame__compiler__sim2c_383, 571, 596, 9, 58},
  {entry__compiler__sim2c_382, NULL, 566, 596, 7, 59},
  {entry__compiler__sim2c_421, NULL, 597, 597, 28, 67},
  {entry__compiler__sim2c_423, NULL, 598, 598, 20, 46},
  {cont__compiler__sim2c_424, &frame__compiler__sim2c_423, 598, 598, 46, 46},
  {entry__compiler__sim2c_381, NULL, 565, 596, 5, 60},
  {cont__compiler__sim2c_418, &frame__compiler__sim2c_381, 597, 597, 8, 25},
  {cont__compiler__sim2c_419, &frame__compiler__sim2c_381, 597, 597, 8, 25},
  {cont__compiler__sim2c_420, &frame__compiler__sim2c_381, 597, 597, 5, 67},
  {cont__compiler__sim2c_422, &frame__compiler__sim2c_381, 598, 598, 5, 46},
  {cont__compiler__sim2c_425, &frame__compiler__sim2c_381, 599, 599, 5, 29},
  {cont__compiler__sim2c_426, &frame__compiler__sim2c_381, },
  {entry__compiler__sim2c_436, NULL, 610, 610, 21, 74},
  {cont__compiler__sim2c_439, &frame__compiler__sim2c_436, 610, 610, 13, 74},
  {entry__compiler__sim2c_432, NULL, 608, 608, 11, 41},
  {cont__compiler__sim2c_434, &frame__compiler__sim2c_432, 609, 609, 14, 29},
  {cont__compiler__sim2c_435, &frame__compiler__sim2c_432, 609, 610, 11, 74},
  {entry__compiler__sim2c_440, NULL, 612, 612, 39, 70},
  {cont__compiler__sim2c_443, &frame__compiler__sim2c_440, 612, 612, 11, 70},
  {cont__compiler__sim2c_444, &frame__compiler__sim2c_440, 613, 623, 17, 66},
  {cont__compiler__sim2c_447, &frame__compiler__sim2c_440, 613, 623, 11, 66},
  {entry__compiler__sim2c_449, NULL, 625, 625, 9, 35},
  {cont__compiler__sim2c_450, &frame__compiler__sim2c_449, 627, 627, 29, 49},
  {cont__compiler__sim2c_451, &frame__compiler__sim2c_449, 628, 628, 42, 62},
  {cont__compiler__sim2c_452, &frame__compiler__sim2c_449, 626, 629, 15, 11},
  {cont__compiler__sim2c_456, &frame__compiler__sim2c_449, 626, 629, 9, 11},
  {cont__compiler__sim2c_457, &frame__compiler__sim2c_449, 630, 630, 37, 57},
  {cont__compiler__sim2c_458, &frame__compiler__sim2c_449, 630, 630, 9, 59},
  {cont__compiler__sim2c_460, &frame__compiler__sim2c_449, 631, 631, 9, 38},
  {entry__compiler__sim2c_431, NULL, 606, 623, 7, 68},
  {cont__compiler__sim2c_448, &frame__compiler__sim2c_431, 624, 631, 7, 38},
  {entry__compiler__sim2c_462, NULL, 632, 632, 20, 46},
  {cont__compiler__sim2c_463, &frame__compiler__sim2c_462, 632, 632, 46, 46},
  {entry__compiler__sim2c_430, NULL, 605, 631, 5, 39},
  {cont__compiler__sim2c_461, &frame__compiler__sim2c_430, 632, 632, 5, 46},
  {cont__compiler__sim2c_464, &frame__compiler__sim2c_430, 633, 633, 5, 29},
  {cont__compiler__sim2c_465, &frame__compiler__sim2c_430, },
  {entry__compiler__sim2c_472, NULL, 640, 640, 50, 72},
  {entry__compiler__sim2c_471, NULL, 640, 640, 27, 72},
  {entry__compiler__sim2c_476, NULL, 641, 641, 28, 67},
  {entry__compiler__sim2c_478, NULL, 642, 642, 20, 46},
  {cont__compiler__sim2c_479, &frame__compiler__sim2c_478, 642, 642, 46, 46},
  {entry__compiler__sim2c_468, NULL, 638, 638, 35, 52},
  {cont__compiler__sim2c_469, &frame__compiler__sim2c_468, 638, 638, 5, 53},
  {cont__compiler__sim2c_470, &frame__compiler__sim2c_468, 640, 640, 5, 72},
  {cont__compiler__sim2c_473, &frame__compiler__sim2c_468, 641, 641, 8, 25},
  {cont__compiler__sim2c_474, &frame__compiler__sim2c_468, 641, 641, 8, 25},
  {cont__compiler__sim2c_475, &frame__compiler__sim2c_468, 641, 641, 5, 67},
  {cont__compiler__sim2c_477, &frame__compiler__sim2c_468, 642, 642, 5, 46},
  {cont__compiler__sim2c_480, &frame__compiler__sim2c_468, 643, 643, 5, 29},
  {cont__compiler__sim2c_481, &frame__compiler__sim2c_468, },
  {entry__compiler__sim2c_485, NULL, 649, 651, 11, 13},
  {entry__compiler__sim2c_487, NULL, 653, 657, 11, 13},
  {entry__compiler__sim2c_484, NULL, 647, 657, 7, 15},
  {cont__compiler__sim2c_489, &frame__compiler__sim2c_484, 658, 658, 7, 22},
  {entry__compiler__sim2c_491, NULL, 659, 659, 20, 46},
  {cont__compiler__sim2c_492, &frame__compiler__sim2c_491, 659, 659, 46, 46},
  {entry__compiler__sim2c_483, NULL, 646, 658, 5, 22},
  {cont__compiler__sim2c_490, &frame__compiler__sim2c_483, 659, 659, 5, 46},
  {cont__compiler__sim2c_493, &frame__compiler__sim2c_483, 660, 660, 5, 29},
  {cont__compiler__sim2c_494, &frame__compiler__sim2c_483, },
  {entry__compiler__sim2c_497, NULL, 661, 661, 72, 77},
  {entry__compiler__sim2c_496, NULL, 661, 661, 40, 77},
  {entry__compiler__sim2c_499, NULL, 662, 662, 51, 71},
  {cont__compiler__sim2c_501, &frame__compiler__sim2c_499, 662, 662, 43, 71},
  {entry__compiler__sim2c_503, NULL, 663, 663, 45, 62},
  {cont__compiler__sim2c_505, &frame__compiler__sim2c_503, 663, 663, 37, 62},
  {entry__compiler__sim2c_507, NULL, 664, 664, 47, 68},
  {cont__compiler__sim2c_509, &frame__compiler__sim2c_507, 664, 664, 39, 68},
  {entry__compiler__sim2c_515, NULL, 668, 668, 5, 31},
  {cont__compiler__sim2c_517, &frame__compiler__sim2c_515, 669, 669, 5, 31},
  {cont__compiler__sim2c_519, &frame__compiler__sim2c_515, 669, 669, 36, 36},
  {entry__compiler__sim2c_521, NULL, 670, 670, 43, 62},
  {cont__compiler__sim2c_524, &frame__compiler__sim2c_521, 670, 670, 35, 62},
  {entry__compiler__sim2c_531, NULL, 691, 726, 5, 12},
  {entry__compiler__sim2c_535, NULL, 727, 727, 40, 65},
  {cont__compiler__sim2c_537, &frame__compiler__sim2c_535, 727, 727, 40, 65},
  {entry__compiler__sim2c_539, NULL, 728, 729, 5, 35},
  {entry__compiler__sim2c_547, NULL, 776, 776, 15, 45},
  {cont__compiler__sim2c_550, &frame__compiler__sim2c_547, 776, 776, 7, 45},
  {entry__compiler__sim2c_557, NULL, 779, 779, 15, 64},
  {cont__compiler__sim2c_559, &frame__compiler__sim2c_557, 779, 779, 7, 64},
  {entry__compiler__sim2c_563, NULL, 781, 781, 15, 48},
  {cont__compiler__sim2c_565, &frame__compiler__sim2c_563, 781, 781, 7, 48},
  {entry__compiler__sim2c_569, NULL, 783, 783, 15, 51},
  {cont__compiler__sim2c_571, &frame__compiler__sim2c_569, 783, 783, 7, 51},
  {entry__compiler__sim2c_544, NULL, 775, 775, 8, 29},
  {cont__compiler__sim2c_545, &frame__compiler__sim2c_544, 775, 775, 8, 44},
  {cont__compiler__sim2c_546, &frame__compiler__sim2c_544, 775, 776, 5, 45},
  {cont__compiler__sim2c_551, &frame__compiler__sim2c_544, 777, 777, 13, 46},
  {cont__compiler__sim2c_553, &frame__compiler__sim2c_544, 777, 777, 5, 46},
  {cont__compiler__sim2c_554, &frame__compiler__sim2c_544, 778, 778, 8, 29},
  {cont__compiler__sim2c_555, &frame__compiler__sim2c_544, 778, 778, 8, 46},
  {cont__compiler__sim2c_556, &frame__compiler__sim2c_544, 778, 779, 5, 64},
  {cont__compiler__sim2c_560, &frame__compiler__sim2c_544, 780, 780, 10, 31},
  {cont__compiler__sim2c_561, &frame__compiler__sim2c_544, 780, 780, 33, 59},
  {cont__compiler__sim2c_562, &frame__compiler__sim2c_544, 780, 781, 5, 48},
  {cont__compiler__sim2c_566, &frame__compiler__sim2c_544, 782, 782, 10, 31},
  {cont__compiler__sim2c_567, &frame__compiler__sim2c_544, 782, 782, 33, 61},
  {cont__compiler__sim2c_568, &frame__compiler__sim2c_544, 782, 783, 5, 51},
  {entry__compiler__sim2c_583, NULL, 793, 793, 57, 57},
  {cont__compiler__sim2c_584, &frame__compiler__sim2c_583, 793, 793, 13, 58},
  {cont__compiler__sim2c_585, &frame__compiler__sim2c_583, 793, 793, 5, 58},
  {entry__compiler__sim2c_590, NULL, 805, 805, 7, 45},
  {entry__compiler__sim2c_592, NULL, 807, 807, 15, 47},
  {cont__compiler__sim2c_595, &frame__compiler__sim2c_592, 807, 807, 7, 47},
  {entry__compiler__sim2c_602, NULL, 813, 813, 51, 51},
  {cont__compiler__sim2c_603, &frame__compiler__sim2c_602, 813, 813, 13, 52},
  {cont__compiler__sim2c_604, &frame__compiler__sim2c_602, 813, 813, 5, 52},
  {entry__compiler__sim2c_611, NULL, 827, 827, 26, 43},
  {cont__compiler__sim2c_612, &frame__compiler__sim2c_611, 827, 827, 13, 50},
  {cont__compiler__sim2c_616, &frame__compiler__sim2c_611, 827, 827, 7, 50},
  {entry__compiler__sim2c_610, NULL, 826, 827, 5, 50},
  {entry__compiler__sim2c_620, NULL, 830, 830, 49, 75},
  {cont__compiler__sim2c_622, &frame__compiler__sim2c_620, 830, 830, 43, 75},
  {entry__compiler__sim2c_626, NULL, 834, 834, 42, 69},
  {cont__compiler__sim2c_629, &frame__compiler__sim2c_626, 834, 834, 36, 69},
  {entry__compiler__sim2c_636, NULL, 852, 852, 38, 44},
  {cont__compiler__sim2c_637, &frame__compiler__sim2c_636, 852, 852, 38, 45},
  {cont__compiler__sim2c_638, &frame__compiler__sim2c_636, 852, 852, 7, 45},
  {cont__compiler__sim2c_639, &frame__compiler__sim2c_636, 853, 854, 13, 43},
  {cont__compiler__sim2c_642, &frame__compiler__sim2c_636, 853, 854, 7, 43},
  {entry__compiler__sim2c_643, NULL, 856, 856, 7, 16},
  {entry__compiler__sim2c_648, NULL, 866, 866, 5, 32},
  {cont__compiler__sim2c_649, &frame__compiler__sim2c_648, 867, 875, 11, 38},
  {cont__compiler__sim2c_658, &frame__compiler__sim2c_648, 867, 875, 5, 38},
  {entry__compiler__sim2c_668, NULL, 884, 892, 7, 10},
  {entry__compiler__sim2c_670, NULL, 894, 900, 13, 39},
  {cont__compiler__sim2c_673, &frame__compiler__sim2c_670, 894, 900, 7, 39},
  {entry__compiler__sim2c_675, NULL, 902, 902, 5, 39},
  {cont__compiler__sim2c_676, &frame__compiler__sim2c_675, 903, 903, 13, 43},
  {cont__compiler__sim2c_679, &frame__compiler__sim2c_675, 903, 903, 5, 43},
  {entry__compiler__sim2c_683, NULL, 909, 911, 11, 43},
  {cont__compiler__sim2c_686, &frame__compiler__sim2c_683, 909, 911, 5, 43},
  {entry__compiler__sim2c_689, NULL, 916, 919, 7, 37},
  {entry__compiler__sim2c_691, NULL, 921, 928, 13, 39},
  {cont__compiler__sim2c_694, &frame__compiler__sim2c_691, 921, 928, 7, 39},
  {entry__compiler__sim2c_696, NULL, 930, 930, 27, 47},
  {cont__compiler__sim2c_697, &frame__compiler__sim2c_696, 930, 930, 13, 52},
  {cont__compiler__sim2c_699, &frame__compiler__sim2c_696, 930, 930, 5, 52},
  {entry__compiler__sim2c_717, NULL, 940, 940, 60, 75},
  {cont__compiler__sim2c_718, &frame__compiler__sim2c_717, 940, 940, 43, 75},
  {cont__compiler__sim2c_719, &frame__compiler__sim2c_717, 940, 940, 43, 75},
  {entry__compiler__sim2c_721, NULL, 941, 941, 19, 46},
  {cont__compiler__sim2c_723, &frame__compiler__sim2c_721, 941, 941, 13, 46},
  {entry__compiler__sim2c_729, NULL, 946, 947, 23, 43},
  {cont__compiler__sim2c_732, &frame__compiler__sim2c_729, 946, 947, 17, 43},
  {entry__compiler__sim2c_726, NULL, 945, 945, 18, 38},
  {cont__compiler__sim2c_727, &frame__compiler__sim2c_726, 945, 945, 18, 38},
  {cont__compiler__sim2c_728, &frame__compiler__sim2c_726, 945, 947, 15, 44},
  {entry__compiler__sim2c_736, NULL, 949, 950, 23, 45},
  {cont__compiler__sim2c_739, &frame__compiler__sim2c_736, 949, 950, 17, 45},
  {entry__compiler__sim2c_733, NULL, 948, 948, 18, 46},
  {cont__compiler__sim2c_734, &frame__compiler__sim2c_733, 948, 948, 18, 46},
  {cont__compiler__sim2c_735, &frame__compiler__sim2c_733, 948, 950, 15, 46},
  {entry__compiler__sim2c_740, NULL, 952, 953, 23, 48},
  {cont__compiler__sim2c_742, &frame__compiler__sim2c_740, 952, 953, 17, 48},
  {entry__compiler__sim2c_724, NULL, 943, 943, 13, 37},
  {cont__compiler__sim2c_725, &frame__compiler__sim2c_724, 944, 953, 13, 50},
  {entry__compiler__sim2c_710, NULL, 938, 938, 28, 50},
  {cont__compiler__sim2c_711, &frame__compiler__sim2c_710, 938, 938, 52, 64},
  {cont__compiler__sim2c_712, &frame__compiler__sim2c_710, 938, 938, 9, 65},
  {cont__compiler__sim2c_713, &frame__compiler__sim2c_710, 940, 940, 15, 37},
  {cont__compiler__sim2c_715, &frame__compiler__sim2c_710, 940, 940, 11, 38},
  {cont__compiler__sim2c_716, &frame__compiler__sim2c_710, 940, 940, 11, 75},
  {cont__compiler__sim2c_720, &frame__compiler__sim2c_710, 939, 953, 9, 52},
  {entry__compiler__sim2c_708, NULL, 937, 937, 10, 37},
  {cont__compiler__sim2c_709, &frame__compiler__sim2c_708, 937, 953, 7, 53},
  {entry__compiler__sim2c_745, NULL, 955, 955, 33, 55},
  {cont__compiler__sim2c_746, &frame__compiler__sim2c_745, 955, 955, 33, 66},
  {cont__compiler__sim2c_747, &frame__compiler__sim2c_745, 955, 955, 17, 70},
  {cont__compiler__sim2c_749, &frame__compiler__sim2c_745, 955, 955, 9, 70},
  {entry__compiler__sim2c_743, NULL, 954, 954, 10, 39},
  {cont__compiler__sim2c_744, &frame__compiler__sim2c_743, 954, 955, 7, 70},
  {entry__compiler__sim2c_704, NULL, 935, 935, 11, 24},
  {cont__compiler__sim2c_706, &frame__compiler__sim2c_704, 935, 935, 5, 24},
  {cont__compiler__sim2c_707, &frame__compiler__sim2c_704, 936, 955, 5, 71},
  {entry__compiler__sim2c_752, NULL, 959, 965, 7, 30},
  {entry__compiler__sim2c_754, NULL, 967, 974, 13, 39},
  {cont__compiler__sim2c_757, &frame__compiler__sim2c_754, 967, 974, 7, 39},
  {entry__compiler__sim2c_759, NULL, 976, 976, 27, 47},
  {cont__compiler__sim2c_760, &frame__compiler__sim2c_759, 976, 976, 13, 52},
  {cont__compiler__sim2c_762, &frame__compiler__sim2c_759, 976, 976, 5, 52},
  {entry__compiler__sim2c_768, NULL, 984, 989, 7, 33},
  {entry__compiler__sim2c_770, NULL, 991, 998, 13, 39},
  {cont__compiler__sim2c_773, &frame__compiler__sim2c_770, 991, 998, 7, 39},
  {entry__compiler__sim2c_775, NULL, 1000, 1000, 27, 47},
  {cont__compiler__sim2c_776, &frame__compiler__sim2c_775, 1000, 1000, 13, 52},
  {cont__compiler__sim2c_778, &frame__compiler__sim2c_775, 1000, 1000, 5, 52},
  {entry__compiler__sim2c_787, NULL, 1010, 1010, 30, 47},
  {cont__compiler__sim2c_788, &frame__compiler__sim2c_787, 1010, 1010, 14, 57},
  {cont__compiler__sim2c_789, &frame__compiler__sim2c_787, 1010, 1010, 11, 57},
  {entry__compiler__sim2c_790, NULL, 1011, 1011, 11, 19},
  {entry__compiler__sim2c_795, NULL, 1017, 1020, 17, 47},
  {cont__compiler__sim2c_800, &frame__compiler__sim2c_795, 1017, 1020, 11, 47},
  {entry__compiler__sim2c_801, NULL, 1022, 1025, 17, 43},
  {cont__compiler__sim2c_804, &frame__compiler__sim2c_801, 1022, 1025, 11, 43},
  {entry__compiler__sim2c_805, NULL, 1027, 1030, 17, 27},
  {cont__compiler__sim2c_808, &frame__compiler__sim2c_805, 1027, 1030, 11, 27},
  {entry__compiler__sim2c_809, NULL, 1032, 1035, 17, 45},
  {cont__compiler__sim2c_812, &frame__compiler__sim2c_809, 1032, 1035, 11, 45},
  {entry__compiler__sim2c_813, NULL, 1037, 1040, 17, 60},
  {cont__compiler__sim2c_815, &frame__compiler__sim2c_813, 1037, 1040, 11, 60},
  {entry__compiler__sim2c_785, NULL, 1009, 1009, 11, 30},
  {cont__compiler__sim2c_786, &frame__compiler__sim2c_785, 1007, 1011, 7, 20},
  {cont__compiler__sim2c_792, &frame__compiler__sim2c_785, 1013, 1013, 7, 42},
  {cont__compiler__sim2c_793, &frame__compiler__sim2c_785, 1015, 1015, 9, 30},
  {cont__compiler__sim2c_794, &frame__compiler__sim2c_785, 1014, 1040, 7, 62},
  {entry__compiler__sim2c_782, NULL, 1006, 1006, 12, 29},
  {cont__compiler__sim2c_783, &frame__compiler__sim2c_782, 1006, 1006, 12, 40},
  {cont__compiler__sim2c_784, &frame__compiler__sim2c_782, 1006, 1040, 5, 63},
  {entry__compiler__sim2c_818, NULL, 1043, 1045, 5, 31},
  {entry__compiler__sim2c_821, NULL, 1048, 1051, 7, 10},
  {entry__compiler__sim2c_823, NULL, 1053, 1060, 13, 39},
  {cont__compiler__sim2c_826, &frame__compiler__sim2c_823, 1053, 1060, 7, 39},
  {entry__compiler__sim2c_828, NULL, 1062, 1062, 27, 47},
  {cont__compiler__sim2c_829, &frame__compiler__sim2c_828, 1062, 1062, 13, 52},
  {cont__compiler__sim2c_831, &frame__compiler__sim2c_828, 1062, 1062, 5, 52},
  {entry__compiler__sim2c_834, NULL, 1066, 1070, 7, 10},
  {entry__compiler__sim2c_836, NULL, 1072, 1079, 13, 39},
  {cont__compiler__sim2c_839, &frame__compiler__sim2c_836, 1072, 1079, 7, 39},
  {entry__compiler__sim2c_841, NULL, 1081, 1081, 27, 47},
  {cont__compiler__sim2c_842, &frame__compiler__sim2c_841, 1081, 1081, 13, 52},
  {cont__compiler__sim2c_844, &frame__compiler__sim2c_841, 1081, 1081, 5, 52},
  {entry__compiler__sim2c_850, NULL, 1085, 1087, 5, 30},
  {entry__compiler__sim2c_854, NULL, 1089, 1089, 53, 64},
  {cont__compiler__sim2c_855, &frame__compiler__sim2c_854, 1089, 1089, 22, 64},
  {entry__compiler__sim2c_1, NULL, 232, 232, 3, 41},
  {cont__compiler__sim2c_43, &frame__compiler__sim2c_1, 233, 233, 35, 71},
  {cont__compiler__sim2c_45, &frame__compiler__sim2c_1, 233, 233, 3, 72},
  {cont__compiler__sim2c_46, &frame__compiler__sim2c_1, 240, 273, 3, 61},
  {cont__compiler__sim2c_113, &frame__compiler__sim2c_1, 274, 274, 3, 70},
  {cont__compiler__sim2c_117, &frame__compiler__sim2c_1, 275, 275, 3, 61},
  {cont__compiler__sim2c_121, &frame__compiler__sim2c_1, 276, 286, 3, 13},
  {cont__compiler__sim2c_124, &frame__compiler__sim2c_1, 287, 288, 3, 71},
  {cont__compiler__sim2c_129, &frame__compiler__sim2c_1, 289, 291, 3, 26},
  {cont__compiler__sim2c_132, &frame__compiler__sim2c_1, 292, 292, 3, 63},
  {cont__compiler__sim2c_136, &frame__compiler__sim2c_1, 293, 299, 3, 45},
  {cont__compiler__sim2c_141, &frame__compiler__sim2c_1, 300, 300, 3, 64},
  {cont__compiler__sim2c_145, &frame__compiler__sim2c_1, 303, 304, 3, 70},
  {cont__compiler__sim2c_148, &frame__compiler__sim2c_1, 306, 306, 6, 30},
  {cont__compiler__sim2c_149, &frame__compiler__sim2c_1, 306, 306, 6, 41},
  {cont__compiler__sim2c_151, &frame__compiler__sim2c_1, 306, 308, 3, 58},
  {cont__compiler__sim2c_157, &frame__compiler__sim2c_1, 309, 309, 3, 30},
  {cont__compiler__sim2c_159, &frame__compiler__sim2c_1, 310, 310, 6, 29},
  {cont__compiler__sim2c_160, &frame__compiler__sim2c_1, 310, 310, 3, 59},
  {cont__compiler__sim2c_164, &frame__compiler__sim2c_1, 311, 311, 3, 29},
  {cont__compiler__sim2c_165, &frame__compiler__sim2c_1, 312, 353, 3, 46},
  {cont__compiler__sim2c_235, &frame__compiler__sim2c_1, 354, 359, 3, 58},
  {cont__compiler__sim2c_241, &frame__compiler__sim2c_1, 360, 360, 3, 63},
  {cont__compiler__sim2c_245, &frame__compiler__sim2c_1, 361, 363, 3, 13},
  {cont__compiler__sim2c_251, &frame__compiler__sim2c_1, 367, 379, 3, 32},
  {cont__compiler__sim2c_265, &frame__compiler__sim2c_1, 380, 380, 3, 77},
  {cont__compiler__sim2c_268, &frame__compiler__sim2c_1, 382, 382, 3, 65},
  {cont__compiler__sim2c_272, &frame__compiler__sim2c_1, 383, 392, 3, 13},
  {cont__compiler__sim2c_285, &frame__compiler__sim2c_1, 414, 415, 3, 67},
  {cont__compiler__sim2c_288, &frame__compiler__sim2c_1, 416, 416, 3, 62},
  {cont__compiler__sim2c_292, &frame__compiler__sim2c_1, 417, 417, 3, 28},
  {cont__compiler__sim2c_293, &frame__compiler__sim2c_1, 560, 560, 3, 49},
  {cont__compiler__sim2c_380, &frame__compiler__sim2c_1, 561, 599, 3, 29},
  {cont__compiler__sim2c_427, &frame__compiler__sim2c_1, 600, 600, 3, 48},
  {cont__compiler__sim2c_429, &frame__compiler__sim2c_1, 602, 633, 3, 29},
  {cont__compiler__sim2c_466, &frame__compiler__sim2c_1, 634, 634, 3, 39},
  {cont__compiler__sim2c_467, &frame__compiler__sim2c_1, 635, 643, 3, 29},
  {cont__compiler__sim2c_482, &frame__compiler__sim2c_1, 644, 660, 3, 29},
  {cont__compiler__sim2c_495, &frame__compiler__sim2c_1, 661, 661, 3, 77},
  {cont__compiler__sim2c_498, &frame__compiler__sim2c_1, 662, 662, 3, 71},
  {cont__compiler__sim2c_502, &frame__compiler__sim2c_1, 663, 663, 3, 62},
  {cont__compiler__sim2c_506, &frame__compiler__sim2c_1, 664, 664, 3, 68},
  {cont__compiler__sim2c_510, &frame__compiler__sim2c_1, 665, 665, 10, 34},
  {cont__compiler__sim2c_511, &frame__compiler__sim2c_1, 665, 665, 3, 42},
  {cont__compiler__sim2c_512, &frame__compiler__sim2c_1, 666, 666, 3, 39},
  {cont__compiler__sim2c_514, &frame__compiler__sim2c_1, 667, 669, 3, 36},
  {cont__compiler__sim2c_520, &frame__compiler__sim2c_1, 670, 670, 3, 62},
  {cont__compiler__sim2c_525, &frame__compiler__sim2c_1, 671, 671, 10, 32},
  {cont__compiler__sim2c_526, &frame__compiler__sim2c_1, 671, 671, 3, 40},
  {cont__compiler__sim2c_527, &frame__compiler__sim2c_1, 672, 689, 3, 18},
  {cont__compiler__sim2c_529, &frame__compiler__sim2c_1, 690, 690, 10, 35},
  {cont__compiler__sim2c_530, &frame__compiler__sim2c_1, 690, 726, 3, 13},
  {cont__compiler__sim2c_533, &frame__compiler__sim2c_1, 727, 727, 10, 35},
  {cont__compiler__sim2c_534, &frame__compiler__sim2c_1, 727, 727, 10, 65},
  {cont__compiler__sim2c_538, &frame__compiler__sim2c_1, 727, 729, 3, 36},
  {cont__compiler__sim2c_541, &frame__compiler__sim2c_1, 730, 773, 3, 10},
  {cont__compiler__sim2c_543, &frame__compiler__sim2c_1, 774, 783, 3, 52},
  {cont__compiler__sim2c_572, &frame__compiler__sim2c_1, 784, 785, 3, 19},
  {cont__compiler__sim2c_574, &frame__compiler__sim2c_1, 786, 786, 3, 49},
  {cont__compiler__sim2c_575, &frame__compiler__sim2c_1, 787, 787, 3, 46},
  {cont__compiler__sim2c_576, &frame__compiler__sim2c_1, 788, 789, 3, 10},
  {cont__compiler__sim2c_578, &frame__compiler__sim2c_1, 790, 791, 3, 38},
  {cont__compiler__sim2c_580, &frame__compiler__sim2c_1, 792, 792, 6, 45},
  {cont__compiler__sim2c_581, &frame__compiler__sim2c_1, 792, 792, 6, 45},
  {cont__compiler__sim2c_582, &frame__compiler__sim2c_1, 792, 793, 3, 58},
  {cont__compiler__sim2c_586, &frame__compiler__sim2c_1, 794, 794, 3, 16},
  {cont__compiler__sim2c_588, &frame__compiler__sim2c_1, 795, 795, 3, 30},
  {cont__compiler__sim2c_589, &frame__compiler__sim2c_1, 803, 807, 3, 48},
  {cont__compiler__sim2c_596, &frame__compiler__sim2c_1, 808, 810, 3, 52},
  {cont__compiler__sim2c_598, &frame__compiler__sim2c_1, 811, 811, 3, 75},
  {cont__compiler__sim2c_599, &frame__compiler__sim2c_1, 812, 812, 6, 39},
  {cont__compiler__sim2c_600, &frame__compiler__sim2c_1, 812, 812, 6, 39},
  {cont__compiler__sim2c_601, &frame__compiler__sim2c_1, 812, 813, 3, 52},
  {cont__compiler__sim2c_605, &frame__compiler__sim2c_1, 814, 816, 3, 6},
  {cont__compiler__sim2c_607, &frame__compiler__sim2c_1, 817, 824, 3, 24},
  {cont__compiler__sim2c_609, &frame__compiler__sim2c_1, 825, 827, 3, 51},
  {cont__compiler__sim2c_617, &frame__compiler__sim2c_1, 828, 828, 3, 16},
  {cont__compiler__sim2c_618, &frame__compiler__sim2c_1, 829, 829, 3, 27},
  {cont__compiler__sim2c_619, &frame__compiler__sim2c_1, 830, 830, 3, 75},
  {cont__compiler__sim2c_623, &frame__compiler__sim2c_1, 831, 833, 3, 44},
  {cont__compiler__sim2c_625, &frame__compiler__sim2c_1, 834, 834, 3, 69},
  {cont__compiler__sim2c_630, &frame__compiler__sim2c_1, 835, 848, 9, 10},
  {cont__compiler__sim2c_633, &frame__compiler__sim2c_1, 835, 848, 3, 10},
  {cont__compiler__sim2c_634, &frame__compiler__sim2c_1, 849, 849, 3, 44},
  {cont__compiler__sim2c_635, &frame__compiler__sim2c_1, 850, 856, 3, 17},
  {cont__compiler__sim2c_645, &frame__compiler__sim2c_1, 857, 864, 3, 6},
  {cont__compiler__sim2c_647, &frame__compiler__sim2c_1, 865, 875, 3, 39},
  {cont__compiler__sim2c_659, &frame__compiler__sim2c_1, 876, 876, 3, 22},
  {cont__compiler__sim2c_660, &frame__compiler__sim2c_1, 877, 877, 3, 26},
  {cont__compiler__sim2c_661, &frame__compiler__sim2c_1, 878, 879, 9, 47},
  {cont__compiler__sim2c_663, &frame__compiler__sim2c_1, 878, 879, 3, 47},
  {cont__compiler__sim2c_664, &frame__compiler__sim2c_1, 880, 880, 3, 29},
  {cont__compiler__sim2c_665, &frame__compiler__sim2c_1, 881, 881, 3, 15},
  {cont__compiler__sim2c_667, &frame__compiler__sim2c_1, 882, 900, 3, 41},
  {cont__compiler__sim2c_674, &frame__compiler__sim2c_1, 901, 903, 3, 43},
  {cont__compiler__sim2c_680, &frame__compiler__sim2c_1, 904, 906, 3, 43},
  {cont__compiler__sim2c_682, &frame__compiler__sim2c_1, 908, 911, 3, 44},
  {cont__compiler__sim2c_687, &frame__compiler__sim2c_1, 913, 913, 3, 25},
  {cont__compiler__sim2c_688, &frame__compiler__sim2c_1, 914, 928, 3, 41},
  {cont__compiler__sim2c_695, &frame__compiler__sim2c_1, 929, 930, 3, 52},
  {cont__compiler__sim2c_700, &frame__compiler__sim2c_1, 931, 933, 9, 37},
  {cont__compiler__sim2c_702, &frame__compiler__sim2c_1, 931, 933, 3, 37},
  {cont__compiler__sim2c_703, &frame__compiler__sim2c_1, 934, 955, 3, 72},
  {cont__compiler__sim2c_750, &frame__compiler__sim2c_1, 956, 956, 3, 25},
  {cont__compiler__sim2c_751, &frame__compiler__sim2c_1, 957, 974, 3, 41},
  {cont__compiler__sim2c_758, &frame__compiler__sim2c_1, 975, 976, 3, 52},
  {cont__compiler__sim2c_763, &frame__compiler__sim2c_1, 977, 980, 9, 45},
  {cont__compiler__sim2c_765, &frame__compiler__sim2c_1, 977, 980, 3, 45},
  {cont__compiler__sim2c_766, &frame__compiler__sim2c_1, 981, 981, 3, 25},
  {cont__compiler__sim2c_767, &frame__compiler__sim2c_1, 982, 998, 3, 41},
  {cont__compiler__sim2c_774, &frame__compiler__sim2c_1, 999, 1000, 3, 52},
  {cont__compiler__sim2c_779, &frame__compiler__sim2c_1, 1001, 1004, 9, 45},
  {cont__compiler__sim2c_780, &frame__compiler__sim2c_1, 1001, 1004, 3, 45},
  {cont__compiler__sim2c_781, &frame__compiler__sim2c_1, 1005, 1040, 3, 64},
  {cont__compiler__sim2c_816, &frame__compiler__sim2c_1, 1041, 1041, 3, 25},
  {cont__compiler__sim2c_817, &frame__compiler__sim2c_1, 1042, 1045, 3, 32},
  {cont__compiler__sim2c_820, &frame__compiler__sim2c_1, 1046, 1060, 3, 41},
  {cont__compiler__sim2c_827, &frame__compiler__sim2c_1, 1061, 1062, 3, 52},
  {cont__compiler__sim2c_832, &frame__compiler__sim2c_1, 1063, 1063, 3, 25},
  {cont__compiler__sim2c_833, &frame__compiler__sim2c_1, 1064, 1079, 3, 41},
  {cont__compiler__sim2c_840, &frame__compiler__sim2c_1, 1080, 1081, 3, 52},
  {cont__compiler__sim2c_845, &frame__compiler__sim2c_1, 1082, 1082, 3, 25},
  {cont__compiler__sim2c_846, &frame__compiler__sim2c_1, 1083, 1083, 11, 58},
  {cont__compiler__sim2c_848, &frame__compiler__sim2c_1, 1083, 1083, 3, 58},
  {cont__compiler__sim2c_849, &frame__compiler__sim2c_1, 1084, 1087, 3, 31},
  {cont__compiler__sim2c_852, &frame__compiler__sim2c_1, 1088, 1088, 3, 15},
  {cont__compiler__sim2c_853, &frame__compiler__sim2c_1, 1089, 1089, 3, 64},
  {cont__compiler__sim2c_857, &frame__compiler__sim2c_1, 1089, 1089, 64, 64}
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
  "compiler",
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
  allocate_initialized_frame_gc(0, 7);
  // 57: "std__if" = 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__cc48021895f2809c;
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 58: "std__is_defined" = 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__cb05e9320ae22386;
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
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 59: "std__equal" = 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__17988d443223256d;
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
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 60: "std__less" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76a027f311988656;
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
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 61: "std__length_of" = 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__58b854e1382f539f;
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
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 62: "std__is_empty" = 5
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d8272d0f8bc407b3;
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
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 63: "std__unless" = 6
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__582190112b914cb7;
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
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 55: $compiler::privileged_polymorphic_functions
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
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  arguments->slots[4] = frame->slots[4] /* temp__5 */;
  arguments->slots[5] = frame->slots[5] /* temp__6 */;
  arguments->slots[6] = frame->slots[6] /* temp__7 */;
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
  initialize_future(var.compiler__privileged_polymorphic_functions, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__print_source_3(void) {
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
static void entry__compiler__print_source_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 34: writeln "<newline>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7ca425275e2bb55b;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__print_source_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 36: writeln "<indent_marker>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__41a1d3500d2c5fd2;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__print_source_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 38: writeln "<outdent_marker>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4b30bdab57f18372;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__print_source_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 39: :
  // 40:   write chr
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__print_source_3, 0);
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
  arguments->slots[2] = func__compiler__print_source_4;
  arguments->slots[3] = get__indent_marker();
  arguments->slots[4] = func__compiler__print_source_6;
  arguments->slots[5] = get__outdent_marker();
  arguments->slots[6] = func__compiler__print_source_8;
  arguments->slots[7] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__print_source_1(void) {
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
  arguments->slots[1] = func__compiler__print_source_2;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__eprint_source_3(void) {
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
static void entry__compiler__eprint_source_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 47: ewriteln "<newline>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7ca425275e2bb55b;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__eprint_source_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 49: ewriteln "<indent_marker>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__41a1d3500d2c5fd2;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__eprint_source_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 51: ewriteln "<outdent_marker>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4b30bdab57f18372;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__eprint_source_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 52: :
  // 53:   ewrite chr
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__eprint_source_3, 0);
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
  arguments->slots[2] = func__compiler__eprint_source_4;
  arguments->slots[3] = get__indent_marker();
  arguments->slots[4] = func__compiler__eprint_source_5;
  arguments->slots[5] = get__outdent_marker();
  arguments->slots[6] = func__compiler__eprint_source_6;
  arguments->slots[7] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__eprint_source_1(void) {
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
  arguments->slots[1] = func__compiler__eprint_source_2;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__generate_dispatcher_function_1(void) {
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
  arguments->slots[0] = string__7fb24a3fca4aa852;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__66ccbf91860d092a;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__generate_dispatcher_function_4;
}
static void cont__compiler__generate_dispatcher_function_4(void) {
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
  frame->cont = cont__compiler__generate_dispatcher_function_5;
}
static void cont__compiler__generate_dispatcher_function_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 68: ... "
  // 69:   static void type__@(name)(void) {
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7fb24a3fca4aa852;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__fc8c36a84adb366f;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__generate_dispatcher_function_7;
}
static void cont__compiler__generate_dispatcher_function_7(void) {
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
  frame->cont = cont__compiler__generate_dispatcher_function_8;
}
static void cont__compiler__generate_dispatcher_function_8(void) {
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
  frame->cont = cont__compiler__generate_dispatcher_function_9;
}
static void cont__compiler__generate_dispatcher_function_9(void) {
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
  frame->cont = cont__compiler__generate_dispatcher_function_10;
}
static void cont__compiler__generate_dispatcher_function_10(void) {
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
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__generate_dispatcher_function_11, 0);
  // 91: :
  // 92:   write_to_functions
  // 93:     "  myself = get_attribute(arguments->slots[0], poly_idx__@(name));@nl;"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__generate_dispatcher_function_16, 0);
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
  frame->cont = cont__compiler__generate_dispatcher_function_19;
}
static void entry__compiler__generate_dispatcher_function_11(void) {
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
  arguments->slots[0] = string__75f4eb726550b6de;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__d81f45a403c7e2f7;
  arguments->slots[3] = frame->slots[1] /* id */;
  arguments->slots[4] = string__578a5af303e9ceb;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__generate_dispatcher_function_15;
}
static void cont__compiler__generate_dispatcher_function_15(void) {
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
static void entry__compiler__generate_dispatcher_function_16(void) {
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
  arguments->slots[0] = string__75f4eb726550b6de;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__generate_dispatcher_function_18;
}
static void cont__compiler__generate_dispatcher_function_18(void) {
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
static void cont__compiler__generate_dispatcher_function_19(void) {
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
  arguments->slots[0] = string__3dbc7d1f8cf28ba6;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__9f2e0c02fff25101;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__generate_dispatcher_function_22;
}
static void cont__compiler__generate_dispatcher_function_22(void) {
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
static void entry__demangled_1(void) {
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
  arguments->slots[0] = string__2d7981f4e5f02b9a;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__demangled_4;
}
static void cont__demangled_4(void) {
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
  frame->cont = cont__demangled_5;
}
static void cont__demangled_5(void) {
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
static void entry__compiler__update_info_1(void) {
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
  frame->cont = cont__compiler__update_info_2;
}
static void cont__compiler__update_info_2(void) {
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
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__update_info_3, 0);
  // 196: :
  // 197:   return info
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__update_info_58, 0);
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
  frame->cont = cont__compiler__update_info_59;
}
static void entry__compiler__update_info_53(void) {
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
static void entry__compiler__update_info_54(void) {
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
  frame->cont = cont__compiler__update_info_55;
}
static void cont__compiler__update_info_55(void) {
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
  arguments->slots[0] = string__94b9534b986c24a9;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__80670d894d05691d;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__update_info_56;
}
static void cont__compiler__update_info_56(void) {
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
static void entry__compiler__update_info_57(void) {
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
static void entry__compiler__update_info_38(void) {
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
static void entry__compiler__update_info_39(void) {
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
  frame->cont = cont__compiler__update_info_40;
}
static void cont__compiler__update_info_40(void) {
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
  arguments->slots[0] = string__94b9534b986c24a9;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__f8ba3c062f1b8631;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__update_info_41;
}
static void cont__compiler__update_info_41(void) {
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
static void entry__compiler__update_info_42(void) {
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
  frame->cont = cont__compiler__update_info_43;
}
static void cont__compiler__update_info_43(void) {
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
  arguments->slots[0] = string__94b9534b986c24a9;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__80670d894d05691d;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__update_info_45;
}
static void cont__compiler__update_info_45(void) {
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
static void entry__compiler__update_info_25(void) {
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
static void entry__compiler__update_info_26(void) {
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
  frame->cont = cont__compiler__update_info_27;
}
static void cont__compiler__update_info_27(void) {
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
  arguments->slots[0] = string__94b9534b986c24a9;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__f8ba3c062f1b8631;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__update_info_29;
}
static void cont__compiler__update_info_29(void) {
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
static void entry__compiler__update_info_30(void) {
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
static void entry__compiler__update_info_16(void) {
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
static void entry__compiler__update_info_17(void) {
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
static void entry__compiler__update_info_8(void) {
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
static void entry__compiler__update_info_9(void) {
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
  frame->cont = cont__compiler__update_info_10;
}
static void cont__compiler__update_info_10(void) {
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
  arguments->slots[0] = string__94b9534b986c24a9;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__634c61c70382d128;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__update_info_13;
}
static void cont__compiler__update_info_13(void) {
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
static void entry__compiler__update_info_5(void) {
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
  frame->cont = cont__compiler__update_info_6;
}
static void cont__compiler__update_info_6(void) {
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
  frame->cont = cont__compiler__update_info_7;
}
static void cont__compiler__update_info_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 136: ... :
  // 137:   return undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__update_info_8, 0);
  // 138: :
  // 139:   Error "
  // 140:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 141:     function and cannot be used otherwise!@
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__update_info_9, 0);
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
static void entry__compiler__update_info_14(void) {
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
  frame->cont = cont__compiler__update_info_15;
}
static void cont__compiler__update_info_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 145: ... :
  // 146:   return undefined
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__update_info_16, 0);
  // 147: :
  // 148:   return info
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__update_info_17, 0);
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
static void entry__compiler__update_info_18(void) {
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
  frame->cont = cont__compiler__update_info_19;
}
static void cont__compiler__update_info_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 152: ... :
  // 153:   Error "
  // 154:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 155:     function and id assigned to!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__update_info_20, 0);
  // 156: STATIC_SINGLE, STATIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_SINGLE();
  arguments->slots[1] = get__STATIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__update_info_24;
}
static void entry__compiler__update_info_20(void) {
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
  frame->cont = cont__compiler__update_info_21;
}
static void cont__compiler__update_info_21(void) {
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
  arguments->slots[0] = string__94b9534b986c24a9;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__67c02c7b1bf18880;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__update_info_23;
}
static void cont__compiler__update_info_23(void) {
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
static void cont__compiler__update_info_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 156: ... :
  // 157:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__update_info_25, 0);
  // 158: ... :
  // 159:   Error "
  // 160:     The symbol "@(name.demangled)" is used as a single-assign @
  // 161:     dynamic and is assigned to!@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__update_info_26, 0);
  // 162: ... :
  // 163:   return info
  frame->slots[8] /* temp__6 */ = create_closure(entry__compiler__update_info_30, 0);
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
static void entry__compiler__update_info_31(void) {
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
  frame->cont = cont__compiler__update_info_32;
}
static void cont__compiler__update_info_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 167: ... :
  // 168:   Error "
  // 169:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 170:     function and as a single-assign dynamic!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__update_info_33, 0);
  // 171: STATIC_SINGLE, DYNAMIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_SINGLE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__update_info_37;
}
static void entry__compiler__update_info_33(void) {
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
  frame->cont = cont__compiler__update_info_34;
}
static void cont__compiler__update_info_34(void) {
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
  arguments->slots[0] = string__94b9534b986c24a9;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__aafcf41c458e8f41;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__update_info_36;
}
static void cont__compiler__update_info_36(void) {
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
static void cont__compiler__update_info_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 171: ... :
  // 172:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__update_info_38, 0);
  // 173: ... :
  // 174:   Error "
  // 175:     The symbol "@(name.demangled)" is used as a single-assign @
  // 176:     dynamic and is assigned to!@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__update_info_39, 0);
  // 177: ... :
  // 178:   Error "
  // 179:     The symbol "@(name.demangled)" is used as a single-assign @
  // 180:     dynamic and as a multi-assign dynamic!@
  frame->slots[8] /* temp__6 */ = create_closure(entry__compiler__update_info_42, 0);
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
static void entry__compiler__update_info_46(void) {
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
  frame->cont = cont__compiler__update_info_47;
}
static void cont__compiler__update_info_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 184: ... :
  // 185:   Error "
  // 186:     The symbol "@(name.demangled)" is used as a polymorphic @
  // 187:     function and as a multi-assign dynamic!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__update_info_48, 0);
  // 188: STATIC_SINGLE, STATIC_MULTI, DYNAMIC_MULTI
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_SINGLE();
  arguments->slots[1] = get__STATIC_MULTI();
  arguments->slots[2] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__update_info_52;
}
static void entry__compiler__update_info_48(void) {
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
  frame->cont = cont__compiler__update_info_49;
}
static void cont__compiler__update_info_49(void) {
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
  arguments->slots[0] = string__94b9534b986c24a9;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__a09d645d506640e9;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__update_info_51;
}
static void cont__compiler__update_info_51(void) {
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
static void cont__compiler__update_info_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 188: ... :
  // 189:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__update_info_53, 0);
  // 190: ... :
  // 191:   Error "
  // 192:     The symbol "@(name.demangled)" is used as a single-assign @
  // 193:     dynamic and as a multi-assign dynamic!@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__update_info_54, 0);
  // 194: :
  // 195:   return info
  frame->slots[8] /* temp__6 */ = create_closure(entry__compiler__update_info_57, 0);
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
static void entry__compiler__update_info_3(void) {
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
  frame->cont = cont__compiler__update_info_4;
}
static void cont__compiler__update_info_4(void) {
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
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__update_info_5, 0);
  // 142: ... :
  // 143:   case
  // 144:     variable_kind_of(info)
  // 145:     STATIC_SINGLE:
  // 146:       return undefined
  // 147:     :
  // 148:       return info
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__update_info_14, 0);
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
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__update_info_18, 0);
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
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__update_info_31, 0);
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
  frame->slots[9] /* temp__6 */ = create_closure(entry__compiler__update_info_46, 0);
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
static void entry__compiler__update_info_58(void) {
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
static void cont__compiler__update_info_59(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_1(void) {
  allocate_initialized_frame_gc(3, 36);
  // slot allocations:
  // filenames: 0
  // is_main: 1
  // return__10: 2
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
  // generated_phase_6: 26
  // generated_code: 27
  // generated_collections: 28
  // delayed_statements: 29
  // used_literals: 30
  // def_count: 31
  // depth: 32
  frame->slots[2] /* return__10 */ = create_continuation();
  // _define $mangle_filename 
  // : ($name)
  //   has_prefix temp__1 name "./"
  // 
  //   temp__2:
  //     contains temp__1 module_name "__"
  // 
  //     temp__2:
  //       std::negate temp__2 1
  //       before temp__1 module_name "__" temp__2
  //       std::negate temp__4 1
  //       range temp__3 name 2 temp__4
  //       append temp__1 temp__3 !name
  // 
  //     temp__3:
  //       std::negate temp__1 1
  //       range !name name 3 temp__1
  // 
  //     if temp__1 temp__2 temp__3
  // 
  //   if temp__1 temp__2
  //   std::key_value_pair temp__2 '/' "__"
  //   replace_all temp__1 name temp__2
  //   -> temp__1
  frame->slots[3] /* mangle_filename */ = func__compiler__sim2c_2;
  // _define $need 
  // :
  //   (
  //     mangled_name
  //     info
  //     -> return
  //   )
  //   contains temp__1 mangled_name "__"
  // 
  //   temp__2:
  //     before $namespace mangled_name "__"
  //     behind $name mangled_name "__"
  //     exported_names $namespaces name
  //     is_defined temp__2 namespaces
  // 
  //     temp__3:
  //       namespaces temp__2 namespace
  //       is_defined temp__1 temp__2
  //       -> temp__1
  // 
  //     std::and temp__1 temp__2 temp__3
  //     if temp__1 return
  // 
  //   temp__3:
  //     global_names $definition mangled_name
  //     is_defined temp__1 definition
  // 
  //     temp__2:
  //       check_usage mangled_name definition info
  //       return
  // 
  //     if temp__1 temp__2
  // 
  //   if temp__1 temp__2 temp__3
  //   needed_names temp__1 mangled_name
  //   update_info $updated_info mangled_name temp__1 info
  //   is_defined temp__1 updated_info
  // 
  //   temp__2:
  //     temp__1 updated_info
  //     needed_names !needed_names mangled_name temp__1
  // 
  //   if temp__1 temp__2
  frame->slots[13] /* need */ = func__compiler__sim2c_19;
  define__compiler__required_modules(undefined);
  define__compiler__used_namespaces(undefined);
  define__compiler__defined_namespaces(undefined);
  define__compiler__namespace_mappings(undefined);
  define__compiler__included_files(undefined);
  define__compiler__linked_libraries(undefined);
  define__compiler__dependent_data(undefined);
  define__compiler__global_names(undefined);
  define__compiler__exported_names(undefined);
  define__compiler__needed_names(undefined);
  define__compiler__assigned_names(undefined);
  define__compiler__string_literals(undefined);
  define__compiler__use_inline_c(undefined);
  define__compiler__defined_structs(undefined);
  define__compiler__defined_nodes(undefined);
  define__compiler__defined_functions(undefined);
  define__compiler__enumeration_count(undefined);
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
  frame->slots[26] /* generated_phase_6 */ = create_cell();
  frame->slots[27] /* generated_code */ = create_cell();
  frame->slots[28] /* generated_collections */ = create_cell();
  frame->slots[29] /* delayed_statements */ = create_cell();
  frame->slots[30] /* used_literals */ = create_cell();
  define__used_string_literals(undefined);
  define__compiler__write_to_declarations(create_future());
  define__compiler__write_to_top_level_variable_names(create_future());
  define__compiler__write_to_top_level_variable_declarations(create_future());
  define__compiler__write_to_global_variable_declarations(create_future());
  define__compiler__write_to_continuation_table(create_future());
  define__compiler__write_to_delayed_continuation_table(create_future());
  define__compiler__write_to_functions(create_future());
  define__compiler__write_to_phase_1(create_future());
  define__compiler__write_to_phase_2(create_future());
  define__compiler__write_to_phase_3(create_future());
  define__compiler__write_to_phase_4(create_future());
  define__compiler__write_to_phase_5(create_future());
  define__compiler__write_to_phase_6(create_future());
  define__compiler__use_literal(create_future());
  define__compiler__write_to_generated_collections(create_future());
  define__compiler__write_to_delayed_statements(create_future());
  define__compiler__use_identifier(create_future());
  define__compiler__current_continuation_info(undefined);
  frame->slots[31] /* def_count */ = create_future();
  frame->slots[32] /* depth */ = create_future();
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
  // 219: %%compiler::required_modules empty_insert_order_table
  set__compiler__required_modules(get__empty_insert_order_table());
  // 220: %%compiler::used_namespaces empty_insert_order_set
  set__compiler__used_namespaces(get__empty_insert_order_set());
  // 221: %%compiler::defined_namespaces empty_insert_order_set
  set__compiler__defined_namespaces(get__empty_insert_order_set());
  // 222: %%compiler::namespace_mappings empty_insert_order_table
  set__compiler__namespace_mappings(get__empty_insert_order_table());
  // 223: %%compiler::included_files empty_insert_order_set
  set__compiler__included_files(get__empty_insert_order_set());
  // 224: %%compiler::linked_libraries empty_insert_order_set
  set__compiler__linked_libraries(get__empty_insert_order_set());
  // 225: %%compiler::dependent_data empty_insert_order_set
  set__compiler__dependent_data(get__empty_insert_order_set());
  // 226: %%compiler::global_names empty_key_order_table
  set__compiler__global_names(get__empty_key_order_table());
  // 227: %%compiler::exported_names empty_key_order_table
  set__compiler__exported_names(get__empty_key_order_table());
  // 228: %%compiler::needed_names empty_key_order_table
  set__compiler__needed_names(get__empty_key_order_table());
  // 229: %%compiler::assigned_names empty_set
  set__compiler__assigned_names(get__empty_set());
  // 230: %%compiler::string_literals empty_table
  set__compiler__string_literals(get__empty_table());
  // 231: %%compiler::use_inline_c false # set, if an inline-C expression is encountered
  set__compiler__use_inline_c(get__false());
  // 232: %%compiler::defined_structs set("NODE")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5e0ae28b5c407d7c;
  result_count = 1;
  myself = get__set();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_43;
}
static void entry__compiler__sim2c_2(void) {
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
  arguments->slots[1] = string__2d7981f4e6782bea;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_4;
}
static void cont__compiler__sim2c_4(void) {
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
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_5, 0);
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
  frame->cont = cont__compiler__sim2c_16;
}
static void entry__compiler__sim2c_7(void) {
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
  frame->cont = cont__compiler__sim2c_8;
}
static void cont__compiler__sim2c_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 214: ... before(module_name "__" -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_9;
}
static void cont__compiler__sim2c_9(void) {
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
  frame->cont = cont__compiler__sim2c_10;
}
static void cont__compiler__sim2c_10(void) {
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
  frame->cont = cont__compiler__sim2c_11;
}
static void cont__compiler__sim2c_11(void) {
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
  frame->cont = cont__compiler__sim2c_12;
}
static void cont__compiler__sim2c_12(void) {
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
static void entry__compiler__sim2c_13(void) {
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
  frame->cont = cont__compiler__sim2c_14;
}
static void cont__compiler__sim2c_14(void) {
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
  frame->cont = cont__compiler__sim2c_15;
}
static void cont__compiler__sim2c_15(void) {
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
static void entry__compiler__sim2c_5(void) {
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
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_6;
}
static void cont__compiler__sim2c_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 213: ... :
  // 214:   !name before(module_name "__" -1) .append. range(name 2 -1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_7, 0);
  // 215: :
  // 216:   !name range(name 3 -1)
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__sim2c_13, 0);
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
static void cont__compiler__sim2c_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 217: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_17;
}
static void cont__compiler__sim2c_17(void) {
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
  frame->cont = cont__compiler__sim2c_18;
}
static void cont__compiler__sim2c_18(void) {
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
static void entry__compiler__sim2c_19(void) {
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
  // 401: mangled_name .contains. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_20;
}
static void cont__compiler__sim2c_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 401: ... :
  // 402:   $namespace mangled_name .before. "__"
  // 403:   $name mangled_name .behind. "__"
  // 404:   $namespaces exported_names(name)
  // 405:   if namespaces.is_defined && namespaces(namespace).is_defined return
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_21, 0);
  // 406: :
  // 407:   $definition global_names(mangled_name)
  // 408:   if definition.is_defined:
  // 409:     check_usage mangled_name definition info
  // 410:     return
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__sim2c_30, 0);
  // 400: if
  // 401:   mangled_name .contains. "__":
  // 402:     $namespace mangled_name .before. "__"
  // 403:     $name mangled_name .behind. "__"
  // 404:     $namespaces exported_names(name)
  // 405:     if namespaces.is_defined && namespaces(namespace).is_defined return
  // 406:   :
  // 407:     $definition global_names(mangled_name)
  // 408:     if definition.is_defined:
  // 409:       check_usage mangled_name definition info
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_35;
}
static void entry__compiler__sim2c_33(void) {
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
  // 409: check_usage mangled_name definition info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[1] /* definition */;
  arguments->slots[2] = frame->slots[2] /* info */;
  result_count = 0;
  myself = get__check_usage();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_34;
}
static void cont__compiler__sim2c_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 410: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_21(void) {
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
  // 402: $namespace mangled_name .before. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_22;
}
static void cont__compiler__sim2c_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 403: $name mangled_name .behind. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_23;
}
static void cont__compiler__sim2c_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* name */, arguments->slots[0]);
  // 404: $namespaces exported_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* name */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_24;
}
static void cont__compiler__sim2c_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* namespaces */, arguments->slots[0]);
  // 405: ... namespaces.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* namespaces */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_25;
}
static void cont__compiler__sim2c_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 405: ... namespaces(namespace).is_defined
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_26, 0);
  // 405: ... namespaces.is_defined && namespaces(namespace).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_29;
}
static void entry__compiler__sim2c_26(void) {
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
  // 405: ... namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = frame->slots[0] /* namespaces */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_27;
}
static void cont__compiler__sim2c_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 405: ... namespaces(namespace).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_28;
}
static void cont__compiler__sim2c_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 405: ... namespaces(namespace).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 405: if namespaces.is_defined && namespaces(namespace).is_defined return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* return */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_30(void) {
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
  // 407: $definition global_names(mangled_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_31;
}
static void cont__compiler__sim2c_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* definition */, arguments->slots[0]);
  // 408: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_32;
}
static void cont__compiler__sim2c_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 408: ... :
  // 409:   check_usage mangled_name definition info
  // 410:   return
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_33, 0);
  // 408: if definition.is_defined:
  // 409:   check_usage mangled_name definition info
  // 410:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 411: ... needed_names(mangled_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  result_count = 1;
  myself = get__needed_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_36;
}
static void cont__compiler__sim2c_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 411: $updated_info update_info(mangled_name needed_names(mangled_name) info)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__update_info();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_37;
}
static void cont__compiler__sim2c_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* updated_info */, arguments->slots[0]);
  // 412: ... updated_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* updated_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_38;
}
static void cont__compiler__sim2c_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 412: ... : !needed_names(mangled_name) updated_info
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_39, 0);
  // 412: if updated_info.is_defined: !needed_names(mangled_name) updated_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_41;
}
static void entry__compiler__sim2c_39(void) {
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
  // 412: ... !needed_names(mangled_name) updated_info
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* updated_info */;
  // 412: ... !needed_names(mangled_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__needed_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_40;
}
static void cont__compiler__sim2c_40(void) {
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
static void cont__compiler__sim2c_41(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__compiler__defined_structs(arguments->slots[0]);
  // 233: ... c_code(.source_of "")
  {
    NODE *temp = clone_object_and_attributes(get__c_code());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_of, empty_string);
    frame->slots[34] /* temp__2 */ = temp;

  }
  // 233: ... "SIMPLE_NODE" = c_code(.source_of "")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1c6c7289032a5d69;
  arguments->slots[1] = frame->slots[34] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_45;
}
static void cont__compiler__sim2c_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 233: %%compiler::defined_nodes table("SIMPLE_NODE" = c_code(.source_of ""))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_46;
}
static void cont__compiler__sim2c_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__compiler__defined_nodes(arguments->slots[0]);
  // 234: %%compiler::defined_functions empty_set
  set__compiler__defined_functions(get__empty_set());
  // 235: %%compiler::enumeration_count 0
  set__compiler__enumeration_count(number__0);
  // 236: $$fragments empty_list
  ((CELL *)frame->slots[4])->contents /* fragments */ = get__empty_list();
  // 237: $$trees empty_list
  ((CELL *)frame->slots[5])->contents /* trees */ = get__empty_list();
  // 238: $$all_defined_names empty_list
  ((CELL *)frame->slots[6])->contents /* all_defined_names */ = get__empty_list();
  // 239: $$all_used_names empty_list
  ((CELL *)frame->slots[7])->contents /* all_used_names */ = get__empty_list();
  // 240: ... : (no filename)
  // 241:   $$buf load(filename)
  // 242:   try
  // 243:     :
  // 244:       from_utf8 &buf
  // 245:     :
  // 246:       Error "Source file is not in a valid utf-8-encoding!"
  // 247:   if do_show_debug_infos:
  // 248:     ewrite "
  // 249:       load "@(filename)@quot;
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_47, 2);
  // 240: for_each filenames: (no filename)
  // 241:   $$buf load(filename)
  // 242:   try
  // 243:     :
  // 244:       from_utf8 &buf
  // 245:     :
  // 246:       Error "Source file is not in a valid utf-8-encoding!"
  // 247:   if do_show_debug_infos:
  // 248:     ewrite "
  // 249:       load "@(filename)@quot;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filenames */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_113;
}
static void entry__compiler__sim2c_47(void) {
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
  define__compiler__submodule_no(create_future());
  frame->slots[7] /* submodule_fragments */ = create_cell();
  frame->slots[8] /* first_idx */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 241: $$buf load(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_48;
}
static void cont__compiler__sim2c_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* buf */ = arguments->slots[0];
  // 243: :
  // 244:   from_utf8 &buf
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_49, 0);
  // 242: try
  // 243:   :
  // 244:     from_utf8 &buf
  // 245:   :
  // 246:     Error "Source file is not in a valid utf-8-encoding!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_51;
  result_count = 0;
  myself = get__try();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_53;
}
static void entry__compiler__sim2c_49(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 244: from_utf8 &buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_50;
}
static void cont__compiler__sim2c_50(void) {
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
static void entry__compiler__sim2c_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 246: Error "Source file is not in a valid utf-8-encoding!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38b3477328e1d61b;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 247: ... :
  // 248:   ewrite "
  // 249:     load "@(filename)@quot;
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_54, 0);
  // 247: if do_show_debug_infos:
  // 248:   ewrite "
  // 249:     load "@(filename)@quot;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_58;
}
static void entry__compiler__sim2c_54(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 248: ... "
  // 249:   load "@(filename)@quot;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__5a1f574683baa2f5;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__2d7981f4e6182bcf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_57;
}
static void cont__compiler__sim2c_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 248: ewrite "
  // 249:   load "@(filename)@quot;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 250: ... : write_timing_info "loading" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_59, 0);
  // 250: if do_time_passes: write_timing_info "loading" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_61;
}
static void entry__compiler__sim2c_59(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 250: ... write_timing_info "loading" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ba340f9515cad09d;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 251: ... length_of(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* buf */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_62;
}
static void cont__compiler__sim2c_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 251: ... length_of(buf) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_63;
}
static void cont__compiler__sim2c_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 251: if length_of(buf) == 0: Error "Empty source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_64;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_66;
}
static void entry__compiler__sim2c_64(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 251: ... Error "Empty source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1cbf9967f0b4797a;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 252: ... buf(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[6])->contents /* buf */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_67;
}
static void cont__compiler__sim2c_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 252: ... buf(1) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[11] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_68;
}
static void cont__compiler__sim2c_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 252: ... buf(1) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_69;
}
static void cont__compiler__sim2c_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 252: if buf(1) <= ' ': Error "Whitespace at start of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_70;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_72;
}
static void entry__compiler__sim2c_70(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 252: ... Error "Whitespace at start of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__cdb2cfe249b97e8f;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 253: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_73;
}
static void cont__compiler__sim2c_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__4 */ = arguments->slots[0];
  // 253: ... buf(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__4 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[6])->contents /* buf */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_74;
}
static void cont__compiler__sim2c_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__3 */ = arguments->slots[0];
  // 253: ... buf(-1) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_75;
}
static void cont__compiler__sim2c_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 253: ... buf(-1) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_76;
}
static void cont__compiler__sim2c_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 253: if buf(-1) != newline: Error "Missing newline at end of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_77;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_79;
}
static void entry__compiler__sim2c_77(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 253: ... Error "Missing newline at end of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f5ba012e5873af55;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 254: ... buf .has_prefix. "#!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* buf */;
  arguments->slots[1] = string__2d7981f4e6102be4;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_81;
}
static void cont__compiler__sim2c_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 254: ... : !is_main true
  frame->slots[10] /* temp__2 */ = create_closure(entry__compiler__sim2c_82, 0);
  // 254: if buf .has_prefix. "#!": !is_main true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_83;
}
static void entry__compiler__sim2c_82(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 254: ... !is_main true
  ((CELL *)frame->slots[0])->contents /* is_main */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 255: %compiler::submodule_no no-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* no */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_84;
}
static void cont__compiler__sim2c_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__submodule_no(), arguments->slots[0]);
  // 256: $$submodule_fragments cut_into_fragments(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* buf */;
  result_count = 1;
  myself = get__cut_into_fragments();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_85;
}
static void cont__compiler__sim2c_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* submodule_fragments */ = arguments->slots[0];
  // 257: ... : write_timing_info "fragmenting" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_86, 0);
  // 257: if do_time_passes: write_timing_info "fragmenting" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_88;
}
static void entry__compiler__sim2c_86(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 257: ... write_timing_info "fragmenting" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28e9a3192e794ba6;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 258: update_each &submodule_fragments: (&fragment) tokenize &fragment
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* submodule_fragments */;
  arguments->slots[1] = func__compiler__sim2c_89;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_91;
}
static void entry__compiler__sim2c_89(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fragment: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* fragment */ = create_cell_with_contents(arguments->slots[0]);
  // 258: ... tokenize &fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  result_count = 1;
  myself = get__tokenize();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_90;
}
static void cont__compiler__sim2c_90(void) {
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
static void cont__compiler__sim2c_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* submodule_fragments */ = arguments->slots[0];
  // 259: ... : write_timing_info "tokenizing" filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_92, 0);
  // 259: if do_time_passes: write_timing_info "tokenizing" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_94;
}
static void entry__compiler__sim2c_92(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 259: ... write_timing_info "tokenizing" filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__170b25ca95be486;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_94(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 260: $$first_idx 1
  ((CELL *)frame->slots[8])->contents /* first_idx */ = number__1;
  // 261: ... : (-> done)
  // 262:   for_each submodule_fragments: (idx fragment)
  // 263:     case
  // 264:       source_of(fragment)(1)
  // 265:       '#':
  // 266:         !first_idx idx+1
  // 267:         push &trees parse_statement(fragment)
  // 268:       '<':
  // 269:         !first_idx idx+1
  // 270:         push &trees parse_meta_instruction(fragment)
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__compiler__sim2c_95, 0);
  // 261: do: (-> done)
  // 262:   for_each submodule_fragments: (idx fragment)
  // 263:     case
  // 264:       source_of(fragment)(1)
  // 265:       '#':
  // 266:         !first_idx idx+1
  // 267:         push &trees parse_statement(fragment)
  // 268:       '<':
  // 269:         !first_idx idx+1
  // 270:         push &trees parse_meta_instruction(fragment)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_109;
}
static void entry__compiler__sim2c_95(void) {
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
  // 262: ... : (idx fragment)
  // 263:   case
  // 264:     source_of(fragment)(1)
  // 265:     '#':
  // 266:       !first_idx idx+1
  // 267:       push &trees parse_statement(fragment)
  // 268:     '<':
  // 269:       !first_idx idx+1
  // 270:       push &trees parse_meta_instruction(fragment)
  // 271:     :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__compiler__sim2c_96, 2);
  // 262: for_each submodule_fragments: (idx fragment)
  // 263:   case
  // 264:     source_of(fragment)(1)
  // 265:     '#':
  // 266:       !first_idx idx+1
  // 267:       push &trees parse_statement(fragment)
  // 268:     '<':
  // 269:       !first_idx idx+1
  // 270:       push &trees parse_meta_instruction(fragment)
  // 271:     :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* submodule_fragments */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_108;
}
static void entry__compiler__sim2c_99(void) {
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
  // 266: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_100;
}
static void cont__compiler__sim2c_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 267: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_101;
}
static void cont__compiler__sim2c_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 267: push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* trees */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_102;
}
static void cont__compiler__sim2c_102(void) {
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
static void entry__compiler__sim2c_103(void) {
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
  // 269: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_104;
}
static void cont__compiler__sim2c_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 270: ... parse_meta_instruction(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* fragment */;
  result_count = 1;
  myself = get__parse_meta_instruction();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_105;
}
static void cont__compiler__sim2c_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 270: push &trees parse_meta_instruction(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* trees */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_106;
}
static void cont__compiler__sim2c_106(void) {
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
static void entry__compiler__sim2c_107(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // done: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* done */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 272: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_96(void) {
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
  // 264: source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fragment */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_97;
}
static void cont__compiler__sim2c_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 264: source_of(fragment)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[6] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_98;
}
static void cont__compiler__sim2c_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 265: ... :
  // 266:   !first_idx idx+1
  // 267:   push &trees parse_statement(fragment)
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_99, 0);
  // 268: ... :
  // 269:   !first_idx idx+1
  // 270:   push &trees parse_meta_instruction(fragment)
  frame->slots[8] /* temp__4 */ = create_closure(entry__compiler__sim2c_103, 0);
  // 271: :
  // 272:   done
  frame->slots[9] /* temp__5 */ = create_closure(entry__compiler__sim2c_107, 0);
  // 263: case
  // 264:   source_of(fragment)(1)
  // 265:   '#':
  // 266:     !first_idx idx+1
  // 267:     push &trees parse_statement(fragment)
  // 268:   '<':
  // 269:     !first_idx idx+1
  // 270:     push &trees parse_meta_instruction(fragment)
  // 271:   :
  // 272:     done
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
static void cont__compiler__sim2c_108(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_109(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 273: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_110;
}
static void cont__compiler__sim2c_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 273: ... range(submodule_fragments first_idx -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* submodule_fragments */;
  arguments->slots[1] = ((CELL *)frame->slots[8])->contents /* first_idx */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_111;
}
static void cont__compiler__sim2c_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 273: append &fragments range(submodule_fragments first_idx -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* fragments */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_112;
}
static void cont__compiler__sim2c_112(void) {
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
static void cont__compiler__sim2c_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 274: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_114, 1);
  // 274: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* fragments */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_117;
}
static void entry__compiler__sim2c_114(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fragment: 0
  // trees: 1
  frame->slots[1] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 274: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_115;
}
static void cont__compiler__sim2c_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 274: ... push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* trees */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_116;
}
static void cont__compiler__sim2c_116(void) {
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
static void cont__compiler__sim2c_117(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 275: ... : write_timing_info "parsing" filenames(1)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_118, 0);
  // 275: if do_time_passes: write_timing_info "parsing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_121;
}
static void entry__compiler__sim2c_118(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 275: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_119;
}
static void cont__compiler__sim2c_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 275: ... write_timing_info "parsing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__94440f9215cbe09d;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_121(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 276: ... :
  // 277:   #if do_show_compiler_debug_infos:
  // 278:     $$header_printed false
  // 279:     for_each global_names: (name type)
  // 280:       unless header_printed:
  // 281:         print_line "# Global variables"
  // 282:         !header_printed true
  // 283:       print_line "  " name
  // 284:   
  // 285:   print_trees trees
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_122, 0);
  // 276: if do_pretty_print:
  // 277:   #if do_show_compiler_debug_infos:
  // 278:     $$header_printed false
  // 279:     for_each global_names: (name type)
  // 280:       unless header_printed:
  // 281:         print_line "# Global variables"
  // 282:         !header_printed true
  // 283:       print_line "  " name
  // 284:   
  // 285:   print_trees trees
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_124;
}
static void entry__compiler__sim2c_122(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: print_trees trees
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  result_count = 0;
  myself = get__print_trees();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_123;
}
static void cont__compiler__sim2c_123(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 286: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_124(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 287: ... : # the main program should terminate cleanly
  // 288:   push &trees procedure_call(.functor_of std_identifier("terminate"))
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_125, 0);
  // 287: if is_main: # the main program should terminate cleanly
  // 288:   push &trees procedure_call(.functor_of std_identifier("terminate"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_129;
}
static void entry__compiler__sim2c_125(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 288: ... std_identifier("terminate")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__72f826ea16a3e460;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_127;
}
static void cont__compiler__sim2c_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 288: ... procedure_call(.functor_of std_identifier("terminate"))
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 288: push &trees procedure_call(.functor_of std_identifier("terminate"))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_128;
}
static void cont__compiler__sim2c_128(void) {
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
static void cont__compiler__sim2c_129(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 289: update_each &trees: (&tree)
  // 290:   %%compiler::index 1
  // 291:   expand_statement &tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = func__compiler__sim2c_130;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_132;
}
static void entry__compiler__sim2c_130(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // tree: 0
  // return__2: 1
  frame->slots[1] /* return__2 */ = create_continuation_with_exit(exit__compiler__sim2c_130);
  define__compiler__index(undefined);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* tree */ = create_cell_with_contents(arguments->slots[0]);
  // 290: %%compiler::index 1
  set__compiler__index(number__1);
  // 291: expand_statement &tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  result_count = 1;
  myself = get__expand_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_131;
}
static void cont__compiler__sim2c_131(void) {
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
static void exit__compiler__sim2c_130(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  func = continuation_type_function;
}
static void cont__compiler__sim2c_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* trees */ = arguments->slots[0];
  // 292: ... : write_timing_info "expanding" filenames(1)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_133, 0);
  // 292: if do_time_passes: write_timing_info "expanding" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_136;
}
static void entry__compiler__sim2c_133(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 292: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_134;
}
static void cont__compiler__sim2c_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 292: ... write_timing_info "expanding" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__66f024ec077397c2;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_136(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 293: ... : (&tree)
  // 294:   %%compiler::defined_names empty_list
  // 295:   %%compiler::used_names empty_insert_order_table
  // 296:   %%compiler::index 1
  // 297:   annotate_statement &tree
  // 298:   push &all_defined_names compiler::defined_names
  // 299:   push &all_used_names compiler::used_names
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_137, 1);
  // 293: update_each &trees: (&tree)
  // 294:   %%compiler::defined_names empty_list
  // 295:   %%compiler::used_names empty_insert_order_table
  // 296:   %%compiler::index 1
  // 297:   annotate_statement &tree
  // 298:   push &all_defined_names compiler::defined_names
  // 299:   push &all_used_names compiler::used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_141;
}
static void entry__compiler__sim2c_137(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // tree: 0
  // return__3: 1
  // all_defined_names: 2
  // all_used_names: 3
  frame->slots[1] /* return__3 */ = create_continuation_with_exit(exit__compiler__sim2c_137);
  frame->slots[2] = myself->closure.frame->slots[6]; /* all_defined_names */
  frame->slots[3] = myself->closure.frame->slots[7]; /* all_used_names */
  define__compiler__defined_names(undefined);
  define__compiler__used_names(undefined);
  define__compiler__index(undefined);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* tree */ = create_cell_with_contents(arguments->slots[0]);
  // 294: %%compiler::defined_names empty_list
  set__compiler__defined_names(get__empty_list());
  // 295: %%compiler::used_names empty_insert_order_table
  set__compiler__used_names(get__empty_insert_order_table());
  // 296: %%compiler::index 1
  set__compiler__index(number__1);
  // 297: annotate_statement &tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  result_count = 1;
  myself = get__annotate_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_138;
}
static void cont__compiler__sim2c_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tree */ = arguments->slots[0];
  // 298: push &all_defined_names compiler::defined_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* all_defined_names */;
  arguments->slots[1] = get__compiler__defined_names();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_139;
}
static void cont__compiler__sim2c_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* all_defined_names */ = arguments->slots[0];
  // 299: push &all_used_names compiler::used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_used_names */;
  arguments->slots[1] = get__compiler__used_names();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_140;
}
static void cont__compiler__sim2c_140(void) {
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
static void exit__compiler__sim2c_137(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tree */;
  func = continuation_type_function;
}
static void cont__compiler__sim2c_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* trees */ = arguments->slots[0];
  // 300: ... : write_timing_info "annotating" filenames(1)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_142, 0);
  // 300: if do_time_passes: write_timing_info "annotating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_145;
}
static void entry__compiler__sim2c_142(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 300: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_143;
}
static void cont__compiler__sim2c_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 300: ... write_timing_info "annotating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1d581a51a85b6426;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_145(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 301: $$all_actions empty_list
  ((CELL *)frame->slots[8])->contents /* all_actions */ = get__empty_list();
  // 303: $$top_level_names
  // 304:   if(do_print_warnings (-> empty_insert_order_table) -> empty_table)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = func__compiler__sim2c_146;
  arguments->slots[2] = func__compiler__sim2c_147;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_148;
}
static void entry__compiler__sim2c_146(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 304: ... -> empty_insert_order_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_insert_order_table();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_147(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 304: ... -> empty_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__empty_table();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* top_level_names */ = arguments->slots[0];
  // 306: ... required_modules.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_149;
}
static void cont__compiler__sim2c_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__2 */ = arguments->slots[0];
  // 306: ... is_main
  frame->slots[35] /* temp__3 */ = create_closure(entry__compiler__sim2c_150, 0);
  // 306: ... required_modules.is_empty && is_main
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__2 */;
  arguments->slots[1] = frame->slots[35] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_151;
}
static void entry__compiler__sim2c_150(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: ... is_main
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_151(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 306: if required_modules.is_empty && is_main:
  // 307:   !required_modules("basic/stdlib") types::grammar_node
  // 308:   !required_modules("system/stdlib") types::grammar_node
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_152;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_157;
}
static void entry__compiler__sim2c_152(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 307: !required_modules("basic/stdlib") types::grammar_node
  frame->slots[0] /* temp__1 */ = get__types__grammar_node();
  // 307: !required_modules("basic/stdlib")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__c3e1e344d34946eb;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_154;
}
static void cont__compiler__sim2c_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__required_modules(arguments->slots[0]);
  // 308: !required_modules("system/stdlib") types::grammar_node
  frame->slots[0] /* temp__1 */ = get__types__grammar_node();
  // 308: !required_modules("system/stdlib")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b567219b137172d;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_156;
}
static void cont__compiler__sim2c_156(void) {
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
static void cont__compiler__sim2c_157(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 309: !required_modules("nothing") undefined
  frame->slots[33] /* temp__1 */ = get__undefined();
  // 309: !required_modules("nothing")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a23c0f9515cb809d;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 1;
  myself = get__required_modules();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_159;
}
static void cont__compiler__sim2c_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__required_modules(arguments->slots[0]);
  // 310: ... used_namespaces.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_160;
}
static void cont__compiler__sim2c_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 310: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_161;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_164;
}
static void entry__compiler__sim2c_161(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 310: ... !used_namespaces("std") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 310: ... !used_namespaces("std")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa724815d896ba8;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_163;
}
static void cont__compiler__sim2c_163(void) {
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
static void cont__compiler__sim2c_164(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 311: !used_namespaces("nothing") false
  frame->slots[33] /* temp__1 */ = get__false();
  // 311: !used_namespaces("nothing")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a23c0f9515cb809d;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_165;
}
static void cont__compiler__sim2c_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_namespaces(arguments->slots[0]);
  // 312: ... : (defined_names)
  // 313:   for_each defined_names: (info)
  // 314:     $ident identifier_of(info)
  // 315:     unless
  // 316:       info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 317:         $namespace namespace_of(ident)
  // 318:         $name name_of(ident)
  // 319:         if
  // 320:           namespace.is_defined:
  // 321:             $$namespaces exported_names(name)
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_166, 1);
  // 312: for_each all_defined_names: (defined_names)
  // 313:   for_each defined_names: (info)
  // 314:     $ident identifier_of(info)
  // 315:     unless
  // 316:       info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 317:         $namespace namespace_of(ident)
  // 318:         $name name_of(ident)
  // 319:         if
  // 320:           namespace.is_defined:
  // 321:             $$namespaces exported_names(name)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* all_defined_names */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_235;
}
static void entry__compiler__sim2c_178(void) {
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
  // 321: $$namespaces exported_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_179;
}
static void cont__compiler__sim2c_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* namespaces */ = arguments->slots[0];
  // 322: ... namespaces.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* namespaces */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_180;
}
static void cont__compiler__sim2c_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 322: ... : !namespaces table()
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_181, 0);
  // 322: unless namespaces.is_defined: !namespaces table()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_183;
}
static void entry__compiler__sim2c_181(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // namespaces: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* namespaces */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 322: ... !namespaces table()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_182;
}
static void cont__compiler__sim2c_182(void) {
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
static void cont__compiler__sim2c_183(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 323: ... namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* namespaces */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_184;
}
static void cont__compiler__sim2c_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 323: ... namespaces(namespace).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_185;
}
static void cont__compiler__sim2c_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 323: ... :
  // 324:   SyntaxError identifier_of(info) "
  // 325:     An identifier named "@(namespace)::@(name)" was already @
  // 326:     defined@
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_186, 0);
  // 323: if namespaces(namespace).is_defined:
  // 324:   SyntaxError identifier_of(info) "
  // 325:     An identifier named "@(namespace)::@(name)" was already @
  // 326:     defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_191;
}
static void entry__compiler__sim2c_186(void) {
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
  // 324: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_187;
}
static void cont__compiler__sim2c_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 324: ... "
  // 325:   An identifier named "@(namespace)::@(name)" was already @
  // 326:   defined@
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__b18861f6a8c886ba;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__2d7981f4e6d82bff;
  arguments->slots[3] = frame->slots[2] /* name */;
  arguments->slots[4] = string__95b7f6cc14260ab8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_190;
}
static void cont__compiler__sim2c_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 324: SyntaxError identifier_of(info) "
  // 325:   An identifier named "@(namespace)::@(name)" was already @
  // 326:   defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_191(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 327: ... used_namespaces(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_192;
}
static void cont__compiler__sim2c_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 327: ... :
  // 328:   if global_names(name).is_defined:
  // 329:     SyntaxError identifier_of(info) "
  // 330:       The definition of "@(namespace)::@(name)" clashes with the @
  // 331:       already defined identifier "@(name)@quot;@
  // 332:   $info_1 top_level_names(name)
  // 333:   if info_1.is_defined:
  // 334:     SyntaxError identifier_of(info) "
  // 335:       The definition of "@(namespace)::@(name)" clashes with the @
  // 336:       definition of "@(namespace_of(identifier_of(info_1)))@
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_193, 0);
  // 327: if used_namespaces(namespace):
  // 328:   if global_names(name).is_defined:
  // 329:     SyntaxError identifier_of(info) "
  // 330:       The definition of "@(namespace)::@(name)" clashes with the @
  // 331:       already defined identifier "@(name)@quot;@
  // 332:   $info_1 top_level_names(name)
  // 333:   if info_1.is_defined:
  // 334:     SyntaxError identifier_of(info) "
  // 335:       The definition of "@(namespace)::@(name)" clashes with the @
  // 336:       definition of "@(namespace_of(identifier_of(info_1)))@
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_214;
}
static void entry__compiler__sim2c_193(void) {
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
  // 328: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_194;
}
static void cont__compiler__sim2c_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 328: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_195;
}
static void cont__compiler__sim2c_195(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 328: ... :
  // 329:   SyntaxError identifier_of(info) "
  // 330:     The definition of "@(namespace)::@(name)" clashes with the @
  // 331:     already defined identifier "@(name)@quot;@
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_196, 0);
  // 328: if global_names(name).is_defined:
  // 329:   SyntaxError identifier_of(info) "
  // 330:     The definition of "@(namespace)::@(name)" clashes with the @
  // 331:     already defined identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_202;
}
static void entry__compiler__sim2c_196(void) {
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
  // 329: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_197;
}
static void cont__compiler__sim2c_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 329: ... "
  // 330:   The definition of "@(namespace)::@(name)" clashes with the @
  // 331:   already defined identifier "@(name)@quot;@
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__69658745890c070;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__2d7981f4e6d82bff;
  arguments->slots[3] = frame->slots[2] /* name */;
  arguments->slots[4] = string__c419bd2045fe53aa;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_201;
}
static void cont__compiler__sim2c_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 329: SyntaxError identifier_of(info) "
  // 330:   The definition of "@(namespace)::@(name)" clashes with the @
  // 331:   already defined identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_202(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 332: $info_1 top_level_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_203;
}
static void cont__compiler__sim2c_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* info_1 */, arguments->slots[0]);
  // 333: ... info_1.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* info_1 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_204;
}
static void cont__compiler__sim2c_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 333: ... :
  // 334:   SyntaxError identifier_of(info) "
  // 335:     The definition of "@(namespace)::@(name)" clashes with the @
  // 336:     definition of "@(namespace_of(identifier_of(info_1)))@
  // 337:     ::@(name)" because both namespaces are used@
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_205, 0);
  // 333: if info_1.is_defined:
  // 334:   SyntaxError identifier_of(info) "
  // 335:     The definition of "@(namespace)::@(name)" clashes with the @
  // 336:     definition of "@(namespace_of(identifier_of(info_1)))@
  // 337:     ::@(name)" because both namespaces are used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_212;
}
static void entry__compiler__sim2c_205(void) {
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
  // 334: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_206;
}
static void cont__compiler__sim2c_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 336: ... identifier_of(info_1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info_1 */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_207;
}
static void cont__compiler__sim2c_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 336: ... namespace_of(identifier_of(info_1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_208;
}
static void cont__compiler__sim2c_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 334: ... "
  // 335:   The definition of "@(namespace)::@(name)" clashes with the @
  // 336:   definition of "@(namespace_of(identifier_of(info_1)))@
  // 337:   ::@(name)" because both namespaces are used@
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__69658745890c070;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = string__2d7981f4e6d82bff;
  arguments->slots[3] = frame->slots[2] /* name */;
  arguments->slots[4] = string__b5bb4d11daae5f7a;
  arguments->slots[5] = frame->slots[6] /* temp__3 */;
  arguments->slots[6] = string__2d7981f4e6d82bff;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__6de219341b32224c;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_211;
}
static void cont__compiler__sim2c_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 334: SyntaxError identifier_of(info) "
  // 335:   The definition of "@(namespace)::@(name)" clashes with the @
  // 336:   definition of "@(namespace_of(identifier_of(info_1)))@
  // 337:   ::@(name)" because both namespaces are used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_212(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 338: !top_level_names(name) info
  frame->slots[5] /* temp__1 */ = frame->slots[1] /* info */;
  // 338: !top_level_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_213;
}
static void cont__compiler__sim2c_213(void) {
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
static void cont__compiler__sim2c_214(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 339: !namespaces(namespace) info
  frame->slots[5] /* temp__1 */ = frame->slots[2] /* info */;
  // 339: !namespaces(namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* namespaces */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_215;
}
static void cont__compiler__sim2c_215(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* namespaces */ = arguments->slots[0];
  // 340: !exported_names(name) namespaces
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* namespaces */;
  // 340: !exported_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_216;
}
static void cont__compiler__sim2c_216(void) {
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
static void entry__compiler__sim2c_217(void) {
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
  // 342: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_218;
}
static void cont__compiler__sim2c_218(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 342: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_219;
}
static void cont__compiler__sim2c_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 342: ... :
  // 343:   SyntaxError identifier_of(info) "
  // 344:     An identifier named "@(name)" was already defined@
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__sim2c_220, 0);
  // 342: if global_names(name).is_defined:
  // 343:   SyntaxError identifier_of(info) "
  // 344:     An identifier named "@(name)" was already defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_223;
}
static void entry__compiler__sim2c_220(void) {
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
  // 343: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_221;
}
static void cont__compiler__sim2c_221(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 343: ... "
  // 344:   An identifier named "@(name)" was already defined@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b18861f6a8c886ba;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__95b7f6cc14260ab8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_222;
}
static void cont__compiler__sim2c_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 343: SyntaxError identifier_of(info) "
  // 344:   An identifier named "@(name)" was already defined@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_223(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 345: $namespaces exported_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__exported_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_224;
}
static void cont__compiler__sim2c_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespaces */, arguments->slots[0]);
  // 346: ... namespaces.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespaces */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_225;
}
static void cont__compiler__sim2c_225(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 346: ... :
  // 347:   for_each namespaces: (nspace _dummy)
  // 348:     if used_namespaces(nspace):
  // 349:       SyntaxError identifier_of(info) "
  // 350:         The definition of "@(name)" clashes with the already @
  // 351:         defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_226, 0);
  // 346: if namespaces.is_defined:
  // 347:   for_each namespaces: (nspace _dummy)
  // 348:     if used_namespaces(nspace):
  // 349:       SyntaxError identifier_of(info) "
  // 350:         The definition of "@(name)" clashes with the already @
  // 351:         defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_232;
}
static void entry__compiler__sim2c_229(void) {
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
  // 349: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_230;
}
static void cont__compiler__sim2c_230(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 349: ... "
  // 350:   The definition of "@(name)" clashes with the already @
  // 351:   defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__69658745890c070;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__c419bd2045fe53aa;
  arguments->slots[3] = frame->slots[2] /* nspace */;
  arguments->slots[4] = string__2d7981f4e6d82bff;
  arguments->slots[5] = frame->slots[1] /* name */;
  arguments->slots[6] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_231;
}
static void cont__compiler__sim2c_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 349: SyntaxError identifier_of(info) "
  // 350:   The definition of "@(name)" clashes with the already @
  // 351:   defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_227(void) {
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
  // 348: ... used_namespaces(nspace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* nspace */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_228;
}
static void cont__compiler__sim2c_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 348: ... :
  // 349:   SyntaxError identifier_of(info) "
  // 350:     The definition of "@(name)" clashes with the already @
  // 351:     defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_229, 0);
  // 348: if used_namespaces(nspace):
  // 349:   SyntaxError identifier_of(info) "
  // 350:     The definition of "@(name)" clashes with the already @
  // 351:     defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_226(void) {
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
  // 347: ... : (nspace _dummy)
  // 348:   if used_namespaces(nspace):
  // 349:     SyntaxError identifier_of(info) "
  // 350:       The definition of "@(name)" clashes with the already @
  // 351:       defined identifier "@(nspace)::@(name)@quot;@
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_227, 2);
  // 347: for_each namespaces: (nspace _dummy)
  // 348:   if used_namespaces(nspace):
  // 349:     SyntaxError identifier_of(info) "
  // 350:       The definition of "@(name)" clashes with the already @
  // 351:       defined identifier "@(nspace)::@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespaces */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 352: !global_names(name) info
  frame->slots[4] /* temp__1 */ = frame->slots[1] /* info */;
  // 352: !global_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_233;
}
static void cont__compiler__sim2c_233(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__global_names(arguments->slots[0]);
  // 353: !top_level_names(name) info
  frame->slots[4] /* temp__1 */ = frame->slots[1] /* info */;
  // 353: !top_level_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* top_level_names */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_234;
}
static void cont__compiler__sim2c_234(void) {
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
static void entry__compiler__sim2c_174(void) {
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
  // 317: $namespace namespace_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_175;
}
static void cont__compiler__sim2c_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespace */, arguments->slots[0]);
  // 318: $name name_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_176;
}
static void cont__compiler__sim2c_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 320: namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_177;
}
static void cont__compiler__sim2c_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 320: ... :
  // 321:   $$namespaces exported_names(name)
  // 322:   unless namespaces.is_defined: !namespaces table()
  // 323:   if namespaces(namespace).is_defined:
  // 324:     SyntaxError identifier_of(info) "
  // 325:       An identifier named "@(namespace)::@(name)" was already @
  // 326:       defined@
  // 327:   if used_namespaces(namespace):
  // 328:     if global_names(name).is_defined:
  // 329:       SyntaxError identifier_of(info) "
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_178, 0);
  // 341: :
  // 342:   if global_names(name).is_defined:
  // 343:     SyntaxError identifier_of(info) "
  // 344:       An identifier named "@(name)" was already defined@
  // 345:   $namespaces exported_names(name)
  // 346:   if namespaces.is_defined:
  // 347:     for_each namespaces: (nspace _dummy)
  // 348:       if used_namespaces(nspace):
  // 349:         SyntaxError identifier_of(info) "
  // 350:           The definition of "@(name)" clashes with the already @
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_217, 0);
  // 319: if
  // 320:   namespace.is_defined:
  // 321:     $$namespaces exported_names(name)
  // 322:     unless namespaces.is_defined: !namespaces table()
  // 323:     if namespaces(namespace).is_defined:
  // 324:       SyntaxError identifier_of(info) "
  // 325:         An identifier named "@(namespace)::@(name)" was already @
  // 326:         defined@
  // 327:     if used_namespaces(namespace):
  // 328:       if global_names(name).is_defined:
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
static void entry__compiler__sim2c_167(void) {
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
  // 314: $ident identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_168;
}
static void cont__compiler__sim2c_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ident */, arguments->slots[0]);
  // 316: info.is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_169;
}
static void cont__compiler__sim2c_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 316: ... attribute_of(info).is_defined
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__sim2c_170, 0);
  // 316: info.is_a_static_single_definition && attribute_of(info).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_173;
}
static void entry__compiler__sim2c_170(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 316: ... attribute_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_171;
}
static void cont__compiler__sim2c_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 316: ... attribute_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_172;
}
static void cont__compiler__sim2c_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 316: ... attribute_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 316: ... :
  // 317:   $namespace namespace_of(ident)
  // 318:   $name name_of(ident)
  // 319:   if
  // 320:     namespace.is_defined:
  // 321:       $$namespaces exported_names(name)
  // 322:       unless namespaces.is_defined: !namespaces table()
  // 323:       if namespaces(namespace).is_defined:
  // 324:         SyntaxError identifier_of(info) "
  // 325:           An identifier named "@(namespace)::@(name)" was already @
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__sim2c_174, 0);
  // 315: unless
  // 316:   info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 317:     $namespace namespace_of(ident)
  // 318:     $name name_of(ident)
  // 319:     if
  // 320:       namespace.is_defined:
  // 321:         $$namespaces exported_names(name)
  // 322:         unless namespaces.is_defined: !namespaces table()
  // 323:         if namespaces(namespace).is_defined:
  // 324:           SyntaxError identifier_of(info) "
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
static void entry__compiler__sim2c_166(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // defined_names: 0
  // top_level_names: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* top_level_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 313: ... : (info)
  // 314:   $ident identifier_of(info)
  // 315:   unless
  // 316:     info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 317:       $namespace namespace_of(ident)
  // 318:       $name name_of(ident)
  // 319:       if
  // 320:         namespace.is_defined:
  // 321:           $$namespaces exported_names(name)
  // 322:           unless namespaces.is_defined: !namespaces table()
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_167, 1);
  // 313: for_each defined_names: (info)
  // 314:   $ident identifier_of(info)
  // 315:   unless
  // 316:     info.is_a_static_single_definition && attribute_of(info).is_defined:
  // 317:       $namespace namespace_of(ident)
  // 318:       $name name_of(ident)
  // 319:       if
  // 320:         namespace.is_defined:
  // 321:           $$namespaces exported_names(name)
  // 322:           unless namespaces.is_defined: !namespaces table()
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
static void cont__compiler__sim2c_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: ... :
  // 355:   $$top_level_used_names empty_insert_order_table
  // 356:   for_each all_used_names: (used_names)
  // 357:     for_each used_names: (mangled_name info)
  // 358:       !top_level_used_names(mangled_name) info
  // 359:   check_definitions top_level_names top_level_used_names
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_236, 0);
  // 354: if do_print_warnings:
  // 355:   $$top_level_used_names empty_insert_order_table
  // 356:   for_each all_used_names: (used_names)
  // 357:     for_each used_names: (mangled_name info)
  // 358:       !top_level_used_names(mangled_name) info
  // 359:   check_definitions top_level_names top_level_used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_241;
}
static void entry__compiler__sim2c_236(void) {
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
  // 355: $$top_level_used_names empty_insert_order_table
  ((CELL *)frame->slots[2])->contents /* top_level_used_names */ = get__empty_insert_order_table();
  // 356: ... : (used_names)
  // 357:   for_each used_names: (mangled_name info)
  // 358:     !top_level_used_names(mangled_name) info
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_237, 1);
  // 356: for_each all_used_names: (used_names)
  // 357:   for_each used_names: (mangled_name info)
  // 358:     !top_level_used_names(mangled_name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* all_used_names */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_240;
}
static void entry__compiler__sim2c_238(void) {
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
  // 358: !top_level_used_names(mangled_name) info
  frame->slots[3] /* temp__1 */ = frame->slots[1] /* info */;
  // 358: !top_level_used_names(mangled_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* top_level_used_names */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_239;
}
static void cont__compiler__sim2c_239(void) {
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
static void entry__compiler__sim2c_237(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // used_names: 0
  // top_level_used_names: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* top_level_used_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 357: ... : (mangled_name info)
  // 358:   !top_level_used_names(mangled_name) info
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_238, 2);
  // 357: for_each used_names: (mangled_name info)
  // 358:   !top_level_used_names(mangled_name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* used_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_240(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 359: check_definitions top_level_names top_level_used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* top_level_names */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* top_level_used_names */;
  result_count = frame->caller_result_count;
  myself = get__check_definitions();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_241(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 360: ... : write_timing_info "analyzing" filenames(1)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_242, 0);
  // 360: if do_time_passes: write_timing_info "analyzing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_245;
}
static void entry__compiler__sim2c_242(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 360: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_243;
}
static void cont__compiler__sim2c_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 360: ... write_timing_info "analyzing" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5ab424ea8372e502;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_245(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 361: ... :
  // 362:   for_each trees: (tree) write debug_string(strip(tree) 0 99)
  // 363:   terminate
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_246, 0);
  // 361: if do_dump_trees:
  // 362:   for_each trees: (tree) write debug_string(strip(tree) 0 99)
  // 363:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_251;
}
static void entry__compiler__sim2c_246(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // trees: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* trees */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 362: for_each trees: (tree) write debug_string(strip(tree) 0 99)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* trees */;
  arguments->slots[1] = func__compiler__sim2c_247;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_250;
}
static void entry__compiler__sim2c_247(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // tree: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 362: ... strip(tree)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__strip();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_248;
}
static void cont__compiler__sim2c_248(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 362: ... debug_string(strip(tree) 0 99)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__99;
  result_count = 1;
  myself = get__debug_string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_249;
}
static void cont__compiler__sim2c_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 362: ... write debug_string(strip(tree) 0 99)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_250(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 363: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_251(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 364: $$all_definitions empty_list
  ((CELL *)frame->slots[10])->contents /* all_definitions */ = get__empty_list();
  // 365: $$all_statements empty_list
  ((CELL *)frame->slots[11])->contents /* all_statements */ = get__empty_list();
  // 366: $$max_temp_idx 0
  ((CELL *)frame->slots[12])->contents /* max_temp_idx */ = number__0;
  // 367: ... : (tree)
  // 368:   unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 369:     %%compiler::temp_idx 0
  // 370:     %%compiler::actions empty_list
  // 371:     %already_defined_names top_level_names
  // 372:     %%definitions empty_list
  // 373:     %%statements empty_list
  // 374:     simplify_statement tree
  // 375:     push &all_statements statements
  // 376:     push &all_definitions definitions
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_252, 1);
  // 367: for_each trees: (tree)
  // 368:   unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 369:     %%compiler::temp_idx 0
  // 370:     %%compiler::actions empty_list
  // 371:     %already_defined_names top_level_names
  // 372:     %%definitions empty_list
  // 373:     %%statements empty_list
  // 374:     simplify_statement tree
  // 375:     push &all_statements statements
  // 376:     push &all_definitions definitions
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* trees */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_265;
}
static void entry__compiler__sim2c_257(void) {
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
  define__compiler__temp_idx(undefined);
  define__compiler__actions(undefined);
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
  // 369: %%compiler::temp_idx 0
  set__compiler__temp_idx(number__0);
  // 370: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 371: %already_defined_names top_level_names
  initialize_maybe_future(get__already_defined_names(), ((CELL *)frame->slots[1])->contents /* top_level_names */);
  // 372: %%definitions empty_list
  set__definitions(get__empty_list());
  // 373: %%statements empty_list
  set__statements(get__empty_list());
  // 374: simplify_statement tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* tree */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_258;
}
static void cont__compiler__sim2c_258(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 375: push &all_statements statements
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_statements */;
  arguments->slots[1] = get__statements();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_259;
}
static void cont__compiler__sim2c_259(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* all_statements */ = arguments->slots[0];
  // 376: push &all_definitions definitions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* all_definitions */;
  arguments->slots[1] = get__definitions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_260;
}
static void cont__compiler__sim2c_260(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* all_definitions */ = arguments->slots[0];
  // 377: $tmp_idx temp_idx
  initialize_maybe_future(frame->slots[7] /* tmp_idx */, get__temp_idx());
  // 378: ... : extend_to &max_temp_idx tmp_idx
  frame->slots[8] /* temp__1 */ = create_closure(entry__compiler__sim2c_261, 0);
  // 378: push &actions: extend_to &max_temp_idx tmp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_263;
}
static void entry__compiler__sim2c_261(void) {
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
  // 378: ... extend_to &max_temp_idx tmp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  arguments->slots[1] = frame->slots[1] /* tmp_idx */;
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_262;
}
static void cont__compiler__sim2c_262(void) {
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
static void cont__compiler__sim2c_263(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 379: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_264;
}
static void cont__compiler__sim2c_264(void) {
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
static void entry__compiler__sim2c_252(void) {
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
  // 368: ... tree.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_253;
}
static void cont__compiler__sim2c_253(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 368: ... tree.is_a_meta_instruction
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__sim2c_254, 0);
  // 368: ... tree.is_a_remark || tree.is_a_meta_instruction
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_256;
}
static void entry__compiler__sim2c_254(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tree: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tree */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 368: ... tree.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  result_count = 1;
  myself = get__is_a_meta_instruction();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_255;
}
static void cont__compiler__sim2c_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 368: ... tree.is_a_meta_instruction
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_256(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 368: ... :
  // 369:   %%compiler::temp_idx 0
  // 370:   %%compiler::actions empty_list
  // 371:   %already_defined_names top_level_names
  // 372:   %%definitions empty_list
  // 373:   %%statements empty_list
  // 374:   simplify_statement tree
  // 375:   push &all_statements statements
  // 376:   push &all_definitions definitions
  // 377:   $tmp_idx temp_idx
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__compiler__sim2c_257, 0);
  // 368: unless tree.is_a_remark || tree.is_a_meta_instruction:
  // 369:   %%compiler::temp_idx 0
  // 370:   %%compiler::actions empty_list
  // 371:   %already_defined_names top_level_names
  // 372:   %%definitions empty_list
  // 373:   %%statements empty_list
  // 374:   simplify_statement tree
  // 375:   push &all_statements statements
  // 376:   push &all_definitions definitions
  // 377:   $tmp_idx temp_idx
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
static void cont__compiler__sim2c_265(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 380: for_each all_actions: (stmt_actions) for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* all_actions */;
  arguments->slots[1] = func__compiler__sim2c_266;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_268;
}
static void entry__compiler__sim2c_267(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // action: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 380: ... action
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* action */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_266(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt_actions: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 380: ... for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_actions */;
  arguments->slots[1] = func__compiler__sim2c_267;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_268(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 381: !all_actions empty_list
  ((CELL *)frame->slots[8])->contents /* all_actions */ = get__empty_list();
  // 382: ... : write_timing_info "simplifying" filenames(1)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_269, 0);
  // 382: if do_time_passes: write_timing_info "simplifying" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_272;
}
static void entry__compiler__sim2c_269(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 382: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_270;
}
static void cont__compiler__sim2c_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 382: ... write_timing_info "simplifying" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72ed7b1f2279c943;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_272(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 383: ... :
  // 384:   for_each all_definitions: (defs)
  // 385:     for_each defs: (def)
  // 386:       if
  // 387:         def.is_a_key_value_pair:
  // 388:           writeln "_define " key_of(def) ' ' std::value_of(def)
  // 389:         :
  // 390:           writeln "_define " def
  // 391:   for_each all_statements: (stmts) print_trees stmts
  // 392:   terminate
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_273, 0);
  // 383: if do_print_simplified_source:
  // 384:   for_each all_definitions: (defs)
  // 385:     for_each defs: (def)
  // 386:       if
  // 387:         def.is_a_key_value_pair:
  // 388:           writeln "_define " key_of(def) ' ' std::value_of(def)
  // 389:         :
  // 390:           writeln "_define " def
  // 391:   for_each all_statements: (stmts) print_trees stmts
  // 392:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_285;
}
static void entry__compiler__sim2c_273(void) {
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
  // 384: for_each all_definitions: (defs)
  // 385:   for_each defs: (def)
  // 386:     if
  // 387:       def.is_a_key_value_pair:
  // 388:         writeln "_define " key_of(def) ' ' std::value_of(def)
  // 389:       :
  // 390:         writeln "_define " def
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* all_definitions */;
  arguments->slots[1] = func__compiler__sim2c_274;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_282;
}
static void entry__compiler__sim2c_277(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // def: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* def */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 388: ... key_of(def)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_278;
}
static void cont__compiler__sim2c_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 388: ... std::value_of(def)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_279;
}
static void cont__compiler__sim2c_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 388: writeln "_define " key_of(def) ' ' std::value_of(def)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__7c84ae5484fdf7e0;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  arguments->slots[2] = character__32;
  arguments->slots[3] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_281(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // def: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* def */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 390: writeln "_define " def
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7c84ae5484fdf7e0;
  arguments->slots[1] = frame->slots[0] /* def */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_275(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // def: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 387: def.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* def */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_276;
}
static void cont__compiler__sim2c_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 387: ... :
  // 388:   writeln "_define " key_of(def) ' ' std::value_of(def)
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_277, 0);
  // 389: :
  // 390:   writeln "_define " def
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__sim2c_281, 0);
  // 386: if
  // 387:   def.is_a_key_value_pair:
  // 388:     writeln "_define " key_of(def) ' ' std::value_of(def)
  // 389:   :
  // 390:     writeln "_define " def
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
static void entry__compiler__sim2c_274(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // defs: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 385: for_each defs: (def)
  // 386:   if
  // 387:     def.is_a_key_value_pair:
  // 388:       writeln "_define " key_of(def) ' ' std::value_of(def)
  // 389:     :
  // 390:       writeln "_define " def
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defs */;
  arguments->slots[1] = func__compiler__sim2c_275;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_282(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 391: for_each all_statements: (stmts) print_trees stmts
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* all_statements */;
  arguments->slots[1] = func__compiler__sim2c_283;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_284;
}
static void entry__compiler__sim2c_283(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmts: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 391: ... print_trees stmts
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmts */;
  result_count = frame->caller_result_count;
  myself = get__print_trees();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_284(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 392: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_285(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 414: ... : (used_names)
  // 415:   for_each used_names: (mangled_name info) need mangled_name info
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_286, 1);
  // 414: for_each all_used_names: (used_names)
  // 415:   for_each used_names: (mangled_name info) need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* all_used_names */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_288;
}
static void entry__compiler__sim2c_287(void) {
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
  // 415: ... need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mangled_name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* need */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_286(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // used_names: 0
  // need: 1
  frame->slots[1] = myself->closure.frame->slots[13]; /* need */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 415: ... : (mangled_name info) need mangled_name info
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_287, 2);
  // 415: for_each used_names: (mangled_name info) need mangled_name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* used_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_288(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 416: ... : write_timing_info "mangling" filenames(1)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_289, 0);
  // 416: if do_time_passes: write_timing_info "mangling" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_292;
}
static void entry__compiler__sim2c_289(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_290;
}
static void cont__compiler__sim2c_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 416: ... write_timing_info "mangling" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7690af9104a5e1e7;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_292(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 417: if do_check_only terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = get__terminate();
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_293;
}
static void cont__compiler__sim2c_293(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 418: $$generated_declarations ""
  ((CELL *)frame->slots[14])->contents /* generated_declarations */ = empty_string;
  // 419: $$generated_top_level_variable_names ""
  ((CELL *)frame->slots[15])->contents /* generated_top_level_variable_names */ = empty_string;
  // 420: $$generated_top_level_variable_declarations ""
  ((CELL *)frame->slots[16])->contents /* generated_top_level_variable_declarations */ = empty_string;
  // 421: $$generated_global_variable_declarations ""
  ((CELL *)frame->slots[17])->contents /* generated_global_variable_declarations */ = empty_string;
  // 422: $$generated_continuation_table ""
  ((CELL *)frame->slots[18])->contents /* generated_continuation_table */ = empty_string;
  // 423: $$generated_delayed_continuation_table ""
  ((CELL *)frame->slots[19])->contents /* generated_delayed_continuation_table */ = empty_string;
  // 424: $$generated_functions ""
  ((CELL *)frame->slots[20])->contents /* generated_functions */ = empty_string;
  // 425: $$generated_phase_1 ""
  ((CELL *)frame->slots[21])->contents /* generated_phase_1 */ = empty_string;
  // 432: $$generated_phase_2 ""
  ((CELL *)frame->slots[22])->contents /* generated_phase_2 */ = empty_string;
  // 439: $$generated_phase_3 ""
  ((CELL *)frame->slots[23])->contents /* generated_phase_3 */ = empty_string;
  // 450: $$generated_phase_4 ""
  ((CELL *)frame->slots[24])->contents /* generated_phase_4 */ = empty_string;
  // 468: $$generated_phase_5 ""
  ((CELL *)frame->slots[25])->contents /* generated_phase_5 */ = empty_string;
  // 483: $$generated_phase_6 ""
  ((CELL *)frame->slots[26])->contents /* generated_phase_6 */ = empty_string;
  // 486: $$generated_code ""
  ((CELL *)frame->slots[27])->contents /* generated_code */ = empty_string;
  // 487: $$generated_collections ""
  ((CELL *)frame->slots[28])->contents /* generated_collections */ = empty_string;
  // 488: $$delayed_statements ""
  ((CELL *)frame->slots[29])->contents /* delayed_statements */ = empty_string;
  // 489: $$used_literals empty_table
  ((CELL *)frame->slots[30])->contents /* used_literals */ = get__empty_table();
  // 490: %%used_string_literals empty_table
  set__used_string_literals(get__empty_table());
  // 492: ... : (args*)
  // 493:   $txt string(args*)
  // 494:   push &actions: append &generated_declarations txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_294, -1);
  // 492: %compiler::write_to_declarations: (args*)
  // 493:   $txt string(args*)
  // 494:   push &actions: append &generated_declarations txt
  initialize_future(get__compiler__write_to_declarations(), frame->slots[33] /* temp__1 */);
  // 496: ... : (args*)
  // 497:   $txt string(args*)
  // 498:   push &actions: append &generated_top_level_variable_names txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_299, -1);
  // 496: %compiler::write_to_top_level_variable_names: (args*)
  // 497:   $txt string(args*)
  // 498:   push &actions: append &generated_top_level_variable_names txt
  initialize_future(get__compiler__write_to_top_level_variable_names(), frame->slots[33] /* temp__1 */);
  // 500: ... : (args*)
  // 501:   $txt string(args*)
  // 502:   push &actions: append &generated_top_level_variable_declarations txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_304, -1);
  // 500: %compiler::write_to_top_level_variable_declarations: (args*)
  // 501:   $txt string(args*)
  // 502:   push &actions: append &generated_top_level_variable_declarations txt
  initialize_future(get__compiler__write_to_top_level_variable_declarations(), frame->slots[33] /* temp__1 */);
  // 504: ... : (args*)
  // 505:   $txt string(args*)
  // 506:   push &actions: append &generated_global_variable_declarations txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_309, -1);
  // 504: %compiler::write_to_global_variable_declarations: (args*)
  // 505:   $txt string(args*)
  // 506:   push &actions: append &generated_global_variable_declarations txt
  initialize_future(get__compiler__write_to_global_variable_declarations(), frame->slots[33] /* temp__1 */);
  // 508: ... : (args*)
  // 509:   $txt string(args*)
  // 510:   push &actions: append &generated_continuation_table txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_314, -1);
  // 508: %compiler::write_to_continuation_table: (args*)
  // 509:   $txt string(args*)
  // 510:   push &actions: append &generated_continuation_table txt
  initialize_future(get__compiler__write_to_continuation_table(), frame->slots[33] /* temp__1 */);
  // 512: ... : (args*)
  // 513:   $txt string(args*)
  // 514:   push &actions: append &generated_delayed_continuation_table txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_319, -1);
  // 512: %compiler::write_to_delayed_continuation_table: (args*)
  // 513:   $txt string(args*)
  // 514:   push &actions: append &generated_delayed_continuation_table txt
  initialize_future(get__compiler__write_to_delayed_continuation_table(), frame->slots[33] /* temp__1 */);
  // 516: ... : (args*)
  // 517:   $txt string(args*)
  // 518:   push &actions: append &generated_functions txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_324, -1);
  // 516: %compiler::write_to_functions: (args*)
  // 517:   $txt string(args*)
  // 518:   push &actions: append &generated_functions txt
  initialize_future(get__compiler__write_to_functions(), frame->slots[33] /* temp__1 */);
  // 520: ... : (args*)
  // 521:   $txt string(args*)
  // 522:   push &actions: append &generated_phase_1 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_329, -1);
  // 520: %compiler::write_to_phase_1: (args*)
  // 521:   $txt string(args*)
  // 522:   push &actions: append &generated_phase_1 txt
  initialize_future(get__compiler__write_to_phase_1(), frame->slots[33] /* temp__1 */);
  // 524: ... : (args*)
  // 525:   $txt string(args*)
  // 526:   push &actions: append &generated_phase_2 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_334, -1);
  // 524: %compiler::write_to_phase_2: (args*)
  // 525:   $txt string(args*)
  // 526:   push &actions: append &generated_phase_2 txt
  initialize_future(get__compiler__write_to_phase_2(), frame->slots[33] /* temp__1 */);
  // 528: ... : (args*)
  // 529:   $txt string(args*)
  // 530:   push &actions: append &generated_phase_3 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_339, -1);
  // 528: %compiler::write_to_phase_3: (args*)
  // 529:   $txt string(args*)
  // 530:   push &actions: append &generated_phase_3 txt
  initialize_future(get__compiler__write_to_phase_3(), frame->slots[33] /* temp__1 */);
  // 532: ... : (args*)
  // 533:   $txt string(args*)
  // 534:   push &actions: append &generated_phase_4 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_344, -1);
  // 532: %compiler::write_to_phase_4: (args*)
  // 533:   $txt string(args*)
  // 534:   push &actions: append &generated_phase_4 txt
  initialize_future(get__compiler__write_to_phase_4(), frame->slots[33] /* temp__1 */);
  // 536: ... : (args*)
  // 537:   $txt string(args*)
  // 538:   push &actions: append &generated_phase_5 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_349, -1);
  // 536: %compiler::write_to_phase_5: (args*)
  // 537:   $txt string(args*)
  // 538:   push &actions: append &generated_phase_5 txt
  initialize_future(get__compiler__write_to_phase_5(), frame->slots[33] /* temp__1 */);
  // 540: ... : (args*)
  // 541:   $txt string(args*)
  // 542:   push &actions: append &generated_phase_6 txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_354, -1);
  // 540: %compiler::write_to_phase_6: (args*)
  // 541:   $txt string(args*)
  // 542:   push &actions: append &generated_phase_6 txt
  initialize_future(get__compiler__write_to_phase_6(), frame->slots[33] /* temp__1 */);
  // 544: ... : (name literal)
  // 545:   push &actions: !used_literals(name) literal
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_359, 2);
  // 544: %compiler::use_literal: (name literal)
  // 545:   push &actions: !used_literals(name) literal
  initialize_future(get__compiler__use_literal(), frame->slots[33] /* temp__1 */);
  // 547: ... : (args*)
  // 548:   $txt string(args*)
  // 549:   push &actions: append &generated_collections txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_363, -1);
  // 547: %compiler::write_to_generated_collections: (args*)
  // 548:   $txt string(args*)
  // 549:   push &actions: append &generated_collections txt
  initialize_future(get__compiler__write_to_generated_collections(), frame->slots[33] /* temp__1 */);
  // 551: ... : (args*)
  // 552:   $txt string(args*)
  // 553:   push &actions: append &delayed_statements txt
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_368, -1);
  // 551: %compiler::write_to_delayed_statements: (args*)
  // 552:   $txt string(args*)
  // 553:   push &actions: append &delayed_statements txt
  initialize_future(get__compiler__write_to_delayed_statements(), frame->slots[33] /* temp__1 */);
  // 555: ... : (ident)
  // 556:   if ident .has_prefix. "get__":
  // 557:     $name range(ident 6 -1)
  // 558:     need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_373, 1);
  // 555: %compiler::use_identifier: (ident)
  // 556:   if ident .has_prefix. "get__":
  // 557:     $name range(ident 6 -1)
  // 558:     need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  initialize_future(get__compiler__use_identifier(), frame->slots[33] /* temp__1 */);
  // 560: show_compiler_debug_info "GENERATE DEFINITIONS"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c44673b4643f1172;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_380;
}
static void entry__compiler__sim2c_376(void) {
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
  // 557: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_377;
}
static void cont__compiler__sim2c_377(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 557: $name range(ident 6 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = number__6;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_378;
}
static void cont__compiler__sim2c_378(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 558: ... types::grammar_node(.variable_kind_of STATIC_SINGLE)
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_SINGLE());
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 558: need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* need */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_294(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[14]; /* generated_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 493: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_295;
}
static void cont__compiler__sim2c_295(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 494: ... : append &generated_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_296, 0);
  // 494: push &actions: append &generated_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_298;
}
static void entry__compiler__sim2c_296(void) {
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
  // 494: ... append &generated_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_297;
}
static void cont__compiler__sim2c_297(void) {
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
static void cont__compiler__sim2c_298(void) {
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
static void entry__compiler__sim2c_299(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_top_level_variable_names: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[15]; /* generated_top_level_variable_names */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 497: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_300;
}
static void cont__compiler__sim2c_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 498: ... : append &generated_top_level_variable_names txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_301, 0);
  // 498: push &actions: append &generated_top_level_variable_names txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_303;
}
static void entry__compiler__sim2c_301(void) {
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
  // 498: ... append &generated_top_level_variable_names txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_302;
}
static void cont__compiler__sim2c_302(void) {
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
static void cont__compiler__sim2c_303(void) {
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
static void entry__compiler__sim2c_304(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_top_level_variable_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[16]; /* generated_top_level_variable_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 501: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_305;
}
static void cont__compiler__sim2c_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 502: ... : append &generated_top_level_variable_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_306, 0);
  // 502: push &actions: append &generated_top_level_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_308;
}
static void entry__compiler__sim2c_306(void) {
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
  // 502: ... append &generated_top_level_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_307;
}
static void cont__compiler__sim2c_307(void) {
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
static void cont__compiler__sim2c_308(void) {
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
static void entry__compiler__sim2c_309(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_global_variable_declarations: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[17]; /* generated_global_variable_declarations */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 505: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_310;
}
static void cont__compiler__sim2c_310(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 506: ... : append &generated_global_variable_declarations txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_311, 0);
  // 506: push &actions: append &generated_global_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_313;
}
static void entry__compiler__sim2c_311(void) {
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
  // 506: ... append &generated_global_variable_declarations txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_global_variable_declarations */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_312;
}
static void cont__compiler__sim2c_312(void) {
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
static void cont__compiler__sim2c_313(void) {
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
static void entry__compiler__sim2c_314(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_continuation_table: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[18]; /* generated_continuation_table */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 509: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_315;
}
static void cont__compiler__sim2c_315(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 510: ... : append &generated_continuation_table txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_316, 0);
  // 510: push &actions: append &generated_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_318;
}
static void entry__compiler__sim2c_316(void) {
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
  // 510: ... append &generated_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_continuation_table */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_317;
}
static void cont__compiler__sim2c_317(void) {
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
static void cont__compiler__sim2c_318(void) {
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
static void entry__compiler__sim2c_319(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_delayed_continuation_table: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[19]; /* generated_delayed_continuation_table */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 513: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_320;
}
static void cont__compiler__sim2c_320(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 514: ... : append &generated_delayed_continuation_table txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_321, 0);
  // 514: push &actions: append &generated_delayed_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_323;
}
static void entry__compiler__sim2c_321(void) {
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
  // 514: ... append &generated_delayed_continuation_table txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_delayed_continuation_table */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_322;
}
static void cont__compiler__sim2c_322(void) {
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
static void cont__compiler__sim2c_323(void) {
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
static void entry__compiler__sim2c_324(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_functions: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[20]; /* generated_functions */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 517: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_325;
}
static void cont__compiler__sim2c_325(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 518: ... : append &generated_functions txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_326, 0);
  // 518: push &actions: append &generated_functions txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_328;
}
static void entry__compiler__sim2c_326(void) {
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
  // 518: ... append &generated_functions txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_functions */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_327;
}
static void cont__compiler__sim2c_327(void) {
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
static void cont__compiler__sim2c_328(void) {
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
static void entry__compiler__sim2c_329(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_1: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[21]; /* generated_phase_1 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 521: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_330;
}
static void cont__compiler__sim2c_330(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 522: ... : append &generated_phase_1 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_331, 0);
  // 522: push &actions: append &generated_phase_1 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_333;
}
static void entry__compiler__sim2c_331(void) {
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
  // 522: ... append &generated_phase_1 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_1 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_332;
}
static void cont__compiler__sim2c_332(void) {
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
static void cont__compiler__sim2c_333(void) {
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
static void entry__compiler__sim2c_334(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_2: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[22]; /* generated_phase_2 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 525: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_335;
}
static void cont__compiler__sim2c_335(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 526: ... : append &generated_phase_2 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_336, 0);
  // 526: push &actions: append &generated_phase_2 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_338;
}
static void entry__compiler__sim2c_336(void) {
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
  // 526: ... append &generated_phase_2 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_2 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_337;
}
static void cont__compiler__sim2c_337(void) {
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
static void cont__compiler__sim2c_338(void) {
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
static void entry__compiler__sim2c_339(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_3: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[23]; /* generated_phase_3 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 529: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_340;
}
static void cont__compiler__sim2c_340(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 530: ... : append &generated_phase_3 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_341, 0);
  // 530: push &actions: append &generated_phase_3 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_343;
}
static void entry__compiler__sim2c_341(void) {
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
  // 530: ... append &generated_phase_3 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_3 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_342;
}
static void cont__compiler__sim2c_342(void) {
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
static void cont__compiler__sim2c_343(void) {
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
static void entry__compiler__sim2c_344(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_4: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[24]; /* generated_phase_4 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 533: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_345;
}
static void cont__compiler__sim2c_345(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 534: ... : append &generated_phase_4 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_346, 0);
  // 534: push &actions: append &generated_phase_4 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_348;
}
static void entry__compiler__sim2c_346(void) {
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
  // 534: ... append &generated_phase_4 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_4 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_347;
}
static void cont__compiler__sim2c_347(void) {
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
static void cont__compiler__sim2c_348(void) {
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
static void entry__compiler__sim2c_349(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_5: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[25]; /* generated_phase_5 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 537: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_350;
}
static void cont__compiler__sim2c_350(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 538: ... : append &generated_phase_5 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_351, 0);
  // 538: push &actions: append &generated_phase_5 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_353;
}
static void entry__compiler__sim2c_351(void) {
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
  // 538: ... append &generated_phase_5 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_5 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_352;
}
static void cont__compiler__sim2c_352(void) {
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
static void cont__compiler__sim2c_353(void) {
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
static void entry__compiler__sim2c_354(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_phase_6: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[26]; /* generated_phase_6 */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 541: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_355;
}
static void cont__compiler__sim2c_355(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 542: ... : append &generated_phase_6 txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_356, 0);
  // 542: push &actions: append &generated_phase_6 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_358;
}
static void entry__compiler__sim2c_356(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // generated_phase_6: 0
  // txt: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* generated_phase_6 */
  frame->slots[1] = myself->closure.frame->slots[2]; /* txt */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 542: ... append &generated_phase_6 txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_phase_6 */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_357;
}
static void cont__compiler__sim2c_357(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* generated_phase_6 */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_358(void) {
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
static void entry__compiler__sim2c_359(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // name: 0
  // literal: 1
  // used_literals: 2
  frame->slots[2] = myself->closure.frame->slots[30]; /* used_literals */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 545: ... : !used_literals(name) literal
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_360, 0);
  // 545: push &actions: !used_literals(name) literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_362;
}
static void entry__compiler__sim2c_360(void) {
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
  // 545: ... !used_literals(name) literal
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* literal */;
  // 545: ... !used_literals(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* used_literals */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_361;
}
static void cont__compiler__sim2c_361(void) {
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
static void cont__compiler__sim2c_362(void) {
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
static void entry__compiler__sim2c_363(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // generated_collections: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[28]; /* generated_collections */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 548: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_364;
}
static void cont__compiler__sim2c_364(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 549: ... : append &generated_collections txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_365, 0);
  // 549: push &actions: append &generated_collections txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_367;
}
static void entry__compiler__sim2c_365(void) {
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
  // 549: ... append &generated_collections txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_collections */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_366;
}
static void cont__compiler__sim2c_366(void) {
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
static void cont__compiler__sim2c_367(void) {
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
static void entry__compiler__sim2c_368(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // args: 0
  // delayed_statements: 1
  // txt: 2
  frame->slots[1] = myself->closure.frame->slots[29]; /* delayed_statements */
  frame->slots[2] /* txt */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 552: $txt string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_369;
}
static void cont__compiler__sim2c_369(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* txt */, arguments->slots[0]);
  // 553: ... : append &delayed_statements txt
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_370, 0);
  // 553: push &actions: append &delayed_statements txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_372;
}
static void entry__compiler__sim2c_370(void) {
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
  // 553: ... append &delayed_statements txt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* delayed_statements */;
  arguments->slots[1] = frame->slots[1] /* txt */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_371;
}
static void cont__compiler__sim2c_371(void) {
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
static void cont__compiler__sim2c_372(void) {
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
static void entry__compiler__sim2c_373(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // ident: 0
  // need: 1
  frame->slots[1] = myself->closure.frame->slots[13]; /* need */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 556: ... ident .has_prefix. "get__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = string__405aee03eb306008;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_375;
}
static void cont__compiler__sim2c_375(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 556: ... :
  // 557:   $name range(ident 6 -1)
  // 558:   need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_376, 0);
  // 556: if ident .has_prefix. "get__":
  // 557:   $name range(ident 6 -1)
  // 558:   need name types::grammar_node(.variable_kind_of STATIC_SINGLE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_380(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 561: ... : (stmt_idx defs)
  // 562:   %%compiler::actions empty_list
  // 563:   %%compiler::delayed_code ""
  // 564:   %%compiler::index 0
  // 565:   collect_output $code:
  // 566:     for_each defs: ($definition)
  // 567:       $$source undefined
  // 568:       if definition.is_a_key_value_pair:
  // 569:         !source std::value_of(definition)
  // 570:         !definition key_of(definition)
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_381, 2);
  // 561: for_each all_definitions: (stmt_idx defs)
  // 562:   %%compiler::actions empty_list
  // 563:   %%compiler::delayed_code ""
  // 564:   %%compiler::index 0
  // 565:   collect_output $code:
  // 566:     for_each defs: ($definition)
  // 567:       $$source undefined
  // 568:       if definition.is_a_key_value_pair:
  // 569:         !source std::value_of(definition)
  // 570:         !definition key_of(definition)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_427;
}
static void entry__compiler__sim2c_381(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // stmt_idx: 0
  // defs: 1
  // return__6: 2
  // generated_code: 3
  // all_actions: 4
  // code: 5
  frame->slots[2] /* return__6 */ = create_continuation();
  frame->slots[3] = myself->closure.frame->slots[27]; /* generated_code */
  frame->slots[4] = myself->closure.frame->slots[8]; /* all_actions */
  define__compiler__actions(undefined);
  define__compiler__delayed_code(undefined);
  define__compiler__index(undefined);
  frame->slots[5] /* code */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 562: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 563: %%compiler::delayed_code ""
  set__compiler__delayed_code(empty_string);
  // 564: %%compiler::index 0
  set__compiler__index(number__0);
  // 565: ... :
  // 566:   for_each defs: ($definition)
  // 567:     $$source undefined
  // 568:     if definition.is_a_key_value_pair:
  // 569:       !source std::value_of(definition)
  // 570:       !definition key_of(definition)
  // 571:     if
  // 572:       definition.is_c_code:
  // 573:         define_c_code definition
  // 574:       :
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__sim2c_382, 0);
  // 565: collect_output $code:
  // 566:   for_each defs: ($definition)
  // 567:     $$source undefined
  // 568:     if definition.is_a_key_value_pair:
  // 569:       !source std::value_of(definition)
  // 570:       !definition key_of(definition)
  // 571:     if
  // 572:       definition.is_c_code:
  // 573:         define_c_code definition
  // 574:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_418;
}
static void entry__compiler__sim2c_390(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // definition: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 573: define_c_code definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = frame->caller_result_count;
  myself = get__define_c_code();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_391(void) {
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // return__5: 0
  // definition: 1
  // source: 2
  // name: 3
  // attribute: 4
  frame->slots[0] /* return__5 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[2] = myself->closure.frame->slots[1]; /* source */
  frame->slots[3] /* name */ = create_cell();
  frame->slots[4] /* attribute */ = create_future();
  define__compiler__suffix(create_future());
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 575: ... identifier_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_392;
}
static void cont__compiler__sim2c_392(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 575: $$name mangled_name_of(identifier_of(definition))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_393;
}
static void cont__compiler__sim2c_393(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* name */ = arguments->slots[0];
  // 576: $attribute attribute_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_394;
}
static void cont__compiler__sim2c_394(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* attribute */, arguments->slots[0]);
  // 577: ... attribute.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* attribute */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_395;
}
static void cont__compiler__sim2c_395(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 577: ... :
  // 578:   append &name "__"
  // 579:   append &name mangled_name_of(attribute)
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__sim2c_396, 0);
  // 577: if attribute.is_defined:
  // 578:   append &name "__"
  // 579:   append &name mangled_name_of(attribute)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_400;
}
static void entry__compiler__sim2c_396(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // attribute: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* name */
  frame->slots[1] = myself->closure.frame->slots[4]; /* attribute */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 578: append &name "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_397;
}
static void cont__compiler__sim2c_397(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* name */ = arguments->slots[0];
  // 579: ... mangled_name_of(attribute)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* attribute */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_398;
}
static void cont__compiler__sim2c_398(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 579: append &name mangled_name_of(attribute)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_399;
}
static void cont__compiler__sim2c_399(void) {
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
static void cont__compiler__sim2c_400(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 580: %compiler::suffix string("__" name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5f02b9a;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_401;
}
static void cont__compiler__sim2c_401(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__suffix(), arguments->slots[0]);
  // 582: source.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* source */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_402;
}
static void cont__compiler__sim2c_402(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 582: ... source.is_a_polymorphic_function_constant
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__sim2c_403, 0);
  // 582: source.is_defined && source.is_a_polymorphic_function_constant
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_405;
}
static void entry__compiler__sim2c_403(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 582: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_404;
}
static void cont__compiler__sim2c_404(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 582: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_405(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 582: ... :
  // 583:   define_polymorphic_function definition source.is_a_setter
  frame->slots[8] /* temp__4 */ = create_closure(entry__compiler__sim2c_406, 0);
  // 584: :
  // 585:   case
  // 586:     attribute_kind_of(definition)
  // 587:     ATTRIBUTE_KIND:
  // 588:       define_attribute definition source
  // 589:     METHOD_KIND:
  // 590:       if
  // 591:         attribute_of(definition).is_defined:
  // 592:           define_method definition source
  // 593:         :
  // ...
  frame->slots[9] /* temp__5 */ = create_closure(entry__compiler__sim2c_408, 0);
  // 581: if
  // 582:   source.is_defined && source.is_a_polymorphic_function_constant:
  // 583:     define_polymorphic_function definition source.is_a_setter
  // 584:   :
  // 585:     case
  // 586:       attribute_kind_of(definition)
  // 587:       ATTRIBUTE_KIND:
  // 588:         define_attribute definition source
  // 589:       METHOD_KIND:
  // 590:         if
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_417;
}
static void entry__compiler__sim2c_414(void) {
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
  // 592: define_method definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_method();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_415(void) {
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
  // 594: define_type_function definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_type_function();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_410(void) {
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
  // 588: define_attribute definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_attribute();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_411(void) {
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
  // 591: attribute_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_412;
}
static void cont__compiler__sim2c_412(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 591: attribute_of(definition).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_413;
}
static void cont__compiler__sim2c_413(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 591: ... :
  // 592:   define_method definition source
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_414, 0);
  // 593: :
  // 594:   define_type_function definition source
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__sim2c_415, 0);
  // 590: if
  // 591:   attribute_of(definition).is_defined:
  // 592:     define_method definition source
  // 593:   :
  // 594:     define_type_function definition source
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
static void entry__compiler__sim2c_416(void) {
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
  // 596: define_variable definition source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = frame->caller_result_count;
  myself = get__define_variable();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_406(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 583: ... source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_407;
}
static void cont__compiler__sim2c_407(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 583: define_polymorphic_function definition source.is_a_setter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__define_polymorphic_function();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_408(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // definition: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 586: attribute_kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_409;
}
static void cont__compiler__sim2c_409(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 587: ... :
  // 588:   define_attribute definition source
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_410, 0);
  // 589: ... :
  // 590:   if
  // 591:     attribute_of(definition).is_defined:
  // 592:       define_method definition source
  // 593:     :
  // 594:       define_type_function definition source
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_411, 0);
  // 595: :
  // 596:   define_variable definition source
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__sim2c_416, 0);
  // 585: case
  // 586:   attribute_kind_of(definition)
  // 587:   ATTRIBUTE_KIND:
  // 588:     define_attribute definition source
  // 589:   METHOD_KIND:
  // 590:     if
  // 591:       attribute_of(definition).is_defined:
  // 592:         define_method definition source
  // 593:       :
  // 594:         define_type_function definition source
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
static void cont__compiler__sim2c_417(void) {
  myself = frame->slots[0] /* return__5 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_383(void) {
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
  // 567: $$source undefined
  ((CELL *)frame->slots[1])->contents /* source */ = get__undefined();
  // 568: ... definition.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_384;
}
static void cont__compiler__sim2c_384(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 568: ... :
  // 569:   !source std::value_of(definition)
  // 570:   !definition key_of(definition)
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_385, 0);
  // 568: if definition.is_a_key_value_pair:
  // 569:   !source std::value_of(definition)
  // 570:   !definition key_of(definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_388;
}
static void entry__compiler__sim2c_385(void) {
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
  // 569: !source std::value_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_386;
}
static void cont__compiler__sim2c_386(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* source */ = arguments->slots[0];
  // 570: !definition key_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* definition */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_387;
}
static void cont__compiler__sim2c_387(void) {
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
static void cont__compiler__sim2c_388(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 572: definition.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_389;
}
static void cont__compiler__sim2c_389(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 572: ... :
  // 573:   define_c_code definition
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_390, 0);
  // 574: :
  // 575:   $$name mangled_name_of(identifier_of(definition))
  // 576:   $attribute attribute_of(definition)
  // 577:   if attribute.is_defined:
  // 578:     append &name "__"
  // 579:     append &name mangled_name_of(attribute)
  // 580:   %compiler::suffix string("__" name)
  // 581:   if
  // 582:     source.is_defined && source.is_a_polymorphic_function_constant:
  // 583:       define_polymorphic_function definition source.is_a_setter
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_391, 0);
  // 571: if
  // 572:   definition.is_c_code:
  // 573:     define_c_code definition
  // 574:   :
  // 575:     $$name mangled_name_of(identifier_of(definition))
  // 576:     $attribute attribute_of(definition)
  // 577:     if attribute.is_defined:
  // 578:       append &name "__"
  // 579:       append &name mangled_name_of(attribute)
  // 580:     %compiler::suffix string("__" name)
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
static void entry__compiler__sim2c_382(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // defs: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* defs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 566: for_each defs: ($definition)
  // 567:   $$source undefined
  // 568:   if definition.is_a_key_value_pair:
  // 569:     !source std::value_of(definition)
  // 570:     !definition key_of(definition)
  // 571:   if
  // 572:     definition.is_c_code:
  // 573:       define_c_code definition
  // 574:     :
  // 575:       $$name mangled_name_of(identifier_of(definition))
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defs */;
  arguments->slots[1] = func__compiler__sim2c_383;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_418(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* code */, arguments->slots[0]);
  // 597: ... delayed_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_419;
}
static void cont__compiler__sim2c_419(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 597: ... delayed_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_420;
}
static void cont__compiler__sim2c_420(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 597: if delayed_code != "": write_to_delayed_statements delayed_code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_421;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_422;
}
static void entry__compiler__sim2c_421(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 597: ... write_to_delayed_statements delayed_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  result_count = frame->caller_result_count;
  myself = get__write_to_delayed_statements();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_422(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 598: ... : append &generated_code code
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__sim2c_423, 0);
  // 598: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_425;
}
static void entry__compiler__sim2c_423(void) {
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
  // 598: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_424;
}
static void cont__compiler__sim2c_424(void) {
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
static void cont__compiler__sim2c_425(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 599: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_426;
}
static void cont__compiler__sim2c_426(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[2] /* return__6 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_427(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 600: show_compiler_debug_info "GENERATE STATEMENTS"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c050814d5faecc7a;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_429;
}
static void cont__compiler__sim2c_429(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 601: %%compiler::current_continuation_info undefined
  set__compiler__current_continuation_info(get__undefined());
  // 602: ... :
  // 603:   %%compiler::actions empty_list
  // 604:   %%compiler::delayed_code ""
  // 605:   collect_output $code:
  // 606:     if
  // 607:       is_main:
  // 608:         begin_continuation "main_entry"
  // 609:         if max_temp_idx > 0:
  // 610:           writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 611:       :
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_430, 0);
  // 602: do:
  // 603:   %%compiler::actions empty_list
  // 604:   %%compiler::delayed_code ""
  // 605:   collect_output $code:
  // 606:     if
  // 607:       is_main:
  // 608:         begin_continuation "main_entry"
  // 609:         if max_temp_idx > 0:
  // 610:           writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 611:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_466;
}
static void entry__compiler__sim2c_430(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // return__7: 0
  // is_main: 1
  // max_temp_idx: 2
  // mangle_filename: 3
  // generated_code: 4
  // all_actions: 5
  // code: 6
  frame->slots[0] /* return__7 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[2] = myself->closure.frame->slots[12]; /* max_temp_idx */
  frame->slots[3] = myself->closure.frame->slots[3]; /* mangle_filename */
  frame->slots[4] = myself->closure.frame->slots[27]; /* generated_code */
  frame->slots[5] = myself->closure.frame->slots[8]; /* all_actions */
  define__compiler__actions(undefined);
  define__compiler__delayed_code(undefined);
  frame->slots[6] /* code */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 603: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 604: %%compiler::delayed_code ""
  set__compiler__delayed_code(empty_string);
  // 605: ... :
  // 606:   if
  // 607:     is_main:
  // 608:       begin_continuation "main_entry"
  // 609:       if max_temp_idx > 0:
  // 610:         writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 611:     :
  // 612:       write_to_continuation_table "  {run__@(module_name), NULL, "
  // 613:       write "
  // 614:         static int already_run = false;
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__sim2c_431, 0);
  // 605: collect_output $code:
  // 606:   if
  // 607:     is_main:
  // 608:       begin_continuation "main_entry"
  // 609:       if max_temp_idx > 0:
  // 610:         writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 611:     :
  // 612:       write_to_continuation_table "  {run__@(module_name), NULL, "
  // 613:       write "
  // 614:         static int already_run = false;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_461;
}
static void entry__compiler__sim2c_449(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // mangle_filename: 2
  // continuation: 3
  frame->slots[2] = myself->closure.frame->slots[2]; /* mangle_filename */
  frame->slots[3] /* continuation */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 625: write_source_as_remark info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 0;
  myself = get__write_source_as_remark();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_450;
}
static void cont__compiler__sim2c_450(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 627: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_451;
}
static void cont__compiler__sim2c_451(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 628: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_452;
}
static void cont__compiler__sim2c_452(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 626: ... "
  // 627:     func = run__@(mangle_filename(name));
  // 628:     frame->cont = cont__run__@(mangle_filename(name));
  // 629:   }
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__ca75d5c2b6ab3b0c;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = string__3fab381eeea84c47;
  arguments->slots[3] = frame->slots[6] /* temp__3 */;
  arguments->slots[4] = string__b40af3cb5d887d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_456;
}
static void cont__compiler__sim2c_456(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 626: write "
  // 627:     func = run__@(mangle_filename(name));
  // 628:     frame->cont = cont__run__@(mangle_filename(name));
  // 629:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_457;
}
static void cont__compiler__sim2c_457(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 630: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_458;
}
static void cont__compiler__sim2c_458(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 630: $continuation "cont__run__@(mangle_filename(name))"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6a214ac420f089ff;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_460;
}
static void cont__compiler__sim2c_460(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* continuation */, arguments->slots[0]);
  // 631: next_continuation continuation
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* continuation */;
  result_count = frame->caller_result_count;
  myself = get__next_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_431(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // is_main: 0
  // max_temp_idx: 1
  // mangle_filename: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[1] = myself->closure.frame->slots[2]; /* max_temp_idx */
  frame->slots[2] = myself->closure.frame->slots[3]; /* mangle_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 607: ... :
  // 608:   begin_continuation "main_entry"
  // 609:   if max_temp_idx > 0:
  // 610:     writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_432, 0);
  // 611: :
  // 612:   write_to_continuation_table "  {run__@(module_name), NULL, "
  // 613:   write "
  // 614:     static int already_run = false;
  // 615:     
  // 616:     EXPORT void run__@(module_name)(void) {
  // 617:       if (already_run) {
  // 618:         func = frame->cont;
  // 619:         frame->cont = invalid_continuation;
  // 620:         return;
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__sim2c_440, 0);
  // 606: if
  // 607:   is_main:
  // 608:     begin_continuation "main_entry"
  // 609:     if max_temp_idx > 0:
  // 610:       writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  // 611:   :
  // 612:     write_to_continuation_table "  {run__@(module_name), NULL, "
  // 613:     write "
  // 614:       static int already_run = false;
  // 615:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_448;
}
static void entry__compiler__sim2c_436(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 610: ... "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__41028e5a9545c479;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_439;
}
static void cont__compiler__sim2c_439(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 610: writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_432(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 608: begin_continuation "main_entry"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__295c7d0427bb24d8;
  result_count = 0;
  myself = get__begin_continuation();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_434;
}
static void cont__compiler__sim2c_434(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 609: ... max_temp_idx > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_435;
}
static void cont__compiler__sim2c_435(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 609: ... :
  // 610:   writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_436, 0);
  // 609: if max_temp_idx > 0:
  // 610:   writeln "  allocate_initialized_frame_gc(0, @(max_temp_idx));"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_440(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // max_temp_idx: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 612: ... "  {run__@(module_name), NULL, "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__4594ae5b852cb87f;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__3794a6c106b6c980;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_443;
}
static void cont__compiler__sim2c_443(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 612: write_to_continuation_table "  {run__@(module_name), NULL, "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__write_to_continuation_table();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_444;
}
static void cont__compiler__sim2c_444(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 613: ... "
  // 614:   static int already_run = false;
  // 615:   
  // 616:   EXPORT void run__@(module_name)(void) {
  // 617:     if (already_run) {
  // 618:       func = frame->cont;
  // 619:       frame->cont = invalid_continuation;
  // 620:       return;
  // 621:     }
  // 622:     already_run = true;
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__8eebb379fdb22853;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__bbab7a959fd798d;
  arguments->slots[3] = ((CELL *)frame->slots[0])->contents /* max_temp_idx */;
  arguments->slots[4] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_447;
}
static void cont__compiler__sim2c_447(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 613: write "
  // 614:   static int already_run = false;
  // 615:   
  // 616:   EXPORT void run__@(module_name)(void) {
  // 617:     if (already_run) {
  // 618:       func = frame->cont;
  // 619:       frame->cont = invalid_continuation;
  // 620:       return;
  // 621:     }
  // 622:     already_run = true;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_448(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 624: ... : (name info)
  // 625:   write_source_as_remark info
  // 626:   write "
  // 627:       func = run__@(mangle_filename(name));
  // 628:       frame->cont = cont__run__@(mangle_filename(name));
  // 629:     }
  // 630:   $continuation "cont__run__@(mangle_filename(name))"
  // 631:   next_continuation continuation
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__sim2c_449, 2);
  // 624: for_each required_modules: (name info)
  // 625:   write_source_as_remark info
  // 626:   write "
  // 627:       func = run__@(mangle_filename(name));
  // 628:       frame->cont = cont__run__@(mangle_filename(name));
  // 629:     }
  // 630:   $continuation "cont__run__@(mangle_filename(name))"
  // 631:   next_continuation continuation
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_461(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* code */, arguments->slots[0]);
  // 632: ... : append &generated_code code
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__sim2c_462, 0);
  // 632: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_464;
}
static void entry__compiler__sim2c_462(void) {
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
  // 632: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_463;
}
static void cont__compiler__sim2c_463(void) {
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
static void cont__compiler__sim2c_464(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 633: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_465;
}
static void cont__compiler__sim2c_465(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__7 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_466(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 634: $def_count length_of(all_definitions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* all_definitions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_467;
}
static void cont__compiler__sim2c_467(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[31] /* def_count */, arguments->slots[0]);
  // 635: ... : (stmt_idx stmts)
  // 636:   %%compiler::actions empty_list
  // 637:   %%compiler::delayed_code ""
  // 638:   %compiler::suffix string("__" stmt_idx+def_count)
  // 639:   %%compiler::index 0
  // 640:   collect_output $code: for_each stmts: (stmt) generate_statement stmt
  // 641:   if delayed_code != "": write_to_delayed_statements delayed_code
  // 642:   push &actions: append &generated_code code
  // 643:   push &all_actions actions
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_468, 2);
  // 635: for_each all_statements: (stmt_idx stmts)
  // 636:   %%compiler::actions empty_list
  // 637:   %%compiler::delayed_code ""
  // 638:   %compiler::suffix string("__" stmt_idx+def_count)
  // 639:   %%compiler::index 0
  // 640:   collect_output $code: for_each stmts: (stmt) generate_statement stmt
  // 641:   if delayed_code != "": write_to_delayed_statements delayed_code
  // 642:   push &actions: append &generated_code code
  // 643:   push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* all_statements */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_482;
}
static void entry__compiler__sim2c_468(void) {
  allocate_initialized_frame_gc(6, 9);
  // slot allocations:
  // stmt_idx: 0
  // stmts: 1
  // return__8: 2
  // def_count: 3
  // generated_code: 4
  // all_actions: 5
  // code: 6
  frame->slots[2] /* return__8 */ = create_continuation();
  frame->slots[3] = myself->closure.frame->slots[31]; /* def_count */
  frame->slots[4] = myself->closure.frame->slots[27]; /* generated_code */
  frame->slots[5] = myself->closure.frame->slots[8]; /* all_actions */
  define__compiler__actions(undefined);
  define__compiler__delayed_code(undefined);
  define__compiler__suffix(create_future());
  define__compiler__index(undefined);
  frame->slots[6] /* code */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 636: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 637: %%compiler::delayed_code ""
  set__compiler__delayed_code(empty_string);
  // 638: ... stmt_idx+def_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_idx */;
  arguments->slots[1] = frame->slots[3] /* def_count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_469;
}
static void cont__compiler__sim2c_469(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 638: %compiler::suffix string("__" stmt_idx+def_count)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e5f02b9a;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_470;
}
static void cont__compiler__sim2c_470(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__suffix(), arguments->slots[0]);
  // 639: %%compiler::index 0
  set__compiler__index(number__0);
  // 640: ... : for_each stmts: (stmt) generate_statement stmt
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__sim2c_471, 0);
  // 640: collect_output $code: for_each stmts: (stmt) generate_statement stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_473;
}
static void entry__compiler__sim2c_472(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 640: ... generate_statement stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt */;
  result_count = frame->caller_result_count;
  myself = get__generate_statement();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_471(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmts: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* stmts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 640: ... for_each stmts: (stmt) generate_statement stmt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmts */;
  arguments->slots[1] = func__compiler__sim2c_472;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_473(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* code */, arguments->slots[0]);
  // 641: ... delayed_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_474;
}
static void cont__compiler__sim2c_474(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 641: ... delayed_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_475;
}
static void cont__compiler__sim2c_475(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 641: if delayed_code != "": write_to_delayed_statements delayed_code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_476;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_477;
}
static void entry__compiler__sim2c_476(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 641: ... write_to_delayed_statements delayed_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__delayed_code();
  result_count = frame->caller_result_count;
  myself = get__write_to_delayed_statements();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_477(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 642: ... : append &generated_code code
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__sim2c_478, 0);
  // 642: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_480;
}
static void entry__compiler__sim2c_478(void) {
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
  // 642: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_479;
}
static void cont__compiler__sim2c_479(void) {
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
static void cont__compiler__sim2c_480(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 643: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_481;
}
static void cont__compiler__sim2c_481(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[2] /* return__8 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_482(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 644: ... :
  // 645:   %%compiler::actions empty_list
  // 646:   collect_output $code:
  // 647:     if
  // 648:       is_main:
  // 649:         write "
  // 650:             terminate(0); // should never be reached
  // 651:           }
  // 652:       :
  // 653:         write "
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_483, 0);
  // 644: do:
  // 645:   %%compiler::actions empty_list
  // 646:   collect_output $code:
  // 647:     if
  // 648:       is_main:
  // 649:         write "
  // 650:             terminate(0); // should never be reached
  // 651:           }
  // 652:       :
  // 653:         write "
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_495;
}
static void entry__compiler__sim2c_483(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // return__9: 0
  // is_main: 1
  // generated_code: 2
  // all_actions: 3
  // code: 4
  frame->slots[0] /* return__9 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* is_main */
  frame->slots[2] = myself->closure.frame->slots[27]; /* generated_code */
  frame->slots[3] = myself->closure.frame->slots[8]; /* all_actions */
  define__compiler__actions(undefined);
  frame->slots[4] /* code */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 645: %%compiler::actions empty_list
  set__compiler__actions(get__empty_list());
  // 646: ... :
  // 647:   if
  // 648:     is_main:
  // 649:       write "
  // 650:           terminate(0); // should never be reached
  // 651:         }
  // 652:     :
  // 653:       write "
  // 654:           frame = frame->caller_frame;
  // 655:           func = frame->cont;
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__sim2c_484, 0);
  // 646: collect_output $code:
  // 647:   if
  // 648:     is_main:
  // 649:       write "
  // 650:           terminate(0); // should never be reached
  // 651:         }
  // 652:     :
  // 653:       write "
  // 654:           frame = frame->caller_frame;
  // 655:           func = frame->cont;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_490;
}
static void entry__compiler__sim2c_484(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_main: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_main */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 647: if
  // 648:   is_main:
  // 649:     write "
  // 650:         terminate(0); // should never be reached
  // 651:       }
  // 652:   :
  // 653:     write "
  // 654:         frame = frame->caller_frame;
  // 655:         func = frame->cont;
  // 656:         frame->cont = invalid_continuation;
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_485;
  arguments->slots[2] = func__compiler__sim2c_487;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_489;
}
static void entry__compiler__sim2c_485(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 649: write "
  // 650:     terminate(0); // should never be reached
  // 651:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5c9d8231ad282235;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_487(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 653: write "
  // 654:     frame = frame->caller_frame;
  // 655:     func = frame->cont;
  // 656:     frame->cont = invalid_continuation;
  // 657:   }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a61426acc3f10dab;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_489(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 658: end_continuation
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__end_continuation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_490(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* code */, arguments->slots[0]);
  // 659: ... : append &generated_code code
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__sim2c_491, 0);
  // 659: push &actions: append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_493;
}
static void entry__compiler__sim2c_491(void) {
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
  // 659: ... append &generated_code code
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_code */;
  arguments->slots[1] = frame->slots[1] /* code */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_492;
}
static void cont__compiler__sim2c_492(void) {
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
static void cont__compiler__sim2c_493(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 660: push &all_actions actions
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* all_actions */;
  arguments->slots[1] = get__actions();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_494;
}
static void cont__compiler__sim2c_494(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* all_actions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__9 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_495(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 661: for_each all_actions: (stmt_actions) for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* all_actions */;
  arguments->slots[1] = func__compiler__sim2c_496;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_498;
}
static void entry__compiler__sim2c_497(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // action: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 661: ... action
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* action */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_496(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt_actions: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 661: ... for_each stmt_actions: (action) action
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* stmt_actions */;
  arguments->slots[1] = func__compiler__sim2c_497;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_498(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 662: for_each required_modules: (name _info) writeln "/// require @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = func__compiler__sim2c_499;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_502;
}
static void entry__compiler__sim2c_499(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 662: ... "/// require @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__58cb04c59ab3549a;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_501;
}
static void cont__compiler__sim2c_501(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 662: ... writeln "/// require @(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_502(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: for_each linked_libraries: (name) writeln "/// link @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__linked_libraries();
  arguments->slots[1] = func__compiler__sim2c_503;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_506;
}
static void entry__compiler__sim2c_503(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 663: ... "/// link @(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7d8c250ccd5bbd65;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_505;
}
static void cont__compiler__sim2c_505(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 663: ... writeln "/// link @(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_506(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 664: for_each dependent_data: (filemask) writeln "/// data @(filemask)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__dependent_data();
  arguments->slots[1] = func__compiler__sim2c_507;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_510;
}
static void entry__compiler__sim2c_507(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filemask: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 664: ... "/// data @(filemask)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6d8c238ccd0b3d65;
  arguments->slots[1] = frame->slots[0] /* filemask */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_509;
}
static void cont__compiler__sim2c_509(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 664: ... writeln "/// data @(filemask)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_510(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 665: ... required_modules.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_511;
}
static void cont__compiler__sim2c_511(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 665: unless required_modules.is_empty writeln
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = get__writeln();
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_512;
}
static void cont__compiler__sim2c_512(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 666: !included_files("runtime/platform.h") true
  frame->slots[33] /* temp__1 */ = get__true();
  // 666: !included_files("runtime/platform.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3ae3b0d72c49c8db;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_514;
}
static void cont__compiler__sim2c_514(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__included_files(arguments->slots[0]);
  // 667: if use_inline_c:
  // 668:   !included_files("stdint.h") true
  // 669:   !included_files("stdlib.h") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__use_inline_c();
  arguments->slots[1] = func__compiler__sim2c_515;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_520;
}
static void entry__compiler__sim2c_515(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 668: !included_files("stdint.h") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 668: !included_files("stdint.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72c4a8d406a50228;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_517;
}
static void cont__compiler__sim2c_517(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__included_files(arguments->slots[0]);
  // 669: !included_files("stdlib.h") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 669: !included_files("stdlib.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7cc4ad5406a55228;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_519;
}
static void cont__compiler__sim2c_519(void) {
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
static void cont__compiler__sim2c_520(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 670: for_each included_files: (name) writeln "#include <@(name)>"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__included_files();
  arguments->slots[1] = func__compiler__sim2c_521;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_525;
}
static void entry__compiler__sim2c_521(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 670: ... "#include <@(name)>"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__3d6a095dad2a247d;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cdf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_524;
}
static void cont__compiler__sim2c_524(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 670: ... writeln "#include <@(name)>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_525(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 671: ... included_files.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__included_files();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_526;
}
static void cont__compiler__sim2c_526(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 671: unless included_files.is_empty writeln
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = get__writeln();
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_527;
}
static void cont__compiler__sim2c_527(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 672: write "
  // 673:   /**********************
  // 674:   D E C L A R A T I O N S
  // 675:   **********************/
  // 676:   
  // 677:   #ifndef IMPORT
  // 678:     #define IMPORT extern
  // 679:   #endif
  // 680:   
  // 681:   #ifndef EXPORT
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36e833feb0906b55;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_529;
}
static void cont__compiler__sim2c_529(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 690: ... included_files("stdint.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__72c4a8d406a50228;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_530;
}
static void cont__compiler__sim2c_530(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 690: unless included_files("stdint.h"):
  // 691:   write "
  // 692:     typedef __INT8_TYPE__ int8_t;
  // 693:     typedef __INT16_TYPE__ int16_t;
  // 694:     typedef __INT32_TYPE__ int32_t;
  // 695:     typedef __INT64_TYPE__ int64_t;
  // 696:     typedef __INTPTR_TYPE__ intptr_t;
  // 697:     
  // 698:     #ifdef __UINT8_TYPE__
  // 699:       typedef __UINT8_TYPE__ uint8_t;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_531;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_533;
}
static void entry__compiler__sim2c_531(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 691: write "
  // 692:   typedef __INT8_TYPE__ int8_t;
  // 693:   typedef __INT16_TYPE__ int16_t;
  // 694:   typedef __INT32_TYPE__ int32_t;
  // 695:   typedef __INT64_TYPE__ int64_t;
  // 696:   typedef __INTPTR_TYPE__ intptr_t;
  // 697:   
  // 698:   #ifdef __UINT8_TYPE__
  // 699:     typedef __UINT8_TYPE__ uint8_t;
  // 700:   #else
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a047b2b18829c385;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_533(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 727: ... included_files("stdlib.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7cc4ad5406a55228;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_534;
}
static void cont__compiler__sim2c_534(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__2 */ = arguments->slots[0];
  // 727: ... included_files("stdlib.h") || included_files("stddef.h")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__2 */;
  arguments->slots[1] = func__compiler__sim2c_535;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_538;
}
static void entry__compiler__sim2c_535(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 727: ... included_files("stddef.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__64c4ac5406a5d228;
  result_count = 1;
  myself = get__included_files();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_537;
}
static void cont__compiler__sim2c_537(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 727: ... included_files("stddef.h")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_538(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 727: unless included_files("stdlib.h") || included_files("stddef.h"):
  // 728:   write "
  // 729:     typedef __SIZE_TYPE__ size_t;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = func__compiler__sim2c_539;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_541;
}
static void entry__compiler__sim2c_539(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 728: write "
  // 729:   typedef __SIZE_TYPE__ size_t;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b0f44c3748f83ed0;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_541(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 730: write "
  // 731:   // INSERT HERE //
  // 732:   
  // 733:   #if UINTPTR_MAX == 0xffffffffffffffff
  // 734:     #define FIRST_INVALID_ADDRESS 0xc000000000000000UL
  // 735:     #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)
  // 736:   #else
  // 737:     #define FIRST_INVALID_ADDRESS 0xc0000000
  // 738:     #define SAMPLE_POINTER ((void *)0x12345678)
  // 739:   #endif
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__96a80854500bbe37;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_543;
}
static void cont__compiler__sim2c_543(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 774: for_each needed_names: (name info)
  // 775:   if variable_kind_of(info) == POLYMORPHIC:
  // 776:     writeln "static int poly_idx__@(name);"
  // 777:   writeln "static NODE_GETTER get__@(name);"
  // 778:   if variable_kind_of(info) == STATIC_SINGLE:
  // 779:     writeln "static NODE_GETTER get_value_or_future__@(name);"
  // 780:   case variable_kind_of(info) STATIC_MULTI, DYNAMIC_MULTI:
  // 781:     writeln "static NODE_SETTER set__@(name);"
  // 782:   case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 783:     writeln "static NODE_SETTER define__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__needed_names();
  arguments->slots[1] = func__compiler__sim2c_544;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_572;
}
static void entry__compiler__sim2c_569(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 783: ... "static NODE_SETTER define__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__16f790c158cdffe3;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_571;
}
static void cont__compiler__sim2c_571(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 783: writeln "static NODE_SETTER define__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_544(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 775: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_545;
}
static void cont__compiler__sim2c_545(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 775: ... variable_kind_of(info) == POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_546;
}
static void cont__compiler__sim2c_546(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 775: ... :
  // 776:   writeln "static int poly_idx__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_547, 0);
  // 775: if variable_kind_of(info) == POLYMORPHIC:
  // 776:   writeln "static int poly_idx__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_551;
}
static void entry__compiler__sim2c_547(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 776: ... "static int poly_idx__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__dd59fa996655f7be;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_550;
}
static void cont__compiler__sim2c_550(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 776: writeln "static int poly_idx__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_551(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 777: ... "static NODE_GETTER get__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7bc4c42d1b67ee3a;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_553;
}
static void cont__compiler__sim2c_553(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 777: writeln "static NODE_GETTER get__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_554;
}
static void cont__compiler__sim2c_554(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 778: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_555;
}
static void cont__compiler__sim2c_555(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 778: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_556;
}
static void cont__compiler__sim2c_556(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 778: ... :
  // 779:   writeln "static NODE_GETTER get_value_or_future__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_557, 0);
  // 778: if variable_kind_of(info) == STATIC_SINGLE:
  // 779:   writeln "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_560;
}
static void entry__compiler__sim2c_557(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 779: ... "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f144f4e2b96df7e3;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_559;
}
static void cont__compiler__sim2c_559(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 779: writeln "static NODE_GETTER get_value_or_future__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_560(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 780: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_561;
}
static void cont__compiler__sim2c_561(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 780: ... STATIC_MULTI, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_MULTI();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_562;
}
static void cont__compiler__sim2c_562(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 780: ... :
  // 781:   writeln "static NODE_SETTER set__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_563, 0);
  // 780: case variable_kind_of(info) STATIC_MULTI, DYNAMIC_MULTI:
  // 781:   writeln "static NODE_SETTER set__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_566;
}
static void entry__compiler__sim2c_563(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 781: ... "static NODE_SETTER set__@(name);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7bc4c42d1b4eae3a;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cda;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_565;
}
static void cont__compiler__sim2c_565(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 781: writeln "static NODE_SETTER set__@(name);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_566(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 782: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_567;
}
static void cont__compiler__sim2c_567(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 782: ... DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__DYNAMIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_568;
}
static void cont__compiler__sim2c_568(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 782: ... :
  // 783:   writeln "static NODE_SETTER define__@(name);"
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_569, 0);
  // 782: case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 783:   writeln "static NODE_SETTER define__@(name);"
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
static void cont__compiler__sim2c_572(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 784: write "
  // 785:   static struct {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__ff4edce8b0a2fa27;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_574;
}
static void cont__compiler__sim2c_574(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 786: write generated_top_level_variable_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[16])->contents /* generated_top_level_variable_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_575;
}
static void cont__compiler__sim2c_575(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 787: write generated_global_variable_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[17])->contents /* generated_global_variable_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_576;
}
static void cont__compiler__sim2c_576(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 788: write "
  // 789:   } var;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b07009729763a0f0;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_578;
}
static void cont__compiler__sim2c_578(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 790: write "
  // 791:   static const char *var_names[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__75573d7e471fdc32;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_580;
}
static void cont__compiler__sim2c_580(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 792: ... generated_top_level_variable_names != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[15])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_581;
}
static void cont__compiler__sim2c_581(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__2 */ = arguments->slots[0];
  // 792: ... generated_top_level_variable_names != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_582;
}
static void cont__compiler__sim2c_582(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 792: ... :
  // 793:   writeln range(generated_top_level_variable_names 1 -3)
  frame->slots[35] /* temp__3 */ = create_closure(entry__compiler__sim2c_583, 0);
  // 792: if generated_top_level_variable_names != "":
  // 793:   writeln range(generated_top_level_variable_names 1 -3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = frame->slots[35] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_586;
}
static void entry__compiler__sim2c_583(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // generated_top_level_variable_names: 0
  frame->slots[0] = myself->closure.frame->slots[15]; /* generated_top_level_variable_names */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 793: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_584;
}
static void cont__compiler__sim2c_584(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 793: ... range(generated_top_level_variable_names 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_top_level_variable_names */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_585;
}
static void cont__compiler__sim2c_585(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 793: writeln range(generated_top_level_variable_names 1 -3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_586(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 794: write "};@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa727015ff16bc6;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_588;
}
static void cont__compiler__sim2c_588(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 795: write generated_declarations
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[14])->contents /* generated_declarations */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_589;
}
static void cont__compiler__sim2c_589(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 803: if
  // 804:   is_main:
  // 805:     writeln "static void main_entry(void);"
  // 806:   :
  // 807:     writeln "void run__@(module_name)(void);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_590;
  arguments->slots[2] = func__compiler__sim2c_592;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_596;
}
static void entry__compiler__sim2c_590(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 805: writeln "static void main_entry(void);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c3452dad239e6464;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_592(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 807: ... "void run__@(module_name)(void);"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__1f74a3bba8d254fe;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__a1240cd997f230c1;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_595;
}
static void cont__compiler__sim2c_595(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 807: writeln "void run__@(module_name)(void);"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_596(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 808: write "
  // 809:   
  // 810:   static CONTINUATION_INFO continuation_info[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b4688827b8af4941;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_598;
}
static void cont__compiler__sim2c_598(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 811: append &generated_continuation_table generated_delayed_continuation_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* generated_continuation_table */;
  arguments->slots[1] = ((CELL *)frame->slots[19])->contents /* generated_delayed_continuation_table */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_599;
}
static void cont__compiler__sim2c_599(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[18])->contents /* generated_continuation_table */ = arguments->slots[0];
  // 812: ... generated_continuation_table != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* generated_continuation_table */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_600;
}
static void cont__compiler__sim2c_600(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__2 */ = arguments->slots[0];
  // 812: ... generated_continuation_table != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[34] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_601;
}
static void cont__compiler__sim2c_601(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 812: ... :
  // 813:   writeln range(generated_continuation_table 1 -3)
  frame->slots[35] /* temp__3 */ = create_closure(entry__compiler__sim2c_602, 0);
  // 812: if generated_continuation_table != "":
  // 813:   writeln range(generated_continuation_table 1 -3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  arguments->slots[1] = frame->slots[35] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_605;
}
static void entry__compiler__sim2c_602(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // generated_continuation_table: 0
  frame->slots[0] = myself->closure.frame->slots[18]; /* generated_continuation_table */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 813: ... 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_603;
}
static void cont__compiler__sim2c_603(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 813: ... range(generated_continuation_table 1 -3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* generated_continuation_table */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_604;
}
static void cont__compiler__sim2c_604(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 813: writeln range(generated_continuation_table 1 -3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_605(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 814: write "
  // 815:   };
  // 816:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__380aff8b5e307d33;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_607;
}
static void cont__compiler__sim2c_607(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 817: write "
  // 818:   union NODE {
  // 819:     struct {
  // 820:       FUNC type;
  // 821:       ATTRIBUTES *attributes;
  // 822:     };
  // 823:     CONTINUATION continuation;
  // 824:     CLOSURE closure;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__817a259dab23f435;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_609;
}
static void cont__compiler__sim2c_609(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 825: if use_inline_c:
  // 826:   for_each defined_nodes: (name _node)
  // 827:     write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__use_inline_c();
  arguments->slots[1] = func__compiler__sim2c_610;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_617;
}
static void entry__compiler__sim2c_611(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // node: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 827: ... name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_612;
}
static void cont__compiler__sim2c_612(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 827: ... "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__578a5af303e9cc1;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__2d7981f4e6d02bcf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_616;
}
static void cont__compiler__sim2c_616(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 827: write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_610(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 826: for_each defined_nodes: (name _node)
  // 827:   write "  @(name) @(name.to_lower_case);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_nodes();
  arguments->slots[1] = func__compiler__sim2c_611;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_617(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 828: write "};@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa727015ff16bc6;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_618;
}
static void cont__compiler__sim2c_618(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 829: write generated_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[20])->contents /* generated_functions */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_619;
}
static void cont__compiler__sim2c_619(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 830: for_each used_literals: (name _literal) write "static NODE *@(name);@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[30])->contents /* used_literals */;
  arguments->slots[1] = func__compiler__sim2c_620;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_623;
}
static void entry__compiler__sim2c_620(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 830: ... "static NODE *@(name);@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__cb6a78473f66a6a1;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__2d7981f4e6d02bcf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_622;
}
static void cont__compiler__sim2c_622(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 830: ... write "static NODE *@(name);@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_623(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 831: write "
  // 832:   
  // 833:   static const char *used_namespaces[] = {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__44a800d7e66fda5b;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_625;
}
static void cont__compiler__sim2c_625(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 834: for_each used_namespaces: (name) write "  @quot;@(name)@quot;,@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  arguments->slots[1] = func__compiler__sim2c_626;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_630;
}
static void entry__compiler__sim2c_626(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 834: ... "  @quot;@(name)@quot;,@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fa730415f296bee;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__fa730c15f496bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_629;
}
static void cont__compiler__sim2c_629(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 834: ... write "  @quot;@(name)@quot;,@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_630(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 835: ... "
  // 836:     NULL
  // 837:   };
  // 838:   
  // 839:   static MODULE_INFO module_info = {
  // 840:     NULL,
  // 841:     "@(module_name)",
  // 842:     continuation_info,
  // 843:     sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  // 844:     (NODE **)&var,
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__5e3d918a06749390;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__b90701ef69cd6166;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_633;
}
static void cont__compiler__sim2c_633(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 835: write "
  // 836:     NULL
  // 837:   };
  // 838:   
  // 839:   static MODULE_INFO module_info = {
  // 840:     NULL,
  // 841:     "@(module_name)",
  // 842:     continuation_info,
  // 843:     sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  // 844:     (NODE **)&var,
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_634;
}
static void cont__compiler__sim2c_634(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 849: $depth count_occurrences(module_name "__")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__module_name();
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_635;
}
static void cont__compiler__sim2c_635(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[32] /* depth */, arguments->slots[0]);
  // 851: ... : ($filename)
  // 852:   truncate_until &filename '/' -(depth+1)
  // 853:   write "
  // 854:     DEBUG_FILENAME("@(filename)@quot;)@
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_636, 1);
  // 850: for_each
  // 851:   filenames: ($filename)
  // 852:     truncate_until &filename '/' -(depth+1)
  // 853:     write "
  // 854:       DEBUG_FILENAME("@(filename)@quot;)@
  // 855:   :
  // 856:     write ", "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filenames */;
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  arguments->slots[2] = func__compiler__sim2c_643;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_645;
}
static void entry__compiler__sim2c_636(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // filename: 0
  // depth: 1
  frame->slots[1] = myself->closure.frame->slots[32]; /* depth */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* filename */ = create_cell_with_contents(arguments->slots[0]);
  // 852: ... depth+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* depth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_637;
}
static void cont__compiler__sim2c_637(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 852: ... depth+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_638;
}
static void cont__compiler__sim2c_638(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 852: truncate_until &filename '/' -(depth+1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_639;
}
static void cont__compiler__sim2c_639(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 853: ... "
  // 854:   DEBUG_FILENAME("@(filename)@quot;)@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9c11f7a3e8641900;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[2] = string__2d7981f4e6182bec;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_642;
}
static void cont__compiler__sim2c_642(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 853: write "
  // 854:   DEBUG_FILENAME("@(filename)@quot;)@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_643(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 856: write ", "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6682be5;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_645(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 857: write "
  // 858:   }
  // 859:   };
  // 860:   
  // 861:   /******
  // 862:   C O D E
  // 863:   ******/
  // 864:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__d1bc6cafcb964c0d;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_647;
}
static void cont__compiler__sim2c_647(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 865: ... : (name _info)
  // 866:   $fname mangle_filename(name)
  // 867:   write "
  // 868:     IMPORT void collect__@(fname)(void);
  // 869:     IMPORT void phase_1__@(fname)(void);
  // 870:     IMPORT void phase_2__@(fname)(void);
  // 871:     IMPORT void phase_3__@(fname)(void);
  // 872:     IMPORT void phase_4__@(fname)(void);
  // 873:     IMPORT void phase_5__@(fname)(void);
  // 874:     IMPORT void phase_6__@(fname)(void);
  // ...
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_648, 2);
  // 865: for_each required_modules: (name _info)
  // 866:   $fname mangle_filename(name)
  // 867:   write "
  // 868:     IMPORT void collect__@(fname)(void);
  // 869:     IMPORT void phase_1__@(fname)(void);
  // 870:     IMPORT void phase_2__@(fname)(void);
  // 871:     IMPORT void phase_3__@(fname)(void);
  // 872:     IMPORT void phase_4__@(fname)(void);
  // 873:     IMPORT void phase_5__@(fname)(void);
  // 874:     IMPORT void phase_6__@(fname)(void);
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_659;
}
static void entry__compiler__sim2c_648(void) {
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
  // 866: $fname mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_649;
}
static void cont__compiler__sim2c_649(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* fname */, arguments->slots[0]);
  // 867: ... "
  // 868:   IMPORT void collect__@(fname)(void);
  // 869:   IMPORT void phase_1__@(fname)(void);
  // 870:   IMPORT void phase_2__@(fname)(void);
  // 871:   IMPORT void phase_3__@(fname)(void);
  // 872:   IMPORT void phase_4__@(fname)(void);
  // 873:   IMPORT void phase_5__@(fname)(void);
  // 874:   IMPORT void phase_6__@(fname)(void);
  // 875:   IMPORT void run__@(fname)(void);
  argument_count = 17;
  arguments = node_p;
  arguments->slots[0] = string__7cb40b96062f3614;
  arguments->slots[1] = frame->slots[3] /* fname */;
  arguments->slots[2] = string__4b1f5385e2b9ec5c;
  arguments->slots[3] = frame->slots[3] /* fname */;
  arguments->slots[4] = string__4b1f5345e2b9ec5c;
  arguments->slots[5] = frame->slots[3] /* fname */;
  arguments->slots[6] = string__4b1f5305e2b9ec5c;
  arguments->slots[7] = frame->slots[3] /* fname */;
  arguments->slots[8] = string__4b1f52c5e2b9ec5c;
  arguments->slots[9] = frame->slots[3] /* fname */;
  arguments->slots[10] = string__4b1f5285e2b9ec5c;
  arguments->slots[11] = frame->slots[3] /* fname */;
  arguments->slots[12] = string__4b1f5245e2b9ec5c;
  arguments->slots[13] = frame->slots[3] /* fname */;
  arguments->slots[14] = string__fa3f5235fd3e2424;
  arguments->slots[15] = frame->slots[3] /* fname */;
  arguments->slots[16] = string__66ccbf91860d092a;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_658;
}
static void cont__compiler__sim2c_658(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 867: write "
  // 868:   IMPORT void collect__@(fname)(void);
  // 869:   IMPORT void phase_1__@(fname)(void);
  // 870:   IMPORT void phase_2__@(fname)(void);
  // 871:   IMPORT void phase_3__@(fname)(void);
  // 872:   IMPORT void phase_4__@(fname)(void);
  // 873:   IMPORT void phase_5__@(fname)(void);
  // 874:   IMPORT void phase_6__@(fname)(void);
  // 875:   IMPORT void run__@(fname)(void);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_659(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 876: write generated_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[27])->contents /* generated_code */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_660;
}
static void cont__compiler__sim2c_660(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 877: write delayed_statements
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[29])->contents /* delayed_statements */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_661;
}
static void cont__compiler__sim2c_661(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 878: ... "
  // 879:   EXPORT void collect__@(module_name)(void) {
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__bcb42196062f3614;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__fc8c36a84adb366f;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_663;
}
static void cont__compiler__sim2c_663(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 878: write "
  // 879:   EXPORT void collect__@(module_name)(void) {
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_664;
}
static void cont__compiler__sim2c_664(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 880: write generated_collections
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[28])->contents /* generated_collections */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_665;
}
static void cont__compiler__sim2c_665(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 881: write "}@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4e02bcf;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_667;
}
static void cont__compiler__sim2c_667(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 882: if
  // 883:   is_main:
  // 884:     write "
  // 885:       
  // 886:       int main(int argc, char **argv) {
  // 887:         main_argc = argc;
  // 888:         main_argv = argv;
  // 889:         initialize_runtime();
  // 890:       
  // 891:         // initialization phase 1
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_668;
  arguments->slots[2] = func__compiler__sim2c_670;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_674;
}
static void entry__compiler__sim2c_668(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 884: write "
  // 885:   
  // 886:   int main(int argc, char **argv) {
  // 887:     main_argc = argc;
  // 888:     main_argv = argv;
  // 889:     initialize_runtime();
  // 890:   
  // 891:     // initialization phase 1
  // 892:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25aa47136a75b74b;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_670(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 894: ... "
  // 895:   
  // 896:   static int already_run_phase_1 = false;
  // 897:   
  // 898:   EXPORT void phase_1__@(module_name)(void) {
  // 899:     if (already_run_phase_1) return;
  // 900:     already_run_phase_1 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__1aafb345f496a1;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d7e0d1a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_673;
}
static void cont__compiler__sim2c_673(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 894: write "
  // 895:   
  // 896:   static int already_run_phase_1 = false;
  // 897:   
  // 898:   EXPORT void phase_1__@(module_name)(void) {
  // 899:     if (already_run_phase_1) return;
  // 900:     already_run_phase_1 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_674(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 901: ... : (name _info)
  // 902:   $mangled_name mangle_filename(name)
  // 903:   writeln "  phase_1__@(mangled_name)();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_675, 2);
  // 901: for_each required_modules: (name _info)
  // 902:   $mangled_name mangle_filename(name)
  // 903:   writeln "  phase_1__@(mangled_name)();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_680;
}
static void entry__compiler__sim2c_675(void) {
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
  // 902: $mangled_name mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_676;
}
static void cont__compiler__sim2c_676(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mangled_name */, arguments->slots[0]);
  // 903: ... "  phase_1__@(mangled_name)();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb25123ef1fa6f;
  arguments->slots[1] = frame->slots[3] /* mangled_name */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_679;
}
static void cont__compiler__sim2c_679(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 903: writeln "  phase_1__@(mangled_name)();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_680(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 904: write "
  // 905:   @
  // 906:     register_module_info(&module_info);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6759f0f7c95235d;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_682;
}
static void cont__compiler__sim2c_682(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 908: for_each defined_namespaces: (namespace)
  // 909:   write "
  // 910:     @
  // 911:       define_namespace("@(namespace)");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_namespaces();
  arguments->slots[1] = func__compiler__sim2c_683;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_687;
}
static void entry__compiler__sim2c_683(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // namespace: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 909: ... "
  // 910:   @
  // 911:     define_namespace("@(namespace)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__d93952e55b2e5d9;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__860afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_686;
}
static void cont__compiler__sim2c_686(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 909: write "
  // 910:   @
  // 911:     define_namespace("@(namespace)");
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_687(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 913: write generated_phase_1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[21])->contents /* generated_phase_1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_688;
}
static void cont__compiler__sim2c_688(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 914: if
  // 915:   is_main:
  // 916:     write "
  // 917:       @
  // 918:       
  // 919:         // initialization phase 2
  // 920:   :
  // 921:     write "
  // 922:       }
  // 923:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_689;
  arguments->slots[2] = func__compiler__sim2c_691;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_695;
}
static void entry__compiler__sim2c_689(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 916: write "
  // 917:   @
  // 918:   
  // 919:     // initialization phase 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f5b495312d83add5;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_691(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 921: ... "
  // 922:   }
  // 923:   
  // 924:   static int already_run_phase_2 = false;
  // 925:   
  // 926:   EXPORT void phase_2__@(module_name)(void) {
  // 927:     if (already_run_phase_2) return;
  // 928:     already_run_phase_2 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b0acf1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d4e0c9a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_694;
}
static void cont__compiler__sim2c_694(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 921: write "
  // 922:   }
  // 923:   
  // 924:   static int already_run_phase_2 = false;
  // 925:   
  // 926:   EXPORT void phase_2__@(module_name)(void) {
  // 927:     if (already_run_phase_2) return;
  // 928:     already_run_phase_2 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_695(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 929: ... : (name _info)
  // 930:   writeln "  phase_2__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_696, 2);
  // 929: for_each required_modules: (name _info)
  // 930:   writeln "  phase_2__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_700;
}
static void entry__compiler__sim2c_696(void) {
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
  // 930: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_697;
}
static void cont__compiler__sim2c_697(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 930: ... "  phase_2__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb25d23ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_699;
}
static void cont__compiler__sim2c_699(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 930: writeln "  phase_2__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_700(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 931: ... "
  // 932:   @
  // 933:     set_module("@(module_name)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f93d0720893942d5;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__860afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_702;
}
static void cont__compiler__sim2c_702(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 931: write "
  // 932:   @
  // 933:     set_module("@(module_name)");
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_703;
}
static void cont__compiler__sim2c_703(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 934: for_each used_literals: (name literal)
  // 935:   write "  @(name) = "
  // 936:   cond
  // 937:     -> literal.is_a_numeric_literal:
  // 938:       $value replace_all(node::value_of(literal) '@apos;' = "")
  // 939:       if
  // 940:         not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 941:           write "from_double(@(value));@nl;"
  // 942:         :
  // 943:           $int_val value.to_integer
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[30])->contents /* used_literals */;
  arguments->slots[1] = func__compiler__sim2c_704;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_750;
}
static void entry__compiler__sim2c_745(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 955: ... node::value_of(literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_746;
}
static void cont__compiler__sim2c_746(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 955: ... node::value_of(literal).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_747;
}
static void cont__compiler__sim2c_747(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 955: ... "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2666ac8409f84460;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_749;
}
static void cont__compiler__sim2c_749(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 955: writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_736(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 949: ... "
  // 950:   from_uint64(@(int_val)ULL);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__228915c9d5a8e125;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  arguments->slots[2] = string__1f441a036092dd;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_739;
}
static void cont__compiler__sim2c_739(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 949: write "
  // 950:   from_uint64(@(int_val)ULL);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_729(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 946: ... "
  // 947:   from_uint32(@(int_val)U);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__22891489d598e125;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  arguments->slots[2] = string__680afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_732;
}
static void cont__compiler__sim2c_732(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 946: write "
  // 947:   from_uint32(@(int_val)U);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_726(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 945: ... int_val <= 0xffffffff
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0xffffffff;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_727;
}
static void cont__compiler__sim2c_727(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 945: ... int_val <= 0xffffffff
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_728;
}
static void cont__compiler__sim2c_728(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 945: ... :
  // 946:   write "
  // 947:     from_uint32(@(int_val)U);
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__sim2c_729, 0);
  // 945: -> int_val <= 0xffffffff:
  // 946:   write "
  // 947:     from_uint32(@(int_val)U);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_733(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // int_val: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* int_val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 948: ... int_val <= 0xffffffffffffffff
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0xffffffffffffffff;
  arguments->slots[1] = frame->slots[0] /* int_val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_734;
}
static void cont__compiler__sim2c_734(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 948: ... int_val <= 0xffffffffffffffff
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_735;
}
static void cont__compiler__sim2c_735(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 948: ... :
  // 949:   write "
  // 950:     from_uint64(@(int_val)ULL);
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__sim2c_736, 0);
  // 948: -> int_val <= 0xffffffffffffffff:
  // 949:   write "
  // 950:     from_uint64(@(int_val)ULL);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_740(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 952: ... "
  // 953:   from_digit_string("@(value)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__c470b0c3df48bfe1;
  arguments->slots[1] = frame->slots[0] /* value */;
  arguments->slots[2] = string__860afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_742;
}
static void cont__compiler__sim2c_742(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 952: write "
  // 953:   from_digit_string("@(value)");
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_721(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 941: ... "from_double(@(value));@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__ecd034ad7215125;
  arguments->slots[1] = frame->slots[0] /* value */;
  arguments->slots[2] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_723;
}
static void cont__compiler__sim2c_723(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 941: write "from_double(@(value));@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_724(void) {
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
  // 943: $int_val value.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_725;
}
static void cont__compiler__sim2c_725(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* int_val */, arguments->slots[0]);
  // 945: -> int_val <= 0xffffffff:
  // 946:   write "
  // 947:     from_uint32(@(int_val)U);
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_726, 0);
  // 948: -> int_val <= 0xffffffffffffffff:
  // 949:   write "
  // 950:     from_uint64(@(int_val)ULL);
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_733, 0);
  // 951: :
  // 952:   write "
  // 953:     from_digit_string("@(value)");
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_740, 0);
  // 944: cond
  // 945:   -> int_val <= 0xffffffff:
  // 946:     write "
  // 947:       from_uint32(@(int_val)U);
  // 948:   -> int_val <= 0xffffffffffffffff:
  // 949:     write "
  // 950:       from_uint64(@(int_val)ULL);
  // 951:   :
  // 952:     write "
  // 953:       from_digit_string("@(value)");
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
static void entry__compiler__sim2c_710(void) {
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
  // 938: ... node::value_of(literal)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__node__value_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_711;
}
static void cont__compiler__sim2c_711(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 938: ... '@apos;' = ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__39;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_712;
}
static void cont__compiler__sim2c_712(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 938: $value replace_all(node::value_of(literal) '@apos;' = "")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_713;
}
static void cont__compiler__sim2c_713(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* value */, arguments->slots[0]);
  // 940: ... value .has_prefix. "0x"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = string__2d7981f4e6882bbd;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_715;
}
static void cont__compiler__sim2c_715(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 940: not(value .has_prefix. "0x")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_716;
}
static void cont__compiler__sim2c_716(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 940: ... value .contains. alt('.' 'e' 'E')
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__sim2c_717, 0);
  // 940: not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_720;
}
static void entry__compiler__sim2c_717(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 940: ... alt('.' 'e' 'E')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = character__101;
  arguments->slots[2] = character__69;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_718;
}
static void cont__compiler__sim2c_718(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 940: ... value .contains. alt('.' 'e' 'E')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_719;
}
static void cont__compiler__sim2c_719(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 940: ... value .contains. alt('.' 'e' 'E')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_720(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 940: ... :
  // 941:   write "from_double(@(value));@nl;"
  frame->slots[6] /* temp__5 */ = create_closure(entry__compiler__sim2c_721, 0);
  // 942: :
  // 943:   $int_val value.to_integer
  // 944:   cond
  // 945:     -> int_val <= 0xffffffff:
  // 946:       write "
  // 947:         from_uint32(@(int_val)U);
  // 948:     -> int_val <= 0xffffffffffffffff:
  // 949:       write "
  // 950:         from_uint64(@(int_val)ULL);
  // 951:     :
  // ...
  frame->slots[7] /* temp__6 */ = create_closure(entry__compiler__sim2c_724, 0);
  // 939: if
  // 940:   not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 941:     write "from_double(@(value));@nl;"
  // 942:   :
  // 943:     $int_val value.to_integer
  // 944:     cond
  // 945:       -> int_val <= 0xffffffff:
  // 946:         write "
  // 947:           from_uint32(@(int_val)U);
  // 948:       -> int_val <= 0xffffffffffffffff:
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
static void entry__compiler__sim2c_708(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 937: ... literal.is_a_numeric_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__is_a_numeric_literal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_709;
}
static void cont__compiler__sim2c_709(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 937: ... :
  // 938:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 939:   if
  // 940:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 941:       write "from_double(@(value));@nl;"
  // 942:     :
  // 943:       $int_val value.to_integer
  // 944:       cond
  // 945:         -> int_val <= 0xffffffff:
  // 946:           write "
  // ...
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_710, 0);
  // 937: -> literal.is_a_numeric_literal:
  // 938:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 939:   if
  // 940:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 941:       write "from_double(@(value));@nl;"
  // 942:     :
  // 943:       $int_val value.to_integer
  // 944:       cond
  // 945:         -> int_val <= 0xffffffff:
  // 946:           write "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_743(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // literal: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* literal */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 954: ... literal.is_a_character_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* literal */;
  result_count = 1;
  myself = get__is_a_character_literal();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_744;
}
static void cont__compiler__sim2c_744(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 954: ... :
  // 955:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__sim2c_745, 0);
  // 954: -> literal.is_a_character_literal:
  // 955:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_704(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // literal: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 935: ... "  @(name) = "
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__fa730415fc16bec;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_706;
}
static void cont__compiler__sim2c_706(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 935: write "  @(name) = "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_707;
}
static void cont__compiler__sim2c_707(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 937: -> literal.is_a_numeric_literal:
  // 938:   $value replace_all(node::value_of(literal) '@apos;' = "")
  // 939:   if
  // 940:     not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 941:       write "from_double(@(value));@nl;"
  // 942:     :
  // 943:       $int_val value.to_integer
  // 944:       cond
  // 945:         -> int_val <= 0xffffffff:
  // 946:           write "
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__sim2c_708, 0);
  // 954: -> literal.is_a_character_literal:
  // 955:   writeln "from_uchar32(@(node::value_of(literal).to_integer));"
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__sim2c_743, 0);
  // 936: cond
  // 937:   -> literal.is_a_numeric_literal:
  // 938:     $value replace_all(node::value_of(literal) '@apos;' = "")
  // 939:     if
  // 940:       not(value .has_prefix. "0x") && value .contains. alt('.' 'e' 'E'):
  // 941:         write "from_double(@(value));@nl;"
  // 942:       :
  // 943:         $int_val value.to_integer
  // 944:         cond
  // 945:           -> int_val <= 0xffffffff:
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
static void cont__compiler__sim2c_750(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 956: write generated_phase_2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[22])->contents /* generated_phase_2 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_751;
}
static void cont__compiler__sim2c_751(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 957: if
  // 958:   is_main:
  // 959:     write "
  // 960:       @
  // 961:       
  // 962:         // initialization phase 3
  // 963:       
  // 964:         initialize_phase_3();
  // 965:         resolve_symbols();
  // 966:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_752;
  arguments->slots[2] = func__compiler__sim2c_754;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_758;
}
static void entry__compiler__sim2c_752(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 959: write "
  // 960:   @
  // 961:   
  // 962:     // initialization phase 3
  // 963:   
  // 964:     initialize_phase_3();
  // 965:     resolve_symbols();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__cb22ed554b280fb1;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_754(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 967: ... "
  // 968:   }
  // 969:   
  // 970:   static int already_run_phase_3 = false;
  // 971:   
  // 972:   EXPORT void phase_3__@(module_name)(void) {
  // 973:     if (already_run_phase_3) return;
  // 974:     already_run_phase_3 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b0edf1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d5e0c1a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_757;
}
static void cont__compiler__sim2c_757(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 967: write "
  // 968:   }
  // 969:   
  // 970:   static int already_run_phase_3 = false;
  // 971:   
  // 972:   EXPORT void phase_3__@(module_name)(void) {
  // 973:     if (already_run_phase_3) return;
  // 974:     already_run_phase_3 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_758(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 975: ... : (name _info)
  // 976:   writeln "  phase_3__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_759, 2);
  // 975: for_each required_modules: (name _info)
  // 976:   writeln "  phase_3__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_763;
}
static void entry__compiler__sim2c_759(void) {
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
  // 976: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_760;
}
static void cont__compiler__sim2c_760(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 976: ... "  phase_3__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb25923ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_762;
}
static void cont__compiler__sim2c_762(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 976: writeln "  phase_3__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_763(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 977: ... "
  // 978:   @
  // 979:     set_module("@(module_name)");
  // 980:     set_used_namespaces(used_namespaces);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f93d0720893942d5;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__f647f212951f31f8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_765;
}
static void cont__compiler__sim2c_765(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 977: write "
  // 978:   @
  // 979:     set_module("@(module_name)");
  // 980:     set_used_namespaces(used_namespaces);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_766;
}
static void cont__compiler__sim2c_766(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 981: write generated_phase_3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[23])->contents /* generated_phase_3 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_767;
}
static void cont__compiler__sim2c_767(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 982: if
  // 983:   is_main:
  // 984:     write "
  // 985:       @
  // 986:       
  // 987:         // initialization phase 4
  // 988:       
  // 989:         initialize_phase_4();
  // 990:   :
  // 991:     write "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_768;
  arguments->slots[2] = func__compiler__sim2c_770;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_774;
}
static void entry__compiler__sim2c_768(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 984: write "
  // 985:   @
  // 986:   
  // 987:     // initialization phase 4
  // 988:   
  // 989:     initialize_phase_4();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__19b03dcd2fdc791;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_770(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 991: ... "
  // 992:   }
  // 993:   
  // 994:   static int already_run_phase_4 = false;
  // 995:   
  // 996:   EXPORT void phase_4__@(module_name)(void) {
  // 997:     if (already_run_phase_4) return;
  // 998:     already_run_phase_4 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b12af1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d2e0f9a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_773;
}
static void cont__compiler__sim2c_773(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 991: write "
  // 992:   }
  // 993:   
  // 994:   static int already_run_phase_4 = false;
  // 995:   
  // 996:   EXPORT void phase_4__@(module_name)(void) {
  // 997:     if (already_run_phase_4) return;
  // 998:     already_run_phase_4 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_774(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  //  999: ... : (name _info)
  // 1000:   writeln "  phase_4__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_775, 2);
  //  999: for_each required_modules: (name _info)
  // 1000:   writeln "  phase_4__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_779;
}
static void entry__compiler__sim2c_775(void) {
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
  // 1000: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_776;
}
static void cont__compiler__sim2c_776(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1000: ... "  phase_4__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb24523ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_778;
}
static void cont__compiler__sim2c_778(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1000: writeln "  phase_4__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_779(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1001: ... "
  // 1002:   @
  // 1003:     set_module("@(module_name)");
  // 1004:     set_used_namespaces(used_namespaces);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f93d0720893942d5;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__f647f212951f31f8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_780;
}
static void cont__compiler__sim2c_780(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 1001: write "
  // 1002:   @
  // 1003:     set_module("@(module_name)");
  // 1004:     set_used_namespaces(used_namespaces);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_781;
}
static void cont__compiler__sim2c_781(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1005: for_each needed_names: (name info)
  // 1006:   unless global_names(name).is_defined:
  // 1007:     $namespace
  // 1008:       if
  // 1009:         name .contains. "__"
  // 1010:         -> string('@quot;' name .before. "__" '@quot;')
  // 1011:         -> "NULL"
  // 1012:     
  // 1013:     $basename name .truncate_until. "__"
  // 1014:     case
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__needed_names();
  arguments->slots[1] = func__compiler__sim2c_782;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_816;
}
static void entry__compiler__sim2c_795(void) {
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
  // 1017: ... "
  // 1018:   @
  // 1019:     use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1020:   &get__@(name), &poly_idx__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__82877bb737e0bc50;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__fa733415f296bee;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__65b0238fc1fb0d7a;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__4a0e52ffba34c725;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_800;
}
static void cont__compiler__sim2c_800(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1017: write "
  // 1018:   @
  // 1019:     use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1020:   &get__@(name), &poly_idx__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_801(void) {
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
  // 1022: ... "
  // 1023:   @
  // 1024:     use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1025:   &get_value_or_future__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__c1145f87c6ab68aa;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__fa733415f296bee;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__65b0238fc1fb0d7a;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__f681eab2d5b5e9a9;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_804;
}
static void cont__compiler__sim2c_804(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1022: write "
  // 1023:   @
  // 1024:     use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1025:   &get_value_or_future__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_805(void) {
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
  // 1027: ... "
  // 1028:   @
  // 1029:     use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1030:   &set__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__f63e3617473fc88a;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__fa733415f296bee;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__65b0238fc1fb0d7a;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__6594a8f5052ca9ff;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_808;
}
static void cont__compiler__sim2c_808(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1027: write "
  // 1028:   @
  // 1029:     use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1030:   &set__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_809(void) {
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
  // 1032: ... "
  // 1033:   @
  // 1034:     use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1035:   &get__@(name), &define__@(name));
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = string__b45bfb6d6d495155;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__fa733415f296bee;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__65b0238fc1fb0d7a;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__9ccb3018e8f13bec;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_812;
}
static void cont__compiler__sim2c_812(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1032: write "
  // 1033:   @
  // 1034:     use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1035:   &get__@(name), &define__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_813(void) {
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
  // 1037: ... "
  // 1038:   @
  // 1039:     use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1040:   &get__@(name), &set__@(name), &define__@(name));
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__5b5ec7878e89a218;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  arguments->slots[2] = string__fa733415f296bee;
  arguments->slots[3] = frame->slots[1] /* basename */;
  arguments->slots[4] = string__65b0238fc1fb0d7a;
  arguments->slots[5] = frame->slots[2] /* name */;
  arguments->slots[6] = string__6594a8f5052ca9ff;
  arguments->slots[7] = frame->slots[2] /* name */;
  arguments->slots[8] = string__9ccb3018e8f13bec;
  arguments->slots[9] = frame->slots[2] /* name */;
  arguments->slots[10] = string__fa732015ff16bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_815;
}
static void cont__compiler__sim2c_815(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1037: write "
  // 1038:   @
  // 1039:     use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1040:   &get__@(name), &set__@(name), &define__@(name));
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_785(void) {
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
  // 1009: name .contains. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_786;
}
static void cont__compiler__sim2c_786(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1010: -> string('@quot;' name .before. "__" '@quot;')
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_787, 0);
  // 1007: $namespace
  // 1008:   if
  // 1009:     name .contains. "__"
  // 1010:     -> string('@quot;' name .before. "__" '@quot;')
  // 1011:     -> "NULL"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = func__compiler__sim2c_790;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_792;
}
static void entry__compiler__sim2c_787(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1010: ... name .before. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_788;
}
static void cont__compiler__sim2c_788(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1010: ... string('@quot;' name .before. "__" '@quot;')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_789;
}
static void cont__compiler__sim2c_789(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1010: -> string('@quot;' name .before. "__" '@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__sim2c_790(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1011: -> "NULL"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5e0ae40b5c007d75;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__sim2c_792(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* namespace */, arguments->slots[0]);
  // 1013: $basename name .truncate_until. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_793;
}
static void cont__compiler__sim2c_793(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* basename */, arguments->slots[0]);
  // 1015: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_794;
}
static void cont__compiler__sim2c_794(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1016: ... :
  // 1017:   write "
  // 1018:     @
  // 1019:       use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1020:     &get__@(name), &poly_idx__@(name));
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__sim2c_795, 0);
  // 1021: ... :
  // 1022:   write "
  // 1023:     @
  // 1024:       use_read_only(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1025:     &get_value_or_future__@(name));
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__sim2c_801, 0);
  // 1026: ... :
  // 1027:   write "
  // 1028:     @
  // 1029:       use_read_write(@(namespace), @quot;@(basename)", &get__@(name), @
  // 1030:     &set__@(name));
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__sim2c_805, 0);
  // 1031: ... :
  // 1032:   write "
  // 1033:     @
  // 1034:       use_single_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1035:     &get__@(name), &define__@(name));
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__sim2c_809, 0);
  // 1036: ... :
  // 1037:   write "
  // 1038:     @
  // 1039:       use_multi_assign_dynamic(@(namespace), @quot;@(basename)", @
  // 1040:     &get__@(name), &set__@(name), &define__@(name));
  frame->slots[9] /* temp__6 */ = create_closure(entry__compiler__sim2c_813, 0);
  // 1014: case
  // 1015:   variable_kind_of(info)
  // 1016:   POLYMORPHIC:
  // 1017:     write "
  // 1018:       @
  // 1019:         use_polymorphic_function(@(namespace), @quot;@(basename)", @
  // 1020:       &get__@(name), &poly_idx__@(name));
  // 1021:   STATIC_SINGLE:
  // 1022:     write "
  // 1023:       @
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
static void entry__compiler__sim2c_782(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1006: ... global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_783;
}
static void cont__compiler__sim2c_783(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1006: ... global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_784;
}
static void cont__compiler__sim2c_784(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1006: ... :
  // 1007:   $namespace
  // 1008:     if
  // 1009:       name .contains. "__"
  // 1010:       -> string('@quot;' name .before. "__" '@quot;')
  // 1011:       -> "NULL"
  // 1012:   
  // 1013:   $basename name .truncate_until. "__"
  // 1014:   case
  // 1015:     variable_kind_of(info)
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__sim2c_785, 0);
  // 1006: unless global_names(name).is_defined:
  // 1007:   $namespace
  // 1008:     if
  // 1009:       name .contains. "__"
  // 1010:       -> string('@quot;' name .before. "__" '@quot;')
  // 1011:       -> "NULL"
  // 1012:   
  // 1013:   $basename name .truncate_until. "__"
  // 1014:   case
  // 1015:     variable_kind_of(info)
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
static void cont__compiler__sim2c_816(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1041: write generated_phase_4
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[24])->contents /* generated_phase_4 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_817;
}
static void cont__compiler__sim2c_817(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1042: if is_main:
  // 1043:   write "
  // 1044:     @
  // 1045:       resolve_attributes();
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_818;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_820;
}
static void entry__compiler__sim2c_818(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1043: write "
  // 1044:   @
  // 1045:     resolve_attributes();
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29050caaed294603;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_820(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1046: if
  // 1047:   is_main:
  // 1048:     write "
  // 1049:       
  // 1050:         // initialization phase 5
  // 1051:       @;
  // 1052:   :
  // 1053:     write "
  // 1054:       }
  // 1055:       
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_821;
  arguments->slots[2] = func__compiler__sim2c_823;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_827;
}
static void entry__compiler__sim2c_821(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1048: write "
  // 1049:   
  // 1050:     // initialization phase 5
  // 1051:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a9896ddd6eafadae;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_823(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1053: ... "
  // 1054:   }
  // 1055:   
  // 1056:   static int already_run_phase_5 = false;
  // 1057:   
  // 1058:   EXPORT void phase_5__@(module_name)(void) {
  // 1059:     if (already_run_phase_5) return;
  // 1060:     already_run_phase_5 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b16bf1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d3e0f1a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_826;
}
static void cont__compiler__sim2c_826(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1053: write "
  // 1054:   }
  // 1055:   
  // 1056:   static int already_run_phase_5 = false;
  // 1057:   
  // 1058:   EXPORT void phase_5__@(module_name)(void) {
  // 1059:     if (already_run_phase_5) return;
  // 1060:     already_run_phase_5 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_827(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1061: ... : (name _info)
  // 1062:   writeln "  phase_5__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_828, 2);
  // 1061: for_each required_modules: (name _info)
  // 1062:   writeln "  phase_5__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_832;
}
static void entry__compiler__sim2c_828(void) {
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
  // 1062: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_829;
}
static void cont__compiler__sim2c_829(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1062: ... "  phase_5__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb24123ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_831;
}
static void cont__compiler__sim2c_831(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1062: writeln "  phase_5__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_832(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1063: write generated_phase_5
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[25])->contents /* generated_phase_5 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_833;
}
static void cont__compiler__sim2c_833(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1064: if
  // 1065:   is_main:
  // 1066:     write "
  // 1067:         initialize_function_attributes();
  // 1068:       
  // 1069:         // initialization phase 6
  // 1070:       @;
  // 1071:   :
  // 1072:     write "
  // 1073:       }
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_834;
  arguments->slots[2] = func__compiler__sim2c_836;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_840;
}
static void entry__compiler__sim2c_834(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1066: write "
  // 1067:     initialize_function_attributes();
  // 1068:   
  // 1069:     // initialization phase 6
  // 1070:   @;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1cd8a7b21f5517c3;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__sim2c_836(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1072: ... "
  // 1073:   }
  // 1074:   
  // 1075:   static int already_run_phase_6 = false;
  // 1076:   
  // 1077:   EXPORT void phase_6__@(module_name)(void) {
  // 1078:     if (already_run_phase_6) return;
  // 1079:     already_run_phase_6 = true;
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b9a3b1a8f1dfe8ab;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__d0e0e9a7b944caae;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_839;
}
static void cont__compiler__sim2c_839(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1072: write "
  // 1073:   }
  // 1074:   
  // 1075:   static int already_run_phase_6 = false;
  // 1076:   
  // 1077:   EXPORT void phase_6__@(module_name)(void) {
  // 1078:     if (already_run_phase_6) return;
  // 1079:     already_run_phase_6 = true;
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_840(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1080: ... : (name _info)
  // 1081:   writeln "  phase_6__@(mangle_filename(name))();"
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_841, 2);
  // 1080: for_each required_modules: (name _info)
  // 1081:   writeln "  phase_6__@(mangle_filename(name))();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__required_modules();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_845;
}
static void entry__compiler__sim2c_841(void) {
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
  // 1081: ... mangle_filename(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* mangle_filename */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_842;
}
static void cont__compiler__sim2c_842(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1081: ... "  phase_6__@(mangle_filename(name))();"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fedb24d23ef1fa6f;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__fa732415f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_844;
}
static void cont__compiler__sim2c_844(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1081: writeln "  phase_6__@(mangle_filename(name))();"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_845(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1082: write generated_phase_6
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[26])->contents /* generated_phase_6 */;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_846;
}
static void cont__compiler__sim2c_846(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1083: ... "  register_collector(collect__@(module_name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__476ac52a7f81f4a0;
  arguments->slots[1] = get__module_name();
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_848;
}
static void cont__compiler__sim2c_848(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__1 */ = arguments->slots[0];
  // 1083: writeln "  register_collector(collect__@(module_name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[33] /* temp__1 */;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_849;
}
static void cont__compiler__sim2c_849(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1084: if is_main:
  // 1085:   write "
  // 1086:     @
  // 1087:       execute(main_entry);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* is_main */;
  arguments->slots[1] = func__compiler__sim2c_850;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_852;
}
static void entry__compiler__sim2c_850(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1085: write "
  // 1086:   @
  // 1087:     execute(main_entry);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__3734ffa0d2ae2d12;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_852(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1088: write "}@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4e02bcf;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_853;
}
static void cont__compiler__sim2c_853(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1089: ... : write_timing_info "generating" filenames(1)
  frame->slots[33] /* temp__1 */ = create_closure(entry__compiler__sim2c_854, 0);
  // 1089: if do_time_passes: write_timing_info "generating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = frame->slots[33] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__sim2c_857;
}
static void entry__compiler__sim2c_854(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filenames: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filenames */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1089: ... filenames(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* filenames */;
  func = myself->type;
  frame->cont = cont__compiler__sim2c_855;
}
static void cont__compiler__sim2c_855(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1089: ... write_timing_info "generating" filenames(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1d702a52a35b6426;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__sim2c_857(void) {
  myself = frame->slots[2] /* return__10 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__sim2c(void) {
  var.compiler__print_source = collect_node(var.compiler__print_source);
  var.compiler__eprint_source = collect_node(var.compiler__eprint_source);
  var.compiler__privileged_polymorphic_functions = collect_node(var.compiler__privileged_polymorphic_functions);
  var.compiler__generate_dispatcher_function = collect_node(var.compiler__generate_dispatcher_function);
  var._demangled = collect_node(var._demangled);
  var.compiler__update_info = collect_node(var.compiler__update_info);
  var.compiler__sim2c = collect_node(var.compiler__sim2c);
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
  number__6 = from_uint32(6U);
  character__35 = from_uchar32(35);
  number__99 = from_uint32(99U);
  character__47 = from_uchar32(47);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__4 = from_uint32(4U);
  number__0xffffffffffffffff = from_uint64(18446744073709551615ULL);
  number__0xffffffff = from_uint32(4294967295U);
  character__60 = from_uchar32(60);
  character__34 = from_uchar32(34);
  number__5 = from_uint32(5U);
  character__39 = from_uchar32(39);
  character__32 = from_uchar32(32);
  character__101 = from_uchar32(101);
  number__1 = from_uint32(1U);
  character__69 = from_uchar32(69);
  character__46 = from_uchar32(46);
  number__2 = from_uint32(2U);
  string__7ca425275e2bb55b = from_latin_1_string("<newline>", 9);
  func__compiler__print_source_4 = create_function(entry__compiler__print_source_4, 0);
  string__41a1d3500d2c5fd2 = from_latin_1_string("<indent_marker>", 15);
  func__compiler__print_source_6 = create_function(entry__compiler__print_source_6, 0);
  string__4b30bdab57f18372 = from_latin_1_string("<outdent_marker>", 16);
  func__compiler__print_source_8 = create_function(entry__compiler__print_source_8, 0);
  func__compiler__print_source_2 = create_function(entry__compiler__print_source_2, 1);
  func__compiler__print_source_1 = create_function(entry__compiler__print_source_1, 1);
  func__compiler__eprint_source_4 = create_function(entry__compiler__eprint_source_4, 0);
  func__compiler__eprint_source_5 = create_function(entry__compiler__eprint_source_5, 0);
  func__compiler__eprint_source_6 = create_function(entry__compiler__eprint_source_6, 0);
  func__compiler__eprint_source_2 = create_function(entry__compiler__eprint_source_2, 1);
  func__compiler__eprint_source_1 = create_function(entry__compiler__eprint_source_1, 1);
  string__7fb24a3fca4aa852 = from_latin_1_string("static void type__", 18);
  string__66ccbf91860d092a = from_latin_1_string("(void);\012", 8);
  string__fc8c36a84adb366f = from_latin_1_string("(void) {\012", 9);
  string__75f4eb726550b6de = from_latin_1_string("  myself = get_attribute(arguments->slots[0], poly_idx__", 56);
  string__d81f45a403c7e2f7 = from_latin_1_string("); // ", 6);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  string__fa732015ff16bc6 = from_latin_1_string(");\012", 3);
  string__3dbc7d1f8cf28ba6 = from_latin_1_string(
    "  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {\n"
    "    if (argument_count != 1) {\n"
    "      if (argument_count != 2) invalid_arguments_error();\n"
    "      NODE *attr = arguments->slots[1];\n"
    "      NODE *temp = clone_object_and_attributes(arguments->slots[0]);\n"
    "      update_start_p = node_p;\n"
    "      set_attribute_value(temp->attributes, poly_idx__",
    328);
  string__9f2e0c02fff25101 = from_latin_1_string(
    ", attr);\n"
    "      arguments = node_p;\n"
    "      argument_count = 1;\n"
    "      arguments->slots[0] = temp;\n"
    "    } else {\n"
    "      arguments = node_p;\n"
    "      arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);\n"
    "    }\n"
    "    func = frame->cont;\n"
    "    frame->cont = invalid_continuation;\n"
    "  } else {\n"
    "    func = myself->type;\n"
    "  }\n"
    "}\n",
    308);
  func__compiler__generate_dispatcher_function_1 = create_function(entry__compiler__generate_dispatcher_function_1, 1);
  string__2d7981f4e5f02b9a = from_latin_1_string("__", 2);
  string__2d7981f4e6d82bff = from_latin_1_string("::", 2);
  func__demangled_1 = create_function(entry__demangled_1, 1);
  string__94b9534b986c24a9 = from_latin_1_string("The symbol \042", 12);
  string__634c61c70382d128 = from_latin_1_string("\042 is used as a polymorphic function and cannot be used otherwise!", 65);
  string__67c02c7b1bf18880 = from_latin_1_string("\042 is used as a polymorphic function and id assigned to!", 55);
  string__f8ba3c062f1b8631 = from_latin_1_string("\042 is used as a single-assign dynamic and is assigned to!", 56);
  string__aafcf41c458e8f41 = from_latin_1_string("\042 is used as a polymorphic function and as a single-assign dynamic!", 67);
  string__80670d894d05691d = from_latin_1_string("\042 is used as a single-assign dynamic and as a multi-assign dynamic!", 67);
  string__a09d645d506640e9 = from_latin_1_string("\042 is used as a polymorphic function and as a multi-assign dynamic!", 66);
  func__compiler__update_info_1 = create_function(entry__compiler__update_info_1, 3);
  string__2d7981f4e6782bea = from_latin_1_string("./", 2);
  func__compiler__sim2c_2 = create_function(entry__compiler__sim2c_2, 1);
  func__compiler__sim2c_19 = create_function(entry__compiler__sim2c_19, 2);
  string__5e0ae28b5c407d7c = from_latin_1_string("NODE", 4);
  string__1c6c7289032a5d69 = from_latin_1_string("SIMPLE_NODE", 11);
  string__38b3477328e1d61b = from_latin_1_string("Source file is not in a valid utf-8-encoding!", 45);
  func__compiler__sim2c_51 = create_function(entry__compiler__sim2c_51, 0);
  string__5a1f574683baa2f5 = from_latin_1_string("load \042", 6);
  string__2d7981f4e6182bcf = from_latin_1_string("\042\012", 2);
  string__ba340f9515cad09d = from_latin_1_string("loading", 7);
  string__1cbf9967f0b4797a = from_latin_1_string("Empty source text!", 18);
  func__compiler__sim2c_64 = create_function(entry__compiler__sim2c_64, 0);
  string__cdb2cfe249b97e8f = from_latin_1_string("Whitespace at start of source text!", 35);
  func__compiler__sim2c_70 = create_function(entry__compiler__sim2c_70, 0);
  string__f5ba012e5873af55 = from_latin_1_string("Missing newline at end of source text!", 38);
  func__compiler__sim2c_77 = create_function(entry__compiler__sim2c_77, 0);
  string__2d7981f4e6102be4 = from_latin_1_string("#!", 2);
  string__28e9a3192e794ba6 = from_latin_1_string("fragmenting", 11);
  func__compiler__sim2c_89 = create_function(entry__compiler__sim2c_89, 1);
  string__170b25ca95be486 = from_latin_1_string("tokenizing", 10);
  string__94440f9215cbe09d = from_latin_1_string("parsing", 7);
  string__72f826ea16a3e460 = from_latin_1_string("terminate", 9);
  func__compiler__sim2c_130 = create_function(entry__compiler__sim2c_130, 1);
  string__66f024ec077397c2 = from_latin_1_string("expanding", 9);
  string__1d581a51a85b6426 = from_latin_1_string("annotating", 10);
  func__compiler__sim2c_146 = create_function(entry__compiler__sim2c_146, 0);
  func__compiler__sim2c_147 = create_function(entry__compiler__sim2c_147, 0);
  string__c3e1e344d34946eb = from_latin_1_string("basic/stdlib", 12);
  string__b567219b137172d = from_latin_1_string("system/stdlib", 13);
  func__compiler__sim2c_152 = create_function(entry__compiler__sim2c_152, 0);
  string__a23c0f9515cb809d = from_latin_1_string("nothing", 7);
  string__fa724815d896ba8 = from_latin_1_string("std", 3);
  func__compiler__sim2c_161 = create_function(entry__compiler__sim2c_161, 0);
  string__b18861f6a8c886ba = from_latin_1_string("An identifier named \042", 21);
  string__95b7f6cc14260ab8 = from_latin_1_string("\042 was already defined", 21);
  string__69658745890c070 = from_latin_1_string("The definition of \042", 19);
  string__c419bd2045fe53aa = from_latin_1_string("\042 clashes with the already defined identifier \042", 47);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__b5bb4d11daae5f7a = from_latin_1_string("\042 clashes with the definition of \042", 34);
  string__6de219341b32224c = from_latin_1_string("\042 because both namespaces are used", 34);
  string__5ab424ea8372e502 = from_latin_1_string("analyzing", 9);
  func__compiler__sim2c_247 = create_function(entry__compiler__sim2c_247, 1);
  func__compiler__sim2c_267 = create_function(entry__compiler__sim2c_267, 1);
  func__compiler__sim2c_266 = create_function(entry__compiler__sim2c_266, 1);
  string__72ed7b1f2279c943 = from_latin_1_string("simplifying", 11);
  string__7c84ae5484fdf7e0 = from_latin_1_string("_define ", 8);
  func__compiler__sim2c_275 = create_function(entry__compiler__sim2c_275, 1);
  func__compiler__sim2c_274 = create_function(entry__compiler__sim2c_274, 1);
  func__compiler__sim2c_283 = create_function(entry__compiler__sim2c_283, 1);
  string__7690af9104a5e1e7 = from_latin_1_string("mangling", 8);
  string__405aee03eb306008 = from_latin_1_string("get__", 5);
  string__c44673b4643f1172 = from_latin_1_string("GENERATE DEFINITIONS", 20);
  func__compiler__sim2c_383 = create_function(entry__compiler__sim2c_383, 1);
  func__compiler__sim2c_421 = create_function(entry__compiler__sim2c_421, 0);
  string__c050814d5faecc7a = from_latin_1_string("GENERATE STATEMENTS", 19);
  string__295c7d0427bb24d8 = from_latin_1_string("main_entry", 10);
  string__41028e5a9545c479 = from_latin_1_string("  allocate_initialized_frame_gc(0, ", 35);
  string__2d7981f4e6402bfe = from_latin_1_string(");", 2);
  string__4594ae5b852cb87f = from_latin_1_string("  {run__", 8);
  string__3794a6c106b6c980 = from_latin_1_string(", NULL, ", 8);
  string__8eebb379fdb22853 = from_latin_1_string(
    "static int already_run = false;\n"
    "\n"
    "EXPORT void run__",
    50);
  string__bbab7a959fd798d = from_latin_1_string(
    "(void) {\n"
    "  if (already_run) {\n"
    "    func = frame->cont;\n"
    "    frame->cont = invalid_continuation;\n"
    "    return;\n"
    "  }\n"
    "  already_run = true;\n"
    "  allocate_initialized_frame_gc(0, ",
    167);
  string__ca75d5c2b6ab3b0c = from_latin_1_string("  func = run__", 14);
  string__3fab381eeea84c47 = from_latin_1_string(
    ";\n"
    "  frame->cont = cont__run__",
    29);
  string__b40af3cb5d887d33 = from_latin_1_string(
    ";\n"
    "}\n",
    4);
  string__6a214ac420f089ff = from_latin_1_string("cont__run__", 11);
  func__compiler__sim2c_472 = create_function(entry__compiler__sim2c_472, 1);
  func__compiler__sim2c_476 = create_function(entry__compiler__sim2c_476, 0);
  string__5c9d8231ad282235 = from_latin_1_string(
    "  terminate(0); // should never be reached\n"
    "}\n",
    45);
  func__compiler__sim2c_485 = create_function(entry__compiler__sim2c_485, 0);
  string__a61426acc3f10dab = from_latin_1_string(
    "  frame = frame->caller_frame;\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "}\n",
    93);
  func__compiler__sim2c_487 = create_function(entry__compiler__sim2c_487, 0);
  func__compiler__sim2c_497 = create_function(entry__compiler__sim2c_497, 1);
  func__compiler__sim2c_496 = create_function(entry__compiler__sim2c_496, 1);
  string__58cb04c59ab3549a = from_latin_1_string("/// require ", 12);
  func__compiler__sim2c_499 = create_function(entry__compiler__sim2c_499, 2);
  string__7d8c250ccd5bbd65 = from_latin_1_string("/// link ", 9);
  func__compiler__sim2c_503 = create_function(entry__compiler__sim2c_503, 1);
  string__6d8c238ccd0b3d65 = from_latin_1_string("/// data ", 9);
  func__compiler__sim2c_507 = create_function(entry__compiler__sim2c_507, 1);
  string__3ae3b0d72c49c8db = from_latin_1_string("runtime/platform.h", 18);
  string__72c4a8d406a50228 = from_latin_1_string("stdint.h", 8);
  string__7cc4ad5406a55228 = from_latin_1_string("stdlib.h", 8);
  func__compiler__sim2c_515 = create_function(entry__compiler__sim2c_515, 0);
  string__3d6a095dad2a247d = from_latin_1_string("#include <", 10);
  string__578a5af303e9cdf = from_latin_1_string(">", 1);
  func__compiler__sim2c_521 = create_function(entry__compiler__sim2c_521, 1);
  string__36e833feb0906b55 = from_latin_1_string(
    "/**********************\n"
    "D E C L A R A T I O N S\n"
    "**********************/\n"
    "\n"
    "#ifndef IMPORT\n"
    "  #define IMPORT extern\n"
    "#endif\n"
    "\n"
    "#ifndef EXPORT\n"
    "  #define EXPORT\n"
    "#endif\n"
    "\n"
    "#ifndef NULL\n"
    "  #define NULL ((void *)0)\n"
    "#endif\n"
    "#define false 0\n"
    "#define true 1\n",
    238);
  string__a047b2b18829c385 = from_latin_1_string(
    "typedef __INT8_TYPE__ int8_t;\n"
    "typedef __INT16_TYPE__ int16_t;\n"
    "typedef __INT32_TYPE__ int32_t;\n"
    "typedef __INT64_TYPE__ int64_t;\n"
    "typedef __INTPTR_TYPE__ intptr_t;\n"
    "\n"
    "#ifdef __UINT8_TYPE__\n"
    "  typedef __UINT8_TYPE__ uint8_t;\n"
    "#else\n"
    "  typedef unsigned __INT8_TYPE__ uint8_t;\n"
    "#endif\n"
    "\n"
    "#ifdef __UINT16_TYPE__\n"
    "  typedef __UINT16_TYPE__ uint16_t;\n"
    "#else\n"
    "  typedef unsigned __INT16_TYPE__ uint16_t;\n"
    "#endif\n"
    "\n"
    "#ifdef __UINT32_TYPE__\n"
    "  typedef __UINT32_TYPE__ uint32_t;\n"
    "#else\n"
    "  typedef unsigned __INT32_TYPE__ uint32_t;\n"
    "#endif\n"
    "\n"
    "#ifdef __UINT64_TYPE__\n"
    "  typedef __UINT64_TYPE__ uint64_t;\n"
    "#else\n"
    "  typedef unsigned __INT64_TYPE__ uint64_t;\n"
    "#endif\n"
    "\n"
    "#ifdef __UINTPTR_TYPE__\n"
    "  typedef __UINTPTR_TYPE__ uintptr_t;\n"
    "#else\n"
    "  typedef unsigned __INTPTR_TYPE__ uintptr_t;\n"
    "#endif\n",
    745);
  func__compiler__sim2c_531 = create_function(entry__compiler__sim2c_531, 0);
  string__64c4ac5406a5d228 = from_latin_1_string("stddef.h", 8);
  func__compiler__sim2c_535 = create_function(entry__compiler__sim2c_535, 0);
  string__b0f44c3748f83ed0 = from_latin_1_string("typedef __SIZE_TYPE__ size_t;\012", 30);
  func__compiler__sim2c_539 = create_function(entry__compiler__sim2c_539, 0);
  string__96a80854500bbe37 = from_latin_1_string(
    "// INSERT HERE //\n"
    "\n"
    "#if UINTPTR_MAX == 0xffffffffffffffff\n"
    "  #define FIRST_INVALID_ADDRESS 0xc000000000000000UL\n"
    "  #define SAMPLE_POINTER ((void *)0x123456789abcdef0UL)\n"
    "#else\n"
    "  #define FIRST_INVALID_ADDRESS 0xc0000000\n"
    "  #define SAMPLE_POINTER ((void *)0x12345678)\n"
    "#endif\n"
    "\n"
    "#define MAKE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)+1))\n"
    "#define RETRIEVE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)-1))\n"
    "#define CONTAINS_AN_ATTRIBUTE_VALUE(node) (((uintptr_t)node)&1)\n"
    "\n"
    "#define ENCODE_ADDRESS(addr) ((void *)((uintptr_t)addr | 2))\n"
    "#define DECODE_ADDRESS(addr) ((void *)((uintptr_t)addr & -3))\n"
    "#define IS_AN_INVALID_ADDRESS(addr) ((uintptr_t)addr & 2)\n"
    "\n"
    "#define MSB (1L << (8*sizeof(void *)-1))\n"
    "#define ENCODE_TO_LENGTH(addr) ((void *)(((uintptr_t)addr >> 1) | MSB))\n"
    "#define DECODE_FROM_LENGTH(addr) ((void *)((uintptr_t)addr << 1))\n"
    "#define IS_AN_INVALID_LENGTH(addr) ((uintptr_t)addr & MSB)\n"
    "\n"
    "#define IS_COLLECTED(addr) (((void *)(addr)) >= coll_node_buf && ((void *)(addr)) < coll_node_buf_end)\n"
    "#define IS_STATIC(addr) (((void *)(addr)) >= static_node_buf && ((void *)(addr)) < static_node_buf_end)\n"
    "#define MARK(addr) (((MEMORY_BLOCK *)(addr))-1)->mark = current_mark;\n"
    "\n"
    "#define ALLOCATION_SIZE(size) (((size)+sizeof(void *)-1)&-sizeof(void *))\n"
    "#define TYPEOF(node) (node)->type\n"
    "#define SIZEOF(node) (node)->attributes->vtable->size\n"
    "\n"
    "#ifdef WITHIN_LIBRARY\n"
    "  #define DEBUG_FILENAME(filename) filename\n"
    "#else\n"
    "  #define DEBUG_FILENAME(filename) \042./\042 filename\n"
    "#endif\n"
    "\n"
    "#ifdef __CYGWIN__\n"
    "  extern FUNC invalid_continuation;\n"
    "#else\n"
    "  extern void invalid_continuation(void);\n"
    "#endif\n",
    1572);
  string__dd59fa996655f7be = from_latin_1_string("static int poly_idx__", 21);
  string__578a5af303e9cda = from_latin_1_string(";", 1);
  string__7bc4c42d1b67ee3a = from_latin_1_string("static NODE_GETTER get__", 24);
  string__f144f4e2b96df7e3 = from_latin_1_string("static NODE_GETTER get_value_or_future__", 40);
  string__7bc4c42d1b4eae3a = from_latin_1_string("static NODE_SETTER set__", 24);
  string__16f790c158cdffe3 = from_latin_1_string("static NODE_SETTER define__", 27);
  func__compiler__sim2c_544 = create_function(entry__compiler__sim2c_544, 2);
  string__ff4edce8b0a2fa27 = from_latin_1_string("static struct {\012", 16);
  string__b07009729763a0f0 = from_latin_1_string("} var;\012", 7);
  string__75573d7e471fdc32 = from_latin_1_string("static const char *var_names[] = {\012", 35);
  string__fa727015ff16bc6 = from_latin_1_string("};\012", 3);
  string__c3452dad239e6464 = from_latin_1_string("static void main_entry(void);", 29);
  func__compiler__sim2c_590 = create_function(entry__compiler__sim2c_590, 0);
  string__1f74a3bba8d254fe = from_latin_1_string("void run__", 10);
  string__a1240cd997f230c1 = from_latin_1_string("(void);", 7);
  func__compiler__sim2c_592 = create_function(entry__compiler__sim2c_592, 0);
  string__b4688827b8af4941 = from_latin_1_string(
    "\n"
    "static CONTINUATION_INFO continuation_info[] = {\n",
    50);
  string__380aff8b5e307d33 = from_latin_1_string(
    "};\n"
    "\n",
    4);
  string__817a259dab23f435 = from_latin_1_string(
    "union NODE {\n"
    "  struct {\n"
    "    FUNC type;\n"
    "    ATTRIBUTES *attributes;\n"
    "  };\n"
    "  CONTINUATION continuation;\n"
    "  CLOSURE closure;\n",
    120);
  string__2d7981f4e6082be5 = from_latin_1_string("  ", 2);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  string__2d7981f4e6d02bcf = from_latin_1_string(";\012", 2);
  func__compiler__sim2c_611 = create_function(entry__compiler__sim2c_611, 2);
  func__compiler__sim2c_610 = create_function(entry__compiler__sim2c_610, 0);
  string__cb6a78473f66a6a1 = from_latin_1_string("static NODE *", 13);
  func__compiler__sim2c_620 = create_function(entry__compiler__sim2c_620, 2);
  string__44a800d7e66fda5b = from_latin_1_string(
    "\n"
    "static const char *used_namespaces[] = {\n",
    42);
  string__fa730415f296bee = from_latin_1_string("  \042", 3);
  string__fa730c15f496bc6 = from_latin_1_string("\042,\012", 3);
  func__compiler__sim2c_626 = create_function(entry__compiler__sim2c_626, 1);
  string__5e3d918a06749390 = from_latin_1_string(
    "  NULL\n"
    "};\n"
    "\n"
    "static MODULE_INFO module_info = {\n"
    "  NULL,\n"
    "  \042",
    57);
  string__b90701ef69cd6166 = from_latin_1_string(
    "\042,\n"
    "  continuation_info,\n"
    "  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),\n"
    "  (NODE **)&var,\n"
    "  var_names,\n"
    "  sizeof(var_names)/sizeof(const char *),\n"
    "  used_namespaces,\n"
    "  {",
    173);
  string__9c11f7a3e8641900 = from_latin_1_string("DEBUG_FILENAME(\042", 16);
  string__2d7981f4e6182bec = from_latin_1_string("\042)", 2);
  string__2d7981f4e6682be5 = from_latin_1_string(", ", 2);
  func__compiler__sim2c_643 = create_function(entry__compiler__sim2c_643, 0);
  string__d1bc6cafcb964c0d = from_latin_1_string(
    "}\n"
    "};\n"
    "\n"
    "/******\n"
    "C O D E\n"
    "******/\n"
    "\n",
    31);
  string__7cb40b96062f3614 = from_latin_1_string("IMPORT void collect__", 21);
  string__4b1f5385e2b9ec5c = from_latin_1_string(
    "(void);\n"
    "IMPORT void phase_1__",
    29);
  string__4b1f5345e2b9ec5c = from_latin_1_string(
    "(void);\n"
    "IMPORT void phase_2__",
    29);
  string__4b1f5305e2b9ec5c = from_latin_1_string(
    "(void);\n"
    "IMPORT void phase_3__",
    29);
  string__4b1f52c5e2b9ec5c = from_latin_1_string(
    "(void);\n"
    "IMPORT void phase_4__",
    29);
  string__4b1f5285e2b9ec5c = from_latin_1_string(
    "(void);\n"
    "IMPORT void phase_5__",
    29);
  string__4b1f5245e2b9ec5c = from_latin_1_string(
    "(void);\n"
    "IMPORT void phase_6__",
    29);
  string__fa3f5235fd3e2424 = from_latin_1_string(
    "(void);\n"
    "IMPORT void run__",
    25);
  string__bcb42196062f3614 = from_latin_1_string("EXPORT void collect__", 21);
  string__2d7981f4e4e02bcf = from_latin_1_string("}\012", 2);
  string__25aa47136a75b74b = from_latin_1_string(
    "\n"
    "int main(int argc, char **argv) {\n"
    "  main_argc = argc;\n"
    "  main_argv = argv;\n"
    "  initialize_runtime();\n"
    "\n"
    "  // initialization phase 1\n"
    "\n",
    129);
  func__compiler__sim2c_668 = create_function(entry__compiler__sim2c_668, 0);
  string__1aafb345f496a1 = from_latin_1_string(
    "\n"
    "static int already_run_phase_1 = false;\n"
    "\n"
    "EXPORT void phase_1__",
    63);
  string__d7e0d1a7b944caae = from_latin_1_string(
    "(void) {\n"
    "  if (already_run_phase_1) return;\n"
    "  already_run_phase_1 = true;\n",
    74);
  func__compiler__sim2c_670 = create_function(entry__compiler__sim2c_670, 0);
  string__fedb25123ef1fa6f = from_latin_1_string("  phase_1__", 11);
  string__fa732415f616bf7 = from_latin_1_string("();", 3);
  string__6759f0f7c95235d = from_latin_1_string("  register_module_info(&module_info);\012", 38);
  string__d93952e55b2e5d9 = from_latin_1_string("  define_namespace(\042", 20);
  string__860afb0b5fb87d33 = from_latin_1_string("\042);\012", 4);
  func__compiler__sim2c_683 = create_function(entry__compiler__sim2c_683, 1);
  string__f5b495312d83add5 = from_latin_1_string(
    "\n"
    "  // initialization phase 2\n",
    29);
  func__compiler__sim2c_689 = create_function(entry__compiler__sim2c_689, 0);
  string__b9a3b0acf1dfe8ab = from_latin_1_string(
    "}\n"
    "\n"
    "static int already_run_phase_2 = false;\n"
    "\n"
    "EXPORT void phase_2__",
    65);
  string__d4e0c9a7b944caae = from_latin_1_string(
    "(void) {\n"
    "  if (already_run_phase_2) return;\n"
    "  already_run_phase_2 = true;\n",
    74);
  func__compiler__sim2c_691 = create_function(entry__compiler__sim2c_691, 0);
  string__fedb25d23ef1fa6f = from_latin_1_string("  phase_2__", 11);
  string__f93d0720893942d5 = from_latin_1_string("  set_module(\042", 14);
  string__fa730415fc16bec = from_latin_1_string(" = ", 3);
  string__2d7981f4e6882bbd = from_latin_1_string("0x", 2);
  string__ecd034ad7215125 = from_latin_1_string("from_double(", 12);
  string__22891489d598e125 = from_latin_1_string("from_uint32(", 12);
  string__680afb0b5fb87d33 = from_latin_1_string("U);\012", 4);
  string__228915c9d5a8e125 = from_latin_1_string("from_uint64(", 12);
  string__1f441a036092dd = from_latin_1_string("ULL);\012", 6);
  string__c470b0c3df48bfe1 = from_latin_1_string("from_digit_string(\042", 19);
  string__2666ac8409f84460 = from_latin_1_string("from_uchar32(", 13);
  func__compiler__sim2c_704 = create_function(entry__compiler__sim2c_704, 2);
  string__cb22ed554b280fb1 = from_latin_1_string(
    "\n"
    "  // initialization phase 3\n"
    "\n"
    "  initialize_phase_3();\n"
    "  resolve_symbols();\n",
    75);
  func__compiler__sim2c_752 = create_function(entry__compiler__sim2c_752, 0);
  string__b9a3b0edf1dfe8ab = from_latin_1_string(
    "}\n"
    "\n"
    "static int already_run_phase_3 = false;\n"
    "\n"
    "EXPORT void phase_3__",
    65);
  string__d5e0c1a7b944caae = from_latin_1_string(
    "(void) {\n"
    "  if (already_run_phase_3) return;\n"
    "  already_run_phase_3 = true;\n",
    74);
  func__compiler__sim2c_754 = create_function(entry__compiler__sim2c_754, 0);
  string__fedb25923ef1fa6f = from_latin_1_string("  phase_3__", 11);
  string__f647f212951f31f8 = from_latin_1_string(
    "\042);\n"
    "  set_used_namespaces(used_namespaces);\n",
    44);
  string__19b03dcd2fdc791 = from_latin_1_string(
    "\n"
    "  // initialization phase 4\n"
    "\n"
    "  initialize_phase_4();\n",
    54);
  func__compiler__sim2c_768 = create_function(entry__compiler__sim2c_768, 0);
  string__b9a3b12af1dfe8ab = from_latin_1_string(
    "}\n"
    "\n"
    "static int already_run_phase_4 = false;\n"
    "\n"
    "EXPORT void phase_4__",
    65);
  string__d2e0f9a7b944caae = from_latin_1_string(
    "(void) {\n"
    "  if (already_run_phase_4) return;\n"
    "  already_run_phase_4 = true;\n",
    74);
  func__compiler__sim2c_770 = create_function(entry__compiler__sim2c_770, 0);
  string__fedb24523ef1fa6f = from_latin_1_string("  phase_4__", 11);
  string__5e0ae40b5c007d75 = from_latin_1_string("NULL", 4);
  func__compiler__sim2c_790 = create_function(entry__compiler__sim2c_790, 0);
  string__82877bb737e0bc50 = from_latin_1_string("  use_polymorphic_function(", 27);
  string__fa733415f296bee = from_latin_1_string(", \042", 3);
  string__65b0238fc1fb0d7a = from_latin_1_string("\042, &get__", 9);
  string__4a0e52ffba34c725 = from_latin_1_string(", &poly_idx__", 13);
  string__c1145f87c6ab68aa = from_latin_1_string("  use_read_only(", 16);
  string__f681eab2d5b5e9a9 = from_latin_1_string(", &get_value_or_future__", 24);
  string__f63e3617473fc88a = from_latin_1_string("  use_read_write(", 17);
  string__6594a8f5052ca9ff = from_latin_1_string(", &set__", 8);
  string__b45bfb6d6d495155 = from_latin_1_string("  use_single_assign_dynamic(", 28);
  string__9ccb3018e8f13bec = from_latin_1_string(", &define__", 11);
  string__5b5ec7878e89a218 = from_latin_1_string("  use_multi_assign_dynamic(", 27);
  func__compiler__sim2c_782 = create_function(entry__compiler__sim2c_782, 2);
  string__29050caaed294603 = from_latin_1_string("  resolve_attributes();\012", 24);
  func__compiler__sim2c_818 = create_function(entry__compiler__sim2c_818, 0);
  string__a9896ddd6eafadae = from_latin_1_string(
    "\n"
    "  // initialization phase 5\n"
    "\n",
    30);
  func__compiler__sim2c_821 = create_function(entry__compiler__sim2c_821, 0);
  string__b9a3b16bf1dfe8ab = from_latin_1_string(
    "}\n"
    "\n"
    "static int already_run_phase_5 = false;\n"
    "\n"
    "EXPORT void phase_5__",
    65);
  string__d3e0f1a7b944caae = from_latin_1_string(
    "(void) {\n"
    "  if (already_run_phase_5) return;\n"
    "  already_run_phase_5 = true;\n",
    74);
  func__compiler__sim2c_823 = create_function(entry__compiler__sim2c_823, 0);
  string__fedb24123ef1fa6f = from_latin_1_string("  phase_5__", 11);
  string__1cd8a7b21f5517c3 = from_latin_1_string(
    "  initialize_function_attributes();\n"
    "\n"
    "  // initialization phase 6\n"
    "\n",
    66);
  func__compiler__sim2c_834 = create_function(entry__compiler__sim2c_834, 0);
  string__b9a3b1a8f1dfe8ab = from_latin_1_string(
    "}\n"
    "\n"
    "static int already_run_phase_6 = false;\n"
    "\n"
    "EXPORT void phase_6__",
    65);
  string__d0e0e9a7b944caae = from_latin_1_string(
    "(void) {\n"
    "  if (already_run_phase_6) return;\n"
    "  already_run_phase_6 = true;\n",
    74);
  func__compiler__sim2c_836 = create_function(entry__compiler__sim2c_836, 0);
  string__fedb24d23ef1fa6f = from_latin_1_string("  phase_6__", 11);
  string__476ac52a7f81f4a0 = from_latin_1_string("  register_collector(collect__", 30);
  string__3734ffa0d2ae2d12 = from_latin_1_string("  execute(main_entry);\012", 23);
  func__compiler__sim2c_850 = create_function(entry__compiler__sim2c_850, 0);
  string__1d702a52a35b6426 = from_latin_1_string("generating", 10);
  func__compiler__sim2c_1 = create_function(entry__compiler__sim2c_1, -1);
  string__cc48021895f2809c = from_latin_1_string("std__if", 7);
  string__cb05e9320ae22386 = from_latin_1_string("std__is_defined", 15);
  string__17988d443223256d = from_latin_1_string("std__equal", 10);
  string__76a027f311988656 = from_latin_1_string("std__less", 9);
  string__58b854e1382f539f = from_latin_1_string("std__length_of", 14);
  string__d8272d0f8bc407b3 = from_latin_1_string("std__is_empty", 13);
  string__582190112b914cb7 = from_latin_1_string("std__unless", 11);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__sim2c(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("sim2c");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("compiler", "print_source", get__compiler__print_source, &var.compiler__print_source);
  define_single_assign_static("compiler", "eprint_source", get__compiler__eprint_source, &var.compiler__eprint_source);
  define_single_assign_static("compiler", "privileged_polymorphic_functions", get__compiler__privileged_polymorphic_functions, &var.compiler__privileged_polymorphic_functions);
  define_single_assign_static("compiler", "generate_dispatcher_function", get__compiler__generate_dispatcher_function, &var.compiler__generate_dispatcher_function);
  define_single_assign_static("compiler", "update_info", get__compiler__update_info, &var.compiler__update_info);
  define_single_assign_static("compiler", "sim2c", get__compiler__sim2c, &var.compiler__sim2c);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__sim2c(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
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
  use_multi_assign_dynamic("compiler", "actions", &get__compiler__actions, &set__compiler__actions, &define__compiler__actions);
  use_multi_assign_dynamic("compiler", "assigned_names", &get__compiler__assigned_names, &set__compiler__assigned_names, &define__compiler__assigned_names);
  use_multi_assign_dynamic("compiler", "current_continuation_info", &get__compiler__current_continuation_info, &set__compiler__current_continuation_info, &define__compiler__current_continuation_info);
  use_multi_assign_dynamic("compiler", "defined_functions", &get__compiler__defined_functions, &set__compiler__defined_functions, &define__compiler__defined_functions);
  use_multi_assign_dynamic("compiler", "defined_names", &get__compiler__defined_names, &set__compiler__defined_names, &define__compiler__defined_names);
  use_multi_assign_dynamic("compiler", "defined_namespaces", &get__compiler__defined_namespaces, &set__compiler__defined_namespaces, &define__compiler__defined_namespaces);
  use_multi_assign_dynamic("compiler", "defined_nodes", &get__compiler__defined_nodes, &set__compiler__defined_nodes, &define__compiler__defined_nodes);
  use_multi_assign_dynamic("compiler", "defined_structs", &get__compiler__defined_structs, &set__compiler__defined_structs, &define__compiler__defined_structs);
  use_multi_assign_dynamic("compiler", "delayed_code", &get__compiler__delayed_code, &set__compiler__delayed_code, &define__compiler__delayed_code);
  use_multi_assign_dynamic("compiler", "dependent_data", &get__compiler__dependent_data, &set__compiler__dependent_data, &define__compiler__dependent_data);
  use_multi_assign_dynamic("compiler", "enumeration_count", &get__compiler__enumeration_count, &set__compiler__enumeration_count, &define__compiler__enumeration_count);
  use_multi_assign_dynamic("compiler", "exported_names", &get__compiler__exported_names, &set__compiler__exported_names, &define__compiler__exported_names);
  use_multi_assign_dynamic("compiler", "global_names", &get__compiler__global_names, &set__compiler__global_names, &define__compiler__global_names);
  use_multi_assign_dynamic("compiler", "included_files", &get__compiler__included_files, &set__compiler__included_files, &define__compiler__included_files);
  use_multi_assign_dynamic("compiler", "index", &get__compiler__index, &set__compiler__index, &define__compiler__index);
  use_multi_assign_dynamic("compiler", "linked_libraries", &get__compiler__linked_libraries, &set__compiler__linked_libraries, &define__compiler__linked_libraries);
  use_multi_assign_dynamic("compiler", "namespace_mappings", &get__compiler__namespace_mappings, &set__compiler__namespace_mappings, &define__compiler__namespace_mappings);
  use_multi_assign_dynamic("compiler", "needed_names", &get__compiler__needed_names, &set__compiler__needed_names, &define__compiler__needed_names);
  use_multi_assign_dynamic("compiler", "required_modules", &get__compiler__required_modules, &set__compiler__required_modules, &define__compiler__required_modules);
  use_multi_assign_dynamic("compiler", "string_literals", &get__compiler__string_literals, &set__compiler__string_literals, &define__compiler__string_literals);
  use_single_assign_dynamic("compiler", "submodule_no", &get__compiler__submodule_no, &define__compiler__submodule_no);
  use_single_assign_dynamic("compiler", "suffix", &get__compiler__suffix, &define__compiler__suffix);
  use_multi_assign_dynamic("compiler", "temp_idx", &get__compiler__temp_idx, &set__compiler__temp_idx, &define__compiler__temp_idx);
  use_single_assign_dynamic("compiler", "use_identifier", &get__compiler__use_identifier, &define__compiler__use_identifier);
  use_multi_assign_dynamic("compiler", "use_inline_c", &get__compiler__use_inline_c, &set__compiler__use_inline_c, &define__compiler__use_inline_c);
  use_single_assign_dynamic("compiler", "use_literal", &get__compiler__use_literal, &define__compiler__use_literal);
  use_multi_assign_dynamic("compiler", "used_names", &get__compiler__used_names, &set__compiler__used_names, &define__compiler__used_names);
  use_multi_assign_dynamic("compiler", "used_namespaces", &get__compiler__used_namespaces, &set__compiler__used_namespaces, &define__compiler__used_namespaces);
  use_single_assign_dynamic("compiler", "write_to_continuation_table", &get__compiler__write_to_continuation_table, &define__compiler__write_to_continuation_table);
  use_single_assign_dynamic("compiler", "write_to_declarations", &get__compiler__write_to_declarations, &define__compiler__write_to_declarations);
  use_single_assign_dynamic("compiler", "write_to_delayed_continuation_table", &get__compiler__write_to_delayed_continuation_table, &define__compiler__write_to_delayed_continuation_table);
  use_single_assign_dynamic("compiler", "write_to_delayed_statements", &get__compiler__write_to_delayed_statements, &define__compiler__write_to_delayed_statements);
  use_single_assign_dynamic("compiler", "write_to_functions", &get__compiler__write_to_functions, &define__compiler__write_to_functions);
  use_single_assign_dynamic("compiler", "write_to_generated_collections", &get__compiler__write_to_generated_collections, &define__compiler__write_to_generated_collections);
  use_single_assign_dynamic("compiler", "write_to_global_variable_declarations", &get__compiler__write_to_global_variable_declarations, &define__compiler__write_to_global_variable_declarations);
  use_single_assign_dynamic("compiler", "write_to_phase_1", &get__compiler__write_to_phase_1, &define__compiler__write_to_phase_1);
  use_single_assign_dynamic("compiler", "write_to_phase_2", &get__compiler__write_to_phase_2, &define__compiler__write_to_phase_2);
  use_single_assign_dynamic("compiler", "write_to_phase_3", &get__compiler__write_to_phase_3, &define__compiler__write_to_phase_3);
  use_single_assign_dynamic("compiler", "write_to_phase_4", &get__compiler__write_to_phase_4, &define__compiler__write_to_phase_4);
  use_single_assign_dynamic("compiler", "write_to_phase_5", &get__compiler__write_to_phase_5, &define__compiler__write_to_phase_5);
  use_single_assign_dynamic("compiler", "write_to_phase_6", &get__compiler__write_to_phase_6, &define__compiler__write_to_phase_6);
  use_single_assign_dynamic("compiler", "write_to_top_level_variable_declarations", &get__compiler__write_to_top_level_variable_declarations, &define__compiler__write_to_top_level_variable_declarations);
  use_single_assign_dynamic("compiler", "write_to_top_level_variable_names", &get__compiler__write_to_top_level_variable_names, &define__compiler__write_to_top_level_variable_names);
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
  use_read_only(NULL, "defined_namespaces", &get__defined_namespaces, &get_value_or_future__defined_namespaces);
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
  use_read_only(NULL, "mangled_name_of", &get__mangled_name_of, &get_value_or_future__mangled_name_of);
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
  use_multi_assign_dynamic(NULL, "used_string_literals", &get__used_string_literals, &set__used_string_literals, &define__used_string_literals);
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

static int already_run_phase_5 = false;

EXPORT void phase_5__sim2c(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.compiler__print_source, &func__compiler__print_source_1);
  assign_variable(&var.compiler__eprint_source, &func__compiler__eprint_source_1);
  assign_variable(&var.compiler__generate_dispatcher_function, &func__compiler__generate_dispatcher_function_1);
  assign_variable(&var._demangled, &func__demangled_1);
  assign_variable(&var.compiler__update_info, &func__compiler__update_info_1);
  assign_variable(&var.compiler__sim2c, &func__compiler__sim2c_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__sim2c(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__sim2c);
}
